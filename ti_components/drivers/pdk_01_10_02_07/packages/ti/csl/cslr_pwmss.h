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
#ifndef CSLR_PWMSS_H_
#define CSLR_PWMSS_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>


/**************************************************************************
* Register Overlay Structure for ALL
**************************************************************************/
typedef struct {
    volatile Uint32 IDVER;
    volatile Uint32 SYSCONFIG;
    volatile Uint32 CLKCONFIG;
    volatile Uint32 CLKSTATUS;
    volatile Uint8  RSVD0[32];
} CSL_PwmssRegs;


/**************************************************************************
* Register Macros
**************************************************************************/
#define CSL_PWMSS_CLKSTATUS                                     (0xCU)
#define CSL_PWMSS_CLKCONFIG                                     (0x8U)
#define CSL_PWMSS_SYSCONFIG                                     (0x4U)
#define CSL_PWMSS_IDVER                                         (0x0U)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* CLKSTATUS */

#define CSL_PWMSS_CLKSTATUS_ECAP_CLK_EN_ACK_MASK                (0x00000001U)
#define CSL_PWMSS_CLKSTATUS_ECAP_CLK_EN_ACK_SHIFT               (0U)
#define CSL_PWMSS_CLKSTATUS_ECAP_CLK_EN_ACK_RESETVAL            (0x00000000U)
#define CSL_PWMSS_CLKSTATUS_ECAP_CLK_EN_ACK_MAX                 (0x00000001U)

#define CSL_PWMSS_CLKSTATUS_ECAP_CLKSTOP_ACK_MASK               (0x00000002U)
#define CSL_PWMSS_CLKSTATUS_ECAP_CLKSTOP_ACK_SHIFT              (1U)
#define CSL_PWMSS_CLKSTATUS_ECAP_CLKSTOP_ACK_RESETVAL           (0x00000000U)
#define CSL_PWMSS_CLKSTATUS_ECAP_CLKSTOP_ACK_MAX                (0x00000001U)

#define CSL_PWMSS_CLKSTATUS_EQEP_CLK_EN_ACK_MASK                (0x00000010U)
#define CSL_PWMSS_CLKSTATUS_EQEP_CLK_EN_ACK_SHIFT               (4U)
#define CSL_PWMSS_CLKSTATUS_EQEP_CLK_EN_ACK_RESETVAL            (0x00000000U)
#define CSL_PWMSS_CLKSTATUS_EQEP_CLK_EN_ACK_MAX                 (0x00000001U)

#define CSL_PWMSS_CLKSTATUS_EQEP_CLKSTOP_ACK_MASK               (0x00000020U)
#define CSL_PWMSS_CLKSTATUS_EQEP_CLKSTOP_ACK_SHIFT              (5U)
#define CSL_PWMSS_CLKSTATUS_EQEP_CLKSTOP_ACK_RESETVAL           (0x00000000U)
#define CSL_PWMSS_CLKSTATUS_EQEP_CLKSTOP_ACK_MAX                (0x00000001U)

#define CSL_PWMSS_CLKSTATUS_EPWM_CLK_EN_ACK_MASK                (0x00000100U)
#define CSL_PWMSS_CLKSTATUS_EPWM_CLK_EN_ACK_SHIFT               (8U)
#define CSL_PWMSS_CLKSTATUS_EPWM_CLK_EN_ACK_RESETVAL            (0x00000000U)
#define CSL_PWMSS_CLKSTATUS_EPWM_CLK_EN_ACK_MAX                 (0x00000001U)

#define CSL_PWMSS_CLKSTATUS_EPWM_CLKSTOP_ACK_MASK               (0x00000200U)
#define CSL_PWMSS_CLKSTATUS_EPWM_CLKSTOP_ACK_SHIFT              (9U)
#define CSL_PWMSS_CLKSTATUS_EPWM_CLKSTOP_ACK_RESETVAL           (0x00000000U)
#define CSL_PWMSS_CLKSTATUS_EPWM_CLKSTOP_ACK_MAX                (0x00000001U)

#define CSL_PWMSS_CLKSTATUS_RESETVAL                            (0x00000000U)

/* CLKCONFIG */

#define CSL_PWMSS_CLKCONFIG_ECAPCLK_EN_MASK                     (0x00000001U)
#define CSL_PWMSS_CLKCONFIG_ECAPCLK_EN_SHIFT                    (0U)
#define CSL_PWMSS_CLKCONFIG_ECAPCLK_EN_RESETVAL                 (0x00000001U)
#define CSL_PWMSS_CLKCONFIG_ECAPCLK_EN_MAX                      (0x00000001U)

