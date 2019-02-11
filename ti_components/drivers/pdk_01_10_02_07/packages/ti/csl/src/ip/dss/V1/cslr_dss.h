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
#ifndef CSLR_DSS_H_V1
#define CSLR_DSS_H_V1

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
    volatile Uint32 REVISION;
    volatile Uint8  RSVD0[12];
    volatile Uint32 SYSCONFIG;
    volatile Uint32 SYSSTS;
    volatile Uint8  RSVD1[40];
    volatile Uint32 CTRL;
    volatile Uint8  RSVD2[24];
    volatile Uint32 STS;
} CSL_DssRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

/* This register contains the Display subsystem revision number */
#define CSL_DSS_REVISION                                        (0x0U)

/* This register controls the various parameters of the OCP interface */
#define CSL_DSS_SYSCONFIG                                       (0x10U)

/* This register provides status information about the module */
#define CSL_DSS_SYSSTS                                          (0x14U)

/* This register contains the Display subsystem control bits */
#define CSL_DSS_CTRL                                            (0x40U)

/* This register contains the Display subsystem status */
#define CSL_DSS_STS                                             (0x5CU)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* REVISION */

#define CSL_DSS_REVISION_REV_MASK                               (0x000000FFU)
#define CSL_DSS_REVISION_REV_SHIFT                              (0U)
#define CSL_DSS_REVISION_REV_RESETVAL                           (0x00000060U)
#define CSL_DSS_REVISION_REV_MAX                                (0x000000ffU)

#define CSL_DSS_REVISION_RESETVAL                               (0x00000060U)

/* SYSCONFIG */

#define CSL_DSS_SYSCONFIG_RESETVAL                              (0x00000000U)

/* SYSSTS */

#define CSL_DSS_SYSSTS_RESETDONE_MASK                           (0x00000001U)
#define CSL_DSS_SYSSTS_RESETDONE_SHIFT                          (0U)
#define CSL_DSS_SYSSTS_RESETDONE_RESETVAL                       (0x00000001U)
#define CSL_DSS_SYSSTS_RESETDONE_RSTCOMP                        (0x00000001U)
#define CSL_DSS_SYSSTS_RESETDONE_RSTACT                         (0x00000000U)

#define CSL_DSS_SYSSTS_RESETVAL                                 (0x00000001U)

/* CTRL */

#define CSL_DSS_CTRL_LCD1_CLK_SWITCH_MASK                       (0x00000001U)
#define CSL_DSS_CTRL_LCD1_CLK_SWITCH_SHIFT                      (0U)
#define CSL_DSS_CTRL_LCD1_CLK_SWITCH_RESETVAL                   (0x00000000U)
#define CSL_DSS_CTRL_LCD1_CLK_SWITCH_DSS_CLK_SEL                (0x00000000U)
#define CSL_DSS_CTRL_LCD1_CLK_SWITCH_DPLL_DSI1_A_CLK1_SEL       (0x00000001U)

#define CSL_DSS_CTRL_DSI1_A_CLK_SWITCH_MASK                     (0x00000002U)
#define CSL_DSS_CTRL_DSI1_A_CLK_SWITCH_SHIFT                    (1U)
#define CSL_DSS_CTRL_DSI1_A_CLK_SWITCH_RESETVAL                 (0x00000000U)
#define CSL_DSS_CTRL_DSI1_A_CLK_SWITCH_DPLL_DSI1_A_CLK2_SEL     (0x00000001U)
#define CSL_DSS_CTRL_DSI1_A_CLK_SWITCH_DSS_CLK_SEL              (0x00000000U)

#define CSL_DSS_CTRL_FCK_CLK_SWITCH_MASK                        (0x00000380U)
#define CSL_DSS_CTRL_FCK_CLK_SWITCH_SHIFT                       (7U)
#define CSL_DSS_CTRL_FCK_CLK_SWITCH_RESETVAL                    (0x00000000U)
#define CSL_DSS_CTRL_FCK_CLK_SWITCH_DPLL_DSI1_A_CLK1            (0x00000001U)
#define CSL_DSS_CTRL_FCK_CLK_SWITCH_DPLL_DSI1_B_CLK1            (0x00000002U)
#define CSL_DSS_CTRL_FCK_CLK_SWITCH_DPLL_HDMI_CLK1              (0x00000003U)
#define CSL_DSS_CTRL_FCK_CLK_SWITCH_DSS_CLK                     (0x00000000U)
#define CSL_DSS_CTRL_FCK_CLK_SWITCH_DPLL_DSI1_C_CLK1            (0x00000004U)

