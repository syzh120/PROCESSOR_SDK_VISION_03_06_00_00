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
 * ======== proxy.c ========
 *
 * Network Address Translation
 *
 */

#include <stkmain.h>
#ifdef _INCLUDE_NAT_CODE
#include "nat.h"
#include "proxy.h"

/* Head of linked lists for proxies */
static PROXY *pProxy[4] = { 0, 0, 0, 0 };

static HANDLE ProxyFind( uint ProxyMode, UINT16 Port );
static void   ProxyComplete();


/* Static "current" values. We get away with this since PROXY is */
/* single threaded. */

static PROXYENTRY *ppeCurrent;
static PBM_Pkt    *pPktCurrent;
static int        ChecksumCurrent;
static IPHDR      *pIpHdrCurrent;
static uint       ModeCurrent;
static uint       Altered;

/*-------------------------------------------------------------------- */
/* ProxyNew - Create a PROXY */

/* ProxyType      - NatMode */
/* Protocol       - Protocol (TCP or UDP) */
/* Port           - TCP/UDP Port */
/* IPTarget       - Target IP of Local Machine (for mapping) */
/* pfnEnableCb    - Callback for enabling new proxy */
/* pfnTxCb        - Callback for Local to Foreign packet */
/* pfnRxCb        - Callback for Foreign to Local packet */

/*-------------------------------------------------------------------- */
HANDLE ProxyNew( uint NatMode, UINT8 Protocol, UINT16 Port, IPN IPTarget,
                 int (*pfnEnableCb)( NATINFO *, uint ),
                 int (*pfnTxCb)( NATINFO *, IPHDR * ),
                 int (*pfnRxCb)( NATINFO *, IPHDR * ) )
{
    PROXY    *pp;
    PROXY    **ppProxList;

    /* Check for illegal arguments */
    if( !Port || (NatMode > 1) )
        return(0);

    /* Adjust Nat Mode by protocol */
    if( Protocol == IPPROTO_UDP )
        NatMode += PROXY_OFFSET_UDP;
    else if( Protocol != IPPROTO_TCP )
        return(0);

    /* Can't proxy reserved port range */
    if( Port >= SOCK_RESPORT_FIRST && Port <= SOCK_RESPORT_LAST )
        return(0);

    /* If a proxy already exists, delete it */
    if( (pp = ProxyFind( NatMode, Port )) != 0 )
        ProxyFree( pp );

    if( !(pp = mmAlloc(sizeof(PROXY))) )
    {
        DbgPrintf(DBG_WARN,"ProxyNew: OOM");
        NotifyLowResource();
        return(0);
    }

    /* Initialize type */
    pp->Type = HTYPE_PROXY;

    /* Set information */
    pp->NatMode     = NatMode;
    pp->Port        = Port;
    pp->IPTarget    = IPTarget;
    pp->pfnEnableCb = pfnEnableCb;
    pp->pfnTxCb     = pfnTxCb;
    pp->pfnRxCb     = pfnRxCb;

    /* Init our forward pointer */
    pp->pNext     = 0;

    /* Get the list pointer */
    ppProxList = &pProxy[NatMode];

    /* If there's a "next" entry, point to it and point it */
    /* back to us */
    if( *ppProxList )
    {
        pp->pNext         = *ppProxList;
        pp->pNext->ppPrev = &pp->pNext;
    }

    /* Put us at head of the list */
    *ppProxList = pp;
    pp->ppPrev  = ppProxList;

    return( pp );
}

/*-------------------------------------------------------------------- */
/* ProxyFree - Free a proxy entry */
/*-------------------------------------------------------------------- */
void ProxyFree( HANDLE hProxy )
{
    PROXY *pp = (PROXY *)hProxy;

#ifdef _STRONG_CHECKING
    if( pp->Type != HTYPE_PROXY )
    {
        DbgPrintf(DBG_ERROR,"ProxyFree: HTYPE %04x",pp->Type);
        return;
    }
#endif

    /* Remove Entry from linked list */
    *pp->ppPrev = pp->pNext;
    if( pp->pNext )
        pp->pNext->ppPrev = pp->ppPrev;

    /* Zap it */
    pp->Type = 0;
    mmFree( pp );
}

/*-------------------------------------------------------------------- */
/* ProxyFind - Find a proxy entry from Type and Port */
/*-------------------------------------------------------------------- */
static HANDLE ProxyFind( uint ProxyMode, UINT16 Port )
{
    PROXY *pp;

    /* Quick error check */
    if( ProxyMode > 3 )
        return(0);

    /* Get the first entry */
    pp = pProxy[ProxyMode];

    /* Search */
    while( pp )
    {
        if( pp->Port == Port )
            return( pp );
        pp = pp->pNext;
    }

    return(0);
}

