/*
 * Copyright (c) 2012-2014 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== NotifySetup.c ========
 */
#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Startup.h>

#include <ti/sdo/ipc/_Notify.h>
#include <ti/sdo/ipc/family/vayu/NotifyDriverMbx.h>
#include <ti/sdo/ipc/notifyDrivers/NotifyDriverShm.h>
#include <ti/sdo/utils/_MultiProc.h>

#if defined(xdc_target__isaCompatible_64P)

#include <ti/sysbios/family/c64p/EventCombiner.h>
#include <ti/sysbios/family/c64p/Hwi.h>
#include <ti/sysbios/family/shared/vayu/IntXbar.h>

#elif defined(xdc_target__isaCompatible_arp32)

#include <ti/sysbios/family/arp32/Hwi.h>

#elif defined(xdc_target__isaCompatible_v7M)

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/family/arm/ducati/Core.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>
#include <ti/sysbios/family/shared/vayu/IntXbar.h>

#elif defined(xdc_target__isaCompatible_v7A)

#include <ti/sysbios/family/arm/gic/Hwi.h>
#include <ti/sysbios/family/shared/vayu/IntXbar.h>

#else
#error Invalid target
#endif

#include "package/internal/NotifySetup.xdc.h"


#define EVENT_GROUP_SIZE 32

/* register access methods */
#define REG16(A)        (*(volatile UInt16 *)(A))
#define REG32(A)        (*(volatile UInt32 *)(A))

/* ipc helper macros */
#define MAILBOX_REG_VAL(m) (0x1 << (2 * (m)))

#define VIRTID(procId) (NotifySetup_procIdTable[(procId)])

#define MBX_BASEADDR_IDX(idx) ((NotifySetup_mailboxTable[(idx)] >> 16) & 0xFFFF)

#define MBX_USER_IDX(idx) ((NotifySetup_mailboxTable[(idx)] >> 8) & 0xFF)

#define SUBMBX_IDX(idx) (NotifySetup_mailboxTable[(idx)] & 0xFF)

#define MAILBOX_ADDR(idx) \
        (NotifySetup_mailboxBaseAddr[MBX_BASEADDR_IDX(idx)])

#define MAILBOX_STATUS(idx) \
        (MAILBOX_ADDR((idx)) + 0xC0 + (0x4 * SUBMBX_IDX((idx))))

#define MAILBOX_IRQENABLE_SET(idx) \
        (MAILBOX_ADDR((idx)) + 0x108 + (0x10 * MBX_USER_IDX((idx))))

#define MBOX_IRQ_ENABLE(idx) \
    ((REG32(MAILBOX_IRQENABLE_SET((idx))) & \
    MAILBOX_REG_VAL(SUBMBX_IDX((idx)))) != 0)

#define MBOX_MSG_COUNT(idx) (REG32(MAILBOX_STATUS((idx))))


/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*
 *  ======== NotifySetup_Module_startup ========
 */
