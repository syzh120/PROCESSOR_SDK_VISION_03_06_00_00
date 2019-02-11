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
 * ======== rtable.c ========
 *
 * Routines related to route table
 *
 */

#include <stkmain.h>
#include "route.h"

static RT   *prtFirstExp  = 0;    /* First route in Exp list */
static uint _RtNoTimer    = 0;    /* Set to disable timer */

static UINT32 dwTestChecked = 0;
static UINT32 dwTestAttempt = 0;
static UINT32 dwTestRevived = 0;

static void  RtTimeoutCheck();
static void  RtFlush();

/*-------------------------------------------------------------------- */
/* RouteMsg() */
/* Sevices initialization, resource and timer messages */
/*-------------------------------------------------------------------- */
void RouteMsg( uint Msg )
{
    static HANDLE hTimer;

    switch( Msg )
    {
    /* System Initialization */
    case MSG_EXEC_SYSTEM_INIT:
        /* The odd timer period helps stagger it from the LLI timer */
        hTimer = TimerNew( &RouteMsg, TIMER_TICKS_ROUTE, MSG_ROUTE_TIMER );
        NodeTreeNew();
        break;

    /* System Shutdown */
    case MSG_EXEC_SYSTEM_SHUTDOWN:
        RtFlush();
        NodeTreeFree();
        if( hTimer )
            TimerFree( hTimer );
        break;

    /* Ten Second Timer */
    case MSG_ROUTE_TIMER:
        RtTimeoutCheck();
        break;
    }
}

/*-------------------------------------------------------------------- */
/* RtTimeoutCheck - Check for Timed-out Route */
/*-------------------------------------------------------------------- */
static void RtTimeoutCheck()
{
    RT     *prt;
    UINT32 dwTimeNow;
    UINT32 dwTimeTmp;

    /* The timeout list is pre-sorted by time. Continue timing out */
    /* routes until we done ONE that isn't ready. */

    if( _RtNoTimer )
        return;

    dwTimeNow = llTimerGetTime(0);

dwTestChecked++;
    do
    {
        /* Get expired entry off list */
        prt = prtFirstExp;
        if( prt && prt->dwTimeout <= dwTimeNow )
            prtFirstExp = prt->pNextExp;
        else
            prt = 0;

        if( prt )
        {
dwTestAttempt++;
            /* Clear the expiration time */
            prt->dwTimeout = 0;

            /* If this is of type "KEEPALIVE", call the LLI to */
            /* get the KEEPALIVE time and defer timeout. */
            if( (prt->Flags & FLG_RTE_KEEPALIVE) &&
                    (dwTimeTmp = LLIGetValidTime( prt->hLLI )) &&
                    (dwTimeTmp > dwTimeNow) )
            {
dwTestRevived++;
                _RtExpListInsert( prt, dwTimeTmp );
            }
            else
            {
                /* Timeout Entry */
                prt->Flags |= FLG_RTE_EXPIRED;

                /* Remove it from the node chain */
                _RtNodeRemove( prt );

                /* Next, post a report */
                RTCReport(MSG_RTC_EXPIRED, prt->IPAddr, prt->IPMask);

                /* Notify all who cache routes */
                IPRtChange( (HANDLE)prt );
                SockPcbRtChange( (HANDLE)prt );

                /* DeRef the expired node (was ref'd when timeout set) */
                RtDeRef( prt );
            }
        }
    } while( prt );
}

/*-------------------------------------------------------------------- */
/* RtFlush - Flush the Route Tree */
/*-------------------------------------------------------------------- */
static void RtFlush()
{
    uint   wKilled;
    RT     *prt;

    /* Kill Everything in the Timeout List */
    prt = prtFirstExp;
    while( prt )
    {
        /* Timeout Entry */
        prt->Flags |= FLG_RTE_EXPIRED;

        /* Get it out of the list */
        prtFirstExp = prt->pNextExp;

        /* Clear the expiration time */
        prt->dwTimeout = 0;

        /* Remove it from the node chain */
        _RtNodeRemove( prt );

        /* DeRef the expired node (was ref'd when timeout set) */
        RtDeRef( prt );

        /* Go to next entry */
        prt = prtFirstExp;
    }

    /* Kill all STATIC routes */
    do
    {
        /* Start Walking */
        prt = RtWalkBegin();
        wKilled = 0;
        while( prt && !wKilled )
        {
            /* Look for ANY static route */
            if( prt->Flags & FLG_RTE_STATIC )
            {
                /* Found a static route */

                /* Make it non-static */
                prt->Flags &= ~FLG_RTE_STATIC;

                /* Remove it from the node chain */
                _RtNodeRemove( prt );

                /* DeRef it */
                RtDeRef( prt );

                /* Flag that we killed a route */
                wKilled = 1;
            }
            else
                prt = RtWalkNext(prt);
        }
        /* We killed a route or ran out of routes. Either way */
        /* we need to end the walk (and potentially start over). */
        RtWalkEnd( prt );
    } while( wKilled );
}


