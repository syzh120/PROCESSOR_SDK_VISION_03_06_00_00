/*
 * Copyright (c) 2013-2014, Texas Instruments Incorporated
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
 * ======== lli6.c ========
 *
 * The file implements the LLI6 Module which is responsible
 * for keeping track of the Neighbor Cache entries and the
 * Neighbor Unreachability Algorithm as specified in RFC 2461
 *
 */

#include <stkmain.h>

#ifdef _INCLUDE_IPv6_CODE

/**********************************************************************
 *************************** Local Definitions ************************
 **********************************************************************/

/* Unique Message: This is used to keep track of the internal LLI6 TIMER */
#define MSG_LLIV6_TIMER            (ID_LLIV6*MSG_BLOCK + 1)

/**********************************************************************
 *************************** Global Variables *************************
 **********************************************************************/

/* This is the GLOBAL LLI6 Timer which is a fast timer executed to implement
 * the Neighbor Unreachability Detection Algorithm. */
static HANDLE hLLI6Timer;

/* This is the GLOBAL LLI6 Entry List which keeps track of all the LLI6 entries
 * which exist in the System. */
static LLI6_ENTRY* gLLI6EntryList = NULL;

/**********************************************************************
 *************************** LLI6 Functions ***************************
 **********************************************************************/

/** 
 *  @b Description
 *  @n  
 *      The function is used to get the LLIv6 handle matching the MAC
 *      address. 
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  mac_address
 *      The MAC Address for which we are trying to locate the LLI6 Entry.
 *  @param[in]  ptr_device
 *      The device on which the LLI6 Entry should exist. This can be NULL
 *      If NULL then the search will cycle through all LLI6 Entries which
 *      exist in the System.
 *
 *  @retval
 *   Handle to the corresponding LLI6 Entry  -   Success
 *  @retval
 *   0                                       -   Error
 */
