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
 * ======== sb.c ========
 *
 * Socket Buffer
 *
 */

#include <stkmain.h>

/*-------------------------------------------------------------------- */
/* SBNew() */
/* Creates a Socket Buffer */
/*-------------------------------------------------------------------- */
HANDLE SBNew( INT32 Max, INT32 Min, uint Mode )
{
    SB *pSB;

#ifdef _STRONG_CHECKING
    /* Verify legal mode */
    if( Mode!=SB_MODE_LINEAR && Mode!=SB_MODE_ATOMIC && Mode!=SB_MODE_HYBRID )
    {
        DbgPrintf(DBG_WARN,"SBNew: Illegal Mode");
        return(0);
    }
#endif

    /* Allocate Object */
    if( !(pSB = mmAlloc(sizeof(SB))) )
    {
        NotifyLowResource();
        return(0);
    }

    /* Zero-init Object */
    mmZeroInit( pSB, sizeof(SB) );

    /* Allocate external buffer if LINEAR */
    if( Mode == SB_MODE_LINEAR && Max )
    {
        pSB->pData = mmBulkAlloc( Max );
        if( !pSB->pData )
        {
            DbgPrintf(DBG_WARN,"SBNew: Buffer OOM");
            mmFree( pSB );
            return(0);
        }
    }

    /* Initialize type */
    pSB->Type       = HTYPE_SB;
    pSB->Mode       = Mode;

    /* Initialize the object */
    pSB->Max        = Max;
    pSB->Min        = Min;

    return( (HANDLE)pSB );
}

/*-------------------------------------------------------------------- */
/* SBFree() */
/* Frees a SB */
/*-------------------------------------------------------------------- */
void SBFree( HANDLE h )
{
    SB      *pSB  = (SB *)h;
    PBM_Pkt *pPkt;

#ifdef _STRONG_CHECKING
    if( pSB->Type != HTYPE_SB )
    {
        DbgPrintf(DBG_ERROR,"SBFree: HTYPE %04x",pSB->Type);
        return;
    }
#endif

    /* Kill type for debug */
    pSB->Type = 0;

    if( pSB->Mode == SB_MODE_LINEAR )
    {
        /* Free the data buffer */
        if( pSB->pData )
            mmBulkFree( pSB->pData );
    }
    else
    {
        /* Free the Packets */
        while( (pPkt = pSB->pPktFirst) )
        {
            pSB->pPktFirst = pPkt->pNext;
            PBM_free( pPkt );
        }
    }

    /* Free the SB */
    mmFree( pSB );
}

/*-------------------------------------------------------------------- */
/* SBFlush() */
/* Flush all data in SB and free associated buffer when fFree set */
/*-------------------------------------------------------------------- */
void SBFlush( HANDLE h, uint fFree )
{
    SB      *pSB  = (SB *)h;
    PBM_Pkt *pPkt;

#ifdef _STRONG_CHECKING
    if( pSB->Type != HTYPE_SB )
    {
        DbgPrintf(DBG_ERROR,"SBFlush: HTYPE %04x",pSB->Type);
        return;
    }
#endif

    /* Zap the total */
    pSB->Total = 0;

    if( pSB->Mode == SB_MODE_LINEAR )
    {
        /* Reset the object */
        pSB->Head = pSB->Tail = 0;

        if( fFree && pSB->pData )
        {
            /* Free Data Buffer */
            mmBulkFree( pSB->pData );
            pSB->pData = 0;
        }
    }
    else
    {
        /* Free the Packets */
        while( (pPkt = pSB->pPktFirst) )
        {
            pSB->pPktFirst = pPkt->pNext;
            PBM_free( pPkt );
        }
    }
}

