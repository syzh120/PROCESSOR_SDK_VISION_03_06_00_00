/*
 * Copyright (c) 2013-2015, Texas Instruments Incorporated
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
 * ======== sock.c ========
 *
 * Object member functions for the Sock device object.
 *
 * These functions get access to the SOCK object structure and can
 * adjust values, but usually call protocol functions for perform
 * action.
 *
 */

#include <stkmain.h>
#include "sock.h"
#include "socket.h"

/*-------------------------------------------------------------------- */
/* SockNew() */
/* Creates a socket */
/*-------------------------------------------------------------------- */
int SockNew( int Family, int Type, int Protocol,
             int RxBufSize, int TxBufSize, HANDLE *phSock )
{
    SOCK   *ps;
    int    error = 0;

    /* Check to see is request makes sense */
    /* AF_INET, SOCK_DGRAM: must use IPPROTO_UDP */
    /* AF_INET, SOCK_STREAM: must use IPPROTO_TCP */
    /* AF_INET, SOCK_RAW: protocol can be anything, including NULL */
    if( Family != AF_INET )
        return( EPFNOSUPPORT );

    if( Type == SOCK_DGRAM )
    {
        if( !Protocol )
            Protocol = IPPROTO_UDP;
        else if( Protocol != IPPROTO_UDP)
            return( EPROTOTYPE );
    }
    else if( Type == SOCK_STREAM || Type == SOCK_STREAMNC )
    {
        if( !Protocol )
            Protocol = IPPROTO_TCP;
        else if( Protocol != IPPROTO_TCP )
            return( EPROTOTYPE );
    }
    else if( Type != SOCK_RAW )
        return( ESOCKTNOSUPPORT );

    /* If we got here, we have a legal socket request */

    /* Attempt to allocate space for the socket */
    if( !(ps = mmAlloc(sizeof(SOCK))) )
    {
        NotifyLowResource();
        error = ENOMEM;
        goto socknew_done;
    }

    /* Initialize what we can */
    mmZeroInit( ps, sizeof(SOCK) );     /* Most Q's and counts init to Zero */
    ps->fd.Type      = HTYPE_SOCK;
    ps->fd.OpenCount = 1;
    ps->Family    = (uint)Family;       /* INET or FILE */
    ps->SockType  = (uint)Type;         /* STREAM, DGRAM or RAW */
    ps->Protocol  = (uint)Protocol;     /* IP protocol # or NULL */

    ps->IpTtl     = SOCK_TTL_DEFAULT;
    ps->IpTos     = SOCK_TOS_DEFAULT;

    /* Init default timeouts */
    ps->RxTimeout  = SOCK_TIMEIO * 1000;
    ps->TxTimeout  = SOCK_TIMEIO * 1000;

    /* Initialize the default socket priority. */
    ps->SockPriority = PRIORITY_UNDEFINED;

    /* Setup desired buffer sizes (if any) */
    if( RxBufSize )
        ps->RxBufSize = RxBufSize;
    if( TxBufSize )
        ps->TxBufSize = TxBufSize;

    /* Allocate Rx socket buffer */
    if( Type == SOCK_STREAM )
    {
        if( !ps->RxBufSize )
            ps->RxBufSize = SOCK_TCPRXBUF;
        ps->hSBRx = SBNew( ps->RxBufSize, SOCK_BUFMINRX, SB_MODE_LINEAR );
    }
    else if( Type == SOCK_STREAMNC )
    {
        ps->StateFlags = SS_ATOMICREAD;
        if( !ps->RxBufSize )
            ps->RxBufSize = SOCK_TCPRXLIMIT;
        ps->hSBRx = SBNew( ps->RxBufSize, SOCK_BUFMINRX, SB_MODE_HYBRID );
    }
    else
    {
        ps->StateFlags = SS_ATOMICREAD | SS_ATOMIC;
        if( !ps->RxBufSize )
            ps->RxBufSize = SOCK_UDPRXLIMIT;
        ps->hSBRx = SBNew( ps->RxBufSize, SOCK_BUFMINRX, SB_MODE_ATOMIC );
    }
    if( !ps->hSBRx )
    {
        error = ENOMEM;
        goto socknew_error;
    }

    /* Finalize Socket Status */
    if( Type == SOCK_STREAM || Type == SOCK_STREAMNC )
    {
        ps->StateFlags |= SS_CONNREQUIRED;

        if( !ps->TxBufSize )
            ps->TxBufSize = SOCK_TCPTXBUF;
        ps->hSBTx = SBNew( ps->TxBufSize, SOCK_BUFMINTX, SB_MODE_LINEAR );
        if( !ps->hSBTx )
        {
            error = ENOMEM;
            goto socknew_error;
        }

        /* Set the SockProt Type */
        ps->SockProt = SOCKPROT_TCP;
    }
    else
    {
        ps->StateFlags |= (SS_ADDR | SS_ATOMICWRITE);

        ps->hSBTx = 0;

        /* Set the SockProt Type */
        if( Type == SOCK_DGRAM )
            ps->SockProt = SOCKPROT_UDP;
        else
            ps->SockProt = SOCKPROT_RAW;
    }

    /* Attach the socket to protocol processing */
    if( (error = SockPrAttach( ps )) )
        goto socknew_error;

    *phSock = (HANDLE)ps;

socknew_done:
    /* Return */
    return( error );

socknew_error:
    /* Free the Rx and Tx Buffers */
    if( ps->hSBRx )
        SBFree( ps->hSBRx );
    if( ps->hSBTx )
        SBFree( ps->hSBTx );

    /* Free the sock memory */
    ps->fd.Type = 0;
    mmFree( ps );

    /* Return the error */
    return( error );
}

/*-------------------------------------------------------------------- */
/* SockClose() */
/* Close a socket */
/*-------------------------------------------------------------------- */
int SockClose( HANDLE h )
{
    SOCK*           ps = (SOCK *)h;
    int             error = 0;
    MCAST_SOCK_REC* ptr_mcast_rec;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockClose: HTYPE %04x\n",ps->fd.Type);
        return( ENOTSOCK );
    }
