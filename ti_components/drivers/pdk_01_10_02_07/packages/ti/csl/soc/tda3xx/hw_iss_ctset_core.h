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
 *  \file   hw_iss_ctset_core.h
 *
 *  \brief  Register-level header file for ISS_CTSET_CORE
 *
**/

#ifndef HW_ISS_CTSET_CORE_H_
#define HW_ISS_CTSET_CORE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define CTSETIDEN                                                   (0x0U)
#define CTSETSYSCFG                                                 (0x10U)
#define SETSTR                                                      (0x14U)
#define CTSETCFG                                                    (0x24U)
#define SETSPLREG                                                   (0x28U)
#define SETEVTENBL1                                                 (0x30U)
#define SETEVTENBL2                                                 (0x34U)
#define SETEVTENBL3                                                 (0x38U)
#define SETEVTENBL4                                                 (0x3cU)
#define SETEVTENBL5                                                 (0x40U)
#define SETEVTENBL6                                                 (0x44U)
#define SETEVTENBL7                                                 (0x48U)
#define SETEVTENBL8                                                 (0x4cU)
#define SETMSTID                                                    (0x50U)
#define CTCNTL                                                      (0x800U)
#define CTSTMCNTL                                                   (0x820U)
#define CTSTMMSTID                                                  (0x824U)
#define CTSTMINTVL                                                  (0x828U)
#define CTSTMSEL0                                                   (0x82cU)
#define CTSTMSEL1                                                   (0x830U)
#define TINTVLR0                                                    (0x840U)
#define TINTVLR1                                                    (0x844U)
#define TINTVLR2                                                    (0x848U)
#define TINTVLR3                                                    (0x84cU)
#define TINTVLR4                                                    (0x850U)
#define TINTVLR5                                                    (0x854U)
#define TINTVLR6                                                    (0x858U)
#define TINTVLR7                                                    (0x85cU)
#define TINTVLR8                                                    (0x860U)
#define TINTVLR9                                                    (0x864U)
#define TINTVLR10                                                   (0x868U)
#define TINTVLR11                                                   (0x86cU)
#define TINTVLR12                                                   (0x870U)
#define TINTVLR13                                                   (0x874U)
#define TINTVLR14                                                   (0x878U)
#define TINTVLR15                                                   (0x87cU)
#define CTNUMDBG                                                    (0x8c0U)
#define CTDBGSGL0                                                   (0x8c4U)
#define CTDBGSGL1                                                   (0x8c8U)
#define CTDBGSGL2                                                   (0x8ccU)
#define CTDBGSGL3                                                   (0x8d0U)
#define CTDBGSGL4                                                   (0x8d4U)
#define CTDBGSGL5                                                   (0x8d8U)
#define CTDBGSGL6                                                   (0x8dcU)
#define CTDBGSGL7                                                   (0x8e0U)
#define CTGNBL0                                                     (0x9f0U)
#define CTGNBL1                                                     (0x9f4U)
#define CTGRST0                                                     (0x9f8U)
#define CTGRST1                                                     (0x9fcU)
#define CTCR0                                                       (0xa00U)
#define CTCR1                                                       (0xa04U)
#define CTCR2                                                       (0xa08U)
#define CTCR3                                                       (0xa0cU)
#define CTCR4                                                       (0xa10U)
#define CTCR5                                                       (0xa14U)
#define CTCR6                                                       (0xa18U)
#define CTCR7                                                       (0xa1cU)
#define CTCR8                                                       (0xa20U)
#define CTCR9                                                       (0xa24U)
#define CTCR10                                                      (0xa28U)
#define CTCR11                                                      (0xa2cU)
#define CTCR12                                                      (0xa30U)
#define CTCR13                                                      (0xa34U)
#define CTCR14                                                      (0xa38U)
#define CTCR15                                                      (0xa3cU)
#define CTCR16                                                      (0xa40U)
#define CTCR17                                                      (0xa44U)
#define CTCR18                                                      (0xa48U)
#define CTCR19                                                      (0xa4cU)
#define CTCR20                                                      (0xa50U)
#define CTCR21                                                      (0xa54U)
#define CTCR22                                                      (0xa58U)
#define CTCR23                                                      (0xa5cU)
#define CTCR24                                                      (0xa60U)
#define CTCR25                                                      (0xa64U)
#define CTCR26                                                      (0xa68U)
#define CTCR27                                                      (0xa6cU)
#define CTCR28                                                      (0xa70U)
#define CTCR29                                                      (0xa74U)
#define CTCR30                                                      (0xa78U)
#define CTCR31                                                      (0xa7cU)
#define CTCNTR0                                                     (0xb00U)
#define CTCNTR1                                                     (0xb04U)
#define CTCNTR2                                                     (0xb08U)
#define CTCNTR3                                                     (0xb0cU)
#define CTCNTR4                                                     (0xb10U)
#define CTCNTR5                                                     (0xb14U)
#define CTCNTR6                                                     (0xb18U)
#define CTCNTR7                                                     (0xb1cU)
#define CTCNTR8                                                     (0xb20U)
#define CTCNTR9                                                     (0xb24U)
#define CTCNTR10                                                    (0xb28U)
#define CTCNTR11                                                    (0xb2cU)
#define CTCNTR12                                                    (0xb30U)
#define CTCNTR13                                                    (0xb34U)
#define CTCNTR14                                                    (0xb38U)
#define CTCNTR15                                                    (0xb3cU)
#define CTCNTR16                                                    (0xb40U)
#define CTCNTR17                                                    (0xb44U)
#define CTCNTR18                                                    (0xb48U)
#define CTCNTR19                                                    (0xb4cU)
#define CTCNTR20                                                    (0xb50U)
#define CTCNTR21                                                    (0xb54U)
#define CTCNTR22                                                    (0xb58U)
#define CTCNTR23                                                    (0xb5cU)
#define CTCNTR24                                                    (0xb60U)
#define CTCNTR25                                                    (0xb64U)
#define CTCNTR26                                                    (0xb68U)
#define CTCNTR27                                                    (0xb6cU)
#define CTCNTR28                                                    (0xb70U)
#define CTCNTR29                                                    (0xb74U)
#define CTCNTR30                                                    (0xb78U)
#define CTCNTR31                                                    (0xb7cU)
#define CTEOI                                                       (0xc00U)
#define CTIRQSTAT_RAW                                               (0xc04U)
#define CTIRQSTAT                                                   (0xc08U)
#define CTIRQENABLE_SET                                             (0xc0cU)
#define CTIRQENABLE_CLR                                             (0xc10U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define CTSETIDEN_MINOR_SHIFT                                                           (0U)
#define CTSETIDEN_MINOR_MASK                                                            (0x0000003fU)

#define CTSETIDEN_CUSTOM_SHIFT                                                          (6U)
#define CTSETIDEN_CUSTOM_MASK                                                           (0x000000c0U)

#define CTSETIDEN_MAJOR_SHIFT                                                           (8U)
#define CTSETIDEN_MAJOR_MASK                                                            (0x00000700U)

#define CTSETIDEN_RTL_SHIFT                                                             (11U)
#define CTSETIDEN_RTL_MASK                                                              (0x0000f800U)

#define CTSETIDEN_FUNCTION_SHIFT                                                        (16U)
#define CTSETIDEN_FUNCTION_MASK                                                         (0x0fff0000U)

#define CTSETIDEN_SCHEME_SHIFT                                                          (30U)
#define CTSETIDEN_SCHEME_MASK                                                           (0xc0000000U)

#define CTSETIDEN_RESERVED_SHIFT                                                        (28U)
#define CTSETIDEN_RESERVED_MASK                                                         (0x30000000U)

#define CTSETSYSCFG_SOFTRESET_SHIFT                                                     (0U)
#define CTSETSYSCFG_SOFTRESET_MASK                                                      (0x00000001U)

#define CTSETSYSCFG_IDLEMODE_SHIFT                                                      (2U)
#define CTSETSYSCFG_IDLEMODE_MASK                                                       (0x0000000cU)

#define CTSETSYSCFG_RESERVED1_SHIFT                                                     (1U)
#define CTSETSYSCFG_RESERVED1_MASK                                                      (0x00000002U)

#define CTSETSYSCFG_RESERVED2_SHIFT                                                     (4U)
#define CTSETSYSCFG_RESERVED2_MASK                                                      (0xfffffff0U)

#define SETSTR_RESETDONE_SHIFT                                                          (0U)
#define SETSTR_RESETDONE_MASK                                                           (0x00000001U)

#define SETSTR_HWFIFOEMPTY_SHIFT                                                        (8U)
#define SETSTR_HWFIFOEMPTY_MASK                                                         (0x00000100U)

#define SETSTR_RESERVED1_SHIFT                                                          (1U)
#define SETSTR_RESERVED1_MASK                                                           (0x000000feU)

#define SETSTR_RESERVED2_SHIFT                                                          (9U)
#define SETSTR_RESERVED2_MASK                                                           (0xfffffe00U)

#define CTSETCFG_STARTCAPONTRIG_SHIFT                                                   (1U)
#define CTSETCFG_STARTCAPONTRIG_MASK                                                    (0x00000002U)

#define CTSETCFG_STOPCAPONTRIG_SHIFT                                                    (2U)
#define CTSETCFG_STOPCAPONTRIG_MASK                                                     (0x00000004U)

#define CTSETCFG_DETECTMODE_SHIFT                                                       (3U)
#define CTSETCFG_DETECTMODE_MASK                                                        (0x00000008U)

#define CTSETCFG_EVENTEDGE_SHIFT                                                        (4U)
#define CTSETCFG_EVENTEDGE_MASK                                                         (0x00000010U)

#define CTSETCFG_CAPENABLE_SHIFT                                                        (7U)
#define CTSETCFG_CAPENABLE_MASK                                                         (0x00000080U)

#define CTSETCFG_OWNERSHIP_SHIFT                                                        (28U)
#define CTSETCFG_OWNERSHIP_MASK                                                         (0xf0000000U)

#define CTSETCFG_RESERVED1_SHIFT                                                        (0U)
#define CTSETCFG_RESERVED1_MASK                                                         (0x00000001U)

#define CTSETCFG_RESERVED2_SHIFT                                                        (5U)
#define CTSETCFG_RESERVED2_MASK                                                         (0x00000060U)

#define CTSETCFG_RESERVED3_SHIFT                                                        (8U)
#define CTSETCFG_RESERVED3_MASK                                                         (0x0fffff00U)

#define SETSPLREG_WINDOWSIZE_SHIFT                                                      (0U)
#define SETSPLREG_WINDOWSIZE_MASK                                                       (0x000000ffU)

#define SETSPLREG_RESERVED_SHIFT                                                        (8U)
#define SETSPLREG_RESERVED_MASK                                                         (0xffffff00U)

#define SETEVTENBL1_EVTENABLE_SHIFT                                                     (0U)
#define SETEVTENBL1_EVTENABLE_MASK                                                      (0xffffffffU)

#define SETEVTENBL2_EVTENABLE_SHIFT                                                     (0U)
#define SETEVTENBL2_EVTENABLE_MASK                                                      (0xffffffffU)

#define SETEVTENBL3_EVTENABLE_SHIFT                                                     (0U)
#define SETEVTENBL3_EVTENABLE_MASK                                                      (0xffffffffU)

#define SETEVTENBL4_EVTENABLE_SHIFT                                                     (0U)
#define SETEVTENBL4_EVTENABLE_MASK                                                      (0xffffffffU)

