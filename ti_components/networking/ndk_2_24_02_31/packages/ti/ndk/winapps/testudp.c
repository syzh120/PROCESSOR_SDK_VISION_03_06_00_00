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
 * ======== testudp.c ========
 * Test the crude echo by sending to port 7 and waiting
 * for replies.
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "sockets.h"

#define UDP_LOW   1

/*
 * Maximum payload sizes over UDP
 *
 * A payload greater than 1472 bytes (IPv4) or 1452 (IPv6) requires a packet
 * size greater than 1514 bytes, which is the maximum over Ethernet.
 *
 * Ethernet Frame for IPv4:
 *
 *     [EthHdr (14)] [UdpHdr (8)] [Ipv4Hdr (20)] [payload (1472)]
 *
 *     (1514 = 14 + 8 + 20 + 1472)
 *
 * Ethernet Frame for IPv6:
 *
 *     [EthHdr (14)] [UdpHdr (8)] [Ipv6Hdr (40)] [payload(1452)]
 *
 *     (1514 = 14 + 8 + 40 + 1452)
 */
#define UDP_IPv4_MAXPAYLOAD  1472
#define UDP_IPv6_MAXPAYLOAD  1452

#define TIMEOUT   1         /* seconds */
#define BUFSIZE   1500
#define PORT      7

/*
 *  ======== main ========
 */
int main(int argc, char *argv[])
{
    SOCKET s;
    unsigned short port = PORT;
    char * buf = NULL;
    char * name = argv[0];
    char cnt;
    int testsize;
    int nr;
    int i;
    int sent = 0;
    int UDP_HIGH = 0;
    fd_set readfds;
    struct timeval timeout;
    time_t ts;
    int status = EXIT_SUCCESS;
    int value;
    struct addrinfo hints;
    struct addrinfo *results = NULL;
    char portString[10];

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [IPv4 or IPv6 addr] [update] [port]\n", name);
        status = EXIT_FAILURE;
        goto QUIT;
    }


    /* update (argv[2]) not used yet */

    if (argc > 3) {
        port = (unsigned short)strtoul(argv[3], NULL, 0);
    }

    /* convert the port into string format in order to pass it to getaddrinfo */
    sprintf(portString,"%d", port);

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

    /* set max UDP payload accordingly for IPv4/IPv6 to avoid fragmentation */
    if (results->ai_family == AF_INET) {
        UDP_HIGH = UDP_IPv4_MAXPAYLOAD;
        fprintf(stderr, "IPv4 address\n");
    }
    else if (results->ai_family == AF_INET6) {
        UDP_HIGH = UDP_IPv6_MAXPAYLOAD;
        fprintf(stderr, "IPv6 address\n");
    }
    else {
        fprintf(stderr, "error: unknown protocol family: %d\n",
                results->ai_family);
        status = EXIT_FAILURE;
        goto QUIT;
    }

    printf("\nTesting target client at %s:%d\n", argv[1], port);
    printf("Testing UDP packet payloads from %d to %d bytes...\n",
           UDP_LOW, UDP_HIGH);

    /* create socket. ai_family determined for us via getaddrinfo() call */
    if ((s = socket(results->ai_family, results->ai_socktype, 0)) < 0) {
        fprintf(stderr, "%s: failed socket (%d)\n", name, getError());
        status = errno;
        goto QUIT;
    }

    if (!(buf = malloc(BUFSIZE))) {
        printf("failed temp buffer allocation\n");
        status = EXIT_FAILURE;
        goto QUIT;
    }

    ts = time(0);

    testsize = UDP_LOW;

    while (!kbhit()) {
        cnt = testsize;
        for (i = 0; i < testsize; i++) {
            buf[i] = cnt++;
        }

        if ((sent = sendto(s, buf, testsize, 0, results->ai_addr, results->ai_addrlen)) < 0) {

            printf("send failed (%d)\n", getError());
            status = errno;
            goto QUIT;
        }

        /* Wait for data to be echoed back */

        FD_ZERO(&readfds);
        FD_SET(s, &readfds);
        timeout.tv_sec = TIMEOUT;
        timeout.tv_usec = 0;

        if (select(s + 1, &readfds, NULL, NULL, &timeout) != 1) {
            fprintf(stderr, "%s: failed on size %d\n", name, testsize);
            status = errno;
            goto QUIT;
        }

        nr = recv(s, buf, BUFSIZE, 0);
        if (nr != testsize) {
            fprintf(stderr, "%s: unexpected return from recv (%d)\n", name, nr);
            status = errno;
            goto QUIT;
        }

        /* Verify Data */
        cnt = testsize;
        for (i = 0; i < testsize; i++) {
            if (buf[i] != (char)cnt++) {
                fprintf(stderr, "%s: Data verify failed on byte %d of %d!\n", 
                    name, i, testsize - 1);
                goto QUIT;
            }
        }

        /* Bump test size */
        testsize++;
        if (testsize > UDP_HIGH) {
            printf("Test loop passed - resetting\n");
            testsize = UDP_LOW;
        }
    }

    status = EXIT_SUCCESS;

    printf("Exiting test. Time = %d seconds", (int)(time(0) - ts));

QUIT:
    if (buf) {
        free(buf);
    }

    if (s >= 0) {
        (void)closesocket(s);
    }

    socketsShutdown();

    return (status);
}
