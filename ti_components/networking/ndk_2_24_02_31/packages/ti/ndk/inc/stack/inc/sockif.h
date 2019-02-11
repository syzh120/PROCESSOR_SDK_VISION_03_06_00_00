/*
 * Copyright (c) 2012-2013, Texas Instruments Incorporated
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
 * ======== sockif.h ========
 *
 * Sock object public definitions
 *
 */

#include "fdtif.h"
#include "listlib.h"

#ifndef _SOCKIF_INC_
#define _SOCKIF_INC_

/* Socket Ephemeral Port Range (Public and Reserved) */
#define SOCK_USERPORT_FIRST 0xE000      /* Local User Ports */
#define SOCK_USERPORT_LAST  0xEFFF
#define SOCK_RESPORT_FIRST  0xF000      /* Reserved NAT Ports */
#define SOCK_RESPORT_LAST   0xFFFE

/* Protocol Control Commands */
#define PRC_IFDOWN              0       /* interface transition */
#define PRC_ROUTEDEAD           1       /* select new route if possible ??? */
#define PRC_QUENCH2             3       /* DEC congestion bit says slow down */
#define PRC_QUENCH              4       /* some one said to slow down */
#define PRC_MSGSIZE             5       /* message size forced drop */
#define PRC_HOSTDEAD            6       /* host appears to be down */
#define PRC_HOSTUNREACH         7       /* deprecated (use PRC_UNREACH_HOST) */
#define PRC_UNREACH_NET         8       /* no route to network */
#define PRC_UNREACH_HOST        9       /* no route to host */
#define PRC_UNREACH_PROTOCOL    10      /* dst says bad protocol */
#define PRC_UNREACH_PORT        11      /* bad port # */
#define PRC_UNREACH_NEEDFRAG    12      /* (use PRC_MSGSIZE) */
#define PRC_UNREACH_SRCFAIL     13      /* source route failed */
#define PRC_REDIRECT_NET        14      /* net routing redirect */
#define PRC_REDIRECT_HOST       15      /* host routing redirect */
#define PRC_REDIRECT_TOSNET     16      /* redirect for type of service & net */
#define PRC_REDIRECT_TOSHOST    17      /* redirect for tos & host */
#define PRC_TIMXCEED_INTRANS    18      /* packet lifetime expired in transit */
#define PRC_TIMXCEED_REASS      19      /* lifetime expired on reass q */
#define PRC_PARAMPROB           20      /* header incorrect */
#define PRC_NCMDS               21

/* IP Socket Options (IpFlags) */
#define SOCK_IP_HDRINCL         0x0001  /* Include IP Header (raw only) */
#define SOCK_IP_OPTIONS         0x0002  /* Use supplied IP Options */

/* Multicast Socket Record Information:
 *  Multicast requests are now stored on per socket basis; instead of a per
 *  interface basis. This structure is a linked list of multicast records which
 *  are stored on each socket. Sockets could have joined multiple multicast
 *  groups. */
typedef struct _mcast_sock
{
    LIST_NODE           links;          /* List of multicast socket records */
    struct ip_mreq      mreq;           /* Multicast Request                */
    HANDLE              hIf;            /* Handle to the interface          */
}MCAST_SOCK_REC;

typedef struct mcast_sock_rec6
{
    LIST_NODE           links;
    struct ipv6_mreq    mreq;
    HANDLE              hIf;
} MCAST_SOCK_REC6;

/* Socket Priority
 *  Each socket can be associated with a specific priority. This priority
 *  can be configured through the setsockopt API. All packets transmitted
 *  through this socket will have the same priority. This is used by the
 *  VLAN drivers in the system to remark the packets with an appropriate
 *  Layer2 User Priority value.
 *  By default; there is no priority associated with the socket. */
#define PRIORITY_UNDEFINED 0xFFFF

#define SOCKPROT_NONE   0
#define SOCKPROT_TCP    1
#define SOCKPROT_UDP    2
#define SOCKPROT_RAW    3

