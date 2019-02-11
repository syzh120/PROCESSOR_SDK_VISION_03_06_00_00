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
 * ======== nat.c ========
 *
 * Network Address Translation
 *
 */

#include <stkmain.h>
#ifndef _INCLUDE_NAT_CODE
void NatMsg( uint Msg ) { (void)Msg; }
#else
#include "nat.h"

/* Head of linked lists for TIME, IN, and LOCAL */
static NATENTRY *pneTIME;
static NATENTRY *pneMAPPED[32];
static NATENTRY *pneLOCAL[32];
static uint     EphemUsed;               /* Number of ephemeral ports used */

/* Next port to use in mapping */
static UINT16  PortNextMapped = SOCK_RESPORT_FIRST;

static void  NatTimeoutCheck();
static void  NatFlush();

/* Hash with 3 groups of 5 bits each (approximately) */
#define HASHPORT(a) ((((a)>>10)+((a)>>5)+(a))&0x1f)

/*-------------------------------------------------------------------- */
/* NatMsg() */
/* Sevices initialization, resource and timer messages */
/*-------------------------------------------------------------------- */
void NatMsg( uint Msg )
{
    static HANDLE hTimer;
    int           i;

    switch( Msg )
    {
    /* System Initialization */
    case MSG_EXEC_SYSTEM_INIT:
        /* The odd timer period helps stagger it from other timers */
        hTimer = TimerNew( &NatMsg, TIMER_TICKS_NAT, MSG_NAT_TIMER );
        mmZeroInit( &nats, sizeof(NATSTATS) );
        pneTIME = 0;
        for(i=0; i<32; i++)
        {
            pneMAPPED[i]  = 0;
            pneLOCAL[i] = 0;
        }
        EphemUsed = 0;
        break;

    /* System Shutdown */
    case MSG_EXEC_SYSTEM_SHUTDOWN:
        NatFlush();
        if( hTimer )
            TimerFree( hTimer );
        break;

    /* Low Resoruces */
    case MSG_EXEC_LOW_RESOURCES:
        NatFlush();
        break;

    /* Long Term Timer */
    case MSG_NAT_TIMER:
        NatTimeoutCheck();
        break;
    }
}

/*-------------------------------------------------------------------- */
/* NatFlush - Flush all NAT entries */
/*-------------------------------------------------------------------- */
static void NatFlush()
{
    /* Kill Everything */
    while( pneTIME )
    {
        NatFree( pneTIME );
    }
}

/*-------------------------------------------------------------------- */
/* NatTimeoutCheck - Check for Timed-out Entry */
/*-------------------------------------------------------------------- */
static void NatTimeoutCheck()
{
    NATENTRY *pne,*pneTmp;
    UINT32  TimeNow;

    TimeNow = llTimerGetTime(0);

    pne = pneTIME;
    while( pne )
    {
        /* Get next entry */
        pneTmp = pne->pNextTIME;

        /* Check for expired entry */
        if( pne->NI.Timeout <= TimeNow )
        {
            /* Free this entry */
            NatFree( pne );
        }

        /* Setup for next loop */
        pne = pneTmp;
    }
}

