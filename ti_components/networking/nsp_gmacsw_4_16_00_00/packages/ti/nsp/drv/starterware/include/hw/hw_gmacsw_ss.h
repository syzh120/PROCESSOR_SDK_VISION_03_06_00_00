/*
 *
 * hw_gmacsw_ss.h - register-level header file for GMAC_SW
 *
 */

/*
 * Copyright (C) 2008-2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _HW_GMACSW_SS_H_
#define _HW_GMACSW_SS_H_

#ifdef __cplusplus
extern "C"
{
#endif


/*!**************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define GMAC_SW_ID_VER                                                                                      (0x00000000u)
#define GMAC_SW_CONTROL                                                                                     (0x00000004u)
#define GMAC_SW_SOFT_RESET                                                                                  (0x00000008u)
#define GMAC_SW_STAT_PORT_EN                                                                                (0x0000000Cu)
#define GMAC_SW_PTYPE                                                                                       (0x00000010u)
#define GMAC_SW_SOFT_IDLE                                                                                   (0x00000014u)
#define GMAC_SW_THRU_RATE                                                                                   (0x00000018u)
#define GMAC_SW_GAP_THRESH                                                                                  (0x0000001Cu)
#define GMAC_SW_TX_START_WDS                                                                                (0x00000020u)
#define GMAC_SW_FLOW_CONTROL                                                                                (0x00000024u)
#define GMAC_SW_VLAN_LTYPE                                                                                  (0x00000028u)
#define GMAC_SW_TS_LTYPE                                                                                    (0x0000002Cu)
#define GMAC_SW_DLR_LTYPE                                                                                   (0x00000030u)


/*!**************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

/*!**************************************** GMAC_SW_ID_VER ******************************************/

#define GMAC_SW_ID_VER_CPSW_3G_MINOR_VER_SHIFT                                                              (0x00000000u)
#define GMAC_SW_ID_VER_CPSW_3G_MINOR_VER_MASK                                                               (0x000000FFu)

#define GMAC_SW_ID_VER_CPSW_3G_MAJ_VER_SHIFT                                                                (0x00000008u)
#define GMAC_SW_ID_VER_CPSW_3G_MAJ_VER_MASK                                                                 (0x00000700u)

#define GMAC_SW_ID_VER_CPSW_3G_RTL_VER_SHIFT                                                                (0x0000000Bu)
#define GMAC_SW_ID_VER_CPSW_3G_RTL_VER_MASK                                                                 (0x0000F800u)

#define GMAC_SW_ID_VER_CPSW_3G_IDENT_SHIFT                                                                  (0x00000010u)
#define GMAC_SW_ID_VER_CPSW_3G_IDENT_MASK                                                                   (0xFFFF0000u)


/*!*************************************** GMAC_SW_CONTROL *****************************************/

#define GMAC_SW_CONTROL_FIFO_LOOPBACK_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_CONTROL_FIFO_LOOPBACK_MASK                                                                  (0x00000001u)

#define GMAC_SW_CONTROL_VLAN_AWARE_SHIFT                                                                    (0x00000001u)
#define GMAC_SW_CONTROL_VLAN_AWARE_MASK                                                                     (0x00000002u)

#define GMAC_SW_CONTROL_RX_VLAN_ENCAP_SHIFT                                                                 (0x00000002u)
#define GMAC_SW_CONTROL_RX_VLAN_ENCAP_MASK                                                                  (0x00000004u)

#define GMAC_SW_CONTROL_DLR_EN_SHIFT                                                                        (0x00000003u)
#define GMAC_SW_CONTROL_DLR_EN_MASK                                                                         (0x00000008u)

#define GMAC_SW_CONTROL_RESERVED_SHIFT                                                                      (0x00000004u)
#define GMAC_SW_CONTROL_RESERVED_MASK                                                                       (0xFFFFFFF0u)


/*!************************************** GMAC_SW_SOFT_RESET ****************************************/

#define GMAC_SW_SOFT_RESET_SOFT_RESET_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_SOFT_RESET_SOFT_RESET_MASK                                                                  (0x00000001u)

#define GMAC_SW_SOFT_RESET_RESERVED_SHIFT                                                                   (0x00000001u)
#define GMAC_SW_SOFT_RESET_RESERVED_MASK                                                                    (0xFFFFFFFEu)


/*!************************************* GMAC_SW_STAT_PORT_EN ***************************************/

#define GMAC_SW_STAT_PORT_EN_P0_STAT_EN_SHIFT                                                               (0x00000000u)
#define GMAC_SW_STAT_PORT_EN_P0_STAT_EN_MASK                                                                (0x00000001u)