#endif

    /* If the socket is being closed; we need to ensure that all the multicast group
     * this socket has joined are left. */
    ptr_mcast_rec = (MCAST_SOCK_REC *)list_get_head ((LIST_NODE**)&ps->pMcastList);
    while (ptr_mcast_rec != NULL)
    {
        /* Leave the multicast group */
        IGMPLeave (h, &ptr_mcast_rec->mreq);

        /* Get the head; since the IGMPLeave will have deleted the entry from the list. */
        ptr_mcast_rec = (MCAST_SOCK_REC *)list_get_head ((LIST_NODE**)&ps->pMcastList);
    }

    /* Abort any incoming connections to a "listening" socket */
    if( ps->OptionFlags & SO_ACCEPTCONN )
    {
        SOCK *psTemp;

        while( ps->pPending )
        {
            /* Dequeue the socket */
            psTemp = ps->pPending;
            ps->pPending = psTemp->pPending;
            if( ps->pPending )
                ps->pPending->pPrevQ = ps;
            psTemp->StateFlags &= ~SS_PENDINGQ;

            /* Abort the socket */
            SockIntAbort( psTemp );
        }

        while( ps->pReady )
        {
            /* Dequeue the socket */
            psTemp = ps->pReady;
            ps->pReady = psTemp->pReady;
            if( ps->pReady )
                ps->pReady->pPrevQ = ps;
            psTemp->StateFlags &= ~SS_READYQ;

            /* Abort the socket */
            SockIntAbort( psTemp );
        }

        ps->ConnTotal = 0;
    }

    /* If not connection oriented, we're done */
    if( !(ps->StateFlags & SS_CONNREQUIRED) )
        goto close_drop;

    /* Disconnect any connections to the connection oriented socket */
    if( ps->StateFlags & SS_ISCONNECTED )
    {
        /* Flush the input queue (we're not going to be reading) */
        SockShutdown( ps, SHUT_RD );

        /* If linger is not set, we'll free the socket via our SockNotify */
        if( !(ps->OptionFlags & SO_LINGER) )
        {
            ps->StateFlags |= SS_CLOSING;

            /* Start Disconnect */
            return( SockPrDisconnect( ps ) );
        }

        /* Since linger is set, we'll drop the socket now (after linger time) */
        ps->StateFlags |= SS_LINGERING;
        error = SockPrDisconnect( ps );
        if( error )
            goto close_drop;

        /* Can't linger on non-blocking sockets */
        if( ps->StateFlags & SS_NBIO )
            goto close_drop;

        /* If no linget time, drop now */
        if( !ps->dwLingerTime )
            goto close_drop;

        /* Wait for the socket to disconnect */
        while( ps->StateFlags & SS_LINGERING )
        {
            /* If we ever timeout, break out of this loop */
            if( !FdWaitEvent( ps, FD_EVENT_READ, ps->dwLingerTime ) )
                break;
        }
    }

close_drop:
    SockIntAbort( ps );

    return( error );
}

/*-------------------------------------------------------------------- */
/* SockIntAbort() */
/* Close a socket - Called only internally to stack */
/*-------------------------------------------------------------------- */
void SockIntAbort( SOCK *ps )
{
    /* Detach the socket from protocol processing */
    SockPrDetach( ps );

    /* DeRef any held route */
    if( ps->hRoute )
        RtDeRef( ps->hRoute );

    /* Free the Rx and Tx Buffers */
    if( ps->hSBRx )
        SBFree( ps->hSBRx );
    if( ps->hSBTx )
        SBFree( ps->hSBTx );

    /* Free the sock memory */
    ps->fd.Type = 0;
    mmFree( ps );
}

/*-------------------------------------------------------------------- */
/* SockCheck() */
/* Check for socket read/write/except status */
/*-------------------------------------------------------------------- */
int SockCheck( HANDLE h, int IoType )
{
    SOCK *ps = (SOCK *)h;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockCheck: HTYPE %04x\n",ps->fd.Type);
        return( 0 );
    }
#endif

    switch( IoType )
    {
    case SOCK_READ:
        /* Return TRUE if readable */

        /* Simply return TRUE for the following error cases */
        /* - Error pending sockets */
        /* - When shutdown for recv */
        if( ps->ErrorPending || (ps->StateFlags & SS_CANTRCVMORE) )
            return(1);

        /* Also return true if socket can be "read" */
        if( ps->OptionFlags & SO_ACCEPTCONN )
        {
            if( ps->pReady )
                return(1);
        }
        else
        {
            if( SBGetTotal(ps->hSBRx) >= SBGetMin(ps->hSBRx) )
                return(1);
        }
        break;

    case SOCK_WRITE:
        /* Return TRUE if writeable */

        /* Simply return TRUE for the following error cases */
        /* - Listening sockets (can not be written) */
        /* - Error pending sockets */
        /* - When shutdown for write */
        if( (ps->OptionFlags & SO_ACCEPTCONN) || ps->ErrorPending ||
                (ps->StateFlags & SS_CANTSENDMORE) )
            return(1);

        /* Also return true if connected and can write */
        if( !(ps->StateFlags & SS_CONNREQUIRED) ||
             (ps->StateFlags & SS_ISCONNECTED)  )
        {
            /* Writable "connected" cases */
            if( (ps->StateFlags & SS_ATOMICWRITE) ||
                    (SBGetSpace(ps->hSBTx) >= SBGetMin(ps->hSBTx)) )
                return(1);
        }
        break;

    case SOCK_EXCEPT:
        /* Return TRUE if OOB data present, shutdown, or pending error */
        if( ps->StateFlags & SS_OOBACTIVE ||
                    ps->StateFlags & SS_CANTRCVMORE || ps->ErrorPending )
            return(1);
        break;
    }
    return(0);
}

/*-------------------------------------------------------------------- */
/* SockStatus() */
/* Return socket read/write status */
/*-------------------------------------------------------------------- */
int SockStatus( HANDLE h, int request, int *results )
{
    SOCK *ps = (SOCK *)h;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockStatus: HTYPE %04x\n",ps->fd.Type);
        return( EINVAL );
    }
#endif

    if( request==FDSTATUS_RECV && results )
    {
        /* Return socket receive status */
        /* returns -1 if socket can not be read or has error pending */
        /* Listening sockets = 1 if at least 1 connection available */
        /* TCP/UDP sockets = bytes available */
        if( ps->ErrorPending || (ps->StateFlags & SS_CANTRCVMORE) )
            *results = -1;
        else if( ps->OptionFlags & SO_ACCEPTCONN )
        {
            if( ps->pReady )
                *results = 1;
            else
                *results = 0;
        }
        else if( (ps->StateFlags&SS_CONNREQUIRED) &&
                 !(ps->StateFlags&SS_ISCONNECTED) )
            *results = -1;
        else
        {
            if( ps->hSBRx )
                *results = (int)SBGetTotal( ps->hSBRx );
            else
                *results = 0;
        }
    }
    else if( request==FDSTATUS_SEND && results )
    {
        /* Return socket send status */
        /* returns -1 if socket can not be written or has error pending */
        /* Listening sockets = -1 */
        /* TCP sockets = max byte send w/o blocking */
        /* Other sockets = max byte send w/o message size error */
        if( ps->ErrorPending ||
                (ps->StateFlags & SS_CANTSENDMORE) ||
                (ps->OptionFlags & SO_ACCEPTCONN) ||
                ((ps->StateFlags&SS_CONNREQUIRED) &&
                    !(ps->StateFlags&SS_ISCONNECTED)) )
            *results = -1;
        else if( ps->StateFlags & SS_ATOMICWRITE )
        {
            /* Here we are UDP or RAW */
            int tmp;

            /* Get MTU */
            if( ps->hRoute )
                tmp = RtGetMTU( ps->hRoute );
            else
                tmp = 1500;

            /* Sub off any auto-generated IP header */
            tmp -= SockGetIpHdrSize( ps );

            /* Sub off any UDP header */
            if( ps->SockType == SOCK_DGRAM )
                tmp -= UDPHDR_SIZE;

            *results = tmp;
        }
        else if( ps->hSBTx )
            *results = SBGetSpace(ps->hSBTx);
        else
            *results = 0;
    }
    else
        return( EINVAL );

    return(0);
}


