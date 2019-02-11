/*
 *  @file   HWSpinlock.c
 *
 *  @brief      Usr lib to access Hardware SpinLock.
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

#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/slog.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <HwSpinLockCmdBase.h>
#include <GateHWSpinlock.h>
#include <ti/syslink/utils/Trace.h>

#define IPC_DRIVER_NAME         "/dev/ipc"

#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static int ipcHandler = -1;
static int ref_cnt = 0;

int moduleUnInitialized()
{
    if(ipcHandler < 0)
        return 1;
    else
        return 0;
}

int initIPCHandler(int *IpcDrv_handle)
{
    int status = 0;

    pthread_mutex_lock(&mutex);
    if (ref_cnt++ == 0) {
        *IpcDrv_handle = open (IPC_DRIVER_NAME,
                                        O_SYNC | O_RDWR);
        if (*IpcDrv_handle < 0) {
            GT_setFailureReason (curTrace,
                     GT_4CLASS,
                     "initIPCHandler",
                     -1,
                     "couldn't open ipc device\n");
            ref_cnt--;
            *IpcDrv_handle = -1;
            status = -errno;
        } else {
            status = fcntl (*IpcDrv_handle, F_SETFD, FD_CLOEXEC);
            if (status != 0) {
                GT_setFailureReason (curTrace,
                         GT_4CLASS,
                         "initIPCHandler",
                         -1,
                         "Failed to set file descriptor flags\n");
                close (*IpcDrv_handle);
                *IpcDrv_handle = -1;
                ref_cnt--;
                status = -errno;
            }
        }
    }

    pthread_mutex_unlock(&mutex);
    return status;
}

void deinitIPCHandler(int *IpcDrv_handle)
{
    if(IpcDrv_handle ==  0 || *IpcDrv_handle < 0){
        GT_setFailureReason (curTrace,
                 GT_4CLASS,
                 "deinitIPCHandler",
                 -1,
                 "Incorrect handle passed");

        return;
    }

    pthread_mutex_lock(&mutex);

    if (--ref_cnt == 0) {
        close (*IpcDrv_handle);
        *IpcDrv_handle = -1;
    }
    pthread_mutex_unlock(&mutex);
}

int HwSpinlock_create(int lockID, GateHWSpinlock_LocalProtect protectType)
{
    Int status = GateHWSpinlock_S_SUCCESS;
    int osStatus = 0;
    HWSpinLockDrv_CmdArgs cmdArgs;

    if (lockID < 0) {
        status = GateHWSpinlock_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "HwSpinlock_create",
                             status,
                             "Incorrect parameter passed");
        return -1;
    }

    status = initIPCHandler(&ipcHandler);
    if (status < 0) {
        status = GateHWSpinlock_E_FAIL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "HwSpinlock_create",
                             status,
                             "Failed to initiate module");
        return -1;
    }

    cmdArgs.apiStatus = -1;
    cmdArgs.handleID = -1;
    cmdArgs.resID = lockID;
    cmdArgs.protectType = protectType;
    osStatus = ioctl (ipcHandler, CMD_HWSPINLOCK_CREATE, &cmdArgs);

    if (osStatus < 0) {
        status = GateHWSpinlock_E_OSFAILURE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "HwSpinlock_delete",
                             status,
                             "ioctl failed!");
        return -1;
    }
    else if (cmdArgs.apiStatus != 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "HwSpinlock_create",
                             status,
                            "API failed");
        return -1;
    }

    return cmdArgs.handleID;

}

int HwSpinlock_delete (int token)
{
    Int status = GateHWSpinlock_S_SUCCESS;
    int osStatus = 0;
    HWSpinLockDrv_CmdArgs cmdArgs;

    if(moduleUnInitialized()) {
        status = GateHWSpinlock_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "HwSpinlock_delete",
                             status,
                             "Module not initialized!");
        return status;
    }
    if(token < 0) {
        status = GateHWSpinlock_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "HwSpinlock_delete",
                             status,
                             "Incorrect arguments passed!");
        return status;
    }

    cmdArgs.apiStatus = -1;
    cmdArgs.handleID = token;

    osStatus = ioctl (ipcHandler, CMD_HWSPINLOCK_DELETE, &cmdArgs);

    if (osStatus < 0) {
        status = GateHWSpinlock_E_OSFAILURE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "HwSpinlock_delete",
                             status,
                             "ioctl failed!");
    }
    else {
        status = cmdArgs.apiStatus;
    }
    deinitIPCHandler(&ipcHandler);

    return status;
}

int* HwSpinlock_enter(int token)
{
    int status;
    int osStatus;
    HWSpinLockDrv_CmdArgs cmdArgs;

    if(token < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "HwSpinlock_enter",
                             -1,
                             "Module not initialized!");

        return (int *)(-1);
    }
    if(moduleUnInitialized()) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "HwSpinlock_enter",
                             -1,
                             "Module not initialized!");
        return (int *)(-1);
    }


    cmdArgs.apiStatus = -1;
    cmdArgs.handleID = token;

    osStatus = ioctl (ipcHandler, CMD_HWSPINLOCK_ENTER, &cmdArgs);

    if (osStatus < 0) {
        status = GateHWSpinlock_E_OSFAILURE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "HwSpinlock_enter",
                             status,
                             "ioctl failed!");
        return (int *)(-1);
    }
    else if(cmdArgs.apiStatus != 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "HwSpinlock_enter",
                             cmdArgs.apiStatus,
                             "API failed!");

        return (int *)(-1);
    }

    return cmdArgs.key;
}

int HwSpinlock_leave(int* key, int token)
{
    int status;
    int osStatus;
    HWSpinLockDrv_CmdArgs cmdArgs;

    if(token < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "HwSpinlock_leave",
                             -1,
                             "Incorrect arguments passed!");

        return -1;
    }
    if(moduleUnInitialized()) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "HwSpinlock_leave",
                             -1,
                             "Module not initialized!");
        return -1;
    }

    cmdArgs.apiStatus = -1;
    cmdArgs.handleID = token;
    cmdArgs.key = key;

    osStatus = ioctl (ipcHandler, CMD_HWSPINLOCK_LEAVE, &cmdArgs);

    if (osStatus < 0) {
        status = GateHWSpinlock_E_OSFAILURE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "HwSpinlock_leave",
                             status,
                             "ioctl failed!");
        return -1;
    }
    else if (cmdArgs.apiStatus != 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "HwSpinlock_leave",
                             cmdArgs.apiStatus,
                             "API failed!");

        return -1;
    }

    return 0;
}

int HwSpinlock_GetLockId(int token)
{
    int status;
    int osStatus = 0;
    HWSpinLockDrv_CmdArgs cmdArgs;

    if(token < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "HwSpinlock_GetLockId",
                             -1,
                             "Incorrect arguments passed!");

        return -1;
    }
    if(moduleUnInitialized()) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "HwSpinlock_GetLockId",
                             -1,
                             "Module not initialized!");
        return -1;
    }

    cmdArgs.apiStatus = -1;
    cmdArgs.handleID = token;

    osStatus = ioctl (ipcHandler, CMD_HWSPINLOCK_GETLOCKID, &cmdArgs);

    if (osStatus < 0) {
        status = GateHWSpinlock_E_OSFAILURE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "HwSpinlock_GetLockId",
                             status,
                             "ioctl failed!");
        return -1;
    }
    else if(cmdArgs.apiStatus != 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "HwSpinlock_GetLockId",
                             -1,
                             "API failed!");

        return -1;
    }

    return cmdArgs.resID;

}
#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