Int NotifySetup_Module_startup(Int phase)
{
#if defined(xdc_target__isaCompatible_64P)

    extern cregister volatile UInt DNUM;

    if (!IntXbar_Module_startupDone()) {
        return (Startup_NOTDONE);
    }

    /* connect mailbox interrupts at startup */
    if (DNUM == 0) {               /* DSP1 */
        IntXbar_connect(24, 284);  // eve1 mailbox 0 user 1
        IntXbar_connect(25, 293);  // eve2 mailbox 0 user 1
        IntXbar_connect(26, 249);  // system mailbox 5 user 0
        NotifySetup_module->interruptTable[6] = 57; // IPU1-0
        NotifySetup_module->interruptTable[9] = 57; // IPU1-1

        /* plug eve3 and eve4 mbxs only if eve3 and eve4 exists */
        if ((MultiProc_getId("EVE3") != MultiProc_INVALIDID) ||
            (MultiProc_getId("EVE4") != MultiProc_INVALIDID)) {
            IntXbar_connect(27, 302);  // eve3 mailbox 0 user 1
            IntXbar_connect(28, 311);  // eve4 mailbox 0 user 1
        }

        /* plug mbx7 only if DSP2 or IPU2 exists */
        if ((MultiProc_getId("DSP2") != MultiProc_INVALIDID) ||
            (MultiProc_getId("IPU2") != MultiProc_INVALIDID) ||
            (MultiProc_getId("IPU2-0") != MultiProc_INVALIDID)) {
            IntXbar_connect(29, 257);  // system mailbox 7 user 0
            NotifySetup_module->interruptTable[7] = 60; // IPU2-0
        }

        /* plug mbx8 only if IPU2-1 exists */
        if (MultiProc_getId("IPU2-1") != MultiProc_INVALIDID) {
            IntXbar_connect(30, 261);  // system mailbox 8 user 0
            NotifySetup_module->interruptTable[10] = 61; // IPU2-1
        }
    }
    else if (DNUM == 1) {          /* DSP2 */
        IntXbar_connect(24, 287);  // eve1 mailbox 1 user 1
        IntXbar_connect(25, 296);  // eve2 mailbox 1 user 1
        IntXbar_connect(26, 253);  // system mailbox 6 user 0
        NotifySetup_module->interruptTable[7] = 57; // IPU2-0
        NotifySetup_module->interruptTable[10] = 57; // IPU2-1

        /* plug eve3 and eve4 mbxs only if eve3 and eve4 exists */
        if ((MultiProc_getId("EVE3") != MultiProc_INVALIDID) ||
            (MultiProc_getId("EVE4") != MultiProc_INVALIDID)) {
            IntXbar_connect(27, 305);  // eve3 mailbox 1 user 1
            IntXbar_connect(28, 314);  // eve4 mailbox 1 user 1
        }

        /* plug mbx7 only if DSP1 or IPU1 exists */
        if ((MultiProc_getId("DSP1") != MultiProc_INVALIDID) ||
            (MultiProc_getId("IPU1") != MultiProc_INVALIDID) ||
            (MultiProc_getId("IPU1-0") != MultiProc_INVALIDID)) {
            IntXbar_connect(29, 258);  // system mailbox 7 user 1
            NotifySetup_module->interruptTable[6] = 60; // IPU1-0
        }

        /* plug mbx8 only if IPU1-1 exists */
        if (MultiProc_getId("IPU1-1") != MultiProc_INVALIDID) {
            IntXbar_connect(30, 262);  // system mailbox 8 user 1
            NotifySetup_module->interruptTable[9] = 61; // IPU1-1
        }
    }

    return (Startup_DONE);

#elif defined(xdc_target__isaCompatible_arp32)

    /* nothing to do on this processor */
    return (Startup_DONE);

#elif defined(xdc_target__isaCompatible_v7M)

    if (!IntXbar_Module_startupDone()) {
        return (Startup_NOTDONE);
    }

    /* connect mailbox interrupts at startup */
    if (Core_ipuId == 1) {
        if ((BIOS_smpEnabled) || (Core_getId() == 0)) {
            /* IPU1-0 */
            IntXbar_connect(42, 285);  // eve1 mailbox 0 user 2
            IntXbar_connect(43, 294);  // eve2 mailbox 0 user 2
            IntXbar_connect(44, 250);  // system mailbox 5 user 1

            /* plug eve3 and eve4 mbxs only if eve3 and eve4 exists */
            if ((MultiProc_getId("EVE3") != MultiProc_INVALIDID) ||
                (MultiProc_getId("EVE4") != MultiProc_INVALIDID)) {
                IntXbar_connect(45, 303);  // eve3 mailbox 0 user 2
                IntXbar_connect(46, 312);  // eve4 mailbox 0 user 2
            }

            /* plug mbx7 only if DSP2, IPU1-1, or IPU2 exists */
            if ((MultiProc_getId("DSP2") != MultiProc_INVALIDID) ||
                (MultiProc_getId("IPU1-1") != MultiProc_INVALIDID) ||
                (MultiProc_getId("IPU2") != MultiProc_INVALIDID) ||
                (MultiProc_getId("IPU2-0") != MultiProc_INVALIDID)) {
                IntXbar_connect(47, 259);  // system mailbox 7 user 2
            }

            /* plug mbx8 only if IPU2-1 exists */
            if (MultiProc_getId("IPU2-1") != MultiProc_INVALIDID) {
                IntXbar_connect(48, 263);  // system mailbox 8 user 2
            }
        }
        else { /* IPU1-1 */
            IntXbar_connect(49, 289);  // eve1 mailbox 1 user 3
            IntXbar_connect(50, 298);  // eve2 mailbox 1 user 3
            IntXbar_connect(51, 252);  // system mailbox 5 user 3

            /* plug eve3 and eve4 mbxs only if eve3 and eve4 exists */
            if ((MultiProc_getId("EVE3") != MultiProc_INVALIDID) ||
                (MultiProc_getId("EVE4") != MultiProc_INVALIDID)) {
                IntXbar_connect(52, 307);  // eve3 mailbox 1 user 3
                IntXbar_connect(53, 316);  // eve4 mailbox 1 user 3
            }

            /* plug mbx8 only if DSP2, IPU1-0, or IPU2 exists */
            if ((MultiProc_getId("DSP2") != MultiProc_INVALIDID) ||
                (MultiProc_getId("IPU1-0") != MultiProc_INVALIDID) ||
                (MultiProc_getId("IPU2") != MultiProc_INVALIDID) ||
                (MultiProc_getId("IPU2-0") != MultiProc_INVALIDID)) {
                IntXbar_connect(54, 263);  // system mailbox 8 user 2
            }
        }
    }
    else {
        if ((BIOS_smpEnabled) || (Core_getId() == 0)) {
            /* IPU2-0 */
            IntXbar_connect(42, 288);  // eve1 mailbox 1 user 2
            IntXbar_connect(43, 297);  // eve2 mailbox 1 user 2
            IntXbar_connect(44, 254);  // system mailbox 6 user 1

            /* plug eve3 and eve4 mbxs only if eve3 and eve4 exists */
            if ((MultiProc_getId("EVE3") != MultiProc_INVALIDID) ||
                (MultiProc_getId("EVE4") != MultiProc_INVALIDID)) {
                IntXbar_connect(45, 306);  // eve3 mailbox 1 user 2
                IntXbar_connect(46, 315);  // eve4 mailbox 1 user 2
            }

            /* plug mbx7 only if DSP1 or IPU1 exists */
            if ((MultiProc_getId("DSP1") != MultiProc_INVALIDID) ||
                (MultiProc_getId("IPU1") != MultiProc_INVALIDID) ||
                (MultiProc_getId("IPU1-0") != MultiProc_INVALIDID)) {
                IntXbar_connect(47, 260);  // system mailbox 7 user 3
            }

            /* plug mbx8 only if IPU1-1 exists */
            if (MultiProc_getId("IPU1-1") != MultiProc_INVALIDID) {
                IntXbar_connect(48, 264);  // system mailbox 8 user 3
            }
        }
        else { /* IPU2-1 */
            IntXbar_connect(49, 289);  // eve1 mailbox 1 user 3
            IntXbar_connect(50, 298);  // eve2 mailbox 1 user 3
            IntXbar_connect(51, 256);  // system mailbox 6 user 3

            /* plug eve3 and eve4 mbxs only if eve3 and eve4 exists */
            if ((MultiProc_getId("EVE3") != MultiProc_INVALIDID) ||
                (MultiProc_getId("EVE4") != MultiProc_INVALIDID)) {
                IntXbar_connect(52, 307);  // eve3 mailbox 1 user 3
                IntXbar_connect(53, 316);  // eve4 mailbox 1 user 3
            }

            /* plug mbx8 only if DSP2 or IPU2 exists */
            if ((MultiProc_getId("DSP1") != MultiProc_INVALIDID) ||
                (MultiProc_getId("IPU1") != MultiProc_INVALIDID) ||
                (MultiProc_getId("IPU1-0") != MultiProc_INVALIDID)) {
                IntXbar_connect(54, 264);  // system mailbox 8 user 3
            }
        }
    }

    return (Startup_DONE);

#elif defined(xdc_target__isaCompatible_v7A)

    if (!IntXbar_Module_startupDone()) {
        return (Startup_NOTDONE);
    }

    /* connect mailbox interrupts at startup */
    IntXbar_connect(127, 286);  // eve1 mailbox 0 user 3
    IntXbar_connect(128, 295);  // eve2 mailbox 0 user 3
    IntXbar_connect(129, 251);  // system mailbox 5 user 2

    /* plug eve3 and eve4 mbxs only if eve3 and eve4 exists */
    if ((MultiProc_getId("EVE3") != MultiProc_INVALIDID) ||
        (MultiProc_getId("EVE4") != MultiProc_INVALIDID)) {
        IntXbar_connect(130, 304);  // eve3 mailbox 0 user 3
        IntXbar_connect(131, 313);  // eve4 mailbox 0 user 3
    }

    /* plug mbx6 only if DSP2 or IPU2 exists */
    if ((MultiProc_getId("DSP2") != MultiProc_INVALIDID) ||
        (MultiProc_getId("IPU2") != MultiProc_INVALIDID) ||
        (MultiProc_getId("IPU2-0") != MultiProc_INVALIDID)) {
        IntXbar_connect(134, 255);  // system mailbox 6 user 2
    }

    return (Startup_DONE);

#else
#error Invalid target
#endif
}

