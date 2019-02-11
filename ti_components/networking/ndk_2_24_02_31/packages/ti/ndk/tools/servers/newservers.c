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
 * ======== newservers.c ========
 *
 * This module demonstrates the use of the server daemon added in NDK 1.7.
 *
 * It provides all the functionality of:
 *     echosrv() : echosrv.c
 *     datasrv() : datasrv.c
 *     nullsrv() : nullsrv.c
 *     oobsrv()  : oobsrv.c
 *
 * The original source files are still provided to illustrate a traditional
 * server. This file contains only the daemon service task functions
 * required when using the server daemon.
 *
 */

#include <netmain.h>

#define DATASRV_BUFSIZE 512
#define NULLSRV_BUFSIZE 1500

/* dtask_tcp_echo() - TCP Echo Server Daemon Function (SOCK_STREAMNC) */
/* (SOCK_STREAMNC, port 7) */
/* Returns "1" if socket 's' is still open, and "0" if its been closed */
int dtask_tcp_echo( SOCKET s, UINT32 unused )
{
    struct timeval to;
    int            i;
    char           *pBuf;
    HANDLE         hBuffer;

    (void)unused;

    /* Configure our socket timeout to be 5 seconds */
    to.tv_sec  = 5;
    to.tv_usec = 0;
    setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &to, sizeof( to ) );
    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &to, sizeof( to ) );

    i = 1;
    setsockopt( s, IPPROTO_TCP, TCP_NOPUSH, &i, 4 );

    for(;;)
    {
        i = (int)recvnc( s, (void **)&pBuf, 0, &hBuffer );

        /* If we read data, echo it back */
        if( i > 0 )
        {
            if( send( s, pBuf, i, 0 ) < 0 )
                break;
            recvncfree( hBuffer );
        }
        /* If the connection got an error or disconnect, close */
        else
            break;
    }

    fdClose( s );

    /* Return "0" since we closed the socket */
    return(0);
}



/* dtask_udp_echo() - UDP Echo Server Daemon Function */
/* (SOCK_DGRAM, port 7) */
/* Returns "1" if socket 's' is still open, and "0" if its been closed */
int dtask_udp_echo( SOCKET s, UINT32 unused )
{
    struct sockaddr_in sin1;
    struct timeval     to;
    int                i,tmp;
    char               *pBuf;
    HANDLE             hBuffer;

    (void)unused;

    /* Configure our socket timeout to be 3 seconds */
    to.tv_sec  = 3;
    to.tv_usec = 0;
    setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &to, sizeof( to ) );
    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &to, sizeof( to ) );

    for(;;)
    {
        tmp = sizeof( sin1 );
        i = (int)recvncfrom( s, (void **)&pBuf, 0,(struct sockaddr *)&sin1, &tmp, &hBuffer );

        /* Spit any data back out */
        if( i >= 0 )
        {
            sendto( s, pBuf, i, 0,(struct sockaddr *)&sin1, sizeof(sin1) );
            recvncfree( hBuffer );
        }
        else
            break;
    }

    /* Since the socket is still open, return "1" */
    /* (we need to leave UDP sockets open) */
    return(1);
}



