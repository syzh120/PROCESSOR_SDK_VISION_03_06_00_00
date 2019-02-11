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
 * ======== sockint.c ========
 *
 * Object member functions for the Sock device object.
 *
 * These functions are called from elsewhere in the stack, and would
 * not be called from the user layer.
 *
 */

#include <stkmain.h>
#include "sock.h"

/*-------------------------------------------------------------------- */
/* SockNotify() */
/* Notifies Socket of activity */
/* Returns 1 if the message was accepted, and 0 if the message */
/* was rejected. The action taken on a rejected message is */
/* message and protocol dependent. */
/*-------------------------------------------------------------------- */
int SockNotify( HANDLE h, int Notification )
{
    SOCK *ps = (SOCK *)h;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockNotify: HTYPE %04x",ps->fd.Type);
        return(0);
    }
#endif

    /* This switch handles active and listen-queued sockets */
    switch( Notification )
    {
    case SOCK_NOTIFY_CONNECT:
        /* Notification that Socket is fully connected */

        /* First, set socket state to CONNECTED */
        ps->StateFlags &= ~SS_ISCONNECTING;
        ps->StateFlags |= SS_ISCONNECTED;

        /* There are two cases for a connect. The first is a child of */
        /* a "listening" socket, and the other is an independently */
        /* connected socket. In the latter case, we simply wake the */
        /* owning task. */
        if( !ps->pParent )
            FdSignalEvent( ps, FD_EVENT_READ|FD_EVENT_WRITE );
        else
        {
            /* When the socket is a child of a listening socket, we move */
            /* the socket in question from the pending queue to the ready */
            /* queue of the parent. */

            /* If its on the pending queue, we'll move it off */
            if( ps->StateFlags & SS_PENDINGQ )
            {
                /* Dequeue from Pending */
                ps->StateFlags &= ~SS_PENDINGQ;
                ps->pPrevQ->pPending = ps->pPending;
                if( ps->pPending )
                    ps->pPending->pPrevQ = ps->pPrevQ;

                /* Enqueue onto Ready */
                ps->pReady = ps->pParent->pReady;
                ps->pPrevQ = ps->pParent;
                if( ps->pReady )
                    ps->pReady->pPrevQ = ps;
                ps->pParent->pReady = ps;
                ps->StateFlags |= SS_READYQ;
            }

            /* Now we wake the owning task of the parent socket */
            FdSignalEvent( ps->pParent, FD_EVENT_READ );
        }
        break;

    case SOCK_NOTIFY_RCVACK:
        /* Notification that Socket write data has been consumed */

        /* Wake owning task if waiting on write */
        FdSignalEvent( ps, FD_EVENT_WRITE );
        break;

    case SOCK_NOTIFY_RCVDATA:
        /* Notification that Socket read data is available */

        /* If we're closing or can't receive more flush new data */
        if( ps->StateFlags & (SS_CLOSING|SS_CANTRCVMORE) )
        {
            if( ps->hSBRx )
                SBFlush( ps->hSBRx, 1 );
            /* Reject the message to tell TCP we "flushed" */
            return(0);
        }

        /* Wake owning task if waiting on read */
        if( !ps->pParent )
            FdSignalEvent( ps, FD_EVENT_READ );
        break;

    case SOCK_NOTIFY_RCVFIN:
        /* Notification that the Socket will receive no more data */

        /* Mark the fact that we can't (won't) receive more data. This */
        /* will prevent the receive routine from blocking */
        ps->StateFlags |= SS_CANTRCVMORE;

        /* If not a listen-queued socket, wake the owning task if the */
        /* task is waiting on read or on OOB conditions */
        if( !ps->pParent )
            FdSignalEvent( ps, FD_EVENT_READ | FD_EVENT_EXCEPT );
        break;

    case SOCK_NOTIFY_DISCONNECT:
        /* Notification that the connection is disconnected, but not */
        /* yet closed. Can not send or receive data */

        /* Adjust the current state */
        ps->StateFlags &= ~(SS_ISCONNECTING | SS_LINGERING);
        ps->StateFlags |= (SS_CANTRCVMORE | SS_CANTSENDMORE);

        /* If not a listen-queued socket, wake the owning task if it */
        /* is waiting on any wait condition */
        if( !ps->pParent )
            FdSignalEvent( ps, FD_EVENT_READ|FD_EVENT_WRITE|FD_EVENT_EXCEPT );
        break;

    case SOCK_NOTIFY_CLOSED:
        /* Notification that the connection is fully closed. */

        /* If we were closing, this is what we were waiting for */
        if( ps->StateFlags & SS_CLOSING )
            SockIntAbort( ps );
        else
        {
            /* Reset the socket state */
            ps->StateFlags &= ~( SS_ISCONNECTING | SS_ISCONNECTED |
                                 SS_LINGERING );
            ps->StateFlags |= (SS_CANTRCVMORE | SS_CANTSENDMORE);

            /* If not a listen-queued socket, wake the owning task if it */
            /* is waiting on any wait condition */
            if( !ps->pParent )
                FdSignalEvent( ps, FD_EVENT_READ|FD_EVENT_WRITE|FD_EVENT_EXCEPT );
            /* Else, we abort the socket entirely. */
            /* [ Note that a socket on the READYQ normally can not reach this */
            /* state unless it has been dropped (not just closed) by the peer. */
            /* In this case, any sent data is lost. ] */
            else if( ps->StateFlags & (SS_READYQ | SS_PENDINGQ) )
                SockSpawnAbort( ps );
        }
        break;

    case SOCK_NOTIFY_ERROR:
        if( !ps->pParent )
            FdSignalEvent( ps, FD_EVENT_READ|FD_EVENT_WRITE|FD_EVENT_EXCEPT );
        break;
    }

    return(1);
}

