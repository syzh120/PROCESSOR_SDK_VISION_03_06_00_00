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
 * ======== ipif.h ========
 *
 */


#ifndef _C_IPIF_INC
#define _C_IPIF_INC  /* #defined if this .h file has been included */

/*----------------------------------------------------------------------- */
/* Global Task Information */

/* Defined Messages */
#define MSG_IP_TIMER                    (ID_IP*MSG_BLOCK + 0)

/*----------------------------------------------------------------------- */
/* Standard IP Equates */

/* IP FRAGMENTATION BITS */
#define IP_DF   0x4000                  /* Ip DON'T FRAGMENT Bit */
#define IP_MF   0x2000                  /* Ip MORE FRAGMENTS Bit */

/* IP Statistics */
typedef struct {
        UINT32  Total;          /* total packets received */
        UINT32  Odropped;       /* lost packets due to nobufs, etc. */
        UINT32  Badsum;         /* checksum bad */
        UINT32  Badhlen;        /* ip header length < data size */
        UINT32  Badlen;         /* ip length < ip header length */
        UINT32  Badoptions;     /* error in option processing */
        UINT32  Badvers;        /* ip version != 4 */
        UINT32  Forward;        /* packets forwarded */
        UINT32  Noproto;        /* unknown or unsupported protocol */
        UINT32  Delivered;      /* datagrams delivered to upper level */
        UINT32  Cantforward;    /* packets rcvd for unreachable dest */
        UINT32  CantforwardBA;  /* packets rcvd with illegal addressing */
        UINT32  Expired;        /* Packets not forwards becaused expired */
        UINT32  Redirectsent;   /* packets forwarded on same net */
        UINT32  Localout;       /* total ip packets generated here */
        UINT32  Localnoroute;   /* Local packets discarded due to no route */
        UINT32  Reassembled;    /* total packets reassembled ok */
        UINT32  Fragments;      /* fragments received */
        UINT32  Fragdropped;    /* frags dropped (dups, out of space) */
        UINT32  Fragtimeout;    /* fragments timed out */
        UINT32  Fragmented;     /* datagrams successfully fragmented */
        UINT32  Ofragments;     /* output fragments created */
        UINT32  Cantfrag;       /* don't fragment flag was set, etc. */
        UINT32  CacheHit;       /* Route cache hit */
        UINT32  CacheMiss;      /* Route cache miss */
        UINT32  Filtered;       /* packets filtered by firewall */
        } IPSTATS;

/* IP OPTIONS FLAGS */
#define IPOPT_EOL       0               /* End of Options */
#define IPOPT_NOP       1               /* NOP */
#define IPOPT_RR        7               /* Record Route */
#define IPOPT_TS        68              /* timestamp */
#define IPOPT_SECURITY  130             /*/provide s,c,h,tcc */
#define IPOPT_LSRR      131             /* Loose Source Record Route */
#define IPOPT_SATID     136             /* satnet id */
#define IPOPT_SSRR      137             /* Strict Source Record Route */
#define IPOPT_RA        148             /* router alert */

/* Offsets to fields in options other than EOL and NOP. */
#define IPOPT_OPTVAL        0       /* option ID */
#define IPOPT_OLEN      1       /* option length */
#define IPOPT_OFFSET        2       /* offset within option */
#define IPOPT_MINOFF        4       /* min value of above */

/* Global Statistics */
extern IPSTATS ips;

/* Access Functions */
_extern int    IPTxPacket( PBM_Pkt *pPkt, uint Flags );
_extern void   IPRxPacket( PBM_Pkt *pPkt );
_extern void   IPChecksum( IPHDR *pbHdr );
_extern HANDLE IPGetRoute( uint RtCallFlags, IPN IPDst );
_extern void   IPRtChange( HANDLE hRt );
_extern void   IPReasm( PBM_Pkt *pPkt );
_extern void   IPFilterSet( IPN IPAddr, IPN IPMask );

/* IP Tx Parameters */

/* --[ We asume that all SO_ supported flags are above 0xF ]---------- */
#if ((0xF & (SO_BROADCAST | SO_DONTROUTE)) != 0)
#error Flag Conflict with SOCKET.H
#endif
/* ------------------------------------------------------------------- */

/* Flags Parameter Values */
#define FLG_IPTX_FORWARDING     0x0001       /* Forwarding packet from IPRx */
#define FLG_IPTX_DONTFRAG       0x0002       /* Set the IP_DF bit */
#define FLG_IPTX_RAW            0x0004       /* All IP header is valid */
#define FLG_IPTX_SRCROUTE       0x0008       /* Packet was source routed */
#define FLG_IPTX_DONTROUTE      SO_DONTROUTE /* Send only to local subnets */
#define FLG_IPTX_BROADCAST      SO_BROADCAST /* Allow broadcast packets */
#define FLG_IPTX_SOSUPPORTED    (SO_DONTROUTE|SO_BROADCAST)

/* Return Values */
#define IPTX_SUCCESS            0               /* Packet OK */
#define IPTX_ERROR              EINVAL          /* Invalid packet */
#define IPTX_ERROR_UNREACH      EHOSTUNREACH    /* Route not found */
#define IPTX_ERROR_HOSTDOWN     EHOSTDOWN       /* Route not UP */
#define IPTX_ERROR_REJECTED     EHOSTDOWN       /* REJECT Route */
#define IPTX_ERROR_EACCES       EACCES          /* Illegal operation */
#define IPTX_ERROR_ADDRNOTAVAIL EADDRNOTAVAIL   /* Could not alloc MAC addr */
#define IPTX_ERROR_MSGSIZE      EMSGSIZE        /* Fragmentation failed */

#endif