/*-------------------------------------------------------------------- */
/* SockShutdown() */
/* Shutdown Socket Connection */
/*-------------------------------------------------------------------- */
int SockShutdown( HANDLE h, int how )
{
    SOCK   *ps = (SOCK *)h;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockShutdown: HTYPE %04x\n",ps->fd.Type);
        return( ENOTSOCK );
    }
#endif

    /* Shutdown Read */
    if( how == SHUT_RD || how == SHUT_RDWR )
    {
        ps->StateFlags |= SS_CANTRCVMORE;

        /* Listening sockets don't need to be flushed */
        if( !(ps->OptionFlags & SO_ACCEPTCONN) )
        {
            /* Perform read flush */
            if( ps->hSBRx )
                SBFlush( ps->hSBRx, 1 );

            /* Notify the protocol of status change */
            SockPrRecv( ps );
        }

        /* Notify the socket of status change */
        FdSignalEvent( ps, FD_EVENT_READ|FD_EVENT_EXCEPT );
    }

    /* Shutdown Write */
    if( how == SHUT_WR || how == SHUT_RDWR )
    {
        /* Listening sockets can not be "written" as it is */
        if( ps->OptionFlags & SO_ACCEPTCONN )
            return(0);

        ps->StateFlags |= SS_CANTSENDMORE;

        /* If the socket is connection oriented, we should tell the */
        /* peer that we're done sending data. */
        if( ps->StateFlags & SS_CONNREQUIRED )
            SockPrDisconnect( ps );

        /* Notify the socket of status change */
        FdSignalEvent( ps, FD_EVENT_WRITE );
    }
    return(0);
}

/*-------------------------------------------------------------------- */
/* SockConnect() */
/* Create Socket Connection */
/*-------------------------------------------------------------------- */
int SockConnect( HANDLE h, PSA pName )
{
    SOCK   *ps = (SOCK *)h;
    PSA_IN  psa_in = (PSA_IN)pName;
    int    error = 0;
    HANDLE hRt;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockConnect: HTYPE %04x\n",ps->fd.Type);
        return( ENOTSOCK );
    }
#endif

    /* If socket is "accepting", then it can't "connect" */
    if( ps->OptionFlags & SO_ACCEPTCONN )
    {
        error = EOPNOTSUPP;
        goto SockConnectDone;
    }

    /* We can have only one active connection */
    /* If connection oriented, we can have only one active connection */
    if( ps->StateFlags & (SS_ISCONNECTED | SS_ISCONNECTING) )
    {
        /* If connection oriented, we have an error condition */
        if( ps->StateFlags & SS_CONNREQUIRED )
        {
            if( !(ps->StateFlags & SS_ISCONNECTED) )
                error = EALREADY;
            else
                error = EISCONN;
            goto SockConnectDone;
        }
        /* Otherwise, we'll disconnect first */
        if( (error = SockDisconnect( h )) )
            goto SockConnectDone;
    }

    /* Check for a pending error (from a previous connect session) */
    if( ps->ErrorPending )
    {
        error = ps->ErrorPending;
        ps->ErrorPending = 0;
        goto SockConnectDone;
    }

    /* First create the socket side binding */

    /* If we aren't bound to an IP, we'll just pick one. We try and pick */
    /* the IP address of the egress device that matches the Ip network of */
    /* the destination address. */

    /* Note: If LIP is valid, then the port must also be valid */
    if( !ps->LIP )
    {
        UINT32 IPHost=0;
        UINT32 IPDst;

        IPDst = psa_in->sin_addr.s_addr;

        /* This function will potentially have to examine routes, but */
        /* we'll try the easy cases first. We use the route table under */
        /* the following conditions: */
        /*     IPDst is not all 0's or all 1's */
        /*     IPDst is not IP Multicast */
        /*     IPDst does not map to a locally bound subnet */
        if( IPDst!=INADDR_ANY && IPDst!=INADDR_BROADCAST &&
                !(IN_MULTICAST(IPDst)) && !(IPHost=BindIFNet2IPHost(0,IPDst)) )
        {
            /* We have to use the route table */
            hRt = IPGetRoute( 0, IPDst );
            if( hRt )
            {
                /* We can look up the IP of the outgoing IF directly. */
                IPHost=BindIFNet2IPHost( RtGetIF(hRt), RtGetIPAddr(hRt) );
                RtDeRef( hRt );
            }
        }

        /* If still no good host IP and the socket has an egress device, */
        /* then we'll use the IP address of that device else we'll use */
        /* any address we can */
        if( !IPHost )
        {
            if( ps->hIFTx )
                IPHost = BindIF2IPHost( ps->hIFTx );
            else if( !(IPHost = BindIF2IPHost( 0 )) )
            {
                /* Here we have no IP addresses, plus the user did not */
                /* specify an egress device. So we don't send out packets */
                /* with 0.0.0.0 haphazardly, we'll error out instead */
                error = ENXIO;
                goto SockConnectDone;
            }
        }

        if( (error = SockPcbBind( h, IPHost, 0 )) )
            goto SockConnectDone;
    }

    /* Establish the PCB socket connection */
    if( (error = SockPcbConnect( h, psa_in->sin_addr.s_addr, psa_in->sin_port )) )
        goto SockConnectDone;

    /* Make sure these are clear */
    ps->StateFlags &= ~(SS_CANTRCVMORE | SS_CANTSENDMORE);

    /* Validate a route for this connection */
    hRt = SockValidateRoute( ps );

    /* Non-Connection oriented socket just "connects" */
    if( !(ps->StateFlags & SS_CONNREQUIRED) )
    {
        /* Easy case - just set to ISCONNECTED */
        ps->StateFlags |= SS_ISCONNECTED;
        goto SockConnectDone;
    }

    /* A connection oriented socket will not connect if we didn't find */
    /* a route. */
    if( !hRt )
        return( EHOSTUNREACH );

    /* Set ISCONNECTING flag (ISCONNECTED set via SockNotify) */
    ps->StateFlags |= SS_ISCONNECTING;

    /* Establish the protocol connection */
    error = SockPrConnect( ps );

    /* If no error and not connected and not non-blocking, we wait */
    while( !error && !ps->ErrorPending &&
           !(ps->StateFlags & (SS_NBIO|SS_ISCONNECTED)) )
    {
        /* If we ever time out, we have an error */
        if( !FdWaitEvent( ps, FD_EVENT_WRITE, SOCK_TIMECONNECT*1000 ) )
            error = ETIMEDOUT;
    }

    /* Check for a pending error (again) */
    if( ps->ErrorPending )
    {
        error = ps->ErrorPending;
        ps->ErrorPending = 0;
    }

    /* Any error up to now is fatal */
    if( error )
    {
        ps->StateFlags &= ~SS_ISCONNECTING;
        SockPrDisconnect( ps );
    }
    /* Else check to see if we should return EINPROGRESS for NBIO */
    else if( !(ps->StateFlags & SS_ISCONNECTED) )
        error = EINPROGRESS;

