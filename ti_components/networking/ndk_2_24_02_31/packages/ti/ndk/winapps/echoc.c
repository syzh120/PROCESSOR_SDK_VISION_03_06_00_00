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
 *  ======== echoc.c ========
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sockets.h"

#define PORT        7

#define BUFSIZE     8192
#define TESTSIZE    6500

/*
 *  ======== main ========
 */
int main(int argc, char *argv[])
{
    SOCKET s;
    unsigned short port = PORT;
    char *buf = NULL;
    int bufsize = BUFSIZE;
    char *name = argv[0];
    int i;
    int testsize;
    int trial;
    int nr;
    int show;
    int update = 1;
    int bytes;
    time_t ts;
    time_t tn;
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
    

    if (argc > 2) {
        update = (int)strtol(argv[2], NULL, 0);
    }

    if (argc > 3) {
        port = (unsigned short)strtoul(argv[3], NULL, 0);
    }

    /* convert the port into string format in order to pass it to getaddrinfo */
    sprintf(portString,"%d", port);

    /* initialize sockets environment */
    socketsStartup();

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

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
    if ((s = socket(results->ai_family, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "%s: failed socket (%d)\n", name, getError());
        status = errno;
        goto QUIT;
    }
    
    /* connect. ai_addr set to AF_INET or AF_INET6 by getaddrinfo() call */
    if (connect(s, results->ai_addr, results->ai_addrlen) < 0) {
        perror("connect: ");
        fprintf(stderr, "%s: failed connect (%d)\n", name, getError());
        status = errno;
        goto QUIT;
    }

    buf = malloc(bufsize);
    if (!buf) {
        fprintf(stderr, "%s: failed buffer allocation\n", name);
        goto QUIT;
    }

    testsize = TESTSIZE;
    trial = 0;
    bytes = 0;

    ts = time(0);

    while (!kbhit()) {
        trial++;
        show = !(trial % update);

        /* Fill buffer with a test pattern */
        for (i = 0; i < testsize; i++) {
            buf[i] = (char)i;
        }

        /* Send the buffer */
        if (show) {
            printf("%d Sending %d bytes ... ", trial, testsize);
        }

        if (send(s, buf, testsize, 0) < 0) {
            printf("send failed (%d)\n", getError());
            break;
        }

        /* Clear the buffer */
        memset(buf, 0, testsize);

        /* Try and receive the test pattern back */
        if (show) {
            printf("receive ... ");
        }

        for (i = 0; i < testsize; i += nr) {
            nr = recv(s, buf + i, bufsize - i, 0);
            if (nr <= 0) {
                perror("recv failed: ");
                fprintf(stderr,"%s: recv failed (%d)\n", name, getError());
                break;
            }
        }

        /* Verify reception size */
        if (i != testsize) {
            fprintf(stderr, "%s: received %d (not %d) bytes\n", name, i, testsize);
            break;
        }

        /* Verify the test pattern */
        if (show) {
            printf("verify ... ");
        }

        for (i = 0; i < testsize; i++) {
            if (buf[i] != (char)i) {
                fprintf(stderr, "%s: verify failed at byte %d\n", name, i);
                goto QUIT;
            }
        }

        if ((bytes + testsize) < bytes) {
            ts = time(0);
            bytes = 0;
        } 
        else {
            bytes += testsize;

            if (show) {
                tn = time(0) - ts;
                if (tn) {
                    printf("passed - %ld bytes/s\n", bytes / tn);
                }
                else {
                    printf("passed\n");
                }
            }
        }
    }

    status = EXIT_SUCCESS;

QUIT:
    if (buf) {
        free(buf);
    }

    if (s > 0) {
        closesocket(s);
    }

    if (results) {
        freeaddrinfo(results);
    }

    socketsShutdown();

    return (status);
}
