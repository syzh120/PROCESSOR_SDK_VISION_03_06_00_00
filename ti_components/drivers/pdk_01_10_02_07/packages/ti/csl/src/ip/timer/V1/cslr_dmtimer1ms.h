/********************************************************************
 * Copyright (C) 2013-2014 Texas Instruments Incorporated.
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
#ifndef CSLR_DMTIMER1MS_H_
#define CSLR_DMTIMER1MS_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>


/**************************************************************************
* Register Overlay Structure for __ALL__
**************************************************************************/
typedef struct {
    volatile Uint32 TIDR;
    volatile Uint8  RSVD0[12];
    volatile Uint32 TIOCP_CFG;
    volatile Uint8  RSVD1[12];
    volatile Uint32 IRQ_EOI;
    volatile Uint32 IRQSTATUS_RAW;
    volatile Uint32 IRQSTATUS;
    volatile Uint32 IRQSTATUS_SET;
    volatile Uint32 IRQSTATUS_CLR;
    volatile Uint32 IRQWAKEEN;
    volatile Uint32 TCLR;
    volatile Uint32 TCRR;
    volatile Uint32 TLDR;
    volatile Uint32 TTGR;
    volatile Uint32 TWPS;
    volatile Uint32 TMAR;
    volatile Uint32 TCAR1;
    volatile Uint32 TSICR;
    volatile Uint32 TCAR2;
    volatile Uint32 TPIR;
    volatile Uint32 TNIR;
    volatile Uint32 TCVR;
    volatile Uint32 TOCR;
    volatile Uint32 TOWR;
} CSL_Dmtimer1msRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

/* This read only register contains the revision number of the module. A write 
 * to this register has no effect. This Register is used by software to track 
 * features, bugs, and compatibility. */
#define CSL_DMTIMER1MS_TIDR                                     (0x0U)

/* This register controls the various parameters of the OCP interface */
#define CSL_DMTIMER1MS_TIOCP_CFG                                (0x10U)

/* Software End-Of-Interrupt: Allows the generation of further pulses on the 
 * interrupt line, if an new interrupt event is pending, when using the pulsed 
 * output. Unused when using the level interrupt line (depending on module 
 * integration). */
#define CSL_DMTIMER1MS_IRQ_EOI                                  (0x20U)

/* Component interrupt request status. Check the corresponding secondary 
 * status register. Raw status is set even if event is not enabled. Write 1 to 
 * set the (raw) status, mostly for debug. */
#define CSL_DMTIMER1MS_IRQSTATUS_RAW                            (0x24U)

/* Component interrupt request status. Check the corresponding secondary 
 * status register.Enabled status isn't set unless event is enabled.Write 1 to 
 * clear the status after interrupt has been serviced (raw status gets 
 * cleared, i.e. even if not enabled). */
#define CSL_DMTIMER1MS_IRQSTATUS                                (0x28U)

/* Component interrupt request enable Write 1 to set (enable interrupt). 
 * Readout equal to corresponding _CLR register. */
#define CSL_DMTIMER1MS_IRQSTATUS_SET                            (0x2CU)

/* Component interrupt request enable Write 1 to clear (disable interrupt). 
 * Readout equal to corresponding _SET register. */
#define CSL_DMTIMER1MS_IRQSTATUS_CLR                            (0x30U)

/* Wakeup-enabled events taking place when module is idle shall generate an 
 * asynchronous wakeup. */
#define CSL_DMTIMER1MS_IRQWAKEEN                                (0x34U)

/* This register controls optional features specific to the timer 
 * functionality */
#define CSL_DMTIMER1MS_TCLR                                     (0x38U)

/* This register holds the value of the internal counter */
#define CSL_DMTIMER1MS_TCRR                                     (0x3CU)

/* This register holds the timer's load value */
#define CSL_DMTIMER1MS_TLDR                                     (0x40U)

/* This register triggers a counter reload of timer by writing any value in 
 * it. */
#define CSL_DMTIMER1MS_TTGR                                     (0x44U)

/* This register contains the write posting bits for all writ-able functional 
 * registers */
#define CSL_DMTIMER1MS_TWPS                                     (0x48U)

/* This register holds the match value to be compared with the counter's value */
#define CSL_DMTIMER1MS_TMAR                                     (0x4CU)

/* This register holds the value of the first counter register capture */
#define CSL_DMTIMER1MS_TCAR1                                    (0x50U)

/* Timer Synchronous Interface Control Register */
#define CSL_DMTIMER1MS_TSICR                                    (0x54U)

/* This register holds the value of the second counter register capture */
#define CSL_DMTIMER1MS_TCAR2                                    (0x58U)

