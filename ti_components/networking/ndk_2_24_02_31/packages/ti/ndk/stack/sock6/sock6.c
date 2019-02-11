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
 * ======== sock6.c ========
 *
 * The file implements the SOCK6 object which is the socket
 * library for IPv6.
 *
 */

#include <stkmain.h>
#include "sock6.h"
#include <socket.h>

#ifdef _INCLUDE_IPv6_CODE

static int joinGroup(HANDLE hSock, struct ipv6_mreq* mreq);
static int leaveGroup(HANDLE hSock, struct ipv6_mreq* mreq);

/**
 *  @b Description
 *  @n
 *      The function creates a new IPv6 Socket.
 *
 *  @param[in]  Family
 *      Socket Family. Only AF_INET6 is supported.
 *  @param[in]  Type
 *      The type of socket being created
 *          - SOCK_DGRAM : UDP Socket
 *          - SOCK_STREAM: TCP Socket
 *          - SOCK_RAW   : RAW Socket (TBD)
 *  @param[in]  Protocol
 *      Valid Values are 0, IPPROTO_UDP and IPPROTO_TCP.
 *  @param[in] RxBufSize
 *      Receive buffer size of the V6 Socket.
 *  @param[in] TxBufSize
 *      Transmit buffer size of the V6 Socket.
 *  @param[out] phSock
 *      Socket Handle which is returned.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   Non Zero
 */
