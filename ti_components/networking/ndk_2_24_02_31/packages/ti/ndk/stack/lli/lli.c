/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
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
 * ======== lli.c ========
 *
 * Link Layer Handling routines
 *
 */

#include <stkmain.h>
#include "lli.h"

static LLI  *plliFirstExp  = 0;            /* Points to first LLI in Exp list */

/*-------------------------------------------------------------------- */
/* LLIMsg() */
/* Sevices Address Resolution */
/*-------------------------------------------------------------------- */
void LLIMsg( uint Msg )
{
    static HANDLE hTimer = 0;

    switch( Msg )
    {
    /* System Initialization */
    case MSG_EXEC_SYSTEM_INIT:
        /* Create a 1 second timer */
        hTimer = TimerNew( &LLIMsg, TIMER_TICKS_LLI, MSG_LLI_TIMER );
        break;

    /* System Shutdown */
    case MSG_EXEC_SYSTEM_SHUTDOWN:
        _LLITimeoutFlush();
        if( hTimer )
            TimerFree( hTimer );
        break;

    /* Low Resources */
    case MSG_EXEC_LOW_RESOURCES:
        _LLITimeoutFlush();
        break;

    /* One Second Timer */
    case MSG_LLI_TIMER:
        _LLITimeoutCheck();
        break;
    }

    return;
}

/*-------------------------------------------------------------------- */
/* LLINew() */
/* Create */
/*-------------------------------------------------------------------- */
HANDLE LLINew( HANDLE hRt, UINT8 *pMacAddr )
{
    LLI    *plli;

    /* Route is required */
    if( !hRt )
    {
        DbgPrintf(DBG_ERROR,"LLINew: No Route");
        return(0);
    }

    if( !(plli = mmAlloc(sizeof(LLI))) )
    {
        DbgPrintf(DBG_WARN,"LLINew: OOM");
        NotifyLowResource();
        return(0);
    }

    /* Most things are zero init */
    mmZeroInit( plli, sizeof(LLI) );

    /* Initialize type */
    plli->Type = HTYPE_LLI;

    /* Initialize non-zero parameters */
    plli->hRt  = hRt;

    /* Copy in the MacAddr if any */
    if( !pMacAddr )
        plli->Status = LLI_STATUS_IDLE;
    else
    {
        plli->Status = LLI_STATUS_VALID;
        mmCopy( plli->MacAddr, pMacAddr, 6 );
    }

    /* initialize the ARP packet queue */
    PBMQ_init(&(plli->ArpPktQ));

    return( (HANDLE)plli );
}

/*-------------------------------------------------------------------- */
/* LLIFree */
/* Destroy LLI */
/*-------------------------------------------------------------------- */
void LLIFree( HANDLE hLLI )
{
    LLI    *plli = (LLI *)hLLI;
    PBM_Pkt *pCurPkt = NULL;

#ifdef _STRONG_CHECKING
    if( plli->Type != HTYPE_LLI )
    {
        DbgPrintf(DBG_ERROR,"LLIFree: HTYPE %04x",plli->Type);
        return;
    }
#endif

    /* Kill type for debug */
    plli->Type = 0;

    /* Remove from exp list */
    _LLIExpListRemove( plli );

    /*
     * Fix for SDOCM00088612
     * de-queue all PBM packets waiting on this LLI and free them
     */
    /* Free any attached packet */
    while ((pCurPkt = PBMQ_deq(&(plli->ArpPktQ))) != NULL) {
        PBM_free(pCurPkt);
    }

    mmFree( plli );
}

