/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
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
*  \file     hw_gpio.h
*  \brief    register-level header file for GPIO
*
**/

#ifndef HW_GPIO_H_
#define HW_GPIO_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define GPIO_REVISION                                                                                       (0x0U)
#define GPIO_SYSCONFIG                                                                                      (0x10U)
#define GPIO_IRQSTATUS_RAW_0                                                                                (0x24U)
#define GPIO_IRQSTATUS_RAW_1                                                                                (0x28U)
#define GPIO_IRQSTATUS_0                                                                                    (0x2cU)
#define GPIO_IRQSTATUS_1                                                                                    (0x30U)
#define GPIO_IRQSTATUS_SET_0                                                                                (0x34U)
#define GPIO_IRQSTATUS_SET_1                                                                                (0x38U)
#define GPIO_IRQSTATUS_CLR_0                                                                                (0x3cU)
#define GPIO_IRQSTATUS_CLR_1                                                                                (0x40U)
#define GPIO_IRQWAKEN_0                                                                                     (0x44U)
#define GPIO_IRQWAKEN_1                                                                                     (0x48U)
#define GPIO_SYSSTATUS                                                                                      (0x114U)
#define GPIO_CTRL                                                                                           (0x130U)
#define GPIO_OE                                                                                             (0x134U)
#define GPIO_DATAIN                                                                                         (0x138U)
#define GPIO_DATAOUT                                                                                        (0x13cU)
#define GPIO_LEVELDETECT0                                                                                   (0x140U)
#define GPIO_LEVELDETECT1                                                                                   (0x144U)
#define GPIO_RISINGDETECT                                                                                   (0x148U)
#define GPIO_FALLINGDETECT                                                                                  (0x14cU)
#define GPIO_DEBOUNCENABLE                                                                                  (0x150U)
#define GPIO_DEBOUNCINGTIME                                                                                 (0x154U)
#define GPIO_CLEARDATAOUT                                                                                   (0x190U)
#define GPIO_SETDATAOUT                                                                                     (0x194U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define GPIO_REVISION_REVISION_SHIFT                                                                        (0U)
#define GPIO_REVISION_REVISION_MASK                                                                         (0xffffffffU)

#define GPIO_SYSCONFIG_AUTOIDLE_SHIFT                                                                       (0U)
#define GPIO_SYSCONFIG_AUTOIDLE_MASK                                                                        (0x00000001U)
#define GPIO_SYSCONFIG_AUTOIDLE_FREERUN                                                                      (0U)
#define GPIO_SYSCONFIG_AUTOIDLE_AUTOMATIC                                                                    (1U)

#define GPIO_SYSCONFIG_SOFTRESET_SHIFT                                                                      (1U)
#define GPIO_SYSCONFIG_SOFTRESET_MASK                                                                       (0x00000002U)
#define GPIO_SYSCONFIG_SOFTRESET_NORMAL                                                                      (0U)
#define GPIO_SYSCONFIG_SOFTRESET_RESET                                                                       (1U)

#define GPIO_SYSCONFIG_ENAWAKEUP_SHIFT                                                                      (2U)
#define GPIO_SYSCONFIG_ENAWAKEUP_MASK                                                                       (0x00000004U)
#define GPIO_SYSCONFIG_ENAWAKEUP_DISABLE                                                                     (0U)
#define GPIO_SYSCONFIG_ENAWAKEUP_ENABLE                                                                      (1U)

#define GPIO_SYSCONFIG_IDLEMODE_SHIFT                                                                       (3U)
#define GPIO_SYSCONFIG_IDLEMODE_MASK                                                                        (0x00000018U)
#define GPIO_SYSCONFIG_IDLEMODE_FORCEIDLE                                                                    (0U)
#define GPIO_SYSCONFIG_IDLEMODE_NOIDLE                                                                       (1U)
#define GPIO_SYSCONFIG_IDLEMODE_SMARTIDLE                                                                    (2U)
#define GPIO_SYSCONFIG_IDLEMODE_SMARTIDLEWAKEUP                                                              (3U)

