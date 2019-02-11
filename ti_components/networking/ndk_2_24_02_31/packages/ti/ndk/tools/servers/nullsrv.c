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
 * ======== nullsrv.c ========
 *
 */

#include <netmain.h>

#define FAST_SERVER     1
#define HYBRID_SERVER   0
#define NORMALNC_SERVER 0
#define NORMAL_SERVER   0

#if FAST_SERVER
/*--------------------------------------------------------------------- */
/* Fast Sockets Programming */
/*--------------------------------------------------------------------- */
void nullsrv()
{
    SOCKET   stcp = INVALID_SOCKET;
    SOCKET   stcpactive = INVALID_SOCKET;
    struct   sockaddr_in sin1;
    struct   timeval timeout;           /* Timeout struct for select */
    int      size;
    int      cnt;
    char     *pBuf;
    HANDLE   hBuffer;

    /* Allocate the file environment for this task */
    fdOpenSession( TaskSelf() );

    /* Create the main TCP listen socket */
    stcp = socket(AF_INET, SOCK_STREAMNC, IPPROTO_TCP);
    if( stcp == INVALID_SOCKET )
        goto leave;

    /* Set Port = 1001, leaving IP address = Any */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family = AF_INET;
    sin1.sin_port   = htons(1001);

    /* Bind socket */
    if ( bind( stcp, (PSA) &sin1, sizeof(sin1) ) < 0 )
        goto leave;

    /* Start listening */
    if ( listen( stcp, 1) < 0 )
        goto leave;

    /* Configure our timeout to be 15 seconds */
    timeout.tv_sec  = 15;
    timeout.tv_usec = 0;
    setsockopt( stcp, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof( timeout ) );
    setsockopt( stcp, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof( timeout ) );

    DbgPrintf(DBG_INFO, "nullsrv: NullSrv (fast) Initialized\n");

    /* Run until task is destroyed by the system */
    for(;;)
    {
        /* Get a connection */
        size = sizeof( sin1 );
        stcpactive = accept( stcp, (PSA)&sin1, &size );
        if( stcpactive == INVALID_SOCKET )
            goto leave;

        /* Read and toss TCP data */
        do
        {
            /* There is data available on the active connection */
            cnt = (int)recvnc( stcpactive, (void **)&pBuf, 0, &hBuffer );

            /* If the connection is closed or got an error, close */
            if( cnt <= 0 )
            {
                fdClose( stcpactive );
                stcpactive = INVALID_SOCKET;
            }
            else
                recvncfree( hBuffer );
        } while( cnt > 0 );
    }

leave:
    /* We only get here on an error - close the sockets */
    if( stcp != INVALID_SOCKET )
        fdClose( stcp );

    DbgPrintf(DBG_INFO, "nullsrv: NullSrv (fast) Fatal Error\n");

    /* This task is killed by the system - here, we block */
    TaskBlock( TaskSelf() );
}
#endif

