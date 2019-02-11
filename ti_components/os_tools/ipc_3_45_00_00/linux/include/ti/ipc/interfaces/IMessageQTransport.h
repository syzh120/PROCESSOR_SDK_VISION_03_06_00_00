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

/**
 *  @file linux/include/ti/ipc/interfaces/IMessageQTransport.h
 *
 *  @brief Primary interface for all MessageQ transports
 *
 *  A typical memory based transport used as the primary transport for
 *  MessageQ would implement this interface. The transport implementation
 *  has to be registered with MessageQ using the MessageQ_registerTransport
 *  method. This is typically done by the factor code.
 *
 *  The IMessageQTransport interface includes the following instance methods:
 *
 *  bind - create transport resources on behalf of the given queue
 *  unbind - delete transport resources used by the given queue
 *  put - send the message
 */

/*
 *  ======== IMessageQTransport.h ========
 */

#ifndef IMESSAGEQTRANSPORT_H
#define IMESSAGEQTRANSPORT_H

#include <ti/ipc/interfaces/ITransport.h>

#if defined (__cplusplus)
extern "C" {
#endif

/*!
 *  @brief  Interface type ID
 *
 *  This ID uniquely identifies this interface type.
 */
#define IMessageQTransport_TypeId 0x02

/*!
 *  @brief IMessageQTransport_Handle type
 *
 *  An opaque instance handle.
 */
typedef struct IMessageQTransport_Object *IMessageQTransport_Handle;

/*!
 *  @brief The interface function table
 *
 *  All transports must provide a concrete implementation for each of
 *  these virtual functions. The transport user (e.g. MessageQ) will
 *  invoke the implementation functions through the interface function
 *  stubs defined below.
 */
typedef struct IMessageQTransport_Fxns {

    Int (*bind)(void *handle, UInt32 queueId);
    /*!< function pointer for bind method
     *
     *  This method allows the transport to bind/create resources
     *  needed for message delivery. The method is invoked when a
     *  new message queue is created and for all existing queues
     *  when attaching to a processor.
     *
     *  @param[in]  inst        Transport instance handle
     *  @param[in]  queueId     Message queue identifier
     *
     *  @return A MessageQ defined status code (e.g. MessageQ_S_SUCCESS)
     */

    Int (*unbind)(void *handle, UInt32 queueId);
    /*!< function pointer for unbind method
     *
     *  This method allows the transport to unbind/delete resources
     *  which where allocated on behalf of the given message queue.
     *  This method is invoked when deleting a message queue and for
     *  all existing queues when detaching from a processor.
     *
     *  @param[in]  inst        Transport instance handle
     *  @param[in]  queueId     Message queue identifier
     *
     *  @return A MessageQ defined status code (e.g. MessageQ_S_SUCCESS)
     */

    Bool (*put)(void *handle, Ptr msg);
    /*!< function pointer for put method
     *
     *  Invoked to deliver the given message. Once MessageQ calls into this
     *  method, the message ownership has been transferred to the transport.
     *  Regardless of the outcome of message delivery, the message ownership
     *  is *never* returned back to MessageQ. If delivery fails, the message
     *  is lost but all resources must be reclaimed.
     *
     *  @param[in]  inst        Transport instance handle
     *  @param[in]  msg         Pointer to the message (MessageQ_Msg)
     *
     *  @return Status result:
     *          - TRUE: message was delivered
     *          - FALSE: delivery failure, message lost
     */
} IMessageQTransport_Fxns;

/*!
 *  @brief The instance object definition for IMessageQTransport
 *
 *  All instances of this interface type must define this object
 *  within the implementation object. It must be the first element
 *  of the instance object and it must be named 'base'. Otherwise,
 *  the converter functions below will fail.
 *
 *  typedef TransportAcme_Object {
 *      IMessageQTransport_Object base;
 *      ...
 *  } TransportAcme_Object;
 */
typedef struct IMessageQTransport_Object {

    ITransport_Object base;
    /*!< Base class inheritance
     *
     *  The instance constructor must initialize this base object.
     */

    IMessageQTransport_Fxns *fxns;
    /*!< Address of interface function table
     *
     *  The instance constructor must initialize this field to contain
     *  the address of the instance function table.
     *
     *  IMessageQTransport_Fxns TransportAcme_fxns = {
     *      .bind   = TransportAcme_bind,
     *      .unbind = TransportAcme_unbind,
     *      .put    = TransportAcme_put
     *  };
     *
     *  obj->base.fxns = &TransportAcme_fxns;
     */
} IMessageQTransport_Object;

/*!
 *  @brief Bind transport resources on behalf of the given message queue
 *
 *  Interface function to invoke transport implementation.
 *
 *  @sa IMessageQTransport_Fxns.bind()
 *
 *  @param[in]  inst        Transport instance handle
 *  @param[in]  queueId     Message queue identifier
 *
 *  @return A MessageQ defined status code (e.g. MessageQ_S_SUCCESS)
 */
static inline
Int IMessageQTransport_bind(IMessageQTransport_Handle inst, UInt32 queueId)
{
    IMessageQTransport_Object *obj = (IMessageQTransport_Object *)inst;
    return obj->fxns->bind((void *)inst, queueId);
}

/*!
 *  @brief Unbind transport resources allocated for the given message queue
 *
 *  Interface function to invoke transport implementation.
 *
 *  @sa IMessageQTransport_Fxns.unbind()
 *
 *  @param[in]  inst        Transport instance handle
 *  @param[in]  queueId     Message queue identifier
 *
 *  @return A MessageQ defined status code (e.g. MessageQ_S_SUCCESS)
 */
static inline
Int IMessageQTransport_unbind(IMessageQTransport_Handle inst, UInt32 queueId)
{
    IMessageQTransport_Object *obj = (IMessageQTransport_Object *)inst;
    return obj->fxns->unbind((void *)inst, queueId);
}

/*!
 *  @brief Deliver the given message
 *
 *  Interface function to invoke transport implementation.
 *
 *  @sa IMessageQTransport_Fxns.put()
 *
 *  @param[in]  inst        Transport instance handle
 *  @param[in]  msg         Pointer to the message (MessageQ_Msg)
 *
 *  @return A MessageQ defined status code (e.g. MessageQ_S_SUCCESS)
 */
static inline
Bool IMessageQTransport_put(IMessageQTransport_Handle inst, Ptr msg)
{
    IMessageQTransport_Object *obj = (IMessageQTransport_Object *)inst;
    return obj->fxns->put((void *)inst, msg);
}

/*!
 *  @brief Convert the instance handle to a base class handle
 *
 *  Use this method to safely get a handle to the base interface.
 *  The returned handle can be used to invoke methods on the base
 *  interface.
 *
 *  @param[in]  inst        Transport instance handle
 *
 *  @return An ITransport_Handle for the given instance object
 */
static inline
ITransport_Handle IMessageQTransport_upCast(IMessageQTransport_Handle inst)
{
    IMessageQTransport_Object *obj = (IMessageQTransport_Object *)inst;
    return (ITransport_Handle)&obj->base;
}

/*!
 *  @brief Convert the base class handle into and instance handle
 *
 *  Use this method to safely get a handle to the interface instance.
 *  The returned handle can be used to invoke methods on the instance
 *  object.
 *
 *  @param[in]  inst        ITransport_handle of the instance object
 *
 *  @return An ITransport_Handle for the given instance
 */
static inline
IMessageQTransport_Handle IMessageQTransport_downCast(ITransport_Handle base)
{
    return (IMessageQTransport_Handle)base;
}

#if defined (__cplusplus)
}
#endif
#endif /* IMESSAGEQTRANSPORT_H */