/*-------------------------------------------------------------------- */
/* SBRead() */
/* Read data from a SB */
/*-------------------------------------------------------------------- */
INT32 SBRead
(
    HANDLE  h,
    INT32   Size,
    INT32   Off,
    UINT8   *pbDst,
    IPN     *pIPFrom,
    uint    *pPortFrom,
    UINT8   flagPeek
)
{
    SB       *pSB  = (SB *)h;

#ifdef _STRONG_CHECKING
    if( pSB->Type != HTYPE_SB )
    {
        DbgPrintf(DBG_ERROR,"SBRead: HTYPE %04x",pSB->Type);
        return( 0 );
    }
#endif

    if( pSB->Mode == SB_MODE_LINEAR )
    {
        /* Linear Case */

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
        /* Atomic Case */
        PBM_Pkt  *pPkt;
        INT32    BytesCopied,ToCopy;

        /* Get the first frag */
        pPkt = pSB->pPktFirst;

        /* There must be a first frag */
        if( !pPkt )
        {
            DbgPrintf(DBG_ERROR,"SBRead: Internal ATOMIC error");
            return(0);
        }

        /* Copy in the "from" stuff */
        if( pIPFrom )
            *pIPFrom = pPkt->Aux2;
        if( pPortFrom )
            *pPortFrom = (uint)pPkt->Aux1;

        BytesCopied = 0;

        for(;;)
        {
            /* Get the most bytes we can copy this frag */
            ToCopy = (INT32)pPkt->ValidLen;

            /* If we don't want the entire frag, trim it down */
            if( (BytesCopied + ToCopy) > Size )
                ToCopy = Size - BytesCopied;

            /* Copy the data from the frag */
            if( ToCopy )
                mmCopy( pbDst + BytesCopied,
                        pPkt->pDataBuffer + pPkt->DataOffset, (uint)ToCopy );

            BytesCopied += ToCopy;

            /* Handle ATOMIC mode */
            if( pSB->Mode == SB_MODE_ATOMIC )
            {
                /* If not "peeking", then fix the frag list and the totals */
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
                break;
            }

            /* Here we are in HYBRID mode */

            /* If "peeking", just get next frag */
            if( flagPeek )
                pPkt = pPkt->pNext;
            else
            {
                /* Fix the frag list and the totals */
                pSB->Total -= ToCopy;

                if( ToCopy == (INT32)pPkt->ValidLen )
                {
                    /* We used the whole frag, remove it */
                    pSB->pPktFirst = pPkt->pNext;
                    PBM_free( pPkt );
                    pPkt = pSB->pPktFirst;
                }
                else
                {
                    /* Some data left - patch frag */
                    pPkt->DataOffset += (uint)ToCopy;
                    pPkt->ValidLen   -= (uint)ToCopy;
                    break;
                }
            }

            /* Stop if we've copied the full request or out of frags */
            if( BytesCopied == Size || !pPkt )
                break;
        }
        return( BytesCopied );
    }
}

/*-------------------------------------------------------------------- */
/* SBReadNC() */
/* Read data without copy from a SB */
/*-------------------------------------------------------------------- */
PBM_Pkt *SBReadNC( HANDLE h, IPN *pIPFrom, uint *pPortFrom )
{
    SB       *pSB  = (SB *)h;

#ifdef _STRONG_CHECKING
    if( pSB->Type != HTYPE_SB )
    {
        DbgPrintf(DBG_ERROR,"SBReadNC: HTYPE %04x",pSB->Type);
        return( 0 );
    }
#endif

    if( pSB->Mode == SB_MODE_LINEAR )
        return(0);
    else
    {
        /* Atomic Case */
        PBM_Pkt  *pPkt;

        /* Get the first frag */
        pPkt = pSB->pPktFirst;

        /* There must be a first frag */
        if( !pPkt )
        {
            DbgPrintf(DBG_ERROR,"SBReadNC: Internal ATOMIC error");
            return(0);
        }

        /* Copy in the "from" stuff */
        if( pIPFrom )
            *pIPFrom = pPkt->Aux2;
        if( pPortFrom )
            *pPortFrom = (uint)pPkt->Aux1;

        /* Remove the frag (lie about NULL byte packets) */
        if( !pPkt->ValidLen && (pSB->Mode == SB_MODE_ATOMIC) )
            pSB->Total--;
        else
            pSB->Total -= (INT32)pPkt->ValidLen;
        pSB->pPktFirst = pPkt->pNext;
        pPkt->pNext = 0;

        return( pPkt );
    }
}

/*-------------------------------------------------------------------- */
/* SBWrite() */
/* Write data (or attach frag) to a SB */
/*-------------------------------------------------------------------- */
INT32 SBWrite( HANDLE h, INT32 Size, void *pData, PBM_Pkt *pPkt )
{
    SB      *pSB = (SB *)h;

#ifdef _STRONG_CHECKING
    if( pSB->Type != HTYPE_SB )
    {
        DbgPrintf(DBG_ERROR,"SBWrite: HTYPE %04x",pSB->Type);
        return( 0 );
    }
#endif

    if( pSB->Mode == SB_MODE_LINEAR )
    {
        /* Linear Case */
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
        /* Atomic Case */
        if( !pPkt )
        {
            DbgPrintf(DBG_ERROR,"SBWrite: No Pkt");
            return( 0 );
        }

        /* Normally the caller is charged with preparing the pkt */
        /* for appending, but if a pointer or size is supplied, then */
        /* we do it here */
        if( pData )
            pPkt->DataOffset = (uint)((UINT8 *)pData - pPkt->pDataBuffer);
        if( Size )
            pPkt->ValidLen = Size;

        /* Put this frag (chain) in the list */
        if( !pSB->pPktFirst )
        {
            pPkt->pPrev = 0;
            pSB->pPktFirst = pPkt;
        }
        else
        {
            pPkt->pPrev = pSB->pPktLast;
            pSB->pPktLast->pNext = pPkt;
        }

        /* We are always the last frag */
        pPkt->pNext = 0;
        pSB->pPktLast = pPkt;

        /* Adjust SB total count (lie for NULL byte packets) */
        if( !pPkt->ValidLen && (pSB->Mode == SB_MODE_ATOMIC) )
            pSB->Total++;
        else
            pSB->Total += pPkt->ValidLen;
    }

    return( Size );
}


