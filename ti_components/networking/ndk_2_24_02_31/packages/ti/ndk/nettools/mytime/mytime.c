/*
 * Copyright (c) 2013, Texas Instruments Incorporated
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
 * */
/*
 *  ======== mytime.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <stdint.h>

#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Swi.h>

#include <ti/ndk/inc/netmain.h>
#include <ti/ndk/inc/_stack.h>
#include <ti/ndk/nettools/mytime/mytime.h>

/* Flag used to avoid re-initialization */
static int initialized = 0;

/*
 * currentTime is used to keep count of the number of seconds since the epoch.
 * In our case, the epoch is defined to be January 1, 1970, 00:00:00
 */
static uint32_t currentTime = 0;

/* Use the Clock module to imitate a real time clock */
static Clock_Handle systemClock = NULL;

/*
 *  ======== tick ========
 */
static void tick(unsigned int arg0)
{
    Swi_disable();
    currentTime++;
    Swi_enable();
}

/*
 *  ======== MYTIME_gettime ========
 */
uint32_t MYTIME_gettime(void)
{
    return (currentTime);
}

/*
 *  ======== MYTIME_settime ========
 */
void MYTIME_settime(uint32_t newtime)
{
    currentTime = newtime;
}

/*
 *  ======== MYTIME_init ========
 */
void MYTIME_init(void)
{
    Clock_Params clkParams;

    /* Don't re-initialize before MYTIME_exit is called */
    if (initialized) {
        return;
    }

    /*
     *  Create BIOS Clock instance with function tick(), period = 1 sec.
     *  This clock is used to imitate a real time clock for systems that don't
     *  actually have one. Its function increments the currentTime.
     */
    Clock_Params_init(&clkParams);
    clkParams.period = 1000;
    clkParams.startFlag = TRUE;
    systemClock = Clock_create((ti_sysbios_knl_Clock_FuncPtr)tick,
            clkParams.period, &clkParams, NULL);
    if (!systemClock) {
        System_abort("MYTIME_init: Error: sytem clock creation failed\n");
    }

    /* Set flag indicating that initialization has completed */
    initialized = 1;
}

/*
 *  ======== MYTIME_exit ========
 */
void MYTIME_exit(void)
{
    /* Don't free anything unless we've already initialized! */
    if (!initialized) {
        return;
    }
    Clock_stop(systemClock);
    Clock_delete(&systemClock);

    /* Set flag indicating that de-initialization has completed */
    initialized = 0;
}
