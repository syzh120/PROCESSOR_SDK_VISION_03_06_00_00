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
 *  \file   hw_eve2_prm.h
 *
 *  \brief  Register-level header file for PRCM
 *
**/

#ifndef HW_EVE2_PRM_H_
#define HW_EVE2_PRM_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define PM_EVE2_PWRSTCTRL                                       (0x0U)
#define PM_EVE2_PWRSTST                                         (0x4U)
#define RM_EVE2_RSTCTRL                                         (0x10U)
#define RM_EVE2_RSTST                                           (0x14U)
#define PM_EVE2_EVE2_WKDEP                                      (0x20U)
#define RM_EVE2_EVE2_CONTEXT                                    (0x24U)


/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define PM_EVE2_PWRSTCTRL_EVE2_BANK_ONSTATE_SHIFT               (16U)
#define PM_EVE2_PWRSTCTRL_EVE2_BANK_ONSTATE_MASK                (0x00030000U)
#define PM_EVE2_PWRSTCTRL_EVE2_BANK_ONSTATE_MEM_ON               (3U)

#define PM_EVE2_PWRSTCTRL_POWERSTATE_SHIFT                      (0U)
#define PM_EVE2_PWRSTCTRL_POWERSTATE_MASK                       (0x00000003U)
#define PM_EVE2_PWRSTCTRL_POWERSTATE_OFF                         (0U)
#define PM_EVE2_PWRSTCTRL_POWERSTATE_INACT                       (2U)
#define PM_EVE2_PWRSTCTRL_POWERSTATE_RESERVED                    (1U)
#define PM_EVE2_PWRSTCTRL_POWERSTATE_ON                          (3U)

#define PM_EVE2_PWRSTCTRL_LOWPOWERSTATECHANGE_SHIFT             (4U)
#define PM_EVE2_PWRSTCTRL_LOWPOWERSTATECHANGE_MASK              (0x00000010U)
#define PM_EVE2_PWRSTCTRL_LOWPOWERSTATECHANGE_EN                 (1U)
#define PM_EVE2_PWRSTCTRL_LOWPOWERSTATECHANGE_DIS                (0U)

#define PM_EVE2_PWRSTST_POWERSTATEST_SHIFT                      (0U)
#define PM_EVE2_PWRSTST_POWERSTATEST_MASK                       (0x00000003U)
#define PM_EVE2_PWRSTST_POWERSTATEST_ON                          (3U)
#define PM_EVE2_PWRSTST_POWERSTATEST_OFF                         (0U)
#define PM_EVE2_PWRSTST_POWERSTATEST_RET                         (1U)
#define PM_EVE2_PWRSTST_POWERSTATEST_INACTIVE                    (2U)

#define PM_EVE2_PWRSTST_INTRANSITION_SHIFT                      (20U)
#define PM_EVE2_PWRSTST_INTRANSITION_MASK                       (0x00100000U)
#define PM_EVE2_PWRSTST_INTRANSITION_NO                          (0U)
#define PM_EVE2_PWRSTST_INTRANSITION_ONGOING                     (1U)

#define PM_EVE2_PWRSTST_LOGICSTATEST_SHIFT                      (2U)
#define PM_EVE2_PWRSTST_LOGICSTATEST_MASK                       (0x00000004U)
#define PM_EVE2_PWRSTST_LOGICSTATEST_ON                          (1U)
#define PM_EVE2_PWRSTST_LOGICSTATEST_OFF                         (0U)

#define PM_EVE2_PWRSTST_EVE2_BANK_STATEST_SHIFT                 (4U)
#define PM_EVE2_PWRSTST_EVE2_BANK_STATEST_MASK                  (0x00000030U)
#define PM_EVE2_PWRSTST_EVE2_BANK_STATEST_MEM_ON                 (3U)
#define PM_EVE2_PWRSTST_EVE2_BANK_STATEST_RESERVED1              (1U)
#define PM_EVE2_PWRSTST_EVE2_BANK_STATEST_MEM_OFF                (0U)
#define PM_EVE2_PWRSTST_EVE2_BANK_STATEST_RESERVED               (2U)

#define PM_EVE2_PWRSTST_LASTPOWERSTATEENTERED_SHIFT             (24U)
#define PM_EVE2_PWRSTST_LASTPOWERSTATEENTERED_MASK              (0x03000000U)
#define PM_EVE2_PWRSTST_LASTPOWERSTATEENTERED_ON                 (3U)
#define PM_EVE2_PWRSTST_LASTPOWERSTATEENTERED_OFF                (0U)
#define PM_EVE2_PWRSTST_LASTPOWERSTATEENTERED_RET                (1U)
#define PM_EVE2_PWRSTST_LASTPOWERSTATEENTERED_INACTIVE           (2U)

