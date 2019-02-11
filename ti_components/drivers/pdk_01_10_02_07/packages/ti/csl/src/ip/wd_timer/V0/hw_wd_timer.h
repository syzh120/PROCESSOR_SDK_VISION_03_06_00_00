/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
 * \file  hw_wd_timer.h
 *
 * \brief Register-level header file for WD_TIMER
 *
**/

#ifndef HW_WD_TIMER_H_
#define HW_WD_TIMER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define WD_TIMER_WIDR                                                                                       (0x0U)
#define WD_TIMER_WDSC                                                                                       (0x10U)
#define WD_TIMER_WDST                                                                                       (0x14U)
#define WD_TIMER_WISR                                                                                       (0x18U)
#define WD_TIMER_WIER                                                                                       (0x1cU)
#define WD_TIMER_WWER                                                                                       (0x20U)
#define WD_TIMER_WCLR                                                                                       (0x24U)
#define WD_TIMER_WCRR                                                                                       (0x28U)
#define WD_TIMER_WLDR                                                                                       (0x2cU)
#define WD_TIMER_WTGR                                                                                       (0x30U)
#define WD_TIMER_WWPS                                                                                       (0x34U)
#define WD_TIMER_WDLY                                                                                       (0x44U)
#define WD_TIMER_WSPR                                                                                       (0x48U)
#define WD_TIMER_WIRQEOI                                                                                    (0x50U)
#define WD_TIMER_WIRQSTATRAW                                                                                (0x54U)
#define WD_TIMER_WIRQSTAT                                                                                   (0x58U)
#define WD_TIMER_WIRQENSET                                                                                  (0x5cU)
#define WD_TIMER_WIRQENCLR                                                                                  (0x60U)
#define WD_TIMER_WIRQWAKEEN                                                                                 (0x64U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define WD_TIMER_WIDR_REV_SHIFT                                                                             (0U)
#define WD_TIMER_WIDR_REV_MASK                                                                              (0xffffffffU)

#define WD_TIMER_WDSC_SOFTRESET_SHIFT                                                                       (1U)
#define WD_TIMER_WDSC_SOFTRESET_MASK                                                                        (0x00000002U)
#define WD_TIMER_WDSC_SOFTRESET_NOACTION                                                                     (0U)
#define WD_TIMER_WDSC_SOFTRESET_RESETCMD                                                                     (1U)
#define WD_TIMER_WDSC_SOFTRESET_RESETONGOING                                                                 (1U)
#define WD_TIMER_WDSC_SOFTRESET_RESETCOMPLETED                                                               (0U)

#define WD_TIMER_WDSC_RESERVED_SHIFT                                                                        (0U)
#define WD_TIMER_WDSC_RESERVED_MASK                                                                         (0x00000001U)

#define WD_TIMER_WDSC_IDLEMODE_SHIFT                                                                        (3U)
#define WD_TIMER_WDSC_IDLEMODE_MASK                                                                         (0x00000018U)
#define WD_TIMER_WDSC_IDLEMODE_FORCEIDLE                                                                     (0U)
#define WD_TIMER_WDSC_IDLEMODE_NOIDLE                                                                        (1U)
#define WD_TIMER_WDSC_IDLEMODE_SMARTIDLE                                                                     (2U)
#define WD_TIMER_WDSC_IDLEMODE_SMARTIDLEWAKEUP                                                               (3U)

#define WD_TIMER_WDSC_EMUFREE_SHIFT                                                                         (5U)
#define WD_TIMER_WDSC_EMUFREE_MASK                                                                          (0x00000020U)
#define WD_TIMER_WDSC_EMUFREE_DISABLED                                                                       (0U)
#define WD_TIMER_WDSC_EMUFREE_ENABLED                                                                        (1U)

#define WD_TIMER_WDSC_RESERVED1_SHIFT                                                                       (2U)
#define WD_TIMER_WDSC_RESERVED1_MASK                                                                        (0x00000004U)

#define WD_TIMER_WDSC_RESERVED2_SHIFT                                                                       (6U)
#define WD_TIMER_WDSC_RESERVED2_MASK                                                                        (0xffffffc0U)

