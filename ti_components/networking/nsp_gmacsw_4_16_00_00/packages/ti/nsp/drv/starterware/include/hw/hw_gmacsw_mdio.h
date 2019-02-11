/*
 *
 * hw_gmacsw_mdio.h - register-level header file for GMAC_SW
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

#ifndef _HW_GMACSW_MDIO_H_
#define _HW_GMACSW_MDIO_H_

#ifdef __cplusplus
extern "C"
{
#endif


/*!**************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define GMAC_SW_MDIO_VER                                                                                     (0x00000000u)
#define GMAC_SW_MDIO_CONTROL                                                                                 (0x00000004u)
#define GMAC_SW_MDIO_ALIVE                                                                                   (0x00000008u)
#define GMAC_SW_MDIO_LINK                                                                                    (0x0000000Cu)
#define GMAC_SW_MDIO_LINKINTRAW                                                                              (0x00000010u)
#define GMAC_SW_MDIO_LINKINTMASKED                                                                           (0x00000014u)
#define GMAC_SW_MDIO_USERINTRAW                                                                              (0x00000020u)
#define GMAC_SW_MDIO_USERINTMASKED                                                                           (0x00000024u)
#define GMAC_SW_MDIO_USERINTMASKSET                                                                          (0x00000028u)
#define GMAC_SW_MDIO_USERINTMASKCLR                                                                          (0x0000002Cu)
#define GMAC_SW_MDIO_USERACCESS0                                                                             (0x00000080u)
#define GMAC_SW_MDIO_USERPHYSEL0                                                                             (0x00000084u)
#define GMAC_SW_MDIO_USERACCESS1                                                                             (0x00000088u)
#define GMAC_SW_MDIO_USERPHYSEL1                                                                             (0x0000008Cu)


/*!**************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

/*!*************************************** GMAC_SW_MDIO_VER *****************************************/

#define GMAC_SW_MDIO_VER_REVMIN_SHIFT                                                                        (0x00000000u)
#define GMAC_SW_MDIO_VER_REVMIN_MASK                                                                         (0x000000FFu)

#define GMAC_SW_MDIO_VER_REVMAJ_SHIFT                                                                        (0x00000008u)
#define GMAC_SW_MDIO_VER_REVMAJ_MASK                                                                         (0x0000FF00u)

#define GMAC_SW_MDIO_VER_MODID_SHIFT                                                                         (0x00000010u)
#define GMAC_SW_MDIO_VER_MODID_MASK                                                                          (0xFFFF0000u)


/*!************************************* GMAC_SW_MDIO_CONTROL ***************************************/

#define GMAC_SW_MDIO_CONTROL_CLKDIV_SHIFT                                                                    (0x00000000u)
#define GMAC_SW_MDIO_CONTROL_CLKDIV_MASK                                                                     (0x0000FFFFu)

#define GMAC_SW_MDIO_CONTROL_RESERVED3_SHIFT                                                                 (0x00000010u)
#define GMAC_SW_MDIO_CONTROL_RESERVED3_MASK                                                                  (0x00010000u)

#define GMAC_SW_MDIO_CONTROL_INTTESTENB_SHIFT                                                                (0x00000011u)
#define GMAC_SW_MDIO_CONTROL_INTTESTENB_MASK                                                                 (0x00020000u)

#define GMAC_SW_MDIO_CONTROL_FAULTENB_SHIFT                                                                  (0x00000012u)
#define GMAC_SW_MDIO_CONTROL_FAULTENB_MASK                                                                   (0x00040000u)

#define GMAC_SW_MDIO_CONTROL_FAULT_SHIFT                                                                     (0x00000013u)
#define GMAC_SW_MDIO_CONTROL_FAULT_MASK                                                                      (0x00080000u)

#define GMAC_SW_MDIO_CONTROL_PREAMBLE_SHIFT                                                                  (0x00000014u)
#define GMAC_SW_MDIO_CONTROL_PREAMBLE_MASK                                                                   (0x00100000u)

