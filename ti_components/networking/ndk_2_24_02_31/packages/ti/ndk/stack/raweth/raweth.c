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
 * ======== raweth.c ========
 *
 * The file implements the interface to send and receive Raw Ethernet 
 * traffic using NDK stack and NIMU architecture. 
 *
 */

#include <stkmain.h>

/* Raw ethernet stats */
RAWETHSTATS     raweths;   

/** 
 *  @b Description
 *  @n    
 *      The function is the interface routine which is called to send 
 *      a packet via a raw ethernet socket object.
 *
 *  @param[in]  hRawEthSock
 *      Handle to the Raw ethernet socket.
 *  @param[in]  pBuffer            
 *      Handle to the data buffer that needs to be sent
 *  @param[in]  len            
 *      length of the data
 *
 *  @retval
 *      0       - Successfully sent out the packet.
 *      ENOBUFS - Error allocating memory for the packet. Packet
 *                not sent out.
 */
int RawEthTxPacket (HANDLE hRawEthSock, char* pBuffer, int len)
{
    SOCKRAWETH*    	ps = (SOCKRAWETH *)hRawEthSock;
    PBM_Pkt*       	pPkt;

    /* The maximum packet size that can be transmitted is limited 
     * by either the MTU of the interface on which the packet will 
     * be transmitted or by the TxBufSize configured on this socket,
     * whichever is the smaller value of those.
     * There is no layer to do the fragmentation on the Raw Eth Tx path,
     * hence its important to limit the packet size by the MTU so as to 
     * avoid drops at the driver.
     */
    if( ((ps->TxBufSize) && (len > ps->TxBufSize)) || (len > IFGetMTU( ps->hIF )) )
    {
        /* The packet size too big to transmit using the specified
         * settings.
         */
        return EMSGSIZE;
    }

    /* Allocate a packet */
    if ((pPkt = NIMUCreatePacket(len)) == NULL)
    {
        /* Increment Error stats */
        raweths.SndNoPacket++;
        return (ENOBUFS);
    }

    /* Adjust the offset to add the Ethernet header 
     * The start of buffer sent as argument to this function
     * is assumed to be the start of the eth header.
     */
    pPkt->DataOffset -= ETHHDR_SIZE;

    /* No TxBuffer Free callback function registered. Copy over 
     * the buffer specified. This is the copy version of send
     */
    mmCopy((pPkt->pDataBuffer + pPkt->DataOffset), pBuffer, len);

    /* Configure the length and offsets to accomodate the buffers */
    pPkt->ValidLen    =  len;

    /* We will use the PktPriority field of the PBM_Pkt data structure
     * to store the priority if configured. This can be used by the
     * ethernet driver to provide some kind of differentiation/
     * prioritization.
     * Inherit the priority from the socket; this is assuming all packets 
     * flowing through a socket will have the same priority.
     */
    pPkt->PktPriority = ps->SockPriority;

    NIMUSendPacket ((HANDLE)ps->hIF, pPkt);

    /* Increment Success Stats */
    raweths.SndTotal++;

    return 0;
}

/** 
 *  @b Description
 *  @n    
 *      The function is the interface routine which is called to send 
 *      a packet without any copy via a raw ethernet socket object.
 *
 *  @param[in]  hRawEthSock
 *      Handle to the Raw ethernet socket.
 *  @param[in]  pBuffer            
 *      Handle to the data buffer that needs to be sent
 *  @param[in]  len            
 *      length of the data
 *  @param[in]  hPkt            
 *      Handle to the packet that needs to be sent
 *
 *  @retval
 *      0       - Successfully sent out the packet.
 *      EINVAL  - Bad Packet / Buffer handles, packet not sent out.
 */
int RawEthTxPacketNC (HANDLE hRawEthSock, char* pBuffer, int len, HANDLE hPkt)
{
    SOCKRAWETH*     ps      = (SOCKRAWETH *)hRawEthSock;
    PBM_Pkt*       	pPkt    = (PBM_Pkt *)hPkt;

    /* Validate the packet. The buffer passed is valid only if the
     * buffer handle in the packet is the same as the one present in the
     * packet passed.
     */
    if ((pPkt->pDataBuffer + pPkt->DataOffset) != (UINT8 *)pBuffer)
    {
        raweths.SndNoPacket++;
        return (EINVAL);
    }

    /* Configure the length and offsets to accomodate the buffers */
    pPkt->ValidLen    =  len;

    /* We will use the PktPriority field of the PBM_Pkt data structure
     * to store the priority if configured. This can be used by the
     * ethernet driver to provide some kind of differentiation/
     * prioritization.
     * Inherit the priority from the socket; this is assuming all packets 
     * flowing through a socket will have the same priority.
     */
    pPkt->PktPriority = ps->SockPriority;

    NIMUSendPacket ((HANDLE)ps->hIF, pPkt);

    /* Increment Success Stats */
    raweths.SndTotal++;

    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      This routine is the API interface routine which is called
 *      by the NIMU layer when the ethernet type doesnt match any
 *      of the well know standard ethernet types. This function
 *      checks if a raw ethernet socket object exists for the
 *      ethernet type in the packet and if so enqueus in the socket
 *      buffer for the application to receive.
 *
 *  @param[in]  hPkt      
 *      Handle to the packet which is to be passed up the NDK stack.
 *
 *  @retval
 *   -1     -   Error
 *  @retval
 *   0      -   Success
 */
int RawEthRxPacket (PBM_Handle hPkt)
{

    PBM_Pkt*        ptr_pkt = (PBM_Pkt *)hPkt;
    UINT32          Type, len;
    ETHHDR*         ptr_eth_header;
    SOCKRAWETH*     hRawEthSock;
	HANDLE			hSBRx;

    /* Increment Receive stats */
    raweths.RcvTotal++;

    /* NIMU layer would have already advanced the Data offset
     * of the packet buffer to exclude L2 since its already
     * inspected it. Lets move the offsets back to start of L2
     * so that we have the complete Ethernet packet as it is
     * to pass up to the application.
     */
    ptr_pkt->ValidLen   += ptr_pkt->L2HdrLen;
    ptr_pkt->DataOffset -= ptr_pkt->L2HdrLen;

    /* Get the pointer to the Ethernet Header. */
    ptr_eth_header = (ETHHDR *) (ptr_pkt->pDataBuffer + ptr_pkt->DataOffset);

    /* Use the type field to determine if we have a matching
     * raw ethernet channel open
     */
    Type = ntohs (ptr_eth_header->Type);

    hRawEthSock = RawEthSockPcbFind (Type, ptr_pkt->hIFRx);

    if (!hRawEthSock)
    {
        /* No matching Raw ethernet socket configured to
         * handle this packet. Increment error stats and
         * return error. NIMU layer will drop the packet.
         */
        raweths.RcvDrops++;
        return -1;
    }

    /* If we are here, we found a valid socket */
    len = ptr_pkt->ValidLen;

	/* Get the receiver buffer handle */
	hSBRx = RawEthSockGetRx(hRawEthSock);

    /* Enqueue the data to the Socket buffer. */
    if( len && (SBGetSpace(hSBRx) >= len) )
    {
        SBWrite( hRawEthSock->hSBRx, len, (ptr_pkt->pDataBuffer + ptr_pkt->DataOffset), ptr_pkt );

        /* Notify the socket of the pending received packet. */
        RawEthSockNotify( hRawEthSock, SOCK_NOTIFY_RCVDATA );
    }
    else
    {
        /* Increment Receive Error Stats */
        raweths.RcvDrops++;
        return -1;
    }

    return 0;
}

