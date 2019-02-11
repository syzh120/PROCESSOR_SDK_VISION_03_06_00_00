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
 * ======== ipout.c ========
 *
 * Routines related to IP Transmit
 *
 */

#include <stkmain.h>
#include "ip.h"

/*-------------------------------------------------------------------- */
/* IPTxPacket() */
/* Handles requests to send IP packets */
/*-------------------------------------------------------------------- */
int IPTxPacket( PBM_Pkt *pPkt, uint Flags )
{
    HANDLE   hIFTx,hIFRx,hRt=0;
    uint     w,Valid;
    IPHDR    *pIpHdr;
    IPN      IPDst,IPSrc;

/*///// Simulate Trouble //////// */
/* static int foo = 0; */
/* if( !(foo++ % 13) ){ PktFree(hPkt); return(IPTX_SUCCESS); } */
/*/////////////////////////////// */

    if( !_IPExecuting )
    {
        PBM_free( pPkt );
        return(IPTX_SUCCESS);
    }

    /* Get the IP header pointer */
    pIpHdr = (IPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);
    
    /* Save the pIpHdr in case of timestamping  */
    pPkt->pIpHdr = (UINT8*) pIpHdr;

    /* Get the the receiving interface (we use it a lot) */
    hIFRx = pPkt->hIFRx;

    /* Get valid bytes (we use it a lot) */
    Valid = pPkt->ValidLen;


    /* 
     * Patch up header if not forwarding or in raw mode.
     *
     * This code WILL patch:
     *     TotalLength, Frag/Offset, and Id
     *    
     * This code WILL NOT patch:
     *     Ttl, Protocol, IpSrc, IpDst
     */
    if( !(Flags & (FLG_IPTX_FORWARDING|FLG_IPTX_RAW)) )
    {
        /* Set Total Length */
        pIpHdr->TotalLen = HNC16( Valid );

        /* Set IP Identification */
        pIpHdr->Id = HNC16(IP_INDEX);
        IP_INDEX++;

        /* Set Don't Frag (when specified) */
        if( Flags & FLG_IPTX_DONTFRAG )
            pIpHdr->FlagOff = HNC16( IP_DF );
        else
            pIpHdr->FlagOff = 0;
    }
    else if( Flags & FLG_IPTX_RAW )
    {
        /* We'll follow BSD's lead on this one */
        if( !pIpHdr->Id )
        {
            pIpHdr->Id = HNC16(IP_INDEX);
            IP_INDEX++;
        }
    }

    /* Perform Checksum */
    IPChecksum( pIpHdr );

    /* Set Ethertype */
    pPkt->EtherType = 0x800;

    /* Now find a route and send! */

    /* Get IP Source and Destination */
    IPSrc = RdNet32( &pIpHdr->IPSrc );
    IPDst = RdNet32( &pIpHdr->IPDst );

    /*
     * Our final goal is to have the following:
     *
     * Valid EtherType in Packet Object
     * Valid IFTx in Pkt
     * Handle to a route or mapable IP Dst
     *
     * If any of these are not valid now, we can't hand the packet
     * off the the device.
     */

    /* Check for directed IP - override to standard BCAST */
    if( IP_DIRECTED_BCAST && (hIFTx = BindGetIFByDBCast(IPDst)) )
        IPDst = INADDR_BROADCAST;
    else
        hIFTx = pPkt->hIFTx;

    /* Check for old style BCAST - override to standard BCAST */
    if( IPDst == INADDR_ANY )
        IPDst = INADDR_BROADCAST;

    /* If we have a multicast or broadcast IP addr, we mark it as valid */
    /* and distribute it directly to the egress device(s). */

    /* IP BROADCAST/MULTICAST */
    if( IPDst == INADDR_BROADCAST || IN_MULTICAST(IPDst) )
    {
        /* If this socket can not broadcast, then this is an error */
        if( IPDst == INADDR_BROADCAST && !(Flags & FLG_IPTX_BROADCAST) )
        {
            PBM_free( pPkt );
            return( IPTX_ERROR_EACCES );
        }

        /* We need an egress interface */
        if( !hIFTx )
        {
            hIFTx = BindIPHost2IF( IPSrc );
            if( !hIFTx )
            {
                PBM_free( pPkt );
                return( IPTX_ERROR_ADDRNOTAVAIL );
            }
        }

        /* Set the egress IF */
        pPkt->hIFTx = hIFTx;

        /* We don't need a route */
        PBM_setRoute( pPkt, 0 );

        goto IpRouteDone;
    }

    /* We never transmit a loopback address */
    if( IN_LOOPBACK(IPDst) )
        goto local_packet;

    /* Get preliminary route info */
    hRt   = pPkt->hRoute;

    /* If the DONTROUTE flag is set, we route to HOST routes only. */
    /* The search will discard intermediate GATEWAYS. This allows a */
    /* packet to find a local host in the event that a redirect */
    /* has been mistakenly entered into the route table. */
    if( Flags & FLG_IPTX_DONTROUTE )
    {
        hRt = 0;
        w = FLG_RTF_CLONE|FLG_RTF_REPORT|FLG_RTF_HOST;
    }
    else
        w = FLG_RTF_CLONE|FLG_RTF_REPORT;

    /* We need a route to get hIFTx */
    /* If we don't have a route, we must find one */
    if( !hRt )
    {
        /* Now find the next hop for this packet. Search for a route */
        /* WITH cloning. */
        if( !(hRt = IPGetRoute(w, IPDst)) )
        {
            if( !(Flags & FLG_IPTX_FORWARDING) )
                ips.Localnoroute++;
            else
            {
                ips.Cantforward++;
                ICMPGenPacket(pIpHdr,hIFRx,ICMP_UNREACH,ICMP_UNREACH_NET,0);
            }
            PBM_free( pPkt );
            return( IPTX_ERROR_UNREACH );
        }

        /* Set the route in the packet */
        PBM_setRoute( pPkt, hRt );

        /* Now we can deref the local copy */
        RtDeRef( hRt );
    }

    /* Here we have a route we think we can use */
    w = RtGetFlags( hRt );

    /* If the route is down, we're still unreachable */
    if( !(w & FLG_RTE_UP) )
    {
        if( !(Flags & FLG_IPTX_FORWARDING) )
            ips.Localnoroute++;
        else
        {
            ips.Cantforward++;
            ICMPGenPacket(pIpHdr,hIFRx,ICMP_UNREACH,ICMP_UNREACH_HOST,0);
        }
        PBM_free( pPkt );
        return( IPTX_ERROR_HOSTDOWN );
    }

    /* If the route is rejecting, we're still unreachable */
    if( w & FLG_RTE_REJECT )
    {
        if( !(Flags & FLG_IPTX_FORWARDING) )
            ips.Localnoroute++;
        else
        {
            ips.Cantforward++;
            ICMPGenPacket(pIpHdr,hIFRx,ICMP_UNREACH,ICMP_UNREACH_HOST,0);
        }
        PBM_free( pPkt );
        return( IPTX_ERROR_REJECTED );
    }

    /* If the route is a black hole, stop here */
    if( w & FLG_RTE_BLACKHOLE )
    {
        PBM_free( pPkt );
        return( IPTX_SUCCESS );
    }

    /* If the route is local, give the packet to the input function */
    if( w & FLG_RTE_IFLOCAL )
    {
local_packet:
        /* Note: If hIFRx is not null, we have an error */
        if( hIFRx )
        {
            /* Setting the IF to NULL tell Rx that this is a LOCAL IF */
            pPkt->hIFRx = 0;
            /* Still, better warn the operator */
            DbgPrintf(DBG_WARN,"IPTxPacket: Route loop");
        }

        /* No sense keeping the route around */
        PBM_setRoute( pPkt, 0 );

        /* Give the packet to Rx */
        IPRxPacket( pPkt );
        return( IPTX_SUCCESS );
    }

    /* Make sure the egress interface is set */
    hIFTx = RtGetIF( hRt );
    pPkt->hIFTx = hIFTx;

IpRouteDone:
    if( !(Flags & FLG_IPTX_FORWARDING) )
        ips.Localout++;
    else
    {
        /* Bump Forwarding Stats and Check for redirects */
        ips.Forward++;

        if( hIFTx == hIFRx && hRt )
        {
            IPN IPTAddr, IPTMask;

            IPTAddr = RtGetIPAddr( hRt );
            IPTMask = RtGetIPMask( hRt );

            /* A redirect is NOT sent in the following cases: */
            /*   - The packet was source routed */
            /*   - The Route was created or modifed by ICMP (DYNAMIC|MODIFIED) */
            /*   - The Route is the default route (IPMask != 0) */
            /*   - The sender is not a part of the next-hop subnet */

            if( !(Flags&FLG_IPTX_SRCROUTE) &&
                !(w&(FLG_RTE_DYNAMIC|FLG_RTE_MODIFIED)) &&
                IPTMask!=0 && ((IPSrc&IPTMask)==IPTAddr) )
            {
                /* We passed all the tests - we should generate an */
                /* ICMP redirect. */
                ips.Redirectsent++;
                ICMPGenPacket( pIpHdr, hIFRx, ICMP_REDIRECT,
                               ICMP_REDIRECT_HOST, IPTAddr );
            }
        }
    }

    /* Make sure the packet can fit out the egress device */
    w     = IFGetMTU( hIFTx );
    Valid = HNC16(pIpHdr->TotalLen);
    if( w < Valid )
    {
        /* Fragmentation required */
        UINT16 off,hlen,size,offbase,offtmp;
        PBM_Pkt *pPkt2;
        IPHDR   *pIpHdr2;

        /*
         * Get the 4 bit header length value from the VerLen field in the IP
         * header (VerLen stores both the IP version and the header length).
         * Units of header length are in 32-bit words (so multiply by 4)
         */
        hlen = (pIpHdr->VerLen & 0xF) * 4;

        /* If the DF flag is set, we're done */
        if( pIpHdr->FlagOff & HNC16(IP_DF) )
            goto IpRouteCantFrag;

        /* Record the offset base (we may be fragmenting a packet fragment */
        /* from a previous hop) */
        offbase = HNC16(pIpHdr->FlagOff);

        /* Get the payload bytes per frag amount */
        w = (w - hlen) & ~7;
        if( w )
        {
            /* Send out a bunch of fragmented packets */
            for( off=0; off<(UINT16)Valid-hlen; off+=w )
            {
                /* Get the payload size for this fragment */
                size = w;
                if( (off+size) > ((UINT16)Valid-hlen) )
                    size = (UINT16)Valid - hlen - off;

                /* Create the packet */
                if( !(pPkt2 = NIMUCreatePacket( size+hlen )) )
                    goto IpRouteCantFrag;                

                /* Get the IP header pointer */
                pIpHdr2 = (IPHDR *)(pPkt2->pDataBuffer + pPkt2->DataOffset);

                /* Fixup packet frag info */
                pPkt2->ValidLen = size+hlen;

                /* Copy the IP header and data */
                mmCopy( pIpHdr2, pIpHdr, hlen );
                mmCopy( ((UINT8 *)pIpHdr2)+hlen,
                        ((UINT8 *)pIpHdr)+hlen+off, size );

                /* Add this fragment offset to the base offset */
                offtmp = offbase + (off>>3);

                /* Set the MF bit as required (may already be set in offbase) */
                if( (off+size) < ((UINT16)Valid-hlen) )
                    offtmp |= IP_MF;

                /* Set the offset */
                pIpHdr2->FlagOff = HNC16(offtmp);

                /* Set the total length */
                pIpHdr2->TotalLen = HNC16( (size+hlen) );

                /* Perform Checksum */
                IPChecksum( pIpHdr2 );

                /* Set Ethertype */
                pPkt2->EtherType = 0x800;

                /* Set Destination Info */
                pPkt2->hIFTx = hIFTx;
                PBM_setRoute( pPkt2, pPkt->hRoute );

                ips.Ofragments++;
                /*
                 *  Send the packet
                 *
                 *  Get the network interface object on which the packet will
                 *  be transmitted.  Check if we need to support the ARP
                 *  protocol or not? If not then we can bypass the ARP
                 *  resolution.
                 */
                {
                    NETIF_DEVICE* ptr_net_device = (NETIF_DEVICE *)hIFTx;
                    if (ptr_net_device->flags & NIMU_DEVICE_NO_ARP)
                    {
                        /* Send the packet on the interface and return */
                        NIMUSendPacket (hIFTx, pPkt2);
                    }
                    else
                    {
                        /* Pass the packet for the resolution. */
                        LLITxIpPacket (pPkt2, IPDst);
                    }
                }
            }

            ips.Fragmented++;
            PBM_free( pPkt );
            return( IPTX_SUCCESS );
        }

IpRouteCantFrag:
        ips.Cantfrag++;
        ICMPGenPacket(pIpHdr,hIFRx,ICMP_UNREACH,ICMP_UNREACH_NEEDFRAG,0);
        PBM_free( pPkt );
        return( IPTX_ERROR_MSGSIZE );
    }
    /*
     *  Send the packet
     *
     *  Get the network interface object on which the packet will
     *  be transmitted.  Check if we need to support the ARP
     *  protocol or not? If not then we can bypass the ARP
     *  resolution.
     */
    {
        NETIF_DEVICE* ptr_net_device = (NETIF_DEVICE *)hIFTx;
        if (ptr_net_device->flags & NIMU_DEVICE_NO_ARP)
        {
            /* Send the packet on the interface and return */
            NIMUSendPacket (hIFTx, pPkt);
        }
        else
        {
            /* Pass the packet for the resolution. */
            LLITxIpPacket (pPkt, IPDst);
        }
    }

    return( IPTX_SUCCESS );
}

