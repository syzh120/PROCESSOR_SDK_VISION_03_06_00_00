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
 * ======== rtc.c ========
 *
 * Route "Helper" Routines (Route Control)
 *
 */

#include <stkmain.h>

char *pstrMsgName[] = { "Up","Down","Miss","New","Expired","Removed",
                        "Modified","Redirect" };

static void _RTCSendRtAdv();

#define RTC_HOOKMAX   5
static RTCHOOK pfnHook[ RTC_HOOKMAX ];

/*-------------------------------------------------------------------- */
/* RTCMsg() */
/* Sevices initialization, resource, and timer messages */
/*-------------------------------------------------------------------- */
void RTCMsg( uint Msg )
{
    static HANDLE hTimer = 0;
    static uint   RtcTicks = 0;

    switch( Msg )
    {
    /* System Initialization */
    case MSG_EXEC_SYSTEM_INIT:
        /* Clear out hooked functions */
        mmZeroInit( pfnHook, sizeof(pfnHook) );
        /* Create a timer using an approximation to stagger it from LLI */
        hTimer = TimerNew( &RTCMsg, TIMER_TICKS_RTC, MSG_RTC_TIMER );
        break;

    case MSG_EXEC_SYSTEM_SHUTDOWN:
        if( hTimer )
            TimerFree( hTimer );
        break;

    case MSG_RTC_TIMER:
        RtcTicks += TIMER_TICKS_RTC;
        if( RTC_RTADV_TIME && RtcTicks > RTC_RTADV_TIME )
            _RTCSendRtAdv();
        break;
    }
}

/*-------------------------------------------------------------------- */
/* RTCAddHook() */
/* Install hook function to receive route control messages */
/*-------------------------------------------------------------------- */
uint RTCAddHook( void (*pfn)( uint, UINT32, UINT32 ) )
{
    int i;
    for( i=0; i<RTC_HOOKMAX; i++ )
    {
        if( !pfnHook[i] )
        {
            pfnHook[i] = pfn;
            return(1);
        }
    }
    return( 0 );
}

/*-------------------------------------------------------------------- */
/* RTCRemoveHook() */
/* Install hook function to receive route control messages */
/*-------------------------------------------------------------------- */
void RTCRemoveHook( void (*pfn)( uint, UINT32, UINT32 ) )
{
    int i;
    for( i=0; i<RTC_HOOKMAX; i++ )
    {
        if( pfnHook[i] == pfn )
        {
            pfnHook[i] = 0;
            break;
        }
    }
}

/*-------------------------------------------------------------------- */
/* RTCReport() */
/* Route Control Status Report */
/*-------------------------------------------------------------------- */
void RTCReport( uint Msg, UINT32 dwParam1, UINT32 dwParam2 )
{
    char strTmp[80];
    int  i;

    /* Call the callback functions */
    for( i=0; i<RTC_HOOKMAX; i++ )
        if( pfnHook[i] )
            (*pfnHook[i])( Msg, dwParam1, dwParam2 );

    if( !RTC_ENABLE_DEBUG )
        return;
    else if( Msg == MSG_RTC_DUPIP )
    {
        UINT8 *bMAC = (UINT8 *)dwParam2;

        NDK_sprintf( strTmp,
                 "A=[%03d.%03d.%03d.%03d] Mac=[%02x:%02x:%02x:%02x:%02x:%02x]",
                  (UINT8)(dwParam1&0xFF), (UINT8)((dwParam1>>8)&0xFF),
                  (UINT8)((dwParam1>>16)&0xFF), (UINT8)((dwParam1>>24)&0xFF),
                  *(bMAC+0),*(bMAC+1),*(bMAC+2),*(bMAC+3),
                  *(bMAC+4),*(bMAC+5) );
        DbgPrintf(DBG_WARN,"KrnMsg: Msg=[DupIP   ] %s", strTmp);
    }
    else if( Msg >= MSG_RTC_UP && Msg <= MSG_RTC_REDIRECT )
    {
        NDK_sprintf( strTmp, "A=[%03d.%03d.%03d.%03d] M=[%03d.%03d.%03d.%03d]",
                   (UINT8)(dwParam1&0xFF), (UINT8)((dwParam1>>8)&0xFF),
                   (UINT8)((dwParam1>>16)&0xFF), (UINT8)((dwParam1>>24)&0xFF),
                   (UINT8)(dwParam2&0xFF), (UINT8)((dwParam2>>8)&0xFF),
                   (UINT8)((dwParam2>>16)&0xFF), (UINT8)((dwParam2>>24)&0xFF));
        Msg -= MSG_RTC_UP;
        DbgPrintf(DBG_INFO,"KrnMsg: Msg=[%-8s] %s", pstrMsgName[Msg], strTmp);
    }
}

/*-------------------------------------------------------------------- */
/* _RTCSendRtAdv() */
/* Internal routine to send Router Advertisements */
/*-------------------------------------------------------------------- */
static void _RTCSendRtAdv()
{
    HANDLE hBind,hIF;
    IPN    IPHost;

    /* Send a route advertisement for each router */
    hBind = BindGetFirst();
    while( hBind )
    {
        hIF = BindGetIF( hBind );
        BindGetIP( hBind, &IPHost, 0, 0 );
        ICMPSendRtAdv( hIF, RTC_RTADV_LIFE, IPHost, RTC_RTADV_PREF );
        hBind = BindGetNext( hBind );
    }
}

