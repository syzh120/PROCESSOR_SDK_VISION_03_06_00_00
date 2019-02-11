/*
 * Copyright (c) 2013, Texas Instruments Incorporated
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
 *  ======== _GateMP.h ========
 *
 *  Internal header
 *
 */
#ifndef _GATEMP_H
#define _GATEMP_H

#include <ti/ipc/GateMP.h>

#include <ti/syslink/inc/IObject.h>
#include <ti/syslink/utils/IGateProvider.h>

#if defined (__cplusplus)
extern "C" {
#endif

/* Helper macros */
#define GETREMOTE(mask) ((GateMP_RemoteProtect)(mask >> 8))
#define GETLOCAL(mask)  ((GateMP_LocalProtect)(mask & 0xFF))
#define SETMASK(remoteProtect, localProtect) \
                        ((Bits32)(remoteProtect << 8 | localProtect))

/*!
 *  @brief  Structure for the Handle for the GateMP.
 */
typedef struct {
    GateMP_Params           params;
    /*!< Instance specific creation parameters */
    GateMP_RemoteProtect    remoteProtect;
    GateMP_LocalProtect     localProtect;
    Ptr                     nsKey;
    Int                     numOpens;

    Bits16                  mask;
    Bits16                  creatorProcId;
    Bits32                  arg;

    IGateProvider_Handle    gateHandle; /* remote gate handle */
    Ipc_ObjType             objType;
    IGateProvider_Handle    localGate;  /* local gate handle */

    UInt                    resourceId;
    /*!< Resource id of GateMP proxy */
} GateMP_Object;

/* Has GateMP been setup */
Bool GateMP_isSetup(Void);

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* _GATEMP_H */