/* Sock Object Structure */
typedef struct _sock {
             FILEDESC   fd;             /* File descriptor header */

             uint       Family;         /* Address Family as AF_ in socket.h */
             uint       SockType;       /* Type as SOCK_ in socket.h */
             uint       Protocol;       /* IP Protocol: TCP, UDP, ICMP, etc. */

             uint       IpFlags;        /* IP Protocol Options (raw only) */
             uint       IpTtl;          /* IP TTL */
             uint       IpTos;          /* IP TOS */
             uint       IpOptSize;      /* IP Header Options Size */
             UINT8      IpOptions[40];  /* IP Header Options */

             UINT16     SockPriority;   /* Socket Priority. */
             uint       SockProt;       /* Socket Protocol Handler */

             uint       OptionFlags;    /* SO_ options as defined in socket.h */
             uint       StateFlags;     /* SS_ flags as defined below */
             UINT32     dwLingerTime;   /* Time used when SO_LINGER set */

             /* Protocol Control */
             struct _sock *pProtNext;   /* Pointer to next in protocol list */
             struct _sock *pProtPrev;   /* Pointer to prev in protocol list */
             IPN        FIP;            /* Foreign IP address */
             uint       FPort;          /* Foreign Port */
             IPN        LIP;            /* Local IP address (NULL for wildcard) */
             uint       LPort;          /* Local Port (NULL if not bound) */
             IPN        BIP;            /* Bound IP address (SS_ADDR only) */
             uint       BPort;          /* Bound Port (SS_ADDR only) */
             HANDLE     hTP;            /* Handle to protocol specific data */
             HANDLE     hRoute;         /* Handle to cached route */
             HANDLE     hIFTx;          /* Handle to Default IF for transmit */

             /* Connection State Stuff */
             struct _sock *pParent;     /* Pointer back to accept socket */
             struct _sock *pPrevQ;      /* Prev socket in pend/ready queue */
             struct _sock *pPending;    /* Pending connection sockets */
             struct _sock *pReady;      /* Ready connected sockets */
             uint       ConnMax;        /* Max pending/ready connections */
             uint       ConnTotal;      /* Total connections */

             /* Read/Write Stuff */
             int        ErrorPending;   /* Error returned on next socket call */
             INT32      OOBMark;        /* Out of band info mark */
             uint       OOBData;        /* Out of band info data */
             UINT32     RxTimeout;      /* Timeout for Rx IO on stream */
             UINT32     TxTimeout;      /* Timeout for Tx IO on stream */
             UINT32     RxBufSize;      /* Rx Buffer Size */
             UINT32     TxBufSize;      /* Tx Buffer Size */
             HANDLE     hSBRx;          /* Rx Buffer */
             HANDLE     hSBTx;          /* Tx Buffer */

             MCAST_SOCK_REC* pMcastList; /* List of multicast addresses on the socket. */

             TimestampFxn pTimestampFxn; /* Callout function pointer to */
                                         /* timestamp TX  */
        } SOCK;

/* Socket Protocol Block */
typedef struct _sockpcb {
             IPN        IPAddrLocal;    /* Local IP Address */
             uint       PortLocal;      /* Local IP Port */
             IPN        IPAddrForeign;  /* Foreign IP Address */
             uint       PortForeign;    /* Foreign IP Port */
             uint       State;          /* Socket State (protocol dependent) */
        } SOCKPCB;

/* Socket Access Functions */

/*------------------------------------------------------------------------ */
/* General Access Functions (called from upper layers) */
_extern int    SockNew( int Family, int Type, int Protocol,
                        int RxBufSize, int TxBufSize, HANDLE *phSock );
_extern int    SockClose( HANDLE hSock );

_extern int    SockCheck( HANDLE hSock, int IoType );
#define  SOCK_READ       0
#define  SOCK_WRITE      1
#define  SOCK_EXCEPT     2

_extern int    SockStatus( HANDLE hSock, int request, int *results );

_extern int    SockSet(HANDLE hSock, int Type, int Prop, void *pbuf, int size);
_extern int    SockGet(HANDLE hSock, int Type, int Prop, void *pbuf, int *psize);

