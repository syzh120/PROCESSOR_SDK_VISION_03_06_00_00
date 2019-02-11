/*
 *  @file       syslink_devctl.c
 *
 *  @brief      devctl handler for the ipc resource manager
 *
 *
 *  @ver        02.00.00.46_alpha1
 *
 *  ============================================================================
 *
 *  Copyright (c) 2010-2015, Texas Instruments Incorporated
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

#include "proto.h"
#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/procmgr.h>
#include <sys/neutrino.h>
#include <sys/siginfo.h>
#include <sys/mman.h>
#include <signal.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <ti/syslink/Std.h>
#include "MessageQCopyDrvDefs.h"
#include "HwSpinLockCmdBase.h"
#include "NameServerDrvDefs.h"
#include "MessageQDrvDefs.h"
#include "MultiProcDrvDefs.h"
#include <ti/syslink/build/Qnx/resmgr/dcmd_syslink.h>

#include <ti/syslink/utils/Trace.h>

extern Int MessageQCopyDrv_devctl (resmgr_context_t *ctp, io_devctl_t *msg,
                                   ipc_ocb_t *ocb);
extern Int GateHWSpinlockDrv_devctl (resmgr_context_t * ctp, io_devctl_t * msg,
                                     ipc_ocb_t * ocb);
extern int ipc_messageq_devctl(resmgr_context_t *ctp, io_devctl_t *msg,
                                   ipc_ocb_t *ocb);
extern int ipc_nameserver_devctl(resmgr_context_t *ctp, io_devctl_t *msg,
                                     ipc_ocb_t * ocb);
extern int ipc_multiproc_devctl(resmgr_context_t *ctp, io_devctl_t *msg,
                                     ipc_ocb_t * ocb);
extern int ipc_gatemp_devctl(resmgr_context_t *ctp, io_devctl_t *msg,
                                 ipc_ocb_t * ocb);
extern int ipc_gatehwspinlock_devctl(resmgr_context_t *ctp, io_devctl_t *msg,
                                 ipc_ocb_t * ocb);

/**
 * Handler for devctl() messages.
 *
 * Handles special devctl() messages that we export for control.
 *
 * \param ctp    Thread's associated context information.
 * \param msg    The actual devctl() message.
 * \param ocb    OCB associated with client's session.
 *
 * \return POSIX errno value.
 *
 * \retval EOK        Success.
 * \retval ENOTSUP    Unsupported devctl().
 */
int ipc_devctl(resmgr_context_t *ctp, io_devctl_t *msg, ipc_ocb_t *ocb)
{
    int status = 0;
    int commandClass = 0;

    if ((status = iofunc_devctl_default(ctp, msg, &(ocb->ocb))) !=
         _RESMGR_DEFAULT) {
        return(status);
    }
    status = 0;

    commandClass = (unsigned char)(msg->i.dcmd >> 8);

    iofunc_unlock_ocb_default(ctp, msg, &(ocb->ocb));

    switch (commandClass)
    {
        case MESSAGEQCOPY_BASE_CMD:
            status = MessageQCopyDrv_devctl( ctp, msg, ocb);
            break;
#ifndef IPC_PLATFORM_VAYU
        case HWSPINLOCKDRV_BASE_CMD:
            status = GateHWSpinlockDrv_devctl(ctp, msg, ocb);
            break;
#endif
        case _DCMD_IPC_NAMESERVER:
            status = ipc_nameserver_devctl(ctp, msg, ocb);
            break;
        case _DCMD_IPC_MESSAGEQ:
            status = ipc_messageq_devctl(ctp, msg, ocb);
            break;
        case _DCMD_IPC_MULTIPROC:
            status = ipc_multiproc_devctl(ctp, msg, ocb);
            break;
#ifdef IPC_PLATFORM_VAYU
        case _DCMD_IPC_GATEMP:
            status = ipc_gatemp_devctl(ctp, msg, ocb);
            break;
        case _DCMD_IPC_GATEHWSPINLOCK:
            status = ipc_gatehwspinlock_devctl(ctp, msg, ocb);
            break;
#endif
        default:
            status = _RESMGR_ERRNO(ENOSYS);
            GT_1trace( curTrace, GT_3CLASS,
                      "Command Class not supported 0x%x",
                      (unsigned int)commandClass);
            break;
    }

    iofunc_lock_ocb_default(ctp, msg, &(ocb->ocb));

    return status;
}
