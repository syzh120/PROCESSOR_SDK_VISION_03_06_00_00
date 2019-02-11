/*
 *
 * hw_gmacsw_sl.h - register-level header file for GMAC_SW
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

#ifndef _HW_GMACSW_SL_H_
#define _HW_GMACSW_SL_H_

#ifdef __cplusplus
extern "C"
{
#endif


/*!**************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define GMAC_SW_SL_IDVER                                                                                    (0x00000000u)
#define GMAC_SW_SL_MACCONTROL                                                                               (0x00000004u)
#define GMAC_SW_SL_MACSTATUS                                                                                (0x00000008u)
#define GMAC_SW_SL_SOFT_RESET                                                                               (0x0000000Cu)
#define GMAC_SW_SL_RX_MAXLEN                                                                                (0x00000010u)
#define GMAC_SW_SL_BOFFTEST                                                                                 (0x00000014u)
#define GMAC_SW_SL_RX_PAUSE                                                                                 (0x00000018u)
#define GMAC_SW_SL_TX_PAUSE                                                                                 (0x0000001Cu)
#define GMAC_SW_SL_EMCONTROL                                                                                (0x00000020u)
#define GMAC_SW_SL_RX_PRI_MAP                                                                               (0x00000024u)
#define GMAC_SW_SL_TX_GAP                                                                                   (0x00000028u)


/*!**************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

/*!**************************************** GMAC_SW_SL_IDVER ******************************************/

#define GMAC_SW_SL_IDVER_Y_SHIFT                                                                               (0x00000000u)
#define GMAC_SW_SL_IDVER_Y_MASK                                                                                (0x000000FFu)

#define GMAC_SW_SL_IDVER_X_SHIFT                                                                               (0x00000008u)
#define GMAC_SW_SL_IDVER_X_MASK                                                                                (0x00000700u)

#define GMAC_SW_SL_IDVER_Z_SHIFT                                                                               (0x0000000Bu)
#define GMAC_SW_SL_IDVER_Z_MASK                                                                                (0x0000F800u)

#define GMAC_SW_SL_IDVER_IDENT_SHIFT                                                                           (0x00000010u)
#define GMAC_SW_SL_IDVER_IDENT_MASK                                                                            (0xFFFF0000u)


/*!************************************** GMAC_SW_SL_MACCONTROL ****************************************/

#define GMAC_SW_SL_MACCONTROL_FULLDUPLEX_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_SL_MACCONTROL_FULLDUPLEX_MASK                                                                  (0x00000001u)

#define GMAC_SW_SL_MACCONTROL_LOOPBACK_SHIFT                                                                   (0x00000001u)
#define GMAC_SW_SL_MACCONTROL_LOOPBACK_MASK                                                                    (0x00000002u)

#define GMAC_SW_SL_MACCONTROL_MTEST_SHIFT                                                                      (0x00000002u)
#define GMAC_SW_SL_MACCONTROL_MTEST_MASK                                                                       (0x00000004u)

#define GMAC_SW_SL_MACCONTROL_RX_FLOW_EN_SHIFT                                                                 (0x00000003u)
#define GMAC_SW_SL_MACCONTROL_RX_FLOW_EN_MASK                                                                  (0x00000008u)

#define GMAC_SW_SL_MACCONTROL_TX_FLOW_EN_SHIFT                                                                 (0x00000004u)
#define GMAC_SW_SL_MACCONTROL_TX_FLOW_EN_MASK                                                                  (0x00000010u)

#define GMAC_SW_SL_MACCONTROL_GMII_EN_SHIFT                                                                    (0x00000005u)
#define GMAC_SW_SL_MACCONTROL_GMII_EN_MASK                                                                     (0x00000020u)

#define GMAC_SW_SL_MACCONTROL_TX_PACE_SHIFT                                                                    (0x00000006u)
#define GMAC_SW_SL_MACCONTROL_TX_PACE_MASK                                                                     (0x00000040u)

#define GMAC_SW_SL_MACCONTROL_GIG_SHIFT                                                                        (0x00000007u)
#define GMAC_SW_SL_MACCONTROL_GIG_MASK                                                                         (0x00000080u)

#define GMAC_SW_SL_MACCONTROL_RESERVED4_SHIFT                                                                  (0x00000008u)
#define GMAC_SW_SL_MACCONTROL_RESERVED4_MASK                                                                   (0x00000300u)

#define GMAC_SW_SL_MACCONTROL_TX_SHORT_GAP_EN_SHIFT                                                            (0x0000000Au)
#define GMAC_SW_SL_MACCONTROL_TX_SHORT_GAP_EN_MASK                                                             (0x00000400u)

