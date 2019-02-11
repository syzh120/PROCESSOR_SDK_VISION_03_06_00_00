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
 * ======== tfdtp_echo_test.c ========
 * Test the crude echo by sending to port 7 and waiting
 * for replies.
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "sockets.h"
#include "../../packages/ti/nsp/drv/inc/tfdtp_types.h"

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

#define TIMEOUT   5         /* seconds */
#define PORT      7
#define ETH_FRAME_SIZE 1500

/*
 *  ======== main ========
 */
int main(int argc, char *argv[])
{
    SOCKET s = NULL;
    unsigned short port = PORT;
    char * buf = NULL;
    char * name = argv[0];
    long cnt;
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
    FILE * input_fp = NULL;
    FILE * output_fp = NULL;
    char filename[1024];
    long file_size;
    tfdtp_packet_t udptest_tx;
    tfdtp_packet_t udptest_rx;
    unsigned int no_bytes;
    unsigned int max_payload_size;
    unsigned int payload_size;
    char recv_buf[ETH_FRAME_SIZE];
    unsigned int testhdr_size = sizeof(udptest_tx.header);
    unsigned int frame_size;
    char * frame_buffer = NULL;
    unsigned int frame_offset = 0;
    unsigned int total_seq = 0;
    unsigned int file_pos = 0;

    if (argc < 6) {
        fprintf(stderr, "Usage: %s [IPv4 or IPv6 addr] [port] [input] [output] [frame size]\n", name);
        status = EXIT_FAILURE;
        goto QUIT;
    }

    port = (unsigned short)strtoul(argv[2], NULL, 0);

    /* convert the port into string format in order to pass it to getaddrinfo */
    sprintf(portString, "%d", port);

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
        max_payload_size = UDP_IPv4_MAXPAYLOAD - testhdr_size;
    }
    else if (results->ai_family == AF_INET6) {
        UDP_HIGH = UDP_IPv6_MAXPAYLOAD;
        fprintf(stderr, "IPv6 address\n");
        max_payload_size = UDP_IPv6_MAXPAYLOAD - testhdr_size;
    }
    else {
        fprintf(stderr, "error: unknown protocol family: %d\n",
            results->ai_family);
        status = EXIT_FAILURE;
        goto QUIT;
    }

    printf("\nTesting target client at %s:%d\n", argv[1], port);
    printf("Max packet payloads %d bytes...\n", max_payload_size);

    /* create socket. ai_family determined for us via getaddrinfo() call */
    if ((s = socket(results->ai_family, results->ai_socktype, 0)) < 0) {
        fprintf(stderr, "%s: failed socket (%d)\n", name, getError());
        status = errno;
        goto QUIT;
    }

    /* Open & copy input file into ram */
    strcpy(filename, argv[3]);
    input_fp = fopen(filename, "rb");
    if (NULL == input_fp) {
        status = EXIT_FAILURE;
        goto QUIT;
    }
    fseek(input_fp, 0, SEEK_END);
    file_size = ftell(input_fp);
    rewind(input_fp);

    /* Open output file for writing */
    strcpy(filename, argv[4]);
    output_fp = fopen(filename, "wb");
    if (NULL == output_fp) {
        status = EXIT_FAILURE;
        goto QUIT;
    }

    /* Get frame size from input arg */
    frame_size = atoi(argv[5]);
    if ((frame_size == 0) || (frame_size > file_size))
    {
        fprintf(stderr, "%s: incorrect frame size (%d)\n", name, frame_size);
        status = EXIT_FAILURE;
        goto QUIT;
    }

    frame_buffer = malloc(frame_size);
    if (NULL == frame_buffer)
    {
        fprintf(stderr, "%s: failed to allocate buffer (%d)\n", name, getError());
        status = errno;
        goto QUIT;
    }

    total_seq = (frame_size + max_payload_size - 1) / max_payload_size;

    /* Initialize TFDTP Header */
    memset(&udptest_tx, 0, sizeof(udptest_tx));

    FD_ZERO(&readfds);
    FD_SET(s, &readfds);
    timeout.tv_sec = TIMEOUT;
    timeout.tv_usec = 0;

    printf("Start Transmitting...\n");

    ts = time(0);

    for (cnt = 0; cnt < file_size; cnt += frame_size)
    {
        if ((cnt + frame_size) > file_size)
        {
            break;
        }

        payload_size = max_payload_size;

        /* read file for frame size */
        no_bytes = fread(frame_buffer, 1, frame_size, input_fp);
        if (no_bytes != frame_size)
        {
            fprintf(stderr, "%s: failed to read %s (%d)\n", name, filename, getError());
            status = EXIT_FAILURE;
            goto QUIT;
        }

        for (i = 0, frame_offset = 0; i < total_seq; i++, frame_offset += payload_size)
        {
            udptest_tx.header.flags = TFDTP_VER;
            udptest_tx.header.seq_num = i;
            udptest_tx.header.total_seq_num = total_seq;
            udptest_tx.header.frame_offset = frame_offset;
            if (i == 0)
            {
                udptest_tx.header.flags |= TFDTP_SOF;
            }
            if (i == (total_seq-1))
            {
                /* Remaining data in the file */
                payload_size = frame_size - frame_offset;
                udptest_tx.header.flags |= TFDTP_EOF;
            }

            memcpy(&udptest_tx.payload, &frame_buffer[frame_offset], payload_size);

            if ((sent = sendto(s, &udptest_tx, (payload_size + testhdr_size),
                0, results->ai_addr, results->ai_addrlen)) < 0)
            {
                printf("send failed (%d)\n", getError());
                status = errno;
                goto QUIT;
            }
            udptest_tx.header.seq_num++;

            if (select(FD_SETSIZE, &readfds, NULL, NULL, &timeout) != 1) {
                fprintf(stderr, "%s: failed on size %d\n", name, payload_size + testhdr_size);
                status = errno;
                goto QUIT;
            }

            nr = recv(s, &udptest_rx, ETH_FRAME_SIZE, 0);
            if (nr != (payload_size + testhdr_size)) {
                fprintf(stderr, "%s: unexpected return from recv (%d)\n", name, nr);
                status = errno;
                goto QUIT;
            }

            if (udptest_rx.header.seq_num != i)
            {
                fprintf(stderr, "%s: recv'd packet (%d) / skip packet (%d)\n",
                                    name, udptest_rx.header.seq_num, i);
            }

            file_pos = udptest_rx.header.frame_id * frame_size + udptest_rx.header.frame_offset;
            status = fseek(output_fp, file_pos, SEEK_SET);
            if (status != 0)
            {
                goto QUIT;
            }
            /* Write data back to output file */
            no_bytes = fwrite(&udptest_rx.payload, 1, payload_size, output_fp);
            if (no_bytes != payload_size)
            {
                fprintf(stderr, "%s: failed to write %s (%d)\n", name, filename, getError());
                status = EXIT_FAILURE;
                goto QUIT;
            }
        }
        udptest_tx.header.frame_id++;
    }

    status = EXIT_SUCCESS;

    printf("Exiting test. Time = %d seconds", (int)(time(0) - ts));

QUIT:
    printf("\nTest Status [%d]\n", status);

    if (input_fp)
    {
        fclose(input_fp);
    }

    if (output_fp)
    {
        fclose(output_fp);
    }

    if (frame_buffer) {
        free(frame_buffer);
    }

    if (s >= 0) {
        (void)closesocket(s);
    }

    socketsShutdown();

    return (status);
}
