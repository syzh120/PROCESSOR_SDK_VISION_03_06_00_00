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
 *  ======== GateHWSpinlock.xdc ========
 *
 */

package ti.sdo.ipc.gates;

import xdc.runtime.Error;
import xdc.runtime.Assert;
import xdc.runtime.IGateProvider;
import xdc.runtime.Diags;
import xdc.runtime.Log;

import ti.sdo.ipc.interfaces.IGateMPSupport;

/*!
 *  ======== GateHWSpinlock ========
 *  Multiprocessor gate that utilizes a hardware spinlock
 */
@ModuleStartup

module GateHWSpinlock inherits IGateMPSupport
{
    /*!
     *  ======== BasicView ========
     *  @_nodoc
     */
    metaonly struct BasicView {
        UInt    lockNum;
        UInt    nested;
    }

    /*!
     *  ======== rovViewInfo ========
     *  @_nodoc
     */
    @Facet
    metaonly config xdc.rov.ViewInfo.Instance rovViewInfo =
        xdc.rov.ViewInfo.create({
            viewMap: [
                ['Basic',
                    {
                        type: xdc.rov.ViewInfo.INSTANCE,
                        viewInitFxn: 'viewInitBasic',
                        structName: 'BasicView'
                    }
                ],
            ]
        });

    /*!
     *  ======== LM_enter ========
     *  Logged on gate enter
     */
    config Log.Event LM_enter = {
        mask: Diags.USER1,
        msg: "LM_enter: Gate (lockNum = %d) entered, returning key = %d"
    };

    /*!
     *  ======== LM_leave ========
     *  Logged on gate leave
     */
    config Log.Event LM_leave = {
        mask: Diags.USER1,
        msg: "LM_leave: Gate (lockNum = %d) left using key = %d"
    };

    /*!
     *  ======== LM_create ========
     *  Logged on gate create
     */
    config Log.Event LM_create = {
        mask: Diags.USER1,
        msg: "LM_create: Gate (lockNum = %d) created"
    };

    /*!
     *  ======== LM_open ========
     *  Logged on gate open
     */
    config Log.Event LM_open = {
        mask: Diags.USER1,
        msg: "LM_open: Remote gate (lockNum = %d) opened"
    };

    /*!
     *  ======== LM_delete ========
     *  Logged on gate deletion
     */
    config Log.Event LM_delete = {
        mask: Diags.USER1,
        msg: "LM_delete: Gate (lockNum = %d) deleted"
    };

    /*!
     *  ======== LM_close ========
     *  Logged on gate close
     */
    config Log.Event LM_close = {
        mask: Diags.USER1,
        msg: "LM_close: Gate (lockNum = %d) closed"
    };

    /*!
     *  ======== A_invSpinLockNum ========
     *  Assert raised when provided lockNum is invalid for the relevant device
     */
    config Assert.Id A_invSpinLockNum  = {
        msg: "A_invSpinLockNum: Invalid hardware spinlock number"
    };

    /*! Device-specific base address for HW Semaphore subsystem */
    config Ptr baseAddr = null;

    /*!
     *  ======== setReserved ========
     *  Reserve a HW spinlock for use outside of IPC.
     *
     *  GateMP will, by default, manage all HW spinlocks on the device unless
     *  this API is used to set aside specific spinlocks for use outside
     *  of IPC.
     *
     *  @param(lockNum)      HW spinlock number to reserve
     */
    metaonly Void setReserved(UInt lockNum);



instance:

    /*!
     *  @_nodoc
     *  ======== enter ========
     *  Enter this gate
     */
    @DirectCall
    override IArg enter();

    /*!
     *  @_nodoc
     *  ======== leave ========
     *  Leave this gate
     */
    @DirectCall
    override Void leave(IArg key);

internal:

    /*! Device-specific number of semphores in the HW Semaphore subsystem */
    config UInt numLocks;

    /*! Mask of reserved HW spinlocks */
    config Bits32 reservedMaskArr[];

    struct Instance_State {
        UInt            lockNum;   /* The lock number being used */
        UInt            nested;    /* For nesting */
        IGateProvider.Handle     localGate;
    };
}