/*-------------------------------------------------------------------- */
/* SockSetOOBMark() */
/* Notifies Socket of OOB Data, and sets synchronization mark */
/*-------------------------------------------------------------------- */
void SockSetOOBMark( HANDLE hSock, INT32 OOBMark )
{
    SOCK  *ps = (SOCK *)hSock;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockSetOOBMark: HTYPE %04x",ps->fd.Type);
        return;
    }
#endif

    /* Store the mark */
    ps->OOBMark = OOBMark;

    /* Enter OOB mode */
    ps->StateFlags |= SS_OOBACTIVE;

    /* Clear the held data */
    ps->StateFlags &= ~SS_OOBDATAVALID;

    /* Wake owning task if waiting on OOB data */
    FdSignalEvent( ps, FD_EVENT_EXCEPT );
}

/*-------------------------------------------------------------------- */
/* SockSetOOBData() */
/* Sets th OOB Data byte once in OOB Mode */
/*-------------------------------------------------------------------- */
void SockSetOOBData( HANDLE hSock, UINT8 OOBData )
{
    SOCK     *ps = (SOCK *)hSock;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockSetOOBMark: HTYPE %04x",ps->fd.Type);
        return;
    }
#endif

    /* Store the data */
    ps->OOBData = OOBData;

    /* Set valid */
    ps->StateFlags |= SS_OOBDATAVALID;

    /* Wake owning task if waiting on OOB data */
    FdSignalEvent( ps, FD_EVENT_EXCEPT );
}

/*-------------------------------------------------------------------- */
/* SockSpawnAbort() */
/* Called to abort a socket spawned via a call to SockPcbResolve */
/*-------------------------------------------------------------------- */
void SockSpawnAbort( HANDLE h )
{
    SOCK *ps = (SOCK *)h;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockSpawnAbort: HTYPE %04x",ps->fd.Type);
        return;
    }
    if( !ps->pParent )
    {
        DbgPrintf(DBG_ERROR,"SockSpawnAbort: No Parent!");
        return;
    }
#endif

    /* This is pretty simple - just dequeue and abort */
    if( ps->StateFlags & SS_PENDINGQ )
    {
        /* Zap flag & Dequeue */
        ps->StateFlags &= ~SS_PENDINGQ;
        ps->pPrevQ->pPending = ps->pPending;
        if( ps->pPending )
            ps->pPending->pPrevQ = ps->pPrevQ;
    }
    else if( ps->StateFlags & SS_READYQ )
    {
        /* Zap flag & Dequeue */
        ps->StateFlags &= ~SS_READYQ;
        ps->pPrevQ->pReady = ps->pReady;
        if( ps->pReady )
            ps->pReady->pPrevQ = ps->pPrevQ;
    }
    ps->pParent->ConnTotal--;
    ps->pParent = 0;
    SockIntAbort( ps );
}


/*-------------------------------------------------------------------- */
/* SockValidateRoute() */
/* Attempt to get a valid route for a connected socket */
/*-------------------------------------------------------------------- */
HANDLE SockValidateRoute( HANDLE h )
{
    SOCK *ps = (SOCK *)h;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockValidateRoute: HTYPE %04x",ps->fd.Type);
        return(0);
    }
