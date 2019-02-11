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
 * ======== ipcp.c ========
 *
 * Member functions of PPP/IPCP
 *
 */

#include <stkmain.h>
#include "ppp.h"

#ifdef _INCLUDE_PPP_CODE

#define IPCP_TIMER_CFGRETRY      3

/* IPCP Codes */
#define IPCPCODE_CFGREQ          1
#define IPCPCODE_CFGACK          2
#define IPCPCODE_CFGNAK          3
#define IPCPCODE_CFGREJ          4
#define IPCPCODE_TERMREQ         5
#define IPCPCODE_TERMACK         6
#define IPCPCODE_CODEREJ         7

#define IPCPOPT_IPADDRS          1
#define IPCPOPT_COMPPROTO        2
#define IPCPOPT_IPADDR           3
#define IPCPOPT_PRI_DNS          129
#define IPCPOPT_PRI_NBNS         130
#define IPCPOPT_SEC_DNS          131
#define IPCPOPT_SEC_NBNS         132

#define HOPT(x) ((x)-129+16)
#define EXTENDED_OPT_MASK        0xF0000

static void ipcpSendCfg( PPP_SESSION *p );

/*-------------------------------------------------------------------- */
/* ipcpInit() */
/* Initialize IPCP and set it to CLOSED state */
/*-------------------------------------------------------------------- */
void ipcpInit( PPP_SESSION *p )
{
    p->ipcp.State     = PROT_STATE_CLOSED;
    p->ipcp.StateCFG  = PROT_CFG_IDLE;
    p->ipcp.StateACK  = PROT_CFG_IDLE;

    /* The following can be used before we start */

    /* Set the options we allow */
    p->ipcp.OptMask = (1<<IPCPOPT_IPADDR);

    /* If using extensions, add to options */
    if( p->Flags & PPPFLG_OPT_USE_MSE && p->Flags & PPPFLG_SERVER )
        p->ipcp.OptMask |= EXTENDED_OPT_MASK;
}

/*-------------------------------------------------------------------- */
/* ipcpStart() */
/* Start IPCP session */
/*-------------------------------------------------------------------- */
void ipcpStart( PPP_SESSION *p )
{
    /* Set our new state */
    p->ipcp.State = PROT_STATE_OPEN;

    /* Set our new state */
    p->ipcp.StateCFG  = PROT_CFG_PENDING;
    p->ipcp.Count     = 5;               /* Retry Count */

    /* Set some defaults */
    p->ipcp.LastId    = 0;               /* Default Id */
    p->ipcp.UseMask = (1<<IPCPOPT_IPADDR);

    /* If using extensions, add to server or client flags */
    if( p->Flags & PPPFLG_OPT_USE_MSE && p->Flags & PPPFLG_CLIENT )
        p->ipcp.UseMask |= EXTENDED_OPT_MASK;

    ipcpSendCfg( p );
}

