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
 * ======== dhcpsm.c ========
 *
 * Simple DHCP Client Utility
 *
 */

#include "dhcp.h"

/* LOCAL FUNCTIONS */
static void   StateSelecting(DHCPLEASE *pLease);
static void   StateRequesting(DHCPLEASE *pLease);
static void   StateBound(DHCPLEASE *pLease);
static void   StateRenewRebind(DHCPLEASE *pLease);

static void   dhcpIPRemove( DHCPLEASE *pLease );
static int    dhcpIPAdd( DHCPLEASE *pLease );

static void StateSelecting(DHCPLEASE *pLease)
{
    IPN    IPOffer,IPServer;
    UINT16 MaxTries;
    UINT32 TimeStart;

    MaxTries = 3;
Retry:
#if DEBUGON
    DbgPrintf(DBG_INFO, "DHCP: StateSelecting:\r\n");
#endif

    /* Build the DHCP request packet and Send it */
    pLease->SendSize = dhcpBuildDiscover(pLease);
    dhcpPacketSend( pLease, INADDR_BROADCAST );

    /* Get the time */
    TimeStart = llTimerGetTime(0);

    while( (TimeStart + 2) >= llTimerGetTime(0) )
    {
        /* Get reply (waits for 3 seconds) */
        dhcpPacketReceive(pLease);

        if( dhcpVerifyMessage( pLease, &IPOffer, &IPServer ) == DHCPOFFER)
        {
            pLease->IPAddress = IPOffer;
            pLease->IPServer  = IPServer;
            pLease->StateNext = REQUESTING;
            return;
        }
    }

    /* Timeout - try again */
    if( --MaxTries )
        goto Retry;

    /* Failed to get proper response */
    pLease->StateNext = INIT;
    TaskSleep( 5*1000 );  /* wait 5 seconds before trying again */
    return;
}

static void StateRequesting(DHCPLEASE *pLease)
{
    UINT16 MessageType;
    UINT16 MaxTries;
    UINT32 TimeStart;
    int    rc;

    MaxTries = 3;
Retry:
#if DEBUGON
    DbgPrintf(DBG_INFO, "DHCP: StateRequesting:\r\n");
#endif

    /* Build and Send the Request */
    pLease->SendSize = dhcpBuildRequest(pLease);
    dhcpPacketSend( pLease, INADDR_BROADCAST );

    /* Get the time */
    TimeStart = llTimerGetTime(0);

    while( (TimeStart + 2) >= llTimerGetTime(0) )
    {
        dhcpPacketReceive(pLease);

        MessageType = dhcpVerifyMessage(pLease, 0, 0);

        switch (MessageType)
        {
        case DHCPACK:
            /* VerifyMessageType only returns valid message if */
            /* IPAddr and IPServer match. */

            /* Process the packet */
            dhcpPacketProcess(pLease);

            /* Add the IP address */
            rc = dhcpIPAdd( pLease );
            if( rc == 1 )
            {
                /* The address was added */
                pLease->LeaseStartTime = TimeStart;
                pLease->StateNext = BOUND;  /* Success */
                return;
            }
            if( rc == 0 )
            {
                /* The address was refused */
                pLease->SendSize = dhcpBuildDecline(pLease);
                dhcpPacketSend( pLease, INADDR_BROADCAST );
            }
            goto Problem;

        case DHCPNAK :
            goto Problem;

        default:
#if DEBUGON
            DbgPrintf( DBG_INFO, "DHCP: StateRequesting: Got bad message %d\r\n", MessageType );
#endif
            break;
        }
    }

    /* Timeout - try again */
    if( --MaxTries )
        goto Retry;

Problem:
    /* Failed to get proper response */
    pLease->StateNext = INIT;
    TaskSleep( 5*1000 );  /* wait 5 seconds before trying again */
    return;
}