#define SETEVTENBL5_EVTENABLE_SHIFT                                                     (0U)
#define SETEVTENBL5_EVTENABLE_MASK                                                      (0xffffffffU)

#define SETEVTENBL6_EVTENABLE_SHIFT                                                     (0U)
#define SETEVTENBL6_EVTENABLE_MASK                                                      (0xffffffffU)

#define SETEVTENBL7_EVTENABLE_SHIFT                                                     (0U)
#define SETEVTENBL7_EVTENABLE_MASK                                                      (0xffffffffU)

#define SETEVTENBL8_EVTENABLE_SHIFT                                                     (0U)
#define SETEVTENBL8_EVTENABLE_MASK                                                      (0x7fffffffU)

#define SETEVTENBL8_RESERVED_SHIFT                                                      (31U)
#define SETEVTENBL8_RESERVED_MASK                                                       (0x80000000U)

#define SETMSTID_MASTID_SHIFT                                                           (0U)
#define SETMSTID_MASTID_MASK                                                            (0x000000ffU)

#define SETMSTID_RESERVED_SHIFT                                                         (8U)
#define SETMSTID_RESERVED_MASK                                                          (0xffffff00U)

#define CTCNTL_ENBL_SHIFT                                                               (0U)
#define CTCNTL_ENBL_MASK                                                                (0x00000001U)

#define CTCNTL_RESERVED_SHIFT                                                           (1U)
#define CTCNTL_RESERVED_MASK                                                            (0x00000006U)

#define CTCNTL_REVID_SHIFT                                                              (3U)
#define CTCNTL_REVID_MASK                                                               (0x00000078U)

#define CTCNTL_NUMCNTR_SHIFT                                                            (7U)
#define CTCNTL_NUMCNTR_MASK                                                             (0x00001f80U)

#define CTCNTL_NUMTIMR_SHIFT                                                            (13U)
#define CTCNTL_NUMTIMR_MASK                                                             (0x0003e000U)

#define CTCNTL_NUMINPT_SHIFT                                                            (18U)
#define CTCNTL_NUMINPT_MASK                                                             (0x03fc0000U)

#define CTCNTL_NUMSTM_SHIFT                                                             (26U)
#define CTCNTL_NUMSTM_MASK                                                              (0xfc000000U)

#define CTSTMCNTL_ENBL_SHIFT                                                            (0U)
#define CTSTMCNTL_ENBL_MASK                                                             (0x00000001U)

#define CTSTMCNTL_SENDOVR_SHIFT                                                         (1U)
#define CTSTMCNTL_SENDOVR_MASK                                                          (0x00000002U)

#define CTSTMCNTL_CSMXPORT_SHIFT                                                        (2U)
#define CTSTMCNTL_CSMXPORT_MASK                                                         (0x00000004U)

#define CTSTMCNTL_CCMAVAIL_SHIFT                                                        (3U)
#define CTSTMCNTL_CCMAVAIL_MASK                                                         (0x00000008U)

#define CTSTMCNTL_CCMXPORT_SHIFT                                                        (4U)
#define CTSTMCNTL_CCMXPORT_MASK                                                         (0x00000010U)

#define CTSTMCNTL_XPORTACT_SHIFT                                                        (5U)
#define CTSTMCNTL_XPORTACT_MASK                                                         (0x00000020U)

#define CTSTMCNTL_NUMXPORT_SHIFT                                                        (6U)
#define CTSTMCNTL_NUMXPORT_MASK                                                         (0x00000fc0U)

#define CTSTMCNTL_RESERVED_SHIFT                                                        (12U)
#define CTSTMCNTL_RESERVED_MASK                                                         (0xfffff000U)

#define CTSTMMSTID_MASTID_SHIFT                                                         (0U)
#define CTSTMMSTID_MASTID_MASK                                                          (0x000000ffU)

#define CTSTMMSTID_RESERVED_SHIFT                                                       (8U)
#define CTSTMMSTID_RESERVED_MASK                                                        (0xffffff00U)

#define CTSTMINTVL_INTERVAL_SHIFT                                                       (0U)
#define CTSTMINTVL_INTERVAL_MASK                                                        (0x0000ffffU)

#define CTSTMINTVL_RESERVED_SHIFT                                                       (16U)
#define CTSTMINTVL_RESERVED_MASK                                                        (0xffff0000U)

#define CTSTMSEL0_COUNTSEL_SHIFT                                                        (0U)
#define CTSTMSEL0_COUNTSEL_MASK                                                         (0xffffffffU)

#define CTSTMSEL1_COUNTSEL_SHIFT                                                        (0U)
#define CTSTMSEL1_COUNTSEL_MASK                                                         (0xffffffffU)

#define TINTVLR0_INTERVAL_SHIFT                                                         (0U)
#define TINTVLR0_INTERVAL_MASK                                                          (0xffffffffU)

#define TINTVLR1_INTERVAL_SHIFT                                                         (0U)
#define TINTVLR1_INTERVAL_MASK                                                          (0xffffffffU)

#define TINTVLR2_INTERVAL_SHIFT                                                         (0U)
#define TINTVLR2_INTERVAL_MASK                                                          (0xffffffffU)

#define TINTVLR3_INTERVAL_SHIFT                                                         (0U)
#define TINTVLR3_INTERVAL_MASK                                                          (0xffffffffU)

#define TINTVLR4_INTERVAL_SHIFT                                                         (0U)
#define TINTVLR4_INTERVAL_MASK                                                          (0xffffffffU)

#define TINTVLR5_INTERVAL_SHIFT                                                         (0U)
#define TINTVLR5_INTERVAL_MASK                                                          (0xffffffffU)

#define TINTVLR6_INTERVAL_SHIFT                                                         (0U)
#define TINTVLR6_INTERVAL_MASK                                                          (0xffffffffU)

#define TINTVLR7_INTERVAL_SHIFT                                                         (0U)
#define TINTVLR7_INTERVAL_MASK                                                          (0xffffffffU)

#define TINTVLR8_INTERVAL_SHIFT                                                         (0U)
#define TINTVLR8_INTERVAL_MASK                                                          (0xffffffffU)

#define TINTVLR9_INTERVAL_SHIFT                                                         (0U)
#define TINTVLR9_INTERVAL_MASK                                                          (0xffffffffU)

#define TINTVLR10_INTERVAL_SHIFT                                                        (0U)
#define TINTVLR10_INTERVAL_MASK                                                         (0xffffffffU)

#define TINTVLR11_INTERVAL_SHIFT                                                        (0U)
#define TINTVLR11_INTERVAL_MASK                                                         (0xffffffffU)

#define TINTVLR12_INTERVAL_SHIFT                                                        (0U)
#define TINTVLR12_INTERVAL_MASK                                                         (0xffffffffU)

#define TINTVLR13_INTERVAL_SHIFT                                                        (0U)
#define TINTVLR13_INTERVAL_MASK                                                         (0xffffffffU)

#define TINTVLR14_INTERVAL_SHIFT                                                        (0U)
#define TINTVLR14_INTERVAL_MASK                                                         (0xffffffffU)

#define TINTVLR15_INTERVAL_SHIFT                                                        (0U)
#define TINTVLR15_INTERVAL_MASK                                                         (0xffffffffU)

#define CTNUMDBG_NUMEVNT_SHIFT                                                          (0U)
#define CTNUMDBG_NUMEVNT_MASK                                                           (0x0000000fU)

#define CTNUMDBG_RESERVED_SHIFT                                                         (4U)
#define CTNUMDBG_RESERVED_MASK                                                          (0xfffffff0U)

#define CTDBGSGL0_INPSEL_SHIFT                                                          (0U)
#define CTDBGSGL0_INPSEL_MASK                                                           (0x000000ffU)

#define CTDBGSGL0_RESERVED_SHIFT                                                        (8U)
#define CTDBGSGL0_RESERVED_MASK                                                         (0xffffff00U)

#define CTDBGSGL1_INPSEL_SHIFT                                                          (0U)
#define CTDBGSGL1_INPSEL_MASK                                                           (0x000000ffU)

#define CTDBGSGL1_RESERVED_SHIFT                                                        (8U)
#define CTDBGSGL1_RESERVED_MASK                                                         (0xffffff00U)

#define CTDBGSGL2_INPSEL_SHIFT                                                          (0U)
#define CTDBGSGL2_INPSEL_MASK                                                           (0x000000ffU)

#define CTDBGSGL2_RESERVED_SHIFT                                                        (8U)
#define CTDBGSGL2_RESERVED_MASK                                                         (0xffffff00U)

#define CTDBGSGL3_INPSEL_SHIFT                                                          (0U)
#define CTDBGSGL3_INPSEL_MASK                                                           (0x000000ffU)

#define CTDBGSGL3_RESERVED_SHIFT                                                        (8U)
#define CTDBGSGL3_RESERVED_MASK                                                         (0xffffff00U)

#define CTDBGSGL4_INPSEL_SHIFT                                                          (0U)
#define CTDBGSGL4_INPSEL_MASK                                                           (0x000000ffU)

#define CTDBGSGL4_RESERVED_SHIFT                                                        (8U)
#define CTDBGSGL4_RESERVED_MASK                                                         (0xffffff00U)

#define CTDBGSGL5_INPSEL_SHIFT                                                          (0U)
#define CTDBGSGL5_INPSEL_MASK                                                           (0x000000ffU)

#define CTDBGSGL5_RESERVED_SHIFT                                                        (8U)
#define CTDBGSGL5_RESERVED_MASK                                                         (0xffffff00U)

#define CTDBGSGL6_INPSEL_SHIFT                                                          (0U)
#define CTDBGSGL6_INPSEL_MASK                                                           (0x000000ffU)

#define CTDBGSGL6_RESERVED_SHIFT                                                        (8U)
#define CTDBGSGL6_RESERVED_MASK                                                         (0xffffff00U)

#define CTDBGSGL7_INPSEL_SHIFT                                                          (0U)
#define CTDBGSGL7_INPSEL_MASK                                                           (0x000000ffU)

#define CTDBGSGL7_RESERVED_SHIFT                                                        (8U)
#define CTDBGSGL7_RESERVED_MASK                                                         (0xffffff00U)

#define CTGNBL0_ENABLE_SHIFT                                                            (0U)
#define CTGNBL0_ENABLE_MASK                                                             (0xffffffffU)

#define CTGNBL1_ENABLE_SHIFT                                                            (0U)
#define CTGNBL1_ENABLE_MASK                                                             (0xffffffffU)

#define CTGRST0_RESET_SHIFT                                                             (0U)
#define CTGRST0_RESET_MASK                                                              (0xffffffffU)

#define CTGRST1_RESET_SHIFT                                                             (0U)
#define CTGRST1_RESET_MASK                                                              (0xffffffffU)

#define CTCR0_ENBL_SHIFT                                                                (0U)
#define CTCR0_ENBL_MASK                                                                 (0x00000001U)

#define CTCR0_RESET_SHIFT                                                               (1U)
#define CTCR0_RESET_MASK                                                                (0x00000002U)

#define CTCR0_CHAIN_SHIFT                                                               (2U)
#define CTCR0_CHAIN_MASK                                                                (0x00000004U)

#define CTCR0_DURMODE_SHIFT                                                             (3U)
#define CTCR0_DURMODE_MASK                                                              (0x00000008U)

#define CTCR0_FREE_SHIFT                                                                (4U)
#define CTCR0_FREE_MASK                                                                 (0x00000010U)

