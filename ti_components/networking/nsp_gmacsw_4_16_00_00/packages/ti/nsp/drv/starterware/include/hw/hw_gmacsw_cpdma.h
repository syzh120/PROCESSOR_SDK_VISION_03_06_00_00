/*
 *
 * hw_gmacsw_cpdma.h - register-level header file for GMAC_SW
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

#ifndef _HW_GMACSW_CPDMA_H_
#define _HW_GMACSW_CPDMA_H_

#ifdef __cplusplus
extern "C"
{
#endif


/*!**************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define GMAC_SW_TX_IDVER                                                                                    (0x00000000u)
#define GMAC_SW_TX_CONTROL                                                                                  (0x00000004u)
#define GMAC_SW_TX_TEARDOWN                                                                                 (0x00000008u)
#define GMAC_SW_RX_IDVER                                                                                    (0x00000010u)
#define GMAC_SW_RX_CONTROL                                                                                  (0x00000014u)
#define GMAC_SW_RX_TEARDOWN                                                                                 (0x00000018u)
#define GMAC_SW_CPDMA_SOFT_RESET                                                                            (0x0000001Cu)
#define GMAC_SW_DMACONTROL                                                                                  (0x00000020u)
#define GMAC_SW_DMASTATUS                                                                                   (0x00000024u)
#define GMAC_SW_RX_BUFFER_OFFSET                                                                            (0x00000028u)
#define GMAC_SW_EMCONTROL                                                                                   (0x0000002Cu)
#define GMAC_SW_TX_PRI0_RATE                                                                                (0x00000030u)
#define GMAC_SW_TX_PRI1_RATE                                                                                (0x00000034u)
#define GMAC_SW_TX_PRI2_RATE                                                                                (0x00000038u)
#define GMAC_SW_TX_PRI3_RATE                                                                                (0x0000003Cu)
#define GMAC_SW_TX_PRI4_RATE                                                                                (0x00000040u)
#define GMAC_SW_TX_PRI5_RATE                                                                                (0x00000044u)
#define GMAC_SW_TX_PRI6_RATE                                                                                (0x00000048u)
#define GMAC_SW_TX_PRI7_RATE                                                                                (0x0000004Cu)
#define GMAC_SW_TX_INTSTAT_RAW                                                                              (0x00000080u)
#define GMAC_SW_TX_INTSTAT_MASKED                                                                           (0x00000084u)
#define GMAC_SW_TX_INTMASK_SET                                                                              (0x00000088u)
#define GMAC_SW_TX_INTMASK_CLEAR                                                                            (0x0000008Cu)
#define GMAC_SW_CPDMA_IN_VECTOR                                                                             (0x00000090u)
#define GMAC_SW_CPDMA_EOI_VECTOR                                                                            (0x00000094u)
#define GMAC_SW_RX_INTSTAT_RAW                                                                              (0x000000A0u)
#define GMAC_SW_RX_INTSTAT_MASKED                                                                           (0x000000A4u)
#define GMAC_SW_RX_INTMASK_SET                                                                              (0x000000A8u)
#define GMAC_SW_RX_INTMASK_CLEAR                                                                            (0x000000ACu)
#define GMAC_SW_DMA_INTSTAT_RAW                                                                             (0x000000B0u)
#define GMAC_SW_DMA_INTSTAT_MASKED                                                                          (0x000000B4u)
#define GMAC_SW_DMA_INTMASK_SET                                                                             (0x000000B8u)
#define GMAC_SW_DMA_INTMASK_CLEAR                                                                           (0x000000BCu)
#define GMAC_SW_RX0_PENDTHRESH                                                                              (0x000000C0u)
#define GMAC_SW_RX1_PENDTHRESH                                                                              (0x000000C4u)
#define GMAC_SW_RX2_PENDTHRESH                                                                              (0x000000C8u)
#define GMAC_SW_RX3_PENDTHRESH                                                                              (0x000000CCu)
#define GMAC_SW_RX4_PENDTHRESH                                                                              (0x000000D0u)
#define GMAC_SW_RX5_PENDTHRESH                                                                              (0x000000D4u)
#define GMAC_SW_RX6_PENDTHRESH                                                                              (0x000000D8u)
#define GMAC_SW_RX7_PENDTHRESH                                                                              (0x000000DCu)
#define GMAC_SW_RX0_FREEBUFFER                                                                              (0x000000E0u)
#define GMAC_SW_RX1_FREEBUFFER                                                                              (0x000000E4u)
#define GMAC_SW_RX2_FREEBUFFER                                                                              (0x000000E8u)
#define GMAC_SW_RX3_FREEBUFFER                                                                              (0x000000ECu)
#define GMAC_SW_RX4_FREEBUFFER                                                                              (0x000000F0u)
#define GMAC_SW_RX5_FREEBUFFER                                                                              (0x000000F4u)
#define GMAC_SW_RX6_FREEBUFFER                                                                              (0x000000F8u)
#define GMAC_SW_RX7_FREEBUFFER                                                                              (0x000000FCu)


/*!**************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

/*!*************************************** GMAC_SW_TX_IDVER *****************************************/

#define GMAC_SW_TX_IDVER_TX_MINOR_VER_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_TX_IDVER_TX_MINOR_VER_MASK                                                                  (0x000000FFu)

#define GMAC_SW_TX_IDVER_TX_MAJOR_VER_SHIFT                                                                 (0x00000008u)
#define GMAC_SW_TX_IDVER_TX_MAJOR_VER_MASK                                                                  (0x0000FF00u)

#define GMAC_SW_TX_IDVER_TX_IDENT_SHIFT                                                                     (0x00000010u)
#define GMAC_SW_TX_IDVER_TX_IDENT_MASK                                                                      (0xFFFF0000u)


/*!************************************** GMAC_SW_TX_CONTROL ****************************************/

#define GMAC_SW_TX_CONTROL_TX_EN_SHIFT                                                                      (0x00000000u)
#define GMAC_SW_TX_CONTROL_TX_EN_MASK                                                                       (0x00000001u)

#define GMAC_SW_TX_CONTROL_RESERVED1_SHIFT                                                                  (0x00000001u)
#define GMAC_SW_TX_CONTROL_RESERVED1_MASK                                                                   (0xFFFFFFFEu)


/*!************************************* GMAC_SW_TX_TEARDOWN ***************************************/

#define GMAC_SW_TX_TEARDOWN_TX_TDN_CH_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_TX_TEARDOWN_TX_TDN_CH_MASK                                                                  (0x00000007u)

#define GMAC_SW_TX_TEARDOWN_RESERVED1_SHIFT                                                                 (0x00000003u)
#define GMAC_SW_TX_TEARDOWN_RESERVED1_MASK                                                                  (0x7FFFFFF8u)

#define GMAC_SW_TX_TEARDOWN_TX_TDN_RDY_SHIFT                                                                (0x0000001Fu)
#define GMAC_SW_TX_TEARDOWN_TX_TDN_RDY_MASK                                                                 (0x80000000u)


/*!*************************************** GMAC_SW_RX_IDVER *****************************************/

#define GMAC_SW_RX_IDVER_RX_MINOR_VER_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_RX_IDVER_RX_MINOR_VER_MASK                                                                  (0x000000FFu)

#define GMAC_SW_RX_IDVER_RX_MAJOR_VER_SHIFT                                                                 (0x00000008u)
#define GMAC_SW_RX_IDVER_RX_MAJOR_VER_MASK                                                                  (0x0000FF00u)

#define GMAC_SW_RX_IDVER_RX_IDENT_SHIFT                                                                     (0x00000010u)
#define GMAC_SW_RX_IDVER_RX_IDENT_MASK                                                                      (0xFFFF0000u)


/*!************************************** GMAC_SW_RX_CONTROL ****************************************/

#define GMAC_SW_RX_CONTROL_RX_EN_SHIFT                                                                      (0x00000000u)
#define GMAC_SW_RX_CONTROL_RX_EN_MASK                                                                       (0x00000001u)

#define GMAC_SW_RX_CONTROL_RESERVED1_SHIFT                                                                  (0x00000001u)
#define GMAC_SW_RX_CONTROL_RESERVED1_MASK                                                                   (0xFFFFFFFEu)