/*
 *  ======== NotifySetup_interruptTable ========
 */
UInt16 NotifySetup_interruptTable(Int srcVirtId)
{
    return (NotifySetup_module->interruptTable[srcVirtId]);
}

/*
 *  ======== NotifySetup_attach ========
 *  Create driver instance specified at config time.
 *
 *  This functions is generated by the NotifySetup.xdt template.
 */

/*
 *  ======== NotifySetup_sharedMemReq ========
 *  Compute how much shared memory is required by the driver.
 *
 *  This functions is generated by the NotifySetup.xdt template.
 */

/*
 * ======== NotifySetup_numIntLines ========
 * Return number of available interrupt lines to the current processor.
 */
UInt16 NotifySetup_numIntLines(UInt16 remoteProcId)
{
    return (1);
}

/*
 *  ======== NotifySetup_driverType ========
 *  Find driver type for given connection.
 *
 *  Search the connection array for the given remote processor. If
 *  found, return the requested notify driver type.
 */
NotifySetup_Driver NotifySetup_driverType(UInt16 remoteProcId)
{
    Int i;
    NotifySetup_Driver driver = NotifySetup_Driver_SHAREDMEMORY;

    /* look for remote processor in connection array */
    for (i = 0; i < NotifySetup_module->connAry.length; i++) {
        if (remoteProcId == NotifySetup_module->connAry.elem[i].procId) {
            driver = NotifySetup_module->connAry.elem[i].driver;
            break;
        }
    }

    return (driver);
}

