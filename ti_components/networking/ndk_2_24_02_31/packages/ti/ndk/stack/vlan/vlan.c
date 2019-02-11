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
 * ======== vlan.c ========
 *
 * The file implements the VLAN core stack functionality.  
 *
 */

#include <stkmain.h>

/**********************************************************************
 *************************** Local Structures *************************
 **********************************************************************/

struct VLAN_SRC_IF;

/*********************************************************************
 * STRUCTURE NAME : VLAN_NODE
 *********************************************************************
 * DESCRIPTION   :
 *  The structure describes the VLAN NODE.
 *********************************************************************/
typedef struct VLAN_NODE
{
    LIST_NODE           links;
    UINT16              vlan_id;
    UINT8               default_priority;
    UINT8               prio_mapping[MAX_PRIO_VAL];
    struct VLAN_SRC_IF* ptr_src;
    NETIF_DEVICE*       ptr_vlan_device;
}VLAN_NODE;

/*********************************************************************
 * STRUCTURE NAME : VLAN_SRC_IF
 *********************************************************************
 * DESCRIPTION   :
 *  The structure describes the VLAN Source Interface. Each source 
 *  interface on which a VLAN NIMU network object is created will have
 *  an object of this type existing in the system. Each VLAN source 
 *  interface object in turn can have multiple VLANNodes executing on 
 *  top of it provided the VLAN identifiers are unique for the source
 *  device.
 *********************************************************************/
typedef struct VLAN_SRC_IF
{
    LIST_NODE       links;
    NETIF_DEVICE*   ptr_src_device;
    VLAN_NODE       vlan_nodes;
}VLAN_SRC_IF;

/*********************************************************************
 * STRUCTURE NAME : VLAN_MCB
 *********************************************************************
 * DESCRIPTION   :
 *  The structure is used to hold all the information of the VLAN 
 *  module.
 *********************************************************************/
typedef struct VLAN_MCB
{
    VLAN_SRC_IF   vlan_src;
}VLAN_MCB;

/**********************************************************************
 ******************************* Globals ******************************
 **********************************************************************/
VLAN_MCB vlan_mcb;

/**********************************************************************
 ************************* Static Definitions *************************
 **********************************************************************/

static VLAN_SRC_IF* VLANFindSourceInterface (uint device_index);
static VLAN_NODE* VLANFindNode (UINT16 vlan_id, VLAN_SRC_IF* ptr_src);

/** 
 *  @b Description
 *  @n    
 *      The function is called by the NIMU Receive function when a VLAN
 *      packet is received. The function validates the packet and ensures
 *      that there is a valid VLAN node on the system which can process the
 *      packet. 
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  hPkt            
 *      Handle to the packet which needs to be sent
 *
 *  @retval
 *   Encapsulated Protocol -    Success
 *  @retval
 *   0xFFFF                -    Error
 */
uint VLANReceivePacket (PBM_Handle hPkt)
{
    PBM_Pkt*        ptr_pkt;
    NETIF_DEVICE*   ptr_src_device;
    VLAN_SRC_IF*    ptr_src;
    VLAN_NODE*      ptr_node;
    uint            encap_protocol = 0xFFFF;
    VLANHDR*        ptr_vlanhdr;
    UINT16          vlan_id;

    /* Get the pointer to the packet. */
    ptr_pkt = (PBM_Pkt *)hPkt;

    /* Ensure that the received packet has a valid Source NODE. If the parameter
     * was not set by the driver then we cannot proceed as we dont know where the
     * packet came from. */
    ptr_src_device = (NETIF_DEVICE *)ptr_pkt->hIFRx;
    if (ptr_src_device == NULL)
        return encap_protocol;

    /* Get the VLAN Source Interface: If none exists then this interface is not
     * capable of receiving VLAN frames. */
    ptr_src = VLANFindSourceInterface (ptr_src_device->index);
    if (ptr_src == NULL)
        return encap_protocol;

    /* Get the pointer to the VLAN Header */
    ptr_vlanhdr = (VLANHDR *) (ptr_pkt->pDataBuffer + ptr_pkt->DataOffset);

    /* Extract the VLAN Identifier. */
    vlan_id = ntohs(ptr_vlanhdr->TCI) & MAX_VLAN_ID;

    /* Get the VLAN Node matching the VLAN ID: If none exists then it indicates there
     * is no VLAN node; hence no NIMU network interface object capable of handling the
     * VLAN Identifier.  */
    ptr_node = VLANFindNode (vlan_id, ptr_src);
    if (ptr_node == NULL)
        return encap_protocol;

    /* We can proceed with the packet. Modify the fields in the packet appropriately. */
    ptr_pkt->ValidLen   -= VLANHDR_SIZE;
    ptr_pkt->DataOffset += VLANHDR_SIZE;
    ptr_pkt->EtherType   = ntohs(ptr_vlanhdr->EncapProtocol);
    ptr_pkt->L2HdrLen   += VLANHDR_SIZE;
    ptr_pkt->hIFRx       = (HANDLE)ptr_node->ptr_vlan_device;

    /* Return the encapsulated protocol in host order. */
    return ptr_pkt->EtherType;
}

