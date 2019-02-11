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
 * ======== lli6if.h ========
 *
 * Extern functions exported by LLI6 module.
 *
 */


#ifndef _C_LLI6_INC
#define _C_LLI6_INC  /* #defined if this .h file has been included */

/* LLI6 Status Defintions: These definitions define the state in which the
 * LLI6 Entry exists. This is as per the Neighbor Unreachability Detection
 * Algorithm. */
#define ICMPV6_LLI_INCOMPLETE   0x1
#define ICMPV6_LLI_REACHABLE    0x2
#define ICMPV6_LLI_STALE        0x3
#define ICMPV6_LLI_DELAY        0x4
#define ICMPV6_LLI_PROBE        0x5
#define ICMPV6_LLI_DEAD			0x6

/** 
 * @brief 
 *  The structure describes the LLI6 Entry. 
 *
 * @details
 *  This is the Neighbor Cache which maps the unicast IPv6 address to the Link Layer 
 *  Address. The structure also contains the necessary information to execute the
 *  Neighbor Unreachability Detection Algorithm.
 *
 *  Since interfaces can have multiple IPv6 addresses. It is possible that there can 
 *  be multiple Unicast IPv6 addresses being mapped to a single LLI6 entry. 
 */
typedef struct LLI6_ENTRY
{
    /**
     * @brief   Links to other LLI6 Objects
     */
    LIST_NODE           links;

    /**
     * @brief   Reference Counter
     */
	UINT32				RefCount;

    /**
     * @brief   The IsRouter Flag is maintained per NEIGH Entry.
     */
    UINT8               IsRouter;

    /**
     * @brief   Device on which the LLI6 Entry exists.
     */
	NETIF_DEVICE* 		ptr_device;

    /**
     * @brief   Packet awaiting resolution.
     */
    PBM_Pkt*            pPkt;

    /**
     * @brief   MAC Address of the Entry.
     */
    UINT8               MacAddr[6];

    /**
     * @brief   Neighbor Status as per the Neighbor Unreachability Detection.
     */
    UINT32              status;

    /**
     * @brief   Source Address to be used while sending Neighbor Solicitations.
     */
    IP6N                SrcAddr;

    /**
     * @brief   Target Address to be used while sending Neighbor Solicitations.
     */
	IP6N                TargetAddr;

    /**
     * @brief   Number of Neighbor Solicitation Probes that have been sent out.
     */
    UINT16              NumProbes;

    /**
     * @brief   Timestamp when the Last NS was sent out.
     */
    UINT32              LastSendNS;

    /**
     * @brief   Timestamp of the Last Reachability Confirmation
     */    
    UINT32              LastReachTS;
}LLI6_ENTRY;

/********************************************************************** 
 * Exported API (KERNEL MODE):
 *  These functions are exported by the LLI6 Module and are available 
 *  for internal NDK core stack usage only.
 ***********************************************************************/
_extern HANDLE LLI6New (RT6_ENTRY* ptr_rt6, UINT8* pMacAddress, UINT8 IsRouter);
_extern void   LLI6Update (HANDLE hLLI6, UINT8* mac_address, UINT32 RxPktType, UINT32 Flags);
_extern void   LLI6Free (HANDLE hLLI6);
_extern UINT8  LLI6IsRouter (HANDLE hLLI6);
_extern UINT8  LLI6IsDead (HANDLE hLLI6);
_extern UINT8  LLI6IsValid (HANDLE hLLI6);
_extern void   LLI6IncRefCount (HANDLE hLLI6);
_extern void   LLI6SetIncomplete (HANDLE hLLI6);
_extern NETIF_DEVICE* LLI6GetNetDevice (HANDLE hLLI6);
_extern void   LLI6TxIPPacket (PBM_Pkt *pPkt, HANDLE hlli6, NETIF_DEVICE* ptr_device, 
							   IP6N Address);

#endif /* _C_LLI6_INC */

