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
 * ======== route.c ========
 *
 * Route table object
 *
 */

#include <stkmain.h>
#include "route.h"

/*-------------------------------------------------------------------- */
/* RtNew - Create a route entry structure */
/* Static function used only by route API */
/*-------------------------------------------------------------------- */
static HANDLE RtNew()
{
    RT  *prt;

    if( !(prt = mmAlloc(sizeof(RT))) )
    {
        DbgPrintf(DBG_WARN,"RtNew: OOM");
        NotifyLowResource();
        return(0);
    }

    /* Initialize type */
    prt->Type = HTYPE_RT;

    /* Initialize refcount */
    prt->RefCount = 1;

    /* Initialize defaults */
    prt->pNextExp     = 0;
    prt->pNext        = 0;
    prt->dwTimeout    = 0;
    prt->Flags        = 0;
    prt->FailCode     = 0;
    prt->hNode        = 0;
    prt->hIF          = 0;
    prt->hLLI         = 0;
    prt->ProtMTU      = ROUTE_DEFAULT_MTU;

    return( (HANDLE)prt );
}

/*-------------------------------------------------------------------- */
/* RtFree - Destroy Route */
/* Static function used only by route API */
/*-------------------------------------------------------------------- */
static void RtFree( RT *prt )
{
    /* Kill type for debug */
    prt->Type = 0;

    /* Free the LLI */
    if( prt->hLLI )
        LLIFree( prt->hLLI );

    /* Remove from Timeout list */
    _RtExpListRemove( prt );

    /* Remove from Node list */
    _RtNodeRemove( prt );

    /* Free the handle if we're done with it */
    mmFree( prt );
}

/*-------------------------------------------------------------------- */
/* RtDeRef - DeReference a Route */
/* Decrement the reference count, and free if it reaches ZERO. */
/*-------------------------------------------------------------------- */
void RtDeRef( HANDLE hRt )
{
    RT     *prt = (RT *)hRt;

#ifdef _STRONG_CHECKING
    if( prt->Type != HTYPE_RT )
    {
        DbgPrintf(DBG_ERROR,"RtFree: HTYPE %04x",prt->Type);
        return;
    }
#endif

    /* Standard DeRef */
    /* (Zap the type if route should be deleted) */
    if( prt->RefCount != 65535 )
    {
        if( prt->RefCount > 1 )
            prt->RefCount--;                /* Deref one count */
        else
        {
            /* Post a report if needed */
            /* If the route is still active (has a node), we'll report it. */
            /* Otherwise, we'll assume it was a time-out. */
            if( prt->hNode )
                RTCReport(MSG_RTC_REMOVED, prt->IPAddr, prt->IPMask);
            RtFree( prt );
        }
    }
}

#ifdef _STRONG_CHECKING

/*-------------------------------------------------------------------- */
/* RtGetIPAddr - Get IP Addr */
/* Get the destination Ip Address associated with */
/* the route. */
/*-------------------------------------------------------------------- */
IPN RtGetIPAddr( HANDLE hRt )
{
    RT *prt = (RT *)hRt;

    if( prt->Type != HTYPE_RT )
    {
        DbgPrintf(DBG_ERROR,"RtGetIpAddr: HTYPE %04x",prt->Type);
        return(0);
    }
    return( prt->IPAddr );
}

/*-------------------------------------------------------------------- */
/* RtGetIPMask - Get IP Mask */
/* Get the destination Ip Mask associated with */
/* the route. */
/*-------------------------------------------------------------------- */
IPN RtGetIPMask( HANDLE hRt )
{
    RT *prt = (RT *)hRt;

    if( prt->Type != HTYPE_RT )
    {
        DbgPrintf(DBG_ERROR,"RtGetIpMask: HTYPE %04x",prt->Type);
        return(0);
    }
    return( prt->IPMask );
}

