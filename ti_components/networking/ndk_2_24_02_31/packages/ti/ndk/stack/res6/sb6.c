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
 * ======== sb6.c ========
 *
 * The file implements the Socket Buffer for IPv6.
 *
 */


#include <stkmain.h>

#ifdef _INCLUDE_IPv6_CODE

/**********************************************************************
 ****************************** SB6 Functions *************************
 **********************************************************************/

/** 
 *  @b Description
 *  @n  
 *      The function is called to create a new socket buffer for the IPv6
 *      socket layer.
 *
 *  @param[in]  Max
 *      Sets the Maximum Buffer size.
 *  @param[in]  Min
 *      Sets the Minimum Buffer size
 *  @param[in]  Mode
 *      This defines the mode in which the Socket Buffer will operate.
 *      Valid values for these are as follows:-
 *       - SB_MODE_LINEAR
 *          In this mode there is a single buffer and data is copied into
 *          it. This is used for TCP sockets.
 *       - SB_MODE_ATOMIC
 *          In this mode the received packets are enqueued into a linked list
 *          This is used for UDP sockets.
 *
 *  @retval
 *      Success -   0
 *  @retval      
 *      Error   -   Non Zero
 */
HANDLE SB6New( INT32 Max, INT32 Min, uint Mode )
{
    SB* pSB;

    /* Basic Validations: Mode should be VALID. */
    if( Mode!=SB_MODE_LINEAR && Mode!=SB_MODE_ATOMIC)
        return 0;

    /* Basic Validations: Min and MAX should be VALID. */
    if ((Min == 0) || (Max == 0))
        return 0;

    /* Allocate memory for the Sokcet Buffer object. */
    pSB = mmAlloc(sizeof(SB));
    if(pSB == NULL)
    {
        /* Error: We are running out of memory. */
        NotifyLowResource();
        return(0);
    }

    /* Initialize the allocated block of memory. */ 
    mmZeroInit (pSB, sizeof(SB));

    /* Allocate external buffer if LINEAR */
    if(Mode == SB_MODE_LINEAR)
    {
        pSB->pData = mmBulkAlloc(Max);
        if(pSB->pData == NULL)
        {
            DbgPrintf(DBG_WARN,"SB6New: Buffer OOM");
            mmFree(pSB);
            return(0);
        }
    }

    /* Initialize the Socket Buffer Object. */ 
    pSB->Type = HTYPE_SB;
    pSB->Mode = Mode;
    pSB->Max  = Max;
    pSB->Min  = Min;

    /* Return the allocated Socket Buffer HANDLE. */
    return( (HANDLE)pSB );
}

/** 
 *  @b Description
 *  @n  
 *      The function is called to cleanup the socket buffer object for V6.
 *
 *  @param[in]  h
 *      Handle to the socket buffer object which is to be cleaned up.
 *
 *  @retval
 *      Not Applicable.
 */
void SB6Free( HANDLE h )
{
    SB*         pSB  = (SB *)h;
    PBM_Pkt*    pPkt;

    /* Cleanup the memory in the socket buffer; this is dependent on the mode of operation. */
    if( pSB->Mode == SB_MODE_LINEAR )
    {
        /* LINEAR Mode: We need to cleanup the allocated block of memory. */
        if( pSB->pData )
            mmBulkFree( pSB->pData );
    }
    else
    {
        /* ATOMIC Mode: We need to dequeue and cleanup any packets which are in the queue. */
        while( (pPkt = pSB->pPktFirst) )
        {
            pSB->pPktFirst = pPkt->pNext;
            PBM_free( pPkt );
        }
    }

    /* Cleanup the allocated block of memory for the Socket Buffer. */ 
    mmFree (pSB);
    return;
}

/** 
 *  @b Description
 *  @n  
 *      The function is called to flush out all data in the socket
 *      buffers. The function is similar to SB6Free except it does
 *      not clean out the SOCKET Buffer object itself.
 *
 *  @param[in]  h
 *      Handle to the socket buffer object 
 *  @param[in]  fFree
 *      Flag which indicates how to handle internal SB memory. When
 *      set to 1 the function will clean up the internal memory and
 *      when passed as 0; the internal memory block will be retained
 *
 *  @retval
 *      Not Applicable.
 */
void SB6Flush( HANDLE h, uint fFree )
{
    SB      *pSB  = (SB *)h;
    PBM_Pkt *pPkt;

    /* Flush the counter. */
    pSB->Total = 0;

    /* Check the Mode in which we are operating. */
    if( pSB->Mode == SB_MODE_LINEAR )
    {
        /* LINEAR Mode: Reset the Head and Tail pointers */
        pSB->Head = pSB->Tail = 0;

        /* Check if we were asked to clean internal memory. */
        if( fFree && pSB->pData )
        {
            /* YES. Clean it out. */
            mmBulkFree( pSB->pData );
            pSB->pData = 0;
        }
    }
    else
    {
        /* ATOMIC Mode: Cycle through all packets which reside in the queue
         * and clean them out. */
        while( (pPkt = pSB->pPktFirst) )
        {
            pSB->pPktFirst = pPkt->pNext;
            PBM_free( pPkt );
        }
    }
}

