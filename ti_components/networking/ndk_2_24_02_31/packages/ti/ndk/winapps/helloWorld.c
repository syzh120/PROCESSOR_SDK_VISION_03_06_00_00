/*
 * Copyright (c) 2013, Texas Instruments Incorporated
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
 * ======== helloWorld.c ========
 * Test the crude echo by sending to port 7 and waiting
 * for a reply.
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "sockets.h"

#define PORT            7

#define MESSAGE         "Hello, World!"
#define TESTSIZE        64

#define TIMEOUT         1  /* seconds */

/*
 *  ======== main ========
 */
int main(int argc, char *argv[])
{
    SOCKET s;
    unsigned short port = PORT;
    char data[TESTSIZE] = MESSAGE;
    char *name = argv[0];
    fd_set readfds;
    struct timeval timeout;
    time_t ts;
    int nr;
    int status = EXIT_SUCCESS;
    int value;
    struct addrinfo hints;
    struct addrinfo *results = NULL;
    char portString[10];

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [IPv4 or IPv6 addr] [port]\n", name);
        status = EXIT_FAILURE;
        goto QUIT;
    }

    if (argc > 2) {
        port = (unsigned short)strtoul(argv[2], NULL, 0);
    }

    /* convert the port into string format in order to pass it to getaddrinfo */
    sprintf(portString,"%d", port);

    printf("\nTesting UDP echo server at %s:%d\n", argv[1], port);

    /* initialize sockets environment */
    socketsStartup();

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

    /*
     * getaddrinfo() fills in the results struct for us appropriately
     * depending on whether the IP address is v4 or v6
     *
     * argv[1] = IPv4 or IPv6 address passed in from command line
     * argv[2] = port number passed in from command line
     */
    value = getaddrinfo(argv[1], portString, &hints, &results);

    if (value != 0) {
        fprintf(stderr, "getaddrinfo failed: %d\n", value);
        if (value == -2 || value == 11004) {
            fprintf(stderr, "unrecognized IP address\n");
        }
        status = EXIT_FAILURE;
        goto QUIT;
    }

    /* create socket. ai_family determined for us via getaddrinfo() call */
    if ((s = socket(results->ai_family, results->ai_socktype, 0)) < 0) {
        fprintf(stderr, "%s: failed socket (%d)\n", name, getError());
        status = errno;
        goto QUIT;
    }
    
    ts = time(0);

    /* Send the string to the server */
    if (sendto(s, data, strlen(data), 0, results->ai_addr, results->ai_addrlen) < 0) {

        fprintf(stderr, "%s: send failed (%d)\n", name, getError());
        status = errno;
        goto QUIT;
    }

    /* Wait for the reply */
    FD_ZERO(&readfds);
    FD_SET(s, &readfds);

    timeout.tv_sec = TIMEOUT;
    timeout.tv_usec = 0;

    if (select(s + 1, &readfds, NULL, NULL, &timeout) != 1) {
        fprintf(stderr, "%s: timed out waiting for reply\n", name);
        status = errno;
        goto QUIT;
    }

    nr = (int)recv(s, data, sizeof(data), 0);

    if (nr > 0) {
        printf("\nReceived back %d bytes.\nData echoed: %s\n", nr, data);
        status = 0;
    } else {
        fprintf(stderr, "%s: recv failed (%d)\n", name, getError());
    }

    printf("Exiting test. Time = %d seconds\n", (int)(time(0) - ts));

QUIT:
    if (s >= 0) {
        (void)closesocket(s);
    }

    socketsShutdown();

    return (status);
}
