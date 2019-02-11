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
 * ======== auth.c ========
 *
 * Authentication functions for PPP/LCP
 *
 */

#include <stkmain.h>
#include <netmain.h>
#include "ppp.h"
#include "md5.h"

#ifdef _INCLUDE_PPP_CODE

#define AUTH_TIMER_TIMEOUT      8
#define AUTH_TIMER_CFGRETRY     3

/* PAP Codes */
#define PAPCODE_REQ     1
#define PAPCODE_ACK     2
#define PAPCODE_NAK     3

/* CHAP Codes */
#define CHAPCODE_CHALLENGE      1
#define CHAPCODE_RESPONSE       2
#define CHAPCODE_SUCCESS        3
#define CHAPCODE_FAILURE        4

static uint authGetPassword( PPP_SESSION *p );
static void papSendCfg( PPP_SESSION *p );
static void chapSendMsg( PPP_SESSION *p, UINT8 Message, UINT8 Id );

/*-------------------------------------------------------------------- */
/* authInit() */
/* Initialize AUTH and set it to CLOSED state */
/*-------------------------------------------------------------------- */
void authInit( PPP_SESSION *p )
{
    char    tmpname[32];
    HANDLE  hName;
    int     rc = 0;
    int     size;

    p->auth.State     = PROT_STATE_CLOSED;

    /* Set options use "best" protocol first */
    if( p->Flags & PPPFLG_OPT_AUTH_CHAP )
        p->auth.Protocol = PPPPROT_CHAP;
    else if( p->Flags & PPPFLG_OPT_AUTH_PAP )
        p->auth.Protocol = PPPPROT_PAP;
    else
        p->auth.Protocol = 0;

    llExit();

    /* (Try to get the authentication name from the registry) */
    rc = CfgGetEntry( 0, CFGTAG_SYSINFO, CFGITEM_SYSINFO_REALMPPP,
                      1, &hName );
    if( rc > 0 )
    {
        size = 31;
        rc = CfgEntryGetData( hName, &size, (UINT8 *)tmpname );
        CfgEntryDeRef( hName );
        if( rc > 0 )
            tmpname[rc]=0;
    }

    llEnter();

    if( rc <= 0 )
        strcpy( p->auth.AuthName, "DSPIP" );
    else
        strcpy( p->auth.AuthName, tmpname );
}

/*-------------------------------------------------------------------- */
/* authStart() */
/* Start AUTH layer */
/*-------------------------------------------------------------------- */
void authStart( PPP_SESSION *p )
{
    /* Set our new state */
    p->auth.State = PROT_STATE_OPEN;

    /* Set some defaults */
    p->auth.LastId = 0;                 /* Default Id */

    /* If PAP, send CFG request */
    if( p->auth.Protocol == PPPPROT_PAP && p->Flags & PPPFLG_CLIENT )
    {
        /* Set our new state */
        p->auth.Count = 5;
        papSendCfg( p );
    }
    /* Else if CHAP server, send challenge */
    else if( p->auth.Protocol == PPPPROT_CHAP && p->Flags & PPPFLG_SERVER )
    {
        /* Set our new state */
        p->auth.Count = 5;
        chapSendMsg( p, CHAPCODE_CHALLENGE, ++p->auth.LastId );
    }
    /* Else set an idle timeout */
    else
    {
        /* Set a timeout for the peer */
        p->auth.Timer = AUTH_TIMER_TIMEOUT;
        p->auth.Count = 0;
    }
}

/*-------------------------------------------------------------------- */
/* authTimer() */
/* Called every second for AUTH timeout */
/*-------------------------------------------------------------------- */
void authTimer( PPP_SESSION *p )
{
    /* What we do depends on our state */
    if( p->auth.Timer && !--p->auth.Timer )
        switch( p->auth.State )
        {
        case PROT_STATE_OPEN:
            /* See if we need a CFG message retry */
            if( p->auth.Count )
            {
                p->auth.Count--;
                if( p->auth.Protocol == PPPPROT_PAP )
                    papSendCfg( p );
                else if( p->auth.Protocol == PPPPROT_CHAP )
                {
                   /* Resend challenge or response */

                   /* If we're a server, we must be resending the challenge */
                   if( p->Flags & PPPFLG_SERVER )
                       chapSendMsg( p, CHAPCODE_CHALLENGE, ++p->auth.LastId );
                   /* Else resend response */
                   else
                       chapSendMsg( p, CHAPCODE_RESPONSE, p->auth.LastId );
                }
            }
            else
            {
                p->auth.State = PROT_STATE_STOPPED;
                pppEvent( (HANDLE)p, PPP_EVENT_AUTH_STOPPED );
            }
            break;
        }
}


