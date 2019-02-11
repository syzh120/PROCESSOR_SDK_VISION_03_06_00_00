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
 * ======== ipv6_frag.c ========
 *
 * The file handles the IPv6 Fragment Reassembly processing.
 *
 */

#include <stkmain.h>
#include "ipv6.h"

#ifdef _INCLUDE_IPv6_CODE

/**********************************************************************
 *************************** Local Structures *************************
 **********************************************************************/

/** 
 * @brief 
 *  The structure describes the Fragment Reassembly Queue. 
 *
 * @details
 *  This data structure identifies all the IPv6 fragment packets awaiting 
 *  reassembly for a given Fragment ID, IPv6 Source Address and IPV6 
 *  Destination Address.
 *
 */
typedef struct FRAG6Q
{
    /**
     * @brief   Links to other FRAG6Q Objects
     */
    LIST_NODE       Links;           

    /**
     * @brief   Type of the Fragment
     */
    UINT32          Type;           

    /**
     * @brief   Unique Identification number for fragments in this queue
     */
    UINT32          Id;             

    /**
     * @brief   IPv6 Source Address of the fragments in this queue.
     */
    IP6N            Srcaddr;        

    /**
     * @brief   IPv6 Destination Address of the fragments in this queue.
     */
    IP6N            Dstaddr;        

    /**
     * @brief   Sorted list of all the fragments in this queue. The fragments
     *          are sorted in increasing order of their offsets.
     */
    PBM_Pkt*        Fragments;      

    /**
     * @brief   Maximum timeout for reassembly of fragments in this queue. 
     *          Its measured from the time instance queue is created. Beyond this 
     *          time, all fragments in the queue are discarded and fragment 
     *          reassembly for this packet is aborted.
     */
    UINT32          Timeout;        

    /**
     * @brief   Next Header Offset of the last extension header in the
     *          unfragmentable part of Fragment 0 of this queue.
     */
    UINT32          NextHdrOffset;  
                                    
    /**
     * @brief   Next Header value from the Fragment 0 of this queue.
     */
    UINT8              NextHdrValue;
}FRAG6Q;

/**********************************************************************
 *************************** Local Definitions ************************
 **********************************************************************/

/* Flags to mark the position of fragment in its fragment queue */
#define FRAG_LAST       0x80000000
#define FRAG_MIDDLE     0x40000000
#define FRAG_FIRST      0x20000000

/* Bit mask to extract the 13 bit fragment offset from the 
 * Fragmentation header of the packet.
 */
/*
 * |-+-+-+-+-+-+-+-+-+-+-+-+-|-+-+|-+|
 * |    Fragment Offset      |Rsvd| M|
 *  ---------------------------------
 */
#define FRAG_OFFSET     0x0000FFF8

/* Time in seconds after which reassembly of fragments in
 * a specified fragment queue is abandoned. The default 
 * value specified by RFC 2460 is 60 seconds.
 */
#define IPV6_FRAG6Q_MAXTIME     60

/* Timer messages to track IPv6 Fragment Reassembly */
#define MSG_IPV6_NEED_REASM_TIMER   (ID_IPV6*MSG_BLOCK + 1)
#define MSG_IPV6_REASM_TIMER        (ID_IPV6*MSG_BLOCK + 2)

/**********************************************************************
 *************************** Global Variables *************************
 **********************************************************************/

/* Global variable to hold the list of IPv6 fragment queues awaiting
 * reassembly in the stack.
 */
FRAG6Q* gFragQList = NULL;

/* IPv6 Reassembly Timer */
static HANDLE hIPv6ReasmTimer;

/* Global variable to track the fragment Identifiers for all
 * the fragments we generate while transmitting large packets.
 * RFC 2460 defines this as a 32 bit unsigned integer.
 */
static UINT32   gFragIdCtr = 1;

/**********************************************************************
 ************ IPV6 Fragment Reassembly Handling Functions *************
 **********************************************************************/

/** 
 *  @b Description
 *  @n  
 *      This function disposes all fragments buffered in
 *      the queue and cleans the queue. It also updates 
 *      reassembly stats accordingly.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_fragQ
 *      Fragment queue onto which the fragment needs to be buffered.
 *
 *  @param[in]  fUpdateStats
 *      This flag when set to 1 indicates that the queue is being 
 *      cleaned up because of an error like Reassembly Timeout
 *      /Reassembly error.
 *
 *  @retval
 *      None
 */
static void IPv6FragQFree (FRAG6Q *ptr_fragQ, uint fUpdateStats)
{
    PBM_Pkt *pPkt = NULL;

    /* Unlink this fragQ from the global list of fragment buffers list */
    list_remove_node ((LIST_NODE**)&gFragQList, (LIST_NODE*)ptr_fragQ);    

    /* Free all the fragments queued in this fragQ. */
    while( (pPkt = ptr_fragQ->Fragments) )
    {
        ptr_fragQ->Fragments = pPkt->pNext;
        PBM_free( pPkt );

        /* If this is set to 1, we are here because of a
         * reassembly error, so increment dropped stats.
         */
        if( fUpdateStats )
        {
#ifdef IPV6_REASM_DEBUG
            DbgPrintf(DBG_INFO, "IPv6FragQFree: TODO: Increment the dropped frag stats \n");
#endif
        }
    }

    /* Free the fragQ */
    mmFree( ptr_fragQ );

    return;
}

/** 
 *  @b Description
 *  @n  
 *      This function iterates through all fragmentation
 *      queues, and checks for any timeouts. If it finds
 *      a queue whose reassembly process has been initiated
 *      over MAX_IPV6_REASMTIME, then the fragQ is cleaned 
 *      up.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @retval
 *      None
 */
