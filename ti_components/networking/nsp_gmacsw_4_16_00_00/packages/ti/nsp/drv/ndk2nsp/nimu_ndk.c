/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
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
 */

/*!
 *   \file  nimu_ndk.c
 *
 *   \brief
 *          Interface module to support NIMU packet architecture for NDK
 *
 */


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* OS/Posix headers */

/* NDK Dependencies */
#include <ti/ndk/inc/stkmain.h>

/* Project dependency headers */
#include "ndk2nsp.h"
#include "private/debug_.h"

/* This module's header */
#include "nimu_ndk.h"


/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/

extern PBMQ PBMQ_free;

/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#define VLAN_TAG_SIZE         (4U)
#define ETH_FRAME_SIZE        ((uint32_t)ETH_MAX_PAYLOAD + VLAN_TAG_SIZE)

/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/

static int  NIMU_NDK_init        (STKEVENT_Handle hEvent);

static int  NIMU_NDK_start       (NETIF_DEVICE* pNETIFDevice);
static int  NIMU_NDK_stop        (NETIF_DEVICE* pNETIFDevice);
static void NIMU_NDK_poll        (NETIF_DEVICE* pNETIFDevice, unsigned int timer_tick);
static int  NIMU_NDK_send        (NETIF_DEVICE* pNETIFDevice, PBM_Handle hPkt);
static void NIMU_NDK_pktService  (NETIF_DEVICE* pNETIFDevice);
static int  NIMU_NDK_ioctl       (NETIF_DEVICE* pNETIFDevice, unsigned int cmd, void* pBuf, unsigned int size);
static int  NIMU_NDK_addEthernetHeader( NETIF_DEVICE *pNETIFDevice, PBM_Handle hPkt,
                                  uint8_t *dst_mac, uint8_t *src_mac, uint16_t ether_type );


/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/

#if !defined(NSP_DYNAMIC_ALLOCATION)
NETIF_DEVICE NETIF_DEVICE_Eth0_Obj;
/*We define the second NETIF_DEVICE to be used by the NDK here in case of DUAL MAC MODE*/
NETIF_DEVICE NETIF_DEVICE_Eth1_Obj;
#endif


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

/*!
 * \brief
 *   NIMUDeviceTable
 *
 * \details
 *  This is the NIMU Device Table for the Platform.
 *  This should be defined for each platform. Since the current platform
 *  has a single network Interface; this has been defined here. If the
 *  platform supports more than one network interface this should be
 *  defined to have a list of "initialization" functions for each of the
 *  interfaces.
 */
NIMU_DEVICE_TABLE_ENTRY NIMUDeviceTable[MAC_NUM_PORTS+1U] =
{
    /*!
     * \brief  NIMU_NDK_Init for this network device
     */
    &NIMU_NDK_init,
    /*In DUAL MAC MODE, since we have two NETIF_DEVICEs, we need to have two inits for the NIMU_DEVICEs*/
    #ifdef DUAL_MAC_MODE
    &NIMU_NDK_init,
    #else
    NULL,
    #endif
    NULL
};

/*This is required to keep track of which NIMU Device was initialized and do the set up accordingly*/
static int deviceInitCount = 0;

/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

/*!
 *  @b NIMU_NDK_Init
 *  @n
 *  The function is used to initialize and register the GMACSW
 *  with the Network Interface Management Unit (NIMU)
 *
 *  \param[in]  hEvent
 *      Stack Event Handle.
 *
 *  \retval
 *      Success -   0
 *  \retval
 *      Error   -   <0
 */
