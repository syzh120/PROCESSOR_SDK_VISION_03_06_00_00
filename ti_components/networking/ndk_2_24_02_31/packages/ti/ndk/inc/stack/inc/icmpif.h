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
 * ======== icmpif.h ========
 *
 */


#ifndef _C_ICMPIF_INC
#define _C_ICMPIF_INC  /* #defined if this .h file has been included */

/*----------------------------------------------------------------------- */
/* Standard ICMP Equates */

#define ICMP_ECHOREPLY                  0       /* echo reply */
#define ICMP_UNREACH                    3       /* dest unreachable, codes: */
#define     ICMP_UNREACH_NET            0       /* bad net */
#define     ICMP_UNREACH_HOST           1       /* bad host */
#define     ICMP_UNREACH_PROTOCOL       2       /* bad protocol */
#define     ICMP_UNREACH_PORT           3       /* bad port */
#define     ICMP_UNREACH_NEEDFRAG       4       /* IP_DF caused drop */
#define     ICMP_UNREACH_SRCFAIL        5       /* src route failed */
#define     ICMP_UNREACH_NET_UNKNOWN    6       /* unknown net */
#define     ICMP_UNREACH_HOST_UNKNOWN   7       /* unknown host */
#define     ICMP_UNREACH_ISOLATED       8       /* src host isolated */
#define     ICMP_UNREACH_NET_PROHIB     9       /* prohibited access */
#define     ICMP_UNREACH_HOST_PROHIB    10      /* ditto */
#define     ICMP_UNREACH_TOSNET         11      /* bad tos for net */
#define     ICMP_UNREACH_TOSHOST        12      /* bad tos for host */
#define     ICMP_UNREACH_FILTER_PROHIB  13      /* admin prohib */
#define     ICMP_UNREACH_HOST_PRECEDENCE 14     /* host prec vio. */
#define     ICMP_UNREACH_PRECEDENCE_CUTOFF 15   /* prec cutoff */
#define ICMP_SOURCEQUENCH               4       /* packet lost, slow down */
#define ICMP_REDIRECT                   5       /* shorter route, codes: */
#define     ICMP_REDIRECT_NET           0       /* for network */
#define     ICMP_REDIRECT_HOST          1       /* for host */
#define     ICMP_REDIRECT_TOSNET        2       /* for tos and net */
#define     ICMP_REDIRECT_TOSHOST       3       /* for tos and host */
#define ICMP_ECHO                       8       /* echo service */
#define ICMP_ROUTERADVERT               9       /* router advertisement */
#define ICMP_ROUTERSOLICIT              10      /* router solicitation */
#define ICMP_TIMXCEED                   11      /* time exceeded, code: */
#define     ICMP_TIMXCEED_INTRANS       0       /* ttl==0 in transit */
#define     ICMP_TIMXCEED_REASS         1       /* ttl==0 in reass */
#define ICMP_PARAMPROB                  12      /* ip header bad */
#define     ICMP_PARAMPROB_OPTABSENT    1       /* req. opt. absent */
#define ICMP_TSTAMP                     13      /* timestamp request */
#define ICMP_TSTAMPREPLY                14      /* timestamp reply */
#define ICMP_IREQ                       15      /* information request */
#define ICMP_IREQREPLY                  16      /* information reply */
#define ICMP_MASKREQ                    17      /* address mask request */
#define ICMP_MASKREPLY                  18      /* address mask reply */

#define ICMP_MAXTYPE                    18

/*------------------------------------------------------------------------- */
/* Statisics Data */

extern UINT32   _ICMPInErrors;
extern UINT32   _ICMPOutErrors;
extern UINT32   _ICMPIn[ ICMP_MAXTYPE+1 ];
extern UINT32   _ICMPOut[ ICMP_MAXTYPE+1 ];

/*----------------------------------------------------------------------- */
/* ICMP Functions */

_extern void   ICMPInput( PBM_Pkt *pPkt );

_extern void   ICMPChecksum( ICMPHDR *pIcHdr, uint Size );

_extern void   ICMPGenPacket( IPHDR *pIpHdr, HANDLE hIFRx,
                              uint Type, uint Code, UINT32 Aux );

_extern void   ICMPSendRtAdv( HANDLE hIF, uint wLife,
                              IPN IPAddr, long Pref );

#endif

