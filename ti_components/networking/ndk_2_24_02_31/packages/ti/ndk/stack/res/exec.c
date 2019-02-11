/*
 * Copyright (c) 2012-2015, Texas Instruments Incorporated
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
 * ======== exec.c ========
 *
 * Dispatch executive
 *
 */

#include <stkmain.h>

/* Configuration Structure */
IPCONFIG _ipcfg = { DEF_ICMP_DO_REDIRECT,
                    DEF_ICMP_TTL,
                    DEF_ICMP_TTL_ECHO,
                    DEF_IP_INDEX,
                    DEF_IP_FORWARDING,
                    DEF_IP_NATENABLE,
                    DEF_IP_FILTERENABLE,
                    DEF_IP_REASM_MAXTIME,
                    DEF_IP_REASM_MAXSIZE,
                    DEF_IP_DIRECTED_BCAST,
                    DEF_TCP_REASM_MAXPKT,
                    DEF_RTC_ENABLE_DEBUG,
                    DEF_RTC_RTADV_TIME,
                    DEF_RTC_RTADV_LIFE,
                    DEF_RTC_RTADV_PREF,
                    DEF_LLI_ARP_DOWN_TIME,
                    DEF_LLI_KEEPALIVE_TIMEOUT,
                    DEF_LLI_INACTIVITY_TIMEOUT,
                    DEF_ROUTE_CLONE_TIMEOUT,
                    DEF_ROUTE_DEFAULT_MTU,
                    DEF_SOCK_TTL_DEFAULT,
                    DEF_SOCK_TOS_DEFAULT,
                    DEF_SOCK_MAXCONNECT,
                    DEF_SOCK_TIMECONNECT,
                    DEF_SOCK_TIMEIO,
                    DEF_SOCK_TCPTXBUF,
                    DEF_SOCK_TCPRXBUF,
                    DEF_SOCK_TCPRXLIMIT,
                    DEF_SOCK_UDPRXLIMIT,
                    DEF_SOCK_BUFMINTX,
                    DEF_SOCK_BUFMINRX,
                    DEF_PIPE_TIMEIO,
                    DEF_PIPE_BUFSIZE,
                    DEF_PIPE_BUFMINTX,
                    DEF_PIPE_BUFMINRX,
                    DEF_TCP_KEEP_IDLE,
                    DEF_TCP_KEEP_INTVL,
                    DEF_TCP_KEEP_MAXIDLE,
                    DEF_ICMP_DONT_REPLY_BCAST,
                    DEF_ICMP_DONT_REPLY_MCAST,
                    DEF_RT_RTGARP,
                    DEF_ICMP_DONT_REPLY_ECHO,
                    DEF_UDP_SEND_ICMP_PORTUNREACH,
                    DEF_TCP_SEND_RST,
                    DEF_SOCK_RAWETHRXLIMIT,
                  };

/* Task Structure */
typedef struct {
                void    (*pHandler)( uint );
                uint    TaskId;         /* Task ID */
               } TASK;

#define NUM_TASKS       ID_LAST

void LLIMsg( uint );
void RouteMsg( uint );
void NatMsg( uint );
void IPMsg( uint );
void TcpMsg( uint );
void RTCMsg( uint );

#ifdef _INCLUDE_IPv6_CODE
void IPv6FragMsg (uint);
void LLI6Msg  (uint);
void Bind6Msg (uint);
void Route6Msg (uint);
#endif

static TASK tasks[NUM_TASKS] = {
    { &LLIMsg,    ID_LLI    },
    { &IPMsg,     ID_IP     },
    { &RouteMsg,  ID_ROUTE  },
    { &NatMsg,    ID_NAT    },
    { &RTCMsg,    ID_RTC    },
    { &IGMPMsg,   ID_IGMP   },
#ifdef _INCLUDE_IPv6_CODE
    { &IPv6FragMsg,   ID_IPV6  },
    { &LLI6Msg,   ID_LLIV6  },
    { &Bind6Msg,  ID_BIND6  },
    { &Route6Msg, ID_ROUTE6 },
#endif
    };

/* Exec Status Codes */
#define ES_CLOSED       0
#define ES_READY        1
#define ES_OPEN         2
static uint ExecStatus = ES_CLOSED;

static void ExecBroadcast( uint Msg );

