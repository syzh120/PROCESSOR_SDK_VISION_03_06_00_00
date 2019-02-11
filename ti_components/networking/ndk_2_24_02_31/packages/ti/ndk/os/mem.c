/*
 * Copyright (c) 2013, Texas Instruments Incorporated
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
 * ======== mem.c ========
 *
 * Block oriented memory manager implemented using BIOS6
 *
 */

#include <netmain.h>
#include <_oskern.h>

#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>

/* Raw Memory Configuration */

extern const int ti_ndk_config_Global_rawPageSize;
extern const int ti_ndk_config_Global_rawPageCount;

/* Memory Block Structures */

/* Memory Block */
typedef struct {
                uint            Flags;
#define MBF_BUSY        0x8000
#define MBF_INDEXMASK   0x03FF
                UINT8           bData[1];
               } MEMORYBLOCK;

/* P.I.T. */
#if defined(__TMS470__)
extern PITENTRY ti_ndk_config_Global_pit[];
extern UINT8    ti_ndk_config_Global_pitBuffer[];
#elif defined (__IAR_SYSTEMS_ICC__)
extern PITENTRY ti_ndk_config_Global_pit[];
extern UINT8    ti_ndk_config_Global_pitBuffer[];
#else
extern far PITENTRY ti_ndk_config_Global_pit[];
extern far UINT8    ti_ndk_config_Global_pitBuffer[];
#endif

/* P.I.T. Info */
uint   PITCount = 0;
uint   PITUsed  = 0;
uint   PITHigh  = 0;

/* Memory Bucket Information */

#define MEMORY_ID_COUNT         7

extern const int ti_ndk_config_Global_smallest;
extern const int ti_ndk_config_Global_largest;

/* Memory Slot Tracking */
#if defined(__TMS470__)
extern uint ti_ndk_config_Global_Id2Size[];
#elif defined (__IAR_SYSTEMS_ICC__)
extern uint ti_ndk_config_Global_Id2Size[];
#else
extern far uint ti_ndk_config_Global_Id2Size[];
#endif

/* High Water Mark Tracking */
int BlockMax[ MEMORY_ID_COUNT ];
int BlockCount[ MEMORY_ID_COUNT ];
int PageMax[ MEMORY_ID_COUNT ];
int PageCount[ MEMORY_ID_COUNT ];

static UINT32  mmCalls     = 0;
static UINT32  mmFrees     = 0;
static UINT32  mmFails     = 0;
static UINT32  mmBulkCalls = 0;
static UINT32  mmBulkFails = 0;
static UINT32  mmBulkFrees = 0;

/* Initialize the Memory System */
int _mmInit()
{
    uint w;

    /* Init PIT */
    PITCount = ti_ndk_config_Global_rawPageCount;
    PITCount = PITHigh = PITUsed = 0;
    for(w=0; w<ti_ndk_config_Global_rawPageCount; w++)
    {
        ti_ndk_config_Global_pit[w].PageSize = ti_ndk_config_Global_rawPageSize;
        ti_ndk_config_Global_pit[w].pPageStart =
                ti_ndk_config_Global_pitBuffer +
                (ti_ndk_config_Global_rawPageSize*w);
        ti_ndk_config_Global_pit[w].BlockSize  = 0;
        PITCount++;
    }

    /* Init Block Statistics */
    for(w=0; w<MEMORY_ID_COUNT; w++)
    {
        BlockMax[w]   = 0;
        BlockCount[w] = 0;
        PageMax[w]    = 0;
        PageCount[w]  = 0;
    }

    return(1);
}

/* Initialize a new Page, subdividing into blocks */
static void mmInitPage( uint PitIdx, uint SizeIdx )
{
    uint         w;
    uint         Inc;
    UINT8*        pb;

    /* Init the PIT Entry */
    ti_ndk_config_Global_pit[PitIdx].BlockSize =
            ti_ndk_config_Global_Id2Size[SizeIdx];
    ti_ndk_config_Global_pit[PitIdx].BlockSizeIdx  = SizeIdx;
    ti_ndk_config_Global_pit[PitIdx].BlocksPerPage =
            ti_ndk_config_Global_pit[PitIdx].PageSize /
            ti_ndk_config_Global_Id2Size[SizeIdx];
    ti_ndk_config_Global_pit[PitIdx].AllocCount    = 0;
    ti_ndk_config_Global_pit[PitIdx].IdxFreeCheck  = 0;

    /* Init the Memory Blocks in the New Page */
    pb   = ti_ndk_config_Global_pit[PitIdx].pPageStart;
    Inc  = ti_ndk_config_Global_pit[PitIdx].BlockSize;
    for( w=0; w<ti_ndk_config_Global_pit[PitIdx].BlocksPerPage; w++ )
    {
        ((MEMORYBLOCK *)pb)->Flags = PitIdx;
        pb += Inc;
    }

    /* Bump used count */
    PITUsed++;
    if( PITUsed > PITHigh )
        PITHigh = PITUsed;

    /* Maintian Page Block Statistics */
    w = ti_ndk_config_Global_pit[PitIdx].BlockSizeIdx;
    PageCount[ w ]++;
    if( PageCount[ w ] > PageMax[ w ] )
        PageMax[ w ] = PageCount[ w ];
}