#define CSL_DSS_CTRL_DSI1_B_CLK_SWITCH_MASK                     (0x00000400U)
#define CSL_DSS_CTRL_DSI1_B_CLK_SWITCH_SHIFT                    (10U)
#define CSL_DSS_CTRL_DSI1_B_CLK_SWITCH_RESETVAL                 (0x00000000U)
#define CSL_DSS_CTRL_DSI1_B_CLK_SWITCH_DPLL_DSI1_B_CLK2_SEL     (0x00000001U)
#define CSL_DSS_CTRL_DSI1_B_CLK_SWITCH_DSS_CLK_SEL              (0x00000000U)

#define CSL_DSS_CTRL_RFBI_SWITCH_MASK                           (0x00004000U)
#define CSL_DSS_CTRL_RFBI_SWITCH_SHIFT                          (14U)
#define CSL_DSS_CTRL_RFBI_SWITCH_RESETVAL                       (0x00000000U)
#define CSL_DSS_CTRL_RFBI_SWITCH_VP1_SEL                        (0x00000000U)
#define CSL_DSS_CTRL_RFBI_SWITCH_VP2_SEL                        (0x00000001U)

#define CSL_DSS_CTRL_LCD2_CLK_SWITCH_MASK                       (0x00001000U)
#define CSL_DSS_CTRL_LCD2_CLK_SWITCH_SHIFT                      (12U)
#define CSL_DSS_CTRL_LCD2_CLK_SWITCH_RESETVAL                   (0x00000000U)
#define CSL_DSS_CTRL_LCD2_CLK_SWITCH_DSS_CLK_SEL                (0x00000000U)
#define CSL_DSS_CTRL_LCD2_CLK_SWITCH_DPLL_DSI1_B_CLK1_SEL       (0x00000001U)

#define CSL_DSS_CTRL_PARALLEL_SEL_MASK                          (0x00030000U)
#define CSL_DSS_CTRL_PARALLEL_SEL_SHIFT                         (16U)
#define CSL_DSS_CTRL_PARALLEL_SEL_RESETVAL                      (0x00000000U)
#define CSL_DSS_CTRL_PARALLEL_SEL_LCD1                          (0x00000001U)
#define CSL_DSS_CTRL_PARALLEL_SEL_HDMI                          (0x00000000U)
#define CSL_DSS_CTRL_PARALLEL_SEL_LCD2                          (0x00000002U)
#define CSL_DSS_CTRL_PARALLEL_SEL_LCD3                          (0x00000003U)

#define CSL_DSS_CTRL_DSI1_C_CLK_SWITCH_MASK                     (0x00040000U)
#define CSL_DSS_CTRL_DSI1_C_CLK_SWITCH_SHIFT                    (18U)
#define CSL_DSS_CTRL_DSI1_C_CLK_SWITCH_RESETVAL                 (0x00000000U)
#define CSL_DSS_CTRL_DSI1_C_CLK_SWITCH_DPLL_DSI1_C_CLK2_SEL     (0x00000001U)
#define CSL_DSS_CTRL_DSI1_C_CLK_SWITCH_DSS_CLK_SEL              (0x00000000U)

#define CSL_DSS_CTRL_LCD3_CLK_SWITCH_MASK                       (0x00080000U)
#define CSL_DSS_CTRL_LCD3_CLK_SWITCH_SHIFT                      (19U)
#define CSL_DSS_CTRL_LCD3_CLK_SWITCH_RESETVAL                   (0x00000000U)
#define CSL_DSS_CTRL_LCD3_CLK_SWITCH_DSS_CLK_SEL                (0x00000000U)
#define CSL_DSS_CTRL_LCD3_CLK_SWITCH_DPLL_DSI1_C_CLK1_SEL       (0x00000001U)

#define CSL_DSS_CTRL_RFBI_SWITCH2_MASK                          (0x00100000U)
#define CSL_DSS_CTRL_RFBI_SWITCH2_SHIFT                         (20U)
#define CSL_DSS_CTRL_RFBI_SWITCH2_RESETVAL                      (0x00000000U)
#define CSL_DSS_CTRL_RFBI_SWITCH2_VP1_2_SEL                     (0x00000000U)
#define CSL_DSS_CTRL_RFBI_SWITCH2_VP3_SEL                       (0x00000001U)

#define CSL_DSS_CTRL_RESETVAL                                   (0x00000000U)

/* STS */

#define CSL_DSS_STS_LCD1_CLK_STS_MASK                           (0x00000003U)
#define CSL_DSS_STS_LCD1_CLK_STS_SHIFT                          (0U)
#define CSL_DSS_STS_LCD1_CLK_STS_RESETVAL                       (0x00000001U)
#define CSL_DSS_STS_LCD1_CLK_STS_DSS_CLK_SEL                    (0x00000001U)
#define CSL_DSS_STS_LCD1_CLK_STS_DPLL_DSI1_A_CLK1_SEL           (0x00000002U)
#define CSL_DSS_STS_LCD1_CLK_STS_LCD1_CLK_TRANSITION            (0x00000000U)