_extern int    SockShutdown( HANDLE hSock, int how );

_extern int    SockConnect( HANDLE hSock, PSA pName );
_extern int    SockDisconnect( HANDLE hSock );
_extern int    SockBind( HANDLE hSock, PSA pName );

_extern int    SockGetName( HANDLE hSock, PSA pSockName, PSA pPeerName );

_extern int    SockListen( HANDLE hSock, int maxcon );
_extern int    SockAccept( HANDLE hSock, HANDLE *phSock );

_extern int    SockRecv( HANDLE hSock, INT8 *pBuf, INT32 size,
                        int flags, PSA pPeer, INT32 *pRetSize );
_extern int    SockSend( HANDLE hSock, INT8 *pBuf, INT32 size,
                        int flags, INT32 *pRetSize );
_extern int    SockRecvNC( HANDLE hSock, int flags, PSA pPeer, PBM_Pkt **ppPkt );

_extern int    SockGetPcb( uint SockProt, uint BufSize, UINT8 *pBuf );
_extern void SockCleanPcb (uint SockProt, IPN IPAddress);

/*------------------------------------------------------------------------ */
/* PCB Related Socket Access Functions (called from stack protocols) */
_extern int      SockPcbAttach( HANDLE hSock );
_extern int      SockPcbDetach( HANDLE hSock );
_extern void     SockPcbCleanup();
_extern int      SockPcbBind( HANDLE hSock, IPN IP, uint Port );
_extern int      SockPcbConnect( HANDLE hSock, IPN IP, uint Port );
_extern HANDLE   SockPcbResolve( uint SockProt, IPN LIP, uint LPort,
				 IPN FIP, uint FPort, uint Match,
				 uint * MaxFlag );
#define SOCK_RESOLVE_BEST       1       /* Return Best Match */
#define SOCK_RESOLVE_EXACT      2       /* Return Exact Match */
#define SOCK_RESOLVE_SPAWN      3       /* Return exact, or spawn on best match */
_extern HANDLE   SockPcbResolveChain( HANDLE hSock, uint wSockProt, uint Prot,
                                IPN LIP, uint LPort, IPN FIP, uint FPort );
_extern void   SockPcbCtlError( uint Code, IPHDR *pIpHdr );
_extern void   SockPcbRtChange( HANDLE hRt );

/*------------------------------------------------------------------------ */
/* Low-level Access Functions (called from stack protocols) */
_extern int    SockNotify( HANDLE hSock, int Notification );
#define SOCK_NOTIFY_CONNECT     1
#define SOCK_NOTIFY_RCVACK      2
#define SOCK_NOTIFY_RCVDATA     3
#define SOCK_NOTIFY_RCVFIN      4
#define SOCK_NOTIFY_DISCONNECT  5
#define SOCK_NOTIFY_CLOSED      6
#define SOCK_NOTIFY_ERROR       7

_extern void   SockSetOOBMark( HANDLE hSock, INT32 OOBMark );
_extern void   SockSetOOBData( HANDLE hSock, UINT8 OOBData );
_extern void   SockSpawnAbort( HANDLE hSock );
_extern HANDLE SockValidateRoute( HANDLE hSock );
_extern PBM_Pkt *SockCreatePacket( HANDLE hSock, uint Size );

/* Low Level Object Interface */

