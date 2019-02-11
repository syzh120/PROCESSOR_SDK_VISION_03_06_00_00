/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014-2016
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

/**
*
*  \file   hw_mcspi.h
*
*  \brief  register-level header file for MCSPI
*
**/

#ifndef HW_MCSPI_H_
#define HW_MCSPI_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define MCSPI_HL_REV                                                                                        ((uint32_t)0x0U)
#define MCSPI_HL_HWINFO                                                                                     ((uint32_t)0x4U)
#define MCSPI_HL_SYSCONFIG                                                                                  ((uint32_t)0x10U)
#define MCSPI_REVISION                                                                                      ((uint32_t)0x100U)
#define MCSPI_SYSCONFIG                                                                                     ((uint32_t)0x110U)
#define MCSPI_SYSSTATUS                                                                                     ((uint32_t)0x114U)
#define MCSPI_IRQSTATUS                                                                                     ((uint32_t)0x118U)
#define MCSPI_IRQENABLE                                                                                     ((uint32_t)0x11cU)
#define MCSPI_WAKEUPENABLE                                                                                  ((uint32_t)0x120U)
#define MCSPI_SYST                                                                                          ((uint32_t)0x124U)
#define MCSPI_MODULCTRL                                                                                     ((uint32_t)0x128U)
#define MCSPI_CH0CONF                                                                                       ((uint32_t)0x12cU)
#define MCSPI_CH0STAT                                                                                       ((uint32_t)0x130U)
#define MCSPI_CH0CTRL                                                                                       ((uint32_t)0x134U)
#define MCSPI_TX0                                                                                           ((uint32_t)0x138U)
#define MCSPI_RX0                                                                                           ((uint32_t)0x13cU)
#define MCSPI_CH1CONF                                                                                       ((uint32_t)0x140U)
#define MCSPI_CH1STAT                                                                                       ((uint32_t)0x144U)
#define MCSPI_CH1CTRL                                                                                       ((uint32_t)0x148U)
#define MCSPI_TX1                                                                                           ((uint32_t)0x14cU)
#define MCSPI_RX1                                                                                           ((uint32_t)0x150U)
#define MCSPI_CH2CONF                                                                                       ((uint32_t)0x154U)
#define MCSPI_CH2STAT                                                                                       ((uint32_t)0x158U)
#define MCSPI_CH2CTRL                                                                                       ((uint32_t)0x15cU)
#define MCSPI_TX2                                                                                           ((uint32_t)0x160U)
#define MCSPI_RX2                                                                                           ((uint32_t)0x164U)
#define MCSPI_CH3CONF                                                                                       ((uint32_t)0x168U)
#define MCSPI_CH3STAT                                                                                       ((uint32_t)0x16cU)
#define MCSPI_CH3CTRL                                                                                       ((uint32_t)0x170U)
#define MCSPI_TX3                                                                                           ((uint32_t)0x174U)
#define MCSPI_RX3                                                                                           ((uint32_t)0x178U)
#define MCSPI_XFERLEVEL                                                                                     ((uint32_t)0x17cU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define MCSPI_HL_REV_REVISION_SHIFT                                                                         ((uint32_t)0U)
#define MCSPI_HL_REV_REVISION_MASK                                                                          ((uint32_t)0xffffffffU)

#define MCSPI_HL_HWINFO_USEFIFO_SHIFT                                                                       ((uint32_t)0U)
#define MCSPI_HL_HWINFO_USEFIFO_MASK                                                                        ((uint32_t)0x00000001U)
#define MCSPI_HL_HWINFO_USEFIFO_FIFOEN                                                                       ((uint32_t)1U)
#define MCSPI_HL_HWINFO_USEFIFO_NOFIFO                                                                       ((uint32_t)0U)

#define MCSPI_HL_HWINFO_FFNBYTE_SHIFT                                                                       ((uint32_t)1U)
#define MCSPI_HL_HWINFO_FFNBYTE_MASK                                                                        ((uint32_t)0x0000003eU)
#define MCSPI_HL_HWINFO_FFNBYTE_FF16BYTES                                                                    ((uint32_t)1U)
#define MCSPI_HL_HWINFO_FFNBYTE_FF32BYTES                                                                    ((uint32_t)2U)
#define MCSPI_HL_HWINFO_FFNBYTE_FF64BYTES                                                                    ((uint32_t)4U)
#define MCSPI_HL_HWINFO_FFNBYTE_FF128BYTES                                                                   ((uint32_t)8U)
#define MCSPI_HL_HWINFO_FFNBYTE_FF256BYTES                                                                   ((uint32_t)16U)

#define MCSPI_HL_HWINFO_RSVD_SHIFT                                                                          ((uint32_t)7U)
#define MCSPI_HL_HWINFO_RSVD_MASK                                                                           ((uint32_t)0xffffff80U)

#define MCSPI_HL_HWINFO_RETMODE_SHIFT                                                                       ((uint32_t)6U)
#define MCSPI_HL_HWINFO_RETMODE_MASK                                                                        ((uint32_t)0x00000040U)
#define MCSPI_HL_HWINFO_RETMODE_NORETMODE                                                                    ((uint32_t)0U)
#define MCSPI_HL_HWINFO_RETMODE_RETMODEEN                                                                    ((uint32_t)1U)

#define MCSPI_HL_SYSCONFIG_IDLEMODE_SHIFT                                                                   ((uint32_t)2U)
#define MCSPI_HL_SYSCONFIG_IDLEMODE_MASK                                                                    ((uint32_t)0x0000000cU)
#define MCSPI_HL_SYSCONFIG_IDLEMODE_SMARTIDLEWAKEUP                                                          ((uint32_t)3U)
#define MCSPI_HL_SYSCONFIG_IDLEMODE_FORCEIDLE                                                                ((uint32_t)0U)
#define MCSPI_HL_SYSCONFIG_IDLEMODE_NOIDLE                                                                   ((uint32_t)1U)
#define MCSPI_HL_SYSCONFIG_IDLEMODE_SMARTIDLE                                                                ((uint32_t)2U)

#define MCSPI_HL_SYSCONFIG_RSVD_SHIFT                                                                       ((uint32_t)4U)
#define MCSPI_HL_SYSCONFIG_RSVD_MASK                                                                        ((uint32_t)0xfffffff0U)

#define MCSPI_HL_SYSCONFIG_SOFTRESET_SHIFT                                                                  ((uint32_t)0U)
#define MCSPI_HL_SYSCONFIG_SOFTRESET_MASK                                                                   ((uint32_t)0x00000001U)
#define MCSPI_HL_SYSCONFIG_SOFTRESET_RESETDONE                                                               ((uint32_t)0U)
#define MCSPI_HL_SYSCONFIG_SOFTRESET_NOACTION                                                                ((uint32_t)0U)
#define MCSPI_HL_SYSCONFIG_SOFTRESET_SOFTRESET                                                               ((uint32_t)1U)
#define MCSPI_HL_SYSCONFIG_SOFTRESET_RESETONGOING                                                            ((uint32_t)1U)

#define MCSPI_HL_SYSCONFIG_FREEEMU_SHIFT                                                                    ((uint32_t)1U)
#define MCSPI_HL_SYSCONFIG_FREEEMU_MASK                                                                     ((uint32_t)0x00000002U)
#define MCSPI_HL_SYSCONFIG_FREEEMU_EMUDIS                                                                    ((uint32_t)1U)
#define MCSPI_HL_SYSCONFIG_FREEEMU_EMUEN                                                                     ((uint32_t)0U)

#define MCSPI_REVISION_REVISION_SHIFT                                                                       ((uint32_t)0U)
#define MCSPI_REVISION_REVISION_MASK                                                                        ((uint32_t)0xffffffffU)

#define MCSPI_SYSCONFIG_SIDLEMODE_SHIFT                                                                     ((uint32_t)3U)
#define MCSPI_SYSCONFIG_SIDLEMODE_MASK                                                                      ((uint32_t)0x00000018U)
#define MCSPI_SYSCONFIG_SIDLEMODE_FORCE                                                                      ((uint32_t)0U)
#define MCSPI_SYSCONFIG_SIDLEMODE_NO                                                                         ((uint32_t)1U)
#define MCSPI_SYSCONFIG_SIDLEMODE_SMART                                                                      ((uint32_t)2U)
#define MCSPI_SYSCONFIG_SIDLEMODE_SMART_IDLE_WAKEUP                                                          ((uint32_t)3U)

#define MCSPI_SYSCONFIG_RESERVED_14_SHIFT                                                                   ((uint32_t)10U)
#define MCSPI_SYSCONFIG_RESERVED_14_MASK                                                                    ((uint32_t)0xfffffc00U)

#define MCSPI_SYSCONFIG_SOFTRESET_SHIFT                                                                     ((uint32_t)1U)
#define MCSPI_SYSCONFIG_SOFTRESET_MASK                                                                      ((uint32_t)0x00000002U)
#define MCSPI_SYSCONFIG_SOFTRESET_OFF                                                                        ((uint32_t)0U)
#define MCSPI_SYSCONFIG_SOFTRESET_ON                                                                         ((uint32_t)1U)

#define MCSPI_SYSCONFIG_CLOCKACTIVITY_SHIFT                                                                 ((uint32_t)8U)
#define MCSPI_SYSCONFIG_CLOCKACTIVITY_MASK                                                                  ((uint32_t)0x00000300U)
#define MCSPI_SYSCONFIG_CLOCKACTIVITY_NONE                                                                   ((uint32_t)0U)
#define MCSPI_SYSCONFIG_CLOCKACTIVITY_OCP                                                                    ((uint32_t)1U)
#define MCSPI_SYSCONFIG_CLOCKACTIVITY_FUNC                                                                   ((uint32_t)2U)
#define MCSPI_SYSCONFIG_CLOCKACTIVITY_BOTH                                                                   ((uint32_t)3U)

#define MCSPI_SYSCONFIG_AUTOIDLE_SHIFT                                                                      ((uint32_t)0U)
#define MCSPI_SYSCONFIG_AUTOIDLE_MASK                                                                       ((uint32_t)0x00000001U)
#define MCSPI_SYSCONFIG_AUTOIDLE_OFF                                                                         ((uint32_t)0U)
#define MCSPI_SYSCONFIG_AUTOIDLE_ON                                                                          ((uint32_t)1U)

#define MCSPI_SYSCONFIG_ENAWAKEUP_SHIFT                                                                     ((uint32_t)2U)
#define MCSPI_SYSCONFIG_ENAWAKEUP_MASK                                                                      ((uint32_t)0x00000004U)
#define MCSPI_SYSCONFIG_ENAWAKEUP_NOWAKEUP                                                                   ((uint32_t)0U)
#define MCSPI_SYSCONFIG_ENAWAKEUP_ON                                                                         ((uint32_t)1U)

#define MCSPI_SYSCONFIG_RESERVED_15_SHIFT                                                                   ((uint32_t)5U)
#define MCSPI_SYSCONFIG_RESERVED_15_MASK                                                                    ((uint32_t)0x000000e0U)

#define MCSPI_SYSSTATUS_RESERVED_16_SHIFT                                                                   ((uint32_t)1U)
#define MCSPI_SYSSTATUS_RESERVED_16_MASK                                                                    ((uint32_t)0xfffffffeU)

#define MCSPI_SYSSTATUS_RESETDONE_SHIFT                                                                     ((uint32_t)0U)
#define MCSPI_SYSSTATUS_RESETDONE_MASK                                                                      ((uint32_t)0x00000001U)
#define MCSPI_SYSSTATUS_RESETDONE_INPROGRESS                                                                 ((uint32_t)0U)
#define MCSPI_SYSSTATUS_RESETDONE_COMPLETED                                                                  ((uint32_t)1U)

#define MCSPI_IRQSTATUS_RESERVED_7_SHIFT                                                                    ((uint32_t)15U)
#define MCSPI_IRQSTATUS_RESERVED_7_MASK                                                                     ((uint32_t)0x00008000U)

#define MCSPI_IRQSTATUS_RX3_FULL_SHIFT                                                                      ((uint32_t)14U)
#define MCSPI_IRQSTATUS_RX3_FULL_MASK                                                                       ((uint32_t)0x00004000U)
#define MCSPI_IRQSTATUS_RX3_FULL_NOEVNT_R                                                                    ((uint32_t)0U)
#define MCSPI_IRQSTATUS_RX3_FULL_EVNT_R                                                                      ((uint32_t)1U)
#define MCSPI_IRQSTATUS_RX3_FULL_NOEFFECT_W                                                                  ((uint32_t)0U)
#define MCSPI_IRQSTATUS_RX3_FULL_CLEARSRC_W                                                                  ((uint32_t)1U)

#define MCSPI_IRQSTATUS_RESERVED_8_SHIFT                                                                    ((uint32_t)18U)
#define MCSPI_IRQSTATUS_RESERVED_8_MASK                                                                     ((uint32_t)0xfffc0000U)

#define MCSPI_IRQSTATUS_WKS_SHIFT                                                                           ((uint32_t)16U)
#define MCSPI_IRQSTATUS_WKS_MASK                                                                            ((uint32_t)0x00010000U)
#define MCSPI_IRQSTATUS_WKS_NOEVNT_R                                                                         ((uint32_t)0U)
#define MCSPI_IRQSTATUS_WKS_EVNT_R                                                                           ((uint32_t)1U)
#define MCSPI_IRQSTATUS_WKS_NOEFFECT_W                                                                       ((uint32_t)0U)
#define MCSPI_IRQSTATUS_WKS_CLEARSRC_W                                                                       ((uint32_t)1U)

#define MCSPI_IRQSTATUS_RESERVED_9_SHIFT                                                                    ((uint32_t)11U)
#define MCSPI_IRQSTATUS_RESERVED_9_MASK                                                                     ((uint32_t)0x00000800U)

#define MCSPI_IRQSTATUS_RX2_FULL_SHIFT                                                                      ((uint32_t)10U)
#define MCSPI_IRQSTATUS_RX2_FULL_MASK                                                                       ((uint32_t)0x00000400U)
#define MCSPI_IRQSTATUS_RX2_FULL_NOEVNT_R                                                                    ((uint32_t)0U)
#define MCSPI_IRQSTATUS_RX2_FULL_EVNT_R                                                                      ((uint32_t)1U)
#define MCSPI_IRQSTATUS_RX2_FULL_NOEFFECT_W                                                                  ((uint32_t)0U)
#define MCSPI_IRQSTATUS_RX2_FULL_CLEARSRC_W                                                                  ((uint32_t)1U)

