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
 * ======== netdf.h ========
 *
 * Basic network data formats
 *
 */

#ifndef _C_NETDF_INC
#define _C_NETDF_INC  /* #defined if this .h file has been included */

/*---------------- */
/* Ethernet Header */
#define ETHHDR_SIZE     14

typedef struct {
                UINT8   DstMac[6];
                UINT8   SrcMac[6];
                UINT16  Type;
               } ETHHDR;

/*---------------- */
/* VLAN Header */
#define VLANHDR_SIZE     4

typedef struct {
                UINT16  TCI;
                UINT16  EncapProtocol;
               } VLANHDR;

/*----------------------------------------------------------------------- */
/* Ethernet ARP Protocol Header */

#define ARPHDR_SIZE     28

typedef struct {
                UINT16   HardType;
                UINT16   ProtocolType;
                UINT8    HardSize;
                UINT8    ProtocolSize;
                UINT16   Op;
                UINT8    SrcAddr[6];
                UINT8    IPSrc[4];
                UINT8    DstAddr[6];
                UINT8    IPDst[4];
               } ARPHDR;

/*---------------------------------------------------- */
/* IP HEADER */

#define IPHDR_SIZE      20

typedef struct {
                UINT8    VerLen;
                UINT8    Tos;
                UINT16   TotalLen;
                UINT16   Id;
                UINT16   FlagOff;
                UINT8    Ttl;
                UINT8    Protocol;
                UINT16   Checksum;
                IPN      IPSrc;
                IPN      IPDst;
                UINT8    Options[1];
               } IPHDR;

/*---------------------------------------------------- */
/* IPv6 HEADER */

#define IPv6HDR_SIZE      40

typedef struct {
                UINT8    VerTC;
                UINT8    FlowLabel[3];
                UINT16   PayloadLength;
                UINT8    NextHeader;
                UINT8    HopLimit;
                IP6N     SrcAddr;
                IP6N     DstAddr;
               } IPV6HDR;

/*---------------------------------------------------- */
/* ICMP HEADER */

#define ICMPHDR_SIZE    4

typedef struct {
                UINT8    Type;
                UINT8    Code;
                UINT16   Checksum;
                UINT8    Data[1];
               } ICMPHDR;

#define ICMPREQHDR_SIZE 4

typedef struct {
                UINT16    Id;
                UINT16    Seq;
                UINT8     Data[1];
               } ICMPREQHDR;

#define ICMPRTAHDR_SIZE 12

typedef struct {
                UINT8    NumAddr;
                UINT8    Size;
                UINT16   Lifetime;
                struct _rta {
                             IPN     IPAddr;
                             INT32   Pref;
                        } rta[1];
               } ICMPRTAHDR;

/*---------------------------------------------------- */
/* ICMPv6 HEADER */

typedef struct {
                UINT8    Type;
                UINT8    Code;
                UINT16   Checksum;
               } ICMPV6HDR;

/*---------------------------------------------------- */
/* IGMP HEADER */

#define IGMPHDR_SIZE    8

typedef struct {
                UINT8    VerType;
                UINT8    MaxTime;
                UINT16   Checksum;
                IPN      IpAddr;
               } IGMPHDR;


/*---------------------------------------------------- */
/* TCP HEADER */

#define TCPHDR_SIZE     20

typedef struct {
                UINT16   SrcPort;
                UINT16   DstPort;
                UINT32   Seq;
                UINT32   Ack;
                UINT8    HdrLen;
                UINT8    Flags;
                UINT16   WindowSize;
                UINT16   TCPChecksum;
                UINT16   UrgPtr;
                UINT8    Options[1];
               } TCPHDR;

/*---------------------------------------------------- */
/* UDP HEADER */
#define UDPHDR_SIZE     8

typedef struct {
                UINT16   SrcPort;
                UINT16   DstPort;
                UINT16   Length;
                UINT16   UDPChecksum;
               } UDPHDR;

/* Pseudo Header for Checksum */
typedef struct {
                IPN     IPSrc;
                IPN     IPDst;
                UINT16  Length;
                UINT8   Null;
                UINT8   Protocol;
                } PSEUDO;

/*---------------------------------------------------- */
/* V6 PSEUDO HEADER */

typedef struct {
                IP6N     SrcAddr;
                IP6N     DstAddr;
                UINT32   PktLen;
                UINT8    Rsvd[3];
                UINT8    NxtHdr;
               } PSEUDOV6;

/*---------------------------------------------------- */
/* IPV6 Hop-by-Hop Options HEADER */

#define IPV6_HOPOPTSHDR_SIZE      2

typedef struct {
                UINT8    NextHeader;
                UINT8    HdrExtLen;
               } IPV6_HOPOPTSHDR;

/*---------------------------------------------------- */
/* IPV6 Routing HEADER */

#define IPV6_ROUTINGHDR_SIZE      4

typedef struct {
                UINT8    NextHeader;
                UINT8    HdrExtLen;
                UINT8    RoutingType;
                UINT8    SegmentsLeft;
               } IPV6_ROUTINGHDR;

/*---------------------------------------------------- */
/* IPV6 Routing HEADER Type 0 */

#define IPV6_RTGHDR_TYPE0_SIZE      8

typedef struct {
                UINT8    NextHeader;
                UINT8    HdrExtLen;
                UINT8    RoutingType;
                UINT8    SegmentsLeft;
                UINT8    Rsvd[4];
               } IPV6_RTGHDR_TYPE0;

/*---------------------------------------------------- */
/* IPV6 Fragmentation HEADER */

#define IPV6_FRAGHDR_SIZE      8

typedef struct {
                UINT8    NextHeader;
                UINT8    Rsvd;
                UINT16   FragOffset;
                UINT8    FragId[4];
               } IPV6_FRAGHDR;

/*---------------------------------------------------- */
/* IPV6 Destination Options HEADER */

#define IPV6_DSTOPTSHDR_SIZE      2

typedef struct {
                UINT8    NextHeader;
                UINT8    HdrExtLen;
               } IPV6_DSTOPTSHDR;

#endif /* _C_NETDF_INC */