/* This register is used for 1ms tick generation. The TPIR register holds the 
 * value of the positive increment. The value of this register is added with 
 * the value of the TCVR to define whether next value loaded in TCRR will be 
 * the sub-period value or the over-period value. */
#define CSL_DMTIMER1MS_TPIR                                     (0x5CU)

/* This register is used for 1ms tick generation. The TNIR register holds the 
 * value of the negative increment. The value of this register is added with 
 * the value of the TCVR to define whether next value loaded in TCRR will be 
 * the sub-period value or the over-period value. */
#define CSL_DMTIMER1MS_TNIR                                     (0x60U)

/* This register is used for 1ms tick generation. The TCVR register defines 
 * whether next value loaded in TCRR will be the sub-period value or the 
 * over-period value. */
#define CSL_DMTIMER1MS_TCVR                                     (0x64U)

/* This register is used to mask the tick interrupt for a selected number of 
 * ticks. */
#define CSL_DMTIMER1MS_TOCR                                     (0x68U)

/* This register holds the number of masked overflow interrupts. */
#define CSL_DMTIMER1MS_TOWR                                     (0x6CU)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* TIDR */

#define CSL_DMTIMER1MS_TIDR_X_MAJOR_MASK                        (0x00000700U)
#define CSL_DMTIMER1MS_TIDR_X_MAJOR_SHIFT                       (8U)
#define CSL_DMTIMER1MS_TIDR_X_MAJOR_RESETVAL                    (0x00000001U)
#define CSL_DMTIMER1MS_TIDR_X_MAJOR_MAX                         (0x00000007U)

#define CSL_DMTIMER1MS_TIDR_Y_MINOR_MASK                        (0x0000003FU)
#define CSL_DMTIMER1MS_TIDR_Y_MINOR_SHIFT                       (0U)
#define CSL_DMTIMER1MS_TIDR_Y_MINOR_RESETVAL                    (0x00000000U)
#define CSL_DMTIMER1MS_TIDR_Y_MINOR_MAX                         (0x0000003fU)

#define CSL_DMTIMER1MS_TIDR_CUSTOM_MASK                         (0x000000C0U)
#define CSL_DMTIMER1MS_TIDR_CUSTOM_SHIFT                        (6U)
#define CSL_DMTIMER1MS_TIDR_CUSTOM_RESETVAL                     (0x00000000U)
#define CSL_DMTIMER1MS_TIDR_CUSTOM_MAX                          (0x00000003U)

#define CSL_DMTIMER1MS_TIDR_R_RTL_MASK                          (0x0000F800U)
#define CSL_DMTIMER1MS_TIDR_R_RTL_SHIFT                         (11U)
#define CSL_DMTIMER1MS_TIDR_R_RTL_RESETVAL                      (0x00000000U)
#define CSL_DMTIMER1MS_TIDR_R_RTL_MAX                           (0x0000001fU)

#define CSL_DMTIMER1MS_TIDR_FUNC_MASK                           (0x0FFF0000U)
#define CSL_DMTIMER1MS_TIDR_FUNC_SHIFT                          (16U)
#define CSL_DMTIMER1MS_TIDR_FUNC_RESETVAL                       (0x00000000U)
#define CSL_DMTIMER1MS_TIDR_FUNC_MAX                            (0x00000fffU)

#define CSL_DMTIMER1MS_TIDR_SCHEME_MASK                         (0xC0000000U)
#define CSL_DMTIMER1MS_TIDR_SCHEME_SHIFT                        (30U)
#define CSL_DMTIMER1MS_TIDR_SCHEME_RESETVAL                     (0x00000001U)
#define CSL_DMTIMER1MS_TIDR_SCHEME_SCHEME_VALUE_0               (0x00000000U)
#define CSL_DMTIMER1MS_TIDR_SCHEME_SCHEME_VALUE_1               (0x00000001U)

#define CSL_DMTIMER1MS_TIDR_RESETVAL                            (0x50000100U)

/* TIOCP_CFG */

#define CSL_DMTIMER1MS_TIOCP_CFG_EMUFREE_MASK                   (0x00000002U)
#define CSL_DMTIMER1MS_TIOCP_CFG_EMUFREE_SHIFT                  (1U)
#define CSL_DMTIMER1MS_TIOCP_CFG_EMUFREE_RESETVAL               (0x00000000U)
#define CSL_DMTIMER1MS_TIOCP_CFG_EMUFREE_TIMER_FROZEN           (0x00000000U)
#define CSL_DMTIMER1MS_TIOCP_CFG_EMUFREE_TIMER_FREE             (0x00000001U)

