/*
 * Copyright (c) 2012-2013, Texas Instruments Incorporated
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
 * IPv4 stack - UDP layer
 *
 * Handles UDP layer processing in IPv4 stack.
 *
 */

#include <stkmain.h>

/* Private and Public Globals */
UDPSTATS udps;                      /* Stats */

PSEUDO   upseudo;                   /* Pseudo header for checksum */

/*-------------------------------------------------------------------- */
/* void UdpChecksum( UDPHDR *pbHdr ) */
/* Checksums the UDP header */
/*-------------------------------------------------------------------- */
void UdpChecksum( UDPHDR *pUdpHdr )
{
    int     tmp1;
    UINT16  *pw;
    UINT32  TSum;

    /* Get header size in bytes */
    tmp1 = (int)HNC16(upseudo.Length);

    /* Checksum field is NULL in checksum calculations */
    pUdpHdr->UDPChecksum = 0;

    /* Checksum the header */
    pw = (UINT16 *)pUdpHdr;
    TSum = 0;
    for( ; tmp1 > 1; tmp1 -= 2 )
        TSum += (UINT32)*pw++;
#ifdef BIGENDIAN
    if( tmp1 )
        TSum += (UINT32)(*pw & 0xFF00);
#else
    if( tmp1 )
        TSum += (UINT32)(*pw & 0x00FF);
#endif

    /* Checksum the pseudo header */
    pw = (UINT16 *)&upseudo;
    for( tmp1=0; tmp1 < 6; tmp1++ )
        TSum += (UINT32)*pw++;

    TSum = (TSum&0xFFFF) + (TSum>>16);
    TSum = (TSum&0xFFFF) + (TSum>>16);

    /* Special case the 0xFFFF checksum - don't use a checksum */
    /* value of 0x0000 */
    if( TSum != 0xFFFF )
        TSum = ~TSum;

    /* Note checksum is Net/Host byte order independent */
    pUdpHdr->UDPChecksum = (UINT16)TSum;
}

/*-------------------------------------------------------------------- */
/* UdpOutput() */
/* Called when UDP packet should be sent */
/*-------------------------------------------------------------------- */
int UdpOutput( HANDLE hSock, UINT8 *buf, INT32 size, INT32 *pRetSize )
{
    PBM_Pkt     *pPkt;
    HANDLE      hRoute,hIFTx;
    uint        IPHdrLen;
    INT32       mss;
    UDPHDR      *pUdpHdr;
    uint        length;
    int         error;
    SOCK        *pSock = (SOCK *) hSock;

    /* Bound the size to something we can handle */
    if (pSock->TxBufSize == 0) {
        /* If send buffer size (SO_SNDBUF) is not set: */
        /* We'll try and get the MTU from the route, then the egress IF, */
        /* or finally we just assume a default. */
        if ((hRoute = SockGetRoute( hSock ))) {
            mss = (INT32)RtGetMTU( hRoute );
            hIFTx = 0;
        }
        else if ((hIFTx = SockGetIFTx( hSock )))
            mss = (INT32)IFGetMTU( hIFTx );
        else
            mss = UDP_MSS_DEFAULT;
    }
    else {
        mss = pSock->TxBufSize;
        hRoute = SockGetRoute (hSock);
        if( hRoute != 0 )
            hIFTx = 0;
        else
            hIFTx = SockGetIFTx (hSock);
    }

    mss -= SockGetIpHdrSize(hSock) + UDPHDR_SIZE;   /* Sub off IpHdr & UdpHdr */

    if( size > mss )
    {
        error = EMSGSIZE;
        goto UDP_EXIT;
    }

    /* Create the packet */
    /* Payload = size */
    /* Reserve = UDPHDR_SIZE */
    length = UDPHDR_SIZE + (uint)size;
    if( !(pPkt = SockCreatePacket( hSock, (uint)size + UDPHDR_SIZE)) )
    {
        udps.SndNoPacket++;
        error = ENOBUFS;
        goto UDP_EXIT;
    }

    /* Get the IP header len */
    IPHdrLen = pPkt->IpHdrLen;

    /* Assign a UDP header pointer */
    pUdpHdr = (UDPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset + IPHdrLen);

    /* Fill in UDP Header */

    /* Set some UDP header stuff */
    pUdpHdr->SrcPort = SockGetLPort(hSock);
    pUdpHdr->DstPort = SockGetFPort(hSock);
    pUdpHdr->Length  = HNC16( length );

    /* Copy the data */
    mmCopy( ((UINT8 *)pUdpHdr)+UDPHDR_SIZE, buf, (uint)size );

    /* Checksum Header */
    upseudo.IPSrc    = SockGetLIP(hSock);
    upseudo.IPDst    = SockGetFIP(hSock);
    upseudo.Null     = 0;
    upseudo.Protocol = 17;
    upseudo.Length   = pUdpHdr->Length;
    UdpChecksum( pUdpHdr );

    /* Indicate the preferred route and IF */
    PBM_setRoute( pPkt, hRoute );
    pPkt->hIFTx = hIFTx;

    /* Set the timestamp call-out function */
    pPkt->pTimestampFxn = pSock->pTimestampFxn;

    /* Count it */
    udps.SndTotal++;

    /* Send the packet */
    error=(int)IPTxPacket(pPkt,SockGetOptionFlags(hSock)&FLG_IPTX_SOSUPPORTED);

UDP_EXIT:
    if( !error )
        *pRetSize = size;
    else
        *pRetSize = 0;

    return( error );
}