#if HYBRID_SERVER
/*--------------------------------------------------------------------- */
/* Hybrid Test - Use recvnvc(), but keep select() call */
/*--------------------------------------------------------------------- */
void nullsrv()
{
    SOCKET      stcp = INVALID_SOCKET;
    SOCKET      stcpactive = INVALID_SOCKET;
    SOCKET      stcpbusy;
    struct      sockaddr_in sin1;
    struct      timeval timeout;        /* Timeout struct for select */
    int         size;
    int         cnt;
    fd_set      ibits, obits, xbits;
    char        *pBuf;
    HANDLE      hBuffer;

    /* Allocate the file environment for this task */
    fdOpenSession( TaskSelf() );

    /* Create the main TCP listen socket */
    stcp = socket(AF_INET, SOCK_STREAMNC, IPPROTO_TCP);
    if( stcp == INVALID_SOCKET )
        goto leave;

    /* Set Port = 1001, leaving IP address = Any */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family = AF_INET;
    sin1.sin_port   = htons(1001);

    /* Bind socket */
    if ( bind( stcp, (PSA) &sin1, sizeof(sin1) ) < 0 )
        goto leave;

    /* Start listening */
    if ( listen( stcp, 1) < 0 )
        goto leave;

    /* Configure our timeout to be 60 seconds */
    timeout.tv_sec  = 60;
    timeout.tv_usec = 0;

    DbgPrintf(DBG_INFO, "nullsrv: NullSrv (hybrid) Initialized\n");

    /* Run until task is destroyed by the system */
    for(;;)
    {
        /* Clear the select flags */
        FD_ZERO(&ibits);
        FD_ZERO(&obits);
        FD_ZERO(&xbits);

        /* We examine the main TCP, UDP, and active TCP (if any) */
        FD_SET(stcp, &ibits);

        /* Wait for socket activity */
        if( stcpactive == INVALID_SOCKET )
        {
            /* Wait without timeout */
            cnt = fdSelect( 4, &ibits, &obits, &xbits, 0 );
        }
        else
        {
            /* Wait for set timeout - abort active connection on no activity */
            FD_SET(stcpactive, &ibits);
            cnt = fdSelect( 4, &ibits, &obits, &xbits, &timeout );
            if( !cnt )
            {
                fdClose( stcpactive );
                stcpactive = INVALID_SOCKET;
            }
        }

        if( cnt < 0 )
            goto leave;

        /* Check for a new TCP connection */
        if( FD_ISSET(stcp, &ibits) )
        {
            /* We have a new connection. Assign it so sbusy at */
            /* first... */
            size = sizeof( sin1 );
            stcpbusy = accept( stcp, (PSA)&sin1, &size );

            /* If the active socket is free use it, else print out */
            /* a busy message */
            if( stcpactive == INVALID_SOCKET )
                stcpactive = stcpbusy;
            else
                fdClose( stcpbusy );
        }

        /* Check for new data on active TCP connection */
        if( stcpactive != INVALID_SOCKET && FD_ISSET(stcpactive, &ibits) )
        {
            /* There is data available on the active connection */
            cnt = (int)recvnc( stcpactive, (void **)&pBuf, 0, &hBuffer );

            /* If the connection is closed or got an error, close */
            if( cnt <= 0 )
            {
                fdClose( stcpactive );
                stcpactive = INVALID_SOCKET;
            }
            else
                recvncfree( hBuffer );
        }
    }

leave:
    /* We only get here on an error - close the sockets */
    if( stcpactive != INVALID_SOCKET )
        fdClose( stcpactive );
    if( stcp != INVALID_SOCKET )
        fdClose( stcp );

    DbgPrintf(DBG_INFO, "nullsrv: NullSrv (hybrid) Fatal Error\n");

    /* This task is killed by the system - here, we block */
    TaskBlock( TaskSelf() );
}
#endif

#if NORMALNC_SERVER
/*--------------------------------------------------------------------- */
/* Classic Sockets Programming */
/*--------------------------------------------------------------------- */
void nullsrv()
{
    SOCKET      stcp = INVALID_SOCKET;
    SOCKET      stcpactive = INVALID_SOCKET;
    SOCKET      stcpbusy;
    struct      sockaddr_in sin1;
    struct      timeval timeout;        /* Timeout struct for select */
    int         size;
    int         cnt;
    fd_set      ibits, obits, xbits;

    static char buf[2048];

    /* Allocate the file environment for this task */
    fdOpenSession( TaskSelf() );

    /* Create the main TCP listen socket */
    stcp = socket(AF_INET, SOCK_STREAMNC, IPPROTO_TCP);
    if( stcp == INVALID_SOCKET )
        goto leave;

    /* Set Port = 1001, leaving IP address = Any */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family = AF_INET;
    sin1.sin_port   = htons(1001);

    /* Bind socket */
    if ( bind( stcp, (PSA) &sin1, sizeof(sin1) ) < 0 )
        goto leave;

    /* Start listening */
    if ( listen( stcp, 1) < 0 )
        goto leave;

    /* Configure our timeout to be 60 seconds */
    timeout.tv_sec  = 60;
    timeout.tv_usec = 0;

    DbgPrintf(DBG_INFO, "nullsrv: NullSrv (normalnc) Initialized\n");

    /* Run until task is destroyed by the system */
    for(;;)
    {
        /* Clear the select flags */
        FD_ZERO(&ibits);
        FD_ZERO(&obits);
        FD_ZERO(&xbits);

        /* We examine the main TCP, UDP, and active TCP (if any) */
        FD_SET(stcp, &ibits);

        /* Wait for socket activity */
        if( stcpactive == INVALID_SOCKET )
        {
            /* Wait without timeout */
            cnt = fdSelect( 4, &ibits, &obits, &xbits, 0 );
        }
        else
        {
            /* Wait for set timeout - abort active connection on no activity */
            FD_SET(stcpactive, &ibits);
            cnt = fdSelect( 4, &ibits, &obits, &xbits, &timeout );
            if( !cnt )
            {
                fdClose( stcpactive );
                stcpactive = INVALID_SOCKET;
            }
        }

        if( cnt < 0 )
            goto leave;

        /* Check for a new TCP connection */
        if( FD_ISSET(stcp, &ibits) )
        {
            /* We have a new connection. Assign it so sbusy at */
            /* first... */
            size = sizeof( sin1 );
            stcpbusy = accept( stcp, (PSA)&sin1, &size );

            /* If the active socket is free use it, else print out */
            /* a busy message */
            if( stcpactive == INVALID_SOCKET )
                stcpactive = stcpbusy;
            else
                fdClose( stcpbusy );
        }

        /* Check for new data on active TCP connection */
        if( stcpactive != INVALID_SOCKET && FD_ISSET(stcpactive, &ibits) )
        {
            /* There is data available on the active connection */
            cnt = (int)recv( stcpactive, buf, sizeof(buf), 0 );

            /* If the connection is closed or got an error, close */
            if( cnt <= 0 )
            {
                fdClose( stcpactive );
                stcpactive = INVALID_SOCKET;
            }
        }
    }

leave:
    /* We only get here on an error - close the sockets */
    if( stcpactive != INVALID_SOCKET )
        fdClose( stcpactive );
    if( stcp != INVALID_SOCKET )
        fdClose( stcp );

    DbgPrintf(DBG_INFO, "nullsrv: NullSrv (normalnc) Fatal Error\n");

    /* This task is killed by the system - here, we block */
    TaskBlock( TaskSelf() );
}

