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
 *  ======== TransportRpmsg.h ========
 */

/**
 *  @file       TransportRpmsg.h
 *
 *  @brief      Rpmsg transports implemenation
 *
 *              The transports can be register with MessageQ. This is done
 *              via the MessageQ_registerTransport function.
 */

#ifndef _TransportRpmsg_
#define _TransportRpmsg_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/ipc/Ipc.h>
#include <ti/ipc/interfaces/IMessageQTransport.h>

extern Ipc_TransportFactoryFxns TransportRpmsg_Factory;

struct TransportRpmsg_Params {
    UInt16 rprocId;
};
typedef struct TransportRpmsg_Params TransportRpmsg_Params;

typedef IMessageQTransport_Handle TransportRpmsg_Handle;

TransportRpmsg_Handle TransportRpmsg_create(TransportRpmsg_Params *params);
Void TransportRpmsg_delete(TransportRpmsg_Handle *hp);

IMessageQTransport_Handle TransportRpmsg_upCast(TransportRpmsg_Handle handle);
TransportRpmsg_Handle TransportRpmsg_downCast(IMessageQTransport_Handle base);

#ifdef __cplusplus
}
#endif

#endif