#define GMAC_SW_STAT_PORT_EN_P1_STAT_EN_SHIFT                                                               (0x00000001u)
#define GMAC_SW_STAT_PORT_EN_P1_STAT_EN_MASK                                                                (0x00000002u)

#define GMAC_SW_STAT_PORT_EN_P2_STAT_EN_SHIFT                                                               (0x00000002u)
#define GMAC_SW_STAT_PORT_EN_P2_STAT_EN_MASK                                                                (0x00000004u)

#define GMAC_SW_STAT_PORT_EN_RESERVED_SHIFT                                                                 (0x00000003u)
#define GMAC_SW_STAT_PORT_EN_RESERVED_MASK                                                                  (0xFFFFFFF8u)


/*!**************************************** GMAC_SW_PTYPE ******************************************/

#define GMAC_SW_PTYPE_ESC_PRI_LD_VAL_SHIFT                                                                  (0x00000000u)
#define GMAC_SW_PTYPE_ESC_PRI_LD_VAL_MASK                                                                   (0x0000001Fu)

#define GMAC_SW_PTYPE_RESERVED_SHIFT                                                                        (0x00000005u)
#define GMAC_SW_PTYPE_RESERVED_MASK                                                                         (0x000000E0u)

#define GMAC_SW_PTYPE_P0_PTYPE_ESC_SHIFT                                                                    (0x00000008u)
#define GMAC_SW_PTYPE_P0_PTYPE_ESC_MASK                                                                     (0x00000100u)

#define GMAC_SW_PTYPE_P1_PTYPE_ESC_SHIFT                                                                    (0x00000009u)
#define GMAC_SW_PTYPE_P1_PTYPE_ESC_MASK                                                                     (0x00000200u)

#define GMAC_SW_PTYPE_P2_PTYPE_ESC_SHIFT                                                                    (0x0000000Au)
#define GMAC_SW_PTYPE_P2_PTYPE_ESC_MASK                                                                     (0x00000400u)

#define GMAC_SW_PTYPE_RESERVED_2_SHIFT                                                                      (0x0000000Bu)
#define GMAC_SW_PTYPE_RESERVED_2_MASK                                                                       (0x0000F800u)

#define GMAC_SW_PTYPE_P1_PRI1_SHAPE_EN_SHIFT                                                                (0x00000010u)
#define GMAC_SW_PTYPE_P1_PRI1_SHAPE_EN_MASK                                                                 (0x00010000u)

#define GMAC_SW_PTYPE_P1_PRI2_SHAPE_EN_SHIFT                                                                (0x00000011u)
#define GMAC_SW_PTYPE_P1_PRI2_SHAPE_EN_MASK                                                                 (0x00020000u)

#define GMAC_SW_PTYPE_P1_PRI3_SHAPE_EN_SHIFT                                                                (0x00000012u)
#define GMAC_SW_PTYPE_P1_PRI3_SHAPE_EN_MASK                                                                 (0x00040000u)

#define GMAC_SW_PTYPE_P2_PRI1_SHAPE_EN_SHIFT                                                                (0x00000013u)
#define GMAC_SW_PTYPE_P2_PRI1_SHAPE_EN_MASK                                                                 (0x00080000u)

#define GMAC_SW_PTYPE_P2_PRI2_SHAPE_EN_SHIFT                                                                (0x00000014u)
#define GMAC_SW_PTYPE_P2_PRI2_SHAPE_EN_MASK                                                                 (0x00100000u)

#define GMAC_SW_PTYPE_P2_PRI3_SHAPE_EN_SHIFT                                                                (0x00000015u)
#define GMAC_SW_PTYPE_P2_PRI3_SHAPE_EN_MASK                                                                 (0x00200000u)

#define GMAC_SW_PTYPE_RESERVED_3_SHIFT                                                                      (0x00000016u)
#define GMAC_SW_PTYPE_RESERVED_3_MASK                                                                       (0xFFC00000u)


/*!************************************** GMAC_SW_SOFT_IDLE ****************************************/

#define GMAC_SW_SOFT_IDLE_SOFT_IDLE_SHIFT                                                                   (0x00000000u)
#define GMAC_SW_SOFT_IDLE_SOFT_IDLE_MASK                                                                    (0x00000001u)

#define GMAC_SW_SOFT_IDLE_RESERVED_SHIFT                                                                    (0x00000001u)
#define GMAC_SW_SOFT_IDLE_RESERVED_MASK                                                                     (0xFFFFFFFEu)


