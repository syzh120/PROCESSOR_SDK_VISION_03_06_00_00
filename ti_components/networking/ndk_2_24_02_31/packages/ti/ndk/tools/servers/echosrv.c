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
 * ======== echosrv.c ========
 *
 * This program implements a TCP and UDP echo server, which echos back any
 * input it receives.
 *
 */

#include <netmain.h>

/** 
 *  @b Description
 *  @n  
 *      This is the TCP/UDP v4 Echo Server.
 *
 *  @retval
 *      Not Applicable
 */
void echosrv()
{
    SOCKET   stcp = INVALID_SOCKET;
    SOCKET   sudp = INVALID_SOCKET;
    SOCKET   stcpactive = INVALID_SOCKET;
    SOCKET   stcpbusy;
    struct   sockaddr_in sin1;
    struct   timeval timeout;           /* Timeout struct for select */
    int      size,tmp;
    HANDLE   hBuffer;
    char     *pBuf;

    /* Allocate the file environment for this task */
    fdOpenSession( TaskSelf() );

    /* Create the main TCP listen socket */
    stcp = socket(AF_INET, SOCK_STREAMNC, IPPROTO_TCP);
    if( stcp == INVALID_SOCKET )
        goto leave;

    /* Set Port = 7, leaving IP address = Any */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family = AF_INET;
    sin1.sin_port   = htons(7);

    /* Bind socket */
    if ( bind( stcp, (PSA) &sin1, sizeof(sin1) ) < 0 )
        goto leave;

    /* Start listening */
    if ( listen( stcp, 1) < 0 )
        goto leave;

    /* Create our UDP echo socket */
    sudp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if( sudp == INVALID_SOCKET )
        goto leave;

    /* Bind the same as TCP ... Port = 7, IPAddr = Any */
    if ( bind( sudp, (PSA) &sin1, sizeof(sin1) ) < 0 )
        goto leave;

    /* Configure our timeout to be 15 seconds */
    timeout.tv_sec  = 15;
    timeout.tv_usec = 0;

    DbgPrintf(DBG_INFO, "echosrv: EchoSrv Initialized\n");

    /* Run until task is destroyed by the system */
    for(;;)
    {
        fd_set ibits, obits, xbits;
        int    cnt;

        /* Clear the select flags */
        FD_ZERO(&ibits);
        FD_ZERO(&obits);
        FD_ZERO(&xbits);

        /* We examine the main TCP, UDP, and active TCP (if any) */
        FD_SET(stcp, &ibits);
        FD_SET(sudp, &ibits);

        /* Wait for socket activity */
        if( stcpactive == INVALID_SOCKET )
        {
            /* Wait without timeout */
            tmp = fdSelect( 4, &ibits, &obits, &xbits, 0 );
        }
        else
        {
            /* Wait for set timeout - abort active connection on no activity */
            FD_SET(stcpactive, &ibits);
            tmp = fdSelect( 4, &ibits, &obits, &xbits, &timeout );
            if( tmp <= 0 )
            {
                fdClose( stcpactive );
                stcpactive = INVALID_SOCKET;
            }
        }

        if( tmp < 0 )
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

            if( cnt > 0 )
            {
                if( send( stcpactive, pBuf, cnt, 0 ) < 0 )
                {
                    fdClose( stcpactive );
                    stcpactive = INVALID_SOCKET;
                }
                recvncfree( hBuffer );
            }
            /* If the connection got an error or disconnect, close */
            else
            {
                fdClose( stcpactive );
                stcpactive = INVALID_SOCKET;
            }
        }

        /* Check for new data on UDP socket */
        if( FD_ISSET(sudp, &ibits) )
        {
            tmp = sizeof( sin1 );
            cnt = (int)recvncfrom( sudp, (void **)&pBuf, 0,(struct sockaddr *)&sin1, &tmp, &hBuffer );

            /* Spit any data back out */
            if( cnt >= 0 )
            {
                sendto( sudp, pBuf, cnt, 0,(struct sockaddr *)&sin1, sizeof(sin1) );
                recvncfree( hBuffer );
            }
        }
    }

leave:
    /* We only get here on an error - close the sockets */
    if( stcp != INVALID_SOCKET )
        fdClose( stcp );
    if( sudp != INVALID_SOCKET )
        fdClose( sudp );

    DbgPrintf(DBG_INFO, "echosrv: EchoSrv Fatal Error\n");

    /* This task is killed by the system - here, we block */
    TaskBlock( TaskSelf() );
}