#define MCSPI_IRQSTATUS_TX3_EMPTY_SHIFT                                                                     ((uint32_t)12U)
#define MCSPI_IRQSTATUS_TX3_EMPTY_MASK                                                                      ((uint32_t)0x00001000U)
#define MCSPI_IRQSTATUS_TX3_EMPTY_NOEVNT_R                                                                   ((uint32_t)0U)
#define MCSPI_IRQSTATUS_TX3_EMPTY_EVNT_R                                                                     ((uint32_t)1U)
#define MCSPI_IRQSTATUS_TX3_EMPTY_NOEFFECT_W                                                                 ((uint32_t)0U)
#define MCSPI_IRQSTATUS_TX3_EMPTY_CLEARSRC_W                                                                 ((uint32_t)1U)

#define MCSPI_IRQSTATUS_RX1_FULL_SHIFT                                                                      ((uint32_t)6U)
#define MCSPI_IRQSTATUS_RX1_FULL_MASK                                                                       ((uint32_t)0x00000040U)
#define MCSPI_IRQSTATUS_RX1_FULL_NOEVNT_R                                                                    ((uint32_t)0U)
#define MCSPI_IRQSTATUS_RX1_FULL_EVNT_R                                                                      ((uint32_t)1U)
#define MCSPI_IRQSTATUS_RX1_FULL_NOEFFECT_W                                                                  ((uint32_t)0U)
#define MCSPI_IRQSTATUS_RX1_FULL_CLEARSRC_W                                                                  ((uint32_t)1U)

#define MCSPI_IRQSTATUS_TX3_UNDERFLOW_SHIFT                                                                 ((uint32_t)13U)
#define MCSPI_IRQSTATUS_TX3_UNDERFLOW_MASK                                                                  ((uint32_t)0x00002000U)
#define MCSPI_IRQSTATUS_TX3_UNDERFLOW_NOEVNT_R                                                               ((uint32_t)0U)
#define MCSPI_IRQSTATUS_TX3_UNDERFLOW_EVNT_R                                                                 ((uint32_t)1U)
#define MCSPI_IRQSTATUS_TX3_UNDERFLOW_NOEFFECT_W                                                             ((uint32_t)0U)
#define MCSPI_IRQSTATUS_TX3_UNDERFLOW_CLEARSRC_W                                                             ((uint32_t)1U)

#define MCSPI_IRQSTATUS_TX2_EMPTY_SHIFT                                                                     ((uint32_t)8U)
#define MCSPI_IRQSTATUS_TX2_EMPTY_MASK                                                                      ((uint32_t)0x00000100U)
#define MCSPI_IRQSTATUS_TX2_EMPTY_NOEVNT_R                                                                   ((uint32_t)0U)
#define MCSPI_IRQSTATUS_TX2_EMPTY_EVNT_R                                                                     ((uint32_t)1U)
#define MCSPI_IRQSTATUS_TX2_EMPTY_NOEFFECT_W                                                                 ((uint32_t)0U)
#define MCSPI_IRQSTATUS_TX2_EMPTY_CLEARSRC_W                                                                 ((uint32_t)1U)

#define MCSPI_IRQSTATUS_TX2_UNDERFLOW_SHIFT                                                                 ((uint32_t)9U)
#define MCSPI_IRQSTATUS_TX2_UNDERFLOW_MASK                                                                  ((uint32_t)0x00000200U)
#define MCSPI_IRQSTATUS_TX2_UNDERFLOW_NOEVNT_R                                                               ((uint32_t)0U)
#define MCSPI_IRQSTATUS_TX2_UNDERFLOW_EVNT_R                                                                 ((uint32_t)1U)
#define MCSPI_IRQSTATUS_TX2_UNDERFLOW_NOEFFECT_W                                                             ((uint32_t)0U)
#define MCSPI_IRQSTATUS_TX2_UNDERFLOW_CLEARSRC_W                                                             ((uint32_t)1U)

#define MCSPI_IRQSTATUS_TX1_EMPTY_SHIFT                                                                     ((uint32_t)4U)
#define MCSPI_IRQSTATUS_TX1_EMPTY_MASK                                                                      ((uint32_t)0x00000010U)
#define MCSPI_IRQSTATUS_TX1_EMPTY_NOEVNT_R                                                                   ((uint32_t)0U)
#define MCSPI_IRQSTATUS_TX1_EMPTY_EVNT_R                                                                     ((uint32_t)1U)
#define MCSPI_IRQSTATUS_TX1_EMPTY_NOEFFECT_W                                                                 ((uint32_t)0U)
#define MCSPI_IRQSTATUS_TX1_EMPTY_CLEARSRC_W                                                                 ((uint32_t)1U)

#define MCSPI_IRQSTATUS_TX0_UNDERFLOW_SHIFT                                                                 ((uint32_t)1U)
#define MCSPI_IRQSTATUS_TX0_UNDERFLOW_MASK                                                                  ((uint32_t)0x00000002U)
#define MCSPI_IRQSTATUS_TX0_UNDERFLOW_NOEVNT_R                                                               ((uint32_t)0U)
#define MCSPI_IRQSTATUS_TX0_UNDERFLOW_EVNT_R                                                                 ((uint32_t)1U)
#define MCSPI_IRQSTATUS_TX0_UNDERFLOW_NOEFFECT_W                                                             ((uint32_t)0U)
#define MCSPI_IRQSTATUS_TX0_UNDERFLOW_CLEARSRC_W                                                             ((uint32_t)1U)

#define MCSPI_IRQSTATUS_TX1_UNDERFLOW_SHIFT                                                                 ((uint32_t)5U)
#define MCSPI_IRQSTATUS_TX1_UNDERFLOW_MASK                                                                  ((uint32_t)0x00000020U)
#define MCSPI_IRQSTATUS_TX1_UNDERFLOW_NOEVNT_R                                                               ((uint32_t)0U)
#define MCSPI_IRQSTATUS_TX1_UNDERFLOW_EVNT_R                                                                 ((uint32_t)1U)
#define MCSPI_IRQSTATUS_TX1_UNDERFLOW_NOEFFECT_W                                                             ((uint32_t)0U)
#define MCSPI_IRQSTATUS_TX1_UNDERFLOW_CLEARSRC_W                                                             ((uint32_t)1U)

#define MCSPI_IRQSTATUS_RESERVED_10_SHIFT                                                                   ((uint32_t)7U)
#define MCSPI_IRQSTATUS_RESERVED_10_MASK                                                                    ((uint32_t)0x00000080U)

#define MCSPI_IRQSTATUS_RX0_FULL_SHIFT                                                                      ((uint32_t)2U)
#define MCSPI_IRQSTATUS_RX0_FULL_MASK                                                                       ((uint32_t)0x00000004U)
#define MCSPI_IRQSTATUS_RX0_FULL_NOEVNT_R                                                                    ((uint32_t)0U)
#define MCSPI_IRQSTATUS_RX0_FULL_EVNT_R                                                                      ((uint32_t)1U)
#define MCSPI_IRQSTATUS_RX0_FULL_NOEFFECT_W                                                                  ((uint32_t)0U)
#define MCSPI_IRQSTATUS_RX0_FULL_CLEARSRC_W                                                                  ((uint32_t)1U)

#define MCSPI_IRQSTATUS_RX0_OVERFLOW_SHIFT                                                                  ((uint32_t)3U)
#define MCSPI_IRQSTATUS_RX0_OVERFLOW_MASK                                                                   ((uint32_t)0x00000008U)
#define MCSPI_IRQSTATUS_RX0_OVERFLOW_NOEVNT_R                                                                ((uint32_t)0U)
#define MCSPI_IRQSTATUS_RX0_OVERFLOW_EVNT_R                                                                  ((uint32_t)1U)
#define MCSPI_IRQSTATUS_RX0_OVERFLOW_NOEFFECT_W                                                              ((uint32_t)0U)
#define MCSPI_IRQSTATUS_RX0_OVERFLOW_CLEARSRC_W                                                              ((uint32_t)1U)

#define MCSPI_IRQSTATUS_TX0_EMPTY_SHIFT                                                                     ((uint32_t)0U)
#define MCSPI_IRQSTATUS_TX0_EMPTY_MASK                                                                      ((uint32_t)0x00000001U)
#define MCSPI_IRQSTATUS_TX0_EMPTY_NOEVNT_R                                                                   ((uint32_t)0U)
#define MCSPI_IRQSTATUS_TX0_EMPTY_EVNT_R                                                                     ((uint32_t)1U)
#define MCSPI_IRQSTATUS_TX0_EMPTY_NOEFFECT_W                                                                 ((uint32_t)0U)
#define MCSPI_IRQSTATUS_TX0_EMPTY_CLEARSRC_W                                                                 ((uint32_t)1U)

#define MCSPI_IRQSTATUS_EOW_SHIFT                                                                           ((uint32_t)17U)
#define MCSPI_IRQSTATUS_EOW_MASK                                                                            ((uint32_t)0x00020000U)
#define MCSPI_IRQSTATUS_EOW_NOEVNT_R                                                                         ((uint32_t)0U)
#define MCSPI_IRQSTATUS_EOW_EVNT_R                                                                           ((uint32_t)1U)
#define MCSPI_IRQSTATUS_EOW_CLEARSRC_W                                                                       ((uint32_t)1U)
#define MCSPI_IRQSTATUS_EOW_NOEFFECT_W                                                                       ((uint32_t)0U)

#define MCSPI_IRQENABLE_RESERVED_3_SHIFT                                                                    ((uint32_t)7U)
#define MCSPI_IRQENABLE_RESERVED_3_MASK                                                                     ((uint32_t)0x00000080U)

#define MCSPI_IRQENABLE_TX2_UNDERFLOW_ENABLE_SHIFT                                                          ((uint32_t)9U)
#define MCSPI_IRQENABLE_TX2_UNDERFLOW_ENABLE_MASK                                                           ((uint32_t)0x00000200U)
#define MCSPI_IRQENABLE_TX2_UNDERFLOW_ENABLE_IRQDISABLED                                                     ((uint32_t)0U)
#define MCSPI_IRQENABLE_TX2_UNDERFLOW_ENABLE_IRQENABLED                                                      ((uint32_t)1U)

#define MCSPI_IRQENABLE_RESERVED_4_SHIFT                                                                    ((uint32_t)15U)
#define MCSPI_IRQENABLE_RESERVED_4_MASK                                                                     ((uint32_t)0x00008000U)

#define MCSPI_IRQENABLE_TX0_EMPTY_ENABLE_SHIFT                                                              ((uint32_t)0U)
#define MCSPI_IRQENABLE_TX0_EMPTY_ENABLE_MASK                                                               ((uint32_t)0x00000001U)
#define MCSPI_IRQENABLE_TX0_EMPTY_ENABLE_IRQDISABLED                                                         ((uint32_t)0U)
#define MCSPI_IRQENABLE_TX0_EMPTY_ENABLE_IRQENABLED                                                          ((uint32_t)1U)

#define MCSPI_IRQENABLE_RX0_FULL_ENABLE_SHIFT                                                               ((uint32_t)2U)
#define MCSPI_IRQENABLE_RX0_FULL_ENABLE_MASK                                                                ((uint32_t)0x00000004U)
#define MCSPI_IRQENABLE_RX0_FULL_ENABLE_IRQDISABLED                                                          ((uint32_t)0U)
#define MCSPI_IRQENABLE_RX0_FULL_ENABLE_IRQENABLED                                                           ((uint32_t)1U)

#define MCSPI_IRQENABLE_TX1_EMPTY_ENABLE_SHIFT                                                              ((uint32_t)4U)
#define MCSPI_IRQENABLE_TX1_EMPTY_ENABLE_MASK                                                               ((uint32_t)0x00000010U)
#define MCSPI_IRQENABLE_TX1_EMPTY_ENABLE_IRQDISABLED                                                         ((uint32_t)0U)
#define MCSPI_IRQENABLE_TX1_EMPTY_ENABLE_IRQENABLED                                                          ((uint32_t)1U)

#define MCSPI_IRQENABLE_RX1_FULL_ENABLE_SHIFT                                                               ((uint32_t)6U)
#define MCSPI_IRQENABLE_RX1_FULL_ENABLE_MASK                                                                ((uint32_t)0x00000040U)
#define MCSPI_IRQENABLE_RX1_FULL_ENABLE_IRQDISABLED                                                          ((uint32_t)0U)
#define MCSPI_IRQENABLE_RX1_FULL_ENABLE_IRQENABLED                                                           ((uint32_t)1U)

#define MCSPI_IRQENABLE_TX3_EMPTY_ENABLE_SHIFT                                                              ((uint32_t)12U)
#define MCSPI_IRQENABLE_TX3_EMPTY_ENABLE_MASK                                                               ((uint32_t)0x00001000U)
#define MCSPI_IRQENABLE_TX3_EMPTY_ENABLE_IRQDISABLED                                                         ((uint32_t)0U)
#define MCSPI_IRQENABLE_TX3_EMPTY_ENABLE_IRQENABLED                                                          ((uint32_t)1U)

#define MCSPI_IRQENABLE_TX0_UNDERFLOW_ENABLE_SHIFT                                                          ((uint32_t)1U)
#define MCSPI_IRQENABLE_TX0_UNDERFLOW_ENABLE_MASK                                                           ((uint32_t)0x00000002U)
#define MCSPI_IRQENABLE_TX0_UNDERFLOW_ENABLE_IRQDISABLED                                                     ((uint32_t)0U)
#define MCSPI_IRQENABLE_TX0_UNDERFLOW_ENABLE_IRQENABLED                                                      ((uint32_t)1U)

#define MCSPI_IRQENABLE_RX0_OVERFLOW_ENABLE_SHIFT                                                           ((uint32_t)3U)
#define MCSPI_IRQENABLE_RX0_OVERFLOW_ENABLE_MASK                                                            ((uint32_t)0x00000008U)
#define MCSPI_IRQENABLE_RX0_OVERFLOW_ENABLE_IRQDISABLED                                                      ((uint32_t)0U)
#define MCSPI_IRQENABLE_RX0_OVERFLOW_ENABLE_IRQENABLED                                                       ((uint32_t)1U)

#define MCSPI_IRQENABLE_RX3_FULL_ENABLE_SHIFT                                                               ((uint32_t)14U)
#define MCSPI_IRQENABLE_RX3_FULL_ENABLE_MASK                                                                ((uint32_t)0x00004000U)
#define MCSPI_IRQENABLE_RX3_FULL_ENABLE_IRQDISABLED                                                          ((uint32_t)0U)
#define MCSPI_IRQENABLE_RX3_FULL_ENABLE_IRQENABLED                                                           ((uint32_t)1U)