/*-------------------------------------------------------------------- */
/* ipcpInput() */
/* Receive an IPCP packet */
/*-------------------------------------------------------------------- */
void ipcpInput( PPP_SESSION *p, PBM_Pkt *pPkt )
{
    LCPHDR      *pHdr;
    int         TagLen;
    UINT16      Len;
    UINT8       Tag,TagSize,*pTagData;
    UINT8       RetCode;
    int         BadTagLen;
    UINT8       *pBadTagData;
    IPN         IPTmp;

    /* If we're closed, goto IPCPExit now */
    if( p->ipcp.State == PROT_STATE_CLOSED || !pPkt )
        goto IPCPExit;

    /* Get a pointer to the new header */
    pHdr = (LCPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Get packet length */
    Len  = HNC16( pHdr->Length );

    /* Verify that we have the entire packet */
    if( Len > (UINT16)pPkt->ValidLen )
        goto IPCPExit;

    switch( pHdr->Code )
    {
    case IPCPCODE_CFGREQ:
        /*--------------------- */
        /* Configure-Request */
        /*--------------------- */

        /* Scan the options */
        pTagData    = pHdr->TagData;
        TagLen      = (int)(Len - SIZE_LCPHDR);
        RetCode     = IPCPCODE_CFGACK;

        /* Setup these pointers for use by NAK */
        BadTagLen   = 0;
        pBadTagData = pHdr->TagData;

        while( TagLen > 0 )
        {
            Tag     = *pTagData++;
            TagSize = *pTagData++;

            /* Check for malformed packet */
            if( !TagSize )
                goto IPCPExit;

            /* First try reject */
            if( (Tag<129 &&
                   (Tag>16 || !(p->ipcp.OptMask & (1<<Tag))) ) ||
                (Tag>128 &&
                   (Tag>(128+16) || !(p->ipcp.OptMask & (1<<HOPT(Tag)))) ) )
            {
                /* Reject this option */
                if( RetCode != IPCPCODE_CFGREJ )
                {
                    /* We now use the pointer for REJ, so reset them */
                    RetCode     = IPCPCODE_CFGREJ;
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
            if( RetCode != IPCPCODE_CFGREJ )
            {
                if( p->Flags & PPPFLG_SERVER )
                {
                    /* Process as SERVER */
                    switch( Tag )
                    {
                    case IPCPOPT_IPADDR:
                        IPTmp = RdNet32( pTagData );
                        /* As server we insist on our own address */
                        if( IPTmp != p->IPClient )
                        {
                            if( IPTmp && IPTmp!=0xFFFFFFFF &&
                                (p->Flags&PPPFLG_OPT_ALLOW_IP) )
                            {
                                p->IPClient = IPTmp;
                                break;
                            }

                            IPTmp = p->IPClient;
NAKIPADDR:
                            /* We must NAK this value */
                            RetCode = IPCPCODE_CFGNAK;

                            *pBadTagData++ = Tag;
                            *pBadTagData++ = TagSize;
                            WrNet32( pBadTagData, IPTmp );
                            BadTagLen += TagSize;
                            pBadTagData += TagSize - 2;
                        }
                        break;

                    case IPCPOPT_PRI_DNS:
                        IPTmp = RdNet32( pTagData );
                        if( IPTmp != p->IPDNS1 )
                        {
                            IPTmp = p->IPDNS1;
                            goto NAKIPADDR;
                        }
                        break;

                    case IPCPOPT_PRI_NBNS:
                        IPTmp = RdNet32( pTagData );
                        if( IPTmp != p->IPNBNS1 )
                        {
                            IPTmp = p->IPNBNS1;
                            goto NAKIPADDR;
                        }
                        break;

                    case IPCPOPT_SEC_DNS:
                        IPTmp = RdNet32( pTagData );
                        if( IPTmp != p->IPDNS2 )
                        {
                            IPTmp = p->IPDNS2;
                            goto NAKIPADDR;
                        }
                        break;

                    case IPCPOPT_SEC_NBNS:
                        IPTmp = RdNet32( pTagData );
                        if( IPTmp != p->IPNBNS2 )
                        {
                            IPTmp = p->IPNBNS2;
                            goto NAKIPADDR;
                        }
                        break;
                    }
                }
                else
                {
                    /* Process as CLIENT */
                    switch( Tag )
                    {
                    case IPCPOPT_IPADDR:
                        IPTmp = RdNet32( pTagData );
                        p->IPServer = IPTmp;
                        break;
                    }
                }
            }

            /* Goto next tag */
            TagLen -= (int)TagSize;
            pTagData += TagSize - 2;
        }

        /* Reply to this request */
        pHdr->Code = RetCode;
        if( RetCode == IPCPCODE_CFGACK )
        {
            pPkt->ValidLen = Len;
            /* Set new state */
            p->ipcp.StateACK = PROT_CFG_OK;
        }
        else
        {
            /* Change length to reflect bad options */
            BadTagLen += SIZE_LCPHDR;
            pHdr->Length = HNC16(BadTagLen);
            pPkt->ValidLen = BadTagLen;
            /* Set new state */
            p->ipcp.StateACK = PROT_CFG_PENDING;
        }

        /* Send Packet */
        p->SICtrl(p->hSI, SI_MSG_SENDPACKET, PPPPROT_IPCP, pPkt );
        pPkt = 0;
        goto IPCPStateChange;

    case IPCPCODE_CFGACK:
        /*--------------------- */
        /* Configure-Ack */
        /*--------------------- */

        /* If this ID matches ours, we're set */
        if( p->ipcp.LastId == pHdr->Id )
        {
            p->ipcp.StateCFG = PROT_CFG_OK;
            goto IPCPStateChange;
        }
        break;

    case IPCPCODE_CFGNAK:
    case IPCPCODE_CFGREJ:
        /*--------------------- */
        /* Configure-Nak */
        /* Configure-Reject */
        /*--------------------- */
        /* If this ID does not match ours, ignore it */
        if( p->ipcp.LastId != pHdr->Id )
            goto IPCPExit;

        /* Adjust our options according to Nak or Rej */
        pTagData = pHdr->TagData;
        TagLen   = (int)(Len - SIZE_LCPHDR);

        while( TagLen > 0 )
        {
            Tag     = *pTagData++;
            TagSize = *pTagData++;

            /* Check for malformed packet */
            if( !TagSize )
                goto IPCPExit;

            /* Convert extended options (we don't reply using them) */
            if( Tag > 128 )
                Tag = HOPT(Tag);

            switch( Tag )
            {
            case IPCPOPT_IPADDR:
                /* In client mode we accept a NAK, otherwise, just stop */
                if( pHdr->Code == IPCPCODE_CFGNAK && (p->Flags & PPPFLG_CLIENT) )
                    p->IPClient = RdNet32( pTagData );
                else
                    goto StopConnect;
                break;

            case HOPT(IPCPOPT_PRI_DNS):
                /* If NAK, record the proper address */
                if( pHdr->Code == IPCPCODE_CFGNAK )
                    p->IPDNS1 = RdNet32( pTagData );
                break;

            case HOPT(IPCPOPT_SEC_DNS):
                /* If NAK, record the proper address */
                if( pHdr->Code == IPCPCODE_CFGNAK )
                    p->IPDNS2 = RdNet32( pTagData );
                break;

            case HOPT(IPCPOPT_PRI_NBNS):
                /* If NAK, record the proper address */
                if( pHdr->Code == IPCPCODE_CFGNAK )
                    p->IPNBNS1 = RdNet32( pTagData );
                break;

            case HOPT(IPCPOPT_SEC_NBNS):
                /* If NAK, record the proper address */
                if( pHdr->Code == IPCPCODE_CFGNAK )
                    p->IPNBNS2 = RdNet32( pTagData );
                break;

            default:
                goto ZapOption;
            }

            /* If Reject, kill this option */
            if( pHdr->Code == IPCPCODE_CFGREJ )
            {
ZapOption:
                p->ipcp.UseMask &= ~(1<<Tag);
            }

            /* Goto next tag */
            TagLen -= (int)TagSize;
            pTagData += TagSize - 2;
        }

        /* Send a new CFG */
        p->ipcp.StateCFG = PROT_CFG_PENDING;
        p->ipcp.Count    = 5;

        ipcpSendCfg( p );
        break;

    case IPCPCODE_TERMREQ:
        /*--------------------- */
        /* Term Request */
        /*--------------------- */
        /* ACK the request */

        /* Change the code to Ack */
        pHdr->Code = IPCPCODE_TERMACK;

        /* Send Packet */
        pPkt->ValidLen = Len;
        p->SICtrl(p->hSI, SI_MSG_SENDPACKET, PPPPROT_IPCP, pPkt );
        pPkt = 0;

StopConnect:
        p->ipcp.State = PROT_STATE_STOPPED;
        pppEvent( (HANDLE)p, PPP_EVENT_IPCP_STOPPED );
        goto IPCPExit;

    default:
        break;
    }

    goto IPCPExit;

IPCPStateChange:
    if( p->ipcp.State == PROT_STATE_OPEN )
    {
        /* Check to see if we're connected */
        if( p->ipcp.StateCFG == PROT_CFG_OK && p->ipcp.StateACK == PROT_CFG_OK )
        {
            p->ipcp.State = PROT_STATE_CONNECTED;
            pppEvent( p, PPP_EVENT_IPCP_CONNECT );
        }
    }

IPCPExit:
    if( pPkt )
        PBM_free( pPkt );
}

/*-------------------------------------------------------------------- */
/* ipcpTimer() */
/* Called every second for IPCP timeout */
/*-------------------------------------------------------------------- */
void ipcpTimer( PPP_SESSION *p )
{
    /* What we do depends on our state */
    if( p->ipcp.Timer && !--p->ipcp.Timer )
        switch( p->ipcp.State )
        {
        case PROT_STATE_OPEN:
            /* See if we need a CFG message retry */
            if( p->ipcp.Count )
            {
                p->ipcp.Count--;
                ipcpSendCfg( p );
            }
            else
            {
                p->ipcp.State = PROT_STATE_STOPPED;
                pppEvent( (HANDLE)p, PPP_EVENT_IPCP_STOPPED );
            }
            break;
        }
}

/*-------------------------------------------------------------------- */
/* ipcpSendCfg() */
/* Send a IPCP Configuration Request */
/*-------------------------------------------------------------------- */
static void ipcpSendCfg( PPP_SESSION *p )
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
    p->ipcp.Timer = IPCP_TIMER_CFGRETRY;

    /* Bump the Id */
    p->ipcp.LastId++;

    /* Build the CFG packet */
    pHdr->Code = IPCPCODE_CFGREQ;
    pHdr->Id   = p->ipcp.LastId;

    /* Add options */
    pTagData = pHdr->TagData;
    Len      = SIZE_LCPHDR;

    for( wTmp=1; wTmp<32; wTmp++ )
    {
        if( p->ipcp.UseMask & (1<<wTmp) )
            switch( wTmp )
            {
            case IPCPOPT_IPADDR:
                *pTagData++ = IPCPOPT_IPADDR;
                *pTagData++ = 6;
                if( p->Flags & PPPFLG_SERVER )
                {
                    WrNet32( pTagData, p->IPServer );
                }
                else
                {
                    WrNet32( pTagData, p->IPClient );
                }
                pTagData += 4;
                Len += 6;
                break;

            case HOPT(IPCPOPT_PRI_DNS):
                *pTagData++ = IPCPOPT_PRI_DNS;
                *pTagData++ = 6;
                WrNet32( pTagData, p->IPDNS1 );
                pTagData += 4;
                Len += 6;
                break;

            case HOPT(IPCPOPT_SEC_DNS):
                *pTagData++ = IPCPOPT_SEC_DNS;
                *pTagData++ = 6;
                WrNet32( pTagData, p->IPDNS2 );
                pTagData += 4;
                Len += 6;
                break;

            case HOPT(IPCPOPT_PRI_NBNS):
                *pTagData++ = IPCPOPT_PRI_NBNS;
                *pTagData++ = 6;
                WrNet32( pTagData, p->IPNBNS1 );
                pTagData += 4;
                Len += 6;
                break;

            case HOPT(IPCPOPT_SEC_NBNS):
                *pTagData++ = IPCPOPT_SEC_NBNS;
                *pTagData++ = 6;
                WrNet32( pTagData, p->IPNBNS2 );
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
    p->SICtrl(p->hSI, SI_MSG_SENDPACKET, PPPPROT_IPCP, pPkt );
}

#endif