/*-------------------------------------------------------------------- */
/* SBSetMax() */
/* Set the max bytes held in a SB (re-alloc) */
/* Returns the new Max size */
/*-------------------------------------------------------------------- */
INT32 SBSetMax( HANDLE h, INT32 Max )
{
    SB      *pSB  = (SB *)h;
    UINT8   *pData;

#ifdef _STRONG_CHECKING
    if( pSB->Type != HTYPE_SB )
    {
        DbgPrintf(DBG_ERROR,"SBSetMax: HTYPE %04x",pSB->Type);
        return;
    }
#endif

    /* If the requested size is NULL, or if */
    /* there is any data held at the socket, abort */
    if( !Max || pSB->Total )
        return( pSB->Max );

    if( pSB->Mode != SB_MODE_LINEAR )
        pSB->Max = Max;
    else
    {
        /* Alloc new buffer */
        pData = mmBulkAlloc( Max );
        if( !pData )
            return( pSB->Max );

        /* Reset the object */
        pSB->Head = pSB->Tail = 0;

        /* Free the old buffer */
        if( pSB->pData )
            mmBulkFree( pSB->pData );

        /* Install the new buffer */
        pSB->pData = pData;
        pSB->Max = Max;
    }

    return( pSB->Max );
}


/* The following functions are direct structure references when */
/* _STRONG_CHECKING is not defined */
#ifdef _STRONG_CHECKING

/*-------------------------------------------------------------------- */
/* SBGetTotal() */
/* Get the total bytes held in a SB */
/*-------------------------------------------------------------------- */
INT32 SBGetTotal( HANDLE h )
{
    SB    *pSB  = (SB *)h;

    if( pSB->Type != HTYPE_SB )
    {
        DbgPrintf(DBG_ERROR,"SBGetTotal: HTYPE %04x",pSB->Type);
        return(0);
    }

    /* Return Total */
    return( pSB->Total );
}

/*-------------------------------------------------------------------- */
/* SBGetMax() */
/* Get the max bytes held in a SB */
/*-------------------------------------------------------------------- */
INT32 SBGetMax( HANDLE h )
{
    SB    *pSB  = (SB *)h;

    if( pSB->Type != HTYPE_SB )
    {
        DbgPrintf(DBG_ERROR,"SBGetMax: HTYPE %04x",pSB->Type);
        return(0);
    }

    /* Return Max */
    return( pSB->Max );
}

/*-------------------------------------------------------------------- */
/* SBGetMin() */
/* Get the min byte threshold of a SB */
/*-------------------------------------------------------------------- */
INT32 SBGetMin( HANDLE h )
{
    SB    *pSB  = (SB *)h;

    if( pSB->Type != HTYPE_SB )
    {
        DbgPrintf(DBG_ERROR,"SBGetMin: HTYPE %04x",pSB->Type);
        return(0);
    }

    /* Return Min */
    return( pSB->Min );
}

/*-------------------------------------------------------------------- */
/* SBSetMin() */
/* Set the min byte threshold of a SB */
/*-------------------------------------------------------------------- */
void SBSetMin( HANDLE h, UINT32 value )
{
    SB    *pSB  = (SB *)h;

    if( pSB->Type != HTYPE_SB )
    {
        DbgPrintf(DBG_ERROR,"SBSetMin: HTYPE %04x",pSB->Type);
        return;
    }

    /* Set Min */
    pSB->Min = value;
}

/*-------------------------------------------------------------------- */
/* SBGetSpace() */
/* Get the space available in a SB */
/*-------------------------------------------------------------------- */
INT32 SBGetSpace( HANDLE h )
{
    SB    *pSB  = (SB *)h;

    if( pSB->Type != HTYPE_SB )
    {
        DbgPrintf(DBG_ERROR,"SBGetSpace: HTYPE %04x",pSB->Type);
        return(0);
    }

    /* Return free space */
    return( pSB->Max - pSB->Total );
}

#endif
