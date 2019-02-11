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
 * ======== tcp.h ========
 *
 * TCP private data
 *
 */

#ifndef _TCP_INC_
#define _TCP_INC_

/*----------------------------------------------------------------------- */
/* Global Task Information */

/* TCP Header Option Definitions */
#define TCPOPT_EOL              0
#define TCPOPT_NOP              1
#define TCPOPT_MAXSEG           2
#define TCPOLEN_MAXSEG          4
#define TCPOPT_WINDOW           3
#define TCPOLEN_WINDOW          3
#define TCPOPT_SACKPERMITTED    4    /* RFC 2018 - SACK */
#define TCPOPLEN_SACKPERMITTED  2    /* RFC 2018 - SACK */
#define TCPOPT_SACK             5    /* RFC 2018 - SACK */
#define TCPOPT_TIMESTAMP        8
#define TCPOLEN_TIMESTAMP       10


/* TCP Definitions */

#define TCP_ISSINCR     128000          /* ISS Bump Increment */

/* TCP Protocol Definitions */
#define TCP_TFLAGS_DEFAULT      0
#define TCP_MAX_OPTIONS         40      /* Max number of option bytes in hdr */
                                        /* Increased to support RFC 2018 - SACK */
#define TCP_MSS_DEFAULT         536     /* Default mss (BSD uses 512) */
#define TCP_MSS_DEFAULT_NR      1500    /* Default mss sent if no route MTU */
#define TCP_MAXWIN              65535   /* max window size */
#define TCP_MAXBACKOFF          12      /* max index into tcp_backoff[] */

/* Timer Constants (in 1/10 second ticks) */
#define TCPTV_MSL               300     /* max seg lifetime (30 sec) */
#define TCPTV_MAX_IDLE          6000    /* max connection idle (10 min) */
#define TCPTV_RTXMIN            2       /* minimum value retransmit timer */
#define TCPTV_RTXMAX            600     /* max value retransmit timer (60 sec) */
#define TCPTV_PERSMIN           50      /* minumum value persist timer (5 sec) */
#define TCPTV_PERSMAX           600     /* max value persist timer (60 sec) */
#define TCPTV_KEEP_INIT         750     /* initial connect keep alive (75 sec) */
#define TCPTV_SRTTBASE          0       /* base roundtrip time start at 0 */
#define TCPTV_RTTDFLT           30      /* default RTT if no measurements (3 sec) */
#define TCPTV_MINIMALMAXRTT     1       /* maximum allowed RTT default (.1 sec) */

/* Timer Constants (in millisecond) */
#define TCPTV_MAXRTTDFLT        3600000 /* maximum allowed RTT default (1 hr) */

/* dflt time before first probe (2 hours) */
#define TCPTV_KEEP_IDLE         TCP_KEEP_IDLE

/* max keep connection idle (10 min) */
#define TCPTV_KEEP_MAXIDLE      TCP_KEEP_MAXIDLE

/* probe interval (75 seconds) */
#define TCPTV_KEEP_INTVL        TCP_KEEP_INTVL

/* shift for fix point (must be at least 3) */
#define TCP_FIXP_SHIFT          4

/* RangeSet Macro sets time value and verifies it is in range */
#define TCPT_RANGESET(tv, value, tvmin, tvmax) { \
    (tv) = (value); \
        if ((UINT32)(tv) < (UINT32)(tvmin)) \
        (tv) = (tvmin); \
        else if ((UINT32)(tv) > (UINT32)(tvmax)) \
        (tv) = (tvmax); \
}

/* RFC 2018 - Selective Acknowledgement(SACK) related definitions */

/*
 * The settings of TCP_SACK_REXMIT_TIMER_RATIO, TCP_SACK_REXMIT_SEGMENT,
 * and TCP_SACK_TICKS_REXMT definitions allows tuning of retransmission
 * characterstics of SACK.
 *
 */
#define TCP_SACK_REXMIT_TIMER_RATIO   4  /* SACK Retransmission Timer Ratio */
                                         /* t_trtx / TCP_SACK_REXMIT_TIMER_RATIO */
#define TCP_SACK_REXMIT_SEGMENT       1  /* SACK Retransmission Congestion  */
                                         /* Window Segment Count (in MSS unit) */
