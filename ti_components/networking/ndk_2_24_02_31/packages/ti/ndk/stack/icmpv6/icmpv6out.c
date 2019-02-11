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
 * ======== icmpv6out.c ========
 *
 * The file handles the transmission of ICMPv6 Packets.
 *
 */

#include <stkmain.h>

#ifdef _INCLUDE_IPv6_CODE

/** 
 *  @b Description
 *  @n  
 *      This function parses through all the IPv6 extension
 *      headers to check if the packet is an ICMPv6 error
 *      message.
 *
 *  @param[in]  pPkt
 *      The packet that needs to be checked for ICMPv6 error.
 *
 *  @retval
 *      1   -   Packet is an ICMPv6 error message.
 *  @retval
 *      0   -   Packet is not an ICMPv6 error packet.
 */
int IsICMPv6ErrorPkt (PBM_Pkt* pPkt)
{
    IPV6HDR*    ptr_ipv6hdr = (IPV6HDR *) pPkt->pIpHdr;
    /* IPv6 header pointer must have been validated from
     * the calling function, so lets just proceed with
     * retrieving the pointer to the next extension header
     * start and the Next Header value itself.
     */
    UINT8*      pDataBuffer = (UINT8 *) (ptr_ipv6hdr + 1);
    UINT8       NxtHdrVal = ptr_ipv6hdr->NextHeader;
    IPV6_HOPOPTSHDR* ptr_hopoptshdr;
    IPV6_ROUTINGHDR* ptr_rtghdr;   
    IPV6_FRAGHDR*    ptr_fraghdr;
    ICMPV6HDR*       ptr_icmpv6hdr;

    /* Scan through all extension headers and
     * skip over all the headers until we 
     * bump into an L4 header (TCP, UDP or ICMPv6) or
     * a Fragment header. 
     * The extension header processing logic is as follows:-
     * >>   On None, TCP, UDP headers: 
     *      Return 0 indicating this is not ICMPv6 error message
     *
     * >>   On Fragment header:
     *      Check if the Offset and "M" bit of the header are zero.
     *      If so, this indicates that although this is indicated as
     *      a fragment, we have complete payload. So, skip over the 
     *      fragment header and continue parsing the next header.
     *      If the offset is not zero, we dont have entire payload,
     *      so we cant decipher if this is an ICMPv6 error message so
     *      return 0.
     *
     * >>   On DstOptions, HopOptions, RoutingHdr:
     *      Skip over this header and continue parsing.
     */
    while (1)
    {
        switch(NxtHdrVal)
        {
            /* Skip over the header and continue parsing */
            case IPV6_HOPOPTS_HEADER:
            case IPV6_DSTOPTS_HEADER:
            {
                ptr_hopoptshdr = (IPV6_HOPOPTSHDR *)pDataBuffer;
                NxtHdrVal = ptr_hopoptshdr->NextHeader;

                pDataBuffer += ((ptr_hopoptshdr->HdrExtLen + 1) << 3);

                break;
            }
            case IPV6_ROUTING_HEADER:
            {
                ptr_rtghdr = (IPV6_ROUTINGHDR *)pDataBuffer;
                NxtHdrVal = ptr_rtghdr->NextHeader;

                pDataBuffer += ((ptr_rtghdr->HdrExtLen + 1) << 3);

                break;
            }
            /* Check for a valid fragment header and do needful as 
             * documented above.
             */
            case IPV6_FRAGMENT_HEADER:
            {
                ptr_fraghdr = (IPV6_FRAGHDR *)pDataBuffer;
                /* M bit is 0 and Offset is 0 indicating that
                 * this is not exactly a fragment. So just ignore
                 * this header and skip over to the next.
                 */
                if(!(ptr_fraghdr->FragOffset & htons(0xFFF9))) 
                {
                    /* Increment the offset to jump over Fragment header */
                    pDataBuffer += IPV6_FRAGHDR_SIZE;
                    NxtHdrVal = ptr_fraghdr->NextHeader;
                }
                else
                {
                    /* This is an IPv6 Fragment packet which is incomplete,
                     * so we cant really make out if we have enough data to
                     * find L4 header. So just return 0.
                     */
                    return 0;
                }
            }
            /* Check if this is an ICMPv6 error type packet, if so 
             * return 1 otherwise return 0.
             */
            case ICMPv6_HEADER:
            {
                ptr_icmpv6hdr = (ICMPV6HDR *)pDataBuffer;
                if (ptr_icmpv6hdr->Type == ICMPV6_REDIRECT ||
                    ptr_icmpv6hdr->Type == ICMPV6_DST_UNREACHABLE ||
                    ptr_icmpv6hdr->Type == ICMPV6_TIME_EXCEEDED ||
                    ptr_icmpv6hdr->Type == ICMPV6_PARAMETER_PROBLEM ||
                    ptr_icmpv6hdr->Type == ICMPV6_PACKET_TOO_BIG)
                    return 1;
                else
                    return 0;
            }
            /* This cant be ICMPv6 error packet. Return 0. */
            case IPV6_NONE_HEADER:
            {
                return 0;
            }
            case IPPROTO_UDP:
            case IPPROTO_TCP:
            default:
            {
                return 0;
            }
        }
    }
}

