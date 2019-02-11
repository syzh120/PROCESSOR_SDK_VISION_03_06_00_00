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
 *  ======== NameServer.c ========
 */
#include <ti/ipc/Std.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#include <ti/ipc/NameServer.h>
#include <ti/ipc/MultiProc.h>

#include <_IpcLog.h>
#include <ti/syslink/inc/_MultiProc.h>
#include <ti/syslink/inc/IoctlDefs.h>
#include <ti/syslink/inc/usr/Qnx/NameServerDrv.h>
#include <ti/syslink/inc/NameServerDrvDefs.h>

/* traces in this file are controlled via _NameServer_verbose */
Bool _NameServer_verbose = FALSE;
#define verbose _NameServer_verbose

/*
 * The NameServer_*() APIs are reproduced here.  These versions are just
 * front-ends for communicating with the actual NameServer module (currently
 * implemented in the IPC driver process acting as a daemon).
 */

Int NameServer_setup(Void)
{
    Int status;
    NameServerDrv_CmdArgs cmdArgs;

    status = NameServerDrv_ioctl (CMD_NAMESERVER_SETUP, &cmdArgs);
    if (status < 0) {
        PRINTVERBOSE1("NameServer_setup: API (through IOCTL) failed, \
            status=%d\n", status)
    }

    return status;
}

Int NameServer_destroy(Void)
{
    Int status;

    NameServerDrv_CmdArgs cmdArgs;

    PRINTVERBOSE0("NameServer_destroy: entered\n")

    status = NameServerDrv_ioctl (CMD_NAMESERVER_DESTROY, &cmdArgs);

    if (status < 0) {
        PRINTVERBOSE1("NameServer_destroy: API (through IOCTL) failed, \
            status=%d\n", status)
    }

    return status;
}

Void NameServer_Params_init(NameServer_Params *params)
{
    Int status;
    NameServerDrv_CmdArgs cmdArgs;

    cmdArgs.args.ParamsInit.params = params;
    status = NameServerDrv_ioctl (CMD_NAMESERVER_PARAMS_INIT, &cmdArgs);

    if (status < 0) {
        PRINTVERBOSE1("NameServer_Params_init: API (through IOCTL) failed, \
            status=%d\n", status)
        return;
    }

    return;
}

NameServer_Handle NameServer_create(String name,
                                    const NameServer_Params *params)
{
    Int status;
    NameServerDrv_CmdArgs cmdArgs;

    cmdArgs.args.create.name    = name;
    cmdArgs.args.create.nameLen = strlen (name) + 1;
    cmdArgs.args.create.params  = (NameServer_Params *) params;

    status = NameServerDrv_ioctl (CMD_NAMESERVER_CREATE, &cmdArgs);

    if (status < 0) {
        PRINTVERBOSE1("NameServer_create: API (through IOCTL) failed, \
            status=%d\n", status)
        return NULL;
    }

    return cmdArgs.args.create.handle;
}

Ptr NameServer_add(NameServer_Handle nsHandle, String name, Ptr buf,
                   UInt32 len)
{
    Int status;
    NameServerDrv_CmdArgs cmdArgs;

    cmdArgs.args.add.handle  = nsHandle;
    cmdArgs.args.add.name    = name;
    cmdArgs.args.add.nameLen = strlen(name) + 1;
    cmdArgs.args.add.buf     = buf;
    cmdArgs.args.add.len     = len;

    status = NameServerDrv_ioctl(CMD_NAMESERVER_ADD, &cmdArgs);

    if (status < 0) {
        PRINTVERBOSE1("NameServer_add: API (through IOCTL) failed, \
            status=%d\n", status)
        return NULL;
    }

    return cmdArgs.args.add.entry;
}