/*
 *  ======== NotifySetup_plugHwi ========
 */
Void NotifySetup_plugHwi(UInt16 remoteProcId, Int cpuIntrNum,
        NotifySetup_DriverIsr isr)
{
    Error_Block eb;
    UInt        key;
    Hwi_Params  hwiParams;
    UInt16      srcVirtId;
#if defined(xdc_target__isaCompatible_64P)
    Int         eventId;
    UInt        combinedEventId;
#elif defined(xdc_target__isaCompatible_arp32)
    UInt        mbxIdx;
    Int         eventId;
    Bits16      mask;
#elif defined(xdc_target__isaCompatible_v7M) \
    || defined(xdc_target__isaCompatible_v7A)
    UInt16      idx;
    UInt        mbxIdx;
#endif

    Error_init(&eb);

    /* disable interrupts */
    key = Hwi_disable();

    /* map remote processor id to virtual id */
    srcVirtId = VIRTID(remoteProcId);

    /* save driver ISR in dispatch table */
    NotifySetup_module->isrDispatchTable[srcVirtId] = isr;

#if defined(xdc_target__isaCompatible_64P)

    /* program the event dispatcher */
    eventId = NotifySetup_module->interruptTable[srcVirtId];
    EventCombiner_dispatchPlug(eventId, NotifySetup_dispatchIsr, eventId, TRUE);

    /* make sure the interrupt is plugged only once */
    NotifySetup_module->numPlugged[0]++;

    if (NotifySetup_module->numPlugged[0] == 1) {
        combinedEventId = eventId / EVENT_GROUP_SIZE;

        Hwi_Params_init(&hwiParams);
        hwiParams.eventId = combinedEventId;
        hwiParams.arg = combinedEventId;
        hwiParams.enableInt = TRUE;

        Hwi_create(cpuIntrNum, &ti_sysbios_family_c64p_EventCombiner_dispatch,
                &hwiParams, &eb);
        /* TODO: add error handling */

        Hwi_enableInterrupt(cpuIntrNum);
    }

#elif defined(xdc_target__isaCompatible_arp32)

    if ((remoteProcId == NotifySetup_dsp1ProcId) ||
        (remoteProcId == NotifySetup_ipu1_0ProcId) ||
        (remoteProcId == NotifySetup_hostProcId)) {

        mbxIdx = 0;
    }
    else if ((remoteProcId == NotifySetup_dsp2ProcId) ||
        (remoteProcId == NotifySetup_ipu2_0ProcId) ||
        (remoteProcId == NotifySetup_ipu1_1ProcId) ||
        (remoteProcId == NotifySetup_ipu2_1ProcId)) {

        mbxIdx = 1;
    }
    else {
        mbxIdx = 2; /* remote processor must be EVEx */
    }

    /* make sure the interrupt is plugged only once */
    NotifySetup_module->numPlugged[mbxIdx]++;

    if (NotifySetup_module->numPlugged[mbxIdx] == 1) {
        eventId = NotifySetup_module->interruptTable[srcVirtId];

        /* compute the hwi mask */
        mask = (1 << NotifySetup_eveIntVectId_INTC0)
                | (1 << NotifySetup_eveIntVectId_INTC1);

        Hwi_Params_init(&hwiParams);
        hwiParams.arg = eventId;
        hwiParams.vectorNum = cpuIntrNum;
        hwiParams.maskSetting = Hwi_MaskingOption_BITMASK;
        hwiParams.disableIerMask = mask;
        hwiParams.restoreIerMask = mask;

        Hwi_create(eventId, NotifySetup_dispatchIsr, &hwiParams, &eb);
        /* TODO: add error handling */

        Hwi_enableInterrupt(NotifySetup_module->interruptTable[srcVirtId]);
    }

#elif defined(xdc_target__isaCompatible_v7M) \
    || defined(xdc_target__isaCompatible_v7A)

    /* compute table index for given source and destination */
    idx = (srcVirtId * NotifySetup_NUM_CORES) + VIRTID(MultiProc_self());

    /* compute mailbox index */
    mbxIdx = MBX_BASEADDR_IDX(idx);

    /* make sure the interrupt is plugged only once */
    NotifySetup_module->numPlugged[mbxIdx]++;

    if (NotifySetup_module->numPlugged[mbxIdx] == 1) {

        Hwi_Params_init(&hwiParams);
        hwiParams.maskSetting = Hwi_MaskingOption_LOWER;
        hwiParams.arg = cpuIntrNum;

        Hwi_create(cpuIntrNum, NotifySetup_dispatchIsr, &hwiParams, &eb);
        /* TODO: add error handling */

        Hwi_enableInterrupt(cpuIntrNum);
    }

#else
#error Invalid target
#endif

    /* restore interrupts */
    Hwi_restore(key);
}

