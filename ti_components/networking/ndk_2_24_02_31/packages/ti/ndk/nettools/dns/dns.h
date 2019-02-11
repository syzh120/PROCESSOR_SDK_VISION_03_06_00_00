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
 * ======== dns.h ========
 *
 * Basic DNS Resolution Routine Private Include
 *
 */

#ifndef _DNS_H_
#define _DNS_H_

#include <netmain.h>
#include <_stack.h>

/* General Equates */
#define DNS_PORT                53        /* DNS UDP (and TCP) Port */
#define DNS_NAME_MAX            128       /* Max name we'll ever handle */
#define DNS_PACKET_MAX          512       /* Max DNS packet */
#define DNS_DEFAULT_TTL         (3600*4)  /* 4 Hours */
#define MAX_PACKET              1000      /* Packet buffer size we use */

/* Special return code from DnsCheckReply() */
#define DNSCODE_RETRY          -1

/* DNS Record */
typedef struct _dnsrec {
        struct      _dnsrec *pNext;     /* Next Record */
        UINT8       Name[DNS_NAME_MAX]; /* Domain/Query Name */
        UINT16      Type;               /* Record Type */
        UINT16      Class;              /* Record Class */
        UINT32      Ttl;                /* Time to live */
        UINT16      DataLength;         /* Valid Data Length */
        UINT8       Data[DNS_NAME_MAX]; /* Data */
        } DNSREC;

/* DNS Reply Record */
typedef struct _dnsreply {
        UINT16      Flags;              /* DNS reply code / RA / AA */
        UINT16      NumAns;             /* Number of answers */
        DNSREC      *pAns;              /* Chain of answers */
        UINT16      NumAuth;            /* Number of authorities */
        DNSREC      *pAuth;             /* Chain of authorities */
        UINT16      NumAux;             /* Number of additional records */
        DNSREC      *pAux;              /* Chain of additional records */
        } DNSREPLY;

/* DNS Packet */
typedef struct {
        UINT16      Id;                 /* Identification (from client) */
        UINT16      Flags;              /* Type Flags */
#define FLG_DNS_QR      0x8000          /* 0 - Query  1 - Response */
#define MASK_DNS_OP     0x7800          /* Opcode */
#define DNS_OP_STD      0x0000          /* Standard Query        (0) */
#define DNS_OP_INV      0x0800          /* Inverse Query         (1) */
#define DNS_OP_STATUS   0x1000          /* Server Status Request (2) */
#define FLG_DNS_AA      0x0400          /* Authorative answer 1 = Yes */
#define FLG_DNS_TC      0x0200          /* Truncated (reply larger than 512) */
#define FLG_DNS_RD      0x0100          /* Recursion Desired */
#define FLG_DNS_RA      0x0080          /* Recursion Available */
#define MASK_DNS_RES    0x0070          /* Reserved Bits */
#define MASK_DNS_RCODE  0x000F          /* Return Code */
        UINT16      NumQ;               /* Number of Queries */
        UINT16      NumA;               /* Number of Answers */
        UINT16      NumAuth;            /* Number of Authorities */
        UINT16      NumAux;             /* Number of Additional records */
        UINT8       Data[500];          /* Queries and Replies */
        } DNSHDR;

/* Resource Record Equates (that we use) */

/* 16 bit pointer detect */
#define RR_PTR          0xc0            /* When 2 MSBs set, cnt is a 16 bit ptr */

/* Record Class */
#define C_IN            1               /* Internet */

/* Record Types */
#define T_A             1               /* host address */
#define T_NS            2               /* authoritative name server */
#define T_CNAME         5               /* canonical name for an alias */
#define T_PTR           12              /* domain name pointer */
#define T_HINFO         13              /* host information */
/* New Type for IPv6 Host Address */
#define T_AAAA          28              /* IPv6 Host Address (RFC 3596) */

/* Shared Functions for Server and Client */
extern int  DNSResolveQuery(UINT16 ReqType, DNSREC *pQuery, DNSREPLY **ppReply);
extern void DNSReplyFree( DNSREPLY *pReply, uint fFreeReplyBuffer );

int DNSGetQuery( DNSHDR *pDNS, DNSREC *pQuery );
int DNSGetReply( DNSHDR *pDNS, UINT16 Id, int cc, DNSREPLY *pReply );
int DNSBuildRequest( DNSHDR *pDNS, UINT16 Id, DNSREC *pQuery );
int DNSBuildReply( DNSHDR *pDNS, UINT16 Id, DNSREC *pQ, DNSREPLY *pA );

/* Resource Records are UINT8 aligned */
/* These MACROS assume "p" is an UINT8 pointer */
#define DNSREAD16(s, p) { \
        (s) = ((UINT16)*(p) << 8) | ((UINT16)*((p)+1)); \
        (p) += 2; }

#define DNSREAD32(l, p) { \
        (l) = ((UINT32)*(p) << 24) | ((UINT32)*((p)+1) << 16) | \
              ((UINT32)*((p)+2) << 8) | ((UINT32)*((p)+3)); \
        (p) += 4; }

#define DNSWRITE16(s, p) { \
        *(p)++ = (UINT8)((s)>>8); \
        *(p)++ = (UINT8)(s); };

#define DNSWRITE32(l, p) { \
        *(p)++ = (UINT8)((l)>>24); \
        *(p)++ = (UINT8)((l)>>16); \
        *(p)++ = (UINT8)((l)>>8); \
        *(p)++ = (UINT8)(l); };

#endif