#define CTCR0_IDLE_SHIFT                                                                (5U)
#define CTCR0_IDLE_MASK                                                                 (0x00000020U)

#define CTCR0_OVRFLW_SHIFT                                                              (6U)
#define CTCR0_OVRFLW_MASK                                                               (0x00000040U)

#define CTCR0_CHNSDW_SHIFT                                                              (7U)
#define CTCR0_CHNSDW_MASK                                                               (0x00000080U)

#define CTCR0_INT_SHIFT                                                                 (8U)
#define CTCR0_INT_MASK                                                                  (0x00000100U)

#define CTCR0_DBG_SHIFT                                                                 (9U)
#define CTCR0_DBG_MASK                                                                  (0x00000200U)

#define CTCR0_RESTART_SHIFT                                                             (10U)
#define CTCR0_RESTART_MASK                                                              (0x00000400U)

#define CTCR0_WDMODE_SHIFT                                                              (11U)
#define CTCR0_WDMODE_MASK                                                               (0x00000800U)

#define CTCR0_DBG_TRIG_STAT_SHIFT                                                       (12U)
#define CTCR0_DBG_TRIG_STAT_MASK                                                        (0x00001000U)

#define CTCR0_RESERVED_SHIFT                                                            (13U)
#define CTCR0_RESERVED_MASK                                                             (0x0000e000U)

#define CTCR0_INPSEL_SHIFT                                                              (16U)
#define CTCR0_INPSEL_MASK                                                               (0x00ff0000U)

#define CTCR0_WDRESET_SHIFT                                                             (24U)
#define CTCR0_WDRESET_MASK                                                              (0xff000000U)

#define CTCR1_ENBL_SHIFT                                                                (0U)
#define CTCR1_ENBL_MASK                                                                 (0x00000001U)

#define CTCR1_RESET_SHIFT                                                               (1U)
#define CTCR1_RESET_MASK                                                                (0x00000002U)

#define CTCR1_CHAIN_SHIFT                                                               (2U)
#define CTCR1_CHAIN_MASK                                                                (0x00000004U)

#define CTCR1_DURMODE_SHIFT                                                             (3U)
#define CTCR1_DURMODE_MASK                                                              (0x00000008U)

#define CTCR1_FREE_SHIFT                                                                (4U)
#define CTCR1_FREE_MASK                                                                 (0x00000010U)

#define CTCR1_IDLE_SHIFT                                                                (5U)
#define CTCR1_IDLE_MASK                                                                 (0x00000020U)

#define CTCR1_OVRFLW_SHIFT                                                              (6U)
#define CTCR1_OVRFLW_MASK                                                               (0x00000040U)

#define CTCR1_CHNSDW_SHIFT                                                              (7U)
#define CTCR1_CHNSDW_MASK                                                               (0x00000080U)

#define CTCR1_INT_SHIFT                                                                 (8U)
#define CTCR1_INT_MASK                                                                  (0x00000100U)

#define CTCR1_DBG_SHIFT                                                                 (9U)
#define CTCR1_DBG_MASK                                                                  (0x00000200U)

#define CTCR1_RESTART_SHIFT                                                             (10U)
#define CTCR1_RESTART_MASK                                                              (0x00000400U)

#define CTCR1_WDMODE_SHIFT                                                              (11U)
#define CTCR1_WDMODE_MASK                                                               (0x00000800U)

#define CTCR1_DBG_TRIG_STAT_SHIFT                                                       (12U)
#define CTCR1_DBG_TRIG_STAT_MASK                                                        (0x00001000U)

#define CTCR1_RESERVED_SHIFT                                                            (13U)
#define CTCR1_RESERVED_MASK                                                             (0x0000e000U)

#define CTCR1_INPSEL_SHIFT                                                              (16U)
#define CTCR1_INPSEL_MASK                                                               (0x00ff0000U)

#define CTCR1_WDRESET_SHIFT                                                             (24U)
#define CTCR1_WDRESET_MASK                                                              (0xff000000U)

#define CTCR2_ENBL_SHIFT                                                                (0U)
#define CTCR2_ENBL_MASK                                                                 (0x00000001U)

#define CTCR2_RESET_SHIFT                                                               (1U)
#define CTCR2_RESET_MASK                                                                (0x00000002U)

#define CTCR2_CHAIN_SHIFT                                                               (2U)
#define CTCR2_CHAIN_MASK                                                                (0x00000004U)

#define CTCR2_DURMODE_SHIFT                                                             (3U)
#define CTCR2_DURMODE_MASK                                                              (0x00000008U)

#define CTCR2_FREE_SHIFT                                                                (4U)
#define CTCR2_FREE_MASK                                                                 (0x00000010U)

#define CTCR2_IDLE_SHIFT                                                                (5U)
#define CTCR2_IDLE_MASK                                                                 (0x00000020U)

#define CTCR2_OVRFLW_SHIFT                                                              (6U)
#define CTCR2_OVRFLW_MASK                                                               (0x00000040U)

#define CTCR2_CHNSDW_SHIFT                                                              (7U)
#define CTCR2_CHNSDW_MASK                                                               (0x00000080U)

#define CTCR2_INT_SHIFT                                                                 (8U)
#define CTCR2_INT_MASK                                                                  (0x00000100U)

#define CTCR2_DBG_SHIFT                                                                 (9U)
#define CTCR2_DBG_MASK                                                                  (0x00000200U)

#define CTCR2_RESTART_SHIFT                                                             (10U)
#define CTCR2_RESTART_MASK                                                              (0x00000400U)

#define CTCR2_WDMODE_SHIFT                                                              (11U)
#define CTCR2_WDMODE_MASK                                                               (0x00000800U)

#define CTCR2_DBG_TRIG_STAT_SHIFT                                                       (12U)
#define CTCR2_DBG_TRIG_STAT_MASK                                                        (0x00001000U)

#define CTCR2_RESERVED_SHIFT                                                            (13U)
#define CTCR2_RESERVED_MASK                                                             (0x0000e000U)

#define CTCR2_INPSEL_SHIFT                                                              (16U)
#define CTCR2_INPSEL_MASK                                                               (0x00ff0000U)

#define CTCR2_WDRESET_SHIFT                                                             (24U)
#define CTCR2_WDRESET_MASK                                                              (0xff000000U)

#define CTCR3_ENBL_SHIFT                                                                (0U)
#define CTCR3_ENBL_MASK                                                                 (0x00000001U)

#define CTCR3_RESET_SHIFT                                                               (1U)
#define CTCR3_RESET_MASK                                                                (0x00000002U)

#define CTCR3_CHAIN_SHIFT                                                               (2U)
#define CTCR3_CHAIN_MASK                                                                (0x00000004U)

#define CTCR3_DURMODE_SHIFT                                                             (3U)
#define CTCR3_DURMODE_MASK                                                              (0x00000008U)

#define CTCR3_FREE_SHIFT                                                                (4U)
#define CTCR3_FREE_MASK                                                                 (0x00000010U)

#define CTCR3_IDLE_SHIFT                                                                (5U)
#define CTCR3_IDLE_MASK                                                                 (0x00000020U)

#define CTCR3_OVRFLW_SHIFT                                                              (6U)
#define CTCR3_OVRFLW_MASK                                                               (0x00000040U)

#define CTCR3_CHNSDW_SHIFT                                                              (7U)
#define CTCR3_CHNSDW_MASK                                                               (0x00000080U)

#define CTCR3_INT_SHIFT                                                                 (8U)
#define CTCR3_INT_MASK                                                                  (0x00000100U)

#define CTCR3_DBG_SHIFT                                                                 (9U)
#define CTCR3_DBG_MASK                                                                  (0x00000200U)

#define CTCR3_RESTART_SHIFT                                                             (10U)
#define CTCR3_RESTART_MASK                                                              (0x00000400U)

#define CTCR3_WDMODE_SHIFT                                                              (11U)
#define CTCR3_WDMODE_MASK                                                               (0x00000800U)

#define CTCR3_DBG_TRIG_STAT_SHIFT                                                       (12U)
#define CTCR3_DBG_TRIG_STAT_MASK                                                        (0x00001000U)

#define CTCR3_RESERVED_SHIFT                                                            (13U)
#define CTCR3_RESERVED_MASK                                                             (0x0000e000U)

#define CTCR3_INPSEL_SHIFT                                                              (16U)
#define CTCR3_INPSEL_MASK                                                               (0x00ff0000U)

#define CTCR3_WDRESET_SHIFT                                                             (24U)
#define CTCR3_WDRESET_MASK                                                              (0xff000000U)

#define CTCR4_ENBL_SHIFT                                                                (0U)
#define CTCR4_ENBL_MASK                                                                 (0x00000001U)

#define CTCR4_RESET_SHIFT                                                               (1U)
#define CTCR4_RESET_MASK                                                                (0x00000002U)

#define CTCR4_CHAIN_SHIFT                                                               (2U)
#define CTCR4_CHAIN_MASK                                                                (0x00000004U)

#define CTCR4_DURMODE_SHIFT                                                             (3U)
#define CTCR4_DURMODE_MASK                                                              (0x00000008U)

#define CTCR4_FREE_SHIFT                                                                (4U)
#define CTCR4_FREE_MASK                                                                 (0x00000010U)

#define CTCR4_IDLE_SHIFT                                                                (5U)
#define CTCR4_IDLE_MASK                                                                 (0x00000020U)

#define CTCR4_OVRFLW_SHIFT                                                              (6U)
#define CTCR4_OVRFLW_MASK                                                               (0x00000040U)

#define CTCR4_CHNSDW_SHIFT                                                              (7U)
#define CTCR4_CHNSDW_MASK                                                               (0x00000080U)

#define CTCR4_INT_SHIFT                                                                 (8U)
#define CTCR4_INT_MASK                                                                  (0x00000100U)

#define CTCR4_DBG_SHIFT                                                                 (9U)
#define CTCR4_DBG_MASK                                                                  (0x00000200U)

#define CTCR4_RESTART_SHIFT                                                             (10U)
#define CTCR4_RESTART_MASK                                                              (0x00000400U)

#define CTCR4_WDMODE_SHIFT                                                              (11U)
#define CTCR4_WDMODE_MASK                                                               (0x00000800U)

#define CTCR4_DBG_TRIG_STAT_SHIFT                                                       (12U)
#define CTCR4_DBG_TRIG_STAT_MASK                                                        (0x00001000U)

#define CTCR4_RESERVED_SHIFT                                                            (13U)
#define CTCR4_RESERVED_MASK                                                             (0x0000e000U)

#define CTCR4_INPSEL_SHIFT                                                              (16U)
#define CTCR4_INPSEL_MASK                                                               (0x00ff0000U)

#define CTCR4_WDRESET_SHIFT                                                             (24U)
#define CTCR4_WDRESET_MASK                                                              (0xff000000U)

#define CTCR5_ENBL_SHIFT                                                                (0U)
#define CTCR5_ENBL_MASK                                                                 (0x00000001U)

#define CTCR5_RESET_SHIFT                                                               (1U)
#define CTCR5_RESET_MASK                                                                (0x00000002U)

#define CTCR5_CHAIN_SHIFT                                                               (2U)
#define CTCR5_CHAIN_MASK                                                                (0x00000004U)

#define CTCR5_DURMODE_SHIFT                                                             (3U)
#define CTCR5_DURMODE_MASK                                                              (0x00000008U)

#define CTCR5_FREE_SHIFT                                                                (4U)
#define CTCR5_FREE_MASK                                                                 (0x00000010U)

