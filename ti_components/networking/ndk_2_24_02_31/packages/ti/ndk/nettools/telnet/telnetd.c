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
 * ========  ========
 *
 * Telnet Server Utility
 *
 */

#include "telnet.h"

/* Some instance and buffering limits */
#define BUFSIZE     512

/* Application Supplies Echo */
#define APP_ECHO        1

/* Data specific to a telnet connection task */

typedef struct _ti {
        UINT8       options[256];

        SOCKET      sNet;                  /* Socket to Telnet client */
        SOCKET      sTerm;                 /* Socket to Terminal */

        int         InputState;            /* Status of input processing */

        UINT8       tnet[BUFSIZE];         /* Data ready for NET */
        int         tnetcnt;
        UINT8       fterm[BUFSIZE];        /* Raw data from terminal */
        int         ftermcnt;
        int         ftermridx;             /* Read index */
        UINT8       fnet[BUFSIZE];         /* Raw data from network */
        int         fnetcnt;
        int         fnetridx;              /* Read index */
        UINT8       tterm[BUFSIZE];        /* Data ready for terminal */
        int         ttermcnt;
} TINSTANCE;


/* 
 * TelnetOpen
 * Create an instance of the Telnet Server
 */
HANDLE TelnetOpen( NTARGS *pNTA, NTPARAM_TELNET *pNTP )
{
    HANDLE hEntry;
    IPN    IpAddr;

    if( !pNTA || !pNTP )
        return(0);

    /* Check for called by address */
    if( pNTA->CallMode == NT_MODE_IPADDR )
        IpAddr = pNTA->IPAddr;
    /* Check for called by IfIfx */
    else if( pNTA->CallMode == NT_MODE_IFIDX )
    {
        if( !NtIfIdx2Ip( pNTA->IfIdx, &IpAddr ) )
            return(0);
    }
    else
        return(0);

    if ( !pNTP->Callback )
        return(0);

    if( !pNTP->MaxCon )
        pNTP->MaxCon = 4;

    if( !pNTP->Port )
        pNTP->Port = 23;

    hEntry = DaemonNew( SOCK_STREAM, IpAddr, pNTP->Port,
                        (int(*)(SOCKET,UINT32))telnetClientProcess,
                        OS_TASKPRINORM, OS_TASKSTKLOW,
                        (UINT32)(pNTP->Callback), pNTP->MaxCon );

    return( hEntry );
}

/* 
 * TelnetClose
 *
 * Destroy an instance of the Telnet Server
 */
void TelnetClose( HANDLE h )
{
    DaemonFree( h );
}


static void telnet_engine( TINSTANCE *pti );
static int  CmdWriteBytes( TINSTANCE *pti, UINT8 *pData, int len );
static int  CmdWriteCmd( TINSTANCE *pti, UINT8 cmd, UINT8 opt );
static void telnet_termdata( TINSTANCE *pti );
static void telnet_netdata( TINSTANCE *pti );

/* 
 * telnetClientProcess()
 *
 * Connects to terminal via callback and initiates telnet
 */
