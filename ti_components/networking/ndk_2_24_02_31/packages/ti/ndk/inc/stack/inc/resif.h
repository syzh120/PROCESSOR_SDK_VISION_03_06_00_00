/*
 * Copyright (c) 2012 - 2014, Texas Instruments Incorporated
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
 * ======== resif.h ========
 *
 * Basic resource and dispatch functions
 *
 */

#ifndef _C_RESIF_INC
#define _C_RESIF_INC  /* #defined if this .h file has been included */

/*----------------------------------------------------------------------- */
/*----[ Configuration ]-------------------------------------------------- */
/*----------------------------------------------------------------------- */

typedef struct _ipconfig {
        uint    IcmpDoRedirect;     /* Update RtTable on ICMP redirect (1=Yes) */
        uint    IcmpTtl;            /* TTL for ICMP messages RFC1700 says 64 */
        uint    IcmpTtlEcho;        /* TTL for ICMP echo RFC1700 says 64 */
        uint    IpIndex;            /* IP Start Index */
        uint    IpForwarding;       /* IP Forwarding (1 = Enabled) */
        uint    IpNatEnable;        /* IP NAT Enable (1 = Yes) */
        uint    IpFilterEnable;     /* IP Filtering Enable (1 = Yes) */
        uint    IpReasmMaxTime;     /* Max reassembly time in seconds */
        uint    IpReasmMaxSize;     /* Max reassembly packet size */
        uint    IpDirectedBCast;    /* Look for directed BCast IP addresses */
        uint    TcpReasmMaxPkt;     /* Max reasm pkts held by TCP socket */
        uint    RtcEnableDebug;     /* Enable Route Control Messages (1=On) */
        uint    RtcAdvTime;         /* Time in sec to send RtAdv (0=don't) */
        uint    RtcAdvLife;         /* Litetime of route in RtAdv */
        int     RtcAdvPref;         /* Preference Level (signed) in RtAdv */
        uint    RtArpDownTime;      /* Time 5 failed ARPs keep Rt down (sec) */
        uint    RtKeepaliveTime;    /* VALIDATED route timeout (sec) */
		uint    RtArpInactvity;		/* ARP Inactivity Timeout (sec) */
        uint    RtCloneTimeout;     /* INITIAL route timeout (sec) */
        uint    RtDefaultMTU;       /* Default MTU for internal routes */
        uint    SockTtlDefault;     /* Default Packet TTL */
        uint    SockTosDefault;     /* Default Packet TOS */
        int     SockMaxConnect;     /* Max Socket Connections */
        uint    SockTimeConnect;    /* Max time to connect (sec) */
        uint    SockTimeIo;         /* Default Socket IO timeout (sec) */
        int     SockTcpTxBufSize;   /* TCP Transmit buffer size */
        int     SockTcpRxBufSize;   /* TCP Receive buffer size (copy mode) */
        int     SockTcpRxLimit;     /* TCP Receive limit (non-copy mode) */
        int     SockUdpRxLimit;     /* UDP Receive limit */
        int     SockBufMinTx;       /* Min Tx space for "able to write" */
        int     SockBufMinRx;       /* Min Rx data for "able to read" */
        uint    PipeTimeIo;         /* Default Pipe IO timeout (sec) */
        int     PipeBufSize;        /* Pipe internal buffer size */
        int     PipeBufMinTx;       /* Min Tx space for "able to write" */
        int     PipeBufMinRx;       /* Min Rx data for "able to read" */
        uint    TcpKeepIdle;        /* Time (in 0.1 sec) connection muse be idle */
                                    /* for TCP to send first keepalive probe. */
        uint    TcpKeepIntvl;       /* Time (in 0.1 sec) between consecutive TCP */
                                    /* keep alive probes */
        uint    TcpKeepMaxIdle;     /* Time (in 0.1 sec) that a TCP connection can */
                                    /* go without responding to a probe before */
                                    /* being dropped */
        uint    IcmpDontReplyBCast; /* Don't Reply To ICMP ECHO REQ packets   */
                                    /* sent to BCast or Directed BCast */
        uint    IcmpDontReplyMCast; /* Don't Reply To ICMP ECHO REQ packets   */
                                    /* sent to Multi-Cast  */
        uint    RtGarp;             /* How to handle received gratuitous ARP   */
        uint    IcmpDontReplyEcho;  /* Don't Reply to ICMP ECHO packets   */
        uint    UdpSendIcmpPortUnreach; /* Send ICMP Port Unreach if UDP port  */
                                    /* is opened or not.   */
        uint    TcpSendRst;         /* Send RST if TCP port is opened or not.   */
        int     SockRawEthRxLimit;  /* Raw Ethernet Receive limit */
        } IPCONFIG;