/*-------------------------------------------------------------------- */
/* NatNew - Create a NAT entry */
/* IPLocal      - IP of Local Machine */
/* PortLocal    - Port of Local Machine */
/* IPForeign    - IP of (Foreign) Peer */
/* PortForeign  - Port of (Foreign) Peer */
/* Protocol     - Protocol */
/* PortMapped   - Public Port (0=Reserved Ephemeral) */
/* Timeout      - Timeout is seconds (0=Static Entry) */
/*-------------------------------------------------------------------- */
HANDLE NatNew( IPN IPLocal, UINT16 PortLocal,
               IPN IPForeign, UINT16 PortForeign,
               UINT8 Protocol, UINT16 PortMapped,
               UINT32 Timeout )
{
    NATENTRY *pne;
    UINT16   Index;
    uint     Flags = 0;

    /* Check for illegal arguments */
    if( !PortLocal || !IPLocal )
        return(0);

    /* Check for artificial limit on NAT entries */
    if( nats.Entries >= NAT_MAXENTRIES )
        return(0);

    /* If this is going to be an Ephemeral mapping, make sure */
    /* we have a free port */
    if( !PortMapped || (PortMapped >= SOCK_RESPORT_FIRST &&
                        PortMapped <= SOCK_RESPORT_LAST) )
    {
        /* If too many ephem used, error out */
        if( EphemUsed > (SOCK_RESPORT_LAST-SOCK_RESPORT_FIRST) )
            return(0);
        EphemUsed++;
        Flags |= NI_FLG_RESERVED;
    }

    if( !(pne = mmAlloc(sizeof(NATENTRY))) )
    {
        DbgPrintf(DBG_WARN,"NatNew: OOM");
        NotifyLowResource();
        return(0);
    }

    /* Initialize type and flags */
    pne->Type     = HTYPE_NAT;
    pne->Flags    = Flags;

    if( PortMapped )
    {
        if( !IPForeign || !PortForeign )
            pne->Flags |= NI_FLG_WILD;
    }
    /* Else use ephemeral port - find one now */
    else
    {
        do
        {
            PortMapped = PortNextMapped;
            if( ++PortNextMapped > SOCK_RESPORT_LAST )
                PortNextMapped = SOCK_RESPORT_FIRST;
        } while( NatFindPNI( 0, 0, 0, 0, 0, PortMapped ) );
    }

    /* Set PNI information */
    pne->NI.TcpState    = NI_TCP_CLOSED;
    pne->NI.IPLocal     = IPLocal;
    pne->NI.PortLocal   = PortLocal;
    pne->NI.IPForeign   = IPForeign;
    pne->NI.PortForeign = PortForeign;
    pne->NI.Protocol    = Protocol;
    pne->NI.PortMapped  = PortMapped;
    pne->NI.Timeout     = llTimerGetTime(0) + Timeout;
    pne->NI.hProxyEntry = 0;

    /* Flag static entries */
    if( !Timeout )
        pne->Flags |= NI_FLG_STATIC;

    /* Init forward pointers */
    pne->pNextTIME   = 0;
    pne->pNextMAPPED = 0;
    pne->pNextLOCAL  = 0;

    /* If static, clear the timeout list */
    /* Else add it to the timeout list */
    if( pne->Flags & NI_FLG_STATIC )
        pne->ppPrevTIME = 0;
    else
    {
        /* If there's a "next" entry, point to it and point it */
        /* back to us */
        if( pneTIME )
        {
            pne->pNextTIME             = pneTIME;
            pne->pNextTIME->ppPrevTIME = &pne->pNextTIME;
        }

        /* Put us at head of the TIME list */
        pneTIME = pne;
        pne->ppPrevTIME = &pneTIME;
    }

    /* Hash for LOCAL */
    Index = HASHPORT(PortLocal);

    /* If there's a "next" entry, point to it and point it */
    /* back to us */
    if( pneLOCAL[Index] )
    {
        pne->pNextLOCAL            = pneLOCAL[Index];
        pne->pNextLOCAL->ppPrevLOCAL = &pne->pNextLOCAL;
    }

    /* Put us at head of the LOCAL list */
    pneLOCAL[Index]  = pne;
    pne->ppPrevLOCAL = &pneLOCAL[Index];

    /* Hash for MAPPED */
    Index = HASHPORT(PortMapped);

    /* If there's a "next" entry, point to it and point it */
    /* back to us */
    if( pneMAPPED[Index] )
    {
        pne->pNextMAPPED               = pneMAPPED[Index];
        pne->pNextMAPPED->ppPrevMAPPED = &pne->pNextMAPPED;
    }

    /* Put us at head of the MAPPED list */
    pneMAPPED[Index]  = pne;
    pne->ppPrevMAPPED = &pneMAPPED[Index];

    /* Keep stats */
    nats.Entries++;
    if( nats.Entries > nats.MaxEntries )
        nats.MaxEntries = nats.Entries;

    return( pne );
}

