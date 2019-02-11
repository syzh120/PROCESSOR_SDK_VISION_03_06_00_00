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
 * ======== route6.c ========
 *
 * The file has functions which handle the Route6 objects
 *
 */

#include <stkmain.h>

#ifdef _INCLUDE_IPv6_CODE

/**********************************************************************
 *************************** Local Definitions ************************
 **********************************************************************/

/* Unique Messages: This is used to keep track of the internal ROUTE6 TIMERS */
#define MSG_ROUTE6_TIMER            (ID_ROUTE6*MSG_BLOCK + 1)

/**********************************************************************
 *************************** Global Variables *************************
 **********************************************************************/

/* This is a GLOBAL Timer which is used to handle the ROUTE6 Entries.
 * All Routing entries are subjected to timeouts */
static HANDLE   hRoute6Timer = 0;

/* This is a GLOBAL Linked List which keeps track of all IPv6 Routes; 
 * which include Network Routes (CLONING), HOST Routes (Cloned from 
 * Network Routes) and all Default Routes. Default Routes are always
 * added to the end of this list. */
static RT6_ENTRY* gIPv6RoutingTable = NULL;

/* This is the pointer which contains the Pointer to the Default Gateway 
 * which is to be used next. */
static RT6_ENTRY* gRoundRobinDefaultRoute = NULL;

/**********************************************************************
 *************************** ROUTE6 Functions *************************
 **********************************************************************/

/** 
 *  @b Description
 *  @n  
 *      The function executes the Route6 Lifetime Management.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @retval
 *      Not Applicable.
 */
static void Route6LifetimeMgmt (void)
{
    RT6_ENTRY*   ptr_rt6;
    UINT32       CurrentTime;

    /* Cycle through all the Routing Table. */ 
    ptr_rt6 = (RT6_ENTRY *)list_get_head ((LIST_NODE**)&gIPv6RoutingTable);
    while (ptr_rt6 != NULL)
    {
        /* Lifetime Management is DONE only on CLONING and GATEWAY Routes? */
        if (ptr_rt6->Flags & (FLG_RTE_CLONING|FLG_RTE_GATEWAY))
        {
            /* OK; Good now check if there is a TIMEOUT associated with this or not? */
            if (ptr_rt6->dwTimeout != INFINITE_LT)
            {
                /* Get the current time. */
                CurrentTime = llTimerGetTime (0);

                /* Check if the entry has expired or not? */
                if (CurrentTime > ptr_rt6->dwTimeout)
                {
                    /* Delete the routing entry since the routing timer has expired.
                     * In this case we need to notify the socket layer too (since it caches
                     * routes) */
                    Sock6PcbRtChange (ptr_rt6);
                    Rt6Free (ptr_rt6);

                    /* Since we cleaned the route we need to start again. */
                    ptr_rt6 = (RT6_ENTRY *)list_get_head ((LIST_NODE**)&gIPv6RoutingTable);
                    continue;
                }
            }
        }

        /* Special case: For Local HOST Routes there is no LLI6 Entry which is associated */
        if (ptr_rt6->Flags & FLG_RTE_IFLOCAL)
        {
            /* Get the next routing entry. */
            ptr_rt6 = (RT6_ENTRY *)list_get_next((LIST_NODE*)ptr_rt6);
            continue;
        }

        /* LLI6 Entry Cleanup: Check if there are any LLI6 Entries which need to be cleaned up. 
         * NOTE: LLI6 Entries exist only for HOST and GATEWAY Routes. */
        if (ptr_rt6->Flags & (FLG_RTE_HOST|FLG_RTE_GATEWAY))
        { 
            /* HOST/GATEWAY Route: Sanity Check we should always have an LLI6 Entry here. */
            if (ptr_rt6->hLLI6 != 0)
            {
                /* Check if the LLI6 Entry is a ROUTER or HOST? */
                if (LLI6IsRouter (ptr_rt6->hLLI6) == 0)
                {
                    /* HOST Entry: Check if the LLI6 Entry is DEAD */
                    if (LLI6IsDead (ptr_rt6->hLLI6) == 1)
                    {
                        /* Delete the routing entry since the LLI6 entry is no longer valid. 
                         * In this case we need to notify the socket layer too (since it caches
                         * routes) */
                        Sock6PcbRtChange (ptr_rt6);
                        Rt6Free (ptr_rt6);

                        /* Since we cleaned the route we need to start again. */
                        ptr_rt6 = (RT6_ENTRY *)list_get_head ((LIST_NODE**)&gIPv6RoutingTable);
                        continue;
                    }
                }
                else
                {
                    /* ROUTER Entry: We dont clean LLI6 Entries for routers even if they are DEAD.*/
                }
            }
            else
            {
                /* This should never be the case; just a SANITY Check... */
                DbgPrintf (DBG_ERROR, "Rt6Lifetime: Rt6 object 0x%p has no LLI6 entry\n", ptr_rt6);
            }
        }

        /* Get the next routing entry. */
        ptr_rt6 = (RT6_ENTRY *)list_get_next((LIST_NODE*)ptr_rt6);
    }
    return;
}

/** 
 *  @b Description
 *  @n  
 *      Sevices intialization and resource messages for the ROUTE6 Module
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  Msg
 *      The message event which needs to be handled.
 *
 *  @retval
 *      Not Applicable.
 */
