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
 * ======== bind.c ========
 *
 * IP/Ether binding object
 *
 */

#include <stkmain.h>

/* Address Structure */
typedef struct _bind {
          uint          Type;           /* Set to HTYPE_BIND */
          struct _bind  *pNext;         /* Next Binding */
          HANDLE        hIF;            /* Interface Handle */
          HANDLE        hRtNet;         /* Net Route */
          HANDLE        hRtHost;        /* Host Route */
          IPN           IPHost;         /* IP Addr */
          IPN           IPNet;          /* IP Net */
          IPN           IPMask;         /* IP Mask */
         } BIND;

static BIND *pbindFirst = 0;

/*-------------------------------------------------------------------- */
/* BindNew() */
/* Create */
/*-------------------------------------------------------------------- */
HANDLE BindNew( HANDLE hIF, IPN IPHost, IPN IPMask )
{
    BIND   *pbind,*pbtmp;
    IPN    IPNet = 0xffffffff;
    uint   type;

    /* Verify the IF Handle */
    if( !hIF )
    {
        DbgPrintf(DBG_ERROR,"BindNew: Illegal Device Handle");
        return(0);
    }

    /* Get the IF type */
    type = IFGetType(hIF);

    /* Calc IPNet */
    if( IPMask != 0xffffffff )
        IPNet = IPHost & IPMask;

    /* Search for duplicate bindings */
    if( (pbtmp = (BIND *)BindFindByHost(0, IPHost) ) ||
        ((IPNet!=0xffffffff) && (pbtmp = (BIND *)BindFindByNet(0, IPNet))) )
    {
        /* Duplicate bindings allowed on PPP links */
        if( type != HTYPE_PPP && IFGetType(pbtmp->hIF) != HTYPE_PPP )
        {
            DbgPrintf(DBG_WARN,"BindNew: Duplicate bindings ignored");
            return(0);
        }
    }

    if( !(pbind = mmAlloc(sizeof(BIND))) )
    {
        DbgPrintf(DBG_WARN,"BindNew: OOM");
        NotifyLowResource();
        return(0);
    }

    /* Initialize type */
    pbind->Type = HTYPE_BIND;

    /* Fill in the binding */
    pbind->hIF      = hIF;
    pbind->IPHost   = IPHost;
    pbind->IPNet    = IPNet;
    pbind->IPMask   = IPMask;

    /* Create a host and net route for this binding */
    pbind->hRtHost = RtCreate( FLG_RTF_REPORT, FLG_RTE_HOST|FLG_RTE_IFLOCAL,
                               IPHost, 0xffffffff, hIF, 0, 0 );
    if( (IPNet!=0xffffffff) && type != HTYPE_PPP )
    {
        pbind->hRtNet = RtCreate( FLG_RTF_REPORT, FLG_RTE_CLONING,
                                  IPNet, IPMask, hIF, 0, 0 );
    }
    else
        pbind->hRtNet = 0;

    /* Tack binding pointer onto the list */
    pbind->pNext = pbindFirst;
    pbindFirst   = pbind;

    /* Gratuitous ARP on Ethernet */
    if( IFGetType( hIF ) == HTYPE_ETH && IPHost != INADDR_ANY
                                         && IPHost != INADDR_BROADCAST )
        LLIGenArpPacket( hIF, IPHost );

    return( (HANDLE)pbind );
}

/*-------------------------------------------------------------------- */
/* BindFree() */
/* Destroy */
/*-------------------------------------------------------------------- */
void BindFree( HANDLE h )
{
    BIND *pbind = (BIND *)h;
    BIND *pbindTmp;

#ifdef _STRONG_CHECKING
    if( pbind->Type != HTYPE_BIND )
    {
        DbgPrintf(DBG_ERROR,"BindFree: HTYPE %04x",pbind->Type);
        return;
    }
#endif

    /* Kill type for debug */
    pbind->Type = 0;

    /* Remove from list */
    if( pbind == pbindFirst )
        pbindFirst = pbind->pNext;
    else
    {
        pbindTmp = pbindFirst;
        while( pbindTmp && pbindTmp->pNext != pbind )
            pbindTmp = pbindTmp->pNext;
        if( pbindTmp )
            pbindTmp->pNext = pbind->pNext;
    }

    /* Deref Routes */
    if( pbind->hRtHost )
    {
        RtRemove( pbind->hRtHost, FLG_RTF_REPORT, RTC_NETUNREACH );
        RtDeRef( pbind->hRtHost );
    }
    if( pbind->hRtNet )
    {
        RtRemove( pbind->hRtNet, FLG_RTF_REPORT, RTC_NETUNREACH );
        RtDeRef( pbind->hRtNet );
    }

    /* Free Entry */
    mmFree( pbind );
}

/*-------------------------------------------------------------------- */
/* BindFindByIF( HANDLE hIF ) */
/* Find a binding by searching IP Host address */
/* hIF can be NULL */
/*-------------------------------------------------------------------- */
HANDLE BindFindByIF( HANDLE hIF )
{
    BIND *pbind;

    pbind = pbindFirst;
    while(pbind)
    {
        if( hIF && pbind->hIF != hIF )
            pbind = pbind->pNext;
        else
            break;
    }
    return( pbind );
}

