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
 * ======== tcp6prot.c ========
 *
 * The file handle the TCP Protocol functions for V6. 
 *
 */

#include <stkmain.h>
#include "tcp6.h"

#ifdef _INCLUDE_IPv6_CODE

/**********************************************************************
 ************************** TCP6PROT FUNCTIONS ************************
 **********************************************************************/

/** 
 *  @b Description
 *  @n  
 *      The function is used to create a new TCP socket and is called 
 *      from the SOCK6 module.
 *
 *  @param[in]   h
 *      Handle to the socket being created.
 *  @param[out]  phTcp
 *      The TCP Protocol information which is populated.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   Non Zero
 */
int TCP6PrAttach (HANDLE h, HANDLE *phTcp)
{
    TCPPROT *pt;

    /* Allocate memory for the TCP Protocol Block. */ 
    pt = mmAlloc(sizeof(TCPPROT));
    if(pt == NULL)
    {
        DbgPrintf(DBG_WARN,"TcpPrAttach: OOM");
        NotifyLowResource();
        return( ENOMEM );
    }

    /* Initialize the allocated memory block. */ 
    mmZeroInit( pt, sizeof(TCPPROT) );

    /* Populate the structure. */
    pt->hSock    = h;
    pt->t_state  = TSTATE_CLOSED;
    pt->t_mss    = TCP_MSS_DEFAULT;
    pt->t_flags  = TCP_TFLAGS_DEFAULT;
    pt->t_srtt   = TCPTV_SRTTBASE << TCP_FIXP_SHIFT;
    pt->t_rttvar = TCPTV_RTTDFLT << TCP_FIXP_SHIFT;
    pt->t_trtx   = pt->t_rttvar >> (TCP_FIXP_SHIFT-1);
    pt->t_maxrtt = TCPTV_MAXRTTDFLT;
    pt->snd_cwnd = TCP_MAXWIN;

    /* Get the socket receive and transmit handles. */
    pt->hSBRx = Sock6GetRx(h);
    pt->hSBTx = Sock6GetTx(h);

    /* Store the handle to the protocol information structure. */ 
    *phTcp = (HANDLE)pt;

    /* Attach the socket to the protocol family list. */
    Sock6PcbAttach (h);

    /* Add the protocol object to the timeout list. */
    TCP6TimeoutAdd (pt);
    return(0);
}

/** 
 *  @b Description
 *  @n  
 *      The function is called by the SOCKET Layer to indicate that the
 *      socket has been marked as LISTENING. This internally implies that
 *      the socket can no longer be used for data reception and transmission
 *      so the function clears the internal protocol resources.
 *
 *  @param[in]   h
 *      Handle to the socket 
 *  @param[in]  hTcp
 *      Handle to the TCP protocol information
 *
 *  @retval
 *      Always returns 0.
 */