/*!************************************* GMAC_SW_RX_TEARDOWN ***************************************/

#define GMAC_SW_RX_TEARDOWN_RX_TDN_CH_SHIFT                                                                 (0x00000000u)
#define GMAC_SW_RX_TEARDOWN_RX_TDN_CH_MASK                                                                  (0x00000007u)

#define GMAC_SW_RX_TEARDOWN_RESERVED1_SHIFT                                                                 (0x00000003u)
#define GMAC_SW_RX_TEARDOWN_RESERVED1_MASK                                                                  (0x7FFFFFF8u)

#define GMAC_SW_RX_TEARDOWN_RX_TDN_RDY_SHIFT                                                                (0x0000001Fu)
#define GMAC_SW_RX_TEARDOWN_RX_TDN_RDY_MASK                                                                 (0x80000000u)


/*!*********************************** GMAC_SW_CPDMA_SOFT_RESET *************************************/

#define GMAC_SW_CPDMA_SOFT_RESET_SOFT_RESET_SHIFT                                                           (0x00000000u)
#define GMAC_SW_CPDMA_SOFT_RESET_SOFT_RESET_MASK                                                            (0x00000001u)

#define GMAC_SW_CPDMA_SOFT_RESET_RESERVED1_SHIFT                                                            (0x00000001u)
#define GMAC_SW_CPDMA_SOFT_RESET_RESERVED1_MASK                                                             (0xFFFFFFFEu)


/*!************************************** GMAC_SW_DMACONTROL ****************************************/

#define GMAC_SW_DMACONTROL_TX_PTYPE_SHIFT                                                                   (0x00000000u)
#define GMAC_SW_DMACONTROL_TX_PTYPE_MASK                                                                    (0x00000001u)

#define GMAC_SW_DMACONTROL_RX_OWNERSHIP_SHIFT                                                               (0x00000001u)
#define GMAC_SW_DMACONTROL_RX_OWNERSHIP_MASK                                                                (0x00000002u)

#define GMAC_SW_DMACONTROL_RX_OFFLEN_BLOCK_SHIFT                                                            (0x00000002u)
#define GMAC_SW_DMACONTROL_RX_OFFLEN_BLOCK_MASK                                                             (0x00000004u)

#define GMAC_SW_DMACONTROL_CMD_IDLE_SHIFT                                                                   (0x00000003u)
#define GMAC_SW_DMACONTROL_CMD_IDLE_MASK                                                                    (0x00000008u)

#define GMAC_SW_DMACONTROL_RX_CEF_SHIFT                                                                     (0x00000004u)
#define GMAC_SW_DMACONTROL_RX_CEF_MASK                                                                      (0x00000010u)

#define GMAC_SW_DMACONTROL_RESERVED2_SHIFT                                                                  (0x00000005u)
#define GMAC_SW_DMACONTROL_RESERVED2_MASK                                                                   (0x000000E0u)

#define GMAC_SW_DMACONTROL_TX_RLIM_SHIFT                                                                    (0x00000008u)
#define GMAC_SW_DMACONTROL_TX_RLIM_MASK                                                                     (0x0000FF00u)

#define GMAC_SW_DMACONTROL_RESERVED1_SHIFT                                                                  (0x00000010u)
#define GMAC_SW_DMACONTROL_RESERVED1_MASK                                                                   (0xFFFF0000u)


/*!************************************** GMAC_SW_DMASTATUS ****************************************/

#define GMAC_SW_DMASTATUS_RESERVED4_SHIFT                                                                   (0x00000000u)
#define GMAC_SW_DMASTATUS_RESERVED4_MASK                                                                    (0x000000FFu)

#define GMAC_SW_DMASTATUS_RX_ERR_CH_SHIFT                                                                   (0x00000008u)
#define GMAC_SW_DMASTATUS_RX_ERR_CH_MASK                                                                    (0x00000700u)

#define GMAC_SW_DMASTATUS_RESERVED3_SHIFT                                                                   (0x0000000Bu)
#define GMAC_SW_DMASTATUS_RESERVED3_MASK                                                                    (0x00000800u)

#define GMAC_SW_DMASTATUS_RX_HOST_ERR_CODE_SHIFT                                                            (0x0000000Cu)
#define GMAC_SW_DMASTATUS_RX_HOST_ERR_CODE_MASK                                                             (0x0000F000u)

#define GMAC_SW_DMASTATUS_TX_ERR_CH_SHIFT                                                                   (0x00000010u)
#define GMAC_SW_DMASTATUS_TX_ERR_CH_MASK                                                                    (0x00070000u)

#define GMAC_SW_DMASTATUS_RESERVED2_SHIFT                                                                   (0x00000013u)
#define GMAC_SW_DMASTATUS_RESERVED2_MASK                                                                    (0x00080000u)

#define GMAC_SW_DMASTATUS_TX_HOST_ERR_CODE_SHIFT                                                            (0x00000014u)
#define GMAC_SW_DMASTATUS_TX_HOST_ERR_CODE_MASK                                                             (0x00F00000u)

#define GMAC_SW_DMASTATUS_RESERVED1_SHIFT                                                                   (0x00000018u)
#define GMAC_SW_DMASTATUS_RESERVED1_MASK                                                                    (0x7F000000u)

#define GMAC_SW_DMASTATUS_IDLE_SHIFT                                                                        (0x0000001Fu)
#define GMAC_SW_DMASTATUS_IDLE_MASK                                                                         (0x80000000u)


/*!*********************************** GMAC_SW_RX_BUFFER_OFFSET *************************************/

#define GMAC_SW_RX_BUFFER_OFFSET_RX_BUFFER_OFFSET_SHIFT                                                     (0x00000000u)
#define GMAC_SW_RX_BUFFER_OFFSET_RX_BUFFER_OFFSET_MASK                                                      (0x0000FFFFu)

#define GMAC_SW_RX_BUFFER_OFFSET_RESERVED1_SHIFT                                                            (0x00000010u)
#define GMAC_SW_RX_BUFFER_OFFSET_RESERVED1_MASK                                                             (0xFFFF0000u)


/*!************************************** GMAC_SW_EMCONTROL ****************************************/

#define GMAC_SW_EMCONTROL_FREE_SHIFT                                                                        (0x00000000u)
#define GMAC_SW_EMCONTROL_FREE_MASK                                                                         (0x00000001u)

#define GMAC_SW_EMCONTROL_SOFT_SHIFT                                                                        (0x00000001u)
#define GMAC_SW_EMCONTROL_SOFT_MASK                                                                         (0x00000002u)

#define GMAC_SW_EMCONTROL_RESERVED1_SHIFT                                                                   (0x00000002u)
#define GMAC_SW_EMCONTROL_RESERVED1_MASK                                                                    (0xFFFFFFFCu)


/*!************************************* GMAC_SW_TX_PRI0_RATE ***************************************/

#define GMAC_SW_TX_PRI0_RATE_PRIN_SEND_CNT_SHIFT                                                            (0x00000000u)
#define GMAC_SW_TX_PRI0_RATE_PRIN_SEND_CNT_MASK                                                             (0x00003FFFu)

#define GMAC_SW_TX_PRI0_RATE_RESERVED2_SHIFT                                                                (0x0000000Eu)
#define GMAC_SW_TX_PRI0_RATE_RESERVED2_MASK                                                                 (0x0000C000u)

#define GMAC_SW_TX_PRI0_RATE_PRIN_IDLE_CNT_SHIFT                                                            (0x00000010u)
#define GMAC_SW_TX_PRI0_RATE_PRIN_IDLE_CNT_MASK                                                             (0x3FFF0000u)

#define GMAC_SW_TX_PRI0_RATE_RESERVED1_SHIFT                                                                (0x0000001Eu)
#define GMAC_SW_TX_PRI0_RATE_RESERVED1_MASK                                                                 (0xC0000000u)


/*!************************************* GMAC_SW_TX_PRI1_RATE ***************************************/

#define GMAC_SW_TX_PRI1_RATE_PRIN_SEND_CNT_SHIFT                                                            (0x00000000u)
#define GMAC_SW_TX_PRI1_RATE_PRIN_SEND_CNT_MASK                                                             (0x00003FFFu)

