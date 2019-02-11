/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2015
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

#ifndef HW_RTI_H_
#define HW_RTI_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define RTI_RTIGCTRL                                                (0x0U)
#define RTI_RTITBCTRL                                               (0x4U)
#define RTI_RTICAPCTRL                                              (0x8U)
#define RTI_RTICOMPCTRL                                             (0xcU)
#define RTI_RTIFRC0                                                 (0x10U)
#define RTI_RTIUC0                                                  (0x14U)
#define RTI_RTICPUC0                                                (0x18U)
#define RTI_RTICAFRC0                                               (0x20U)
#define RTI_RTICAUC0                                                (0x24U)
#define RTI_RTIFRC1                                                 (0x30U)
#define RTI_RTIUC1                                                  (0x34U)
#define RTI_RTICPUC1                                                (0x38U)
#define RTI_RTICAFRC1                                               (0x40U)
#define RTI_RTICAUC1                                                (0x44U)
#define RTI_RTICOMP0                                                (0x50U)
#define RTI_RTIUDCP0                                                (0x54U)
#define RTI_RTICOMP1                                                (0x58U)
#define RTI_RTIUDCP1                                                (0x5cU)
#define RTI_RTICOMP2                                                (0x60U)
#define RTI_RTIUDCP2                                                (0x64U)
#define RTI_RTICOMP3                                                (0x68U)
#define RTI_RTIUDCP3                                                (0x6cU)
#define RTI_RTITBLCOMP                                              (0x70U)
#define RTI_RTITBHCOMP                                              (0x74U)
#define RTI_RTISETINT                                               (0x80U)
#define RTI_RTICLEARINT                                             (0x84U)
#define RTI_RTIINTFLAG                                              (0x88U)
#define RTI_RTIDWDCTRL                                              (0x90U)
#define RTI_RTIDWDPRLD                                              (0x94U)
#define RTI_RTIWDSTATUS                                             (0x98U)
#define RTI_RTIWDKEY                                                (0x9cU)
#define RTI_RTIDWDCNTR                                              (0xa0U)
#define RTI_RTIDWWDRXNCTRL                                          (0xa4U)
#define RTI_RTIDWWDSIZECTRL                                         (0xa8U)
#define RTI_RTIINTCLRENABLE                                         (0xacU)
#define RTI_RTICOMP0CLR                                             (0xb0U)
#define RTI_RTICOMP1CLR                                             (0xb4U)
#define RTI_RTICOMP2CLR                                             (0xb8U)
#define RTI_RTICOMP3CLR                                             (0xbcU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define RTI_RTIGCTRL_CNT0EN_SHIFT                                                       (0U)
#define RTI_RTIGCTRL_CNT0EN_MASK                                                        (0x00000001U)

#define RTI_RTIGCTRL_CNT1EN_SHIFT                                                       (1U)
#define RTI_RTIGCTRL_CNT1EN_MASK                                                        (0x00000002U)

#define RTI_RTIGCTRL_COS_SHIFT                                                          (15U)
#define RTI_RTIGCTRL_COS_MASK                                                           (0x00008000U)

#define RTI_RTIGCTRL_NTUSEL_SHIFT                                                       (16U)
#define RTI_RTIGCTRL_NTUSEL_MASK                                                        (0x000f0000U)

#define RTI_RTITBCTRL_TBEXT_SHIFT                                                       (0U)
#define RTI_RTITBCTRL_TBEXT_MASK                                                        (0x00000001U)

#define RTI_RTITBCTRL_INC_SHIFT                                                         (1U)
#define RTI_RTITBCTRL_INC_MASK                                                          (0x00000002U)

#define RTI_RTICAPCTRL_CAPCNTR0_SHIFT                                                   (0U)
#define RTI_RTICAPCTRL_CAPCNTR0_MASK                                                    (0x00000001U)

#define RTI_RTICAPCTRL_CAPCNTR1_SHIFT                                                   (1U)
#define RTI_RTICAPCTRL_CAPCNTR1_MASK                                                    (0x00000002U)

#define RTI_RTICOMPCTRL_COMPSEL0_SHIFT                                                  (0U)
#define RTI_RTICOMPCTRL_COMPSEL0_MASK                                                   (0x00000001U)