/*-------------------------------------------------------------------- */
/* LLIGetValidTime() - Return the Valid Time of the LLI */
/* When an LLI is vailidated via ARP, it remains valid for a */
/* certain length of time. This function returns the expiration */
/* time of an LLI entry (0 for STATIC or invalid entries). */
/*-------------------------------------------------------------------- */
UINT32 LLIGetValidTime( HANDLE hLLI )
{
    UINT32 dwTimeNow;
    LLI    *plli = (LLI *)hLLI;

#ifdef _STRONG_CHECKING
    if( plli->Type != HTYPE_LLI )
    {
        DbgPrintf(DBG_ERROR,"LLIGetValidTime: HTYPE %04x",plli->Type);
        return(0);
    }
#endif

    /* Return NULL on an invalid LLI */
    if( plli->Status != LLI_STATUS_VALID )
        return(0);

    /* Get the current time. */
    dwTimeNow = llTimerGetTime(0);

    /* The Routing Entry is expiring and it has requested the LLI layer to check if
     * the entry can be deleted or not? Check if we need to execute the ARP Cache
     * Revalidation Logic. This can be done only on the following conditions
     *  - If the LLI entry has been used in the LAST LLI_INACTIVITY_TIMEOUT sec.
     *  If the condition is satisifed we move to the revalidation stage and send 
     *  out an ARP packet. In this state packets are transmitted as if the entry
     *  was valid. */
    if (dwTimeNow < (plli->LastUsed + LLI_INACTIVITY_TIMEOUT))
    {
        /* The LLI has moved into the revalidation stage.*/
        plli->Status = LLI_STATUS_REVALID1;

        /* Insert into timeout list */
        _LLIExpListInsert (plli, dwTimeNow + 1);

        /* Send out the ARP Request. */
        LLIGenArpPacket( RtGetIF(plli->hRt), RtGetIPAddr(plli->hRt) );

        /* Allow some time for the revalidation ARP reply to come; dont allow the routing
         * entry to time out immediately. This will now be handled in the next Routing Timer
         * Message i.e. after TIMER_TICKS_ROUTE ticks. */
        return (dwTimeNow + 1);
    }

    /* Return the valid time of the LLI */
    return( plli->Timeout );
}

/*-------------------------------------------------------------------- */
/* LLIGetMacAddr() - Return the MacAddr (if valid) of the LLI */
/* Checks the status of the LLI and returns MacAddr if valid */
/*-------------------------------------------------------------------- */
uint LLIGetMacAddr( HANDLE hLLI, UINT8 *pMacAddr, uint MaxLen )
{
    LLI    *plli = (LLI *)hLLI;

#ifdef _STRONG_CHECKING
    if( plli->Type != HTYPE_LLI )
    {
        DbgPrintf(DBG_ERROR,"LLIGetValidTime: HTYPE %04x",plli->Type);
        return(0);
    }
#endif

    /* Return NULL on an invalid LLI */
    if( plli->Status != LLI_STATUS_VALID || !pMacAddr || MaxLen<6 )
        return(0);

    /* Return the MacAddr */
    mmCopy( pMacAddr, plli->MacAddr, 6 );
    return( 1 );
}

/*-------------------------------------------------------------------- */
/* _LLIExpListInsert - Insert LLI into expiration list */
/*-------------------------------------------------------------------- */
void _LLIExpListInsert( LLI *plli, UINT32 Exp )
{
    LLI *plliTmp;

    if( !Exp )
        _LLIExpListRemove( plli );
    else
    {
        /* Remove the entry if its already in the list */
        if( plli->Timeout )
            _LLIExpListRemove( plli );

        /* Save the expiration */
        plli->Timeout = Exp;

        /* Now add the entry to the list */
        /* Check the easy case - being first */
        if( !plliFirstExp || plliFirstExp->Timeout >= Exp )
        {
            /* What we point to next */
            plli->pNextExp = plliFirstExp;
            /* Before us...pointing to us */
            plliFirstExp = plli;
        }
        else
        {
            /* Find an entry we expire AFTER */
            plliTmp = plliFirstExp;
            while( plliTmp->pNextExp &&
                   plliTmp->pNextExp->Timeout < Exp )
                plliTmp = plliTmp->pNextExp;

            /* What we point to next */
            plli->pNextExp = plliTmp->pNextExp;
            /* Before us...pointing to us */
            plliTmp->pNextExp = plli;
        }
    }
}

