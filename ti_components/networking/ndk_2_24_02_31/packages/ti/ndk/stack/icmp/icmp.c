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
 * ======== icmp.c ========
 *
 * Routines related to ICMP
 *
 */

#include <stkmain.h>

UINT32   _ICMPInErrors  = 0;
UINT32   _ICMPOutErrors = 0;
UINT32   _ICMPIn[ ICMP_MAXTYPE+1 ];
UINT32   _ICMPOut[ ICMP_MAXTYPE+1 ];

/*-------------------------------------------------------------------- */
/* void ICMPChecksum( ICMPHDR *picmp ) */
/* Checksums an ICMP header */
/*-------------------------------------------------------------------- */
void ICMPChecksum( ICMPHDR *pIcHdr, uint Size )
{
    int     tmp1;
    UINT16  *pw;
    UINT32  TSum;

    /* Checksum field is NULL in checksum calculations */
    pIcHdr->Checksum = 0;

    /* Checksum the header */
    pw = (UINT16 *)pIcHdr;
    TSum = 0;
    for( tmp1=Size; tmp1 > 1; tmp1 -= 2 )
        TSum += (UINT32)*pw++;
#ifdef BIGENDIAN
    if( tmp1 )
        TSum += (UINT32)(*pw & 0xFF00);
#else
    if( tmp1 )
        TSum += (UINT32)(*pw & 0x00FF);
#endif
    TSum = (TSum&0xFFFF) + (TSum>>16);
    TSum = (TSum&0xFFFF) + (TSum>>16);
    TSum = ~TSum;

    /* Note checksum is Net/Host byte order independent */
    pIcHdr->Checksum = (UINT16)TSum;
}

/*-------------------------------------------------------------------- */
/* ICMPGenPacket( pbHdr, hIFRx, Type, Code, dwAux ) */
/* Generates 8 byte ICMP Message Packet */
/*-------------------------------------------------------------------- */
void ICMPGenPacket( IPHDR *pIpHdr, HANDLE hIFRx,
                    uint Type, uint Code, UINT32 Aux )
{
    PBM_Pkt  *pPkt;
    uint     IPHdrLen,ICMPLen;
    UINT8    *pb;
    ICMPHDR  *pIcHdr;
    IPN      IPSrc,IPTmp;

    /* Don't let idiots crash us */
    if( Type > ICMP_MAXTYPE )
    {
        _ICMPOutErrors++;
        return;
    }

    /* Get the source of this disaster */
    IPSrc = RdNet32( &pIpHdr->IPSrc );

    /* Get the IP header len */
    IPHdrLen = (pIpHdr->VerLen & 0xF) * 4;

    /* Don't send ICMP for anything but first fragment */
    if( pIpHdr->FlagOff & ~(HNC16(IP_DF|IP_MF)) )
        return;

    /* Don't ICMP to bad address */
    if( IPSrc == INADDR_ANY || IPSrc == INADDR_BROADCAST ||
            IN_EXPERIMENTAL(IPSrc) || IN_MULTICAST(IPSrc) ||
            IN_LOOPBACK(IPSrc) )
        return;

    /* Don't ICMP because of a packet sent to a bad address */
    IPTmp = RdNet32( &pIpHdr->IPDst );
    if( IPTmp == INADDR_ANY || IPTmp == INADDR_BROADCAST ||
            IN_EXPERIMENTAL(IPTmp) || IN_MULTICAST(IPTmp) ||
            IN_LOOPBACK(IPTmp) )
        return;

    /* Bump the stats */
    _ICMPOut[ Type ]++;

    /* Create the packet */
    /* Payload = ICMPHDR + 4 bytes, PLUS the org IP header + 8 bytes */
    /* Also add in the size for a STANDARD IP header for the new pkt */
    ICMPLen = ICMPHDR_SIZE + 4 + IPHdrLen + 8;

    if( !(pPkt = NIMUCreatePacket( ICMPLen + IPHDR_SIZE )) )
    {
        _ICMPOutErrors++;
        return;
    }    

    /* Get a pointer to the new ICMP header */
    /* pb --> Layer3 */
    /* pIcHdr --> Layer4 */
    pb     = pPkt->pDataBuffer + pPkt->DataOffset;
    pIcHdr = (ICMPHDR *)(pb + IPHDR_SIZE);

    /* Set the type and code */
    pIcHdr->Type = (UINT8)Type;
    pIcHdr->Code = (UINT8)Code;

    /* The next four bytes are supplied to us in Aux */
    WrNet32( pIcHdr->Data, Aux );

    /* Copy the original IP header, plus 8 bytes of original payload */
    mmCopy( pIcHdr->Data+4, pIpHdr, IPHdrLen+8 );

    /* Checksum the ICMP header */
    ICMPChecksum( pIcHdr, ICMPLen );

    /* Get a pointer to the IP header - the packet is already Layer3 */
    pIpHdr  = (IPHDR *)pb;

    /* Set some IP header stuff */
    pIpHdr->VerLen   = 0x45;      /* Required when creating own header */
    pIpHdr->Ttl      = ICMP_TTL;  /* Use default ICMP Ttl */
    pIpHdr->Tos      = 0;         /* Rcmd'd for ICMP errors */
    pIpHdr->Protocol = 1;         /* ICMP */

    WrNet32( &pIpHdr->IPDst, IPSrc );

    /* Find a good IP source address */
    if( hIFRx || !(IPSrc = BindIFNet2IPHost( 0, IPSrc )) )
        IPSrc = BindIF2IPHost( hIFRx );
    WrNet32( &pIpHdr->IPSrc, IPSrc );

    /* Set the fragment valid data size */
    pPkt->ValidLen = ICMPLen+IPHDR_SIZE;

    /* Send the packet */
    IPTxPacket( pPkt, 0 );
}

