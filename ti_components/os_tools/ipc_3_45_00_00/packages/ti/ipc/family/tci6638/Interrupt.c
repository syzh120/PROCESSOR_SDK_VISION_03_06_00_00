/*
 * Copyright (c) 2013-2015 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== Interrupt.c ========
 *  C647x based interrupt manager.
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <ti/sdo/ipc/notifyDrivers/IInterrupt.h>

#include "package/internal/Interrupt.xdc.h"


/*
 *  ======== Interrupt_intEnable ========
 */
Void Interrupt_intEnable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    Assert_isTrue(FALSE, Interrupt_A_notImplemented);
}

/*!
 *  ======== Interrupt_intDisable ========
 */
Void Interrupt_intDisable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    Assert_isTrue(FALSE, Interrupt_A_notImplemented);
}

/*
 *  ======== Interrupt_intRegister ========
 */
Void Interrupt_intRegister(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
        Fxn func, UArg arg)
{
    Assert_isTrue(FALSE, Interrupt_A_notImplemented);
}

Void Interrupt_intUnregister(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    Assert_isTrue(FALSE, Interrupt_A_notImplemented);
}

/*
 *  ======== Interrupt_intSend ========
 */
Void Interrupt_intSend(UInt16 procId, IInterrupt_IntInfo *intInfo, UArg arg)
{
    Assert_isTrue(FALSE, Interrupt_A_notImplemented);
}

/*
 *  ======== Interrupt_intClear ========
 */
UInt Interrupt_intClear(UInt16 procId, IInterrupt_IntInfo *intInfo)
{
    Assert_isTrue(FALSE, Interrupt_A_notImplemented);
    return (Interrupt_INVALIDPAYLOAD);
}

/*
 *  ======== Interrupt_checkAndClear ========
 */
UInt Interrupt_checkAndClear(UInt16 procId, IInterrupt_IntInfo *intInfo)
{
    Assert_isTrue(FALSE, Interrupt_A_notImplemented);
    return (0);
}