#ifdef _STRONG_CHECKING
_extern uint   SockGetProtocol( HANDLE h );
_extern uint   SockGetIpHdrSize( HANDLE h );
_extern HANDLE SockGetTx( HANDLE h );
_extern HANDLE SockGetRx( HANDLE h );
_extern HANDLE SockGetTP( HANDLE h );
_extern IPN    SockGetLIP( HANDLE h );
_extern IPN    SockGetFIP( HANDLE h );
_extern uint   SockGetLPort( HANDLE h );
_extern uint   SockGetFPort( HANDLE h );
_extern HANDLE SockGetRoute( HANDLE h );
_extern HANDLE SockGetIFTx( HANDLE h );
_extern uint   SockGetOptionFlags( HANDLE h );
_extern void   SockSetError( HANDLE h, int Error );
#else
#define SockGetProtocol( h )     (((SOCK *)h)->Protocol)
#define SockGetIpHdrSize( h )    ((((SOCK *)h)->IpFlags & IP_HDRINCL) ? 0 : (IPHDR_SIZE + (((SOCK *)h)->IpOptSize)))
#define SockGetTx( h )           (((SOCK *)h)->hSBTx)
#define SockGetRx( h )           (((SOCK *)h)->hSBRx)
#define SockGetTP( h )           (((SOCK *)h)->hTP)
#define SockGetLIP( h )          (((SOCK *)h)->LIP)
#define SockGetFIP( h )          (((SOCK *)h)->FIP)
#define SockGetLPort( h )        (((SOCK *)h)->LPort)
#define SockGetFPort( h )        (((SOCK *)h)->FPort)
#define SockGetRoute( h )        (((SOCK *)h)->hRoute)
#define SockGetIFTx( h )         (((SOCK *)h)->hIFTx)
#define SockGetOptionFlags( h )  (((SOCK *)h)->OptionFlags)
#define SockSetError( h, e )     (((SOCK *)h)->ErrorPending=(e))
#endif

#ifdef _INCLUDE_IPv6_CODE

/**
 * @brief
 *  The structure describes the IPv6 Socket data structure.
 *
 * @details
 *  This data structure identifies a socket used for communication
 *  over IPv6.
 */
typedef struct SOCK6 {
    /**
     * @brief   File descriptor header
     */
    FILEDESC    fd;

    /**
     * @brief   Address family of the socket (AF_INET6)
     */
    UINT8       Family;

    /**
     * @brief   Socket Type (SOCK_STREAM/SOCK_DGRAM/SOCK_RAW)
     */
    UINT8       SockType;

    /**
     * @brief   IP Protocol (TCP/UDP/ICMPV6 etc)
     */
    UINT8       Protocol;

    /* IPv6 Specific Options */
    /**
     * @brief   Flow label associated with the socket.
     */
    UINT32      FlowLabel;

    /**
     * @brief   Hop Limit for Unicast packets.
     */
    UINT8        HopLimit;

    /**
     * @brief   Scope ID associated with the socket.
     */
    UINT32      ScopeId;
    /* End of IPv6 Specific Options */

    /**
     * @brief   Socket Priority.
     */
    UINT16      SockPriority;

    /**
     * @brief   Socket Protocol Handler (SOCKPROT_NONE/SOCKPROT_TCP/
     *                                   SOCKPROT_UDP/SOCKPROT_RAW)
     */
    UINT32      SockProt;

    /**
     * @brief   Socket Option flags (SO_...) as defined in socket.h
     */
    uint       OptionFlags;

    /**
     * @brief   Socket State flags (SS_...). Defined and used by
     *          NDK core stack internally.
     */
    uint       StateFlags;

    /**
     * @brief   Time used when SO_LINGER set
     */
    UINT32      dwLingerTime;

    /* Protocol Control */
    /**
     * @brief   Pointer to next socket in protocol list
     */
    struct SOCK6   *pProtNext;

    /**
     * @brief   Pointer to previous socket in protocol list
     */
     struct SOCK6  *pProtPrev;

    /**
     * @brief   Foreign Host's IPv6 Address
     */
    IP6N        FIP;

    /**
     * @brief   Foreign Host's Port
     */
    UINT16      FPort;

    /**
     * @brief   Local IPv6 Address (NULL for wildcard)
     */
    IP6N        LIP;

    /**
     * @brief   Local Port to which socket is bound (NULL if not bound)
     */
    UINT16      LPort;

    /**
     * @brief   IPv6 Address to which this socket is bound (valid for DGRAM sockets)
     */
     IP6N       BIP;

    /**
     * @brief   Port to which this socket is bound (valid for DGRAM sockets)
     */
     UINT16     BPort;

    /**
     * @brief   Handle to Protocol specific data
     */
    HANDLE      hTP;

    /**
     * @brief   Handle to the cached V6 Route.
     */
    HANDLE     hRoute6;

    /**
     * @brief   Handle to default Interface for transmit
     */
    HANDLE      hIFTx;

    /* End of Protocol Control */

    /* Connection State Stuff */
    /**
     * @brief   Handle to the parent socket.
     */
    struct SOCK6   *pParent;

    /**
     * @brief   Previous Socket in Pending/ready queue.
     */
    struct SOCK6   *pPrevQ;

    /**
     * @brief   Pending connection sockets list.
     */
    struct SOCK6   *pPending;

    /**
     * @brief   Ready/connected sockets list.
     */
    struct SOCK6   *pReady;

    /**
     * @brief   Maximum allowed pending/ready connections on this
     *          socket.
     */
     UINT32     ConnMax;

    /**
     * @brief   Total number of current connections on socket.
     */
     UINT32     ConnTotal;

    /* End of Connection State Stuff */

    /* Read/Write Stuff */

    /**
     * @brief   Error returned on socket call
     */
    int         ErrorPending;

    /**
     * @brief   Out of band info mark
     */
    INT32      OOBMark;

    /**
     * @brief   Out of band info data
     */
    uint       OOBData;

    /**
     * @brief   Receive Timeout for stream sockets.
     */
    UINT32      RxTimeout;

    /**
     * @brief   Transmit Timeout for stream sockets.
     */
    UINT32      TxTimeout;

    /**
     * @brief   Receive buffer size
     */
    UINT32      RxBufSize;

    /**
     * @brief   Transmit buffer size
     */
    UINT32      TxBufSize;

    /**
     * @brief   Handle to Receive buffer of the socket.
     */
    HANDLE      hSBRx;

    /**
     * @brief   Handle to Transmit buffer of the socket.
     */
    HANDLE      hSBTx;

    /**
     * @brief   List of multicast addresses on the socket.
     */
    MCAST_SOCK_REC6 * pMcastList;

    /* End of Read/Write Stuff */
} SOCK6;