#define CSL_DMTIMER1MS_TIOCP_CFG_IDLEMODE_MASK                  (0x0000000CU)
#define CSL_DMTIMER1MS_TIOCP_CFG_IDLEMODE_SHIFT                 (2U)
#define CSL_DMTIMER1MS_TIOCP_CFG_IDLEMODE_RESETVAL              (0x00000002U)
#define CSL_DMTIMER1MS_TIOCP_CFG_IDLEMODE_IDLE_MODE_0X0         (0x00000000U)
#define CSL_DMTIMER1MS_TIOCP_CFG_IDLEMODE_IDLE_MODE_0X1         (0x00000001U)
#define CSL_DMTIMER1MS_TIOCP_CFG_IDLEMODE_IDLE_MODE_0X2         (0x00000002U)
#define CSL_DMTIMER1MS_TIOCP_CFG_IDLEMODE_IDLE_MODE_0X3         (0x00000003U)

#define CSL_DMTIMER1MS_TIOCP_CFG_SOFTRESET_MASK                 (0x00000001U)
#define CSL_DMTIMER1MS_TIOCP_CFG_SOFTRESET_SHIFT                (0U)
#define CSL_DMTIMER1MS_TIOCP_CFG_SOFTRESET_RESETVAL             (0x00000000U)
#define CSL_DMTIMER1MS_TIOCP_CFG_SOFTRESET_SOFTRESET_VALUE_0    (0x00000000U)
#define CSL_DMTIMER1MS_TIOCP_CFG_SOFTRESET_SOFTRESET_VALUE_1    (0x00000001U)

#define CSL_DMTIMER1MS_TIOCP_CFG_RESETVAL                       (0x00000008U)

/* IRQ_EOI */

#define CSL_DMTIMER1MS_IRQ_EOI_LINE_NUMBER_MASK                 (0x00000001U)
#define CSL_DMTIMER1MS_IRQ_EOI_LINE_NUMBER_SHIFT                (0U)
#define CSL_DMTIMER1MS_IRQ_EOI_LINE_NUMBER_RESETVAL             (0x00000000U)
#define CSL_DMTIMER1MS_IRQ_EOI_LINE_NUMBER_MAX                  (0x00000001U)

#define CSL_DMTIMER1MS_IRQ_EOI_RESETVAL                         (0x00000000U)

/* IRQSTATUS_RAW */

#define CSL_DMTIMER1MS_IRQSTATUS_RAW_MAT_IT_FLAG_MASK           (0x00000001U)
#define CSL_DMTIMER1MS_IRQSTATUS_RAW_MAT_IT_FLAG_SHIFT          (0U)
#define CSL_DMTIMER1MS_IRQSTATUS_RAW_MAT_IT_FLAG_RESETVAL       (0x00000000U)
#define CSL_DMTIMER1MS_IRQSTATUS_RAW_MAT_IT_FLAG_MAX            (0x00000001U)

#define CSL_DMTIMER1MS_IRQSTATUS_RAW_OVF_IT_FLAG_MASK           (0x00000002U)
#define CSL_DMTIMER1MS_IRQSTATUS_RAW_OVF_IT_FLAG_SHIFT          (1U)
#define CSL_DMTIMER1MS_IRQSTATUS_RAW_OVF_IT_FLAG_RESETVAL       (0x00000000U)
#define CSL_DMTIMER1MS_IRQSTATUS_RAW_OVF_IT_FLAG_MAX            (0x00000001U)

#define CSL_DMTIMER1MS_IRQSTATUS_RAW_TCAR_IT_FLAG_MASK          (0x00000004U)
#define CSL_DMTIMER1MS_IRQSTATUS_RAW_TCAR_IT_FLAG_SHIFT         (2U)
#define CSL_DMTIMER1MS_IRQSTATUS_RAW_TCAR_IT_FLAG_RESETVAL      (0x00000000U)
#define CSL_DMTIMER1MS_IRQSTATUS_RAW_TCAR_IT_FLAG_MAX           (0x00000001U)

#define CSL_DMTIMER1MS_IRQSTATUS_RAW_RESETVAL                   (0x00000000U)

/* IRQSTATUS */

#define CSL_DMTIMER1MS_IRQSTATUS_MAT_IT_FLAG_MASK               (0x00000001U)
#define CSL_DMTIMER1MS_IRQSTATUS_MAT_IT_FLAG_SHIFT              (0U)
#define CSL_DMTIMER1MS_IRQSTATUS_MAT_IT_FLAG_RESETVAL           (0x00000000U)
#define CSL_DMTIMER1MS_IRQSTATUS_MAT_IT_FLAG_MAX                (0x00000001U)