#define CTCR5_IDLE_SHIFT                                                                (5U)
#define CTCR5_IDLE_MASK                                                                 (0x00000020U)

#define CTCR5_OVRFLW_SHIFT                                                              (6U)
#define CTCR5_OVRFLW_MASK                                                               (0x00000040U)

#define CTCR5_CHNSDW_SHIFT                                                              (7U)
#define CTCR5_CHNSDW_MASK                                                               (0x00000080U)

#define CTCR5_INT_SHIFT                                                                 (8U)
#define CTCR5_INT_MASK                                                                  (0x00000100U)

#define CTCR5_DBG_SHIFT                                                                 (9U)
#define CTCR5_DBG_MASK                                                                  (0x00000200U)

#define CTCR5_RESTART_SHIFT                                                             (10U)
#define CTCR5_RESTART_MASK                                                              (0x00000400U)

#define CTCR5_WDMODE_SHIFT                                                              (11U)
#define CTCR5_WDMODE_MASK                                                               (0x00000800U)

#define CTCR5_DBG_TRIG_STAT_SHIFT                                                       (12U)
#define CTCR5_DBG_TRIG_STAT_MASK                                                        (0x00001000U)

#define CTCR5_RESERVED_SHIFT                                                            (13U)
#define CTCR5_RESERVED_MASK                                                             (0x0000e000U)

#define CTCR5_INPSEL_SHIFT                                                              (16U)
#define CTCR5_INPSEL_MASK                                                               (0x00ff0000U)

#define CTCR5_WDRESET_SHIFT                                                             (24U)
#define CTCR5_WDRESET_MASK                                                              (0xff000000U)

#define CTCR6_ENBL_SHIFT                                                                (0U)
#define CTCR6_ENBL_MASK                                                                 (0x00000001U)

#define CTCR6_RESET_SHIFT                                                               (1U)
#define CTCR6_RESET_MASK                                                                (0x00000002U)

#define CTCR6_CHAIN_SHIFT                                                               (2U)
#define CTCR6_CHAIN_MASK                                                                (0x00000004U)

#define CTCR6_DURMODE_SHIFT                                                             (3U)
#define CTCR6_DURMODE_MASK                                                              (0x00000008U)

#define CTCR6_FREE_SHIFT                                                                (4U)
#define CTCR6_FREE_MASK                                                                 (0x00000010U)

#define CTCR6_IDLE_SHIFT                                                                (5U)
#define CTCR6_IDLE_MASK                                                                 (0x00000020U)

#define CTCR6_OVRFLW_SHIFT                                                              (6U)
#define CTCR6_OVRFLW_MASK                                                               (0x00000040U)

#define CTCR6_CHNSDW_SHIFT                                                              (7U)
#define CTCR6_CHNSDW_MASK                                                               (0x00000080U)

#define CTCR6_INT_SHIFT                                                                 (8U)
#define CTCR6_INT_MASK                                                                  (0x00000100U)

#define CTCR6_DBG_SHIFT                                                                 (9U)
#define CTCR6_DBG_MASK                                                                  (0x00000200U)

#define CTCR6_RESTART_SHIFT                                                             (10U)
#define CTCR6_RESTART_MASK                                                              (0x00000400U)

#define CTCR6_WDMODE_SHIFT                                                              (11U)
#define CTCR6_WDMODE_MASK                                                               (0x00000800U)

#define CTCR6_DBG_TRIG_STAT_SHIFT                                                       (12U)
#define CTCR6_DBG_TRIG_STAT_MASK                                                        (0x00001000U)

#define CTCR6_RESERVED_SHIFT                                                            (13U)
#define CTCR6_RESERVED_MASK                                                             (0x0000e000U)

#define CTCR6_INPSEL_SHIFT                                                              (16U)
#define CTCR6_INPSEL_MASK                                                               (0x00ff0000U)

#define CTCR6_WDRESET_SHIFT                                                             (24U)
#define CTCR6_WDRESET_MASK                                                              (0xff000000U)

#define CTCR7_ENBL_SHIFT                                                                (0U)
#define CTCR7_ENBL_MASK                                                                 (0x00000001U)

#define CTCR7_RESET_SHIFT                                                               (1U)
#define CTCR7_RESET_MASK                                                                (0x00000002U)

#define CTCR7_CHAIN_SHIFT                                                               (2U)
#define CTCR7_CHAIN_MASK                                                                (0x00000004U)

#define CTCR7_DURMODE_SHIFT                                                             (3U)
#define CTCR7_DURMODE_MASK                                                              (0x00000008U)

#define CTCR7_FREE_SHIFT                                                                (4U)
#define CTCR7_FREE_MASK                                                                 (0x00000010U)

#define CTCR7_IDLE_SHIFT                                                                (5U)
#define CTCR7_IDLE_MASK                                                                 (0x00000020U)

#define CTCR7_OVRFLW_SHIFT                                                              (6U)
#define CTCR7_OVRFLW_MASK                                                               (0x00000040U)

#define CTCR7_CHNSDW_SHIFT                                                              (7U)
#define CTCR7_CHNSDW_MASK                                                               (0x00000080U)

#define CTCR7_INT_SHIFT                                                                 (8U)
#define CTCR7_INT_MASK                                                                  (0x00000100U)

#define CTCR7_DBG_SHIFT                                                                 (9U)
#define CTCR7_DBG_MASK                                                                  (0x00000200U)

#define CTCR7_RESTART_SHIFT                                                             (10U)
#define CTCR7_RESTART_MASK                                                              (0x00000400U)

#define CTCR7_WDMODE_SHIFT                                                              (11U)
#define CTCR7_WDMODE_MASK                                                               (0x00000800U)

#define CTCR7_DBG_TRIG_STAT_SHIFT                                                       (12U)
#define CTCR7_DBG_TRIG_STAT_MASK                                                        (0x00001000U)

#define CTCR7_RESERVED_SHIFT                                                            (13U)
#define CTCR7_RESERVED_MASK                                                             (0x0000e000U)

#define CTCR7_INPSEL_SHIFT                                                              (16U)
#define CTCR7_INPSEL_MASK                                                               (0x00ff0000U)

#define CTCR7_WDRESET_SHIFT                                                             (24U)
#define CTCR7_WDRESET_MASK                                                              (0xff000000U)

#define CTCR8_ENBL_SHIFT                                                                (0U)
#define CTCR8_ENBL_MASK                                                                 (0x00000001U)

#define CTCR8_RESET_SHIFT                                                               (1U)
#define CTCR8_RESET_MASK                                                                (0x00000002U)

#define CTCR8_CHAIN_SHIFT                                                               (2U)
#define CTCR8_CHAIN_MASK                                                                (0x00000004U)

#define CTCR8_DURMODE_SHIFT                                                             (3U)
#define CTCR8_DURMODE_MASK                                                              (0x00000008U)

#define CTCR8_FREE_SHIFT                                                                (4U)
#define CTCR8_FREE_MASK                                                                 (0x00000010U)

#define CTCR8_IDLE_SHIFT                                                                (5U)
#define CTCR8_IDLE_MASK                                                                 (0x00000020U)

#define CTCR8_OVRFLW_SHIFT                                                              (6U)
#define CTCR8_OVRFLW_MASK                                                               (0x00000040U)

#define CTCR8_CHNSDW_SHIFT                                                              (7U)
#define CTCR8_CHNSDW_MASK                                                               (0x00000080U)

#define CTCR8_INT_SHIFT                                                                 (8U)
#define CTCR8_INT_MASK                                                                  (0x00000100U)

#define CTCR8_DBG_SHIFT                                                                 (9U)
#define CTCR8_DBG_MASK                                                                  (0x00000200U)

#define CTCR8_RESTART_SHIFT                                                             (10U)
#define CTCR8_RESTART_MASK                                                              (0x00000400U)

#define CTCR8_WDMODE_SHIFT                                                              (11U)
#define CTCR8_WDMODE_MASK                                                               (0x00000800U)

#define CTCR8_DBG_TRIG_STAT_SHIFT                                                       (12U)
#define CTCR8_DBG_TRIG_STAT_MASK                                                        (0x00001000U)

#define CTCR8_RESERVED_SHIFT                                                            (13U)
#define CTCR8_RESERVED_MASK                                                             (0x0000e000U)

#define CTCR8_INPSEL_SHIFT                                                              (16U)
#define CTCR8_INPSEL_MASK                                                               (0x00ff0000U)

#define CTCR8_WDRESET_SHIFT                                                             (24U)
#define CTCR8_WDRESET_MASK                                                              (0xff000000U)

#define CTCR9_ENBL_SHIFT                                                                (0U)
#define CTCR9_ENBL_MASK                                                                 (0x00000001U)

#define CTCR9_RESET_SHIFT                                                               (1U)
#define CTCR9_RESET_MASK                                                                (0x00000002U)

#define CTCR9_CHAIN_SHIFT                                                               (2U)
#define CTCR9_CHAIN_MASK                                                                (0x00000004U)

#define CTCR9_DURMODE_SHIFT                                                             (3U)
#define CTCR9_DURMODE_MASK                                                              (0x00000008U)

#define CTCR9_FREE_SHIFT                                                                (4U)
#define CTCR9_FREE_MASK                                                                 (0x00000010U)

#define CTCR9_IDLE_SHIFT                                                                (5U)
#define CTCR9_IDLE_MASK                                                                 (0x00000020U)

#define CTCR9_OVRFLW_SHIFT                                                              (6U)
#define CTCR9_OVRFLW_MASK                                                               (0x00000040U)

#define CTCR9_CHNSDW_SHIFT                                                              (7U)
#define CTCR9_CHNSDW_MASK                                                               (0x00000080U)

#define CTCR9_INT_SHIFT                                                                 (8U)
#define CTCR9_INT_MASK                                                                  (0x00000100U)

#define CTCR9_DBG_SHIFT                                                                 (9U)
#define CTCR9_DBG_MASK                                                                  (0x00000200U)

#define CTCR9_RESTART_SHIFT                                                             (10U)
#define CTCR9_RESTART_MASK                                                              (0x00000400U)

#define CTCR9_WDMODE_SHIFT                                                              (11U)
#define CTCR9_WDMODE_MASK                                                               (0x00000800U)

#define CTCR9_DBG_TRIG_STAT_SHIFT                                                       (12U)
#define CTCR9_DBG_TRIG_STAT_MASK                                                        (0x00001000U)

#define CTCR9_RESERVED_SHIFT                                                            (13U)
#define CTCR9_RESERVED_MASK                                                             (0x0000e000U)

#define CTCR9_INPSEL_SHIFT                                                              (16U)
#define CTCR9_INPSEL_MASK                                                               (0x00ff0000U)

#define CTCR9_WDRESET_SHIFT                                                             (24U)
#define CTCR9_WDRESET_MASK                                                              (0xff000000U)

#define CTCR10_ENBL_SHIFT                                                               (0U)
#define CTCR10_ENBL_MASK                                                                (0x00000001U)

#define CTCR10_RESET_SHIFT                                                              (1U)
#define CTCR10_RESET_MASK                                                               (0x00000002U)

#define CTCR10_CHAIN_SHIFT                                                              (2U)
#define CTCR10_CHAIN_MASK                                                               (0x00000004U)

#define CTCR10_DURMODE_SHIFT                                                            (3U)
#define CTCR10_DURMODE_MASK                                                             (0x00000008U)

#define CTCR10_FREE_SHIFT                                                               (4U)
#define CTCR10_FREE_MASK                                                                (0x00000010U)

