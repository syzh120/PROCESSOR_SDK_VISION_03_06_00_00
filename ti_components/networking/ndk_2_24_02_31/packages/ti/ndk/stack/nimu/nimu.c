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
 * ======== nimu.c ========
 *
 * Implements the network interface management code. This is required when
 * the NDK Core stack has been built to be able to handle multiple drivers.
 * The file has the code which resides in the data path.
 *
 */

#include <stkmain.h>

/*********************************************************************
 * STRUCTURE NAME : NIMU_MCB
 *********************************************************************
 * DESCRIPTION   :
 *  The structure keeps track of all the information which is required
 *  by the Network Interface Management Unit (NIMU)
 *********************************************************************/
typedef struct NIMU_MCB
{
    NETIF_DEVICE devices;      /* Device List.          */    
    int          header_size;  /* L2 Rsvd. Header Size  */
    int          trailer_size; /* L2 Rsvd. Trailer Size */
}NIMU_MCB;

/* This is the NIMU Master Control block. */
NIMU_MCB    nimu_mcb;

/** 
 *  @b Description
 *  @n    
 *      The function is the interface routine which is called to send 
 *      a packet via the registered the NIMU Network Interface Object.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  hIF             
 *      Handle of the NIMU Network interface object on which the packet 
 *      will be transmitted.
 *  @param[in]  pPkt            
 *      Handle to the packet which needs to be sent
 *  @retval
 *   Not Applicable.
 */
void NIMUSendPacket (HANDLE hIF, PBM_Pkt *pPkt)
{
    NETIF_DEVICE*   ptr_device;

    /* Get the NIMU Network Interface object. */
    ptr_device = (NETIF_DEVICE *)hIF;

    /* Pass the packet to the driver through the registered 'send' function. */
    if (ptr_device->send (ptr_device, (PBM_Handle)pPkt) < 0)
    {
        /* Driver reported an error and was unable to transmit the packet. 
         * The NIMU will clean the packet memory. */
        PBM_free( (PBM_Handle)pPkt );
        return;
    }
    return;
}

/** 
 *  @b Description
 *  @n    
 *      The function is used to add an appropriate layer2 header as 
 *      specified by the NIMU object. This function is called when the
 *      packet is passed down from layer3 to layer2 and is used to prep
 *      the packet by adding the correct layer2 header. 
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_device      
 *      The NIMU Network interface object on which the packet will be 
 *      transmitted and which is used to tag the correct L2 header.
 *  @param[in]  hPkt            
 *      Handle to the packet which will be sent out and on which the L2 
 *      header is added.
 *  @param[in]  dst_mac         
 *      The Dst MAC Address to be added on the packet
 *  @param[in]  src_mac         
 *      The Src MAC Address to be added on the packet
 *  @param[in]  protocol         
 *      The 'Protocol' tag which needs to be appended.
 *
 *  @retval
 *   0  -   Success
 *  @retval
 *   <0  -  Error
 */
int NIMUAddHeader 
(
    NETIF_DEVICE* ptr_device, 
    HANDLE        hPkt, 
    UINT8*        dst_mac, 
    UINT8*        src_mac, 
    UINT16        protocol
) 
{
    /* Did the interface have a Layer2 Header function? */ 
    if (ptr_device->add_header)
    {
        /* Pass the packet to the interface to add the layer2 header. */
        if (ptr_device->add_header(ptr_device, hPkt, dst_mac, src_mac, protocol) < 0)
            return -1;
    }
    
    /* Done. No errors detected. */
    return 0;
}

/** 
 *  @b Description
 *  @n    
 *      The function is called by the NDK Net Scheduler to service all
 *      NIMU Network Interface objects registered in the system. This 
 *      is called when the NDK scheduler detects that a packet has been
 *      received by the lower HAL drivers and needs to be serviced.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @retval
 *   Not Applicable.
 */
void NIMUPacketService (void)
{
    NETIF_DEVICE*   ptr_device;

    /* Get the head of the list. */
    ptr_device = (NETIF_DEVICE *)list_get_head ((LIST_NODE**)&nimu_mcb.devices);
    while (ptr_device != NULL)
    {
        /* Poll the network device */
        if (ptr_device->pkt_service)
            ptr_device->pkt_service(ptr_device);

        /* Go to the next element. */
        ptr_device = (NETIF_DEVICE*)list_get_next ((LIST_NODE*)ptr_device);
    }
    return;
}

