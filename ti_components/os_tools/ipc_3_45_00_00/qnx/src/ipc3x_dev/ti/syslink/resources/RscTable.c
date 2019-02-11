/*
 *  @file       RscTable.c
 *
 *  @brief      Resource Table parser.
 *
 *  ============================================================================
 *
 *  Copyright (c) 2012-2016, Texas Instruments Incorporated
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


#if defined (__cplusplus)
extern "C" {
#endif

#include <ti/syslink/Std.h>
#include <ti/syslink/utils/List.h>
#include <ti/syslink/utils/Memory.h>
#include <ti/syslink/utils/Trace.h>
#include <RscTable.h>
#include <OsalKfile.h>
#include <_MultiProc.h>
#include <dload_api.h>
#include <ti/syslink/ProcMgr.h>
#include <Processor.h>
#include <Bitops.h>
#include <_MessageQCopyDefs.h>
#include <ProcDefs.h>
#include <sys/mman.h>

/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*
 * ZEROINIT_CHUNKS - Set to 1 to zero-init chunk allocations for
 *                   dynamically allocated remote core memory carveout
 *                   sections. Default is 0 to achieve better startup
 *                   performance.
 */
#define ZEROINIT_CHUNKS 0

#define RSC_TABLE_STRING ".resource_table"
#define DDR_MEM 0x80000000

typedef struct Carveout_Elem_tag {
    List_Elem  elem;
    UInt32     addr;
    UInt32     size;
} Carveout_Elem;

/*!
 *  @brief  RscTable Header
 */
typedef struct RscTable_Header_tag {
    UInt32 ver;
    UInt32 num;
    UInt32 reserved[2];
    UInt32 offset[];
} RscTable_Header;

/*!
 *  @brief  RscTable Entry
 */
typedef struct RscTable_MemEntry_tag {
    UInt32 type;
    UInt32 da;       /* Device Virtual Address */
    UInt32 pa;       /* Physical Address */
    UInt32 len;
    UInt32 flags;
    UInt32 reserved;
    Char   name[32];
} RscTable_MemEntry;

/*!
 *  @brief  RscTable Module state object
 */
typedef struct RscTable_ModuleObject_tag {
    RscTable_Handle       handles [MultiProc_MAXPROCESSORS];
    /*!< Array of Handles of RscTable instances */
} RscTable_ModuleObject;

/*!
 *  @brief  RscTable instance object
 */
struct RscTable_Object_tag {
    UInt16                 procId;
    /*!< Processor ID associated with this RscTable. */
    Char *                 fileName;
    /*!< File name associated with this RscTable. */
    Void *                 rscTable;
    /*!< Pointer to the resource table. */
    UInt32                 rscTableLen;
    /*!< Resource table length. */
    UInt32                 rscTableDA;
    /*!< Resource table device address. */
    Ipc_MemEntry           memEntries[IPC_MAX_MEMENTRIES];
    /*!< Memory Entries for the remote processor. */
    UInt32                 numMemEntries;
    /*!< Number of Memory Entries in the memEntries array. */
    struct fw_rsc_vdev_vring * vrings;
    /*!< Vring info for the remote processor. */
    UInt32                 numVrings;
    /*!< Number of vrings. */
    UInt32                 vringPa;
    /*!< PAddr of vrings space. */
    UInt32                 vringBufsPa;
    /*!< PAddr of vring bufs space. */
    struct fw_rsc_trace    trace;
    /*!< Trace info. */
    List_Handle            chunks;
    /*!< Allocated Chunks. */
} ;

/* Defines the RscTable_Object type. */
typedef struct RscTable_Object_tag RscTable_Object;

/* =============================================================================
 *  Globals
 * =============================================================================
 */
/*!
 *  @var    RscTable_state
 *
 *  @brief  RscTable state object variable
 */
#if !defined(IPC_BUILD_DEBUG)
static
#endif /* if !defined(IPC_BUILD_DEBUG) */
RscTable_ModuleObject RscTable_state;


/* =============================================================================
 *  APIs
 * =============================================================================
 */