#define MCSPI_IRQENABLE_RESERVED_5_SHIFT                                                                    ((uint32_t)18U)
#define MCSPI_IRQENABLE_RESERVED_5_MASK                                                                     ((uint32_t)0xfffc0000U)

#define MCSPI_IRQENABLE_RESERVED_6_SHIFT                                                                    ((uint32_t)11U)
#define MCSPI_IRQENABLE_RESERVED_6_MASK                                                                     ((uint32_t)0x00000800U)

#define MCSPI_IRQENABLE_WKE_SHIFT                                                                           ((uint32_t)16U)
#define MCSPI_IRQENABLE_WKE_MASK                                                                            ((uint32_t)0x00010000U)
#define MCSPI_IRQENABLE_WKE_IRQDISABLED                                                                      ((uint32_t)0U)
#define MCSPI_IRQENABLE_WKE_IRQENABLED                                                                       ((uint32_t)1U)

#define MCSPI_IRQENABLE_TX2_EMPTY_ENABLE_SHIFT                                                              ((uint32_t)8U)
#define MCSPI_IRQENABLE_TX2_EMPTY_ENABLE_MASK                                                               ((uint32_t)0x00000100U)
#define MCSPI_IRQENABLE_TX2_EMPTY_ENABLE_IRQDISABLED                                                         ((uint32_t)0U)
#define MCSPI_IRQENABLE_TX2_EMPTY_ENABLE_IRQENABLED                                                          ((uint32_t)1U)

#define MCSPI_IRQENABLE_RX2_FULL_ENABLE_SHIFT                                                               ((uint32_t)10U)
#define MCSPI_IRQENABLE_RX2_FULL_ENABLE_MASK                                                                ((uint32_t)0x00000400U)
#define MCSPI_IRQENABLE_RX2_FULL_ENABLE_IRQDISABLED                                                          ((uint32_t)0U)
#define MCSPI_IRQENABLE_RX2_FULL_ENABLE_IRQENABLED                                                           ((uint32_t)1U)

#define MCSPI_IRQENABLE_TX3_UNDERFLOW_ENABLE_SHIFT                                                          ((uint32_t)13U)
#define MCSPI_IRQENABLE_TX3_UNDERFLOW_ENABLE_MASK                                                           ((uint32_t)0x00002000U)
#define MCSPI_IRQENABLE_TX3_UNDERFLOW_ENABLE_IRQDISABLED                                                     ((uint32_t)0U)
#define MCSPI_IRQENABLE_TX3_UNDERFLOW_ENABLE_IRQENABLED                                                      ((uint32_t)1U)

#define MCSPI_IRQENABLE_TX1_UNDERFLOW_ENABLE_SHIFT                                                          ((uint32_t)5U)
#define MCSPI_IRQENABLE_TX1_UNDERFLOW_ENABLE_MASK                                                           ((uint32_t)0x00000020U)
#define MCSPI_IRQENABLE_TX1_UNDERFLOW_ENABLE_IRQDISABLED                                                     ((uint32_t)0U)
#define MCSPI_IRQENABLE_TX1_UNDERFLOW_ENABLE_IRQENABLED                                                      ((uint32_t)1U)

#define MCSPI_IRQENABLE_EOW_ENABLE_SHIFT                                                                    ((uint32_t)17U)
#define MCSPI_IRQENABLE_EOW_ENABLE_MASK                                                                     ((uint32_t)0x00020000U)
#define MCSPI_IRQENABLE_EOW_ENABLE_IRQENABLED                                                                ((uint32_t)1U)
#define MCSPI_IRQENABLE_EOW_ENABLE_IRQDISABLED                                                               ((uint32_t)0U)

#define MCSPI_WAKEUPENABLE_RESERVED_18_SHIFT                                                                ((uint32_t)1U)
#define MCSPI_WAKEUPENABLE_RESERVED_18_MASK                                                                 ((uint32_t)0xfffffffeU)

#define MCSPI_WAKEUPENABLE_WKEN_SHIFT                                                                       ((uint32_t)0U)
#define MCSPI_WAKEUPENABLE_WKEN_MASK                                                                        ((uint32_t)0x00000001U)
#define MCSPI_WAKEUPENABLE_WKEN_NOWAKEUP                                                                     ((uint32_t)0U)
#define MCSPI_WAKEUPENABLE_WKEN_WAKEUP                                                                       ((uint32_t)1U)

#define MCSPI_SYST_SPIEN_2_SHIFT                                                                            ((uint32_t)2U)
#define MCSPI_SYST_SPIEN_2_MASK                                                                             ((uint32_t)0x00000004U)

#define MCSPI_SYST_WAKD_SHIFT                                                                               ((uint32_t)7U)
#define MCSPI_SYST_WAKD_MASK                                                                                ((uint32_t)0x00000080U)
#define MCSPI_SYST_WAKD_DRIVENLOW                                                                            ((uint32_t)0U)
#define MCSPI_SYST_WAKD_DRIVENHIGH                                                                           ((uint32_t)1U)

#define MCSPI_SYST_SPIDAT_0_SHIFT                                                                           ((uint32_t)4U)
#define MCSPI_SYST_SPIDAT_0_MASK                                                                            ((uint32_t)0x00000010U)

#define MCSPI_SYST_SPIEN_1_SHIFT                                                                            ((uint32_t)1U)
#define MCSPI_SYST_SPIEN_1_MASK                                                                             ((uint32_t)0x00000002U)

#define MCSPI_SYST_RESERVED_17_SHIFT                                                                        ((uint32_t)12U)
#define MCSPI_SYST_RESERVED_17_MASK                                                                         ((uint32_t)0xfffff000U)

#define MCSPI_SYST_SPIDATDIR1_SHIFT                                                                         ((uint32_t)9U)
#define MCSPI_SYST_SPIDATDIR1_MASK                                                                          ((uint32_t)0x00000200U)
#define MCSPI_SYST_SPIDATDIR1_OUT                                                                            ((uint32_t)0U)
#define MCSPI_SYST_SPIDATDIR1_IN                                                                             ((uint32_t)1U)

#define MCSPI_SYST_SSB_SHIFT                                                                                ((uint32_t)11U)
#define MCSPI_SYST_SSB_MASK                                                                                 ((uint32_t)0x00000800U)
#define MCSPI_SYST_SSB_OFF                                                                                   ((uint32_t)0U)
#define MCSPI_SYST_SSB_SETTHEMALL                                                                            ((uint32_t)1U)

#define MCSPI_SYST_SPICLK_SHIFT                                                                             ((uint32_t)6U)
#define MCSPI_SYST_SPICLK_MASK                                                                              ((uint32_t)0x00000040U)

#define MCSPI_SYST_SPIDATDIR0_SHIFT                                                                         ((uint32_t)8U)
#define MCSPI_SYST_SPIDATDIR0_MASK                                                                          ((uint32_t)0x00000100U)
#define MCSPI_SYST_SPIDATDIR0_OUT                                                                            ((uint32_t)0U)
#define MCSPI_SYST_SPIDATDIR0_IN                                                                             ((uint32_t)1U)

#define MCSPI_SYST_SPIENDIR_SHIFT                                                                           ((uint32_t)10U)
#define MCSPI_SYST_SPIENDIR_MASK                                                                            ((uint32_t)0x00000400U)
#define MCSPI_SYST_SPIENDIR_OUT                                                                              ((uint32_t)0U)
#define MCSPI_SYST_SPIENDIR_IN                                                                               ((uint32_t)1U)

#define MCSPI_SYST_SPIEN_3_SHIFT                                                                            ((uint32_t)3U)
#define MCSPI_SYST_SPIEN_3_MASK                                                                             ((uint32_t)0x00000008U)

#define MCSPI_SYST_SPIEN_0_SHIFT                                                                            ((uint32_t)0U)
#define MCSPI_SYST_SPIEN_0_MASK                                                                             ((uint32_t)0x00000001U)

#define MCSPI_SYST_SPIDAT_1_SHIFT                                                                           ((uint32_t)5U)
#define MCSPI_SYST_SPIDAT_1_MASK                                                                            ((uint32_t)0x00000020U)

#define MCSPI_MODULCTRL_MS_SHIFT                                                                            ((uint32_t)2U)
#define MCSPI_MODULCTRL_MS_MASK                                                                             ((uint32_t)0x00000004U)
#define MCSPI_MODULCTRL_MS_MASTER                                                                            ((uint32_t)0U)
#define MCSPI_MODULCTRL_MS_SLAVE                                                                             ((uint32_t)1U)

#define MCSPI_MODULCTRL_RESERVED_11_SHIFT                                                                   ((uint32_t)9U)
#define MCSPI_MODULCTRL_RESERVED_11_MASK                                                                    ((uint32_t)0xfffffe00U)

#define MCSPI_MODULCTRL_SYSTEM_TEST_SHIFT                                                                   ((uint32_t)3U)
#define MCSPI_MODULCTRL_SYSTEM_TEST_MASK                                                                    ((uint32_t)0x00000008U)
#define MCSPI_MODULCTRL_SYSTEM_TEST_OFF                                                                      ((uint32_t)0U)
#define MCSPI_MODULCTRL_SYSTEM_TEST_ON                                                                       ((uint32_t)1U)

#define MCSPI_MODULCTRL_SINGLE_SHIFT                                                                        ((uint32_t)0U)
#define MCSPI_MODULCTRL_SINGLE_MASK                                                                         ((uint32_t)0x00000001U)
#define MCSPI_MODULCTRL_SINGLE_MULTI                                                                         ((uint32_t)0U)
#define MCSPI_MODULCTRL_SINGLE_SINGLE                                                                        ((uint32_t)1U)

#define MCSPI_MODULCTRL_PIN34_SHIFT                                                                         ((uint32_t)1U)
#define MCSPI_MODULCTRL_PIN34_MASK                                                                          ((uint32_t)0x00000002U)
#define MCSPI_MODULCTRL_PIN34_3PINMODE                                                                       ((uint32_t)1U)
#define MCSPI_MODULCTRL_PIN34_4PINMODE                                                                       ((uint32_t)0U)

#define MCSPI_MODULCTRL_INITDLY_SHIFT                                                                       ((uint32_t)4U)
#define MCSPI_MODULCTRL_INITDLY_MASK                                                                        ((uint32_t)0x00000070U)
#define MCSPI_MODULCTRL_INITDLY_4CLKDLY                                                                      ((uint32_t)1U)
#define MCSPI_MODULCTRL_INITDLY_NODELAY                                                                      ((uint32_t)0U)
#define MCSPI_MODULCTRL_INITDLY_8CLKDLY                                                                      ((uint32_t)2U)
#define MCSPI_MODULCTRL_INITDLY_16CLKDLY                                                                     ((uint32_t)3U)
#define MCSPI_MODULCTRL_INITDLY_32CLKDLY                                                                     ((uint32_t)4U)

#define MCSPI_MODULCTRL_MOA_SHIFT                                                                           ((uint32_t)7U)
#define MCSPI_MODULCTRL_MOA_MASK                                                                            ((uint32_t)0x00000080U)
#define MCSPI_MODULCTRL_MOA_MULTIACCES                                                                       ((uint32_t)1U)
#define MCSPI_MODULCTRL_MOA_NOMULTIACCESS                                                                    ((uint32_t)0U)

#define MCSPI_MODULCTRL_FDAA_SHIFT                                                                          ((uint32_t)8U)
#define MCSPI_MODULCTRL_FDAA_MASK                                                                           ((uint32_t)0x00000100U)
#define MCSPI_MODULCTRL_FDAA_SHADOWREGEN                                                                     ((uint32_t)1U)
#define MCSPI_MODULCTRL_FDAA_NOSHADOWREG                                                                     ((uint32_t)0U)

#define MCSPI_CH0CONF_CLKD_SHIFT                                                                            ((uint32_t)2U)
#define MCSPI_CH0CONF_CLKD_MASK                                                                             ((uint32_t)0x0000003cU)
#define MCSPI_CH0CONF_CLKD_DIVBY4K                                                                           ((uint32_t)12U)
#define MCSPI_CH0CONF_CLKD_DIVBY8                                                                            ((uint32_t)3U)
#define MCSPI_CH0CONF_CLKD_DIVBY8K                                                                           ((uint32_t)13U)
#define MCSPI_CH0CONF_CLKD_DIVBY2K                                                                           ((uint32_t)11U)
#define MCSPI_CH0CONF_CLKD_DIVBY1K                                                                           ((uint32_t)10U)
#define MCSPI_CH0CONF_CLKD_DIVBY512                                                                          ((uint32_t)9U)
#define MCSPI_CH0CONF_CLKD_DIVBY32K                                                                          ((uint32_t)15U)
#define MCSPI_CH0CONF_CLKD_DIVBY4                                                                            ((uint32_t)2U)
#define MCSPI_CH0CONF_CLKD_DIVBY1                                                                            ((uint32_t)0U)
#define MCSPI_CH0CONF_CLKD_DIVBY64                                                                           ((uint32_t)6U)
#define MCSPI_CH0CONF_CLKD_DIVBY256                                                                          ((uint32_t)8U)
#define MCSPI_CH0CONF_CLKD_DIVBY128                                                                          ((uint32_t)7U)
#define MCSPI_CH0CONF_CLKD_DIVBY32                                                                           ((uint32_t)5U)
#define MCSPI_CH0CONF_CLKD_DIVBY16K                                                                          ((uint32_t)14U)
#define MCSPI_CH0CONF_CLKD_DIVBY16                                                                           ((uint32_t)4U)
#define MCSPI_CH0CONF_CLKD_DIVBY2                                                                            ((uint32_t)1U)

#define MCSPI_CH0CONF_RESERVED_0_SHIFT                                                                      ((uint32_t)30U)
#define MCSPI_CH0CONF_RESERVED_0_MASK                                                                       ((uint32_t)0xc0000000U)

#define MCSPI_CH0CONF_PHA_SHIFT                                                                             ((uint32_t)0U)
#define MCSPI_CH0CONF_PHA_MASK                                                                              ((uint32_t)0x00000001U)
#define MCSPI_CH0CONF_PHA_ODD                                                                                ((uint32_t)0U)
#define MCSPI_CH0CONF_PHA_EVEN                                                                               ((uint32_t)1U)