#define CTCR10_IDLE_SHIFT                                                               (5U)
#define CTCR10_IDLE_MASK                                                                (0x00000020U)

#define CTCR10_OVRFLW_SHIFT                                                             (6U)
#define CTCR10_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR10_CHNSDW_SHIFT                                                             (7U)
#define CTCR10_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR10_INT_SHIFT                                                                (8U)
#define CTCR10_INT_MASK                                                                 (0x00000100U)

#define CTCR10_DBG_SHIFT                                                                (9U)
#define CTCR10_DBG_MASK                                                                 (0x00000200U)

#define CTCR10_RESTART_SHIFT                                                            (10U)
#define CTCR10_RESTART_MASK                                                             (0x00000400U)

#define CTCR10_WDMODE_SHIFT                                                             (11U)
#define CTCR10_WDMODE_MASK                                                              (0x00000800U)

#define CTCR10_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR10_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR10_RESERVED_SHIFT                                                           (13U)
#define CTCR10_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR10_INPSEL_SHIFT                                                             (16U)
#define CTCR10_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR10_WDRESET_SHIFT                                                            (24U)
#define CTCR10_WDRESET_MASK                                                             (0xff000000U)

#define CTCR11_ENBL_SHIFT                                                               (0U)
#define CTCR11_ENBL_MASK                                                                (0x00000001U)

#define CTCR11_RESET_SHIFT                                                              (1U)
#define CTCR11_RESET_MASK                                                               (0x00000002U)

#define CTCR11_CHAIN_SHIFT                                                              (2U)
#define CTCR11_CHAIN_MASK                                                               (0x00000004U)

#define CTCR11_DURMODE_SHIFT                                                            (3U)
#define CTCR11_DURMODE_MASK                                                             (0x00000008U)

#define CTCR11_FREE_SHIFT                                                               (4U)
#define CTCR11_FREE_MASK                                                                (0x00000010U)

#define CTCR11_IDLE_SHIFT                                                               (5U)
#define CTCR11_IDLE_MASK                                                                (0x00000020U)

#define CTCR11_OVRFLW_SHIFT                                                             (6U)
#define CTCR11_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR11_CHNSDW_SHIFT                                                             (7U)
#define CTCR11_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR11_INT_SHIFT                                                                (8U)
#define CTCR11_INT_MASK                                                                 (0x00000100U)

#define CTCR11_DBG_SHIFT                                                                (9U)
#define CTCR11_DBG_MASK                                                                 (0x00000200U)

#define CTCR11_RESTART_SHIFT                                                            (10U)
#define CTCR11_RESTART_MASK                                                             (0x00000400U)

#define CTCR11_WDMODE_SHIFT                                                             (11U)
#define CTCR11_WDMODE_MASK                                                              (0x00000800U)

#define CTCR11_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR11_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR11_RESERVED_SHIFT                                                           (13U)
#define CTCR11_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR11_INPSEL_SHIFT                                                             (16U)
#define CTCR11_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR11_WDRESET_SHIFT                                                            (24U)
#define CTCR11_WDRESET_MASK                                                             (0xff000000U)

#define CTCR12_ENBL_SHIFT                                                               (0U)
#define CTCR12_ENBL_MASK                                                                (0x00000001U)

#define CTCR12_RESET_SHIFT                                                              (1U)
#define CTCR12_RESET_MASK                                                               (0x00000002U)

#define CTCR12_CHAIN_SHIFT                                                              (2U)
#define CTCR12_CHAIN_MASK                                                               (0x00000004U)

#define CTCR12_DURMODE_SHIFT                                                            (3U)
#define CTCR12_DURMODE_MASK                                                             (0x00000008U)

#define CTCR12_FREE_SHIFT                                                               (4U)
#define CTCR12_FREE_MASK                                                                (0x00000010U)

#define CTCR12_IDLE_SHIFT                                                               (5U)
#define CTCR12_IDLE_MASK                                                                (0x00000020U)

#define CTCR12_OVRFLW_SHIFT                                                             (6U)
#define CTCR12_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR12_CHNSDW_SHIFT                                                             (7U)
#define CTCR12_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR12_INT_SHIFT                                                                (8U)
#define CTCR12_INT_MASK                                                                 (0x00000100U)

#define CTCR12_DBG_SHIFT                                                                (9U)
#define CTCR12_DBG_MASK                                                                 (0x00000200U)

#define CTCR12_RESTART_SHIFT                                                            (10U)
#define CTCR12_RESTART_MASK                                                             (0x00000400U)

#define CTCR12_WDMODE_SHIFT                                                             (11U)
#define CTCR12_WDMODE_MASK                                                              (0x00000800U)

#define CTCR12_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR12_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR12_RESERVED_SHIFT                                                           (13U)
#define CTCR12_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR12_INPSEL_SHIFT                                                             (16U)
#define CTCR12_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR12_WDRESET_SHIFT                                                            (24U)
#define CTCR12_WDRESET_MASK                                                             (0xff000000U)

#define CTCR13_ENBL_SHIFT                                                               (0U)
#define CTCR13_ENBL_MASK                                                                (0x00000001U)

#define CTCR13_RESET_SHIFT                                                              (1U)
#define CTCR13_RESET_MASK                                                               (0x00000002U)

#define CTCR13_CHAIN_SHIFT                                                              (2U)
#define CTCR13_CHAIN_MASK                                                               (0x00000004U)

#define CTCR13_DURMODE_SHIFT                                                            (3U)
#define CTCR13_DURMODE_MASK                                                             (0x00000008U)

#define CTCR13_FREE_SHIFT                                                               (4U)
#define CTCR13_FREE_MASK                                                                (0x00000010U)

#define CTCR13_IDLE_SHIFT                                                               (5U)
#define CTCR13_IDLE_MASK                                                                (0x00000020U)

#define CTCR13_OVRFLW_SHIFT                                                             (6U)
#define CTCR13_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR13_CHNSDW_SHIFT                                                             (7U)
#define CTCR13_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR13_INT_SHIFT                                                                (8U)
#define CTCR13_INT_MASK                                                                 (0x00000100U)

#define CTCR13_DBG_SHIFT                                                                (9U)
#define CTCR13_DBG_MASK                                                                 (0x00000200U)

#define CTCR13_RESTART_SHIFT                                                            (10U)
#define CTCR13_RESTART_MASK                                                             (0x00000400U)

#define CTCR13_WDMODE_SHIFT                                                             (11U)
#define CTCR13_WDMODE_MASK                                                              (0x00000800U)

#define CTCR13_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR13_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR13_RESERVED_SHIFT                                                           (13U)
#define CTCR13_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR13_INPSEL_SHIFT                                                             (16U)
#define CTCR13_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR13_WDRESET_SHIFT                                                            (24U)
#define CTCR13_WDRESET_MASK                                                             (0xff000000U)

#define CTCR14_ENBL_SHIFT                                                               (0U)
#define CTCR14_ENBL_MASK                                                                (0x00000001U)

#define CTCR14_RESET_SHIFT                                                              (1U)
#define CTCR14_RESET_MASK                                                               (0x00000002U)

#define CTCR14_CHAIN_SHIFT                                                              (2U)
#define CTCR14_CHAIN_MASK                                                               (0x00000004U)

#define CTCR14_DURMODE_SHIFT                                                            (3U)
#define CTCR14_DURMODE_MASK                                                             (0x00000008U)

#define CTCR14_FREE_SHIFT                                                               (4U)
#define CTCR14_FREE_MASK                                                                (0x00000010U)

#define CTCR14_IDLE_SHIFT                                                               (5U)
#define CTCR14_IDLE_MASK                                                                (0x00000020U)

#define CTCR14_OVRFLW_SHIFT                                                             (6U)
#define CTCR14_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR14_CHNSDW_SHIFT                                                             (7U)
#define CTCR14_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR14_INT_SHIFT                                                                (8U)
#define CTCR14_INT_MASK                                                                 (0x00000100U)

#define CTCR14_DBG_SHIFT                                                                (9U)
#define CTCR14_DBG_MASK                                                                 (0x00000200U)

#define CTCR14_RESTART_SHIFT                                                            (10U)
#define CTCR14_RESTART_MASK                                                             (0x00000400U)

#define CTCR14_WDMODE_SHIFT                                                             (11U)
#define CTCR14_WDMODE_MASK                                                              (0x00000800U)

#define CTCR14_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR14_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR14_RESERVED_SHIFT                                                           (13U)
#define CTCR14_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR14_INPSEL_SHIFT                                                             (16U)
#define CTCR14_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR14_WDRESET_SHIFT                                                            (24U)
#define CTCR14_WDRESET_MASK                                                             (0xff000000U)

#define CTCR15_ENBL_SHIFT                                                               (0U)
#define CTCR15_ENBL_MASK                                                                (0x00000001U)

#define CTCR15_RESET_SHIFT                                                              (1U)
#define CTCR15_RESET_MASK                                                               (0x00000002U)

#define CTCR15_CHAIN_SHIFT                                                              (2U)
#define CTCR15_CHAIN_MASK                                                               (0x00000004U)

#define CTCR15_DURMODE_SHIFT                                                            (3U)
#define CTCR15_DURMODE_MASK                                                             (0x00000008U)

#define CTCR15_FREE_SHIFT                                                               (4U)
#define CTCR15_FREE_MASK                                                                (0x00000010U)

#define CTCR15_IDLE_SHIFT                                                               (5U)
#define CTCR15_IDLE_MASK                                                                (0x00000020U)

#define CTCR15_OVRFLW_SHIFT                                                             (6U)
#define CTCR15_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR15_CHNSDW_SHIFT                                                             (7U)
#define CTCR15_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR15_INT_SHIFT                                                                (8U)
#define CTCR15_INT_MASK                                                                 (0x00000100U)

#define CTCR15_DBG_SHIFT                                                                (9U)
#define CTCR15_DBG_MASK                                                                 (0x00000200U)

#define CTCR15_RESTART_SHIFT                                                            (10U)
#define CTCR15_RESTART_MASK                                                             (0x00000400U)

#define CTCR15_WDMODE_SHIFT                                                             (11U)
#define CTCR15_WDMODE_MASK                                                              (0x00000800U)

#define CTCR15_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR15_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR15_RESERVED_SHIFT                                                           (13U)
#define CTCR15_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR15_INPSEL_SHIFT                                                             (16U)
#define CTCR15_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR15_WDRESET_SHIFT                                                            (24U)
#define CTCR15_WDRESET_MASK                                                             (0xff000000U)

#define CTCR16_ENBL_SHIFT                                                               (0U)
#define CTCR16_ENBL_MASK                                                                (0x00000001U)

#define CTCR16_RESET_SHIFT                                                              (1U)
#define CTCR16_RESET_MASK                                                               (0x00000002U)

#define CTCR16_CHAIN_SHIFT                                                              (2U)
#define CTCR16_CHAIN_MASK                                                               (0x00000004U)

#define CTCR16_DURMODE_SHIFT                                                            (3U)
#define CTCR16_DURMODE_MASK                                                             (0x00000008U)

#define CTCR16_FREE_SHIFT                                                               (4U)
#define CTCR16_FREE_MASK                                                                (0x00000010U)

#define CTCR16_IDLE_SHIFT                                                               (5U)
#define CTCR16_IDLE_MASK                                                                (0x00000020U)

#define CTCR16_OVRFLW_SHIFT                                                             (6U)
#define CTCR16_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR16_CHNSDW_SHIFT                                                             (7U)
#define CTCR16_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR16_INT_SHIFT                                                                (8U)
#define CTCR16_INT_MASK                                                                 (0x00000100U)

