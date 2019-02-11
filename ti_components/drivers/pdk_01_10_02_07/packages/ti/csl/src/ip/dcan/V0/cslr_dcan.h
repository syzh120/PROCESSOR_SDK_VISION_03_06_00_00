/********************************************************************
 * Copyright (C) 2013-2016 Texas Instruments Incorporated.
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
#ifndef CSLR_DCAN_H
#define CSLR_DCAN_H

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
    volatile Uint32 CTL;
    volatile Uint32 ES;
    volatile Uint32 ERRC;
    volatile Uint32 BTR;
    volatile Uint32 INT;
    volatile Uint32 TEST;
    volatile Uint8  RSVD0[4];
    volatile Uint32 PERR;
    volatile Uint8  RSVD1[96];
    volatile Uint32 ABOTR;
    volatile Uint32 TXRQ_X;
    volatile Uint32 TXRQ12;
    volatile Uint32 TXRQ34;
    volatile Uint32 TXRQ56;
    volatile Uint32 TXRQ78;
    volatile Uint32 NWDAT_X;
    volatile Uint32 NWDAT12;
    volatile Uint32 NWDAT34;
    volatile Uint32 NWDAT56;
    volatile Uint32 NWDAT78;
    volatile Uint32 INTPND_X;
    volatile Uint32 INTPND12;
    volatile Uint32 INTPND34;
    volatile Uint32 INTPND56;
    volatile Uint32 INTPND78;
    volatile Uint32 MSGVAL_X;
    volatile Uint32 MSGVAL12;
    volatile Uint32 MSGVAL34;
    volatile Uint32 MSGVAL56;
    volatile Uint32 MSGVAL78;
    volatile Uint8  RSVD2[4];
    volatile Uint32 INTMUX12;
    volatile Uint32 INTMUX34;
    volatile Uint32 INTMUX56;
    volatile Uint32 INTMUX78;
    volatile Uint8  RSVD3[24];
    volatile Uint32 IF1CMD;
    volatile Uint32 IF1MSK;
    volatile Uint32 IF1ARB;
    volatile Uint32 IF1MCTL;
    volatile Uint32 IF1DATA;
    volatile Uint32 IF1DATB;
    volatile Uint8  RSVD4[8];
    volatile Uint32 IF2CMD;
    volatile Uint32 IF2MSK;
    volatile Uint32 IF2ARB;
    volatile Uint32 IF2MCTL;
    volatile Uint32 IF2DATA;
    volatile Uint32 IF2DATB;
    volatile Uint8  RSVD5[8];
    volatile Uint32 IF3OBS;
    volatile Uint32 IF3MSK;
    volatile Uint32 IF3ARB;
    volatile Uint32 IF3MCTL;
    volatile Uint32 IF3DATA;
    volatile Uint32 IF3DATB;
    volatile Uint8  RSVD6[8];
    volatile Uint32 IF3UPD12;
    volatile Uint32 IF3UPD34;
    volatile Uint32 IF3UPD56;
    volatile Uint32 IF3UPD78;
    volatile Uint8  RSVD7[112];
    volatile Uint32 TIOC;
    volatile Uint32 RIOC;
    volatile Uint8  RSVD8[56];
} CSL_DcanRegs;


/**************************************************************************
* Register Macros
**************************************************************************/
#define CSL_DCAN_CTL                                            (0x0U)
#define CSL_DCAN_ES                                             (0x4U)
#define CSL_DCAN_ERRC                                           (0x8U)
#define CSL_DCAN_BTR                                            (0xCU)
#define CSL_DCAN_INT                                            (0x10U)
#define CSL_DCAN_TEST                                           (0x14U)
#define CSL_DCAN_PERR                                           (0x1CU)
#define CSL_DCAN_ABOTR                                          (0x80U)
#define CSL_DCAN_TXRQ_X                                         (0x84U)
#define CSL_DCAN_TXRQ12                                         (0x88U)
#define CSL_DCAN_TXRQ34                                         (0x8CU)
#define CSL_DCAN_TXRQ56                                         (0x90U)
#define CSL_DCAN_TXRQ78                                         (0x94U)
#define CSL_DCAN_NWDAT_X                                        (0x98U)
#define CSL_DCAN_NWDAT12                                        (0x9CU)
#define CSL_DCAN_NWDAT34                                        (0xA0U)
#define CSL_DCAN_NWDAT56                                        (0xA4U)
#define CSL_DCAN_NWDAT78                                        (0xA8U)
#define CSL_DCAN_INTPND_X                                       (0xACU)
#define CSL_DCAN_INTPND12                                       (0xB0U)
#define CSL_DCAN_INTPND34                                       (0xB4U)
#define CSL_DCAN_INTPND56                                       (0xB8U)
#define CSL_DCAN_INTPND78                                       (0xBCU)
#define CSL_DCAN_MSGVAL_X                                       (0xC0U)
#define CSL_DCAN_MSGVAL12                                       (0xC4U)
#define CSL_DCAN_MSGVAL34                                       (0xC8U)
#define CSL_DCAN_MSGVAL56                                       (0xCCU)
#define CSL_DCAN_MSGVAL78                                       (0xD0U)
#define CSL_DCAN_INTMUX12                                       (0xD8U)
#define CSL_DCAN_INTMUX34                                       (0xDCU)
#define CSL_DCAN_INTMUX56                                       (0xE0U)
#define CSL_DCAN_INTMUX78                                       (0xE4U)
#define CSL_DCAN_IF1CMD                                         (0x100U)
#define CSL_DCAN_IF1MSK                                         (0x104U)
#define CSL_DCAN_IF1ARB                                         (0x108U)
#define CSL_DCAN_IF1MCTL                                        (0x10CU)
#define CSL_DCAN_IF1DATA                                        (0x110U)
#define CSL_DCAN_IF1DATB                                        (0x114U)
#define CSL_DCAN_IF2CMD                                         (0x120U)
#define CSL_DCAN_IF2MSK                                         (0x124U)
#define CSL_DCAN_IF2ARB                                         (0x128U)
#define CSL_DCAN_IF2MCTL                                        (0x12CU)
#define CSL_DCAN_IF2DATA                                        (0x130U)
#define CSL_DCAN_IF2DATB                                        (0x134U)
#define CSL_DCAN_IF3OBS                                         (0x140U)
#define CSL_DCAN_IF3MSK                                         (0x144U)
#define CSL_DCAN_IF3ARB                                         (0x148U)
#define CSL_DCAN_IF3MCTL                                        (0x14CU)
#define CSL_DCAN_IF3DATA                                        (0x150U)
#define CSL_DCAN_IF3DATB                                        (0x154U)
#define CSL_DCAN_IF3UPD12                                       (0x160U)
#define CSL_DCAN_IF3UPD34                                       (0x164U)
#define CSL_DCAN_IF3UPD56                                       (0x168U)
#define CSL_DCAN_IF3UPD78                                       (0x16CU)
#define CSL_DCAN_TIOC                                           (0x1E0U)
#define CSL_DCAN_RIOC                                           (0x1E4U)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* CTL */

#define CSL_DCAN_CTL_INIT_MASK                                  (0x00000001U)
#define CSL_DCAN_CTL_INIT_SHIFT                                 (0U)
#define CSL_DCAN_CTL_INIT_RESETVAL                              (0x00000001U)
#define CSL_DCAN_CTL_INIT_EN_1_0X0                              (0x00000000U)
#define CSL_DCAN_CTL_INIT_EN_2_0X1                              (0x00000001U)

#define CSL_DCAN_CTL_IE0_MASK                                   (0x00000002U)
#define CSL_DCAN_CTL_IE0_SHIFT                                  (1U)
#define CSL_DCAN_CTL_IE0_RESETVAL                               (0x00000000U)
#define CSL_DCAN_CTL_IE0_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_CTL_IE0_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_CTL_SIE_MASK                                   (0x00000004U)
#define CSL_DCAN_CTL_SIE_SHIFT                                  (2U)
#define CSL_DCAN_CTL_SIE_RESETVAL                               (0x00000000U)
#define CSL_DCAN_CTL_SIE_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_CTL_SIE_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_CTL_EIE_MASK                                   (0x00000008U)
#define CSL_DCAN_CTL_EIE_SHIFT                                  (3U)
#define CSL_DCAN_CTL_EIE_RESETVAL                               (0x00000000U)
#define CSL_DCAN_CTL_EIE_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_CTL_EIE_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_CTL_DAR_MASK                                   (0x00000020U)
#define CSL_DCAN_CTL_DAR_SHIFT                                  (5U)
#define CSL_DCAN_CTL_DAR_RESETVAL                               (0x00000000U)
#define CSL_DCAN_CTL_DAR_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_CTL_DAR_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_CTL_CCE_MASK                                   (0x00000040U)
#define CSL_DCAN_CTL_CCE_SHIFT                                  (6U)
#define CSL_DCAN_CTL_CCE_RESETVAL                               (0x00000000U)
#define CSL_DCAN_CTL_CCE_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_CTL_CCE_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_CTL_TEST_MASK                                  (0x00000080U)
#define CSL_DCAN_CTL_TEST_SHIFT                                 (7U)
#define CSL_DCAN_CTL_TEST_RESETVAL                              (0x00000000U)
#define CSL_DCAN_CTL_TEST_EN_1_0X0                              (0x00000000U)
#define CSL_DCAN_CTL_TEST_EN_2_0X1                              (0x00000001U)

#define CSL_DCAN_CTL_IDS_MASK                                   (0x00000100U)
#define CSL_DCAN_CTL_IDS_SHIFT                                  (8U)
#define CSL_DCAN_CTL_IDS_RESETVAL                               (0x00000000U)
#define CSL_DCAN_CTL_IDS_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_CTL_IDS_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_CTL_ABO_MASK                                   (0x00000200U)
#define CSL_DCAN_CTL_ABO_SHIFT                                  (9U)
#define CSL_DCAN_CTL_ABO_RESETVAL                               (0x00000000U)
#define CSL_DCAN_CTL_ABO_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_CTL_ABO_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_CTL_PMD_MASK                                   (0x00003C00U)
#define CSL_DCAN_CTL_PMD_SHIFT                                  (10U)
#define CSL_DCAN_CTL_PMD_RESETVAL                               (0x00000005U)
#define CSL_DCAN_CTL_PMD_MAX                                    (0x0000000fU)

#define CSL_DCAN_CTL_SWR_MASK                                   (0x00008000U)
#define CSL_DCAN_CTL_SWR_SHIFT                                  (15U)
#define CSL_DCAN_CTL_SWR_RESETVAL                               (0x00000000U)
#define CSL_DCAN_CTL_SWR_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_CTL_SWR_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_CTL_INITDBG_MASK                               (0x00010000U)
#define CSL_DCAN_CTL_INITDBG_SHIFT                              (16U)
#define CSL_DCAN_CTL_INITDBG_RESETVAL                           (0x00000000U)
#define CSL_DCAN_CTL_INITDBG_EN_1_0X0                           (0x00000000U)
#define CSL_DCAN_CTL_INITDBG_EN_2_0X1                           (0x00000001U)

#define CSL_DCAN_CTL_IE1_MASK                                   (0x00020000U)
#define CSL_DCAN_CTL_IE1_SHIFT                                  (17U)
#define CSL_DCAN_CTL_IE1_RESETVAL                               (0x00000000U)
#define CSL_DCAN_CTL_IE1_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_CTL_IE1_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_CTL_DE1_MASK                                   (0x00040000U)
#define CSL_DCAN_CTL_DE1_SHIFT                                  (18U)
#define CSL_DCAN_CTL_DE1_RESETVAL                               (0x00000000U)
#define CSL_DCAN_CTL_DE1_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_CTL_DE1_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_CTL_DE2_MASK                                   (0x00080000U)
#define CSL_DCAN_CTL_DE2_SHIFT                                  (19U)
#define CSL_DCAN_CTL_DE2_RESETVAL                               (0x00000000U)
#define CSL_DCAN_CTL_DE2_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_CTL_DE2_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_CTL_DE3_MASK                                   (0x00100000U)
#define CSL_DCAN_CTL_DE3_SHIFT                                  (20U)
#define CSL_DCAN_CTL_DE3_RESETVAL                               (0x00000000U)
#define CSL_DCAN_CTL_DE3_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_CTL_DE3_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_CTL_PDR_MASK                                   (0x01000000U)
#define CSL_DCAN_CTL_PDR_SHIFT                                  (24U)
#define CSL_DCAN_CTL_PDR_RESETVAL                               (0x00000000U)
#define CSL_DCAN_CTL_PDR_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_CTL_PDR_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_CTL_WUBA_MASK                                  (0x02000000U)
#define CSL_DCAN_CTL_WUBA_SHIFT                                 (25U)
#define CSL_DCAN_CTL_WUBA_RESETVAL                              (0x00000000U)
#define CSL_DCAN_CTL_WUBA_EN_1_0X0                              (0x00000000U)
#define CSL_DCAN_CTL_WUBA_EN_2_0X1                              (0x00000001U)

#define CSL_DCAN_CTL_RESETVAL                                   (0x00001401U)

/* ES */

#define CSL_DCAN_ES_LEC_MASK                                    (0x00000007U)
#define CSL_DCAN_ES_LEC_SHIFT                                   (0U)
#define CSL_DCAN_ES_LEC_RESETVAL                                (0x00000007U)
#define CSL_DCAN_ES_LEC_EN_1_0X0                                (0x00000000U)
#define CSL_DCAN_ES_LEC_EN_2_0X1                                (0x00000001U)
#define CSL_DCAN_ES_LEC_EN_3_0X2                                (0x00000002U)
#define CSL_DCAN_ES_LEC_EN_4_0X3                                (0x00000003U)
#define CSL_DCAN_ES_LEC_EN_5_0X4                                (0x00000004U)
#define CSL_DCAN_ES_LEC_EN_6_0X5                                (0x00000005U)
#define CSL_DCAN_ES_LEC_EN_7_0X6                                (0x00000006U)
#define CSL_DCAN_ES_LEC_EN_8_0X7                                (0x00000007U)