static void IPv6ReasmTimeout (void)
{
    FRAG6Q  *ptr_fragQ;
    UINT32 TimeNow;

    /* Get the current time tick. */
    TimeNow = llTimerGetTime(0);

    /* Iterate through list of fragment queues */
    ptr_fragQ = (FRAG6Q *)list_get_head ((LIST_NODE**)&gFragQList);
    while (ptr_fragQ != NULL)
    {
        /* RFC 2460 - Section 4.5
         * The following error conditions may arise when reassembling
         * fragmented packets:
         * If insufficient fragments are received to complete reassembly
         * of a packet within 60 seconds of the reception of the first-
         * arriving fragment of that packet, reassembly of that packet 
         * must be abandoned and all the fragments that have been received
         * for that packet must be discarded. If the first fragment (i.e., 
         * the one with a fragment offset of zero) has been received, an 
         * ICMP Time Exceeded -- Fragment Reassembly Time Exceeded message
         * should be sent to the source of that fragment.
         */
        /* Uh-oh, this fragQ is over it's reassembly time. This
         * must be cleaned up.
         */
        if( ptr_fragQ->Timeout < TimeNow )
        {
            if(ptr_fragQ->Fragments->Aux1 & FRAG_FIRST)
                ICMPv6SendTimeExceeded (ICMPV6_TIME_EXCEEDED_FRAGMENT, ptr_fragQ->Fragments);

            /* Clean up the fragment queue */
            IPv6FragQFree( ptr_fragQ, 1 );
        }

        /* Get the next fragmentation queue entry. */
        ptr_fragQ = (FRAG6Q *)list_get_next((LIST_NODE*)ptr_fragQ);
    }
}

/** 
 *  @b Description
 *  @n  
 *      IPv6 Fragmentation & Reassembly module's
 *      event handling function.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  Msg
 *      The message event which needs to be handled.
 *
 *  @retval
 *      None.
 */
void IPv6FragMsg (uint Msg)
{
    switch (Msg)
    {
        /* System Initialization */
        case MSG_EXEC_SYSTEM_INIT:
        {
            hIPv6ReasmTimer = 0;
            break;
        }
        /* System Shutdown */
        case MSG_EXEC_SYSTEM_SHUTDOWN:
        {
            /* System is shutting down. */
        
            /* Flush the IPv6 Reassembly queue */
            while( gFragQList )
                IPv6FragQFree( gFragQList, 1 );

            if (hIPv6ReasmTimer)
            {
                /* Close the IPv6 Reassembly Timer. */
                TimerFree (hIPv6ReasmTimer);
                hIPv6ReasmTimer = 0;
            }
            break;
        }
        case MSG_IPV6_NEED_REASM_TIMER:
        {
            /* Create the IPv6 Fragment Reassembly timer if not already
             * running. 
             */
            if (!hIPv6ReasmTimer)
            {
                hIPv6ReasmTimer = TimerNew( &IPv6FragMsg, TIMER_TICKS_IPV6_REASM, MSG_IPV6_REASM_TIMER );
            }
            break;
        }
        /* Half Second Timer Tick */
        case MSG_IPV6_REASM_TIMER:
        {
            /* Cycle through all the IPv6 Entries and update them appropriately. */
            if( gFragQList )
                IPv6ReasmTimeout();
            /* If no outstanding fragment reassembly queues,
             * cleanup the timer.
             */
            else
            {
                if (hIPv6ReasmTimer)
                {
                    /* Close the IPv6 Reassembly Timer. */
                    TimerFree (hIPv6ReasmTimer);
                    hIPv6ReasmTimer = 0;
                }
            }
            break;
        }
    }
}

/** 
 *  @b Description
 *  @n  
 *      This function is called to create a fragmentation queue
 *      that buffers all fragments matching a given tuple specified by
 *      <source IPv6 address, destination IPv6 address, Fragment Id>.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  id
 *      Fragment ID of this fragment. Fragment ID is a 32 bit unsigned
 *      integer uniquely identifying the fragments generated from a given
 *      packet.
 *
 *  @param[in]  srcaddr
 *      The IPv6 Source Address of the fragment.
 *  
 *  @param[in]  dstaddr
 *      The IPv6 Destination Address of the fragment.
 *
 *  @retval
 *      Success -   Handle to the corresponding FragQ Entry
 *  @retval
 *      Error   -   NULL
 */
static FRAG6Q*  IPv6CreateFragQ (UINT32 id, IP6N srcaddr, IP6N dstaddr)
{
    FRAG6Q*   ptr_fragQ = NULL;

    /* Allocate memory for a new fragmentation queue entry. */
    if ((ptr_fragQ = mmAlloc (sizeof(FRAG6Q))) == NULL)
    { 
        NotifyLowResource();
        return NULL;
    }

    /* Initialize the allocated block of memory. */
    mmZeroInit ((void *)ptr_fragQ, sizeof(FRAG6Q));

    /* Initialize and populate the new fragment queue */
    ptr_fragQ->Type = HTYPE_IPFRAG;
    ptr_fragQ->Id = id;
    ptr_fragQ->Srcaddr = srcaddr;
    ptr_fragQ->Dstaddr = dstaddr;
    ptr_fragQ->Timeout = llTimerGetTime(0) + IPV6_FRAG6Q_MAXTIME;

    /* Add the new fragment queue to the existing list. */
    list_add ((LIST_NODE**)&gFragQList, (LIST_NODE*)ptr_fragQ);

    /* Start the IPv6 Fragment Reassembly Timer if not running already */
    IPv6FragMsg (MSG_IPV6_NEED_REASM_TIMER);

    /* Return the handle to the new fragQ we just created */
    return ptr_fragQ;
}

/** 
 *  @b Description
 *  @n  
 *      This function is called to find the fragmentation queue
 *      matching a given tuple specified by 
 *      <source IPv6 address, destination IPv6 address, Fragment Id>.
 *      If no existing fragmentation queue is found matching the given
 *      arguments (meaning that no fragments matching the source, 
 *      destination IP addresses and fragment ID have ever reached us), 
 *      this function in turn calls IPv6CreateFragQ to create the 
 *      necessary fragmentation queue. 
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  id
 *      Fragment ID of this fragment. Fragment ID is a 32 bit unsigned
 *      integer uniquely identifying the fragments generated from a given
 *      packet.
 *
 *  @param[in]  srcaddr
 *      The IPv6 Source Address of the fragment.
 *  
 *  @param[in]  dstaddr
 *      The IPv6 Destination Address of the fragment.
 *
 *  @retval
 *      Success   -   Handle to the corresponding FragQ Entry
 *  @retval
 *      Error   -   NULL
 */