/* dtask_tcp_datasrv() - TCP Data Server Daemon Function */
/* (SOCK_STREAM, port 1000) */
/* Returns "1" if socket 's' is still open, and "0" if it's been closed */
int dtask_tcp_datasrv( SOCKET s, UINT32 unused )
{
    struct timeval to;
    int            i, size, count, remainder, totalSent, sent;
    char          *data;
    int            allocFailed = 0;

    (void)unused;

    data = (char *)mmAlloc(DATASRV_BUFSIZE);
    if (!data) {
        /* allocation failed, resources low */
        DbgPrintf(DBG_INFO,
            "dtask_tcp_datasrv: allocation failed, sending constant size\n");
        allocFailed = 1;
    }

    if (!allocFailed) {
        /* initialize data buffer */
        for (i = 0; i < DATASRV_BUFSIZE; i++) {
            data[i] = ' ' + i;
        }
    }

    /* Configure our socket timeout to be 5 seconds */
    to.tv_sec  = 5;
    to.tv_usec = 0;
    setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &to, sizeof( to ) );
    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &to, sizeof( to ) );

    i = 1;
    setsockopt( s, IPPROTO_TCP, TCP_NOPUSH, &i, 4 );

    for(;;)
    {
        totalSent = 0;

        /* receive request for amount of data to send from client */
        i = (int)recv( s, (char *)&size, sizeof(int), 0 );

/* ---- Special Code for Big Endian Build ---- */
#ifdef BIGENDIAN
        /* Size comes in as little endian! */
        /* We need to convert it */
        size = ((size>>24)&0xFF) + ((size>>8)&0xFF00) + ((size<<8)&0xFF0000) + (size<<24);
#endif
/* ------------------------------------------- */

        /* divide total size of data to send into 512 byte chunks */
        count = size / DATASRV_BUFSIZE;
        remainder = size % DATASRV_BUFSIZE;

        if( i==sizeof(int) )
        {
            if (allocFailed) {
                /* couldn't get a buffer, just send value we rec'vd back */
                if ((send(s, (char *)&size, sizeof(int), 0) < 0)) {
                    DbgPrintf(DBG_INFO,
                            "dtask_tcp_datasrv: send returned < 0!\n");
                    break;
                }
            }
            else {
                /* allocation succeeded: send DATASRV_BUFSIZE * count bytes */
                sent = 0;
                for (i = 0; i < count; i++) {
                    /* send DATASRV_BUFSIZE num bytes until we get close to size */
                    if ((sent = send( s, data, DATASRV_BUFSIZE, 0)) < 0 ) {
                        DbgPrintf(DBG_INFO,
                                "dtask_tcp_datasrv: send returned < 0!\n");
                        break;
                    }

                    totalSent += sent;
                }

                /* send the remainder (to get total sent up to 'size' */
                if (remainder > 0) {
                    totalSent += send(s, (char *)&size, remainder, 0);
                }
            }
        }
        else {
            DbgPrintf(DBG_INFO, "dtask_tcp_datasrv: received invalid size\n");
            break;
        }
    }

    if (data) {
        mmFree(data);
    }

    /* Note in dtask_tcp_echo() we close the socket at this */
    /* point. Here we'll leave it open to test the daemon. */

    /* Return "1" since the socket is still open */
    return(1);
}



/* dtask_tcp_nullsrv() - TCP Data Server Daemon Function */
/* (SOCK_STREAMNC, port 1001) */
/* Returns "1" if socket 's' is still open, and "0" if its been closed */
int dtask_tcp_nullsrv( SOCKET s, UINT32 unused )
{
    struct timeval to;
    int            i;
    char           *pBuf;
    HANDLE         hBuffer;

    (void)unused;

    /* Configure our socket timeout to be 5 seconds */
    to.tv_sec  = 5;
    to.tv_usec = 0;
    setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &to, sizeof( to ) );
    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &to, sizeof( to ) );

    for(;;)
    {
        /* There is data available on the active connection */
        i = (int)recvnc( s, (void **)&pBuf, 0, &hBuffer );

        /* If the connection is closed or got an error, close */
        if( i <= 0 )
            break;
        else
            recvncfree( hBuffer );
    }

    /* Note in dtask_tcp_echo() we close the socket at this */
    /* point. Here we'll leave it open to test the daemon. */

    /* Return "1" since the socket is still open */
    return(1);
}



/* dtask_tcp_oobsrv() - TCP Data Server Daemon Function */
/* (SOCK_STREAMNC. port 999) */
/* Returns "1" if socket 's' is still open, and "0" if its been closed */
int dtask_tcp_oobsrv( SOCKET s, UINT32 unused )
{
    struct timeval to;
    int            i;
    char           buf[16];

    (void)unused;

    /* Configure our socket timeout to be 5 seconds */
    to.tv_sec  = 5;
    to.tv_usec = 0;
    setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &to, sizeof( to ) );
    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &to, sizeof( to ) );

    /* OOB Data Test */
    /* Will send 10 bytes of data, 1 OOB, and then 10 more data */
    /* Client shoud read as */
    /*    10 bytes (0, 1, 2, 3, 4, 5, 6, 7, 8, 9) */
    /*    1  byte  (99) */
    /*    10 bytes (0, 1, 2, 3, 4, 5, 6, 7, 8, 9) */
    for(i=0; i<10; i++)
        buf[i] = i;
    buf[10] = 99;
    send( s, buf, 11, MSG_OOB );
    send( s, buf, 10, 0 );

    fdClose( s );

    /* Return "0" since we closed the socket */
    return(0);
}

