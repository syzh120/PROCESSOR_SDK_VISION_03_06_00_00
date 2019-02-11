/*
 *
 * hw_gmacsw_ale.h - register-level header file for GMAC_SW ALE
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

#ifndef _HW_GMACSW_ALE_H_
#define _HW_GMACSW_ALE_H_

#ifdef __cplusplus
extern "C"
{
#endif


/*!**************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define GMAC_SW_ALE_IDVER                                                                                       (0x00000000u)
#define GMAC_SW_ALE_CONTROL                                                                                     (0x00000008u)
#define GMAC_SW_ALE_PRESCALE                                                                                    (0x00000010u)
#define GMAC_SW_ALE_UNKNOWN_VLAN                                                                                (0x00000018u)
#define GMAC_SW_ALE_TBLCTL                                                                                      (0x00000020u)
#define GMAC_SW_ALE_TBLW2                                                                                       (0x00000034u)
#define GMAC_SW_ALE_TBLW1                                                                                       (0x00000038u)
#define GMAC_SW_ALE_TBLW0                                                                                       (0x0000003Cu)
#define GMAC_SW_ALE_PORTCTL0                                                                                    (0x00000040u)
#define GMAC_SW_ALE_PORTCTL1                                                                                    (0x00000044u)
#define GMAC_SW_ALE_PORTCTL2                                                                                    (0x00000048u)
#define GMAC_SW_ALE_PORTCTL3                                                                                    (0x0000004Cu)
#define GMAC_SW_ALE_PORTCTL4                                                                                    (0x00000050u)
#define GMAC_SW_ALE_PORTCTL5                                                                                    (0x00000054u)


/*!**************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

/*!**************************************** GMAC_SW_ALE_IDVER ******************************************/

#define GMAC_SW_ALE_IDVER_MINOR_VER_SHIFT                                                                       (0x00000000u)
#define GMAC_SW_ALE_IDVER_MINOR_VER_MASK                                                                        (0x000000FFu)

#define GMAC_SW_ALE_IDVER_MAJ_VER_SHIFT                                                                         (0x00000008u)
#define GMAC_SW_ALE_IDVER_MAJ_VER_MASK                                                                          (0x0000FF00u)

#define GMAC_SW_ALE_IDVER_IDENT_SHIFT                                                                           (0x00000010u)
#define GMAC_SW_ALE_IDVER_IDENT_MASK                                                                            (0xFFFF0000u)


/*!*************************************** GMAC_SW_ALE_CONTROL *****************************************/

#define GMAC_SW_ALE_CONTROL_ENABLE_RATE_LIMIT_SHIFT                                                             (0x00000000u)
#define GMAC_SW_ALE_CONTROL_ENABLE_RATE_LIMIT_MASK                                                              (0x00000001u)

#define GMAC_SW_ALE_CONTROL_ENABLE_AUTH_MODE_SHIFT                                                              (0x00000001u)
#define GMAC_SW_ALE_CONTROL_ENABLE_AUTH_MODE_MASK                                                               (0x00000002u)

#define GMAC_SW_ALE_CONTROL_VLAN_AWARE_SHIFT                                                                    (0x00000002u)
#define GMAC_SW_ALE_CONTROL_VLAN_AWARE_MASK                                                                     (0x00000004u)

#define GMAC_SW_ALE_CONTROL_RATE_LIMIT_TX_SHIFT                                                                 (0x00000003u)
#define GMAC_SW_ALE_CONTROL_RATE_LIMIT_TX_MASK                                                                  (0x00000008u)

#define GMAC_SW_ALE_CONTROL_BYPASS_SHIFT                                                                        (0x00000004u)
#define GMAC_SW_ALE_CONTROL_BYPASS_MASK                                                                         (0x00000010u)

#define GMAC_SW_ALE_CONTROL_ENABLE_OUI_DENY_SHIFT                                                               (0x00000005u)
#define GMAC_SW_ALE_CONTROL_ENABLE_OUI_DENY_MASK                                                                (0x00000020u)