#endif

#if NORMAL_SERVER
/*--------------------------------------------------------------------- */
/* Classic Sockets Programming */
/*--------------------------------------------------------------------- */
void nullsrv()
{
    SOCKET      stcp = INVALID_SOCKET;
    SOCKET      stcpactive = INVALID_SOCKET;
    SOCKET      stcpbusy;
    struct      sockaddr_in sin1;
    struct      timeval timeout;        /* Timeout struct for select */
    int         size;
    int         cnt;
    fd_set      ibits, obits, xbits;

    static char buf[2048];

    /* Allocate the file environment for this task */
    fdOpenSession( TaskSelf() );

    /* Create the main TCP listen socket */
    stcp = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( stcp == INVALID_SOCKET )
        goto leave;

    /* Set Port = 1001, leaving IP address = Any */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family = AF_INET;
    sin1.sin_port   = htons(1001);

    /* Bind socket */
    if ( bind( stcp, (PSA) &sin1, sizeof(sin1) ) < 0 )
        goto leave;

    /* Start listening */
    if ( listen( stcp, 1) < 0 )
        goto leave;

    /* Configure our timeout to be 60 seconds */
    timeout.tv_sec  = 60;
    timeout.tv_usec = 0;

    DbgPrintf(DBG_INFO, "nullsrv: NullSrv (normal) Initialized\n");

    /* Run until task is destroyed by the system */
    for(;;)
    {
        /* Clear the select flags */
        FD_ZERO(&ibits);
        FD_ZERO(&obits);
        FD_ZERO(&xbits);

        /* We examine the main TCP, UDP, and active TCP (if any) */
        FD_SET(stcp, &ibits);

        /* Wait for socket activity */
        if( stcpactive == INVALID_SOCKET )
        {
            /* Wait without timeout */
            cnt = fdSelect( 4, &ibits, &obits, &xbits, 0 );
        }
        else
        {
            /* Wait for set timeout - abort active connection on no activity */
            FD_SET(stcpactive, &ibits);
            cnt = fdSelect( 4, &ibits, &obits, &xbits, &timeout );
            if( !cnt )
            {
                fdClose( stcpactive );
                stcpactive = INVALID_SOCKET;
            }
        }

        if( cnt < 0 )
            goto leave;

        /* Check for a new TCP connection */
        if( FD_ISSET(stcp, &ibits) )
        {
            /* We have a new connection. Assign it so sbusy at */
            /* first... */
            size = sizeof( sin1 );
            stcpbusy = accept( stcp, (PSA)&sin1, &size );

            /* If the active socket is free use it, else close stcpbusy */
            if( stcpactive == INVALID_SOCKET )
                stcpactive = stcpbusy;
            else
                fdClose( stcpbusy );
        }

        /* Check for new data on active TCP connection */
        if( stcpactive != INVALID_SOCKET && FD_ISSET(stcpactive, &ibits) )
        {
            /* There is data available on the active connection */
            cnt = (int)recv( stcpactive, buf, sizeof(buf), 0 );

            /* If the connection is closed or got an error, close */
            if( cnt <= 0 )
            {
                fdClose( stcpactive );
                stcpactive = INVALID_SOCKET;
            }
        }
    }

leave:
    /* We only get here on an error - close the sockets */
    if( stcpactive != INVALID_SOCKET )
        fdClose( stcpactive );
    if( stcp != INVALID_SOCKET )
        fdClose( stcp );

    DbgPrintf(DBG_INFO, "nullsrv: NullSrv (normal) Fatal Error\n");

    /* This task is killed by the system - here, we block */
    TaskBlock( TaskSelf() );
}

#endif