/*-------------------------------------------------------------------- */
/* _LLIExpListRemove - Remove LLI from expiration list */
/* Note: Normally, entries will be removed off the top of the list. */
/* However, if it is prematurely removed, it may be anywhere in the */
/* list. */
/*-------------------------------------------------------------------- */
void _LLIExpListRemove( LLI *plli )
{
    LLI *plliTmp;

    /* Clear the expiration time */
    plli->Timeout = 0;

    /* Check to see if we're the head of the list */
    if( plli == plliFirstExp )
        plliFirstExp = plli->pNextExp;
    else
    {
        /* Look for us */
        plliTmp = plliFirstExp;
        while( plliTmp && plliTmp->pNextExp != plli )
            plliTmp = plliTmp->pNextExp;

        /* Patch entry which points to us */
        if( plliTmp )
            plliTmp->pNextExp = plli->pNextExp;
    }
}

/*-------------------------------------------------------------------- */
/* LLITimeoutCheck - Check for Timed-out ARPs */
/*-------------------------------------------------------------------- */
void _LLITimeoutCheck()
{
    LLI     *plli;
    UINT32  TimeNow;
    PBM_Pkt *pCurPkt = NULL;

    /* The timeout list is pre-sorted by time. Continue timing out */
    /* ARPs until we find one that hasn't yet expired. */
    TimeNow = llTimerGetTime(0);
    do
    {
        /* Get an expired entry off the list */
        plli = plliFirstExp;
        if( plli && plli->Timeout <= TimeNow )
        {
            plliFirstExp = plli->pNextExp;
            /* Make sure route does't go away when during check */
            RtRef( plli->hRt );
        }
        else
            plli = 0;

        /* Process an expired entry */
        if( plli )
        {
            /* Clear the expiration time */
            plli->Timeout = 0;

            /* Timeout ARP */
            if( (plli->Status == LLI_STATUS_ARP5) || (plli->Status == LLI_STATUS_REVALID3))
            {
                /* ARP going down! Too many requests. */

                /* Back into timeout list */
                _LLIExpListInsert( plli, TimeNow + LLI_ARP_DOWN_TIME );

                /* Knock down the route */
                plli->Status = LLI_STATUS_DOWN;
                RtSetFailure( plli->hRt, FLG_RTF_REPORT, RTC_HOSTUNREACH );

                /*
                 * Fix for SDOCM00088612
                 * dequeue each packet and pass it back to IPTxPacket
                 */
                while ((pCurPkt = PBMQ_deq(&(plli->ArpPktQ))) != NULL) {
                    /* Return any waiting packet to IP */
                    /* Use the forwarding flag since to gen ICMP error */
                    IPTxPacket( pCurPkt, FLG_IPTX_FORWARDING );
                }
            }
            else if( plli->Status == LLI_STATUS_DOWN )
            {
                /* Downed ARP coming up for air */
                plli->Status = LLI_STATUS_IDLE;
                RtSetFailure( plli->hRt, FLG_RTF_REPORT, 0 );
            }

            /* ARP Retry if not "down" */
            if ((plli->Status >= LLI_STATUS_ARP0 && plli->Status < LLI_STATUS_ARP5) || 
                (plli->Status >= LLI_STATUS_REVALID1 && plli->Status <= LLI_STATUS_REVALID2))
            {
                /* When at first ARP doesn't succeed ... */
                plli->Status++;

                /* Insert into timeout list */
                _LLIExpListInsert( plli, TimeNow + 1 );

                /* Send ARP for this packet */
                LLIGenArpPacket( RtGetIF(plli->hRt), RtGetIPAddr(plli->hRt) );
            }
            /* Now we can DeRef the route */
            RtDeRef( plli->hRt );
        }
    } while( plli );
}

