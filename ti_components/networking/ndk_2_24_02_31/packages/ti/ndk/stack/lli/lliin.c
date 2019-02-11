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
 * ======== lliin.c ========
 *
 * Link level resolution.
 *
 */

#include <stkmain.h>
#include "lli.h"

static LLI_ReportARP reportARPFxn = NULL;

/*-------------------------------------------------------------------- */
/* updateRtTable - if exists, update a route with an LLI entry as */
/*                 specified by the IF and IP/MAC address pair */
/* Returns a referenced route handle */
/*-------------------------------------------------------------------- */
static HANDLE updateRtTable(HANDLE hIF, IPN IPAddr, UINT8 *pMacAddr) 
{
    HANDLE  hRt;
    PBM_Pkt *pCurPkt = NULL;
    LLI     *plli;

    (void)hIF;

    /* Check if we already have it */
    if( (hRt = RtFind( FLG_RTF_HOST, IPAddr )) )
    {
        /* We have a match - update it */

        /* Get the LLI to update */
        plli = (LLI *)RtGetLLI( hRt );

        if( plli )
        {
            /* Update the MAcAddr */
            mmCopy( plli->MacAddr, pMacAddr, 6 );

            /* Update the LLI Status */
            plli->Status = LLI_STATUS_VALID;

            /* Remove the LLI from the timeout list */
            _LLIExpListRemove( plli );

            /* Record the new valid timeout */
            plli->Timeout = llTimerGetTime(0) +
                            (UINT32)LLI_KEEPALIVE_TIMEOUT;

            /* Mark the route as up if it is down */
            if( RtGetFailure( plli->hRt ) )
                RtSetFailure( plli->hRt, FLG_RTF_REPORT, 0 );

            /*
             * Fix for SDOCM00088612
             * dequeue any waiting packet and pass it back to LLITxIpPacket
             */
            while ((pCurPkt = PBMQ_deq(&(plli->ArpPktQ))) != NULL) {
                LLITxIpPacket( pCurPkt, IPAddr );
            }
        }
    }

    /* Return the referenced route */
    return( hRt );
}

/*-------------------------------------------------------------------- */
/* LLIValidateRoute - Create/correct a route with an LLI entry as */
/*                    specified by the IF and IP/MAC address pair */
/* Returns a referenced route handle */
/*-------------------------------------------------------------------- */
HANDLE LLIValidateRoute( HANDLE hIF, IPN IPAddr, UINT8 *pMacAddr )
{
    HANDLE  hRt;

    /* If an entry is found, update it */ 
    hRt = updateRtTable(hIF, IPAddr, pMacAddr);

    if (hRt == NULL) {
        /* We don't have a match - create one */

        /* Create the route */
        hRt = RtCreate( FLG_RTF_REPORT, FLG_RTE_HOST|FLG_RTE_KEEPALIVE,
                        IPAddr, 0xffffffff, hIF, 0, pMacAddr );
    }

        /* Set the route timeout */
    /* Bug fix: Update the route too when LLI is refreshed. */
        if( hRt )
            RtSetTimeout( hRt, (UINT32)LLI_KEEPALIVE_TIMEOUT );

    /* Return the referenced route */
    return( hRt );
}

/*********************************************************************
 * FUNCTION NAME : LLIRxPacket
 *********************************************************************
 * DESCRIPTION   :
 *  The function is called to receive an ARP packet. 
 *
 * NOTES         :
 *  The function is based on the non NIMU version above but changes 
 *  were done to add the support to add custom L2 headers per network
 *  interface object. Since the changes were done across the function
 *  and instead of messing the above version a cleaner NIMU version was
 *  developed.
 *********************************************************************/