static FRAG6Q* IPv6FindFragQ (UINT32 id, IP6N srcaddr, IP6N dstaddr)
{
    FRAG6Q*   ptr_fragQ = NULL;

    /* Search the fragmentation queue for a match? */
    ptr_fragQ = (FRAG6Q *)list_get_head ((LIST_NODE**)&gFragQList);
    while (ptr_fragQ != NULL)
    {
        /* RFC 2460 - Section 4.5
         * The following rules govern reassembly:
         * An original packet is reassembled only from fragment
         * packets that have the same Source Address, 
         * Destination Address, and Frgament Identification.
         */
        /* Do we have a match? */
        if ((IPv6CompareAddress(ptr_fragQ->Srcaddr, srcaddr) == 1)
             && (IPv6CompareAddress(ptr_fragQ->Dstaddr, dstaddr) == 1)
             && (ptr_fragQ->Id == id))
            return ptr_fragQ;

        /* Get the next fragmentation queue entry. */
        ptr_fragQ = (FRAG6Q *)list_get_next((LIST_NODE*)ptr_fragQ);
    }

    /* If we are here, we didnt find a fragmentation queue
     * matching our source, destination addresses and
     * fragment ID. So, we create one.
     */
    ptr_fragQ = IPv6CreateFragQ (id, srcaddr, dstaddr);

    /* Return the handle to FragQ */
    return ptr_fragQ;
}

/** 
 *  @b Description
 *  @n  
 *      This function is called to buffer a fragment packet onto a 
 *      specified fragment queue for reassembly later.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_fragQ
 *      Fragment queue onto which the fragment needs to be buffered.
 *
 *  @param[in]  pPkt
 *      Packet to enqueue.
 *  
 *  @param[in]  ptr_fraghdr
 *      Pointer to fragment header of the packet.
 *
 *  @param[in]  ptr_ipv6hdr
 *      Pointer to IPv6 header of the packet.
 *
 *  @retval
 *      Success -   Handle to the corresponding FragQ Entry
 *  @retval
 *      Error   -   NULL
 */