#define GMAC_SW_SL_MACCONTROL_CMD_IDLE_SHIFT                                                                   (0x0000000Bu)
#define GMAC_SW_SL_MACCONTROL_CMD_IDLE_MASK                                                                    (0x00000800u)

#define GMAC_SW_SL_MACCONTROL_RESERVED3_SHIFT                                                                  (0x0000000Cu)
#define GMAC_SW_SL_MACCONTROL_RESERVED3_MASK                                                                   (0x00007000u)

#define GMAC_SW_SL_MACCONTROL_IFCTL_A_SHIFT                                                                    (0x0000000Fu)
#define GMAC_SW_SL_MACCONTROL_IFCTL_A_MASK                                                                     (0x00008000u)

#define GMAC_SW_SL_MACCONTROL_IFCTL_B_SHIFT                                                                    (0x00000010u)
#define GMAC_SW_SL_MACCONTROL_IFCTL_B_MASK                                                                     (0x00010000u)

#define GMAC_SW_SL_MACCONTROL_GIG_FORCE_SHIFT                                                                  (0x00000011u)
#define GMAC_SW_SL_MACCONTROL_GIG_FORCE_MASK                                                                   (0x00020000u)

#define GMAC_SW_SL_MACCONTROL_EXT_EN_SHIFT                                                                     (0x00000012u)
#define GMAC_SW_SL_MACCONTROL_EXT_EN_MASK                                                                      (0x00040000u)

#define GMAC_SW_SL_MACCONTROL_RESERVED2_SHIFT                                                                  (0x00000013u)
#define GMAC_SW_SL_MACCONTROL_RESERVED2_MASK                                                                   (0x00180000u)

#define GMAC_SW_SL_MACCONTROL_TX_SHORT_GAP_LIM_EN_SHIFT                                                        (0x00000015u)
#define GMAC_SW_SL_MACCONTROL_TX_SHORT_GAP_LIM_EN_MASK                                                         (0x00200000u)

#define GMAC_SW_SL_MACCONTROL_RX_CEF_EN_SHIFT                                                                  (0x00000016u)
#define GMAC_SW_SL_MACCONTROL_RX_CEF_EN_MASK                                                                   (0x00400000u)

#define GMAC_SW_SL_MACCONTROL_RX_CSF_EN_SHIFT                                                                  (0x00000017u)
#define GMAC_SW_SL_MACCONTROL_RX_CSF_EN_MASK                                                                   (0x00800000u)

#define GMAC_SW_SL_MACCONTROL_RX_CMF_EN_SHIFT                                                                  (0x00000018u)
#define GMAC_SW_SL_MACCONTROL_RX_CMF_EN_MASK                                                                   (0x01000000u)

#define GMAC_SW_SL_MACCONTROL_RESERVED1_SHIFT                                                                  (0x00000019u)
#define GMAC_SW_SL_MACCONTROL_RESERVED1_MASK                                                                   (0xFE000000u)


/*!************************************** GMAC_SW_SL_MACSTATUS ****************************************/

#define GMAC_SW_SL_MACSTATUS_TX_FLOW_ACT_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_SL_MACSTATUS_TX_FLOW_ACT_MASK                                                                  (0x00000001u)

#define GMAC_SW_SL_MACSTATUS_RX_FLOW_ACT_SHIFT                                                                 (0x00000001u)
#define GMAC_SW_SL_MACSTATUS_RX_FLOW_ACT_MASK                                                                  (0x00000002u)

#define GMAC_SW_SL_MACSTATUS_RESERVED2_SHIFT                                                                   (0x00000002u)
#define GMAC_SW_SL_MACSTATUS_RESERVED2_MASK                                                                    (0x00000004u)

#define GMAC_SW_SL_MACSTATUS_EXT_FULLDUPLEX_SHIFT                                                              (0x00000003u)
#define GMAC_SW_SL_MACSTATUS_EXT_FULLDUPLEX_MASK                                                               (0x00000008u)

#define GMAC_SW_SL_MACSTATUS_EXT_GIG_SHIFT                                                                     (0x00000004u)
#define GMAC_SW_SL_MACSTATUS_EXT_GIG_MASK                                                                      (0x00000010u)

#define GMAC_SW_SL_MACSTATUS_RESERVED1_SHIFT                                                                   (0x00000005u)
#define GMAC_SW_SL_MACSTATUS_RESERVED1_MASK                                                                    (0x7FFFFFE0u)

#define GMAC_SW_SL_MACSTATUS_IDLE_SHIFT                                                                        (0x0000001Fu)
#define GMAC_SW_SL_MACSTATUS_IDLE_MASK                                                                         (0x80000000u)