void LLIRxPacket( PBM_Pkt *pPkt )
{
    HANDLE          hIF;
    HANDLE          hRt = 0;
    IPN             IPDst;
    IPN             IPSrc;
    UINT8           replymac[6];
    uint            w;
    LLI*            plli;
    ARPHDR*         pArpHdr;
    NETIF_DEVICE*   ptr_net_device;
#ifdef _INCLUDE_ACD_SUPPORT
    HANDLE          thisBind = NULL;
    IPN             thisIP;
    IPN             thisMask;
    IPN             thisNet;
#endif

    /* Get the interface the packet was received on */
    hIF = pPkt->hIFRx;

    /* Translate this into the network interface object. */
    ptr_net_device = (NETIF_DEVICE *)hIF;

    /* Provide access to ARP packets for protocols like ACD RFC5227 */
    if (reportARPFxn) {
        reportARPFxn(pPkt->pDataBuffer + pPkt->DataOffset - pPkt->L2HdrLen);
    }

    /* Get a pointer to the ARP header */
    pArpHdr = (ARPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Check to see if we Rx'd our own frame */
    if( *((UINT16 *)pArpHdr->SrcAddr) == *((UINT16 *)(ptr_net_device->mac_address)) &&
        *((UINT16 *)(pArpHdr->SrcAddr+2)) == *((UINT16 *)(ptr_net_device->mac_address+2)) &&
        *((UINT16 *)(pArpHdr->SrcAddr+4)) == *((UINT16 *)(ptr_net_device->mac_address+4)) )
        goto LLIRXEXIT;

    /* By Default: We will reply with our MAC address */
    mmCopy (replymac, ptr_net_device->mac_address, 6);

    /* Basic Validations: If the source MAC is a multicast or broadcast, then this is an
     * illegal ARP packet. We simply ignore it. */
    if( pArpHdr->SrcAddr[0] & 1 )
        goto LLIRXEXIT;

    /* Get the IP Source and Dest */
    IPSrc = RdNet32(pArpHdr->IPSrc);
    IPDst = RdNet32(pArpHdr->IPDst);

    /* Check if stack is configured to process Gratuitous ARP packets */
    if (RT_GARP) {
        /* 
         *  Check if it is a GARP packet 
         *  IPSrc == IPDst && DstMACAddr == 00:00:00:00:00:00
         *
         */
        if (IPSrc == IPDst && *((UINT16 *)pArpHdr->DstAddr) == 0 &&
            *((UINT16 *)(pArpHdr->DstAddr+2)) == 0 &&
            *((UINT16 *)(pArpHdr->DstAddr+4)) == 0) {
            if (RT_GARP == 1) {
                /* if exists, update routing table */
                hRt = updateRtTable(hIF, IPSrc, pArpHdr->SrcAddr); 
            }
            else {
                /* if exists update, if not add to routing table */
                hRt = LLIValidateRoute( hIF, IPSrc, pArpHdr->SrcAddr);
            }

            /* Do not reply to GARP, no need to process further */
            goto LLIRXEXIT;
        }
    }

    /* If the sender thinks they are us, we have a problem */
    if( BindFindByHost( hIF, IPSrc ) )
    {
        /* Notify Route Control of the problem */
        RTCReport( MSG_RTC_DUPIP, IPSrc, (UINT32)(pArpHdr->SrcAddr) );

        /* We always reply to this condition */
        IPDst = IPSrc;
    }
    /* else If this packet is for the local IF, we record the source */
#ifdef _INCLUDE_ACD_SUPPORT
    else if( (thisBind = BindFindByHost( hIF, IPDst )) )
#else
    else if( BindFindByHost( hIF, IPDst ) )
#endif
    {
        /* Update the host route with the supplied MAC, or create */
        /* a new host route given the supplied MAC. */

        /* NOTE: The DHCP RFC recommends sending gratuitous ARP */
        /*       requests with a source IP of 0.0.0.0, so if */
        /*       IPSrc is NULL, don't validate it */

#ifdef _INCLUDE_ACD_SUPPORT
        /* get the IP info from the local binding */
        BindGetIP(thisBind, &thisIP, &thisNet, &thisMask);
#endif
        if( IPSrc ) {
#ifdef _INCLUDE_ACD_SUPPORT
            /*
             * Use our subnet mask to check whether the IP address of sender
             * is in our local subnet or not.  If the sender's IP AND'ed with
             * our subnet mask results in the same network address as ours,
             * then the sender is in the same subnet:
             */
            if (thisNet == (IPSrc & thisMask)) {
#endif
                hRt = LLIValidateRoute( hIF, IPSrc, pArpHdr->SrcAddr );
#ifdef _INCLUDE_ACD_SUPPORT
            }
#endif
        }

        /* replymac is the REPLY MacAddr (Already set to hIF's address) */
    }
    /* else Check for Proxy Arp Reply */
    else
    {
        /* We check PROXY first. If PROXY is set to respond, then we */
        /* know we have different IF's, thus PROXYPUB is not possible. */
        /* Otherwise, we'll check for a PROXYPUB. */
        if( !(hRt = RtFind( FLG_RTF_PROXY, IPDst )) )
            goto CheckProxyPub;
        else
        {
            w = RtGetFlags( hRt );

            /* If this is a Standard Proxy, */
            /* replymac is the REPLY MAC (Already set to hIF's Directed MAC) */
            if( (w & FLG_RTE_PROXY) && (hIF != RtGetIF( hRt )) )
                goto RequestValid;
        }
CheckProxyPub:
        /* Check for a ProxyPub address */
        if( !(hRt = RtFind( FLG_RTF_PROXYPUB, IPDst )) )
            goto LLIRXEXIT;
        else
        {
            w = RtGetFlags( hRt );

            if( !(w & FLG_RTE_PROXYPUB) || hIF != RtGetIF( hRt ) )
                /* Not a proxy, or not on Proxy IF */
                goto LLIRXEXIT;
            else
            {
                /* ProxyPub - Publish another adapter's MAC on its behalf */
                plli = (LLI *)RtGetLLI( hRt );

                /* Setup replymac to be the REPLY MAC */
                mmCopy( replymac, plli->MacAddr, 6 );
            }
        }
    }

RequestValid:
    /* If we get here, we may need to reply. */
    if( pArpHdr->Op == HNC16(0x01) )
    {
        /* We need to send the ARP Reply. With NIMU we will use the Network Interface
         * Objects add_header API to add the correct ethernet header. This will ensure
         * that even if the lower order interface is VLAN then the correct header is 
         * added. */ 

        /* Configure the ARP header. */ 
        pArpHdr->HardType       = HNC16(0x1);
        pArpHdr->ProtocolType   = HNC16(0x800);
        pArpHdr->Op             = HNC16(0x2);
        pArpHdr->HardSize       = 6;
        pArpHdr->ProtocolSize   = 4;

        /* Source address is the new destination address */
        mmCopy (pArpHdr->DstAddr, pArpHdr->SrcAddr, 6 );

        /* The source address is the MAC address of the network interface object. */
        mmCopy (pArpHdr->SrcAddr, replymac, 6 );

        /* IPDst   = New SrcIP */
        WrNet32 (pArpHdr->IPSrc, IPDst );

        /* IPSrc   = New DstIP */
        WrNet32 (pArpHdr->IPDst, IPSrc );

        /* We are transmitting an ARP packet; so configure the length correctly. */ 
        pPkt->ValidLen = ARPHDR_SIZE;

        /* Add the Layer2 header. */
        if (NIMUAddHeader (ptr_net_device, (HANDLE) pPkt, pArpHdr->DstAddr, replymac, 0x806) == 0)
        {
            /* Layer2 header has been added successfully; now we can send the packet */
            NIMUSendPacket (hIF, pPkt);
        }
        else
        {
            /* Error was detected; clean the packet memory. */
            PBM_free (pPkt);
        }
        
        /* We don't free the packet */
        pPkt = 0;        
    }

LLIRXEXIT:
    /* hRt Must be DeRef'd */
    if( hRt )
        RtDeRef( hRt );
    /* hPkt Must be Free'd */
    if( pPkt )
        PBM_free( pPkt );
}

void LLI_setARPHook(LLI_ReportARP fxn)
{
    reportARPFxn = fxn;
}