#define GMAC_SW_TX_PRI1_RATE_RESERVED2_SHIFT                                                                (0x0000000Eu)
#define GMAC_SW_TX_PRI1_RATE_RESERVED2_MASK                                                                 (0x0000C000u)

#define GMAC_SW_TX_PRI1_RATE_PRIN_IDLE_CNT_SHIFT                                                            (0x00000010u)
#define GMAC_SW_TX_PRI1_RATE_PRIN_IDLE_CNT_MASK                                                             (0x3FFF0000u)

#define GMAC_SW_TX_PRI1_RATE_RESERVED1_SHIFT                                                                (0x0000001Eu)
#define GMAC_SW_TX_PRI1_RATE_RESERVED1_MASK                                                                 (0xC0000000u)


/*!************************************* GMAC_SW_TX_PRI2_RATE ***************************************/

#define GMAC_SW_TX_PRI2_RATE_PRIN_SEND_CNT_SHIFT                                                            (0x00000000u)
#define GMAC_SW_TX_PRI2_RATE_PRIN_SEND_CNT_MASK                                                             (0x00003FFFu)

#define GMAC_SW_TX_PRI2_RATE_RESERVED2_SHIFT                                                                (0x0000000Eu)
#define GMAC_SW_TX_PRI2_RATE_RESERVED2_MASK                                                                 (0x0000C000u)

#define GMAC_SW_TX_PRI2_RATE_PRIN_IDLE_CNT_SHIFT                                                            (0x00000010u)
#define GMAC_SW_TX_PRI2_RATE_PRIN_IDLE_CNT_MASK                                                             (0x3FFF0000u)

#define GMAC_SW_TX_PRI2_RATE_RESERVED1_SHIFT                                                                (0x0000001Eu)
#define GMAC_SW_TX_PRI2_RATE_RESERVED1_MASK                                                                 (0xC0000000u)


/*!************************************* GMAC_SW_TX_PRI3_RATE ***************************************/

#define GMAC_SW_TX_PRI3_RATE_PRIN_SEND_CNT_SHIFT                                                            (0x00000000u)
#define GMAC_SW_TX_PRI3_RATE_PRIN_SEND_CNT_MASK                                                             (0x00003FFFu)

#define GMAC_SW_TX_PRI3_RATE_RESERVED2_SHIFT                                                                (0x0000000Eu)
#define GMAC_SW_TX_PRI3_RATE_RESERVED2_MASK                                                                 (0x0000C000u)

#define GMAC_SW_TX_PRI3_RATE_PRIN_IDLE_CNT_SHIFT                                                            (0x00000010u)
#define GMAC_SW_TX_PRI3_RATE_PRIN_IDLE_CNT_MASK                                                             (0x3FFF0000u)

#define GMAC_SW_TX_PRI3_RATE_RESERVED1_SHIFT                                                                (0x0000001Eu)
#define GMAC_SW_TX_PRI3_RATE_RESERVED1_MASK                                                                 (0xC0000000u)


/*!************************************* GMAC_SW_TX_PRI4_RATE ***************************************/

#define GMAC_SW_TX_PRI4_RATE_PRIN_SEND_CNT_SHIFT                                                            (0x00000000u)
#define GMAC_SW_TX_PRI4_RATE_PRIN_SEND_CNT_MASK                                                             (0x00003FFFu)

#define GMAC_SW_TX_PRI4_RATE_RESERVED2_SHIFT                                                                (0x0000000Eu)
#define GMAC_SW_TX_PRI4_RATE_RESERVED2_MASK                                                                 (0x0000C000u)

#define GMAC_SW_TX_PRI4_RATE_PRIN_IDLE_CNT_SHIFT                                                            (0x00000010u)
#define GMAC_SW_TX_PRI4_RATE_PRIN_IDLE_CNT_MASK                                                             (0x3FFF0000u)

#define GMAC_SW_TX_PRI4_RATE_RESERVED1_SHIFT                                                                (0x0000001Eu)
#define GMAC_SW_TX_PRI4_RATE_RESERVED1_MASK                                                                 (0xC0000000u)


/*!************************************* GMAC_SW_TX_PRI5_RATE ***************************************/

#define GMAC_SW_TX_PRI5_RATE_PRIN_SEND_CNT_SHIFT                                                            (0x00000000u)
#define GMAC_SW_TX_PRI5_RATE_PRIN_SEND_CNT_MASK                                                             (0x00003FFFu)

#define GMAC_SW_TX_PRI5_RATE_RESERVED2_SHIFT                                                                (0x0000000Eu)
#define GMAC_SW_TX_PRI5_RATE_RESERVED2_MASK                                                                 (0x0000C000u)

#define GMAC_SW_TX_PRI5_RATE_PRIN_IDLE_CNT_SHIFT                                                            (0x00000010u)
#define GMAC_SW_TX_PRI5_RATE_PRIN_IDLE_CNT_MASK                                                             (0x3FFF0000u)

#define GMAC_SW_TX_PRI5_RATE_RESERVED1_SHIFT                                                                (0x0000001Eu)
#define GMAC_SW_TX_PRI5_RATE_RESERVED1_MASK                                                                 (0xC0000000u)


/*!************************************* GMAC_SW_TX_PRI6_RATE ***************************************/

#define GMAC_SW_TX_PRI6_RATE_PRIN_SEND_CNT_SHIFT                                                            (0x00000000u)
#define GMAC_SW_TX_PRI6_RATE_PRIN_SEND_CNT_MASK                                                             (0x00003FFFu)

#define GMAC_SW_TX_PRI6_RATE_RESERVED2_SHIFT                                                                (0x0000000Eu)
#define GMAC_SW_TX_PRI6_RATE_RESERVED2_MASK                                                                 (0x0000C000u)

#define GMAC_SW_TX_PRI6_RATE_PRIN_IDLE_CNT_SHIFT                                                            (0x00000010u)
#define GMAC_SW_TX_PRI6_RATE_PRIN_IDLE_CNT_MASK                                                             (0x3FFF0000u)

#define GMAC_SW_TX_PRI6_RATE_RESERVED1_SHIFT                                                                (0x0000001Eu)
#define GMAC_SW_TX_PRI6_RATE_RESERVED1_MASK                                                                 (0xC0000000u)


/*!************************************* GMAC_SW_TX_PRI7_RATE ***************************************/

#define GMAC_SW_TX_PRI7_RATE_PRIN_SEND_CNT_SHIFT                                                            (0x00000000u)
#define GMAC_SW_TX_PRI7_RATE_PRIN_SEND_CNT_MASK                                                             (0x00003FFFu)

#define GMAC_SW_TX_PRI7_RATE_RESERVED2_SHIFT                                                                (0x0000000Eu)
#define GMAC_SW_TX_PRI7_RATE_RESERVED2_MASK                                                                 (0x0000C000u)

#define GMAC_SW_TX_PRI7_RATE_PRIN_IDLE_CNT_SHIFT                                                            (0x00000010u)
#define GMAC_SW_TX_PRI7_RATE_PRIN_IDLE_CNT_MASK                                                             (0x3FFF0000u)

#define GMAC_SW_TX_PRI7_RATE_RESERVED1_SHIFT                                                                (0x0000001Eu)
#define GMAC_SW_TX_PRI7_RATE_RESERVED1_MASK                                                                 (0xC0000000u)


/*!************************************ GMAC_SW_TX_INTSTAT_RAW **************************************/

#define GMAC_SW_TX_INTSTAT_RAW_TX0_PEND_SHIFT                                                               (0x00000000u)
#define GMAC_SW_TX_INTSTAT_RAW_TX0_PEND_MASK                                                                (0x00000001u)

#define GMAC_SW_TX_INTSTAT_RAW_TX1_PEND_SHIFT                                                               (0x00000001u)
#define GMAC_SW_TX_INTSTAT_RAW_TX1_PEND_MASK                                                                (0x00000002u)

#define GMAC_SW_TX_INTSTAT_RAW_TX2_PEND_SHIFT                                                               (0x00000002u)
#define GMAC_SW_TX_INTSTAT_RAW_TX2_PEND_MASK                                                                (0x00000004u)