int telnetClientProcess( SOCKET s, SOCKET (*cbfn)(PSA) )
{
#ifdef _INCLUDE_IPv6_CODE
    struct sockaddr_in6 sin1;
#else
    struct sockaddr_in  sin1;
#endif
    int                tmp1;
    TINSTANCE          *pti;

    /* Alloc our instance structure */
    pti = mmBulkAlloc( sizeof(TINSTANCE) );

    /* If the alloc failed, abort */
    if( !pti )
        return(1);

    /* Initialize the instance structure */
    bzero( pti, sizeof(TINSTANCE) );
    pti->sNet = s;

    /* Initialize socket defaults (sNet is already initialized) */
    pti->sTerm = INVALID_SOCKET;

    /* Create Local Connection */

    /* First, find out who we're connected to */
    tmp1 = sizeof( sin1 );
    getpeername( pti->sNet,(struct sockaddr *)&sin1, &tmp1 );

    /* Call the callback function with the peer name */
    /* and get our terminal socket */
    if( (pti->sTerm = cbfn((struct sockaddr *)&sin1 )) == INVALID_SOCKET )
        goto leave;

    /* Initialize Connection Instance */

    /* Set the default state of the options we do use */
    pti->options[OPT_BINARY] = OS_WONT | OS_DONT;
    pti->options[OPT_ECHO  ] = OS_WILL | OS_DONT;
    pti->options[OPT_SGA   ] = OS_WILL | OS_DONT;
    pti->options[OPT_STATUS] = OS_WONT | OS_DONT;
    pti->options[OPT_TM    ] = OS_WONT | OS_DONT;
    pti->options[OPT_EXOPL ] = OS_WONT | OS_DONT;

    /* Tell the other side our configuration preferences */
    CmdWriteCmd( pti, CMD_WILL, OPT_ECHO );
    CmdWriteCmd( pti, CMD_WILL, OPT_SGA );

    /* Start Telnet */
    telnet_engine( pti );

leave:
    /* telnet task is dead, and we need to clean up the sockets. */
    if( pti->sTerm != INVALID_SOCKET )
        fdClose(pti->sTerm);

    mmBulkFree(pti);

    /* Return "1" since the original socket is still open */
    return(1);
}

static int CmdWriteBytes( TINSTANCE *pti, UINT8 *pData, int len )
{
    if( (pti->tnetcnt+len) > BUFSIZE )
        return(0);
    while(len--)
        pti->tnet[pti->tnetcnt++] = *pData++;
    return(1);
}

static int CmdWriteCmd( TINSTANCE *pti, UINT8 cmd, UINT8 opt )
{
    if( (pti->tnetcnt+3) > BUFSIZE )
        return(0);
    pti->tnet[pti->tnetcnt++] = CMD_IAC;
    pti->tnet[pti->tnetcnt++] = cmd;
    pti->tnet[pti->tnetcnt++] = opt;
    return(1);
}

static void telnet_engine( TINSTANCE *pti )
{
    int quit = 0;

    for(;;)
    {
        /* If there is data from the telnet peer to process, do so */
        if( pti->fnetcnt )
            telnet_netdata( pti );

        /* If there is data to send to terminal, send it */
        if( pti->ttermcnt )
        {
            if( send( pti->sTerm, pti->tterm, pti->ttermcnt, 0 ) < 0 )
                quit = 1;
            pti->ttermcnt = 0;
        }

        /* If there is data from the terminal, process it */
        if( pti->ftermcnt )
            telnet_termdata( pti );

        /* If there is data to send to telnet peer, send it */
        if( pti->tnetcnt )
        {
            if( send( pti->sNet, pti->tnet, pti->tnetcnt, 0 ) < 0 )
                quit = 1;
            pti->tnetcnt = 0;
        }

        /* If everyone is idle, drop into a select call. */
        if( !pti->tnetcnt && !pti->ttermcnt &&
                          !pti->fnetcnt && !pti->ftermcnt )
        {
            fd_set ibits;
            int    c;

            if( quit )
                break;

            FD_ZERO(&ibits);

            FD_SET( pti->sNet, &ibits );
            FD_SET( pti->sTerm, &ibits );

            c = fdSelect( (int)(pti->sTerm)+1, &ibits, 0, 0, (struct timeval *)0 );
            if( c < 0 )
                break;

            /* Read new data from the network */
            if( FD_ISSET(pti->sNet, &ibits) )
            {
                c = recv( pti->sNet, pti->fnet, BUFSIZE, 0 );
                if( c <= 0 )
                    quit = 1;
                else
                    pti->fnetcnt = c;
                pti->fnetridx = 0;
            }

            /* Read new data from the terminal */
            if( FD_ISSET(pti->sTerm, &ibits) )
            {
                c = recv( pti->sTerm, pti->fterm, BUFSIZE, 0 );
                if( c <= 0 )
                    quit = 1;
                else
                    pti->ftermcnt = c;
                pti->ftermridx = 0;
            }
        }
    }
}