#define RTI_RTICOMPCTRL_COMPSEL1_SHIFT                                                  (4U)
#define RTI_RTICOMPCTRL_COMPSEL1_MASK                                                   (0x00000010U)

#define RTI_RTICOMPCTRL_COMPSEL2_SHIFT                                                  (8U)
#define RTI_RTICOMPCTRL_COMPSEL2_MASK                                                   (0x00000100U)

#define RTI_RTICOMPCTRL_COMPSEL3_SHIFT                                                  (12U)
#define RTI_RTICOMPCTRL_COMPSEL3_MASK                                                   (0x00001000U)

#define RTI_RTIFRC0_FRC0_SHIFT                                                          (0U)
#define RTI_RTIFRC0_FRC0_MASK                                                           (0xffffffffU)

#define RTI_RTIUC0_UC0_SHIFT                                                            (0U)
#define RTI_RTIUC0_UC0_MASK                                                             (0xffffffffU)

#define RTI_RTICPUC0_CPUC0_SHIFT                                                        (0U)
#define RTI_RTICPUC0_CPUC0_MASK                                                         (0xffffffffU)

#define RTI_RTICAFRC0_CAFRC0_SHIFT                                                      (0U)
#define RTI_RTICAFRC0_CAFRC0_MASK                                                       (0xffffffffU)

#define RTI_RTICAUC0_CAUC0_SHIFT                                                        (0U)
#define RTI_RTICAUC0_CAUC0_MASK                                                         (0xffffffffU)

#define RTI_RTIFRC1_FRC1_SHIFT                                                          (0U)
#define RTI_RTIFRC1_FRC1_MASK                                                           (0xffffffffU)

#define RTI_RTIUC1_UC1_SHIFT                                                            (0U)
#define RTI_RTIUC1_UC1_MASK                                                             (0xffffffffU)

#define RTI_RTICPUC1_CPUC1_SHIFT                                                        (0U)
#define RTI_RTICPUC1_CPUC1_MASK                                                         (0xffffffffU)

#define RTI_RTICAFRC1_CAFRC1_SHIFT                                                      (0U)
#define RTI_RTICAFRC1_CAFRC1_MASK                                                       (0xffffffffU)

#define RTI_RTICAUC1_CAUC1_SHIFT                                                        (0U)
#define RTI_RTICAUC1_CAUC1_MASK                                                         (0xffffffffU)

#define RTI_RTICOMP0_COMP0_SHIFT                                                        (0U)
#define RTI_RTICOMP0_COMP0_MASK                                                         (0xffffffffU)

#define RTI_RTIUDCP0_UDCP0_SHIFT                                                        (0U)
#define RTI_RTIUDCP0_UDCP0_MASK                                                         (0xffffffffU)

#define RTI_RTICOMP1_COMP1_SHIFT                                                        (0U)
#define RTI_RTICOMP1_COMP1_MASK                                                         (0xffffffffU)

#define RTI_RTIUDCP1_UDCP1_SHIFT                                                        (0U)
#define RTI_RTIUDCP1_UDCP1_MASK                                                         (0xffffffffU)

#define RTI_RTICOMP2_COMP2_SHIFT                                                        (0U)
#define RTI_RTICOMP2_COMP2_MASK                                                         (0xffffffffU)

#define RTI_RTIUDCP2_UDCP2_SHIFT                                                        (0U)
#define RTI_RTIUDCP2_UDCP2_MASK                                                         (0xffffffffU)

#define RTI_RTICOMP3_COMP3_SHIFT                                                        (0U)
#define RTI_RTICOMP3_COMP3_MASK                                                         (0xffffffffU)

#define RTI_RTIUDCP3_UDCP3_SHIFT                                                        (0U)
#define RTI_RTIUDCP3_UDCP3_MASK                                                         (0xffffffffU)

#define RTI_RTITBLCOMP_TBLCOMP_SHIFT                                                    (0U)
#define RTI_RTITBLCOMP_TBLCOMP_MASK                                                     (0xffffffffU)

#define RTI_RTITBHCOMP_TBHCOMP_SHIFT                                                    (0U)
#define RTI_RTITBHCOMP_TBHCOMP_MASK                                                     (0xffffffffU)