SockConnectDone:
    return( error );
}

/*-------------------------------------------------------------------- */
/* SockDisconnect() */
/* Disconnect a Socket */
/*-------------------------------------------------------------------- */
int SockDisconnect( HANDLE h )
{
    SOCK *ps = (SOCK *)h;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockDisconnect: HTYPE %04x\n",ps->fd.Type);
        return( ENOTSOCK );
    }
#endif

    /* If connection required, this call is invalid */
    if( ps->StateFlags & SS_CONNREQUIRED )
        return( EINVAL );

    /* Make sure we are connected */
    if( !(ps->StateFlags & (SS_ISCONNECTED | SS_ISCONNECTING)) )
        return( ENOTCONN );

    /* Disconnect (back to idle) */
    ps->StateFlags &= ~(SS_ISCONNECTING|SS_ISCONNECTED|SS_CLOSING);

    /* Revert to strict bindings */
    ps->LIP   = ps->BIP;
    ps->LPort = ps->BPort;
    ps->FIP   = 0;
    ps->FPort = 0;

    /* Toss any cached route */
    if( ps->hRoute )
    {
        RtDeRef( ps->hRoute );
        ps->hRoute = 0;
    }

    return( 0 );
}

/*-------------------------------------------------------------------- */
/* SockBind() */
/* Bind Address and Port to Socket */
/*-------------------------------------------------------------------- */
int SockBind( HANDLE h, PSA pName )
{
    SOCK *ps = (SOCK *)h;
    PSA_IN psa_in = (PSA_IN)pName;
    int  error = 0;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockBind: HTYPE %04x\n",ps->fd.Type);
        return( ENOTSOCK );
    }
#endif

    /* The only obvious error is that we're already bound */
    /* Note: Even AF_TASK type sockets will have an "IP" (Socket Id) */
    if( ps->LPort || !psa_in )
        return( EINVAL );

    error = SockPcbBind( ps, psa_in->sin_addr.s_addr, psa_in->sin_port );

    if( !error )
    {
        ps->BIP   = ps->LIP;
        ps->BPort = ps->LPort;
    }

    return( error );
}

/*-------------------------------------------------------------------- */
/* SockGetName */
/* Get Local and/or Peer Address and Port of Socket */
/*-------------------------------------------------------------------- */
int SockGetName( HANDLE h, PSA pSockName, PSA pPeerName)
{
    SOCK *ps = (SOCK *)h;
    PSA_IN psa_Localin = (PSA_IN)pSockName;
    PSA_IN psa_Peerin = (PSA_IN)pPeerName;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockGetName: HTYPE %04x\n",ps->fd.Type);
        return( ENOTSOCK );
    }
#endif

    if( psa_Localin )
    {
        psa_Localin->sin_family      = (UINT8)ps->Family;
        psa_Localin->sin_port        = ps->LPort;
        psa_Localin->sin_addr.s_addr = ps->LIP;
    }

    if( psa_Peerin )
    {
        psa_Peerin->sin_family      = (UINT8)ps->Family;
        psa_Peerin->sin_port        = ps->FPort;
        psa_Peerin->sin_addr.s_addr = ps->FIP;
    }

    return( 0 );
}

/*-------------------------------------------------------------------- */
/* SockListen() */
/* Listen for socket connections */
/*-------------------------------------------------------------------- */
int SockListen( HANDLE h, int maxcon )
{
    SOCK *ps = (SOCK *)h;
    int  error = 0;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockListen: HTYPE %04x\n",ps->fd.Type);
        return( ENOTSOCK );
    }
#endif

    /* To listen, we must be connection oriented */
    if( !(ps->StateFlags & SS_CONNREQUIRED) )
        return( EOPNOTSUPP );

    /* We also can't already be connected */
    if( ps->StateFlags & (SS_ISCONNECTED | SS_ISCONNECTING) )
        return( EISCONN );

    /* Call the protocol to start the listening process */
    if( !(error = SockPrListen(ps)) )
    {
        /* Success - Setup our state change */

        /* Set the listen bit */
        ps->OptionFlags |= SO_ACCEPTCONN;

        /* Once listening, there's no way to stop. Hence, we */
        /* can free the socket buffers */
        if( ps->hSBRx )
            SBFree( ps->hSBRx );
        if( ps->hSBTx )
            SBFree( ps->hSBTx );
        ps->hSBRx = ps->hSBTx = 0;

        /* Bound maxcon and set */
        if( maxcon < 0 )
            maxcon = 0;
        if( maxcon > SOCK_MAXCONNECT )
            maxcon = SOCK_MAXCONNECT;
        ps->ConnMax = maxcon;
    }

    return( error );
}

/*-------------------------------------------------------------------- */
/* SockAccept() */
/* Accept a socket connection from a listening socket */
/*-------------------------------------------------------------------- */
int SockAccept( HANDLE h, HANDLE *phSock )
{
    SOCK   *ps = (SOCK *)h;
    SOCK   *psRet;
    int    error = 0;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockAccept: HTYPE %04x\n",ps->fd.Type);
        return( ENOTSOCK );
    }
#endif

    /* If not accepting, then we can't listen */
    if( !(ps->OptionFlags & SO_ACCEPTCONN) )
        return( EINVAL );

    for(;;)
    {
        /* Return Error if Error */
        if( ps->ErrorPending )
        {
            error = ps->ErrorPending;
            ps->ErrorPending = 0;
            return( error );
        }

        /* If shutdown for READ, return error */
        if( ps->StateFlags & SS_CANTRCVMORE )
            return( ECONNABORTED );

        /* If connection ready, return connection */
        if( ps->pReady )
        {
            /* Unchain the next socket */
            psRet = ps->pReady;
            ps->pReady = psRet->pReady;
            if( ps->pReady )
                ps->pReady->pPrevQ = ps;
            psRet->pReady  = 0;
            psRet->pParent = 0;
            psRet->StateFlags &= ~SS_READYQ;
            ps->ConnTotal--;

            *phSock = (HANDLE)psRet;

            return(0);
        }

        /* If non-blocking, return EWOULDBLOCK */
        if( ps->StateFlags & SS_NBIO )
            return( EWOULDBLOCK );

        /* Wait forever (until wake) */
        if( !FdWaitEvent( ps, FD_EVENT_READ, 0 ) )
            return( EWOULDBLOCK );
    }
}