#define MCSPI_CH0CONF_TURBO_SHIFT                                                                           ((uint32_t)19U)
#define MCSPI_CH0CONF_TURBO_MASK                                                                            ((uint32_t)0x00080000U)
#define MCSPI_CH0CONF_TURBO_TURBO                                                                            ((uint32_t)1U)
#define MCSPI_CH0CONF_TURBO_OFF                                                                              ((uint32_t)0U)

#define MCSPI_CH0CONF_SPIENSLV_SHIFT                                                                        ((uint32_t)21U)
#define MCSPI_CH0CONF_SPIENSLV_MASK                                                                         ((uint32_t)0x00600000U)
#define MCSPI_CH0CONF_SPIENSLV_SPIEN2                                                                        ((uint32_t)2U)
#define MCSPI_CH0CONF_SPIENSLV_SPIEN3                                                                        ((uint32_t)3U)
#define MCSPI_CH0CONF_SPIENSLV_SPIEN0                                                                        ((uint32_t)0U)
#define MCSPI_CH0CONF_SPIENSLV_SPIEN1                                                                        ((uint32_t)1U)

#define MCSPI_CH0CONF_DPE0_SHIFT                                                                            ((uint32_t)16U)
#define MCSPI_CH0CONF_DPE0_MASK                                                                             ((uint32_t)0x00010000U)
#define MCSPI_CH0CONF_DPE0_DISABLED                                                                          ((uint32_t)1U)
#define MCSPI_CH0CONF_DPE0_ENABLED                                                                           ((uint32_t)0U)

#define MCSPI_CH0CONF_IS_SHIFT                                                                              ((uint32_t)18U)
#define MCSPI_CH0CONF_IS_MASK                                                                               ((uint32_t)0x00040000U)
#define MCSPI_CH0CONF_IS_LINE0                                                                               ((uint32_t)0U)
#define MCSPI_CH0CONF_IS_LINE1                                                                               ((uint32_t)1U)

#define MCSPI_CH0CONF_DMAR_SHIFT                                                                            ((uint32_t)15U)
#define MCSPI_CH0CONF_DMAR_MASK                                                                             ((uint32_t)0x00008000U)
#define MCSPI_CH0CONF_DMAR_DISABLED                                                                          ((uint32_t)0U)
#define MCSPI_CH0CONF_DMAR_ENABLED                                                                           ((uint32_t)1U)

#define MCSPI_CH0CONF_FORCE_SHIFT                                                                           ((uint32_t)20U)
#define MCSPI_CH0CONF_FORCE_MASK                                                                            ((uint32_t)0x00100000U)
#define MCSPI_CH0CONF_FORCE_DEASSERT                                                                         ((uint32_t)0U)
#define MCSPI_CH0CONF_FORCE_ASSERT                                                                           ((uint32_t)1U)

#define MCSPI_CH0CONF_WL_SHIFT                                                                              ((uint32_t)7U)
#define MCSPI_CH0CONF_WL_MASK                                                                               ((uint32_t)0x00000f80U)
#define MCSPI_CH0CONF_WL_21BITS                                                                              ((uint32_t)20U)
#define MCSPI_CH0CONF_WL_26BITS                                                                              ((uint32_t)25U)
#define MCSPI_CH0CONF_WL_18BITS                                                                              ((uint32_t)17U)
#define MCSPI_CH0CONF_WL_20BITS                                                                              ((uint32_t)19U)
#define MCSPI_CH0CONF_WL_5BITS                                                                               ((uint32_t)4U)
#define MCSPI_CH0CONF_WL_6BITS                                                                               ((uint32_t)5U)
#define MCSPI_CH0CONF_WL_11BITS                                                                              ((uint32_t)10U)
#define MCSPI_CH0CONF_WL_8BITS                                                                               ((uint32_t)7U)
#define MCSPI_CH0CONF_WL_13BITS                                                                              ((uint32_t)12U)
#define MCSPI_CH0CONF_WL_29BITS                                                                              ((uint32_t)28U)
#define MCSPI_CH0CONF_WL_12BITS                                                                              ((uint32_t)11U)
#define MCSPI_CH0CONF_WL_32BITS                                                                              ((uint32_t)31U)
#define MCSPI_CH0CONF_WL_31BITS                                                                              ((uint32_t)30U)
#define MCSPI_CH0CONF_WL_30BITS                                                                              ((uint32_t)29U)
#define MCSPI_CH0CONF_WL_9BITS                                                                               ((uint32_t)8U)
#define MCSPI_CH0CONF_WL_7BITS                                                                               ((uint32_t)6U)
#define MCSPI_CH0CONF_WL_10BITS                                                                              ((uint32_t)9U)
#define MCSPI_CH0CONF_WL_16BITS                                                                              ((uint32_t)15U)
#define MCSPI_CH0CONF_WL_17BITS                                                                              ((uint32_t)16U)
#define MCSPI_CH0CONF_WL_14BITS                                                                              ((uint32_t)13U)
#define MCSPI_CH0CONF_WL_15BITS                                                                              ((uint32_t)14U)
#define MCSPI_CH0CONF_WL_RSVD1                                                                               ((uint32_t)1U)
#define MCSPI_CH0CONF_WL_RSVD0                                                                               ((uint32_t)0U)
#define MCSPI_CH0CONF_WL_27BITS                                                                              ((uint32_t)26U)
#define MCSPI_CH0CONF_WL_23BITS                                                                              ((uint32_t)22U)
#define MCSPI_CH0CONF_WL_RSVD2                                                                               ((uint32_t)2U)
#define MCSPI_CH0CONF_WL_19BITS                                                                              ((uint32_t)18U)
#define MCSPI_CH0CONF_WL_4BITS                                                                               ((uint32_t)3U)
#define MCSPI_CH0CONF_WL_25BITS                                                                              ((uint32_t)24U)
#define MCSPI_CH0CONF_WL_24BITS                                                                              ((uint32_t)23U)
#define MCSPI_CH0CONF_WL_22BITS                                                                              ((uint32_t)21U)
#define MCSPI_CH0CONF_WL_28BITS                                                                              ((uint32_t)27U)

#define MCSPI_CH0CONF_DPE1_SHIFT                                                                            ((uint32_t)17U)
#define MCSPI_CH0CONF_DPE1_MASK                                                                             ((uint32_t)0x00020000U)
#define MCSPI_CH0CONF_DPE1_ENABLED                                                                           ((uint32_t)0U)
#define MCSPI_CH0CONF_DPE1_DISABLED                                                                          ((uint32_t)1U)

#define MCSPI_CH0CONF_EPOL_SHIFT                                                                            ((uint32_t)6U)
#define MCSPI_CH0CONF_EPOL_MASK                                                                             ((uint32_t)0x00000040U)
#define MCSPI_CH0CONF_EPOL_ACTIVELOW                                                                         ((uint32_t)1U)
#define MCSPI_CH0CONF_EPOL_ACTIVEHIGH                                                                        ((uint32_t)0U)

#define MCSPI_CH0CONF_DMAW_SHIFT                                                                            ((uint32_t)14U)
#define MCSPI_CH0CONF_DMAW_MASK                                                                             ((uint32_t)0x00004000U)
#define MCSPI_CH0CONF_DMAW_ENABLED                                                                           ((uint32_t)1U)
#define MCSPI_CH0CONF_DMAW_DISABLED                                                                          ((uint32_t)0U)

#define MCSPI_CH0CONF_TRM_SHIFT                                                                             ((uint32_t)12U)
#define MCSPI_CH0CONF_TRM_MASK                                                                              ((uint32_t)0x00003000U)
#define MCSPI_CH0CONF_TRM_TRANSONLY                                                                          ((uint32_t)2U)
#define MCSPI_CH0CONF_TRM_RSVD                                                                               ((uint32_t)3U)
#define MCSPI_CH0CONF_TRM_TRANSRECEI                                                                         ((uint32_t)0U)
#define MCSPI_CH0CONF_TRM_RECEIVONLY                                                                         ((uint32_t)1U)

#define MCSPI_CH0CONF_POL_SHIFT                                                                             ((uint32_t)1U)
#define MCSPI_CH0CONF_POL_MASK                                                                              ((uint32_t)0x00000002U)
#define MCSPI_CH0CONF_POL_ACTIVELOW                                                                          ((uint32_t)1U)
#define MCSPI_CH0CONF_POL_ACTIVEHIGH                                                                         ((uint32_t)0U)

#define MCSPI_CH0CONF_SBE_SHIFT                                                                             ((uint32_t)23U)
#define MCSPI_CH0CONF_SBE_MASK                                                                              ((uint32_t)0x00800000U)
#define MCSPI_CH0CONF_SBE_DISABLED                                                                           ((uint32_t)0U)
#define MCSPI_CH0CONF_SBE_ENABLED                                                                            ((uint32_t)1U)

#define MCSPI_CH0CONF_SBPOL_SHIFT                                                                           ((uint32_t)24U)
#define MCSPI_CH0CONF_SBPOL_MASK                                                                            ((uint32_t)0x01000000U)
#define MCSPI_CH0CONF_SBPOL_LOWLEVEL                                                                         ((uint32_t)0U)
#define MCSPI_CH0CONF_SBPOL_HIGHLEVEL                                                                        ((uint32_t)1U)

#define MCSPI_CH0CONF_TCS0_SHIFT                                                                            ((uint32_t)25U)
#define MCSPI_CH0CONF_TCS0_MASK                                                                             ((uint32_t)0x06000000U)
#define MCSPI_CH0CONF_TCS0_THREECYCLEDLY                                                                     ((uint32_t)3U)
#define MCSPI_CH0CONF_TCS0_TWOCYCLEDLY                                                                       ((uint32_t)2U)
#define MCSPI_CH0CONF_TCS0_ONECYCLEDLY                                                                       ((uint32_t)1U)
#define MCSPI_CH0CONF_TCS0_ZEROCYCLEDLY                                                                      ((uint32_t)0U)

#define MCSPI_CH0CONF_FFER_SHIFT                                                                            ((uint32_t)28U)
#define MCSPI_CH0CONF_FFER_MASK                                                                             ((uint32_t)0x10000000U)
#define MCSPI_CH0CONF_FFER_FFENABLED                                                                         ((uint32_t)1U)
#define MCSPI_CH0CONF_FFER_FFDISABLED                                                                        ((uint32_t)0U)

#define MCSPI_CH0CONF_FFEW_SHIFT                                                                            ((uint32_t)27U)
#define MCSPI_CH0CONF_FFEW_MASK                                                                             ((uint32_t)0x08000000U)
#define MCSPI_CH0CONF_FFEW_FFENABLED                                                                         ((uint32_t)1U)
#define MCSPI_CH0CONF_FFEW_FFDISABLED                                                                        ((uint32_t)0U)

#define MCSPI_CH0CONF_CLKG_SHIFT                                                                            ((uint32_t)29U)
#define MCSPI_CH0CONF_CLKG_MASK                                                                             ((uint32_t)0x20000000U)
#define MCSPI_CH0CONF_CLKG_ONECYCLE                                                                          ((uint32_t)1U)
#define MCSPI_CH0CONF_CLKG_POWERTWO                                                                          ((uint32_t)0U)

#define MCSPI_CH0STAT_RXS_SHIFT                                                                             ((uint32_t)0U)
#define MCSPI_CH0STAT_RXS_MASK                                                                              ((uint32_t)0x00000001U)
#define MCSPI_CH0STAT_RXS_EMPTY                                                                              ((uint32_t)0U)
#define MCSPI_CH0STAT_RXS_FULL                                                                               ((uint32_t)1U)

#define MCSPI_CH0STAT_EOT_SHIFT                                                                             ((uint32_t)2U)
#define MCSPI_CH0STAT_EOT_MASK                                                                              ((uint32_t)0x00000004U)
#define MCSPI_CH0STAT_EOT_COMPLETED                                                                          ((uint32_t)1U)
#define MCSPI_CH0STAT_EOT_INPROGRESS                                                                         ((uint32_t)0U)

#define MCSPI_CH0STAT_RESERVED_2_SHIFT                                                                      ((uint32_t)7U)
#define MCSPI_CH0STAT_RESERVED_2_MASK                                                                       ((uint32_t)0xffffff80U)

#define MCSPI_CH0STAT_TXS_SHIFT                                                                             ((uint32_t)1U)
#define MCSPI_CH0STAT_TXS_MASK                                                                              ((uint32_t)0x00000002U)
#define MCSPI_CH0STAT_TXS_EMPTY                                                                              ((uint32_t)1U)
#define MCSPI_CH0STAT_TXS_FULL                                                                               ((uint32_t)0U)

#define MCSPI_CH0STAT_RXFFF_SHIFT                                                                           ((uint32_t)6U)
#define MCSPI_CH0STAT_RXFFF_MASK                                                                            ((uint32_t)0x00000040U)
#define MCSPI_CH0STAT_RXFFF_FULL                                                                             ((uint32_t)1U)
#define MCSPI_CH0STAT_RXFFF_NOTFULL                                                                          ((uint32_t)0U)

#define MCSPI_CH0STAT_TXFFF_SHIFT                                                                           ((uint32_t)4U)
#define MCSPI_CH0STAT_TXFFF_MASK                                                                            ((uint32_t)0x00000010U)
#define MCSPI_CH0STAT_TXFFF_FULL                                                                             ((uint32_t)1U)
#define MCSPI_CH0STAT_TXFFF_NOTFULL                                                                          ((uint32_t)0U)

#define MCSPI_CH0STAT_RXFFE_SHIFT                                                                           ((uint32_t)5U)
#define MCSPI_CH0STAT_RXFFE_MASK                                                                            ((uint32_t)0x00000020U)
#define MCSPI_CH0STAT_RXFFE_EMPTY                                                                            ((uint32_t)1U)
#define MCSPI_CH0STAT_RXFFE_NOTEMPTY                                                                         ((uint32_t)0U)

#define MCSPI_CH0STAT_TXFFE_SHIFT                                                                           ((uint32_t)3U)
#define MCSPI_CH0STAT_TXFFE_MASK                                                                            ((uint32_t)0x00000008U)
#define MCSPI_CH0STAT_TXFFE_EMPTY                                                                            ((uint32_t)1U)
#define MCSPI_CH0STAT_TXFFE_NOTEMPTY                                                                         ((uint32_t)0U)

#define MCSPI_CH0CTRL_RESERVED_1_SHIFT                                                                      ((uint32_t)1U)
#define MCSPI_CH0CTRL_RESERVED_1_MASK                                                                       ((uint32_t)0x000000feU)