/* Some MACROS to use with our "pti" variable */

#define IS_WONT(x)              (!(pti->options[(x)]&OS_WILL))
#define IS_WILL(x)              (pti->options[(x)]&OS_WILL)
#define IS_DONT(x)              (!(pti->options[(x)]&OS_DO))
#define IS_DO(x)                (pti->options[(x)]&OS_DO)

#define SET_WONT(x)             (pti->options[(x)]&=~OS_WILL)
#define SET_WILL(x)             (pti->options[(x)]|=OS_WILL)
#define SET_DONT(x)             (pti->options[(x)]&=~OS_DO)
#define SET_DO(x)               (pti->options[(x)]|=OS_DO)

/* Status of Telnet Input Processing */
#define TOK_NORMAL      0   /* Normal operation */
#define TOK_IAC         1   /* rcvd IAC */
#define TOK_CR          2   /* rcvd CR */
#define TOK_SB          3   /* In SB/SE Pairing */
#define TOK_WILL        4   /* rcvd will */
#define TOK_WONT        5   /* rcvd wont */
#define TOK_DO          6   /* rcvd do */
#define TOK_DONT        7   /* rcvd dont */

static void telnet_netdata( TINSTANCE *pti )
{
    UINT8 data;

    /* Process data from the network */
    while( pti->fnetridx < pti->fnetcnt )
    {
        data = pti->fnet[pti->fnetridx++];

        switch( pti->InputState )
        {
        case TOK_NORMAL:
            /* Under normal operation, we channel the charater to */
            /* the terminal. We may also echo it back to the sender */
            if( data == CMD_IAC )
            {
                pti->InputState = TOK_IAC;
                break;
            }

            /* Copy the data to the output buffer */

            /* Must be able to fit in output buffer */
            if( (pti->ttermcnt+2) > BUFSIZE )
                goto abort;

            /* If echoing, the character must also fit in tnetcnt */
            if( IS_WILL(OPT_ECHO) && (pti->tnetcnt+2) > BUFSIZE )
                goto abort;

            /* Write to terminal */
            pti->tterm[pti->ttermcnt++] = data;

#if !APP_ECHO
            /* Echo back to network */
            if( IS_WILL(OPT_ECHO) )
                pti->tnet[pti->tnetcnt++] = data;
#endif

            if( data == '\r' && IS_DONT(OPT_BINARY) )
                pti->InputState = TOK_CR;
            break;

        case TOK_IAC:
            switch( data )
            {
            case CMD_IAC:
                /* Copy the data to the output buffer */

                /* Must be able to fit in output buffer */
                if( (pti->ttermcnt+2) > BUFSIZE )
                    goto abort;

                /* If echoing, the character must also fit in tnetcnt */
                if( IS_WILL(OPT_ECHO) && (pti->tnetcnt+2) > BUFSIZE )
                    goto abort;

                /* Write to terminal */
                pti->tterm[pti->ttermcnt++] = data;

#if !APP_ECHO
                /* Echo double sequence back to network */
                if( IS_WILL(OPT_ECHO) )
                {
                    pti->tnet[pti->tnetcnt++] = data;
                    pti->tnet[pti->tnetcnt++] = data;
                }
#endif

                pti->InputState = TOK_NORMAL;
                break;

            case CMD_AYT:
                if( !CmdWriteBytes( pti, (UINT8 *)"YES", 3 ) )
                    goto abort;
                pti->InputState = TOK_NORMAL;
                break;

            case CMD_SB:
                pti->InputState = TOK_SB;
                break;

            case CMD_SE:
                pti->InputState = TOK_NORMAL;
                break;

            case CMD_WILL:
                pti->InputState = TOK_WILL;
                break;

            case CMD_WONT:
                pti->InputState = TOK_WONT;
                break;

            case CMD_DO:
                pti->InputState = TOK_DO;
                break;

            case CMD_DONT:
                pti->InputState = TOK_DONT;
                break;

            default:
                pti->InputState = TOK_NORMAL;
                break;
            }
            break;

        case TOK_CR:
            /* If "\r\0", eat the '\0'. Let "\r\n" go through */
            if( data != 0 )
                pti->fnetridx--;
#if !APP_ECHO
            else
            {
                /* Still Echo back to network */
                if( IS_WILL(OPT_ECHO) )
                    pti->tnet[pti->tnetcnt++] = data;
            }
#endif
            pti->InputState = TOK_NORMAL;
            break;

        case TOK_SB:
            if( data != CMD_IAC )
                break;
            pti->InputState = TOK_IAC;
            break;

        case TOK_WILL:
            /* Other side saying "WILL: something". The only thing */
            /* we agree to turn "on" is SGA & BINARY. We'll ignore */
            /* timing mark since "WILL" is a reply. */
            /* We reply to everything else with DONT */
            if( data == OPT_BINARY || data == OPT_SGA )
            {
                if( IS_DONT(data) )
                {
                    if( !CmdWriteCmd( pti, CMD_DO, data ) )
                        goto abort;
                    SET_DO(data);
                }
            }
            else if( data != OPT_TM )
            {
                if( !CmdWriteCmd( pti, CMD_DONT, data ) )
                    goto abort;
            }
            pti->InputState = TOK_NORMAL;
            break;

        case TOK_WONT:
            /* Other side saying "WONT: something". We don't care */
            /* what it is - we just change the state. */
            if( IS_DO(data) )
            {
                if( !CmdWriteCmd( pti, CMD_DONT, data ) )
                    goto abort;
                SET_DONT(data);
            }
            pti->InputState = TOK_NORMAL;
            break;

        case TOK_DO:
            /* Other side saying "DO: something". The only thing */
            /* we agree to turn "on" is SGA, BINARY or ECHO. */
            /* We'll always reply to timing mark with "WILL". */
            /* We don't reply to anything else since nothing else */
            /* can possible be in an "on" state */
            if( data == OPT_BINARY || data == OPT_SGA ||
                data == OPT_ECHO || data == OPT_TM )
            {
                if( IS_WONT(data) )
                {
                    if( !CmdWriteCmd( pti, CMD_WILL, data ) )
                        goto abort;
                    if( data != OPT_TM )
                        SET_WILL(data);
                }
            }
            pti->InputState = TOK_NORMAL;
            break;

        case TOK_DONT:
            /* Other side saying "DONT: something". We can turn */
            /* anything "off". */
            if( IS_WILL(data) )
            {
                if( !CmdWriteCmd( pti, CMD_WONT, data ) )
                    goto abort;
                SET_WONT(data);
            }
            pti->InputState = TOK_NORMAL;
            break;

        default:
            pti->InputState = TOK_NORMAL;
            break;
        }
    }
    pti->fnetcnt = 0;
    return;

abort:
    /* Back up one character */
    pti->fnetridx--;
    return;
}

static void telnet_termdata( TINSTANCE *pti )
{
    UINT8 data;

    /* Process data from the terminal */
    while( pti->ftermridx < pti->ftermcnt )
    {
        data = pti->fterm[pti->ftermridx++];

        /* Must be able to fit in output buffer */
        if( (pti->tnetcnt+2) > BUFSIZE )
            goto abort;

        /* Write to network */

        /* All '\n' becomes '\r\n' */
        /* All '\r' becomes '\rNUL' */
        /* All [CMD_IAC] becomes [CMD_IAC][CMD_IAC] */

        if( data == '\n' && IS_WONT(OPT_BINARY) )
            pti->tnet[pti->tnetcnt++] = '\r';

        pti->tnet[pti->tnetcnt++] = data;

        if( data == CMD_IAC )
            pti->tnet[pti->tnetcnt++] = CMD_IAC;

        if( data == '\r' && IS_WONT(OPT_BINARY) )
            pti->tnet[pti->tnetcnt++] = 0;
    }

    pti->ftermcnt = 0;
    return;

abort:
    pti->ftermridx--;
    return;
}