#define GMAC_SW_TX_INTSTAT_RAW_TX3_PEND_SHIFT                                                               (0x00000003u)
#define GMAC_SW_TX_INTSTAT_RAW_TX3_PEND_MASK                                                                (0x00000008u)

#define GMAC_SW_TX_INTSTAT_RAW_TX4_PEND_SHIFT                                                               (0x00000004u)
#define GMAC_SW_TX_INTSTAT_RAW_TX4_PEND_MASK                                                                (0x00000010u)

#define GMAC_SW_TX_INTSTAT_RAW_TX5_PEND_SHIFT                                                               (0x00000005u)
#define GMAC_SW_TX_INTSTAT_RAW_TX5_PEND_MASK                                                                (0x00000020u)

#define GMAC_SW_TX_INTSTAT_RAW_TX6_PEND_SHIFT                                                               (0x00000006u)
#define GMAC_SW_TX_INTSTAT_RAW_TX6_PEND_MASK                                                                (0x00000040u)

#define GMAC_SW_TX_INTSTAT_RAW_TX7_PEND_SHIFT                                                               (0x00000007u)
#define GMAC_SW_TX_INTSTAT_RAW_TX7_PEND_MASK                                                                (0x00000080u)

#define GMAC_SW_TX_INTSTAT_RAW_RESERVED1_SHIFT                                                              (0x00000008u)
#define GMAC_SW_TX_INTSTAT_RAW_RESERVED1_MASK                                                               (0xFFFFFF00u)


/*!********************************** GMAC_SW_TX_INTSTAT_MASKED ************************************/

#define GMAC_SW_TX_INTSTAT_MASKED_TX0_PEND_SHIFT                                                            (0x00000000u)
#define GMAC_SW_TX_INTSTAT_MASKED_TX0_PEND_MASK                                                             (0x00000001u)

#define GMAC_SW_TX_INTSTAT_MASKED_TX1_PEND_SHIFT                                                            (0x00000001u)
#define GMAC_SW_TX_INTSTAT_MASKED_TX1_PEND_MASK                                                             (0x00000002u)

#define GMAC_SW_TX_INTSTAT_MASKED_TX2_PEND_SHIFT                                                            (0x00000002u)
#define GMAC_SW_TX_INTSTAT_MASKED_TX2_PEND_MASK                                                             (0x00000004u)

#define GMAC_SW_TX_INTSTAT_MASKED_TX3_PEND_SHIFT                                                            (0x00000003u)
#define GMAC_SW_TX_INTSTAT_MASKED_TX3_PEND_MASK                                                             (0x00000008u)

#define GMAC_SW_TX_INTSTAT_MASKED_TX4_PEND_SHIFT                                                            (0x00000004u)
#define GMAC_SW_TX_INTSTAT_MASKED_TX4_PEND_MASK                                                             (0x00000010u)

#define GMAC_SW_TX_INTSTAT_MASKED_TX5_PEND_SHIFT                                                            (0x00000005u)
#define GMAC_SW_TX_INTSTAT_MASKED_TX5_PEND_MASK                                                             (0x00000020u)

#define GMAC_SW_TX_INTSTAT_MASKED_TX6_PEND_SHIFT                                                            (0x00000006u)
#define GMAC_SW_TX_INTSTAT_MASKED_TX6_PEND_MASK                                                             (0x00000040u)

#define GMAC_SW_TX_INTSTAT_MASKED_TX7_PEND_SHIFT                                                            (0x00000007u)
#define GMAC_SW_TX_INTSTAT_MASKED_TX7_PEND_MASK                                                             (0x00000080u)

#define GMAC_SW_TX_INTSTAT_MASKED_RESERVED1_SHIFT                                                           (0x00000008u)
#define GMAC_SW_TX_INTSTAT_MASKED_RESERVED1_MASK                                                            (0xFFFFFF00u)


/*!************************************ GMAC_SW_TX_INTMASK_SET **************************************/

#define GMAC_SW_TX_INTMASK_SET_TX0_MASK_SHIFT                                                               (0x00000000u)
#define GMAC_SW_TX_INTMASK_SET_TX0_MASK_MASK                                                                (0x00000001u)

#define GMAC_SW_TX_INTMASK_SET_TX1_MASK_SHIFT                                                               (0x00000001u)
#define GMAC_SW_TX_INTMASK_SET_TX1_MASK_MASK                                                                (0x00000002u)

#define GMAC_SW_TX_INTMASK_SET_TX2_MASK_SHIFT                                                               (0x00000002u)
#define GMAC_SW_TX_INTMASK_SET_TX2_MASK_MASK                                                                (0x00000004u)

#define GMAC_SW_TX_INTMASK_SET_TX3_MASK_SHIFT                                                               (0x00000003u)
#define GMAC_SW_TX_INTMASK_SET_TX3_MASK_MASK                                                                (0x00000008u)

#define GMAC_SW_TX_INTMASK_SET_TX4_MASK_SHIFT                                                               (0x00000004u)
#define GMAC_SW_TX_INTMASK_SET_TX4_MASK_MASK                                                                (0x00000010u)

#define GMAC_SW_TX_INTMASK_SET_TX5_MASK_SHIFT                                                               (0x00000005u)
#define GMAC_SW_TX_INTMASK_SET_TX5_MASK_MASK                                                                (0x00000020u)

#define GMAC_SW_TX_INTMASK_SET_TX6_MASK_SHIFT                                                               (0x00000006u)
#define GMAC_SW_TX_INTMASK_SET_TX6_MASK_MASK                                                                (0x00000040u)

#define GMAC_SW_TX_INTMASK_SET_TX7_MASK_SHIFT                                                               (0x00000007u)
#define GMAC_SW_TX_INTMASK_SET_TX7_MASK_MASK                                                                (0x00000080u)

#define GMAC_SW_TX_INTMASK_SET_RESERVED1_SHIFT                                                              (0x00000008u)
#define GMAC_SW_TX_INTMASK_SET_RESERVED1_MASK                                                               (0xFFFFFF00u)


/*!*********************************** GMAC_SW_TX_INTMASK_CLEAR *************************************/

#define GMAC_SW_TX_INTMASK_CLEAR_TX0_MASK_SHIFT                                                             (0x00000000u)
#define GMAC_SW_TX_INTMASK_CLEAR_TX0_MASK_MASK                                                              (0x00000001u)

#define GMAC_SW_TX_INTMASK_CLEAR_TX1_MASK_SHIFT                                                             (0x00000001u)
#define GMAC_SW_TX_INTMASK_CLEAR_TX1_MASK_MASK                                                              (0x00000002u)

#define GMAC_SW_TX_INTMASK_CLEAR_TX2_MASK_SHIFT                                                             (0x00000002u)
#define GMAC_SW_TX_INTMASK_CLEAR_TX2_MASK_MASK                                                              (0x00000004u)

#define GMAC_SW_TX_INTMASK_CLEAR_TX3_MASK_SHIFT                                                             (0x00000003u)
#define GMAC_SW_TX_INTMASK_CLEAR_TX3_MASK_MASK                                                              (0x00000008u)

#define GMAC_SW_TX_INTMASK_CLEAR_TX4_MASK_SHIFT                                                             (0x00000004u)
#define GMAC_SW_TX_INTMASK_CLEAR_TX4_MASK_MASK                                                              (0x00000010u)

#define GMAC_SW_TX_INTMASK_CLEAR_TX5_MASK_SHIFT                                                             (0x00000005u)
#define GMAC_SW_TX_INTMASK_CLEAR_TX5_MASK_MASK                                                              (0x00000020u)

#define GMAC_SW_TX_INTMASK_CLEAR_TX6_MASK_SHIFT                                                             (0x00000006u)
#define GMAC_SW_TX_INTMASK_CLEAR_TX6_MASK_MASK                                                              (0x00000040u)

#define GMAC_SW_TX_INTMASK_CLEAR_TX7_MASK_SHIFT                                                             (0x00000007u)
#define GMAC_SW_TX_INTMASK_CLEAR_TX7_MASK_MASK                                                              (0x00000080u)

