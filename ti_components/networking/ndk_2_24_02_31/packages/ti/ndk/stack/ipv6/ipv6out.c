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
 * ======== ipv6out.c ========
 *
 * The file handles the transmission of IPv6 Packets.
 * It also handles fragmentation of the packets, if
 * the packets being transmitted are larger than the
 * configured MTU on the transmit device.
 *
 */

#include <stkmain.h>
#include "ipv6.h"

#ifdef _INCLUDE_IPv6_CODE

/**********************************************************************
 ****************** IPV6 Packet Transmit Handling Functions ***********
 **********************************************************************/

 /** 
 *  @b Description
 *  @n  
 *      The function is used to get an IPv6 route matching the destination
 *      IP Address. The function increments the reference counter for the
 *      ROUTE6 object. 
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  DstIP     
 *      IPv6 Destination IP address we are trying to find a route for.
 *
 *  @retval
 *      Success - Handle of the Route6 object to be used.
 *  @retval
 *      Error   - 0
 */
HANDLE IPv6GetRoute (IP6N DstIP)
{
    HANDLE hRoute6;
    
    /* Get a ROUTE for the Destination address. */        
    hRoute6 = Rt6Find (FLG_RTE_HOST | FLG_RTE_CLONING | FLG_RTE_GATEWAY | FLG_RTF_CLONE, 
                       DstIP, NULL);

    /* Increment the reference counter if we found a route. */
    if (hRoute6 != 0)
        Rt6IncRefCount(hRoute6);

    /* Return the Route */
    return hRoute6;
}