#define GMAC_SW_MDIO_CONTROL_RESERVED2_SHIFT                                                                 (0x00000015u)
#define GMAC_SW_MDIO_CONTROL_RESERVED2_MASK                                                                  (0x00E00000u)

#define GMAC_SW_MDIO_CONTROL_HIGHEST_USER_CHANNEL_SHIFT                                                      (0x00000018u)
#define GMAC_SW_MDIO_CONTROL_HIGHEST_USER_CHANNEL_MASK                                                       (0x1F000000u)

#define GMAC_SW_MDIO_CONTROL_RESERVED1_SHIFT                                                                 (0x0000001Du)
#define GMAC_SW_MDIO_CONTROL_RESERVED1_MASK                                                                  (0x20000000u)

#define GMAC_SW_MDIO_CONTROL_ENABLE_SHIFT                                                                    (0x0000001Eu)
#define GMAC_SW_MDIO_CONTROL_ENABLE_MASK                                                                     (0x40000000u)

#define GMAC_SW_MDIO_CONTROL_IDLE_SHIFT                                                                      (0x0000001Fu)
#define GMAC_SW_MDIO_CONTROL_IDLE_MASK                                                                       (0x80000000u)


/*!************************************** GMAC_SW_MDIO_ALIVE ****************************************/

#define GMAC_SW_MDIO_ALIVE_ALIVE_SHIFT                                                                       (0x00000000u)
#define GMAC_SW_MDIO_ALIVE_ALIVE_MASK                                                                        (0xFFFFFFFFu)


/*!*************************************** GMAC_SW_MDIO_LINK *****************************************/

#define GMAC_SW_MDIO_LINK_LINK_SHIFT                                                                         (0x00000000u)
#define GMAC_SW_MDIO_LINK_LINK_MASK                                                                          (0xFFFFFFFFu)


/*!************************************ GMAC_SW_MDIO_LINKINTRAW **************************************/

#define GMAC_SW_MDIO_LINKINTRAW_LINKINTRAW_SHIFT                                                             (0x00000000u)
#define GMAC_SW_MDIO_LINKINTRAW_LINKINTRAW_MASK                                                              (0x00000003u)

#define GMAC_SW_MDIO_LINKINTRAW_RESERVED1_SHIFT                                                              (0x00000002u)
#define GMAC_SW_MDIO_LINKINTRAW_RESERVED1_MASK                                                               (0xFFFFFFFCu)


/*!********************************** GMAC_SW_MDIO_LINKINTMASKED ************************************/

#define GMAC_SW_MDIO_LINKINTMASKED_LINKINTMASKED_SHIFT                                                       (0x00000000u)
#define GMAC_SW_MDIO_LINKINTMASKED_LINKINTMASKED_MASK                                                        (0x00000003u)

#define GMAC_SW_MDIO_LINKINTMASKED_RESERVED1_SHIFT                                                           (0x00000002u)
#define GMAC_SW_MDIO_LINKINTMASKED_RESERVED1_MASK                                                            (0xFFFFFFFCu)


/*!************************************ GMAC_SW_MDIO_USERINTRAW **************************************/

#define GMAC_SW_MDIO_USERINTRAW_USERINTRAW_SHIFT                                                             (0x00000000u)
#define GMAC_SW_MDIO_USERINTRAW_USERINTRAW_MASK                                                              (0x00000003u)

#define GMAC_SW_MDIO_USERINTRAW_RESERVED1_SHIFT                                                              (0x00000002u)
#define GMAC_SW_MDIO_USERINTRAW_RESERVED1_MASK                                                               (0xFFFFFFFCu)


/*!********************************** GMAC_SW_MDIO_USERINTMASKED ************************************/

#define GMAC_SW_MDIO_USERINTMASKED_USERINTMASKED_SHIFT                                                       (0x00000000u)
#define GMAC_SW_MDIO_USERINTMASKED_USERINTMASKED_MASK                                                        (0x00000003u)

#define GMAC_SW_MDIO_USERINTMASKED_RESERVED1_SHIFT                                                           (0x00000002u)
#define GMAC_SW_MDIO_USERINTMASKED_RESERVED1_MASK                                                            (0xFFFFFFFCu)