/*-------------------------------------------------------------------- */
/* LLITimeoutFlush - Dump all LLI's in the timeout list */
/*-------------------------------------------------------------------- */
void _LLITimeoutFlush()
{
    LLI    *plli;
    PBM_Pkt *pCurPkt = NULL;

    /* When a low resource condition or flush occurs, we'll free any */
    /* packet which is waiting at a pending LLI, and make the LLI "IDLE" */

    while( (plli = plliFirstExp) )
    {
        /* Get it out of the list */
        plliFirstExp = plli->pNextExp;

        /* Set status to IDLE */
        plli->Status = LLI_STATUS_IDLE;

        /*
         * Fix for SDOCM00088612
         * Free any waiting packet from ARP queue
         */
        while ((pCurPkt = PBMQ_deq(&(plli->ArpPktQ))) != NULL) {
            PBM_free(pCurPkt);
        }
    }
}

/** 
 *  @b Description
 *  @n  
 *      The function is used to add a static Route/LLI Entry for a given
 *      IP Address and MAC Address. If a Route/LLI entry already exists with 
 *      the same IP Address, it is updated with the new MAC Address specified
 *      here. 
 *
 *      This function is available to application developers and 
 *      can be called from outside kernel mode.
 *
 *  @param[in]  IPAddr
 *      The IPv4 Address of the destination device.
 *
 *  @param[in]  pMacAddr
 *      The 6 byte ethernet MAC address of the device corresponding to the 
 *      supplied IPv4 address.
 *
 *  @retval
 *      0      -   Success
 *  @retval
 *      -1     -   Error
 */
int LLIAddStaticEntry( IPN IPAddr, UINT8 *pMacAddr )
{
    HANDLE  hRt, hIFTx;
    LLI*    pLLI;

    /* Kernel is not re-entrant. Obtain lock to continue */
    llEnter();

    /* Validate input */

    /* Erroneous input if:
     * 1. No Mac Address specified.
     * 2. IP Address specified is either ANY / Broadcast / Multicast IP Address.
     * 3. IP Address specified is a local IP Address.
     */
    if( !pMacAddr || 
        (IPAddr == INADDR_ANY || IPAddr == INADDR_BROADCAST ||
        (IN_MULTICAST (IPAddr)) || (BindFindByHost(0,IPAddr)))
      )
    {
        /* Release kernel lock. */
        llExit();

        /* Invalid Input. Return error. */
        return -1;
    }


    /* Find the net/cloning route for this IP Address. Network/cloning route
     * for this network is available only if we have a local interface configured on
     * the same network. Otherwise, this API will return the default gateway if any
     * configured. If no cloning and gateway routes found matching this IP Address,
     * it results in an error condition. Since there is no point to configuring this
     * ARP entry if we cannot route packets to the destination IP Address specified, we 
     * throw an error.
     */
    hRt = IPGetRoute( 0, IPAddr );
    if( hRt )
    {
        /* Look up the interface to use to transmit packets to this 
         * IP/MAC Address destination.
         */
        hIFTx =  RtGetIF(hRt);
        RtDeRef( hRt );
    }
    else
    {
        /* No route found, cannot create a static route. */

        /* Release kernel lock. */
        llExit();

        /* Return error. */
        return -1;
    }

    /* Next, we check if there is already a route configured with
     * matching IP Address. If there exists a static / dynamic 
     * LLI entry with the same IP address, we update it. If no
     * matching route entry already exists, we create one.
     */
    hRt = RtFind( FLG_RTF_HOST, IPAddr );
    if( hRt )
    {
        /* Route already exists for this IP Address. Let's update it
         * if possible.
         */
        if( RtGetFlags(hRt) & FLG_RTE_STATIC  )
    
        {
            /* Static LLI/Route Entry. Just update the MAC Address and 
             * Return.
             */
            /* Get the LLI to update */
            pLLI = (LLI *)RtGetLLI( hRt );

            if( pLLI )
            {
                /* Update the MAcAddr */
                mmCopy( pLLI->MacAddr, pMacAddr, 6 );

                /* Update the LLI Status */
                pLLI->Status = LLI_STATUS_VALID;
            }

            /* Release kernel lock. */
            llExit();

            /* Done updating. Return Success. */
            return 0;
        }
        else
        {
            /* Dynamic LLI/Route Entry. Need to delete this entry and create a 
             * new static entry, since Static entries always override 
             * dynamic entries.
             */
            RtRemove( hRt, FLG_RTF_REPORT, RTC_HOSTUNREACH );    

           /* Fall through to create a new static LLI/route entry. */
        }
    }
   
    if( 1 )
    {
        /* Now create the Host, Static route matching this ARP entry. */
        hRt = RtCreate( FLG_RTF_REPORT, FLG_RTE_HOST|FLG_RTE_STATIC,
                        IPAddr, 0xffffffff, hIFTx, 0, pMacAddr );
        if( hRt )
        {
            /* Successfully created the static route/LLI entry. Deref it 
             * and return.
             */
            RtDeRef( hRt );

            /* Release kernel lock. */
            llExit();

            /* Return success. */
            return 0;
        }
        else
        {
            /* Error in creating the new route/LLI entry. */

            /* Release kernel lock. */
            llExit();

            /* Return error. */
            return -1;
        }
    }
}

