/*
 *
 * hw_gmacsw_port.h - register-level header file for GMAC_SW
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

#ifndef _HW_GMACSW_PORT_H_
#define _HW_GMACSW_PORT_H_

#ifdef __cplusplus
extern "C"
{
#endif


/*!**************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define GMAC_SW_P0_CONTROL                                                                                  (0x00000000u)
#define GMAC_SW_P0_MAX_BLKS                                                                                 (0x00000008u)
#define GMAC_SW_P0_BLK_CNT                                                                                  (0x0000000Cu)
#define GMAC_SW_P0_TX_IN_CTL                                                                                (0x00000010u)
#define GMAC_SW_P0_PORT_VLAN                                                                                (0x00000014u)
#define GMAC_SW_P0_TX_PRI_MAP                                                                               (0x00000018u)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP                                                                         (0x0000001Cu)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP                                                                          (0x00000020u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0                                                                         (0x00000030u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1                                                                         (0x00000034u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2                                                                         (0x00000038u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3                                                                         (0x0000003Cu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4                                                                         (0x00000040u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5                                                                         (0x00000044u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6                                                                         (0x00000048u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7                                                                         (0x0000004Cu)
#define GMAC_SW_P1_CONTROL                                                                                  (0x00000100u)
#define GMAC_SW_P1_MAX_BLKS                                                                                 (0x00000108u)
#define GMAC_SW_P1_BLK_CNT                                                                                  (0x0000010Cu)
#define GMAC_SW_P1_TX_IN_CTL                                                                                (0x00000110u)
#define GMAC_SW_P1_PORT_VLAN                                                                                (0x00000114u)
#define GMAC_SW_P1_TX_PRI_MAP                                                                               (0x00000118u)
#define GMAC_SW_P1_TS_SEQ_MTYPE                                                                             (0x0000011Cu)
#define GMAC_SW_P1_SA_LO                                                                                    (0x00000120u)
#define GMAC_SW_P1_SA_HI                                                                                    (0x00000124u)
#define GMAC_SW_P1_SEND_PERCENT                                                                             (0x00000128u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0                                                                         (0x00000130u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1                                                                         (0x00000134u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2                                                                         (0x00000138u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3                                                                         (0x0000013Cu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4                                                                         (0x00000140u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5                                                                         (0x00000144u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6                                                                         (0x00000148u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7                                                                         (0x0000014Cu)
#define GMAC_SW_P1_IDLE2LPI                                                                                 (0x00000150u)
#define GMAC_SW_P1_LPI2WAKE                                                                                 (0x00000154u)
#define GMAC_SW_P2_CONTROL                                                                                  (0x00000200u)
#define GMAC_SW_P2_MAX_BLKS                                                                                 (0x00000208u)
#define GMAC_SW_P2_BLK_CNT                                                                                  (0x0000020Cu)
#define GMAC_SW_P2_TX_IN_CTL                                                                                (0x00000210u)
#define GMAC_SW_P2_PORT_VLAN                                                                                (0x00000214u)
#define GMAC_SW_P2_TX_PRI_MAP                                                                               (0x00000218u)
#define GMAC_SW_P2_TS_SEQ_MTYPE                                                                             (0x0000021Cu)
#define GMAC_SW_P2_SA_LO                                                                                    (0x00000220u)
#define GMAC_SW_P2_SA_HI                                                                                    (0x00000224u)
#define GMAC_SW_P2_SEND_PERCENT                                                                             (0x00000228u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0                                                                         (0x00000230u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1                                                                         (0x00000234u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2                                                                         (0x00000238u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3                                                                         (0x0000023Cu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4                                                                         (0x00000240u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5                                                                         (0x00000244u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6                                                                         (0x00000248u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7                                                                         (0x0000024Cu)
#define GMAC_SW_P2_IDLE2LPI                                                                                 (0x00000250u)
#define GMAC_SW_P2_LPI2WAKE                                                                                 (0x00000254u)


/*!**************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

/*!************************************** GMAC_SW_P0_CONTROL ****************************************/

#define GMAC_SW_P0_CONTROL_RESERVED_SHIFT                                                                   (0x00000000u)
#define GMAC_SW_P0_CONTROL_RESERVED_MASK                                                                    (0x0000FFFFu)

#define GMAC_SW_P0_CONTROL_P0_DSCP_PRI_EN_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P0_CONTROL_P0_DSCP_PRI_EN_MASK                                                              (0x00010000u)

#define GMAC_SW_P0_CONTROL_P0_VLAN_LTYPE1_EN_SHIFT                                                          (0x00000014u)
#define GMAC_SW_P0_CONTROL_P0_VLAN_LTYPE1_EN_MASK                                                           (0x00100000u)

#define GMAC_SW_P0_CONTROL_P0_VLAN_LTYPE2_EN_SHIFT                                                          (0x00000015u)
#define GMAC_SW_P0_CONTROL_P0_VLAN_LTYPE2_EN_MASK                                                           (0x00200000u)

#define GMAC_SW_P0_CONTROL_P0_PASS_PRI_TAGGED_SHIFT                                                         (0x00000018u)
#define GMAC_SW_P0_CONTROL_P0_PASS_PRI_TAGGED_MASK                                                          (0x01000000u)

#define GMAC_SW_P0_CONTROL_P0_DLR_CPDMA_CH_SHIFT                                                            (0x0000001Cu)
#define GMAC_SW_P0_CONTROL_P0_DLR_CPDMA_CH_MASK                                                             (0x70000000u)


/*!************************************* GMAC_SW_P0_MAX_BLKS ***************************************/

#define GMAC_SW_P0_MAX_BLKS_P0_RX_MAX_BLKS_SHIFT                                                            (0x00000000u)
#define GMAC_SW_P0_MAX_BLKS_P0_RX_MAX_BLKS_MASK                                                             (0x0000000Fu)

#define GMAC_SW_P0_MAX_BLKS_P0_TX_MAX_BLKS_SHIFT                                                            (0x00000004u)
#define GMAC_SW_P0_MAX_BLKS_P0_TX_MAX_BLKS_MASK                                                             (0x000001F0u)

#define GMAC_SW_P0_MAX_BLKS_RESERVED_SHIFT                                                                  (0x00000009u)
#define GMAC_SW_P0_MAX_BLKS_RESERVED_MASK                                                                   (0x0000FE00u)


/*!************************************** GMAC_SW_P0_BLK_CNT ****************************************/

#define GMAC_SW_P0_BLK_CNT_P0_RX_BLK_CNT_SHIFT                                                              (0x00000000u)
#define GMAC_SW_P0_BLK_CNT_P0_RX_BLK_CNT_MASK                                                               (0x0000000Fu)

#define GMAC_SW_P0_BLK_CNT_P0_TX_BLK_CNT_SHIFT                                                              (0x00000004u)
#define GMAC_SW_P0_BLK_CNT_P0_TX_BLK_CNT_MASK                                                               (0x000001F0u)

#define GMAC_SW_P0_BLK_CNT_RESERVED_SHIFT                                                                   (0x00000009u)
#define GMAC_SW_P0_BLK_CNT_RESERVED_MASK                                                                    (0x0000FE00u)


/*!************************************* GMAC_SW_P0_TX_IN_CTL ***************************************/

#define GMAC_SW_P0_TX_IN_CTL_TX_PRI_WDS_SHIFT                                                               (0x00000000u)
#define GMAC_SW_P0_TX_IN_CTL_TX_PRI_WDS_MASK                                                                (0x000003FFu)

#define GMAC_SW_P0_TX_IN_CTL_RESERVED_SHIFT                                                                 (0x0000000Au)
#define GMAC_SW_P0_TX_IN_CTL_RESERVED_MASK                                                                  (0x00000C00u)

#define GMAC_SW_P0_TX_IN_CTL_TX_BLKS_REM_SHIFT                                                              (0x0000000Cu)
#define GMAC_SW_P0_TX_IN_CTL_TX_BLKS_REM_MASK                                                               (0x0000F000u)