/*-------------------------------------------------------------------- */
/* SockSet() */
/* Set Socket Parameter Value */
/*-------------------------------------------------------------------- */
int SockSet(HANDLE hSock, int Type, int Prop, void *pbuf, int size)
{
    SOCK *ps = (SOCK *)hSock;
    int  value,error = 0;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockSet: HTYPE %04x\n",ps->fd.Type);
        return( ENOTSOCK );
    }
#endif

    /* Check size and pointer, just to be safe */
    if( size && !pbuf )
        return( EINVAL );

    /* We also handle IPPROTO_IP and IPROTO_TCP */
    if( Type != SOL_SOCKET )
    {
        if( Type == IPPROTO_TCP )
        {
            if( ps->SockProt == SOCKPROT_TCP )
                return( TcpPrSetOption( hSock, ps->hTP, Prop, pbuf, size ) );
            else
                return( EINVAL );
        }
        if( Type == IPPROTO_IP )
        {
            if((Prop != IP_OPTIONS) && (Prop != IP_ADD_MEMBERSHIP) && (Prop != IP_DROP_MEMBERSHIP))
            {
                if( size != sizeof(int) )
                    return( EINVAL );
                value = *(int *)pbuf;
            }

            /* Set Property */
            switch( Prop )
            {
                case IP_TOS:
                    ps->IpTos = (uint)value;
                    break;

                case IP_TTL:
                    ps->IpTtl = (uint)value;
                    break;

                case IP_HDRINCL:
                    /* Only RAW sockets support this option */
                    if( ps->SockProt != SOCKPROT_RAW )
                        return( EINVAL );
                    if( value )
                        ps->IpFlags |= SOCK_IP_HDRINCL;
                    else
                        ps->IpFlags &= ~SOCK_IP_HDRINCL;
                    break;

                case IP_OPTIONS:
                    /* Connection oriented sockets do not support options */
                    if( (ps->StateFlags & SS_CONNREQUIRED) || size > 40 )
                        return( EINVAL );
                    ps->IpOptSize = (size + 3) & ~3;
                    if( ps->IpOptSize )
                        mmCopy( ps->IpOptions, pbuf, ps->IpOptSize );
                    break;

                case IP_ADD_MEMBERSHIP:
                case IP_DROP_MEMBERSHIP:
                {
                    struct ip_mreq* ptr_ipmreq;

                    /* Validate the arguments. */
                    if (size != sizeof(struct ip_mreq))
                        return (EINVAL);                    

                    /* Get the pointer to the IP Multicast request. */
                    ptr_ipmreq = (struct ip_mreq *)pbuf;

                    /* Validate the arguments. */
                    if (!IN_MULTICAST((IPN)ptr_ipmreq->imr_multiaddr.s_addr))
                        return (EINVAL);

                    /* Call the appropriate handler. */
                    if (Prop == IP_ADD_MEMBERSHIP)
                        return IGMPJoin(hSock, ptr_ipmreq);
                    return IGMPLeave(hSock, ptr_ipmreq);
                }
            }
        }
        return( 0 );
    }

    /* Socket Properties */

    /* Handle the structure based first */

    switch( Prop )
    {
    case SO_LINGER:
        {
            struct linger *pl = (struct linger *)pbuf;

            if( size != sizeof(struct linger) )
                return( EINVAL );
            if( pl->l_onoff )
                ps->OptionFlags |= SO_LINGER;
            else
                ps->OptionFlags &= ~SO_LINGER;
            ps->dwLingerTime = (UINT32)pl->l_linger * 1000;

            return(0);
        }

    case SO_SNDTIMEO:
    case SO_RCVTIMEO:
        {
            struct timeval *ptv = (struct timeval *)pbuf;
            UINT32         Time;

            if( size != sizeof(struct timeval) )
                return( EINVAL );

            Time = (UINT32)ptv->tv_sec*1000;
            Time += (UINT32)((ptv->tv_usec+999)/1000);

            if( Prop == SO_SNDTIMEO )
                ps->TxTimeout = Time;
            else
                ps->RxTimeout = Time;
            return(0);
        }

    case SO_IFDEVICE:
        {
            HANDLE h;

            /* Only DGRAM sockets can use the IFDEVICE option */
            if( !(ps->StateFlags & SS_ADDR) || size != sizeof(uint) )
                return( EINVAL );

            h = (HANDLE)NIMUFindByIndex ( *(uint *)pbuf );
            if (!h)
                return EINVAL;

            ps->hIFTx = h;
            return(0);
        }
    case SO_TXTIMESTAMP:
        ps->pTimestampFxn = (TimestampFxn) ((UINT32) pbuf);
        break;
    case SO_PRIORITY:
        {
            /* Extract the user priority */
            UINT16 priority = *((UINT16 *)pbuf);

            /* There are at max. 8 levels of priority. 
             *  A special value of PRIORITY_UNDEFINED (0xFFFF) is used to move the socket back 
             *  to NO PRIORITY state. */
            if (priority != PRIORITY_UNDEFINED)
            {
                if (priority >= 8)
                    return EINVAL;
            }

            /* Set the priority in the socket. */
            ps->SockPriority = priority;
            DbgPrintf(DBG_INFO,
                    "SockSet: DEBUG: Configuring socket priority to be 0x%x\n",
                    priority);
            return 0;
        }
    }

    /* For the remainder, the property value is an int */
    if( size < sizeof(int) )
        return( EINVAL );
    value = *(int *)pbuf;

    switch( Prop )
    {
    case SO_BLOCKING:
        if( value )
            ps->StateFlags &= ~SS_NBIO;
        else
            ps->StateFlags |= SS_NBIO;
        break;

    case SO_DEBUG:
    case SO_KEEPALIVE:
    case SO_DONTROUTE:
    case SO_USELOOPBACK:
    case SO_BROADCAST:
    case SO_REUSEADDR:
    case SO_REUSEPORT:
    case SO_OOBINLINE:
    case SO_TIMESTAMP:
        if( value )
            ps->OptionFlags |= (uint)Prop;
        else
            ps->OptionFlags &= (uint)~Prop;
        break;

    case SO_SNDBUF:
        if( ps->hSBTx && SBSetMax(ps->hSBTx,value)!=value )
            error = EINVAL;
        else
            ps->TxBufSize = value;
        break;

    case SO_RCVBUF:
        if( ps->hSBRx && SBSetMax(ps->hSBRx,value)!=value )
            error = EINVAL;
        else
            ps->RxBufSize = value;
        break;

    case SO_SNDLOWAT:
        if( ps->hSBTx )
            SBSetMin( ps->hSBTx, value );
        break;

    case SO_RCVLOWAT:
        if( ps->hSBRx )
            SBSetMin( ps->hSBRx, value );
        break;

    case SO_ERROR:
        ps->ErrorPending = value;
        break;

    default:
        error = ENOPROTOOPT;
        break;
    }

    return(error);
}

