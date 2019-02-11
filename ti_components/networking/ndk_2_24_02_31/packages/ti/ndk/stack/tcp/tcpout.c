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
 * ======== tcpout.c ========
 *
 * TCP out functions
 *
 */

#include <stkmain.h>
#include "tcp.h"

/*#define TCP_DEBUG */

/* TCP Flags Based on State */
static UINT8 tcp_outflags[] = {
        TCP_RST | TCP_ACK,      /* CLOSED */
        0,                      /* LISTEN */
        TCP_SYN,                /* SYNSENT */
        TCP_SYN | TCP_ACK,      /* SYNRCVD */
        TCP_ACK,                /* ESTAB */
        TCP_ACK,                /* CLOSEWAIT */
        TCP_FIN|TCP_ACK,        /* FINWAIT1 */
        TCP_FIN|TCP_ACK,        /* CLOSING */
        TCP_FIN|TCP_ACK,        /* LASTACK */
        TCP_ACK,                /* FINWAIT2 */
        TCP_ACK };              /* TIMEWAIT */

/*-------------------------------------------------------------------- */
/* getNextHole */
/* Get the next unSACK'd hole in the SACK Tx Table */
/*-------------------------------------------------------------------- */
static inline UINT32 getNextHole(TCPPROT *pt, UINT32* pNextHole)
{
    SACK_TxEntry* pEntry;

    if (pt->pSack->rexmtIndex == 0xFFFFFFFF) {
        pt->pSack->rexmtIndex = pt->pSack->txTableTop;
    }
    else {
        pt->pSack->rexmtIndex++;
        pt->pSack->rexmtIndex &= (SACK_TABLE_SIZE - 1);
    }

    while (pt->pSack->rexmtIndex != pt->pSack->txTableBottom) {
        pEntry = &pt->pSack->SACK_txTable[pt->pSack->rexmtIndex];
        if (pEntry->sacked == 0) {
            *pNextHole = pEntry->leftEdge;
            return (1);
        }
        pt->pSack->rexmtIndex++;
        pt->pSack->rexmtIndex &= (SACK_TABLE_SIZE - 1);
    }

    return (0);
}

/*-------------------------------------------------------------------- */
/* addSegmentSackTxTable() */
/* add transmitted segment into SACK Tx Table */
/*-------------------------------------------------------------------- */
static inline void addSegmentSackTxTable(TCPPROT* pt, UINT32 segmentLen)
{
    SACK_TxEntry* pEntry;

    pEntry = &pt->pSack->SACK_txTable[pt->pSack->txTableBottom];
    pEntry->leftEdge = pt->snd_nxt;
    pEntry->rightEdge = pt->snd_nxt + segmentLen - 1;
    pEntry->sacked = 0;
    pt->pSack->txTableBottom++;
    pt->pSack->txTableBottom &= (SACK_TABLE_SIZE - 1);
}

