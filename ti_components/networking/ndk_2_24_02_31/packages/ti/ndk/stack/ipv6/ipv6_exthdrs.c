/*
 * Copyright (c) 2013-2014, Texas Instruments Incorporated
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
 * ======== ipv6_exthdrs.c ========
 *
 * The file handles the IPv6 extension header processing.
 *
 */


#include <stkmain.h>
#include "ipv6.h"

#ifdef _INCLUDE_IPv6_CODE

/**********************************************************************
 *************************** Local Definitions ************************
 **********************************************************************/

/**********************************************************************
 *************** IPV6 Extension Header Handling Functions *************
 **********************************************************************/

/** 
 *  @b Description
 *  @n  
 *      The function handles the Hop by Hop options.
 *
 *  @param[in]  pPkt
 *      Pointer to the entire IPv6 Packet.
 *
 *  @retval
 *      Error processing Hop by Hop extension header    -   -1
 *  @retval
 *      Success -   Next header value from hop by hop options header
 */
static int IPv6ParseHopOptions (PBM_Pkt* pPkt, IPV6HDR* ptr_ipv6hdr)
{
    IPV6_HOPOPTSHDR*    ptr_hopoptshdr = NULL;
    UINT16              HopOptsLen, DataLen, Offset, OptLen, OptType;
    UINT32              errPointer;
    IP6N                dstAddr;

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses out of ptr_ipv6hdr
     * as this data is potentially un-aligned (SDOCM00097361)
     */
    mmCopy((char *)&dstAddr, (char *)&ptr_ipv6hdr->DstAddr, sizeof(IP6N));

    /* Get the pointer to the Hop-by-Hop options Header. */
    ptr_hopoptshdr = (IPV6_HOPOPTSHDR *) (pPkt->pDataBuffer + pPkt->DataOffset);

    /* Aux1 is used to hold the offset (from the start of IPv6 header) of 
     * "Next Header" field of this header. This is modified along the 
     * receive path as extension headers are parsed. 
     * Used by IPv6 fragmentation and reassembly layer module.
     */
    pPkt->Aux1 = (UINT32) ((UINT8*)(ptr_hopoptshdr) - (UINT8*) (pPkt->pIpHdr));

    /* Get offset to the Hop by Hop option data */
    Offset = (pPkt->DataOffset + IPV6_HOPOPTSHDR_SIZE);

	/* RFC 2460 - Section 4.3
     * Hdr Ext Len  8-bit unsigned integer. Length of the Hop-by-Hop 
     *              options header in 8-octet units, not including the 
     *              first 8 octets.
     */
	HopOptsLen = (UINT16)((ptr_hopoptshdr->HdrExtLen + 1) << 3);

    /* Length of data to process in bytes 
     * = Hop options data len - 2 (Next Header + Hdr Ext len)
     */
    DataLen = (HopOptsLen - 2);

    /* Scan through the option data buffer */
    while (DataLen > 0) {

        /* RFC 2460 - Section 4.2 
         * Two of the currently-defined extension headers -- 
         * the Hop-by-Hop and Destination Options headers --
         * carry a variable number of type-length-value (TLV)
         * encoded "options" of the following format:
         * |-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|- - - - - - - - 
         * | Option Type   | Opt Data Len  | Option Data
         * |  (8 bit)      |  (8 bit)      | (Variable len)
         *  -+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|- - - - - - - - 
         * Option Type   8-bit identifier of the type of option
         * Opt Data Len  8-bit unsigned integer. Length of option
         *               data field of this option, in octets.
         * Option Data   Variable-length field. Option-Type-specific
         *               data.
         */
        /* Get the Option Type and Option Length. */
        OptType = (UINT8)*(pPkt->pDataBuffer + Offset);

        /* Get to the option data, i.e., skip the T, L vectors */
        OptLen = (UINT8)*(pPkt->pDataBuffer + Offset + 1) + 2;

        /* Currently RFC 2460 defines only 2 options:
         * Pad0 and PadN options. 
         */
        switch (OptType)
        {
            case IPV6_PAD1_OPT:
            {
                OptLen = 1;
                break;
            }
            case IPV6_PADN_OPT:
            {
                break;
            }
            default:
            {
                /* RFC 2460, Section 4.2 
                 * The Option Type identifiers are internally encoded such that 
                 * their highest-order two bits specify the action that must be 
                 * taken if the processing IPv6 node does not recognize the option
                 * type:
                 * 00   -   Skip over this option and continue processing the 
                 *          header.
                 * 01   -   discard the packet.
                 * 10   -   discard the packet and, regardless of whether or not
                 *          the packet's destination address was a multicast address,
                 *          send an ICMP parameter problem, code 2, message to the 
                 *          packet's source address, pointing to the unrecognized
                 *          option type.
                 * 11   -   discard the packet and, only if the packet's destination
                 *          address was not a multicast address, send an ICMP 
                 *          parameter problem, code 2, message to the packet's 
                 *          source address, pointing to the unregognized option type.
                 */
                 /* If we are here, we dont recognize the option, so do needful */
                 switch ((OptType & 0xC0) >> 6)
                 {
                    case 0:
                    {
                        /*
                         * Fix for SDOCM00102280
                         *
                         * Original implementation correctly ignored the option,
                         * but didn't implement the "continue processing the
                         * header" part.
                         *
                         * Break out of this switch so that the while loop will
                         * move past this option and onto the next ones (i.e.
                         * while (DataLen > 0)...)
                         */
                         break;
                    }
                    case 1:
                    {
                        /* Discard the packet */
                        ipv6mcb.ip6stats.InExtnHdrErrors++;
                        PBM_free(pPkt);
                        return -1;
                    }
                    case 2:
                    {
                        /* Send an ICMP Parameter Problem and discard packet */
                        ipv6mcb.ip6stats.InExtnHdrErrors++;
                        errPointer = (UINT8 *)(pPkt->pDataBuffer + Offset) - (UINT8 *)ptr_ipv6hdr;
                        ICMPv6SendParameterProblem (ICMPV6_PARAM_PROBLEM_INV_OPTION, pPkt, errPointer);
                        PBM_free(pPkt);
                        return -1;
                    }
                    case 3:
                    {
                        /* Send an ICMP Parameter Problem if destination IP not multicast
                         * and discard packet 
                         */
                        if(!IPv6IsMulticast(dstAddr))
                        {
                            errPointer = (UINT8 *)(pPkt->pDataBuffer + Offset) - (UINT8 *)ptr_ipv6hdr;
                            ICMPv6SendParameterProblem (ICMPV6_PARAM_PROBLEM_INV_OPTION, pPkt, errPointer);
                        }
                        ipv6mcb.ip6stats.InExtnHdrErrors++;
                        PBM_free(pPkt);
                        return -1;
                    }
                 }
                break;
            }
        }

        /* Move the offset and len according to the 
         * option data len 
         */
        Offset += OptLen;
        DataLen -= OptLen;
    }

    /* Increment the offset to jump over Hop-by-Hop options header */
    pPkt->DataOffset += (HopOptsLen);
    pPkt->ValidLen   -= (HopOptsLen);

    /* Increment the IpHdrLen to include this extension header length too.
     * Used by Fragmentation/reassembly module.
     */
    pPkt->IpHdrLen += (HopOptsLen);

    return ptr_hopoptshdr->NextHeader;
}

