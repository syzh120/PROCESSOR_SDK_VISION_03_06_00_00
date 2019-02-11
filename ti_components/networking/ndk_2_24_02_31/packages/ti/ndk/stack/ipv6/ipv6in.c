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
 * ======== ipv6in.c ========
 *
 * The file handles the reception of IPv6 Packets.
 *
 */


#include <stkmain.h>
#include "ipv6.h"

#ifdef _INCLUDE_IPv6_CODE

/** 
 *  @b Description
 *  @n  
 *      This function is used to process an IPv6 packet received
 *      on the network.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  pPkt     
 *      Pointer to the IPv6 packet.
 *
 *  @retval
 *   Not Applicable.
 */
void IPv6RxPacket (PBM_Pkt *pPkt)
{
    IPV6HDR*        ptr_ipv6hdr;
    int             local = 0;
    NETIF_DEVICE*   ptr_device;
    IP6N        srcAddr;
    IP6N        dstAddr;

    /* Get the interface on which the packet was received. */
    ptr_device = (NETIF_DEVICE *)pPkt->hIFRx;

    /* Proceed only if an IPv6 stack is initialized on the interface. */
    if (ptr_device->ptr_ipv6device == NULL)
    {
        /* IPv6 Stack was not initialized on the interface; we should drop the packet */
        PBM_free (pPkt);
        return;
    }

    /* Increment stats */
    ipv6mcb.ip6stats.InReceives++;

    /* Get the pointer to the IPv6 Header. */
    ptr_ipv6hdr = (IPV6HDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses out of ptr_ipv6hdr
     * as this data is potentially un-aligned (SDOCM00097361)
     */
    mmCopy((char *)&srcAddr, (char *)&ptr_ipv6hdr->SrcAddr, sizeof(IP6N));
    mmCopy((char *)&dstAddr, (char *)&ptr_ipv6hdr->DstAddr, sizeof(IP6N));

    /* Validate the packet:
     *  a) Make sure the version is correctly configured. 
     *  b) Packet Length in IPv6 Header SHOULD NOT be greater than the length of rxed pkt */
    if (((ptr_ipv6hdr->VerTC & 0xF0) != 0x60) || (ptr_ipv6hdr->PayloadLength == 0) )
    {
        ipv6mcb.ip6stats.InHdrErrors++;
        PBM_free (pPkt);
        return;
    }
    /* Packet is truncated ? */
    if (ntohs (ptr_ipv6hdr->PayloadLength) > pPkt->ValidLen)
    {
        ipv6mcb.ip6stats.InTruncatedPkts++;
        PBM_free (pPkt);
        return;
    }

    /* Store the IPv6 Header lengh and pointer in the packet. 
     * Used by IPv6 fragmentation and reassembly layer module.
     */
    pPkt->IpHdrLen = sizeof(IPV6HDR);
    pPkt->pIpHdr = (UINT8 *) ptr_ipv6hdr;

    /* Aux1 is used to hold the offset (from the start of IPv6 header) of 
     * "Next Header" field of this header. This is modified along the 
     * receive path as extension headers are parsed. 
     * Used by IPv6 fragmentation and reassembly layer module.
     */
    pPkt->Aux1 = 6;

    /* Is this a multicast packet? */
    if (IPv6IsMulticast(dstAddr))
    {
        /* Increment multicast stats */
        ipv6mcb.ip6stats.InMcastPkts++;

        /* Multicast Packet: Check if the group has been joined on the interface or not? */
        local = MLDTestGroup (pPkt->hIFRx, dstAddr);
    }
    else
    {
        /* Unicast Packet. Check if this is a loopback address? */
        if (IPv6CompareAddress(dstAddr, IPV6_LOOPBACK_ADDRESS) == 1)
        {
            /* Loopback packets are always local. */
            local = 1;
        }
        else
        {
            /* This is a non local UNICAST Packet; check the IPv6 bindings? */
            local = (int)Bind6FindByHost (pPkt->hIFRx, dstAddr);
        }
    }

    /* On IPv6 we are acting only as a HOST and not a ROUTER; thus if we received a packet
     * which is not meant for us this packet is dropped. */
    if (local == 0)
    {
        /* Increment the error counter; clean memory and return. */
        ipv6mcb.ip6stats.InForwErrors++;
        PBM_free (pPkt);
        return;
    }

    /* Increment the offset to jump over the IPv6 Header; which has been processed. */
    pPkt->DataOffset = pPkt->DataOffset + IPv6HDR_SIZE;
    pPkt->ValidLen   = pPkt->ValidLen   - IPv6HDR_SIZE;

    /* Packet is meant for the local NDK stack. Process the extension headers. */
    IPv6ParseExtnHeaders (pPkt, ptr_ipv6hdr);

    /* IPv6 Packet has been processed. */
    return;
}


#endif /* _INCLUDE_IPv6_CODE */

