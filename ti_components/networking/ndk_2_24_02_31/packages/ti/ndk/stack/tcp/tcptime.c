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
 * ======== tcptime.c ========
 *
 * TCP Timer Timeout Functions
 *
 */

#include <stkmain.h>
#include "tcp.h"

/* tcp_backoff - Exponential backoff applied to Timer Ticks */
static UINT32 tcp_backoff[TCP_MAXBACKOFF+1] =
       { 1, 2, 4, 8, 16, 32, 64, 64, 64, 128, 128, 128, 128 };

/*-------------------------------------------------------------------- */
/* TcpSetPersist */
/* Set persist time used when client advertised window is Zero */
/*-------------------------------------------------------------------- */
void TcpSetPersist( TCPPROT *pt )
{
    UINT32 Ticks;

    /* Calculate */
    Ticks = ( pt->t_srtt + 2 * pt->t_rttvar ) >> TCP_FIXP_SHIFT;
    Ticks *= tcp_backoff[pt->t_rtxindex];

    /* Start/restart persistance timer. */
    TCPT_RANGESET( pt->TicksPersist, Ticks, TCPTV_PERSMIN, TCPTV_PERSMAX);

    /* Back off some more next time */
    if (pt->t_rtxindex < TCP_MAXBACKOFF)
        pt->t_rtxindex++;
}

/*-------------------------------------------------------------------- */
/* TcpTimeoutWait2 */
/* Called when the TCP wait timer (TIME_WAIT or FIN_WAIT_2) has fired */
/*-------------------------------------------------------------------- */
void TcpTimeoutWait2( TCPPROT *pt )
{
    /* If we're in the TIMEWAIT state, close the control block */
    /* Otherwise, we're in FIN_WAIT_2 - if we've been idle for more */
    /* than MAX_IDLE (10min), close the control block. Otherwise, */
    /* time another interval. */
    if( pt->t_state != TSTATE_TIMEWAIT && pt->t_tidle <= TCPTV_MAX_IDLE )
        pt->TicksWait2 = TCPTV_KEEP_INTVL;
    else
        TcpClose( pt );
}

/*-------------------------------------------------------------------- */
/* TcpTimeoutPersist */
/* Called when the TCP retransmit timer has expired */
/*-------------------------------------------------------------------- */
void TcpTimeoutPersist( TCPPROT *pt )
{
    DbgPrintf(DBG_INFO,"TcpTimeoutPersist: Persist Timeout");

    /* Bump the timeout stats */
    tcps.PersistTimeout++;

    /* Set the next persist timeout */
    TcpSetPersist( pt );

    /* Force a segment (check for lost window advertisement) */
    pt->t_flags |= TF_PERSIST;
    TcpOutput( pt );
}

/*-------------------------------------------------------------------- */
/* TcpTimeoutKeep */
/* Called when the TCP KeepAlive timer has expired */
/*-------------------------------------------------------------------- */
void TcpTimeoutKeep( TCPPROT *pt )
{
    INT32  KeepAlive;

    DbgPrintf(DBG_INFO,"TcpTimeoutKeep: Keep Timeout");

    /* Bump the timeout stats */
    tcps.KeepTimeout++;

    /* Check for timeout on a connection request */
    if( pt->t_state < TSTATE_ESTAB )
        goto KeepDrop;

    /* Get the socket option KEEPALIVE */
    KeepAlive = SockGetOptionFlags( pt->hSock ) & SO_KEEPALIVE;

    /* Once "closed", KeepAlive no longer applies. Otherwise, when */
    /* KeepAlive is set, send a probe. */
    if( KeepAlive && pt->t_state <= TSTATE_CLOSEWAIT )
    {
        /* If we've been idle too long (2 hours + 10 min), drop connection */
        if( pt->t_tidle >= TCPTV_KEEP_IDLE + TCPTV_KEEP_MAXIDLE )
            goto KeepDrop;

        /* Bump the "probe" stats */
        tcps.KeepProbe++;

        /* Send a keepalive packet */
        TcpGenPacket( pt, SockGetFIP(pt->hSock), SockGetFPort(pt->hSock),
                      SockGetLIP(pt->hSock), SockGetLPort(pt->hSock),
                      pt->rcv_nxt, pt->snd_una-1, TCP_ACK );

        /* Set to probe again in in 75 seconds */
        pt->TicksKeep = TCPTV_KEEP_INTVL;
    }
    else
    {
        /* We're not active */
        /* Set to probe again in in 2 hours seconds */
        pt->TicksKeep = TCPTV_KEEP_IDLE;
    }
    return;

KeepDrop:
    /* Bump the drop stats */
    tcps.KeepDrops++;

    /* Set socket error and drop connection */
    TcpDrop( pt, ETIMEDOUT );
}

