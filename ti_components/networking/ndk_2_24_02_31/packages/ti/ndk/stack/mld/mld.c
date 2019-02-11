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
 * ======== mld.c ========
 *
 * The file handles the Multicast Listner Discovery Protocol for IPv6
 *
 */


#include <stkmain.h>

#ifdef _INCLUDE_IPv6_CODE

/*********************************************************************
 * STRUCTURE NAME : MLD_MCAST_NODE
 *********************************************************************
 * DESCRIPTION   :
 *  The structure defines the Multicast Node. Since IPv6 operates on
 *  Multicast the node contains information about all the Multicast
 *  Groups which have been joined on an interface. 
 *********************************************************************/
typedef struct MLD_MCAST_NODE
{
    LIST_NODE       links;              /* Links to other Multicast Nodes */
    IP6N            MulticastAddress;   /* IPv6 Multicast Address Joined */
    NETIF_DEVICE*   ptr_device;         /* Device on which the address was joined */
}MLD_MCAST_NODE;

/**********************************************************************
 *************************** Global Variables *************************
 **********************************************************************/

/* This is a Global List which contains all the Multicast Addresses which are 
 * ACTIVE in the System. */
MLD_MCAST_NODE* gMLDNodeList = NULL;

/**********************************************************************
 *************************** MLD Functions ****************************
 **********************************************************************/

/** 
 *  @b Description
 *  @n  
 *      This function is used to create a Multicast Node.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  MulticastAddress
 *      IPv6 Multicast address being joined.
 *
 *  @param[in]  ptr_device
 *      The pointer to the NIMU Network Interface object over which the
 *      multicast address is being joined.
 *
 *  @retval
 *   Pointer to the new Multicast Node  -   Success
 *  @retval
 *   NULL                               -   Error
 */
static MLD_MCAST_NODE* MLDCreateMulticastNode (NETIF_DEVICE* ptr_device, IP6N MulticastAddress)
{
    MLD_MCAST_NODE* ptrMulticastNode;

    /* Allocate memory for the Multicast Node. */
    ptrMulticastNode = mmAlloc (sizeof(MLD_MCAST_NODE));
    if (ptrMulticastNode == NULL)
        return NULL;

    /* Initialize the allocated block of memory */
    mmZeroInit (ptrMulticastNode, sizeof(MLD_MCAST_NODE));

    /* Populate the structure and add to the list. */
    ptrMulticastNode->MulticastAddress = MulticastAddress;
    ptrMulticastNode->ptr_device       = ptr_device;

    /* Add it to the global list. */
    list_add ((LIST_NODE**)&gMLDNodeList, (LIST_NODE*)ptrMulticastNode);
    return ptrMulticastNode;
}

/** 
 *  @b Description
 *  @n  
 *      This function is used to delete a Multicast Node.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptrMulticastNode
 *      Pointer to the Multicast Node to be deleted from the system.
 *
 *  @retval
 *      Not Applicable.
 */
static void MLDDeleteMulticastNode (MLD_MCAST_NODE* ptrMulticastNode)
{
    /* Remove the Multicast Node from the global list. */
    list_remove_node ((LIST_NODE**)&gMLDNodeList, (LIST_NODE *)ptrMulticastNode);

    /* Cleanup the allocated block of memory */
    mmFree (ptrMulticastNode);
    return; 
}

/** 
 *  @b Description
 *  @n  
 *      This function is used to find the Multicast Node with the specific properties.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_device
 *      Pointer to the Network Interface object on which the multicast address would
 *      have been joined.
 *  @param[in]  MulticastAddress
 *      Multicast Address which needs to be searched
 *
 *  @retval
 *   Pointer to the new Multicast Node  -   Matching Entry Found
 *  @retval
 *   NULL                               -   No Match Found.
 */
static MLD_MCAST_NODE* MLDFindMulticastNode (NETIF_DEVICE* ptr_device, IP6N MulticastAddress)
{
    MLD_MCAST_NODE* ptrMulticastNode;

    /* Cycle through all the entries. */
    ptrMulticastNode = (MLD_MCAST_NODE *)list_get_head ((LIST_NODE**)&gMLDNodeList);
    while (ptrMulticastNode != NULL)
    {
        /* Do we have a match at the interface level? */
        if (ptrMulticastNode->ptr_device == ptr_device)
        {
            /* Match the IPv6 Address */
            if ((ptrMulticastNode->MulticastAddress.u.addr32[0] == MulticastAddress.u.addr32[0]) &&
                (ptrMulticastNode->MulticastAddress.u.addr32[1] == MulticastAddress.u.addr32[1]) &&
                (ptrMulticastNode->MulticastAddress.u.addr32[2] == MulticastAddress.u.addr32[2]) &&
                (ptrMulticastNode->MulticastAddress.u.addr32[3] == MulticastAddress.u.addr32[3]))
            {
                /* OK. We got a perfect match... */
                return ptrMulticastNode;
            }
        }
        /* Goto the next multicast node entry. */
        ptrMulticastNode = (MLD_MCAST_NODE *)list_get_next ((LIST_NODE*)ptrMulticastNode);
    }

    /* No Match Found. */
    return NULL; 
}