static int NIMU_NDK_init(STKEVENT_Handle hEvent)
{
    /*Storing in array to copy later by indexing rather than using IF ELSE*/
    char *NETIF_DEVICE_NAMES[2] = {"eth0","eth1"};

    /*Increment the count so that we know whether we are dealing with the interface 1 or 2*/
    deviceInitCount++;

    NETIF_DEVICE *pNETIFDevice;

#if defined(NSP_DYNAMIC_ALLOCATION)
    /* Allocate memory for the Network Interface Object */
    pNETIFDevice = (NETIF_DEVICE *) mmAlloc(sizeof(NETIF_DEVICE));
    if (pNETIFDevice == NULL)
    {
        dprint("Error: Unable to allocate memory for the NIMU interface object\n");
        return -1;
    }
#else
    if(1==deviceInitCount)
    {
        pNETIFDevice = &NETIF_DEVICE_Eth0_Obj;
    }
    else
    {
        pNETIFDevice = &NETIF_DEVICE_Eth1_Obj;
    }
#endif

    /* Initialize the allocated memory block. */
    memset(pNETIFDevice, 0, sizeof(NETIF_DEVICE));

#if !defined(NSP_DYNAMIC_ALLOCATION)
    /*
     * Tell stack NOT to call mmFree for us on this instance!
     * This allows driver to have full control over the means of
     * allocating/freeing for this NIMU device instance.
     */
    pNETIFDevice->flags = NIMU_DEVICE_NO_FREE;
#endif


    /* Populate the Network Interface Object. */
    strcpy(pNETIFDevice->name, NETIF_DEVICE_NAMES[deviceInitCount-1]);
    /*This index can later be used to make interface specific decisions*/
    pNETIFDevice->index = deviceInitCount-1;

    /*
     * MTU is i total size of the (IP) packet that can fit into an Ethernet.
     * For Ethernet it is 1500bytes
     */
#if defined(ENABLE_JUMBO_FRAMES)
    /*
     * For TDA hardware maximum packet length for CPDMA can't be more that 2048
     * due to packet length being 11 bits in descriptors. Hence Jumbo packet of
     * max. 2K can be used
     */
       pNETIFDevice->mtu         = 2000U;
#else
    pNETIFDevice->mtu         = (uint32_t)(ETH_FRAME_SIZE - (uint32_t)ETHHDR_SIZE - VLAN_TAG_SIZE);
#endif

    /* Stash the STKEVENT_Handle until we use it in the start function */
    pNETIFDevice->pvt_data    = (void *) hEvent;

    /* Populate the Driver Interface Functions. */
    pNETIFDevice->start       = &NIMU_NDK_start;
    pNETIFDevice->stop        = &NIMU_NDK_stop;
    pNETIFDevice->poll        = &NIMU_NDK_poll;
    pNETIFDevice->send        = &NIMU_NDK_send;
    pNETIFDevice->pkt_service = &NIMU_NDK_pktService;
    pNETIFDevice->ioctl       = &NIMU_NDK_ioctl;
    pNETIFDevice->add_header  = &NIMU_NDK_addEthernetHeader;

    /* Register the device with NIMU */
    if (NIMURegister (pNETIFDevice) < 0)
    {
        dprint("Error: Unable to register the GMACSW\n");
        return -1;
    }

    dprint("Registration of the GMACSW Successful\n");

    return 0;
}

/*!
 *  @b NIMU_NDK_Start
 *  @n
 *  The function is used to initialize and start the GMACSW
 *  controller and device.
 *
 *  \param[in]  pNETIFDevice
 *      NETIF_DEVICE structure pointer.
 *
 *  \retval
 *      Success -   0
 *  \retval
 *      Error   -   <0
 */
static int NIMU_NDK_start(NETIF_DEVICE *pNETIFDevice)
{
    /*This variable tells us if we are dealing with interface 1 or 2*/
    uint32_t devIdx = pNETIFDevice->index-1U;
    int retVal = -1;
    NDK2NSP_Handle hNDK2NSP;

    /* Open the translation layer, which itself opens the hardware driver */
    hNDK2NSP = NDK2NSP_open((STKEVENT_Handle)pNETIFDevice->pvt_data);

    if (NULL != hNDK2NSP)
    {
        /* Save off a pointer to the translation layer */
        pNETIFDevice->pvt_data = (void *) hNDK2NSP;

        /* Copy the MAC Address into the network interface object here. */
        mmCopy(&pNETIFDevice->mac_address[0], &hNDK2NSP->bMacAddr[0], (uint)6U);

        /* Set the 'initial' Receive Filter */
        hNDK2NSP->Filter = ETH_PKTFLT_ALL;
        if(0U == devIdx)
        {
            NDK2NSP_setRx(hNDK2NSP);
        }

        /* Inform the world that we are operational. */
        dprint("GMACSW has been started successfully\n");

        retVal = 0;
    }

    return retVal;
}