/* Uninit an sub-divided Page */
static void mmUnInitPage( uint PitIdx )
{
    /* Init the PIT Entry */
    ti_ndk_config_Global_pit[PitIdx].BlockSize = 0;

    /* Dec used count */
    PITUsed--;

    /* Maintian Page Block */
    PageCount[ ti_ndk_config_Global_pit[PitIdx].BlockSizeIdx ]--;
}

/* Allocate Memory */
void *mmAlloc( uint Size )
{
    uint UseSizeIdx,UseSize;
    uint PitIdx, PitFree, tmp1, tmp2;
    MEMORYBLOCK* pmb;
    uint CritState;

    /* Get index to bucket size, including memory block rsvd uint */
    UseSize = Size+sizeof(uint);

    /* Verify size request at boundary conditions first */
    if( UseSize <= ti_ndk_config_Global_smallest )
        UseSizeIdx = 0;
    else if( UseSize > ti_ndk_config_Global_largest )
        return(0);
    else
    {
        UseSizeIdx = MEMORY_ID_COUNT/2;
        if( ti_ndk_config_Global_Id2Size[UseSizeIdx] >= UseSize )
        {
            while( ti_ndk_config_Global_Id2Size[UseSizeIdx-1] >= UseSize )
                UseSizeIdx--;
        }
        else
        {
            while( ti_ndk_config_Global_Id2Size[UseSizeIdx] < UseSize )
                UseSizeIdx++;
        }
    }

    CritState = OEMSysCritOn();

    mmCalls++;

    /* Look for a PIT already using this size */
    PitIdx  = 0;                        /* Index */
    tmp1    = 0;                        /* Number of PITs examined */
    PitFree = PITCount;                 /* Set "free" to invalid */
    while( PitIdx < PITCount )
    {
        /* Only examined blocks currently in use */
        if( !ti_ndk_config_Global_pit[PitIdx].BlockSize )
            PitFree = PitIdx;
        else
        {
            /* Bump the "examined" count of USED entries */
            tmp1++;

            /* See if we can use this page. It must be our size, */
            /* plus have an entry available */
            if( ti_ndk_config_Global_pit[PitIdx].BlockSizeIdx == UseSizeIdx &&
                    ti_ndk_config_Global_pit[PitIdx].AllocCount <
                    ti_ndk_config_Global_pit[PitIdx].BlocksPerPage )
                goto MMA_PITVALID;
        }

        /* If we've checked all the used entries and have a free entry, */
        /* then use the free entry now */
        if( tmp1 == PITUsed && PitFree != PITCount )
        {
            /* Set Free Page */
            PitIdx = PitFree;

            /* Initialize free page */
            mmInitPage( PitIdx, UseSizeIdx );

            goto MMA_PITVALID;
        }

        /* Nothing found yet - try next entry */
        PitIdx++;
    }

    /* Here we didn't find a free or usable PIT, so we have an OOM */
    /* error or a fatal error */
    if( PITUsed != PITCount )
        DbgPrintf(DBG_ERROR,"mmAlloc: PIT Used Sync");
    goto MMA_ERROR;

MMA_PITVALID:
    /* Allocate the Memory */
    UseSize = ti_ndk_config_Global_Id2Size[UseSizeIdx];

    /* Init our search point (tmp1) to the most likely free block */
    tmp1 = tmp2 = ti_ndk_config_Global_pit[PitIdx].IdxFreeCheck;

    pmb = (MEMORYBLOCK *)(ti_ndk_config_Global_pit[PitIdx].pPageStart +
            (tmp1*UseSize));

    /* Find a free memory page */
    while( pmb->Flags & MBF_BUSY )
    {
        /* Bump the pmb */
        if( ++tmp1 == ti_ndk_config_Global_pit[PitIdx].BlocksPerPage )
        {
            tmp1 = 0;
            pmb = (MEMORYBLOCK *)(ti_ndk_config_Global_pit[PitIdx].pPageStart);
        }
        else
            pmb = (MEMORYBLOCK *)((UINT8 *)pmb + UseSize );

        /* Check for error (tmp1 wrapped) */
        if( tmp1 == tmp2 )
        {
            /* FATAL */
            DbgPrintf(DBG_ERROR,"mmAlloc: PIT FreeBlk Sync");
            goto MMA_ERROR;
        }
    }

    /* Allocate the memory page */
    pmb->Flags |= MBF_BUSY;
    ti_ndk_config_Global_pit[PitIdx].AllocCount++;

    /* Setup next possible free idx */
    if( ++tmp1 == ti_ndk_config_Global_pit[PitIdx].BlocksPerPage )
        tmp1 = 0;
    ti_ndk_config_Global_pit[PitIdx].IdxFreeCheck = tmp1;

    /* Maintain Block Statistics */
    BlockCount[ UseSizeIdx ]++;
    if( BlockCount[ UseSizeIdx ] > BlockMax[ UseSizeIdx ] )
        BlockMax[ UseSizeIdx ] = BlockCount[ UseSizeIdx ];

    OEMSysCritOff( CritState );
    return( pmb->bData );

MMA_ERROR:
    mmFails++;
    OEMSysCritOff( CritState );
    return( 0 );
}

