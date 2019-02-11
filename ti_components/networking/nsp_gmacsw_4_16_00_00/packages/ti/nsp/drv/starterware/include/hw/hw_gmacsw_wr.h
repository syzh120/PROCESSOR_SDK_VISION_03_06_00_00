/*
 *
 * hw_gmacsw_wr.h - register-level header file for GMAC_SW
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

#ifndef _HW_GMACSW_WR_H_
#define _HW_GMACSW_WR_H_

#ifdef __cplusplus
extern "C"
{
#endif


/*!**************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define GMAC_SW_IDVER                                                                                       (0x00000000u)
#define GMAC_SW_SOFT_RESET                                                                                  (0x00000004u)
#define GMAC_SW_CONTROL                                                                                     (0x00000008u)
#define GMAC_SW_INT_CONTROL                                                                                 (0x0000000Cu)
#define GMAC_SW_C0_RX_THRESH_EN                                                                             (0x00000010u)
#define GMAC_SW_C0_RX_EN                                                                                    (0x00000014u)
#define GMAC_SW_C0_TX_EN                                                                                    (0x00000018u)
#define GMAC_SW_C0_MISC_EN                                                                                  (0x0000001Cu)
#define GMAC_SW_C1_RX_THRESH_EN                                                                             (0x00000020u)
#define GMAC_SW_C1_RX_EN                                                                                    (0x00000024u)
#define GMAC_SW_C1_TX_EN                                                                                    (0x00000028u)
#define GMAC_SW_C1_MISC_EN                                                                                  (0x0000002Cu)
#define GMAC_SW_C2_RX_THRESH_EN                                                                             (0x00000030u)
#define GMAC_SW_C2_RX_EN                                                                                    (0x00000034u)
#define GMAC_SW_C2_TX_EN                                                                                    (0x00000038u)
#define GMAC_SW_C2_MISC_EN                                                                                  (0x0000003Cu)
#define GMAC_SW_C0_RX_THRESH_STAT                                                                           (0x00000040u)
#define GMAC_SW_C0_RX_STAT                                                                                  (0x00000044u)
#define GMAC_SW_C0_TX_STAT                                                                                  (0x00000048u)
#define GMAC_SW_C0_MISC_STAT                                                                                (0x0000004Cu)
#define GMAC_SW_C1_RX_THRESH_STAT                                                                           (0x00000050u)
#define GMAC_SW_C1_RX_STAT                                                                                  (0x00000054u)
#define GMAC_SW_C1_TX_STAT                                                                                  (0x00000058u)
#define GMAC_SW_C1_MISC_STAT                                                                                (0x0000005Cu)
#define GMAC_SW_C2_RX_THRESH_STAT                                                                           (0x00000060u)
#define GMAC_SW_C2_RX_STAT                                                                                  (0x00000064u)
#define GMAC_SW_C2_TX_STAT                                                                                  (0x00000068u)
#define GMAC_SW_C2_MISC_STAT                                                                                (0x0000006Cu)
#define GMAC_SW_C0_RX_IMAX                                                                                  (0x00000070u)
#define GMAC_SW_C0_TX_IMAX                                                                                  (0x00000074u)
#define GMAC_SW_C1_RX_IMAX                                                                                  (0x00000078u)
#define GMAC_SW_C1_TX_IMAX                                                                                  (0x0000007Cu)
#define GMAC_SW_C2_RX_IMAX                                                                                  (0x00000080u)
#define GMAC_SW_C2_TX_IMAX                                                                                  (0x00000084u)
#define GMAC_SW_RGMII_CTL                                                                                   (0x00000088u)


/*!**************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

/*!**************************************** GMAC_SW_IDVER ******************************************/

#define GMAC_SW_IDVER_MINOR_SHIFT                                                                           (0x00000000u)
#define GMAC_SW_IDVER_MINOR_MASK                                                                            (0x0000003Fu)

#define GMAC_SW_IDVER_CUSTOM_SHIFT                                                                          (0x00000006u)
#define GMAC_SW_IDVER_CUSTOM_MASK                                                                           (0x000000C0u)

#define GMAC_SW_IDVER_MAJOR_SHIFT                                                                           (0x00000008u)
#define GMAC_SW_IDVER_MAJOR_MASK                                                                            (0x00000700u)

#define GMAC_SW_IDVER_RTL_SHIFT                                                                             (0x0000000Bu)
#define GMAC_SW_IDVER_RTL_MASK                                                                              (0x0000F800u)