static void StateRenewRebind( DHCPLEASE *pLease )
{
    UINT16 MessageType;
    UINT32 TimeAbort;
    UINT32 TimeStart;

#if DEBUGON
    DbgPrintf(DBG_INFO, "DHCP: StateRenewRebind:\r\n");
#endif

    if( pLease->State == RENEWING )
        TimeAbort = pLease->T2;
    else
        TimeAbort = pLease->T3;

Retry:
    pLease->SendSize = dhcpBuildRequest(pLease);
    dhcpPacketSend( pLease, pLease->IPServer );

    /* Get the time */
    TimeStart = llTimerGetTime(0);

    while( (TimeStart+5) >= llTimerGetTime(0) )
    {
        dhcpPacketReceive(pLease);

        MessageType = dhcpVerifyMessage( pLease, 0, 0 );
        switch (MessageType)
        {
        case DHCPACK :
            /* Call packet process to reprocess all tags */
            dhcpPacketProcess(pLease);

            /* Notify application that configuration has been altered */
            if( pLease->pCb )
                (*pLease->pCb)( pLease->hCb,
                                NETTOOLS_STAT_RUNNING+DHCPCODE_IPRENEW );

            pLease->LeaseStartTime = TimeStart;
            pLease->StateNext = BOUND;
            return;

        case DHCPNAK :
            /* If NAK, remove IP and restart with INIT */
            dhcpIPRemove( pLease );
            pLease->StateNext = INIT;
            return;

        default :
#if DEBUGON
            DbgPrintf( DBG_INFO, "DHCP: StateRenewRebind: Got bad message %d\r\n", MessageType );
#endif
            break;
        }
    }

    /*  Timeout - try again if not at TimeAbort */
    if( (TimeStart+10) < TimeAbort )
        goto Retry;

    /*  Have failed to get any response */
    /*  Set next state */
    if( pLease->State == RENEWING )
        pLease->StateNext = REBINDING;
    else
    {
        dhcpIPRemove( pLease );
        pLease->StateNext = INIT;
    }
    return;
}

static void StateBound( DHCPLEASE *pLease )
{
    UINT32 LeaseTime, RenewalT1Time, RenewalT2Time, TimeNow, TimeSleep;

#if DEBUGON
    DbgPrintf(DBG_INFO, "DHCP: StateBound:\r\n");
#endif

    /* Times are in network order, convert to host order */
    LeaseTime     = ntohl(pLease->LeaseTime);
    RenewalT1Time = ntohl(pLease->RenewalT1Time);
    RenewalT2Time = ntohl(pLease->RenewalT2Time);

    /* If server did not specify T1 and T2, use default */
    if( !RenewalT1Time )
        RenewalT1Time = LeaseTime - (LeaseTime >> 1);   /*  50% */
    if( !RenewalT2Time )
        RenewalT2Time = LeaseTime - (LeaseTime >> 3);   /*  87.5% */

    pLease->T1 = pLease->LeaseStartTime + RenewalT1Time;
    pLease->T2 = pLease->LeaseStartTime + RenewalT2Time;
    pLease->T3 = pLease->LeaseStartTime + LeaseTime;

    /* If any of the times overflowed, we "sleep" forever. This can */
    /* only happen when lease is in decades and we have a large */
    /* initial clock setting. */
    if( pLease->T1 < RenewalT1Time ||
            pLease->T2 < RenewalT2Time || pLease->T3 < LeaseTime )
        TaskBlock( TaskSelf() );

    /* Sleep for lease time (one day at a time) */
    TimeNow = llTimerGetTime(0);
    if( TimeNow < pLease->T1 )
    {
        TimeSleep = pLease->T1 - TimeNow;
        while( TimeSleep > 86400 )
        {
            TaskSleep( 86400 * 1000 );
            TimeSleep -= 86400;
        }
        TaskSleep( TimeSleep * 1000 );
    }

    /* Start renewal process */
    pLease->StateNext = RENEWING;
}

/*---------------------------------------------------------------- */
/* Add IP Network to System */
/* Returns: */
/*      1 - Address added */
/*      0 - Address refused */
/*     <0 - Error */
/*---------------------------------------------------------------- */
static int dhcpIPAdd( DHCPLEASE *pLease )
{
    CI_IPNET NA;
    CI_ROUTE RT;
    int      rc;

    /* Initialize Network Address */
    bzero( &NA, sizeof(NA) );
    NA.NetType = CFG_NETTYPE_DYNAMIC;
    NA.IPAddr  = pLease->IPAddress;
    NA.IPMask  = pLease->IPSubnetMask;
    if( strlen(pLease->DomainName) < CFG_DOMAIN_MAX )
        strcpy( NA.Domain, pLease->DomainName );

    /* Add the Entry */
    
    /* Note we need to keep a copy of the address we add in the event */
    /* that we need to remove it later. An alternate way of doing this */
    /* would be to search the configuration for the entry we want to */
    /* remove once its time, but this way is cleaner. */
   
    rc = CfgAddEntry( 0, CFGTAG_IPNET, pLease->IfIdx, CFG_ADDMODE_NOSAVE,
                      sizeof(CI_IPNET), (UINT8 *)&NA, &pLease->hCE_IPAddr );
    if( rc < 0 )
    {
        /* If this is a service error, the entry was still added */
        if( rc <= CFGERROR_SERVICE )
            CfgRemoveEntry( 0, pLease->hCE_IPAddr );
        pLease->hCE_IPAddr   = 0;
        pLease->IPAddressOld = 0;

        /* If this is a service error, then the IP address is already */
        /* in use. Else, its a fatal system error. */
        if( rc <= CFGERROR_SERVICE )
            return(0);
        return( -1 );
    }

    /* Save IP Address */
    pLease->IPAddressOld = pLease->IPAddress;

    
    /* Add gateway route if supplied */
   
    if( pLease->IPGate )
    {
        /* Add the default gateway. Since it is the default, the */
        /* destination address and mask are both zero (we go ahead */
        /* and show the assignment for clarity). */
        bzero( &RT, sizeof(RT) );
        RT.IPDestAddr = 0;
        RT.IPDestMask = 0;
        RT.IPGateAddr = pLease->IPGate;

        /* Add the route */
        rc = CfgAddEntry( 0, CFGTAG_ROUTE, 0, 0, sizeof(CI_ROUTE),
                          (UINT8 *)&RT, &pLease->hCE_IPGate );
        if( rc < 0 )
        {
            /* If this is a service error, the entry was still added */
            if( rc <= CFGERROR_SERVICE )
                CfgRemoveEntry( 0, pLease->hCE_IPGate );
            pLease->hCE_IPGate   = 0;
        }
    }


    /* Notify system of new state */

    if( pLease->pCb )
        (*pLease->pCb)( pLease->hCb, NETTOOLS_STAT_RUNNING+DHCPCODE_IPADD );

    return(1);
}

