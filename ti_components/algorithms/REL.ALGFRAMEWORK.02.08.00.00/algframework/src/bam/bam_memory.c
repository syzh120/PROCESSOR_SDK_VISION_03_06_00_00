/*
*
* Copyright (c) 2012-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/



/*****************************************************************************/
/* bam_memory.c v1.0.2                                                           */
/* The functions bam_malloc(), bam_free() are modified versions of malloc(), free()  */
/* Except that the pacjets containing meta-information are not written into the heap */
/* Instead they come from a pool of packets that are separately passed to bam_minit()*/
/*  This module contains the functions which implement the dynamic memory    */
/*  management routines.  The algorithms used are based on the algorithms    */
/*  described in Knuth's "The Art Of Computer Programming, Vol 1" on pages   */
/*  435-441. Algorithm 2.5A has been modified to improve the resistance to   */
/*  fragmentation.                               */
/*                                       */
/*  Knuth gives two reasons for prefering "first fit" over "best fit".       */
/*   1) The algorithm is significantly faster, since the whole of the free   */
/*  store does not have to be searched for each allocation           */
/*  (or deallocation).                           */
/*   2) The first fit algorithm is more resistant to overflow during         */
/*  repeated allocation and deallocation than is the best fit algorithm  */
/*  (See problems 36-43 on page 456).                    */
/*                                       */
/*  The following assumptions/rules apply:                   */
/*                                       */
/*   1) Packets are allocated a minimum of MINSIZE words                 */
/*   2) The heap can be reset at any time by calling the function        */
/*  "minit"                                  */
/*                                       */
/*  The following items are defined in this module :                 */
/*   minit()    : Function to initialize dynamic memory management       */
/*   malloc()   : Function to allocate memory from mem mgmt system.      */
/*   calloc()   : Allocate and clear memory from mem mgmt system.        */
/*   realloc()  : Reallocate a packet                    */
/*   free()     : Function to free allocated memory.             */
/*                                       */
/*  _sys_memory : Array to contain all memory allocate by system.        */
/*   sys_free   : Pointer to free list                   */
/*                                       */
/*   free_memory() : Return total amount of available free memory.       */
/*   max_free() : Return largest single free memory block in heap.       */
/*                                       */
/*****************************************************************************/
/*#define DEBUG*/
#pragma CHECK_MISRA ("none")

#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "cpu.h"
#ifndef HOST_EMULATION

#include <_lock.h>

#else

void _lock(void){}
void _unlock(void){}

#endif

#pragma RESET_MISRA ("required")

#include "bam_common.h"
#include "bam_mempkt.h"

/*****************************************************************************/
/* Declare the memory pool as a .usect called .sysmem.	The size of the	     */
/* section .sysmem is determined by the linker via the -heap option	     */
/*****************************************************************************/

/*---------------------------------------------------------------------------*/
/* Define the heap memory area.  Note that allocated space is actually       */
/* (re)allocated in the linker.  The object must appear in the ".sysmem"     */
/* data section, and it must be aligned properly.                            */
/*---------------------------------------------------------------------------*/
/* Autoinitialize the first packet to indicate a single heap packet whose    */
/* size is equal to the total heap minus the size of the header (a BAM_Packet).  */
/* This is equivalent to calling minit() at boot time.                       */
/*---------------------------------------------------------------------------*/

/* CHECK_MISRA("-20.1")  -> Disable rule 20.1  */
/* These names are not used in any standard library */
static BAM_Packet _bam_imemla_memory[1];
static BAM_Packet _bam_imemha_memory[1];
static BAM_Packet _bam_imemlb_memory[1];
static BAM_Packet _bam_imemhb_memory[1];
static BAM_Packet _bam_wmem_memory[1];
/*RESET_MISRA("20.1")  -> Reset rule 20.1  */

/* CHECK_MISRA("-15.1")  -> Disable rule 15.1 */
/* Goto statement is used */
/* Deviation is allowed because we use GOTO several times throughout the code but they are all forward GOTO to a single exit point */

static int32_t bam_num_packets;
static int32_t bam_packet_index;
int32_t bam_stat_num_packets;