/*-------------------------------------------------------------------- */
/* addSackOption() */
/* add SACK option entries to TCP header */
/*-------------------------------------------------------------------- */
static inline UINT32 addSackOption(TCPPROT* pt, UINT8* optBuf,
                                   UINT32 optLen)
{
    TCPREASM* pCurrent;
    SACK_RcvEntry* pEntry;
    SACK_RcvEntry* pEntry2;
    UINT32 i;
    UINT32 j;
    UINT32 temp;
    UINT32 changed;
    UINT32 sackOptLenIndex;
    UINT32* sackBlock;

    /* 
     *  Make sure that there is enough space for at list one SACK option 
     *  2(NOP) + 1(SACK Option) + 1(Option Length) + 4(LE) + 4(RE) = 12
     *
     */
    if ((optLen + 12) > TCP_MAX_OPTIONS) {
        return (optLen);
    }

    /* First build the received blocks table */
    pCurrent = pt->pReasm;
    pEntry = &pt->pSack->SACK_rcvTable[0];
    pEntry->leftEdge = pCurrent->seq;
    pEntry->rightEdge = pCurrent->end_seq;
    pEntry->arrival = pCurrent->arrival;
    pt->pSack->rcvTableBottom = 1;
    pt->pSack->rcvTableTop = 0;
    i = 0;
    pCurrent = pCurrent->pNext;
    while (pCurrent && 
        pt->pSack->rcvTableBottom < SACK_TABLE_SIZE) {
        while (i != pt->pSack->rcvTableBottom) {
            pEntry = &pt->pSack->SACK_rcvTable[i];
            if (SEQ_GEQ(pCurrent->seq, pEntry->leftEdge) &&
                SEQ_LEQ(pCurrent->seq, (pEntry->rightEdge + 1))) {
                if (SEQ_GT(pCurrent->end_seq, (pEntry->rightEdge + 1))) {
                    pEntry->rightEdge = pCurrent->end_seq;
                    if (SEQ_GT(pCurrent->arrival, pEntry->arrival)) {
                        pEntry->arrival = pCurrent->arrival;
                    }
                }
            } else 
            if (SEQ_LEQ(pCurrent->end_seq, pEntry->rightEdge) &&
                SEQ_GEQ(pCurrent->end_seq, (pEntry->leftEdge - 1))) {
                if (SEQ_LT(pCurrent->seq, (pEntry->leftEdge - 1))) {
                    pEntry->leftEdge = pCurrent->seq;
                    if (SEQ_GT(pCurrent->arrival, pEntry->arrival)) {
                        pEntry->arrival = pCurrent->arrival;
                    }
                }
            } else {
                pEntry = &pt->pSack->SACK_rcvTable[pt->pSack->rcvTableBottom]; 
                pEntry->leftEdge = pCurrent->seq;
                pEntry->rightEdge = pCurrent->end_seq;
                pEntry->arrival = pCurrent->arrival;
                pt->pSack->rcvTableBottom++;
            }
            i++;
        }
        pCurrent = pCurrent->pNext;
    }

    /* If there are more than one entry, sort them on arrival order */
    if (pt->pSack->rcvTableBottom > 1) {
        do {
            i = pt->pSack->rcvTableTop;
            j = i + 1;
            changed = 0;
            while (j != pt->pSack->rcvTableBottom) {
                pEntry = &pt->pSack->SACK_rcvTable[i];
                pEntry2 = &pt->pSack->SACK_rcvTable[j];
                if (SEQ_GT(pEntry2->arrival, pEntry->arrival)) {
                    changed = 1;
                    temp = pEntry->leftEdge;
                    pEntry->leftEdge = pEntry2->leftEdge;
                    pEntry2->leftEdge = temp;
                    temp = pEntry->rightEdge;
                    pEntry->rightEdge = pEntry2->rightEdge;
                    pEntry2->rightEdge = temp;
                    temp = pEntry->arrival;
                    pEntry->arrival = pEntry2->arrival;
                    pEntry2->arrival = temp;
                }
                i = j;
                j++;
            }
        } while (changed);
    }

    /* store as many as possible SACK options */
    optBuf[optLen++] = TCPOPT_NOP;
    optBuf[optLen++] = TCPOPT_NOP;
    optBuf[optLen++] = TCPOPT_SACK;
    sackOptLenIndex = optLen++; /* store length information later */
    sackBlock = (UINT32*) &optBuf[optLen];
    i = pt->pSack->rcvTableTop;
    while (optLen < TCP_MAX_OPTIONS && i !=  pt->pSack->rcvTableBottom) {
        pEntry = &pt->pSack->SACK_rcvTable[i];
        *sackBlock++ = HNC32(pEntry->leftEdge);
        *sackBlock++ = HNC32(pEntry->rightEdge);
        optLen += SACK_OPTION_SIZE;
        i++;
    }
    optBuf[sackOptLenIndex] = (optLen - sackOptLenIndex - 1) + 2; 

    return (optLen);
}

