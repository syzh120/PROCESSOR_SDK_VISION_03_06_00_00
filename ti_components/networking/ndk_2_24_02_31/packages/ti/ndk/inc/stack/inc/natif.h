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
 * ======== natif.h ========
 *
 */

#ifndef _C_NATIF_INC
#define _C_NATIF_INC  /* #defined if this .h file has been included */

/*----------------------------------------------------------------------- */
/* Global Task Information */
#define NAT_MAXENTRIES                  2048

/* Defined Messages */
#define MSG_NAT_TIMER                   (ID_NAT*MSG_BLOCK + 0)

/* NAT Statistics */
typedef struct {
    UINT32      TxExamined;     /* Number of packets examined */
    UINT32      TxQualified;    /* Number of possible packets */
    UINT32      TxAltered;      /* Number of packets altered */
    UINT32      RxExamined;     /* Number of packets examined */
    UINT32      RxQualified;    /* Number of possible packets */
    UINT32      RxAltered;      /* Number of packets altered */
    UINT32      Entries;        /* Number of translation entries */
    UINT32      MaxEntries;     /* Max number of translation entries */
    UINT32      LongTerm;       /* Entries with extended timeouts */
    UINT32      MaxLongTerm;    /* Max entries with extended timeouts */
    } NATSTATS;

/* NAT Statistics */
extern NATSTATS nats;

/* NAT "Shared" IP Server */
extern IPN      NatIpServer;

/* Time a NAT entry can be idle */
#define NAT_IDLE_SECONDS                60              /* Non-Tcp tranlation */
#define NAT_TCP_IDLE_SECONDS            60              /* Unconnected socket */
#define NAT_TCP_SYN_SECONDS             60              /* Connecting socket */
#define NAT_TCP_ACTIVE_SECONDS          (3600*24*5)     /* Connected socket */
#define NAT_TCP_CLOSED_SECONDS          5               /* Closed socket */

/* NAT Access Functions called by IP */
int  NatIpTxInput( PBM_Pkt *pPkt );
int  NatIpRxInput( PBM_Pkt *pPkt );

/* NAT Access Functions called by USER */
void NatSetConfig( IPN IPAddr, IPN IPMask, IPN IPServer, uint MTU );

/*------------------------------------------------------------------------- */
/* NAT Info Entry Structure */
typedef struct _natinfo {
    uint                TcpState;       /* Current TCP State (Simplified) */
#define NI_TCP_IDLE         0               /* Closed or closing */
#define NI_TCP_SYNSENT_TX   1               /* Connecing */
#define NI_TCP_SYNSENT_RX   2               /* Connecing */
#define NI_TCP_SYNSENT_ALL  3               /* Both SYN sent - waiting ACK */
#define NI_TCP_ESTAB        4               /* Established */
#define NI_TCP_CLOSING_TX   5               /* Closing */
#define NI_TCP_CLOSING_RX   6               /* Closing */
#define NI_TCP_CLOSED       7               /* Closed */
    IPN                 IPLocal;        /* Translated IP Address */
    UINT16              PortLocal;      /* Translated TCP/UDP Port */
    IPN                 IPForeign;      /* IP Adress of Foreign Peer */
    UINT16              PortForeign;    /* Port of Foreign Peer */
    UINT8               Protocol;       /* IP Potocol */
    UINT16              PortMapped;     /* Locally Mapped TCP/UDP Port (router) */
    HANDLE              hProxyEntry;    /* Handle to Proxy Entry (if any) */
    UINT32              Timeout;        /* Expiration time in SECONDS */
    void                *pUserData;     /* Pointer to proxy callback data */
    } NATINFO;

/*-------------------------------------------------------------------- */
/* Nat Entry Routines */
/*-------------------------------------------------------------------- */
_extern HANDLE   NatNew( IPN IPLocal, UINT16 PortLocal,
                        IPN IPForeign, UINT16 PortForeign,
                        UINT8 Protocol, UINT16 PortMapped,
                        UINT32 Timeout );
_extern void     NatFree( HANDLE hNat );
_extern NATINFO *NatGetPNI( HANDLE hNat );

/*-------------------------------------------------------------------- */
/* Proxy Routines */
/*-------------------------------------------------------------------- */

/* Mode used by Nat and Proxy */
#define NAT_MODE_TX           0
#define NAT_MODE_RX           1

/* Proxy Access Functions called by USER */
_extern HANDLE ProxyNew( uint NatMode, UINT8 Protocol, UINT16 Port, IPN IPTarget,
                         int (*pfnEnableCb)( NATINFO *, uint ),
                         int (*pfnTxCb)( NATINFO *, IPHDR * ),
                         int (*pfnRxCb)( NATINFO *, IPHDR * ) );
_extern void   ProxyFree( HANDLE hProxy );
_extern IPHDR  *ProxyPacketMod( uint Offset, uint OldSize, uint NewSize,
                                UINT8 *pData );

/* Proxy Access Functions called by NAT */
_extern int    ProxyEntrySpawn( uint NatMode, UINT8 Protocol, UINT16 Port,
                               HANDLE *phProxyEntry, IPN *pIPLocal );
#define       ProxyEntryFree(x) mmFree(x)
_extern int    ProxyEnable( NATINFO *pni, uint Enable );
_extern void   ProxyTx( NATINFO *pni, PBM_Pkt *pPkt, IPHDR *pIpHdr );
_extern void   ProxyRx( NATINFO *pni, PBM_Pkt *pPkt, IPHDR *pIpHdr );

#endif