#define CSL_DCAN_ES_TXOK_MASK                                   (0x00000008U)
#define CSL_DCAN_ES_TXOK_SHIFT                                  (3U)
#define CSL_DCAN_ES_TXOK_RESETVAL                               (0x00000001U)
#define CSL_DCAN_ES_TXOK_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_ES_TXOK_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_ES_RXOK_MASK                                   (0x00000010U)
#define CSL_DCAN_ES_RXOK_SHIFT                                  (4U)
#define CSL_DCAN_ES_RXOK_RESETVAL                               (0x00000000U)
#define CSL_DCAN_ES_RXOK_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_ES_RXOK_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_ES_EPASS_MASK                                  (0x00000020U)
#define CSL_DCAN_ES_EPASS_SHIFT                                 (5U)
#define CSL_DCAN_ES_EPASS_RESETVAL                              (0x00000001U)
#define CSL_DCAN_ES_EPASS_EN_1_0X0                              (0x00000000U)
#define CSL_DCAN_ES_EPASS_EN_2_0X1                              (0x00000001U)

#define CSL_DCAN_ES_EWARN_MASK                                  (0x00000040U)
#define CSL_DCAN_ES_EWARN_SHIFT                                 (6U)
#define CSL_DCAN_ES_EWARN_RESETVAL                              (0x00000001U)
#define CSL_DCAN_ES_EWARN_EN_1_0X0                              (0x00000000U)
#define CSL_DCAN_ES_EWARN_EN_2_0X1                              (0x00000001U)

#define CSL_DCAN_ES_BOFF_MASK                                   (0x00000080U)
#define CSL_DCAN_ES_BOFF_SHIFT                                  (7U)
#define CSL_DCAN_ES_BOFF_RESETVAL                               (0x00000000U)
#define CSL_DCAN_ES_BOFF_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_ES_BOFF_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_ES_PER__MASK                                   (0x00000100U)
#define CSL_DCAN_ES_PER__SHIFT                                  (8U)
#define CSL_DCAN_ES_PER__RESETVAL                               (0x00000000U)
#define CSL_DCAN_ES_PER__EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_ES_PER__EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_ES_WAKEUP_PND_MASK                             (0x00000200U)
#define CSL_DCAN_ES_WAKEUP_PND_SHIFT                            (9U)
#define CSL_DCAN_ES_WAKEUP_PND_RESETVAL                         (0x00000000U)
#define CSL_DCAN_ES_WAKEUP_PND_EN_1_0X0                         (0x00000000U)
#define CSL_DCAN_ES_WAKEUP_PND_EN_2_0X1                         (0x00000001U)

#define CSL_DCAN_ES_PDA_MASK                                    (0x00000400U)
#define CSL_DCAN_ES_PDA_SHIFT                                   (10U)
#define CSL_DCAN_ES_PDA_RESETVAL                                (0x00000000U)
#define CSL_DCAN_ES_PDA_EN_1_0X0                                (0x00000000U)
#define CSL_DCAN_ES_PDA_EN_2_0X1                                (0x00000001U)

#define CSL_DCAN_ES_RESETVAL                                    (0x0000006fU)

/* ERRC */

#define CSL_DCAN_ERRC_TEC_MASK                                  (0x000000FFU)
#define CSL_DCAN_ERRC_TEC_SHIFT                                 (0U)
#define CSL_DCAN_ERRC_TEC_RESETVAL                              (0x00000000U)
#define CSL_DCAN_ERRC_TEC_MAX                                   (0x000000ffU)

#define CSL_DCAN_ERRC_REC_MASK                                  (0x00007F00U)
#define CSL_DCAN_ERRC_REC_SHIFT                                 (8U)
#define CSL_DCAN_ERRC_REC_RESETVAL                              (0x00000000U)
#define CSL_DCAN_ERRC_REC_MAX                                   (0x0000007fU)

#define CSL_DCAN_ERRC_RP_MASK                                   (0x00008000U)
#define CSL_DCAN_ERRC_RP_SHIFT                                  (15U)
#define CSL_DCAN_ERRC_RP_RESETVAL                               (0x00000000U)
#define CSL_DCAN_ERRC_RP_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_ERRC_RP_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_ERRC_RESETVAL                                  (0x00000000U)

/* BTR */

#define CSL_DCAN_BTR_BRP_MASK                                   (0x0000003FU)
#define CSL_DCAN_BTR_BRP_SHIFT                                  (0U)
#define CSL_DCAN_BTR_BRP_RESETVAL                               (0x00000001U)
#define CSL_DCAN_BTR_BRP_MAX                                    (0x0000003fU)

#define CSL_DCAN_BTR_SJW_MASK                                   (0x000000C0U)
#define CSL_DCAN_BTR_SJW_SHIFT                                  (6U)
#define CSL_DCAN_BTR_SJW_RESETVAL                               (0x00000000U)
#define CSL_DCAN_BTR_SJW_MAX                                    (0x00000003U)

#define CSL_DCAN_BTR_TSEG1_MASK                                 (0x00000F00U)
#define CSL_DCAN_BTR_TSEG1_SHIFT                                (8U)
#define CSL_DCAN_BTR_TSEG1_RESETVAL                             (0x00000003U)
#define CSL_DCAN_BTR_TSEG1_MAX                                  (0x0000000fU)

#define CSL_DCAN_BTR_TSEG2_MASK                                 (0x00007000U)
#define CSL_DCAN_BTR_TSEG2_SHIFT                                (12U)
#define CSL_DCAN_BTR_TSEG2_RESETVAL                             (0x00000002U)
#define CSL_DCAN_BTR_TSEG2_MAX                                  (0x00000007U)

#define CSL_DCAN_BTR_BRPE_MASK                                  (0x000F0000U)
#define CSL_DCAN_BTR_BRPE_SHIFT                                 (16U)
#define CSL_DCAN_BTR_BRPE_RESETVAL                              (0x00000000U)
#define CSL_DCAN_BTR_BRPE_MAX                                   (0x0000000fU)

#define CSL_DCAN_BTR_RESETVAL                                   (0x00002301U)

/* INT */

#define CSL_DCAN_INT_INT0ID_MASK                                (0x0000FFFFU)
#define CSL_DCAN_INT_INT0ID_SHIFT                               (0U)
#define CSL_DCAN_INT_INT0ID_RESETVAL                            (0x00000000U)
#define CSL_DCAN_INT_INT0ID_MAX                                 (0x0000ffffU)

#define CSL_DCAN_INT_INT1ID_MASK                                (0x00FF0000U)
#define CSL_DCAN_INT_INT1ID_SHIFT                               (16U)
#define CSL_DCAN_INT_INT1ID_RESETVAL                            (0x00000000U)
#define CSL_DCAN_INT_INT1ID_MAX                                 (0x000000ffU)

#define CSL_DCAN_INT_RESETVAL                                   (0x00000000U)

/* TEST */

#define CSL_DCAN_TEST_SILENT_MASK                               (0x00000008U)
#define CSL_DCAN_TEST_SILENT_SHIFT                              (3U)
#define CSL_DCAN_TEST_SILENT_RESETVAL                           (0x00000000U)
#define CSL_DCAN_TEST_SILENT_EN_1_0X0                           (0x00000000U)
#define CSL_DCAN_TEST_SILENT_EN_2_0X1                           (0x00000001U)

#define CSL_DCAN_TEST_LBACK_MASK                                (0x00000010U)
#define CSL_DCAN_TEST_LBACK_SHIFT                               (4U)
#define CSL_DCAN_TEST_LBACK_RESETVAL                            (0x00000000U)
#define CSL_DCAN_TEST_LBACK_EN_1_0X0                            (0x00000000U)
#define CSL_DCAN_TEST_LBACK_EN_2_0X1                            (0x00000001U)

#define CSL_DCAN_TEST_TX_MASK                                   (0x00000060U)
#define CSL_DCAN_TEST_TX_SHIFT                                  (5U)
#define CSL_DCAN_TEST_TX_RESETVAL                               (0x00000000U)
#define CSL_DCAN_TEST_TX_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_TEST_TX_EN_2_0X1                               (0x00000001U)
#define CSL_DCAN_TEST_TX_EN_3_0XA                               (0x0000000aU)
#define CSL_DCAN_TEST_TX_EN_4_0XB                               (0x0000000bU)

#define CSL_DCAN_TEST_RX_MASK                                   (0x00000080U)
#define CSL_DCAN_TEST_RX_SHIFT                                  (7U)
#define CSL_DCAN_TEST_RX_RESETVAL                               (0x00000000U)
#define CSL_DCAN_TEST_RX_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_TEST_RX_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_TEST_EXL_MASK                                  (0x00000100U)
#define CSL_DCAN_TEST_EXL_SHIFT                                 (8U)
#define CSL_DCAN_TEST_EXL_RESETVAL                              (0x00000000U)
#define CSL_DCAN_TEST_EXL_EN_1_0X0                              (0x00000000U)
#define CSL_DCAN_TEST_EXL_EN_2_0X1                              (0x00000001U)

#define CSL_DCAN_TEST_RDA_MASK                                  (0x00000200U)
#define CSL_DCAN_TEST_RDA_SHIFT                                 (9U)
#define CSL_DCAN_TEST_RDA_RESETVAL                              (0x00000000U)
#define CSL_DCAN_TEST_RDA_EN_1_0X0                              (0x00000000U)
#define CSL_DCAN_TEST_RDA_EN_2_0X1                              (0x00000001U)

#define CSL_DCAN_TEST_RESETVAL                                  (0x00000000U)

/* PERR */

#define CSL_DCAN_PERR_MESSAGE_NUMBER_MASK                       (0x000000FFU)
#define CSL_DCAN_PERR_MESSAGE_NUMBER_SHIFT                      (0U)
#define CSL_DCAN_PERR_MESSAGE_NUMBER_RESETVAL                   (0x00000000U)
#define CSL_DCAN_PERR_MESSAGE_NUMBER_MAX                        (0x000000ffU)

#define CSL_DCAN_PERR_WORD_NUMBER_MASK                          (0x00000700U)
#define CSL_DCAN_PERR_WORD_NUMBER_SHIFT                         (8U)
#define CSL_DCAN_PERR_WORD_NUMBER_RESETVAL                      (0x00000000U)
#define CSL_DCAN_PERR_WORD_NUMBER_EN_1_0X05                     (0x00000005U)

#define CSL_DCAN_PERR_RESETVAL                                  (0x00000000U)

/* ABOTR */

#define CSL_DCAN_ABOTR_ABO_TIME_MASK                            (0xFFFFFFFFU)
#define CSL_DCAN_ABOTR_ABO_TIME_SHIFT                           (0U)
#define CSL_DCAN_ABOTR_ABO_TIME_RESETVAL                        (0x00000000U)
#define CSL_DCAN_ABOTR_ABO_TIME_MAX                             (0xffffffffU)

#define CSL_DCAN_ABOTR_RESETVAL                                 (0x00000000U)

/* TXRQ_X */

#define CSL_DCAN_TXRQ_X_TXRQSTREG1_MASK                         (0x00000003U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG1_SHIFT                        (0U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG1_RESETVAL                     (0x00000000U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG1_MAX                          (0x00000003U)

#define CSL_DCAN_TXRQ_X_TXRQSTREG2_MASK                         (0x0000000CU)
#define CSL_DCAN_TXRQ_X_TXRQSTREG2_SHIFT                        (2U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG2_RESETVAL                     (0x00000000U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG2_MAX                          (0x00000003U)

#define CSL_DCAN_TXRQ_X_TXRQSTREG3_MASK                         (0x00000030U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG3_SHIFT                        (4U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG3_RESETVAL                     (0x00000000U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG3_MAX                          (0x00000003U)

#define CSL_DCAN_TXRQ_X_TXRQSTREG4_MASK                         (0x000000C0U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG4_SHIFT                        (6U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG4_RESETVAL                     (0x00000000U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG4_MAX                          (0x00000003U)

#define CSL_DCAN_TXRQ_X_TXRQSTREG5_MASK                         (0x00000300U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG5_SHIFT                        (8U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG5_RESETVAL                     (0x00000000U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG5_MAX                          (0x00000003U)

#define CSL_DCAN_TXRQ_X_TXRQSTREG6_MASK                         (0x00000C00U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG6_SHIFT                        (10U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG6_RESETVAL                     (0x00000000U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG6_MAX                          (0x00000003U)

#define CSL_DCAN_TXRQ_X_TXRQSTREG7_MASK                         (0x00003000U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG7_SHIFT                        (12U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG7_RESETVAL                     (0x00000000U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG7_MAX                          (0x00000003U)

#define CSL_DCAN_TXRQ_X_TXRQSTREG8_MASK                         (0x0000C000U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG8_SHIFT                        (14U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG8_RESETVAL                     (0x00000000U)
#define CSL_DCAN_TXRQ_X_TXRQSTREG8_MAX                          (0x00000003U)

#define CSL_DCAN_TXRQ_X_RESETVAL                                (0x00000000U)

/* TXRQ12 */

#define CSL_DCAN_TXRQ12_TXRQS_0_MASK                            (0x0000FFFFU)
#define CSL_DCAN_TXRQ12_TXRQS_0_SHIFT                           (0U)
#define CSL_DCAN_TXRQ12_TXRQS_0_RESETVAL                        (0x00000000U)
#define CSL_DCAN_TXRQ12_TXRQS_0_MAX                             (0x0000ffffU)

#define CSL_DCAN_TXRQ12_TXRQS_1_MASK                            (0xFFFF0000U)
#define CSL_DCAN_TXRQ12_TXRQS_1_SHIFT                           (16U)
#define CSL_DCAN_TXRQ12_TXRQS_1_RESETVAL                        (0x00000000U)
#define CSL_DCAN_TXRQ12_TXRQS_1_MAX                             (0x0000ffffU)

#define CSL_DCAN_TXRQ12_RESETVAL                                (0x00000000U)

/* TXRQ34 */

#define CSL_DCAN_TXRQ34_TXRQS_0_MASK                            (0x0000FFFFU)
#define CSL_DCAN_TXRQ34_TXRQS_0_SHIFT                           (0U)
#define CSL_DCAN_TXRQ34_TXRQS_0_RESETVAL                        (0x00000000U)
#define CSL_DCAN_TXRQ34_TXRQS_0_MAX                             (0x0000ffffU)