/** 
 *  @b Description
 *  @n    
 *      The function is the 'send' interface routine for the VLAN
 *      virtual NIMU Network Interface object. 
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  pPkt            
 *      Handle to the packet which needs to be sent
 *
 *  @retval
 *      Always returns 0.
 */
static int VLANSend (NETIF_DEVICE* ptr_net_device, PBM_Handle hPkt)
{
    VLAN_NODE*  ptr_node;

    /* Get the pointer to the VLAN node information block. */
    ptr_node = (VLAN_NODE *)ptr_net_device->pvt_data;

    /* Send the packet through the source interface. NOTE: We always return SUCCESS
     * from this function because if the source interface was unable to send the packet
     * the NIMUSendPacket API would have already cleaned the packet memory; if we returned
     * error from here the packet would get cleaned again which we dont want to do. */ 
    NIMUSendPacket (ptr_node->ptr_src->ptr_src_device, hPkt);
    return 0;
}

/** 
 *  @b Description
 *  @n    
 *      The function is the 'add_header' interface routine for the VLAN
 *      virtual NIMU Network Interface object. The functions adds a VLAN
 *      header on the packet.
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
 *  @param[in]  ether_type         
 *      The 'Protocol' tag which needs to be appended.
 *
 *  @retval
 *   0  -   Success
 *  @retval
 *   <0  -  Error
 */