/*!
 *  @b NIMU_NDK_Stop
 *  @n
 *  The function is used to de-initialize and stop the GMACSW
 *  controller and device.
 *
 *  \param[in]  pNETIFDevice
 *      NETIF_DEVICE structure pointer.
 *
 *  \retval
 *      Success -   0
 *  \retval
 *      Error   -   <0
 */
/*
 * MISRA-C:2004 Rule 16.7 deviation to match the required function signature
 * defined in nimuif.h
 */
static int NIMU_NDK_stop(NETIF_DEVICE* pNETIFDevice)
{
    deviceInitCount--;

    NDK2NSP_Handle hNDK2NSP;

    /* Get the pointer to the private data */
    hNDK2NSP = (NDK2NSP_Handle )pNETIFDevice->pvt_data;

    /* Call low-level close function */
    NDK2NSP_close(hNDK2NSP);
    
#if !defined(NSP_DYNAMIC_ALLOCATION)
    /* Clear the NETIF_DEVICE memory block. */
    memset(pNETIFDevice, 0, sizeof(NETIF_DEVICE));
#endif

    /* GMACSW Controller has been stopped. */
    return 0;
}

/*!
 *  @b NIMU_NDK_Poll
 *  @n
 *  The function is used to poll the GMACSW controller to check
 *  if there has been any activity
 *
 *  \param[in]  pNETIFDevice
 *      NETIF_DEVICE structure pointer.
 *  \param[in]  timer_tick
 *      Flag to poll the driver.
 *
 *  \retval
 *      void
 */
static void NIMU_NDK_poll(NETIF_DEVICE* pNETIFDevice, unsigned int timer_tick)
{
    /* Call the driver's periodic polling function */
    if (timer_tick)
    {
        /* Get the pointer to the private data */
        NDK2NSP_Handle hNDK2NSP = (NDK2NSP_Handle )pNETIFDevice->pvt_data;

        uint32_t currLinkedInterface, prevLinkedInterface;

        prevLinkedInterface = hNDK2NSP->currLinkedInterface;
        GMACSW_periodicTick(hNDK2NSP->hGMACSW);
        currLinkedInterface = hNDK2NSP->currLinkedInterface;

        if (currLinkedInterface != prevLinkedInterface)
        {
            /* The linked interface has changed, so update MAC address in the NDK stack */
            mmCopy(pNETIFDevice->mac_address, &hNDK2NSP->bMacAddr[currLinkedInterface][0], (uint)6U);
        }
    }
}

/*!
 *  @b NIMU_NDK_Send
 *  @n
 *  The function is the interface routine invoked by the NDK stack to
 *  pass packets to the driver.
 *
 *  \param[in]  pNETIFDevice
 *      NETIF_DEVICE structure pointer.
 *  \param[in]  hPkt
 *      Packet to be sent out on wire.
 *
 *  \retval
 *      Success -   0
 *  \retval
 *      Error   -   <0
 */
/*
 * MISRA-C:2004 Rule 16.7 deviation to match the required function signature
 * defined in nimuif.h
 */
