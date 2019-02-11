/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
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
*
*  \file    hw_dsp_icfg.h
*
*  \brief   register-level header file for DSP
*
**/

#ifndef HW_DSP_ICFG_H_
#define HW_DSP_ICFG_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define DSP_PDCCMD                                                                                          (0x810000U)
#define DSP_MM_REVID                                                                                        (0x812000U)
#define DSP_L2CFG                                                                                           (0x840000U)
#define DSP_L1PCFG                                                                                          (0x840020U)
#define DSP_L1PCC                                                                                           (0x840024U)
#define DSP_L1DCFG                                                                                          (0x840040U)
#define DSP_L1DCC                                                                                           (0x840044U)
#define DSP_L2WBAR                                                                                          (0x844000U)
#define DSP_L2WWC                                                                                           (0x844004U)
#define DSP_L2WIBAR                                                                                         (0x844010U)
#define DSP_L2WIWC                                                                                          (0x844014U)
#define DSP_L2IBAR                                                                                          (0x844018U)
#define DSP_L2IWC                                                                                           (0x84401cU)
#define DSP_L1PIBAR                                                                                         (0x844020U)
#define DSP_L1PIWC                                                                                          (0x844024U)
#define DSP_L1DWIBAR                                                                                        (0x844030U)
#define DSP_L1DWIWC                                                                                         (0x844034U)
#define DSP_L1DWBAR                                                                                         (0x844040U)
#define DSP_L1DIBAR                                                                                         (0x844048U)
#define DSP_L1DIWC                                                                                          (0x84404cU)
#define DSP_L2WB                                                                                            (0x845000U)
#define DSP_L2WBINV                                                                                         (0x845004U)
#define DSP_L2INV                                                                                           (0x845008U)
#define DSP_L1PINV                                                                                          (0x845028U)
#define DSP_L1DWB                                                                                           (0x845040U)
#define DSP_L1DWBINV                                                                                        (0x845044U)
#define DSP_L1DINV                                                                                          (0x845048U)
#define DSP_L2MPFAR                                                                                         (0x84a000U)
#define DSP_L2MPFSR                                                                                         (0x84a004U)
#define DSP_L2MPFCR                                                                                         (0x84a008U)
#define DSP_L1PMPFAR                                                                                        (0x84a400U)
#define DSP_L1PMPFSR                                                                                        (0x84a404U)
#define DSP_L1PMPFCR                                                                                        (0x84a408U)
#define DSP_L1DMPFAR                                                                                        (0x84ac00U)
#define DSP_L1DMPFSR                                                                                        (0x84ac04U)
#define DSP_L1DMPFCR                                                                                        (0x84ac08U)
#define DSP_MPLK0                                                                                           (0x84ad00U)
#define DSP_MPLKCMD                                                                                         (0x84ad10U)
#define DSP_MPLKSTAT                                                                                        (0x84ad14U)
#define DSP_L1DMPPA16                                                                                       (0x84ae40U)
#define DSP_CPUARBE                                                                                         (0x820200U)
#define DSP_IDMAARBE                                                                                        (0x820204U)
#define DSP_SDMAARBE                                                                                        (0x820208U)
#define DSP_ECFGARBE                                                                                        (0x820210U)
#define DSP_ECFGERR                                                                                         (0x820408U)
#define DSP_ECFGERRCLR                                                                                      (0x82040cU)
#define DSP_CPUARBD                                                                                         (0x841040U)
#define DSP_IDMAARBD                                                                                        (0x841044U)
#define DSP_SDMAARBD                                                                                        (0x841048U)
#define DSP_UCARBD                                                                                          (0x84104cU)
#define DSP_CPUARBU                                                                                         (0x841000U)
#define DSP_IDMAARBU                                                                                        (0x841004U)
#define DSP_SDMAARBU                                                                                        (0x841008U)
#define DSP_UCARBU                                                                                          (0x84100cU)
#define DSP_MDMAERR                                                                                         (0x846020U)
#define DSP_MDMAERRCLR                                                                                      (0x846024U)
#define DSP_MDMAARBU                                                                                        (0x841010U)
#define DSP_IDMA0_STAT                                                                                      (0x820000U)
#define DSP_IDMA0_MASK                                                                                      (0x820004U)
#define DSP_IDMA0_SOURCE                                                                                    (0x820008U)
#define DSP_IDMA0_DEST                                                                                      (0x82000cU)
#define DSP_IDMA0_COUNT                                                                                     (0x820010U)
#define DSP_IDMA1_STAT                                                                                      (0x820100U)
#define DSP_IDMA1_SOURCE                                                                                    (0x820108U)
#define DSP_IDMA1_DEST                                                                                      (0x82010cU)
#define DSP_IDMA1_COUNT                                                                                     (0x820110U)
#define DSP_EVTFLAG0                                                                                        (0x800000U)
#define DSP_EVTSET0                                                                                         (0x800020U)
#define DSP_EVTCLR0                                                                                         (0x800040U)
#define DSP_EVTMASK0                                                                                        (0x800080U)
#define DSP_EXPMASK0                                                                                        (0x8000c0U)
#define DSP_MEVTFLAG0                                                                                       (0x8000a0U)
#define DSP_MEXPFLAG0                                                                                       (0x8000e0U)
#define DSP_INTMUX3                                                                                         (0x80010cU)
#define DSP_INTMUX2                                                                                         (0x800108U)
#define DSP_INTMUX1                                                                                         (0x800104U)
#define DSP_INTXSTAT                                                                                        (0x800180U)
#define DSP_INTXCLR                                                                                         (0x800184U)
#define DSP_INTDMASK                                                                                        (0x800188U)
#define DSP_AEGMUX1                                                                                         (0x800144U)
#define DSP_AEGMUX0                                                                                         (0x800140U)
#define DSP_EDCINTMSK                                                                                       (0x831100U)
#if defined (SOC_TDA2PX)
#define DSP_EDCINTFLG                                                                                       (0x831104U)
#define DSP_L1DEDCMD                                                                                        (0x831108U)
#define DSP_L1DDCSTAT                                                                                       (0x83110cU)
#define DSP_L1DDNCSTAT                                                                                      (0x831110U)
#define DSP_L1DTCSTAT                                                                                       (0x831114U)
#define DSP_L1DTNCSTAT                                                                                      (0x831118U)
#define DSP_L1DDEDADDR                                                                                      (0x83111cU)
#define DSP_L1DTEDADDR                                                                                      (0x831120U)
#define DSP_L1DEDCNT                                                                                        (0x831124U)
#define DSP_L2TEDCMD                                                                                        (0x831128U)
#define DSP_L2TCSTAT                                                                                        (0x83112CU)
#define DSP_L2TNCSTAT                                                                                       (0x831130U)
#define DSP_L2TEDADDR                                                                                       (0x831134U)
#define DSP_L2TEDCNT                                                                                        (0x83115CU)
#define DSP_L1PTEDCMD                                                                                       (0x831160U)
#define DSP_L1PTEDSTAT                                                                                      (0x831164U)
#define DSP_L1PTEDADDR                                                                                      (0x831168U)
#define DSP_L1PTEDCNT                                                                                       (0x83116CU)
#endif
#define DSP_L1PEDSTAT                                                                                       (0x846404U)
#define DSP_L1PEDCMD                                                                                        (0x846408U)
#define DSP_L1PEDADDR                                                                                       (0x84640cU)
#define DSP_L2EDSTAT                                                                                        (0x846004U)
#define DSP_L2EDCMD                                                                                         (0x846008U)
#define DSP_L2EDADDR                                                                                        (0x84600cU)
#define DSP_L2EDCPEC                                                                                        (0x846018U)
#define DSP_L2EDCEN                                                                                         (0x846030U)
#define DSP_EVTFLAG1                                                                                        (0x800004U)
#define DSP_EVTFLAG2                                                                                        (0x800008U)
#define DSP_EVTFLAG3                                                                                        (0x80000cU)
#define DSP_EVTCLR1                                                                                         (0x800044U)
#define DSP_EVTCLR2                                                                                         (0x800048U)
#define DSP_EVTCLR3                                                                                         (0x80004cU)
#define DSP_EVTSET1                                                                                         (0x800024U)
#define DSP_EVTSET2                                                                                         (0x800028U)
#define DSP_EVTSET3                                                                                         (0x80002cU)
#define DSP_EVTMASK1                                                                                        (0x800084U)
#define DSP_EVTMASK2                                                                                        (0x800088U)
#define DSP_EVTMASK3                                                                                        (0x80008cU)
#define DSP_MEVTFLAG1                                                                                       (0x8000a4U)
#define DSP_MEVTFLAG2                                                                                       (0x8000a8U)
#define DSP_MEVTFLAG3                                                                                       (0x8000acU)
#define DSP_EXPMASK1                                                                                        (0x8000c4U)
#define DSP_EXPMASK2                                                                                        (0x8000c8U)
#define DSP_EXPMASK3                                                                                        (0x8000ccU)
#define DSP_MEXPFLAG1                                                                                       (0x8000e4U)
#define DSP_MEXPFLAG2                                                                                       (0x8000e8U)
#define DSP_MEXPFLAG3                                                                                       (0x8000ecU)
#define DSP_L1PMPPA17                                                                                       (0x84a644U)
#define DSP_L1PMPPA18                                                                                       (0x84a648U)
#define DSP_L1PMPPA19                                                                                       (0x84a648U)
#define DSP_L1PMPPA20                                                                                       (0x84a648U)
#define DSP_L1PMPPA21                                                                                       (0x84a648U)
#define DSP_L1PMPPA22                                                                                       (0x84a648U)
#define DSP_L1PMPPA23                                                                                       (0x84a648U)
#define DSP_L1PMPPA24                                                                                       (0x84a648U)
#define DSP_L1PMPPA25                                                                                       (0x84a648U)
#define DSP_L1PMPPA26                                                                                       (0x84a648U)
#define DSP_L1PMPPA27                                                                                       (0x84a648U)
#define DSP_L1PMPPA28                                                                                       (0x84a648U)
#define DSP_L1PMPPA29                                                                                       (0x84a648U)
#define DSP_L1PMPPA30                                                                                       (0x84a648U)
#define DSP_L1PMPPA31                                                                                       (0x84a648U)
#define DSP_MPLK1                                                                                           (0x84ad04U)
#define DSP_MPLK2                                                                                           (0x84ad08U)
#define DSP_MPLK3                                                                                           (0x84ad0cU)
#define DSP_L1DMPPA17                                                                                       (0x84ae44U)
#define DSP_L1DMPPA18                                                                                       (0x84ae48U)
#define DSP_L1DMPPA19                                                                                       (0x84ae4cU)
#define DSP_L1DMPPA20                                                                                       (0x84ae50U)
#define DSP_L1DMPPA21                                                                                       (0x84ae54U)
#define DSP_L1DMPPA22                                                                                       (0x84ae58U)
#define DSP_L1DMPPA23                                                                                       (0x84ae5cU)
#define DSP_L1DMPPA24                                                                                       (0x84ae60U)
#define DSP_L1DMPPA25                                                                                       (0x84ae64U)
#define DSP_L1DMPPA26                                                                                       (0x84ae68U)
#define DSP_L1DMPPA27                                                                                       (0x84ae6cU)
#define DSP_L1DMPPA28                                                                                       (0x84ae70U)
#define DSP_L1DMPPA29                                                                                       (0x84ae74U)
#define DSP_L1DMPPA30                                                                                       (0x84ae78U)
#define DSP_L1DMPPA31                                                                                       (0x84ae7cU)
#define DSP_L1DWWC                                                                                          (0x844044U)
#define DSP_MAR(n)                                                                                          (0x848000U + ((n) * 4U))
#define DSP_L2MPPA(n)                                                                                       (0x84a200U + ((n) * 4U))
#define DSP_L1PMPPA16                                                                                       (0x84a640U)
#define DSP_PAMAP(n)                                                                                        (0x820500U + ((n) * 4U))

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define DSP_PDCCMD_RESV_1_SHIFT                                                                             (17U)
#define DSP_PDCCMD_RESV_1_MASK                                                                              (0xfffe0000U)

#define DSP_PDCCMD_RESV_2_SHIFT                                                                             (0U)
#define DSP_PDCCMD_RESV_2_MASK                                                                              (0x0000ffffU)

#define DSP_PDCCMD_MEGPD_SHIFT                                                                              (16U)
#define DSP_PDCCMD_MEGPD_MASK                                                                               (0x00010000U)

#define DSP_MM_REVID_MM_REVID_SHIFT                                                                         (0U)
#define DSP_MM_REVID_MM_REVID_MASK                                                                          (0xffffffffU)

#define DSP_L2CFG_RESV_1_SHIFT                                                                              (28U)
#define DSP_L2CFG_RESV_1_MASK                                                                               (0xf0000000U)

#define DSP_L2CFG_NUM_MM_SHIFT                                                                              (24U)
#define DSP_L2CFG_NUM_MM_MASK                                                                               (0x0f000000U)

#define DSP_L2CFG_RESV_2_SHIFT                                                                              (20U)
#define DSP_L2CFG_RESV_2_MASK                                                                               (0x00f00000U)

#define DSP_L2CFG_MMID_SHIFT                                                                                (16U)
#define DSP_L2CFG_MMID_MASK                                                                                 (0x000f0000U)

#define DSP_L2CFG_RESV_3_SHIFT                                                                              (10U)
#define DSP_L2CFG_RESV_3_MASK                                                                               (0x0000fc00U)

#define DSP_L2CFG_IP_SHIFT                                                                                  (9U)
#define DSP_L2CFG_IP_MASK                                                                                   (0x00000200U)

#define DSP_L2CFG_ID_SHIFT                                                                                  (8U)
#define DSP_L2CFG_ID_MASK                                                                                   (0x00000100U)

#define DSP_L2CFG_RESV_4_SHIFT                                                                              (4U)
#define DSP_L2CFG_RESV_4_MASK                                                                               (0x000000f0U)

#define DSP_L2CFG_L2CC_SHIFT                                                                                (3U)
#define DSP_L2CFG_L2CC_MASK                                                                                 (0x00000008U)

#define DSP_L2CFG_L2MODE_SHIFT                                                                              (0U)
#define DSP_L2CFG_L2MODE_MASK                                                                               (0x00000007U)

#define DSP_L1PCFG_RESV_1_SHIFT                                                                             (3U)
#define DSP_L1PCFG_RESV_1_MASK                                                                              (0xfffffff8U)

#define DSP_L1PCFG_L1PMODE_SHIFT                                                                            (0U)
#define DSP_L1PCFG_L1PMODE_MASK                                                                             (0x00000007U)

#define DSP_L1PCC_RESV_1_SHIFT                                                                              (17U)
#define DSP_L1PCC_RESV_1_MASK                                                                               (0xfffe0000U)

#define DSP_L1PCC_POPER_SHIFT                                                                               (16U)
#define DSP_L1PCC_POPER_MASK                                                                                (0x00010000U)

#define DSP_L1PCC_RESV_2_SHIFT                                                                              (1U)
#define DSP_L1PCC_RESV_2_MASK                                                                               (0x0000fffeU)

#define DSP_L1PCC_OPER_SHIFT                                                                                (0U)
#define DSP_L1PCC_OPER_MASK                                                                                 (0x00000001U)

#define DSP_L1DCFG_RESV_1_SHIFT                                                                             (3U)
#define DSP_L1DCFG_RESV_1_MASK                                                                              (0xfffffff8U)

#define DSP_L1DCFG_L1DMODE_SHIFT                                                                            (0U)
#define DSP_L1DCFG_L1DMODE_MASK                                                                             (0x00000007U)

#define DSP_L1DCC_RESV_1_SHIFT                                                                              (19U)
#define DSP_L1DCC_RESV_1_MASK                                                                               (0x3fff80000U)

#define DSP_L1DCC_POPER_SHIFT                                                                               (16U)
#define DSP_L1DCC_POPER_MASK                                                                                (0x00010000U)

#define DSP_L1DCC_RESV_2_SHIFT                                                                              (3U)
#define DSP_L1DCC_RESV_2_MASK                                                                               (0x0003fff8U)

#define DSP_L1DCC_OPER_SHIFT                                                                                (0U)
#define DSP_L1DCC_OPER_MASK                                                                                 (0x00000001U)

#define DSP_L2WBAR_L2WBAR_SHIFT                                                                             (0U)
#define DSP_L2WBAR_L2WBAR_MASK                                                                              (0xffffffffU)

#define DSP_L2WWC_RESV_1_SHIFT                                                                              (16U)
#define DSP_L2WWC_RESV_1_MASK                                                                               (0xffff0000U)

#define DSP_L2WWC_L2WWC_SHIFT                                                                               (0U)
#define DSP_L2WWC_L2WWC_MASK                                                                                (0x0000ffffU)

#define DSP_L2WIBAR_L2WIBAR_SHIFT                                                                           (0U)
#define DSP_L2WIBAR_L2WIBAR_MASK                                                                            (0xffffffffU)

#define DSP_L2WIWC_RESV_1_SHIFT                                                                             (16U)
#define DSP_L2WIWC_RESV_1_MASK                                                                              (0xffff0000U)

#define DSP_L2WIWC_L2WIWC_SHIFT                                                                             (0U)
#define DSP_L2WIWC_L2WIWC_MASK                                                                              (0x0000ffffU)

#define DSP_L2IBAR_L2IBAR_SHIFT                                                                             (0U)
#define DSP_L2IBAR_L2IBAR_MASK                                                                              (0xffffffffU)

#define DSP_L2IWC_RESV_1_SHIFT                                                                              (16U)
#define DSP_L2IWC_RESV_1_MASK                                                                               (0xffff0000U)

#define DSP_L2IWC_L2IWC_SHIFT                                                                               (0U)
#define DSP_L2IWC_L2IWC_MASK                                                                                (0x0000ffffU)

#define DSP_L1PIBAR_L1PIBAR_SHIFT                                                                           (0U)
#define DSP_L1PIBAR_L1PIBAR_MASK                                                                            (0xffffffffU)

#define DSP_L1PIWC_RESV_1_SHIFT                                                                             (16U)
#define DSP_L1PIWC_RESV_1_MASK                                                                              (0xffff0000U)

#define DSP_L1PIWC_L1PIWC_SHIFT                                                                             (0U)
#define DSP_L1PIWC_L1PIWC_MASK                                                                              (0x0000ffffU)

#define DSP_L1DWIBAR_L1DWIBAR_SHIFT                                                                         (0U)
#define DSP_L1DWIBAR_L1DWIBAR_MASK                                                                          (0xffffffffU)

#define DSP_L1DWIWC_RESV_1_SHIFT                                                                            (16U)
#define DSP_L1DWIWC_RESV_1_MASK                                                                             (0xffff0000U)

#define DSP_L1DWIWC_L1DWIWC_SHIFT                                                                           (0U)
#define DSP_L1DWIWC_L1DWIWC_MASK                                                                            (0x0000ffffU)

#define DSP_L1DWBAR_L1DWBAR_SHIFT                                                                           (0U)
#define DSP_L1DWBAR_L1DWBAR_MASK                                                                            (0xffffffffU)

#define DSP_L1DIBAR_L1DIBAR_SHIFT                                                                           (0U)
#define DSP_L1DIBAR_L1DIBAR_MASK                                                                            (0xffffffffU)

#define DSP_L1DIWC_RESV_1_SHIFT                                                                             (16U)
#define DSP_L1DIWC_RESV_1_MASK                                                                              (0xffff0000U)

#define DSP_L1DIWC_L1DIWC_SHIFT                                                                             (0U)
#define DSP_L1DIWC_L1DIWC_MASK                                                                              (0x0000ffffU)

#define DSP_L2WB_C_SHIFT                                                                                    (0U)
#define DSP_L2WB_C_MASK                                                                                     (0x00000001U)

#define DSP_L2WB_RESV_1_SHIFT                                                                               (1U)
#define DSP_L2WB_RESV_1_MASK                                                                                (0xfffffffeU)

#define DSP_L2WBINV_C_SHIFT                                                                                 (0U)
#define DSP_L2WBINV_C_MASK                                                                                  (0x00000001U)

#define DSP_L2WBINV_RESV_1_SHIFT                                                                            (1U)
#define DSP_L2WBINV_RESV_1_MASK                                                                             (0xfffffffeU)

#define DSP_L2INV_I_SHIFT                                                                                   (0U)
#define DSP_L2INV_I_MASK                                                                                    (0x00000001U)

#define DSP_L2INV_RESV_1_SHIFT                                                                              (1U)
#define DSP_L2INV_RESV_1_MASK                                                                               (0xfffffffeU)

#define DSP_L1PINV_I_SHIFT                                                                                  (0U)
#define DSP_L1PINV_I_MASK                                                                                   (0x00000001U)

#define DSP_L1PINV_RESV_1_SHIFT                                                                             (1U)
#define DSP_L1PINV_RESV_1_MASK                                                                              (0xfffffffeU)

#define DSP_L1DWB_C_SHIFT                                                                                   (0U)
#define DSP_L1DWB_C_MASK                                                                                    (0x00000001U)

#define DSP_L1DWB_RESV_1_SHIFT                                                                              (1U)
#define DSP_L1DWB_RESV_1_MASK                                                                               (0xfffffffeU)

#define DSP_L1DWBINV_C_SHIFT                                                                                (0U)
#define DSP_L1DWBINV_C_MASK                                                                                 (0x00000001U)

#define DSP_L1DWBINV_RESV_1_SHIFT                                                                           (1U)
#define DSP_L1DWBINV_RESV_1_MASK                                                                            (0xfffffffeU)

#define DSP_L1DINV_I_SHIFT                                                                                  (0U)
#define DSP_L1DINV_I_MASK                                                                                   (0x00000001U)

#define DSP_L1DINV_RESV_1_SHIFT                                                                             (1U)
#define DSP_L1DINV_RESV_1_MASK                                                                              (0xfffffffeU)

#define DSP_L2MPFAR_ADDR_SHIFT                                                                              (0U)
#define DSP_L2MPFAR_ADDR_MASK                                                                               (0xffffffffU)

#define DSP_L2MPFSR_RESV_1_SHIFT                                                                            (16U)
#define DSP_L2MPFSR_RESV_1_MASK                                                                             (0xffff0000U)

#define DSP_L2MPFSR_FID_SHIFT                                                                               (9U)
#define DSP_L2MPFSR_FID_MASK                                                                                (0x0000fe00U)

#define DSP_L2MPFSR_LOCAL_SHIFT                                                                             (8U)
#define DSP_L2MPFSR_LOCAL_MASK                                                                              (0x00000100U)

#define DSP_L2MPFSR_RESV_2_SHIFT                                                                            (6U)
#define DSP_L2MPFSR_RESV_2_MASK                                                                             (0x000000c0U)

#define DSP_L2MPFSR_SR_SHIFT                                                                                (5U)
#define DSP_L2MPFSR_SR_MASK                                                                                 (0x00000020U)

#define DSP_L2MPFSR_SW_SHIFT                                                                                (4U)
#define DSP_L2MPFSR_SW_MASK                                                                                 (0x00000010U)

#define DSP_L2MPFSR_UR_SHIFT                                                                                (2U)
#define DSP_L2MPFSR_UR_MASK                                                                                 (0x00000004U)

#define DSP_L2MPFSR_UW_SHIFT                                                                                (1U)
#define DSP_L2MPFSR_UW_MASK                                                                                 (0x00000002U)

#define DSP_L2MPFSR_RESV_3_SHIFT                                                                            (3U)
#define DSP_L2MPFSR_RESV_3_MASK                                                                             (0x00000008U)

#define DSP_L2MPFSR_RESV_4_SHIFT                                                                            (0U)
#define DSP_L2MPFSR_RESV_4_MASK                                                                             (0x00000001U)

#define DSP_L2MPFCR_RESV_1_SHIFT                                                                            (1U)
#define DSP_L2MPFCR_RESV_1_MASK                                                                             (0xfffffffeU)

#define DSP_L2MPFCR_MPFCLR_SHIFT                                                                            (0U)
#define DSP_L2MPFCR_MPFCLR_MASK                                                                             (0x00000001U)

#define DSP_L1PMPFAR_ADDR_SHIFT                                                                             (0U)
#define DSP_L1PMPFAR_ADDR_MASK                                                                              (0xffffffffU)

#define DSP_L1PMPFSR_RESV_1_SHIFT                                                                           (16U)
#define DSP_L1PMPFSR_RESV_1_MASK                                                                            (0xffff0000U)

#define DSP_L1PMPFSR_FID_SHIFT                                                                              (9U)
#define DSP_L1PMPFSR_FID_MASK                                                                               (0x0000fe00U)

#define DSP_L1PMPFSR_LOCAL_SHIFT                                                                            (8U)
#define DSP_L1PMPFSR_LOCAL_MASK                                                                             (0x00000100U)

#define DSP_L1PMPFSR_RESV_2_SHIFT                                                                           (6U)
#define DSP_L1PMPFSR_RESV_2_MASK                                                                            (0x000000c0U)

#define DSP_L1PMPFSR_SR_SHIFT                                                                               (5U)
#define DSP_L1PMPFSR_SR_MASK                                                                                (0x00000020U)

#define DSP_L1PMPFSR_SW_SHIFT                                                                               (4U)
#define DSP_L1PMPFSR_SW_MASK                                                                                (0x00000010U)

#define DSP_L1PMPFSR_UR_SHIFT                                                                               (2U)
#define DSP_L1PMPFSR_UR_MASK                                                                                (0x00000004U)

#define DSP_L1PMPFSR_UW_SHIFT                                                                               (1U)
#define DSP_L1PMPFSR_UW_MASK                                                                                (0x00000002U)

#define DSP_L1PMPFSR_RESV_3_SHIFT                                                                           (3U)
#define DSP_L1PMPFSR_RESV_3_MASK                                                                            (0x00000008U)

#define DSP_L1PMPFSR_RESV_4_SHIFT                                                                           (0U)
#define DSP_L1PMPFSR_RESV_4_MASK                                                                            (0x00000001U)

#define DSP_L1PMPFCR_RESV_1_SHIFT                                                                           (1U)
#define DSP_L1PMPFCR_RESV_1_MASK                                                                            (0xfffffffeU)

#define DSP_L1PMPFCR_MPFCLR_SHIFT                                                                           (0U)
#define DSP_L1PMPFCR_MPFCLR_MASK                                                                            (0x00000001U)

#define DSP_L1DMPFAR_L1DMPFAR_SHIFT                                                                         (0U)
#define DSP_L1DMPFAR_L1DMPFAR_MASK                                                                          (0xffffffffU)

#define DSP_L1DMPFSR_RESV_1_SHIFT                                                                           (16U)
#define DSP_L1DMPFSR_RESV_1_MASK                                                                            (0xffff0000U)

#define DSP_L1DMPFSR_FID_SHIFT                                                                              (9U)
#define DSP_L1DMPFSR_FID_MASK                                                                               (0x0000fe00U)

#define DSP_L1DMPFSR_LOCAL_SHIFT                                                                            (8U)
#define DSP_L1DMPFSR_LOCAL_MASK                                                                             (0x00000100U)

#define DSP_L1DMPFSR_RESV_2_SHIFT                                                                           (6U)
#define DSP_L1DMPFSR_RESV_2_MASK                                                                            (0x000000c0U)

#define DSP_L1DMPFSR_SR_SHIFT                                                                               (5U)
#define DSP_L1DMPFSR_SR_MASK                                                                                (0x00000020U)

#define DSP_L1DMPFSR_SW_SHIFT                                                                               (4U)
#define DSP_L1DMPFSR_SW_MASK                                                                                (0x00000010U)

#define DSP_L1DMPFSR_SX_SHIFT                                                                               (3U)
#define DSP_L1DMPFSR_SX_MASK                                                                                (0x00000008U)

#define DSP_L1DMPFSR_UR_SHIFT                                                                               (2U)
#define DSP_L1DMPFSR_UR_MASK                                                                                (0x00000004U)

#define DSP_L1DMPFSR_UW_SHIFT                                                                               (1U)
#define DSP_L1DMPFSR_UW_MASK                                                                                (0x00000002U)

#define DSP_L1DMPFSR_UX_SHIFT                                                                               (0U)
#define DSP_L1DMPFSR_UX_MASK                                                                                (0x00000001U)

#define DSP_L1DMPFCR_RESV_1_SHIFT                                                                           (1U)
#define DSP_L1DMPFCR_RESV_1_MASK                                                                            (0xfffffffeU)

#define DSP_L1DMPFCR_MPFCLR_SHIFT                                                                           (0U)
#define DSP_L1DMPFCR_MPFCLR_MASK                                                                            (0x00000001U)

#define DSP_MPLK0_MPLK_SHIFT                                                                                (0U)
#define DSP_MPLK0_MPLK_MASK                                                                                 (0xffffffffU)

#define DSP_MPLKCMD_RESV_1_SHIFT                                                                            (3U)
#define DSP_MPLKCMD_RESV_1_MASK                                                                             (0xfffffff8U)

#define DSP_MPLKCMD_KEYR_SHIFT                                                                              (2U)
#define DSP_MPLKCMD_KEYR_MASK                                                                               (0x00000004U)

#define DSP_MPLKCMD_LOCK_SHIFT                                                                              (1U)
#define DSP_MPLKCMD_LOCK_MASK                                                                               (0x00000002U)

#define DSP_MPLKCMD_UNLOCK_SHIFT                                                                            (0U)
#define DSP_MPLKCMD_UNLOCK_MASK                                                                             (0x00000001U)

#define DSP_MPLKSTAT_RESV_1_SHIFT                                                                           (1U)
#define DSP_MPLKSTAT_RESV_1_MASK                                                                            (0xfffffffeU)

#define DSP_MPLKSTAT_LK_SHIFT                                                                               (0U)
#define DSP_MPLKSTAT_LK_MASK                                                                                (0x00000001U)

#define DSP_L1DMPPA16_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1DMPPA16_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1DMPPA16_AID5_SHIFT                                                                            (15U)
#define DSP_L1DMPPA16_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1DMPPA16_AID4_SHIFT                                                                            (14U)
#define DSP_L1DMPPA16_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1DMPPA16_AID3_SHIFT                                                                            (13U)
#define DSP_L1DMPPA16_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1DMPPA16_AID2_SHIFT                                                                            (12U)
#define DSP_L1DMPPA16_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1DMPPA16_AID1_SHIFT                                                                            (11U)
#define DSP_L1DMPPA16_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1DMPPA16_AID0_SHIFT                                                                            (10U)
#define DSP_L1DMPPA16_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1DMPPA16_AIDX_SHIFT                                                                            (9U)
#define DSP_L1DMPPA16_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1DMPPA16_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1DMPPA16_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1DMPPA16_NS_SHIFT                                                                              (7U)
#define DSP_L1DMPPA16_NS_MASK                                                                               (0x00000080U)

#define DSP_L1DMPPA16_EMU_SHIFT                                                                             (6U)
#define DSP_L1DMPPA16_EMU_MASK                                                                              (0x00000040U)

#define DSP_L1DMPPA16_SR_SHIFT                                                                              (5U)
#define DSP_L1DMPPA16_SR_MASK                                                                               (0x00000020U)

#define DSP_L1DMPPA16_SW_SHIFT                                                                              (4U)
#define DSP_L1DMPPA16_SW_MASK                                                                               (0x00000010U)

#define DSP_L1DMPPA16_SX_SHIFT                                                                              (3U)
#define DSP_L1DMPPA16_SX_MASK                                                                               (0x00000008U)

#define DSP_L1DMPPA16_UR_SHIFT                                                                              (2U)
#define DSP_L1DMPPA16_UR_MASK                                                                               (0x00000004U)

#define DSP_L1DMPPA16_UW_SHIFT                                                                              (1U)
#define DSP_L1DMPPA16_UW_MASK                                                                               (0x00000002U)

#define DSP_L1DMPPA16_UX_SHIFT                                                                              (0U)
#define DSP_L1DMPPA16_UX_MASK                                                                               (0x00000001U)

#define DSP_CPUARBE_RESV_1_SHIFT                                                                            (19U)
#define DSP_CPUARBE_RESV_1_MASK                                                                             (0xfff80000U)

#define DSP_CPUARBE_PRI_SHIFT                                                                               (16U)
#define DSP_CPUARBE_PRI_MASK                                                                                (0x00070000U)

#define DSP_CPUARBE_RESV_2_SHIFT                                                                            (6U)
#define DSP_CPUARBE_RESV_2_MASK                                                                             (0x0000ffc0U)

#define DSP_CPUARBE_MAXWAIT_SHIFT                                                                           (0U)
#define DSP_CPUARBE_MAXWAIT_MASK                                                                            (0x0000003fU)

#define DSP_IDMAARBE_RESV_1_SHIFT                                                                           (6U)
#define DSP_IDMAARBE_RESV_1_MASK                                                                            (0xffffffc0U)

#define DSP_IDMAARBE_MAXWAIT_SHIFT                                                                          (0U)
#define DSP_IDMAARBE_MAXWAIT_MASK                                                                           (0x0000003fU)

#define DSP_SDMAARBE_RESV_1_SHIFT                                                                           (6U)
#define DSP_SDMAARBE_RESV_1_MASK                                                                            (0xffffffc0U)

#define DSP_SDMAARBE_MAXWAIT_SHIFT                                                                          (0U)
#define DSP_SDMAARBE_MAXWAIT_MASK                                                                           (0x0000003fU)

#define DSP_ECFGARBE_RESV_2_SHIFT                                                                           (19U)
#define DSP_ECFGARBE_RESV_2_MASK                                                                            (0xfff80000U)

#define DSP_ECFGARBE_PRI_SHIFT                                                                              (16U)
#define DSP_ECFGARBE_PRI_MASK                                                                               (0x00070000U)

#define DSP_ECFGARBE_RESV_1_SHIFT                                                                           (0U)
#define DSP_ECFGARBE_RESV_1_MASK                                                                            (0x0000ffffU)

#define DSP_ECFGERR_ERR_SHIFT                                                                               (29U)
#define DSP_ECFGERR_ERR_MASK                                                                                (0xe0000000U)

#define DSP_ECFGERR_RESV_2_SHIFT                                                                            (12U)
#define DSP_ECFGERR_RESV_2_MASK                                                                             (0x1ffff000U)

#define DSP_ECFGERR_XID_SHIFT                                                                               (8U)
#define DSP_ECFGERR_XID_MASK                                                                                (0x00000f00U)

#define DSP_ECFGERR_RESV_1_SHIFT                                                                            (3U)
#define DSP_ECFGERR_RESV_1_MASK                                                                             (0x000000f8U)

#define DSP_ECFGERR_STAT_SHIFT                                                                              (0U)
#define DSP_ECFGERR_STAT_MASK                                                                               (0x00000007U)

#define DSP_ECFGERRCLR_RESV_1_SHIFT                                                                         (1U)
#define DSP_ECFGERRCLR_RESV_1_MASK                                                                          (0xfffffffeU)

#define DSP_ECFGERRCLR_CLR_SHIFT                                                                            (0U)
#define DSP_ECFGERRCLR_CLR_MASK                                                                             (0x00000001U)

#define DSP_CPUARBD_RESV_1_SHIFT                                                                            (19U)
#define DSP_CPUARBD_RESV_1_MASK                                                                             (0xfff80000U)

#define DSP_CPUARBD_PRI_SHIFT                                                                               (16U)
#define DSP_CPUARBD_PRI_MASK                                                                                (0x00070000U)

#define DSP_CPUARBD_RESV_2_SHIFT                                                                            (6U)
#define DSP_CPUARBD_RESV_2_MASK                                                                             (0x0000ffc0U)

#define DSP_CPUARBD_MAXWAIT_SHIFT                                                                           (0U)
#define DSP_CPUARBD_MAXWAIT_MASK                                                                            (0x0000003fU)

#define DSP_IDMAARBD_RESV_1_SHIFT                                                                           (6U)
#define DSP_IDMAARBD_RESV_1_MASK                                                                            (0xffffffc0U)

#define DSP_IDMAARBD_MAXWAIT_SHIFT                                                                          (0U)
#define DSP_IDMAARBD_MAXWAIT_MASK                                                                           (0x0000003fU)

#define DSP_SDMAARBD_RESV_1_SHIFT                                                                           (6U)
#define DSP_SDMAARBD_RESV_1_MASK                                                                            (0xffffffc0U)

#define DSP_SDMAARBD_MAXWAIT_SHIFT                                                                          (0U)
#define DSP_SDMAARBD_MAXWAIT_MASK                                                                           (0x0000003fU)

#define DSP_UCARBD_RESV_1_SHIFT                                                                             (6U)
#define DSP_UCARBD_RESV_1_MASK                                                                              (0xffffffc0U)

#define DSP_UCARBD_MAXWAIT_SHIFT                                                                            (0U)
#define DSP_UCARBD_MAXWAIT_MASK                                                                             (0x0000003fU)

#define DSP_CPUARBU_RESV_1_SHIFT                                                                            (19U)
#define DSP_CPUARBU_RESV_1_MASK                                                                             (0xfff80000U)

#define DSP_CPUARBU_PRI_SHIFT                                                                               (16U)
#define DSP_CPUARBU_PRI_MASK                                                                                (0x00070000U)

#define DSP_CPUARBU_RESV_2_SHIFT                                                                            (6U)
#define DSP_CPUARBU_RESV_2_MASK                                                                             (0x0000ffc0U)

#define DSP_CPUARBU_MAXWAIT_SHIFT                                                                           (0U)
#define DSP_CPUARBU_MAXWAIT_MASK                                                                            (0x0000003fU)

#define DSP_IDMAARBU_RESV_1_SHIFT                                                                           (6U)
#define DSP_IDMAARBU_RESV_1_MASK                                                                            (0xffffffc0U)

#define DSP_IDMAARBU_MAXWAIT_SHIFT                                                                          (0U)
#define DSP_IDMAARBU_MAXWAIT_MASK                                                                           (0x0000003fU)

#define DSP_SDMAARBU_RESV_1_SHIFT                                                                           (6U)
#define DSP_SDMAARBU_RESV_1_MASK                                                                            (0xffffffc0U)