/*-------------------------------------------------------------------- */
/* TcpOutput() */
/* Called when a TCP may need to be sent */
/*-------------------------------------------------------------------- */
int TcpOutput( TCPPROT *pt )
{
    int         sendmore, error = 0;
    INT32       mss,off,sndwin,len,optlen,tmp,TxbTotal,advwin;
    UINT32      dwTmp;
    UINT8       flags;
    UINT8       opt[TCP_MAX_OPTIONS];
    PBM_Pkt     *pPkt;
    uint        IPHdrLen;
    UINT8       *pPayload;
    TCPHDR      *pTcpHdr;

    UINT32      savedSndNxt;       /* RFC 2018 - SACK  */
    UINT32      sackRexmitLen = 0; /* RFC 2018 - SACK */

    /* Get our receive window (function should not return <0, but */
    /* check anyway). We also know our window can not shrink. */
    /* (We can not reduce the size of an allocated receive buffer). */
    /* Since we're not re-entrant, we only need to do this once */
    advwin = SBGetSpace( pt->hSBRx );
    if( advwin < 0 )
        advwin = 0;
    else if( advwin > TCP_MAXWIN )
        advwin = TCP_MAXWIN;

sendagain:

    sendmore = 0;

    /* RFC2018 - Check if it is for SACK retransmission */
    if (pt->sackActive && pt->pSack->rexmtTimeout) {
        savedSndNxt = pt->snd_nxt;                  
        if (!getNextHole(pt, &pt->snd_nxt)) {
            pt->snd_nxt = savedSndNxt;
            return (0);
        }
    }

    /* Get the total bytes left to send */
    /* We'll use this value several times */
    TxbTotal = SBGetTotal( pt->hSBTx );

    /* Get the mss */
    /* We compare the uint mss to UINT32 values quite a bit */
    mss = (INT32)pt->t_mss;

    /* Determine length of data to be transmitted */
    /* If there are some critical flags set, send */

    /* If we've been idle for longer than 4 times the current retransmit time, */
    /* go back to "slow start" by resetting the congestion window */
    if( pt->snd_una==pt->snd_max && pt->t_tidle > (pt->t_trtx<<2) )
        pt->snd_cwnd = mss;

    /* off = Offset from beginning of send buffer to the first byte to send */
    /* sndwin = Min of adverstised or congestion window */
    off = pt->snd_nxt - pt->snd_una;
    sndwin = (pt->snd_wnd < pt->snd_cwnd) ? pt->snd_wnd : pt->snd_cwnd;

    /* Get default TCP flags based on the current state */
    flags = tcp_outflags[ pt->t_state ];

    /* Check for persist condition */
    if( pt->t_flags & TF_PERSIST )
    {
        /* If the window is still closed, open it window 1 byte */
        /* else reset the persist state. */
        if( !sndwin )
        {
            sndwin = 1;

            /* If there is more data to send, make sure FIN is not set */
            if( off < TxbTotal )
                flags &= ~TCP_FIN;
        }
        else
        {
            /* Clear Persist */
            pt->t_flags &= ~TF_PERSIST;
            pt->TicksPersist = 0;
            pt->t_rtxindex   = 0;

            /* Set NEEDOUTPUT to use what window is available */
            /* Otherwise we may decide not to send again! */
            pt->t_flags |= TF_NEEDOUTPUT;
        }
    }

    /* RFC2018 - SACK  */
    if (pt->sackActive && pt->pSack->rexmtTimeout) {
        SACK_TxEntry* pEntry;

        pEntry = &pt->pSack->SACK_txTable[pt->pSack->rexmtIndex];
            len = pEntry->rightEdge - pEntry->leftEdge + 1;
    }
    else {
        /* Set len = the max number of bytes we can send this time */
        /* This is bound by the current send window, or the number of bytes */
        /* we have left to send. */
        if( sndwin < TxbTotal )
            len = sndwin - off;
        else
            len = TxbTotal - off;

        /* Check for a problem (len < 0) - we sent too much */
        if( len < 0 )
        {
            len = 0;

            /* We are either in a normal FIN wait state: */
            /*         (sndwin < off < TxbTotal) , */
            /* or our send window shrank. If the window shrank to zero, */
            /* back up to last ACK'd data and turn off Rexmt. This will */
            /* cause us to drop into PERSIST if we don't send. */
            if( !sndwin )
            {
                pt->snd_nxt = pt->snd_una;
                pt->TicksRexmt = 0;
            }
        }

        /* 
         * See if we have to bust up our send into multiple segments
         * this pass
         */
        if( len > mss )
        {
            len = mss;
            sendmore = 1;
        }
    }

    /* Clear any pending FIN flag if this isn't the last data to go */
    if( SEQ_LT( pt->snd_nxt + len, pt->snd_una + TxbTotal ) )
        flags &= ~TCP_FIN;

    /* Check for various send conditions */
    if( len )
    {
        /* If there is no data currently outstanding, or if all delays are */
        /* disabled, send regardless of any other condition. */
        if( (pt->snd_nxt == pt->snd_una) || (pt->t_flags & TF_NODELAY) )
            goto send;

        /* Send if we have a full segment */
        /* Send if we have at least half the peer's max window */
        /* Send if we're emptying out the send buffer and NOPUSH is not set */
        /* Send if forced output (from persist, ENOBUFS, or must ACK) */
        /* Send on a retransmit (here snd_nxt was set back to snd_una) */
        if( len==mss || len>=(INT32)(pt->snd_wnd_max/2) ||
                ( !(pt->t_flags & TF_NOPUSH) && ((len+off) >= TxbTotal) ) ||
                ( pt->t_flags & (TF_PERSIST|TF_NEEDOUTPUT|TF_ACKNOW) ) ||
                ( SEQ_LT( pt->snd_nxt, pt->snd_max ) ) )
            goto send;
    }

    /* Send if we must ACK (ACK_NOW), or */
    /* if we have urgent data, or */
    /* if we are sending the SYN or RST flag */
    if( (pt->t_flags&TF_ACKNOW) ||
            SEQ_GT(pt->snd_up,pt->snd_una) ||
            (flags&(TCP_SYN|TCP_RST))  )
        goto send;

    /* Check for Window Update Conditions */

    /* Get the number of bytes that our receive window has opened */
    if( (tmp = advwin-(pt->rcv_adv-pt->rcv_nxt)) > 0 )
    {
        /* If the window has opened by 2 segments, advertise new window */
        if( tmp >= 2 * mss )
            goto send;

        /* If the window has opened by half our receive buffer, advertise */
        if( tmp >= SBGetMax(pt->hSBRx)/2 )
            goto send;
    }

    /* Lastly, we'll send if FIN is set and we haven't sent it yet, or */
    /* if we're here because of a re-transmit on the FIN packet */
    if( (flags & TCP_FIN) &&
            ( !(pt->t_flags & TF_SENTFIN) || (pt->snd_nxt == pt->snd_una) ) )
        goto send;

    /* If we get here, we were unable to send, or decided not to */
    /* send. We also know that we are not in the PERSIST state. */
    /* If there is data to send and there is no retransmit in progress, */
    /* then we'll go into PERSIST mode now to wait for a larger window. */
    if( TxbTotal && !pt->TicksRexmt )
    {
        pt->t_rtxindex = 0;     /* Reset backoff for initial persist */
        TcpSetPersist( pt );    /* Initialize Persist */
    }

    /* RFC2018 - SACK - If SACK retransmitting, restore snd_nxt */
    if (pt->sackActive && pt->pSack->rexmtTimeout) {
        pt->snd_nxt = savedSndNxt;
    }

    return(0);

send:
    /* If we get here, we're going to send something */

    optlen = 0;

    /* If SYN is being sent we'll also include MAXSEG,  */
    /* and if SACK is permitted, SACK-permitted is added */
    if( flags & TCP_SYN )
    {
        /* Reset sending sequence number to our assigned ISS */
        pt->snd_nxt = pt->iss;

        /* Validate the route and the route metrics for this socket. */
        /* This will return the MSS we advertise, but not the one */
        /* we actually restrict ourselves to. */
        tmp = TcpValidateMetrics( pt, 0 );

        /* Add in options if not disabled */
        if( !(pt->t_flags & TF_NOOPT) )
        {
            /* Send our max seg size */
            opt[0] = TCPOPT_MAXSEG;     /* TCPOPT_MAXSEG */
            opt[1] = TCPOLEN_MAXSEG;    /* MAXSEG Size */
            opt[2] = (UINT8)(tmp >> 8);
            opt[3] = (UINT8)(tmp);
            optlen += 4;

            /* RFC 2018 - SACK */
            if (pt->sackActive) {
                /* Add SACK permit option */
                opt[optlen++] = TCPOPT_SACKPERMITTED;  /* TCPOPT_SACKPEMIT */
                opt[optlen++] = TCPOPLEN_SACKPERMITTED; /* SACK Permit size */
                opt[optlen++] = TCPOPT_NOP;
                opt[optlen++] = TCPOPT_NOP;
            }
        }

        /* Adjust send length to make room for options */
        if( len > mss - optlen)
        {
            len = mss - optlen;
            sendmore = 1;
        }
    }

    /* RFC 2018 - SACK */
    if (pt->pReasm && pt->sackActive) {
        optlen = addSackOption(pt, opt, optlen);
        if ( len > mss - optlen) {
            len = mss - optlen;
            sendmore = 1;
        }
    }

    /* Create the packet */
    /* Payload = len */
    /* Reserve = TCPHDR_SIZE + optlen */
    if( !(pPkt = SockCreatePacket( pt->hSock, (uint)len+
                                   TCPHDR_SIZE+(uint)optlen )) )
    {
        /* RFC2018 - SACK - If SACK retransmitting, restore snd_nxt */
        if (pt->sackActive && pt->pSack->rexmtTimeout) {
            pt->snd_nxt = savedSndNxt;
        }

        /* Out of buffers condition */
        pt->t_flags |= TF_NEEDOUTPUT;
        tcps.SndNoBufs++;
        if( pt->t_state != TSTATE_ESTAB )
            return( ENOBUFS );
        else
            return( 0 );
    }

    /* Get the IP header len */
    IPHdrLen = pPkt->IpHdrLen;

    /* Assign a TCP header pointer */
    pTcpHdr = (TCPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset + IPHdrLen);

    /* Get pointer to payload */
    pPayload  = pPkt->pDataBuffer + pPkt->DataOffset +
                IPHdrLen + TCPHDR_SIZE + optlen;

    /* Build the TCP Packet */
    if( len )
    {
        /* We're Sending Data */

        /* Update the send type stats */
        if( pt->t_flags & TF_PERSIST )
            tcps.SndProbe++;          /* Window probes sent */
        else if( SEQ_LT(pt->snd_nxt,pt->snd_max) )
        {
            tcps.SndRexmitPack++;     /* Retransmit packets */
            tcps.SndRexmitByte+=len;  /* Retransmit bytes */
        }
        else
        {
            tcps.SndPack++;           /* Send packets */
            tcps.SndByte+=len;        /* Send bytes */
        }

        /* Copy in the payload (with PEEK flag set to "1") */
        SBRead( pt->hSBTx, len, off, pPayload, 0, 0, 1 );

        /* RCF 2018 - SACK */
                if (pt->sackActive && !pt->pSack->rexmtTimeout) {
                    addSegmentSackTxTable(pt, len); 
                }

        /* If sending the last bit of data, set the PSH flag */
        if( (len+off) == TxbTotal )
            flags |= TCP_PSH;
    }
    else
    {
        /* We're Not Sending Data */

        /* Update the send type stats */
        if( pt->t_flags & (TF_ACKNOW|TF_DELACK) )
            tcps.SndAcks++;           /* Peek ACKS sent */
        else if( flags & (TCP_SYN | TCP_FIN | TCP_RST) )
            tcps.SndCtrl++;           /* Control packets sent */
        else if( SEQ_GT( pt->snd_up, pt->snd_una ) )
            tcps.SndUrg++;            /* URG only packets else */
        else
            tcps.SndWinUp++;          /* Window update packets */
    }

    /* Fill in TCP Header */

    /* Set some TCP header stuff */
    pTcpHdr->HdrLen  = (UINT8)(((TCPHDR_SIZE+optlen)>>2)<<4);
    pTcpHdr->SrcPort = SockGetLPort(pt->hSock);
    pTcpHdr->DstPort = SockGetFPort(pt->hSock);

    /* Fill in Sequence Numbers */

    /* If resending a FIN make sure to use to old sequence number */
    if((flags&TCP_FIN) && (pt->t_flags&TF_SENTFIN) && (pt->snd_nxt==pt->snd_max))
        pt->snd_nxt--;

    /* Since we may have resent data, snd_nxt can be less than snd_max. If */
    /* we're sending data or SYN/FIN flag, we'll use snd_nxt. For status */
    /* updates, we use snd_max. */
    if( len || (flags&(TCP_SYN|TCP_FIN)) )
        dwTmp = HNC32(pt->snd_nxt);
    else
        dwTmp = HNC32(pt->snd_max);

    WrNet32( &pTcpHdr->Seq, dwTmp );

#ifdef TCP_DEBUG
    DbgPrintf(DBG_INFO, "TcpOutput: Send %04X, F=%04X, S=%08X, ", (int)pt, flags,
            HNC32(dwTmp));
    DbgPrintf(DBG_INFO, "TcpOutput: A=%08X, ", pt->rcv_nxt);
#endif

    dwTmp = HNC32(pt->rcv_nxt);
    WrNet32( &pTcpHdr->Ack, dwTmp );

    /* Copy in TCP header options */
    if( optlen )
        mmCopy( pTcpHdr->Options, opt, (uint)optlen );

    /* Copy Window Size */
    pTcpHdr->WindowSize = HNC16(((uint)advwin));

#ifdef TCP_DEBUG
    DbgPrintf(DBG_INFO, "TcpOutput: L=%d, W=%d\n", len, advwin);
#endif

    /* Check for Urgent data */
    if( SEQ_GT( pt->snd_up, pt->snd_nxt ) )
    {
        dwTmp = pt->snd_up - pt->snd_nxt;
        pTcpHdr->UrgPtr = HNC16(((uint)dwTmp));
        flags |= TCP_URG;
    }
    else
    {
        /* Keep "up" bumped over to the far left */
        pt->snd_up = pt->snd_una;
        pTcpHdr->UrgPtr = 0;
    }

    /* Now we can set flags */
    pTcpHdr->Flags = flags;

    /* Fixup packet frag info */
    dwTmp = len+TCPHDR_SIZE+optlen;
    dwTmp = (UINT32)(HNC16(((uint)dwTmp)));

    /* Checksum Header */
    tpseudo.IPSrc    = SockGetLIP(pt->hSock);
    tpseudo.IPDst    = SockGetFIP(pt->hSock);
    tpseudo.Null     = 0;
    tpseudo.Protocol = 6;
    tpseudo.Length   = (UINT16)dwTmp;
    TcpChecksum( pTcpHdr );

    /* The packet is all set to go, but we need to update some of */
    /* our sequences and timers. */

    /* If in persist state, just update snd_max */
    if( pt->t_flags & TF_PERSIST )
    {
        /* Length is always 1 */
        if( SEQ_GT( pt->snd_nxt+len, pt->snd_max ) )
            pt->snd_max = pt->snd_nxt+len;
    }
    else
    {
        /* Update sequences and timers */
        dwTmp = pt->snd_nxt;            /* Save this for later */

        /* Advance snd_nxt */
        /* SYN and FIN count as a squence byte */
        if( flags & TCP_SYN )
            pt->snd_nxt++;
        if( flags & TCP_FIN )
        {
            pt->snd_nxt++;
            pt->t_flags |= TF_SENTFIN;
        }

        /* Count actual payload bytes */
        pt->snd_nxt += len;

        /* If sending new data, bump snd_max, and potentially time */
        /* segment */
        if( SEQ_GT( pt->snd_nxt, pt->snd_max ) )
        {
            pt->snd_max = pt->snd_nxt;

            /* If timer isn't going, time this sequence */
            if( !pt->t_trtt )
            {
                pt->t_trtt = 1;
                pt->t_rttseq = dwTmp;
                tcps.SegsTimed++;
            }
        }

        /* Set the Retransmit timer if not already set, unless we don't */
        /* expect an ACK (snd_nxt == snd_una) */
        if( !pt->TicksRexmt && (pt->snd_nxt != pt->snd_una) )
        {
            pt->TicksRexmt = pt->t_trtx;

            /* Since we just sent a packet, we don't "persist" */
            if( pt->TicksPersist )
            {
                pt->TicksPersist = 0;
                pt->t_rtxindex = 0;
            }
        }
    }

    /* If we've advertised a larger window, remember it */
    if( advwin > 0 && SEQ_GT( pt->rcv_nxt + advwin, pt->rcv_adv ) )
        pt->rcv_adv = pt->rcv_nxt + advwin;

    /* Clear ACK related flags */
    pt->t_flags &= ~(TF_NEEDOUTPUT|TF_ACKNOW|TF_DELACK|TF_PERSIST);

    /* Indicate the preferred route */
    PBM_setRoute( pPkt, SockGetRoute( pt->hSock ) );

    /* Count it */
    tcps.SndTotal++;

    /* Send the packet */
    error = IPTxPacket( pPkt,
                        SockGetOptionFlags(pt->hSock) & FLG_IPTX_SOSUPPORTED );

    /* Handle error cases */
    if( error )
    {
        /* RFC2018 - SACK - If SACK retransmitting, restore snd_nxt */
        if (pt->sackActive && pt->pSack->rexmtTimeout) {
            pt->snd_nxt = savedSndNxt;
        }

        if( (error == EHOSTUNREACH || error == EHOSTDOWN) &&
            pt->t_state >= TSTATE_SYNRCVD )
        {
            pt->t_softerror = error;
            return( 0 );
        }
        return( error );
    }

    /* RFC2018 - SACK */
    if (pt->sackActive && pt->pSack->rexmtTimeout) {
        sackRexmitLen += len;
        pt->snd_nxt = savedSndNxt;
        /*  Check if SACK retransmission exceeds congestion window */
        if (sackRexmitLen > pt->snd_cwnd) {
            pt->snd_nxt = savedSndNxt;
            sendmore = 0;
        }
        else {
            sendmore = 1;
        }
    }

    if( sendmore )
        goto sendagain;

    return(0);
}