/** 
 *  @b Description
 *  @n  
 *      The function is used to delete a previously configured static Route/
 *      LLI entry based on the IPv4 address specified.
 *
 *      This function is available to application developers and 
 *      can be called from outside kernel mode.
 *
 *  @param[in]  IPAddr
 *      The IPv4 Address of the destination device.
 *
 *  @retval
 *      0      -   Success
 *  @retval
 *      -1     -   Error
 */
int LLIRemoveStaticEntry( IPN IPAddr )
{
    HANDLE  hRt;

    /* Kernel is not re-entrant. Obtain lock to continue */
    llEnter();

    /* Check to see if we have any routes / LLI entries
     * associated with the IP - MAC Address Pairing
     * specified. 
     */
    if( (hRt = RtFind( FLG_RTF_HOST|FLG_RTE_STATIC, IPAddr )) )
    {
        /* We have a match - remove the route and associated
         * LLI entry now.
         */
        RtRemove( hRt, FLG_RTF_REPORT, RTC_HOSTUNREACH );
        RtDeRef( hRt );

        /* Release kernel lock. */
        llExit();

        /* Return Success. */
        return 0;
    } 
    
    /* Release kernel lock. */
    llExit();

    /* Couldn't find any matching entry with parameters specified.
     * Return error.
     */
    return -1;
}

/** 
 *  @b Description
 *  @n  
 *      This API can be used to retrieve the number of static
 *      ARP entries and a replicated list of such entries configured in the
 *      system. This API traverses through the route and LLI (ARP) table 
 *      configured in NDK, finds any static routes/LLI entries configured,
 *      and creates a copy of them and returns them as a linked list of LLI_INFO
 *      structures for the requesting application to use.
 *
 *      This function is available to application developers and 
 *      can be called from outside kernel mode.
 *
 *  @sa
 *      LLIFreeStaticARPTable
 *
 *  @param[out]  pNumEntries
 *      Pointer to hold the number of static ARP entries in the system.
 *
 *  @param[out]  pStaticArpTable
 *      Pointer to hold the replicated static ARP entry table returned by this 
 *      API.
 *
 *  @retval
 *      Not Applicable.
 */