#define DSP_SDMAARBU_MAXWAIT_SHIFT                                                                          (0U)
#define DSP_SDMAARBU_MAXWAIT_MASK                                                                           (0x0000003fU)

#define DSP_UCARBU_RESV_1_SHIFT                                                                             (6U)
#define DSP_UCARBU_RESV_1_MASK                                                                              (0xffffffc0U)

#define DSP_UCARBU_MAXWAIT_SHIFT                                                                            (0U)
#define DSP_UCARBU_MAXWAIT_MASK                                                                             (0x0000003fU)

#define DSP_MDMAERR_ERR_SHIFT                                                                               (29U)
#define DSP_MDMAERR_ERR_MASK                                                                                (0xe0000000U)

#define DSP_MDMAERR_RESV_2_SHIFT                                                                            (12U)
#define DSP_MDMAERR_RESV_2_MASK                                                                             (0x1ffff000U)

#define DSP_MDMAERR_XID_SHIFT                                                                               (8U)
#define DSP_MDMAERR_XID_MASK                                                                                (0x00000f00U)

#define DSP_MDMAERR_RESV_1_SHIFT                                                                            (3U)
#define DSP_MDMAERR_RESV_1_MASK                                                                             (0x000000f8U)

#define DSP_MDMAERR_STAT_SHIFT                                                                              (0U)
#define DSP_MDMAERR_STAT_MASK                                                                               (0x00000007U)

#define DSP_MDMAERRCLR_RESV_1_SHIFT                                                                         (1U)
#define DSP_MDMAERRCLR_RESV_1_MASK                                                                          (0xfffffffeU)

#define DSP_MDMAERRCLR_CLR_SHIFT                                                                            (0U)
#define DSP_MDMAERRCLR_CLR_MASK                                                                             (0x00000001U)

#define DSP_MDMAARBU_RESV_1_SHIFT                                                                           (27U)
#define DSP_MDMAARBU_RESV_1_MASK                                                                            (0xf8000000U)

#define DSP_MDMAARBU_UPRI_SHIFT                                                                             (24U)
#define DSP_MDMAARBU_UPRI_MASK                                                                              (0x07000000U)

#define DSP_MDMAARBU_RESV_2_SHIFT                                                                           (19U)
#define DSP_MDMAARBU_RESV_2_MASK                                                                            (0x00f80000U)

#define DSP_MDMAARBU_PRI_SHIFT                                                                              (16U)
#define DSP_MDMAARBU_PRI_MASK                                                                               (0x00070000U)

#define DSP_MDMAARBU_RESV_3_SHIFT                                                                           (0U)
#define DSP_MDMAARBU_RESV_3_MASK                                                                            (0x0000ffffU)

#define DSP_IDMA0_STAT__RESV1_SHIFT                                                                         (2U)
#define DSP_IDMA0_STAT__RESV1_MASK                                                                          (0xfffffffcU)

#define DSP_IDMA0_STAT_PEND_SHIFT                                                                           (1U)
#define DSP_IDMA0_STAT_PEND_MASK                                                                            (0x00000002U)

#define DSP_IDMA0_STAT_ACTV_SHIFT                                                                           (0U)
#define DSP_IDMA0_STAT_ACTV_MASK                                                                            (0x00000001U)

#define DSP_IDMA0_MASK_M0_SHIFT                                                                             (0U)
#define DSP_IDMA0_MASK_M0_MASK                                                                              (0x00000001U)

#define DSP_IDMA0_MASK_M1_SHIFT                                                                             (1U)
#define DSP_IDMA0_MASK_M1_MASK                                                                              (0x00000002U)

#define DSP_IDMA0_MASK_M2_SHIFT                                                                             (2U)
#define DSP_IDMA0_MASK_M2_MASK                                                                              (0x00000004U)

#define DSP_IDMA0_MASK_M3_SHIFT                                                                             (3U)
#define DSP_IDMA0_MASK_M3_MASK                                                                              (0x00000008U)

#define DSP_IDMA0_MASK_M4_SHIFT                                                                             (4U)
#define DSP_IDMA0_MASK_M4_MASK                                                                              (0x00000010U)

#define DSP_IDMA0_MASK_M5_SHIFT                                                                             (5U)
#define DSP_IDMA0_MASK_M5_MASK                                                                              (0x00000020U)

#define DSP_IDMA0_MASK_M6_SHIFT                                                                             (6U)
#define DSP_IDMA0_MASK_M6_MASK                                                                              (0x00000040U)

#define DSP_IDMA0_MASK_M7_SHIFT                                                                             (7U)
#define DSP_IDMA0_MASK_M7_MASK                                                                              (0x00000080U)

#define DSP_IDMA0_MASK_M8_SHIFT                                                                             (8U)
#define DSP_IDMA0_MASK_M8_MASK                                                                              (0x00000100U)

#define DSP_IDMA0_MASK_M9_SHIFT                                                                             (9U)
#define DSP_IDMA0_MASK_M9_MASK                                                                              (0x00000200U)

#define DSP_IDMA0_MASK_M10_SHIFT                                                                            (10U)
#define DSP_IDMA0_MASK_M10_MASK                                                                             (0x00000400U)

#define DSP_IDMA0_MASK_M11_SHIFT                                                                            (11U)
#define DSP_IDMA0_MASK_M11_MASK                                                                             (0x00000800U)

#define DSP_IDMA0_MASK_M12_SHIFT                                                                            (12U)
#define DSP_IDMA0_MASK_M12_MASK                                                                             (0x00001000U)

#define DSP_IDMA0_MASK_M13_SHIFT                                                                            (13U)
#define DSP_IDMA0_MASK_M13_MASK                                                                             (0x00002000U)

#define DSP_IDMA0_MASK_M14_SHIFT                                                                            (14U)
#define DSP_IDMA0_MASK_M14_MASK                                                                             (0x00004000U)

#define DSP_IDMA0_MASK_M15_SHIFT                                                                            (15U)
#define DSP_IDMA0_MASK_M15_MASK                                                                             (0x00008000U)

#define DSP_IDMA0_MASK_M16_SHIFT                                                                            (16U)
#define DSP_IDMA0_MASK_M16_MASK                                                                             (0x00010000U)

#define DSP_IDMA0_MASK_M17_SHIFT                                                                            (17U)
#define DSP_IDMA0_MASK_M17_MASK                                                                             (0x00020000U)

#define DSP_IDMA0_MASK_M18_SHIFT                                                                            (18U)
#define DSP_IDMA0_MASK_M18_MASK                                                                             (0x00040000U)

#define DSP_IDMA0_MASK_M19_SHIFT                                                                            (19U)
#define DSP_IDMA0_MASK_M19_MASK                                                                             (0x00080000U)

#define DSP_IDMA0_MASK_M20_SHIFT                                                                            (20U)
#define DSP_IDMA0_MASK_M20_MASK                                                                             (0x00100000U)

#define DSP_IDMA0_MASK_M21_SHIFT                                                                            (21U)
#define DSP_IDMA0_MASK_M21_MASK                                                                             (0x00200000U)

#define DSP_IDMA0_MASK_M22_SHIFT                                                                            (22U)
#define DSP_IDMA0_MASK_M22_MASK                                                                             (0x00400000U)

#define DSP_IDMA0_MASK_M23_SHIFT                                                                            (23U)
#define DSP_IDMA0_MASK_M23_MASK                                                                             (0x00800000U)

#define DSP_IDMA0_MASK_M24_SHIFT                                                                            (24U)
#define DSP_IDMA0_MASK_M24_MASK                                                                             (0x01000000U)

#define DSP_IDMA0_MASK_M25_SHIFT                                                                            (25U)
#define DSP_IDMA0_MASK_M25_MASK                                                                             (0x02000000U)

#define DSP_IDMA0_MASK_M26_SHIFT                                                                            (26U)
#define DSP_IDMA0_MASK_M26_MASK                                                                             (0x04000000U)

#define DSP_IDMA0_MASK_M27_SHIFT                                                                            (27U)
#define DSP_IDMA0_MASK_M27_MASK                                                                             (0x08000000U)

#define DSP_IDMA0_MASK_M28_SHIFT                                                                            (28U)
#define DSP_IDMA0_MASK_M28_MASK                                                                             (0x10000000U)

#define DSP_IDMA0_MASK_M29_SHIFT                                                                            (29U)
#define DSP_IDMA0_MASK_M29_MASK                                                                             (0x20000000U)

#define DSP_IDMA0_MASK_M31_SHIFT                                                                            (31U)
#define DSP_IDMA0_MASK_M31_MASK                                                                             (0x80000000U)

#define DSP_IDMA0_MASK_M30_SHIFT                                                                            (30U)
#define DSP_IDMA0_MASK_M30_MASK                                                                             (0x40000000U)

#define DSP_IDMA0_SOURCE_SOURCEADDR_SHIFT                                                                   (5U)
#define DSP_IDMA0_SOURCE_SOURCEADDR_MASK                                                                    (0xffffffe0U)

#define DSP_IDMA0_SOURCE__RESV1_SHIFT                                                                       (0U)
#define DSP_IDMA0_SOURCE__RESV1_MASK                                                                        (0x0000001fU)

#define DSP_IDMA0_DEST_DESTADDR_SHIFT                                                                       (5U)
#define DSP_IDMA0_DEST_DESTADDR_MASK                                                                        (0xffffffe0U)

#define DSP_IDMA0_DEST__RESV1_SHIFT                                                                         (0U)
#define DSP_IDMA0_DEST__RESV1_MASK                                                                          (0x0000001fU)

#define DSP_IDMA0_COUNT__RESV1_SHIFT                                                                        (29U)
#define DSP_IDMA0_COUNT__RESV1_MASK                                                                         (0xe0000000U)

#define DSP_IDMA0_COUNT_INT_SHIFT                                                                           (28U)
#define DSP_IDMA0_COUNT_INT_MASK                                                                            (0x10000000U)

#define DSP_IDMA0_COUNT__RESV2_SHIFT                                                                        (4U)
#define DSP_IDMA0_COUNT__RESV2_MASK                                                                         (0x0ffffff0U)

#define DSP_IDMA0_COUNT_COUNT_SHIFT                                                                         (0U)
#define DSP_IDMA0_COUNT_COUNT_MASK                                                                          (0x0000000fU)

#define DSP_IDMA1_STAT__RESV1_SHIFT                                                                         (2U)
#define DSP_IDMA1_STAT__RESV1_MASK                                                                          (0xfffffffcU)

#define DSP_IDMA1_STAT_PEND_SHIFT                                                                           (1U)
#define DSP_IDMA1_STAT_PEND_MASK                                                                            (0x00000002U)

#define DSP_IDMA1_STAT_ACTV_SHIFT                                                                           (0U)
#define DSP_IDMA1_STAT_ACTV_MASK                                                                            (0x00000001U)

#define DSP_IDMA1_SOURCE_SOURCEADDR_SHIFT                                                                   (0U)
#define DSP_IDMA1_SOURCE_SOURCEADDR_MASK                                                                    (0xffffffffU)

#define DSP_IDMA1_DEST_DESTADDR_SHIFT                                                                       (2U)
#define DSP_IDMA1_DEST_DESTADDR_MASK                                                                        (0xfffffffcU)

#define DSP_IDMA1_DEST__RESV1_SHIFT                                                                         (0U)
#define DSP_IDMA1_DEST__RESV1_MASK                                                                          (0x00000003U)

#define DSP_IDMA1_COUNT_PRI_SHIFT                                                                           (29U)
#define DSP_IDMA1_COUNT_PRI_MASK                                                                            (0xe0000000U)

#define DSP_IDMA1_COUNT_INT_SHIFT                                                                           (28U)
#define DSP_IDMA1_COUNT_INT_MASK                                                                            (0x10000000U)

#define DSP_IDMA1_COUNT__RESV1_SHIFT                                                                        (17U)
#define DSP_IDMA1_COUNT__RESV1_MASK                                                                         (0x0ffe0000U)

#define DSP_IDMA1_COUNT_FILL_SHIFT                                                                          (16U)
#define DSP_IDMA1_COUNT_FILL_MASK                                                                           (0x00010000U)

#define DSP_IDMA1_COUNT_COUNT_SHIFT                                                                         (0U)
#define DSP_IDMA1_COUNT_COUNT_MASK                                                                          (0x0000ffffU)

#define DSP_EVTFLAG0_EF0_SHIFT                                                                              (0U)
#define DSP_EVTFLAG0_EF0_MASK                                                                               (0x00000001U)

#define DSP_EVTFLAG0_EF1_SHIFT                                                                              (1U)
#define DSP_EVTFLAG0_EF1_MASK                                                                               (0x00000002U)

#define DSP_EVTFLAG0_EF2_SHIFT                                                                              (2U)
#define DSP_EVTFLAG0_EF2_MASK                                                                               (0x00000004U)

#define DSP_EVTFLAG0_EF3_SHIFT                                                                              (3U)
#define DSP_EVTFLAG0_EF3_MASK                                                                               (0x00000008U)

#define DSP_EVTFLAG0_EF4_SHIFT                                                                              (4U)
#define DSP_EVTFLAG0_EF4_MASK                                                                               (0x00000010U)

#define DSP_EVTFLAG0_EF5_SHIFT                                                                              (5U)
#define DSP_EVTFLAG0_EF5_MASK                                                                               (0x00000020U)

#define DSP_EVTFLAG0_EF6_SHIFT                                                                              (6U)
#define DSP_EVTFLAG0_EF6_MASK                                                                               (0x00000040U)

#define DSP_EVTFLAG0_EF7_SHIFT                                                                              (7U)
#define DSP_EVTFLAG0_EF7_MASK                                                                               (0x00000080U)

#define DSP_EVTFLAG0_EF8_SHIFT                                                                              (8U)
#define DSP_EVTFLAG0_EF8_MASK                                                                               (0x00000100U)

#define DSP_EVTFLAG0_EF9_SHIFT                                                                              (9U)
#define DSP_EVTFLAG0_EF9_MASK                                                                               (0x00000200U)

#define DSP_EVTFLAG0_EF10_SHIFT                                                                             (10U)
#define DSP_EVTFLAG0_EF10_MASK                                                                              (0x00000400U)

#define DSP_EVTFLAG0_EF11_SHIFT                                                                             (11U)
#define DSP_EVTFLAG0_EF11_MASK                                                                              (0x00000800U)

#define DSP_EVTFLAG0_EF12_SHIFT                                                                             (12U)
#define DSP_EVTFLAG0_EF12_MASK                                                                              (0x00001000U)

#define DSP_EVTFLAG0_EF13_SHIFT                                                                             (13U)
#define DSP_EVTFLAG0_EF13_MASK                                                                              (0x00002000U)

#define DSP_EVTFLAG0_EF14_SHIFT                                                                             (14U)
#define DSP_EVTFLAG0_EF14_MASK                                                                              (0x00004000U)

#define DSP_EVTFLAG0_EF15_SHIFT                                                                             (15U)
#define DSP_EVTFLAG0_EF15_MASK                                                                              (0x00008000U)

#define DSP_EVTFLAG0_EF16_SHIFT                                                                             (16U)
#define DSP_EVTFLAG0_EF16_MASK                                                                              (0x00010000U)

#define DSP_EVTFLAG0_EF17_SHIFT                                                                             (17U)
#define DSP_EVTFLAG0_EF17_MASK                                                                              (0x00020000U)

#define DSP_EVTFLAG0_EF18_SHIFT                                                                             (18U)
#define DSP_EVTFLAG0_EF18_MASK                                                                              (0x00040000U)

#define DSP_EVTFLAG0_EF19_SHIFT                                                                             (19U)
#define DSP_EVTFLAG0_EF19_MASK                                                                              (0x00080000U)

#define DSP_EVTFLAG0_EF20_SHIFT                                                                             (20U)
#define DSP_EVTFLAG0_EF20_MASK                                                                              (0x00100000U)

#define DSP_EVTFLAG0_EF21_SHIFT                                                                             (21U)
#define DSP_EVTFLAG0_EF21_MASK                                                                              (0x00200000U)

#define DSP_EVTFLAG0_EF22_SHIFT                                                                             (22U)
#define DSP_EVTFLAG0_EF22_MASK                                                                              (0x00400000U)

#define DSP_EVTFLAG0_EF23_SHIFT                                                                             (23U)
#define DSP_EVTFLAG0_EF23_MASK                                                                              (0x00800000U)

#define DSP_EVTFLAG0_EF24_SHIFT                                                                             (24U)
#define DSP_EVTFLAG0_EF24_MASK                                                                              (0x01000000U)

#define DSP_EVTFLAG0_EF25_SHIFT                                                                             (25U)
#define DSP_EVTFLAG0_EF25_MASK                                                                              (0x02000000U)

#define DSP_EVTFLAG0_EF26_SHIFT                                                                             (26U)
#define DSP_EVTFLAG0_EF26_MASK                                                                              (0x04000000U)

#define DSP_EVTFLAG0_EF27_SHIFT                                                                             (27U)
#define DSP_EVTFLAG0_EF27_MASK                                                                              (0x08000000U)

#define DSP_EVTFLAG0_EF28_SHIFT                                                                             (28U)
#define DSP_EVTFLAG0_EF28_MASK                                                                              (0x10000000U)

#define DSP_EVTFLAG0_EF29_SHIFT                                                                             (29U)
#define DSP_EVTFLAG0_EF29_MASK                                                                              (0x20000000U)

#define DSP_EVTFLAG0_EF31_SHIFT                                                                             (31U)
#define DSP_EVTFLAG0_EF31_MASK                                                                              (0x80000000U)

#define DSP_EVTFLAG0_EF30_SHIFT                                                                             (30U)
#define DSP_EVTFLAG0_EF30_MASK                                                                              (0x40000000U)

#define DSP_EVTSET0_ES0_SHIFT                                                                               (0U)
#define DSP_EVTSET0_ES0_MASK                                                                                (0x00000001U)

#define DSP_EVTSET0_ES1_SHIFT                                                                               (1U)
#define DSP_EVTSET0_ES1_MASK                                                                                (0x00000002U)

#define DSP_EVTSET0_ES2_SHIFT                                                                               (2U)
#define DSP_EVTSET0_ES2_MASK                                                                                (0x00000004U)

#define DSP_EVTSET0_ES3_SHIFT                                                                               (3U)
#define DSP_EVTSET0_ES3_MASK                                                                                (0x00000008U)

#define DSP_EVTSET0_ES4_SHIFT                                                                               (4U)
#define DSP_EVTSET0_ES4_MASK                                                                                (0x00000010U)

#define DSP_EVTSET0_ES5_SHIFT                                                                               (5U)
#define DSP_EVTSET0_ES5_MASK                                                                                (0x00000020U)

#define DSP_EVTSET0_ES6_SHIFT                                                                               (6U)
#define DSP_EVTSET0_ES6_MASK                                                                                (0x00000040U)

#define DSP_EVTSET0_ES7_SHIFT                                                                               (7U)
#define DSP_EVTSET0_ES7_MASK                                                                                (0x00000080U)

#define DSP_EVTSET0_ES8_SHIFT                                                                               (8U)
#define DSP_EVTSET0_ES8_MASK                                                                                (0x00000100U)

#define DSP_EVTSET0_ES9_SHIFT                                                                               (9U)
#define DSP_EVTSET0_ES9_MASK                                                                                (0x00000200U)

#define DSP_EVTSET0_ES10_SHIFT                                                                              (10U)
#define DSP_EVTSET0_ES10_MASK                                                                               (0x00000400U)

#define DSP_EVTSET0_ES11_SHIFT                                                                              (11U)
#define DSP_EVTSET0_ES11_MASK                                                                               (0x00000800U)

#define DSP_EVTSET0_ES12_SHIFT                                                                              (12U)
#define DSP_EVTSET0_ES12_MASK                                                                               (0x00001000U)

#define DSP_EVTSET0_ES13_SHIFT                                                                              (13U)
#define DSP_EVTSET0_ES13_MASK                                                                               (0x00002000U)

#define DSP_EVTSET0_ES14_SHIFT                                                                              (14U)
#define DSP_EVTSET0_ES14_MASK                                                                               (0x00004000U)

#define DSP_EVTSET0_ES15_SHIFT                                                                              (15U)
#define DSP_EVTSET0_ES15_MASK                                                                               (0x00008000U)

#define DSP_EVTSET0_ES16_SHIFT                                                                              (16U)
#define DSP_EVTSET0_ES16_MASK                                                                               (0x00010000U)

#define DSP_EVTSET0_ES17_SHIFT                                                                              (17U)
#define DSP_EVTSET0_ES17_MASK                                                                               (0x00020000U)

#define DSP_EVTSET0_ES18_SHIFT                                                                              (18U)
#define DSP_EVTSET0_ES18_MASK                                                                               (0x00040000U)

#define DSP_EVTSET0_ES19_SHIFT                                                                              (19U)
#define DSP_EVTSET0_ES19_MASK                                                                               (0x00080000U)

#define DSP_EVTSET0_ES20_SHIFT                                                                              (20U)
#define DSP_EVTSET0_ES20_MASK                                                                               (0x00100000U)

#define DSP_EVTSET0_ES21_SHIFT                                                                              (21U)
#define DSP_EVTSET0_ES21_MASK                                                                               (0x00200000U)

#define DSP_EVTSET0_ES22_SHIFT                                                                              (22U)
#define DSP_EVTSET0_ES22_MASK                                                                               (0x00400000U)

#define DSP_EVTSET0_ES23_SHIFT                                                                              (23U)
#define DSP_EVTSET0_ES23_MASK                                                                               (0x00800000U)

#define DSP_EVTSET0_ES24_SHIFT                                                                              (24U)
#define DSP_EVTSET0_ES24_MASK                                                                               (0x01000000U)

#define DSP_EVTSET0_ES25_SHIFT                                                                              (25U)
#define DSP_EVTSET0_ES25_MASK                                                                               (0x02000000U)

#define DSP_EVTSET0_ES26_SHIFT                                                                              (26U)
#define DSP_EVTSET0_ES26_MASK                                                                               (0x04000000U)

#define DSP_EVTSET0_ES27_SHIFT                                                                              (27U)
#define DSP_EVTSET0_ES27_MASK                                                                               (0x08000000U)

#define DSP_EVTSET0_ES28_SHIFT                                                                              (28U)
#define DSP_EVTSET0_ES28_MASK                                                                               (0x10000000U)

#define DSP_EVTSET0_ES29_SHIFT                                                                              (29U)
#define DSP_EVTSET0_ES29_MASK                                                                               (0x20000000U)

#define DSP_EVTSET0_ES31_SHIFT                                                                              (31U)
#define DSP_EVTSET0_ES31_MASK                                                                               (0x80000000U)

#define DSP_EVTSET0_ES30_SHIFT                                                                              (30U)
#define DSP_EVTSET0_ES30_MASK                                                                               (0x40000000U)

#define DSP_EVTCLR0_EC0_SHIFT                                                                               (0U)
#define DSP_EVTCLR0_EC0_MASK                                                                                (0x00000001U)

#define DSP_EVTCLR0_EC1_SHIFT                                                                               (1U)
#define DSP_EVTCLR0_EC1_MASK                                                                                (0x00000002U)

#define DSP_EVTCLR0_EC2_SHIFT                                                                               (2U)
#define DSP_EVTCLR0_EC2_MASK                                                                                (0x00000004U)

#define DSP_EVTCLR0_EC3_SHIFT                                                                               (3U)
#define DSP_EVTCLR0_EC3_MASK                                                                                (0x00000008U)

#define DSP_EVTCLR0_EC4_SHIFT                                                                               (4U)
#define DSP_EVTCLR0_EC4_MASK                                                                                (0x00000010U)

#define DSP_EVTCLR0_EC5_SHIFT                                                                               (5U)
#define DSP_EVTCLR0_EC5_MASK                                                                                (0x00000020U)

#define DSP_EVTCLR0_EC6_SHIFT                                                                               (6U)
#define DSP_EVTCLR0_EC6_MASK                                                                                (0x00000040U)

#define DSP_EVTCLR0_EC7_SHIFT                                                                               (7U)
#define DSP_EVTCLR0_EC7_MASK                                                                                (0x00000080U)

#define DSP_EVTCLR0_EC8_SHIFT                                                                               (8U)
#define DSP_EVTCLR0_EC8_MASK                                                                                (0x00000100U)

#define DSP_EVTCLR0_EC9_SHIFT                                                                               (9U)
#define DSP_EVTCLR0_EC9_MASK                                                                                (0x00000200U)

#define DSP_EVTCLR0_EC10_SHIFT                                                                              (10U)
#define DSP_EVTCLR0_EC10_MASK                                                                               (0x00000400U)

#define DSP_EVTCLR0_EC11_SHIFT                                                                              (11U)
#define DSP_EVTCLR0_EC11_MASK                                                                               (0x00000800U)

#define DSP_EVTCLR0_EC12_SHIFT                                                                              (12U)
#define DSP_EVTCLR0_EC12_MASK                                                                               (0x00001000U)

#define DSP_EVTCLR0_EC13_SHIFT                                                                              (13U)
#define DSP_EVTCLR0_EC13_MASK                                                                               (0x00002000U)

#define DSP_EVTCLR0_EC14_SHIFT                                                                              (14U)
#define DSP_EVTCLR0_EC14_MASK                                                                               (0x00004000U)

#define DSP_EVTCLR0_EC15_SHIFT                                                                              (15U)
#define DSP_EVTCLR0_EC15_MASK                                                                               (0x00008000U)

#define DSP_EVTCLR0_EC16_SHIFT                                                                              (16U)
#define DSP_EVTCLR0_EC16_MASK                                                                               (0x00010000U)

#define DSP_EVTCLR0_EC17_SHIFT                                                                              (17U)
#define DSP_EVTCLR0_EC17_MASK                                                                               (0x00020000U)

#define DSP_EVTCLR0_EC18_SHIFT                                                                              (18U)
#define DSP_EVTCLR0_EC18_MASK                                                                               (0x00040000U)

#define DSP_EVTCLR0_EC19_SHIFT                                                                              (19U)
#define DSP_EVTCLR0_EC19_MASK                                                                               (0x00080000U)

#define DSP_EVTCLR0_EC20_SHIFT                                                                              (20U)
#define DSP_EVTCLR0_EC20_MASK                                                                               (0x00100000U)

#define DSP_EVTCLR0_EC21_SHIFT                                                                              (21U)
#define DSP_EVTCLR0_EC21_MASK                                                                               (0x00200000U)

#define DSP_EVTCLR0_EC22_SHIFT                                                                              (22U)
#define DSP_EVTCLR0_EC22_MASK                                                                               (0x00400000U)

#define DSP_EVTCLR0_EC23_SHIFT                                                                              (23U)
#define DSP_EVTCLR0_EC23_MASK                                                                               (0x00800000U)

#define DSP_EVTCLR0_EC24_SHIFT                                                                              (24U)
#define DSP_EVTCLR0_EC24_MASK                                                                               (0x01000000U)

#define DSP_EVTCLR0_EC25_SHIFT                                                                              (25U)
#define DSP_EVTCLR0_EC25_MASK                                                                               (0x02000000U)

#define DSP_EVTCLR0_EC26_SHIFT                                                                              (26U)
#define DSP_EVTCLR0_EC26_MASK                                                                               (0x04000000U)

#define DSP_EVTCLR0_EC27_SHIFT                                                                              (27U)
#define DSP_EVTCLR0_EC27_MASK                                                                               (0x08000000U)

#define DSP_EVTCLR0_EC28_SHIFT                                                                              (28U)
#define DSP_EVTCLR0_EC28_MASK                                                                               (0x10000000U)

#define DSP_EVTCLR0_EC29_SHIFT                                                                              (29U)
#define DSP_EVTCLR0_EC29_MASK                                                                               (0x20000000U)

#define DSP_EVTCLR0_EC31_SHIFT                                                                              (31U)
#define DSP_EVTCLR0_EC31_MASK                                                                               (0x80000000U)

#define DSP_EVTCLR0_EC30_SHIFT                                                                              (30U)
#define DSP_EVTCLR0_EC30_MASK                                                                               (0x40000000U)

#define DSP_EVTMASK0_EM0_SHIFT                                                                              (0U)
#define DSP_EVTMASK0_EM0_MASK                                                                               (0x00000001U)

#define DSP_EVTMASK0_EM1_SHIFT                                                                              (1U)
#define DSP_EVTMASK0_EM1_MASK                                                                               (0x00000002U)

#define DSP_EVTMASK0_EM2_SHIFT                                                                              (2U)
#define DSP_EVTMASK0_EM2_MASK                                                                               (0x00000004U)

#define DSP_EVTMASK0_EM3_SHIFT                                                                              (3U)
#define DSP_EVTMASK0_EM3_MASK                                                                               (0x00000008U)

#define DSP_EVTMASK0_EM4_SHIFT                                                                              (4U)
#define DSP_EVTMASK0_EM4_MASK                                                                               (0x00000010U)

#define DSP_EVTMASK0_EM5_SHIFT                                                                              (5U)
#define DSP_EVTMASK0_EM5_MASK                                                                               (0x00000020U)

#define DSP_EVTMASK0_EM6_SHIFT                                                                              (6U)
#define DSP_EVTMASK0_EM6_MASK                                                                               (0x00000040U)

#define DSP_EVTMASK0_EM7_SHIFT                                                                              (7U)
#define DSP_EVTMASK0_EM7_MASK                                                                               (0x00000080U)

#define DSP_EVTMASK0_EM8_SHIFT                                                                              (8U)
#define DSP_EVTMASK0_EM8_MASK                                                                               (0x00000100U)

#define DSP_EVTMASK0_EM9_SHIFT                                                                              (9U)
#define DSP_EVTMASK0_EM9_MASK                                                                               (0x00000200U)

#define DSP_EVTMASK0_EM10_SHIFT                                                                             (10U)
#define DSP_EVTMASK0_EM10_MASK                                                                              (0x00000400U)

#define DSP_EVTMASK0_EM11_SHIFT                                                                             (11U)
#define DSP_EVTMASK0_EM11_MASK                                                                              (0x00000800U)

#define DSP_EVTMASK0_EM12_SHIFT                                                                             (12U)
#define DSP_EVTMASK0_EM12_MASK                                                                              (0x00001000U)

#define DSP_EVTMASK0_EM13_SHIFT                                                                             (13U)
#define DSP_EVTMASK0_EM13_MASK                                                                              (0x00002000U)

#define DSP_EVTMASK0_EM14_SHIFT                                                                             (14U)
#define DSP_EVTMASK0_EM14_MASK                                                                              (0x00004000U)

#define DSP_EVTMASK0_EM15_SHIFT                                                                             (15U)
#define DSP_EVTMASK0_EM15_MASK                                                                              (0x00008000U)

#define DSP_EVTMASK0_EM16_SHIFT                                                                             (16U)
#define DSP_EVTMASK0_EM16_MASK                                                                              (0x00010000U)

#define DSP_EVTMASK0_EM17_SHIFT                                                                             (17U)
#define DSP_EVTMASK0_EM17_MASK                                                                              (0x00020000U)

#define DSP_EVTMASK0_EM18_SHIFT                                                                             (18U)
#define DSP_EVTMASK0_EM18_MASK                                                                              (0x00040000U)

#define DSP_EVTMASK0_EM19_SHIFT                                                                             (19U)
#define DSP_EVTMASK0_EM19_MASK                                                                              (0x00080000U)

#define DSP_EVTMASK0_EM20_SHIFT                                                                             (20U)
#define DSP_EVTMASK0_EM20_MASK                                                                              (0x00100000U)

#define DSP_EVTMASK0_EM21_SHIFT                                                                             (21U)
#define DSP_EVTMASK0_EM21_MASK                                                                              (0x00200000U)

#define DSP_EVTMASK0_EM22_SHIFT                                                                             (22U)
#define DSP_EVTMASK0_EM22_MASK                                                                              (0x00400000U)

#define DSP_EVTMASK0_EM23_SHIFT                                                                             (23U)
#define DSP_EVTMASK0_EM23_MASK                                                                              (0x00800000U)

#define DSP_EVTMASK0_EM24_SHIFT                                                                             (24U)
#define DSP_EVTMASK0_EM24_MASK                                                                              (0x01000000U)

#define DSP_EVTMASK0_EM25_SHIFT                                                                             (25U)
#define DSP_EVTMASK0_EM25_MASK                                                                              (0x02000000U)

#define DSP_EVTMASK0_EM26_SHIFT                                                                             (26U)
#define DSP_EVTMASK0_EM26_MASK                                                                              (0x04000000U)

#define DSP_EVTMASK0_EM27_SHIFT                                                                             (27U)
#define DSP_EVTMASK0_EM27_MASK                                                                              (0x08000000U)

#define DSP_EVTMASK0_EM28_SHIFT                                                                             (28U)
#define DSP_EVTMASK0_EM28_MASK                                                                              (0x10000000U)

#define DSP_EVTMASK0_EM29_SHIFT                                                                             (29U)
#define DSP_EVTMASK0_EM29_MASK                                                                              (0x20000000U)

#define DSP_EVTMASK0_EM31_SHIFT                                                                             (31U)
#define DSP_EVTMASK0_EM31_MASK                                                                              (0x80000000U)

#define DSP_EVTMASK0_EM30_SHIFT                                                                             (30U)
#define DSP_EVTMASK0_EM30_MASK                                                                              (0x40000000U)

#define DSP_EXPMASK0_XM0_SHIFT                                                                              (0U)
#define DSP_EXPMASK0_XM0_MASK                                                                               (0x00000001U)

#define DSP_EXPMASK0_XM1_SHIFT                                                                              (1U)
#define DSP_EXPMASK0_XM1_MASK                                                                               (0x00000002U)

#define DSP_EXPMASK0_XM2_SHIFT                                                                              (2U)
#define DSP_EXPMASK0_XM2_MASK                                                                               (0x00000004U)

#define DSP_EXPMASK0_XM3_SHIFT                                                                              (3U)
#define DSP_EXPMASK0_XM3_MASK                                                                               (0x00000008U)

#define DSP_EXPMASK0_XM4_SHIFT                                                                              (4U)
#define DSP_EXPMASK0_XM4_MASK                                                                               (0x00000010U)

#define DSP_EXPMASK0_XM5_SHIFT                                                                              (5U)
#define DSP_EXPMASK0_XM5_MASK                                                                               (0x00000020U)

#define DSP_EXPMASK0_XM6_SHIFT                                                                              (6U)
#define DSP_EXPMASK0_XM6_MASK                                                                               (0x00000040U)

#define DSP_EXPMASK0_XM7_SHIFT                                                                              (7U)
#define DSP_EXPMASK0_XM7_MASK                                                                               (0x00000080U)

#define DSP_EXPMASK0_XM8_SHIFT                                                                              (8U)
#define DSP_EXPMASK0_XM8_MASK                                                                               (0x00000100U)

#define DSP_EXPMASK0_XM9_SHIFT                                                                              (9U)
#define DSP_EXPMASK0_XM9_MASK                                                                               (0x00000200U)

#define DSP_EXPMASK0_XM10_SHIFT                                                                             (10U)
#define DSP_EXPMASK0_XM10_MASK                                                                              (0x00000400U)

#define DSP_EXPMASK0_XM11_SHIFT                                                                             (11U)
#define DSP_EXPMASK0_XM11_MASK                                                                              (0x00000800U)

#define DSP_EXPMASK0_XM12_SHIFT                                                                             (12U)
#define DSP_EXPMASK0_XM12_MASK                                                                              (0x00001000U)

#define DSP_EXPMASK0_XM13_SHIFT                                                                             (13U)
#define DSP_EXPMASK0_XM13_MASK                                                                              (0x00002000U)

#define DSP_EXPMASK0_XM14_SHIFT                                                                             (14U)
#define DSP_EXPMASK0_XM14_MASK                                                                              (0x00004000U)

#define DSP_EXPMASK0_XM15_SHIFT                                                                             (15U)
#define DSP_EXPMASK0_XM15_MASK                                                                              (0x00008000U)

#define DSP_EXPMASK0_XM16_SHIFT                                                                             (16U)
#define DSP_EXPMASK0_XM16_MASK                                                                              (0x00010000U)

#define DSP_EXPMASK0_XM17_SHIFT                                                                             (17U)
#define DSP_EXPMASK0_XM17_MASK                                                                              (0x00020000U)

#define DSP_EXPMASK0_XM18_SHIFT                                                                             (18U)
#define DSP_EXPMASK0_XM18_MASK                                                                              (0x00040000U)

#define DSP_EXPMASK0_XM19_SHIFT                                                                             (19U)
#define DSP_EXPMASK0_XM19_MASK                                                                              (0x00080000U)

#define DSP_EXPMASK0_XM20_SHIFT                                                                             (20U)
#define DSP_EXPMASK0_XM20_MASK                                                                              (0x00100000U)

#define DSP_EXPMASK0_XM21_SHIFT                                                                             (21U)
#define DSP_EXPMASK0_XM21_MASK                                                                              (0x00200000U)

#define DSP_EXPMASK0_XM22_SHIFT                                                                             (22U)
#define DSP_EXPMASK0_XM22_MASK                                                                              (0x00400000U)

#define DSP_EXPMASK0_XM23_SHIFT                                                                             (23U)
#define DSP_EXPMASK0_XM23_MASK                                                                              (0x00800000U)

#define DSP_EXPMASK0_XM24_SHIFT                                                                             (24U)
#define DSP_EXPMASK0_XM24_MASK                                                                              (0x01000000U)

#define DSP_EXPMASK0_XM25_SHIFT                                                                             (25U)
#define DSP_EXPMASK0_XM25_MASK                                                                              (0x02000000U)

#define DSP_EXPMASK0_XM26_SHIFT                                                                             (26U)
#define DSP_EXPMASK0_XM26_MASK                                                                              (0x04000000U)

#define DSP_EXPMASK0_XM27_SHIFT                                                                             (27U)
#define DSP_EXPMASK0_XM27_MASK                                                                              (0x08000000U)

