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
#ifndef CSLR_CPSW_SS_H_
#define CSLR_CPSW_SS_H_

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
    volatile Uint32 ID_VER;
    volatile Uint32 CONTROL;
    volatile Uint32 SOFT_RESET;
    volatile Uint32 STAT_PORT_EN;
    volatile Uint32 PTYPE;
    volatile Uint32 SOFT_IDLE;
    volatile Uint8 THRU_RATE;
    volatile Uint8  RSVD0[3];
    volatile Uint32 GAP_THRESH;
    volatile Uint32 TX_START_WDS;
    volatile Uint16 FLOW_CONTROL;
    volatile Uint8  RSVD1[2];
    volatile Uint32 VLAN_LTYPE;
    volatile Uint32 TS_LTYPE;
    volatile Uint16 DLR_LTYPE;
    volatile Uint8  RSVD2[30];
} CSL_Cpsw_SsRegs;


/**************************************************************************
* Register Macros
**************************************************************************/
#define CSL_CPSW_SS_PTYPE                                       (0x10U)
#define CSL_CPSW_SS_VLAN_LTYPE                                  (0x28U)
#define CSL_CPSW_SS_STAT_PORT_EN                                (0xCU)
#define CSL_CPSW_SS_CONTROL                                     (0x4U)
#define CSL_CPSW_SS_SOFT_IDLE                                   (0x14U)
#define CSL_CPSW_SS_ID_VER                                      (0x0U)
#define CSL_CPSW_SS_TX_START_WDS                                (0x20U)
#define CSL_CPSW_SS_SOFT_RESET                                  (0x8U)
#define CSL_CPSW_SS_GAP_THRESH                                  (0x1CU)
#define CSL_CPSW_SS_TS_LTYPE                                    (0x2CU)
#define CSL_CPSW_SS_THRU_RATE                                   (0x18U)
#define CSL_CPSW_SS_DLR_LTYPE                                   (0x30U)
#define CSL_CPSW_SS_FLOW_CONTROL                                (0x24U)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* PTYPE */

#define CSL_CPSW_SS_PTYPE_ESC_PRI_LD_VAL_MASK                   (0x0000001FU)
#define CSL_CPSW_SS_PTYPE_ESC_PRI_LD_VAL_SHIFT                  (0U)
#define CSL_CPSW_SS_PTYPE_ESC_PRI_LD_VAL_RESETVAL               (0x00000000U)
#define CSL_CPSW_SS_PTYPE_ESC_PRI_LD_VAL_MAX                    (0x0000001fU)

#define CSL_CPSW_SS_PTYPE_P0_PTYPE_ESC_MASK                     (0x00000100U)
#define CSL_CPSW_SS_PTYPE_P0_PTYPE_ESC_SHIFT                    (8U)
#define CSL_CPSW_SS_PTYPE_P0_PTYPE_ESC_RESETVAL                 (0x00000000U)
#define CSL_CPSW_SS_PTYPE_P0_PTYPE_ESC_MAX                      (0x00000001U)

#define CSL_CPSW_SS_PTYPE_P1_PTYPE_ESC_MASK                     (0x00000200U)
#define CSL_CPSW_SS_PTYPE_P1_PTYPE_ESC_SHIFT                    (9U)
#define CSL_CPSW_SS_PTYPE_P1_PTYPE_ESC_RESETVAL                 (0x00000000U)
#define CSL_CPSW_SS_PTYPE_P1_PTYPE_ESC_MAX                      (0x00000001U)

#define CSL_CPSW_SS_PTYPE_P2_PTYPE_ESC_MASK                     (0x00000400U)
#define CSL_CPSW_SS_PTYPE_P2_PTYPE_ESC_SHIFT                    (10U)
#define CSL_CPSW_SS_PTYPE_P2_PTYPE_ESC_RESETVAL                 (0x00000000U)
#define CSL_CPSW_SS_PTYPE_P2_PTYPE_ESC_MAX                      (0x00000001U)

