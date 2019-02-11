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
 * ======== udpif.h ========
 *
 * UDP interface functions
 *
 */


#ifndef _UDPIF_INC_
#define _UDPIF_INC_

#define UDP_MSS_DEFAULT 1500        /* Default Max seg size */

/** 
 * @brief 
 *  The structure describes the UDP Statistics block.
 *
 * @details
 *  This structure is used to hold various stats and
 *  counters by the UDP module. A separate copy of this
 *  stats is maintained by the IPv4 and IPv6 stacks.
 */
typedef struct _udpstat {
    /**
     * @brief   Total UDP datagrams received.
     */
    UINT32  RcvTotal;       

    /**
     * @brief   Number UDP packets received with length 
     * shorter than UDP header length.
     */
    UINT32  RcvShort;       

    /**
     * @brief   Number of UDP packets received with length
     * larger than the packet size.
     */
    UINT32  RcvBadLen;      

    /**
     * @brief   Number of UDP packets received with checksum errs
     */
    UINT32  RcvBadSum;      

    /**
     * @brief   Number of UDP Packets dropped because of the receiver 
     * socket queue being full.
     */
    UINT32  RcvFull;        

    /**
     * @brief   Number of UDP packets received that are destined
     * to a port on the host on which there exists no listening
     * socket/application.
     */
    UINT32  RcvNoPort;      

    /**
     * @brief   Number of UDP multicast/broadcast packets received
     * that are destined to a port on the host stack on which there
     * exists no listening socket/application.
     */
    UINT32  RcvNoPortB;     

    /**
     * @brief   Total UDP packets sent.
     */
    UINT32  SndTotal;       

    /**
     * @brief   Packets dropped because of memory allocation problems.
     */
    UINT32  SndNoPacket;    

} UDPSTATS;

extern UDPSTATS udps;
extern PSEUDO   upseudo;

#ifdef _INCLUDE_IPv6_CODE
/* IPv6 UDP stats block */
extern UDPSTATS udp6_stats;
#endif

/* UDP Functions */
_extern void  UdpInput( PBM_Pkt *pPkt );
_extern int   UdpOutput( HANDLE h, UINT8 *pBuf, INT32 sz, INT32 *prsz );
_extern void  UdpChecksum( UDPHDR * );

#ifdef _INCLUDE_IPv6_CODE
_extern void Udp6Input (PBM_Pkt* pPkt, IPV6HDR* ptr_ipv6hdr);
_extern int  Udp6Output(HANDLE hSock, UINT8 *buf, INT32 size, INT32 *pRetSize);
#endif

#endif


