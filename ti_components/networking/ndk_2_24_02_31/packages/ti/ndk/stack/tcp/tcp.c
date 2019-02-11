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
 * ======== tcp.c ========
 *
 * TCP General functions
 *
 */

#include <stkmain.h>
#include "tcp.h"

/* Private and Public Globals */
UINT32   tcp_iss = 0x7F000000;  /* Initial send sequence */
TCPSTATS tcps;                  /* Stats */
TCPPROT  *ptTimeFirst = 0;      /* Pointer to first time-out candidate */
PSEUDO   tpseudo;               /* Pseudo header for checksum */

/*-------------------------------------------------------------------- */
/* void TcpChecksum( TCPHDR *pbHdr ) */
/* Checksums the TCP header */
/*-------------------------------------------------------------------- */
void TcpChecksum( TCPHDR *pTcpHdr )
{
    int     tmp1;
    UINT16  *pw;
    UINT32  TSum;

    /* Get header size in bytes */
    tmp1 = (int)HNC16(tpseudo.Length);

    /* Checksum field is NULL in checksum calculations */
    pTcpHdr->TCPChecksum = 0;

    /* Checksum the header */
    pw = (UINT16 *)pTcpHdr;
    TSum = 0;
    for( ; tmp1 > 1; tmp1 -= 2 )
        TSum += (UINT32)*pw++;
#ifdef BIGENDIAN
    if( tmp1 )
        TSum += (UINT32)(*pw & 0xFF00);
#else
    if( tmp1 )
        TSum += (UINT32)(*pw & 0x00FF);
#endif

    /* Checksum the pseudo header */
    pw = (UINT16 *)&tpseudo;
    for( tmp1=0; tmp1 < 6; tmp1++ )
        TSum += (UINT32)*pw++;

    TSum = (TSum&0xFFFF) + (TSum>>16);
    TSum = (TSum&0xFFFF) + (TSum>>16);
    TSum = ~TSum;

    /* Note checksum is Net/Host byte order independent */
    pTcpHdr->TCPChecksum = (UINT16)TSum;
}

/*-------------------------------------------------------------------- */
/* TCP Timeout Functions */
/*-------------------------------------------------------------------- */

/*-------------------------------------------------------------------- */
/* TcpTimeoutAdd */
/* Add TCP object to timeout canditate list */
/*-------------------------------------------------------------------- */
void TcpTimeoutAdd( TCPPROT *pt )
{
    /* Easiest to always insert at head of list */
    pt->pPrev = 0;
    pt->pNext = ptTimeFirst;
    if( ptTimeFirst )
        ptTimeFirst->pPrev = pt;
    ptTimeFirst = pt;
}

/*-------------------------------------------------------------------- */
/* TcpTimeoutRemove */
/* Remove TCP object from timeout canditate list */
/*-------------------------------------------------------------------- */
void TcpTimeoutRemove( TCPPROT *pt )
{
    /* Patch preceeding entry */
    if( !pt->pPrev )
        ptTimeFirst = pt->pNext;
    else
        pt->pPrev->pNext = pt->pNext;

    /* Patch following entry */
    if( pt->pNext )
       pt->pNext->pPrev = pt->pPrev;
}

/*-------------------------------------------------------------------- */
/* TcpTimeoutCheck */
/* Scan timeout list for TCP timeouts */
/*-------------------------------------------------------------------- */
void TcpTimeoutCheck()
{
    TCPPROT *pt;
    TCPPROT **ppt;
    UINT32  TimeWaitCnt = 0;
    UINT32  TicksTWLow  = 0xFFFFFFFF;
    UINT32  TicksTWHigh = 0;;

    ppt = &ptTimeFirst;

    while( *ppt )
    {
        pt = *ppt;

        /* Check all timers. If pt goes away by calling the timeout */
        /* function, then move on to the next one. */
        if( pt->TicksRexmt && !--pt->TicksRexmt )
        {
            TcpTimeoutRexmt( pt );
            if( *ppt != pt )
                continue;
        }


        /* RFC 2018 - SACK */
        if( pt->TicksSackRexmt && !--pt->TicksSackRexmt )
        {
            TcpTimeoutSackRexmt( pt );
            if( *ppt != pt )
                continue;
        }

        if( pt->TicksPersist && !--pt->TicksPersist )
        {
            TcpTimeoutPersist( pt );
            if( *ppt != pt )
                continue;
        }

        if( pt->TicksKeep && !--pt->TicksKeep )
        {
            TcpTimeoutKeep( pt );
            if( *ppt != pt )
                continue;
        }

        if( pt->TicksWait2 )
        {
            if( !--pt->TicksWait2 )
            {
                TcpTimeoutWait2( pt );
                if( *ppt != pt )
                    continue;
            }
            else if( pt->t_state == TSTATE_TIMEWAIT )
            {
                TimeWaitCnt++;
                if( pt->TicksWait2 < TicksTWLow )
                    TicksTWLow = pt->TicksWait2;
                if( pt->TicksWait2 > TicksTWHigh )
                    TicksTWHigh = pt->TicksWait2;
            }
        }

        /* Perform any delayed ACK */
        if( pt->t_flags & TF_DELACK )
        {
            pt->t_flags &= ~TF_DELACK;
            pt->t_flags |= TF_ACKNOW;
            tcps.DelAck++;
            TcpOutput(pt);
        }
        else if( pt->t_flags & TF_NEEDOUTPUT )
            TcpOutput(pt);

        /* Bump Idle time */
        pt->t_tidle++;

        /* Bump RTT counter if active */
        if( pt->t_trtt )
            pt->t_trtt++;

        /* Move on to next block */
        ppt = &pt->pNext;
    }

    /* Bump TCP start sequence */
    tcp_iss += TCP_ISSINCR/2;

    /* Fix any socket glut in TIMEWAIT */
    if( TimeWaitCnt >= 20 )
    {
        /* Set a cutoff half way in the range */
        TicksTWLow = (TicksTWLow+TicksTWHigh)/2;

        ppt = &ptTimeFirst;

        while( *ppt )
        {
            pt = *ppt;

            /* Accelerate TIMEWAIT timeouts that fall in the */
            /* cutoff range. */
            if( pt->TicksWait2 && pt->t_state == TSTATE_TIMEWAIT )
            {
                if( pt->TicksWait2 <= TicksTWLow )
                {
                    pt->TicksWait2 = 0;
                    TcpTimeoutWait2( pt );
                    if( *ppt != pt )
                        continue;
                }
            }

            /* Move on to next block */
            ppt = &pt->pNext;
        }
    }
}