#define CSL_CPSW_SS_PTYPE_P1_PRI1_SHAPE_EN_MASK                 (0x00010000U)
#define CSL_CPSW_SS_PTYPE_P1_PRI1_SHAPE_EN_SHIFT                (16U)
#define CSL_CPSW_SS_PTYPE_P1_PRI1_SHAPE_EN_RESETVAL             (0x00000000U)
#define CSL_CPSW_SS_PTYPE_P1_PRI1_SHAPE_EN_MAX                  (0x00000001U)

#define CSL_CPSW_SS_PTYPE_P1_PRI2_SHAPE_EN_MASK                 (0x00020000U)
#define CSL_CPSW_SS_PTYPE_P1_PRI2_SHAPE_EN_SHIFT                (17U)
#define CSL_CPSW_SS_PTYPE_P1_PRI2_SHAPE_EN_RESETVAL             (0x00000000U)
#define CSL_CPSW_SS_PTYPE_P1_PRI2_SHAPE_EN_MAX                  (0x00000001U)

#define CSL_CPSW_SS_PTYPE_P1_PRI3_SHAPE_EN_MASK                 (0x00040000U)
#define CSL_CPSW_SS_PTYPE_P1_PRI3_SHAPE_EN_SHIFT                (18U)
#define CSL_CPSW_SS_PTYPE_P1_PRI3_SHAPE_EN_RESETVAL             (0x00000000U)
#define CSL_CPSW_SS_PTYPE_P1_PRI3_SHAPE_EN_MAX                  (0x00000001U)

#define CSL_CPSW_SS_PTYPE_P2_PRI1_SHAPE_EN_MASK                 (0x00080000U)
#define CSL_CPSW_SS_PTYPE_P2_PRI1_SHAPE_EN_SHIFT                (19U)
#define CSL_CPSW_SS_PTYPE_P2_PRI1_SHAPE_EN_RESETVAL             (0x00000000U)
#define CSL_CPSW_SS_PTYPE_P2_PRI1_SHAPE_EN_MAX                  (0x00000001U)

#define CSL_CPSW_SS_PTYPE_P2_PRI2_SHAPE_EN_MASK                 (0x00100000U)
#define CSL_CPSW_SS_PTYPE_P2_PRI2_SHAPE_EN_SHIFT                (20U)
#define CSL_CPSW_SS_PTYPE_P2_PRI2_SHAPE_EN_RESETVAL             (0x00000000U)
#define CSL_CPSW_SS_PTYPE_P2_PRI2_SHAPE_EN_MAX                  (0x00000001U)

#define CSL_CPSW_SS_PTYPE_P2_PRI3_SHAPE_EN_MASK                 (0x00200000U)
#define CSL_CPSW_SS_PTYPE_P2_PRI3_SHAPE_EN_SHIFT                (21U)
#define CSL_CPSW_SS_PTYPE_P2_PRI3_SHAPE_EN_RESETVAL             (0x00000000U)
#define CSL_CPSW_SS_PTYPE_P2_PRI3_SHAPE_EN_MAX                  (0x00000001U)

#define CSL_CPSW_SS_PTYPE_RESETVAL                              (0x00000000U)

/* VLAN_LTYPE */

#define CSL_CPSW_SS_VLAN_LTYPE_VLAN_LTYPE1_MASK                 (0x0000FFFFU)
#define CSL_CPSW_SS_VLAN_LTYPE_VLAN_LTYPE1_SHIFT                (0U)
#define CSL_CPSW_SS_VLAN_LTYPE_VLAN_LTYPE1_RESETVAL             (0x00008100U)
#define CSL_CPSW_SS_VLAN_LTYPE_VLAN_LTYPE1_MAX                  (0x0000ffffU)

#define CSL_CPSW_SS_VLAN_LTYPE_VLAN_LTYPE2_MASK                 (0xFFFF0000U)
#define CSL_CPSW_SS_VLAN_LTYPE_VLAN_LTYPE2_SHIFT                (16U)
#define CSL_CPSW_SS_VLAN_LTYPE_VLAN_LTYPE2_RESETVAL             (0x00008100U)
#define CSL_CPSW_SS_VLAN_LTYPE_VLAN_LTYPE2_MAX                  (0x0000ffffU)

#define CSL_CPSW_SS_VLAN_LTYPE_RESETVAL                         (0x81008100U)

/* STAT_PORT_EN */