/*---------------------------------------------------------------- */
/* Remove IP Network from System */
/*---------------------------------------------------------------- */
static void dhcpIPRemove( DHCPLEASE *pLease )
{
    /* Remove IP Address */
    if( pLease->hCE_IPAddr )
        CfgRemoveEntry( 0, pLease->hCE_IPAddr );
    pLease->hCE_IPAddr = 0;

    /* Unload the gateway address if we've installed one */
    if( pLease->hCE_IPGate )
        CfgRemoveEntry( 0, pLease->hCE_IPGate );
    pLease->hCE_IPGate = 0;

    /* Manually clear the configuration */
    dhcpOptionsClear();

    /* Notify system of new state */
    if( pLease->pCb )
        (*pLease->pCb)( pLease->hCb, NETTOOLS_STAT_RUNNING+DHCPCODE_IPREMOVE );
}

/*
 * dhcpState()
 *
 * Main State Machine
 */
int dhcpState(DHCPLEASE *pLease)
{
    int    MaxDiscover = 0;
    int    i;

    fdOpenSession(TaskSelf());

    /* Setup Xid */
    pLease->Xid =  0;
    for(i=0; i<4; i++)
    {
       pLease->Xid <<= 8;
       pLease->Xid |= (UINT32)(pLease->MacAddress[i+2])&0xFF;
    }

    /* Notify system of new task state */
    if( pLease->pCb )
        (*pLease->pCb)( pLease->hCb, NETTOOLS_STAT_RUNNING );

restartLoop:
    /* If we're out of tries, exit */
    if( ++MaxDiscover > MAX_DISCOVER_TRIES )
        goto Exit;

    /* Set IPAddress to wildcard for now */
    /* *** EVENTUALLY WILL BE SET TO "DESIRED" VALUE *** */
    pLease->IPAddress = INADDR_ANY;

    /* Clear the lease information */
    pLease->LeaseTime     = 0;
    pLease->RenewalT1Time = 0;
    pLease->RenewalT2Time = 0;

    /* Start by selecting a server */
    pLease->StateNext = SELECTING;

    /* While there's a next state, process it */
    while( pLease->StateNext )
    {
        pLease->State     = pLease->StateNext;
        pLease->StateNext = 0;

        /* Open our socket environment */
        if( pLease->State != BOUND && dhcpSocketOpen( pLease ) != 0 )
            goto Exit;

        switch (pLease->State)
        {
        case INIT :
            dhcpSocketClose( pLease );
            goto restartLoop;

        case SELECTING :
            /* Set IPServer to broadcast */
            pLease->IPServer = INADDR_BROADCAST;
            StateSelecting(pLease);
            break;

        case REQUESTING :
            StateRequesting(pLease);
            break;

        case BOUND :
            /* Reset Max Discover */
            MaxDiscover = 0;
            StateBound(pLease);
            break;

        case RENEWING :
            StateRenewRebind(pLease);
            break;

        case REBINDING :
            /* Set IPServer to broadcast */
            pLease->IPServer = INADDR_BROADCAST;
            StateRenewRebind(pLease);
            break;

        default :
            break;
        }

        /* Close socket environment */
        if( pLease->State != BOUND )
            dhcpSocketClose( pLease );
    }

Exit:
#if DEBUGON
    DbgPrintf(DBG_INFO, "DHCP dhcpState: Leaving Task");
#endif

    /* Inform the system of the fault */
    /* Use the DHCP state as the return code */
    if( pLease->pCb )
        (*pLease->pCb)(pLease->hCb, NETTOOLS_STAT_FAULT+pLease->State);

    /* We are destroyed by the system task, so here we block */
    TaskBlock( TaskSelf() );

    return(0);
}