/*!************************************** GMAC_SW_SL_SOFT_RESET ****************************************/

#define GMAC_SW_SL_SOFT_RESET_SOFT_RESET_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_SL_SOFT_RESET_SOFT_RESET_MASK                                                                  (0x00000001u)

#define GMAC_SW_SL_SOFT_RESET_RESERVED1_SHIFT                                                                  (0x00000001u)
#define GMAC_SW_SL_SOFT_RESET_RESERVED1_MASK                                                                   (0xFFFFFFFEu)


/*!************************************** GMAC_SW_SL_RX_MAXLEN ****************************************/

#define GMAC_SW_SL_RX_MAXLEN_RX_MAXLEN_SHIFT                                                                   (0x00000000u)
#define GMAC_SW_SL_RX_MAXLEN_RX_MAXLEN_MASK                                                                    (0x00003FFFu)

#define GMAC_SW_SL_RX_MAXLEN_RESERVED1_SHIFT                                                                   (0x0000000Eu)
#define GMAC_SW_SL_RX_MAXLEN_RESERVED1_MASK                                                                    (0xFFFFC000u)


/*!*************************************** GMAC_SW_SL_BOFFTEST *****************************************/

#define GMAC_SW_SL_BOFFTEST_TX_BACKOFF_SHIFT                                                                   (0x00000000u)
#define GMAC_SW_SL_BOFFTEST_TX_BACKOFF_MASK                                                                    (0x000003FFu)

#define GMAC_SW_SL_BOFFTEST_RESERVED2_SHIFT                                                                    (0x0000000Au)
#define GMAC_SW_SL_BOFFTEST_RESERVED2_MASK                                                                     (0x00000C00u)

#define GMAC_SW_SL_BOFFTEST_COLL_COUNT_SHIFT                                                                   (0x0000000Cu)
#define GMAC_SW_SL_BOFFTEST_COLL_COUNT_MASK                                                                    (0x0000F000u)

#define GMAC_SW_SL_BOFFTEST_RNDNUM_SHIFT                                                                       (0x00000010u)
#define GMAC_SW_SL_BOFFTEST_RNDNUM_MASK                                                                        (0x03FF0000u)

#define GMAC_SW_SL_BOFFTEST_PACEVAL_SHIFT                                                                      (0x0000001Au)
#define GMAC_SW_SL_BOFFTEST_PACEVAL_MASK                                                                       (0x7C000000u)

#define GMAC_SW_SL_BOFFTEST_RESERVED1_SHIFT                                                                    (0x0000001Fu)
#define GMAC_SW_SL_BOFFTEST_RESERVED1_MASK                                                                     (0x80000000u)


/*!*************************************** GMAC_SW_SL_RX_PAUSE *****************************************/

#define GMAC_SW_SL_RX_PAUSE_RX_PAUSETIMER_SHIFT                                                                (0x00000000u)
#define GMAC_SW_SL_RX_PAUSE_RX_PAUSETIMER_MASK                                                                 (0x0000FFFFu)

#define GMAC_SW_SL_RX_PAUSE_RESERVED1_SHIFT                                                                    (0x00000010u)
#define GMAC_SW_SL_RX_PAUSE_RESERVED1_MASK                                                                     (0xFFFF0000u)


/*!*************************************** GMAC_SW_SL_TX_PAUSE *****************************************/

#define GMAC_SW_SL_TX_PAUSE_TX_PAUSETIMER_SHIFT                                                                (0x00000000u)
#define GMAC_SW_SL_TX_PAUSE_TX_PAUSETIMER_MASK                                                                 (0x0000FFFFu)

#define GMAC_SW_SL_TX_PAUSE_RESERVED1_SHIFT                                                                    (0x00000010u)
#define GMAC_SW_SL_TX_PAUSE_RESERVED1_MASK                                                                     (0xFFFF0000u)


/*!************************************** GMAC_SW_SL_EMCONTROL ****************************************/

#define GMAC_SW_SL_EMCONTROL_FREE_SHIFT                                                                        (0x00000000u)
#define GMAC_SW_SL_EMCONTROL_FREE_MASK                                                                         (0x00000001u)

#define GMAC_SW_SL_EMCONTROL_SOFT_SHIFT                                                                        (0x00000001u)
#define GMAC_SW_SL_EMCONTROL_SOFT_MASK                                                                         (0x00000002u)

#define GMAC_SW_SL_EMCONTROL_RESERVED1_SHIFT                                                                   (0x00000002u)
#define GMAC_SW_SL_EMCONTROL_RESERVED1_MASK                                                                    (0xFFFFFFFCu)


/*!************************************** GMAC_SW_SL_RX_PRI_MAP ****************************************/