/*-------------------------------------------------------------------- */
/* ProxyEntrySpawn - Create New Proxy Entry */
/*-------------------------------------------------------------------- */
int ProxyEntrySpawn( uint NatMode, UINT8 Protocol, UINT16 Port,
                     HANDLE *phProxyEntry, IPN *pIPLocal )
{
    PROXY *pp;
    PROXYENTRY *ppe;

    /* Quick error check */
    if( NatMode > 1 )
        return(0);

    /* Adjust Nat Mode by protocol */
    if( Protocol == IPPROTO_UDP )
        NatMode += PROXY_OFFSET_UDP;
    else if( Protocol != IPPROTO_TCP )
        return(0);

    /* Get the first entry */
    pp = pProxy[NatMode];

    /* Search */
    while( pp )
    {
        if( pp->Port == Port )
            goto Found;
        pp = pp->pNext;
    }
    return(0);

Found:
    if( !(ppe = mmAlloc(sizeof(PROXYENTRY))) )
    {
        DbgPrintf(DBG_WARN,"ProxyEntryNew: OOM");
        NotifyLowResource();
        return(0);
    }

    mmZeroInit( ppe, sizeof(PROXYENTRY) );

    /* Initialize type */
    ppe->Type = HTYPE_PROXYENTRY;

    /* Set information */
    ppe->pfnEnableCb = pp->pfnEnableCb;
    ppe->pfnTxCb = pp->pfnTxCb;
    ppe->pfnRxCb = pp->pfnRxCb;

    /* If the entry handle pointer is valid, return it */
    if( phProxyEntry )
        *phProxyEntry = ppe;

    /* If the IP pointer is valid, return the IPDst */
    if( pIPLocal )
        *pIPLocal = pp->IPTarget;

    /* Return success */
    return( 1 );
}

/*-------------------------------------------------------------------- */
/* ProxyEnable */
/* Called to Enable or Disable a Proxy */
/*-------------------------------------------------------------------- */
int ProxyEnable( NATINFO *pni, uint Enable )
{
    /* Get the current proxy entry */
    ppeCurrent = (PROXYENTRY *)pni->hProxyEntry;

    /* Call user callback */
    if( ppeCurrent->pfnEnableCb )
        return( ppeCurrent->pfnEnableCb( pni, Enable ) );

    /* If no callback we always enable */
    return(1);
}

/*-------------------------------------------------------------------- */
/* ProxyTx */
/* Called to modify a proxy TX packet */
/*-------------------------------------------------------------------- */
void ProxyTx( NATINFO *pni, PBM_Pkt *pPkt, IPHDR *pIpHdr )
{
    ModeCurrent = NAT_MODE_TX;

    /* Save the current packet and header */
    pPktCurrent   = pPkt;
    pIpHdrCurrent = pIpHdr;

    /* Assume we don't rechecksum the entire packet */
    ChecksumCurrent = 1;
    Altered         = 0;

    /* Get the current proxy entry */
    ppeCurrent = (PROXYENTRY *)pni->hProxyEntry;

    /* Call user callback */
    if( ppeCurrent->pfnTxCb )
        if( !ppeCurrent->pfnTxCb( pni, pIpHdr ) )
        {
            PBM_free( pPktCurrent );
            return;
        }

    /* At this point, the globals variables hold information about what */
    /* could actually be a new packet (if the size changed). Thus, we */
    /* can't do anything more here */
    ProxyComplete();
}

/*-------------------------------------------------------------------- */
/* ProxyRx */
/* Called to modify a proxy RX packet */
/*-------------------------------------------------------------------- */
void ProxyRx( NATINFO *pni, PBM_Pkt *pPkt, IPHDR *pIpHdr )
{
    ModeCurrent = NAT_MODE_RX;

    /* Save the current packet and header */
    pPktCurrent   = pPkt;
    pIpHdrCurrent = pIpHdr;

    /* Assume we don't rechecksum the entire packet */
    ChecksumCurrent = 1;
    Altered         = 0;

    /* Get the current proxy entry */
    ppeCurrent = (PROXYENTRY *)pni->hProxyEntry;

    /* Call user callback */
    if( ppeCurrent->pfnRxCb )
        if( !ppeCurrent->pfnRxCb( pni, pIpHdr ) )
        {
            PBM_free( pPktCurrent );
            return;
        }

    /* At this point, the global variables hold information about what */
    /* could actually be a new packet (if the size changed). Thus, we */
    /* can't do anything more here */
    ProxyComplete();
}