#define CTCR16_DBG_SHIFT                                                                (9U)
#define CTCR16_DBG_MASK                                                                 (0x00000200U)

#define CTCR16_RESTART_SHIFT                                                            (10U)
#define CTCR16_RESTART_MASK                                                             (0x00000400U)

#define CTCR16_WDMODE_SHIFT                                                             (11U)
#define CTCR16_WDMODE_MASK                                                              (0x00000800U)

#define CTCR16_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR16_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR16_RESERVED_SHIFT                                                           (13U)
#define CTCR16_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR16_INPSEL_SHIFT                                                             (16U)
#define CTCR16_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR16_WDRESET_SHIFT                                                            (24U)
#define CTCR16_WDRESET_MASK                                                             (0xff000000U)

#define CTCR17_ENBL_SHIFT                                                               (0U)
#define CTCR17_ENBL_MASK                                                                (0x00000001U)

#define CTCR17_RESET_SHIFT                                                              (1U)
#define CTCR17_RESET_MASK                                                               (0x00000002U)

#define CTCR17_CHAIN_SHIFT                                                              (2U)
#define CTCR17_CHAIN_MASK                                                               (0x00000004U)

#define CTCR17_DURMODE_SHIFT                                                            (3U)
#define CTCR17_DURMODE_MASK                                                             (0x00000008U)

#define CTCR17_FREE_SHIFT                                                               (4U)
#define CTCR17_FREE_MASK                                                                (0x00000010U)

#define CTCR17_IDLE_SHIFT                                                               (5U)
#define CTCR17_IDLE_MASK                                                                (0x00000020U)

#define CTCR17_OVRFLW_SHIFT                                                             (6U)
#define CTCR17_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR17_CHNSDW_SHIFT                                                             (7U)
#define CTCR17_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR17_INT_SHIFT                                                                (8U)
#define CTCR17_INT_MASK                                                                 (0x00000100U)

#define CTCR17_DBG_SHIFT                                                                (9U)
#define CTCR17_DBG_MASK                                                                 (0x00000200U)

#define CTCR17_RESTART_SHIFT                                                            (10U)
#define CTCR17_RESTART_MASK                                                             (0x00000400U)

#define CTCR17_WDMODE_SHIFT                                                             (11U)
#define CTCR17_WDMODE_MASK                                                              (0x00000800U)

#define CTCR17_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR17_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR17_RESERVED_SHIFT                                                           (13U)
#define CTCR17_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR17_INPSEL_SHIFT                                                             (16U)
#define CTCR17_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR17_WDRESET_SHIFT                                                            (24U)
#define CTCR17_WDRESET_MASK                                                             (0xff000000U)

#define CTCR18_ENBL_SHIFT                                                               (0U)
#define CTCR18_ENBL_MASK                                                                (0x00000001U)

#define CTCR18_RESET_SHIFT                                                              (1U)
#define CTCR18_RESET_MASK                                                               (0x00000002U)

#define CTCR18_CHAIN_SHIFT                                                              (2U)
#define CTCR18_CHAIN_MASK                                                               (0x00000004U)

#define CTCR18_DURMODE_SHIFT                                                            (3U)
#define CTCR18_DURMODE_MASK                                                             (0x00000008U)

#define CTCR18_FREE_SHIFT                                                               (4U)
#define CTCR18_FREE_MASK                                                                (0x00000010U)

#define CTCR18_IDLE_SHIFT                                                               (5U)
#define CTCR18_IDLE_MASK                                                                (0x00000020U)

#define CTCR18_OVRFLW_SHIFT                                                             (6U)
#define CTCR18_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR18_CHNSDW_SHIFT                                                             (7U)
#define CTCR18_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR18_INT_SHIFT                                                                (8U)
#define CTCR18_INT_MASK                                                                 (0x00000100U)

#define CTCR18_DBG_SHIFT                                                                (9U)
#define CTCR18_DBG_MASK                                                                 (0x00000200U)

#define CTCR18_RESTART_SHIFT                                                            (10U)
#define CTCR18_RESTART_MASK                                                             (0x00000400U)

#define CTCR18_WDMODE_SHIFT                                                             (11U)
#define CTCR18_WDMODE_MASK                                                              (0x00000800U)

#define CTCR18_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR18_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR18_RESERVED_SHIFT                                                           (13U)
#define CTCR18_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR18_INPSEL_SHIFT                                                             (16U)
#define CTCR18_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR18_WDRESET_SHIFT                                                            (24U)
#define CTCR18_WDRESET_MASK                                                             (0xff000000U)

#define CTCR19_ENBL_SHIFT                                                               (0U)
#define CTCR19_ENBL_MASK                                                                (0x00000001U)

#define CTCR19_RESET_SHIFT                                                              (1U)
#define CTCR19_RESET_MASK                                                               (0x00000002U)

#define CTCR19_CHAIN_SHIFT                                                              (2U)
#define CTCR19_CHAIN_MASK                                                               (0x00000004U)

#define CTCR19_DURMODE_SHIFT                                                            (3U)
#define CTCR19_DURMODE_MASK                                                             (0x00000008U)

#define CTCR19_FREE_SHIFT                                                               (4U)
#define CTCR19_FREE_MASK                                                                (0x00000010U)

#define CTCR19_IDLE_SHIFT                                                               (5U)
#define CTCR19_IDLE_MASK                                                                (0x00000020U)

#define CTCR19_OVRFLW_SHIFT                                                             (6U)
#define CTCR19_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR19_CHNSDW_SHIFT                                                             (7U)
#define CTCR19_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR19_INT_SHIFT                                                                (8U)
#define CTCR19_INT_MASK                                                                 (0x00000100U)

#define CTCR19_DBG_SHIFT                                                                (9U)
#define CTCR19_DBG_MASK                                                                 (0x00000200U)

#define CTCR19_RESTART_SHIFT                                                            (10U)
#define CTCR19_RESTART_MASK                                                             (0x00000400U)

#define CTCR19_WDMODE_SHIFT                                                             (11U)
#define CTCR19_WDMODE_MASK                                                              (0x00000800U)

#define CTCR19_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR19_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR19_RESERVED_SHIFT                                                           (13U)
#define CTCR19_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR19_INPSEL_SHIFT                                                             (16U)
#define CTCR19_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR19_WDRESET_SHIFT                                                            (24U)
#define CTCR19_WDRESET_MASK                                                             (0xff000000U)

#define CTCR20_ENBL_SHIFT                                                               (0U)
#define CTCR20_ENBL_MASK                                                                (0x00000001U)

#define CTCR20_RESET_SHIFT                                                              (1U)
#define CTCR20_RESET_MASK                                                               (0x00000002U)

#define CTCR20_CHAIN_SHIFT                                                              (2U)
#define CTCR20_CHAIN_MASK                                                               (0x00000004U)

#define CTCR20_DURMODE_SHIFT                                                            (3U)
#define CTCR20_DURMODE_MASK                                                             (0x00000008U)

#define CTCR20_FREE_SHIFT                                                               (4U)
#define CTCR20_FREE_MASK                                                                (0x00000010U)

#define CTCR20_IDLE_SHIFT                                                               (5U)
#define CTCR20_IDLE_MASK                                                                (0x00000020U)

#define CTCR20_OVRFLW_SHIFT                                                             (6U)
#define CTCR20_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR20_CHNSDW_SHIFT                                                             (7U)
#define CTCR20_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR20_INT_SHIFT                                                                (8U)
#define CTCR20_INT_MASK                                                                 (0x00000100U)

#define CTCR20_DBG_SHIFT                                                                (9U)
#define CTCR20_DBG_MASK                                                                 (0x00000200U)

#define CTCR20_RESTART_SHIFT                                                            (10U)
#define CTCR20_RESTART_MASK                                                             (0x00000400U)

#define CTCR20_WDMODE_SHIFT                                                             (11U)
#define CTCR20_WDMODE_MASK                                                              (0x00000800U)

#define CTCR20_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR20_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR20_RESERVED_SHIFT                                                           (13U)
#define CTCR20_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR20_INPSEL_SHIFT                                                             (16U)
#define CTCR20_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR20_WDRESET_SHIFT                                                            (24U)
#define CTCR20_WDRESET_MASK                                                             (0xff000000U)

#define CTCR21_ENBL_SHIFT                                                               (0U)
#define CTCR21_ENBL_MASK                                                                (0x00000001U)

#define CTCR21_RESET_SHIFT                                                              (1U)
#define CTCR21_RESET_MASK                                                               (0x00000002U)

#define CTCR21_CHAIN_SHIFT                                                              (2U)
#define CTCR21_CHAIN_MASK                                                               (0x00000004U)

#define CTCR21_DURMODE_SHIFT                                                            (3U)
#define CTCR21_DURMODE_MASK                                                             (0x00000008U)

#define CTCR21_FREE_SHIFT                                                               (4U)
#define CTCR21_FREE_MASK                                                                (0x00000010U)

#define CTCR21_IDLE_SHIFT                                                               (5U)
#define CTCR21_IDLE_MASK                                                                (0x00000020U)

#define CTCR21_OVRFLW_SHIFT                                                             (6U)
#define CTCR21_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR21_CHNSDW_SHIFT                                                             (7U)
#define CTCR21_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR21_INT_SHIFT                                                                (8U)
#define CTCR21_INT_MASK                                                                 (0x00000100U)

#define CTCR21_DBG_SHIFT                                                                (9U)
#define CTCR21_DBG_MASK                                                                 (0x00000200U)

#define CTCR21_RESTART_SHIFT                                                            (10U)
#define CTCR21_RESTART_MASK                                                             (0x00000400U)

#define CTCR21_WDMODE_SHIFT                                                             (11U)
#define CTCR21_WDMODE_MASK                                                              (0x00000800U)

#define CTCR21_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR21_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR21_RESERVED_SHIFT                                                           (13U)
#define CTCR21_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR21_INPSEL_SHIFT                                                             (16U)
#define CTCR21_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR21_WDRESET_SHIFT                                                            (24U)
#define CTCR21_WDRESET_MASK                                                             (0xff000000U)

#define CTCR22_ENBL_SHIFT                                                               (0U)
#define CTCR22_ENBL_MASK                                                                (0x00000001U)

#define CTCR22_RESET_SHIFT                                                              (1U)
#define CTCR22_RESET_MASK                                                               (0x00000002U)

#define CTCR22_CHAIN_SHIFT                                                              (2U)
#define CTCR22_CHAIN_MASK                                                               (0x00000004U)

#define CTCR22_DURMODE_SHIFT                                                            (3U)
#define CTCR22_DURMODE_MASK                                                             (0x00000008U)

#define CTCR22_FREE_SHIFT                                                               (4U)
#define CTCR22_FREE_MASK                                                                (0x00000010U)

#define CTCR22_IDLE_SHIFT                                                               (5U)
#define CTCR22_IDLE_MASK                                                                (0x00000020U)

#define CTCR22_OVRFLW_SHIFT                                                             (6U)
#define CTCR22_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR22_CHNSDW_SHIFT                                                             (7U)
#define CTCR22_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR22_INT_SHIFT                                                                (8U)
#define CTCR22_INT_MASK                                                                 (0x00000100U)

#define CTCR22_DBG_SHIFT                                                                (9U)
#define CTCR22_DBG_MASK                                                                 (0x00000200U)

#define CTCR22_RESTART_SHIFT                                                            (10U)
#define CTCR22_RESTART_MASK                                                             (0x00000400U)