/**
 * @brief
 *  The structure describes the IPv6 Socket Protocol specific
 *  properties.
 *
 */
typedef struct SOCK6PCB {
    /**
     * @brief   Local IPv6 Address
     */
    IP6N        IPAddrLocal;

    /**
     * @brief   Local IP Port
     */
    UINT16      PortLocal;

    /**
     * @brief   Foreign host's IPv6 Address
     */
    IP6N        IPAddrForeign;

    /**
     * @brief   Foreign IP Port
     */
    UINT16      PortForeign;

    /**
     * @brief   Socket state (protocol dependent)
     */
    UINT32      State;
} SOCK6PCB;

/* Socket Access Functions */

/*------------------------------------------------------------------------ */
/* General Access Functions (called from upper layers) */
_extern int    Sock6New( int Family, int Type, int Protocol,
                        int RxBufSize, int TxBufSize, HANDLE *phSock );
_extern int    Sock6Close( HANDLE hSock );

_extern int    Sock6Check( HANDLE hSock, int IoType );

_extern int    Sock6Status( HANDLE hSock, int request, int *results );

_extern int    Sock6Set(HANDLE hSock, int Type, int Prop, void *pbuf, int size);
_extern int    Sock6Get(HANDLE hSock, int Type, int Prop, void *pbuf, int *psize);

_extern int    Sock6Shutdown( HANDLE hSock, int how );

_extern int    Sock6Connect( HANDLE hSock, PSA pName );
_extern int    Sock6Disconnect( HANDLE hSock );
_extern int    Sock6Bind( HANDLE hSock, PSA pName );

_extern int    Sock6GetName( HANDLE hSock, PSA pSockName, PSA pPeerName );

_extern int    Sock6Listen( HANDLE hSock, int maxcon );
_extern int    Sock6Accept( HANDLE hSock, HANDLE *phSock );

_extern int    Sock6Recv( HANDLE hSock, INT8 *pBuf, INT32 size,
                        int flags, PSA pPeer, INT32 *pRetSize );