static HANDLE LLI6Find (UINT8* mac_address, NETIF_DEVICE* ptr_device)
{
    LLI6_ENTRY* ptr_lli6;

    /* Validate the arguments. */
    if (mac_address == NULL)
        return 0;

    /* Cycle through the LLI6 List. */
    ptr_lli6 = (LLI6_ENTRY *)list_get_head ((LIST_NODE**)&gLLI6EntryList);
    while (ptr_lli6 != NULL)
    {
        /* Match the MAC Address */
        if((*(mac_address)     == ptr_lli6->MacAddr[0]) && (*(mac_address + 1) == ptr_lli6->MacAddr[1]) &&
           (*(mac_address + 2) == ptr_lli6->MacAddr[2]) && (*(mac_address + 3) == ptr_lli6->MacAddr[3]) &&
           (*(mac_address + 4) == ptr_lli6->MacAddr[4]) && (*(mac_address + 5) == ptr_lli6->MacAddr[5]))
        {
            /* Check if the Network Device entry was specified. 
             * If not then we return the HANDLE to the LLI6 Entry. */
            if (ptr_device == NULL)
                return (HANDLE)ptr_lli6;

            /* Check if this matches the LLI6 Entry we are */
            if (ptr_device == ptr_lli6->ptr_device)
                return (HANDLE)ptr_lli6;

            /* There is NO Match */
            return 0;
        }

        /* Get the next LLI6 Entry. */
        ptr_lli6 = (LLI6_ENTRY *)list_get_next ((LIST_NODE*)ptr_lli6);
    }

    /* Control comes here implies that there is no match. */
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function implements the IsRouter State Machine. The RFC
 *      states that if an LLI entry moves from the IsRouter state to
 *      HOST Mode; then the corresponding Routing Entries need to be
 *      deleted too.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_lliv6
 *      LLI6 Entry on which the IsRouter State Machine is executed.
 *  @param[in]  RxPktType
 *      The Received ICMPv6 NDISC Packet Type.
 *  @param[in]  IsMacDifferent
 *      Flag set to 1 if the MAC Addresses are different else 0.
 *  @param[in]  IsMacDifferent
 *      Flags which are the from the NA; else 0.
 *
 *  @retval
 *   Not Applicable.
 */
static void LLI6IsRouterStatMachine (LLI6_ENTRY* ptr_lliv6, UINT32 RxPktType, UINT8 IsMacDifferent, UINT32 Flags)
{
    UINT8 newIsRouterFlag = 0;

    /* If we received a RA; then set the IsRouter field to 1 as specified by
     * RFC 2461 Section 6.3.4 */
    if (RxPktType == ICMPV6_ROUTER_ADVERTISMENT)
        ptr_lliv6->IsRouter = 1;

    /* All other manipulations are done if we received a Neighbor Advertisment; all other packet types
     * do not carry any information about the ROUTER State. */
    if (RxPktType == ICMPV6_NEIGH_ADVERTISMENT)
    {
        /* Check if the MAC Addresses were different. */
        if (IsMacDifferent == 0)
        {
            /* No. The MAC Addresses were the same. In this case we use the (R) Flag to determine
             * the new Router Status. */
            if (Flags & ICMPV6_NA_R_FLAG)
            {
                /* The (R) Flag was set in the NA; so we set the IsRouterFlag. */
                newIsRouterFlag = 1;
            }
            else
            {
                /* The (R) Flag was NOT set in the NA; */
                newIsRouterFlag = 0;
            }
        }
        else
        {
            /* MAC Address was different. In this case we will check the (O) Flag to determine
             * the new Router Status. */
            if (Flags & ICMPV6_NA_O_FLAG)
            {
                /* The (O) Flag was set in the NA; so we set the IsRouterFlag depending on the
                 * (R) Flag. */
                if (Flags & ICMPV6_NA_R_FLAG)
                {
                    /* The (R) Flag was set in the NA; so we set the IsRouterFlag. */
                    newIsRouterFlag = 1;
                }
                else
                {
                    /* The (R) Flag was NOT set in the NA; */
                    newIsRouterFlag = 0;
                }
            }
            else
            {
                /* The (O) FLAG was not set; in this case there is no reason to execute the IsRouter
                 * State Machine. */
                return;
            }
        }

        /* Update the IsRouter Status. Check if we are moving from ROUTER to HOST Mode. 
         * If so be the case then this ROUTING Entry is NO Longer useful and should NOT
         * be used. */
        if ((ptr_lliv6->IsRouter == 1) && (newIsRouterFlag == 0))
        {
            /* We move the LLI6 Entry to HOST Mode and then to the DEAD State; 
             * it will be cleaned up by the ROUTING Timers. */
            ptr_lliv6->IsRouter = newIsRouterFlag;
            ptr_lliv6->status   = ICMPV6_LLI_DEAD;
        }
        else
        {
            /* Set the status of the new LLI6 Entry. */
            ptr_lliv6->IsRouter = newIsRouterFlag;
        }
    }
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function implements the Neighbor Unreachability Detection 
 *      State Machine. 
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_lli6
 *      LLI6 Entry on which the IsRouter State Machine is executed.
 *  @param[in]  RxPktType
 *      The Received ICMPv6 NDISC Packet Type.
 *  @param[in]  mac_address
 *      The MAC Address.
 *  @param[in]  IsMacAddressDifferent
 *      Flag set to 1 if the MAC Addresses are different else 0.
 *  @param[in]  Flags
 *      Flags which are the from the NA; else 0.
 *
 *  @retval
 *   Not Applicable.
 */
static void LLI6NeighUnreachStateMachine
(
    LLI6_ENTRY* ptr_lli6, 
    UINT32      RxPktType,
    UINT8*      mac_address,
    UINT8       IsMacAddressDifferent, 
    UINT32      Flags
)
{
    PBM_Pkt*    pPkt;

    /*******************************************************************
     * Execute the Neighbor Unreachability Detection State Machine
     *  This is as documented in RFC 2461 Appendix C.
     *******************************************************************/
    if (ptr_lli6->status == ICMPV6_LLI_INCOMPLETE)
    {
        /* If we were in the INCOMPLETE state and we received a NDISC Packet with no MAC
         * Address; then we will remain in the INCOMPLETE state and cannot proceed further. */
        if (mac_address == NULL)
            return;

        /* Move forward to the next stage. */
        if ((RxPktType == ICMPV6_ROUTER_SOLICITATION) || (RxPktType == ICMPV6_ROUTER_ADVERTISMENT) ||
            (RxPktType == ICMPV6_NEIGH_SOLICIT) || (RxPktType == ICMPV6_REDIRECT))
        {
            ptr_lli6->status = ICMPV6_LLI_STALE;
#ifdef LLI6_DEBUG
            DbgPrintf(DBG_INFO, "LLI6NeighUnreachStateMachine: DEBUG: LLI6: 0x%p INCOMPLETE --> STALE\n",
                    ptr_lli6);
#endif
        }

        /* If we received a NA and the (S) Flag was SET; then we move into the REACHABLE state. */
        if ((RxPktType == ICMPV6_NEIGH_ADVERTISMENT) && (Flags & ICMPV6_NA_S_FLAG))
        {
            /* We moved into the REACHABLE Stage; remember when this happened! */
            ptr_lli6->status      = ICMPV6_LLI_REACHABLE;
            ptr_lli6->LastReachTS = llTimerGetTime (0);
#ifdef LLI6_DEBUG
            DbgPrintf(DBG_INFO, "LLI6NeighUnreachStateMachine: DEBUG: LLI6: 0x%p INCOMPLETE --> REACHABLE\n",
                    ptr_lli6);
#endif
        }

        /* If we received a NA and the (S) Flag was NOT SET; then we move into the STALE state. */
        if ((RxPktType == ICMPV6_NEIGH_ADVERTISMENT) && !(Flags & ICMPV6_NA_S_FLAG))
        {
            ptr_lli6->status = ICMPV6_LLI_STALE;
#ifdef LLI6_DEBUG
            DbgPrintf(DBG_INFO, "LLI6NeighUnreachStateMachine: DEBUG: LLI6: 0x%p INCOMPLETE --> STALE\n",
                    ptr_lli6);
#endif
        }

        /* Update the MAC Address with the new information */
        mmCopy ((void *)&ptr_lli6->MacAddr[0], (void *)mac_address, 6);

        /* Check if there are any more packets pending in the queue and if so send them out. */
        pPkt = ptr_lli6->pPkt;
        ptr_lli6->pPkt = 0;
        if(pPkt)
            LLI6TxIPPacket (pPkt, ptr_lli6, ptr_lli6->ptr_device, ptr_lli6->TargetAddr);

        return;
    }

    /* Control comes here implies that the status of the Neighbor Entry is NOT INCOMPLETE. */

    /* If we received a NA with Solicted Flag set and Override flag NOT set and 
     * there was no MAC Address changes; move to REACHABLE */
    if ((RxPktType == ICMPV6_NEIGH_ADVERTISMENT) && !(Flags & ICMPV6_NA_O_FLAG) && 
        (Flags & ICMPV6_NA_S_FLAG) && (IsMacAddressDifferent == 0))
    {
        /* We moved into the REACHABLE Stage; remember when this happened! */
        ptr_lli6->status      = ICMPV6_LLI_REACHABLE;
        ptr_lli6->LastReachTS = llTimerGetTime (0);
#ifdef LLI6_DEBUG
        DbgPrintf(DBG_INFO, "LLI6NeighUnreachStateMachine: DEBUG: LLI6: 0x%p REACHABLE\n", ptr_lli6);
#endif
        return;
    }

    /* If we received a NA with Solicted Flag set and Override flag NOT set and there was 
     * a MAC Address change; move to STALE */
    if ((ptr_lli6->status == ICMPV6_LLI_REACHABLE) && (RxPktType == ICMPV6_NEIGH_ADVERTISMENT) &&
        !(Flags & ICMPV6_NA_O_FLAG) && (Flags & ICMPV6_NA_S_FLAG) && (IsMacAddressDifferent == 1))
    {
        ptr_lli6->status = ICMPV6_LLI_STALE;
#ifdef LLI6_DEBUG
        DbgPrintf(DBG_INFO, "LLI6NeighUnreachStateMachine: DEBUG: LLI6: 0x%p STALE\n", ptr_lli6);
#endif
        return;
    }

    /* If we received a NA with Solicted Flag set and Override flag set; move to REACHABLE and 
     * update with the new MAC Address. */
    if ((RxPktType == ICMPV6_NEIGH_ADVERTISMENT) && (Flags & ICMPV6_NA_O_FLAG) && (Flags & ICMPV6_NA_S_FLAG))
    {
        /* We moved into the REACHABLE Stage; remember when this happened! */
        ptr_lli6->status      = ICMPV6_LLI_REACHABLE;
        ptr_lli6->LastReachTS = llTimerGetTime (0);

#ifdef LLI6_DEBUG
        DbgPrintf(DBG_INFO, "LLI6NeighUnreachStateMachine: DEBUG: LLI6: 0x%p REACHABLE\n", ptr_lli6);
#endif
        /* Update only if the MAC Address is specified. */
        if (mac_address != NULL)
            mmCopy ((void *)&ptr_lli6->MacAddr[0], (void *)mac_address, 6);
        return;
    }

    /* If we received a NA with Solicted Flag set and Override flag set; move to STALE and 
     * update with the new MAC Address. */
    if ((RxPktType == ICMPV6_NEIGH_ADVERTISMENT) && (Flags & ICMPV6_NA_O_FLAG) && 
        !(Flags & ICMPV6_NA_S_FLAG) && (IsMacAddressDifferent == 1))
    {
        ptr_lli6->status = ICMPV6_LLI_STALE;

#ifdef LLI6_DEBUG
        DbgPrintf(DBG_INFO, "LLI6NeighUnreachStateMachine: DEBUG: LLI6: 0x%p STALE\n", ptr_lli6);
#endif

        /* Update only if the MAC Address is specified. */
        if (mac_address != NULL)
            mmCopy ((void *)&ptr_lli6->MacAddr[0], (void *)mac_address, 6);
        return;
    }

    /* If we received a NA with Solicited and Override flags both RESET and the 
     * MAC Addresses are different; we dont overwrite with the new MAC address
     * But we place the Neighbor entry in STALE state */
    if ((RxPktType == ICMPV6_NEIGH_ADVERTISMENT) && !(Flags & ICMPV6_NA_O_FLAG) && 
        !(Flags & ICMPV6_NA_S_FLAG) && (IsMacAddressDifferent == 1))
    {
        ptr_lli6->status = ICMPV6_LLI_STALE;
#ifdef LLI6_DEBUG
        DbgPrintf(DBG_INFO, "LLI6NeighUnreachStateMachine: DEBUG: LLI6: 0x%p STALE\n", ptr_lli6);
#endif
        return;
    }

    /* If we received a RS, RA, NS or Redirect move to STALE and update with the new MAC Address. */
    if ((RxPktType != ICMPV6_NEIGH_ADVERTISMENT) && (IsMacAddressDifferent == 1))
    {
        ptr_lli6->status = ICMPV6_LLI_STALE;

#ifdef LLI6_DEBUG
        DbgPrintf(DBG_INFO, "LLI6NeighUnreachStateMachine: DEBUG: LLI6: 0x%p STALE\n", ptr_lli6);
#endif
        /* Update only if the MAC Address is specified. */
        if (mac_address != NULL)
            mmCopy ((void *)&ptr_lli6->MacAddr[0], (void *)mac_address, 6);
        return;
    }
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function is used to update the LLI6 Entry. This is called whenever
 *      one of the Neighbour Discovery packets are received:-
 *          a) NS
 *          b) NA
 *          c) RS
 *          d) RA
 *          e) Redirect.
 *      The function executes the Neighbor Unreachability Detection 
 *      and Is Router State Machine.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  hLLI6
 *      Handle to the LLI6 Entry being updated.
 *  @param[in]  mac_address
 *      MAC Address which needs to be updated. This can be NULL in which
 *      case only the IsRouterStateMachine is executed; the Neighbor 
 *      Unreachability State Machine is bypassed.
 *
 *  @param[in]  RxPktType
 *      The packet type received which has triggered a call to this function.
 *  @param[in]  Flags
 *      The flags field in the NA Header received. 0 for all other packets.
 *
 *  @retval
 *   Not Applicable.
 */
