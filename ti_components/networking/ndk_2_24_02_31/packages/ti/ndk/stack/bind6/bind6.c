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
 * ======== bind6.c ========
 *
 * The file implements the BIND6 Module. The BIND6 Module is responsible
 * for keeping track of all LOCAL IPv6 Addresses which have been assigned
 * to the interfaces.
 *
 */


#include <stkmain.h>

#ifdef _INCLUDE_IPv6_CODE

/**********************************************************************
 *************************** Local Definitions ************************
 **********************************************************************/

/* Unique Messages: These are used to keep track of the various internal BIND6 TIMERS */
#define MSG_BIND6_LT_TIMER            (ID_BIND6*MSG_BLOCK + 1)
#define MSG_BIND6_NEED_DAD_TIMER      (ID_BIND6*MSG_BLOCK + 2)
#define MSG_BIND6_DAD_TIMER           (ID_BIND6*MSG_BLOCK + 3)

/**********************************************************************
 *************************** Global Variables *************************
 **********************************************************************/

/* The Global Bind6 List which keeps track of all the BIND6_ENTRY objects 
 * which have been VALIDATED and have passed the DAD Test. */
static BIND6_ENTRY*  gBind6List    = NULL;

/* The Global Bind6 List which keeps track of all the BIND6_ENTRY objects
 * which are currently executing the DAD Test. */
static BIND6_ENTRY*  gBind6DADList = NULL;

/* The BIND6_ENTRY Module maintains the following timers: 
 *  a) Lifetime Management Timer
 *      This is a very Slow Timer
 *      This is created as soon as the module initializes itself
 *  b) DAD Process
 *      This is a FAST Timer.
 *      Created on Demand; when there is DAD process to be executed. */
static HANDLE  hBind6LifetimeTimer = 0;
static HANDLE  hBind6DADTimer      = 0;

/**********************************************************************
 *************************** BIND6 Functions **************************
 **********************************************************************/

/** 
 *  @b Description
 *  @n  
 *      Internal Function which runs the DAD process on all entries 
 *      in the BIND6_ENTRY DAD List.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @retval
 *      0   -   No more elements in the DAD List
 *  @retval
 *      1   -   More elements in the DAD List.
 */
static int Bind6RunDAD (void)
{
    NETIF_DEVICE*     ptr_device;
    BIND6_ENTRY*      ptr_bind6;
    IP6N              DstAddress;

    /* Cycle through the DAD Info List. */
    ptr_bind6 = (BIND6_ENTRY *)list_get_head ((LIST_NODE **)&gBind6DADList);
    while (ptr_bind6 != NULL)
    {
        /* Get the interface handle on which the BIND6Object has been mappped. */
        ptr_device = ptr_bind6->ptr_device;

        /* All DAD Requests are sent out on the Multicast Solicited Address; here we
         * create this address. */
        DstAddress.u.addr32[0] = htonl (0xFF020000);
        DstAddress.u.addr32[1] = 0;
        DstAddress.u.addr32[2] = htonl(0x1);

        DstAddress.u.addr32[3] = ntohl(ptr_bind6->IPHost.u.addr32[3]);
        DstAddress.u.addr32[3] = 0xFF000000 | DstAddress.u.addr32[3];
        DstAddress.u.addr32[3] = htonl(DstAddress.u.addr32[3]);
        
        /* Send out the Neighbor solicitation */
        ICMPv6SendNS (ptr_device, DstAddress, IPV6_UNSPECIFIED_ADDRESS, ptr_bind6->IPHost);
            
        /* Decrement the number of probes transmitted. */
        ptr_bind6->NumProbes--;

        /* Are there more probes left; if not then remove the DAD Info Block. */
        if (ptr_bind6->NumProbes == 0)
        {
            /* DAD: SUCCESS
             *  We sent out all the DAD requests and we did not 
             *  receive any NA with our address. This means that we
             *  can move this address in the BIND6_ENTRY object to 
             *  permanent stage. */
            BIND6_ENTRY* ptrTmpNext = (BIND6_ENTRY *)list_get_next ((LIST_NODE *)ptr_bind6);

            /* Move the current address to PERMANENT State i.e. RESET the TENTATIVE Flag. */
            ptr_bind6->flags = ptr_bind6->flags & ~BIND6_TENTATIVE_ADDRESS;

            /* Ensure that there is an IPv6 Record on the device */
            if (ptr_device->ptr_ipv6device == NULL)
            {
                /* This is a FATAL Error and this condition should never arise. */
                DbgPrintf (DBG_ERROR, "Bind6RunDAD: Error: Executing DAD on interface %s with no IPv6 record",
                        ptr_device->name);
                return 1;
            }

            /* Increment DAD Success ICMPv6 stats */
            icmp6stats.DADSuccess++;

            /* Check if there is a registered call back routine to be invoked */
            if (ptr_device->ptr_ipv6device->DADStatus)
            {
                /* Call back functions are invoked outside kernel context */
                llExit ();
                ptr_device->ptr_ipv6device->DADStatus (ptr_bind6->IPHost, ptr_device->index, 1);
                llEnter();
            }

            /* Remove the BIND6_ENTRY Object from the DAD Process List and Add it to the PERMANENT
             * List. */
            list_remove_node ((LIST_NODE**)&gBind6DADList, (LIST_NODE*)ptr_bind6);
            list_cat ((LIST_NODE**)&gBind6List, (LIST_NODE**)&ptr_bind6);
            
            /* Remember the next entry. */
            ptr_bind6 = ptrTmpNext;
        }
        else
        {
            /* Get the next entry. */
            ptr_bind6 = (BIND6_ENTRY *)list_get_next ((LIST_NODE *)ptr_bind6);
        }
    }

    /* Is the DAD Process List Empty? If yes then we are no longer interested in the timer. */
    if (list_get_head ((LIST_NODE **)&gBind6DADList) == NULL)
        return 0;

    /* More DAD Entries to process; keep the timer alive? */
    return 1;
}