/*-------------------------------------------------------------------- */
/* RtGetFlags */
/* Get the Route Status Flags */
/*-------------------------------------------------------------------- */
uint RtGetFlags( HANDLE hRt )
{
    RT *prt = (RT *)hRt;

    if( prt->Type != HTYPE_RT )
    {
        DbgPrintf(DBG_ERROR,"RtGetFlags: HTYPE %04x",prt->Type);
        return(0);
    }
    return( prt->Flags );
}

/*-------------------------------------------------------------------- */
/* RtGetIF */
/* Get Interface Handle */
/*-------------------------------------------------------------------- */
HANDLE RtGetIF( HANDLE hRt )
{
    RT *prt = (RT *)hRt;

    if( prt->Type != HTYPE_RT )
    {
        DbgPrintf(DBG_ERROR,"RtGetIF: HTYPE %04x",prt->Type);
        return( 0 );
    }
    return( prt->hIF );
}

/*-------------------------------------------------------------------- */
/* RtGetMTU */
/* Get MTU of route */
/*-------------------------------------------------------------------- */
uint RtGetMTU( HANDLE hRt )
{
    RT *prt = (RT *)hRt;

    if( prt->Type != HTYPE_RT )
    {
        DbgPrintf(DBG_ERROR,"RtGetMTU: HTYPE %04x",prt->Type);
        return( 0 );
    }
    return( prt->ProtMTU );
}

/*-------------------------------------------------------------------- */
/* RtGetGateIP */
/* Get Gate IP Address */
/*-------------------------------------------------------------------- */
IPN RtGetGateIP( HANDLE hRt )
{
    RT *prt = (RT *)hRt;

    if( prt->Type != HTYPE_RT )
    {
        DbgPrintf(DBG_ERROR,"RtGetGateIP: HTYPE %04x",prt->Type);
        return( 0 );
    }
    return( prt->IPGate );
}

/*-------------------------------------------------------------------- */
/* RtGetLLI */
/* Get LLI */
/*-------------------------------------------------------------------- */
HANDLE RtGetLLI( HANDLE hRt )
{
    RT *prt = (RT *)hRt;

    if( prt->Type != HTYPE_RT )
    {
        DbgPrintf(DBG_ERROR,"RtGetLLI: HTYPE %04x",prt->Type);
        return( 0 );
    }
    return( prt->hLLI );
}

/*-------------------------------------------------------------------- */
/* RtGetFailure */
/* Get Failure Code */
/*-------------------------------------------------------------------- */
uint RtGetFailure( HANDLE hRt )
{
    RT *prt = (RT *)hRt;

    if( prt->Type != HTYPE_RT )
    {
        DbgPrintf(DBG_ERROR,"RtGetFailure: HTYPE %04x",prt->Type);
        return( 0 );
    }
    return( prt->FailCode );
}

/*-------------------------------------------------------------------- */
/* RtSetMTU */
/* Set the MTU of route */
/*-------------------------------------------------------------------- */
void RtSetMTU( HANDLE hRt, uint mtu )
{
    RT *prt = (RT *)hRt;

    if( prt->Type != HTYPE_RT )
    {
        DbgPrintf(DBG_ERROR,"RtSetMTU: HTYPE %04x",prt->Type);
        return;
    }
    prt->ProtMTU = mtu;
}

/*-------------------------------------------------------------------- */
/* RtSetLLI */
/* Set LLI Entry */
/*-------------------------------------------------------------------- */
void RtSetLLI( HANDLE hRt, HANDLE hLLI )
{
    RT *prt = (RT *)hRt;

    if( prt->Type != HTYPE_RT )
    {
        DbgPrintf(DBG_ERROR,"RtSetLLI: HTYPE %04x",prt->Type);
        return;
    }

    /* Make sure we don't already have an entry */
    if( prt->hLLI )
    {
        DbgPrintf(DBG_ERROR,"RtSetLLI: Double Set");
        return;
    }

    prt->hLLI = hLLI;
}

#endif