#define TCP_SACK_TICKS_REXMIT         2  /* If a SACK option is received,  */
                                         /* the current traditional retransmit */
                                         /* timeout tick value is incremented */
                                         /* by TCP_SACK_TICKS_REXMIT. */

#define SACK_TABLE_SIZE  64   /* entries, it must be power of 2 (2,4,8,...) */
#define SACK_OPTION_SIZE 8    /* octets */

typedef  struct SACK_TxEntry {
        UINT32 leftEdge;    /*  left edge of segment  */
        UINT32 rightEdge;   /*  right edge of segment */
        UINT32 sacked;      /*  SACK'd or not         */
} SACK_TxEntry;

typedef  struct SACK_RcvEntry {
        UINT32 leftEdge;    /*  left edge of continuous block  */
        UINT32 rightEdge;   /*  right edge of continuous block */
        UINT32 arrival;     /*  arrival order of block         */
} SACK_RcvEntry;

typedef struct SACK_Info {
    UINT32 rexmtTimeout;  /* SACK retransmit timer expired */
    UINT32 rexmtIndex;    /* Index of segment at SACK_txTable to rexmit  */
    SACK_TxEntry SACK_txTable[SACK_TABLE_SIZE]; /* SACK TX table  */
    UINT32 txTableTop;    /* index to top of SACK TX table */
    UINT32 txTableBottom; /* index to bottom of SACK TX table */
    SACK_RcvEntry SACK_rcvTable[SACK_TABLE_SIZE]; /* SACK RCV table */
    UINT32 rcvTableTop;   /* index to top of SACK RCV table  */
    UINT32 rcvTableBottom;/* index to bootom of SACK RCV table */
} SACK_Info;

/* TCP Net Packet Format Definitions */

/* TCP Flag Equates */
#define TCP_FIN         0x01
#define TCP_SYN         0x02
#define TCP_RST         0x04
#define TCP_PSH         0x08
#define TCP_ACK         0x10
#define TCP_URG         0x20

/* TCP Protocol Block */
typedef struct _tcpprot {
        struct  _tcpprot *pNext;
        struct  _tcpprot *pPrev;
        HANDLE  hSock;                  /* Handle to parent socket */
        HANDLE  hSBRx;                  /* Receive Socket Buffer */
        HANDLE  hSBTx;                  /* Transmit Socket Buffer */
        uint    reasm_pkt_cnt;          /* Number of pkts held for REASM */
        struct  _tcpreasm *pReasm;      /* Out of order frags */
        UINT32  TicksRexmt;             /* Retransmit Timer */
        UINT32  TicksPersist;           /* Persist Timer */
        UINT32  TicksKeep;              /* Keepalive Timer */
        UINT32  TicksWait2;             /* FIN_WAIT2 Timer */
        uint    t_mss;                  /* maximum segment size */
        int     t_state;                /* state of this connection */
        int     t_rtxindex;             /* Index into tcp_backoff[] */
        uint    t_flags;
#define TF_ACKNOW        0x0001          /* ack peer immediately */
#define TF_DELACK        0x0002          /* ack, but try to delay it */
#define TF_NODELAY       0x0004          /* don't delay packets to coalesce */
#define TF_NOOPT         0x0008          /* don't use tcp options */
#define TF_NOPUSH        0x0010          /* don't use buffer empty to goto send */
#define TF_SENTFIN       0x0020          /* have sent FIN */
#define TF_RCVD_MSS      0x0040          /* other side has send MSS */
#define TF_REQ_TSTMP     0x0080          /* have/will request timestamps */
#define TF_RCVD_TSTMP    0x0100          /* a timestamp was received in SYN */
#define TF_PERSIST       0x0200          /* called from PERSIST */
#define TF_DETACHED      0x0400          /* Detached by the Socket layer  */
#define TF_NEEDOUTPUT    0x0800          /* Last call to output was aborted */
#define TF_SACKPERMITTED 0x1000          /* RFC 2018 - SACK is permitted */

/* The following fields are used as in the protocol specification. */
/* See RFC783, Dec. 1981, page 21. */
/* send sequence variables */
        UINT32  iss;                    /* initial send sequence number */
        UINT32  snd_una;                /* send unacknowledged */
        UINT32  snd_nxt;                /* send next */
        UINT32  snd_max;                /* highest sequence number sent */
        UINT32  snd_up;                 /* send urgent pointer */
        UINT32  snd_wnd_max;            /* max send window we got */
        UINT32  snd_wnd;                /* send window */
        UINT32  snd_cwnd;               /* congestion-controlled window */
        UINT32  snd_wndack;             /* ACK value of last Window Update */

/* receive sequence variables */
        UINT32  rcv_nxt;                /* receive next */
        UINT32  rcv_up;                 /* receive urgent pointer */
        UINT32  rcv_adv;                /* advertised window */
/* Transmit timing stuff. */
        UINT32  t_tidle;                /* inactivity time (in ticks) */
        UINT32  t_trtt;                 /* rttseq's round trip time (in ticks) */
        UINT32  t_rttseq;               /* sequence number being timed in trtt */
        UINT32  t_trtx;                 /* current value of rtx timer (in ticks) */
        INT32   t_srtt;                 /* FIXP: smoothed round-trip time */
        INT32   t_rttvar;               /* FIXP: variance in round-trip time */
        UINT32  t_maxrtt;               /* max allowed rtt value (in ticks) */

/* out-of-band data */
        int     t_softerror;            /* possible error not yet reported */
                                        /* This is the "best guess" error */
                                        /* when a problem is detected */

/* RFC 2018 - SACK  */
        SACK_Info* pSack;               /* If SACK is enabled,  */
                                        /* pointer to SACK_Info */
        UINT32  TicksSackRexmt;         /* SACK retransmission timer (in ticks) */
        UINT32  sackActive;             /* SACK is active for current connection */
        UINT32  arrivalOrder;           /* RFC requires SACKing most recent one */
                                        /* first. So, NDK needs to keep track of */
                                                /* arrival order */
} TCPPROT;