static int VLANAddHeader 
(
    NETIF_DEVICE* ptr_net_device, 
    PBM_Handle    hPkt, 
    UINT8*        dst_mac, 
    UINT8*        src_mac, 
    UINT16        ether_type
)
{
    PBM_Pkt*    pPkt = (PBM_Pkt *)hPkt;
    VLANHDR*    ptr_vlanhdr;
    VLAN_NODE*  ptr_node;
    UINT16      TCI;

    /* Get the pointer to the packet. */
    pPkt = (PBM_Pkt *)hPkt;
    if (pPkt == NULL)
        return -1;

    /* Get the pointer to the VLAN node information block. */
    ptr_node = (VLAN_NODE *)ptr_net_device->pvt_data;

    /* Check if there is sufficient space to add the header 
     * If not then this is a fatal error; we should always have sufficient space
     * allocated at the head of the packet to account for a Layer2 header. 
     * Report this to the world. */
    if (pPkt->DataOffset < VLANHDR_SIZE)
    {
        DbgPrintf(DBG_ERROR,"VLANAddHeader: No space for VLAN Header");
        return -1;
    }

    /* Back up to make room for VLAN header. */
    pPkt->DataOffset -= VLANHDR_SIZE;

    /* Get a pointer to the space reserved for the layer2 header. */
    ptr_vlanhdr = (VLANHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Create the TCI for the VLAN header
     *  If the packet had no priority we add the default priority.
     *  If the packet has the priority we use the mapping table to mark it. */
    if (pPkt->PktPriority == PRIORITY_UNDEFINED)
    {
        TCI = (ptr_node->default_priority << 13) | (ptr_node->vlan_id);
    }
    else
    {
        TCI = (ptr_node->prio_mapping[pPkt->PktPriority] << 13) | (ptr_node->vlan_id);
    }

    /* Populate the VLAN header. */ 
    ptr_vlanhdr->TCI           = htons(TCI);
    ptr_vlanhdr->EncapProtocol = HNC16(ether_type);

    /* Increment the total length of the packet to account for the new VLAN header which has 
     * been added. */
    pPkt->ValidLen = pPkt->ValidLen + VLANHDR_SIZE;

    /* Add the lower layer header using the VLAN Source interface block */
    if (NIMUAddHeader (ptr_node->ptr_src->ptr_src_device, hPkt, dst_mac, src_mac, 0x8100) < 0)
    {
        /* There was an error and the header could not be added. Clean the packet memory */
        PBM_free (hPkt);
        return -1;
    }

    /* Header has been successfully added. */
    return 0;
}

/** 
 *  @b Description
 *  @n    
 *      The function is the VLAN wrapper for the IOCTL function. 
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_net_device
 *      This is the VLAN Network Interface object. 
 *  @param[in]  cmd
 *      This is IOCTL command which has been issued
 *  @param[in]  pBuf
 *      Buffer which stores command specific data
 *  @param[in]  size
 *      Size of the buffer.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
static int VLANIoctl (NETIF_DEVICE* ptr_net_device, uint cmd, void* pBuf, uint size)
{
    VLAN_NODE*      ptr_node;
    NETIF_DEVICE*   ptr_src_device;

    /* Get the pointer to the VLAN node information block. */
    ptr_node = (VLAN_NODE *)ptr_net_device->pvt_data;

    /* Basic Sanity Checks: We need to ensure the internal pointers are valid. */
    if ((ptr_node == NULL) || (ptr_node->ptr_src == NULL))
    {
        DbgPrintf (DBG_ERROR,
                "VLANIoctl: Error: Internal VLAN Database corrupted\n");
        return -1;
    }

    /* Get the pointer to the source device. */
    ptr_src_device = ptr_node->ptr_src->ptr_src_device;
    if (ptr_src_device == NULL)
    {
        DbgPrintf (DBG_ERROR,
                "VLANIoctl: Error: VLAN Device %s has no source interface\n",
                ptr_net_device->name);
        return -1;
    }

    /* Call the IOTCL Handler; if registered. If no IOTCL is handled return error */
    if (ptr_src_device->ioctl == NULL)
        return -1;

    /* Call the source interface IOCTL handler. */
    return ptr_src_device->ioctl (ptr_src_device, cmd, pBuf, size);
}

/** 
 *  @b Description
 *  @n    
 *      The function is used to find a VLAN source interface matching the
 *      device index. The function will cycle through all the VLAN source
 *      interfaces which exist in the System.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  device_index
 *      The index for which we are trying to find a VLAN source interface
 *
 *  @retval
 *   VLAN Source Interface  - Matching entry found
 *  @retval
 *   NULL                   - No Matching entry found
 */
static VLAN_SRC_IF* VLANFindSourceInterface (uint device_index)
{
    VLAN_SRC_IF* ptr_src;

    /* Get the pointer to the head of the source interfaces. */
    ptr_src = (VLAN_SRC_IF *)list_get_head ((LIST_NODE**)&vlan_mcb.vlan_src);
    while (ptr_src != NULL)
    {
        /* Did we get a match? */
        if (ptr_src->ptr_src_device->index == device_index)
            return ptr_src;

        /* Jump to the next entry */
        ptr_src = (VLAN_SRC_IF *)list_get_next ((LIST_NODE *)ptr_src);
    }

    /* No matching entry found. */
    return NULL;
}

/** 
 *  @b Description
 *  @n    
 *      The function is used to create a new VLAN source interface.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  device_index
 *      The index for which the new VLAN source interface will be
 *      created.
 *
 *  @retval
 *   VLAN Source Interface  - Success
 *  @retval
 *   NULL                   - Error
 */
static VLAN_SRC_IF* VLANCreateSourceInterface (uint device_index)
{
    VLAN_SRC_IF*    ptr_src;

    /* Allocate memory for the VLAN source interface. */
    ptr_src = mmAlloc (sizeof(VLAN_SRC_IF));
    if (ptr_src == NULL)
        return NULL;

    /* Initialize the allocated memory block. */
    mmZeroInit (ptr_src, sizeof(VLAN_SRC_IF));

    /* Populate the structure. */
    ptr_src->ptr_src_device = NIMUFindByIndex(device_index);

    /* Add the VLAN source interface to the global list. */
    list_add ((LIST_NODE**)&vlan_mcb.vlan_src, (LIST_NODE *)ptr_src);

    /* Return the allocated VLAN Source interface. */
    return ptr_src;
}

