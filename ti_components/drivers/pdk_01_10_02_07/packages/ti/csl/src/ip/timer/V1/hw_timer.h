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
 * \file  hw_timer.h
 *
 * \brief Register-level header file for TIMER
 *
**/

#ifndef HW_TIMER_H_
#define HW_TIMER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define TIMER_TIDR                                                                                          (0x0U)
#define TIMER_TIOCP_CFG                                                                                     (0x10U)
#define TIMER_IRQ_EOI                                                                                       (0x20U)
#define TIMER_IRQSTATUS_RAW                                                                                 (0x24U)
#define TIMER_IRQSTATUS                                                                                     (0x28U)
#define TIMER_IRQENABLE_SET                                                                                 (0x2cU)
#define TIMER_IRQENABLE_CLR                                                                                 (0x30U)
#define TIMER_IRQWAKEEN                                                                                     (0x34U)
#define TIMER_TCLR                                                                                          (0x38U)
#define TIMER_TCRR                                                                                          (0x3cU)
#define TIMER_TLDR                                                                                          (0x40U)
#define TIMER_TTGR                                                                                          (0x44U)
#define TIMER_TWPS                                                                                          (0x48U)
#define TIMER_TMAR                                                                                          (0x4cU)
#define TIMER_TCAR1                                                                                         (0x50U)
#define TIMER_TSICR                                                                                         (0x54U)
#define TIMER_TCAR2                                                                                         (0x58U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define TIMER_TIDR_REVISION_SHIFT                                                                           (0U)
#define TIMER_TIDR_REVISION_MASK                                                                            (0xffffffffU)

#define TIMER_TIOCP_CFG_EMUFREE_SHIFT                                                                       (1U)
#define TIMER_TIOCP_CFG_EMUFREE_MASK                                                                        (0x00000002U)
#define TIMER_TIOCP_CFG_EMUFREE_TIMER_FROZEN                                                                 (0U)
#define TIMER_TIOCP_CFG_EMUFREE_TIMER_FREE                                                                   (1U)

#define TIMER_TIOCP_CFG_IDLEMODE_SHIFT                                                                      (2U)
#define TIMER_TIOCP_CFG_IDLEMODE_MASK                                                                       (0x0000000cU)
#define TIMER_TIOCP_CFG_IDLEMODE_IDLE_MODE_0X0                                                               (0U)
#define TIMER_TIOCP_CFG_IDLEMODE_IDLE_MODE_0X1                                                               (1U)
#define TIMER_TIOCP_CFG_IDLEMODE_IDLE_MODE_0X2                                                               (2U)
#define TIMER_TIOCP_CFG_IDLEMODE_IDLE_MODE_0X3                                                               (3U)

#define TIMER_TIOCP_CFG_SOFTRESET_SHIFT                                                                     (0U)
#define TIMER_TIOCP_CFG_SOFTRESET_MASK                                                                      (0x00000001U)
#define TIMER_TIOCP_CFG_SOFTRESET_SOFTRESET_VALUE_0                                                          (0U)
#define TIMER_TIOCP_CFG_SOFTRESET_SOFTRESET_VALUE_1                                                          (1U)

#define TIMER_TIOCP_CFG_RESERVED_SHIFT                                                                      (4U)
#define TIMER_TIOCP_CFG_RESERVED_MASK                                                                       (0xfffffff0U)

#define TIMER_IRQ_EOI_LINE_NUMBER_SHIFT                                                                     (0U)
#define TIMER_IRQ_EOI_LINE_NUMBER_MASK                                                                      (0x00000001U)

#define TIMER_IRQ_EOI_RESERVED_SHIFT                                                                        (1U)
#define TIMER_IRQ_EOI_RESERVED_MASK                                                                         (0xfffffffeU)

#define TIMER_IRQSTATUS_RAW_MAT_IT_FLAG_SHIFT                                                               (0U)
#define TIMER_IRQSTATUS_RAW_MAT_IT_FLAG_MASK                                                                (0x00000001U)

#define TIMER_IRQSTATUS_RAW_OVF_IT_FLAG_SHIFT                                                               (1U)
#define TIMER_IRQSTATUS_RAW_OVF_IT_FLAG_MASK                                                                (0x00000002U)