/*-------------------------------------------------------------------- */
/* SockGet() */
/* Get Socket Parameter Value */
/*-------------------------------------------------------------------- */
int SockGet(HANDLE hSock, int Type, int Prop, void *pbuf, int *psize)
{
    SOCK *ps = (SOCK *)hSock;
    int  error = 0;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockGet: HTYPE %04x\n",ps->fd.Type);
        return( ENOTSOCK );
    }
#endif

    /* Check pointers, just to be safe */
    if( !psize || !pbuf )
        return( EINVAL );

    /* We also handle IPPROTO_IP and IPROTO_TCP */
    if( Type != SOL_SOCKET )
    {
        if( Type == IPPROTO_TCP )
        {
            if( ps->SockProt == SOCKPROT_TCP )
                return( TcpPrGetOption( hSock, ps->hTP, Prop, pbuf, psize ) );
            else
                return( EINVAL );
        }
        if( Type == IPPROTO_IP )
        {
            if( Prop != IP_OPTIONS )
            {
                if( *psize < sizeof(int) )
                    return( EINVAL );
                *psize = sizeof(int);
            }

            switch( Prop )
            {
            case IP_TOS:
                *(int *)pbuf = (int)ps->IpTos;
                return(0);

            case IP_TTL:
                *(int *)pbuf = (int)ps->IpTtl;
                return(0);

            case IP_HDRINCL:
                if( ps->IpFlags & SOCK_IP_HDRINCL )
                    *(int *)pbuf = 1;
                else
                    *(int *)pbuf = 0;
                return(0);

            case IP_OPTIONS:
                if( *psize < (int)ps->IpOptSize )
                    return( EINVAL );
                *psize = (int)ps->IpOptSize;
                mmCopy( pbuf, ps->IpOptions, ps->IpOptSize );
                return(0);
            }
        }
        return( EINVAL );
    }

    /* Socket Properties */

    /* Handle the structure based first */

    switch( Prop )
    {
    case SO_LINGER:
        {
            struct linger *pl = (struct linger *)pbuf;
            if( *psize < sizeof( struct linger ) )
                return( EINVAL );
            *psize = sizeof( struct linger );
            if( ps->OptionFlags & SO_LINGER )
                pl->l_onoff = 1;
            else
                pl->l_onoff = 0;
            pl->l_linger = (int)(ps->dwLingerTime/1000);
            return(0);
        }

    case SO_SNDTIMEO:
    case SO_RCVTIMEO:
        {
            struct timeval *ptv = (struct timeval *)pbuf;

            if( *psize < sizeof(struct timeval) )
                return( EINVAL );
            *psize = sizeof( struct timeval );
            if( Prop == SO_SNDTIMEO )
            {
                ptv->tv_sec = ps->TxTimeout / 1000;
                ptv->tv_usec = (ps->TxTimeout % 1000) * 1000;
            }
            else
            {
                ptv->tv_sec = ps->RxTimeout / 1000;
                ptv->tv_usec = (ps->RxTimeout % 1000) * 1000;
            }
            return(0);
        }

    case SO_IFDEVICE:
        {
            if( *psize < sizeof( uint ) )
                return( EINVAL );
            *psize = sizeof( uint );
            if( !ps->hIFTx )
                *(uint *)pbuf = 0;
            else
                *(uint *)pbuf = IFGetIndex( ps->hIFTx );
            return(0);
        }
    case SO_PRIORITY:
        {
            if( *psize != sizeof(UINT16))
                return( EINVAL );
            *psize = sizeof(UINT16);
            *(UINT16 *)pbuf = ps->SockPriority;
            break;
        }
    }

    /* For the remainder, the property value is an int */
    if( *psize < sizeof(int) )
        return( EINVAL );
    *psize = sizeof(int);

    switch( Prop )
    {
    case SO_BLOCKING:
        if( ps->StateFlags & SS_NBIO )
            *(int *)pbuf = 0;
        else
            *(int *)pbuf = 1;
        break;

    case SO_DEBUG:
    case SO_KEEPALIVE:
    case SO_DONTROUTE:
    case SO_USELOOPBACK:
    case SO_BROADCAST:
    case SO_REUSEADDR:
    case SO_REUSEPORT:
    case SO_OOBINLINE:
    case SO_TIMESTAMP:
        if( ps->OptionFlags & (uint)Prop )
            *(int *)pbuf = 1;
        else
            *(int *)pbuf = 0;
        break;

    case SO_SNDBUF:
        *(int *)pbuf = ps->TxBufSize;
        break;

    case SO_RCVBUF:
        *(int *)pbuf = ps->RxBufSize;
        break;

    case SO_SNDLOWAT:
        if( ps->hSBTx )
            *(int *)pbuf = (int)SBGetMin( ps->hSBTx );
        else
            *(int *)pbuf = SOCK_BUFMINRX;
        break;

    case SO_RCVLOWAT:
        if( ps->hSBRx )
            *(int *)pbuf = (int)SBGetMin( ps->hSBRx );
        else
            *(int *)pbuf = SOCK_BUFMINRX;
        break;

    case SO_ERROR:
        *(int *)pbuf = ps->ErrorPending;
        ps->ErrorPending = 0;
        break;

    case SO_TYPE:
        *(int *)pbuf = (int)ps->SockType;
        break;

    default:
        error = ENOPROTOOPT;
        break;
    }

    return(error);
}

/*-------------------------------------------------------------------- */
/* SockRecv */
/* Receive data from a socket. Optionally fill in the Peer name. */
/*-------------------------------------------------------------------- */
int SockRecv
(
    HANDLE      h,
    char        *pBuf,
    INT32       size,
    int         flags,
    PSA         pPeer,
    INT32       *pRetSize
)
{
    SOCK     *ps = (SOCK *)h;
    int      read_again = 1;
    int      error      = 0;
    INT32    Total      = 0;
    INT32    SizeCopy   = 0;
    INT32    PeekOffset = 0;
    IPN      IPFrom;
    uint     PortFrom;
    PSA_IN   psa_Peerin = (PSA_IN)pPeer;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockRecv: HTYPE %04x\n",ps->fd.Type);
        return( ENOTSOCK );
    }