#define GMAC_SW_ALE_CONTROL_EN_VID0_MODE_SHIFT                                                                  (0x00000006u)
#define GMAC_SW_ALE_CONTROL_EN_VID0_MODE_MASK                                                                   (0x00000040u)

#define GMAC_SW_ALE_CONTROL_LEARN_NO_VID_SHIFT                                                                  (0x00000007u)
#define GMAC_SW_ALE_CONTROL_LEARN_NO_VID_MASK                                                                   (0x00000080u)

#define GMAC_SW_ALE_CONTROL_EN_P0_UNI_FLOOD_SHIFT                                                               (0x00000008u)
#define GMAC_SW_ALE_CONTROL_EN_P0_UNI_FLOOD_MASK                                                                (0x00000100u)

#define GMAC_SW_ALE_CONTROL_AGE_OUT_NOW_SHIFT                                                                   (0x0000001Du)
#define GMAC_SW_ALE_CONTROL_AGE_OUT_NOW_MASK                                                                    (0x20000000u)

#define GMAC_SW_ALE_CONTROL_CLEAR_TABLE_SHIFT                                                                   (0x0000001Eu)
#define GMAC_SW_ALE_CONTROL_CLEAR_TABLE_MASK                                                                    (0x40000000u)

#define GMAC_SW_ALE_CONTROL_ENABLE_ALE_SHIFT                                                                    (0x0000001Fu)
#define GMAC_SW_ALE_CONTROL_ENABLE_ALE_MASK                                                                     (0x80000000u)


/*!*************************************** GMAC_SW_ALE_PRESCALE *****************************************/

#define GMAC_SW_ALE_PRESCALE_PRESCALE_SHIFT                                                                     (0x00000000u)
#define GMAC_SW_ALE_PRESCALE_PRESCALE_MASK                                                                      (0x000FFFFFu)


/*!************************************* GMAC_SW_ALE_UNKNOWN_VLAN ***************************************/

#define GMAC_SW_ALE_UNKNOWN_VLAN_UNKNOWN_VLAN_MEMBER_LIST_SHIFT                                                 (0x00000000u)
#define GMAC_SW_ALE_UNKNOWN_VLAN_UNKNOWN_VLAN_MEMBER_LIST_MASK                                                  (0x0000003Fu)

#define GMAC_SW_ALE_UNKNOWN_VLAN_UNKNOWN_MCAST_FLOOD_MASK_SHIFT                                                 (0x00000008u)
#define GMAC_SW_ALE_UNKNOWN_VLAN_UNKNOWN_MCAST_FLOOD_MASK_MASK                                                  (0x00003F00u)

#define GMAC_SW_ALE_UNKNOWN_VLAN_UNKNOWN_REG_MCAST_FLOOD_MASK_SHIFT                                             (0x00000010u)
#define GMAC_SW_ALE_UNKNOWN_VLAN_UNKNOWN_REG_MCAST_FLOOD_MASK_MASK                                              (0x003F0000u)

#define GMAC_SW_ALE_UNKNOWN_VLAN_UNKNOWN_FORCE_UNTAGGED_EGRESS_SHIFT                                            (0x00000018u)
#define GMAC_SW_ALE_UNKNOWN_VLAN_UNKNOWN_FORCE_UNTAGGED_EGRESS_MASK                                             (0x3F000000u)


/*!**************************************** GMAC_SW_ALE_TBLCTL ******************************************/

#define GMAC_SW_ALE_TBLCTL_ENTRY_POINTER_SHIFT                                                                  (0x00000000u)
#define GMAC_SW_ALE_TBLCTL_ENTRY_POINTER_MASK                                                                   (0x000003FFu)

#define GMAC_SW_ALE_TBLCTL_WRITE_RDZ_SHIFT                                                                      (0x0000001Fu)
#define GMAC_SW_ALE_TBLCTL_WRITE_RDZ_MASK                                                                       (0x80000000u)


/*!**************************************** GMAC_SW_ALE_TBLW2 ******************************************/

#define GMAC_SW_ALE_TBLW2_ENTRY71_64_SHIFT                                                                      (0x00000000u)
#define GMAC_SW_ALE_TBLW2_ENTRY71_64_MASK                                                                       (0x000000FFu)


