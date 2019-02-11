/*
 * Copyright (c) 2012, Texas Instruments Incorporated
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
 * ======== timer.c ========
 *
 * Timer support
 *
 */

#include <stkmain.h>

/* Timer */
typedef struct _timer {
        uint            Type;           /* Set to HTYPE_TIMER */
        struct _timer   *pNext;         /* Pointer to next timer */
        void (*pHandler)( uint );       /* Message Handler */
        uint            Msg;            /* Message to send on trigger */
        uint            Trigger;        /* Trigger val (in half secs) */
        uint            Period;         /* Trigger val (in half secs) */
       } TTIMER;

static TTIMER *ptFirst = 0;
static uint   MasterTicks = 0;

static void TimerListInsert( TTIMER *pt );
static void TimerListRemove( TTIMER *pt );

/*-------------------------------------------------------------------- */
/* TimerNew() */
/* Creates a task owned timer */
/*-------------------------------------------------------------------- */
HANDLE TimerNew( void (*pHandler)(uint), uint HSCount, uint Msg )
{
    TTIMER *pt;

    /* Timers should all be alloced up front - If the alloc fails, */
    /* we're pretty much toast. However, we won't lock ... */
    if( !(pt = mmAlloc(sizeof(TTIMER))) )
    {
        DbgPrintf(DBG_ERROR,"TimerNew: OOM");
        NotifyLowResource();
        return( 0 );
    }

    /* Initialize type */
    pt->Type = HTYPE_TIMER;

    /* Initialize "program" */
    pt->pHandler = pHandler;
    pt->Msg      = Msg;
    pt->Period   = HSCount;

    /* Insert into list */
    TimerListInsert(pt);

    return( (HANDLE)pt );
}

/*-------------------------------------------------------------------- */
/* TimerFree() */
/* Destroys a task owned timer */
/*-------------------------------------------------------------------- */
void TimerFree( HANDLE h )
{
    TTIMER *pt = (TTIMER *)h;

#ifdef _STRONG_CHECKING
    if( !pt || pt->Type != HTYPE_TIMER )
    {
        DbgPrintf(DBG_ERROR,"TimerFree: HTYPE %04x",pt->Type);
        return;
    }
#endif

    /* Remove from list */
    TimerListRemove( pt );

    /* Kill type for debug */
    pt->Type = 0;

    mmFree( h );
}

/*-------------------------------------------------------------------- */
/* TimerHSTick() */
/* Services all timers */
/*-------------------------------------------------------------------- */
void TimerHSTick()
{
    TTIMER *pt;

    /* Bump the master count */
    MasterTicks++;

    /* The timeout list is pre-sorted by time. Continue triggering */
    /* timers until we get ONE that isn't ready. */

    while( (pt=ptFirst) && pt->Trigger == MasterTicks )
    {
        /* Go to next timer */
        ptFirst = pt->pNext;

        /* Put TIMER back in list */
        TimerListInsert(pt);

        /* Post Task Message */
        pt->pHandler( pt->Msg );
    }
}

/*-------------------------------------------------------------------- */
/* TimerListInsert() */
/*-------------------------------------------------------------------- */
static void TimerListInsert( TTIMER *pt )
{
    TTIMER *ptTmp;

    pt->Trigger = pt->Period + MasterTicks;

    /* Check the easy case - being first */
    if( !ptFirst
        || (ptFirst->Trigger-MasterTicks) >= (pt->Trigger-MasterTicks) )
    {
        /* What we point to next */
        pt->pNext = ptFirst;
        /* Before us...pointing to us */
        ptFirst = pt;
    }
    else
    {
        /* Find an entry we expire AFTER */
        ptTmp = ptFirst;
        while( ptTmp->pNext && (ptTmp->pNext->Trigger-MasterTicks)
                                < (pt->Trigger-MasterTicks) )
            ptTmp = ptTmp->pNext;

        /* What we point to next (can be NULL) */
        pt->pNext = ptTmp->pNext;
        /* Before us...pointing to us (can be overwiting a NULL) */
        ptTmp->pNext = pt;
    }
}

/*-------------------------------------------------------------------- */
/* TimerListRemove() */
/*-------------------------------------------------------------------- */
static void TimerListRemove( TTIMER *pt )
{
    TTIMER *ptTmp;

    /* Check to see if we're the head of the list */
    if( pt == ptFirst )
        ptFirst = pt->pNext;
    else
    {
        /* Look for us */
        ptTmp = ptFirst;
        while( ptTmp && ptTmp->pNext != pt )
            ptTmp = ptTmp->pNext;

        /* Patch entry which points to us (if any) */
        if( ptTmp )
            ptTmp->pNext = pt->pNext;
    }
}