#ifdef _INCLUDE_IPv6_CODE

/** 
 *  @b Description
 *  @n  
 *      This is the TCP/UDP v6 Echo Server.
 *
 *  @retval
 *      Not Applicable
 */
void v6echosrv()
{
    SOCKET   stcp = INVALID_SOCKET;
    SOCKET   sudp = INVALID_SOCKET;
    SOCKET   stcpactive = INVALID_SOCKET;
    SOCKET   stcpbusy;
    struct   sockaddr_in6 sin1;
    struct   timeval timeout;           /* Timeout struct for select */
    int      size,tmp;
    char     Buffer[1500];

    /* Allocate the file environment for this task */
    fdOpenSession( TaskSelf() );

    /* Create the main TCPv6 Listening Socket. */ 
    stcp = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    if( stcp == INVALID_SOCKET )
        goto leave;

    /* Set Port = 7, leaving IP address = Any and bind the socket. */
    bzero( &sin1, sizeof(struct sockaddr_in6) );
    sin1.sin6_family = AF_INET6;
    sin1.sin6_port   = htons(7);
    if ( bind( stcp, (PSA) &sin1, sizeof(sin1) ) < 0 )
        goto leave;

    /* Listen for connections. */ 
    if ( listen( stcp, 1) < 0 )
        goto leave;

    /* Create our UDP echo socket */
    sudp = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    if( sudp == INVALID_SOCKET )
        goto leave;

    /* Bind the same as TCP ... Port = 7, IPAddr = Any */
    if ( bind( sudp, (PSA) &sin1, sizeof(sin1) ) < 0 )
        goto leave;

    /* Configure our timeout to be 15 seconds */
    timeout.tv_sec  = 15;
    timeout.tv_usec = 0;

    DbgPrintf(DBG_INFO, "v6echosrv: V6EchoSrv Initialized\n");

    /* Run until task is destroyed by the system */
    for(;;)
    {
        fd_set ibits, obits, xbits;
        int    cnt;

        /* Clear the select flags */
        FD_ZERO(&ibits);
        FD_ZERO(&obits);
        FD_ZERO(&xbits);

        /* We examine the main TCP, UDP, and active TCP (if any) */
        FD_SET(stcp, &ibits);
        FD_SET(sudp, &ibits);

        /* Wait for socket activity */
        if( stcpactive == INVALID_SOCKET )
        {
            /* Wait without timeout */
            tmp = fdSelect( 4, &ibits, &obits, &xbits, 0 );
        }
        else
        {
            /* Wait for set timeout - abort active connection on no activity */
            FD_SET(stcpactive, &ibits);
            tmp = fdSelect( 4, &ibits, &obits, &xbits, &timeout );
            if( tmp <= 0 )
            {
                fdClose( stcpactive );
                stcpactive = INVALID_SOCKET;
            }
        }

        if( tmp < 0 )
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
            cnt = recv( stcpactive, (void *)&Buffer[0], sizeof(Buffer), 0 );
            if( cnt > 0 )
            {
                if( send( stcpactive, (void *)&Buffer[0], cnt, 0 ) < 0 )
                {
                    fdClose( stcpactive );
                    stcpactive = INVALID_SOCKET;
                }
            }
            /* If the connection got an error or disconnect, close */
            else
            {
                fdClose( stcpactive );
                stcpactive = INVALID_SOCKET;
            }
        }

        /* Check for new data on UDP socket */
        if( FD_ISSET(sudp, &ibits) )
        {
            tmp = sizeof( sin1 );
            cnt = recvfrom (sudp, (void *)&Buffer[0], sizeof(Buffer), 0, (struct sockaddr *)&sin1, &tmp);

            /* Spit any data back out */
            if( cnt >= 0 )
            {
                sendto( sudp, (void *)&Buffer[0], cnt, 0,(struct sockaddr *)&sin1, sizeof(sin1) );
            }
        }
    }

leave:
    /* We only get here on an error - close the sockets */
    if( stcp != INVALID_SOCKET )
        fdClose( stcp );
    if( sudp != INVALID_SOCKET )
        fdClose( sudp );

    DbgPrintf(DBG_INFO, "v6echosrv: V6EchoSrv Fatal Error\n");

    /* This task is killed by the system - here, we block */
    TaskBlock( TaskSelf() );
}

#endif /* _INCLUDE_IPv6_CODE */

