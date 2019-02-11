/*
 * Copyright (c) 2012-2014 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== IMessageQTransport.xdc ========
 */
package ti.sdo.ipc.interfaces;

/*!
 *  ======== IMessageQTransport ========
 *  Interface for the transports used by MessageQ
 *
 *  The transport implementations have to register with
 *  {@link ti.sdo.ipc.MessageQ}. This is done via the
 *  {@link ti.sdo.ipc.MessageQ#registerTransport} function.
 *
 *  If transports need additional processing during startup,
 *  there are multiple hook points to run start-up code that
 *  the transport implementation can use.
 */

interface IMessageQTransport inherits ITransport {
    /*!
     *  Transport return values
     *
     *  @p(blist)
     *  -{@link #S_SUCCESS}: Operation was successful
     *  -{@link #E_FAIL}: Operation resulted in a failure
     *  -{@link #E_ERROR}: Operation resulted in an error.
     *  @p
     */
    enum Status {
        S_SUCCESS = 0,
        E_FAIL = -1,
        E_ERROR = -2
    };

    /*!
     *  Reason for error function being called
     *
     *  First field in the {@link #errFxn}
     */
    enum Reason {
        Reason_FAILEDPUT,
        Reason_INTERNALERR,
        Reason_PHYSICALERR,
        Reason_FAILEDALLOC
    };

    /*!
     *  Asynchronous error function for the transport module
     */
    config ErrFxn errFxn = null;

    /*!
     *  Typedef for transport error callback function.
     *
     *  First parameter: Why the error function is being called.
     *
     *  Second parameter: Handle of transport that had the error. NULL denotes
     *  that it is a system error, not a specific transport.
     *
     *  Third parameter: Pointer to the message. This is only valid for
     *  {@link #Reason_FAILEDPUT}.
     *
     *  Fourth parameter: Transport specific information. Refer to individual
     *  transports for more details.
     */
    typedef Void (*ErrFxn)(Reason, Handle, Ptr, UArg);

    /*!
     *  ======== setErrFxn ========
     *  Sets the asynchronous error function for the transport module
     *
     *  This API allows the user to set the function that will be called in
     *  case of an asynchronous error by the transport.
     *
     *  @param(errFxn)        Function that is called when an asynchronous
     *                        error occurs.
     */
    Void setErrFxn(ErrFxn errFxn);

instance:

    /*!
     *  Which priority messages should this transport manage.
     */
    config UInt priority = 0;

    /*!
     *  ======== create ========
     *  Create a Transport instance
     *
     *  This function creates a transport instance. The transport is
     *  responsible for registering with MessageQ via the
     *  {@link ti.sdo.ipc.MessageQ#registerTransport} API.
     *
     *  @param(procId)        Remote processor id that this instance
     *                        will communicate with.
     */
    create(UInt16 procId);

    /*!
     *  ======== getStatus ========
     *  Status of a Transport instance
     *
     *  This function returns the status of the transport instance.
     *
     *  @b(returns)             Returns status of Transport instance
     */
    @DirectCall
    Int getStatus();

    /*!
     *  ======== put ========
     *  Put the message to the remote processor
     *
     *  If the transport can accept the message, it returns TRUE. Accepting
     *  a message does not mean that it is transmitted. It simply means that
     *  the transport should be able to send the message. If the actual transfer
     *  fails, the transport calls the {@#ErrFxn} (assuming it is set up via the
     *  {@#setErrFxn} API. If the {@#ErrFxn} is not set, the message is dropped.
     *  (also...should an error be raised or just System_printf?).
     *
     *  If the transport cannot send the message, it returns FALSE and a
     *  filled in Error_Block. The caller still owns the message.
     *
     *  @param(msg)             Pointer the message to be sent
     *
     *  @b(returns)             TRUE denotes acceptance of the message to
     *                          be sent. FALSE denotes the message could not be
     *                          sent.
     */
    @DirectCall
    Bool put(Ptr msg);

    /*!
     *  ======== Control ========
     *  Send a control command to the transport instance
     *
     *  This is function allows transport to specify control commands. Refer
     *  to individual transport implementions for more details.
     *
     *  @param(cmd)             Requested command
     *  @param(cmdArgs)         Accompanying field for the command. This is
     *                          command specific.
     *
     *  @b(returns)             TRUE denotes acceptance of the command. FALSE
     *                          denotes failure of the command.
     */
    @DirectCall
    Bool control(UInt cmd, UArg cmdArg);
}