#define MCSPI_CH0CTRL_EN_SHIFT                                                                              ((uint32_t)0U)
#define MCSPI_CH0CTRL_EN_MASK                                                                               ((uint32_t)0x00000001U)
#define MCSPI_CH0CTRL_EN_ACT                                                                                 ((uint32_t)1U)
#define MCSPI_CH0CTRL_EN_NACT                                                                                ((uint32_t)0U)

#define MCSPI_CH0CTRL_EXTCLK_SHIFT                                                                          ((uint32_t)8U)
#define MCSPI_CH0CTRL_EXTCLK_MASK                                                                           ((uint32_t)0x0000ff00U)
#define MCSPI_CH0CTRL_EXTCLK_EXTZERO                                                                         ((uint32_t)0U)
#define MCSPI_CH0CTRL_EXTCLK_EXTONE                                                                          ((uint32_t)1U)
#define MCSPI_CH0CTRL_EXTCLK_EXT4080                                                                         ((uint32_t)255U)

#define MCSPI_CH0CTRL_RESERVED_2_SHIFT                                                                      ((uint32_t)16U)
#define MCSPI_CH0CTRL_RESERVED_2_MASK                                                                       ((uint32_t)0xffff0000U)

#define MCSPI_TX0_TDATA_SHIFT                                                                               ((uint32_t)0U)
#define MCSPI_TX0_TDATA_MASK                                                                                ((uint32_t)0xffffffffU)

#define MCSPI_RX0_RDATA_SHIFT                                                                               ((uint32_t)0U)
#define MCSPI_RX0_RDATA_MASK                                                                                ((uint32_t)0xffffffffU)

#define MCSPI_CH1CONF_CLKD_SHIFT                                                                            ((uint32_t)2U)
#define MCSPI_CH1CONF_CLKD_MASK                                                                             ((uint32_t)0x0000003cU)
#define MCSPI_CH1CONF_CLKD_DIVBY4K                                                                           ((uint32_t)12U)
#define MCSPI_CH1CONF_CLKD_DIVBY8                                                                            ((uint32_t)3U)
#define MCSPI_CH1CONF_CLKD_DIVBY8K                                                                           ((uint32_t)13U)
#define MCSPI_CH1CONF_CLKD_DIVBY2K                                                                           ((uint32_t)11U)
#define MCSPI_CH1CONF_CLKD_DIVBY1K                                                                           ((uint32_t)10U)
#define MCSPI_CH1CONF_CLKD_DIVBY512                                                                          ((uint32_t)9U)
#define MCSPI_CH1CONF_CLKD_DIVBY32K                                                                          ((uint32_t)15U)
#define MCSPI_CH1CONF_CLKD_DIVBY4                                                                            ((uint32_t)2U)
#define MCSPI_CH1CONF_CLKD_DIVBY1                                                                            ((uint32_t)0U)
#define MCSPI_CH1CONF_CLKD_DIVBY64                                                                           ((uint32_t)6U)
#define MCSPI_CH1CONF_CLKD_DIVBY256                                                                          ((uint32_t)8U)
#define MCSPI_CH1CONF_CLKD_DIVBY128                                                                          ((uint32_t)7U)
#define MCSPI_CH1CONF_CLKD_DIVBY32                                                                           ((uint32_t)5U)
#define MCSPI_CH1CONF_CLKD_DIVBY16K                                                                          ((uint32_t)14U)
#define MCSPI_CH1CONF_CLKD_DIVBY16                                                                           ((uint32_t)4U)
#define MCSPI_CH1CONF_CLKD_DIVBY2                                                                            ((uint32_t)1U)

#define MCSPI_CH1CONF_RESERVED_0_SHIFT                                                                      ((uint32_t)30U)
#define MCSPI_CH1CONF_RESERVED_0_MASK                                                                       ((uint32_t)0xc0000000U)

#define MCSPI_CH1CONF_PHA_SHIFT                                                                             ((uint32_t)0U)
#define MCSPI_CH1CONF_PHA_MASK                                                                              ((uint32_t)0x00000001U)
#define MCSPI_CH1CONF_PHA_ODD                                                                                ((uint32_t)0U)
#define MCSPI_CH1CONF_PHA_EVEN                                                                               ((uint32_t)1U)

#define MCSPI_CH1CONF_TURBO_SHIFT                                                                           ((uint32_t)19U)
#define MCSPI_CH1CONF_TURBO_MASK                                                                            ((uint32_t)0x00080000U)
#define MCSPI_CH1CONF_TURBO_TURBO                                                                            ((uint32_t)1U)
#define MCSPI_CH1CONF_TURBO_OFF                                                                              ((uint32_t)0U)

#define MCSPI_CH1CONF_RESERVED_1_SHIFT                                                                      ((uint32_t)21U)
#define MCSPI_CH1CONF_RESERVED_1_MASK                                                                       ((uint32_t)0x00600000U)

#define MCSPI_CH1CONF_DPE0_SHIFT                                                                            ((uint32_t)16U)
#define MCSPI_CH1CONF_DPE0_MASK                                                                             ((uint32_t)0x00010000U)
#define MCSPI_CH1CONF_DPE0_DISABLED                                                                          ((uint32_t)1U)
#define MCSPI_CH1CONF_DPE0_ENABLED                                                                           ((uint32_t)0U)

#define MCSPI_CH1CONF_IS_SHIFT                                                                              ((uint32_t)18U)
#define MCSPI_CH1CONF_IS_MASK                                                                               ((uint32_t)0x00040000U)
#define MCSPI_CH1CONF_IS_LINE0                                                                               ((uint32_t)0U)
#define MCSPI_CH1CONF_IS_LINE1                                                                               ((uint32_t)1U)

#define MCSPI_CH1CONF_DMAR_SHIFT                                                                            ((uint32_t)15U)
#define MCSPI_CH1CONF_DMAR_MASK                                                                             ((uint32_t)0x00008000U)
#define MCSPI_CH1CONF_DMAR_DISABLED                                                                          ((uint32_t)0U)
#define MCSPI_CH1CONF_DMAR_ENABLED                                                                           ((uint32_t)1U)

#define MCSPI_CH1CONF_FORCE_SHIFT                                                                           ((uint32_t)20U)
#define MCSPI_CH1CONF_FORCE_MASK                                                                            ((uint32_t)0x00100000U)
#define MCSPI_CH1CONF_FORCE_DEASSERT                                                                         ((uint32_t)0U)
#define MCSPI_CH1CONF_FORCE_ASSERT                                                                           ((uint32_t)1U)

#define MCSPI_CH1CONF_WL_SHIFT                                                                              ((uint32_t)7U)
#define MCSPI_CH1CONF_WL_MASK                                                                               ((uint32_t)0x00000f80U)
#define MCSPI_CH1CONF_WL_21BITS                                                                              ((uint32_t)20U)
#define MCSPI_CH1CONF_WL_26BITS                                                                              ((uint32_t)25U)
#define MCSPI_CH1CONF_WL_18BITS                                                                              ((uint32_t)17U)
#define MCSPI_CH1CONF_WL_20BITS                                                                              ((uint32_t)19U)
#define MCSPI_CH1CONF_WL_5BITS                                                                               ((uint32_t)4U)
#define MCSPI_CH1CONF_WL_6BITS                                                                               ((uint32_t)5U)
#define MCSPI_CH1CONF_WL_11BITS                                                                              ((uint32_t)10U)
#define MCSPI_CH1CONF_WL_8BITS                                                                               ((uint32_t)7U)
#define MCSPI_CH1CONF_WL_13BITS                                                                              ((uint32_t)12U)
#define MCSPI_CH1CONF_WL_29BITS                                                                              ((uint32_t)28U)
#define MCSPI_CH1CONF_WL_12BITS                                                                              ((uint32_t)11U)
#define MCSPI_CH1CONF_WL_32BITS                                                                              ((uint32_t)31U)
#define MCSPI_CH1CONF_WL_31BITS                                                                              ((uint32_t)30U)
#define MCSPI_CH1CONF_WL_30BITS                                                                              ((uint32_t)29U)
#define MCSPI_CH1CONF_WL_9BITS                                                                               ((uint32_t)8U)
#define MCSPI_CH1CONF_WL_7BITS                                                                               ((uint32_t)6U)
#define MCSPI_CH1CONF_WL_10BITS                                                                              ((uint32_t)9U)
#define MCSPI_CH1CONF_WL_16BITS                                                                              ((uint32_t)15U)
#define MCSPI_CH1CONF_WL_17BITS                                                                              ((uint32_t)16U)
#define MCSPI_CH1CONF_WL_14BITS                                                                              ((uint32_t)13U)
#define MCSPI_CH1CONF_WL_15BITS                                                                              ((uint32_t)14U)
#define MCSPI_CH1CONF_WL_RSVD1                                                                               ((uint32_t)1U)
#define MCSPI_CH1CONF_WL_RSVD0                                                                               ((uint32_t)0U)
#define MCSPI_CH1CONF_WL_27BITS                                                                              ((uint32_t)26U)
#define MCSPI_CH1CONF_WL_23BITS                                                                              ((uint32_t)22U)
#define MCSPI_CH1CONF_WL_RSVD2                                                                               ((uint32_t)2U)
#define MCSPI_CH1CONF_WL_19BITS                                                                              ((uint32_t)18U)
#define MCSPI_CH1CONF_WL_4BITS                                                                               ((uint32_t)3U)
#define MCSPI_CH1CONF_WL_25BITS                                                                              ((uint32_t)24U)
#define MCSPI_CH1CONF_WL_24BITS                                                                              ((uint32_t)23U)
#define MCSPI_CH1CONF_WL_22BITS                                                                              ((uint32_t)21U)
#define MCSPI_CH1CONF_WL_28BITS                                                                              ((uint32_t)27U)

#define MCSPI_CH1CONF_DPE1_SHIFT                                                                            ((uint32_t)17U)
#define MCSPI_CH1CONF_DPE1_MASK                                                                             ((uint32_t)0x00020000U)
#define MCSPI_CH1CONF_DPE1_ENABLED                                                                           ((uint32_t)0U)
#define MCSPI_CH1CONF_DPE1_DISABLED                                                                          ((uint32_t)1U)

#define MCSPI_CH1CONF_EPOL_SHIFT                                                                            ((uint32_t)6U)
#define MCSPI_CH1CONF_EPOL_MASK                                                                             ((uint32_t)0x00000040U)
#define MCSPI_CH1CONF_EPOL_ACTIVELOW                                                                         ((uint32_t)1U)
#define MCSPI_CH1CONF_EPOL_ACTIVEHIGH                                                                        ((uint32_t)0U)

#define MCSPI_CH1CONF_DMAW_SHIFT                                                                            ((uint32_t)14U)
#define MCSPI_CH1CONF_DMAW_MASK                                                                             ((uint32_t)0x00004000U)
#define MCSPI_CH1CONF_DMAW_ENABLED                                                                           ((uint32_t)1U)
#define MCSPI_CH1CONF_DMAW_DISABLED                                                                          ((uint32_t)0U)

#define MCSPI_CH1CONF_TRM_SHIFT                                                                             ((uint32_t)12U)
#define MCSPI_CH1CONF_TRM_MASK                                                                              ((uint32_t)0x00003000U)
#define MCSPI_CH1CONF_TRM_TRANSONLY                                                                          ((uint32_t)2U)
#define MCSPI_CH1CONF_TRM_RSVD                                                                               ((uint32_t)3U)
#define MCSPI_CH1CONF_TRM_TRANSRECEI                                                                         ((uint32_t)0U)
#define MCSPI_CH1CONF_TRM_RECEIVONLY                                                                         ((uint32_t)1U)

#define MCSPI_CH1CONF_POL_SHIFT                                                                             ((uint32_t)1U)
#define MCSPI_CH1CONF_POL_MASK                                                                              ((uint32_t)0x00000002U)
#define MCSPI_CH1CONF_POL_ACTIVELOW                                                                          ((uint32_t)1U)
#define MCSPI_CH1CONF_POL_ACTIVEHIGH                                                                         ((uint32_t)0U)

#define MCSPI_CH1CONF_SBE_SHIFT                                                                             ((uint32_t)23U)
#define MCSPI_CH1CONF_SBE_MASK                                                                              ((uint32_t)0x00800000U)
#define MCSPI_CH1CONF_SBE_DISABLED                                                                           ((uint32_t)0U)
#define MCSPI_CH1CONF_SBE_ENABLED                                                                            ((uint32_t)1U)

#define MCSPI_CH1CONF_SBPOL_SHIFT                                                                           ((uint32_t)24U)
#define MCSPI_CH1CONF_SBPOL_MASK                                                                            ((uint32_t)0x01000000U)
#define MCSPI_CH1CONF_SBPOL_LOWLEVEL                                                                         ((uint32_t)0U)
#define MCSPI_CH1CONF_SBPOL_HIGHLEVEL                                                                        ((uint32_t)1U)

#define MCSPI_CH1CONF_TCS1_SHIFT                                                                            ((uint32_t)25U)
#define MCSPI_CH1CONF_TCS1_MASK                                                                             ((uint32_t)0x06000000U)
#define MCSPI_CH1CONF_TCS1_THREECYCLEDLY                                                                     ((uint32_t)3U)
#define MCSPI_CH1CONF_TCS1_TWOCYCLEDLY                                                                       ((uint32_t)2U)
#define MCSPI_CH1CONF_TCS1_ONECYCLEDLY                                                                       ((uint32_t)1U)
#define MCSPI_CH1CONF_TCS1_ZEROCYCLEDLY                                                                      ((uint32_t)0U)

#define MCSPI_CH1CONF_FFER_SHIFT                                                                            ((uint32_t)28U)
#define MCSPI_CH1CONF_FFER_MASK                                                                             ((uint32_t)0x10000000U)
#define MCSPI_CH1CONF_FFER_FFENABLED                                                                         ((uint32_t)1U)
#define MCSPI_CH1CONF_FFER_FFDISABLED                                                                        ((uint32_t)0U)

#define MCSPI_CH1CONF_FFEW_SHIFT                                                                            ((uint32_t)27U)
#define MCSPI_CH1CONF_FFEW_MASK                                                                             ((uint32_t)0x08000000U)
#define MCSPI_CH1CONF_FFEW_FFENABLED                                                                         ((uint32_t)1U)
#define MCSPI_CH1CONF_FFEW_FFDISABLED                                                                        ((uint32_t)0U)

#define MCSPI_CH1CONF_CLKG_SHIFT                                                                            ((uint32_t)29U)
#define MCSPI_CH1CONF_CLKG_MASK                                                                             ((uint32_t)0x20000000U)
#define MCSPI_CH1CONF_CLKG_ONECYCLE                                                                          ((uint32_t)1U)
#define MCSPI_CH1CONF_CLKG_POWERTWO                                                                          ((uint32_t)0U)

