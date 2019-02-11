/*
 * Copyright (c) 2014, Texas Instruments Incorporated
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
 * ======== conping.c ========
 *
 * Raw sockets example program - PING
 *
 */

#include <netmain.h>
#include <_stack.h>                     /* For packet headers only */
#include "console.h"

#define MAXPACKET       1000     /* max packet size */
#define PING_IDENT      0x1234      /* Ping Id */
#define NROUTES         9           /* number of record route slots */
#define DATALEN         100     /* default data length */

static void BuildPing( char *pBuf, UINT16 seq );
static int  CheckPing( char *pBuf, UINT16 sSeq, int cc, struct sockaddr_in *from);
static void Ping( IPN IPAddr, int rrop );

/*------------------------------------------------------------------------- */
/* ConCmdPing() */
/* Function to send ICMP ping request */
/*------------------------------------------------------------------------- */
void ConCmdPing( int ntok, char *tok1, char *tok2 )
{
    IPN IPPing;
    int rrop = 0;

    /* Check for 'ping /r x.x.x.x' */
    if( ntok == 2 && !stricmp( tok1, "/r" ) )
    {
        rrop = 1;
        ntok = 1;
        tok1 = tok2;
    }

    /* Check for 'ping x.x.x.x' */
    if( ntok == 1 )
    {
       if( !ConStrToIPN( tok1, &IPPing ) )
           ConPrintf("Invalid address\n\n");
       else
           Ping( IPPing, rrop );
    }
    else if( !ntok )
    {
        ConPrintf("\n[Ping Command]\n");
        ConPrintf("\nCalled to generate ICMP echo requests\n\n");
        ConPrintf("ping x.x.x.x     - Ping IP address\n");
        ConPrintf("ping /r 1.2.3.4  - Ping IP address with record route\n");
        ConPrintf("ping hostname    - Resolve 'hostname' and ping\n\n");
    }
    else
        ConPrintf("\nCommand error. Type 'ping' for help\n");
}

