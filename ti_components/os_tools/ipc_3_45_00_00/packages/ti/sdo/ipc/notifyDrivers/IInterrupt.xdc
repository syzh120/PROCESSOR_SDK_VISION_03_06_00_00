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
 *  ======== IInterrupt.xdc ========
 *
 */

/*!
 *  ======== IInterrupt ========
 *  Interface for the inter-processor interrupts
 */
interface IInterrupt {

    struct IntInfo {
        UInt  localIntId;
        UInt  remoteIntId;
        UInt  intVectorId;
    }

    /*!
     *  ======== intEnable ========
     *  Enables the interrupt corresponding to intId
     *
     *  @param(remoteProcId)  Remote MultiProc Id
     *  @param(intInfo)       Information needed to configure interrupt line
     */
    @DirectCall
    Void intEnable(UInt16 remoteProcId, IntInfo *intInfo);

    /*!
     *  ======== intDisable ========
     *  Disables the interrupt corresponding to intId
     *
     *  @param(remoteProcId)  Remote MultiProc Id
     *  @param(intInfo)       Information needed to configure interrupt line
     */
    @DirectCall
    Void intDisable(UInt16 remoteProcId, IntInfo *intInfo);

    /*!
     *  ======== intRegister ========
     *  Register an interrupt line to a remote processor
     *
     *  @param(remoteProcId)  Remote MultiProc Id
     *  @param(intInfo)       Information needed to configure interrupt line
     *  @param(func)          Function to register.
     *  @param(arg)           Argument that will be passed to func
     */
    @DirectCall
    Void intRegister(UInt16 remoteProcId, IntInfo *intInfo, Fxn func, UArg arg);

    /*!
     *  ======== intUnregister ========
     *  Unregister an interrupt line to a remote processor
     *
     *  @param(remoteProcId)  Remote MultiProc Id
     *  @param(intInfo)       Information needed to configure interrupt line
     */
    @DirectCall
    Void intUnregister(UInt16 remoteProcId, IntInfo *intInfo);

    /*!
     *  ======== intSend ========
     *  Send interrupt to the remote processor
     *
     *  @param(remoteProcId)  Remote MultiProc Id
     *  @param(intInfo)       Information needed to configure interrupt line
     *  @param(arg)           Argument for sending interrupt.
     */
    @DirectCall
    Void intSend(UInt16 remoteProcId, IntInfo *intInfo, UArg arg);

    /*!
     *  @_nodoc
     *  Post an interrupt locally.
     *
     *  Used to simulate receiving an interrupt from a remote (source)
     *  processor
     *
     *  @param(remoteProcId)  Source MultiProc Id
     *  @param(intInfo)       Information needed to configure interrupt line
     *  @param(arg)           Argument for sending interrupt.
     */
    @DirectCall
    Void intPost(UInt16 srcProcId, IntInfo *intInfo, UArg arg);

    /*!
     *  ======== intClear ========
     *  Clear interrupt
     *
     *  @param(remoteProcId)  Remote MultiProc Id
     *  @param(intInfo)       Information needed to configure interrupt line
     *
     *  @b(returns)           Value (if any) of the interrupt before
     *                        it was cleared
     */
    @DirectCall
    UInt intClear(UInt16 remoteProcId, IntInfo *intInfo);
}