/*-------------------------------------------------------------------- */
/* ExecOpen() */
/* Prepare for execution */
/*-------------------------------------------------------------------- */
void ExecOpen()
{
    if( ExecStatus != ES_CLOSED )
    {
        DbgPrintf(DBG_ERROR,"ExecStart: Already Open");
        return;
    }

    /* Mark exec status as started */
    ExecStatus = ES_READY;

    /* Init the Task List */
    ExecBroadcast( MSG_EXEC_SYSTEM_INIT );

    /* Initialize Stats */
    /* (We also initialize TCP/ICMP/UDP/RAW stats here since they do not */
    /* have their own MSG routine) */
    mmZeroInit( &tcps, sizeof( TCPSTATS ) );
    _ICMPInErrors  = 0;
    _ICMPOutErrors = 0;
    mmZeroInit( _ICMPIn, sizeof( UINT32 ) * (ICMP_MAXTYPE+1) );
    mmZeroInit( _ICMPOut, sizeof( UINT32 ) * (ICMP_MAXTYPE+1) );
    mmZeroInit( &udps, sizeof( UDPSTATS ) );
    mmZeroInit( &raws, sizeof( RAWSTATS ) );
    /* Initialize the Raw Ethernet Channel Management Stats. */
    mmZeroInit( &raweths, sizeof( RAWETHSTATS ) );

    /* Initialize the Raw ethernet Socket Protocol block. */
    RawEthSockPcbInit();

#ifdef _INCLUDE_IPv6_CODE
    mmZeroInit( &tcp6_stats, sizeof( TCPSTATS ) );
    mmZeroInit( &udp6_stats, sizeof( UDPSTATS ) );
    mmZeroInit( &raw6_stats, sizeof( RAWSTATS ) );
    mmZeroInit( &icmp6stats, sizeof( ICMPV6STATS ) );
#endif

    /* Mark exec status as open */
    ExecStatus = ES_OPEN;
}

/*-------------------------------------------------------------------- */
/* ExecClose() */
/* Shutdown the system */
/*-------------------------------------------------------------------- */
void ExecClose()
{
    SockPcbCleanup();

    /*
	 *  Close ALL IPv4 sockets bound to wildcard address on stack
     *  shutdown/reboot (fix for SDOCM00115513)
	 */
    SockCleanPcb(SOCKPROT_TCP, INADDR_ANY);
    SockCleanPcb(SOCKPROT_UDP, INADDR_ANY);
    SockCleanPcb(SOCKPROT_RAW, INADDR_ANY);

#ifdef _INCLUDE_IPv6_CODE
    Sock6PcbCleanup();

    /*
	 *  Close ALL IPv6 sockets bound to wildcard address on stack
     *  shutdown/reboot (fix for SDOCM00115513)
	 */
    Sock6CleanPcb(SOCKPROT_TCP, IPV6_UNSPECIFIED_ADDRESS);
    Sock6CleanPcb(SOCKPROT_UDP, IPV6_UNSPECIFIED_ADDRESS);
    Sock6CleanPcb(SOCKPROT_RAW, IPV6_UNSPECIFIED_ADDRESS);
#endif
    RawEthSockPcbCleanup();
    ExecBroadcast( MSG_EXEC_SYSTEM_SHUTDOWN );
    ExecStatus = ES_CLOSED;
}

/*-------------------------------------------------------------------- */
/* ExecTimer() */
/* Called on 1/10th second intervals */
/*-------------------------------------------------------------------- */
void ExecTimer()
{
    static int count = 0;

    TcpTimeoutCheck();

#ifdef _INCLUDE_IPv6_CODE
    TCP6TimeoutCheck();
#endif

    if( ++count == 5 )
    {
        count = 0;
        TimerHSTick();
    }
}

/*-------------------------------------------------------------------- */
/* ExecHRef() */
/* References a handle, adding to the reference count */
/*-------------------------------------------------------------------- */
void ExecHRef( HANDLE h )
{
    HDATA* ph = (HDATA *)h;

#ifdef _STRONG_CHECKING
    if( !(ph->Type & HTYPE_FLAG_REFSUPPORT) )
    {
        DbgPrintf(DBG_ERROR,"ExecHRef: HTYPE %04x",ph->Type);
        return;
    }
#endif

    /* Standard Ref */
    if( ph->RefCount != 65535 )
        ph->RefCount++;
}

/*-------------------------------------------------------------------- */
/* ExecLowResource() */
/* Serious resource problem! */
/*-------------------------------------------------------------------- */
void ExecLowResource()
{
    /* This is a problem, but there's not much we can do. Some tasks */
    /* like IP and TCP may be holding an inordinate amount of resources, */
    /* so we notify everyone of the problem, and they should free up */
    /* all but essential memory. */

    /* The resource message is handled via a broadcast flag since it is */
    /* very important that all tasks get the message. */

    ExecBroadcast( MSG_EXEC_LOW_RESOURCES );
    SockPcbCleanup();
}

/*-------------------------------------------------------------------- */
/* ExecBroadcast() */
/* Call every task in the Task List with the supplied message value, */
/* using the system static message. */
/*-------------------------------------------------------------------- */
static void ExecBroadcast( uint Msg )
{
    int tmp1;

    /* Notify the Task List with broadcast message */
    for( tmp1=1; tmp1<=NUM_TASKS; tmp1++ )
        (*tasks[tmp1-1].pHandler)(Msg);
}

