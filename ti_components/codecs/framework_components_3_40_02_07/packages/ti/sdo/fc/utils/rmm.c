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
 *
 */
/*
 *  ======== rmm.c ========
 *  This memory manager provides general heap management one memory segment.
 *
 *  Memory blocks are allocated from the end of the first free memory
 *  block large enough to satisfy the request.
 */

/*
 *  This define is for Logging and must precede the inclusion of any xdc
 *  header files
 */
#define Registry_CURDESC ti_sdo_fc_utils_rmm_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <ti/sdo/fc/global/FCSettings.h>

#include "rmm.h"

#include "_rmm.h"

#define OFFSET(base, address) ((UInt32)(address) - (UInt32)(base))


static Bool allocBlock(RMM_Handle rmm, UInt32 size, UInt32 *addr);
static Bool freeBlock(RMM_Handle rmm, UInt32 addr, UInt32 size);

Registry_Desc ti_sdo_fc_utils_rmm_desc;


static Int refCount  = 0;

/*
 *  ======== RMM_alloc ========
 */
Bool RMM_alloc(RMM_Handle rmm, UInt32 size, UInt32 *addr)
{
    Bool                status;

    Assert_isTrue(rmm != NULL, (Assert_Id)NULL);
    Assert_isTrue(addr != NULL, (Assert_Id)NULL);
    Assert_isTrue(size > 0, (Assert_Id)NULL);

    status = allocBlock(rmm, size, addr);

    return (status);
}

/*
 *  ======== RMM_check ========
 */
Void RMM_check(RMM_Handle rmm, RMM_Stat *stat)
{
    RMM_Header *head;
    RMM_Header *prev;
    RMM_Header *curr;
    RMM_Header *headers;
    Int         nFreeBlocks;
    Int         nFreeHeaders;
    UInt32      totalFree = 0;
    UInt32      maxBlockSize = 0;

    head = &(rmm->freeList);
    curr = prev = head;
    nFreeBlocks = 0;

    /* Array of RMM Headers */
    headers = (RMM_Header *)((UInt32)rmm + rmm->headers);

    /* Check the free blocks */
    while (prev->next != -1) {
        curr = headers + prev->next;
        nFreeBlocks++;
        totalFree += curr->size;

        if (maxBlockSize < curr->size) {
            maxBlockSize = curr->size;
        }

        if (curr->next != -1) {
            Assert_isTrue(curr->addr < (headers + curr->next)->addr,
                    (Assert_Id)NULL);
        }

        prev = curr;
    }

    head = &(rmm->headerPool);
    curr = prev = head;

    /* Count number of headers in the free pool */
    nFreeHeaders = 0;
    while (prev->next != -1) {
        curr = headers + prev->next;
        nFreeHeaders++;
        prev = curr;
    }

    Assert_isTrue((nFreeHeaders + nFreeBlocks) == rmm->nHeaders,
            (Assert_Id)NULL);

    stat->nBlocks = nFreeBlocks;
    stat->size = rmm->length;
    stat->used = rmm->length - totalFree;
    stat->length = maxBlockSize;
}

/*
 *  ======== RMM_create ========
 */
RMM_Handle RMM_create(RMM_Attrs *attrs)
{
    RMM_Obj    *handle;
    Int         i;
    RMM_Header *headers;
    Int         segid;
    Uns         size;


    Assert_isTrue(attrs != NULL, (Assert_Id)NULL);
    Assert_isTrue(attrs->maxFreeListBlocks > 0, (Assert_Id)NULL);
    Assert_isTrue(attrs->length > 0, (Assert_Id)NULL);
    Assert_isTrue(attrs->allocFxn != NULL, (Assert_Id)NULL);
    Assert_isTrue(attrs->freeFxn != NULL, (Assert_Id)NULL);

    segid = attrs->segid;

    /* Allocate RMM object */
    handle = (RMM_Obj *)(attrs->allocFxn)(segid, sizeof(RMM_Obj),
            sizeof(UInt32));

    if (handle != NULL) {
        handle->segid = segid;
        handle->length = attrs->length;
        handle->nHeaders = attrs->maxFreeListBlocks;
        handle->allocFxn = attrs->allocFxn;
        handle->freeFxn = attrs->freeFxn;

        /*
         *  Allocate pool of RMM_Header objects. This is so we will
         *  not have to do any allocation in RMM_free(), and should help
         *  prevent memory from fragmenting.
         */
        size = attrs->maxFreeListBlocks * sizeof(RMM_Header);
        headers = (RMM_Header *)(attrs->allocFxn)(segid, size, sizeof(UInt32));

        if (headers == NULL) {
            (attrs->freeFxn)(segid, handle, sizeof(RMM_Obj));
            handle = NULL;
        }
        else {
            /*
             *  Save the offset of the headers buffer. This is in case we are
             *  sharing the RMM object accross processes, and the virtual
             *  addresses of the object (and its header array) are different.
             */
            handle->headers = OFFSET(handle, headers);

            /*
             *  Initialize the free list with the first free block.
             *  Note: the head of the list is not actually used as a header
             *  for a free block, but contains the index of the first header.
             */
            (handle->freeList).next = 0; /* Index of the first header */
            headers[0].next = -1;          /* End of freelist */
            headers[0].addr = attrs->base;
            headers[0].size = attrs->length;

            /*
             *  Queue up the remaining RMM headers. The head of the list
             *  is not used as an RMM_Header. The list is empty when
             *  headerPool.next == &headerPool
             */
            handle->headerPool.next = 1;       /* Index of second header */

            for (i = 1; i < attrs->maxFreeListBlocks; i++) {
                headers[i].next = i + 1;
            }
            headers[attrs->maxFreeListBlocks - 1].next = -1; /* end of list */
        }
    }

    return (handle);
}