/** 
 *  @b Description
 *  @n  
 *      Run the BIND6_ENTRY Lifetime Management 
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @retval
 *      Not Applicable.
 */
static void Bind6LifetimeMgmt (void)
{
    BIND6_ENTRY*  ptr_bind6;
    UINT32        CurrentTime;

    /* Cycle through and run the Life Time Management */
    ptr_bind6 = (BIND6_ENTRY *)list_get_head ((LIST_NODE**)&gBind6List);
    while (ptr_bind6 != NULL)
    {
        /* Special Case: If the Lifetimes are INFINITE; there is nothing else to do. */
        if ((ptr_bind6->ValidLifetime == INFINITE_LT) && (ptr_bind6->PreferredLifetime == INFINITE_LT))
        {
            /* Goto the next element */
            ptr_bind6 = (BIND6_ENTRY *)list_get_next ((LIST_NODE*)ptr_bind6);
            continue;
        }

        /* Get a snapshot of the current time. */
        CurrentTime = llTimerGetTime(0);        

        /* Perform the preferred lifetime management; if it was specified. */
        if ((ptr_bind6->PreferredLifetime != INFINITE_LT) && (CurrentTime > ptr_bind6->PreferredLifetime))
        {
            /* YES. Preferred Lifetime has expired. */
            ptr_bind6->PreferredLifetime = 0;

            /* Deprecate the address. */
            ptr_bind6->flags = BIND6_DEPRECATED_ADDRESS;
        }

        /* Perform Valid Lifetime Management; if it was specified. */
        if ((ptr_bind6->ValidLifetime != INFINITE_LT) && (CurrentTime > ptr_bind6->ValidLifetime))
        {
            BIND6_ENTRY*  ptr_expiredBind6;
            
            /* YES. Valid Lifetime has expired; remove the BIND6 Entry from the list. 
             * Remember the expired entry. */
            ptr_expiredBind6 = ptr_bind6; 

            /* Get the next element. */
            ptr_bind6 = (BIND6_ENTRY *)list_get_next ((LIST_NODE*)ptr_bind6);

            /* Remove the expired element. */
            list_remove_node ((LIST_NODE**)&gBind6List, (LIST_NODE*)ptr_expiredBind6);

            /* Remove the bindings from the System. */
            Bind6Free (ptr_expiredBind6);

            /* This element has been handled. */
            continue;
        }

        /* Goto the next element. */
        ptr_bind6 = (BIND6_ENTRY *)list_get_next ((LIST_NODE*)ptr_bind6);
    }

    return;
}

/** 
 *  @b Description
 *  @n  
 *      Sevices intialization and resource messages for the BIND6 Module
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  Msg
 *      The message event which needs to be handled.
 *
 *  @retval
 *      Not Applicable.
 */
void Bind6Msg (uint Msg)
{
    switch( Msg )
    {
        /* System Initialization */
        case MSG_EXEC_SYSTEM_INIT:
        {
            /* Create the Lifetime Management Timer. */
            hBind6LifetimeTimer = TimerNew (&Bind6Msg, TIMER_TICKS_BIND6, MSG_BIND6_LT_TIMER);
            break;
        }
        /* System Shutdown */
        case MSG_EXEC_SYSTEM_SHUTDOWN:
        {
            /* System is shutting down. Shutdown all timers. */
            if (hBind6LifetimeTimer)
            {
                /* Close the timer */
                TimerFree (hBind6LifetimeTimer);
                hBind6LifetimeTimer = 0;
            }
            if (hBind6DADTimer)
            {
                /* Close the DAD timer. */
                TimerFree (hBind6DADTimer);
                hBind6DADTimer = 0;
            }
            break;
        }
        /* A message saying that the Lifetime management timer has expired. */
        case MSG_BIND6_LT_TIMER:
        {
            /* Run the Lifetime Management on all BIND6_ENTRY objects. */
            Bind6LifetimeMgmt ();
            break;      
        }
        /* A message saying we have new DAD timer is required; */
        case MSG_BIND6_NEED_DAD_TIMER:
        {
            if( hBind6DADTimer == 0)
                hBind6DADTimer = TimerNew (&Bind6Msg, 1, MSG_BIND6_DAD_TIMER);
            break;
        }
        /* Half Second Timer Tick */
        case MSG_BIND6_DAD_TIMER:
        {
            /* The DAD timer has expired execute; the DAD state machine on all pending objects */
            if( !Bind6RunDAD() )
            {
                /* We can shutdown the DAD Timer as there are no more objects left. */   
                TimerFree( hBind6DADTimer );
                hBind6DADTimer = 0;
            }
            break;
        }
    }
    return;
}