#define WD_TIMER_WDST_RESETDONE_SHIFT                                                                       (0U)
#define WD_TIMER_WDST_RESETDONE_MASK                                                                        (0x00000001U)
#define WD_TIMER_WDST_RESETDONE_ONGOING                                                                      (0U)
#define WD_TIMER_WDST_RESETDONE_RESETDONE                                                                    (1U)

#define WD_TIMER_WDST_RESERVED_SHIFT                                                                        (1U)
#define WD_TIMER_WDST_RESERVED_MASK                                                                         (0xfffffffeU)

#define WD_TIMER_WISR_OVF_IT_FLAG_SHIFT                                                                     (0U)
#define WD_TIMER_WISR_OVF_IT_FLAG_MASK                                                                      (0x00000001U)
#define WD_TIMER_WISR_OVF_IT_FLAG_READ_0                                                                     (0U)
#define WD_TIMER_WISR_OVF_IT_FLAG_READ_1                                                                     (1U)
#define WD_TIMER_WISR_OVF_IT_FLAG_WRITE_0                                                                    (0U)
#define WD_TIMER_WISR_OVF_IT_FLAG_WRITE_1                                                                    (1U)

#define WD_TIMER_WISR_DLY_IT_FLAG_SHIFT                                                                     (1U)
#define WD_TIMER_WISR_DLY_IT_FLAG_MASK                                                                      (0x00000002U)
#define WD_TIMER_WISR_DLY_IT_FLAG_READ_0                                                                     (0U)
#define WD_TIMER_WISR_DLY_IT_FLAG_READ_1                                                                     (1U)
#define WD_TIMER_WISR_DLY_IT_FLAG_WRITE_0                                                                    (0U)
#define WD_TIMER_WISR_DLY_IT_FLAG_WRITE_1                                                                    (1U)

#define WD_TIMER_WISR_RESERVED_SHIFT                                                                        (2U)
#define WD_TIMER_WISR_RESERVED_MASK                                                                         (0xfffffffcU)

#define WD_TIMER_WIER_OVF_IT_ENA_SHIFT                                                                      (0U)
#define WD_TIMER_WIER_OVF_IT_ENA_MASK                                                                       (0x00000001U)
#define WD_TIMER_WIER_OVF_IT_ENA_DISABLED                                                                    (0U)
#define WD_TIMER_WIER_OVF_IT_ENA_ENABLED                                                                     (1U)

#define WD_TIMER_WIER_DLY_IT_ENA_SHIFT                                                                      (1U)
#define WD_TIMER_WIER_DLY_IT_ENA_MASK                                                                       (0x00000002U)
#define WD_TIMER_WIER_DLY_IT_ENA_DISABLED                                                                    (0U)
#define WD_TIMER_WIER_DLY_IT_ENA_ENABLED                                                                     (1U)

#define WD_TIMER_WIER_RESERVED_SHIFT                                                                        (2U)
#define WD_TIMER_WIER_RESERVED_MASK                                                                         (0xfffffffcU)

#define WD_TIMER_WWER_OVF_WK_ENA_SHIFT                                                                      (0U)
#define WD_TIMER_WWER_OVF_WK_ENA_MASK                                                                       (0x00000001U)
#define WD_TIMER_WWER_OVF_WK_ENA_DISABLED                                                                    (0U)
#define WD_TIMER_WWER_OVF_WK_ENA_ENABLED                                                                     (1U)

#define WD_TIMER_WWER_DLY_WK_ENA_SHIFT                                                                      (1U)
#define WD_TIMER_WWER_DLY_WK_ENA_MASK                                                                       (0x00000002U)
#define WD_TIMER_WWER_DLY_WK_ENA_DISABLED                                                                    (0U)
#define WD_TIMER_WWER_DLY_WK_ENA_ENABLED                                                                     (1U)

#define WD_TIMER_WWER_RESERVED_SHIFT                                                                        (2U)
#define WD_TIMER_WWER_RESERVED_MASK                                                                         (0xfffffffcU)