#define CSL_DCAN_TXRQ34_TXRQS_1_MASK                            (0xFFFF0000U)
#define CSL_DCAN_TXRQ34_TXRQS_1_SHIFT                           (16U)
#define CSL_DCAN_TXRQ34_TXRQS_1_RESETVAL                        (0x00000000U)
#define CSL_DCAN_TXRQ34_TXRQS_1_MAX                             (0x0000ffffU)

#define CSL_DCAN_TXRQ34_RESETVAL                                (0x00000000U)

/* TXRQ56 */

#define CSL_DCAN_TXRQ56_TXRQS_0_MASK                            (0x0000FFFFU)
#define CSL_DCAN_TXRQ56_TXRQS_0_SHIFT                           (0U)
#define CSL_DCAN_TXRQ56_TXRQS_0_RESETVAL                        (0x00000000U)
#define CSL_DCAN_TXRQ56_TXRQS_0_MAX                             (0x0000ffffU)

#define CSL_DCAN_TXRQ56_TXRQS_1_MASK                            (0xFFFF0000U)
#define CSL_DCAN_TXRQ56_TXRQS_1_SHIFT                           (16U)
#define CSL_DCAN_TXRQ56_TXRQS_1_RESETVAL                        (0x00000000U)
#define CSL_DCAN_TXRQ56_TXRQS_1_MAX                             (0x0000ffffU)

#define CSL_DCAN_TXRQ56_RESETVAL                                (0x00000000U)

/* TXRQ78 */

#define CSL_DCAN_TXRQ78_TXRQS_0_MASK                            (0x0000FFFFU)
#define CSL_DCAN_TXRQ78_TXRQS_0_SHIFT                           (0U)
#define CSL_DCAN_TXRQ78_TXRQS_0_RESETVAL                        (0x00000000U)
#define CSL_DCAN_TXRQ78_TXRQS_0_MAX                             (0x0000ffffU)

#define CSL_DCAN_TXRQ78_TXRQS_1_MASK                            (0xFFFF0000U)
#define CSL_DCAN_TXRQ78_TXRQS_1_SHIFT                           (16U)
#define CSL_DCAN_TXRQ78_TXRQS_1_RESETVAL                        (0x00000000U)
#define CSL_DCAN_TXRQ78_TXRQS_1_MAX                             (0x0000ffffU)

#define CSL_DCAN_TXRQ78_RESETVAL                                (0x00000000U)

/* NWDAT_X */

#define CSL_DCAN_NWDAT_X_NEWDATREG1_MASK                        (0x00000003U)
#define CSL_DCAN_NWDAT_X_NEWDATREG1_SHIFT                       (0U)
#define CSL_DCAN_NWDAT_X_NEWDATREG1_RESETVAL                    (0x00000000U)
#define CSL_DCAN_NWDAT_X_NEWDATREG1_MAX                         (0x00000003U)

#define CSL_DCAN_NWDAT_X_NEWDATREG2_MASK                        (0x0000000CU)
#define CSL_DCAN_NWDAT_X_NEWDATREG2_SHIFT                       (2U)
#define CSL_DCAN_NWDAT_X_NEWDATREG2_RESETVAL                    (0x00000000U)
#define CSL_DCAN_NWDAT_X_NEWDATREG2_MAX                         (0x00000003U)

#define CSL_DCAN_NWDAT_X_NEWDATREG3_MASK                        (0x00000030U)
#define CSL_DCAN_NWDAT_X_NEWDATREG3_SHIFT                       (4U)
#define CSL_DCAN_NWDAT_X_NEWDATREG3_RESETVAL                    (0x00000000U)
#define CSL_DCAN_NWDAT_X_NEWDATREG3_MAX                         (0x00000003U)

#define CSL_DCAN_NWDAT_X_NEWDATREG4_MASK                        (0x000000C0U)
#define CSL_DCAN_NWDAT_X_NEWDATREG4_SHIFT                       (6U)
#define CSL_DCAN_NWDAT_X_NEWDATREG4_RESETVAL                    (0x00000000U)
#define CSL_DCAN_NWDAT_X_NEWDATREG4_MAX                         (0x00000003U)

#define CSL_DCAN_NWDAT_X_NEWDATREG5_MASK                        (0x00000300U)
#define CSL_DCAN_NWDAT_X_NEWDATREG5_SHIFT                       (8U)
#define CSL_DCAN_NWDAT_X_NEWDATREG5_RESETVAL                    (0x00000000U)
#define CSL_DCAN_NWDAT_X_NEWDATREG5_MAX                         (0x00000003U)

#define CSL_DCAN_NWDAT_X_NEWDATREG6_MASK                        (0x00000C00U)
#define CSL_DCAN_NWDAT_X_NEWDATREG6_SHIFT                       (10U)
#define CSL_DCAN_NWDAT_X_NEWDATREG6_RESETVAL                    (0x00000000U)
#define CSL_DCAN_NWDAT_X_NEWDATREG6_MAX                         (0x00000003U)

#define CSL_DCAN_NWDAT_X_NEWDATREG7_MASK                        (0x00003000U)
#define CSL_DCAN_NWDAT_X_NEWDATREG7_SHIFT                       (12U)
#define CSL_DCAN_NWDAT_X_NEWDATREG7_RESETVAL                    (0x00000000U)
#define CSL_DCAN_NWDAT_X_NEWDATREG7_MAX                         (0x00000003U)

#define CSL_DCAN_NWDAT_X_NEWDATREG8_MASK                        (0x0000C000U)
#define CSL_DCAN_NWDAT_X_NEWDATREG8_SHIFT                       (14U)
#define CSL_DCAN_NWDAT_X_NEWDATREG8_RESETVAL                    (0x00000000U)
#define CSL_DCAN_NWDAT_X_NEWDATREG8_MAX                         (0x00000003U)

#define CSL_DCAN_NWDAT_X_RESETVAL                               (0x00000000U)

/* NWDAT12 */

#define CSL_DCAN_NWDAT12_NEWDAT_0_MASK                          (0x0000FFFFU)
#define CSL_DCAN_NWDAT12_NEWDAT_0_SHIFT                         (0U)
#define CSL_DCAN_NWDAT12_NEWDAT_0_RESETVAL                      (0x00000000U)
#define CSL_DCAN_NWDAT12_NEWDAT_0_MAX                           (0x0000ffffU)

#define CSL_DCAN_NWDAT12_NEWDAT_1_MASK                          (0xFFFF0000U)
#define CSL_DCAN_NWDAT12_NEWDAT_1_SHIFT                         (16U)
#define CSL_DCAN_NWDAT12_NEWDAT_1_RESETVAL                      (0x00000000U)
#define CSL_DCAN_NWDAT12_NEWDAT_1_MAX                           (0x0000ffffU)

#define CSL_DCAN_NWDAT12_RESETVAL                               (0x00000000U)

/* NWDAT34 */

#define CSL_DCAN_NWDAT34_NEWDAT_0_MASK                          (0x0000FFFFU)
#define CSL_DCAN_NWDAT34_NEWDAT_0_SHIFT                         (0U)
#define CSL_DCAN_NWDAT34_NEWDAT_0_RESETVAL                      (0x00000000U)
#define CSL_DCAN_NWDAT34_NEWDAT_0_MAX                           (0x0000ffffU)

#define CSL_DCAN_NWDAT34_NEWDAT_1_MASK                          (0xFFFF0000U)
#define CSL_DCAN_NWDAT34_NEWDAT_1_SHIFT                         (16U)
#define CSL_DCAN_NWDAT34_NEWDAT_1_RESETVAL                      (0x00000000U)
#define CSL_DCAN_NWDAT34_NEWDAT_1_MAX                           (0x0000ffffU)

#define CSL_DCAN_NWDAT34_RESETVAL                               (0x00000000U)

/* NWDAT56 */

#define CSL_DCAN_NWDAT56_NEWDAT_0_MASK                          (0x0000FFFFU)
#define CSL_DCAN_NWDAT56_NEWDAT_0_SHIFT                         (0U)
#define CSL_DCAN_NWDAT56_NEWDAT_0_RESETVAL                      (0x00000000U)
#define CSL_DCAN_NWDAT56_NEWDAT_0_MAX                           (0x0000ffffU)

#define CSL_DCAN_NWDAT56_NEWDAT_1_MASK                          (0xFFFF0000U)
#define CSL_DCAN_NWDAT56_NEWDAT_1_SHIFT                         (16U)
#define CSL_DCAN_NWDAT56_NEWDAT_1_RESETVAL                      (0x00000000U)
#define CSL_DCAN_NWDAT56_NEWDAT_1_MAX                           (0x0000ffffU)

#define CSL_DCAN_NWDAT56_RESETVAL                               (0x00000000U)

/* NWDAT78 */

#define CSL_DCAN_NWDAT78_NEWDAT_0_MASK                          (0x0000FFFFU)
#define CSL_DCAN_NWDAT78_NEWDAT_0_SHIFT                         (0U)
#define CSL_DCAN_NWDAT78_NEWDAT_0_RESETVAL                      (0x00000000U)
#define CSL_DCAN_NWDAT78_NEWDAT_0_MAX                           (0x0000ffffU)

#define CSL_DCAN_NWDAT78_NEWDAT_1_MASK                          (0xFFFF0000U)
#define CSL_DCAN_NWDAT78_NEWDAT_1_SHIFT                         (16U)
#define CSL_DCAN_NWDAT78_NEWDAT_1_RESETVAL                      (0x00000000U)
#define CSL_DCAN_NWDAT78_NEWDAT_1_MAX                           (0x0000ffffU)

#define CSL_DCAN_NWDAT78_RESETVAL                               (0x00000000U)

/* INTPND_X */

#define CSL_DCAN_INTPND_X_INTPNDREG1_MASK                       (0x00000003U)
#define CSL_DCAN_INTPND_X_INTPNDREG1_SHIFT                      (0U)
#define CSL_DCAN_INTPND_X_INTPNDREG1_RESETVAL                   (0x00000000U)
#define CSL_DCAN_INTPND_X_INTPNDREG1_MAX                        (0x00000003U)

#define CSL_DCAN_INTPND_X_INTPNDREG2_MASK                       (0x0000000CU)
#define CSL_DCAN_INTPND_X_INTPNDREG2_SHIFT                      (2U)
#define CSL_DCAN_INTPND_X_INTPNDREG2_RESETVAL                   (0x00000000U)
#define CSL_DCAN_INTPND_X_INTPNDREG2_MAX                        (0x00000003U)

#define CSL_DCAN_INTPND_X_INTPNDREG3_MASK                       (0x00000030U)
#define CSL_DCAN_INTPND_X_INTPNDREG3_SHIFT                      (4U)
#define CSL_DCAN_INTPND_X_INTPNDREG3_RESETVAL                   (0x00000000U)
#define CSL_DCAN_INTPND_X_INTPNDREG3_MAX                        (0x00000003U)

#define CSL_DCAN_INTPND_X_INTPNDREG4_MASK                       (0x000000C0U)
#define CSL_DCAN_INTPND_X_INTPNDREG4_SHIFT                      (6U)
#define CSL_DCAN_INTPND_X_INTPNDREG4_RESETVAL                   (0x00000000U)
#define CSL_DCAN_INTPND_X_INTPNDREG4_MAX                        (0x00000003U)

#define CSL_DCAN_INTPND_X_INTPNDREG5_MASK                       (0x00000300U)
#define CSL_DCAN_INTPND_X_INTPNDREG5_SHIFT                      (8U)
#define CSL_DCAN_INTPND_X_INTPNDREG5_RESETVAL                   (0x00000000U)
#define CSL_DCAN_INTPND_X_INTPNDREG5_MAX                        (0x00000003U)

#define CSL_DCAN_INTPND_X_INTPNDREG6_MASK                       (0x00000C00U)
#define CSL_DCAN_INTPND_X_INTPNDREG6_SHIFT                      (10U)
#define CSL_DCAN_INTPND_X_INTPNDREG6_RESETVAL                   (0x00000000U)
#define CSL_DCAN_INTPND_X_INTPNDREG6_MAX                        (0x00000003U)

#define CSL_DCAN_INTPND_X_INTPNDREG7_MASK                       (0x00003000U)
#define CSL_DCAN_INTPND_X_INTPNDREG7_SHIFT                      (12U)
#define CSL_DCAN_INTPND_X_INTPNDREG7_RESETVAL                   (0x00000000U)
#define CSL_DCAN_INTPND_X_INTPNDREG7_MAX                        (0x00000003U)

#define CSL_DCAN_INTPND_X_INTPNDREG8_MASK                       (0x0000C000U)
#define CSL_DCAN_INTPND_X_INTPNDREG8_SHIFT                      (14U)
#define CSL_DCAN_INTPND_X_INTPNDREG8_RESETVAL                   (0x00000000U)
#define CSL_DCAN_INTPND_X_INTPNDREG8_MAX                        (0x00000003U)

#define CSL_DCAN_INTPND_X_RESETVAL                              (0x00000000U)

/* INTPND12 */

#define CSL_DCAN_INTPND12_INTPND_0_MASK                         (0x0000FFFFU)
#define CSL_DCAN_INTPND12_INTPND_0_SHIFT                        (0U)
#define CSL_DCAN_INTPND12_INTPND_0_RESETVAL                     (0x00000000U)
#define CSL_DCAN_INTPND12_INTPND_0_MAX                          (0x0000ffffU)

#define CSL_DCAN_INTPND12_INTPND_1_MASK                         (0xFFFF0000U)
#define CSL_DCAN_INTPND12_INTPND_1_SHIFT                        (16U)
#define CSL_DCAN_INTPND12_INTPND_1_RESETVAL                     (0x00000000U)
#define CSL_DCAN_INTPND12_INTPND_1_MAX                          (0x0000ffffU)

#define CSL_DCAN_INTPND12_RESETVAL                              (0x00000000U)

/* INTPND34 */

#define CSL_DCAN_INTPND34_INTPND_0_MASK                         (0x0000FFFFU)
#define CSL_DCAN_INTPND34_INTPND_0_SHIFT                        (0U)
#define CSL_DCAN_INTPND34_INTPND_0_RESETVAL                     (0x00000000U)
#define CSL_DCAN_INTPND34_INTPND_0_MAX                          (0x0000ffffU)