/*-------------------------------------------------------------------- */
/* _RtNodeInsert - Insert a route into the Node tree */
/* Returns 1 on Success */
/*         0 on Error */
/*-------------------------------------------------------------------- */
uint _RtNodeInsert( RT *prt )
{
    RT *prtFirst,*prtPrev,*prtNext;

    /* Check for idiots */
    if( prt->hNode )
        return(1);

    /* Get the node that is or will be associated with this route */
    if( !(prt->hNode = NodeAdd(prt->IPAddr,prt->IPMask,prt->MaskBits)) )
        return(0);

    /* Get the first route for this node */
    prtFirst = (RT *)NodeGetRt( prt->hNode );

    if( !prtFirst )
    {
        /* This is the easy case. We're the first and only! */
        prtFirst = prt;
    }
    else
    {
        /* We need to find: */
        /* 1. Who's first     (prtFirst) */
        /* 2. Who's BEFORE us (prtPrev) */
        /* 3. Who's AFTER us  (prtNext) */
        /* We always sort by MOST specific MASK first. In the case of */
        /* a MASK tie, the higher IP address wins. In case an address tie, */
        /* the higher flags value wins (GATEWAY found before HOST, etc.). */

        /* i.e. THIS FUNCTION IS NOT USED TO MODIFY EXISTING ROUTES! */

        prtPrev = 0;
        prtNext = prtFirst;
        while( prtNext )
        {
            /* Most Specific Mask Wins */
            if( prt->MaskBits > prtNext->MaskBits )
                break;

            /* In case of a tie ... */
            if( prt->MaskBits == prtNext->MaskBits )
            {
                /* Higher IP address breaks ties */
                if( prt->IPAddr > prtNext->IPAddr )
                    break;

                /* Incase of a tie... */
                if( prt->IPAddr == prtNext->IPAddr )
                {
                    if( prt->Flags > prtNext->Flags )
                        break;
                }
            }

            /* Otherwise, get the next Rt in the chain */
            prtPrev = prtNext;
            prtNext = prtNext->pNext;
        }

        /* Now prtNext holds the entry we go BEFORE, and prtPrev holds */
        /* the entry we go AFTER. */
        if( !prtPrev )
        {
            /* Here, we're still first, but we need to chain the old */
            /* routes to us. */
            prtFirst = prt;
            prt->pNext = prtNext;
        }
        else
        {
            /* Here, there is someone before us, and potentially after us. */
            prtPrev->pNext = prt;
            prt->pNext = prtNext;
        }
    }

    /* prtFirst holds the new route chain head */
    NodeSetRt( prt->hNode, prtFirst );
    return(1);
}

/*-------------------------------------------------------------------- */
/* _RtNodeRemove - Remove route from node tree */
/*-------------------------------------------------------------------- */
void _RtNodeRemove( RT *prt )
{
    RT *prtFirst,*prtNext,*prtPrev;

    if( prt->hNode )
    {
        /* Remove us from the node */
        prtFirst = (RT *)NodeGetRt( prt->hNode );
        prtNext  = prtFirst;

        /* Look for our entry (we may not be there) */
        while( prtNext != prt && prtNext->pNext )
        {
            prtPrev = prtNext;
            prtNext = prtNext->pNext;
        }

        /* Check to see if we're in the list */
        if( prtNext == prt )
        {
            /* Remove ourselves from the chain */

            /* If we're first, set the node Rt to our "next" */
            /* otherwise, set the PREV rt to point our "next". */
            if( prt == prtFirst )
                NodeSetRt( prt->hNode, prt->pNext );
            else
                prtPrev->pNext = prt->pNext;
        }
        NodeDeRef( prt->hNode );
        prt->hNode = 0;
    }
}

/*-------------------------------------------------------------------- */
/* _RtExpListInsert - Insert route into expiration list */
/*-------------------------------------------------------------------- */
void _RtExpListInsert( RT *prt, UINT32 dwExp )
{
    RT *prtTmp;

    if( !dwExp )
        _RtExpListRemove( prt );
    else
    {
        /* Remove the entry if its already in the list */
        if( prt->dwTimeout )
            _RtExpListRemove( prt );

        /* Save the expiration */
        prt->dwTimeout = dwExp;

        /* Now add the entry to the list */
        /* Check the easy case - being first */
        if( !prtFirstExp || prtFirstExp->dwTimeout >= dwExp )
        {
            /* What we point to next */
            prt->pNextExp = prtFirstExp;
            /* Before us...pointing to us */
            prtFirstExp = prt;
        }
        else
        {
            /* Find an entry we expire AFTER */
            prtTmp = prtFirstExp;
            while( prtTmp->pNextExp &&
                   prtTmp->pNextExp->dwTimeout < dwExp )
                prtTmp = prtTmp->pNextExp;

            /* What we point to next */
            prt->pNextExp = prtTmp->pNextExp;
            /* Before us...pointing to us */
            prtTmp->pNextExp = prt;
        }
    }
}

