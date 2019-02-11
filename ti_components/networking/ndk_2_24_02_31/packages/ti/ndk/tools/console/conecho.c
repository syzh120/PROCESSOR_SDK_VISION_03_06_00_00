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
 * ======== conecho.c ========
 *
 * Example TCP/UDP sockets program - ECHO
 *
 */

#include <netmain.h>
#include "console.h"

static void EchoTcp( IPN IPAddr );
static void EchoUdp( IPN IPAddr );
static void OobTest( IPN IPAddr, uint fInline );

/*------------------------------------------------------------------------- */
/* ConCmdEcho() */
/* Function to run TCP/UDP echo tests */
/*------------------------------------------------------------------------- */
void ConCmdEcho( int ntok, char *tok1, char *tok2 )
{
    IPN IPTmp;

    /* Check for 'Echo tcp x.x.x.x' */
    if( ntok == 2 && !strcmp( tok1, "tcp" ) )
    {
       if( !ConStrToIPN( tok2, &IPTmp ) )
           ConPrintf("Invalid address\n\n");
       else
           EchoTcp( IPTmp );
    }
    /* Check for 'Echo udp x.x.x.x' */
    else if( ntok == 2 && !strcmp( tok1, "udp" ) )
    {
       if( !ConStrToIPN( tok2, &IPTmp ) )
           ConPrintf("Invalid address\n");
       else
           EchoUdp( IPTmp );
    }
    /* Check for 'Echo tcpurg x.x.x.x' */
    else if( ntok == 2 && !strcmp( tok1, "tcpurg" ) )
    {
       if( !ConStrToIPN( tok2, &IPTmp ) )
           ConPrintf("Invalid address\n");
       else
       {
           OobTest( IPTmp, 0 );
           OobTest( IPTmp, 1 );
       }
    }
    else if( ntok == 0 )
    {
        ConPrintf("\n[Echo Command]\n");
        ConPrintf("\nRun TCP and UDP packet echo tests. Note that the\n");
        ConPrintf("'tcpurg' test requires a compatible target\n\n");
        ConPrintf("echo tcp x.x.x.x    - Run TCP echo test\n");
        ConPrintf("echo udp x.x.x.x    - Run UDP echo test\n");
        ConPrintf("echo tcpurg x.x.x.x - Run TCP urgent data test\n\n");
    }
    else
        ConPrintf("\nCommand error. Type 'echo' for help\n");
}