#define CSL_DCAN_INTPND34_INTPND_1_MASK                         (0xFFFF0000U)
#define CSL_DCAN_INTPND34_INTPND_1_SHIFT                        (16U)
#define CSL_DCAN_INTPND34_INTPND_1_RESETVAL                     (0x00000000U)
#define CSL_DCAN_INTPND34_INTPND_1_MAX                          (0x0000ffffU)

#define CSL_DCAN_INTPND34_RESETVAL                              (0x00000000U)

/* INTPND56 */

#define CSL_DCAN_INTPND56_INTPND_0_MASK                         (0x0000FFFFU)
#define CSL_DCAN_INTPND56_INTPND_0_SHIFT                        (0U)
#define CSL_DCAN_INTPND56_INTPND_0_RESETVAL                     (0x00000000U)
#define CSL_DCAN_INTPND56_INTPND_0_MAX                          (0x0000ffffU)

#define CSL_DCAN_INTPND56_INTPND_1_MASK                         (0xFFFF0000U)
#define CSL_DCAN_INTPND56_INTPND_1_SHIFT                        (16U)
#define CSL_DCAN_INTPND56_INTPND_1_RESETVAL                     (0x00000000U)
#define CSL_DCAN_INTPND56_INTPND_1_MAX                          (0x0000ffffU)

#define CSL_DCAN_INTPND56_RESETVAL                              (0x00000000U)

/* INTPND78 */

#define CSL_DCAN_INTPND78_INTPND_0_MASK                         (0x0000FFFFU)
#define CSL_DCAN_INTPND78_INTPND_0_SHIFT                        (0U)
#define CSL_DCAN_INTPND78_INTPND_0_RESETVAL                     (0x00000000U)
#define CSL_DCAN_INTPND78_INTPND_0_MAX                          (0x0000ffffU)

#define CSL_DCAN_INTPND78_INTPND_1_MASK                         (0xFFFF0000U)
#define CSL_DCAN_INTPND78_INTPND_1_SHIFT                        (16U)
#define CSL_DCAN_INTPND78_INTPND_1_RESETVAL                     (0x00000000U)
#define CSL_DCAN_INTPND78_INTPND_1_MAX                          (0x0000ffffU)

#define CSL_DCAN_INTPND78_RESETVAL                              (0x00000000U)

/* MSGVAL_X */

#define CSL_DCAN_MSGVAL_X_MSGVALREG1_MASK                       (0x00000003U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG1_SHIFT                      (0U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG1_RESETVAL                   (0x00000000U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG1_MAX                        (0x00000003U)

#define CSL_DCAN_MSGVAL_X_MSGVALREG2_MASK                       (0x0000000CU)
#define CSL_DCAN_MSGVAL_X_MSGVALREG2_SHIFT                      (2U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG2_RESETVAL                   (0x00000000U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG2_MAX                        (0x00000003U)

#define CSL_DCAN_MSGVAL_X_MSGVALREG3_MASK                       (0x00000030U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG3_SHIFT                      (4U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG3_RESETVAL                   (0x00000000U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG3_MAX                        (0x00000003U)

#define CSL_DCAN_MSGVAL_X_MSGVALREG4_MASK                       (0x000000C0U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG4_SHIFT                      (6U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG4_RESETVAL                   (0x00000000U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG4_MAX                        (0x00000003U)

#define CSL_DCAN_MSGVAL_X_MSGVALREG5_MASK                       (0x00000300U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG5_SHIFT                      (8U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG5_RESETVAL                   (0x00000000U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG5_MAX                        (0x00000003U)

#define CSL_DCAN_MSGVAL_X_MSGVALREG6_MASK                       (0x00000C00U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG6_SHIFT                      (10U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG6_RESETVAL                   (0x00000000U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG6_MAX                        (0x00000003U)

#define CSL_DCAN_MSGVAL_X_MSGVALREG7_MASK                       (0x00003000U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG7_SHIFT                      (12U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG7_RESETVAL                   (0x00000000U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG7_MAX                        (0x00000003U)

#define CSL_DCAN_MSGVAL_X_MSGVALREG8_MASK                       (0x0000C000U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG8_SHIFT                      (14U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG8_RESETVAL                   (0x00000000U)
#define CSL_DCAN_MSGVAL_X_MSGVALREG8_MAX                        (0x00000003U)

#define CSL_DCAN_MSGVAL_X_RESETVAL                              (0x00000000U)

/* MSGVAL12 */

#define CSL_DCAN_MSGVAL12_MSGVAL_0_MASK                         (0x0000FFFFU)
#define CSL_DCAN_MSGVAL12_MSGVAL_0_SHIFT                        (0U)
#define CSL_DCAN_MSGVAL12_MSGVAL_0_RESETVAL                     (0x00000000U)
#define CSL_DCAN_MSGVAL12_MSGVAL_0_MAX                          (0x0000ffffU)

#define CSL_DCAN_MSGVAL12_MSGVAL_1_MASK                         (0xFFFF0000U)
#define CSL_DCAN_MSGVAL12_MSGVAL_1_SHIFT                        (16U)
#define CSL_DCAN_MSGVAL12_MSGVAL_1_RESETVAL                     (0x00000000U)
#define CSL_DCAN_MSGVAL12_MSGVAL_1_MAX                          (0x0000ffffU)

#define CSL_DCAN_MSGVAL12_RESETVAL                              (0x00000000U)

/* MSGVAL34 */

#define CSL_DCAN_MSGVAL34_MSGVAL_0_MASK                         (0x0000FFFFU)
#define CSL_DCAN_MSGVAL34_MSGVAL_0_SHIFT                        (0U)
#define CSL_DCAN_MSGVAL34_MSGVAL_0_RESETVAL                     (0x00000000U)
#define CSL_DCAN_MSGVAL34_MSGVAL_0_MAX                          (0x0000ffffU)

#define CSL_DCAN_MSGVAL34_MSGVAL_1_MASK                         (0xFFFF0000U)
#define CSL_DCAN_MSGVAL34_MSGVAL_1_SHIFT                        (16U)
#define CSL_DCAN_MSGVAL34_MSGVAL_1_RESETVAL                     (0x00000000U)
#define CSL_DCAN_MSGVAL34_MSGVAL_1_MAX                          (0x0000ffffU)

#define CSL_DCAN_MSGVAL34_RESETVAL                              (0x00000000U)

/* MSGVAL56 */

#define CSL_DCAN_MSGVAL56_MSGVAL_0_MASK                         (0x0000FFFFU)
#define CSL_DCAN_MSGVAL56_MSGVAL_0_SHIFT                        (0U)
#define CSL_DCAN_MSGVAL56_MSGVAL_0_RESETVAL                     (0x00000000U)
#define CSL_DCAN_MSGVAL56_MSGVAL_0_MAX                          (0x0000ffffU)

#define CSL_DCAN_MSGVAL56_MSGVAL_1_MASK                         (0xFFFF0000U)
#define CSL_DCAN_MSGVAL56_MSGVAL_1_SHIFT                        (16U)
#define CSL_DCAN_MSGVAL56_MSGVAL_1_RESETVAL                     (0x00000000U)
#define CSL_DCAN_MSGVAL56_MSGVAL_1_MAX                          (0x0000ffffU)

#define CSL_DCAN_MSGVAL56_RESETVAL                              (0x00000000U)

/* MSGVAL78 */

#define CSL_DCAN_MSGVAL78_MSGVAL_0_MASK                         (0x0000FFFFU)
#define CSL_DCAN_MSGVAL78_MSGVAL_0_SHIFT                        (0U)
#define CSL_DCAN_MSGVAL78_MSGVAL_0_RESETVAL                     (0x00000000U)
#define CSL_DCAN_MSGVAL78_MSGVAL_0_MAX                          (0x0000ffffU)

#define CSL_DCAN_MSGVAL78_MSGVAL_1_MASK                         (0xFFFF0000U)
#define CSL_DCAN_MSGVAL78_MSGVAL_1_SHIFT                        (16U)
#define CSL_DCAN_MSGVAL78_MSGVAL_1_RESETVAL                     (0x00000000U)
#define CSL_DCAN_MSGVAL78_MSGVAL_1_MAX                          (0x0000ffffU)

#define CSL_DCAN_MSGVAL78_RESETVAL                              (0x00000000U)

/* INTMUX12 */

#define CSL_DCAN_INTMUX12_INTMUX_0_MASK                         (0x0000FFFFU)
#define CSL_DCAN_INTMUX12_INTMUX_0_SHIFT                        (0U)
#define CSL_DCAN_INTMUX12_INTMUX_0_RESETVAL                     (0x00000000U)
#define CSL_DCAN_INTMUX12_INTMUX_0_MAX                          (0x0000ffffU)

#define CSL_DCAN_INTMUX12_INTMUX_1_MASK                         (0xFFFF0000U)
#define CSL_DCAN_INTMUX12_INTMUX_1_SHIFT                        (16U)
#define CSL_DCAN_INTMUX12_INTMUX_1_RESETVAL                     (0x00000000U)
#define CSL_DCAN_INTMUX12_INTMUX_1_MAX                          (0x0000ffffU)

#define CSL_DCAN_INTMUX12_RESETVAL                              (0x00000000U)

/* INTMUX34 */

#define CSL_DCAN_INTMUX34_INTMUX_0_MASK                         (0x0000FFFFU)
#define CSL_DCAN_INTMUX34_INTMUX_0_SHIFT                        (0U)
#define CSL_DCAN_INTMUX34_INTMUX_0_RESETVAL                     (0x00000000U)
#define CSL_DCAN_INTMUX34_INTMUX_0_MAX                          (0x0000ffffU)

#define CSL_DCAN_INTMUX34_INTMUX_1_MASK                         (0xFFFF0000U)
#define CSL_DCAN_INTMUX34_INTMUX_1_SHIFT                        (16U)
#define CSL_DCAN_INTMUX34_INTMUX_1_RESETVAL                     (0x00000000U)
#define CSL_DCAN_INTMUX34_INTMUX_1_MAX                          (0x0000ffffU)

#define CSL_DCAN_INTMUX34_RESETVAL                              (0x00000000U)

/* INTMUX56 */

#define CSL_DCAN_INTMUX56_INTMUX_0_MASK                         (0x0000FFFFU)
#define CSL_DCAN_INTMUX56_INTMUX_0_SHIFT                        (0U)
#define CSL_DCAN_INTMUX56_INTMUX_0_RESETVAL                     (0x00000000U)
#define CSL_DCAN_INTMUX56_INTMUX_0_MAX                          (0x0000ffffU)

#define CSL_DCAN_INTMUX56_INTMUX_1_MASK                         (0xFFFF0000U)
#define CSL_DCAN_INTMUX56_INTMUX_1_SHIFT                        (16U)
#define CSL_DCAN_INTMUX56_INTMUX_1_RESETVAL                     (0x00000000U)
#define CSL_DCAN_INTMUX56_INTMUX_1_MAX                          (0x0000ffffU)

#define CSL_DCAN_INTMUX56_RESETVAL                              (0x00000000U)

/* INTMUX78 */

#define CSL_DCAN_INTMUX78_INTMUX_0_MASK                         (0x0000FFFFU)
#define CSL_DCAN_INTMUX78_INTMUX_0_SHIFT                        (0U)
#define CSL_DCAN_INTMUX78_INTMUX_0_RESETVAL                     (0x00000000U)
#define CSL_DCAN_INTMUX78_INTMUX_0_MAX                          (0x0000ffffU)

#define CSL_DCAN_INTMUX78_INTMUX_1_MASK                         (0xFFFF0000U)
#define CSL_DCAN_INTMUX78_INTMUX_1_SHIFT                        (16U)
#define CSL_DCAN_INTMUX78_INTMUX_1_RESETVAL                     (0x00000000U)
#define CSL_DCAN_INTMUX78_INTMUX_1_MAX                          (0x0000ffffU)

#define CSL_DCAN_INTMUX78_RESETVAL                              (0x00000000U)

/* IF1CMD */

#define CSL_DCAN_IF1CMD_MESSAGE_NUMBER_MASK                     (0x000000FFU)
#define CSL_DCAN_IF1CMD_MESSAGE_NUMBER_SHIFT                    (0U)
#define CSL_DCAN_IF1CMD_MESSAGE_NUMBER_RESETVAL                 (0x00000000U)
#define CSL_DCAN_IF1CMD_MESSAGE_NUMBER_MAX                      (0x000000ffU)

#define CSL_DCAN_IF1CMD_DMAACTIVE_MASK                          (0x00004000U)
#define CSL_DCAN_IF1CMD_DMAACTIVE_SHIFT                         (14U)
#define CSL_DCAN_IF1CMD_DMAACTIVE_RESETVAL                      (0x00000000U)
#define CSL_DCAN_IF1CMD_DMAACTIVE_EN_1_0X0                      (0x00000000U)
#define CSL_DCAN_IF1CMD_DMAACTIVE_EN_2_0X1                      (0x00000001U)

#define CSL_DCAN_IF1CMD_BUSY_MASK                               (0x00008000U)
#define CSL_DCAN_IF1CMD_BUSY_SHIFT                              (15U)
#define CSL_DCAN_IF1CMD_BUSY_RESETVAL                           (0x00000000U)
#define CSL_DCAN_IF1CMD_BUSY_EN_1_0X0                           (0x00000000U)
#define CSL_DCAN_IF1CMD_BUSY_EN_2_0X1                           (0x00000001U)

#define CSL_DCAN_IF1CMD_DATA_B_MASK                             (0x00010000U)
#define CSL_DCAN_IF1CMD_DATA_B_SHIFT                            (16U)
#define CSL_DCAN_IF1CMD_DATA_B_RESETVAL                         (0x00000000U)
#define CSL_DCAN_IF1CMD_DATA_B_EN_1_0X0                         (0x00000000U)
#define CSL_DCAN_IF1CMD_DATA_B_EN_2_0X1                         (0x00000001U)