#ifdef _INCLUDE_IPv6_CODE

/* dtask_tcp_echo() - TCP Echo Server Daemon Function (SOCK_STREAM) */
/* (SOCK_STREAM, port 7) */
/* Returns "1" if socket 's' is still open, and "0" if its been closed */
int dtask_tcp_echo6( SOCKET s, UINT32 unused )
{
    struct timeval to;
    int            i;
    char           Buffer[1500];

    (void)unused;

    /* Configure our socket timeout to be 5 seconds */
    to.tv_sec  = 5;
    to.tv_usec = 0;
    setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &to, sizeof( to ) );
    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &to, sizeof( to ) );

    i = 1;
    setsockopt( s, IPPROTO_TCP, TCP_NOPUSH, &i, 4 );

    for(;;)
    {
        i = (int)recv( s, (void **)&Buffer[0], sizeof(Buffer), 0);

        /* If we read data, echo it back */
        if( i > 0 )
        {
            if( send( s, &Buffer[0], i, 0 ) < 0 )
                break;
        }
        /* If the connection got an error or disconnect, close */
        else
            break;
    }

    fdClose( s );

    /* Return "0" since we closed the socket */
    return(0);
}

/* dtask_udp_echo6() - UDP Echo Server Daemon Function */
/* (SOCK_DGRAM, port 7) */
/* Returns "1" if socket 's' is still open, and "0" if its been closed */
int dtask_udp_echo6( SOCKET s, UINT32 unused )
{
    struct sockaddr_in6 sin1;
    struct timeval      to;
    int                 i,tmp;
    char                Buffer[1500];

    (void)unused;

    /* Configure our socket timeout to be 3 seconds */
    to.tv_sec  = 3;
    to.tv_usec = 0;
    setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &to, sizeof( to ) );
    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &to, sizeof( to ) );

    for(;;)
    {
        tmp = sizeof( sin1 );
        i = (int)recvfrom( s, (void **)&Buffer[0], sizeof(Buffer), 0, (struct sockaddr *)&sin1, &tmp);

        /* Spit any data back out */
        if( i >= 0 )
        {
            sendto( s, &Buffer[0], i, 0,(struct sockaddr *)&sin1, sizeof(sin1) );
        }
        else
            break;
    }

    /* Since the socket is still open, return "1" */
    /* (we need to leave UDP sockets open) */
    return(1);
}

/* dtask_tcp_nullsrv6() - TCP/IPv6 Data Server Daemon Function */
/* (SOCK_STREAMNC, port 1001) */
/* Returns "1" if socket 's' is still open, and "0" if its been closed */
int dtask_tcp_nullsrv6( SOCKET s, UINT32 unused )
{
    struct timeval to;
    int            i;
    char           *Buffer;

    (void)unused;

    Buffer = (char *)mmAlloc(NULLSRV_BUFSIZE);
    if (!Buffer) {
        /* allocation failed, resources low */
        DbgPrintf(DBG_INFO,
            "dtask_tcp_nullsrv6: buffer allocation failed\n");

        fdClose(s);
        return (0);
    }


    /* Configure our socket timeout to be 5 seconds */
    to.tv_sec  = 5;
    to.tv_usec = 0;
    setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &to, sizeof( to ) );
    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &to, sizeof( to ) );

    for(;;)
    {
        /* There is data available on the active connection */
        i = (int)recv( s, (void **)&Buffer[0], NULLSRV_BUFSIZE, 0);

        /* If the connection is closed or got an error, close */
        if( i <= 0 )
            break;
    }

    if (Buffer) {
        mmFree(Buffer);
    }

    /* Note in dtask_tcp_echo() we close the socket at this */
    /* point. Here we'll leave it open to test the daemon. */

    /* Return "1" since the socket is still open */
    return(1);
}

#endif /* _INCLUDE_IPv6_CODE */