/** 
 *  @b Description
 *  @n    
 *      The function is used to delete a VLAN source interface from
 *      the system. This is called when there 'exist' no more
 *      VLAN nodes on the source interface.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_src
 *      Pointer to the VLAN source interface which is being deleted.
 *
 *  @retval
 *   VLAN Source Interface  - Success
 *  @retval
 *   NULL                   - Error
 */
static void VLANDeleteSourceInterface (VLAN_SRC_IF* ptr_src)
{
    /* Remove the VLAN source interface from the global list. */
    list_remove_node ((LIST_NODE**)&vlan_mcb.vlan_src, (LIST_NODE *)ptr_src);

    /* Cleanup the memory */
    mmFree (ptr_src);
    return;
}

/** 
 *  @b Description
 *  @n    
 *      The function is used to find a VLAN node matching the VLAN 
 *      Identifier on the specified VLAN source interface.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  vlan_id
 *      VLAN identifier.
 *  @param[in]  ptr_src
 *      Pointer to the VLAN Source Interface
 *
 *  @retval
 *   VLAN Node  - Matching entry
 *  @retval
 *   NULL       - No matching entry
 */
static VLAN_NODE* VLANFindNode (UINT16 vlan_id, VLAN_SRC_IF* ptr_src)
{
    VLAN_NODE* ptr_node;

    /* Get the pointer to the VLAN Nodes. */ 
    ptr_node = (VLAN_NODE *)list_get_head ((LIST_NODE**)&ptr_src->vlan_nodes);
    while (ptr_node != NULL)
    {
        /* Did we get a match? */
        if (ptr_node->vlan_id == vlan_id)
            return ptr_node;

        /* Jump to the next entry */
        ptr_node = (VLAN_NODE *)list_get_next ((LIST_NODE *)ptr_node);
    }

    /* No matching entry found. */
    return NULL;
}

/** 
 *  @b Description
 *  @n    
 *      The function is used to create a new VLAN node with 
 *      the specified properties.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  vlan_id
 *      VLAN identifier.
 *  @param[in]  default_priority
 *      Default Priority used to mark packets with when there are no
 *      existing priority marking on the packet.
 *  @param[in]  prio_mapping[]
 *      This is an array which maps the packet priority to a VLAN user
 *      priority.
 *  @param[in]  ptr_src
 *      Pointer to the VLAN source interface block on which the VLAN 
 *      node is executing.
 *
 *  @retval
 *   VLAN Node  - Success
 *  @retval
 *   NULL       - Error
 */
static VLAN_NODE* VLANCreateNode 
(
    UINT16       vlan_id, 
    UINT8        default_priority, 
    UINT8        prio_mapping[],
    VLAN_SRC_IF* ptr_src
)
{
    VLAN_NODE*    ptr_node;

    /* Allocate memory for the VLAN node. */
    ptr_node = mmAlloc (sizeof(VLAN_NODE));
    if (ptr_node == NULL)
        return NULL;

    /* Initialize the allocated memory block. */
    mmZeroInit (ptr_node, sizeof(VLAN_NODE));

    /* Populate the structure. */
    ptr_node->vlan_id           = vlan_id;
    ptr_node->default_priority  = default_priority;    
    ptr_node->vlan_id           = vlan_id;
    ptr_node->ptr_src           = ptr_src;
    mmCopy (&ptr_node->prio_mapping[0], &prio_mapping[0], MAX_PRIO_VAL);

    /* Add the VLAN Node to the VLAN Source Interface list. */
    list_add ((LIST_NODE**)&ptr_src->vlan_nodes, (LIST_NODE*)ptr_node);

    /* Return the allocated VLAN Source interface. */
    return ptr_node;
}