#define GMAC_SW_TX_INTMASK_CLEAR_RESERVED1_SHIFT                                                            (0x00000008u)
#define GMAC_SW_TX_INTMASK_CLEAR_RESERVED1_MASK                                                             (0xFFFFFF00u)


/*!*********************************** GMAC_SW_CPDMA_IN_VECTOR *************************************/

#define GMAC_SW_CPDMA_IN_VECTOR_DMA_IN_VECTOR_SHIFT                                                         (0x00000000u)
#define GMAC_SW_CPDMA_IN_VECTOR_DMA_IN_VECTOR_MASK                                                          (0xFFFFFFFFu)


/*!*********************************** GMAC_SW_CPDMA_EOI_VECTOR *************************************/

#define GMAC_SW_CPDMA_EOI_VECTOR_DMA_EOI_VECTOR_SHIFT                                                       (0x00000000u)
#define GMAC_SW_CPDMA_EOI_VECTOR_DMA_EOI_VECTOR_MASK                                                        (0x0000001Fu)

#define GMAC_SW_CPDMA_EOI_VECTOR_RESERVED1_SHIFT                                                            (0x00000005u)
#define GMAC_SW_CPDMA_EOI_VECTOR_RESERVED1_MASK                                                             (0xFFFFFFE0u)


/*!************************************ GMAC_SW_RX_INTSTAT_RAW **************************************/

#define GMAC_SW_RX_INTSTAT_RAW_RX0_PEND_SHIFT                                                               (0x00000000u)
#define GMAC_SW_RX_INTSTAT_RAW_RX0_PEND_MASK                                                                (0x00000001u)

#define GMAC_SW_RX_INTSTAT_RAW_RX1_PEND_SHIFT                                                               (0x00000001u)
#define GMAC_SW_RX_INTSTAT_RAW_RX1_PEND_MASK                                                                (0x00000002u)

#define GMAC_SW_RX_INTSTAT_RAW_RX2_PEND_SHIFT                                                               (0x00000002u)
#define GMAC_SW_RX_INTSTAT_RAW_RX2_PEND_MASK                                                                (0x00000004u)

#define GMAC_SW_RX_INTSTAT_RAW_RX3_PEND_SHIFT                                                               (0x00000003u)
#define GMAC_SW_RX_INTSTAT_RAW_RX3_PEND_MASK                                                                (0x00000008u)

#define GMAC_SW_RX_INTSTAT_RAW_RX4_PEND_SHIFT                                                               (0x00000004u)
#define GMAC_SW_RX_INTSTAT_RAW_RX4_PEND_MASK                                                                (0x00000010u)

#define GMAC_SW_RX_INTSTAT_RAW_RX5_PEND_SHIFT                                                               (0x00000005u)
#define GMAC_SW_RX_INTSTAT_RAW_RX5_PEND_MASK                                                                (0x00000020u)

#define GMAC_SW_RX_INTSTAT_RAW_RX6_PEND_SHIFT                                                               (0x00000006u)
#define GMAC_SW_RX_INTSTAT_RAW_RX6_PEND_MASK                                                                (0x00000040u)

#define GMAC_SW_RX_INTSTAT_RAW_RX7_PEND_SHIFT                                                               (0x00000007u)
#define GMAC_SW_RX_INTSTAT_RAW_RX7_PEND_MASK                                                                (0x00000080u)

#define GMAC_SW_RX_INTSTAT_RAW_RX0_THRESH_PEND_SHIFT                                                        (0x00000008u)
#define GMAC_SW_RX_INTSTAT_RAW_RX0_THRESH_PEND_MASK                                                         (0x00000100u)

#define GMAC_SW_RX_INTSTAT_RAW_RX1_THRESH_PEND_SHIFT                                                        (0x00000009u)
#define GMAC_SW_RX_INTSTAT_RAW_RX1_THRESH_PEND_MASK                                                         (0x00000200u)

#define GMAC_SW_RX_INTSTAT_RAW_RX2_THRESH_PEND_SHIFT                                                        (0x0000000Au)
#define GMAC_SW_RX_INTSTAT_RAW_RX2_THRESH_PEND_MASK                                                         (0x00000400u)

#define GMAC_SW_RX_INTSTAT_RAW_RX3_THRESH_PEND_SHIFT                                                        (0x0000000Bu)
#define GMAC_SW_RX_INTSTAT_RAW_RX3_THRESH_PEND_MASK                                                         (0x00000800u)

#define GMAC_SW_RX_INTSTAT_RAW_RX4_THRESH_PEND_SHIFT                                                        (0x0000000Cu)
#define GMAC_SW_RX_INTSTAT_RAW_RX4_THRESH_PEND_MASK                                                         (0x00001000u)

#define GMAC_SW_RX_INTSTAT_RAW_RX5_THRESH_PEND_SHIFT                                                        (0x0000000Du)
#define GMAC_SW_RX_INTSTAT_RAW_RX5_THRESH_PEND_MASK                                                         (0x00002000u)

#define GMAC_SW_RX_INTSTAT_RAW_RX6_THRESH_PEND_SHIFT                                                        (0x0000000Eu)
#define GMAC_SW_RX_INTSTAT_RAW_RX6_THRESH_PEND_MASK                                                         (0x00004000u)

#define GMAC_SW_RX_INTSTAT_RAW_RX7_THRESH_PEND_SHIFT                                                        (0x0000000Fu)
#define GMAC_SW_RX_INTSTAT_RAW_RX7_THRESH_PEND_MASK                                                         (0x00008000u)

#define GMAC_SW_RX_INTSTAT_RAW_RESERVED1_SHIFT                                                              (0x00000010u)
#define GMAC_SW_RX_INTSTAT_RAW_RESERVED1_MASK                                                               (0xFFFF0000u)


/*!********************************** GMAC_SW_RX_INTSTAT_MASKED ************************************/

#define GMAC_SW_RX_INTSTAT_MASKED_RX0_PEND_SHIFT                                                            (0x00000000u)
#define GMAC_SW_RX_INTSTAT_MASKED_RX0_PEND_MASK                                                             (0x00000001u)

#define GMAC_SW_RX_INTSTAT_MASKED_RX1_PEND_SHIFT                                                            (0x00000001u)
#define GMAC_SW_RX_INTSTAT_MASKED_RX1_PEND_MASK                                                             (0x00000002u)

#define GMAC_SW_RX_INTSTAT_MASKED_RX2_PEND_SHIFT                                                            (0x00000002u)
#define GMAC_SW_RX_INTSTAT_MASKED_RX2_PEND_MASK                                                             (0x00000004u)

#define GMAC_SW_RX_INTSTAT_MASKED_RX3_PEND_SHIFT                                                            (0x00000003u)
#define GMAC_SW_RX_INTSTAT_MASKED_RX3_PEND_MASK                                                             (0x00000008u)

#define GMAC_SW_RX_INTSTAT_MASKED_RX4_PEND_SHIFT                                                            (0x00000004u)
#define GMAC_SW_RX_INTSTAT_MASKED_RX4_PEND_MASK                                                             (0x00000010u)

#define GMAC_SW_RX_INTSTAT_MASKED_RX5_PEND_SHIFT                                                            (0x00000005u)
#define GMAC_SW_RX_INTSTAT_MASKED_RX5_PEND_MASK                                                             (0x00000020u)

#define GMAC_SW_RX_INTSTAT_MASKED_RX6_PEND_SHIFT                                                            (0x00000006u)
#define GMAC_SW_RX_INTSTAT_MASKED_RX6_PEND_MASK                                                             (0x00000040u)

#define GMAC_SW_RX_INTSTAT_MASKED_RX7_PEND_SHIFT                                                            (0x00000007u)
#define GMAC_SW_RX_INTSTAT_MASKED_RX7_PEND_MASK                                                             (0x00000080u)

#define GMAC_SW_RX_INTSTAT_MASKED_RX0_THRESH_PEND_SHIFT                                                     (0x00000008u)
#define GMAC_SW_RX_INTSTAT_MASKED_RX0_THRESH_PEND_MASK                                                      (0x00000100u)

#define GMAC_SW_RX_INTSTAT_MASKED_RX1_THRESH_PEND_SHIFT                                                     (0x00000009u)
#define GMAC_SW_RX_INTSTAT_MASKED_RX1_THRESH_PEND_MASK                                                      (0x00000200u)