#define RTI_RTISETINT_SETINT0_SHIFT                                                     (0U)
#define RTI_RTISETINT_SETINT0_MASK                                                      (0x00000001U)

#define RTI_RTISETINT_SETINT1_SHIFT                                                     (1U)
#define RTI_RTISETINT_SETINT1_MASK                                                      (0x00000002U)

#define RTI_RTISETINT_SETINT2_SHIFT                                                     (2U)
#define RTI_RTISETINT_SETINT2_MASK                                                      (0x00000004U)

#define RTI_RTISETINT_SETINT3_SHIFT                                                     (3U)
#define RTI_RTISETINT_SETINT3_MASK                                                      (0x00000008U)

#define RTI_RTISETINT_SETDMA0_SHIFT                                                     (8U)
#define RTI_RTISETINT_SETDMA0_MASK                                                      (0x00000100U)

#define RTI_RTISETINT_SETDMA1_SHIFT                                                     (9U)
#define RTI_RTISETINT_SETDMA1_MASK                                                      (0x00000200U)

#define RTI_RTISETINT_SETDMA2_SHIFT                                                     (10U)
#define RTI_RTISETINT_SETDMA2_MASK                                                      (0x00000400U)

#define RTI_RTISETINT_SETDMA3_SHIFT                                                     (11U)
#define RTI_RTISETINT_SETDMA3_MASK                                                      (0x00000800U)

#define RTI_RTISETINT_SETTBINT_SHIFT                                                    (16U)
#define RTI_RTISETINT_SETTBINT_MASK                                                     (0x00010000U)

#define RTI_RTISETINT_SETOVL0INT_SHIFT                                                  (17U)
#define RTI_RTISETINT_SETOVL0INT_MASK                                                   (0x00020000U)

#define RTI_RTISETINT_SETOVL1INT_SHIFT                                                  (18U)
#define RTI_RTISETINT_SETOVL1INT_MASK                                                   (0x00040000U)

#define RTI_RTICLEARINT_CLEARINT0_SHIFT                                                 (0U)
#define RTI_RTICLEARINT_CLEARINT0_MASK                                                  (0x00000001U)

#define RTI_RTICLEARINT_CLEARINT1_SHIFT                                                 (1U)
#define RTI_RTICLEARINT_CLEARINT1_MASK                                                  (0x00000002U)

#define RTI_RTICLEARINT_CLEARINT2_SHIFT                                                 (2U)
#define RTI_RTICLEARINT_CLEARINT2_MASK                                                  (0x00000004U)

#define RTI_RTICLEARINT_CLEARINT3_SHIFT                                                 (3U)
#define RTI_RTICLEARINT_CLEARINT3_MASK                                                  (0x00000008U)

#define RTI_RTICLEARINT_CLEARDMA0_SHIFT                                                 (8U)
#define RTI_RTICLEARINT_CLEARDMA0_MASK                                                  (0x00000100U)

#define RTI_RTICLEARINT_CLEARDMA1_SHIFT                                                 (9U)
#define RTI_RTICLEARINT_CLEARDMA1_MASK                                                  (0x00000200U)

#define RTI_RTICLEARINT_CLEARDMA2_SHIFT                                                 (10U)
#define RTI_RTICLEARINT_CLEARDMA2_MASK                                                  (0x00000400U)

#define RTI_RTICLEARINT_CLEARDMA3_SHIFT                                                 (11U)
#define RTI_RTICLEARINT_CLEARDMA3_MASK                                                  (0x00000800U)

#define RTI_RTICLEARINT_CLEARTBINT_SHIFT                                                (16U)
#define RTI_RTICLEARINT_CLEARTBINT_MASK                                                 (0x00010000U)

#define RTI_RTICLEARINT_CLEAROVL0INT_SHIFT                                              (17U)
#define RTI_RTICLEARINT_CLEAROVL0INT_MASK                                               (0x00020000U)

#define RTI_RTICLEARINT_CLEAROVL1INT_SHIFT                                              (18U)
#define RTI_RTICLEARINT_CLEAROVL1INT_MASK                                               (0x00040000U)

