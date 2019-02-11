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
 * ======== ipfrag.c ========
 *
 * Routines related to IP fragmentation
 *
 */

#include <stkmain.h>
#include "ip.h"

#define FRAG_LAST       0x80000000
#define FRAG_MIDDLE     0x40000000
#define FRAG_FIRST      0x20000000
#define FRAG_OFFSET     0x0000FFFF

REASM *_IPReasmPtr = 0;

/*-------------------------------------------------------------------- */
/* IPReasm() - Attempt to reassemble packet fragment */
/* Takes the supplied packet fragment, and attempts to reassemble it */
/* into a complete packet. If the packet under reassembly is too large, */
/* the reassembly is aborted. */
/*-------------------------------------------------------------------- */
void IPReasm( PBM_Pkt *pPkt )
{
    IPHDR       *pIpHdr;
    UINT16      Id;
    REASM       *pr;
    uint        tmp, hdrlen;
    UINT32      Tmp, Off, Tmp2;
    PBM_Pkt     *pPktT;
    UINT8       *pb;

    ips.Fragments++;

    /* Get the IP header pointer */
    pIpHdr = (IPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* First, try and find a partially assembled packet with this ID */
    Id = HNC16( pIpHdr->Id );
    pr = _IPReasmPtr;
    while( pr )
    {
        if( pr->Id == Id )
            goto ReasmContinue;
        pr = pr->pNext;
    }

    /* We didn't find this Id in the list, so we'll create a new packet */
    /* to hold it. */
    if( !(pr = mmAlloc( sizeof(REASM) )) )
    {
        ips.Fragdropped++;
        PBM_free( pPkt );
        return;
    }

    /* Initialize new entry */
    mmZeroInit( pr, sizeof(REASM) );
    pr->Type    = HTYPE_IPFRAG;
    pr->Id      = Id;
    pr->Timeout = llTimerGetTime(0) + IP_REASM_MAXTIME;

    /* Insert into our list */
    if( _IPReasmPtr )
    {
        pr->pNext = _IPReasmPtr;
        _IPReasmPtr->pPrev = pr;
    }
    _IPReasmPtr = pr;

ReasmContinue:
    /* Now we have the packet under reassembly in "pr", and our */
    /* particular fragment in pPkt. */

    /* Now prepare the frag for insertion into the packet */

    /* Get IP hdrlen & total length */
    hdrlen = (uint)pPkt->IpHdrLen;
    tmp    = (uint)(HNC16( pIpHdr->TotalLen ));

    /* Aux2 = Data length of frag data */
    pPkt->Aux2 = (UINT32)(tmp - hdrlen);

    tmp = HNC16( pIpHdr->FlagOff );

    /* If DONT_FRAG is set, we should never have got here! */
    /* However, "correct" and "working" are two diffent things. */
    /* In the spirit of "be liberal in what you accept", we'll */
    /* ignore the IP_DF flag. */
    tmp &= ~IP_DF;

    /* Define Aux1 to be a flag + header or offset */

    /* Mark us as FIRST, MIDDLE, or LAST frag */
    if( !(tmp & IP_MF) )
        pPkt->Aux1 = FRAG_LAST;
    else
        pPkt->Aux1 = FRAG_MIDDLE;

    /* Set tmp = data offset */
    tmp = (tmp & ~IP_MF) * 8;

    /* If we're over our max, zap it */
    if( (tmp+(uint)(pPkt->Aux2)) > IP_REASM_MAXSIZE )
    {
        ips.Fragdropped++;
        PBM_free( pPkt );
        IPReasmFree( pr, 1 );
        return;
    }

    /* If we're the first frag, then Aux1 is our header size */
    if( !tmp )
        pPkt->Aux1 = FRAG_FIRST | (UINT32)hdrlen;
    /* Else Aux1 is of offset */
    else
    {
        pPkt->Aux1 |= (UINT32)tmp;

        /* We also need to remove the IP header from non-first frags */
        pPkt->ValidLen   -= hdrlen;
        pPkt->DataOffset += hdrlen;
    }

    /* Insert the packet into the correct place in the list */
    if( !(pPktT=pr->pPkt) || (pPkt->Aux1 <= pPktT->Aux1) )
    {
        pr->pPkt = pPkt;
        pPkt->pPrev = 0;
        pPkt->pNext = pPktT;
    }
    else
    {
        while( pPktT->pNext && (pPktT->pNext->Aux1 < pPkt->Aux1) )
            pPktT = pPktT->pNext;

        pPkt->pPrev = pPktT;
        pPkt->pNext = pPktT->pNext;
        pPktT->pNext = pPkt;
    }
    if( pPkt->pNext )
        pPkt->pNext->pPrev = pPkt;


    /* Now see if we have a complete packet */
    pPkt = pr->pPkt;

    /* First we must have a "first frag" */
    if( !(pPkt->Aux1 & FRAG_FIRST) )
        return;

    /* Tmp = Running length (not including IP header) */
    Tmp = 0;

    while( pPkt )
    {
        /* If this is a "FIRST", then use the largest initial size */
        if( pPkt->Aux1 & FRAG_FIRST )
        {
            if( pPkt->Aux2 > Tmp )
                Tmp = pPkt->Aux2;
        }
        else
        {
            /* If there is a hole between data we have and the next */
            /* offset, then abort */
            Tmp2 = pPkt->Aux1 & FRAG_OFFSET;
            if( Tmp2 > Tmp )
                return;

            Tmp2 = Tmp - Tmp2;      /* Data Overlap */
            if( pPkt->Aux2 > Tmp2 )
            {
                /* Combine this frag into length */
                Tmp += pPkt->Aux2 - Tmp2;
            }

            /* If this is the last frag, we're done */
            if( pPkt->Aux1 & FRAG_LAST )
                break;
        }
        pPkt = pPkt->pNext;
    }

    if( pPkt )
    {
        /* Here we have a completed packet! */

        /* Add in the original IP header size to length */
        Tmp += pr->pPkt->Aux1 & FRAG_OFFSET;

        /* Create the combined packet */
        pPkt = NIMUCreatePacket( Tmp );
        if( !pPkt )
        {
            /* Can't allocate final packet */
            IPReasmFree( pr, 1 );
            return;
        }

        pPkt->ValidLen = Tmp;
        pb = pPkt->pDataBuffer + pPkt->DataOffset;

        pPktT = pr->pPkt;
        pPkt->hIFRx = pPktT->hIFRx;

        /* Tmp = Running length (not including IP header) */
        /* Off = Running offset (length) (including IP header) */
        Tmp   = 0;
        Off = 0;

        while( pPktT )
        {
            /* If this is a "FIRST", then use the largest initial size */
            if( pPktT->Aux1 & FRAG_FIRST )
            {
                if( pPktT->Aux2 > Tmp )
                {
                    /* Special for "first frag" - add in IP header */
                    Off = pPktT->Aux2+(pPktT->Aux1&FRAG_OFFSET);
                    mmCopy( pb, pPktT->pDataBuffer+pPktT->DataOffset,
                            (uint)Off );
                    Tmp = pPktT->Aux2;
                }
            }
            else
            {
                Tmp2 = Tmp - (pPktT->Aux1&FRAG_OFFSET);      /* Data Overlap */
                if( pPktT->Aux2 > Tmp2 )
                {
                    /* Combine this frag into buffer */
                    pPktT->Aux2 -= Tmp2;
                    mmCopy( pb+Off, pPktT->pDataBuffer+pPktT->DataOffset+Tmp2,
                           (uint)pPktT->Aux2 );

                    /* Combine this frag into length */
                    Tmp += pPktT->Aux2;
                    Off += pPktT->Aux2;
                }

                /* If this is the last frag, we're done */
                if( pPktT->Aux1 & FRAG_LAST )
                    break;
            }
            pPktT = pPktT->pNext;
        }

        /* Free the REASM struct and send the packet */
        ips.Reassembled++;
        IPReasmFree( pr, 0 );

        pIpHdr = (IPHDR *)pb;
        pIpHdr->FlagOff  = 0;
        pIpHdr->TotalLen = HNC16((uint)Off);
        IPChecksum( pIpHdr );

        IPRxPacket( pPkt );
    }
    return;
}

/*-------------------------------------------------------------------- */
/* IPReasmTimeout() - Check reasm list for reassembly timeout */
/*-------------------------------------------------------------------- */
void IPReasmTimeout()
{
    REASM  *pr;
    REASM  *prNext;
    UINT32 TimeNow;

    TimeNow = llTimerGetTime(0);

    prNext = _IPReasmPtr;
    while( (pr = prNext) )
    {
        prNext = pr->pNext;
        if( pr->Timeout < TimeNow )
        {
            ips.Fragtimeout++;
            IPReasmFree( pr, 1 );
        }
    }
}

/*-------------------------------------------------------------------- */
/* IPReasmFree() - Free a reasm entry and bump stats */
/*-------------------------------------------------------------------- */
void IPReasmFree( REASM *pr, uint fUpateStats )
{
    PBM_Pkt *pPkt;

    /* Remove from chain */
    if( pr->pNext )
        pr->pNext->pPrev = pr->pPrev;

    if( !pr->pPrev )
        _IPReasmPtr = pr->pNext;
    else
        pr->pPrev->pNext = pr->pNext;

    /* Free packets */
    while( (pPkt = pr->pPkt) )
    {
        pr->pPkt = pPkt->pNext;
        PBM_free( pPkt );
        if( fUpateStats )
            ips.Fragdropped++;
    }

    /* Free REASM record */
    mmFree( pr );
    return;
}