RscTable_Handle
RscTable_alloc (Char * fileName, UInt16 procId)
{
    Int status = 0;
    RscTable_Object * obj = NULL;
    OsalKfile_Handle fileDesc  = NULL;
    UInt32 res_offs = 0, res_addr = 0, res_size = 0;
    List_Params params;

    // Check if this one is already registered
    if (RscTable_state.handles[procId]) {
        /* Not setting status here since this function does not return status.*/
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "RscTable_alloc",
                             RSCTABLE_E_INVALIDARG,
                             "Invalid procId specified");
        return NULL;
    }

    // Find the resource table in the file
    status = OsalKfile_open (fileName, "r", &fileDesc);
    if (status < 0) {
        /* Not setting status here since this function does not return status.*/
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "RscTable_alloc",
                             RSCTABLE_E_INVALIDARG,
                             "Invalid fileDesc specified");
        return NULL;
    }

    status = DLOAD_get_section_offset((LOADER_FILE_DESC *)fileDesc,
                                      RSC_TABLE_STRING, &res_offs, &res_size,
                                      &res_addr);
    if (status == TRUE) {
        obj = Memory_calloc(NULL, sizeof (RscTable_Object), 0, NULL);
        if (obj != NULL) {
            // Allocate memory to hold the table
            obj->rscTable = Memory_alloc(NULL, res_size, 0, NULL);
            if (obj->rscTable == NULL) {
                /* Not setting status here since this function does not return
                 * status.*/
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "RscTable_alloc",
                                     RSCTABLE_E_MEMORY,
                                     "Unable to allocate rscTable");
                Memory_free(NULL, obj, sizeof (RscTable_Object));
                obj = NULL;
            }
            else {
                obj->rscTableLen = res_size;
                status = OsalKfile_seek(fileDesc, res_offs,
                                        OsalKfile_Pos_SeekSet);
                if (status < 0) {
                    /* Not setting status here since this function does not
                     * return status.*/
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "RscTable_alloc",
                                         RSCTABLE_E_FAIL,
                                         "Unable to seek to rsctable in file");
                    Memory_free(NULL, obj->rscTable, res_size);
                    Memory_free(NULL, obj, sizeof (RscTable_Object));
                    obj = NULL;
                }
                else {
                    // Copy the table to the allocated memory
                    status = OsalKfile_read(fileDesc, (char *)obj->rscTable, 1,
                                            res_size);
                    if (status < 0) {
                        /* Not setting status here since this function does not
                         * return status.*/
                        GT_setFailureReason (curTrace,
                                             GT_4CLASS,
                                             "RscTable_alloc",
                                             RSCTABLE_E_FAIL,
                                             "Unable to read rsctable in file");
                        Memory_free(NULL, obj->rscTable, res_size);
                        Memory_free(NULL, obj, sizeof (RscTable_Object));
                        obj = NULL;
                    }
                    else {
                        obj->rscTableDA = res_addr;
                        List_Params_init(&params);
                        obj->chunks = List_create(&params);
                        if (obj->chunks == NULL) {
                            /* Not setting status here since this function does
                             * not return status.*/
                            GT_setFailureReason (curTrace,
                                                 GT_4CLASS,
                                                 "RscTable_alloc",
                                                 RSCTABLE_E_FAIL,
                                                 "Unable to create list");
                            Memory_free(NULL, obj->rscTable, res_size);
                            Memory_free(NULL, obj, sizeof (RscTable_Object));
                            obj = NULL;
                        }
                    }
                }
            }
        }
        else {
            /* Not setting status here since this function does not return
             * status.*/
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "RscTable_alloc",
                                 RSCTABLE_E_MEMORY,
                                 "Unable to allocate obj");
        }
    }
    else {
        /* Not setting status here since this function does not return status.*/
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "RscTable_alloc",
                             RSCTABLE_E_FAIL,
                             "Unable to find resource table in file");
    }

    OsalKfile_close(&fileDesc);

    // If successful, save coreId-handle pair for later access
    if (obj) {
        obj->procId = procId;
        RscTable_state.handles[procId] = (RscTable_Handle)obj;
    }

    return (RscTable_Handle)obj;
}