/** 
 *  @b Description
 *  @n  
 *      Trying to find the Host in a specific List.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_list
 *      The pointer to the list which will be searched.
 *
 *  @param[in]  ptr_device
 *      Pointer to the NIMU Network Interface object which has 
 *      to be searched for the IPv6 address.
 *
 *  @param[in]  IP
 *      IPv6 Address to be searched for.
 *
 *  @retval
 *   Match      -   Handle to the BIND6_ENTRY Object
 *  @retval
 *   No Match   -   0
 */
static HANDLE _Bind6FindByHostInList (LIST_NODE** ptr_list, NETIF_DEVICE* ptr_device, IP6N IP)
{
    BIND6_ENTRY*  ptr_bind6;

    /* Get the head of the list. */
    ptr_bind6 = (BIND6_ENTRY *)list_get_head (ptr_list);
    while (ptr_bind6 != NULL)
    {
        /* Match the interface handle if specified */
        if ((ptr_device == NULL) || (ptr_bind6->ptr_device == ptr_device))
        {
            /* Now we need to match the IPAddress specified. */
            if (IPv6CompareAddress (IP, ptr_bind6->IPHost) == 1)
                return (HANDLE)ptr_bind6;
        }

        /* Goto the next entry. */
        ptr_bind6 = (BIND6_ENTRY *)list_get_next ((LIST_NODE*)ptr_bind6);
    }

    /* Control comes here implies that there was no match */
    return 0;        
}

/** 
 *  @b Description
 *  @n  
 *      Find a binding by searching IF handle with IP Host addr
 *      This is an external NDK Stack API and is available to
 *      other modules. In this we search only addresses which
 *      have passed the DAD Procedure since these are VALID.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_device
 *      Pointer to the NIMU Network Interface object which has 
 *      to be searched for the IPv6 address.
 *
 *  @param[in]  IP
 *      IPv6 Address to be searched for.
 *
 *  @retval
 *      Match    -  Handle to the BIND6_ENTRY Object
 *  @retval
 *      No Match -  0
 */
HANDLE Bind6FindByHost (NETIF_DEVICE* ptr_device, IP6N IP)
{
    return _Bind6FindByHostInList ((LIST_NODE**)&gBind6List, ptr_device, IP);
}

/** 
 *  @b Description
 *  @n  
 *      Trying to find the IF handle with IP Net addr in a specific List.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_list
 *      The pointer to the list which will be searched.
 *
 *  @param[in]  ptr_device
 *      Pointer to the NIMU Network Interface object which has 
 *      to be searched for the IPv6 address.
 *
 *  @param[in]  IPNet
 *      IPv6 Network Address to be searched for.
 *
 *  @retval
 *   Match      - Handle to the BIND6_ENTRY Object 
 *  @retval
 *   No Match   - 0
 */