#define GMAC_SW_P0_TX_IN_CTL_TX_IN_SEL_SHIFT                                                                (0x00000010u)
#define GMAC_SW_P0_TX_IN_CTL_TX_IN_SEL_MASK                                                                 (0x00030000u)

#define GMAC_SW_P0_TX_IN_CTL_TX_RATE_EN_SHIFT                                                               (0x00000014u)
#define GMAC_SW_P0_TX_IN_CTL_TX_RATE_EN_MASK                                                                (0x00F00000u)


/*!************************************* GMAC_SW_P0_PORT_VLAN ***************************************/

#define GMAC_SW_P0_PORT_VLAN_PORT_VID_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_P0_PORT_VLAN_PORT_VID_MASK                                                                  (0x00000FFFu)

#define GMAC_SW_P0_PORT_VLAN_PORT_CFI_SHIFT                                                                 (0x0000000Cu)
#define GMAC_SW_P0_PORT_VLAN_PORT_CFI_MASK                                                                  (0x00001000u)

#define GMAC_SW_P0_PORT_VLAN_PORT_PRI_SHIFT                                                                 (0x0000000Du)
#define GMAC_SW_P0_PORT_VLAN_PORT_PRI_MASK                                                                  (0x0000E000u)


/*!************************************ GMAC_SW_P0_TX_PRI_MAP **************************************/

#define GMAC_SW_P0_TX_PRI_MAP_PRI0_SHIFT                                                                    (0x00000000u)
#define GMAC_SW_P0_TX_PRI_MAP_PRI0_MASK                                                                     (0x00000003u)

#define GMAC_SW_P0_TX_PRI_MAP_RESERVED_SHIFT                                                                (0x00000002u)
#define GMAC_SW_P0_TX_PRI_MAP_RESERVED_MASK                                                                 (0x0000000Cu)

#define GMAC_SW_P0_TX_PRI_MAP_PRI1_SHIFT                                                                    (0x00000004u)
#define GMAC_SW_P0_TX_PRI_MAP_PRI1_MASK                                                                     (0x00000030u)

#define GMAC_SW_P0_TX_PRI_MAP_RESERVED_2_SHIFT                                                              (0x00000006u)
#define GMAC_SW_P0_TX_PRI_MAP_RESERVED_2_MASK                                                               (0x000000C0u)

#define GMAC_SW_P0_TX_PRI_MAP_PRI2_SHIFT                                                                    (0x00000008u)
#define GMAC_SW_P0_TX_PRI_MAP_PRI2_MASK                                                                     (0x00000300u)

#define GMAC_SW_P0_TX_PRI_MAP_RESERVED_3_SHIFT                                                              (0x0000000Au)
#define GMAC_SW_P0_TX_PRI_MAP_RESERVED_3_MASK                                                               (0x00000C00u)

#define GMAC_SW_P0_TX_PRI_MAP_PRI3_SHIFT                                                                    (0x0000000Cu)
#define GMAC_SW_P0_TX_PRI_MAP_PRI3_MASK                                                                     (0x00003000u)

#define GMAC_SW_P0_TX_PRI_MAP_RESERVED_4_SHIFT                                                              (0x0000000Eu)
#define GMAC_SW_P0_TX_PRI_MAP_RESERVED_4_MASK                                                               (0x0000C000u)

#define GMAC_SW_P0_TX_PRI_MAP_PRI4_SHIFT                                                                    (0x00000010u)
#define GMAC_SW_P0_TX_PRI_MAP_PRI4_MASK                                                                     (0x00030000u)

#define GMAC_SW_P0_TX_PRI_MAP_PRI5_SHIFT                                                                    (0x00000014u)
#define GMAC_SW_P0_TX_PRI_MAP_PRI5_MASK                                                                     (0x00300000u)

#define GMAC_SW_P0_TX_PRI_MAP_PRI6_SHIFT                                                                    (0x00000018u)
#define GMAC_SW_P0_TX_PRI_MAP_PRI6_MASK                                                                     (0x03000000u)

#define GMAC_SW_P0_TX_PRI_MAP_PRI7_SHIFT                                                                    (0x0000001Cu)
#define GMAC_SW_P0_TX_PRI_MAP_PRI7_MASK                                                                     (0x30000000u)


/*!********************************* GMAC_SW_P0_CPDMA_TX_PRI_MAP ***********************************/

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI0_SHIFT                                                              (0x00000000u)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI0_MASK                                                               (0x00000007u)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI1_SHIFT                                                              (0x00000004u)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI1_MASK                                                               (0x00000070u)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI2_SHIFT                                                              (0x00000008u)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI2_MASK                                                               (0x00000700u)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI3_SHIFT                                                              (0x0000000Cu)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI3_MASK                                                               (0x00007000u)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI4_SHIFT                                                              (0x00000010u)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI4_MASK                                                               (0x00070000u)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI5_SHIFT                                                              (0x00000014u)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI5_MASK                                                               (0x00700000u)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI6_SHIFT                                                              (0x00000018u)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI6_MASK                                                               (0x07000000u)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI7_SHIFT                                                              (0x0000001Cu)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI7_MASK                                                               (0x70000000u)


/*!********************************** GMAC_SW_P0_CPDMA_RX_CH_MAP ************************************/

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P1_PRI0_SHIFT                                                            (0x00000000u)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P1_PRI0_MASK                                                             (0x00000007u)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_RESERVED_SHIFT                                                           (0x00000003u)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_RESERVED_MASK                                                            (0x00000008u)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P1_PRI1_SHIFT                                                            (0x00000004u)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P1_PRI1_MASK                                                             (0x00000070u)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_RESERVED_2_SHIFT                                                         (0x00000007u)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_RESERVED_2_MASK                                                          (0x00000080u)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P1_PRI2_SHIFT                                                            (0x00000008u)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P1_PRI2_MASK                                                             (0x00000700u)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_RESERVED_3_SHIFT                                                         (0x0000000Bu)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_RESERVED_3_MASK                                                          (0x00000800u)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P1_PRI3_SHIFT                                                            (0x0000000Cu)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P1_PRI3_MASK                                                             (0x00007000u)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_RESERVED_4_SHIFT                                                         (0x0000000Fu)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_RESERVED_4_MASK                                                          (0x00008000u)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P2_PRI0_SHIFT                                                            (0x00000010u)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P2_PRI0_MASK                                                             (0x00070000u)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P2_PRI1_SHIFT                                                            (0x00000014u)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P2_PRI1_MASK                                                             (0x00700000u)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P2_PRI2_SHIFT                                                            (0x00000018u)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P2_PRI2_MASK                                                             (0x07000000u)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P2_PRI3_SHIFT                                                            (0x0000001Cu)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P2_PRI3_MASK                                                             (0x70000000u)