#define CSL_DMTIMER1MS_IRQSTATUS_OVF_IT_FLAG_MASK               (0x00000002U)
#define CSL_DMTIMER1MS_IRQSTATUS_OVF_IT_FLAG_SHIFT              (1U)
#define CSL_DMTIMER1MS_IRQSTATUS_OVF_IT_FLAG_RESETVAL           (0x00000000U)
#define CSL_DMTIMER1MS_IRQSTATUS_OVF_IT_FLAG_MAX                (0x00000001U)

#define CSL_DMTIMER1MS_IRQSTATUS_TCAR_IT_FLAG_MASK              (0x00000004U)
#define CSL_DMTIMER1MS_IRQSTATUS_TCAR_IT_FLAG_SHIFT             (2U)
#define CSL_DMTIMER1MS_IRQSTATUS_TCAR_IT_FLAG_RESETVAL          (0x00000000U)
#define CSL_DMTIMER1MS_IRQSTATUS_TCAR_IT_FLAG_MAX               (0x00000001U)

#define CSL_DMTIMER1MS_IRQSTATUS_RESETVAL                       (0x00000000U)

/* IRQSTATUS_SET */

#define CSL_DMTIMER1MS_IRQSTATUS_SET_MAT_EN_FLAG_MASK           (0x00000001U)
#define CSL_DMTIMER1MS_IRQSTATUS_SET_MAT_EN_FLAG_SHIFT          (0U)
#define CSL_DMTIMER1MS_IRQSTATUS_SET_MAT_EN_FLAG_RESETVAL       (0x00000000U)
#define CSL_DMTIMER1MS_IRQSTATUS_SET_MAT_EN_FLAG_MAX            (0x00000001U)

#define CSL_DMTIMER1MS_IRQSTATUS_SET_OVF_EN_FLAG_MASK           (0x00000002U)
#define CSL_DMTIMER1MS_IRQSTATUS_SET_OVF_EN_FLAG_SHIFT          (1U)
#define CSL_DMTIMER1MS_IRQSTATUS_SET_OVF_EN_FLAG_RESETVAL       (0x00000000U)
#define CSL_DMTIMER1MS_IRQSTATUS_SET_OVF_EN_FLAG_MAX            (0x00000001U)

#define CSL_DMTIMER1MS_IRQSTATUS_SET_TCAR_EN_FLAG_MASK          (0x00000004U)
#define CSL_DMTIMER1MS_IRQSTATUS_SET_TCAR_EN_FLAG_SHIFT         (2U)
#define CSL_DMTIMER1MS_IRQSTATUS_SET_TCAR_EN_FLAG_RESETVAL      (0x00000000U)
#define CSL_DMTIMER1MS_IRQSTATUS_SET_TCAR_EN_FLAG_MAX           (0x00000001U)

#define CSL_DMTIMER1MS_IRQSTATUS_SET_RESETVAL                   (0x00000000U)

/* IRQSTATUS_CLR */

#define CSL_DMTIMER1MS_IRQSTATUS_CLR_MAT_EN_FLAG_MASK           (0x00000001U)
#define CSL_DMTIMER1MS_IRQSTATUS_CLR_MAT_EN_FLAG_SHIFT          (0U)
#define CSL_DMTIMER1MS_IRQSTATUS_CLR_MAT_EN_FLAG_RESETVAL       (0x00000000U)
#define CSL_DMTIMER1MS_IRQSTATUS_CLR_MAT_EN_FLAG_MAX            (0x00000001U)

#define CSL_DMTIMER1MS_IRQSTATUS_CLR_OVF_EN_FLAG_MASK           (0x00000002U)
#define CSL_DMTIMER1MS_IRQSTATUS_CLR_OVF_EN_FLAG_SHIFT          (1U)
#define CSL_DMTIMER1MS_IRQSTATUS_CLR_OVF_EN_FLAG_RESETVAL       (0x00000000U)
#define CSL_DMTIMER1MS_IRQSTATUS_CLR_OVF_EN_FLAG_MAX            (0x00000001U)

#define CSL_DMTIMER1MS_IRQSTATUS_CLR_TCAR_EN_FLAG_MASK          (0x00000004U)
#define CSL_DMTIMER1MS_IRQSTATUS_CLR_TCAR_EN_FLAG_SHIFT         (2U)
#define CSL_DMTIMER1MS_IRQSTATUS_CLR_TCAR_EN_FLAG_RESETVAL      (0x00000000U)
#define CSL_DMTIMER1MS_IRQSTATUS_CLR_TCAR_EN_FLAG_MAX           (0x00000001U)

#define CSL_DMTIMER1MS_IRQSTATUS_CLR_RESETVAL                   (0x00000000U)

/* IRQWAKEEN */