/*-------------------------------------------------------------------- */
/* _RtExpListRemove - Remove route from expiration list */
/* Note: Normally, routes will be removed off the top of the list. */
/* However, if the route is prematurely removed, it may be anywhere */
/* in the list. */
/*-------------------------------------------------------------------- */
void _RtExpListRemove( RT *prt )
{
    RT *prtTmp;

    /* Clear the expiration time */
    prt->dwTimeout = 0;

    /* Check to see if we're the head of the list */
    if( prt == prtFirstExp )
        prtFirstExp = prt->pNextExp;
    else
    {
        /* Look for us */
        prtTmp = prtFirstExp;
        while( prtTmp && prtTmp->pNextExp != prt )
            prtTmp = prtTmp->pNextExp;

        /* Patch entry which points to us */
        if( prtTmp )
            prtTmp->pNextExp = prt->pNextExp;
    }
}

/*-------------------------------------------------------------------- */
/* RtWalkBegin - Get First Route in Tree */
/* (Refs returned route) */
/*-------------------------------------------------------------------- */
HANDLE RtWalkBegin()
{
    HANDLE hNode;
    HANDLE hRt = 0;

    /* Disable Timeouts */
    _RtNoTimer++;

    /* Get the first node */
    hNode = NodeWalk( 0 );

    /* Return the first route on the fist node */
    while( hNode && !hRt )
    {
        if( (hRt = NodeGetRt( hNode )) )
            RtRef( hRt );
        else
            hNode = NodeWalk( hNode );
    }

    return( hRt );
}

/*-------------------------------------------------------------------- */
/* RtWalkNext - Get Next Route in Tree */
/* (DeRefs supplied route) */
/* (Refs returned route) */
/*-------------------------------------------------------------------- */
HANDLE RtWalkNext( HANDLE hRt )
{
    RT     *prt    = (RT *)hRt;
    RT     *prtRet = 0;
    HANDLE hNode;

    if( prt->Type != HTYPE_RT )
    {
        DbgPrintf(DBG_ERROR,"RtWalkGetNext: HTYPE %04x",prt->Type);
        return(0);
    }

    /* First walk down the Rt list */
    if( (prtRet = prt->pNext) )
        RtRef( prtRet );
    else
    {
        hNode = NodeWalk( prt->hNode );
        while( hNode && !prtRet )
        {
            if( (prtRet = (RT*)NodeGetRt( hNode )) )
                RtRef( prtRet );
            else
                hNode = NodeWalk( hNode );
        }
    }

    RtDeRef( prt );

    return( prtRet );
}

/*-------------------------------------------------------------------- */
/* RtWalkEnd - End Tree Walk */
/*-------------------------------------------------------------------- */
void RtWalkEnd( HANDLE hRt )
{
    if( hRt )
    {
        if( ((RT*)hRt)->Type != HTYPE_RT )
            DbgPrintf(DBG_ERROR,"RtWalkEnd: Bad HTYPE");
        else
            RtDeRef( hRt );
    }

    /* Enable Timeouts */
    if( _RtNoTimer )
        _RtNoTimer--;
}

/*
void RtDiag()
{
    RT    *prt;
    UINT32 dwTimeNow;

    if( _RtNoTimer )
        DbgPrintf(DBG_INFO,"RtDiag: Timeouts Disabled");
    else
        DbgPrintf(DBG_INFO,"RtDiag: Timeouts Enabled");

    DbgPrintf(DBG_INFO,"RtDiag: Expiration Check:%u  Attempt:%u  Revive:%u",
                        dwTestChecked,dwTestAttempt,dwTestRevived);

    dwTimeNow = llTimerGetTime(0);
    prt = prtFirstExp;

    if( !prt )
        DbgPrintf(DBG_INFO,"RtDiag: No routes in Timeout List!");
    else if( (prt->dwTimeout+6) <= dwTimeNow )
        DbgPrintf(DBG_INFO,"RtDiag: Timeout Overdue");
    else if( prt->dwTimeout <= dwTimeNow )
        DbgPrintf(DBG_INFO,"RtDiag: Timeout Pending");
    else
        DbgPrintf(DBG_INFO,"RtDiag: Next Timeout in %u Seconds",
                                            prt->dwTimeout-dwTimeNow);
}
*/