#define WD_TIMER_WCLR_RESERVED_SHIFT                                                                        (0U)
#define WD_TIMER_WCLR_RESERVED_MASK                                                                         (0x00000003U)

#define WD_TIMER_WCLR_PTV_SHIFT                                                                             (2U)
#define WD_TIMER_WCLR_PTV_MASK                                                                              (0x0000001cU)

#define WD_TIMER_WCLR_PRE_SHIFT                                                                             (5U)
#define WD_TIMER_WCLR_PRE_MASK                                                                              (0x00000020U)
#define WD_TIMER_WCLR_PRE_DISABLED                                                                           (0U)
#define WD_TIMER_WCLR_PRE_ENABLED                                                                            (1U)

#define WD_TIMER_WCLR_RESERVED1_SHIFT                                                                       (6U)
#define WD_TIMER_WCLR_RESERVED1_MASK                                                                        (0xffffffc0U)

#define WD_TIMER_WCRR_TIMER_COUNTER_SHIFT                                                                   (0U)
#define WD_TIMER_WCRR_TIMER_COUNTER_MASK                                                                    (0xffffffffU)

#define WD_TIMER_WLDR_TIMER_LOAD_SHIFT                                                                      (0U)
#define WD_TIMER_WLDR_TIMER_LOAD_MASK                                                                       (0xffffffffU)

#define WD_TIMER_WTGR_TTGR_VALUE_SHIFT                                                                      (0U)
#define WD_TIMER_WTGR_TTGR_VALUE_MASK                                                                       (0xffffffffU)

#define WD_TIMER_WWPS_W_PEND_WCLR_SHIFT                                                                     (0U)
#define WD_TIMER_WWPS_W_PEND_WCLR_MASK                                                                      (0x00000001U)
#define WD_TIMER_WWPS_W_PEND_WCLR_READY                                                                      (0U)
#define WD_TIMER_WWPS_W_PEND_WCLR_PENDING                                                                    (1U)

#define WD_TIMER_WWPS_W_PEND_WTGR_SHIFT                                                                     (3U)
#define WD_TIMER_WWPS_W_PEND_WTGR_MASK                                                                      (0x00000008U)
#define WD_TIMER_WWPS_W_PEND_WTGR_READY                                                                      (0U)
#define WD_TIMER_WWPS_W_PEND_WTGR_PENDING                                                                    (1U)

#define WD_TIMER_WWPS_W_PEND_WSPR_SHIFT                                                                     (4U)
#define WD_TIMER_WWPS_W_PEND_WSPR_MASK                                                                      (0x00000010U)
#define WD_TIMER_WWPS_W_PEND_WSPR_READY                                                                      (0U)
#define WD_TIMER_WWPS_W_PEND_WSPR_PENDING                                                                    (1U)

#define WD_TIMER_WWPS_W_PEND_WDLY_SHIFT                                                                     (5U)
#define WD_TIMER_WWPS_W_PEND_WDLY_MASK                                                                      (0x00000020U)
#define WD_TIMER_WWPS_W_PEND_WDLY_READY                                                                      (0U)
#define WD_TIMER_WWPS_W_PEND_WDLY_PENDING                                                                    (1U)

#define WD_TIMER_WWPS_RESERVED_SHIFT                                                                        (6U)
#define WD_TIMER_WWPS_RESERVED_MASK                                                                         (0xffffffc0U)

#define WD_TIMER_WWPS_W_PEND_WCRR_SHIFT                                                                     (1U)
#define WD_TIMER_WWPS_W_PEND_WCRR_MASK                                                                      (0x00000002U)
#define WD_TIMER_WWPS_W_PEND_WCRR_READY                                                                      (0U)
#define WD_TIMER_WWPS_W_PEND_WCRR_PENDING                                                                    (1U)

#define WD_TIMER_WWPS_W_PEND_WLDR_SHIFT                                                                     (2U)
#define WD_TIMER_WWPS_W_PEND_WLDR_MASK                                                                      (0x00000004U)
#define WD_TIMER_WWPS_W_PEND_WLDR_READY                                                                      (0U)
#define WD_TIMER_WWPS_W_PEND_WLDR_PENDING                                                                    (1U)

