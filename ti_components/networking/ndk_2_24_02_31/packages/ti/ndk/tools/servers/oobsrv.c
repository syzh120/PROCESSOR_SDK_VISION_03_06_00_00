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
 * ======== oobsrv.c ========
 *
 * This program implements a TCP OOB data server, which listens on port
 * 999, and initiates a TCPURG data test when a connection is made.
 *
 */

#include <netmain.h>

/* TCP/UDP Echo Server */
void oobsrv()
{
    SOCKET   stcp = INVALID_SOCKET;
    SOCKET   stcpactive = INVALID_SOCKET;
    struct   sockaddr_in sin1;
    char     buf[32];
    int      size,tmp;

    /* Allocate the file environment for this task */
    fdOpenSession( TaskSelf() );

    /* Create the main TCP listen socket */
    stcp = socket(AF_INET, SOCK_STREAMNC, IPPROTO_TCP);
    if( stcp == INVALID_SOCKET )
        goto leave;

    /* Set Port = 999, leaving IP address = Any */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family = AF_INET;
    sin1.sin_port   = htons(999);

    /* Bind socket */
    if ( bind( stcp, (PSA) &sin1, sizeof(sin1) ) < 0 )
        goto leave;

    /* Start listening */
    if ( listen( stcp, 1) < 0 )
        goto leave;

    DbgPrintf(DBG_INFO, "oobsrv: OobSrv Initialized\n");

    /* Run until task is destroyed by the system */
    for(;;)
    {
        size = sizeof( sin1 );
        stcpactive = accept( stcp, (PSA)&sin1, &size );
        if( stcpactive == INVALID_SOCKET )
                goto leave;

        /* OOB Data Test */
        /* Will send 10 bytes of data, 1 OOB, and then 10 more data */
        /* Client shoud read as */
        /*    10 bytes (0, 1, 2, 3, 4, 5, 6, 7, 8, 9) */
        /*    1  byte  (99) */
        /*    10 bytes (0, 1, 2, 3, 4, 5, 6, 7, 8, 9) */
        for(tmp=0; tmp<10; tmp++)
            buf[tmp] = tmp;
        buf[10] = 99;
        send( stcpactive, buf, 11, MSG_OOB );
        send( stcpactive, buf, 10, 0 );

        fdClose( stcpactive );
    }

leave:
    /* We only get here on an error - close the sockets */
    if( stcp != INVALID_SOCKET )
        fdClose( stcp );

    DbgPrintf(DBG_INFO, "oobsrv: OobSrv Fatal Error\n");

    /* This task is killed by the system - here, we will block */
    TaskBlock( TaskSelf() );
}