#define CSL_CPSW_SS_STAT_PORT_EN_P0_STAT_EN_MASK                (0x00000001U)
#define CSL_CPSW_SS_STAT_PORT_EN_P0_STAT_EN_SHIFT               (0U)
#define CSL_CPSW_SS_STAT_PORT_EN_P0_STAT_EN_RESETVAL            (0x00000000U)
#define CSL_CPSW_SS_STAT_PORT_EN_P0_STAT_EN_MAX                 (0x00000001U)

#define CSL_CPSW_SS_STAT_PORT_EN_P1_STAT_EN_MASK                (0x00000002U)
#define CSL_CPSW_SS_STAT_PORT_EN_P1_STAT_EN_SHIFT               (1U)
#define CSL_CPSW_SS_STAT_PORT_EN_P1_STAT_EN_RESETVAL            (0x00000000U)
#define CSL_CPSW_SS_STAT_PORT_EN_P1_STAT_EN_MAX                 (0x00000001U)

#define CSL_CPSW_SS_STAT_PORT_EN_P2_STAT_EN_MASK                (0x00000004U)
#define CSL_CPSW_SS_STAT_PORT_EN_P2_STAT_EN_SHIFT               (2U)
#define CSL_CPSW_SS_STAT_PORT_EN_P2_STAT_EN_RESETVAL            (0x00000000U)
#define CSL_CPSW_SS_STAT_PORT_EN_P2_STAT_EN_MAX                 (0x00000001U)

#define CSL_CPSW_SS_STAT_PORT_EN_RESETVAL                       (0x00000000U)

/* CONTROL */

#define CSL_CPSW_SS_CONTROL_FIFO_LOOPBACK_MASK                  (0x00000001U)
#define CSL_CPSW_SS_CONTROL_FIFO_LOOPBACK_SHIFT                 (0U)
#define CSL_CPSW_SS_CONTROL_FIFO_LOOPBACK_RESETVAL              (0x00000000U)
#define CSL_CPSW_SS_CONTROL_FIFO_LOOPBACK_MAX                   (0x00000001U)

#define CSL_CPSW_SS_CONTROL_VLAN_AWARE_MASK                     (0x00000002U)
#define CSL_CPSW_SS_CONTROL_VLAN_AWARE_SHIFT                    (1U)
#define CSL_CPSW_SS_CONTROL_VLAN_AWARE_RESETVAL                 (0x00000000U)
#define CSL_CPSW_SS_CONTROL_VLAN_AWARE_MAX                      (0x00000001U)

#define CSL_CPSW_SS_CONTROL_RX_VLAN_ENCAP_MASK                  (0x00000004U)
#define CSL_CPSW_SS_CONTROL_RX_VLAN_ENCAP_SHIFT                 (2U)
#define CSL_CPSW_SS_CONTROL_RX_VLAN_ENCAP_RESETVAL              (0x00000000U)
#define CSL_CPSW_SS_CONTROL_RX_VLAN_ENCAP_MAX                   (0x00000001U)

#define CSL_CPSW_SS_CONTROL_DLR_EN_MASK                         (0x00000008U)
#define CSL_CPSW_SS_CONTROL_DLR_EN_SHIFT                        (3U)
#define CSL_CPSW_SS_CONTROL_DLR_EN_RESETVAL                     (0x00000000U)
#define CSL_CPSW_SS_CONTROL_DLR_EN_MAX                          (0x00000001U)

#define CSL_CPSW_SS_CONTROL_RESETVAL                            (0x00000000U)

/* SOFT_IDLE */

#define CSL_CPSW_SS_SOFT_IDLE_SOFT_IDLE_MASK                    (0x00000001U)
#define CSL_CPSW_SS_SOFT_IDLE_SOFT_IDLE_SHIFT                   (0U)
#define CSL_CPSW_SS_SOFT_IDLE_SOFT_IDLE_RESETVAL                (0x00000000U)
#define CSL_CPSW_SS_SOFT_IDLE_SOFT_IDLE_MAX                     (0x00000001U)

#define CSL_CPSW_SS_SOFT_IDLE_RESETVAL                          (0x00000000U)

/* ID_VER */