// allocate any addr
Int Chunk_allocate (RscTable_Object *obj, UInt32 size, UInt32 * pa)
{
    Int status = 0;
    List_Elem * elem = NULL;
    Void * da;
    long long paddr;
    UInt32 len;

    if (!pa || !obj || !obj->chunks) {
        status = RSCTABLE_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "Chunk_allocate",
                             status,
                             "Invalid arg passed");
        GT_3trace(curTrace, GT_4CLASS, "obj [0x%x] obj->chunks [0x%x] pa [0x%x]", obj, obj ? obj->chunks : NULL, pa);
    }
    else {
        // first try to allocate contiguous mem
        da = mmap64(NULL, size,
                    PROT_NOCACHE | PROT_READ | PROT_WRITE,
#if ZEROINIT_CHUNKS
                    MAP_ANON | MAP_PHYS | MAP_SHARED,
#else
                    MAP_ANON | MAP_PHYS | MAP_SHARED | MAP_NOINIT,
#endif
                    NOFD,
                    0);
        if (da == MAP_FAILED) {
            // TODO: try to allocate non-contigous mem then get the pages
            status = RSCTABLE_E_MEMORY;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Chunk_allocate",
                                 status,
                                 "Unable to allocate chunk");
        }
        else {
            /* Make sure the memory is contiguous */
            status = mem_offset64(da, NOFD, size, &paddr, &len);
            if (status || (len != size)) {
                munmap(da, size);
                status = RSCTABLE_E_MEMORY;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "Chunk_allocate",
                                     status,
                                     "mem_offset64 failed");
            }
            else {
                *pa = (UInt32)paddr;
                // save the memory so that it can be freed later
                elem = Memory_alloc(NULL, sizeof(Carveout_Elem), 0, NULL);
                if (elem == NULL) {
                    munmap(da, size);
                    status = RSCTABLE_E_MEMORY;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "Chunk_allocate",
                                         status,
                                         "Memory_alloc failed");
                }
                else {
                    ((Carveout_Elem *)elem)->addr = (UInt32)da;
                    ((Carveout_Elem *)elem)->size = size;
                    List_put(obj->chunks, elem);
                }
            }
        }
    }
    return status;
}

