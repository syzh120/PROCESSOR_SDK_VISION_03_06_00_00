/*
 * Copyright (c) 2012-2015, Texas Instruments Incorporated
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
 * ======== sock6pcb.c ========
 *
 * Object member functions for the Sock6 device object. These
 * functions include protocol control type access to the SOCKET
 * object.
 *
 */

#include <stkmain.h>
#include "sock6.h"

#ifdef _INCLUDE_IPv6_CODE

/**********************************************************************
 *************************** Global Variables *************************
 **********************************************************************/

/* Socket Protocol list */
static SOCK6 *pSockList[] = { 0, 0, 0, 0, 0 };

/* Next User Port for Ephemeral Ports */
static uint wUserPort = SOCK_USERPORT_FIRST;

/**********************************************************************
 ************************ SOCK6 PCB Functions *************************
 **********************************************************************/

/**
 *  @b Description
 *  @n
 *      The function attaches the SOCKET to the appropriate list.
 *
 *  @param[in]  hSock
 *      The pointer to the socket which we will attach to the corresponding
 *      list.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   Non Zero
 */
int Sock6PcbAttach (HANDLE hSock)
{
    SOCK6* ps;

    /* Get the pointer to the socket. */
    ps = (SOCK6 *)hSock;

    /* Insert the Socket into the appropriate family list */
    ps->pProtPrev = 0;
    ps->pProtNext = pSockList[ps->SockProt];
    pSockList[ps->SockProt] = (HANDLE)ps;

    /* Patch entry which follows us (if any) */
    if (ps->pProtNext)
        ps->pProtNext->pProtPrev = ps;

    return(0);
}

/**
 *  @b Description
 *  @n
 *      The function detaches the SOCKET from the appropriate list.
 *
 *  @param[in]  hSock
 *      The pointer to the socket which we will detach from the
 *      corresponding list.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   Non Zero
 */