#define CSL_CPSW_SS_ID_VER_CPSW_3G_MINOR_VER_MASK               (0x000000FFU)
#define CSL_CPSW_SS_ID_VER_CPSW_3G_MINOR_VER_SHIFT              (0U)
#define CSL_CPSW_SS_ID_VER_CPSW_3G_MINOR_VER_RESETVAL           (0x00000012U)
#define CSL_CPSW_SS_ID_VER_CPSW_3G_MINOR_VER_MAX                (0x000000ffU)

#define CSL_CPSW_SS_ID_VER_CPSW_3G_MAJ_VER_MASK                 (0x00000700U)
#define CSL_CPSW_SS_ID_VER_CPSW_3G_MAJ_VER_SHIFT                (8U)
#define CSL_CPSW_SS_ID_VER_CPSW_3G_MAJ_VER_RESETVAL             (0x00000001U)
#define CSL_CPSW_SS_ID_VER_CPSW_3G_MAJ_VER_MAX                  (0x00000007U)

#define CSL_CPSW_SS_ID_VER_CPSW_3G_RTL_VER_MASK                 (0x0000F800U)
#define CSL_CPSW_SS_ID_VER_CPSW_3G_RTL_VER_SHIFT                (11U)
#define CSL_CPSW_SS_ID_VER_CPSW_3G_RTL_VER_RESETVAL             (0x00000000U)
#define CSL_CPSW_SS_ID_VER_CPSW_3G_RTL_VER_MAX                  (0x0000001fU)

#define CSL_CPSW_SS_ID_VER_CPSW_3G_IDENT_MASK                   (0xFFFF0000U)
#define CSL_CPSW_SS_ID_VER_CPSW_3G_IDENT_SHIFT                  (16U)
#define CSL_CPSW_SS_ID_VER_CPSW_3G_IDENT_RESETVAL               (0x00000019U)
#define CSL_CPSW_SS_ID_VER_CPSW_3G_IDENT_MAX                    (0x0000ffffU)

#define CSL_CPSW_SS_ID_VER_RESETVAL                             (0x00190112U)

/* TX_START_WDS */

#define CSL_CPSW_SS_TX_START_WDS_TX_START_WDS_MASK              (0x000007FFU)
#define CSL_CPSW_SS_TX_START_WDS_TX_START_WDS_SHIFT             (0U)
#define CSL_CPSW_SS_TX_START_WDS_TX_START_WDS_RESETVAL          (0x00000020U)
#define CSL_CPSW_SS_TX_START_WDS_TX_START_WDS_MAX               (0x000007ffU)

#define CSL_CPSW_SS_TX_START_WDS_RESETVAL                       (0x00000020U)

/* SOFT_RESET */

#define CSL_CPSW_SS_SOFT_RESET_SOFT_RESET_MASK                  (0x00000001U)
#define CSL_CPSW_SS_SOFT_RESET_SOFT_RESET_SHIFT                 (0U)
#define CSL_CPSW_SS_SOFT_RESET_SOFT_RESET_RESETVAL              (0x00000000U)
#define CSL_CPSW_SS_SOFT_RESET_SOFT_RESET_MAX                   (0x00000001U)

#define CSL_CPSW_SS_SOFT_RESET_RESETVAL                         (0x00000000U)

/* GAP_THRESH */

#define CSL_CPSW_SS_GAP_THRESH_GAP_THRESH_MASK                  (0x0000001FU)
#define CSL_CPSW_SS_GAP_THRESH_GAP_THRESH_SHIFT                 (0U)
#define CSL_CPSW_SS_GAP_THRESH_GAP_THRESH_RESETVAL              (0x0000000bU)
#define CSL_CPSW_SS_GAP_THRESH_GAP_THRESH_MAX                   (0x0000001fU)

#define CSL_CPSW_SS_GAP_THRESH_RESETVAL                         (0x0000000bU)

/* TS_LTYPE */

#define CSL_CPSW_SS_TS_LTYPE_TS_LTYPE1_MASK                     (0x0000FFFFU)
#define CSL_CPSW_SS_TS_LTYPE_TS_LTYPE1_SHIFT                    (0U)
#define CSL_CPSW_SS_TS_LTYPE_TS_LTYPE1_RESETVAL                 (0x00000000U)
#define CSL_CPSW_SS_TS_LTYPE_TS_LTYPE1_MAX                      (0x0000ffffU)