#define GPIO_SYSCONFIG_RESERVED_SHIFT                                                                       (5U)
#define GPIO_SYSCONFIG_RESERVED_MASK                                                                        (0xffffffe0U)

#define GPIO_IRQSTATUS_RAW_0_INTLINE_SHIFT                                                                  (0U)
#define GPIO_IRQSTATUS_RAW_0_INTLINE_MASK                                                                   (0xffffffffU)

#define GPIO_IRQSTATUS_RAW_1_INTLINE_SHIFT                                                                  (0U)
#define GPIO_IRQSTATUS_RAW_1_INTLINE_MASK                                                                   (0xffffffffU)

#define GPIO_IRQSTATUS_0_INTLINE_SHIFT                                                                      (0U)
#define GPIO_IRQSTATUS_0_INTLINE_MASK                                                                       (0xffffffffU)

#define GPIO_IRQSTATUS_1_INTLINE_SHIFT                                                                      (0U)
#define GPIO_IRQSTATUS_1_INTLINE_MASK                                                                       (0xffffffffU)

#define GPIO_IRQSTATUS_SET_0_INTLINE_SHIFT                                                                  (0U)
#define GPIO_IRQSTATUS_SET_0_INTLINE_MASK                                                                   (0xffffffffU)

#define GPIO_IRQSTATUS_SET_1_INTLINE_SHIFT                                                                  (0U)
#define GPIO_IRQSTATUS_SET_1_INTLINE_MASK                                                                   (0xffffffffU)

#define GPIO_IRQSTATUS_CLR_0_INTLINE_SHIFT                                                                  (0U)
#define GPIO_IRQSTATUS_CLR_0_INTLINE_MASK                                                                   (0xffffffffU)

#define GPIO_IRQSTATUS_CLR_1_INTLINE_SHIFT                                                                  (0U)
#define GPIO_IRQSTATUS_CLR_1_INTLINE_MASK                                                                   (0xffffffffU)

#define GPIO_IRQWAKEN_0_INTLINE_SHIFT                                                                       (0U)
#define GPIO_IRQWAKEN_0_INTLINE_MASK                                                                        (0xffffffffU)

#define GPIO_IRQWAKEN_1_INTLINE_SHIFT                                                                       (0U)
#define GPIO_IRQWAKEN_1_INTLINE_MASK                                                                        (0xffffffffU)

#define GPIO_SYSSTATUS_RESETDONE_SHIFT                                                                      (0U)
#define GPIO_SYSSTATUS_RESETDONE_MASK                                                                       (0x00000001U)
#define GPIO_SYSSTATUS_RESETDONE_INPROGRESS                                                                  (0U)
#define GPIO_SYSSTATUS_RESETDONE_COMPLETE                                                                    (1U)

#define GPIO_SYSSTATUS_RESERVED_SHIFT                                                                       (1U)
#define GPIO_SYSSTATUS_RESERVED_MASK                                                                        (0xfffffffeU)

#define GPIO_CTRL_DISABLEMODULE_SHIFT                                                                       (0U)
#define GPIO_CTRL_DISABLEMODULE_MASK                                                                        (0x00000001U)
#define GPIO_CTRL_DISABLEMODULE_ENABLED                                                                      (0U)
#define GPIO_CTRL_DISABLEMODULE_DISABLED                                                                     (1U)

#define GPIO_CTRL_GATINGRATIO_SHIFT                                                                         (1U)
#define GPIO_CTRL_GATINGRATIO_MASK                                                                          (0x00000006U)
#define GPIO_CTRL_GATINGRATIO_N_1                                                                            (0U)
#define GPIO_CTRL_GATINGRATIO_N_2                                                                            (1U)
#define GPIO_CTRL_GATINGRATIO_N_4                                                                            (2U)
#define GPIO_CTRL_GATINGRATIO_N_8                                                                            (3U)