static BAM_Packet *_bam_packet_pool;
static BAM_Packet (*poolArray)[];

/*----------------------------------------------------------------------------
 * vcop_heap datastructure representing the state of a VCOP memory heap
 *---------------------------------------------------------------------------*/
typedef struct vheap
{
    BAM_Packet      *freeblk;  /* Pointer to heap freelist               */
    void         *beg;      /* Location of the beginning of the heap  */
    int32_t          len;      /* Length of the heap                     */
    int32_t          aliased;  /* Aliased state of the heap              */
    int32_t          aliasidx; /* Index of aliased heap freelist         */
} vcop_heap;

#define IMEML_SIZE 0x4000
#define IMEMH_SIZE 0x4000
#define WMEM_SIZE  0x8000

#if defined(CORE_EVE)

#ifndef HOST_EMULATION

/*----------------------------------------------------------------------------
 * Setup the VCOP memory allocator state, consisting of:
 *  - pointer to the freelist for the heap
 *  - the location of the heap in VCOP memory
 *  - the total size of the heap
 *  - whether the heap is aliased by another heap
 *  - ID of the aliased heap, if applicable
 *---------------------------------------------------------------------------*/
static vcop_heap vcop_mem[5] =
{
        { _bam_imemla_memory, ibufla, (int32_t)IMEML_SIZE, 0, VCOP_IBUFLB },
        { _bam_imemha_memory, ibufha, (int32_t)IMEMH_SIZE, 0, VCOP_IBUFHB },
        { _bam_imemlb_memory, ibuflb, (int32_t)IMEML_SIZE, 1, VCOP_NONE },
        { _bam_imemhb_memory, ibufhb, (int32_t)IMEMH_SIZE, 1, VCOP_NONE },
        { _bam_wmem_memory,   wbuf,   (int32_t)WMEM_SIZE,  0, VCOP_NONE }
};

#else

static __declspec(align(BAM_MEM_DEFAULT_ALIGNMENT)) uint8_t ibuflamem[IMEML_SIZE];
static __declspec(align(BAM_MEM_DEFAULT_ALIGNMENT)) uint8_t ibufhamem[IMEMH_SIZE];
static __declspec(align(BAM_MEM_DEFAULT_ALIGNMENT)) uint8_t ibuflbmem[IMEML_SIZE];
static __declspec(align(BAM_MEM_DEFAULT_ALIGNMENT)) uint8_t ibufhbmem[IMEMH_SIZE];
static __declspec(align(BAM_MEM_DEFAULT_ALIGNMENT)) uint8_t wbufmem[WMEM_SIZE];

/*----------------------------------------------------------------------------
 * Setup the VCOP memory allocator state, consisting of:
 *  - pointer to the freelist for the heap
 *  - the location of the heap in VCOP memory
 *  - the total size of the heap
 *  - whether the heap is aliased by another heap
 *  - ID of the aliased heap, if applicable
 *---------------------------------------------------------------------------*/
static vcop_heap vcop_mem[5] =
{
        { _bam_imemla_memory, ibuflamem, (int32_t)IMEML_SIZE, 0, VCOP_IBUFLB },
        { _bam_imemha_memory, ibufhamem, (int32_t)IMEMH_SIZE, 0, VCOP_IBUFHB },
        { _bam_imemlb_memory, ibuflbmem, (int32_t)IMEML_SIZE, 1, VCOP_NONE },
        { _bam_imemhb_memory, ibufhbmem, (int32_t)IMEMH_SIZE, 1, VCOP_NONE },
        { _bam_wmem_memory,   wbufmem,   (int32_t)WMEM_SIZE,  0, VCOP_NONE }
};
#endif
#elif defined(CORE_DSP)

static vcop_heap vcop_mem[5] =
{
        { _bam_imemla_memory, NULL, (int32_t)0, 0, VCOP_IBUFLB },
        { _bam_imemha_memory, NULL, (int32_t)0, 0, VCOP_IBUFHB },
        { _bam_imemlb_memory, NULL, (int32_t)0, 1, VCOP_NONE },
        { _bam_imemhb_memory, NULL, (int32_t)0, 1, VCOP_NONE },
        { _bam_wmem_memory,   NULL, (int32_t)0, 0, VCOP_NONE }
}; 
#endif