#define CSL_DSS_STS_DSI1_A_CLK_STS_MASK                         (0x00000180U)
#define CSL_DSS_STS_DSI1_A_CLK_STS_SHIFT                        (7U)
#define CSL_DSS_STS_DSI1_A_CLK_STS_RESETVAL                     (0x00000001U)
#define CSL_DSS_STS_DSI1_A_CLK_STS_DSS_CLK_SEL                  (0x00000001U)
#define CSL_DSS_STS_DSI1_A_CLK_STS_DPLL_DSI_A_CLK2_SEL          (0x00000002U)
#define CSL_DSS_STS_DSI1_A_CLK_STS_DSI1_A_CLK_TRANSITION        (0x00000000U)

#define CSL_DSS_STS_DSI1_B_CLK_STS_MASK                         (0x00000600U)
#define CSL_DSS_STS_DSI1_B_CLK_STS_SHIFT                        (9U)
#define CSL_DSS_STS_DSI1_B_CLK_STS_RESETVAL                     (0x00000001U)
#define CSL_DSS_STS_DSI1_B_CLK_STS_DSS_CLK_SEL                  (0x00000001U)
#define CSL_DSS_STS_DSI1_B_CLK_STS_DPLL_DSI1_B_CLK2_SEL         (0x00000002U)
#define CSL_DSS_STS_DSI1_B_CLK_STS_DSI1_B_CLK_TRANSITION        (0x00000000U)

#define CSL_DSS_STS_LCD2_CLK_STS_MASK                           (0x00001800U)
#define CSL_DSS_STS_LCD2_CLK_STS_SHIFT                          (11U)
#define CSL_DSS_STS_LCD2_CLK_STS_RESETVAL                       (0x00000001U)
#define CSL_DSS_STS_LCD2_CLK_STS_DSS_CLK_SEL                    (0x00000001U)
#define CSL_DSS_STS_LCD2_CLK_STS_DPLL_DSI1_B_CLK1_SEL           (0x00000002U)
#define CSL_DSS_STS_LCD2_CLK_STS_LCD2_CLK_TRANSITION            (0x00000000U)

#define CSL_DSS_STS_FCK_CLK_STS_MASK                            (0x000F8000U)
#define CSL_DSS_STS_FCK_CLK_STS_SHIFT                           (15U)
#define CSL_DSS_STS_FCK_CLK_STS_RESETVAL                        (0x00000001U)
#define CSL_DSS_STS_FCK_CLK_STS_MAX                             (0x0000001fU)

#define CSL_DSS_STS_RFBI_STS_MASK                               (0x00300000U)
#define CSL_DSS_STS_RFBI_STS_SHIFT                              (20U)
#define CSL_DSS_STS_RFBI_STS_RESETVAL                           (0x00000000U)
#define CSL_DSS_STS_RFBI_STS_VP2_SEL                            (0x00000001U)
#define CSL_DSS_STS_RFBI_STS_VP1_SEL                            (0x00000000U)
#define CSL_DSS_STS_RFBI_STS_VP3_SEL                            (0x00000002U)

#define CSL_DSS_STS_DSI1_C_CLK_STS_MASK                         (0x00C00000U)
#define CSL_DSS_STS_DSI1_C_CLK_STS_SHIFT                        (22U)
#define CSL_DSS_STS_DSI1_C_CLK_STS_RESETVAL                     (0x00000001U)
#define CSL_DSS_STS_DSI1_C_CLK_STS_DSS_CLK_SEL                  (0x00000001U)
#define CSL_DSS_STS_DSI1_C_CLK_STS_DPLL_DSI1_C_CLK2_SEL         (0x00000002U)
#define CSL_DSS_STS_DSI1_C_CLK_STS_DSI1_C_CLK_TRANSITION        (0x00000000U)

#define CSL_DSS_STS_LCD3_CLK_STS_MASK                           (0x03000000U)
#define CSL_DSS_STS_LCD3_CLK_STS_SHIFT                          (24U)
#define CSL_DSS_STS_LCD3_CLK_STS_RESETVAL                       (0x00000001U)
#define CSL_DSS_STS_LCD3_CLK_STS_DSS_CLK_SEL                    (0x00000001U)
#define CSL_DSS_STS_LCD3_CLK_STS_DPLL_DSI1_C_CLK1_SEL           (0x00000002U)
#define CSL_DSS_STS_LCD3_CLK_STS_LCD3_CLK_TRANSITION            (0x00000000U)

#define CSL_DSS_STS_RESETVAL                                    (0x01408a81U)

#ifdef __cplusplus
}
#endif
#endif