/** 
 *  @b Description
 *  @n    
 *      The function is used to delete a VLAN node from the system
 *      If this was the only VLAN node on the VLAN source interface
 *      then the function will end up deleting the VLAN source 
 *      interface too.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_node
 *      VLAN Node to be deleted.
 *  @param[in]  ptr_src
 *      Pointer to the VLAN source interface block on which the VLAN 
 *      node was present.
 *
 *  @retval
 *      Not Applicable
 */
static void VLANDeleteNode (VLAN_NODE* ptr_node, VLAN_SRC_IF* ptr_src)
{
    /* Remove the VLAN node from the VLAN source interface list. */ 
    list_remove_node ((LIST_NODE**)&ptr_src->vlan_nodes, (LIST_NODE *)ptr_node);

    /* Cleanup the memory */
    mmFree (ptr_node);

    /* Check if the VLAN Source list has more VLAN nodes or not? */
    if (list_get_head((LIST_NODE**)&ptr_src->vlan_nodes) == NULL)
    {
        /* No more VLAN nodes on this source interface? There is no need to
         * keep this entry; delete the VLAN source interface too. */
        VLANDeleteSourceInterface (ptr_src);
    }
    return;
}

/** 
 *  @b Description
 *  @n    
 *      The function is used to initialize and start the VLAN virtual 
 *      NIMU Network Interface Object.  This is just a DUMMY stub function 
 *      provided for NIMU.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_net_device
 *      The VLAN NIMU Network Interface Object.
 *
 *  @retval
 *      Always returns 0 i.e. SUCCESS
 */
static int VLANStart (NETIF_DEVICE* ptr_net_device)
{
    (void)ptr_net_device;

    /* No need to do anything here. The VLAN Node and associated 
     * NIMU Network Interface Object is UP and Running. */
    return 0;
}

/** 
 *  @b Description
 *  @n    
 *      The function is used to close and stop the VLAN virtual
 *      NIMU Network Interface object. The function deletes the 
 *      VLAN Node from the system.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_net_device
 *      The VLAN NIMU Network Interface Object to be stopped
 *
 *  @retval
 *      Always returns 0 i.e. SUCCESS
 */
static int VLANStop (NETIF_DEVICE* ptr_net_device)
{
    VLAN_NODE*      ptr_node;
    VLAN_SRC_IF*    ptr_src;

    /* Control comes here implies that we are 'stopping' a VLAN Node */
    ptr_node = (VLAN_NODE *)ptr_net_device->pvt_data;
    ptr_src  = (VLAN_SRC_IF *)ptr_node->ptr_src;

    /* Decrement the reference counter for the source interface */
    ptr_src->ptr_src_device->RefCount--;

    /* Delete the VLAN Node from the system and source interface 
     * NOTE: We dont need to worry about the source interface; 
     * because the 'VLANDeleteNode' API will automatically delete
     * the source interface if there are no more VLAN nodes. */
    VLANDeleteNode (ptr_node, ptr_src);
    return 0;
}

/** 
 *  @b Description
 *  @n   
 *      The API is available to user applications to be able to create
 *      a VLAN virtual device on a source interface 
 *
 *  @param[in]  index             
 *      Source Interface Index on which the  VLAN device is created
 *  @param[in]  vlan_id           
 *      VLAN Identifier associated with the VLAN device
 *  @param[in]  default_priority  
 *      Default User Priority configured in the VLAN packet if no packet 
 *      priority is defined.
 *  @param[in]  prio_mapping      
 *      The mapping which maps the packet priority to the VLAN user 
 *      priority which is a part of the VLAN header.
 *
 *  @retval
 *   Index of the new VLAN device    -   Success
 *  @retval
 *   <0                              -   Error
 */