/*****************************************************************************/
/* MINSIZE is the smallest packet we will allocate.  It is required that     */
/* (MINSIZE + OVERHEAD >= sizeof(BAM_Packet)), else the packet won't be large    */
/* enough to store the bookkeeping needed to be placed in the free list.     */
/*****************************************************************************/
#define MINSIZE 4
#define MINSIZE_MINUS_1 3
#define MINSIZE_SHIFT 2

/*----------------------------------------------------------------------------
 * ALNBYTES is the amount by which the allocation should be aligned: 32 bytes,
 * not used any more hre as we pass the alignment as argument to the bam_getMemPacket()
 *---------------------------------------------------------------------------*/
#define ALNBYTES 0x20

/*****************************************************************************/
/* This flag tells malloc if the heap needs to be initialized	             */
/*****************************************************************************/
static int32_t first_call = 1;

/*----------------------------------------------------------------------------
 * vcop_view represents the vcop memory view state: FLAT (default) or ALIASED
 *---------------------------------------------------------------------------*/
static VCOP_MEMVIEW vcop_view = VCOP_MEMFLAT;

/*----------------------------------------------------------------------------
 * VCOP_SETVIEW - Set the memory view of the VCOP memory heaps
 *---------------------------------------------------------------------------*/
void bam_setview(VCOP_MEMVIEW view) { vcop_view = view; }

/*****************************************************************************/
/*                                       */
/*  MINIT - This function performs the initial setup of the heap, and can    */
/*          be called by the user to completely reset the memory management  */
/*          system.                                          */
/*                                       */
/*****************************************************************************/
int32_t bam_minit(BAM_Packet *packet_pool, int32_t num_packets,BAM_InternalMemParams * intMemParams)
{

    int32_t heap, i;
    int32_t status= 0;

    _lock();

#ifdef CORE_DSP
    vcop_mem[0].beg = intMemParams->dataIoMem; /* Ping buffer for the lower half */
    vcop_mem[1].beg = (int8_t*)intMemParams->dataIoMem + (intMemParams->dataIoMemSize/4); /* Ping buffer for the higher half */
    vcop_mem[2].beg = ((int8_t*)vcop_mem[0].beg + intMemParams->dataIoMemSize/2); /* Pong buffer for the lower half */
    vcop_mem[3].beg = ((int8_t*)vcop_mem[1].beg + intMemParams->dataIoMemSize/2); /* Pong buffer for the higher half */
    vcop_mem[4].beg = intMemParams->scratchOrConstMem;
    vcop_mem[0].len = intMemParams->dataIoMemSize/4;
    vcop_mem[1].len = intMemParams->dataIoMemSize/4;
    vcop_mem[2].len = intMemParams->dataIoMemSize/4;
    vcop_mem[3].len = intMemParams->dataIoMemSize/4;
    vcop_mem[4].len = intMemParams->scratchOrConstMemSize;
#endif

    bam_num_packets= num_packets;

    if (packet_pool != NULL) {
        _bam_packet_pool= packet_pool;
    }
    else {
#ifdef DEBUG_BAM_MALLOC
        PRINTF("Error bam_init: packet_pool pointer is NULL\n");
#endif
        status= -1;
        goto EXIT;
    }

    /*------------------------------------------------------------------------
     * To initialize the memory system, set up the free list in each applicable
     * heap to point to the entire heap and initialize the heap to a single
     * empty packet.
     *-----------------------------------------------------------------------*/
    for (heap = VCOP_IBUFLA; heap <= VCOP_WMEM; heap++)
    {
        memsz_t size;
        uint32_t temp;
        int32_t temp2;

        temp= ((uint32_t)vcop_mem[heap].len & ~(uint32_t)(MINSIZE-1));
        temp2= - ((int32_t)temp);
        size= (memsz_t)temp2;

        vcop_mem[heap].freeblk->packet_size = size;
        vcop_mem[heap].freeblk->next_free   = LIMIT;
        vcop_mem[heap].freeblk->uaptr        = vcop_mem[heap].beg;
    }

    poolArray= (BAM_Packet (*)[])(void*)_bam_packet_pool;

    for (i=0;i<bam_num_packets;i++) {
        (*poolArray)[i].heap= VCOP_NONE;
    }

    bam_packet_index= 0;
    bam_stat_num_packets= 0;

    first_call = 0; /* CLEAR THE FLAG */
    _unlock();

    EXIT:
    return status;
}
/*********************************************************************************
 * Application can use this function to check the consistancy of the heap, after
 * all memory has been freed.
 * If any error is returned then not all memories have been freed, which could
 * point to some memory leak somewhere.
*********************************************************************************/
int32_t bam_mcheck(void){
    int32_t status= 0;

    if ((vcop_mem[VCOP_IBUFLA].freeblk!= _bam_imemla_memory) || (vcop_mem[VCOP_IBUFHA].freeblk!= _bam_imemha_memory)
            || (vcop_mem[VCOP_IBUFLB].freeblk!= _bam_imemlb_memory) || (vcop_mem[VCOP_IBUFHB].freeblk!= _bam_imemhb_memory)
            || (vcop_mem[VCOP_WMEM].freeblk!= _bam_wmem_memory)) {
        status= -1;
        }

    return status;

}

