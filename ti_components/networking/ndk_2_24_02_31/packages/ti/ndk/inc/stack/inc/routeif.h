/*
 * Copyright (c) 2013, Texas Instruments Incorporated
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
 * ======== routeif.h ========
 *
 */


#ifndef _C_ROUTEIF_INC
#define _C_ROUTEIF_INC  /* #defined if this .h file has been included */

/*----------------------------------------------------------------------- */
/* Global Task Information */

/*----------------------------------------------------------------------- */
/* Route Defined Messages */
#define MSG_ROUTE_TIMER                 (ID_ROUTE*MSG_BLOCK + 0)

/*----------------------------------------------------------------------- */
/* Route Status Flags */
/* Note: Routes are sorted by their flag values, so the higher value */
/*       flags are higher priority routes. (IFLOCAL before GATEWAY, etc.) */
#define FLG_RTE_UP              0x0001  /* Entry is "up" */
#define FLG_RTE_EXPIRED         0x0002  /* Entry is expired */
#define FLG_RTE_KEEPALIVE       0x0004  /* Stays Valid via ARP refresh */
#define FLG_RTE_STATIC          0x0008  /* Entry is static */
#define FLG_RTE_BLACKHOLE       0x0010  /* Discard packets w/o error */
#define FLG_RTE_REJECT          0x0020  /* Discard packets with error */
#define FLG_RTE_MODIFIED        0x0040  /* Modified dynamically (via redirect) */
#define FLG_RTE_DYNAMIC         0x0080  /* Created dynamically (via redirect) */
/* One of the following is always set and is thus the priority */
#define FLG_RTE_PROXYPUB        0x0100  /* Reply to ARP other MAC */
#define FLG_RTE_PROXY           0x0200  /* Reply to ARP w/IF MAC when not IF */
#define FLG_RTE_CLONING         0x0400  /* Generate clone routes for this route */
#define FLG_RTE_HOST            0x0800  /* Host Route (no sub-net mask) */
#define FLG_RTE_GATEWAY         0x1000  /* Gate is an IP gateway (indirect) */
#define FLG_RTE_IFLOCAL         0x2000  /* Host Address is LOCAL */