/** 
 *  @b Description
 *  @n    
 *      The function is called by the NDK Net Scheduler to allow HAL
 *      drivers to be able to perform 'periodic' activities; such as
 *      Ethernet Link management. There also exists a mode in which
 *      the HAL drivers can execute in 'polled' mode. In this case this
 *      the HAL drivers do not use 'interrupts' and are polled by the
 *      NDK Net Scheduler to check for transmit/receive activity. 
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  fEvents      
 *      This is set to 1 if the function is invoked by the NDK Net 
 *      Scheduler because of a timer tick. Set to 0 otherwise. This flag is 
 *      available to the HAL drivers to determine the source of the function
 *      invocation.
 *
 *  @retval
 *   Not Applicable.
 */
void NIMUPacketServiceCheck (int fEvents)
{
    NETIF_DEVICE*   ptr_device;

    /* Get the head of the list. */
    ptr_device = (NETIF_DEVICE *)list_get_head ((LIST_NODE**)&nimu_mcb.devices);
    while (ptr_device != NULL)
    {
        /* Poll the network device */
        if (ptr_device->poll)
            ptr_device->poll(ptr_device, fEvents);

        /* Go to the next element. */
        ptr_device = (NETIF_DEVICE*)list_get_next ((LIST_NODE*)ptr_device);
    }
    return;
}

/** 
 *  @b Description
 *  @n  
 *      This routine is the API interface routine which needs to be
 *      invoked by the drivers to pass the packet up the NDK core stack
 *      The function takes the raw packet received from the MAC device, 
 *      and validates the link level related data. Packets are passed
 *      up the stack on the basis of the 'protocol' field. 
 *
 *  @param[in]  hPkt      
 *      Handle to the packet which is to be passed up the NDK stack.
 *
 *  @retval
 *   -1     -   Error
 *  @retval
 *   0      -   Success
 */
