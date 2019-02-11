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
 */
/*
 *  ======== ping_rpmsg.c ========
 *
 *  Works with the ping_rpmsg BIOS sample over the rpmsg-proto socket.
 */

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/* Ipc Socket Protocol Family */
#include <net/rpmsg.h>

#define NUM_LOOPS_DFLT 100
#define CORE_ID_DFLT   0 /* CORE ID should be (MultiProc ID - 1) */

long diff(struct timespec start, struct timespec end)
{
    struct timespec temp;

    if ((end.tv_nsec - start.tv_nsec) < 0) {
        temp.tv_sec = end.tv_sec - start.tv_sec-1;
        temp.tv_nsec = 1000000000UL + end.tv_nsec - start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }

    return (temp.tv_sec * 1000000UL + temp.tv_nsec / 1000);
}

int main (int argc, char ** argv)
{
    unsigned int numLoops = NUM_LOOPS_DFLT;
    short coreId = CORE_ID_DFLT;
    int send_sock, err, recv_sock;
    struct sockaddr_rpmsg src_addr, dst_addr;
    socklen_t len;
    const char *msg = "Ping!";
    char buf[512];
    struct timespec   start,end;
    long              elapsed=0,delta;
    int i;
    fd_set rfds;

    /* Parse Args: */
    switch (argc) {
        case 1:
           /* use defaults */
           break;
        case 2:
           numLoops = atoi(argv[1]);
           break;
        case 3:
           numLoops   = atoi(argv[1]);
           coreId     = atoi(argv[2]);
           break;
        default:
           printf("Usage: %s [<numLoops>] [<CoreId>]\n", argv[0]);
           printf("\tDefaults: numLoops: %d; CoreId: %d\n",
                   NUM_LOOPS_DFLT, CORE_ID_DFLT);
           exit(0);
    }

    /* create an RPMSG socket */
    send_sock = socket(AF_RPMSG, SOCK_SEQPACKET, 0);
    if (send_sock < 0) {
        printf("socket failed for send_sock: %s (%d)\n", strerror(errno), errno);
        return -1;
    }

    /* connect to remote service */
    memset(&dst_addr, 0, sizeof(dst_addr));
    dst_addr.family = AF_RPMSG;
    dst_addr.vproc_id = coreId;
    dst_addr.addr = 51; // use 51 for ping_tasks;
    //dst_addr.addr = 61; // use 61 for messageQ transport;

    printf("Connecting to address 0x%x on vprocId %d\n",
            dst_addr.addr, dst_addr.vproc_id);

    len = sizeof(struct sockaddr_rpmsg);
    err = connect(send_sock, (struct sockaddr *)&dst_addr, len);
    if (err < 0) {
        printf("connect failed: %s (%d)\n", strerror(errno), errno);
        return -1;
    }

    /* let's see what local address we got */
    err = getsockname(send_sock, (struct sockaddr *)&src_addr, &len);
    if (err < 0) {
        printf("getsockname failed for send_sock: %s (%d)\n", strerror(errno), errno);
        return -1;
    }

    printf("Our address: send_sock: socket family: %d, proc id = %d, addr = %d\n",
                 src_addr.family, src_addr.vproc_id, src_addr.addr);

    /* bind a local endpoint for receiving responses */
    /* create an RPMSG socket */
    recv_sock = socket(AF_RPMSG, SOCK_SEQPACKET, 0);
    if (recv_sock < 0) {
        printf("socket failed for recv_sock: %s (%d)\n", strerror(errno), errno);
        return -1;
    }

    /* bind to the source address */
    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.family = AF_RPMSG;
    src_addr.vproc_id = coreId;
    src_addr.addr  = 51; // use 51 for ping_tasks;

    printf("Binding to address 0x%x on vprodId %d\n",
            src_addr.addr, src_addr.vproc_id);

    len = sizeof(struct sockaddr_rpmsg);
    err = bind(recv_sock, (struct sockaddr *)&src_addr, len);
    if (err < 0) {
        printf("bind failed: %s (%d)\n", strerror(errno), errno);
        return -1;
    }

    /* let's see what local address we got */
    err = getsockname(recv_sock, (struct sockaddr *)&src_addr, &len);
    if (err < 0) {
        printf("getsockname failed for recv_sock: %s (%d)\n", strerror(errno), errno);
        return -1;
    }

    printf("Our address: recv_sock: socket family: %d, proc id = %d, addr = %d\n",
                 src_addr.family, src_addr.vproc_id, src_addr.addr);

    FD_ZERO(&rfds);
    FD_SET(recv_sock, &rfds);

    printf("Sending \"%s\" in a loop.\n", msg);

    for (i = 0; i < numLoops; i++) {
        clock_gettime(CLOCK_REALTIME, &start);

        err = send(send_sock, msg, strlen(msg) + 1, 0);
        if (err < 0) {
            printf("sendto failed: %s (%d)\n", strerror(errno), errno);
            return -1;
        }

        err = select(recv_sock + 1, &rfds, NULL, NULL, NULL);

        /* if error, try again */
        if (err < 0) {
            printf("Warning: select failed, trying again\n");
            continue;
        }

        memset(&src_addr, 0, sizeof(src_addr));

        len = sizeof(src_addr);

        err = recvfrom(recv_sock, buf, sizeof(buf), 0,
                       (struct sockaddr *)&src_addr, &len);

        if (err < 0) {
            printf("recvfrom failed: %s (%d)\n", strerror(errno), errno);
            return -1;
        }
        if (len != sizeof(src_addr)) {
            printf("recvfrom: got bad addr len (%d)\n", len);
            return -1;
        }

        clock_gettime(CLOCK_REALTIME, &end);
        delta = diff(start,end);
        elapsed += delta;

        printf("%d: Received msg: %s, from: %d\n", i, buf, src_addr.addr);

        /*
        printf ("Message time: %ld usecs\n", delta);
        printf("Received a msg from address 0x%x on processor %d\n",
                           src_addr.addr, src_addr.vproc_id);
        printf("Message content: \"%s\".\n", buf);
        */
    }
    printf ("Avg time: %ld usecs over %d iterations\n", elapsed / i, i);

    close(send_sock);
    close(recv_sock);

    return 0;
}
