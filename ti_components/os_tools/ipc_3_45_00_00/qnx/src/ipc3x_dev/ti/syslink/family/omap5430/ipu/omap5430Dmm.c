/*
 *  @file  omap5430Dmm.c
 *
 *  @brief  MMU programming module
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2010-2013, Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  Contact information for paper mail:
 *  Texas Instruments
 *  Post Office Box 655303
 *  Dallas, Texas 75265
 *  Contact information:
 *  http://www-k.ext.ti.com/sc/technical-support/product-information-centers.htm?
 *  DCMP=TIHomeTracking&HQS=Other+OT+home_d_contact
 *  ============================================================================
 *
 */

/*
 *  ======== dmm.c ========
 *  Purpose:
 *The Dynamic Memory Manager (DMM) module manages the DSP Virtual address
 *space that can be directly mapped to any MPU buffer or memory region
 *
 * Public Functions:
 * ----------------------
 *    dmm_create_tables            -- Done
 *    dmm_create                    -- Done
 *    dmm_destroy                -- Done
 *    dmm_exit
 *    dmm_init                    -- Done
 *    dmm_map_memory            -- Done
 *    DMM_Reset
 *    dmm_reserve_memory        -- Done
 *    dmm_unmap_memory
 *    dmm_unreserve_memory        -- Done
 *
 * Private Functions:
 * -------------------
 *    add_region
 *    create_region
 *    get_region
 *    get_free_region                -- Done
 *    get_mapped_region            -- Done
 *
 *  Notes:
 *Region: Generic memory entity having a start address and a size
 *Chunk:  Reserved region
 *
 *!
 */

#include <errno.h>
#include <ti/syslink/Std.h>
#include "OMAP5430Dmm.h"
#include <OsalMutex.h>

#define DMM_ADDR_VIRTUAL(x, a)                        \
    do {                                \
        x = (((struct map_page *)(a) - p_virt_mapping_tbl) * PAGE_SIZE \
                        + dyn_mem_map_begin);\
    } while (0)

#define DMM_ADDR_TO_INDEX(i, a)                        \
    do {                                \
        i = (((a) - dyn_mem_map_begin) / PAGE_SIZE);        \
    } while (0)

struct map_page {
    u32 region_size:31;
    u32 b_reserved:1;
};

/*  Create the free list */
static struct map_page *p_virt_mapping_tbl;
static u32 i_freeregion;    /* The index of free region */
static u32 i_freesize;
static u32 table_size;/* The size of virtual and physical pages tables */
static u32 dyn_mem_map_begin;
OsalMutex_Handle     dmm_lock;

/*
 *  ======== get_mapped_region ========
 *  Purpose:
 *  Returns the requestedmapped region
 */
struct map_page *get_mapped_region(u32 addr)
{
    u32 i = 0;
    struct map_page *curr_region = NULL;

    if (p_virt_mapping_tbl == NULL)
        return curr_region;

    DMM_ADDR_TO_INDEX(i, addr);
    if (i < table_size && (p_virt_mapping_tbl[i].b_reserved))
        curr_region = p_virt_mapping_tbl + i;
    return curr_region;
}



/*
 *  ======== get_free_region ========
 *  Purpose:
 *  Returns the requested free region
 */
struct map_page *get_free_region(u32 size)
{
    struct map_page *curr_region = NULL;
    u32 i = 0;
    u32 region_size = 0;
    u32 next_i = 0;

    if (p_virt_mapping_tbl == NULL)
        return curr_region;
    if (size > i_freesize) {
        /* Find the largest free region
        * (coalesce during the traversal) */
        while (i < table_size) {
            region_size = p_virt_mapping_tbl[i].region_size;
            next_i = i+region_size;
            if (p_virt_mapping_tbl[i].b_reserved == false) {
                /* Coalesce, if possible */
                if (next_i < table_size &&
                p_virt_mapping_tbl[next_i].b_reserved
                            == false) {
                    p_virt_mapping_tbl[i].region_size +=
                    p_virt_mapping_tbl[next_i].region_size;
                    continue;
                }
                region_size *= PAGE_SIZE;
                if (region_size > i_freesize)     {
                    i_freeregion = i;
                    i_freesize = region_size;
                }
            }
            i = next_i;
        }
    }
    if (size <= i_freesize) {
        curr_region = p_virt_mapping_tbl + i_freeregion;
        i_freeregion += (size / PAGE_SIZE);
        i_freesize -= size;
    }
    return curr_region;
}




/*
 *  ======== dmm_delete_tables ========
 *  Purpose:
 *Delete DMM Tables.
 */
void dmm_delete_tables(void)
{
    /* Delete all DMM tables */
    IArg key = 0;
    OsalMutex_enter(dmm_lock);
    if (p_virt_mapping_tbl != NULL) {
        free(p_virt_mapping_tbl);
        p_virt_mapping_tbl = NULL;
    }
    OsalMutex_leave(dmm_lock, key);
}




/*  ======== dmm_create_tables ========
 *  Purpose:
 *Create table to hold information of the virtual memory that is reserved
 *for DSP.
 */
