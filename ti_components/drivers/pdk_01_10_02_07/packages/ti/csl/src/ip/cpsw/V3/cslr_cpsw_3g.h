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
#ifndef CSLR_CPSW_3G_H_
#define CSLR_CPSW_3G_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>


/**************************************************************************
* Register Overlay Structure for port_info
**************************************************************************/
typedef struct {
    volatile Uint32 P_CONTROL;
    volatile Uint32 P_CONTROL2;
    volatile Uint32 P_MAX_BLKS;
    volatile Uint32 P_BLK_CNT;
    volatile Uint32 P_TX_IN_CTL;
    volatile Uint32 P_PORT_VLAN;
    volatile Uint32 P_TX_PRI_MAP;
    volatile Uint32 P_TS_SEQ_MTYPE;
    volatile Uint32 P_SA_LO;
    volatile Uint32 P_SA_HI;
    volatile Uint32 P_SEND_PERCENT;
    volatile Uint8  RSVD0[4];
    volatile Uint32 P_RX_DSCP_PRI_MAP[8];
    volatile Uint32 P_IDLE2LPI;
    volatile Uint32 P_LPI2WAKE;
    volatile Uint8  RSVD1[168];
} CSL_Cpsw_3gPort_infoRegs;


/**************************************************************************
* Register Overlay Structure for ale
**************************************************************************/
typedef struct {
    volatile Uint32 ID;
    volatile Uint8  RSVD0[4];
    volatile Uint32 CONTROL;
    volatile Uint8  RSVD1[4];
    volatile Uint32 PRESCALE;
    volatile Uint8  RSVD2[4];
    volatile Uint32 UNKNOWN_VLAN;
    volatile Uint8  RSVD3[4];
    volatile Uint32 TABLE_CONTROL;
    volatile Uint8  RSVD4[16];
    volatile Uint32 TABLE_WORD2;
    volatile Uint32 TABLE_WORD1;
    volatile Uint32 TABLE_WORD0;
    volatile Uint32 PORT_CONTROL[6];
} CSL_Cpsw_3gAleRegs;


/**************************************************************************
* Register Overlay Structure for stats
**************************************************************************/
typedef struct {
    volatile Uint32 RXGOODFRAMES;
    volatile Uint32 RXBROADCASTFRAMES;
    volatile Uint32 RXMULTICASTFRAMES;
    volatile Uint32 RXPAUSEFRAMES;
    volatile Uint32 RXCRCERRORS;
    volatile Uint32 RXALIGNCODEERRORS;
    volatile Uint32 RXOVERSIZEDFRAMES;
    volatile Uint32 RXJABBERFRAMES;
    volatile Uint32 RXUNDERSIZEDFRAMES;
    volatile Uint32 RXFRAGMENTS;
    volatile Uint8  RSVD0[8];
    volatile Uint32 RXOCTETS;
    volatile Uint32 TXGOODFRAMES;
    volatile Uint32 TXBROADCASTFRAMES;
    volatile Uint32 TXMULTICASTFRAMES;
    volatile Uint32 TXPAUSEFRAMES;
    volatile Uint32 TXDEFERREDFRAMES;
    volatile Uint32 TXCOLLISIONFRAMES;
    volatile Uint32 TXSINGLECOLLFRAMES;
    volatile Uint32 TXMULTCOLLFRAMES;
    volatile Uint32 TXEXCESSIVECOLLISIONS;
    volatile Uint32 TXLATECOLLISIONS;
    volatile Uint32 TXUNDERRUN;
    volatile Uint32 TXCARRIERSENSEERRORS;
    volatile Uint32 TXOCTETS;
    volatile Uint32 OCTETFRAMES64;
    volatile Uint32 OCTETFRAMES65T127;
    volatile Uint32 OCTETFRAMES128T255;
    volatile Uint32 OCTETFRAMES256T511;
    volatile Uint32 OCTETFRAMES512T1023;
    volatile Uint32 OCTETFRAMES1024TUP;
    volatile Uint32 NETOCTETS;
    volatile Uint32 RXSOFOVERRUNS;
    volatile Uint32 RXMOFOVERRUNS;
    volatile Uint32 RXDMAOVERRUNS;
} CSL_Cpsw_3gStatsRegs;


/**************************************************************************
* Register Overlay Structure
**************************************************************************/
typedef struct {
    volatile Uint32 ID_VER;
    volatile Uint32 SW_CONTROL;
    volatile Uint32 SOFT_RESET;
    volatile Uint32 STAT_PORT_EN;
    volatile Uint32 PTYPE;
    volatile Uint32 SOFT_IDLE;
    volatile Uint32 THRU_RATE;
    volatile Uint32 GAP_THRESH;
    volatile Uint32 TX_START_WDS;
    volatile Uint32 FLOW_CONTROL;
    volatile Uint32 VLAN_LTYPE;
    volatile Uint32 TS_LTYPE;
    volatile Uint32 DLR_LTYPE;
    volatile Uint32 EEE_PRESCALE;
    volatile Uint32 STATUS;
    volatile Uint8  RSVD0[196];
    volatile Uint32 P0_CONTROL;
    volatile Uint8  RSVD1[4];
    volatile Uint32 P0_MAX_BLKS;
    volatile Uint32 P0_BLK_CNT;
    volatile Uint32 P0_TX_IN_CTL;
    volatile Uint32 P0_PORT_VLAN;
    volatile Uint32 P0_TX_PRI_MAP;
    volatile Uint32 CDMA_TX_PRI_MAP;
    volatile Uint32 P0_CPDMA_RX_CH_MAP;
    volatile Uint8  RSVD2[12];
    volatile Uint32 P0_RX_DSCP_PRI_MAP[8];
    volatile Uint32 P0_IDLE2LPI;
    volatile Uint32 P0_LPI2WAKE;
    volatile Uint8  RSVD3[168];
    CSL_Cpsw_3gPort_infoRegs	PORT_INFO[2];
    volatile Uint8  RSVD4[1280];
    CSL_Cpsw_3gStatsRegs	STATS;
    volatile Uint8  RSVD5[880];
    CSL_Cpsw_3gAleRegs	ALE;
} CSL_Cpsw_3gRegs;




/**************************************************************************
* Register Macros
**************************************************************************/

/* P_CONTROL */
#define CSL_CPSW_3G_P_CONTROL(n)                                ((uint32_t)0x200U + ((n) * ((uint32_t)(0x100U))))

/* P_CONTROL2 */
#define CSL_CPSW_3G_P_CONTROL2(n)                               ((uint32_t)0x204U + ((n) * ((uint32_t)(0x100U))))

/* P_MAX_BLKS */
#define CSL_CPSW_3G_P_MAX_BLKS(n)                               ((uint32_t)0x208U + ((n) * ((uint32_t)(0x100U))))

/* P_BLK_CNT */
#define CSL_CPSW_3G_P_BLK_CNT(n)                                ((uint32_t)0x20CU + ((n) * ((uint32_t)(0x100U))))

/* P_TX_IN_CTL */
#define CSL_CPSW_3G_P_TX_IN_CTL(n)                              ((uint32_t)0x210U + ((n) * ((uint32_t)(0x100U))))

/* P_PORT_VLAN */
#define CSL_CPSW_3G_P_PORT_VLAN(n)                              ((uint32_t)0x214U + ((n) * ((uint32_t)(0x100U))))

/* P_TX_PRI_MAP */
#define CSL_CPSW_3G_P_TX_PRI_MAP(n)                             ((uint32_t)0x218U + ((n) * ((uint32_t)(0x100U))))

/* P_TS_SEQ_MTYPE */
#define CSL_CPSW_3G_P_TS_SEQ_MTYPE(n)                           ((uint32_t)0x21CU + ((n) * ((uint32_t)(0x100U))))

/* P_SA_LO */
#define CSL_CPSW_3G_P_SA_LO(n)                                  ((uint32_t)0x220U + ((n) * ((uint32_t)(0x100U))))

/* P_SA_HI */
#define CSL_CPSW_3G_P_SA_HI(n)                                  ((uint32_t)0x224U + ((n) * ((uint32_t)(0x100U))))

/* P_SEND_PERCENT */
#define CSL_CPSW_3G_P_SEND_PERCENT(n)                           ((uint32_t)0x228U + ((n) * ((uint32_t)(0x100U))))

