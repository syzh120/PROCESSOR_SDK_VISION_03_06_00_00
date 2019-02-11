/*
 *  Copyright (C) 2008-2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   hw_rtc_prm.h
 *
 *  \brief  Register-level header file for PRCM
 *
**/

#ifndef HW_RTC_PRM_H_
#define HW_RTC_PRM_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define PM_RTC_RTCSS_WKDEP                                      (0x0U)
#define RM_RTC_RTCSS_CONTEXT                                    (0x4U)


/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_MPU_SHIFT           (0U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_MPU_MASK            (0x00000001U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_MPU_ENABLED          (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_MPU_DISABLED         (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_IPU2_SHIFT          (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_IPU2_MASK           (0x00000002U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_IPU2_ENABLED         (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_IPU2_DISABLED        (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_DSP1_SHIFT          (2U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_DSP1_MASK           (0x00000004U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_DSP1_ENABLED         (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_DSP1_DISABLED        (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_IPU1_SHIFT          (4U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_IPU1_MASK           (0x00000010U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_IPU1_ENABLED         (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_IPU1_DISABLED        (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_DSP2_SHIFT          (5U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_DSP2_MASK           (0x00000020U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_DSP2_ENABLED         (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_DSP2_DISABLED        (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE1_SHIFT          (6U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE1_MASK           (0x00000040U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE1_ENABLED         (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE1_DISABLED        (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE2_SHIFT          (7U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE2_MASK           (0x00000080U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE2_ENABLED         (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE2_DISABLED        (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE3_SHIFT          (8U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE3_MASK           (0x00000100U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE3_ENABLED         (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE3_DISABLED        (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE4_SHIFT          (9U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE4_MASK           (0x00000200U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE4_ENABLED         (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE4_DISABLED        (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_MPU_SHIFT           (10U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_MPU_MASK            (0x00000400U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_MPU_ENABLED          (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_MPU_DISABLED         (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_IPU2_SHIFT          (11U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_IPU2_MASK           (0x00000800U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_IPU2_ENABLED         (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_IPU2_DISABLED        (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_DSP1_SHIFT          (12U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_DSP1_MASK           (0x00001000U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_DSP1_ENABLED         (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_DSP1_DISABLED        (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_IPU1_SHIFT          (14U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_IPU1_MASK           (0x00004000U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_IPU1_ENABLED         (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_IPU1_DISABLED        (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_DSP2_SHIFT          (15U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_DSP2_MASK           (0x00008000U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_DSP2_ENABLED         (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_DSP2_DISABLED        (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE1_SHIFT          (16U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE1_MASK           (0x00010000U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE1_ENABLED         (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE1_DISABLED        (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE2_SHIFT          (17U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE2_MASK           (0x00020000U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE2_ENABLED         (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE2_DISABLED        (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE3_SHIFT          (18U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE3_MASK           (0x00040000U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE3_ENABLED         (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE3_DISABLED        (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE4_SHIFT          (19U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE4_MASK           (0x00080000U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE4_ENABLED         (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE4_DISABLED        (0U)

#define RM_RTC_RTCSS_CONTEXT_LOSTCONTEXT_DFF_SHIFT              (0U)
#define RM_RTC_RTCSS_CONTEXT_LOSTCONTEXT_DFF_MASK               (0x00000001U)
#define RM_RTC_RTCSS_CONTEXT_LOSTCONTEXT_DFF_LOST                (1U)
#define RM_RTC_RTCSS_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED          (0U)

#ifdef __cplusplus
}
#endif

#endif /* HW_RTC_PRM_H_ */