static void Ping( IPN IPAddr, int rrop )
{
    char    rspace[3 + 4 * NROUTES + 1];    /* Record Route Space */
    char    IpStr[24];
    fd_set  ibits;
    int     cc,fromlen;
    UINT16  cnt_send=0, cnt_recv=0;         /* Packets send and received */
    SOCKET  s;                              /* ICMP socket file descriptor */
    struct  sockaddr_in to;                    /* who to ping */
    struct  sockaddr_in from;                  /* who replied */
    char    *pBuf = 0;
    struct  timeval timeout;                /* Timeout struct for select */
    UINT32  timestart;

    /* Create the ICMP Socket */
    s = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if( s == INVALID_SOCKET )
    {
        ConPrintf("failed socket create (%d)\n",fdError());
        goto pingleave;
    }

    /* Create to "to" address */
    bzero( &to, sizeof(struct sockaddr_in));
    to.sin_family       = AF_INET;
    to.sin_addr.s_addr  = IPAddr;

    /* Create to "from" address */
    bzero( &from, sizeof(struct sockaddr_in));
    from.sin_family     = AF_INET;

    if( rrop )
    {
        /* Add options to IP Header to Record Route */
        rspace[IPOPT_OPTVAL] = IPOPT_RR;
        rspace[IPOPT_OLEN]   = sizeof(rspace);
        rspace[IPOPT_OFFSET] = IPOPT_MINOFF;
        if(setsockopt(s, IPPROTO_IP, IP_OPTIONS, rspace, sizeof(rspace)) < 0)
        {
            ConPrintf("failed set IP options (%d)\n",fdError());
            goto pingleave;
        }
    }

    /* Set socket option to allow us to broadcast */
    cc = 1;
    if( setsockopt( s, SOL_SOCKET, SO_BROADCAST, &cc, sizeof(int) ) < 0 )
    {
        ConPrintf("failed set IP broadcast (%d)\n",fdError());
        goto pingleave;
    }

    /* Configure our timeout to be 0.5 seconds */
    timeout.tv_sec  = 0;
    timeout.tv_usec = 500000;

    /* Allocate a working buffer */
    if( !(pBuf = mmBulkAlloc( MAXPACKET )) )
    {
        ConPrintf("failed allocate working buffer\n");
        goto pingleave;
    }

    /* Print opening remark */
    NtIPN2Str( IPAddr, IpStr );
    ConPrintf("Pinging %s with %d data bytes\n\n", IpStr, DATALEN-8 );

    /* Ping loop */
    while( cnt_send < 5 )
    {
        /* Use send count for sequence - starts at "1" */
        cnt_send++;

        /* Build the ping packet */
        BuildPing( pBuf, cnt_send );

        /* Get the time now */
        timestart = llTimerGetTime(0);
        cnt_recv = 0;

        /* Send the ping */
        cc = sendto( s, pBuf, DATALEN, 0,(struct sockaddr *)&to, sizeof(to) );
        if( cc < 0 )
            ConPrintf("failed sento (%d)\n",fdError());
        else if( cc != DATALEN )
            ConPrintf("sento - partial write!\n");

again:
        /* Select for timeout period second */
        FD_ZERO(&ibits);
        FD_SET(s, &ibits);
        if( fdSelect( (int)s, &ibits, 0, 0, &timeout ) < 0 )
        {
            ConPrintf("failed select (%d)\n",fdError());
            goto pingleave;
        }

        /* Check for a reply */
        if( FD_ISSET(s, &ibits) )
        {
            fromlen = sizeof(from);
            cc = (int)recvfrom( s, pBuf, MAXPACKET, 0,(struct sockaddr *)&from, &fromlen );
            if( cc < 0 )
            {
                ConPrintf("failed recvfrom (%d)\n",fdError());
                goto pingleave;
            }

            /* Check the reply. Bump the recv count if good reply */
            if( CheckPing( pBuf, cnt_send, cc, &from ) )
                cnt_recv++;
        }

        /* Check for about 2 seconds */
        if( (timestart+2) > llTimerGetTime(0) )
            goto again;


        /* If send is more than reply, then we missed a reply */
        if( !cnt_recv )
            ConPrintf("Reply timeout\n");
        else
            ConPrintf("\n");
    }

pingleave:
    if( pBuf )
        mmBulkFree( pBuf );
    if( s != INVALID_SOCKET )
        fdClose( s );

    ConPrintf("\n");
}

static void BuildPing( char *pBuf, UINT16 seq )
{
    ICMPHDR    *pIcHdr;
    ICMPREQHDR *pReqHdr;
    int        cc;

    /* Fill in the ping data buffer */
    for( cc = 8; cc < DATALEN; cc++ )
        *(pBuf+cc) = '0'+cc;

    /* Get pointers to the ICMP and ICMPREQ headers */
    pIcHdr  = (ICMPHDR *)pBuf;
    pReqHdr = (ICMPREQHDR *)pIcHdr->Data;

    /* Fill out echo request */
    pIcHdr->Type   = ICMP_ECHO;
    pIcHdr->Code   = 0;
    pReqHdr->Id    = HNC16(PING_IDENT);
    pReqHdr->Seq   = HNC16(seq);

    /* Checksum the ICMP header */
    /* Although the checksum function is reentrant, we follow the rules */
    /* and call llEnter()/llExit() since this is a stack function. */
    llEnter();
    ICMPChecksum( pIcHdr, DATALEN );
    llExit();
}