#endif

    /* Check for accepting socket type */
    if( ps->OptionFlags & SO_ACCEPTCONN )
        return( EINVAL );

    /* Check for a null read */
    if( !size )
        goto rx_complete;

    /* Check the OOB flag */
    if( flags & MSG_OOB )
    {
        /* MSG_OOB Specified */

        /* If in OOBINLINE mode, this flag is illegal, or */
        /* If stocket is not in OOB mode, it is illegal */
        if( (ps->OptionFlags & SO_OOBINLINE) ||
                !(ps->StateFlags & SS_OOBACTIVE) )
            return( EINVAL );

        /* If we don't have the OOB data yet, then we have a blocking */
        /* situation */
        if( !(ps->StateFlags & SS_OOBDATAVALID) )
            return( EWOULDBLOCK );

        /* We have the OOB Data ready - Complete the recv call */
        *pBuf = ps->OOBData;
        SizeCopy = 1;

        /* Clear the OOB mode if not PEEKING */
        if( !(flags & MSG_PEEK) )
            ps->StateFlags &= ~(SS_OOBACTIVE | SS_OOBDATAVALID);

        goto rx_complete;
    }

rx_restart:
    /* Get the total bytes available */
    Total = SBGetTotal(ps->hSBRx) - PeekOffset;

    /* Check for blocking condition */
    if( !Total )
    {
        /* Check all non-blocking conditions first */

        /* Return any pending error */
        if( ps->ErrorPending )
        {
            /* Don't eat the error if we're returning data */
            if( !SizeCopy )
            {
                error = ps->ErrorPending;
                /* Only consume the error when not peeking */
                if( !(flags & MSG_PEEK) )
                    ps->ErrorPending = 0;
            }
            goto rx_dontblock;
        }

        /* Set read_again to zero. This will cause us not to try */
        /* another read if we fall out of the blocking code */
        read_again = 0;

        /* Don't block if the socket is no longer connected (this is */
        /* actually an error condition) */
        if( (ps->StateFlags & SS_CONNREQUIRED) &&
                !(ps->StateFlags & (SS_ISCONNECTED|SS_ISCONNECTING)) )
        {
            error = ENOTCONN;
            goto rx_dontblock;
        }

        /* Don't block if the receiver is shut down */
        if( ps->StateFlags & SS_CANTRCVMORE )
        {
            error = 0;
            goto rx_dontblock;
        }

        /* Don't block if there was an overriding request not to block */
        /* Don't block on NBIO if there was NO overriding request to block */
        if( (flags & MSG_DONTWAIT) ||
            ( !(flags & MSG_WAITALL) && (ps->StateFlags & SS_NBIO) ) )
        {
            error = EWOULDBLOCK;
            goto rx_dontblock;
        }

        /* If we copied the minimum and WAITALL is not set, then don't block */
        /* the minimum. (If ATOMIC, SizeCopy will be zero.) */
        if( SizeCopy >= SBGetMin(ps->hSBRx) && !(flags&MSG_WAITALL) )
            goto rx_dontblock;

        /* Finally, the blocking code */

        /* If we get a file event, then try the loop again */
        if( FdWaitEvent( ps, FD_EVENT_READ, ps->RxTimeout ) )
        {
            read_again = 1;
            goto rx_restart;
        }
        else
            error = EWOULDBLOCK;
    }

rx_dontblock:
    /* If we read nothing this time around, we're done */
    if( !Total )
        goto rx_complete;

    /* Get how much data to copy */

    /* Adjust to buffer size */
    if( size < (Total+SizeCopy) )
        Total = size-SizeCopy;

    /* Don't cross an OOB mark */
    if( (ps->StateFlags & SS_OOBACTIVE) && ps->OOBMark && Total > ps->OOBMark )
    {
        read_again = 0;
        Total = ps->OOBMark;
    }

    if( Total )
    {
        if( flags & MSG_PEEK )
        {
            Total = SBRead( ps->hSBRx, Total, PeekOffset,
                            (UINT8 *)(pBuf+SizeCopy), &IPFrom, &PortFrom, 1 );

            /* Move the peek offet since we don't consume data from hSBRx */
            PeekOffset += Total;
        }
        else
        {
            Total = SBRead( ps->hSBRx, Total, 0, (UINT8 *)(pBuf+SizeCopy),
                                                 &IPFrom, &PortFrom, 0 );

            if( ps->StateFlags & SS_OOBACTIVE )
            {
                /* Clear the OOB mode if at the mark */
                if( !ps->OOBMark )
                    ps->StateFlags &= ~(SS_OOBACTIVE | SS_OOBDATAVALID);
                /* Otherwise, move us towards the mark */
                else
                    ps->OOBMark -= Total;
            }
        }

        if( psa_Peerin )
        {
            /* Get Peer Data from Socket */
            psa_Peerin->sin_family      = (UINT8)ps->Family;

            if( ps->StateFlags & SS_ADDR )
            {
                psa_Peerin->sin_port        = PortFrom;
                psa_Peerin->sin_addr.s_addr = IPFrom;
            }
            else
            {
                psa_Peerin->sin_port        = ps->FPort;
                psa_Peerin->sin_addr.s_addr = ps->FIP;
            }
        }

        /* Record that we received this data */
        SizeCopy += Total;

        /* Notify the protocol of status change */
        SockPrRecv( ps );

        /* If we're ATOMIC, get out now */
        if( ps->StateFlags & SS_ATOMIC )
        {
            *pRetSize = Total;
            return(0);
        }
    }

    /* Try and get all the data if possible */
    if( read_again && size > SizeCopy )
        goto rx_restart;

rx_complete:
    *pRetSize = SizeCopy;
    if( SizeCopy )
        return(0);
    return(error);
}

/*-------------------------------------------------------------------- */
/* SockRecvNC */
/* Receive data from a socket without copy. */
/* Optionally fill in the Peer name. */
/*-------------------------------------------------------------------- */
int SockRecvNC( HANDLE h, int flags, PSA pPeer, PBM_Pkt **ppPkt )
{
    SOCK     *ps = (SOCK *)h;
    int      error    = 0;
    INT32    Total    = 0;
    IPN      IPFrom;
    uint     PortFrom;
    PSA_IN   psa_Peerin = (PSA_IN)pPeer;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockRecv: HTYPE %04x\n",ps->fd.Type);
        return( ENOTSOCK );
    }
#endif

    /* Check for accepting socket type */
    if( ps->OptionFlags & SO_ACCEPTCONN )
        return( EINVAL );

    /* Check the OOB and PEEK flag */
    if( flags & (MSG_OOB|MSG_PEEK) )
        return( EINVAL );

    /* Must be ATOMIC socket */
    if( !(ps->StateFlags & SS_ATOMICREAD) )
        return( EINVAL );

