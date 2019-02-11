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
 *  \file   spinlock.c
 *
 *  \brief  Spinlock APIs.
 *
 *  This file contains the device abstraction layer APIs for Spinlock.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_spinlock.h>

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
uint32_t SPINLOCKRevision(uint32_t baseAddr)
{
    uint32_t ret;

    ret = HW_RD_REG32(baseAddr + SPINLOCK_REVISION);

    return (ret);
}

uint32_t SPINLOCKSystatus(uint32_t baseAddr)
{
    uint32_t status;

    status = HW_RD_FIELD32(baseAddr + SPINLOCK_SYSTATUS,
                           SPINLOCK_SYSTATUS_RESETDONE);

    return (status);
}

uint32_t SPINLOCKSystatusIU0(uint32_t baseAddr)
{
    uint32_t status;

    status = HW_RD_FIELD32(baseAddr + SPINLOCK_SYSTATUS,
                           SPINLOCK_SYSTATUS_IU0);

    return (status);
}

void SPINLOCKModuleReset(uint32_t baseAddr)
{
    /*
     * Setting the SOFTRESET bit in System Configuration register.
     * Doing so would reset the Spinlock module.
     */
    HW_WR_FIELD32(baseAddr + SPINLOCK_SYSCONFIG,
                  SPINLOCK_SYSCONFIG_SOFTRESET,
                  SPINLOCK_SYSCONFIG_SOFTRESET_DORESET);

    /* Waiting until the Spinlock Module is reset.*/
    while (0U == HW_RD_FIELD32(baseAddr + SPINLOCK_SYSTATUS,
                               SPINLOCK_SYSTATUS_RESETDONE))
    {
        /* Do nothing - Busy wait */
    }
}

uint32_t SPINLOCKLockStatusSet(uint32_t baseAddr, uint32_t lockNumber)
{
    uint32_t lockStatus;

    lockStatus = HW_RD_FIELD32(baseAddr + SPINLOCK_LOCK_REG(lockNumber),
                               SPINLOCK_LOCK_REG_TAKEN);

    return (lockStatus);
}

void SPINLOCKLockStatusFree(uint32_t baseAddr, uint32_t lockNumber)
{
    HW_WR_FIELD32(baseAddr + SPINLOCK_LOCK_REG(lockNumber),
                  SPINLOCK_LOCK_REG_TAKEN,
                  SPINLOCK_LOCK_REG_TAKEN_FREE);
}
/********************************* End of file ******************************/