/*
 *  ======== RMM_delete ========
 */
Void RMM_delete(RMM_Handle rmm)
{
    Uns         size;

    Assert_isTrue(rmm != NULL, (Assert_Id)NULL);

    /* Free the buffer of RMM_Headers */
    if (rmm->headers) {
        size = rmm->nHeaders * sizeof(RMM_Header);
        (rmm->freeFxn)(rmm->segid, (Void *)((UInt32)rmm + rmm->headers), size);
    }

    (rmm->freeFxn)(rmm->segid, rmm, sizeof(RMM_Obj));
}

/*
 *  ======== RMM_exit ========
 */
Void RMM_exit(Void)
{
    if (--refCount == 0) {
    }
}

/*
 *  ======== RMM_free ========
 */
Bool RMM_free(RMM_Handle rmm, UInt32 addr, UInt32 size)
{
    Bool status = TRUE;

    Assert_isTrue(rmm != NULL, (Assert_Id)NULL);
    Assert_isTrue(size > 0, (Assert_Id)NULL);

    /* Free memory */
    status = freeBlock(rmm, addr, size);

    return (status);
}

/*
 *  ======== RMM_init ========
 */
Void RMM_init(Void)
{
    Registry_Result   result;

    if (refCount++ == 0) {
        FCSettings_init();

        result = Registry_addModule(&ti_sdo_fc_utils_rmm_desc, RMM_MODNAME);
        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the FC default */
            FCSettings_setDiags(RMM_MODNAME);
        }
    }
}

/*
 *  ======== allocBlock ========
 *  This allocation function allocates memory from the lowest addresses
 *  first.
 */
static Bool allocBlock(RMM_Handle rmm, UInt32 size, UInt32 *addr)
{
    RMM_Header *head;
    RMM_Header *poolHead;
    RMM_Header *prev;
    RMM_Header *curr;
    RMM_Header *headers;
    Int         nextIdx;
    Int         currIdx;
    UInt32      blockSize;
    Bool        retVal = FALSE;

    /* Initialize head pointer to point to beginning of free list */
    head = &(rmm->freeList);

    /* prev pointer should point to the previous entry, start by pointing
       to the head of free list */
    prev = head;

    /* Array of RMM Headers */
    headers = (RMM_Header *)((UInt32)rmm + (UInt32)rmm->headers);

    /* Protect queues in case of context switch */
/*      Task_disable();*/

    /* Loop through free list till you reach the end (-1) */
    while ((currIdx = prev->next) != -1) {

        /* curr pointer should point to the current freeList entry */
        curr = headers + prev->next;

        /* nextIdx should point to the next entry in the linked list */
        nextIdx = curr->next;

        /* size of the current free block */
        blockSize = curr->size;

        if (blockSize >= size) {       /* big enough */

            /* If the block is a perfect match */
            if (blockSize == size) {

                /*
                 *  Remove current header from the list of free blocks
                 *  and put it back in the pool of "allocated" headers, at the
                 *  beginning of the list.
                 */

                /* To remove entry from freeList, adjust the next pointer of
                   the prev entry */
                prev->next = nextIdx;

                /* poolHead points to headerPool which is list of allocated
                   blocks  */
                poolHead = &(rmm->headerPool);

                /* Adjust next pointer of curr */
                curr->next = poolHead->next;

                /* current entry will become the new beginning of headerPool */
                poolHead->next = currIdx;
            }

            /* This is the allocated address, return it */
            *addr = curr->addr;

            /* Adjust current entries size and addr to account for allocated
               memory */
            curr->size -= size;
            curr->addr += size;

            retVal = TRUE;
            break;
        }
        prev = curr;
    }

/*      Task_enable();*/

    return (retVal);
}

