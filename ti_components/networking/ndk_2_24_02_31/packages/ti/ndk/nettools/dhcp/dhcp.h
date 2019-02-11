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
 * ======== dhcp.h ========
 *
 * Simple DHCP Client Utility
 *
 */

#ifndef _DHCP_H
#define _DHCP_H

#include <netmain.h>
#include <_stack.h>

#define NDHCPS              67
#define NDHCPC              68

#define SZCHADDR            16          /* size of client haddr field */
#define SZSNAME             64          /* size of server name field */
#define SZFNAME             128         /* size of file name field */

/*
 *  Size of DHCP options field.
 */
#define SZOPTIONS           312

/* values for op */
#define BOOTREQUEST         1
#define BOOTREPLY           2

/* Debug Flag(s) */
#define DEBUGON             0

/* values for htype and hlen */
#define ETHERNET            1
#define ELEN                6

/*
 *  Maximum size for DHCP client host name.
 *
 *  *** NOTE: changing this value requires a rebuild of NETTOOLS! ***
 *
 *  NOTE: The client hostname size is actually governed by 2 definitions:
 *      1) CFG_HOSTNAME_MAX (defined in netcfg.h)
 *      2) HOSTNAME_LENGTH (defined in dhcp.h)
 *  These two values must be consistent!  If one is changed, both must be
 *  changed.
 *
 *  RFC 2131 and 2132 do not clearly specify what the maximum size for this
 *  value should be.  255 was determined based on MSDN "Host Name Resolution for
 *  IPv4" on Microsoft's website (the size is [255 + 1] to make room for "\0"). 
 *  See notes for fix of CQ15114 for more details.
 *  
 */
#define HOSTNAME_LENGTH     256

#define BUFFER_SIZE         1024
#define MAX_DISCOVER_TRIES  12          /*  Maximum attempts in INIT State */

/* structure of a DHCP message */
typedef struct _dhcp
{
    INT8   op;                  /* request or reply */
    INT8   htype;               /* hardware type */
    INT8   hlen;                /* hardware address length */
    INT8   hops;                /* set to zero */
    UINT32  xid;                 /* transaction id */
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
} DHCP;

/* DHCP Message Types */
#define     DHCPDISCOVER        1
#define     DHCPOFFER           2
#define     DHCPREQUEST         3
#define     DHCPDECLINE         4
#define     DHCPACK             5
#define     DHCPNAK             6
#define     DHCPRELEASE         7
#define     DHCPINFORM          8

/* structure of a DHCP lease information */
typedef struct _dhcpLEASE
{
    UINT16 StateInitial;        /* Starting State */
    UINT16 State;               /* Current State */
    UINT16 StateNext;           /* Next State */
    IPN    IPAddress;           /* IP Address from DHCP Server */
    IPN    IPAddressOld;        /* IP Address being used */
    IPN    IPSubnetMask;        /* IP SubnetMask */
    IPN    IPGate;              /* IP Gateway Address */
    UINT32 LeaseExpires;        /* Time to moved to Init State */
    UINT32 LeaseTime;           /* Lease Time from Server */
    UINT32 RenewalT1Time;       /* Renewal T1 Time Fron Server */
    UINT32 RenewalT2Time;       /* Renewal T2 Time from Server */
    IPN    IPServer;            /* Server Address */
    UINT32 LeaseStartTime;      /* Time REQUEST was sent */
    UINT32 T1;                  /* Time to moved to Renewing State */
    UINT32 T2;                  /* Time to moved to Rebinding State */
    UINT32 T3;                  /* Time to moved to Init State (Lease Expired) */
    UINT32 Xid;                 /* transaction Id */
    INT16  MaxDiscoverTries;
    char   MacAddress[ELEN];    /* The MAC address of the target interface */
    HANDLE hCb;                 /* Handle for callback function */
    void   (*pCb)(HANDLE,uint); /* Callback function for results */
    uint   IfIdx;               /* Index to pysical DHCP interface */
    HANDLE dhcpTASK;            /* HANDLE to the task for this instance */
    HANDLE hCE_IPAddr;          /* HANDLE to CfgEntry of IP Network */
    HANDLE hCE_IPGate;          /* HANDLE to CfgEntry of installed IP Gateway */
    int    ReceivedSize;
    int    SendSize;
    SOCKET Sock;
    struct sockaddr_in sin1;
    INT8   DomainName[SZFNAME]; /* domain name */
    char   HostName[HOSTNAME_LENGTH];
	UINT8  ClientID[HOSTNAME_LENGTH];	/* Client Identifier to be used. */
    char   Buffer[BUFFER_SIZE]; /* Transmit/Receive  buffer */
    UINT8  *pOptions;           /* options to request */
    int    options_len;         /* length of options */
} DHCPLEASE;


#define RFC1084 0x63825363      /* vendor magic cookie from 1084 */

/* States */
enum DhcpState
{
    STATEZERO,
    BOUND,
    INIT,
    REBINDING,
    REBOOTING,
    RENEWING,
    REQUESTING,
    SELECTING,
    DHCPEND
};

/* Errors */
enum DhcpErrors
{
    DHCP_NOERROR=0,
    DHCP_ERR_ISSET,
    DHCP_ERR_NAK,
    DHCP_ERR_OFFER,
    DHCP_ERR_RECV,
    DHCP_ERR_REQUEST,
    DHCP_ERR_SELECT,
    DHCP_ERR_SEND,
    DHCP_ERR_END
};


/* Global Functions used only by DHCP */
extern int    dhcpSocketOpen(DHCPLEASE *pLease);
extern void   dhcpSocketClose(DHCPLEASE *pLease);
extern int    dhcpPacketSend( DHCPLEASE *pLease, IPN IPServer );
extern int    dhcpPacketReceive(DHCPLEASE *pLease);
extern int    dhcpState(DHCPLEASE *pLease);
extern int    dhcpBuildRequest(DHCPLEASE *pLease);
extern int    dhcpBuildDecline(DHCPLEASE *pLease);
extern int    dhcpBuildDiscover(DHCPLEASE *pLease);
extern UINT16 dhcpVerifyMessage(DHCPLEASE *pLease,IPN *pIPAddr,IPN *pIPServer);
extern void   dhcpPacketProcess(DHCPLEASE *pLease);
extern void   dhcpBuildOptions(UINT8 **pBuf, DHCPLEASE *pLease);
extern void   dhcpDecodeType( UINT8 tag, int length, UINT8 *data );
extern void   dhcpOptionsClear( void );

#endif /*  _DHCP_H */