/*!********************************* GMAC_SW_P0_RX_DSCP_PRI_MAP0 ***********************************/

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI0_SHIFT                                                              (0x00000000u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI0_MASK                                                               (0x00000007u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI1_SHIFT                                                              (0x00000004u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI1_MASK                                                               (0x00000070u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI2_SHIFT                                                              (0x00000008u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI2_MASK                                                               (0x00000700u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI3_SHIFT                                                              (0x0000000Cu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI3_MASK                                                               (0x00007000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI4_SHIFT                                                              (0x00000010u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI4_MASK                                                               (0x00070000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI5_SHIFT                                                              (0x00000014u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI5_MASK                                                               (0x00700000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI6_SHIFT                                                              (0x00000018u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI6_MASK                                                               (0x07000000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI7_SHIFT                                                              (0x0000001Cu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI7_MASK                                                               (0x70000000u)


/*!********************************* GMAC_SW_P0_RX_DSCP_PRI_MAP1 ***********************************/

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI8_SHIFT                                                              (0x00000000u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI8_MASK                                                               (0x00000007u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI9_SHIFT                                                              (0x00000004u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI9_MASK                                                               (0x00000070u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI10_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI10_MASK                                                              (0x00000700u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI11_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI11_MASK                                                              (0x00007000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI12_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI12_MASK                                                              (0x00070000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI13_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI13_MASK                                                              (0x00700000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI14_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI14_MASK                                                              (0x07000000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI15_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI15_MASK                                                              (0x70000000u)


/*!********************************* GMAC_SW_P0_RX_DSCP_PRI_MAP2 ***********************************/

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI16_SHIFT                                                             (0x00000000u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI16_MASK                                                              (0x00000007u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI17_SHIFT                                                             (0x00000004u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI17_MASK                                                              (0x00000070u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI18_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI18_MASK                                                              (0x00000700u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI19_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI19_MASK                                                              (0x00007000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI20_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI20_MASK                                                              (0x00070000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI21_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI21_MASK                                                              (0x00700000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI22_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI22_MASK                                                              (0x07000000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI23_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI23_MASK                                                              (0x70000000u)


/*!********************************* GMAC_SW_P0_RX_DSCP_PRI_MAP3 ***********************************/

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI24_SHIFT                                                             (0x00000000u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI24_MASK                                                              (0x00000007u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI25_SHIFT                                                             (0x00000004u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI25_MASK                                                              (0x00000070u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI26_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI26_MASK                                                              (0x00000700u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI27_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI27_MASK                                                              (0x00007000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI28_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI28_MASK                                                              (0x00070000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_5_SHIFT                                                        (0x00000013u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_5_MASK                                                         (0x00080000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI29_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI29_MASK                                                              (0x00700000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_6_SHIFT                                                        (0x00000017u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_6_MASK                                                         (0x00800000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI30_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI30_MASK                                                              (0x07000000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_7_SHIFT                                                        (0x0000001Bu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_7_MASK                                                         (0x08000000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI31_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI31_MASK                                                              (0x70000000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_8_SHIFT                                                        (0x0000001Fu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_8_MASK                                                         (0x80000000u)


/*!********************************* GMAC_SW_P0_RX_DSCP_PRI_MAP4 ***********************************/

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI32_SHIFT                                                             (0x00000000u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI32_MASK                                                              (0x00000007u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI33_SHIFT                                                             (0x00000004u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI33_MASK                                                              (0x00000070u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI34_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI34_MASK                                                              (0x00000700u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI35_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI35_MASK                                                              (0x00007000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI36_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI36_MASK                                                              (0x00070000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI37_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI37_MASK                                                              (0x00700000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI38_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI38_MASK                                                              (0x07000000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI39_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI39_MASK                                                              (0x70000000u)


/*!********************************* GMAC_SW_P0_RX_DSCP_PRI_MAP5 ***********************************/

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI40_SHIFT                                                             (0x00000000u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI40_MASK                                                              (0x00000007u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI41_SHIFT                                                             (0x00000004u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI41_MASK                                                              (0x00000070u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI42_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI42_MASK                                                              (0x00000700u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI43_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI43_MASK                                                              (0x00007000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI44_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI44_MASK                                                              (0x00070000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI45_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI45_MASK                                                              (0x00700000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI46_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI46_MASK                                                              (0x07000000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI47_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI47_MASK                                                              (0x70000000u)


/*!********************************* GMAC_SW_P0_RX_DSCP_PRI_MAP6 ***********************************/

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI48_SHIFT                                                             (0x00000000u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI48_MASK                                                              (0x00000007u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI49_SHIFT                                                             (0x00000004u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI49_MASK                                                              (0x00000070u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI50_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI50_MASK                                                              (0x00000700u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI51_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI51_MASK                                                              (0x00007000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI52_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI52_MASK                                                              (0x00070000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI53_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI53_MASK                                                              (0x00700000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI54_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI54_MASK                                                              (0x07000000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI55_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI55_MASK                                                              (0x70000000u)


/*!********************************* GMAC_SW_P0_RX_DSCP_PRI_MAP7 ***********************************/

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI56_SHIFT                                                             (0x00000000u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI56_MASK                                                              (0x00000007u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI57_SHIFT                                                             (0x00000004u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI57_MASK                                                              (0x00000070u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI58_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI58_MASK                                                              (0x00000700u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI59_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI59_MASK                                                              (0x00007000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI60_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI60_MASK                                                              (0x00070000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI61_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI61_MASK                                                              (0x00700000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI62_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI62_MASK                                                              (0x07000000u)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI63_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI63_MASK                                                              (0x70000000u)


/*!************************************** GMAC_SW_P1_CONTROL ****************************************/

#define GMAC_SW_P1_CONTROL_P1_TS_RX_EN_SHIFT                                                                (0x00000000u)
#define GMAC_SW_P1_CONTROL_P1_TS_RX_EN_MASK                                                                 (0x00000001u)

#define GMAC_SW_P1_CONTROL_P1_TS_TX_EN_SHIFT                                                                (0x00000001u)
#define GMAC_SW_P1_CONTROL_P1_TS_TX_EN_MASK                                                                 (0x00000002u)

#define GMAC_SW_P1_CONTROL_P1_TS_LTYPE1_EN_SHIFT                                                            (0x00000002u)
#define GMAC_SW_P1_CONTROL_P1_TS_LTYPE1_EN_MASK                                                             (0x00000004u)

#define GMAC_SW_P1_CONTROL_P1_TS_LTYPE2_EN_SHIFT                                                            (0x00000003u)
#define GMAC_SW_P1_CONTROL_P1_TS_LTYPE2_EN_MASK                                                             (0x00000008u)

#define GMAC_SW_P1_CONTROL_P1_TS_ANNEX_D_EN_SHIFT                                                           (0x00000004u)
#define GMAC_SW_P1_CONTROL_P1_TS_ANNEX_D_EN_MASK                                                            (0x00000010u)

#define GMAC_SW_P1_CONTROL_P1_TS_ANNEX_E_EN_SHIFT                                                           (0x00000005u)
#define GMAC_SW_P1_CONTROL_P1_TS_ANNEX_E_EN_MASK                                                            (0x00000020u)

#define GMAC_SW_P1_CONTROL_P1_TS_ANNEX_F_EN_SHIFT                                                           (0x00000006u)
#define GMAC_SW_P1_CONTROL_P1_TS_ANNEX_F_EN_MASK                                                            (0x00000040u)

#define GMAC_SW_P1_CONTROL_P1_TS_UNI_EN_SHIFT                                                               (0x00000007u)
#define GMAC_SW_P1_CONTROL_P1_TS_UNI_EN_MASK                                                                (0x00000080u)

#define GMAC_SW_P1_CONTROL_P1_TS_TTL_NONZERO_SHIFT                                                          (0x00000008u)
#define GMAC_SW_P1_CONTROL_P1_TS_TTL_NONZERO_MASK                                                           (0x00000100u)

#define GMAC_SW_P1_CONTROL_P1_TS_129_SHIFT                                                                  (0x00000009u)
#define GMAC_SW_P1_CONTROL_P1_TS_129_MASK                                                                   (0x00000200u)

#define GMAC_SW_P1_CONTROL_P1_TS_130_SHIFT                                                                  (0x0000000Au)
#define GMAC_SW_P1_CONTROL_P1_TS_130_MASK                                                                   (0x00000400u)

#define GMAC_SW_P1_CONTROL_P1_TS_131_SHIFT                                                                  (0x0000000Bu)
#define GMAC_SW_P1_CONTROL_P1_TS_131_MASK                                                                   (0x00000800u)

#define GMAC_SW_P1_CONTROL_P1_TS_132_SHIFT                                                                  (0x0000000Cu)
#define GMAC_SW_P1_CONTROL_P1_TS_132_MASK                                                                   (0x00001000u)

#define GMAC_SW_P1_CONTROL_P1_TS_319_SHIFT                                                                  (0x0000000Du)
#define GMAC_SW_P1_CONTROL_P1_TS_319_MASK                                                                   (0x00002000u)

#define GMAC_SW_P1_CONTROL_P1_TS_320_SHIFT                                                                  (0x0000000Eu)
#define GMAC_SW_P1_CONTROL_P1_TS_320_MASK                                                                   (0x00004000u)

#define GMAC_SW_P1_CONTROL_RESERVED_2_SHIFT                                                                 (0x0000000Fu)
#define GMAC_SW_P1_CONTROL_RESERVED_2_MASK                                                                  (0x00008000u)

#define GMAC_SW_P1_CONTROL_P1_DSCP_PRI_EN_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P1_CONTROL_P1_DSCP_PRI_EN_MASK                                                              (0x00010000u)

#define GMAC_SW_P1_CONTROL_P1_VLAN_LTYPE1_EN_SHIFT                                                          (0x00000014u)
#define GMAC_SW_P1_CONTROL_P1_VLAN_LTYPE1_EN_MASK                                                           (0x00100000u)

#define GMAC_SW_P1_CONTROL_P1_VLAN_LTYPE2_EN_SHIFT                                                          (0x00000015u)
#define GMAC_SW_P1_CONTROL_P1_VLAN_LTYPE2_EN_MASK                                                           (0x00200000u)

#define GMAC_SW_P1_CONTROL_P1_PASS_PRI_TAGGED_SHIFT                                                         (0x00000018u)
#define GMAC_SW_P1_CONTROL_P1_PASS_PRI_TAGGED_MASK                                                          (0x01000000u)


/*!************************************* GMAC_SW_P1_MAX_BLKS ***************************************/

#define GMAC_SW_P1_MAX_BLKS_P1_RX_MAX_BLKS_SHIFT                                                            (0x00000000u)
#define GMAC_SW_P1_MAX_BLKS_P1_RX_MAX_BLKS_MASK                                                             (0x0000000Fu)

#define GMAC_SW_P1_MAX_BLKS_P1_TX_MAX_BLKS_SHIFT                                                            (0x00000004u)
#define GMAC_SW_P1_MAX_BLKS_P1_TX_MAX_BLKS_MASK                                                             (0x000001F0u)

#define GMAC_SW_P1_MAX_BLKS_RESERVED_SHIFT                                                                  (0x00000009u)
#define GMAC_SW_P1_MAX_BLKS_RESERVED_MASK                                                                   (0x0000FE00u)


/*!************************************** GMAC_SW_P1_BLK_CNT ****************************************/

#define GMAC_SW_P1_BLK_CNT_P1_RX_BLK_CNT_SHIFT                                                              (0x00000000u)
#define GMAC_SW_P1_BLK_CNT_P1_RX_BLK_CNT_MASK                                                               (0x0000000Fu)

#define GMAC_SW_P1_BLK_CNT_P1_TX_BLK_CNT_SHIFT                                                              (0x00000004u)
#define GMAC_SW_P1_BLK_CNT_P1_TX_BLK_CNT_MASK                                                               (0x000001F0u)

#define GMAC_SW_P1_BLK_CNT_RESERVED_SHIFT                                                                   (0x00000009u)
#define GMAC_SW_P1_BLK_CNT_RESERVED_MASK                                                                    (0x0000FE00u)


/*!************************************* GMAC_SW_P1_TX_IN_CTL ***************************************/

#define GMAC_SW_P1_TX_IN_CTL_TX_PRI_WDS_SHIFT                                                               (0x00000000u)
#define GMAC_SW_P1_TX_IN_CTL_TX_PRI_WDS_MASK                                                                (0x000003FFu)

#define GMAC_SW_P1_TX_IN_CTL_RESERVED_SHIFT                                                                 (0x0000000Au)
#define GMAC_SW_P1_TX_IN_CTL_RESERVED_MASK                                                                  (0x00000C00u)

#define GMAC_SW_P1_TX_IN_CTL_TX_BLKS_REM_SHIFT                                                              (0x0000000Cu)
#define GMAC_SW_P1_TX_IN_CTL_TX_BLKS_REM_MASK                                                               (0x0000F000u)

#define GMAC_SW_P1_TX_IN_CTL_TX_IN_SEL_SHIFT                                                                (0x00000010u)
#define GMAC_SW_P1_TX_IN_CTL_TX_IN_SEL_MASK                                                                 (0x00030000u)

#define GMAC_SW_P1_TX_IN_CTL_TX_RATE_EN_SHIFT                                                               (0x00000014u)
#define GMAC_SW_P1_TX_IN_CTL_TX_RATE_EN_MASK                                                                (0x00F00000u)

#define GMAC_SW_P1_TX_IN_CTL_HOST_BLKS_REM_SHIFT                                                            (0x00000018u)
#define GMAC_SW_P1_TX_IN_CTL_HOST_BLKS_REM_MASK                                                             (0x0F000000u)


/*!************************************* GMAC_SW_P1_PORT_VLAN ***************************************/

#define GMAC_SW_P1_PORT_VLAN_PORT_VID_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_P1_PORT_VLAN_PORT_VID_MASK                                                                  (0x00000FFFu)

#define GMAC_SW_P1_PORT_VLAN_PORT_CFI_SHIFT                                                                 (0x0000000Cu)
#define GMAC_SW_P1_PORT_VLAN_PORT_CFI_MASK                                                                  (0x00001000u)

#define GMAC_SW_P1_PORT_VLAN_PORT_PRI_SHIFT                                                                 (0x0000000Du)
#define GMAC_SW_P1_PORT_VLAN_PORT_PRI_MASK                                                                  (0x0000E000u)


/*!************************************ GMAC_SW_P1_TX_PRI_MAP **************************************/

#define GMAC_SW_P1_TX_PRI_MAP_PRI0_SHIFT                                                                    (0x00000000u)
#define GMAC_SW_P1_TX_PRI_MAP_PRI0_MASK                                                                     (0x00000003u)

#define GMAC_SW_P1_TX_PRI_MAP_RESERVED_SHIFT                                                                (0x00000002u)
#define GMAC_SW_P1_TX_PRI_MAP_RESERVED_MASK                                                                 (0x0000000Cu)

#define GMAC_SW_P1_TX_PRI_MAP_PRI1_SHIFT                                                                    (0x00000004u)
#define GMAC_SW_P1_TX_PRI_MAP_PRI1_MASK                                                                     (0x00000030u)

#define GMAC_SW_P1_TX_PRI_MAP_RESERVED_2_SHIFT                                                              (0x00000006u)
#define GMAC_SW_P1_TX_PRI_MAP_RESERVED_2_MASK                                                               (0x000000C0u)

#define GMAC_SW_P1_TX_PRI_MAP_PRI2_SHIFT                                                                    (0x00000008u)
#define GMAC_SW_P1_TX_PRI_MAP_PRI2_MASK                                                                     (0x00000300u)

#define GMAC_SW_P1_TX_PRI_MAP_RESERVED_3_SHIFT                                                              (0x0000000Au)
#define GMAC_SW_P1_TX_PRI_MAP_RESERVED_3_MASK                                                               (0x00000C00u)

#define GMAC_SW_P1_TX_PRI_MAP_PRI3_SHIFT                                                                    (0x0000000Cu)
#define GMAC_SW_P1_TX_PRI_MAP_PRI3_MASK                                                                     (0x00003000u)

#define GMAC_SW_P1_TX_PRI_MAP_RESERVED_4_SHIFT                                                              (0x0000000Eu)
#define GMAC_SW_P1_TX_PRI_MAP_RESERVED_4_MASK                                                               (0x0000C000u)

#define GMAC_SW_P1_TX_PRI_MAP_PRI4_SHIFT                                                                    (0x00000010u)
#define GMAC_SW_P1_TX_PRI_MAP_PRI4_MASK                                                                     (0x00030000u)

#define GMAC_SW_P1_TX_PRI_MAP_PRI5_SHIFT                                                                    (0x00000014u)
#define GMAC_SW_P1_TX_PRI_MAP_PRI5_MASK                                                                     (0x00300000u)

#define GMAC_SW_P1_TX_PRI_MAP_PRI6_SHIFT                                                                    (0x00000018u)
#define GMAC_SW_P1_TX_PRI_MAP_PRI6_MASK                                                                     (0x03000000u)

#define GMAC_SW_P1_TX_PRI_MAP_PRI7_SHIFT                                                                    (0x0000001Cu)
#define GMAC_SW_P1_TX_PRI_MAP_PRI7_MASK                                                                     (0x30000000u)


/*!*********************************** GMAC_SW_P1_TS_SEQ_MTYPE *************************************/

#define GMAC_SW_P1_TS_SEQ_MTYPE_P1_TS_MSG_TYPE_EN_SHIFT                                                     (0x00000000u)
#define GMAC_SW_P1_TS_SEQ_MTYPE_P1_TS_MSG_TYPE_EN_MASK                                                      (0x0000FFFFu)

#define GMAC_SW_P1_TS_SEQ_MTYPE_P1_TS_SEQ_ID_OFFSET_SHIFT                                                   (0x00000010u)
#define GMAC_SW_P1_TS_SEQ_MTYPE_P1_TS_SEQ_ID_OFFSET_MASK                                                    (0x003F0000u)


/*!*************************************** GMAC_SW_P1_SA_LO *****************************************/

#define GMAC_SW_P1_SA_LO_MACSRCADDR_15_8_SHIFT                                                              (0x00000000u)
#define GMAC_SW_P1_SA_LO_MACSRCADDR_15_8_MASK                                                               (0x000000FFu)

#define GMAC_SW_P1_SA_LO_MACSRCADDR_7_0_SHIFT                                                               (0x00000008u)
#define GMAC_SW_P1_SA_LO_MACSRCADDR_7_0_MASK                                                                (0x0000FF00u)


/*!*************************************** GMAC_SW_P1_SA_HI *****************************************/

#define GMAC_SW_P1_SA_HI_MACSRCADDR_47_40_SHIFT                                                             (0x00000000u)
#define GMAC_SW_P1_SA_HI_MACSRCADDR_47_40_MASK                                                              (0x000000FFu)

#define GMAC_SW_P1_SA_HI_MACSRCADDR_39_32_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P1_SA_HI_MACSRCADDR_39_32_MASK                                                              (0x0000FF00u)

#define GMAC_SW_P1_SA_HI_MACSRCADDR_31_24_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P1_SA_HI_MACSRCADDR_31_24_MASK                                                              (0x00FF0000u)

#define GMAC_SW_P1_SA_HI_MACSRCADDR_23_16_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P1_SA_HI_MACSRCADDR_23_16_MASK                                                              (0xFF000000u)


/*!*********************************** GMAC_SW_P1_SEND_PERCENT *************************************/

#define GMAC_SW_P1_SEND_PERCENT_PRI1_SEND_PERCENT_SHIFT                                                     (0x00000000u)
#define GMAC_SW_P1_SEND_PERCENT_PRI1_SEND_PERCENT_MASK                                                      (0x0000007Fu)

#define GMAC_SW_P1_SEND_PERCENT_RESERVED_SHIFT                                                              (0x00000007u)
#define GMAC_SW_P1_SEND_PERCENT_RESERVED_MASK                                                               (0x00000080u)

#define GMAC_SW_P1_SEND_PERCENT_PRI2_SEND_PERCENT_SHIFT                                                     (0x00000008u)
#define GMAC_SW_P1_SEND_PERCENT_PRI2_SEND_PERCENT_MASK                                                      (0x00007F00u)

#define GMAC_SW_P1_SEND_PERCENT_RESERVED_2_SHIFT                                                            (0x0000000Fu)
#define GMAC_SW_P1_SEND_PERCENT_RESERVED_2_MASK                                                             (0x00008000u)

#define GMAC_SW_P1_SEND_PERCENT_PRI3_SEND_PERCENT_SHIFT                                                     (0x00000010u)
#define GMAC_SW_P1_SEND_PERCENT_PRI3_SEND_PERCENT_MASK                                                      (0x007F0000u)


/*!********************************* GMAC_SW_P1_RX_DSCP_PRI_MAP0 ***********************************/

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI0_SHIFT                                                              (0x00000000u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI0_MASK                                                               (0x00000007u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI1_SHIFT                                                              (0x00000004u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI1_MASK                                                               (0x00000070u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI2_SHIFT                                                              (0x00000008u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI2_MASK                                                               (0x00000700u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI3_SHIFT                                                              (0x0000000Cu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI3_MASK                                                               (0x00007000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI4_SHIFT                                                              (0x00000010u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI4_MASK                                                               (0x00070000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_5_SHIFT                                                        (0x00000013u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_5_MASK                                                         (0x00080000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI5_SHIFT                                                              (0x00000014u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI5_MASK                                                               (0x00700000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_6_SHIFT                                                        (0x00000017u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_6_MASK                                                         (0x00800000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI6_SHIFT                                                              (0x00000018u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI6_MASK                                                               (0x07000000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_7_SHIFT                                                        (0x0000001Bu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_7_MASK                                                         (0x08000000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI7_SHIFT                                                              (0x0000001Cu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI7_MASK                                                               (0x70000000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_8_SHIFT                                                        (0x0000001Fu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_8_MASK                                                         (0x80000000u)


/*!********************************* GMAC_SW_P1_RX_DSCP_PRI_MAP1 ***********************************/

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI8_SHIFT                                                              (0x00000000u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI8_MASK                                                               (0x00000007u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI9_SHIFT                                                              (0x00000004u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI9_MASK                                                               (0x00000070u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI10_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI10_MASK                                                              (0x00000700u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI11_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI11_MASK                                                              (0x00007000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI12_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI12_MASK                                                              (0x00070000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI13_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI13_MASK                                                              (0x00700000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI14_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI14_MASK                                                              (0x07000000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI15_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI15_MASK                                                              (0x70000000u)


/*!********************************* GMAC_SW_P1_RX_DSCP_PRI_MAP2 ***********************************/

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI16_SHIFT                                                             (0x00000000u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI16_MASK                                                              (0x00000007u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI17_SHIFT                                                             (0x00000004u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI17_MASK                                                              (0x00000070u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI18_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI18_MASK                                                              (0x00000700u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI19_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI19_MASK                                                              (0x00007000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI20_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI20_MASK                                                              (0x00070000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI21_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI21_MASK                                                              (0x00700000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI22_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI22_MASK                                                              (0x07000000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI23_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI23_MASK                                                              (0x70000000u)


/*!********************************* GMAC_SW_P1_RX_DSCP_PRI_MAP3 ***********************************/

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI24_SHIFT                                                             (0x00000000u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI24_MASK                                                              (0x00000007u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI25_SHIFT                                                             (0x00000004u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI25_MASK                                                              (0x00000070u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI26_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI26_MASK                                                              (0x00000700u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI27_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI27_MASK                                                              (0x00007000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI28_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI28_MASK                                                              (0x00070000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI29_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI29_MASK                                                              (0x00700000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI30_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI30_MASK                                                              (0x07000000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI31_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI31_MASK                                                              (0x70000000u)


/*!********************************* GMAC_SW_P1_RX_DSCP_PRI_MAP4 ***********************************/

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI32_SHIFT                                                             (0x00000000u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI32_MASK                                                              (0x00000007u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI33_SHIFT                                                             (0x00000004u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI33_MASK                                                              (0x00000070u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI34_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI34_MASK                                                              (0x00000700u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI35_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI35_MASK                                                              (0x00007000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI36_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI36_MASK                                                              (0x00070000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI37_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI37_MASK                                                              (0x00700000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI38_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI38_MASK                                                              (0x07000000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI39_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI39_MASK                                                              (0x70000000u)


/*!********************************* GMAC_SW_P1_RX_DSCP_PRI_MAP5 ***********************************/

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI40_SHIFT                                                             (0x00000000u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI40_MASK                                                              (0x00000007u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI41_SHIFT                                                             (0x00000004u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI41_MASK                                                              (0x00000070u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI42_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI42_MASK                                                              (0x00000700u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI43_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI43_MASK                                                              (0x00007000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI44_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI44_MASK                                                              (0x00070000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI45_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI45_MASK                                                              (0x00700000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI46_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI46_MASK                                                              (0x07000000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI47_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI47_MASK                                                              (0x70000000u)


/*!********************************* GMAC_SW_P1_RX_DSCP_PRI_MAP6 ***********************************/

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI48_SHIFT                                                             (0x00000000u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI48_MASK                                                              (0x00000007u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI49_SHIFT                                                             (0x00000004u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI49_MASK                                                              (0x00000070u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI50_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI50_MASK                                                              (0x00000700u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI51_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI51_MASK                                                              (0x00007000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI52_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI52_MASK                                                              (0x00070000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI53_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI53_MASK                                                              (0x00700000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI54_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI54_MASK                                                              (0x07000000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI55_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI55_MASK                                                              (0x70000000u)


/*!********************************* GMAC_SW_P1_RX_DSCP_PRI_MAP7 ***********************************/

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI56_SHIFT                                                             (0x00000000u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI56_MASK                                                              (0x00000007u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI57_SHIFT                                                             (0x00000004u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI57_MASK                                                              (0x00000070u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI58_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI58_MASK                                                              (0x00000700u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI59_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI59_MASK                                                              (0x00007000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI60_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI60_MASK                                                              (0x00070000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI61_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI61_MASK                                                              (0x00700000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI62_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI62_MASK                                                              (0x07000000u)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI63_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI63_MASK                                                              (0x70000000u)


/*!************************************** GMAC_SW_P2_CONTROL ****************************************/

#define GMAC_SW_P2_CONTROL_P2_TS_RX_EN_SHIFT                                                                (0x00000000u)
#define GMAC_SW_P2_CONTROL_P2_TS_RX_EN_MASK                                                                 (0x00000001u)

#define GMAC_SW_P2_CONTROL_P2_TS_TX_EN_SHIFT                                                                (0x00000001u)
#define GMAC_SW_P2_CONTROL_P2_TS_TX_EN_MASK                                                                 (0x00000002u)

#define GMAC_SW_P2_CONTROL_P2_TS_LTYPE1_EN_SHIFT                                                            (0x00000002u)
#define GMAC_SW_P2_CONTROL_P2_TS_LTYPE1_EN_MASK                                                             (0x00000004u)

#define GMAC_SW_P2_CONTROL_P2_TS_LTYPE2_EN_SHIFT                                                            (0x00000003u)
#define GMAC_SW_P2_CONTROL_P2_TS_LTYPE2_EN_MASK                                                             (0x00000008u)

#define GMAC_SW_P2_CONTROL_P2_TS_ANNEX_D_EN_SHIFT                                                           (0x00000004u)
#define GMAC_SW_P2_CONTROL_P2_TS_ANNEX_D_EN_MASK                                                            (0x00000010u)

#define GMAC_SW_P1_CONTROL_P2_TS_ANNEX_E_EN_SHIFT                                                           (0x00000005u)
#define GMAC_SW_P1_CONTROL_P2_TS_ANNEX_E_EN_MASK                                                            (0x00000020u)

#define GMAC_SW_P1_CONTROL_P2_TS_ANNEX_F_EN_SHIFT                                                           (0x00000006u)
#define GMAC_SW_P1_CONTROL_P2_TS_ANNEX_F_EN_MASK                                                            (0x00000040u)

#define GMAC_SW_P1_CONTROL_P2_TS_UNI_EN_SHIFT                                                               (0x00000007u)
#define GMAC_SW_P1_CONTROL_P2_TS_UNI_EN_MASK                                                                (0x00000080u)

#define GMAC_SW_P2_CONTROL_P2_TS_TTL_NONZERO_SHIFT                                                          (0x00000008u)
#define GMAC_SW_P2_CONTROL_P2_TS_TTL_NONZERO_MASK                                                           (0x00000100u)

#define GMAC_SW_P2_CONTROL_P2_TS_129_SHIFT                                                                  (0x00000009u)
#define GMAC_SW_P2_CONTROL_P2_TS_129_MASK                                                                   (0x00000200u)

#define GMAC_SW_P2_CONTROL_P2_TS_130_SHIFT                                                                  (0x0000000Au)
#define GMAC_SW_P2_CONTROL_P2_TS_130_MASK                                                                   (0x00000400u)

#define GMAC_SW_P2_CONTROL_P2_TS_131_SHIFT                                                                  (0x0000000Bu)
#define GMAC_SW_P2_CONTROL_P2_TS_131_MASK                                                                   (0x00000800u)

#define GMAC_SW_P2_CONTROL_P2_TS_132_SHIFT                                                                  (0x0000000Cu)
#define GMAC_SW_P2_CONTROL_P2_TS_132_MASK                                                                   (0x00001000u)

#define GMAC_SW_P2_CONTROL_P2_TS_319_SHIFT                                                                  (0x0000000Du)
#define GMAC_SW_P2_CONTROL_P2_TS_319_MASK                                                                   (0x00002000u)

#define GMAC_SW_P2_CONTROL_P2_TS_320_SHIFT                                                                  (0x0000000Eu)
#define GMAC_SW_P2_CONTROL_P2_TS_320_MASK                                                                   (0x00004000u)

#define GMAC_SW_P2_CONTROL_RESERVED_2_SHIFT                                                                 (0x0000000Fu)
#define GMAC_SW_P2_CONTROL_RESERVED_2_MASK                                                                  (0x00008000u)

#define GMAC_SW_P2_CONTROL_P2_DSCP_PRI_EN_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P2_CONTROL_P2_DSCP_PRI_EN_MASK                                                              (0x00010000u)

#define GMAC_SW_P2_CONTROL_P2_VLAN_LTYPE1_EN_SHIFT                                                          (0x00000014u)
#define GMAC_SW_P2_CONTROL_P2_VLAN_LTYPE1_EN_MASK                                                           (0x00100000u)

#define GMAC_SW_P2_CONTROL_P2_VLAN_LTYPE2_EN_SHIFT                                                          (0x00000015u)
#define GMAC_SW_P2_CONTROL_P2_VLAN_LTYPE2_EN_MASK                                                           (0x00200000u)

#define GMAC_SW_P2_CONTROL_P2_PASS_PRI_TAGGED_SHIFT                                                         (0x00000018u)
#define GMAC_SW_P2_CONTROL_P2_PASS_PRI_TAGGED_MASK                                                          (0x01000000u)


/*!************************************* GMAC_SW_P2_MAX_BLKS ***************************************/

#define GMAC_SW_P2_MAX_BLKS_P2_RX_MAX_BLKS_SHIFT                                                            (0x00000000u)
#define GMAC_SW_P2_MAX_BLKS_P2_RX_MAX_BLKS_MASK                                                             (0x0000000Fu)

#define GMAC_SW_P2_MAX_BLKS_P2_TX_MAX_BLKS_SHIFT                                                            (0x00000004u)
#define GMAC_SW_P2_MAX_BLKS_P2_TX_MAX_BLKS_MASK                                                             (0x000001F0u)

#define GMAC_SW_P2_MAX_BLKS_RESERVED_SHIFT                                                                  (0x00000009u)
#define GMAC_SW_P2_MAX_BLKS_RESERVED_MASK                                                                   (0xFFFFFE00u)


/*!************************************** GMAC_SW_P2_BLK_CNT ****************************************/

#define GMAC_SW_P2_BLK_CNT_P2_RX_BLK_CNT_SHIFT                                                              (0x00000000u)
#define GMAC_SW_P2_BLK_CNT_P2_RX_BLK_CNT_MASK                                                               (0x0000000Fu)

#define GMAC_SW_P2_BLK_CNT_P2_TX_BLK_CNT_SHIFT                                                              (0x00000004u)
#define GMAC_SW_P2_BLK_CNT_P2_TX_BLK_CNT_MASK                                                               (0x000001F0u)

#define GMAC_SW_P2_BLK_CNT_RESERVED_SHIFT                                                                   (0x00000009u)
#define GMAC_SW_P2_BLK_CNT_RESERVED_MASK                                                                    (0xFFFFFE00u)


/*!************************************* GMAC_SW_P2_TX_IN_CTL ***************************************/

#define GMAC_SW_P2_TX_IN_CTL_TX_PRI_WDS_SHIFT                                                               (0x00000000u)
#define GMAC_SW_P2_TX_IN_CTL_TX_PRI_WDS_MASK                                                                (0x000003FFu)

#define GMAC_SW_P2_TX_IN_CTL_RESERVED_SHIFT                                                                 (0x0000000Au)
#define GMAC_SW_P2_TX_IN_CTL_RESERVED_MASK                                                                  (0x00000C00u)

#define GMAC_SW_P2_TX_IN_CTL_TX_BLKS_REM_SHIFT                                                              (0x0000000Cu)
#define GMAC_SW_P2_TX_IN_CTL_TX_BLKS_REM_MASK                                                               (0x0000F000u)

#define GMAC_SW_P2_TX_IN_CTL_TX_IN_SEL_SHIFT                                                                (0x00000010u)
#define GMAC_SW_P2_TX_IN_CTL_TX_IN_SEL_MASK                                                                 (0x00030000u)

#define GMAC_SW_P2_TX_IN_CTL_RESERVED_2_SHIFT                                                               (0x00000012u)
#define GMAC_SW_P2_TX_IN_CTL_RESERVED_2_MASK                                                                (0x000C0000u)

#define GMAC_SW_P2_TX_IN_CTL_TX_RATE_EN_SHIFT                                                               (0x00000014u)
#define GMAC_SW_P2_TX_IN_CTL_TX_RATE_EN_MASK                                                                (0x00F00000u)

#define GMAC_SW_P2_TX_IN_CTL_HOST_BLKS_REM_SHIFT                                                            (0x00000018u)
#define GMAC_SW_P2_TX_IN_CTL_HOST_BLKS_REM_MASK                                                             (0x0F000000u)

#define GMAC_SW_P2_TX_IN_CTL_RESERVED_3_SHIFT                                                               (0x0000001Cu)
#define GMAC_SW_P2_TX_IN_CTL_RESERVED_3_MASK                                                                (0xF0000000u)


/*!************************************* GMAC_SW_P2_PORT_VLAN ***************************************/

#define GMAC_SW_P2_PORT_VLAN_PORT_VID_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_P2_PORT_VLAN_PORT_VID_MASK                                                                  (0x00000FFFu)

#define GMAC_SW_P2_PORT_VLAN_PORT_CFI_SHIFT                                                                 (0x0000000Cu)
#define GMAC_SW_P2_PORT_VLAN_PORT_CFI_MASK                                                                  (0x00001000u)

#define GMAC_SW_P2_PORT_VLAN_PORT_PRI_SHIFT                                                                 (0x0000000Du)
#define GMAC_SW_P2_PORT_VLAN_PORT_PRI_MASK                                                                  (0x0000E000u)


/*!************************************ GMAC_SW_P2_TX_PRI_MAP **************************************/

#define GMAC_SW_P2_TX_PRI_MAP_PRI0_SHIFT                                                                    (0x00000000u)
#define GMAC_SW_P2_TX_PRI_MAP_PRI0_MASK                                                                     (0x00000003u)

#define GMAC_SW_P2_TX_PRI_MAP_RESERVED_SHIFT                                                                (0x00000002u)
#define GMAC_SW_P2_TX_PRI_MAP_RESERVED_MASK                                                                 (0x0000000Cu)

#define GMAC_SW_P2_TX_PRI_MAP_PRI1_SHIFT                                                                    (0x00000004u)
#define GMAC_SW_P2_TX_PRI_MAP_PRI1_MASK                                                                     (0x00000030u)

#define GMAC_SW_P2_TX_PRI_MAP_RESERVED_2_SHIFT                                                              (0x00000006u)
#define GMAC_SW_P2_TX_PRI_MAP_RESERVED_2_MASK                                                               (0x000000C0u)

#define GMAC_SW_P2_TX_PRI_MAP_PRI2_SHIFT                                                                    (0x00000008u)
#define GMAC_SW_P2_TX_PRI_MAP_PRI2_MASK                                                                     (0x00000300u)

#define GMAC_SW_P2_TX_PRI_MAP_RESERVED_3_SHIFT                                                              (0x0000000Au)
#define GMAC_SW_P2_TX_PRI_MAP_RESERVED_3_MASK                                                               (0x00000C00u)

#define GMAC_SW_P2_TX_PRI_MAP_PRI3_SHIFT                                                                    (0x0000000Cu)
#define GMAC_SW_P2_TX_PRI_MAP_PRI3_MASK                                                                     (0x00003000u)

#define GMAC_SW_P2_TX_PRI_MAP_RESERVED_4_SHIFT                                                              (0x0000000Eu)
#define GMAC_SW_P2_TX_PRI_MAP_RESERVED_4_MASK                                                               (0x0000C000u)

#define GMAC_SW_P2_TX_PRI_MAP_PRI4_SHIFT                                                                    (0x00000010u)
#define GMAC_SW_P2_TX_PRI_MAP_PRI4_MASK                                                                     (0x00030000u)

#define GMAC_SW_P2_TX_PRI_MAP_PRI5_SHIFT                                                                    (0x00000014u)
#define GMAC_SW_P2_TX_PRI_MAP_PRI5_MASK                                                                     (0x00300000u)

#define GMAC_SW_P2_TX_PRI_MAP_PRI6_SHIFT                                                                    (0x00000018u)
#define GMAC_SW_P2_TX_PRI_MAP_PRI6_MASK                                                                     (0x03000000u)

#define GMAC_SW_P2_TX_PRI_MAP_PRI7_SHIFT                                                                    (0x0000001Cu)
#define GMAC_SW_P2_TX_PRI_MAP_PRI7_MASK                                                                     (0x30000000u)


/*!*********************************** GMAC_SW_P2_TS_SEQ_MTYPE *************************************/

#define GMAC_SW_P2_TS_SEQ_MTYPE_P2_TS_MSG_TYPE_EN_SHIFT                                                     (0x00000000u)
#define GMAC_SW_P2_TS_SEQ_MTYPE_P2_TS_MSG_TYPE_EN_MASK                                                      (0x0000FFFFu)

#define GMAC_SW_P2_TS_SEQ_MTYPE_P2_TS_SEQ_ID_OFFSET_SHIFT                                                   (0x00000010u)
#define GMAC_SW_P2_TS_SEQ_MTYPE_P2_TS_SEQ_ID_OFFSET_MASK                                                    (0x003F0000u)


/*!*************************************** GMAC_SW_P2_SA_LO *****************************************/

#define GMAC_SW_P2_SA_LO_MACSRCADDR_15_8_SHIFT                                                              (0x00000000u)
#define GMAC_SW_P2_SA_LO_MACSRCADDR_15_8_MASK                                                               (0x000000FFu)

#define GMAC_SW_P2_SA_LO_MACSRCADDR_7_0_SHIFT                                                               (0x00000008u)
#define GMAC_SW_P2_SA_LO_MACSRCADDR_7_0_MASK                                                                (0x0000FF00u)


/*!*************************************** GMAC_SW_P2_SA_HI *****************************************/

#define GMAC_SW_P2_SA_HI_MACSRCADDR_47_40_SHIFT                                                             (0x00000000u)
#define GMAC_SW_P2_SA_HI_MACSRCADDR_47_40_MASK                                                              (0x000000FFu)

#define GMAC_SW_P2_SA_HI_MACSRCADDR_39_32_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P2_SA_HI_MACSRCADDR_39_32_MASK                                                              (0x0000FF00u)

#define GMAC_SW_P2_SA_HI_MACSRCADDR_31_24_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P2_SA_HI_MACSRCADDR_31_24_MASK                                                              (0x00FF0000u)

#define GMAC_SW_P2_SA_HI_MACSRCADDR_23_16_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P2_SA_HI_MACSRCADDR_23_16_MASK                                                              (0xFF000000u)


/*!*********************************** GMAC_SW_P2_SEND_PERCENT *************************************/

#define GMAC_SW_P2_SEND_PERCENT_PRI1_SEND_PERCENT_SHIFT                                                     (0x00000000u)
#define GMAC_SW_P2_SEND_PERCENT_PRI1_SEND_PERCENT_MASK                                                      (0x0000007Fu)

#define GMAC_SW_P2_SEND_PERCENT_RESERVED_SHIFT                                                              (0x00000007u)
#define GMAC_SW_P2_SEND_PERCENT_RESERVED_MASK                                                               (0x00000080u)

#define GMAC_SW_P2_SEND_PERCENT_PRI2_SEND_PERCENT_SHIFT                                                     (0x00000008u)
#define GMAC_SW_P2_SEND_PERCENT_PRI2_SEND_PERCENT_MASK                                                      (0x00007F00u)

#define GMAC_SW_P2_SEND_PERCENT_RESERVED_2_SHIFT                                                            (0x0000000Fu)
#define GMAC_SW_P2_SEND_PERCENT_RESERVED_2_MASK                                                             (0x00008000u)

#define GMAC_SW_P2_SEND_PERCENT_PRI3_SEND_PERCENT_SHIFT                                                     (0x00000010u)
#define GMAC_SW_P2_SEND_PERCENT_PRI3_SEND_PERCENT_MASK                                                      (0x007F0000u)


/*!********************************* GMAC_SW_P2_RX_DSCP_PRI_MAP0 ***********************************/

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI0_SHIFT                                                              (0x00000000u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI0_MASK                                                               (0x00000007u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI1_SHIFT                                                              (0x00000004u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI1_MASK                                                               (0x00000070u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI2_SHIFT                                                              (0x00000008u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI2_MASK                                                               (0x00000700u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI3_SHIFT                                                              (0x0000000Cu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI3_MASK                                                               (0x00007000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI4_SHIFT                                                              (0x00000010u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI4_MASK                                                               (0x00070000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI5_SHIFT                                                              (0x00000014u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI5_MASK                                                               (0x00700000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI6_SHIFT                                                              (0x00000018u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI6_MASK                                                               (0x07000000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI7_SHIFT                                                              (0x0000001Cu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI7_MASK                                                               (0x70000000u)


/*!********************************* GMAC_SW_P2_RX_DSCP_PRI_MAP1 ***********************************/

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI8_SHIFT                                                              (0x00000000u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI8_MASK                                                               (0x00000007u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI9_SHIFT                                                              (0x00000004u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI9_MASK                                                               (0x00000070u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI10_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI10_MASK                                                              (0x00000700u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI11_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI11_MASK                                                              (0x00007000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI12_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI12_MASK                                                              (0x00070000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI13_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI13_MASK                                                              (0x00700000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI14_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI14_MASK                                                              (0x07000000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI15_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI15_MASK                                                              (0x70000000u)


/*!********************************* GMAC_SW_P2_RX_DSCP_PRI_MAP2 ***********************************/

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI16_SHIFT                                                             (0x00000000u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI16_MASK                                                              (0x00000007u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI17_SHIFT                                                             (0x00000004u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI17_MASK                                                              (0x00000070u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI18_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI18_MASK                                                              (0x00000700u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI19_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI19_MASK                                                              (0x00007000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI20_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI20_MASK                                                              (0x00070000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI21_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI21_MASK                                                              (0x00700000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI22_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI22_MASK                                                              (0x07000000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI23_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI23_MASK                                                              (0x70000000u)


/*!********************************* GMAC_SW_P2_RX_DSCP_PRI_MAP3 ***********************************/

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI24_SHIFT                                                             (0x00000000u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI24_MASK                                                              (0x00000007u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI25_SHIFT                                                             (0x00000004u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI25_MASK                                                              (0x00000070u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI26_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI26_MASK                                                              (0x00000700u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI27_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI27_MASK                                                              (0x00007000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI28_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI28_MASK                                                              (0x00070000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI29_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI29_MASK                                                              (0x00700000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI30_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI30_MASK                                                              (0x07000000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI31_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI31_MASK                                                              (0x70000000u)


/*!********************************* GMAC_SW_P2_RX_DSCP_PRI_MAP4 ***********************************/

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI32_SHIFT                                                             (0x00000000u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI32_MASK                                                              (0x00000007u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI33_SHIFT                                                             (0x00000004u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI33_MASK                                                              (0x00000070u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI34_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI34_MASK                                                              (0x00000700u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI35_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI35_MASK                                                              (0x00007000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI36_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI36_MASK                                                              (0x00070000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI37_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI37_MASK                                                              (0x00700000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI38_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI38_MASK                                                              (0x07000000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI39_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI39_MASK                                                              (0x70000000u)


/*!********************************* GMAC_SW_P2_RX_DSCP_PRI_MAP5 ***********************************/

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI40_SHIFT                                                             (0x00000000u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI40_MASK                                                              (0x00000007u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI41_SHIFT                                                             (0x00000004u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI41_MASK                                                              (0x00000070u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI42_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI42_MASK                                                              (0x00000700u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI43_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI43_MASK                                                              (0x00007000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI44_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI44_MASK                                                              (0x00070000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI45_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI45_MASK                                                              (0x00700000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI46_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI46_MASK                                                              (0x07000000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI47_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI47_MASK                                                              (0x70000000u)


/*!********************************* GMAC_SW_P2_RX_DSCP_PRI_MAP6 ***********************************/

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI48_SHIFT                                                             (0x00000000u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI48_MASK                                                              (0x00000007u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI49_SHIFT                                                             (0x00000004u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI49_MASK                                                              (0x00000070u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI50_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI50_MASK                                                              (0x00000700u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI51_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI51_MASK                                                              (0x00007000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI52_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI52_MASK                                                              (0x00070000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_5_SHIFT                                                        (0x00000013u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_5_MASK                                                         (0x00080000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI53_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI53_MASK                                                              (0x00700000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_6_SHIFT                                                        (0x00000017u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_6_MASK                                                         (0x00800000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI54_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI54_MASK                                                              (0x07000000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_7_SHIFT                                                        (0x0000001Bu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_7_MASK                                                         (0x08000000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI55_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI55_MASK                                                              (0x70000000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_8_SHIFT                                                        (0x0000001Fu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_8_MASK                                                         (0x80000000u)


/*!********************************* GMAC_SW_P2_RX_DSCP_PRI_MAP7 ***********************************/

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI56_SHIFT                                                             (0x00000000u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI56_MASK                                                              (0x00000007u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_SHIFT                                                          (0x00000003u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_MASK                                                           (0x00000008u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI57_SHIFT                                                             (0x00000004u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI57_MASK                                                              (0x00000070u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_2_SHIFT                                                        (0x00000007u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_2_MASK                                                         (0x00000080u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI58_SHIFT                                                             (0x00000008u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI58_MASK                                                              (0x00000700u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_3_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_3_MASK                                                         (0x00000800u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI59_SHIFT                                                             (0x0000000Cu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI59_MASK                                                              (0x00007000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_4_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_4_MASK                                                         (0x00008000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI60_SHIFT                                                             (0x00000010u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI60_MASK                                                              (0x00070000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_5_SHIFT                                                        (0x00000013u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_5_MASK                                                         (0x00080000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI61_SHIFT                                                             (0x00000014u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI61_MASK                                                              (0x00700000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_6_SHIFT                                                        (0x00000017u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_6_MASK                                                         (0x00800000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI62_SHIFT                                                             (0x00000018u)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI62_MASK                                                              (0x07000000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_7_SHIFT                                                        (0x0000001Bu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_7_MASK                                                         (0x08000000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI63_SHIFT                                                             (0x0000001Cu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI63_MASK                                                              (0x70000000u)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_8_SHIFT                                                        (0x0000001Fu)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_8_MASK                                                         (0x80000000u)


/*!**************************************************************************************************
* End of File
****************************************************************************************************/
#ifdef __cplusplus
}
#endif

#endif  /* _HW_GMACSW_PORT_H_ */
