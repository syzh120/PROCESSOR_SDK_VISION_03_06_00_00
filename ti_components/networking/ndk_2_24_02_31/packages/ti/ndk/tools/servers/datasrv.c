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
 * ======== datasrv.c ========
 *
 */

#include <netmain.h>

static char buf[1024];

void datasrv()
{
    SOCKET   stcp = INVALID_SOCKET;
    SOCKET   stcpactive = INVALID_SOCKET;
    SOCKET   stcpbusy;
    struct   sockaddr_in sin1;
    struct   timeval timeout;           /* Timeout struct for select */
    int      size,tmp;

    /* Allocate the file environment for this task */
    fdOpenSession( TaskSelf() );

    /* Create the main TCP listen socket */
    stcp = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( stcp == INVALID_SOCKET )
        goto leave;

    /* Set Port = 1000, leaving IP address = Any */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family = AF_INET;
    sin1.sin_port   = htons(1000);

    /* Bind socket */
    if ( bind( stcp, (PSA) &sin1, sizeof(sin1) ) < 0 )
        goto leave;

    /* Start listening */
    if ( listen( stcp, 1) < 0 )
        goto leave;

    /* Configure our timeout to be 60 seconds */
    timeout.tv_sec  = 60;
    timeout.tv_usec = 0;

    DbgPrintf(DBG_INFO, "datasrv: DataSrv Initialized\n");

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
            cnt = (int)recv( stcpactive, (char *)&size, sizeof(int), 0 );

/* ---- Special Code for Big Endian Build ---- */
#ifdef BIGENDIAN
            /* Size comes in as little endian! */
            /* We need to convert it */
            size = ((size>>24)&0xFF) + ((size>>8)&0xFF00) + ((size<<8)&0xFF0000) + (size<<24);
#endif
/* ------------------------------------------- */

            if( cnt == sizeof(int) )
            {
                if( send( stcpactive, buf, size, 0 ) < 0 )
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
    }

leave:
    /* We only get here on an error - close the sockets */
    if( stcp != INVALID_SOCKET )
        fdClose( stcp );

    DbgPrintf(DBG_INFO, "datasrv: DataSrv Fatal Error\n");

    /* This task is killed by the system - here, we block */
    TaskBlock( TaskSelf() );
}