void LLI6Update (HANDLE hLLI6, UINT8* mac_address, UINT32 RxPktType, UINT32 Flags)
{
    LLI6_ENTRY* ptr_lliv6;
    UINT8       IsMacAddressDifferent = 0;

    /* Get the LLI6 Object. */
    ptr_lliv6 = (LLI6_ENTRY *)hLLI6;

    /* Check if the MAC Address is specified. */
    if (mac_address != NULL)
    {
        /* The MAC Address is specified; check if it is different than the existing MAC Address */
        if((*(mac_address)     != ptr_lliv6->MacAddr[0]) || (*(mac_address + 1) != ptr_lliv6->MacAddr[1]) ||
           (*(mac_address + 2) != ptr_lliv6->MacAddr[2]) || (*(mac_address + 3) != ptr_lliv6->MacAddr[3]) ||
           (*(mac_address + 4) != ptr_lliv6->MacAddr[4]) || (*(mac_address + 5) != ptr_lliv6->MacAddr[5]))
        {
            /* MAC Address are different. */
            IsMacAddressDifferent = 1;
        }
    }

    /* Execute the NEIGHBOR Unreachability Detection */
    LLI6NeighUnreachStateMachine (ptr_lliv6, RxPktType, mac_address, IsMacAddressDifferent, Flags);
    
    /* Always execute the IsRouterState Machine.*/
    LLI6IsRouterStatMachine (ptr_lliv6, RxPktType, IsMacAddressDifferent, Flags);
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function cycles through all the LLI Entries which exist in the
 *      System and modifies their state as per the Neighbor Cache Algorithm.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @retval
 *      Not Applicable.
 */
static void LLI6TimerCheck (void)
{
    LLI6_ENTRY*      ptr_lli6;
    IP6N             SrcAddress;
    UINT32           CurrentTime;

    /* Get the LLI6 Entry from the list. */
    ptr_lli6 = (LLI6_ENTRY *)list_get_head ((LIST_NODE**)&gLLI6EntryList);
    while (ptr_lli6 != NULL)
    {
        /* Get the current time in the System. */
        CurrentTime = llTimerGetTime(0);

        /* Proceed with the Neighbor State Machine */
        switch (ptr_lli6->status)
        {
            case ICMPV6_LLI_INCOMPLETE:
            {
                /* Can we send out more probes on this entry? */
                if (ptr_lli6->NumProbes < IPV6_MAX_MULTICAST_SOLICIT)
                {
                    /* YES we can and has there been sufficient time between the probes. 
                     * We use the value from the IPv6 Device Record; since this can be modified by RA. */
                    if (CurrentTime >= (ptr_lli6->LastSendNS + ptr_lli6->ptr_device->ptr_ipv6device->RetransTimer))
                    {
                        IP6N DstAddress;
                        IP6N SrcAddress;

                        /* Make the Solicited Node Multicast Address */
                        DstAddress.u.addr32[0] = htonl (0xFF020000);
                        DstAddress.u.addr32[1] = 0;
                        DstAddress.u.addr32[2] = htonl (0x1);
                       
                        DstAddress.u.addr32[3] = ntohl(ptr_lli6->TargetAddr.u.addr32[3]);
                        DstAddress.u.addr32[3] = 0xFF000000 | DstAddress.u.addr32[3];
                        DstAddress.u.addr32[3] = htonl(DstAddress.u.addr32[3]);
        

                        /* RFC 2461: Section 7.2.2 states that If the source address of the 
                         * packet prompting the solicitation is the same as one of the addresses 
                         * assigned to the outgoing interface, that address SHOULD be placed in 
                         * the IP Source Address of the outgoing solicitation. Otherwise, any one 
                         * of the addresses assigned to the interface should be used. */
                        if (IPv6CompareAddress(ptr_lli6->SrcAddr, IPV6_UNSPECIFIED_ADDRESS))
                        {
                            /* We dont know the Source Address prompting the Solicitation; use one of the
                             * addresses of the interface. */
                            SrcAddress = Bind6IF2IPHost (ptr_lli6->ptr_device);
                            if (IPv6CompareAddress (SrcAddress, IPV6_UNSPECIFIED_ADDRESS) == 1)
                                DbgPrintf (DBG_ERROR, "LLI6TimerCheck: FATAL Error: Device does not have any IPv6 Address\n");
                        }
                        else
                        {
                            /* Use the Source Address prompting the solicitation. */
                            SrcAddress = ptr_lli6->SrcAddr;
                        }

#ifdef LLI6_DEBUG                        
                        DbgPrintf(DBG_INFO, "LLI6TimerCheck: DEBUG: Sending out NS in INCOMPLETE LLI6: 0x%p\n", ptr_lli6);
#endif

                        /* Send out the NS Request. */
                        ICMPv6SendNS (ptr_lli6->ptr_device, DstAddress, SrcAddress, ptr_lli6->TargetAddr);

                        /* Remember the time when the NS was sent. */
                        ptr_lli6->LastSendNS = CurrentTime;

                        /* Increment the number of probes. */
                        ptr_lli6->NumProbes++;
                    }
                }
                else
                {
                    /* We have exceeded all the retransmissions; this entry is no longer valid. 
                     * We need to delete both the LLI6 and Route6 Entries. */
                    ptr_lli6->status = ICMPV6_LLI_DEAD;
#ifdef LLI6_DEBUG
                    DbgPrintf(DBG_INFO, "LLI6TimerCheck: DEBUG: 0x%p INCOMPLETE --> DEAD\n", ptr_lli6);
#endif
                }
                break;
            }
            case ICMPV6_LLI_REACHABLE:
            {
                /* The LLI Entry was reachable; check if there has been a timeout
                 * of more than Reachable time since last positive confirmation and if so we 
                 * move the LLI Status to STALE. */
                if (CurrentTime > (ptr_lli6->LastReachTS + ptr_lli6->ptr_device->ptr_ipv6device->ReachableTime))
                {
                    ptr_lli6->status = ICMPV6_LLI_STALE;

                    /* Initialize the rest of the state parameters too. */
                    ptr_lli6->NumProbes   = 0;
                    ptr_lli6->LastSendNS  = 0;
                    ptr_lli6->LastReachTS = 0;

#ifdef LLI6_DEBUG
                    DbgPrintf(DBG_INFO, "LLI6TimerCheck: DEBUG: 0x%p REACHABLE --> STALE\n", ptr_lli6);
#endif
                }
                break;
            }
            case ICMPV6_LLI_STALE:
            {
                /* In the stale state there is no action taken until a packet is sent. */
                break;
            }
            case ICMPV6_LLI_DELAY:
            {
                /* Check if the entry has been in this state; for the last IPV6_DELAY_FIRST_PROBE_TIME 
                 * seconds and if so we move the state to PROBE */
                if (CurrentTime >= (ptr_lli6->LastReachTS + IPV6_DELAY_FIRST_PROBE_TIME))
                {
                    /* Change the status of the LLI6 entry to PROBE */
                    ptr_lli6->status = ICMPV6_LLI_PROBE;

                    /* Initialize the rest of the state parameters too. */
                    ptr_lli6->NumProbes   = 0;
                    ptr_lli6->LastSendNS  = 0;
                    ptr_lli6->LastReachTS = 0;

#ifdef LLI6_DEBUG
                    DbgPrintf(DBG_INFO, "LLI6TimerCheck: DEBUG: 0x%p DELAY --> PROBE\n",
                            ptr_lli6);
#endif                    
                }
                break;
            }            
            case ICMPV6_LLI_PROBE:
            {
                /* Can we send out more probes on this entry? */
                if (ptr_lli6->NumProbes < IPV6_MAX_UNICAST_SOLICIT)
                {
                    /* YES we can and has there been sufficient time between the probes. 
                     * We use the value from the IPv6 Device Records; since this can be modified by RA. */
                    if (CurrentTime >= (ptr_lli6->LastSendNS + ptr_lli6->ptr_device->ptr_ipv6device->RetransTimer))
                    {
                        /* RFC 2461: Section 7.2.2 states that If the source address of the 
                         * packet prompting the solicitation is the same as one of the addresses 
                         * assigned to the outgoing interface, that address SHOULD be placed in 
                         * the IP Source Address of the outgoing solicitation. Otherwise, any one 
                         * of the addresses assigned to the interface should be used. */
                        if (IPv6CompareAddress(ptr_lli6->SrcAddr, IPV6_UNSPECIFIED_ADDRESS))
                        {
                            /* We dont know the Source Address prompting the Solicitation; use one of the
                             * addresses of the interface. */
                            SrcAddress = Bind6IF2IPHost (ptr_lli6->ptr_device);
                            if (IPv6CompareAddress (SrcAddress, IPV6_UNSPECIFIED_ADDRESS) == 1)
                                DbgPrintf (DBG_ERROR, "LLI6TimerCheck: FATAL Error: Device does not have any IPv6 Address\n");
                        }
                        else
                        {
                            /* Use the Source Address prompting the solicitation. */
                            SrcAddress = ptr_lli6->SrcAddr;
                        }
#ifdef LLI6_DEBUG
                        DbgPrintf(DBG_INFO, "LLI6TimerCheck: DEBUG: Sending out DIRECTED NS in PROBE LLI6: 0x%p\n", ptr_lli6);
#endif
                        /* In the PROBE state; we send out a DIRECTED NS to the TARGET Address. */
                        ICMPv6SendNS (ptr_lli6->ptr_device, ptr_lli6->TargetAddr, SrcAddress, ptr_lli6->TargetAddr);

                        /* Remember the time when the NS was sent. */
                        ptr_lli6->LastSendNS = CurrentTime;

                        /* Increment the number of probes. */
                        ptr_lli6->NumProbes++;
                    }
                }
                else
                {
                    /* We have exceeded all the retransmissions; this entry is no longer valid. 
                     * Remove the route this in turn will also delete the corresponding LLI6 Entry. */
                    ptr_lli6->status = ICMPV6_LLI_DEAD;
#ifdef LLI6_DEBUG
                    DbgPrintf(DBG_INFO, "LLI6TimerCheck: DEBUG: 0x%p PROBE --> DEAD\n",
                            ptr_lli6);
#endif
                }
                break;
            }
        }

        /* Get the next entry from the list. */
        ptr_lli6 = (LLI6_ENTRY *)list_get_next ((LIST_NODE*)ptr_lli6);
    }

    /* Work is done. */
    return;
}

/**
 *  @b Description
 *  @n  
 *      Sevices intialization and resource messages for the LLI6 Module.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  Msg
 *      The message event which needs to be handled.
 *
 *  @retval
 *      Not Applicable.
 */
void LLI6Msg (uint Msg)
{
    switch( Msg )
    {
        /* System Initialization */
        case MSG_EXEC_SYSTEM_INIT:
        {
            /* Create the LLI6 Timer as soon as the module is initialized. */
            hLLI6Timer = TimerNew( &LLI6Msg, TIMER_TICKS_LLI, MSG_LLIV6_TIMER );
            break;
        }
        /* System Shutdown */
        case MSG_EXEC_SYSTEM_SHUTDOWN:
        {
            /* System is shutting down. */
            if (hLLI6Timer)
            {
                /* Close the LLI6 Timer. */
                TimerFree (hLLI6Timer);
                hLLI6Timer = 0;
            }
            break;
        }
        /* LLI6 Second Timer Tick */
        case MSG_LLIV6_TIMER:
        {
            /* Cycle through all the LLI6 Entries and update them appropriately. */
            LLI6TimerCheck ();
            break;
        }
    }
}

/** 
 *  @b Description
 *  @n  
 *      The function Increments the reference counter for the LLI6 Entry. 
 *      This can be invoked by the ROUTE6 Module if it detects multiple 
 *      hosts which have different IP addresses but are actual one and
 *      the same.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  hLLI6
 *      Handle of the LLI6 Entry whose reference counter we need to increment.
 *
 *  @retval
 *      Not Applicable.
 */
void LLI6IncRefCount (HANDLE hLLI6)
{
    LLI6_ENTRY* ptr_lli6;

    /* Validate the arguments. */
    ptr_lli6 = (LLI6_ENTRY *)hLLI6;
    if (ptr_lli6 == NULL)
        return;

    /* Increment the reference count */
    ptr_lli6->RefCount++;
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function verifies if the LLI6 Entry belongs to a ROUTER or HOST.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  hLLI6
 *      Handle to the LLI6 Entry which we need to verify.
 *
 *  @retval
 *      1   - LLI6 Entry belongs to a ROUTER
 *  @retval
 *      0   - LLI6 Entry belongs to a HOST
 */
UINT8 LLI6IsRouter (HANDLE hLLI6)
{
    LLI6_ENTRY* ptr_lli6;

    /* Validate the arguments. */
    ptr_lli6 = (LLI6_ENTRY *)hLLI6;
    if (ptr_lli6 == NULL)
        return 0;
        
    /* Return the router status appropriately. */
    if (ptr_lli6->IsRouter == 1)
        return 1;
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function checks if the LLI6 Entry is DEAD or not?
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  hLLI6
 *      Handle to the LLI6 Entry which we need to check.
 *
 *  @retval
 *      1   - LLI6 Entry is DEAD & can be removed.
 *  @retval
 *      0   - LLI6 Entry is not DEAD
 */
UINT8 LLI6IsDead (HANDLE hLLI6)
{
    LLI6_ENTRY* ptr_lli6;

    /* Validate the arguments. */
    ptr_lli6 = (LLI6_ENTRY *)hLLI6;
    if (ptr_lli6 == NULL)
        return 0;
        
    /* Return the status appropriately. */
    if (ptr_lli6->status == ICMPV6_LLI_DEAD)
        return 1;
    return 0;        
}

/** 
 *  @b Description
 *  @n  
 *      The function checks if the LLI6 Entry is VALID or not?
 *      An LLI6 Entry can be used only if it is !INCOMPLETE and
 *      its !DEAD
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  hLLI6
 *      Handle to the LLI6 Entry which we need to check.
 *
 *  @retval
 *      1   - LLI6 Entry is VALID and can be used.
 *  @retval
 *      0   - LLI6 Entry is not VALID and should not be used.
 */
UINT8 LLI6IsValid (HANDLE hLLI6)
{
    LLI6_ENTRY* ptr_lli6;

    /* Validate the arguments. */
    ptr_lli6 = (LLI6_ENTRY *)hLLI6;
    if (ptr_lli6 == NULL)
        return 0;
        
    /* Return the status appropriately. */
    if ((ptr_lli6->status != ICMPV6_LLI_DEAD) && (ptr_lli6->status != ICMPV6_LLI_INCOMPLETE))
        return 1;

    /* The LLI6 Entry is not VALID. */
    return 0;        
}

/** 
 *  @b Description
 *  @n  
 *      The function moves an LLI6 Entry to INCOMPLETE STATE. This API should be used 
 *      very carefully as it might break the  Neighbor Unreachability Detection Logic.
 *      This is currently being used from the ROUTE6 Module to handle the special case
 *      for the Default Router Selection.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  hLLI6
 *      Handle to the LLI6 Entry whose status needs to be modified.
 *
 *  @retval
 *      Not Applicable.
 */
void LLI6SetIncomplete (HANDLE hLLI6)
{
    LLI6_ENTRY* ptr_lli6;

    /* Validate the arguments. */
    ptr_lli6 = (LLI6_ENTRY *)hLLI6;
    if (ptr_lli6 == NULL)
        return;

    /* Set the LLI6 state to INCOMPLETE. */
    ptr_lli6->status = ICMPV6_LLI_INCOMPLETE;
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function gets the network device associated with the LLI6 Entry.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  hLLI6
 *      Handle to the LLI6 Entry whose network device we need to return.
 *
 *  @retval
 *      Success - Handle to the Network Device
 *      Error   - 0
 */
NETIF_DEVICE* LLI6GetNetDevice (HANDLE hLLI6)
{
    LLI6_ENTRY* ptr_lli6;

    /* Validate the arguments. */
    ptr_lli6 = (LLI6_ENTRY *)hLLI6;
    if (ptr_lli6 == NULL)
        return 0;

    /* Return the Network Device. */
    return ptr_lli6->ptr_device;
}

/** 
 *  @b Description
 *  @n  
 *      This function is used to create a new LLI6 Entry. LLI6 Entries
 *      can only be created by the ROUTE6 Module.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_rt6
 *      Pointer to the Route6 Entry on which the LLI6 Object is created.
 *  @param[in]  pMacAddress
 *      Pointer to the layer2 MAC Address.
 *  @param[in]  IsRouter
 *      Flag which indicates if the LLI6 Entry is ROUTER or HOST. This is
 *      set to 1 for ROUTER and 0 for HOST.
 *
 *  @retval
 *   Handle to the new LLI Entry  -   Success
 *  @retval
 *   0                            -   Error
 */
HANDLE LLI6New (RT6_ENTRY* ptr_rt6, UINT8* pMacAddress, UINT8 IsRouter)
{
    LLI6_ENTRY* ptr_lli6;

    /* Validate the arguments: */
    if (ptr_rt6 == NULL)
        return 0;

    /* DUPLICATE Check: Cycle through all the LLI6 Entries which exist in the
     * System and see if we have a MATCH. */
    ptr_lli6 = LLI6Find (pMacAddress, NULL);
    if (ptr_lli6 != NULL)
    {
        /* Match Found: Ensure that the LLI6 Entry resides on the same network device
         * as the ROUTE6 object. */
        if (ptr_rt6->ptr_device != ptr_lli6->ptr_device)
        {
            DbgPrintf (DBG_ERROR, "LLI6New: RT6 Creates LLI6 on %s but LLI6 resides on %s\n", 
                       ptr_rt6->ptr_device->name, ptr_lli6->ptr_device->name);
            return 0;
        }

        /* We are reusing the same LLI6 Entry. Increment the reference counter. */
        ptr_lli6->RefCount++;

#ifdef LLI6_DEBUG
        DbgPrintf(DBG_INFO, "LLI6New: DEBUG: LLI6 entry 0x%p has reference counter %d\n",
                ptr_lli6, ptr_lli6->RefCount);
#endif
        /* Return the existing LLI6 entry. */
        return ptr_lli6;
    }

    /* No LLI Entry exists; we need to create a new one. So allocate memory for the new LLI6 Object. */
    ptr_lli6 = (LLI6_ENTRY *)mmAlloc (sizeof(LLI6_ENTRY));
    if (ptr_lli6 == NULL)
    {
        DbgPrintf (DBG_ERROR, "LLI6New: OOM\n");
        NotifyLowResource ();
        return 0;
    }

    /* Initialize the allocated block of memory */
    mmZeroInit ((void *)ptr_lli6, sizeof(LLI6_ENTRY));

    /* Populate the structure. */
    ptr_lli6->LastReachTS = llTimerGetTime(0);
    ptr_lli6->ptr_device  = ptr_rt6->ptr_device;
    ptr_lli6->SrcAddr     = IPV6_UNSPECIFIED_ADDRESS;
    ptr_lli6->RefCount    = 1;
    ptr_lli6->TargetAddr  = ptr_rt6->NextHop;
    
    /* Was the MAC Address specified? */
    if (pMacAddress != NULL)
    {
        /* YES. Remember it and move the LLI6 status to STALE. */
        mmCopy ((void *)&ptr_lli6->MacAddr[0], (void *)pMacAddress, 6);
        ptr_lli6->status = ICMPV6_LLI_STALE;
    }
    else
    {
        /* If there is no MAC Address specified then the LLIv6 entry is in
         * the INCOMPLETE State. */
        ptr_lli6->status = ICMPV6_LLI_INCOMPLETE;
    }

    /* Set the IsRouter Flag correctly. */
    ptr_lli6->IsRouter = IsRouter;

#ifdef LLI6_DEBUG
    DbgPrintf(DBG_INFO,
            "LLI6New: DEBUG: Creating LLI6 entry 0x%p STATE: %d ROUTER: %d\n",
            ptr_lli6, ptr_lli6->status, ptr_lli6->IsRouter);
#endif

    /* Add the LLI6 Entry to the Global List. */
    list_add ((LIST_NODE**)&gLLI6EntryList, (LIST_NODE*)ptr_lli6);

    /* Return the handle of the new LLI entry created. */
    return ptr_lli6;
}

/** 
 *  @b Description
 *  @n  
 *      This function is used to delete the LLI6 Entry. LLI6 Entries
 *      can only be deleted by the ROUTE6 Module.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  hLLI6
 *      Handle to the LLI6 Object to be deleted.
 *
 *  @retval
 *   Not Applicable.
 */
void LLI6Free (HANDLE hLLI6)
{
    LLI6_ENTRY* ptr_lli6;

    /* Get the pointer to the LLI6 Object handle. */
    ptr_lli6 = (LLI6_ENTRY *)hLLI6;

    /* Decrement the number of references being held. */
    ptr_lli6->RefCount = ptr_lli6->RefCount - 1;

    /* Delete only if there are no more references. */
    if (ptr_lli6->RefCount != 0)
    {
#ifdef LLI6_DEBUG
        DbgPrintf(DBG_INFO,
                "LLI6Free: DEBUG: LLI6 0x%p not freed up because %d references held\n",
                ptr_lli6, ptr_lli6->RefCount);
#endif
        return;
    }

    /* Remove the LLI6 Entry from the global list */
    list_remove_node ((LIST_NODE **)&gLLI6EntryList, (LIST_NODE *)ptr_lli6);

#ifdef LLI6_DEBUG
    DbgPrintf(DBG_INFO, "LLI6Free: DEBUG: Deleting LLI6 0x%p\n", ptr_lli6);
#endif

    /* Clean any pending packets. */
    if (ptr_lli6->pPkt)
        PBM_free (ptr_lli6->pPkt);

    /* Clean the LLI Memory */
    mmFree (ptr_lli6);
    return;
}

/** 
 *  @b Description
 *  @n  
 *      This function is called from the IPv6 stack to resolve the IPv6 address to 
 *      a corresponding MAC address and push the packet to the drivers.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  pPkt
 *      Pointer to the packet which needs to be transmitted.
 *  @param[in]  hLLI6
 *      Handle to the LLI6 Entry.
 *  @param[in]  ptr_device
 *      Pointer to the Network Interface Object on which the packet needs
 *      to be sent out.
 *  @param[in]  Address
 *      The Destination Address of the packet.
 *
 *  @retval
 *      Not Applicable.
 */
void LLI6TxIPPacket (PBM_Pkt *pPkt, HANDLE hLLI6, NETIF_DEVICE* ptr_device, IP6N Address)
{
    UINT8       bMACDst[6];
    IPV6HDR*    ptr_ipv6hdr;
    IP6N        srcAddr;
    LLI6_ENTRY* ptr_lli6 = (LLI6_ENTRY *)hLLI6;

    /* Is this a Multicast Packet? */
    if (IPv6IsMulticast(Address))
    {
        /* Multicast Address. */
        bMACDst[0] = 0x33;
        bMACDst[1] = 0x33;
        bMACDst[2] = Address.u.addr8[12];
        bMACDst[3] = Address.u.addr8[13];
        bMACDst[4] = Address.u.addr8[14];
        bMACDst[5] = Address.u.addr8[15];
    }
    else
    {
        /* Unicast Address: There should exist an LLI6 Entry for this. */
        if (ptr_lli6 == NULL)
        {
            DbgPrintf(DBG_ERROR,"LLI6TxIPPacket: No LLI6 Entry.");
            PBM_free (pPkt);
            return;
        }

        /* If the LLI6 Entry is DEAD we dont send out the packet for HOST Routes. 
         * But for Gateway routes we still let the packet through. */
        if ((ptr_lli6->status == ICMPV6_LLI_DEAD) && (ptr_lli6->IsRouter == 0))
        {
            PBM_free (pPkt);
            return;
        }

        /* Neighbor Unreachability Detection Logic:
         *  As per RFC 2461 Section 7.3.2: The first time when a node sends a packet and the
         *  status of the entry is STALE; we change the state to be DELAY */
        if (ptr_lli6->status == ICMPV6_LLI_STALE)
        {
            /* Remember the time this event took place; for the neighbor state machine to 
             * operate. */
            ptr_lli6->LastReachTS = llTimerGetTime(0);
            ptr_lli6->status      = ICMPV6_LLI_DELAY;

            /* RFC 2461: Section 7.2.2 states that If the source address of the 
             * packet prompting the solicitation is the same as one of the addresses 
             * assigned to the outgoing interface, that address SHOULD be placed in 
             * the IP Source Address of the outgoing solicitation. Otherwise, any one 
             * of the addresses assigned to the interface should be used.
             *
             * Here we store the Source Address of the packet prompting the SOLICITATION 
             * in the LLI6 Entry; this needs to be stored because we need to know this address
             * since we will also be sending NS later on as the LLI entry moves from DELAY 
             * to the PROBE state. */
            ptr_ipv6hdr = (IPV6HDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

            /*
             * NOTE: use mmCopy to copy the 16 byte IP6N addresses out of ptr_ipv6hdr
             * as this data is potentially un-aligned (SDOCM00097361)
             */
            mmCopy((char *)&srcAddr, (char *)&ptr_ipv6hdr->SrcAddr, sizeof(IP6N));

            ptr_lli6->SrcAddr = srcAddr;

#ifdef LLI6_DEBUG
            DbgPrintf(DBG_INFO,
                    "LLI6TxIPPacket: DEBUG: LLI6: 0x%p STALE --> DELAY\n",
                    ptr_lli6);
#endif
            /* Continue; sending out the packet though... */
        }

        /* Neighbor Unreachability Detection Logic:
         *  As per RFC 2461 Appendix C: If we are in the INCOMPLETE state; we will in turn
         *  send out a NS request here.  */      
        if (ptr_lli6->status == ICMPV6_LLI_INCOMPLETE)
        {
            /* Enqueue the packet which is being transmitted. We hold only one packet at a
             * time; so if there are any previous packets pending; clean them out. */
            if (ptr_lli6->pPkt)
                PBM_free (ptr_lli6->pPkt);

            /* Enqueue the current packet. */
            ptr_lli6->pPkt = pPkt;

            /* RFC 2461: Section 7.2.2 states that If the source address of the 
             * packet prompting the solicitation is the same as one of the addresses 
             * assigned to the outgoing interface, that address SHOULD be placed in 
             * the IP Source Address of the outgoing solicitation. Otherwise, any one 
             * of the addresses assigned to the interface should be used.
             *
             * Here we store the Source Address of the packet prompting the SOLICITATION 
             * in the LLI6 Entry; this needs to be stored because we need to know this address
             * since we will also be sending NS in the INCOMPLETE state when the LLI6 Timer 
             * expires. */
            ptr_ipv6hdr = (IPV6HDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

            /*
             * NOTE: use mmCopy to copy the 16 byte IP6N addresses out of ptr_ipv6hdr
             * as this data is potentially un-aligned (SDOCM00097361)
             */
            mmCopy((char *)&srcAddr, (char *)&ptr_ipv6hdr->SrcAddr, sizeof(IP6N));

            ptr_lli6->SrcAddr = srcAddr;

            /* Initialize the rest of the state parameters too. The timer will expire 
             * and handle the transmission of the NS Requests. This technique will ensure
             * that we have at least REACHABLE time between NS requests. */
            ptr_lli6->NumProbes   = 0;
            ptr_lli6->LastSendNS  = 0;
            ptr_lli6->LastReachTS = 0;

#ifdef LLI6_DEBUG
            DbgPrintf(DBG_INFO,
                    "LLI6TxIPPacket: DEBUG: LLI6 Entry 0x%p in INCOMPLETE; Packet queued.\n",
                    ptr_lli6);
#endif
            /*
             * Force NS message out immediately instead of waiting for timer
             * (SDOCM00098531)
             */
            LLI6TimerCheck();

            return;
        }

        /* Copy the MAC Address */
        mmCopy (bMACDst, ptr_lli6->MacAddr, 6);
    }

    /* Add an Ethernet Header to the packet. The Protocol type in the Ethernet Header
     * is IPv6. */ 
    if (NIMUAddHeader (ptr_device, (HANDLE) pPkt, bMACDst, NULL, 0x86DD) == 0)
    {
        /* Send the packet through the NIMU Interface. */
        NIMUSendPacket (ptr_device, pPkt);
    }
    else
    {
        /* There was an error and the header could not be added. Clean the packet
         * memory */
        PBM_free (pPkt);
    }
    return;
}

#endif /* _INCLUDE_IPv6_CODE */