#endif

    /* DeRef any held route */
    if( ps->hRoute )
        RtDeRef( ps->hRoute );
    ps->hRoute = 0;

    /* If the destination is a BCAST or MCAST, we don't use a route. */
    /* Otherwise; find the next hop for this destination. Search with cloning. */
    if( ps->FIP != INADDR_ANY &&
            ps->FIP != INADDR_BROADCAST && !(IN_MULTICAST(ps->FIP)) &&
            (!IP_DIRECTED_BCAST || !BindGetIFByDBCast(ps->FIP)) )
        ps->hRoute = IPGetRoute( FLG_RTF_CLONE|FLG_RTF_REPORT, ps->FIP );

    return( ps->hRoute );
}

/*-------------------------------------------------------------------- */
/* SockCreatePacket */
/* Creates Ip Packet using Socket info */
/*-------------------------------------------------------------------- */
PBM_Pkt *SockCreatePacket( HANDLE hSock, uint Payload )
{
    SOCK    *ps = (SOCK *)hSock;
    PBM_Pkt *pPkt;
    IPHDR   *pIpHdr;
    uint    IPHdrSize;

    /* Note "ps" can be NULL */
    if( !ps )
        IPHdrSize = IPHDR_SIZE;
    else if( ps->IpFlags & IP_HDRINCL )
        IPHdrSize = 0;
    else
        IPHdrSize = IPHDR_SIZE + ps->IpOptSize;

    if( !(pPkt = NIMUCreatePacket(Payload + IPHdrSize)) )
        return( 0 );

    /* Inherit the packet priority from the socket; since all packets
     * transmitted from a particular socket will have the same priority.*/
    if (ps)
        pPkt->PktPriority = ps->SockPriority;
    else
        pPkt->PktPriority = PRIORITY_UNDEFINED;

    /* Set the IpHdrLen */
    pPkt->IpHdrLen = IPHdrSize;

    /* Set the valid data to the required size of the payload+IP */
    pPkt->ValidLen = Payload + IPHdrSize;

    if( !ps || !(ps->IpFlags & IP_HDRINCL) )
    {
        /* Fill in IP Header */
        pIpHdr    = (IPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);
        pIpHdr->VerLen  = 0x40 + IPHdrSize/4;
        if( ps )
        {
            pIpHdr->Protocol = (UINT8)ps->Protocol;
            pIpHdr->Ttl      = (UINT8)ps->IpTtl;
            pIpHdr->Tos      = (UINT8)ps->IpTos;
            WrNet32( &pIpHdr->IPSrc, ps->LIP );
            WrNet32( &pIpHdr->IPDst, ps->FIP );
            if( ps->IpOptSize )
                mmCopy( pIpHdr->Options, ps->IpOptions, ps->IpOptSize );
        }
        else
        {
            pIpHdr->Protocol = 0;
            pIpHdr->Ttl      = SOCK_TTL_DEFAULT;
            pIpHdr->Tos      = SOCK_TOS_DEFAULT;
            WrNet32( &pIpHdr->IPSrc, 0 );
            WrNet32( &pIpHdr->IPDst, 0 );
        }
    }
    return( pPkt );
}


/* The following functions are direct sturcture accesses when */
/* not using _STRONG_CHECKING */
#ifdef _STRONG_CHECKING

/*-------------------------------------------------------------------- */
/* SockGetProtocol() */
/* Returns the socket's Protocol */
/*-------------------------------------------------------------------- */
uint SockGetProtocol( HANDLE h )
{
    if( ((SOCK *)h)->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockGetProtocol: HTYPE %04x",((SOCK *)h)->fd.Type);
        return( 0 );
    }
    return( ((SOCK *)h)->Protocol );
}

/*-------------------------------------------------------------------- */
/* SockGetIpHdrSize() */
/* Returns the socket's Protocol */
/*-------------------------------------------------------------------- */
uint SockGetIpHdrSize( HANDLE h )
{
    if( ((SOCK *)h)->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockGetIpHdrSize: HTYPE %04x",((SOCK *)h)->fd.Type);
        return( 0 );
    }

    if( ((SOCK *)h)->IpFlags & IP_HDRINCL )
        return(0);
    else
        return( IPHDR_SIZE + ((SOCK *)h)->IpOptSize );
}

/*-------------------------------------------------------------------- */
/* SockGetTx() */
/* Returns the handle to the socket's Tx SB */
/*-------------------------------------------------------------------- */
HANDLE SockGetTx( HANDLE h )
{
    if( ((SOCK *)h)->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockGetLTB: HTYPE %04x",((SOCK *)h)->fd.Type);
        return( 0 );
    }
    return( ((SOCK *)h)->hSBTx );
}