int VLANAddDevice 
(
    uint        index, 
    UINT16      vlan_id, 
    UINT8       default_priority, 
    UINT8       prio_mapping[MAX_PRIO_VAL]
)
{
    VLAN_SRC_IF*    ptr_src;
    VLAN_NODE*      ptr_node;
    NETIF_DEVICE*   ptr_device;

    /* Validate the arguments:
     * - VLAN Identifier are limited to a 12 bit value */
    if (vlan_id > MAX_VLAN_ID)
        return -EINVAL;

    /* Move into kernel mode. */
    llEnter();

    /* Validate the arguments. 
     * - Make sure the source interface specified exists in the System */
    if (NIMUFindByIndex (index) == NULL)
    {
        /* The source interface does not exist; move back to user mode and return
         * the error. */
        llExit();
        return -EINVAL;
    }

    /* Check if there exists a VLAN Source interface */
    ptr_src = VLANFindSourceInterface (index);
    if (ptr_src == NULL)
    {
        /* No VLAN Source Interface was detected; create a new one. */
        ptr_src = VLANCreateSourceInterface(index);
        if (ptr_src == NULL)
        {
            /* FATAL Error: Unable to create the VLAN source interface */
            llExit ();
            return -ENOMEM;
        }
    }

    /* Control comes here only with a valid VLAN Source Interface 
     * Now we check if the VLAN ID already exists or not? */
    if (VLANFindNode(vlan_id, ptr_src) != NULL)
    {
        /* This indicates that a VLAN node with the specified 'vlan_id' already
         * exists in the System. We cannot have duplicate VLAN ID present on the
         * same VLAN Source interface. */
         llExit ();
         return -EINVAL;
    }

    /* Control comes here indicates we are good and we can proceed with creating
     * the VLAN Node. */
    ptr_node = VLANCreateNode (vlan_id, default_priority, prio_mapping, ptr_src);
    if (ptr_node == NULL)
    {
        /* Error: We were unable to create the VLAN Node. */   
        llExit ();
        return -ENOMEM;
    }

    /* Allocate memory for the VLAN NIMU Network Interface Object. */
    ptr_device = mmAlloc(sizeof(NETIF_DEVICE));
    if (ptr_device == NULL)
    {
        /* Error: Memory allocation failed */
        NotifyLowResource ();
        llExit();
        return -ENOMEM;
    }

    /* Initialize the allocated memory block. */
    mmZeroInit (ptr_device, sizeof(NETIF_DEVICE));

    /* Store the backpointer to the new device created in the VLAN Node too. */
    ptr_node->ptr_vlan_device = ptr_device;

    /* Populate the Network Interface Object. */
    NDK_sprintf (ptr_device->name, "%s:%d", ptr_src->ptr_src_device->name, vlan_id);
    ptr_device->pvt_data = (void *)ptr_node;

    /* To compute the VLAN Device MTU we will use the 
     * Source Interface MTU and decrement the VLAN Header. */
    ptr_device->mtu = ptr_src->ptr_src_device->mtu - VLANHDR_SIZE;

    /* The MAC Address of the new VLAN NIMU object is inherited from the source interface */
    mmCopy (ptr_device->mac_address, ptr_src->ptr_src_device->mac_address, 6); 

    /* Populate the Driver Interface Functions. */
    ptr_device->start       = VLANStart;
    ptr_device->stop        = VLANStop;
    ptr_device->poll        = NULL;
    ptr_device->send        = VLANSend;
    ptr_device->pkt_service = NULL;
    ptr_device->ioctl       = VLANIoctl;
    ptr_device->add_header  = VLANAddHeader;

    /* Register the device with NIMU */
    if (NIMURegister (ptr_device) < 0)
    {
        /* FATAL Error: This should never occur... */
        llExit();
        return -1;
    }

    /* Increment the reference counter for the source interface */
    ptr_src->ptr_src_device->RefCount++;

    /* Exit out of the kernel mode. */
    llExit();
    return ptr_device->index;
}

/** 
 *  @b Description
 *  @n   
 *      The API is available to user applications to be able to delete 
 *      a previously created VLAN device. 
 *
 *  @param[in]  dev_index           
 *      Index of the VLAN NIMU Interface Object which is to be deleted.  
 *      This should be the same as the returned value from VLANAddDevice.
 *
 *  @retval
 *   0    -   Success
 *  @retval
 *   <0   -   Error
 */