/*****************************************************************************/
/*                                       */
/*  MALLOC - Allocate a packet of a given size, and return pointer to it.    */
/*                                       */
/*****************************************************************************/
BAM_Packet *bam_getMemPacket(VCOP_MEMHEAP heap, int32_t alignment, size_t size)
{
    uint8_t (*uaptr)[];
    BAM_Packet *packet= 0;
    int32_t allocsize = (int32_t)size;
    uint8_t *addr;
    uint32_t addr_int;
    uint32_t alignment_1;

    /*------------------------------------------------------------------------
     * If the memory is "aliased", aliased heaps are off limits to user
     *-----------------------------------------------------------------------*/
    if ( (vcop_view == VCOP_MEMALIASED) && (vcop_mem[heap].aliased != 0)) {
#ifdef DEBUG_BAM_MALLOC
        PRINTF("bam_getMemPacket error, alias mode used but heap is in image buffer B\n");
#endif
        goto EXIT;
    }

    /*------------------------------------------------------------------------
     * If allocsize is zero or if heap is empty, don't attempt to allocate
     *-----------------------------------------------------------------------*/
    if ((allocsize == 0) || (vcop_mem[heap].len == 0)) {
        goto EXIT;
    }

    /*------------------------------------------------------------------------
     * Align the size of the allocation request so that the allocated address
     * can be aligned along a 32byte (256bit) boundary to accomodate VCOP usage
     * scenarios.  Also include 4-bytes so that the original, unaligned memory
     * address can be stored off to be retrieved later by vcop_free(). Then,
     * adjust the size of the allocation according to MINSIZE in order to ensure
     * that the address of the field "next_free" remains strickly aligned in all
     * packets on the free list.
     *
     * Essentially, we need a buffer that looks like this, where OVERHEAD refers
     * to the internal allocator overhead to maintain the allocated size:
     *
     *      ------------------------------------------------------------
     *     | OVERHEAD | alignment - OVERHEAD | sizeof(void*) | allocsize |
     *      ------------------------------------------------------------
     *                ^- unaln addr
     *
     * This turns into:
     *
     *      ------------------------------------------------------------
     *     | <- 4b -> | <----- 0x1Cb -----> | <--- 4b ----> | allocsize |
     *      ------------------------------------------------------------
     *                ^- unaln addr
     *
     * mem_alloc() will return "unaln addr", and the VCOP allocator needs to
     * be able to align that address to be 32byte aligned and also take into
     * account 4bytes of space to store the "unaln addr" so that it can be found
     * by vcop_free().  The reason we need both 32bytes (consisting of total
     * overhead) AND 4-bytes for sizeof(void*) is to handle the case in which
     * "unaln addr" is already aligned along a 32 byte boundary and we still
     * need 4bytes of space at which to store the value for vcop_free() to know
     * what address it needs to free.  If this is not done, vcop_free() cannot
     * know what address it has to free nor would it know that the address it
     * was given was already aligned.  Thus we waste total 36bytes overhead
     * per allocation, which for VCOP is acceptable.
     *-----------------------------------------------------------------------*/
/* CHECK_MISRA("-12.7")  -> Disable rule 12.7  */
/* Operand of bitwise operation is not unsigned integer */
/* Need to update MISRA-C policy document: Deviation allowed since compiler preserved the signed bit when right shifting signed integer */
    allocsize= (((allocsize + MINSIZE_MINUS_1)>>MINSIZE_SHIFT)<<MINSIZE_SHIFT);
/* RESET_MISRA("12.7")  -> Reset rule 12.7*/

    if (first_call) {
#ifdef DEBUG_BAM_MALLOC
        PRINTF("bam_getMemPacket error, bam_init() should have been called prior to this call\n");
#endif
        goto EXIT;
    }

    _lock();

    /*------------------------------------------------------------------------
     * Allocate requested memory from primary heap
     *-----------------------------------------------------------------------*/
    packet = bam_mem_alloc(&vcop_mem[heap].freeblk, (size_t)allocsize, alignment, heap);

    if ((packet != NULL) && (packet != LIMIT)) {
        packet->heap= heap;
    }
    else {
        goto EXIT;
    }

    /*------------------------------------------------------------------------
     * If the memory is "aliased", allocate also from the aliased block.
     * There are two primary reasons for this:
     *
     * 1.) The allocator can guarantee that if it returns an allocated address
     *     from the primary heap, the precise and expected area of memory is also
     *     available in the aliased heap.
     * 2.) The allocator can guarantee that both the primary and aliased heaps
     *     are setup correctly by the user and no other data is placed in them
     *     that would impact heap accessibility or allocatable size.
     *-----------------------------------------------------------------------*/
    if ( (vcop_view == VCOP_MEMALIASED) && (vcop_mem[heap].aliasidx != VCOP_NONE))
    {
        int32_t aheap  = vcop_mem[heap].aliasidx;
        /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
        /* Cast between a pointer and an integral type */
        /* Deviation allowed as we want to obtain the offset between two pointers */
        intptr_t pdiff  = (intptr_t)vcop_mem[aheap].beg - (intptr_t)vcop_mem[heap].beg;
        /* RESET_MISRA("11.3")  -> Reset rule 11.3*/
        BAM_Packet *apacket = bam_mem_alloc(&vcop_mem[aheap].freeblk, (size_t)allocsize, alignment, aheap);

        /*--------------------------------------------------------------------
         * If allocation of aliased heap fails, free primary heap and return 0.
         * The allocator cannot guarantee that the aliased buffer can be used
         * safely.
         *-------------------------------------------------------------------*/
        if ((apacket == NULL) || (apacket == LIMIT))
        {
            bam_mem_free(&vcop_mem[heap].freeblk, packet);
            packet= apacket;
            goto EXIT;
        }

        apacket->heap= aheap;

        /*--------------------------------------------------------------------
         * If the ptrs are not consistent or in sync, free both and return 0.
         * This means the allocator has determined that something has impacted
         * the accessibilty or allocatable size of either or both of the heaps.
         *-------------------------------------------------------------------*/
        /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
        /* Cast between a pointer and an integral type */
        /* Deviation allowed as we want to obtain the offset between two pointers */
        if (((intptr_t)apacket->uaptr - (intptr_t)packet->uaptr) != pdiff)
        {
            bam_mem_free(&vcop_mem[heap].freeblk,   packet);
            bam_mem_free(&vcop_mem[aheap].freeblk, apacket);
            packet= NULL;
            goto EXIT;
        }
        /* RESET_MISRA("11.3")  -> Reset rule 11.3*/
        packet->apacket= apacket;
    }

    /*------------------------------------------------------------------------
     * Align the memory pointer by 32 bytes, including space for actual ptr
     *-----------------------------------------------------------------------*/
    uaptr= (uint8_t(*)[])packet->uaptr;
    addr= &((*uaptr)[0]);
    alignment_1= ((uint32_t)alignment - 1U);
    /* CHECK_MISRA("-12.7")  -> Disable rule 12.7  */
    /* Operand of bitwise operation is not unsigned integer */
    /* Deviation allowed since compiler preserved the signed bit when doing and operation */
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* Cast between a pointer and an integral type */
    /* Deviation allowed since we are doing pointer arithmetic to align */
    addr_int= ((uintptr_t)addr + alignment_1) & (~alignment_1);
    /* RESET_MISRA("12.7")  -> Reset rule 12.7*/
    packet->ptr= (void*)addr_int;
    /* RESET_MISRA("11.3")  -> Reset rule 11.3*/

    EXIT:
    _unlock();
    /*------------------------------------------------------------------------
     * Record unaligned memory pointer so that it can be freed later
     *-----------------------------------------------------------------------*/
    /*((void**)mem)[-1] = &packet;*/

    return packet;
}