int dmm_create_tables(u32 addr, u32 size)
{
    int status = 0;

    IArg key = 0;

    dmm_delete_tables();
    OsalMutex_enter(dmm_lock);

    dyn_mem_map_begin = addr;
    table_size = (size/PAGE_SIZE) + 1;
    /*  Create the free list */
    p_virt_mapping_tbl = (struct map_page *)malloc(
                    table_size*sizeof(struct map_page));
    if (p_virt_mapping_tbl == NULL)
        status = -ENOMEM;
    /* On successful allocation,
    * all entries are zero ('free') */
    i_freeregion = 0;
    i_freesize = table_size*PAGE_SIZE;
    p_virt_mapping_tbl[0].region_size = table_size;
    OsalMutex_leave(dmm_lock, key);

    return status;
}

/*
 *  ======== dmm_create ========
 *  Purpose:
 *Create a dynamic memory manager object.
 */
int dmm_create(void)
{
    int status = 0;
    dmm_lock = OsalMutex_create (OsalMutex_Type_Interruptible);

    return status;
}



/*
 *  ======== dmm_destroy ========
 *  Purpose:
 *Release the communication memory manager resources.
 */
void dmm_destroy(void)
{
    dmm_delete_tables();
    OsalMutex_delete(&dmm_lock);
}




/*
 *  ======== dmm_init ========
 *  Purpose:
 *Initializes private state of DMM module.
 */
void dmm_init(void)
{
    p_virt_mapping_tbl = NULL ;
    table_size = 0;
}

/*
 *  ======== dmm_reserve_memory ========
 *  Purpose:
 *Reserve a chunk of virtually contiguous DSP/IVA address space.
 */
int dmm_reserve_memory(u32 size, u32 *p_rsv_addr)
{

    int status = 0;

    struct map_page *node;
    u32 rsv_addr = 0;
    u32 rsv_size = 0;
    IArg key = 0;


     OsalMutex_enter(dmm_lock);

    /* Try to get a DSP chunk from the free list */
    node = get_free_region(size);
    if (node != NULL) {
        /*  DSP chunk of given size is available. */
        DMM_ADDR_VIRTUAL(rsv_addr, node);
        /* Calculate the number entries to use */
        rsv_size = size/PAGE_SIZE;
        if (rsv_size < node->region_size) {
            /* Mark remainder of free region */
            node[rsv_size].b_reserved = false;
            node[rsv_size].region_size =
                node->region_size - rsv_size;
        }
        /*  get_region will return first fit chunk. But we only use what
            is requested. */
        node->b_reserved = true;
        node->region_size = rsv_size;
        /* Return the chunk's starting address */
        *p_rsv_addr = rsv_addr;
    } else
        /*dSP chunk of given size is not available */
        status = -ENOMEM;
    OsalMutex_leave(dmm_lock, key);

    return status;
}


/*
 *  ======== dmm_unreserve_memory ========
 *  Purpose:
 *Free a chunk of reserved DSP/IVA address space.
 */

int dmm_unreserve_memory(u32 rsv_addr, u32 *psize)
{
    int status = 0;

    struct map_page *chunk;
    IArg key = 0;

     OsalMutex_enter(dmm_lock);
    /* Find the chunk containing the reserved address */
    chunk = get_mapped_region(rsv_addr);
    if (chunk == NULL)
        status = -ENXIO;
    if(status < 0); // why is this required -- Vikas KM
    if (status == 0) {
        chunk->b_reserved = false;
        *psize = chunk->region_size * PAGE_SIZE;
        /* NOTE: We do NOT coalesce free regions here.
         * Free regions are coalesced in get_region(), as it traverses
         *the whole mapping table
         */
    }
    OsalMutex_leave(dmm_lock, key);

    return status;
}

#ifdef DSP_DMM_DEBUG
int dmm_mem_map_dump(void)
{

    struct map_page *curNode = NULL;
    u32 i;
    u32 freemem = 0;
    u32 bigsize = 0;

    IArg key = 0;
    OsalMutex_enter(dmm_lock);

    if (p_virt_mapping_tbl != NULL) {
        for (i = 0; i < table_size; i +=
                p_virt_mapping_tbl[i].region_size) {
            curNode = p_virt_mapping_tbl + i;
            if (curNode->b_reserved == true)    {
                printf("RESERVED size = 0x%x, "
                    "Map size = 0x%x\n",
                    (curNode->region_size * PAGE_SIZE),
                    (curNode->b_mapped == false) ? 0 :
                    (curNode->mapped_size * PAGE_SIZE));
            } else {
                printf("UNRESERVED size = 0x%x\n",
                    (curNode->region_size * PAGE_SIZE));

                freemem += (curNode->region_size * PAGE_SIZE);
                if (curNode->region_size > bigsize)
                    bigsize = curNode->region_size;
            }
        }
    }
    printf("Total DSP VA FREE memory = %d Mbytes\n",
            freemem/(1024*1024));
    printf("Total DSP VA USED memory= %d Mbytes \n",
            (((table_size * PAGE_SIZE)-freemem))/(1024*1024));
    printf("DSP VA - Biggest FREE block = %d Mbytes \n\n",
            (bigsize*PAGE_SIZE/(1024*1024)));
    OsalMutex_leave(dmm_lock, key);

    return 0;
}
#endif

