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
 *  \file   hw_gpu_prm.h
 *
 *  \brief  Register-level header file for PRCM
 *
**/

#ifndef HW_GPU_PRM_H_
#define HW_GPU_PRM_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define PM_GPU_PWRSTCTRL                                        (0x0U)
#define PM_GPU_PWRSTST                                          (0x4U)
#define RM_GPU_GPU_CONTEXT                                      (0x24U)


/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define PM_GPU_PWRSTCTRL_GPU_MEM_ONSTATE_SHIFT                  (16U)
#define PM_GPU_PWRSTCTRL_GPU_MEM_ONSTATE_MASK                   (0x00030000U)
#define PM_GPU_PWRSTCTRL_GPU_MEM_ONSTATE_MEM_ON                  (3U)

#define PM_GPU_PWRSTCTRL_POWERSTATE_SHIFT                       (0U)
#define PM_GPU_PWRSTCTRL_POWERSTATE_MASK                        (0x00000003U)
#define PM_GPU_PWRSTCTRL_POWERSTATE_OFF                          (0U)
#define PM_GPU_PWRSTCTRL_POWERSTATE_INACT                        (2U)
#define PM_GPU_PWRSTCTRL_POWERSTATE_RESERVED                     (1U)
#define PM_GPU_PWRSTCTRL_POWERSTATE_ON                           (3U)

#define PM_GPU_PWRSTCTRL_LOWPOWERSTATECHANGE_SHIFT              (4U)
#define PM_GPU_PWRSTCTRL_LOWPOWERSTATECHANGE_MASK               (0x00000010U)
#define PM_GPU_PWRSTCTRL_LOWPOWERSTATECHANGE_EN                  (1U)
#define PM_GPU_PWRSTCTRL_LOWPOWERSTATECHANGE_DIS                 (0U)

#define PM_GPU_PWRSTST_POWERSTATEST_SHIFT                       (0U)
#define PM_GPU_PWRSTST_POWERSTATEST_MASK                        (0x00000003U)
#define PM_GPU_PWRSTST_POWERSTATEST_ON                           (3U)
#define PM_GPU_PWRSTST_POWERSTATEST_OFF                          (0U)
#define PM_GPU_PWRSTST_POWERSTATEST_RET                          (1U)
#define PM_GPU_PWRSTST_POWERSTATEST_INACTIVE                     (2U)

#define PM_GPU_PWRSTST_INTRANSITION_SHIFT                       (20U)
#define PM_GPU_PWRSTST_INTRANSITION_MASK                        (0x00100000U)
#define PM_GPU_PWRSTST_INTRANSITION_NO                           (0U)
#define PM_GPU_PWRSTST_INTRANSITION_ONGOING                      (1U)

#define PM_GPU_PWRSTST_LOGICSTATEST_SHIFT                       (2U)
#define PM_GPU_PWRSTST_LOGICSTATEST_MASK                        (0x00000004U)
#define PM_GPU_PWRSTST_LOGICSTATEST_ON                           (1U)
#define PM_GPU_PWRSTST_LOGICSTATEST_OFF                          (0U)

#define PM_GPU_PWRSTST_GPU_MEM_STATEST_SHIFT                    (4U)
#define PM_GPU_PWRSTST_GPU_MEM_STATEST_MASK                     (0x00000030U)
#define PM_GPU_PWRSTST_GPU_MEM_STATEST_MEM_ON                    (3U)
#define PM_GPU_PWRSTST_GPU_MEM_STATEST_RESERVED1                 (1U)
#define PM_GPU_PWRSTST_GPU_MEM_STATEST_MEM_OFF                   (0U)
#define PM_GPU_PWRSTST_GPU_MEM_STATEST_RESERVED                  (2U)

#define PM_GPU_PWRSTST_LASTPOWERSTATEENTERED_SHIFT              (24U)
#define PM_GPU_PWRSTST_LASTPOWERSTATEENTERED_MASK               (0x03000000U)
#define PM_GPU_PWRSTST_LASTPOWERSTATEENTERED_ON                  (3U)
#define PM_GPU_PWRSTST_LASTPOWERSTATEENTERED_OFF                 (0U)
#define PM_GPU_PWRSTST_LASTPOWERSTATEENTERED_RET                 (1U)
#define PM_GPU_PWRSTST_LASTPOWERSTATEENTERED_INACTIVE            (2U)

#define RM_GPU_GPU_CONTEXT_LOSTCONTEXT_DFF_SHIFT                (0U)
#define RM_GPU_GPU_CONTEXT_LOSTCONTEXT_DFF_MASK                 (0x00000001U)
#define RM_GPU_GPU_CONTEXT_LOSTCONTEXT_DFF_LOST                  (1U)
#define RM_GPU_GPU_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED            (0U)

#define RM_GPU_GPU_CONTEXT_LOSTMEM_GPU_MEM_SHIFT                (8U)
#define RM_GPU_GPU_CONTEXT_LOSTMEM_GPU_MEM_MASK                 (0x00000100U)
#define RM_GPU_GPU_CONTEXT_LOSTMEM_GPU_MEM_LOST                  (1U)
#define RM_GPU_GPU_CONTEXT_LOSTMEM_GPU_MEM_MAINTAINED            (0U)

#ifdef __cplusplus
}
#endif

#endif /* HW_GPU_PRM_H_ */