#define CSL_DCAN_IF1CMD_DATA_A_MASK                             (0x00020000U)
#define CSL_DCAN_IF1CMD_DATA_A_SHIFT                            (17U)
#define CSL_DCAN_IF1CMD_DATA_A_RESETVAL                         (0x00000000U)
#define CSL_DCAN_IF1CMD_DATA_A_EN_1_0X0                         (0x00000000U)
#define CSL_DCAN_IF1CMD_DATA_A_EN_2_0X1                         (0x00000001U)

#define CSL_DCAN_IF1CMD_TXRQST_NEWDAT_MASK                      (0x00040000U)
#define CSL_DCAN_IF1CMD_TXRQST_NEWDAT_SHIFT                     (18U)
#define CSL_DCAN_IF1CMD_TXRQST_NEWDAT_RESETVAL                  (0x00000000U)
#define CSL_DCAN_IF1CMD_TXRQST_NEWDAT_EN_1_0X0                  (0x00000000U)
#define CSL_DCAN_IF1CMD_TXRQST_NEWDAT_EN_2_0X1                  (0x00000001U)

#define CSL_DCAN_IF1CMD_CLRINTPND_MASK                          (0x00080000U)
#define CSL_DCAN_IF1CMD_CLRINTPND_SHIFT                         (19U)
#define CSL_DCAN_IF1CMD_CLRINTPND_RESETVAL                      (0x00000000U)
#define CSL_DCAN_IF1CMD_CLRINTPND_EN_1_0X0                      (0x00000000U)
#define CSL_DCAN_IF1CMD_CLRINTPND_EN_2_0X1                      (0x00000001U)

#define CSL_DCAN_IF1CMD_CONTROL_MASK                            (0x00100000U)
#define CSL_DCAN_IF1CMD_CONTROL_SHIFT                           (20U)
#define CSL_DCAN_IF1CMD_CONTROL_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF1CMD_CONTROL_EN_1_0X0                        (0x00000000U)
#define CSL_DCAN_IF1CMD_CONTROL_EN_2_0X1                        (0x00000001U)

#define CSL_DCAN_IF1CMD_ARB_MASK                                (0x00200000U)
#define CSL_DCAN_IF1CMD_ARB_SHIFT                               (21U)
#define CSL_DCAN_IF1CMD_ARB_RESETVAL                            (0x00000000U)
#define CSL_DCAN_IF1CMD_ARB_EN_1_0X0                            (0x00000000U)
#define CSL_DCAN_IF1CMD_ARB_EN_2_0X1                            (0x00000001U)

#define CSL_DCAN_IF1CMD_MASK_MASK                               (0x00400000U)
#define CSL_DCAN_IF1CMD_MASK_SHIFT                              (22U)
#define CSL_DCAN_IF1CMD_MASK_RESETVAL                           (0x00000000U)
#define CSL_DCAN_IF1CMD_MASK_EN_1_0X0                           (0x00000000U)
#define CSL_DCAN_IF1CMD_MASK_EN_2_0X1                           (0x00000001U)

#define CSL_DCAN_IF1CMD_WR_RD_MASK                              (0x00800000U)
#define CSL_DCAN_IF1CMD_WR_RD_SHIFT                             (23U)
#define CSL_DCAN_IF1CMD_WR_RD_RESETVAL                          (0x00000000U)
#define CSL_DCAN_IF1CMD_WR_RD_EN_1_0X0                          (0x00000000U)
#define CSL_DCAN_IF1CMD_WR_RD_EN_2_0X1                          (0x00000001U)

#define CSL_DCAN_IF1CMD_RESETVAL                                (0x00000000U)

/* IF1MSK */

#define CSL_DCAN_IF1MSK_MSK_MASK                                (0x1FFFFFFFU)
#define CSL_DCAN_IF1MSK_MSK_SHIFT                               (0U)
#define CSL_DCAN_IF1MSK_MSK_RESETVAL                            (0x00000000U)
#define CSL_DCAN_IF1MSK_MSK_MAX                                 (0x1fffffffU)

#define CSL_DCAN_IF1MSK_MDIR_MASK                               (0x40000000U)
#define CSL_DCAN_IF1MSK_MDIR_SHIFT                              (30U)
#define CSL_DCAN_IF1MSK_MDIR_RESETVAL                           (0x00000001U)
#define CSL_DCAN_IF1MSK_MDIR_EN_1_0X0                           (0x00000000U)
#define CSL_DCAN_IF1MSK_MDIR_EN_2_0X1                           (0x00000001U)

#define CSL_DCAN_IF1MSK_MXTD_MASK                               (0x80000000U)
#define CSL_DCAN_IF1MSK_MXTD_SHIFT                              (31U)
#define CSL_DCAN_IF1MSK_MXTD_RESETVAL                           (0x00000001U)
#define CSL_DCAN_IF1MSK_MXTD_EN_1_0X0                           (0x00000000U)
#define CSL_DCAN_IF1MSK_MXTD_EN_2_0X1                           (0x00000001U)

#define CSL_DCAN_IF1MSK_RESETVAL                                (0xe0000000U)

/* IF1ARB */

#define CSL_DCAN_IF1ARB_ID28_TO_ID0_MASK                        (0x1FFFFFFFU)
#define CSL_DCAN_IF1ARB_ID28_TO_ID0_SHIFT                       (0U)
#define CSL_DCAN_IF1ARB_ID28_TO_ID0_RESETVAL                    (0x00000000U)
#define CSL_DCAN_IF1ARB_ID28_TO_ID0_MAX                         (0x1fffffffU)

#define CSL_DCAN_IF1ARB_DIR_MASK                                (0x20000000U)
#define CSL_DCAN_IF1ARB_DIR_SHIFT                               (29U)
#define CSL_DCAN_IF1ARB_DIR_RESETVAL                            (0x00000000U)
#define CSL_DCAN_IF1ARB_DIR_EN_1_0X0                            (0x00000000U)
#define CSL_DCAN_IF1ARB_DIR_EN_2_0X1                            (0x00000001U)

#define CSL_DCAN_IF1ARB_XTD_MASK                                (0x40000000U)
#define CSL_DCAN_IF1ARB_XTD_SHIFT                               (30U)
#define CSL_DCAN_IF1ARB_XTD_RESETVAL                            (0x00000000U)
#define CSL_DCAN_IF1ARB_XTD_EN_1_0X0                            (0x00000000U)
#define CSL_DCAN_IF1ARB_XTD_EN_2_0X1                            (0x00000001U)

#define CSL_DCAN_IF1ARB_MSGVAL_MASK                             (0x80000000U)
#define CSL_DCAN_IF1ARB_MSGVAL_SHIFT                            (31U)
#define CSL_DCAN_IF1ARB_MSGVAL_RESETVAL                         (0x00000000U)
#define CSL_DCAN_IF1ARB_MSGVAL_EN_1_0X0                         (0x00000000U)
#define CSL_DCAN_IF1ARB_MSGVAL_EN_2_0X1                         (0x00000001U)

#define CSL_DCAN_IF1ARB_RESETVAL                                (0x00000000U)

/* IF1MCTL */

#define CSL_DCAN_IF1MCTL_DLC_MASK                               (0x0000000FU)
#define CSL_DCAN_IF1MCTL_DLC_SHIFT                              (0U)
#define CSL_DCAN_IF1MCTL_DLC_RESETVAL                           (0x00000000U)
#define CSL_DCAN_IF1MCTL_DLC_MAX                                (0x0000000fU)

#define CSL_DCAN_IF1MCTL_EOB_MASK                               (0x00000080U)
#define CSL_DCAN_IF1MCTL_EOB_SHIFT                              (7U)
#define CSL_DCAN_IF1MCTL_EOB_RESETVAL                           (0x00000000U)
#define CSL_DCAN_IF1MCTL_EOB_EN_1_0X0                           (0x00000000U)
#define CSL_DCAN_IF1MCTL_EOB_EN_2_0X1                           (0x00000001U)

#define CSL_DCAN_IF1MCTL_TXRQST_MASK                            (0x00000100U)
#define CSL_DCAN_IF1MCTL_TXRQST_SHIFT                           (8U)
#define CSL_DCAN_IF1MCTL_TXRQST_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF1MCTL_TXRQST_EN_1_0X0                        (0x00000000U)
#define CSL_DCAN_IF1MCTL_TXRQST_EN_2_0X1                        (0x00000001U)

#define CSL_DCAN_IF1MCTL_RMTEN_MASK                             (0x00000200U)
#define CSL_DCAN_IF1MCTL_RMTEN_SHIFT                            (9U)
#define CSL_DCAN_IF1MCTL_RMTEN_RESETVAL                         (0x00000000U)
#define CSL_DCAN_IF1MCTL_RMTEN_EN_1_0X0                         (0x00000000U)
#define CSL_DCAN_IF1MCTL_RMTEN_EN_2_0X1                         (0x00000001U)

#define CSL_DCAN_IF1MCTL_RXIE_MASK                              (0x00000400U)
#define CSL_DCAN_IF1MCTL_RXIE_SHIFT                             (10U)
#define CSL_DCAN_IF1MCTL_RXIE_RESETVAL                          (0x00000000U)
#define CSL_DCAN_IF1MCTL_RXIE_EN_1_0X0                          (0x00000000U)
#define CSL_DCAN_IF1MCTL_RXIE_EN_2_0X1                          (0x00000001U)

#define CSL_DCAN_IF1MCTL_TXIE_MASK                              (0x00000800U)
#define CSL_DCAN_IF1MCTL_TXIE_SHIFT                             (11U)
#define CSL_DCAN_IF1MCTL_TXIE_RESETVAL                          (0x00000000U)
#define CSL_DCAN_IF1MCTL_TXIE_EN_1_0X0                          (0x00000000U)
#define CSL_DCAN_IF1MCTL_TXIE_EN_2_0X1                          (0x00000001U)

#define CSL_DCAN_IF1MCTL_UMASK_MASK                             (0x00001000U)
#define CSL_DCAN_IF1MCTL_UMASK_SHIFT                            (12U)
#define CSL_DCAN_IF1MCTL_UMASK_RESETVAL                         (0x00000000U)
#define CSL_DCAN_IF1MCTL_UMASK_EN_1_0X0                         (0x00000000U)
#define CSL_DCAN_IF1MCTL_UMASK_EN_2_0X1                         (0x00000001U)

#define CSL_DCAN_IF1MCTL_INTPND_MASK                            (0x00002000U)
#define CSL_DCAN_IF1MCTL_INTPND_SHIFT                           (13U)
#define CSL_DCAN_IF1MCTL_INTPND_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF1MCTL_INTPND_EN_1_0X0                        (0x00000000U)
#define CSL_DCAN_IF1MCTL_INTPND_EN_2_0X1                        (0x00000001U)

#define CSL_DCAN_IF1MCTL_MSGLST_MASK                            (0x00004000U)
#define CSL_DCAN_IF1MCTL_MSGLST_SHIFT                           (14U)
#define CSL_DCAN_IF1MCTL_MSGLST_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF1MCTL_MSGLST_EN_1_0X0                        (0x00000000U)
#define CSL_DCAN_IF1MCTL_MSGLST_EN_2_0X1                        (0x00000001U)

#define CSL_DCAN_IF1MCTL_NEWDAT_MASK                            (0x00008000U)
#define CSL_DCAN_IF1MCTL_NEWDAT_SHIFT                           (15U)
#define CSL_DCAN_IF1MCTL_NEWDAT_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF1MCTL_NEWDAT_EN_1_0X0                        (0x00000000U)
#define CSL_DCAN_IF1MCTL_NEWDAT_EN_2_0X1                        (0x00000001U)

#define CSL_DCAN_IF1MCTL_RESETVAL                               (0x00000000U)

/* IF1DATA */

#define CSL_DCAN_IF1DATA_DATA_0_MASK                            (0x000000FFU)
#define CSL_DCAN_IF1DATA_DATA_0_SHIFT                           (0U)
#define CSL_DCAN_IF1DATA_DATA_0_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF1DATA_DATA_0_MAX                             (0x000000ffU)

#define CSL_DCAN_IF1DATA_DATA_1_MASK                            (0x0000FF00U)
#define CSL_DCAN_IF1DATA_DATA_1_SHIFT                           (8U)
#define CSL_DCAN_IF1DATA_DATA_1_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF1DATA_DATA_1_MAX                             (0x000000ffU)

#define CSL_DCAN_IF1DATA_DATA_2_MASK                            (0x00FF0000U)
#define CSL_DCAN_IF1DATA_DATA_2_SHIFT                           (16U)
#define CSL_DCAN_IF1DATA_DATA_2_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF1DATA_DATA_2_MAX                             (0x000000ffU)

#define CSL_DCAN_IF1DATA_DATA_3_MASK                            (0xFF000000U)
#define CSL_DCAN_IF1DATA_DATA_3_SHIFT                           (24U)
#define CSL_DCAN_IF1DATA_DATA_3_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF1DATA_DATA_3_MAX                             (0x000000ffU)

#define CSL_DCAN_IF1DATA_RESETVAL                               (0x00000000U)

/* IF1DATB */

#define CSL_DCAN_IF1DATB_DATA_4_MASK                            (0x000000FFU)
#define CSL_DCAN_IF1DATB_DATA_4_SHIFT                           (0U)
#define CSL_DCAN_IF1DATB_DATA_4_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF1DATB_DATA_4_MAX                             (0x000000ffU)

#define CSL_DCAN_IF1DATB_DATA_5_MASK                            (0x0000FF00U)
#define CSL_DCAN_IF1DATB_DATA_5_SHIFT                           (8U)
#define CSL_DCAN_IF1DATB_DATA_5_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF1DATB_DATA_5_MAX                             (0x000000ffU)

#define CSL_DCAN_IF1DATB_DATA_6_MASK                            (0x00FF0000U)
#define CSL_DCAN_IF1DATB_DATA_6_SHIFT                           (16U)
#define CSL_DCAN_IF1DATB_DATA_6_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF1DATB_DATA_6_MAX                             (0x000000ffU)

#define CSL_DCAN_IF1DATB_DATA_7_MASK                            (0xFF000000U)
#define CSL_DCAN_IF1DATB_DATA_7_SHIFT                           (24U)
#define CSL_DCAN_IF1DATB_DATA_7_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF1DATB_DATA_7_MAX                             (0x000000ffU)