int Sock6PcbDetach( HANDLE hSock )
{
    SOCK6* ps;

    /* Get the pointer to the socket. */
    ps = (SOCK6 *)hSock;

    /* Patch preceeding entry */
    if( !ps->pProtPrev )
        pSockList[ps->SockProt] = (HANDLE)ps->pProtNext;
    else
        ps->pProtPrev->pProtNext = ps->pProtNext;

    /* Patch following entry */
    if( ps->pProtNext )
        ps->pProtNext->pProtPrev = ps->pProtPrev;

    /* Just to be tidy...*/
    ps->pProtPrev = 0;
    ps->pProtNext = 0;

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function finds a socket matching the criteria given.
 *
 *  @param[in]  ps
 *      The pointer to the socket from where the search is started.
 *  @param[in]  LIP
 *      The Local IPv6 Address
 *  @param[in]  LIP
 *      The Local Port
 *  @param[in]  FIP
 *      The Foreign IPv6 Address
 *  @param[in]  FPort
 *      The Foreign Port
 *  @param[out] pwc
 *      The resultant "best" value the search yielded. A value of 0 is the best
 *      possible match in which all the parameters were matched perfectly.
 *  @param[in]  FindAll
 *      Passing a value of 1 will ensure that the search will stop after the first
 *      possible match. This might not be the best possible result. Passing a value
 *      of 0 will ensure that the search yields the best possible match.
 *
 *  @retval
 *      Success -   Socket Matching the search criteria.
 *  @retval
 *      Error   -   No socket matching the criteria is found.
 */
static SOCK6 *Sock6PcbFind
(
    SOCK6*  ps,
    IP6N    LIP,
    uint    LPort,
    IP6N    FIP,
    uint    FPort,
    int*    pwc,
    int     FindAll
)
{
    SOCK6 *psBest = 0;
    int  wcBest = 9;
    int  wc;

    /* Find the "best" match for the supplied parameters. */
    for( ; ps; ps = ps->pProtNext )
    {
        /* Clear wild cards */
        wc = 0;

        /* Local port NULL means socket is not bound */
        if (!ps->LPort)
            continue;

        /* If local ports don't match, this entry can't match */
        if( ps->LPort != LPort )
            continue;

        /* Check if the local IP is a multicast packet. In that case we need to search
         * the multicast socket chain for a match */
        if(IPv6IsMulticast(LIP)) {
            MCAST_SOCK_REC6 * mcast_rec;

            /* Cycle through all the multicast records on the socket. */
            mcast_rec = (MCAST_SOCK_REC6 *)list_get_head((LIST_NODE**)&ps->pMcastList);
            while (mcast_rec != NULL) {
                /* Check if we get a hit? */
                if (IPv6CompareAddress(_IPv6_a2i(mcast_rec->mreq.ipv6mr_multiaddr), LIP)) {
                    return ps;
                }

                /* Get the next multicast record. */
                mcast_rec = (MCAST_SOCK_REC6 *)list_get_next((LIST_NODE*)mcast_rec);
            }

            /* Control comes here on no match. */
            continue;
        }

        /* Local IP must match, or be wildcard */
        if(!IPv6CompareAddress (ps->LIP, LIP))
        {
            if( (IPv6CompareAddress(LIP, IPV6_UNSPECIFIED_ADDRESS) == 1) ||
            	(IPv6CompareAddress(ps->LIP, IPV6_UNSPECIFIED_ADDRESS) == 1))
                wc++;
            else
                continue;
        }

        /* Foreign Port+IP must both match or both be wildcard */
        if( ps->FPort != FPort || !IPv6CompareAddress (ps->FIP, FIP) )
        {
            if( ((IPv6CompareAddress(FIP, IPV6_UNSPECIFIED_ADDRESS) == 1) && !FPort) ||
            	((IPv6CompareAddress(ps->FIP, IPV6_UNSPECIFIED_ADDRESS) == 1) && !ps->FPort) )
                wc++;
            else
                continue;
        }

        if( wc < wcBest )
        {
            wcBest = wc;
            psBest = ps;
            if( !wcBest )
                break;
        }

        if( FindAll )
            break;
    }

    if( pwc )
        *pwc = wcBest;
    return(psBest);
}

/**
 *  @b Description
 *  @n
 *      The function finds a RAW socket matching the criteria given.
 *
 *  @param[in]  ps
 *      The pointer to the socket from where the search is started.
 *  @param[in]  Prot
 *      The protocol field which describes the layer4 header.
 *  @param[in]  LIP
 *      The Local IPv6 Address
 *  @param[in]  FIP
 *      The Foreign IPv6 Address
 *  @param[in]  FPort
 *      The Foreign Port
 *  @param[out] pwc
 *      The resultant "best" value the search yielded. A value of 0 is the best
 *      possible match in which all the parameters were matched perfectly.
 *  @param[in]  FindAll
 *      Passing a value of 1 will ensure that the search will stop after the first
 *      possible match. This might not be the best possible result. Passing a value
 *      of 0 will ensure that the search yields the best possible match.
 *
 *  @retval
 *      Success -   Socket Matching the search criteria.
 *  @retval
 *      Error   -   No socket matching the criteria is found.
 */
static SOCK6* Sock6PcbFindRaw
(
    SOCK6*  ps,
    uint    Prot,
    IP6N    LIP,
    IP6N    FIP,
    int*    pwc,
    int     FindAll
)
{
    SOCK6*  psBest = 0;
    int     wcBest = 9;
    int     wc;

    /* Cycle through the socket chain. */
    for( ; ps; ps = ps->pProtNext )
    {
        /* Seed value which indicates for the best search. */
        wc = 0;

        /* Check if the protocol is WILDCARDED? If not then match it.
         * If there is no match; skip and goto the next entry. */
        if( ps->Protocol && ps->Protocol != Prot )
            continue;

        /* Match the Local IP; if specified. */
        if(IPv6CompareAddress (ps->LIP, LIP) == 0)
        {
            if((IPv6CompareAddress(LIP, IPV6_UNSPECIFIED_ADDRESS) == 1) ||
               (IPv6CompareAddress(ps->LIP, IPV6_UNSPECIFIED_ADDRESS) == 1))
                wc++;
            else
                continue;
        }

        /* Match the Foreign IP; if specified. */
        if(IPv6CompareAddress (ps->FIP, FIP) == 0)
        {
            if( (IPv6CompareAddress(FIP, IPV6_UNSPECIFIED_ADDRESS) == 1) ||
            	(IPv6CompareAddress(ps->FIP, IPV6_UNSPECIFIED_ADDRESS) == 1))
                wc++;
            else
                continue;
        }

        /* Store and remember only the best match. */
        if( wc < wcBest )
        {
            wcBest = wc;
            psBest = ps;
            if( !wcBest )
                break;
        }

        /* Do we need find more entries? */
        if (FindAll)
            break;
    }

    /* Return the best match. */
    if(pwc)
        *pwc = wcBest;
    return(psBest);
}

/**
 *  @b Description
 *  @n
 *      The function binds the socket to the specific Local IP and Port.
 *
 *  @param[in]  hSock
 *      Handle to the socket which is to be bound.
 *  @param[in]  LIP
 *      Local IPv6 Address to which the socket is to bound.
 *  @param[in]  LPort
 *      Local Port to which the socket is to be bound.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   Non Zero
 */
int Sock6PcbBind (HANDLE hSock, IP6N LIP, uint LPort)
{
    SOCK6* ps    = (SOCK6 *)hSock;
    SOCK6* psTmp;
    int    fEphem = 0;
    uint   SockOpts;

    /* Anything goes with Raw sockets */
    if( ps->SockProt == SOCKPROT_RAW )
    {
        SockOpts = 0;
        goto SockPcbBindOk;
    }

    /* On multicast addrs, REUSEADDR is the same as REUSEPORT */
    SockOpts = ps->OptionFlags & (SO_REUSEPORT|SO_REUSEADDR);
    if( SockOpts == SO_REUSEADDR )
    {
        if( IPv6IsMulticast( LIP ) )
            SockOpts = (SO_REUSEADDR|SO_REUSEPORT);
    }

    /* If LPort is NULL, and we are already bound to an LPort, */
    /* then we'll use the previously bound value. */
    if( !LPort && ps->LPort )
        LPort = ps->LPort;

    /* OPTION: We *may* want to restrict IP addresses to those actually */
    /* available on our system. */
    /* OPTION: We *may* want to restrict reserved ports to some "system" */
    /* class user. */

    /* Check for ephemeral port */
SockPcbBindEphem:
    if( !LPort )
    {
        if( ++wUserPort > SOCK_USERPORT_LAST )
              wUserPort = SOCK_USERPORT_FIRST;
        LPort = HNC16(wUserPort);
        fEphem = 1;
    }

    /* Find the best match */
    psTmp = Sock6PcbFind( pSockList[ps->SockProt], LIP, LPort, IPV6_UNSPECIFIED_ADDRESS, 0, 0, 0 );

    /* Check for conflict (and that we didn't match ourselves) */
    if( psTmp && psTmp != ps && LPort == psTmp->LPort )
    {
        if( !IPv6CompareAddress(LIP, IPV6_UNSPECIFIED_ADDRESS) &&
                !IPv6CompareAddress(psTmp->LIP, IPV6_UNSPECIFIED_ADDRESS) &&
        	!IPv6CompareAddress(psTmp->LIP, LIP) )
            goto SockPcbBindOk;

        /* We don't allow conflicts on ephemeral ports */
        if( fEphem )
        {
            LPort = 0;
            goto SockPcbBindEphem;
        }

        /* We have a port conflict. See if we keep going anyway */

        /* Address Conflict */

        /* Exception 1: Check for "REUSEPORT" on both sockets */
        if( psTmp->OptionFlags & SockOpts & SO_REUSEPORT )
            goto SockPcbBindOk;

        /* Exception 2: One or the other Local IP is "wildcard", but not both, */
        /*              and both have REUSEADDR set. */
        if( ((IPv6CompareAddress(LIP, IPV6_UNSPECIFIED_ADDRESS) == 1) &&
        	  !IPv6CompareAddress(psTmp->LIP, IPV6_UNSPECIFIED_ADDRESS)) ||
                  (!IPv6CompareAddress(LIP, IPV6_UNSPECIFIED_ADDRESS) &&
        	  (IPv6CompareAddress(psTmp->LIP, IPV6_UNSPECIFIED_ADDRESS) == 1)) &&
                      (psTmp->OptionFlags & SockOpts & SO_REUSEADDR) )
            goto SockPcbBindOk;

        return( EADDRINUSE );
    }

SockPcbBindOk:
    /* If we got here, the addr is OK */
    ps->LIP   = LIP;
    ps->LPort = LPort;
    ps->OptionFlags |= SockOpts;

    return(0);
}

/**
 *  @b Description
 *  @n
 *      The function sets the Foreign IP And Port in the SOCKET to
 *      the ones passed in this API. The function ensures there is
 *      no duplication present.
 *
 *  @param[in]  hSock
 *      Socket Handle to be configured with the IP and Port.
 *  @param[in]  FIP
 *      Foreign IP Address
 *  @param[in]  FPort
 *      Foreign Port
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   Non Zero
 */
int Sock6PcbConnect( HANDLE hSock, IP6N FIP, uint FPort )
{
    SOCK6   *ps    = (SOCK6 *)hSock;
    SOCK6   *psTmp;
    int    wc;

    /* These validations are required only for UDP and TCP. */
    if( ps->SockProt != SOCKPROT_RAW )
    {
        /* We should have a LOCAL Binding existing at this point in time. If one
         * is not present we can no longer guarantee uniqueness of the socket. */
        if (IPv6CompareAddress(ps->LIP, IPV6_UNSPECIFIED_ADDRESS) == 1)
            return EINVAL;

        /* Ensure that the Foreign IP and Port are also specified. */
        if( (IPv6CompareAddress(FIP, IPV6_UNSPECIFIED_ADDRESS) == 1) || !FPort )
            return EINVAL;

        /* Get the best socket match we can. */
        psTmp = Sock6PcbFind( pSockList[ps->SockProt], ps->LIP, ps->LPort, FIP, FPort, &wc, 0);

        /* Check for a duplicate? */
        if(psTmp && (psTmp != ps) && (wc == 0))
            return( EADDRINUSE );
    }

    /* Control comes here implies that we are unique. */
    ps->FIP   = FIP;
    ps->FPort = FPort;
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function finds a socket matching the criteria given. The
 *      function unlike the SockPcbResolve can be used to start searches
 *      from various points in the list.
 *
 *  @param[in]  hSock
 *      The socket handle from where the search will start. A value of 0
 *      here indicates that the search is started from the begining of the
 *      list.
 *  @param[in]  SockProt
 *      The Socket Protocol Family.
 *  @param[in]  Prot
 *      The Protocol family
 *  @param[in]  LIP
 *      The Local IPv6 Address
 *  @param[in]  LPort
 *      The Local Port
 *  @param[in]  FIP
 *      The Foreign IPv6 Address
 *  @param[in]  FPort
 *      The Foreign Port
 *
 *  @retval
 *      Handle to Socket Matching the search criteria.
 */
HANDLE Sock6PcbResolveChain (HANDLE hSock, uint SockProt, uint Prot,
                             IP6N LIP, uint LPort, IP6N FIP, uint FPort)
{
    SOCK6 *ps = (SOCK6 *)hSock;

    /* Determine the starting location for the search.
     * If none is specified; we start the search from the head of the list. */
    if (!ps)
        ps = pSockList[SockProt];
    else
        ps = ps->pProtNext;

    /* RAW Socket lookups are different then the traditional TCP/UDP. */
    if (SockProt != SOCKPROT_RAW)
        ps = Sock6PcbFind( ps, LIP, LPort, FIP, FPort, 0, 1 );
    else
        ps = Sock6PcbFindRaw( ps, Prot, LIP, FIP, 0, 1 );

    /* Return the matching socket handle. */
    return(ps);
}

/**
 *  @b Description
 *  @n
 *      The function finds a socket matching the criteria given.
 *
 *  @param[in]  SockProt
 *      The Socket Protocol Family.
 *  @param[in]  LIP
 *      The Local IPv6 Address
 *  @param[in]  LPort
 *      The Local Port
 *  @param[in]  FIP
 *      The Foreign IPv6 Address
 *  @param[in]  FPort
 *      The Foreign Port
 *  @param[in]  Match
 *      The type of resolution which is being sought.
 *       - SOCK_RESOLVE_EXACT: Exact Match all parameters should match
 *       - SOCK_RESOLVE_BEST : Best Possible Match.
 *       - SOCK_RESOLVE_SPAWN: Match and then spawn a new socket.
 *
 *  @retval
 *      Handle to Socket Matching the search criteria.
 */
HANDLE Sock6PcbResolve
(
    uint SockProt,
    IP6N LIP,
    uint LPort,
    IP6N FIP,
    uint FPort,
    uint Match,
    uint * MaxFlag
)
{
    SOCK6* ps;
    SOCK6* psSpawn;
    int    wc;

    /* Assume max connections are not exceeded */
    *MaxFlag = 0;

    /* Try and find the best possible match. */
    ps = Sock6PcbFind( pSockList[SockProt], LIP, LPort, FIP, FPort, &wc, 0 );

    /* If there is no match found or if the match criteria was EXACT and none was
     * found return an Error.*/
    if (!ps || (wc && Match == SOCK_RESOLVE_EXACT))
        return 0;

    /* If we dont need to spawn return the socket handle we found. */
    if( Match != SOCK_RESOLVE_SPAWN )
        return ps;

    /* At this time we are trying to SPAWN a new connection; if there is a perfect
     * match then this implies that the connection already exists. */
    if (wc == 0)
        return ps;

    /* We can spawn only if the matching socket is 'listening' for connections */
    if ((ps->OptionFlags & SO_ACCEPTCONN) == 0)
        return 0;

    /* Check if spawning the connection does not exceed the limits. */
    if( ps->ConnTotal >= ps->ConnMax ) {
        *MaxFlag = 1;
        return(0);
    }

    /* Time to create the new socket. */
    if (Sock6New(ps->Family, ps->SockType, ps->Protocol, ps->RxBufSize, ps->TxBufSize, (HANDLE *)&psSpawn))
        return(0);

    /* Inherit the socket options. */
    psSpawn->OptionFlags |= ps->OptionFlags & ~(SO_ACCEPTCONN);
    psSpawn->dwLingerTime = ps->dwLingerTime;
    psSpawn->RxTimeout    = ps->RxTimeout;
    psSpawn->TxTimeout    = ps->TxTimeout;

    /* Inherit the V6 Specific Information. */
    psSpawn->FlowLabel    = ps->FlowLabel;
    psSpawn->HopLimit     = ps->HopLimit;
    psSpawn->ScopeId      = ps->ScopeId;

    /* Since control comes here only for TCP sockets; we need to inherit some of the TCP Protocol
     * specific properties. */
    TCP6PrInherit (ps, ps->hTP, psSpawn, psSpawn->hTP);

    /* Initialize the parameters; next time onwards we want a perfect match for this connection. */
    psSpawn->LIP    = LIP;
    psSpawn->LPort  = LPort;
    psSpawn->FIP    = FIP;
    psSpawn->FPort  = FPort;

    /* Enqueue the spawned socket into the PENDING queue. Once the socket moves into the CONNECTED
     * stage; we will move this from the PENDING to the READY queue. The 'accept' call is waiting
     * on the READY queue to proceed. */
    psSpawn->pParent     = ps;
    psSpawn->pPrevQ      = ps;
    psSpawn->pPending    = ps->pPending;
    if( psSpawn->pPending )
        psSpawn->pPending->pPrevQ = psSpawn;
    ps->pPending         = psSpawn;
    psSpawn->StateFlags |= SS_PENDINGQ;

    /* Increment the number of connections which are pending. */
    ps->ConnTotal++;

    /* Return the handle to the spawned connection. */
    return(psSpawn);
}

/**
 *  @b Description
 *  @n
 *      The function is called from the ROUTE6 Module to indicate
 *      that there has been a change in the IPv6 ROUTING Table. The
 *      function invalidates all sockets which have cached this route
 *      This will ensure that subsequent packets being transmitted
 *      via these sockets relook the routing table for the correct match.
 *
 *  @param[in]  hRt6
 *      Handle to the V6 routing entry which has expired.
 *
 *  @retval
 *      Not Applicable
 */
void Sock6PcbRtChange(HANDLE hRt6)
{
    SOCK6*  ps;
    int     i;

    /* Cycle through all the socket families. */
    for( i=SOCKPROT_TCP; i<=SOCKPROT_RAW; i++ )
    {
        /* Get the head of the socket list. */
        ps = pSockList[i];

        /* Cycle through all sockets in the socket family. */
        while(ps)
        {
            /* Check if the cached route matches the route being deleted? */
            if (ps->hRoute6 == hRt6)
            {
                /* Invalidate the cached route. */
                ps->hRoute6 = 0;

                /* Clean it up i.e. drop the reference counter. */
                Rt6Free (hRt6);
            }

            /* Goto the next socket entry. */
            ps = ps->pProtNext;
        }
    }
    return;
}

/**
 *  @b Description
 *  @n
 *      The function aborts all closing sockets in the IPv6 socket family.
 *
 *  @retval
 *      Not Applicable.
 */
void Sock6PcbCleanup()
{
    SOCK6 *ps;
    int  GotOne;

    /* The only type of socket that can be "closing" is TCP
     * We'll search and we'll search until no Closing socket lives */
    do
    {
        GotOne = 0;

        /* Cycle through the TCP Family and make all sockets are closed. */
        ps = pSockList[SOCKPROT_TCP];
        while( ps )
        {
            if( ps->StateFlags & SS_CLOSING )
            {
                GotOne = 1;
                Sock6IntAbort( ps );
                break;
            }
            ps = ps->pProtNext;
        }
    } while( GotOne );
}

/**
 *  @b Description
 *  @n
 *      The function cycles through all the socket entries for the
 *      specified protocol family and closes any socket which matches the
 *      IP Address specified. The function was added to ensure that when
 *      an IP address is modified then any sockets which are using the OLD
 *      IP Address should be closed.
 *
 *      If a socket is waiting to accept incoming connections, an error is set
 *      with a wake up signal to allow a blocked accept() call to return. This
 *      allows an clean reboot/shutdown with no dangling sockets, as well as
 *      giving control back to an application Task so it can handle stack
 *      reboot or shutdown appropriately.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  SockProt
 *      Socket Family
 *  @param[in]  IPAddress
 *      OLD IP Address to which a socket might be bound to and which needs
 *      to be cleaned.
 *
 *  @retval
 *      Not Applicable
 */
void Sock6CleanPcb (uint SockProt, IP6N IPAddress)
{
    SOCK6    *ps;
    int error;

    /* Validate the socket protocol family. */
    if( SockProt<SOCKPROT_TCP || SockProt>SOCKPROT_RAW )
        return;

    /* Cycle through all the entries in the socket table. */
    ps = pSockList [SockProt];
    while (ps != NULL)
    {
        /* Clean the entry only if we have a match */
        if ((IPv6CompareAddress(ps->LIP, IPAddress) == 1))
        {
            /*
             *  Look for any sockets that are blocked on accept() call
             *  (fix for SDOCM00115513)
             */
            if (ps->OptionFlags & SO_ACCEPTCONN)
            {
                /* Set an error for this socket to force accept() to return */
                error = ECONNABORTED;
                Sock6Set((HANDLE)ps, SOL_SOCKET, SO_ERROR, &error,
                        sizeof(error));
                /*
                 *  Wake the socket blocked on accept(), allowing accept() to
                 *  handle the error and return
                 */
                FdSignalEvent(ps, FD_EVENT_READ);
            }

            Sock6Close (ps);
        }

        /* Get the next entry. */
        ps = ps->pProtNext;
    }
    return;
}

/*-------------------------------------------------------------------- */
/* SockGetPcb() */
/* Return socket PCB list */
/*-------------------------------------------------------------------- */
int Sock6GetPcb( uint SockProt, uint BufSize, UINT8 *pBuf )
{
    SOCK6    *ps;
    SOCK6PCB *ppcb;
    int     i;

    DbgPrintf(DBG_INFO, "Sock6GetPcb: UNTESTED CODE\n");

    if( SockProt<SOCKPROT_TCP || SockProt>SOCKPROT_RAW )
        return(0);

    ps = pSockList[ SockProt ];

    i=0;
    while( ps && BufSize >= sizeof( SOCK6PCB ))
    {
        ppcb = (SOCK6PCB *)pBuf;

        ppcb->IPAddrLocal   = ps->LIP;
        ppcb->PortLocal     = ps->LPort;
        ppcb->IPAddrForeign = ps->FIP;
        ppcb->PortForeign   = ps->FPort;
        if( ps->hTP )
        {
            ppcb->State = 1;
            ppcb->State = Sock6PrGetState( ps, ps->hTP );
        }
        else
            ppcb->State = 0;
        if( !ppcb->State && (ps->OptionFlags & SO_ACCEPTCONN) )
            ppcb->State = 1;

        i++;
        BufSize -= sizeof(SOCK6PCB);
        pBuf    += sizeof(SOCK6PCB);

        ps = ps->pProtNext;
    }

    return(i);
}

#endif /* _INCLUDE_IPv6_CODE */

