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
 * ======== icmpin.c ========
 *
 * Routines receving ICMP packets
 *
 */

#include <stkmain.h>

static void ICMPRevSrcRoute( uint IPHdrLen, IPHDR *pbHdrIP );

/*-------------------------------------------------------------------- */
/* ICMPInput() */
/* Rx ICMP Packet */
/*-------------------------------------------------------------------- */
void ICMPInput( PBM_Pkt *pPkt )
{
    HANDLE     hTemp;
    uint       w,IPHdrLen,ICMPLen;
    IPN        IPSrc,IPDst;
    uint       Type,Code;
    UINT8      *pb;
    IPHDR      *pIpHdr;
    ICMPHDR    *pIcHdr;

    /* Get the IP header len */
    IPHdrLen = pPkt->IpHdrLen;

    /* Get the buffer pointer */
    pb = pPkt->pDataBuffer + pPkt->DataOffset;

    /* Assign an IP header pointer */
    pIpHdr = (IPHDR *)pb;

    /* Assign a ICMP header pointer */
    pIcHdr = (ICMPHDR *)(pb + IPHdrLen);

    /* Get the total length of the ICMP message */
    ICMPLen = (uint)(HNC16( pIpHdr->TotalLen )) - IPHdrLen;

    /* Check for packet too small */
    if( ICMPLen < ICMPHDR_SIZE )
    {
ICMPError:
        _ICMPInErrors++;
        PBM_free( pPkt );
        return;
    }

    /* Check checksum */
    w = (uint)pIcHdr->Checksum;
    if( w == 0xFFFF )
        w = 0;
    ICMPChecksum( pIcHdr, ICMPLen );
    if( w != (uint)pIcHdr->Checksum )
        goto ICMPError;

    /* Check for bad type */
    Type = (uint)pIcHdr->Type;
    Code = (uint)pIcHdr->Code;
    if( Type > ICMP_MAXTYPE )
        goto ICMPError;

    /* Bump the stats */
    _ICMPIn[ Type ]++;

    /* Get source and destination */
    IPSrc = RdNet32(&pIpHdr->IPSrc);
    IPDst = RdNet32(&pIpHdr->IPDst);

    /* Process the Message */
    switch( Type )
    {
    case ICMP_UNREACH:
        switch (Code)
        {
        case ICMP_UNREACH_NET:
        case ICMP_UNREACH_HOST:
        case ICMP_UNREACH_PROTOCOL:
        case ICMP_UNREACH_PORT:
        case ICMP_UNREACH_SRCFAIL:
            Code += PRC_UNREACH_NET;
            break;

        case ICMP_UNREACH_NEEDFRAG:
            Code = PRC_MSGSIZE;
            break;

        case ICMP_UNREACH_NET_UNKNOWN:
        case ICMP_UNREACH_NET_PROHIB:
        case ICMP_UNREACH_TOSNET:
            Code = PRC_UNREACH_NET;
            break;

        case ICMP_UNREACH_HOST_UNKNOWN:
        case ICMP_UNREACH_ISOLATED:
        case ICMP_UNREACH_HOST_PROHIB:
        case ICMP_UNREACH_TOSHOST:
            Code = PRC_UNREACH_HOST;
            break;

        case ICMP_UNREACH_FILTER_PROHIB:
        case ICMP_UNREACH_HOST_PRECEDENCE:
        case ICMP_UNREACH_PRECEDENCE_CUTOFF:
            Code = PRC_UNREACH_PORT;
            break;

        default:
            goto bad_code;
        }
        goto deliver;

    case ICMP_TIMXCEED:
        if( Code > 1 )
            goto bad_code;
        Code += PRC_TIMXCEED_INTRANS;
        goto deliver;

    case ICMP_PARAMPROB:
        if( Code > 1 )
            goto bad_code;
        Code = PRC_PARAMPROB;
            goto deliver;

    case ICMP_SOURCEQUENCH:
        if( Code )
            goto bad_code;
        Code = PRC_QUENCH;

    deliver:
        SockPcbCtlError( Code, (IPHDR *)(pIcHdr->Data + 4) );
        break;

    bad_code:
        break;

    case ICMP_REDIRECT:
        if( Code > 3 )
            goto bad_code;

        /* Handle Route Change Immediately */
        pIpHdr = (IPHDR *)(pIcHdr->Data + 4);

        /* IPSrc is the route we're trying to get to */
        IPSrc = RdNet32(&pIpHdr->IPDst);

        /* IPDst is the gatway we should be uisng */
        IPDst = RdNet32(((IPN *)(pIcHdr->Data)));

        /* Redirect route if option is set */
        if( ICMP_DO_REDIRECT )
        {
            RtRedirect( IPSrc, IPDst );
            SockPcbCtlError(PRC_REDIRECT_NET+Code, (IPHDR *)(pIcHdr->Data+4));
        }

        /* Lastly, send a report */
        RTCReport( MSG_RTC_REDIRECT, IPSrc, IPDst );
        break;

    /* Echo Request */
    case ICMP_ECHO:
        /* 
         *  If configured, not to reply to ICMP ECHO REQ packets   
         *  simply discard it.
         * 
         */
        if (ICMP_DONT_REPLY_ECHO) {
            PBM_free( pPkt );
            return;
        }

        /* If this packet is for us, reflect it */
        if( BindFindByHost( 0, IPDst ) || IN_LOOPBACK(IPDst) )
            goto ICMP_REFLECT;

        /* 
         *  If configured, reply to ICMP ECHO REQ packets sent to  
         *  BCast, Directed BCast, and MCast addresses.
         * 
         */

        if ((ICMP_DONT_REPLY_BCAST == 0 && IPDst == INADDR_BROADCAST) ||
            (ICMP_DONT_REPLY_MCAST == 0 && IN_MULTICAST(IPDst)))  {
            /* Get a local IP addr to use as "dst" */
            IPDst = BindIFNet2IPHost(0,IPSrc);

            /* Only reply to a limited broadast with IP in */
            /* the same subnet as the source address */
            if (IPDst)
                goto ICMP_REFLECT;
        }
        else if (ICMP_DONT_REPLY_BCAST == 0 && IP_DIRECTED_BCAST) {
            hTemp = BindGetIFByDBCast(IPDst);
            if( hTemp )
            {
                IPDst = BindIF2IPHost( hTemp );
                goto ICMP_REFLECT;
            }
        }
        break;

    /* The following are just sent to Raw */
    case ICMP_ECHOREPLY:
    case ICMP_ROUTERADVERT:
    case ICMP_ROUTERSOLICIT:
    case ICMP_TSTAMPREPLY:
    case ICMP_IREQREPLY:
    case ICMP_MASKREPLY:
    default:
        break;
    }

    /* Give most packets to Raw */
    RawInput( pPkt );
    return;

ICMP_REFLECT:
    /* Don't forward back to bad address */
    if( IPSrc == INADDR_ANY || IPSrc == INADDR_BROADCAST ||
            IN_EXPERIMENTAL(IPSrc) || IN_MULTICAST(IPSrc) ||
            IN_LOOPBACK(IPSrc) )
    {
        PBM_free( pPkt );
        return;
    }

    /* Fix the TTL */
    pIpHdr->Ttl = ICMP_TTL_ECHO;

    /* Change the type to reply */
    pIcHdr->Type = ICMP_ECHOREPLY;

    /* Bump the stats */
    _ICMPOut[ ICMP_ECHOREPLY ]++;

    /* Swap Src and Dst */
    /* The Old Src is now the Dst */
    WrNet32( &pIpHdr->IPSrc, IPDst );
    WrNet32( &pIpHdr->IPDst, IPSrc );

    /* Checksum the reply */
    ICMPChecksum( pIcHdr, ICMPLen );

    /* Now we must reverse the source route (if any) */
    if( IPHdrLen > IPHDR_SIZE )
        ICMPRevSrcRoute( IPHdrLen, pIpHdr );

    /* Send the packet */
    IPTxPacket( pPkt, FLG_IPTX_RAW );

    return;
}