/* Route Flag Full Description */
/*  FLG_RTE_UP */
/*      When set, indicates that the route is valid. The only time this */
/*      flag is cleared is when the route is being initialized, or when */
/*      an error condition is signaled via RtSetFailure(). The flag is */
/*      reset to TRUE by calling RtSetFailure() with NULL failure code, */
/*      or if the route is modified. */
/*  FLG_RTE_EXPIRED */
/*      When set, indicates that the route is expired. The flag can not */
/*      be cleared. A new route must be created. Expired routes are never */
/*      "found", but a route cached by another entity may expire why it */
/*      is being held. */
/*  FLG_RTE_BLACKHOLE */
/*      When set, indicates that the route is a "black hole". All */
/*      packets destined for this address are silently discarded. */
/*  FLG_RTE_REJECT */
/*      When set, indicates that the route is to an invalid address. All */
/*      packets destined for this address are discarded with an error */
/*      indication. */
/*  FLG_RTE_MODIFIED */
/*      When set, indicates that the route has been modified as a result */
/*      of a ICMP redirect message. */
/*  FLG_RTE_DYNAMIC */
/*      When set, indicates that the route was created dynamically via */
/*      an ICMP redirect. */
/*  FLG_RTE_STATIC */
/*      This flag is set when a route should remain in the routing table */
/*      even if it has no references. Various routes can be STATIC. In */
/*      this implimenation, STATIC routes will be manually referenced */
/*      by the system during create, and will be manually dereferenced */
/*      by the system during system shutdown. */
/*  FLG_RTE_PROXY */
/*      When set, indicates that ARP should respond to ARP requests for */
/*      the associated IP host/network when the network appears on a IF */
/*      device which is different from the incoming ARP request. The MAC */
/*      address supplied in the reply is that associated with the stack */
/*      IF device from which the request was received. A PROXY entry */
/*      has no LLI. This is used to "trick" clients into sending packets */
/*      to the router when subnets are split. */
/*      PROXY and PROXYPUB have nothing in common other than the word */
/*      PROXY in their name. */
/*  FLG_RTE_PROXYPUB */
/*      When set, indicates that ARP should respond to ARP requests for */
/*      the associated IP address with the supplied static MAC address */
/*      when the host is on the _same_ IF device as the incoming ARP */
/*      request. This allows support of hosts which do not implement */
/*      ARP (as if this is going to happen). PROXYPUB entries always */
/*      are created with a Mac Address, and thus contain a static LLI. */
/*      PROXY and PROXYPUB have nothing in common other than the word */
/*      PROXY in their name. */
/*  FLG_RTE_HOST */
/*      When set, indicates that the route entry is a host route. A */
/*      host route has no subnet mask (or rather a subnet mask of */
/*      all 1's in this implemenation). When searching for a route, */
/*      host routes always match before network routes (unless the */
/*      search is for a specific network mask). */
/*  FLG_RTE_GATEWAY */
/*      When set, indicates that the host or network route is indirectly */
/*      accessable via an IP gateway. For a route with this flag set, */
/*      the GateIP address is always valid. Most GATEWAY routes will also */
/*      be network routes, however a host redirect from ICMP can spawn */
/*      a host route with a different gateway than its parent route. In */
/*      general however, GATEWAY routes do not "clone" into host routes. */
/*  FLG_RTE_IFLOCAL */
/*      When set, indicates that the host route does not have a valid */
/*      LLI entry because the host is local to the stack. The MAC address */
/*      of this local IP host address can be obtained from the interface */
/*      handle associated with the route. */
/*      Local routes are in the routing table for the benefit of packets */
/*      which originate from the stack's upper layers. For ARP reqeusts */
/*      and routing of incoming packets to our stack, the IP address */
/*      list published via the Bind object is used. ARP will not respond */
/*      to, nor IP accept packets addressed to an IP adress not in the */
/*      Bind list, even if an IFLOCAL address is in the route table. */
/*  FLG_RTE_CLONING */
/*      When set, indicates that the network route is a cloning route. */
/*      Cloning routes clone host routes when a route allocation is */
/*      performed on a host address that is a member of the route */
/*      entry's network address. Cloned host routes take on most of the */
/*      properties of their parent network route, with the following */
/*      alterations: */
/*          - Any MODIFIED or DYNAMIC flags are cleared. */
/*          - The STATIC flag is never set. */
/*          - The HOST flag is set and the netmask is set to 1's. */
/*          - Any metrics are COPIED and set in the new HOST route. */
/*          - The CLONING flag is cleared. */
/*  FLG_RTE_KEEPALIVE */
/*      When set, indicates that the route can be updated via ARP. In */
/*      this case, LLI will track the time of the last ARP request or */
/*      reply. When the route expires (the expiration queue is not */
/*      resorted for every ARP), the LLI entry is checked to see if the */
/*      route expiration should be extended. */
/*--------------------------------------------------------------------------- */
/* Route Flags to Available Propery Decode */
/*  FLG_RTE_UP         Off */
/*    - Failure Code Available */
/*  FLG_RTE_GATEWAY    On */
/*    - IP Gateway Available */
/*  FLG_RTE_GATEWAY    Off */
/*  FLG_RTE_IFLOCAL    Off */
/*    - Interface Handle Available */
/*  FLG_RTE_PROXYPUB   On */
/*    - LLI available */
/*  FLG_RTE_HOST       On */
/*  FLG_RTE_GATEWAY    Off */
/*  FLG_RTE_PROXY      Off */
/*  FLG_RTE_IFLOCAL    Off */
/*     - LLI Entry Available */
/*  FLG_RTE_HOST       Off */
/*     - Network Route IPAddr and IPMask Available */
/*  FLG_RTE_HOST       On */
/*     - Network Route IPAddr Available (IPMask would return 1's) */
/*--------------------------------------------------------------------------- */