/*-------------------------------------------------------------------- */
/* SockGetRx() */
/* Returns the handle to the socket's Rx SB */
/*-------------------------------------------------------------------- */
HANDLE SockGetRx( HANDLE h )
{
    if( ((SOCK *)h)->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockGetLRB: HTYPE %04x",((SOCK *)h)->fd.Type);
        return( 0 );
    }
    return( ((SOCK *)h)->hSBRx );
}

/*-------------------------------------------------------------------- */
/* SockGetTP() */
/* Returns the handle to the socket's transport protocol */
/*-------------------------------------------------------------------- */
HANDLE SockGetTP( HANDLE h )
{
    if( ((SOCK *)h)->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockGetTP: HTYPE %04x",((SOCK *)h)->fd.Type);
        return( 0 );
    }
    return( ((SOCK *)h)->hTP );
}

/*-------------------------------------------------------------------- */
/* SockGetLIP() */
/* Returns the socket's Local IP */
/*-------------------------------------------------------------------- */
IPN SockGetLIP( HANDLE h )
{
    if( ((SOCK *)h)->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockGetLIP: HTYPE %04x",((SOCK *)h)->fd.Type);
        return( 0 );
    }
    return( ((SOCK *)h)->LIP );
}

/*-------------------------------------------------------------------- */
/* SockGetFIP() */
/* Returns the socket's foreign IP */
/*-------------------------------------------------------------------- */
IPN SockGetFIP( HANDLE h )
{
    if( ((SOCK *)h)->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockGetFIP: HTYPE %04x",((SOCK *)h)->fd.Type);
        return( 0 );
    }
    return( ((SOCK *)h)->FIP );
}

/*-------------------------------------------------------------------- */
/* SockGetLPort() */
/* Returns the socket's Local Port */
/*-------------------------------------------------------------------- */
uint SockGetLPort( HANDLE h )
{
    if( ((SOCK *)h)->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockGetLPort: HTYPE %04x",((SOCK *)h)->fd.Type);
        return( 0 );
    }
    return( ((SOCK *)h)->LPort );
}

/*-------------------------------------------------------------------- */
/* SockGetFPort() */
/* Returns the socket's Foreign Port */
/*-------------------------------------------------------------------- */
uint SockGetFPort( HANDLE h )
{
    if( ((SOCK *)h)->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockGetFPort: HTYPE %04x",((SOCK *)h)->fd.Type);
        return( 0 );
    }
    return( ((SOCK *)h)->FPort );
}

/*-------------------------------------------------------------------- */
/* SockGetRoute() */
/* Returns the socket's cached route */
/*-------------------------------------------------------------------- */
HANDLE SockGetRoute( HANDLE h )
{
    if( ((SOCK *)h)->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockGetRoute: HTYPE %04x",((SOCK *)h)->fd.Type);
        return( 0 );
    }
    return( ((SOCK *)h)->hRoute );
}

/*-------------------------------------------------------------------- */
/* SockGetIFTx() */
/* Returns the socket's egress IF (used only in special cases) */
/*-------------------------------------------------------------------- */
HANDLE SockGetIFTx( HANDLE h )
{
    if( ((SOCK *)h)->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockGetIFTx: HTYPE %04x",((SOCK *)h)->fd.Type);
        return( 0 );
    }
    return( ((SOCK *)h)->hIFTx );
}

/*-------------------------------------------------------------------- */
/* SockGetOptionFlags() */
/* Returns the socket's Option Flags */
/*-------------------------------------------------------------------- */
uint SockGetOptionFlags( HANDLE h )
{
    if( ((SOCK *)h)->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockGetOptionFlags: HTYPE %04x",((SOCK *)h)->fd.Type);
        return( 0 );
    }
    return( ((SOCK *)h)->OptionFlags );
}

/*-------------------------------------------------------------------- */
/* SockSetError() */
/* Set the socket's ErrorPending value */
/*-------------------------------------------------------------------- */
void SockSetError( HANDLE h, int Error )
{
    if( ((SOCK *)h)->fd.Type != HTYPE_SOCK )
    {
        DbgPrintf(DBG_ERROR,"SockSetError: HTYPE %04x",((SOCK *)h)->fd.Type);
        return;
    }
    ((SOCK *)h)->ErrorPending = Error;
}

#endif