/*!**************************************** GMAC_SW_ALE_TBLW1 ******************************************/

#define GMAC_SW_ALE_TBLW1_ENTRY63_32_SHIFT                                                                      (0x00000000u)
#define GMAC_SW_ALE_TBLW1_ENTRY63_32_MASK                                                                       (0xFFFFFFFFu)


/*!**************************************** GMAC_SW_ALE_TBLW0 ******************************************/

#define GMAC_SW_ALE_TBLW0_ENTRY31_0_SHIFT                                                                       (0x00000000u)
#define GMAC_SW_ALE_TBLW0_ENTRY31_0_MASK                                                                        (0xFFFFFFFFu)


/*!*************************************** GMAC_SW_ALE_PORTCTL0 *****************************************/

#define GMAC_SW_ALE_PORTCTL0_PORT_STATE_SHIFT                                                                   (0x00000000u)
#define GMAC_SW_ALE_PORTCTL0_PORT_STATE_MASK                                                                    (0x00000003u)

#define GMAC_SW_ALE_PORTCTL0_DROP_UNTAGGED_SHIFT                                                                (0x00000002u)
#define GMAC_SW_ALE_PORTCTL0_DROP_UNTAGGED_MASK                                                                 (0x00000004u)

#define GMAC_SW_ALE_PORTCTL0_VID_INGRESS_CHECK_SHIFT                                                            (0x00000003u)
#define GMAC_SW_ALE_PORTCTL0_VID_INGRESS_CHECK_MASK                                                             (0x00000008u)

#define GMAC_SW_ALE_PORTCTL0_NO_LEARN_SHIFT                                                                     (0x00000004u)
#define GMAC_SW_ALE_PORTCTL0_NO_LEARN_MASK                                                                      (0x00000010u)

#define GMAC_SW_ALE_PORTCTL0_NO_SA_UPDATE_SHIFT                                                                 (0x00000005u)
#define GMAC_SW_ALE_PORTCTL0_NO_SA_UPDATE_MASK                                                                  (0x00000020u)

#define GMAC_SW_ALE_PORTCTL0_MCAST_LIMIT_SHIFT                                                                  (0x00000010u)
#define GMAC_SW_ALE_PORTCTL0_MCAST_LIMIT_MASK                                                                   (0x00FF0000u)

#define GMAC_SW_ALE_PORTCTL0_BCAST_LIMIT_SHIFT                                                                  (0x00000018u)
#define GMAC_SW_ALE_PORTCTL0_BCAST_LIMIT_MASK                                                                   (0xFF000000u)


/*!*************************************** GMAC_SW_ALE_PORTCTL1 *****************************************/

#define GMAC_SW_ALE_PORTCTL1_PORT_STATE_SHIFT                                                                   (0x00000000u)
#define GMAC_SW_ALE_PORTCTL1_PORT_STATE_MASK                                                                    (0x00000003u)

#define GMAC_SW_ALE_PORTCTL1_DROP_UNTAGGED_SHIFT                                                                (0x00000002u)
#define GMAC_SW_ALE_PORTCTL1_DROP_UNTAGGED_MASK                                                                 (0x00000004u)

#define GMAC_SW_ALE_PORTCTL1_VID_INGRESS_CHECK_SHIFT                                                            (0x00000003u)
#define GMAC_SW_ALE_PORTCTL1_VID_INGRESS_CHECK_MASK                                                             (0x00000008u)

#define GMAC_SW_ALE_PORTCTL1_NO_LEARN_SHIFT                                                                     (0x00000004u)
#define GMAC_SW_ALE_PORTCTL1_NO_LEARN_MASK                                                                      (0x00000010u)

#define GMAC_SW_ALE_PORTCTL1_NO_SA_UPDATE_SHIFT                                                                 (0x00000005u)
#define GMAC_SW_ALE_PORTCTL1_NO_SA_UPDATE_MASK                                                                  (0x00000020u)