static int NIMU_NDK_send(NETIF_DEVICE* pNETIFDevice, PBM_Handle hPkt)
{
    /*This variable tells us if we are dealing with interface 1 or 2*/
    uint32_t devIdx = pNETIFDevice->index-1U;

    NDK2NSP_Handle hNDK2NSP;

    /* Get the pointer to the private data */
    hNDK2NSP = (NDK2NSP_Handle) pNETIFDevice->pvt_data;

    /*
     * Make sure the driver does not transmit packet less than min. as per the
     * Ethernet standards.
     */
    if (PBM_getValidLen(hPkt) < 60)
    {
        /* Zero pad the packet data to at least 60 known bytes */
        memset ( (void*)( PBM_getDataBuffer(hPkt) +
                          PBM_getDataOffset(hPkt) +
                          PBM_getValidLen(hPkt) ), 0, (size_t)(60U-PBM_getValidLen(hPkt)));
        /* With Ethernet FCS, total transmitted size will be the minimum 64 bytes */
        PBM_setValidLen(hPkt, (uint)60U);
    }

    /* Enqueue the packet */
    My_PBMQ_enq(&hNDK2NSP->txReadyPBMPacketQueue[devIdx], hPkt);

#if defined(NSP_INSTRUMENTATION_ENABLED)
    ndk2NspStats.txReadyPBMPacketEnqueue[devIdx]++;
#endif

    /* Pass the packet to the translation layer */
    NDK2NSP_sendTxPackets(hNDK2NSP, devIdx);

    /* Packet has been successfully transmitted or enqueued to be sent when link comes up */
    return 0;
}

/*!
 *  @b NIMU_NDK_PktService
 *  @n
 *  The function is called by the NDK core stack to receive any packets
 *  from the driver. It is called in the context of the main NDK service
 *  task.
 *
 *  \param[in]  pNETIFDevice
 *      NETIF_DEVICE structure pointer.
 *
 *  \retval
 *      void
 */
static void NIMU_NDK_pktService (NETIF_DEVICE* pNETIFDevice)
{
    /*This variable tells us if we are dealing with interface 1 or 2*/
    uint32_t devIdx = pNETIFDevice->index-1U;

    NDK2NSP_Handle hNDK2NSP;
    PBM_Handle hPBMPacket;

    /* Get the pointer to the private data */
    hNDK2NSP = (NDK2NSP_Handle )pNETIFDevice->pvt_data;

    /* Give all queued packets to the NDK stack */
    hPBMPacket = My_PBMQ_deq(&hNDK2NSP->rxReadyPBMPacketQueue[devIdx]);
    while (hPBMPacket != NULL)
    {
#if defined(NSP_INSTRUMENTATION_ENABLED)
        ndk2NspStats.rxReadyPBMPacketDequeue[devIdx]++;
#endif

        /* Prepare the packet so that it can be passed up the networking stack.
         * If this 'step' is not done the fields in the packet are not correct
         * and the packet will eventually be dropped.  */
        PBM_setIFRx(hPBMPacket, pNETIFDevice);

        /* Pass the packet to the NDK Core stack. */
        NIMUReceivePacket(hPBMPacket);

        /* No need to do this here as already done in LOCAL_prepTFDTPRxPacketQueue function */
#if !defined (TFDTP_STACK_ENABLED)
        /* Allocate a new PBM packet to be used */
        hPBMPacket = PBM_alloc((uint)(hNDK2NSP->PktMTU + (uint32_t)4U + PKT_PREPAD));

        /* Put the new packet on the free queue */
        if (hPBMPacket)
        {
            My_PBMQ_enq(&hNDK2NSP->rxFreePBMPacketQueue, hPBMPacket);
#if defined(NSP_INSTRUMENTATION_ENABLED)
            ndk2NspStats.rxFreePBMPacketEnqueue++;
#endif
        }
#if defined(NSP_INSTRUMENTATION_ENABLED)
        else
        {
            /* This should not happen since NIMUReceivePacket
             * should be returning the packet using PBM_free()
             * and we should just be getting it back right away
             * using PBM_alloc()
             */
            printf("ERROR: PBM_alloc() failure...exiting!\n");
            printf("PBMQ_free count = %d\n",PBMQ_count(&PBMQ_free));
            exit(1);
        }
#endif
#endif
        hPBMPacket = My_PBMQ_deq(&hNDK2NSP->rxReadyPBMPacketQueue[devIdx]);
    }
}

/*!
 *  @b NIMU_NDK_Ioctl
 *  @n
 *  The function is called by the NDK core stack to configure the
 *  driver
 *
 *  \param[in]  pNETIFDevice
 *      NETIF_DEVICE structure pointer.
 *  \param[in]  cmd
 *      Ioctl command.
 *  \param[in]  pBuf
 *      Mac address to be added or deleted.
 *  \param[in]  size
 *      Size of Mac Address.
 *
 *  \retval
 *      Success -   0
 *  \retval
 *      Error   -   <0
 */