/*-------------------------------------------------------------------- */
/* ICMPRevSrcRoute() */
/* Reverse the source route of a packet */
/*-------------------------------------------------------------------- */
static void ICMPRevSrcRoute( uint IPHdrLen, IPHDR *pIpHdr )
{
    uint   OptIdx,OptBytes,OptSize;
    UINT8  Opt;
    int    OffFirst,OffLast;
    IPN    IPTmp;

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
                return;
        }

        /* Check for source routing */
        if( Opt == IPOPT_SSRR || Opt == IPOPT_LSRR )
        {
            /* Source route in use. We must reverse it. */

            /* First, set Offset to 4 */
            pIpHdr->Options[OptIdx+2] = 4;

            /* Now reverse the route */
            OffFirst = OptIdx+3;
            OffLast  = OptIdx+OptSize-4;

            /* We know the DestIP is now the last thing in the source */
            /* route, and what was last in the source route is now */
            /* DestIP */
            mmCopy( &IPTmp, pIpHdr->Options+OffLast, 4 );
            mmCopy( pIpHdr->Options+OffLast, &pIpHdr->IPDst, 4 );
            mmCopy( &pIpHdr->IPDst, &IPTmp, 4 );

            /* We've used OffLast, so bump it down */
            OffLast -= 4;

            /* Now, while OffFirst < OffLast, do SWAPS. */
            while( OffFirst < OffLast )
            {
                mmCopy( &IPTmp, pIpHdr->Options+OffLast, 4 );
                mmCopy( pIpHdr->Options+OffLast, pIpHdr->Options+OffFirst, 4 );
                mmCopy( pIpHdr->Options+OffFirst, &IPTmp, 4 );
                OffFirst += 4;
                OffLast  -= 4;
            }
        }
    }
}