/*!********************************** GMAC_SW_MDIO_USERINTMASKSET ************************************/

#define GMAC_SW_MDIO_USERINTMASKSET_USERINTMASKSET_SHIFT                                                     (0x00000000u)
#define GMAC_SW_MDIO_USERINTMASKSET_USERINTMASKSET_MASK                                                      (0x00000003u)

#define GMAC_SW_MDIO_USERINTMASKSET_RESERVED1_SHIFT                                                          (0x00000002u)
#define GMAC_SW_MDIO_USERINTMASKSET_RESERVED1_MASK                                                           (0xFFFFFFFCu)


/*!********************************** GMAC_SW_MDIO_USERINTMASKCLR ************************************/

#define GMAC_SW_MDIO_USERINTMASKCLR_USERINTMASKCLEAR_SHIFT                                                   (0x00000000u)
#define GMAC_SW_MDIO_USERINTMASKCLR_USERINTMASKCLEAR_MASK                                                    (0x00000003u)

#define GMAC_SW_MDIO_USERINTMASKCLR_RESERVED1_SHIFT                                                          (0x00000002u)
#define GMAC_SW_MDIO_USERINTMASKCLR_RESERVED1_MASK                                                           (0xFFFFFFFCu)


/*!*********************************** GMAC_SW_MDIO_USERACCESS0 *************************************/

#define GMAC_SW_MDIO_USERACCESS0_DATA_SHIFT                                                                  (0x00000000u)
#define GMAC_SW_MDIO_USERACCESS0_DATA_MASK                                                                   (0x0000FFFFu)

#define GMAC_SW_MDIO_USERACCESS0_PHYADR_SHIFT                                                                (0x00000010u)
#define GMAC_SW_MDIO_USERACCESS0_PHYADR_MASK                                                                 (0x001F0000u)

#define GMAC_SW_MDIO_USERACCESS0_REGADR_SHIFT                                                                (0x00000015u)
#define GMAC_SW_MDIO_USERACCESS0_REGADR_MASK                                                                 (0x03E00000u)

#define GMAC_SW_MDIO_USERACCESS0_RESERVED1_SHIFT                                                             (0x0000001Au)
#define GMAC_SW_MDIO_USERACCESS0_RESERVED1_MASK                                                              (0x1C000000u)

#define GMAC_SW_MDIO_USERACCESS0_ACK_SHIFT                                                                   (0x0000001Du)
#define GMAC_SW_MDIO_USERACCESS0_ACK_MASK                                                                    (0x20000000u)

#define GMAC_SW_MDIO_USERACCESS0_WRITE_SHIFT                                                                 (0x0000001Eu)
#define GMAC_SW_MDIO_USERACCESS0_WRITE_MASK                                                                  (0x40000000u)

#define GMAC_SW_MDIO_USERACCESS0_GO_SHIFT                                                                    (0x0000001Fu)
#define GMAC_SW_MDIO_USERACCESS0_GO_MASK                                                                     (0x80000000u)


/*!*********************************** GMAC_SW_MDIO_USERPHYSEL0 *************************************/

#define GMAC_SW_MDIO_USERPHYSEL0_PHYADDRMON_SHIFT                                                            (0x00000000u)
#define GMAC_SW_MDIO_USERPHYSEL0_PHYADDRMON_MASK                                                             (0x0000001Fu)

#define GMAC_SW_MDIO_USERPHYSEL0_RESERVED2_SHIFT                                                             (0x00000005u)
#define GMAC_SW_MDIO_USERPHYSEL0_RESERVED2_MASK                                                              (0x00000020u)

#define GMAC_SW_MDIO_USERPHYSEL0_LINKINTENB_SHIFT                                                            (0x00000006u)
#define GMAC_SW_MDIO_USERPHYSEL0_LINKINTENB_MASK                                                             (0x00000040u)

#define GMAC_SW_MDIO_USERPHYSEL0_LINKSEL_SHIFT                                                               (0x00000007u)
#define GMAC_SW_MDIO_USERPHYSEL0_LINKSEL_MASK                                                                (0x00000080u)