/*-------------------------------------------------------------------- */
/* ProxyComplete */
/* This function is called once all packet modifications are */
/* complete. When using TCP, the TCP sequences are adjusted. */
/* Plus the packet checksums may need to be recalculated. */
/*-------------------------------------------------------------------- */
static void ProxyComplete()
{
    uint    IPHdrLen;
    UINT16  Length;

    /* Get the length of the IP header */
    IPHdrLen = (pIpHdrCurrent->VerLen & 0xf) * 4;

    /* Get the length of the payload */
    Length =  HNC16(pIpHdrCurrent->TotalLen);
    Length -= IPHdrLen;
    Length =  HNC16(Length);

    /* Do the easy case first: UDP */
    if( pIpHdrCurrent->Protocol == IPPROTO_UDP )
    {
        UDPHDR  *pUdpHdr;

        /* Get UDP packet header */
        pUdpHdr = (UDPHDR *)(((UINT8 *)pIpHdrCurrent) + IPHdrLen);

        /* If the UDP checksum is invalid, redo it */
        if( !ChecksumCurrent )
        {
            /* Checksum Header */
            upseudo.IPSrc  = RdNet32( &pIpHdrCurrent->IPSrc );
            upseudo.IPDst  = RdNet32( &pIpHdrCurrent->IPDst );
            upseudo.Null     = 0;
            upseudo.Protocol = 17;
            upseudo.Length   = Length;
            UdpChecksum( pUdpHdr );
        }
    }
    /* Else we're TCP */
    else
    {
        TCPHDR  *pTcpHdr;
        UINT32  Seq,Ack,NewSeq,NewAck;
        int     offack,offseq;

        /* Get TCP packet header */
        pTcpHdr = (TCPHDR *)(((UINT8 *)pIpHdrCurrent) + IPHdrLen);

        /* Get Seq and Ack */
        Seq = RdNet32( &pTcpHdr->Seq );
        NewSeq = HNC32(Seq);
        Ack = RdNet32( &pTcpHdr->Ack );
        NewAck = HNC32(Ack);

        /* Adjust sequencing */
        if( ModeCurrent == NAT_MODE_TX )
        {
            if( SEQ_LEQ( NewSeq, ppeCurrent->TxSeqThresh ) )
                offseq = ppeCurrent->TxOffset1;
            else
                offseq = ppeCurrent->TxOffset2;
            if( SEQ_LEQ( NewAck, ppeCurrent->RxSeqThresh ) )
                offack = ppeCurrent->RxOffset1;
            else
                offack = ppeCurrent->RxOffset2;
        }
        else
        {
            if( SEQ_LEQ( NewAck, ppeCurrent->TxSeqThresh ) )
                offack = ppeCurrent->TxOffset1;
            else
                offack = ppeCurrent->TxOffset2;
            if( SEQ_LEQ( NewSeq, ppeCurrent->RxSeqThresh ) )
                offseq = ppeCurrent->RxOffset1;
            else
                offseq = ppeCurrent->RxOffset2;
        }

        /* If the sequence numbers have changed, replace them */
        if( offseq != 0 || offack != 0 )
        {
            /* Replace the SEQ and ACK values */
            NewSeq = (UINT32)((INT32)NewSeq+(INT32)offseq);
            NewSeq = HNC32(NewSeq);
            NewAck = (UINT32)((INT32)NewAck-(INT32)offack);
            NewAck = HNC32(NewAck);

            WrNet32( &pTcpHdr->Seq, NewSeq );
            WrNet32( &pTcpHdr->Ack, NewAck );

            ChecksumCurrent = 0;
        }

        /* If the TCP checksum is invalid, redo it */
        if( !ChecksumCurrent )
        {
            /* Checksum Header */
            tpseudo.IPSrc  = RdNet32( &pIpHdrCurrent->IPSrc );
            tpseudo.IPDst  = RdNet32( &pIpHdrCurrent->IPDst );
            tpseudo.Null     = 0;
            tpseudo.Protocol = 6;
            tpseudo.Length   = Length;
            TcpChecksum( pTcpHdr );
        }
    }

    /* Send packet */
    IPTxPacket( pPktCurrent, FLG_IPTX_FORWARDING );
}

