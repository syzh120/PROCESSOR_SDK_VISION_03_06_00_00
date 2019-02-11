/*
 * Copyright (c) 2014-2015 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== INetworkTransport.h ========
 */

#ifndef INETWORKTRANSPORT_H
#define INETWORKTRANSPORT_H

#include <ti/ipc/interfaces/ITransport.h>


/*
 *  ======== INetworkTransport_Handle ========
 *  Opaque handle to interface instance object
 */
typedef struct INetworkTransport_Object *INetworkTransport_Handle;

/*
 *  ======== INetworkTransport_TypeId ========
 *  Unique identifier for this interface
 */
#define INetworkTransport_TypeId 0x03

/*
 *  ======== INetworkTransport_Fxns ========
 *  Interface virtual function table
 */
typedef struct INetworkTransport_Fxns {
    Int (*bind)(void *handle, UInt32 queueId);
    Int (*unbind)(void *handle, UInt32 queueId);
    Bool (*put)(void *handle, Ptr msg);
} INetworkTransport_Fxns;

/*
 *  ======== INetworkTransport_Object ========
 *  Abstract instance object
 */
typedef struct INetworkTransport_Object {
    ITransport_Object base;             /* inheritance */
    INetworkTransport_Fxns *fxns;       /* virtual functions */
} INetworkTransport_Object;

/*
 *  ======== INetworkTransport_bind ========
 *  Instance function stub
 */
static inline
Bool INetworkTransport_bind(INetworkTransport_Handle inst, UInt32 queueId)
{
    INetworkTransport_Object *obj = (INetworkTransport_Object *)inst;
    return (obj->fxns->bind((void *)inst, queueId));
}

/*
 *  ======== INetworkTransport_unbind ========
 *  Instance function stub
 */
static inline
Bool INetworkTransport_unbind(INetworkTransport_Handle inst, UInt32 queueId)
{
    INetworkTransport_Object *obj = (INetworkTransport_Object *)inst;
    return (obj->fxns->unbind((void *)inst, queueId));
}

/*
 *  ======== INetworkTransport_put ========
 *  Instance function stub
 */
static inline
Bool INetworkTransport_put(INetworkTransport_Handle inst, Ptr msg)
{
    INetworkTransport_Object *obj = (INetworkTransport_Object *)inst;
    return (obj->fxns->put((void *)inst, msg));
}

/*
 *  ======== INetworkTransport_upCast ========
 *  Instance converter
 */
static inline
ITransport_Handle INetworkTransport_upCast(INetworkTransport_Handle inst)
{
    INetworkTransport_Object *obj = (INetworkTransport_Object *)inst;
    return ((ITransport_Handle)&obj->base);
}

/*
 *  ======== INetworkTransport_downCast ========
 *  Instance converter
 */
static inline
INetworkTransport_Handle INetworkTransport_downCast(ITransport_Handle base)
{
    return ((INetworkTransport_Handle)base);
}

#endif /* INETWORKTRANSPORT_H */
