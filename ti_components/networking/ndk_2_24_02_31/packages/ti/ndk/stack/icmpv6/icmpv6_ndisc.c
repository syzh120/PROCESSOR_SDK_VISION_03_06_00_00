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
 * ======== icmpv6_ndisc.c ========
 *
 * The file has functions which handle the Neighbour Discovery
 * process as defined in the ICMPv6 Protocol
 *
 */

#include <stkmain.h>

#ifdef _INCLUDE_IPv6_CODE

/**********************************************************************
 *************************** Local Definitions ************************
 **********************************************************************/

/* This value is the number of ticks per sec. Configured right now as 2 Ticks per sec i.e. 500ms */
#define TICKS_PER_SEC   2
const UINT32 TIME_2HOURS = (2 * 60 * 60 * TICKS_PER_SEC);

/**********************************************************************
 **************************** NDISC Functions *************************
 **********************************************************************/

/** 
 *  @b Description
 *  @n  
 *      The function is used to send out a Neighbor solicitation
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_device
 *      The Network Interface object on which the packet is to be transmitted.
 *
 *  @param[in]  DstAddress
 *      The destination address to which the NS packet is directed too.
 *      As per RFC 2461; this can either be the Solicted Node Multicast
 *      Address or the the target address.
 *      
 *  @param[in]  SrcAddress 
 *      The Source address of the interface; this can either be UNSPECIFIED
 *      i.e. :: if the NS is being sent for DAD or it will be the address
 *      of the source interface.
 *
 *  @param[in]  TargetAddress
 *      The Target address to which the NS message is being transmitted.
 *
 *  @retval
 *      0   -   Success
 *  @retval
 *      <0  -   Error
 */