/*--------------------------------------------------------------------- */
/* RtSetFailure - Fail Route */
/* Flags: */
/*     FLG_RTF_REPORT      Report failure */
/* Failure Code: */
/*     NULL               - No Failure */
/*     RTC_HOSTDOWN       - Host is down */
/*     RTC_HOSTUNREACH    - Host unreachable */
/*     RTC_NETUNREACH     - Network unreachable */
/*--------------------------------------------------------------------- */
void RtSetFailure( HANDLE hRt, uint CallFlags, uint FailCode )
{
    RT *prt = (RT *)hRt;

#ifdef _STRONG_CHECKING
    if( prt->Type != HTYPE_RT )
    {
        DbgPrintf(DBG_ERROR,"RtSetFailure: HTYPE %04x",prt->Type);
        return;
    }
#endif

    /* First, update the failure code and UP flag */
    if( (prt->FailCode = FailCode) != 0 )
        prt->Flags &= ~FLG_RTE_UP;
    else
        prt->Flags |= FLG_RTE_UP;

    /* Post a report if requested */
    if( CallFlags & FLG_RTF_REPORT )
    {
        /* Send Routing Report */
        if( prt->Flags & FLG_RTE_UP )
            RTCReport( MSG_RTC_UP, prt->IPAddr, prt->IPMask );
        else
            RTCReport( MSG_RTC_DOWN, prt->IPAddr, prt->IPMask );
    }
}

/*--------------------------------------------------------------------- */
/* RtRemove - Remove a Route from the Route Table */
/* Flags: */
/*     FLG_RTF_REPORT      Report removal */
/* Failure Code: */
/*     RTC_HOSTDOWN       - Host is down */
/*     RTC_HOSTUNREACH    - Host unreachable */
/*     RTC_NETUNREACH     - Network unreachable */
/* Called to remove a route from the route table independently of any */
/* held refereces. This will cause the route to return the designated */
/* failure code to those that still hold a reference, but this function */
/* will also attempt to flush all cached references. */
/*--------------------------------------------------------------------- */
void RtRemove( HANDLE hRt, uint CallFlags, uint FailCode )
{
    RT   *prt = (RT *)hRt;
    int  deref = 0;

#ifdef _STRONG_CHECKING
    if( prt->Type != HTYPE_RT )
    {
        DbgPrintf(DBG_ERROR,"RtSetFailure: HTYPE %04x",prt->Type);
        return;
    }
#endif

    /* Set the failure code */
    prt->Flags |= FLG_RTE_UP;
    prt->FailCode = FailCode;

    /* Remove the entry from the timeout list if necessary */
    /* And keep track of the times we will deref */
    if( prt->dwTimeout )
    {
        _RtExpListRemove( prt );
        deref++;
    }

    /* If we're STATIC, clear it and add a deref */
    if( prt->Flags & FLG_RTE_STATIC )
    {
        prt->Flags &= ~FLG_RTE_STATIC;
        deref++;
    }

    /* Post a report if requested */
    if( CallFlags & FLG_RTF_REPORT )
        RTCReport( MSG_RTC_REMOVED, prt->IPAddr, prt->IPMask );

    /* Remove from Node list (removes the route from the route table) */
    _RtNodeRemove( prt );

    /* Notify all who cache routes */
    IPRtChange( (HANDLE)prt );
    SockPcbRtChange( (HANDLE)prt );

    /* DeRef the route for any TimeoutList or STATIC removals */
    while( deref-- )
        RtDeRef( prt );
}

/*--------------------------------------------------------------------- */
/* RtSetTimeout */
/* Set the timeout for a node in seconds */
/*--------------------------------------------------------------------- */
void RtSetTimeout( HANDLE hRt, UINT32 dwTimeout )
{
    RT    *prt = (RT *)hRt;

#ifdef _STRONG_CHECKING
    if( prt->Type != HTYPE_RT )
    {
        DbgPrintf(DBG_ERROR,"RtSetTimeout: HTYPE %04x",prt->Type);
        return;
    }
#endif

    /* Ignore this call if the route is already expired */
    if( prt->Flags & FLG_RTE_EXPIRED )
        return;

    /* Add one reference to the route if this is a NEW timeout */
    if( !prt->dwTimeout )
        RtRef( prt );

    /* Get physical Timeout in Seconds */
    dwTimeout += llTimerGetTime(0);

    /* Set the Timeout */
    _RtExpListInsert( prt, dwTimeout );
}