#define GMAC_SW_IDVER_FUNCTION_SHIFT                                                                        (0x00000010u)
#define GMAC_SW_IDVER_FUNCTION_MASK                                                                         (0x0FFF0000u)

#define GMAC_SW_IDVER_RESERVED1_SHIFT                                                                       (0x0000001Cu)
#define GMAC_SW_IDVER_RESERVED1_MASK                                                                        (0x30000000u)

#define GMAC_SW_IDVER_SCHEME_SHIFT                                                                          (0x0000001Eu)
#define GMAC_SW_IDVER_SCHEME_MASK                                                                           (0xC0000000u)


/*!************************************** GMAC_SW_SOFT_RESET ****************************************/

#define GMAC_SW_SOFT_RESET_SOFT_RESET_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_SOFT_RESET_SOFT_RESET_MASK                                                                  (0x00000001u)

#define GMAC_SW_SOFT_RESET_RESERVED1_SHIFT                                                                  (0x00000001u)
#define GMAC_SW_SOFT_RESET_RESERVED1_MASK                                                                   (0xFFFFFFFEu)


/*!*************************************** GMAC_SW_CONTROL *****************************************/

#define GMAC_SW_CONTROL_MMR_IDLEMODE_SHIFT                                                                  (0x00000000u)
#define GMAC_SW_CONTROL_MMR_IDLEMODE_MASK                                                                   (0x00000003u)
#define GMAC_SW_CONTROL_MMR_IDLEMODE_EN_0X1                                                                 (0x00000001u)
#define GMAC_SW_CONTROL_MMR_IDLEMODE_EN_0X2                                                                 (0x00000002u)
#define GMAC_SW_CONTROL_MMR_IDLEMODE_EN_0X3                                                                 (0x00000003u)
#define GMAC_SW_CONTROL_MMR_IDLEMODE_EN_0X0                                                                 (0x00000000u)

#define GMAC_SW_CONTROL_MMR_STDBYMODE_SHIFT                                                                 (0x00000002u)
#define GMAC_SW_CONTROL_MMR_STDBYMODE_MASK                                                                  (0x0000000Cu)
#define GMAC_SW_CONTROL_MMR_STDBYMODE_EN_0X2                                                                (0x00000002u)
#define GMAC_SW_CONTROL_MMR_STDBYMODE_EN_0X0                                                                (0x00000000u)
#define GMAC_SW_CONTROL_MMR_STDBYMODE_EN_0X1                                                                (0x00000001u)
#define GMAC_SW_CONTROL_MMR_STDBYMODE_EN_0X3                                                                (0x00000003u)

#define GMAC_SW_CONTROL_RESERVED1_SHIFT                                                                     (0x00000004u)
#define GMAC_SW_CONTROL_RESERVED1_MASK                                                                      (0xFFFFFFF0u)


/*!************************************* GMAC_SW_INT_CONTROL ***************************************/

#define GMAC_SW_INT_CONTROL_INT_PRESCALE_SHIFT                                                              (0x00000000u)
#define GMAC_SW_INT_CONTROL_INT_PRESCALE_MASK                                                               (0x00000FFFu)

#define GMAC_SW_INT_CONTROL_RESERVED2_SHIFT                                                                 (0x0000000Cu)
#define GMAC_SW_INT_CONTROL_RESERVED2_MASK                                                                  (0x0000F000u)

#define GMAC_SW_INT_CONTROL_INT_PACE_EN_SHIFT                                                               (0x00000010u)
#define GMAC_SW_INT_CONTROL_INT_PACE_EN_MASK                                                                (0x003F0000u)

#define GMAC_SW_INT_CONTROL_RESERVED1_SHIFT                                                                 (0x00000016u)
#define GMAC_SW_INT_CONTROL_RESERVED1_MASK                                                                  (0x7FC00000u)

#define GMAC_SW_INT_CONTROL_INT_TEST_SHIFT                                                                  (0x0000001Fu)
#define GMAC_SW_INT_CONTROL_INT_TEST_MASK                                                                   (0x80000000u)


/*!*********************************** GMAC_SW_C0_RX_THRESH_EN *************************************/

#define GMAC_SW_C0_RX_THRESH_EN_C0_RX_THRESH_EN_SHIFT                                                       (0x00000000u)
#define GMAC_SW_C0_RX_THRESH_EN_C0_RX_THRESH_EN_MASK                                                        (0x000000FFu)