/*--------------------------------------------------------------------------- */
/* Legal Route Flag Combinations */
/*  FLG_RTE_BLACKHOLE */
/*    FLG_RTE_REJECT      must be OFF */
/*  FLG_RTE_REJECT */
/*    FLG_RTE_BLACKHOLE   must be OFF */
/*  FLG_RTE_DYNAMIC */
/*    FLG_RTE_GATEWAY     must be ON */
/*  FLG_RTE_MODIFIED */
/*    FLG_RTE_GATEWAY     must be ON */
/*  FLG_RTE_HOST */
/*    FLG_RTE_CLONING     must be OFF */
/*  FLG_RTE_PROXY */
/*    FLG_RTE_GATEWAY     must be OFF */
/*    FLG_RTE_DYNAMIC     must be OFF */
/*    FLG_RTE_MODIFIED    must be OFF */
/*    FLG_RTE_CLONING     must be OFF */
/*  FLG_RTE_PROXYPUB */
/*    FLG_RTE_HOST        must be ON */
/*    FLG_RTE_CLONING     must be OFF */
/*    FLG_RTE_GATEWAY     must be OFF */
/*    FLG_RTE_DYNAMIC     must be OFF */
/*    FLG_RTE_MODIFIED    must be OFF */
/*  FLG_RTE_GATEWAY */
/*    FLG_RTE_PROXY       must be OFF */
/*    FLG_RTE_PROXYPUB    must be OFF */
/*    FLG_RTE_IFLOCAL     must be OFF */
/*    FLG_RTE_CLONING     must be OFF */
/*  FLG_RTE_IFLOCAL */
/*    FLG_RTE_HOST        must be ON */
/*    FLG_RTE_CLONING     must be OFF */
/*    FLG_RTE_GATEWAY     must be OFF */
/*    FLG_RTE_DYNAMIC     must be OFF */
/*    FLG_RTE_MODIFIED    must be OFF */
/*    FLG_RTE_PROXY       must be OFF */
/*    FLG_RTE_PROXYPUB    must be OFF */
/*    FLG_RTE_METRICS     must be OFF */
/*  FLG_RTE_CLONING */
/*    FLG_RTE_HOST        must be OFF */
/*    FLG_RTE_PROXY       must be OFF */
/*    FLG_RTE_PROXYPUB    must be OFF */
/*    FLG_RTE_GATEWAY     must be OFF */
/*    FLG_RTE_DYNAMIC     must be OFF */
/*    FLG_RTE_MODIFIED    must be OFF */
/*    FLG_RTE_IFLOCAL     must be OFF */
/*--------------------------------------------------------------------------- */

/*------------------------------------------------------------------------- */
/* Route Entry Structure */
typedef struct _rt {
    uint        Type;             /* Set to HTYPE_RT */
    uint        RefCount;         /* # of open alloc's to this entry */
    struct _rt  *pNextExp;        /* Next entry in Expiration List */
    UINT32      dwTimeout;        /* Expiration time in SECONDS */
    HANDLE      hNode;            /* Associated Node */
    struct _rt  *pNext;           /* Next entry with same masked IP */
    uint        Flags;            /* Entry flags */
    IPN         IPAddr;           /* Destination IP address */
    IPN         IPMask;           /* Destination IP Mask */
    uint        MaskBits;         /* Number of 1 bits in mask */
    uint        FailCode;         /* NULL, or failure code */
    HANDLE      hIF;              /* IF (if any) */
    uint        ProtMTU;          /* Protocol MTU as for this route */
    IPN         IPGate;           /* Gateway IP addr (if any) */
    HANDLE      hLLI;             /* LLI Entry (if any) */
    } RT;