typedef struct _tcpreasm {
    struct _tcpreasm *pNext;            /* Pointer to next reasm struct */
    PBM_Pkt     *pPkt;                  /* Pkt involved */
    UINT32      seq;                    /* Starting sequence */
    UINT32      end_seq;                /* Ending sequence */
    UINT32      eatseq;                 /* Eat sequence (OOB byte) */
    UINT32      eatflag;                /* Set when eat_seq is valid */
    UINT32      arrival;                /* Arrival order of segment */
                                        /* (required by RFC2018 SACK) */
    UINT8       *pData;                 /* Pointer to data */
} TCPREASM;


/* TCP State */
#define TSTATE_CLOSED       0
#define TSTATE_LISTEN       1
#define TSTATE_SYNSENT      2
#define TSTATE_SYNRCVD      3
#define TSTATE_ESTAB        4
#define TSTATE_CLOSEWAIT    5
#define TSTATE_FINWAIT1     6
#define TSTATE_CLOSING      7
#define TSTATE_LASTACK      8
#define TSTATE_FINWAIT2     9
#define TSTATE_TIMEWAIT     10

/* Local Functions */
extern void   TcpDrop( TCPPROT *pt, int Error );
extern void   TcpClose( TCPPROT *pt );
extern int    TcpOutput( TCPPROT *pt );
extern void   TcpTimeoutAdd( TCPPROT *pt );
extern void   TcpTimeoutRemove( TCPPROT *pt );
extern void   TcpTimeoutRexmt( TCPPROT *pt );
extern void   TcpTimeoutSackRexmt( TCPPROT *pt );
extern void   TcpTimeoutKeep( TCPPROT *pt );
extern void   TcpTimeoutPersist( TCPPROT *pt );
extern void   TcpTimeoutWait2( TCPPROT *pt );
extern void   TcpSetPersist( TCPPROT *pt );
extern uint   TcpValidateMetrics( TCPPROT *pt, uint rcvmss );
extern void   TcpXmitTimer( TCPPROT *pt, UINT32 rtt );
extern void   TcpGenPacket( TCPPROT *pt, IPN IPDst, uint PortDst,
                            IPN IPSrc, uint PortSrc,
                            UINT32 seq, UINT32 ack, int flags );

/* TCP Global Variables */

extern UINT32  tcp_iss;                 /* Send Sequence */
extern UINT32  tcp_now;                 /* TCP Tick Time */

#endif