/** 
 *  @b Description
 *  @n  
 *      This function is called from the IPv6 Stack receive handler to verify if the
 *      address specified here has been joined or not?
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_device
 *      Pointer to the Network Interface object on which the IPv6 packet was rxed.
 *  @param[in]  multicast_address
 *      This is the IPAddress from the Destination field of the IPv6 Packet.
 *
 *  @retval
 *   1  -   Multicast Group has been joined 
 *  @retval
 *   0  -   The group has not been joined.
 */
int MLDTestGroup (NETIF_DEVICE* ptr_device, IP6N multicast_address)
{
    /* Check if the Multicast group exists or not? */
    if (MLDFindMulticastNode (ptr_device, multicast_address) == NULL)
        return 0;

    /* Multicast Group exists. */
    return 1;
}

/** 
 *  @b Description
 *  @n  
 *      This function is used to join a multicast group over a specific
 *      interface.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_device
 *      The pointer to the NIMU Network Interface object over which the
 *      multicast address is being joined.
 *
 *  @param[in]  multicast_address
 *      IPv6 Multicast address being joined.
 *
 *  @retval
 *   0  -   Success
 *  @retval
 *  <0  -   Error
 */
int MLDJoinGroup (NETIF_DEVICE* ptr_device, IP6N multicast_address)
{
    char    mcast_mac_address[6];

    /* Check if the address has already been joined. */
    if (MLDFindMulticastNode (ptr_device, multicast_address) != NULL)
    {
        /* The Multicast group has already been joined. Work is done. */
        return 0;
    }

    /* Convert the IPv6 Multicast Address to a multicast MAC Address.
     * The first two bytes of the MAC address is also 0x33 */
    mcast_mac_address[0] = 0x33;
    mcast_mac_address[1] = 0x33;

    /* The next 4 bytes of the MAC Address are copied from the 4 lower order
     * bytes of the Multicast IP Address. */
    mcast_mac_address[2] = multicast_address.u.addr8[12];
    mcast_mac_address[3] = multicast_address.u.addr8[13];
    mcast_mac_address[4] = multicast_address.u.addr8[14];
    mcast_mac_address[5] = multicast_address.u.addr8[15];

    /* Once we have the Multicast MAC Address; send the request to the NIMU
     * Network Interface Object and driver to join the multicast group. */
    if (ptr_device->ioctl(ptr_device, NIMU_ADD_MULTICAST_ADDRESS, (void*)&mcast_mac_address, 6) < 0)
    {
        /* Error: Device was unable to join the group... Recovery here to maybe move 
         * the device to promiscuous mode. */
        DbgPrintf (DBG_ERROR,
        "MLDJoinGroup: Error: Driver unable to join the multicast address\n");
        return -1;
    }

    /* Create a new MLD Node and add it to the list */
    if (MLDCreateMulticastNode (ptr_device, multicast_address) == NULL)
    {
        DbgPrintf (DBG_ERROR,
                "MLDJoinGroup: Error: Unable to create the MLD Node\n");
        return -1;
    }

    /* MLD Node has been created and the group has been joined succesfully. */
    return 0; 
}

/** 
 *  @b Description
 *  @n  
 *      This function is used to leave a multicast group over a specific
 *      interface.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_device
 *      The pointer to the NIMU Network Interface object over which the
 *      multicast address is being left.
 *
 *  @param[in]  multicast_address
 *      IPv6 Multicast address being left.
 *
 *  @retval
 *   0  -   Success
 *  @retval
 *  <0  -   Error
 */
int MLDLeaveGroup (NETIF_DEVICE* ptr_device, IP6N multicast_address)
{
    char            mcast_mac_address[6];
    MLD_MCAST_NODE* ptr_mcastNode;

    /* Check if the address exists over the interface or not? If not then
     * work is completed and there is nothing else to do. */
    ptr_mcastNode = MLDFindMulticastNode (ptr_device, multicast_address);
    if (ptr_mcastNode == NULL)
        return 0;

    /* Convert the IPv6 Multicast Address to a multicast MAC Address.
     * The first two bytes of the MAC address is also 0x33 */
    mcast_mac_address[0] = 0x33;
    mcast_mac_address[1] = 0x33;

    /* The next 4 bytes of the MAC Address are copied from the 4 lower order
     * bytes of the Multicast IP Address. */
    mcast_mac_address[2] = multicast_address.u.addr8[12];
    mcast_mac_address[3] = multicast_address.u.addr8[13];
    mcast_mac_address[4] = multicast_address.u.addr8[14];
    mcast_mac_address[5] = multicast_address.u.addr8[15];

    /* Once we have the Multicast MAC Address; send the request to the NIMU
     * Network Interface Object and driver to leave the multicast group. */
    ptr_device->ioctl(ptr_device, NIMU_DEL_MULTICAST_ADDRESS, (void*)&mcast_mac_address, 6);

    /* Delete the MLD Node*/
    MLDDeleteMulticastNode (ptr_mcastNode);

    /* Work has been completed successfully. */ 
    return 0; 
}

#endif /* _INCLUDE_IPv6_CODE */