#define GMAC_SW_C0_RX_THRESH_EN_RESERVED1_SHIFT                                                             (0x00000008u)
#define GMAC_SW_C0_RX_THRESH_EN_RESERVED1_MASK                                                              (0xFFFFFF00u)


/*!*************************************** GMAC_SW_C0_RX_EN *****************************************/

#define GMAC_SW_C0_RX_EN_C0_RX_EN_SHIFT                                                                     (0x00000000u)
#define GMAC_SW_C0_RX_EN_C0_RX_EN_MASK                                                                      (0x000000FFu)

#define GMAC_SW_C0_RX_EN_RESERVED1_SHIFT                                                                    (0x00000008u)
#define GMAC_SW_C0_RX_EN_RESERVED1_MASK                                                                     (0xFFFFFF00u)


/*!*************************************** GMAC_SW_C0_TX_EN *****************************************/

#define GMAC_SW_C0_TX_EN_C0_TX_EN_SHIFT                                                                     (0x00000000u)
#define GMAC_SW_C0_TX_EN_C0_TX_EN_MASK                                                                      (0x000000FFu)

#define GMAC_SW_C0_TX_EN_RESERVED1_SHIFT                                                                    (0x00000008u)
#define GMAC_SW_C0_TX_EN_RESERVED1_MASK                                                                     (0xFFFFFF00u)


/*!************************************** GMAC_SW_C0_MISC_EN ****************************************/

#define GMAC_SW_C0_MISC_EN_C0_MISC_EN_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_C0_MISC_EN_C0_MISC_EN_MASK                                                                  (0x0000001Fu)

#define GMAC_SW_C0_MISC_EN_RESERVED1_SHIFT                                                                  (0x00000005u)
#define GMAC_SW_C0_MISC_EN_RESERVED1_MASK                                                                   (0xFFFFFFE0u)


/*!*********************************** GMAC_SW_C1_RX_THRESH_EN *************************************/

#define GMAC_SW_C1_RX_THRESH_EN_C1_RX_THRESH_EN_SHIFT                                                       (0x00000000u)
#define GMAC_SW_C1_RX_THRESH_EN_C1_RX_THRESH_EN_MASK                                                        (0x000000FFu)

#define GMAC_SW_C1_RX_THRESH_EN_RESERVED1_SHIFT                                                             (0x00000008u)
#define GMAC_SW_C1_RX_THRESH_EN_RESERVED1_MASK                                                              (0xFFFFFF00u)


/*!*************************************** GMAC_SW_C1_RX_EN *****************************************/

#define GMAC_SW_C1_RX_EN_C1_RX_EN_SHIFT                                                                     (0x00000000u)
#define GMAC_SW_C1_RX_EN_C1_RX_EN_MASK                                                                      (0x000000FFu)

#define GMAC_SW_C1_RX_EN_RESERVED1_SHIFT                                                                    (0x00000008u)
#define GMAC_SW_C1_RX_EN_RESERVED1_MASK                                                                     (0xFFFFFF00u)


/*!*************************************** GMAC_SW_C1_TX_EN *****************************************/

#define GMAC_SW_C1_TX_EN_C1_TX_EN_SHIFT                                                                     (0x00000000u)
#define GMAC_SW_C1_TX_EN_C1_TX_EN_MASK                                                                      (0x000000FFu)

#define GMAC_SW_C1_TX_EN_RESERVED1_SHIFT                                                                    (0x00000008u)
#define GMAC_SW_C1_TX_EN_RESERVED1_MASK                                                                     (0xFFFFFF00u)


/*!************************************** GMAC_SW_C1_MISC_EN ****************************************/

#define GMAC_SW_C1_MISC_EN_C1_MISC_EN_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_C1_MISC_EN_C1_MISC_EN_MASK                                                                  (0x0000001Fu)

#define GMAC_SW_C1_MISC_EN_RESERVED1_SHIFT                                                                  (0x00000005u)
#define GMAC_SW_C1_MISC_EN_RESERVED1_MASK                                                                   (0xFFFFFFE0u)


/*!*********************************** GMAC_SW_C2_RX_THRESH_EN *************************************/

#define GMAC_SW_C2_RX_THRESH_EN_C2_RX_THRESH_EN_SHIFT                                                       (0x00000000u)
#define GMAC_SW_C2_RX_THRESH_EN_C2_RX_THRESH_EN_MASK                                                        (0x000000FFu)