#define DSP_EXPMASK0_XM28_SHIFT                                                                             (28U)
#define DSP_EXPMASK0_XM28_MASK                                                                              (0x10000000U)

#define DSP_EXPMASK0_XM29_SHIFT                                                                             (29U)
#define DSP_EXPMASK0_XM29_MASK                                                                              (0x20000000U)

#define DSP_EXPMASK0_XM31_SHIFT                                                                             (31U)
#define DSP_EXPMASK0_XM31_MASK                                                                              (0x80000000U)

#define DSP_EXPMASK0_XM30_SHIFT                                                                             (30U)
#define DSP_EXPMASK0_XM30_MASK                                                                              (0x40000000U)

#define DSP_MEVTFLAG0_MEF0_SHIFT                                                                            (0U)
#define DSP_MEVTFLAG0_MEF0_MASK                                                                             (0x00000001U)

#define DSP_MEVTFLAG0_MEF1_SHIFT                                                                            (1U)
#define DSP_MEVTFLAG0_MEF1_MASK                                                                             (0x00000002U)

#define DSP_MEVTFLAG0_MEF2_SHIFT                                                                            (2U)
#define DSP_MEVTFLAG0_MEF2_MASK                                                                             (0x00000004U)

#define DSP_MEVTFLAG0_MEF3_SHIFT                                                                            (3U)
#define DSP_MEVTFLAG0_MEF3_MASK                                                                             (0x00000008U)

#define DSP_MEVTFLAG0_MEF4_SHIFT                                                                            (4U)
#define DSP_MEVTFLAG0_MEF4_MASK                                                                             (0x00000010U)

#define DSP_MEVTFLAG0_MEF5_SHIFT                                                                            (5U)
#define DSP_MEVTFLAG0_MEF5_MASK                                                                             (0x00000020U)

#define DSP_MEVTFLAG0_MEF6_SHIFT                                                                            (6U)
#define DSP_MEVTFLAG0_MEF6_MASK                                                                             (0x00000040U)

#define DSP_MEVTFLAG0_MEF7_SHIFT                                                                            (7U)
#define DSP_MEVTFLAG0_MEF7_MASK                                                                             (0x00000080U)

#define DSP_MEVTFLAG0_MEF8_SHIFT                                                                            (8U)
#define DSP_MEVTFLAG0_MEF8_MASK                                                                             (0x00000100U)

#define DSP_MEVTFLAG0_MEF9_SHIFT                                                                            (9U)
#define DSP_MEVTFLAG0_MEF9_MASK                                                                             (0x00000200U)

#define DSP_MEVTFLAG0_MEF10_SHIFT                                                                           (10U)
#define DSP_MEVTFLAG0_MEF10_MASK                                                                            (0x00000400U)

#define DSP_MEVTFLAG0_MEF11_SHIFT                                                                           (11U)
#define DSP_MEVTFLAG0_MEF11_MASK                                                                            (0x00000800U)

#define DSP_MEVTFLAG0_MEF12_SHIFT                                                                           (12U)
#define DSP_MEVTFLAG0_MEF12_MASK                                                                            (0x00001000U)

#define DSP_MEVTFLAG0_MEF13_SHIFT                                                                           (13U)
#define DSP_MEVTFLAG0_MEF13_MASK                                                                            (0x00002000U)

#define DSP_MEVTFLAG0_MEF14_SHIFT                                                                           (14U)
#define DSP_MEVTFLAG0_MEF14_MASK                                                                            (0x00004000U)

#define DSP_MEVTFLAG0_MEF15_SHIFT                                                                           (15U)
#define DSP_MEVTFLAG0_MEF15_MASK                                                                            (0x00008000U)

#define DSP_MEVTFLAG0_MEF16_SHIFT                                                                           (16U)
#define DSP_MEVTFLAG0_MEF16_MASK                                                                            (0x00010000U)

#define DSP_MEVTFLAG0_MEF17_SHIFT                                                                           (17U)
#define DSP_MEVTFLAG0_MEF17_MASK                                                                            (0x00020000U)

#define DSP_MEVTFLAG0_MEF18_SHIFT                                                                           (18U)
#define DSP_MEVTFLAG0_MEF18_MASK                                                                            (0x00040000U)

#define DSP_MEVTFLAG0_MEF19_SHIFT                                                                           (19U)
#define DSP_MEVTFLAG0_MEF19_MASK                                                                            (0x00080000U)

#define DSP_MEVTFLAG0_MEF20_SHIFT                                                                           (20U)
#define DSP_MEVTFLAG0_MEF20_MASK                                                                            (0x00100000U)

#define DSP_MEVTFLAG0_MEF21_SHIFT                                                                           (21U)
#define DSP_MEVTFLAG0_MEF21_MASK                                                                            (0x00200000U)

#define DSP_MEVTFLAG0_MEF22_SHIFT                                                                           (22U)
#define DSP_MEVTFLAG0_MEF22_MASK                                                                            (0x00400000U)

#define DSP_MEVTFLAG0_MEF23_SHIFT                                                                           (23U)
#define DSP_MEVTFLAG0_MEF23_MASK                                                                            (0x00800000U)

#define DSP_MEVTFLAG0_MEF24_SHIFT                                                                           (24U)
#define DSP_MEVTFLAG0_MEF24_MASK                                                                            (0x01000000U)

#define DSP_MEVTFLAG0_MEF25_SHIFT                                                                           (25U)
#define DSP_MEVTFLAG0_MEF25_MASK                                                                            (0x02000000U)

#define DSP_MEVTFLAG0_MEF26_SHIFT                                                                           (26U)
#define DSP_MEVTFLAG0_MEF26_MASK                                                                            (0x04000000U)

#define DSP_MEVTFLAG0_MEF27_SHIFT                                                                           (27U)
#define DSP_MEVTFLAG0_MEF27_MASK                                                                            (0x08000000U)

#define DSP_MEVTFLAG0_MEF28_SHIFT                                                                           (28U)
#define DSP_MEVTFLAG0_MEF28_MASK                                                                            (0x10000000U)

#define DSP_MEVTFLAG0_MEF29_SHIFT                                                                           (29U)
#define DSP_MEVTFLAG0_MEF29_MASK                                                                            (0x20000000U)

#define DSP_MEVTFLAG0_MEF31_SHIFT                                                                           (31U)
#define DSP_MEVTFLAG0_MEF31_MASK                                                                            (0x80000000U)

#define DSP_MEVTFLAG0_MEF30_SHIFT                                                                           (30U)
#define DSP_MEVTFLAG0_MEF30_MASK                                                                            (0x40000000U)

#define DSP_MEXPFLAG0_MXF0_SHIFT                                                                            (0U)
#define DSP_MEXPFLAG0_MXF0_MASK                                                                             (0x00000001U)

#define DSP_MEXPFLAG0_MXF1_SHIFT                                                                            (1U)
#define DSP_MEXPFLAG0_MXF1_MASK                                                                             (0x00000002U)

#define DSP_MEXPFLAG0_MXF2_SHIFT                                                                            (2U)
#define DSP_MEXPFLAG0_MXF2_MASK                                                                             (0x00000004U)

#define DSP_MEXPFLAG0_MXF3_SHIFT                                                                            (3U)
#define DSP_MEXPFLAG0_MXF3_MASK                                                                             (0x00000008U)

#define DSP_MEXPFLAG0_MXF4_SHIFT                                                                            (4U)
#define DSP_MEXPFLAG0_MXF4_MASK                                                                             (0x00000010U)

#define DSP_MEXPFLAG0_MXF5_SHIFT                                                                            (5U)
#define DSP_MEXPFLAG0_MXF5_MASK                                                                             (0x00000020U)

#define DSP_MEXPFLAG0_MXF6_SHIFT                                                                            (6U)
#define DSP_MEXPFLAG0_MXF6_MASK                                                                             (0x00000040U)

#define DSP_MEXPFLAG0_MXF7_SHIFT                                                                            (7U)
#define DSP_MEXPFLAG0_MXF7_MASK                                                                             (0x00000080U)

#define DSP_MEXPFLAG0_MXF8_SHIFT                                                                            (8U)
#define DSP_MEXPFLAG0_MXF8_MASK                                                                             (0x00000100U)

#define DSP_MEXPFLAG0_MXF9_SHIFT                                                                            (9U)
#define DSP_MEXPFLAG0_MXF9_MASK                                                                             (0x00000200U)

#define DSP_MEXPFLAG0_MXF10_SHIFT                                                                           (10U)
#define DSP_MEXPFLAG0_MXF10_MASK                                                                            (0x00000400U)

#define DSP_MEXPFLAG0_MXF11_SHIFT                                                                           (11U)
#define DSP_MEXPFLAG0_MXF11_MASK                                                                            (0x00000800U)

#define DSP_MEXPFLAG0_MXF12_SHIFT                                                                           (12U)
#define DSP_MEXPFLAG0_MXF12_MASK                                                                            (0x00001000U)

#define DSP_MEXPFLAG0_MXF13_SHIFT                                                                           (13U)
#define DSP_MEXPFLAG0_MXF13_MASK                                                                            (0x00002000U)

#define DSP_MEXPFLAG0_MXF14_SHIFT                                                                           (14U)
#define DSP_MEXPFLAG0_MXF14_MASK                                                                            (0x00004000U)

#define DSP_MEXPFLAG0_MXF15_SHIFT                                                                           (15U)
#define DSP_MEXPFLAG0_MXF15_MASK                                                                            (0x00008000U)

#define DSP_MEXPFLAG0_MXF16_SHIFT                                                                           (16U)
#define DSP_MEXPFLAG0_MXF16_MASK                                                                            (0x00010000U)

#define DSP_MEXPFLAG0_MXF17_SHIFT                                                                           (17U)
#define DSP_MEXPFLAG0_MXF17_MASK                                                                            (0x00020000U)

#define DSP_MEXPFLAG0_MXF18_SHIFT                                                                           (18U)
#define DSP_MEXPFLAG0_MXF18_MASK                                                                            (0x00040000U)

#define DSP_MEXPFLAG0_MXF19_SHIFT                                                                           (19U)
#define DSP_MEXPFLAG0_MXF19_MASK                                                                            (0x00080000U)

#define DSP_MEXPFLAG0_MXF20_SHIFT                                                                           (20U)
#define DSP_MEXPFLAG0_MXF20_MASK                                                                            (0x00100000U)

#define DSP_MEXPFLAG0_MXF21_SHIFT                                                                           (21U)
#define DSP_MEXPFLAG0_MXF21_MASK                                                                            (0x00200000U)

#define DSP_MEXPFLAG0_MXF22_SHIFT                                                                           (22U)
#define DSP_MEXPFLAG0_MXF22_MASK                                                                            (0x00400000U)

#define DSP_MEXPFLAG0_MXF23_SHIFT                                                                           (23U)
#define DSP_MEXPFLAG0_MXF23_MASK                                                                            (0x00800000U)

#define DSP_MEXPFLAG0_MXF24_SHIFT                                                                           (24U)
#define DSP_MEXPFLAG0_MXF24_MASK                                                                            (0x01000000U)

#define DSP_MEXPFLAG0_MXF25_SHIFT                                                                           (25U)
#define DSP_MEXPFLAG0_MXF25_MASK                                                                            (0x02000000U)

#define DSP_MEXPFLAG0_MXF26_SHIFT                                                                           (26U)
#define DSP_MEXPFLAG0_MXF26_MASK                                                                            (0x04000000U)

#define DSP_MEXPFLAG0_MXF27_SHIFT                                                                           (27U)
#define DSP_MEXPFLAG0_MXF27_MASK                                                                            (0x08000000U)

#define DSP_MEXPFLAG0_MXF28_SHIFT                                                                           (28U)
#define DSP_MEXPFLAG0_MXF28_MASK                                                                            (0x10000000U)

#define DSP_MEXPFLAG0_MXF29_SHIFT                                                                           (29U)
#define DSP_MEXPFLAG0_MXF29_MASK                                                                            (0x20000000U)

#define DSP_MEXPFLAG0_MXF31_SHIFT                                                                           (31U)
#define DSP_MEXPFLAG0_MXF31_MASK                                                                            (0x80000000U)

#define DSP_MEXPFLAG0_MXF30_SHIFT                                                                           (30U)
#define DSP_MEXPFLAG0_MXF30_MASK                                                                            (0x40000000U)

#define DSP_INTMUX3__RESV3_SHIFT                                                                            (31U)
#define DSP_INTMUX3__RESV3_MASK                                                                             (0x80000000U)

#define DSP_INTMUX3__RESV2_SHIFT                                                                            (23U)
#define DSP_INTMUX3__RESV2_MASK                                                                             (0x00800000U)

#define DSP_INTMUX3__RESV1_SHIFT                                                                            (15U)
#define DSP_INTMUX3__RESV1_MASK                                                                             (0x00008000U)

#define DSP_INTMUX3__RESV0_SHIFT                                                                            (7U)
#define DSP_INTMUX3__RESV0_MASK                                                                             (0x00000080U)

#define DSP_INTMUX3_INTSEL15_SHIFT                                                                          (24U)
#define DSP_INTMUX3_INTSEL15_MASK                                                                           (0x7f000000U)

#define DSP_INTMUX3_INTSEL14_SHIFT                                                                          (16U)
#define DSP_INTMUX3_INTSEL14_MASK                                                                           (0x007f0000U)

#define DSP_INTMUX3_INTSEL13_SHIFT                                                                          (8U)
#define DSP_INTMUX3_INTSEL13_MASK                                                                           (0x00007f00U)

#define DSP_INTMUX3_INTSEL12_SHIFT                                                                          (0U)
#define DSP_INTMUX3_INTSEL12_MASK                                                                           (0x0000007fU)

#define DSP_INTMUX2__RESV3_SHIFT                                                                            (31U)
#define DSP_INTMUX2__RESV3_MASK                                                                             (0x80000000U)

#define DSP_INTMUX2__RESV2_SHIFT                                                                            (23U)
#define DSP_INTMUX2__RESV2_MASK                                                                             (0x00800000U)

#define DSP_INTMUX2__RESV1_SHIFT                                                                            (15U)
#define DSP_INTMUX2__RESV1_MASK                                                                             (0x00008000U)

#define DSP_INTMUX2__RESV0_SHIFT                                                                            (7U)
#define DSP_INTMUX2__RESV0_MASK                                                                             (0x00000080U)

#define DSP_INTMUX2_INTSEL11_SHIFT                                                                          (24U)
#define DSP_INTMUX2_INTSEL11_MASK                                                                           (0x7f000000U)

#define DSP_INTMUX2_INTSEL10_SHIFT                                                                          (16U)
#define DSP_INTMUX2_INTSEL10_MASK                                                                           (0x007f0000U)

#define DSP_INTMUX2_INTSEL9_SHIFT                                                                           (8U)
#define DSP_INTMUX2_INTSEL9_MASK                                                                            (0x00007f00U)

#define DSP_INTMUX2_INTSEL8_SHIFT                                                                           (0U)
#define DSP_INTMUX2_INTSEL8_MASK                                                                            (0x0000007fU)

#define DSP_INTMUX1__RESV3_SHIFT                                                                            (31U)
#define DSP_INTMUX1__RESV3_MASK                                                                             (0x80000000U)

#define DSP_INTMUX1__RESV2_SHIFT                                                                            (23U)
#define DSP_INTMUX1__RESV2_MASK                                                                             (0x00800000U)

#define DSP_INTMUX1__RESV1_SHIFT                                                                            (15U)
#define DSP_INTMUX1__RESV1_MASK                                                                             (0x00008000U)

#define DSP_INTMUX1__RESV0_SHIFT                                                                            (7U)
#define DSP_INTMUX1__RESV0_MASK                                                                             (0x00000080U)

#define DSP_INTMUX1_INTSEL7_SHIFT                                                                           (24U)
#define DSP_INTMUX1_INTSEL7_MASK                                                                            (0x7f000000U)

#define DSP_INTMUX1_INTSEL6_SHIFT                                                                           (16U)
#define DSP_INTMUX1_INTSEL6_MASK                                                                            (0x007f0000U)

#define DSP_INTMUX1_INTSEL5_SHIFT                                                                           (8U)
#define DSP_INTMUX1_INTSEL5_MASK                                                                            (0x00007f00U)

#define DSP_INTMUX1_INTSEL4_SHIFT                                                                           (0U)
#define DSP_INTMUX1_INTSEL4_MASK                                                                            (0x0000007fU)

#define DSP_INTXSTAT_SYSINT_SHIFT                                                                           (24U)
#define DSP_INTXSTAT_SYSINT_MASK                                                                            (0xff000000U)

#define DSP_INTXSTAT_CPUINT_SHIFT                                                                           (16U)
#define DSP_INTXSTAT_CPUINT_MASK                                                                            (0x00ff0000U)

#define DSP_INTXSTAT__RESV3_SHIFT                                                                           (1U)
#define DSP_INTXSTAT__RESV3_MASK                                                                            (0x0000fffeU)

#define DSP_INTXSTAT_DROP_SHIFT                                                                             (0U)
#define DSP_INTXSTAT_DROP_MASK                                                                              (0x00000001U)

#define DSP_INTXCLR__RESV3_SHIFT                                                                            (1U)
#define DSP_INTXCLR__RESV3_MASK                                                                             (0xfffffffeU)

#define DSP_INTXCLR_CLEAR_SHIFT                                                                             (0U)
#define DSP_INTXCLR_CLEAR_MASK                                                                              (0x00000001U)

#define DSP_INTDMASK__RESV1_SHIFT                                                                           (16U)
#define DSP_INTDMASK__RESV1_MASK                                                                            (0xffff0000U)

#define DSP_INTDMASK_IDM4_SHIFT                                                                             (4U)
#define DSP_INTDMASK_IDM4_MASK                                                                              (0x00000010U)

#define DSP_INTDMASK_IDM5_SHIFT                                                                             (5U)
#define DSP_INTDMASK_IDM5_MASK                                                                              (0x00000020U)

#define DSP_INTDMASK_IDM6_SHIFT                                                                             (6U)
#define DSP_INTDMASK_IDM6_MASK                                                                              (0x00000040U)

#define DSP_INTDMASK_IDM7_SHIFT                                                                             (7U)
#define DSP_INTDMASK_IDM7_MASK                                                                              (0x00000080U)

#define DSP_INTDMASK_IDM8_SHIFT                                                                             (8U)
#define DSP_INTDMASK_IDM8_MASK                                                                              (0x00000100U)

#define DSP_INTDMASK_IDM9_SHIFT                                                                             (9U)
#define DSP_INTDMASK_IDM9_MASK                                                                              (0x00000200U)

#define DSP_INTDMASK_IDM10_SHIFT                                                                            (10U)
#define DSP_INTDMASK_IDM10_MASK                                                                             (0x00000400U)

#define DSP_INTDMASK_IDM11_SHIFT                                                                            (11U)
#define DSP_INTDMASK_IDM11_MASK                                                                             (0x00000800U)

#define DSP_INTDMASK_IDM12_SHIFT                                                                            (12U)
#define DSP_INTDMASK_IDM12_MASK                                                                             (0x00001000U)

#define DSP_INTDMASK_IDM13_SHIFT                                                                            (13U)
#define DSP_INTDMASK_IDM13_MASK                                                                             (0x00002000U)

#define DSP_INTDMASK_IDM14_SHIFT                                                                            (14U)
#define DSP_INTDMASK_IDM14_MASK                                                                             (0x00004000U)

#define DSP_INTDMASK_IDM15_SHIFT                                                                            (15U)
#define DSP_INTDMASK_IDM15_MASK                                                                             (0x00008000U)

#define DSP_INTDMASK__RESV0_SHIFT                                                                           (0U)
#define DSP_INTDMASK__RESV0_MASK                                                                            (0x0000000fU)

#define DSP_AEGMUX1_AEGSEL7_SHIFT                                                                           (24U)
#define DSP_AEGMUX1_AEGSEL7_MASK                                                                            (0x7f000000U)

#define DSP_AEGMUX1_AEGSEL6_SHIFT                                                                           (16U)
#define DSP_AEGMUX1_AEGSEL6_MASK                                                                            (0x007f0000U)

#define DSP_AEGMUX1_AEGSEL5_SHIFT                                                                           (8U)
#define DSP_AEGMUX1_AEGSEL5_MASK                                                                            (0x00007f00U)

#define DSP_AEGMUX1_AEGSEL4_SHIFT                                                                           (0U)
#define DSP_AEGMUX1_AEGSEL4_MASK                                                                            (0x0000007fU)

#define DSP_AEGMUX0_AEGSEL3_SHIFT                                                                           (24U)
#define DSP_AEGMUX0_AEGSEL3_MASK                                                                            (0x7f000000U)

#define DSP_AEGMUX0_AEGSEL2_SHIFT                                                                           (16U)
#define DSP_AEGMUX0_AEGSEL2_MASK                                                                            (0x007f0000U)

#define DSP_AEGMUX0_AEGSEL1_SHIFT                                                                           (8U)
#define DSP_AEGMUX0_AEGSEL1_MASK                                                                            (0x00007f00U)

#define DSP_AEGMUX0_AEGSEL0_SHIFT                                                                           (0U)
#define DSP_AEGMUX0_AEGSEL0_MASK                                                                            (0x0000007fU)

#if defined (SOC_TDA2PX)
#define DSP_EDCINTMSK_L1DDATA_SHIFT                                                                         (0U)
#define DSP_EDCINTMSK_L1DDATA_MASK                                                                          (0x00000001U)

#define DSP_EDCINTMSK_L1DTAG_SHIFT                                                                          (1U)
#define DSP_EDCINTMSK_L1DTAG_MASK                                                                           (0x00000002U)

#define DSP_EDCINTMSK_L2MPPA_SHIFT                                                                          (2U)
#define DSP_EDCINTMSK_L2MPPA_MASK                                                                           (0x00000004U)

#define DSP_EDCINTMSK_L2TAG_SHIFT                                                                           (3U)
#define DSP_EDCINTMSK_L2TAG_MASK                                                                            (0x00000008U)

#define DSP_EDCINTMSK_L2SNOP_SHIFT                                                                          (4U)
#define DSP_EDCINTMSK_L2SNOP_MASK                                                                           (0x00000010U)

#define DSP_EDCINTMSK_L2LRU_SHIFT                                                                           (5U)
#define DSP_EDCINTMSK_L2LRU_MASK                                                                            (0x00000020U)

#define DSP_EDCINTMSK_L1PTAG_SHIFT                                                                          (6U)
#define DSP_EDCINTMSK_L1PTAG_MASK                                                                           (0x00000040U)

#define DSP_EDCINTFLG_L1DDATA_SHIFT                                                                         (0U)
#define DSP_EDCINTFLG_L1DDATA_MASK                                                                          (0x00000001U)

#define DSP_EDCINTFLG_L1DTAG_SHIFT                                                                          (1U)
#define DSP_EDCINTFLG_L1DTAG_MASK                                                                           (0x00000002U)

#define DSP_EDCINTFLG_L2MPPA_SHIFT                                                                          (2U)
#define DSP_EDCINTFLG_L2MPPA_MASK                                                                           (0x00000004U)

#define DSP_EDCINTFLG_L2TAG_SHIFT                                                                           (3U)
#define DSP_EDCINTFLG_L2TAG_MASK                                                                            (0x00000008U)

#define DSP_EDCINTFLG_L2SNOP_SHIFT                                                                          (4U)
#define DSP_EDCINTFLG_L2SNOP_MASK                                                                           (0x00000010U)

#define DSP_EDCINTFLG_L2LRU_SHIFT                                                                           (5U)
#define DSP_EDCINTFLG_L2LRU_MASK                                                                            (0x00000020U)

#define DSP_EDCINTFLG_L1PTAG_SHIFT                                                                          (6U)
#define DSP_EDCINTFLG_L1PTAG_MASK                                                                           (0x00000040U)

#define DSP_L1DEDCMD_ENDATA_SHIFT                                                                           (0U)
#define DSP_L1DEDCMD_ENDATA_MASK                                                                            (0x00000001U)

#define DSP_L1DEDCMD_ENTAG_SHIFT                                                                            (1U)
#define DSP_L1DEDCMD_ENTAG_MASK                                                                             (0x00000002U)

#define DSP_L1DEDCMD_SUSPDATA_SHIFT                                                                         (8U)
#define DSP_L1DEDCMD_SUSPDATA_MASK                                                                          (0x00000100U)

#define DSP_L1DEDCMD_SUSPTAG_SHIFT                                                                          (9U)
#define DSP_L1DEDCMD_SUSPTAG_MASK                                                                           (0x00000200U)

#define DSP_L1DEDCMD_NCCLRDATA_SHIFT                                                                        (16U)
#define DSP_L1DEDCMD_NCCLRDATA_MASK                                                                         (0x00010000U)

#define DSP_L1DEDCMD_NCCLRTAG_SHIFT                                                                         (17U)
#define DSP_L1DEDCMD_NCCLRTAG_MASK                                                                          (0x00020000U)

#define DSP_L1DEDCMD_CCLRDATA_SHIFT                                                                         (24U)
#define DSP_L1DEDCMD_CCLRDATA_MASK                                                                          (0x01000000U)

#define DSP_L1DEDCMD_CCLRTAG_SHIFT                                                                          (25U)
#define DSP_L1DEDCMD_CCLRTAG_MASK                                                                           (0x02000000U)

#define DSP_L1DDCSTAT_EN_SHIFT                                                                              (0U)
#define DSP_L1DDCSTAT_EN_MASK                                                                               (0x00000001U)

#define DSP_L1DDCSTAT_SUSP_SHIFT                                                                            (1U)
#define DSP_L1DDCSTAT_SUSP_MASK                                                                             (0x00000002U)

#define DSP_L1DDCSTAT_BITPOS_SHIFT                                                                          (2U)
#define DSP_L1DDCSTAT_BITPOS_MASK                                                                           (0x0000001CU)

#define DSP_L1DDCSTAT_BYTE_SHIFT                                                                            (5U)
#define DSP_L1DDCSTAT_BYTE_MASK                                                                             (0x00000060U)

#define DSP_L1DDCSTAT_BANK_SHIFT                                                                            (7U)
#define DSP_L1DDCSTAT_BANK_MASK                                                                             (0x00000380U)

#define DSP_L1DDCSTAT_CERR2_SHIFT                                                                           (30U)
#define DSP_L1DDCSTAT_CERR2_MASK                                                                            (0x40000000U)

#define DSP_L1DDCSTAT_CERR1_SHIFT                                                                           (31U)
#define DSP_L1DDCSTAT_CERR1_MASK                                                                            (0x80000000U)

#define DSP_L1DDNCSTAT_EN_SHIFT                                                                             (0U)
#define DSP_L1DDNCSTAT_EN_MASK                                                                              (0x00000001U)

#define DSP_L1DDNCSTAT_SUSP_SHIFT                                                                           (1U)
#define DSP_L1DDNCSTAT_SUSP_MASK                                                                            (0x00000002U)

#define DSP_L1DDNCSTAT_BYTE_SHIFT                                                                           (5U)
#define DSP_L1DDNCSTAT_BYTE_MASK                                                                            (0x00000060U)

#define DSP_L1DDNCSTAT_BANK_SHIFT                                                                           (7U)
#define DSP_L1DDNCSTAT_BANK_MASK                                                                            (0x00000380U)

#define DSP_L1DDNCSTAT_CERR2_SHIFT                                                                          (30U)
#define DSP_L1DDNCSTAT_CERR2_MASK                                                                           (0x40000000U)

#define DSP_L1DDNCSTAT_CERR1_SHIFT                                                                          (31U)
#define DSP_L1DDNCSTAT_CERR1_MASK                                                                           (0x80000000U)

#define DSP_L1DTCSTAT_EN_SHIFT                                                                              (0U)
#define DSP_L1DTCSTAT_EN_MASK                                                                               (0x00000001U)

#define DSP_L1DTCSTAT_SUSP_SHIFT                                                                            (1U)
#define DSP_L1DTCSTAT_SUSP_MASK                                                                             (0x00000002U)

#define DSP_L1DTCSTAT_BITPOS_SHIFT                                                                          (2U)
#define DSP_L1DTCSTAT_BITPOS_MASK                                                                           (0x0000001CU)

#define DSP_L1DTCSTAT_CHAN_SHIFT                                                                            (5U)
#define DSP_L1DTCSTAT_CHAN_MASK                                                                             (0x00000060U)

#define DSP_L1DTCSTAT_BANK_SHIFT                                                                            (7U)
#define DSP_L1DTCSTAT_BANK_MASK                                                                             (0x00000380U)

#define DSP_L1DTCSTAT_CERR2_SHIFT                                                                           (30U)
#define DSP_L1DTCSTAT_CERR2_MASK                                                                            (0x40000000U)

#define DSP_L1DTCSTAT_CERR1_SHIFT                                                                           (31U)
#define DSP_L1DTCSTAT_CERR1_MASK                                                                            (0x80000000U)

#define DSP_L1DTNCSTAT_EN_SHIFT                                                                             (0U)
#define DSP_L1DTNCSTAT_EN_MASK                                                                              (0x00000001U)

#define DSP_L1DTNCSTAT_SUSP_SHIFT                                                                           (1U)
#define DSP_L1DTNCSTAT_SUSP_MASK                                                                            (0x00000002U)

#define DSP_L1DTNCSTAT_CHAN_SHIFT                                                                           (5U)
#define DSP_L1DTNCSTAT_CHAN_MASK                                                                            (0x00000060U)

#define DSP_L1DTNCSTAT_BANK_SHIFT                                                                           (7U)
#define DSP_L1DTNCSTAT_BANK_MASK                                                                            (0x00000380U)

#define DSP_L1DTNCSTAT_NCERR2_SHIFT                                                                         (30U)
#define DSP_L1DTNCSTAT_NCERR2_MASK                                                                          (0x40000000U)

#define DSP_L1DTNCSTAT_NCERR1_SHIFT                                                                         (31U)
#define DSP_L1DTNCSTAT_NCERR1_MASK                                                                          (0x80000000U)

#define DSP_L1DDEDADDR_CADDR_SHIFT                                                                          (0U)
#define DSP_L1DDEDADDR_CADDR_MASK                                                                           (0x000003FFU)

#define DSP_L1DDEDADDR_NCADDR_SHIFT                                                                         (16U)
#define DSP_L1DDEDADDR_NCADDR_MASK                                                                          (0x03FF0000U)

#define DSP_L1DTEDADDR_CADDR_SHIFT                                                                          (0U)
#define DSP_L1DTEDADDR_CADDR_MASK                                                                           (0x000003FFU)

#define DSP_L1DTEDADDR_NCADDR_SHIFT                                                                         (16U)
#define DSP_L1DTEDADDR_NCADDR_MASK                                                                          (0x03FF0000U)

#define DSP_L1DEDCNT_CPECNT_SHIFT                                                                           (0U)
#define DSP_L1DEDCNT_CPECNT_MASK                                                                            (0x0000FFFFU)

#define DSP_L1DEDCNT_NCPECNT_SHIFT                                                                          (16U)
#define DSP_L1DEDCNT_NCPECNT_MASK                                                                           (0xFFFF0000U)

#define DSP_L1PTEDCMD_EN_SHIFT                                                                              (0U)
#define DSP_L1PTEDCMD_EN_MASK                                                                               (0x00000001U)

#define DSP_L2TEDCMD_TAGEN_SHIFT                                                                            (0U)
#define DSP_L2TEDCMD_TAGEN_MASK                                                                             (0x00000001U)

#define DSP_L2TEDCMD_NCCLRTAG_SHIFT                                                                         (8U)
#define DSP_L2TEDCMD_NCCLRTAG_MASK                                                                          (0x00000100U)

#define DSP_L2TEDCMD_CCLRTAG_SHIFT                                                                          (16U)
#define DSP_L2TEDCMD_CCLRTAG_MASK                                                                           (0x00010000U)

#define DSP_L2TCSTAT_EN_SHIFT                                                                               (0U)
#define DSP_L2TCSTAT_EN_MASK                                                                                (0x00000001U)

#define DSP_L2TCSTAT_BITPOS_SHIFT                                                                           (2U)
#define DSP_L2TCSTAT_BITPOS_MASK                                                                            (0x0000007CU)

#define DSP_L2TCSTAT_CHAN_SHIFT                                                                             (7U)
#define DSP_L2TCSTAT_CHAN_MASK                                                                              (0x00000080U)

#define DSP_L2TCSTAT_BANK_SHIFT                                                                             (8U)
#define DSP_L2TCSTAT_BANK_MASK                                                                              (0x00000100U)

#define DSP_L2TCSTAT_CERR2_SHIFT                                                                            (30U)
#define DSP_L2TCSTAT_CERR2_MASK                                                                             (0x40000000U)

#define DSP_L2TCSTAT_CERR1_SHIFT                                                                            (31U)
#define DSP_L2TCSTAT_CERR1_MASK                                                                             (0x80000000U)

#define DSP_L2TNCSTAT_EN_SHIFT                                                                              (0U)
#define DSP_L2TNCSTAT_EN_MASK                                                                               (0x00000001U)

#define DSP_L2TNCSTAT_BANK_SHIFT                                                                            (8U)
#define DSP_L2TNCSTAT_BANK_MASK                                                                             (0x00000100U)

#define DSP_L2TNCSTAT_NCERR2_SHIFT                                                                          (30U)
#define DSP_L2TNCSTAT_NCERR2_MASK                                                                           (0x40000000U)

#define DSP_L2TNCSTAT_NCERR1_SHIFT                                                                          (31U)
#define DSP_L2TNCSTAT_NCERR1_MASK                                                                           (0x80000000U)

#define DSP_L2TEDADDR_CADDR_SHIFT                                                                           (0U)
#define DSP_L2TEDADDR_CADDR_MASK                                                                            (0x000003FFU)

#define DSP_L2TEDADDR_NCADDR_SHIFT                                                                          (16U)
#define DSP_L2TEDADDR_NCADDR_MASK                                                                           (0x03FF0000U)

#define DSP_L2TEDCNT_CPECNT_SHIFT                                                                           (0U)
#define DSP_L2TEDCNT_CPECNT_MASK                                                                            (0x0000FFFFU)

#define DSP_L2TEDCNT_NCPECNT_SHIFT                                                                          (16U)
#define DSP_L2TEDCNT_NCPECNT_MASK                                                                           (0xFFFF0000U)

#define DSP_L1PTEDCMD_EN_SHIFT                                                                              (0U)
#define DSP_L1PTEDCMD_EN_MASK                                                                               (0x00000001U)

#define DSP_L1PTEDCMD_EN_SHIFT                                                                              (0U)
#define DSP_L1PTEDCMD_EN_MASK                                                                               (0x00000001U)

#define DSP_L1PTEDCMD_NCCLR_SHIFT                                                                           (5U)
#define DSP_L1PTEDCMD_NCCLR_MASK                                                                            (0x00000020U)

#define DSP_L1PTEDSTAT_EN_SHIFT                                                                             (0U)
#define DSP_L1PTEDSTAT_EN_MASK                                                                              (0x00000001U)

#define DSP_L1PTEDSTAT_CERR1_SHIFT                                                                          (30U)
#define DSP_L1PTEDSTAT_CERR1_MASK                                                                           (0x40000000U)

#define DSP_L1PTEDSTAT_CERR2_SHIFT                                                                          (31U)
#define DSP_L1PTEDSTAT_CERR2_MASK                                                                           (0x80000000U)

#define DSP_L1PTEDCMD_NCERR1_SHIFT                                                                          (30U)
#define DSP_L1PTEDCMD_NCERR1_MASK                                                                           (0x40000000U)

#define DSP_L1PTEDCMD_NCERR2_SHIFT                                                                          (31U)
#define DSP_L1PTEDCMD_NCERR2_MASK                                                                           (0x80000000U)

#define DSP_L1PTEDADDR_NCADDR_SHIFT                                                                         (16U)
#define DSP_L1PTEDADDR_NCADDR_MASK                                                                          (0x0FFF0000U)

#define DSP_L1PTEDCNT_NCPECNT_SHIFT                                                                         (16U)
#define DSP_L1PTEDCNT_NCPECNT_MASK                                                                          (0xFFFF0000U)
#endif

#define DSP_L1PEDSTAT_RESV1_SHIFT                                                                           (7U)
#define DSP_L1PEDSTAT_RESV1_MASK                                                                            (0xffffff80U)

#define DSP_L1PEDSTAT_DMAERR_SHIFT                                                                          (6U)
#define DSP_L1PEDSTAT_DMAERR_MASK                                                                           (0x00000040U)

#define DSP_L1PEDSTAT_PERR_SHIFT                                                                            (5U)
#define DSP_L1PEDSTAT_PERR_MASK                                                                             (0x00000020U)

#define DSP_L1PEDSTAT_RESV2_SHIFT                                                                           (4U)
#define DSP_L1PEDSTAT_RESV2_MASK                                                                            (0x00000010U)

#define DSP_L1PEDSTAT_SUSP_SHIFT                                                                            (3U)
#define DSP_L1PEDSTAT_SUSP_MASK                                                                             (0x00000008U)

#define DSP_L1PEDSTAT_DIS_SHIFT                                                                             (2U)
#define DSP_L1PEDSTAT_DIS_MASK                                                                              (0x00000004U)

#define DSP_L1PEDSTAT_RESV3_SHIFT                                                                           (1U)
#define DSP_L1PEDSTAT_RESV3_MASK                                                                            (0x00000002U)

#define DSP_L1PEDSTAT_EN_SHIFT                                                                              (0U)
#define DSP_L1PEDSTAT_EN_MASK                                                                               (0x00000001U)

#define DSP_L1PEDCMD_RESV1_SHIFT                                                                            (7U)
#define DSP_L1PEDCMD_RESV1_MASK                                                                             (0xffffff80U)

#define DSP_L1PEDCMD_DMACLR_SHIFT                                                                           (6U)
#define DSP_L1PEDCMD_DMACLR_MASK                                                                            (0x00000040U)

#define DSP_L1PEDCMD_PCLR_SHIFT                                                                             (5U)
#define DSP_L1PEDCMD_PCLR_MASK                                                                              (0x00000020U)