/*---------------------------------------------------------------------- */
/* EchoTcp() */
/* Test ECHO with a TCP socket */
/*---------------------------------------------------------------------- */
static void EchoTcp( IPN IPAddr )
{
    SOCKET  s;
    struct  sockaddr_in sin1;
    int     test,i;
    char    *pBuf = 0;
    struct  timeval timeout;

    ConPrintf("\n== Start TCP Echo Client Test ==\n");

    /* Create test socket */
    s = socket(AF_INET, SOCK_STREAMNC, IPPROTO_TCP);
    if( s == INVALID_SOCKET )
    {
        ConPrintf("failed socket create (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for connect */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family      = AF_INET;
    sin1.sin_addr.s_addr = IPAddr;
    sin1.sin_port        = htons(7);

    /* Configure our timeout to be 5 seconds */
    timeout.tv_sec  = 5;
    timeout.tv_usec = 0;
    setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof( timeout ) );
    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof( timeout ) );

    /* Connect socket */
    if ( connect( s, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf("failed connect (%d)\n",fdError());
        goto leave;
    }

    /* Allocate a working buffer */
    if( !(pBuf = mmBulkAlloc( 12288 )) )
    {
        ConPrintf("failed temp buffer allocation\n");
        goto leave;
    }

    /* Start Test */
    for( test=48; test<=12288; test*=2 )
    {
        /* Fill buffer with a test pattern */
        for(i=0; i<test; i++)
            *(pBuf+i) = (char)i;

        /* Send the buffer */
        ConPrintf("Sending %d bytes ... ",test);
        if( send( s, pBuf, test, 0 ) < 0 )
        {
            ConPrintf("send failed (%d)\n",fdError());
            break;
        }

        /* Clear the test pattern */
        mmZeroInit( pBuf, (uint)test );

        /* Try and receive the test pattern back */
        ConPrintf("receive ... ");
        i = recv( s, pBuf, test, MSG_WAITALL );
        if( i < 0 )
        {
            ConPrintf("recv failed (%d)\n",fdError());
            break;
        }

        /* Verify reception size */
        if( i != test )
        {
            ConPrintf("received %d (not %d) bytes\n",i,test);
            break;
        }

        /* Verify the test pattern */
        ConPrintf("verify ... ");
        for(i=0; i<test; i++)
            if( *(pBuf+i) != (char)i )
            {
                ConPrintf("verify failed at byte %d\n",i);
                break;
            }
        if( i==test )
            ConPrintf("passed\n");
    }
leave:
    if( pBuf )
        mmBulkFree( pBuf );
    if( s != INVALID_SOCKET )
        fdClose( s );

    ConPrintf("== End TCP Echo Client Test ==\n\n");
}

/*---------------------------------------------------------------------- */
/* EchoUdp() */
/* Test ECHO with a UDP socket */
/*---------------------------------------------------------------------- */
static void EchoUdp( IPN IPAddr )
{
    SOCKET  s;
    struct  sockaddr_in sin1;
    struct  sockaddr_in sin2;
    int     test,i,tmp;
    char    *pBuf = 0;
    struct  timeval timeout;

    ConPrintf("\n== Start UDP Echo Client Test ==\n");

    /* Create test socket */
    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if( s == INVALID_SOCKET )
    {
        ConPrintf("failed socket create (%d)\n",fdError());
        goto leave;
    }

    /* We must bind since we won't issue a connect */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    if( bind( s, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf("failed bind (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for the SendTo */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family      = AF_INET;
    sin1.sin_addr.s_addr = IPAddr;
    sin1.sin_port        = htons(7);

    /* Configure our timeout to be 5 seconds */
    timeout.tv_sec  = 5;
    timeout.tv_usec = 0;
    setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof( timeout ) );
    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof( timeout ) );

    /* Allocate a working buffer */
    if( !(pBuf = mmBulkAlloc( 1024 )) )
    {
        ConPrintf("failed temp buffer allocation\n");
        goto leave;
    }

    /* Start Test */
    for( test=8; test<=1024; test*=2 )
    {
        /* Fill buffer with a test pattern */
        for(i=0; i<test; i++)
            *(pBuf+i) = (char)i;

        /* Send the buffer */
        ConPrintf("Sending %d bytes . ",test);
        if( sendto( s, pBuf, test, 0,(struct sockaddr *)&sin1, sizeof(sin1) ) < 0 )
        {
            ConPrintf("send failed (%d)\n",fdError());
            break;
        }

        /* Clear the test pattern */
        mmZeroInit( pBuf, (uint)test );

        /* Try and receive the test pattern back */
        ConPrintf("receive . ");
        tmp = sizeof( sin2 );
        if( recvfrom( s, pBuf, test, MSG_WAITALL,(struct sockaddr *)&sin2, &tmp ) < 0 )
        {
            ConPrintf("recv failed (%d)\n",fdError());
            break;
        }

        /* Verify the test pattern */
        ConPrintf("(");
        ConPrintIPN( sin2.sin_addr.s_addr );
        ConPrintf(":%d) verify . ", htons( sin2.sin_port ) );
        for(i=0; i<test; i++)
            if( *(pBuf+i) != (char)i )
            {
                ConPrintf("verify failed at byte %d\n",i);
                break;
            }
        if( i==test )
            ConPrintf("passed\n");
    }
leave:
    if( pBuf )
        mmBulkFree( pBuf );
    if( s != INVALID_SOCKET )
        fdClose( s );

    ConPrintf("== End UDP Echo Client Test ==\n\n");
}

/*---------------------------------------------------------------------- */
/* OobTest() */
/* Test receiving OOB data with a TCP socket */
/*---------------------------------------------------------------------- */
static void OobTest( IPN IPAddr, uint fInline )
{
    SOCKET  s;
    struct  sockaddr_in sin1;
    int     test,i;
    char    buf[48];
    struct  timeval timeout;

    ConPrintf("\n== Start OOB Test ==\n");

    /* Create the test socket */
    s = socket(AF_INET, SOCK_STREAMNC, IPPROTO_TCP);
    if( s == INVALID_SOCKET )
    {
        ConPrintf("failed socket create (%d)\n",fdError());
        goto leave;
    }

    /* Prepare the address for connecting */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family      = AF_INET;
    sin1.sin_addr.s_addr = IPAddr;
    sin1.sin_port        = htons(999);

    /* Configure our timeout to be 5 seconds */
    timeout.tv_sec  = 5;
    timeout.tv_usec = 0;
    setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof( timeout ) );
    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof( timeout ) );

    /* Connect the socket */
    if ( connect( s, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
        ConPrintf("failed connect (%d)\n",fdError());
        goto leave;
    }

    /* Sending a single byte to *OUR* ehco server will trigger the OOB */
    /* test. This test will fail if connected to a generic echo server */
    if( !fInline )
        ConPrintf("\nConnected in NORMAL mode\n");
    else
    {
        ConPrintf("\nConnected in INLINE mode\n");

        /* Setup socket for "inline" OOB data */
        i = 1;
        if( setsockopt( s, SOL_SOCKET, SO_OOBINLINE,
                        (char * )&i, sizeof(i) ) < 0 )
        {
            ConPrintf("failed setsockopt (%d)\n",fdError());
            goto leave;
        }
    }

    /* We need to sleep for a bit to make sure all the packets get here */
    TaskSleep( 2*1000 );

    /* Call receive without the OOB flag */
    /*  This should return all the data bytes up to the OOB mark. */

    if( (test = recv( s, buf, sizeof(buf), 0 )) < 0 )
        ConPrintf("failed read 1 (%d)\n",fdError());
    else
    {
        ConPrintf("Received %d normal bytes ( ",test);
        for( i=0; i<test; i++ )
            ConPrintf("%d ",*(buf+i));
        ConPrintf(")\n");
    }

    /* Call receive with the OOB flag */
    /*  This should return a single OOB data byte in NORMAL */
    /*  mode, and an error in INLINE mode */
    if( (test=recv( s, buf, sizeof(buf), MSG_OOB )) < 0 )
    {
        if( !fInline )
            ConPrintf("failed read 2 (%d)\n",fdError());
    }
    else
    {
        if( fInline )
            ConPrintf("read 2 passed - should have failed\n");
        ConPrintf("Received %d OOB byte(s) (%d)\n",test,*buf);
    }

    /* Call receive without the OOB flag */
    /*     This should return remainder of the data in the buffer */

    if( (test = recv( s, buf, sizeof(buf), 0 )) < 0 )
        ConPrintf("failed read 3 (%d)\n",fdError());
    else
    {
        ConPrintf("Received %d normal bytes ( ",test);
        for( i=0; i<test; i++ )
            ConPrintf("%d ",*(buf+i));
        ConPrintf(")\n");
    }

leave:
    if( s != INVALID_SOCKET )
        fdClose( s );

    ConPrintf("\n== End OOB Test ==\n\n");
}