#define GMAC_SW_C2_RX_THRESH_EN_RESERVED1_SHIFT                                                             (0x00000008u)
#define GMAC_SW_C2_RX_THRESH_EN_RESERVED1_MASK                                                              (0xFFFFFF00u)


/*!*************************************** GMAC_SW_C2_RX_EN *****************************************/

#define GMAC_SW_C2_RX_EN_C2_RX_EN_SHIFT                                                                     (0x00000000u)
#define GMAC_SW_C2_RX_EN_C2_RX_EN_MASK                                                                      (0x000000FFu)

#define GMAC_SW_C2_RX_EN_RESERVED1_SHIFT                                                                    (0x00000008u)
#define GMAC_SW_C2_RX_EN_RESERVED1_MASK                                                                     (0xFFFFFF00u)


/*!*************************************** GMAC_SW_C2_TX_EN *****************************************/

#define GMAC_SW_C2_TX_EN_C2_TX_EN_SHIFT                                                                     (0x00000000u)
#define GMAC_SW_C2_TX_EN_C2_TX_EN_MASK                                                                      (0x000000FFu)

#define GMAC_SW_C2_TX_EN_RESERVED1_SHIFT                                                                    (0x00000008u)
#define GMAC_SW_C2_TX_EN_RESERVED1_MASK                                                                     (0xFFFFFF00u)


/*!************************************** GMAC_SW_C2_MISC_EN ****************************************/

#define GMAC_SW_C2_MISC_EN_C2_MISC_EN_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_C2_MISC_EN_C2_MISC_EN_MASK                                                                  (0x0000001Fu)

#define GMAC_SW_C2_MISC_EN_RESERVED1_SHIFT                                                                  (0x00000005u)
#define GMAC_SW_C2_MISC_EN_RESERVED1_MASK                                                                   (0xFFFFFFE0u)


/*!********************************** GMAC_SW_C0_RX_THRESH_STAT ************************************/

#define GMAC_SW_C0_RX_THRESH_STAT_C0_RX_THRESH_STAT_SHIFT                                                   (0x00000000u)
#define GMAC_SW_C0_RX_THRESH_STAT_C0_RX_THRESH_STAT_MASK                                                    (0x000000FFu)

#define GMAC_SW_C0_RX_THRESH_STAT_RESERVED1_SHIFT                                                           (0x00000008u)
#define GMAC_SW_C0_RX_THRESH_STAT_RESERVED1_MASK                                                            (0xFFFFFF00u)


/*!************************************** GMAC_SW_C0_RX_STAT ****************************************/

#define GMAC_SW_C0_RX_STAT_C0_RX_STAT_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_C0_RX_STAT_C0_RX_STAT_MASK                                                                  (0x000000FFu)

#define GMAC_SW_C0_RX_STAT_RESERVED1_SHIFT                                                                  (0x00000008u)
#define GMAC_SW_C0_RX_STAT_RESERVED1_MASK                                                                   (0xFFFFFF00u)


/*!************************************** GMAC_SW_C0_TX_STAT ****************************************/

#define GMAC_SW_C0_TX_STAT_C0_TX_STAT_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_C0_TX_STAT_C0_TX_STAT_MASK                                                                  (0x000000FFu)

#define GMAC_SW_C0_TX_STAT_RESERVED1_SHIFT                                                                  (0x00000008u)
#define GMAC_SW_C0_TX_STAT_RESERVED1_MASK                                                                   (0xFFFFFF00u)


/*!************************************* GMAC_SW_C0_MISC_STAT ***************************************/

#define GMAC_SW_C0_MISC_STAT_C0_MISC_STAT_SHIFT                                                             (0x00000000u)
#define GMAC_SW_C0_MISC_STAT_C0_MISC_STAT_MASK                                                              (0x0000001Fu)

#define GMAC_SW_C0_MISC_STAT_RESERVED1_SHIFT                                                                (0x00000005u)
#define GMAC_SW_C0_MISC_STAT_RESERVED1_MASK                                                                 (0xFFFFFFE0u)


/*!********************************** GMAC_SW_C1_RX_THRESH_STAT ************************************/

#define GMAC_SW_C1_RX_THRESH_STAT_C1_RX_THRESH_STAT_SHIFT                                                   (0x00000000u)
#define GMAC_SW_C1_RX_THRESH_STAT_C1_RX_THRESH_STAT_MASK                                                    (0x000000FFu)