#define TIMER_IRQSTATUS_RAW_TCAR_IT_FLAG_SHIFT                                                              (2U)
#define TIMER_IRQSTATUS_RAW_TCAR_IT_FLAG_MASK                                                               (0x00000004U)

#define TIMER_IRQSTATUS_RAW_RESERVED_SHIFT                                                                  (3U)
#define TIMER_IRQSTATUS_RAW_RESERVED_MASK                                                                   (0xfffffff8U)

#define TIMER_IRQSTATUS_MAT_IT_FLAG_SHIFT                                                                   (0U)
#define TIMER_IRQSTATUS_MAT_IT_FLAG_MASK                                                                    (0x00000001U)

#define TIMER_IRQSTATUS_OVF_IT_FLAG_SHIFT                                                                   (1U)
#define TIMER_IRQSTATUS_OVF_IT_FLAG_MASK                                                                    (0x00000002U)

#define TIMER_IRQSTATUS_TCAR_IT_FLAG_SHIFT                                                                  (2U)
#define TIMER_IRQSTATUS_TCAR_IT_FLAG_MASK                                                                   (0x00000004U)

#define TIMER_IRQSTATUS_RESERVED_SHIFT                                                                      (3U)
#define TIMER_IRQSTATUS_RESERVED_MASK                                                                       (0xfffffff8U)

#define TIMER_IRQENABLE_SET_MAT_EN_FLAG_SHIFT                                                               (0U)
#define TIMER_IRQENABLE_SET_MAT_EN_FLAG_MASK                                                                (0x00000001U)

#define TIMER_IRQENABLE_SET_OVF_EN_FLAG_SHIFT                                                               (1U)
#define TIMER_IRQENABLE_SET_OVF_EN_FLAG_MASK                                                                (0x00000002U)

#define TIMER_IRQENABLE_SET_TCAR_EN_FLAG_SHIFT                                                              (2U)
#define TIMER_IRQENABLE_SET_TCAR_EN_FLAG_MASK                                                               (0x00000004U)

#define TIMER_IRQENABLE_SET_RESERVED_SHIFT                                                                  (3U)
#define TIMER_IRQENABLE_SET_RESERVED_MASK                                                                   (0xfffffff8U)

#define TIMER_IRQENABLE_CLR_MAT_EN_FLAG_SHIFT                                                               (0U)
#define TIMER_IRQENABLE_CLR_MAT_EN_FLAG_MASK                                                                (0x00000001U)

#define TIMER_IRQENABLE_CLR_OVF_EN_FLAG_SHIFT                                                               (1U)
#define TIMER_IRQENABLE_CLR_OVF_EN_FLAG_MASK                                                                (0x00000002U)

#define TIMER_IRQENABLE_CLR_TCAR_EN_FLAG_SHIFT                                                              (2U)
#define TIMER_IRQENABLE_CLR_TCAR_EN_FLAG_MASK                                                               (0x00000004U)

#define TIMER_IRQENABLE_CLR_RESERVED_SHIFT                                                                  (3U)
#define TIMER_IRQENABLE_CLR_RESERVED_MASK                                                                   (0xfffffff8U)

#define TIMER_IRQWAKEEN_MAT_WUP_ENA_SHIFT                                                                   (0U)
#define TIMER_IRQWAKEEN_MAT_WUP_ENA_MASK                                                                    (0x00000001U)
#define TIMER_IRQWAKEEN_MAT_WUP_ENA_MAT_WUP_ENA_VALUE_0                                                      (0U)
#define TIMER_IRQWAKEEN_MAT_WUP_ENA_MAT_WUP_ENA_VALUE_1                                                      (1U)

#define TIMER_IRQWAKEEN_OVF_WUP_ENA_SHIFT                                                                   (1U)
#define TIMER_IRQWAKEEN_OVF_WUP_ENA_MASK                                                                    (0x00000002U)
#define TIMER_IRQWAKEEN_OVF_WUP_ENA_OVF_WUP_ENA_VALUE_0                                                      (0U)
#define TIMER_IRQWAKEEN_OVF_WUP_ENA_OVF_WUP_ENA_VALUE_1                                                      (1U)