#define RTI_RTIINTFLAG_INT0_SHIFT                                                       (0U)
#define RTI_RTIINTFLAG_INT0_MASK                                                        (0x00000001U)

#define RTI_RTIINTFLAG_INT1_SHIFT                                                       (1U)
#define RTI_RTIINTFLAG_INT1_MASK                                                        (0x00000002U)

#define RTI_RTIINTFLAG_INT2_SHIFT                                                       (2U)
#define RTI_RTIINTFLAG_INT2_MASK                                                        (0x00000004U)

#define RTI_RTIINTFLAG_INT3_SHIFT                                                       (3U)
#define RTI_RTIINTFLAG_INT3_MASK                                                        (0x00000008U)

#define RTI_RTIINTFLAG_TBINT_SHIFT                                                      (16U)
#define RTI_RTIINTFLAG_TBINT_MASK                                                       (0x00010000U)

#define RTI_RTIINTFLAG_OVL0INT_SHIFT                                                    (17U)
#define RTI_RTIINTFLAG_OVL0INT_MASK                                                     (0x00020000U)

#define RTI_RTIINTFLAG_OVL1INT_SHIFT                                                    (18U)
#define RTI_RTIINTFLAG_OVL1INT_MASK                                                     (0x00040000U)

#define RTI_RTIDWDCTRL_DWDCTRL_15_0_SHIFT                                               (0U)
#define RTI_RTIDWDCTRL_DWDCTRL_15_0_MASK                                                (0x0000ffffU)

#define RTI_RTIDWDCTRL_DWDCTRL_31_16_SHIFT                                              (16U)
#define RTI_RTIDWDCTRL_DWDCTRL_31_16_MASK                                               (0xffff0000U)
#define RTI_RTIDWDCTRL_DWDCTRL_DISABLE                                                  (0x5312ACEDU)
#define RTI_RTIDWDCTRL_DWDCTRL_ENABLE                                                   (0xA98559DAU)

#define RTI_RTIDWDPRLD_DWDPRLD_SHIFT                                                    (0U)
#define RTI_RTIDWDPRLD_DWDPRLD_MASK                                                     (0x00000fffU)
#define RTI_RTIDWDPRLD_DWDPRLD_MAX                                                      (0x0FFFU)

#define RTI_RTIWDSTATUS_AWDST_SHIFT                                                     (0U)
#define RTI_RTIWDSTATUS_AWDST_MASK                                                      (0x00000001U)

#define RTI_RTIWDSTATUS_DWDST_SHIFT                                                     (1U)
#define RTI_RTIWDSTATUS_DWDST_MASK                                                      (0x00000002U)

#define RTI_RTIWDSTATUS_KEYST_SHIFT                                                     (2U)
#define RTI_RTIWDSTATUS_KEYST_MASK                                                      (0x00000004U)
#define RTI_RTIWDSTATUS_KEYST_CORRECT_KEY                                               (0x00000000U)
#define RTI_RTIWDSTATUS_KEYST_INCORRECT_KEY                                             (0x00000001U)

#define RTI_RTIWDSTATUS_START_TIME_VIOL_SHIFT                                           (3U)
#define RTI_RTIWDSTATUS_START_TIME_VIOL_MASK                                            (0x00000008U)

#define RTI_RTIWDSTATUS_END_TIME_VIOL_SHIFT                                             (4U)
#define RTI_RTIWDSTATUS_END_TIME_VIOL_MASK                                              (0x00000010U)

#define RTI_RTIWDSTATUS_DWWD_ST_SHIFT                                                   (5U)
#define RTI_RTIWDSTATUS_DWWD_ST_MASK                                                    (0x00000020U)

#define RTI_RTIWDKEY_WDKEY_SHIFT                                                        (0U)
#define RTI_RTIWDKEY_WDKEY_MASK                                                         (0x0000ffffU)
#define RTI_RTIWDKEY_WDKEY_FIRST_WRITE                                                  (0x0000E51AU)
#define RTI_RTIWDKEY_WDKEY_SECOND_WRITE                                                 (0x0000A35CU)

#define RTI_RTIDWDCNTR_DWDCNTR_15_0_SHIFT                                               (0U)
#define RTI_RTIDWDCNTR_DWDCNTR_15_0_MASK                                                (0x0000ffffU)

