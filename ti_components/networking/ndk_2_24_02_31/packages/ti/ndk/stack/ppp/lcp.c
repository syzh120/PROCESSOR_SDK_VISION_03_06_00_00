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
 * ======== lcp.c ========
 *
 * Member functions of PPP/LCP
 *
 */

#include <stkmain.h>
#include "ppp.h"

#ifdef _INCLUDE_PPP_CODE

/* Timer Equates */
#define LCP_TIMER_CFGIDLE       10
#define LCP_TIMER_CFGRETRY      3
#define LCP_TIMER_ECHOREQUEST   5
#define LCP_TIMER_ECHORETRY     5

/* LCP Codes */
#define LCPCODE_CFGREQ          1
#define LCPCODE_CFGACK          2
#define LCPCODE_CFGNAK          3
#define LCPCODE_CFGREJ          4
#define LCPCODE_TERMREQ         5
#define LCPCODE_TERMACK         6
#define LCPCODE_CODEREJ         7
#define LCPCODE_PROTREJ         8
#define LCPCODE_ECHOREQ         9
#define LCPCODE_ECHOREPLY       10
#define LCPCODE_DISCREQ         11

/* LCP Configuration Options */
#define LCPOPT_MRU              1
#define LCPOPT_CMAP             2
#define LCPOPT_AUTH             3
#define LCPOPT_MAGIC            5
#define LCPOPT_PFC              7
#define LCPOPT_ACFC             8

static void lcpSendCfg( PPP_SESSION *p );
static void lcpSendTerm( PPP_SESSION *p );
static void lcpSendEcho( PPP_SESSION *p );

/*-------------------------------------------------------------------- */
/* lcpInit() */
/* Initialize LCP and set it to CLOSED state */
/*-------------------------------------------------------------------- */
void lcpInit( PPP_SESSION *p )
{
    p->lcp.State     = PROT_STATE_CLOSED;
    p->lcp.StateCFG  = PROT_CFG_IDLE;
    p->lcp.StateACK  = PROT_CFG_IDLE;
    p->lcp.PeerMagic = 0;
    llTimerGetTime(&p->lcp.OurMagic);
    p->lcp.OurMagic = (p->lcp.OurMagic << 4) + llTimerGetTime(0);

    /* The following can be used prior to our startup */

    /* Set the options we allow */
    p->lcp.OptMask  = (1<<LCPOPT_MRU) | (1<<LCPOPT_MAGIC);

    /* Allow the peer to declare PFC and ACFP */
    if( p->Flags & PPPFLG_OPT_ALLOW_HC )
        p->lcp.OptMask |= (1<<LCPOPT_PFC) | (1<<LCPOPT_ACFC);

    /* On client, we allow authentication */
    if( p->Flags & PPPFLG_CLIENT )
        p->lcp.OptMask |= (1<<LCPOPT_AUTH);

    /* If requested, we allow CMAP */
    if( p->Flags & PPPFLG_SIOPT_RECVCMAP )
        p->lcp.OptMask |= (1<<LCPOPT_CMAP);
}

/*-------------------------------------------------------------------- */
/* lcpOpen() */
/* Open LCP and set passive or active */
/*-------------------------------------------------------------------- */
void lcpOpen( PPP_SESSION *p, uint fStart )
{
    /* Set our new state */
    if(p->lcp.State == PROT_STATE_CLOSED || p->lcp.State == PROT_STATE_STOPPED)
        p->lcp.State = PROT_STATE_OPEN;

    /* Start our negotiation if desired */
    if( fStart && p->lcp.StateCFG == PROT_CFG_IDLE )
    {
        p->lcp.StateCFG = PROT_CFG_PENDING;
        p->lcp.Count    = 5;               /* Retry Count */

        /* Set some defaults */
        p->lcp.LastId   = 0;               /* Default Id */
        p->MTU_Rx       = p->MTU_Phys;     /* Our MTU (MRU) */

        /* Desired Options */
        p->lcp.UseMask  = (1<<LCPOPT_MRU) | (1<<LCPOPT_MAGIC);
        if( p->auth.Protocol )
            p->lcp.UseMask |= (1<<LCPOPT_AUTH);

        /* If requested, we send CMAP */
        if( p->Flags & PPPFLG_SIOPT_SENDCMAP )
            p->lcp.UseMask |= (1<<LCPOPT_CMAP);

        lcpSendCfg( p );

        p->SICtrl( p->hSI, SI_MSG_CALLSTATUS, SI_CSTATUS_NEGOTIATE, 0);
    }
    else
    {
        /* Regardless of state, we set a timeout. If this timeout */
        /* fires while StateACK is idle, we close */
        p->lcp.Timer = LCP_TIMER_CFGIDLE;
        p->lcp.Count = 0;
    }
}