extern IPCONFIG _ipcfg;             /* Configuration */

#define ICMP_DO_REDIRECT        (_ipcfg.IcmpDoRedirect)
#define ICMP_TTL                (_ipcfg.IcmpTtl)
#define ICMP_TTL_ECHO           (_ipcfg.IcmpTtlEcho)
#define ICMP_DONT_REPLY_BCAST   (_ipcfg.IcmpDontReplyBCast)
#define ICMP_DONT_REPLY_MCAST   (_ipcfg.IcmpDontReplyMCast)
#define ICMP_DONT_REPLY_ECHO    (_ipcfg.IcmpDontReplyEcho)
#define IP_INDEX                (_ipcfg.IpIndex)
#define IP_FORWARDING           (_ipcfg.IpForwarding)
#define IP_NATENABLE            (_ipcfg.IpNatEnable)
#define IP_FILTERENABLE         (_ipcfg.IpFilterEnable)
#define IP_REASM_MAXTIME        (_ipcfg.IpReasmMaxTime)
#define IP_REASM_MAXSIZE        (_ipcfg.IpReasmMaxSize)
#define IP_DIRECTED_BCAST       (_ipcfg.IpDirectedBCast)
#define TCP_REASM_MAXPKT        (_ipcfg.TcpReasmMaxPkt)
#define RTC_ENABLE_DEBUG        (_ipcfg.RtcEnableDebug)
#define RTC_RTADV_TIME          (_ipcfg.RtcAdvTime)
#define RTC_RTADV_LIFE          (_ipcfg.RtcAdvLife)
#define RTC_RTADV_PREF          (_ipcfg.RtcAdvPref)
#define RT_GARP                 (_ipcfg.RtGarp)
#define LLI_ARP_DOWN_TIME       (_ipcfg.RtArpDownTime)
#define LLI_KEEPALIVE_TIMEOUT   (_ipcfg.RtKeepaliveTime)
#define LLI_INACTIVITY_TIMEOUT  (_ipcfg.RtArpInactvity)
#define ROUTE_CLONE_TIMEOUT     (_ipcfg.RtCloneTimeout)
#define ROUTE_DEFAULT_MTU       (_ipcfg.RtDefaultMTU)
#define SOCK_TTL_DEFAULT        (_ipcfg.SockTtlDefault)
#define SOCK_TOS_DEFAULT        (_ipcfg.SockTosDefault)
#define SOCK_MAXCONNECT         (_ipcfg.SockMaxConnect)
#define SOCK_TIMECONNECT        (_ipcfg.SockTimeConnect)
#define SOCK_TIMEIO             (_ipcfg.SockTimeIo)
#define SOCK_TCPTXBUF           (_ipcfg.SockTcpTxBufSize)
#define SOCK_TCPRXBUF           (_ipcfg.SockTcpRxBufSize)
#define SOCK_TCPRXLIMIT         (_ipcfg.SockTcpRxLimit)
#define SOCK_UDPRXLIMIT         (_ipcfg.SockUdpRxLimit)
#define SOCK_RAWETHRXLIMIT      (_ipcfg.SockRawEthRxLimit)
#define SOCK_BUFMINTX           (_ipcfg.SockBufMinTx)
#define SOCK_BUFMINRX           (_ipcfg.SockBufMinRx)
#define PIPE_TIMEIO             (_ipcfg.PipeTimeIo)
#define PIPE_BUFSIZE            (_ipcfg.PipeBufSize)
#define PIPE_BUFMINTX           (_ipcfg.PipeBufMinTx)
#define PIPE_BUFMINRX           (_ipcfg.PipeBufMinRx)
#define TCP_KEEP_IDLE           (_ipcfg.TcpKeepIdle)
#define TCP_KEEP_INTVL          (_ipcfg.TcpKeepIntvl)
#define TCP_KEEP_MAXIDLE        (_ipcfg.TcpKeepMaxIdle)
#define TCP_SEND_RST            (_ipcfg.TcpSendRst)
#define UDP_SEND_ICMP_PORTUNREACH (_ipcfg.UdpSendIcmpPortUnreach)


