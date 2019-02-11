/*
 * Copyright (c) 2012, Texas Instruments Incorporated
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
 * ======== dhcps.h ========
 *
 * DHCP Server
 *
 */

#ifndef _DHCPS_H
#define _DHCPS_H

#include <netmain.h>
#include <_stack.h>

#define NDHCPS          67
#define NDHCPC          68

#define SZCHADDR        16              /* size of client haddr field */
#define SZSNAME         64              /* size of server name field */
#define SZFNAME         128             /* size of file name field */
#define SZOPTIONS       312             /* size of options field */

/* values for op */
#define BOOTREQUEST     1
#define BOOTREPLY       2

/* values for htype and hlen */
#define ETHERNET                1
#define ELEN                    6
#define BUFFER_SIZE             1024

/* structure of a DHCPS message */
typedef struct _dhcps
{
    INT8   op;                  /* request or reply */
    INT8   htype;               /* hardware type */
    INT8   hlen;                /* hardware address length */
    INT8   hops;                /* set to zero */
    UINT32 xid;                 /* transaction id */
    UINT16 secs;                /* time client has been trying */
    UINT16 flags;               /* Flags */
    INT32  ciaddr;              /* client IP address */
    INT32  yiaddr;              /* your (client) IP address */
    INT32  siaddr;              /* server IP address */
    INT32  giaddr;              /* gateway IP address */
    INT8   chaddr[SZCHADDR];    /* client hardware address */
    INT8   sname[SZSNAME];      /* Optional server host name, Null terminated */
    INT8   file[SZFNAME];       /* boot file name */
    INT8   options[SZOPTIONS];  /* Optional Parameter Field */
} DHCPS;

#define RFC1084         0x63825363      /* vendor magic cookie from 1084 */

/* DHCP Message Types */
#define     DHCPDISCOVER        1
#define     DHCPOFFER           2
#define     DHCPREQUEST         3
#define     DHCPDECLINE         4
#define     DHCPACK             5
#define     DHCPNAK             6
#define     DHCPRELEASE         7
#define     DHCPINFORM          8

#endif /*  _DHCPS_H */

