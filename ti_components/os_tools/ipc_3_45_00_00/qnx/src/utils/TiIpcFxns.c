/*
 * Copyright (c) 2013-2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  @file       TiIpcFxns.c
 *  @brief      Common functions interface with the QnX TI-IPC driver, based
 *              on MessageQCopy.
 *
 */

/* Standard headers */
#include <ti/ipc/Std.h>

/* Socket Headers */
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#include <sys/neutrino.h>
#include <sys/syspage.h>

#include "ti/ipc/ti_ipc.h"

/* For PRINTVERBOSE* */
#include <_IpcLog.h>
#include <_TiIpcFxns.h>

/*  Traces in this file are controlled via _TiIpcFxns_verbose */
Bool _TiIpcFxns_verbose = FALSE;
#define verbose _TiIpcFxns_verbose

/* connect to remote service */
int TiIpcFxns_connect(int fd, UInt16 procId, int dst)
{
    tiipc_remote_params dst_addr;
    int                   err;

    dst_addr.remote_addr = dst;
    dst_addr.remote_proc = procId;

    /* This just sets the remote procId/dst fields of the file object: */
    err = ioctl(fd, TIIPC_IOCSETREMOTE, &dst_addr);
    if (err < 0) {
         printf("IOCSETREMOTE failed: %s (%d)\n", strerror(errno), errno);
         return (-1);
    }

    PRINTVERBOSE3("Connected over fd: %d\n\tdst vproc_id: %d, dst addr: %d\n",
                  fd, procId - 1, dst)
    return(0);
}

int TiIpcFxns_bindAddr(int fd, UInt32 localAddr)
{
    tiipc_local_params src_addr;
    int         err;

    src_addr.local_addr = localAddr;

    /* This calls MessageQCopy_create():  */
    err = ioctl(fd, TIIPC_IOCSETLOCAL, &src_addr);
    if (err >= 0) {
        PRINTVERBOSE2("IOCSETLOCAL: bound fd: %d, src addr: %d\n",
                      fd, localAddr)
    }

    return (err);
}
