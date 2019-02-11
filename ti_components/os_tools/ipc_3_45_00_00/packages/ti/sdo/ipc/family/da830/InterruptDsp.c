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
 *  ======== InterruptDsp.c ========
 *  Dsp interrupt manager.
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <ti/sysbios/family/c64p/Hwi.h>

#include <ti/sdo/ipc/Ipc.h>
#include <ti/sdo/ipc/notifyDrivers/IInterrupt.h>
#include "package/internal/InterruptDsp.xdc.h"

/* register use to generate interrupt between cores */
#define CHIPSIGREG  0x01C14174

/* event ids associated with inter-core interrupts */
#define DSP2ARM_CHIPINT0    28
#define DSP2ARM_CHIPINT1    29
#define ARM2DSP_CHIPINT2    5
#define ARM2DSP_CHIPINT3    67

/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*!
 *  ======== InterruptDsp_intEnable ========
 *  Enable GPP interrupt
 */
Void InterruptDsp_intEnable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    Hwi_enableInterrupt(intInfo->intVectorId);
}

/*!
 *  ======== InterruptDsp_intDisable ========
 *  Disables GPP interrupt
 */
Void InterruptDsp_intDisable(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    Hwi_disableInterrupt(intInfo->intVectorId);
}

/*!
 *  ======== InterruptDsp_intRegister ========
 *  Register ISR for remote processor interrupt
 */
Void InterruptDsp_intRegister(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
                              Fxn func, UArg arg)
{
    Hwi_Params  hwiAttrs;
    UInt        key;

    Assert_isTrue(intInfo->intVectorId <= 15,
                  ti_sdo_ipc_Ipc_A_internal);

    Assert_isTrue(intInfo->localIntId == ARM2DSP_CHIPINT2 ||
                  intInfo->localIntId == ARM2DSP_CHIPINT3,
                  ti_sdo_ipc_Ipc_A_internal);

    /* Disable global interrupts */
    key = Hwi_disable();

    InterruptDsp_intClear(remoteProcId, intInfo); //TODO

    /* Register interrupt for communication between ARM and DSP */
    Hwi_Params_init(&hwiAttrs);
    hwiAttrs.maskSetting = Hwi_MaskingOption_SELF;
    hwiAttrs.arg         = arg;
    hwiAttrs.eventId     = intInfo->localIntId;

    Hwi_create(intInfo->intVectorId,
               (Hwi_FuncPtr)func,
               &hwiAttrs,
               NULL);

    /* Restore global interrupts */
    Hwi_restore(key);

    /* enable the interrupt vector */
    Hwi_enableInterrupt(intInfo->intVectorId);
}

/*!
 *  ======== InterruptDsp_intUnregister ========
 */
Void InterruptDsp_intUnregister(UInt16 remoteProcId,
                                IInterrupt_IntInfo *intInfo)
{
    Hwi_Handle  hwiHandle;

    /* Delete the Hwi (and disable the corresponding interrupt) */
    hwiHandle = Hwi_getHandle(intInfo->intVectorId);
    Hwi_delete(&hwiHandle);
}

/*!
 *  ======== InterruptDsp_intSend ========
 *  Send interrupt to the remote processor
 */
Void InterruptDsp_intSend(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo,
                          UArg arg)
{
    UInt32 intBitPos;
    volatile UInt32 *chipSigReg = (volatile UInt32 *)CHIPSIGREG;

    switch (intInfo->remoteIntId) {
        case DSP2ARM_CHIPINT0:
            intBitPos = 0;
            break;
        case DSP2ARM_CHIPINT1:
            intBitPos = 1;
            break;
        default:
            intBitPos = 0;  /* keep Coverity happy */
        break;
    }

    chipSigReg[0] = (1 << intBitPos);
}

/*!
 *  ======== InterruptDsp_intPost ========
 */
Void InterruptDsp_intPost(UInt16 srcProcId, IInterrupt_IntInfo *intInfo,
                          UArg arg)
{
    UInt16 intBitPos;
    volatile UInt32 *chipSigReg = (volatile UInt32 *)CHIPSIGREG;

    switch (intInfo->localIntId) {
        case ARM2DSP_CHIPINT2:
            intBitPos = 2;
            break;
        case ARM2DSP_CHIPINT3:
            intBitPos = 3;
            break;
        default:
            intBitPos = 0;  /* keep Coverity happy */
        break;
    }

    chipSigReg[0] = (1 << intBitPos);
}

/*!
 *  ======== InterruptDsp_intClear ========
 *  Clear interrupt
 */
UInt InterruptDsp_intClear(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    UInt32 statBitPos;
    volatile UInt32 *chipSigReg = (volatile UInt32 *)CHIPSIGREG;

    switch (intInfo->localIntId) {
        case ARM2DSP_CHIPINT2:
            statBitPos = 2;
            break;
        case ARM2DSP_CHIPINT3:
            statBitPos = 3;
            break;
        default:
            statBitPos = 0; /* keep Coverity happy */
        break;
    }

    chipSigReg[1] = (1 << statBitPos);

    return (0);
}

Bool InterruptDsp_isIntSet(UInt16 remoteProcId, IInterrupt_IntInfo *intInfo)
{
    UInt32           statBitPos;
    volatile UInt32 *chipSigReg = (volatile UInt32 *)CHIPSIGREG;
    UInt32           mask;

    switch (intInfo->localIntId) {
        case ARM2DSP_CHIPINT2:
            statBitPos = 2;
            break;
        case ARM2DSP_CHIPINT3:
            statBitPos = 3;
            break;
        default:
            statBitPos = 0; /* keep Coverity happy */
        break;
    }

    mask = 1 << statBitPos;
    if ((chipSigReg[0] & mask) == mask) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}