#define GMAC_SW_MDIO_USERPHYSEL0_RESERVED1_SHIFT                                                             (0x00000008u)
#define GMAC_SW_MDIO_USERPHYSEL0_RESERVED1_MASK                                                              (0xFFFFFF00u)


/*!*********************************** GMAC_SW_MDIO_USERACCESS1 *************************************/

#define GMAC_SW_MDIO_USERACCESS1_DATA_SHIFT                                                                  (0x00000000u)
#define GMAC_SW_MDIO_USERACCESS1_DATA_MASK                                                                   (0x0000FFFFu)

#define GMAC_SW_MDIO_USERACCESS1_PHYADR_SHIFT                                                                (0x00000010u)
#define GMAC_SW_MDIO_USERACCESS1_PHYADR_MASK                                                                 (0x001F0000u)

#define GMAC_SW_MDIO_USERACCESS1_REGADR_SHIFT                                                                (0x00000015u)
#define GMAC_SW_MDIO_USERACCESS1_REGADR_MASK                                                                 (0x03E00000u)

#define GMAC_SW_MDIO_USERACCESS1_RESERVED1_SHIFT                                                             (0x0000001Au)
#define GMAC_SW_MDIO_USERACCESS1_RESERVED1_MASK                                                              (0x1C000000u)

#define GMAC_SW_MDIO_USERACCESS1_ACK_SHIFT                                                                   (0x0000001Du)
#define GMAC_SW_MDIO_USERACCESS1_ACK_MASK                                                                    (0x20000000u)

#define GMAC_SW_MDIO_USERACCESS1_WRITE_SHIFT                                                                 (0x0000001Eu)
#define GMAC_SW_MDIO_USERACCESS1_WRITE_MASK                                                                  (0x40000000u)

#define GMAC_SW_MDIO_USERACCESS1_GO_SHIFT                                                                    (0x0000001Fu)
#define GMAC_SW_MDIO_USERACCESS1_GO_MASK                                                                     (0x80000000u)


/*!*********************************** GMAC_SW_MDIO_USERPHYSEL1 *************************************/

#define GMAC_SW_MDIO_USERPHYSEL1_DATA_SHIFT                                                                  (0x00000000u)
#define GMAC_SW_MDIO_USERPHYSEL1_DATA_MASK                                                                   (0x0000FFFFu)

#define GMAC_SW_MDIO_USERPHYSEL1_PHYADR_SHIFT                                                                (0x00000010u)
#define GMAC_SW_MDIO_USERPHYSEL1_PHYADR_MASK                                                                 (0x001F0000u)

#define GMAC_SW_MDIO_USERPHYSEL1_REGADR_SHIFT                                                                (0x00000015u)
#define GMAC_SW_MDIO_USERPHYSEL1_REGADR_MASK                                                                 (0x03E00000u)

#define GMAC_SW_MDIO_USERPHYSEL1_RESERVED1_SHIFT                                                             (0x0000001Au)
#define GMAC_SW_MDIO_USERPHYSEL1_RESERVED1_MASK                                                              (0x1C000000u)

#define GMAC_SW_MDIO_USERPHYSEL1_ACK_SHIFT                                                                   (0x0000001Du)
#define GMAC_SW_MDIO_USERPHYSEL1_ACK_MASK                                                                    (0x20000000u)

#define GMAC_SW_MDIO_USERPHYSEL1_WRITE_SHIFT                                                                 (0x0000001Eu)
#define GMAC_SW_MDIO_USERPHYSEL1_WRITE_MASK                                                                  (0x40000000u)

#define GMAC_SW_MDIO_USERPHYSEL1_GO_SHIFT                                                                    (0x0000001Fu)
#define GMAC_SW_MDIO_USERPHYSEL1_GO_MASK                                                                     (0x80000000u)


/*!**************************************************************************************************
* End of File
****************************************************************************************************/
#ifdef __cplusplus
}
#endif

#endif  /* _HW_GMACSW_MDIO_H_ */