#define CSL_DMTIMER1MS_IRQWAKEEN_MAT_WUP_ENA_MASK               (0x00000001U)
#define CSL_DMTIMER1MS_IRQWAKEEN_MAT_WUP_ENA_SHIFT              (0U)
#define CSL_DMTIMER1MS_IRQWAKEEN_MAT_WUP_ENA_RESETVAL           (0x00000000U)
#define CSL_DMTIMER1MS_IRQWAKEEN_MAT_WUP_ENA_MAT_WUP_ENA_VALUE_0  (0x00000000U)
#define CSL_DMTIMER1MS_IRQWAKEEN_MAT_WUP_ENA_MAT_WUP_ENA_VALUE_1  (0x00000001U)

#define CSL_DMTIMER1MS_IRQWAKEEN_OVF_WUP_ENA_MASK               (0x00000002U)
#define CSL_DMTIMER1MS_IRQWAKEEN_OVF_WUP_ENA_SHIFT              (1U)
#define CSL_DMTIMER1MS_IRQWAKEEN_OVF_WUP_ENA_RESETVAL           (0x00000000U)
#define CSL_DMTIMER1MS_IRQWAKEEN_OVF_WUP_ENA_OVF_WUP_ENA_VALUE_0  (0x00000000U)
#define CSL_DMTIMER1MS_IRQWAKEEN_OVF_WUP_ENA_OVF_WUP_ENA_VALUE_1  (0x00000001U)

#define CSL_DMTIMER1MS_IRQWAKEEN_TCAR_WUP_ENA_MASK              (0x00000004U)
#define CSL_DMTIMER1MS_IRQWAKEEN_TCAR_WUP_ENA_SHIFT             (2U)
#define CSL_DMTIMER1MS_IRQWAKEEN_TCAR_WUP_ENA_RESETVAL          (0x00000000U)
#define CSL_DMTIMER1MS_IRQWAKEEN_TCAR_WUP_ENA_TCAR_WUP_ENA_VALUE_0  (0x00000000U)
#define CSL_DMTIMER1MS_IRQWAKEEN_TCAR_WUP_ENA_TCAR_WUP_ENA_VALUE_1  (0x00000001U)

#define CSL_DMTIMER1MS_IRQWAKEEN_RESETVAL                       (0x00000000U)

/* TCLR */

#define CSL_DMTIMER1MS_TCLR_TCM_MASK                            (0x00000300U)
#define CSL_DMTIMER1MS_TCLR_TCM_SHIFT                           (8U)
#define CSL_DMTIMER1MS_TCLR_TCM_RESETVAL                        (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_TCM_NO_EDGE                         (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_TCM_RISE_EDGE                       (0x00000001U)
#define CSL_DMTIMER1MS_TCLR_TCM_FALL_EDGE                       (0x00000002U)
#define CSL_DMTIMER1MS_TCLR_TCM_BOTH_EDGES                      (0x00000003U)

#define CSL_DMTIMER1MS_TCLR_ST_MASK                             (0x00000001U)
#define CSL_DMTIMER1MS_TCLR_ST_SHIFT                            (0U)
#define CSL_DMTIMER1MS_TCLR_ST_RESETVAL                         (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_ST_CNT_STOP                         (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_ST_CNT_START                        (0x00000001U)

#define CSL_DMTIMER1MS_TCLR_PTV_MASK                            (0x0000001CU)
#define CSL_DMTIMER1MS_TCLR_PTV_SHIFT                           (2U)
#define CSL_DMTIMER1MS_TCLR_PTV_RESETVAL                        (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_PTV_PTV                             (0x00000000U)

#define CSL_DMTIMER1MS_TCLR_CE_MASK                             (0x00000040U)
#define CSL_DMTIMER1MS_TCLR_CE_SHIFT                            (6U)
#define CSL_DMTIMER1MS_TCLR_CE_RESETVAL                         (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_CE_DSB_CMP                          (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_CE_ENB_CMP                          (0x00000001U)

#define CSL_DMTIMER1MS_TCLR_AR_MASK                             (0x00000002U)
#define CSL_DMTIMER1MS_TCLR_AR_SHIFT                            (1U)
#define CSL_DMTIMER1MS_TCLR_AR_RESETVAL                         (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_AR_ONE_SHOT                         (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_AR_AUTO_REL                         (0x00000001U)

#define CSL_DMTIMER1MS_TCLR_CAPT_MODE_MASK                      (0x00002000U)
#define CSL_DMTIMER1MS_TCLR_CAPT_MODE_SHIFT                     (13U)
#define CSL_DMTIMER1MS_TCLR_CAPT_MODE_RESETVAL                  (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_CAPT_MODE_FIRST_CAPT                (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_CAPT_MODE_SEC_CAPT                  (0x00000001U)