Int NameServer_get(NameServer_Handle handle, String name, Ptr buf,
                   UInt32 * len, UInt16 procId[])
{
    Int status;
    UInt32 procLen = 0;
    NameServerDrv_CmdArgs cmdArgs;

    cmdArgs.args.get.name = name;
    cmdArgs.args.get.handle = handle;
    cmdArgs.args.get.procId  = procId;
    if (procId != NULL) {
        while (procId[procLen] != MultiProc_INVALIDID) {
            procLen++;
        }
    }
    cmdArgs.args.get.procLen = procLen;
    cmdArgs.args.get.buf = buf;
    cmdArgs.args.get.len = *len;
    cmdArgs.args.get.nameLen = strlen(name) + 1;

    status = NameServerDrv_ioctl (CMD_NAMESERVER_GET, &cmdArgs);

    if (status < 0) {
        PRINTVERBOSE1("NameServer_get: API (through IOCTL) failed, \
            status=%d\n", status)
        return status;
    }

    *len = cmdArgs.args.get.len;

    return status;
}


Ptr NameServer_addUInt32(NameServer_Handle nsHandle, String name, UInt32 value)
{
    Int status;
    NameServerDrv_CmdArgs cmdArgs;

    cmdArgs.args.addUInt32.handle  = nsHandle;
    cmdArgs.args.addUInt32.name    = name;
    cmdArgs.args.addUInt32.nameLen = strlen(name) + 1;
    cmdArgs.args.addUInt32.value   = value;
    status = NameServerDrv_ioctl(CMD_NAMESERVER_ADDUINT32, &cmdArgs);

    if (status < 0) {
        PRINTVERBOSE1("NameServer_addUInt32: API (through IOCTL) failed, \
            status=%d\n", status)
        return NULL;
    }

    return cmdArgs.args.addUInt32.entry;
}

Int NameServer_getUInt32(NameServer_Handle nsHandle, String name, Ptr buf,
                          UInt16 procId[])
{
    Int status;
    UInt32 *val;
    NameServerDrv_CmdArgs cmdArgs;

    cmdArgs.args.getUInt32.name  = name;
    cmdArgs.args.getUInt32.handle  = nsHandle;
    if (procId != NULL) {
        memcpy(cmdArgs.args.getUInt32.procId, procId,
               sizeof(UInt16) * MultiProc_MAXPROCESSORS);
    }
    else {
        cmdArgs.args.getUInt32.procId[0] = (UInt16)-1;
    }
    status = NameServerDrv_ioctl (CMD_NAMESERVER_GETUINT32, &cmdArgs);

    if (status < 0) {
        PRINTVERBOSE1("NameServer_getUInt32: API (through IOCTL) failed, \
            status=%d\n", status)
        return status;
    }

    val = (UInt32 *)buf;
    *val = cmdArgs.args.getUInt32.value;

    return status;
}

Int NameServer_remove(NameServer_Handle nsHandle, String name)
{
    Int status;
    NameServerDrv_CmdArgs cmdArgs;

    cmdArgs.args.remove.handle  = nsHandle;
    cmdArgs.args.remove.name    = name;
    cmdArgs.args.remove.nameLen = strlen(name) + 1;
    status = NameServerDrv_ioctl(CMD_NAMESERVER_REMOVE, &cmdArgs);

    if (status < 0) {
        PRINTVERBOSE1("NameServer_remove: API (through IOCTL) failed, \
            status=%d\n", status)
    }

    return status;
}

Int NameServer_removeEntry(NameServer_Handle nsHandle, Ptr entry)
{
    Int status;
    NameServerDrv_CmdArgs cmdArgs;

    cmdArgs.args.removeEntry.handle = nsHandle;
    cmdArgs.args.removeEntry.entry  = entry;
    status = NameServerDrv_ioctl (CMD_NAMESERVER_REMOVEENTRY, &cmdArgs);

    if (status < 0) {
        PRINTVERBOSE1("NameServer_removeEntry: API (through IOCTL) failed, \
            status=%d\n", status)
    }

    return status;
}

Int NameServer_delete(NameServer_Handle *nsHandle)
{
    Int status;
    NameServerDrv_CmdArgs cmdArgs;

    cmdArgs.args.delete.handle = *nsHandle;
    status = NameServerDrv_ioctl (CMD_NAMESERVER_DELETE, &cmdArgs);

    if (status < 0) {
        PRINTVERBOSE1("NameServer_delete: API (through IOCTL) failed, \
            status=%d\n", status)
        return status;
    }

    *nsHandle = cmdArgs.args.delete.handle;

    return status;
}