/** 
 *  @b Description
 *  @n  
 *      The function sends a destination unreachable message. The
 *      function accepts Code as a parameter and can be used to
 *      send different messages.
 *
 *  @param[in]  Code
 *      Code to be added to the ICMPv6 Destination Unreachable message
 *      Valid Values range from 0 - 4 as specified in RFC 2463.
 *  @param[in]  pOrgPkt
 *      The offending packet which causes the packet to be sent out.
 *
 *  @retval
 *      0   -   Success
 *  @retval
 *      <0   -  Error
 */
int ICMPv6SendDstUnreachable (UINT8 Code, PBM_Pkt* pOrgPkt)
{
    ICMPV6_DST_UNREACHABLE_HDR* ptr_DstUnreachHdr;
    PBM_Pkt*                    pPkt;
    int                         len;
    IPV6HDR*                    ptr_ip6vhdr;
    IPV6HDR*                    ptr_Orgipv6hdr;
    NETIF_DEVICE*               ptr_net_device;
    PSEUDOV6                    pseudo_hdr;
    HANDLE                      hLLI6;
    UINT8*                      ptr_dataPayload;
    IP6N                        SrcAddressUsed;
    IP6N                        ip6vHdrSrcAddr;
    IP6N                        ip6vHdrDstAddr;
    IP6N                        origIpv6HdrSrcAddr;
    IP6N                        origIpv6HdrDstAddr;

    /* Validate the arguments. */
    if ((Code > ICMPV6_DST_UNREACH_PORT) || (Code == ICMPV6_DST_UNREACH_UNUSED))
        return -1;
    
    /* Get the pointer to the Original IPv6 Header. */
    ptr_Orgipv6hdr = (IPV6HDR *)pOrgPkt->pIpHdr;
    if (ptr_Orgipv6hdr == NULL)
    {
        DbgPrintf (DBG_ERROR, "ICMPv6SendDstUnreachableError: ICMPv6 Dst Unreachable; but no IPv6 header present\n");
        return -1;
    }

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses out of the IPv6
     * header as this data is potentially un-aligned (SDOCM00097361)
     */
    mmCopy((char *)&origIpv6HdrSrcAddr, (char *)&ptr_Orgipv6hdr->SrcAddr, sizeof(IP6N));
    mmCopy((char *)&origIpv6HdrDstAddr, (char *)&ptr_Orgipv6hdr->DstAddr, sizeof(IP6N));

    /* Determine the source address to be used in the packet. Check if the packet was 
     * destined to a multicast address
     */
    if (IPv6IsMulticast(origIpv6HdrDstAddr) == 1)
    {
        /* RFC 4443 Section 2.4 states the following:
         * An ICMPv6 error message MUST NOT be sent as a result of
         * receiving:
         *
         * a packet destined to an IPv6 multicast address (there are
         * two exceptions to this rule: (1) the Packet Too Big
         * Message - Section 3.2 - to allow Path MTU discovery to
         * work for IPv6 multicast, and (2) the Parameter Problem
         * Message, Code 2 - Section 3.4 - reporting an unrecognized
         * IPv6 option that has the Option Type highest-order two
         * bits set to 10).
         * 
         */
        /* We dont send the ICMPv6 error packet, since the destination
         * address is multicast address and we do not fall under any
         * exceptions stated above.
         */
        return 0;
    }
    else
    {
        /* This is a UNICAST packet; we can reuse the destination address as is. */
        SrcAddressUsed = origIpv6HdrDstAddr;
    }

    /* RFC 4443 Section 2.4 states that:
     * (e) An ICMPv6 error message MUST NOT be originated as a result of
     * receiving the following:
     *
     * (e.1) An ICMPv6 error message.
     *
     * (e.2) An ICMPv6 redirect message [IPv6-DISC].
     */ 
    /* Check for the above 2 conditions in the Original Packet and if 
     * they are true, i.e. the original packet was an ICMPv6 error message,
     * then we dont send the ICMPv6 Destination Unreachable error message.
     */
    if (IsICMPv6ErrorPkt(pOrgPkt))
        return -1;

    /* Here we calculate the length of data we will stuff into the Destination 
     * Unreachable packet; this includes copying the Offending packets IPv6 Header */
    len = ntohs(ptr_Orgipv6hdr->PayloadLength) + IPv6HDR_SIZE;

    /* RFC 2463 states that we should not exceed the IPv6 Minimum MTU and if so we need
     * to reduce the amount of data we are appending to the end of the Dst Unreachable
     * packet. 
     * NOTE: Account for the ICMPv6 Header and IPv6 Header which will be added. */
    if (len > (MIN_IPV6_MTU - IPv6HDR_SIZE - sizeof (ICMPV6_DST_UNREACHABLE_HDR)))
        len = (MIN_IPV6_MTU - IPv6HDR_SIZE - sizeof (ICMPV6_DST_UNREACHABLE_HDR));

    /* Allocate memory for the Destination Unreachable packet. The size of the packet
     * should be big enough to account for the following:-
     *  - IPv6 Header
     *  - Dst Unreachable Payload Length computed 
     *  - Dst Unreachable Header. */
    pPkt = NIMUCreatePacket (IPv6HDR_SIZE + sizeof (ICMPV6_DST_UNREACHABLE_HDR) + len);
    if (pPkt == NULL)
    {
        /* We are running out of memory. */
        NotifyLowResource ();
        return -1;
    }

    /* Get the IPv6 header pointer for the new packet */
    ptr_ip6vhdr = (IPV6HDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Get the pointer to the destination unreachable header. */
    ptr_DstUnreachHdr = (ICMPV6_DST_UNREACHABLE_HDR *)(((UINT8 *)ptr_ip6vhdr) + IPv6HDR_SIZE);

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses into ptr_ip6vhdr
     * as ptr_ipv6hdr->SrcAddr/DstAddr are potentially un-aligned
     * (SDOCM00097361)
     */
    mmCopy((char *)&ip6vHdrSrcAddr, (char *)&ptr_ip6vhdr->SrcAddr, sizeof(IP6N));
    mmCopy((char *)&ip6vHdrDstAddr, (char *)&ptr_ip6vhdr->DstAddr, sizeof(IP6N));

    /* Populate the destination unreachable header. */
    ptr_DstUnreachHdr->Type   = 1;
    ptr_DstUnreachHdr->Code   = Code;
    ptr_DstUnreachHdr->Unused = 0;

    /* Copy as much of the offending packet into the Destination Unreachable packet. */
    ptr_dataPayload = (UINT8 *)ptr_DstUnreachHdr + sizeof (ICMPV6_DST_UNREACHABLE_HDR);
    mmCopy ((void *)ptr_dataPayload, (void *)ptr_Orgipv6hdr, len);

    /* Determine the route; we need to send the packet back to the Source Address of
     * the offending packet. If there exists no route we cannot proceed. */
    pPkt->hRoute6 = IPv6GetRoute (origIpv6HdrSrcAddr);
    if (pPkt->hRoute6 == 0)
        return -1;

    /* Get the network device associated with the ROUTE6 Object; this is accessed
     * via the LLI6 Entry. */
    hLLI6          = Rt6GetLLI(pPkt->hRoute6);
    ptr_net_device = LLI6GetNetDevice(hLLI6);    

    /* Populate the IPv6 Header. */
    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses into ptr_ipv6hdr
     * as ptr_ipv6hdr->SrcAddr/DstAddr are potentially un-aligned
     * (SDOCM00097361)
     */
    mmCopy((char *)&ptr_ip6vhdr->DstAddr, (char *)&origIpv6HdrSrcAddr, sizeof(IP6N));
    mmCopy((char *)&ptr_ip6vhdr->SrcAddr, (char *)&SrcAddressUsed, sizeof(IP6N));
    ptr_ip6vhdr->NextHeader     = IPPROTO_ICMPV6;
    ptr_ip6vhdr->HopLimit       = ptr_net_device->ptr_ipv6device->CurHopLimit;
    ptr_ip6vhdr->PayloadLength  = htons(sizeof (ICMPV6_DST_UNREACHABLE_HDR) + len);

    /* Create the Pseudo Header for checksum calculations. */
    pseudo_hdr.SrcAddr = ip6vHdrSrcAddr;
    pseudo_hdr.DstAddr = ip6vHdrDstAddr;
    pseudo_hdr.PktLen  = ptr_ip6vhdr->PayloadLength;
    pseudo_hdr.Rsvd[0] = 0;
    pseudo_hdr.Rsvd[1] = 0;
    pseudo_hdr.Rsvd[2] = 0;
    pseudo_hdr.NxtHdr  = IPPROTO_ICMPV6;

    /* Compute the ICMPv6 Checksum. */
    ptr_DstUnreachHdr->Checksum = 0;
    ptr_DstUnreachHdr->Checksum = IPv6Layer4ComputeChecksum ((UINT8 *)ptr_DstUnreachHdr, &pseudo_hdr);

    /* Set the valid len of the packet; which is the ICMPv6 Dst Unreachable 
     * Header and the data payload. */
    pPkt->ValidLen = (sizeof (ICMPV6_DST_UNREACHABLE_HDR) + len);

    /* Pass the packet to the IPv6 Layer for transmission. */
    IPv6TxPacket (pPkt, 0);
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function sends a Time Exceeded message. The function accepts 
 *      Code as a parameter and can be used to send different messages.
 *
 *  @param[in]  Code
 *      Code to be added to the ICMPv6 Time Exceeded message
 *      Valid Values range from 0 - 1 as specified in RFC 2463.
 *  @param[in]  pOrgPkt
 *      The offending packet which causes the packet to be sent out.
 *
 *  @retval
 *      0   -   Success
 *  @retval
 *      <0   -  Error
 */
int ICMPv6SendTimeExceeded (UINT8 Code, PBM_Pkt* pOrgPkt)
{
    ICMPV6_TIME_EXCEEDED_HDR*   ptr_icmpv6TimeExceededHdr;
    PBM_Pkt*                    pPkt;
    int                         len;
    IPV6HDR*                    ptr_ip6vhdr;
    IPV6HDR*                    ptr_Orgipv6hdr;
    NETIF_DEVICE*               ptr_net_device;
    PSEUDOV6                    pseudo_hdr;
    HANDLE                      hLLI6;
    UINT8*                      ptr_dataPayload;
    IP6N                        SrcAddressUsed;
    IP6N                        ip6vHdrSrcAddr;
    IP6N                        ip6vHdrDstAddr;
    IP6N                        origIpv6HdrSrcAddr;
    IP6N                        origIpv6HdrDstAddr;

    /* Validate the arguments. */
    if (Code > ICMPV6_TIME_EXCEEDED_FRAGMENT)
        return -1;

    /* Get the pointer to the Original IPv6 Header. */
    ptr_Orgipv6hdr = (IPV6HDR *)pOrgPkt->pIpHdr;
    if (ptr_Orgipv6hdr == NULL)
    {
        DbgPrintf (DBG_ERROR, "ICMPv6SendTimeExceeded: Error: ICMPv6 Time Exceeded; but no IPv6 header present\n");
        return -1;
    }

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses out of the IPv6
     * header as this data is potentially un-aligned (SDOCM00097361)
     */
    mmCopy((char *)&origIpv6HdrSrcAddr, (char *)&ptr_Orgipv6hdr->SrcAddr, sizeof(IP6N));
    mmCopy((char *)&origIpv6HdrDstAddr, (char *)&ptr_Orgipv6hdr->DstAddr, sizeof(IP6N));

    /* Determine the source address to be used in the packet. Check if the packet was 
     * destined to a multicast address
     */
    if (IPv6IsMulticast(origIpv6HdrDstAddr) == 1)
    {
        /* RFC 4443 Section 2.4 states the following:
         * An ICMPv6 error message MUST NOT be sent as a result of
         * receiving:
         *
         * a packet destined to an IPv6 multicast address (there are
         * two exceptions to this rule: (1) the Packet Too Big
         * Message - Section 3.2 - to allow Path MTU discovery to
         * work for IPv6 multicast, and (2) the Parameter Problem
         * Message, Code 2 - Section 3.4 - reporting an unrecognized
         * IPv6 option that has the Option Type highest-order two
         * bits set to 10).
         * 
         */
        /* We dont send the ICMPv6 error packet, since the destination
         * address is multicast address and we do not fall under any
         * exceptions stated above.
         */
        return 0;
    }
    else
    {
        /* This is a UNICAST packet; we can reuse the destination address as is. */
        SrcAddressUsed = origIpv6HdrDstAddr;
    }

    /* RFC 4443 Section 2.4 states that:
     * (e) An ICMPv6 error message MUST NOT be originated as a result of
     * receiving the following:
     *
     * (e.1) An ICMPv6 error message.
     *
     * (e.2) An ICMPv6 redirect message [IPv6-DISC].
     */ 
    /* Check for the above 2 conditions in the Original Packet and if 
     * they are true, i.e. the original packet was an ICMPv6 error message,
     * then we dont send the ICMPv6 Time Exceeded error message.
     */
    if (IsICMPv6ErrorPkt(pOrgPkt))
        return -1;

    /* Here we calculate the length of data we will stuff into the Time Exceeded 
     * packet; this includes copying the Offending packets IPv6 Header */
    len = ntohs(ptr_Orgipv6hdr->PayloadLength) + IPv6HDR_SIZE;

    /* RFC 2463 states that we should not exceed the IPv6 Minimum MTU and if so we need
     * to reduce the amount of data we are appending to the end of the Time Exceeded
     * packet. 
     * NOTE: Account for the ICMPv6 Header and IPv6 Header which will be added. */
    if (len > (MIN_IPV6_MTU - IPv6HDR_SIZE - sizeof (ICMPV6_TIME_EXCEEDED_HDR)))
        len = (MIN_IPV6_MTU - IPv6HDR_SIZE - sizeof (ICMPV6_TIME_EXCEEDED_HDR));

    /* Allocate memory for the Destination Unreachable packet. The size of the packet
     * should be big enough to account for the following:-
     *  - IPv6 Header
     *  - Dst Unreachable Payload Length computed 
     *  - Dst Unreachable Header. */
    pPkt = NIMUCreatePacket (IPv6HDR_SIZE + sizeof (ICMPV6_TIME_EXCEEDED_HDR) + len);
    if (pPkt == NULL)
    {
        /* We are running out of memory. */
        NotifyLowResource ();
        return -1;
    }

    /* Get the IPv6 header pointer for the new packet */
    ptr_ip6vhdr = (IPV6HDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses into ptr_ip6vhdr
     * as ptr_ipv6hdr->SrcAddr/DstAddr are potentially un-aligned
     * (SDOCM00097361)
     */
    mmCopy((char *)&ip6vHdrSrcAddr, (char *)&ptr_ip6vhdr->SrcAddr, sizeof(IP6N));
    mmCopy((char *)&ip6vHdrDstAddr, (char *)&ptr_ip6vhdr->DstAddr, sizeof(IP6N));

    /* Get the pointer to the Time Exceeded header. */
    ptr_icmpv6TimeExceededHdr = (ICMPV6_TIME_EXCEEDED_HDR *)(((UINT8 *)ptr_ip6vhdr) + IPv6HDR_SIZE);

    /* Populate the destination unreachable header. */
    ptr_icmpv6TimeExceededHdr->Type   = 3;
    ptr_icmpv6TimeExceededHdr->Code   = Code;
    ptr_icmpv6TimeExceededHdr->Unused = 0;

    /* Copy as much of the offending packet into the Time Exceeded packet. */
    ptr_dataPayload = (UINT8 *)ptr_icmpv6TimeExceededHdr + sizeof (ICMPV6_TIME_EXCEEDED_HDR);
    mmCopy ((void *)ptr_dataPayload, (void *)ptr_Orgipv6hdr, len);

    /* Determine the route; we need to send the packet back to the Source Address of
     * the offending packet. If there exists no route we cannot proceed. */
    pPkt->hRoute6 = IPv6GetRoute (origIpv6HdrSrcAddr);
    if (pPkt->hRoute6 == 0)
        return -1;

    /* Get the network device associated with the ROUTE6 Object; this is accessed
     * via the LLI6 Entry. */
    hLLI6          = Rt6GetLLI(pPkt->hRoute6);
    ptr_net_device = LLI6GetNetDevice(hLLI6);    

    /* Populate the IPv6 Header. */
    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses into ptr_ipv6hdr
     * as ptr_ipv6hdr->{SrcAddr, DstAddr] are potentially un-aligned
     * (SDOCM00097361)
     */
    mmCopy((char *)&ptr_ip6vhdr->DstAddr, (char *)&origIpv6HdrSrcAddr, sizeof(IP6N));
    mmCopy((char *)&ptr_ip6vhdr->SrcAddr, (char *)&SrcAddressUsed, sizeof(IP6N));
    ptr_ip6vhdr->NextHeader     = IPPROTO_ICMPV6;
    ptr_ip6vhdr->HopLimit       = ptr_net_device->ptr_ipv6device->CurHopLimit;
    ptr_ip6vhdr->PayloadLength  = htons(sizeof (ICMPV6_TIME_EXCEEDED_HDR) + len);

    /* Create the Pseudo Header for checksum calculations. */
    pseudo_hdr.SrcAddr = ip6vHdrSrcAddr;
    pseudo_hdr.DstAddr = ip6vHdrDstAddr;
    pseudo_hdr.PktLen  = ptr_ip6vhdr->PayloadLength;
    pseudo_hdr.Rsvd[0] = 0;
    pseudo_hdr.Rsvd[1] = 0;
    pseudo_hdr.Rsvd[2] = 0;
    pseudo_hdr.NxtHdr  = IPPROTO_ICMPV6;

    /* Compute the ICMPv6 Checksum. */
    ptr_icmpv6TimeExceededHdr->Checksum = 0;
    ptr_icmpv6TimeExceededHdr->Checksum = IPv6Layer4ComputeChecksum ((UINT8 *)ptr_icmpv6TimeExceededHdr, &pseudo_hdr);

    /* Set the valid len of the packet; which is the ICMPv6 Time Exceeded Header 
     * and the data payload. */
    pPkt->ValidLen = (sizeof (ICMPV6_TIME_EXCEEDED_HDR) + len);

    /* Pass the packet to the IPv6 Layer for transmission. */
    IPv6TxPacket (pPkt, 0);
    return 0;
}


/** 
 *  @b Description
 *  @n  
 *      The function sends the Parameter Problem message. The function 
 *      accepts Code as a parameter and can be used to send different 
 *      messages.
 *
 *  @param[in]  Code
 *      Code to be added to the ICMPv6 Time Exceeded message
 *      Valid Values range from 0 - 2 as specified in RFC 2463.
 *  @param[in]  pOrgPkt
 *      The offending packet which causes the packet to be sent out.
 *  @param[in]  Pointer
 *      Identifies the Code Offset within the packet where the error occurred.
 *
 *  @retval
 *      0   -   Success
 *  @retval
 *      <0   -  Error
 */
int ICMPv6SendParameterProblem (UINT8 Code, PBM_Pkt* pOrgPkt, UINT32 Pointer)
{
    ICMPV6_PARAM_PROB_HDR*      ptr_icmpv6ParamProblem;
    PBM_Pkt*                    pPkt;
    int                         len;
    IPV6HDR*                    ptr_ip6vhdr;
    IPV6HDR*                    ptr_Orgipv6hdr;
    NETIF_DEVICE*               ptr_net_device;
    PSEUDOV6                    pseudo_hdr;
    HANDLE                      hLLI6;
    UINT8*                      ptr_dataPayload;
    IP6N                        SrcAddressUsed;
    IP6N                        origIpv6HdrSrcAddr;
    IP6N                        origIpv6HdrDstAddr;

    /* Validate the arguments. */
    if (Code > ICMPV6_PARAM_PROBLEM_INV_OPTION)
        return -1;

    /* Get the pointer to the Original IPv6 Header. */
    ptr_Orgipv6hdr = (IPV6HDR *)pOrgPkt->pIpHdr;
    if (ptr_Orgipv6hdr == NULL)
    {
        DbgPrintf (DBG_ERROR, "ICMPv6SendParameterProblem: Error: ICMPv6 Parameter Problem; but no IPv6 header present\n");
        return -1;
    }

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses out of the IPv6
     * header as this data is potentially un-aligned (SDOCM00097361)
     */
    mmCopy((char *)&origIpv6HdrSrcAddr, (char *)&ptr_Orgipv6hdr->SrcAddr, sizeof(IP6N));
    mmCopy((char *)&origIpv6HdrDstAddr, (char *)&ptr_Orgipv6hdr->DstAddr, sizeof(IP6N));

    /* Determine the source address to be used in the packet. Check if the packet was 
     * destined to a multicast address
     */
    if (IPv6IsMulticast(origIpv6HdrDstAddr) == 1)
    {
        /* RFC 4443 Section 2.4 states the following:
         * An ICMPv6 error message MUST NOT be sent as a result of
         * receiving:
         *
         * a packet destined to an IPv6 multicast address (there are
         * two exceptions to this rule: (1) the Packet Too Big
         * Message - Section 3.2 - to allow Path MTU discovery to
         * work for IPv6 multicast, and (2) the Parameter Problem
         * Message, Code 2 - Section 3.4 - reporting an unrecognized
         * IPv6 option that has the Option Type highest-order two
         * bits set to 10).
         * 
         */
        /* We send the ICMPv6 error packet, even though the destination
         * address is multicast address. The exception (2) stated above is
         * taken care of in IPv6 extension header processing itself, i.e.
         * if we do encounter an IPv6 extension header with an option we do 
         * not recognize and the option type's highest order 2 bits are not 
         * set to 10, we do not even raise an ICMPv6 error to arrive here.
         * So, if we have arrived here, it means that its because we satisfy
         * exception (2) stated above, so we send out the ICMPv6 error packet.
         */

        /* RFC 2463 Section 2.2 states that if the packet destination address is
         * MULTICAST we need to send the Source Address of the REPLY 
         * to the UNICAST Address of the interface. */

        if(Bind6GetLinkLocalAddress(pOrgPkt->hIFRx, &SrcAddressUsed) < 0)
            return -1;
    }
    else
    {
        /* This is a UNICAST packet; we can reuse the destination address as is. */
        SrcAddressUsed = origIpv6HdrDstAddr;
    }

    /* RFC 4443 Section 2.4 states that:
     * (e) An ICMPv6 error message MUST NOT be originated as a result of
     * receiving the following:
     *
     * (e.1) An ICMPv6 error message.
     *
     * (e.2) An ICMPv6 redirect message [IPv6-DISC].
     */ 
    /* Check for the above 2 conditions in the Original Packet and if 
     * they are true, i.e. the original packet was an ICMPv6 error message,
     * then we dont send the ICMPv6 Parameter Problem error message.
     */
    if (IsICMPv6ErrorPkt(pOrgPkt))
        return -1;

    /* Here we calculate the length of data we will stuff into the Time Exceeded 
     * packet; this includes copying the Offending packets IPv6 Header */
    len = ntohs(ptr_Orgipv6hdr->PayloadLength) + IPv6HDR_SIZE;

    /* RFC 2463 states that we should not exceed the IPv6 Minimum MTU and if so we need
     * to reduce the amount of data we are appending to the end of the Time Exceeded
     * packet. 
     * NOTE: Account for the ICMPv6 Header and IPv6 Header which will be added. */
    if (len > (MIN_IPV6_MTU - IPv6HDR_SIZE - sizeof (ICMPV6_PARAM_PROB_HDR)))
        len = (MIN_IPV6_MTU - IPv6HDR_SIZE - sizeof (ICMPV6_PARAM_PROB_HDR));

    /* Allocate memory for the Destination Unreachable packet. The size of the packet
     * should be big enough to account for the following:-
     *  - IPv6 Header
     *  - Dst Unreachable Payload Length computed 
     *  - Dst Unreachable Header. */
    pPkt = NIMUCreatePacket (IPv6HDR_SIZE + sizeof (ICMPV6_PARAM_PROB_HDR) + len);
    if (pPkt == NULL)
    {
        /* We are running out of memory. */
        NotifyLowResource ();
        return -1;
    }

    /* Get the IPv6 header pointer for the new packet */
    ptr_ip6vhdr = (IPV6HDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Get the pointer to the Time Exceeded header. */
    ptr_icmpv6ParamProblem = (ICMPV6_PARAM_PROB_HDR *)(((UINT8 *)ptr_ip6vhdr) + IPv6HDR_SIZE);

    /* Populate the destination unreachable header. */
    ptr_icmpv6ParamProblem->Type    = 4;
    ptr_icmpv6ParamProblem->Code    = Code;
    ptr_icmpv6ParamProblem->Pointer = htonl(Pointer);

    /* Copy as much of the offending packet into the Time Exceeded packet. */
    ptr_dataPayload = (UINT8 *)ptr_icmpv6ParamProblem + sizeof (ICMPV6_PARAM_PROB_HDR);
    mmCopy ((void *)ptr_dataPayload, (void *)ptr_Orgipv6hdr, len);

    /* Determine the route; we need to send the packet back to the Source Address of
     * the offending packet. If there exists no route we cannot proceed. */
    pPkt->hRoute6 = IPv6GetRoute (origIpv6HdrSrcAddr);
    if (pPkt->hRoute6 == 0)
        return -1;

    /* Get the network device associated with the ROUTE6 Object; this is accessed
     * via the LLI6 Entry. */
    hLLI6          = Rt6GetLLI(pPkt->hRoute6);
    ptr_net_device = LLI6GetNetDevice(hLLI6);    

    /* Populate the IPv6 Header. */
    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses into ptr_ipv6hdr
     * as ptr_ipv6hdr->SrcAddr/DstAddr are potentially un-aligned
     * (SDOCM00097361)
     */
    mmCopy((char *)&ptr_ip6vhdr->DstAddr, (char *)&origIpv6HdrSrcAddr, sizeof(IP6N));
    mmCopy((char *)&ptr_ip6vhdr->SrcAddr, (char *)&SrcAddressUsed, sizeof(IP6N));

    ptr_ip6vhdr->NextHeader     = IPPROTO_ICMPV6;
    ptr_ip6vhdr->HopLimit       = ptr_net_device->ptr_ipv6device->CurHopLimit;
    ptr_ip6vhdr->PayloadLength  = htons(sizeof (ICMPV6_PARAM_PROB_HDR) + len);

    /* Create the Pseudo Header for checksum calculations. */
    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses
     * as ptr_ipv6hdr->SrcAddr/DstAddr are potentially un-aligned
     * (SDOCM00097361)
     */
    mmCopy((char *)&pseudo_hdr.SrcAddr, (char *)&ptr_ip6vhdr->SrcAddr, sizeof(IP6N));
    mmCopy((char *)&pseudo_hdr.DstAddr, (char *)&ptr_ip6vhdr->DstAddr, sizeof(IP6N));

    pseudo_hdr.PktLen  = ptr_ip6vhdr->PayloadLength;
    pseudo_hdr.Rsvd[0] = 0;
    pseudo_hdr.Rsvd[1] = 0;
    pseudo_hdr.Rsvd[2] = 0;
    pseudo_hdr.NxtHdr  = IPPROTO_ICMPV6;

    /* Compute the ICMPv6 Checksum. */
    ptr_icmpv6ParamProblem->Checksum = 0;
    ptr_icmpv6ParamProblem->Checksum = IPv6Layer4ComputeChecksum ((UINT8 *)ptr_icmpv6ParamProblem, &pseudo_hdr);

    /* Set the valid len of the packet; which is the ICMPv6 Time Exceeded Header 
     * and the data payload. */
    pPkt->ValidLen = (sizeof (ICMPV6_PARAM_PROB_HDR) + len);

    /* Pass the packet to the IPv6 Layer for transmission. */
    IPv6TxPacket (pPkt, 0);
    return 0;
}

#endif /* _INCLUDE_IPv6_CODE */