void Route6Msg (uint Msg)
{
    switch( Msg )
    {
        /* System Initialization */
        case MSG_EXEC_SYSTEM_INIT:
        {
            /* Create the Lifetime Management Timer: */
            hRoute6Timer = TimerNew (&Route6Msg, TIMER_TICKS_LLI, MSG_ROUTE6_TIMER);
            break;
        }
        /* System Shutdown */
        case MSG_EXEC_SYSTEM_SHUTDOWN:
        {
            /* System is shutting down. Shutdown all timers. */
            if (hRoute6Timer)
            {
                /* Close the timer */
                TimerFree (hRoute6Timer);
                hRoute6Timer = 0;
            }
            break;
        }
        /* A message saying that the Lifetime management timer has expired. */
        case MSG_ROUTE6_TIMER:
        {
            /* Run the Lifetime Management on all Route6 Entries. */ 
            Route6LifetimeMgmt ();
            break;      
        }
    }
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function creates a new routing entry.
 *
 *  @param[in]  flags
 *      Specifies flags.
 *  @param[in]  IPAddr
 *      This is the IPv6 address for which the route is created.
 *  @param[in]  IPMask
 *      This is the IPv6 subnet mask.
 *  @param[in]  NextHop
 *      This is the Next Hop gateway associated with the route.
 *  @param[in]  mac_address
 *      This is the MAC Address associated with the ROUTE. This can be NULL.
 *  @param[in]  ptr_device
 *      This is the interface on which the route is created.
 *  @param[in]  ValidLifetime
 *      Timeout for which this route will remain valid. This is VALID only 
 *      for CLONING Routes. Once the CLONING Route is timed out all HOST 
 *      routes derived from this will also be removed. If this is INFINITE_LT
 *      then the routes are always active.
 *
 *  @retval
 *      Success -   Handle to the new route
 *  @retval
 *      Error   -   0
 */
HANDLE Rt6Create 
(
    UINT32        flags, 
    IP6N          IPAddr, 
    IP6N          IPMask, 
    IP6N          NextHop, 
    UINT8*        mac_address,
    NETIF_DEVICE* ptr_device, 
    UINT32        ValidLifetime
)
{
    RT6_ENTRY*   ptr_rt6;

    /* Validate the arguments: We need to ensure that there is a device associated with the route. */
    if (ptr_device == NULL)
    {
        DbgPrintf(DBG_ERROR,"Rt6Create: No device specified.\n");
        return 0;
    }

    /* Route6 Objects can be created only on devices which have an IPv6 record. */
    if (ptr_device->ptr_ipv6device == NULL)
    {
        DbgPrintf(DBG_ERROR,"Rt6Create: Route6 on %s but this is not IPv6 compatible\n", ptr_device->name);
        return 0;
    }

    /* Check here for duplicates? We cannot have multiple CLONING Routes 
     * for the same network. */
    if (flags & FLG_RTE_CLONING)
    {
        ptr_rt6 = (RT6_ENTRY *)Rt6Find (FLG_RTE_CLONING, IPAddr, ptr_device);
        if (ptr_rt6 != NULL)
            return ptr_rt6;
    }

    /* Allocate memory for a new routing entry. */
    ptr_rt6 = mmAlloc (sizeof(RT6_ENTRY));
    if (ptr_rt6 == NULL) {
        /* fix for SDOCM00101710 */
        DbgPrintf(DBG_WARN,
        "Rt6Create: Error: OOM: failed to create route (alloc of %d bytes)\n",
                sizeof(RT6_ENTRY));

        NotifyLowResource();
        return 0;
    }

    /* Initialize the allocated block of memory. */
    mmZeroInit ((void *)ptr_rt6, sizeof(RT6_ENTRY));

    /* Initialize and populate the new route */
    ptr_rt6->Flags      = flags;
    ptr_rt6->IPAddr     = IPAddr;
    ptr_rt6->IPMask     = IPMask;
    ptr_rt6->NextHop    = NextHop;
    ptr_rt6->ptr_device = ptr_device;  
    ptr_rt6->RefCount   = 1;

    /* The timeout is valid only for CLONING and GATEWAY Routes; all host routes are never timed out. */
    if (flags & (FLG_RTE_CLONING|FLG_RTE_GATEWAY))
    {
        /* Cloning Route Detected: Set the Timeout for it. */
        if (ValidLifetime == INFINITE_LT)
            ptr_rt6->dwTimeout = INFINITE_LT;
        else
            ptr_rt6->dwTimeout = llTimerGetTime(0) + ValidLifetime;
    }
    else
    {
        /* Host Route Detected: These routes are never timed out. */
        ptr_rt6->dwTimeout = INFINITE_LT;
    }

    /* Compute the Network Address of the route */
    ptr_rt6->NetworkAddr.u.addr32[0] = IPAddr.u.addr32[0] & ptr_rt6->IPMask.u.addr32[0];
    ptr_rt6->NetworkAddr.u.addr32[1] = IPAddr.u.addr32[1] & ptr_rt6->IPMask.u.addr32[1];
    ptr_rt6->NetworkAddr.u.addr32[2] = IPAddr.u.addr32[2] & ptr_rt6->IPMask.u.addr32[2];
    ptr_rt6->NetworkAddr.u.addr32[3] = IPAddr.u.addr32[3] & ptr_rt6->IPMask.u.addr32[3];

    /* If we have an IF, get the MTU */
    if (ptr_device)
        ptr_rt6->ProtMTU = IFGetMTU (ptr_device);

    /* Special Case: Check if this is a Local HOST Route being created */
    if (flags & FLG_RTE_IFLOCAL)
    {
        /* For Local HOST Routes we dont create LLI6 Entries since these are LOCAL 
         * Thus we simply add them to the Routing table. */
        list_add ((LIST_NODE**)&gIPv6RoutingTable, (LIST_NODE*)ptr_rt6);

        /* The Next Hop Address is the same as the IP Address. */
        ptr_rt6->NextHop = IPAddr;

        /* Return the new route. */
        return (HANDLE)ptr_rt6;
    }

    /* Further processing is specific to the type of ROUTE being created. */
    if (flags & FLG_RTE_HOST)
    {
        RT6_ENTRY* ptr_defaultrt6;

        /* For HOST Routes: Check if the NextHop Address is UNSPECIFIED; then
         * initialize it to be the same as the IPAddr; this means ON LINK; else
         * we have already initialized to the passed argument. */
        if (IPv6CompareAddress(ptr_rt6->NextHop, IPV6_UNSPECIFIED_ADDRESS))
            ptr_rt6->NextHop = IPAddr;

        /* Check if there exists a GATEWAY Route which has the same Next Hop Address. */
        ptr_defaultrt6 = (RT6_ENTRY *)Rt6FindDefaultRouter(ptr_rt6->NextHop, ptr_device);
        if (ptr_defaultrt6 != NULL)
        {
            /* If the MAC Address was specified then we need to update both the HOST
             * and GATEWAY Entries with the new LLI6 Entry which is being created.
             * This is because this is the latest information we have. */
            if (mac_address != NULL)
            {
                /* Create the new LLI6 Entry */
                ptr_rt6->hLLI6 = LLI6New (ptr_rt6, mac_address, 1);
                if (ptr_rt6->hLLI6 == 0)
                {
                    /* Error: Unable to create the LLI Entry. */
                    DbgPrintf (DBG_ERROR, "Rt6Create: Error: Unable to create LLI6 for ROUTE6 0x%p\n", ptr_rt6);
                    mmFree (ptr_rt6);
                    return 0;
                }

                /* Get rid of the Gateway LLI6 Entry. */
                LLI6Free (ptr_defaultrt6->hLLI6);

                /* Link the Gateway and Host LLI6 Entries with each other. */
                ptr_defaultrt6->hLLI6 = ptr_rt6->hLLI6;
                LLI6IncRefCount (ptr_rt6->hLLI6);
            }
            else
            {
                /* There was no MAC Address Information; in this case we simply inherit 
                 * the LLI6 Information from the Gateway. */
                ptr_rt6->hLLI6 = ptr_defaultrt6->hLLI6;
                LLI6IncRefCount (ptr_rt6->hLLI6);
            }
        }
        else
        {
            /* There was no matching GATEWAY; with the same address so we need to 
             * create a new LLI6 Entry for the HOST. */
            ptr_rt6->hLLI6 = LLI6New (ptr_rt6, mac_address, 0);
            if (ptr_rt6->hLLI6 == 0)
            {
                /* Error: Unable to create the LLI Entry. */
                DbgPrintf (DBG_ERROR, "Rt6Create: Error: Unable to create LLI6 for ROUTE6 0x%p\n", ptr_rt6);
                mmFree (ptr_rt6);
                return 0;
            }
        }
#ifdef ROUTE6_DEBUG
        /* Debug: Print the network address for which the route is created. */
        DbgPrintf(DBG_INFO,
                "Rt6Create: Creating Route6 Entry for HOST 0x%p LLI6: 0x%p\n",
                ptr_rt6, ptr_rt6->hLLI6);
        IPv6DisplayIPAddress (ptr_rt6->NetworkAddr);
#endif
    }
    else if (flags & FLG_RTE_GATEWAY)
    {
        RT6_ENTRY* ptr_hostrt6;

        /* Check if there exists a HOST Route which maps to the same address. */
        ptr_hostrt6 = (RT6_ENTRY *)Rt6Find (FLG_RTE_HOST, NextHop, ptr_device);
        if (ptr_hostrt6 != NULL)
        {
            /* If the MAC Address was specified then we need to update both the HOST
             * and GATEWAY Entries with the new LLI6 Entry which is being created.
             * This is because this is the latest information we have. */
            if (mac_address != NULL)
            {
                /* Create the new LLI6 Entry */
                ptr_rt6->hLLI6 = LLI6New (ptr_rt6, mac_address, 1);
                if (ptr_rt6->hLLI6 == 0)
                {
                    /* Error: Unable to create the LLI Entry. */
                    DbgPrintf (DBG_ERROR, "Rt6Create: Error: Unable to create LLI6 for ROUTE6 0x%p\n", ptr_rt6);
                    mmFree (ptr_rt6);
                    return 0;
                }

                /* Get rid of the HOST LLI6 Entry. */
                LLI6Free (ptr_hostrt6->hLLI6);

                /* Link the Gateway and Host LLI6 Entries with each other. */
                ptr_hostrt6->hLLI6 = ptr_rt6->hLLI6;
                LLI6IncRefCount (ptr_rt6->hLLI6);
            }
            else
            {
                /* There was no MAC Address information in this case we inherit 
                 * the LLI6 from the HOST Route. */
                ptr_rt6->hLLI6 = ptr_hostrt6->hLLI6;
                LLI6IncRefCount (ptr_rt6->hLLI6);
            }
        }
        else
        {
            /* Create the new LLI6 Entry. */
            ptr_rt6->hLLI6 = LLI6New (ptr_rt6, mac_address, 1);
            if (ptr_rt6->hLLI6 == 0)
            {
                /* Error: Unable to create the LLI Entry. */
                DbgPrintf (DBG_ERROR, "Rt6Create: Error: Unable to create LLI6 for ROUTE6 0x%p\n", ptr_rt6);
                mmFree (ptr_rt6);
                return 0;
            }                
        }
#ifdef ROUTE6_DEBUG
        /* Debug: Print the network address for which the route is created. */
        DbgPrintf(DBG_INFO,
                "Rt6Create: Creating Route6 Entry for GATEWAY 0x%p LLI6 0x%p\n",
                ptr_rt6, ptr_rt6->hLLI6);
        IPv6DisplayIPAddress (ptr_rt6->NextHop);
#endif
        /* Gateway Routes are always added to the end of the routing list chain. This is because
         * we want to search for more direct host routes before we start sending packets to the 
         * default gateways. */
        list_cat ((LIST_NODE**)&gIPv6RoutingTable, (LIST_NODE**)&ptr_rt6);
        return (HANDLE)ptr_rt6;
    }
    else
    {
#ifdef ROUTE6_DEBUG
        /* Debug: Print the network address for which the route is created. */
        DbgPrintf(DBG_INFO, "Rt6Create: Creating Route6 Entry for NETWORK 0x%p\n",
                ptr_rt6);
        IPv6DisplayIPAddress (ptr_rt6->NetworkAddr);
#endif
    }

    /* Add the new route to the routing table. */
    list_add ((LIST_NODE**)&gIPv6RoutingTable, (LIST_NODE*)ptr_rt6);

    /* Return the new route. */
    return (HANDLE)ptr_rt6;
}

/** 
 *  @b Description
 *  @n  
 *      The function modifies an existing routing entry.
 *
 *  @param[in]  hRoute6
 *      Handle to the route which is to be modified.
 *  @param[in]  flags
 *      Specifies flags.
 *  @param[in]  IPAddr
 *      This is the IPv6 address for which the route is created.
 *  @param[in]  IPMask
 *      This is the IPv6 subnet mask.
 *  @param[in]  NextHop
 *      This is the Next Hop gateway associated with the route.
 *  @param[in]  mac_address
 *      This is the MAC Address associated with the ROUTE. This can be NULL.
 *  @param[in]  ptr_device
 *      This is the interface on which the route is created.
 *  @param[in]  ValidLifetime
 *      Timeout for which this route will remain valid. This is VALID only 
 *      for CLONING Routes. Once the CLONING Route is timed out all HOST 
 *      routes derived from this will also be removed. If this is INFINITE_LT
 *      then the routes are always active.
 *
 *  @retval
 *      Success -   Handle to the modified route
 *  @retval
 *      Error   -   0
 */
HANDLE Rt6Modify
(
    HANDLE        hRoute6,
    UINT32        flags, 
    IP6N          IPAddr, 
    IP6N          IPMask, 
    IP6N          NextHop, 
    UINT8*        mac_address,
    NETIF_DEVICE* ptr_device, 
    UINT32        ValidLifetime
)
{
    RT6_ENTRY*   ptr_rt6;

    /* Get the Routing Entry which is to be modified. */
    ptr_rt6 = (RT6_ENTRY *)hRoute6;
    if (ptr_rt6 == NULL)
        return 0;

    /* If the Route FLAGS are being modified; then we need to delete the old ROUTE
     * and RECREATE a new one with the new flags. */
    if (ptr_rt6->Flags != flags)
    {
        /* Delete the routing entry since the modification request has yielded in a new 
         * routing entry to be created. */
        Sock6PcbRtChange (ptr_rt6);
        Rt6Free (ptr_rt6);

        /* Create a new routing entry and returns its handle. */
        return Rt6Create (flags, IPAddr, IPMask, NextHop, mac_address, ptr_device, ValidLifetime);
    }

    /* If the Next HOP Entries are different; then we need to delete the OLD ROUTE and 
     * RECREATE a new one; this is required since the LLI6 Block will now be different too. */
    if (IPv6CompareAddress(ptr_rt6->NextHop,NextHop) == 0)
    {
        /* Delete the routing entry since the modification request has yielded in a new 
         * next hop gateway to be used. */
        Sock6PcbRtChange (ptr_rt6);
        Rt6Free (ptr_rt6);

        /* Create a new routing entry and returns its handle. */
        return Rt6Create (flags, IPAddr, IPMask, NextHop, mac_address, ptr_device, ValidLifetime);            
    }

    /* Modify the Routing Entry. */
    ptr_rt6->Flags      = flags;
    ptr_rt6->IPAddr     = IPAddr;
    ptr_rt6->IPMask     = IPMask;
    ptr_rt6->NextHop    = NextHop;
    ptr_rt6->ptr_device = ptr_device;

    /* The timeout is valid only for CLONING and GATEWAY Routes; all host routes are never timed out. */
    if (flags & (FLG_RTE_CLONING|FLG_RTE_GATEWAY))
    {
        /* Cloning Route Detected: Set the Timeout for it. */
        if (ValidLifetime == INFINITE_LT)
            ptr_rt6->dwTimeout = INFINITE_LT;
        else
            ptr_rt6->dwTimeout = llTimerGetTime(0) + ValidLifetime;
    }
    else
    {
        /* Host Route Detected: These routes are never timed out. */
        ptr_rt6->dwTimeout = INFINITE_LT;
    }

    /* Compute the Network Address of the route */
    ptr_rt6->NetworkAddr.u.addr32[0] = IPAddr.u.addr32[0] & ptr_rt6->IPMask.u.addr32[0];
    ptr_rt6->NetworkAddr.u.addr32[1] = IPAddr.u.addr32[1] & ptr_rt6->IPMask.u.addr32[1];
    ptr_rt6->NetworkAddr.u.addr32[2] = IPAddr.u.addr32[2] & ptr_rt6->IPMask.u.addr32[2];
    ptr_rt6->NetworkAddr.u.addr32[3] = IPAddr.u.addr32[3] & ptr_rt6->IPMask.u.addr32[3];

    /* If we have an IF, get the MTU */
    if (ptr_device)
        ptr_rt6->ProtMTU = IFGetMTU (ptr_device);

    /* Return the modified routing entry. */ 
    return ptr_rt6;
}

/** 
 *  @b Description
 *  @n  
 *      The function frees an existing routing entry.
 *
 *  @param[in]  hRoute6
 *      Route to be deleted.
 *
 *  @retval
 *      Not Applicable.
 */
void Rt6Free (HANDLE hRoute6)
{
    RT6_ENTRY*   ptr_rt6;
    RT6_ENTRY*   ptr_cloneRt6;
    IP6N         NetworkAddress;

    /* Get the routing entry. */
    ptr_rt6 = (RT6_ENTRY *)hRoute6;
    if (ptr_rt6 == NULL)
    {
        DbgPrintf(DBG_ERROR, "Rt6Free: No Valid Routing Entry passed.\n");
        return;
    }

    /* Decrement the reference */
    ptr_rt6->RefCount = ptr_rt6->RefCount - 1;

    /* Delete the ROUTE6 Entry only if there are no more references being held. */
    if (ptr_rt6->RefCount != 0)
        return;
    
    /* If there exists an LLI6 Entry then we need to delete it too. */
    if (ptr_rt6->hLLI6)
        LLI6Free (ptr_rt6->hLLI6);
    
    /* Remove the route from the routing table; this needs to be done before
     * else the subsequent checks for "cloned" routes will get stuck infinitely. */
    list_remove_node ((LIST_NODE**)&gIPv6RoutingTable, (LIST_NODE*)ptr_rt6);

    /* Check if the route being deleted is LOCAL or not? */
    if ((ptr_rt6->Flags & FLG_RTE_IFLOCAL) == 0)
    {
        /* NO. Not a local route. 
         * NOTE: If we are cleaning a CLONING Route then we need to remove any routes cloned
         * from this too. This implies that we cycle through all the Routing Entries and check
         * for such routes too. */
        if (ptr_rt6->Flags & FLG_RTE_CLONING)
        {
            /* Check if there exists any routes cloned from the parent network route.
             * Cycle through the Routing Table for search routes */ 
            ptr_cloneRt6 = (RT6_ENTRY *)list_get_head ((LIST_NODE**)&gIPv6RoutingTable);
            while (ptr_cloneRt6 != NULL)
            {
                /* Get the Clone RT Network Mask with respect to the network mask of the route being deleted? */
                NetworkAddress.u.addr32[0] = ptr_cloneRt6->IPAddr.u.addr32[0] & ptr_rt6->IPMask.u.addr32[0];
                NetworkAddress.u.addr32[1] = ptr_cloneRt6->IPAddr.u.addr32[1] & ptr_rt6->IPMask.u.addr32[1];
                NetworkAddress.u.addr32[2] = ptr_cloneRt6->IPAddr.u.addr32[2] & ptr_rt6->IPMask.u.addr32[2];
                NetworkAddress.u.addr32[3] = ptr_cloneRt6->IPAddr.u.addr32[3] & ptr_rt6->IPMask.u.addr32[3];

                /* Do we have a match? */
                if ((IPv6CompareAddress(ptr_rt6->NetworkAddr, NetworkAddress) == 1) && 
                    (ptr_cloneRt6->ptr_device == ptr_rt6->ptr_device))
                {
                    /* The routes were cloned so we need to delete it too since they were derived 
                     * from the main parent route which is being deleted. Notify the socket layer
                     * about this too. */
                    Sock6PcbRtChange (ptr_cloneRt6);
                    Rt6Free (ptr_cloneRt6);
 
                    /* Since cleaning the routes in turn changes the linked list; its best to start
                     * from scratch again. */
                    ptr_cloneRt6 = (RT6_ENTRY *)list_get_head ((LIST_NODE**)&gIPv6RoutingTable);
                }
                else
                {
                    /* Get the next routing entry. */
                    ptr_cloneRt6 = (RT6_ENTRY *)list_get_next((LIST_NODE*)ptr_cloneRt6);
                }
            }
        }

        /* If we are deleting a HOST or GATEWAY Route we need to make sure that 
         * if the address is in the NEXT HOP Field; then we remove that Routing
         * Entry too. */
        if (ptr_rt6->Flags & (FLG_RTE_HOST|FLG_RTE_GATEWAY))
        {
            /* Cycle through the entire ROUTING table for routes. */
            ptr_cloneRt6 = (RT6_ENTRY *)list_get_head ((LIST_NODE**)&gIPv6RoutingTable);
            while (ptr_cloneRt6 != NULL)
            {
                /* Do we have a match? */
                if((IPv6CompareAddress(ptr_cloneRt6->NextHop, ptr_rt6->NextHop) == 1) && 
                   (ptr_cloneRt6->ptr_device == ptr_rt6->ptr_device))
                {
                    /* Clean the routing entry and notify the socket layer. */
                    Sock6PcbRtChange (ptr_cloneRt6);
                    Rt6Free (ptr_cloneRt6);

                    /* Since cleaning the routes in turn changes the linked list; its best to start
                     * from scratch again. */
                    ptr_cloneRt6 = (RT6_ENTRY *)list_get_head ((LIST_NODE**)&gIPv6RoutingTable);
                }
                else
                {
                    /* Get the next routing entry. */
                    ptr_cloneRt6 = (RT6_ENTRY *)list_get_next((LIST_NODE*)ptr_cloneRt6);
                }
            }
        }

        /* While deleting GATEWAY Routes ensure that we reset the GLOBAL Default Round Robin
         * Router Selector to NULL. */
        if (ptr_rt6->Flags & FLG_RTE_GATEWAY)
            gRoundRobinDefaultRoute = NULL;
    }

    /* Clean the route memory. */
    mmFree (ptr_rt6);
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function cleans all routes on a specific interface
 *
 *  @param[in]  ptr_device
 *      Pointer to the device for which all routes will be cleaned.
 *
 *  @retval
 *      Not Applicable.
 */
void Rt6FlushInterfaceRoutes (NETIF_DEVICE* ptr_device)
{
    RT6_ENTRY*   ptr_rt6;

    /* Cycle through all the routing entries in the IPv6 Routing Table and clean them out
     * if they match the interface. */
    ptr_rt6 = (RT6_ENTRY *)list_get_head ((LIST_NODE**)&gIPv6RoutingTable);
    while (ptr_rt6 != NULL)
    {
        /* Do we have a match? */
        if (ptr_rt6->ptr_device == ptr_device)
        {
            /* YES. We need to clean this route and notify the socket layer. */
            Sock6PcbRtChange (ptr_rt6);
            Rt6Free (ptr_rt6);

            /* Removing the route changes the Routing Table; so we start again from the beginning. */
            ptr_rt6 = (RT6_ENTRY *)list_get_head ((LIST_NODE**)&gIPv6RoutingTable);
        }
        else
        {
            /* Get the next routing entry. */
            ptr_rt6 = (RT6_ENTRY *)list_get_next((LIST_NODE*)ptr_rt6);
        }
    }
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function searches the routing table for a route to be used.
 *
 *  @param[in]  Flags
 *      Flags associated with the routing entry. Specifies the SEARCH
 *      Parameters that can be used to find a ROUTING Entry. 
 *      FLG_RTE_HOST    -> Search ROUTE6 table for only HOST routes
 *      FLG_RTE_CLONING -> Search ROUTE6 table for only NETWORK routes
 *      0               -> Search all ROUTES (Host & Network)
 *                         but Network routes are not cloned.
 *      FLG_RTF_CLONE   -> Invalid. 
 *      FLG_RTE_GATEWAY -> Invalid. (Use the Rt6FindDefaultRouter API) 
 *
 *      The flags should be SET to 
 *          FLG_RTE_HOST | FLG_RTE_CLONING | FLG_RTE_GATEWAY | FLG_RTF_CLONE
 *      From the IPv6 Routing Lookup API; since this will search all Valid
 *      Routes and if the ROUTE is a CLONING Route then it will be 
 *      CLONED (FLG_RTF_CLONE) too.
 *  @param[in]  IPAddress
 *      The IPv6 address for which we are trying to find a ROUTE. 
 *  @param[in]  ptr_device
 *      Device on which the route exists. This can be NULL.
 *
 *  @retval
 *      Match   -   Handle to the routing 6 entry
 *  @retval
 *      No Match    -   0     
 */
HANDLE Rt6Find (UINT32 Flags, IP6N IPAddress, NETIF_DEVICE* ptr_device)
{
    RT6_ENTRY*   ptr_rt6;
    RT6_ENTRY*   prtClone;
    IP6N         NetworkAddress;
    UINT32       NewFlags;
    RT6_ENTRY*   ptr_defaultRoute;


    /* Search the routing table for a match? */
    ptr_rt6 = (RT6_ENTRY *)list_get_head ((LIST_NODE**)&gIPv6RoutingTable);
    while (ptr_rt6 != NULL)
    {
        
        /* Was a network device specified? */
        if (ptr_device != NULL)
        {
            /* YES. Check if we need to proceed further with the routing lookup. */
            if (ptr_device != ptr_rt6->ptr_device)
            {
                /* NO; the route is not what we are looking for */
                ptr_rt6 = (RT6_ENTRY *)list_get_next((LIST_NODE*)ptr_rt6);
                continue;                    
            }
        }

        /* Were there any special routes we are interested in? */
        if (Flags != 0)
        {
            /* Check if the routing entry matches the flags or not? */
            if ((Flags & ptr_rt6->Flags) == 0)
            {
                /* NO; the route is not what we are looking for */
                ptr_rt6 = (RT6_ENTRY *)list_get_next((LIST_NODE*)ptr_rt6);
                continue;
            }
        }

        /* Compute the Network Address of the Dst we are trying to route */
        NetworkAddress.u.addr32[0] = IPAddress.u.addr32[0] & ptr_rt6->IPMask.u.addr32[0];
        NetworkAddress.u.addr32[1] = IPAddress.u.addr32[1] & ptr_rt6->IPMask.u.addr32[1];
        NetworkAddress.u.addr32[2] = IPAddress.u.addr32[2] & ptr_rt6->IPMask.u.addr32[2];
        NetworkAddress.u.addr32[3] = IPAddress.u.addr32[3] & ptr_rt6->IPMask.u.addr32[3];
 
        /* Check if the Network Address matches. */
        if ((IPv6CompareAddress(ptr_rt6->NetworkAddr, NetworkAddress) == 1))
            break;

        /* We need to move to the next routing entry. */
        ptr_rt6 = (RT6_ENTRY *)list_get_next((LIST_NODE*)ptr_rt6);
    }

    /* Did we get a matching ROUTING Entry; we can use; if none exists then we are done. */
    if (ptr_rt6 == NULL)
        return 0;

    /* Control comes here; indicates that a valid ROUTING Entry was found. 
     * Check the type of route found. FOR HOST Routes; nothing needs to be done. */
    if (ptr_rt6->Flags & FLG_RTE_HOST)
        return ptr_rt6;

    /* Check if the route is a NETWORK (CLONING) Route; in this case we might need to CLONE
     * the Entry into a HOST Route only if the FLAGS indicate so. */
    if (ptr_rt6->Flags & FLG_RTE_CLONING)
    {
        /* We found a NETWORK Route; do we need to CLONE this to a HOST route. */
        if (Flags & FLG_RTF_CLONE)
        {
            /* Copy the flags */
            NewFlags = ptr_rt6->Flags;

            /* Clear the flags that don't carry over */
            NewFlags &= ~(FLG_RTE_CLONING|FLG_RTE_STATIC|FLG_RTE_DYNAMIC);

            /* Make us a host route */
            NewFlags |= FLG_RTE_HOST;

            /* Create the new clone route; since this a HOST Route set the timeout to be INFINITE. */
            prtClone = Rt6Create (NewFlags, IPAddress, IPV6_HOST_MASK, IPV6_UNSPECIFIED_ADDRESS, 
                                  NULL, ptr_rt6->ptr_device, INFINITE_LT);

            /* Return the cloned route. */
            return prtClone;
        }
        else
        {
            /* We cannot clone the NETWORK Route; simply return the NETWORK Route. */
            return ptr_rt6;
        }
    }

    /* Control comes here; implies that the ROUTE6 object was a GATEWAY Route; in this case we need to
     * perform the default ROUTER Selection Logic here. */
    if (ptr_rt6->Flags & FLG_RTE_GATEWAY)
    {
        /* Remember the first default gateway. */
        ptr_defaultRoute = ptr_rt6;

        do
        {
            /* YES. Do we have a VALID LLI Entry Matching the Gateway and is this 
             * in any state besides INCOMPLETE. If so then we select this gateway */
            if (LLI6IsValid (ptr_rt6->hLLI6) == 1)
                return ptr_rt6;

            /* Check if there is another default gateway which could be used. */
            ptr_rt6 = (RT6_ENTRY *)list_get_next((LIST_NODE*)ptr_rt6);
        }while (ptr_rt6 != NULL);

        /* Control comes here implies that all the Default ROUTER Entries were 
         * either INCOMPLETE or DEAD.
         * RFC 2461 states that we need to select the GATEWAYS in ROUND ROBIN Order now. 
         * If there is no ROUTER selected till now; select the first one. */
        if (gRoundRobinDefaultRoute == NULL)
        {
            gRoundRobinDefaultRoute = ptr_defaultRoute;
        }
        else
        {
            /* Move the Round Robin Router Selection Pointer to the next GATEWAY Entry. */
            gRoundRobinDefaultRoute = (RT6_ENTRY *)list_get_next((LIST_NODE*)gRoundRobinDefaultRoute);

            /* If we have reached the end of the list; select the first Default router again. */
            if (gRoundRobinDefaultRoute == NULL)
                gRoundRobinDefaultRoute = ptr_defaultRoute;
        }

        /* Since we are now using the DEFAULT Router; move the corresponding entry to 
         * INCOMPLETE state. */
        LLI6SetIncomplete (gRoundRobinDefaultRoute->hLLI6);
        
        /* If the control comes here; we had 1 or more default routes all of which had their LLI6
         * entries in the INCOMPLTE state. So in this case return any routing entry. */
        return gRoundRobinDefaultRoute;
    }

    /* Control should never come here. There was an INVALID Flag combination. */
    DbgPrintf(DBG_ERROR,"Rt6Find: Route6 0x%p has INVALID Flags 0x%x\n", ptr_rt6, ptr_rt6->Flags);
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function returns the LLIv6 entry given the Route6 handle
 *
 *  @param[in]  hRoute6
 *      The handle to the route6 object whose LLIv6 handle we are 
 *      interested in.
 *
 *  @retval
 *      Success -   Handle to the LLIv6
 *  @retval
 *      Error   -   0  
 */
HANDLE Rt6GetLLI (HANDLE hRoute6)
{
    RT6_ENTRY*   ptr_rt6;

    /* Get the routing entry */
    ptr_rt6 = (RT6_ENTRY *)hRoute6;
    if (ptr_rt6 == NULL)
        return 0;

    /* Return the handle of the LLI v6 object. */
    return ptr_rt6->hLLI6;
}

/** 
 *  @b Description
 *  @n  
 *      The function gets the Interface handle associated with the Route6
 *      object.
 *
 *  @param[in]  hRoute6
 *      The handle to the route6 object whose Interface handle we are 
 *      interested in.
 *
 *  @retval
 *      Success -   Handle to the Interface
 *  @retval
 *      Error   -   0  
 */
HANDLE Rt6GetIF (HANDLE hRoute6)
{
    RT6_ENTRY*   ptr_rt6;

    /* Get the routing entry */
    ptr_rt6 = (RT6_ENTRY *)hRoute6;
    if (ptr_rt6 == NULL)
        return 0;

    /* Return the handle of the Interface handle. */
    return ptr_rt6->ptr_device;
}

/** 
 *  @b Description
 *  @n  
 *      The function gets the MTU associated with the Route6 object.
 *
 *  @param[in]  hRoute6
 *      The handle to the ROUTE6 Object whose MTU we are interested in.
 *
 *  @retval
 *      Success -   MTU of the route.
 *  @retval
 *      Error   -   0
 */
UINT32 Rt6GetMTU (HANDLE hRoute6)
{
    RT6_ENTRY*   ptr_rt6;

    /* Get the routing entry */
    ptr_rt6 = (RT6_ENTRY *)hRoute6;
    if (ptr_rt6 == NULL)
        return 0;

    /* Return the handle of the Interface handle. */
    return ptr_rt6->ProtMTU;        
}

/** 
 *  @b Description
 *  @n  
 *      The function checks if the route specified is LOCAL or not? 
 *
 *  @param[in]  hRoute
 *      The handle to the ROUTE6 Object.
 *
 *  @retval
 *      Success -   MTU of the route.
 *  @retval
 *      Error   -   0
 */
int Rt6IsLocalRoute (HANDLE hRoute)
{
    RT6_ENTRY* ptr_rt6;

    /* Get the routing entry. */
    ptr_rt6 = (RT6_ENTRY *)hRoute;
    if (ptr_rt6 == NULL)
        return 0;

    /* Check if this is a local route? */
    if (ptr_rt6->Flags & FLG_RTE_IFLOCAL)
        return 1;

    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function increments the reference count for a route6.
 *
 *  @param[in]  hRoute6
 *      The handle to the route6 object whose reference counter
 *      needs to be incremented. 
 *
 *  @retval
 *      Success -   Handle to the Interface
 *  @retval
 *      Error   -   0  
 */
void Rt6IncRefCount (HANDLE hRoute6)
{
    RT6_ENTRY*   ptr_rt6;

    /* Get the routing entry */
    ptr_rt6 = (RT6_ENTRY *)hRoute6;
    if (ptr_rt6 == NULL)
        return;

    /* Increment the reference count. */
    ptr_rt6->RefCount++;
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function checks if the route specified is 
 *      a default route?
 *
 *  @param[in]  hRoute6
 *      The handle to the ROUTE6 Object.
 *
 *  @retval
 *      Success -   1.
 *  @retval
 *      Error   -   0
 */
int Rt6IsDefaultRoute (HANDLE hRoute6)
{
    RT6_ENTRY* ptr_rt6;

    /* Get the routing entry. */
    ptr_rt6 = (RT6_ENTRY *)hRoute6;
    if (ptr_rt6 == NULL)
        return 0;

    /* Check if this is a default route? */
    if (Rt6FindDefaultRouter(ptr_rt6->NextHop, ptr_rt6->ptr_device))
        return 1;

    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function returns the Network Address associated
 *      with a route.
 *
 *  @param[in]  hRoute6
 *      The handle to the ROUTE6 Object.
 *  @param[out]  IPNet
 *      The handle to the Network Address to be returned.
 *
 *  @retval
 *      None
 */
void Rt6GetNetworkAddr (HANDLE hRoute6, IP6N* IPNet)
{
    RT6_ENTRY* ptr_rt6;

    /* Initialize the memory */
    mmZeroInit(IPNet, sizeof(IP6N));

    /* Get the routing entry. */
    ptr_rt6 = (RT6_ENTRY *)hRoute6;
    if (ptr_rt6 == NULL || IPNet == NULL)
        return;
    else
    {
        /* Copy the Network address from the route */
        mmCopy((void *)IPNet, (void *)&ptr_rt6->NetworkAddr, sizeof(IP6N));
        return;
    }
}

/** 
 *  @b Description
 *  @n  
 *      The function checks if the Router Address Matches an entry in
 *      the default Router List. 
 *
 *  @param[in]  RouterAddress
 *      The Default router address we are trying to find.
 *  @param[in]  ptr_device
 *      Device on which the default router is being searched. If specified
 *      as NULL; then the device is wildcarded and all default routes are
 *      searched.
 *
 *  @retval
 *      Match   -   Handle to the Default Router
 *  @retval
 *      No Match    -   0
 */
HANDLE Rt6FindDefaultRouter (IP6N RouterAddress, NETIF_DEVICE* ptr_device)
{
    RT6_ENTRY* ptr_rt6;

    /* Check if the default router already exists or not? So we cycle through the entire
     * routing table and check for a match? */
    ptr_rt6 = (RT6_ENTRY *)list_get_head ((LIST_NODE**)&gIPv6RoutingTable);
    while (ptr_rt6 != NULL)
    {
        /* Does the device match or is it wildcarded? */
        if ((ptr_device == NULL) || (ptr_rt6->ptr_device == ptr_device))
        {
            /* YES. Is this a default route? */
            if (ptr_rt6->Flags & FLG_RTE_GATEWAY)
            {
                /* YES; this is one... Does the IP Gateway Match? */
                if (IPv6CompareAddress(ptr_rt6->NextHop, RouterAddress) == 1)
                {
                    /* YES. We have a match? */
                    return (HANDLE)ptr_rt6;
                }
            }
        }

        /* Goto the next routing entry. */
        ptr_rt6 = (RT6_ENTRY *)list_get_next ((LIST_NODE*)ptr_rt6);
    }

    /* No match found. */
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function is used to update the ROUTE6 and corresponding LLI6 Entry. 
 *      This is called whenever a Neighbor Discovery Packet is received and the
 *      Target Address is meant for us. 
 *
 *  @param[in]  hRoute
 *      Handle to the route we need to update.
 *  @param[in]  RxPacketType
 *      Type of NDISC Packet received.
 *  @param[in]  mac_address
 *      MAC Address information if present from the NDISC Packet.
 *  @param[in]  Flags
 *      The flags field in the Received NA Header. Its set to 0 for all other packets.
 *  @param[in]  Lifetime
 *      New Lifetime value to be updated with valid only for RA. Else ignored in this
 *      function.
 *
 *  @retval
 *      Not Applicable
 */
void Rt6Update (HANDLE hRoute, UINT32 RxPacketType, UINT8* mac_address, UINT32 Flags, UINT32 Lifetime)
{
    RT6_ENTRY* ptr_rt6;

    /* Get the routing entry. */
    ptr_rt6 = (RT6_ENTRY *)hRoute;
    if (ptr_rt6 == NULL)
        return;

    /* If we received a Router Advertisment; we need to update the routing table entry too. */
    if (RxPacketType == ICMPV6_ROUTER_ADVERTISMENT)
        ptr_rt6->dwTimeout = llTimerGetTime(0) + Lifetime;

    /* If the MAC Address is specified; and there exists an LLI6 entry update it too. */
    LLI6Update (ptr_rt6->hLLI6, mac_address, RxPacketType, Flags);
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function replicates the IPv6 Routing Table
 *      and creates a duplicate copy which is then returned
 *      back to the callee. The replicated routing table list
 *      needs to be cleaned by the callee.
 *      This function is available to system developers and 
 *      can be called from outside kernel mode.
 *  @sa
 *      Route6CleanTable
 *
 *  @retval
 *      Head of the copy of the IPv6 Routing Table
 */
RT6_ENTRY* Rt6GetTable (void)
{
    RT6_ENTRY*  ptr_clonedRtList = NULL;

    /* Enter the kernel mode. */
    llEnter ();

    /* Replicate the routing table. */
    ptr_clonedRtList = (RT6_ENTRY *)list_replicate((LIST_NODE*)gIPv6RoutingTable, sizeof(RT6_ENTRY), 
                                                   mmAlloc, mmFree);

    /* Exit the kernel mode. */
    llExit ();

    /* Return the Cloned Routing Table. */
    return ptr_clonedRtList;
}

/**
 *  @b Description
 *  @n  
 *      The function is called to clean the memory allocated by a previous
 *      call to Route6GetTable. The function cleans the replicated copy 
 *      of the routing table.
 *      This function is available to system developers and 
 *      can be called from outside kernel mode.
 *  @sa
 *      Route6GetTable
 *
 *  @param[in]  ptr_list
 *      This is the head of the duplicate list which will be cleaned up.
 *
 *  @retval
 *      Not Applicable
 */
void Rt6CleanTable (RT6_ENTRY* ptr_list)
{
    /* Enter the kernel mode. */
    llEnter ();

    /* Cleanup the list. */
    list_clean( (LIST_NODE*)ptr_list, mmFree);

    /* Exit the kernel mode. */
    llExit ();
    return;
}

#endif /* _INCLUDE_IPv6_CODE */