BAM_Packet *bam_get_packet(int32_t heap){

    int32_t i= 0;
    BAM_Packet *packetPtr= LIMIT;

    while (((*poolArray)[bam_packet_index].heap!= VCOP_NONE) && (i < bam_num_packets)) {
        bam_packet_index++;
        if (bam_packet_index== bam_num_packets){
            bam_packet_index= 0;
        }
        i++;
    }

    if (i== bam_num_packets) {
#ifdef DEBUG
        PRINTF("bam_get_packet() error, array bam_packet_pool too small, increase BAM_NUM_GUARD_PACKETS in file bam_mempkt.h and recompile\n");
#endif
    }
    else {
        (*poolArray)[bam_packet_index].heap= heap;
        packetPtr= &((*poolArray)[bam_packet_index]);
        bam_stat_num_packets++;
    }

    return packetPtr;
}

/*****************************************************************************/
/*                                                                           */
/*  MEM_ALLOC - Generic malloc algorithm, operating on a given freelist ptr  */
/*                                                                           */
/*****************************************************************************/
BAM_Packet *bam_mem_alloc(BAM_Packet **free_mem, size_t allocsize, int32_t alignment, int32_t heap)
{
    BAM_Packet *current, *next, *prev;
    uint32_t ptr_al;
    uint32_t alignment_1;
    uint8_t (*ptr)[];

    _lock();

    current = *free_mem;
    prev = 0;

    /*-----------------------------------------------------------------------*/
    /* Find the first block large enough to hold the requested allocation    */
    /*-----------------------------------------------------------------------*/
    while ((current != LIMIT) && ((int32_t)-current->packet_size < (int32_t)allocsize))
    {
        prev = current;
        current = current->next_free;
    }

    if (current == LIMIT)
    {
        /*-------------------------------------------------------------------*/
        /* No block large enough was found, so return NULL.		     */
        /*-------------------------------------------------------------------*/
#ifdef DEBUG
        PRINTF("bam_mem_alloc() error, no block large enough was found\n");
#endif
        current= NULL;
        goto EXIT;
    }

    /* Calculate the aligned version of the pointer of the memory block that was just found */
    ptr= (uint8_t (*)[])(void*)current->uaptr;
    alignment_1= ((uint32_t)alignment - 1U);
    /* CHECK_MISRA("-12.7")  -> Disable rule 12.7  */
    /* Operand of bitwise operation is not unsigned integer */
    /* Deviation allowed since compiler preserved the signed bit when doing and operation */
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* Cast between a pointer and an integral type */
    /* Deviation allowed since we are doing pointer arithmetic to align */
    ptr_al= ((uintptr_t)ptr + alignment_1) & (~alignment_1);
    /* RESET_MISRA("12.7")  -> Reset rule 12.7*/
    /* If the aligned version of the pointer is not equal to the non-aligned version then we resume the search of the memory block, but this time with
     * allocsize incremented by the amount alignment, otherwise the memory block that was found is correct */
    if ((uintptr_t)ptr != ptr_al) {
    /* RESET_MISRA("11.3")  -> Reset rule 11.3*/
        allocsize+= (size_t)alignment;
        while ((current != LIMIT) && ((int32_t)-current->packet_size < (int32_t)allocsize))
        {
            prev = current;
            current = current->next_free;
        }

        if (current == LIMIT)
        {
            /*-------------------------------------------------------------------*/
            /* No block large enough was found, so return NULL.          */
            /*-------------------------------------------------------------------*/
#ifdef DEBUG
            PRINTF("bam_mem_alloc() error, no block large enough was found\n");
#endif
            current= NULL;
            goto EXIT;
        }
    }

    if ((int32_t)(-current->packet_size) > ((int32_t)allocsize + (int32_t)MINSIZE))
    {
        /*-------------------------------------------------------------------*/
        /* The packet is larger than needed; split the block and mark the    */
        /* smaller-addressed block as used.  The smaller-addressed block     */
        /* was chosen as a way to ensure that freed blocks get recycled	     */
        /* before allocations are made from the large original free block.   */
        /* However, this may tend to increase the length of the free list    */
        /* search for a large enough block.                                            */
        /*-------------------------------------------------------------------*/
        /* Knuth's algorithm 2.5a instead allocates the larger-addressed     */
        /* block to the user.  This tends to leave the largest free blocks   */
        /* at the beginning of the free list.  Knuth's 2.5a' uses a "rover"  */
        /* pointer to prevent small free blocks from being concentrated in   */
        /* any part of the list.                                                                  */
        /*-------------------------------------------------------------------*/
        /*next = (BAM_Packet *)((char *)current + allocsize + OVERHEAD);*/
        next= bam_get_packet(heap);

        if (next == LIMIT)
        {
            /*-------------------------------------------------------------------*/
            /* No more packet available                                          */
            /*-------------------------------------------------------------------*/
            current= LIMIT;
            goto EXIT;
        }

        next->packet_size=current->packet_size+allocsize;/*NEG==FREE*/
        ptr= (uint8_t (*)[])(void*)current->uaptr;
        next->uaptr= (void*)&((*ptr)[allocsize]);
        current->packet_size = allocsize; /* POSITIVE==IN USE */

        if (prev) {
            prev->next_free = next;
        }
        else     {
            *free_mem       = next;
        }

        next->next_free = current->next_free;
    }
    else
    {
        /*-------------------------------------------------------------------*/
        /* Allocate the whole block and remove it from the free list.	     */
        /*-------------------------------------------------------------------*/
        if (prev) {
            prev->next_free = current->next_free;
        }
        else      {
            *free_mem       = current->next_free;
        }

        current->packet_size = -current->packet_size; /* POSITIVE==IN USE */
    }

    EXIT:
    _unlock();
    return (current);
}