Int
RscTable_process (UInt16 procId, Bool tryAlloc, UInt32 * numBlocks,
    Processor_Handle procHandle, ProcMgr_BootMode bootMode)
{
    Int status = 0;
    Int ret = 0;
    RscTable_Object * obj = NULL;
    RscTable_Header * table = NULL;
    UInt i = 0, j = 0;
    UInt dmem_num = 0;
    struct fw_rsc_vdev *vdev = NULL;
    struct fw_rsc_vdev_vring * vring = NULL;
    UInt32 vr_size = 0;
#if !ZEROINIT_CHUNKS
    UInt32 vringVA = 0, vringSize = 0;
#endif

    // Find the table for this coreId, if not found, return an error
    if (procId >= MultiProc_MAXPROCESSORS || !RscTable_state.handles[procId]) {
        status = RSCTABLE_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "RscTable_process",
                             status,
                             "Invalid procId specified");
        return status;
    }

    obj = (RscTable_Object *)RscTable_state.handles[procId];
    table = (RscTable_Header *)obj->rscTable;

    obj->numMemEntries = 0;

    // TODO: Check the version
    printf("RscTable_process: RscTable version is [%d]\n", table->ver);

    // Process the table for this core, allocating carveout memory if necessary
    for (i = 0; i < table->num && !ret; i++) {
        RscTable_MemEntry * entry =
                (RscTable_MemEntry *)((UInt32)table + table->offset[i]);
        switch (entry->type) {
            case TYPE_CARVEOUT :
            {
                // TODO: need to allocate this mem from carveout
                struct fw_rsc_carveout * cout =
                    (struct fw_rsc_carveout *)entry;
                UInt32 pa = 0;

                if (bootMode == ProcMgr_BootMode_NoBoot) {
                    /* Lookup physical address of carveout from page table */
                    if (Processor_translateFromPte(procHandle,
                        &cout->pa, cout->da) != ProcMgr_S_SUCCESS) {
                        status = RSCTABLE_E_FAIL;
                        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "RscTable_process",
                             status,
                             "Failed to lookup address from page table");
                        ret = -1;
                    }
                }
                else {
                    if (cout->pa == 0) {
                        ret = Chunk_allocate (obj, cout->len, &pa);
                    }
                    if (!ret) {
                        cout->pa = pa;
                    }
                }

                if (ret == 0) {
                    if (obj->numMemEntries == IPC_MAX_MEMENTRIES) {
                        ret = -1;
                    }
                    else {
                        obj->memEntries[obj->numMemEntries].slaveVirtAddr =
                            cout->da;
                        obj->memEntries[obj->numMemEntries].masterPhysAddr =
                            cout->pa;
                        obj->memEntries[obj->numMemEntries].size =
                            cout->len;
                        obj->memEntries[obj->numMemEntries].map = TRUE;
                        obj->memEntries[obj->numMemEntries].mapMask =
                            ProcMgr_SLAVEVIRT;
                        obj->memEntries[obj->numMemEntries].isCached =
                            FALSE;
                        obj->memEntries[obj->numMemEntries].isValid = TRUE;
                        obj->numMemEntries++;
                    }
                }
                printf ("RscTable_process: carveout [%s] @ da [0x%08x] pa [0x%08x] len [0x%x]\n", cout->name, cout->da, cout->pa, cout->len);
                break;
            }
            case TYPE_DEVMEM :
            {
                // only care about mem in DDR for now
                struct fw_rsc_devmem * dmem = (struct fw_rsc_devmem *)entry;
                UInt32 pa = 0;

                if (dmem->pa >= DDR_MEM) {
                    // HACK: treat vring mem specially, vring is always the
                    //       first devmem entry, may change in future
                    if (dmem_num++ == 0) {
                        if (bootMode == ProcMgr_BootMode_NoBoot) {
                            /*
                             * Lookup physical address of vrings from page
                             * table
                             */
                            if (Processor_translateFromPte(procHandle,
                                &pa, dmem->da) != ProcMgr_S_SUCCESS) {
                                status = RSCTABLE_E_FAIL;
                                GT_setFailureReason (curTrace,
                                    GT_4CLASS,
                                    "RscTable_process",
                                    status,
                                    "Failed to lookup address from page table");
                                ret = -1;
                            }
                            obj->vringPa = pa;
                            obj->vringBufsPa = pa + vr_size;
                        }
                        else {
                            // memory should already be reserved for vring
                            if (obj->vringPa == 0) {
                                // vdev must have been defined first
                                GT_setFailureReason (curTrace,
                                                 GT_4CLASS,
                                                 "RscTable_process",
                                                 status,
                                                 "Vring Must be Defined First");

                                ret = -1;
                            }
                            else if (obj->vringPa != dmem->pa && (!tryAlloc)) {
                                // defined pa does not match allocated pa, and
                                // either the mmu is disabled or the platform has
                                // not given permission to allocate on our own
                                ret = -1;
                                GT_setFailureReason (curTrace,
                                                 GT_4CLASS,
                                                 "RscTable_process",
                                                 status,
                                                 "Vring PA Mis-match");

                                GT_2trace (curTrace, GT_4CLASS,
                                       "vringPa is 0x%x, dmem->pa is 0x%x",
                                       obj->vringPa, dmem->pa);
                            }
                        }
                        if (ret == 0) {
#if !ZEROINIT_CHUNKS
                            /* Map the phys mem to local */
                            vringVA = (UInt32)mmap_device_io(vringSize,
                                obj->vringPa);
                            if (vringVA != MAP_DEVICE_FAILED) {
                                /* Zero-init the vring */
                                Memory_set((Ptr)vringVA, 0, vringSize);
                                munmap_device_io(vringVA, vringSize);
                            }
                            else {
                                GT_0trace(curTrace, GT_4CLASS,
                                    "RscTable_alloc: "
                                    "Warning - Unable to zero-init vring mem");
                            }
#endif
                            /*
                             * Override the vring 'da' field in resource table.
                             * This allows the slave to look it up when creating
                             * the VirtQueues
                             */
                            for (j = 0; j < vdev->num_of_vrings; j++) {
                                vring = (struct fw_rsc_vdev_vring *)
                                    ((UInt32)vdev + sizeof(*vdev) +
                                     (sizeof(*vring) * j));
                                vring->da = obj->vringPa + (j *
                                    vr_size / vdev->num_of_vrings);
                            }

                            /*
                             * Override the physical address provided by the
                             * entry with the physical locations of the vrings
                             * as allocated when we processed the vdev entry
                             * (or as allocated by external loader for late
                             * attach mode)
                             */
                            dmem->pa = obj->vringPa;
                        }
                    }
                }
                if (!ret) {
                    if (obj->numMemEntries == IPC_MAX_MEMENTRIES) {
                        ret = -1;
                    }
                    else {
                        obj->memEntries[obj->numMemEntries].slaveVirtAddr =
                                dmem->da;
                        obj->memEntries[obj->numMemEntries].masterPhysAddr =
                                dmem->pa;
                        obj->memEntries[obj->numMemEntries].size = dmem->len;
                        obj->memEntries[obj->numMemEntries].map = TRUE;
                        obj->memEntries[obj->numMemEntries].mapMask =
                            ProcMgr_SLAVEVIRT;
                        obj->memEntries[obj->numMemEntries].isCached = FALSE;
                        obj->memEntries[obj->numMemEntries].isValid = TRUE;
                        obj->numMemEntries++;
                    }
                }

                // TODO: need to make sure this mem exists/is set aside, or allocate it
                printf ("RscTable_process: devmem [%s] @ da [0x%08x] pa [0x%08x] len [0x%x]\n", dmem->name, dmem->da, dmem->pa, dmem->len);
                break;
            }
            case TYPE_TRACE :
            {
                // TODO: save da for future use
                struct fw_rsc_trace * trace = (struct fw_rsc_trace *)entry;
                Memory_copy(&obj->trace, trace, sizeof(*trace));
                printf ("RscTable_process: trace [%s] @ da [0x%08x] len [0x%x]\n", trace->name, trace->da, trace->len);
                break;
            }
            case TYPE_VDEV :
            {
                // TODO: save vring info for future use
                UInt32 vr_bufs_size = 0;
                UInt32 pa = 0;

                vdev = (struct fw_rsc_vdev *)entry;
                obj->numVrings = vdev->num_of_vrings;
                obj->vrings = Memory_alloc(NULL,
                                           sizeof (*vring) * obj->numVrings, 0,
                                           NULL);
                if (!obj->vrings)
                    ret = -1;
                for (j = 0; j < vdev->num_of_vrings && !ret; j++) {
                    vring = (struct fw_rsc_vdev_vring *)
                                ((UInt32)vdev + sizeof(*vdev) +
                                 (sizeof(*vring) * j));
                    /*
                     * Making a copy of original vring, given obj->vrings[j].da
                     * is used as slave virtual address in RscTable_getInfo(),
                     * and that is what the original vring definition contains.
                     */
                    Memory_copy (&obj->vrings[j], vring, sizeof (*vring));
                    printf ("RscTable_process: vring [%d] @ [0x%08x]\n",
                            vring->num, vring->da);
                    // Hack, we know this is the size alignment
                    if (vring->num != MessageQCopy_NUMBUFS ||
                        vring->align != MessageQCopy_VRINGALIGN) {
                        printf ("RscTable_process: warning size mis-match!\n");
                        ret = -1;
                    }
                    vr_size += ROUND_UP(MessageQCopy_RINGSIZE, 0x4000);
                    vr_bufs_size += (vring->num) * RPMSG_BUF_SIZE;
                }
                if ((!ret) && (bootMode != ProcMgr_BootMode_NoBoot)) {
                    // HACK: round up to multiple of 1MB, because we know this
                    //       is the size of the remote entry
                    ret = Chunk_allocate(obj,
                        ROUND_UP(vr_size + vr_bufs_size, 0x100000),
                        &pa);
                }

                if (!ret) {
#if !ZEROINIT_CHUNKS
                    vringSize = vr_size + vr_bufs_size;
#endif
                    if (bootMode != ProcMgr_BootMode_NoBoot) {
                        obj->vringPa = pa;
                        obj->vringBufsPa = pa + vr_size;
                    }
                }
                else if (obj->vrings) {
                    Memory_free (NULL, obj->vrings,
                                 sizeof(*vring) * obj->numVrings);
                    obj->vrings = NULL;
                }

                break;
            }
            default :
                break;
        }
    }

    if (ret) {
        status = RSCTABLE_E_FAIL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "RscTable_process",
                             status,
                             "Failure happened in processing table");
        if (obj->vrings)
            Memory_free(NULL, obj->vrings,
                        sizeof(*obj->vrings) * obj->numVrings);
        obj->vrings = NULL;
        obj->numMemEntries = 0;
    }
    *numBlocks = obj->numMemEntries;

    return status;
}

