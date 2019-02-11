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
 *  \ingroup CSL_IP_MODULE
 *  \defgroup CSL_SPINLOCK Spinlock
 *
 *  @{
 */
/**
 *  \file   spinlock.h
 *
 *  \brief  Spinlock APIs and macros.
 *
 *  This file contains the prototypes of the APIs present in the
 *  device abstraction layer file of Spinlock.
 *  This may also contains some related macros.
 */

#ifndef  SPINLOCK_H_
#define  SPINLOCK_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/cslr_spinlock.h>

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This API provides the SPINLOCK_REVISION of the SPINLOCK module.\n
 *
 * \param   baseAddr       Memory address of SPINLOCK module.\n
 *
 * \return  Revision Number.\n
 *
 */
uint32_t SPINLOCKRevision(uint32_t baseAddr);

/**
 * \brief   This API provides the status of each bank of 32 locks that
 *         can be read from the SPINLOCK_SYSTATUS register.\n
 *
 * \param   baseAddr       Memory address of SPINLOCK module.\n
 *
 * \return  Current Status of the lock.\n
 *          Reset done status :\n
 *                  Read 0x0: Reset in progress.\n
 *                  Read 0x1: Reset is completed.\n
 *
 */
uint32_t SPINLOCKSystatus(uint32_t baseAddr);

/**
 * \brief   This API provides the lock status of the Spinlock module.\n
 *
 * \param   baseAddr       Memory address of SPINLOCK module.\n
 *
 * \return  Lock status.\n
 *          In-Use flag 0, covering lock registers 0 - 31.\n
 *          Read 0x0: All lock registers 0-31 are in the Not Taken
 *                    state.(Free)\n
 *          Read 0x1: At least one of the lock registers 0-31 is in the Taken
 *                    state.\n
 *
 */
uint32_t SPINLOCKSystatusIU0(uint32_t baseAddr);

/**
 * \brief   This API performs the module reset of the Spinlock module. It also
 *          waits until the reset process is complete.\n
 *
 * \param   baseAddr       Memory address of SPINLOCK module.\n
 *
 * \return  None.\n
 *
 */
void SPINLOCKModuleReset(uint32_t baseAddr);

/**
 * \brief   This API performs the Read operation for Lock status of the
 *          SPINLOCK_LOCK_REG, in order to acquire a Spinlock.\n
 *
 * \param   baseAddr       Memory address of SPINLOCK module.\n
 *
 * \param   lockNumber    Lock number in Spinlock module that should be
 *                        acquired.\n
 *
 * \return  Status of the Lock Register.\n
 *          Lock state :\n
 *              Read 0x0: Lock was previously NOT Taken(Free). The requester is
 *                        granted the lock.\n
 *              Read 0x1: Lock was previously Taken(Not Free). The requester is
 *                        not granted the lock and must retry.\n
 *
 */
uint32_t SPINLOCKLockStatusSet(uint32_t baseAddr, uint32_t lockNumber);

/**
 * \brief   This API performs the write operation for Lock status of the
 *          SPINLOCK_LOCK_REG, in order to Free the lock.\n
 *          Lock state :\n
 *             Write 0x0: Set the lock to Not Taken(Free).\n
 *             Write 0x1: No update to the lock value.\n
 *
 * \param   baseAddr       Memory address of SPINLOCK module.\n
 *
 * \param   lockNumber    Lock number in Spinlock module that should be
 *                        released.\n
 *
 * \return  None.\n
 *
 */
void SPINLOCKLockStatusFree(uint32_t baseAddr, uint32_t lockNumber);

#ifdef __cplusplus
}
#endif

#endif
 /** @} */
/********************************* End of file ******************************/
