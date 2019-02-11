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
 * ======== rawethsock.c ========
 *
 * The file implements the RAWETHSOCK object which is the socket
 * library for Raw Ethernet Sockets. Raw Ethernet Sockets are 
 * useful for transporting data over Ethernet network using custom
 * Layer 2 Protocol types, i.e other than IPv4, IPv6 etc.
 *
 */

#include <stkmain.h>
#include "rawethsock.h"
#include <socket.h>

/** 
 *  @b Description
 *  @n  
 *      The function creates a new Raw Ethernet Socket.
 *
 *  @param[in]  Family
 *      Socket Family. Only AF_RAWETH is supported.
 *  @param[in]  Type
 *      The type of socket being created
 *          - SOCKRAWETH   : RAW Socket 
 *  @param[in]  Protocol
 *      Valid Values are 0, IPPROTO_UDP and IPPROTO_TCP.
 *  @param[in] RxBufSize
 *      Receive buffer size of the Socket.
 *  @param[in] TxBufSize
 *      Transmit buffer size of the Socket.
 *  @param[out] phSock 
 *      Socket Handle which is returned.
 *
 *  @retval
 *      Success -   0
 *  @retval      
 *      Error   -   Non Zero
 */
int RawEthSockNew( int Family, int Type, int Protocol,
             int RxBufSize, int TxBufSize, HANDLE *phSock )
{
    SOCKRAWETH  *ps;
    int         error = 0;

    /*
     * Check to see is request makes sense
     * 
     * AF_RAWETH, SOCKRAWETH: protocol can be anything, including NULL
     * 
     */
    if( Family != AF_RAWETH )
        return( EPFNOSUPPORT );

    if( Type != SOCK_RAWETH )
        return( ESOCKTNOSUPPORT );

    /*
     * If we got here, we have a legal socket request
     */

    /* Attempt to allocate space for the socket */
    if( !(ps = mmAlloc(sizeof(SOCKRAWETH))) )
    {
        NotifyLowResource();
        error = ENOMEM;
        goto socknew_done;
    }

    /* Initialize the socket with defaults   */
    mmZeroInit( ps, sizeof(SOCKRAWETH) );     
    ps->fd.Type         = HTYPE_RAWETHSOCK;
    ps->fd.OpenCount    = 1;
    ps->Family          = (UINT32)Family;       /*    AF_RAWETH      */
    ps->SockType        = (UINT32)Type;         /*    SOCKRAWETH    */
    ps->Protocol        = (UINT32)Protocol;     /*    L3 Protocol Number  */

    /* Init default timeouts    */
    ps->RxTimeout       = SOCK_TIMEIO * 1000;

    /* Initialize the default socket priority. */
    ps->SockPriority    = PRIORITY_UNDEFINED;

    /* Setup desired buffer sizes (if any)  */
    if( RxBufSize )
        ps->RxBufSize   = RxBufSize;
    if( TxBufSize )
        ps->TxBufSize   = TxBufSize;

    /* Allocate Rx socket buffer    */
    /* The Raw Eth Sockets are designed to be zero copy on both
     * send and receive.
     */
    if( 1 )
    {
        ps->StateFlags = SS_ATOMICREAD;
        if( !ps->RxBufSize )
            ps->RxBufSize = SOCK_RAWETHRXLIMIT;
        ps->hSBRx = SBNew( ps->RxBufSize, SOCK_BUFMINRX, SB_MODE_HYBRID );
    }

    if( !ps->hSBRx )
    {
        error = ENOMEM;
        goto socknew_error;
    }

    /* Finalize Socket Status   */
    if( 1 )
    {
        ps->StateFlags |= SS_ATOMICWRITE;            

        ps->hSBTx = 0;

        /* Set the SockProt Type    */
        ps->SockProt = SOCKPROT_RAWETH;
    }

    /* Attach the socket to protocol processing */
    if( (error = RawEthSockPrAttach( ps )) )
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

/** 
 *  @b Description
 *  @n  
 *      The function closes a Raw ethernet Socket.
 *
 *  @param[in]  h
 *      Socket Handle which is to be closed.
 *
 *  @retval
 *      Success -   0
 *  @retval      
 *      Error   -   Non Zero
 */
int RawEthSockClose( HANDLE h )
{
    SOCKRAWETH*    ps = (SOCKRAWETH *)h;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_RAWETHSOCK )
    {
        DbgPrintf(DBG_ERROR,"RawEthSockClose: HTYPE %04x",ps->fd.Type);
        return( ENOTSOCK );
    }
#endif

    /* Detach the socket from protocol processing */
    RawEthSockPrDetach( ps );

    /* Free the Rx and Tx Buffers */
    if( ps->hSBRx )
        SBFree( ps->hSBRx );
    if( ps->hSBTx )
        SBFree( ps->hSBTx );

    /* Free the sock memory */
    ps->fd.Type = 0;
    mmFree( ps );

    return( 0 );
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
int RawEthSockCheck( HANDLE h, int IoType )
{
    SOCKRAWETH *ps = (SOCKRAWETH *)h;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_RAWETHSOCK )
    {
        DbgPrintf(DBG_ERROR,"RawEthSockCheck: HTYPE %04x",ps->fd.Type);
        return( 0 );
    }
#endif

    switch( IoType )
    {
        case SOCK_READ:
        {
                
            /*
             * Return TRUE if readable
             */

            /* Simply return TRUE for the following error cases
             * - Error pending sockets
             * - When shutdown for recv
             */
            if( ps->ErrorPending || (ps->StateFlags & SS_CANTRCVMORE) )
                return(1);

            /* Also return true if socket can be "read" */
            if( SBGetTotal(ps->hSBRx) >= SBGetMin(ps->hSBRx) )
                return(1);

            break;
        }

        case SOCK_WRITE:
        {
    
            /*
             * Return TRUE if writeable
             */

            /* Simply return TRUE for the following error cases
             * - Error pending sockets
             * - When shutdown for write
             */
            if( ps->ErrorPending || (ps->StateFlags & SS_CANTSENDMORE) )
                return(1);

            /* Also return true if connected and can write */
            /* Writable "connected" cases */
            if( (ps->StateFlags & SS_ATOMICWRITE) ||
                (ps->hSBTx && (SBGetSpace(ps->hSBTx) >= SBGetMin(ps->hSBTx))))
                return(1);
        
            break;
        }

        case SOCK_EXCEPT:
        {
            /* Return TRUE if pending error or socket is being shutdown */
            if( ps->ErrorPending || (ps->StateFlags & SS_CANTRCVMORE) )
                return(1);

            break;
        }
    }

    /* No operation pending on this socket. */
    return(0);
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
int RawEthSockStatus( HANDLE h, int request, int *results )
{
    SOCKRAWETH *ps = (SOCKRAWETH *)h;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_RAWETHSOCK )
    {
        DbgPrintf(DBG_ERROR,"RawEthSockStatus: HTYPE %04x",ps->fd.Type);
        return( EINVAL );
    }
#endif

    if( request==FDSTATUS_RECV && results )
    {
        /* Return socket receive status
         * returns -1 if socket can not be read or has error pending
         * otherwise returns bytes available
         */
        if( ps->ErrorPending || (ps->StateFlags & SS_CANTRCVMORE) )
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
        /* Return socket send status
         * returns -1 if socket can not be written or has error pending
         * Other sockets = max byte send w/o message size error
         */
        if( ps->ErrorPending || (ps->StateFlags & SS_CANTSENDMORE) )
            *results = -1;
        else if( ps->hSBTx )
            *results = SBGetSpace(ps->hSBTx);
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
 *      The function shuts down the raw ethernet socket. 
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
int RawEthSockShutdown( HANDLE h, int how )
{
    SOCKRAWETH   *ps = (SOCKRAWETH *)h;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_RAWETHSOCK )
    {
        DbgPrintf(DBG_ERROR,"RawEthSockShutdown: HTYPE %04x",ps->fd.Type);
        return( ENOTSOCK );
    }
#endif

    /* Shutdown Read */
    if( how == SHUT_RD || how == SHUT_RDWR )
    {
        ps->StateFlags |= SS_CANTRCVMORE;

        /* Perform read flush */
        if( ps->hSBRx )
            SBFlush( ps->hSBRx, 1 );

        /* Notify the socket of status change */
        FdSignalEvent( ps, FD_EVENT_READ|FD_EVENT_EXCEPT );
    }

    /* Shutdown Write */
    if( how == SHUT_WR || how == SHUT_RDWR )
    {
        ps->StateFlags |= SS_CANTSENDMORE;

        /* Notify the socket of status change */
        FdSignalEvent( ps, FD_EVENT_WRITE );
    }

    return(0);
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
/* ARGSUSED */
int RawEthSockSet(HANDLE hSock, int Type, int Prop, void *pbuf, int size)
{
    SOCKRAWETH *ps = (SOCKRAWETH *)hSock;
    int  value,error = 0;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_RAWETHSOCK )
    {
        DbgPrintf(DBG_ERROR,"RawEthSockSet: HTYPE %04x",ps->fd.Type);
        return( ENOTSOCK );
    }
#endif

    /* Check size and pointer, just to be safe */
    if( size && !pbuf )
        return( EINVAL );

    /*
     * Configure the Socket Properties
     */

    switch( Prop )
    {
        case SO_RCVTIMEO:
        {
            struct timeval *ptv = (struct timeval *)pbuf;
            UINT32         Time;

            if( size != sizeof(struct timeval) )
                return( EINVAL );

            Time = (UINT32)ptv->tv_sec*1000;
            Time += (UINT32)((ptv->tv_usec+999)/1000);

            ps->RxTimeout = Time;

            return(0);
        }

        case SO_IFDEVICE:
        {
            HANDLE h;

            if( size != sizeof(UINT32) )
                return( EINVAL );

            h = (HANDLE)NIMUFindByIndex ( *(UINT32 *)pbuf );
            if (!h)
                return EINVAL;

            ps->hIF = h;
            return(0);
        }
        
        case SO_TXTIMESTAMP:
        {
            ps->pTimestampFxn = (TimestampFxn) ((UINT32) pbuf);
            return(0);
        }

        default:
        {
            break;
        }
    }

    /* For the remainder, the property value is an int */
    if( size < sizeof(int) )
        return( EINVAL );
    value = *(int *)pbuf;

    switch( Prop )
    {
        case SO_SNDBUF:
        {
            /* No buffering on the Transmit path. This value
             * only limits the maximum size of packet that we 
             * can transmit using the Raw ethernet module.
             */
            ps->TxBufSize = value;
            break;
        }

        case SO_RCVBUF:
        {
            if( ps->hSBRx && SBSetMax(ps->hSBRx,value)!=value )
                error = EINVAL;
            else
                ps->RxBufSize = value;
            break;
        }

        case SO_RCVLOWAT:
        {
            if( ps->hSBRx )
                SBSetMin( ps->hSBRx, value );
            break;
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
/* ARGSUSED */
int RawEthSockGet(HANDLE hSock, int Type, int Prop, void *pbuf, int *psize)
{
    SOCKRAWETH *ps = (SOCKRAWETH *)hSock;
    int  error = 0;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_RAWETHSOCK )
    {
        DbgPrintf(DBG_ERROR,"RawEthSockGet: HTYPE %04x",ps->fd.Type);
        return( ENOTSOCK );
    }
#endif

    /* Check pointers, just to be safe */
    if( !psize || !pbuf )
        return( EINVAL );

    /*
     * Socket Properties
     */

    /*
     * Handle the structure based first
     */

    switch( Prop )
    {
        case SO_RCVTIMEO:
        {
            struct timeval *ptv = (struct timeval *)pbuf;

            if( *psize < sizeof(struct timeval) )
                return( EINVAL );
            *psize = sizeof( struct timeval );

            ptv->tv_sec = ps->RxTimeout / 1000;
            ptv->tv_usec = (ps->RxTimeout % 1000) * 1000;

            return(0);
        }

        case SO_IFDEVICE:
        {
            if( *psize < sizeof( UINT32 ) )
                return( EINVAL );
            *psize = sizeof( UINT32 );
            if( !ps->hIF )
                *(UINT32 *)pbuf = 0;
            else
                *(UINT32 *)pbuf = IFGetIndex( ps->hIF );
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

        case SO_RCVLOWAT:
        {
            if( ps->hSBRx )
                *(int *)pbuf = (int)SBGetMin( ps->hSBRx );
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
 *      The function receives data from a socket without copy.
 *
 *  @param[in]  h
 *      Socket Handle from where data has to be read.
 *  @param[in]  ppPkt
 *      Pointer in which the packet received will be returned.
 *
 *  @retval
 *      Success     -   0
 *  @retval      
 *      Error       -   Non Zero
 */
int RawEthSockRecvNC( HANDLE h, PBM_Pkt **ppPkt )
{
    SOCKRAWETH *ps     = (SOCKRAWETH *)h;
    int         error   = 0;
    INT32       Total   = 0;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_RAWETHSOCK )
    {
        DbgPrintf(DBG_ERROR,"RawEthSockRecvNC: HTYPE %04x",ps->fd.Type);
        return( ENOTSOCK );
    }
#endif

    /* Must be ATOMIC socket    */
    if( !(ps->StateFlags & SS_ATOMICREAD) )
        return( EINVAL );

    /* Cant receive data if no interface configured. */
    if( !ps->hIF )
        return( ENXIO );

rx_restart:
    /* Get the total bytes available */
    Total = SBGetTotal(ps->hSBRx);

    /* Check for blocking condition */
    if( !Total )
    {
        /*
         * Check all non-blocking conditions first
         */

        /* Return any pending error */
        if( ps->ErrorPending )
        {
            error = ps->ErrorPending;
            ps->ErrorPending = 0;
            goto rx_dontblock;
        }

        /* Don't block if the receiver is shut down */
        if( ps->StateFlags & SS_CANTRCVMORE )
        {
            error = 0;
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
        /* Read data packet NULL 
         * We dont care about deciphering the IP address/port number from where
         * the packet is received hence the NULLs in the call to SBReadNC
         */
        *ppPkt = SBReadNC( ps->hSBRx, NULL, NULL );

        return(0);
    }
}

/** 
 *  @b Description
 *  @n  
 *      The function send data out using a socket. This is
 *      the "copy" implementation of send() wherein the data
 *      buffer is copied over by the L3 before being sent out.
 *      Thus, the buffer allocation and free is responsibility of
 *      the application.
 *
 *  @param[in]  h
 *      Socket Handle from where data has to be send out
 *  @param[in]  pBuf
 *      Data Buffer which contains the data to be sent out.
 *  @param[in]  size
 *      Size of the data buffer passed.
 *  @param[in]  pRetSize
 *      Total number of data bytes actually sent out.
 *
 *  @retval
 *      Success     -   0
 *  @retval      
 *      Error       -   Non Zero
 */
int RawEthSockSend
(
    HANDLE   h,
    char     *pBuf,
    INT32    size,
    INT32    *pRetSize
)
{
    SOCKRAWETH *ps = (SOCKRAWETH *)h;
    int         error = 0;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_RAWETHSOCK )
    {
        DbgPrintf(DBG_ERROR,"RawEthSockSend: HTYPE %04x",ps->fd.Type);
        return( ENOTSOCK );
    }
#endif

    /* Bound size */
    if( size <= 0  || !pBuf || !pRetSize)
        return( EINVAL );

    /*
     * This routine doesn't actually enqueue any data, since "how"
     * the data is queued is dependent on the protocol.
     * It returns any error returned and number of bytes sent out.
     */
    if( 1 )
    {
        /*
         * Check error conditions in our loop since the error may
         * occur while we're sending
         */

        /* Return any pending error */
        if( ps->ErrorPending )
        {
            error = ps->ErrorPending;
            goto send_error;
        }

        /* Can't send if send shutdown */
        if( ps->StateFlags & SS_CANTSENDMORE )
        {
            error = ESHUTDOWN;
            goto send_error;
        }

        /* Cant send data if no interface configured. */
        if( !ps->hIF )
        {
            error = ENXIO;
            goto send_error;
        }

        /* Send the Data */
        error = RawEthTxPacket ( (HANDLE)ps, pBuf, size);

        /* Break out now on an error condition */
        if( error )
            goto send_error;

        /* If we're ATOMIC, we sent what we could - leave now */
        if( ps->StateFlags & SS_ATOMICWRITE )
        {
            *pRetSize = size;
            return(0);
        }
    }


send_error:
    return( error );
}

/** 
 *  @b Description
 *  @n  
 *      The function send data out using a socket without 
 *      copy.
 *
 *  @param[in]  h
 *      Socket Handle from where data has to be send out
 *  @param[in]  pBuf
 *      Data Buffer which contains the data to be sent out.
 *  @param[in]  size
 *      Size of the data buffer passed.
 *  @param[in]  hPkt
 *      Handle to the packet that needs to be sent out on wire.
 *  @param[in]  pRetSize
 *      Total number of data bytes actually sent out.
 *
 *  @retval
 *      Success     -   0
 *  @retval      
 *      Error       -   Non Zero
 */
int RawEthSockSendNC
(
    HANDLE   h,
    char     *pBuf,
    INT32    size,
    HANDLE   hPkt,
    INT32    *pRetSize
)
{
    SOCKRAWETH *ps = (SOCKRAWETH *)h;
    int         error = 0;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_RAWETHSOCK )
    {
        DbgPrintf(DBG_ERROR,"RawEthSockSend: HTYPE %04x",ps->fd.Type);
        return( ENOTSOCK );
    }
#endif

    /* Bound size */
    if( size <= 0  || !pBuf || !hPkt || (size > PBM_getBufferLen(hPkt)) )
        return( EINVAL );

 
    /*
     * This routine doesn't actually enqueue any data, since "how"
     * the data is queued is dependent on the protocol.
     * It returns any error returned and number of bytes sent out.
     */
    if( 1 )
    {
        /*
         * Check error conditions in our loop since the error may
         * occur while we're sending
         */

        /* Return any pending error */
        if( ps->ErrorPending )
        {
            error = ps->ErrorPending;
            goto send_error;
        }

        /* Can't send if send shutdown */
        if( ps->StateFlags & SS_CANTSENDMORE )
        {
            error = ESHUTDOWN;
            goto send_error;
        }

        /* Cant send data if no interface configured. */
        if( !ps->hIF )
        {
            error = ENXIO;
            goto send_error;
        }

        /* Send the Data */
        error = RawEthTxPacketNC ( (HANDLE)ps, pBuf, size, hPkt );

        /* Break out now on an error condition */
        if( error )
            goto send_error;

        /* If we're ATOMIC, we sent what we could - leave now */
        if( ps->StateFlags & SS_ATOMICWRITE )
        {
            *pRetSize = size;
            return(0);
        }
    }

send_error:
    return( error );
}

/** 
 *  @b Description
 *  @n  
 *      This function is called by RawEthernet object to notify 
 *      the socket of any read/write/connection status activity.
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
int RawEthSockNotify( HANDLE h, int Notification )
{
    SOCKRAWETH *ps = (SOCKRAWETH *)h;

#ifdef _STRONG_CHECKING
    if( ps->fd.Type != HTYPE_RAWETHSOCK )
    {
        DbgPrintf(DBG_ERROR,"RawEthSockNotify: HTYPE %04x",ps->fd.Type);
        return(0);
    }
#endif

    /*
     * This switch handles active sockets.
     */
    switch( Notification )
    {
        case SOCK_NOTIFY_RCVDATA:
        {
            /* Notification that Socket read data is available */

            /* If we're closing or can't receive more flush new data */
            if( ps->StateFlags & (SS_CANTRCVMORE) )
            {
                if( ps->hSBRx )
                    SBFlush( ps->hSBRx, 1 );
                /* Reject the message to tell RawEth module we "flushed" */
                return (0);
            }

            /* Wake owning task if waiting on read */
            FdSignalEvent( ps, FD_EVENT_READ );

            break;
        }

        case SOCK_NOTIFY_ERROR:
        {
            FdSignalEvent( ps, FD_EVENT_READ|FD_EVENT_WRITE|FD_EVENT_EXCEPT );
            break;
        }
    }

    return(1);
}

/** 
 *  @b Description
 *  @n  
 *      The function creates a Raw Ethernet packet for the SOCKRAWETH Family.
 *
 *  @param[in]  hSock
 *      Handle of the socket for which the packet is being created.
 *
 *  @param[in]  Payload
 *      Size of the packet
 *
 *  @param[in]  pError
 *      Pointer to propagate back any errors from this API.
 *
 *  @retval
 *      Success -   Pointer to the packet created
 *  @retval
 *      Error   -   NULL                            
 */
PBM_Pkt* RawEthSockCreatePacket( HANDLE hSock, UINT32 Payload, UINT32* pError )
{
    SOCKRAWETH*     ps = (SOCKRAWETH *)hSock;
    PBM_Pkt*        pPkt;

    /* The maximum packet size that can be transmitted is limited 
     * by either the MTU of the interface on which the packet will 
     * be transmitted or by the TxBufSize configured on this socket,
     * whichever is the smaller value of those.
     * There is no layer to do the fragmentation on the Raw Eth Tx path,
     * hence its important to limit the packet size by the MTU so as to 
     * avoid drops at the driver.
     */
    if( ((ps->TxBufSize) && (Payload > ps->TxBufSize)) || ((ps->hIF) && (Payload > IFGetMTU( ps->hIF ))) )
    {
        /* The packet size too big to transmit using the specified
         * settings.
         */
        *pError = EMSGSIZE;
        return NULL;
    }
   
    /* Allocate space for an ethernet packet and initialize its
     * offset.
     */
    if( !(pPkt = NIMUCreatePacket( Payload )))
    {
        *pError = ENOBUFS;
        return NULL;
    }
    else
    {
        /* Adjust the offset to add the Ethernet header 
         * The application expects the buffer start to be pointing
         * to the ethernet header offset in the packet.
         */
        pPkt->DataOffset -= ETHHDR_SIZE;

        /* Inherit the packet priority from the socket; since all 
         * packets transmitted from a particular socket will have 
         * the same priority.
         */
        pPkt->PktPriority = ps->SockPriority;
            
        /* Packet allocation and initialization successful. */
        return pPkt;
    }
}