#define CSL_DCAN_IF1DATB_RESETVAL                               (0x00000000U)

/* IF2CMD */

#define CSL_DCAN_IF2CMD_MESSAGE_NUMBER_MASK                     (0x000000FFU)
#define CSL_DCAN_IF2CMD_MESSAGE_NUMBER_SHIFT                    (0U)
#define CSL_DCAN_IF2CMD_MESSAGE_NUMBER_RESETVAL                 (0x00000000U)
#define CSL_DCAN_IF2CMD_MESSAGE_NUMBER_MAX                      (0x000000ffU)

#define CSL_DCAN_IF2CMD_DMAACTIVE_MASK                          (0x00004000U)
#define CSL_DCAN_IF2CMD_DMAACTIVE_SHIFT                         (14U)
#define CSL_DCAN_IF2CMD_DMAACTIVE_RESETVAL                      (0x00000000U)
#define CSL_DCAN_IF2CMD_DMAACTIVE_EN_1_0X0                      (0x00000000U)
#define CSL_DCAN_IF2CMD_DMAACTIVE_EN_2_0X1                      (0x00000001U)

#define CSL_DCAN_IF2CMD_BUSY_MASK                               (0x00008000U)
#define CSL_DCAN_IF2CMD_BUSY_SHIFT                              (15U)
#define CSL_DCAN_IF2CMD_BUSY_RESETVAL                           (0x00000000U)
#define CSL_DCAN_IF2CMD_BUSY_EN_1_0X0                           (0x00000000U)
#define CSL_DCAN_IF2CMD_BUSY_EN_2_0X1                           (0x00000001U)

#define CSL_DCAN_IF2CMD_DATA_B_MASK                             (0x00010000U)
#define CSL_DCAN_IF2CMD_DATA_B_SHIFT                            (16U)
#define CSL_DCAN_IF2CMD_DATA_B_RESETVAL                         (0x00000000U)
#define CSL_DCAN_IF2CMD_DATA_B_EN_1_0X0                         (0x00000000U)
#define CSL_DCAN_IF2CMD_DATA_B_EN_2_0X1                         (0x00000001U)

#define CSL_DCAN_IF2CMD_DATA_A_MASK                             (0x00020000U)
#define CSL_DCAN_IF2CMD_DATA_A_SHIFT                            (17U)
#define CSL_DCAN_IF2CMD_DATA_A_RESETVAL                         (0x00000000U)
#define CSL_DCAN_IF2CMD_DATA_A_EN_1_0X0                         (0x00000000U)
#define CSL_DCAN_IF2CMD_DATA_A_EN_2_0X1                         (0x00000001U)

#define CSL_DCAN_IF2CMD_TXRQST_NEWDAT_MASK                      (0x00040000U)
#define CSL_DCAN_IF2CMD_TXRQST_NEWDAT_SHIFT                     (18U)
#define CSL_DCAN_IF2CMD_TXRQST_NEWDAT_RESETVAL                  (0x00000000U)
#define CSL_DCAN_IF2CMD_TXRQST_NEWDAT_EN_1_0X0                  (0x00000000U)
#define CSL_DCAN_IF2CMD_TXRQST_NEWDAT_EN_2_0X1                  (0x00000001U)

#define CSL_DCAN_IF2CMD_CLRINTPND_MASK                          (0x00080000U)
#define CSL_DCAN_IF2CMD_CLRINTPND_SHIFT                         (19U)
#define CSL_DCAN_IF2CMD_CLRINTPND_RESETVAL                      (0x00000000U)
#define CSL_DCAN_IF2CMD_CLRINTPND_EN_1_0X0                      (0x00000000U)
#define CSL_DCAN_IF2CMD_CLRINTPND_EN_2_0X1                      (0x00000001U)

#define CSL_DCAN_IF2CMD_CONTROL_MASK                            (0x00100000U)
#define CSL_DCAN_IF2CMD_CONTROL_SHIFT                           (20U)
#define CSL_DCAN_IF2CMD_CONTROL_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF2CMD_CONTROL_EN_1_0X0                        (0x00000000U)
#define CSL_DCAN_IF2CMD_CONTROL_EN_2_0X1                        (0x00000001U)

#define CSL_DCAN_IF2CMD_ARB_MASK                                (0x00200000U)
#define CSL_DCAN_IF2CMD_ARB_SHIFT                               (21U)
#define CSL_DCAN_IF2CMD_ARB_RESETVAL                            (0x00000000U)
#define CSL_DCAN_IF2CMD_ARB_EN_1_0X0                            (0x00000000U)
#define CSL_DCAN_IF2CMD_ARB_EN_2_0X1                            (0x00000001U)

#define CSL_DCAN_IF2CMD_MASK_MASK                               (0x00400000U)
#define CSL_DCAN_IF2CMD_MASK_SHIFT                              (22U)
#define CSL_DCAN_IF2CMD_MASK_RESETVAL                           (0x00000000U)
#define CSL_DCAN_IF2CMD_MASK_EN_1_0X0                           (0x00000000U)
#define CSL_DCAN_IF2CMD_MASK_EN_2_0X1                           (0x00000001U)

#define CSL_DCAN_IF2CMD_WR_RD_MASK                              (0x00800000U)
#define CSL_DCAN_IF2CMD_WR_RD_SHIFT                             (23U)
#define CSL_DCAN_IF2CMD_WR_RD_RESETVAL                          (0x00000000U)
#define CSL_DCAN_IF2CMD_WR_RD_EN_1_0X0                          (0x00000000U)
#define CSL_DCAN_IF2CMD_WR_RD_EN_2_0X1                          (0x00000001U)

#define CSL_DCAN_IF2CMD_RESETVAL                                (0x00000000U)

/* IF2MSK */

#define CSL_DCAN_IF2MSK_MSK_MASK                                (0x1FFFFFFFU)
#define CSL_DCAN_IF2MSK_MSK_SHIFT                               (0U)
#define CSL_DCAN_IF2MSK_MSK_RESETVAL                            (0x00000000U)
#define CSL_DCAN_IF2MSK_MSK_MAX                                 (0x1fffffffU)

#define CSL_DCAN_IF2MSK_MDIR_MASK                               (0x40000000U)
#define CSL_DCAN_IF2MSK_MDIR_SHIFT                              (30U)
#define CSL_DCAN_IF2MSK_MDIR_RESETVAL                           (0x00000001U)
#define CSL_DCAN_IF2MSK_MDIR_EN_1_0X0                           (0x00000000U)
#define CSL_DCAN_IF2MSK_MDIR_EN_2_0X1                           (0x00000001U)

#define CSL_DCAN_IF2MSK_MXTD_MASK                               (0x80000000U)
#define CSL_DCAN_IF2MSK_MXTD_SHIFT                              (31U)
#define CSL_DCAN_IF2MSK_MXTD_RESETVAL                           (0x00000001U)
#define CSL_DCAN_IF2MSK_MXTD_EN_1_0X0                           (0x00000000U)
#define CSL_DCAN_IF2MSK_MXTD_EN_2_0X1                           (0x00000001U)

#define CSL_DCAN_IF2MSK_RESETVAL                                (0xe0000000U)

/* IF2ARB */

#define CSL_DCAN_IF2ARB_ID28_TO_ID0_MASK                        (0x1FFFFFFFU)
#define CSL_DCAN_IF2ARB_ID28_TO_ID0_SHIFT                       (0U)
#define CSL_DCAN_IF2ARB_ID28_TO_ID0_RESETVAL                    (0x00000000U)
#define CSL_DCAN_IF2ARB_ID28_TO_ID0_MAX                         (0x1fffffffU)

#define CSL_DCAN_IF2ARB_DIR_MASK                                (0x20000000U)
#define CSL_DCAN_IF2ARB_DIR_SHIFT                               (29U)
#define CSL_DCAN_IF2ARB_DIR_RESETVAL                            (0x00000000U)
#define CSL_DCAN_IF2ARB_DIR_EN_1_0X0                            (0x00000000U)
#define CSL_DCAN_IF2ARB_DIR_EN_2_0X1                            (0x00000001U)

#define CSL_DCAN_IF2ARB_XTD_MASK                                (0x40000000U)
#define CSL_DCAN_IF2ARB_XTD_SHIFT                               (30U)
#define CSL_DCAN_IF2ARB_XTD_RESETVAL                            (0x00000000U)
#define CSL_DCAN_IF2ARB_XTD_EN_1_0X0                            (0x00000000U)
#define CSL_DCAN_IF2ARB_XTD_EN_2_0X1                            (0x00000001U)

#define CSL_DCAN_IF2ARB_MSGVAL_MASK                             (0x80000000U)
#define CSL_DCAN_IF2ARB_MSGVAL_SHIFT                            (31U)
#define CSL_DCAN_IF2ARB_MSGVAL_RESETVAL                         (0x00000000U)
#define CSL_DCAN_IF2ARB_MSGVAL_EN_1_0X0                         (0x00000000U)
#define CSL_DCAN_IF2ARB_MSGVAL_EN_2_0X1                         (0x00000001U)

#define CSL_DCAN_IF2ARB_RESETVAL                                (0x00000000U)

/* IF2MCTL */

#define CSL_DCAN_IF2MCTL_DLC_MASK                               (0x0000000FU)
#define CSL_DCAN_IF2MCTL_DLC_SHIFT                              (0U)
#define CSL_DCAN_IF2MCTL_DLC_RESETVAL                           (0x00000000U)
#define CSL_DCAN_IF2MCTL_DLC_MAX                                (0x0000000fU)

#define CSL_DCAN_IF2MCTL_EOB_MASK                               (0x00000080U)
#define CSL_DCAN_IF2MCTL_EOB_SHIFT                              (7U)
#define CSL_DCAN_IF2MCTL_EOB_RESETVAL                           (0x00000000U)
#define CSL_DCAN_IF2MCTL_EOB_EN_1_0X0                           (0x00000000U)
#define CSL_DCAN_IF2MCTL_EOB_EN_2_0X1                           (0x00000001U)

#define CSL_DCAN_IF2MCTL_TXRQST_MASK                            (0x00000100U)
#define CSL_DCAN_IF2MCTL_TXRQST_SHIFT                           (8U)
#define CSL_DCAN_IF2MCTL_TXRQST_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF2MCTL_TXRQST_EN_1_0X0                        (0x00000000U)
#define CSL_DCAN_IF2MCTL_TXRQST_EN_2_0X1                        (0x00000001U)

#define CSL_DCAN_IF2MCTL_RMTEN_MASK                             (0x00000200U)
#define CSL_DCAN_IF2MCTL_RMTEN_SHIFT                            (9U)
#define CSL_DCAN_IF2MCTL_RMTEN_RESETVAL                         (0x00000000U)
#define CSL_DCAN_IF2MCTL_RMTEN_EN_1_0X0                         (0x00000000U)
#define CSL_DCAN_IF2MCTL_RMTEN_EN_2_0X1                         (0x00000001U)

#define CSL_DCAN_IF2MCTL_RXIE_MASK                              (0x00000400U)
#define CSL_DCAN_IF2MCTL_RXIE_SHIFT                             (10U)
#define CSL_DCAN_IF2MCTL_RXIE_RESETVAL                          (0x00000000U)
#define CSL_DCAN_IF2MCTL_RXIE_EN_1_0X0                          (0x00000000U)
#define CSL_DCAN_IF2MCTL_RXIE_EN_2_0X1                          (0x00000001U)

#define CSL_DCAN_IF2MCTL_TXIE_MASK                              (0x00000800U)
#define CSL_DCAN_IF2MCTL_TXIE_SHIFT                             (11U)
#define CSL_DCAN_IF2MCTL_TXIE_RESETVAL                          (0x00000000U)
#define CSL_DCAN_IF2MCTL_TXIE_EN_1_0X0                          (0x00000000U)
#define CSL_DCAN_IF2MCTL_TXIE_EN_2_0X1                          (0x00000001U)

#define CSL_DCAN_IF2MCTL_UMASK_MASK                             (0x00001000U)
#define CSL_DCAN_IF2MCTL_UMASK_SHIFT                            (12U)
#define CSL_DCAN_IF2MCTL_UMASK_RESETVAL                         (0x00000000U)
#define CSL_DCAN_IF2MCTL_UMASK_EN_1_0X0                         (0x00000000U)
#define CSL_DCAN_IF2MCTL_UMASK_EN_2_0X1                         (0x00000001U)

#define CSL_DCAN_IF2MCTL_INTPND_MASK                            (0x00002000U)
#define CSL_DCAN_IF2MCTL_INTPND_SHIFT                           (13U)
#define CSL_DCAN_IF2MCTL_INTPND_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF2MCTL_INTPND_EN_1_0X0                        (0x00000000U)
#define CSL_DCAN_IF2MCTL_INTPND_EN_2_0X1                        (0x00000001U)

#define CSL_DCAN_IF2MCTL_MSGLST_MASK                            (0x00004000U)
#define CSL_DCAN_IF2MCTL_MSGLST_SHIFT                           (14U)
#define CSL_DCAN_IF2MCTL_MSGLST_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF2MCTL_MSGLST_EN_1_0X0                        (0x00000000U)
#define CSL_DCAN_IF2MCTL_MSGLST_EN_2_0X1                        (0x00000001U)

#define CSL_DCAN_IF2MCTL_NEWDAT_MASK                            (0x00008000U)
#define CSL_DCAN_IF2MCTL_NEWDAT_SHIFT                           (15U)
#define CSL_DCAN_IF2MCTL_NEWDAT_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF2MCTL_NEWDAT_EN_1_0X0                        (0x00000000U)
#define CSL_DCAN_IF2MCTL_NEWDAT_EN_2_0X1                        (0x00000001U)

#define CSL_DCAN_IF2MCTL_RESETVAL                               (0x00000000U)

/* IF2DATA */

#define CSL_DCAN_IF2DATA_DATA_0_MASK                            (0x000000FFU)
#define CSL_DCAN_IF2DATA_DATA_0_SHIFT                           (0U)
#define CSL_DCAN_IF2DATA_DATA_0_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF2DATA_DATA_0_MAX                             (0x000000ffU)