rx_restart:
    /* Get the total bytes available */
    Total = SBGetTotal(ps->hSBRx);

    /* Check for blocking condition */
    if( !Total )
    {
        /* Check all non-blocking conditions first */

        /* Return any pending error */
        if( ps->ErrorPending )
        {
            error = ps->ErrorPending;
            ps->ErrorPending = 0;
            goto rx_dontblock;
        }

        /* Don't block if the socket is no longer connected (this is */
        /* actually an error condition) */
        if( (ps->StateFlags & SS_CONNREQUIRED) &&
                !(ps->StateFlags & (SS_ISCONNECTED|SS_ISCONNECTING)) )
        {
            error = ENOTCONN;
            goto rx_dontblock;
        }

        /* Don't block if the receiver is shut down */
        if( ps->StateFlags & SS_CANTRCVMORE )
        {
            error = 0;
            goto rx_dontblock;
        }

        /* Don't block if there was an overriding request not to block */
        /* Don't block on NBIO if there was NO overriding request to block */
        if( (flags & MSG_DONTWAIT) ||
            ( !(flags & MSG_WAITALL) && (ps->StateFlags & SS_NBIO) ) )
        {
            error = EWOULDBLOCK;
            goto rx_dontblock;
        }

        /* Finally, the blocking code */

        /* If we get a file event, then try the loop again */
        if( FdWaitEvent( ps, FD_EVENT_READ, ps->RxTimeout ) )
            goto rx_restart;
        else
            error = EWOULDBLOCK;
    }

rx_dontblock:
    /* Check for FATAL blocking condition */
    if( !Total )
    {
        *ppPkt = 0;
        return(error);
    }
    else
    {
        /* We don't support OOB on this type of read, so clear any OOB mark */
        if( ps->StateFlags & SS_OOBACTIVE )
            ps->StateFlags &= ~(SS_OOBACTIVE | SS_OOBDATAVALID);

        /* Read data packet */
        *ppPkt = SBReadNC( ps->hSBRx, &IPFrom, &PortFrom );

        /* Fill in peer if supplied */
        if( psa_Peerin )
        {
            /* Get Peer Data from Socket */
            psa_Peerin->sin_family      = (UINT8)ps->Family;

            if( ps->StateFlags & SS_ADDR )
            {
                psa_Peerin->sin_port        = PortFrom;
                psa_Peerin->sin_addr.s_addr = IPFrom;
            }
            else
            {
                psa_Peerin->sin_port        = ps->FPort;
                psa_Peerin->sin_addr.s_addr = ps->FIP;
            }
        }

        /* Notify the protocol of status change */
        SockPrRecv( ps );
        return(0);
    }
}

/*-------------------------------------------------------------------- */
/* SockSend() */
/* Send data to a socket. */
/*-------------------------------------------------------------------- */
int SockSend
(
    HANDLE   h,
    char     *pBuf,
    INT32    size,
    int      flags,
    INT32    *pRetSize
)
{
    SOCK     *ps = (SOCK *)h;
    int      DontRoute = 0, error = 0;
    INT32    SizeCopy = 0;
    INT32    AddCopy;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockRecv: HTYPE %04x\n",ps->fd.Type);
        return( ENOTSOCK );
    }
#endif

    /* Set a flag to see if we should temporarily add SO_DONTROUTE */
    if( (flags & MSG_DONTROUTE) && (ps->StateFlags & SS_ATOMICWRITE) &&
                                  !(ps->OptionFlags & SO_DONTROUTE) )
        DontRoute = 1;

    /* Bound size */
    if( size < 0 )
        return( EINVAL );
    if( !size && !(ps->StateFlags & SS_ATOMICWRITE) )
        return( EINVAL );

    /* This routine doesn't actually enqueue any data, since "how" */
    /* the data is queued is dependent on the protocol. */

    /* Since in a reduced memory stack (i.e.: us), it is possible to */
    /* run out of memory before buffer limits are reached, we don't */
    /* even bother to check memory status. The protocol returns the */
    /* number of bytes consumed, and hence, when to block. */

    while( SizeCopy<size || !size )
    {
        /* Check error conditions in our loop since the error may */
        /* occur while we're sending */

        /* Return any pending error */
        if( ps->ErrorPending )
        {
            error = ps->ErrorPending;
            /* Only consume the error if we're actually going to report it */
            if( !SizeCopy )
                ps->ErrorPending = 0;
            break;
        }

        /* Must be connected - our upper layer ALWAYS connects on a UDP */
        /* sendto(). */
        if( !(ps->StateFlags & SS_ISCONNECTED) )
        {
            error = ENOTCONN;
            break;
        }

        /* Can't send if send shutdown */
        if( ps->StateFlags & SS_CANTSENDMORE )
        {
            error = ESHUTDOWN;
            break;
        }

        /* Send the Data */
        if( DontRoute )
            ps->OptionFlags |= SO_DONTROUTE;
        if( flags & MSG_OOB )
        {
            if( ps->SockProt == SOCKPROT_TCP )
                error = TcpPrSendOOB( (HANDLE)ps, ps->hTP,
                                      (UINT8 *)(pBuf+SizeCopy),
                                      size-SizeCopy, &AddCopy );
            else
                error = EINVAL;
        }
        else
        {
            if( ps->SockProt == SOCKPROT_TCP )
                error = TcpPrSend( (HANDLE)ps, ps->hTP,
                                   (UINT8 *)(pBuf+SizeCopy),
                                   size-SizeCopy, &AddCopy );
            else if( ps->SockProt == SOCKPROT_UDP )
                error = UdpOutput( (HANDLE)ps, (UINT8 *)(pBuf+SizeCopy),
                                    size-SizeCopy, &AddCopy );
            else if( ps->SockProt == SOCKPROT_RAW )
                error = RawOutput( (HANDLE)ps, (UINT8 *)(pBuf+SizeCopy),
                                    size-SizeCopy, &AddCopy );
            else
                error = EINVAL;
        }

        if( DontRoute )
            ps->OptionFlags &= ~SO_DONTROUTE;

        /* Break out now on an error condition */
        if( error )
            break;

        /* Mark what we did copy */
        SizeCopy += AddCopy;        

        /* If we're ATOMIC, we sent what we could - leave now */
        if( ps->StateFlags & SS_ATOMICWRITE )
        {
            *pRetSize = SizeCopy;
            return(0);
        }

        /* Check blocking condition */
        if( SizeCopy < size && !AddCopy )
        {
            /* We need to block (protocol did not handle the data ) */

            /* Can't block a non-blocking socket */
            /* If we timeout, we have an error and break the loop */
            if( (ps->StateFlags & SS_NBIO) || (flags & MSG_DONTWAIT) ||
                    !FdWaitEvent( ps, FD_EVENT_WRITE, ps->TxTimeout ) )
            {
                error = EWOULDBLOCK;
                break;
            }
        }
    }

    *pRetSize = SizeCopy;
    if( SizeCopy )
        return(0);
    return( error );
}