int VLANDelDevice (UINT16 dev_index)
{
    NETIF_DEVICE*   ptr_vlan_device;

    /* Move into kernel mode. */
    llEnter();

    /* Validate the arguments:
     *  - Check if the device index specified exists in the NIMU Module. */
    ptr_vlan_device = NIMUFindByIndex (dev_index);
    if (ptr_vlan_device == NULL)
    {
        /* Error: This indicates that the device does not exist */
        llExit ();
        return -EINVAL;
    }

    /* Ok; we got the device. Now we need to identify if the device is
     * VLAN or not? We could use either of the following schemes for this
     *  a) Cycle through all the source interfaces and all their VLAN nodes 
     *     and get a match. 
     *  b) Check the START Function to be the same as VLANStart. 
     * We will go with (b); because VLAN is a closed module inside the NDK
     * core stack and no user can modify the 'start' function; at least not
     * through some supported API. */
    if (ptr_vlan_device->start != &VLANStart)
    {
        /* Device existed but it was not a VLAN Node. */
        llExit ();
        return -EINVAL;
    }

    /* Unregister the VLAN Device from the NIMU Module. */
    if (NIMUUnregister (ptr_vlan_device) < 0)
    {
        /* The VLAN device could not be stopped. */
        llExit ();
        return -1;
    }

    /* Cleanup the memory allocated for the VLAN Node NIMU Object. */
    mmFree (ptr_vlan_device);

    /* Exit out of the kernel mode. */
    llExit();
    return 0;
}

/** 
 *  @b Description
 *  @n    
 *      The function is used to initialize the VLAN module in the NDK
 *      core stack
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @retval
 *   Not Applicable.
 */
void VLANInit (void)
{
    int header_size;
    int trailer_size;

    /* Initialize the global variable. */
    mmZeroInit (&vlan_mcb, sizeof(VLAN_MCB));

    /* Get the NIMU header and trailer size. */
    NIMUGetRsvdSizeInfo (&header_size, &trailer_size);

    /* Check if we have sufficient space for the headers? 
     * For VLAN we need to have space for at least the VLAN+Ethernet header. */
    if (header_size < (VLANHDR_SIZE + ETHHDR_SIZE))
    {
        /* There was not sufficient space. Create additional space at 
         * the head of the packet. We dont worry about the trailer. */
        header_size = header_size + VLANHDR_SIZE + ETHHDR_SIZE;
        NIMUSetRsvdSizeInfo (header_size, trailer_size);
    }
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function is used to deinitialize the VLAN module.
 *      The function is called to close and shutdown all the VLAN
 *      enabled NIMU Network Interface objects which exist in the 
 *      System
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @retval
 *   Not Applicable.
 */
void VLANDeinit (void)
{
    VLAN_NODE*      ptr_node;
    VLAN_SRC_IF*    ptr_src;
    NETIF_DEVICE*   ptr_vlandevice;

    while (1)
    {
        /* Cycle through all the source interfaces */
        ptr_src = (VLAN_SRC_IF *)list_get_head ((LIST_NODE**)&vlan_mcb.vlan_src);
        if (ptr_src != NULL)
        {
            /* Found the VLAN Source interface; now get the VLAN node. */ 
            ptr_node = (VLAN_NODE *)list_get_head ((LIST_NODE **)&ptr_src->vlan_nodes);
            if (ptr_node != NULL)
            {
                /* Found the VLAN Node to delete. Unregister the corresponding VLAN NIMU
                 * Network Interface Object. */ 
                ptr_vlandevice = ptr_node->ptr_vlan_device;

                /* Unregister the associated VLAN NIMU Network Interface object */
                if (NIMUUnregister(ptr_vlandevice) < 0) {
                    DbgPrintf(DBG_INFO,
                            "VLANDeinit: Failed to unregister VLAN device %s\n",
                            ptr_node->ptr_vlan_device->name);
                }

                /*
                 *  Cleanup the memory for the VLAN NIMU Network Interface
                 *  object.
                 */
                mmFree (ptr_vlandevice);
            }
            else
            {
                /*
                 *  Error: This case should not happen; there is NO VLAN Node
                 *  on this source interface. This source interface should have
                 *  been deleted when the last VLAN node was removed. Lets
                 *  inform the world and return we cant recover from this.
                 */
                DbgPrintf(DBG_INFO,
                   "VLANDeinit: Error: VLAN Source %s and Node inconsistency\n",
                   ptr_src->ptr_src_device->name);
                break;
            }
        }
        else
        {
            /* There are no more VLAN Source interfaces and VLAN nodes; we are done. */
            break;
        }
    }
    return;
}

