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
 * ======== sock6int.c ========
 *
 * The file implements the SOCKET6 Family. 
 *
 */


#include <stkmain.h>
#include "sock6.h"

#ifdef _INCLUDE_IPv6_CODE

/** 
 *  @b Description
 *  @n  
 *      This function is called to abort a socket spawned via 
 *      a call to Sock6PcbResolve
 *
 *  @param[in]  h
 *      Socket handle of the Spawned socket.
 *
 *  @retval
 *      Not Applicable.
 */
void Sock6SpawnAbort( HANDLE h )
{
    SOCK6 *ps = (SOCK6 *)h;

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
    Sock6IntAbort( ps );
}

/** 
 *  @b Description
 *  @n  
 *      This function is called by Layer4 to notify the socket
 *      of any read/write/connection status activity.
 *
 *  @param[in]  h
 *      Socket handle on which activity has been detected
 *
 *  @param[in]  Notification
 *      Notification Event detected.
 *
 *  @retval
 *      1   -   Message was accepted
 *  @retval
 *      0   -   Message was not accepted
 *
 *  The action taken on a rejected message is message and protocol dependent.
 */
int Sock6Notify( HANDLE h, int Notification )
{
    SOCK6* ps = (SOCK6 *)h;

    /* Process the notification depending on the type of message received. */
    switch (Notification)
    {
        case SOCK_NOTIFY_CONNECT:
        {
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
        }
        case SOCK_NOTIFY_RCVACK:
        {
            /* Notification that Socket write data has been consumed */

            /* Wake owning task if waiting on write */
            FdSignalEvent( ps, FD_EVENT_WRITE );
            break;
        }
        case SOCK_NOTIFY_RCVDATA:
        {
            /* Notification to the socket that data has been received. 
             * In this case we need to signal the parent task that data 
             * has been received. 
             */

            /* If we're closing or can't receive more flush new data */
            if (ps->StateFlags & (SS_CLOSING|SS_CANTRCVMORE))
            {
                if (ps->hSBRx)
                    SB6Flush(ps->hSBRx, 1);

                /* Reject the message to tell TCP we "flushed" */
                return(0);
            }

            /* Wake owning task if waiting on read */
            if (!ps->pParent)
                FdSignalEvent(ps, FD_EVENT_READ);

            break;
        }
        case SOCK_NOTIFY_RCVFIN:
        {
            /* Notification that the Socket will receive no more data */

            /* Mark the fact that we can't (won't) receive more data. This */
            /* will prevent the receive routine from blocking */
            ps->StateFlags |= SS_CANTRCVMORE;

            /* If not a listen-queued socket, wake the owning task if the */
            /* task is waiting on read or on OOB conditions */
            if( !ps->pParent )
                FdSignalEvent( ps, FD_EVENT_READ | FD_EVENT_EXCEPT );            
            break;
        }
        case SOCK_NOTIFY_DISCONNECT:
        {
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
        }
        case SOCK_NOTIFY_CLOSED:
        {
            /* Notification that the connection is fully closed. */
            /* If we were closing, this is what we were waiting for */
            if( ps->StateFlags & SS_CLOSING )
                Sock6IntAbort( ps );
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
                    Sock6SpawnAbort( (HANDLE)ps );
            }
            break;
        }
        case SOCK_NOTIFY_ERROR:
        {
            if( !ps->pParent )
                FdSignalEvent( ps, FD_EVENT_READ|FD_EVENT_WRITE|FD_EVENT_EXCEPT );            
            break;
        }
    }

    /* Message was successfully processed. */
    return 1;
}

/** 
 *  @b Description
 *  @n  
 *      This function finds and caches a route in the SOCK6 object.
 *      The Foreign IP associated with the socket is used to determine
 *      the route.
 *
 *  @param[in]  h
 *      Socket handle on which route is to be cached
 *
 *  @retval
 *      Success   -   Handle to the ROUTE6 object
 *  @retval
 *      Error     -   0
 */
HANDLE Sock6ValidateRoute(HANDLE h)
{
    SOCK6*  ps = (SOCK6 *)h;

    /* Dereference any cached routes we had. */ 
    if (ps->hRoute6 != 0)
        Rt6Free(ps->hRoute6);
    ps->hRoute6 = 0;

    /* We can stored cached routes only for packets which are UNICAST. */
    if (IPv6CompareAddress(IPV6_UNSPECIFIED_ADDRESS, ps->FIP) == 0)
    {
        /* Its not an unspecified address. Is this Multicast? */
        if (IPv6IsMulticast(ps->FIP) == 0)
        {
            /* OK; not a multicast address; packet can be routed. 
             * This will also increment the reference counter of the
             * cached route. */
            ps->hRoute6 = IPv6GetRoute (ps->FIP);
        }
    }
    return ps->hRoute6;
}

