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
 *  \file   hw_mpu_prm.h
 *
 *  \brief  Register-level header file for PRCM
 *
**/

#ifndef HW_MPU_PRM_H_
#define HW_MPU_PRM_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define PM_MPU_PWRSTCTRL                                        (0x0U)
#define PM_MPU_PWRSTST                                          (0x4U)
#define RM_MPU_MPU_CONTEXT                                      (0x24U)


/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define PM_MPU_PWRSTCTRL_POWERSTATE_SHIFT                       (0U)
#define PM_MPU_PWRSTCTRL_POWERSTATE_MASK                        (0x00000003U)
#define PM_MPU_PWRSTCTRL_POWERSTATE_RESERVED                     (0U)
#define PM_MPU_PWRSTCTRL_POWERSTATE_INACT                        (2U)
#define PM_MPU_PWRSTCTRL_POWERSTATE_RET                          (1U)
#define PM_MPU_PWRSTCTRL_POWERSTATE_ON                           (3U)

#define PM_MPU_PWRSTCTRL_MPU_L2_RETSTATE_SHIFT                  (9U)
#define PM_MPU_PWRSTCTRL_MPU_L2_RETSTATE_MASK                   (0x00000200U)
#define PM_MPU_PWRSTCTRL_MPU_L2_RETSTATE_MEM_RET                 (1U)
#define PM_MPU_PWRSTCTRL_MPU_L2_RETSTATE_MEM_OFF                 (0U)

#define PM_MPU_PWRSTCTRL_MPU_RAM_RETSTATE_SHIFT                 (10U)
#define PM_MPU_PWRSTCTRL_MPU_RAM_RETSTATE_MASK                  (0x00000400U)
#define PM_MPU_PWRSTCTRL_MPU_RAM_RETSTATE_MEM_RET                (1U)

#define PM_MPU_PWRSTCTRL_MPU_L2_ONSTATE_SHIFT                   (18U)
#define PM_MPU_PWRSTCTRL_MPU_L2_ONSTATE_MASK                    (0x000c0000U)
#define PM_MPU_PWRSTCTRL_MPU_L2_ONSTATE_MEM_ON                   (3U)

#define PM_MPU_PWRSTCTRL_MPU_RAM_ONSTATE_SHIFT                  (20U)
#define PM_MPU_PWRSTCTRL_MPU_RAM_ONSTATE_MASK                   (0x00300000U)
#define PM_MPU_PWRSTCTRL_MPU_RAM_ONSTATE_MEM_ON                  (3U)

#define PM_MPU_PWRSTCTRL_LOWPOWERSTATECHANGE_SHIFT              (4U)
#define PM_MPU_PWRSTCTRL_LOWPOWERSTATECHANGE_MASK               (0x00000010U)
#define PM_MPU_PWRSTCTRL_LOWPOWERSTATECHANGE_DIS                 (0U)

#define PM_MPU_PWRSTCTRL_LOGICRETSTATE_SHIFT                    (2U)
#define PM_MPU_PWRSTCTRL_LOGICRETSTATE_MASK                     (0x00000004U)
#define PM_MPU_PWRSTCTRL_LOGICRETSTATE_LOGIC_RET                 (1U)
#define PM_MPU_PWRSTCTRL_LOGICRETSTATE_LOGIC_OFF                 (0U)

#define PM_MPU_PWRSTST_POWERSTATEST_SHIFT                       (0U)
#define PM_MPU_PWRSTST_POWERSTATEST_MASK                        (0x00000003U)
#define PM_MPU_PWRSTST_POWERSTATEST_ON                           (3U)
#define PM_MPU_PWRSTST_POWERSTATEST_OFF                          (0U)
#define PM_MPU_PWRSTST_POWERSTATEST_RET                          (1U)
#define PM_MPU_PWRSTST_POWERSTATEST_INACTIVE                     (2U)

#define PM_MPU_PWRSTST_INTRANSITION_SHIFT                       (20U)
#define PM_MPU_PWRSTST_INTRANSITION_MASK                        (0x00100000U)
#define PM_MPU_PWRSTST_INTRANSITION_NO                           (0U)
#define PM_MPU_PWRSTST_INTRANSITION_ONGOING                      (1U)

