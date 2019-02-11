/*
 * Copyright (c) 2012-2013, Texas Instruments Incorporated
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
 *  ======== INotifyDriver.xdc ========
 *
 */

/*!
 *  ======== INotifyDriver ========
 *  Notify driver interface
 *
 *  Interface implemented by all drivers for the notify module.  Modules that
 *  implement this interface expect the eventId arguments to be valid.
 */

interface INotifyDriver {

instance:

    /*!
     *  ======== registerEvent ========
     *  Register a callback to an event
     *
     *  This driver function is called by the Notify_registerEvent function
     *  within the Notify module gate. Refer to its documentation for more
     *  details.
     *
     *  @param(eventId)      Number of event that is being registered
     */
    @DirectCall
    Void registerEvent(UInt32 eventId);

    /*!
     *  ======== unregisterEvent ========
     *  Remove an event listener from an event
     *
     *  This driver function is called by the Notify_unregisterEvent function
     *  within the Notify module gate. Refer to it for more details.
     *
     *  @param(eventId)      Number of event that is being unregistered
     */
    @DirectCall
    Void unregisterEvent(UInt32 eventId);

    /*!
     *  ======== sendEvent ========
     *  Send a signal to an event
     *
     *  This interface function is called by the Notify_sendEvent function.
     *  Notify_sendEvent does not provide any context protection for
     *  INotifyDriver_sendEvent, so appropriate measures must be taken within
     *  the driver itself.
     *
     *  @param(eventId)      Number of event to signal
     *  @param(payload)      Payload (optional) to pass to callback function
     *  @param(waitClear)    If TRUE, have the NotifyDriver wait for
     *                       acknowledgement back from the destination
     *                       processor.
     *
     *  @b(returns)          Notify status
     */
    @DirectCall
    Int sendEvent(UInt32 eventId, UInt32 payload, Bool waitClear);

    /*!
     *  ======== disable ========
     *  Disable a NotifyDriver instance
     *
     *  Disables the ability of a Notify driver to receive events for a given
     *  processor. This interface function is called by the Notify_disable
     *  function. Refer to its documentation for more details.
     */
    @DirectCall
    Void disable();

    /*!
     *  ======== enable ========
     *  Enable a NotifyDriver instance
     *
     *  Enables the ability of a Notify driver to receive events for a given
     *  processor. This interface function is called by the Notify_restore
     *  function. Refer to its documentation for more details.
     */
    @DirectCall
    Void enable();

    /*!
     *  ======== disableEvent ========
     *  Disable an event
     *
     *  This interface function is called by the Notify_disableEvent function.
     *  Refer to its documentation for more details.
     *
     *  The Notify module does validation of the eventId.  The Notify module
     *  enters calls this function within the Notify module gate.
     *
     *  @param(eventId)      Number of event to disable
     */
    @DirectCall
    Void disableEvent(UInt32 eventId);

    /*!
     *  ======== enableEvent ========
     *  Enable an event
     *
     *  This interface function is called by the Notify_disableEvent function.
     *  Refer to its documentation for more details.
     *
     *  The Notify module does validation of the eventId.  The Notify module
     *  enters calls this function within the Notify module gate.
     *
     *  @param(eventId)      Number of event to enable
     */
    @DirectCall
    Void enableEvent(UInt32 eventId);

    /*! @_nodoc
     *  ======== setNotifyHandle ========
     *  Called during Notify instance creation to 'send' its handle to its
     *  corresponding notify driver instance
     */
    @DirectCall
    Void setNotifyHandle(Ptr driverHandle);

}
