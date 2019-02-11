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
 * ======== natpkt.c ========
 *
 * NAT Address Translation, packet routines
 *
 */

#include <stkmain.h>
#ifdef _INCLUDE_NAT_CODE
#include "nat.h"

/* The IP address info used in mappings */
IPN NatIpServer = 0;
static IPN NatIpAddr   = 0;
static IPN NatIpMask   = 0;
static uint NatMTU     = 0;

/* Timeouts based on TCP state */
static UINT32 StateTimeout[8] = { NAT_TCP_IDLE_SECONDS,     /* NI_TCP_IDLE */
                                  NAT_TCP_SYN_SECONDS,      /* NI_TCP_SYNSENT_TX */
                                  NAT_TCP_SYN_SECONDS,      /* NI_TCP_SYNSENT_RX */
                                  NAT_TCP_SYN_SECONDS,      /* NI_TCP_SYNSENT_ALL */
                                  NAT_TCP_ACTIVE_SECONDS,   /* NI_TCP_ESTAB */
                                  NAT_TCP_IDLE_SECONDS,     /* NI_TCP_CLOSING_TX */
                                  NAT_TCP_IDLE_SECONDS,     /* NI_TCP_CLOSING_RX */
                                  NAT_TCP_CLOSED_SECONDS }; /* NI_TCP_CLOSED */

/* TCP Flag Equates */
#define FIN 0x01
#define SYN 0x02
#define RST 0x04
#define PSH 0x08
#define ACK 0x10
#define URG 0x20

/* TCP Header Option Definitions */
#define TCPOPT_EOL              0
#define TCPOPT_NOP              1
#define TCPOPT_MAXSEG           2
#define TCPOLEN_MAXSEG          4

/* NAT Translation Statistics */
NATSTATS nats;

static UINT32   NatCkMod(IPN IPOld, UINT16 PortOld, IPN IPNew, UINT16 PortNew );
static void     NatTcp( PBM_Pkt *pPkt, uint fRx, NATINFO *pni, TCPHDR *pTcpHdr );
static int      NatIcmpError( PBM_Pkt *pPkt, IPHDR *pIpHdr );


/*-------------------------------------------------------------------- */
/* NatSetConfig - Setup the NAT configuration */
/*-------------------------------------------------------------------- */
void NatSetConfig( IPN IPAddr, IPN IPMask, IPN IPServer, uint MTU )
{
    /* Quick sanity check. The Sever IP can't be in the mapping subnet */
    /* Also MTU must be 64 to 1500. */
    /* Setting the mask to NULL will disable NAT. */
    if( ((IPServer & IPMask)==(IPAddr & IPMask)) || (MTU<64 || MTU>1500) )
        IPMask = 0;

    NatIpAddr   = IPAddr;
    NatIpMask   = IPMask;
    NatIpServer = IPServer;
    NatMTU      = MTU;
}

/*-------------------------------------------------------------------- */
/* NatCkMod() */
/* Calculates the modification factor for adjusting an IP checksum */
/*-------------------------------------------------------------------- */
static UINT32 NatCkMod( IPN IPOld, UINT16 PortOld, IPN IPNew, UINT16 PortNew )
{
    UINT32  CkMod,CkOrg;

    CkOrg =  IPOld & 0xFFFF;
    CkOrg += (IPOld>>16) & 0xFFFF;
    CkOrg += (UINT32) PortOld;
    CkOrg =  (CkOrg&0xFFFF) + (CkOrg>>16);
    CkMod =  IPNew & 0xFFFF;
    CkMod += (IPNew>>16) & 0xFFFF;
    CkMod += (UINT32) PortNew;
    CkMod =  (CkMod&0xFFFF) + (CkMod>>16);
    CkMod -= CkOrg;
    return(((CkMod&0xFFFF) + (CkMod>>16)) & 0xFFFF);
}