/*-------------------------------------------------------------------- */
/* BindFindByHost( HANDLE hIF, IPN IP ) */
/* Find a binding by searching IF handle with IP Host addr */
/* hIF can be NULL */
/*-------------------------------------------------------------------- */
HANDLE BindFindByHost( HANDLE hIF, IPN IP )
{
    BIND *pbind;

    pbind = pbindFirst;
    while( pbind )
    {
        if( IP == pbind->IPHost && (!hIF || pbind->hIF == hIF) )
            break;
        pbind = pbind->pNext;
    }

    return( pbind );
}

/*-------------------------------------------------------------------- */
/* BindFindByNet( HANDLE hIF, IPN IP ) */
/* Find a binding by searching IF handle with IP Net Addr */
/* hIF can be NULL */
/*-------------------------------------------------------------------- */
HANDLE BindFindByNet( HANDLE hIF, IPN IP )
{
    BIND *pbind;

    pbind = pbindFirst;
    while( pbind )
    {
        if( ((IP & pbind->IPMask) == pbind->IPNet) &&
            (!hIF || pbind->hIF == hIF) )
            break;
        pbind = pbind->pNext;
    }

    return( pbind );
}

/*-------------------------------------------------------------------- */
/* BindIFNet2IPHost( HANDLE hIF, IPN IP ) */
/* Return an IP host address for this IF */
/* hIF can be NULL */
/*-------------------------------------------------------------------- */
IPN BindIFNet2IPHost( HANDLE hIF, IPN IP )
{
    BIND *pbind;

    if( !(pbind = (BIND *)BindFindByNet( hIF, IP )) )
        return(0);

    return( pbind->IPHost );
}

/*-------------------------------------------------------------------- */
/* BindIF2IPHost( HANDLE hIF ) */
/* Return an IP host address for this IF */
/* hIF can be NULL */
/*-------------------------------------------------------------------- */
IPN BindIF2IPHost( HANDLE hIF )
{
    BIND *pbind;

    if( !(pbind = (BIND *)BindFindByIF( hIF )) )
        return(0);

    return( pbind->IPHost );
}

/*-------------------------------------------------------------------- */
/* BindIPHost2IF( IPN IP ) */
/* Return an IF for this IP Host */
/*-------------------------------------------------------------------- */
HANDLE BindIPHost2IF( IPN IP )
{
    BIND *pbind;

    if( !(pbind = (BIND *)BindFindByHost( 0, IP )) )
        return(0);

    return( pbind->hIF );
}

/*-------------------------------------------------------------------- */
/* BindIPNet2IF( IPN IP ) */
/* Return an IF for this IP Network */
/*-------------------------------------------------------------------- */
HANDLE BindIPNet2IF( IPN IP )
{
    BIND *pbind;

    if( !(pbind = (BIND *)BindFindByNet( 0, IP )) )
        return(0);

    return( pbind->hIF );
}

/*-------------------------------------------------------------------- */
/* BindGetFirst() */
/* Get the first binding */
/*-------------------------------------------------------------------- */
HANDLE BindGetFirst()
{
    return( pbindFirst );
}

/*-------------------------------------------------------------------- */
/* BindGetNext() */
/* Get the next binding */
/*-------------------------------------------------------------------- */
HANDLE BindGetNext( HANDLE hBind )
{
    BIND *pbind = (BIND *)hBind;

#ifdef _STRONG_CHECKING
    if( pbind->Type != HTYPE_BIND )
    {
        DbgPrintf(DBG_ERROR,"BindGetNext: HTYPE %d",pbind->Type);
        return(0);
    }
#endif

    return( pbind->pNext );
}

/*-------------------------------------------------------------------- */
/* BindGetIF() */
/* Get the Interface associated with a binding */
/*-------------------------------------------------------------------- */
HANDLE BindGetIF( HANDLE hBind )
{
    BIND *pbind = (BIND *)hBind;

#ifdef _STRONG_CHECKING
    if( pbind->Type != HTYPE_BIND )
    {
        DbgPrintf(DBG_ERROR,"BindGetIF: HTYPE %d",pbind->Type);
        return(0);
    }
#endif

    return( pbind->hIF );
}

/*-------------------------------------------------------------------- */
/* BindGetIP() */
/* Get the IP information associated with a binding */
/*-------------------------------------------------------------------- */
void BindGetIP( HANDLE hBind, IPN *pIPHost, IPN *pIPNet, IPN *pIPMask )
{
    BIND *pbind = (BIND *)hBind;

#ifdef _STRONG_CHECKING
    if( pbind->Type != HTYPE_BIND )
    {
        DbgPrintf(DBG_ERROR,"BindGetIP: HTYPE %d",pbind->Type);
        return;
    }
#endif

    if( pIPHost )
        *pIPHost = pbind->IPHost;
    if( pIPNet )
        *pIPNet = pbind->IPNet;
    if( pIPMask )
        *pIPMask = pbind->IPMask;
}


/*-------------------------------------------------------------------- */
/* BindGetIFByDBCast() */
/* Return an interface handle based on a directed broadcast address */
/*-------------------------------------------------------------------- */
HANDLE BindGetIFByDBCast( IPN IP )
{
    BIND *pbind;

    if( !(pbind = (BIND *)BindFindByNet( 0, IP )) )
        return(0);

    if( (pbind->IPMask != 0xFFFFFFFF) &&
            ((pbind->IPMask | IP) == 0xFFFFFFFF) )
        return( pbind->hIF );

    return(0);
}