int Sock6New( int Family, int Type, int Protocol, int RxBufSize, int TxBufSize, HANDLE *phSock)
{
    SOCK6* ps;

    /* Validate the arguments
     *  We support only the AF_INET6 Family */
    if( Family != AF_INET6 )
        return( EPFNOSUPPORT );

    /* Check the Socket Type. */
    if( Type == SOCK_DGRAM )
    {
        if( !Protocol )
            Protocol = IPPROTO_UDP;
        else if( Protocol != IPPROTO_UDP)
            return( EPROTOTYPE );
    }
    else if( Type == SOCK_STREAM)
    {
        if( !Protocol )
            Protocol = IPPROTO_TCP;
        else if( Protocol != IPPROTO_TCP )
            return( EPROTOTYPE );
    }
    else if( Type != SOCK_RAW )
        return( ESOCKTNOSUPPORT );

    /* Allocate memory for the V6 Socket. */
    if( !(ps = mmAlloc(sizeof(SOCK6))) )
    {
        NotifyLowResource();
        return ENOMEM;
    }

    /* Initialize the allocated block of memory. */
    mmZeroInit( ps, sizeof(SOCK6) );     /* Most Q's and counts init to Zero */

    /* Populate the data structure. */
    ps->fd.Type      = HTYPE_SOCK6;
    ps->fd.OpenCount = 1;
    ps->Family       = (uint)Family;       /* INET6 */
    ps->SockType     = (uint)Type;         /* STREAM, DGRAM or RAW */
    ps->Protocol     = (uint)Protocol;     /* IP protocol # or NULL */

    /* Initialize the V6 Specific Parameters. */
    ps->FlowLabel    = 0;
    ps->HopLimit     = IPV6_UCAST_DEF_HOP_LIMIT;
    ps->ScopeId      = 0;

    /* Initialize the default timeouts */
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
        ps->hSBRx = (HANDLE)SB6New( ps->RxBufSize, SOCK_BUFMINRX, SB_MODE_LINEAR );
    }
    else
    {
        ps->StateFlags = SS_ATOMICREAD | SS_ATOMIC;
        if( !ps->RxBufSize )
            ps->RxBufSize = SOCK_UDPRXLIMIT;
        ps->hSBRx = (HANDLE)SB6New( ps->RxBufSize, SOCK_BUFMINRX, SB_MODE_ATOMIC );
    }

    /* Make sure the memory was allocated. */
    if (!ps->hSBRx)
    {
        /* Error: Unable to allocate the Receive buffers; clean up and return error. */
        mmFree (ps);
        return ENOMEM;
    }

    /* Finalize Socket Status */
    if (Type == SOCK_STREAM)
    {
        ps->StateFlags |= SS_CONNREQUIRED;

        if( !ps->TxBufSize )
            ps->TxBufSize = SOCK_TCPTXBUF;

        /* Allocate memory for the transmit buffer. */
        ps->hSBTx = (HANDLE)SB6New( ps->TxBufSize, SOCK_BUFMINTX, SB_MODE_LINEAR );
        if (!ps->hSBTx)
        {
            SB6Free (ps->hSBRx);
            mmFree (ps);
            return ENOMEM;
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

    /* Add the Socket to the Socket List. */
    Sock6PrAttach (ps);

    /* Return the allocated socket handle */
    *phSock = (HANDLE)ps;
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function binds an address and port to the socket.
 *
 *  @param[in]  h
 *      Socket Handle passed.
 *  @param[in]  pName
 *      IPv6 Address and Port Information to which the socket will be bound.
 *
 *  @retval
 *      Success     -   0
 *  @retval
 *      Error       -   Non Zero
 */
int Sock6Bind( HANDLE h, PSA pName )
{
    SOCK6*  ps = (SOCK6 *)h;
    PSA_IN6 psa_in6 = (PSA_IN6)pName;
    IP6N    LocalIP;
    int     error;

    /* Extract the Local IP Address */
    mmCopy ((void *)&LocalIP, (void *)&psa_in6->sin6_addr, sizeof(IP6N));

    /* Bind the socket */
    error = Sock6PcbBind(ps, LocalIP, psa_in6->sin6_port);
    if (error == 0)
    {
        /* Set the Bind Address/Port. */
        ps->BIP   = ps->LIP;
        ps->BPort = ps->LPort;
    }

    /* Work has been done. */
    return error;
}

/**
 *  @b Description
 *  @n
 *      The function receives data from a socket.
 *
 *  @param[in]  h
 *      Socket Handle from where data has to be read.
 *  @param[in]  pBuf
 *      Data Buffer where data has to be copied after it is read from the socket.
 *  @param[in]  size
 *      Size of the data buffer passed.
 *  @param[in]  flags
 *      Flags
 *  @param[in]  pPeer
 *      Peer Information from where the packet was received.
 *  @param[in]  pRetSize
 *      Total number of data bytes actually received.
 *
 *  @retval
 *      Success     -   0
 *  @retval
 *      Error       -   Non Zero
 */
int Sock6Recv
(
    HANDLE      h,
    char*       pBuf,
    INT32       size,
    int         flags,
    PSA         pPeer,
    INT32*      pRetSize
)
{
    SOCK6*   ps = (SOCK6 *)h;
    int      read_again = 1;
    int      error      = 0;
    INT32    Total      = 0;
    INT32    SizeCopy   = 0;
    INT32    PeekOffset = 0;
    PSA_IN6  psa_Peerin6 = (PSA_IN6)pPeer;

    /* We dont receive data from a socket which is listening. */
    if( ps->OptionFlags & SO_ACCEPTCONN )
        return EINVAL;

    /* If the size of the data buffer is 0 or its not specified; we return
     * immediately. */
    if ((size == 0)|| (pBuf == NULL))
    {
        *pRetSize = 0;
         return 0;
    }

    /* Check the OOB flag */
    if( flags & MSG_OOB )
    {
        /* MSG_OOB Specified */

        /* If in OOBINLINE mode, this flag is illegal, or */
        /* If stocket is not in OOB mode, it is illegal */
        if( (ps->OptionFlags & SO_OOBINLINE) || !(ps->StateFlags & SS_OOBACTIVE) )
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
    Total = SB6GetTotal(ps->hSBRx) - PeekOffset;

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
        if( SizeCopy >= SB6GetMin(ps->hSBRx) && !(flags&MSG_WAITALL) )
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
            Total = SB6Read(ps->hSBRx, Total, PeekOffset, (UINT8 *)(pBuf+SizeCopy), psa_Peerin6, 1);

            /* Move the peek offet since we don't consume data from hSBRx */
            PeekOffset += Total;
        }
        else
        {
            Total = SB6Read( ps->hSBRx, Total, 0, (UINT8 *)(pBuf+SizeCopy), psa_Peerin6, 0 );
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

        /* We have already populated the PEER Information in the SB; here we fill up what
         * we cant do there. */
        if( psa_Peerin6 )
        {
            /* Get Peer Data from Socket */
            psa_Peerin6->sin6_family      = (UINT8)ps->Family;

            if((ps->StateFlags & SS_ADDR) == 0)
            {
                psa_Peerin6->sin6_port  = ps->FPort;
		        memcpy((void *)&psa_Peerin6->sin6_addr, (void *)&ps->FIP, sizeof(IP6N));
            }
        }

        /* Record that we received this data */
        SizeCopy += Total;

        /* Notify the protocol of status change */
        Sock6PrRecv( ps );

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

/**
 *  @b Description
 *  @n
 *      The function send data out from a socket.
 *
 *  @param[in]  h
 *      Socket Handle from where data has to be send out
 *  @param[in]  pBuf
 *      Data Buffer which contains the data to be sent out.
 *  @param[in]  size
 *      Size of the data buffer passed.
 *  @param[in]  flags
 *      Flags
 *  @param[in]  pRetSize
 *      Total number of data bytes actually sent out.
 *
 *  @retval
 *      Success     -   0
 *  @retval
 *      Error       -   Non Zero
 */
int Sock6Send
(
    HANDLE   h,
    char     *pBuf,
    INT32    size,
    int      flags,
    INT32    *pRetSize
)
{
    SOCK6*  ps = (SOCK6 *)h;
    int     DontRoute = 0, error = 0;
    INT32   SizeCopy = 0;
    INT32   AddCopy;

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

        /* Checking if we are sending OOB Data. */
        if( flags & MSG_OOB )
        {
            /* YES. Out of Band data is supported only for TCP. */
            if( ps->SockProt == SOCKPROT_TCP )
            {
                /* Pass the data to the TCP Out of Band Data Handler. */
                error = TCP6PrSendOOB ((HANDLE)ps, ps->hTP,
                                       (UINT8 *)(pBuf+SizeCopy),
                                       size-SizeCopy, &AddCopy );
            }
            else
            {
                /* Error: Invalid flag combination; report it. */
                error = EINVAL;
            }
        }
        else
        {
            /* OOB data was not being sent. Pass the data to the appropriate layer4
             * output handler. */
            if( ps->SockProt == SOCKPROT_UDP )
                error = Udp6Output( (HANDLE)ps, (UINT8 *)(pBuf+SizeCopy), size-SizeCopy, &AddCopy);
            else if( ps->SockProt == SOCKPROT_RAW )
                error = Raw6Output( (HANDLE)ps, (UINT8 *)(pBuf+SizeCopy), size-SizeCopy, &AddCopy);
            else if( ps->SockProt == SOCKPROT_TCP )
                error = TCP6PrSend( (HANDLE)ps, (HANDLE)ps->hTP, (UINT8 *)(pBuf+SizeCopy), size-SizeCopy, &AddCopy);
            else
                error = EINVAL;
        }

        /* Break out now on an error condition */
        if( error )
            break;

        if( DontRoute )
            ps->OptionFlags &= ~SO_DONTROUTE;

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

/**
 *  @b Description
 *  @n
 *      The function connects the socket.
 *
 *  @param[in]  h
 *      Socket Handle which is to be connected.
 *  @param[in]  pName
 *      Socket Address Information to which the socket will be connected.
 *
 *  @retval
 *      Success     -   0
 *  @retval
 *      Error       -   Non Zero
 */
int Sock6Connect( HANDLE h, PSA pName )
{
    SOCK6*          ps = (SOCK6 *)h;
    PSA_IN6         psa_in6 = (PSA_IN6)pName;
    int             error = 0;
    HANDLE          hRt = 0;
    IP6N            FIP;
    IP6N            LIP;
    NETIF_DEVICE*   ptr_device;
    IP6N            IPNet;

    /* If the socket is waiting for connections we cannot connect it... */
    if( ps->OptionFlags & SO_ACCEPTCONN )
        return EOPNOTSUPP;

    /* The socket can be connected only once. */
    if( ps->StateFlags & (SS_ISCONNECTED | SS_ISCONNECTING) )
    {
        /* If connection oriented, we have an error condition */
        if( ps->StateFlags & SS_CONNREQUIRED )
        {
            if( !(ps->StateFlags & SS_ISCONNECTED) )
                return EALREADY;
            else
                return EISCONN;
        }
        return EISCONN;
    }

    /* Extract and copy the Foreign IP. */
    mmCopy((void *)&FIP, (void *)&psa_in6->sin6_addr, sizeof(IP6N));

    /* If the Foreign IP is UNSPECIFIED; we dont support it. */
    if((IPv6CompareAddress(FIP, IPV6_UNSPECIFIED_ADDRESS) == 1))
        return EINVAL;

    /* Now we need to create the socket side LOCAL Bindings.
     * Check if the socket is bound to a LOCAL IP or not? */
    if((IPv6CompareAddress(ps->LIP, IPV6_UNSPECIFIED_ADDRESS) == 1))
    {
        /* The socket is NOT bound to a LOCAL Address. We need to
         * bind this to a correct local address which can be used.
         * The selection of a LOCAL IP Depends on the FOREIGN IP
         * to which the packet will be sent.
         *
         * Check if the FIP is a LINK Local Address? */
        if ((IPv6IsMulticast(FIP) == 1) || (IPv6IsLinkLocal(FIP) == 1))
        {
            /* YES. We use the scope id to get the interface. */
            ptr_device = NIMUFindByIndex (psa_in6->sin6_scope_id);
            if (ptr_device == NULL)
                return EINVAL;

            /* Once we have a valid scope-id to which the packet needs to
             * be sent out; we check if there exists a BIND6 Object for the
             * Interface. If none exists then this index does not have V6
             * enabled. */
            if (Bind6GetLinkLocalAddress(ptr_device, &LIP) < 0)
                return -1;

            if (!IPv6IsMulticast(FIP))
            {
                /* Use the routing table for a match. */
                hRt = Rt6Find(FLG_RTE_HOST | FLG_RTE_CLONING | FLG_RTE_GATEWAY | FLG_RTF_CLONE, FIP, ptr_device);
                if (hRt == 0)
                    return EHOSTUNREACH;
            }
        }
        else
        {
            /* OK; the address was not link local. Is the address the loopback address? */
            if (IPv6CompareAddress(FIP, IPV6_LOOPBACK_ADDRESS) == 1)
            {
                /* This is a loopback address; we can use any address here since the packet
                 * will never leave the box. */
                LIP = IPV6_LOOPBACK_ADDRESS;

                /* We find only the Local Host Route. */
                hRt = Rt6Find(FLG_RTE_HOST | FLG_RTE_IFLOCAL, FIP, NULL);
                if (hRt == 0)
                    return EHOSTUNREACH;
            }
            else
            {
                /* This is a GLOBAL Address to which the packet is being routed.
                 * Use the Routing Table here to determine the ROUTE6 handle. */
                hRt = Rt6Find (FLG_RTE_HOST | FLG_RTE_CLONING | FLG_RTE_GATEWAY | FLG_RTF_CLONE, FIP, NULL);
                if (hRt == 0)
                    return EHOSTUNREACH;

                /* Get the network device associated with the ROUTE */
                ptr_device = Rt6GetIF(hRt);

                /* If we are using default route, find the first global address
                 * found matching the device.
                 */
                if (Rt6IsDefaultRoute(hRt))
                {
                    /* Set the Network Mask to be zero. */
                    mmZeroInit((void *)&IPNet, sizeof(IP6N));
                }
                else
                {
                    /* Get the Network Address associated with this route. */
                    Rt6GetNetworkAddr(hRt, &IPNet);
                }

                /* Use one of the GLOBAL Addresses associated with the Device */
                if (Bind6GetGlobalAddress(ptr_device, IPNet, &LIP) < 0)
                {
                    /* There exists no GLOBAL Address on the interface. Yet the ROUTING Table uses this
                     * interface for a default gateway.
                     */
                     return EINVAL;
                }
            }
        }

        /* Bind the socket now; if there is an error return the code. */
        error = Sock6PcbBind (h, LIP, 0);
        if (error != 0)
            return error;
    }
    else
    {
        /* OK; the socket was bound to a Local IP Address. */
        HANDLE hBindObj;

        /* Check the Local IP if it is Loopback or not? */
        if (IPv6CompareAddress(ps->LIP, IPV6_LOOPBACK_ADDRESS) == 1)
        {
            /* YES. This is a loopback address. Get a matching route */
            hRt = Rt6Find(FLG_RTE_HOST | FLG_RTE_IFLOCAL, FIP, NULL);
            if (hRt == 0)
                return EHOSTUNREACH;
        }
        else
        {
            /* NO: Not a loopback address; Get the Binding object associated with the Local IP Address. */
            hBindObj = Bind6FindByHost(NULL, ps->LIP);
            if (hBindObj == 0)
            {
                /* This is an error; we were bound to an IP Address which does not exist
                 * in the global IPv6 system binding. */
                return EINVAL;
            }

            /* Get the Interface handle associated with the Binding Object */
            ptr_device = Bind6GetInterfaceHandle (hBindObj);

            if (!IPv6IsMulticast(FIP))
            {
                /* Now we need to search the routing table for a match. */
                hRt = Rt6Find(FLG_RTE_HOST | FLG_RTE_CLONING | FLG_RTE_GATEWAY | FLG_RTF_CLONE, FIP, ptr_device);
                if (hRt == 0)
                    return EHOSTUNREACH;
            }
        }
    }

    /* Ensure that the Local IP/Port, Foreign IP/Port combination is unique in the system. */
    if( (error = Sock6PcbConnect( h, FIP, psa_in6->sin6_port )) )
        return error;

    if (!IPv6IsMulticast(FIP))
    {
        /* By the time control comes here we know the following:-
         *  a) Route Exists to the destination.
         *  b) Bindings (LIP, LPort, FIP, FPort) are unique
         * Check if there exists a ROUTE already associated with the socket?
         * If one exists we simply drop reference to it. */
        if (ps->hRoute6 != 0)
            Rt6Free (ps->hRoute6);

        /* Cache the new route instead. */
        Rt6IncRefCount (hRt);
        ps->hRoute6 = hRt;
    }

    /* Make sure these are clear */
    ps->StateFlags &= ~(SS_CANTRCVMORE | SS_CANTSENDMORE);

    /* For UDP Sockets; we are connected at this stage and dont need to do anything else. */
    if( (ps->StateFlags & SS_CONNREQUIRED) == 0)
    {
        /* Easy case - just set to ISCONNECTED */
        ps->StateFlags |= SS_ISCONNECTED;
        return 0;
    }

    /* Set ISCONNECTING flag (ISCONNECTED set via Sock6Notify) */
    ps->StateFlags |= SS_ISCONNECTING;

    /* Establish the protocol connection */
    error = Sock6PrConnect( ps );

    /* If no error and not connected and not non-blocking, we wait */
    while( !error && !ps->ErrorPending && !(ps->StateFlags & (SS_NBIO|SS_ISCONNECTED)) )
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
        Sock6PrDisconnect( ps );
    }
    /* Else check to see if we should return EINPROGRESS for NBIO */
    else if( !(ps->StateFlags & SS_ISCONNECTED) )
        error = EINPROGRESS;

    return( error );
}

/**
 *  @b Description
 *  @n
 *      The function cleans up the internal memory for the V6 Socket.
 *
 *  @param[in]  ps
 *      Pointer to the SOCK6 Object which will be cleaned up.
 *
 *  @retval
 *      Not Applicable.
 */
void Sock6IntAbort(SOCK6 *ps)
{
    /* Remove the socket from the global socket family list. */
    Sock6PrDetach( ps );

    /* Remove any cached ROUTE6 references. */
    if (ps->hRoute6 != 0)
        Rt6Free (ps->hRoute6);

    /* Clean out the cached routes. */
    ps->hRoute6 = 0;

    /* Free the Rx and Tx Buffers */
    if( ps->hSBRx )
        SB6Free( ps->hSBRx );
    if( ps->hSBTx )
        SB6Free( ps->hSBTx );

    /* Free the sock memory */
    ps->fd.Type = 0;
    mmFree( ps );
    return;
}

/**
 *  @b Description
 *  @n
 *      The function closes an IPv6 Socket.
 *
 *  @param[in]  h
 *      Socket Handle which is to be closed.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   Non Zero
 */
int Sock6Close( HANDLE h )
{
    SOCK6 * ps = (SOCK6 *)h;
    MCAST_SOCK_REC6 * mcast_rec;
    int error;

    /* Leave all multicast groups this socket has joined */
    while ((mcast_rec = (MCAST_SOCK_REC6 *)list_get_head(
                (LIST_NODE **)&ps->pMcastList))) {

        /* leaveGroup deletes the entry from the list */
        leaveGroup(h, &mcast_rec->mreq);
    }

    /* Check if the socket is CONNECTION Oriented or not? */
    if((ps->StateFlags & SS_CONNREQUIRED) == 0)
    {
        /* Non-Connection Oriented socket: Simply close the socket. */
        Sock6IntAbort (ps);
        return 0;
    }

    /* Control comes here implies that the socket is a CONNECTION Oriented socket
     * Check if the socket state is accepting connections? */
    if( ps->OptionFlags & SO_ACCEPTCONN )
    {
        SOCK6* psTemp;

        /* If the socket accepting connections is being closed; we flush
         * out any connections which reside in the PENDING queue (SPAWNED)
         * socket connections which have still not been moved to the READY
         * queue. These are connections which have been SPAWNED but not yet
         * been connected */
        while (ps->pPending)
        {
            /* Dequeue the socket */
            psTemp = ps->pPending;
            ps->pPending = psTemp->pPending;
            if( ps->pPending )
                ps->pPending->pPrevQ = ps;
            psTemp->StateFlags &= ~SS_PENDINGQ;

            /* Close the enqueued PENDING socket */
            Sock6IntAbort (psTemp);
        }

        /* If the socket accepting connections has been closed; we
         * close all sockets which are in the READY queue. These are connections
         * which have been SPAWNED and CONNECTED but not picked up by the application
         * through the 'accept' call. */
        while (ps->pReady)
        {
            /* Dequeue the socket */
            psTemp = ps->pReady;
            ps->pReady = psTemp->pReady;
            if( ps->pReady )
                ps->pReady->pPrevQ = ps;
            psTemp->StateFlags &= ~SS_READYQ;

            /* Close the enqueued READY socket */
            Sock6IntAbort (psTemp);
        }

        /* Reset the counters; since now there are no more pending sockets. */
        ps->ConnTotal = 0;
    }

    /* Check if the socket is connected? */
    if( ps->StateFlags & SS_ISCONNECTED )
    {
        /* YES; it is shutdown the READ Pipe. */
        Sock6Shutdown( ps, SHUT_RD );

        /* Check if the LINGER option is set or not? */
        if((ps->OptionFlags & SO_LINGER) == 0)
        {
            /* Linger option is NOT Set; indicate that the socket is CLOSING. */
            ps->StateFlags |= SS_CLOSING;

            /* Start the TCP Disconnect state machine. */
            return Sock6PrDisconnect(ps);
        }

        /* Set the flag indicating that this is a LINGERING socket. */
        ps->StateFlags |= SS_LINGERING;

        /* Start the TCP Disconnect state machine. */
        error = Sock6PrDisconnect( ps );
        if( error )
        {
            /* If an error is detected; then we simply close and return from here. */
            Sock6IntAbort (ps);
            return 0;
        }

        /* Check if this is a NON Blocking socket? */
        if( ps->StateFlags & SS_NBIO )
        {
            /* Lingering option is not supported in this mode; simply close and return */
            Sock6IntAbort (ps);
            return 0;
        }

        /* Check if the Lingering timeout has been specified? */
        if(ps->dwLingerTime == 0)
        {
            /* No Lingering timeout has been specified; simply close and return. */
            Sock6IntAbort (ps);
            return 0;
        }

        /* We need to wait now till either of the following events to take place:-
         *  a) Disconnect State Machine Executes and a Sock6Notify is invoked with a DISCONNECT event.
         *  b) Lingering Timeout takes place */
        while( ps->StateFlags & SS_LINGERING )
        {
            /* If we ever timeout (Return value of 0), break out of this loop. */
            if( !FdWaitEvent( ps, FD_EVENT_READ, ps->dwLingerTime ) )
                break;
        }
    }

    /* Close the socket */
    Sock6IntAbort (ps);
    return (0);
}

/**
 *  @b Description
 *  @n
 *      The function disconnects an IPv6 Socket. This is not the same as
 *      close; since the socket is not cleaned up.
 *
 *  @param[in]  h
 *      Socket Handle which is to be disconnected.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   Non Zero
 */
int Sock6Disconnect(HANDLE h)
{
    SOCK6 *ps = (SOCK6 *)h;

    /* We dont Disconnect Connection Oriented sockets. */
    if( ps->StateFlags & SS_CONNREQUIRED )
        return( EINVAL );

    /* We can disconnect only if the socket has already been connected. */
    if( !(ps->StateFlags & (SS_ISCONNECTED | SS_ISCONNECTING)) )
        return( ENOTCONN );

    /* Set the flags appropriatetly. */
    ps->StateFlags &= ~(SS_ISCONNECTING|SS_ISCONNECTED|SS_CLOSING);

    /* Move back to the original Bindings. */
    ps->LIP   = ps->BIP;
    ps->LPort = ps->BPort;
    ps->FIP   = IPV6_UNSPECIFIED_ADDRESS;
    ps->FPort = 0;

    /* Remove any cached ROUTE6 references. */
    if (ps->hRoute6 != 0)
        Rt6Free (ps->hRoute6);

    /* Clean out the cached routes. */
    ps->hRoute6 = 0;
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is called to determine if there is any operation
 *      pending on the socket.
 *
 *  @param[in]  h
 *      Socket Handle which needs to be checked.
 *  @param[in]  IoType
 *      Type of operation which is pending.
 *
 *  @retval
 *      1 -   Operation is pending
 *  @retval
 *      0 -   Operation is not pending
 */
int Sock6Check( HANDLE h, int IoType )
{
    SOCK6* ps = (SOCK6 *)h;

    /* Process depending on the type passed. */
    switch( IoType )
    {
        case SOCK_READ:
        {
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
                if( SB6GetTotal(ps->hSBRx) >= SB6GetMin(ps->hSBRx) )
                    return(1);
            }
            break;
        }
        case SOCK_WRITE:
        {
            /* Return TRUE if writeable */

            /* Simply return TRUE for the following error cases */
            /* - Listening sockets (can not be written) */
            /* - Error pending sockets */
            /* - When shutdown for write */
            if( (ps->OptionFlags & SO_ACCEPTCONN) || ps->ErrorPending || (ps->StateFlags & SS_CANTSENDMORE) )
                return(1);

            /* Also return true if connected and can write */
            if( !(ps->StateFlags & SS_CONNREQUIRED) ||
                 (ps->StateFlags & SS_ISCONNECTED)  )
            {
                /* Writable "connected" cases */
                if( (ps->StateFlags & SS_ATOMICWRITE) || (SB6GetSpace(ps->hSBTx) >= SB6GetMin(ps->hSBTx)) )
                    return(1);
            }
            break;
        }
        case SOCK_EXCEPT:
        {
            /* Return TRUE if OOB data present, shutdown, or pending error */
            if( ps->StateFlags & SS_OOBACTIVE || ps->StateFlags & SS_CANTRCVMORE || ps->ErrorPending )
                return(1);
            break;
        }
    }
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function returns the socket status.
 *
 *  @param[in]  h
 *      Socket Handle which needs to be checked.
 *  @param[in]  request
 *      Type of request
 *  @param[out] results
 *      Result buffer which has the result of the request.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   Non Zero
 */
int Sock6Status( HANDLE h, int request, int *results )
{
    SOCK6 *ps = (SOCK6 *)h;

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
                *results = (int)SB6GetTotal( ps->hSBRx );
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
            if( ps->hRoute6 )
            {
                tmp = Rt6GetMTU( ps->hRoute6 );
            }
            else
                tmp = 1500;

            /* Sub off any auto-generated IP header. */
            /* This doesnt include any extension headers */
            /* at the moment. */
            tmp -= Sock6GetIpHdrSize( ps );

            /* Sub off any UDP header */
            if( ps->SockType == SOCK_DGRAM )
                tmp -= UDPHDR_SIZE;

            *results = tmp;
        }
        else if( ps->hSBTx )
            *results = SB6GetSpace(ps->hSBTx);
        else
            *results = 0;
    }
    else
        return( EINVAL );

    return(0);
}

/**
 *  @b Description
 *  @n
 *      The function shuts down the V6 socket.
 *
 *  @param[in]  h
 *      Socket Handle which is to be shutdown.
 *  @param[out] how
 *      -  SHUT_RD: Closes the Read  pipe of the socket
 *      -  SHUT_WR: Closes the Write pipe of the socket
 *      -  SHUT_RDWR: Closes both the Read & Write pipes.
 *
 *  @retval
 *      Always returns 0.
 */
int Sock6Shutdown(HANDLE h, int how)
{
    SOCK6*  ps = (SOCK6 *)h;

    /* Do we need to close the read pipe? */
    if ((how == SHUT_RD) || (how == SHUT_RDWR))
    {
        /* Set the socket state flag indicating no more data can be received. */
        ps->StateFlags |= SS_CANTRCVMORE;

        /* If the socket is operating in listening mode we dont need to
         * do anything since there is NO READ pipe associated with it. We closed
         * it as soon as we did the 'listen'. */
        if ((ps->OptionFlags & SO_ACCEPTCONN) == 0)
        {
            /* Not an ACCEPTING socket; shutdown the READ pipe. */
            if( ps->hSBRx )
                SB6Flush( ps->hSBRx, 1 );

            /* Notify the protocol of status change; this is a NOOP for UDP, RAW
             * sockets; but for TCP sockets this can be used to send out a zero
             * window advertisement. */
            Sock6PrRecv (ps);
        }

        /* Notify the socket of status change */
        FdSignalEvent( ps, FD_EVENT_READ|FD_EVENT_EXCEPT );
    }

    /* Do we need to close the write pipe? */
    if ((how == SHUT_WR) || (how == SHUT_RDWR))
    {
        /* Set the flag indicating data cannot be sent out on this socket. */
        ps->StateFlags |= SS_CANTSENDMORE;

        /* If the socket is operating in listening mode we dont need to
         * do anything since there is NO WRITE pipe associated with it. We closed
         * it as soon as we did the 'listen'. */
        if( ps->OptionFlags & SO_ACCEPTCONN )
            return 0;

        /* If the socket is connection oriented, we should tell the
         * peer that we're done sending data. */
        if( ps->StateFlags & SS_CONNREQUIRED )
            Sock6PrDisconnect (ps);

        /* Notify the socket of status change */
        FdSignalEvent( ps, FD_EVENT_WRITE );
    }

    /* Work has been done. */
    return(0);
}

/**
 *  @b Description
 *  @n
 *      The function gets information about the Local and Peer to
 *      which the socket has been connected.
 *
 *  @param[in]  h
 *      Socket Handle for which the information is required.
 *  @param[out] pSockName
 *      Local Information is populated in this.
 *  @param[out] pPeerName
 *      Peer Information is populated in this.
 *
 *  @retval
 *      Always returns 0.
 */
int Sock6GetName( HANDLE h, PSA pSockName, PSA pPeerName)
{
    SOCK6 *ps = (SOCK6 *)h;
    PSA_IN6 psa_Localin6 = (PSA_IN6)pSockName;
    PSA_IN6 psa_Peerin6 = (PSA_IN6)pPeerName;

    /* Populate the local information if required. */
    if( psa_Localin6 )
    {
        psa_Localin6->sin6_family      = (UINT8)ps->Family;
        psa_Localin6->sin6_port        = ps->LPort;
        mmCopy((void *)&psa_Localin6->sin6_addr, (void *)&ps->LIP, sizeof(UINT32) * 4);
    }

    /* Populate the local information if required. */
    if( psa_Peerin6 )
    {
        psa_Peerin6->sin6_family      = (UINT8)ps->Family;
        psa_Peerin6->sin6_port        = ps->FPort;
        mmCopy((void *)&psa_Peerin6->sin6_addr, (void *)&ps->FIP, sizeof(UINT32) * 4);
    }
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function listens on STREAM sockets waiting for connections
 *      to arrive
 *
 *  @param[in]  h
 *      Socket Handle on which connections are being listened for.
 *  @param[in] maxcon
 *      Maximum number of connections that can be accepted.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   Non Zero
 */
int Sock6Listen( HANDLE h, int maxcon )
{
    SOCK6 *ps = (SOCK6 *)h;
    int  error = 0;

    /* The Listen API is valid only for Connection Oriented sockets */
    if( (ps->StateFlags & SS_CONNREQUIRED) == 0)
        return( EOPNOTSUPP );

    /* The socket cant already be connected or in the process of connecting to another host. */
    if( ps->StateFlags & (SS_ISCONNECTED | SS_ISCONNECTING) )
        return( EISCONN );

    /* Clean up the internal resources which TCP holds. */
    error = TCP6PrListen ((HANDLE)ps, ps->hTP);
    if(error == 0)
    {
        /* Now we clean up the socket internals.
         *  Mark the socket so that we know it accepts connections. */
        ps->OptionFlags |= SO_ACCEPTCONN;

        /* Clean up the socket buffers; the socket can no longer be used
         * for reception or transmission. */
        if( ps->hSBRx )
            SB6Free( ps->hSBRx );
        if( ps->hSBTx )
            SB6Free( ps->hSBTx );
        ps->hSBRx = ps->hSBTx = 0;

        /* Set the maximum number of connections which can be accepted. */
        if( maxcon < 0 )
            maxcon = 0;
        if( maxcon > SOCK_MAXCONNECT )
            maxcon = SOCK_MAXCONNECT;
        ps->ConnMax = maxcon;
    }
    return error;
}

/**
 *  @b Description
 *  @n
 *      The function accepts connections on a socket which is listening
 *      for connections to arrive.
 *
 *  @param[in]  h
 *      Socket Handle which is listening for connections.
 *  @param[out] phSock
 *      Socket Handle which is created after accepting the connection.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   Non Zero
 */
int Sock6Accept( HANDLE h, HANDLE *phSock )
{
    SOCK6*  ps = (SOCK6 *)h;
    SOCK6*  psRet;
    int     error = 0;

    /* The socket should be waiting for connections i.e. should have already
     * executed the 'listen' API. If not then this is an invalid operation. */
    if( !(ps->OptionFlags & SO_ACCEPTCONN) )
        return EINVAL;

    /* Loop around forever; waiting for a connection to arrive. */
    while (1)
    {
        /* If there are any errors pending on the listening socket; return
         * immediately with the appropriate error code. */
        if( ps->ErrorPending )
        {
            error = ps->ErrorPending;
            ps->ErrorPending = 0;
            return error;
        }

        /* If the listening socket has been shutdown, return immediately
         * with the appropriate error code. */
        if( ps->StateFlags & SS_CANTRCVMORE )
            return ECONNABORTED;

        /* Check if there are any connections which have arrived. */
        if (ps->pReady)
        {
            /* Got one; remove this from the ready list */
            psRet = ps->pReady;
            ps->pReady = psRet->pReady;
            if( ps->pReady )
                ps->pReady->pPrevQ = ps;
            psRet->pReady  = 0;
            psRet->pParent = 0;
            psRet->StateFlags &= ~SS_READYQ;

            /* We can accept more connections now. */
            ps->ConnTotal--;

            /* Return its handle to the callee. */
            *phSock = (HANDLE)psRet;
            return 0;
        }

        /* If we are operating in NON Blocking mode indicate to the callee
         * that since there were no connections available this would be blocking. */
        if(ps->StateFlags & SS_NBIO)
            return EWOULDBLOCK;

        /* Wait forever (until wake) */
        if( !FdWaitEvent( ps, FD_EVENT_READ, 0 ) )
            return EWOULDBLOCK;
    }
}

/**
 *  @b Description
 *  @n
 *      The function is used to set the socket parameters
 *
 *  @param[in]   hSock
 *      Handle to the socket.
 *  @param[in]  Type
 *      Socket Level which is to be configured.
 *          - SOL_SOCKET:   Socket Properties
 *          - IPPROTO_TCP:  TCP Properties
 *          - IPPROTO_IPV6: IPv6 Properties
 *  @param[in]  Prop
 *      The Property which needs to be configured.
 *  @param[in]  pbuf
 *      Data buffer where the value of property is present
 *  @param[in]  size
 *      Size of the Data buffer
 *
 *  @retval
 *     Success  -   0
 *  @retval
 *     Error    -   Non Zero
 */
int Sock6Set(HANDLE hSock, int Type, int Prop, void *pbuf, int size)
{
    SOCK6* ps = (SOCK6 *)hSock;
    int    value,error = 0;

    /* Basic validations: Before we proceed further. */
    if( size && !pbuf )
        return EINVAL;

    /* Check if the request is for SOCKET, TCP or IPv6 properties? */
    if( Type != SOL_SOCKET )
    {
        /* Check if we are handling the TCP Options. */
        if( Type == IPPROTO_TCP )
        {
            /* TCP Options can only be configured if the socket is TCP. */
            if( ps->SockProt == SOCKPROT_TCP )
                return( TCP6PrSetOption( hSock, ps->hTP, Prop, pbuf, size ) );

            /* The socket was not TCP; this is an invalid operation. */
            return EINVAL;
        }

        /* Check if we are configuring the IPv6 Options. */
        if( Type == IPPROTO_IPV6 )
        {
            int status = 0;
            /* Process the IPv6 Options. */
            switch( Prop )
            {
                case IPV6_UNICAST_HOPS:
                {
                    /* Validate the size. */
                    if( size != sizeof(int) )
                        return EINVAL;

                    /* Get the current hop limit. */
                    value = *(int *)pbuf;

                    /* Set the hop limit in the socket. */
                    if (value < -1 || value > 255)
                        return EINVAL;
                    else if (value == -1)
                        ps->HopLimit = IPV6_UCAST_DEF_HOP_LIMIT;
                    else
                        ps->HopLimit = (uint)value;
                    break;
                }

                case IPV6_JOIN_GROUP:
                case IPV6_LEAVE_GROUP:
                {
                    struct ipv6_mreq * mreq;

                    if (size != sizeof(struct ipv6_mreq)) {
                        DbgPrintf(DBG_INFO,
                                "Sock6Set: invalid size arg for JOIN/LEAVE\n");
                        return EINVAL;
                    }

                    mreq = (struct ipv6_mreq *)pbuf;
                    if (!IPv6IsMulticast(_IPv6_a2i(mreq->ipv6mr_multiaddr))) {
                        DbgPrintf(DBG_INFO,
                                "Sock6Set: not multicast address JOIN/LEAVE\n");
                        return EINVAL;
                    }

                    if (Prop == IPV6_JOIN_GROUP) {
                        status = joinGroup(hSock, mreq);
                    }
                    else {
                        status = leaveGroup(hSock, mreq);
                    }

                    break;
                }

                default:
                {
                    /* Currently no other option is supported. */
                    return EINVAL;
                }
            }

            /* IPv6 options have been successfully configured. */
            return status;
        }
        else
        {
            /* Invalid Type specified. */
            return EINVAL;
        }
    }

    /* Control comes here if TYPE was SOCKET. Process the options.
     * We first start with the STRUCTURE based options. */
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
            return 0;
        }
    }

    /* For the remainder, the property value is an int */
    if( size < sizeof(int) )
        return( EINVAL );
    value = *(int *)pbuf;

    /* Process the options. */
    switch( Prop )
    {
        case SO_BLOCKING:
        {
            if( value )
                ps->StateFlags &= ~SS_NBIO;
            else
                ps->StateFlags |= SS_NBIO;
            break;
        }

        case SO_DEBUG:
        case SO_KEEPALIVE:
        case SO_DONTROUTE:
        case SO_USELOOPBACK:
        case SO_BROADCAST:
        case SO_REUSEADDR:
        case SO_REUSEPORT:
        case SO_OOBINLINE:
        case SO_TIMESTAMP:
        {
            if( value )
                ps->OptionFlags |= (uint)Prop;
            else
                ps->OptionFlags &= (uint)~Prop;
            break;
        }
        case SO_SNDBUF:
        {
            if( ps->hSBTx && SB6SetMax(ps->hSBTx,value)!=value )
                error = EINVAL;
            else
                ps->TxBufSize = value;
            break;
        }
        case SO_RCVBUF:
        {
            if( ps->hSBRx && SB6SetMax(ps->hSBRx,value)!=value )
                error = EINVAL;
            else
                ps->RxBufSize = value;
            break;
        }
        case SO_SNDLOWAT:
        {
            if( ps->hSBTx )
                SB6SetMin( ps->hSBTx, value );
            break;
        }
        case SO_RCVLOWAT:
        {
            if( ps->hSBRx )
                SB6SetMin( ps->hSBRx, value );
            break;
        }
        case SO_ERROR:
        {
            ps->ErrorPending = value;
            break;
        }
        default:
        {
            error = ENOPROTOOPT;
            break;
        }
    }

    return(error);
}

/**
 *  @b Description
 *  @n
 *      The function is used to get the socket parameters
 *
 *  @param[in]   hSock
 *      Handle to the socket.
 *  @param[in]  Type
 *      Socket Level which is to be configured.
 *          - SOL_SOCKET:   Socket Properties
 *          - IPPROTO_TCP:  TCP Properties
 *          - IPPROTO_IPV6: IPv6 Properties
 *  @param[in]  Prop
 *      The Property which needs to be configured.
 *  @param[out] pbuf
 *      Data buffer where the value of property will be stored.
 *  @param[out] psize
 *      Size of the Data buffer
 *
 *  @retval
 *     Success  -   0
 *  @retval
 *     Error    -   Non Zero
 */
int Sock6Get(HANDLE hSock, int Type, int Prop, void *pbuf, int *psize)
{
    SOCK6 *ps = (SOCK6 *)hSock;
    int  error = 0;

    /* Basic validations: Before we proceed further. */
    if( !psize || !pbuf )
        return( EINVAL );

    /* Check if the request is for SOCKET, TCP or IPv6 properties? */
    if( Type != SOL_SOCKET )
    {
        /* Check if the request is for TCP or IPv6 properties? */
        if( Type == IPPROTO_TCP )
        {
            /* TCP Requests can only be handled if the socket is TCP. */
            if( ps->SockProt == SOCKPROT_TCP )
                return TCP6PrGetOption (hSock, ps->hTP, Prop, pbuf, psize);
            return EINVAL;
        }

        /* Check if the request is for IPv6 properties? */
        if( Type == IPPROTO_IPV6 )
        {
            switch( Prop )
            {
                default:
                {
                    /* Currently no property option is supported. */
                    return EINVAL;
                }
            }
        }

        /* Control comes here; implies that an invalid type was specified. */
        return EINVAL;
    }

    /* Control comes here if the request is for SOCKET properties.
     * First handle all properties which are structure based. */
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
        case SO_PRIORITY:
        {
            if( *psize != sizeof(UINT16))
                return( EINVAL );
            *psize = sizeof(UINT16);
            *(UINT16 *)pbuf = ps->SockPriority;
            break;
        }
    }

    /* For the remainder, the property value is an integer;
     * validate the arguments here. */
    if( *psize < sizeof(int) )
        return( EINVAL );
    *psize = sizeof(int);

    switch( Prop )
    {
        case SO_BLOCKING:
        {
            if( ps->StateFlags & SS_NBIO )
                *(int *)pbuf = 0;
            else
                *(int *)pbuf = 1;
            break;
        }
        case SO_DEBUG:
        case SO_KEEPALIVE:
        case SO_DONTROUTE:
        case SO_USELOOPBACK:
        case SO_BROADCAST:
        case SO_REUSEADDR:
        case SO_REUSEPORT:
        case SO_OOBINLINE:
        case SO_TIMESTAMP:
        {
            if( ps->OptionFlags & (uint)Prop )
                *(int *)pbuf = 1;
            else
                *(int *)pbuf = 0;
            break;
        }
        case SO_SNDBUF:
        {
            *(int *)pbuf = ps->TxBufSize;
            break;
        }
        case SO_RCVBUF:
        {
            *(int *)pbuf = ps->RxBufSize;
            break;
        }
        case SO_SNDLOWAT:
        {
            if( ps->hSBTx )
                *(int *)pbuf = (int)SB6GetMin( ps->hSBTx );
            else
                *(int *)pbuf = SOCK_BUFMINRX;
            break;
        }
        case SO_RCVLOWAT:
        {
            if( ps->hSBRx )
                *(int *)pbuf = (int)SB6GetMin( ps->hSBRx );
            else
                *(int *)pbuf = SOCK_BUFMINRX;
            break;
        }
        case SO_ERROR:
        {
            *(int *)pbuf = ps->ErrorPending;
            ps->ErrorPending = 0;
            break;
        }
        case SO_TYPE:
        {
            *(int *)pbuf = (int)ps->SockType;
            break;
        }
        default:
        {
            error = ENOPROTOOPT;
            break;
        }
    }
    return(error);
}

/**
 *  @b Description
 *  @n
 *      The function is called from the setsockopt to join a multicast
 *      group using the MLD module.
 *
 *  @param[in]  hSock
 *      Handle to the socket on which the multicast group is being joined.
 *  @param[in]  mreq
 *      Multicast Request structure populated by the application which
 *      contains the Multicast group address and the interface
 *      on which the group is being joined.
 *
 *  @retval
 *   0          -   Success
 *  @retval
 *   Non Zero   -   Error
 */
static int joinGroup(HANDLE hSock, struct ipv6_mreq * mreq)
{
    MCAST_SOCK_REC6 * mcast_rec;
    SOCK6 * s = (SOCK6 *)hSock;
    NETIF_DEVICE * net_device;

    if ((net_device = NIMUFindByIndex(mreq->ipv6mr_interface)) == NULL) {
        return (EINVAL);
    }

    /*
     * Check for duplicates - if the multicast group has already been
     * joined then no need to do anything.
     */
    mcast_rec = (MCAST_SOCK_REC6 *)list_get_head((LIST_NODE**)&s->pMcastList);
    while (mcast_rec != NULL) {
        if (IPv6CompareAddress(_IPv6_a2i(mcast_rec->mreq.ipv6mr_multiaddr),
                               _IPv6_a2i(mreq->ipv6mr_multiaddr))) {

            return (0);
        }
        mcast_rec = (MCAST_SOCK_REC6 *)list_get_next((LIST_NODE*)mcast_rec);
    }

    if ((mcast_rec = mmAlloc(sizeof(MCAST_SOCK_REC6))) == NULL) {
        NotifyLowResource();
        return (ENOMEM);
    }

    mmCopy(&mcast_rec->mreq, mreq, sizeof(struct ipv6_mreq));
    mcast_rec->hIf = net_device;

    if (MLDJoinGroup(net_device, _IPv6_a2i(mreq->ipv6mr_multiaddr)) != 0) {
        DbgPrintf(DBG_INFO, "joinGroup: MLDJoinGroup failed\n");
        mmFree(mcast_rec);
        return (ENOBUFS);
    }

    /* Once the group has been successfully joined add it to the socket list */
    list_add((LIST_NODE **)&s->pMcastList, (LIST_NODE *)mcast_rec);

    /* Group has been joined successfully. */
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is called from the setsockopt to leave a multicast
 *      group.
 *
 *  @param[in]  hSock
 *      Handle to the socket on which the multicast group is leaving.
 *  @param[in]  mreq
 *      Multicast Request structure populated by the application which
 *      contains the Multicast group address and the interface
 *      on which the group will be left.
 *
 *  @retval
 *   0          -   Success
 *  @retval
 *   Non Zero   -   Error
 */
static int leaveGroup(HANDLE hSock, struct ipv6_mreq * mreq)
{
    MCAST_SOCK_REC6 * mcast_rec;
    SOCK6 * s = (SOCK6 *)hSock;

    /* Search the socket list for a match */
    mcast_rec = (MCAST_SOCK_REC6 *)list_get_head((LIST_NODE**)&s->pMcastList);
    while (mcast_rec != NULL) {
        if (IPv6CompareAddress(_IPv6_a2i(mcast_rec->mreq.ipv6mr_multiaddr),
                               _IPv6_a2i(mreq->ipv6mr_multiaddr))) {

            MLDLeaveGroup(mcast_rec->hIf, _IPv6_a2i(mreq->ipv6mr_multiaddr));

            list_remove_node((LIST_NODE **)&s->pMcastList, (LIST_NODE* )mcast_rec);
            mmFree(mcast_rec);

            return 0;
        }

        mcast_rec = (MCAST_SOCK_REC6 *)list_get_next ((LIST_NODE*)mcast_rec);
    }

    return (EADDRNOTAVAIL);
}

#endif /* _INCLUDE_IPv6_CODE */