#define GMAC_SW_RX_INTSTAT_MASKED_RX2_THRESH_PEND_SHIFT                                                     (0x0000000Au)
#define GMAC_SW_RX_INTSTAT_MASKED_RX2_THRESH_PEND_MASK                                                      (0x00000400u)

#define GMAC_SW_RX_INTSTAT_MASKED_RX3_THRESH_PEND_SHIFT                                                     (0x0000000Bu)
#define GMAC_SW_RX_INTSTAT_MASKED_RX3_THRESH_PEND_MASK                                                      (0x00000800u)

#define GMAC_SW_RX_INTSTAT_MASKED_RX4_THRESH_PEND_SHIFT                                                     (0x0000000Cu)
#define GMAC_SW_RX_INTSTAT_MASKED_RX4_THRESH_PEND_MASK                                                      (0x00001000u)

#define GMAC_SW_RX_INTSTAT_MASKED_RX5_THRESH_PEND_SHIFT                                                     (0x0000000Du)
#define GMAC_SW_RX_INTSTAT_MASKED_RX5_THRESH_PEND_MASK                                                      (0x00002000u)

#define GMAC_SW_RX_INTSTAT_MASKED_RX6_THRESH_PEND_SHIFT                                                     (0x0000000Eu)
#define GMAC_SW_RX_INTSTAT_MASKED_RX6_THRESH_PEND_MASK                                                      (0x00004000u)

#define GMAC_SW_RX_INTSTAT_MASKED_RX7_THRESH_PEND_SHIFT                                                     (0x0000000Fu)
#define GMAC_SW_RX_INTSTAT_MASKED_RX7_THRESH_PEND_MASK                                                      (0x00008000u)

#define GMAC_SW_RX_INTSTAT_MASKED_RESERVED1_SHIFT                                                           (0x00000010u)
#define GMAC_SW_RX_INTSTAT_MASKED_RESERVED1_MASK                                                            (0xFFFF0000u)


/*!************************************ GMAC_SW_RX_INTMASK_SET **************************************/

#define GMAC_SW_RX_INTMASK_SET_RX0_PEND_MASK_SHIFT                                                          (0x00000000u)
#define GMAC_SW_RX_INTMASK_SET_RX0_PEND_MASK_MASK                                                           (0x00000001u)

#define GMAC_SW_RX_INTMASK_SET_RX1_PEND_MASK_SHIFT                                                          (0x00000001u)
#define GMAC_SW_RX_INTMASK_SET_RX1_PEND_MASK_MASK                                                           (0x00000002u)

#define GMAC_SW_RX_INTMASK_SET_RX2_PEND_MASK_SHIFT                                                          (0x00000002u)
#define GMAC_SW_RX_INTMASK_SET_RX2_PEND_MASK_MASK                                                           (0x00000004u)

#define GMAC_SW_RX_INTMASK_SET_RX3_PEND_MASK_SHIFT                                                          (0x00000003u)
#define GMAC_SW_RX_INTMASK_SET_RX3_PEND_MASK_MASK                                                           (0x00000008u)

#define GMAC_SW_RX_INTMASK_SET_RX4_PEND_MASK_SHIFT                                                          (0x00000004u)
#define GMAC_SW_RX_INTMASK_SET_RX4_PEND_MASK_MASK                                                           (0x00000010u)

#define GMAC_SW_RX_INTMASK_SET_RX5_PEND_MASK_SHIFT                                                          (0x00000005u)
#define GMAC_SW_RX_INTMASK_SET_RX5_PEND_MASK_MASK                                                           (0x00000020u)

#define GMAC_SW_RX_INTMASK_SET_RX6_PEND_MASK_SHIFT                                                          (0x00000006u)
#define GMAC_SW_RX_INTMASK_SET_RX6_PEND_MASK_MASK                                                           (0x00000040u)

#define GMAC_SW_RX_INTMASK_SET_RX7_PEND_MASK_SHIFT                                                          (0x00000007u)
#define GMAC_SW_RX_INTMASK_SET_RX7_PEND_MASK_MASK                                                           (0x00000080u)

#define GMAC_SW_RX_INTMASK_SET_RX0_THRESH_PEND_MASK_SHIFT                                                   (0x00000008u)
#define GMAC_SW_RX_INTMASK_SET_RX0_THRESH_PEND_MASK_MASK                                                    (0x00000100u)

#define GMAC_SW_RX_INTMASK_SET_RX1_THRESH_PEND_MASK_SHIFT                                                   (0x00000009u)
#define GMAC_SW_RX_INTMASK_SET_RX1_THRESH_PEND_MASK_MASK                                                    (0x00000200u)

#define GMAC_SW_RX_INTMASK_SET_RX2_THRESH_PEND_MASK_SHIFT                                                   (0x0000000Au)
#define GMAC_SW_RX_INTMASK_SET_RX2_THRESH_PEND_MASK_MASK                                                    (0x00000400u)

#define GMAC_SW_RX_INTMASK_SET_RX3_THRESH_PEND_MASK_SHIFT                                                   (0x0000000Bu)
#define GMAC_SW_RX_INTMASK_SET_RX3_THRESH_PEND_MASK_MASK                                                    (0x00000800u)

#define GMAC_SW_RX_INTMASK_SET_RX4_THRESH_PEND_MASK_SHIFT                                                   (0x0000000Cu)
#define GMAC_SW_RX_INTMASK_SET_RX4_THRESH_PEND_MASK_MASK                                                    (0x00001000u)

#define GMAC_SW_RX_INTMASK_SET_RX5_THRESH_PEND_MASK_SHIFT                                                   (0x0000000Du)
#define GMAC_SW_RX_INTMASK_SET_RX5_THRESH_PEND_MASK_MASK                                                    (0x00002000u)

#define GMAC_SW_RX_INTMASK_SET_RX6_THRESH_PEND_MASK_SHIFT                                                   (0x0000000Eu)
#define GMAC_SW_RX_INTMASK_SET_RX6_THRESH_PEND_MASK_MASK                                                    (0x00004000u)

#define GMAC_SW_RX_INTMASK_SET_RX7_THRESH_PEND_MASK_SHIFT                                                   (0x0000000Fu)
#define GMAC_SW_RX_INTMASK_SET_RX7_THRESH_PEND_MASK_MASK                                                    (0x00008000u)

#define GMAC_SW_RX_INTMASK_SET_RESERVED1_SHIFT                                                              (0x00000010u)
#define GMAC_SW_RX_INTMASK_SET_RESERVED1_MASK                                                               (0xFFFF0000u)


/*!*********************************** GMAC_SW_RX_INTMASK_CLEAR *************************************/

#define GMAC_SW_RX_INTMASK_CLEAR_RX0_PEND_MASK_SHIFT                                                        (0x00000000u)
#define GMAC_SW_RX_INTMASK_CLEAR_RX0_PEND_MASK_MASK                                                         (0x00000001u)

#define GMAC_SW_RX_INTMASK_CLEAR_RX1_PEND_MASK_SHIFT                                                        (0x00000001u)
#define GMAC_SW_RX_INTMASK_CLEAR_RX1_PEND_MASK_MASK                                                         (0x00000002u)

#define GMAC_SW_RX_INTMASK_CLEAR_RX2_PEND_MASK_SHIFT                                                        (0x00000002u)
#define GMAC_SW_RX_INTMASK_CLEAR_RX2_PEND_MASK_MASK                                                         (0x00000004u)

#define GMAC_SW_RX_INTMASK_CLEAR_RX3_PEND_MASK_SHIFT                                                        (0x00000003u)
#define GMAC_SW_RX_INTMASK_CLEAR_RX3_PEND_MASK_MASK                                                         (0x00000008u)

#define GMAC_SW_RX_INTMASK_CLEAR_RX4_PEND_MASK_SHIFT                                                        (0x00000004u)
#define GMAC_SW_RX_INTMASK_CLEAR_RX4_PEND_MASK_MASK                                                         (0x00000010u)

#define GMAC_SW_RX_INTMASK_CLEAR_RX5_PEND_MASK_SHIFT                                                        (0x00000005u)
#define GMAC_SW_RX_INTMASK_CLEAR_RX5_PEND_MASK_MASK                                                         (0x00000020u)