#define CTCR22_WDMODE_SHIFT                                                             (11U)
#define CTCR22_WDMODE_MASK                                                              (0x00000800U)

#define CTCR22_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR22_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR22_RESERVED_SHIFT                                                           (13U)
#define CTCR22_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR22_INPSEL_SHIFT                                                             (16U)
#define CTCR22_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR22_WDRESET_SHIFT                                                            (24U)
#define CTCR22_WDRESET_MASK                                                             (0xff000000U)

#define CTCR23_ENBL_SHIFT                                                               (0U)
#define CTCR23_ENBL_MASK                                                                (0x00000001U)

#define CTCR23_RESET_SHIFT                                                              (1U)
#define CTCR23_RESET_MASK                                                               (0x00000002U)

#define CTCR23_CHAIN_SHIFT                                                              (2U)
#define CTCR23_CHAIN_MASK                                                               (0x00000004U)

#define CTCR23_DURMODE_SHIFT                                                            (3U)
#define CTCR23_DURMODE_MASK                                                             (0x00000008U)

#define CTCR23_FREE_SHIFT                                                               (4U)
#define CTCR23_FREE_MASK                                                                (0x00000010U)

#define CTCR23_IDLE_SHIFT                                                               (5U)
#define CTCR23_IDLE_MASK                                                                (0x00000020U)

#define CTCR23_OVRFLW_SHIFT                                                             (6U)
#define CTCR23_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR23_CHNSDW_SHIFT                                                             (7U)
#define CTCR23_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR23_INT_SHIFT                                                                (8U)
#define CTCR23_INT_MASK                                                                 (0x00000100U)

#define CTCR23_DBG_SHIFT                                                                (9U)
#define CTCR23_DBG_MASK                                                                 (0x00000200U)

#define CTCR23_RESTART_SHIFT                                                            (10U)
#define CTCR23_RESTART_MASK                                                             (0x00000400U)

#define CTCR23_WDMODE_SHIFT                                                             (11U)
#define CTCR23_WDMODE_MASK                                                              (0x00000800U)

#define CTCR23_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR23_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR23_RESERVED_SHIFT                                                           (13U)
#define CTCR23_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR23_INPSEL_SHIFT                                                             (16U)
#define CTCR23_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR23_WDRESET_SHIFT                                                            (24U)
#define CTCR23_WDRESET_MASK                                                             (0xff000000U)

#define CTCR24_ENBL_SHIFT                                                               (0U)
#define CTCR24_ENBL_MASK                                                                (0x00000001U)

#define CTCR24_RESET_SHIFT                                                              (1U)
#define CTCR24_RESET_MASK                                                               (0x00000002U)

#define CTCR24_CHAIN_SHIFT                                                              (2U)
#define CTCR24_CHAIN_MASK                                                               (0x00000004U)

#define CTCR24_DURMODE_SHIFT                                                            (3U)
#define CTCR24_DURMODE_MASK                                                             (0x00000008U)

#define CTCR24_FREE_SHIFT                                                               (4U)
#define CTCR24_FREE_MASK                                                                (0x00000010U)

#define CTCR24_IDLE_SHIFT                                                               (5U)
#define CTCR24_IDLE_MASK                                                                (0x00000020U)

#define CTCR24_OVRFLW_SHIFT                                                             (6U)
#define CTCR24_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR24_CHNSDW_SHIFT                                                             (7U)
#define CTCR24_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR24_INT_SHIFT                                                                (8U)
#define CTCR24_INT_MASK                                                                 (0x00000100U)

#define CTCR24_DBG_SHIFT                                                                (9U)
#define CTCR24_DBG_MASK                                                                 (0x00000200U)

#define CTCR24_RESTART_SHIFT                                                            (10U)
#define CTCR24_RESTART_MASK                                                             (0x00000400U)

#define CTCR24_WDMODE_SHIFT                                                             (11U)
#define CTCR24_WDMODE_MASK                                                              (0x00000800U)

#define CTCR24_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR24_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR24_RESERVED_SHIFT                                                           (13U)
#define CTCR24_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR24_INPSEL_SHIFT                                                             (16U)
#define CTCR24_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR24_WDRESET_SHIFT                                                            (24U)
#define CTCR24_WDRESET_MASK                                                             (0xff000000U)

#define CTCR25_ENBL_SHIFT                                                               (0U)
#define CTCR25_ENBL_MASK                                                                (0x00000001U)

#define CTCR25_RESET_SHIFT                                                              (1U)
#define CTCR25_RESET_MASK                                                               (0x00000002U)

#define CTCR25_CHAIN_SHIFT                                                              (2U)
#define CTCR25_CHAIN_MASK                                                               (0x00000004U)

#define CTCR25_DURMODE_SHIFT                                                            (3U)
#define CTCR25_DURMODE_MASK                                                             (0x00000008U)

#define CTCR25_FREE_SHIFT                                                               (4U)
#define CTCR25_FREE_MASK                                                                (0x00000010U)

#define CTCR25_IDLE_SHIFT                                                               (5U)
#define CTCR25_IDLE_MASK                                                                (0x00000020U)

#define CTCR25_OVRFLW_SHIFT                                                             (6U)
#define CTCR25_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR25_CHNSDW_SHIFT                                                             (7U)
#define CTCR25_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR25_INT_SHIFT                                                                (8U)
#define CTCR25_INT_MASK                                                                 (0x00000100U)

#define CTCR25_DBG_SHIFT                                                                (9U)
#define CTCR25_DBG_MASK                                                                 (0x00000200U)

#define CTCR25_RESTART_SHIFT                                                            (10U)
#define CTCR25_RESTART_MASK                                                             (0x00000400U)

#define CTCR25_WDMODE_SHIFT                                                             (11U)
#define CTCR25_WDMODE_MASK                                                              (0x00000800U)

#define CTCR25_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR25_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR25_RESERVED_SHIFT                                                           (13U)
#define CTCR25_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR25_INPSEL_SHIFT                                                             (16U)
#define CTCR25_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR25_WDRESET_SHIFT                                                            (24U)
#define CTCR25_WDRESET_MASK                                                             (0xff000000U)

#define CTCR26_ENBL_SHIFT                                                               (0U)
#define CTCR26_ENBL_MASK                                                                (0x00000001U)

#define CTCR26_RESET_SHIFT                                                              (1U)
#define CTCR26_RESET_MASK                                                               (0x00000002U)

#define CTCR26_CHAIN_SHIFT                                                              (2U)
#define CTCR26_CHAIN_MASK                                                               (0x00000004U)

#define CTCR26_DURMODE_SHIFT                                                            (3U)
#define CTCR26_DURMODE_MASK                                                             (0x00000008U)

#define CTCR26_FREE_SHIFT                                                               (4U)
#define CTCR26_FREE_MASK                                                                (0x00000010U)

#define CTCR26_IDLE_SHIFT                                                               (5U)
#define CTCR26_IDLE_MASK                                                                (0x00000020U)

#define CTCR26_OVRFLW_SHIFT                                                             (6U)
#define CTCR26_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR26_CHNSDW_SHIFT                                                             (7U)
#define CTCR26_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR26_INT_SHIFT                                                                (8U)
#define CTCR26_INT_MASK                                                                 (0x00000100U)

#define CTCR26_DBG_SHIFT                                                                (9U)
#define CTCR26_DBG_MASK                                                                 (0x00000200U)

#define CTCR26_RESTART_SHIFT                                                            (10U)
#define CTCR26_RESTART_MASK                                                             (0x00000400U)

#define CTCR26_WDMODE_SHIFT                                                             (11U)
#define CTCR26_WDMODE_MASK                                                              (0x00000800U)

#define CTCR26_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR26_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR26_RESERVED_SHIFT                                                           (13U)
#define CTCR26_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR26_INPSEL_SHIFT                                                             (16U)
#define CTCR26_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR26_WDRESET_SHIFT                                                            (24U)
#define CTCR26_WDRESET_MASK                                                             (0xff000000U)

#define CTCR27_ENBL_SHIFT                                                               (0U)
#define CTCR27_ENBL_MASK                                                                (0x00000001U)

#define CTCR27_RESET_SHIFT                                                              (1U)
#define CTCR27_RESET_MASK                                                               (0x00000002U)

#define CTCR27_CHAIN_SHIFT                                                              (2U)
#define CTCR27_CHAIN_MASK                                                               (0x00000004U)

#define CTCR27_DURMODE_SHIFT                                                            (3U)
#define CTCR27_DURMODE_MASK                                                             (0x00000008U)

#define CTCR27_FREE_SHIFT                                                               (4U)
#define CTCR27_FREE_MASK                                                                (0x00000010U)

#define CTCR27_IDLE_SHIFT                                                               (5U)
#define CTCR27_IDLE_MASK                                                                (0x00000020U)

#define CTCR27_OVRFLW_SHIFT                                                             (6U)
#define CTCR27_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR27_CHNSDW_SHIFT                                                             (7U)
#define CTCR27_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR27_INT_SHIFT                                                                (8U)
#define CTCR27_INT_MASK                                                                 (0x00000100U)

#define CTCR27_DBG_SHIFT                                                                (9U)
#define CTCR27_DBG_MASK                                                                 (0x00000200U)

#define CTCR27_RESTART_SHIFT                                                            (10U)
#define CTCR27_RESTART_MASK                                                             (0x00000400U)

#define CTCR27_WDMODE_SHIFT                                                             (11U)
#define CTCR27_WDMODE_MASK                                                              (0x00000800U)

#define CTCR27_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR27_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR27_RESERVED_SHIFT                                                           (13U)
#define CTCR27_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR27_INPSEL_SHIFT                                                             (16U)
#define CTCR27_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR27_WDRESET_SHIFT                                                            (24U)
#define CTCR27_WDRESET_MASK                                                             (0xff000000U)

#define CTCR28_ENBL_SHIFT                                                               (0U)
#define CTCR28_ENBL_MASK                                                                (0x00000001U)

#define CTCR28_RESET_SHIFT                                                              (1U)
#define CTCR28_RESET_MASK                                                               (0x00000002U)

#define CTCR28_CHAIN_SHIFT                                                              (2U)
#define CTCR28_CHAIN_MASK                                                               (0x00000004U)

#define CTCR28_DURMODE_SHIFT                                                            (3U)
#define CTCR28_DURMODE_MASK                                                             (0x00000008U)

#define CTCR28_FREE_SHIFT                                                               (4U)
#define CTCR28_FREE_MASK                                                                (0x00000010U)

#define CTCR28_IDLE_SHIFT                                                               (5U)
#define CTCR28_IDLE_MASK                                                                (0x00000020U)

#define CTCR28_OVRFLW_SHIFT                                                             (6U)
#define CTCR28_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR28_CHNSDW_SHIFT                                                             (7U)
#define CTCR28_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR28_INT_SHIFT                                                                (8U)
#define CTCR28_INT_MASK                                                                 (0x00000100U)

#define CTCR28_DBG_SHIFT                                                                (9U)
#define CTCR28_DBG_MASK                                                                 (0x00000200U)

#define CTCR28_RESTART_SHIFT                                                            (10U)
#define CTCR28_RESTART_MASK                                                             (0x00000400U)

#define CTCR28_WDMODE_SHIFT                                                             (11U)
#define CTCR28_WDMODE_MASK                                                              (0x00000800U)

