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
 * ======== lliout.c ========
 *
 * Link level resolution
 *
 */

#include <stkmain.h>
#include "lli.h"

static UINT8   bEtherBCast[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

/*********************************************************************
 * FUNCTION NAME : LLITxIpPacket
 *********************************************************************
 * DESCRIPTION   :
 *  The function is called to resolve the MAC address and transmit the
 *  packet out through the NIMU Interface.
 *
 * NOTES         :
 *  The function is based on the non NIMU version above but changes 
 *  were done to add the support to add custom L2 headers per network
 *  interface object. Since the changes were done across the function
 *  and instead of messing the above version a cleaner NIMU version was
 *  developed.
 *********************************************************************/
void LLITxIpPacket( PBM_Pkt *pPkt, IPN IPDst )
{
    UINT32          tmp;
    LLI*            plli;
    UINT8           bMACDst[6];
    HANDLE          hIF,hRt;
    NETIF_DEVICE*   ptr_net_device;

    /* We must have a packet. It must have an egress interface */
    /* It must be a layer 3 packet. It must have room for the */
    /* layer 2 header. */
    if( !pPkt || !(hIF = pPkt->hIFTx) || (pPkt->DataOffset < ETHHDR_SIZE) )
    {
        DbgPrintf(DBG_ERROR,"LLITxIpPacket: Bad Packet");
        PBM_free( pPkt );
        return;
    }

    /* Get the network interface object on which the packet will be transmitted. 
     * If the network interface does not support ARP then we can directly pass the 
     * packet to the device; bypassing everything */
    ptr_net_device = (NETIF_DEVICE *)hIF;
    if (ptr_net_device->flags & NIMU_DEVICE_NO_ARP)
    {
        DbgPrintf (DBG_ERROR,"LLITxIpPacket: Interface does not support ARP!");
        PBM_free (pPkt);
        return;
    }
    
    /* If the IP address is mappable, do it now */
    if( IPDst == INADDR_BROADCAST )
        mmCopy( bMACDst, bEtherBCast, 6 );
    else if( IN_MULTICAST(IPDst) )
    {
        /* Map the relevant IP bits */
        tmp = HNC32(IPDst);
        tmp = (tmp & 0x7fffff) | 0x5e000000;

        /* Form multicast MAC address */
        bMACDst[0] = 0x01;
        bMACDst[1] = 0x00;
        bMACDst[2] = (UINT8)(tmp >> 24);
        bMACDst[3] = (UINT8)(tmp >> 16);
        bMACDst[4] = (UINT8)(tmp >> 8);
        bMACDst[5] = (UINT8)(tmp);
    }
    else
    {
        /* We must find a destination MACAddr for the packet */

        /* The route MUST be valid */
        if( !(hRt = pPkt->hRoute) )
        {
            DbgPrintf(DBG_ERROR,"LLIResolve: No DstMAC/Route");
            PBM_free( pPkt );
            return;
        }

        /* Override the egress IF with that from the route */
        hIF = RtGetIF( hRt );

        /* Get the route flags */
        tmp = RtGetFlags( hRt );

        /* - The route can not be CLONING, GATEWAY or IFLOCAL */
        /* - The route MUST have an LLI */
        if( (tmp & (FLG_RTE_CLONING|FLG_RTE_GATEWAY|FLG_RTE_IFLOCAL)) ||
            !(plli = RtGetLLI( hRt )) )
        {
            DbgPrintf(DBG_ERROR,"LLIResolve: Invalid Route %04x",tmp);
            PBM_free( pPkt );
            return;
        }

        /* If the LLI does not have a valid MacAddr, then we need to */
        /* do some resolving, else assign the destination */
        if (plli->Status >= LLI_STATUS_VALID)
        {
            mmCopy( bMACDst, plli->MacAddr, 6 );

            /* Remember the last time the LLI entry was used. */
            plli->LastUsed = llTimerGetTime(0);
        }
        else
        {
            /*
             * Here we have an LLI without a valid MacAddr. The methodology
             * of obtaining a MacAddr on Ethernet is via ARP. Here we
             * attach the pending packet to the LLI entry for later.  Once we
             * receive a response to our ARP request and have a valid mapping,
             * the packet will be transmitted appropriately.
             *
             * Fix for SDOCM00088612
             * Use the forwarding flag since to gen ICMP error
             * Enqueue the packet.  Don't discard previous packet!
             */
            PBMQ_enq(&(plli->ArpPktQ), pPkt);

            /* Send an ARP if IDLE */
            if( plli->Status == LLI_STATUS_IDLE )
            {
                /* Signify we've initiated ARP */
                plli->Status = LLI_STATUS_ARP1;

                /* Insert into timeout list */
                _LLIExpListInsert( plli, llTimerGetTime(0) + 2 );

                /* Send the ARP */
                LLIGenArpPacket( RtGetIF(plli->hRt), RtGetIPAddr(plli->hRt) );
            }

            /* We're done for now */
            return;
        }
    }

    /* Add the Layer2 Header. */
    if (NIMUAddHeader ((NETIF_DEVICE *)hIF, (HANDLE) pPkt, bMACDst, NULL, 0x800) == 0)
    {
        /* Layer2 header was added successfully; the packet can now be sent out */

        /* Clear any held route */
        PBM_setRoute( pPkt, 0 );

        /* If required call the timestamp function */
        if (pPkt->pTimestampFxn != NULL) {
            (pPkt->pTimestampFxn)(pPkt->pIpHdr);
             pPkt->pTimestampFxn = NULL;
        }

        /* Send the packet through the NIMU Interface. */
        NIMUSendPacket (hIF, pPkt);
    }
    else
    {
        /* There was an error and the header could not be added. Clean the packet
         * memory */
        PBM_free (pPkt);
    }
}

/*********************************************************************
 * FUNCTION NAME : LLIGenArpPacket
 *********************************************************************
 * DESCRIPTION   :
 *  The function is called to send an ARP packet.
 *
 * NOTES         :
 *  The function is based on the non NIMU version above but changes 
 *  were done to add the support to add custom L2 headers per network
 *  interface object. Since the changes were done across the function
 *  and instead of messing the above version a cleaner NIMU version was
 *  developed.
 *********************************************************************/
void LLIGenArpPacket( HANDLE hIF, IPN IPDst )
{
    IPN             IPSrc;
    PBM_Pkt*        pPkt;
    ARPHDR*         pArpHdr;
    NETIF_DEVICE*   ptr_net_device;

    /* Get the parameters (Interface and DestIP) */
    IPSrc = BindIFNet2IPHost( hIF, IPDst );

    /* Allow for cross sub-net ARP requests */
    if( !IPSrc )
        IPSrc = BindIF2IPHost( hIF );

    /* Check for misconfiguration */
    if( !hIF || !IPDst || IPDst==0xFFFFFFFF || !IPSrc )
    {
        DbgPrintf(DBG_ERROR,"LLIGenArpPacket: Illegal ARP Attempt - Check Configuration");
        return;
    }

    /* Create the packet */
    if( !(pPkt = NIMUCreatePacket(ARPHDR_SIZE)) )
        return;

    /* Get the pointer to the interface on which the packet is to be transmitted. */
    ptr_net_device = (NETIF_DEVICE *)hIF;
    
    /* Get a pointer to the ARP header */
    pArpHdr = (ARPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Populate the ARP Packet. */
    pArpHdr->HardType       = HNC16(0x1);
    pArpHdr->ProtocolType   = HNC16(0x800);
    pArpHdr->Op             = HNC16(0x1);
    pArpHdr->HardSize       = 6;
    pArpHdr->ProtocolSize   = 4;
    WrNet32 (pArpHdr->IPSrc, IPSrc);
    WrNet32 (pArpHdr->IPDst, IPDst);
    mmZeroInit (pArpHdr->DstAddr, 6);
    mmCopy (pArpHdr->SrcAddr, ptr_net_device->mac_address, 6);

    /*
     * Update valid length to account for the size of this ARP header.
     * NIMUAddHeader should then further update it for ETHHDR_SIZE
     * (SDOCM00084826).
     */
    pPkt->ValidLen = ARPHDR_SIZE;

    if (NIMUAddHeader (ptr_net_device, (HANDLE) pPkt, bEtherBCast, NULL, 0x806) == 0)
    {
        /* Layer 2 header has been added successfully; now only can we send the 
         * packet through the NIMU Interface. */
        NIMUSendPacket (hIF, pPkt);
    }
    else
    {
        /* There was an error and the header could not be added. Clean the packet
         * memory */
        PBM_free (pPkt);
    }
}

