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
 * ======== dhcpbild.c ========
 *
 * Simple DHCP Client Utility
 *
 */

#include "dhcp.h"

static int dhcpBuildHeader(DHCPLEASE *pLease);

/*
 * dhcpBuildRequest()
 * Build a DHCP Packet
 * This function builds DHCPREQUEST
 */
int dhcpBuildRequest(DHCPLEASE *pLease)
{
    DHCP  *pb = (DHCP *)pLease->Buffer;
    UINT8  *pv;
    int offset;

#if DEBUGON
    DbgPrintf(DBG_INFO, "dhcpBuildRequest:\r\n");
#endif

    offset = dhcpBuildHeader(pLease);

    /* When requesting, we don't respond to ARP requests */
    if( pLease->State == REQUESTING )
        bzero( &pb->ciaddr, 4);
    else
        bcopy( &pLease->IPAddress, &pb->ciaddr, 4);

#if DEBUGON
    DbgPrintf(DBG_INFO, "dhcpBuildRequest: IPADDR 0x%X, ciaddr 0x%X\r\n",pLease->IPAddress,
            pb->ciaddr);
#endif

    pv = (UINT8 *) pb->options;
    pv += offset;

    /* DHCP Request */
    *pv++ = DHCPOPT_DHCP_MESSAGE_TYPE;
    *pv++ = 1;
    *pv++ = DHCPREQUEST;

    if (pLease->State == REQUESTING)
    {
       *pv++ = DHCPOPT_REQUESTED_IP_ADDRESS;
       *pv++ = 4;
       bcopy( &pLease->IPAddress, pv, 4 );
       pv += 4;

       *pv++ = DHCPOPT_SERVER_IDENTIFIER;
       *pv++ = 4;
       bcopy( &pLease->IPServer, pv, 4 );
       pv += 4;
    }

    dhcpBuildOptions(&pv, pLease);

    *pv = DHCPOPT_END;

    return( sizeof(DHCP) );
}

/*
 * dhcpBuildDecline()
 * Build a DHCP Packet
 * This function sends DHCPDISCOVER if there is no known server.
 * Otherwise; it will send a DHCPREQUEST.
 */
int dhcpBuildDecline(DHCPLEASE *pLease)
{
    DHCP  *pb = (DHCP *)pLease->Buffer;
    UINT8  *pv;
    int offset;

#if DEBUGON
    DbgPrintf(DBG_INFO, "dhcpBuildDecline:\r\n");
#endif

    offset = dhcpBuildHeader(pLease);

    pv = (UINT8 *) pb->options;
    pv += offset;

    /* DHCP Decline */
    *pv++ = DHCPOPT_DHCP_MESSAGE_TYPE;
    *pv++ = 1;
    *pv++ = DHCPDECLINE;

    *pv++ = DHCPOPT_REQUESTED_IP_ADDRESS;
    *pv++ = 4;
    bcopy( &pLease->IPAddress, pv, 4 );
    pv += 4;

    *pv++ = DHCPOPT_SERVER_IDENTIFIER;
    *pv++ = 4;
    bcopy( &pLease->IPServer, pv, 4 );
    pv += 4;

    *pv = DHCPOPT_END;

    return( sizeof(DHCP) );
}

/*
 * dhcpBuildDiscover()
 * Build a DHCP Packet
 * This function builds DHCPDISCOVER
 */
int dhcpBuildDiscover(DHCPLEASE *pLease)
{
    DHCP  *pb = (DHCP *)pLease->Buffer;
    UINT8  *pv;
    int offset;

#if DEBUGON
    DbgPrintf(DBG_INFO, "dhcpBuildDiscover:\r\n");
#endif

    offset = dhcpBuildHeader(pLease);

    pv = (UINT8 *) pb->options;
    pv += offset;

    /* DHCP Discover */
    *pv++ = DHCPOPT_DHCP_MESSAGE_TYPE;
    *pv++ = 1;
    *pv++ = DHCPDISCOVER;

    /* Add the Request List */
    dhcpBuildOptions(&pv, pLease);

    *pv = DHCPOPT_END;

    return( sizeof(DHCP) );
}

/* 
 * dhcpBuildHeader()
 * Build a DHCP Packet
 * This function sends DHCPDISCOVER if there is no known server.
 * Otherwise; it will send a DHCPREQUEST.
 */
int dhcpBuildHeader(DHCPLEASE *pLease)
{
    DHCP  *pb = (DHCP *)pLease->Buffer;
    UINT8  *pv;
    UINT32 Magic = htonl(RFC1084);
    int Length;

#if DEBUGON
    DbgPrintf(DBG_INFO, "dhcpBuildHeader: Start\r\n");
#endif

    bzero(pb, sizeof(DHCP));

    pb->op     = BOOTREQUEST;
    pb->htype  = ETHERNET;
    pb->hlen   = ELEN;
    pb->xid    = pLease->Xid;        /* A non-zero ID number */
    pb->secs   = 0;
    bcopy( pLease->MacAddress, pb->chaddr, ELEN);
    bcopy( &Magic, pb->options, 4);

    /* PV is our options pointer */
    pv = (UINT8 *) pb->options;
    pv += 4;

    /* Inset Tags */

    /* Client ID - It is recommened to supply this */
    /* RFC 2131 4.2. We check if the configuration supplied a  */
    /* Client Identifer; if not we will use the default MAC address */
    if (pLease->ClientID[0] == 0)
    {
        /* No Client Identifier specified in the configuration; use
         * the default MAC Address */
        *pv++ = DHCPOPT_CLIENT_IDENTIFIER;
        *pv++ = 7;
        *pv++ = 1;
        bcopy( pLease->MacAddress, pv, 6 );   /* Use MAC name for now. */
        pv += 6;
    }
    else
    {
        /* Use the configuration specified. */
        UINT8   clientIDLen;
        *pv++ = DHCPOPT_CLIENT_IDENTIFIER;

        /* Get the length of the client ID. It will be the first byte */
        clientIDLen = pLease->ClientID[0];

        /* Configure the Client Identifier length */
        *pv++ = clientIDLen + 1;

        /* Configure the type to be 0; because this contains another 
         * value besides the hardware type. */
        *pv++ = 0;

        /* Copy the client identifer */
        bcopy( &pLease->ClientID[1], pv, clientIDLen );
        pv += clientIDLen;
    }

    /* Our Hostname */
    /* RFC 2132  3.14 */

    *pv++ = DHCPOPT_HOSTNAME;
    Length = strlen(pLease->HostName);
    *pv++ = (UINT8)Length;
    bcopy( pLease->HostName, pv, Length );
    pv += Length;

    *pv = DHCPOPT_END;

    return((int)(pv - (UINT8 *)(pb->options)));
}