Int
RscTable_getMemEntries (UInt16 procId, Ipc_MemEntry *memEntries,
                        UInt32 * numMemEntries)
{
    Int status = 0;
    RscTable_Object *obj = NULL;

    // Find the table for this procId, if not found, return an error
    if (procId >= MultiProc_MAXPROCESSORS || !RscTable_state.handles[procId]) {
        status = RSCTABLE_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "RscTable_getMemEntries",
                             status,
                             "Invalid ProcId specified");
        return status;
    }

    obj = (RscTable_Object *)RscTable_state.handles[procId];

    if (obj->memEntries && obj->numMemEntries &&
        *numMemEntries >= obj->numMemEntries) {
        *numMemEntries = obj->numMemEntries;
        Memory_copy(memEntries, obj->memEntries,
                    sizeof(*memEntries) * obj->numMemEntries);
    }
    else {
        status = RSCTABLE_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "RscTable_getMemEntries",
                             status,
                             "Invalid num of memEntries or memEntries is NULL");
    }

    return status;
}

Int
RscTable_getInfo (UInt16 procId, UInt32 type, UInt32 extra, UInt32 * da,
                  UInt32 *pa, UInt32 * len)
{
    Int status = 0;
    RscTable_Object *obj = NULL;

    // Find the table for this procId, if not found, return an error
    if (procId >= MultiProc_MAXPROCESSORS || !RscTable_state.handles[procId]) {
        status = RSCTABLE_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "RscTable_getInfo",
                             status,
                             "Invalid procId specified");
        return status;
    }

    obj = (RscTable_Object *)RscTable_state.handles[procId];

    if (type == TYPE_TRACE) {
        if (da && len) {
            *da = obj->trace.da;
            *len = obj->trace.len;
        }
        else {
            status = RSCTABLE_E_INVALIDARG;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "RscTable_getInfo",
                                 status,
                                 "Invalid pointer passed");
        }
    }
    else if (type == TYPE_VDEV) {
        if (extra == 0 && len) {
            *len = obj->numVrings;
        }
        else if (extra < obj->numVrings && da) {
            *da = obj->vrings[extra-1].da;
        }
        else {
            status = RSCTABLE_E_INVALIDARG;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "RscTable_getInfo",
                                 status,
                                 "Invalid pointer passed");
        }
    }
    else {
        // type not supported
        status = -1;
    }

    return status;
    // Retrieve the info for a certain resource type (ex. Vring info)
}

