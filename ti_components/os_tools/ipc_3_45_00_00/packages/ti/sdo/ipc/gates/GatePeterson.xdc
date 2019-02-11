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
 *  ======== GatePeterson.xdc ========
 *
 */

package ti.sdo.ipc.gates;

import xdc.runtime.Error;
import xdc.runtime.Assert;
import xdc.runtime.IGateProvider;
import xdc.runtime.Diags;
import xdc.runtime.Log;
import xdc.rov.ViewInfo;

import ti.sdo.utils.MultiProc;
import ti.sdo.ipc.Ipc;

import ti.sdo.ipc.interfaces.IGateMPSupport;

/*!
 *  ======== GatePeterson ========
 *  IGateMPSupport gate based on the Peterson algorithm
 *
 *  This module implements the {@link ti.sdo.ipc.interfaces.IGateMPSupport}
 *  interface using the Peterson Algorithm in shared memory. This
 *  implementation works for only 2 processors.
 *
 *  Each GatePeterson instance requires a small piece of
 *  shared memory.  The base address of this shared memory is specified as
 *  the 'sharedAddr' argument to the create. The amount of shared memory
 *  consumed by a single instance can be obtained using the
 *  {@link #sharedMemReq} call.
 *
 *  Shared memory has to conform to the following specification.  Padding is
 *  added between certain elements in shared memory if cache alignment is
 *  required for the region in which the instance is placed.
 *
 *  @p(code)
 *
 *              shmBaseAddr -> --------------------------- bytes
 *                             |  version                | 4
 *              (Attrs struct) |  creatorProcId          | 2
 *                             |  openerProcId           | 2
 *                             |  (PADDING if aligned)   |
 *                             |-------------------------|
 *                             |  flag[0]                | 2
 *                             |  (PADDING if aligned)   |
 *                             |-------------------------|
 *                             |  flag[1]                | 2
 *                             |  (PADDING if aligned)   |
 *                             |-------------------------|
 *                             |  turn                   | 2
 *                             |  (PADDING if aligned)   |
 *                             |-------------------------|
 *  @p
 */
@InstanceInitError
@InstanceFinalize

module GatePeterson inherits IGateMPSupport
{
    /*! @_nodoc */
    metaonly struct BasicView {
        String  objType;
        Ptr     localGate;
        UInt    nested;
        UInt    creatorProcId;
        UInt    openerProcId;
        String  gateOwner;
    }

    /*! @_nodoc */
    @Facet
    metaonly config ViewInfo.Instance rovViewInfo =
        ViewInfo.create({
            viewMap: [
                ['Basic',
                    {
                        type: ViewInfo.INSTANCE,
                        viewInitFxn: 'viewInitBasic',
                        structName: 'BasicView'
                    }
                ],
            ]
        });

    /*!
     *  ======== E_gateRemotelyOpened ========
     *  Error raised when gate cannot be opened because of the opener's ID
     *
     *  Error raised in {@link #open} when trying to remotely open a
     *  GatePeterson instance whose configured opener processor Id does
     *  not match that of the opener's MultiProc id. but it has already been
     *  opened/created on two other processors.  GatePeterson only works with
     *  two processors.
     */
    config Error.Id E_gateRemotelyOpened  = {
        msg: "E_gateRemotelyOpened: Gate already in use by two other processors: creator: %d, opener: %d"
    };

    /*!
     *  ======== numInstances ========
     *  Maximum number of instances supported by the GatePeterson module
     */
    config UInt numInstances = 512;

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

    /* Used for the 'flag' in shared memory */
    const UInt32 FREE = 0;
    const UInt32 BUSY = 1;

    /* Stored in shared memory */
    struct Attrs {
        Bits16   creatorProcId;
        Bits16   openerProcId;
    };

    /* initializes shared memory */
    Void postInit(Object *obj);

    struct Instance_State {
        Attrs           *attrs;
        volatile Bits16 *flag[2];
        volatile Bits16 *turn;
        UInt16          selfId;
        UInt16          otherId;
        UInt            nested;    /* For nesting */
        IGateProvider.Handle localGate;
        Ipc.ObjType     objType;
        SizeT           cacheLineSize;
        Bool            cacheEnabled;
    };
}