int32_t bam_put_packet(BAM_Packet *packet){

    int32_t status= 0;

    if (packet == NULL) {
#ifdef DEBUG_BAM_MALLOC
        PRINTF("bam_put_packet() error, input pointer was NULL\n");
#endif
        status= -1;
    }
    else {
        packet->heap= VCOP_NONE;
        bam_stat_num_packets--;
    }

    return status;

}

/*----------------------------------------------------------------------------
 * VCOP_FREE - Return a packet allocated by vcop_malloc to the VCOP free memory
 *             pool.  The algorithm will automatically calculate which heap from
 *             which to free the memory.
 *---------------------------------------------------------------------------*/
void bam_releaseMemPacket(BAM_Packet *packet)
{
    int32_t heap;

    /*------------------------------------------------------------------------
     * If pointer is NULL, just return
     *-----------------------------------------------------------------------*/
    if (packet == 0) {
#ifdef DEBUG_BAM_MALLOC
        PRINTF("bam_releaseMemPacket() error, input pointer was NULL\n");
#endif
        goto EXIT;
    }

    /*------------------------------------------------------------------------
     * Extract actual pointer to be freed
     *-----------------------------------------------------------------------*/
    /*ptr = ((void**)userptr)[-1];*/

    for (heap = VCOP_IBUFLA; heap <= VCOP_WMEM; heap++)
    {
        if (packet->heap== heap)
        {
            _lock();

            /*----------------------------------------------------------------
             * If aliased view, free memory from aliased block
             *---------------------------------------------------------------*/
            if ( (vcop_view == VCOP_MEMALIASED) && (vcop_mem[heap].aliasidx != VCOP_NONE))
            {
                int32_t aheap = vcop_mem[heap].aliasidx;
                bam_mem_free(&vcop_mem[aheap].freeblk, packet->apacket);
            }

            /*----------------------------------------------------------------
             * Free memory from block
             *---------------------------------------------------------------*/
            bam_mem_free(&vcop_mem[heap].freeblk, packet);
            goto EXIT;
        }
    }
    EXIT:
    _unlock();
    return;
}