/*------------------------------------------------------------------------- */
/* Route Call Flags */
#define FLG_RTF_REPORT          0x0001  /* Forward report to reporting chain */
#define FLG_RTF_CLONE           0x0002  /* Clone network route to host route */
#define FLG_RTF_HOST            0x0004  /* Find only host routes */
#define FLG_RTF_PROXY           0x0008  /* Find only PROXY routes */
#define FLG_RTF_PROXYPUB        0x0010  /* Find only PROXYPUB routes */
#define FLG_RTF_CONDITIONAL     (FLG_RTF_HOST|FLG_RTF_PROXY|FLG_RTF_PROXYPUB)

/*------------------------------------------------------------------------- */
/* Route Failure Codes */
#define RTC_HOSTDOWN            0x0001  /* Host is down */
#define RTC_HOSTUNREACH         0x0002  /* Host unreachable */
#define RTC_NETUNREACH          0x0003  /* Network unreachable */

/*------------------------------------------------------------------------- */
/* Access Functions */

#define RtRef(x)   ExecHRef(x)

/* Route Maintainence Calls */
_extern HANDLE  RtCreate( uint CallFlags, uint Flags, IPN IPAddr,
                         IPN IPMask, HANDLE hIF, IPN IPGate, UINT8 *pMacAddr );
_extern void    RtRedirect( IPN IPAddr, IPN IPGate );

_extern HANDLE  RtFind( uint CallFlags, IPN IP );
_extern void    RtDeRef( HANDLE hRt );

_extern HANDLE  RtWalkBegin();
_extern HANDLE  RtWalkNext( HANDLE hRt );
_extern void    RtWalkEnd( HANDLE hRt );

/* Route Object Management Calls */
_extern void    RtSetFailure( HANDLE hRt, uint CallFlags, uint FailCode );
_extern void    RtRemove( HANDLE hRt, uint CallFlags, uint FailCode );
_extern void    RtSetTimeout( HANDLE hRt, UINT32 dwTimeOut );

#ifdef _STRONG_CHECKING
_extern void    RtSetLLI( HANDLE hRt, HANDLE hLLI );
_extern void    RtSetMTU( HANDLE hRt, uint mtu );
_extern uint    RtGetFlags( HANDLE hRt );
_extern IPN     RtGetIPAddr( HANDLE hRt );
_extern IPN     RtGetIPMask( HANDLE hRt );
_extern IPN     RtGetGateIP( HANDLE hRt );
_extern HANDLE  RtGetIF( HANDLE hRt );
_extern uint    RtGetMTU( HANDLE hRt );
_extern HANDLE  RtGetLLI( HANDLE hRt );
_extern uint    RtGetFailure( HANDLE hRt );
#else
#define RtSetLLI( h, x )        (((RT *)(h))->hLLI = (x))
#define RtSetMTU( h, x )        (((RT *)(h))->ProtMTU=(x))
#define RtGetIPAddr( h )        (((RT *)(h))->IPAddr)
#define RtGetIPMask( h )        (((RT *)(h))->IPMask)
#define RtGetFlags( h )         (((RT *)(h))->Flags)
#define RtGetIF( h )            (((RT *)(h))->hIF)
#define RtGetMTU( h )           (((RT *)(h))->ProtMTU)
#define RtGetGateIP(h)          (((RT *)(h))->IPGate)
#define RtGetLLI( h )           (((RT *)(h))->hLLI)
#define RtGetFailure( h )       (((RT *)(h))->FailCode)
#endif

/* The following function is reserved for kernel use */
/* (Special handling for route entries in PBM structure) */
#ifndef __cplusplus
static inline void PBM_setRoute( PBM_Pkt *pPkt, HANDLE hRoute )
{
    if( hRoute )
        RtRef( hRoute );
    if( pPkt->hRoute )
        RtDeRef( pPkt->hRoute );
    pPkt->hRoute = hRoute;
}
#endif

#endif