/*--------------------------------------------------------------------- */
/* RtFind - Find a route */
/* Flags: */
/*     FLG_RTF_CLONE       Create cloned entry if needed */
/*     FLG_RTF_REPORT      Report any new or unfound route */
/*     FLG_RTF_HOST        Find only non-GATEWAY HOST routes */
/*     FLG_RTF_PROXY       Find only PROXY or PROXYPUB routes */
/*     FLG_RTF_PROXYPUB    Find only PROXY or PROXYPUB routes */
/* (Bumps reference count) */
/*--------------------------------------------------------------------- */
HANDLE RtFind( uint wCallFlags, IPN IP )
{
    RT     *prt,*prtClone;
    int    Search = 1;
    HANDLE hNode = 0;

    while( Search )
    {
        /* The following is guaranteed to find a node */
        hNode = NodeFind( IP, hNode );

        /* Now we need to find the "best" route on this node. */
        /* Note: Our search can be affected by the call flags */

        /* Get the route */
        prt = (RT *)NodeGetRt( hNode );

        /* We'll set the following flag to TRUE if we pass over a match */
        Search = 0;

        while( prt )
        {
            /* Try this route */
            if( (IP & prt->IPMask) != (prt->IPAddr & prt->IPMask) )
                goto RouteNotAccepted;

            /* Quit now if there are no matching conditions */
            if( !(wCallFlags & FLG_RTF_CONDITIONAL) )
                break;

            /* If we discard the match due to search criteria, first */
            /* mark if we can or can not continue. We don't continue */
            /* if we are at the far left node. */
            if( prt->IPAddr & prt->IPMask )
                Search = 1;

            /* Host only search */
            if( wCallFlags & FLG_RTF_HOST )
            {
                /* We never match gateway routes here - even if they are */
                /* "host" routes (host re-directs) */
                if( prt->Flags & FLG_RTE_GATEWAY )
                    goto RouteNotAccepted;

                /* If this is not a host route, if the CLONING flags is set, */
                /* we will still accept it if the route can clone into a */
                /* host route. */
                if( !(prt->Flags & FLG_RTE_HOST) )
                {
                    /* We will reject this route unless it is a viable clone */
                    /* route and the caller wants to clone. */
                    if( !(wCallFlags & FLG_RTF_CLONE) ||
                        !(prt->Flags & FLG_RTE_CLONING) )
                        goto RouteNotAccepted;
                }
                break;
            }

            /* Proxy only search */
            if( wCallFlags & FLG_RTF_PROXY )
            {
                if( !(prt->Flags & FLG_RTE_PROXY) )
                    goto RouteNotAccepted;
                break;
            }

            /* ProxyPub only search */
            if( wCallFlags & FLG_RTF_PROXYPUB )
            {
                if( !(prt->Flags & FLG_RTE_PROXYPUB) )
                    goto RouteNotAccepted;
                break;
            }

            /* This route is acceptable */
            break;

RouteNotAccepted:
            /* No match yet */
            prt = prt->pNext;
        }

        /* Reference the matched route (if any) */
        if( prt )
        {
            RtRef( prt );
            Search = 0;
        }
    }

    /* We no longer need the node */
    NodeDeRef( hNode );

    /* If we have a route, we may need to clone it */
    if( prt && (prt->Flags & FLG_RTE_CLONING) && (wCallFlags & FLG_RTF_CLONE) )
    {
        uint   NewFlags;

        /* Yep, we have to clone ... */

        /* Copy the flags */
        NewFlags = prt->Flags;

        /* Clear the flags that don't carry over */
        NewFlags &= ~(FLG_RTE_CLONING|FLG_RTE_STATIC|FLG_RTE_DYNAMIC);

        /* Make us a host */
        NewFlags |= FLG_RTE_HOST;

        if( !(prtClone = RtCreate( wCallFlags, NewFlags, IP, 0xffffffff,
                                   prt->hIF, prt->IPGate, 0 )) )
            DbgPrintf(DBG_WARN,"RtFind: Clone creation failed!");
        else
        {
            /* Mark as "keep-alive" route */
            prtClone->Flags |= FLG_RTE_KEEPALIVE;

            /* Set Default Timeout for Clone Node */
            RtSetTimeout( prtClone, ROUTE_CLONE_TIMEOUT );
        }

        /* DeRef the source node */
        RtDeRef( prt );

        /* We now use the clone node */
        prt = prtClone;
    }

    /* If we have no match, this is a "miss" */
    if( !prt )
    {
        /* Miss! Post a report if needed */
        if( wCallFlags & FLG_RTF_REPORT )
        {
            /* Send Routing Report */
            RTCReport( MSG_RTC_MISS, IP, 0xffffffff );
        }
    }

    /* NOTE: prt contains one of three things: */
    /*  1. NULL for a "miss" */
    /*  2. The referenced original route found */
    /*  3. The referenced clone route (original unreferenced above). */

    return( prt );
}

