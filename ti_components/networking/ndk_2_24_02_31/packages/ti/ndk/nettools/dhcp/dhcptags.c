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
 * ======== dhcptags.c ========
 *
 * Simple DHCP Client Utility
 * See RFC 2132 for more information
 *
 */

#include "dhcp.h"

#define FIELD_BASESIZE  0x0F /* these bitmask allows you to see only the size */
#define FLG_IGNORE      0x10 /* bit specifies tag should be ignored */
#define FLG_DEFAULT     0x20 /* bit specifies option used by default */
#define FLG_ISSTRING    0x40 /* bit specifies option is string data */
#define FLG_ISADDRESS   0x80 /* bit specifies option is IP address data */

#define MAX_TYPE         76   /* the largest option we know about */

/* The following array specifies the minimum length of data and the */
/* type of data for each option type.  The type of data is stored in the */
/* upper 4 bits, and the length is stored in the lower 4 bits. */
/* There is one array element for each RFC 2132 code we know about. */
static UINT8 DHCPTypeCode[ MAX_TYPE + 1 ] = {
    FLG_IGNORE,                      /* 0 - pad */
    4 | FLG_ISADDRESS | FLG_DEFAULT, /* 1 - subnet mask */
    4,                               /* 2 - time offset */
    4 | FLG_ISADDRESS | FLG_DEFAULT, /* 3 - router */
    4 | FLG_ISADDRESS,               /* 4 - time server */
    4 | FLG_ISADDRESS,               /* 5 - name servers */
    4 | FLG_ISADDRESS | FLG_DEFAULT, /* 6 - domain name servers */
    4 | FLG_ISADDRESS,               /* 7 - log server */
    4 | FLG_ISADDRESS,               /* 8 - cookie server */
    4 | FLG_ISADDRESS,               /* 9 - LPR server */
    4 | FLG_ISADDRESS,               /* 10 - impress server */
    4 | FLG_ISADDRESS,               /* 11 - resource location server */
    1 | FLG_ISSTRING | FLG_IGNORE,   /* 12 - hostname */
    2,                               /* 13 - boot file size */
    1 | FLG_ISSTRING,                /* 14 - merit dump file */
    1 | FLG_ISSTRING | FLG_DEFAULT,  /* 15 - domain name */
    4 | FLG_ISADDRESS,               /* 16 - swap server */
    1 | FLG_ISSTRING,                /* 17 - root path */
    1 | FLG_ISSTRING,                /* 18 - extensions path */
    1,                               /* 19 - IP forwarding */
    1,                               /* 20 - non-local source routing */
    8 | FLG_ISADDRESS,               /* 21 - policy filter */
    2,                               /* 22 - maximum datagram reassembly size */
    1,                               /* 23 - default IP TTL */
    4,                               /* 24 - path MTU aging timeout */
    2,                               /* 25 - path MTU plateau table */
    2,                               /* 26 - interface MTU */
    1,                               /* 27 - all subnets are local */
    4 | FLG_ISADDRESS,               /* 28 - broadcast addresses */
    1,                               /* 29 - perform mask discovery */
    1,                               /* 30 - mask supplier */
    1,                               /* 31 - perform router discovery */
    4 | FLG_ISADDRESS,               /* 32 - router solicitation address */
    8 | FLG_ISADDRESS,               /* 33 - static route */
    1,                               /* 34 - trailer encapsulation */
    4,                               /* 35 - ARP cache timeout */
    1,                               /* 36 - ethernet encapsulation */
    1,                               /* 37 - TCP default TTL */
    4,                               /* 38 - TCP keepalive interval */
    1,                               /* 39 - TCP keepalive garbage */
    1,                               /* 40 - NIS domain */
    4 | FLG_ISADDRESS,               /* 41 - NIS servers */
    4 | FLG_ISADDRESS,               /* 42 - NIS time protocol servers */
    1 | FLG_ISSTRING,                /* 43 - vendor specific information */
    4 | FLG_ISADDRESS | FLG_DEFAULT, /* 44 - netbios name server */
    4 | FLG_ISADDRESS,               /* 45 - netbios datagram distribution server */
    1                 | FLG_DEFAULT, /* 46 - netbios node type */
    1 | FLG_ISSTRING  | FLG_DEFAULT, /* 47 - netbios scope */
    4 | FLG_ISADDRESS,               /* 48 - xwindows font server */
    4 | FLG_ISADDRESS,               /* 49 - xwindows display manager */
    4 | FLG_ISADDRESS,               /* 50 - requested IP address */
    4,                               /* 51 - IP address lease time */
    1,                               /* 52 - option overload */
    1,                               /* 53 - DHCP message type */
    4 | FLG_ISADDRESS,               /* 54 - server identifier */
    1 | FLG_ISSTRING,                /* 55 - parameter request list */
    1 | FLG_ISSTRING,                /* 56 - message */
    2 | FLG_ISSTRING,                /* 57 - maximum DHCP message size */
    4,                               /* 58 - renewal T1 time value */
    4,                               /* 59 - renewal T2 time value */
    2,                               /* 60 - vendor class identifier */
    2 | FLG_ISSTRING,                /* 61 - client identifier */
    1 | FLG_ISSTRING,                /* 62 - ??? */
    1 | FLG_ISSTRING,                /* 63 - ??? */
    1 | FLG_ISSTRING,                /* 64 - NIS+ domain */
    4 | FLG_ISADDRESS,               /* 65 - NIS+ servers */
    1 | FLG_ISSTRING,                /* 66 - TFTP server name */
    1 | FLG_ISSTRING,                /* 67 - bootfile name */
    4 | FLG_ISADDRESS,               /* 68 - mobile IP home agent */
    4 | FLG_ISADDRESS,               /* 69 - SMTP server */
    4 | FLG_ISADDRESS,               /* 70 - POP3 server */
    4 | FLG_ISADDRESS,               /* 71 - NNTP server */
    4 | FLG_ISADDRESS,               /* 72 - Default WWW server */
    4 | FLG_ISADDRESS,               /* 73 - Default finger server */
    4 | FLG_ISADDRESS,               /* 74 - Default IRC server */
    4 | FLG_ISADDRESS,               /* 75 - streettalk server */
    4 | FLG_ISADDRESS,               /* 76 - streettalk discovery assistance server */
};


