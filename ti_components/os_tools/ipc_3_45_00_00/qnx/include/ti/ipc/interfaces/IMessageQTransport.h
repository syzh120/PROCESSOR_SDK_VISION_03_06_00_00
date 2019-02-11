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
 *  ======== IMessageQTransport.h ========
 */

#ifndef IMESSAGEQTRANSPORT_H
#define IMESSAGEQTRANSPORT_H

#include <ti/ipc/interfaces/ITransport.h>

/* opaque instance handle */
typedef struct IMessageQTransport_Object *IMessageQTransport_Handle;

#define IMessageQTransport_TypeId 0x02

/* virtual functions */
typedef struct IMessageQTransport_Fxns {
    Int (*bind)(void *handle, UInt32 queueId);
    Int (*unbind)(void *handle, UInt32 queueId);
    Bool (*put)(void *handle, Ptr msg);
} IMessageQTransport_Fxns;

/* abstract instance object */
typedef struct IMessageQTransport_Object {
    ITransport_Object base;             /* inheritance */
    IMessageQTransport_Fxns *fxns;      /* virtual functions */
} IMessageQTransport_Object;

/* function stubs */
static inline
Int IMessageQTransport_bind(IMessageQTransport_Handle inst, UInt32 queueId)
{
    IMessageQTransport_Object *obj = (IMessageQTransport_Object *)inst;
    return obj->fxns->bind((void *)inst, queueId);
}

static inline
Int IMessageQTransport_unbind(IMessageQTransport_Handle inst, UInt32 queueId)
{
    IMessageQTransport_Object *obj = (IMessageQTransport_Object *)inst;
    return obj->fxns->unbind((void *)inst, queueId);
}

static inline
Bool IMessageQTransport_put(IMessageQTransport_Handle inst, Ptr msg)
{
    IMessageQTransport_Object *obj = (IMessageQTransport_Object *)inst;
    return obj->fxns->put((void *)inst, msg);
}

/* instance convertors */
static inline
ITransport_Handle IMessageQTransport_upCast(IMessageQTransport_Handle inst)
{
    IMessageQTransport_Object *obj = (IMessageQTransport_Object *)inst;
    return (ITransport_Handle)&obj->base;
}

static inline
IMessageQTransport_Handle IMessageQTransport_downCast(ITransport_Handle base)
{
    return (IMessageQTransport_Handle)base;
}

#endif /* IMESSAGEQTRANSPORT_H */
