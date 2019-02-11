/*
 * Copyright (c) 2014-2015, Texas Instruments Incorporated
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
 */

/*
 *    ======== tcpEchoIPv6.c ========
 *    Contains BSD sockets code.
 */

#include <string.h>

#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <stdio.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* NDK BSD support */
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <unistd.h>
#include <netdb.h>

#define TCPPACKETSIZE 256
#define NUMTCPWORKERS 3

/*
 *  ======== tcpWorker ========
 *  Task to handle TCP connection. Can be multiple Tasks running
 *  this function.
 */
Void tcpWorker(UArg arg0, UArg arg1)
{
    int  clientfd = (int)arg0;
    int  bytesRcvd;
    int  bytesSent;
    char buffer[TCPPACKETSIZE];

    System_printf("tcpWorker: start clientfd = 0x%x\n", clientfd);

    while ((bytesRcvd = recv(clientfd, buffer, TCPPACKETSIZE, 0)) > 0) {
        bytesSent = send(clientfd, buffer, bytesRcvd, 0);
        if (bytesSent < 0 || bytesSent != bytesRcvd) {
            System_printf("Error: send failed.\n");
            break;
        }
    }
    System_printf("tcpWorker stop clientfd = 0x%x\n", clientfd);

    close(clientfd);
}

/*
 *  ======== tcpHandler ========
 *  Creates new Task to handle new TCP connections.
 */
Void tcpHandler(UArg arg0, UArg arg1)
{
    int                     status;
    int                     clientfd;
    int                     server;
    char                    port[8];
    struct addrinfo        *results = NULL;
    struct addrinfo        *currAddr = NULL;
    struct addrinfo         hints;
    struct sockaddr_storage clientAddr;
    socklen_t               addrlen = sizeof(clientAddr);
    int                     optval;
    int                     optlen = sizeof(optval);
    Task_Handle             taskHandle;
    Task_Params             taskParams;
    Error_Block             eb;

    /* Initialize local variables */
    server = -1;
    memset(&hints, 0, sizeof(hints));
    memset(&clientAddr, 0, addrlen);

    fdOpenSession(TaskSelf());

    /* Let NDK stack get initialized */
    TaskSleep(5000);

    /*
     *  Use getaddrinfo for generic socket set up code. The family (AF_INET or
     *  AF_INET6) is passed in via arg1 and dictates whether the socket is an
     *  IPv4 or IPv6 socket.
     */
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = (int)arg1;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    sprintf(port, "%d", arg0);
    status = getaddrinfo(NULL, port, &hints, &results);
    if (status != 0) {
        System_printf("tcpHandler: Error: getaddrinfo failed (%d).\n", status);
        return;
    }

    /*
     *  Cycle through the list of address structs returned from getaddrinfo,
     *  trying each until we succeed:
     */
    for (currAddr = results; currAddr != NULL; currAddr = currAddr->ai_next) {
        server = socket(currAddr->ai_family, currAddr->ai_socktype,
                currAddr->ai_protocol);
        if (server == -1) {
            System_printf("Error: socket not created.\n");
            goto nextaddr;
        }

        status = bind(server, currAddr->ai_addr, currAddr->ai_addrlen);
        if (status == -1) {
            System_printf("Error: bind failed.\n");
            goto nextaddr;
        }

        status = listen(server, NUMTCPWORKERS);
        if (status == -1) {
            System_printf("Error: listen failed.\n");
            goto nextaddr;
        }

        optval = 1;
        if (setsockopt(server, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen)
                == -1) {
            System_printf("Error: setsockopt failed\n");
            goto nextaddr;
        }

        /* We have a valid socket set up */
        break;

nextaddr:
        if (server > 0) {
            close(server);
        }
        server = -1;
    }

    freeaddrinfo(results);

    if (server == -1) {
        System_printf("Error: could not create a valid socket\n");
        return;
    }

    while ((clientfd =
            accept(server, (struct sockaddr *)&clientAddr, &addrlen)) != -1) {

        System_printf("tcpHandler: Creating thread clientfd = %d\n", clientfd);

        /* Init the Error_Block */
        Error_init(&eb);

        /* Initialize the defaults and set the parameters. */
        Task_Params_init(&taskParams);
        taskParams.arg0 = (UArg)clientfd;
        taskParams.stackSize = 1280;
        taskHandle = Task_create((Task_FuncPtr)tcpWorker, &taskParams, &eb);
        if (taskHandle == NULL) {
            System_printf("Error: Failed to create new Task\n");
            close(clientfd);
        }

        /* addrlen is a value-result param, must reset for next accept call */
        addrlen = sizeof(clientAddr);
    }

    System_printf("Error: accept failed.\n");

    if (server > 0) {
        close(server);
    }

    fdCloseSession(Task_self());
}

