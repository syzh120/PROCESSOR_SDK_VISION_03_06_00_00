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
 *  ======== GateHWSem.xdc ========
 *
 */

package ti.sdo.ipc.gates;

import xdc.runtime.Assert;
import xdc.runtime.IGateProvider;

import ti.sdo.ipc.interfaces.IGateMPSupport;

/*!
 *  ======== GateHWSem ========
 *  Multiprocessor gate that utilizes hardware semaphores
 */
@ModuleStartup

module GateHWSem inherits IGateMPSupport
{
    /*! @_nodoc */
    metaonly struct BasicView {
        Ptr     semNum;
        UInt    nested;
        String  enteredBy;      /* Which core has entered the hw sem */
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
     *  ======== A_invSemNum ========
     *  Asserted when supplied semNum is invalid for the relevant device
     */
    config Assert.Id A_invSemNum  = {
        msg: "A_invSemNum: Invalid hardware semaphore number"
    };

    /*!
     *  ======== setReserved ========
     *  Reserve a HW sempahore for use outside of IPC.
     *
     *  GateMP will, by default, manage all HW semaphores on the device unless
     *  this API is used to set aside specific HW semaphores for use outside
     *  of IPC.
     *
     *  @param(semNum)      HW semaphore number to reserve
     */
    metaonly Void setReserved(UInt semNum);

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

    /*! Device-specific base address for HW Semaphore subsystem */
    config Ptr baseAddr;

    /*! Device-specific query offset for HW Semaphore subsystem (for ROV) */
    config Ptr queryAddr;

    /*! Device-specific number of semphores in the HW Semaphore subsystem */
    config UInt numSems;

    /*! Mask of reserved HW semaphores */
    config Bits32 reservedMaskArr[];

    struct Instance_State {
        UInt                     semNum;    /* The sem number being used */
        UInt                     nested;    /* For nesting */
        IGateProvider.Handle     localGate;
    };
}
