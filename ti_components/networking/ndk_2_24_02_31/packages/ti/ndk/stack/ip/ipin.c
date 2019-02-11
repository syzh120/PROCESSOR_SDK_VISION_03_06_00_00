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
 * ======== ipin.c ========
 *
 * Routines related to IP Receive
 *
 */

#include <stkmain.h>
#include "ip.h"

static IPN _IPFltAddr = 0;
static IPN _IPFltMask = 0;

/*-------------------------------------------------------------------- */
/* IPFilterSet() - Set IP Filtered Net */
/* The stack has the ability to protect one network (which can be */
/* a combination of multiple networks). The IP address and mask is */
/* set by this function. The feature is enabled via a configuration */
/* entry. */
/*-------------------------------------------------------------------- */
void IPFilterSet( IPN IPAddr, IPN IPMask )
{
    _IPFltAddr = IPAddr & IPMask;
    _IPFltMask = IPMask;
}

/*-------------------------------------------------------------------- */
/* IPRouteIP() - Find Route's Outgoing IP */
/* Return the IP address of the outgoing IF for a packet routed */
/* to the IP address supplied in IPDst. The Source IP is provided */
/* in the event that the Dest IP does not contain any relevant */
/* information (e.g.: broadcast or multicast). */
/*-------------------------------------------------------------------- */
static IPN IPRouteIP( HANDLE hIF, IPN IPDst, IPN IPSrc, uint Opt )
{
    HANDLE hRt;
    IPN    IPOut;

    /* This function will potentially have to examine routes, but */
    /* we'll try the easy cases first. */

    /* First look at the wildcard addresses */
    /* We take the following wildcards: */
    /*     - The Dst is an all 0's BCast */
    /*     - The Dst is an all 1's BCast */
    /*     - The Dst is a Multicast Addr */
    if( IPDst==INADDR_ANY || IPDst==INADDR_BROADCAST || IN_MULTICAST(IPDst) )
    {
        /* The packet is ours, but we don't have a sub-net to lookup */
        /* our IF's IP address. First, we'll try and find one based */
        /* in the IPNet of the source */
        if( !(IPOut = BindIFNet2IPHost( hIF, IPSrc )) )
        {
            /* Oops, now we're not sure of the true dest - we'll */
            /* simply return anything we find on hIF */
            IPOut = BindIF2IPHost( hIF );
        }
        return( IPOut );
    }

    /* See if this packet is addressed directly to a bound subnet */
    if( (IPOut = BindIFNet2IPHost( 0, IPDst )) != 0 )
        return( IPOut );

    /* If we get here, we can't be IPOPT_SSRR */
    if( Opt == IPOPT_SSRR )
        return(0);

    /* Now find the next hop for this packet. Search for a route */
    /* WITHOUT cloning. All we need from the route is the outgoing */
    /* IF / IP. */
    if( !(hRt = IPGetRoute(0, IPDst)) )
        return(0);

    /* We have a viable route for the packet. Now, get the IP host */
    /* address of the outgoing IF on the IP subnet of the next hop. */

    /* We can look up the IP of the outgoing IF directly. */
    IPOut = BindIFNet2IPHost( RtGetIF(hRt), RtGetIPAddr(hRt) );
    RtDeRef( hRt );

    /* Note: Sometimes IPOut will be NULL! */
    /* IPOut == NULL is an odd case. What happens is */
    /* that we have a route for a host for which we don't */
    /* have a network! This can only be caused by an illegal */
    /* host, or by a misconfiguration. Since we have no */
    /* outgoing IP for this IF/Host, we're forced to */
    /* return NULL. */
    return( IPOut );
}