#define GMAC_SW_SL_RX_PRI_MAP_PRI0_SHIFT                                                                       (0x00000000u)
#define GMAC_SW_SL_RX_PRI_MAP_PRI0_MASK                                                                        (0x00000007u)

#define GMAC_SW_SL_RX_PRI_MAP_RESERVED8_SHIFT                                                                  (0x00000003u)
#define GMAC_SW_SL_RX_PRI_MAP_RESERVED8_MASK                                                                   (0x00000008u)

#define GMAC_SW_SL_RX_PRI_MAP_PRI1_SHIFT                                                                       (0x00000004u)
#define GMAC_SW_SL_RX_PRI_MAP_PRI1_MASK                                                                        (0x00000070u)

#define GMAC_SW_SL_RX_PRI_MAP_RESERVED7_SHIFT                                                                  (0x00000007u)
#define GMAC_SW_SL_RX_PRI_MAP_RESERVED7_MASK                                                                   (0x00000080u)

#define GMAC_SW_SL_RX_PRI_MAP_PRI2_SHIFT                                                                       (0x00000008u)
#define GMAC_SW_SL_RX_PRI_MAP_PRI2_MASK                                                                        (0x00000700u)

#define GMAC_SW_SL_RX_PRI_MAP_RESERVED6_SHIFT                                                                  (0x0000000Bu)
#define GMAC_SW_SL_RX_PRI_MAP_RESERVED6_MASK                                                                   (0x00000800u)

#define GMAC_SW_SL_RX_PRI_MAP_PRI3_SHIFT                                                                       (0x0000000Cu)
#define GMAC_SW_SL_RX_PRI_MAP_PRI3_MASK                                                                        (0x00007000u)

#define GMAC_SW_SL_RX_PRI_MAP_RESERVED5_SHIFT                                                                  (0x0000000Fu)
#define GMAC_SW_SL_RX_PRI_MAP_RESERVED5_MASK                                                                   (0x00008000u)

#define GMAC_SW_SL_RX_PRI_MAP_PRI4_SHIFT                                                                       (0x00000010u)
#define GMAC_SW_SL_RX_PRI_MAP_PRI4_MASK                                                                        (0x00070000u)

#define GMAC_SW_SL_RX_PRI_MAP_RESERVED4_SHIFT                                                                  (0x00000013u)
#define GMAC_SW_SL_RX_PRI_MAP_RESERVED4_MASK                                                                   (0x00080000u)

#define GMAC_SW_SL_RX_PRI_MAP_PRI5_SHIFT                                                                       (0x00000014u)
#define GMAC_SW_SL_RX_PRI_MAP_PRI5_MASK                                                                        (0x00700000u)

#define GMAC_SW_SL_RX_PRI_MAP_RESERVED3_SHIFT                                                                  (0x00000017u)
#define GMAC_SW_SL_RX_PRI_MAP_RESERVED3_MASK                                                                   (0x00800000u)

#define GMAC_SW_SL_RX_PRI_MAP_PRI6_SHIFT                                                                       (0x00000018u)
#define GMAC_SW_SL_RX_PRI_MAP_PRI6_MASK                                                                        (0x07000000u)

#define GMAC_SW_SL_RX_PRI_MAP_RESERVED2_SHIFT                                                                  (0x0000001Bu)
#define GMAC_SW_SL_RX_PRI_MAP_RESERVED2_MASK                                                                   (0x08000000u)

#define GMAC_SW_SL_RX_PRI_MAP_PRI7_SHIFT                                                                       (0x0000001Cu)
#define GMAC_SW_SL_RX_PRI_MAP_PRI7_MASK                                                                        (0x70000000u)

#define GMAC_SW_SL_RX_PRI_MAP_RESERVED1_SHIFT                                                                  (0x0000001Fu)
#define GMAC_SW_SL_RX_PRI_MAP_RESERVED1_MASK                                                                   (0x80000000u)


/*!**************************************** GMAC_SW_SL_TX_GAP ******************************************/

#define GMAC_SW_SL_TX_GAP_TX_GAP_SHIFT                                                                         (0x00000000u)
#define GMAC_SW_SL_TX_GAP_TX_GAP_MASK                                                                          (0x000001FFu)

#define GMAC_SW_SL_TX_GAP_RESERVED1_SHIFT                                                                      (0x00000009u)
#define GMAC_SW_SL_TX_GAP_RESERVED1_MASK                                                                       (0xFFFFFE00u)


/*!**************************************************************************************************
* End of File
****************************************************************************************************/
#ifdef __cplusplus
}
#endif

#endif  /* _HW_GMACSW_SL_H_ */