int NIMUReceivePacket (PBM_Handle hPkt)
{
    PBM_Pkt*      ptr_pkt = (PBM_Pkt *)hPkt;
    uint          Type;
    ETHHDR*       ptr_eth_header;
	int			  retVal;


    /* Make sure we received a valid packet. */
    if (ptr_pkt == NULL)
        return -1;

    /* Basic validations: The received packet should conform to the Ethernet standards */
    if((ptr_pkt->ValidLen < ETH_MIN_PAYLOAD) || (ptr_pkt->ValidLen > ETH_MAX_PAYLOAD))
    {
        DbgPrintf(DBG_WARN,"NIMUReceivePacket: Bad Size; Payload is %d bytes", ptr_pkt->ValidLen);
        PBM_free(ptr_pkt);
        return -1;
    }

    /* Get the pointer to the Ethernet Header. */
    ptr_eth_header = (ETHHDR *) (ptr_pkt->pDataBuffer + ptr_pkt->DataOffset);

    /* Set the flags to indicate the type of packet: Unicast, Broadcast or Multicast */
    if (ptr_eth_header->DstMac[0] & 0x1)
    {
        /* The packet is either a multicast or broadcast packet. */
        if (ptr_eth_header->DstMac[1] == 0xFF)
            ptr_pkt->Flags |= FLG_PKT_MACBCAST;
        else
            ptr_pkt->Flags |= FLG_PKT_MACMCAST;
    }

    /* Use the type field to determine which */
    Type = ntohs (ptr_eth_header->Type);

    /* Adjust the packet to point to past Ethernet and set the fields in the packet structure. */
    ptr_pkt->ValidLen   -= ETHHDR_SIZE;
    ptr_pkt->DataOffset += ETHHDR_SIZE;
    ptr_pkt->EtherType   = Type;
    ptr_pkt->L2HdrLen    = ETHHDR_SIZE;

    /* Check if the packet type is a VLAN packet. */
    if (Type == 0x8100)
        Type = VLANReceivePacket (hPkt);

    /* Dispatch the Packet to the appropriate protocol layer. */
    switch( Type )
    {
        case 0x800:
        {
            /* Received packet is an IP Packet. */
            IPRxPacket( ptr_pkt );
            break;
        }
        case 0x806:
        {
            /* Received packet is an ARP Packet. */
            LLIRxPacket( ptr_pkt );
            break;
        }
#ifdef _INCLUDE_PPPOE_CODE
        case ETHERTYPE_PPPOE_CTRL:
        case ETHERTYPE_PPPOE_DATA:
        {
            /* Received packet is a PPP Packet (control or data) */
            pppoeInput( ptr_pkt );
            break;
        }
#endif
#ifdef _INCLUDE_IPv6_CODE
        case 0x86DD:
        {
            IPv6RxPacket (ptr_pkt);
            break;
        }
#endif

        default:
        {
            /* Pass up the packet to Raw Ethernet Packet
             * Handler Object.
             */
            retVal = RawEthRxPacket (ptr_pkt);

            /* No Raw ethernet channel found matching the
             * ethernet type in the packet/invalid packet. 
             * Free the packet.
             */
            if (retVal != 0)
            {
                /* Unrecognized packet; drop the packet */
            PBM_free( ptr_pkt );
            break;
            }
        }
    }

    /* Work has been completed. */
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function is a generic utility function which creates a packet
 *      that is used for transmission on any network interface object which
 *      has been registered with the NIMU. The packet allocated has 'header'
 *      and 'trailer' padding added.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  packet_size      
 *      Size of the packet which needs to be allocated.
 *
 *  @retval
 *   Handle to the packet   -   Success
 *  @retval
 *   NULL                   -   Error
 */
PBM_Pkt* NIMUCreatePacket (uint packet_size)
{
    PBM_Pkt *pPkt;

    /* Verify legal Ethernet size range */
    if( packet_size < ETH_MIN_PAYLOAD )
        packet_size = ETH_MIN_PAYLOAD;

    /* Ensure that we account for the header and trailer sizes */ 
    packet_size += nimu_mcb.header_size + nimu_mcb.trailer_size;

    /* Allocate the packet */
    pPkt = PBM_alloc(packet_size);
    if (pPkt == NULL)
        return NULL;

    /* Offset the data pointer to leave enough space for the Layer2 header. */
    pPkt->DataOffset = nimu_mcb.header_size;

    /* Return the packet. */
    return (pPkt);
}

/** 
 *  @b Description
 *  @n  
 *      The function is a UTILITY function which is provided for use
 *      to driver authors if the driver is a simple Ethernet driver.
 *      Driver Authors should initialize the 'add_header' field of the
 *      NIMU Network Interface object to this function.
 *
 *      This will ensure that all packets passed to the driver are 
 *      pre-pended with the correct layer2 ethernet header before they
 *      are transmitted. Failure to do will cause no Layer2 headers to
 *      be added. 
 *
 *  @param[in]  ptr_net_device      
 *      The NIMU Network interface object on which the packet will be 
 *      transmitted and which is used to tag the correct L2 header.
 *  @param[in]  hPkt            
 *      Handle to the packet which will be sent out and on which the L2 
 *      header is added.
 *  @param[in]  dst_mac         
 *      The Dst MAC Address to be added on the packet
 *  @param[in]  src_mac         
 *      The Src MAC Address to be added on the packet
 *  @param[in]  ether_type         
 *      The 'Protocol' tag which needs to be appended.
 *
 *  @retval
 *   0   -   Success
 *  @retval
 *   <0  -   Error
 */
int NIMUAddEthernetHeader 
(
    NETIF_DEVICE* ptr_net_device, 
    PBM_Handle    hPkt, 
    UINT8*        dst_mac, 
    UINT8*        src_mac, 
    UINT16        ether_type
)
{
    PBM_Pkt* pPkt = (PBM_Pkt *)hPkt;
    ETHHDR*  pEthHdr;

    /* Get the pointer to the packet. */
    pPkt = (PBM_Pkt *)hPkt;
    if (pPkt == NULL)
        return -1;

    /* Check if there is sufficient space to add the header 
     * If not then this is a fatal error; we should always have sufficient space
     * allocated at the head of the packet to account for a Layer2 header. 
     * Report this to the world. */
    if (pPkt->DataOffset < ETHHDR_SIZE)
    {
        DbgPrintf(DBG_ERROR,"NIMUAddEtherHeader: No space for Ethernet header");
        return -1;
    }

    /* Back up to make room for Ethernet Layer2 header */
    pPkt->DataOffset -= ETHHDR_SIZE;

    /* Get a pointer to the space reserved for the layer2 header. */
    pEthHdr = (ETHHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* If a source mac address was specified; use it instead */
    if (src_mac == NULL)
        mmCopy (pEthHdr->SrcMac, ptr_net_device->mac_address, 6);
    else
        mmCopy (pEthHdr->SrcMac, src_mac, 6);

    /* Copy the destination MAC address as is. */
    mmCopy (pEthHdr->DstMac, dst_mac, 6);

    /* Configure the type in network order. */
    pEthHdr->Type = HNC16(ether_type);

    /* Increment the length to account for the Ethernet Header just added. */
    pPkt->ValidLen = pPkt->ValidLen + ETHHDR_SIZE;
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function gets the number of NIMU Network Interface Objects 
 *      currently active in the system.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @retval
 *      Number of NIMU objects in the system.
 */
static UINT16 NIMUGetNumOfObject (void)
{
    UINT16          count = 0;
    NETIF_DEVICE*   ptr_device;

    /* Get the head of the list. */
    ptr_device = (NETIF_DEVICE *)list_get_head ((LIST_NODE**)&nimu_mcb.devices);
    while (ptr_device != NULL)
    {
        /* Increment the count. */
        count++;

        /* Go to the next element. */
        ptr_device = (NETIF_DEVICE*)list_get_next ((LIST_NODE*)ptr_device);
    }

    /* Return the number of network interface objects detected. */
    return count;        
} 

/** 
 *  @b Description
 *  @n  
 *      The function searches the NIMU database and finds an entry matching
 *      the device 'index'
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  index      
 *      The device index we are trying to locate.
 *
 *  @retval
 *   NIMU Network Interface Object   -   Matching entry found.
 *  @retval
 *   NULL                            -   No Match
 */
NETIF_DEVICE* NIMUFindByIndex (uint index)
{
    NETIF_DEVICE*   ptr_device;

    /* Get the head of the list. */
    ptr_device = (NETIF_DEVICE *)list_get_head ((LIST_NODE**)&nimu_mcb.devices);
    while (ptr_device != NULL)
    {
        /* Did we get the match? */
        if (ptr_device->index == index)
            return ptr_device;

        /* Go to the next element. */
        ptr_device = (NETIF_DEVICE*)list_get_next ((LIST_NODE*)ptr_device);
    }

    /* No matching entry found. */
    return NULL;
}

/** 
 *  @b Description
 *  @n  
 *      The function searches the NIMU database and finds an entry matching
 *      the device 'name'
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  name      
 *      The device name we are trying to locate.
 *
 *  @retval
 *   NIMU Network Interface Object   -   Matching entry found.
 *  @retval
 *   NULL                            -   No Match
 */
NETIF_DEVICE* NIMUFindByName (char* name)
{
    NETIF_DEVICE*   ptr_device;

    /* Get the head of the list. */
    ptr_device = (NETIF_DEVICE *)list_get_head ((LIST_NODE**)&nimu_mcb.devices);
    while (ptr_device != NULL)
    {
        /* Did we get the match? */
        if (strcmp(ptr_device->name, name) == 0)
            return ptr_device;

        /* Go to the next element. */
        ptr_device = (NETIF_DEVICE*)list_get_next ((LIST_NODE*)ptr_device);
    }

    /* No matching entry found. */
    return NULL;
}

/** 
 *  @b Description
 *  @n  
 *      The function is used to allocate a new 'unique' device index.
 *      Device indexes allocated for a NIMU Network Interface object
 *      should be unique. The API uses the 'index' specified by the
 *      driver registering the NIMU object as a starting seed. 
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  start_index      
 *      The device index specified in the NIMU Object by the driver
 *
 *  @retval
 *  Unique Device Index         -   Success
 *  @retval
 *  NIMU_DEFAULT_MAX_DEVICE     -   Error
 */
static uint NIMUAllocateIndex (uint start_index)
{
    uint num_tries = 0;

    do 
    {
        /* If the specified index exceeds the MAX permissible then restart
         * the search. */
        if ((start_index >= NIMU_DEFAULT_MAX_DEVICE) || (start_index == 0))
            start_index = 1;

        /* Check if there exists a device with the specific index. 
         * If there is no matching device then we can use this index. */
        if (NIMUFindByIndex(start_index) == NULL)
            return start_index;

        /* Device exists so we need to move ahead to the next slot. */
        start_index++;

        /* Increment the number of tries. */
        num_tries++;
    }while (num_tries != NIMU_DEFAULT_MAX_DEVICE);

    /* If control comes here then this implies that there we exceeded 
     * the max allowed number of devices in the system. */
    return NIMU_DEFAULT_MAX_DEVICE;
}

/** 
 *  @b Description
 *  @n  
 *      The function is used to allocate a new 'unique' device name.
 *      Device names allocated for a NIMU Network Interface object
 *      should be unique. The API uses the 'name' specified by the
 *      driver registering the NIMU object as a starting seed. 
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  name      
 *      The device name specified in the NIMU Object by the driver
 *
 *  @retval
 *  Unique Device Name  -   Success
 *  @retval
 *  NULL                -   Error
 */
static char* NIMUAllocateName (char* OrgName, char* NewName)
{
    uint    num_tries = 0;

    /* Start with the specified name. */
    strcpy (NewName, OrgName);

    do 
    {
        /* Check if there exists a device with the specific name. 
         * If there is no matching device then we can use this name. */
        if (NIMUFindByName(NewName) == NULL)
            return NewName;

        /* Device exists so we need to move ahead to the next slot. */
        NDK_sprintf (NewName, "%s:%d", OrgName, num_tries+1); 

        /* Increment the number of tries. */
        num_tries++;
    }while (num_tries != NIMU_DEFAULT_MAX_DEVICE);

    /* If control comes here then this implies that there we exceeded 
     * the max allowed number of devices in the system. */
    return NULL;
} 

/** 
 *  @b Description
 *  @n  
 *      This API is used by driver authors to register a network device
 *      with the NDK Network Interface Management Unit. The function 
 *      verifies the arguments, checks for duplicates and adds the device
 *      to NIMU (Network Interface Management Unit)
 *
 *  @param[in]  ptr_netif_device      
 *      The NIMU Network Interface Object to be registered.
 *
 *  @retval
 *  0       -   Success
 *  @retval
 *  <0      -   Error
 */
int NIMURegister (NETIF_DEVICE* ptr_netif_device)
{
    char Name[MAX_INTERFACE_NAME_LEN];

    /* Validate the arguments */
    if (ptr_netif_device == NULL)
        return -1;

    /* The driver should support some of the basic operations. */
    if ((ptr_netif_device->start == NULL) || (ptr_netif_device->stop == NULL) ||
        (ptr_netif_device->send  == NULL))
    {
        /* These are the basic operations and we cannot proceed without these operations. */
        return -1;
    }

    /* Allocate a unique device index. */
    ptr_netif_device->index = NIMUAllocateIndex (ptr_netif_device->index);
    if (ptr_netif_device->index == NIMU_DEFAULT_MAX_DEVICE)
        return -1;

    /* Ensure that the device name is unique. */
    if (NIMUAllocateName (ptr_netif_device->name, &Name[0]) == NULL)
        return -1;

    /* Copy the 'unique' device name to the Network Interface Device */
    strcpy (ptr_netif_device->name, Name);

    /* The device can now be opened and initialized. */
    if (ptr_netif_device->start (ptr_netif_device) < 0)
        return -1;

    /* Increment the reference counter. */
    ptr_netif_device->RefCount++;

    /* NOTES: For backwards compatibility; we set the type to either PPP or ETHER
     * depending on the 'flag' definition. This field will be obsoleted in the future. */
    if (ptr_netif_device->flags & NIMU_DEVICE_NO_ARP)
        ptr_netif_device->type = HTYPE_PPP;
    else
        ptr_netif_device->type = HTYPE_ETH;

    /* The device is now up and ready. */
    ptr_netif_device->flags = ptr_netif_device->flags | NIMU_DEVICE_UP;

    /* Device has been successfully started so add it to the device list. */
    list_add ((LIST_NODE**)&nimu_mcb.devices, (LIST_NODE *)ptr_netif_device);
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      This API is used by driver authors to unregister and stop the 
 *      network device from the NIMU. The device should have been registered 
 *      with the NIMU.
 *
 *  @param[in]  ptr_netif_device      
 *      The NIMU Network Interface Object to be unregistered.
 *
 *  @retval
 *  0       -   Success
 *  @retval
 *  <0      -   Error, where Error can be:
 *
 *  -1      -   Invalid argument passed
 *  -2      -   Device name does not match device instance
 *  -3      -   Device not stopped due to non-zero reference count
 *  -4      -   Device not registered with NIMU
 *
 */
int NIMUUnregister (NETIF_DEVICE* ptr_netif_device)
{
    NETIF_DEVICE*   ptr_device;
    int deviceFlags = 0;

    /* Validate the arguments */
    if (ptr_netif_device == NULL)
        return -1;

    /* Make sure that the device has been registered with the NIMU. */
    ptr_device = NIMUFindByName (ptr_netif_device->name);
    if (ptr_device != NULL)
    {
        /* Make sure we got the same node as what we are trying to delete */
        if (ptr_device != ptr_netif_device)
            return -2;

        /*
         * Decrement the reference counter as we are now trying to 'stop' the
         * interface
         */
        ptr_netif_device->RefCount--;
        if (ptr_netif_device->RefCount == 0)
        {
            /* Rm this device from the list b/c it might get freed in stop() */
            list_remove_node ((LIST_NODE**)&nimu_mcb.devices,
                    (LIST_NODE *)ptr_netif_device);

            /* Save the value of flags, as stop() may free the device */
            deviceFlags = ptr_netif_device->flags;

            /* No more references detected; stop the device. */
            ptr_netif_device->stop (ptr_netif_device);

            /*
             * Fix for SDOCM00103411
             *
             * Allow driver to control the means of allocation for the NIMU
             * device instance.  If 'flags' does not have the
             * NIMU_DEVICE_NO_FREE bit set, then this works exactly as it did
             * previously (calls mmFree(), which forces the driver to allocate
             * the device instance using mmAlloc()).
             *
             * If 'flags' has NIMU_DEVICE_NO_FREE bit set, then
             * don't call mmFree() here.  In this case, driver is responsible
             * for allocation and clean up of device instances.
             */
            if (!(deviceFlags & NIMU_DEVICE_NO_FREE)) {
                /* Cleanup the memory */
                mmFree (ptr_netif_device);
            }
        }
        else {
            /* RefCount still not zero, cannot stop/free device instance yet */
            return -3;
        }
        
        /* Device has been successfully stopped. */
        return 0;
    }

    /* Device did not exist in the NIMU Module. */
    return -4;
}

/** 
 *  @b Description
 *  @n  
 *      The function handles the NIMU Special IOCTL Commands only.
 *      Most of the IOCTL commands are specific directed to a particular
 *      Network Interface object; the following are the exceptions to
 *      this rule:-
 *          -  NIMU_GET_NUM_NIMU_OBJ
 *              Used to get the number of NIMU Network Interface objects
 *              active in the current system
 *          -  NIMU_GET_ALL_INDEX
 *              Used to get an array of device index which are active in
 *              the current system. 
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  cmd      
 *      One of the special commands mentioned above.
 *  @param[in]  pBuf 
 *      The pointer to the buffer where the result of the command 
 *      execution will be stored.
 *  @param[in]  size 
 *      The size of the result buffer i.e. pBuf.
 *
 *  @retval
 *  0       -   Success
 *  @retval
 *  <0      -   Error
 */
static int NIMUIoctlSpecialCmd (uint cmd, void* pBuf, uint size)
{
    /* Process the special command. */
    switch (cmd)
    {
        case NIMU_GET_NUM_NIMU_OBJ:
        {
            /* Validate the arguments and make sure there is enough space. */
            if ((pBuf != NULL) && (size == sizeof(UINT16)))
            {
                /* Populate with the number of NIMU Objects */ 
                *(UINT16 *)pBuf = NIMUGetNumOfObject();
            }
            else
            {
                /* Invalid arguments. */
                return -EINVAL;
            }
            break;
        }
        case NIMU_GET_ALL_INDEX:
        {
            int num = NIMUGetNumOfObject();
            int index = 0;

            /* Make sure we had enough space. */
            if ((pBuf != NULL) && (size >= (sizeof(UINT16)*num)))
            {
                /* Cycle through all the network interface objects. */
                NETIF_DEVICE*   ptr_device;

                /* Initialize the memory block which has been passed.  */
                mmZeroInit (pBuf, size);

                /* Get the head of the list. */
                ptr_device = (NETIF_DEVICE *)list_get_head ((LIST_NODE**)&nimu_mcb.devices);
                while (ptr_device != NULL)
                {
                    /* Store the index. */ 
                    *((UINT16 *)pBuf + index) = ptr_device->index; 

                    /* Go to the next element. */
                    ptr_device = (NETIF_DEVICE*)list_get_next ((LIST_NODE*)ptr_device);
                    index = index + 1;
                }
            }
            else
            {
                /* Invalid Arguments. */
                return -EINVAL;
            }
            break;
        }
        default:
        {
            /* Not a special command; then why did we come here? We return a special error here! */ 
            return -1;
        }
    }

    /* Command has been processed successfully. */
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function is the standard IOCTL interface to the NIMU module
 *      and is used to get/set parameters to the NIMU. The API is available
 *      to use for applications outside the core NDK stack since it does
 *      the necessary llEnter/llExit.
 *
 *  @param[in]  cmd      
 *      One of the special commands mentioned above.
 *  @param[in]  ptr_nimu_ifreq      
 *      The NIMU Interface request structure which identifies the NIMU
 *      object to which the 'cmd' is directed upon.  
 *  @param[in]  pBuf 
 *      The pointer to the buffer where the result of the command 
 *      execution will be stored.
 *  @param[in]  size 
 *      The size of the result buffer i.e. pBuf.
 *
 *  @retval
 *  0       -   Success
 *  @retval
 *  <0      -   Error
 */
int NIMUIoctl(uint cmd, NIMU_IF_REQ* ptr_nimu_ifreq, void* pBuf, uint size)
{
    NETIF_DEVICE*   ptr_device;
    int             ret_code = 0;

    /* Critical Section Begin. */
    llEnter();

    /* Special case command handling */
    if (cmd >= NIMU_GET_NUM_NIMU_OBJ && cmd <= NIMU_GET_ALL_INDEX)
    {
        /* Handle the Special Commands */
        ret_code = NIMUIoctlSpecialCmd (cmd, pBuf, size);

        /* Critical Section End. */
        llExit ();

        /* Return the status of the command. */
        return ret_code;
    }

    /* Validate the arguments. */
    if (ptr_nimu_ifreq == NULL)
    {
        llExit();
        return -EINVAL;
    }

    /* Search for the corresponding device referenced by the NIMU Interface
     * Request. 
     *
     * NOTE: There are now two techniques of retreiving the network interface
     * object being described. One is to use the device index and the other is
     * to use the name. The 'name' is more user friendly and will remain the 
     * same through multiple 'open' and 'close'. Lets see if we can get a hit 
     * through the name. */
    ptr_device = NIMUFindByName (ptr_nimu_ifreq->name);
    if (ptr_device == NULL)
    {
        /* No entry matching device name was found; use the 'index' instead. */
        ptr_device = NIMUFindByIndex (ptr_nimu_ifreq->index);
        if (ptr_device == NULL)
        {
            /* The device does not exist in the NIMU Module. */
            llExit();
            return -EINVAL;
        }
    }

    /* Control comes here implies that we have a valid network interface object.
     * Process the request accordingly. */
    switch (cmd)
    {
        case NIMU_GET_DEVICE_HANDLE:
        {
            /* We need to pass the device handle to the callee. */
            if ((pBuf != NULL) && (size == sizeof(HANDLE)))
            {
                /* Store the handle of the device. */
                *(HANDLE *)pBuf = (HANDLE)ptr_device;
            }
            else
            {
                /* Invalid arguments detected. */
                ret_code = -EINVAL; 
            }
            break;
        }
        case NIMU_GET_DEVICE_MTU:
        {
            /* We need to pass the device MTU to the callee. */
            if ((pBuf != NULL) && (size == sizeof(UINT16)))
            {
                /* Pass the MTU of the device. */
                *(UINT16 *)pBuf = ptr_device->mtu;
            }
            else
            {
                /* Invalid arguments detected. */
                ret_code = -EINVAL; 
            }
            break;
        }
        case NIMU_SET_DEVICE_MTU:
        {
            /* We need to set the device MTU */
            if ((pBuf != NULL) && (size == sizeof(UINT16)))
            {
                /* Set the MTU of the device. */
                ptr_device->mtu = *(UINT16 *)pBuf;
            }
            else
            {
                /* Invalid arguments detected. */
                ret_code = -EINVAL; 
            }
            break;
        }
        case NIMU_GET_DEVICE_MAC:
        {
            /* We need to pass the device MAC Address to the callee. */
            if ((pBuf != NULL) && (size == (sizeof(UINT8)*6) ))
            {
                /* Copy the MAC Address into the callee buffer. */
                mmCopy ((UINT8 *)pBuf, ptr_device->mac_address, 6);
            }
            else
            {
                /* Invalid arguments detected. */
                ret_code = -EINVAL;
            }
            break;
        }
        case NIMU_SET_DEVICE_MAC:
        {
            /* Configuring the MAC Address implies that we will first pass it to 
             * the driver and let the driver correctly configure it. We will then 
             * configure the NIMU layer. */
            if (ptr_device->ioctl != NULL)
            {
                /* Check if the MAC Address can be changed. */
                ret_code = ptr_device->ioctl (ptr_device, cmd, pBuf, size);
                if (ret_code == 0)
                {
                    /* MAC address was changed in the driver. Do the needful in the NIMU too. */
                    mmCopy (ptr_device->mac_address, (UINT8 *)pBuf, 6);
                }
            }
            else
            {
                /* The device does not support changing the MAC address @ run time. */
                ret_code = -EOPNOTSUPP;
            }
            break;
        }
        case NIMU_GET_DEVICE_FLAGS:
        {
            break;
        }
        case NIMU_SET_DEVICE_FLAGS:
        {
            break;
        }
        case NIMU_GET_DEVICE_NAME:
        {
            /* We need to pass the device name to the callee. */
            if ((pBuf != NULL) && (size >= (sizeof(UINT8)*MAX_INTERFACE_NAME_LEN) ))
            {
                /* Copy the device name. */ 
                strcpy ((INT8 *)pBuf, ptr_device->name);
            }
            else
            {
                /* Invalid arguments detected. */
                ret_code = -EINVAL;
            }
            break;
        }
        case NIMU_GET_DEVICE_INDEX:
        {
            /* We need to pass the device index to the callee. */
            if ((pBuf != NULL) && (size == sizeof(UINT16)))
            {
                /* Copy the device index. */ 
                *(UINT16 *)pBuf = ptr_device->index;
            }
            else
            {
                /* Invalid arguments detected. */
                ret_code = -EINVAL;
            }
            break;
        }
        default:
        {
            /* Request was not for the NIMU Module. Pass the request down to the driver. 
             * But if the driver does not support IOCTL we return INVALID else we will
             * return whatever the driver returns. */
            if (ptr_device->ioctl != NULL)
                ret_code = ptr_device->ioctl (ptr_device, cmd, pBuf, size);
            else
                ret_code = -EINVAL;
        }
    }

    /* Critical Section End. */
    llExit ();

    /* Return the status of the operation. */
    return ret_code;
}

/** 
 *  @b Description
 *  @n  
 *      The function is to used to retrieve the header and trailer reserved
 *      size information. The Network Interface Management Unit keeps track
 *      of all devices present in the system and is also responsible for 
 *      ensuring that there is suffient headroom and tailroom for various 
 *      driver layers to be able to add headers or trailers as the need be.
 *      This ensures that there are no copies being done because of 
 *      insufficient headroom.
 *
 *      The function is available for usage; but it should only be called
 *      from kernel mode (llEnter()/llExit()) 
 *      
 *  @param[out]  header_size
 *      The current header size which is reserved. 
 *  @param[out]  trailer_size
 *      The current trailer size which is reserved. 
 *  @retval
 *   Not Applicable.
 */
void NIMUGetRsvdSizeInfo (int* header_size, int* trailer_size)
{
    /* Populate the current reserved header and trailer size. */
    *header_size  = nimu_mcb.header_size;
    *trailer_size = nimu_mcb.trailer_size;
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function is to used to set the header and trailer reserved
 *      size information. This is typically used by driver authors if the
 *      driver needs a L2 header or trailer and the current size are not
 *      sufficient.
 *
 *      There is no validation done on the arguments.
 *
 *      The function is available for usage; but it should only be called
 *      from kernel mode (llEnter()/llExit()) 
 *      
 *  @param[in]  header_size
 *      The new header size which is to be reserved
 *  @param[in]  trailer_size
 *      The new trailer size which is to be reserved 
 *  @retval
 *   Not Applicable.
 */
void NIMUSetRsvdSizeInfo (int header_size, int trailer_size)
{
    /* Configure the current header and trailer sizes. */ 
    nimu_mcb.header_size  = header_size;
    nimu_mcb.trailer_size = trailer_size;
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function initializes the NDK core stack Network Interface
 *      Management Unit 
 *
 *      This is for *internal* NDK Stack Usage.
 *      
 *  @param[in]  hEvent
 *      The stack event handle which is used by the NDK Network 
 *      Scheduler to indicate data is present on the drivers. This 
 *      handle is required by the drivers for its operation.
 *
 *  @retval
 *   0      -   Success
 *  @retval
 *   <0     -   Error
 */
int NIMUInit (STKEVENT_Handle hEvent)
{
    int index = 0;

    /* Initialize the NIMU MCB. */
    mmZeroInit ((void *)&nimu_mcb, sizeof (NIMU_MCB));

    /* Set the NIMU Header and Trailer to 'defaults' */
    nimu_mcb.header_size  = NIMU_DEFAULT_HEADER_RSVD_LEN;
    nimu_mcb.trailer_size = NIMU_DEFAULT_TRAILER_RSVD_LEN;

    /* Cycle through the NIMU Device Table and initialize all of the 
     * listed network devices. */
    while (NIMUDeviceTable[index].init != NULL)
    {
        /* Call the initialization function */
        NIMUDeviceTable[index].init (hEvent);

        /* Jump to the next entry. */
        index = index + 1;
    }

    /* NIMU is up and operational. */
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function closes the NDK core stack Network Interface
 *      Management Unit 
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @retval
 *   Not applicable.
 */
void NIMUShutdown (void)
{
    NETIF_DEVICE*   ptr_device;
    int retcode = 0;

    /* Cycle through all the network interface objects in the NIMU
     * and close them out. */
    ptr_device = (NETIF_DEVICE *)list_get_head ((LIST_NODE**)&nimu_mcb.devices);
    while (ptr_device != NULL)
    {
        /* Unregister the NIMU Network Interface Object. */
        if ((retcode = NIMUUnregister (ptr_device)) < 0)
        {
            /*
             *  Error: Unable to deregister or stop the device. We need to
             *  recover and move ahead. So we remove it from the list
             */
            DbgPrintf(DBG_INFO,
              "NIMUShutdown: Error: Failed to unregister NIMU Object %s (%d)\n",
              ptr_device->name, retcode);
        }

        /* Go to the next element. */
        ptr_device =
                (NETIF_DEVICE *)list_get_head ((LIST_NODE**)&nimu_mcb.devices);
    }
    return;
}

