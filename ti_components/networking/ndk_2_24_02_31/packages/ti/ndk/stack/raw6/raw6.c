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
 * ======== raw6.c ========
 *
 * The file has functions which handle the RAW6 sockets.
 *
 */


#include <stkmain.h>

#ifdef _INCLUDE_IPv6_CODE

/**********************************************************************
 *************************** Global Variables *************************
 **********************************************************************/

/* RAW Statistics for IPv6. */
RAWSTATS    raw6_stats;

/**********************************************************************
 ***************************** RAW6 Functions *************************
 **********************************************************************/

/** 
 *  @b Description
 *  @n  
 *      The function is called to transmit a RAW packet over an IPv6 network.
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
 *      Error   -   Non Zero
 */
int Raw6Output( HANDLE hSock, UINT8 *buf, INT32 size, INT32 *pRetSize)
{
    PBM_Pkt*    pPkt;
    SOCK6*      ps;
    HANDLE      hRoute6;
    IP6N        srcAddr;
    IP6N        dstAddr;

    /* Get the socket Information. */
    ps = (SOCK6 *)hSock;

    /* Create the packet for the payload. The Protocol is inherited from the 
     * SOCKET Protocol Family. */
    pPkt = Sock6CreatePacket (hSock, (uint)size, ps->Protocol);
    if(pPkt == NULL)
    {
        raw6_stats.SndNoPacket++;
        *pRetSize = 0;
        return ENOBUFS;
    }

    /* Get the route information associated with the socket. */
    hRoute6 = Sock6GetRoute (hSock);

    /* Copy the data payload. */ 
    mmCopy ((pPkt->pDataBuffer + pPkt->DataOffset + pPkt->IpHdrLen), buf, (uint)size);

    /* Increment the statistics. */ 
    raw6_stats.SndTotal++;

    /* RFC 2292 Section 3.1 states that the stack should calculate and insert the
     * ICMPv6 Checksum. For all other RAW6 sockets; this is done through the 
     * IPV6_CHECKSUM option. */
    if (ps->Protocol == IPPROTO_ICMPV6)
    {
        PSEUDOV6    pseudo_hdr;
        IPV6HDR*    ptr_ipv6hdr;
        ICMPV6HDR*  ptr_icmpv6hdr;

        /* Get the IPv6 Header. */
        ptr_ipv6hdr = (IPV6HDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

        /* Get the ICMPV6 Header. */
        ptr_icmpv6hdr = (ICMPV6HDR *)(pPkt->pDataBuffer + pPkt->DataOffset + pPkt->IpHdrLen);

        /*
         * NOTE: use mmCopy to copy the 16 byte IP6N addresses out of ptr_ipv6hdr
         * as this data is potentially un-aligned (SDOCM00097361)
         */
        mmCopy((char *)&srcAddr, (char *)&ptr_ipv6hdr->SrcAddr, sizeof(IP6N));
        mmCopy((char *)&dstAddr, (char *)&ptr_ipv6hdr->DstAddr, sizeof(IP6N));


        /* Initialize and populate the PSEUDO Header. */
        pseudo_hdr.SrcAddr = srcAddr;
        pseudo_hdr.DstAddr = dstAddr;
        pseudo_hdr.PktLen  = htons(pPkt->ValidLen);
        pseudo_hdr.Rsvd[0] = 0;
        pseudo_hdr.Rsvd[1] = 0;
        pseudo_hdr.Rsvd[2] = 0;
        pseudo_hdr.NxtHdr  = IPPROTO_ICMPV6;

        /* Initialize and compute the checksum. */
        ptr_icmpv6hdr->Checksum = 0;
        ptr_icmpv6hdr->Checksum = IPv6Layer4ComputeChecksum ((UINT8 *)ptr_icmpv6hdr, &pseudo_hdr);
    }
    else
    {
        /* TODO: This needs to be handled along with the IPV6_CHECKSUM Socket Option. */
    }

    /* Set the Route Information in the socket. */
    PBM_setRoute6 (pPkt, hRoute6);

    /* Pass the packet to the IPv6 Layer for transmission. */ 
    IPv6TxPacket (pPkt, 0);

    /* The packet has been successfully transmitted */
    *pRetSize = size;
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function is called when a RAW packet is received over the IPv6
 *      Network.
 *
 *  @param[in]  pPkt
 *      The packet received.
 *  @param[in]  ptr_ipv6hdr
 *      The IPv6 Header of the received packet.
 *  @param[in]  Protocol
 *      The Layer4 Protocol received. This is not necessarily the same as the
 *      Next Header in the IPv6 header.
 *
 *  @retval
 *      Not Applicable.
 */
void Raw6Input (PBM_Pkt* pPkt, IPV6HDR* ptr_ipv6hdr, UINT8 Protocol)
{
    HANDLE      hSock;
    HANDLE      hSockNext;
    HANDLE      hSBRx;
    UINT16      PayloadLength;
    PBM_Pkt*    pPktCopy;
    IP6N        srcAddr;
    IP6N        dstAddr;
            
    /* Increment the statistics. */ 
    raw6_stats.RcvTotal++;

    /* Get the length of the RAW packet. */ 
    PayloadLength = ntohs(ptr_ipv6hdr->PayloadLength);

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses out of ptr_ipv6hdr
     * as this data is potentially un-aligned (SDOCM00097361)
     */
    mmCopy((char *)&srcAddr, (char *)&ptr_ipv6hdr->SrcAddr, sizeof(IP6N));
    mmCopy((char *)&dstAddr, (char *)&ptr_ipv6hdr->DstAddr, sizeof(IP6N));

    /* Copy the Source address for "PEER" Information. */
    mmCopy((void *)&pPkt->SrcAddress,(void *)&ptr_ipv6hdr->SrcAddr, sizeof(IP6N));

    /* Control comes here; implies that the packet is a UNICAST packet; we need to get a
     * matching socket handle for the packet. For RAW Sockets there can be multiple 
     * recepients. We start the initial search from the head of the list. */
    hSock = Sock6PcbResolveChain (0, SOCKPROT_RAW, Protocol, dstAddr, 0, srcAddr, 0);
    if (hSock == 0)
    {
        /* There is no socket waiting for this packet. Drop it! */
        PBM_free (pPkt);
        return;
    }

    do 
    {
        /* Get the next socket handle. In this case we start the search from the previous handle. */
        hSockNext = Sock6PcbResolveChain (hSock, SOCKPROT_RAW, Protocol, dstAddr, 
                                          0, srcAddr, 0);

        /* Get the socket receive buffer. */
        hSBRx = Sock6GetRx (hSock);

        /* Make sure there is space in the receive buffer. */
        if(SB6GetSpace(hSBRx) < (INT32)PayloadLength)
        {
            /* Error: There is no space in the receive buffer; increment the statistics and abort. */
            raws.RcvFull++;
        }
        else
        {
            /* Check if the packet needs to be copied or not? Are there more sockets waiting for
             * the packet?  */
            if (hSockNext == 0)
            {
                /* NO. In this case we can send the original packet to the SOCKET */
                pPktCopy = pPkt;
            }
            else
            {
                /* YES. In this case we need to copy the packet. */   
                pPktCopy = PBM_copy (pPkt);
                if (pPktCopy == NULL)
                {
                    /* FATAL Error: Drop processing the current packet. */
                    PBM_free (pPkt);
                    return;
                }
            }

            /* Give the packet to the Socket Buffer Module */
            SB6Write( hSBRx, (INT32)PayloadLength, 0, pPktCopy );
 
            /* Notify the socket layer that data has been received. */ 
            Sock6Notify( hSock, SOCK_NOTIFY_RCVDATA );
        }

        /* Get the next socket; we start the search from the next socket. */
        hSock = hSockNext;
    }while (hSock != 0);

    /* Control comes here; implies that the packet has been passed to all the sockets */
    return;
}

#endif /* _INCLUDE_IPv6_CODE */

