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
 * ======== pbm.c ========
 *
 * Packet buffer manager
 *
 */

#include <stkmain.h>

/* Limitation of using mmAlloc */
#define MMALLOC_MAXSIZE 3068

/* Our PBM types */
#define PBM_MAGIC_POOL      0x0F1E2D3C
#define PBM_MAGIC_ALLOC     0x4B5A6978

/*
 *  Buffers defined in either pbm_data.c or *.c file generated from
 *  ti.ndk.config package.
 */
/*
 *  TODO: this ARM special case must not be shipped! Temporary band aid to make
 *  baseline release
 */
#if defined(__TMS470__)
extern UINT8 ti_ndk_config_Global_pBufMem[];
extern UINT8 ti_ndk_config_Global_pHdrMem[];
#elif defined (__IAR_SYSTEMS_ICC__)
extern UINT8 ti_ndk_config_Global_pBufMem[];
extern UINT8 ti_ndk_config_Global_pHdrMem[];
#else
extern far UINT8 ti_ndk_config_Global_pBufMem[];
extern far UINT8 ti_ndk_config_Global_pHdrMem[];
#endif

extern const int ti_ndk_config_Global_numFrameBuf;
extern const int ti_ndk_config_Global_sizeFrameBuf;

/* Flag to make sure we've been opened */
static uint     IsOpen = 0;

/* Queue for Pooled Packets */
PBMQ     PBMQ_free;

/*-------------------------------------------------------------------- */
/* PBM_open() */
/* Open the buffer manager and initialize the free pool */
/*-------------------------------------------------------------------- */
uint PBM_open()
{
    UINT8   *pBufTmp;
    UINT8   *pHdrTmp;
    PBM_Pkt *pPkt;
    uint    i;

    /* Initialize global data */

    /* Initialize Free Queue */
    PBMQ_init(&PBMQ_free);

    /* Get temp pointers */
    pBufTmp = ti_ndk_config_Global_pBufMem;
    pHdrTmp = ti_ndk_config_Global_pHdrMem;

    /* Break memory array into packet buffers and push onto free queue */
    for( i=0; i<ti_ndk_config_Global_numFrameBuf; i++ )
    {
        pPkt = (PBM_Pkt *)pHdrTmp;
        pHdrTmp += sizeof(PBM_Pkt);

        pPkt->Type        = PBM_MAGIC_POOL;
        pPkt->BufferLen   = ti_ndk_config_Global_sizeFrameBuf;
        pPkt->pDataBuffer = pBufTmp;
        pPkt->pTimestampFxn = 0;
        pBufTmp += ti_ndk_config_Global_sizeFrameBuf;

        PBMQ_enq( &PBMQ_free, pPkt );
    }

    IsOpen = 1;

    return(1);
}


/*-------------------------------------------------------------------- */
/* PBM_close() */
/* Close the buffer manager and free all allocated memory */
/*-------------------------------------------------------------------- */
void PBM_close()
{
    IsOpen = 0;
}