/* IP Stack Config Default Values */
#define DEF_ICMP_DO_REDIRECT        1
#define DEF_ICMP_TTL                64
#define DEF_ICMP_TTL_ECHO           255
#define DEF_ICMP_DONT_REPLY_BCAST   0       /* 0 = Reply  */
#define DEF_ICMP_DONT_REPLY_MCAST   0       /* 0 = Reply  */
#define DEF_ICMP_DONT_REPLY_ECHO    0       /* 0 = Reply  */
#define DEF_IP_INDEX                1
#define DEF_IP_FORWARDING           0
#define DEF_IP_NATENABLE            0
#define DEF_IP_FILTERENABLE         0
#define DEF_IP_REASM_MAXTIME        10
#define DEF_IP_REASM_MAXSIZE        3020
#define DEF_IP_DIRECTED_BCAST       1
#define DEF_TCP_REASM_MAXPKT        2
#define DEF_RTC_ENABLE_DEBUG        0
#define DEF_RTC_RTADV_TIME          0   /* Normally 15 when "forwarding" */
#define DEF_RTC_RTADV_LIFE          120
#define DEF_RTC_RTADV_PREF          0
#define DEF_RT_RTGARP               0  /* Do not update routing table */
#define DEF_LLI_ARP_DOWN_TIME       20
#define DEF_LLI_KEEPALIVE_TIMEOUT   120
#define DEF_LLI_INACTIVITY_TIMEOUT	3
#define DEF_ROUTE_CLONE_TIMEOUT     120
#define DEF_ROUTE_DEFAULT_MTU       1500
#define DEF_SOCK_TTL_DEFAULT        64
#define DEF_SOCK_TOS_DEFAULT        0
#define DEF_SOCK_MAXCONNECT         8
#define DEF_SOCK_TIMECONNECT        80
#define DEF_SOCK_TIMEIO             0
#define DEF_SOCK_TCPTXBUF           8192
#define DEF_SOCK_TCPRXBUF           8192
#define DEF_SOCK_TCPRXLIMIT         8192
#define DEF_SOCK_UDPRXLIMIT         8192
#define DEF_SOCK_RAWETHRXLIMIT      8192
#define DEF_SOCK_BUFMINTX           2048
#define DEF_SOCK_BUFMINRX           1
#define DEF_PIPE_TIMEIO             0
#define DEF_PIPE_BUFSIZE            2048
#define DEF_PIPE_BUFMINTX           256
#define DEF_PIPE_BUFMINRX           1
#define DEF_TCP_KEEP_IDLE           72000   /* 2 hours */
#define DEF_TCP_KEEP_INTVL          750     /* 75 seconds */
#define DEF_TCP_KEEP_MAXIDLE        6000    /* 10 minutes */
#define DEF_TCP_SEND_RST            1       /* 1 = Send  */
#define DEF_UDP_SEND_ICMP_PORTUNREACH 1     /* 1 = Send  */

/*----------------------------------------------------------------------- */
/*----[ EXEC ]----------------------------------------------------------- */
/*----------------------------------------------------------------------- */

/* Global Task Identifiers */
#define ID_NULL         0
#define ID_LLI          1
#define ID_IP           2
#define ID_ROUTE        3
#define ID_NAT          4
#define ID_RTC          5
#define ID_IGMP         6

#ifdef _INCLUDE_IPv6_CODE
/*--- */
#define ID_IPV6		7
#define ID_LLIV6		8
#define ID_BIND6        9
#define ID_ROUTE6       10

#define ID_LAST         10
#else
/*--- */
#define ID_LAST         6
#endif /* _INCLUDE_IPv6_CODE */

/* Size of message block assigned to each task */
#define MSG_BLOCK                       50

/* The first "MSG_BLOCK" messages are reserved */
#define MSG_EXEC_SYSTEM_INIT            1
#define MSG_EXEC_SYSTEM_SHUTDOWN        2
#define MSG_EXEC_LOW_RESOURCES          3

#define ExecHType(x) (((HDATA*)x)->Type)

/* Exec Functions */
_extern void    ExecOpen();
_extern void    ExecClose();
_extern void    ExecTimer();        /* 1/10th second timer */
_extern void    ExecLowResource();
_extern void    ExecHRef( HANDLE );

/*----------------------------------------------------------------------- */
/*----[ TIMER ]---------------------------------------------------------- */
/*----------------------------------------------------------------------- */

/* Timer Access Functions */
_extern void    TimerHSTick();
_extern HANDLE  TimerNew( void (*pHandler)(uint), uint HSCount, uint Msg );
_extern void    TimerFree(HANDLE);