/*
 *  ======== NotifySetup_unplugHwi ========
 */
Void NotifySetup_unplugHwi(UInt16 remoteProcId, Int cpuIntrNum)
{
    UInt        key;
    Hwi_Handle  hwi;
    UInt16      srcVirtId;
#if defined(xdc_target__isaCompatible_64P)
    Int         eventId;
#elif defined(xdc_target__isaCompatible_arp32)
    UInt        mbxIdx;
#elif defined(xdc_target__isaCompatible_v7M) \
    || defined(xdc_target__isaCompatible_v7A)
    UInt16      idx;
    UInt        mbxIdx;
#endif

    /* disable global interrupts (TODO: should be a gated module) */
    key = Hwi_disable();

    /* map processor id to virtual id */
    srcVirtId = VIRTID(remoteProcId);

    /* remove driver isr from dispatch table */
    NotifySetup_module->isrDispatchTable[srcVirtId] = NULL;

#if defined(xdc_target__isaCompatible_64P)

    /* unplug interrupt if last user */
    NotifySetup_module->numPlugged[0]--;

    if (NotifySetup_module->numPlugged[0] == 0) {
        hwi = Hwi_getHandle(cpuIntrNum);
        Hwi_delete(&hwi);
    }

    /* unprogram the event dispatcher */
    eventId = NotifySetup_module->interruptTable[srcVirtId];
    EventCombiner_disableEvent(eventId);

#elif defined(xdc_target__isaCompatible_arp32)

    if ((remoteProcId == NotifySetup_dsp1ProcId) ||
        (remoteProcId == NotifySetup_ipu1_0ProcId) ||
        (remoteProcId == NotifySetup_hostProcId)) {

        mbxIdx = 0;
    }
    else if ((remoteProcId == NotifySetup_dsp2ProcId) ||
        (remoteProcId == NotifySetup_ipu2_0ProcId) ||
        (remoteProcId == NotifySetup_ipu1_1ProcId) ||
        (remoteProcId == NotifySetup_ipu2_1ProcId)) {

        mbxIdx = 1;
    }
    else {
        mbxIdx = 2; /* remote processor must be EVEx */
    }

    /* unplug interrupt if last user */
    NotifySetup_module->numPlugged[mbxIdx]--;

    if (NotifySetup_module->numPlugged[0] == 0) {
        hwi = Hwi_getHandle(cpuIntrNum);
        Hwi_delete(&hwi);
    }

#elif defined(xdc_target__isaCompatible_v7M) \
    || defined(xdc_target__isaCompatible_v7A)

    /* decrement plug count */
    idx = (srcVirtId * NotifySetup_NUM_CORES) + VIRTID(MultiProc_self());
    mbxIdx = MBX_BASEADDR_IDX(idx);
    NotifySetup_module->numPlugged[mbxIdx]--;

    /* unplug interrupt if last user */
    if (NotifySetup_module->numPlugged[0] == 0) {
        hwi = Hwi_getHandle(cpuIntrNum);
        Hwi_delete(&hwi);
    }

#else
#error Invalid target
#endif

    /* restore global interrupts */
    Hwi_restore(key);
}