/*-------------------------------------------------------------------- */
/* authGetPassword() */
/* Gets the password for the supplied UserId */
/*-------------------------------------------------------------------- */
static uint authGetPassword( PPP_SESSION *p )
{
    CI_ACCT CA;
    uint    index;
    uint    retval = 0;
    int     rc;

    llExit();
    index = 1;
    for(;;)
    {
        rc = CfgGetImmediate( 0, CFGTAG_ACCT, CFGITEM_ACCT_PPP,
                              index, sizeof(CA), (UINT8 *)&CA );
        if( !rc )
            break;
        if( !strcmp( CA.Username, p->UserId ) &&
                          (CA.Flags&p->Flags&PPPFLG_CHMASK) )
        {
            strcpy( p->Password, CA.Password );
            retval = 1;
            break;
        }
        index++;
    }
    llEnter();

    return( retval );
}

/*-------------------------------------------------------------------- */
/* papSendCfg() */
/* Send a AUTH Configuration Request */
/*-------------------------------------------------------------------- */
static void papSendCfg( PPP_SESSION *p )
{
    PBM_Pkt *pPkt;
    LCPHDR  *pHdr;
    UINT16  Len,wTmp;
    UINT8   *pTagData;

    /* Create the packet */
    if( !(pPkt = NIMUCreatePacket(256)) )
        return;

    /* Get a pointer to the new header */
    pHdr = (LCPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Reset the timeout */
    p->auth.Timer = AUTH_TIMER_CFGRETRY;

    /* Bump the Id */
    p->auth.LastId++;

    /* RIGHT NOW, PAP ONLY */

    /* Build the CFG packet */
    pHdr->Code = PAPCODE_REQ;
    pHdr->Id   = p->auth.LastId;

    /* Add options */
    pTagData = pHdr->TagData;
    Len      = SIZE_LCPHDR;

    /* User Id */
    wTmp = strlen( p->UserId );
    *pTagData++ = (UINT8)wTmp;
    mmCopy( pTagData, p->UserId, wTmp );
    pTagData += wTmp;
    Len += wTmp + 1;

    /* Password */
    wTmp = strlen( p->Password );
    *pTagData++ = (UINT8)wTmp;
    mmCopy( pTagData, p->Password, wTmp );
    pTagData += wTmp;
    Len += wTmp + 1;

    pHdr->Length = HNC16(Len);

    /* Send the packet */
    pPkt->ValidLen = Len;
    p->SICtrl(p->hSI, SI_MSG_SENDPACKET, PPPPROT_PAP, pPkt );
}

/*-------------------------------------------------------------------- */
/* papInput() */
/* Packet input function for PAP */
/*-------------------------------------------------------------------- */
void papInput( PPP_SESSION *p, PBM_Pkt *pPkt )
{
    LCPHDR      *pHdr;
    UINT16      Len;
    UINT8       *pTagData;
    UINT8       c;
    char        Password[PPPNAMELEN];

    /* If we're anything but open, discard the packet */
    if( p->auth.State != PROT_STATE_OPEN  || !pPkt )
        goto PAPExit;

    /* Get a pointer to the new header */
    pHdr = (LCPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Get packet length */
    Len  = HNC16( pHdr->Length );

    /* Verify that we have the entire packet */
    if( Len > (UINT16)pPkt->ValidLen )
        goto PAPExit;

    switch( pHdr->Code )
    {
    case PAPCODE_REQ:
        /*--------------------- */
        /* Authentication-Request */
        /*--------------------- */
        if( !(p->Flags & PPPFLG_SERVER) )
            goto AUTH_REJECT;

        pTagData = pHdr->TagData;

        /* Get UserId and write into instance structure */
        c = *pTagData++;
        if( c >= PPPNAMELEN )
            goto AUTH_REJECT;
        mmCopy( p->UserId, pTagData, c );
        p->UserId[c] = 0;
        pTagData += c;

        /* Get Password and write into temp string */
        c = *pTagData++;
        if( c >= PPPNAMELEN )
            goto AUTH_REJECT;
        mmCopy( Password, pTagData, c );
        Password[c] = 0;
        pTagData += c;

        /* The the real password in tht user structure and compare to supplied */
        if( authGetPassword(p) && !strcmp( Password, p->Password ) )
        {
            /* Ack this authentication */
            pHdr->Code   = PAPCODE_ACK;
            pHdr->Length = HNC16(SIZE_LCPHDR);

            /* Send the packet */
            pPkt->ValidLen = SIZE_LCPHDR;
            p->SICtrl(p->hSI, SI_MSG_SENDPACKET, PPPPROT_PAP, pPkt );
            pPkt = 0;

            p->auth.State = PROT_STATE_CONNECTED;
            pppEvent( (HANDLE)p, PPP_EVENT_AUTH_CONNECT );
            break;
        }

AUTH_REJECT:
        pHdr->Code   = PAPCODE_NAK;
        pHdr->Length = HNC16(SIZE_LCPHDR);

        /* Send the packet */
        pPkt->ValidLen = SIZE_LCPHDR;
        p->SICtrl(p->hSI, SI_MSG_SENDPACKET, PPPPROT_PAP, pPkt );
        pPkt = 0;

        p->auth.State = PROT_STATE_STOPPED;
        pppEvent( (HANDLE)p, PPP_EVENT_AUTH_STOPPED );
        break;

    case PAPCODE_ACK:
        if( (p->Flags & PPPFLG_CLIENT) && pHdr->Id == p->auth.LastId )
        {
            p->auth.State = PROT_STATE_CONNECTED;
            pppEvent( (HANDLE)p, PPP_EVENT_AUTH_CONNECT );
        }
        break;

    case PAPCODE_NAK:
        if( pHdr->Id == p->auth.LastId )
        {
            p->auth.State = PROT_STATE_STOPPED;
            pppEvent( (HANDLE)p, PPP_EVENT_AUTH_STOPPED );
        }
        break;

    default:
        break;
    }

PAPExit:
    if( pPkt )
        PBM_free( pPkt );
}


/*-------------------------------------------------------------------- */
/* chapSendMsg() */
/* Send a CHAP message */
/*-------------------------------------------------------------------- */
static void chapSendMsg( PPP_SESSION *p, UINT8 Message, UINT8 Id )
{
    PBM_Pkt *pPkt;
    LCPHDR  *pHdr;
    UINT16  Len;
    UINT8   *pTagData;
    UINT32  Tmp;
    char    *pstrTmp;

    /* Create the packet */
    if( !(pPkt = NIMUCreatePacket( 256 )) )
        return;

    /* Get a pointer to the new header */
    pHdr = (LCPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Build the CFG packet */
    pHdr->Code = Message;
    pHdr->Id   = Id;

    /* Add options */
    pTagData = pHdr->TagData;
    Len      = SIZE_LCPHDR;

    if( pHdr->Code <= CHAPCODE_RESPONSE )
    {
        /* Reset the timeout */
        p->auth.Timer = AUTH_TIMER_CFGRETRY;

        /* If this is a challenge, re-seed the challenge data */
        if( pHdr->Code == CHAPCODE_CHALLENGE )
        {
            Tmp = llTimerGetTime(0);
            mmCopy( p->auth.SeedData, &Tmp, 4);
            mmCopy( p->auth.SeedData+4, &Tmp, 4);
            mmCopy( p->auth.SeedData+8, p->auth.SeedData, 8);
            p->auth.SeedLen = 16;
            pstrTmp = p->auth.AuthName;
        }
        else
            pstrTmp = p->UserId;

        /* Challenge data */
        *pTagData++ = p->auth.SeedLen;
        mmCopy( pTagData, p->auth.SeedData, p->auth.SeedLen );
        pTagData += p->auth.SeedLen;
        Len += p->auth.SeedLen + 1;

        /* Userid */
        Tmp = strlen( pstrTmp );
        mmCopy( pTagData, pstrTmp, Tmp );
        pTagData += Tmp;
        Len += (UINT16)Tmp;
    }

    pHdr->Length = HNC16(Len);

    /* Send the packet */
    pPkt->ValidLen = Len;
    p->SICtrl(p->hSI, SI_MSG_SENDPACKET, PPPPROT_CHAP, pPkt );
}

/*-------------------------------------------------------------------- */
/* chapInput() */
/* Packet input function for CHAP */
/*-------------------------------------------------------------------- */
void chapInput( PPP_SESSION *p, PBM_Pkt *pPkt )
{
    LCPHDR      *pHdr;
    int         TagLen;
    UINT16      Len;
    UINT8       *pTagData;
    UINT8       c;
    UINT8       KeyResults[32];
    UINT8       KeyInput[32+PPPNAMELEN+2];
    UINT8       *pKeyData;
    int         KeyLen;
    uint        ChallengeLen;
    MD5_CTX     context;              /* context */

    /* If we're not open or connected, discard packet */
    if( (p->auth.State != PROT_STATE_OPEN &&
         p->auth.State != PROT_STATE_CONNECTED) || !pPkt )
        goto CHAPExit;

    /* Get a pointer to the new header */
    pHdr = (LCPHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Get packet length */
    Len  = HNC16( pHdr->Length );

    /* Verify that we have the entire packet */
    if( Len > (UINT16)pPkt->ValidLen )
        goto CHAPExit;

    /* Get pointer to tag data and length */
    pTagData = pHdr->TagData;
    TagLen   = (int)(Len - SIZE_LCPHDR);

    switch( pHdr->Code )
    {
    case CHAPCODE_CHALLENGE:
        /* Only handle challenge request if client */
        if( !(p->Flags & PPPFLG_CLIENT) )
            break;

        /* Get challenge data */
        ChallengeLen = *pTagData++;

        /* We expect 16 to 32 bytes */
        if( ChallengeLen<16 || ChallengeLen>32 )
            break;

        /* Copy Id and Password into key input */
        pKeyData = KeyInput;
        *pKeyData++ = pHdr->Id;
        KeyLen = strlen( p->Password );
        mmCopy( pKeyData, p->Password, KeyLen );

        /* Apply encryption */
        MD5Init( &context );
        MD5Update( &context, KeyInput, KeyLen+1 );
        MD5Update( &context, pTagData, ChallengeLen );
        MD5Final( p->auth.SeedData, &context );
        p->auth.SeedLen = ChallengeLen;

        /* Send response */
        p->auth.Count  = 5;               /* Retry Count */
        p->auth.LastId = pHdr->Id;
        chapSendMsg( p, CHAPCODE_RESPONSE, p->auth.LastId );
        break;

    case CHAPCODE_RESPONSE:
        /* Only handle challenge response if server */
        if( !(p->Flags & PPPFLG_SERVER) )
            break;

        /* Only examine response to most recent challenge */
        if( pHdr->Id != p->auth.LastId )
            break;

        /* Get challenge data */
        c = *pTagData++;

        /* We expect 16 bytes */
        if( c != 16 )
            goto AUTH_FAIL;

        /* Get UserId */
        TagLen -= 17;
        if( TagLen<1 || TagLen>=PPPNAMELEN )
            goto AUTH_FAIL;
        mmCopy( p->UserId, pTagData+16, TagLen );
        p->UserId[TagLen] = 0;

        /* Get the password for this user */
        if( !authGetPassword(p) )
            goto AUTH_FAIL;

        /* Copy Id and Password into key input */
        pKeyData = KeyInput;
        *pKeyData++ = pHdr->Id;
        KeyLen = strlen( p->Password );
        mmCopy( pKeyData, p->Password, KeyLen );

        /* Apply encryption */
        MD5Init( &context );
        MD5Update( &context, KeyInput, KeyLen+1 );
        MD5Update( &context, p->auth.SeedData, 16 );
        MD5Final( KeyResults, &context );

        /* Compare */
        for( c=0; c<16; c++ )
            if( KeyResults[c] != *(pTagData+c) )
                goto AUTH_FAIL;

        /* Send success */
        chapSendMsg( p, CHAPCODE_SUCCESS, p->auth.LastId );
        if( p->auth.State == PROT_STATE_OPEN )
        {
            p->auth.State = PROT_STATE_CONNECTED;
            pppEvent( (HANDLE)p, PPP_EVENT_AUTH_CONNECT );
        }
        break;

AUTH_FAIL:
        chapSendMsg( p, CHAPCODE_FAILURE, p->auth.LastId );
        p->auth.State = PROT_STATE_STOPPED;
        pppEvent( (HANDLE)p, PPP_EVENT_AUTH_STOPPED );
        break;

    case CHAPCODE_SUCCESS:
        if( (p->Flags & PPPFLG_CLIENT) &&
            pHdr->Id == p->auth.LastId &&
            p->auth.State == PROT_STATE_OPEN )
        {
            p->auth.State = PROT_STATE_CONNECTED;
            pppEvent( (HANDLE)p, PPP_EVENT_AUTH_CONNECT );
        }
        break;

    case CHAPCODE_FAILURE:
        if( pHdr->Id == p->auth.LastId )
        {
            p->auth.State = PROT_STATE_STOPPED;
            pppEvent( (HANDLE)p, PPP_EVENT_AUTH_STOPPED );
        }
        break;

    default:
        break;
    }

CHAPExit:
    PBM_free( pPkt );
}

#endif