#define PM_MPU_PWRSTST_LOGICSTATEST_SHIFT                       (2U)
#define PM_MPU_PWRSTST_LOGICSTATEST_MASK                        (0x00000004U)
#define PM_MPU_PWRSTST_LOGICSTATEST_ON                           (1U)
#define PM_MPU_PWRSTST_LOGICSTATEST_OFF                          (0U)

#define PM_MPU_PWRSTST_MPU_L2_STATEST_SHIFT                     (6U)
#define PM_MPU_PWRSTST_MPU_L2_STATEST_MASK                      (0x000000c0U)
#define PM_MPU_PWRSTST_MPU_L2_STATEST_MEM_ON                     (3U)
#define PM_MPU_PWRSTST_MPU_L2_STATEST_MEM_RET                    (1U)
#define PM_MPU_PWRSTST_MPU_L2_STATEST_MEM_OFF                    (0U)
#define PM_MPU_PWRSTST_MPU_L2_STATEST_RESERVED                   (2U)

#define PM_MPU_PWRSTST_MPU_RAM_STATEST_SHIFT                    (8U)
#define PM_MPU_PWRSTST_MPU_RAM_STATEST_MASK                     (0x00000300U)
#define PM_MPU_PWRSTST_MPU_RAM_STATEST_MEM_ON                    (3U)
#define PM_MPU_PWRSTST_MPU_RAM_STATEST_MEM_RET                   (1U)
#define PM_MPU_PWRSTST_MPU_RAM_STATEST_MEM_OFF                   (0U)
#define PM_MPU_PWRSTST_MPU_RAM_STATEST_RESERVED                  (2U)

#define PM_MPU_PWRSTST_LASTPOWERSTATEENTERED_SHIFT              (24U)
#define PM_MPU_PWRSTST_LASTPOWERSTATEENTERED_MASK               (0x03000000U)
#define PM_MPU_PWRSTST_LASTPOWERSTATEENTERED_ON                  (3U)
#define PM_MPU_PWRSTST_LASTPOWERSTATEENTERED_OFF                 (0U)
#define PM_MPU_PWRSTST_LASTPOWERSTATEENTERED_RET                 (1U)
#define PM_MPU_PWRSTST_LASTPOWERSTATEENTERED_INACTIVE            (2U)

#define RM_MPU_MPU_CONTEXT_LOSTCONTEXT_DFF_SHIFT                (0U)
#define RM_MPU_MPU_CONTEXT_LOSTCONTEXT_DFF_MASK                 (0x00000001U)
#define RM_MPU_MPU_CONTEXT_LOSTCONTEXT_DFF_LOST                  (1U)
#define RM_MPU_MPU_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED            (0U)

#define RM_MPU_MPU_CONTEXT_LOSTMEM_MPU_L2_SHIFT                 (9U)
#define RM_MPU_MPU_CONTEXT_LOSTMEM_MPU_L2_MASK                  (0x00000200U)
#define RM_MPU_MPU_CONTEXT_LOSTMEM_MPU_L2_LOST                   (1U)
#define RM_MPU_MPU_CONTEXT_LOSTMEM_MPU_L2_MAINTAINED             (0U)

#define RM_MPU_MPU_CONTEXT_LOSTMEM_MPU_RAM_SHIFT                (10U)
#define RM_MPU_MPU_CONTEXT_LOSTMEM_MPU_RAM_MASK                 (0x00000400U)
#define RM_MPU_MPU_CONTEXT_LOSTMEM_MPU_RAM_LOST                  (1U)
#define RM_MPU_MPU_CONTEXT_LOSTMEM_MPU_RAM_MAINTAINED            (0U)

#define RM_MPU_MPU_CONTEXT_LOSTCONTEXT_RFF_SHIFT                (1U)
#define RM_MPU_MPU_CONTEXT_LOSTCONTEXT_RFF_MASK                 (0x00000002U)
#define RM_MPU_MPU_CONTEXT_LOSTCONTEXT_RFF_LOST                  (1U)
#define RM_MPU_MPU_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED            (0U)

#ifdef __cplusplus
}
#endif

#endif /* HW_MPU_PRM_H_ */

