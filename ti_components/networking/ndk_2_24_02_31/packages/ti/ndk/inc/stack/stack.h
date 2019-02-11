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
 * ======== stack.h ========
 *
 * Main stack include
 *
 */

#ifndef _C_STACK_INC
#define _C_STACK_INC  /* #defined if this .h file has been included */

#ifndef _NDK_EXTERN_CONFIG /* Configuration overridden by Makefiles */
/*#define  _STRONG_CHECKING       // All handles checked */
/*#define  _INCLUDE_NAT_CODE      // Include NAT and IP filtering */
#define  _INCLUDE_PPP_CODE      /* Include PPP module */
#define  _INCLUDE_PPPOE_CODE    /* Enable PPPOE Client */
#endif

#include "inc/listlib.h"
#include "inc/netdf.h"
#include "inc/resif.h"
#include "inc/bindif.h"
#include "inc/etherif.h"
#include "inc/icmpif.h"
#include "inc/igmpif.h"
#include "inc/ipif.h"
#include "inc/lliif.h"
#include "inc/natif.h"
#include "inc/nodeif.h"
#include "inc/rawif.h"
#include "inc/routeif.h"
#include "inc/rtcif.h"
#include "inc/sockif.h"
#include "inc/pipeif.h"
#include "inc/tcpif.h"
#include "inc/udpif.h"
#include "inc/fdtif.h"
#include "inc/pppoeif.h"
#include "inc/pppif.h"
#include "inc/vlanif.h"
#include "inc/nimuif.h"
#include "inc/bind6if.h"
#include "inc/ip6if.h"
#include "inc/route6if.h"
#include "inc/lli6if.h"
#include "inc/icmp6if.h"
#include "inc/mldif.h"
#include "inc/rawethif.h"

/*---------------------------------------------------------------------- */
/* Handle Types */
/*---------------------------------------------------------------------- */

/* Standard REFERENCED Handle Structure */
typedef struct _hdata {
                uint    Type;          /* Handle Type (for generic dispatch) */
                uint    RefCount;      /* Handle Ref Count (when supported) */
               } HDATA;

#define HTYPE_FLAG_MASK         0xF000
#define HTYPE_FLAG_REFSUPPORT   0x1000

#define HTYPE_INDEX_MASK        0x0FFF
#define HTYPE_ETH               0x0001          /* Ethernet Device */
#define HTYPE_TIMER             0x0002          /* Timer */
#define HTYPE_LLI               0x0003          /* Link-level Info */
#define HTYPE_PKT               0x0004          /* Packet */
#define HTYPE_FRAG              0x0005          /* Memory Fragment */
#define HTYPE_NODE              0x1006          /* Route Node */
#define HTYPE_RT                0x1008          /* Route Entry */
#define HTYPE_BIND              0x0009          /* IP/IF Binding */
#define HTYPE_SOCK              0x000a          /* Socket */
#define HTYPE_SB                0x000b          /* Socket Buffer */
#define HTYPE_IPFRAG            0x000c          /* IP Packet Fragment */
#define HTYPE_FDTABLE           0x000d          /* File Descriptor Table */
#define HTYPE_FD                0x000e          /* File Descriptor */
#define HTYPE_NAT               0x000f          /* NAT Entry */
#define HTYPE_PIPE              0x0010          /* Pipe */
#define HTYPE_PROXY             0x0011          /* Proxy Delcaration */
#define HTYPE_PROXYENTRY        0x0012          /* Proxy Entry */
#define HTYPE_PPP               0x0013          /* PPP Device */
#define HTYPE_PPPOE_SERVER      0x0014          /* PPPOE Server */
#define HTYPE_PPPOE_CLIENT      0x0015          /* PPPOE Client */
#define HTYPE_SOCK6             0x0016          /* IPv6 Socket */
#define HTYPE_RAWETHSOCK        0x0017          /* Raw Ethernet Socket */
#define HTYPE_AUX               0x0fff          /* Non-registered Type */

/* Keep Timer Ticks here. Note slow timers are staggered using prime */
/* numbers for tick counts. */
#define TIMER_TICKS_LLI         2               /* Fast timer (for retries) */
#define TIMER_TICKS_RTC         11              /* Slow timer (RTADV msg) */
#define TIMER_TICKS_ROUTE       23              /* Slow timer (entry timeout) */
#define TIMER_TICKS_IP          29              /* Slow timer (reasm) */
#define TIMER_TICKS_NAT         31              /* Slow timer (entry timeout) */

#ifdef _INCLUDE_IPv6_CODE
#define TIMER_TICKS_IPV6_REASM  2               /* Fast timer (for IPv6 fragment reassembly) */
#define TIMER_TICKS_BIND6       2               /* Fast Timer for V6 Address LT Management */
#endif

#endif