#define DSP_L1PEDCMD_RESV2_SHIFT                                                                            (4U)
#define DSP_L1PEDCMD_RESV2_MASK                                                                             (0x00000010U)

#define DSP_L1PEDCMD_SUSP_SHIFT                                                                             (3U)
#define DSP_L1PEDCMD_SUSP_MASK                                                                              (0x00000008U)

#define DSP_L1PEDCMD_DIS_SHIFT                                                                              (2U)
#define DSP_L1PEDCMD_DIS_MASK                                                                               (0x00000004U)

#define DSP_L1PEDCMD_RESV3_SHIFT                                                                            (1U)
#define DSP_L1PEDCMD_RESV3_MASK                                                                             (0x00000002U)

#define DSP_L1PEDCMD_EN_SHIFT                                                                               (0U)
#define DSP_L1PEDCMD_EN_MASK                                                                                (0x00000001U)

#define DSP_L1PEDADDR_ADDR_SHIFT                                                                            (5U)
#define DSP_L1PEDADDR_ADDR_MASK                                                                             (0xffffffe0U)

#define DSP_L1PEDADDR_RESV1_SHIFT                                                                           (1U)
#define DSP_L1PEDADDR_RESV1_MASK                                                                            (0x0000001eU)

#define DSP_L1PEDADDR_RAM_SHIFT                                                                             (0U)
#define DSP_L1PEDADDR_RAM_MASK                                                                              (0x00000001U)

#define DSP_L2EDSTAT_RESV1_SHIFT                                                                            (24U)
#define DSP_L2EDSTAT_RESV1_MASK                                                                             (0xff000000U)

#define DSP_L2EDSTAT_BITPOS_SHIFT                                                                           (16U)
#define DSP_L2EDSTAT_BITPOS_MASK                                                                            (0x00ff0000U)

#define DSP_L2EDSTAT_RESV2_SHIFT                                                                            (10U)
#define DSP_L2EDSTAT_RESV2_MASK                                                                             (0x0000fc00U)

#define DSP_L2EDSTAT_NERR_SHIFT                                                                             (8U)
#define DSP_L2EDSTAT_NERR_MASK                                                                              (0x00000300U)

#define DSP_L2EDSTAT_VERR_SHIFT                                                                             (7U)
#define DSP_L2EDSTAT_VERR_MASK                                                                              (0x00000080U)

#define DSP_L2EDSTAT_DMAERR_SHIFT                                                                           (6U)
#define DSP_L2EDSTAT_DMAERR_MASK                                                                            (0x00000040U)

#define DSP_L2EDSTAT_PERR_SHIFT                                                                             (5U)
#define DSP_L2EDSTAT_PERR_MASK                                                                              (0x00000020U)

#define DSP_L2EDSTAT_DERR_SHIFT                                                                             (4U)
#define DSP_L2EDSTAT_DERR_MASK                                                                              (0x00000010U)

#define DSP_L2EDSTAT_SUSP_SHIFT                                                                             (3U)
#define DSP_L2EDSTAT_SUSP_MASK                                                                              (0x00000008U)

#define DSP_L2EDSTAT_DIS_SHIFT                                                                              (2U)
#define DSP_L2EDSTAT_DIS_MASK                                                                               (0x00000004U)

#define DSP_L2EDSTAT_RESV3_SHIFT                                                                            (1U)
#define DSP_L2EDSTAT_RESV3_MASK                                                                             (0x00000002U)

#define DSP_L2EDSTAT_EN_SHIFT                                                                               (0U)
#define DSP_L2EDSTAT_EN_MASK                                                                                (0x00000001U)

#define DSP_L2EDCMD_RESV1_SHIFT                                                                             (8U)
#define DSP_L2EDCMD_RESV1_MASK                                                                              (0xffffff00U)

#define DSP_L2EDCMD_VCLR_SHIFT                                                                              (7U)
#define DSP_L2EDCMD_VCLR_MASK                                                                               (0x00000080U)

#define DSP_L2EDCMD_DMACLR_SHIFT                                                                            (6U)
#define DSP_L2EDCMD_DMACLR_MASK                                                                             (0x00000040U)

#define DSP_L2EDCMD_PCLR_SHIFT                                                                              (5U)
#define DSP_L2EDCMD_PCLR_MASK                                                                               (0x00000020U)

#define DSP_L2EDCMD_DCLR_SHIFT                                                                              (4U)
#define DSP_L2EDCMD_DCLR_MASK                                                                               (0x00000010U)

#define DSP_L2EDCMD_SUSP_SHIFT                                                                              (3U)
#define DSP_L2EDCMD_SUSP_MASK                                                                               (0x00000008U)

#define DSP_L2EDCMD_DIS_SHIFT                                                                               (2U)
#define DSP_L2EDCMD_DIS_MASK                                                                                (0x00000004U)

#define DSP_L2EDCMD_RESV3_SHIFT                                                                             (1U)
#define DSP_L2EDCMD_RESV3_MASK                                                                              (0x00000002U)

#define DSP_L2EDCMD_EN_SHIFT                                                                                (0U)
#define DSP_L2EDCMD_EN_MASK                                                                                 (0x00000001U)

#define DSP_L2EDADDR_ADDR_SHIFT                                                                             (5U)
#define DSP_L2EDADDR_ADDR_MASK                                                                              (0xffffffe0U)

#define DSP_L2EDADDR_RESV1_SHIFT                                                                            (1U)
#define DSP_L2EDADDR_RESV1_MASK                                                                             (0x00000006U)

#define DSP_L2EDADDR_RAM_SHIFT                                                                              (0U)
#define DSP_L2EDADDR_RAM_MASK                                                                               (0x00000001U)

#define DSP_L2EDADDR_L2WAY_SHIFT                                                                            (3U)
#define DSP_L2EDADDR_L2WAY_MASK                                                                             (0x00000018U)

#define DSP_L2EDCPEC_RESV1_SHIFT                                                                            (8U)
#define DSP_L2EDCPEC_RESV1_MASK                                                                             (0xffffff00U)

#define DSP_L2EDCPEC_CNT_SHIFT                                                                              (0U)
#define DSP_L2EDCPEC_CNT_MASK                                                                               (0x000000ffU)

#define DSP_L2EDCEN_RESV1_SHIFT                                                                             (5U)
#define DSP_L2EDCEN_RESV1_MASK                                                                              (0xffffffe0U)

#define DSP_L2EDCEN_SDMAEN_SHIFT                                                                            (4U)
#define DSP_L2EDCEN_SDMAEN_MASK                                                                             (0x00000010U)

#define DSP_L2EDCEN_PL2SEN_SHIFT                                                                            (3U)
#define DSP_L2EDCEN_PL2SEN_MASK                                                                             (0x00000008U)

#define DSP_L2EDCEN_DL2SEN_SHIFT                                                                            (2U)
#define DSP_L2EDCEN_DL2SEN_MASK                                                                             (0x00000004U)

#define DSP_L2EDCEN_PL2CEN_SHIFT                                                                            (1U)
#define DSP_L2EDCEN_PL2CEN_MASK                                                                             (0x00000002U)

#define DSP_L2EDCEN_DL2CEN_SHIFT                                                                            (0U)
#define DSP_L2EDCEN_DL2CEN_MASK                                                                             (0x00000001U)

#define DSP_EVTFLAG1_EF32_SHIFT                                                                             (0U)
#define DSP_EVTFLAG1_EF32_MASK                                                                              (0x00000001U)

#define DSP_EVTFLAG1_EF33_SHIFT                                                                             (1U)
#define DSP_EVTFLAG1_EF33_MASK                                                                              (0x00000002U)

#define DSP_EVTFLAG1_EF34_SHIFT                                                                             (2U)
#define DSP_EVTFLAG1_EF34_MASK                                                                              (0x00000004U)

#define DSP_EVTFLAG1_EF35_SHIFT                                                                             (3U)
#define DSP_EVTFLAG1_EF35_MASK                                                                              (0x00000008U)

#define DSP_EVTFLAG1_EF36_SHIFT                                                                             (4U)
#define DSP_EVTFLAG1_EF36_MASK                                                                              (0x00000010U)

#define DSP_EVTFLAG1_EF37_SHIFT                                                                             (5U)
#define DSP_EVTFLAG1_EF37_MASK                                                                              (0x00000020U)

#define DSP_EVTFLAG1_EF38_SHIFT                                                                             (6U)
#define DSP_EVTFLAG1_EF38_MASK                                                                              (0x00000040U)

#define DSP_EVTFLAG1_EF39_SHIFT                                                                             (7U)
#define DSP_EVTFLAG1_EF39_MASK                                                                              (0x00000080U)

#define DSP_EVTFLAG1_EF40_SHIFT                                                                             (8U)
#define DSP_EVTFLAG1_EF40_MASK                                                                              (0x00000100U)

#define DSP_EVTFLAG1_EF41_SHIFT                                                                             (9U)
#define DSP_EVTFLAG1_EF41_MASK                                                                              (0x00000200U)

#define DSP_EVTFLAG1_EF42_SHIFT                                                                             (10U)
#define DSP_EVTFLAG1_EF42_MASK                                                                              (0x00000400U)

#define DSP_EVTFLAG1_EF43_SHIFT                                                                             (11U)
#define DSP_EVTFLAG1_EF43_MASK                                                                              (0x00000800U)

#define DSP_EVTFLAG1_EF44_SHIFT                                                                             (12U)
#define DSP_EVTFLAG1_EF44_MASK                                                                              (0x00001000U)

#define DSP_EVTFLAG1_EF45_SHIFT                                                                             (13U)
#define DSP_EVTFLAG1_EF45_MASK                                                                              (0x00002000U)

#define DSP_EVTFLAG1_EF46_SHIFT                                                                             (14U)
#define DSP_EVTFLAG1_EF46_MASK                                                                              (0x00004000U)

#define DSP_EVTFLAG1_EF47_SHIFT                                                                             (15U)
#define DSP_EVTFLAG1_EF47_MASK                                                                              (0x00008000U)

#define DSP_EVTFLAG1_EF48_SHIFT                                                                             (16U)
#define DSP_EVTFLAG1_EF48_MASK                                                                              (0x00010000U)

#define DSP_EVTFLAG1_EF49_SHIFT                                                                             (17U)
#define DSP_EVTFLAG1_EF49_MASK                                                                              (0x00020000U)

#define DSP_EVTFLAG1_EF50_SHIFT                                                                             (18U)
#define DSP_EVTFLAG1_EF50_MASK                                                                              (0x00040000U)

#define DSP_EVTFLAG1_EF51_SHIFT                                                                             (19U)
#define DSP_EVTFLAG1_EF51_MASK                                                                              (0x00080000U)

#define DSP_EVTFLAG1_EF52_SHIFT                                                                             (20U)
#define DSP_EVTFLAG1_EF52_MASK                                                                              (0x00100000U)

#define DSP_EVTFLAG1_EF53_SHIFT                                                                             (21U)
#define DSP_EVTFLAG1_EF53_MASK                                                                              (0x00200000U)

#define DSP_EVTFLAG1_EF54_SHIFT                                                                             (22U)
#define DSP_EVTFLAG1_EF54_MASK                                                                              (0x00400000U)

#define DSP_EVTFLAG1_EF55_SHIFT                                                                             (23U)
#define DSP_EVTFLAG1_EF55_MASK                                                                              (0x00800000U)

#define DSP_EVTFLAG1_EF56_SHIFT                                                                             (24U)
#define DSP_EVTFLAG1_EF56_MASK                                                                              (0x01000000U)

#define DSP_EVTFLAG1_EF57_SHIFT                                                                             (25U)
#define DSP_EVTFLAG1_EF57_MASK                                                                              (0x02000000U)

#define DSP_EVTFLAG1_EF58_SHIFT                                                                             (26U)
#define DSP_EVTFLAG1_EF58_MASK                                                                              (0x04000000U)

#define DSP_EVTFLAG1_EF59_SHIFT                                                                             (27U)
#define DSP_EVTFLAG1_EF59_MASK                                                                              (0x08000000U)

#define DSP_EVTFLAG1_EF60_SHIFT                                                                             (28U)
#define DSP_EVTFLAG1_EF60_MASK                                                                              (0x10000000U)

#define DSP_EVTFLAG1_EF61_SHIFT                                                                             (29U)
#define DSP_EVTFLAG1_EF61_MASK                                                                              (0x20000000U)

#define DSP_EVTFLAG1_EF62_SHIFT                                                                             (30U)
#define DSP_EVTFLAG1_EF62_MASK                                                                              (0x40000000U)

#define DSP_EVTFLAG1_EF63_SHIFT                                                                             (31U)
#define DSP_EVTFLAG1_EF63_MASK                                                                              (0x80000000U)

#define DSP_EVTFLAG2_EF64_SHIFT                                                                             (0U)
#define DSP_EVTFLAG2_EF64_MASK                                                                              (0x00000001U)

#define DSP_EVTFLAG2_EF65_SHIFT                                                                             (1U)
#define DSP_EVTFLAG2_EF65_MASK                                                                              (0x00000002U)

#define DSP_EVTFLAG2_EF66_SHIFT                                                                             (2U)
#define DSP_EVTFLAG2_EF66_MASK                                                                              (0x00000004U)

#define DSP_EVTFLAG2_EF67_SHIFT                                                                             (3U)
#define DSP_EVTFLAG2_EF67_MASK                                                                              (0x00000008U)

#define DSP_EVTFLAG2_EF68_SHIFT                                                                             (4U)
#define DSP_EVTFLAG2_EF68_MASK                                                                              (0x00000010U)

#define DSP_EVTFLAG2_EF69_SHIFT                                                                             (5U)
#define DSP_EVTFLAG2_EF69_MASK                                                                              (0x00000020U)

#define DSP_EVTFLAG2_EF70_SHIFT                                                                             (6U)
#define DSP_EVTFLAG2_EF70_MASK                                                                              (0x00000040U)

#define DSP_EVTFLAG2_EF71_SHIFT                                                                             (7U)
#define DSP_EVTFLAG2_EF71_MASK                                                                              (0x00000080U)

#define DSP_EVTFLAG2_EF72_SHIFT                                                                             (8U)
#define DSP_EVTFLAG2_EF72_MASK                                                                              (0x00000100U)

#define DSP_EVTFLAG2_EF73_SHIFT                                                                             (9U)
#define DSP_EVTFLAG2_EF73_MASK                                                                              (0x00000200U)

#define DSP_EVTFLAG2_EF74_SHIFT                                                                             (10U)
#define DSP_EVTFLAG2_EF74_MASK                                                                              (0x00000400U)

#define DSP_EVTFLAG2_EF75_SHIFT                                                                             (11U)
#define DSP_EVTFLAG2_EF75_MASK                                                                              (0x00000800U)

#define DSP_EVTFLAG2_EF76_SHIFT                                                                             (12U)
#define DSP_EVTFLAG2_EF76_MASK                                                                              (0x00001000U)

#define DSP_EVTFLAG2_EF77_SHIFT                                                                             (13U)
#define DSP_EVTFLAG2_EF77_MASK                                                                              (0x00002000U)

#define DSP_EVTFLAG2_EF78_SHIFT                                                                             (14U)
#define DSP_EVTFLAG2_EF78_MASK                                                                              (0x00004000U)

#define DSP_EVTFLAG2_EF79_SHIFT                                                                             (15U)
#define DSP_EVTFLAG2_EF79_MASK                                                                              (0x00008000U)

#define DSP_EVTFLAG2_EF80_SHIFT                                                                             (16U)
#define DSP_EVTFLAG2_EF80_MASK                                                                              (0x00010000U)

#define DSP_EVTFLAG2_EF81_SHIFT                                                                             (17U)
#define DSP_EVTFLAG2_EF81_MASK                                                                              (0x00020000U)

#define DSP_EVTFLAG2_EF82_SHIFT                                                                             (18U)
#define DSP_EVTFLAG2_EF82_MASK                                                                              (0x00040000U)

#define DSP_EVTFLAG2_EF83_SHIFT                                                                             (19U)
#define DSP_EVTFLAG2_EF83_MASK                                                                              (0x00080000U)

#define DSP_EVTFLAG2_EF84_SHIFT                                                                             (20U)
#define DSP_EVTFLAG2_EF84_MASK                                                                              (0x00100000U)

#define DSP_EVTFLAG2_EF85_SHIFT                                                                             (21U)
#define DSP_EVTFLAG2_EF85_MASK                                                                              (0x00200000U)

#define DSP_EVTFLAG2_EF86_SHIFT                                                                             (22U)
#define DSP_EVTFLAG2_EF86_MASK                                                                              (0x00400000U)

#define DSP_EVTFLAG2_EF87_SHIFT                                                                             (23U)
#define DSP_EVTFLAG2_EF87_MASK                                                                              (0x00800000U)

#define DSP_EVTFLAG2_EF88_SHIFT                                                                             (24U)
#define DSP_EVTFLAG2_EF88_MASK                                                                              (0x01000000U)

#define DSP_EVTFLAG2_EF89_SHIFT                                                                             (25U)
#define DSP_EVTFLAG2_EF89_MASK                                                                              (0x02000000U)

#define DSP_EVTFLAG2_EF90_SHIFT                                                                             (26U)
#define DSP_EVTFLAG2_EF90_MASK                                                                              (0x04000000U)

#define DSP_EVTFLAG2_EF91_SHIFT                                                                             (27U)
#define DSP_EVTFLAG2_EF91_MASK                                                                              (0x08000000U)

#define DSP_EVTFLAG2_EF92_SHIFT                                                                             (28U)
#define DSP_EVTFLAG2_EF92_MASK                                                                              (0x10000000U)

#define DSP_EVTFLAG2_EF93_SHIFT                                                                             (29U)
#define DSP_EVTFLAG2_EF93_MASK                                                                              (0x20000000U)

#define DSP_EVTFLAG2_EF94_SHIFT                                                                             (30U)
#define DSP_EVTFLAG2_EF94_MASK                                                                              (0x40000000U)

#define DSP_EVTFLAG2_EF95_SHIFT                                                                             (31U)
#define DSP_EVTFLAG2_EF95_MASK                                                                              (0x80000000U)

#define DSP_EVTFLAG3_EF96_SHIFT                                                                             (0U)
#define DSP_EVTFLAG3_EF96_MASK                                                                              (0x00000001U)

#define DSP_EVTFLAG3_EF97_SHIFT                                                                             (1U)
#define DSP_EVTFLAG3_EF97_MASK                                                                              (0x00000002U)

#define DSP_EVTFLAG3_EF98_SHIFT                                                                             (2U)
#define DSP_EVTFLAG3_EF98_MASK                                                                              (0x00000004U)

#define DSP_EVTFLAG3_EF99_SHIFT                                                                             (3U)
#define DSP_EVTFLAG3_EF99_MASK                                                                              (0x00000008U)

#define DSP_EVTFLAG3_EF100_SHIFT                                                                            (4U)
#define DSP_EVTFLAG3_EF100_MASK                                                                             (0x00000010U)

#define DSP_EVTFLAG3_EF101_SHIFT                                                                            (5U)
#define DSP_EVTFLAG3_EF101_MASK                                                                             (0x00000020U)

#define DSP_EVTFLAG3_EF102_SHIFT                                                                            (6U)
#define DSP_EVTFLAG3_EF102_MASK                                                                             (0x00000040U)

#define DSP_EVTFLAG3_EF103_SHIFT                                                                            (7U)
#define DSP_EVTFLAG3_EF103_MASK                                                                             (0x00000080U)

#define DSP_EVTFLAG3_EF104_SHIFT                                                                            (8U)
#define DSP_EVTFLAG3_EF104_MASK                                                                             (0x00000100U)

#define DSP_EVTFLAG3_EF105_SHIFT                                                                            (9U)
#define DSP_EVTFLAG3_EF105_MASK                                                                             (0x00000200U)

#define DSP_EVTFLAG3_EF106_SHIFT                                                                            (10U)
#define DSP_EVTFLAG3_EF106_MASK                                                                             (0x00000400U)

#define DSP_EVTFLAG3_EF107_SHIFT                                                                            (11U)
#define DSP_EVTFLAG3_EF107_MASK                                                                             (0x00000800U)

#define DSP_EVTFLAG3_EF108_SHIFT                                                                            (12U)
#define DSP_EVTFLAG3_EF108_MASK                                                                             (0x00001000U)

#define DSP_EVTFLAG3_EF109_SHIFT                                                                            (13U)
#define DSP_EVTFLAG3_EF109_MASK                                                                             (0x00002000U)

#define DSP_EVTFLAG3_EF110_SHIFT                                                                            (14U)
#define DSP_EVTFLAG3_EF110_MASK                                                                             (0x00004000U)

#define DSP_EVTFLAG3_EF111_SHIFT                                                                            (15U)
#define DSP_EVTFLAG3_EF111_MASK                                                                             (0x00008000U)

#define DSP_EVTFLAG3_EF112_SHIFT                                                                            (16U)
#define DSP_EVTFLAG3_EF112_MASK                                                                             (0x00010000U)

#define DSP_EVTFLAG3_EF113_SHIFT                                                                            (17U)
#define DSP_EVTFLAG3_EF113_MASK                                                                             (0x00020000U)

#define DSP_EVTFLAG3_EF114_SHIFT                                                                            (18U)
#define DSP_EVTFLAG3_EF114_MASK                                                                             (0x00040000U)

#define DSP_EVTFLAG3_EF115_SHIFT                                                                            (19U)
#define DSP_EVTFLAG3_EF115_MASK                                                                             (0x00080000U)

#define DSP_EVTFLAG3_EF116_SHIFT                                                                            (20U)
#define DSP_EVTFLAG3_EF116_MASK                                                                             (0x00100000U)

#define DSP_EVTFLAG3_EF117_SHIFT                                                                            (21U)
#define DSP_EVTFLAG3_EF117_MASK                                                                             (0x00200000U)

#define DSP_EVTFLAG3_EF118_SHIFT                                                                            (22U)
#define DSP_EVTFLAG3_EF118_MASK                                                                             (0x00400000U)

#define DSP_EVTFLAG3_EF119_SHIFT                                                                            (23U)
#define DSP_EVTFLAG3_EF119_MASK                                                                             (0x00800000U)

#define DSP_EVTFLAG3_EF120_SHIFT                                                                            (24U)
#define DSP_EVTFLAG3_EF120_MASK                                                                             (0x01000000U)

#define DSP_EVTFLAG3_EF121_SHIFT                                                                            (25U)
#define DSP_EVTFLAG3_EF121_MASK                                                                             (0x02000000U)

#define DSP_EVTFLAG3_EF122_SHIFT                                                                            (26U)
#define DSP_EVTFLAG3_EF122_MASK                                                                             (0x04000000U)

#define DSP_EVTFLAG3_EF123_SHIFT                                                                            (27U)
#define DSP_EVTFLAG3_EF123_MASK                                                                             (0x08000000U)

#define DSP_EVTFLAG3_EF124_SHIFT                                                                            (28U)
#define DSP_EVTFLAG3_EF124_MASK                                                                             (0x10000000U)

#define DSP_EVTFLAG3_EF125_SHIFT                                                                            (29U)
#define DSP_EVTFLAG3_EF125_MASK                                                                             (0x20000000U)

#define DSP_EVTFLAG3_EF126_SHIFT                                                                            (30U)
#define DSP_EVTFLAG3_EF126_MASK                                                                             (0x40000000U)

#define DSP_EVTFLAG3_EF127_SHIFT                                                                            (31U)
#define DSP_EVTFLAG3_EF127_MASK                                                                             (0x80000000U)

#define DSP_EVTCLR1_EC32_SHIFT                                                                              (0U)
#define DSP_EVTCLR1_EC32_MASK                                                                               (0x00000001U)

#define DSP_EVTCLR1_EC33_SHIFT                                                                              (1U)
#define DSP_EVTCLR1_EC33_MASK                                                                               (0x00000002U)

#define DSP_EVTCLR1_EC34_SHIFT                                                                              (2U)
#define DSP_EVTCLR1_EC34_MASK                                                                               (0x00000004U)

#define DSP_EVTCLR1_EC35_SHIFT                                                                              (3U)
#define DSP_EVTCLR1_EC35_MASK                                                                               (0x00000008U)

#define DSP_EVTCLR1_EC36_SHIFT                                                                              (4U)
#define DSP_EVTCLR1_EC36_MASK                                                                               (0x00000010U)

#define DSP_EVTCLR1_EC37_SHIFT                                                                              (5U)
#define DSP_EVTCLR1_EC37_MASK                                                                               (0x00000020U)

#define DSP_EVTCLR1_EC38_SHIFT                                                                              (6U)
#define DSP_EVTCLR1_EC38_MASK                                                                               (0x00000040U)

#define DSP_EVTCLR1_EC39_SHIFT                                                                              (7U)
#define DSP_EVTCLR1_EC39_MASK                                                                               (0x00000080U)

#define DSP_EVTCLR1_EC40_SHIFT                                                                              (8U)
#define DSP_EVTCLR1_EC40_MASK                                                                               (0x00000100U)

#define DSP_EVTCLR1_EC41_SHIFT                                                                              (9U)
#define DSP_EVTCLR1_EC41_MASK                                                                               (0x00000200U)

#define DSP_EVTCLR1_EC42_SHIFT                                                                              (10U)
#define DSP_EVTCLR1_EC42_MASK                                                                               (0x00000400U)

#define DSP_EVTCLR1_EC43_SHIFT                                                                              (11U)
#define DSP_EVTCLR1_EC43_MASK                                                                               (0x00000800U)

#define DSP_EVTCLR1_EC44_SHIFT                                                                              (12U)
#define DSP_EVTCLR1_EC44_MASK                                                                               (0x00001000U)

#define DSP_EVTCLR1_EC45_SHIFT                                                                              (13U)
#define DSP_EVTCLR1_EC45_MASK                                                                               (0x00002000U)

#define DSP_EVTCLR1_EC46_SHIFT                                                                              (14U)
#define DSP_EVTCLR1_EC46_MASK                                                                               (0x00004000U)

#define DSP_EVTCLR1_EC47_SHIFT                                                                              (15U)
#define DSP_EVTCLR1_EC47_MASK                                                                               (0x00008000U)

#define DSP_EVTCLR1_EC48_SHIFT                                                                              (16U)
#define DSP_EVTCLR1_EC48_MASK                                                                               (0x00010000U)

#define DSP_EVTCLR1_EC49_SHIFT                                                                              (17U)
#define DSP_EVTCLR1_EC49_MASK                                                                               (0x00020000U)

#define DSP_EVTCLR1_EC50_SHIFT                                                                              (18U)
#define DSP_EVTCLR1_EC50_MASK                                                                               (0x00040000U)

#define DSP_EVTCLR1_EC51_SHIFT                                                                              (19U)
#define DSP_EVTCLR1_EC51_MASK                                                                               (0x00080000U)

#define DSP_EVTCLR1_EC52_SHIFT                                                                              (20U)
#define DSP_EVTCLR1_EC52_MASK                                                                               (0x00100000U)

#define DSP_EVTCLR1_EC53_SHIFT                                                                              (21U)
#define DSP_EVTCLR1_EC53_MASK                                                                               (0x00200000U)

#define DSP_EVTCLR1_EC54_SHIFT                                                                              (22U)
#define DSP_EVTCLR1_EC54_MASK                                                                               (0x00400000U)

#define DSP_EVTCLR1_EC55_SHIFT                                                                              (23U)
#define DSP_EVTCLR1_EC55_MASK                                                                               (0x00800000U)

#define DSP_EVTCLR1_EC56_SHIFT                                                                              (24U)
#define DSP_EVTCLR1_EC56_MASK                                                                               (0x01000000U)

#define DSP_EVTCLR1_EC57_SHIFT                                                                              (25U)
#define DSP_EVTCLR1_EC57_MASK                                                                               (0x02000000U)

#define DSP_EVTCLR1_EC58_SHIFT                                                                              (26U)
#define DSP_EVTCLR1_EC58_MASK                                                                               (0x04000000U)

#define DSP_EVTCLR1_EC59_SHIFT                                                                              (27U)
#define DSP_EVTCLR1_EC59_MASK                                                                               (0x08000000U)

#define DSP_EVTCLR1_EC60_SHIFT                                                                              (28U)
#define DSP_EVTCLR1_EC60_MASK                                                                               (0x10000000U)

#define DSP_EVTCLR1_EC61_SHIFT                                                                              (29U)
#define DSP_EVTCLR1_EC61_MASK                                                                               (0x20000000U)

#define DSP_EVTCLR1_EC62_SHIFT                                                                              (30U)
#define DSP_EVTCLR1_EC62_MASK                                                                               (0x40000000U)

#define DSP_EVTCLR1_EC63_SHIFT                                                                              (31U)
#define DSP_EVTCLR1_EC63_MASK                                                                               (0x80000000U)

#define DSP_EVTCLR2_EC64_SHIFT                                                                              (0U)
#define DSP_EVTCLR2_EC64_MASK                                                                               (0x00000001U)

#define DSP_EVTCLR2_EC65_SHIFT                                                                              (1U)
#define DSP_EVTCLR2_EC65_MASK                                                                               (0x00000002U)

#define DSP_EVTCLR2_EC66_SHIFT                                                                              (2U)
#define DSP_EVTCLR2_EC66_MASK                                                                               (0x00000004U)

#define DSP_EVTCLR2_EC67_SHIFT                                                                              (3U)
#define DSP_EVTCLR2_EC67_MASK                                                                               (0x00000008U)

#define DSP_EVTCLR2_EC68_SHIFT                                                                              (4U)
#define DSP_EVTCLR2_EC68_MASK                                                                               (0x00000010U)

#define DSP_EVTCLR2_EC69_SHIFT                                                                              (5U)
#define DSP_EVTCLR2_EC69_MASK                                                                               (0x00000020U)

#define DSP_EVTCLR2_EC70_SHIFT                                                                              (6U)
#define DSP_EVTCLR2_EC70_MASK                                                                               (0x00000040U)

#define DSP_EVTCLR2_EC71_SHIFT                                                                              (7U)
#define DSP_EVTCLR2_EC71_MASK                                                                               (0x00000080U)

#define DSP_EVTCLR2_EC72_SHIFT                                                                              (8U)
#define DSP_EVTCLR2_EC72_MASK                                                                               (0x00000100U)

#define DSP_EVTCLR2_EC73_SHIFT                                                                              (9U)
#define DSP_EVTCLR2_EC73_MASK                                                                               (0x00000200U)

#define DSP_EVTCLR2_EC74_SHIFT                                                                              (10U)
#define DSP_EVTCLR2_EC74_MASK                                                                               (0x00000400U)

#define DSP_EVTCLR2_EC75_SHIFT                                                                              (11U)
#define DSP_EVTCLR2_EC75_MASK                                                                               (0x00000800U)

#define DSP_EVTCLR2_EC76_SHIFT                                                                              (12U)
#define DSP_EVTCLR2_EC76_MASK                                                                               (0x00001000U)

#define DSP_EVTCLR2_EC77_SHIFT                                                                              (13U)
#define DSP_EVTCLR2_EC77_MASK                                                                               (0x00002000U)

#define DSP_EVTCLR2_EC78_SHIFT                                                                              (14U)
#define DSP_EVTCLR2_EC78_MASK                                                                               (0x00004000U)

#define DSP_EVTCLR2_EC79_SHIFT                                                                              (15U)
#define DSP_EVTCLR2_EC79_MASK                                                                               (0x00008000U)

#define DSP_EVTCLR2_EC80_SHIFT                                                                              (16U)
#define DSP_EVTCLR2_EC80_MASK                                                                               (0x00010000U)

#define DSP_EVTCLR2_EC81_SHIFT                                                                              (17U)
#define DSP_EVTCLR2_EC81_MASK                                                                               (0x00020000U)

#define DSP_EVTCLR2_EC82_SHIFT                                                                              (18U)
#define DSP_EVTCLR2_EC82_MASK                                                                               (0x00040000U)

#define DSP_EVTCLR2_EC83_SHIFT                                                                              (19U)
#define DSP_EVTCLR2_EC83_MASK                                                                               (0x00080000U)

#define DSP_EVTCLR2_EC84_SHIFT                                                                              (20U)
#define DSP_EVTCLR2_EC84_MASK                                                                               (0x00100000U)

#define DSP_EVTCLR2_EC85_SHIFT                                                                              (21U)
#define DSP_EVTCLR2_EC85_MASK                                                                               (0x00200000U)

#define DSP_EVTCLR2_EC86_SHIFT                                                                              (22U)
#define DSP_EVTCLR2_EC86_MASK                                                                               (0x00400000U)

#define DSP_EVTCLR2_EC87_SHIFT                                                                              (23U)
#define DSP_EVTCLR2_EC87_MASK                                                                               (0x00800000U)

#define DSP_EVTCLR2_EC88_SHIFT                                                                              (24U)
#define DSP_EVTCLR2_EC88_MASK                                                                               (0x01000000U)

#define DSP_EVTCLR2_EC89_SHIFT                                                                              (25U)
#define DSP_EVTCLR2_EC89_MASK                                                                               (0x02000000U)

#define DSP_EVTCLR2_EC90_SHIFT                                                                              (26U)
#define DSP_EVTCLR2_EC90_MASK                                                                               (0x04000000U)

#define DSP_EVTCLR2_EC91_SHIFT                                                                              (27U)
#define DSP_EVTCLR2_EC91_MASK                                                                               (0x08000000U)

#define DSP_EVTCLR2_EC92_SHIFT                                                                              (28U)
#define DSP_EVTCLR2_EC92_MASK                                                                               (0x10000000U)

#define DSP_EVTCLR2_EC93_SHIFT                                                                              (29U)
#define DSP_EVTCLR2_EC93_MASK                                                                               (0x20000000U)

#define DSP_EVTCLR2_EC94_SHIFT                                                                              (30U)
#define DSP_EVTCLR2_EC94_MASK                                                                               (0x40000000U)

#define DSP_EVTCLR2_EC95_SHIFT                                                                              (31U)
#define DSP_EVTCLR2_EC95_MASK                                                                               (0x80000000U)

#define DSP_EVTCLR3_EC96_SHIFT                                                                              (0U)
#define DSP_EVTCLR3_EC96_MASK                                                                               (0x00000001U)

#define DSP_EVTCLR3_EC97_SHIFT                                                                              (1U)
#define DSP_EVTCLR3_EC97_MASK                                                                               (0x00000002U)

#define DSP_EVTCLR3_EC98_SHIFT                                                                              (2U)
#define DSP_EVTCLR3_EC98_MASK                                                                               (0x00000004U)

#define DSP_EVTCLR3_EC99_SHIFT                                                                              (3U)
#define DSP_EVTCLR3_EC99_MASK                                                                               (0x00000008U)

#define DSP_EVTCLR3_EC100_SHIFT                                                                             (4U)
#define DSP_EVTCLR3_EC100_MASK                                                                              (0x00000010U)

#define DSP_EVTCLR3_EC101_SHIFT                                                                             (5U)
#define DSP_EVTCLR3_EC101_MASK                                                                              (0x00000020U)

#define DSP_EVTCLR3_EC102_SHIFT                                                                             (6U)
#define DSP_EVTCLR3_EC102_MASK                                                                              (0x00000040U)

#define DSP_EVTCLR3_EC103_SHIFT                                                                             (7U)
#define DSP_EVTCLR3_EC103_MASK                                                                              (0x00000080U)

#define DSP_EVTCLR3_EC104_SHIFT                                                                             (8U)
#define DSP_EVTCLR3_EC104_MASK                                                                              (0x00000100U)

#define DSP_EVTCLR3_EC105_SHIFT                                                                             (9U)
#define DSP_EVTCLR3_EC105_MASK                                                                              (0x00000200U)

#define DSP_EVTCLR3_EC106_SHIFT                                                                             (10U)
#define DSP_EVTCLR3_EC106_MASK                                                                              (0x00000400U)

#define DSP_EVTCLR3_EC107_SHIFT                                                                             (11U)
#define DSP_EVTCLR3_EC107_MASK                                                                              (0x00000800U)

#define DSP_EVTCLR3_EC108_SHIFT                                                                             (12U)
#define DSP_EVTCLR3_EC108_MASK                                                                              (0x00001000U)

#define DSP_EVTCLR3_EC109_SHIFT                                                                             (13U)
#define DSP_EVTCLR3_EC109_MASK                                                                              (0x00002000U)

#define DSP_EVTCLR3_EC110_SHIFT                                                                             (14U)
#define DSP_EVTCLR3_EC110_MASK                                                                              (0x00004000U)

#define DSP_EVTCLR3_EC111_SHIFT                                                                             (15U)
#define DSP_EVTCLR3_EC111_MASK                                                                              (0x00008000U)

#define DSP_EVTCLR3_EC112_SHIFT                                                                             (16U)
#define DSP_EVTCLR3_EC112_MASK                                                                              (0x00010000U)

#define DSP_EVTCLR3_EC113_SHIFT                                                                             (17U)
#define DSP_EVTCLR3_EC113_MASK                                                                              (0x00020000U)

#define DSP_EVTCLR3_EC114_SHIFT                                                                             (18U)
#define DSP_EVTCLR3_EC114_MASK                                                                              (0x00040000U)

#define DSP_EVTCLR3_EC115_SHIFT                                                                             (19U)
#define DSP_EVTCLR3_EC115_MASK                                                                              (0x00080000U)

#define DSP_EVTCLR3_EC116_SHIFT                                                                             (20U)
#define DSP_EVTCLR3_EC116_MASK                                                                              (0x00100000U)

#define DSP_EVTCLR3_EC117_SHIFT                                                                             (21U)
#define DSP_EVTCLR3_EC117_MASK                                                                              (0x00200000U)

#define DSP_EVTCLR3_EC118_SHIFT                                                                             (22U)
#define DSP_EVTCLR3_EC118_MASK                                                                              (0x00400000U)

#define DSP_EVTCLR3_EC119_SHIFT                                                                             (23U)
#define DSP_EVTCLR3_EC119_MASK                                                                              (0x00800000U)