static int CheckPing( char *pBuf,UINT16 sSeq,int cc,struct sockaddr_in *from )
{
    char       IpStr[24];
    ICMPHDR    *pIcHdr;
    ICMPREQHDR *pReqHdr;
    IPHDR      *pIpHdr;
    int        IPHdrLen;
    int        ICMPLen;
    UINT16     Id,Seq;
    int        i,j,size;
    UINT8      *cp,*cpMark;
    UINT32     l;

    /* Get header pointers */
    pIpHdr   = (IPHDR *)pBuf;
    IPHdrLen = (pIpHdr->VerLen & 0xF) * 4;
    pIcHdr   = (ICMPHDR *)(pBuf+IPHdrLen);
    pReqHdr  = (ICMPREQHDR *)pIcHdr->Data;

    /* Get the total length of the ICMP message */
    ICMPLen = (uint)(HNC16( pIpHdr->TotalLen )) - IPHdrLen;

    /* Verify the ICMP type */
    if( pIcHdr->Type != ICMP_ECHOREPLY )
        return(0);

    /* Get the seq and the id */
    Seq = (int)HNC16(pReqHdr->Seq);
    Id  = (int)HNC16(pReqHdr->Id);

    /* Get an ASCII string of who replied */
    NtIPN2Str( from->sin_addr.s_addr, IpStr );

    /* If the reply is incorrect, don't continue */
    if( Id != PING_IDENT || Seq != sSeq )
    {
        ConPrintf("Non-matching echo reply from %s\n", IpStr);
        return(0);
    }

    /* Print out data on correct reply */
    ConPrintf("Reply from %s, %d bytes, Seq=%u, TTL = %d\n",
                                           IpStr, ICMPLen-8, Seq, pIpHdr->Ttl);

    /* Validate the data payload */
    if( ICMPLen != DATALEN )
        ConPrintf("Data length error in reply (%d of %d)\n",cc,DATALEN);
    for( cc = 8; cc < DATALEN; cc++ )
        if( *(UINT8 *)((pBuf+IPHdrLen+cc)) != (UINT8)('0'+cc) )
        {
            ConPrintf("Data verification error in reply (%d 0x%x 0x%x)\n", cc, *(UINT8 *)((pBuf+IPHdrLen+cc)), '0'+cc );
            break;
        }

    /* Display any IP Header options */
    cp = (UINT8 *)pBuf + IPHDR_SIZE;

    for (; IPHdrLen > IPHDR_SIZE; --IPHdrLen, ++cp)
    {
        switch (*cp)
        {
        case IPOPT_EOL:
            IPHdrLen = 0;
            break;
        case IPOPT_LSRR:
        case IPOPT_SSRR:
            (void)ConPrintf("SSRR/LSRR: ");
            cpMark = cp;
            size = j = *++cp;
            ++cp;
            if (j > IPOPT_MINOFF)
                for (;;)
                {
                    l  = (UINT32)(*(cp)) << 24;
                    l |= (UINT32)(*(cp+1)) << 16;
                    l |= (UINT32)(*(cp+2)) << 8;
                    l |= (UINT32)(*(cp+3));
                    cp+=4;
                    NtIPN2Str( htonl(l), IpStr );
                    ConPrintf("%s ",IpStr);
                    j -= 4;
                    if (j <= IPOPT_MINOFF)
                        break;
                }
            ConPrintf("\n");
            cp = cpMark + size;
            IPHdrLen -= size;
            break;

        case IPOPT_RR:
            cpMark = cp;
            size = j = *++cp;
            i = *++cp;              /* pointer */
            ++cp;                   /* Pad */
            if (i > j)
                i = j;
            i -= IPOPT_MINOFF;
            if (i <= 0)
                goto contRR;
            (void)ConPrintf("RR: ");
            for (;;)
            {
                l  = (UINT32)(*(cp)) << 24;
                l |= (UINT32)(*(cp+1)) << 16;
                l |= (UINT32)(*(cp+2)) << 8;
                l |= (UINT32)(*(cp+3));
                cp += 4;
                NtIPN2Str( htonl(l), IpStr );
                ConPrintf("%s ",IpStr);
                i -= 4;
                if (i <= 0)
                    break;
            }
            ConPrintf("\n");
        contRR:
            cp = cpMark + size;
            IPHdrLen -= size;
            break;

        case IPOPT_NOP:
            ConPrintf("NOP\n");
            break;
        default:
            ConPrintf("unknown option %x\n", *cp);
            break;
        }
    }
    return(1);
}