#define CSL_DMTIMER1MS_TCLR_TRG_MASK                            (0x00000C00U)
#define CSL_DMTIMER1MS_TCLR_TRG_SHIFT                           (10U)
#define CSL_DMTIMER1MS_TCLR_TRG_RESETVAL                        (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_TRG_NO_TRG                          (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_TRG_OVF_TRG                         (0x00000001U)
#define CSL_DMTIMER1MS_TCLR_TRG_OVF_MAT_TRG                     (0x00000002U)
#define CSL_DMTIMER1MS_TCLR_TRG_RESERVED                        (0x00000003U)

#define CSL_DMTIMER1MS_TCLR_PT_MASK                             (0x00001000U)
#define CSL_DMTIMER1MS_TCLR_PT_SHIFT                            (12U)
#define CSL_DMTIMER1MS_TCLR_PT_RESETVAL                         (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_PT_PULSE                            (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_PT_TOGGLE                           (0x00000001U)

#define CSL_DMTIMER1MS_TCLR_SCPWM_MASK                          (0x00000080U)
#define CSL_DMTIMER1MS_TCLR_SCPWM_SHIFT                         (7U)
#define CSL_DMTIMER1MS_TCLR_SCPWM_RESETVAL                      (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_SCPWM_DEF_LOW                       (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_SCPWM_DEF_HIGH                      (0x00000001U)

#define CSL_DMTIMER1MS_TCLR_PRE_MASK                            (0x00000020U)
#define CSL_DMTIMER1MS_TCLR_PRE_SHIFT                           (5U)
#define CSL_DMTIMER1MS_TCLR_PRE_RESETVAL                        (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_PRE_NO_PRESCAL                      (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_PRE_PRESCAL_ON                      (0x00000001U)

#define CSL_DMTIMER1MS_TCLR_GPO_CFG_MASK                        (0x00004000U)
#define CSL_DMTIMER1MS_TCLR_GPO_CFG_SHIFT                       (14U)
#define CSL_DMTIMER1MS_TCLR_GPO_CFG_RESETVAL                    (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_GPO_CFG_GPO_CFG_0                   (0x00000000U)
#define CSL_DMTIMER1MS_TCLR_GPO_CFG_GPO_CFG_1                   (0x00000001U)

#define CSL_DMTIMER1MS_TCLR_RESETVAL                            (0x00000000U)

/* TCRR */

#define CSL_DMTIMER1MS_TCRR_TIMER_COUNTER_MASK                  (0xFFFFFFFFU)
#define CSL_DMTIMER1MS_TCRR_TIMER_COUNTER_SHIFT                 (0U)
#define CSL_DMTIMER1MS_TCRR_TIMER_COUNTER_RESETVAL              (0x00000000U)
#define CSL_DMTIMER1MS_TCRR_TIMER_COUNTER_MAX                   (0xffffffffU)

#define CSL_DMTIMER1MS_TCRR_RESETVAL                            (0x00000000U)

/* TLDR */

#define CSL_DMTIMER1MS_TLDR_LOAD_VALUE_MASK                     (0xFFFFFFFFU)
#define CSL_DMTIMER1MS_TLDR_LOAD_VALUE_SHIFT                    (0U)
#define CSL_DMTIMER1MS_TLDR_LOAD_VALUE_RESETVAL                 (0x00000000U)
#define CSL_DMTIMER1MS_TLDR_LOAD_VALUE_MAX                      (0xffffffffU)

#define CSL_DMTIMER1MS_TLDR_RESETVAL                            (0x00000000U)

/* TTGR */

#define CSL_DMTIMER1MS_TTGR_TTGR_VALUE_MASK                     (0xFFFFFFFFU)
#define CSL_DMTIMER1MS_TTGR_TTGR_VALUE_SHIFT                    (0U)
#define CSL_DMTIMER1MS_TTGR_TTGR_VALUE_RESETVAL                 (0xffffffffU)
#define CSL_DMTIMER1MS_TTGR_TTGR_VALUE_MAX                      (0xffffffffU)

#define CSL_DMTIMER1MS_TTGR_RESETVAL                            (0xffffffffU)

/* TWPS */

#define CSL_DMTIMER1MS_TWPS_W_PEND_TMAR_MASK                    (0x00000010U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TMAR_SHIFT                   (4U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TMAR_RESETVAL                (0x00000000U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TMAR_MAR_NPEND               (0x00000000U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TMAR_MAR_PEND                (0x00000001U)

#define CSL_DMTIMER1MS_TWPS_W_PEND_TCRR_MASK                    (0x00000002U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TCRR_SHIFT                   (1U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TCRR_RESETVAL                (0x00000000U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TCRR_CRR_NPEND               (0x00000000U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TCRR_CRR_PEND                (0x00000001U)