/*-------------------------------------------------------------------- */
/* SockSetOOBMark() */
/* Notifies Socket of OOB Data, and sets synchronization mark */
/*-------------------------------------------------------------------- */
void Sock6SetOOBMark( HANDLE hSock, INT32 OOBMark )
{
    SOCK6  *ps = (SOCK6 *)hSock;

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
void Sock6SetOOBData( HANDLE hSock, UINT8 OOBData )
{
    SOCK6     *ps = (SOCK6 *)hSock;

    /* Store the data */
    ps->OOBData = OOBData;

    /* Set valid */
    ps->StateFlags |= SS_OOBDATAVALID;

    /* Wake owning task if waiting on OOB data */
    FdSignalEvent( ps, FD_EVENT_EXCEPT );
}

/** 
 *  @b Description
 *  @n  
 *      The function creates an IPv6 packet for the SOCKET6 Family.
 *      It fills in the IPv6 header of the packet with values 
 *      from the socket if a valid handle is passed, else with
 *      defaults. 
 *
 *  @param[in]  hSock
 *      Handle of the socket for which the packet is being created.
 *
 *  @param[in]  Payload
 *      Size of the packet
 *
 *  @param[in]  NextHeader
 *      Size of the packet
 *
 *  @retval
 *      Success -   Pointer to the packet created
 *  @retval
 *      Error   -   NULL                            
 */
PBM_Pkt* Sock6CreatePacket( HANDLE hSock, uint Payload, uint NextHeader)
{
    SOCK6*      ps = (SOCK6 *)hSock;
    PBM_Pkt*    pPkt;
    IPV6HDR*    ptr_ipv6hdr;
    uint        IPv6HdrSize;
    UINT32      IPv6FlowLabel;

    /* Currently, we dont have support for extension headers.
     */
    IPv6HdrSize = IPv6HDR_SIZE;

    /* Allocate memory for the packet. */
    if (!(pPkt = NIMUCreatePacket(Payload + IPv6HdrSize)))
        return (0);

    /* Set the IpHdrLen to IPv6Header Size + Length of all IPv6 extn headers
     * This allows the TCP/UDP layer to offset correctly to copy over its
     * payload. 
     * Currently, we dont support extension header addition, so the IP Header
     * length is just 40 bytes (sizeof(IPV6HDR))
     */
    pPkt->IpHdrLen = IPv6HdrSize;

    /* Set the valid data to the required size of the payload */
    pPkt->ValidLen = Payload;

    /* Fill in IPv6 Header */
    ptr_ipv6hdr    = (IPV6HDR *)(pPkt->pDataBuffer + pPkt->DataOffset);
    ptr_ipv6hdr->VerTC         = 0x60;
    ptr_ipv6hdr->PayloadLength = (UINT16)htons(pPkt->ValidLen);

    /* If a valid socket handle was passed, fill in the IPv6 header 
     * based on the socket properties. */
    if (ps)
    {
        IPv6FlowLabel = ntohl(ps->FlowLabel);
        mmCopy((void *)&ptr_ipv6hdr->FlowLabel, (void *)&IPv6FlowLabel, sizeof(UINT8) * 3);
        ptr_ipv6hdr->HopLimit = ps->HopLimit;

        mmCopy((void *)&ptr_ipv6hdr->SrcAddr, (void *)&ps->LIP, sizeof(IP6N));
        mmCopy((void *)&ptr_ipv6hdr->DstAddr, (void *)&ps->FIP, sizeof(IP6N));

        /* Inherit the packet priority from the socket; since all packets
         * transmitted from a particular socket will have the same priority.*/
        pPkt->PktPriority = ps->SockPriority;
    }

    /* If no valid socket handle passed, fill in the IPv6 Header 
     * with defaults.
     */
    else
    {
        ptr_ipv6hdr->FlowLabel[0] = 0;
        ptr_ipv6hdr->FlowLabel[1] = 0;
        ptr_ipv6hdr->FlowLabel[2] = 0;
        ptr_ipv6hdr->HopLimit  = IPV6_UCAST_DEF_HOP_LIMIT;
        /*
         * NOTE: use mmCopy to copy the 16 byte IP6N addresses out of ptr_ipv6hdr
         * as this data is potentially un-aligned (SDOCM00097361)
         */
        mmCopy((void *)&ptr_ipv6hdr->SrcAddr, (void *)&IPV6_UNSPECIFIED_ADDRESS, sizeof(IP6N));
        mmCopy((void *)&ptr_ipv6hdr->DstAddr, (void *)&IPV6_UNSPECIFIED_ADDRESS, sizeof(IP6N));
    }

    /* No extension headers configured, so the next header of
     * IPv6 header is L4 type that has been passed to this 
     * function.
     */
    ptr_ipv6hdr->NextHeader = (UINT8)NextHeader;

    /* Successfully constructed the IPv6 Header of the packet. */
    return (pPkt);        
}

#endif /* _INCLUDE_IPv6_CODE */