/*
 * MISRA-C:2004 Rule 16.7 deviation to match the required function signature
 * defined in nimuif.h
 */
static int NIMU_NDK_ioctl (NETIF_DEVICE* pNETIFDevice, unsigned int cmd, void* pBuf, unsigned int size)
{
    NDK2NSP_Handle  hNDK2NSP;
    uint32_t        count = 0;
    uint32_t        index;
    uint8_t         *mac_address_add_del = (uint8_t *)pBuf;

    /* Get the pointer to the private data */
    hNDK2NSP = (NDK2NSP_Handle )pNETIFDevice->pvt_data;

    /* Process the command. */
    switch (cmd)
    {
        case (unsigned int)NIMU_ADD_MULTICAST_ADDRESS:
        {
            /* Validate the arguments. */
            if ((pBuf == NULL) || (size != 6U))
            {
                return -EINVAL;
            }

            /* We need to add an address to the NIMU Network Interface Object's multicast
             * list. Check for duplicate addresses. */
            while (count < hNDK2NSP->MCastCnt)
            {
                uint8_t *mac_address_list = (uint8_t *)&hNDK2NSP->bMCast[count*6U];

                /* Check for a matching MAC Addresses in the list */
                for (index = 0; index < 6U; index++)
                {
                    if (mac_address_add_del[index] != mac_address_list[index])
                    {
                        break;
                    }
                }

                /* Check if there is a hit or not? */
                if (index == 6U)
                {
                    /* Duplicate MAC address; the address was already present in the list.
                     * This is not an error we will still return SUCCESS here */
                    return 0;
                }

                /* No HIT! Goto the next entry in the device multicast list. */
                count++;
            }

            /* Control comes here implies that the MAC Address needs to be added to the
             * device list. The variable 'count' is pointing to the free location available
             * in which the multicast address can be added. But before we do so check if
             * we dont exceed the upper limit? */
            if (count >= PKT_MAX_MCAST)
            {
                return -ENOMEM;
            }

            /* Add the multicast address to the end of the list. */
            memcpy(&hNDK2NSP->bMCast[count*6U], mac_address_add_del, (size_t)6U);
            hNDK2NSP->MCastCnt++;

            /* Configure the Ethernet controller with the new multicast list. */
            NDK2NSP_setRx(hNDK2NSP);
            break;
        }
        case (unsigned int)NIMU_DEL_MULTICAST_ADDRESS:
        {
            /* Validate the arguments. */
            if ((pBuf == NULL) || (size != 6U))
            {
                return -EINVAL;
            }

            /* We need to delete an address from the NIMU Network Interface Object's multicast
             * list. First cycle through and make sure the entry exists. */
            while (count < hNDK2NSP->MCastCnt)
            {
                uint8_t *mac_address_list = (uint8_t *)&hNDK2NSP->bMCast[count*6U];

                /* Match the MAC Addresses  */
                for ( index=0; index<6U; index++)
                {
                    if( *(mac_address_add_del+index) != *(mac_address_list+index))
                    {
                        break;
                    }
                }

                /* Check if there is a hit or not? */
                if (index == 6U)
                {
                    /* Found the matching entry. We can now delete this! */
                    break;
                }

                /* No HIT! Goto the next entry in the device multicast list. */
                count++;
            }

            /* Did we find a match or not? If not then report the error back */
            if (count == hNDK2NSP->MCastCnt)
            {
                return -EINVAL;
            }

            /* At this time 'count' points to the entry being deleted. We now need to copy all
             * the entries after the 'del' entry back one space in the multicast array. */
            for (index = count; index < (hNDK2NSP->MCastCnt - (uint32_t)1U); index++)
            {
                memcpy(&hNDK2NSP->bMCast[index*6U], &hNDK2NSP->bMCast[(index+1U)*6U], (size_t)6U);
            }

            /* Decrement the multicast entries. */
            hNDK2NSP->MCastCnt--;

            /* Configure the Ethernet controller with the new multicast list. */
            NDK2NSP_setRx (hNDK2NSP);
            break;
        }
        case (unsigned int)NIMU_SET_DEVICE_MAC:
        {
            /* Validate the arguments. */
            if ((pBuf == NULL) || (size != 6U))
            {
                return -EINVAL;
            }
            break;
        }
        /* Let the driver handle rest of the commands */
        default:
        {
            /* call the switch driver's Ioctl handler to take care of this. */
            return (int)NDK2NSP_ioctl(hNDK2NSP, cmd, pBuf, size);
        }
    }
    return 0;
}