/*
 *  ======== NotifySetup_Shm_attach ========
 */
Int NotifySetup_Shm_attach(UInt16 remoteProcId, Ptr sharedAddr)
{
    NotifyDriverShm_Params notifyShmParams;
    NotifyDriverShm_Handle shmDrvHandle;
    ti_sdo_ipc_Notify_Handle notifyHandle;
    Int status = Notify_S_SUCCESS;
    Error_Block eb;

    Error_init(&eb);

    NotifyDriverShm_Params_init(&notifyShmParams);
    notifyShmParams.sharedAddr = sharedAddr;
    notifyShmParams.remoteProcId  = remoteProcId;

    /* Set the intVectorId if on the DSP */
    if ((MultiProc_self() == NotifySetup_dsp1ProcId) ||
        (MultiProc_self() == NotifySetup_dsp2ProcId)) {
            notifyShmParams.intVectorId = NotifySetup_dspIntVectId;
    }

    /* Set the intVectorId if on the EVE */
    if ((MultiProc_self() == NotifySetup_eve1ProcId) ||
        (MultiProc_self() == NotifySetup_eve2ProcId) ||
        (MultiProc_self() == NotifySetup_eve3ProcId) ||
        (MultiProc_self() == NotifySetup_eve4ProcId)) {

        if (VIRTID(remoteProcId) < 4) {
            notifyShmParams.intVectorId = NotifySetup_eveIntVectId_INTC1;
        }
        else {
            notifyShmParams.intVectorId = NotifySetup_eveIntVectId_INTC0;
        }
    }

    /* create the notify driver instance */
    shmDrvHandle = NotifyDriverShm_create(&notifyShmParams, &eb);

    if (shmDrvHandle == NULL) {
        return (Notify_E_FAIL);
    }

    /* create the front-end notify instance */
    notifyHandle = ti_sdo_ipc_Notify_create(
            NotifyDriverShm_Handle_upCast(shmDrvHandle), remoteProcId, 0,
            NULL, &eb);

    if (notifyHandle == NULL) {
        NotifyDriverShm_delete(&shmDrvHandle);
        status = Notify_E_FAIL;
    }

    return (status);
}

/*!
 *  ======== NotifySetup_Shm_sharedMemReq ========
 */
SizeT NotifySetup_Shm_sharedMemReq(UInt16 remoteProcId, Ptr sharedAddr)
{
    SizeT memReq;
    NotifyDriverShm_Params notifyShmParams;

    NotifyDriverShm_Params_init(&notifyShmParams);
    notifyShmParams.sharedAddr = sharedAddr;

    memReq = NotifyDriverShm_sharedMemReq(&notifyShmParams);

    return (memReq);
}

/*
 *  ======== NotifySetup_Mbx_attach ========
 */