Int
RscTable_update (UInt16 procId, ProcMgr_Handle procHandle)
{
    // Updates the table to physical memory so that phys addrs are available to
    // the remote cores.  This should be called only after loading the remote
    // cores.
    Int status = 0;
    RscTable_Object *obj = NULL;
    UInt32 rscTableVA = 0, rscTablePA = 0;

    // Find the table for this procId, if not found, return an error
    if (procId >= MultiProc_MAXPROCESSORS || !RscTable_state.handles[procId]) {
        status = RSCTABLE_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "RscTable_update",
                             status,
                             "Invalid ProcId specified");
        return status;
    }

    obj = (RscTable_Object *)RscTable_state.handles[procId];

    status = ProcMgr_translateAddr(procHandle, (Ptr *)&rscTablePA,
                                   ProcMgr_AddrType_MasterPhys,
                                   (Ptr)obj->rscTableDA,
                                   ProcMgr_AddrType_SlaveVirt);
    if (status < 0) {
        status = RSCTABLE_E_FAIL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "RscTable_update",
                             status,
                             "Unable to get the Master PA for RscTable");
    }
    else {
        /* Map the phys mem to local */
        rscTableVA = (UInt32)mmap_device_io(obj->rscTableLen, rscTablePA);
        if (rscTableVA != MAP_DEVICE_FAILED) {
            /* Copy the updated table to the memory */
            Memory_copy((Ptr)rscTableVA, obj->rscTable, obj->rscTableLen);
            munmap_device_io(rscTableVA, obj->rscTableLen);
        }
        else {
            status = RSCTABLE_E_FAIL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "RscTable_update",
                                 status,
                                 "Unable to map memory");
        }
    }

    return status;
}

