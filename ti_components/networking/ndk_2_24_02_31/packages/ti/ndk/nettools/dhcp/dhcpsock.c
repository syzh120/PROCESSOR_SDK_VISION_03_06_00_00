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
 * ======== dhcpsock.c ========
 *
 * Simple DHCP Client Utility
 *
 */

#include "dhcp.h"

/* Create Parameters for Client and Server Addresses */

int dhcpSocketOpen( DHCPLEASE *pLease )
{
    struct timeval TimeWait;
    int            On;
    int            rc;
    int            reuse = 1;

    if( pLease->Sock != INVALID_SOCKET )
        return(0);

    pLease->Sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if( pLease->Sock == INVALID_SOCKET )
        return(1);

	/* Reuse the ports: This will ensure that multiple DHCP Clients can run at the same time and
     * bind does not return an error */
    if (setsockopt(pLease->Sock, SOL_SOCKET, SO_REUSEPORT, (char *)&reuse, sizeof(reuse)) < 0)
    {
        rc = 2;
        goto sockError;
    } 

    bzero( &pLease->sin1, sizeof(struct sockaddr_in) );
    pLease->sin1.sin_family      = AF_INET;
    pLease->sin1.sin_addr.s_addr = INADDR_ANY;
    pLease->sin1.sin_port        = htons(NDHCPC);

    /* Bind to IP=[0.0.0.0], Port=[DHCP Client] */
    if( bind( pLease->Sock, (PSA) &pLease->sin1, sizeof(pLease->sin1) ) < 0 )
    {
        rc = 2;
        goto sockError;
    }

    /* Set socket option to allow us to broadcast */
    On = 1;
    if( setsockopt( pLease->Sock, SOL_SOCKET, SO_BROADCAST,
                    &On, sizeof(int) ) < 0 )
    {
        rc = 3;
        goto sockError;
    }

    /* Set socket option to specifiy a default packet egress device */
    /* The SO_IFDEVICE option is specific to this stack. Otherwise; */
    /* the socket layer could not specify the egress device. */
    if( setsockopt( pLease->Sock, SOL_SOCKET, SO_IFDEVICE,
                    &pLease->IfIdx, sizeof(uint) ) < 0 )
    {
        rc = 4;
        goto sockError;
    }

    /* Set the SOCK recv timeout to be 3 seconds */
    TimeWait.tv_sec  = 3;
    TimeWait.tv_usec = 0;
    
    if (setsockopt(pLease->Sock, SOL_SOCKET, SO_RCVTIMEO, &TimeWait, sizeof(TimeWait)) < 0) {
        rc = 5;
        goto sockError;
    }
    return(0);

sockError:
    fdClose(pLease->Sock);
    pLease->Sock = INVALID_SOCKET;
    return(rc);
}

void dhcpSocketClose(DHCPLEASE *pLease)
{
    if (pLease->Sock != INVALID_SOCKET)
        fdClose(pLease->Sock);
    pLease->Sock = INVALID_SOCKET;
}

int dhcpPacketSend( DHCPLEASE *pLease, IPN IPServer )
{
    int rc;
    rc = 0;

    /* We'll send to the supplied server IP address */
    pLease->sin1.sin_addr.s_addr = IPServer;
    pLease->sin1.sin_port        = htons(NDHCPS);

    /* Send the DHCP request packet */
    if( sendto( pLease->Sock, pLease->Buffer, pLease->SendSize, 0,
                (struct sockaddr *)&pLease->sin1, sizeof(pLease->sin1) ) < 0 )
        rc = 1;

    return(rc);
}

int dhcpPacketReceive(DHCPLEASE *pLease)
{
    int rc;
    DHCP *pb = (DHCP *)pLease->Buffer;

    /*  Clear the Receive Buffer */
    bzero(pb, sizeof(DHCP));

#if DEBUGON
    DbgPrintf(DBG_INFO, "dhcpPacketReceive: PacketReceive\r\n");
#endif

    pLease->ReceivedSize = (int)recv( pLease->Sock, pLease->Buffer,
                                      BUFFER_SIZE, 0 );
    rc = pLease->ReceivedSize;

    if( !rc )
        rc = DHCP_ERR_RECV;

    return(rc);
}