/*--------------------------------------------------------------------- */
/* RtCreate - Create a route */
/* Parameters: */
/*     CallFlags      Call Type Flags */
/*     Flags          Route Type Flags */
/*     IPAddr         Destination IP address of route */
/*     IPMask         Destination IP Mask of route (or NULL) */
/*     hIF            Interface (or NULL) */
/*     IPGate         Gate IP address (or NULL) */
/*     pMacAddr       Static host MAC address for hLLI (or NULL) */
/* Description: */
/*     Called to create a new host or network route and add it to the */
/*     route table. Existing routes can not be modified via this call. */

/*     Some flag combinations make no sense, but only the following are */
/*     strictly enforced. */

/*     FLG_RTE_UP in Flags is always SET. */

/*     FLG_RTE_EXPIRED and FLG_RET_MODIFIED in Flags is always CLEARED. */

/*     If FLG_RTE_STATIC is specified in Flags, the route is referenced */
/*     once by the route code, and later dereferenced during shutdown. */

/*     If FLG_RTE_PROXYPUB is specified in Flags, then FLG_RTE_HOST must */
/*     also be set, and pMacAddr must be valid. */

/*     If FLG_RTE_HOST is specified in Flags then the route is a host */
/*     route and IPMask is ignored. FLG_RTE_CLONING can not be set. */

/*     If FLG_RTE_GATEWAY is specified in Flags, then IPGate specifies */
/*     a valid IP address. */

/*     If FLG_RTE_IFLOCAL is specified in Flags, then the specified host */
/*     address is local to this machine. FLG_RTE_HOST must also be set and */
/*     hIF must be valid. */

/*     If FLG_RTE_CLONING is specified in Flags, the route is a cloning */
/*     network route. The IPMask argument must be valid, and the */
/*     FLG_RTE_HOST or FLG_RET_GATEWAY flag must not be set. */

/*     Note: LLIs do not "reference" their parent routes. If they did, */
/*     the route refcnt would never reach zero. */

/* Flags: */
/*     FLG_RTF_REPORT      Report any new or unfound route */