/*-------------------------------------------------------------------- */
/* IPRxPacket() */
/* Processes message containing a newly received IP packet */
/*-------------------------------------------------------------------- */
void IPRxPacket( PBM_Pkt *pPkt )
{
    HANDLE   hIFRx;
    uint     w,IPHdrLen,SrcRoute;
    IPHDR    *pIpHdr;
    IPN      IPDst,IPSrc,IPTmp;
#ifdef _INCLUDE_NAT_CODE
    int      NatRC;
#endif

/*///// Simulate Trouble //////// */
/* static int foo = 0; */
/* if( !(foo++ % 13) ){ PktFree(hPkt); return; } */
/*/////////////////////////////// */

    /* If not executing, then no frame gets through */
    if( !_IPExecuting )
    {
        PBM_free( pPkt );
        return;
    }

    /* Get the IP header pointer */
    pIpHdr = (IPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Get the the receiving interface (we use it a lot) */
    hIFRx = pPkt->hIFRx;

    /* Bump Rx Count */
    ips.Total++;

    /* We only handle IP version 4 */
    if( (pIpHdr->VerLen & 0xf0) != 0x40 )
    {
        ips.Badvers++;
        PBM_free( pPkt );
        return;
    }

    /* Make sure size is in range and not bigger than the packet length */
    if( (IPHdrLen = ((pIpHdr->VerLen & 0xf)*4) ) < IPHDR_SIZE ||
                     IPHdrLen > pPkt->ValidLen )
    {
        ips.Badhlen++;
        PBM_free( pPkt );
        return;
    }

    /* Save IP hdr length */
    pPkt->IpHdrLen = IPHdrLen;

    /* Make sure total length is reasonable, and not bigger than the */
    /* packet length */
    w = (uint)pIpHdr->TotalLen;
    if( HNC16(w) > pPkt->ValidLen )
    {
        ips.Badlen++;
        PBM_free( pPkt );
        return;
    }

    /* Verify the IP header checksum */
    w = (uint)pIpHdr->Checksum;
    if( w == 0xFFFF )
        w = 0;
    IPChecksum( pIpHdr );
    if( w != (uint)pIpHdr->Checksum )
    {
        ips.Badsum++;
        PBM_free( pPkt );
        return;
    }

    /* Record the Destination and Source IP */
    IPDst = RdNet32( &pIpHdr->IPDst );
    IPSrc = RdNet32( &pIpHdr->IPSrc );

    /* Initially assume no source routing */
    SrcRoute = 0;

    /* Process any IP Options */
    if( IPHdrLen > IPHDR_SIZE )
    {
        uint    OptIdx,OptBytes,OptSize;
        UINT8   Opt;

        /* Byte count of options */
        OptBytes = IPHdrLen - IPHDR_SIZE;

        /* Process option bytes */
        for( OptIdx = 0; OptIdx < OptBytes; OptIdx += OptSize )
        {
            Opt = pIpHdr->Options[OptIdx];

            /* Validate Option and Get Size */
            if( Opt == IPOPT_EOL )
                break;
            else if( Opt == IPOPT_NOP )
                OptSize = 1;
            else
            {
                OptSize = pIpHdr->Options[OptIdx+1];
                if( OptSize <= 0 || OptSize > OptBytes )
                {
                    /* This is an ICMP error */
                    /* Give the whole works to ICMP */
                    ips.Badoptions++;
                    w = IPHDR_SIZE + OptIdx + 1;
                    ICMPGenPacket( pIpHdr, hIFRx, ICMP_PARAMPROB, w, 0 );
                    PBM_free( pPkt );
                    return;
                }
            }

            /* Check for legal option offset on RECORD ROUTE variants */
            if( Opt == IPOPT_RR || Opt == IPOPT_SSRR || Opt == IPOPT_LSRR )
            {
                /* Get the offset */
                w = pIpHdr->Options[OptIdx+2];

                /* Offset less than 4 is illegal */
                if( w<4 )
                {
                    /* This is an ICMP error */
                    /* Give the whole works to ICMP */
                    ips.Badoptions++;
                    w = IPHDR_SIZE+OptIdx+2;
                    ICMPGenPacket( pIpHdr, hIFRx, ICMP_PARAMPROB, w, 0 );
                    PBM_free( pPkt );
                    return;
                }

                /* Make offset Zero based (is normally 1 based) */
                w--;
            }

            /* Process Option */
            switch( Opt )
            {
            /* OPTION: NOP */
            case IPOPT_NOP:
            default:
                break;

            /* OPTION: Record Route */
            case IPOPT_RR:
                /* Ignore if there's no more room */
                if( (w+4) >= OptSize )
                    break;

                /* Get the IP of the outgoing IF (or local host) */
                if( !(IPTmp = IPRouteIP( hIFRx, IPDst, IPSrc, Opt )) )
                {
                    /* If no address found, we have an error */
                    /* Give the whole works to ICMP */
                    ips.Cantforward++;
                    if( IP_FORWARDING )
                        ICMPGenPacket( pIpHdr, hIFRx, ICMP_UNREACH,
                                       ICMP_UNREACH_HOST, 0 );
                    PBM_free( pPkt );
                    return;
                }

                /* Save IP addr in the header */
                mmCopy( pIpHdr->Options+OptIdx+w, (UINT8 *)&IPTmp, 4 );

                /* Bump the offset */
                pIpHdr->Options[OptIdx+2] += sizeof(IPN);

                break;

            /* OPTION: Source Route */
            case IPOPT_LSRR:
            case IPOPT_SSRR:
                /* If the packet isn't addressed to us, there's not much */
                /* to do. */
                if( !BindFindByHost( 0, IPDst) )
                {
                    /* If using SSRR or not routing, this is an error */
                    if( Opt == IPOPT_SSRR || !IP_FORWARDING )
                    {
                        ips.Cantforward++;
                        ICMPGenPacket( pIpHdr, hIFRx, ICMP_UNREACH,
                                            ICMP_UNREACH_SRCFAIL, 0 );
                        PBM_free( pPkt );
                        return;
                    }
                    /* Here we're using LSRR, but we can't do anything */
                    break;
                }

                /* Here we know the packet is for us. If we're at the */
                /* end of the source route, we're done */

                if( w >= OptSize )
                    break;

                /* Get the IP addr of the next hop */
                mmCopy( (UINT8 *)&IPDst, pIpHdr->Options+OptIdx+w, 4 );

                /* If we don't forward, or we can't get the next hop, */
                /* this is an error */
                if( !IP_FORWARDING ||
                    !(IPTmp = IPRouteIP( hIFRx, IPDst, IPSrc, Opt )) )
                {
                    ips.Cantforward++;
                    ICMPGenPacket( pIpHdr, hIFRx, ICMP_UNREACH,
                                               ICMP_UNREACH_SRCFAIL, 0 );
                    PBM_free( pPkt );
                    return;
                }

                /* Save outgoing IP addr in the header */
                mmCopy( pIpHdr->Options+OptIdx+w, (UINT8 *)&IPTmp, 4 );

                /* Patch the next hop destination */
                WrNet32( &pIpHdr->IPDst, IPDst );

                /* Bump the offset */
                pIpHdr->Options[OptIdx+2] += sizeof(IPN);

                /* Set Source Routing */
                SrcRoute = 1;

                /* The packet is now "from" us (local IF) */
                /* This suspends the normal error checks for looping packets */
                pPkt->hIFRx = hIFRx = 0;

                break;
            }
        }
    }

    /* If we have a filtered NET, then a packet from outside the */
    /* filtered net can not enter the filtered net */
    if( IP_FILTERENABLE && _IPFltMask )
    {
        /* If the destination is in the protected net and the source */
        /* is not, drop the packet. */
        if( ( IPDst & _IPFltMask ) == _IPFltAddr &&
            ( IPSrc & _IPFltMask ) != _IPFltAddr )
        {
            ips.Filtered++;
            PBM_free( pPkt );
            return;
        }
    }

    /* If not source routing, see if the packet is for us. */
    if( !SrcRoute )
    {
        /* We take the following packets: */
        /*     - The Dst is an all 0's BCast */
        /*     - The Dst is an all 1's BCast */
        /*     - The Dst is a Multicast Addr */
        /*     - The Dst is one of our host addresses */
        /*     - Sent directly to a non-configured IF (non-TCP) */
        /*     - Sent from a local peer to a loopback address */
        if( IPDst == INADDR_ANY ||
            IPDst == INADDR_BROADCAST ||
            IN_MULTICAST(IPDst) ||
            BindFindByHost( 0, IPDst ) ||
            ( IP_DIRECTED_BCAST && BindGetIFByDBCast(IPDst) ) ||
            ( !(pPkt->Flags & (FLG_PKT_MACMCAST|FLG_PKT_MACBCAST)) &&
                hIFRx && !BindFindByIF(hIFRx) &&
                pIpHdr->Protocol != IPPROTO_TCP  ) ||
            ( !hIFRx && IN_LOOPBACK(IPDst) ) )
        {
            /* The packet is for us!!! */

            /*
             *  If IPDst is a multicast address, check extra
             *  for perfect filtering:   
             *  - 224.0.0.1 is always allowed.
             *  - If host is not joined, the others are filtered out.
             *
             */
            if (IN_MULTICAST(IPDst) && IPDst != HNC32(0xe0000001) && 
                !IGMPTestGroup(IPDst, IFGetIndex(hIFRx))) {
                /* Discard the packet, and update the counter */
                ips.CantforwardBA++;
                PBM_free( pPkt );
                return;
            }

            /* First we must reassemble any fragmented packets */
            if( pIpHdr->FlagOff & ~HNC16(IP_DF) )
            {
                /* Packet is fragmented */
                /* We pass the packet to the IPReasm function, which */
                /* consumes the packet. When a packet is ready, it is */
                /* resubmitted to IpRxPacket */
                IPReasm( pPkt );
                return;
            }

#ifdef _INCLUDE_NAT_CODE
            if( IP_NATENABLE )
            {
                /* NAT Processing for Received Packets */
                NatRC = NatIpRxInput( pPkt );
                if( NatRC > 0 )
                    goto forward_post_nat;
                if( NatRC < 0 )
                    return;
            }
#endif

            /* Track packets we deliver to upper layers */
            ips.Delivered++;

            /* Dispatch the IP packet */
            switch( pIpHdr->Protocol )
            {
            case IPPROTO_TCP:
                TcpInput( pPkt );
                break;
            case IPPROTO_UDP:
                UdpInput( pPkt );
                break;
            case IPPROTO_ICMP:
                ICMPInput( pPkt );
                break;
            case IPPROTO_IGMP:
                IGMPInput( pPkt );
                break;
            default:
                ips.Delivered--;
                ips.Noproto++;
                RawInput( pPkt );
                break;
            }
            return;
        }
    }

    /* If we get here, the packet is not for us */
    /* Verify Packet can be forwarded */

    /* We can not foward ... */
    /*    - if the packet was rx'd on a local IF AND we're not source */
    /*      routing (this is loop caused by a bad route configuration) */
    /*    - if forwarding disabled */
    /*    - if addressed to an experimental, multicast, or loopback IP */
    /*    - if mac addr received on was broadcast */

    if( (!hIFRx && !SrcRoute) || !IP_FORWARDING ||
        IPDst == INADDR_ANY || IPDst == INADDR_BROADCAST ||
        IN_EXPERIMENTAL(IPDst) || IN_MULTICAST(IPDst) ||
        IN_LOOPBACK(IPDst) || (pPkt->Flags & FLG_PKT_MACBCAST) )
    {
        ips.CantforwardBA++;
        PBM_free( pPkt );
        return;
    }

    /* Forward Packet */

    /* Process Time to Live */
    if( pIpHdr->Ttl < 2 )
    {
        ips.Expired++;
        ICMPGenPacket( pIpHdr, hIFRx, ICMP_TIMXCEED, ICMP_TIMXCEED_INTRANS, 0 );
        PBM_free( pPkt );
        return;
    }
    pIpHdr->Ttl--;

#ifdef _INCLUDE_NAT_CODE
    /* NAT Processing for Transmitted Packets */
    if( IP_NATENABLE && NatIpTxInput( pPkt ) )
        return;
forward_post_nat:
#endif

    /* Set the IPTx Flags */
    /* Send the packet */
    if( SrcRoute )
        IPTxPacket( pPkt, FLG_IPTX_FORWARDING|FLG_IPTX_SRCROUTE );
     else
        IPTxPacket( pPkt, FLG_IPTX_FORWARDING );

    return;
}