#define CSL_CPSW_SS_TS_LTYPE_TS_LTYPE2_MASK                     (0xFFFF0000U)
#define CSL_CPSW_SS_TS_LTYPE_TS_LTYPE2_SHIFT                    (16U)
#define CSL_CPSW_SS_TS_LTYPE_TS_LTYPE2_RESETVAL                 (0x00000000U)
#define CSL_CPSW_SS_TS_LTYPE_TS_LTYPE2_MAX                      (0x0000ffffU)

#define CSL_CPSW_SS_TS_LTYPE_RESETVAL                           (0x00000000U)

/* THRU_RATE */

#define CSL_CPSW_SS_THRU_RATE_CPDMA_THRU_RATE_MASK              (0x0000000FU)
#define CSL_CPSW_SS_THRU_RATE_CPDMA_THRU_RATE_SHIFT             (0U)
#define CSL_CPSW_SS_THRU_RATE_CPDMA_THRU_RATE_RESETVAL          (0x00000003U)
#define CSL_CPSW_SS_THRU_RATE_CPDMA_THRU_RATE_MAX               (0x0000000fU)

#define CSL_CPSW_SS_THRU_RATE_SL_RX_THRU_RATE_MASK              (0x0000F000U)
#define CSL_CPSW_SS_THRU_RATE_SL_RX_THRU_RATE_SHIFT             (12U)
#define CSL_CPSW_SS_THRU_RATE_SL_RX_THRU_RATE_RESETVAL          (0x00000003U)
#define CSL_CPSW_SS_THRU_RATE_SL_RX_THRU_RATE_MAX               (0x0000000fU)

#define CSL_CPSW_SS_THRU_RATE_RESETVAL                          (0x00003003U)

/* DLR_LTYPE */

#define CSL_CPSW_SS_DLR_LTYPE_DLR_LTYPE_MASK                    (0x0000FFFFU)
#define CSL_CPSW_SS_DLR_LTYPE_DLR_LTYPE_SHIFT                   (0U)
#define CSL_CPSW_SS_DLR_LTYPE_DLR_LTYPE_RESETVAL                (0x000080e1U)
#define CSL_CPSW_SS_DLR_LTYPE_DLR_LTYPE_MAX                     (0x0000ffffU)

#define CSL_CPSW_SS_DLR_LTYPE_RESETVAL                          (0x000080e1U)

/* FLOW_CONTROL */

#define CSL_CPSW_SS_FLOW_CONTROL_P0_FLOW_EN_MASK                (0x00000001U)
#define CSL_CPSW_SS_FLOW_CONTROL_P0_FLOW_EN_SHIFT               (0U)
#define CSL_CPSW_SS_FLOW_CONTROL_P0_FLOW_EN_RESETVAL            (0x00000001U)
#define CSL_CPSW_SS_FLOW_CONTROL_P0_FLOW_EN_MAX                 (0x00000001U)

#define CSL_CPSW_SS_FLOW_CONTROL_P1_FLOW_EN_MASK                (0x00000002U)
#define CSL_CPSW_SS_FLOW_CONTROL_P1_FLOW_EN_SHIFT               (1U)
#define CSL_CPSW_SS_FLOW_CONTROL_P1_FLOW_EN_RESETVAL            (0x00000000U)
#define CSL_CPSW_SS_FLOW_CONTROL_P1_FLOW_EN_MAX                 (0x00000001U)

#define CSL_CPSW_SS_FLOW_CONTROL_P2_FLOW_EN_MASK                (0x00000004U)
#define CSL_CPSW_SS_FLOW_CONTROL_P2_FLOW_EN_SHIFT               (2U)
#define CSL_CPSW_SS_FLOW_CONTROL_P2_FLOW_EN_RESETVAL            (0x00000000U)
#define CSL_CPSW_SS_FLOW_CONTROL_P2_FLOW_EN_MAX                 (0x00000001U)

#define CSL_CPSW_SS_FLOW_CONTROL_RESETVAL                       (0x00000001U)

#ifdef __cplusplus
}
#endif
#endif