/*
 *  ======== freeBlock ========
 */
static Bool freeBlock(RMM_Handle rmm, UInt32 addr, UInt32 size)
{
    RMM_Header *head;
    RMM_Header *poolHead;
    RMM_Header *curr;
    RMM_Header *next = NULL;
    RMM_Header *rhead;
    RMM_Header *headers;
    Int         nextIdx;
    Int         currIdx;
    Int         tmpIdx;
    Bool        joined = FALSE;
    Bool        retVal = TRUE;


    Assert_isTrue(size > 0, (Assert_Id)NULL);

    /* Get the head of the free list */
    head = &(rmm->freeList);

    /* Array of RMM Headers */
    headers = (RMM_Header *)((UInt32)rmm + (UInt32)rmm->headers);

    /* Protect queues in case of context switch */
/*       TSK_disable();*/

    /*
     *  Search down the list of free blocks for the right place to put a
     *  header with address "addr". List is sorted by address, with lowest
     *  address first in the list.
     */
    curr = head;
    currIdx = nextIdx = curr->next;
    while ((nextIdx != -1) && (addr > headers[nextIdx].addr)) {
        curr = headers + nextIdx;
        currIdx = nextIdx;
        nextIdx = curr->next;
    }

    if (nextIdx != -1) {
        next = headers + nextIdx;
    }
    if (currIdx != -1) {
        curr = headers + currIdx;
    }

    /*
     *  The freed block should be put in between curr and next, and the
     *  it should not extend into the next block.
     *  In the case that curr and next are in the middle of the list,
     *  we should have
     *      curr->addr < addr  and (addr + size) <= next->addr
     */
    /*
     *  List is empty, or found element to insert after, or inserting at
     *  the beginning of the list
     */

    /* Got to the end of the list or found element to insert before */
    Assert_isTrue((currIdx == -1) || (curr->addr < addr) ||
            (currIdx == head->next), (Assert_Id)NULL);
    Assert_isTrue((nextIdx == -1) || (addr + size <= next->addr),
            (Assert_Id)NULL);

    /* Join with upper block, if possible */
    if ((nextIdx != -1) && ((addr + size) == next->addr)) {
        next->size += size;
        next->addr = addr;
        joined = TRUE;
    }

    /* Join with the lower block, if possible */
    if ((currIdx != -1) && (currIdx != nextIdx) &&
            ((curr->addr + curr->size) == addr)) {
        if (joined) {
            /*
             *  We need to join the upper block and lower blocks, returning
             *  one of the headers back to the free pool.
             */
            curr->size += next->size;

            /* Take "next" out of the free block list */
            curr->next = next->next;

            /* Put "next" in the pool of free headers */
            poolHead = &(rmm->headerPool);
            next->next = poolHead->next;
            poolHead->next = nextIdx;
        }
        else {
            curr->size += size;
            joined = TRUE;
        }
    }

    /*
     *  If we can't join the block we're freeing to an existing free block,
     *  we need to get an RMM_Header from the free pool, initialize it, and
     *  insert it in the free list.
     */
    if (!joined) {
        poolHead = &(rmm->headerPool);

        /* If the pool of headers is empty, we're stuck */
        if (poolHead->next == -1) {
            /* List is empty */
            Assert_isTrue(FALSE, (Assert_Id)NULL);
            retVal = FALSE;
        }
        else {
            /* Take the first header in the free pool. */
            tmpIdx = poolHead->next;
            rhead = headers + tmpIdx;

            poolHead->next = rhead->next;

            /*
             *  Now insert rhead into the free block list:
             *      curr --> rhead --> next
             */
            if (currIdx == nextIdx) {
                /* Insert at the beginning of the list */
                curr = head;
            }
            curr->next = tmpIdx;
            rhead->next = nextIdx;
            rhead->addr = addr;
            rhead->size = size;
        }
    }

/*      TSK_enable();*/

    return (retVal);
}
