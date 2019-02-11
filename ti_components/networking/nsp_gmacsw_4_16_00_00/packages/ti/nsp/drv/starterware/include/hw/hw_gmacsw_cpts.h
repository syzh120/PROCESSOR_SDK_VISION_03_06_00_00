/*
 *
 * hw_gmacsw_cpts.h - register-level header file for GMAC_SW
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

#ifndef _HW_GMACSW_CPTS_H_
#define _HW_GMACSW_CPTS_H_

#ifdef __cplusplus
extern "C"
{
#endif


/*!**************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define GMAC_SW_CPTS_IDVER                                                                                  (0x00000000u)
#define GMAC_SW_CPTS_CONTROL                                                                                (0x00000004u)
#define GMAC_SW_CPTS_TS_PUSH                                                                                (0x0000000Cu)
#define GMAC_SW_CPTS_TS_LOAD_VAL                                                                            (0x00000010u)
#define GMAC_SW_CPTS_TS_LOAD_EN                                                                             (0x00000014u)
#define GMAC_SW_CPTS_INTSTAT_RAW                                                                            (0x00000020u)
#define GMAC_SW_CPTS_INTSTAT_MASKED                                                                         (0x00000024u)
#define GMAC_SW_CPTS_INT_ENABLE                                                                             (0x00000028u)
#define GMAC_SW_CPTS_EVENT_POP                                                                              (0x00000030u)
#define GMAC_SW_CPTS_EVENT_LOW                                                                              (0x00000034u)
#define GMAC_SW_CPTS_EVENT_HIGH                                                                             (0x00000038u)


/*!**************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

/*!************************************** GMAC_SW_CPTS_IDVER ****************************************/

#define GMAC_SW_CPTS_IDVER_MINOR_VER_SHIFT                                                                  (0x00000000u)
#define GMAC_SW_CPTS_IDVER_MINOR_VER_MASK                                                                   (0x000000FFu)

#define GMAC_SW_CPTS_IDVER_MAJOR_VER_SHIFT                                                                  (0x00000008u)
#define GMAC_SW_CPTS_IDVER_MAJOR_VER_MASK                                                                   (0x00000700u)

#define GMAC_SW_CPTS_IDVER_RTL_VER_SHIFT                                                                    (0x0000000Bu)
#define GMAC_SW_CPTS_IDVER_RTL_VER_MASK                                                                     (0x0000F800u)

#define GMAC_SW_CPTS_IDVER_TX_IDENT_SHIFT                                                                   (0x00000010u)
#define GMAC_SW_CPTS_IDVER_TX_IDENT_MASK                                                                    (0xFFFF0000u)


/*!************************************* GMAC_SW_CPTS_CONTROL ***************************************/

#define GMAC_SW_CPTS_CONTROL_CPTS_EN_SHIFT                                                                  (0x00000000u)
#define GMAC_SW_CPTS_CONTROL_CPTS_EN_MASK                                                                   (0x00000001u)

#define GMAC_SW_CPTS_CONTROL_INT_TEST_SHIFT                                                                 (0x00000001u)
#define GMAC_SW_CPTS_CONTROL_INT_TEST_MASK                                                                  (0x00000002u)

#define GMAC_SW_CPTS_CONTROL_RESERVED2_SHIFT                                                                (0x00000002u)
#define GMAC_SW_CPTS_CONTROL_RESERVED2_MASK                                                                 (0x000000FCu)

#define GMAC_SW_CPTS_CONTROL_HW1_TS_PUSH_EN_SHIFT                                                           (0x00000008u)
#define GMAC_SW_CPTS_CONTROL_HW1_TS_PUSH_EN_MASK                                                            (0x00000100u)

#define GMAC_SW_CPTS_CONTROL_HW2_TS_PUSH_EN_SHIFT                                                           (0x00000009u)
#define GMAC_SW_CPTS_CONTROL_HW2_TS_PUSH_EN_MASK                                                            (0x00000200u)

#define GMAC_SW_CPTS_CONTROL_HW3_TS_PUSH_EN_SHIFT                                                           (0x0000000Au)
#define GMAC_SW_CPTS_CONTROL_HW3_TS_PUSH_EN_MASK                                                            (0x00000400u)

#define GMAC_SW_CPTS_CONTROL_HW4_TS_PUSH_EN_SHIFT                                                           (0x0000000Bu)
#define GMAC_SW_CPTS_CONTROL_HW4_TS_PUSH_EN_MASK                                                            (0x00000800u)

#define GMAC_SW_CPTS_CONTROL_RESERVED1_SHIFT                                                                (0x0000000Cu)
#define GMAC_SW_CPTS_CONTROL_RESERVED1_MASK                                                                 (0xFFFFF000u)


/*!************************************* GMAC_SW_CPTS_TS_PUSH ***************************************/

#define GMAC_SW_CPTS_TS_PUSH_TS_PUSH_SHIFT                                                                  (0x00000000u)
#define GMAC_SW_CPTS_TS_PUSH_TS_PUSH_MASK                                                                   (0x00000001u)

#define GMAC_SW_CPTS_TS_PUSH_RESERVED1_SHIFT                                                                (0x00000001u)
#define GMAC_SW_CPTS_TS_PUSH_RESERVED1_MASK                                                                 (0xFFFFFFFEu)