/*-------------------------------------------------------------------- */
/* NatFree - Free a NAT entry */
/*-------------------------------------------------------------------- */
void NatFree( HANDLE hNat )
{
    NATENTRY *pne = (NATENTRY *)hNat;

#ifdef _STRONG_CHECKING
    if( pne->Type != HTYPE_NAT )
    {
        DbgPrintf(DBG_ERROR,"NatFree: HTYPE %04x",pne->Type);
        return;
    }
#endif

    /* If entry contains a proxy, signal its destruction */
    if( pne->NI.hProxyEntry )
        ProxyEnable( &pne->NI, 0 );

    /* Remove Entry from all three linked lists */
    if( pne->ppPrevTIME )
    {
        *pne->ppPrevTIME = pne->pNextTIME;
        if( pne->pNextTIME )
            pne->pNextTIME->ppPrevTIME = pne->ppPrevTIME;
    }
    *pne->ppPrevMAPPED   = pne->pNextMAPPED;
    if( pne->pNextMAPPED )
        pne->pNextMAPPED->ppPrevMAPPED = pne->ppPrevMAPPED;
    *pne->ppPrevLOCAL  = pne->pNextLOCAL;
    if( pne->pNextLOCAL )
        pne->pNextLOCAL->ppPrevLOCAL = pne->ppPrevLOCAL;

    /* If used an ephemeral port, track it */
    if( pne->Flags & NI_FLG_RESERVED )
        EphemUsed--;

    /* If this entry had a proxy entry, free it */
    if( pne->NI.hProxyEntry )
        ProxyEntryFree( pne->NI.hProxyEntry );

    /* If in the long-term TCP state, update the stats */
    if( pne->NI.TcpState == NI_TCP_ESTAB )
        nats.LongTerm--;

    /* Update normal stats */
    nats.Entries--;

    /* Zap it */
    pne->Type = 0;
    mmFree( pne );
}

/* NatGetPNI - Return PNI from Nat Handle */
NATINFO *NatGetPNI( HANDLE hNat )
{
    NATENTRY *pne = (NATENTRY *)hNat;

#ifdef _STRONG_CHECKING
    if( pne->Type != HTYPE_NAT )
    {
        DbgPrintf(DBG_ERROR,"NatGetPNI: HTYPE %04x",pne->Type);
        return(0);
    }
#endif

    return( &pne->NI );
}