#define MCSPI_CH1STAT_RXS_SHIFT                                                                             ((uint32_t)0U)
#define MCSPI_CH1STAT_RXS_MASK                                                                              ((uint32_t)0x00000001U)
#define MCSPI_CH1STAT_RXS_EMPTY                                                                              ((uint32_t)0U)
#define MCSPI_CH1STAT_RXS_FULL                                                                               ((uint32_t)1U)

#define MCSPI_CH1STAT_EOT_SHIFT                                                                             ((uint32_t)2U)
#define MCSPI_CH1STAT_EOT_MASK                                                                              ((uint32_t)0x00000004U)
#define MCSPI_CH1STAT_EOT_COMPLETED                                                                          ((uint32_t)1U)
#define MCSPI_CH1STAT_EOT_INPROGRESS                                                                         ((uint32_t)0U)

#define MCSPI_CH1STAT_RESERVED_2_SHIFT                                                                      ((uint32_t)7U)
#define MCSPI_CH1STAT_RESERVED_2_MASK                                                                       ((uint32_t)0xffffff80U)

#define MCSPI_CH1STAT_TXS_SHIFT                                                                             ((uint32_t)1U)
#define MCSPI_CH1STAT_TXS_MASK                                                                              ((uint32_t)0x00000002U)
#define MCSPI_CH1STAT_TXS_EMPTY                                                                              ((uint32_t)1U)
#define MCSPI_CH1STAT_TXS_FULL                                                                               ((uint32_t)0U)

#define MCSPI_CH1STAT_RXFFE_SHIFT                                                                           ((uint32_t)5U)
#define MCSPI_CH1STAT_RXFFE_MASK                                                                            ((uint32_t)0x00000020U)
#define MCSPI_CH1STAT_RXFFE_EMPTY                                                                            ((uint32_t)1U)
#define MCSPI_CH1STAT_RXFFE_NOTEMPTY                                                                         ((uint32_t)0U)

#define MCSPI_CH1STAT_RXFFF_SHIFT                                                                           ((uint32_t)6U)
#define MCSPI_CH1STAT_RXFFF_MASK                                                                            ((uint32_t)0x00000040U)
#define MCSPI_CH1STAT_RXFFF_FULL                                                                             ((uint32_t)1U)
#define MCSPI_CH1STAT_RXFFF_NOTFULL                                                                          ((uint32_t)0U)

#define MCSPI_CH1STAT_TXFFE_SHIFT                                                                           ((uint32_t)3U)
#define MCSPI_CH1STAT_TXFFE_MASK                                                                            ((uint32_t)0x00000008U)
#define MCSPI_CH1STAT_TXFFE_EMPTY                                                                            ((uint32_t)1U)
#define MCSPI_CH1STAT_TXFFE_NOTEMPTY                                                                         ((uint32_t)0U)

#define MCSPI_CH1STAT_TXFFF_SHIFT                                                                           ((uint32_t)4U)
#define MCSPI_CH1STAT_TXFFF_MASK                                                                            ((uint32_t)0x00000010U)
#define MCSPI_CH1STAT_TXFFF_FULL                                                                             ((uint32_t)1U)
#define MCSPI_CH1STAT_TXFFF_NOTFULL                                                                          ((uint32_t)0U)

#define MCSPI_CH1CTRL_RESERVED_1_SHIFT                                                                      ((uint32_t)1U)
#define MCSPI_CH1CTRL_RESERVED_1_MASK                                                                       ((uint32_t)0x000000feU)

#define MCSPI_CH1CTRL_EN_SHIFT                                                                              ((uint32_t)0U)
#define MCSPI_CH1CTRL_EN_MASK                                                                               ((uint32_t)0x00000001U)
#define MCSPI_CH1CTRL_EN_ACT                                                                                 ((uint32_t)1U)
#define MCSPI_CH1CTRL_EN_NACT                                                                                ((uint32_t)0U)

#define MCSPI_CH1CTRL_EXTCLK_SHIFT                                                                          ((uint32_t)8U)
#define MCSPI_CH1CTRL_EXTCLK_MASK                                                                           ((uint32_t)0x0000ff00U)
#define MCSPI_CH1CTRL_EXTCLK_EXTZERO                                                                         ((uint32_t)0U)
#define MCSPI_CH1CTRL_EXTCLK_EXTONE                                                                          ((uint32_t)1U)
#define MCSPI_CH1CTRL_EXTCLK_EXT4080                                                                         ((uint32_t)255U)

#define MCSPI_CH1CTRL_RESERVED_2_SHIFT                                                                      ((uint32_t)16U)
#define MCSPI_CH1CTRL_RESERVED_2_MASK                                                                       ((uint32_t)0xffff0000U)

#define MCSPI_TX1_TDATA_SHIFT                                                                               ((uint32_t)0U)
#define MCSPI_TX1_TDATA_MASK                                                                                ((uint32_t)0xffffffffU)

#define MCSPI_RX1_RDATA_SHIFT                                                                               ((uint32_t)0U)
#define MCSPI_RX1_RDATA_MASK                                                                                ((uint32_t)0xffffffffU)

#define MCSPI_CH2CONF_CLKD_SHIFT                                                                            ((uint32_t)2U)
#define MCSPI_CH2CONF_CLKD_MASK                                                                             ((uint32_t)0x0000003cU)
#define MCSPI_CH2CONF_CLKD_DIVBY4K                                                                           ((uint32_t)12U)
#define MCSPI_CH2CONF_CLKD_DIVBY8                                                                            ((uint32_t)3U)
#define MCSPI_CH2CONF_CLKD_DIVBY8K                                                                           ((uint32_t)13U)
#define MCSPI_CH2CONF_CLKD_DIVBY2K                                                                           ((uint32_t)11U)
#define MCSPI_CH2CONF_CLKD_DIVBY1K                                                                           ((uint32_t)10U)
#define MCSPI_CH2CONF_CLKD_DIVBY512                                                                          ((uint32_t)9U)
#define MCSPI_CH2CONF_CLKD_DIVBY32K                                                                          ((uint32_t)15U)
#define MCSPI_CH2CONF_CLKD_DIVBY4                                                                            ((uint32_t)2U)
#define MCSPI_CH2CONF_CLKD_DIVBY1                                                                            ((uint32_t)0U)
#define MCSPI_CH2CONF_CLKD_DIVBY64                                                                           ((uint32_t)6U)
#define MCSPI_CH2CONF_CLKD_DIVBY256                                                                          ((uint32_t)8U)
#define MCSPI_CH2CONF_CLKD_DIVBY128                                                                          ((uint32_t)7U)
#define MCSPI_CH2CONF_CLKD_DIVBY32                                                                           ((uint32_t)5U)
#define MCSPI_CH2CONF_CLKD_DIVBY16K                                                                          ((uint32_t)14U)
#define MCSPI_CH2CONF_CLKD_DIVBY16                                                                           ((uint32_t)4U)
#define MCSPI_CH2CONF_CLKD_DIVBY2                                                                            ((uint32_t)1U)

#define MCSPI_CH2CONF_RESERVED_0_SHIFT                                                                      ((uint32_t)30U)
#define MCSPI_CH2CONF_RESERVED_0_MASK                                                                       ((uint32_t)0xc0000000U)

#define MCSPI_CH2CONF_PHA_SHIFT                                                                             ((uint32_t)0U)
#define MCSPI_CH2CONF_PHA_MASK                                                                              ((uint32_t)0x00000001U)
#define MCSPI_CH2CONF_PHA_ODD                                                                                ((uint32_t)0U)
#define MCSPI_CH2CONF_PHA_EVEN                                                                               ((uint32_t)1U)

#define MCSPI_CH2CONF_TURBO_SHIFT                                                                           ((uint32_t)19U)
#define MCSPI_CH2CONF_TURBO_MASK                                                                            ((uint32_t)0x00080000U)
#define MCSPI_CH2CONF_TURBO_TURBO                                                                            ((uint32_t)1U)
#define MCSPI_CH2CONF_TURBO_OFF                                                                              ((uint32_t)0U)

#define MCSPI_CH2CONF_RESERVED_1_SHIFT                                                                      ((uint32_t)21U)
#define MCSPI_CH2CONF_RESERVED_1_MASK                                                                       ((uint32_t)0x00600000U)

#define MCSPI_CH2CONF_DPE0_SHIFT                                                                            ((uint32_t)16U)
#define MCSPI_CH2CONF_DPE0_MASK                                                                             ((uint32_t)0x00010000U)
#define MCSPI_CH2CONF_DPE0_DISABLED                                                                          ((uint32_t)1U)
#define MCSPI_CH2CONF_DPE0_ENABLED                                                                           ((uint32_t)0U)

#define MCSPI_CH2CONF_IS_SHIFT                                                                              ((uint32_t)18U)
#define MCSPI_CH2CONF_IS_MASK                                                                               ((uint32_t)0x00040000U)
#define MCSPI_CH2CONF_IS_LINE0                                                                               ((uint32_t)0U)
#define MCSPI_CH2CONF_IS_LINE1                                                                               ((uint32_t)1U)

#define MCSPI_CH2CONF_DMAR_SHIFT                                                                            ((uint32_t)15U)
#define MCSPI_CH2CONF_DMAR_MASK                                                                             ((uint32_t)0x00008000U)
#define MCSPI_CH2CONF_DMAR_DISABLED                                                                          ((uint32_t)0U)
#define MCSPI_CH2CONF_DMAR_ENABLED                                                                           ((uint32_t)1U)

#define MCSPI_CH2CONF_FORCE_SHIFT                                                                           ((uint32_t)20U)
#define MCSPI_CH2CONF_FORCE_MASK                                                                            ((uint32_t)0x00100000U)
#define MCSPI_CH2CONF_FORCE_DEASSERT                                                                         ((uint32_t)0U)
#define MCSPI_CH2CONF_FORCE_ASSERT                                                                           ((uint32_t)1U)

#define MCSPI_CH2CONF_WL_SHIFT                                                                              ((uint32_t)7U)
#define MCSPI_CH2CONF_WL_MASK                                                                               ((uint32_t)0x00000f80U)
#define MCSPI_CH2CONF_WL_21BITS                                                                              ((uint32_t)20U)
#define MCSPI_CH2CONF_WL_26BITS                                                                              ((uint32_t)25U)
#define MCSPI_CH2CONF_WL_18BITS                                                                              ((uint32_t)17U)
#define MCSPI_CH2CONF_WL_20BITS                                                                              ((uint32_t)19U)
#define MCSPI_CH2CONF_WL_5BITS                                                                               ((uint32_t)4U)
#define MCSPI_CH2CONF_WL_6BITS                                                                               ((uint32_t)5U)
#define MCSPI_CH2CONF_WL_11BITS                                                                              ((uint32_t)10U)
#define MCSPI_CH2CONF_WL_8BITS                                                                               ((uint32_t)7U)
#define MCSPI_CH2CONF_WL_13BITS                                                                              ((uint32_t)12U)
#define MCSPI_CH2CONF_WL_29BITS                                                                              ((uint32_t)28U)
#define MCSPI_CH2CONF_WL_12BITS                                                                              ((uint32_t)11U)
#define MCSPI_CH2CONF_WL_32BITS                                                                              ((uint32_t)31U)
#define MCSPI_CH2CONF_WL_31BITS                                                                              ((uint32_t)30U)
#define MCSPI_CH2CONF_WL_30BITS                                                                              ((uint32_t)29U)
#define MCSPI_CH2CONF_WL_9BITS                                                                               ((uint32_t)8U)
#define MCSPI_CH2CONF_WL_7BITS                                                                               ((uint32_t)6U)
#define MCSPI_CH2CONF_WL_10BITS                                                                              ((uint32_t)9U)
#define MCSPI_CH2CONF_WL_16BITS                                                                              ((uint32_t)15U)
#define MCSPI_CH2CONF_WL_17BITS                                                                              ((uint32_t)16U)
#define MCSPI_CH2CONF_WL_14BITS                                                                              ((uint32_t)13U)
#define MCSPI_CH2CONF_WL_15BITS                                                                              ((uint32_t)14U)
#define MCSPI_CH2CONF_WL_RSVD1                                                                               ((uint32_t)1U)
#define MCSPI_CH2CONF_WL_RSVD0                                                                               ((uint32_t)0U)
#define MCSPI_CH2CONF_WL_27BITS                                                                              ((uint32_t)26U)
#define MCSPI_CH2CONF_WL_23BITS                                                                              ((uint32_t)22U)
#define MCSPI_CH2CONF_WL_RSVD2                                                                               ((uint32_t)2U)
#define MCSPI_CH2CONF_WL_19BITS                                                                              ((uint32_t)18U)
#define MCSPI_CH2CONF_WL_4BITS                                                                               ((uint32_t)3U)
#define MCSPI_CH2CONF_WL_25BITS                                                                              ((uint32_t)24U)
#define MCSPI_CH2CONF_WL_24BITS                                                                              ((uint32_t)23U)
#define MCSPI_CH2CONF_WL_22BITS                                                                              ((uint32_t)21U)
#define MCSPI_CH2CONF_WL_28BITS                                                                              ((uint32_t)27U)

#define MCSPI_CH2CONF_DPE1_SHIFT                                                                            ((uint32_t)17U)
#define MCSPI_CH2CONF_DPE1_MASK                                                                             ((uint32_t)0x00020000U)
#define MCSPI_CH2CONF_DPE1_ENABLED                                                                           ((uint32_t)0U)
#define MCSPI_CH2CONF_DPE1_DISABLED                                                                          ((uint32_t)1U)

#define MCSPI_CH2CONF_EPOL_SHIFT                                                                            ((uint32_t)6U)
#define MCSPI_CH2CONF_EPOL_MASK                                                                             ((uint32_t)0x00000040U)
#define MCSPI_CH2CONF_EPOL_ACTIVELOW                                                                         ((uint32_t)1U)
#define MCSPI_CH2CONF_EPOL_ACTIVEHIGH                                                                        ((uint32_t)0U)

#define MCSPI_CH2CONF_DMAW_SHIFT                                                                            ((uint32_t)14U)
#define MCSPI_CH2CONF_DMAW_MASK                                                                             ((uint32_t)0x00004000U)
#define MCSPI_CH2CONF_DMAW_ENABLED                                                                           ((uint32_t)1U)
#define MCSPI_CH2CONF_DMAW_DISABLED                                                                          ((uint32_t)0U)