_extern int    Sock6Send( HANDLE hSock, INT8 *pBuf, INT32 size,
                        int flags, INT32 *pRetSize );
_extern int    Sock6RecvNC( HANDLE hSock, int flags, PSA pPeer, PBM_Pkt **ppPkt );

_extern int    Sock6GetPcb( uint SockProt, uint BufSize, UINT8 *pBuf );
_extern void   Sock6CleanPcb (uint SockProt, IP6N IPAddress);

/*------------------------------------------------------------------------ */
/* PCB Related Socket Access Functions (called from stack protocols) */
_extern int    Sock6PcbAttach( HANDLE hSock );
_extern int    Sock6PcbDetach( HANDLE hSock );
_extern void   Sock6PcbCleanup();
_extern int    Sock6PcbBind( HANDLE hSock, IP6N IP, uint Port );
_extern int    Sock6PcbConnect( HANDLE hSock, IP6N IP, uint Port );
_extern HANDLE Sock6PcbResolve( uint SockProt, IP6N LIP, uint LPort,
				IP6N FIP, uint FPort, uint Match,
				 uint * MaxFlag );
_extern HANDLE Sock6PcbResolveChain( HANDLE hSock, uint wSockProt, uint Prot,
                              IP6N LIP, uint LPort, IP6N FIP, uint FPort );
_extern void   Sock6PcbRtChange( HANDLE hRt );

/*------------------------------------------------------------------------ */
/* Low-level Access Functions (called from stack protocols) */
_extern int    Sock6Notify( HANDLE hSock, int Notification );
_extern void   Sock6SetOOBMark( HANDLE hSock, INT32 OOBMark );
_extern void   Sock6SetOOBData( HANDLE hSock, UINT8 OOBData );
_extern void   Sock6SpawnAbort( HANDLE hSock );
_extern PBM_Pkt *Sock6CreatePacket( HANDLE hSock, uint Size, uint NextHeader );
_extern HANDLE Sock6ValidateRoute(HANDLE h);

/*------------------------------------------------------------------------ */
/* Protocol Specific Socket Functions */
_extern void Sock6PrCtlError(SOCK6 *ps, uint Code);

/* Low Level Object Interface */
#define Sock6GetProtocol( h )     (((SOCK6 *)h)->Protocol)
#define Sock6GetIpHdrSize( h )    (IPv6HDR_SIZE)
#define Sock6GetTx( h )           (((SOCK6 *)h)->hSBTx)
#define Sock6GetRx( h )           (((SOCK6 *)h)->hSBRx)
#define Sock6GetTP( h )           (((SOCK6 *)h)->hTP)
#define Sock6GetLIP( h )          (((SOCK6 *)h)->LIP)
#define Sock6GetFIP( h )          (((SOCK6 *)h)->FIP)
#define Sock6GetLPort( h )        (((SOCK6 *)h)->LPort)
#define Sock6GetFPort( h )        (((SOCK6 *)h)->FPort)
#define Sock6GetRoute( h )        (((SOCK6 *)h)->hRoute6)
#define Sock6GetIFTx( h )         (((SOCK6 *)h)->hIFTx)
#define Sock6GetOptionFlags( h )  (((SOCK6 *)h)->OptionFlags)
#define Sock6SetError( h, e )     (((SOCK6 *)h)->ErrorPending=(e))

#endif /* _INCLUDE_IPv6_CODE */

#define SOCKPROT_RAWETH    4

/**
 * @brief
 *  The structure describes the Raw Ethernet Sock Object Structure.
 *
 * @details
 *  This data structure identifies a socket used for communication
 *  over Raw Ethernet Sockets.
 */