#define GMAC_SW_RX_INTMASK_CLEAR_RX6_PEND_MASK_SHIFT                                                        (0x00000006u)
#define GMAC_SW_RX_INTMASK_CLEAR_RX6_PEND_MASK_MASK                                                         (0x00000040u)

#define GMAC_SW_RX_INTMASK_CLEAR_RX7_PEND_MASK_SHIFT                                                        (0x00000007u)
#define GMAC_SW_RX_INTMASK_CLEAR_RX7_PEND_MASK_MASK                                                         (0x00000080u)

#define GMAC_SW_RX_INTMASK_CLEAR_RX0_THRESH_PEND_MASK_SHIFT                                                 (0x00000008u)
#define GMAC_SW_RX_INTMASK_CLEAR_RX0_THRESH_PEND_MASK_MASK                                                  (0x00000100u)

#define GMAC_SW_RX_INTMASK_CLEAR_RX1_THRESH_PEND_MASK_SHIFT                                                 (0x00000009u)
#define GMAC_SW_RX_INTMASK_CLEAR_RX1_THRESH_PEND_MASK_MASK                                                  (0x00000200u)

#define GMAC_SW_RX_INTMASK_CLEAR_RX2_THRESH_PEND_MASK_SHIFT                                                 (0x0000000Au)
#define GMAC_SW_RX_INTMASK_CLEAR_RX2_THRESH_PEND_MASK_MASK                                                  (0x00000400u)

#define GMAC_SW_RX_INTMASK_CLEAR_RX3_THRESH_PEND_MASK_SHIFT                                                 (0x0000000Bu)
#define GMAC_SW_RX_INTMASK_CLEAR_RX3_THRESH_PEND_MASK_MASK                                                  (0x00000800u)

#define GMAC_SW_RX_INTMASK_CLEAR_RX4_THRESH_PEND_MASK_SHIFT                                                 (0x0000000Cu)
#define GMAC_SW_RX_INTMASK_CLEAR_RX4_THRESH_PEND_MASK_MASK                                                  (0x00001000u)

#define GMAC_SW_RX_INTMASK_CLEAR_RX5_THRESH_PEND_MASK_SHIFT                                                 (0x0000000Du)
#define GMAC_SW_RX_INTMASK_CLEAR_RX5_THRESH_PEND_MASK_MASK                                                  (0x00002000u)

#define GMAC_SW_RX_INTMASK_CLEAR_RX6_THRESH_PEND_MASK_SHIFT                                                 (0x0000000Eu)
#define GMAC_SW_RX_INTMASK_CLEAR_RX6_THRESH_PEND_MASK_MASK                                                  (0x00004000u)

#define GMAC_SW_RX_INTMASK_CLEAR_RX7_THRESH_PEND_MASK_SHIFT                                                 (0x0000000Fu)
#define GMAC_SW_RX_INTMASK_CLEAR_RX7_THRESH_PEND_MASK_MASK                                                  (0x00008000u)

#define GMAC_SW_RX_INTMASK_CLEAR_RESERVED1_SHIFT                                                            (0x00000010u)
#define GMAC_SW_RX_INTMASK_CLEAR_RESERVED1_MASK                                                             (0xFFFF0000u)


/*!*********************************** GMAC_SW_DMA_INTSTAT_RAW *************************************/

#define GMAC_SW_DMA_INTSTAT_RAW_STAT_PEND_SHIFT                                                             (0x00000000u)
#define GMAC_SW_DMA_INTSTAT_RAW_STAT_PEND_MASK                                                              (0x00000001u)

#define GMAC_SW_DMA_INTSTAT_RAW_HOST_PEND_SHIFT                                                             (0x00000001u)
#define GMAC_SW_DMA_INTSTAT_RAW_HOST_PEND_MASK                                                              (0x00000002u)

#define GMAC_SW_DMA_INTSTAT_RAW_RESERVED1_SHIFT                                                             (0x00000002u)
#define GMAC_SW_DMA_INTSTAT_RAW_RESERVED1_MASK                                                              (0xFFFFFFFCu)


/*!********************************** GMAC_SW_DMA_INTSTAT_MASKED ************************************/

#define GMAC_SW_DMA_INTSTAT_MASKED_STAT_PEND_SHIFT                                                          (0x00000000u)
#define GMAC_SW_DMA_INTSTAT_MASKED_STAT_PEND_MASK                                                           (0x00000001u)

#define GMAC_SW_DMA_INTSTAT_MASKED_HOST_PEND_SHIFT                                                          (0x00000001u)
#define GMAC_SW_DMA_INTSTAT_MASKED_HOST_PEND_MASK                                                           (0x00000002u)

#define GMAC_SW_DMA_INTSTAT_MASKED_RESERVED1_SHIFT                                                          (0x00000002u)
#define GMAC_SW_DMA_INTSTAT_MASKED_RESERVED1_MASK                                                           (0xFFFFFFFCu)


/*!*********************************** GMAC_SW_DMA_INTMASK_SET *************************************/

#define GMAC_SW_DMA_INTMASK_SET_STAT_INT_MASK_SHIFT                                                         (0x00000000u)
#define GMAC_SW_DMA_INTMASK_SET_STAT_INT_MASK_MASK                                                          (0x00000001u)

#define GMAC_SW_DMA_INTMASK_SET_HOST_ERR_INT_MASK_SHIFT                                                     (0x00000001u)
#define GMAC_SW_DMA_INTMASK_SET_HOST_ERR_INT_MASK_MASK                                                      (0x00000002u)

#define GMAC_SW_DMA_INTMASK_SET_RESERVED1_SHIFT                                                             (0x00000002u)
#define GMAC_SW_DMA_INTMASK_SET_RESERVED1_MASK                                                              (0xFFFFFFFCu)


/*!********************************** GMAC_SW_DMA_INTMASK_CLEAR ************************************/

#define GMAC_SW_DMA_INTMASK_CLEAR_STAT_INT_MASK_SHIFT                                                       (0x00000000u)
#define GMAC_SW_DMA_INTMASK_CLEAR_STAT_INT_MASK_MASK                                                        (0x00000001u)

#define GMAC_SW_DMA_INTMASK_CLEAR_HOST_ERR_INT_MASK_SHIFT                                                   (0x00000001u)
#define GMAC_SW_DMA_INTMASK_CLEAR_HOST_ERR_INT_MASK_MASK                                                    (0x00000002u)

#define GMAC_SW_DMA_INTMASK_CLEAR_RESERVED1_SHIFT                                                           (0x00000002u)
#define GMAC_SW_DMA_INTMASK_CLEAR_RESERVED1_MASK                                                            (0xFFFFFFFCu)


/*!************************************ GMAC_SW_RX0_PENDTHRESH **************************************/

#define GMAC_SW_RX0_PENDTHRESH_RX_PENDTHRESH_SHIFT                                                          (0x00000000u)
#define GMAC_SW_RX0_PENDTHRESH_RX_PENDTHRESH_MASK                                                           (0x000000FFu)

#define GMAC_SW_RX0_PENDTHRESH_RESERVED1_SHIFT                                                              (0x00000008u)
#define GMAC_SW_RX0_PENDTHRESH_RESERVED1_MASK                                                               (0xFFFFFF00u)


/*!************************************ GMAC_SW_RX1_PENDTHRESH **************************************/

#define GMAC_SW_RX1_PENDTHRESH_RX_PENDTHRESH_SHIFT                                                          (0x00000000u)
#define GMAC_SW_RX1_PENDTHRESH_RX_PENDTHRESH_MASK                                                           (0x000000FFu)

#define GMAC_SW_RX1_PENDTHRESH_RESERVED1_SHIFT                                                              (0x00000008u)
#define GMAC_SW_RX1_PENDTHRESH_RESERVED1_MASK                                                               (0xFFFFFF00u)


/*!************************************ GMAC_SW_RX2_PENDTHRESH **************************************/

#define GMAC_SW_RX2_PENDTHRESH_RX_PENDTHRESH_SHIFT                                                          (0x00000000u)
#define GMAC_SW_RX2_PENDTHRESH_RX_PENDTHRESH_MASK                                                           (0x000000FFu)

