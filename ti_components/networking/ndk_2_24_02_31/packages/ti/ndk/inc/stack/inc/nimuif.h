/*
 * Copyright (c) 2012-2015, Texas Instruments Incorporated
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
 * ======== nimuif.h ========
 *
 * The file contains defintions and structures which describe the network
 * interface management unit.
 *
 */
#ifndef _C_NIMUIF_INC
#define _C_NIMUIF_INC

#include "ip6if.h"

/* Default Limit Definitions for the NIMU. */
#define NIMU_DEFAULT_MAX_DEVICE          256
#define NIMU_DEFAULT_HEADER_RSVD_LEN     20
#define NIMU_DEFAULT_TRAILER_RSVD_LEN    4

/* Interface Name Length */
#define MAX_INTERFACE_NAME_LEN           20

/* Interface Device Flag Definitions:  */

/* These bit masks define the receive properties of the device. */
#define NIMU_PKTFLT_BROADCAST            0x1    /* Device is receiving broadcast packets.     */
#define NIMU_PKTFLT_MULTICAST            0x2    /* Device is configured for multicast filters */
#define NIMU_PKTFLT_ALLMULTICAST         0x4    /* Device is receiving all MULTICAST Frames   */
#define NIMU_PKTFLT_PROMISC              0x8    /* Device is in PROMISC. Mode                 */

#define NIMU_DEVICE_UP                   0x10   /* Device is UP                               */
#define NIMU_DEVICE_NO_ARP               0x20   /* Device does not support ARP.               */

/* Driver is responsible for alloc/free the dev instance (SDOCM00103411) */
#define NIMU_DEVICE_NO_FREE              0x40

/********************************************************************
 *********************** IOCTL Definitions **************************
 ********************************************************************/

#define NIMU_IOCTL_RANGE_START          100

/* Special case commands: These commands should have the NIMU Interface
 * request set as NULL. */
#define NIMU_GET_NUM_NIMU_OBJ           (NIMU_IOCTL_RANGE_START + 1)
#define NIMU_GET_ALL_INDEX              (NIMU_IOCTL_RANGE_START + 2)

#define NIMU_GET_DEVICE_HANDLE          (NIMU_IOCTL_RANGE_START + 10)
#define NIMU_GET_DEVICE_MTU             (NIMU_IOCTL_RANGE_START + 11)
#define NIMU_SET_DEVICE_MTU             (NIMU_IOCTL_RANGE_START + 12)
#define NIMU_GET_DEVICE_MAC             (NIMU_IOCTL_RANGE_START + 13)
#define NIMU_SET_DEVICE_MAC             (NIMU_IOCTL_RANGE_START + 14)
#define NIMU_GET_DEVICE_FLAGS           (NIMU_IOCTL_RANGE_START + 15)
#define NIMU_SET_DEVICE_FLAGS           (NIMU_IOCTL_RANGE_START + 16)
#define NIMU_GET_DEVICE_NAME            (NIMU_IOCTL_RANGE_START + 17)
#define NIMU_GET_DEVICE_INDEX           (NIMU_IOCTL_RANGE_START + 18)
#define NIMU_ADD_MULTICAST_ADDRESS      (NIMU_IOCTL_RANGE_START + 19)
#define NIMU_DEL_MULTICAST_ADDRESS      (NIMU_IOCTL_RANGE_START + 20)

#define NIMU_IOCTL_RANGE_END            150

/*********************************************************************
 * STRUCTURE NAME : NETIF_DEVICE
 *********************************************************************
 * DESCRIPTION   :
 *  The structure describes the network interface object. Each device
 *  driver in the system which is attached to the NDK stack should be
 *  associated with an instance of this object. The object describes
 *  the interface between the NDK Core stack and the drivers.
 *********************************************************************/