Int
RscTable_free (RscTable_Handle * handle)
{
    Int status = 0;
    RscTable_Object * obj = NULL;
    Int i = 0;
    List_Elem * elem;

    // Remove resource table from coreId-Handle pair list
    if (handle && *handle) {
        // sanity check
        for (i = 0; i < MultiProc_MAXPROCESSORS; i++) {
            if (RscTable_state.handles[i] == *handle)
                break;
        }
        if (i < MultiProc_MAXPROCESSORS) {
            obj = (RscTable_Object *)(*handle);
            // Additional sanity check
            if (obj->procId == i) {
                // Free vrings, memEntries, etc.
                if (obj->chunks) {
                    while ((elem = List_get(obj->chunks))) {
                        Carveout_Elem * co_elem = (Carveout_Elem *)elem;
                        munmap((Void *)co_elem->addr, co_elem->size);
                        Memory_free(NULL, co_elem, sizeof(Carveout_Elem));
                    }
                    List_delete(&obj->chunks);
                    obj->chunks = NULL;
                }
                if (obj->vrings)
                    Memory_free(NULL, obj->vrings,
                                sizeof(*obj->vrings) * obj->numVrings);
                obj->vrings = NULL;
                obj->numMemEntries = 0;

                if (obj->rscTable)
                    Memory_free(NULL, obj->rscTable, obj->rscTableLen);
                obj->rscTableDA = 0;
                Memory_free(NULL, obj, sizeof (RscTable_Object));
                *handle = NULL;
                RscTable_state.handles[i] = NULL;
            }
        }
        else {
            status = RSCTABLE_E_INVALIDARG;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "RscTable_free",
                                 status,
                                 "Invalid handle passed");
        }
    }
    else {
        status = RSCTABLE_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "RscTable_free",
                             status,
                             "Invalid handle passed");
    }

    return status;
}

Int RscTable_setStatus(UInt16 procId, UInt32 value)
{
    Int i;
    Int status = 0;

    RscTable_Object * obj = (RscTable_Object *)RscTable_state.handles[procId];
    RscTable_Header * table = (RscTable_Header *)obj->rscTable;

    /* Look for the vdev entry and update the status */
    for (i = 0; i < table->num; i++) {
        RscTable_MemEntry * entry =
                (RscTable_MemEntry *)((UInt32)table + table->offset[i]);
        if (entry->type == TYPE_VDEV) {
            struct fw_rsc_vdev *vdev = (struct fw_rsc_vdev *)entry;
            vdev->status = value;
            break;
        }
    }

    if (i == table->num) {
        status = RSCTABLE_E_FAIL;
    }

    return status;
}

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
