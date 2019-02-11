/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
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

/*!
 *   \file  raw_loopback.c
 *
 *   \brief
 *          Host PC (Linux) utility for doing raw external loopback
 *
 */



/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* OS/Posix headers */
#include <unistd.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>


/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#define DEFAULT_IF          "eth0"
#define DEFAULT_PACKET_CNT  (1024)
#define BUF_SIZ             (1536)


/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/* Ethernet Frame Header */
typedef struct ether_frame_header
{
    uint8_t dstMac[6];
    uint8_t srcMac[6];
    uint16_t etherType;
} __attribute__ ((packed)) ether_frame_header_t;

/* Ethernet Frame */
typedef struct ether_frame
{
    ether_frame_header_t header;
    uint8_t payload[ETH_DATA_LEN];
} __attribute__ ((packed)) ether_frame_t;


/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    int             sockfd;
    struct ifreq    if_idx;
    struct ifreq    if_mac;
    uint16_t        proto = 0x88B5;
    int             tx_len = 0;
    char            buffer[BUF_SIZ];
    char            ifName[IFNAMSIZ];
    uint32_t        dest[6];
    uint32_t        source[6];

    ether_frame_t               *ef     = (ether_frame_t *) buffer;
    ether_frame_header_t        *eh     = &ef->header;
    struct sockaddr_ll socket_address;

    uint32_t packetCnt      = 0;
    uint32_t totalPacketCnt = DEFAULT_PACKET_CNT;

    /* Get interface name */
    if (argc > 1)
    {
        strcpy(ifName, argv[1]);
        printf("ifName:\n\t%s\n", ifName);

        if (argc > 2)
        {
            /* Third argument, if given, is total packet count */
            uint32_t temp;
            sscanf(argv[2], "%d", &temp);
            if (temp < totalPacketCnt)
            {
                totalPacketCnt = temp;
            }
            printf("totalPacketCnt:\n\t%d\n", totalPacketCnt);
        }
    }
    else
    {
        strcpy(ifName, DEFAULT_IF);
    }

    /* Open RAW socket to recieve/send on */
    if ((sockfd = socket(AF_PACKET, SOCK_RAW, htons(proto))) == -1)
    {
        perror("socket");
    }

    /* Get the index of the interface to send on */
    memset(&if_idx, 0, sizeof(struct ifreq));
    strncpy(if_idx.ifr_name, ifName, IFNAMSIZ-1);
    if (ioctl(sockfd, SIOCGIFINDEX, &if_idx) < 0)
    {

        perror("SIOCGIFINDEX");
    }

    /* Get the MAC address of the interface to send on */
    memset(&if_mac, 0, sizeof(struct ifreq));
    strncpy(if_mac.ifr_name, ifName, IFNAMSIZ-1);
    if (ioctl(sockfd, SIOCGIFHWADDR, &if_mac) < 0)
    {
        perror("SIOCGIFHWADDR");
    }
    memcpy((void *)source, (void *)(if_mac.ifr_hwaddr.sa_data), 6);

    /* Clear the Ethernet header */
    memset(buffer, 0, BUF_SIZ);

    socket_address.sll_family = PF_PACKET;
    socket_address.sll_ifindex  = if_idx.ifr_ifindex;   /* Index of the network device */
    socket_address.sll_hatype   = ARPHRD_ETHER;         /* ARP hardware identifier is ethernet*/
    socket_address.sll_pkttype  = PACKET_OTHERHOST;     /* Target is another host*/
    socket_address.sll_halen    = ETH_ALEN;             /* Address length*/
    memcpy(socket_address.sll_addr, dest, 6);           /* Address */

    packetCnt = 0;
    while (packetCnt < totalPacketCnt)
    {
        /* Recv packet */
        tx_len = recvfrom(sockfd, buffer, ETH_FRAME_LEN, 0, NULL, NULL);
        if (-1 == tx_len)
        {
            printf("Recv failed\n");
            exit(-1);
        }
        else
        {
            printf("Recv'd packet %d with length of %d octets.\n", packetCnt, tx_len);
        }

        /* Move Rx source MAC addresses to Tx dest MAC address */
        memcpy((void *)eh->dstMac, (void *)&buffer[6], 6);
        /* Move Tx source MAC addresses */
        memcpy(eh->srcMac, source, 6);

        /* Send packet */
        if (sendto(sockfd, buffer, tx_len, 0, (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll)) < 0)
        {
            printf("Send failed\n");
            exit(-1);
        }

        /* Increment packetCnt */
        packetCnt++;
    }

    printf("Done!\n");

    return 0;
}


/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