#define CSL_PWMSS_CLKCONFIG_ECAPCLKSTOP_REQ_MASK                (0x00000002U)
#define CSL_PWMSS_CLKCONFIG_ECAPCLKSTOP_REQ_SHIFT               (1U)
#define CSL_PWMSS_CLKCONFIG_ECAPCLKSTOP_REQ_RESETVAL            (0x00000000U)
#define CSL_PWMSS_CLKCONFIG_ECAPCLKSTOP_REQ_MAX                 (0x00000001U)

#define CSL_PWMSS_CLKCONFIG_EQEPCLK_EN_MASK                     (0x00000010U)
#define CSL_PWMSS_CLKCONFIG_EQEPCLK_EN_SHIFT                    (4U)
#define CSL_PWMSS_CLKCONFIG_EQEPCLK_EN_RESETVAL                 (0x00000001U)
#define CSL_PWMSS_CLKCONFIG_EQEPCLK_EN_MAX                      (0x00000001U)

#define CSL_PWMSS_CLKCONFIG_EQEPCLKSTOP_REQ_MASK                (0x00000020U)
#define CSL_PWMSS_CLKCONFIG_EQEPCLKSTOP_REQ_SHIFT               (5U)
#define CSL_PWMSS_CLKCONFIG_EQEPCLKSTOP_REQ_RESETVAL            (0x00000000U)
#define CSL_PWMSS_CLKCONFIG_EQEPCLKSTOP_REQ_MAX                 (0x00000001U)

#define CSL_PWMSS_CLKCONFIG_EPWMCLK_EN_MASK                     (0x00000100U)
#define CSL_PWMSS_CLKCONFIG_EPWMCLK_EN_SHIFT                    (8U)
#define CSL_PWMSS_CLKCONFIG_EPWMCLK_EN_RESETVAL                 (0x00000001U)
#define CSL_PWMSS_CLKCONFIG_EPWMCLK_EN_MAX                      (0x00000001U)

#define CSL_PWMSS_CLKCONFIG_EPWMCLKSTOP_REQ_MASK                (0x00000200U)
#define CSL_PWMSS_CLKCONFIG_EPWMCLKSTOP_REQ_SHIFT               (9U)
#define CSL_PWMSS_CLKCONFIG_EPWMCLKSTOP_REQ_RESETVAL            (0x00000000U)
#define CSL_PWMSS_CLKCONFIG_EPWMCLKSTOP_REQ_MAX                 (0x00000001U)

#define CSL_PWMSS_CLKCONFIG_RESETVAL                            (0x00000111U)

/* SYSCONFIG */

#define CSL_PWMSS_SYSCONFIG_SOFTRESET_MASK                      (0x00000001U)
#define CSL_PWMSS_SYSCONFIG_SOFTRESET_SHIFT                     (0U)
#define CSL_PWMSS_SYSCONFIG_SOFTRESET_RESETVAL                  (0x00000000U)
#define CSL_PWMSS_SYSCONFIG_SOFTRESET_MAX                       (0x00000001U)

#define CSL_PWMSS_SYSCONFIG_FREEEMU_MASK                        (0x00000002U)
#define CSL_PWMSS_SYSCONFIG_FREEEMU_SHIFT                       (1U)
#define CSL_PWMSS_SYSCONFIG_FREEEMU_RESETVAL                    (0x00000000U)
#define CSL_PWMSS_SYSCONFIG_FREEEMU_SENSITIVE_TO_SUSPEND        (0U)
#define CSL_PWMSS_SYSCONFIG_FREEEMU_NOT_SENSITIVE_TO_SUSPEND    (1U)
#define CSL_PWMSS_SYSCONFIG_FREEEMU_VAL_0                       (CSL_PWMSS_SYSCONFIG_FREEEMU_SENSITIVE_TO_SUSPEND)
#define CSL_PWMSS_SYSCONFIG_FREEEMU_VAL_1                       (CSL_PWMSS_SYSCONFIG_FREEEMU_NOT_SENSITIVE_TO_SUSPEND)

