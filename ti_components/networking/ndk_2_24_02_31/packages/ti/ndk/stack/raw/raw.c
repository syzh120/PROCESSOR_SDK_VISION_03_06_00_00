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
 * ======== raw.c ========
 *
 * Raw General Functions
 *
 */
#include <stkmain.h>

/* Private and Public Globals */
RAWSTATS raws;                      /* Stats */

#define RAW_MSS_DEFAULT     1500    /* Default Max seg size (including IP) */

/*-------------------------------------------------------------------- */
/* RawOutput() */
/* Called when RAW packet should be sent */
/*-------------------------------------------------------------------- */
int RawOutput( HANDLE hSock, UINT8 *buf, INT32 size, INT32 *pRetSize)
{
    PBM_Pkt     *pPkt;
    HANDLE      hRoute,hIFTx;
    INT32       mss;
    int         error;

    /* Bound the size to something we can handle */
    /* We'll try and get the MTU from the route, then the egress IF, */
    /* or finally we just assume a default. */
    if( (hRoute = SockGetRoute( hSock )) )
    {
        mss = (INT32)RtGetMTU( hRoute );
        hIFTx = 0;
    }
    else if( (hIFTx = SockGetIFTx( hSock )) )
        mss = (INT32)IFGetMTU( hIFTx );
    else
        mss = RAW_MSS_DEFAULT;

    mss -= SockGetIpHdrSize(hSock);     /* Sub off IpHdr (if any) */

    /* Create the packet */
    if( !(pPkt = SockCreatePacket( hSock, (uint)size )) )
    {
        raws.SndNoPacket++;
        error = ENOBUFS;
        goto RAW_EXIT;
    }

    /* Copy the data */
    mmCopy( (pPkt->pDataBuffer + pPkt->DataOffset + pPkt->IpHdrLen),
             buf, (uint)size );

    /* Indicate the preferred route and IF */
    PBM_setRoute( pPkt, hRoute );
    pPkt->hIFTx = hIFTx;

    /* Count it */
    raws.SndTotal++;

    /* Send the packet */
    error=(int)IPTxPacket(pPkt,SockGetOptionFlags(hSock)&FLG_IPTX_SOSUPPORTED);

RAW_EXIT:
    if( !error )
        *pRetSize = size;
    else
        *pRetSize = 0;

    return( error );
}

/*-------------------------------------------------------------------- */
/* RawInput() */
/* Rx RAW Packet */
/*-------------------------------------------------------------------- */
void RawInput( PBM_Pkt *pPkt )
{
    PBM_Pkt    *pPktCopy;
    HANDLE     hSock,hSockNext,hSBRx,hIFTx;
    uint       RawLen,fBcast = 0;
    IPN        IPSrc,IPDst;
    IPHDR      *pIpHdr;

    /* Assign an IP header pointer */
    pIpHdr = (IPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Count the total number of packets in */
    raws.RcvTotal++;

    /* Get the total length of the message */
    RawLen = (uint)(HNC16( pIpHdr->TotalLen ));

    /* Get source and destination */
    IPSrc = RdNet32(&pIpHdr->IPSrc);
    IPDst = RdNet32(&pIpHdr->IPDst);

    /* Set the Frag Parms to hand off to a SB */
    pPkt->Aux1 = 0x10000;   /* Source Port (0) */
    pPkt->Aux2 = IPSrc;     /* Source IP */
    pPkt->ValidLen = RawLen;

    /* Cache whether we are doing BROADCAST/MULTICAST */
    if( IPDst == INADDR_BROADCAST || IN_MULTICAST( IPDst ) ||
            (pPkt->Flags & (FLG_PKT_MACMCAST|FLG_PKT_MACBCAST)) )
        fBcast = 1;

    /* We have to copy the frag for each socket with a matchng PCB */
    hSock = SockPcbResolveChain( 0, SOCKPROT_RAW, pIpHdr->Protocol,
                                 IPDst, 0, IPSrc, 0 );

     while( hSock )
    {
        /* Get the handle to the next match (so we know if we have one) */
        hSockNext= SockPcbResolveChain( hSock, SOCKPROT_RAW, pIpHdr->Protocol,
                                        IPDst, 0, IPSrc, 0 );

        /* Filter Broadcast and Multicast */
        if( fBcast )
        {
            /* Get the broadcast IF of this socket */
            hIFTx = SockGetIFTx( hSock );

            /* If there is a specified BCAST device, and the packet's */
            /* Rx device doesn't match it, then we ignore the packet */
            if( hIFTx && ( hIFTx != pPkt->hIFRx ) )
            {
                hSock = hSockNext;
                continue;
            }
        }

        /* Get the Linear Receive Buffer */
        hSBRx = SockGetRx( hSock );

        if( SBGetSpace( hSBRx ) < (INT32)RawLen )
            raws.RcvFull++;
        else
        {
            /* Copy the frag if there may be more matches */
            /* Else this is our last time through the loop */
            if( !hSockNext || !(pPktCopy = PBM_copy( pPkt )) )
            {
                pPktCopy = pPkt;
                pPkt = 0;
                hSockNext = 0;
            }

            /* Give the frag to the SB */
            SBWrite( hSBRx, (INT32)RawLen, 0, pPktCopy );

            /* Notify the Socket */
            SockNotify( hSock, SOCK_NOTIFY_RCVDATA );
        }

        /* Check next matching socket */
        hSock = hSockNext;
    }


    /* Free the packet if we didn't use it */
    if( pPkt )
        PBM_free( pPkt );

    return;
}