/*-------------------------------------------------------------------- */
/* PBM_alloc() */
/* Allocate a Packet Buffer Object */
/* (Can be called at ISR time by HAL) */
/* (Can be called in kernel mode by STACK) */
/*-------------------------------------------------------------------- */
PBM_Handle PBM_alloc( uint MaxSize )
{
    PBM_Pkt     *pPkt = 0;

    /* Verify we're open */
    if( !IsOpen )
        return(0);

    /* Allocate Buffer off the Free Pool is size is OK */
    if( MaxSize <= ti_ndk_config_Global_sizeFrameBuf )
        pPkt = (PBM_Pkt *)PBMQ_deq( &PBMQ_free );
    else
    {
        /* Allocate header from memory */
        pPkt = (PBM_Pkt *)mmAlloc( sizeof(PBM_Pkt) );
        if( pPkt )
        {
            pPkt->Type        = PBM_MAGIC_ALLOC;
            pPkt->BufferLen   = MaxSize;

            /*
             * Allocate Buffer from Memory
             *
             * mmAlloc() is safe at interrupt time
             *
             * Note: a max size breaks down as follows:
             *
             * MMALLOC_MAXSIZE (3068) -> 3016 byte max buff size passed to
             * sendto()
             *
             * 3068: -20 (nimu_mcb hdr_size) - 4 (nimu_mcb trailer_size)
             *       - 20 (IP hdr size) - 8 (UDP hdr size) = 3016
             *
             * So, passing a size of 3017 causes the app to fail below if check
             * and sendto returns error of -55 (ENOBUFS).
             *
             * Note also that nimu_mcb sizes may vary by device, these sizes
             * were based from the evmOMAPL138
             */
            if( MaxSize <= MMALLOC_MAXSIZE )
                pPkt->pDataBuffer = mmAlloc( MaxSize );
            else
            {
                /* Note: If the system needs to support packet buffers */
                /*       greater than MMALLOC_MAXSIZE, then there needs */
                /*       to be large buffer pool or an allocation scheme */
                /*       that can be called at ISR time, since this */
                /*       buffer allocation function can be called from */
                /*       device drivers at interrupt time. */

                /*       The mmAlloc() function can be called from an */
                /*       ISR, but its buffer limited at around 3K. Since */
                /*       the DSP/BIOS memory function can't be called at */
                /*       ISR time, we can't use them here. */

                /*       The addition of large buffer support can be */
                /*       added here if needed. */
#ifndef _INCLUDE_JUMBOFRAME_SUPPORT
                pPkt->pDataBuffer = 0;
#else
                pPkt->pDataBuffer = jumbo_mmAlloc( MaxSize );
#endif
            }

            /* If no buffer, free header */
            if( !pPkt->pDataBuffer )
            {
                mmFree( pPkt );
                pPkt = 0;
            }
        }
    }

    /* If we have a packet, clear all "zero-init" fields. These are */
    /* all the fields starting with "Flags" down. */
    /* NOTE: With the exception of the Packet Priority which should  */
    /* be set to UNDEFINED. */
    if( pPkt )
    {
        mmZeroInit( &pPkt->Flags,
                    sizeof(PBM_Pkt)-((uint)&(pPkt->Flags)-(uint)pPkt));

        /* Ensure that the packet priority is configured to NO PRIORITY. */
        pPkt->PktPriority = PRIORITY_UNDEFINED;
    }

    return( (PBM_Handle)pPkt );
}


/*-------------------------------------------------------------------- */
/* PBM_free() */
/* Free a Packet Buffer Object */
/* (Can be called at ISR time by HAL) */
/* (Can be called in kernel mode by STACK) */
/*-------------------------------------------------------------------- */
void PBM_free( PBM_Handle hPkt )
{
    PBM_Pkt *pPkt = (PBM_Pkt *)hPkt;

    /* Validate the type */
    if(!pPkt || (pPkt->Type!=PBM_MAGIC_POOL && pPkt->Type!=PBM_MAGIC_ALLOC)) {
        DbgPrintf(DBG_ERROR,"PBM_free: Invalid Packet");
        return;
    }

    /* Free any held route */
    /* Note: We do not call RtDeRef() from outside of kernel mode. However, */
    /*       it is impossible for a device driver to be passed a packet that */
    /*       contains a route reference. Thus, if there is a route on this */
    /*       packet, we must have been called from the stack and thus are in */
    /*       kernel mode already. */
    if( pPkt->hRoute )
    {
        RtDeRef( pPkt->hRoute );
        pPkt->hRoute = 0;
    }

#ifdef _INCLUDE_IPv6_CODE
    /* Check if there exists a reference to an IPv6 Route; if one exists we 
     * need to clean it. */
    if (pPkt->hRoute6)
    {
        Rt6Free (pPkt->hRoute6);
        pPkt->hRoute6 = 0;
    }
#endif

    /* If a pool packet, return to free pool */
    if( pPkt->Type == PBM_MAGIC_POOL )
        PBMQ_enq( &PBMQ_free, pPkt );
    /* Else it is an allocated packet, free it */
    else
    {
        if( pPkt->BufferLen <= MMALLOC_MAXSIZE )
            mmFree( pPkt->pDataBuffer );
#ifdef _INCLUDE_JUMBOFRAME_SUPPORT        
        else
        {
            /* When supporting buffers larger than MMALLOC_MAXSIZE, */
            /* they can be freed here. */

            jumbo_mmFree( pPkt->pDataBuffer );
        }
#endif
        mmFree( pPkt );
    }
}