/** 
 *  @b Description
 *  @n  
 *      The function is called to read data from the Socket Buffer
 *      object.
 *
 *  @param[in]  h
 *      Handle to the socket buffer object 
 *  @param[in]  Size
 *      Size of the Buffer in which data has to be copied. 
 *  @param[in]  Off
 *      Offset
 *  @param[in]  pbDst
 *      Pointer to the destination where the data has to be copied to.
 *  @param[in]  pPeer
 *      Pointer to the peer information record; where information about
 *      the peer is recorded.
 *  @param[in]  flagPeek
 *      Flag which indicates if the function was just called to PEEK or
 *      READ. In PEEK i.e. flagPeek = 0 the pointers in the SOCKET buffer
 *      object are not updated.
 *
 *  @retval
 *      Error   -   0
 *  @retval
 *      Success -   Number of bytes read and copied into the supplied buffer.
 */
INT32 SB6Read
(
    HANDLE  h,
    INT32   Size,
    INT32   Off,
    UINT8*  pbDst,
    PSA_IN6 pPeer,
    UINT8   flagPeek
)
{
    SB* pSB  = (SB *)h;

    /* Check the mode in which the socket buffer is operating. */
    if( pSB->Mode == SB_MODE_LINEAR )
    {
        /* LINEAR MODE: */
        INT32 Len;

        /* Adjust size if too large */
        if( (Size+Off) > pSB->Total )
            Size = pSB->Total - Off;

        if( Size <= 0 )
            return( Size );

        /* Copy data when pointer supplied */
        if( pbDst )
        {
            /* First Copy */
            Len = pSB->Max - (pSB->Tail+Off);
            if( Len >= 0 )
            {
                if( Len > Size )
                    Len = Size;
                if( Len )
                    mmCopy( pbDst, pSB->pData + pSB->Tail + Off, (uint)Len );

                /* Copy the potential second block */
                if( Size > Len )
                {
                    /* Len is the number of bytes already copied */
                    mmCopy( pbDst+Len, pSB->pData, (uint)(Size-Len) );
                }
            }
            else
            {
                /* Here Len is the additional offset from the start */
                Len = 0-Len;
                mmCopy( pbDst, pSB->pData+Len, (uint)Size );
            }
        }

        /* Advance the tail pointer and adjust Total if not "peeking" */
        if( !flagPeek )
        {
            pSB->Tail = (pSB->Tail+(Size+Off))%pSB->Max;
            pSB->Total -= (Size+Off);
        }

        return( Size );
    }
    else
    {
        /* ATOMIC Mode: */
        PBM_Pkt  *pPkt;
        INT32    BytesCopied,ToCopy;

        /* Get the first pending packet. */
        pPkt = pSB->pPktFirst;

        /* There should always exist at least element in the queue. */
        if( !pPkt )
        {
            DbgPrintf(DBG_ERROR,"SBRead: Internal ATOMIC error");
            return(0);
        }

        /* Populate the Peer Information; if provided. */
        if (pPeer != NULL)
        {
            pPeer->sin6_port     = (uint)pPkt->SrcPort;
            mmCopy ((void *)&pPeer->sin6_addr, (void *)&pPkt->SrcAddress, sizeof(struct in6_addr));
            pPeer->sin6_scope_id = ((NETIF_DEVICE *)(pPkt->hIFRx))->index;
        }

        /* Initialize the number of bytes that we have copied. */
        BytesCopied = 0;

        /* Get the number of valid PAYLOAD bytes in this packet. */
        ToCopy = (INT32)pPkt->ValidLen;

        /* Check if we can copy this or not? The buffer allocated by the application might not
         * be large enough? */ 
        if( (BytesCopied + ToCopy) > Size )
            ToCopy = Size - BytesCopied;

        /* Copy the data. */
        if( ToCopy )
            mmCopy( pbDst + BytesCopied, pPkt->pDataBuffer + pPkt->DataOffset, (uint)ToCopy );

        /* Increment the number of bytes that have been copied. */
        BytesCopied += ToCopy;

        /* Increment the pointers if we are NOT peeking. */ 
        if( !flagPeek )
        {
            /* Lie for NULL byte packets */
            if( !pPkt->ValidLen )
                pSB->Total--;
            else
                pSB->Total -= (INT32)pPkt->ValidLen;
            pSB->pPktFirst = pPkt->pNext;
            PBM_free( pPkt );
        }
        return( BytesCopied );
    }
}