/** 
 *  @b Description
 *  @n  
 *      The function handles the Routing options.
 *
 *  @param[in]  pPkt
 *      Pointer to the entire IPv6 Packet.
 *
 *  @retval
 *      Error processing Hop by Hop extension header    -   -1
 *  @retval
 *      Success -   Next header value from hop by hop options header
 */
static int IPv6ParseRoutingHdr (PBM_Pkt* pPkt, IPV6HDR* ptr_ipv6hdr)
{
    IPV6_ROUTINGHDR*    ptr_rtghdr = NULL;
    UINT16              RtgHdrLen;
    UINT32              errPointer;

    /* Get the pointer to the Routing Header. */
    ptr_rtghdr = (IPV6_ROUTINGHDR *) (pPkt->pDataBuffer + pPkt->DataOffset);

    /* For now, we are in HOST only mode, so we discard all packets
     * with routing header in which Segments Left is non-zero.
     */
    if ((ptr_rtghdr->SegmentsLeft != 0) && (ipv6mcb.IsRouter == 0))
    {
#ifdef IPV6_EXTHDR_DEBUG
        DbgPrintf(DBG_INFO, "IPv6ParseRoutingHdr: TODO: Recvd IPV6 packet with routing header, SegmentsLeft non zero, discard the packet \n");
#endif
        ipv6mcb.ip6stats.InExtnHdrErrors++;
        PBM_free(pPkt);
        return -1;
    }

    /* RFC 2460 - Section 4.4 
     * If while processing a received packet, a node encounters
     * a Routing header with an unrecognized Routing Type value,
     * the required behavior of the node depends on the value
     * of the Segments left feild, as follows:
     *  -   If the Segments Left is zero, the node must ignore the
     *      Routing header and proceed to process the next header
     *      in the packet, whose type is identified by the Next 
     *      Header field in the routing header.
     *  -   If Segments Left is non-zero, the node must discard the
     *      packet and send an ICMP Parameter Problem, code 0, message
     *      to the packet's Source Address, pointing to the unrecognized
     *      Routing Type.
     */
    /* The only routing header type we support is "Type 0"
     * as defined in RFC 2460 at the moment.
     */
    if (ptr_rtghdr->RoutingType != 0)
    {
        if (ptr_rtghdr->SegmentsLeft == 0)
        {
#ifdef IPV6_EXTHDR_DEBUG
            DbgPrintf(DBG_INFO, "IPv6ParseRoutingHdr: Invalid routing type, but Segments left zero, skip routing header \n");
#endif
        }
        else
        {
            errPointer = (UINT8 *)&ptr_rtghdr->RoutingType - (UINT8 *)ptr_ipv6hdr;
            ICMPv6SendParameterProblem (ICMPV6_PARAM_PROBLEM_ERR_HEADER, pPkt, errPointer);
            ipv6mcb.ip6stats.InExtnHdrErrors++;
            PBM_free(pPkt);
            return -1;
        }
    }

    /* Aux1 is used to hold the offset (from the start of IPv6 header) of 
     * "Next Header" field of this header. This is modified along the 
     * receive path as extension headers are parsed. 
     * Used by IPv6 fragmentation and reassembly layer module.
     */
    pPkt->Aux1 = (UINT32) ((UINT8*)(ptr_rtghdr) - (UINT8*) (ptr_ipv6hdr));

	/* RFC 2460 - Section 4.4
     * Hdr Ext Len  8-bit unsigned integer. Length of the Routing 
     *              header in 8-octet units, not including the 
     *              first 8 octets.
     */
	RtgHdrLen = (UINT16)((ptr_rtghdr->HdrExtLen + 1) << 3);

    /* If we are not in "Host-only" mode, only then we 
     * process Routing header options.
     * Otherwise, just skip over Routing header and continue
     * processing the next header.
     */
    if (ipv6mcb.IsRouter != 0)
    {
        DbgPrintf(DBG_ERROR, "IPv6ParseRoutingHdr: NDK Stack operates only in HOST Mode.\n");
        ipv6mcb.ip6stats.InForwErrors++;
        return -1;
    }

    /* Increment the offset to jump over Routing header */
    pPkt->DataOffset += (RtgHdrLen);
    pPkt->ValidLen   -= (RtgHdrLen);

    /* Increment the IpHdrLen to include this extension header length too.
     * Used by Fragmentation/reassembly module.
     */
    pPkt->IpHdrLen += (RtgHdrLen);

    return ptr_rtghdr->NextHeader;
}