/******************************************************************************/
/*                                                                                                                                     */
/*  MEM_FREE - Generic free algorithm, operating on a given freelist ptr                                */
/*                                                                                                                                    */
/*****************************************************************************/
void bam_mem_free(BAM_Packet **free_mem, BAM_Packet *packet)
{
    BAM_Packet *next, *prev;
    uint8_t (*sysblock)[];
    uint8_t (*uaptr)[];

    _lock();

    if (packet == 0) {
#ifdef DEBUG_BAM_MALLOC
        PRINTF("bam_mem_free() error, input packet pointer was NULL\n");
#endif
        goto EXIT; /* HANDLE NULL POINTER */
    }

    /*-----------------------------------------------------------------------*/
    /* If there is no free memory before this free, then this packet becomes */
    /* the free_mem and there is no need to check for coalescing             */
    /*-----------------------------------------------------------------------*/
    if(*free_mem == LIMIT)
    {
        *free_mem = packet;
        packet->packet_size = -packet->packet_size; /* NEGATIVE==FREE */
        goto EXIT;
    }

    next = *free_mem;
    prev = 0;
    sysblock = (uint8_t (*)[])packet->uaptr;

    /*-----------------------------------------------------------------------*/
    /* Search the free list for the *free* packets physically closest to     */
    /* the packet to be freed.  PREV is the closest free packet with a	     */
    /* smaller address, and NEXT is the closest free packet with a larger    */
    /* address.								     */
    /*-----------------------------------------------------------------------*/
    while ((next != LIMIT) && ((uint8_t*)next->uaptr < (*sysblock)))
    {
        prev = next;
        next = next->next_free;
    }

    /*-----------------------------------------------------------------------*/
    /* Coalesce with next block if possible.                                 */
    /*-----------------------------------------------------------------------*/
    if ((next != LIMIT) && (&((*sysblock)[packet->packet_size]) == (uint8_t *)next->uaptr))
    {
        packet->next_free = next->next_free;
        packet->packet_size=  (packet->packet_size - next->packet_size);/* POS==USED */
        bam_put_packet(next); /* put packet back to the pool of packets */
    }
    else {
        packet->next_free = next;	/* START TO PUT INTO LIST */
    }

    if (prev)               /* ARE WE THE NEW HEAD OF THE LIST */
    {
        /*-------------------------------------------------------------------*/
        /* sysblock is not the head of the free list; try to coalesce with   */
        /* prev                                                              */
        /*-------------------------------------------------------------------*/
        uaptr= (uint8_t (*)[])prev->uaptr;

        if ( &((*uaptr)[- prev->packet_size]) == (*sysblock))
        {
            prev->next_free = packet->next_free;
            prev->packet_size = prev->packet_size -packet->packet_size;/*NEG==FREE*/
            bam_put_packet(packet);
        }
        else
        {
            prev->next_free = packet;
            packet->packet_size = -packet->packet_size; /* NEGATIVE==FREE */
        }
    }
    else
    {
        *free_mem = packet;
        packet->packet_size = -packet->packet_size; /* NEGATIVE==FREE */
    }

    EXIT:
    _unlock();
    return;
}

/*RESET_MISRA("15.1")  -> Reset rule 15.1 for GOTO */