/** 
 *  @b Description
 *  @n  
 *      The function is called to write data to the Socket Buffer
 *      object.
 *
 *  @param[in]  h
 *      Handle to the socket buffer object 
 *  @param[in]  Size
 *      Size of the Buffer from where data has to be copied.
 *  @param[in]  pData
 *      Pointer to where the data payload starts.
 *  @param[in]  pPkt
 *      Pointer to received packet whose data payload is added to the
 *      socket buffer.
 *
 *  @retval
 *      Error   -   0
 *  @retval      
 *      Success -   Number of bytes copied into the socket buffer.
 */
INT32 SB6Write (HANDLE h, INT32 Size, void *pData, PBM_Pkt *pPkt)
{
    SB      *pSB = (SB *)h;

    /* Determine the Mode. */
    if( pSB->Mode == SB_MODE_LINEAR )
    {
        /* LINEAR Mode: */
        INT32 Len;

        /* Adjust size if too large */
        Len = pSB->Max - pSB->Total;
        if( Size > Len )
            Size = Len;

        /* Copy data */
        if( !pSB->pData )
            Size = 0;
        else if( Size )
        {
            /* First Copy */
            Len = pSB->Max - pSB->Head;
            if( Len > Size )
                Len = Size;
            if( Len )
                mmCopy( pSB->pData + pSB->Head, (UINT8 *)pData, (uint)Len );

            /* Potential Second Copy */
            if( Size > Len )
                mmCopy( pSB->pData, ((UINT8 *)pData)+Len, (uint)(Size-Len) );

            /* Advance head pointer and ajdust Total */
            pSB->Head = (pSB->Head+Size)%pSB->Max;
            pSB->Total += Size;
        }

        /* Free packet if provided */
        if( pPkt )
            PBM_free( pPkt );
    }
    else
    {
        /* ATOMIC Mode: We need to have a received packet. */
        if(!pPkt)
        {
            DbgPrintf(DBG_ERROR,"SBWrite: No Pkt");
            return( 0 );
        }

        /* In ATOMIC Mode; we can use the DataOffset and ValidLen fields
         * inside the packet structure to determine the exact location and
         * size of the data payload. 
         * If these parameters are specified; then they override 
         * default behavior. Since the fields in the packet might not be
         * completly correct. */
        if(pData)
            pPkt->DataOffset = (uint)((UINT8 *)pData - pPkt->pDataBuffer);
        if(Size)
            pPkt->ValidLen = Size;

        /* Add the Packet to the list of packets and enqueue this in the socket buffer.
         * Packets are always enqueued at the end of the list to maintain order.  */ 
        if(pSB->pPktFirst == NULL)
        {
            pPkt->pPrev     = 0;
            pSB->pPktFirst  = pPkt;
        }
        else
        {
            pPkt->pPrev          = pSB->pPktLast;
            pSB->pPktLast->pNext = pPkt;
        }
        pPkt->pNext     = 0;
        pSB->pPktLast   = pPkt;

        /* Adjust the Total Count of data which is available in the SOCKET Buffer. 
         * ZERO Payload packets are added as a 1 BYTE packet. */
        if( !pPkt->ValidLen && (pSB->Mode == SB_MODE_ATOMIC) )
            pSB->Total++;
        else
            pSB->Total += pPkt->ValidLen;
    }

    /* Return the size of data copied into the socket buffer. */
    return( Size );
}

/** 
 *  @b Description
 *  @n  
 *      The function sets the max bytes held in the socket buffer.
 *
 *  @param[in]  h
 *      Handle to the socket buffer object 
 *  @param[in]  Max
 *      New MAXIMUM Size
 *
 *  @retval
 *      Success - Returns the same value as 'Max'
 *  @retval
 *      Error   - Returns the original value i.e. '!Max'
 */
INT32 SB6SetMax( HANDLE h, INT32 Max )
{
    SB*     pSB  = (SB *)h;
    UINT8*  pData;

    /* Basic Validations: If the new SIZE is 0; we cannot proceed; so 
     * we return the current size. */
    if (Max == 0)
        return pSB->Max;

    /* Basic Validations: If there is DATA pending in the socket buffer; then
     * we cannot change this setting */
    if (pSB->Total)
        return pSB->Max;

    /* Further processing is dependent on the type of mode. */
    if(pSB->Mode != SB_MODE_LINEAR)
    {
        /* ATOMIC Mode: No change required here. */
        pSB->Max = Max;
    }
    else
    {
        /* LINEAR Mode: Allocate new memory block. */
        pData = mmBulkAlloc(Max);
        if (pData == NULL)
            return( pSB->Max );

        /* Reset the pointers. */
        pSB->Head = pSB->Tail = 0;

        /* Clenaup the old buffers. */
        if( pSB->pData )
            mmBulkFree( pSB->pData );

        /* Initialize the pointers to the new buffer. */
        pSB->pData = pData;
        pSB->Max = Max;
    }

    /* The buffer size has been modified. */
    return( pSB->Max );
}

#endif /* _INCLUDE_IPv6_CODE */