/*!
 *  @b NIMU_NDK_addEthernetHeader
 *  @n
 *  The function is called by the NDK core stack to insert the
 *  MAC addresses into the top of a network packet
 *
 *  \param[in]  pNETIFDevice
 *      NETIF_DEVICE structure pointer.
 *  \param[in]  hPkt
 *      PBM_Handle packet handle.
 *  \param[in]  dst_mac
 *      Destination Mac address to be added to frame.
 *  \param[in]  src_mac
 *      Source Mac address to be added to frame
 *      (can be NULL to let this function determine from driver).
 *  \param[in]  ether_type
 *      16-bit ethertype for frame.
 *
 *  \retval
 *      Success -   0
 *  \retval
 *      Error   -   <0
 */
/*
 * MISRA-C:2004 Rule 16.7 deviation to match the required function signature
 * defined in nimuif.h
 */
static int NIMU_NDK_addEthernetHeader(NETIF_DEVICE *pNETIFDevice, PBM_Handle hPkt,
                                      uint8_t *dst_mac, uint8_t *src_mac, uint16_t ether_type )
{
    NDK2NSP_Handle  hNDK2NSP;
    PBM_Pkt* pPkt = (PBM_Pkt *)hPkt;
    ETHHDR*  pEthHdr;

    /* Get the pointer to the private data */
    hNDK2NSP = (NDK2NSP_Handle )pNETIFDevice->pvt_data;

    /* Get the pointer to the packet. */
    pPkt = (PBM_Pkt *)hPkt;
    if (pPkt == NULL)
    {
        return -1;
    }

    /* Check if there is sufficient space to add the header
     * If not then this is a fatal error; we should always have sufficient space
     * allocated at the head of the packet to account for a Layer2 header.
     * Report this to the world. */
    if (pPkt->DataOffset < ETHHDR_SIZE)
    {
        DbgPrintf((uint)DBG_ERROR,"NIMUAddEtherHeader: No space for Ethernet header");
        return -1;
    }

    /* Back up to make room for Ethernet Layer2 header */
    pPkt->DataOffset -= ETHHDR_SIZE;

    /* Get a pointer to the space reserved for the layer2 header. */
    /* Double cast to avoid MISRA-C:2004 11.4 */
    pEthHdr = (ETHHDR *)((void *)(pPkt->pDataBuffer + pPkt->DataOffset));

    /* If a source mac address was specified; use it instead */
    if (src_mac == NULL)
    {
        if (hNDK2NSP->currLinkedInterface == 0)
        {
            mmCopy (pEthHdr->SrcMac, &hNDK2NSP->bMacAddr[0][0], (uint)6U);
        }
        else
        {
            mmCopy (pEthHdr->SrcMac, &hNDK2NSP->bMacAddr[1][0], (uint)6U);
        }
    }
    else
    {
        mmCopy (pEthHdr->SrcMac, src_mac, (uint)6U);
    }

    /* Copy the destination MAC address as is. */
    mmCopy (pEthHdr->DstMac, dst_mac, (uint)6U);

    /* Configure the type in network order. */
    /* FIXME: Assumes little endian */
    pEthHdr->Type = (UINT16) ( ((uint16_t)(((uint16_t)(ether_type >> 8)) & 0x00FFU)) + ((uint16_t)(((uint16_t)(ether_type << 8)) & 0xFF00U)) );

    /* Increment the length to account for the Ethernet Header just added. */
    pPkt->ValidLen = pPkt->ValidLen + (uint)ETHHDR_SIZE;
    return 0;
}


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

