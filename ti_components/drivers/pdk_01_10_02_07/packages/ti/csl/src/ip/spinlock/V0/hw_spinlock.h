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
 */

/**
 *
 *  \file    hw_spinlock.h
 *
 *  \brief   register-level header file for SPINLOCK
 *
**/

#ifndef HW_SPINLOCK_H_
#define HW_SPINLOCK_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define SPINLOCK_REVISION                                                                                  (0x0U)
#define SPINLOCK_SYSCONFIG                                                                                 (0x10U)
#define SPINLOCK_SYSTATUS                                                                                  (0x14U)
#define SPINLOCK_LOCK_REG(n)                                                                               ((uint32_t)0x800U + ((n) * 4U))

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define SPINLOCK_SYSCONFIG_AUTOGATING_SHIFT                                                               (0U)
#define SPINLOCK_SYSCONFIG_AUTOGATING_MASK                                                                (0x00000001U)
#define SPINLOCK_SYSCONFIG_AUTOGATING_FREERUNNING                                                         (0U)
#define SPINLOCK_SYSCONFIG_AUTOGATING_GATED                                                               (1U)

#define SPINLOCK_SYSCONFIG_SOFTRESET_SHIFT                                                                (1U)
#define SPINLOCK_SYSCONFIG_SOFTRESET_MASK                                                                 (0x00000002U)
#define SPINLOCK_SYSCONFIG_SOFTRESET_NOOP                                                                 (0U)
#define SPINLOCK_SYSCONFIG_SOFTRESET_DORESET                                                              (1U)

#define SPINLOCK_SYSCONFIG_ENWAKEUP_SHIFT                                                                 (2U)
#define SPINLOCK_SYSCONFIG_ENWAKEUP_MASK                                                                  (0x00000004U)
#define SPINLOCK_SYSCONFIG_ENWAKEUP_NOWAKEUPGEN                                                           (0U)
#define SPINLOCK_SYSCONFIG_ENWAKEUP_WAKEUPGEN1                                                            (1U)

#define SPINLOCK_SYSCONFIG_SIDLEMODE_SHIFT                                                                (3U)
#define SPINLOCK_SYSCONFIG_SIDLEMODE_MASK                                                                 (0x00000018U)
#define SPINLOCK_SYSCONFIG_SIDLEMODE_FORCEIDLE                                                            (0U)
#define SPINLOCK_SYSCONFIG_SIDLEMODE_NOIDLE                                                               (1U)
#define SPINLOCK_SYSCONFIG_SIDLEMODE_SMARTIDLE                                                            (2U)
#define SPINLOCK_SYSCONFIG_SIDLEMODE_UNUSED3                                                              (3U)

#define SPINLOCK_SYSCONFIG_RESERVED0_SHIFT                                                                (5U)
#define SPINLOCK_SYSCONFIG_RESERVED0_MASK                                                                 (0x000000e0U)

#define SPINLOCK_SYSCONFIG_RESERVED1_SHIFT                                                                (9U)
#define SPINLOCK_SYSCONFIG_RESERVED1_MASK                                                                 (0xfffffe00U)

#define SPINLOCK_SYSTATUS_IU0_SHIFT                                                                       (8U)
#define SPINLOCK_SYSTATUS_IU0_MASK                                                                        (0x00000100U)

#define SPINLOCK_SYSTATUS_IU1_SHIFT                                                                       (9U)
#define SPINLOCK_SYSTATUS_IU1_MASK                                                                        (0x00000200U)

#define SPINLOCK_SYSTATUS_IU2_SHIFT                                                                       (10U)
#define SPINLOCK_SYSTATUS_IU2_MASK                                                                        (0x00000400U)

#define SPINLOCK_SYSTATUS_IU3_SHIFT                                                                       (11U)
#define SPINLOCK_SYSTATUS_IU3_MASK                                                                        (0x00000800U)

#define SPINLOCK_SYSTATUS_IU4_SHIFT                                                                       (12U)
#define SPINLOCK_SYSTATUS_IU4_MASK                                                                        (0x00001000U)

#define SPINLOCK_SYSTATUS_IU5_SHIFT                                                                       (13U)
#define SPINLOCK_SYSTATUS_IU5_MASK                                                                        (0x00002000U)

#define SPINLOCK_SYSTATUS_IU6_SHIFT                                                                       (14U)
#define SPINLOCK_SYSTATUS_IU6_MASK                                                                        (0x00004000U)

#define SPINLOCK_SYSTATUS_IU7_SHIFT                                                                       (15U)
#define SPINLOCK_SYSTATUS_IU7_MASK                                                                        (0x00008000U)

#define SPINLOCK_SYSTATUS_RESERVED_SHIFT                                                                  (16U)
#define SPINLOCK_SYSTATUS_RESERVED_MASK                                                                   (0x00ff0000U)

#define SPINLOCK_SYSTATUS_NUMLOCKS_SHIFT                                                                  (24U)
#define SPINLOCK_SYSTATUS_NUMLOCKS_MASK                                                                   (0xff000000U)
#define SPINLOCK_SYSTATUS_NUMLOCKS_32LOCKS                                                                (1U)
#define SPINLOCK_SYSTATUS_NUMLOCKS_64LOCKS                                                                (2U)
#define SPINLOCK_SYSTATUS_NUMLOCKS_128LOCKS                                                               (4U)
#define SPINLOCK_SYSTATUS_NUMLOCKS_256LOCKS                                                               (8U)

#define SPINLOCK_SYSTATUS_RESETDONE_SHIFT                                                                 (0U)
#define SPINLOCK_SYSTATUS_RESETDONE_MASK                                                                  (0x00000001U)

#define SPINLOCK_SYSTATUS_RESERVED1_SHIFT                                                                 (1U)
#define SPINLOCK_SYSTATUS_RESERVED1_MASK                                                                  (0x000000feU)

#define SPINLOCK_LOCK_REG_TAKEN_SHIFT                                                                     (0U)
#define SPINLOCK_LOCK_REG_TAKEN_MASK                                                                      (0x00000001U)
#define SPINLOCK_LOCK_REG_TAKEN_FREE                                                                      (0U)
#define SPINLOCK_LOCK_REG_TAKEN_BUSY                                                                      (1U)

#define SPINLOCK_LOCK_REG_RESERVED_SHIFT                                                                  (1U)
#define SPINLOCK_LOCK_REG_RESERVED_MASK                                                                   (0xfffffffeU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_SPINLOCK_H_ */