#define GMAC_SW_ALE_PORTCTL1_MCAST_LIMIT_SHIFT                                                                  (0x00000010u)
#define GMAC_SW_ALE_PORTCTL1_MCAST_LIMIT_MASK                                                                   (0x00FF0000u)

#define GMAC_SW_ALE_PORTCTL1_BCAST_LIMIT_SHIFT                                                                  (0x00000018u)
#define GMAC_SW_ALE_PORTCTL1_BCAST_LIMIT_MASK                                                                   (0xFF000000u)


/*!*************************************** GMAC_SW_ALE_PORTCTL2 *****************************************/

#define GMAC_SW_ALE_PORTCTL2_PORT_STATE_SHIFT                                                                   (0x00000000u)
#define GMAC_SW_ALE_PORTCTL2_PORT_STATE_MASK                                                                    (0x00000003u)

#define GMAC_SW_ALE_PORTCTL2_DROP_UNTAGGED_SHIFT                                                                (0x00000002u)
#define GMAC_SW_ALE_PORTCTL2_DROP_UNTAGGED_MASK                                                                 (0x00000004u)

#define GMAC_SW_ALE_PORTCTL2_VID_INGRESS_CHECK_SHIFT                                                            (0x00000003u)
#define GMAC_SW_ALE_PORTCTL2_VID_INGRESS_CHECK_MASK                                                             (0x00000008u)

#define GMAC_SW_ALE_PORTCTL2_NO_LEARN_SHIFT                                                                     (0x00000004u)
#define GMAC_SW_ALE_PORTCTL2_NO_LEARN_MASK                                                                      (0x00000010u)

#define GMAC_SW_ALE_PORTCTL2_NO_SA_UPDATE_SHIFT                                                                 (0x00000005u)
#define GMAC_SW_ALE_PORTCTL2_NO_SA_UPDATE_MASK                                                                  (0x00000020u)

#define GMAC_SW_ALE_PORTCTL2_MCAST_LIMIT_SHIFT                                                                  (0x00000010u)
#define GMAC_SW_ALE_PORTCTL2_MCAST_LIMIT_MASK                                                                   (0x00FF0000u)

#define GMAC_SW_ALE_PORTCTL2_BCAST_LIMIT_SHIFT                                                                  (0x00000018u)
#define GMAC_SW_ALE_PORTCTL2_BCAST_LIMIT_MASK                                                                   (0xFF000000u)


/*!*************************************** GMAC_SW_ALE_PORTCTL3 *****************************************/

#define GMAC_SW_ALE_PORTCTL3_PORT_STATE_SHIFT                                                                   (0x00000000u)
#define GMAC_SW_ALE_PORTCTL3_PORT_STATE_MASK                                                                    (0x00000003u)

#define GMAC_SW_ALE_PORTCTL3_DROP_UNTAGGED_SHIFT                                                                (0x00000002u)
#define GMAC_SW_ALE_PORTCTL3_DROP_UNTAGGED_MASK                                                                 (0x00000004u)

#define GMAC_SW_ALE_PORTCTL3_VID_INGRESS_CHECK_SHIFT                                                            (0x00000003u)
#define GMAC_SW_ALE_PORTCTL3_VID_INGRESS_CHECK_MASK                                                             (0x00000008u)

#define GMAC_SW_ALE_PORTCTL3_NO_LEARN_SHIFT                                                                     (0x00000004u)
#define GMAC_SW_ALE_PORTCTL3_NO_LEARN_MASK                                                                      (0x00000010u)

#define GMAC_SW_ALE_PORTCTL3_NO_SA_UPDATE_SHIFT                                                                 (0x00000005u)
#define GMAC_SW_ALE_PORTCTL3_NO_SA_UPDATE_MASK                                                                  (0x00000020u)

#define GMAC_SW_ALE_PORTCTL3_MCAST_LIMIT_SHIFT                                                                  (0x00000010u)
#define GMAC_SW_ALE_PORTCTL3_MCAST_LIMIT_MASK                                                                   (0x00FF0000u)

#define GMAC_SW_ALE_PORTCTL3_BCAST_LIMIT_SHIFT                                                                  (0x00000018u)
#define GMAC_SW_ALE_PORTCTL3_BCAST_LIMIT_MASK                                                                   (0xFF000000u)