#define CSL_DCAN_IF2DATA_DATA_1_MASK                            (0x0000FF00U)
#define CSL_DCAN_IF2DATA_DATA_1_SHIFT                           (8U)
#define CSL_DCAN_IF2DATA_DATA_1_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF2DATA_DATA_1_MAX                             (0x000000ffU)

#define CSL_DCAN_IF2DATA_DATA_2_MASK                            (0x00FF0000U)
#define CSL_DCAN_IF2DATA_DATA_2_SHIFT                           (16U)
#define CSL_DCAN_IF2DATA_DATA_2_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF2DATA_DATA_2_MAX                             (0x000000ffU)

#define CSL_DCAN_IF2DATA_DATA_3_MASK                            (0xFF000000U)
#define CSL_DCAN_IF2DATA_DATA_3_SHIFT                           (24U)
#define CSL_DCAN_IF2DATA_DATA_3_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF2DATA_DATA_3_MAX                             (0x000000ffU)

#define CSL_DCAN_IF2DATA_RESETVAL                               (0x00000000U)

/* IF2DATB */

#define CSL_DCAN_IF2DATB_DATA_4_MASK                            (0x000000FFU)
#define CSL_DCAN_IF2DATB_DATA_4_SHIFT                           (0U)
#define CSL_DCAN_IF2DATB_DATA_4_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF2DATB_DATA_4_MAX                             (0x000000ffU)

#define CSL_DCAN_IF2DATB_DATA_5_MASK                            (0x0000FF00U)
#define CSL_DCAN_IF2DATB_DATA_5_SHIFT                           (8U)
#define CSL_DCAN_IF2DATB_DATA_5_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF2DATB_DATA_5_MAX                             (0x000000ffU)

#define CSL_DCAN_IF2DATB_DATA_6_MASK                            (0x00FF0000U)
#define CSL_DCAN_IF2DATB_DATA_6_SHIFT                           (16U)
#define CSL_DCAN_IF2DATB_DATA_6_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF2DATB_DATA_6_MAX                             (0x000000ffU)

#define CSL_DCAN_IF2DATB_DATA_7_MASK                            (0xFF000000U)
#define CSL_DCAN_IF2DATB_DATA_7_SHIFT                           (24U)
#define CSL_DCAN_IF2DATB_DATA_7_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF2DATB_DATA_7_MAX                             (0x000000ffU)

#define CSL_DCAN_IF2DATB_RESETVAL                               (0x00000000U)

/* IF3OBS */

#define CSL_DCAN_IF3OBS_MASK_MASK                               (0x00000001U)
#define CSL_DCAN_IF3OBS_MASK_SHIFT                              (0U)
#define CSL_DCAN_IF3OBS_MASK_RESETVAL                           (0x00000000U)
#define CSL_DCAN_IF3OBS_MASK_EN_1_0X0                           (0x00000000U)
#define CSL_DCAN_IF3OBS_MASK_EN_2_0X1                           (0x00000001U)

#define CSL_DCAN_IF3OBS_ARB_MASK                                (0x00000002U)
#define CSL_DCAN_IF3OBS_ARB_SHIFT                               (1U)
#define CSL_DCAN_IF3OBS_ARB_RESETVAL                            (0x00000000U)
#define CSL_DCAN_IF3OBS_ARB_EN_1_0X0                            (0x00000000U)
#define CSL_DCAN_IF3OBS_ARB_EN_2_0X1                            (0x00000001U)

#define CSL_DCAN_IF3OBS_CTRL_MASK                               (0x00000004U)
#define CSL_DCAN_IF3OBS_CTRL_SHIFT                              (2U)
#define CSL_DCAN_IF3OBS_CTRL_RESETVAL                           (0x00000000U)
#define CSL_DCAN_IF3OBS_CTRL_EN_1_0X0                           (0x00000000U)
#define CSL_DCAN_IF3OBS_CTRL_EN_2_0X1                           (0x00000001U)

#define CSL_DCAN_IF3OBS_DATAA_MASK                              (0x00000008U)
#define CSL_DCAN_IF3OBS_DATAA_SHIFT                             (3U)
#define CSL_DCAN_IF3OBS_DATAA_RESETVAL                          (0x00000000U)
#define CSL_DCAN_IF3OBS_DATAA_EN_1_0X0                          (0x00000000U)
#define CSL_DCAN_IF3OBS_DATAA_EN_2_0X1                          (0x00000001U)

#define CSL_DCAN_IF3OBS_DATAB_MASK                              (0x00000010U)
#define CSL_DCAN_IF3OBS_DATAB_SHIFT                             (4U)
#define CSL_DCAN_IF3OBS_DATAB_RESETVAL                          (0x00000000U)
#define CSL_DCAN_IF3OBS_DATAB_EN_1_0X0                          (0x00000000U)
#define CSL_DCAN_IF3OBS_DATAB_EN_2_0X1                          (0x00000001U)

#define CSL_DCAN_IF3OBS_IF3_SM_MASK                             (0x00000100U)
#define CSL_DCAN_IF3OBS_IF3_SM_SHIFT                            (8U)
#define CSL_DCAN_IF3OBS_IF3_SM_RESETVAL                         (0x00000000U)
#define CSL_DCAN_IF3OBS_IF3_SM_EN_1_0X0                         (0x00000000U)
#define CSL_DCAN_IF3OBS_IF3_SM_EN_2_0X1                         (0x00000001U)

#define CSL_DCAN_IF3OBS_IF3_SA_MASK                             (0x00000200U)
#define CSL_DCAN_IF3OBS_IF3_SA_SHIFT                            (9U)
#define CSL_DCAN_IF3OBS_IF3_SA_RESETVAL                         (0x00000000U)
#define CSL_DCAN_IF3OBS_IF3_SA_EN_1_0X0                         (0x00000000U)
#define CSL_DCAN_IF3OBS_IF3_SA_EN_2_0X1                         (0x00000001U)

#define CSL_DCAN_IF3OBS_IF3_SC_MASK                             (0x00000400U)
#define CSL_DCAN_IF3OBS_IF3_SC_SHIFT                            (10U)
#define CSL_DCAN_IF3OBS_IF3_SC_RESETVAL                         (0x00000000U)
#define CSL_DCAN_IF3OBS_IF3_SC_EN_1_0X0                         (0x00000000U)
#define CSL_DCAN_IF3OBS_IF3_SC_EN_2_0X1                         (0x00000001U)

#define CSL_DCAN_IF3OBS_IF3_SDA_MASK                            (0x00000800U)
#define CSL_DCAN_IF3OBS_IF3_SDA_SHIFT                           (11U)
#define CSL_DCAN_IF3OBS_IF3_SDA_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF3OBS_IF3_SDA_EN_1_0X0                        (0x00000000U)
#define CSL_DCAN_IF3OBS_IF3_SDA_EN_2_0X1                        (0x00000001U)

#define CSL_DCAN_IF3OBS_IF3_SDB_MASK                            (0x00001000U)
#define CSL_DCAN_IF3OBS_IF3_SDB_SHIFT                           (12U)
#define CSL_DCAN_IF3OBS_IF3_SDB_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF3OBS_IF3_SDB_EN_1_0X0                        (0x00000000U)
#define CSL_DCAN_IF3OBS_IF3_SDB_EN_2_0X1                        (0x00000001U)

#define CSL_DCAN_IF3OBS_IF3_UPD_MASK                            (0x00008000U)
#define CSL_DCAN_IF3OBS_IF3_UPD_SHIFT                           (15U)
#define CSL_DCAN_IF3OBS_IF3_UPD_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF3OBS_IF3_UPD_EN_1_0X0                        (0x00000000U)
#define CSL_DCAN_IF3OBS_IF3_UPD_EN_2_0X1                        (0x00000001U)

#define CSL_DCAN_IF3OBS_RESETVAL                                (0x00000000U)

/* IF3MSK */

#define CSL_DCAN_IF3MSK_MSK_MASK                                (0x1FFFFFFFU)
#define CSL_DCAN_IF3MSK_MSK_SHIFT                               (0U)
#define CSL_DCAN_IF3MSK_MSK_RESETVAL                            (0x00000000U)
#define CSL_DCAN_IF3MSK_MSK_MAX                                 (0x1fffffffU)

#define CSL_DCAN_IF3MSK_MDIR_MASK                               (0x40000000U)
#define CSL_DCAN_IF3MSK_MDIR_SHIFT                              (30U)
#define CSL_DCAN_IF3MSK_MDIR_RESETVAL                           (0x00000001U)
#define CSL_DCAN_IF3MSK_MDIR_EN_1_0X0                           (0x00000000U)
#define CSL_DCAN_IF3MSK_MDIR_EN_2_0X1                           (0x00000001U)

#define CSL_DCAN_IF3MSK_MXTD_MASK                               (0x80000000U)
#define CSL_DCAN_IF3MSK_MXTD_SHIFT                              (31U)
#define CSL_DCAN_IF3MSK_MXTD_RESETVAL                           (0x00000001U)
#define CSL_DCAN_IF3MSK_MXTD_EN_1_0X0                           (0x00000000U)
#define CSL_DCAN_IF3MSK_MXTD_EN_2_0X1                           (0x00000001U)

#define CSL_DCAN_IF3MSK_RESETVAL                                (0xe0000000U)

/* IF3ARB */

#define CSL_DCAN_IF3ARB_ID28_TO_ID0_MASK                        (0x1FFFFFFFU)
#define CSL_DCAN_IF3ARB_ID28_TO_ID0_SHIFT                       (0U)
#define CSL_DCAN_IF3ARB_ID28_TO_ID0_RESETVAL                    (0x00000000U)
#define CSL_DCAN_IF3ARB_ID28_TO_ID0_MAX                         (0x1fffffffU)

#define CSL_DCAN_IF3ARB_DIR_MASK                                (0x20000000U)
#define CSL_DCAN_IF3ARB_DIR_SHIFT                               (29U)
#define CSL_DCAN_IF3ARB_DIR_RESETVAL                            (0x00000000U)
#define CSL_DCAN_IF3ARB_DIR_EN_1_0X0                            (0x00000000U)
#define CSL_DCAN_IF3ARB_DIR_EN_2_0X1                            (0x00000001U)

#define CSL_DCAN_IF3ARB_XTD_MASK                                (0x40000000U)
#define CSL_DCAN_IF3ARB_XTD_SHIFT                               (30U)
#define CSL_DCAN_IF3ARB_XTD_RESETVAL                            (0x00000000U)
#define CSL_DCAN_IF3ARB_XTD_EN_1_0X0                            (0x00000000U)
#define CSL_DCAN_IF3ARB_XTD_EN_2_0X1                            (0x00000001U)

#define CSL_DCAN_IF3ARB_MSGVAL_MASK                             (0x80000000U)
#define CSL_DCAN_IF3ARB_MSGVAL_SHIFT                            (31U)
#define CSL_DCAN_IF3ARB_MSGVAL_RESETVAL                         (0x00000000U)
#define CSL_DCAN_IF3ARB_MSGVAL_EN_1_0X0                         (0x00000000U)
#define CSL_DCAN_IF3ARB_MSGVAL_EN_2_0X1                         (0x00000001U)

#define CSL_DCAN_IF3ARB_RESETVAL                                (0x00000000U)

/* IF3MCTL */

#define CSL_DCAN_IF3MCTL_DLC_MASK                               (0x0000000FU)
#define CSL_DCAN_IF3MCTL_DLC_SHIFT                              (0U)
#define CSL_DCAN_IF3MCTL_DLC_RESETVAL                           (0x00000000U)
#define CSL_DCAN_IF3MCTL_DLC_MAX                                (0x0000000fU)

#define CSL_DCAN_IF3MCTL_EOB_MASK                               (0x00000080U)
#define CSL_DCAN_IF3MCTL_EOB_SHIFT                              (7U)
#define CSL_DCAN_IF3MCTL_EOB_RESETVAL                           (0x00000000U)
#define CSL_DCAN_IF3MCTL_EOB_EN_1_0X0                           (0x00000000U)
#define CSL_DCAN_IF3MCTL_EOB_EN_2_0X1                           (0x00000001U)

#define CSL_DCAN_IF3MCTL_TXRQST_MASK                            (0x00000100U)
#define CSL_DCAN_IF3MCTL_TXRQST_SHIFT                           (8U)
#define CSL_DCAN_IF3MCTL_TXRQST_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF3MCTL_TXRQST_EN_1_0X0                        (0x00000000U)
#define CSL_DCAN_IF3MCTL_TXRQST_EN_2_0X1                        (0x00000001U)

#define CSL_DCAN_IF3MCTL_RMTEN_MASK                             (0x00000200U)
#define CSL_DCAN_IF3MCTL_RMTEN_SHIFT                            (9U)
#define CSL_DCAN_IF3MCTL_RMTEN_RESETVAL                         (0x00000000U)
#define CSL_DCAN_IF3MCTL_RMTEN_EN_1_0X0                         (0x00000000U)
#define CSL_DCAN_IF3MCTL_RMTEN_EN_2_0X1                         (0x00000001U)

#define CSL_DCAN_IF3MCTL_RXIE_MASK                              (0x00000400U)
#define CSL_DCAN_IF3MCTL_RXIE_SHIFT                             (10U)
#define CSL_DCAN_IF3MCTL_RXIE_RESETVAL                          (0x00000000U)
#define CSL_DCAN_IF3MCTL_RXIE_EN_1_0X0                          (0x00000000U)
#define CSL_DCAN_IF3MCTL_RXIE_EN_2_0X1                          (0x00000001U)

#define CSL_DCAN_IF3MCTL_TXIE_MASK                              (0x00000800U)
#define CSL_DCAN_IF3MCTL_TXIE_SHIFT                             (11U)
#define CSL_DCAN_IF3MCTL_TXIE_RESETVAL                          (0x00000000U)
#define CSL_DCAN_IF3MCTL_TXIE_EN_1_0X0                          (0x00000000U)
#define CSL_DCAN_IF3MCTL_TXIE_EN_2_0X1                          (0x00000001U)