#define RM_EVE2_RSTCTRL_RST_EVE2_LRST_SHIFT                     (0U)
#define RM_EVE2_RSTCTRL_RST_EVE2_LRST_MASK                      (0x00000001U)
#define RM_EVE2_RSTCTRL_RST_EVE2_LRST_ASSERT                     (1U)
#define RM_EVE2_RSTCTRL_RST_EVE2_LRST_CLEAR                      (0U)

#define RM_EVE2_RSTCTRL_RST_EVE2_SHIFT                          (1U)
#define RM_EVE2_RSTCTRL_RST_EVE2_MASK                           (0x00000002U)
#define RM_EVE2_RSTCTRL_RST_EVE2_ASSERT                          (1U)
#define RM_EVE2_RSTCTRL_RST_EVE2_CLEAR                           (0U)

#define RM_EVE2_RSTST_RST_EVE2_EMU_SHIFT                        (2U)
#define RM_EVE2_RSTST_RST_EVE2_EMU_MASK                         (0x00000004U)
#define RM_EVE2_RSTST_RST_EVE2_EMU_RESET_YES                     (1U)
#define RM_EVE2_RSTST_RST_EVE2_EMU_RESET_NO                      (0U)

#define RM_EVE2_RSTST_RST_EVE2_LRST_SHIFT                       (0U)
#define RM_EVE2_RSTST_RST_EVE2_LRST_MASK                        (0x00000001U)
#define RM_EVE2_RSTST_RST_EVE2_LRST_RESET_YES                    (1U)
#define RM_EVE2_RSTST_RST_EVE2_LRST_RESET_NO                     (0U)

#define RM_EVE2_RSTST_RST_EVE2_SHIFT                            (1U)
#define RM_EVE2_RSTST_RST_EVE2_MASK                             (0x00000002U)
#define RM_EVE2_RSTST_RST_EVE2_RESET_YES                         (1U)
#define RM_EVE2_RSTST_RST_EVE2_RESET_NO                          (0U)

#define RM_EVE2_RSTST_RST_EVE2_EMU_REQ_SHIFT                    (3U)
#define RM_EVE2_RSTST_RST_EVE2_EMU_REQ_MASK                     (0x00000008U)
#define RM_EVE2_RSTST_RST_EVE2_EMU_REQ_RESET_YES                 (1U)
#define RM_EVE2_RSTST_RST_EVE2_EMU_REQ_RESET_NO                  (0U)

#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_MPU_SHIFT               (0U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_MPU_MASK                (0x00000001U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_MPU_ENABLED              (1U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_MPU_DISABLED             (0U)

#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_DSP1_SHIFT              (2U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_DSP1_MASK               (0x00000004U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_DSP1_ENABLED             (1U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_DSP1_DISABLED            (0U)

#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_IPU2_SHIFT              (1U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_IPU2_MASK               (0x00000002U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_IPU2_ENABLED             (1U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_IPU2_DISABLED            (0U)

#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_SDMA_SHIFT              (3U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_SDMA_MASK               (0x00000008U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_SDMA_ENABLED             (1U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_SDMA_DISABLED            (0U)

#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_IPU1_SHIFT              (4U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_IPU1_MASK               (0x00000010U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_IPU1_ENABLED             (1U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_IPU1_DISABLED            (0U)

#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_DSP2_SHIFT              (5U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_DSP2_MASK               (0x00000020U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_DSP2_ENABLED             (1U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_DSP2_DISABLED            (0U)

#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_EVE1_SHIFT              (6U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_EVE1_MASK               (0x00000040U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_EVE1_ENABLED             (1U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_EVE1_DISABLED            (0U)

#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_EVE3_SHIFT              (8U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_EVE3_MASK               (0x00000100U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_EVE3_ENABLED             (1U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_EVE3_DISABLED            (0U)

#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_EVE4_SHIFT              (9U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_EVE4_MASK               (0x00000200U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_EVE4_ENABLED             (1U)
#define PM_EVE2_EVE2_WKDEP_WKUPDEP_EVE2_EVE4_DISABLED            (0U)

#define RM_EVE2_EVE2_CONTEXT_LOSTCONTEXT_DFF_SHIFT              (0U)
#define RM_EVE2_EVE2_CONTEXT_LOSTCONTEXT_DFF_MASK               (0x00000001U)
#define RM_EVE2_EVE2_CONTEXT_LOSTCONTEXT_DFF_LOST                (1U)
#define RM_EVE2_EVE2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED          (0U)

#define RM_EVE2_EVE2_CONTEXT_LOSTMEM_EVE_BANK_SHIFT             (8U)
#define RM_EVE2_EVE2_CONTEXT_LOSTMEM_EVE_BANK_MASK              (0x00000100U)
#define RM_EVE2_EVE2_CONTEXT_LOSTMEM_EVE_BANK_LOST               (1U)
#define RM_EVE2_EVE2_CONTEXT_LOSTMEM_EVE_BANK_MAINTAINED         (0U)

#ifdef __cplusplus
}
#endif

#endif /* HW_EVE2_PRM_H_ */