int ICMPv6SendNS (NETIF_DEVICE* ptr_device, IP6N DstAddress, IP6N SrcAddress, IP6N TargetAddress)
{
    ICMPV6_NS_HDR*  ptr_icmpv6Hdr;
    PBM_Pkt*        pPkt;
    UINT16          len;
    PSEUDOV6        pseudo_hdr;
    IPV6HDR*        ptr_ipv6hdr;
    ICMPV6_OPT*     ptr_icmpv6Opt;
    UINT8*          ptr_MacAddress = NULL;

    /* Increment the stats. */
    icmp6stats.OutMsgs++;

    /* Calculate the length of the NS packet which needs to be transmitted. */
    len = sizeof (ICMPV6_NS_HDR);

    /* Check if we need to add the Source Link Layer Address option or not? 
     * This is required only if the source address is specified */
    if (IPv6CompareAddress(SrcAddress, IPV6_UNSPECIFIED_ADDRESS) == 0)
    {
        /* The source address was specified. We will now be advertising our 
         * source link local address to the world. Thus we need to account for
         * this in the lenght of the packet. 
         *  Increment the length by 1 (Type) + 1 (Len) + 6 (MAC Address) */
        len = len + 8;
        ptr_MacAddress = &ptr_device->mac_address[0];
    }

    /* Allocate memory for the Neighbor Solicitation Packet. Ensure that the
     * allocation accounts for the IPv6 Header. */
    pPkt = NIMUCreatePacket (len + sizeof (IPV6HDR));
    if (pPkt == NULL)
    {
        /* Error: Unable to allocate packet memory. */
        DbgPrintf(DBG_INFO, "ICMPv6SendNS: OOM\n");
        NotifyLowResource();
        return -1;
    }

    /* Create the PSEUDO Header */
    pseudo_hdr.SrcAddr = SrcAddress;
    pseudo_hdr.DstAddr = DstAddress;
    pseudo_hdr.PktLen  = htons(len);
    pseudo_hdr.Rsvd[0] = 0;
    pseudo_hdr.Rsvd[1] = 0;
    pseudo_hdr.Rsvd[2] = 0;
    pseudo_hdr.NxtHdr  = IPPROTO_ICMPV6;

    /* Get the pointer to the ICMPv6 Header. */
    ptr_icmpv6Hdr = (ICMPV6_NS_HDR *)(pPkt->pDataBuffer + pPkt->DataOffset + sizeof(IPV6HDR));

    /* Initialize the ICMPv6 Header. */
    ptr_icmpv6Hdr->Type          = ICMPV6_NEIGH_SOLICIT;
    ptr_icmpv6Hdr->Code          = 0;
    ptr_icmpv6Hdr->Reserved      = 0;
    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses into ptr_icmpv6Hdr
     * as ptr_icmpv6Hdr->{SrcAddr, DstAddr] are potentially un-aligned
     * (SDOCM00097361)
     */
    mmCopy((char *)&ptr_icmpv6Hdr->TargetAddress, (char *)&TargetAddress,
            sizeof(IP6N));

    /* Check if we need to any options; options are added after the NS header. */
    if (ptr_MacAddress != NULL)
    {
        /* Get the pointer to the ICMPv6 option */
        ptr_icmpv6Opt = (ICMPV6_OPT *)(pPkt->pDataBuffer + pPkt->DataOffset + sizeof(IPV6HDR) + sizeof(ICMPV6_NS_HDR));

        /* Populate the option buffer. */
        ptr_icmpv6Opt->Type   = ICMPV6_SOURCE_LL_ADDRESS;
        ptr_icmpv6Opt->Length = 1;

        /* Copy the MAC Address into the option data area */
        mmCopy (((UINT8 *)ptr_icmpv6Opt + sizeof(ICMPV6_OPT)), ptr_MacAddress, 6);
    }

    /* Compute the ICMPv6 Checksum. */
    ptr_icmpv6Hdr->Checksum = 0;
    ptr_icmpv6Hdr->Checksum = IPv6Layer4ComputeChecksum ((UINT8 *)ptr_icmpv6Hdr, &pseudo_hdr);

    /* Now get the pointer to the IPv6 Header and initialize its various fields. */
    ptr_ipv6hdr             = (IPV6HDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses into ptr_ipv6hdr
     * as ptr_ipv6hdr->{SrcAddr, DstAddr] are potentially un-aligned
     * (SDOCM00097361)
     */
    mmCopy((char *)&ptr_ipv6hdr->SrcAddr, (char *)&SrcAddress, sizeof(IP6N));
    mmCopy((char *)&ptr_ipv6hdr->DstAddr, (char *)&DstAddress, sizeof(IP6N));

    ptr_ipv6hdr->HopLimit   = 255;
    ptr_ipv6hdr->NextHeader = IPPROTO_ICMPV6;

    /* Set the valid len of the packet; which is the ICMP-NS Header. */
    pPkt->ValidLen = len;

    /* If the packet is a DAD NS Packet; then we cant use the routing tables
     * to decide where the packet should go; the decision can be taken here itself. */
    pPkt->hIFTx = (HANDLE)ptr_device;

    /* Pass the packet to the IPv6 Layer for transmission. */
    IPv6TxPacket (pPkt, 0);
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function is used to send out a Neighbor Advertisment.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_device
 *      The Network Interface object on which the packet is to be transmitted.
 *
 *  @param[in]  DstAddress
 *      The destination address to which the NA packet is directed too.
 *      
 *  @param[in]  SrcAddress 
 *      The Source address of the interface
 *
 *  @param[in]  TargetAddress
 *      The Target address to which the NA message is being transmitted.
 *
 *  @param[in]  Flags
 *      The value of the (R)eserved, (S)olicited and (O)verride flags.
 *
 *  @retval
 *      0   -   Success
 *  @retval
 *      <0  -   Error
 */
int ICMPv6SendNA (NETIF_DEVICE* ptr_device, IP6N DstAddress, IP6N SrcAddress, IP6N TargetAddress, UINT8 Flags)
{
    ICMPV6_NA_HDR*  ptr_icmpv6Hdr;
    PBM_Pkt*        pPkt;
    PSEUDOV6        pseudo_hdr;
    ICMPV6_OPT*     ptr_icmpv6Opt;
    IPV6HDR*        ptr_ipv6hdr;

    /* Increment the stats. */
    icmp6stats.OutMsgs++;

    /* Calculate the length of the NA packet which needs to be transmitted. We always add the TARGET
     * Link Layer address option in our NA packets. 
     *  i.e. Allocate an additional 1 (Type) + 1 (Len) + 6 (MAC Address) i.e. 8 bytes. */
    pPkt = NIMUCreatePacket(sizeof (ICMPV6_NA_HDR) + 8 + sizeof (IPV6HDR));
    if (pPkt == NULL)
    {
        /* Error: Unable to allocate packet memory. */
        DbgPrintf(DBG_INFO, "ICMPv6SendNA: OOM\n");
        NotifyLowResource();
        return -1;
    }

    /* Create the PSEUDO Header */
    pseudo_hdr.SrcAddr = SrcAddress;
    pseudo_hdr.DstAddr = DstAddress;
    pseudo_hdr.PktLen  = htons(sizeof (ICMPV6_NA_HDR) + 8);
    pseudo_hdr.Rsvd[0] = 0;
    pseudo_hdr.Rsvd[1] = 0;
    pseudo_hdr.Rsvd[2] = 0;
    pseudo_hdr.NxtHdr  = IPPROTO_ICMPV6;

    /* Get the pointer to the ICMPv6 Header. */
    ptr_icmpv6Hdr = (ICMPV6_NA_HDR *)(pPkt->pDataBuffer + pPkt->DataOffset + sizeof(IPV6HDR));

    /* Initialize the ICMPv6 Header. */
    ptr_icmpv6Hdr->Type          = ICMPV6_NEIGH_ADVERTISMENT;
    ptr_icmpv6Hdr->Code          = 0;
    ptr_icmpv6Hdr->Flags         = Flags;
    ptr_icmpv6Hdr->Reserved[0]   = 0;
    ptr_icmpv6Hdr->Reserved[1]   = 0;
    ptr_icmpv6Hdr->Reserved[2]   = 0;
    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses into ptr_icmpv6Hdr
     * as ptr_icmpv6Hdr->{SrcAddr, DstAddr] are potentially un-aligned
     * (SDOCM00097361)
     */
    mmCopy((char *)&ptr_icmpv6Hdr->TargetAddress, (char *)&TargetAddress,
            sizeof(IP6N));

    /* Get the pointer to the ICMPv6 Option which comes after the ICMPv6 NA Header. */
    ptr_icmpv6Opt = (ICMPV6_OPT *)(pPkt->pDataBuffer + pPkt->DataOffset + sizeof(IPV6HDR) + sizeof(ICMPV6_NA_HDR));
    ptr_icmpv6Opt->Type   = ICMPV6_TARGET_LL_ADDRESS;
    ptr_icmpv6Opt->Length = 1;

    /* Now we copy the MAC Address of the device into this space. */
    mmCopy (((UINT8 *)ptr_icmpv6Opt + sizeof(ICMPV6_OPT)), &ptr_device->mac_address[0], 6);

    /* Compute the ICMPv6 Checksum. */
    ptr_icmpv6Hdr->Checksum = 0;
    ptr_icmpv6Hdr->Checksum = IPv6Layer4ComputeChecksum ((UINT8 *)ptr_icmpv6Hdr, &pseudo_hdr);

    /* Now get the pointer to the IPv6 Header and initialize its various fields. */
    ptr_ipv6hdr             = (IPV6HDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses into ptr_ipv6hdr
     * as ptr_ipv6hdr->{SrcAddr, DstAddr] are potentially un-aligned
     * (SDOCM00097361)
     */
    mmCopy((char *)&ptr_ipv6hdr->SrcAddr, (char *)&SrcAddress, sizeof(IP6N));
    mmCopy((char *)&ptr_ipv6hdr->DstAddr, (char *)&DstAddress, sizeof(IP6N));

    ptr_ipv6hdr->HopLimit   = 255;
    ptr_ipv6hdr->NextHeader = IPPROTO_ICMPV6;

    /* Set the valid len of the packet; which is the ICMP-NA Header + Target Option */
    pPkt->ValidLen = (sizeof (ICMPV6_NA_HDR) + 8);

    /* Set the interface handle on which the packet is to be transmitted. */
    pPkt->hIFTx    = (HANDLE)ptr_device;

    /* Pass the packet to the IPv6 Layer for transmission. */
    IPv6TxPacket (pPkt, 0);
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function handles the ICMPv6 Neighbour Solicitation Message
 *
 *  @param[in]  pPkt
 *      Pointer to the entire ICMPv6 Packet.
 *
 *  @param[in]  ptr_ipv6hdr
 *      Pointer to the IPv6 Header.
 *
 *  @sa
 *      RFC-2461 Section 7.1.1, 7.2.3 & 7.2.4.
 *
 *  @retval
 *      0   -   Success
 *  @retval
 *      <0  -   Error
 */
int ICMPv6RecvNS (PBM_Pkt* pPkt, IPV6HDR* ptr_ipv6hdr)
{
    ICMPV6_NS_HDR*  ptr_icmpv6Hdr;
    HANDLE          hBind6Obj;
    NETIF_DEVICE*   ptr_device;
    ICMPV6_OPT*     ptr_icmpv6Opt;
    int             payload_len;
    UINT8*          ptr_source_ll_address = NULL;
    UINT8           Flags;
    HANDLE          hRoute6;
    UINT8           IsSrcAddressUnspecified = 0;
    IP6N            srcAddr;
    IP6N            dstAddr;
    IP6N            targetAddress;

    /*
     * Validate the packet: The hop limit in the packet should be 255.
     * (Fix for SDOCM00100321)
     */
    if (ptr_ipv6hdr->HopLimit != 255) {
        return -1;
    }

    /* Get the pointer to the Neighbour Solicitation Message */
    ptr_icmpv6Hdr = (ICMPV6_NS_HDR *) (pPkt->pDataBuffer + pPkt->DataOffset);

    /*
     * Validate the packet: The ICMP Code field in the packet should be 0, else
     * the packet should be silently dropped (Fix for SDOCM00101510).
     */
    if (ptr_icmpv6Hdr->Code != 0) {
        return -1;
    }

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses out of ptr_ipv6hdr
     * as this data is potentially un-aligned (SDOCM00097361)
     */
    mmCopy((char *)&srcAddr,       (char *)&ptr_ipv6hdr->SrcAddr, sizeof(IP6N));
    mmCopy((char *)&dstAddr,       (char *)&ptr_ipv6hdr->DstAddr, sizeof(IP6N));
    mmCopy((char *)&targetAddress, (char *)&ptr_icmpv6Hdr->TargetAddress,
            sizeof(IP6N));

    /* Validate the packet: The target address should be a UNICAST or ANYCAST address. */
    if (IPv6IsMulticast(targetAddress))
        return -1;

    /* Check if the Source Address of the NS is UNSPECIFIED or not? Set the Flag. */
    if (IPv6CompareAddress(srcAddr, IPV6_UNSPECIFIED_ADDRESS) == 1)
        IsSrcAddressUnspecified = 1;

    /* Process and validate any options which exist in the packet. 
     * We have already processed the ICMP NS Header; so now start after it. */
    payload_len   = ntohs (ptr_ipv6hdr->PayloadLength) - sizeof(ICMPV6_NS_HDR);
    ptr_icmpv6Opt = (ICMPV6_OPT *)(pPkt->pDataBuffer + pPkt->DataOffset + sizeof(ICMPV6_NS_HDR));

    /* Cycle through all the options and extract them. */
    while (payload_len > 0)
    {
        /* Ensure that the length value is non-zero */
        if (ptr_icmpv6Opt->Length == 0)
            return -1;

        /* Process the options. */
        switch (ptr_icmpv6Opt->Type)
        {
            case ICMPV6_SOURCE_LL_ADDRESS:
            {
                /* Get the pointer target Link Layer Address */
                ptr_source_ll_address = (UINT8 *)((UINT8 *)ptr_icmpv6Opt + sizeof(ICMPV6_OPT));
                break;
            }
            case ICMPV6_TARGET_LL_ADDRESS:
            case ICMPV6_PREFIX_INFORMATION:
            case ICMPV6_REDIRECTED_HEADER:
            case ICMPV6_MTU:
            {
                break;
            }            
            default:
            {
                /* Error: Unknown type received. We skip this option and carry on. */
                break;
            } 
        }

        /* Get the next option */
        payload_len = payload_len - (ptr_icmpv6Opt->Length << 3);
        ptr_icmpv6Opt = (ICMPV6_OPT *) ((char*)ptr_icmpv6Opt + (ptr_icmpv6Opt->Length << 3));
    }

    /* We have cycled through all the options and have them extracted; now do some of the
     * standard RFC validations here. */

    /* Validation: If the Source Address is UNSPECIFIED; the SOURCE LL option should be NULL. */
    if ((IsSrcAddressUnspecified == 1) && (ptr_source_ll_address != NULL))
        return -1;

    /* Validation: For Multicast Solicitations; the Source LL option should be NON NULL */
    /*
     * Fix for SDOCM00100304: Check for source address = "::". Must accept
     * NS message that has:
     *   
     *     source address: unspecified (all zeros "::" address)
     *     dest   address: solicited node multicast address
     *     link layer source address: should be NULL
     *
     * Such a message is used in DAD. Dropping packet here and not responding
     * allows another host to duplicate our address!
     */
    if ((IsSrcAddressUnspecified == 0) && (IPv6IsMulticast(dstAddr) == 1) &&
            (ptr_source_ll_address == NULL)) {
        return -1;
    }

    /* DAD Check: Validate the address and make sures it not the same as one on which
     * we are *also* running DAD. This is a SCENARIO; where both us and the other node
     * have the same address and executing DAD at the same time. */
    if (IsSrcAddressUnspecified == 1)
    {
        /* Validation: If the source address is UNSPECIFIED; then the destination address 
         * should be a SOLICITED Node Multicast Address */
        if (IPv6IsMulticast(dstAddr) == 0)
            return -1;

        /* Run the packet through the DAD. */
        if (Bind6DADCheck(pPkt->hIFRx, targetAddress) < 0)
            return -1;
    }
    
    /* Get the BIND object matching the Target Address; if there is no BIND object then
     * we cannot handle this packet. */
    hBind6Obj = Bind6FindByHost (pPkt->hIFRx, targetAddress);
    if (hBind6Obj == 0)
        return -1;

    /* Get the network device associated with the address being 'solicited'. */
    ptr_device = Bind6GetInterfaceHandle (hBind6Obj);
    
    /* Our Address was permanent; check if this is a DAD Packet being sent to us. */
    if (IsSrcAddressUnspecified == 1)
    {
        /* This was a DAD NS being sent; our address is permanent and so we win. 
         * Send out the appropriate Neighbour Advertisment message as specified in 
         * RFC 2461 Section 7.2.4.
         *  - Target Address should be copied from the SOLICITATION Target Address
         *  - Set the Router only if we are router.
         *  - Override Flag should be set; since we are not providing any PROXY Service.
         *  - If the Source of the Solicitation is the UNSPECIFIED Address 
         *      a) Node must Multicast Advertisment to ALL Nodes Address.
         *      b) Set Solicited Flag to 0. */        
        if (ipv6mcb.IsRouter)
            Flags = ICMPV6_NA_O_FLAG | ICMPV6_NA_R_FLAG;
        else
            Flags = ICMPV6_NA_O_FLAG;

        /* Send out the Neighbour Advertisment. */
        ICMPv6SendNA (ptr_device, IPV6_ALL_NODES_ADDRESS, targetAddress, 
                      targetAddress, Flags);

        /* Cleanout the Neighbor Solicitation packet. Return success; since the packet was handled */
        PBM_free (pPkt);
        return 0;
    }

    /* We need to update the Neighbor Table at this stage. */
    hRoute6 = Rt6Find (FLG_RTE_HOST, srcAddr, pPkt->hIFRx);
    if (hRoute6 == 0)
    {
        /* Host Routing Entry does not exist; check the GATEWAY Table too. */
        hRoute6 = Rt6FindDefaultRouter (srcAddr, pPkt->hIFRx);
        if (hRoute6 == 0)
        {
            /* RFC 2461 Section 7.2.3 states that if a Neighbor entry does not exist; 
             * then we should create a new one. The entry does not exist in the HOST or GATEWAY tables. */
#ifdef ICMPV6_NDISC_DEBUG
            hRoute6 =
#endif
            Rt6Create (FLG_RTE_HOST, srcAddr, IPV6_HOST_MASK, IPV6_UNSPECIFIED_ADDRESS, 
                                 ptr_source_ll_address, pPkt->hIFRx, 0);
#ifdef ICMPV6_NDISC_DEBUG
            DbgPrintf(DBG_INFO, "ICMPv6RecvNS: DEBUG: Received a VALID NS for SOURCE Address Creating new RT6 Entry 0x%x\n", hRoute6);
            IPv6DisplayIPAddress (srcAddr);
#endif
        }
        else
        {
            /* The Entry exists in the GATEWAY Table; so update it accordingly. */
            Rt6Update (hRoute6, ICMPV6_NEIGH_SOLICIT, ptr_source_ll_address, 0, 0);
#ifdef ICMPV6_NDISC_DEBUG
            DbgPrintf(DBG_INFO, "ICMPv6RecvNS: DEBUG: Received a VALID NS for SOURCE Address Updating GATEWAY Entry 0x%x\n", hRoute6);
            IPv6DisplayIPAddress (srcAddr);
#endif
        }
    }
    else
    {
        /* RFC 2461 Section 7.2.3 states that if a Neighbor entry exists; then it needs to be updated */
        Rt6Update (hRoute6, ICMPV6_NEIGH_SOLICIT, ptr_source_ll_address, 0, 0);
#ifdef ICMPV6_NDISC_DEBUG
        DbgPrintf(DBG_INFO, "ICMPv6RecvNS: DEBUG: Received a VALID NS for SOURCE Address Updating RT6 Entry 0x%x\n", hRoute6);
        IPv6DisplayIPAddress (srcAddr);
#endif
    }

    /* We now need to send out a NA; 
     *  - Target Address should be copied from the NS Target Address 
     *  - Destination Address should be SRC Address of the NS. 
     *  - Solicited Flag should be set to 1. 
     *  - Override Flag should be set to 1 if not providing PROXY Service */
    if (ipv6mcb.IsRouter)
        Flags = ICMPV6_NA_S_FLAG | ICMPV6_NA_R_FLAG | ICMPV6_NA_O_FLAG;
    else
        Flags = ICMPV6_NA_S_FLAG | ICMPV6_NA_O_FLAG;

    /* Send out the NA message in response to the NS request. */
    ICMPv6SendNA (ptr_device, srcAddr, targetAddress,
                  targetAddress, Flags);

    /* Cleanout the Neighbor Solicitation packet. Return success; since the packet was handled */
    PBM_free (pPkt);
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function handles the ICMPv6 Neighbour Advertisment Message
 *
 *  @param[in]  pPkt
 *      Pointer to the entire ICMPv6 Packet.
 *
 *  @param[in]  ptr_ipv6hdr
 *      Pointer to the IPv6 Header.
 *
 *  @sa
 *      RFC-2461 Section 7.1.2
 *
 *  @retval
 *      0   -   Success
 *  @retval
 *      <0  -   Error
 */
int ICMPv6RecvNA (PBM_Pkt* pPkt, IPV6HDR* ptr_ipv6hdr)
{
    ICMPV6_NA_HDR*  ptr_icmpv6Hdr;
    int             payload_len;
    ICMPV6_OPT*     ptr_icmpv6Opt;
    HANDLE          hBind6Obj;
    HANDLE          hRoute6;
    UINT8*          ptr_target_ll_address = NULL;
    IP6N            srcAddr;
    IP6N            dstAddr;
    IP6N            targetAddress;

    /* Get the pointer to the Neighbour Advertisment Message */
    ptr_icmpv6Hdr = (ICMPV6_NA_HDR *) (pPkt->pDataBuffer + pPkt->DataOffset);

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses out of ptr_ipv6hdr
     * as this data is potentially un-aligned (SDOCM00097361)
     */
    mmCopy((char *)&srcAddr, (char *)&ptr_ipv6hdr->SrcAddr, sizeof(IP6N));
    mmCopy((char *)&dstAddr, (char *)&ptr_ipv6hdr->DstAddr, sizeof(IP6N));
    mmCopy((char *)&targetAddress, (char *)&ptr_icmpv6Hdr->TargetAddress,
            sizeof(IP6N));

    /* Validate the packet: The hop limit in the packet should be 255. */
    if (ptr_ipv6hdr->HopLimit != 255)
        return -1;

    /* The length of the packet as derived from the IP header should be >= 24 bytes*/
    if (ntohs(ptr_ipv6hdr->PayloadLength) < 24)
        return -1;

    /* The ICMP Code for Neighbor advertisments should be 0. */
    if (ptr_icmpv6Hdr->Code != 0)
        return -1;

    /* The target address should not be a Multicast address. */
    if (IPv6IsMulticast (targetAddress))
        return -1;

    /* If the destination address is a multicast address; */
    if (IPv6IsMulticast(dstAddr))
    {
        /* Then the (S)olicited flag should be 0.  */
        if (ptr_icmpv6Hdr->Flags & ICMPV6_NA_S_FLAG) 
            return -1;
    }

    /* Process and validate any options which exist in the packet. 
     * We have already processed the ICMP NA Header; so now start after it. */
    payload_len   = ntohs (ptr_ipv6hdr->PayloadLength) - sizeof(ICMPV6_NA_HDR);
    ptr_icmpv6Opt = (ICMPV6_OPT *)(pPkt->pDataBuffer + pPkt->DataOffset + sizeof(ICMPV6_NA_HDR));

    /* Process and cycle through all the options. */
    while (payload_len > 0)
    {
        /* Ensure that the length value is non-zero */
        if (ptr_icmpv6Opt->Length == 0)
            return -1;

        /* Process the options. */
        switch (ptr_icmpv6Opt->Type)
        {
            case ICMPV6_TARGET_LL_ADDRESS:
            {
                /* Get the pointer target Link Layer Address */
                ptr_target_ll_address = (UINT8 *)((UINT8 *)ptr_icmpv6Opt + sizeof(ICMPV6_OPT));
                break;
            }
            case ICMPV6_SOURCE_LL_ADDRESS:
            case ICMPV6_PREFIX_INFORMATION:
            case ICMPV6_REDIRECTED_HEADER:
            case ICMPV6_MTU:
            {
                break;
            }            
            default:
            {
                /* Error: Unknown type received. We skip this option and carry on. */
                break;
            } 
        }

        /* Get the next option */
        payload_len = payload_len - (ptr_icmpv6Opt->Length << 3);
        ptr_icmpv6Opt = (ICMPV6_OPT *) ((char*)ptr_icmpv6Opt + (ptr_icmpv6Opt->Length << 3));
    }

    /* DAD Check: Validate the address and make sures it not the same as one on which
     * we are *also* running DAD. */
    if (Bind6DADCheck(pPkt->hIFRx, targetAddress) < 0)
        return -1;

    /* Control comes here implies that this is a "VALID Advertisment" 
     *  So lets check if the NA was for us. */
    hBind6Obj = Bind6FindByHost (pPkt->hIFRx, targetAddress);
    if (hBind6Obj != 0)
    {
        /* Our address was permanent; yet somebody else is also advertising the same address. */
        DbgPrintf(DBG_INFO, "ICMPv6RecvNA: WARNING --> Misbehaving IPv6 Node detected on network\n");
        return -1;
    }
    else
    {
        /* We need to update the Neighbor Table at this stage. 
         * RFC 2461 Section 7.2.5 states that if a NA is received search the Neighbor Cache; 
         * if no entry is found silently discard the packet; dont need to create a new one.
         * We need to find to have a HOST Route which exists for the Target Address. */
        hRoute6 = Rt6Find (FLG_RTE_HOST, srcAddr, pPkt->hIFRx);
        if (hRoute6 != 0)
        {
            /* Found a HOST Route: Update it accordingly. */
            Rt6Update (hRoute6, ICMPV6_NEIGH_ADVERTISMENT, ptr_target_ll_address, ptr_icmpv6Hdr->Flags, 0);
        }
        else
        {
            /* Not a HOST Route: Maybe we need to search the DEFAULT Routing Table too. */
            hRoute6 = Rt6FindDefaultRouter (srcAddr, pPkt->hIFRx);
            if (hRoute6 != 0)
            {
                /* Found a GATEWAY Route: Update it accordingly. */
                Rt6Update (hRoute6, ICMPV6_NEIGH_ADVERTISMENT, ptr_target_ll_address, ptr_icmpv6Hdr->Flags, 0);
            }
        }

#ifdef ICMPV6_NDISC_DEBUG
        DbgPrintf(DBG_INFO, "ICMPv6RecvNA: DEBUG: Received a VALID NA Route6: 0x%x with TA:\n", hRoute6);
        IPv6DisplayIPAddress (targetAddress);
#endif
    }

    /* Cleanout the Neighbor Advertisment packet. Return success; since the packet was handled */
    PBM_free (pPkt);
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function handles the ICMPv6 Router Advertisment Message
 *
 *  @param[in]  pPkt
 *      Pointer to the entire ICMPv6 Packet.
 *
 *  @param[in]  ptr_ipv6hdr
 *      Pointer to the IPv6 Header.
 *
 *  @sa
 *      RFC-2461 Section 6.1
 *
 *  @retval
 *      0   -   Success
 *  @retval
 *      <0  -   Error
 */
int ICMPv6RecvRA (PBM_Pkt* pPkt, IPV6HDR* ptr_ipv6hdr)
{
    ICMPV6_RA_HDR*      ptr_icmpv6Hdr;
    ICMPV6_OPT*         ptr_icmpv6Opt;
    int                 payload_len;
    NETIF_DEVICE*       ptr_device;
    UINT8*              ptr_src_ll_address = NULL;
    UINT32              mtu                = 0;
    ICMPV6_PREFIX_OPT*  ptr_prefix_opt     = NULL;
    IP6N                address;
    HANDLE              hRoute6;
    UINT32              RetransTime;
    UINT32              ReachableTime;
    IP6N                srcAddr;
    IP6N                dstAddr;

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses out of ptr_ipv6hdr
     * as this data is potentially un-aligned (SDOCM00097361)
     */
    mmCopy((char *)&srcAddr, (char *)&ptr_ipv6hdr->SrcAddr, sizeof(IP6N));
    mmCopy((char *)&dstAddr, (char *)&ptr_ipv6hdr->DstAddr, sizeof(IP6N));

    /* Get the interface on which the packet was received. */
    ptr_device = (NETIF_DEVICE *)pPkt->hIFRx;

    /* Get the pointer to the Router Advertisment Message */
    ptr_icmpv6Hdr = (ICMPV6_RA_HDR *) (pPkt->pDataBuffer + pPkt->DataOffset);

    /* Validate the packet: The hop limit in the packet should be 255. */
    if (ptr_ipv6hdr->HopLimit != 255)
        return -1;

    /* The length of the packet as derived from the IP header should be >= 16 bytes*/
    if (ntohs(ptr_ipv6hdr->PayloadLength) < 16)
        return -1;

    /* The ICMP Code for Router advertisments should be 0. */
    if (ptr_icmpv6Hdr->Code != 0)
        return -1;

    /* The IPv6 Source address in the packet should be a LINK Local Address. */
    if ((srcAddr.u.addr16[0] & IPV6_LINKLOCALMASK.u.addr16[0]) != htons (0xFE80))
        return -1;

    /* Extract the Retransmit and Reachable Times from the packet. */
    mmCopy ((void*)&RetransTime, (void *)&ptr_icmpv6Hdr->RetransTime, 4);
    mmCopy ((void*)&ReachableTime, (void *)&ptr_icmpv6Hdr->ReachableTime, 4);

    /* Process and validate any options which exist in the packet. 
     * We have already processed the ICMP NA Header; so now start after it. */
    payload_len   = ntohs (ptr_ipv6hdr->PayloadLength) - sizeof(ICMPV6_RA_HDR);
    ptr_icmpv6Opt = (ICMPV6_OPT *)(pPkt->pDataBuffer + pPkt->DataOffset + sizeof(ICMPV6_RA_HDR));

    /* Process and cycle through all the options. */
    while (payload_len > 0)
    {
        /* Ensure that the length value is non-zero */
        if (ptr_icmpv6Opt->Length == 0)
            return -1;

        /* Process the options. */
        switch (ptr_icmpv6Opt->Type)
        {
            case ICMPV6_SOURCE_LL_ADDRESS:
            {
                /* Get the pointer source Link Layer Address */
                ptr_src_ll_address = (UINT8 *)((UINT8 *)ptr_icmpv6Opt + sizeof(ICMPV6_OPT));
                break;
            }
            case ICMPV6_MTU:
            {
                /* Copy the MTU */
                mmCopy ((void *)&mtu, (void *)((UINT8 *)ptr_icmpv6Opt + sizeof(ICMPV6_OPT) + 2), 4);

                /* Convert the MTU to Host Order. */
                mtu = ntohl (mtu);

                /* Can we accept this MTU? 
                 *  The published MTU cannot be less than the Min required for IPv6 or
                 *  Be greater than the one belonging to the interface on which the packet
                 *  was received. */
                if ((mtu < MIN_IPV6_MTU) || (mtu > ptr_device->mtu))
                    return -1;
                break;
            }
            case ICMPV6_PREFIX_INFORMATION:
            {
                IPV6_DEV_RECORD*    ptr_ipv6device;
                UINT32              PreferredLifetime;
                UINT32              ValidLifetime;
                IP6N                SubnetMask;
                HANDLE              hBind6Obj;
                UINT32              StoredLifetime;
                HANDLE              hPrefixRoute;

                /* Get the IPv6 Device Information. */
                ptr_ipv6device = (IPV6_DEV_RECORD *)ptr_device->ptr_ipv6device;

                /* Get the pointer to the prefix information */
                ptr_prefix_opt = (ICMPV6_PREFIX_OPT *)ptr_icmpv6Opt;

                /* Get the preferred and valid lifetimes from the packet. */
                mmCopy ((void*)&ValidLifetime, (void *)&ptr_prefix_opt->ValidLifetime, 4);
                mmCopy ((void*)&PreferredLifetime, (void *)&ptr_prefix_opt->PreferredLifetime, 4);

                /* Store the lifetimes in host order. */
                ValidLifetime     = ntohl(ValidLifetime);
                PreferredLifetime = ntohl(PreferredLifetime);

                /* Validate the fields: Prefix length can be between 0 and 128. */
                if (ptr_prefix_opt->PrefixLength > 128)
                    return -1;

                /* Here we process the Prefix Information option as specified in 
                 * RFC 2462 Section 5.5.3: Router Advertisment Processing. 
                 *
                 * If the prefix option has the prefix as Link Local then it should be ignored. */
                if ((ptr_prefix_opt->Prefix.u.addr16[0] & IPV6_LINKLOCALMASK.u.addr16[0]) == htons (0xFE80))
                    break;

                /* If the preferred lifetime > valid lifetime; ignore the option */
                if (PreferredLifetime > ValidLifetime)
                    break;

                /* Check the length of the prefix and that of the interface identifier. 
                 *  Currently on NDK we support only 64 bit Interface Identifiers. */
                if ((ptr_prefix_opt->PrefixLength + 64) > 128)
                    break;

                /* Create the subnet mask; currently we support 64 bit Interface Identifiers only
                 * This means that the Subnet Mask cannot be > 64 bits. Hence the */
                IPv6GetSubnetMaskFromBits (&SubnetMask, ptr_prefix_opt->PrefixLength);

                /* If the ON Link Flag is SET; we follow RFC 2461 Section 6.3.4 */
                if (ptr_prefix_opt->Flags & ICMPV6_PREFIX_OPT_L_FLAG)
                {
                    /* Check if the Routing Prefix Exists or not? */
                    hPrefixRoute = Rt6Find (FLG_RTE_CLONING, ptr_prefix_opt->Prefix, ptr_device);
                    if (hPrefixRoute == 0)
                    {
                        /* Routing Prefix does not exist; we need to create a new one only if the
                         * Valid Lifetime is non-zero. */
                        if (ValidLifetime != 0)
                        {
                            /* Create a Routing Entry for this prefix. 
                             *  This is a CLONING Route because its actually a network route which can be 
                             *  instantiated to have multiple host routes. 
                             *  There is no Default Gateway associated with the route since this is an 
                             *  ON Link Prefix. */
                            Rt6Create (FLG_RTE_CLONING, ptr_prefix_opt->Prefix, SubnetMask, 
                                       IPV6_UNSPECIFIED_ADDRESS, NULL, ptr_device, ValidLifetime);
                        }
                    }
                    else
                    {
                        /* There exists a ROUTING Prefix; */
                        if (ValidLifetime == 0)
                        {
                            /* If the Valid Lifetime is 0; then we can delete the prefix. */
                            Rt6Free (hPrefixRoute);
                        }
                        else
                        {
                            /* If the Valid Lifetime is non 0; then we update it to the new time. */
                            Rt6Update (hPrefixRoute, ICMPV6_ROUTER_ADVERTISMENT, NULL, 0, ValidLifetime);
                        }
                    }
                }

                /* If the Autonomous Flag is SET; we follow the RFC 2462 Section 5.5.3 and procees the option
                 * accordingly. */ 
                if (ptr_prefix_opt->Flags & ICMPV6_PREFIX_OPT_A_FLAG)
                {
                    /* Form the new address we need to join; copy the higher order 64 bits from the prefix*/
                    address.u.addr16[0] = ptr_prefix_opt->Prefix.u.addr16[0];
                    address.u.addr16[1] = ptr_prefix_opt->Prefix.u.addr16[1];
                    address.u.addr16[2] = ptr_prefix_opt->Prefix.u.addr16[2];
                    address.u.addr16[3] = ptr_prefix_opt->Prefix.u.addr16[3];

                    /* The lower order 64 bits i.e. 8 bytes are the interface Identifier. */
                    mmCopy ((void *)&address.u.addr16[4], (void *)&ptr_ipv6device->EUI64[0], 8);

                    /* Check if the address binding exists or not? */
                    hBind6Obj = Bind6FindByHost (ptr_device,address);
                    if (hBind6Obj == 0)
                    {
                        /* Create a new address binding on the interface. */
                        Bind6New (ptr_device, address, SubnetMask, ValidLifetime, PreferredLifetime, 0);
                    }
                    else
                    {
                        /* Now get the Stored Lifetime of the binding object. */
                        StoredLifetime = Bind6GetLifetime (hBind6Obj);

                        /* If the stored and received lifetimes are infinite; dont do anything. */
                        if ((StoredLifetime == INFINITE_LT) && (ValidLifetime == INFINITE_LT))
                            break;

                        /* Update the Lifetime in the object. 
                         *  If the received lifetime > 2 hours of stored lifetime; update it. */
                        if (ValidLifetime > StoredLifetime + TIME_2HOURS)
                            Bind6SetLifetime (hBind6Obj, ValidLifetime);

                        /* If the stored lifetime is less than or equal to 2 hours and the received lifetime is 
                         * less than or equal to Stored Lifetime; we need to check if the RA is authenticated; 
                         * currently on NDK we dont support authentication; so we will not do anything. */
                        if ((StoredLifetime < (llTimerGetTime(0) + TIME_2HOURS)) && 
                            (ValidLifetime <= StoredLifetime))
                            break;

                        /* Reset the lifetime to be 2 hours. */
                        Bind6SetLifetime (hBind6Obj, llTimerGetTime(0) + TIME_2HOURS);
                    }
                }
                break;
            }
            case ICMPV6_TARGET_LL_ADDRESS:
            case ICMPV6_REDIRECTED_HEADER:
            {
                break;
            }
            default:
            {
                /* Error: Unknown type received. We skip this option and carry on. */
                break;
            }
        }

        /* Get the next option */
        payload_len = payload_len - (ptr_icmpv6Opt->Length << 3);
        ptr_icmpv6Opt = (ICMPV6_OPT *) ((char*)ptr_icmpv6Opt + (ptr_icmpv6Opt->Length << 3));
    }

    /* Copy the (M)anaged Flag to the interface */
    if (ptr_icmpv6Hdr->Flags & ICMPV6_RA_M_FLAG)
        ptr_device->ptr_ipv6device->ManagedFlag = 1;
    else
        ptr_device->ptr_ipv6device->ManagedFlag = 0;

    /* Copy the (O)ther Config Flag to the interface */
    if ((ptr_icmpv6Hdr->Flags & ICMPV6_RA_O_FLAG) || (ptr_device->ptr_ipv6device->ManagedFlag == 1))
        ptr_device->ptr_ipv6device->OtherConfigFlag = 1;
    else
        ptr_device->ptr_ipv6device->OtherConfigFlag = 0;

    /* Extract and copy the current Hop Limit only if specified. */
    if (ptr_icmpv6Hdr->CurHopLimit != 0)
        ptr_device->ptr_ipv6device->CurHopLimit = ptr_icmpv6Hdr->CurHopLimit;

    /* Extract and copy the Retransmission Timer if specified (in Seconds)*/
    if (RetransTime != 0)
        ptr_device->ptr_ipv6device->RetransTimer = ntohl(RetransTime) / 1000;

    /* Extract and copy the Reachable Timer if specified (in Seconds) */
    if (ReachableTime != 0)
        ptr_device->ptr_ipv6device->ReachableTime = ntohl(ReachableTime) / 1000;

    /* Copy the MTU option only if specified. */
    if (mtu != 0)
        ptr_device->ptr_ipv6device->LinkMTU = mtu;

    /* Update the Default Router List.RFC 2461 Section 6.3.4 states that if the 
     * advertisment contains a Source Link Layer Address option the LINK Layer 
     * address should be recorded in the Neighbor Cache (create one if none
     * exists) Also set the IsRouter FLAG Always. */
    hRoute6 = Rt6FindDefaultRouter (srcAddr, ptr_device);
    if (hRoute6 == 0)
    {
        /* There was no ROUTER Entry present. Create one in the GATEWAY Table. 
         * Provided there exists a valid RouterLifetime. */
        if (ptr_icmpv6Hdr->RouterLifetime != 0)
        {
            /* Create a new default route. */
#ifdef ICMPV6_NDISC_DEBUG
            hRoute6 =
#endif
            Rt6Create (FLG_RTE_GATEWAY, IPV6_UNSPECIFIED_ADDRESS, 
                                 IPV6_UNSPECIFIED_ADDRESS, srcAddr, 
                                 ptr_src_ll_address, ptr_device, ntohs(ptr_icmpv6Hdr->RouterLifetime));                
#ifdef ICMPV6_NDISC_DEBUG
            DbgPrintf(DBG_INFO, "ICMPv6RecvRA: Received RA Creating Default Route 0x%x NextHop: \n", hRoute6);
            IPv6DisplayIPAddress (srcAddr);
#endif
        }
        else
        {
            /* The Router Lifetime was 0; ignore and dont create the entry. */
        }
    }
    else
    {
        /* There is a valid entry in the GATEWAY Table; we need it to be updated now. */
        if (ptr_icmpv6Hdr->RouterLifetime == 0)
        {
            /* Router lifetime is 0; implies that the GATEWAY should be deleted. */
            Rt6Free (hRoute6);
        }
        else
        {
            /* Update router with the new lifetime and also update the Neighbor Unreachability state. */
            Rt6Update (hRoute6, ICMPV6_ROUTER_ADVERTISMENT, ptr_src_ll_address, 0,
                       ntohs(ptr_icmpv6Hdr->RouterLifetime));
#ifdef ICMPV6_NDISC_DEBUG
            DbgPrintf(DBG_INFO, "ICMPv6RecvRA: DEBUG: Received RA Updating Default Route 0x%x NextHop: \n", hRoute6);
            IPv6DisplayIPAddress (srcAddr);
#endif
        }
    }

    /* Cleanup the packet and indicate SUCCESS since the packet has been processed successfully. */
    PBM_free (pPkt);
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function handles the ICMPv6 Redirect Message
 *
 *  @param[in]  pPkt
 *      Pointer to the entire ICMPv6 Packet.
 *
 *  @param[in]  ptr_ipv6hdr
 *      Pointer to the IPv6 Header.
 *
 *  @sa
 *      RFC-2461 Section 8
 *
 *  @retval
 *      0   -   Success
 *  @retval
 *      <0  -   Error
 */
int ICMPv6RecvRedirect (PBM_Pkt* pPkt, IPV6HDR* ptr_ipv6hdr)
{
    NETIF_DEVICE*           ptr_device;
    ICMPV6_REDIRECT_HDR*    ptr_icmpv6Hdr;
    ICMPV6_OPT*             ptr_icmpv6Opt;
    int                     payload_len;
    UINT8*                  ptr_target_ll_address = NULL;
    HANDLE                  hRoute6;
    IP6N                    srcAddr;
    IP6N                    dstAddr;
    IP6N                    targetAddress;
    IP6N                    destinationAddress;

    /* Get the interface on which the packet was received. */
    ptr_device = (NETIF_DEVICE *)pPkt->hIFRx;

    /* Get the pointer to the REDIRECT Message */
    ptr_icmpv6Hdr = (ICMPV6_REDIRECT_HDR *) (pPkt->pDataBuffer + pPkt->DataOffset);

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses out of ptr_ipv6hdr
     * as this data is potentially un-aligned (SDOCM00097361)
     */
    mmCopy((char *)&srcAddr, (char *)&ptr_ipv6hdr->SrcAddr, sizeof(IP6N));
    mmCopy((char *)&dstAddr, (char *)&ptr_ipv6hdr->DstAddr, sizeof(IP6N));
    mmCopy((char *)&targetAddress, (char *)&ptr_icmpv6Hdr->TargetAddress,
            sizeof(IP6N));
    mmCopy((char *)&destinationAddress,
            (char *)&ptr_icmpv6Hdr->DestinationAddress, sizeof(IP6N));

    /* Validate the packet: The hop limit in the packet should be 255. */
    if (ptr_ipv6hdr->HopLimit != 255)
        return -1;

    /* The length of the packet as derived from the IP header should be >= 40 bytes*/
    if (ntohs(ptr_ipv6hdr->PayloadLength) < 40)
        return -1;

    /* The ICMP Code for Redirect messages should be 0. */
    if (ptr_icmpv6Hdr->Code != 0)
        return -1;

    /* The IPv6 Source address in the packet should be a LINK Local Address. */
    if ((srcAddr.u.addr16[0] & IPV6_LINKLOCALMASK.u.addr16[0]) != htons (0xFE80))
        return -1;

    /* The Destination address in the Redirect message should not be a Multicast address */
    if (IPv6IsMulticast(destinationAddress))
        return -1;

    /* The Target address in the Redirect message should either be a Link Local Address or 
     * it should be the same as the Destination Address. */
    if ((targetAddress.u.addr16[0] & IPV6_LINKLOCALMASK.u.addr16[0]) != htons (0xFE80) && 
        (IPv6CompareAddress (targetAddress, destinationAddress) == 0))
        return -1;

    /* The IP Source address of the Redirect is the same as the current first hop router for the
     * Destination Address. */

    /* Process and validate any options which exist in the packet. 
     * We have already processed the ICMP NA Header; so now start after it. */
    payload_len   = ntohs (ptr_ipv6hdr->PayloadLength) - sizeof(ICMPV6_REDIRECT_HDR);
    ptr_icmpv6Opt = (ICMPV6_OPT *)(pPkt->pDataBuffer + pPkt->DataOffset + sizeof(ICMPV6_REDIRECT_HDR));

    /* Process and cycle through all the options. */
    while (payload_len > 0)
    {
        /* Ensure that the length value is non-zero */
        if (ptr_icmpv6Opt->Length == 0)
            return -1;

        /* Process the options. */
        switch (ptr_icmpv6Opt->Type)
        {
            case ICMPV6_TARGET_LL_ADDRESS:
            {
                /* Get the pointer target Link Layer Address */
                ptr_target_ll_address = (UINT8 *)((UINT8 *)ptr_icmpv6Opt + sizeof(ICMPV6_OPT));
                break;
            }
            case ICMPV6_REDIRECTED_HEADER:
            {
                break;
            }
            default:
            {
                DbgPrintf(DBG_INFO, "ICMPv6RecvRedirect: DEBUG: Received option %d in REDIRECT\n",
                        ptr_icmpv6Opt->Type);
                break;
            }
        }

        /* Get the next option */
        payload_len = payload_len - (ptr_icmpv6Opt->Length << 3);
        ptr_icmpv6Opt = (ICMPV6_OPT *) ((char*)ptr_icmpv6Opt + (ptr_icmpv6Opt->Length << 3));
    }

    /* We need to update the Neighbor Table at this stage. */
    hRoute6 = Rt6Find (FLG_RTE_HOST, targetAddress, ptr_device);
    if (hRoute6 == 0)
    {
        /* Host Routing Entry does not exist; check the GATEWAY Table too. */
        hRoute6 = Rt6FindDefaultRouter (targetAddress, ptr_device);
        if (hRoute6 == 0)
        {
            /* RFC 2461 Section 8.3 states that if a Neighbor entry does not exist; 
             * then we should create a new one. The entry does not exist in the HOST or GATEWAY tables. */
#ifdef ICMPV6_NDISC_DEBUG
            hRoute6 =
#endif
            Rt6Create (FLG_RTE_HOST, targetAddress, IPV6_HOST_MASK, 
                                 IPV6_UNSPECIFIED_ADDRESS, ptr_target_ll_address, ptr_device, 0);
#ifdef ICMPV6_NDISC_DEBUG
            DbgPrintf(DBG_INFO, "ICMPv6RecvRedirect: DEBUG: Received a VALID Redirect for Target Address Creating new RT6 Entry 0x%x\n", hRoute6);
#endif
        }
        else
        {
            /* The Entry exists in the GATEWAY Table; so update it accordingly. */
            Rt6Update (hRoute6, ICMPV6_REDIRECT, ptr_target_ll_address, 0, 0);
#ifdef ICMPV6_NDISC_DEBUG
            DbgPrintf(DBG_INFO, "ICMPv6RecvRedirect: DEBUG: Received a VALID Redirect for Target Address Updating GATEWAY Entry 0x%x\n", hRoute6);
#endif
        }
    }
    else
    {
        /* RFC 2461 Section 8.3 states that if a Neighbor entry exists; then it needs to be updated */
        Rt6Update (hRoute6, ICMPV6_REDIRECT, ptr_target_ll_address, 0, 0);
#ifdef ICMPV6_NDISC_DEBUG
        DbgPrintf(DBG_INFO, "ICMPv6RecvRedirect: DEBUG: Received a VALID Redirect for Target Address Updating RT6 Entry 0x%x\n", hRoute6);
#endif
    }

    /* Process the redirected option: Check if we have a ROUTE to the Destination Address. */
    hRoute6 = Rt6Find (FLG_RTE_HOST, destinationAddress, ptr_device);
    if (hRoute6 == 0)
    {
        /* No Route Exists; we need to create a new HOST Route with the following properties
         *  HOST Route: All Packets to DST. ADRESS SHOULD be sent through TARGET ADDRESS */
        Rt6Create (FLG_RTE_HOST, destinationAddress, IPV6_HOST_MASK,
                             targetAddress, ptr_target_ll_address, ptr_device, 0);
    }
    else
    {
        /* There already exists a ROUTE to the DST Address but we dont know if it goes
         * through the TARGET Address. */
        Rt6Modify (hRoute6, FLG_RTE_HOST, destinationAddress, IPV6_HOST_MASK,
                             targetAddress, ptr_target_ll_address, ptr_device, 0);
    }

    /* Packet has been successfully processed; cleanup the memory. */
    PBM_free (pPkt);
    return 0;    
}

/** 
 *  @b Description
 *  @n  
 *      The function handles the ICMPv6 Router Solicitation Message
 *
 *  @param[in]  pPkt
 *      Pointer to the entire ICMPv6 Packet.
 *
 *  @param[in]  ptr_ipv6hdr
 *      Pointer to the IPv6 Header.
 *
 *  @sa
 *      RFC-2461 Section 6.1
 *
 *  @retval
 *      0   -   Success
 *  @retval
 *      <0  -   Error
 */
int ICMPv6RecvRS (PBM_Pkt* pPkt, IPV6HDR* ptr_ipv6hdr)
{
    (void)ptr_ipv6hdr;

    /* If we are operating in Host Mode; then this packet should never be received and
     * should be dropped silently. */
    if (ipv6mcb.IsRouter == 0)
    {
        PBM_free (pPkt);
        return 0;
    }

    /* Currently the NDK IPv6 Stack supports only Host Mode; so this case is not handled. */
    DbgPrintf(DBG_INFO, "ICMPv6RecvRS: NDK IPv6 Stack operates only in HOST Mode\n");
    return -1;
}

/** 
 *  @b Description
 *  @n  
 *      The function is used to send out a Router solicitation. All RS
 *      messages are sent to the ALL_ROUTER Destination Address.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_device
 *      The Network Interface object on which the packet is to be transmitted.
 *
 *  @param[in]  SrcAddress 
 *      The Source address of the interface; this could be set to the UNSPECIFIED
 *      address. If the Source address is UNSPECIFIED; the function does not append
 *      the SOURCE_LL Option to the RS packet.
 *
 *  @retval
 *      0   -   Success
 *  @retval
 *      <0  -   Error
 */
int ICMPv6SendRS (NETIF_DEVICE* ptr_device, IP6N SrcAddress)
{
    ICMPV6_RS_HDR*  ptr_icmpv6Hdr;
    PBM_Pkt*        pPkt;
    UINT16          len;
    PSEUDOV6        pseudo_hdr;
    IPV6HDR*        ptr_ipv6hdr;
    ICMPV6_OPT*     ptr_icmpv6Opt;
    UINT8*          ptr_MacAddress = NULL;

    /* Increment the stats. */
    icmp6stats.OutMsgs++;

    /* Calculate the length of the NS packet which needs to be transmitted. */
    len = sizeof (ICMPV6_RS_HDR);

    /* Check if we need to add the Source Link Layer Address option or not? 
     * This is required only if the source address is specified */
    if (IPv6CompareAddress(SrcAddress, IPV6_UNSPECIFIED_ADDRESS) == 0)
    {
        /* The source address was specified. We will now be advertising our 
         * source link local address to the world. Thus we need to account for
         * this in the lenght of the packet. 
         *  Increment the length by 1 (Type) + 1 (Len) + 6 (MAC Address) */
        len = len + 8;
        ptr_MacAddress = &ptr_device->mac_address[0];
    }

    /* Allocate memory for the Neighbor Solicitation Packet. Ensure that the
     * allocation accounts for the IPv6 Header. */
    pPkt = NIMUCreatePacket (len + sizeof (IPV6HDR));
    if (pPkt == NULL)
    {
        /* Error: Unable to allocate packet memory. */
        DbgPrintf(DBG_INFO, "ICMPv6SendRS: OOM\n");
        NotifyLowResource();
        return -1;
    }

    /* Create the PSEUDO Header */
    pseudo_hdr.SrcAddr = SrcAddress;
    pseudo_hdr.DstAddr = IPV6_ALL_ROUTER_ADDRESS;
    pseudo_hdr.PktLen  = htons(len);
    pseudo_hdr.Rsvd[0] = 0;
    pseudo_hdr.Rsvd[1] = 0;
    pseudo_hdr.Rsvd[2] = 0;
    pseudo_hdr.NxtHdr  = IPPROTO_ICMPV6;

    /* Get the pointer to the ICMPv6 Header. */
    ptr_icmpv6Hdr = (ICMPV6_RS_HDR *)(pPkt->pDataBuffer + pPkt->DataOffset + sizeof(IPV6HDR));

    /* Initialize the ICMPv6 Header. */
    ptr_icmpv6Hdr->Type          = ICMPV6_ROUTER_SOLICITATION;
    ptr_icmpv6Hdr->Code          = 0;
    ptr_icmpv6Hdr->Reserved      = 0;

    /* Check if we need to any options; options are added after the NS header. */
    if (ptr_MacAddress != NULL)
    {    
        /* Get the pointer to the ICMPv6 option */
        ptr_icmpv6Opt = (ICMPV6_OPT *)(pPkt->pDataBuffer + pPkt->DataOffset + sizeof(IPV6HDR) + 
                                       sizeof(ICMPV6_RS_HDR));

        /* Populate the option buffer. */
        ptr_icmpv6Opt->Type   = ICMPV6_SOURCE_LL_ADDRESS;
        ptr_icmpv6Opt->Length = 1;

        /* Copy the MAC Address into the option data area */
        mmCopy (((UINT8 *)ptr_icmpv6Opt + sizeof(ICMPV6_OPT)), &ptr_device->mac_address[0], 6);
    }

    /* Compute the ICMPv6 Checksum. */
    ptr_icmpv6Hdr->Checksum = 0;
    ptr_icmpv6Hdr->Checksum = IPv6Layer4ComputeChecksum ((UINT8 *)ptr_icmpv6Hdr, &pseudo_hdr);

    /* Now get the pointer to the IPv6 Header and initialize its various fields. */
    ptr_ipv6hdr             = (IPV6HDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses into ptr_ipv6hdr
     * as ptr_ipv6hdr->{SrcAddr, DstAddr] are potentially un-aligned
     * (SDOCM00097361)
     */
    mmCopy((char *)&ptr_ipv6hdr->SrcAddr, (char *)&SrcAddress, sizeof(IP6N));
    mmCopy((char *)&ptr_ipv6hdr->DstAddr, (char *)&IPV6_ALL_ROUTER_ADDRESS, sizeof(IP6N));

    ptr_ipv6hdr->HopLimit   = 255;
    ptr_ipv6hdr->NextHeader = IPPROTO_ICMPV6;

    /* Set the valid len of the packet; which is the ICMP-NS Header. */
    pPkt->ValidLen = len;

    /* All Router Solicitation Packets are always sent to the ALL Router Group address
     * and thus we cant use ROUTING Tables here. So instead we select the tx interface 
     * here itself. */
    pPkt->hIFTx = (HANDLE)ptr_device;

    /* Pass the packet to the IPv6 Layer for transmission. */
    IPv6TxPacket (pPkt, 0);
    return 0;        
}

#endif /* _INCLUDE_IPv6_CODE */