#define GMAC_SW_RX2_PENDTHRESH_RESERVED1_SHIFT                                                              (0x00000008u)
#define GMAC_SW_RX2_PENDTHRESH_RESERVED1_MASK                                                               (0xFFFFFF00u)


/*!************************************ GMAC_SW_RX3_PENDTHRESH **************************************/

#define GMAC_SW_RX3_PENDTHRESH_RX_PENDTHRESH_SHIFT                                                          (0x00000000u)
#define GMAC_SW_RX3_PENDTHRESH_RX_PENDTHRESH_MASK                                                           (0x000000FFu)

#define GMAC_SW_RX3_PENDTHRESH_RESERVED1_SHIFT                                                              (0x00000008u)
#define GMAC_SW_RX3_PENDTHRESH_RESERVED1_MASK                                                               (0xFFFFFF00u)


/*!************************************ GMAC_SW_RX4_PENDTHRESH **************************************/

#define GMAC_SW_RX4_PENDTHRESH_RX_PENDTHRESH_SHIFT                                                          (0x00000000u)
#define GMAC_SW_RX4_PENDTHRESH_RX_PENDTHRESH_MASK                                                           (0x000000FFu)

#define GMAC_SW_RX4_PENDTHRESH_RESERVED1_SHIFT                                                              (0x00000008u)
#define GMAC_SW_RX4_PENDTHRESH_RESERVED1_MASK                                                               (0xFFFFFF00u)


/*!************************************ GMAC_SW_RX5_PENDTHRESH **************************************/

#define GMAC_SW_RX5_PENDTHRESH_RX_PENDTHRESH_SHIFT                                                          (0x00000000u)
#define GMAC_SW_RX5_PENDTHRESH_RX_PENDTHRESH_MASK                                                           (0x000000FFu)

#define GMAC_SW_RX5_PENDTHRESH_RESERVED1_SHIFT                                                              (0x00000008u)
#define GMAC_SW_RX5_PENDTHRESH_RESERVED1_MASK                                                               (0xFFFFFF00u)


/*!************************************ GMAC_SW_RX6_PENDTHRESH **************************************/

#define GMAC_SW_RX6_PENDTHRESH_RX_PENDTHRESH_SHIFT                                                          (0x00000000u)
#define GMAC_SW_RX6_PENDTHRESH_RX_PENDTHRESH_MASK                                                           (0x000000FFu)

#define GMAC_SW_RX6_PENDTHRESH_RESERVED1_SHIFT                                                              (0x00000008u)
#define GMAC_SW_RX6_PENDTHRESH_RESERVED1_MASK                                                               (0xFFFFFF00u)


/*!************************************ GMAC_SW_RX7_PENDTHRESH **************************************/

#define GMAC_SW_RX7_PENDTHRESH_RX_PENDTHRESH_SHIFT                                                          (0x00000000u)
#define GMAC_SW_RX7_PENDTHRESH_RX_PENDTHRESH_MASK                                                           (0x000000FFu)

#define GMAC_SW_RX7_PENDTHRESH_RESERVED1_SHIFT                                                              (0x00000008u)
#define GMAC_SW_RX7_PENDTHRESH_RESERVED1_MASK                                                               (0xFFFFFF00u)


/*!************************************ GMAC_SW_RX0_FREEBUFFER **************************************/

#define GMAC_SW_RX0_FREEBUFFER_RX_FREEBUFFER_SHIFT                                                          (0x00000000u)
#define GMAC_SW_RX0_FREEBUFFER_RX_FREEBUFFER_MASK                                                           (0x0000FFFFu)

#define GMAC_SW_RX0_FREEBUFFER_RESERVED1_SHIFT                                                              (0x00000010u)
#define GMAC_SW_RX0_FREEBUFFER_RESERVED1_MASK                                                               (0xFFFF0000u)


/*!************************************ GMAC_SW_RX1_FREEBUFFER **************************************/

#define GMAC_SW_RX1_FREEBUFFER_RX_FREEBUFFER_SHIFT                                                          (0x00000000u)
#define GMAC_SW_RX1_FREEBUFFER_RX_FREEBUFFER_MASK                                                           (0x0000FFFFu)

#define GMAC_SW_RX1_FREEBUFFER_RESERVED1_SHIFT                                                              (0x00000010u)
#define GMAC_SW_RX1_FREEBUFFER_RESERVED1_MASK                                                               (0xFFFF0000u)


/*!************************************ GMAC_SW_RX2_FREEBUFFER **************************************/

#define GMAC_SW_RX2_FREEBUFFER_RX_FREEBUFFER_SHIFT                                                          (0x00000000u)
#define GMAC_SW_RX2_FREEBUFFER_RX_FREEBUFFER_MASK                                                           (0x0000FFFFu)

#define GMAC_SW_RX2_FREEBUFFER_RESERVED1_SHIFT                                                              (0x00000010u)
#define GMAC_SW_RX2_FREEBUFFER_RESERVED1_MASK                                                               (0xFFFF0000u)


/*!************************************ GMAC_SW_RX3_FREEBUFFER **************************************/

#define GMAC_SW_RX3_FREEBUFFER_RX_FREEBUFFER_SHIFT                                                          (0x00000000u)
#define GMAC_SW_RX3_FREEBUFFER_RX_FREEBUFFER_MASK                                                           (0x0000FFFFu)

#define GMAC_SW_RX3_FREEBUFFER_RESERVED1_SHIFT                                                              (0x00000010u)
#define GMAC_SW_RX3_FREEBUFFER_RESERVED1_MASK                                                               (0xFFFF0000u)


/*!************************************ GMAC_SW_RX4_FREEBUFFER **************************************/

#define GMAC_SW_RX4_FREEBUFFER_RX_FREEBUFFER_SHIFT                                                          (0x00000000u)
#define GMAC_SW_RX4_FREEBUFFER_RX_FREEBUFFER_MASK                                                           (0x0000FFFFu)

#define GMAC_SW_RX4_FREEBUFFER_RESERVED1_SHIFT                                                              (0x00000010u)
#define GMAC_SW_RX4_FREEBUFFER_RESERVED1_MASK                                                               (0xFFFF0000u)


/*!************************************ GMAC_SW_RX5_FREEBUFFER **************************************/

#define GMAC_SW_RX5_FREEBUFFER_RX_FREEBUFFER_SHIFT                                                          (0x00000000u)
#define GMAC_SW_RX5_FREEBUFFER_RX_FREEBUFFER_MASK                                                           (0x0000FFFFu)

#define GMAC_SW_RX5_FREEBUFFER_RESERVED1_SHIFT                                                              (0x00000010u)
#define GMAC_SW_RX5_FREEBUFFER_RESERVED1_MASK                                                               (0xFFFF0000u)


/*!************************************ GMAC_SW_RX6_FREEBUFFER **************************************/

#define GMAC_SW_RX6_FREEBUFFER_RX_FREEBUFFER_SHIFT                                                          (0x00000000u)
#define GMAC_SW_RX6_FREEBUFFER_RX_FREEBUFFER_MASK                                                           (0x0000FFFFu)

#define GMAC_SW_RX6_FREEBUFFER_RESERVED1_SHIFT                                                              (0x00000010u)
#define GMAC_SW_RX6_FREEBUFFER_RESERVED1_MASK                                                               (0xFFFF0000u)


/*!************************************ GMAC_SW_RX7_FREEBUFFER **************************************/

#define GMAC_SW_RX7_FREEBUFFER_RX_FREEBUFFER_SHIFT                                                          (0x00000000u)
#define GMAC_SW_RX7_FREEBUFFER_RX_FREEBUFFER_MASK                                                           (0x0000FFFFu)

#define GMAC_SW_RX7_FREEBUFFER_RESERVED1_SHIFT                                                              (0x00000010u)
#define GMAC_SW_RX7_FREEBUFFER_RESERVED1_MASK                                                               (0xFFFF0000u)


/*!**************************************************************************************************
* End of File
****************************************************************************************************/
#ifdef __cplusplus
}
#endif

#endif  /* _HW_GMACSW_CPDMA_H_ */
