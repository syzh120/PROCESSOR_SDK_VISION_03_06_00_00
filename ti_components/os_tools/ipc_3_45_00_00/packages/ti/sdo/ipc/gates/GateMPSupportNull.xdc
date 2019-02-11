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
 *  ======== GateMPSupportNull.xdc ========
 *
 */

import xdc.runtime.Assert;

/*!
 *  ======== GateMPSupportNull ========
 *  Module to plug GateMP proxies
 */
module GateMPSupportNull inherits ti.sdo.ipc.interfaces.IGateMPSupport
{

    /*!
     *  Assert raised when trying to use GateMPSupportNull's enter or leave
     */
    config Assert.Id A_invalidAction  = {
        msg: "A_invalidAction: Cannot use ti.sdo.ipc.gates.GateMPSupportNull"
    };

    /*!
     *  Error codes returned by certain calls in GateMP
     */
    enum Action {
        Action_NONE   =  0,
        Action_ASSERT =  1
    };

    /*!
     *  ======== action ========
     *  Assert if the enter and/or leave is called
     */
    config Action action = Action_ASSERT;

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

    struct Instance_State {
        UInt   resourceId;
    };

}