#define DSP_EVTCLR3_EC120_SHIFT                                                                             (24U)
#define DSP_EVTCLR3_EC120_MASK                                                                              (0x01000000U)

#define DSP_EVTCLR3_EC121_SHIFT                                                                             (25U)
#define DSP_EVTCLR3_EC121_MASK                                                                              (0x02000000U)

#define DSP_EVTCLR3_EC122_SHIFT                                                                             (26U)
#define DSP_EVTCLR3_EC122_MASK                                                                              (0x04000000U)

#define DSP_EVTCLR3_EC123_SHIFT                                                                             (27U)
#define DSP_EVTCLR3_EC123_MASK                                                                              (0x08000000U)

#define DSP_EVTCLR3_EC124_SHIFT                                                                             (28U)
#define DSP_EVTCLR3_EC124_MASK                                                                              (0x10000000U)

#define DSP_EVTCLR3_EC125_SHIFT                                                                             (29U)
#define DSP_EVTCLR3_EC125_MASK                                                                              (0x20000000U)

#define DSP_EVTCLR3_EC126_SHIFT                                                                             (30U)
#define DSP_EVTCLR3_EC126_MASK                                                                              (0x40000000U)

#define DSP_EVTCLR3_EC127_SHIFT                                                                             (31U)
#define DSP_EVTCLR3_EC127_MASK                                                                              (0x80000000U)

#define DSP_EVTSET1_ES32_SHIFT                                                                              (0U)
#define DSP_EVTSET1_ES32_MASK                                                                               (0x00000001U)

#define DSP_EVTSET1_ES33_SHIFT                                                                              (1U)
#define DSP_EVTSET1_ES33_MASK                                                                               (0x00000002U)

#define DSP_EVTSET1_ES34_SHIFT                                                                              (2U)
#define DSP_EVTSET1_ES34_MASK                                                                               (0x00000004U)

#define DSP_EVTSET1_ES35_SHIFT                                                                              (3U)
#define DSP_EVTSET1_ES35_MASK                                                                               (0x00000008U)

#define DSP_EVTSET1_ES36_SHIFT                                                                              (4U)
#define DSP_EVTSET1_ES36_MASK                                                                               (0x00000010U)

#define DSP_EVTSET1_ES37_SHIFT                                                                              (5U)
#define DSP_EVTSET1_ES37_MASK                                                                               (0x00000020U)

#define DSP_EVTSET1_ES38_SHIFT                                                                              (6U)
#define DSP_EVTSET1_ES38_MASK                                                                               (0x00000040U)

#define DSP_EVTSET1_ES39_SHIFT                                                                              (7U)
#define DSP_EVTSET1_ES39_MASK                                                                               (0x00000080U)

#define DSP_EVTSET1_ES40_SHIFT                                                                              (8U)
#define DSP_EVTSET1_ES40_MASK                                                                               (0x00000100U)

#define DSP_EVTSET1_ES41_SHIFT                                                                              (9U)
#define DSP_EVTSET1_ES41_MASK                                                                               (0x00000200U)

#define DSP_EVTSET1_ES42_SHIFT                                                                              (10U)
#define DSP_EVTSET1_ES42_MASK                                                                               (0x00000400U)

#define DSP_EVTSET1_ES43_SHIFT                                                                              (11U)
#define DSP_EVTSET1_ES43_MASK                                                                               (0x00000800U)

#define DSP_EVTSET1_ES44_SHIFT                                                                              (12U)
#define DSP_EVTSET1_ES44_MASK                                                                               (0x00001000U)

#define DSP_EVTSET1_ES45_SHIFT                                                                              (13U)
#define DSP_EVTSET1_ES45_MASK                                                                               (0x00002000U)

#define DSP_EVTSET1_ES46_SHIFT                                                                              (14U)
#define DSP_EVTSET1_ES46_MASK                                                                               (0x00004000U)

#define DSP_EVTSET1_ES47_SHIFT                                                                              (15U)
#define DSP_EVTSET1_ES47_MASK                                                                               (0x00008000U)

#define DSP_EVTSET1_ES48_SHIFT                                                                              (16U)
#define DSP_EVTSET1_ES48_MASK                                                                               (0x00010000U)

#define DSP_EVTSET1_ES49_SHIFT                                                                              (17U)
#define DSP_EVTSET1_ES49_MASK                                                                               (0x00020000U)

#define DSP_EVTSET1_ES50_SHIFT                                                                              (18U)
#define DSP_EVTSET1_ES50_MASK                                                                               (0x00040000U)

#define DSP_EVTSET1_ES51_SHIFT                                                                              (19U)
#define DSP_EVTSET1_ES51_MASK                                                                               (0x00080000U)

#define DSP_EVTSET1_ES52_SHIFT                                                                              (20U)
#define DSP_EVTSET1_ES52_MASK                                                                               (0x00100000U)

#define DSP_EVTSET1_ES53_SHIFT                                                                              (21U)
#define DSP_EVTSET1_ES53_MASK                                                                               (0x00200000U)

#define DSP_EVTSET1_ES54_SHIFT                                                                              (22U)
#define DSP_EVTSET1_ES54_MASK                                                                               (0x00400000U)

#define DSP_EVTSET1_ES55_SHIFT                                                                              (23U)
#define DSP_EVTSET1_ES55_MASK                                                                               (0x00800000U)

#define DSP_EVTSET1_ES56_SHIFT                                                                              (24U)
#define DSP_EVTSET1_ES56_MASK                                                                               (0x01000000U)

#define DSP_EVTSET1_ES57_SHIFT                                                                              (25U)
#define DSP_EVTSET1_ES57_MASK                                                                               (0x02000000U)

#define DSP_EVTSET1_ES58_SHIFT                                                                              (26U)
#define DSP_EVTSET1_ES58_MASK                                                                               (0x04000000U)

#define DSP_EVTSET1_ES59_SHIFT                                                                              (27U)
#define DSP_EVTSET1_ES59_MASK                                                                               (0x08000000U)

#define DSP_EVTSET1_ES60_SHIFT                                                                              (28U)
#define DSP_EVTSET1_ES60_MASK                                                                               (0x10000000U)

#define DSP_EVTSET1_ES61_SHIFT                                                                              (29U)
#define DSP_EVTSET1_ES61_MASK                                                                               (0x20000000U)

#define DSP_EVTSET1_ES62_SHIFT                                                                              (30U)
#define DSP_EVTSET1_ES62_MASK                                                                               (0x40000000U)

#define DSP_EVTSET1_ES63_SHIFT                                                                              (31U)
#define DSP_EVTSET1_ES63_MASK                                                                               (0x80000000U)

#define DSP_EVTSET2_ES64_SHIFT                                                                              (0U)
#define DSP_EVTSET2_ES64_MASK                                                                               (0x00000001U)

#define DSP_EVTSET2_ES65_SHIFT                                                                              (1U)
#define DSP_EVTSET2_ES65_MASK                                                                               (0x00000002U)

#define DSP_EVTSET2_ES66_SHIFT                                                                              (2U)
#define DSP_EVTSET2_ES66_MASK                                                                               (0x00000004U)

#define DSP_EVTSET2_ES67_SHIFT                                                                              (3U)
#define DSP_EVTSET2_ES67_MASK                                                                               (0x00000008U)

#define DSP_EVTSET2_ES68_SHIFT                                                                              (4U)
#define DSP_EVTSET2_ES68_MASK                                                                               (0x00000010U)

#define DSP_EVTSET2_ES69_SHIFT                                                                              (5U)
#define DSP_EVTSET2_ES69_MASK                                                                               (0x00000020U)

#define DSP_EVTSET2_ES70_SHIFT                                                                              (6U)
#define DSP_EVTSET2_ES70_MASK                                                                               (0x00000040U)

#define DSP_EVTSET2_ES71_SHIFT                                                                              (7U)
#define DSP_EVTSET2_ES71_MASK                                                                               (0x00000080U)

#define DSP_EVTSET2_ES72_SHIFT                                                                              (8U)
#define DSP_EVTSET2_ES72_MASK                                                                               (0x00000100U)

#define DSP_EVTSET2_ES73_SHIFT                                                                              (9U)
#define DSP_EVTSET2_ES73_MASK                                                                               (0x00000200U)

#define DSP_EVTSET2_ES74_SHIFT                                                                              (10U)
#define DSP_EVTSET2_ES74_MASK                                                                               (0x00000400U)

#define DSP_EVTSET2_ES75_SHIFT                                                                              (11U)
#define DSP_EVTSET2_ES75_MASK                                                                               (0x00000800U)

#define DSP_EVTSET2_ES76_SHIFT                                                                              (12U)
#define DSP_EVTSET2_ES76_MASK                                                                               (0x00001000U)

#define DSP_EVTSET2_ES77_SHIFT                                                                              (13U)
#define DSP_EVTSET2_ES77_MASK                                                                               (0x00002000U)

#define DSP_EVTSET2_ES78_SHIFT                                                                              (14U)
#define DSP_EVTSET2_ES78_MASK                                                                               (0x00004000U)

#define DSP_EVTSET2_ES79_SHIFT                                                                              (15U)
#define DSP_EVTSET2_ES79_MASK                                                                               (0x00008000U)

#define DSP_EVTSET2_ES80_SHIFT                                                                              (16U)
#define DSP_EVTSET2_ES80_MASK                                                                               (0x00010000U)

#define DSP_EVTSET2_ES81_SHIFT                                                                              (17U)
#define DSP_EVTSET2_ES81_MASK                                                                               (0x00020000U)

#define DSP_EVTSET2_ES82_SHIFT                                                                              (18U)
#define DSP_EVTSET2_ES82_MASK                                                                               (0x00040000U)

#define DSP_EVTSET2_ES83_SHIFT                                                                              (19U)
#define DSP_EVTSET2_ES83_MASK                                                                               (0x00080000U)

#define DSP_EVTSET2_ES84_SHIFT                                                                              (20U)
#define DSP_EVTSET2_ES84_MASK                                                                               (0x00100000U)

#define DSP_EVTSET2_ES85_SHIFT                                                                              (21U)
#define DSP_EVTSET2_ES85_MASK                                                                               (0x00200000U)

#define DSP_EVTSET2_ES86_SHIFT                                                                              (22U)
#define DSP_EVTSET2_ES86_MASK                                                                               (0x00400000U)

#define DSP_EVTSET2_ES87_SHIFT                                                                              (23U)
#define DSP_EVTSET2_ES87_MASK                                                                               (0x00800000U)

#define DSP_EVTSET2_ES88_SHIFT                                                                              (24U)
#define DSP_EVTSET2_ES88_MASK                                                                               (0x01000000U)

#define DSP_EVTSET2_ES89_SHIFT                                                                              (25U)
#define DSP_EVTSET2_ES89_MASK                                                                               (0x02000000U)

#define DSP_EVTSET2_ES90_SHIFT                                                                              (26U)
#define DSP_EVTSET2_ES90_MASK                                                                               (0x04000000U)

#define DSP_EVTSET2_ES91_SHIFT                                                                              (27U)
#define DSP_EVTSET2_ES91_MASK                                                                               (0x08000000U)

#define DSP_EVTSET2_ES92_SHIFT                                                                              (28U)
#define DSP_EVTSET2_ES92_MASK                                                                               (0x10000000U)

#define DSP_EVTSET2_ES93_SHIFT                                                                              (29U)
#define DSP_EVTSET2_ES93_MASK                                                                               (0x20000000U)

#define DSP_EVTSET2_ES94_SHIFT                                                                              (30U)
#define DSP_EVTSET2_ES94_MASK                                                                               (0x40000000U)

#define DSP_EVTSET2_ES95_SHIFT                                                                              (31U)
#define DSP_EVTSET2_ES95_MASK                                                                               (0x80000000U)

#define DSP_EVTSET3_ES96_SHIFT                                                                              (0U)
#define DSP_EVTSET3_ES96_MASK                                                                               (0x00000001U)

#define DSP_EVTSET3_ES97_SHIFT                                                                              (1U)
#define DSP_EVTSET3_ES97_MASK                                                                               (0x00000002U)

#define DSP_EVTSET3_ES98_SHIFT                                                                              (2U)
#define DSP_EVTSET3_ES98_MASK                                                                               (0x00000004U)

#define DSP_EVTSET3_ES99_SHIFT                                                                              (3U)
#define DSP_EVTSET3_ES99_MASK                                                                               (0x00000008U)

#define DSP_EVTSET3_ES100_SHIFT                                                                             (4U)
#define DSP_EVTSET3_ES100_MASK                                                                              (0x00000010U)

#define DSP_EVTSET3_ES101_SHIFT                                                                             (5U)
#define DSP_EVTSET3_ES101_MASK                                                                              (0x00000020U)

#define DSP_EVTSET3_ES102_SHIFT                                                                             (6U)
#define DSP_EVTSET3_ES102_MASK                                                                              (0x00000040U)

#define DSP_EVTSET3_ES103_SHIFT                                                                             (7U)
#define DSP_EVTSET3_ES103_MASK                                                                              (0x00000080U)

#define DSP_EVTSET3_ES104_SHIFT                                                                             (8U)
#define DSP_EVTSET3_ES104_MASK                                                                              (0x00000100U)

#define DSP_EVTSET3_ES105_SHIFT                                                                             (9U)
#define DSP_EVTSET3_ES105_MASK                                                                              (0x00000200U)

#define DSP_EVTSET3_ES106_SHIFT                                                                             (10U)
#define DSP_EVTSET3_ES106_MASK                                                                              (0x00000400U)

#define DSP_EVTSET3_ES107_SHIFT                                                                             (11U)
#define DSP_EVTSET3_ES107_MASK                                                                              (0x00000800U)

#define DSP_EVTSET3_ES108_SHIFT                                                                             (12U)
#define DSP_EVTSET3_ES108_MASK                                                                              (0x00001000U)

#define DSP_EVTSET3_ES109_SHIFT                                                                             (13U)
#define DSP_EVTSET3_ES109_MASK                                                                              (0x00002000U)

#define DSP_EVTSET3_ES110_SHIFT                                                                             (14U)
#define DSP_EVTSET3_ES110_MASK                                                                              (0x00004000U)

#define DSP_EVTSET3_ES111_SHIFT                                                                             (15U)
#define DSP_EVTSET3_ES111_MASK                                                                              (0x00008000U)

#define DSP_EVTSET3_ES112_SHIFT                                                                             (16U)
#define DSP_EVTSET3_ES112_MASK                                                                              (0x00010000U)

#define DSP_EVTSET3_ES113_SHIFT                                                                             (17U)
#define DSP_EVTSET3_ES113_MASK                                                                              (0x00020000U)

#define DSP_EVTSET3_ES114_SHIFT                                                                             (18U)
#define DSP_EVTSET3_ES114_MASK                                                                              (0x00040000U)

#define DSP_EVTSET3_ES115_SHIFT                                                                             (19U)
#define DSP_EVTSET3_ES115_MASK                                                                              (0x00080000U)

#define DSP_EVTSET3_ES116_SHIFT                                                                             (20U)
#define DSP_EVTSET3_ES116_MASK                                                                              (0x00100000U)

#define DSP_EVTSET3_ES117_SHIFT                                                                             (21U)
#define DSP_EVTSET3_ES117_MASK                                                                              (0x00200000U)

#define DSP_EVTSET3_ES118_SHIFT                                                                             (22U)
#define DSP_EVTSET3_ES118_MASK                                                                              (0x00400000U)

#define DSP_EVTSET3_ES119_SHIFT                                                                             (23U)
#define DSP_EVTSET3_ES119_MASK                                                                              (0x00800000U)

#define DSP_EVTSET3_ES120_SHIFT                                                                             (24U)
#define DSP_EVTSET3_ES120_MASK                                                                              (0x01000000U)

#define DSP_EVTSET3_ES121_SHIFT                                                                             (25U)
#define DSP_EVTSET3_ES121_MASK                                                                              (0x02000000U)

#define DSP_EVTSET3_ES122_SHIFT                                                                             (26U)
#define DSP_EVTSET3_ES122_MASK                                                                              (0x04000000U)

#define DSP_EVTSET3_ES123_SHIFT                                                                             (27U)
#define DSP_EVTSET3_ES123_MASK                                                                              (0x08000000U)

#define DSP_EVTSET3_ES124_SHIFT                                                                             (28U)
#define DSP_EVTSET3_ES124_MASK                                                                              (0x10000000U)

#define DSP_EVTSET3_ES125_SHIFT                                                                             (29U)
#define DSP_EVTSET3_ES125_MASK                                                                              (0x20000000U)

#define DSP_EVTSET3_ES126_SHIFT                                                                             (30U)
#define DSP_EVTSET3_ES126_MASK                                                                              (0x40000000U)

#define DSP_EVTSET3_ES127_SHIFT                                                                             (31U)
#define DSP_EVTSET3_ES127_MASK                                                                              (0x80000000U)

#define DSP_EVTMASK1_EM32_SHIFT                                                                             (0U)
#define DSP_EVTMASK1_EM32_MASK                                                                              (0x00000001U)

#define DSP_EVTMASK1_EM33_SHIFT                                                                             (1U)
#define DSP_EVTMASK1_EM33_MASK                                                                              (0x00000002U)

#define DSP_EVTMASK1_EM34_SHIFT                                                                             (2U)
#define DSP_EVTMASK1_EM34_MASK                                                                              (0x00000004U)

#define DSP_EVTMASK1_EM35_SHIFT                                                                             (3U)
#define DSP_EVTMASK1_EM35_MASK                                                                              (0x00000008U)

#define DSP_EVTMASK1_EM36_SHIFT                                                                             (4U)
#define DSP_EVTMASK1_EM36_MASK                                                                              (0x00000010U)

#define DSP_EVTMASK1_EM37_SHIFT                                                                             (5U)
#define DSP_EVTMASK1_EM37_MASK                                                                              (0x00000020U)

#define DSP_EVTMASK1_EM38_SHIFT                                                                             (6U)
#define DSP_EVTMASK1_EM38_MASK                                                                              (0x00000040U)

#define DSP_EVTMASK1_EM39_SHIFT                                                                             (7U)
#define DSP_EVTMASK1_EM39_MASK                                                                              (0x00000080U)

#define DSP_EVTMASK1_EM40_SHIFT                                                                             (8U)
#define DSP_EVTMASK1_EM40_MASK                                                                              (0x00000100U)

#define DSP_EVTMASK1_EM41_SHIFT                                                                             (9U)
#define DSP_EVTMASK1_EM41_MASK                                                                              (0x00000200U)

#define DSP_EVTMASK1_EM42_SHIFT                                                                             (10U)
#define DSP_EVTMASK1_EM42_MASK                                                                              (0x00000400U)

#define DSP_EVTMASK1_EM43_SHIFT                                                                             (11U)
#define DSP_EVTMASK1_EM43_MASK                                                                              (0x00000800U)

#define DSP_EVTMASK1_EM44_SHIFT                                                                             (12U)
#define DSP_EVTMASK1_EM44_MASK                                                                              (0x00001000U)

#define DSP_EVTMASK1_EM45_SHIFT                                                                             (13U)
#define DSP_EVTMASK1_EM45_MASK                                                                              (0x00002000U)

#define DSP_EVTMASK1_EM46_SHIFT                                                                             (14U)
#define DSP_EVTMASK1_EM46_MASK                                                                              (0x00004000U)

#define DSP_EVTMASK1_EM47_SHIFT                                                                             (15U)
#define DSP_EVTMASK1_EM47_MASK                                                                              (0x00008000U)

#define DSP_EVTMASK1_EM48_SHIFT                                                                             (16U)
#define DSP_EVTMASK1_EM48_MASK                                                                              (0x00010000U)

#define DSP_EVTMASK1_EM49_SHIFT                                                                             (17U)
#define DSP_EVTMASK1_EM49_MASK                                                                              (0x00020000U)

#define DSP_EVTMASK1_EM50_SHIFT                                                                             (18U)
#define DSP_EVTMASK1_EM50_MASK                                                                              (0x00040000U)

#define DSP_EVTMASK1_EM51_SHIFT                                                                             (19U)
#define DSP_EVTMASK1_EM51_MASK                                                                              (0x00080000U)

#define DSP_EVTMASK1_EM52_SHIFT                                                                             (20U)
#define DSP_EVTMASK1_EM52_MASK                                                                              (0x00100000U)

#define DSP_EVTMASK1_EM53_SHIFT                                                                             (21U)
#define DSP_EVTMASK1_EM53_MASK                                                                              (0x00200000U)

#define DSP_EVTMASK1_EM54_SHIFT                                                                             (22U)
#define DSP_EVTMASK1_EM54_MASK                                                                              (0x00400000U)

#define DSP_EVTMASK1_EM55_SHIFT                                                                             (23U)
#define DSP_EVTMASK1_EM55_MASK                                                                              (0x00800000U)

#define DSP_EVTMASK1_EM56_SHIFT                                                                             (24U)
#define DSP_EVTMASK1_EM56_MASK                                                                              (0x01000000U)

#define DSP_EVTMASK1_EM57_SHIFT                                                                             (25U)
#define DSP_EVTMASK1_EM57_MASK                                                                              (0x02000000U)

#define DSP_EVTMASK1_EM58_SHIFT                                                                             (26U)
#define DSP_EVTMASK1_EM58_MASK                                                                              (0x04000000U)

#define DSP_EVTMASK1_EM59_SHIFT                                                                             (27U)
#define DSP_EVTMASK1_EM59_MASK                                                                              (0x08000000U)

#define DSP_EVTMASK1_EM60_SHIFT                                                                             (28U)
#define DSP_EVTMASK1_EM60_MASK                                                                              (0x10000000U)

#define DSP_EVTMASK1_EM61_SHIFT                                                                             (29U)
#define DSP_EVTMASK1_EM61_MASK                                                                              (0x20000000U)

#define DSP_EVTMASK1_EM62_SHIFT                                                                             (30U)
#define DSP_EVTMASK1_EM62_MASK                                                                              (0x40000000U)

#define DSP_EVTMASK1_EM63_SHIFT                                                                             (31U)
#define DSP_EVTMASK1_EM63_MASK                                                                              (0x80000000U)

#define DSP_EVTMASK2_EM64_SHIFT                                                                             (0U)
#define DSP_EVTMASK2_EM64_MASK                                                                              (0x00000001U)

#define DSP_EVTMASK2_EM65_SHIFT                                                                             (1U)
#define DSP_EVTMASK2_EM65_MASK                                                                              (0x00000002U)

#define DSP_EVTMASK2_EM66_SHIFT                                                                             (2U)
#define DSP_EVTMASK2_EM66_MASK                                                                              (0x00000004U)

#define DSP_EVTMASK2_EM67_SHIFT                                                                             (3U)
#define DSP_EVTMASK2_EM67_MASK                                                                              (0x00000008U)

#define DSP_EVTMASK2_EM68_SHIFT                                                                             (4U)
#define DSP_EVTMASK2_EM68_MASK                                                                              (0x00000010U)

#define DSP_EVTMASK2_EM69_SHIFT                                                                             (5U)
#define DSP_EVTMASK2_EM69_MASK                                                                              (0x00000020U)

#define DSP_EVTMASK2_EM70_SHIFT                                                                             (6U)
#define DSP_EVTMASK2_EM70_MASK                                                                              (0x00000040U)

#define DSP_EVTMASK2_EM71_SHIFT                                                                             (7U)
#define DSP_EVTMASK2_EM71_MASK                                                                              (0x00000080U)

#define DSP_EVTMASK2_EM72_SHIFT                                                                             (8U)
#define DSP_EVTMASK2_EM72_MASK                                                                              (0x00000100U)

#define DSP_EVTMASK2_EM73_SHIFT                                                                             (9U)
#define DSP_EVTMASK2_EM73_MASK                                                                              (0x00000200U)

#define DSP_EVTMASK2_EM74_SHIFT                                                                             (10U)
#define DSP_EVTMASK2_EM74_MASK                                                                              (0x00000400U)

#define DSP_EVTMASK2_EM75_SHIFT                                                                             (11U)
#define DSP_EVTMASK2_EM75_MASK                                                                              (0x00000800U)

#define DSP_EVTMASK2_EM76_SHIFT                                                                             (12U)
#define DSP_EVTMASK2_EM76_MASK                                                                              (0x00001000U)

#define DSP_EVTMASK2_EM77_SHIFT                                                                             (13U)
#define DSP_EVTMASK2_EM77_MASK                                                                              (0x00002000U)

#define DSP_EVTMASK2_EM78_SHIFT                                                                             (14U)
#define DSP_EVTMASK2_EM78_MASK                                                                              (0x00004000U)

#define DSP_EVTMASK2_EM79_SHIFT                                                                             (15U)
#define DSP_EVTMASK2_EM79_MASK                                                                              (0x00008000U)

#define DSP_EVTMASK2_EM80_SHIFT                                                                             (16U)
#define DSP_EVTMASK2_EM80_MASK                                                                              (0x00010000U)

#define DSP_EVTMASK2_EM81_SHIFT                                                                             (17U)
#define DSP_EVTMASK2_EM81_MASK                                                                              (0x00020000U)

#define DSP_EVTMASK2_EM82_SHIFT                                                                             (18U)
#define DSP_EVTMASK2_EM82_MASK                                                                              (0x00040000U)

#define DSP_EVTMASK2_EM83_SHIFT                                                                             (19U)
#define DSP_EVTMASK2_EM83_MASK                                                                              (0x00080000U)

#define DSP_EVTMASK2_EM84_SHIFT                                                                             (20U)
#define DSP_EVTMASK2_EM84_MASK                                                                              (0x00100000U)

#define DSP_EVTMASK2_EM85_SHIFT                                                                             (21U)
#define DSP_EVTMASK2_EM85_MASK                                                                              (0x00200000U)

#define DSP_EVTMASK2_EM86_SHIFT                                                                             (22U)
#define DSP_EVTMASK2_EM86_MASK                                                                              (0x00400000U)

#define DSP_EVTMASK2_EM87_SHIFT                                                                             (23U)
#define DSP_EVTMASK2_EM87_MASK                                                                              (0x00800000U)

#define DSP_EVTMASK2_EM88_SHIFT                                                                             (24U)
#define DSP_EVTMASK2_EM88_MASK                                                                              (0x01000000U)

#define DSP_EVTMASK2_EM89_SHIFT                                                                             (25U)
#define DSP_EVTMASK2_EM89_MASK                                                                              (0x02000000U)

#define DSP_EVTMASK2_EM90_SHIFT                                                                             (26U)
#define DSP_EVTMASK2_EM90_MASK                                                                              (0x04000000U)

#define DSP_EVTMASK2_EM91_SHIFT                                                                             (27U)
#define DSP_EVTMASK2_EM91_MASK                                                                              (0x08000000U)

#define DSP_EVTMASK2_EM92_SHIFT                                                                             (28U)
#define DSP_EVTMASK2_EM92_MASK                                                                              (0x10000000U)

#define DSP_EVTMASK2_EM93_SHIFT                                                                             (29U)
#define DSP_EVTMASK2_EM93_MASK                                                                              (0x20000000U)

#define DSP_EVTMASK2_EM94_SHIFT                                                                             (30U)
#define DSP_EVTMASK2_EM94_MASK                                                                              (0x40000000U)

#define DSP_EVTMASK2_EM95_SHIFT                                                                             (31U)
#define DSP_EVTMASK2_EM95_MASK                                                                              (0x80000000U)

#define DSP_EVTMASK3_EM96_SHIFT                                                                             (0U)
#define DSP_EVTMASK3_EM96_MASK                                                                              (0x00000001U)

#define DSP_EVTMASK3_EM97_SHIFT                                                                             (1U)
#define DSP_EVTMASK3_EM97_MASK                                                                              (0x00000002U)

#define DSP_EVTMASK3_EM98_SHIFT                                                                             (2U)
#define DSP_EVTMASK3_EM98_MASK                                                                              (0x00000004U)

#define DSP_EVTMASK3_EM99_SHIFT                                                                             (3U)
#define DSP_EVTMASK3_EM99_MASK                                                                              (0x00000008U)

#define DSP_EVTMASK3_EM100_SHIFT                                                                            (4U)
#define DSP_EVTMASK3_EM100_MASK                                                                             (0x00000010U)

#define DSP_EVTMASK3_EM101_SHIFT                                                                            (5U)
#define DSP_EVTMASK3_EM101_MASK                                                                             (0x00000020U)

#define DSP_EVTMASK3_EM102_SHIFT                                                                            (6U)
#define DSP_EVTMASK3_EM102_MASK                                                                             (0x00000040U)

#define DSP_EVTMASK3_EM103_SHIFT                                                                            (7U)
#define DSP_EVTMASK3_EM103_MASK                                                                             (0x00000080U)

#define DSP_EVTMASK3_EM104_SHIFT                                                                            (8U)
#define DSP_EVTMASK3_EM104_MASK                                                                             (0x00000100U)

#define DSP_EVTMASK3_EM105_SHIFT                                                                            (9U)
#define DSP_EVTMASK3_EM105_MASK                                                                             (0x00000200U)

#define DSP_EVTMASK3_EM106_SHIFT                                                                            (10U)
#define DSP_EVTMASK3_EM106_MASK                                                                             (0x00000400U)

#define DSP_EVTMASK3_EM107_SHIFT                                                                            (11U)
#define DSP_EVTMASK3_EM107_MASK                                                                             (0x00000800U)

#define DSP_EVTMASK3_EM108_SHIFT                                                                            (12U)
#define DSP_EVTMASK3_EM108_MASK                                                                             (0x00001000U)

#define DSP_EVTMASK3_EM109_SHIFT                                                                            (13U)
#define DSP_EVTMASK3_EM109_MASK                                                                             (0x00002000U)

#define DSP_EVTMASK3_EM110_SHIFT                                                                            (14U)
#define DSP_EVTMASK3_EM110_MASK                                                                             (0x00004000U)

#define DSP_EVTMASK3_EM111_SHIFT                                                                            (15U)
#define DSP_EVTMASK3_EM111_MASK                                                                             (0x00008000U)

#define DSP_EVTMASK3_EM112_SHIFT                                                                            (16U)
#define DSP_EVTMASK3_EM112_MASK                                                                             (0x00010000U)

#define DSP_EVTMASK3_EM113_SHIFT                                                                            (17U)
#define DSP_EVTMASK3_EM113_MASK                                                                             (0x00020000U)

#define DSP_EVTMASK3_EM114_SHIFT                                                                            (18U)
#define DSP_EVTMASK3_EM114_MASK                                                                             (0x00040000U)

#define DSP_EVTMASK3_EM115_SHIFT                                                                            (19U)
#define DSP_EVTMASK3_EM115_MASK                                                                             (0x00080000U)

#define DSP_EVTMASK3_EM116_SHIFT                                                                            (20U)
#define DSP_EVTMASK3_EM116_MASK                                                                             (0x00100000U)

#define DSP_EVTMASK3_EM117_SHIFT                                                                            (21U)
#define DSP_EVTMASK3_EM117_MASK                                                                             (0x00200000U)

#define DSP_EVTMASK3_EM118_SHIFT                                                                            (22U)
#define DSP_EVTMASK3_EM118_MASK                                                                             (0x00400000U)

#define DSP_EVTMASK3_EM119_SHIFT                                                                            (23U)
#define DSP_EVTMASK3_EM119_MASK                                                                             (0x00800000U)

#define DSP_EVTMASK3_EM120_SHIFT                                                                            (24U)
#define DSP_EVTMASK3_EM120_MASK                                                                             (0x01000000U)

#define DSP_EVTMASK3_EM121_SHIFT                                                                            (25U)
#define DSP_EVTMASK3_EM121_MASK                                                                             (0x02000000U)

#define DSP_EVTMASK3_EM122_SHIFT                                                                            (26U)
#define DSP_EVTMASK3_EM122_MASK                                                                             (0x04000000U)

#define DSP_EVTMASK3_EM123_SHIFT                                                                            (27U)
#define DSP_EVTMASK3_EM123_MASK                                                                             (0x08000000U)

#define DSP_EVTMASK3_EM124_SHIFT                                                                            (28U)
#define DSP_EVTMASK3_EM124_MASK                                                                             (0x10000000U)

#define DSP_EVTMASK3_EM125_SHIFT                                                                            (29U)
#define DSP_EVTMASK3_EM125_MASK                                                                             (0x20000000U)

#define DSP_EVTMASK3_EM126_SHIFT                                                                            (30U)
#define DSP_EVTMASK3_EM126_MASK                                                                             (0x40000000U)

#define DSP_EVTMASK3_EM127_SHIFT                                                                            (31U)
#define DSP_EVTMASK3_EM127_MASK                                                                             (0x80000000U)

#define DSP_MEVTFLAG1_MEF32_SHIFT                                                                           (0U)
#define DSP_MEVTFLAG1_MEF32_MASK                                                                            (0x00000001U)

#define DSP_MEVTFLAG1_MEF33_SHIFT                                                                           (1U)
#define DSP_MEVTFLAG1_MEF33_MASK                                                                            (0x00000002U)

#define DSP_MEVTFLAG1_MEF34_SHIFT                                                                           (2U)
#define DSP_MEVTFLAG1_MEF34_MASK                                                                            (0x00000004U)

#define DSP_MEVTFLAG1_MEF35_SHIFT                                                                           (3U)
#define DSP_MEVTFLAG1_MEF35_MASK                                                                            (0x00000008U)

#define DSP_MEVTFLAG1_MEF36_SHIFT                                                                           (4U)
#define DSP_MEVTFLAG1_MEF36_MASK                                                                            (0x00000010U)

#define DSP_MEVTFLAG1_MEF37_SHIFT                                                                           (5U)
#define DSP_MEVTFLAG1_MEF37_MASK                                                                            (0x00000020U)

#define DSP_MEVTFLAG1_MEF38_SHIFT                                                                           (6U)
#define DSP_MEVTFLAG1_MEF38_MASK                                                                            (0x00000040U)

#define DSP_MEVTFLAG1_MEF39_SHIFT                                                                           (7U)
#define DSP_MEVTFLAG1_MEF39_MASK                                                                            (0x00000080U)

#define DSP_MEVTFLAG1_MEF40_SHIFT                                                                           (8U)
#define DSP_MEVTFLAG1_MEF40_MASK                                                                            (0x00000100U)

#define DSP_MEVTFLAG1_MEF41_SHIFT                                                                           (9U)
#define DSP_MEVTFLAG1_MEF41_MASK                                                                            (0x00000200U)

#define DSP_MEVTFLAG1_MEF42_SHIFT                                                                           (10U)
#define DSP_MEVTFLAG1_MEF42_MASK                                                                            (0x00000400U)

#define DSP_MEVTFLAG1_MEF43_SHIFT                                                                           (11U)
#define DSP_MEVTFLAG1_MEF43_MASK                                                                            (0x00000800U)

#define DSP_MEVTFLAG1_MEF44_SHIFT                                                                           (12U)
#define DSP_MEVTFLAG1_MEF44_MASK                                                                            (0x00001000U)

#define DSP_MEVTFLAG1_MEF45_SHIFT                                                                           (13U)
#define DSP_MEVTFLAG1_MEF45_MASK                                                                            (0x00002000U)

#define DSP_MEVTFLAG1_MEF46_SHIFT                                                                           (14U)
#define DSP_MEVTFLAG1_MEF46_MASK                                                                            (0x00004000U)

#define DSP_MEVTFLAG1_MEF47_SHIFT                                                                           (15U)
#define DSP_MEVTFLAG1_MEF47_MASK                                                                            (0x00008000U)

#define DSP_MEVTFLAG1_MEF48_SHIFT                                                                           (16U)
#define DSP_MEVTFLAG1_MEF48_MASK                                                                            (0x00010000U)

#define DSP_MEVTFLAG1_MEF49_SHIFT                                                                           (17U)
#define DSP_MEVTFLAG1_MEF49_MASK                                                                            (0x00020000U)

#define DSP_MEVTFLAG1_MEF50_SHIFT                                                                           (18U)
#define DSP_MEVTFLAG1_MEF50_MASK                                                                            (0x00040000U)

#define DSP_MEVTFLAG1_MEF51_SHIFT                                                                           (19U)
#define DSP_MEVTFLAG1_MEF51_MASK                                                                            (0x00080000U)

#define DSP_MEVTFLAG1_MEF52_SHIFT                                                                           (20U)
#define DSP_MEVTFLAG1_MEF52_MASK                                                                            (0x00100000U)

#define DSP_MEVTFLAG1_MEF53_SHIFT                                                                           (21U)
#define DSP_MEVTFLAG1_MEF53_MASK                                                                            (0x00200000U)

#define DSP_MEVTFLAG1_MEF54_SHIFT                                                                           (22U)
#define DSP_MEVTFLAG1_MEF54_MASK                                                                            (0x00400000U)

#define DSP_MEVTFLAG1_MEF55_SHIFT                                                                           (23U)
#define DSP_MEVTFLAG1_MEF55_MASK                                                                            (0x00800000U)

#define DSP_MEVTFLAG1_MEF56_SHIFT                                                                           (24U)
#define DSP_MEVTFLAG1_MEF56_MASK                                                                            (0x01000000U)

#define DSP_MEVTFLAG1_MEF57_SHIFT                                                                           (25U)
#define DSP_MEVTFLAG1_MEF57_MASK                                                                            (0x02000000U)

#define DSP_MEVTFLAG1_MEF58_SHIFT                                                                           (26U)
#define DSP_MEVTFLAG1_MEF58_MASK                                                                            (0x04000000U)

#define DSP_MEVTFLAG1_MEF59_SHIFT                                                                           (27U)
#define DSP_MEVTFLAG1_MEF59_MASK                                                                            (0x08000000U)

#define DSP_MEVTFLAG1_MEF60_SHIFT                                                                           (28U)
#define DSP_MEVTFLAG1_MEF60_MASK                                                                            (0x10000000U)

#define DSP_MEVTFLAG1_MEF61_SHIFT                                                                           (29U)
#define DSP_MEVTFLAG1_MEF61_MASK                                                                            (0x20000000U)