/* NatFindPNI - Find PNI */
/* In RX mode, IPLocal and PortLocal are NULL */
/* In TX mode, PortMapped is NULL */
/* *** Any non-Zero parameter must match *** */
NATINFO *NatFindPNI( IPN IPLocal, UINT16 PortLocal,
                     IPN IPForeign, UINT16 PortForeign,
                     UINT8 Protocol, UINT16 PortMapped )
{
    NATENTRY *pne,*pneWild = 0;
    int      UseProxy;
    UINT16   Index;
    HANDLE   hProxyEntry;

    /* All non-zero entries must match. */

    /* "PortForeign" can be NULL. This occurs when a */
    /* non-proxied entry is created before the foreign port */
    /* is known. Since it is non-proxied, it does not need */
    /* to be unique. */

    /* Load a linked list by HASHing PortMapped or PortLocal */
    if( PortMapped )
    {
        Index = HASHPORT(PortMapped);
        pne = pneMAPPED[Index];

        while( pne )
        {
            /* If PortMapped is non-Zero, match on PortMapped, */
            /* Protocol, IPForeign and PortForeign */
            if( (!PortMapped  || PortMapped == pne->NI.PortMapped) &&
                (!Protocol    || Protocol   == pne->NI.Protocol) &&
                (!IPForeign   || !pne->NI.IPForeign ||
                                 IPForeign  == pne->NI.IPForeign) &&
                (!PortForeign || !pne->NI.PortForeign ||
                                 PortForeign == pne->NI.PortForeign) )
            {
                /* If this is not a WILD, we match */
                if( !(pne->Flags & NI_FLG_WILD) )
                    return( &pne->NI );
                /* Else if we don't need an exact match we break */
                else if( !IPForeign || !PortForeign )
                    return( &pne->NI );

                /* For now, just remember we had a WC match */
                pneWild = pne;
            }
            pne = pne->pNextMAPPED;
        }

    }
    else if( PortLocal )
    {
        Index = HASHPORT(PortLocal);
        pne = pneLOCAL[Index];

        while( pne )
        {
            /* If PortLocal is non-Zero, match on PortLocal, */
            /* Protocol, IPForeign and PortForeign */
            if( (!IPLocal    || IPLocal    == pne->NI.IPLocal) &&
                (!PortLocal  || PortLocal  == pne->NI.PortLocal) &&
                (!Protocol   || Protocol   == pne->NI.Protocol) &&
                (!IPForeign   || !pne->NI.IPForeign ||
                                 IPForeign  == pne->NI.IPForeign) &&
                (!PortForeign || !pne->NI.PortForeign ||
                                 PortForeign == pne->NI.PortForeign) )
            {
                /* If this is not a WILD, we match */
                if( !(pne->Flags & NI_FLG_WILD) )
                    return( &pne->NI );
                /* Else if we don't need an exact match we break */
                else if( !IPForeign || !PortForeign )
                    return( &pne->NI );

                /* For now, just remember we had a WC match */
                pneWild = pne;
            }
            pne = pne->pNextLOCAL;
        }
    }
    else
        return(0);

    /* Handle a WildCard Match */
    if( pneWild )
    {
        /* Since this entry is WILD and both IPForeign and PortForeign */
        /* are valid, then we spawn a new NATENTRY to handle this */
        /* connection. This is done so that the TCP state detection */
        /* remains valid. The parent entry is allowed to expire. */

        /* NOTE: *DO NOT* Bump the timeout of the parent entry. */
        /* There is no reason to change the timeout of a parent entry. */
        /* If its not to "go away", it would be created as "static". */
        /* Otherwise; the programmer may be relying on a smaller timeout */
        /* than "NAT_IDLE_SECONDS". */
        /* pneWild->NI.Timeout = NAT_IDLE_SECONDS; */


        /* Create the new entry */
        pne = (NATENTRY *) NatNew( pneWild->NI.IPLocal,
                                   pneWild->NI.PortLocal,
                                   IPForeign, PortForeign,
                                   pneWild->NI.Protocol,
                                   pneWild->NI.PortMapped,
                                   NAT_IDLE_SECONDS );
        if( !pne )
            return(0);
        return( &pne->NI );
    }

    /* We haven't found an entry yet. Try the installed Proxy entries */

    /* If no protocol specified, we can't continue */
    if( !Protocol )
        return(0);

    /* We handle Rx and Tx a little different */
    if( PortMapped )
    {
        /* Attempt a proxy spawn on the destination port */
        /* On success the local IP destination is returned in IPLocal */
        UseProxy = ProxyEntrySpawn( NAT_MODE_RX, Protocol, PortMapped,
                                    &hProxyEntry, &IPLocal );

        /* On RX type proxies, the local port is the Mapped port. */
        /* Only IP address is altered. */
        if( UseProxy )
            PortLocal = PortMapped;
    }
    else
    {
        /* Attempt a proxy spawn on the destination port */
        UseProxy = ProxyEntrySpawn( NAT_MODE_TX, Protocol, PortForeign,
                                    &hProxyEntry, 0 );
    }

    /* If we got a proxy, create a NAT entry for it */
    if( UseProxy )
    {
        pne = (NATENTRY *)NatNew( IPLocal, PortLocal,
                                  IPForeign, PortForeign,
                                  Protocol, PortMapped, NAT_IDLE_SECONDS );

        /* Free Proxy entry if NAT entry not created */
        if( !pne )
        {
            ProxyEntryFree( hProxyEntry );
            return( 0 );
        }

        pne->NI.hProxyEntry = hProxyEntry;

        /* Signal creation of the entry */
        if( !ProxyEnable( &pne->NI, 1 ) )
        {
            /* The user rejected the entry */
            ProxyEntryFree( hProxyEntry );
            pne->NI.hProxyEntry = 0;
            NatFree( pne );
            return(0);
        }

        return( &pne->NI );
    }

    /* Here there was no Proxy. If PortMapped is NULL, this is an */
    /* outgoing packet. Thus we autocreate a PNI. This is for simple */
    /* non-proxied NAT. */
    if( !PortMapped )
    {
        pne = (NATENTRY *)NatNew( IPLocal, PortLocal,
                                  IPForeign, PortForeign,
                                  Protocol, 0, NAT_IDLE_SECONDS );
        if( pne )
            return( &pne->NI );
    }
    return(0);
}


#endif