/*----------------------------------------------------------------------- */
/*----[ SB ]------------------------------------------------------------- */
/*----------------------------------------------------------------------- */

/* SB Structure */
typedef struct _sb {
             uint       Type;           /* Set to TYPE_SB */
             uint       Mode;           /* Set to LINEAR or ATOMIC */
             INT32      Total;          /* Total readable chars in buffer */
             INT32      Max;            /* High water mark */
             INT32      Min;            /* Low water mark */
             INT32      Head;           /* Head Ptr Offset (Linear) */
             INT32      Tail;           /* Tail Ptr Offset (Linear) */
             UINT8      *pData;         /* Data Buffer     (Linear) */
             PBM_Pkt    *pPktFirst;     /* First Pkt       (Atomic) */
             PBM_Pkt    *pPktLast;      /* Last Pkt        (Atomic) */
           } SB;

/* SB Modes */
#define SB_MODE_LINEAR          1
#define SB_MODE_ATOMIC          2
#define SB_MODE_HYBRID          3

/* Access functions */
_extern HANDLE SBNew( INT32  Max, INT32  Min, uint wMode );
_extern void   SBFree( HANDLE h );
_extern void   SBFlush( HANDLE h, uint fFree );
_extern INT32  SBRead( HANDLE h, INT32 Size, INT32 Offset, UINT8 *pbDst,
                      IPN *pIPFrom, uint *pPortFrom, UINT8 flagPeek );
_extern PBM_Pkt *SBReadNC( HANDLE h, IPN *pIPFrom, uint *pPortFrom );
_extern INT32  SBWrite( HANDLE h, INT32 Size, void *pData, PBM_Pkt *pPkt );
_extern INT32  SBSetMax( HANDLE h, INT32 Max );

#ifdef _STRONG_CHECKING
_extern INT32  SBGetTotal( HANDLE h );
_extern INT32  SBGetMax( HANDLE h );
_extern INT32  SBGetMin( HANDLE h );
_extern void   SBSetMin( HANDLE h, UINT32 value );
_extern INT32  SBGetSpace( HANDLE h );
#else
#define SBGetTotal( h )         (((SB *)(h))->Total)
#define SBGetMax( h )           (((SB *)(h))->Max )
#define SBGetMin( h )           (((SB *)(h))->Min )
#define SBSetMin( h, x )        (((SB *)(h))->Min = (x))
#define SBGetSpace( h )         (((SB *)(h))->Max - ((SB *)(h))->Total )
#endif

#ifdef _INCLUDE_IPv6_CODE
/* Access functions */
_extern HANDLE SB6New( INT32  Max, INT32  Min, uint wMode );
_extern void   SB6Free( HANDLE h );
_extern void   SB6Flush( HANDLE h, uint fFree );
_extern INT32  SB6Read( HANDLE h, INT32 Size, INT32 Offset, UINT8 *pbDst, PSA_IN6 pPeer, UINT8 flagPeek );
_extern INT32  SB6Write( HANDLE h, INT32 Size, void *pData, PBM_Pkt *pPkt );
_extern INT32  SB6SetMax( HANDLE h, INT32 Max );

#define SB6GetTotal( h )         (((SB *)(h))->Total)
#define SB6GetMax( h )           (((SB *)(h))->Max )
#define SB6GetMin( h )           (((SB *)(h))->Min )
#define SB6SetMin( h, x )        (((SB *)(h))->Min = (x))
#define SB6GetSpace( h )         (((SB *)(h))->Max - ((SB *)(h))->Total )

#endif /* _INCLUDE_IPv6_CODE */

/*----------------------------------------------------------------------- */
/*----[ IF ]------------------------------------------------------------- */
/*----------------------------------------------------------------------- */

/*------------------------------------------------------------------------- */
/* Generic IF Device Structure */

typedef struct _ifdev {
        uint        Type;                     /* Set to HTYPE_ETH */
        uint        llIndex;                  /* Low-level Device Index */
        uint        ProtMTU;                  /* MTU of payload */
       } IFDEV;

/*----------------------------------------------------------------------- */
/* Generic IF Access Functions */

/* NIMU */
#define         IFGetType(h)              (((NETIF_DEVICE *)(h))->type)
#define         IFGetIndex( h )           (((NETIF_DEVICE *)(h))->index)
#define         IFGetMTU( h )             (((NETIF_DEVICE *)(h))->mtu)

#endif