#define DSP_MEVTFLAG1_MEF62_SHIFT                                                                           (30U)
#define DSP_MEVTFLAG1_MEF62_MASK                                                                            (0x40000000U)

#define DSP_MEVTFLAG1_MEF63_SHIFT                                                                           (31U)
#define DSP_MEVTFLAG1_MEF63_MASK                                                                            (0x80000000U)

#define DSP_MEVTFLAG2_MEF64_SHIFT                                                                           (0U)
#define DSP_MEVTFLAG2_MEF64_MASK                                                                            (0x00000001U)

#define DSP_MEVTFLAG2_MEF65_SHIFT                                                                           (1U)
#define DSP_MEVTFLAG2_MEF65_MASK                                                                            (0x00000002U)

#define DSP_MEVTFLAG2_MEF66_SHIFT                                                                           (2U)
#define DSP_MEVTFLAG2_MEF66_MASK                                                                            (0x00000004U)

#define DSP_MEVTFLAG2_MEF67_SHIFT                                                                           (3U)
#define DSP_MEVTFLAG2_MEF67_MASK                                                                            (0x00000008U)

#define DSP_MEVTFLAG2_MEF68_SHIFT                                                                           (4U)
#define DSP_MEVTFLAG2_MEF68_MASK                                                                            (0x00000010U)

#define DSP_MEVTFLAG2_MEF69_SHIFT                                                                           (5U)
#define DSP_MEVTFLAG2_MEF69_MASK                                                                            (0x00000020U)

#define DSP_MEVTFLAG2_MEF70_SHIFT                                                                           (6U)
#define DSP_MEVTFLAG2_MEF70_MASK                                                                            (0x00000040U)

#define DSP_MEVTFLAG2_MEF71_SHIFT                                                                           (7U)
#define DSP_MEVTFLAG2_MEF71_MASK                                                                            (0x00000080U)

#define DSP_MEVTFLAG2_MEF72_SHIFT                                                                           (8U)
#define DSP_MEVTFLAG2_MEF72_MASK                                                                            (0x00000100U)

#define DSP_MEVTFLAG2_MEF73_SHIFT                                                                           (9U)
#define DSP_MEVTFLAG2_MEF73_MASK                                                                            (0x00000200U)

#define DSP_MEVTFLAG2_MEF74_SHIFT                                                                           (10U)
#define DSP_MEVTFLAG2_MEF74_MASK                                                                            (0x00000400U)

#define DSP_MEVTFLAG2_MEF75_SHIFT                                                                           (11U)
#define DSP_MEVTFLAG2_MEF75_MASK                                                                            (0x00000800U)

#define DSP_MEVTFLAG2_MEF76_SHIFT                                                                           (12U)
#define DSP_MEVTFLAG2_MEF76_MASK                                                                            (0x00001000U)

#define DSP_MEVTFLAG2_MEF77_SHIFT                                                                           (13U)
#define DSP_MEVTFLAG2_MEF77_MASK                                                                            (0x00002000U)

#define DSP_MEVTFLAG2_MEF78_SHIFT                                                                           (14U)
#define DSP_MEVTFLAG2_MEF78_MASK                                                                            (0x00004000U)

#define DSP_MEVTFLAG2_MEF79_SHIFT                                                                           (15U)
#define DSP_MEVTFLAG2_MEF79_MASK                                                                            (0x00008000U)

#define DSP_MEVTFLAG2_MEF80_SHIFT                                                                           (16U)
#define DSP_MEVTFLAG2_MEF80_MASK                                                                            (0x00010000U)

#define DSP_MEVTFLAG2_MEF81_SHIFT                                                                           (17U)
#define DSP_MEVTFLAG2_MEF81_MASK                                                                            (0x00020000U)

#define DSP_MEVTFLAG2_MEF82_SHIFT                                                                           (18U)
#define DSP_MEVTFLAG2_MEF82_MASK                                                                            (0x00040000U)

#define DSP_MEVTFLAG2_MEF83_SHIFT                                                                           (19U)
#define DSP_MEVTFLAG2_MEF83_MASK                                                                            (0x00080000U)

#define DSP_MEVTFLAG2_MEF84_SHIFT                                                                           (20U)
#define DSP_MEVTFLAG2_MEF84_MASK                                                                            (0x00100000U)

#define DSP_MEVTFLAG2_MEF85_SHIFT                                                                           (21U)
#define DSP_MEVTFLAG2_MEF85_MASK                                                                            (0x00200000U)

#define DSP_MEVTFLAG2_MEF86_SHIFT                                                                           (22U)
#define DSP_MEVTFLAG2_MEF86_MASK                                                                            (0x00400000U)

#define DSP_MEVTFLAG2_MEF87_SHIFT                                                                           (23U)
#define DSP_MEVTFLAG2_MEF87_MASK                                                                            (0x00800000U)

#define DSP_MEVTFLAG2_MEF88_SHIFT                                                                           (24U)
#define DSP_MEVTFLAG2_MEF88_MASK                                                                            (0x01000000U)

#define DSP_MEVTFLAG2_MEF89_SHIFT                                                                           (25U)
#define DSP_MEVTFLAG2_MEF89_MASK                                                                            (0x02000000U)

#define DSP_MEVTFLAG2_MEF90_SHIFT                                                                           (26U)
#define DSP_MEVTFLAG2_MEF90_MASK                                                                            (0x04000000U)

#define DSP_MEVTFLAG2_MEF91_SHIFT                                                                           (27U)
#define DSP_MEVTFLAG2_MEF91_MASK                                                                            (0x08000000U)

#define DSP_MEVTFLAG2_MEF92_SHIFT                                                                           (28U)
#define DSP_MEVTFLAG2_MEF92_MASK                                                                            (0x10000000U)

#define DSP_MEVTFLAG2_MEF93_SHIFT                                                                           (29U)
#define DSP_MEVTFLAG2_MEF93_MASK                                                                            (0x20000000U)

#define DSP_MEVTFLAG2_MEF94_SHIFT                                                                           (30U)
#define DSP_MEVTFLAG2_MEF94_MASK                                                                            (0x40000000U)

#define DSP_MEVTFLAG2_MEF95_SHIFT                                                                           (31U)
#define DSP_MEVTFLAG2_MEF95_MASK                                                                            (0x80000000U)

#define DSP_MEVTFLAG3_MEF96_SHIFT                                                                           (0U)
#define DSP_MEVTFLAG3_MEF96_MASK                                                                            (0x00000001U)

#define DSP_MEVTFLAG3_MEF97_SHIFT                                                                           (1U)
#define DSP_MEVTFLAG3_MEF97_MASK                                                                            (0x00000002U)

#define DSP_MEVTFLAG3_MEF98_SHIFT                                                                           (2U)
#define DSP_MEVTFLAG3_MEF98_MASK                                                                            (0x00000004U)

#define DSP_MEVTFLAG3_MEF99_SHIFT                                                                           (3U)
#define DSP_MEVTFLAG3_MEF99_MASK                                                                            (0x00000008U)

#define DSP_MEVTFLAG3_MEF100_SHIFT                                                                          (4U)
#define DSP_MEVTFLAG3_MEF100_MASK                                                                           (0x00000010U)

#define DSP_MEVTFLAG3_MEF101_SHIFT                                                                          (5U)
#define DSP_MEVTFLAG3_MEF101_MASK                                                                           (0x00000020U)

#define DSP_MEVTFLAG3_MEF102_SHIFT                                                                          (6U)
#define DSP_MEVTFLAG3_MEF102_MASK                                                                           (0x00000040U)

#define DSP_MEVTFLAG3_MEF103_SHIFT                                                                          (7U)
#define DSP_MEVTFLAG3_MEF103_MASK                                                                           (0x00000080U)

#define DSP_MEVTFLAG3_MEF104_SHIFT                                                                          (8U)
#define DSP_MEVTFLAG3_MEF104_MASK                                                                           (0x00000100U)

#define DSP_MEVTFLAG3_MEF105_SHIFT                                                                          (9U)
#define DSP_MEVTFLAG3_MEF105_MASK                                                                           (0x00000200U)

#define DSP_MEVTFLAG3_MEF106_SHIFT                                                                          (10U)
#define DSP_MEVTFLAG3_MEF106_MASK                                                                           (0x00000400U)

#define DSP_MEVTFLAG3_MEF107_SHIFT                                                                          (11U)
#define DSP_MEVTFLAG3_MEF107_MASK                                                                           (0x00000800U)

#define DSP_MEVTFLAG3_MEF108_SHIFT                                                                          (12U)
#define DSP_MEVTFLAG3_MEF108_MASK                                                                           (0x00001000U)

#define DSP_MEVTFLAG3_MEF109_SHIFT                                                                          (13U)
#define DSP_MEVTFLAG3_MEF109_MASK                                                                           (0x00002000U)

#define DSP_MEVTFLAG3_MEF110_SHIFT                                                                          (14U)
#define DSP_MEVTFLAG3_MEF110_MASK                                                                           (0x00004000U)

#define DSP_MEVTFLAG3_MEF111_SHIFT                                                                          (15U)
#define DSP_MEVTFLAG3_MEF111_MASK                                                                           (0x00008000U)

#define DSP_MEVTFLAG3_MEF112_SHIFT                                                                          (16U)
#define DSP_MEVTFLAG3_MEF112_MASK                                                                           (0x00010000U)

#define DSP_MEVTFLAG3_MEF113_SHIFT                                                                          (17U)
#define DSP_MEVTFLAG3_MEF113_MASK                                                                           (0x00020000U)

#define DSP_MEVTFLAG3_MEF114_SHIFT                                                                          (18U)
#define DSP_MEVTFLAG3_MEF114_MASK                                                                           (0x00040000U)

#define DSP_MEVTFLAG3_MEF115_SHIFT                                                                          (19U)
#define DSP_MEVTFLAG3_MEF115_MASK                                                                           (0x00080000U)

#define DSP_MEVTFLAG3_MEF116_SHIFT                                                                          (20U)
#define DSP_MEVTFLAG3_MEF116_MASK                                                                           (0x00100000U)

#define DSP_MEVTFLAG3_MEF117_SHIFT                                                                          (21U)
#define DSP_MEVTFLAG3_MEF117_MASK                                                                           (0x00200000U)

#define DSP_MEVTFLAG3_MEF118_SHIFT                                                                          (22U)
#define DSP_MEVTFLAG3_MEF118_MASK                                                                           (0x00400000U)

#define DSP_MEVTFLAG3_MEF119_SHIFT                                                                          (23U)
#define DSP_MEVTFLAG3_MEF119_MASK                                                                           (0x00800000U)

#define DSP_MEVTFLAG3_MEF120_SHIFT                                                                          (24U)
#define DSP_MEVTFLAG3_MEF120_MASK                                                                           (0x01000000U)

#define DSP_MEVTFLAG3_MEF121_SHIFT                                                                          (25U)
#define DSP_MEVTFLAG3_MEF121_MASK                                                                           (0x02000000U)

#define DSP_MEVTFLAG3_MEF122_SHIFT                                                                          (26U)
#define DSP_MEVTFLAG3_MEF122_MASK                                                                           (0x04000000U)

#define DSP_MEVTFLAG3_MEF123_SHIFT                                                                          (27U)
#define DSP_MEVTFLAG3_MEF123_MASK                                                                           (0x08000000U)

#define DSP_MEVTFLAG3_MEF124_SHIFT                                                                          (28U)
#define DSP_MEVTFLAG3_MEF124_MASK                                                                           (0x10000000U)

#define DSP_MEVTFLAG3_MEF125_SHIFT                                                                          (29U)
#define DSP_MEVTFLAG3_MEF125_MASK                                                                           (0x20000000U)

#define DSP_MEVTFLAG3_MEF126_SHIFT                                                                          (30U)
#define DSP_MEVTFLAG3_MEF126_MASK                                                                           (0x40000000U)

#define DSP_MEVTFLAG3_MEF127_SHIFT                                                                          (31U)
#define DSP_MEVTFLAG3_MEF127_MASK                                                                           (0x80000000U)

#define DSP_EXPMASK1_XM32_SHIFT                                                                             (0U)
#define DSP_EXPMASK1_XM32_MASK                                                                              (0x00000001U)

#define DSP_EXPMASK1_XM33_SHIFT                                                                             (1U)
#define DSP_EXPMASK1_XM33_MASK                                                                              (0x00000002U)

#define DSP_EXPMASK1_XM34_SHIFT                                                                             (2U)
#define DSP_EXPMASK1_XM34_MASK                                                                              (0x00000004U)

#define DSP_EXPMASK1_XM35_SHIFT                                                                             (3U)
#define DSP_EXPMASK1_XM35_MASK                                                                              (0x00000008U)

#define DSP_EXPMASK1_XM36_SHIFT                                                                             (4U)
#define DSP_EXPMASK1_XM36_MASK                                                                              (0x00000010U)

#define DSP_EXPMASK1_XM37_SHIFT                                                                             (5U)
#define DSP_EXPMASK1_XM37_MASK                                                                              (0x00000020U)

#define DSP_EXPMASK1_XM38_SHIFT                                                                             (6U)
#define DSP_EXPMASK1_XM38_MASK                                                                              (0x00000040U)

#define DSP_EXPMASK1_XM39_SHIFT                                                                             (7U)
#define DSP_EXPMASK1_XM39_MASK                                                                              (0x00000080U)

#define DSP_EXPMASK1_XM40_SHIFT                                                                             (8U)
#define DSP_EXPMASK1_XM40_MASK                                                                              (0x00000100U)

#define DSP_EXPMASK1_XM41_SHIFT                                                                             (9U)
#define DSP_EXPMASK1_XM41_MASK                                                                              (0x00000200U)

#define DSP_EXPMASK1_XM42_SHIFT                                                                             (10U)
#define DSP_EXPMASK1_XM42_MASK                                                                              (0x00000400U)

#define DSP_EXPMASK1_XM43_SHIFT                                                                             (11U)
#define DSP_EXPMASK1_XM43_MASK                                                                              (0x00000800U)

#define DSP_EXPMASK1_XM44_SHIFT                                                                             (12U)
#define DSP_EXPMASK1_XM44_MASK                                                                              (0x00001000U)

#define DSP_EXPMASK1_XM45_SHIFT                                                                             (13U)
#define DSP_EXPMASK1_XM45_MASK                                                                              (0x00002000U)

#define DSP_EXPMASK1_XM46_SHIFT                                                                             (14U)
#define DSP_EXPMASK1_XM46_MASK                                                                              (0x00004000U)

#define DSP_EXPMASK1_XM47_SHIFT                                                                             (15U)
#define DSP_EXPMASK1_XM47_MASK                                                                              (0x00008000U)

#define DSP_EXPMASK1_XM48_SHIFT                                                                             (16U)
#define DSP_EXPMASK1_XM48_MASK                                                                              (0x00010000U)

#define DSP_EXPMASK1_XM49_SHIFT                                                                             (17U)
#define DSP_EXPMASK1_XM49_MASK                                                                              (0x00020000U)

#define DSP_EXPMASK1_XM50_SHIFT                                                                             (18U)
#define DSP_EXPMASK1_XM50_MASK                                                                              (0x00040000U)

#define DSP_EXPMASK1_XM51_SHIFT                                                                             (19U)
#define DSP_EXPMASK1_XM51_MASK                                                                              (0x00080000U)

#define DSP_EXPMASK1_XM52_SHIFT                                                                             (20U)
#define DSP_EXPMASK1_XM52_MASK                                                                              (0x00100000U)

#define DSP_EXPMASK1_XM53_SHIFT                                                                             (21U)
#define DSP_EXPMASK1_XM53_MASK                                                                              (0x00200000U)

#define DSP_EXPMASK1_XM54_SHIFT                                                                             (22U)
#define DSP_EXPMASK1_XM54_MASK                                                                              (0x00400000U)

#define DSP_EXPMASK1_XM55_SHIFT                                                                             (23U)
#define DSP_EXPMASK1_XM55_MASK                                                                              (0x00800000U)

#define DSP_EXPMASK1_XM56_SHIFT                                                                             (24U)
#define DSP_EXPMASK1_XM56_MASK                                                                              (0x01000000U)

#define DSP_EXPMASK1_XM57_SHIFT                                                                             (25U)
#define DSP_EXPMASK1_XM57_MASK                                                                              (0x02000000U)

#define DSP_EXPMASK1_XM58_SHIFT                                                                             (26U)
#define DSP_EXPMASK1_XM58_MASK                                                                              (0x04000000U)

#define DSP_EXPMASK1_XM59_SHIFT                                                                             (27U)
#define DSP_EXPMASK1_XM59_MASK                                                                              (0x08000000U)

#define DSP_EXPMASK1_XM60_SHIFT                                                                             (28U)
#define DSP_EXPMASK1_XM60_MASK                                                                              (0x10000000U)

#define DSP_EXPMASK1_XM61_SHIFT                                                                             (29U)
#define DSP_EXPMASK1_XM61_MASK                                                                              (0x20000000U)

#define DSP_EXPMASK1_XM62_SHIFT                                                                             (30U)
#define DSP_EXPMASK1_XM62_MASK                                                                              (0x40000000U)

#define DSP_EXPMASK1_XM63_SHIFT                                                                             (31U)
#define DSP_EXPMASK1_XM63_MASK                                                                              (0x80000000U)

#define DSP_EXPMASK2_XM64_SHIFT                                                                             (0U)
#define DSP_EXPMASK2_XM64_MASK                                                                              (0x00000001U)

#define DSP_EXPMASK2_XM65_SHIFT                                                                             (1U)
#define DSP_EXPMASK2_XM65_MASK                                                                              (0x00000002U)

#define DSP_EXPMASK2_XM66_SHIFT                                                                             (2U)
#define DSP_EXPMASK2_XM66_MASK                                                                              (0x00000004U)

#define DSP_EXPMASK2_XM67_SHIFT                                                                             (3U)
#define DSP_EXPMASK2_XM67_MASK                                                                              (0x00000008U)

#define DSP_EXPMASK2_XM68_SHIFT                                                                             (4U)
#define DSP_EXPMASK2_XM68_MASK                                                                              (0x00000010U)

#define DSP_EXPMASK2_XM69_SHIFT                                                                             (5U)
#define DSP_EXPMASK2_XM69_MASK                                                                              (0x00000020U)

#define DSP_EXPMASK2_XM70_SHIFT                                                                             (6U)
#define DSP_EXPMASK2_XM70_MASK                                                                              (0x00000040U)

#define DSP_EXPMASK2_XM71_SHIFT                                                                             (7U)
#define DSP_EXPMASK2_XM71_MASK                                                                              (0x00000080U)

#define DSP_EXPMASK2_XM72_SHIFT                                                                             (8U)
#define DSP_EXPMASK2_XM72_MASK                                                                              (0x00000100U)

#define DSP_EXPMASK2_XM73_SHIFT                                                                             (9U)
#define DSP_EXPMASK2_XM73_MASK                                                                              (0x00000200U)

#define DSP_EXPMASK2_XM74_SHIFT                                                                             (10U)
#define DSP_EXPMASK2_XM74_MASK                                                                              (0x00000400U)

#define DSP_EXPMASK2_XM75_SHIFT                                                                             (11U)
#define DSP_EXPMASK2_XM75_MASK                                                                              (0x00000800U)

#define DSP_EXPMASK2_XM76_SHIFT                                                                             (12U)
#define DSP_EXPMASK2_XM76_MASK                                                                              (0x00001000U)

#define DSP_EXPMASK2_XM77_SHIFT                                                                             (13U)
#define DSP_EXPMASK2_XM77_MASK                                                                              (0x00002000U)

#define DSP_EXPMASK2_XM78_SHIFT                                                                             (14U)
#define DSP_EXPMASK2_XM78_MASK                                                                              (0x00004000U)

#define DSP_EXPMASK2_XM79_SHIFT                                                                             (15U)
#define DSP_EXPMASK2_XM79_MASK                                                                              (0x00008000U)

#define DSP_EXPMASK2_XM80_SHIFT                                                                             (16U)
#define DSP_EXPMASK2_XM80_MASK                                                                              (0x00010000U)

#define DSP_EXPMASK2_XM81_SHIFT                                                                             (17U)
#define DSP_EXPMASK2_XM81_MASK                                                                              (0x00020000U)

#define DSP_EXPMASK2_XM82_SHIFT                                                                             (18U)
#define DSP_EXPMASK2_XM82_MASK                                                                              (0x00040000U)

#define DSP_EXPMASK2_XM83_SHIFT                                                                             (19U)
#define DSP_EXPMASK2_XM83_MASK                                                                              (0x00080000U)

#define DSP_EXPMASK2_XM84_SHIFT                                                                             (20U)
#define DSP_EXPMASK2_XM84_MASK                                                                              (0x00100000U)

#define DSP_EXPMASK2_XM85_SHIFT                                                                             (21U)
#define DSP_EXPMASK2_XM85_MASK                                                                              (0x00200000U)

#define DSP_EXPMASK2_XM86_SHIFT                                                                             (22U)
#define DSP_EXPMASK2_XM86_MASK                                                                              (0x00400000U)

#define DSP_EXPMASK2_XM87_SHIFT                                                                             (23U)
#define DSP_EXPMASK2_XM87_MASK                                                                              (0x00800000U)

#define DSP_EXPMASK2_XM88_SHIFT                                                                             (24U)
#define DSP_EXPMASK2_XM88_MASK                                                                              (0x01000000U)

#define DSP_EXPMASK2_XM89_SHIFT                                                                             (25U)
#define DSP_EXPMASK2_XM89_MASK                                                                              (0x02000000U)

#define DSP_EXPMASK2_XM90_SHIFT                                                                             (26U)
#define DSP_EXPMASK2_XM90_MASK                                                                              (0x04000000U)

#define DSP_EXPMASK2_XM91_SHIFT                                                                             (27U)
#define DSP_EXPMASK2_XM91_MASK                                                                              (0x08000000U)

#define DSP_EXPMASK2_XM92_SHIFT                                                                             (28U)
#define DSP_EXPMASK2_XM92_MASK                                                                              (0x10000000U)

#define DSP_EXPMASK2_XM93_SHIFT                                                                             (29U)
#define DSP_EXPMASK2_XM93_MASK                                                                              (0x20000000U)

#define DSP_EXPMASK2_XM94_SHIFT                                                                             (30U)
#define DSP_EXPMASK2_XM94_MASK                                                                              (0x40000000U)

#define DSP_EXPMASK2_XM95_SHIFT                                                                             (31U)
#define DSP_EXPMASK2_XM95_MASK                                                                              (0x80000000U)

#define DSP_EXPMASK3_XM96_SHIFT                                                                             (0U)
#define DSP_EXPMASK3_XM96_MASK                                                                              (0x00000001U)

#define DSP_EXPMASK3_XM97_SHIFT                                                                             (1U)
#define DSP_EXPMASK3_XM97_MASK                                                                              (0x00000002U)

#define DSP_EXPMASK3_XM98_SHIFT                                                                             (2U)
#define DSP_EXPMASK3_XM98_MASK                                                                              (0x00000004U)

#define DSP_EXPMASK3_XM99_SHIFT                                                                             (3U)
#define DSP_EXPMASK3_XM99_MASK                                                                              (0x00000008U)

#define DSP_EXPMASK3_XM100_SHIFT                                                                            (4U)
#define DSP_EXPMASK3_XM100_MASK                                                                             (0x00000010U)

#define DSP_EXPMASK3_XM101_SHIFT                                                                            (5U)
#define DSP_EXPMASK3_XM101_MASK                                                                             (0x00000020U)

#define DSP_EXPMASK3_XM102_SHIFT                                                                            (6U)
#define DSP_EXPMASK3_XM102_MASK                                                                             (0x00000040U)

#define DSP_EXPMASK3_XM103_SHIFT                                                                            (7U)
#define DSP_EXPMASK3_XM103_MASK                                                                             (0x00000080U)

#define DSP_EXPMASK3_XM104_SHIFT                                                                            (8U)
#define DSP_EXPMASK3_XM104_MASK                                                                             (0x00000100U)

#define DSP_EXPMASK3_XM105_SHIFT                                                                            (9U)
#define DSP_EXPMASK3_XM105_MASK                                                                             (0x00000200U)

#define DSP_EXPMASK3_XM106_SHIFT                                                                            (10U)
#define DSP_EXPMASK3_XM106_MASK                                                                             (0x00000400U)

#define DSP_EXPMASK3_XM107_SHIFT                                                                            (11U)
#define DSP_EXPMASK3_XM107_MASK                                                                             (0x00000800U)

#define DSP_EXPMASK3_XM108_SHIFT                                                                            (12U)
#define DSP_EXPMASK3_XM108_MASK                                                                             (0x00001000U)

#define DSP_EXPMASK3_XM109_SHIFT                                                                            (13U)
#define DSP_EXPMASK3_XM109_MASK                                                                             (0x00002000U)

#define DSP_EXPMASK3_XM110_SHIFT                                                                            (14U)
#define DSP_EXPMASK3_XM110_MASK                                                                             (0x00004000U)

#define DSP_EXPMASK3_XM111_SHIFT                                                                            (15U)
#define DSP_EXPMASK3_XM111_MASK                                                                             (0x00008000U)

#define DSP_EXPMASK3_XM112_SHIFT                                                                            (16U)
#define DSP_EXPMASK3_XM112_MASK                                                                             (0x00010000U)

#define DSP_EXPMASK3_XM113_SHIFT                                                                            (17U)
#define DSP_EXPMASK3_XM113_MASK                                                                             (0x00020000U)

#define DSP_EXPMASK3_XM114_SHIFT                                                                            (18U)
#define DSP_EXPMASK3_XM114_MASK                                                                             (0x00040000U)

#define DSP_EXPMASK3_XM115_SHIFT                                                                            (19U)
#define DSP_EXPMASK3_XM115_MASK                                                                             (0x00080000U)

#define DSP_EXPMASK3_XM116_SHIFT                                                                            (20U)
#define DSP_EXPMASK3_XM116_MASK                                                                             (0x00100000U)

#define DSP_EXPMASK3_XM117_SHIFT                                                                            (21U)
#define DSP_EXPMASK3_XM117_MASK                                                                             (0x00200000U)

#define DSP_EXPMASK3_XM118_SHIFT                                                                            (22U)
#define DSP_EXPMASK3_XM118_MASK                                                                             (0x00400000U)

#define DSP_EXPMASK3_XM119_SHIFT                                                                            (23U)
#define DSP_EXPMASK3_XM119_MASK                                                                             (0x00800000U)

#define DSP_EXPMASK3_XM120_SHIFT                                                                            (24U)
#define DSP_EXPMASK3_XM120_MASK                                                                             (0x01000000U)

#define DSP_EXPMASK3_XM121_SHIFT                                                                            (25U)
#define DSP_EXPMASK3_XM121_MASK                                                                             (0x02000000U)

#define DSP_EXPMASK3_XM122_SHIFT                                                                            (26U)
#define DSP_EXPMASK3_XM122_MASK                                                                             (0x04000000U)

#define DSP_EXPMASK3_XM123_SHIFT                                                                            (27U)
#define DSP_EXPMASK3_XM123_MASK                                                                             (0x08000000U)

#define DSP_EXPMASK3_XM124_SHIFT                                                                            (28U)
#define DSP_EXPMASK3_XM124_MASK                                                                             (0x10000000U)

#define DSP_EXPMASK3_XM125_SHIFT                                                                            (29U)
#define DSP_EXPMASK3_XM125_MASK                                                                             (0x20000000U)

#define DSP_EXPMASK3_XM126_SHIFT                                                                            (30U)
#define DSP_EXPMASK3_XM126_MASK                                                                             (0x40000000U)

#define DSP_EXPMASK3_XM127_SHIFT                                                                            (31U)
#define DSP_EXPMASK3_XM127_MASK                                                                             (0x80000000U)

#define DSP_MEXPFLAG1_MXF32_SHIFT                                                                           (0U)
#define DSP_MEXPFLAG1_MXF32_MASK                                                                            (0x00000001U)

#define DSP_MEXPFLAG1_MXF33_SHIFT                                                                           (1U)
#define DSP_MEXPFLAG1_MXF33_MASK                                                                            (0x00000002U)

#define DSP_MEXPFLAG1_MXF34_SHIFT                                                                           (2U)
#define DSP_MEXPFLAG1_MXF34_MASK                                                                            (0x00000004U)

#define DSP_MEXPFLAG1_MXF35_SHIFT                                                                           (3U)
#define DSP_MEXPFLAG1_MXF35_MASK                                                                            (0x00000008U)

#define DSP_MEXPFLAG1_MXF36_SHIFT                                                                           (4U)
#define DSP_MEXPFLAG1_MXF36_MASK                                                                            (0x00000010U)

#define DSP_MEXPFLAG1_MXF37_SHIFT                                                                           (5U)
#define DSP_MEXPFLAG1_MXF37_MASK                                                                            (0x00000020U)

#define DSP_MEXPFLAG1_MXF38_SHIFT                                                                           (6U)
#define DSP_MEXPFLAG1_MXF38_MASK                                                                            (0x00000040U)

#define DSP_MEXPFLAG1_MXF39_SHIFT                                                                           (7U)
#define DSP_MEXPFLAG1_MXF39_MASK                                                                            (0x00000080U)

#define DSP_MEXPFLAG1_MXF40_SHIFT                                                                           (8U)
#define DSP_MEXPFLAG1_MXF40_MASK                                                                            (0x00000100U)

#define DSP_MEXPFLAG1_MXF41_SHIFT                                                                           (9U)
#define DSP_MEXPFLAG1_MXF41_MASK                                                                            (0x00000200U)

#define DSP_MEXPFLAG1_MXF42_SHIFT                                                                           (10U)
#define DSP_MEXPFLAG1_MXF42_MASK                                                                            (0x00000400U)

#define DSP_MEXPFLAG1_MXF43_SHIFT                                                                           (11U)
#define DSP_MEXPFLAG1_MXF43_MASK                                                                            (0x00000800U)

#define DSP_MEXPFLAG1_MXF44_SHIFT                                                                           (12U)
#define DSP_MEXPFLAG1_MXF44_MASK                                                                            (0x00001000U)

#define DSP_MEXPFLAG1_MXF45_SHIFT                                                                           (13U)
#define DSP_MEXPFLAG1_MXF45_MASK                                                                            (0x00002000U)

#define DSP_MEXPFLAG1_MXF46_SHIFT                                                                           (14U)
#define DSP_MEXPFLAG1_MXF46_MASK                                                                            (0x00004000U)

#define DSP_MEXPFLAG1_MXF47_SHIFT                                                                           (15U)
#define DSP_MEXPFLAG1_MXF47_MASK                                                                            (0x00008000U)

#define DSP_MEXPFLAG1_MXF48_SHIFT                                                                           (16U)
#define DSP_MEXPFLAG1_MXF48_MASK                                                                            (0x00010000U)

#define DSP_MEXPFLAG1_MXF49_SHIFT                                                                           (17U)
#define DSP_MEXPFLAG1_MXF49_MASK                                                                            (0x00020000U)

#define DSP_MEXPFLAG1_MXF50_SHIFT                                                                           (18U)
#define DSP_MEXPFLAG1_MXF50_MASK                                                                            (0x00040000U)

#define DSP_MEXPFLAG1_MXF51_SHIFT                                                                           (19U)
#define DSP_MEXPFLAG1_MXF51_MASK                                                                            (0x00080000U)

#define DSP_MEXPFLAG1_MXF52_SHIFT                                                                           (20U)
#define DSP_MEXPFLAG1_MXF52_MASK                                                                            (0x00100000U)

#define DSP_MEXPFLAG1_MXF53_SHIFT                                                                           (21U)
#define DSP_MEXPFLAG1_MXF53_MASK                                                                            (0x00200000U)

#define DSP_MEXPFLAG1_MXF54_SHIFT                                                                           (22U)
#define DSP_MEXPFLAG1_MXF54_MASK                                                                            (0x00400000U)

#define DSP_MEXPFLAG1_MXF55_SHIFT                                                                           (23U)
#define DSP_MEXPFLAG1_MXF55_MASK                                                                            (0x00800000U)

#define DSP_MEXPFLAG1_MXF56_SHIFT                                                                           (24U)
#define DSP_MEXPFLAG1_MXF56_MASK                                                                            (0x01000000U)

#define DSP_MEXPFLAG1_MXF57_SHIFT                                                                           (25U)
#define DSP_MEXPFLAG1_MXF57_MASK                                                                            (0x02000000U)

#define DSP_MEXPFLAG1_MXF58_SHIFT                                                                           (26U)
#define DSP_MEXPFLAG1_MXF58_MASK                                                                            (0x04000000U)

#define DSP_MEXPFLAG1_MXF59_SHIFT                                                                           (27U)
#define DSP_MEXPFLAG1_MXF59_MASK                                                                            (0x08000000U)

#define DSP_MEXPFLAG1_MXF60_SHIFT                                                                           (28U)
#define DSP_MEXPFLAG1_MXF60_MASK                                                                            (0x10000000U)

#define DSP_MEXPFLAG1_MXF61_SHIFT                                                                           (29U)
#define DSP_MEXPFLAG1_MXF61_MASK                                                                            (0x20000000U)

#define DSP_MEXPFLAG1_MXF62_SHIFT                                                                           (30U)
#define DSP_MEXPFLAG1_MXF62_MASK                                                                            (0x40000000U)

#define DSP_MEXPFLAG1_MXF63_SHIFT                                                                           (31U)
#define DSP_MEXPFLAG1_MXF63_MASK                                                                            (0x80000000U)

#define DSP_MEXPFLAG2_MXF64_SHIFT                                                                           (0U)
#define DSP_MEXPFLAG2_MXF64_MASK                                                                            (0x00000001U)

#define DSP_MEXPFLAG2_MXF65_SHIFT                                                                           (1U)
#define DSP_MEXPFLAG2_MXF65_MASK                                                                            (0x00000002U)

#define DSP_MEXPFLAG2_MXF66_SHIFT                                                                           (2U)
#define DSP_MEXPFLAG2_MXF66_MASK                                                                            (0x00000004U)

#define DSP_MEXPFLAG2_MXF67_SHIFT                                                                           (3U)
#define DSP_MEXPFLAG2_MXF67_MASK                                                                            (0x00000008U)

#define DSP_MEXPFLAG2_MXF68_SHIFT                                                                           (4U)
#define DSP_MEXPFLAG2_MXF68_MASK                                                                            (0x00000010U)

#define DSP_MEXPFLAG2_MXF69_SHIFT                                                                           (5U)
#define DSP_MEXPFLAG2_MXF69_MASK                                                                            (0x00000020U)

#define DSP_MEXPFLAG2_MXF70_SHIFT                                                                           (6U)
#define DSP_MEXPFLAG2_MXF70_MASK                                                                            (0x00000040U)

#define DSP_MEXPFLAG2_MXF71_SHIFT                                                                           (7U)
#define DSP_MEXPFLAG2_MXF71_MASK                                                                            (0x00000080U)

#define DSP_MEXPFLAG2_MXF72_SHIFT                                                                           (8U)
#define DSP_MEXPFLAG2_MXF72_MASK                                                                            (0x00000100U)

#define DSP_MEXPFLAG2_MXF73_SHIFT                                                                           (9U)
#define DSP_MEXPFLAG2_MXF73_MASK                                                                            (0x00000200U)

#define DSP_MEXPFLAG2_MXF74_SHIFT                                                                           (10U)
#define DSP_MEXPFLAG2_MXF74_MASK                                                                            (0x00000400U)

#define DSP_MEXPFLAG2_MXF75_SHIFT                                                                           (11U)
#define DSP_MEXPFLAG2_MXF75_MASK                                                                            (0x00000800U)

#define DSP_MEXPFLAG2_MXF76_SHIFT                                                                           (12U)
#define DSP_MEXPFLAG2_MXF76_MASK                                                                            (0x00001000U)

#define DSP_MEXPFLAG2_MXF77_SHIFT                                                                           (13U)
#define DSP_MEXPFLAG2_MXF77_MASK                                                                            (0x00002000U)

#define DSP_MEXPFLAG2_MXF78_SHIFT                                                                           (14U)
#define DSP_MEXPFLAG2_MXF78_MASK                                                                            (0x00004000U)

#define DSP_MEXPFLAG2_MXF79_SHIFT                                                                           (15U)
#define DSP_MEXPFLAG2_MXF79_MASK                                                                            (0x00008000U)

#define DSP_MEXPFLAG2_MXF80_SHIFT                                                                           (16U)
#define DSP_MEXPFLAG2_MXF80_MASK                                                                            (0x00010000U)

#define DSP_MEXPFLAG2_MXF81_SHIFT                                                                           (17U)
#define DSP_MEXPFLAG2_MXF81_MASK                                                                            (0x00020000U)

#define DSP_MEXPFLAG2_MXF82_SHIFT                                                                           (18U)
#define DSP_MEXPFLAG2_MXF82_MASK                                                                            (0x00040000U)

#define DSP_MEXPFLAG2_MXF83_SHIFT                                                                           (19U)
#define DSP_MEXPFLAG2_MXF83_MASK                                                                            (0x00080000U)

#define DSP_MEXPFLAG2_MXF84_SHIFT                                                                           (20U)
#define DSP_MEXPFLAG2_MXF84_MASK                                                                            (0x00100000U)

#define DSP_MEXPFLAG2_MXF85_SHIFT                                                                           (21U)
#define DSP_MEXPFLAG2_MXF85_MASK                                                                            (0x00200000U)

#define DSP_MEXPFLAG2_MXF86_SHIFT                                                                           (22U)
#define DSP_MEXPFLAG2_MXF86_MASK                                                                            (0x00400000U)

#define DSP_MEXPFLAG2_MXF87_SHIFT                                                                           (23U)
#define DSP_MEXPFLAG2_MXF87_MASK                                                                            (0x00800000U)

#define DSP_MEXPFLAG2_MXF88_SHIFT                                                                           (24U)
#define DSP_MEXPFLAG2_MXF88_MASK                                                                            (0x01000000U)

#define DSP_MEXPFLAG2_MXF89_SHIFT                                                                           (25U)
#define DSP_MEXPFLAG2_MXF89_MASK                                                                            (0x02000000U)