/* P_RX_DSCP_PRI_MAP */
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP(n,i)                      ((uint32_t)0x230U + ((n) * ((uint32_t)(0x100U))) + ((i) * ((uint32_t)(0x4U)))

/* P_IDLE2LPI */
#define CSL_CPSW_3G_P_IDLE2LPI(n)                               ((uint32_t)0x250U + ((n) * ((uint32_t)(0x100U))))

/* P_LPI2WAKE */
#define CSL_CPSW_3G_P_LPI2WAKE(n)                               ((uint32_t)0x254U + ((n) * ((uint32_t)(0x100U))))

/* ID */
#define CSL_CPSW_3G_ID                                          ((uint32_t)(0xD00U))

/* CONTROL */
#define CSL_CPSW_3G_CONTROL                                     ((uint32_t)(0xD08U))

/* PRESCALE */
#define CSL_CPSW_3G_PRESCALE                                    ((uint32_t)(0xD10U))

/* UNKNOWN_VLAN */
#define CSL_CPSW_3G_UNKNOWN_VLAN                                ((uint32_t)(0xD18U))

/* TABLE_CONTROL */
#define CSL_CPSW_3G_TABLE_CONTROL                               ((uint32_t)(0xD20U))

/* TABLE_WORD2 */
#define CSL_CPSW_3G_TABLE_WORD2                                 ((uint32_t)(0xD34U))

/* TABLE_WORD1 */
#define CSL_CPSW_3G_TABLE_WORD1                                 ((uint32_t)(0xD38U))

/* TABLE_WORD0 */
#define CSL_CPSW_3G_TABLE_WORD0                                 ((uint32_t)(0xD3CU))

/* PORT_CONTROL */
#define CSL_CPSW_3G_PORT_CONTROL(i)                             ((uint32_t)0xD40U + ((i) * ((uint32_t)(0x4U))))

/* RXGOODFRAMES */
#define CSL_CPSW_3G_RXGOODFRAMES                                ((uint32_t)(0x900U))

/* RXBROADCASTFRAMES */
#define CSL_CPSW_3G_RXBROADCASTFRAMES                           ((uint32_t)(0x904U))

/* RXMULTICASTFRAMES */
#define CSL_CPSW_3G_RXMULTICASTFRAMES                           ((uint32_t)(0x908U))

/* RXPAUSEFRAMES */
#define CSL_CPSW_3G_RXPAUSEFRAMES                               ((uint32_t)(0x90CU))

/* RXCRCERRORS */
#define CSL_CPSW_3G_RXCRCERRORS                                 ((uint32_t)(0x910U))

/* RXALIGNCODEERRORS */
#define CSL_CPSW_3G_RXALIGNCODEERRORS                           ((uint32_t)(0x914U))

/* RXOVERSIZEDFRAMES */
#define CSL_CPSW_3G_RXOVERSIZEDFRAMES                           ((uint32_t)(0x918U))

/* RXJABBERFRAMES */
#define CSL_CPSW_3G_RXJABBERFRAMES                              ((uint32_t)(0x91CU))

/* RXUNDERSIZEDFRAMES */
#define CSL_CPSW_3G_RXUNDERSIZEDFRAMES                          ((uint32_t)(0x920U))

/* RXFRAGMENTS */
#define CSL_CPSW_3G_RXFRAGMENTS                                 ((uint32_t)(0x924U))

/* RXOCTETS */
#define CSL_CPSW_3G_RXOCTETS                                    ((uint32_t)(0x930U))

/* TXGOODFRAMES */
#define CSL_CPSW_3G_TXGOODFRAMES                                ((uint32_t)(0x934U))

/* TXBROADCASTFRAMES */
#define CSL_CPSW_3G_TXBROADCASTFRAMES                           ((uint32_t)(0x938U))

/* TXMULTICASTFRAMES */
#define CSL_CPSW_3G_TXMULTICASTFRAMES                           ((uint32_t)(0x93CU))

/* TXPAUSEFRAMES */
#define CSL_CPSW_3G_TXPAUSEFRAMES                               ((uint32_t)(0x940U))

/* TXDEFERREDFRAMES */
#define CSL_CPSW_3G_TXDEFERREDFRAMES                            ((uint32_t)(0x944U))

/* TXCOLLISIONFRAMES */
#define CSL_CPSW_3G_TXCOLLISIONFRAMES                           ((uint32_t)(0x948U))

/* TXSINGLECOLLFRAMES */
#define CSL_CPSW_3G_TXSINGLECOLLFRAMES                          ((uint32_t)(0x94CU))

/* TXMULTCOLLFRAMES */
#define CSL_CPSW_3G_TXMULTCOLLFRAMES                            ((uint32_t)(0x950U))

/* TXEXCESSIVECOLLISIONS */
#define CSL_CPSW_3G_TXEXCESSIVECOLLISIONS                       ((uint32_t)(0x954U))

/* TXLATECOLLISIONS */
#define CSL_CPSW_3G_TXLATECOLLISIONS                            ((uint32_t)(0x958U))

/* TXUNDERRUN */
#define CSL_CPSW_3G_TXUNDERRUN                                  ((uint32_t)(0x95CU))

/* TXCARRIERSENSEERRORS */
#define CSL_CPSW_3G_TXCARRIERSENSEERRORS                        ((uint32_t)(0x960U))

/* TXOCTETS */
#define CSL_CPSW_3G_TXOCTETS                                    ((uint32_t)(0x964U))

/* OCTETFRAMES64 */
#define CSL_CPSW_3G_OCTETFRAMES64                               ((uint32_t)(0x968U))

/* OCTETFRAMES65T127 */
#define CSL_CPSW_3G_OCTETFRAMES65T127                           ((uint32_t)(0x96CU))

/* OCTETFRAMES128T255 */
#define CSL_CPSW_3G_OCTETFRAMES128T255                          ((uint32_t)(0x970U))

/* OCTETFRAMES256T511 */
#define CSL_CPSW_3G_OCTETFRAMES256T511                          ((uint32_t)(0x974U))

/* OCTETFRAMES512T1023 */
#define CSL_CPSW_3G_OCTETFRAMES512T1023                         ((uint32_t)(0x978U))

/* OCTETFRAMES1024TUP */
#define CSL_CPSW_3G_OCTETFRAMES1024TUP                          ((uint32_t)(0x97CU))

/* NETOCTETS */
#define CSL_CPSW_3G_NETOCTETS                                   ((uint32_t)(0x980U))

/* RXSOFOVERRUNS */
#define CSL_CPSW_3G_RXSOFOVERRUNS                               ((uint32_t)(0x984U))

/* RXMOFOVERRUNS */
#define CSL_CPSW_3G_RXMOFOVERRUNS                               ((uint32_t)(0x988U))

/* RXDMAOVERRUNS */
#define CSL_CPSW_3G_RXDMAOVERRUNS                               ((uint32_t)(0x98CU))

/* ID_VER */
#define CSL_CPSW_3G_ID_VER                                      ((uint32_t)(0x0U))

/* SW_CONTROL */
#define CSL_CPSW_3G_SW_CONTROL                                  ((uint32_t)(0x4U))

/* SOFT_RESET */
#define CSL_CPSW_3G_SOFT_RESET                                  ((uint32_t)(0x8U))

/* STAT_PORT_EN */
#define CSL_CPSW_3G_STAT_PORT_EN                                ((uint32_t)(0xCU))

/* PTYPE */
#define CSL_CPSW_3G_PTYPE                                       ((uint32_t)(0x10U))

/* SOFT_IDLE */
#define CSL_CPSW_3G_SOFT_IDLE                                   ((uint32_t)(0x14U))

/* THRU_RATE */
#define CSL_CPSW_3G_THRU_RATE                                   ((uint32_t)(0x18U))

/* GAP_THRESH */
#define CSL_CPSW_3G_GAP_THRESH                                  ((uint32_t)(0x1CU))

/* TX_START_WDS */
#define CSL_CPSW_3G_TX_START_WDS                                ((uint32_t)(0x20U))

/* FLOW_CONTROL */
#define CSL_CPSW_3G_FLOW_CONTROL                                ((uint32_t)(0x24U))

/* VLAN_LTYPE */
#define CSL_CPSW_3G_VLAN_LTYPE                                  ((uint32_t)(0x28U))

/* TS_LTYPE */
#define CSL_CPSW_3G_TS_LTYPE                                    ((uint32_t)(0x2CU))

/* DLR_LTYPE */
#define CSL_CPSW_3G_DLR_LTYPE                                   ((uint32_t)(0x30U))

/* EEE_PRESCALE */
#define CSL_CPSW_3G_EEE_PRESCALE                                ((uint32_t)(0x34U))

/* STATUS */
#define CSL_CPSW_3G_STATUS                                      ((uint32_t)(0x38U))

/* P0_CONTROL */
#define CSL_CPSW_3G_P0_CONTROL                                  ((uint32_t)(0x100U))

/* P0_MAX_BLKS */
#define CSL_CPSW_3G_P0_MAX_BLKS                                 ((uint32_t)(0x108U))

/* P0_BLK_CNT */
#define CSL_CPSW_3G_P0_BLK_CNT                                  ((uint32_t)(0x10CU))

/* P0_TX_IN_CTL */
#define CSL_CPSW_3G_P0_TX_IN_CTL                                ((uint32_t)(0x110U))

/* P0_PORT_VLAN */
#define CSL_CPSW_3G_P0_PORT_VLAN                                ((uint32_t)(0x114U))

/* P0_TX_PRI_MAP */
#define CSL_CPSW_3G_P0_TX_PRI_MAP                               ((uint32_t)(0x118U))

/* CDMA_TX_PRI_MAP */
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP                             ((uint32_t)(0x11CU))

/* P0_CPDMA_RX_CH_MAP */
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP                          ((uint32_t)(0x120U))

/* P0_RX_DSCP_PRI_MAP */
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP(i)                       ((uint32_t)0x130U + ((i) * ((uint32_t)(0x4U))))

/* P0_IDLE2LPI */
#define CSL_CPSW_3G_P0_IDLE2LPI                                 ((uint32_t)(0x150U))

/* P0_LPI2WAKE */
#define CSL_CPSW_3G_P0_LPI2WAKE                                 ((uint32_t)(0x154U))


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* P_CONTROL */

#define CSL_CPSW_3G_P_CONTROL_P_TS_RX_EN_MASK                   ((uint32_t)(0x00000001U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_RX_EN_SHIFT                  ((uint32_t)(0U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_RX_EN_RESETVAL               ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_RX_EN_MAX                    ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_P_TS_TX_EN_MASK                   ((uint32_t)(0x00000002U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_TX_EN_SHIFT                  ((uint32_t)(1U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_TX_EN_RESETVAL               ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_TX_EN_MAX                    ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_P_TS_LTYPE1_EN_MASK               ((uint32_t)(0x00000004U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_LTYPE1_EN_SHIFT              ((uint32_t)(2U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_LTYPE1_EN_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_LTYPE1_EN_MAX                ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_P_TS_LTYPE2_EN_MASK               ((uint32_t)(0x00000008U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_LTYPE2_EN_SHIFT              ((uint32_t)(3U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_LTYPE2_EN_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_LTYPE2_EN_MAX                ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_P_TS_ANNEX_D_EN_MASK              ((uint32_t)(0x00000010U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_ANNEX_D_EN_SHIFT             ((uint32_t)(4U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_ANNEX_D_EN_RESETVAL          ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_ANNEX_D_EN_MAX               ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_P_TS_ANNEX_E_EN_MASK              ((uint32_t)(0x00000020U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_ANNEX_E_EN_SHIFT             ((uint32_t)(5U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_ANNEX_E_EN_RESETVAL          ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_ANNEX_E_EN_MAX               ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_P_TS_ANNEX_F_EN_MASK              ((uint32_t)(0x00000040U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_ANNEX_F_EN_SHIFT             ((uint32_t)(6U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_ANNEX_F_EN_RESETVAL          ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_ANNEX_F_EN_MAX               ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_P_TS_UNI_EN_MASK                  ((uint32_t)(0x00000080U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_UNI_EN_SHIFT                 ((uint32_t)(7U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_UNI_EN_RESETVAL              ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_UNI_EN_MAX                   ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_P_TS_TTL_NONZERO_MASK             ((uint32_t)(0x00000100U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_TTL_NONZERO_SHIFT            ((uint32_t)(8U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_TTL_NONZERO_RESETVAL         ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_TTL_NONZERO_MAX              ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_P_TS_129_MASK                     ((uint32_t)(0x00000200U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_129_SHIFT                    ((uint32_t)(9U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_129_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_129_MAX                      ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_P_TS_130_MASK                     ((uint32_t)(0x00000400U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_130_SHIFT                    ((uint32_t)(10U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_130_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_130_MAX                      ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_P_TS_131_MASK                     ((uint32_t)(0x00000800U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_131_SHIFT                    ((uint32_t)(11U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_131_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_131_MAX                      ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_P_TS_132_MASK                     ((uint32_t)(0x00001000U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_132_SHIFT                    ((uint32_t)(12U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_132_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_132_MAX                      ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_P_TS_319_MASK                     ((uint32_t)(0x00002000U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_319_SHIFT                    ((uint32_t)(13U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_319_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_319_MAX                      ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_P_TS_320_MASK                     ((uint32_t)(0x00004000U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_320_SHIFT                    ((uint32_t)(14U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_320_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_320_MAX                      ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_P_TS_107_MASK                     ((uint32_t)(0x00008000U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_107_SHIFT                    ((uint32_t)(15U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_107_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_TS_107_MAX                      ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_P_DSCP_PRI_EN_MASK                ((uint32_t)(0x00010000U))
#define CSL_CPSW_3G_P_CONTROL_P_DSCP_PRI_EN_SHIFT               ((uint32_t)(16U))
#define CSL_CPSW_3G_P_CONTROL_P_DSCP_PRI_EN_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_DSCP_PRI_EN_MAX                 ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_P_VLAN_LTYPE1_EN_MASK             ((uint32_t)(0x00100000U))
#define CSL_CPSW_3G_P_CONTROL_P_VLAN_LTYPE1_EN_SHIFT            ((uint32_t)(20U))
#define CSL_CPSW_3G_P_CONTROL_P_VLAN_LTYPE1_EN_RESETVAL         ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_VLAN_LTYPE1_EN_MAX              ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_P_VLAN_LTYPE2_EN_MASK             ((uint32_t)(0x00200000U))
#define CSL_CPSW_3G_P_CONTROL_P_VLAN_LTYPE2_EN_SHIFT            ((uint32_t)(21U))
#define CSL_CPSW_3G_P_CONTROL_P_VLAN_LTYPE2_EN_RESETVAL         ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_VLAN_LTYPE2_EN_MAX              ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_P_PASS_PRI_TAGGED_MASK            ((uint32_t)(0x01000000U))
#define CSL_CPSW_3G_P_CONTROL_P_PASS_PRI_TAGGED_SHIFT           ((uint32_t)(24U))
#define CSL_CPSW_3G_P_CONTROL_P_PASS_PRI_TAGGED_RESETVAL        ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_PASS_PRI_TAGGED_MAX             ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_P_TX_CLKSTOP_EN_MASK              ((uint32_t)(0x02000000U))
#define CSL_CPSW_3G_P_CONTROL_P_TX_CLKSTOP_EN_SHIFT             ((uint32_t)(25U))
#define CSL_CPSW_3G_P_CONTROL_P_TX_CLKSTOP_EN_RESETVAL          ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL_P_TX_CLKSTOP_EN_MAX               ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_CONTROL_RESETVAL                          ((uint32_t)(0x00000000U))

/* P_CONTROL2 */

#define CSL_CPSW_3G_P_CONTROL2_P_TS_MCAST_TYPE_EN_MASK          ((uint32_t)(0x0000FFFFU))
#define CSL_CPSW_3G_P_CONTROL2_P_TS_MCAST_TYPE_EN_SHIFT         ((uint32_t)(0U))
#define CSL_CPSW_3G_P_CONTROL2_P_TS_MCAST_TYPE_EN_RESETVAL      ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL2_P_TS_MCAST_TYPE_EN_MAX           ((uint32_t)(0x0000ffffU))

#define CSL_CPSW_3G_P_CONTROL2_P_DOMAIN_OFFSET_MASK             ((uint32_t)(0x003F0000U))
#define CSL_CPSW_3G_P_CONTROL2_P_DOMAIN_OFFSET_SHIFT            ((uint32_t)(16U))
#define CSL_CPSW_3G_P_CONTROL2_P_DOMAIN_OFFSET_RESETVAL         ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_CONTROL2_P_DOMAIN_OFFSET_MAX              ((uint32_t)(0x0000003fU))

#define CSL_CPSW_3G_P_CONTROL2_RESETVAL                         ((uint32_t)(0x00000000U))

/* P_MAX_BLKS */

#define CSL_CPSW_3G_P_MAX_BLKS_P_RX_MAX_BLKS_MASK               ((uint32_t)(0x0000000FU))
#define CSL_CPSW_3G_P_MAX_BLKS_P_RX_MAX_BLKS_SHIFT              ((uint32_t)(0U))
#define CSL_CPSW_3G_P_MAX_BLKS_P_RX_MAX_BLKS_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_MAX_BLKS_P_RX_MAX_BLKS_MAX                ((uint32_t)(0x0000000fU))

#define CSL_CPSW_3G_P_MAX_BLKS_P_TX_MAX_BLKS_MASK               ((uint32_t)(0x000001F0U))
#define CSL_CPSW_3G_P_MAX_BLKS_P_TX_MAX_BLKS_SHIFT              ((uint32_t)(4U))
#define CSL_CPSW_3G_P_MAX_BLKS_P_TX_MAX_BLKS_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_MAX_BLKS_P_TX_MAX_BLKS_MAX                ((uint32_t)(0x0000001fU))

#define CSL_CPSW_3G_P_MAX_BLKS_RESETVAL                         ((uint32_t)(0x00000000U))

/* P_BLK_CNT */

#define CSL_CPSW_3G_P_BLK_CNT_P_RX_BLK_CNT_MASK                 ((uint32_t)(0x0000000FU))
#define CSL_CPSW_3G_P_BLK_CNT_P_RX_BLK_CNT_SHIFT                ((uint32_t)(0U))
#define CSL_CPSW_3G_P_BLK_CNT_P_RX_BLK_CNT_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_BLK_CNT_P_RX_BLK_CNT_MAX                  ((uint32_t)(0x0000000fU))

#define CSL_CPSW_3G_P_BLK_CNT_P_TX_BLK_CNT_MASK                 ((uint32_t)(0x000001F0U))
#define CSL_CPSW_3G_P_BLK_CNT_P_TX_BLK_CNT_SHIFT                ((uint32_t)(4U))
#define CSL_CPSW_3G_P_BLK_CNT_P_TX_BLK_CNT_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_BLK_CNT_P_TX_BLK_CNT_MAX                  ((uint32_t)(0x0000001fU))

#define CSL_CPSW_3G_P_BLK_CNT_RESETVAL                          ((uint32_t)(0x00000000U))

/* P_TX_IN_CTL */

#define CSL_CPSW_3G_P_TX_IN_CTL_TX_PRI_WDS_MASK                 ((uint32_t)(0x000003FFU))
#define CSL_CPSW_3G_P_TX_IN_CTL_TX_PRI_WDS_SHIFT                ((uint32_t)(0U))
#define CSL_CPSW_3G_P_TX_IN_CTL_TX_PRI_WDS_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_TX_IN_CTL_TX_PRI_WDS_MAX                  ((uint32_t)(0x000003ffU))

#define CSL_CPSW_3G_P_TX_IN_CTL_TX_BLKS_REM_MASK                ((uint32_t)(0x0000F000U))
#define CSL_CPSW_3G_P_TX_IN_CTL_TX_BLKS_REM_SHIFT               ((uint32_t)(12U))
#define CSL_CPSW_3G_P_TX_IN_CTL_TX_BLKS_REM_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_TX_IN_CTL_TX_BLKS_REM_MAX                 ((uint32_t)(0x0000000fU))

#define CSL_CPSW_3G_P_TX_IN_CTL_TX_IN_SEL_MASK                  ((uint32_t)(0x00030000U))
#define CSL_CPSW_3G_P_TX_IN_CTL_TX_IN_SEL_SHIFT                 ((uint32_t)(16U))
#define CSL_CPSW_3G_P_TX_IN_CTL_TX_IN_SEL_RESETVAL              ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_TX_IN_CTL_TX_IN_SEL_MAX                   ((uint32_t)(0x00000003U))

#define CSL_CPSW_3G_P_TX_IN_CTL_TX_RATE_EN_MASK                 ((uint32_t)(0x00F00000U))
#define CSL_CPSW_3G_P_TX_IN_CTL_TX_RATE_EN_SHIFT                ((uint32_t)(20U))
#define CSL_CPSW_3G_P_TX_IN_CTL_TX_RATE_EN_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_TX_IN_CTL_TX_RATE_EN_MAX                  ((uint32_t)(0x0000000fU))

#define CSL_CPSW_3G_P_TX_IN_CTL_HOST_BLKS_REM_MASK              ((uint32_t)(0x0F000000U))
#define CSL_CPSW_3G_P_TX_IN_CTL_HOST_BLKS_REM_SHIFT             ((uint32_t)(24U))
#define CSL_CPSW_3G_P_TX_IN_CTL_HOST_BLKS_REM_RESETVAL          ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_TX_IN_CTL_HOST_BLKS_REM_MAX               ((uint32_t)(0x0000000fU))

#define CSL_CPSW_3G_P_TX_IN_CTL_RESETVAL                        ((uint32_t)(0x00000000U))

/* P_PORT_VLAN */

#define CSL_CPSW_3G_P_PORT_VLAN_PORT_VID_MASK                   ((uint32_t)(0x00000FFFU))
#define CSL_CPSW_3G_P_PORT_VLAN_PORT_VID_SHIFT                  ((uint32_t)(0U))
#define CSL_CPSW_3G_P_PORT_VLAN_PORT_VID_RESETVAL               ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_PORT_VLAN_PORT_VID_MAX                    ((uint32_t)(0x00000fffU))

#define CSL_CPSW_3G_P_PORT_VLAN_PORT_CFI_MASK                   ((uint32_t)(0x00001000U))
#define CSL_CPSW_3G_P_PORT_VLAN_PORT_CFI_SHIFT                  ((uint32_t)(12U))
#define CSL_CPSW_3G_P_PORT_VLAN_PORT_CFI_RESETVAL               ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_PORT_VLAN_PORT_CFI_MAX                    ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P_PORT_VLAN_PORT_PRI_MASK                   ((uint32_t)(0x0000E000U))
#define CSL_CPSW_3G_P_PORT_VLAN_PORT_PRI_SHIFT                  ((uint32_t)(13U))
#define CSL_CPSW_3G_P_PORT_VLAN_PORT_PRI_RESETVAL               ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_PORT_VLAN_PORT_PRI_MAX                    ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P_PORT_VLAN_RESETVAL                        ((uint32_t)(0x00000000U))

/* P_TX_PRI_MAP */

#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI0_MASK                      ((uint32_t)(0x00000003U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI0_SHIFT                     ((uint32_t)(0U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI0_RESETVAL                  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI0_MAX                       ((uint32_t)(0x00000003U))

#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI1_MASK                      ((uint32_t)(0x00000030U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI1_SHIFT                     ((uint32_t)(4U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI1_RESETVAL                  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI1_MAX                       ((uint32_t)(0x00000003U))

#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI2_MASK                      ((uint32_t)(0x00000300U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI2_SHIFT                     ((uint32_t)(8U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI2_RESETVAL                  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI2_MAX                       ((uint32_t)(0x00000003U))

#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI3_MASK                      ((uint32_t)(0x00003000U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI3_SHIFT                     ((uint32_t)(12U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI3_RESETVAL                  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI3_MAX                       ((uint32_t)(0x00000003U))

#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI4_MASK                      ((uint32_t)(0x00030000U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI4_SHIFT                     ((uint32_t)(16U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI4_RESETVAL                  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI4_MAX                       ((uint32_t)(0x00000003U))

#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI5_MASK                      ((uint32_t)(0x00300000U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI5_SHIFT                     ((uint32_t)(20U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI5_RESETVAL                  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI5_MAX                       ((uint32_t)(0x00000003U))

#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI6_MASK                      ((uint32_t)(0x03000000U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI6_SHIFT                     ((uint32_t)(24U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI6_RESETVAL                  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI6_MAX                       ((uint32_t)(0x00000003U))

#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI7_MASK                      ((uint32_t)(0x30000000U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI7_SHIFT                     ((uint32_t)(28U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI7_RESETVAL                  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_TX_PRI_MAP_PRI7_MAX                       ((uint32_t)(0x00000003U))

#define CSL_CPSW_3G_P_TX_PRI_MAP_RESETVAL                       ((uint32_t)(0x00000000U))

/* P_TS_SEQ_MTYPE */

#define CSL_CPSW_3G_P_TS_SEQ_MTYPE_P_TS_MSG_TYPE_EN_MASK        ((uint32_t)(0x0000FFFFU))
#define CSL_CPSW_3G_P_TS_SEQ_MTYPE_P_TS_MSG_TYPE_EN_SHIFT       ((uint32_t)(0U))
#define CSL_CPSW_3G_P_TS_SEQ_MTYPE_P_TS_MSG_TYPE_EN_RESETVAL    ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_TS_SEQ_MTYPE_P_TS_MSG_TYPE_EN_MAX         ((uint32_t)(0x0000ffffU))

#define CSL_CPSW_3G_P_TS_SEQ_MTYPE_P1_TS_SEQ_ID_OFFSET_MASK     ((uint32_t)(0x003F0000U))
#define CSL_CPSW_3G_P_TS_SEQ_MTYPE_P1_TS_SEQ_ID_OFFSET_SHIFT    ((uint32_t)(16U))
#define CSL_CPSW_3G_P_TS_SEQ_MTYPE_P1_TS_SEQ_ID_OFFSET_RESETVAL  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_TS_SEQ_MTYPE_P1_TS_SEQ_ID_OFFSET_MAX      ((uint32_t)(0x0000003fU))

#define CSL_CPSW_3G_P_TS_SEQ_MTYPE_RESETVAL                     ((uint32_t)(0x00000000U))

/* P_SA_LO */

#define CSL_CPSW_3G_P_SA_LO_MACSRCADDR_15_8_MASK                ((uint32_t)(0x000000FFU))
#define CSL_CPSW_3G_P_SA_LO_MACSRCADDR_15_8_SHIFT               ((uint32_t)(0U))
#define CSL_CPSW_3G_P_SA_LO_MACSRCADDR_15_8_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_SA_LO_MACSRCADDR_15_8_MAX                 ((uint32_t)(0x000000ffU))

#define CSL_CPSW_3G_P_SA_LO_MACSRCADDR_7_0_MASK                 ((uint32_t)(0x0000FF00U))
#define CSL_CPSW_3G_P_SA_LO_MACSRCADDR_7_0_SHIFT                ((uint32_t)(8U))
#define CSL_CPSW_3G_P_SA_LO_MACSRCADDR_7_0_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_SA_LO_MACSRCADDR_7_0_MAX                  ((uint32_t)(0x000000ffU))

#define CSL_CPSW_3G_P_SA_LO_RESETVAL                            ((uint32_t)(0x00000000U))

/* P_SA_HI */

#define CSL_CPSW_3G_P_SA_HI_MACSRCADDR_47_40_MASK               ((uint32_t)(0x000000FFU))
#define CSL_CPSW_3G_P_SA_HI_MACSRCADDR_47_40_SHIFT              ((uint32_t)(0U))
#define CSL_CPSW_3G_P_SA_HI_MACSRCADDR_47_40_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_SA_HI_MACSRCADDR_47_40_MAX                ((uint32_t)(0x000000ffU))

#define CSL_CPSW_3G_P_SA_HI_MACSRCADDR_39_32_MASK               ((uint32_t)(0x0000FF00U))
#define CSL_CPSW_3G_P_SA_HI_MACSRCADDR_39_32_SHIFT              ((uint32_t)(8U))
#define CSL_CPSW_3G_P_SA_HI_MACSRCADDR_39_32_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_SA_HI_MACSRCADDR_39_32_MAX                ((uint32_t)(0x000000ffU))

#define CSL_CPSW_3G_P_SA_HI_MACSRCADDR_31_24_MASK               ((uint32_t)(0x00FF0000U))
#define CSL_CPSW_3G_P_SA_HI_MACSRCADDR_31_24_SHIFT              ((uint32_t)(16U))
#define CSL_CPSW_3G_P_SA_HI_MACSRCADDR_31_24_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_SA_HI_MACSRCADDR_31_24_MAX                ((uint32_t)(0x000000ffU))

#define CSL_CPSW_3G_P_SA_HI_MACSRCADDR_23_16_MASK               ((uint32_t)(0xFF000000U))
#define CSL_CPSW_3G_P_SA_HI_MACSRCADDR_23_16_SHIFT              ((uint32_t)(24U))
#define CSL_CPSW_3G_P_SA_HI_MACSRCADDR_23_16_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_SA_HI_MACSRCADDR_23_16_MAX                ((uint32_t)(0x000000ffU))

#define CSL_CPSW_3G_P_SA_HI_RESETVAL                            ((uint32_t)(0x00000000U))

/* P_SEND_PERCENT */

#define CSL_CPSW_3G_P_SEND_PERCENT_PRI1_SEND_PERCENT_MASK       ((uint32_t)(0x0000007FU))
#define CSL_CPSW_3G_P_SEND_PERCENT_PRI1_SEND_PERCENT_SHIFT      ((uint32_t)(0U))
#define CSL_CPSW_3G_P_SEND_PERCENT_PRI1_SEND_PERCENT_RESETVAL   ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_SEND_PERCENT_PRI1_SEND_PERCENT_MAX        ((uint32_t)(0x0000007fU))

#define CSL_CPSW_3G_P_SEND_PERCENT_PRI2_SEND_PERCENT_MASK       ((uint32_t)(0x00007F00U))
#define CSL_CPSW_3G_P_SEND_PERCENT_PRI2_SEND_PERCENT_SHIFT      ((uint32_t)(8U))
#define CSL_CPSW_3G_P_SEND_PERCENT_PRI2_SEND_PERCENT_RESETVAL   ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_SEND_PERCENT_PRI2_SEND_PERCENT_MAX        ((uint32_t)(0x0000007fU))

#define CSL_CPSW_3G_P_SEND_PERCENT_PRI3_SEND_PERCENT_MASK       ((uint32_t)(0x007F0000U))
#define CSL_CPSW_3G_P_SEND_PERCENT_PRI3_SEND_PERCENT_SHIFT      ((uint32_t)(16U))
#define CSL_CPSW_3G_P_SEND_PERCENT_PRI3_SEND_PERCENT_RESETVAL   ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_SEND_PERCENT_PRI3_SEND_PERCENT_MAX        ((uint32_t)(0x0000007fU))

#define CSL_CPSW_3G_P_SEND_PERCENT_RESETVAL                     ((uint32_t)(0x00000000U))

/* P_RX_DSCP_PRI_MAP */

#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI0_MASK                 ((uint32_t)(0x00000007U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI0_SHIFT                ((uint32_t)(0U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI0_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI0_MAX                  ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI1_MASK                 ((uint32_t)(0x00000070U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI1_SHIFT                ((uint32_t)(4U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI1_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI1_MAX                  ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI2_MASK                 ((uint32_t)(0x00000700U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI2_SHIFT                ((uint32_t)(8U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI2_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI2_MAX                  ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI3_MASK                 ((uint32_t)(0x00007000U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI3_SHIFT                ((uint32_t)(12U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI3_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI3_MAX                  ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI4_MASK                 ((uint32_t)(0x00070000U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI4_SHIFT                ((uint32_t)(16U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI4_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI4_MAX                  ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI5_MASK                 ((uint32_t)(0x00700000U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI5_SHIFT                ((uint32_t)(20U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI5_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI5_MAX                  ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI6_MASK                 ((uint32_t)(0x07000000U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI6_SHIFT                ((uint32_t)(24U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI6_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI6_MAX                  ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI7_MASK                 ((uint32_t)(0x70000000U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI7_SHIFT                ((uint32_t)(28U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI7_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_PRI7_MAX                  ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P_RX_DSCP_PRI_MAP_RESETVAL                  ((uint32_t)(0x00000000U))

/* P_IDLE2LPI */

#define CSL_CPSW_3G_P_IDLE2LPI_P_IDLE2LPI_MASK                  ((uint32_t)(0x000FFFFFU))
#define CSL_CPSW_3G_P_IDLE2LPI_P_IDLE2LPI_SHIFT                 ((uint32_t)(0U))
#define CSL_CPSW_3G_P_IDLE2LPI_P_IDLE2LPI_RESETVAL              ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_IDLE2LPI_P_IDLE2LPI_MAX                   ((uint32_t)(0x000fffffU))

#define CSL_CPSW_3G_P_IDLE2LPI_RESETVAL                         ((uint32_t)(0x00000000U))

/* P_LPI2WAKE */

#define CSL_CPSW_3G_P_LPI2WAKE_P_LPI2WAKE_MASK                  ((uint32_t)(0x000FFFFFU))
#define CSL_CPSW_3G_P_LPI2WAKE_P_LPI2WAKE_SHIFT                 ((uint32_t)(0U))
#define CSL_CPSW_3G_P_LPI2WAKE_P_LPI2WAKE_RESETVAL              ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P_LPI2WAKE_P_LPI2WAKE_MAX                   ((uint32_t)(0x000fffffU))

#define CSL_CPSW_3G_P_LPI2WAKE_RESETVAL                         ((uint32_t)(0x00000000U))

/* ID */

#define CSL_CPSW_3G_ID_MINOR_VER_MASK                           ((uint32_t)(0x000000FFU))
#define CSL_CPSW_3G_ID_MINOR_VER_SHIFT                          ((uint32_t)(0U))
#define CSL_CPSW_3G_ID_MINOR_VER_RESETVAL                       ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_ID_MINOR_VER_MAX                            ((uint32_t)(0x000000ffU))

#define CSL_CPSW_3G_ID_MAJOR_VER_MASK                           ((uint32_t)(0x0000FF00U))
#define CSL_CPSW_3G_ID_MAJOR_VER_SHIFT                          ((uint32_t)(8U))
#define CSL_CPSW_3G_ID_MAJOR_VER_RESETVAL                       ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_ID_MAJOR_VER_MAX                            ((uint32_t)(0x000000ffU))

#define CSL_CPSW_3G_ID_IDENT_MASK                               ((uint32_t)(0xFFFF0000U))
#define CSL_CPSW_3G_ID_IDENT_SHIFT                              ((uint32_t)(16U))
#define CSL_CPSW_3G_ID_IDENT_RESETVAL                           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_ID_IDENT_MAX                                ((uint32_t)(0x0000ffffU))

#define CSL_CPSW_3G_ID_RESETVAL                                 ((uint32_t)(0x00000000U))

/* CONTROL */

#define CSL_CPSW_3G_CONTROL_ENABLE_RATE_LIMIT_MASK              ((uint32_t)(0x00000001U))
#define CSL_CPSW_3G_CONTROL_ENABLE_RATE_LIMIT_SHIFT             ((uint32_t)(0U))
#define CSL_CPSW_3G_CONTROL_ENABLE_RATE_LIMIT_RESETVAL          ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_CONTROL_ENABLE_RATE_LIMIT_MAX               ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_CONTROL_ENABLE_AUTH_MODE_MASK               ((uint32_t)(0x00000002U))
#define CSL_CPSW_3G_CONTROL_ENABLE_AUTH_MODE_SHIFT              ((uint32_t)(1U))
#define CSL_CPSW_3G_CONTROL_ENABLE_AUTH_MODE_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_CONTROL_ENABLE_AUTH_MODE_MAX                ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_CONTROL_VLAN_AWARE_MASK                     ((uint32_t)(0x00000004U))
#define CSL_CPSW_3G_CONTROL_VLAN_AWARE_SHIFT                    ((uint32_t)(2U))
#define CSL_CPSW_3G_CONTROL_VLAN_AWARE_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_CONTROL_VLAN_AWARE_MAX                      ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_CONTROL_RATE_LIMIT_TX_MASK                  ((uint32_t)(0x00000008U))
#define CSL_CPSW_3G_CONTROL_RATE_LIMIT_TX_SHIFT                 ((uint32_t)(3U))
#define CSL_CPSW_3G_CONTROL_RATE_LIMIT_TX_RESETVAL              ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_CONTROL_RATE_LIMIT_TX_MAX                   ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_CONTROL_BYPASS_MASK                         ((uint32_t)(0x00000010U))
#define CSL_CPSW_3G_CONTROL_BYPASS_SHIFT                        ((uint32_t)(4U))
#define CSL_CPSW_3G_CONTROL_BYPASS_RESETVAL                     ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_CONTROL_BYPASS_MAX                          ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_CONTROL_ENABLE_OUI_DENY_MASK                ((uint32_t)(0x00000020U))
#define CSL_CPSW_3G_CONTROL_ENABLE_OUI_DENY_SHIFT               ((uint32_t)(5U))
#define CSL_CPSW_3G_CONTROL_ENABLE_OUI_DENY_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_CONTROL_ENABLE_OUI_DENY_MAX                 ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_CONTROL_EN_VID0_MODE_MASK                   ((uint32_t)(0x00000040U))
#define CSL_CPSW_3G_CONTROL_EN_VID0_MODE_SHIFT                  ((uint32_t)(6U))
#define CSL_CPSW_3G_CONTROL_EN_VID0_MODE_RESETVAL               ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_CONTROL_EN_VID0_MODE_MAX                    ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_CONTROL_LEARN_NO_VID_MASK                   ((uint32_t)(0x00000080U))
#define CSL_CPSW_3G_CONTROL_LEARN_NO_VID_SHIFT                  ((uint32_t)(7U))
#define CSL_CPSW_3G_CONTROL_LEARN_NO_VID_RESETVAL               ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_CONTROL_LEARN_NO_VID_MAX                    ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_CONTROL_EN_P0_UNI_FLOOD_MASK                ((uint32_t)(0x00000100U))
#define CSL_CPSW_3G_CONTROL_EN_P0_UNI_FLOOD_SHIFT               ((uint32_t)(8U))
#define CSL_CPSW_3G_CONTROL_EN_P0_UNI_FLOOD_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_CONTROL_EN_P0_UNI_FLOOD_MAX                 ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_CONTROL_AGE_OUT_NOW_MASK                    ((uint32_t)(0x20000000U))
#define CSL_CPSW_3G_CONTROL_AGE_OUT_NOW_SHIFT                   ((uint32_t)(29U))
#define CSL_CPSW_3G_CONTROL_AGE_OUT_NOW_RESETVAL                ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_CONTROL_AGE_OUT_NOW_MAX                     ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_CONTROL_CLEAR_TABLE_MASK                    ((uint32_t)(0x40000000U))
#define CSL_CPSW_3G_CONTROL_CLEAR_TABLE_SHIFT                   ((uint32_t)(30U))
#define CSL_CPSW_3G_CONTROL_CLEAR_TABLE_RESETVAL                ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_CONTROL_CLEAR_TABLE_MAX                     ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_CONTROL_ENABLE_ALE_MASK                     ((uint32_t)(0x80000000U))
#define CSL_CPSW_3G_CONTROL_ENABLE_ALE_SHIFT                    ((uint32_t)(31U))
#define CSL_CPSW_3G_CONTROL_ENABLE_ALE_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_CONTROL_ENABLE_ALE_MAX                      ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_CONTROL_RESETVAL                            ((uint32_t)(0x00000000U))

/* PRESCALE */

#define CSL_CPSW_3G_PRESCALE_PRESCALE_MASK                      ((uint32_t)(0x000FFFFFU))
#define CSL_CPSW_3G_PRESCALE_PRESCALE_SHIFT                     ((uint32_t)(0U))
#define CSL_CPSW_3G_PRESCALE_PRESCALE_RESETVAL                  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_PRESCALE_PRESCALE_MAX                       ((uint32_t)(0x000fffffU))

#define CSL_CPSW_3G_PRESCALE_RESETVAL                           ((uint32_t)(0x00000000U))

/* UNKNOWN_VLAN */

#define CSL_CPSW_3G_UNKNOWN_VLAN_UNKNOWN_VLAN_MEMBER_LIST_MASK  ((uint32_t)(0x0000003FU))
#define CSL_CPSW_3G_UNKNOWN_VLAN_UNKNOWN_VLAN_MEMBER_LIST_SHIFT  ((uint32_t)(0U))
#define CSL_CPSW_3G_UNKNOWN_VLAN_UNKNOWN_VLAN_MEMBER_LIST_RESETVAL  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_UNKNOWN_VLAN_UNKNOWN_VLAN_MEMBER_LIST_MAX   ((uint32_t)(0x0000003fU))

#define CSL_CPSW_3G_UNKNOWN_VLAN_UNKNOWN_MCAST_FLOOD_MASK_MASK  ((uint32_t)(0x00003F00U))
#define CSL_CPSW_3G_UNKNOWN_VLAN_UNKNOWN_MCAST_FLOOD_MASK_SHIFT  ((uint32_t)(8U))
#define CSL_CPSW_3G_UNKNOWN_VLAN_UNKNOWN_MCAST_FLOOD_MASK_RESETVAL  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_UNKNOWN_VLAN_UNKNOWN_MCAST_FLOOD_MASK_MAX   ((uint32_t)(0x0000003fU))

#define CSL_CPSW_3G_UNKNOWN_VLAN_UNKNOWN_REG_MCAST_FLOOD_MASK_MASK  ((uint32_t)(0x003F0000U))
#define CSL_CPSW_3G_UNKNOWN_VLAN_UNKNOWN_REG_MCAST_FLOOD_MASK_SHIFT  ((uint32_t)(16U))
#define CSL_CPSW_3G_UNKNOWN_VLAN_UNKNOWN_REG_MCAST_FLOOD_MASK_RESETVAL  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_UNKNOWN_VLAN_UNKNOWN_REG_MCAST_FLOOD_MASK_MAX  ((uint32_t)(0x0000003fU))

#define CSL_CPSW_3G_UNKNOWN_VLAN_UNKNOWN_FORCE_UNTAGGED_EGRESS_MASK  ((uint32_t)(0x3F000000U))
#define CSL_CPSW_3G_UNKNOWN_VLAN_UNKNOWN_FORCE_UNTAGGED_EGRESS_SHIFT  ((uint32_t)(24U))
#define CSL_CPSW_3G_UNKNOWN_VLAN_UNKNOWN_FORCE_UNTAGGED_EGRESS_RESETVAL  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_UNKNOWN_VLAN_UNKNOWN_FORCE_UNTAGGED_EGRESS_MAX  ((uint32_t)(0x0000003fU))

#define CSL_CPSW_3G_UNKNOWN_VLAN_RESETVAL                       ((uint32_t)(0x00000000U))

/* TABLE_CONTROL */

#define CSL_CPSW_3G_TABLE_CONTROL_ENTRY_POINTER_MASK            ((uint32_t)(0x000003FFU))
#define CSL_CPSW_3G_TABLE_CONTROL_ENTRY_POINTER_SHIFT           ((uint32_t)(0U))
#define CSL_CPSW_3G_TABLE_CONTROL_ENTRY_POINTER_RESETVAL        ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TABLE_CONTROL_ENTRY_POINTER_MAX             ((uint32_t)(0x000003ffU))

#define CSL_CPSW_3G_TABLE_CONTROL_WRITE_RDZ_MASK                ((uint32_t)(0x80000000U))
#define CSL_CPSW_3G_TABLE_CONTROL_WRITE_RDZ_SHIFT               ((uint32_t)(31U))
#define CSL_CPSW_3G_TABLE_CONTROL_WRITE_RDZ_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TABLE_CONTROL_WRITE_RDZ_MAX                 ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_TABLE_CONTROL_RESETVAL                      ((uint32_t)(0x00000000U))

/* TABLE_WORD2 */

#define CSL_CPSW_3G_TABLE_WORD2_ENTRY_71_64_MASK                ((uint32_t)(0x000000FFU))
#define CSL_CPSW_3G_TABLE_WORD2_ENTRY_71_64_SHIFT               ((uint32_t)(0U))
#define CSL_CPSW_3G_TABLE_WORD2_ENTRY_71_64_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TABLE_WORD2_ENTRY_71_64_MAX                 ((uint32_t)(0x000000ffU))

#define CSL_CPSW_3G_TABLE_WORD2_RESETVAL                        ((uint32_t)(0x00000000U))

/* TABLE_WORD1 */

#define CSL_CPSW_3G_TABLE_WORD1_ENTRY_63_32_MASK                ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_TABLE_WORD1_ENTRY_63_32_SHIFT               ((uint32_t)(0U))
#define CSL_CPSW_3G_TABLE_WORD1_ENTRY_63_32_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TABLE_WORD1_ENTRY_63_32_MAX                 ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_TABLE_WORD1_RESETVAL                        ((uint32_t)(0x00000000U))

/* TABLE_WORD0 */

#define CSL_CPSW_3G_TABLE_WORD0_ENTRY_31_0_MASK                 ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_TABLE_WORD0_ENTRY_31_0_SHIFT                ((uint32_t)(0U))
#define CSL_CPSW_3G_TABLE_WORD0_ENTRY_31_0_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TABLE_WORD0_ENTRY_31_0_MAX                  ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_TABLE_WORD0_RESETVAL                        ((uint32_t)(0x00000000U))

/* PORT_CONTROL */

#define CSL_CPSW_3G_PORT_CONTROL_PORT_STATE_MASK                ((uint32_t)(0x00000003U))
#define CSL_CPSW_3G_PORT_CONTROL_PORT_STATE_SHIFT               ((uint32_t)(0U))
#define CSL_CPSW_3G_PORT_CONTROL_PORT_STATE_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_PORT_CONTROL_PORT_STATE_MAX                 ((uint32_t)(0x00000003U))

#define CSL_CPSW_3G_PORT_CONTROL_DROP_UNTAGGED_MASK             ((uint32_t)(0x00000004U))
#define CSL_CPSW_3G_PORT_CONTROL_DROP_UNTAGGED_SHIFT            ((uint32_t)(2U))
#define CSL_CPSW_3G_PORT_CONTROL_DROP_UNTAGGED_RESETVAL         ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_PORT_CONTROL_DROP_UNTAGGED_MAX              ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_PORT_CONTROL_VID_INGRESS_CHECK_MASK         ((uint32_t)(0x00000008U))
#define CSL_CPSW_3G_PORT_CONTROL_VID_INGRESS_CHECK_SHIFT        ((uint32_t)(3U))
#define CSL_CPSW_3G_PORT_CONTROL_VID_INGRESS_CHECK_RESETVAL     ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_PORT_CONTROL_VID_INGRESS_CHECK_MAX          ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_PORT_CONTROL_NO_LEARN_MASK                  ((uint32_t)(0x00000010U))
#define CSL_CPSW_3G_PORT_CONTROL_NO_LEARN_SHIFT                 ((uint32_t)(4U))
#define CSL_CPSW_3G_PORT_CONTROL_NO_LEARN_RESETVAL              ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_PORT_CONTROL_NO_LEARN_MAX                   ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_PORT_CONTROL_NO_SA_UPDATE_MASK              ((uint32_t)(0x00000020U))
#define CSL_CPSW_3G_PORT_CONTROL_NO_SA_UPDATE_SHIFT             ((uint32_t)(5U))
#define CSL_CPSW_3G_PORT_CONTROL_NO_SA_UPDATE_RESETVAL          ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_PORT_CONTROL_NO_SA_UPDATE_MAX               ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_PORT_CONTROL_MCAST_LIMIT_MASK               ((uint32_t)(0x00FF0000U))
#define CSL_CPSW_3G_PORT_CONTROL_MCAST_LIMIT_SHIFT              ((uint32_t)(16U))
#define CSL_CPSW_3G_PORT_CONTROL_MCAST_LIMIT_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_PORT_CONTROL_MCAST_LIMIT_MAX                ((uint32_t)(0x000000ffU))

#define CSL_CPSW_3G_PORT_CONTROL_BCAST_LIMIT_MASK               ((uint32_t)(0xFF000000U))
#define CSL_CPSW_3G_PORT_CONTROL_BCAST_LIMIT_SHIFT              ((uint32_t)(24U))
#define CSL_CPSW_3G_PORT_CONTROL_BCAST_LIMIT_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_PORT_CONTROL_BCAST_LIMIT_MAX                ((uint32_t)(0x000000ffU))

#define CSL_CPSW_3G_PORT_CONTROL_RESETVAL                       ((uint32_t)(0x00000000U))

/* RXGOODFRAMES */

#define CSL_CPSW_3G_RXGOODFRAMES_COUNT_MASK                     ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_RXGOODFRAMES_COUNT_SHIFT                    ((uint32_t)(0U))
#define CSL_CPSW_3G_RXGOODFRAMES_COUNT_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_RXGOODFRAMES_COUNT_MAX                      ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_RXGOODFRAMES_RESETVAL                       ((uint32_t)(0x00000000U))

/* RXBROADCASTFRAMES */

#define CSL_CPSW_3G_RXBROADCASTFRAMES_COUNT_MASK                ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_RXBROADCASTFRAMES_COUNT_SHIFT               ((uint32_t)(0U))
#define CSL_CPSW_3G_RXBROADCASTFRAMES_COUNT_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_RXBROADCASTFRAMES_COUNT_MAX                 ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_RXBROADCASTFRAMES_RESETVAL                  ((uint32_t)(0x00000000U))

/* RXMULTICASTFRAMES */

#define CSL_CPSW_3G_RXMULTICASTFRAMES_COUNT_MASK                ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_RXMULTICASTFRAMES_COUNT_SHIFT               ((uint32_t)(0U))
#define CSL_CPSW_3G_RXMULTICASTFRAMES_COUNT_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_RXMULTICASTFRAMES_COUNT_MAX                 ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_RXMULTICASTFRAMES_RESETVAL                  ((uint32_t)(0x00000000U))

/* RXPAUSEFRAMES */

#define CSL_CPSW_3G_RXPAUSEFRAMES_COUNT_MASK                    ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_RXPAUSEFRAMES_COUNT_SHIFT                   ((uint32_t)(0U))
#define CSL_CPSW_3G_RXPAUSEFRAMES_COUNT_RESETVAL                ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_RXPAUSEFRAMES_COUNT_MAX                     ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_RXPAUSEFRAMES_RESETVAL                      ((uint32_t)(0x00000000U))

/* RXCRCERRORS */

#define CSL_CPSW_3G_RXCRCERRORS_COUNT_MASK                      ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_RXCRCERRORS_COUNT_SHIFT                     ((uint32_t)(0U))
#define CSL_CPSW_3G_RXCRCERRORS_COUNT_RESETVAL                  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_RXCRCERRORS_COUNT_MAX                       ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_RXCRCERRORS_RESETVAL                        ((uint32_t)(0x00000000U))

/* RXALIGNCODEERRORS */

#define CSL_CPSW_3G_RXALIGNCODEERRORS_COUNT_MASK                ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_RXALIGNCODEERRORS_COUNT_SHIFT               ((uint32_t)(0U))
#define CSL_CPSW_3G_RXALIGNCODEERRORS_COUNT_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_RXALIGNCODEERRORS_COUNT_MAX                 ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_RXALIGNCODEERRORS_RESETVAL                  ((uint32_t)(0x00000000U))

/* RXOVERSIZEDFRAMES */

#define CSL_CPSW_3G_RXOVERSIZEDFRAMES_COUNT_MASK                ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_RXOVERSIZEDFRAMES_COUNT_SHIFT               ((uint32_t)(0U))
#define CSL_CPSW_3G_RXOVERSIZEDFRAMES_COUNT_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_RXOVERSIZEDFRAMES_COUNT_MAX                 ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_RXOVERSIZEDFRAMES_RESETVAL                  ((uint32_t)(0x00000000U))

/* RXJABBERFRAMES */

#define CSL_CPSW_3G_RXJABBERFRAMES_COUNT_MASK                   ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_RXJABBERFRAMES_COUNT_SHIFT                  ((uint32_t)(0U))
#define CSL_CPSW_3G_RXJABBERFRAMES_COUNT_RESETVAL               ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_RXJABBERFRAMES_COUNT_MAX                    ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_RXJABBERFRAMES_RESETVAL                     ((uint32_t)(0x00000000U))

/* RXUNDERSIZEDFRAMES */

#define CSL_CPSW_3G_RXUNDERSIZEDFRAMES_COUNT_MASK               ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_RXUNDERSIZEDFRAMES_COUNT_SHIFT              ((uint32_t)(0U))
#define CSL_CPSW_3G_RXUNDERSIZEDFRAMES_COUNT_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_RXUNDERSIZEDFRAMES_COUNT_MAX                ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_RXUNDERSIZEDFRAMES_RESETVAL                 ((uint32_t)(0x00000000U))

/* RXFRAGMENTS */

#define CSL_CPSW_3G_RXFRAGMENTS_COUNT_MASK                      ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_RXFRAGMENTS_COUNT_SHIFT                     ((uint32_t)(0U))
#define CSL_CPSW_3G_RXFRAGMENTS_COUNT_RESETVAL                  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_RXFRAGMENTS_COUNT_MAX                       ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_RXFRAGMENTS_RESETVAL                        ((uint32_t)(0x00000000U))

/* RXOCTETS */

#define CSL_CPSW_3G_RXOCTETS_COUNT_MASK                         ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_RXOCTETS_COUNT_SHIFT                        ((uint32_t)(0U))
#define CSL_CPSW_3G_RXOCTETS_COUNT_RESETVAL                     ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_RXOCTETS_COUNT_MAX                          ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_RXOCTETS_RESETVAL                           ((uint32_t)(0x00000000U))

/* TXGOODFRAMES */

#define CSL_CPSW_3G_TXGOODFRAMES_COUNT_MASK                     ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_TXGOODFRAMES_COUNT_SHIFT                    ((uint32_t)(0U))
#define CSL_CPSW_3G_TXGOODFRAMES_COUNT_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TXGOODFRAMES_COUNT_MAX                      ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_TXGOODFRAMES_RESETVAL                       ((uint32_t)(0x00000000U))

/* TXBROADCASTFRAMES */

#define CSL_CPSW_3G_TXBROADCASTFRAMES_COUNT_MASK                ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_TXBROADCASTFRAMES_COUNT_SHIFT               ((uint32_t)(0U))
#define CSL_CPSW_3G_TXBROADCASTFRAMES_COUNT_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TXBROADCASTFRAMES_COUNT_MAX                 ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_TXBROADCASTFRAMES_RESETVAL                  ((uint32_t)(0x00000000U))

/* TXMULTICASTFRAMES */

#define CSL_CPSW_3G_TXMULTICASTFRAMES_COUNT_MASK                ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_TXMULTICASTFRAMES_COUNT_SHIFT               ((uint32_t)(0U))
#define CSL_CPSW_3G_TXMULTICASTFRAMES_COUNT_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TXMULTICASTFRAMES_COUNT_MAX                 ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_TXMULTICASTFRAMES_RESETVAL                  ((uint32_t)(0x00000000U))

/* TXPAUSEFRAMES */

#define CSL_CPSW_3G_TXPAUSEFRAMES_COUNT_MASK                    ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_TXPAUSEFRAMES_COUNT_SHIFT                   ((uint32_t)(0U))
#define CSL_CPSW_3G_TXPAUSEFRAMES_COUNT_RESETVAL                ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TXPAUSEFRAMES_COUNT_MAX                     ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_TXPAUSEFRAMES_RESETVAL                      ((uint32_t)(0x00000000U))

/* TXDEFERREDFRAMES */

#define CSL_CPSW_3G_TXDEFERREDFRAMES_COUNT_MASK                 ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_TXDEFERREDFRAMES_COUNT_SHIFT                ((uint32_t)(0U))
#define CSL_CPSW_3G_TXDEFERREDFRAMES_COUNT_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TXDEFERREDFRAMES_COUNT_MAX                  ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_TXDEFERREDFRAMES_RESETVAL                   ((uint32_t)(0x00000000U))

/* TXCOLLISIONFRAMES */

#define CSL_CPSW_3G_TXCOLLISIONFRAMES_COUNT_MASK                ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_TXCOLLISIONFRAMES_COUNT_SHIFT               ((uint32_t)(0U))
#define CSL_CPSW_3G_TXCOLLISIONFRAMES_COUNT_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TXCOLLISIONFRAMES_COUNT_MAX                 ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_TXCOLLISIONFRAMES_RESETVAL                  ((uint32_t)(0x00000000U))

/* TXSINGLECOLLFRAMES */

#define CSL_CPSW_3G_TXSINGLECOLLFRAMES_COUNT_MASK               ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_TXSINGLECOLLFRAMES_COUNT_SHIFT              ((uint32_t)(0U))
#define CSL_CPSW_3G_TXSINGLECOLLFRAMES_COUNT_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TXSINGLECOLLFRAMES_COUNT_MAX                ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_TXSINGLECOLLFRAMES_RESETVAL                 ((uint32_t)(0x00000000U))

/* TXMULTCOLLFRAMES */

#define CSL_CPSW_3G_TXMULTCOLLFRAMES_COUNT_MASK                 ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_TXMULTCOLLFRAMES_COUNT_SHIFT                ((uint32_t)(0U))
#define CSL_CPSW_3G_TXMULTCOLLFRAMES_COUNT_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TXMULTCOLLFRAMES_COUNT_MAX                  ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_TXMULTCOLLFRAMES_RESETVAL                   ((uint32_t)(0x00000000U))

/* TXEXCESSIVECOLLISIONS */

#define CSL_CPSW_3G_TXEXCESSIVECOLLISIONS_COUNT_MASK            ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_TXEXCESSIVECOLLISIONS_COUNT_SHIFT           ((uint32_t)(0U))
#define CSL_CPSW_3G_TXEXCESSIVECOLLISIONS_COUNT_RESETVAL        ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TXEXCESSIVECOLLISIONS_COUNT_MAX             ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_TXEXCESSIVECOLLISIONS_RESETVAL              ((uint32_t)(0x00000000U))

/* TXLATECOLLISIONS */

#define CSL_CPSW_3G_TXLATECOLLISIONS_COUNT_MASK                 ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_TXLATECOLLISIONS_COUNT_SHIFT                ((uint32_t)(0U))
#define CSL_CPSW_3G_TXLATECOLLISIONS_COUNT_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TXLATECOLLISIONS_COUNT_MAX                  ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_TXLATECOLLISIONS_RESETVAL                   ((uint32_t)(0x00000000U))

/* TXUNDERRUN */

#define CSL_CPSW_3G_TXUNDERRUN_COUNT_MASK                       ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_TXUNDERRUN_COUNT_SHIFT                      ((uint32_t)(0U))
#define CSL_CPSW_3G_TXUNDERRUN_COUNT_RESETVAL                   ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TXUNDERRUN_COUNT_MAX                        ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_TXUNDERRUN_RESETVAL                         ((uint32_t)(0x00000000U))

/* TXCARRIERSENSEERRORS */

#define CSL_CPSW_3G_TXCARRIERSENSEERRORS_COUNT_MASK             ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_TXCARRIERSENSEERRORS_COUNT_SHIFT            ((uint32_t)(0U))
#define CSL_CPSW_3G_TXCARRIERSENSEERRORS_COUNT_RESETVAL         ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TXCARRIERSENSEERRORS_COUNT_MAX              ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_TXCARRIERSENSEERRORS_RESETVAL               ((uint32_t)(0x00000000U))

/* TXOCTETS */

#define CSL_CPSW_3G_TXOCTETS_COUNT_MASK                         ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_TXOCTETS_COUNT_SHIFT                        ((uint32_t)(0U))
#define CSL_CPSW_3G_TXOCTETS_COUNT_RESETVAL                     ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TXOCTETS_COUNT_MAX                          ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_TXOCTETS_RESETVAL                           ((uint32_t)(0x00000000U))

/* OCTETFRAMES64 */

#define CSL_CPSW_3G_OCTETFRAMES64_COUNT_MASK                    ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_OCTETFRAMES64_COUNT_SHIFT                   ((uint32_t)(0U))
#define CSL_CPSW_3G_OCTETFRAMES64_COUNT_RESETVAL                ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_OCTETFRAMES64_COUNT_MAX                     ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_OCTETFRAMES64_RESETVAL                      ((uint32_t)(0x00000000U))

/* OCTETFRAMES65T127 */

#define CSL_CPSW_3G_OCTETFRAMES65T127_COUNT_MASK                ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_OCTETFRAMES65T127_COUNT_SHIFT               ((uint32_t)(0U))
#define CSL_CPSW_3G_OCTETFRAMES65T127_COUNT_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_OCTETFRAMES65T127_COUNT_MAX                 ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_OCTETFRAMES65T127_RESETVAL                  ((uint32_t)(0x00000000U))

/* OCTETFRAMES128T255 */

#define CSL_CPSW_3G_OCTETFRAMES128T255_COUNT_MASK               ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_OCTETFRAMES128T255_COUNT_SHIFT              ((uint32_t)(0U))
#define CSL_CPSW_3G_OCTETFRAMES128T255_COUNT_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_OCTETFRAMES128T255_COUNT_MAX                ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_OCTETFRAMES128T255_RESETVAL                 ((uint32_t)(0x00000000U))

/* OCTETFRAMES256T511 */

#define CSL_CPSW_3G_OCTETFRAMES256T511_COUNT_MASK               ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_OCTETFRAMES256T511_COUNT_SHIFT              ((uint32_t)(0U))
#define CSL_CPSW_3G_OCTETFRAMES256T511_COUNT_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_OCTETFRAMES256T511_COUNT_MAX                ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_OCTETFRAMES256T511_RESETVAL                 ((uint32_t)(0x00000000U))

/* OCTETFRAMES512T1023 */

#define CSL_CPSW_3G_OCTETFRAMES512T1023_COUNT_MASK              ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_OCTETFRAMES512T1023_COUNT_SHIFT             ((uint32_t)(0U))
#define CSL_CPSW_3G_OCTETFRAMES512T1023_COUNT_RESETVAL          ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_OCTETFRAMES512T1023_COUNT_MAX               ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_OCTETFRAMES512T1023_RESETVAL                ((uint32_t)(0x00000000U))

/* OCTETFRAMES1024TUP */

#define CSL_CPSW_3G_OCTETFRAMES1024TUP_COUNT_MASK               ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_OCTETFRAMES1024TUP_COUNT_SHIFT              ((uint32_t)(0U))
#define CSL_CPSW_3G_OCTETFRAMES1024TUP_COUNT_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_OCTETFRAMES1024TUP_COUNT_MAX                ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_OCTETFRAMES1024TUP_RESETVAL                 ((uint32_t)(0x00000000U))

/* NETOCTETS */

#define CSL_CPSW_3G_NETOCTETS_COUNT_MASK                        ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_NETOCTETS_COUNT_SHIFT                       ((uint32_t)(0U))
#define CSL_CPSW_3G_NETOCTETS_COUNT_RESETVAL                    ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_NETOCTETS_COUNT_MAX                         ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_NETOCTETS_RESETVAL                          ((uint32_t)(0x00000000U))

/* RXSOFOVERRUNS */

#define CSL_CPSW_3G_RXSOFOVERRUNS_COUNT_MASK                    ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_RXSOFOVERRUNS_COUNT_SHIFT                   ((uint32_t)(0U))
#define CSL_CPSW_3G_RXSOFOVERRUNS_COUNT_RESETVAL                ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_RXSOFOVERRUNS_COUNT_MAX                     ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_RXSOFOVERRUNS_RESETVAL                      ((uint32_t)(0x00000000U))

/* RXMOFOVERRUNS */

#define CSL_CPSW_3G_RXMOFOVERRUNS_COUNT_MASK                    ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_RXMOFOVERRUNS_COUNT_SHIFT                   ((uint32_t)(0U))
#define CSL_CPSW_3G_RXMOFOVERRUNS_COUNT_RESETVAL                ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_RXMOFOVERRUNS_COUNT_MAX                     ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_RXMOFOVERRUNS_RESETVAL                      ((uint32_t)(0x00000000U))

/* RXDMAOVERRUNS */

#define CSL_CPSW_3G_RXDMAOVERRUNS_COUNT_MASK                    ((uint32_t)(0xFFFFFFFFU))
#define CSL_CPSW_3G_RXDMAOVERRUNS_COUNT_SHIFT                   ((uint32_t)(0U))
#define CSL_CPSW_3G_RXDMAOVERRUNS_COUNT_RESETVAL                ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_RXDMAOVERRUNS_COUNT_MAX                     ((uint32_t)(0xffffffffU))

#define CSL_CPSW_3G_RXDMAOVERRUNS_RESETVAL                      ((uint32_t)(0x00000000U))

/* ID_VER */

#define CSL_CPSW_3G_ID_VER_MINOR_VER_MASK                       ((uint32_t)(0x000000FFU))
#define CSL_CPSW_3G_ID_VER_MINOR_VER_SHIFT                      ((uint32_t)(0U))
#define CSL_CPSW_3G_ID_VER_MINOR_VER_RESETVAL                   ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_ID_VER_MINOR_VER_MAX                        ((uint32_t)(0x000000ffU))

#define CSL_CPSW_3G_ID_VER_MAJ_VER_MASK                         ((uint32_t)(0x00000700U))
#define CSL_CPSW_3G_ID_VER_MAJ_VER_SHIFT                        ((uint32_t)(8U))
#define CSL_CPSW_3G_ID_VER_MAJ_VER_RESETVAL                     ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_ID_VER_MAJ_VER_MAX                          ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_ID_VER_RTL_VER_MASK                         ((uint32_t)(0x0000F800U))
#define CSL_CPSW_3G_ID_VER_RTL_VER_SHIFT                        ((uint32_t)(11U))
#define CSL_CPSW_3G_ID_VER_RTL_VER_RESETVAL                     ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_ID_VER_RTL_VER_MAX                          ((uint32_t)(0x0000001fU))

#define CSL_CPSW_3G_ID_VER_IDENT_MASK                           ((uint32_t)(0xFFFF0000U))
#define CSL_CPSW_3G_ID_VER_IDENT_SHIFT                          ((uint32_t)(16U))
#define CSL_CPSW_3G_ID_VER_IDENT_RESETVAL                       ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_ID_VER_IDENT_MAX                            ((uint32_t)(0x0000ffffU))

#define CSL_CPSW_3G_ID_VER_RESETVAL                             ((uint32_t)(0x00000000U))

/* SW_CONTROL */

#define CSL_CPSW_3G_SW_CONTROL_FIFO_LOOPBACK_MASK               ((uint32_t)(0x00000001U))
#define CSL_CPSW_3G_SW_CONTROL_FIFO_LOOPBACK_SHIFT              ((uint32_t)(0U))
#define CSL_CPSW_3G_SW_CONTROL_FIFO_LOOPBACK_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_SW_CONTROL_FIFO_LOOPBACK_MAX                ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_SW_CONTROL_VLAN_AWARE_MASK                  ((uint32_t)(0x00000002U))
#define CSL_CPSW_3G_SW_CONTROL_VLAN_AWARE_SHIFT                 ((uint32_t)(1U))
#define CSL_CPSW_3G_SW_CONTROL_VLAN_AWARE_RESETVAL              ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_SW_CONTROL_VLAN_AWARE_MAX                   ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_SW_CONTROL_RX_VLAN_ENCAP_MASK               ((uint32_t)(0x00000004U))
#define CSL_CPSW_3G_SW_CONTROL_RX_VLAN_ENCAP_SHIFT              ((uint32_t)(2U))
#define CSL_CPSW_3G_SW_CONTROL_RX_VLAN_ENCAP_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_SW_CONTROL_RX_VLAN_ENCAP_MAX                ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_SW_CONTROL_DLR_EN_MASK                      ((uint32_t)(0x00000008U))
#define CSL_CPSW_3G_SW_CONTROL_DLR_EN_SHIFT                     ((uint32_t)(3U))
#define CSL_CPSW_3G_SW_CONTROL_DLR_EN_RESETVAL                  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_SW_CONTROL_DLR_EN_MAX                       ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_SW_CONTROL_EEE_EN_MASK                      ((uint32_t)(0x00000010U))
#define CSL_CPSW_3G_SW_CONTROL_EEE_EN_SHIFT                     ((uint32_t)(4U))
#define CSL_CPSW_3G_SW_CONTROL_EEE_EN_RESETVAL                  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_SW_CONTROL_EEE_EN_MAX                       ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_SW_CONTROL_RESETVAL                         ((uint32_t)(0x00000000U))

/* SOFT_RESET */

#define CSL_CPSW_3G_SOFT_RESET_SOFT_RESET_MASK                  ((uint32_t)(0x00000001U))
#define CSL_CPSW_3G_SOFT_RESET_SOFT_RESET_SHIFT                 ((uint32_t)(0U))
#define CSL_CPSW_3G_SOFT_RESET_SOFT_RESET_RESETVAL              ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_SOFT_RESET_SOFT_RESET_MAX                   ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_SOFT_RESET_RESETVAL                         ((uint32_t)(0x00000000U))

/* STAT_PORT_EN */

#define CSL_CPSW_3G_STAT_PORT_EN_P0_STAT_EN_MASK                ((uint32_t)(0x00000001U))
#define CSL_CPSW_3G_STAT_PORT_EN_P0_STAT_EN_SHIFT               ((uint32_t)(0U))
#define CSL_CPSW_3G_STAT_PORT_EN_P0_STAT_EN_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_STAT_PORT_EN_P0_STAT_EN_MAX                 ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_STAT_PORT_EN_P1_STAT_EN_MASK                ((uint32_t)(0x00000002U))
#define CSL_CPSW_3G_STAT_PORT_EN_P1_STAT_EN_SHIFT               ((uint32_t)(1U))
#define CSL_CPSW_3G_STAT_PORT_EN_P1_STAT_EN_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_STAT_PORT_EN_P1_STAT_EN_MAX                 ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_STAT_PORT_EN_P2_STAT_EN_MASK                ((uint32_t)(0x00000004U))
#define CSL_CPSW_3G_STAT_PORT_EN_P2_STAT_EN_SHIFT               ((uint32_t)(2U))
#define CSL_CPSW_3G_STAT_PORT_EN_P2_STAT_EN_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_STAT_PORT_EN_P2_STAT_EN_MAX                 ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_STAT_PORT_EN_RESETVAL                       ((uint32_t)(0x00000000U))

/* PTYPE */

#define CSL_CPSW_3G_PTYPE_ESC_PRI_LD_VAL_MASK                   ((uint32_t)(0x0000001FU))
#define CSL_CPSW_3G_PTYPE_ESC_PRI_LD_VAL_SHIFT                  ((uint32_t)(0U))
#define CSL_CPSW_3G_PTYPE_ESC_PRI_LD_VAL_RESETVAL               ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_PTYPE_ESC_PRI_LD_VAL_MAX                    ((uint32_t)(0x0000001fU))

#define CSL_CPSW_3G_PTYPE_P0_PTYPE_ESC_MASK                     ((uint32_t)(0x00000100U))
#define CSL_CPSW_3G_PTYPE_P0_PTYPE_ESC_SHIFT                    ((uint32_t)(8U))
#define CSL_CPSW_3G_PTYPE_P0_PTYPE_ESC_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_PTYPE_P0_PTYPE_ESC_MAX                      ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_PTYPE_P1_PTYPE_ESC_MASK                     ((uint32_t)(0x00000200U))
#define CSL_CPSW_3G_PTYPE_P1_PTYPE_ESC_SHIFT                    ((uint32_t)(9U))
#define CSL_CPSW_3G_PTYPE_P1_PTYPE_ESC_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_PTYPE_P1_PTYPE_ESC_MAX                      ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_PTYPE_P2_PTYPE_ESC_MASK                     ((uint32_t)(0x00000400U))
#define CSL_CPSW_3G_PTYPE_P2_PTYPE_ESC_SHIFT                    ((uint32_t)(10U))
#define CSL_CPSW_3G_PTYPE_P2_PTYPE_ESC_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_PTYPE_P2_PTYPE_ESC_MAX                      ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_PTYPE_P1_PRI1_SHAPE_EN_MASK                 ((uint32_t)(0x00010000U))
#define CSL_CPSW_3G_PTYPE_P1_PRI1_SHAPE_EN_SHIFT                ((uint32_t)(16U))
#define CSL_CPSW_3G_PTYPE_P1_PRI1_SHAPE_EN_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_PTYPE_P1_PRI1_SHAPE_EN_MAX                  ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_PTYPE_P1_PRI2_SHAPE_EN_MASK                 ((uint32_t)(0x00020000U))
#define CSL_CPSW_3G_PTYPE_P1_PRI2_SHAPE_EN_SHIFT                ((uint32_t)(17U))
#define CSL_CPSW_3G_PTYPE_P1_PRI2_SHAPE_EN_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_PTYPE_P1_PRI2_SHAPE_EN_MAX                  ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_PTYPE_P1_PRI3_SHAPE_EN_MASK                 ((uint32_t)(0x00040000U))
#define CSL_CPSW_3G_PTYPE_P1_PRI3_SHAPE_EN_SHIFT                ((uint32_t)(18U))
#define CSL_CPSW_3G_PTYPE_P1_PRI3_SHAPE_EN_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_PTYPE_P1_PRI3_SHAPE_EN_MAX                  ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_PTYPE_P2_PRI1_SHAPE_EN_MASK                 ((uint32_t)(0x00080000U))
#define CSL_CPSW_3G_PTYPE_P2_PRI1_SHAPE_EN_SHIFT                ((uint32_t)(19U))
#define CSL_CPSW_3G_PTYPE_P2_PRI1_SHAPE_EN_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_PTYPE_P2_PRI1_SHAPE_EN_MAX                  ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_PTYPE_P2_PRI2_SHAPE_EN_MASK                 ((uint32_t)(0x00100000U))
#define CSL_CPSW_3G_PTYPE_P2_PRI2_SHAPE_EN_SHIFT                ((uint32_t)(20U))
#define CSL_CPSW_3G_PTYPE_P2_PRI2_SHAPE_EN_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_PTYPE_P2_PRI2_SHAPE_EN_MAX                  ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_PTYPE_P2_PRI3_SHAPE_EN_MASK                 ((uint32_t)(0x00200000U))
#define CSL_CPSW_3G_PTYPE_P2_PRI3_SHAPE_EN_SHIFT                ((uint32_t)(21U))
#define CSL_CPSW_3G_PTYPE_P2_PRI3_SHAPE_EN_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_PTYPE_P2_PRI3_SHAPE_EN_MAX                  ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_PTYPE_RESETVAL                              ((uint32_t)(0x00000000U))

/* SOFT_IDLE */

#define CSL_CPSW_3G_SOFT_IDLE_SOFT_IDLE_MASK                    ((uint32_t)(0x00000001U))
#define CSL_CPSW_3G_SOFT_IDLE_SOFT_IDLE_SHIFT                   ((uint32_t)(0U))
#define CSL_CPSW_3G_SOFT_IDLE_SOFT_IDLE_RESETVAL                ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_SOFT_IDLE_SOFT_IDLE_MAX                     ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_SOFT_IDLE_RESETVAL                          ((uint32_t)(0x00000000U))

/* THRU_RATE */

#define CSL_CPSW_3G_THRU_RATE_CPDMA_THRU_RATE_MASK              ((uint32_t)(0x0000000FU))
#define CSL_CPSW_3G_THRU_RATE_CPDMA_THRU_RATE_SHIFT             ((uint32_t)(0U))
#define CSL_CPSW_3G_THRU_RATE_CPDMA_THRU_RATE_RESETVAL          ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_THRU_RATE_CPDMA_THRU_RATE_MAX               ((uint32_t)(0x0000000fU))

#define CSL_CPSW_3G_THRU_RATE_SL_RX_THRU_RATE_MASK              ((uint32_t)(0x0000F000U))
#define CSL_CPSW_3G_THRU_RATE_SL_RX_THRU_RATE_SHIFT             ((uint32_t)(12U))
#define CSL_CPSW_3G_THRU_RATE_SL_RX_THRU_RATE_RESETVAL          ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_THRU_RATE_SL_RX_THRU_RATE_MAX               ((uint32_t)(0x0000000fU))

#define CSL_CPSW_3G_THRU_RATE_RESETVAL                          ((uint32_t)(0x00000000U))

/* GAP_THRESH */

#define CSL_CPSW_3G_GAP_THRESH_GAP_THRESH_MASK                  ((uint32_t)(0x0000001FU))
#define CSL_CPSW_3G_GAP_THRESH_GAP_THRESH_SHIFT                 ((uint32_t)(0U))
#define CSL_CPSW_3G_GAP_THRESH_GAP_THRESH_RESETVAL              ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_GAP_THRESH_GAP_THRESH_MAX                   ((uint32_t)(0x0000001fU))

#define CSL_CPSW_3G_GAP_THRESH_RESETVAL                         ((uint32_t)(0x00000000U))

/* TX_START_WDS */

#define CSL_CPSW_3G_TX_START_WDS_TX_START_WDS_MASK              ((uint32_t)(0x000007FFU))
#define CSL_CPSW_3G_TX_START_WDS_TX_START_WDS_SHIFT             ((uint32_t)(0U))
#define CSL_CPSW_3G_TX_START_WDS_TX_START_WDS_RESETVAL          ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TX_START_WDS_TX_START_WDS_MAX               ((uint32_t)(0x000007ffU))

#define CSL_CPSW_3G_TX_START_WDS_RESETVAL                       ((uint32_t)(0x00000000U))

/* FLOW_CONTROL */

#define CSL_CPSW_3G_FLOW_CONTROL_P0_FLOW_EN_MASK                ((uint32_t)(0x00000001U))
#define CSL_CPSW_3G_FLOW_CONTROL_P0_FLOW_EN_SHIFT               ((uint32_t)(0U))
#define CSL_CPSW_3G_FLOW_CONTROL_P0_FLOW_EN_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_FLOW_CONTROL_P0_FLOW_EN_MAX                 ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_FLOW_CONTROL_P1_FLOW_EN_MASK                ((uint32_t)(0x00000002U))
#define CSL_CPSW_3G_FLOW_CONTROL_P1_FLOW_EN_SHIFT               ((uint32_t)(1U))
#define CSL_CPSW_3G_FLOW_CONTROL_P1_FLOW_EN_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_FLOW_CONTROL_P1_FLOW_EN_MAX                 ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_FLOW_CONTROL_P2_FLOW_EN_MASK                ((uint32_t)(0x00000004U))
#define CSL_CPSW_3G_FLOW_CONTROL_P2_FLOW_EN_SHIFT               ((uint32_t)(2U))
#define CSL_CPSW_3G_FLOW_CONTROL_P2_FLOW_EN_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_FLOW_CONTROL_P2_FLOW_EN_MAX                 ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_FLOW_CONTROL_RESETVAL                       ((uint32_t)(0x00000000U))

/* VLAN_LTYPE */

#define CSL_CPSW_3G_VLAN_LTYPE_VLAN_LTYPE1_MASK                 ((uint32_t)(0x0000FFFFU))
#define CSL_CPSW_3G_VLAN_LTYPE_VLAN_LTYPE1_SHIFT                ((uint32_t)(0U))
#define CSL_CPSW_3G_VLAN_LTYPE_VLAN_LTYPE1_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_VLAN_LTYPE_VLAN_LTYPE1_MAX                  ((uint32_t)(0x0000ffffU))

#define CSL_CPSW_3G_VLAN_LTYPE_VLAN_LTYPE2_MASK                 ((uint32_t)(0xFFFF0000U))
#define CSL_CPSW_3G_VLAN_LTYPE_VLAN_LTYPE2_SHIFT                ((uint32_t)(16U))
#define CSL_CPSW_3G_VLAN_LTYPE_VLAN_LTYPE2_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_VLAN_LTYPE_VLAN_LTYPE2_MAX                  ((uint32_t)(0x0000ffffU))

#define CSL_CPSW_3G_VLAN_LTYPE_RESETVAL                         ((uint32_t)(0x00000000U))

/* TS_LTYPE */

#define CSL_CPSW_3G_TS_LTYPE_TS_LTYPE1_MASK                     ((uint32_t)(0x0000FFFFU))
#define CSL_CPSW_3G_TS_LTYPE_TS_LTYPE1_SHIFT                    ((uint32_t)(0U))
#define CSL_CPSW_3G_TS_LTYPE_TS_LTYPE1_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TS_LTYPE_TS_LTYPE1_MAX                      ((uint32_t)(0x0000ffffU))

#define CSL_CPSW_3G_TS_LTYPE_TS_LTYPE2_MASK                     ((uint32_t)(0xFFFF0000U))
#define CSL_CPSW_3G_TS_LTYPE_TS_LTYPE2_SHIFT                    ((uint32_t)(16U))
#define CSL_CPSW_3G_TS_LTYPE_TS_LTYPE2_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_TS_LTYPE_TS_LTYPE2_MAX                      ((uint32_t)(0x0000ffffU))

#define CSL_CPSW_3G_TS_LTYPE_RESETVAL                           ((uint32_t)(0x00000000U))

/* DLR_LTYPE */

#define CSL_CPSW_3G_DLR_LTYPE_DLR_LTYPE_MASK                    ((uint32_t)(0x0000FFFFU))
#define CSL_CPSW_3G_DLR_LTYPE_DLR_LTYPE_SHIFT                   ((uint32_t)(0U))
#define CSL_CPSW_3G_DLR_LTYPE_DLR_LTYPE_RESETVAL                ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_DLR_LTYPE_DLR_LTYPE_MAX                     ((uint32_t)(0x0000ffffU))

#define CSL_CPSW_3G_DLR_LTYPE_RESETVAL                          ((uint32_t)(0x00000000U))

/* EEE_PRESCALE */

#define CSL_CPSW_3G_EEE_PRESCALE_EEE_PRESCALE_MASK              ((uint32_t)(0x000003FFU))
#define CSL_CPSW_3G_EEE_PRESCALE_EEE_PRESCALE_SHIFT             ((uint32_t)(0U))
#define CSL_CPSW_3G_EEE_PRESCALE_EEE_PRESCALE_RESETVAL          ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_EEE_PRESCALE_EEE_PRESCALE_MAX               ((uint32_t)(0x000003ffU))

#define CSL_CPSW_3G_EEE_PRESCALE_RESETVAL                       ((uint32_t)(0x00000000U))

/* STATUS */

#define CSL_CPSW_3G_STATUS_EEE_CLKSTOP_ACK_MASK                 ((uint32_t)(0x00000001U))
#define CSL_CPSW_3G_STATUS_EEE_CLKSTOP_ACK_SHIFT                ((uint32_t)(0U))
#define CSL_CPSW_3G_STATUS_EEE_CLKSTOP_ACK_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_STATUS_EEE_CLKSTOP_ACK_MAX                  ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_STATUS_EEE_CLKSTOP_REQ_MASK                 ((uint32_t)(0x00000002U))
#define CSL_CPSW_3G_STATUS_EEE_CLKSTOP_REQ_SHIFT                ((uint32_t)(1U))
#define CSL_CPSW_3G_STATUS_EEE_CLKSTOP_REQ_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_STATUS_EEE_CLKSTOP_REQ_MAX                  ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_STATUS_P0_WAIT_IDLE_MASK                    ((uint32_t)(0x00000010U))
#define CSL_CPSW_3G_STATUS_P0_WAIT_IDLE_SHIFT                   ((uint32_t)(4U))
#define CSL_CPSW_3G_STATUS_P0_WAIT_IDLE_RESETVAL                ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_STATUS_P0_WAIT_IDLE_MAX                     ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_STATUS_P1_TX_WAIT_IDLE_MASK                 ((uint32_t)(0x00000020U))
#define CSL_CPSW_3G_STATUS_P1_TX_WAIT_IDLE_SHIFT                ((uint32_t)(5U))
#define CSL_CPSW_3G_STATUS_P1_TX_WAIT_IDLE_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_STATUS_P1_TX_WAIT_IDLE_MAX                  ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_STATUS_P2_TX_WAIT_IDLE_MASK                 ((uint32_t)(0x00000040U))
#define CSL_CPSW_3G_STATUS_P2_TX_WAIT_IDLE_SHIFT                ((uint32_t)(6U))
#define CSL_CPSW_3G_STATUS_P2_TX_WAIT_IDLE_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_STATUS_P2_TX_WAIT_IDLE_MAX                  ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_STATUS_P0_LPI_MASK                          ((uint32_t)(0x00000100U))
#define CSL_CPSW_3G_STATUS_P0_LPI_SHIFT                         ((uint32_t)(8U))
#define CSL_CPSW_3G_STATUS_P0_LPI_RESETVAL                      ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_STATUS_P0_LPI_MAX                           ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_STATUS_P1_RX_LPI_MASK                       ((uint32_t)(0x00001000U))
#define CSL_CPSW_3G_STATUS_P1_RX_LPI_SHIFT                      ((uint32_t)(12U))
#define CSL_CPSW_3G_STATUS_P1_RX_LPI_RESETVAL                   ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_STATUS_P1_RX_LPI_MAX                        ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_STATUS_P1_TX_LPI_MASK                       ((uint32_t)(0x00002000U))
#define CSL_CPSW_3G_STATUS_P1_TX_LPI_SHIFT                      ((uint32_t)(13U))
#define CSL_CPSW_3G_STATUS_P1_TX_LPI_RESETVAL                   ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_STATUS_P1_TX_LPI_MAX                        ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_STATUS_P2_RX_LPI_MASK                       ((uint32_t)(0x00004000U))
#define CSL_CPSW_3G_STATUS_P2_RX_LPI_SHIFT                      ((uint32_t)(14U))
#define CSL_CPSW_3G_STATUS_P2_RX_LPI_RESETVAL                   ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_STATUS_P2_RX_LPI_MAX                        ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_STATUS_P2_TX_LPI_MASK                       ((uint32_t)(0x00008000U))
#define CSL_CPSW_3G_STATUS_P2_TX_LPI_SHIFT                      ((uint32_t)(15U))
#define CSL_CPSW_3G_STATUS_P2_TX_LPI_RESETVAL                   ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_STATUS_P2_TX_LPI_MAX                        ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_STATUS_P0_TX_WAKE_MASK                      ((uint32_t)(0x00010000U))
#define CSL_CPSW_3G_STATUS_P0_TX_WAKE_SHIFT                     ((uint32_t)(16U))
#define CSL_CPSW_3G_STATUS_P0_TX_WAKE_RESETVAL                  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_STATUS_P0_TX_WAKE_MAX                       ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_STATUS_P1_TX_WAKE_MASK                      ((uint32_t)(0x00020000U))
#define CSL_CPSW_3G_STATUS_P1_TX_WAKE_SHIFT                     ((uint32_t)(17U))
#define CSL_CPSW_3G_STATUS_P1_TX_WAKE_RESETVAL                  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_STATUS_P1_TX_WAKE_MAX                       ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_STATUS_P2_TX_WAKE_MASK                      ((uint32_t)(0x00040000U))
#define CSL_CPSW_3G_STATUS_P2_TX_WAKE_SHIFT                     ((uint32_t)(18U))
#define CSL_CPSW_3G_STATUS_P2_TX_WAKE_RESETVAL                  ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_STATUS_P2_TX_WAKE_MAX                       ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_STATUS_P0_FIFO_EMPTY_MASK                   ((uint32_t)(0x00100000U))
#define CSL_CPSW_3G_STATUS_P0_FIFO_EMPTY_SHIFT                  ((uint32_t)(20U))
#define CSL_CPSW_3G_STATUS_P0_FIFO_EMPTY_RESETVAL               ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_STATUS_P0_FIFO_EMPTY_MAX                    ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_STATUS_P1_FIFO_EMPTY_MASK                   ((uint32_t)(0x00200000U))
#define CSL_CPSW_3G_STATUS_P1_FIFO_EMPTY_SHIFT                  ((uint32_t)(21U))
#define CSL_CPSW_3G_STATUS_P1_FIFO_EMPTY_RESETVAL               ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_STATUS_P1_FIFO_EMPTY_MAX                    ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_STATUS_P2_FIFO_EMPTY_MASK                   ((uint32_t)(0x00400000U))
#define CSL_CPSW_3G_STATUS_P2_FIFO_EMPTY_SHIFT                  ((uint32_t)(22U))
#define CSL_CPSW_3G_STATUS_P2_FIFO_EMPTY_RESETVAL               ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_STATUS_P2_FIFO_EMPTY_MAX                    ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_STATUS_RESETVAL                             ((uint32_t)(0x00000000U))

/* P0_CONTROL */

#define CSL_CPSW_3G_P0_CONTROL_P0_DSCP_PRI_EN_MASK              ((uint32_t)(0x00010000U))
#define CSL_CPSW_3G_P0_CONTROL_P0_DSCP_PRI_EN_SHIFT             ((uint32_t)(16U))
#define CSL_CPSW_3G_P0_CONTROL_P0_DSCP_PRI_EN_RESETVAL          ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_CONTROL_P0_DSCP_PRI_EN_MAX               ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P0_CONTROL_P0_TS_VLAN_LTYPE1_EN_MASK        ((uint32_t)(0x00100000U))
#define CSL_CPSW_3G_P0_CONTROL_P0_TS_VLAN_LTYPE1_EN_SHIFT       ((uint32_t)(20U))
#define CSL_CPSW_3G_P0_CONTROL_P0_TS_VLAN_LTYPE1_EN_RESETVAL    ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_CONTROL_P0_TS_VLAN_LTYPE1_EN_MAX         ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P0_CONTROL_P0_TS_VLAN_LTYPE2_EN_MASK        ((uint32_t)(0x00200000U))
#define CSL_CPSW_3G_P0_CONTROL_P0_TS_VLAN_LTYPE2_EN_SHIFT       ((uint32_t)(21U))
#define CSL_CPSW_3G_P0_CONTROL_P0_TS_VLAN_LTYPE2_EN_RESETVAL    ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_CONTROL_P0_TS_VLAN_LTYPE2_EN_MAX         ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P0_CONTROL_P0_PASS_PRI_TAGGED_MASK          ((uint32_t)(0x01000000U))
#define CSL_CPSW_3G_P0_CONTROL_P0_PASS_PRI_TAGGED_SHIFT         ((uint32_t)(24U))
#define CSL_CPSW_3G_P0_CONTROL_P0_PASS_PRI_TAGGED_RESETVAL      ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_CONTROL_P0_PASS_PRI_TAGGED_MAX           ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P0_CONTROL_P0_DLR_CPDMA_CH_MASK             ((uint32_t)(0x70000000U))
#define CSL_CPSW_3G_P0_CONTROL_P0_DLR_CPDMA_CH_SHIFT            ((uint32_t)(28U))
#define CSL_CPSW_3G_P0_CONTROL_P0_DLR_CPDMA_CH_RESETVAL         ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_CONTROL_P0_DLR_CPDMA_CH_MAX              ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P0_CONTROL_RESETVAL                         ((uint32_t)(0x00000000U))

/* P0_MAX_BLKS */

#define CSL_CPSW_3G_P0_MAX_BLKS_P0_RX_MAX_BLKS_MASK             ((uint32_t)(0x0000000FU))
#define CSL_CPSW_3G_P0_MAX_BLKS_P0_RX_MAX_BLKS_SHIFT            ((uint32_t)(0U))
#define CSL_CPSW_3G_P0_MAX_BLKS_P0_RX_MAX_BLKS_RESETVAL         ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_MAX_BLKS_P0_RX_MAX_BLKS_MAX              ((uint32_t)(0x0000000fU))

#define CSL_CPSW_3G_P0_MAX_BLKS_P0_TX_MAX_BLKS_MASK             ((uint32_t)(0x000001F0U))
#define CSL_CPSW_3G_P0_MAX_BLKS_P0_TX_MAX_BLKS_SHIFT            ((uint32_t)(4U))
#define CSL_CPSW_3G_P0_MAX_BLKS_P0_TX_MAX_BLKS_RESETVAL         ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_MAX_BLKS_P0_TX_MAX_BLKS_MAX              ((uint32_t)(0x0000001fU))

#define CSL_CPSW_3G_P0_MAX_BLKS_RESETVAL                        ((uint32_t)(0x00000000U))

/* P0_BLK_CNT */

#define CSL_CPSW_3G_P0_BLK_CNT_P0_RX_BLK_CNT_MASK               ((uint32_t)(0x0000000FU))
#define CSL_CPSW_3G_P0_BLK_CNT_P0_RX_BLK_CNT_SHIFT              ((uint32_t)(0U))
#define CSL_CPSW_3G_P0_BLK_CNT_P0_RX_BLK_CNT_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_BLK_CNT_P0_RX_BLK_CNT_MAX                ((uint32_t)(0x0000000fU))

#define CSL_CPSW_3G_P0_BLK_CNT_P0_TX_BLK_CNT_MASK               ((uint32_t)(0x000001F0U))
#define CSL_CPSW_3G_P0_BLK_CNT_P0_TX_BLK_CNT_SHIFT              ((uint32_t)(4U))
#define CSL_CPSW_3G_P0_BLK_CNT_P0_TX_BLK_CNT_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_BLK_CNT_P0_TX_BLK_CNT_MAX                ((uint32_t)(0x0000001fU))

#define CSL_CPSW_3G_P0_BLK_CNT_RESETVAL                         ((uint32_t)(0x00000000U))

/* P0_TX_IN_CTL */

#define CSL_CPSW_3G_P0_TX_IN_CTL_TX_PRI_WDS_MASK                ((uint32_t)(0x000003FFU))
#define CSL_CPSW_3G_P0_TX_IN_CTL_TX_PRI_WDS_SHIFT               ((uint32_t)(0U))
#define CSL_CPSW_3G_P0_TX_IN_CTL_TX_PRI_WDS_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_TX_IN_CTL_TX_PRI_WDS_MAX                 ((uint32_t)(0x000003ffU))

#define CSL_CPSW_3G_P0_TX_IN_CTL_TX_BLKS_REM_MASK               ((uint32_t)(0x0000F000U))
#define CSL_CPSW_3G_P0_TX_IN_CTL_TX_BLKS_REM_SHIFT              ((uint32_t)(12U))
#define CSL_CPSW_3G_P0_TX_IN_CTL_TX_BLKS_REM_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_TX_IN_CTL_TX_BLKS_REM_MAX                ((uint32_t)(0x0000000fU))

#define CSL_CPSW_3G_P0_TX_IN_CTL_TX_IN_SEL_MASK                 ((uint32_t)(0x00030000U))
#define CSL_CPSW_3G_P0_TX_IN_CTL_TX_IN_SEL_SHIFT                ((uint32_t)(16U))
#define CSL_CPSW_3G_P0_TX_IN_CTL_TX_IN_SEL_RESETVAL             ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_TX_IN_CTL_TX_IN_SEL_MAX                  ((uint32_t)(0x00000003U))

#define CSL_CPSW_3G_P0_TX_IN_CTL_TX_RATE_EN_MASK                ((uint32_t)(0x00F00000U))
#define CSL_CPSW_3G_P0_TX_IN_CTL_TX_RATE_EN_SHIFT               ((uint32_t)(20U))
#define CSL_CPSW_3G_P0_TX_IN_CTL_TX_RATE_EN_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_TX_IN_CTL_TX_RATE_EN_MAX                 ((uint32_t)(0x0000000fU))

#define CSL_CPSW_3G_P0_TX_IN_CTL_RESETVAL                       ((uint32_t)(0x00000000U))

/* P0_PORT_VLAN */

#define CSL_CPSW_3G_P0_PORT_VLAN_PORT_VID_MASK                  ((uint32_t)(0x00000FFFU))
#define CSL_CPSW_3G_P0_PORT_VLAN_PORT_VID_SHIFT                 ((uint32_t)(0U))
#define CSL_CPSW_3G_P0_PORT_VLAN_PORT_VID_RESETVAL              ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_PORT_VLAN_PORT_VID_MAX                   ((uint32_t)(0x00000fffU))

#define CSL_CPSW_3G_P0_PORT_VLAN_PORT_CFI_MASK                  ((uint32_t)(0x00001000U))
#define CSL_CPSW_3G_P0_PORT_VLAN_PORT_CFI_SHIFT                 ((uint32_t)(12U))
#define CSL_CPSW_3G_P0_PORT_VLAN_PORT_CFI_RESETVAL              ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_PORT_VLAN_PORT_CFI_MAX                   ((uint32_t)(0x00000001U))

#define CSL_CPSW_3G_P0_PORT_VLAN_PORT_PRI_MASK                  ((uint32_t)(0x0000E000U))
#define CSL_CPSW_3G_P0_PORT_VLAN_PORT_PRI_SHIFT                 ((uint32_t)(13U))
#define CSL_CPSW_3G_P0_PORT_VLAN_PORT_PRI_RESETVAL              ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_PORT_VLAN_PORT_PRI_MAX                   ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P0_PORT_VLAN_RESETVAL                       ((uint32_t)(0x00000000U))

/* P0_TX_PRI_MAP */

#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI0_MASK                     ((uint32_t)(0x00000003U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI0_SHIFT                    ((uint32_t)(0U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI0_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI0_MAX                      ((uint32_t)(0x00000003U))

#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI1_MASK                     ((uint32_t)(0x00000030U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI1_SHIFT                    ((uint32_t)(4U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI1_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI1_MAX                      ((uint32_t)(0x00000003U))

#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI2_MASK                     ((uint32_t)(0x00000300U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI2_SHIFT                    ((uint32_t)(8U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI2_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI2_MAX                      ((uint32_t)(0x00000003U))

#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI3_MASK                     ((uint32_t)(0x00003000U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI3_SHIFT                    ((uint32_t)(12U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI3_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI3_MAX                      ((uint32_t)(0x00000003U))

#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI4_MASK                     ((uint32_t)(0x00030000U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI4_SHIFT                    ((uint32_t)(16U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI4_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI4_MAX                      ((uint32_t)(0x00000003U))

#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI5_MASK                     ((uint32_t)(0x00300000U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI5_SHIFT                    ((uint32_t)(20U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI5_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI5_MAX                      ((uint32_t)(0x00000003U))

#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI6_MASK                     ((uint32_t)(0x03000000U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI6_SHIFT                    ((uint32_t)(24U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI6_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI6_MAX                      ((uint32_t)(0x00000003U))

#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI7_MASK                     ((uint32_t)(0x30000000U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI7_SHIFT                    ((uint32_t)(28U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI7_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_TX_PRI_MAP_PRI7_MAX                      ((uint32_t)(0x00000003U))

#define CSL_CPSW_3G_P0_TX_PRI_MAP_RESETVAL                      ((uint32_t)(0x00000000U))

/* CDMA_TX_PRI_MAP */

#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI0_MASK                   ((uint32_t)(0x00000007U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI0_SHIFT                  ((uint32_t)(0U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI0_RESETVAL               ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI0_MAX                    ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI1_MASK                   ((uint32_t)(0x00000070U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI1_SHIFT                  ((uint32_t)(4U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI1_RESETVAL               ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI1_MAX                    ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI2_MASK                   ((uint32_t)(0x00000700U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI2_SHIFT                  ((uint32_t)(8U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI2_RESETVAL               ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI2_MAX                    ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI3_MASK                   ((uint32_t)(0x00007000U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI3_SHIFT                  ((uint32_t)(12U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI3_RESETVAL               ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI3_MAX                    ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI4_MASK                   ((uint32_t)(0x00070000U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI4_SHIFT                  ((uint32_t)(16U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI4_RESETVAL               ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI4_MAX                    ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI5_MASK                   ((uint32_t)(0x00700000U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI5_SHIFT                  ((uint32_t)(20U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI5_RESETVAL               ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI5_MAX                    ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI6_MASK                   ((uint32_t)(0x07000000U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI6_SHIFT                  ((uint32_t)(24U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI6_RESETVAL               ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI6_MAX                    ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI7_MASK                   ((uint32_t)(0x70000000U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI7_SHIFT                  ((uint32_t)(28U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI7_RESETVAL               ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_PRI7_MAX                    ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_CDMA_TX_PRI_MAP_RESETVAL                    ((uint32_t)(0x00000000U))

/* P0_CPDMA_RX_CH_MAP */

#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P1_PRI0_MASK             ((uint32_t)(0x00000007U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P1_PRI0_SHIFT            ((uint32_t)(0U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P1_PRI0_RESETVAL         ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P1_PRI0_MAX              ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P1_PRI1_MASK             ((uint32_t)(0x00000070U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P1_PRI1_SHIFT            ((uint32_t)(4U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P1_PRI1_RESETVAL         ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P1_PRI1_MAX              ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P1_PRI2_MASK             ((uint32_t)(0x00000700U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P1_PRI2_SHIFT            ((uint32_t)(8U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P1_PRI2_RESETVAL         ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P1_PRI2_MAX              ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P1_PRI3_MASK             ((uint32_t)(0x00007000U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P1_PRI3_SHIFT            ((uint32_t)(12U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P1_PRI3_RESETVAL         ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P1_PRI3_MAX              ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P2_PRI0_MASK             ((uint32_t)(0x00070000U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P2_PRI0_SHIFT            ((uint32_t)(16U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P2_PRI0_RESETVAL         ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P2_PRI0_MAX              ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P2_PRI1_MASK             ((uint32_t)(0x00700000U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P2_PRI1_SHIFT            ((uint32_t)(20U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P2_PRI1_RESETVAL         ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P2_PRI1_MAX              ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P2_PRI2_MASK             ((uint32_t)(0x07000000U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P2_PRI2_SHIFT            ((uint32_t)(24U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P2_PRI2_RESETVAL         ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P2_PRI2_MAX              ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P2_PRI3_MASK             ((uint32_t)(0x70000000U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P2_PRI3_SHIFT            ((uint32_t)(28U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P2_PRI3_RESETVAL         ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_P2_PRI3_MAX              ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P0_CPDMA_RX_CH_MAP_RESETVAL                 ((uint32_t)(0x00000000U))

/* P0_RX_DSCP_PRI_MAP */

#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI0_MASK                ((uint32_t)(0x00000007U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI0_SHIFT               ((uint32_t)(0U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI0_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI0_MAX                 ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI1_MASK                ((uint32_t)(0x00000070U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI1_SHIFT               ((uint32_t)(4U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI1_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI1_MAX                 ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI2_MASK                ((uint32_t)(0x00000700U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI2_SHIFT               ((uint32_t)(8U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI2_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI2_MAX                 ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI3_MASK                ((uint32_t)(0x00007000U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI3_SHIFT               ((uint32_t)(12U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI3_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI3_MAX                 ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI4_MASK                ((uint32_t)(0x00070000U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI4_SHIFT               ((uint32_t)(16U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI4_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI4_MAX                 ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI5_MASK                ((uint32_t)(0x00700000U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI5_SHIFT               ((uint32_t)(20U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI5_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI5_MAX                 ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI6_MASK                ((uint32_t)(0x07000000U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI6_SHIFT               ((uint32_t)(24U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI6_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI6_MAX                 ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI7_MASK                ((uint32_t)(0x70000000U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI7_SHIFT               ((uint32_t)(28U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI7_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_PRI7_MAX                 ((uint32_t)(0x00000007U))

#define CSL_CPSW_3G_P0_RX_DSCP_PRI_MAP_RESETVAL                 ((uint32_t)(0x00000000U))

/* P0_IDLE2LPI */

#define CSL_CPSW_3G_P0_IDLE2LPI_P0_IDLE2LPI_MASK                ((uint32_t)(0x000FFFFFU))
#define CSL_CPSW_3G_P0_IDLE2LPI_P0_IDLE2LPI_SHIFT               ((uint32_t)(0U))
#define CSL_CPSW_3G_P0_IDLE2LPI_P0_IDLE2LPI_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_IDLE2LPI_P0_IDLE2LPI_MAX                 ((uint32_t)(0x000fffffU))

#define CSL_CPSW_3G_P0_IDLE2LPI_RESETVAL                        ((uint32_t)(0x00000000U))

/* P0_LPI2WAKE */

#define CSL_CPSW_3G_P0_LPI2WAKE_P0_LPI2WAKE_MASK                ((uint32_t)(0x000FFFFFU))
#define CSL_CPSW_3G_P0_LPI2WAKE_P0_LPI2WAKE_SHIFT               ((uint32_t)(0U))
#define CSL_CPSW_3G_P0_LPI2WAKE_P0_LPI2WAKE_RESETVAL            ((uint32_t)(0x00000000U))
#define CSL_CPSW_3G_P0_LPI2WAKE_P0_LPI2WAKE_MAX                 ((uint32_t)(0x000fffffU))

#define CSL_CPSW_3G_P0_LPI2WAKE_RESETVAL                        ((uint32_t)(0x00000000U))

#ifdef __cplusplus
}
#endif
#endif
