/*
 *  @file   HWSpinLockCmd.h
 *
 *  @brief      IOCTL commands for Hardware Spinlock access.
 *
 *
 *  @ver        02.00.00.46_alpha1
 *
 *  ============================================================================
 *
 *  Copyright (c) 2008-2015, Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  Contact information for paper mail:
 *  Texas Instruments
 *  Post Office Box 655303
 *  Dallas, Texas 75265
 *  Contact information:
 *  http://www-k.ext.ti.com/sc/technical-support/product-information-centers.htm?
 *  DCMP=TIHomeTracking&HQS=Other+OT+home_d_contact
 *  ============================================================================
 *
 */

/* QNX specific headers */
#include <sys/ioctl.h>

#if !defined (HWSPINLOCKCMDBASE_H)
#define HWSPINLOCKCMDBASE_H

/*!
 *  @brief  Base command ID for HwSpinLock
 */

typedef enum {
    HWSPINLOCK_CMD_CREATE = 1,
    HWSPINLOCK_CMD_DELETE = 2,
    HWSPINLOCK_CMD_ENTER = 3,
    HWSPINLOCK_CMD_LEAVE = 4,
    HWSPINLOCK_CMD_GETLOCKID = 5,
} HWSpinLock_cmd_types;

typedef struct {
    int resID;
    int protectType;
    int handleID;
    int *key;
    int apiStatus;
}HWSpinLockDrv_CmdArgs;

#define HWSPINLOCKDRV_BASE_CMD                 (0x1D)

#define CMD_HWSPINLOCK_CREATE            _IOWR(HWSPINLOCKDRV_BASE_CMD,\
                                            HWSPINLOCK_CMD_CREATE,\
                                            HWSpinLockDrv_CmdArgs)

#define CMD_HWSPINLOCK_DELETE            _IOWR(HWSPINLOCKDRV_BASE_CMD,\
                                            HWSPINLOCK_CMD_DELETE,\
                                            HWSpinLockDrv_CmdArgs)

#define CMD_HWSPINLOCK_ENTER            _IOWR(HWSPINLOCKDRV_BASE_CMD,\
                                            HWSPINLOCK_CMD_ENTER,\
                                            HWSpinLockDrv_CmdArgs)

#define CMD_HWSPINLOCK_LEAVE            _IOWR(HWSPINLOCKDRV_BASE_CMD,\
                                            HWSPINLOCK_CMD_LEAVE,\
                                            HWSpinLockDrv_CmdArgs)

#define CMD_HWSPINLOCK_GETLOCKID            _IOWR(HWSPINLOCKDRV_BASE_CMD,\
                                            HWSPINLOCK_CMD_GETLOCKID,\
                                            HWSpinLockDrv_CmdArgs)

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */


#endif  /* !defined (HWSPINLOCKCMDBASE_H) */