#define TIMER_IRQWAKEEN_TCAR_WUP_ENA_SHIFT                                                                  (2U)
#define TIMER_IRQWAKEEN_TCAR_WUP_ENA_MASK                                                                   (0x00000004U)
#define TIMER_IRQWAKEEN_TCAR_WUP_ENA_TCAR_WUP_ENA_VALUE_0                                                    (0U)
#define TIMER_IRQWAKEEN_TCAR_WUP_ENA_TCAR_WUP_ENA_VALUE_1                                                    (1U)

#define TIMER_IRQWAKEEN_RESERVED_SHIFT                                                                      (3U)
#define TIMER_IRQWAKEEN_RESERVED_MASK                                                                       (0xfffffff8U)

#define TIMER_TCLR_TCM_SHIFT                                                                                (8U)
#define TIMER_TCLR_TCM_MASK                                                                                 (0x00000300U)
#define TIMER_TCLR_TCM_TCM_VALUE_0X0                                                                         (0U)
#define TIMER_TCLR_TCM_TCM_VALUE_0X1                                                                         (1U)
#define TIMER_TCLR_TCM_TCM_VALUE_0X2                                                                         (2U)
#define TIMER_TCLR_TCM_TCM_VALUE_0X3                                                                         (3U)

#define TIMER_TCLR_ST_SHIFT                                                                                 (0U)
#define TIMER_TCLR_ST_MASK                                                                                  (0x00000001U)
#define TIMER_TCLR_ST_ST_VALUE_0                                                                             (0U)
#define TIMER_TCLR_ST_ST_VALUE_1                                                                             (1U)

#define TIMER_TCLR_PTV_SHIFT                                                                                (2U)
#define TIMER_TCLR_PTV_MASK                                                                                 (0x0000001cU)

#define TIMER_TCLR_CE_SHIFT                                                                                 (6U)
#define TIMER_TCLR_CE_MASK                                                                                  (0x00000040U)
#define TIMER_TCLR_CE_CE_VALUE_0                                                                             (0U)
#define TIMER_TCLR_CE_CE_VALUE_1                                                                             (1U)

#define TIMER_TCLR_AR_SHIFT                                                                                 (1U)
#define TIMER_TCLR_AR_MASK                                                                                  (0x00000002U)
#define TIMER_TCLR_AR_AR_VALUE_0                                                                             (0U)
#define TIMER_TCLR_AR_AR_VALUE_1                                                                             (1U)

#define TIMER_TCLR_RESERVED_SHIFT                                                                           (15U)
#define TIMER_TCLR_RESERVED_MASK                                                                            (0xffff8000U)

#define TIMER_TCLR_CAPT_MODE_SHIFT                                                                          (13U)
#define TIMER_TCLR_CAPT_MODE_MASK                                                                           (0x00002000U)
#define TIMER_TCLR_CAPT_MODE_CAPT_MODE_VALUE_0                                                               (0U)
#define TIMER_TCLR_CAPT_MODE_CAPT_MODE_VALUE_1                                                               (1U)

#define TIMER_TCLR_TRG_SHIFT                                                                                (10U)
#define TIMER_TCLR_TRG_MASK                                                                                 (0x00000c00U)
#define TIMER_TCLR_TRG_TRG_VALUE_0X0                                                                         (0U)
#define TIMER_TCLR_TRG_TRG_VALUE_0X1                                                                         (1U)
#define TIMER_TCLR_TRG_TRG_VALUE_0X2                                                                         (2U)
#define TIMER_TCLR_TRG_TRG_VALUE_0X3                                                                         (3U)

#define TIMER_TCLR_PT_SHIFT                                                                                 (12U)
#define TIMER_TCLR_PT_MASK                                                                                  (0x00001000U)
#define TIMER_TCLR_PT_PT_VALUE_0                                                                             (0U)
#define TIMER_TCLR_PT_PT_VALUE_1                                                                             (1U)

#define TIMER_TCLR_SCPWM_SHIFT                                                                              (7U)
#define TIMER_TCLR_SCPWM_MASK                                                                               (0x00000080U)
#define TIMER_TCLR_SCPWM_SCPWM_VALUE_0                                                                       (0U)
#define TIMER_TCLR_SCPWM_SCPWM_VALUE_1                                                                       (1U)

#define TIMER_TCLR_PRE_SHIFT                                                                                (5U)
#define TIMER_TCLR_PRE_MASK                                                                                 (0x00000020U)
#define TIMER_TCLR_PRE_PRE_VALUE_0                                                                           (0U)
#define TIMER_TCLR_PRE_PRE_VALUE_1                                                                           (1U)

