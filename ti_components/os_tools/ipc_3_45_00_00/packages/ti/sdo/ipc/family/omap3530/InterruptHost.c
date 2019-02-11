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
 *  ======== InterruptHost.c ========
 *  Mailbox based interrupt manager
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>

#include <ti/sysbios/family/arm/a8/intcps/Hwi.h>

#include <ti/sdo/ipc/notifyDrivers/IInterrupt.h>

#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/utils/_MultiProc.h>

#include "package/internal/InterruptHost.xdc.h"

/* Register access method. */
#define REG32(A)   (*(volatile UInt32 *) (A))

/* Mailbox management values */
#define MAILBOX_BASE           0x48094000
#define MAILBOX_MESSAGE_0      MAILBOX_BASE + 0x40
#define MAILBOX_MESSAGE_1      MAILBOX_BASE + 0x44
#define MAILBOX_MSGSTATUS_0    MAILBOX_BASE + 0xC0
#define MAILBOX_MSGSTATUS_1    MAILBOX_BASE + 0xC4
#define MAILBOX_IRQSTATUS_GPP  MAILBOX_BASE + 0x100
#define MAILBOX_IRQSTATUS_DSP  MAILBOX_BASE + 0x108
#define MAILBOX_IRQENABLE_GPP  MAILBOX_BASE + 0x104
#define MAILBOX_IRQENABLE_DSP  MAILBOX_BASE + 0x10C

#define DSPINT  55
#define HOSTINT 26


/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*!
 *  ======== InterruptHost_intEnable ========
 */
Void InterruptHost_intEnable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    Hwi_enableInterrupt(HOSTINT);
}

/*!
 *  ======== InterruptHost_intDisable ========
 */
Void InterruptHost_intDisable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    Hwi_disableInterrupt(HOSTINT);
}

/*!
 *  ======== InterruptHost_intRegister ========
 */
Void InterruptHost_intRegister(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
                              Fxn func, UArg arg)
{
    UInt        key;
    Hwi_Params  hwiAttrs;

    /* Make sure that we're trying to talk to the HOST */
    Assert_isTrue(remoteProcId == MultiProc_getId("DSP"),
            ti_sdo_ipc_Ipc_A_invArgument);

    /* Disable global interrupts */
    key = Hwi_disable();

    InterruptHost_intClear(remoteProcId, intInfo);

    /* Register interrupt for communication between ARM and DSP */
    Hwi_Params_init(&hwiAttrs);
    hwiAttrs.maskSetting = Hwi_MaskingOption_SELF;
    hwiAttrs.arg         = arg;
    Hwi_create(HOSTINT,
               (Hwi_FuncPtr)func,
               &hwiAttrs,
               NULL);

    /* Enable the mailbox interrupt to the DSP */
    REG32(MAILBOX_IRQENABLE_GPP) = 0x4; /* Mailbox 0 */

    /* Restore global interrupts */
    Hwi_restore(key);

    /* Unmask IVA_2_IRQ[10] to allow interrupt to come into DSP */
    Hwi_enableInterrupt(HOSTINT);
}

/*!
 *  ======== InterruptHost_intUnregister ========
 */
Void InterruptHost_intUnregister(UInt16 remoteProcId,
                                IInterrupt_IntInfo *intInfo)
{
    Hwi_Handle  hwiHandle;

    /* Delete the Hwi (and disable the corresponding interrupt) */
    hwiHandle = Hwi_getHandle(HOSTINT);
    Hwi_delete(&hwiHandle);
}

/*!
 *  ======== InterruptHost_intSend ========
 *  Send interrupt to the remote processor
 */
Void InterruptHost_intSend(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
                          UArg arg)
{
    /* Put into the DSP's mailbox to generate the interrupt. */
    REG32(MAILBOX_MESSAGE_0) = arg;
}

/*!
 *  ======== InterruptHost_intPost ========
 */
Void InterruptHost_intPost(UInt16 srcProcId, IInterrupt_IntInfo *intInfo,
                          UArg arg)
{
    /* Put into the GPP's mailbox to generate the interrupt. */
    REG32(MAILBOX_MESSAGE_1) = arg;
}

/*!
 *  ======== Interrupt_intClear ========
 *  Clear interrupt
 */
UInt InterruptHost_intClear(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    UInt arg;

    /* Read into val. */
    arg = REG32(MAILBOX_MESSAGE_1);

    /*
     * Clear the IRQ status.
     * If there are more in the mailbox FIFO, it will re-assert.
     */
    REG32(MAILBOX_IRQSTATUS_GPP) = 0x4; /* Mailbox 0 */

    return (arg);
}