/*-------------------------------------------------------------------- */
/* UdpInput() */
/* Rx UDP Packet */
/*-------------------------------------------------------------------- */
void UdpInput( PBM_Pkt *pPkt )
{
    PBM_Pkt    *pPktCopy;
    HANDLE     hSock,hSockNext,hSBRx,hIFTx;
    uint       w,IPHdrLen,UDPLen;
    IPN        IPSrc,IPDst;
    IPHDR      *pIpHdr;
    UDPHDR     *pUdpHdr;
    uint       MaxFlag;

    /* Get the IP header len */
    IPHdrLen = pPkt->IpHdrLen;

    /* Assign an IP header pointer */
    pIpHdr = (IPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Assign a UDP header pointer */
    pUdpHdr = (UDPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset + IPHdrLen);

    /* Count the total number of packets in */
    udps.RcvTotal++;

    /* Get the total length of the TCP message */
    UDPLen = (uint)(HNC16( pIpHdr->TotalLen )) - IPHdrLen;

    /* Check for packet too small */
    if( UDPLen < UDPHDR_SIZE )
    {
        udps.RcvShort++;
        PBM_free( pPkt );
        return;
    }

    /* Check for bad header length */
    if( pUdpHdr->Length != HNC16(UDPLen) )
    {
        udps.RcvBadLen++;
        PBM_free( pPkt );
        return;
    }

    /* We need some stuff for the pseudo header */
    /* Get source and destination */
    IPSrc = RdNet32(&pIpHdr->IPSrc);
    IPDst = RdNet32(&pIpHdr->IPDst);

    if( pUdpHdr->UDPChecksum )
    {
        /* Init pseudo header for checksum */
        upseudo.IPSrc    = IPSrc;
        upseudo.IPDst    = IPDst;
        upseudo.Null     = 0;
        upseudo.Protocol = 17;
        upseudo.Length   = pUdpHdr->Length;

        /* Verify checksum */
        w = (uint)pUdpHdr->UDPChecksum;
        UdpChecksum( pUdpHdr );
        if( w != (uint)pUdpHdr->UDPChecksum )
        {
            udps.RcvBadSum++;
            PBM_free( pPkt );
            return;
        }
    }

    /* Get the actual number of bytes to "receive" */
    UDPLen -= UDPHDR_SIZE;

    /* Set the Frag Parms to hand off to a SB */
    pPkt->Aux1 = 0x10000 | (UINT32)(pUdpHdr->SrcPort);
    pPkt->Aux2 = IPSrc;
    pPkt->ValidLen = UDPLen;
    pPkt->DataOffset += IPHdrLen+UDPHDR_SIZE;

    /* Handle BROADCAST/MULTICAST */
    if( IPDst == INADDR_BROADCAST || IN_MULTICAST( IPDst ) ||
            (pPkt->Flags & (FLG_PKT_MACMCAST|FLG_PKT_MACBCAST)) )
    {
        /* Multicast Packet */
        /* We have to copy the frag for each socket with a matchng PCB */
        hSock = SockPcbResolveChain( 0, SOCKPROT_UDP, 0, IPDst,
                                     (uint)pUdpHdr->DstPort, IPSrc,
                                     (uint)pUdpHdr->SrcPort );
        w = 0;          /* Recv Flag */
        while( hSock )
        {
            /* Get the handle to the next match (so we know if we have one) */
            hSockNext = SockPcbResolveChain( hSock, SOCKPROT_UDP, 0, IPDst,
                                             (uint)pUdpHdr->DstPort, IPSrc,
                                             (uint)pUdpHdr->SrcPort );

            /* Get the broadcast IF of this socket */
            hIFTx = SockGetIFTx( hSock );

            /* If there is a specified BCAST device, and the packet's */
            /* Rx device doesn't match it, then we ignore the packet */
            if( hIFTx && ( hIFTx != pPkt->hIFRx ) )
            {
                hSock = hSockNext;
                continue;
            }

            /* Flag that we have matched a socket */
            w = 1;

            /* Get the Linear Receive Buffer */
            hSBRx = SockGetRx( hSock );

            if( SBGetSpace( hSBRx ) < (INT32)UDPLen )
                udps.RcvFull++;
            else
            {
                /* Copy the frag if there may be more matches */
                /* Else this is our last time through the loop */
                if( !hSockNext || !(pPktCopy = PBM_copy( pPkt )) )
                {
                    pPktCopy = pPkt;
                    pPkt = 0;
                    hSockNext = 0;
                }

                /* Give the frag to the SB */
                SBWrite( hSBRx, (INT32)UDPLen, 0, pPktCopy );

                /* Notify the Socket */
                SockNotify( hSock, SOCK_NOTIFY_RCVDATA );
            }

            /* Check next matching socket */
            hSock = hSockNext;
        }

        /* If we didn't match anyone, count it */
        if( !w )
            udps.RcvNoPortB++;

        /* Free the packet if we didn't use it */
        if( pPkt )
            PBM_free( pPkt );

        return;
    }

    /* Find a PCB for this packet */
    hSock = SockPcbResolve( SOCKPROT_UDP, IPDst, (uint)pUdpHdr->DstPort,
			    IPSrc, (uint)pUdpHdr->SrcPort, SOCK_RESOLVE_BEST,
			    &MaxFlag );

    /* If there's no PCB, send an ICMP error */
    if( !hSock )
    {
        if( !(pPkt->Flags & FLG_PKT_MACBCAST) && UDP_SEND_ICMP_PORTUNREACH)
            ICMPGenPacket( pIpHdr, pPkt->hIFRx, ICMP_UNREACH,
                           ICMP_UNREACH_PORT, 0 );
        udps.RcvNoPort++;
        PBM_free( pPkt );
        return;
    }

    /* Get the Receive Socket Buffer */
    hSBRx = SockGetRx( hSock );

    /* If there's no space on the receiver queue, then discard the packet */
    /* with an ICMP error */
    if( SBGetSpace( hSBRx ) < (INT32)UDPLen )
    {
        if( !(pPkt->Flags & FLG_PKT_MACBCAST) )
            ICMPGenPacket( pIpHdr, pPkt->hIFRx,
                           ICMP_SOURCEQUENCH, 0, 0 );
        udps.RcvFull++;
        PBM_free( pPkt );
        return;
    }

    /* Give the frag to the SB */
    SBWrite( hSBRx, (INT32)UDPLen, 0, pPkt );

    /* Notify the Socket */
    SockNotify( hSock, SOCK_NOTIFY_RCVDATA );
}