#define CSL_DCAN_IF3MCTL_UMASK_MASK                             (0x00001000U)
#define CSL_DCAN_IF3MCTL_UMASK_SHIFT                            (12U)
#define CSL_DCAN_IF3MCTL_UMASK_RESETVAL                         (0x00000000U)
#define CSL_DCAN_IF3MCTL_UMASK_EN_1_0X0                         (0x00000000U)
#define CSL_DCAN_IF3MCTL_UMASK_EN_2_0X1                         (0x00000001U)

#define CSL_DCAN_IF3MCTL_INTPND_MASK                            (0x00002000U)
#define CSL_DCAN_IF3MCTL_INTPND_SHIFT                           (13U)
#define CSL_DCAN_IF3MCTL_INTPND_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF3MCTL_INTPND_EN_1_0X0                        (0x00000000U)
#define CSL_DCAN_IF3MCTL_INTPND_EN_2_0X1                        (0x00000001U)

#define CSL_DCAN_IF3MCTL_MSGLST_MASK                            (0x00004000U)
#define CSL_DCAN_IF3MCTL_MSGLST_SHIFT                           (14U)
#define CSL_DCAN_IF3MCTL_MSGLST_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF3MCTL_MSGLST_EN_1_0X0                        (0x00000000U)
#define CSL_DCAN_IF3MCTL_MSGLST_EN_2_0X1                        (0x00000001U)

#define CSL_DCAN_IF3MCTL_NEWDAT_MASK                            (0x00008000U)
#define CSL_DCAN_IF3MCTL_NEWDAT_SHIFT                           (15U)
#define CSL_DCAN_IF3MCTL_NEWDAT_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF3MCTL_NEWDAT_EN_1_0X0                        (0x00000000U)
#define CSL_DCAN_IF3MCTL_NEWDAT_EN_2_0X1                        (0x00000001U)

#define CSL_DCAN_IF3MCTL_RESETVAL                               (0x00000000U)

/* IF3DATA */

#define CSL_DCAN_IF3DATA_DATA_0_MASK                            (0x000000FFU)
#define CSL_DCAN_IF3DATA_DATA_0_SHIFT                           (0U)
#define CSL_DCAN_IF3DATA_DATA_0_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF3DATA_DATA_0_MAX                             (0x000000ffU)

#define CSL_DCAN_IF3DATA_DATA_1_MASK                            (0x0000FF00U)
#define CSL_DCAN_IF3DATA_DATA_1_SHIFT                           (8U)
#define CSL_DCAN_IF3DATA_DATA_1_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF3DATA_DATA_1_MAX                             (0x000000ffU)

#define CSL_DCAN_IF3DATA_DATA_2_MASK                            (0x00FF0000U)
#define CSL_DCAN_IF3DATA_DATA_2_SHIFT                           (16U)
#define CSL_DCAN_IF3DATA_DATA_2_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF3DATA_DATA_2_MAX                             (0x000000ffU)

#define CSL_DCAN_IF3DATA_DATA_3_MASK                            (0xFF000000U)
#define CSL_DCAN_IF3DATA_DATA_3_SHIFT                           (24U)
#define CSL_DCAN_IF3DATA_DATA_3_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF3DATA_DATA_3_MAX                             (0x000000ffU)

#define CSL_DCAN_IF3DATA_RESETVAL                               (0x00000000U)

/* IF3DATB */

#define CSL_DCAN_IF3DATB_DATA_4_MASK                            (0x000000FFU)
#define CSL_DCAN_IF3DATB_DATA_4_SHIFT                           (0U)
#define CSL_DCAN_IF3DATB_DATA_4_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF3DATB_DATA_4_MAX                             (0x000000ffU)

#define CSL_DCAN_IF3DATB_DATA_5_MASK                            (0x0000FF00U)
#define CSL_DCAN_IF3DATB_DATA_5_SHIFT                           (8U)
#define CSL_DCAN_IF3DATB_DATA_5_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF3DATB_DATA_5_MAX                             (0x000000ffU)

#define CSL_DCAN_IF3DATB_DATA_6_MASK                            (0x00FF0000U)
#define CSL_DCAN_IF3DATB_DATA_6_SHIFT                           (16U)
#define CSL_DCAN_IF3DATB_DATA_6_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF3DATB_DATA_6_MAX                             (0x000000ffU)

#define CSL_DCAN_IF3DATB_DATA_7_MASK                            (0xFF000000U)
#define CSL_DCAN_IF3DATB_DATA_7_SHIFT                           (24U)
#define CSL_DCAN_IF3DATB_DATA_7_RESETVAL                        (0x00000000U)
#define CSL_DCAN_IF3DATB_DATA_7_MAX                             (0x000000ffU)

#define CSL_DCAN_IF3DATB_RESETVAL                               (0x00000000U)

/* IF3UPD12 */

#define CSL_DCAN_IF3UPD12_IF3UPDEN_0_MASK                       (0x0000FFFFU)
#define CSL_DCAN_IF3UPD12_IF3UPDEN_0_SHIFT                      (0U)
#define CSL_DCAN_IF3UPD12_IF3UPDEN_0_RESETVAL                   (0x00000000U)
#define CSL_DCAN_IF3UPD12_IF3UPDEN_0_MAX                        (0x0000ffffU)

#define CSL_DCAN_IF3UPD12_IF3UPDEN_1_MASK                       (0xFFFF0000U)
#define CSL_DCAN_IF3UPD12_IF3UPDEN_1_SHIFT                      (16U)
#define CSL_DCAN_IF3UPD12_IF3UPDEN_1_RESETVAL                   (0x00000000U)
#define CSL_DCAN_IF3UPD12_IF3UPDEN_1_MAX                        (0x0000ffffU)

#define CSL_DCAN_IF3UPD12_RESETVAL                              (0x00000000U)

/* IF3UPD34 */

#define CSL_DCAN_IF3UPD34_IF3UPDEN_0_MASK                       (0x0000FFFFU)
#define CSL_DCAN_IF3UPD34_IF3UPDEN_0_SHIFT                      (0U)
#define CSL_DCAN_IF3UPD34_IF3UPDEN_0_RESETVAL                   (0x00000000U)
#define CSL_DCAN_IF3UPD34_IF3UPDEN_0_MAX                        (0x0000ffffU)

#define CSL_DCAN_IF3UPD34_IF3UPDEN_1_MASK                       (0xFFFF0000U)
#define CSL_DCAN_IF3UPD34_IF3UPDEN_1_SHIFT                      (16U)
#define CSL_DCAN_IF3UPD34_IF3UPDEN_1_RESETVAL                   (0x00000000U)
#define CSL_DCAN_IF3UPD34_IF3UPDEN_1_MAX                        (0x0000ffffU)

#define CSL_DCAN_IF3UPD34_RESETVAL                              (0x00000000U)

/* IF3UPD56 */

#define CSL_DCAN_IF3UPD56_IF3UPDEN_0_MASK                       (0x0000FFFFU)
#define CSL_DCAN_IF3UPD56_IF3UPDEN_0_SHIFT                      (0U)
#define CSL_DCAN_IF3UPD56_IF3UPDEN_0_RESETVAL                   (0x00000000U)
#define CSL_DCAN_IF3UPD56_IF3UPDEN_0_MAX                        (0x0000ffffU)

#define CSL_DCAN_IF3UPD56_IF3UPDEN_1_MASK                       (0xFFFF0000U)
#define CSL_DCAN_IF3UPD56_IF3UPDEN_1_SHIFT                      (16U)
#define CSL_DCAN_IF3UPD56_IF3UPDEN_1_RESETVAL                   (0x00000000U)
#define CSL_DCAN_IF3UPD56_IF3UPDEN_1_MAX                        (0x0000ffffU)

#define CSL_DCAN_IF3UPD56_RESETVAL                              (0x00000000U)

/* IF3UPD78 */

#define CSL_DCAN_IF3UPD78_IF3UPDEN_0_MASK                       (0x0000FFFFU)
#define CSL_DCAN_IF3UPD78_IF3UPDEN_0_SHIFT                      (0U)
#define CSL_DCAN_IF3UPD78_IF3UPDEN_0_RESETVAL                   (0x00000000U)
#define CSL_DCAN_IF3UPD78_IF3UPDEN_0_MAX                        (0x0000ffffU)

#define CSL_DCAN_IF3UPD78_IF3UPDEN_1_MASK                       (0xFFFF0000U)
#define CSL_DCAN_IF3UPD78_IF3UPDEN_1_SHIFT                      (16U)
#define CSL_DCAN_IF3UPD78_IF3UPDEN_1_RESETVAL                   (0x00000000U)
#define CSL_DCAN_IF3UPD78_IF3UPDEN_1_MAX                        (0x0000ffffU)

#define CSL_DCAN_IF3UPD78_RESETVAL                              (0x00000000U)

/* TIOC */

#define CSL_DCAN_TIOC_IN_MASK                                   (0x00000001U)
#define CSL_DCAN_TIOC_IN_SHIFT                                  (0U)
#define CSL_DCAN_TIOC_IN_RESETVAL                               (0x00000000U)
#define CSL_DCAN_TIOC_IN_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_TIOC_IN_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_TIOC_OUT_MASK                                  (0x00000002U)
#define CSL_DCAN_TIOC_OUT_SHIFT                                 (1U)
#define CSL_DCAN_TIOC_OUT_RESETVAL                              (0x00000000U)
#define CSL_DCAN_TIOC_OUT_EN_1_0X0                              (0x00000000U)
#define CSL_DCAN_TIOC_OUT_EN_2_0X1                              (0x00000001U)

#define CSL_DCAN_TIOC_DIR_MASK                                  (0x00000004U)
#define CSL_DCAN_TIOC_DIR_SHIFT                                 (2U)
#define CSL_DCAN_TIOC_DIR_RESETVAL                              (0x00000000U)
#define CSL_DCAN_TIOC_DIR_EN_1_0X0                              (0x00000000U)
#define CSL_DCAN_TIOC_DIR_EN_2_0X1                              (0x00000001U)

#define CSL_DCAN_TIOC_FUNC_MASK                                 (0x00000008U)
#define CSL_DCAN_TIOC_FUNC_SHIFT                                (3U)
#define CSL_DCAN_TIOC_FUNC_RESETVAL                             (0x00000000U)
#define CSL_DCAN_TIOC_FUNC_EN_1_0X0                             (0x00000000U)
#define CSL_DCAN_TIOC_FUNC_EN_2_0X1                             (0x00000001U)

#define CSL_DCAN_TIOC_OD_MASK                                   (0x00010000U)
#define CSL_DCAN_TIOC_OD_SHIFT                                  (16U)
#define CSL_DCAN_TIOC_OD_RESETVAL                               (0x00000000U)
#define CSL_DCAN_TIOC_OD_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_TIOC_OD_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_TIOC_PD_MASK                                   (0x00020000U)
#define CSL_DCAN_TIOC_PD_SHIFT                                  (17U)
#define CSL_DCAN_TIOC_PD_RESETVAL                               (0x00000000U)
#define CSL_DCAN_TIOC_PD_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_TIOC_PD_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_TIOC_PU_MASK                                   (0x00040000U)
#define CSL_DCAN_TIOC_PU_SHIFT                                  (18U)
#define CSL_DCAN_TIOC_PU_RESETVAL                               (0x00000000U)
#define CSL_DCAN_TIOC_PU_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_TIOC_PU_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_TIOC_RESETVAL                                  (0x00000000U)

/* RIOC */

#define CSL_DCAN_RIOC_IN_MASK                                   (0x00000001U)
#define CSL_DCAN_RIOC_IN_SHIFT                                  (0U)
#define CSL_DCAN_RIOC_IN_RESETVAL                               (0x00000000U)
#define CSL_DCAN_RIOC_IN_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_RIOC_IN_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_RIOC_OUT_MASK                                  (0x00000002U)
#define CSL_DCAN_RIOC_OUT_SHIFT                                 (1U)
#define CSL_DCAN_RIOC_OUT_RESETVAL                              (0x00000000U)
#define CSL_DCAN_RIOC_OUT_EN_1_0X0                              (0x00000000U)
#define CSL_DCAN_RIOC_OUT_EN_2_0X1                              (0x00000001U)

#define CSL_DCAN_RIOC_DIR_MASK                                  (0x00000004U)
#define CSL_DCAN_RIOC_DIR_SHIFT                                 (2U)
#define CSL_DCAN_RIOC_DIR_RESETVAL                              (0x00000000U)
#define CSL_DCAN_RIOC_DIR_EN_1_0X0                              (0x00000000U)
#define CSL_DCAN_RIOC_DIR_EN_2_0X1                              (0x00000001U)

#define CSL_DCAN_RIOC_FUNC_MASK                                 (0x00000008U)
#define CSL_DCAN_RIOC_FUNC_SHIFT                                (3U)
#define CSL_DCAN_RIOC_FUNC_RESETVAL                             (0x00000000U)
#define CSL_DCAN_RIOC_FUNC_EN_1_0X0                             (0x00000000U)
#define CSL_DCAN_RIOC_FUNC_EN_2_0X1                             (0x00000001U)

#define CSL_DCAN_RIOC_OD_MASK                                   (0x00010000U)
#define CSL_DCAN_RIOC_OD_SHIFT                                  (16U)
#define CSL_DCAN_RIOC_OD_RESETVAL                               (0x00000000U)
#define CSL_DCAN_RIOC_OD_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_RIOC_OD_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_RIOC_PD_MASK                                   (0x00020000U)
#define CSL_DCAN_RIOC_PD_SHIFT                                  (17U)
#define CSL_DCAN_RIOC_PD_RESETVAL                               (0x00000000U)
#define CSL_DCAN_RIOC_PD_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_RIOC_PD_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_RIOC_PU_MASK                                   (0x00040000U)
#define CSL_DCAN_RIOC_PU_SHIFT                                  (18U)
#define CSL_DCAN_RIOC_PU_RESETVAL                               (0x00000000U)
#define CSL_DCAN_RIOC_PU_EN_1_0X0                               (0x00000000U)
#define CSL_DCAN_RIOC_PU_EN_2_0X1                               (0x00000001U)

#define CSL_DCAN_RIOC_RESETVAL                                  (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