#define GPIO_CTRL_RESERVED_SHIFT                                                                            (3U)
#define GPIO_CTRL_RESERVED_MASK                                                                             (0xfffffff8U)

#define GPIO_OE_OUTPUTEN_SHIFT                                                                              (0U)
#define GPIO_OE_OUTPUTEN_MASK                                                                               (0xffffffffU)
#define GPIO_OE_OUTPUTEN_ENABLED                                                                             (0U)
#define GPIO_OE_OUTPUTEN_DISABLED                                                                            (1U)

#define GPIO_DATAIN_DATAIN_SHIFT                                                                            (0U)
#define GPIO_DATAIN_DATAIN_MASK                                                                             (0xffffffffU)

#define GPIO_DATAOUT_DATAOUT_SHIFT                                                                          (0U)
#define GPIO_DATAOUT_DATAOUT_MASK                                                                           (0xffffffffU)

#define GPIO_LEVELDETECT0_LEVELDETECT0_SHIFT                                                                (0U)
#define GPIO_LEVELDETECT0_LEVELDETECT0_MASK                                                                 (0xffffffffU)
#define GPIO_LEVELDETECT0_LEVELDETECT0_DISABLED                                                              (0U)
#define GPIO_LEVELDETECT0_LEVELDETECT0_ENABLED                                                               (1U)

#define GPIO_LEVELDETECT1_LEVELDETECT1_SHIFT                                                                (0U)
#define GPIO_LEVELDETECT1_LEVELDETECT1_MASK                                                                 (0xffffffffU)
#define GPIO_LEVELDETECT1_LEVELDETECT1_DISABLED                                                              (0U)
#define GPIO_LEVELDETECT1_LEVELDETECT1_ENABLED                                                               (1U)

#define GPIO_RISINGDETECT_RISINGDETECT_SHIFT                                                                (0U)
#define GPIO_RISINGDETECT_RISINGDETECT_MASK                                                                 (0xffffffffU)
#define GPIO_RISINGDETECT_RISINGDETECT_DISABLED                                                              (0U)
#define GPIO_RISINGDETECT_RISINGDETECT_ENABLED                                                               (1U)

#define GPIO_FALLINGDETECT_FALLINGDETECT_SHIFT                                                              (0U)
#define GPIO_FALLINGDETECT_FALLINGDETECT_MASK                                                               (0xffffffffU)
#define GPIO_FALLINGDETECT_FALLINGDETECT_DISABLED                                                            (0U)
#define GPIO_FALLINGDETECT_FALLINGDETECT_ENABLED                                                             (1U)

#define GPIO_DEBOUNCENABLE_DEBOUNCEENABLE_SHIFT                                                             (0U)
#define GPIO_DEBOUNCENABLE_DEBOUNCEENABLE_MASK                                                              (0xffffffffU)
#define GPIO_DEBOUNCENABLE_DEBOUNCEENABLE_NODEBOUNCE                                                         (0U)
#define GPIO_DEBOUNCENABLE_DEBOUNCEENABLE_DEBOUNCE                                                           (1U)

#define GPIO_DEBOUNCINGTIME_DEBOUNCETIME_SHIFT                                                              (0U)
#define GPIO_DEBOUNCINGTIME_DEBOUNCETIME_MASK                                                               (0x000000ffU)

#define GPIO_DEBOUNCINGTIME_RESERVED_SHIFT                                                                  (8U)
#define GPIO_DEBOUNCINGTIME_RESERVED_MASK                                                                   (0xffffff00U)

#define GPIO_CLEARDATAOUT_INTLINE_SHIFT                                                                     (0U)
#define GPIO_CLEARDATAOUT_INTLINE_MASK                                                                      (0xffffffffU)

#define GPIO_SETDATAOUT_INTLINE_SHIFT                                                                       (0U)
#define GPIO_SETDATAOUT_INTLINE_MASK                                                                        (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_GPIO_H_ */