typedef struct NETIF_DEVICE
{
    /* Links to other network devices. */
    LIST_NODE   links;

    /* Reference Counter: This indicates the number of references of the
     * network interface object is held by components. Network Interface 
     * Objects can only be removed from the system if there are no 
     * references of it held in the System. */
     uint       RefCount;

    /* These are the two identifiers which are associated with each network
     * interface device. The "index" is a numeric representation and the 
     * "name" is a more user friendly string representation of the same. 
     * 
     * NOTES: 
     * Driver Authors can specify these; but in the case of conflicts
     * these values will be modified to be unique in the system. Thus if 
     * driver authors are using these in their code it is best to re-read
     * these values after the 'registration' process. */
    uint        index;
    char        name[MAX_INTERFACE_NAME_LEN];

    /* This defines the interface flags. 
     *
     * NOTES:
     * Driver authors should not set this value as this is used for internal
     * operations inside the NDK stack. */
    uint        flags;

    /* This defines the interface type. 
     *
     * NOTES:
     *  For compatibility with the old network interface object; this is set to
     *  HTYPE_ETHER or HTYPE_PPP; depending on the type of network interface 
     *  object. Moving forward this field will be obsoleted and instead
     *  application authors should use the field instead.
     */
    uint        type;

    /* This is the Max. Protocol MTU associated with the device.
     *
     * NOTES:
     * Driver authors should configure this value to the MAX. Data payload
     * that can be carried without the corresponding Layer2 Header. Thus for
     * example in Ethernet this will be 1514 (Max. Data Payload) - 14 (L2
     * Ethernet Header) = 1500. */
    uint        mtu;

    /* MAC Address with the device. */
    UINT8       mac_address[6];

    /* Pointer to 'private data' associated with the device. This data 
     * pointer is opaque to the NDK stack. 
     *
     * NOTES:
     * Driver authors can use this to store any additional 'driver' 
     * specific data here. Memory allocation and cleanup of this 
     * private block is the responsibility of the driver. */
    void*       pvt_data;

    /*****************************************************************
     ***************** Driver Interface Functions ******************** 
     *****************************************************************/

    /***************************************************************** 
     * The device start function; which is called to initialize and start
     * the driver. The driver should be able to send and receive packets
     * after the successful completion of this API. 
     *
     * RETURNS:
     *  0   -   Success
     *  <0  -   Error
     *****************************************************************/
    int  (*start)(struct NETIF_DEVICE* ptr_net_device);

    /***************************************************************** 
     * The device stop function; which is called to de-initialize and 
     * stop the driver. The driver should NOT send and receive packets 
     * after the successful completion of this API. 
     *
     * RETURNS:
     *  0   -   Success
     *  <0  -   Error
     *****************************************************************/
    int  (*stop)(struct NETIF_DEVICE* ptr_net_device);
    
    /***************************************************************** 
     * The device poll function; which is called by the NDK stack to 
     * poll and check for driver activity. This is a useful function 
     * and can be used by the drivers to check for link activity, 
     * receive and transmit watchdog support etc.
     *****************************************************************/
    void (*poll)(struct NETIF_DEVICE* ptr_net_device, uint timer_tick);

    /*****************************************************************
     * The device send function; which is called by the NDK stack to 
     * pass packets to the driver. On SUCCESS the driver owns the packet 
     * memory and is responsible for cleaning the packet. On ERROR the 
     * NDK core stack will clean the packet memory.
     *
     * RETURNS:
     *  0   -   Success
     *  <0  -   Error
     *****************************************************************/
    int  (*send)(struct NETIF_DEVICE* ptr_net_device, PBM_Handle hPkt);

    /***************************************************************** 
     * The device packet service function; which is called by the NDK 
     * stack scheduler to receive packets from the driver. 
     *****************************************************************/
    void (*pkt_service) (struct NETIF_DEVICE* ptr_net_device);

    /***************************************************************** 
     * The device IOCTL Function is a standard interface to be able to
     * get and set certain device specific parameters. The IOCTL 
     * function is called within the NDK llEnter and llExit critical 
     * sections.
     *
     * RETURNS:
     *  0   -   Success
     *  <0  -   Error
     *****************************************************************/
    int (*ioctl)(struct NETIF_DEVICE* ptr_net_device, uint cmd, void* pbuf,
            uint size);

    /*****************************************************************
     * The device header manipulation function. The NDK Core stack will
     * ensure that the appropriate Layer2 is added to the packet by 
     * calling this function before the packet is passed to the driver
     * through the 'send' API mentioned above. 
     *
     * RETURNS:
     *  0   -   Success
     *  <0  -   Error
     *
     * NOTES  :
     * If the driver being written is a standard 'Ethernet' driver the
     * driver author should ensure that the API 'ether_attach' is 
     * invoked during the 'start' API. This will initialize it 
     * correctly for all 'Ethernet' devices. But at the same time if 
     * this is a driver beyond standard 'Ethernet' it can be used to add
     * 'custom L2' headers.
     *****************************************************************/
    int (*add_header) (struct NETIF_DEVICE* ptr_net_device, PBM_Handle hPkt, 
                       UINT8* dst_mac, UINT8* src_mac, UINT16 ether_type);

    /* Pointer to the IPv6 Device record which is used by the IPv6
     * stack for storing IPv6 specific information. 
     *
     * NOTES:
     * Driver authors should not -use- this field. It is allocated
     * and cleaned up the internal IPv6 stack. */
    IPV6_DEV_RECORD*    ptr_ipv6device;
}NETIF_DEVICE;