/** 
 *  @b Description
 *  @n  
 *      The function handles all IPV6 extension headers.
 *
 *  @param[in]  pPkt
 *      Pointer to the entire IPv6 Packet.
 *
 *  @param[in]  ptr_ipv6hdr
 *      Pointer to the IPv6 Header.
 *
 *  @retval
 *      None
 */
void IPv6ParseExtnHeaders (PBM_Pkt* pPkt, IPV6HDR* ptr_ipv6hdr)
{
    UINT8   NxtHdrVal = ptr_ipv6hdr->NextHeader;
    int     RetVal    = -1;
    int     hopOptHdrCnt = 0;

    while (1)
    {
        switch(NxtHdrVal)
        {
            case IPV6_HOPOPTS_HEADER:
            {
                /*
                 * Fix for SDOCM00102234
                 *
                 * Keep track of number of hop-by-hop headers.  There can only
                 * be one per packet
                 */
                if (++hopOptHdrCnt > 1)
                {
                    /*
                     * Detected multiple hop-by-hop headers, silently discard
                     * the packet (I don't see anywhere in RFC 2460 for
                     * sending an ICMP parameter prob msg for this case).
                     */
                    ipv6mcb.ip6stats.InExtnHdrErrors++;
                    PBM_free(pPkt);
                    return;
                }

               /* RFC 2460 - Section 4.1 
                * IPv6 nodes must accept and attempt to process extension headers in
                * any order and occurring any number of times in the same packet,
                * except for the Hop-by-Hop Options header which is restricted to
                * appear immediately after an IPv6 header only. 
                */
                if(NxtHdrVal != ptr_ipv6hdr->NextHeader)
                {
                    ICMPv6SendParameterProblem (ICMPV6_PARAM_PROBLEM_INV_NEXT_HDR, pPkt, pPkt->Aux1);
#ifdef IPV6_EXTHDR_DEBUG
                    DbgPrintf(DBG_INFO, "IPv6ParseExtnHeaders: NextHop header at invalid locn \n");
#endif
                    ipv6mcb.ip6stats.InExtnHdrErrors++;
                    PBM_free(pPkt);
                    return;
                }

                /* Parse Hop by Hop extension header */
                RetVal = IPv6ParseHopOptions (pPkt, ptr_ipv6hdr);

                break;
            }
            case IPV6_ROUTING_HEADER:
            {
                RetVal = IPv6ParseRoutingHdr (pPkt, ptr_ipv6hdr);
                break;
            }
            case IPV6_FRAGMENT_HEADER:
            {
                RetVal = IPv6ParseFragHdr (pPkt, ptr_ipv6hdr);
               /* IPv6ParseFragHdr returns 1 when the fragment
                * has been successfully queued and no further
                * processing is required by the IPv6 module.
                * so we just return on return value 1.
                */
                if (RetVal == 1)
                    return;
                break;
            }
            case ICMPv6_HEADER:
            {
                /* ICMPv6 Packet. */
                ICMPv6RxPacket (pPkt, ptr_ipv6hdr);
                ipv6mcb.ip6stats.InDelivers++;
                return;
            }
            case IPV6_NONE_HEADER:
            {
                ipv6mcb.ip6stats.InDelivers++;
                PBM_free(pPkt);
                return;
            }
            case IPV6_DSTOPTS_HEADER:
            {
               /* Since the destination and Hop-by-Hop 
                * options definitions are same and the
                * option types defined within them are the
                * same, we for now will call the same 
                * function for processing both these headers
                */
                RetVal = IPv6ParseHopOptions (pPkt, ptr_ipv6hdr);
                break;
            }
            case IPPROTO_UDP:
            {
                Udp6Input (pPkt, ptr_ipv6hdr);
                ipv6mcb.ip6stats.InDelivers++;
                return;
            }
            case IPPROTO_TCP:
            {
                TCP6Input (pPkt, ptr_ipv6hdr);
                ipv6mcb.ip6stats.InDelivers++;
                return;
            }            
            default:
            {
                /* We dont understand the Next header. Need to send out the parameter problem message. */
                ipv6mcb.ip6stats.InUnknownProtos++;
                ICMPv6SendParameterProblem (ICMPV6_PARAM_PROBLEM_INV_NEXT_HDR, pPkt, pPkt->Aux1);
                RetVal = -1;
                break;
            }
        }

        /* Error processing extension header */
        if (RetVal == -1)
            return;
        else
        {
            /* Scan the next extension header */
            NxtHdrVal = RetVal;
        }
    }
}

#endif