#define CSL_DMTIMER1MS_TWPS_W_PEND_TTGR_MASK                    (0x00000008U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TTGR_SHIFT                   (3U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TTGR_RESETVAL                (0x00000000U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TTGR_TGR_NPEND               (0x00000000U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TTGR_TGR_PEND                (0x00000001U)

#define CSL_DMTIMER1MS_TWPS_W_PEND_TCLR_MASK                    (0x00000001U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TCLR_SHIFT                   (0U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TCLR_RESETVAL                (0x00000000U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TCLR_CLR_NPEND               (0x00000000U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TCLR_CLR_PEND                (0x00000001U)

#define CSL_DMTIMER1MS_TWPS_W_PEND_TLDR_MASK                    (0x00000004U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TLDR_SHIFT                   (2U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TLDR_RESETVAL                (0x00000000U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TLDR_LDR_NPEND               (0x00000000U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TLDR_LDR_PEND                (0x00000001U)

#define CSL_DMTIMER1MS_TWPS_W_PEND_TPIR_MASK                    (0x00000020U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TPIR_SHIFT                   (5U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TPIR_RESETVAL                (0x00000000U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TPIR_PIR_NPEND               (0x00000000U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TPIR_PIR_PEND                (0x00000001U)

#define CSL_DMTIMER1MS_TWPS_W_PEND_TNIR_MASK                    (0x00000040U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TNIR_SHIFT                   (6U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TNIR_RESETVAL                (0x00000000U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TNIR_NIR_NPEND               (0x00000000U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TNIR_NIR_PEND                (0x00000001U)

#define CSL_DMTIMER1MS_TWPS_W_PEND_TCVR_MASK                    (0x00000080U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TCVR_SHIFT                   (7U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TCVR_RESETVAL                (0x00000000U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TCVR_CVR_NPEND               (0x00000000U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TCVR_CVR_PEND                (0x00000001U)

#define CSL_DMTIMER1MS_TWPS_W_PEND_TOCR_MASK                    (0x00000100U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TOCR_SHIFT                   (8U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TOCR_RESETVAL                (0x00000000U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TOCR_OCR_NPEND               (0x00000000U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TOCR_OCR_PEND                (0x00000001U)

#define CSL_DMTIMER1MS_TWPS_W_PEND_TOWR_MASK                    (0x00000200U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TOWR_SHIFT                   (9U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TOWR_RESETVAL                (0x00000000U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TOWR_OWR_NPEND               (0x00000000U)
#define CSL_DMTIMER1MS_TWPS_W_PEND_TOWR_OWR_PEND                (0x00000001U)

#define CSL_DMTIMER1MS_TWPS_RESETVAL                            (0x00000000U)

/* TMAR */

#define CSL_DMTIMER1MS_TMAR_COMPARE_VALUE_MASK                  (0xFFFFFFFFU)
#define CSL_DMTIMER1MS_TMAR_COMPARE_VALUE_SHIFT                 (0U)
#define CSL_DMTIMER1MS_TMAR_COMPARE_VALUE_RESETVAL              (0x00000000U)
#define CSL_DMTIMER1MS_TMAR_COMPARE_VALUE_MAX                   (0xffffffffU)

#define CSL_DMTIMER1MS_TMAR_RESETVAL                            (0x00000000U)

/* TCAR1 */

#define CSL_DMTIMER1MS_TCAR1_CAPTURE_VALUE1_MASK                (0xFFFFFFFFU)
#define CSL_DMTIMER1MS_TCAR1_CAPTURE_VALUE1_SHIFT               (0U)
#define CSL_DMTIMER1MS_TCAR1_CAPTURE_VALUE1_RESETVAL            (0x00000000U)
#define CSL_DMTIMER1MS_TCAR1_CAPTURE_VALUE1_MAX                 (0xffffffffU)

#define CSL_DMTIMER1MS_TCAR1_RESETVAL                           (0x00000000U)

/* TSICR */

#define CSL_DMTIMER1MS_TSICR_POSTED_MASK                        (0x00000004U)
#define CSL_DMTIMER1MS_TSICR_POSTED_SHIFT                       (2U)
#define CSL_DMTIMER1MS_TSICR_POSTED_RESETVAL                    (0x00000000U)
#define CSL_DMTIMER1MS_TSICR_POSTED_POSTED_VALUE_0              (0x00000000U)
#define CSL_DMTIMER1MS_TSICR_POSTED_POSTED_VALUE_1              (0x00000001U)