/*-------------------------------------------------------------------- */
/* ICMPSendRtAdv( HANDLE hIFTx, uint Life, IPN IPAddr, UINT32 dwPref ) */
/* Generates 8 byte ICMP Message Packet */
/*-------------------------------------------------------------------- */
void ICMPSendRtAdv( HANDLE hIFTx, uint Life, IPN IPAddr, long Pref )
{
    PBM_Pkt    *pPkt;
    uint       ICMPLen;
    UINT8      *pb;
    ICMPRTAHDR *pRtaHdr;
    ICMPHDR    *pIcHdr;
    IPHDR      *pIpHdr;

    /* Create the packet */
    /* Payload = ICMPHDR + ICMPRTAHDR */
    /* Also add in the size for a STANDARD IP header for the new pkt */
    ICMPLen = ICMPHDR_SIZE + ICMPRTAHDR_SIZE;

    if( !(pPkt = NIMUCreatePacket( ICMPLen + IPHDR_SIZE )) )
    {
        _ICMPOutErrors++;
        return;
    }    

    /* Get a pointer to the new ICMP header */
    /* pb --> Layer3 */
    /* pIcHdr --> Layer4 */
    pb     = pPkt->pDataBuffer + pPkt->DataOffset;
    pIcHdr = (ICMPHDR *)(pb + IPHDR_SIZE);

    /* Bump the stats */
    _ICMPOut[ ICMP_ROUTERADVERT ]++;

    /* Set the type and code */
    pIcHdr->Type = ICMP_ROUTERADVERT;
    pIcHdr->Code = 0;

    /* Get a pointer to the RTA header */
    pRtaHdr= (ICMPRTAHDR *)pIcHdr->Data;

    /* Validate Header */
    pRtaHdr->NumAddr   =  1;
    pRtaHdr->Size      =  2;
    pRtaHdr->Lifetime     =  HNC16(Life);
    WrNet32( &pRtaHdr->rta[0].IPAddr, IPAddr );
    WrNet32( &pRtaHdr->rta[0].Pref, HNC32(Pref) );

    /* Checksum the ICMP header */
    ICMPChecksum( pIcHdr, ICMPLen );

    /* Get a pointer to the IP header - the packet is already Layer3 */
    pIpHdr  = (IPHDR *)pb;

    /* Set some IP header stuff */
    pIpHdr->VerLen   = 0x45;      /* Required when creating own header */
    pIpHdr->Ttl      = ICMP_TTL;  /* Use default ICMP Ttl */
    pIpHdr->Tos      = 0;         /* Rcmd'd for ICMP errors */
    pIpHdr->Protocol = 1;         /* ICMP */

    WrNet32( &pIpHdr->IPSrc, IPAddr );
    WrNet32( &pIpHdr->IPDst, INADDR_BROADCAST );

    /* Set the fragment valid data size */
    pPkt->ValidLen = ICMPLen+IPHDR_SIZE;

    /* Since we know the egress IF, may as well tell IP */
    pPkt->hIFTx = hIFTx;

    /* Send the packet */
    IPTxPacket( pPkt, FLG_IPTX_BROADCAST );
}