/*!*********************************** GMAC_SW_CPTS_TS_LOAD_VAL *************************************/

#define GMAC_SW_CPTS_TS_LOAD_VAL_TS_LOAD_VAL_SHIFT                                                          (0x00000000u)
#define GMAC_SW_CPTS_TS_LOAD_VAL_TS_LOAD_VAL_MASK                                                           (0xFFFFFFFFu)


/*!*********************************** GMAC_SW_CPTS_TS_LOAD_EN *************************************/

#define GMAC_SW_CPTS_TS_LOAD_EN_TS_LOAD_EN_SHIFT                                                            (0x00000000u)
#define GMAC_SW_CPTS_TS_LOAD_EN_TS_LOAD_EN_MASK                                                             (0x00000001u)

#define GMAC_SW_CPTS_TS_LOAD_EN_RESERVED1_SHIFT                                                             (0x00000001u)
#define GMAC_SW_CPTS_TS_LOAD_EN_RESERVED1_MASK                                                              (0xFFFFFFFEu)


/*!*********************************** GMAC_SW_CPTS_INTSTAT_RAW *************************************/

#define GMAC_SW_CPTS_INTSTAT_RAW_TS_PEND_RAW_SHIFT                                                          (0x00000000u)
#define GMAC_SW_CPTS_INTSTAT_RAW_TS_PEND_RAW_MASK                                                           (0x00000001u)

#define GMAC_SW_CPTS_INTSTAT_RAW_RESERVED1_SHIFT                                                            (0x00000001u)
#define GMAC_SW_CPTS_INTSTAT_RAW_RESERVED1_MASK                                                             (0xFFFFFFFEu)


/*!********************************* GMAC_SW_CPTS_INTSTAT_MASKED ***********************************/

#define GMAC_SW_CPTS_INTSTAT_MASKED_TS_PEND_SHIFT                                                           (0x00000000u)
#define GMAC_SW_CPTS_INTSTAT_MASKED_TS_PEND_MASK                                                            (0x00000001u)

#define GMAC_SW_CPTS_INTSTAT_MASKED_RESERVED1_SHIFT                                                         (0x00000001u)
#define GMAC_SW_CPTS_INTSTAT_MASKED_RESERVED1_MASK                                                          (0xFFFFFFFEu)


/*!*********************************** GMAC_SW_CPTS_INT_ENABLE *************************************/

#define GMAC_SW_CPTS_INT_ENABLE_TS_PEND_EN_SHIFT                                                            (0x00000000u)
#define GMAC_SW_CPTS_INT_ENABLE_TS_PEND_EN_MASK                                                             (0x00000001u)

#define GMAC_SW_CPTS_INT_ENABLE_RESERVED1_SHIFT                                                             (0x00000001u)
#define GMAC_SW_CPTS_INT_ENABLE_RESERVED1_MASK                                                              (0xFFFFFFFEu)


/*!************************************ GMAC_SW_CPTS_EVENT_POP **************************************/

#define GMAC_SW_CPTS_EVENT_POP_EVENT_POP_SHIFT                                                              (0x00000000u)
#define GMAC_SW_CPTS_EVENT_POP_EVENT_POP_MASK                                                               (0x00000001u)

#define GMAC_SW_CPTS_EVENT_POP_RESERVED1_SHIFT                                                              (0x00000001u)
#define GMAC_SW_CPTS_EVENT_POP_RESERVED1_MASK                                                               (0xFFFFFFFEu)


/*!************************************ GMAC_SW_CPTS_EVENT_LOW **************************************/

#define GMAC_SW_CPTS_EVENT_LOW_TIME_STAMP_SHIFT                                                             (0x00000000u)
#define GMAC_SW_CPTS_EVENT_LOW_TIME_STAMP_MASK                                                              (0xFFFFFFFFu)


/*!*********************************** GMAC_SW_CPTS_EVENT_HIGH *************************************/

#define GMAC_SW_CPTS_EVENT_HIGH_SEQUENCE_ID_SHIFT                                                           (0x00000000u)
#define GMAC_SW_CPTS_EVENT_HIGH_SEQUENCE_ID_MASK                                                            (0x0000FFFFu)

#define GMAC_SW_CPTS_EVENT_HIGH_MESSAGE_TYPE_SHIFT                                                          (0x00000010u)
#define GMAC_SW_CPTS_EVENT_HIGH_MESSAGE_TYPE_MASK                                                           (0x000F0000u)

#define GMAC_SW_CPTS_EVENT_HIGH_EVENT_TYPE_SHIFT                                                            (0x00000014u)
#define GMAC_SW_CPTS_EVENT_HIGH_EVENT_TYPE_MASK                                                             (0x00F00000u)

#define GMAC_SW_CPTS_EVENT_HIGH_PORT_NUMBER_SHIFT                                                           (0x00000018u)
#define GMAC_SW_CPTS_EVENT_HIGH_PORT_NUMBER_MASK                                                            (0x1F000000u)

#define GMAC_SW_CPTS_EVENT_HIGH_RESERVED1_SHIFT                                                             (0x0000001Du)
#define GMAC_SW_CPTS_EVENT_HIGH_RESERVED1_MASK                                                              (0xE0000000u)


/*!**************************************************************************************************
* End of File
****************************************************************************************************/
#ifdef __cplusplus
}
#endif

#endif  /* _HW_GMACSW_CPTS_H_ */