/*********************************************************************
 * STRUCTURE NAME : NIMU_DEVICE_TABLE_ENTRY
 *********************************************************************
 * DESCRIPTION   :
 *  The structure defines the NIMU Device Table entry. This entry needs
 *  to be populated by the NDK driver authors to the initialization 
 *  function of each network device in the system. 
 *********************************************************************/
typedef struct NIMU_DEVICE_TABLE_ENTRY
{
    /*****************************************************************
     * The driver initialization function which is invoked by the NDK
     * core stack during its own initialization sequence. Driver 
     * authors should use this function to initialize the driver and
     * register it with the NIMU.
     *
     * RETURNS:
     *  0   -   Success
     *  <0  -   Error
     *
     * NOTES:
     *  This function should always have a call to NIMURegister else
     *  the driver is not attached to the NDK core stack and will not
     *  operate.
     *****************************************************************/
    int (*init) (STKEVENT_Handle hEvent);
}NIMU_DEVICE_TABLE_ENTRY;

/*********************************************************************
 * STRUCTURE NAME : NIMU_IF_REQ
 *********************************************************************
 * DESCRIPTION   :
 *  The structure is the NIMU Interface request object which is passed
 *  to the NIMU module through the IOCTL interface.  
 *********************************************************************/
typedef struct NIMU_IF_REQ
{
    uint    index;          /* Device Index associated with NIMU */
    char    name[MAX_INTERFACE_NAME_LEN]; /* Device Name         */
}NIMU_IF_REQ;

/*********************************************************************
 * DESCRIPTION   :
 *  The NIMUDeviceTable is a NULL terminated array of driver 
 *  initialization functions which is called by the NDK Network 
 *  Interface Management functions during the NDK Core Initialization.
 *  The table needs to be populated by the driver authors for each 
 *  platform to have a list of all driver initialization functions. 
 *********************************************************************/
extern NIMU_DEVICE_TABLE_ENTRY  NIMUDeviceTable[];

/**********************************************************************
 *********************** NIMU Extern Functions  ***********************
 **********************************************************************/

/********************************************************************** 
 * NDK Core Stack Usage Only:
 * These functions are used 'internally' by the NDK core stack and should
 * not be used by any application or driver. 
 ***********************************************************************/
_extern int           NIMUInit (STKEVENT_Handle hEvent);
_extern void          NIMUShutdown (void);
_extern void          NIMUPacketService (void);
_extern void          NIMUPacketServiceCheck (int fEvents);
_extern PBM_Pkt*      NIMUCreatePacket (uint packet_size);
_extern void          NIMUSendPacket (HANDLE hIF, PBM_Pkt *pPkt);
_extern NETIF_DEVICE* NIMUFindByIndex (uint index);
_extern NETIF_DEVICE* NIMUFindByName (char* name);
_extern int           NIMUAddEthernetHeader (NETIF_DEVICE* ptr_net_device, PBM_Handle hPkt, 
                                             UINT8* dst_mac, UINT8* src_mac, UINT16 ether_type);
_extern int           NIMUAddHeader (NETIF_DEVICE* ptr_net_device, PBM_Handle hPkt, 
                                     UINT8* dst_mac, UINT8* src_mac, UINT16 protocol);

/********************************************************************** 
 * Exported API (KERNEL MODE):
 * These functions are exported by the NIMU Module and are available
 * for application and driver authors to use. These functions need to 
 * be invoked only from 'kernel' mode. 
 ***********************************************************************/ 
_extern void NIMUSetRsvdSizeInfo (int header_size, int trailer_size);
_extern void NIMUGetRsvdSizeInfo (int* header_size, int* trailer_size);
_extern int  NIMURegister (NETIF_DEVICE* ptr_netif_device);
_extern int  NIMUUnregister (NETIF_DEVICE* ptr_netif_device);
_extern int  NIMUReceivePacket (PBM_Handle hPkt);

/********************************************************************** 
 * Exported API (KERNEL MODE SAFE):
 *  This function is a configuration GET/SET access function and is 
 *  used to configure the NIMU module or the drivers attached to the 
 *  NIMU module. This is available to all the application and driver
 *  authors. This function can be called from outside the 'kernel'
 *  mode. 
 ***********************************************************************/ 
_extern int  NIMUIoctl(uint cmd, NIMU_IF_REQ* ptr_nimu_ifreq, void* pBuf, uint size);

#endif /* _C_NIMUIF_INC */