#define MCSPI_CH2CONF_TRM_SHIFT                                                                             ((uint32_t)12U)
#define MCSPI_CH2CONF_TRM_MASK                                                                              ((uint32_t)0x00003000U)
#define MCSPI_CH2CONF_TRM_TRANSONLY                                                                          ((uint32_t)2U)
#define MCSPI_CH2CONF_TRM_RSVD                                                                               ((uint32_t)3U)
#define MCSPI_CH2CONF_TRM_TRANSRECEI                                                                         ((uint32_t)0U)
#define MCSPI_CH2CONF_TRM_RECEIVONLY                                                                         ((uint32_t)1U)

#define MCSPI_CH2CONF_POL_SHIFT                                                                             ((uint32_t)1U)
#define MCSPI_CH2CONF_POL_MASK                                                                              ((uint32_t)0x00000002U)
#define MCSPI_CH2CONF_POL_ACTIVELOW                                                                          ((uint32_t)1U)
#define MCSPI_CH2CONF_POL_ACTIVEHIGH                                                                         ((uint32_t)0U)

#define MCSPI_CH2CONF_SBE_SHIFT                                                                             ((uint32_t)23U)
#define MCSPI_CH2CONF_SBE_MASK                                                                              ((uint32_t)0x00800000U)
#define MCSPI_CH2CONF_SBE_DISABLED                                                                           ((uint32_t)0U)
#define MCSPI_CH2CONF_SBE_ENABLED                                                                            ((uint32_t)1U)

#define MCSPI_CH2CONF_SBPOL_SHIFT                                                                           ((uint32_t)24U)
#define MCSPI_CH2CONF_SBPOL_MASK                                                                            ((uint32_t)0x01000000U)
#define MCSPI_CH2CONF_SBPOL_LOWLEVEL                                                                         ((uint32_t)0U)
#define MCSPI_CH2CONF_SBPOL_HIGHLEVEL                                                                        ((uint32_t)1U)

#define MCSPI_CH2CONF_TCS2_SHIFT                                                                            ((uint32_t)25U)
#define MCSPI_CH2CONF_TCS2_MASK                                                                             ((uint32_t)0x06000000U)
#define MCSPI_CH2CONF_TCS2_THREECYCLEDLY                                                                     ((uint32_t)3U)
#define MCSPI_CH2CONF_TCS2_TWOCYCLEDLY                                                                       ((uint32_t)2U)
#define MCSPI_CH2CONF_TCS2_ONECYCLEDLY                                                                       ((uint32_t)1U)
#define MCSPI_CH2CONF_TCS2_ZEROCYCLEDLY                                                                      ((uint32_t)0U)

#define MCSPI_CH2CONF_FFER_SHIFT                                                                            ((uint32_t)28U)
#define MCSPI_CH2CONF_FFER_MASK                                                                             ((uint32_t)0x10000000U)
#define MCSPI_CH2CONF_FFER_FFENABLED                                                                         ((uint32_t)1U)
#define MCSPI_CH2CONF_FFER_FFDISABLED                                                                        ((uint32_t)0U)

#define MCSPI_CH2CONF_FFEW_SHIFT                                                                            ((uint32_t)27U)
#define MCSPI_CH2CONF_FFEW_MASK                                                                             ((uint32_t)0x08000000U)
#define MCSPI_CH2CONF_FFEW_FFENABLED                                                                         ((uint32_t)1U)
#define MCSPI_CH2CONF_FFEW_FFDISABLED                                                                        ((uint32_t)0U)

#define MCSPI_CH2CONF_CLKG_SHIFT                                                                            ((uint32_t)29U)
#define MCSPI_CH2CONF_CLKG_MASK                                                                             ((uint32_t)0x20000000U)
#define MCSPI_CH2CONF_CLKG_ONECYCLE                                                                          ((uint32_t)1U)
#define MCSPI_CH2CONF_CLKG_POWERTWO                                                                          ((uint32_t)0U)

#define MCSPI_CH2STAT_RXS_SHIFT                                                                             ((uint32_t)0U)
#define MCSPI_CH2STAT_RXS_MASK                                                                              ((uint32_t)0x00000001U)
#define MCSPI_CH2STAT_RXS_EMPTY                                                                              ((uint32_t)0U)
#define MCSPI_CH2STAT_RXS_FULL                                                                               ((uint32_t)1U)

#define MCSPI_CH2STAT_EOT_SHIFT                                                                             ((uint32_t)2U)
#define MCSPI_CH2STAT_EOT_MASK                                                                              ((uint32_t)0x00000004U)
#define MCSPI_CH2STAT_EOT_COMPLETED                                                                          ((uint32_t)1U)
#define MCSPI_CH2STAT_EOT_INPROGRESS                                                                         ((uint32_t)0U)

#define MCSPI_CH2STAT_RESERVED_2_SHIFT                                                                      ((uint32_t)7U)
#define MCSPI_CH2STAT_RESERVED_2_MASK                                                                       ((uint32_t)0xffffff80U)

#define MCSPI_CH2STAT_TXS_SHIFT                                                                             ((uint32_t)1U)
#define MCSPI_CH2STAT_TXS_MASK                                                                              ((uint32_t)0x00000002U)
#define MCSPI_CH2STAT_TXS_EMPTY                                                                              ((uint32_t)1U)
#define MCSPI_CH2STAT_TXS_FULL                                                                               ((uint32_t)0U)

#define MCSPI_CH2STAT_RXFFE_SHIFT                                                                           ((uint32_t)5U)
#define MCSPI_CH2STAT_RXFFE_MASK                                                                            ((uint32_t)0x00000020U)
#define MCSPI_CH2STAT_RXFFE_EMPTY                                                                            ((uint32_t)1U)
#define MCSPI_CH2STAT_RXFFE_NOTEMPTY                                                                         ((uint32_t)0U)

#define MCSPI_CH2STAT_RXFFF_SHIFT                                                                           ((uint32_t)6U)
#define MCSPI_CH2STAT_RXFFF_MASK                                                                            ((uint32_t)0x00000040U)
#define MCSPI_CH2STAT_RXFFF_FULL                                                                             ((uint32_t)1U)
#define MCSPI_CH2STAT_RXFFF_NOTFULL                                                                          ((uint32_t)0U)

#define MCSPI_CH2STAT_TXFFE_SHIFT                                                                           ((uint32_t)3U)
#define MCSPI_CH2STAT_TXFFE_MASK                                                                            ((uint32_t)0x00000008U)
#define MCSPI_CH2STAT_TXFFE_EMPTY                                                                            ((uint32_t)1U)
#define MCSPI_CH2STAT_TXFFE_NOTEMPTY                                                                         ((uint32_t)0U)

#define MCSPI_CH2STAT_TXFFF_SHIFT                                                                           ((uint32_t)4U)
#define MCSPI_CH2STAT_TXFFF_MASK                                                                            ((uint32_t)0x00000010U)
#define MCSPI_CH2STAT_TXFFF_FULL                                                                             ((uint32_t)1U)
#define MCSPI_CH2STAT_TXFFF_NOTFULL                                                                          ((uint32_t)0U)

#define MCSPI_CH2CTRL_RESERVED_1_SHIFT                                                                      ((uint32_t)1U)
#define MCSPI_CH2CTRL_RESERVED_1_MASK                                                                       ((uint32_t)0x000000feU)

#define MCSPI_CH2CTRL_EN_SHIFT                                                                              ((uint32_t)0U)
#define MCSPI_CH2CTRL_EN_MASK                                                                               ((uint32_t)0x00000001U)
#define MCSPI_CH2CTRL_EN_ACT                                                                                 ((uint32_t)1U)
#define MCSPI_CH2CTRL_EN_NACT                                                                                ((uint32_t)0U)

#define MCSPI_CH2CTRL_EXTCLK_SHIFT                                                                          ((uint32_t)8U)
#define MCSPI_CH2CTRL_EXTCLK_MASK                                                                           ((uint32_t)0x0000ff00U)
#define MCSPI_CH2CTRL_EXTCLK_EXTZERO                                                                         ((uint32_t)0U)
#define MCSPI_CH2CTRL_EXTCLK_EXTONE                                                                          ((uint32_t)1U)
#define MCSPI_CH2CTRL_EXTCLK_EXT4080                                                                         ((uint32_t)255U)

#define MCSPI_CH2CTRL_RESERVED_2_SHIFT                                                                      ((uint32_t)16U)
#define MCSPI_CH2CTRL_RESERVED_2_MASK                                                                       ((uint32_t)0xffff0000U)

#define MCSPI_TX2_TDATA_SHIFT                                                                               ((uint32_t)0U)
#define MCSPI_TX2_TDATA_MASK                                                                                ((uint32_t)0xffffffffU)

#define MCSPI_RX2_RDATA_SHIFT                                                                               ((uint32_t)0U)
#define MCSPI_RX2_RDATA_MASK                                                                                ((uint32_t)0xffffffffU)

#define MCSPI_CH3CONF_CLKD_SHIFT                                                                            ((uint32_t)2U)
#define MCSPI_CH3CONF_CLKD_MASK                                                                             ((uint32_t)0x0000003cU)
#define MCSPI_CH3CONF_CLKD_DIVBY4K                                                                           ((uint32_t)12U)
#define MCSPI_CH3CONF_CLKD_DIVBY8                                                                            ((uint32_t)3U)
#define MCSPI_CH3CONF_CLKD_DIVBY8K                                                                           ((uint32_t)13U)
#define MCSPI_CH3CONF_CLKD_DIVBY2K                                                                           ((uint32_t)11U)
#define MCSPI_CH3CONF_CLKD_DIVBY1K                                                                           ((uint32_t)10U)
#define MCSPI_CH3CONF_CLKD_DIVBY512                                                                          ((uint32_t)9U)
#define MCSPI_CH3CONF_CLKD_DIVBY32K                                                                          ((uint32_t)15U)
#define MCSPI_CH3CONF_CLKD_DIVBY4                                                                            ((uint32_t)2U)
#define MCSPI_CH3CONF_CLKD_DIVBY1                                                                            ((uint32_t)0U)
#define MCSPI_CH3CONF_CLKD_DIVBY64                                                                           ((uint32_t)6U)
#define MCSPI_CH3CONF_CLKD_DIVBY256                                                                          ((uint32_t)8U)
#define MCSPI_CH3CONF_CLKD_DIVBY128                                                                          ((uint32_t)7U)
#define MCSPI_CH3CONF_CLKD_DIVBY32                                                                           ((uint32_t)5U)
#define MCSPI_CH3CONF_CLKD_DIVBY16K                                                                          ((uint32_t)14U)
#define MCSPI_CH3CONF_CLKD_DIVBY16                                                                           ((uint32_t)4U)
#define MCSPI_CH3CONF_CLKD_DIVBY2                                                                            ((uint32_t)1U)

#define MCSPI_CH3CONF_RESERVED_0_SHIFT                                                                      ((uint32_t)30U)
#define MCSPI_CH3CONF_RESERVED_0_MASK                                                                       ((uint32_t)0xc0000000U)

#define MCSPI_CH3CONF_PHA_SHIFT                                                                             ((uint32_t)0U)
#define MCSPI_CH3CONF_PHA_MASK                                                                              ((uint32_t)0x00000001U)
#define MCSPI_CH3CONF_PHA_ODD                                                                                ((uint32_t)0U)
#define MCSPI_CH3CONF_PHA_EVEN                                                                               ((uint32_t)1U)

#define MCSPI_CH3CONF_TURBO_SHIFT                                                                           ((uint32_t)19U)
#define MCSPI_CH3CONF_TURBO_MASK                                                                            ((uint32_t)0x00080000U)
#define MCSPI_CH3CONF_TURBO_TURBO                                                                            ((uint32_t)1U)
#define MCSPI_CH3CONF_TURBO_OFF                                                                              ((uint32_t)0U)

#define MCSPI_CH3CONF_RESERVED_1_SHIFT                                                                      ((uint32_t)21U)
#define MCSPI_CH3CONF_RESERVED_1_MASK                                                                       ((uint32_t)0x00600000U)

#define MCSPI_CH3CONF_DPE0_SHIFT                                                                            ((uint32_t)16U)
#define MCSPI_CH3CONF_DPE0_MASK                                                                             ((uint32_t)0x00010000U)
#define MCSPI_CH3CONF_DPE0_DISABLED                                                                          ((uint32_t)1U)
#define MCSPI_CH3CONF_DPE0_ENABLED                                                                           ((uint32_t)0U)

#define MCSPI_CH3CONF_IS_SHIFT                                                                              ((uint32_t)18U)
#define MCSPI_CH3CONF_IS_MASK                                                                               ((uint32_t)0x00040000U)
#define MCSPI_CH3CONF_IS_LINE0                                                                               ((uint32_t)0U)
#define MCSPI_CH3CONF_IS_LINE1                                                                               ((uint32_t)1U)

#define MCSPI_CH3CONF_DMAR_SHIFT                                                                            ((uint32_t)15U)
#define MCSPI_CH3CONF_DMAR_MASK                                                                             ((uint32_t)0x00008000U)
#define MCSPI_CH3CONF_DMAR_DISABLED                                                                          ((uint32_t)0U)
#define MCSPI_CH3CONF_DMAR_ENABLED                                                                           ((uint32_t)1U)

#define MCSPI_CH3CONF_FORCE_SHIFT                                                                           ((uint32_t)20U)
#define MCSPI_CH3CONF_FORCE_MASK                                                                            ((uint32_t)0x00100000U)
#define MCSPI_CH3CONF_FORCE_DEASSERT                                                                         ((uint32_t)0U)
#define MCSPI_CH3CONF_FORCE_ASSERT                                                                           ((uint32_t)1U)

