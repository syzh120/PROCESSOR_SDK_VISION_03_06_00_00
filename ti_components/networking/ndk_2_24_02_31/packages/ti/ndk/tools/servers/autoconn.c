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
 * */
/*
 * ======== autoconn.c ========
 *
 * This program implements an auto-connecting mechanism for PPP.
 *
 */

#include <netmain.h>
#include <_stack.h>
#include "autoconn.h"

/* State Machine Values */
#define AC_IDLE             0
#define AC_CONNECTING       1
#define AC_CONNECTED        2

static HANDLE hWakeSem      = 0;
static HANDLE hPPPOE        = 0;
static HANDLE hAutoConn     = 0;
static uint NeedConnect     = 0;
static uint NeedDisconnect  = 0;
static uint AutoState       = AC_IDLE;
static uint AutoStatus      = AC_STATUS_CLOSED;

static uint acerr[] = { AC_STATUS_NOPPPOE, AC_STATUS_LCPFAIL,
                        AC_STATUS_AUTHFAIL, AC_STATUS_IPCFGFAIL };

static void autoconn( AUTOCONNPARM *pac );
static void RouteHook( uint msg, UINT32 param1, UINT32 param2 );

_extern HANDLE  IFIndexGetHandle( uint Index );

/*--------------------------------------------------------------------- */
/* AutoConnOpen() */
/* Open the autoconn task */
/*--------------------------------------------------------------------- */
void AutoConnOpen( AUTOCONNPARM *pac )
{
    if( !hAutoConn )
    {
        hAutoConn = TaskCreate( autoconn, "AutoConn", OS_TASKPRINORM, 1500,
                                (UINT32)pac, 0, 0 );
    }
}

/*--------------------------------------------------------------------- */
/* AutoConnClose() */
/* Close the autoconn task when active */
/*--------------------------------------------------------------------- */
void AutoConnClose()
{
    if( hAutoConn )
    {
        /* Close PPPoE if open */
        if( AutoState != AC_IDLE )
        {
            pppoeFree( hPPPOE );
            AutoState = AC_IDLE;
        }

        /* Un-Hook the route control message (stack function needs llEnter/llExit) */
        llEnter();
        RTCRemoveHook( &RouteHook );
        llExit();

        /* Free up our semaphore */
        if( hWakeSem )
        {
            SemDelete( hWakeSem );
            hWakeSem = 0;
        }

        TaskDestroy( hAutoConn );
        hAutoConn  = 0;
    }
    AutoStatus = AC_STATUS_CLOSED;
}

/*--------------------------------------------------------------------- */
/* AutoConnGetStatus() */
/* Get the current connection status (and last error) */
/*--------------------------------------------------------------------- */
uint AutoConnGetStatus()
{
    return( AutoStatus );
}

/*--------------------------------------------------------------------- */
/* AutoConnSetConnect() */
/* Set connection status to disconnect (0) or connect (1) */
/*--------------------------------------------------------------------- */
void AutoConnSetConnect( uint connectflag )
{
    if( connectflag )
        NeedConnect = 1;
    else
        NeedDisconnect = 1;

     if( hWakeSem )
         SemPost( hWakeSem );
}

/*  autoconn */
/*  PPPoE auto-connect function with second based idle timeout */
static void autoconn( AUTOCONNPARM *pac )
{
    UINT32 tmp      = 0;
    UINT32 lastRx   = 0;
    UINT32 lastTx   = 0;
    UINT32 lastTime = 0;

    /* Create wake semaphore for callback to wake us */
    hWakeSem = SemCreate(0);
    if( !hWakeSem )
        return;

    /* Install callback (stack function needs llEnter/llExit) */
    llEnter();
    RTCAddHook( &RouteHook );
    llExit();

    /* Start with a need to connect */
    NeedConnect = 1;

    /* Init the AutoState machine */
    AutoState = AC_IDLE;
    AutoStatus = AC_STATUS_IDLE;

    DbgPrintf(DBG_INFO, "autoconn: PPPoE Auto Connect Initialized\n");

    /* Main Loop - we're killed externally */
    for(;;)
    {
        /* Handle "need connect" */
        if( NeedConnect && AutoState == AC_IDLE )
        {
                hPPPOE = pppoeNew( IFIndexGetHandle(pac->Interface),
                            PPPFLG_CLIENT | PPPFLG_OPT_USE_MSE,
                            pac->Username, pac->Password );

            if( hPPPOE )
            {
                AutoState = AC_CONNECTING;
                AutoStatus = AC_STATUS_CONNECTING;
            }
            else
                AutoStatus = AC_STATUS_SYSTEMFAIL;
        }

        /* Get connection status (if not idle) */
        if( AutoState != AC_IDLE )
        {
            tmp = pppoeGetStatus( hPPPOE );
            if( tmp >= SI_CSTATUS_DISCONNECT )
            {
                pppoeFree( hPPPOE );
                AutoState  = AC_IDLE;
                AutoStatus = acerr[tmp-SI_CSTATUS_DISCONNECT];

                /* TODO: */
                /* On a disconnect we may want to enter a "redial" period. */
                /* This would be a simple wait, except the user may want to */
                /* force an early redial. */
                /* For now, we'll set NeedConnect back to "1". We will redial */
                /* no later than 10 seconds from now (timeout of the SemPend()). */
                NeedConnect = 1;
            }
        }

        /* Handle "connecting" state */
        if( AutoState == AC_CONNECTING )
        {
            /* If connected, print message and break */
            if( tmp == SI_CSTATUS_CONNECTED )
            {
                AutoState  = AC_CONNECTED;
                AutoStatus = AC_STATUS_CONNECTED;
                lastTx = lastRx = 0;
                lastTime = llTimerGetTime(0);
            }
        }

        /* Handle "connected" state */
        if( AutoState == AC_CONNECTED )
        {
            /* Reset the "need to connect" flag */
            NeedConnect = 0;

            /* See if we've been idle */
            if( lastTx != nats.TxAltered || lastRx != nats.RxAltered )
            {
                lastTx = nats.TxAltered;
                lastRx = nats.RxAltered;
                lastTime = llTimerGetTime(0);
            }
            /* If idle, see if we've been idle too long */
            else if( pac->Timeout &&
                    (llTimerGetTime(0) - lastTime) > pac->Timeout )
                NeedDisconnect = 1;
        }

        /* Handle "need disconnect" state */
        if( NeedDisconnect )
        {
            /* Reset the "need to disconnect" flag */
            NeedDisconnect = 0;

            /* Reset the "need to connect" flag */
            NeedConnect = 0;

            /* Disconnect any non-idle state */
            if( AutoState != AC_IDLE )
            {
                pppoeFree( hPPPOE );
                AutoState  = AC_IDLE;
            }

            /* Clear error status on forced disconnect */
            AutoStatus = AC_STATUS_IDLE;
        }


        /* Wait for next time */

        /* If connecting, don't wait long */
        if( AutoState == AC_CONNECTING )
            TaskSleep( 500 );
        else
            SemPend( hWakeSem, 10 * 1000 );
    }
}


/* RouteHook */
/* This functions hooks the stack's route control messages. */
/* it looks for Duplicate IP addresses for AddNetwork() */
/* ARGSUSED */
static void RouteHook( uint msg, UINT32 param1, UINT32 param2 )
{
    (void)param2;

    /* If we have a routing miss, tell autoconn we need to connect */
    /* and wake it up. */
    if( msg == MSG_RTC_MISS )
    {
        NeedConnect = 1;
        SemPost( hWakeSem );
    }
}