/*!*************************************** GMAC_SW_ALE_PORTCTL4 *****************************************/

#define GMAC_SW_ALE_PORTCTL4_PORT_STATE_SHIFT                                                                   (0x00000000u)
#define GMAC_SW_ALE_PORTCTL4_PORT_STATE_MASK                                                                    (0x00000003u)

#define GMAC_SW_ALE_PORTCTL4_DROP_UNTAGGED_SHIFT                                                                (0x00000002u)
#define GMAC_SW_ALE_PORTCTL4_DROP_UNTAGGED_MASK                                                                 (0x00000004u)

#define GMAC_SW_ALE_PORTCTL4_VID_INGRESS_CHECK_SHIFT                                                            (0x00000003u)
#define GMAC_SW_ALE_PORTCTL4_VID_INGRESS_CHECK_MASK                                                             (0x00000008u)

#define GMAC_SW_ALE_PORTCTL4_NO_LEARN_SHIFT                                                                     (0x00000004u)
#define GMAC_SW_ALE_PORTCTL4_NO_LEARN_MASK                                                                      (0x00000010u)

#define GMAC_SW_ALE_PORTCTL4_NO_SA_UPDATE_SHIFT                                                                 (0x00000005u)
#define GMAC_SW_ALE_PORTCTL4_NO_SA_UPDATE_MASK                                                                  (0x00000020u)

#define GMAC_SW_ALE_PORTCTL4_MCAST_LIMIT_SHIFT                                                                  (0x00000010u)
#define GMAC_SW_ALE_PORTCTL4_MCAST_LIMIT_MASK                                                                   (0x00FF0000u)

#define GMAC_SW_ALE_PORTCTL4_BCAST_LIMIT_SHIFT                                                                  (0x00000018u)
#define GMAC_SW_ALE_PORTCTL4_BCAST_LIMIT_MASK                                                                   (0xFF000000u)


/*!*************************************** GMAC_SW_ALE_PORTCTL5 *****************************************/

#define GMAC_SW_ALE_PORTCTL5_PORT_STATE_SHIFT                                                                   (0x00000000u)
#define GMAC_SW_ALE_PORTCTL5_PORT_STATE_MASK                                                                    (0x00000003u)

#define GMAC_SW_ALE_PORTCTL5_DROP_UNTAGGED_SHIFT                                                                (0x00000002u)
#define GMAC_SW_ALE_PORTCTL5_DROP_UNTAGGED_MASK                                                                 (0x00000004u)

#define GMAC_SW_ALE_PORTCTL5_VID_INGRESS_CHECK_SHIFT                                                            (0x00000003u)
#define GMAC_SW_ALE_PORTCTL5_VID_INGRESS_CHECK_MASK                                                             (0x00000008u)

#define GMAC_SW_ALE_PORTCTL5_NO_LEARN_SHIFT                                                                     (0x00000004u)
#define GMAC_SW_ALE_PORTCTL5_NO_LEARN_MASK                                                                      (0x00000010u)

#define GMAC_SW_ALE_PORTCTL5_NO_SA_UPDATE_SHIFT                                                                 (0x00000005u)
#define GMAC_SW_ALE_PORTCTL5_NO_SA_UPDATE_MASK                                                                  (0x00000020u)

#define GMAC_SW_ALE_PORTCTL5_MCAST_LIMIT_SHIFT                                                                  (0x00000010u)
#define GMAC_SW_ALE_PORTCTL5_MCAST_LIMIT_MASK                                                                   (0x00FF0000u)

#define GMAC_SW_ALE_PORTCTL5_BCAST_LIMIT_SHIFT                                                                  (0x00000018u)
#define GMAC_SW_ALE_PORTCTL5_BCAST_LIMIT_MASK                                                                   (0xFF000000u)


/*!**************************************************************************************************
* End of File
****************************************************************************************************/
#ifdef __cplusplus
}
#endif

#endif  /* _HW_GMACSW_ALE_H_ */