#define WD_TIMER_WDLY_WDLY_VALUE_SHIFT                                                                      (0U)
#define WD_TIMER_WDLY_WDLY_VALUE_MASK                                                                       (0xffffffffU)

#define WD_TIMER_WSPR_WSPR_VALUE_SHIFT                                                                      (0U)
#define WD_TIMER_WSPR_WSPR_VALUE_MASK                                                                       (0xffffffffU)

#define WD_TIMER_WIRQEOI_LINE_NUMBER_SHIFT                                                                  (0U)
#define WD_TIMER_WIRQEOI_LINE_NUMBER_MASK                                                                   (0x00000001U)

#define WD_TIMER_WIRQEOI_RESERVED_SHIFT                                                                     (1U)
#define WD_TIMER_WIRQEOI_RESERVED_MASK                                                                      (0xfffffffeU)

#define WD_TIMER_WIRQSTATRAW_EVENT_OVF_SHIFT                                                                (0U)
#define WD_TIMER_WIRQSTATRAW_EVENT_OVF_MASK                                                                 (0x00000001U)
#define WD_TIMER_WIRQSTATRAW_EVENT_OVF_READ_0                                                                (0U)
#define WD_TIMER_WIRQSTATRAW_EVENT_OVF_READ_1                                                                (1U)
#define WD_TIMER_WIRQSTATRAW_EVENT_OVF_WRITE_0                                                               (0U)
#define WD_TIMER_WIRQSTATRAW_EVENT_OVF_WRITE_1                                                               (1U)

#define WD_TIMER_WIRQSTATRAW_EVENT_DLY_SHIFT                                                                (1U)
#define WD_TIMER_WIRQSTATRAW_EVENT_DLY_MASK                                                                 (0x00000002U)
#define WD_TIMER_WIRQSTATRAW_EVENT_DLY_READ_0                                                                (0U)
#define WD_TIMER_WIRQSTATRAW_EVENT_DLY_READ_1                                                                (1U)
#define WD_TIMER_WIRQSTATRAW_EVENT_DLY_WRITE_0                                                               (0U)
#define WD_TIMER_WIRQSTATRAW_EVENT_DLY_WRITE_1                                                               (1U)

#define WD_TIMER_WIRQSTATRAW_RESERVED_SHIFT                                                                 (2U)
#define WD_TIMER_WIRQSTATRAW_RESERVED_MASK                                                                  (0xfffffffcU)

#define WD_TIMER_WIRQSTAT_EVENT_OVF_SHIFT                                                                   (0U)
#define WD_TIMER_WIRQSTAT_EVENT_OVF_MASK                                                                    (0x00000001U)
#define WD_TIMER_WIRQSTAT_EVENT_OVF_READ_0                                                                   (0U)
#define WD_TIMER_WIRQSTAT_EVENT_OVF_READ_1                                                                   (1U)
#define WD_TIMER_WIRQSTAT_EVENT_OVF_WRITE_0                                                                  (0U)
#define WD_TIMER_WIRQSTAT_EVENT_OVF_WRITE_1                                                                  (1U)

#define WD_TIMER_WIRQSTAT_EVENT_DLY_SHIFT                                                                   (1U)
#define WD_TIMER_WIRQSTAT_EVENT_DLY_MASK                                                                    (0x00000002U)
#define WD_TIMER_WIRQSTAT_EVENT_DLY_READ_0                                                                   (0U)
#define WD_TIMER_WIRQSTAT_EVENT_DLY_READ_1                                                                   (1U)
#define WD_TIMER_WIRQSTAT_EVENT_DLY_WRITE_0                                                                  (0U)
#define WD_TIMER_WIRQSTAT_EVENT_DLY_WRITE_1                                                                  (1U)

#define WD_TIMER_WIRQSTAT_RESERVED_SHIFT                                                                    (2U)
#define WD_TIMER_WIRQSTAT_RESERVED_MASK                                                                     (0xfffffffcU)