/*-------------------------------------------------------------------- */
/* TcpGenPacket() */
/* Called to send quick and dirty TCP packets */
/*-------------------------------------------------------------------- */
void TcpGenPacket( TCPPROT *pt, IPN IPDst, uint PortDst,
                   IPN IPSrc, uint PortSrc, UINT32 ack, UINT32 seq, int flags )
{
    PBM_Pkt     *pPkt;
    uint        IPHdrLen,win;
    TCPHDR      *pTcpHdr;
    IPHDR       *pIpHdr;

    if( !pt )
        pPkt = SockCreatePacket( 0, TCPHDR_SIZE);
    else
        pPkt = SockCreatePacket( pt->hSock, TCPHDR_SIZE);

    if( !pPkt )
        return;

    /* Get the IP header len */
    IPHdrLen = pPkt->IpHdrLen;

    /* Assign an IP header pointer */
    pIpHdr = (IPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Assign a TCP header pointer */
    pTcpHdr = (TCPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset + IPHdrLen);

    /* Fill in TCP/IP Header */

    /* Override some IP header stuff */
    pIpHdr->Protocol = 6;
    WrNet32( &pIpHdr->IPSrc, IPSrc );
    WrNet32( &pIpHdr->IPDst, IPDst );

    /* Set some TCP header stuff */
    pTcpHdr->HdrLen  = TCPHDR_SIZE*4;
    pTcpHdr->SrcPort = PortSrc;
    pTcpHdr->DstPort = PortDst;
    pTcpHdr->UrgPtr  = 0;
    seq = HNC32(seq);
    WrNet32( &pTcpHdr->Seq, seq );
    ack = HNC32(ack);
    WrNet32( &pTcpHdr->Ack, ack );

    /* Setup the window size we wish to advertise */
    /* This is the space we have left in the RX buffer */
    if( !pt )
        pTcpHdr->WindowSize = 0;
    else
    {
        win = (uint)SBGetSpace(pt->hSBRx);
        pTcpHdr->WindowSize = HNC16(win);
    }

    /* Set flags */
    pTcpHdr->Flags = flags;

    /* Checksum Header */
    tpseudo.IPSrc    = IPSrc;
    tpseudo.IPDst    = IPDst;
    tpseudo.Null     = 0;
    tpseudo.Protocol = 6;
    tpseudo.Length   = HNC16(TCPHDR_SIZE);
    TcpChecksum( pTcpHdr );

    /* Count it */
    tcps.SndTotal++;

    /* Send the packet */
    if( pt )
        IPTxPacket( pPkt, SockGetOptionFlags(pt->hSock)&FLG_IPTX_SOSUPPORTED );
    else
        IPTxPacket( pPkt, 0 );
}