/*-------------------------------------------------------------------- */
/* NatIpTxInput - NAT Processing of IP Tx packet */
/* Before packet is sent to IPTx for forwarding it is examined to see */
/* if the IP source address is in the NatIpAddr/NatIpMask range. If so, */
/* the following is performed: */
/* 1. If the packet is fragmented it is sent for reassembly */
/* 2. For TCP and UDP packets, the source IP and source Port are used */
/*    to search for a NATINFO entry. If found, the source IP and source */
/*    port are modfied to be NatIpServer, and the mapping port. */
/*    For ICMP packets, a special function is called to detect echo */
/*    requests. */
/* 3. If a NATINFO entry is not found for (1), then a new entry is */
/*    created before the alterations are performed. */
/* 4. If (3) fails, the packet is discarded. */
/* If this function returns 1, the packet was consumed; else returns 0 */
/*-------------------------------------------------------------------- */
int NatIpTxInput( PBM_Pkt *pPkt )
{
    IPHDR   *pIpHdr;
    IPN     IPSrc,IPDst;
    UINT16  *pPortSrc;
    UINT16  PortSrc;
    UINT16  PortDst;
    uint    IPHdrLen;
    NATINFO *pni;
    UINT32  CkMod,CkOrg;
    UINT16  *pChecksum;
    TCPHDR  *pTcpHdr;

    /* If we're not configured, return */
    if( !(NatIpAddr&NatIpMask) )
        return(0);

    nats.TxExamined++;

    /* Get pointer to IP header */
    pIpHdr = (IPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Get IP Source & Destination */
    IPSrc = RdNet32( &pIpHdr->IPSrc );
    IPDst = RdNet32( &pIpHdr->IPDst );

    /* If source isn't from the targeted subnet, or it was sent to the */
    /* targeted subnet, return */
    if( (IPSrc&NatIpMask) != NatIpAddr || (IPDst&NatIpMask) == NatIpAddr )
        return(0);

    /* If the packet is fragmented, reassemble it */
    if( pIpHdr->FlagOff & ~HNC16(IP_DF) )
    {
        /* Reasm will send it through IP RX processing again - Fix the TTL */
        pIpHdr->Ttl++;
        IPReasm( pPkt );
        return(1);
    }

    /* Zap the DF flag. Since NAT may involve MTU change, we hide */
    /* this from the sender. */
    pIpHdr->FlagOff &= ~HNC16(IP_DF);

    /* Get the length of the IP header */
    IPHdrLen = (pIpHdr->VerLen & 0xf) * 4;

    /* Translation varies slightly by protocol */
    if( pIpHdr->Protocol == IPPROTO_TCP )
    {
        /* TCP Packet Translation */

        /* Get TCP packet header */
        pTcpHdr = (TCPHDR *)(((UINT8 *)pIpHdr) + IPHdrLen);

        pPortSrc = &pTcpHdr->SrcPort;
        pChecksum = &pTcpHdr->TCPChecksum;
        PortDst = HNC16( pTcpHdr->DstPort );
    }
    else if( pIpHdr->Protocol == IPPROTO_UDP )
    {
        /* UDP Packet Translation */
        UDPHDR  *pUdpHdr;

        /* Get UDP packet header */
        pUdpHdr = (UDPHDR *)(((UINT8 *)pIpHdr) + IPHdrLen);

        pPortSrc = &pUdpHdr->SrcPort;
        pChecksum = &pUdpHdr->UDPChecksum;
        PortDst = HNC16( pUdpHdr->DstPort );
    }
    else if( pIpHdr->Protocol == IPPROTO_ICMP )
    {
        /* ICMP Packet Translation */
        ICMPHDR *pIcHdr;

        /* Get ICMP packet header */
        pIcHdr = (ICMPHDR *)(((UINT8 *)pIpHdr) + IPHdrLen);

        /* We only translate ECHO and TSTAMP requests */
        if( pIcHdr->Type != ICMP_ECHO && pIcHdr->Type != ICMP_TSTAMP )
            return(0);

        pPortSrc = (UINT16 *)pIcHdr->Data;
        pChecksum = &pIcHdr->Checksum;
        PortDst = 0;
    }
    else
        return(0);

    /* Get source port */
    PortSrc = *pPortSrc;
    PortSrc = HNC16(PortSrc);

    nats.TxQualified++;

    /* Find a NATINFO entry */
    pni = NatFindPNI( IPSrc, PortSrc, IPDst, PortDst, pIpHdr->Protocol, 0 );

    /* If no NATINFO, abort */
    if( !pni )
    {
        PBM_free( pPkt );
        return(1);
    }

    /* Alter the source IP and port */
    nats.TxAltered++;

    /* Mark the packet as having gone through NAT */
    pPkt->Flags |= FLG_PKT_NAT;

    /* Change PortSrc to be the NEW source port */
    PortSrc = HNC16( pni->PortMapped );

    /* Track changes for checksum modification (ICMP doesn't use IP address) */
    if( pIpHdr->Protocol != IPPROTO_ICMP )
         CkMod = NatCkMod( IPSrc, *pPortSrc, NatIpServer, PortSrc );
    else
         CkMod = NatCkMod( 0, *pPortSrc, 0, PortSrc );

    /* Alter the packet */
    WrNet32( &pIpHdr->IPSrc, NatIpServer );
    *pPortSrc = PortSrc;

    /* Adjust the TCP/UDP/ICMP checksum */
    CkOrg = (~(UINT32)*pChecksum) & 0xFFFF;
    CkOrg += CkMod;
    CkOrg = (CkOrg&0xFFFF) + (CkOrg>>16);
    *pChecksum = (UINT16)~CkOrg;

    /* If TCP, do more processing for MTU and record timeout value */
    if( pIpHdr->Protocol == IPPROTO_TCP )
        NatTcp( pPkt, 0, pni, pTcpHdr );
    else
        pni->Timeout = llTimerGetTime(0) + NAT_IDLE_SECONDS;

    /* If this entry has a "proxy", we always consume the packet. */
    /* The proxy will forward any new packets directly to IP */
    if( pni->hProxyEntry )
    {
        ProxyTx( pni, pPkt, pIpHdr );
        return(1);
    }

    return(0);
}

/*-------------------------------------------------------------------- */
/* NatIpRxInput - NAT Processing of IP Rx packet */
/* Packets to be "delivered" to upper layer protocols are first */
/* sent to this routine. If the destination IP address matches the */
/* NatIpServer address, then the following is performed: */
/* 1. For TCP and UDP packets with a destination port in the Nat */
/*    mapping port range, use the port to find a NATINFO entry and */
/*    alter the destination IP address and destination port */
/*    and return TRUE. */
/* 2. Convert incoming ICMP error packets where the attached IP header */
/*    meets the citeria of (1) above. */
/* If this function returns 1, the packet should be re-forwarded */
/* If this function returns -1, the packet was consumed */
/*-------------------------------------------------------------------- */
int NatIpRxInput( PBM_Pkt *pPkt  )
{
    IPHDR   *pIpHdr;
    IPN     IPSrc,IPDst;
    UINT16  *pPortDst;
    UINT16  PortSrc;
    UINT16  PortDst;
    uint    IPHdrLen;
    NATINFO *pni;
    UINT32  CkMod,CkOrg;
    UINT16  *pChecksum;
    TCPHDR  *pTcpHdr;

    /* If we're not configured, return */
    if( !(NatIpAddr&NatIpMask) )
        return(0);

    nats.RxExamined++;

    /* Get pointer to IP header */
    pIpHdr = (IPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Get IP Source & Destination */
    IPSrc = RdNet32( &pIpHdr->IPSrc );
    IPDst = RdNet32( &pIpHdr->IPDst );

    /* If destination isn't us, or the source isn't from outside the */
    /* targeted subnet, return */
    if( IPDst != NatIpServer || (IPSrc&NatIpMask) == NatIpAddr )
        return(0);

    /* Get the length of the IP header */
    IPHdrLen = (pIpHdr->VerLen & 0xf) * 4;

    /* Translation varies slightly by protocol */
    if( pIpHdr->Protocol == IPPROTO_TCP )
    {
        /* TCP Packet Translation */

        /* Get TCP packet header */
        pTcpHdr = (TCPHDR *)(((UINT8 *)pIpHdr) + IPHdrLen);

        pPortDst = &pTcpHdr->DstPort;
        pChecksum = &pTcpHdr->TCPChecksum;
        PortSrc = HNC16( pTcpHdr->SrcPort );
    }
    else if( pIpHdr->Protocol == IPPROTO_UDP )
    {
        /* UDP Packet Translation */
        UDPHDR  *pUdpHdr;

        /* Get UDP packet header */
        pUdpHdr = (UDPHDR *)(((UINT8 *)pIpHdr) + IPHdrLen);

        pPortDst = &pUdpHdr->DstPort;
        pChecksum = &pUdpHdr->UDPChecksum;
        PortSrc = HNC16( pUdpHdr->SrcPort );
    }
    else if( pIpHdr->Protocol == IPPROTO_ICMP )
    {
        /* ICMP Packet Translation */
        ICMPHDR *pIcHdr;
        uint    tmp;

        /* Get ICMP packet header */
        pIcHdr = (ICMPHDR *)(((UINT8 *)pIpHdr) + IPHdrLen);

        /* First see if this is an ICMP error packet */
        tmp = (uint)pIcHdr->Type;
        if( tmp==ICMP_UNREACH || tmp==ICMP_SOURCEQUENCH || tmp==ICMP_REDIRECT
                              || tmp==ICMP_TIMXCEED || tmp==ICMP_PARAMPROB )
            return( NatIcmpError( pPkt, pIpHdr ) );

        /* Here we only translate ECHO and TSTAMP replies */
        if( tmp != ICMP_ECHOREPLY && tmp != ICMP_TSTAMPREPLY )
            return( 0 );

        pPortDst = (UINT16 *)pIcHdr->Data;
        pChecksum = &pIcHdr->Checksum;
        PortSrc = 0;
    }
    else
        return(0);

    /* Get dest port */
    PortDst = *pPortDst;
    PortDst = HNC16(PortDst);

    if( !PortDst )
        return(0);

    nats.RxQualified++;

    /* Find a NATINFO entry */
    pni = NatFindPNI( 0, 0, IPSrc, PortSrc, pIpHdr->Protocol, PortDst );

    /* If no NATINFO, return */
    if( !pni )
        return(0);

    /* Alter the destination IP and port */
    nats.RxAltered++;

    /* Mark the packet as having gone through NAT */
    pPkt->Flags |= FLG_PKT_NAT;

    /* Change PortDst to be the NEW dest port */
    PortDst = HNC16( pni->PortLocal );

    /* Track changes for checksum modification (ICMP doesn't use IP address) */
    if( pIpHdr->Protocol != IPPROTO_ICMP )
        CkMod = NatCkMod( IPDst, *pPortDst, pni->IPLocal, PortDst );
    else
        CkMod = NatCkMod( 0, *pPortDst, 0, PortDst );

    /* Alter the packet */
    WrNet32( &pIpHdr->IPDst, pni->IPLocal );
    *pPortDst = PortDst;

    /* Adjust the TCP/UDP/ICMP checksum */
    CkOrg = (~(UINT32)*pChecksum) & 0xFFFF;
    CkOrg += CkMod;
    CkOrg = (CkOrg&0xFFFF) + (CkOrg>>16);
    *pChecksum = (UINT16)~CkOrg;

    /* If TCP, do more processing for MTU and record timeout value */
    if( pIpHdr->Protocol == IPPROTO_TCP )
        NatTcp( pPkt, 1, pni, pTcpHdr );
    else
        pni->Timeout = llTimerGetTime(0) + NAT_IDLE_SECONDS;

    /* The packet is now "from" us (local IF) */
    /* This suspends normal error checks for looping packets */
    pPkt->hIFRx = 0;

    /* If this entry has a "proxy", we always consume the packet. */
    /* The proxy will forward any new packets directly to IP */
    if( pni->hProxyEntry )
    {
        ProxyRx( pni, pPkt, pIpHdr );
        return(-1);
    }

    return(1);
}

/*-------------------------------------------------------------------- */
/* NatIcmpError - NAT Processing of ICMP Error packets */
/* Here, we are only interested in ICMP error packets, where the header */
/* of the offending IP datagram is attached. */
/* If this function returns 1, the packet should be re-forwarded */
/*-------------------------------------------------------------------- */
static int NatIcmpError( PBM_Pkt *pPkt, IPHDR *pIpHdr )
{
    uint    IPHdrLen;
    ICMPHDR *pIcHdr;
    uint    icmpsize;
    IPHDR   *pIpHdr2;
    NATINFO *pni;
    UINT16  PortDst;
    UINT16  *pPortDst;

    /* Get Pointer to protocol header */
    IPHdrLen = (pIpHdr->VerLen & 0xf) * 4;
    pIcHdr = (ICMPHDR *)(((UINT8 *)pIpHdr) + IPHdrLen);

    /* Get the total length of the ICMP message */
    icmpsize = (uint)(HNC16( pIpHdr->TotalLen )) - IPHdrLen;

    /* The only packets that we process is where the OFFENDING packet */
    /* was sent from a translated source. */
    pIpHdr2  = (IPHDR *)(pIcHdr->Data + 4);
    IPHdrLen = (pIpHdr2->VerLen & 0xf) * 4;

    /* Translation varies slightly by protocol */
    if( pIpHdr2->Protocol == IPPROTO_TCP || pIpHdr2->Protocol == IPPROTO_UDP )
    {
        /* TCP/UDP Packet Translation */
        TCPHDR  *pTcpHdr;

        /* Get TCP packet header */
        pTcpHdr = (TCPHDR *)(((UINT8 *)pIpHdr2) + IPHdrLen);

        pPortDst = &pTcpHdr->SrcPort;
    }
    else if( pIpHdr->Protocol == IPPROTO_ICMP )
    {
        /* ICMP Packet Translation */
        ICMPHDR *pIcHdr2;

        /* Get ICMP packet header */
        pIcHdr2 = (ICMPHDR *)(((UINT8 *)pIpHdr2) + IPHdrLen);

        /* We only translate ECHO and TSTAMP requests */
        if( pIcHdr2->Type != ICMP_ECHO && pIcHdr2->Type != ICMP_TSTAMP )
            return(0);

        pPortDst = (UINT16 *)pIcHdr2->Data;
    }
    else
        return(0);

    /* Get dest port */
    PortDst = *pPortDst;
    PortDst = HNC16(PortDst);

    if( !PortDst )
        return(0);

    nats.RxQualified++;

    /* Find a NATINFO entry */
    pni = NatFindPNI( 0, 0, 0, 0, pIpHdr2->Protocol, PortDst );

    /* If no NATINFO, return */
    if( !pni )
        return(0);

    /* Alter the source IP and port in the OFFENDING header, and */
    /* the DstIP in the real IP header */
    nats.RxAltered++;

    /* Mark the packet as having gone through NAT */
    pPkt->Flags |= FLG_PKT_NAT;

    /* Alter the packet */
    WrNet32( &pIpHdr->IPDst, pni->IPLocal );
    WrNet32( &pIpHdr2->IPSrc, pni->IPLocal );
    *pPortDst = HNC16(pni->PortLocal);

    /* Note: We won't alter the NAT entry timeout since we don't track */
    /*       the original protocol here. Plus an error isn't exactly */
    /*       active use of the entry. */

    /* Since this function is called infrequently, we'll */
    /* just re-checksum the whole packet. */
    ICMPChecksum( pIcHdr, icmpsize );

    /* The packet is now "from" us (local IF) */
    /* This suspends normal error checks for looping packets */
    pPkt->hIFRx = 0;

    return(1);
}

/*-------------------------------------------------------------------- */
/* NatTcp() */
/* TCP Options */
/*   Adjusts MTU negotiation when enabled */
/* TCP NAT Record Timeouts */
/*   Sets a reasonable TCP timeout based on a guess at the current */
/*   TCP state. Note: We only care about keeping the normal */
/*   "established"  state open for a long period of time. Once a FIN */
/*   or RST is detected, the connect is expected to remain relatively */
/*   active until fully closed. */
/*   I.E.: Idle half closed sessions are not kept. */
/*-------------------------------------------------------------------- */
static void NatTcp( PBM_Pkt *pPkt, uint fRx, NATINFO *pni, TCPHDR *pTcpHdr )
{
    int    OptLen;

    (void)pPkt;

    /* Check TCP flags */

    /* RST */
    if( pTcpHdr->Flags & RST )
    {
        if( pni->TcpState == NI_TCP_ESTAB )
            nats.LongTerm--;
        pni->TcpState = NI_TCP_CLOSED;
    }
    /* FIN */
    else if( pTcpHdr->Flags & FIN )
    {
        if( pni->TcpState < NI_TCP_CLOSING_TX )
        {
            if( pni->TcpState == NI_TCP_ESTAB )
                nats.LongTerm--;
            pni->TcpState = NI_TCP_CLOSING_TX + fRx;
        }
        else if( pni->TcpState == NI_TCP_CLOSING_TX )
        {
            if( fRx )
                pni->TcpState = NI_TCP_CLOSED;
        }
        else if( pni->TcpState == NI_TCP_CLOSING_RX )
        {
            if( !fRx )
                pni->TcpState = NI_TCP_CLOSED;
        }
    }
    /* SYN */
    else if( pTcpHdr->Flags & SYN )
    {
        /* Allow a closed state to reconnect */
        if( pni->TcpState == NI_TCP_CLOSED )
            pni->TcpState = NI_TCP_IDLE;

        /* Validate TCP MSS Option */

        /* Set OptLen = TCP Option Length */
        OptLen = (int)((pTcpHdr->HdrLen >> 4) << 2) - TCPHDR_SIZE;
        if( OptLen > 0 )
        {
            int    i = 0;
            INT8   opt,olen;
            uint   mss;
            uint   TcpMTU = NatMTU - 40;

            /* Scan the options */
            for( ; i < OptLen; i+=olen )
            {
                opt = pTcpHdr->Options[i];
                if( opt == TCPOPT_EOL )
                    break;
                if( opt == TCPOPT_NOP )
                    olen = 1;
                else
                {
                    olen = (INT8) pTcpHdr->Options[i+1];

                    /* Check for a max segment size option */
                    if( opt == TCPOPT_MAXSEG && olen == TCPOLEN_MAXSEG )
                    {

                        /* Get the MSS as specified */
                        mss = pTcpHdr->Options[i+3]+pTcpHdr->Options[i+2]*256;

                        /* See if it violates our MTU */
                        if( mss > TcpMTU )
                        {
                            UINT32 tw32o,tw32n,*ptw32;

                            /* Get the 32 bit value containing the 16 bit MTU */
                            ptw32 = (UINT32 *)(&pTcpHdr->Options[i+2]);
                            ptw32 = (UINT32 *)((UINT32)ptw32&~1);
                            tw32o = RdNet32(ptw32);

                            /* Change the MTU */
                            pTcpHdr->Options[i+3] = (UINT8)(TcpMTU & 0xFF);
                            pTcpHdr->Options[i+2] = (UINT8)(TcpMTU >> 8);
                            tw32n = RdNet32(ptw32);

                            /* Fix the checksum */
                            tw32n = NatCkMod( tw32o, 0, tw32n, 0 );
                            tw32o = (~(UINT32)pTcpHdr->TCPChecksum) & 0xFFFF;
                            tw32o += tw32n;
                            tw32o = (tw32o&0xFFFF) + (tw32o>>16);
                            pTcpHdr->TCPChecksum = (UINT16)~tw32o;
                        }
                    }
                }
            }
        }

        /* Advance connect state if possible */
        if( pni->TcpState < NI_TCP_SYNSENT_TX )
            pni->TcpState = NI_TCP_SYNSENT_TX + fRx;
        else if( pni->TcpState == NI_TCP_SYNSENT_TX )
        {
            if( fRx )
                pni->TcpState = NI_TCP_SYNSENT_ALL;
        }
        else if( pni->TcpState == NI_TCP_SYNSENT_RX )
        {
            if( !fRx )
                pni->TcpState = NI_TCP_SYNSENT_ALL;
        }
    }
    /* ACK */
    else if( pTcpHdr->Flags & ACK )
    {
        if( pni->TcpState == NI_TCP_SYNSENT_ALL )
        {
            pni->TcpState = NI_TCP_ESTAB;
            nats.LongTerm++;
            if( nats.LongTerm > nats.MaxLongTerm )
                nats.MaxLongTerm = nats.LongTerm;
        }
    }

    pni->Timeout = llTimerGetTime(0) + StateTimeout[ pni->TcpState ];
}
#endif