static HANDLE _Bind6FindByNetInList (LIST_NODE** ptr_list, NETIF_DEVICE* ptr_device, IP6N IPNet)
{
    BIND6_ENTRY*  ptr_bind6;

    /* Get the head of the list. */
    ptr_bind6 = (BIND6_ENTRY *)list_get_head (ptr_list);
    while (ptr_bind6 != NULL)
    {
        /* Match the interface handle if specified */
        if ((ptr_device == NULL) || (ptr_bind6->ptr_device == ptr_device))
        {
            /* Now we need to match the IPAddress specified. */
            if (IPv6CompareAddress (IPNet, ptr_bind6->IPNet) == 1)
                return (HANDLE)ptr_bind6;
        }

        /* Goto the next entry. */
        ptr_bind6 = (BIND6_ENTRY *)list_get_next ((LIST_NODE*)ptr_bind6);
    }

    /* Control comes here implies that there was no match */
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      Find a binding by searching IF handle with IP Net addr
 *      This is an external NDK Stack API and is available to
 *      other modules. In this we search only addresses which
 *      have passed the DAD Procedure since these are VALID.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_device
 *      Pointer to the NIMU Network Interface object which has 
 *      to be searched for the IPv6 address.
 *
 *  @param[in]  IPNet
 *      IPv6 Network Address we are searching for.
 *
 *  @retval
 *   Match      -   Handle to the BIND6_ENTRY Object
 *  @retval
 *   No Match   -   0
 */
HANDLE Bind6FindByNet (NETIF_DEVICE* ptr_device, IP6N IPNet)
{
    return _Bind6FindByNetInList ((LIST_NODE**)&gBind6List, ptr_device, IPNet);
}

/** 
 *  @b Description
 *  @n  
 *      The function is used to close an IPv6 binding.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  hbind6Obj
 *      The BIND6_ENTRY Object which is to be freed up.
 *
 *  @retval
 *      Not Applicable.
 */
void Bind6Free (HANDLE hbind6Obj)
{
    BIND6_ENTRY*  ptr_bind6;
    BIND6_ENTRY*  curr_bind_ptr;
    IP6N          SolictedNodeMulticastAddress;
    IP6N          Address;
    NETIF_DEVICE* ptr_device;
    int leavegroup = 1;

    /* Get the pointer to the object. */
    ptr_bind6 = (BIND6_ENTRY *)hbind6Obj;
    if (ptr_bind6 == NULL)
        return;

    /* Remember the address and device on which we are trying to delete the BINDING */
    Address    = ptr_bind6->IPHost;
    ptr_device = ptr_bind6->ptr_device;

    /*
     * Determine if we should keep or drop membership for the solicited node
     * multicast address/group (SNMCA) for the address we are removing.
     *
     * If removing link local address, then we want to leave the group
     */
    if (IPv6IsLinkLocal(Address)) {
        leavegroup = 1;
    }
    else {
        /*
         * Fix for SDOCM00101391
         *
         * Implement the following from RFC 4861:
         *
         * 7.2.1. Interface Initialization (page 61)
         *
         * "... Note that multiple unicast addresses may map into the same
         * solicited-node multicast address; a node MUST NOT leave the
         * solicited-node multicast group until all assigned addresses
         * corresponding to that multicast address have been removed."
         *
         * For example, both the link local address:
         *
         *    fe80::aa63:f2ff:fe00:491
         *
         * and the global address:
         *
         *    3ffe::1:aa63:f2ff:fe00:491
         *
         * will share the same SNMCA:
         *
         *    ff02::1:ff00:491
         *
         * Note the last 24 bits are the same in all 3 addresses (00:491)
         */

        /* Get the head of the global Bind6 list. */
        curr_bind_ptr = (BIND6_ENTRY *)list_get_head ((LIST_NODE**)&gBind6List);

        /* Search the list of bound addresses for a shared SNMCA */
        while (curr_bind_ptr != NULL)
        {
            /* Skip over the address we are removing */
            if (IPv6CompareAddress(Address, curr_bind_ptr->IPHost)) {
                /* Get the next bind entry. */
                curr_bind_ptr = (BIND6_ENTRY *)list_get_next((LIST_NODE*)curr_bind_ptr);
                continue;
            }

            /*
             * The lower 24 bits of an IPv6 address are used in computing the
             * corresponding SNMCA and group.  Therefore, two IPv6 addresses
             * will share the same SNMCA/group if their lower 24-bits are
             * equal.
             *
             * Compare lower 24 bits of link local address to those of the IP
             * address being rm'ed. First 8 bits are don't cares as they are
             * 0xFF in the solicited node mcast address.
             *
             * Both addresses should be in network byte order.
             */
            if (((curr_bind_ptr->IPHost.u.addr32[3] | htonl(0xFF000000)) &
                        (~(Address.u.addr32[3] | htonl(0xFF000000)))) == 0) {
                /*
                 * Found a match. Don't leave the group b/c this will kill
                 * SNMC communication with the matching address.
                 */
                leavegroup = 0;
                break;
            }

            /* Get the next bind entry. */
            curr_bind_ptr = (BIND6_ENTRY *)list_get_next((LIST_NODE*)curr_bind_ptr);
        }
    }

    /* Delete the Network and Local Routes which were created by the binding. */
    if (ptr_bind6->hRtNet) {
        Rt6Free(ptr_bind6->hRtNet);
    }
    if (ptr_bind6->hRtHost) {
        Rt6Free(ptr_bind6->hRtHost);
    }

    /* Close any sockets which are bound to the address which is being removed. */
    Sock6CleanPcb (SOCKPROT_TCP, Address);
    Sock6CleanPcb (SOCKPROT_UDP, Address);
    Sock6CleanPcb (SOCKPROT_RAW, Address);

    /* Remove the binding from the correct list. 
     * If the address was TENTATIVE remove from the DAD List else from the 
     * PERMANENT List. */
    if (ptr_bind6->flags & BIND6_TENTATIVE_ADDRESS)
        list_remove_node ((LIST_NODE**)&gBind6DADList, (LIST_NODE*)ptr_bind6);
    else
        list_remove_node ((LIST_NODE**)&gBind6List, (LIST_NODE*)ptr_bind6);

    /* Cleanup the memory of the BIND6_ENTRY object. */
    mmFree (ptr_bind6);
 
    if (leavegroup) {
        /* Now leave the Solicited Node Multicast Address. */
        SolictedNodeMulticastAddress.u.addr32[0] = htonl (0xFF020000);
        SolictedNodeMulticastAddress.u.addr32[1] = 0;
        SolictedNodeMulticastAddress.u.addr32[2] = htonl(0x1);

        SolictedNodeMulticastAddress.u.addr32[3] = ntohl(Address.u.addr32[3]);
        SolictedNodeMulticastAddress.u.addr32[3] =
                0xFF000000 | SolictedNodeMulticastAddress.u.addr32[3];
        SolictedNodeMulticastAddress.u.addr32[3] =
                htonl(SolictedNodeMulticastAddress.u.addr32[3]);

        MLDLeaveGroup (ptr_device, SolictedNodeMulticastAddress);
    }

    /* Work has been done. */
    return;
}

/** 
 *  @b Description
 *  @n  
 *      This function is used to create a new BIND6_ENTRY Object with the
 *      specified properties.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_device
 *      Pointer to the NIMU Network Interface object on which the BIND6_ENTRY
 *      object is to be created.
 *  @param[in]  IPHost
 *      IPv6 Address 
 *  @param[in]  IPMask
 *      IPv6 Mask
 *  @param[in]  ValidLifetime
 *      Valid Lifetime for which the address remains VALID
 *  @param[in]  PreferredLifetime
 *      Preferred Lifetime for which the address remains VALID
 *  @param[in]  IsAnycast
 *      Flag set to 1 if the address is an ANYCAST Address; else set to 0.
 *
 *  @retval
 *   Success    -   Handle to the new BIND6_ENTRY Object
 *  @retval
 *   Error      -   0
 */
HANDLE Bind6New 
(
    NETIF_DEVICE*   ptr_device, 
    IP6N            IPHost, 
    IP6N            IPMask, 
    UINT32          ValidLifetime, 
    UINT32          PreferredLifetime,
    UINT8           IsAnycast
)
{
    BIND6_ENTRY*  ptr_bind6;
    IP6N    NetworkAddress;
    HANDLE  hBind6Obj;
    IP6N    SolictedNodeMulticastAddress;

    /* Validate the arguments. */
    if (ptr_device == NULL)
    {
        DbgPrintf(DBG_ERROR,"Bind6New: Illegal Device Handle");
        return(0);
    }

    /* Multicast Address cannot be assigned to an interface */
    if (IPv6IsMulticast (IPHost) == 1)
        return 0;

    /* Compute the network address. */
    NetworkAddress.u.addr32[0] = IPHost.u.addr32[0] & IPMask.u.addr32[0];
    NetworkAddress.u.addr32[1] = IPHost.u.addr32[1] & IPMask.u.addr32[1];
    NetworkAddress.u.addr32[2] = IPHost.u.addr32[2] & IPMask.u.addr32[2];
    NetworkAddress.u.addr32[3] = IPHost.u.addr32[3] & IPMask.u.addr32[3];

    /* Check for duplicate bindings.
     * - Do we have another binding with the same IP address. */
    if (Bind6FindByHost (ptr_device, IPHost) != 0)
    {
        DbgPrintf(DBG_ERROR,"Bind6New: Duplicate Host Binding Detected");
        return(0);
    }

    /* Check for duplicate bindings.
     * - Do we have another binding which maps to the same Network. */
    if (Bind6FindByNet (ptr_device, NetworkAddress) != 0)
    {
        DbgPrintf(DBG_ERROR,"Bind6New: Duplicate Net Binding Detected");
        return(0);
    }

    /* Before we proceed; we also will check the DAD List; this is done because
     * if we are adding a duplicate address before the first request has completed the
     * DAD Process. This is not exactly an error but we return from here and dont create 
     * a new object. */
    hBind6Obj = _Bind6FindByHostInList ((LIST_NODE**)&gBind6DADList, ptr_device, IPHost);
    if (hBind6Obj != 0)
        return hBind6Obj;
    hBind6Obj = _Bind6FindByNetInList ((LIST_NODE**)&gBind6DADList, ptr_device, NetworkAddress);
    if (hBind6Obj != 0)
        return hBind6Obj;
    
    /* We are clear; lets go ahead and create the BINDING now. Allocate memory for it. */
    ptr_bind6 = mmAlloc (sizeof(BIND6_ENTRY));
    if (ptr_bind6 == NULL)
    {
        DbgPrintf(DBG_WARN,
        "Bind6New: Error: OOM: failed to create binding (alloc of %d bytes)",
                sizeof(BIND6_ENTRY));

        NotifyLowResource();
        return(0);
    }

    /* Initialize the allocated block. */
    mmZeroInit (ptr_bind6, sizeof(BIND6_ENTRY));

    /* Populate the structure. */
    ptr_bind6->ptr_device        = ptr_device;
    ptr_bind6->IPHost            = IPHost;
    ptr_bind6->IPMask            = IPMask;
    ptr_bind6->IPNet             = NetworkAddress;
    ptr_bind6->NumProbes         = 2;                   /* This should be picked from configuration... */

    /* Configure the Valid Lifetime. */
    if (ValidLifetime != INFINITE_LT)
        ptr_bind6->ValidLifetime     = llTimerGetTime (0) + ValidLifetime;
    else
        ptr_bind6->ValidLifetime     = INFINITE_LT;

    /* Configure the Preferred Lifetime. */
    if (PreferredLifetime != INFINITE_LT)
        ptr_bind6->PreferredLifetime = llTimerGetTime (0) + PreferredLifetime;
    else
        ptr_bind6->PreferredLifetime = INFINITE_LT;

    /* Create the Network Route for this BIND6_ENTRY Object. */
    ptr_bind6->hRtNet  = Rt6Create (FLG_RTE_CLONING, NetworkAddress, IPMask, IPV6_UNSPECIFIED_ADDRESS,
                                   NULL, ptr_device, ValidLifetime);
    if (!(ptr_bind6->hRtNet)) {
        /* Route creation failed. Clean up & return. (fix for SDOCM00101710) */
        DbgPrintf(DBG_WARN, "Bind6New: Error: failed to create network route.\n");
        mmFree(ptr_bind6);
        return(0);
    }

    /* Create the Local Host Route for this BIND6_ENTRY Object. */
    ptr_bind6->hRtHost = Rt6Create (FLG_RTE_HOST|FLG_RTE_IFLOCAL, ptr_bind6->IPHost, IPV6_HOST_MASK, 
                                    IPV6_UNSPECIFIED_ADDRESS, NULL, ptr_device, ValidLifetime);

    if (!(ptr_bind6->hRtHost)) {
        /* Route creation failed. Clean up & return. (fix for SDOCM00101710) */
        DbgPrintf(DBG_WARN, "Bind6New: Error: failed to create host route.\n");
        Rt6Free(ptr_bind6->hRtNet);
        mmFree(ptr_bind6);
        return(0);
    }

    /* Check if the Address is ANYCAST or UNICAST? 
     * NOTE: As per RFC 2462 Section 5.4 Duplicate Address Detection is not permitted on ANYCAST
     * and is required only for UNICAST Addresses. */
    if (IsAnycast == 0)
    {
        /* Set the flag indicating that the address is TENTATIVE. */
        ptr_bind6->flags = BIND6_TENTATIVE_ADDRESS;

        /* All TENTATIVE Addresses are added to the DAD Process List. */
        list_add ((LIST_NODE**)&gBind6DADList, (LIST_NODE*)ptr_bind6);

        /* Start the DAD Timer now. */
        Bind6Msg (MSG_BIND6_NEED_DAD_TIMER);
    }
    else
    {
        /* Address is ANYCAST; set the flag. */
        ptr_bind6->flags = BIND6_ANYCAST_ADDRESS;

        /* Add the BIND6_ENTRY Object to the Global BIND6_ENTRY Permanent Address List. */
        list_cat ((LIST_NODE**)&gBind6List, (LIST_NODE**)&ptr_bind6);
    }

    /* Join the Solicited Node Multicast Address for this BINDING Address. */
    SolictedNodeMulticastAddress.u.addr32[0] = htonl (0xFF020000);
    SolictedNodeMulticastAddress.u.addr32[1] = 0;
    SolictedNodeMulticastAddress.u.addr32[2] = htonl(0x1);

    SolictedNodeMulticastAddress.u.addr32[3] = ntohl(IPHost.u.addr32[3]);
    SolictedNodeMulticastAddress.u.addr32[3] =
            0xFF000000 | SolictedNodeMulticastAddress.u.addr32[3];
    SolictedNodeMulticastAddress.u.addr32[3] =
            htonl(SolictedNodeMulticastAddress.u.addr32[3]);

    if (MLDJoinGroup (ptr_device, SolictedNodeMulticastAddress) < 0)
    {
        /* Error: Unable to JOIN the Solicited Node Multicast Group; we cannot proceed 
         * forward without this... Abort and cleanup the BINDING! */
        DbgPrintf(DBG_ERROR, "Bind6New: Unable to JOIN the Solicited Node Multicast Group\n");
        Bind6Free (ptr_bind6);
        return 0;
    }

    /* Return the handle of the newly create BIND6_ENTRY object. */
    return (HANDLE)ptr_bind6;
}

/** 
 *  @b Description
 *  @n  
 *      The function is called by the ICMP6 Module to check if the
 *      received address passes or fails the DAD Check.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_device
 *      The pointer to the network interface device on which the
 *      DAD needs to be stopped.
 *
 *  @param[in]  TargetAddress
 *      The IP Address matching the Target Address in the NS/NA
 *      request.
 *
 *  @retval
 *      Success (No DAD Detected) - 0
 *  @retval
 *      Error (DAD Detected)      - <0
 */
int Bind6DADCheck (NETIF_DEVICE* ptr_device, IP6N TargetAddress)
{
    HANDLE hBind6Obj;

    /* Search for a match in the DAD List. */ 
    hBind6Obj = _Bind6FindByHostInList ((LIST_NODE**)&gBind6DADList, ptr_device, TargetAddress);
    if (hBind6Obj != 0)
    {
        /* The object exists in the DAD list implying that this was a tentative address; this is
         * DAD Failure and so we cleanup the BIND6_ENTRY Object and inform the world */ 
        Bind6Free (hBind6Obj);

        /* Ensure that there is an IPv6 Record on the device */
        if (ptr_device->ptr_ipv6device == NULL)
        {
            /* This is a FATAL Error and this condition should never arise. */
            DbgPrintf (DBG_ERROR, "Bind6DADCheck: Error: Executing DAD on interface %s with no IPv6 record",
                    ptr_device->name);
            return -1;
        }        

        /* Increment DAD Failure ICMPv6 stats */
        icmp6stats.DADFailures++;

        /* Check if there is a registered call back routine to be invoked */
        if (ptr_device->ptr_ipv6device->DADStatus)
        {
            /* Call back functions are invoked outside kernel context */
            llExit ();
            ptr_device->ptr_ipv6device->DADStatus (TargetAddress, ptr_device->index, 0);
            llEnter();
        }
        return -1;
    }

    /* Address looked good; or at least we were not running DAD on it. */
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function returns the interface handle given the BIND6_ENTRY
 *      object.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  hbind6Obj
 *      The BIND6_ENTRY Object whose interface handle we need.
 *
 *  @retval
 *   Success - Handle of the interface
 *  @retval
 *   Error   - 0
 */
NETIF_DEVICE* Bind6GetInterfaceHandle (HANDLE hbind6Obj)
{
    BIND6_ENTRY*  ptr_bind6;

    /* Get the pointer to the object. */
    ptr_bind6 = (BIND6_ENTRY *)hbind6Obj;
    if (ptr_bind6 == NULL)
        return 0;

    /* Return the interface handle. */
    return ptr_bind6->ptr_device;
}

/** 
 *  @b Description
 *  @n  
 *      The function searches the BIND6_ENTRY objects in the system for a specific
 *      interface.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_device
 *      The Network interface object whose BIND6_ENTRY Object we are interested in.
 *
 *  @retval
 *   Handle to the BIND6_ENTRY object
 */
HANDLE Bind6FindByIF (NETIF_DEVICE* ptr_device)
{
    BIND6_ENTRY*  ptr_bind6;

    /* Get the head of the list. */
    ptr_bind6 = (BIND6_ENTRY *)list_get_head ((LIST_NODE**)&gBind6List);
    while (ptr_bind6 != NULL)
    {
        /* Check if we have a match? */
        if (ptr_device && (ptr_bind6->ptr_device == ptr_device))
            return (HANDLE)ptr_bind6;

        /* Goto the next entry. */
        ptr_bind6 = (BIND6_ENTRY *)list_get_next ((LIST_NODE*)ptr_bind6);
    }

    /* There is no match. */
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function searches the BIND6 object and returns a LINK LOCAL Address
 *      for the device.  An Error Condition conveys the fact that there IPv6 
 *      has not been initialized on this interface. 
 *
 *  @param[in]  ptr_device
 *      The Network interface object whose LINK LOCAL Address is required.
 *  @param[out]  IPAddress
 *      The Link Local IP Address is returned
 *
 *  @retval
 *      Success -   0
 *  @retval      
 *      Error   -   -1
 */
int Bind6GetLinkLocalAddress(NETIF_DEVICE* ptr_device, IP6N* IPAddress)
{
    BIND6_ENTRY*  ptr_bind6;

    /* Validate the arguments. */
    if ((ptr_device == NULL) || (IPAddress == NULL))
        return -1;

    /* Initialize the Link Local Address */
    mmZeroInit((void *)IPAddress, sizeof(IP6N));

    /* Get the head of the list. */
    ptr_bind6 = (BIND6_ENTRY *)list_get_head ((LIST_NODE**)&gBind6List);
    while (ptr_bind6 != NULL)
    {
        /* Check if we have a match? */
        if((ptr_bind6->ptr_device == ptr_device) && (IPv6IsLinkLocal (ptr_bind6->IPHost) == 1))
        {
            /* FOUND it! */
            mmCopy ((void *)IPAddress, (void *)&ptr_bind6->IPHost, sizeof(IP6N));
            return 0;
        }

        /* Goto the next entry. */
        ptr_bind6 = (BIND6_ENTRY *)list_get_next ((LIST_NODE*)ptr_bind6);
    }

    /* Control comes here implies that there was no match */
    return -1;
}

/** 
 *  @b Description
 *  @n  
 *      The function searches the BIND6 object and returns a GLOBAL Address
 *      for the device. An Error Condition conveys the fact either IPv6 has not 
 *      been initialized on this interface or there is no GLOBAL Address configured 
 *      on the interface
 *
 *  @param[in]  ptr_device
 *      The Network interface object whose LINK LOCAL Address is required.
 *  @param[in]  IPNetworkAddr
 *      The Network Mask of the IP Address that needs to be retuned. 
 *  @param[out]  IPAddress
 *      The GLOBAL IP Address is returned
 *
 *  @retval
 *      Success -   0
 *  @retval     
 *      Error   -   -1
 */
int Bind6GetGlobalAddress(NETIF_DEVICE* ptr_device, IP6N IPNetworkAddr, IP6N* IPAddress)
{
    BIND6_ENTRY*  ptr_bind6;
    IP6N          NetworkAddress;

    /* Validate the arguments. */
    if ((ptr_device == NULL) || (IPAddress == NULL))
        return -1;

    /* Initialize the Globa Address */
    mmZeroInit((void *)IPAddress, sizeof(IP6N));

    /* Get the head of the list. */
    ptr_bind6 = (BIND6_ENTRY *)list_get_head ((LIST_NODE**)&gBind6List);
    while (ptr_bind6 != NULL)
    {
        /* Check if we have a match? */
        if((ptr_bind6->ptr_device == ptr_device) && (IPv6IsLinkLocal (ptr_bind6->IPHost) == 0))
        {
            /* Ok we might have a match; but we need to ensure that the address is 
             * not Deprecated. */
            if ((ptr_bind6->flags & BIND6_DEPRECATED_ADDRESS) == 0)
            {
                /* Compute the network address. */
                NetworkAddress.u.addr32[0] = IPNetworkAddr.u.addr32[0] & ptr_bind6->IPMask.u.addr32[0];
                NetworkAddress.u.addr32[1] = IPNetworkAddr.u.addr32[1] & ptr_bind6->IPMask.u.addr32[1];
                NetworkAddress.u.addr32[2] = IPNetworkAddr.u.addr32[2] & ptr_bind6->IPMask.u.addr32[2];
                NetworkAddress.u.addr32[3] = IPNetworkAddr.u.addr32[3] & ptr_bind6->IPMask.u.addr32[3];

                /* If an IP Network is specified, we need to find a bind6
                 * entry that matches it. If not specified, then we can
                 * return the first matching global address entry 
                 * bound to the device specified.
                 */
                if ((IPv6CompareAddress(IPNetworkAddr, IPV6_UNSPECIFIED_ADDRESS) == 1) ||
                    (IPv6CompareAddress (NetworkAddress, ptr_bind6->IPNet) == 1))
                {
                    /* Found a matching valid bind6 entry. Fill the IP address and return. */
                    mmCopy ((void *)IPAddress, (void *)&ptr_bind6->IPHost, sizeof(IP6N));
                    return 0;
                }
            }
        }

        /* Goto the next entry. */
        ptr_bind6 = (BIND6_ENTRY *)list_get_next ((LIST_NODE*)ptr_bind6);
    }

    /* Control comes here implies that there was no match */
    return -1;
}

/** 
 *  @b Description
 *  @n  
 *      The function returns the IPv6 address matching the BIND6_ENTRY object.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_device
 *      The Network interface object whose IPv6 Address we are interested in.
 *
 *  @retval
 *   Success - The IPv6 Address matching the interface 
 *  @retval
 *   Error   - IPV6_UNSPECIFIED_ADDRESS (::)
 */
IP6N Bind6IF2IPHost (NETIF_DEVICE* ptr_device)
{
    BIND6_ENTRY *ptr_bind6;

    /* First get the BIND6_ENTRY Object */
    ptr_bind6 = (BIND6_ENTRY *)Bind6FindByIF (ptr_device);
    if (ptr_bind6 == NULL)
    {
        /* Return the UNSPECIFIED address. */
        return IPV6_UNSPECIFIED_ADDRESS;
    }

    /* Return the address of the interface. */
    return (ptr_bind6->IPHost);
}

/** 
 *  @b Description
 *  @n  
 *      The function returns the Lifetime matching the BIND6_ENTRY object.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  hbind6Obj
 *      Handle to the BIND6_ENTRY object whose lifetime we need to get
 *
 *  @retval
 *      Lifetime value associated with the BIND6_ENTRY object.
 */
UINT32 Bind6GetLifetime (HANDLE hbind6Obj)
{
    BIND6_ENTRY*  ptr_bind6;

    /* Get the pointer to the object. */
    ptr_bind6 = (BIND6_ENTRY *)hbind6Obj;
    if (ptr_bind6 == NULL)
        return 0;

    /* Return the Lifetime value associated with the object. */
    return ptr_bind6->ValidLifetime;
}

/** 
 *  @b Description
 *  @n  
 *      The function sets the Lifetime matching the BIND6_ENTRY object.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  hbind6Obj
 *      Handle to the BIND6_ENTRY object whose lifetime we need to get
 *  @param[in]  Lifetime
 *      New Lifetime value to be associated.
 *
 *  @retval
 *      Not Applicable.
 */
void Bind6SetLifetime (HANDLE hbind6Obj, UINT32 Lifetime)
{
    BIND6_ENTRY*  ptr_bind6;

    /* Get the pointer to the object. */
    ptr_bind6 = (BIND6_ENTRY *)hbind6Obj;
    if (ptr_bind6 == NULL)
        return;

    /* Set the Lifetime value associated with the object. */
    ptr_bind6->ValidLifetime = Lifetime;
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function replicates the BIND6 Table and creates a duplicate copy 
 *      which is then returned back to the callee. The replicated BIND table list
 *      needs to be cleaned by the callee. 
 *      This function is available to system developers and  can be called 
 *      from outside kernel mode.
 *  @sa
 *      Bind6CleanTable
 *
 *  @retval
 *      Head of the copy of the BIND6
 */
BIND6_ENTRY* Bind6GetTable (void)
{
    BIND6_ENTRY*  ptr_clonedList = NULL;

    /* Enter the kernel mode. */
    llEnter ();

    /* Replicate the routing table. */
    ptr_clonedList = (BIND6_ENTRY *)list_replicate((LIST_NODE*)gBind6List, sizeof(BIND6_ENTRY), 
                                                   mmAlloc, mmFree);

    /* Exit the kernel mode. */
    llExit ();

    /* Return the Cloned Bind Table. */
    return ptr_clonedList;
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
 *      Bind6GetTable
 *
 *  @param[in]  ptr_list
 *      This is the head of the duplicate list which will be cleaned up.
 *
 *  @retval
 *      Not Applicable
 */
void Bind6CleanTable (BIND6_ENTRY* ptr_list)
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