/*-------------------------------------------------------------------- */
/* ProxyPacketMod */
/* This function is called by the USER to modify a packet */
/*-------------------------------------------------------------------- */
IPHDR *ProxyPacketMod( uint Offset, uint OldSize, uint NewSize, UINT8 *pData )
{
    /* First, adjust the packet */

    /* If the size is the same, its easy */
    if( NewSize == OldSize )
    {
        if( OldSize )
            mmCopy( ((UINT8 *)pIpHdrCurrent)+Offset, pData, OldSize );
    }
    /* If the size changes, we'll copy the entire fragment */
    else
    {
        PBM_Pkt *pPkt;
        uint    OldValid;
        UINT8   *pNewBuf;

        /* Remember the original valid size */
        OldValid = pPktCurrent->ValidLen;

        /* Munge valid to reflect target size */
        pPktCurrent->ValidLen += NewSize - OldSize;

        /* Copy the packet */
        pPkt = PBM_copy( pPktCurrent );

        /* Fix the size */
        pPktCurrent->ValidLen = OldValid;

        /* If we didn't get a copy, punt */
        if( !pPkt )
            return( pIpHdrCurrent );

        /* We know the copied packet is "ok" up to the user */
        /* specified offet. If may be bad after that. First */
        /* copy the user data */
        pNewBuf = pPkt->pDataBuffer + pPkt->DataOffset;

        if( NewSize )
            mmCopy( pNewBuf + Offset, pData, NewSize );

        /* Now copy the remaining data from the old packet */
        if( OldValid > (Offset+OldSize) )
        {
            mmCopy( pNewBuf + Offset + NewSize,
                    ((UINT8 *)pIpHdrCurrent) + Offset + OldSize,
                    OldValid - Offset - OldSize );
        }

        /* The valid size of the new pkt is already correct. */

        /* Free the old pkt */
        PBM_free( pPktCurrent );

        /* Sub in the new pkt */
        pPktCurrent = pPkt;
        pIpHdrCurrent = (IPHDR *)pNewBuf;

        /* Adjust the packet size in the IP header */
        pIpHdrCurrent->TotalLen = HNC16((UINT16)(pPktCurrent->ValidLen));

        /* If TCP, adjust sequencing info */
        if( pIpHdrCurrent->Protocol == IPPROTO_TCP )
        {
            UINT16 IPHdrLen;
            TCPHDR *pTcpHdr;
            uint   Off;

            IPHdrLen = (pIpHdrCurrent->VerLen & 0xf) * 4;
            pTcpHdr = (TCPHDR *)(((UINT8 *)pIpHdrCurrent) + IPHdrLen);

            /* Get the offset into the TCP payload */
            Off =  pTcpHdr->HdrLen >> 2;
            Off += IPHdrLen;

            /* See if alteration was in TCP payload */
            if( Offset >= Off )
            {
                UINT32  Seq;

                /* Start offset from start of TCP payload */
                Off = Offset - Off;

                /* Get the sequenct */
                Seq = RdNet32( &pTcpHdr->Seq );
                Seq = HNC32(Seq);

                Seq += (UINT32)Off;

                if( ModeCurrent == NAT_MODE_TX )
                {
                    /* Track the first alteration in this packet */
                    if( !Altered )
                    {
                        /* If this packet preceeds an old alteration, */
                        /* then we resync the offset in hopes it will be OK */
                        if( SEQ_LEQ( Seq, ppeCurrent->TxSeqThresh ) )
                            ppeCurrent->TxOffset2 = ppeCurrent->TxOffset1;
                        else
                            ppeCurrent->TxOffset1 = ppeCurrent->TxOffset2;
                        ppeCurrent->TxSeqThresh = Seq;
                    }
                    ppeCurrent->TxOffset2 += (NewSize - OldSize);
                }
                else
                {
                    /* Track the first alteration in this packet */
                    if( !Altered )
                    {
                        /* If this packet preceeds an old alteration, */
                        /* then we resync the offset in hopes it will be OK */
                        if( SEQ_LEQ( Seq, ppeCurrent->RxSeqThresh ) )
                            ppeCurrent->RxOffset2 = ppeCurrent->RxOffset1;
                        else
                            ppeCurrent->RxOffset1 = ppeCurrent->RxOffset2;
                        ppeCurrent->RxSeqThresh = Seq;
                    }
                    ppeCurrent->RxOffset2 += (NewSize - OldSize);
                }
                Altered = 1;
            }
        }
    }

    ChecksumCurrent = 0;
    return( pIpHdrCurrent );
}

#endif