#define MCSPI_CH3CONF_WL_SHIFT                                                                              ((uint32_t)7U)
#define MCSPI_CH3CONF_WL_MASK                                                                               ((uint32_t)0x00000f80U)
#define MCSPI_CH3CONF_WL_21BITS                                                                              ((uint32_t)20U)
#define MCSPI_CH3CONF_WL_26BITS                                                                              ((uint32_t)25U)
#define MCSPI_CH3CONF_WL_18BITS                                                                              ((uint32_t)17U)
#define MCSPI_CH3CONF_WL_20BITS                                                                              ((uint32_t)19U)
#define MCSPI_CH3CONF_WL_5BITS                                                                               ((uint32_t)4U)
#define MCSPI_CH3CONF_WL_6BITS                                                                               ((uint32_t)5U)
#define MCSPI_CH3CONF_WL_11BITS                                                                              ((uint32_t)10U)
#define MCSPI_CH3CONF_WL_8BITS                                                                               ((uint32_t)7U)
#define MCSPI_CH3CONF_WL_13BITS                                                                              ((uint32_t)12U)
#define MCSPI_CH3CONF_WL_29BITS                                                                              ((uint32_t)28U)
#define MCSPI_CH3CONF_WL_12BITS                                                                              ((uint32_t)11U)
#define MCSPI_CH3CONF_WL_32BITS                                                                              ((uint32_t)31U)
#define MCSPI_CH3CONF_WL_31BITS                                                                              ((uint32_t)30U)
#define MCSPI_CH3CONF_WL_30BITS                                                                              ((uint32_t)29U)
#define MCSPI_CH3CONF_WL_9BITS                                                                               ((uint32_t)8U)
#define MCSPI_CH3CONF_WL_7BITS                                                                               ((uint32_t)6U)
#define MCSPI_CH3CONF_WL_10BITS                                                                              ((uint32_t)9U)
#define MCSPI_CH3CONF_WL_16BITS                                                                              ((uint32_t)15U)
#define MCSPI_CH3CONF_WL_17BITS                                                                              ((uint32_t)16U)
#define MCSPI_CH3CONF_WL_14BITS                                                                              ((uint32_t)13U)
#define MCSPI_CH3CONF_WL_15BITS                                                                              ((uint32_t)14U)
#define MCSPI_CH3CONF_WL_RSVD1                                                                               ((uint32_t)1U)
#define MCSPI_CH3CONF_WL_RSVD0                                                                               ((uint32_t)0U)
#define MCSPI_CH3CONF_WL_27BITS                                                                              ((uint32_t)26U)
#define MCSPI_CH3CONF_WL_23BITS                                                                              ((uint32_t)22U)
#define MCSPI_CH3CONF_WL_RSVD2                                                                               ((uint32_t)2U)
#define MCSPI_CH3CONF_WL_19BITS                                                                              ((uint32_t)18U)
#define MCSPI_CH3CONF_WL_4BITS                                                                               ((uint32_t)3U)
#define MCSPI_CH3CONF_WL_25BITS                                                                              ((uint32_t)24U)
#define MCSPI_CH3CONF_WL_24BITS                                                                              ((uint32_t)23U)
#define MCSPI_CH3CONF_WL_22BITS                                                                              ((uint32_t)21U)
#define MCSPI_CH3CONF_WL_28BITS                                                                              ((uint32_t)27U)

#define MCSPI_CH3CONF_DPE1_SHIFT                                                                            ((uint32_t)17U)
#define MCSPI_CH3CONF_DPE1_MASK                                                                             ((uint32_t)0x00020000U)
#define MCSPI_CH3CONF_DPE1_ENABLED                                                                           ((uint32_t)0U)
#define MCSPI_CH3CONF_DPE1_DISABLED                                                                          ((uint32_t)1U)

#define MCSPI_CH3CONF_EPOL_SHIFT                                                                            ((uint32_t)6U)
#define MCSPI_CH3CONF_EPOL_MASK                                                                             ((uint32_t)0x00000040U)
#define MCSPI_CH3CONF_EPOL_ACTIVELOW                                                                         ((uint32_t)1U)
#define MCSPI_CH3CONF_EPOL_ACTIVEHIGH                                                                        ((uint32_t)0U)

#define MCSPI_CH3CONF_DMAW_SHIFT                                                                            ((uint32_t)14U)
#define MCSPI_CH3CONF_DMAW_MASK                                                                             ((uint32_t)0x00004000U)
#define MCSPI_CH3CONF_DMAW_ENABLED                                                                           ((uint32_t)1U)
#define MCSPI_CH3CONF_DMAW_DISABLED                                                                          ((uint32_t)0U)

#define MCSPI_CH3CONF_TRM_SHIFT                                                                             ((uint32_t)12U)
#define MCSPI_CH3CONF_TRM_MASK                                                                              ((uint32_t)0x00003000U)
#define MCSPI_CH3CONF_TRM_TRANSONLY                                                                          ((uint32_t)2U)
#define MCSPI_CH3CONF_TRM_RSVD                                                                               ((uint32_t)3U)
#define MCSPI_CH3CONF_TRM_TRANSRECEI                                                                         ((uint32_t)0U)
#define MCSPI_CH3CONF_TRM_RECEIVONLY                                                                         ((uint32_t)1U)

#define MCSPI_CH3CONF_POL_SHIFT                                                                             ((uint32_t)1U)
#define MCSPI_CH3CONF_POL_MASK                                                                              ((uint32_t)0x00000002U)
#define MCSPI_CH3CONF_POL_ACTIVELOW                                                                          ((uint32_t)1U)
#define MCSPI_CH3CONF_POL_ACTIVEHIGH                                                                         ((uint32_t)0U)

#define MCSPI_CH3CONF_SBE_SHIFT                                                                             ((uint32_t)23U)
#define MCSPI_CH3CONF_SBE_MASK                                                                              ((uint32_t)0x00800000U)
#define MCSPI_CH3CONF_SBE_DISABLED                                                                           ((uint32_t)0U)
#define MCSPI_CH3CONF_SBE_ENABLED                                                                            ((uint32_t)1U)

#define MCSPI_CH3CONF_SBPOL_SHIFT                                                                           ((uint32_t)24U)
#define MCSPI_CH3CONF_SBPOL_MASK                                                                            ((uint32_t)0x01000000U)
#define MCSPI_CH3CONF_SBPOL_LOWLEVEL                                                                         ((uint32_t)0U)
#define MCSPI_CH3CONF_SBPOL_HIGHLEVEL                                                                        ((uint32_t)1U)

#define MCSPI_CH3CONF_TCS3_SHIFT                                                                            ((uint32_t)25U)
#define MCSPI_CH3CONF_TCS3_MASK                                                                             ((uint32_t)0x06000000U)
#define MCSPI_CH3CONF_TCS3_THREECYCLEDLY                                                                     ((uint32_t)3U)
#define MCSPI_CH3CONF_TCS3_TWOCYCLEDLY                                                                       ((uint32_t)2U)
#define MCSPI_CH3CONF_TCS3_ONECYCLEDLY                                                                       ((uint32_t)1U)
#define MCSPI_CH3CONF_TCS3_ZEROCYCLEDLY                                                                      ((uint32_t)0U)

#define MCSPI_CH3CONF_FFER_SHIFT                                                                            ((uint32_t)28U)
#define MCSPI_CH3CONF_FFER_MASK                                                                             ((uint32_t)0x10000000U)
#define MCSPI_CH3CONF_FFER_FFENABLED                                                                         ((uint32_t)1U)
#define MCSPI_CH3CONF_FFER_FFDISABLED                                                                        ((uint32_t)0U)

#define MCSPI_CH3CONF_FFEW_SHIFT                                                                            ((uint32_t)27U)
#define MCSPI_CH3CONF_FFEW_MASK                                                                             ((uint32_t)0x08000000U)
#define MCSPI_CH3CONF_FFEW_FFENABLED                                                                         ((uint32_t)1U)
#define MCSPI_CH3CONF_FFEW_FFDISABLED                                                                        ((uint32_t)0U)

#define MCSPI_CH3CONF_CLKG_SHIFT                                                                            ((uint32_t)29U)
#define MCSPI_CH3CONF_CLKG_MASK                                                                             ((uint32_t)0x20000000U)
#define MCSPI_CH3CONF_CLKG_ONECYCLE                                                                          ((uint32_t)1U)
#define MCSPI_CH3CONF_CLKG_POWERTWO                                                                          ((uint32_t)0U)

#define MCSPI_CH3STAT_RXS_SHIFT                                                                             ((uint32_t)0U)
#define MCSPI_CH3STAT_RXS_MASK                                                                              ((uint32_t)0x00000001U)
#define MCSPI_CH3STAT_RXS_EMPTY                                                                              ((uint32_t)0U)
#define MCSPI_CH3STAT_RXS_FULL                                                                               ((uint32_t)1U)

#define MCSPI_CH3STAT_EOT_SHIFT                                                                             ((uint32_t)2U)
#define MCSPI_CH3STAT_EOT_MASK                                                                              ((uint32_t)0x00000004U)
#define MCSPI_CH3STAT_EOT_COMPLETED                                                                          ((uint32_t)1U)
#define MCSPI_CH3STAT_EOT_INPROGRESS                                                                         ((uint32_t)0U)

#define MCSPI_CH3STAT_RESERVED_2_SHIFT                                                                      ((uint32_t)7U)
#define MCSPI_CH3STAT_RESERVED_2_MASK                                                                       ((uint32_t)0xffffff80U)

#define MCSPI_CH3STAT_TXS_SHIFT                                                                             ((uint32_t)1U)
#define MCSPI_CH3STAT_TXS_MASK                                                                              ((uint32_t)0x00000002U)
#define MCSPI_CH3STAT_TXS_EMPTY                                                                              ((uint32_t)1U)
#define MCSPI_CH3STAT_TXS_FULL                                                                               ((uint32_t)0U)

#define MCSPI_CH3STAT_RXFFE_SHIFT                                                                           ((uint32_t)5U)
#define MCSPI_CH3STAT_RXFFE_MASK                                                                            ((uint32_t)0x00000020U)
#define MCSPI_CH3STAT_RXFFE_EMPTY                                                                            ((uint32_t)1U)
#define MCSPI_CH3STAT_RXFFE_NOTEMPTY                                                                         ((uint32_t)0U)

#define MCSPI_CH3STAT_RXFFF_SHIFT                                                                           ((uint32_t)6U)
#define MCSPI_CH3STAT_RXFFF_MASK                                                                            ((uint32_t)0x00000040U)
#define MCSPI_CH3STAT_RXFFF_FULL                                                                             ((uint32_t)1U)
#define MCSPI_CH3STAT_RXFFF_NOTFULL                                                                          ((uint32_t)0U)

#define MCSPI_CH3STAT_TXFFE_SHIFT                                                                           ((uint32_t)3U)
#define MCSPI_CH3STAT_TXFFE_MASK                                                                            ((uint32_t)0x00000008U)
#define MCSPI_CH3STAT_TXFFE_EMPTY                                                                            ((uint32_t)1U)
#define MCSPI_CH3STAT_TXFFE_NOTEMPTY                                                                         ((uint32_t)0U)

#define MCSPI_CH3STAT_TXFFF_SHIFT                                                                           ((uint32_t)4U)
#define MCSPI_CH3STAT_TXFFF_MASK                                                                            ((uint32_t)0x00000010U)
#define MCSPI_CH3STAT_TXFFF_FULL                                                                             ((uint32_t)1U)
#define MCSPI_CH3STAT_TXFFF_NOTFULL                                                                          ((uint32_t)0U)

#define MCSPI_CH3CTRL_RESERVED_1_SHIFT                                                                      ((uint32_t)1U)
#define MCSPI_CH3CTRL_RESERVED_1_MASK                                                                       ((uint32_t)0x000000feU)

#define MCSPI_CH3CTRL_EN_SHIFT                                                                              ((uint32_t)0U)
#define MCSPI_CH3CTRL_EN_MASK                                                                               ((uint32_t)0x00000001U)
#define MCSPI_CH3CTRL_EN_ACT                                                                                 ((uint32_t)1U)
#define MCSPI_CH3CTRL_EN_NACT                                                                                ((uint32_t)0U)

#define MCSPI_CH3CTRL_EXTCLK_SHIFT                                                                          ((uint32_t)8U)
#define MCSPI_CH3CTRL_EXTCLK_MASK                                                                           ((uint32_t)0x0000ff00U)
#define MCSPI_CH3CTRL_EXTCLK_EXTZERO                                                                         ((uint32_t)0U)
#define MCSPI_CH3CTRL_EXTCLK_EXTONE                                                                          ((uint32_t)1U)
#define MCSPI_CH3CTRL_EXTCLK_EXT4080                                                                         ((uint32_t)255U)

#define MCSPI_CH3CTRL_RESERVED_2_SHIFT                                                                      ((uint32_t)16U)
#define MCSPI_CH3CTRL_RESERVED_2_MASK                                                                       ((uint32_t)0xffff0000U)

#define MCSPI_TX3_TDATA_SHIFT                                                                               ((uint32_t)0U)
#define MCSPI_TX3_TDATA_MASK                                                                                ((uint32_t)0xffffffffU)

#define MCSPI_RX3_RDATA_SHIFT                                                                               ((uint32_t)0U)
#define MCSPI_RX3_RDATA_MASK                                                                                ((uint32_t)0xffffffffU)

#define MCSPI_XFERLEVEL_AEL_SHIFT                                                                           ((uint32_t)0U)
#define MCSPI_XFERLEVEL_AEL_MASK                                                                            ((uint32_t)0x000000ffU)
#define MCSPI_XFERLEVEL_AEL_256BYTES                                                                         ((uint32_t)255U)
#define MCSPI_XFERLEVEL_AEL_255BYTES                                                                         ((uint32_t)254U)
#define MCSPI_XFERLEVEL_AEL_2BYTES                                                                           ((uint32_t)1U)
#define MCSPI_XFERLEVEL_AEL_1BYTE                                                                            ((uint32_t)0U)

#define MCSPI_XFERLEVEL_WCNT_SHIFT                                                                          ((uint32_t)16U)
#define MCSPI_XFERLEVEL_WCNT_MASK                                                                           ((uint32_t)0xffff0000U)
#define MCSPI_XFERLEVEL_WCNT_65535WORD                                                                       ((uint32_t)65535U)
#define MCSPI_XFERLEVEL_WCNT_65534WORD                                                                       ((uint32_t)65534U)
#define MCSPI_XFERLEVEL_WCNT_1WORD                                                                           ((uint32_t)1U)
#define MCSPI_XFERLEVEL_WCNT_DISABLE                                                                         ((uint32_t)0U)

#define MCSPI_XFERLEVEL_AFL_SHIFT                                                                           ((uint32_t)8U)
#define MCSPI_XFERLEVEL_AFL_MASK                                                                            ((uint32_t)0x0000ff00U)
#define MCSPI_XFERLEVEL_AFL_256BYTES                                                                         ((uint32_t)255U)
#define MCSPI_XFERLEVEL_AFL_255BYTES                                                                         ((uint32_t)254U)
#define MCSPI_XFERLEVEL_AFL_2BYTES                                                                           ((uint32_t)1U)
#define MCSPI_XFERLEVEL_AFL_1BYTE                                                                            ((uint32_t)0U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MCSPI_H_ */