/** 
 *  @b Description
 *  @n  
 *      The function is used to transmit an IPv6 packet.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  pPkt     
 *      Pointer to the IPv6 packet which needs to be transmitted
 *  @param[in]  Flags
 *      Flags which need to be worked out. (Placeholder)
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int IPv6TxPacket (PBM_Pkt *pPkt, UINT32 Flags)
{
    IPV6HDR*        ptr_ipv6hdr;
    IP6N            srcAddr;
    IP6N            dstAddr;
    NETIF_DEVICE*   ptr_net_device = NULL;
    HANDLE          hBind6Obj;
    HANDLE          ptr_lli6 = NULL;
    int             RetVal = -1;

    /* Get the pointer to the IPv6 Header. */
    ptr_ipv6hdr = (IPV6HDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses out of ptr_ipv6hdr
     * as this data is potentially un-aligned (SDOCM00097361)
     */
    mmCopy((char *)&srcAddr, (char *)&ptr_ipv6hdr->SrcAddr, sizeof(IP6N));
    mmCopy((char *)&dstAddr, (char *)&ptr_ipv6hdr->DstAddr, sizeof(IP6N));

    /* Increment Tx stats */
    ipv6mcb.ip6stats.OutRequests++;

    /* Check if the destination address is MULTICAST? */
    if (IPv6IsMulticast(dstAddr) == 1)
    {
        /* Yes. Packet was a multicast packet; try and get the tranmission interface 
         * using the source IP address. There is a special case here i.e. if the
         * source address is UNSPECIFIED; this is for DAD */
        if (IPv6CompareAddress(srcAddr, IPV6_UNSPECIFIED_ADDRESS) == 1)
        {
            /* This is a DAD packet being transmitted; in this case we already know the
             * interface on which the packet is to be transmitted. */ 
            ptr_net_device = (NETIF_DEVICE *)pPkt->hIFTx;
        }
        else
        {
            /* There was a valid UNICAST address in the packet; use this to get the 
             * corresponding BIND6 object. */
            hBind6Obj = Bind6FindByHost (NULL, srcAddr);
            if (hBind6Obj == 0)
            {
                /* Trying to send a packet with source address which does not match 
                 * any of our BIND6 objects. This is not acceptable. */
                PBM_free (pPkt);
        
                /* Increment Tx error stats */
                ipv6mcb.ip6stats.OutDiscards++;

                return -EADDRNOTAVAIL;
            }

            /* Once we have the BIND6 Object get the corresponding Interface handle. */
            ptr_net_device = Bind6GetInterfaceHandle (hBind6Obj);
        }
    }
    else
    {
        /* Packet is a Unicast Packet; Check if the packet has already been routed or not? */
        if (pPkt->hRoute6 == 0)
        {
            /* NO: The packet has not been routed; lets find a route now. */
            pPkt->hRoute6 = IPv6GetRoute (dstAddr);
            if (pPkt->hRoute6 == 0)
        	{
                /* Increment Tx error stats */
                ipv6mcb.ip6stats.OutNoRoutes++;

            	DbgPrintf(DBG_INFO, "No Route exists for \n");
            	IPv6DisplayIPAddress (dstAddr);
            	PBM_free (pPkt);
            	return -1;
        	}
        }

        /* Check if the Route is a Local Route. */
        if (Rt6IsLocalRoute (pPkt->hRoute6) == 1)
        {
            /* This is a local route; pass it back to the IPv6 Receive.  Patch up the length of 
             * the packet before and pass it back to the IPv6 stack. */
            pPkt->ValidLen = pPkt->ValidLen + sizeof(IPV6HDR);
            pPkt->hIFRx    = Rt6GetIF (pPkt->hRoute6);

            /* Increment Tx stats */
            ipv6mcb.ip6stats.OutTransmits++;

            IPv6RxPacket (pPkt);
            return 0;
        }

        /* Get the corresponding LLI6 Entry and from that the interface on which 
         * the packet is to be sent out. */
        ptr_lli6       = Rt6GetLLI(pPkt->hRoute6);
        ptr_net_device = LLI6GetNetDevice(ptr_lli6);
    }

    /* We now know the interface on which the packet is to be transmitted; make
     * sure that this interface is IPV6 compatible; we dont want to send out 
     * IPv6 packets on an interface which does not support V6. */
    if (ptr_net_device->ptr_ipv6device == NULL)
    {
        PBM_free (pPkt);

        /* Increment Tx error stats */
        ipv6mcb.ip6stats.OutDiscards++;

        return -1;
    }

    /* Check if we need to configure the various field in the packet? */
    if ((Flags & (FLG_IPTX_FORWARDING|FLG_IPTX_RAW)) == 0)
    {
        /* Set the Fields in the IPv6 Header. 
         * TODO: What all fields do we set? */
        ptr_ipv6hdr->VerTC         = 0x60;
        ptr_ipv6hdr->FlowLabel[0]  = 0;
        ptr_ipv6hdr->FlowLabel[1]  = 0;
        ptr_ipv6hdr->FlowLabel[2]  = 0;
        ptr_ipv6hdr->PayloadLength = htons (pPkt->ValidLen);
/*        ptr_ipv6hdr->HopLimit      = ptr_net_device->ptr_ipv6device->CurHopLimit; */
    }

    /* Set the Valid Length in the packet to now include the IPv6 header. */
    pPkt->ValidLen = pPkt->ValidLen + sizeof(IPV6HDR);

    /* Check if the packet fits the MTU configured for the
     * transmit device. If not, we will have to fragment it.
     */
    if( ptr_net_device->mtu < pPkt->ValidLen )
    {
        /* Call the function that handles fragmentation.
         * Let's just use the transmit device and LLI entry already
         * found here.
         */
        /* Increment Tx Frag stats */
        ipv6mcb.ip6stats.OutFragReqds++;

        RetVal =  IPv6TxFragPacket (pPkt, ptr_net_device, ptr_lli6);
        /* Error fragmenting the packet */
        if (RetVal != 0)
        {
            /* Increment Tx Frag error stats */
            ipv6mcb.ip6stats.OutFragFails++;
        }
        else
        {
            /* Increment Tx Frag stats */
            ipv6mcb.ip6stats.OutFragOKs++;
        }
        /* Free the original packet */
        PBM_free( pPkt );
        return RetVal;
    }

    /* Pass the packet down to the LLIv6 Layer for resolution and transmission. 
     * Get the network interface object on which the packet will be transmitted. 
     * Check if we need to support the ARP protocol or not? If not then we can 
     * bypass the ARP resolution. */
    if (ptr_net_device->flags & NIMU_DEVICE_NO_ARP)
    {
        /* Send the packet on the interface and return */
        NIMUSendPacket (ptr_net_device, pPkt);
    }
    else
    {
        /* Pass the packet for the resolution. */
        LLI6TxIPPacket (pPkt, ptr_lli6, ptr_net_device, dstAddr);
    }

    /* Increment Tx stats */
    if (IPv6IsMulticast(dstAddr) == 1)
    {
        ipv6mcb.ip6stats.OutMcastPkts++;
    }
    else
    {
        ipv6mcb.ip6stats.OutTransmits++;
    }

    /* Packet has been successfully transmitted. */
    return 0;
}

#endif /* _INCLUDE_IPv6_CODE */

