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
 * ======== lltimer_bios6.c ========
 *
 * Interface to low-level Timer support
 * (DSP/BIOS6 PRD Based Timing)
 *
 * Note: This driver requires that a 100ms DSP/BIOS PRD timer
 * be added to the aplicatons TCF file, and set to call the
 * function llTimerTick() exported by this module.
 *
 */
#include <netmain.h>
#include <stkmain.h>
#include <ti/sysbios/knl/Clock.h> 

/*--------------------------------------------------------------------- */
/* TIMER Functions */
/*--------------------------------------------------------------------- */

/*
 * This define is set to "1" to allow the timer to get down to 1mS
 * accuracy by using the DSP/BIOS CLK low-resolution time.
 * Set this define to "0" if the DSP/BIOS CLK is *not* based on 1mS
 */
#define DSPBIOS_ENHANCED    1


/*----------------------- */
/* Timer Device */
/*----------------------- */
static UINT32      TimeStart;       /* Time of initialization */
static UINT32      TimeS;           /* Time in seconds */
static UINT32      TimeMS;          /* Time fraction in MS */
static UINT32      LastCLKTime;     /* Last Time value returned from CLK function */
static uint        LastCLKValid;     /* Last Time value returned from CLK function */
static int         TimerOpen = 0;   /* Flag to know if we should be active */

/* This is the semaphore to signal when we have an event */
static STKEVENT_Handle hEvent;

/*-------------------------------------------------------------------- */
/* llTimerTick() */
/* This task just counts HS Ticks as it is called from a DSP/BIOS */
/* PRD function running at 100ms. */
/*-------------------------------------------------------------------- */
void llTimerTick()
{
#ifdef USER_LED1
    LED_TOGGLE( USER_LED1 );
#endif

    if( TimerOpen )
    {
#if DSPBIOS_ENHANCED
        LastCLKTime  = Clock_getTicks();
        LastCLKValid = 1;
#endif
        TimeMS += 100;
        if( TimeMS >= 1000 )
        {
            TimeS++;
            TimeMS -= 1000;
        }
        STKEVENT_signal( hEvent, STKEVENT_TIMER, 1 );
    }
}

/*-------------------------------------------------------------------- */
/* _llTimerInit() */
/* Initiate low-level timer support. Called with current time */
/* in seconds. Timer has a 130 year wrap, so starting time */
/* reference should be chosen with some care. The reference is */
/* irrelevant, but should be consisitent. */
/*-------------------------------------------------------------------- */
void _llTimerInit( STKEVENT_Handle h, UINT32 ctime )
{
    hEvent = h;
    TimeStart = TimeS = ctime;
    TimeMS = 0;
    TimerOpen = 1;
#if DSPBIOS_ENHANCED
    LastCLKValid = 0;
#endif
}

/*-------------------------------------------------------------------- */
/* _llTimerShutdown() */
/* Shutdown low-level timer support */
/*-------------------------------------------------------------------- */
void _llTimerShutdown()
{
    TimerOpen = 0;
}

/*-------------------------------------------------------------------- */
/* llTimerGetTime() */
/* Called to get the system time in S and optionally MS from bootup. */
/*-------------------------------------------------------------------- */
UINT32 llTimerGetTime( UINT32 *pMSFrac )
{
    register uint mask,sec;

    mask = OEMSysCritOn();

    sec = TimeS;
    if(pMSFrac)
    {
#if DSPBIOS_ENHANCED
        if( LastCLKValid )
            *pMSFrac = TimeMS + (Clock_getTicks() - LastCLKTime);
        else
            *pMSFrac = TimeMS;
#else
        *pMSFrac = TimeMS;
#endif
    }

    OEMSysCritOff(mask);

    return(sec);
}

/*-------------------------------------------------------------------- */
/* llTimerGetStartTime() */
/* Called to get the time in S at which the timer was initialized. */
/*-------------------------------------------------------------------- */
UINT32 llTimerGetStartTime()
{
    return( TimeStart );
}
