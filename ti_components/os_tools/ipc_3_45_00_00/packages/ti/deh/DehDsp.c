/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
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
 *
 */

/*
 *  ======== DehDsp.c ========
 *
 */

#include <xdc/runtime/System.h>
#include <xdc/runtime/Startup.h>

#include <ti/sysbios/BIOS.h>
#if defined(HAS_AMMU)
#include <ti/sysbios/hal/ammu/AMMU.h>
#endif
#include <ti/sysbios/family/c64p/Hwi.h>
#include <ti/sysbios/family/c64p/Exception.h>

#include <ti/ipc/MultiProc.h>
#include <ti/deh/Watchdog.h>

#include "package/internal/Deh.xdc.h"

/*
 *  ======== Deh_Module_startup ========
 *
 *  Uses SYS/BIOS Exception handler function for Hwi-based Watchdog ISR.
 *  This is used in order to cause the Watchdog expiration to appear like
 *  an exception, but since Exception_handler() is not called from the
 *  exception dispatcher (Hwi 1, NMI vector) the register and stack
 *  information that is printed is not valid (all zeroes for my runs).
 *  And we can't just plug the exception dispatcher into an Hwi, since it
 *  looks for an actual exception status and returns immediately (through
 *  NRP, which wasn't set for an Hwi) when no real exception is seen.
 */
Int Deh_Module_startup(Int phase)
{
#if defined(HAS_AMMU)
    if (AMMU_Module_startupDone() == TRUE) {
        Watchdog_init((Void (*)(Void))ti_sysbios_family_c64p_Exception_handler);
        return Startup_DONE;
    }

    return Startup_NOTDONE;
#else
    Watchdog_init((Void (*)(Void))ti_sysbios_family_c64p_Exception_handler);

    return Startup_DONE;
#endif
}

/*
 *  ======== Deh_idleBegin ========
 */
Void Deh_idleBegin(Void)
{
    Watchdog_idleBegin();
}

/*
 *  ======== Deh_excHandlerDsp ========
 *  Read data from exception handler and print it to crash dump buffer
 */
Void Deh_excHandlerDsp()
{
    Exception_Status excStatus;
    Exception_getLastStatus(&excStatus);
    memcpy(module->outbuf, excStatus.excContext, sizeof(*excStatus.excContext));

    System_abort("Terminating execution...\n");
}
