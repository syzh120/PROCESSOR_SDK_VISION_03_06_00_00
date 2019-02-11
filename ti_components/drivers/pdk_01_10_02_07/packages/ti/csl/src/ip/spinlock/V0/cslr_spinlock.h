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
#ifndef CSLR_SPINLOCK_H
#define CSLR_SPINLOCK_H

#ifdef __cplusplus
extern "C"
{
#endif

/**************************************************************************
* Register Overlay Structure for __ALL__
**************************************************************************/
typedef struct {
    volatile Uint32 REVISION;
    volatile Uint8  RSVD0[12];
    volatile Uint32 SYSCONFIG;
    volatile Uint32 SYSTATUS;
    volatile Uint8  RSVD1[2024];
    volatile Uint32 LOCK_REG[32];
} CSL_SpinlockRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

/* Read-only IP revision identifier (X.Y.R) used by software to determine
 * features, bugs and compatibility of an instance of this the Spin Lock
 * module. */
#define CSL_SPINLOCK_REVISION                                   (0x0U)

/* This register controls the various parameters of the OCP interface. Note
 * that several fields are present by read-only. */
#define CSL_SPINLOCK_SYSCONFIG                                  (0x10U)

/* This register provides status information about this instance of the Spin
 * Lock module. */
#define CSL_SPINLOCK_SYSTATUS                                   (0x14U)

/* This register is read when attempting to acquire a lock. The lock is
 * automatically taken if it was not taken and the value returned by the read
 * is zero. If the lock was already taken, then the read returns one. Writing
 * a zero to this register frees the lock. */
#define CSL_SPINLOCK_LOCK_REG(i)                                (0x800U + ((i) * (0x4U)))


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* REVISION */

#define CSL_SPINLOCK_REVISION_Y_MINOR_MASK                      (0x0000003FU)
#define CSL_SPINLOCK_REVISION_Y_MINOR_SHIFT                     (0U)
#define CSL_SPINLOCK_REVISION_Y_MINOR_RESETVAL                  (0x00000000U)
#define CSL_SPINLOCK_REVISION_Y_MINOR_MAX                       (0x0000003fU)

#define CSL_SPINLOCK_REVISION_CUSTOM_MASK                       (0x000000C0U)
#define CSL_SPINLOCK_REVISION_CUSTOM_SHIFT                      (6U)
#define CSL_SPINLOCK_REVISION_CUSTOM_RESETVAL                   (0x00000000U)
#define CSL_SPINLOCK_REVISION_CUSTOM_MAX                        (0x00000003U)

#define CSL_SPINLOCK_REVISION_X_MAJOR_MASK                      (0x00000700U)
#define CSL_SPINLOCK_REVISION_X_MAJOR_SHIFT                     (8U)
#define CSL_SPINLOCK_REVISION_X_MAJOR_RESETVAL                  (0x00000000U)
#define CSL_SPINLOCK_REVISION_X_MAJOR_MAX                       (0x00000007U)

#define CSL_SPINLOCK_REVISION_R_RTL_MASK                        (0x0000F800U)
#define CSL_SPINLOCK_REVISION_R_RTL_SHIFT                       (11U)
#define CSL_SPINLOCK_REVISION_R_RTL_RESETVAL                    (0x00000000U)
#define CSL_SPINLOCK_REVISION_R_RTL_MAX                         (0x0000001fU)

#define CSL_SPINLOCK_REVISION_FUNC_MASK                         (0x0FFF0000U)
#define CSL_SPINLOCK_REVISION_FUNC_SHIFT                        (16U)
#define CSL_SPINLOCK_REVISION_FUNC_RESETVAL                     (0x00000002U)
#define CSL_SPINLOCK_REVISION_FUNC_MAX                          (0x00000fffU)

#define CSL_SPINLOCK_REVISION_SCHEME_MASK                       (0xC0000000U)
#define CSL_SPINLOCK_REVISION_SCHEME_SHIFT                      (30U)
#define CSL_SPINLOCK_REVISION_SCHEME_RESETVAL                   (0x00000001U)
#define CSL_SPINLOCK_REVISION_SCHEME_LEGACY                     (0x00000000U)
#define CSL_SPINLOCK_REVISION_SCHEME_HIGHLANDER                 (0x00000001U)

#define CSL_SPINLOCK_REVISION_RESETVAL                          (0x50020000U)

/* SYSCONFIG */

#define CSL_SPINLOCK_SYSCONFIG_AUTOGATING_MASK                  (0x00000001U)
#define CSL_SPINLOCK_SYSCONFIG_AUTOGATING_SHIFT                 (0U)
#define CSL_SPINLOCK_SYSCONFIG_AUTOGATING_RESETVAL              (0x00000001U)
#define CSL_SPINLOCK_SYSCONFIG_AUTOGATING_FREERUNNING           (0x00000000U)
#define CSL_SPINLOCK_SYSCONFIG_AUTOGATING_GATED                 (0x00000001U)

#define CSL_SPINLOCK_SYSCONFIG_SOFTRESET_MASK                   (0x00000002U)
#define CSL_SPINLOCK_SYSCONFIG_SOFTRESET_SHIFT                  (1U)
#define CSL_SPINLOCK_SYSCONFIG_SOFTRESET_RESETVAL               (0x00000000U)
#define CSL_SPINLOCK_SYSCONFIG_SOFTRESET_NOOP                   (0x00000000U)
#define CSL_SPINLOCK_SYSCONFIG_SOFTRESET_DORESET                (0x00000001U)

#define CSL_SPINLOCK_SYSCONFIG_ENWAKEUP_MASK                    (0x00000004U)
#define CSL_SPINLOCK_SYSCONFIG_ENWAKEUP_SHIFT                   (2U)
#define CSL_SPINLOCK_SYSCONFIG_ENWAKEUP_RESETVAL                (0x00000000U)
#define CSL_SPINLOCK_SYSCONFIG_ENWAKEUP_NOWAKEUPGEN             (0x00000000U)
#define CSL_SPINLOCK_SYSCONFIG_ENWAKEUP_WAKEUPGEN1              (0x00000001U)

#define CSL_SPINLOCK_SYSCONFIG_SIDLEMODE_MASK                   (0x00000018U)
#define CSL_SPINLOCK_SYSCONFIG_SIDLEMODE_SHIFT                  (3U)
#define CSL_SPINLOCK_SYSCONFIG_SIDLEMODE_RESETVAL               (0x00000002U)
#define CSL_SPINLOCK_SYSCONFIG_SIDLEMODE_FORCEIDLE              (0x00000000U)
#define CSL_SPINLOCK_SYSCONFIG_SIDLEMODE_NOIDLE                 (0x00000001U)
#define CSL_SPINLOCK_SYSCONFIG_SIDLEMODE_SMARTIDLE              (0x00000002U)
#define CSL_SPINLOCK_SYSCONFIG_SIDLEMODE_UNUSED3                (0x00000003U)

#define CSL_SPINLOCK_SYSCONFIG_CLOCKACTIVITYOCP_MASK            (0x00000100U)
#define CSL_SPINLOCK_SYSCONFIG_CLOCKACTIVITYOCP_SHIFT           (8U)
#define CSL_SPINLOCK_SYSCONFIG_CLOCKACTIVITYOCP_RESETVAL        (0x00000000U)
#define CSL_SPINLOCK_SYSCONFIG_CLOCKACTIVITYOCP_NOTREQUIRED     (0x00000000U)
#define CSL_SPINLOCK_SYSCONFIG_CLOCKACTIVITYOCP_REQUIRED        (0x00000001U)

#define CSL_SPINLOCK_SYSCONFIG_RESETVAL                         (0x00000011U)

/* SYSTATUS */

#define CSL_SPINLOCK_SYSTATUS_IU0_MASK                          (0x00000100U)
#define CSL_SPINLOCK_SYSTATUS_IU0_SHIFT                         (8U)
#define CSL_SPINLOCK_SYSTATUS_IU0_RESETVAL                      (0x00000000U)
#define CSL_SPINLOCK_SYSTATUS_IU0_MAX                           (0x00000001U)

#define CSL_SPINLOCK_SYSTATUS_IU1_MASK                          (0x00000200U)
#define CSL_SPINLOCK_SYSTATUS_IU1_SHIFT                         (9U)
#define CSL_SPINLOCK_SYSTATUS_IU1_RESETVAL                      (0x00000000U)
#define CSL_SPINLOCK_SYSTATUS_IU1_MAX                           (0x00000001U)

#define CSL_SPINLOCK_SYSTATUS_IU2_MASK                          (0x00000400U)
#define CSL_SPINLOCK_SYSTATUS_IU2_SHIFT                         (10U)
#define CSL_SPINLOCK_SYSTATUS_IU2_RESETVAL                      (0x00000000U)
#define CSL_SPINLOCK_SYSTATUS_IU2_MAX                           (0x00000001U)

#define CSL_SPINLOCK_SYSTATUS_IU3_MASK                          (0x00000800U)
#define CSL_SPINLOCK_SYSTATUS_IU3_SHIFT                         (11U)
#define CSL_SPINLOCK_SYSTATUS_IU3_RESETVAL                      (0x00000000U)
#define CSL_SPINLOCK_SYSTATUS_IU3_MAX                           (0x00000001U)

#define CSL_SPINLOCK_SYSTATUS_IU4_MASK                          (0x00001000U)
#define CSL_SPINLOCK_SYSTATUS_IU4_SHIFT                         (12U)
#define CSL_SPINLOCK_SYSTATUS_IU4_RESETVAL                      (0x00000000U)
#define CSL_SPINLOCK_SYSTATUS_IU4_MAX                           (0x00000001U)

#define CSL_SPINLOCK_SYSTATUS_IU5_MASK                          (0x00002000U)
#define CSL_SPINLOCK_SYSTATUS_IU5_SHIFT                         (13U)
#define CSL_SPINLOCK_SYSTATUS_IU5_RESETVAL                      (0x00000000U)
#define CSL_SPINLOCK_SYSTATUS_IU5_MAX                           (0x00000001U)

#define CSL_SPINLOCK_SYSTATUS_IU6_MASK                          (0x00004000U)
#define CSL_SPINLOCK_SYSTATUS_IU6_SHIFT                         (14U)
#define CSL_SPINLOCK_SYSTATUS_IU6_RESETVAL                      (0x00000000U)
#define CSL_SPINLOCK_SYSTATUS_IU6_MAX                           (0x00000001U)

#define CSL_SPINLOCK_SYSTATUS_IU7_MASK                          (0x00008000U)
#define CSL_SPINLOCK_SYSTATUS_IU7_SHIFT                         (15U)
#define CSL_SPINLOCK_SYSTATUS_IU7_RESETVAL                      (0x00000000U)
#define CSL_SPINLOCK_SYSTATUS_IU7_MAX                           (0x00000001U)

#define CSL_SPINLOCK_SYSTATUS_NUMLOCKS_MASK                     (0xFF000000U)
#define CSL_SPINLOCK_SYSTATUS_NUMLOCKS_SHIFT                    (24U)
#define CSL_SPINLOCK_SYSTATUS_NUMLOCKS_RESETVAL                 (0x00000008U)
#define CSL_SPINLOCK_SYSTATUS_NUMLOCKS_MAX                      (0x000000ffU)

#define CSL_SPINLOCK_SYSTATUS_RESETDONE_MASK                    (0x00000001U)
#define CSL_SPINLOCK_SYSTATUS_RESETDONE_SHIFT                   (0U)
#define CSL_SPINLOCK_SYSTATUS_RESETDONE_RESETVAL                (0x00000001U)
#define CSL_SPINLOCK_SYSTATUS_RESETDONE_MAX                     (0x00000001U)

#define CSL_SPINLOCK_SYSTATUS_RESETVAL                          (0x09000001U)

/* LOCK_REG */

#define CSL_SPINLOCK_LOCK_REG_TAKEN_MASK                        (0x00000001U)
#define CSL_SPINLOCK_LOCK_REG_TAKEN_SHIFT                       (0U)
#define CSL_SPINLOCK_LOCK_REG_TAKEN_RESETVAL                    (0x00000000U)
#define CSL_SPINLOCK_LOCK_REG_TAKEN_FREE                        (0x00000000U)
#define CSL_SPINLOCK_LOCK_REG_TAKEN_BUSY                        (0x00000001U)

#define CSL_SPINLOCK_LOCK_REG_RESETVAL                          (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