static int IPv6FragQEnqueueFrag (FRAG6Q* ptr_fragQ, PBM_Pkt* pPkt, IPV6_FRAGHDR* ptr_fraghdr, IPV6HDR* ptr_ipv6hdr)
{
    UINT32      Offset, DataLen, End, errPointer;
    PBM_Pkt*    pPktTmp = NULL;
#ifdef IPV6_REASM_DEBUG
    UINT32      FragId;
#endif

    /* Validate input */
    if(!ptr_fragQ || !pPkt || !ptr_ipv6hdr || !ptr_fraghdr)
        return -1;

    /* Get the Fragment offset in bytes */
    Offset = (ntohs(ptr_fraghdr->FragOffset & 0xFFFF) & FRAG_OFFSET);

#ifdef IPV6_REASM_DEBUG
    /* Get the fragment Id */
    FragId = RdNet32(&ptr_fraghdr->FragId);
    DbgPrintf(DBG_INFO, "IPv6FragQEnqueueFrag: FragId: %d \n", ntohl(FragId & 0xFFFFFFFF));
#endif

    /* Calculate the actual length of data in the fragment. 
     * Data length = IPv6 Payload length - Length of extension headers
     * Extenstion header length = (End of Fragmentation header)  - (End of IPv6 Header)
     */
    DataLen = (ntohs(ptr_ipv6hdr->PayloadLength) 
          - ((UINT8 *) (ptr_fraghdr + 1) - (UINT8 *) (ptr_ipv6hdr + 1)));

    End = Offset + DataLen;

    /* RFC 2460 - Section 4.5
     * The following error conditions may arise when reassembling
     * fragmented packets:
     * If the length and offset of a fragment are such that the 
     * Payload Length of the packet reassembled from the fragment would
     * exceed 65,535 octets, then that fragment must be discarded and an
     * ICMP Parameter Problem, Code 0, message should be sent to the source
     * of the fragment, pointing to the Fragment Offset field of the 
     * fragment packet.
     */
    if(DataLen > MAX_IPV6_PKTSIZE || DataLen <= 0) 
    {
        errPointer = (UINT8 *)&ptr_fraghdr->FragOffset - (UINT8 *)ptr_ipv6hdr;
        ICMPv6SendParameterProblem (ICMPV6_PARAM_PROBLEM_ERR_HEADER, pPkt, errPointer);
        return -1;
    }

    /* Is this the fragment 0 for this queue ? */
    if(!Offset)
    {
       /* RFC 2460 - Section 4.5
        * The following error conditions may arise when reassembling
        * fragmented packets:
        * If the length of a fragment, as derived from the fragment
        * packet's Payload Length field, is not a multiple of 8 octets
        * and the M flag of that fragment is 1, then that fragment must
        * be discarded and an ICMP Parameter Problem, Code 0, message 
        * should be sent to the source of the fragment, pointing to the
        * payload length field of the fragment packet.
        */
       /* Check if the fragment is a multiple of 8 octets and MF bit set? */
       if ((End & 0x7) && (ntohs(ptr_fraghdr->FragOffset & 0xFFFF) & IPV6_MF_BIT))
       {
            errPointer = (UINT8 *)&ptr_ipv6hdr->PayloadLength - (UINT8 *)ptr_ipv6hdr;
            ICMPv6SendParameterProblem (ICMPV6_PARAM_PROBLEM_ERR_HEADER, pPkt, errPointer);
            return -1;
        }

        /* As the fragment 0 packet was passed along from the IPv6Rxpacket 
         * through various extension header processing, at every point, 
         * we store the offset of the "NextHeader" field of that header in the 
         * "Aux1" field of the packet. This is required during reassembly, because
         * this indicates the NextHeader value of the first extension header of
         * the fragmentable part of the original packet.
         *
         * RFC 2460 - Section 4.5
         * The Next Header field of the last header of the Unfragmentable part
         * is obtained from the Next Header field of the first fragment's
         * fragment header
         */
        /* Copy over the NextHdrOffset of previous header from Packet 
         * before we overwrite it with offset and flags.
         */
        ptr_fragQ->NextHdrOffset = (UINT32) (pPkt->Aux1);
        ptr_fragQ->NextHdrValue = ptr_fraghdr->NextHeader;

        /* Aux1 is used to store flags and the fragment offset 
         * which indicate the fragment's position in the
         * fragment buffer/queue. Used in reassembly.
         * For fragment 0, the Offset is set to end of unfragmentable
         * part of the original packet, i.e. points to position after
         * (IPv6 Header + extension headers before fragment header)
         */
        pPkt->Aux1 = FRAG_FIRST;
        pPkt->Aux1 |= pPkt->IpHdrLen;
    }
    else
    {
        /* If "More Fragment" bit not set, this is the last fragment */
        if(!(ntohs(ptr_fraghdr->FragOffset & 0xFFFF) & IPV6_MF_BIT))
        {
#ifdef IPV6_REASM_DEBUG
          DbgPrintf(DBG_INFO, "IPv6FragQEnqueueFrag: received last frag len: %u \n", len);
#endif
            /* Mark the fragment flags as last */
            pPkt->Aux1 = FRAG_LAST;
        }
        else
        {
            /* RFC 2460 - Section 4.5
             * The following error conditions may arise when reassembling
             * fragmented packets:
             * If the length of a fragment, as derived from the fragment
             * packet's Payload Length field, is not a multiple of 8 octets
             * and the M flag of that fragment is 1, then that fragment must
             * be discarded and an ICMP Parameter Problem, Code 0, message 
             * should be sent to the source of the fragment, pointing to the
             * payload length field of the fragment packet.
            */
            /* Check if the fragment is a multiple of 8 octets ? */
            if (End & 0x7)
            {
                errPointer = (UINT8 *)&ptr_ipv6hdr->PayloadLength - (UINT8 *)ptr_ipv6hdr;
                ICMPv6SendParameterProblem (ICMPV6_PARAM_PROBLEM_ERR_HEADER, pPkt, errPointer);
                return -1;
            }
                
            /* Since offset of this fragment is not zero and 
             * the MF bit is set to 1, this has to be a middle
             * fragment. Mark the appropriate flags in Aux1.
             * Used during reassembly
             */
            pPkt->Aux1 = FRAG_MIDDLE;
        }

        /* Mark the fragment's offset in the Aux1. 
         * Used during reassembly.
         */
        pPkt->Aux1 |= Offset;
    }

    /* In the final packet, there will be no fragmentation
     * header, so move the packet offsets accordingly to
     * skip over the Fragmentation header. We have no use
     * for it now, since we have already copied over the
     * NextHeader value from frag header of fragment 0 to
     * fragQ. That's all we need.
     */
     pPkt->DataOffset += IPV6_FRAGHDR_SIZE;
     pPkt->ValidLen   -= IPV6_FRAGHDR_SIZE;

    /* Aux2 is used to store the fragment length */
    pPkt->Aux2 = (UINT32)DataLen;

    /* Iterate through the fragments already buffered, and insert 
     * the fragment packet into the correct place in the list
     * according to its offset and flags.
     */
    /* This is the first fragment/fragment 0 for this fragment 
     * buffer queue. Insert the fragment at fragQ head.
     */
    if( !(pPktTmp=ptr_fragQ->Fragments) || (pPkt->Aux1 <= pPktTmp->Aux1) )
    {
        ptr_fragQ->Fragments = pPkt;
        pPkt->pPrev = NULL;
        pPkt->pNext = pPktTmp;
    }
    else
    {
        /* Find the right place for fragment in the queue */
        while( pPktTmp->pNext && (pPktTmp->pNext->Aux1 < pPkt->Aux1) )
            pPktTmp = pPktTmp->pNext;

        /* Adjust fragment pointers accordingly */
        pPkt->pPrev = pPktTmp;
        pPkt->pNext = pPktTmp->pNext;
        pPktTmp->pNext = pPkt;
    }
    if( pPkt->pNext )
        pPkt->pNext->pPrev = pPkt;

    /* We are done enqueuing the fragment in the fraQ.
     * return SUCCESS.
     */
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      This function checks if the fragment queue/buffer
 *      has enough fragments to be reassembled back into
 *      the original packet. If so, it reassembles all
 *      the fragments and sends the reassembled packet up
 *      the stack for further processing. 
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_fragQ
 *      Fragment queue onto which the fragment needs to be buffered.
 *
 *  @retval
 *      -1  -   Fatal Error while reassembling packets in the queue. 
 *              Clean Fragment queue and abort reassembly.
 *  @retval
 *      0   -   Success, Packet reassembled successfully and 
 *              transmitted up the stack.
 *  @retval
 *       1  -   Not enough fragments to reassemble the packet yet.
 *              Try back later.
 */
static int IPv6FragReasm (FRAG6Q* ptr_fragQ)
{
    PBM_Pkt*    pPkt = NULL;
    UINT32      AccLen , Offset = 0, FragLen = 0;
    PBM_Pkt     *pPktTmp = NULL;
    UINT8       *pBuff = NULL;
    IPV6HDR*    ptr_ipv6hdr = NULL;

    /* Now, we'll go ahead and go through all the queued
     * fragments to see if we can make a complete packet.
     */
    pPkt = ptr_fragQ->Fragments;

    /* Do, we have Fragment 0 yet? */
    if (!(pPkt->Aux1 & FRAG_FIRST))
        return 1;

    /* Running length (not including IP header) of the
     * fragments accumulated so far
     */
    AccLen = 0;

    /* Calculate the total accumulated length of fragments */
    while (pPkt)
    {
        /* If this is the first fragment, initialize the
         * accumulated length.
         */
        if (pPkt->Aux1 & FRAG_FIRST)
        {
            /* Make sure we record the largest size */
            if  (pPkt->Aux2 > AccLen)
                AccLen = pPkt->Aux2;
        }
        else
        {
            /* Check for any holes in data accumulation, i.e.,
             * a hole occurs when there are any fragments missing
             * from the queue. we'll check back later for reassembly.
             */
            FragLen = pPkt->Aux1 & FRAG_OFFSET;
            if (FragLen > AccLen)
                return 1;

            /* Check for any data overlap, i.e. we receive 2 distinct
             * fragments whose data overlaps each other.
             */
            FragLen = AccLen - FragLen;      
            if (pPkt->Aux2 > FragLen)
            {
                /* Combine the overlapping fragment lengths. */
                AccLen += pPkt->Aux2 - FragLen;
            }

           /* If no holes found, and we reached the last fragment,
            * we are done. we are ready for reassembly. we have
            * successfully calculated the total accumulated
            * fragment length.
            */
            if (pPkt->Aux1 & FRAG_LAST)
                 break;
        }

         pPkt = pPkt->pNext;
    }

    /* Check if we can reassemble yet! */
    if (pPkt)
    {
        /* Start reassembling packet. */

        /* Add in the original IP header size + extension headers
         * size in the unfragmentable part to the total length
         * of the packet. This we take only from Fragment 0 
         * which is at head of the fragment queue.
         */
        AccLen += (ptr_fragQ->Fragments->Aux1 & FRAG_OFFSET);

        /* Create the Packet for reassembly */
        if ((pPkt = NIMUCreatePacket (AccLen)) == NULL)
        {
            /* Oops!! There was an error during allocating space
            * for reassembled packet?
            */
            NotifyLowResource();
            return -1;
        }

        /* Initialize the packet details */
        pPkt->ValidLen = AccLen;

        /* Get the pointer to Packet's data buffer */
        pBuff = (UINT8 *)(pPkt->pDataBuffer + pPkt->DataOffset);

        /* Get the fragment 0's details and use it in initializing
         * the reassembled packet. 
         */
        pPktTmp = ptr_fragQ->Fragments;

        /* Copy the Receive Interface from fragment 0 */
        pPkt->hIFRx = pPktTmp->hIFRx;

        /* Lets start over and actually thread together all the
         * fragment data and copy into the reassembled packet.
         */
        /* AccLen = Running length (not including IP header) */
        /* Offset = Running offset (length) (including IP header) */
        AccLen   = 0;
        Offset = 0;

        /* Iterate through all fragments in the queue */
        while (pPktTmp)
        {
            /* If this is the FIRST fragment, then use the largest initial size */
            if (pPktTmp->Aux1 & FRAG_FIRST)
            {
                if (pPktTmp->Aux2 > AccLen)
                {
                    /* From Fragment 0, copy over the IPv6 and extension headers,
                     * i.e. unfragmentable part into the final packet.
                     */
                    Offset = pPktTmp->Aux1 & FRAG_OFFSET;
                    mmCopy ((void *) pBuff, (void *) pPktTmp->pIpHdr , (uint)Offset);

                    /* Copy over to the Next header of the last extension header
                     * of unfrgamentable part, the next header value from fragment header.
                     * Fragment header is going to be stripped off now from the final packet.
                     * Remember, in IPv6FragQEnqueueFrag we saved from Fragment 0, the
                     * Offset of the "Next Header" field of the last extension header before
                     * Fragment header and the Next Header value from the fragment header itself
                     * into the FragQ. We use them now.
                     */
                    mmCopy ((void *) (pBuff + ptr_fragQ->NextHdrOffset), (void *) &ptr_fragQ->NextHdrValue, sizeof(UINT8));

                    /* Copy over the rest of data */
                    mmCopy ((void *) (pBuff + Offset), (void *) (pPktTmp->pDataBuffer + pPktTmp->DataOffset), (UINT32)(pPktTmp->Aux2));

                    AccLen = (UINT32)pPktTmp->Aux2;
                    Offset += (UINT32) pPktTmp->Aux2;
#ifdef IPV6_REASM_DEBUG
                    DbgPrintf(DBG_INFO, "IPv6FragReasm: frag0 len: %d \n", Offset);
#endif
                }
            }
            else
            {
                /* Check for data overlap! */
                FragLen = AccLen - (pPktTmp->Aux1 & FRAG_OFFSET);     
                if (pPktTmp->Aux2 > FragLen)
                {
                    /* Combine the overlapping fragments, and copy over data */
                    pPktTmp->Aux2 -= FragLen;
                    mmCopy ((void *) (pBuff + Offset), (void *) (pPktTmp->pDataBuffer + pPktTmp->DataOffset + FragLen),
                           (uint) (pPktTmp->Aux2));

                    /* Increment length and offset accordingly. */
                    AccLen += pPktTmp->Aux2;
                    Offset += pPktTmp->Aux2;
#ifdef IPV6_REASM_DEBUG
                    DbgPrintf(DBG_INFO, "IPv6FragReasm: fragn len: %d \n", Offset);
#endif
                }

                /* Yoohoo!! We are done. This is the last fragment */
                if (pPktTmp->Aux1 & FRAG_LAST)
                    break;
            }

            pPktTmp = pPktTmp->pNext;
        }

        /* Offset has the total length of accumulated fragments, 
         * including IPv6 Header size. We should not include
         * The IPv6 header size in Payload length, so remove it.
         */
        Offset -= IPv6HDR_SIZE;

        /* Free the FragQ, we are done putting together reassembled packet. */
        IPv6FragQFree (ptr_fragQ, 0);

        /* Initialize rest of IPv6 header fields and send the packet up the stack. */
        ptr_ipv6hdr = (IPV6HDR *)pBuff;
        ptr_ipv6hdr->PayloadLength = htons(Offset);

        /* Increment Reasm stats */
        ipv6mcb.ip6stats.InReasmOKs++;

        IPv6RxPacket (pPkt);
    }

    /* If we are here, reassembly was a success and we sent the packet up
     * return SUCCESS
     */
    return 0;
}

#ifdef IPV6_REASM_DEBUG
/** 
 *  @b Description
 *  @n  
 *      Debug function to dump contents of fragmentation queue.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_fragQ
 *      Fragment queue whose contents need to be printed.
 *
 *  @retval
 *      None.
 */
static void IPv6DumpFragQ(FRAG6Q* ptr_fragQ)
{
    PBM_Pkt* pPkt = NULL;

    /* Validate input */
    if (!ptr_fragQ)
        return;

    DbgPrintf(DBG_INFO, "IPv6DumpFragQ: ***** DUMP *** FragID: %u \n",
            ptr_fragQ->Id);

    /* Get first fragment */
    pPkt = ptr_fragQ->Fragments;

    while (pPkt)
    {
        DbgPrintf(DBG_INFO, "IPv6DumpFragQ: offset: %d len: %d \n",
                pPkt->Aux1 & FRAG_OFFSET, pPkt->Aux2);

        /* Lets move to the next fragment in this queue. */
        pPkt = pPkt->pNext;
    }

    return;
}
#endif

/** 
 *  @b Description
 *  @n  
 *      The function handles all packets with fragmentation
 *      header.
 *
 *  @param[in]  pPkt
 *      Pointer to the entire IPv6 Packet.
 *
 *  @param[in]  ptr_ipv6hdr
 *      Pointer to the IPv6 Header.
 *
 *  @retval
 *      -1  -   Error in processing the packet. Packet has been 
 *              cleaned up.
 *  @retval
 *      1   -   Packet has been successfully processed by fragmentation
 *              module. Its been absorbed by this module for reassembly.
 *              Ignore this packet. This packet is now a responsibility of
 *              the fragmentation layer for further processing.
 */
int IPv6ParseFragHdr (PBM_Pkt* pPkt, IPV6HDR* ptr_ipv6hdr)
{
    IPV6_FRAGHDR*    ptr_fraghdr = NULL;
    FRAG6Q*        fragQ        = NULL;
    int            RetVal        = -1;
    UINT32        FragId        = 0;
    IP6N        srcAddr;
    IP6N        dstAddr;

    /*
     * NOTE: use mmCopy to copy the 16 byte IP6N addresses out of ptr_ipv6hdr
     * as this data is potentially un-aligned (SDOCM00097361)
     */
    mmCopy((char *)&srcAddr, (char *)&ptr_ipv6hdr->SrcAddr, sizeof(IP6N));
    mmCopy((char *)&dstAddr, (char *)&ptr_ipv6hdr->DstAddr, sizeof(IP6N));

    /* Get the pointer to the Fragmentation Header. */
    ptr_fraghdr = (IPV6_FRAGHDR *) (pPkt->pDataBuffer + pPkt->DataOffset);

    /* Check if it is a fragmented frame indeed 
     * i.e if both offset = 0 and MF = 0, skip
     * the fragment header. it just means that
     * the this is the only fragment. we dont
     * need to do any reassembly, so we skip the
     * fragment header and proceed as usual.
     */
    if(!(ptr_fraghdr->FragOffset & htons(0xFFF9))) 
    {
        /* Increment the offset to jump over Fragment header */
        pPkt->DataOffset += IPV6_FRAGHDR_SIZE;
        pPkt->ValidLen   -= IPV6_FRAGHDR_SIZE;

        return ptr_fraghdr->NextHeader;
    }

    FragId = RdNet32(&ptr_fraghdr->FragId);
#ifdef IPV6_REASM_DEBUG
    DbgPrintf(DBG_INFO, "IPv6ParseFragHdr: FragId: %d \n", ntohl(FragId & 0xFFFFFFFF));
#endif

    /* Find the fragment's Queue and buffer it. */
    if ((fragQ = IPv6FindFragQ (ntohl(FragId & 0xFFFFFFFF), srcAddr, dstAddr)))
    {
        /* Enqueue the fragment */
        RetVal = IPv6FragQEnqueueFrag (fragQ, pPkt, ptr_fraghdr, ptr_ipv6hdr);

        /* Check if there was an error buffering the fragment.
         * If so, increment error stats and free the fragment
         * queue.
         */
        if (RetVal != 0)
        {
            /* Increment error stats */
            ipv6mcb.ip6stats.InExtnHdrErrors++;

            /* Clean up the frag queue and all enqueued packets. */
            IPv6FragQFree (fragQ, 1);
            PBM_free(pPkt);

            /* Return error */
            return -1;
        }
        
        /* Increment IPv6 Reasm stats */
        ipv6mcb.ip6stats.InReasmReqds++;

        /* Debug. Dump contents of queue */
#ifdef IPV6_REASM_DEBUG
        IPv6DumpFragQ(fragQ);
        DbgPrintf(DBG_INFO, "IPv6ParseFragHdr: in parsefrag do2: %d \n",  pPkt->DataOffset);
 #endif

        /* Check if we are ready for reassembling the packet yet ? */
        RetVal = IPv6FragReasm (fragQ);

        /* Error. Do the needful. */
        if (RetVal == -1)
        {
            /* Increment error stats */
            ipv6mcb.ip6stats.InReasmFails++;
            
            /* There was an error allocating final reassembled packet
             * This is a fatal error, so we free up the whole fragment 
             * buffer and quit reassembling this packet.
             */
            IPv6FragQFree(fragQ, 1);

            /* Return error */
            return -1;
        }
     }
    else
    {
        /* Error in allocating fragmentation queue. Free the packet. */
        PBM_free(pPkt);

        /* Increment IPv6 error stats */
        ipv6mcb.ip6stats.InReasmFails++;

        return -1;
    }

    /* Success, we take care of freeing the packet buffers too.
     * Since no further processing required by calling function, return 1.
     */
    return 1;
}


/**********************************************************************
 ************ IPV6 Fragmentation on Tx Path Handling Function *********
 **********************************************************************/

/** 
 *  @b Description
 *  @n  
 *      This function is called by IPv6TxPacket when it detects
 *      that the packet cannot be transmitted as a whole using 
 *      a specified tx device. This function handles the fragmentation
 *      and transmit of such a packet.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  pPkt     
 *      Pointer to the IPv6 packet which needs to be transmitted
 *
 *  @param[in]  ptr_net_device
 *      Pointer to the device on which the fragment packets need to
 *      be transmitted
 *
 *  @param[in]  ptr_lli6
 *      Handle to the LLI6 Entry
 *
 *  @retval
 *      Success -   0
 *
 *  @retval
 *      Error   -   <0
 */
int IPv6TxFragPacket  (PBM_Pkt *pPkt, NETIF_DEVICE* ptr_net_device, HANDLE ptr_lli6)
{
    IPV6HDR*        ptr_ipv6hdr = NULL;
    UINT16          PktSize, Unfraglen, FragLen, FragOffset, Size;
    int             NxtHdrVal = -1;
    IPV6_FRAGHDR*        ptr_fraghdr = NULL;
    IPV6_HOPOPTSHDR*     ptr_hopoptshdr = NULL;
    IPV6_DSTOPTSHDR*     ptr_dstoptshdr = NULL;
    IPV6HDR*        ptr_ipv6hdr2 = NULL;
    PBM_Pkt*        pPkt2 = NULL;
    UINT16          OrigPloadOffset = 0, PrevHdrOffset, offtmp = 0;
    UINT32            Id = 0;
    UINT32          IfMtu;

    /* Get the pointer to the IPv6 Header. */
    ptr_ipv6hdr = (IPV6HDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    IfMtu       = ptr_net_device->mtu;
    PktSize     = pPkt->ValidLen;
    if(1)
    {
        /* Step 1: Scan the headers to classify if any
         * extension headers present in the packet need
         * to go into unfragmentable part. The rest of 
         * headers can all be fragmented with payload.
         * RFC 2460 - Section 4.5:
         * ----------------------
         * The unfragmentable part consists of the IPv6
         * header plus any extension headers that must be
         * processed by nodes en-route to the destination,
         * that is all the headers up to and including the 
         * Routing header if present, else the Hop-by-Hop
         * options header if present, else no extension
         * headers.
         * The fragmentable part consists of the rest of
         * the packet, that is any extension headers that
         * need to be processed only by the final destination
         * node(s), plus the upper-layer header and data.
         */
        NxtHdrVal= ptr_ipv6hdr->NextHeader;        

        /* This variable holds the offset (from the start of IPv6
         * header) to "Next Header" field of the last processed
         * extension header.
         */
        PrevHdrOffset = pPkt->DataOffset + 6;

        /* This variable holds the length of Unfragmentable part 
         * of the packet.
         */
        Unfraglen = 0;

        /* This variable holds the Offset to the start of fragmentable
         * part of the packet. This is initialized to the end
         * of IPv6 header and will be moved as we process the
         * extension headers till we reach end of unfragmentable
         * part of the packet, i.e. routing header / 
         * hop by hop header if any.
         */
        OrigPloadOffset  = pPkt->DataOffset + IPv6HDR_SIZE;

        /* Iterate through the extension headers to find the end
         * of unfragmentable part of the packet.
         */
scan_nxthdr:        
        switch(NxtHdrVal)     
        {
            /* Unfragmentable part */
            case IPV6_HOPOPTS_HEADER:
            {
                ptr_hopoptshdr = (IPV6_HOPOPTSHDR *) (pPkt->pDataBuffer + OrigPloadOffset);

                /* Hop-by-Hop is part of Unfragmentable part of packet. Increment 
                 * Unfraglen accordingly to skip over this header.
                 */
                Unfraglen += IPV6_HOPOPTSHDR_SIZE + (ptr_hopoptshdr->HdrExtLen << 3);

                NxtHdrVal = ptr_hopoptshdr->NextHeader;
                break;
            }
            case IPV6_ROUTING_HEADER:
            {
                /* Routing header is part of Unfragmentable part of packet. 
                 * Not yet supported.
                 */
                break;
            }
            case IPV6_DSTOPTS_HEADER:
            {
                ptr_dstoptshdr = (IPV6_DSTOPTSHDR *) (pPkt->pDataBuffer + OrigPloadOffset);

                /* Destination optns is part of Unfragmentable part of packet. 
                 * Increment Unfraglen accordingly to skip over this header.
                 */
                Unfraglen += IPV6_DSTOPTSHDR_SIZE + (ptr_dstoptshdr->HdrExtLen << 3);

                NxtHdrVal = ptr_dstoptshdr->NextHeader;
                break;
            }
            default:
            {   
                /* Found some other header? Indicates end of unfragmentable
                 * part of the packet. We can start fragmenting the packets now.
                 */
                goto build_fragment;
            }
        }

        /* Store the current "Next Header" offset */
        PrevHdrOffset = OrigPloadOffset;

        /* Move the "Next Header" offset to the next one */
        OrigPloadOffset += Unfraglen;

        /* Continue scanning extension headers until we find 
         * the end of unfragmentable part of this packet.
         */
        if(NxtHdrVal >= 0)
            goto scan_nxthdr;

        /* Start building fragments and sending them out. */
build_fragment:      
        /* We want the "Next Header" offset of the last processed
         * extension header, with reference to start of IPv6 Header.
         * So, lets subtract the data offset of start of ipv6 header
         * to obtain the relative offset.
         * For Eg:
         * IPv6 Header offset = 22 bytes
         * HopbyHopHdr offset = 22 + 40 = 62 bytes
         * So, the "Next header" offset of last processed extension 
         * header relative to start of IPv6 header would be 
         * 62 - 22 = 40 bytes from start of IPv6 header. 
         */
        PrevHdrOffset -= pPkt->DataOffset;

        /* Do the above mentioned same math for obtaining the 
         * payload data offset relative to IPV6 header start.
         */
        OrigPloadOffset -= pPkt->DataOffset;

        /* The Unfragmentable part of packet includes the IPv6 
         * header too. So, add its length in too.
         */
        Unfraglen += IPv6HDR_SIZE;

        /* Get the payload size from IPv6 header. 
         * Payload size = size of extension headers + Payload data
         */
        PktSize = ntohs(ptr_ipv6hdr->PayloadLength);

        /* RFC 2460 - Section 4.5
         * The Fragmentable part of the original packet is
         * divided into fragments, each, except possibly the
         * last one, being an integer multiple of 8 octets 
         * long.
         */
        /* Fragment length must be a multiple of 8 octets.
         * Calculate the octet rounded amount of data we can
         * transmit in the first fragment.
         */
        FragLen    = (IfMtu - Unfraglen - IPV6_FRAGHDR_SIZE) & ~0x7;

        if(FragLen)
        {
            /* Loop until we transmit the whole packet */
            for(FragOffset = 0; FragOffset < (UINT16)PktSize; FragOffset += FragLen)
            {
                /* Get the payload size for this fragment */
                Size = FragLen;

                /* Check, if we have the same amount of fragment
                 * data to transmit as the last time?
                 * If not, calculate the remaining of data we need
                 * to send.
                 */
                if( (FragOffset + Size) > PktSize )
                    Size = (UINT16)PktSize - FragOffset;

                /* Fragment packet we are going to create now */
                pPkt2 = NULL;

                /* Create the packet.
                 * Size - length of Fragmentable Part of packet
                 * So, add in IPv6 Header size and Fragment header size
                 * we are going to add these headers to each frag we send.
                 */
                if( !(pPkt2 = NIMUCreatePacket( Size + IPv6HDR_SIZE + IPV6_FRAGHDR_SIZE)) )
                {
                    NotifyLowResource();
                    goto Err;                
                }

                /* Get the IP header pointer */
                ptr_ipv6hdr2 = (IPV6HDR *)(pPkt2->pDataBuffer + pPkt2->DataOffset);

                /* Fixup packet fragment information */
                pPkt2->ValidLen = Size + IPv6HDR_SIZE + IPV6_FRAGHDR_SIZE;

                /* Copy the IP header and data.
                 * We assume the extension headers if any, are in the order
                 * as specified in RFC 2460:
                 * IPv6 hdr --> HopbyHop --> DestnOptions --> Routing 
                 */
                /* Common to all fragments */
                if (1)
                {
                    /* Copy the IPv6 Header from original packet */
                    mmCopy ((void *) ptr_ipv6hdr2, (void *)ptr_ipv6hdr, Unfraglen);
                  
                    /* RFC 2460 - Section 4.5 
                     * Each fragment packet is composed of:
                     * (1) The unfragmentable part of original packet, with the
                     * payload length of the original IPv6 header changed to contain
                     * the length of this fragment packet only (excluding length of
                     * IPv6 header), and the Next header field of the last header of
                     * the Unfragmentable part changed to 44.
                     */
                    /* Set the "Next Header" field of the last header of the 
                     * unfragmentable part of packet to fragment header, since 
                     * we'll be adding fragment header between the unfragmentable
                     * and fragmentable parts of the packet.
                     */
                    *((UINT8 *)ptr_ipv6hdr2 + PrevHdrOffset) = IPV6_FRAGMENT_HEADER;

                    /* Add the fragment header */
                    ptr_fraghdr = (IPV6_FRAGHDR *)(((UINT8 *)ptr_ipv6hdr2) + Unfraglen);

                    /* RFC 2460 - Section 4.5 
                     * Each fragment packet is composed of:
                     * (2) A fragment header containing:
                     *      The Next Header value that identifies the first header
                     *      of the fragmentable part of original packet.
                     *
                     *      A fragment offset containing the offset of the fragment,
                     *      in 8-octet units, relative to the start of fragmentable
                     *      part of the original packet. The fragment offset of the 
                     *      first fragment is 0.
                     *
                     *      An M flag value of 0 if the fragment is the last, else
                     *      an M flag value of 1.
                     *
                     *      The identification value generated for original packet.
                     *
                     * (3)  The fragment itself.
                     */
                    ptr_fraghdr->NextHeader = NxtHdrVal;

                    offtmp = FragOffset;
                
                    /* Set the M bit if this is not the last packet. */
                    if( (FragOffset + Size) < ((UINT16)PktSize) )
                        offtmp |= IPV6_MF_BIT;
        
                    ptr_fraghdr->FragOffset = htons(offtmp);

                }

                /* If this is the first fragment we send */
                if (!FragOffset)
                {
                    /* Since this is fragment 0, generate a new FragId and set it */
                    Id = htonl(gFragIdCtr);
                    gFragIdCtr++;

                    WrNet32(&ptr_fraghdr->FragId, Id);

                    /* Now copy the fragmentable part */
                    mmCopy( (void *)(((UINT8 *)ptr_ipv6hdr2) + Unfraglen + IPV6_FRAGHDR_SIZE),
                            (void *)(((UINT8 *)ptr_ipv6hdr) + OrigPloadOffset), 
                            Size);
                }
                /* Not fragment 0 */
                else
                {
                    /* Set the frag Id generated previously for fragment 0 */
                    WrNet32(&ptr_fraghdr->FragId, Id);

                    /* Now copy the fragmentable part */
                    mmCopy( (void *)(((UINT8 *)ptr_ipv6hdr2) + Unfraglen + IPV6_FRAGHDR_SIZE),
                            (void *)(((UINT8 *)ptr_ipv6hdr) + OrigPloadOffset + FragOffset), 
                            Size);
                }

                /* Set the payload length */
                ptr_ipv6hdr2->PayloadLength = htons(Size + IPV6_FRAGHDR_SIZE);
                
                /* Set Destination Info */
                pPkt2->hIFTx = ptr_net_device;

                /* Send the packet */
                /* Get the network interface object on which the packet will be transmitted. 
                 * Check if we need to support the ARP protocol or not? If not then we can 
                 * bypass the ARP resolution. */
                {
                    if (ptr_net_device->flags & NIMU_DEVICE_NO_ARP)
                    {
                        /* Send the packet on the interface and return */
                        NIMUSendPacket (ptr_net_device, pPkt2);
                    }
                    else
                    {
                        /* Pass the packet for the resolution. */
                        LLI6TxIPPacket (pPkt2, ptr_lli6, ptr_net_device, ptr_ipv6hdr2->DstAddr);
                    }
                }

                /* Increment IPv6 Tx Frag stats */
                ipv6mcb.ip6stats.OutFragCreates++;
            }

            /* Return Success */
            return 0;
        }
    }
Err:
    /* Return error */
    return (IPTX_ERROR_MSGSIZE);
}

#endif