#define GMAC_SW_C1_RX_THRESH_STAT_RESERVED1_SHIFT                                                           (0x00000008u)
#define GMAC_SW_C1_RX_THRESH_STAT_RESERVED1_MASK                                                            (0xFFFFFF00u)


/*!************************************** GMAC_SW_C1_RX_STAT ****************************************/

#define GMAC_SW_C1_RX_STAT_C1_RX_STAT_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_C1_RX_STAT_C1_RX_STAT_MASK                                                                  (0x000000FFu)

#define GMAC_SW_C1_RX_STAT_RESERVED1_SHIFT                                                                  (0x00000008u)
#define GMAC_SW_C1_RX_STAT_RESERVED1_MASK                                                                   (0xFFFFFF00u)


/*!************************************** GMAC_SW_C1_TX_STAT ****************************************/

#define GMAC_SW_C1_TX_STAT_C1_TX_STAT_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_C1_TX_STAT_C1_TX_STAT_MASK                                                                  (0x000000FFu)

#define GMAC_SW_C1_TX_STAT_RESERVED1_SHIFT                                                                  (0x00000008u)
#define GMAC_SW_C1_TX_STAT_RESERVED1_MASK                                                                   (0xFFFFFF00u)


/*!************************************* GMAC_SW_C1_MISC_STAT ***************************************/

#define GMAC_SW_C1_MISC_STAT_C1_MISC_STAT_SHIFT                                                             (0x00000000u)
#define GMAC_SW_C1_MISC_STAT_C1_MISC_STAT_MASK                                                              (0x0000001Fu)

#define GMAC_SW_C1_MISC_STAT_RESERVED1_SHIFT                                                                (0x00000005u)
#define GMAC_SW_C1_MISC_STAT_RESERVED1_MASK                                                                 (0xFFFFFFE0u)


/*!********************************** GMAC_SW_C2_RX_THRESH_STAT ************************************/

#define GMAC_SW_C2_RX_THRESH_STAT_C2_RX_THRESH_STAT_SHIFT                                                   (0x00000000u)
#define GMAC_SW_C2_RX_THRESH_STAT_C2_RX_THRESH_STAT_MASK                                                    (0x000000FFu)

#define GMAC_SW_C2_RX_THRESH_STAT_RESERVED1_SHIFT                                                           (0x00000008u)
#define GMAC_SW_C2_RX_THRESH_STAT_RESERVED1_MASK                                                            (0xFFFFFF00u)


/*!************************************** GMAC_SW_C2_RX_STAT ****************************************/

#define GMAC_SW_C2_RX_STAT_C2_RX_STAT_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_C2_RX_STAT_C2_RX_STAT_MASK                                                                  (0x000000FFu)

#define GMAC_SW_C2_RX_STAT_RESERVED1_SHIFT                                                                  (0x00000008u)
#define GMAC_SW_C2_RX_STAT_RESERVED1_MASK                                                                   (0xFFFFFF00u)


/*!************************************** GMAC_SW_C2_TX_STAT ****************************************/

#define GMAC_SW_C2_TX_STAT_C2_TX_STAT_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_C2_TX_STAT_C2_TX_STAT_MASK                                                                  (0x000000FFu)

#define GMAC_SW_C2_TX_STAT_RESERVED1_SHIFT                                                                  (0x00000008u)
#define GMAC_SW_C2_TX_STAT_RESERVED1_MASK                                                                   (0xFFFFFF00u)


/*!************************************* GMAC_SW_C2_MISC_STAT ***************************************/

#define GMAC_SW_C2_MISC_STAT_C2_MISC_STAT_SHIFT                                                             (0x00000000u)
#define GMAC_SW_C2_MISC_STAT_C2_MISC_STAT_MASK                                                              (0x0000001Fu)

#define GMAC_SW_C2_MISC_STAT_RESERVED1_SHIFT                                                                (0x00000005u)
#define GMAC_SW_C2_MISC_STAT_RESERVED1_MASK                                                                 (0xFFFFFFE0u)


/*!************************************** GMAC_SW_C0_RX_IMAX ****************************************/

#define GMAC_SW_C0_RX_IMAX_C0_RX_IMAX_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_C0_RX_IMAX_C0_RX_IMAX_MASK                                                                  (0x0000003Fu)

#define GMAC_SW_C0_RX_IMAX_RESERVED1_SHIFT                                                                  (0x00000006u)
#define GMAC_SW_C0_RX_IMAX_RESERVED1_MASK                                                                   (0xFFFFFFC0u)


