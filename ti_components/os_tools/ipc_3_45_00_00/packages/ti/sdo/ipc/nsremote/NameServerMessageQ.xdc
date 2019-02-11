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
 *  ======== NameServerMessageQ.xdc ========
 */

import xdc.runtime.Error;
import xdc.runtime.Assert;

import xdc.rov.ViewInfo;

import ti.sysbios.knl.Swi;
import ti.sysbios.syncs.SyncSwi;
import ti.sysbios.knl.Semaphore;
import ti.sysbios.gates.GateMutex;
import ti.sdo.ipc.MessageQ;
import ti.sdo.utils.INameServerRemote;

/*!
 *  ======== NameServerMessageQ ========
 *  Used by NameServer to communicate to remote processors.
 *
 *  This module is used by {@link ti.sdo.utils.NameServer} to communicate
 *  to remote processors using {@link ti.sdo.ipc.MessageQ}.
 *  There needs to be one instance between each two cores in the system.
 *  Interrupts must be enabled before using this module.
 *  This module does not require any share memory.
 */
@ModuleStartup
@InstanceFinalize

module NameServerMessageQ inherits INameServerRemote
{
    /*! maximum number of characters for name in bytes */
    const UInt maxNameLen = 32;

    /*!
     *  Assert raised if first MessageQ created already
     */
    config Assert.Id A_reservedMsgQueueId = {
        msg: "MessageQ Id 0 is reserved for NameServer"
    };

    /*!
     *  Assert raised if too many characters in the name
     */
    config Assert.Id A_nameIsTooLong = {
        msg: "Too many characters in name"
    };

    /*!
     *  Error raised if all the message queue objects are taken
     */
    config Error.Id E_outOfMemory  = {
        msg: "E_outOfMemory: MessageQ_alloc faild from heap: %d"
    };

    /*!
     *  ======== heapId ========
     *  The heap from which to alloc a message.
     */
    config UInt16 heapId = 0;

    /*!
     *  ======== timeoutInMicroSecs ========
     *  The timeout value in terms of microseconds
     *
     *  A NameServer request will return after this amout of time
     *  without a response. The default timeout value is 1 s.
     *  To not wait, use the value of '0'.  To wait forever, use '~(0)'.
     */
    config UInt timeoutInMicroSecs = 1000000;

internal:

    /*
     *  ======== timeout ========
     *  The timeout value to pass into Semaphore_pend
     *
     *  This value is calculated based on timeoutInMicroSecs and the
     *  SYSBIOS clock.tickPeriod.
     */
    config UInt timeout;

    /*!
     *  ======== Type ========
     *  The type of the message
     */
    enum Type {
        REQUEST =  0,
        RESPONSE = 1
    };

    /*!
     *  ======== swiFxn ========
     *  The swi function that will be executed during the call back.
     *
     *  @param(arg0)    argument 0 to swi function
     *  @param(arg1)    argument 1 to swi function
     */
    Void swiFxn(UArg arg0, UArg arg1);

    /* Instance state */
    struct Instance_State {
        UInt16              remoteProcId;   /* remote MultiProc id           */
    };

    /* Module state */
    struct Module_State {
        MessageQ.Handle     msgHandle;      /* messageQ for NameServer       */
        Swi.Handle          swiHandle;      /* instance swi object           */
        SyncSwi.Handle      syncSwiHandle;  /* syncSwi handle                */
        Semaphore.Handle    semRemoteWait;  /* sem to wait on remote proc    */
        GateMutex.Handle    gateMutex;      /* gate to protect critical code */
        Ptr                 msg;            /* pointer to response message   */
    };
}