#define WD_TIMER_WIRQENSET_ENABLE_OVF_SHIFT                                                                 (0U)
#define WD_TIMER_WIRQENSET_ENABLE_OVF_MASK                                                                  (0x00000001U)
#define WD_TIMER_WIRQENSET_ENABLE_OVF_READ_0                                                                 (0U)
#define WD_TIMER_WIRQENSET_ENABLE_OVF_READ_1                                                                 (1U)
#define WD_TIMER_WIRQENSET_ENABLE_OVF_WRITE_0                                                                (0U)
#define WD_TIMER_WIRQENSET_ENABLE_OVF_WRITE_1                                                                (1U)

#define WD_TIMER_WIRQENSET_ENABLE_DLY_SHIFT                                                                 (1U)
#define WD_TIMER_WIRQENSET_ENABLE_DLY_MASK                                                                  (uint32_t)(0x00000002U)
#define WD_TIMER_WIRQENSET_ENABLE_DLY_READ_0                                                                 (0U)
#define WD_TIMER_WIRQENSET_ENABLE_DLY_READ_1                                                                 (1U)
#define WD_TIMER_WIRQENSET_ENABLE_DLY_WRITE_0                                                                (0U)
#define WD_TIMER_WIRQENSET_ENABLE_DLY_WRITE_1                                                                (1U)

#define WD_TIMER_WIRQENSET_RESERVED_SHIFT                                                                   (2U)
#define WD_TIMER_WIRQENSET_RESERVED_MASK                                                                    (0xfffffffcU)

#define WD_TIMER_WIRQENCLR_ENABLE_OVF_SHIFT                                                                 (0U)
#define WD_TIMER_WIRQENCLR_ENABLE_OVF_MASK                                                                  (0x00000001U)
#define WD_TIMER_WIRQENCLR_ENABLE_OVF_READ_0                                                                 (0U)
#define WD_TIMER_WIRQENCLR_ENABLE_OVF_READ_1                                                                 (1U)
#define WD_TIMER_WIRQENCLR_ENABLE_OVF_WRITE_0                                                                (0U)
#define WD_TIMER_WIRQENCLR_ENABLE_OVF_WRITE_1                                                                (1U)

#define WD_TIMER_WIRQENCLR_ENABLE_DLY_SHIFT                                                                 (1U)
#define WD_TIMER_WIRQENCLR_ENABLE_DLY_MASK                                                                  (0x00000002U)
#define WD_TIMER_WIRQENCLR_ENABLE_DLY_READ_0                                                                 (0U)
#define WD_TIMER_WIRQENCLR_ENABLE_DLY_READ_1                                                                 (1U)
#define WD_TIMER_WIRQENCLR_ENABLE_DLY_WRITE_0                                                                (0U)
#define WD_TIMER_WIRQENCLR_ENABLE_DLY_WRITE_1                                                                (1U)

#define WD_TIMER_WIRQENCLR_RESERVED_SHIFT                                                                   (2U)
#define WD_TIMER_WIRQENCLR_RESERVED_MASK                                                                    (0xfffffffcU)

#define WD_TIMER_WIRQWAKEEN_OVF_WK_ENA_SHIFT                                                                (0U)
#define WD_TIMER_WIRQWAKEEN_OVF_WK_ENA_MASK                                                                 (0x00000001U)
#define WD_TIMER_WIRQWAKEEN_OVF_WK_ENA_DISABLED                                                              (0U)
#define WD_TIMER_WIRQWAKEEN_OVF_WK_ENA_ENABLED                                                               (1U)

#define WD_TIMER_WIRQWAKEEN_DLY_WK_ENA_SHIFT                                                                (1U)
#define WD_TIMER_WIRQWAKEEN_DLY_WK_ENA_MASK                                                                 (0x00000002U)
#define WD_TIMER_WIRQWAKEEN_DLY_WK_ENA_DISABLED                                                              (0U)
#define WD_TIMER_WIRQWAKEEN_DLY_WK_ENA_ENABLED                                                               (1U)

#define WD_TIMER_WIRQWAKEEN_RESERVED_SHIFT                                                                  (2U)
#define WD_TIMER_WIRQWAKEEN_RESERVED_MASK                                                                   (0xfffffffcU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_WD_TIMER_H_ */