/*
 * dhcpBuildOptions()
 *
 * Add options list to a DHCP packet. This will add a default
 * list of options, and then append on user supplied options
 */
void dhcpBuildOptions(UINT8 **pBuf, DHCPLEASE *pLease)
{
    UINT8 *pv;
    UINT8 *pvLen;
    UINT8 len;
    UINT8 tag;
    int   i;

    pv = *pBuf;

    /* Add the "REQUEST LIST" tag */
    *pv++ = DHCPOPT_PARAMETER_REQUEST_LIST;

    /* Save the length field pointer */
    pvLen = pv++;
    len   = 0;

    /* First add the default option tags */
    for( tag=0; tag<=MAX_TYPE; tag++ )
        if( DHCPTypeCode[tag] & FLG_DEFAULT )
        {
            *pv++ = tag;
            len++;
        }

    /* Now add the user option tags */
    for( i=0; i<pLease->options_len; i++ )
    {
        /* Get the tag */
        tag = *(pLease->pOptions+i);
        /* Add it if it was not in the default list */
        if( !(DHCPTypeCode[tag] & FLG_DEFAULT) )
        {
            *pv++ = tag;
            len++;
        }
    }

    /* Write out the final length */
    *pvLen = len;

    /* Return the new options pointer */
    *pBuf = pv;
}


/*
 * dhcpDecodeType()
 *
 * Lookup the tag type and put it into the default configuration 
 */
void dhcpDecodeType( UINT8 tag, int length, UINT8 *data )
{
    UINT8 code;
    int size;

    if ( !length )
        return;

    if ( tag <= MAX_TYPE )
    {
        /* read the type code */
        code = DHCPTypeCode[ tag ];
    }
    else
    {
        /* treat unknown types as strings of length 1 */
        code = 1 | FLG_ISSTRING;
    }

    /* if this tag should be ignored, skip it */
    if( code & FLG_IGNORE )
        return;

    /* pull out the size */
    size = code & FIELD_BASESIZE;

    /* if TAG isn't an IP address, it's raw data */
    if ( !(code & FLG_ISADDRESS) )
    {
        /* For fixed data (not string) we use "size" to */
        /* write to the configuration. Since a string is */
        /* variable, we use "length" */
        if( !(code & FLG_ISSTRING) )
        {
            if( length >= size )
                CfgAddEntry( 0, CFGTAG_SYSINFO, tag,
                             CFG_ADDMODE_NOSAVE, size, data, 0 );
        }
        else
        {
            CfgAddEntry( 0, CFGTAG_SYSINFO, tag,
                         CFG_ADDMODE_NOSAVE, length, data, 0 );
        }
    }
    else
    {
        /* TAG is IP address data, modulo "size" */
        while( length >= size )
        {
            CfgAddEntry( 0, CFGTAG_SYSINFO, tag,
                            CFG_ADDMODE_NOSAVE, size, data, 0 );
            length -= size;
            data   += size;
        }
    }
}

/*
 * dhcpOptionsClear()
 *
 * Clear all the DHCP option tags from the configuration
 */
void dhcpOptionsClear()
{
    int    tag;
    HANDLE hEntry;

#if DEBUGON
    DbgPrintf( DBG_INFO, "dhcpOptionsClear: Clearing DHCP options\n" );
#endif

    /* Go through the configuration tag by tag, removing entries */
    for ( tag = 1; tag <= MAX_TYPE; tag++ )
        if( !(DHCPTypeCode[tag] & FLG_IGNORE) )
            while( CfgGetEntry( 0, CFGTAG_SYSINFO, tag, 1, &hEntry ) )
                CfgRemoveEntry( 0, hEntry );
}