#define DSP_MEXPFLAG2_MXF90_SHIFT                                                                           (26U)
#define DSP_MEXPFLAG2_MXF90_MASK                                                                            (0x04000000U)

#define DSP_MEXPFLAG2_MXF91_SHIFT                                                                           (27U)
#define DSP_MEXPFLAG2_MXF91_MASK                                                                            (0x08000000U)

#define DSP_MEXPFLAG2_MXF92_SHIFT                                                                           (28U)
#define DSP_MEXPFLAG2_MXF92_MASK                                                                            (0x10000000U)

#define DSP_MEXPFLAG2_MXF93_SHIFT                                                                           (29U)
#define DSP_MEXPFLAG2_MXF93_MASK                                                                            (0x20000000U)

#define DSP_MEXPFLAG2_MXF94_SHIFT                                                                           (30U)
#define DSP_MEXPFLAG2_MXF94_MASK                                                                            (0x40000000U)

#define DSP_MEXPFLAG2_MXF95_SHIFT                                                                           (31U)
#define DSP_MEXPFLAG2_MXF95_MASK                                                                            (0x80000000U)

#define DSP_MEXPFLAG3_MXF96_SHIFT                                                                           (0U)
#define DSP_MEXPFLAG3_MXF96_MASK                                                                            (0x00000001U)

#define DSP_MEXPFLAG3_MXF97_SHIFT                                                                           (1U)
#define DSP_MEXPFLAG3_MXF97_MASK                                                                            (0x00000002U)

#define DSP_MEXPFLAG3_MXF98_SHIFT                                                                           (2U)
#define DSP_MEXPFLAG3_MXF98_MASK                                                                            (0x00000004U)

#define DSP_MEXPFLAG3_MXF99_SHIFT                                                                           (3U)
#define DSP_MEXPFLAG3_MXF99_MASK                                                                            (0x00000008U)

#define DSP_MEXPFLAG3_MXF100_SHIFT                                                                          (4U)
#define DSP_MEXPFLAG3_MXF100_MASK                                                                           (0x00000010U)

#define DSP_MEXPFLAG3_MXF101_SHIFT                                                                          (5U)
#define DSP_MEXPFLAG3_MXF101_MASK                                                                           (0x00000020U)

#define DSP_MEXPFLAG3_MXF102_SHIFT                                                                          (6U)
#define DSP_MEXPFLAG3_MXF102_MASK                                                                           (0x00000040U)

#define DSP_MEXPFLAG3_MXF103_SHIFT                                                                          (7U)
#define DSP_MEXPFLAG3_MXF103_MASK                                                                           (0x00000080U)

#define DSP_MEXPFLAG3_MXF104_SHIFT                                                                          (8U)
#define DSP_MEXPFLAG3_MXF104_MASK                                                                           (0x00000100U)

#define DSP_MEXPFLAG3_MXF105_SHIFT                                                                          (9U)
#define DSP_MEXPFLAG3_MXF105_MASK                                                                           (0x00000200U)

#define DSP_MEXPFLAG3_MXF106_SHIFT                                                                          (10U)
#define DSP_MEXPFLAG3_MXF106_MASK                                                                           (0x00000400U)

#define DSP_MEXPFLAG3_MXF107_SHIFT                                                                          (11U)
#define DSP_MEXPFLAG3_MXF107_MASK                                                                           (0x00000800U)

#define DSP_MEXPFLAG3_MXF108_SHIFT                                                                          (12U)
#define DSP_MEXPFLAG3_MXF108_MASK                                                                           (0x00001000U)

#define DSP_MEXPFLAG3_MXF109_SHIFT                                                                          (13U)
#define DSP_MEXPFLAG3_MXF109_MASK                                                                           (0x00002000U)

#define DSP_MEXPFLAG3_MXF110_SHIFT                                                                          (14U)
#define DSP_MEXPFLAG3_MXF110_MASK                                                                           (0x00004000U)

#define DSP_MEXPFLAG3_MXF111_SHIFT                                                                          (15U)
#define DSP_MEXPFLAG3_MXF111_MASK                                                                           (0x00008000U)

#define DSP_MEXPFLAG3_MXF112_SHIFT                                                                          (16U)
#define DSP_MEXPFLAG3_MXF112_MASK                                                                           (0x00010000U)

#define DSP_MEXPFLAG3_MXF113_SHIFT                                                                          (17U)
#define DSP_MEXPFLAG3_MXF113_MASK                                                                           (0x00020000U)

#define DSP_MEXPFLAG3_MXF114_SHIFT                                                                          (18U)
#define DSP_MEXPFLAG3_MXF114_MASK                                                                           (0x00040000U)

#define DSP_MEXPFLAG3_MXF115_SHIFT                                                                          (19U)
#define DSP_MEXPFLAG3_MXF115_MASK                                                                           (0x00080000U)

#define DSP_MEXPFLAG3_MXF116_SHIFT                                                                          (20U)
#define DSP_MEXPFLAG3_MXF116_MASK                                                                           (0x00100000U)

#define DSP_MEXPFLAG3_MXF117_SHIFT                                                                          (21U)
#define DSP_MEXPFLAG3_MXF117_MASK                                                                           (0x00200000U)

#define DSP_MEXPFLAG3_MXF118_SHIFT                                                                          (22U)
#define DSP_MEXPFLAG3_MXF118_MASK                                                                           (0x00400000U)

#define DSP_MEXPFLAG3_MXF119_SHIFT                                                                          (23U)
#define DSP_MEXPFLAG3_MXF119_MASK                                                                           (0x00800000U)

#define DSP_MEXPFLAG3_MXF120_SHIFT                                                                          (24U)
#define DSP_MEXPFLAG3_MXF120_MASK                                                                           (0x01000000U)

#define DSP_MEXPFLAG3_MXF121_SHIFT                                                                          (25U)
#define DSP_MEXPFLAG3_MXF121_MASK                                                                           (0x02000000U)

#define DSP_MEXPFLAG3_MXF122_SHIFT                                                                          (26U)
#define DSP_MEXPFLAG3_MXF122_MASK                                                                           (0x04000000U)

#define DSP_MEXPFLAG3_MXF123_SHIFT                                                                          (27U)
#define DSP_MEXPFLAG3_MXF123_MASK                                                                           (0x08000000U)

#define DSP_MEXPFLAG3_MXF124_SHIFT                                                                          (28U)
#define DSP_MEXPFLAG3_MXF124_MASK                                                                           (0x10000000U)

#define DSP_MEXPFLAG3_MXF125_SHIFT                                                                          (29U)
#define DSP_MEXPFLAG3_MXF125_MASK                                                                           (0x20000000U)

#define DSP_MEXPFLAG3_MXF126_SHIFT                                                                          (30U)
#define DSP_MEXPFLAG3_MXF126_MASK                                                                           (0x40000000U)

#define DSP_MEXPFLAG3_MXF127_SHIFT                                                                          (31U)
#define DSP_MEXPFLAG3_MXF127_MASK                                                                           (0x80000000U)

#define DSP_L1PMPPA17_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1PMPPA17_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1PMPPA17_AID5_SHIFT                                                                            (15U)
#define DSP_L1PMPPA17_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1PMPPA17_AID4_SHIFT                                                                            (14U)
#define DSP_L1PMPPA17_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1PMPPA17_AID3_SHIFT                                                                            (13U)
#define DSP_L1PMPPA17_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1PMPPA17_AID2_SHIFT                                                                            (12U)
#define DSP_L1PMPPA17_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1PMPPA17_AID1_SHIFT                                                                            (11U)
#define DSP_L1PMPPA17_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1PMPPA17_AID0_SHIFT                                                                            (10U)
#define DSP_L1PMPPA17_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1PMPPA17_AIDX_SHIFT                                                                            (9U)
#define DSP_L1PMPPA17_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1PMPPA17_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1PMPPA17_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1PMPPA17_SR_SHIFT                                                                              (5U)
#define DSP_L1PMPPA17_SR_MASK                                                                               (0x00000020U)

#define DSP_L1PMPPA17_SW_SHIFT                                                                              (4U)
#define DSP_L1PMPPA17_SW_MASK                                                                               (0x00000010U)

#define DSP_L1PMPPA17_SX_SHIFT                                                                              (3U)
#define DSP_L1PMPPA17_SX_MASK                                                                               (0x00000008U)

#define DSP_L1PMPPA17_UR_SHIFT                                                                              (2U)
#define DSP_L1PMPPA17_UR_MASK                                                                               (0x00000004U)

#define DSP_L1PMPPA17_UW_SHIFT                                                                              (1U)
#define DSP_L1PMPPA17_UW_MASK                                                                               (0x00000002U)

#define DSP_L1PMPPA17_UX_SHIFT                                                                              (0U)
#define DSP_L1PMPPA17_UX_MASK                                                                               (0x00000001U)

#define DSP_L1PMPPA17_RESV_2_SHIFT                                                                          (6U)
#define DSP_L1PMPPA17_RESV_2_MASK                                                                           (0x000000c0U)

#define DSP_L1PMPPA18_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1PMPPA18_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1PMPPA18_AID5_SHIFT                                                                            (15U)
#define DSP_L1PMPPA18_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1PMPPA18_AID4_SHIFT                                                                            (14U)
#define DSP_L1PMPPA18_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1PMPPA18_AID3_SHIFT                                                                            (13U)
#define DSP_L1PMPPA18_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1PMPPA18_AID2_SHIFT                                                                            (12U)
#define DSP_L1PMPPA18_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1PMPPA18_AID1_SHIFT                                                                            (11U)
#define DSP_L1PMPPA18_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1PMPPA18_AID0_SHIFT                                                                            (10U)
#define DSP_L1PMPPA18_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1PMPPA18_AIDX_SHIFT                                                                            (9U)
#define DSP_L1PMPPA18_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1PMPPA18_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1PMPPA18_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1PMPPA18_SR_SHIFT                                                                              (5U)
#define DSP_L1PMPPA18_SR_MASK                                                                               (0x00000020U)

#define DSP_L1PMPPA18_SW_SHIFT                                                                              (4U)
#define DSP_L1PMPPA18_SW_MASK                                                                               (0x00000010U)

#define DSP_L1PMPPA18_SX_SHIFT                                                                              (3U)
#define DSP_L1PMPPA18_SX_MASK                                                                               (0x00000008U)

#define DSP_L1PMPPA18_UR_SHIFT                                                                              (2U)
#define DSP_L1PMPPA18_UR_MASK                                                                               (0x00000004U)

#define DSP_L1PMPPA18_UW_SHIFT                                                                              (1U)
#define DSP_L1PMPPA18_UW_MASK                                                                               (0x00000002U)

#define DSP_L1PMPPA18_UX_SHIFT                                                                              (0U)
#define DSP_L1PMPPA18_UX_MASK                                                                               (0x00000001U)

#define DSP_L1PMPPA18_RESV_2_SHIFT                                                                          (6U)
#define DSP_L1PMPPA18_RESV_2_MASK                                                                           (0x000000c0U)

#define DSP_L1PMPPA19_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1PMPPA19_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1PMPPA19_AID5_SHIFT                                                                            (15U)
#define DSP_L1PMPPA19_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1PMPPA19_AID4_SHIFT                                                                            (14U)
#define DSP_L1PMPPA19_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1PMPPA19_AID3_SHIFT                                                                            (13U)
#define DSP_L1PMPPA19_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1PMPPA19_AID2_SHIFT                                                                            (12U)
#define DSP_L1PMPPA19_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1PMPPA19_AID1_SHIFT                                                                            (11U)
#define DSP_L1PMPPA19_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1PMPPA19_AID0_SHIFT                                                                            (10U)
#define DSP_L1PMPPA19_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1PMPPA19_AIDX_SHIFT                                                                            (9U)
#define DSP_L1PMPPA19_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1PMPPA19_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1PMPPA19_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1PMPPA19_SR_SHIFT                                                                              (5U)
#define DSP_L1PMPPA19_SR_MASK                                                                               (0x00000020U)

#define DSP_L1PMPPA19_SW_SHIFT                                                                              (4U)
#define DSP_L1PMPPA19_SW_MASK                                                                               (0x00000010U)

#define DSP_L1PMPPA19_SX_SHIFT                                                                              (3U)
#define DSP_L1PMPPA19_SX_MASK                                                                               (0x00000008U)

#define DSP_L1PMPPA19_UR_SHIFT                                                                              (2U)
#define DSP_L1PMPPA19_UR_MASK                                                                               (0x00000004U)

#define DSP_L1PMPPA19_UW_SHIFT                                                                              (1U)
#define DSP_L1PMPPA19_UW_MASK                                                                               (0x00000002U)

#define DSP_L1PMPPA19_UX_SHIFT                                                                              (0U)
#define DSP_L1PMPPA19_UX_MASK                                                                               (0x00000001U)

#define DSP_L1PMPPA19_RESV_2_SHIFT                                                                          (6U)
#define DSP_L1PMPPA19_RESV_2_MASK                                                                           (0x000000c0U)

#define DSP_L1PMPPA20_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1PMPPA20_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1PMPPA20_AID5_SHIFT                                                                            (15U)
#define DSP_L1PMPPA20_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1PMPPA20_AID4_SHIFT                                                                            (14U)
#define DSP_L1PMPPA20_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1PMPPA20_AID3_SHIFT                                                                            (13U)
#define DSP_L1PMPPA20_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1PMPPA20_AID2_SHIFT                                                                            (12U)
#define DSP_L1PMPPA20_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1PMPPA20_AID1_SHIFT                                                                            (11U)
#define DSP_L1PMPPA20_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1PMPPA20_AID0_SHIFT                                                                            (10U)
#define DSP_L1PMPPA20_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1PMPPA20_AIDX_SHIFT                                                                            (9U)
#define DSP_L1PMPPA20_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1PMPPA20_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1PMPPA20_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1PMPPA20_SR_SHIFT                                                                              (5U)
#define DSP_L1PMPPA20_SR_MASK                                                                               (0x00000020U)

#define DSP_L1PMPPA20_SW_SHIFT                                                                              (4U)
#define DSP_L1PMPPA20_SW_MASK                                                                               (0x00000010U)

#define DSP_L1PMPPA20_SX_SHIFT                                                                              (3U)
#define DSP_L1PMPPA20_SX_MASK                                                                               (0x00000008U)

#define DSP_L1PMPPA20_UR_SHIFT                                                                              (2U)
#define DSP_L1PMPPA20_UR_MASK                                                                               (0x00000004U)

#define DSP_L1PMPPA20_UW_SHIFT                                                                              (1U)
#define DSP_L1PMPPA20_UW_MASK                                                                               (0x00000002U)

#define DSP_L1PMPPA20_UX_SHIFT                                                                              (0U)
#define DSP_L1PMPPA20_UX_MASK                                                                               (0x00000001U)

#define DSP_L1PMPPA20_RESV_2_SHIFT                                                                          (6U)
#define DSP_L1PMPPA20_RESV_2_MASK                                                                           (0x000000c0U)

#define DSP_L1PMPPA21_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1PMPPA21_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1PMPPA21_AID5_SHIFT                                                                            (15U)
#define DSP_L1PMPPA21_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1PMPPA21_AID4_SHIFT                                                                            (14U)
#define DSP_L1PMPPA21_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1PMPPA21_AID3_SHIFT                                                                            (13U)
#define DSP_L1PMPPA21_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1PMPPA21_AID2_SHIFT                                                                            (12U)
#define DSP_L1PMPPA21_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1PMPPA21_AID1_SHIFT                                                                            (11U)
#define DSP_L1PMPPA21_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1PMPPA21_AID0_SHIFT                                                                            (10U)
#define DSP_L1PMPPA21_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1PMPPA21_AIDX_SHIFT                                                                            (9U)
#define DSP_L1PMPPA21_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1PMPPA21_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1PMPPA21_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1PMPPA21_SR_SHIFT                                                                              (5U)
#define DSP_L1PMPPA21_SR_MASK                                                                               (0x00000020U)

#define DSP_L1PMPPA21_SW_SHIFT                                                                              (4U)
#define DSP_L1PMPPA21_SW_MASK                                                                               (0x00000010U)

#define DSP_L1PMPPA21_SX_SHIFT                                                                              (3U)
#define DSP_L1PMPPA21_SX_MASK                                                                               (0x00000008U)

#define DSP_L1PMPPA21_UR_SHIFT                                                                              (2U)
#define DSP_L1PMPPA21_UR_MASK                                                                               (0x00000004U)

#define DSP_L1PMPPA21_UW_SHIFT                                                                              (1U)
#define DSP_L1PMPPA21_UW_MASK                                                                               (0x00000002U)

#define DSP_L1PMPPA21_UX_SHIFT                                                                              (0U)
#define DSP_L1PMPPA21_UX_MASK                                                                               (0x00000001U)

#define DSP_L1PMPPA21_RESV_2_SHIFT                                                                          (6U)
#define DSP_L1PMPPA21_RESV_2_MASK                                                                           (0x000000c0U)

#define DSP_L1PMPPA22_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1PMPPA22_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1PMPPA22_AID5_SHIFT                                                                            (15U)
#define DSP_L1PMPPA22_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1PMPPA22_AID4_SHIFT                                                                            (14U)
#define DSP_L1PMPPA22_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1PMPPA22_AID3_SHIFT                                                                            (13U)
#define DSP_L1PMPPA22_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1PMPPA22_AID2_SHIFT                                                                            (12U)
#define DSP_L1PMPPA22_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1PMPPA22_AID1_SHIFT                                                                            (11U)
#define DSP_L1PMPPA22_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1PMPPA22_AID0_SHIFT                                                                            (10U)
#define DSP_L1PMPPA22_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1PMPPA22_AIDX_SHIFT                                                                            (9U)
#define DSP_L1PMPPA22_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1PMPPA22_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1PMPPA22_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1PMPPA22_SR_SHIFT                                                                              (5U)
#define DSP_L1PMPPA22_SR_MASK                                                                               (0x00000020U)

#define DSP_L1PMPPA22_SW_SHIFT                                                                              (4U)
#define DSP_L1PMPPA22_SW_MASK                                                                               (0x00000010U)

#define DSP_L1PMPPA22_SX_SHIFT                                                                              (3U)
#define DSP_L1PMPPA22_SX_MASK                                                                               (0x00000008U)

#define DSP_L1PMPPA22_UR_SHIFT                                                                              (2U)
#define DSP_L1PMPPA22_UR_MASK                                                                               (0x00000004U)

#define DSP_L1PMPPA22_UW_SHIFT                                                                              (1U)
#define DSP_L1PMPPA22_UW_MASK                                                                               (0x00000002U)

#define DSP_L1PMPPA22_UX_SHIFT                                                                              (0U)
#define DSP_L1PMPPA22_UX_MASK                                                                               (0x00000001U)

#define DSP_L1PMPPA22_RESV_2_SHIFT                                                                          (6U)
#define DSP_L1PMPPA22_RESV_2_MASK                                                                           (0x000000c0U)

#define DSP_L1PMPPA23_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1PMPPA23_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1PMPPA23_AID5_SHIFT                                                                            (15U)
#define DSP_L1PMPPA23_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1PMPPA23_AID4_SHIFT                                                                            (14U)
#define DSP_L1PMPPA23_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1PMPPA23_AID3_SHIFT                                                                            (13U)
#define DSP_L1PMPPA23_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1PMPPA23_AID2_SHIFT                                                                            (12U)
#define DSP_L1PMPPA23_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1PMPPA23_AID1_SHIFT                                                                            (11U)
#define DSP_L1PMPPA23_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1PMPPA23_AID0_SHIFT                                                                            (10U)
#define DSP_L1PMPPA23_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1PMPPA23_AIDX_SHIFT                                                                            (9U)
#define DSP_L1PMPPA23_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1PMPPA23_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1PMPPA23_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1PMPPA23_SR_SHIFT                                                                              (5U)
#define DSP_L1PMPPA23_SR_MASK                                                                               (0x00000020U)

#define DSP_L1PMPPA23_SW_SHIFT                                                                              (4U)
#define DSP_L1PMPPA23_SW_MASK                                                                               (0x00000010U)

#define DSP_L1PMPPA23_SX_SHIFT                                                                              (3U)
#define DSP_L1PMPPA23_SX_MASK                                                                               (0x00000008U)

#define DSP_L1PMPPA23_UR_SHIFT                                                                              (2U)
#define DSP_L1PMPPA23_UR_MASK                                                                               (0x00000004U)

#define DSP_L1PMPPA23_UW_SHIFT                                                                              (1U)
#define DSP_L1PMPPA23_UW_MASK                                                                               (0x00000002U)

#define DSP_L1PMPPA23_UX_SHIFT                                                                              (0U)
#define DSP_L1PMPPA23_UX_MASK                                                                               (0x00000001U)

#define DSP_L1PMPPA23_RESV_2_SHIFT                                                                          (6U)
#define DSP_L1PMPPA23_RESV_2_MASK                                                                           (0x000000c0U)

#define DSP_L1PMPPA24_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1PMPPA24_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1PMPPA24_AID5_SHIFT                                                                            (15U)
#define DSP_L1PMPPA24_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1PMPPA24_AID4_SHIFT                                                                            (14U)
#define DSP_L1PMPPA24_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1PMPPA24_AID3_SHIFT                                                                            (13U)
#define DSP_L1PMPPA24_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1PMPPA24_AID2_SHIFT                                                                            (12U)
#define DSP_L1PMPPA24_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1PMPPA24_AID1_SHIFT                                                                            (11U)
#define DSP_L1PMPPA24_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1PMPPA24_AID0_SHIFT                                                                            (10U)
#define DSP_L1PMPPA24_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1PMPPA24_AIDX_SHIFT                                                                            (9U)
#define DSP_L1PMPPA24_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1PMPPA24_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1PMPPA24_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1PMPPA24_SR_SHIFT                                                                              (5U)
#define DSP_L1PMPPA24_SR_MASK                                                                               (0x00000020U)

#define DSP_L1PMPPA24_SW_SHIFT                                                                              (4U)
#define DSP_L1PMPPA24_SW_MASK                                                                               (0x00000010U)

#define DSP_L1PMPPA24_SX_SHIFT                                                                              (3U)
#define DSP_L1PMPPA24_SX_MASK                                                                               (0x00000008U)

#define DSP_L1PMPPA24_UR_SHIFT                                                                              (2U)
#define DSP_L1PMPPA24_UR_MASK                                                                               (0x00000004U)

#define DSP_L1PMPPA24_UW_SHIFT                                                                              (1U)
#define DSP_L1PMPPA24_UW_MASK                                                                               (0x00000002U)

#define DSP_L1PMPPA24_UX_SHIFT                                                                              (0U)
#define DSP_L1PMPPA24_UX_MASK                                                                               (0x00000001U)

#define DSP_L1PMPPA24_RESV_2_SHIFT                                                                          (6U)
#define DSP_L1PMPPA24_RESV_2_MASK                                                                           (0x000000c0U)

#define DSP_L1PMPPA25_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1PMPPA25_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1PMPPA25_AID5_SHIFT                                                                            (15U)
#define DSP_L1PMPPA25_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1PMPPA25_AID4_SHIFT                                                                            (14U)
#define DSP_L1PMPPA25_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1PMPPA25_AID3_SHIFT                                                                            (13U)
#define DSP_L1PMPPA25_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1PMPPA25_AID2_SHIFT                                                                            (12U)
#define DSP_L1PMPPA25_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1PMPPA25_AID1_SHIFT                                                                            (11U)
#define DSP_L1PMPPA25_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1PMPPA25_AID0_SHIFT                                                                            (10U)
#define DSP_L1PMPPA25_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1PMPPA25_AIDX_SHIFT                                                                            (9U)
#define DSP_L1PMPPA25_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1PMPPA25_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1PMPPA25_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1PMPPA25_SR_SHIFT                                                                              (5U)
#define DSP_L1PMPPA25_SR_MASK                                                                               (0x00000020U)

#define DSP_L1PMPPA25_SW_SHIFT                                                                              (4U)
#define DSP_L1PMPPA25_SW_MASK                                                                               (0x00000010U)

#define DSP_L1PMPPA25_SX_SHIFT                                                                              (3U)
#define DSP_L1PMPPA25_SX_MASK                                                                               (0x00000008U)

#define DSP_L1PMPPA25_UR_SHIFT                                                                              (2U)
#define DSP_L1PMPPA25_UR_MASK                                                                               (0x00000004U)

#define DSP_L1PMPPA25_UW_SHIFT                                                                              (1U)
#define DSP_L1PMPPA25_UW_MASK                                                                               (0x00000002U)

#define DSP_L1PMPPA25_UX_SHIFT                                                                              (0U)
#define DSP_L1PMPPA25_UX_MASK                                                                               (0x00000001U)

#define DSP_L1PMPPA25_RESV_2_SHIFT                                                                          (6U)
#define DSP_L1PMPPA25_RESV_2_MASK                                                                           (0x000000c0U)

#define DSP_L1PMPPA26_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1PMPPA26_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1PMPPA26_AID5_SHIFT                                                                            (15U)
#define DSP_L1PMPPA26_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1PMPPA26_AID4_SHIFT                                                                            (14U)
#define DSP_L1PMPPA26_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1PMPPA26_AID3_SHIFT                                                                            (13U)
#define DSP_L1PMPPA26_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1PMPPA26_AID2_SHIFT                                                                            (12U)
#define DSP_L1PMPPA26_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1PMPPA26_AID1_SHIFT                                                                            (11U)
#define DSP_L1PMPPA26_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1PMPPA26_AID0_SHIFT                                                                            (10U)
#define DSP_L1PMPPA26_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1PMPPA26_AIDX_SHIFT                                                                            (9U)
#define DSP_L1PMPPA26_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1PMPPA26_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1PMPPA26_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1PMPPA26_SR_SHIFT                                                                              (5U)
#define DSP_L1PMPPA26_SR_MASK                                                                               (0x00000020U)

#define DSP_L1PMPPA26_SW_SHIFT                                                                              (4U)
#define DSP_L1PMPPA26_SW_MASK                                                                               (0x00000010U)

#define DSP_L1PMPPA26_SX_SHIFT                                                                              (3U)
#define DSP_L1PMPPA26_SX_MASK                                                                               (0x00000008U)

#define DSP_L1PMPPA26_UR_SHIFT                                                                              (2U)
#define DSP_L1PMPPA26_UR_MASK                                                                               (0x00000004U)

#define DSP_L1PMPPA26_UW_SHIFT                                                                              (1U)
#define DSP_L1PMPPA26_UW_MASK                                                                               (0x00000002U)

#define DSP_L1PMPPA26_UX_SHIFT                                                                              (0U)
#define DSP_L1PMPPA26_UX_MASK                                                                               (0x00000001U)

#define DSP_L1PMPPA26_RESV_2_SHIFT                                                                          (6U)
#define DSP_L1PMPPA26_RESV_2_MASK                                                                           (0x000000c0U)

#define DSP_L1PMPPA27_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1PMPPA27_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1PMPPA27_AID5_SHIFT                                                                            (15U)
#define DSP_L1PMPPA27_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1PMPPA27_AID4_SHIFT                                                                            (14U)
#define DSP_L1PMPPA27_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1PMPPA27_AID3_SHIFT                                                                            (13U)
#define DSP_L1PMPPA27_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1PMPPA27_AID2_SHIFT                                                                            (12U)
#define DSP_L1PMPPA27_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1PMPPA27_AID1_SHIFT                                                                            (11U)
#define DSP_L1PMPPA27_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1PMPPA27_AID0_SHIFT                                                                            (10U)
#define DSP_L1PMPPA27_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1PMPPA27_AIDX_SHIFT                                                                            (9U)
#define DSP_L1PMPPA27_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1PMPPA27_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1PMPPA27_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1PMPPA27_SR_SHIFT                                                                              (5U)
#define DSP_L1PMPPA27_SR_MASK                                                                               (0x00000020U)

#define DSP_L1PMPPA27_SW_SHIFT                                                                              (4U)
#define DSP_L1PMPPA27_SW_MASK                                                                               (0x00000010U)

#define DSP_L1PMPPA27_SX_SHIFT                                                                              (3U)
#define DSP_L1PMPPA27_SX_MASK                                                                               (0x00000008U)

#define DSP_L1PMPPA27_UR_SHIFT                                                                              (2U)
#define DSP_L1PMPPA27_UR_MASK                                                                               (0x00000004U)

#define DSP_L1PMPPA27_UW_SHIFT                                                                              (1U)
#define DSP_L1PMPPA27_UW_MASK                                                                               (0x00000002U)

#define DSP_L1PMPPA27_UX_SHIFT                                                                              (0U)
#define DSP_L1PMPPA27_UX_MASK                                                                               (0x00000001U)

#define DSP_L1PMPPA27_RESV_2_SHIFT                                                                          (6U)
#define DSP_L1PMPPA27_RESV_2_MASK                                                                           (0x000000c0U)

#define DSP_L1PMPPA28_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1PMPPA28_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1PMPPA28_AID5_SHIFT                                                                            (15U)
#define DSP_L1PMPPA28_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1PMPPA28_AID4_SHIFT                                                                            (14U)
#define DSP_L1PMPPA28_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1PMPPA28_AID3_SHIFT                                                                            (13U)
#define DSP_L1PMPPA28_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1PMPPA28_AID2_SHIFT                                                                            (12U)
#define DSP_L1PMPPA28_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1PMPPA28_AID1_SHIFT                                                                            (11U)
#define DSP_L1PMPPA28_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1PMPPA28_AID0_SHIFT                                                                            (10U)
#define DSP_L1PMPPA28_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1PMPPA28_AIDX_SHIFT                                                                            (9U)
#define DSP_L1PMPPA28_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1PMPPA28_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1PMPPA28_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1PMPPA28_SR_SHIFT                                                                              (5U)
#define DSP_L1PMPPA28_SR_MASK                                                                               (0x00000020U)

#define DSP_L1PMPPA28_SW_SHIFT                                                                              (4U)
#define DSP_L1PMPPA28_SW_MASK                                                                               (0x00000010U)

#define DSP_L1PMPPA28_SX_SHIFT                                                                              (3U)
#define DSP_L1PMPPA28_SX_MASK                                                                               (0x00000008U)

#define DSP_L1PMPPA28_UR_SHIFT                                                                              (2U)
#define DSP_L1PMPPA28_UR_MASK                                                                               (0x00000004U)

#define DSP_L1PMPPA28_UW_SHIFT                                                                              (1U)
#define DSP_L1PMPPA28_UW_MASK                                                                               (0x00000002U)

#define DSP_L1PMPPA28_UX_SHIFT                                                                              (0U)
#define DSP_L1PMPPA28_UX_MASK                                                                               (0x00000001U)

#define DSP_L1PMPPA28_RESV_2_SHIFT                                                                          (6U)
#define DSP_L1PMPPA28_RESV_2_MASK                                                                           (0x000000c0U)

#define DSP_L1PMPPA29_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1PMPPA29_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1PMPPA29_AID5_SHIFT                                                                            (15U)
#define DSP_L1PMPPA29_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1PMPPA29_AID4_SHIFT                                                                            (14U)
#define DSP_L1PMPPA29_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1PMPPA29_AID3_SHIFT                                                                            (13U)
#define DSP_L1PMPPA29_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1PMPPA29_AID2_SHIFT                                                                            (12U)
#define DSP_L1PMPPA29_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1PMPPA29_AID1_SHIFT                                                                            (11U)
#define DSP_L1PMPPA29_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1PMPPA29_AID0_SHIFT                                                                            (10U)
#define DSP_L1PMPPA29_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1PMPPA29_AIDX_SHIFT                                                                            (9U)
#define DSP_L1PMPPA29_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1PMPPA29_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1PMPPA29_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1PMPPA29_SR_SHIFT                                                                              (5U)
#define DSP_L1PMPPA29_SR_MASK                                                                               (0x00000020U)

#define DSP_L1PMPPA29_SW_SHIFT                                                                              (4U)
#define DSP_L1PMPPA29_SW_MASK                                                                               (0x00000010U)

#define DSP_L1PMPPA29_SX_SHIFT                                                                              (3U)
#define DSP_L1PMPPA29_SX_MASK                                                                               (0x00000008U)

#define DSP_L1PMPPA29_UR_SHIFT                                                                              (2U)
#define DSP_L1PMPPA29_UR_MASK                                                                               (0x00000004U)

#define DSP_L1PMPPA29_UW_SHIFT                                                                              (1U)
#define DSP_L1PMPPA29_UW_MASK                                                                               (0x00000002U)

#define DSP_L1PMPPA29_UX_SHIFT                                                                              (0U)
#define DSP_L1PMPPA29_UX_MASK                                                                               (0x00000001U)

#define DSP_L1PMPPA29_RESV_2_SHIFT                                                                          (6U)
#define DSP_L1PMPPA29_RESV_2_MASK                                                                           (0x000000c0U)

#define DSP_L1PMPPA30_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1PMPPA30_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1PMPPA30_AID5_SHIFT                                                                            (15U)
#define DSP_L1PMPPA30_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1PMPPA30_AID4_SHIFT                                                                            (14U)
#define DSP_L1PMPPA30_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1PMPPA30_AID3_SHIFT                                                                            (13U)
#define DSP_L1PMPPA30_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1PMPPA30_AID2_SHIFT                                                                            (12U)
#define DSP_L1PMPPA30_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1PMPPA30_AID1_SHIFT                                                                            (11U)
#define DSP_L1PMPPA30_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1PMPPA30_AID0_SHIFT                                                                            (10U)
#define DSP_L1PMPPA30_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1PMPPA30_AIDX_SHIFT                                                                            (9U)
#define DSP_L1PMPPA30_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1PMPPA30_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1PMPPA30_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1PMPPA30_SR_SHIFT                                                                              (5U)
#define DSP_L1PMPPA30_SR_MASK                                                                               (0x00000020U)

#define DSP_L1PMPPA30_SW_SHIFT                                                                              (4U)
#define DSP_L1PMPPA30_SW_MASK                                                                               (0x00000010U)

#define DSP_L1PMPPA30_SX_SHIFT                                                                              (3U)
#define DSP_L1PMPPA30_SX_MASK                                                                               (0x00000008U)

#define DSP_L1PMPPA30_UR_SHIFT                                                                              (2U)
#define DSP_L1PMPPA30_UR_MASK                                                                               (0x00000004U)

#define DSP_L1PMPPA30_UW_SHIFT                                                                              (1U)
#define DSP_L1PMPPA30_UW_MASK                                                                               (0x00000002U)

#define DSP_L1PMPPA30_UX_SHIFT                                                                              (0U)
#define DSP_L1PMPPA30_UX_MASK                                                                               (0x00000001U)

#define DSP_L1PMPPA30_RESV_2_SHIFT                                                                          (6U)
#define DSP_L1PMPPA30_RESV_2_MASK                                                                           (0x000000c0U)

#define DSP_L1PMPPA31_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1PMPPA31_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1PMPPA31_AID5_SHIFT                                                                            (15U)
#define DSP_L1PMPPA31_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1PMPPA31_AID4_SHIFT                                                                            (14U)
#define DSP_L1PMPPA31_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1PMPPA31_AID3_SHIFT                                                                            (13U)
#define DSP_L1PMPPA31_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1PMPPA31_AID2_SHIFT                                                                            (12U)
#define DSP_L1PMPPA31_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1PMPPA31_AID1_SHIFT                                                                            (11U)
#define DSP_L1PMPPA31_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1PMPPA31_AID0_SHIFT                                                                            (10U)
#define DSP_L1PMPPA31_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1PMPPA31_AIDX_SHIFT                                                                            (9U)
#define DSP_L1PMPPA31_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1PMPPA31_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1PMPPA31_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1PMPPA31_SR_SHIFT                                                                              (5U)
#define DSP_L1PMPPA31_SR_MASK                                                                               (0x00000020U)

#define DSP_L1PMPPA31_SW_SHIFT                                                                              (4U)
#define DSP_L1PMPPA31_SW_MASK                                                                               (0x00000010U)

#define DSP_L1PMPPA31_SX_SHIFT                                                                              (3U)
#define DSP_L1PMPPA31_SX_MASK                                                                               (0x00000008U)

#define DSP_L1PMPPA31_UR_SHIFT                                                                              (2U)
#define DSP_L1PMPPA31_UR_MASK                                                                               (0x00000004U)

#define DSP_L1PMPPA31_UW_SHIFT                                                                              (1U)
#define DSP_L1PMPPA31_UW_MASK                                                                               (0x00000002U)

#define DSP_L1PMPPA31_UX_SHIFT                                                                              (0U)
#define DSP_L1PMPPA31_UX_MASK                                                                               (0x00000001U)

#define DSP_L1PMPPA31_RESV_2_SHIFT                                                                          (6U)
#define DSP_L1PMPPA31_RESV_2_MASK                                                                           (0x000000c0U)

#define DSP_MPLK1_MPLK_SHIFT                                                                                (0U)
#define DSP_MPLK1_MPLK_MASK                                                                                 (0xffffffffU)

#define DSP_MPLK2_MPLK_SHIFT                                                                                (0U)
#define DSP_MPLK2_MPLK_MASK                                                                                 (0xffffffffU)

#define DSP_MPLK3_MPLK_SHIFT                                                                                (0U)
#define DSP_MPLK3_MPLK_MASK                                                                                 (0xffffffffU)

#define DSP_L1DMPPA17_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1DMPPA17_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1DMPPA17_AID5_SHIFT                                                                            (15U)
#define DSP_L1DMPPA17_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1DMPPA17_AID4_SHIFT                                                                            (14U)
#define DSP_L1DMPPA17_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1DMPPA17_AID3_SHIFT                                                                            (13U)
#define DSP_L1DMPPA17_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1DMPPA17_AID2_SHIFT                                                                            (12U)
#define DSP_L1DMPPA17_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1DMPPA17_AID1_SHIFT                                                                            (11U)
#define DSP_L1DMPPA17_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1DMPPA17_AID0_SHIFT                                                                            (10U)
#define DSP_L1DMPPA17_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1DMPPA17_AIDX_SHIFT                                                                            (9U)
#define DSP_L1DMPPA17_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1DMPPA17_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1DMPPA17_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1DMPPA17_SR_SHIFT                                                                              (5U)
#define DSP_L1DMPPA17_SR_MASK                                                                               (0x00000020U)

