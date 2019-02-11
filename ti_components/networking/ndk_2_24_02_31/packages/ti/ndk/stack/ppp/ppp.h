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
 * ======== ppp.h ========
 *
 * Basic includes for PPP
 *
 */


/* Special Read MACRO (is processor independent) */
#define RdNet16s(x)  ((UINT16)((*(UINT8 *)(x)))<<8 | (UINT16)(*(((UINT8 *)(x))+1)))

/*----------------------------------------------- */
/* Network Headers */
/*----------------------------------------------- */

/*-------------------- */
/* LCP Protocol Header */
typedef struct {
                UINT8   Code;
                UINT8   Id;
                UINT16  Length;
                UINT8   TagData[1];
               } LCPHDR;
#define SIZE_LCPHDR     4

/*----------------------------------------------- */
/* PPP Protocols */
#define PPPPROT_IP      0x0021
#define PPPPROT_IPCP    0x8021
#define PPPPROT_LCP     0xc021
#define PPPPROT_PAP     0xc023
#define PPPPROT_CHAP    0xc223

/*----------------------------------------------- */
/* State Codes for LCP and IPCP */
#define PROT_STATE_CLOSED       0       /* Layer Closed */
#define PROT_STATE_OPEN         1       /* Layer Open */
#define PROT_STATE_CONNECTED    2       /* Negotiation completed */
#define PROT_STATE_STOPPED      3       /* Layer Stopped */

/*----------------------------------------------- */
/* State Code for each half of a LCP/IPCP negotiation */
#define PROT_CFG_IDLE           0       /* No connection */
#define PROT_CFG_PENDING        1       /* CFG pending */
#define PROT_CFG_AUTH           2       /* CFG authentication */
#define PROT_CFG_OK             3       /* CFG established */

/*----------------------------------------------- */
/* LCP Instance Structure */
typedef struct {
    uint        State;       /* State of LCP session */
    uint        StateCFG;    /* LCP CFG State machine */
    uint        StateACK;    /* LCP ACK State machine */
    UINT8       LastId;      /* Id of last CFG sent */
    int         Timer;       /* Restart timer */
    int         Count;       /* Restart event count */
    UINT32      PeerMagic;   /* Peer's Magic Number */
    UINT32      OurMagic;    /* Our Magic Number */
    UINT32      OptMask;     /* Available Options */
    UINT32      UseMask;     /* Options in use */
    } LCP_SESSION;

/*----------------------------------------------- */
/* AUTH Instance Structure */
typedef struct {
    uint        State;       /* State of LCP session */
    UINT8       LastId;      /* Id of last CFG sent */
    int         Timer;       /* Restart timer */
    int         Count;       /* Restart event count */
    UINT16      Protocol;    /* Authentication protocol */
    UINT8       SeedLen;     /* MD5 Data seed length */
    UINT8       SeedData[32];/* MD5 Data seed data */
    char        AuthName[32];/* Authenticator Name */
    } AUTH_SESSION;

/*----------------------------------------------- */
/* IPCP Instance Structure */
typedef struct {
    uint        State;       /* State of IPCP session */
    uint        StateCFG;    /* IPCP CFG State machine */
    uint        StateACK;    /* IPCP ACK State machine */
    UINT8       LastId;      /* Id of last CFG sent */
    int         Timer;       /* Restart timer */
    int         Count;       /* Restart event count */
    UINT32      OptMask;     /* Available Options */
    UINT32      UseMask;     /* Options in use */
    } IPCP_SESSION;

/*----------------------------------------------- */
/* PPP Instance Structure */
typedef struct {
/*---[ These fields match IF structure ]--- */
    uint         Type;             /* Set to HTYPE_PPP */
    uint         llIndex;          /* Low-level Device Index */
    uint         ProtMTU;          /* MTU of payload */
/*----------------------------------------- */
    uint         InUse;            /* Non-standard Reference count */
#define INUSE_IDLE      1
#define INUSE_LOCKED    65535
    HANDLE       hSI;              /* Handle to serial interface driver */
    HANDLE       hRoute;           /* Route when connected */
    HANDLE       hNet;             /* Handle to network address in CFG */
    HANDLE       hClient;          /* Handle to client record in CFG */
    uint         Flags;            /* Mode flags */
    UINT32       CMap;             /* Our desired CMap */
    LCP_SESSION  lcp;              /* LCP Session */
    AUTH_SESSION auth;             /* AUTH Session */
    IPCP_SESSION ipcp;             /* LCP Session */
    uint         MTU_Phys;         /* Physical MTU */
    uint         MTU_Rx;           /* MTU of peer */
    uint         MTU_Tx;           /* Our negotiated MTU */
    IPN          IPServer;         /* Server IP (us in server mode) */
    IPN          IPMask;           /* Server IP Mask (when in server mode) */
    IPN          IPClient;         /* Client IP (us in client mode) */
    IPN          IPDNS1;           /* DNS Server 1 */
    IPN          IPDNS2;           /* DNS Server 2 */
    IPN          IPNBNS1;          /* NBNS Server 1 */
    IPN          IPNBNS2;          /* NBNS Server 2 */
    char         UserId[PPPNAMELEN];    /* Username */
    char         Password[PPPNAMELEN];  /* Password */
    void (*SICtrl)( HANDLE, uint, UINT32, PBM_Pkt * );
    NETIF_DEVICE*   ptr_ppp_device; /* The PPP NIMU Network Interface Object  */
    } PPP_SESSION;

/*----------------------------------------------- */
/* PPP Events */
#define PPP_EVENT_LCP_CONNECT           1
#define PPP_EVENT_LCP_STOPPED           2
#define PPP_EVENT_AUTH_CONNECT          3
#define PPP_EVENT_AUTH_STOPPED          4
#define PPP_EVENT_IPCP_CONNECT          5
#define PPP_EVENT_IPCP_STOPPED          6

/*----------------------------------------------- */
/* Private PPP Functions */
void   pppEvent( HANDLE hPPP, uint Event );

/*----------------------------------------------- */
/* Private LCP Functions */
void lcpInit( PPP_SESSION *p );                 /* Init LCP instance */
void lcpOpen( PPP_SESSION *p, uint fStart );    /* Open and/or Start LCP */
void lcpClose( PPP_SESSION *p );                /* Stop the CFG process */
void lcpInput( PPP_SESSION *p, PBM_Pkt *pPkt ); /* Rx a Packet */
void lcpReject( PPP_SESSION *p, PBM_Pkt *pPkt );/* Reject bad protocol Packet */
void lcpTimer( PPP_SESSION *p );                /* Timer Tick */

/*----------------------------------------------- */
/* Private AUTH Functions */
void authInit( PPP_SESSION *p );                /* Init AUTH instance */
void authStart( PPP_SESSION *p );               /* Start AUTH */
void authTimer( PPP_SESSION *p );               /* Timer Tick */
void papInput( PPP_SESSION *p, PBM_Pkt *pPkt ); /* Rx a Packet */
void chapInput( PPP_SESSION *p, PBM_Pkt *pPkt );/* Rx a Packet */

/*----------------------------------------------- */
/* Private IPCP Functions */
void ipcpInit( PPP_SESSION *p );                /* Init IPCP instance */
void ipcpStart( PPP_SESSION *p );               /* Start IPCP */
void ipcpInput( PPP_SESSION *p, PBM_Pkt *pPkt );/* Rx a Packet */
void ipcpTimer( PPP_SESSION *p );               /* Timer Tick */