/* Free Memory */
void mmFree( void *p )
{
    MEMORYBLOCK* pmb;
    uint        PitIdx;
    uint        CritState;

    pmb = (MEMORYBLOCK *)((UINT8 *)p - sizeof(uint));

    /* Check for double free */
    if( !(pmb->Flags & MBF_BUSY) )
    {
        /* FATAL */
        DbgPrintf(DBG_WARN,"mmFree: Double Free");
        return;
    }

    /* Get the index */
    PitIdx = (uint)(pmb->Flags & MBF_INDEXMASK);

    CritState = OEMSysCritOn();

    mmFrees++;

    /* Unallocate the block */
    pmb->Flags &= ~MBF_BUSY;

    /* Maintain Block */
    BlockCount[ ti_ndk_config_Global_pit[PitIdx].BlockSizeIdx ]--;

    /* Free the page if no blocks in use */
    if( !(--ti_ndk_config_Global_pit[PitIdx].AllocCount) )
        mmUnInitPage( PitIdx );

    OEMSysCritOff( CritState );

    return;
}

/* Memory Copy */
void mmCopy( void* pDst, void* pSrc, uint len )
{
    UINT32 *pSrc32, *pDst32;
    UINT8  *pSrc8, *pDst8;

    /* Fast Case */
    if( !(((uint)pDst)&0x3) && !(((uint)pSrc)&0x3) )
    {
        pSrc32 = pSrc;
        pDst32 = pDst;

        while( len > 3 )
        {
            *pDst32++ = *pSrc32++;
            len -= 4;
        }

        if( len )
        {
            pSrc8 = (UINT8 *)pSrc32;
            pDst8 = (UINT8 *)pDst32;

            while( len-- )
                *pDst8++ = *pSrc8++;
        }
    }
    else
    {
        pSrc8 = pSrc;
        pDst8 = pDst;

        while( len-- )
            *pDst8++ = *pSrc8++;
    }
}

/* Memory Clear */
void mmZeroInit( void *pDst, uint len )
{
    UINT32 *pDst32;
    UINT8  *pDst8;

    pDst8 = pDst;

    /* Copy 'till aligned */
    while( (((uint)pDst8)&0x3) && len > 0 )
    {
        *pDst8++ = 0;
        len--;
    }

    if( len )
    {
        pDst32 = (UINT32 *)pDst8;

        /* Copy 'till less than 4 bytes */
        while( len > 3 )
        {
            *pDst32++ = 0;
            len -= 4;
        }

        if( len )
        {
            pDst8 = (UINT8 *)pDst32;

            /* Copy 'till done */
            while( len-- )
                *pDst8++ = 0;
        }
    }
}


/*------------------------------------------------------------- */
/* _mmBulkAllocSeg */
/* This function is used to change the default segment for */
/* mmBulkAlloc() and mmBulkFree(). This function will only */
/* work if no calls to mmBulkAlloc() have been made. */
/*------------------------------------------------------------- */
/* ARGSUSED */
void _mmBulkAllocSeg( uint segId )
{
    /*
     *  For BIOS 6, the default Heap will be used for allocations.  If the user
     *  wishes to change the Heap for mmBulkAlloc(), this should be done using
     *  BIOS or XDC APIs as appropriate.
    uint CritState;

    CritState = OEMSysCritOn();

    if( !mmBulkCalls )
        BulkSegId = segId;

    OEMSysCritOff( CritState );
     */
}


