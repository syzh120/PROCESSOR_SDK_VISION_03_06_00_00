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
 * ======== udp6.c ========
 *
 * The file implements the UDP protocol over IPv6.
 *
 */


#include <stkmain.h>

#ifdef _INCLUDE_IPv6_CODE

/**********************************************************************
 *************************** Global Variables *************************
 **********************************************************************/

/* UDP Statistics for the IPv6 UDP stack. */
UDPSTATS udp6_stats;

/**********************************************************************
 ***************************** UDP6 Functions *************************
 **********************************************************************/

static void processMulticast(PBM_Pkt * pPkt, IP6N srcAddr, int srcPort,
                             IP6N dstAddr, int dstPort, int UDPLen);

/**
 *  @b Description
 *  @n
 *      The function is called to transmit a UDP packet over an IPv6 network.
 *
 *  @param[in]  hSock
 *      Socket handle using which the packet is sent out.
 *  @param[in]  buf
 *      Data Buffer which is to be sent out.
 *  @param[in]  size
 *      Length of the data buffer to be sent out.
 *  @param[out] pRetSize
 *      Actual Length of data sent out.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   Non Zero
 */
int Udp6Output( HANDLE hSock, UINT8 *buf, INT32 size, INT32 *pRetSize )
{
    PBM_Pkt*        pPkt;
    HANDLE          hRoute6;
    UINT16          mss;
    UDPHDR*         pUdpHdr;
    uint            length;
    SOCK6*          pSock;
    PSEUDOV6        pseudo_hdr;

    /* Initialize the return value. */
    *pRetSize = 0;

    /* Get the socket Information. */
    pSock = (SOCK6 *)hSock;

    /* Is the socket associated with a Transmission Buffer Size? */
    if (pSock->TxBufSize == 0)
    {
        /* No; none is specified. Check if there is a ROUTE associated with the socket? */
        hRoute6 = Sock6GetRoute (hSock);
        if (hRoute6)
        {
            /* YES. Get the MTU associated with the Route. */
            mss = (INT32)Rt6GetMTU (hRoute6);
        }
        else
        {
            mss = UDP_MSS_DEFAULT;
        }
    }
    else
    {
        /* There is a transmit buffer size configured. */
        mss = pSock->TxBufSize;

        /* Get the ROUTE6 Information. */
        hRoute6 = Sock6GetRoute (hSock);
    }

    /* Subtract off the IP Header + Extension headers Size and UDP Header Size. */
    mss -= Sock6GetIpHdrSize(hSock) + UDPHDR_SIZE;
    if( size > mss )
        return EMSGSIZE;

    /* Allocate memory for the packet. */
    length = UDPHDR_SIZE + (uint)size;
    if( !(pPkt = Sock6CreatePacket( hSock, length, IPPROTO_UDP )))
    {
        udps.SndNoPacket++;
        PBM_free (pPkt);
        return ENOBUFS;
    }

    /* Store the ROUTE6 Information in the packet itself and increment the reference
     * counter for the ROUTE6 Entry since now the packet is carrying the ROUTE6 Handle. */
    PBM_setRoute6 (pPkt, hRoute6);

    /* Get the pointer to the UDP Header. */
    pUdpHdr = (UDPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset + pPkt->IpHdrLen);

    /* Populate the UDP Header. */
    pUdpHdr->SrcPort = Sock6GetLPort(hSock);
    pUdpHdr->DstPort = Sock6GetFPort(hSock);
    pUdpHdr->Length  = HNC16(length);

    /* Copy the data into the data payload. */
    mmCopy( ((UINT8 *)pUdpHdr)+UDPHDR_SIZE, buf, (uint)size);

    /* Create the Pseudo Header for checksum calculations. */
    pseudo_hdr.SrcAddr = Sock6GetLIP(hSock);
    pseudo_hdr.DstAddr = Sock6GetFIP(hSock);
    pseudo_hdr.PktLen  = pUdpHdr->Length;
    pseudo_hdr.Rsvd[0] = 0;
    pseudo_hdr.Rsvd[1] = 0;
    pseudo_hdr.Rsvd[2] = 0;
    pseudo_hdr.NxtHdr  = IPPROTO_UDP;

    /* Compute the ICMPv6 Checksum. */
    pUdpHdr->UDPChecksum = 0;
    pUdpHdr->UDPChecksum = IPv6Layer4ComputeChecksum ((UINT8 *)pUdpHdr, &pseudo_hdr);

    /* Increment the transmission statistics. */
    udp6_stats.SndTotal++;

    /* Pass the packet to the IPv6 Layer for transmission. */
    IPv6TxPacket (pPkt, 0);

    /* The packet has been successfully transmitted */
    *pRetSize = size;
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is the receive handler which is invoked when a UDP packet
 *      is received over IPv6.
 *
 *  @param[in]  pPkt
 *      The actual UDP6 packet received.
 *  @param[in]  ptr_ipv6hdr
 *      The IPv6 Header of the received UDP packet.
 *
 *  @retval
 *      Not Applicable.
 */
void Udp6Input (PBM_Pkt* pPkt, IPV6HDR* ptr_ipv6hdr)
{
    UDPHDR*     ptr_udpHdr;
    UINT16      PayloadLength;
    PSEUDOV6    pseudo_hdr;
    UINT16      checksum;
    HANDLE      hSock;
    HANDLE      hSBRx;
    IP6N        srcAddr;
    IP6N        dstAddr;
    uint        MaxFlag;

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses out of ptr_ipv6hdr
     * as this data is potentially un-aligned (SDOCM00097361)
     */
    mmCopy((char *)&srcAddr, (char *)&ptr_ipv6hdr->SrcAddr, sizeof(IP6N));
    mmCopy((char *)&dstAddr, (char *)&ptr_ipv6hdr->DstAddr, sizeof(IP6N));

    /* Get the pointer to the UDP header. */
    ptr_udpHdr = (UDPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Increment the number of UDP Packets received. */
    udp6_stats.RcvTotal++;

    /* Get the length of the UDP packet. */
    PayloadLength = ntohs(ptr_ipv6hdr->PayloadLength);

    /* Check for packet too small */
    if( PayloadLength < UDPHDR_SIZE )
    {
        /* Packet is too small; cleanup and return. */
        udp6_stats.RcvShort++;
        PBM_free( pPkt );
        return;
    }

    /* Get the original checksum. */
    checksum = ptr_udpHdr->UDPChecksum;
    if( checksum == 0xFFFF )
        checksum = 0;

    /* Create the Pseudo Header for checksum calculations. */
    pseudo_hdr.SrcAddr = srcAddr;
    pseudo_hdr.DstAddr = dstAddr;
    pseudo_hdr.PktLen  = htons(pPkt->ValidLen);
    pseudo_hdr.Rsvd[0] = 0;
    pseudo_hdr.Rsvd[1] = 0;
    pseudo_hdr.Rsvd[2] = 0;
    pseudo_hdr.NxtHdr  = IPPROTO_UDP;

    /* Before we compute the checksum; initialize it to 0. */
    ptr_udpHdr->UDPChecksum = 0;
    ptr_udpHdr->UDPChecksum = IPv6Layer4ComputeChecksum ((UINT8 *)ptr_udpHdr, &pseudo_hdr);

    /* Validate the checksum. */
    if( checksum != ptr_udpHdr->UDPChecksum)
    {
        /* Checksums are not correct; packet is dropped */
        udp6_stats.RcvBadSum++;
        PBM_free (pPkt);
        return;
    }

    /* Skip the UDP Header. */
    pPkt->DataOffset += (sizeof(UDPHDR));
    pPkt->ValidLen   -= (sizeof(UDPHDR));

    /* Compute the actual "data" payload. */
    PayloadLength = PayloadLength - UDPHDR_SIZE;

    /* Is the Destination Address MULTICAST? */
    if (IPv6IsMulticast(dstAddr)) {
        processMulticast(pPkt, srcAddr, ptr_udpHdr->SrcPort,
                         dstAddr, ptr_udpHdr->DstPort, PayloadLength);

        return;
    }

    /* Control comes here; implies that the packet is a UNICAST packet; we need to get a
     * matching socket handle for the packet. */
    hSock = Sock6PcbResolve (SOCKPROT_UDP, dstAddr, ptr_udpHdr->DstPort,
                             srcAddr, ptr_udpHdr->SrcPort, SOCK_RESOLVE_BEST, &MaxFlag);
    if (hSock == 0)
    {
        /* There is no matching socket for this combination. In this case we send out the
         * Destination Unreachable Message (Code = ICMPV6_DST_UNREACH_PORT) */
        ICMPv6SendDstUnreachable (ICMPV6_DST_UNREACH_PORT, pPkt);

        /* Increment the statistics. */
        udp6_stats.RcvNoPort++;

        /* Cleanup the original packet. */
        PBM_free (pPkt);
        return;
    }

    /* Get the Receive Socket Buffer and ensure there is space in the receiver socket queue
     * to be abke to handle the packet. */
    hSBRx = Sock6GetRx( hSock );

    /* Ensure there is space in the socket buffer. */
    if (SB6GetSpace( hSBRx ) < PayloadLength)
    {
        udps.RcvFull++;
        PBM_free( pPkt );
        return;
    }

    /* Copy the Source address/port for "PEER" Information. */
    mmCopy((void *)&pPkt->SrcAddress,(void *)&srcAddr, sizeof(IP6N));
    pPkt->SrcPort = ptr_udpHdr->SrcPort;

    /* Give the frag to the Socket Buffer. */
    SB6Write( hSBRx, pPkt->ValidLen, 0, pPkt );

    /* Notify the Socket */
    Sock6Notify( hSock, SOCK_NOTIFY_RCVDATA );
    return;
}

static void processMulticast(PBM_Pkt * pPkt, IP6N srcAddr, int srcPort,
                             IP6N dstAddr, int dstPort, int UDPLen)
{
    HANDLE      hSock;
    HANDLE      hSockNext;
    HANDLE      hSBRx;
    PBM_Pkt *   pPktCopy;
    int         w;

    hSock = Sock6PcbResolveChain(0, SOCKPROT_UDP, 0, dstAddr,
                                 dstPort, srcAddr, srcPort);

    w = 0;          /* Recv Flag */
    while (hSock) {
        /* Get the handle to the next match (so we know if we have one) */
        hSockNext = Sock6PcbResolveChain(hSock, SOCKPROT_UDP, 0, dstAddr,
                                         dstPort, srcAddr, srcPort);

        /* Flag that we have matched a socket */
        w = 1;

        /* Get the Linear Receive Buffer */
        hSBRx = Sock6GetRx(hSock);

        if (SBGetSpace(hSBRx) < (INT32)UDPLen) {
            udps.RcvFull++;
        }
        else {
            /* Copy the frag if there may be more matches */
            /* Else this is our last time through the loop */
            if (!hSockNext || !(pPktCopy = PBM_copy( pPkt ))) {
                pPktCopy = pPkt;
                pPkt = 0;
                hSockNext = 0;
            }

            /* Give the frag to the SB */
            SBWrite(hSBRx, (INT32)UDPLen, 0, pPktCopy);

            /* Copy the Source address/port for "PEER" Information. */
            mmCopy((void *)&pPktCopy->SrcAddress, (void *)&srcAddr,
                   sizeof(IP6N));
            pPktCopy->SrcPort = srcPort;

            /* Notify the Socket */
            Sock6Notify(hSock, SOCK_NOTIFY_RCVDATA);
        }

        /* Check next matching socket */
        hSock = hSockNext;
    }

    /* If we didn't match anyone, count it */
    if (!w) {
        udps.RcvNoPortB++;
    }

    /* Free the packet if we didn't use it */
    if (pPkt) {
        PBM_free(pPkt);
    }

    return;
}

#endif /* _INCLUDE_IPv6_CODE */