#define CTCR28_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR28_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR28_RESERVED_SHIFT                                                           (13U)
#define CTCR28_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR28_INPSEL_SHIFT                                                             (16U)
#define CTCR28_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR28_WDRESET_SHIFT                                                            (24U)
#define CTCR28_WDRESET_MASK                                                             (0xff000000U)

#define CTCR29_ENBL_SHIFT                                                               (0U)
#define CTCR29_ENBL_MASK                                                                (0x00000001U)

#define CTCR29_RESET_SHIFT                                                              (1U)
#define CTCR29_RESET_MASK                                                               (0x00000002U)

#define CTCR29_CHAIN_SHIFT                                                              (2U)
#define CTCR29_CHAIN_MASK                                                               (0x00000004U)

#define CTCR29_DURMODE_SHIFT                                                            (3U)
#define CTCR29_DURMODE_MASK                                                             (0x00000008U)

#define CTCR29_FREE_SHIFT                                                               (4U)
#define CTCR29_FREE_MASK                                                                (0x00000010U)

#define CTCR29_IDLE_SHIFT                                                               (5U)
#define CTCR29_IDLE_MASK                                                                (0x00000020U)

#define CTCR29_OVRFLW_SHIFT                                                             (6U)
#define CTCR29_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR29_CHNSDW_SHIFT                                                             (7U)
#define CTCR29_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR29_INT_SHIFT                                                                (8U)
#define CTCR29_INT_MASK                                                                 (0x00000100U)

#define CTCR29_DBG_SHIFT                                                                (9U)
#define CTCR29_DBG_MASK                                                                 (0x00000200U)

#define CTCR29_RESTART_SHIFT                                                            (10U)
#define CTCR29_RESTART_MASK                                                             (0x00000400U)

#define CTCR29_WDMODE_SHIFT                                                             (11U)
#define CTCR29_WDMODE_MASK                                                              (0x00000800U)

#define CTCR29_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR29_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR29_RESERVED_SHIFT                                                           (13U)
#define CTCR29_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR29_INPSEL_SHIFT                                                             (16U)
#define CTCR29_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR29_WDRESET_SHIFT                                                            (24U)
#define CTCR29_WDRESET_MASK                                                             (0xff000000U)

#define CTCR30_ENBL_SHIFT                                                               (0U)
#define CTCR30_ENBL_MASK                                                                (0x00000001U)

#define CTCR30_RESET_SHIFT                                                              (1U)
#define CTCR30_RESET_MASK                                                               (0x00000002U)

#define CTCR30_CHAIN_SHIFT                                                              (2U)
#define CTCR30_CHAIN_MASK                                                               (0x00000004U)

#define CTCR30_DURMODE_SHIFT                                                            (3U)
#define CTCR30_DURMODE_MASK                                                             (0x00000008U)

#define CTCR30_FREE_SHIFT                                                               (4U)
#define CTCR30_FREE_MASK                                                                (0x00000010U)

#define CTCR30_IDLE_SHIFT                                                               (5U)
#define CTCR30_IDLE_MASK                                                                (0x00000020U)

#define CTCR30_OVRFLW_SHIFT                                                             (6U)
#define CTCR30_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR30_CHNSDW_SHIFT                                                             (7U)
#define CTCR30_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR30_INT_SHIFT                                                                (8U)
#define CTCR30_INT_MASK                                                                 (0x00000100U)

#define CTCR30_DBG_SHIFT                                                                (9U)
#define CTCR30_DBG_MASK                                                                 (0x00000200U)

#define CTCR30_RESTART_SHIFT                                                            (10U)
#define CTCR30_RESTART_MASK                                                             (0x00000400U)

#define CTCR30_WDMODE_SHIFT                                                             (11U)
#define CTCR30_WDMODE_MASK                                                              (0x00000800U)

#define CTCR30_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR30_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR30_RESERVED_SHIFT                                                           (13U)
#define CTCR30_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR30_INPSEL_SHIFT                                                             (16U)
#define CTCR30_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR30_WDRESET_SHIFT                                                            (24U)
#define CTCR30_WDRESET_MASK                                                             (0xff000000U)

#define CTCR31_ENBL_SHIFT                                                               (0U)
#define CTCR31_ENBL_MASK                                                                (0x00000001U)

#define CTCR31_RESET_SHIFT                                                              (1U)
#define CTCR31_RESET_MASK                                                               (0x00000002U)

#define CTCR31_CHAIN_SHIFT                                                              (2U)
#define CTCR31_CHAIN_MASK                                                               (0x00000004U)

#define CTCR31_DURMODE_SHIFT                                                            (3U)
#define CTCR31_DURMODE_MASK                                                             (0x00000008U)

#define CTCR31_FREE_SHIFT                                                               (4U)
#define CTCR31_FREE_MASK                                                                (0x00000010U)

#define CTCR31_IDLE_SHIFT                                                               (5U)
#define CTCR31_IDLE_MASK                                                                (0x00000020U)

#define CTCR31_OVRFLW_SHIFT                                                             (6U)
#define CTCR31_OVRFLW_MASK                                                              (0x00000040U)

#define CTCR31_CHNSDW_SHIFT                                                             (7U)
#define CTCR31_CHNSDW_MASK                                                              (0x00000080U)

#define CTCR31_INT_SHIFT                                                                (8U)
#define CTCR31_INT_MASK                                                                 (0x00000100U)

#define CTCR31_DBG_SHIFT                                                                (9U)
#define CTCR31_DBG_MASK                                                                 (0x00000200U)

#define CTCR31_RESTART_SHIFT                                                            (10U)
#define CTCR31_RESTART_MASK                                                             (0x00000400U)

#define CTCR31_WDMODE_SHIFT                                                             (11U)
#define CTCR31_WDMODE_MASK                                                              (0x00000800U)

#define CTCR31_DBG_TRIG_STAT_SHIFT                                                      (12U)
#define CTCR31_DBG_TRIG_STAT_MASK                                                       (0x00001000U)

#define CTCR31_RESERVED_SHIFT                                                           (13U)
#define CTCR31_RESERVED_MASK                                                            (0x0000e000U)

#define CTCR31_INPSEL_SHIFT                                                             (16U)
#define CTCR31_INPSEL_MASK                                                              (0x00ff0000U)

#define CTCR31_WDRESET_SHIFT                                                            (24U)
#define CTCR31_WDRESET_MASK                                                             (0xff000000U)

#define CTCNTR0_COUNT_SHIFT                                                             (0U)
#define CTCNTR0_COUNT_MASK                                                              (0xffffffffU)

#define CTCNTR1_COUNT_SHIFT                                                             (0U)
#define CTCNTR1_COUNT_MASK                                                              (0xffffffffU)

#define CTCNTR2_COUNT_SHIFT                                                             (0U)
#define CTCNTR2_COUNT_MASK                                                              (0xffffffffU)

#define CTCNTR3_COUNT_SHIFT                                                             (0U)
#define CTCNTR3_COUNT_MASK                                                              (0xffffffffU)

#define CTCNTR4_COUNT_SHIFT                                                             (0U)
#define CTCNTR4_COUNT_MASK                                                              (0xffffffffU)

#define CTCNTR5_COUNT_SHIFT                                                             (0U)
#define CTCNTR5_COUNT_MASK                                                              (0xffffffffU)

#define CTCNTR6_COUNT_SHIFT                                                             (0U)
#define CTCNTR6_COUNT_MASK                                                              (0xffffffffU)

#define CTCNTR7_COUNT_SHIFT                                                             (0U)
#define CTCNTR7_COUNT_MASK                                                              (0xffffffffU)

#define CTCNTR8_COUNT_SHIFT                                                             (0U)
#define CTCNTR8_COUNT_MASK                                                              (0xffffffffU)

#define CTCNTR9_COUNT_SHIFT                                                             (0U)
#define CTCNTR9_COUNT_MASK                                                              (0xffffffffU)

#define CTCNTR10_COUNT_SHIFT                                                            (0U)
#define CTCNTR10_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR11_COUNT_SHIFT                                                            (0U)
#define CTCNTR11_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR12_COUNT_SHIFT                                                            (0U)
#define CTCNTR12_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR13_COUNT_SHIFT                                                            (0U)
#define CTCNTR13_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR14_COUNT_SHIFT                                                            (0U)
#define CTCNTR14_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR15_COUNT_SHIFT                                                            (0U)
#define CTCNTR15_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR16_COUNT_SHIFT                                                            (0U)
#define CTCNTR16_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR17_COUNT_SHIFT                                                            (0U)
#define CTCNTR17_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR18_COUNT_SHIFT                                                            (0U)
#define CTCNTR18_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR19_COUNT_SHIFT                                                            (0U)
#define CTCNTR19_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR20_COUNT_SHIFT                                                            (0U)
#define CTCNTR20_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR21_COUNT_SHIFT                                                            (0U)
#define CTCNTR21_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR22_COUNT_SHIFT                                                            (0U)
#define CTCNTR22_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR23_COUNT_SHIFT                                                            (0U)
#define CTCNTR23_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR24_COUNT_SHIFT                                                            (0U)
#define CTCNTR24_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR25_COUNT_SHIFT                                                            (0U)
#define CTCNTR25_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR26_COUNT_SHIFT                                                            (0U)
#define CTCNTR26_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR27_COUNT_SHIFT                                                            (0U)
#define CTCNTR27_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR28_COUNT_SHIFT                                                            (0U)
#define CTCNTR28_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR29_COUNT_SHIFT                                                            (0U)
#define CTCNTR29_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR30_COUNT_SHIFT                                                            (0U)
#define CTCNTR30_COUNT_MASK                                                             (0xffffffffU)

#define CTCNTR31_COUNT_SHIFT                                                            (0U)
#define CTCNTR31_COUNT_MASK                                                             (0xffffffffU)

#define CTEOI_EOI_SHIFT                                                                 (0U)
#define CTEOI_EOI_MASK                                                                  (0x00000001U)

#define CTEOI_RESERVED_SHIFT                                                            (1U)
#define CTEOI_RESERVED_MASK                                                             (0xfffffffeU)

#define CTIRQSTAT_RAW_TIM_INT_IRQ_SHIFT                                                 (0U)
#define CTIRQSTAT_RAW_TIM_INT_IRQ_MASK                                                  (0x00000001U)

#define CTIRQSTAT_RAW_RESERVED_SHIFT                                                    (8U)
#define CTIRQSTAT_RAW_RESERVED_MASK                                                     (0x00000100U)

#define CTIRQSTAT_TIM_INT_SHIFT                                                         (0U)
#define CTIRQSTAT_TIM_INT_MASK                                                          (0x00000001U)

#define CTIRQSTAT_RESERVED_SHIFT                                                        (8U)
#define CTIRQSTAT_RESERVED_MASK                                                         (0x00000100U)

#define CTIRQENABLE_SET_TIM_INT_IES_SHIFT                                               (0U)
#define CTIRQENABLE_SET_TIM_INT_IES_MASK                                                (0x00000001U)

#define CTIRQENABLE_SET_RESERVED_SHIFT                                                  (8U)
#define CTIRQENABLE_SET_RESERVED_MASK                                                   (0x00000100U)

#define CTIRQENABLE_CLR_TIM_INT_IEC_SHIFT                                               (0U)
#define CTIRQENABLE_CLR_TIM_INT_IEC_MASK                                                (0x00000001U)

#define CTIRQENABLE_CLR_RESERVED_SHIFT                                                  (8U)
#define CTIRQENABLE_CLR_RESERVED_MASK                                                   (0x00000100U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_ISS_CTSET_CORE_H_ */