#define RTI_RTIDWDCNTR_DWDCNTR_24_16_SHIFT                                              (16U)
#define RTI_RTIDWDCNTR_DWDCNTR_24_16_MASK                                               (0x01ff0000U)

#define RTI_RTIDWWDRXNCTRL_DWWDRXN_SHIFT                                                (0U)
#define RTI_RTIDWWDRXNCTRL_DWWDRXN_MASK                                                 (0x0000000fU)
#define RTI_RTIDWWDRXNCTRL_DWWDRXN_RESET                                                (0x5U)
#define RTI_RTIDWWDRXNCTRL_DWWDRXN_INTERRUPT                                            (0xAU)


#define RTI_RTIDWWDSIZECTRL_DWWDSIZE_SHIFT                                              (0U)
#define RTI_RTIDWWDSIZECTRL_DWWDSIZE_MASK                                               (0x00ffffffU)
#define RTI_RTIDWWDSIZECTRL_DWWDSIZE_100_PERCENT                                        (0x00000005U)
#define RTI_RTIDWWDSIZECTRL_DWWDSIZE_100_PERCENT_SHIFT                                  (0x0)
#define RTI_RTIDWWDSIZECTRL_DWWDSIZE_50_PERCENT                                         (0x00000050U)
#define RTI_RTIDWWDSIZECTRL_DWWDSIZE_50_PERCENT_SHIFT                                   (0x1)
#define RTI_RTIDWWDSIZECTRL_DWWDSIZE_25_PERCENT                                         (0x00000500U)
#define RTI_RTIDWWDSIZECTRL_DWWDSIZE_25_PERCENT_SHIFT                                   (0x2)
#define RTI_RTIDWWDSIZECTRL_DWWDSIZE_12_5_PERCENT                                       (0x00005000U)
#define RTI_RTIDWWDSIZECTRL_DWWDSIZE_12_5_PERCENT_SHIFT                                 (0x3)
#define RTI_RTIDWWDSIZECTRL_DWWDSIZE_6_25_PERCENT                                       (0x00050000U)
#define RTI_RTIDWWDSIZECTRL_DWWDSIZE_6_25_PERCENT_SHIFT                                 (0x4)
#define RTI_RTIDWWDSIZECTRL_DWWDSIZE_3_125_PERCENT                                      (0x00500000U)
#define RTI_RTIDWWDSIZECTRL_DWWDSIZE_3_125_PERCENT_SHIFT                                (0x5)

#define RTI_RTIINTCLRENABLE_INTCLRENABLE0_SHIFT                                         (0U)
#define RTI_RTIINTCLRENABLE_INTCLRENABLE0_MASK                                          (0x0000000fU)

#define RTI_RTIINTCLRENABLE_INTCLRENABLE1_SHIFT                                         (8U)
#define RTI_RTIINTCLRENABLE_INTCLRENABLE1_MASK                                          (0x00000f00U)

#define RTI_RTIINTCLRENABLE_INTCLRENABLE2_SHIFT                                         (16U)
#define RTI_RTIINTCLRENABLE_INTCLRENABLE2_MASK                                          (0x000f0000U)

#define RTI_RTIINTCLRENABLE_INTCLRENABLE3_SHIFT                                         (24U)
#define RTI_RTIINTCLRENABLE_INTCLRENABLE3_MASK                                          (0x0f000000U)

#define RTI_RTICOMP0CLR_COMP0CLR_SHIFT                                                  (0U)
#define RTI_RTICOMP0CLR_COMP0CLR_MASK                                                   (0xffffffffU)

#define RTI_RTICOMP1CLR_COMP1CLR_SHIFT                                                  (0U)
#define RTI_RTICOMP1CLR_COMP1CLR_MASK                                                   (0xffffffffU)

#define RTI_RTICOMP2CLR_COMP2CLR_SHIFT                                                  (0U)
#define RTI_RTICOMP2CLR_COMP2CLR_MASK                                                   (0xffffffffU)

#define RTI_RTICOMP3CLR_COMP3CLR_SHIFT                                                  (0U)
#define RTI_RTICOMP3CLR_COMP3CLR_MASK                                                   (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_RTI_H_ */