/*-------------------------------------------------------------------- */
/* lcpClose() */
/* Close the LCP and reset */
/*-------------------------------------------------------------------- */
void lcpClose( PPP_SESSION *p )
{
    /* Send Termination if we are connected */
    if( p->lcp.State == PROT_STATE_CONNECTED )
    {
        lcpSendTerm( p );
        p->lcp.State = PROT_STATE_STOPPED;
    }
}

/*-------------------------------------------------------------------- */
/* lcpInput() */
/* Receive an LCP packet */
/*-------------------------------------------------------------------- */
void lcpInput( PPP_SESSION *p, PBM_Pkt *pPkt )
{
    LCPHDR      *pHdr;
    UINT32      dwTmp;
    int         TagLen;
    UINT16      Len,wTmp;
    UINT8       Tag,TagSize,*pTagData,*pb;
    int         RetCode;
    int         BadTagLen;
    UINT8       *pBadTagData;

    /* If we're closed, return now */
    if( p->lcp.State == PROT_STATE_CLOSED )
        goto LCPExit;

    /* Get a pointer to the new header */
    pHdr = (LCPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Get packet length */
    Len  = HNC16( pHdr->Length );

    /* Verify that we have the entire packet */
    if( Len > (UINT16)pPkt->ValidLen )
        goto LCPExit;

    switch( pHdr->Code )
    {
    case LCPCODE_CFGREQ:
        /*--------------------- */
        /* Configure-Request */
        /*--------------------- */

        /* Set default MRU */
        p->MTU_Tx = p->MTU_Phys;

        /* Scan the options */
        pTagData    = pHdr->TagData;
        TagLen      = (int)(Len - SIZE_LCPHDR);
        RetCode     = LCPCODE_CFGACK;

        /* Setup these pointers for use by NAK */
        BadTagLen   = 0;
        pBadTagData = pHdr->TagData;

        while( TagLen > 0 )
        {
            Tag     = *pTagData++;
            TagSize = *pTagData++;

            /* Check for malformed packet */
            if( !TagSize )
                goto LCPExit;

            /* First try reject */
            if( Tag > 31 || !(p->lcp.OptMask & (1<<Tag)) )
            {
                /* Reject this option */
                if( RetCode != LCPCODE_CFGREJ )
                {
                    /* We now use the pointer for REJ, so reset them */
                    RetCode     = LCPCODE_CFGREJ;
                    BadTagLen   = 0;
                    pBadTagData = pHdr->TagData;
                }

                *pBadTagData++ = Tag;
                *pBadTagData++ = TagSize;
                if( TagSize > 2 )
                    mmCopy( pBadTagData, pTagData, TagSize );
                BadTagLen   += TagSize;
                pBadTagData += TagSize - 2;
            }

            /* If not in reject state, process option */
            if( RetCode != LCPCODE_CFGREJ )
            {
                /* Process */
                switch( Tag )
                {
                case LCPOPT_MAGIC:
                    /* If the magic number is ours, discard the request */
                    if( p->lcp.OurMagic )
                    {
                        dwTmp = (((UINT32)RdNet16s( pTagData ))<<16) |
                                ((UINT32)RdNet16s(pTagData+2));
                        if( dwTmp == p->lcp.OurMagic)
                            goto LCPExit;
                    }
                    break;

                case LCPOPT_MRU:
                    wTmp = RdNet16s( pTagData );
                    if( wTmp > (UINT16)p->MTU_Tx )
                    {
                        /* We must NAK this value */
                        RetCode = LCPCODE_CFGNAK;

                        *pBadTagData++ = Tag;
                        *pBadTagData++ = 4;
                        *pBadTagData++ = (UINT8)(p->MTU_Tx/256);
                        *pBadTagData++ = (UINT8)(p->MTU_Tx&255);
                        BadTagLen += 4;
                    }
                    else
                        p->MTU_Tx = wTmp;
                    break;

                case LCPOPT_AUTH:
                    /* If we are a client, we try and accept what the peer */
                    /* is giving us. If we don't handle it, we ask for PAP. */
                    if( p->Flags & PPPFLG_CLIENT )
                    {
                        wTmp = RdNet16s( pTagData );

                        if( ( wTmp == PPPPROT_CHAP &&
                                   (TagSize!=5 || *(pTagData+2)!=5) ) ||
                            ( wTmp != PPPPROT_CHAP && wTmp != PPPPROT_PAP ) )
                        {
                            /* We don't support the requested authorization */
                            /* Ask for PAP, just in case they'll take it */
                            RetCode = LCPCODE_CFGNAK;

                            *pBadTagData++ = Tag;
                            *pBadTagData++ = 4;
                            *pBadTagData++ = (UINT8)(PPPPROT_PAP/256);
                            *pBadTagData++ = (UINT8)(PPPPROT_PAP&255);
                            BadTagLen += 4;
                        }
                        else
                            p->auth.Protocol = wTmp;
                    }
                    break;

                case LCPOPT_CMAP:
                    if( TagSize == 6 )
                    {
                        dwTmp = (((UINT32)RdNet16s( pTagData ))<<16) |
                                ((UINT32)RdNet16s(pTagData+2));
                        p->SICtrl( p->hSI, SI_MSG_PEERCMAP, dwTmp, 0 );
                    }
                    break;

                default:
                    break;
                }
            }

            /* Goto next tag */
            TagLen -= (int)TagSize;
            pTagData += TagSize - 2;
        }

        /* Reply to this request */
        pHdr->Code = RetCode;
        if( RetCode == LCPCODE_CFGACK )
        {
            pPkt->ValidLen = Len;
            /* Set new state */
            p->lcp.StateACK = PROT_CFG_OK;
        }
        else
        {
            /* Change length to reflect bad options */
            BadTagLen += SIZE_LCPHDR;
            pHdr->Length = HNC16(BadTagLen);
            pPkt->ValidLen = BadTagLen;
            /* Set new state */
            p->lcp.StateACK = PROT_CFG_PENDING;
        }

        /* Send Packet */
        p->SICtrl(p->hSI, SI_MSG_SENDPACKET, PPPPROT_LCP, pPkt );
        pPkt = 0;
        goto LCPStateChange;

    case LCPCODE_CFGACK:
        /*--------------------- */
        /* Configure-Ack */
        /*--------------------- */
        /* If this ID does not match ours, ignore it */
        if( p->lcp.LastId != pHdr->Id )
            goto LCPExit;

        /* Scan options */
        pTagData = pHdr->TagData;
        TagLen   = (int)(Len - SIZE_LCPHDR);

        while( TagLen > 0 )
        {
            Tag     = *pTagData++;
            TagSize = *pTagData++;

            /* Check for malformed packet */
            if( !TagSize )
                goto LCPExit;

            switch( Tag )
            {
            case LCPOPT_MAGIC:
                /* Magic number must be ours */
                if( p->lcp.OurMagic )
                {
                    dwTmp = (((UINT32)RdNet16s( pTagData ))<<16) |
                            ((UINT32)RdNet16s(pTagData+2));
                    if( dwTmp != p->lcp.OurMagic )
                        goto LCPExit;
                }
                break;
            }

            /* Goto next tag */
            TagLen -= (int)TagSize;
            pTagData += TagSize - 2;
        }

        /* CFG half is connected */
        p->lcp.StateCFG = PROT_CFG_OK;
        goto LCPStateChange;

    case LCPCODE_CFGNAK:
    case LCPCODE_CFGREJ:
        /*--------------------- */
        /* Configure-Nak */
        /* Configure-Reject */
        /*--------------------- */
        /* If this ID does not match ours, ignore it */
        if( p->lcp.LastId != pHdr->Id )
            goto LCPExit;

        /* Adjust our options according to Nak or Rej */
        pTagData = pHdr->TagData;
        TagLen   = (int)(Len - SIZE_LCPHDR);

        while( TagLen > 0 )
        {
            Tag     = *pTagData++;
            TagSize = *pTagData++;

            /* Check for malformed packet */
            if( !TagSize )
                goto LCPExit;

            switch( Tag )
            {
            case LCPOPT_MRU:
                if( pHdr->Code == LCPCODE_CFGNAK )
                {
                    /* Read the size desired by peer */
                    wTmp = RdNet16s( pTagData );
                    p->MTU_Rx = wTmp;
                }
                break;

            case LCPOPT_MAGIC:
                if( pHdr->Code == LCPCODE_CFGNAK )
                {
                    dwTmp = (((UINT32)RdNet16s( pTagData ))<<16) |
                            ((UINT32)RdNet16s(pTagData+2));
                    p->lcp.OurMagic = dwTmp;
                }
                else
                    p->lcp.OurMagic = 0;
                break;

            case LCPOPT_CMAP:
                /* When CMAP is specified, it is required, but we allow the */
                /* peer to NAK us a superset of the bits we need */
                if( pHdr->Code == LCPCODE_CFGNAK )
                {
                    dwTmp = (((UINT32)RdNet16s( pTagData ))<<16) |
                            ((UINT32)RdNet16s(pTagData+2));
                    /* All our required bits must be in the new map */
                    if( (p->CMap & dwTmp) == p->CMap )
                    {
                        p->CMap = dwTmp;
                        break;
                    }
                }
                goto StopConnect;

            case LCPOPT_AUTH:
                /* Can't negotiate authentication much in server mode */
                if( p->Flags & PPPFLG_SERVER )
                {
                    /* If this is a NAK and we're set to CHAP, and we */
                    /* will accept PAP, we'll try switching to PAP */
                    if( pHdr->Code == LCPCODE_CFGNAK &&
                            p->auth.Protocol == PPPPROT_CHAP &&
                            (p->Flags & PPPFLG_OPT_AUTH_PAP) )
                    {
                        p->auth.Protocol = PPPPROT_PAP;
                        break;
                    }
                    goto StopConnect;
                }
                /* Fallthrough... */

            default:
                goto ZapOption;
            }

            /* If Reject, kill this option */
            if( pHdr->Code == LCPCODE_CFGREJ )
            {
ZapOption:
                p->lcp.UseMask &= ~(1<<Tag);
            }

            /* Goto next tag */
            TagLen -= (int)TagSize;
            pTagData += TagSize - 2;
        }

        /* Send a new CFG */
        p->lcp.StateCFG = PROT_CFG_PENDING;
        p->lcp.Count    = 5;

        lcpSendCfg( p );
        break;

    case LCPCODE_TERMREQ:
        /*--------------------- */
        /* Term Request */
        /*--------------------- */
        /* ACK the request */

        /* Change the code to Ack */
        pHdr->Code = LCPCODE_TERMACK;

        /* Send Packet */
        pPkt->ValidLen = Len;
        p->SICtrl(p->hSI, SI_MSG_SENDPACKET, PPPPROT_LCP, pPkt );
        pPkt = 0;

StopConnect:
        p->lcp.State = PROT_STATE_STOPPED;
        /* Notify PPP */
        pppEvent( (HANDLE)p, PPP_EVENT_LCP_STOPPED );
        break;

    case LCPCODE_ECHOREQ:
        /*--------------------- */
        /* Echo Request */
        /*--------------------- */

        /* Discard request if not connected */
        if( p->lcp.State != PROT_STATE_CONNECTED )
            break;

        /* Change the code to Ack */
        pHdr->Code = LCPCODE_ECHOREPLY;
        pb =  pHdr->TagData;
        *pb++ = (UINT8)(p->lcp.OurMagic >> 24);
        *pb++ = (UINT8)(p->lcp.OurMagic >> 16);
        *pb++ = (UINT8)(p->lcp.OurMagic >> 8);
        *pb   = (UINT8)(p->lcp.OurMagic);

        /* Send Packet */
        pPkt->ValidLen = Len;
        p->SICtrl(p->hSI, SI_MSG_SENDPACKET, PPPPROT_LCP, pPkt );
        pPkt = 0;
        break;

    case LCPCODE_ECHOREPLY:
        /*--------------------- */
        /* Echo Reply */
        /*--------------------- */
        /* Keep track that we got the echo reply */
        if( p->lcp.State == PROT_STATE_CONNECTED )
            p->lcp.Count = 0;
        break;

    default:
        break;
    }
    goto LCPExit;

LCPStateChange:
    if( p->lcp.State == PROT_STATE_OPEN )
    {
        /* Check to see if we should start up a configuration request */
        if( p->lcp.StateCFG == PROT_CFG_IDLE &&
                p->lcp.StateACK != PROT_CFG_IDLE )
            lcpOpen( p, 1 );

        /* Check to see if we're connected */
        if( p->lcp.StateCFG == PROT_CFG_OK && p->lcp.StateACK == PROT_CFG_OK )
        {
            p->lcp.State = PROT_STATE_CONNECTED;
            p->lcp.Timer = LCP_TIMER_ECHOREQUEST;
            p->lcp.Count = 0;
            pppEvent( (HANDLE)p, PPP_EVENT_LCP_CONNECT );
        }
    }

LCPExit:
    if( pPkt )
        PBM_free( pPkt );
}

/*-------------------------------------------------------------------- */
/* lcpReject() */
/* Send a LCP Termination Request */
/*-------------------------------------------------------------------- */
void lcpReject( PPP_SESSION *p, PBM_Pkt *pPkt )
{
    PBM_Pkt    *pPkt2;
    LCPHDR     *pHdr;
    UINT8      *pBuf;

    /* Get a pointer to the new header */
    pBuf = (pPkt->pDataBuffer + pPkt->DataOffset);

    /* Bound packet length */
    if( pPkt->ValidLen > 250 )
        pPkt->ValidLen = 250;

    /* Create new packet */
    if( !(pPkt2 = NIMUCreatePacket( 256 )) )
        return;    

    /* Get a pointer to the new packet header */
    pHdr = (LCPHDR *)(pPkt2->pDataBuffer + pPkt2->DataOffset);

    /* Bump the Id */
    p->lcp.LastId++;

    /* Build the CFG packet */
    pHdr->Code = LCPCODE_PROTREJ;
    pHdr->Id   = p->lcp.LastId;
    pHdr->Length = HNC16((pPkt->ValidLen+SIZE_LCPHDR));

    /* Copy in offending packet */
    mmCopy( pHdr->TagData, pBuf, pPkt->ValidLen );

    /* Free the first packet */
    PBM_free( pPkt );

    /* Send the second packet */
    pPkt2->ValidLen = pPkt->ValidLen+SIZE_LCPHDR;
    p->SICtrl(p->hSI, SI_MSG_SENDPACKET, PPPPROT_LCP, pPkt2 );
}

/*-------------------------------------------------------------------- */
/* lcpTimer() */
/* Called every second for LCP timeout */
/*-------------------------------------------------------------------- */
void lcpTimer( PPP_SESSION *p )
{
    /* What we do depends on our state */
    if( p->lcp.Timer && !--p->lcp.Timer )
        switch( p->lcp.State )
        {
        case PROT_STATE_OPEN:
            /* See if we need a CFG message retry */
            if( p->lcp.Count )
            {
                p->lcp.Count--;
                lcpSendCfg( p );
            }
            else
            {
AbortConnect:
                lcpSendTerm( p );
                p->lcp.State = PROT_STATE_STOPPED;
                pppEvent( (HANDLE)p, PPP_EVENT_LCP_STOPPED );
            }
            break;

        case PROT_STATE_CONNECTED:
            /* We use count to track events without pings */
            p->lcp.Count++;
            if( p->lcp.Count > LCP_TIMER_ECHORETRY )
                goto AbortConnect;

            /* Now send a ping ourselves */
            lcpSendEcho( p );

            /* Reset the timer */
            p->lcp.Timer = LCP_TIMER_ECHOREQUEST;
            break;
        }
}

/*-------------------------------------------------------------------- */
/* lcpSendCfg() */
/* Send a LCP Configuration Request */
/*-------------------------------------------------------------------- */
static void lcpSendCfg( PPP_SESSION *p )
{
    PBM_Pkt    *pPkt;
    LCPHDR     *pHdr;
    UINT16     Len,wTmp;
    UINT8      *pTagData;

    /* Create the packet */
    if( !(pPkt = NIMUCreatePacket( 256 )) )
        return;    

    /* Get a pointer to the new header */
    pHdr = (LCPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Reset the timeout */
    p->lcp.Timer = LCP_TIMER_CFGRETRY;

    /* Bump the Id */
    p->lcp.LastId++;

    /* Build the CFG packet */
    pHdr->Code = LCPCODE_CFGREQ;
    pHdr->Id   = p->lcp.LastId;

    /* Add options */
    pTagData = pHdr->TagData;
    Len      = SIZE_LCPHDR;

    for( wTmp=1; wTmp<32; wTmp++ )
    {
        if( p->lcp.UseMask & (1<<wTmp) )
            switch( wTmp )
            {
            case LCPOPT_MRU:
                *pTagData++ = LCPOPT_MRU;
                *pTagData++ = 4;
                *pTagData++ = (UINT8)(p->MTU_Rx/256);
                *pTagData++ = (UINT8)(p->MTU_Rx&255);
                Len += 4;
                break;

            case LCPOPT_CMAP:
                *pTagData++ = LCPOPT_CMAP;
                *pTagData++ = 6;
                *pTagData++ = (UINT8)(p->CMap>>24);
                *pTagData++ = (UINT8)(p->CMap>>16);
                *pTagData++ = (UINT8)(p->CMap>>8);
                *pTagData++ = (UINT8)(p->CMap);
                Len += 6;
                break;

            case LCPOPT_AUTH:
                switch( p->auth.Protocol )
                {
                case PPPPROT_PAP:
                    *pTagData++ = LCPOPT_AUTH;
                    *pTagData++ = 4;
                    *pTagData++ = (UINT8)(PPPPROT_PAP/256);
                    *pTagData++ = (UINT8)(PPPPROT_PAP&255);
                    Len += 4;
                    break;
                case PPPPROT_CHAP:
                    *pTagData++ = LCPOPT_AUTH;
                    *pTagData++ = 5;
                    *pTagData++ = (UINT8)(PPPPROT_CHAP/256);
                    *pTagData++ = (UINT8)(PPPPROT_CHAP&255);
                    *pTagData++ = 5;    /* MD5 */
                    Len += 5;
                    break;
                }
                break;

            case LCPOPT_MAGIC:
                *pTagData++ = LCPOPT_MAGIC;
                *pTagData++ = 6;
                *pTagData++ = (UINT8)(p->lcp.OurMagic >> 24);
                *pTagData++ = (UINT8)(p->lcp.OurMagic >> 16);
                *pTagData++ = (UINT8)(p->lcp.OurMagic >> 8);
                *pTagData++ = (UINT8)(p->lcp.OurMagic);
                pTagData += 4;
                Len += 6;
                break;

            default:
                break;
            }
    }
    pHdr->Length = HNC16(Len);

    /* Send the packet */
    pPkt->ValidLen = Len;
    p->SICtrl(p->hSI, SI_MSG_SENDPACKET, PPPPROT_LCP, pPkt );
}

/*-------------------------------------------------------------------- */
/* lcpSendTerm() */
/* Send a LCP Termination Request */
/*-------------------------------------------------------------------- */
static void lcpSendTerm( PPP_SESSION *p )
{
    PBM_Pkt    *pPkt;
    LCPHDR     *pHdr;

    /* Create the packet */
    if( !(pPkt = NIMUCreatePacket( 256 )) )
        return;    

    /* Get a pointer to the new header */
    pHdr = (LCPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Bump the Id */
    p->lcp.LastId++;

    /* Build the CFG packet */
    pHdr->Code = LCPCODE_TERMREQ;
    pHdr->Id   = p->lcp.LastId;
    pHdr->Length = HNC16(SIZE_LCPHDR);

    /* Send the packet */
    pPkt->ValidLen = SIZE_LCPHDR;
    p->SICtrl(p->hSI, SI_MSG_SENDPACKET, PPPPROT_LCP, pPkt );
}

/*-------------------------------------------------------------------- */
/* lcpSendEcho() */
/* Send a LCP Echo Request */
/*-------------------------------------------------------------------- */
static void lcpSendEcho( PPP_SESSION *p )
{
    PBM_Pkt    *pPkt;
    LCPHDR     *pHdr;
    UINT8      *pb;

    /* Create the packet */
    if( !(pPkt = NIMUCreatePacket( 256 )) )
        return;

    /* Get a pointer to the new header */
    pHdr = (LCPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Bump the Id */
    p->lcp.LastId++;

    /* Build the CFG packet */
    pHdr->Code   = LCPCODE_ECHOREQ;
    pHdr->Id     = p->lcp.LastId;
    pHdr->Length = HNC16((SIZE_LCPHDR+4));
    pb =  pHdr->TagData;
    *pb++ = (UINT8)(p->lcp.OurMagic >> 24);
    *pb++ = (UINT8)(p->lcp.OurMagic >> 16);
    *pb++ = (UINT8)(p->lcp.OurMagic >> 8);
    *pb   = (UINT8)(p->lcp.OurMagic);

    /* Send the packet */
    pPkt->ValidLen = SIZE_LCPHDR+4;
    p->SICtrl(p->hSI, SI_MSG_SENDPACKET, PPPPROT_LCP, pPkt );
}

#endif