/*------------------------------------------------------------- */
/* mmBulkAlloc */
/* This function is used to allocate memory larger than */
/* 3000 bytes */
/*------------------------------------------------------------- */
void *mmBulkAlloc( INT32 Size )
{
    UINT32 *ptr;
    Error_Block eb;

    Error_init(&eb);
    mmBulkCalls++;

    Size += 8;

    /* allocate chunk of memory from the default Heap */
    ptr = (UINT32 *)Memory_alloc(NULL, Size, 4, &eb);

    /* ensure allocation is valid */
    if (ptr != NULL) {
        *ptr = 0x87654321;
        *(ptr+1) = (UINT32)Size;
        return ((void *)(ptr+2));
    }
    else {
        /*
         *  fix SDOCM00100363 and SDOCM00100867.  No need to reset stack if
         *  allocation fails.
         */
        DbgPrintf(DBG_WARN, "mmBulkAlloc(): could not allocate memory.");
        DbgPrintf(DBG_WARN, Error_getMsg(&eb));
        mmBulkFails++;
        return (0);
   }
}

/*------------------------------------------------------------- */
/* mmBulkFree */
/* This function is used to free memory allocated with */
/* mmBulkAlloc() */
/*------------------------------------------------------------- */
void mmBulkFree( void *pMemory )
{
    UINT32 *ptr = (UINT32 *)pMemory;

    if( !ptr )
    {
        DbgPrintf(DBG_ERROR,"mmBulkFree: NULL pointer");
        return;
    }
    ptr -= 2;
    if( *ptr != 0x87654321 )
    {
        DbgPrintf(DBG_ERROR,"mmBulkFree: Corrupted mem or bad ptr (%08x)",ptr);
        return;
    }

    mmBulkFrees++;
    Memory_free(NULL, (Ptr)ptr, *(ptr+1));
}

/*------------------------------------------------------------- */
/* Memory Check */
/* CallMode MMCHECK_MAP      : Map out allocated memory, but */
/*                             don't dump ID's */
/*          MMCHECK_DUMP     : Dump allocated block ID's */
/*          MMCHECK_SHUTDOWN : Dump allocated block's & free */
/*------------------------------------------------------------- */
void _mmCheck( uint CallMode, int (*pPrn)(const char *,...) )
{
    uint   w;
    UINT32 tmp;
    uint   SizeIdx;
    UINT32 Total;
    uint   PitIdx;

    if( !pPrn )
        goto SHUTDOWN;

    /* Memory Usage */
    SizeIdx = 0;
    Total    = 0;
    while( SizeIdx < MEMORY_ID_COUNT )
    {
        if( !(SizeIdx&3) )
            (*pPrn)("\n");
        (*pPrn)("%4u:%-4u ",BlockMax[SizeIdx],
                ti_ndk_config_Global_Id2Size[SizeIdx]);
        tmp = (UINT32)(BlockMax[SizeIdx]) *
                (UINT32)(ti_ndk_config_Global_Id2Size[SizeIdx]);
        Total  += tmp;
        if(tmp)
            (*pPrn)("(%3d%%)  ",
            (tmp*100)/((UINT32)PageMax[SizeIdx]*
            (UINT32)ti_ndk_config_Global_rawPageSize));
        else
            (*pPrn)("        ");

        SizeIdx++;
    }

    (*pPrn)("\n(%u/", PITHigh*(UINT32)ti_ndk_config_Global_rawPageSize);
    (*pPrn)("%u",     PITCount*(INT32)ti_ndk_config_Global_rawPageSize);
    (*pPrn)(" mmAlloc: %u/%u/%u,",mmCalls,mmFails,mmFrees);
    (*pPrn)(" mmBulk: %u/%u/%u)\n",mmBulkCalls,mmBulkFails,mmBulkFrees);

    /* Walk Memory */
    if( PITUsed )
    {
        (*pPrn)("\n");
        for( PitIdx=0; PitIdx<PITCount; PitIdx++ )
        {
            if( ti_ndk_config_Global_pit[PitIdx].BlockSize )
            {
                MEMORYBLOCK *pmb;

                if( !ti_ndk_config_Global_pit[PitIdx].AllocCount )
                    (*pPrn)("IE: No blocks in alloced page\n");
                else
                    (*pPrn)("%d blocks alloced in %d byte page\n",
                            ti_ndk_config_Global_pit[PitIdx].AllocCount,
                            ti_ndk_config_Global_pit[PitIdx].BlockSize );

                if( CallMode != MMCHECK_MAP )
                {
                    w = 0;
                    while( w < ti_ndk_config_Global_pit[PitIdx].BlocksPerPage )
                    {
                        pmb = (MEMORYBLOCK *)
                                (ti_ndk_config_Global_pit[PitIdx].pPageStart +
                                (w*ti_ndk_config_Global_pit[PitIdx].BlockSize));
                        if( pmb->Flags & MBF_BUSY )
                            (*pPrn)("(%04X)  ", *((uint *)pmb->bData));
                        w++;
                    }
                    (*pPrn)("\n");
                }
            }
        }
    }

    (*pPrn)("\n");

SHUTDOWN:
    if( CallMode == MMCHECK_SHUTDOWN )
        PITCount = 0;
}
