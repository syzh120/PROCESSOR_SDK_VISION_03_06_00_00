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
 *  ======== GateAAMonitor.xdc ========
 *
 */

package ti.sdo.ipc.gates;

import xdc.runtime.Error;
import xdc.runtime.Assert;
import xdc.runtime.IGateProvider;
import xdc.runtime.Diags;
import xdc.runtime.Log;

import ti.sdo.ipc.Ipc;

import ti.sdo.ipc.interfaces.IGateMPSupport;

/*!
 *  ======== GateAAMonitor ========
 *  Multiprocessor gate that utilizes an atomic access monitor (AAM)
 */
@InstanceInitError

module GateAAMonitor inherits IGateMPSupport
{
    /*! @_nodoc */
    metaonly struct BasicView {
        Ptr     sharedAddr;
        UInt    nested;
        String  enteredBy;     /* Entered or free */
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
     *  ======== A_invSharedAddr ========
     *  Assert raised when supplied sharedAddr is invalid
     *
     *  C6472 requires that shared region 0 be placed in SL2 memory and that
     *  all GateMP instances be allocated from region 0.  The gate itself may
     *  be used to protect the contents of any shared region.
     */
    config Assert.Id A_invSharedAddr  = {
        msg: "A_invSharedAddr: Address must be in shared L2 address space"
    };

    /*!
     *  ======== numInstances ========
     *  Maximum number of instances supported by the GateAAMonitor module
     */
    config UInt numInstances = 32;

instance:


internal:

    /*! Get the lock */
    @DirectCall
    UInt getLock(Ptr sharedAddr);

    /*! L1D cache line size is 64 */
    const UInt CACHELINE_SIZE = 64;

    /*!
     *  Range of SL2 RAM on TMS320TCI6486. Used for ensuring sharedAddr is
     *  valid
     */
    const Ptr SL2_RANGE_BASE = 0x00200000;
    const Ptr SL2_RANGE_MAX  = 0x002bffff;

    struct Instance_State {
        volatile UInt32*    sharedAddr;
        UInt                nested;    /* For nesting */
        IGateProvider.Handle localGate;
    };
}