#define CSL_DMTIMER1MS_TSICR_SFT_MASK                           (0x00000002U)
#define CSL_DMTIMER1MS_TSICR_SFT_SHIFT                          (1U)
#define CSL_DMTIMER1MS_TSICR_SFT_RESETVAL                       (0x00000000U)
#define CSL_DMTIMER1MS_TSICR_SFT_SFT_0                          (0x00000000U)
#define CSL_DMTIMER1MS_TSICR_SFT_SFT_1                          (0x00000001U)

#define CSL_DMTIMER1MS_TSICR_READ_MODE_MASK                     (0x00000008U)
#define CSL_DMTIMER1MS_TSICR_READ_MODE_SHIFT                    (3U)
#define CSL_DMTIMER1MS_TSICR_READ_MODE_RESETVAL                 (0x00000000U)
#define CSL_DMTIMER1MS_TSICR_READ_MODE_READ_MODE_VALUE_0        (0x00000000U)
#define CSL_DMTIMER1MS_TSICR_READ_MODE_READ_MODE_VALUE_1        (0x00000001U)

#define CSL_DMTIMER1MS_TSICR_RESETVAL                           (0x00000000U)

/* TCAR2 */

#define CSL_DMTIMER1MS_TCAR2_CAPTURE_VALUE2_MASK                (0xFFFFFFFFU)
#define CSL_DMTIMER1MS_TCAR2_CAPTURE_VALUE2_SHIFT               (0U)
#define CSL_DMTIMER1MS_TCAR2_CAPTURE_VALUE2_RESETVAL            (0x00000000U)
#define CSL_DMTIMER1MS_TCAR2_CAPTURE_VALUE2_MAX                 (0xffffffffU)

#define CSL_DMTIMER1MS_TCAR2_RESETVAL                           (0x00000000U)

/* TPIR */

#define CSL_DMTIMER1MS_TPIR_POSITIVE_INC_VALUE_MASK             (0xFFFFFFFFU)
#define CSL_DMTIMER1MS_TPIR_POSITIVE_INC_VALUE_SHIFT            (0U)
#define CSL_DMTIMER1MS_TPIR_POSITIVE_INC_VALUE_RESETVAL         (0x00000000U)
#define CSL_DMTIMER1MS_TPIR_POSITIVE_INC_VALUE_MAX              (0xffffffffU)

#define CSL_DMTIMER1MS_TPIR_RESETVAL                            (0x00000000U)

/* TNIR */

#define CSL_DMTIMER1MS_TNIR_NEGATIVE_INV_VALUE_MASK             (0xFFFFFFFFU)
#define CSL_DMTIMER1MS_TNIR_NEGATIVE_INV_VALUE_SHIFT            (0U)
#define CSL_DMTIMER1MS_TNIR_NEGATIVE_INV_VALUE_RESETVAL         (0x00000000U)
#define CSL_DMTIMER1MS_TNIR_NEGATIVE_INV_VALUE_MAX              (0xffffffffU)

#define CSL_DMTIMER1MS_TNIR_RESETVAL                            (0x00000000U)

/* TCVR */

#define CSL_DMTIMER1MS_TCVR_COUNTER_VALUE_MASK                  (0xFFFFFFFFU)
#define CSL_DMTIMER1MS_TCVR_COUNTER_VALUE_SHIFT                 (0U)
#define CSL_DMTIMER1MS_TCVR_COUNTER_VALUE_RESETVAL              (0x00000000U)
#define CSL_DMTIMER1MS_TCVR_COUNTER_VALUE_MAX                   (0xffffffffU)

#define CSL_DMTIMER1MS_TCVR_RESETVAL                            (0x00000000U)

/* TOCR */

#define CSL_DMTIMER1MS_TOCR_OVF_COUNTER_VALUE_MASK              (0x00FFFFFFU)
#define CSL_DMTIMER1MS_TOCR_OVF_COUNTER_VALUE_SHIFT             (0U)
#define CSL_DMTIMER1MS_TOCR_OVF_COUNTER_VALUE_RESETVAL          (0x00000000U)
#define CSL_DMTIMER1MS_TOCR_OVF_COUNTER_VALUE_MAX               (0x00ffffffU)

#define CSL_DMTIMER1MS_TOCR_RESETVAL                            (0x00000000U)

/* TOWR */

#define CSL_DMTIMER1MS_TOWR_OVF_WRAPPING_VALUE_MASK             (0x00FFFFFFU)
#define CSL_DMTIMER1MS_TOWR_OVF_WRAPPING_VALUE_SHIFT            (0U)
#define CSL_DMTIMER1MS_TOWR_OVF_WRAPPING_VALUE_RESETVAL         (0x00000000U)
#define CSL_DMTIMER1MS_TOWR_OVF_WRAPPING_VALUE_MAX              (0x00ffffffU)

#define CSL_DMTIMER1MS_TOWR_RESETVAL                            (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