/*-------------------------------------------------------------------- */
/* PBM_copy() */
/* Copy a Packet Buffer Object */
/* (Can be called at ISR time by HAL) */
/* (Can be called in kernel mode by STACK) */
/*-------------------------------------------------------------------- */
PBM_Handle PBM_copy( PBM_Handle hPkt )
{
    PBM_Pkt *pPkt = (PBM_Pkt *)hPkt;
    PBM_Pkt *pPktNew;

    pPktNew = (PBM_Pkt *)PBM_alloc( pPkt->ValidLen + pPkt->DataOffset );

    if( pPktNew )
    {
        /* Copy all structure field from "Flags" down */
        mmCopy( &pPktNew->Flags, &pPkt->Flags,
                sizeof(PBM_Pkt)-((uint)&pPkt->Flags-(uint)pPkt));

        /* Copy the data in the data buffer */
        mmCopy( pPktNew->pDataBuffer + pPktNew->DataOffset,
                pPkt->pDataBuffer + pPkt->DataOffset, pPkt->ValidLen );

        /* Add a reference to a route if we copied it */
        /* Note: We do not call RtRef() from outsise of kernel mode. However, */
        /*       it is impossible for a device driver to be passed a packet that */
        /*       contains a route reference. Thus, if there is a route on this */
        /*       packet, we must have been called from the stack and thus are in */
        /*       kernel mode already. */
        if( pPktNew->hRoute )
            RtRef( pPktNew->hRoute );

#ifdef _INCLUDE_IPv6_CODE
        /* We need to increment the reference counter for the ROUTE6 Handle. */
        if (pPkt->hRoute6)
            Rt6IncRefCount (pPkt->hRoute6);
#endif
    }

    return( (PBM_Handle)pPktNew );
}


/*-------------------------------------------------------------------- */
/* PBMQ_enq() */
/* Enqueue a packet onto the supplied queue */
/*-------------------------------------------------------------------- */
void PBMQ_enq( PBMQ *pQ, PBM_Handle hPkt )
{
    PBM_Pkt *pPkt = (PBM_Pkt *)hPkt;
    uint    mask;

    if( pPkt->Type != PBM_MAGIC_POOL &&
        pPkt->Type != PBM_MAGIC_ALLOC )
    {
        DbgPrintf(DBG_ERROR,"PBM_enq: Invalid Packet");
        return;
    }

    mask = OEMSysCritOn();

    pPkt->pNext = 0;

    if( !pQ->Count )
    {
        /* Queue is empty - Initialize it with this one packet */
        pQ->pHead = pPkt;
        pQ->pTail = pPkt;
        pQ->Count = 1;
    }
    else
    {
        /* Queue is not empty - Push onto END */
        pQ->pTail->pNext = pPkt;
        pQ->pTail        = pPkt;
        pQ->Count++;
    }

    OEMSysCritOff(mask);
}


/*-------------------------------------------------------------------- */
/* PBMQ_deq() */
/* Dequeue a packet from the supplied queue */
/*-------------------------------------------------------------------- */
PBM_Handle PBMQ_deq( PBMQ *pQ )
{
    PBM_Pkt *pPkt;
    uint     mask;

    mask = OEMSysCritOn();

    pPkt = pQ->pHead;

    if( pPkt )
    {
        pQ->pHead = pPkt->pNext;
        if( !pQ->pHead )
            pQ->pTail = 0;
        pQ->Count--;
        pPkt->pPrev = pPkt->pNext = 0;
    }

    OEMSysCritOff(mask);

    return( (PBM_Handle)pPkt );
}