/* Returns: */
/*     Referenced handle to newly created route */
/*--------------------------------------------------------------------- */
HANDLE RtCreate( uint CallFlags, uint Flags, IPN IPAddr,
                 IPN IPMask, HANDLE hIF, IPN IPGate, UINT8 *pMacAddr )
{
    RT     *prt;
    UINT32 dwTest;
    uint MaskBits;

    /* Clear/Set required flags */
    Flags |= FLG_RTE_UP;
    Flags &= ~(FLG_RTE_MODIFIED|FLG_RTE_EXPIRED);

    /* Verify Legal Flag Configuration */

    /* A PROXYPUB entry must be a HOST and have a MAC address supplied. */
    if( (Flags & FLG_RTE_PROXYPUB) && (!(Flags & FLG_RTE_HOST) || !pMacAddr) )
        return(0);

    /* Host routes can not be CLONING routes. Also, if DYNAMIC, they */
    /* must be GATEWAY routes, since directly connected DYNAMIC routes */
    /* are illegal. */
    if( Flags & FLG_RTE_HOST )
    {
        if( Flags & FLG_RTE_CLONING )
            return(0);
        if( (Flags & FLG_RTE_DYNAMIC) && !(Flags & FLG_RTE_GATEWAY) )
            return(0);
    }

    /* GATEWAY routes must have a valid (and reachable) IPGate, and */
    /* can not be CLONING routes. */
    if( Flags & FLG_RTE_GATEWAY )
    {
        if( Flags & FLG_RTE_CLONING )
            return(0);
        if( !IPGate || IPGate == IPAddr || !BindFindByNet(0,IPGate) )
            return(0);
    }
    /* Non-GATWAY routes must have an IF */
    else if( !hIF )
        return(0);

    /* Create Route */

    /* Create the route structure */
    if( !(prt = (RT *)RtNew()) )
        return(0);

    /* Transfer the calling arguments */
    prt->hIF    = hIF;
    prt->Flags  = Flags;
    prt->IPAddr = IPAddr;
    prt->IPMask = IPMask;
    prt->IPGate = IPGate;

    /* If we have an IF, validate the MTU */
    if( hIF )
        prt->ProtMTU = IFGetMTU( hIF );

    /* Check route type */
    if( Flags & FLG_RTE_HOST )
    {
        /* Route is a host route */

        prt->IPMask  = 0xffffffff;
        prt->MaskBits = 32;

        /* If the interface is unknown or Ethernet, then create */
        /* the LLI if MacAddr is provided, or if the route is not */
        /* IFLOCAL or GATEWAY */
        if( (!hIF || IFGetType(hIF)==HTYPE_ETH) &&
            ( pMacAddr || !(prt->Flags & (FLG_RTE_IFLOCAL|FLG_RTE_GATEWAY)) ) )
        {
            /* Create static LLI */
            prt->hLLI = LLINew( prt, pMacAddr );

            /* Check for an error */
            if( !prt->hLLI )
            {
                RtFree( prt );
                return(0);
            }
        }
    }
    else
    {
        /* Route is a network route */

        /* Validate the Mask Bits */
        IPMask = HNC32( IPMask );   /* Convert to host format */
        dwTest = 0x80000000;
        MaskBits = 0;
        while( dwTest & IPMask )
        {
            MaskBits++;
            dwTest >>= 1;
        }
        prt->MaskBits = MaskBits;
    }

    /* We're now ready to add the route to the NODE tree. */
    if( !_RtNodeInsert( prt ) )
    {
        RtFree( prt );
        return(0);
    }

    /* STATIC routes add a system reference which is removed at */
    /* system shutdown */
    if( prt->Flags & FLG_RTE_STATIC )
        RtRef( prt );

    /* Next, post a report if needed */
    if( CallFlags & FLG_RTF_REPORT )
    {
        /* Send Routing Report */
        RTCReport( MSG_RTC_NEW, prt->IPAddr, prt->IPMask );
    }

    return( prt );
}

/*--------------------------------------------------------------------- */
/* RtRedirect - Create Static Host Redirect Route */
/* Parameters: */
/*     IPHost         Host IP address to redirect */
/*     IPGate         Gate IP address */
/* Description: */
/*     Called to create or modify a gatway host route. */
/* Returns: */
/*     void */
/*--------------------------------------------------------------------- */
void RtRedirect( IPN IPHost, IPN IPGate )
{
    RT *prt;

    /* Brain damage check - Gateway must be valid and reachable */
    if( !IPGate || IPGate == IPHost || !BindFindByNet(0,IPGate) )
        return;

    /* Find the closest route we have */
    prt = RtFind( 0, IPHost );

    if( prt )
    {
        /* See if we can modify this route */
        if( (prt->Flags & (FLG_RTE_HOST|FLG_RTE_GATEWAY))
                                   == (FLG_RTE_HOST|FLG_RTE_GATEWAY) )
        {
            /* Modify existing route */
            prt->Flags |= FLG_RTE_MODIFIED;
            prt->IPGate = IPGate;
            RtDeRef( prt );
            return;
        }
        RtDeRef( prt );
    }

    /* Create new gateway route */
    prt = RtCreate( FLG_RTF_REPORT,
                    FLG_RTE_HOST|FLG_RTE_GATEWAY|FLG_RTE_DYNAMIC|FLG_RTE_STATIC,
                    IPHost, 0xffffffff, 0, IPGate, 0 );

    if( prt )
        RtDeRef( prt );
}