#define DSP_L1DMPPA17_SW_SHIFT                                                                              (4U)
#define DSP_L1DMPPA17_SW_MASK                                                                               (0x00000010U)

#define DSP_L1DMPPA17_SX_SHIFT                                                                              (3U)
#define DSP_L1DMPPA17_SX_MASK                                                                               (0x00000008U)

#define DSP_L1DMPPA17_UR_SHIFT                                                                              (2U)
#define DSP_L1DMPPA17_UR_MASK                                                                               (0x00000004U)

#define DSP_L1DMPPA17_UW_SHIFT                                                                              (1U)
#define DSP_L1DMPPA17_UW_MASK                                                                               (0x00000002U)

#define DSP_L1DMPPA17_UX_SHIFT                                                                              (0U)
#define DSP_L1DMPPA17_UX_MASK                                                                               (0x00000001U)

#define DSP_L1DMPPA17_RESV_2_SHIFT                                                                          (6U)
#define DSP_L1DMPPA17_RESV_2_MASK                                                                           (0x000000c0U)

#define DSP_L1DMPPA18_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1DMPPA18_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1DMPPA18_AID5_SHIFT                                                                            (15U)
#define DSP_L1DMPPA18_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1DMPPA18_AID4_SHIFT                                                                            (14U)
#define DSP_L1DMPPA18_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1DMPPA18_AID3_SHIFT                                                                            (13U)
#define DSP_L1DMPPA18_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1DMPPA18_AID2_SHIFT                                                                            (12U)
#define DSP_L1DMPPA18_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1DMPPA18_AID1_SHIFT                                                                            (11U)
#define DSP_L1DMPPA18_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1DMPPA18_AID0_SHIFT                                                                            (10U)
#define DSP_L1DMPPA18_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1DMPPA18_AIDX_SHIFT                                                                            (9U)
#define DSP_L1DMPPA18_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1DMPPA18_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1DMPPA18_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1DMPPA18_NS_SHIFT                                                                              (7U)
#define DSP_L1DMPPA18_NS_MASK                                                                               (0x00000080U)

#define DSP_L1DMPPA18_EMU_SHIFT                                                                             (6U)
#define DSP_L1DMPPA18_EMU_MASK                                                                              (0x00000040U)

#define DSP_L1DMPPA18_SR_SHIFT                                                                              (5U)
#define DSP_L1DMPPA18_SR_MASK                                                                               (0x00000020U)

#define DSP_L1DMPPA18_SW_SHIFT                                                                              (4U)
#define DSP_L1DMPPA18_SW_MASK                                                                               (0x00000010U)

#define DSP_L1DMPPA18_SX_SHIFT                                                                              (3U)
#define DSP_L1DMPPA18_SX_MASK                                                                               (0x00000008U)

#define DSP_L1DMPPA18_UR_SHIFT                                                                              (2U)
#define DSP_L1DMPPA18_UR_MASK                                                                               (0x00000004U)

#define DSP_L1DMPPA18_UW_SHIFT                                                                              (1U)
#define DSP_L1DMPPA18_UW_MASK                                                                               (0x00000002U)

#define DSP_L1DMPPA18_UX_SHIFT                                                                              (0U)
#define DSP_L1DMPPA18_UX_MASK                                                                               (0x00000001U)

#define DSP_L1DMPPA19_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1DMPPA19_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1DMPPA19_AID5_SHIFT                                                                            (15U)
#define DSP_L1DMPPA19_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1DMPPA19_AID4_SHIFT                                                                            (14U)
#define DSP_L1DMPPA19_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1DMPPA19_AID3_SHIFT                                                                            (13U)
#define DSP_L1DMPPA19_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1DMPPA19_AID2_SHIFT                                                                            (12U)
#define DSP_L1DMPPA19_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1DMPPA19_AID1_SHIFT                                                                            (11U)
#define DSP_L1DMPPA19_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1DMPPA19_AID0_SHIFT                                                                            (10U)
#define DSP_L1DMPPA19_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1DMPPA19_AIDX_SHIFT                                                                            (9U)
#define DSP_L1DMPPA19_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1DMPPA19_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1DMPPA19_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1DMPPA19_NS_SHIFT                                                                              (7U)
#define DSP_L1DMPPA19_NS_MASK                                                                               (0x00000080U)

#define DSP_L1DMPPA19_EMU_SHIFT                                                                             (6U)
#define DSP_L1DMPPA19_EMU_MASK                                                                              (0x00000040U)

#define DSP_L1DMPPA19_SR_SHIFT                                                                              (5U)
#define DSP_L1DMPPA19_SR_MASK                                                                               (0x00000020U)

#define DSP_L1DMPPA19_SW_SHIFT                                                                              (4U)
#define DSP_L1DMPPA19_SW_MASK                                                                               (0x00000010U)

#define DSP_L1DMPPA19_SX_SHIFT                                                                              (3U)
#define DSP_L1DMPPA19_SX_MASK                                                                               (0x00000008U)

#define DSP_L1DMPPA19_UR_SHIFT                                                                              (2U)
#define DSP_L1DMPPA19_UR_MASK                                                                               (0x00000004U)

#define DSP_L1DMPPA19_UW_SHIFT                                                                              (1U)
#define DSP_L1DMPPA19_UW_MASK                                                                               (0x00000002U)

#define DSP_L1DMPPA19_UX_SHIFT                                                                              (0U)
#define DSP_L1DMPPA19_UX_MASK                                                                               (0x00000001U)

#define DSP_L1DMPPA20_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1DMPPA20_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1DMPPA20_AID5_SHIFT                                                                            (15U)
#define DSP_L1DMPPA20_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1DMPPA20_AID4_SHIFT                                                                            (14U)
#define DSP_L1DMPPA20_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1DMPPA20_AID3_SHIFT                                                                            (13U)
#define DSP_L1DMPPA20_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1DMPPA20_AID2_SHIFT                                                                            (12U)
#define DSP_L1DMPPA20_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1DMPPA20_AID1_SHIFT                                                                            (11U)
#define DSP_L1DMPPA20_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1DMPPA20_AID0_SHIFT                                                                            (10U)
#define DSP_L1DMPPA20_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1DMPPA20_AIDX_SHIFT                                                                            (9U)
#define DSP_L1DMPPA20_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1DMPPA20_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1DMPPA20_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1DMPPA20_NS_SHIFT                                                                              (7U)
#define DSP_L1DMPPA20_NS_MASK                                                                               (0x00000080U)

#define DSP_L1DMPPA20_EMU_SHIFT                                                                             (6U)
#define DSP_L1DMPPA20_EMU_MASK                                                                              (0x00000040U)

#define DSP_L1DMPPA20_SR_SHIFT                                                                              (5U)
#define DSP_L1DMPPA20_SR_MASK                                                                               (0x00000020U)

#define DSP_L1DMPPA20_SW_SHIFT                                                                              (4U)
#define DSP_L1DMPPA20_SW_MASK                                                                               (0x00000010U)

#define DSP_L1DMPPA20_SX_SHIFT                                                                              (3U)
#define DSP_L1DMPPA20_SX_MASK                                                                               (0x00000008U)

#define DSP_L1DMPPA20_UR_SHIFT                                                                              (2U)
#define DSP_L1DMPPA20_UR_MASK                                                                               (0x00000004U)

#define DSP_L1DMPPA20_UW_SHIFT                                                                              (1U)
#define DSP_L1DMPPA20_UW_MASK                                                                               (0x00000002U)

#define DSP_L1DMPPA20_UX_SHIFT                                                                              (0U)
#define DSP_L1DMPPA20_UX_MASK                                                                               (0x00000001U)

#define DSP_L1DMPPA21_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1DMPPA21_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1DMPPA21_AID5_SHIFT                                                                            (15U)
#define DSP_L1DMPPA21_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1DMPPA21_AID4_SHIFT                                                                            (14U)
#define DSP_L1DMPPA21_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1DMPPA21_AID3_SHIFT                                                                            (13U)
#define DSP_L1DMPPA21_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1DMPPA21_AID2_SHIFT                                                                            (12U)
#define DSP_L1DMPPA21_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1DMPPA21_AID1_SHIFT                                                                            (11U)
#define DSP_L1DMPPA21_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1DMPPA21_AID0_SHIFT                                                                            (10U)
#define DSP_L1DMPPA21_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1DMPPA21_AIDX_SHIFT                                                                            (9U)
#define DSP_L1DMPPA21_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1DMPPA21_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1DMPPA21_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1DMPPA21_NS_SHIFT                                                                              (7U)
#define DSP_L1DMPPA21_NS_MASK                                                                               (0x00000080U)

#define DSP_L1DMPPA21_EMU_SHIFT                                                                             (6U)
#define DSP_L1DMPPA21_EMU_MASK                                                                              (0x00000040U)

#define DSP_L1DMPPA21_SR_SHIFT                                                                              (5U)
#define DSP_L1DMPPA21_SR_MASK                                                                               (0x00000020U)

#define DSP_L1DMPPA21_SW_SHIFT                                                                              (4U)
#define DSP_L1DMPPA21_SW_MASK                                                                               (0x00000010U)

#define DSP_L1DMPPA21_SX_SHIFT                                                                              (3U)
#define DSP_L1DMPPA21_SX_MASK                                                                               (0x00000008U)

#define DSP_L1DMPPA21_UR_SHIFT                                                                              (2U)
#define DSP_L1DMPPA21_UR_MASK                                                                               (0x00000004U)

#define DSP_L1DMPPA21_UW_SHIFT                                                                              (1U)
#define DSP_L1DMPPA21_UW_MASK                                                                               (0x00000002U)

#define DSP_L1DMPPA21_UX_SHIFT                                                                              (0U)
#define DSP_L1DMPPA21_UX_MASK                                                                               (0x00000001U)

#define DSP_L1DMPPA22_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1DMPPA22_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1DMPPA22_AID5_SHIFT                                                                            (15U)
#define DSP_L1DMPPA22_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1DMPPA22_AID4_SHIFT                                                                            (14U)
#define DSP_L1DMPPA22_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1DMPPA22_AID3_SHIFT                                                                            (13U)
#define DSP_L1DMPPA22_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1DMPPA22_AID2_SHIFT                                                                            (12U)
#define DSP_L1DMPPA22_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1DMPPA22_AID1_SHIFT                                                                            (11U)
#define DSP_L1DMPPA22_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1DMPPA22_AID0_SHIFT                                                                            (10U)
#define DSP_L1DMPPA22_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1DMPPA22_AIDX_SHIFT                                                                            (9U)
#define DSP_L1DMPPA22_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1DMPPA22_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1DMPPA22_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1DMPPA22_NS_SHIFT                                                                              (7U)
#define DSP_L1DMPPA22_NS_MASK                                                                               (0x00000080U)

#define DSP_L1DMPPA22_EMU_SHIFT                                                                             (6U)
#define DSP_L1DMPPA22_EMU_MASK                                                                              (0x00000040U)

#define DSP_L1DMPPA22_SR_SHIFT                                                                              (5U)
#define DSP_L1DMPPA22_SR_MASK                                                                               (0x00000020U)

#define DSP_L1DMPPA22_SW_SHIFT                                                                              (4U)
#define DSP_L1DMPPA22_SW_MASK                                                                               (0x00000010U)

#define DSP_L1DMPPA22_SX_SHIFT                                                                              (3U)
#define DSP_L1DMPPA22_SX_MASK                                                                               (0x00000008U)

#define DSP_L1DMPPA22_UR_SHIFT                                                                              (2U)
#define DSP_L1DMPPA22_UR_MASK                                                                               (0x00000004U)

#define DSP_L1DMPPA22_UW_SHIFT                                                                              (1U)
#define DSP_L1DMPPA22_UW_MASK                                                                               (0x00000002U)

#define DSP_L1DMPPA22_UX_SHIFT                                                                              (0U)
#define DSP_L1DMPPA22_UX_MASK                                                                               (0x00000001U)

#define DSP_L1DMPPA23_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1DMPPA23_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1DMPPA23_AID5_SHIFT                                                                            (15U)
#define DSP_L1DMPPA23_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1DMPPA23_AID4_SHIFT                                                                            (14U)
#define DSP_L1DMPPA23_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1DMPPA23_AID3_SHIFT                                                                            (13U)
#define DSP_L1DMPPA23_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1DMPPA23_AID2_SHIFT                                                                            (12U)
#define DSP_L1DMPPA23_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1DMPPA23_AID1_SHIFT                                                                            (11U)
#define DSP_L1DMPPA23_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1DMPPA23_AID0_SHIFT                                                                            (10U)
#define DSP_L1DMPPA23_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1DMPPA23_AIDX_SHIFT                                                                            (9U)
#define DSP_L1DMPPA23_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1DMPPA23_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1DMPPA23_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1DMPPA23_NS_SHIFT                                                                              (7U)
#define DSP_L1DMPPA23_NS_MASK                                                                               (0x00000080U)

#define DSP_L1DMPPA23_EMU_SHIFT                                                                             (6U)
#define DSP_L1DMPPA23_EMU_MASK                                                                              (0x00000040U)

#define DSP_L1DMPPA23_SR_SHIFT                                                                              (5U)
#define DSP_L1DMPPA23_SR_MASK                                                                               (0x00000020U)

#define DSP_L1DMPPA23_SW_SHIFT                                                                              (4U)
#define DSP_L1DMPPA23_SW_MASK                                                                               (0x00000010U)

#define DSP_L1DMPPA23_SX_SHIFT                                                                              (3U)
#define DSP_L1DMPPA23_SX_MASK                                                                               (0x00000008U)

#define DSP_L1DMPPA23_UR_SHIFT                                                                              (2U)
#define DSP_L1DMPPA23_UR_MASK                                                                               (0x00000004U)

#define DSP_L1DMPPA23_UW_SHIFT                                                                              (1U)
#define DSP_L1DMPPA23_UW_MASK                                                                               (0x00000002U)

#define DSP_L1DMPPA23_UX_SHIFT                                                                              (0U)
#define DSP_L1DMPPA23_UX_MASK                                                                               (0x00000001U)

#define DSP_L1DMPPA24_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1DMPPA24_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1DMPPA24_AID5_SHIFT                                                                            (15U)
#define DSP_L1DMPPA24_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1DMPPA24_AID4_SHIFT                                                                            (14U)
#define DSP_L1DMPPA24_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1DMPPA24_AID3_SHIFT                                                                            (13U)
#define DSP_L1DMPPA24_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1DMPPA24_AID2_SHIFT                                                                            (12U)
#define DSP_L1DMPPA24_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1DMPPA24_AID1_SHIFT                                                                            (11U)
#define DSP_L1DMPPA24_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1DMPPA24_AID0_SHIFT                                                                            (10U)
#define DSP_L1DMPPA24_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1DMPPA24_AIDX_SHIFT                                                                            (9U)
#define DSP_L1DMPPA24_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1DMPPA24_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1DMPPA24_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1DMPPA24_NS_SHIFT                                                                              (7U)
#define DSP_L1DMPPA24_NS_MASK                                                                               (0x00000080U)

#define DSP_L1DMPPA24_EMU_SHIFT                                                                             (6U)
#define DSP_L1DMPPA24_EMU_MASK                                                                              (0x00000040U)

#define DSP_L1DMPPA24_SR_SHIFT                                                                              (5U)
#define DSP_L1DMPPA24_SR_MASK                                                                               (0x00000020U)

#define DSP_L1DMPPA24_SW_SHIFT                                                                              (4U)
#define DSP_L1DMPPA24_SW_MASK                                                                               (0x00000010U)

#define DSP_L1DMPPA24_SX_SHIFT                                                                              (3U)
#define DSP_L1DMPPA24_SX_MASK                                                                               (0x00000008U)

#define DSP_L1DMPPA24_UR_SHIFT                                                                              (2U)
#define DSP_L1DMPPA24_UR_MASK                                                                               (0x00000004U)

#define DSP_L1DMPPA24_UW_SHIFT                                                                              (1U)
#define DSP_L1DMPPA24_UW_MASK                                                                               (0x00000002U)

#define DSP_L1DMPPA24_UX_SHIFT                                                                              (0U)
#define DSP_L1DMPPA24_UX_MASK                                                                               (0x00000001U)

#define DSP_L1DMPPA25_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1DMPPA25_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1DMPPA25_AID5_SHIFT                                                                            (15U)
#define DSP_L1DMPPA25_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1DMPPA25_AID4_SHIFT                                                                            (14U)
#define DSP_L1DMPPA25_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1DMPPA25_AID3_SHIFT                                                                            (13U)
#define DSP_L1DMPPA25_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1DMPPA25_AID2_SHIFT                                                                            (12U)
#define DSP_L1DMPPA25_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1DMPPA25_AID1_SHIFT                                                                            (11U)
#define DSP_L1DMPPA25_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1DMPPA25_AID0_SHIFT                                                                            (10U)
#define DSP_L1DMPPA25_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1DMPPA25_AIDX_SHIFT                                                                            (9U)
#define DSP_L1DMPPA25_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1DMPPA25_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1DMPPA25_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1DMPPA25_NS_SHIFT                                                                              (7U)
#define DSP_L1DMPPA25_NS_MASK                                                                               (0x00000080U)

#define DSP_L1DMPPA25_EMU_SHIFT                                                                             (6U)
#define DSP_L1DMPPA25_EMU_MASK                                                                              (0x00000040U)

#define DSP_L1DMPPA25_SR_SHIFT                                                                              (5U)
#define DSP_L1DMPPA25_SR_MASK                                                                               (0x00000020U)

#define DSP_L1DMPPA25_SW_SHIFT                                                                              (4U)
#define DSP_L1DMPPA25_SW_MASK                                                                               (0x00000010U)

#define DSP_L1DMPPA25_SX_SHIFT                                                                              (3U)
#define DSP_L1DMPPA25_SX_MASK                                                                               (0x00000008U)

#define DSP_L1DMPPA25_UR_SHIFT                                                                              (2U)
#define DSP_L1DMPPA25_UR_MASK                                                                               (0x00000004U)

#define DSP_L1DMPPA25_UW_SHIFT                                                                              (1U)
#define DSP_L1DMPPA25_UW_MASK                                                                               (0x00000002U)

#define DSP_L1DMPPA25_UX_SHIFT                                                                              (0U)
#define DSP_L1DMPPA25_UX_MASK                                                                               (0x00000001U)

#define DSP_L1DMPPA26_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1DMPPA26_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1DMPPA26_AID5_SHIFT                                                                            (15U)
#define DSP_L1DMPPA26_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1DMPPA26_AID4_SHIFT                                                                            (14U)
#define DSP_L1DMPPA26_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1DMPPA26_AID3_SHIFT                                                                            (13U)
#define DSP_L1DMPPA26_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1DMPPA26_AID2_SHIFT                                                                            (12U)
#define DSP_L1DMPPA26_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1DMPPA26_AID1_SHIFT                                                                            (11U)
#define DSP_L1DMPPA26_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1DMPPA26_AID0_SHIFT                                                                            (10U)
#define DSP_L1DMPPA26_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1DMPPA26_AIDX_SHIFT                                                                            (9U)
#define DSP_L1DMPPA26_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1DMPPA26_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1DMPPA26_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1DMPPA26_NS_SHIFT                                                                              (7U)
#define DSP_L1DMPPA26_NS_MASK                                                                               (0x00000080U)

#define DSP_L1DMPPA26_EMU_SHIFT                                                                             (6U)
#define DSP_L1DMPPA26_EMU_MASK                                                                              (0x00000040U)

#define DSP_L1DMPPA26_SR_SHIFT                                                                              (5U)
#define DSP_L1DMPPA26_SR_MASK                                                                               (0x00000020U)

#define DSP_L1DMPPA26_SW_SHIFT                                                                              (4U)
#define DSP_L1DMPPA26_SW_MASK                                                                               (0x00000010U)

#define DSP_L1DMPPA26_SX_SHIFT                                                                              (3U)
#define DSP_L1DMPPA26_SX_MASK                                                                               (0x00000008U)

#define DSP_L1DMPPA26_UR_SHIFT                                                                              (2U)
#define DSP_L1DMPPA26_UR_MASK                                                                               (0x00000004U)

#define DSP_L1DMPPA26_UW_SHIFT                                                                              (1U)
#define DSP_L1DMPPA26_UW_MASK                                                                               (0x00000002U)

#define DSP_L1DMPPA26_UX_SHIFT                                                                              (0U)
#define DSP_L1DMPPA26_UX_MASK                                                                               (0x00000001U)

#define DSP_L1DMPPA27_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1DMPPA27_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1DMPPA27_AID5_SHIFT                                                                            (15U)
#define DSP_L1DMPPA27_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1DMPPA27_AID4_SHIFT                                                                            (14U)
#define DSP_L1DMPPA27_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1DMPPA27_AID3_SHIFT                                                                            (13U)
#define DSP_L1DMPPA27_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1DMPPA27_AID2_SHIFT                                                                            (12U)
#define DSP_L1DMPPA27_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1DMPPA27_AID1_SHIFT                                                                            (11U)
#define DSP_L1DMPPA27_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1DMPPA27_AID0_SHIFT                                                                            (10U)
#define DSP_L1DMPPA27_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1DMPPA27_AIDX_SHIFT                                                                            (9U)
#define DSP_L1DMPPA27_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1DMPPA27_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1DMPPA27_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1DMPPA27_NS_SHIFT                                                                              (7U)
#define DSP_L1DMPPA27_NS_MASK                                                                               (0x00000080U)

#define DSP_L1DMPPA27_EMU_SHIFT                                                                             (6U)
#define DSP_L1DMPPA27_EMU_MASK                                                                              (0x00000040U)

#define DSP_L1DMPPA27_SR_SHIFT                                                                              (5U)
#define DSP_L1DMPPA27_SR_MASK                                                                               (0x00000020U)

#define DSP_L1DMPPA27_SW_SHIFT                                                                              (4U)
#define DSP_L1DMPPA27_SW_MASK                                                                               (0x00000010U)

#define DSP_L1DMPPA27_SX_SHIFT                                                                              (3U)
#define DSP_L1DMPPA27_SX_MASK                                                                               (0x00000008U)

#define DSP_L1DMPPA27_UR_SHIFT                                                                              (2U)
#define DSP_L1DMPPA27_UR_MASK                                                                               (0x00000004U)

#define DSP_L1DMPPA27_UW_SHIFT                                                                              (1U)
#define DSP_L1DMPPA27_UW_MASK                                                                               (0x00000002U)

#define DSP_L1DMPPA27_UX_SHIFT                                                                              (0U)
#define DSP_L1DMPPA27_UX_MASK                                                                               (0x00000001U)

#define DSP_L1DMPPA28_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1DMPPA28_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1DMPPA28_AID5_SHIFT                                                                            (15U)
#define DSP_L1DMPPA28_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1DMPPA28_AID4_SHIFT                                                                            (14U)
#define DSP_L1DMPPA28_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1DMPPA28_AID3_SHIFT                                                                            (13U)
#define DSP_L1DMPPA28_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1DMPPA28_AID2_SHIFT                                                                            (12U)
#define DSP_L1DMPPA28_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1DMPPA28_AID1_SHIFT                                                                            (11U)
#define DSP_L1DMPPA28_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1DMPPA28_AID0_SHIFT                                                                            (10U)
#define DSP_L1DMPPA28_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1DMPPA28_AIDX_SHIFT                                                                            (9U)
#define DSP_L1DMPPA28_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1DMPPA28_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1DMPPA28_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1DMPPA28_NS_SHIFT                                                                              (7U)
#define DSP_L1DMPPA28_NS_MASK                                                                               (0x00000080U)

#define DSP_L1DMPPA28_EMU_SHIFT                                                                             (6U)
#define DSP_L1DMPPA28_EMU_MASK                                                                              (0x00000040U)

#define DSP_L1DMPPA28_SR_SHIFT                                                                              (5U)
#define DSP_L1DMPPA28_SR_MASK                                                                               (0x00000020U)

#define DSP_L1DMPPA28_SW_SHIFT                                                                              (4U)
#define DSP_L1DMPPA28_SW_MASK                                                                               (0x00000010U)

#define DSP_L1DMPPA28_SX_SHIFT                                                                              (3U)
#define DSP_L1DMPPA28_SX_MASK                                                                               (0x00000008U)

#define DSP_L1DMPPA28_UR_SHIFT                                                                              (2U)
#define DSP_L1DMPPA28_UR_MASK                                                                               (0x00000004U)

#define DSP_L1DMPPA28_UW_SHIFT                                                                              (1U)
#define DSP_L1DMPPA28_UW_MASK                                                                               (0x00000002U)

#define DSP_L1DMPPA28_UX_SHIFT                                                                              (0U)
#define DSP_L1DMPPA28_UX_MASK                                                                               (0x00000001U)

#define DSP_L1DMPPA29_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1DMPPA29_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1DMPPA29_AID5_SHIFT                                                                            (15U)
#define DSP_L1DMPPA29_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1DMPPA29_AID4_SHIFT                                                                            (14U)
#define DSP_L1DMPPA29_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1DMPPA29_AID3_SHIFT                                                                            (13U)
#define DSP_L1DMPPA29_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1DMPPA29_AID2_SHIFT                                                                            (12U)
#define DSP_L1DMPPA29_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1DMPPA29_AID1_SHIFT                                                                            (11U)
#define DSP_L1DMPPA29_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1DMPPA29_AID0_SHIFT                                                                            (10U)
#define DSP_L1DMPPA29_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1DMPPA29_AIDX_SHIFT                                                                            (9U)
#define DSP_L1DMPPA29_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1DMPPA29_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1DMPPA29_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1DMPPA29_NS_SHIFT                                                                              (7U)
#define DSP_L1DMPPA29_NS_MASK                                                                               (0x00000080U)

#define DSP_L1DMPPA29_EMU_SHIFT                                                                             (6U)
#define DSP_L1DMPPA29_EMU_MASK                                                                              (0x00000040U)

#define DSP_L1DMPPA29_SR_SHIFT                                                                              (5U)
#define DSP_L1DMPPA29_SR_MASK                                                                               (0x00000020U)

#define DSP_L1DMPPA29_SW_SHIFT                                                                              (4U)
#define DSP_L1DMPPA29_SW_MASK                                                                               (0x00000010U)

#define DSP_L1DMPPA29_SX_SHIFT                                                                              (3U)
#define DSP_L1DMPPA29_SX_MASK                                                                               (0x00000008U)

#define DSP_L1DMPPA29_UR_SHIFT                                                                              (2U)
#define DSP_L1DMPPA29_UR_MASK                                                                               (0x00000004U)

#define DSP_L1DMPPA29_UW_SHIFT                                                                              (1U)
#define DSP_L1DMPPA29_UW_MASK                                                                               (0x00000002U)

#define DSP_L1DMPPA29_UX_SHIFT                                                                              (0U)
#define DSP_L1DMPPA29_UX_MASK                                                                               (0x00000001U)

#define DSP_L1DMPPA30_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1DMPPA30_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1DMPPA30_AID5_SHIFT                                                                            (15U)
#define DSP_L1DMPPA30_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1DMPPA30_AID4_SHIFT                                                                            (14U)
#define DSP_L1DMPPA30_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1DMPPA30_AID3_SHIFT                                                                            (13U)
#define DSP_L1DMPPA30_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1DMPPA30_AID2_SHIFT                                                                            (12U)
#define DSP_L1DMPPA30_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1DMPPA30_AID1_SHIFT                                                                            (11U)
#define DSP_L1DMPPA30_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1DMPPA30_AID0_SHIFT                                                                            (10U)
#define DSP_L1DMPPA30_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1DMPPA30_AIDX_SHIFT                                                                            (9U)
#define DSP_L1DMPPA30_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1DMPPA30_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1DMPPA30_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1DMPPA30_NS_SHIFT                                                                              (7U)
#define DSP_L1DMPPA30_NS_MASK                                                                               (0x00000080U)

#define DSP_L1DMPPA30_EMU_SHIFT                                                                             (6U)
#define DSP_L1DMPPA30_EMU_MASK                                                                              (0x00000040U)

#define DSP_L1DMPPA30_SR_SHIFT                                                                              (5U)
#define DSP_L1DMPPA30_SR_MASK                                                                               (0x00000020U)

#define DSP_L1DMPPA30_SW_SHIFT                                                                              (4U)
#define DSP_L1DMPPA30_SW_MASK                                                                               (0x00000010U)

#define DSP_L1DMPPA30_SX_SHIFT                                                                              (3U)
#define DSP_L1DMPPA30_SX_MASK                                                                               (0x00000008U)

#define DSP_L1DMPPA30_UR_SHIFT                                                                              (2U)
#define DSP_L1DMPPA30_UR_MASK                                                                               (0x00000004U)

#define DSP_L1DMPPA30_UW_SHIFT                                                                              (1U)
#define DSP_L1DMPPA30_UW_MASK                                                                               (0x00000002U)

#define DSP_L1DMPPA30_UX_SHIFT                                                                              (0U)
#define DSP_L1DMPPA30_UX_MASK                                                                               (0x00000001U)

#define DSP_L1DMPPA31_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1DMPPA31_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1DMPPA31_AID5_SHIFT                                                                            (15U)
#define DSP_L1DMPPA31_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1DMPPA31_AID4_SHIFT                                                                            (14U)
#define DSP_L1DMPPA31_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1DMPPA31_AID3_SHIFT                                                                            (13U)
#define DSP_L1DMPPA31_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1DMPPA31_AID2_SHIFT                                                                            (12U)
#define DSP_L1DMPPA31_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1DMPPA31_AID1_SHIFT                                                                            (11U)
#define DSP_L1DMPPA31_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1DMPPA31_AID0_SHIFT                                                                            (10U)
#define DSP_L1DMPPA31_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1DMPPA31_AIDX_SHIFT                                                                            (9U)
#define DSP_L1DMPPA31_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1DMPPA31_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1DMPPA31_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1DMPPA31_NS_SHIFT                                                                              (7U)
#define DSP_L1DMPPA31_NS_MASK                                                                               (0x00000080U)

#define DSP_L1DMPPA31_EMU_SHIFT                                                                             (6U)
#define DSP_L1DMPPA31_EMU_MASK                                                                              (0x00000040U)

#define DSP_L1DMPPA31_SR_SHIFT                                                                              (5U)
#define DSP_L1DMPPA31_SR_MASK                                                                               (0x00000020U)

#define DSP_L1DMPPA31_SW_SHIFT                                                                              (4U)
#define DSP_L1DMPPA31_SW_MASK                                                                               (0x00000010U)

#define DSP_L1DMPPA31_SX_SHIFT                                                                              (3U)
#define DSP_L1DMPPA31_SX_MASK                                                                               (0x00000008U)

#define DSP_L1DMPPA31_UR_SHIFT                                                                              (2U)
#define DSP_L1DMPPA31_UR_MASK                                                                               (0x00000004U)

#define DSP_L1DMPPA31_UW_SHIFT                                                                              (1U)
#define DSP_L1DMPPA31_UW_MASK                                                                               (0x00000002U)

#define DSP_L1DMPPA31_UX_SHIFT                                                                              (0U)
#define DSP_L1DMPPA31_UX_MASK                                                                               (0x00000001U)

#define DSP_L1DWWC_RESV_1_SHIFT                                                                             (16U)
#define DSP_L1DWWC_RESV_1_MASK                                                                              (0xffff0000U)

#define DSP_L1DWWC_L1DWWC_SHIFT                                                                             (0U)
#define DSP_L1DWWC_L1DWWC_MASK                                                                              (0x0000ffffU)

#define DSP_MAR_RESV_1_SHIFT                                                                                (4U)
#define DSP_MAR_RESV_1_MASK                                                                                 (0xfffffff0U)

#define DSP_MAR_PFX_SHIFT                                                                                   (3U)
#define DSP_MAR_PFX_MASK                                                                                    (0x00000008U)

#define DSP_MAR_PC_SHIFT                                                                                    (0U)
#define DSP_MAR_PC_MASK                                                                                     (0x00000001U)

#define DSP_MAR_RESV_2_SHIFT                                                                                (1U)
#define DSP_MAR_RESV_2_MASK                                                                                 (0x00000006U)

#define DSP_L2MPPA_RESV_1_SHIFT                                                                             (16U)
#define DSP_L2MPPA_RESV_1_MASK                                                                              (0xffff0000U)

#define DSP_L2MPPA_AID5_SHIFT                                                                               (15U)
#define DSP_L2MPPA_AID5_MASK                                                                                (0x00008000U)

#define DSP_L2MPPA_AID4_SHIFT                                                                               (14U)
#define DSP_L2MPPA_AID4_MASK                                                                                (0x00004000U)

#define DSP_L2MPPA_AID3_SHIFT                                                                               (13U)
#define DSP_L2MPPA_AID3_MASK                                                                                (0x00002000U)

#define DSP_L2MPPA_AID2_SHIFT                                                                               (12U)
#define DSP_L2MPPA_AID2_MASK                                                                                (0x00001000U)

#define DSP_L2MPPA_AID1_SHIFT                                                                               (11U)
#define DSP_L2MPPA_AID1_MASK                                                                                (0x00000800U)

#define DSP_L2MPPA_AID0_SHIFT                                                                               (10U)
#define DSP_L2MPPA_AID0_MASK                                                                                (0x00000400U)

#define DSP_L2MPPA_AIDX_SHIFT                                                                               (9U)
#define DSP_L2MPPA_AIDX_MASK                                                                                (0x00000200U)

#define DSP_L2MPPA_LOCAL_SHIFT                                                                              (8U)
#define DSP_L2MPPA_LOCAL_MASK                                                                               (0x00000100U)

#define DSP_L2MPPA_SR_SHIFT                                                                                 (5U)
#define DSP_L2MPPA_SR_MASK                                                                                  (0x00000020U)

#define DSP_L2MPPA_SW_SHIFT                                                                                 (4U)
#define DSP_L2MPPA_SW_MASK                                                                                  (0x00000010U)

#define DSP_L2MPPA_SX_SHIFT                                                                                 (3U)
#define DSP_L2MPPA_SX_MASK                                                                                  (0x00000008U)

#define DSP_L2MPPA_UR_SHIFT                                                                                 (2U)
#define DSP_L2MPPA_UR_MASK                                                                                  (0x00000004U)

#define DSP_L2MPPA_UW_SHIFT                                                                                 (1U)
#define DSP_L2MPPA_UW_MASK                                                                                  (0x00000002U)

#define DSP_L2MPPA_UX_SHIFT                                                                                 (0U)
#define DSP_L2MPPA_UX_MASK                                                                                  (0x00000001U)

#define DSP_L2MPPA_RESV_2_SHIFT                                                                             (6U)
#define DSP_L2MPPA_RESV_2_MASK                                                                              (0x000000c0U)

#define DSP_L1PMPPA16_RESV_1_SHIFT                                                                          (16U)
#define DSP_L1PMPPA16_RESV_1_MASK                                                                           (0xffff0000U)

#define DSP_L1PMPPA16_AID5_SHIFT                                                                            (15U)
#define DSP_L1PMPPA16_AID5_MASK                                                                             (0x00008000U)

#define DSP_L1PMPPA16_AID4_SHIFT                                                                            (14U)
#define DSP_L1PMPPA16_AID4_MASK                                                                             (0x00004000U)

#define DSP_L1PMPPA16_AID3_SHIFT                                                                            (13U)
#define DSP_L1PMPPA16_AID3_MASK                                                                             (0x00002000U)

#define DSP_L1PMPPA16_AID2_SHIFT                                                                            (12U)
#define DSP_L1PMPPA16_AID2_MASK                                                                             (0x00001000U)

#define DSP_L1PMPPA16_AID1_SHIFT                                                                            (11U)
#define DSP_L1PMPPA16_AID1_MASK                                                                             (0x00000800U)

#define DSP_L1PMPPA16_AID0_SHIFT                                                                            (10U)
#define DSP_L1PMPPA16_AID0_MASK                                                                             (0x00000400U)

#define DSP_L1PMPPA16_AIDX_SHIFT                                                                            (9U)
#define DSP_L1PMPPA16_AIDX_MASK                                                                             (0x00000200U)

#define DSP_L1PMPPA16_LOCAL_SHIFT                                                                           (8U)
#define DSP_L1PMPPA16_LOCAL_MASK                                                                            (0x00000100U)

#define DSP_L1PMPPA16_SR_SHIFT                                                                              (5U)
#define DSP_L1PMPPA16_SR_MASK                                                                               (0x00000020U)

#define DSP_L1PMPPA16_SW_SHIFT                                                                              (4U)
#define DSP_L1PMPPA16_SW_MASK                                                                               (0x00000010U)

#define DSP_L1PMPPA16_SX_SHIFT                                                                              (3U)
#define DSP_L1PMPPA16_SX_MASK                                                                               (0x00000008U)

#define DSP_L1PMPPA16_UR_SHIFT                                                                              (2U)
#define DSP_L1PMPPA16_UR_MASK                                                                               (0x00000004U)

#define DSP_L1PMPPA16_UW_SHIFT                                                                              (1U)
#define DSP_L1PMPPA16_UW_MASK                                                                               (0x00000002U)

#define DSP_L1PMPPA16_UX_SHIFT                                                                              (0U)
#define DSP_L1PMPPA16_UX_MASK                                                                               (0x00000001U)

#define DSP_L1PMPPA16_RESV_2_SHIFT                                                                          (6U)
#define DSP_L1PMPPA16_RESV_2_MASK                                                                           (0x000000c0U)

#define DSP_PAMAP__RESV1_SHIFT                                                                              (3U)
#define DSP_PAMAP__RESV1_MASK                                                                               (0xfffffff8U)

#define DSP_PAMAP_AID_SHIFT                                                                                 (0U)
#define DSP_PAMAP_AID_MASK                                                                                  (0x00000007U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_DSP_ICFG_H_ */