void LLIGetStaticARPTable( UINT32* pNumEntries, LLI_INFO** pStaticArpTable )
{
    HANDLE      hRt;
    LLI_INFO*   pNewLLINode;
	IPN			IPAddr;
	UINT8		MacAddr[6];
	HANDLE		hLLI;
	UINT32		wFlags, Count = 0;

    /* Kernel is not re-entrant. Obtain lock to continue */
    llEnter();

    /* Start the Route Tree Traversal. This disables the Routing table
     * timers, enabling us to get a good stable snapshot of the routing
     * table.
     */
    hRt = RtWalkBegin();

    /* No Routes/Static LLI Entries configured so far? */
    if( !hRt )
    {
        *pNumEntries = 0;
        *pStaticArpTable = NULL;

        /* Release kernel lock. */
        llExit();

        return;
    }

    /* Valid Routes exist. Inspect the routes to see if it is a
     * static entry, if so do the needful, otherwise continue 
     * traversing the tree to find the next one.
     */
    while( hRt )
    {
        /* Get the IP addess and flags of the route */
        IPAddr = RtGetIPAddr( hRt );
        wFlags = RtGetFlags( hRt );

        /* Check if this is a Static Host Route */
        if( (wFlags & FLG_RTE_HOST) && (wFlags & FLG_RTE_STATIC))
        {
            /* Check if a valid MAC address configured on this route?
             * The stack has a MAC address if it has an LLI (link-layer info)
             * object, and LLIGetMacAddr returns 1.
             */
            if( !(hLLI = RtGetLLI( hRt )) || !LLIGetMacAddr( hLLI, MacAddr, 6 ) )
            {
                /* No LLI/ARP entry associated with this route yet? 
                 * This is an erroneus condition and shouldnt happen.
                 * we just skip over this entry and continue onto
                 * the next route.
                 */
                continue;
            }
            else
            {
                /* Route has a valid static LLI entry configured. 
                 * Make a copy of it and append it to the list for 
                 * the application to use later. Also update the number of
                 * static ARP entries found.
                 */
                if( !(pNewLLINode = (LLI_INFO *)mmAlloc( sizeof( LLI_INFO ) )) )
                {
                    /* Memory alloction error. Return since we cant proceed
                     * any further. Clean the list populated so far.
                     */
                    *pNumEntries = 0;

                    if( *pStaticArpTable )
                    {
                        list_clean( (LIST_NODE *)*pStaticArpTable, mmFree );
                    }
        
                    /* Release kernel lock. */
                    llExit();

                    return;
                }
                else
                {
                    mmZeroInit( pNewLLINode, sizeof( LLI_INFO ) );

                    /* Populate the newly allocate static LLI info node with
                     * the IP Address, MAC Address and appropriate flags.
                     */
                    pNewLLINode->IPAddr = IPAddr;
                    mmCopy( pNewLLINode->MacAddr, MacAddr, sizeof( UINT8 ) * 6 );
                    pNewLLINode->IsStatic = 1;

                    /* Add this entry to the Static ARP Table list sent by the application. */
                    list_add( (LIST_NODE **)pStaticArpTable, (LIST_NODE *)pNewLLINode );

                    /* Increment the number of valid static ARP entries found. */
					Count ++;
                }
            }
        }

        /* Get the next available route in the tree */
        hRt = RtWalkNext( hRt );
    }

    /* End the route tree traversal. This enables back the routing table 
     * timers we had disabled using "RtWalkBegin". We are done traversing
     * the route tree, we should enable the timers so that routing table
     * can continue its usual state machine to maintain dynamic routes.
     */
    RtWalkEnd( 0 );

	*pNumEntries = Count;

    /* Release kernel lock. */
    llExit();

    return;
}

/**
 *  @b Description
 *  @n  
 *      This function is called to clean the memory allocated by a previous
 *      call to LLIGetStaticARPTable. This function cleans the replicated copy 
 *      of the static ARP table.
 *
 *      This function is available to application developers and 
 *      can be called from outside kernel mode.
 *
 *  @sa
 *      LLIGetStaticARPTable
 *
 *  @param[in]  pStaticArpTable
 *      This is the head of the duplicated static ARP table list 
 *      which has to be cleaned up.
 *
 *  @retval
 *      Not Applicable
 */
void LLIFreeStaticARPTable (LLI_INFO* pStaticArpTable)
{
    /* Kernel is not re-entrant. Obtain lock to continue */
    llEnter();

    /* Cleanup the ARP list. */
    list_clean( (LIST_NODE*)pStaticArpTable, mmFree );

    /* Release kernel lock. */
    llExit();

    return;
}
