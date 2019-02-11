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
 * ======== icmpv6in.c ========
 *
 * The file handles the reception of ICMPv6 Packets.
 *
 */

#include <stkmain.h>

#ifdef _INCLUDE_IPv6_CODE

/** 
 *  @b Description
 *  @n  
 *      The function process the ICMPv6 Echo Request Packets.
 *
 *  @param[in]  pPkt
 *      Pointer to the entire ICMPv6 Packet.
 *  @param[in]  ptr_ipv6hdr
 *      Pointer to the IPv6 Header.
 *  @sa
 *      RFC 2463 Section 4.1
 *
 *  @retval
 *      0   -   Success
 *  @retval
 *      <0   -  Error
 */
static int ICMPv6RecvEchoRequest (PBM_Pkt* pPkt, IPV6HDR* ptr_ipv6hdr)
{
    ICMPV6_ECHO_HDR*    ptr_echoHdr;
    PSEUDOV6            pseudo_hdr;
    PBM_Pkt*            pPkt2 = NULL;
    IPV6HDR*            ptr_ipv6hdr2 = NULL;
    ICMPV6_ECHO_HDR*    ptr_echoHdr2 = NULL;
    IP6N                SrcAddressUsed;
    IP6N                srcAddr;
    IP6N                dstAddr;

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses out of ptr_ipv6hdr
     * as this data is potentially un-aligned (SDOCM00097361)
     */
    mmCopy((char *)&srcAddr, (char *)&ptr_ipv6hdr->SrcAddr, sizeof(IP6N));
    mmCopy((char *)&dstAddr, (char *)&ptr_ipv6hdr->DstAddr, sizeof(IP6N));

    /* Get the pointer to the ECHO Request Header. */
    ptr_echoHdr = (ICMPV6_ECHO_HDR *) (pPkt->pDataBuffer + pPkt->DataOffset);

    /* Validate the packet: The Code should be 0 */
    if (ptr_echoHdr->Code != 0)
        return -1;

    /* Determine the source address to be used in the packet. Check if the packet was 
     * destined to a multicast address*/
    if (IPv6IsMulticast(dstAddr) == 1)
    {
        /* RFC 2463 Section 2.2 states that if the packet destination address is
         * MULTICAST we need to send the Source Address of the REPLY 
         * to the UNICAST Address of the interface. */
        if(Bind6GetLinkLocalAddress(pPkt->hIFRx, &SrcAddressUsed) < 0)
            return -1;
    }
    else
    {
        /* This is a UNICAST packet; we can reuse the destination address as is. */
        SrcAddressUsed = dstAddr;
    }

    /* Create the ECHO REPLY packet 
     * pPkt->ValidLen now contains only L4 header (ICMPv6 header) size 
     * + data.
     */
    if( !(pPkt2 = NIMUCreatePacket( pPkt->ValidLen + IPv6HDR_SIZE)) )
        return -1;

    /* Get the IP header pointer for the new packet */
    ptr_ipv6hdr2 = (IPV6HDR *)(pPkt2->pDataBuffer + pPkt2->DataOffset);

    /* Fixup packet information 
     * ValidLen should now contain length of L4 data + header only.
     * The IPv6 header size will be added on in IPv6TxPacket
     * during packet transmission.
     */
    pPkt2->ValidLen = pPkt->ValidLen;

    /* We will reuse the original packet to create a reply and send it out. 
     * Some minor modifications need to be done to the packet. 
     *  1.  Swap the Destination and Source Address in the IPv6 Header 
     *  2.  Copy IPv6 header + ICMPv6 header + data step by step 
     *      from original packet skipping out any extension headers
     *      present in the original packet between the IPv6 header
     *      and ICMPv6 header itself.
     *  3.  Change the ICMPv6 Type from ECHO Request to ECHO Reply.
     *  4.  Recompute the ICMPv6 Checksum. 
     */

    /* Step 1: Copy the IPv6 Header from original packet */
    mmCopy ((void *) ptr_ipv6hdr2, (void *)ptr_ipv6hdr, IPv6HDR_SIZE);

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses into ptr_ipv6hdr2
     * as this data is potentially un-aligned (SDOCM00097361)
     */
    /* Step 1: Swap the Destination and Source Address */
    mmCopy((char *)&ptr_ipv6hdr2->DstAddr, (char *)&srcAddr, sizeof(IP6N));
    mmCopy((char *)&ptr_ipv6hdr2->SrcAddr, (char *)&SrcAddressUsed, sizeof(IP6N));

    ptr_ipv6hdr2->NextHeader    = IPPROTO_ICMPV6;
    ptr_ipv6hdr2->PayloadLength = htons(pPkt->ValidLen);

    /* Step 2: Get the pointer to ICMPv6 header. ICMPv6 header
     * now follows the IPv6 header immediately. */
    ptr_echoHdr2 = (ICMPV6_ECHO_HDR *)(((UINT8 *)ptr_ipv6hdr2) + IPv6HDR_SIZE);

    /* Step 2: Copy the ICMPv6 ECHO Header from original packet */
    mmCopy ((void *) ptr_echoHdr2, (void *)ptr_echoHdr, sizeof(ICMPV6_ECHO_HDR));

    /* Step 3: Change the ICMPv6 Type to ECHO REPLY */
    ptr_echoHdr2->Type = ICMPV6_ECHO_REPLY;

	/* Step 2: Copy the ICMPv6 Data from original packet after the
     * ICMPv6 header. */
    mmCopy ((void *) ((UINT8 *)ptr_echoHdr2 + sizeof(ICMPV6_ECHO_HDR)), 
            (void *)((UINT8 *)ptr_echoHdr + sizeof(ICMPV6_ECHO_HDR)) , 
            pPkt->ValidLen - sizeof(ICMPV6_ECHO_HDR));

    /* Step 4: Create the Pseudo Header for checksum calculations. */
    mmCopy((char *)&pseudo_hdr.SrcAddr, (char *)&ptr_ipv6hdr2->SrcAddr, sizeof(IP6N));
    mmCopy((char *)&pseudo_hdr.DstAddr, (char *)&ptr_ipv6hdr2->DstAddr, sizeof(IP6N));

    pseudo_hdr.PktLen  = ptr_ipv6hdr2->PayloadLength;
    pseudo_hdr.Rsvd[0] = 0;
    pseudo_hdr.Rsvd[1] = 0;
    pseudo_hdr.Rsvd[2] = 0;
    pseudo_hdr.NxtHdr  = IPPROTO_ICMPV6;

    /* Step 4: Compute the ICMPv6 Checksum. */
    ptr_echoHdr2->Checksum = 0;
    ptr_echoHdr2->Checksum = IPv6Layer4ComputeChecksum ((UINT8 *)ptr_echoHdr2, &pseudo_hdr);

    /* Increment the stats */
    icmp6stats.OutMsgs++;

    /* Pass the packet to the IPv6 Layer for transmission. */
    IPv6TxPacket (pPkt2, 0);

    /* Free the original packet */
	PBM_free(pPkt);
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function is the interface routine which hooks ICMPv6 Error Packets with the
 *      socket layer. 
 *
 *  @param[in]  Code
 *      Error Code which is to be passed to the socket layer.
 *  @param[in]  ptr_Orgipv6hdr
 *      Pointer to the ORIGINAL IPv6 Header which caused the error.
 *
 *  @retval
 *      Not Applicable.
 */
static void ICMPv6SocketErrorInterface (UINT32 Code, IPV6HDR* ptr_Orgipv6hdr)
{
    HANDLE  hSock;
    HANDLE  hSockNext;
    UINT32  SockProt;
    UINT32  LPort = 0;
    UINT32  FPort = 0;
    IP6N        srcAddr;
    IP6N        dstAddr;

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses out of ptr_ipv6hdr
     * as this data is potentially un-aligned (SDOCM00097361)
     */
    mmCopy((char *)&srcAddr, (char *)&ptr_Orgipv6hdr->SrcAddr, sizeof(IP6N));
    mmCopy((char *)&dstAddr, (char *)&ptr_Orgipv6hdr->DstAddr, sizeof(IP6N));


    /* Check the Next Header field? This check here will fail if the ORIGINAL Packet had 
     * extension headers configured. */
    if((ptr_Orgipv6hdr->NextHeader == IPPROTO_UDP) || (ptr_Orgipv6hdr->NextHeader == IPPROTO_TCP))
    {
        /* Extract out the inner LAYER4 header; TCP and UDP Headers are the same because we
         * are only interested in extracting out the port information. */
        UDPHDR* ptr_OrigUDPHdr = (UDPHDR *) ((UINT8 *)ptr_Orgipv6hdr + sizeof (IPV6HDR));

        /* Initialize the Socket Protocol Family we need to search. */
        SockProt = (ptr_Orgipv6hdr->NextHeader == IPPROTO_UDP) ? SOCKPROT_UDP : SOCKPROT_TCP;

        /* Extract and initialize the Local/Foreign Port Information. */
        LPort = ptr_OrigUDPHdr->SrcPort;
        FPort = ptr_OrigUDPHdr->DstPort;
    }
    else
    {
        /* This could be a RAW Socket; check the RAW Socket chain */
        SockProt = SOCKPROT_RAW;
    }

    /* With the information at hand we search for a possible socket match. */
    hSock = Sock6PcbResolveChain (0, SockProt, ptr_Orgipv6hdr->NextHeader, srcAddr,
                                  LPort, dstAddr, FPort);

    /* There can exist multiple socket recipients; so we cycle through all of them here. */
    while (hSock != 0)
    {
        /* Search for the next match. */
        hSockNext = Sock6PcbResolveChain (hSock, SockProt, ptr_Orgipv6hdr->NextHeader, 
                                          srcAddr, LPort, dstAddr, FPort);

        /* Inform the socket layer about the error */
        Sock6PrCtlError(hSock, Code);

        /* Proceed with the next socket. */
        hSock = hSockNext;
    }
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function is called to receive and process a Destination
 *      Unreachable packet.
 *
 *  @param[in]  pPkt
 *      Pointer to the entire ICMPv6 Packet.
 *
 *  @retval
 *      0   -   Success
 *  @retval
 *      <0   -  Error
 */
static int ICMPv6RecvDstUnreachable (PBM_Pkt* pPkt)
{
    ICMPV6_DST_UNREACHABLE_HDR* ptr_DstUnreachHdr;
    IPV6HDR*                    ptr_Orgipv6hdr;
    UINT32                      Code;

    /* Get the pointer to the Destination Unreachable Packet. */
    ptr_DstUnreachHdr = (ICMPV6_DST_UNREACHABLE_HDR *) (pPkt->pDataBuffer + pPkt->DataOffset);

    /* Decide the Socket Error Code here. */
    switch (ptr_DstUnreachHdr->Code)
    {
        case 0: 
        {
            /* No Route Exists to the destination. */
            Code = EHOSTUNREACH;
            break;
        }
        case 1: 
        {
            /* Communication is ADMIN prohibited. */
            Code = EACCES;
            break;
        }
        case 3:
        {
            /* Address is Unreachable. */
            Code = EHOSTUNREACH;
            break;
        }
        case 4:
        {
            /* Port is Unreachable. */
            Code = ECONNREFUSED;
            break;
        }
        default:
        {
            /* All other cases are invalid. */
            return -1;
        } 
    }

    /* Get the inner packet IPv6 Header. */
    ptr_Orgipv6hdr = (IPV6HDR *) (pPkt->pDataBuffer + pPkt->DataOffset + sizeof (ICMPV6_DST_UNREACHABLE_HDR));

    /* Notify the socket layer about the error. */
    ICMPv6SocketErrorInterface (Code, ptr_Orgipv6hdr);

    /* Clean out the packet memory. */
    PBM_free (pPkt);
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function is called to receive and process a Time Exceeded
 *      message.
 *
 *  @param[in]  pPkt
 *      Pointer to the entire ICMPv6 Packet.
 *
 *  @retval
 *      0   -   Success
 *  @retval
 *      <0   -  Error
 */
static int ICMPv6RecvTimeExceeded (PBM_Pkt* pPkt)
{
    ICMPV6_TIME_EXCEEDED_HDR*   ptr_icmpv6TimeExceededHdr;
    IPV6HDR*                    ptr_Orgipv6hdr;
    UINT32                      Code;

    /* Get the pointer to the Time Exceeded Header. */
    ptr_icmpv6TimeExceededHdr = (ICMPV6_TIME_EXCEEDED_HDR *) (pPkt->pDataBuffer + pPkt->DataOffset);

    /* Decide the Socket Error Code here. */
    switch (ptr_icmpv6TimeExceededHdr->Code)
    {
        case 0: 
        {
            /* Hop Limit Exceeded in Transit */ 
            Code = EHOSTUNREACH;
            break;
        }
        case 1: 
        {
            /* Fragmentation reassembly time exceeded. */
            Code = EHOSTUNREACH;
            break;
        }
        default:
        {
            /* All other cases are invalid. */
            return -1;
        } 
    }

    /* Get the inner packet IPv6 Header. */
    ptr_Orgipv6hdr = (IPV6HDR *) (pPkt->pDataBuffer + pPkt->DataOffset + sizeof (ICMPV6_TIME_EXCEEDED_HDR));

    /* Notify the socket layer about the error. */
    ICMPv6SocketErrorInterface (Code, ptr_Orgipv6hdr);

    /* Clean out the packet memory. */
    PBM_free (pPkt);
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function is called to receive and process a Parameter Problem
 *      message.
 *
 *  @param[in]  pPkt
 *      Pointer to the entire ICMPv6 Packet.
 *
 *  @retval
 *      0   -   Success
 *  @retval
 *      <0   -  Error
 */
static int ICMPv6RecvParamProblem (PBM_Pkt* pPkt)
{
    ICMPV6_PARAM_PROB_HDR*      ptr_icmpv6ParamProblem;
    IPV6HDR*                    ptr_Orgipv6hdr;
    UINT32                      Code;

    /* Get the pointer to the Parameter Problem Header */
    ptr_icmpv6ParamProblem = (ICMPV6_PARAM_PROB_HDR *) (pPkt->pDataBuffer + pPkt->DataOffset);

    /* Decide the Socket Error Code here. */
    switch (ptr_icmpv6ParamProblem->Code)
    {
        case 0: 
        {
            /* Errorneous Header Field */
            Code = EOPNOTSUPP;
            break;
        }
        case 1: 
        {
            /* Unrecognized Next Header. */
            Code = EOPNOTSUPP;
            break;
        }
        case 3:
        {
            /* Unrecognized IPv6 Option */
            Code = EOPNOTSUPP;
            break;
        }
        default:
        {
            /* All other cases are invalid. */
            return -1;
        } 
    }

    /* Get the inner packet IPv6 Header. */
    ptr_Orgipv6hdr = (IPV6HDR *) (pPkt->pDataBuffer + pPkt->DataOffset + sizeof (ICMPV6_PARAM_PROB_HDR));

    /* Notify the socket layer about the error. */
    ICMPv6SocketErrorInterface (Code, ptr_Orgipv6hdr);

    /* Clean out the packet memory. */
    PBM_free (pPkt);
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function is called to receive and process a Packet Too Big
 *      message.
 *
 *  @param[in]  pPkt
 *      Pointer to the entire ICMPv6 Packet.
 *
 *  @retval
 *      0   -   Success
 *  @retval
 *      <0   -  Error
 */
static int ICMPv6RecvPktTooBig (PBM_Pkt* pPkt)
{
    IPV6HDR*    ptr_Orgipv6hdr;

    /* Get the inner packet IPv6 Header. */
    ptr_Orgipv6hdr = (IPV6HDR *) (pPkt->pDataBuffer + pPkt->DataOffset + sizeof (ICMPV6_PKT_TOO_BIG_HDR));

    /* Notify the socket layer about the error. */
    ICMPv6SocketErrorInterface (EMSGSIZE, ptr_Orgipv6hdr);

    /* Clean out the packet memory. */
    PBM_free (pPkt);
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function handles the ICMPv6 Packets.
 *
 *  @param[in]  pPkt
 *      Pointer to the entire ICMPv6 Packet.
 *  @param[in]  ptr_ipv6hdr
 *      Pointer to the IPv6 Header.
 *
 *  @retval
 *      Not Applicable.
 */
int ICMPv6RxPacket (PBM_Pkt* pPkt, IPV6HDR* ptr_ipv6hdr)
{
    ICMPV6HDR*  ptr_icmpv6hdr;
    UINT16      checksum;
    PSEUDOV6    pseudo_hdr;
    IP6N        srcAddr;
    IP6N        dstAddr;

    /* Increment the stats */
    icmp6stats.InMsgs++;

    /* Get the pointer to the ICMPv6 Header. */
    ptr_icmpv6hdr = (ICMPV6HDR *) (pPkt->pDataBuffer + pPkt->DataOffset);

    /* Get the original checksum. */
    checksum = ptr_icmpv6hdr->Checksum;
    if( checksum == 0xFFFF )
        checksum = 0;

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses out of ptr_ipv6hdr
     * as this data is potentially un-aligned (SDOCM00097361)
     */
    mmCopy((char *)&srcAddr, (char *)&ptr_ipv6hdr->SrcAddr, sizeof(IP6N));
    mmCopy((char *)&dstAddr, (char *)&ptr_ipv6hdr->DstAddr, sizeof(IP6N));

    /* Create the Pseudo Header for checksum calculations. */
    pseudo_hdr.SrcAddr = srcAddr;
    pseudo_hdr.DstAddr = dstAddr;
    pseudo_hdr.PktLen  = htons(pPkt->ValidLen);
    pseudo_hdr.Rsvd[0] = 0;
    pseudo_hdr.Rsvd[1] = 0;
    pseudo_hdr.Rsvd[2] = 0;
    pseudo_hdr.NxtHdr  = IPPROTO_ICMPV6;

    /* Compute the new checksum */
    ptr_icmpv6hdr->Checksum = 0;
    ptr_icmpv6hdr->Checksum = IPv6Layer4ComputeChecksum ((UINT8 *)ptr_icmpv6hdr, &pseudo_hdr);

    /* Validate the checksum. */ 
    if( checksum != ptr_icmpv6hdr->Checksum )
    {
        /* Checksums are not correct; packet is dropped */
        icmp6stats.InErrors++;
        PBM_free (pPkt);
        return -1;
    }

    /* Checksums have been validated; now proceed with processing the packet. */
    switch (ptr_icmpv6hdr->Type)
    {
        case ICMPV6_NEIGH_SOLICIT:
        {
            /* Neighbor Solicitation Message Received. */
            if (ICMPv6RecvNS (pPkt, ptr_ipv6hdr) < 0)
            {
                /* The packet was an invalid packet; clean the memory of the packet. */
                PBM_free (pPkt);
                return -1;
            }
            break;
        }
        case ICMPV6_NEIGH_ADVERTISMENT:
        {
            if (ICMPv6RecvNA (pPkt, ptr_ipv6hdr) < 0)
            {
                /* The packet was an invalid packet; clean the memory of the packet. */
                PBM_free (pPkt);
                return -1;
            }
            break;
        }
        case ICMPV6_ECHO_REQUEST:
        {
            if (ICMPv6RecvEchoRequest (pPkt, ptr_ipv6hdr) < 0)
            {
                /* The packet was an invalid packet; clean the memory of the packet. */
                PBM_free (pPkt);
                return -1;
            }
            break;
        }
        case ICMPV6_ECHO_REPLY:
        {
            /* The packet is passed to the RAW6 Module for processing. */
            Raw6Input (pPkt, ptr_ipv6hdr, IPPROTO_ICMPV6);
            break;        
        }
        case ICMPV6_ROUTER_SOLICITATION:
        {
            if (ICMPv6RecvRS (pPkt, ptr_ipv6hdr) < 0)
            {
                /* The packet was an invalid packet; clean the memory of the packet. */
                PBM_free (pPkt);
                return -1;
            }
            break;
        }
        case ICMPV6_ROUTER_ADVERTISMENT:
        {
            if (ICMPv6RecvRA (pPkt, ptr_ipv6hdr) < 0)
            {
                /* The packet was an invalid packet; clean the memory of the packet. */
                PBM_free (pPkt);
                return -1;
            }
            break;
        }
        case ICMPV6_REDIRECT:
        {
            if (ICMPv6RecvRedirect (pPkt, ptr_ipv6hdr) < 0)
            {
                /* The packet was an invalid packet; clean the memory of the packet. */
                PBM_free (pPkt);
                return -1;
            }
            break;
        }
        case ICMPV6_DST_UNREACHABLE:
        {
            if (ICMPv6RecvDstUnreachable (pPkt) < 0)
            {
                /* The packet was an invalid packet; clean the memory of the packet. */
                PBM_free (pPkt);
                return -1;
            }
            break;
        }
        case ICMPV6_TIME_EXCEEDED:
        {
            if (ICMPv6RecvTimeExceeded (pPkt) < 0)
            {
                /* The packet was an invalid packet; clean the memory of the packet. */
                PBM_free (pPkt);
                return -1;
            }
            break;
        }
        case ICMPV6_PARAMETER_PROBLEM:
        {
            if (ICMPv6RecvParamProblem (pPkt) < 0)
            {
                /* The packet was an invalid packet; clean the memory of the packet. */
                PBM_free (pPkt);
                return -1;
            }
            break;
        }
        case ICMPV6_PACKET_TOO_BIG:
        {
            if (ICMPv6RecvPktTooBig (pPkt) < 0)
            {
                /* The packet was an invalid packet; clean the memory of the packet. */
                PBM_free (pPkt);
                return -1;
            }
            break;
        }
        default:
        {
            DbgPrintf(DBG_INFO,
                    "ICMPv6RxPacket: Error: Unknown ICMPv6 Type %d received\n",
                    ptr_icmpv6hdr->Type);
            PBM_free (pPkt);
            return -1;
        }
    }
    return 0;
}

#endif /* _INCLUDE_IPv6_CODE */