int TCP6PrListen(HANDLE h, HANDLE hTcp)
{
    TCPPROT*    pt = (TCPPROT *)hTcp;
    TCPREASM*   pR;

    (void)h;

    /* Clean up any of the internal resources which were allocated
     * when the TCP socket was created. The socket however is retained 
     * and is maintained in the internal SOCKET Family table so that 
     * incomming connections match it. 
     * Make sure that the TCP Protocol state is marked as closed. */
    pt->t_state = TSTATE_CLOSED;

    /* Cleanup any internal packets which are queued up. */
    while( (pR = pt->pReasm) )
    {
        pt->pReasm = pR->pNext;
        PBM_free( pR->pPkt );
    }
    pt->reasm_pkt_cnt = 0;

    /* Clean up the socket receive and transmit handles */
    pt->hSBRx = pt->hSBTx = 0;
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function is called to inherit TCP protocol properties
 *      from parent to child.
 *
 *  @param[in]   hParent
 *      Handle to the parent socket.
 *  @param[in]  hTcpParent
 *      Handle to the parent TCP protocol information
 *  @param[in]   hChild
 *      Handle to the child socket.
 *  @param[in]  hTcpChild
 *      Handle to the child TCP protocol information
 *
 *  @retval
 *      Not Applicable
 */
void TCP6PrInherit (HANDLE hParent, HANDLE hTcpParent, HANDLE hChild, HANDLE hTcpChild)
{
    TCPPROT* ptP = (TCPPROT *)hTcpParent;
    TCPPROT* ptC = (TCPPROT *)hTcpChild;

    (void)hParent;
    (void)hChild;

    /* Inherit the max RTT setting from the parent. */
    ptC->t_maxrtt = ptP->t_maxrtt;
    
    /* RFC 2018 - SACK Support */
    ptC->t_flags |= ptP->t_flags & (TF_NOPUSH|TF_NOOPT|TF_NODELAY|TF_SACKPERMITTED);
    if (ptC->t_flags & TF_SACKPERMITTED) 
    {
        /* Allocate memory for the SACK Information block. */
        ptC->pSack = mmAlloc(sizeof(struct SACK_Info));        
        if (ptC->pSack == NULL) {
            ptC->t_flags &= ~TF_SACKPERMITTED;
        }
        else {
            ptC->pSack->txTableBottom = 0;
            ptC->pSack->txTableTop = 0;
            ptC->pSack->rcvTableBottom = 0;
            ptC->pSack->rcvTableTop = 0;
            ptC->pSack->rexmtTimeout = 0;
            ptC->TicksSackRexmt = 0;
        }
    }
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function is called to update the TCP Information based
 *      on the socket route.
 *
 *  @param[in]   pt
 *      Handle to the TCP protocol information
 *  @param[in]  rcvmss
 *      Received MSS.
 *
 *  @retval
 *      Current MSS to advertise.
 */
uint TCP6ValidateMetrics(TCPPROT *pt, uint rcvmss)
{
    HANDLE hRoute6;
    uint ourmss;

    /* Get the ROUTE6 Information from the socket. */
    hRoute6 = Sock6GetRoute(pt->hSock);
    if (hRoute6 == 0)
        hRoute6 = Sock6ValidateRoute (pt->hSock);

    /* Check if we have a ROUTE6 Object or not? */
    if (hRoute6 == 0)
        ourmss = TCP_MSS_DEFAULT_NR;
    else
        ourmss = Rt6GetMTU(hRoute6);

    /* Take off IpHdr & TcpHdr */
    ourmss -= Sock6GetIpHdrSize(pt->hSock) + TCPHDR_SIZE;

    /* A previous write overrides us */
    if( (pt->t_flags & TF_RCVD_MSS) && pt->t_mss < ourmss )
        ourmss = pt->t_mss;

    /* If we have received an mss, record it */
    if( rcvmss )
    {
        /* Use the smallest of the valid mss values */
        pt->t_flags |= TF_RCVD_MSS;
        if( rcvmss < ourmss )
            pt->t_mss = rcvmss;
        else
            pt->t_mss = ourmss;
    }

    /* If we have a valid (negotiated) mss, return it. Else,
     * return what we'd like to advertise. */
    if( pt->t_flags & TF_RCVD_MSS )
        return( pt->t_mss );
    return( ourmss );
} 

/** 
 *  @b Description
 *  @n  
 *      The function is called to close down the TCP Protocol block.
 *
 *  @param[in]  pt
 *      Pointer to the TCP Protocol Information block. 
 *
 *  @retval
 *     Not Applicable.
 */
void TCP6Close( TCPPROT *pt )
{
    TCPREASM *pR;

    pt->t_state = TSTATE_CLOSED;

    /* Disable all timers */
    pt->TicksRexmt   = 0;
    pt->TicksPersist = 0;
    pt->TicksKeep    = 0;
    pt->TicksWait2   = 0;

    /* Also free held resources */
    while( (pR = pt->pReasm) )
    {
        pt->pReasm = pR->pNext;
        PBM_free( pR->pPkt );
    }
    pt->reasm_pkt_cnt = 0;

    /* RFC 2018 - SACK */
    pt->sackActive = 0;

    /* Notify the Socket (if not already detached) */
    if( !(pt->t_flags & TF_DETACHED) )
        Sock6Notify( pt->hSock, SOCK_NOTIFY_CLOSED );
}

/** 
 *  @b Description
 *  @n  
 *      The function drops a TCP side "socket" with ABORT
 *
 *  @param[in]   pt
 *      Handle to the TCP protocol information
 *  @param[in]  Error
 *      Error Code.
 *
 *  @retval
 *      Not applicable.
 */
void TCP6Drop (TCPPROT *pt, int Error)
{
    /* Drop the connection with "ABORTED" error */
    if( pt->t_state >= TSTATE_SYNRCVD )
    {
        pt->t_state = TSTATE_CLOSED;
        TCP6Output( pt );
        tcp6_stats.Drops++;
    }
    else
        tcp6_stats.ConnDrops++;

    /* Change a TIMEOUT to the soft error if any, and set error code */
    if( Error == ETIMEDOUT && pt->t_softerror )
        Error = pt->t_softerror;
    Sock6SetError( pt->hSock, Error );
    TCP6Close( pt );
}

/** 
 *  @b Description
 *  @n  
 *      The function closes the TCP side "socket", detaches and free resources
 *
 *  @param[in]   hSock
 *      Handle to the socket.
 *  @param[in]  phTcp
 *      Handle to the TCP Protocol Information block. 
 *  @param[in]  fatal
 *      Status flag which if set to 1 indicates that the socket should be closed
 *      immediately and if set to 0 indicates that the TCP close state machine
 *      is invoked.
 *
 *  @retval
 *     Always returns 0.
 */
int TCP6PrDetach( HANDLE hSock, HANDLE *phTcp, int fatal )
{
    TCPPROT *pt = *(TCPPROT **)phTcp;

    /* Mark this so close doesn't notify the socket layer */
    pt->t_flags |= TF_DETACHED;

    /* We CLOSE an unconnected socket, but if something is in progress, */
    /* use DROP. We are detaching, so can't do anything gracefully. */
    if( !fatal && pt->t_state >= TSTATE_SYNRCVD && pt->t_state != TSTATE_TIMEWAIT )
        TCP6Drop( pt, 0 );       /* TCP6Drop() calls TCP6Close() */
    else
        TCP6Close( pt );         /* Must call - frees some resources */

    /* Detach the socket and free the TCP control */
    TCP6TimeoutRemove( pt );
    Sock6PcbDetach( hSock );

    /* Zap the TCP Proto Structure */
    *phTcp = 0;

    /* RFC 2018 - SACK */
    if (pt->pSack != NULL)
        mmFree(pt->pSack);

    mmFree(pt);
    return(0);
}

/** 
 *  @b Description
 *  @n  
 *      The function requests a connection for a TCP6 socket.
 *
 *  @param[in]   h
 *      Handle to the socket.
 *  @param[in]  hTcp
 *      Handle to the TCP Protocol Information block. 
 *
 *  @retval
 *     Always returns 0.
 */
int TCP6PrConnect( HANDLE h, HANDLE hTcp )
{
    TCPPROT *pt = (TCPPROT *)hTcp;
    int     error = 0;

    (void)h;

    /* Bump the stats */
    tcp6_stats.ConnAttempt++;

    /* Set inititial send sequence number */
    pt->snd_una = pt->snd_nxt = pt->snd_max = pt->snd_up = pt->iss = tcp6_iss;
    tcp6_iss += TCP_ISSINCR / 2;

    /* Send the SYN ("KeepAlive" timer is also our connection timeout timer) */
    pt->t_state   = TSTATE_SYNSENT;
    pt->TicksKeep = TCPTV_KEEP_INIT;

    error = TCP6Output( hTcp );
    return( error );
}

/** 
 *  @b Description
 *  @n  
 *      The function disconnects a TCP side "socket" - 
 *      performs "half close"
 *
 *  @param[in]   hSock
 *      Handle to the socket.
 *  @param[in]  hTcp
 *      Handle to the TCP Protocol Information block. 
 *
 *  @retval
 *     Always returns 0.
 */
int TCP6PrDisconnect( HANDLE hSock, HANDLE hTcp )
{
    TCPPROT *pt = (TCPPROT *)hTcp;

    /* If less than connected, just close */
    if( pt->t_state < TSTATE_ESTAB )
        TCP6Close( pt );
    /* Else if connected, move to FINWAIT1 */
    else if( pt->t_state == TSTATE_ESTAB )
    {
        pt->t_state = TSTATE_FINWAIT1;
        TCP6Output( pt );
    }
    /* Else we can only be at CLOSEWAIT */
    /* (unless called more than once in which case we don't care) */
    else if( pt->t_state == TSTATE_CLOSEWAIT )
    {
        pt->t_state = TSTATE_LASTACK;
        TCP6Output( pt );
    }

    /* Notify the Socket if we received a FIN already */
    /* (should only happen if we were in CLOSEWAIT) */
    if( pt->t_state > TSTATE_FINWAIT1 && pt->t_state != TSTATE_FINWAIT2 )
        Sock6Notify( hSock, SOCK_NOTIFY_DISCONNECT );

    return(0);
}

/** 
 *  @b Description
 *  @n  
 *      The function deals with Rx data being removed from buffer
 *
 *  @param[in]   h
 *      Handle to the socket.
 *  @param[in]  hTcp
 *      Handle to the TCP Protocol Information block. 
 *
 *  @retval
 *     Always returns 0.
 */
int TCP6PrRecv( HANDLE h, HANDLE hTcp )
{
    (void)h;

    /* A read may cause us to readjust our window */
    return( TCP6Output( hTcp ) );
}

/** 
 *  @b Description
 *  @n  
 *      The function sends data
 *
 *  @param[in]   h
 *      Handle to the socket.
 *  @param[in]  hTcp
 *      Handle to the TCP Protocol Information block. 
 *  @param[in]  pBuf
 *      Pointer to the data Buffer to be transmitted. 
 *  @param[in]  Size
 *      Size of the data buffer.
 *  @param[out] pRetSize
 *      Number of bytes sent out.
 *
 *  @retval
 *     Always returns 0.
 */
int TCP6PrSend( HANDLE h, HANDLE hTcp, UINT8 *pBuf, INT32 Size, INT32 *pRetSize )
{
    TCPPROT  *pt = (TCPPROT *)hTcp;
    INT32    Space;

    (void)h;

    /* Append as much data as possible to the output buffer */
    Space = SB6GetSpace( pt->hSBTx );
    if( Space < Size )
        Size = Space;

    /* Copy out the data */
    if( Size )
        Size = SB6Write( pt->hSBTx, Size, pBuf, 0 );
    *pRetSize = Size;

    /* Data write may cause us to send data */
    if( Size )
        return( TCP6Output( hTcp ) );
    else
        return( 0 );
}

/** 
 *  @b Description
 *  @n  
 *      The function sends OOB data
 *
 *  @param[in]   h
 *      Handle to the socket.
 *  @param[in]  hTcp
 *      Handle to the TCP Protocol Information block. 
 *  @param[in]  pBuf
 *      Pointer to the data Buffer to be transmitted. 
 *  @param[in]  Size
 *      Size of the data buffer.
 *  @param[out] pRetSize
 *      Number of bytes sent out.
 *
 *  @retval
 *     Always returns 0.
 */
int TCP6PrSendOOB( HANDLE h, HANDLE hTcp, UINT8 *pBuf, INT32 Size, INT32 *pRetSize )
{
    TCPPROT  *pt = (TCPPROT *)hTcp;
    INT32    Space;
    INT32    UseSize;

    (void)h;

    /* Append as much data as possible to the output buffer */
    Space = SB6GetSpace( pt->hSBTx );
    if( Space < Size )
        UseSize = Space;
    else
        UseSize = Size;

    /* Copy out the data */
    if( UseSize )
        UseSize = SB6Write( pt->hSBTx, UseSize, pBuf, 0 );
    *pRetSize = UseSize;

    /* The last byte of the buffer is the urgent data. */
    /* Update urgent pointer if we've appended all the data */
    if( UseSize == Size )
        pt->snd_up = pt->snd_una + SB6GetTotal(pt->hSBTx);

    /* Data write may cause us to send data */
    if( UseSize )
        return( TCP6Output( hTcp ) );
    else
        return( 0 );
}

/** 
 *  @b Description
 *  @n  
 *      The function returns the TCP State
 *
 *  @param[in]   hParent
 *      Handle to the socket.
 *  @param[in]  hTcp
 *      Handle to the TCP Protocol Information Block.
 *
 *  @retval
 *     TCP State
 */
uint TCP6PrGetState( HANDLE hParent, HANDLE hTcp )
{
    (void)hParent;

    return( ((TCPPROT *)hTcp)->t_state );
}

/** 
 *  @b Description
 *  @n  
 *      The function is called to indicate there is an error detected
 *      by the reception of an error ICMPv6 packet.
 *
 *  @param[in]   h
 *      Handle to the socket.
 *  @param[in]  hTcp
 *      Handle to the TCP Protocol Information block. 
 *  @param[in]  Code
 *      Obsolete
 *  @param[in]  Error
 *      Error Code.
 *
 *  @retval
 *      Not Applicable
 */
void TCP6PrCtlError(HANDLE h, HANDLE hTcp, uint Code, int Error )
{
    TCPPROT  *pt = (TCPPROT *)hTcp;

    /* Quench - close congestion window */
    if( Code == PRC_QUENCH )
        pt->snd_cwnd = pt->t_mss;
    else if( Error )
    {
        /* Depending on state, we may ignore some errors */
        if( pt->t_state == TSTATE_ESTAB && (Error == EHOSTUNREACH || Error == EHOSTDOWN))
            return;

       if( pt->t_state<TSTATE_ESTAB && pt->t_rtxindex>3 && pt->t_softerror )
            Sock6SetError( h, Error );
       else
            pt->t_softerror = Error;

       Sock6Notify( h, SOCK_NOTIFY_ERROR );
    }
}

/** 
 *  @b Description
 *  @n  
 *      The function is used to set the TCP options.
 *
 *  @param[in]   h
 *      Handle to the socket.
 *  @param[in]  hTcp
 *      Handle to the TCP Protocol Information block. 
 *  @param[in]  Prop
 *      The Property which needs to be configured.
 *  @param[in]  pBuf
 *      Data buffer where the value of property is present
 *  @param[in]  size
 *      Size of the Data buffer 
 *
 *  @retval
 *     Success  -   0
 *  @retval
 *     Error    -   Non Zero
 */
int TCP6PrSetOption(HANDLE h, HANDLE hTcp, int Prop, void *pBuf, int size)
{
    TCPPROT  *pt = (TCPPROT *)hTcp;
    int      value;

    (void)h;

    if( size != sizeof(int) || !pBuf )
        return( EINVAL );

    value = *(int *)pBuf;

    switch( Prop )
    {
    case TCP_NODELAY:
        if( value )
            pt->t_flags |= TF_NODELAY;
        else
            pt->t_flags &= ~TF_NODELAY;
        return( 0 );

    case TCP_NOPUSH:
        if( value )
            pt->t_flags |= TF_NOPUSH;
        else
            pt->t_flags &= ~TF_NOPUSH;
        return( 0 );

    case TCP_NOOPT:
        if( value )
            pt->t_flags |= TF_NOOPT;
        else
            pt->t_flags &= ~TF_NOOPT;
        return( 0 );

    case TCP_MAXSEG:
        if( (uint)value < pt->t_mss )
            TCP6ValidateMetrics( pt, (uint)value );
        return( 0 );

    case TCP_SACKPERMITTED:
        /* 
         * RCF 2018 - SACK
         * Check if SACK is already set
         * SACK can only be set if socket state is TSATE_CLOSED
         *
         */
        if (pt->pSack != NULL || pt->t_state != TSTATE_CLOSED) {
            return (EINVAL);               
                }

        if (value) {
                        pt->pSack = mmAlloc(sizeof(struct SACK_Info));
                        if (pt->pSack == NULL) {
                            return (EINVAL);
                        }
                    pt->pSack->txTableBottom = 0;
                    pt->pSack->txTableTop = 0;
                    pt->pSack->rcvTableBottom = 0;
                    pt->pSack->rcvTableTop = 0;
            pt->t_flags |= TF_SACKPERMITTED;
                    pt->TicksSackRexmt = 0;
                }
        else {
            pt->t_flags &= ~TF_SACKPERMITTED;
                        if (pt->pSack != NULL) {
                            mmFree(pt->pSack);
                                pt->pSack = NULL;
                pt->sackActive = 0;
                        pt->TicksSackRexmt = 0;
                        }
                }
        return( 0 );

    case TCP_MAXRTT:
        /* convert to clock ticks and make sure a realistic value is used. */
        pt->t_maxrtt = ((UINT32)value+99)/100;
        if( pt->t_maxrtt < TCPTV_MINIMALMAXRTT )
            pt->t_maxrtt = TCPTV_MINIMALMAXRTT;
        return( 0 );
    }
    return( EINVAL );
}

/** 
 *  @b Description
 *  @n  
 *      The function is used to get the TCP options.
 *
 *  @param[in]   h
 *      Handle to the socket.
 *  @param[in]  hTcp
 *      Handle to the TCP Protocol Information block. 
 *  @param[in]  Prop
 *      The Property which needs to be configured.
 *  @param[out] pBuf
 *      Data buffer where the value of property will be copied.
 *  @param[out] psize
 *      Size of the Data buffer 
 *
 *  @retval
 *     Success  -   0
 *  @retval
 *     Error    -   Non Zero
 */
int TCP6PrGetOption(HANDLE h, HANDLE hTcp, int Prop, void *pBuf, int *psize)
{
    TCPPROT  *pt = (TCPPROT *)hTcp;

    (void)h;

    if( *psize < sizeof(int) )
        return( EINVAL );

    *psize = sizeof(int);

    switch( Prop )
    {
    case TCP_NODELAY:
        if( pt->t_flags & TF_NODELAY )
            *(int *)pBuf = 1;
        else
            *(int *)pBuf = 0;
        return( 0 );

    case TCP_NOPUSH:
        if( pt->t_flags & TF_NOPUSH )
            *(int *)pBuf = 1;
        else
            *(int *)pBuf = 0;
        return( 0 );

    case TCP_NOOPT:
        if( pt->t_flags & TF_NOOPT )
            *(int *)pBuf = 1;
        else
            *(int *)pBuf = 0;
        return( 0 );

    case TCP_MAXSEG:
        *(int *)pBuf = (int)pt->t_mss;
        return( 0 );

    case TCP_SACKPERMITTED:
        /* RFC 2018 - SACK */
        if( pt->t_flags & TF_SACKPERMITTED )
            *(int *)pBuf = 1;
        else
            *(int *)pBuf = 0;
        return( 0 );

    case TCP_MAXRTT:
        /* convert to ms instead of clock ticks */
        *(int *)pBuf = (int)pt->t_maxrtt * 100;
        return( 0 );
    }
    return( EINVAL );
}

#endif /* _INCLUDE_IPv6_CODE */