/*!************************************** GMAC_SW_C0_TX_IMAX ****************************************/

#define GMAC_SW_C0_TX_IMAX_C0_TX_IMAX_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_C0_TX_IMAX_C0_TX_IMAX_MASK                                                                  (0x0000003Fu)

#define GMAC_SW_C0_TX_IMAX_RESERVED1_SHIFT                                                                  (0x00000006u)
#define GMAC_SW_C0_TX_IMAX_RESERVED1_MASK                                                                   (0xFFFFFFC0u)


/*!************************************** GMAC_SW_C1_RX_IMAX ****************************************/

#define GMAC_SW_C1_RX_IMAX_C1_RX_IMAX_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_C1_RX_IMAX_C1_RX_IMAX_MASK                                                                  (0x0000003Fu)

#define GMAC_SW_C1_RX_IMAX_RESERVED1_SHIFT                                                                  (0x00000006u)
#define GMAC_SW_C1_RX_IMAX_RESERVED1_MASK                                                                   (0xFFFFFFC0u)


/*!************************************** GMAC_SW_C1_TX_IMAX ****************************************/

#define GMAC_SW_C1_TX_IMAX_C1_TX_IMAX_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_C1_TX_IMAX_C1_TX_IMAX_MASK                                                                  (0x0000003Fu)

#define GMAC_SW_C1_TX_IMAX_RESERVED1_SHIFT                                                                  (0x00000006u)
#define GMAC_SW_C1_TX_IMAX_RESERVED1_MASK                                                                   (0xFFFFFFC0u)


/*!************************************** GMAC_SW_C2_RX_IMAX ****************************************/

#define GMAC_SW_C2_RX_IMAX_C2_RX_IMAX_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_C2_RX_IMAX_C2_RX_IMAX_MASK                                                                  (0x0000003Fu)

#define GMAC_SW_C2_RX_IMAX_RESERVED1_SHIFT                                                                  (0x00000006u)
#define GMAC_SW_C2_RX_IMAX_RESERVED1_MASK                                                                   (0xFFFFFFC0u)


/*!************************************** GMAC_SW_C2_TX_IMAX ****************************************/

#define GMAC_SW_C2_TX_IMAX_C2_TX_IMAX_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_C2_TX_IMAX_C2_TX_IMAX_MASK                                                                  (0x0000003Fu)

#define GMAC_SW_C2_TX_IMAX_RESERVED1_SHIFT                                                                  (0x00000006u)
#define GMAC_SW_C2_TX_IMAX_RESERVED1_MASK                                                                   (0xFFFFFFC0u)


/*!************************************** GMAC_SW_RGMII_CTL ****************************************/

#define GMAC_SW_RGMII_CTL_RGMII1_LINK_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_RGMII_CTL_RGMII1_LINK_MASK                                                                  (0x00000001u)

#define GMAC_SW_RGMII_CTL_RGMII1_SPEED_SHIFT                                                                (0x00000001u)
#define GMAC_SW_RGMII_CTL_RGMII1_SPEED_MASK                                                                 (0x00000006u)

#define GMAC_SW_RGMII_CTL_RGMII1_FULLDUPLEX_SHIFT                                                           (0x00000003u)
#define GMAC_SW_RGMII_CTL_RGMII1_FULLDUPLEX_MASK                                                            (0x00000008u)

#define GMAC_SW_RGMII_CTL_RGMII2_LINK_SHIFT                                                                 (0x00000004u)
#define GMAC_SW_RGMII_CTL_RGMII2_LINK_MASK                                                                  (0x00000010u)

#define GMAC_SW_RGMII_CTL_RGMII2_SPEED_SHIFT                                                                (0x00000005u)
#define GMAC_SW_RGMII_CTL_RGMII2_SPEED_MASK                                                                 (0x00000060u)

#define GMAC_SW_RGMII_CTL_RGMII2_FULLDUPLEX_SHIFT                                                           (0x00000007u)
#define GMAC_SW_RGMII_CTL_RGMII2_FULLDUPLEX_MASK                                                            (0x00000080u)

#define GMAC_SW_RGMII_CTL_RESERVED1_SHIFT                                                                   (0x00000008u)
#define GMAC_SW_RGMII_CTL_RESERVED1_MASK                                                                    (0xFFFFFF00u)


/*!**************************************************************************************************
* End of File
****************************************************************************************************/
#ifdef __cplusplus
}
#endif

#endif  /* _HW_GMACSW_WR_H_ */