/*-------------------------------------------------------------------- */
/* TcpTimeoutRexmt */
/* Called when the TCP retransmit timer has expired */
/*-------------------------------------------------------------------- */
void TcpTimeoutRexmt( TCPPROT *pt )
{
    UINT32 Ticks;

    DbgPrintf(DBG_INFO,"TcpTimeoutRexmt: Retransmit Timeout");

    /* Message has not been acked within retransmit interval. */
    /* Back off to a longer retransmit interval and retransmit one segment. */
    if( ++pt->t_rtxindex > TCP_MAXBACKOFF )
    {
        /* Already at max - drop it like a bad habit */
        pt->t_rtxindex = TCP_MAXBACKOFF;

        /* Bump the drop stats */
        tcps.TimeoutDrops++;

        /* Set socket error and drop connection */
        TcpDrop( pt, ETIMEDOUT );
        return;
    }

    /* Bump the stats */
    tcps.RexmtTimeout++;

    /* Calculate */
    Ticks = ( pt->t_srtt + 4 * pt->t_rttvar ) >> TCP_FIXP_SHIFT;
    Ticks *= tcp_backoff[pt->t_rtxindex];

    /* Start/restart retransmit timer. */
    TCPT_RANGESET( pt->t_trtx, Ticks, TCPTV_RTXMIN, TCPTV_RTXMAX);
    pt->TicksRexmt = pt->t_trtx;

    /* If we've retransmitted four or more times, notify the */
    /* Socket handler. Also, the round trip time is no longer */
    /* accurate, so we reset it. */
    if (pt->t_rtxindex > TCP_MAXBACKOFF / 4)
    {
        /* Notify socket it's losing data */
        SockValidateRoute( pt->hSock );
        /* First pre-adjust rttvar so that RTO will be */
        /* the same if we time out again */
        pt->t_rttvar += pt->t_srtt/4;
        /* Now clear srtt so that the measured RTT is used */
        pt->t_srtt   = TCPTV_SRTTBASE;
    }

    /* Retransmit earliest unacked sequence */
    pt->snd_nxt = pt->snd_una;

    /* Force a segment to be sent. */
    pt->t_flags |= TF_ACKNOW;

    /* If timing a segment in this window, stop the timer. */
    pt->t_trtt = 0;

    /* Close the congestion window down to one segment */
    /* (we'll open it by one segment for each ack we get). */
    /* This "slow start" keeps us from dumping all that data */
    /* as back-to-back packets */
    pt->snd_cwnd = pt->t_mss;                   /* (one segment) */

    /* RFC 2018 - SACK */
        if (pt->sackActive) {
        /* Flush SACK information from tx table and stop the timer */
            pt->pSack->txTableTop = 0;
        pt->pSack->txTableBottom = 0;
                pt->TicksSackRexmt = 0;
        }

    /* Retransmit earliest unacked sequence */
    TcpOutput( pt );
}

/*-------------------------------------------------------------------- */
/* TcpTimeoutSackRexmt */
/* Called when the TCP SACK retransmit timer has expired */
/*-------------------------------------------------------------------- */
void TcpTimeoutSackRexmt( TCPPROT *pt )
{
    DbgPrintf(DBG_INFO,"TcpTimeoutSackRexmt: SACK Rexmit Timeout");

    pt->pSack->rexmtTimeout = 1;

    /* Force a segment to be sent. */
    pt->t_flags |= TF_ACKNOW;

    /* Close the congestion window down to one segment */
    /* (we'll open it by one segment for each ack we get). */
    /* This "slow start" keeps us from dumping all that data */
    /* as back-to-back packets */
    pt->snd_cwnd = TCP_SACK_REXMIT_SEGMENT * pt->t_mss;  /* (one segment) */
    pt->pSack->rexmtIndex = 0xFFFFFFFF;

    /* Retransmit earliest unacked sequence */
    TcpOutput( pt );

    /* restart timer */
    pt->pSack->rexmtTimeout = 0;
    TCPT_RANGESET(pt->TicksSackRexmt, 
                  (pt->t_trtx / TCP_SACK_REXMIT_TIMER_RATIO),
                  1,
                  pt->t_trtx
                 );     
}

/*-------------------------------------------------------------------- */
/* TcpXmitTimer */
/* Called when reset xmit timer based on new RTT data */
/*-------------------------------------------------------------------- */
void TcpXmitTimer( TCPPROT *pt, UINT32 urtt )
{
    INT32       delta;
    INT32       rto;
    INT32       rtt;
    
    /* Discard wild RTT measurements */
    if( urtt > pt->t_maxrtt ) {
        return;
    }

    /* Keep this stat for the heck of it. */
    tcps.RttUpdated++;

    rtt = ((INT32)urtt) << TCP_FIXP_SHIFT;

    if( !pt->t_srtt )
    {
        /* We have no data yet, so just initialize */
        /* srtt   = rtt */
        /* rttvar = srtt / 2 */
        /* RTO    = srtt + 2 * rttvar   (same as 2*rtt) */
        pt->t_srtt   = rtt;
        pt->t_rttvar = pt->t_srtt / 2;
        rto = ( rtt * 2 ) >> TCP_FIXP_SHIFT;
    }
    else
    {
        /* We want to adjust srtt / rttvar by the following formulas: */
        /*      delta  = ticks - srtt */
        /*      srtt   = srtt + (1/8)delta */
        /*      rttvar = rttvar + (1/4)(|delta| - rttvar) */
        /*      RTO    = srtt + 4 * rttvar */
        delta = rtt - pt->t_srtt;

        pt->t_srtt += delta >> 3;
        if( pt->t_srtt < (TCP_FIXP_SHIFT-1) )
            pt->t_srtt = 1 << (TCP_FIXP_SHIFT-1);   /* 0.5 */

        if( delta < 0 )
            delta = -delta;

        delta -= (INT32)pt->t_rttvar;
        pt->t_rttvar += delta >> 2;
        if( pt->t_rttvar < (1 << (TCP_FIXP_SHIFT-2)) )
            pt->t_rttvar = 1 << (TCP_FIXP_SHIFT-2);   /* 0.25 */

        rto = ( pt->t_srtt + 4 * pt->t_rttvar ) >> TCP_FIXP_SHIFT;
    }

    /* Reset RTT timer */
    pt->t_trtt     = 0;

    /* Reset RTT backoff */
    pt->t_rtxindex = 0;

    TCPT_RANGESET( pt->t_trtx, rto, TCPTV_RTXMIN, TCPTV_RTXMAX);
}