Int NotifySetup_Mbx_attach(UInt16 remoteProcId, Ptr sharedAddr)
{
    Int status = Notify_S_SUCCESS;
    NotifyDriverMbx_Params params;
    NotifyDriverMbx_Handle driver;
    ti_sdo_ipc_Notify_Handle notify;
    UInt16 virtId;
    Error_Block eb;

    Error_init(&eb);

    NotifyDriverMbx_Params_init(&params);
    params.remoteProcId = remoteProcId;

    /* set the intVectorId if on the DSP */
    if ((MultiProc_self() == NotifySetup_dsp1ProcId) ||
        (MultiProc_self() == NotifySetup_dsp2ProcId)) {
        params.intVectorId = NotifySetup_dspIntVectId;
    }

    /* set the intVectorId if on the EVE */
    if ((MultiProc_self() == NotifySetup_eve1ProcId) ||
        (MultiProc_self() == NotifySetup_eve2ProcId) ||
        (MultiProc_self() == NotifySetup_eve3ProcId) ||
        (MultiProc_self() == NotifySetup_eve4ProcId)) {

        if (VIRTID(remoteProcId) < 4) {
            params.intVectorId = NotifySetup_eveIntVectId_INTC1;
        }
        else {
            params.intVectorId = NotifySetup_eveIntVectId_INTC0;
        }
    }

    /* set the intVectorId if on the IPU */
    if ((MultiProc_self() == NotifySetup_ipu1_0ProcId) ||
        (MultiProc_self() == NotifySetup_ipu1_1ProcId) ||
        (MultiProc_self() == NotifySetup_ipu2_0ProcId) ||
        (MultiProc_self() == NotifySetup_ipu2_1ProcId)) {

        virtId = VIRTID(remoteProcId);
        params.intVectorId = NotifySetup_module->interruptTable[virtId];
    }

    /* set the intVectorId if on the HOST */
    if (MultiProc_self() == NotifySetup_hostProcId) {
        virtId = VIRTID(remoteProcId);
        params.intVectorId = NotifySetup_module->interruptTable[virtId];
    }

    /* create the notify driver instance */
    driver = NotifyDriverMbx_create(&params, &eb);

    if (driver == NULL) {
        return (Notify_E_FAIL);
    }

    /* create the front-end notify instance */
    notify = ti_sdo_ipc_Notify_create(NotifyDriverMbx_Handle_upCast(driver),
            remoteProcId, 0, NULL, &eb);

    if (notify == NULL) {
        NotifyDriverMbx_delete(&driver);
        status = Notify_E_FAIL;
    }

    return (status);
}

/*!
 *  ======== NotifySetup_Mbx_sharedMemReq ========
 */
SizeT NotifySetup_Mbx_sharedMemReq(UInt16 remoteProcId, Ptr sharedAddr)
{
    SizeT memReq = 0;

    return (memReq);
}

/*
 *************************************************************************
 *                       Internal functions
 *************************************************************************
 */

/*
 *  ======== NotifySetup_dispatchIsr ========
 *  Dispatch the current interrupt to the appropriate notify driver
 *
 *  The given interrupt may be shared by multiple notify drivers. This
 *  ISR inspects the mailbox which raised the interrupt and looks for
 *  all FIFOs which have data and raise the given interrupt. For each
 *  one, the interrupt is dispatched to the registered driver for that
 *  FIFO.
 *
 *  @param(arg) The eventId which raised the interrupt.
 */
Void NotifySetup_dispatchIsr(UArg arg)
{
    Int numProcessed;
    UInt16 idx;
    UInt16 srcVirtId;
    UInt16 dstVirtId = VIRTID(MultiProc_self());
    NotifySetup_DriverIsr driver;

    do {
        numProcessed = 0;

        for (srcVirtId = 0; srcVirtId < NotifySetup_NUM_CORES; srcVirtId++) {

            /* skip null drivers, processor not in system or self */
            driver = NotifySetup_module->isrDispatchTable[srcVirtId];

            if (driver == NULL) {
                continue;
            }

            /* check if processor would raise the given hardware eventId */
            if (arg == NotifySetup_module->interruptTable[srcVirtId]) {

                /* compute table index for given source and destination */
                idx = (srcVirtId * NotifySetup_NUM_CORES) + dstVirtId;

                /* check if submailbox has a message and irq is enabled */
                if ((MBOX_MSG_COUNT(idx) != 0) && MBOX_IRQ_ENABLE(idx)) {

                    /* invoke driver isr to deliver the event */
                    (*driver)(idx);

                    /* event has been delivered */
                    numProcessed++;
                }
            }
        }
    } while (numProcessed != 0);
}