#define TIMER_TCLR_GPO_CFG_SHIFT                                                                            (14U)
#define TIMER_TCLR_GPO_CFG_MASK                                                                             (0x00004000U)
#define TIMER_TCLR_GPO_CFG_GPO_CFG_0                                                                         (0U)
#define TIMER_TCLR_GPO_CFG_GPO_CFG_1                                                                         (1U)

#define TIMER_TCRR_TIMER_COUNTER_SHIFT                                                                      (0U)
#define TIMER_TCRR_TIMER_COUNTER_MASK                                                                       (0xffffffffU)

#define TIMER_TLDR_LOAD_VALUE_SHIFT                                                                         (0U)
#define TIMER_TLDR_LOAD_VALUE_MASK                                                                          (0xffffffffU)

#define TIMER_TTGR_TTGR_VALUE_SHIFT                                                                         (0U)
#define TIMER_TTGR_TTGR_VALUE_MASK                                                                          (0xffffffffU)

#define TIMER_TWPS_W_PEND_TMAR_SHIFT                                                                        (4U)
#define TIMER_TWPS_W_PEND_TMAR_MASK                                                                         (0x00000010U)

#define TIMER_TWPS_W_PEND_TCRR_SHIFT                                                                        (1U)
#define TIMER_TWPS_W_PEND_TCRR_MASK                                                                         (0x00000002U)

#define TIMER_TWPS_W_PEND_TTGR_SHIFT                                                                        (3U)
#define TIMER_TWPS_W_PEND_TTGR_MASK                                                                         (0x00000008U)

#define TIMER_TWPS_W_PEND_TCLR_SHIFT                                                                        (0U)
#define TIMER_TWPS_W_PEND_TCLR_MASK                                                                         (0x00000001U)

#define TIMER_TWPS_RESERVED_SHIFT                                                                           (5U)
#define TIMER_TWPS_RESERVED_MASK                                                                            (0xffffffe0U)

#define TIMER_TWPS_W_PEND_TLDR_SHIFT                                                                        (2U)
#define TIMER_TWPS_W_PEND_TLDR_MASK                                                                         (0x00000004U)

#define TIMER_TMAR_COMPARE_VALUE_SHIFT                                                                      (0U)
#define TIMER_TMAR_COMPARE_VALUE_MASK                                                                       (0xffffffffU)

#define TIMER_TCAR1_CAPTURE_VALUE1_SHIFT                                                                    (0U)
#define TIMER_TCAR1_CAPTURE_VALUE1_MASK                                                                     (0xffffffffU)

#define TIMER_TSICR_RESERVED_28_SHIFT                                                                       (4U)
#define TIMER_TSICR_RESERVED_28_MASK                                                                        (0xfffffff0U)

#define TIMER_TSICR_POSTED_SHIFT                                                                            (2U)
#define TIMER_TSICR_POSTED_MASK                                                                             (0x00000004U)
#define TIMER_TSICR_POSTED_POSTED_VALUE_0                                                                    (0U)
#define TIMER_TSICR_POSTED_POSTED_VALUE_1                                                                    (1U)

#define TIMER_TSICR_RESERVED_1_SHIFT                                                                        (0U)
#define TIMER_TSICR_RESERVED_1_MASK                                                                         (0x00000001U)

#define TIMER_TSICR_SFT_SHIFT                                                                               (1U)
#define TIMER_TSICR_SFT_MASK                                                                                (0x00000002U)
#define TIMER_TSICR_SFT_SFT_0                                                                                (0U)
#define TIMER_TSICR_SFT_SFT_1                                                                                (1U)

#define TIMER_TSICR_READ_MODE_SHIFT                                                                         (3U)
#define TIMER_TSICR_READ_MODE_MASK                                                                          (0x00000008U)
#define TIMER_TSICR_READ_MODE_READ_MODE_VALUE_0                                                              (0U)
#define TIMER_TSICR_READ_MODE_READ_MODE_VALUE_1                                                              (1U)

#define TIMER_TCAR2_CAPTURE_VALUE2_SHIFT                                                                    (0U)
#define TIMER_TCAR2_CAPTURE_VALUE2_MASK                                                                     (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_TIMER_H_ */