/*!************************************** GMAC_SW_THRU_RATE ****************************************/

#define GMAC_SW_THRU_RATE_CPDMA_THRU_RATE_SHIFT                                                             (0x00000000u)
#define GMAC_SW_THRU_RATE_CPDMA_THRU_RATE_MASK                                                              (0x0000000Fu)

#define GMAC_SW_THRU_RATE_RESERVED_SHIFT                                                                    (0x00000004u)
#define GMAC_SW_THRU_RATE_RESERVED_MASK                                                                     (0x000000F0u)

#define GMAC_SW_THRU_RATE_SL_RX_THRU_RATE_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_THRU_RATE_SL_RX_THRU_RATE_MASK                                                              (0x0000F000u)


/*!************************************** GMAC_SW_GAP_THRESH ****************************************/

#define GMAC_SW_GAP_THRESH_GAP_THRESH_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_GAP_THRESH_GAP_THRESH_MASK                                                                  (0x0000001Fu)

#define GMAC_SW_GAP_THRESH_RESERVED_SHIFT                                                                   (0x00000005u)
#define GMAC_SW_GAP_THRESH_RESERVED_MASK                                                                    (0xFFFFFFE0u)


/*!************************************* GMAC_SW_TX_START_WDS ***************************************/

#define GMAC_SW_TX_START_WDS_TX_START_WDS_SHIFT                                                             (0x00000000u)
#define GMAC_SW_TX_START_WDS_TX_START_WDS_MASK                                                              (0x000007FFu)

#define GMAC_SW_TX_START_WDS_RESERVED_SHIFT                                                                 (0x0000000Bu)
#define GMAC_SW_TX_START_WDS_RESERVED_MASK                                                                  (0xFFFFF800u)


/*!************************************* GMAC_SW_FLOW_CONTROL ***************************************/

#define GMAC_SW_FLOW_CONTROL_P0_FLOW_EN_SHIFT                                                               (0x00000000u)
#define GMAC_SW_FLOW_CONTROL_P0_FLOW_EN_MASK                                                                (0x00000001u)

#define GMAC_SW_FLOW_CONTROL_P1_FLOW_EN_SHIFT                                                               (0x00000001u)
#define GMAC_SW_FLOW_CONTROL_P1_FLOW_EN_MASK                                                                (0x00000002u)

#define GMAC_SW_FLOW_CONTROL_P2_FLOW_EN_SHIFT                                                               (0x00000002u)
#define GMAC_SW_FLOW_CONTROL_P2_FLOW_EN_MASK                                                                (0x00000004u)

#define GMAC_SW_FLOW_CONTROL_RESERVED_SHIFT                                                                 (0x00000003u)
#define GMAC_SW_FLOW_CONTROL_RESERVED_MASK                                                                  (0x0000FFF8u)


/*!************************************** GMAC_SW_VLAN_LTYPE ****************************************/

#define GMAC_SW_VLAN_LTYPE_VLAN_LTYPE1_SHIFT                                                                (0x00000000u)
#define GMAC_SW_VLAN_LTYPE_VLAN_LTYPE1_MASK                                                                 (0x0000FFFFu)

#define GMAC_SW_VLAN_LTYPE_VLAN_LTYPE2_SHIFT                                                                (0x00000010u)
#define GMAC_SW_VLAN_LTYPE_VLAN_LTYPE2_MASK                                                                 (0xFFFF0000u)


/*!*************************************** GMAC_SW_TS_LTYPE *****************************************/

#define GMAC_SW_TS_LTYPE_TS_LTYPE1_SHIFT                                                                    (0x00000000u)
#define GMAC_SW_TS_LTYPE_TS_LTYPE1_MASK                                                                     (0x0000FFFFu)

#define GMAC_SW_TS_LTYPE_TS_LTYPE2_SHIFT                                                                    (0x00000010u)
#define GMAC_SW_TS_LTYPE_TS_LTYPE2_MASK                                                                     (0xFFFF0000u)


/*!************************************** GMAC_SW_DLR_LTYPE ****************************************/

#define GMAC_SW_DLR_LTYPE_DLR_LTYPE_SHIFT                                                                   (0x00000000u)
#define GMAC_SW_DLR_LTYPE_DLR_LTYPE_MASK                                                                    (0x0000FFFFu)


/*!**************************************************************************************************
* End of File
****************************************************************************************************/
#ifdef __cplusplus
}
#endif

#endif  /* _HW_GMACSW_SS_H_ */