typedef struct _SOCKRAWETH
{
    /**
     * @brief       File descriptor header
     */
    FILEDESC        fd;

    /**
     * @brief       Address family of the socket (AF_RAWETH)
     */
    UINT32          Family;

    /**
     * @brief       Socket Type (SOCK_RAWETH)
     */
    UINT32          SockType;

    /**
     * @brief       Layer3 Protocol (can by any custom L3 types)
     */
    UINT32          Protocol;

    /**
     * @brief       Socket Priority.
     */
    UINT16          SockPriority;

    /**
     * @brief       Socket Protocol Handler (SOCKPROT_RAWETH)
     */
    UINT32          SockProt;

    /**
     * @brief       Socket State flags (SS_...). Defined and used by
     *              NDK core stack internally.
     */
    UINT32          StateFlags;

    /**
     * @brief       Pointer to next socket in protocol list
     */
    struct _SOCKRAWETH     *pPrev;

    /**
     * @brief       Pointer to previous socket in protocol list
     */
    struct _SOCKRAWETH     *pNext;

    /* Protocol Control */

    /**
     * @brief       Handle to Interface on which packets need to
     *              be Rxed or Txed
     */
    HANDLE          hIF;

    /* Read-Write Stuff */

    /**
     * @brief       Error returned on socket call
     */
    INT32           ErrorPending;

    /**
     * @brief       Receive Timeout for the socket.
     */
    UINT32          RxTimeout;

    /**
     * @brief       Receive buffer size
     */
    UINT32          RxBufSize;

    /**
     * @brief       Transmit buffer size
     */
    UINT32          TxBufSize;

    /**
     * @brief       Handle to Receive buffer of the socket.
     */
    HANDLE          hSBRx;

    /**
     * @brief       Handle to Transmit buffer of the socket.
     */
    HANDLE          hSBTx;

    /**
     * @brief       Handle to Timestamp function.
     */
    TimestampFxn   	pTimestampFxn;

} SOCKRAWETH;

/* Socket Access Functions */

/*------------------------------------------------------------------------ */
/* General Access Functions (called from upper layers) */
_extern int    RawEthSockNew( int Family, int Type, int Protocol,
                        int RxBufSize, int TxBufSize, HANDLE *phSock );
_extern int    RawEthSockClose( HANDLE hSock );

_extern int    RawEthSockCheck( HANDLE hSock, int IoType );

_extern int    RawEthSockStatus( HANDLE hSock, int request, int *results );

_extern int    RawEthSockSet(HANDLE hSock, int Type, int Prop, void *pbuf, int size);
_extern int    RawEthSockGet(HANDLE hSock, int Type, int Prop, void *pbuf, int *psize);

_extern int    RawEthSockShutdown( HANDLE hSock, int how );

_extern int    RawEthSockSend( HANDLE hSock, INT8 *pBuf, INT32 size,
                        INT32 *pRetSize );
_extern int    RawEthSockRecvNC( HANDLE hSock, PBM_Pkt **ppPkt );
_extern int    RawEthSockSendNC( HANDLE hSock, INT8 *pBuf, INT32 size, HANDLE hPkt,
                        INT32 *pRetSize );


/*------------------------------------------------------------------------ */
/* PCB Related Socket Access Functions (called from stack protocols) */
_extern int    RawEthSockPcbAttach( HANDLE hSock );
_extern int    RawEthSockPcbDetach( HANDLE hSock );
_extern void   RawEthSockPcbCleanup(void);
_extern int    RawEthSockPcbInit (void);
_extern SOCKRAWETH* RawEthSockPcbFind( UINT32  Protocol, HANDLE hIF );


/*------------------------------------------------------------------------ */
/* Low-level Access Functions (called from stack protocols) */
_extern int    RawEthSockNotify( HANDLE hSock, int Notification );
_extern PBM_Pkt* RawEthSockCreatePacket( HANDLE hSock, UINT32 Payload, UINT32* pError );

#define RawEthSockGetProtocol( h )        (((SOCKRAWETH *)h)->Protocol)
#define RawEthSockGetRx( h )              (((SOCKRAWETH *)h)->hSBRx)
#define RawEthSockGetIF( h )              (((SOCKRAWETH *)h)->hIF)
#define RawEthSockGetPriority( h )        (((SOCKRAWETH *)h)->SockPriority)
#define RawEthSockSetError( h, e )        (((SOCKRAWETH *)h)->ErrorPending=(e))

#endif /* _SOCKIF_INC_ */