#define CSL_PWMSS_SYSCONFIG_IDLEMODE_MASK                       (0x0000000CU)
#define CSL_PWMSS_SYSCONFIG_IDLEMODE_SHIFT                      (2U)
#define CSL_PWMSS_SYSCONFIG_IDLEMODE_RESETVAL                   (0x00000002U)
#define CSL_PWMSS_SYSCONFIG_IDLEMODE_FORCE_IDLE                 (0U)
#define CSL_PWMSS_SYSCONFIG_IDLEMODE_NO_IDLE                    (1U)
#define CSL_PWMSS_SYSCONFIG_IDLEMODE_SMART_IDLE                 (2U)
#define CSL_PWMSS_SYSCONFIG_IDLEMODE_VAL_0                      (CSL_PWMSS_SYSCONFIG_IDLEMODE_FORCE_IDLE)
#define CSL_PWMSS_SYSCONFIG_IDLEMODE_VAL_1                      (CSL_PWMSS_SYSCONFIG_IDLEMODE_NO_IDLE)
#define CSL_PWMSS_SYSCONFIG_IDLEMODE_VAL_2                      (CSL_PWMSS_SYSCONFIG_IDLEMODE_SMART_IDLE)
#define CSL_PWMSS_SYSCONFIG_IDLEMODE_VAL_3                      (0x00000003U)

#define CSL_PWMSS_SYSCONFIG_STANDBYMODE_MASK                    (0x00000030U)
#define CSL_PWMSS_SYSCONFIG_STANDBYMODE_SHIFT                   (4U)
#define CSL_PWMSS_SYSCONFIG_STANDBYMODE_RESETVAL                (0x00000002U)
#define CSL_PWMSS_SYSCONFIG_STANDBYMODE_FORCE_STANDBY           (0U)
#define CSL_PWMSS_SYSCONFIG_STANDBYMODE_NO_STANDBY              (1U)
#define CSL_PWMSS_SYSCONFIG_STANDBYMODE_SMART_STANDBY           (2U)
#define CSL_PWMSS_SYSCONFIG_STANDBYMODE_VAL_0                   (CSL_PWMSS_SYSCONFIG_STANDBYMODE_FORCE_STANDBY)
#define CSL_PWMSS_SYSCONFIG_STANDBYMODE_VAL_1                   (CSL_PWMSS_SYSCONFIG_STANDBYMODE_NO_STANDBY)
#define CSL_PWMSS_SYSCONFIG_STANDBYMODE_VAL_2                   (CSL_PWMSS_SYSCONFIG_STANDBYMODE_SMART_STANDBY)
#define CSL_PWMSS_SYSCONFIG_STANDBYMODE_VAL_3                   (0x00000003U)

#define CSL_PWMSS_SYSCONFIG_RESETVAL                            (0x00000028U)

/* IDVER */

#define CSL_PWMSS_IDVER_Y_MINOR_MASK                            (0x0000003FU)
#define CSL_PWMSS_IDVER_Y_MINOR_SHIFT                           (0U)
#define CSL_PWMSS_IDVER_Y_MINOR_RESETVAL                        (0x00000000U)
#define CSL_PWMSS_IDVER_Y_MINOR_MAX                             (0x0000003fU)

#define CSL_PWMSS_IDVER_CUSTOM_MASK                             (0x000000C0U)
#define CSL_PWMSS_IDVER_CUSTOM_SHIFT                            (6U)
#define CSL_PWMSS_IDVER_CUSTOM_RESETVAL                         (0x00000000U)
#define CSL_PWMSS_IDVER_CUSTOM_MAX                              (0x00000003U)

#define CSL_PWMSS_IDVER_X_MAJOR_MASK                            (0x00000700U)
#define CSL_PWMSS_IDVER_X_MAJOR_SHIFT                           (8U)
#define CSL_PWMSS_IDVER_X_MAJOR_RESETVAL                        (0x00000000U)
#define CSL_PWMSS_IDVER_X_MAJOR_MAX                             (0x00000007U)

#define CSL_PWMSS_IDVER_R_RTL_MASK                              (0x0000F800U)
#define CSL_PWMSS_IDVER_R_RTL_SHIFT                             (11U)
#define CSL_PWMSS_IDVER_R_RTL_RESETVAL                          (0x00000000U)
#define CSL_PWMSS_IDVER_R_RTL_MAX                               (0x0000001fU)

#define CSL_PWMSS_IDVER_FUNC_MASK                               (0x0FFF0000U)
#define CSL_PWMSS_IDVER_FUNC_SHIFT                              (16U)
#define CSL_PWMSS_IDVER_FUNC_RESETVAL                           (0x00000000U)
#define CSL_PWMSS_IDVER_FUNC_MAX                                (0x00000fffU)

#define CSL_PWMSS_IDVER_SCHEME_MASK                             (0xC0000000U)
#define CSL_PWMSS_IDVER_SCHEME_SHIFT                            (30U)
#define CSL_PWMSS_IDVER_SCHEME_RESETVAL                         (0x00000001U)
#define CSL_PWMSS_IDVER_SCHEME_MAX                              (0x00000003U)

#define CSL_PWMSS_IDVER_RESETVAL                                (0x40000000U)

#ifdef __cplusplus
}
#endif
#endif
