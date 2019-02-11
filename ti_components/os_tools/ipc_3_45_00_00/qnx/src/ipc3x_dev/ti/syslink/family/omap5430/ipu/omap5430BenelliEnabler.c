/*
 *  @file  omap5430BenelliEnabler.c
 *
 *  @brief  MMU programming module
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2010-2015, Texas Instruments Incorporated
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

#include <errno.h>
#include <unistd.h>
#include <ti/syslink/Std.h>

/* OSAL and utils headers */
#include <ti/syslink/utils/List.h>
#include <ti/syslink/utils/Trace.h>
#include <ti/syslink/utils/OsalPrint.h>

/* Module level headers */
#include <OsalDrv.h>
#include <_ProcDefs.h>
#include <Processor.h>
#include <hw/inout.h>
#include <sys/mman.h>

#include <hw_defs.h>
#include <hw_mmu.h>
#include <OMAP5430BenelliHal.h>
#include <OMAP5430BenelliHalMmu.h>
#include <OMAP5430BenelliPhyShmem.h>
#include <OMAP5430BenelliEnabler.h>
#include <stdbool.h>
#include <stdint.h>

#define MMU_REGS_SIZE (sizeof(OMAP5430Benelli_MMURegs) / sizeof (UInt32))
static UInt32 mmu_regs[MMU_REGS_SIZE];


#define PAGE_SIZE 0x1000
static UInt32 nr_tlbs = 0;
#define NR_TLBS_MAX 32
struct iotlb_entry ipu_tlbs[NR_TLBS_MAX];
//struct iotlb_entry dsp_tlbs[NR_TLBS_MAX];

/* Attributes of L2 page tables for DSP MMU.*/
struct page_info {
    /* Number of valid PTEs in the L2 PT*/
    UInt32 num_entries;
};


/* Attributes used to manage the DSP MMU page tables */
struct pg_table_attrs {
    struct sync_cs_object *hcs_object;/* Critical section object handle */
    UInt32 l1_base_pa; /* Physical address of the L1 PT */
    UInt32 l1_base_va; /* Virtual  address of the L1 PT */
    UInt32 l1_size; /* Size of the L1 PT */
    UInt32 l1_tbl_alloc_pa;
    /* Physical address of Allocated mem for L1 table. May not be aligned */
    UInt32 l1_tbl_alloc_va;
    /* Virtual address of Allocated mem for L1 table. May not be aligned */
    UInt32 l1_tbl_alloc_sz;
    /* Size of consistent memory allocated for L1 table.
     * May not be aligned */
    UInt32 l2_base_pa;        /* Physical address of the L2 PT */
    UInt32 l2_base_va;        /* Virtual  address of the L2 PT */
    UInt32 l2_size;        /* Size of the L2 PT */
    UInt32 l2_tbl_alloc_pa;
    /* Physical address of Allocated mem for L2 table. May not be aligned */
    UInt32 l2_tbl_alloc_va;
    /* Virtual address of Allocated mem for L2 table. May not be aligned */
    UInt32 ls_tbl_alloc_sz;
    /* Size of consistent memory allocated for L2 table.
     * May not be aligned */
    UInt32 l2_num_pages;    /* Number of allocated L2 PT */
    struct page_info *pg_info;
};


static struct pg_table_attrs *p_pt_attrs = NULL;
static struct pg_table_attrs *tesla_p_pt_attrs = NULL;

enum pagetype {
    SECTION = 0,
    LARGE_PAGE = 1,
    SMALL_PAGE = 2,
    SUPER_SECTION  = 3
};

static UInt32 shm_phys_addr;
static UInt32 shm_phys_addr_dsp;

#define INREG32(x) in32((uintptr_t)x)
#define OUTREG32(x, y) out32((uintptr_t)x, y)
#define SIZE 0x4

static UInt32 iotlb_dump_cr (struct cr_regs *cr, char *buf);
static Int load_iotlb_entry (OMAP5430BENELLI_HalObject * halObject,
                             struct iotlb_entry *e);
static Int iotlb_cr_valid (struct cr_regs *cr);

static Int benelli_mem_map (OMAP5430BENELLI_HalObject * halObject,
                            UInt32 mpu_addr, UInt32 ul_virt_addr,
                            UInt32 num_bytes, UInt32 map_attr);
static Int benelli_mem_unmap (OMAP5430BENELLI_HalObject * halObject, UInt32 da,
                              UInt32 num_bytes);


static Void iotlb_cr_to_e (struct cr_regs *cr, struct iotlb_entry *e)
{
    e->da       = cr->cam & MMU_CAM_VATAG_MASK;
    e->pa       = cr->ram & MMU_RAM_PADDR_MASK;
    e->valid    = cr->cam & MMU_CAM_V;
    e->prsvd    = cr->cam & MMU_CAM_P;
    e->pgsz     = cr->cam & MMU_CAM_PGSZ_MASK;
    e->endian   = cr->ram & MMU_RAM_ENDIAN_MASK;
    e->elsz     = cr->ram & MMU_RAM_ELSZ_MASK;
    e->mixed    = cr->ram & MMU_RAM_MIXED;
}

static Void iotlb_getLock (OMAP5430BENELLI_HalObject * halObject,
                           struct iotlb_lock *l)
{
    ULONG reg;
    OMAP5430Benelli_MMURegs * mmuRegs =
                                  (OMAP5430Benelli_MMURegs *)halObject->mmuBase;

    reg = INREG32(&mmuRegs->LOCK);
    l->base = MMU_LOCK_BASE(reg);
    l->vict = MMU_LOCK_VICT(reg);
}

static Void iotlb_setLock (OMAP5430BENELLI_HalObject * halObject,
                           struct iotlb_lock *l)
{
    ULONG reg;
    OMAP5430Benelli_MMURegs * mmuRegs =
                                  (OMAP5430Benelli_MMURegs *)halObject->mmuBase;

    reg = (l->base << MMU_LOCK_BASE_SHIFT);
    reg |= (l->vict << MMU_LOCK_VICT_SHIFT);
    OUTREG32(&mmuRegs->LOCK, reg);
}

static void omap5_tlb_read_cr (OMAP5430BENELLI_HalObject * halObject,
                               struct cr_regs *cr)
{
    OMAP5430Benelli_MMURegs * mmuRegs =
                                  (OMAP5430Benelli_MMURegs *)halObject->mmuBase;

    cr->cam = INREG32(&mmuRegs->READ_CAM);
    cr->ram = INREG32(&mmuRegs->READ_RAM);
}

/* only used for iotlb iteration in for-loop */
static struct cr_regs __iotlb_read_cr (OMAP5430BENELLI_HalObject * halObject,
                                       int n)
{
     struct cr_regs cr;
     struct iotlb_lock l;
     iotlb_getLock(halObject, &l);
     l.vict = n;
     iotlb_setLock(halObject, &l);
     omap5_tlb_read_cr(halObject, &cr);
     return cr;
}

#define for_each_iotlb_cr(n, __i, cr)                \
    for (__i = 0;                            \
         (__i < (n)) && (cr = __iotlb_read_cr(halObject, __i), TRUE);    \
         __i++)

static Int save_tlbs (OMAP5430BENELLI_HalObject * halObject, UINT32 procId)
{
    Int i =0;
    struct cr_regs cr_tmp;
    struct iotlb_lock l;

    iotlb_getLock(halObject, &l);

    nr_tlbs = l.base;
#ifdef IPC_SYSBIOS_SMP
    if (procId == PROCTYPE_IPU0)
#else
    if (procId == PROCTYPE_IPU0 || procId == PROCTYPE_IPU1)
#endif
    {
        for_each_iotlb_cr(nr_tlbs, i, cr_tmp) {
            iotlb_cr_to_e(&cr_tmp, &ipu_tlbs[i]);
        }
    }
    //else if (procId == PROCTYPE_DSP) {
            //TODO: Add along with the DSP support.
    //}
    else {
        GT_setFailureReason(curTrace,GT_2CLASS,"save_tlbs",
                            EINVAL, "Invalid Processor Id");
        return -EINVAL;
    }

    return 0;

}

static Int restore_tlbs (OMAP5430BENELLI_HalObject * halObject, UInt32 procId)
{
    Int i = 0;
    Int status = -1;
    struct iotlb_lock save;

    /* Reset the base and victim values */
    save.base = 0;
    save.vict = 0;
    iotlb_setLock(halObject, &save);

#ifdef IPC_SYSBIOS_SMP
    if (procId == PROCTYPE_IPU0)
#else
    if (procId == PROCTYPE_IPU0 || procId == PROCTYPE_IPU1)
#endif
    {
        for (i = 0; i < nr_tlbs; i++) {
            status = load_iotlb_entry(halObject, &ipu_tlbs[i]);
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "restore_tlbs",
                                     status,
                                     "Error restoring the tlbs");
                goto err;
            }
        }
    }
    //else if (procId == PROCTYPE_DSP) {
        //TODO: Add along with the DSP support.
    //}
    else {
        status = -EINVAL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "restore_tlbs",
                             status,
                             "Invalid ProcId");
        goto err;
    }

    return 0;

err:
    return status;
}

static Int save_mmu_regs (OMAP5430BENELLI_HalObject * halObject, UInt32 procId)
{
    UInt32 i = 0;

    if (halObject == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "save_mmu_regs",
                             -ENOMEM,
                             "halObject is NULL");
        return -ENOMEM;
    }

    if (halObject->mmuBase == 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "save_mmu_regs",
                             -ENOMEM,
                             "halObject->mmuBase is 0");
        return -ENOMEM;
    }

    for (i = 0; i < MMU_REGS_SIZE; i++) {
        mmu_regs[i] = INREG32(halObject->mmuBase + (i * 4));
    }

    return 0;
}

static Int restore_mmu_regs (OMAP5430BENELLI_HalObject * halObject,
                             UInt32 procId)
{
    UInt32 i = 0;

    if (halObject == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "restore_mmu_regs",
                             -ENOMEM,
                             "halObject is NULL");
        return -ENOMEM;
    }

    if (halObject->mmuBase == 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "restore_mmu_regs",
                             -ENOMEM,
                             "halObject->mmuBase is 0");
        return -ENOMEM;
    }

    for (i = 0; i < MMU_REGS_SIZE; i++) {
        OUTREG32(halObject->mmuBase + (i * 4), mmu_regs[i]);
    }

    return 0;
}

Int save_mmu_ctxt (OMAP5430BENELLI_HalObject * halObject, UInt32 procId)
{
    Int status = -1;

    status = save_mmu_regs(halObject, procId);
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "save_mmu_ctxt",
                             status,
                             "Unable to save MMU Regs");
        return status;
    }

    status = save_tlbs(halObject, procId);
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "save_mmu_ctxt",
                             status,
                             "Unable to save TLBs");
        return status;
    }
    return status;

}

Int restore_mmu_ctxt (OMAP5430BENELLI_HalObject * halObject, UInt32 procId)
{
    Int status = -1;

    status = restore_mmu_regs(halObject, procId);
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "restore_mmu_ctxt",
                             status,
                             "Unable to restore MMU Regs");
        return status;
    }

    status = restore_tlbs(halObject, procId);
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "restore_mmu_ctxt",
                             status,
                             "Unable to restore TLBS");
        return status;
    }

    return status;
}


 /*=========================================
 * Decides a TLB entry size
 *
 */
static Int get_mmu_entry_size (UInt32 pa, UInt32 size, enum pagetype *size_tlb,
                               UInt32 *entry_size)
{
    Int     status = 0;
    Bool    page_align_4kb  = false;
    Bool    page_align_64kb = false;
    Bool    page_align_1mb = false;
    Bool    page_align_16mb = false;
    UInt32  phys_addr = pa;


    /*  First check the page alignment*/
    if ((phys_addr % PAGE_SIZE_4KB)  == 0)
        page_align_4kb  = true;
    if ((phys_addr % PAGE_SIZE_64KB) == 0)
        page_align_64kb = true;
    if ((phys_addr % PAGE_SIZE_1MB)  == 0)
        page_align_1mb  = true;
    if ((phys_addr % PAGE_SIZE_16MB)  == 0)
        page_align_16mb  = true;

    if ((!page_align_64kb) && (!page_align_1mb)  && (!page_align_4kb)) {
        status = -EINVAL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "get_mmu_entry_size",
                             status,
                             "phys_addr is not properly aligned");
        goto error_exit;
    }

    /*  Now decide the entry size */
    if (size >= PAGE_SIZE_16MB) {
        if (page_align_16mb) {
            *size_tlb   = SUPER_SECTION;
            *entry_size = PAGE_SIZE_16MB;
        } else if (page_align_1mb) {
            *size_tlb   = SECTION;
            *entry_size = PAGE_SIZE_1MB;
        } else if (page_align_64kb) {
            *size_tlb   = LARGE_PAGE;
            *entry_size = PAGE_SIZE_64KB;
        } else if (page_align_4kb) {
            *size_tlb   = SMALL_PAGE;
            *entry_size = PAGE_SIZE_4KB;
        } else {
            status = -EINVAL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "get_mmu_entry_size",
                                 status,
                                 "size and alignment are invalid");
            goto error_exit;
        }
    } else if (size >= PAGE_SIZE_1MB && size < PAGE_SIZE_16MB) {
        if (page_align_1mb) {
            *size_tlb   = SECTION;
            *entry_size = PAGE_SIZE_1MB;
        } else if (page_align_64kb) {
            *size_tlb   = LARGE_PAGE;
            *entry_size = PAGE_SIZE_64KB;
        } else if (page_align_4kb) {
            *size_tlb   = SMALL_PAGE;
            *entry_size = PAGE_SIZE_4KB;
        } else {
            status = -EINVAL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "get_mmu_entry_size",
                                 status,
                                 "size and alignment are invalid");
            goto error_exit;
        }
    } else if (size > PAGE_SIZE_4KB && size < PAGE_SIZE_1MB) {
        if (page_align_64kb) {
            *size_tlb   = LARGE_PAGE;
            *entry_size = PAGE_SIZE_64KB;
        } else if (page_align_4kb) {
            *size_tlb   = SMALL_PAGE;
            *entry_size = PAGE_SIZE_4KB;
        } else {
            status = -EINVAL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "get_mmu_entry_size",
                                 status,
                                 "size and alignment are invalid");
            goto error_exit;
        }
    } else if (size == PAGE_SIZE_4KB) {
        if (page_align_4kb) {
            *size_tlb   = SMALL_PAGE;
            *entry_size = PAGE_SIZE_4KB;
        } else {
            status = -EINVAL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "get_mmu_entry_size",
                                 status,
                                 "size and alignment are invalid");
            goto error_exit;
        }
    } else {
        status = -EINVAL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "get_mmu_entry_size",
                             status,
                             "size is invalid");
        goto error_exit;
    }
    return 0;

error_exit:
    return status;
}


#if 0
/*=========================================
 * Add DSP MMU entries corresponding to given MPU-Physical address
 * and DSP-virtual address
 */
static Int add_dsp_mmu_entry (OMAP5430BENELLI_HalObject * halObject,
                              UInt32 *phys_addr, UInt32 *dsp_addr, UInt32 size)
{
    UInt32 mapped_size = 0;
    enum pagetype size_tlb = SECTION;
    UInt32 entry_size = 0;
    int status = 0;
    struct iotlb_entry tlb_entry;
    int retval = 0;

    while ((mapped_size < size) && (status == 0)) {
        status = get_mmu_entry_size(*phys_addr, (size - mapped_size),
                                    &size_tlb, &entry_size);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "add_dsp_mmu_entry",
                                 status,
                                 "get_mmu_entry_size failed");
            goto error_exit;
        }

        if (size_tlb == SUPER_SECTION)
            tlb_entry.pgsz = MMU_CAM_PGSZ_16M;

        else if (size_tlb == SECTION)
            tlb_entry.pgsz = MMU_CAM_PGSZ_1M;

        else if (size_tlb == LARGE_PAGE)
            tlb_entry.pgsz = MMU_CAM_PGSZ_64K;

        else if (size_tlb == SMALL_PAGE)
            tlb_entry.pgsz = MMU_CAM_PGSZ_4K;

        tlb_entry.elsz = MMU_RAM_ELSZ_16;
        tlb_entry.endian = MMU_RAM_ENDIAN_LITTLE;
        tlb_entry.mixed = MMU_RAM_MIXED;
        tlb_entry.prsvd = MMU_CAM_P;
        tlb_entry.valid = MMU_CAM_V;

        tlb_entry.da = *dsp_addr;
        tlb_entry.pa = *phys_addr;
        retval = load_iotlb_entry(halObject, &tlb_entry);
        if (retval < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "add_dsp_mmu_entry",
                                 retval,
                                 "load_iotlb_entry failed");
            goto error_exit;
        }
        mapped_size  += entry_size;
        *phys_addr   += entry_size;
        *dsp_addr   += entry_size;
    }

    return 0;

error_exit:
    printf("pte set failure retval = 0x%x, status = 0x%x \n",
                            retval, status);

    return retval;
}
#endif


static Int add_entry_ext (OMAP5430BENELLI_HalObject * halObject,
                          UInt32 *phys_addr, UInt32 *dsp_addr, UInt32 size)
{
    UInt32 mapped_size = 0;
    enum pagetype     size_tlb = SECTION;
    UInt32 entry_size = 0;
    Int status = 0;
    UInt32 page_size = HW_PAGE_SIZE_1MB;
    UInt32 flags = 0;

    flags = (DSP_MAPELEMSIZE32 | DSP_MAPLITTLEENDIAN |
                    DSP_MAPPHYSICALADDR);
    while ((mapped_size < size) && (status == 0)) {

        /*  get_mmu_entry_size fills the size_tlb and entry_size
        based on alignment and size of memory to map
        to DSP - size */
        status = get_mmu_entry_size (*phys_addr,
                                     (size - mapped_size),
                                     &size_tlb,
                                     &entry_size);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "add_entry_ext",
                                 status,
                                 "get_mmu_entry_size failed");
            break;
        }
        else {
            if (size_tlb == SUPER_SECTION)
                page_size = HW_PAGE_SIZE_16MB;
            else if (size_tlb == SECTION)
                page_size = HW_PAGE_SIZE_1MB;
            else if (size_tlb == LARGE_PAGE)
                page_size = HW_PAGE_SIZE_64KB;
            else if (size_tlb == SMALL_PAGE)
                page_size = HW_PAGE_SIZE_4KB;

            if (status == 0) {
                status = benelli_mem_map (halObject,
                                          *phys_addr,
                                          *dsp_addr,
                                          page_size,
                                          flags);
                if (status < 0) {
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "add_entry_ext",
                                         status,
                                         "benelli_mem_map failed");
                    break;
                }
                mapped_size  += entry_size;
                *phys_addr   += entry_size;
                *dsp_addr   += entry_size;
            }
        }
    }
    return status;
}

static Int __dump_tlb_entries (OMAP5430BENELLI_HalObject * halObject,
                               struct cr_regs *crs, int num)
{
    int i;
    struct iotlb_lock saved;
    struct cr_regs tmp;
    struct cr_regs *p = crs;

    iotlb_getLock(halObject, &saved);
    for_each_iotlb_cr(num, i, tmp) {
        if (!iotlb_cr_valid(&tmp))
            continue;
        *p++ = tmp;
    }
    iotlb_setLock(halObject, &saved);
    return  p - crs;
}

UInt32 get_BenelliVirtAdd(OMAP5430BENELLI_HalObject * halObject, UInt32 physAdd)
{
    int i, num;
    struct cr_regs *cr;
    struct cr_regs *p = NULL;
    //DWORD dwPhys;
    UInt32 lRetVal = 0;
    num = 32;
    if((halObject->procId != PROCTYPE_DSP) && (shm_phys_addr == 0))
        return 0;
    if((halObject->procId == PROCTYPE_DSP) && (shm_phys_addr_dsp == 0))
        return 0;
    cr = mmap(NULL,
              sizeof(struct cr_regs) * num,
              PROT_NOCACHE | PROT_READ | PROT_WRITE,
              MAP_ANON | MAP_PHYS | MAP_PRIVATE,
              NOFD,
              0);
    if (cr == MAP_FAILED)
    {
        return NULL;
    }

    memset(cr, 0, sizeof(struct cr_regs) * num);

    num = __dump_tlb_entries(halObject, cr, num);
    for (i = 0; i < num; i++)
    {
        p = cr + i;
        if(physAdd >= (p->ram & 0xFFFFF000) &&  physAdd < ((p + 1)->ram & 0xFFFFF000))
        {
            lRetVal = ((p->cam & 0xFFFFF000) + (physAdd - (p->ram & 0xFFFFF000)));
        }
    }
    munmap(cr, sizeof(struct cr_regs) * num);

    return lRetVal;
}


/**
 * dump_tlb_entries - dump cr arrays to given buffer
 * @obj:    target iommu
 * @buf:    output buffer
 **/
static UInt32 dump_tlb_entries (OMAP5430BENELLI_HalObject * halObject,
                                char *buf, UInt32 bytes)
{
    Int i, num;
    struct cr_regs *cr;
    Char *p = buf;

    num = bytes / sizeof(*cr);
    num = min(32, num);
    cr = mmap(NULL,
            sizeof(struct cr_regs) * num,
              PROT_NOCACHE | PROT_READ | PROT_WRITE,
              MAP_ANON | MAP_PHYS | MAP_PRIVATE,
              NOFD,
              0);
    if (!cr)
    {
        return NULL;

    }
    memset(cr, 0, sizeof(struct cr_regs) * num);

    num = __dump_tlb_entries(halObject, cr, num);
    for (i = 0; i < num; i++)
        p += iotlb_dump_cr(cr + i, p);
    munmap(cr, sizeof(struct cr_regs) * num);
    return p - buf;
}


static Void benelli_tlb_dump (OMAP5430BENELLI_HalObject * halObject)
{
    Char *p;

    p = mmap(NULL,
             1000,
             PROT_NOCACHE | PROT_READ | PROT_WRITE,
             MAP_ANON | MAP_PHYS | MAP_PRIVATE,
             NOFD,
             0);
    if (MAP_FAILED != p)
    {
        dump_tlb_entries(halObject, p, 1000);
        munmap(p, 1000);
    }

    return;
}


/*================================
 * Initialize the Benelli MMU.
 *===============================*/

static Int benelli_mmu_init (OMAP5430BENELLI_HalObject * halObject,
                             ProcMgr_AddrInfo * memEntries,
                             UInt32 numMemEntries)
{
    Int ret_val = 0;
    UInt32 phys_addr = 0;
    UInt32 i = 0;
    UInt32 virt_addr = 0;
    OMAP5430Benelli_MMURegs * mmuRegs = NULL;

    if (halObject == NULL) {
        ret_val = -ENOMEM;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "benelli_mmu_init",
                             ret_val,
                             "halObject is NULL");
        goto error_exit;
    }

    if (halObject->mmuBase == 0) {
        ret_val = -ENOMEM;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "benelli_mmu_init",
                             ret_val,
                             "halObject->mmuBase is 0");
        goto error_exit;
    }
    mmuRegs = (OMAP5430Benelli_MMURegs *)halObject->mmuBase;

    /*  Disable the MMU & TWL */
    hw_mmu_disable(halObject->mmuBase);
    hw_mmu_twl_disable(halObject->mmuBase);


    printf("  Programming Benelli memory regions\n");
    printf("=========================================\n");

    for (i = 0; i < numMemEntries; i++) {
        phys_addr = memEntries[i].addr[ProcMgr_AddrType_MasterPhys];
        if (phys_addr == (UInt32)(-1) || phys_addr == 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "benelli_mmu_init",
                                 ret_val,
                                 "Processor_translateAddr failed");
            goto error_exit;
        }
        printf( "VA = [0x%x] of size [0x%x] at PA = [0x%x]\n",
                memEntries[i].addr[ProcMgr_AddrType_SlaveVirt],
                memEntries[i].size,
                (unsigned int)phys_addr);

        /* OMAP5430 SDC code */
        /* Adjust below logic if using cacheable shared memory */
        shm_phys_addr = 1;
        virt_addr = memEntries[i].addr[ProcMgr_AddrType_SlaveVirt];

        ret_val = add_entry_ext(halObject, &phys_addr, &virt_addr,
                                (memEntries[i].size));
        if (ret_val < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "benelli_mmu_init",
                                 ret_val,
                                 "add_entry_ext failed");
            goto error_exit;
        }
    }

    /* Set the TTB to point to the L1 page table's physical address */
    OUTREG32(&mmuRegs->TTB, p_pt_attrs->l1_base_pa);

    /* Enable the TWL */
    hw_mmu_twl_enable(halObject->mmuBase);

    hw_mmu_enable(halObject->mmuBase);

    benelli_tlb_dump(halObject);
    return 0;
error_exit:
    return ret_val;
}

/****************************************************
*
*  Function which sets the TWL of the tesla
*
*
*****************************************************/

static Int tesla_set_twl (OMAP5430BENELLI_HalObject * halObject, Bool on)
{
   Int status = 0;
   OMAP5430Benelli_MMURegs * mmuRegs = NULL;
   ULONG reg;


   if (halObject == NULL) {
       status = -ENOMEM;
       GT_setFailureReason (curTrace,
                            GT_4CLASS,
                            "tesla_set_twl",
                            status,
                            "halObject is NULL");
   }
   else if (halObject->mmuBase == 0) {
       status = -ENOMEM;
       GT_setFailureReason (curTrace,
                            GT_4CLASS,
                            "tesla_set_twl",
                            status,
                            "halObject->mmuBase is NULL");
   }
   else {
       mmuRegs = (OMAP5430Benelli_MMURegs *)halObject->mmuBase;

       /* Setting MMU to Smart Idle Mode */
       reg = INREG32(&mmuRegs->SYSCONFIG);
       reg &= ~MMU_SYS_IDLE_MASK;
       reg |= (MMU_SYS_IDLE_SMART | MMU_SYS_AUTOIDLE);
       OUTREG32(&mmuRegs->SYSCONFIG, reg);

       /* Enabling MMU */
       reg =  INREG32(&mmuRegs->CNTL);

       if (on)
           OUTREG32(&mmuRegs->IRQENABLE, MMU_IRQ_TWL_MASK);
       else
           OUTREG32(&mmuRegs->IRQENABLE, MMU_IRQ_TLB_MISS_MASK);

       reg &= ~MMU_CNTL_MASK;
       if (on)
           reg |= (MMU_CNTL_MMU_EN | MMU_CNTL_TWL_EN);
       else
           reg |= (MMU_CNTL_MMU_EN);

       OUTREG32(&mmuRegs->CNTL, reg);
   }

   return status;
}

static Int tesla_mmu_init(OMAP5430BENELLI_HalObject * halObject,
                          ProcMgr_AddrInfo * memEntries,
                          UInt32 numMemEntries)
{
    Int ret_val = 0;
    UInt32 phys_addr = 0;
    UInt32 i = 0;
    UInt32 virt_addr = 0;
    UInt32 reg;
    OMAP5430Benelli_MMURegs * mmuRegs = NULL;

    if (halObject == NULL) {
        ret_val = -ENOMEM;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "tesla_mmu_init",
                             ret_val,
                             "halObject is NULL");
        goto error_exit;
    }
    if (halObject->mmuBase == 0) {
        ret_val = -ENOMEM;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "tesla_mmu_init",
                             ret_val,
                             "halObject->mmuBase is 0");
        goto error_exit;
    }
    mmuRegs = (OMAP5430Benelli_MMURegs *)halObject->mmuBase;

    /*  Disable the MMU & TWL */
    hw_mmu_disable(halObject->mmuBase);
    hw_mmu_twl_disable(halObject->mmuBase);

    printf("  Programming Tesla memory regions\n");
    printf("=========================================\n");

    for (i = 0; i < numMemEntries; i++) {
        phys_addr = memEntries[i].addr[ProcMgr_AddrType_MasterPhys];
        printf( "VA = [0x%x] of size [0x%x] at PA = [0x%x]\n",
                (unsigned int)memEntries[i].addr[ProcMgr_AddrType_SlaveVirt],
                (unsigned int)memEntries[i].size,
                (unsigned int)phys_addr);

        shm_phys_addr_dsp = 1;

        virt_addr = memEntries[i].addr[ProcMgr_AddrType_SlaveVirt];
        ret_val = add_entry_ext(halObject, &phys_addr, &virt_addr,
                                (memEntries[i].size));

        if (ret_val < 0)
            goto error_exit;
    }

    /* Set the TTB to point to the L1 page table's physical address */
    OUTREG32(&mmuRegs->TTB, tesla_p_pt_attrs->l1_base_pa);
    /* Enable the TWL */
    hw_mmu_twl_enable(halObject->mmuBase);
    hw_mmu_enable(halObject->mmuBase);

    //Set the SYSCONFIG
    reg = INREG32(halObject->mmuBase + 0x10);
    reg&=0xFFFFFFEF;
    reg|=0x11;
    OUTREG32(halObject->mmuBase+0x10, reg);
    benelli_tlb_dump(halObject);
    return 0;
    error_exit:
    return ret_val;
}

static Int init_tesla_page_attributes()
{

    UInt32 pg_tbl_pa = 0;
    off64_t offset = 0;
    UInt32 pg_tbl_va = 0;
    UInt32 align_size = 0;
    UInt32 len = 0;
    UInt32 l1_size = 0x10000;
    UInt32 ls_num_of_pages = 128;
    int status = 0;

    tesla_p_pt_attrs = Memory_alloc (NULL, sizeof(struct pg_table_attrs), 0, NULL);
    if (tesla_p_pt_attrs)
        Memory_set (tesla_p_pt_attrs, 0, sizeof(struct pg_table_attrs));
    else {
        status = -ENOMEM;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "init_tesla_page_attributes",
                             status,
                             "Memory_alloc failed");
        goto error_exit;
    }

    tesla_p_pt_attrs->l1_size = l1_size;
    align_size = tesla_p_pt_attrs->l1_size;
    tesla_p_pt_attrs->l1_tbl_alloc_sz = 0x100000;
    /* Align sizes are expected to be power of 2 */
    /* we like to get aligned on L1 table size */
    pg_tbl_va = (UInt32) mmap64 (NULL,
                                 tesla_p_pt_attrs->l1_tbl_alloc_sz,
                                 PROT_NOCACHE | PROT_READ | PROT_WRITE,
                                 MAP_ANON | MAP_PHYS | MAP_PRIVATE,
                                 NOFD,
                                 0x0);
    if (pg_tbl_va == (UInt32)MAP_FAILED) {
        pg_tbl_va = 0;
        status = -ENOMEM;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "init_tesla_page_attributes",
                             status,
                             "mmap64 failed");
        goto error_exit;
    }
    else {
        /* Make sure the memory is contiguous */
        status = mem_offset64 ((void *)pg_tbl_va, NOFD,
                               tesla_p_pt_attrs->l1_tbl_alloc_sz, &offset, &len);
        pg_tbl_pa = (UInt32)offset;
        if (len != tesla_p_pt_attrs->l1_tbl_alloc_sz) {
            status = -ENOMEM;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "init_tesla_page_attributes",
                                 status,
                                 "phys mem is not contiguous");
        }
        if (status != 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "init_tesla_page_attributes",
                                 status,
                                 "mem_offset64 failed");
            goto error_exit;
        }
    }
    /* Check if the PA is aligned for us */
    if ((pg_tbl_pa) & (align_size-1)) {
        /* PA not aligned to page table size ,*/
        /* try with more allocation and align */
        munmap((void *)pg_tbl_va, tesla_p_pt_attrs->l1_tbl_alloc_sz);
        tesla_p_pt_attrs->l1_tbl_alloc_sz = tesla_p_pt_attrs->l1_tbl_alloc_sz*2;
        /* we like to get aligned on L1 table size */
        pg_tbl_va = (UInt32) mmap64 (NULL,
                                     tesla_p_pt_attrs->l1_tbl_alloc_sz,
                                     PROT_NOCACHE | PROT_READ | PROT_WRITE,
                                     MAP_ANON | MAP_PHYS | MAP_PRIVATE,
                                     NOFD,
                                     0);
        if (pg_tbl_va == (UInt32)MAP_FAILED) {
            pg_tbl_va = 0;
            status = -ENOMEM;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "init_tesla_page_attributes",
                                 status,
                                 "mmap64 failed");
            goto error_exit;
        }
        else {
            /* Make sure the memory is contiguous */
            status = mem_offset64 ((void *)pg_tbl_va, NOFD,
                                   tesla_p_pt_attrs->l1_tbl_alloc_sz, &offset, &len);
            pg_tbl_pa = (UInt32)offset;
            if (len != tesla_p_pt_attrs->l1_tbl_alloc_sz) {
                status = -ENOMEM;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "init_tesla_page_attributes",
                                     status,
                                     "phys mem is not contiguous");
            }
            if (status != 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "init_tesla_page_attributes",
                                     status,
                                     "mem_offset64 failed");
                goto error_exit;
            }
        }
        /* We should be able to get aligned table now */
        tesla_p_pt_attrs->l1_tbl_alloc_pa = pg_tbl_pa;
        tesla_p_pt_attrs->l1_tbl_alloc_va = pg_tbl_va;
        /* Align the PA to the next 'align'  boundary */
        tesla_p_pt_attrs->l1_base_pa = ((pg_tbl_pa) + (align_size-1)) &
                            (~(align_size-1));
        tesla_p_pt_attrs->l1_base_va = pg_tbl_va + (tesla_p_pt_attrs->l1_base_pa -
                                pg_tbl_pa);
    } else {
        /* We got aligned PA, cool */
        tesla_p_pt_attrs->l1_tbl_alloc_pa = pg_tbl_pa;
        tesla_p_pt_attrs->l1_tbl_alloc_va = pg_tbl_va;
        tesla_p_pt_attrs->l1_base_pa = pg_tbl_pa;
        tesla_p_pt_attrs->l1_base_va = pg_tbl_va;
    }

    if (tesla_p_pt_attrs->l1_base_va)
        memset((UInt8*)tesla_p_pt_attrs->l1_base_va, 0x00, tesla_p_pt_attrs->l1_size);
    tesla_p_pt_attrs->l2_num_pages = ls_num_of_pages;
    tesla_p_pt_attrs->l2_size = HW_MMU_COARSE_PAGE_SIZE * tesla_p_pt_attrs->l2_num_pages;
    align_size = 4; /* Make it UInt32 aligned  */
    /* we like to get aligned on L1 table size */
    pg_tbl_va = tesla_p_pt_attrs->l1_base_va + 0x80000;
    pg_tbl_pa = tesla_p_pt_attrs->l1_base_pa + 0x80000;
    tesla_p_pt_attrs->l2_tbl_alloc_pa = pg_tbl_pa;
    tesla_p_pt_attrs->l2_tbl_alloc_va = pg_tbl_va;
    tesla_p_pt_attrs->ls_tbl_alloc_sz = tesla_p_pt_attrs->l2_size;
    tesla_p_pt_attrs->l2_base_pa = pg_tbl_pa;
    tesla_p_pt_attrs->l2_base_va = pg_tbl_va;
    if (tesla_p_pt_attrs->l2_base_va)
        memset((UInt8*)tesla_p_pt_attrs->l2_base_va, 0x00, tesla_p_pt_attrs->l2_size);

    tesla_p_pt_attrs->pg_info = Memory_alloc(NULL, sizeof(struct page_info), 0, NULL);
    if (tesla_p_pt_attrs->pg_info)
        Memory_set (tesla_p_pt_attrs->pg_info, 0, sizeof(struct page_info));
    else {
        status = -ENOMEM;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "init_tesla_page_attributes",
                             status,
                             "Memory_alloc failed");
        goto error_exit;
    }

    return 0;

error_exit:
    if (tesla_p_pt_attrs) {
        if (tesla_p_pt_attrs->pg_info)
            Memory_free (NULL, tesla_p_pt_attrs->pg_info, sizeof(struct page_info));
        if (tesla_p_pt_attrs->l1_tbl_alloc_va) {
            munmap ((void *)tesla_p_pt_attrs->l1_tbl_alloc_va,
                    tesla_p_pt_attrs->l1_tbl_alloc_sz);
        }
        Memory_free (NULL, tesla_p_pt_attrs, sizeof(struct pg_table_attrs));
        tesla_p_pt_attrs = NULL;
    }

    return status;
}

/****************************************************
*
*  Function which sets the TWL of the benelli
*
*
*****************************************************/

static Int benelli_set_twl (OMAP5430BENELLI_HalObject * halObject, Bool on)
{
    Int status = 0;
    OMAP5430Benelli_MMURegs * mmuRegs = NULL;
    ULONG reg;

    if (halObject == NULL) {
        status = -ENOMEM;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "benelli_set_twl",
                             status,
                             "halObject is NULL");
    }
    else if (halObject->mmuBase == 0) {
        status = -ENOMEM;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "benelli_set_twl",
                             status,
                             "halObject->mmuBase is NULL");
    }
    else {
        mmuRegs = (OMAP5430Benelli_MMURegs *)halObject->mmuBase;

        /* Setting MMU to Smart Idle Mode */
        reg = INREG32(&mmuRegs->SYSCONFIG);
        reg &= ~MMU_SYS_IDLE_MASK;
        reg |= (MMU_SYS_IDLE_SMART | MMU_SYS_AUTOIDLE);
        OUTREG32(&mmuRegs->SYSCONFIG, reg);

        /* Enabling MMU */
        reg =  INREG32(&mmuRegs->CNTL);

        if (on)
            OUTREG32(&mmuRegs->IRQENABLE, MMU_IRQ_TWL_MASK);
        else
            OUTREG32(&mmuRegs->IRQENABLE, MMU_IRQ_TLB_MISS_MASK);

        reg &= ~MMU_CNTL_MASK;
        if (on)
            reg |= (MMU_CNTL_MMU_EN | MMU_CNTL_TWL_EN);
        else
            reg |= (MMU_CNTL_MMU_EN);

        OUTREG32(&mmuRegs->CNTL, reg);
    }

    return status;
}


/*========================================
 * This sets up the Benelli processor MMU Page tables
 *
 */
static Int init_mmu_page_attribs (UInt32 l1_size,
                                  UInt32 l1_allign,
                                  UInt32 ls_num_of_pages)
{
    UInt32 pg_tbl_pa = 0;
    off64_t offset = 0;
    UInt32 pg_tbl_va = 0;
    UInt32 align_size = 0;
    UInt32 len = 0;
    int status = 0;

    p_pt_attrs = Memory_alloc (NULL, sizeof(struct pg_table_attrs), 0, NULL);
    if (p_pt_attrs)
        Memory_set (p_pt_attrs, 0, sizeof(struct pg_table_attrs));
    else {
        status = -ENOMEM;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "init_mmu_page_attribs",
                             status,
                             "Memory_alloc failed");
        goto error_exit;
    }

    p_pt_attrs->l1_size = l1_size;
    align_size = p_pt_attrs->l1_size;
    p_pt_attrs->l1_tbl_alloc_sz = 0x100000;
    /* Align sizes are expected to be power of 2 */
    /* we like to get aligned on L1 table size */
    pg_tbl_va = (UInt32) mmap64 (NULL,
                                 p_pt_attrs->l1_tbl_alloc_sz,
                                 PROT_NOCACHE | PROT_READ | PROT_WRITE,
                                 MAP_ANON | MAP_PHYS | MAP_PRIVATE,
                                 NOFD,
                                 0x0);
    if (pg_tbl_va == (UInt32)MAP_FAILED) {
        pg_tbl_va = 0;
        status = -ENOMEM;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "init_mmu_page_attribs",
                             status,
                             "mmap64 failed");
        goto error_exit;
    }
    else {
        /* Make sure the memory is contiguous */
        status = mem_offset64 ((void *)pg_tbl_va, NOFD,
                               p_pt_attrs->l1_tbl_alloc_sz, &offset, &len);
        pg_tbl_pa = (UInt32)offset;
        if (len != p_pt_attrs->l1_tbl_alloc_sz) {
            status = -ENOMEM;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "init_mmu_page_attribs",
                                 status,
                                 "phys mem is not contiguous");
        }
        if (status != 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "init_mmu_page_attribs",
                                 status,
                                 "mem_offset64 failed");
            goto error_exit;
        }
    }
    /* Check if the PA is aligned for us */
    if ((pg_tbl_pa) & (align_size-1)) {
        /* PA not aligned to page table size ,*/
        /* try with more allocation and align */
        munmap((void *)pg_tbl_va, p_pt_attrs->l1_tbl_alloc_sz);
        p_pt_attrs->l1_tbl_alloc_sz = p_pt_attrs->l1_tbl_alloc_sz*2;
        /* we like to get aligned on L1 table size */
        pg_tbl_va = (UInt32) mmap64 (NULL,
                                     p_pt_attrs->l1_tbl_alloc_sz,
                                     PROT_NOCACHE | PROT_READ | PROT_WRITE,
                                     MAP_ANON | MAP_PHYS | MAP_PRIVATE,
                                     NOFD,
                                     0);
        if (pg_tbl_va == (UInt32)MAP_FAILED) {
            pg_tbl_va = 0;
            status = -ENOMEM;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "init_mmu_page_attribs",
                                 status,
                                 "mmap64 failed");
            goto error_exit;
        }
        else {
            /* Make sure the memory is contiguous */
            status = mem_offset64 ((void *)pg_tbl_va, NOFD,
                                   p_pt_attrs->l1_tbl_alloc_sz, &offset, &len);
            pg_tbl_pa = (UInt32)offset;
            if (len != p_pt_attrs->l1_tbl_alloc_sz) {
                status = -ENOMEM;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "init_mmu_page_attribs",
                                     status,
                                     "phys mem is not contiguous");
            }
            if (status != 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "init_mmu_page_attribs",
                                     status,
                                     "mem_offset64 failed");
                goto error_exit;
            }
        }
        /* We should be able to get aligned table now */
        p_pt_attrs->l1_tbl_alloc_pa = pg_tbl_pa;
        p_pt_attrs->l1_tbl_alloc_va = pg_tbl_va;
        /* Align the PA to the next 'align'  boundary */
        p_pt_attrs->l1_base_pa = ((pg_tbl_pa) + (align_size-1)) &
                            (~(align_size-1));
        p_pt_attrs->l1_base_va = pg_tbl_va + (p_pt_attrs->l1_base_pa -
                                pg_tbl_pa);
    } else {
        /* We got aligned PA, cool */
        p_pt_attrs->l1_tbl_alloc_pa = pg_tbl_pa;
        p_pt_attrs->l1_tbl_alloc_va = pg_tbl_va;
        p_pt_attrs->l1_base_pa = pg_tbl_pa;
        p_pt_attrs->l1_base_va = pg_tbl_va;
    }

    if (p_pt_attrs->l1_base_va)
        memset((UInt8*)p_pt_attrs->l1_base_va, 0x00, p_pt_attrs->l1_size);
    p_pt_attrs->l2_num_pages = ls_num_of_pages;
    p_pt_attrs->l2_size = HW_MMU_COARSE_PAGE_SIZE * p_pt_attrs->l2_num_pages;
    align_size = 4; /* Make it UInt32 aligned  */
    /* we like to get aligned on L1 table size */
    pg_tbl_va = p_pt_attrs->l1_base_va + 0x80000;
    pg_tbl_pa = p_pt_attrs->l1_base_pa + 0x80000;
    p_pt_attrs->l2_tbl_alloc_pa = pg_tbl_pa;
    p_pt_attrs->l2_tbl_alloc_va = pg_tbl_va;
    p_pt_attrs->ls_tbl_alloc_sz = p_pt_attrs->l2_size;
    p_pt_attrs->l2_base_pa = pg_tbl_pa;
    p_pt_attrs->l2_base_va = pg_tbl_va;
    if (p_pt_attrs->l2_base_va)
        memset((UInt8*)p_pt_attrs->l2_base_va, 0x00, p_pt_attrs->l2_size);

    p_pt_attrs->pg_info = Memory_alloc(NULL, sizeof(struct page_info) * p_pt_attrs->l2_num_pages, 0, NULL);
    if (p_pt_attrs->pg_info)
        Memory_set (p_pt_attrs->pg_info, 0, sizeof(struct page_info) * p_pt_attrs->l2_num_pages);
    else {
        status = -ENOMEM;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "init_mmu_page_attribs",
                             status,
                             "Memory_alloc failed");
        goto error_exit;
    }
    return 0;

error_exit:
    if (p_pt_attrs) {
        if (p_pt_attrs->pg_info)
            Memory_free (NULL, p_pt_attrs->pg_info, sizeof(struct page_info) * p_pt_attrs->l2_num_pages);
        if (p_pt_attrs->l1_tbl_alloc_va) {
            munmap ((void *)p_pt_attrs->l1_tbl_alloc_va,
                    p_pt_attrs->l1_tbl_alloc_sz);
        }
        Memory_free (NULL, p_pt_attrs, sizeof(struct pg_table_attrs));
        p_pt_attrs = NULL;
    }

    return status;
}


/*========================================
 * This destroys the Benelli processor MMU Page tables
 *
 */
static Void deinit_mmu_page_attribs (Void)
{
    if (p_pt_attrs) {
        if (p_pt_attrs->pg_info)
            Memory_free (NULL, p_pt_attrs->pg_info, sizeof(struct page_info) * p_pt_attrs->l2_num_pages);
        if (p_pt_attrs->l1_tbl_alloc_va) {
            munmap ((void *)p_pt_attrs->l1_tbl_alloc_va,
                    p_pt_attrs->l1_tbl_alloc_sz);
        }
        Memory_free (NULL, p_pt_attrs, sizeof(struct pg_table_attrs));
        p_pt_attrs = NULL;
    }
}


/*========================================
 * This destroys the DSP MMU Page tables
 *
 */
static Void deinit_dsp_mmu_page_attribs(Void)
{
    if (tesla_p_pt_attrs) {
        if (tesla_p_pt_attrs->pg_info)
            Memory_free (NULL, tesla_p_pt_attrs->pg_info, sizeof(struct page_info));
        if (tesla_p_pt_attrs->l1_tbl_alloc_va) {
            munmap ((void *)tesla_p_pt_attrs->l1_tbl_alloc_va,
                    tesla_p_pt_attrs->l1_tbl_alloc_sz);
        }
        Memory_free (NULL, tesla_p_pt_attrs, sizeof(struct pg_table_attrs));
        tesla_p_pt_attrs = NULL;
    }
}


/*============================================
 * This function calculates PTE address (MPU virtual) to be updated
 *  It also manages the L2 page tables
 */
static Int pte_set (UInt32 pa, UInt32 va, UInt32 size,
                    struct hw_mmu_map_attrs_t *attrs, struct pg_table_attrs *pt_Table)
{
    UInt32 i;
    UInt32 pte_val;
    UInt32 pte_addr_l1;
    UInt32 pte_size;
    UInt32 pg_tbl_va; /* Base address of the PT that will be updated */
    UInt32 l1_base_va;
     /* Compiler warns that the next three variables might be used
     * uninitialized in this function. Doesn't seem so. Working around,
     * anyways.  */
    UInt32 l2_base_va = 0;
    UInt32 l2_base_pa = 0;
    UInt32 l2_page_num = 0;
    struct pg_table_attrs *pt = pt_Table;
    struct iotlb_entry    *mapAttrs;
    int status = 0;
    OMAP5430BENELLI_HalMmuEntryInfo setPteInfo;
    mapAttrs = Memory_alloc(0, sizeof(struct iotlb_entry), 0, NULL);

    l1_base_va = pt->l1_base_va;
    pg_tbl_va = l1_base_va;
    if ((size == HW_PAGE_SIZE_64KB) || (size == HW_PAGE_SIZE_4KB)) {
        /* Find whether the L1 PTE points to a valid L2 PT */
        pte_addr_l1 = hw_mmu_pte_addr_l1(l1_base_va, va);
        if (pte_addr_l1 <= (pt->l1_base_va + pt->l1_size)) {
            pte_val = *(UInt32 *)pte_addr_l1;
            pte_size = hw_mmu_pte_sizel1(pte_val);
        } else {
            return -EINVAL;
        }
        /* FIX ME */
        /* TODO: ADD synchronication element*/
        /*        sync_enter_cs(pt->hcs_object);*/
        if (pte_size == HW_MMU_COARSE_PAGE_SIZE) {
            /* Get the L2 PA from the L1 PTE, and find
             * corresponding L2 VA */
            l2_base_pa = hw_mmu_pte_coarsel1(pte_val);
            l2_base_va = l2_base_pa - pt->l2_base_pa +
            pt->l2_base_va;
            l2_page_num = (l2_base_pa - pt->l2_base_pa) /
                    HW_MMU_COARSE_PAGE_SIZE;
        } else if (pte_size == 0) {
            /* L1 PTE is invalid. Allocate a L2 PT and
             * point the L1 PTE to it */
            /* Find a free L2 PT. */
            for (i = 0; (i < pt->l2_num_pages) &&
                (pt->pg_info[i].num_entries != 0); i++)
                ;;
            if (i < pt->l2_num_pages) {
                l2_page_num = i;
                l2_base_pa = pt->l2_base_pa + (l2_page_num *
                       HW_MMU_COARSE_PAGE_SIZE);
                l2_base_va = pt->l2_base_va + (l2_page_num *
                       HW_MMU_COARSE_PAGE_SIZE);
                /* Endianness attributes are ignored for
                 * HW_MMU_COARSE_PAGE_SIZE */
                mapAttrs->endian = attrs->endianism;
                mapAttrs->mixed = attrs->mixedSize;
                mapAttrs->elsz= attrs->element_size;
                mapAttrs->da = va;
                mapAttrs->pa = pa;
                status = hw_mmu_pte_set(pg_tbl_va, l2_base_pa, va,
                                        HW_MMU_COARSE_PAGE_SIZE, attrs);
            } else {
                status = -ENOMEM;
            }
        } else {
            /* Found valid L1 PTE of another size.
             * Should not overwrite it. */
            status = -EINVAL;
        }
        if (status == 0) {
            pg_tbl_va = l2_base_va;
            if (size == HW_PAGE_SIZE_64KB)
                pt->pg_info[l2_page_num].num_entries += 16;
            else
                pt->pg_info[l2_page_num].num_entries++;
        }
    }
    if (status == 0) {
        mapAttrs->endian = attrs->endianism;
        mapAttrs->mixed = attrs->mixedSize;
        mapAttrs->elsz= attrs->element_size;
        mapAttrs->da = va;
        mapAttrs->pa = pa;
        mapAttrs->pgsz = MMU_CAM_PGSZ_16M;
        setPteInfo.elementSize = attrs->element_size;
        setPteInfo.endianism = attrs->endianism;
        setPteInfo.masterPhyAddr = pa;
        setPteInfo.mixedSize = attrs->mixedSize;
        setPteInfo.size = size;
        setPteInfo.slaveVirtAddr = va;

        status = hw_mmu_pte_set(pg_tbl_va, pa, va, size, attrs);
        if (status == RET_OK)
            status = 0;
    }
    Memory_free(0, mapAttrs, sizeof(struct iotlb_entry));
    return status;
}


/*=============================================
 * This function calculates the optimum page-aligned addresses and sizes
 * Caller must pass page-aligned values
 */
static Int pte_update (UInt32 pa, UInt32 va, UInt32 size,
                       struct hw_mmu_map_attrs_t *map_attrs, struct pg_table_attrs *pt_Table)
{
    UInt32 i;
    UInt32 all_bits;
    UInt32 pa_curr = pa;
    UInt32 va_curr = va;
    UInt32 num_bytes = size;
    Int status = 0;
    UInt32 pg_size[] = {HW_PAGE_SIZE_16MB, HW_PAGE_SIZE_1MB,
               HW_PAGE_SIZE_64KB, HW_PAGE_SIZE_4KB};
    while (num_bytes && (status == 0)) {
        /* To find the max. page size with which both PA & VA are
         * aligned */
        all_bits = pa_curr | va_curr;
        for (i = 0; i < 4; i++) {
            if ((num_bytes >= pg_size[i]) && ((all_bits &
               (pg_size[i] - 1)) == 0)) {
                status = pte_set(pa_curr,
                    va_curr, pg_size[i], map_attrs, pt_Table);
                pa_curr += pg_size[i];
                va_curr += pg_size[i];
                num_bytes -= pg_size[i];
                 /* Don't try smaller sizes. Hopefully we have
                 * reached an address aligned to a bigger page
                 * size */
                break;
            }
        }
    }
    return status;
}


/*============================================
 * This function maps MPU buffer to the DSP address space. It performs
* linear to physical address translation if required. It translates each
* page since linear addresses can be physically non-contiguous
* All address & size arguments are assumed to be page aligned (in proc.c)
 *
 */
static Int benelli_mem_map (OMAP5430BENELLI_HalObject * halObject,
                            UInt32 mpu_addr, UInt32 ul_virt_addr,
                            UInt32 num_bytes, UInt32 map_attr)
{
    UInt32 attrs;
    Int status = 0;
    struct hw_mmu_map_attrs_t hw_attrs;
    Int pg_i = 0;

    if (halObject == NULL) {
        status = -ENOMEM;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "benelli_mem_map",
                             status,
                             "halObject is NULL");
    }
    else if (halObject->mmuBase == 0) {
        status = -ENOMEM;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "benelli_mem_map",
                             status,
                             "halObject->mmuBase is 0");
    }
    else if (num_bytes == 0) {
        status = -EINVAL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "benelli_mem_map",
                             status,
                             "num_bytes is 0");
    }
    else {
        if (map_attr != 0) {
            attrs = map_attr;
            attrs |= DSP_MAPELEMSIZE32;
        } else {
            /* Assign default attributes */
            attrs = DSP_MAPVIRTUALADDR | DSP_MAPELEMSIZE32;
        }
        /* Take mapping properties */
        if (attrs & DSP_MAPBIGENDIAN)
            hw_attrs.endianism = HW_BIG_ENDIAN;
        else
            hw_attrs.endianism = HW_LITTLE_ENDIAN;

        hw_attrs.mixedSize = (enum hw_mmu_mixed_size_t)
                     ((attrs & DSP_MAPMIXEDELEMSIZE) >> 2);
        /* Ignore element_size if mixedSize is enabled */
        if (hw_attrs.mixedSize == 0) {
            if (attrs & DSP_MAPELEMSIZE8) {
                /* Size is 8 bit */
                hw_attrs.element_size = HW_ELEM_SIZE_8BIT;
            } else if (attrs & DSP_MAPELEMSIZE16) {
                /* Size is 16 bit */
                hw_attrs.element_size = HW_ELEM_SIZE_16BIT;
            } else if (attrs & DSP_MAPELEMSIZE32) {
                /* Size is 32 bit */
                hw_attrs.element_size = HW_ELEM_SIZE_32BIT;
            } else if (attrs & DSP_MAPELEMSIZE64) {
                /* Size is 64 bit */
                hw_attrs.element_size = HW_ELEM_SIZE_64BIT;
            } else {
                /* Mixedsize isn't enabled, so size can't be
                 * zero here */
                status = -EINVAL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "benelli_mem_map",
                                     status,
                                     "MMU element size is zero");
            }
        }

        if (status >= 0) {
            /*
             * Do OS-specific user-va to pa translation.
             * Combine physically contiguous regions to reduce TLBs.
             * Pass the translated pa to PteUpdate.
             */
            if ((attrs & DSP_MAPPHYSICALADDR)) {
                status = pte_update(mpu_addr, ul_virt_addr, num_bytes,
                                    &hw_attrs, (halObject->procId == MultiProc_getId("DSP"))? tesla_p_pt_attrs: p_pt_attrs);
            }

            /* Don't propogate Linux or HW status to upper layers */
            if (status < 0) {
                /*
                 * Roll out the mapped pages incase it failed in middle of
                 * mapping
                 */
                if (pg_i)
                    benelli_mem_unmap(halObject, ul_virt_addr,
                                      (pg_i * PAGE_SIZE));
            }

            /* In any case, flush the TLB
             * This is called from here instead from pte_update to avoid
             * unnecessary repetition while mapping non-contiguous physical
             * regions of a virtual region */
            hw_mmu_tlb_flushAll(halObject->mmuBase);
        }
    }
    return status;
}



/*
 *  ======== benelli_mem_unmap ========
 *      Invalidate the PTEs for the DSP VA block to be unmapped.
 *
 *      PTEs of a mapped memory block are contiguous in any page table
 *      So, instead of looking up the PTE address for every 4K block,
 *      we clear consecutive PTEs until we unmap all the bytes
 */
static Int benelli_mem_unmap (OMAP5430BENELLI_HalObject * halObject,
                              UInt32 da, UInt32 num_bytes)
{
    UInt32 L1_base_va;
    UInt32 L2_base_va;
    UInt32 L2_base_pa;
    UInt32 L2_page_num;
    UInt32 pte_val;
    UInt32 pte_size;
    UInt32 pte_count;
    UInt32 pte_addr_l1;
    UInt32 pte_addr_l2 = 0;
    UInt32 rem_bytes;
    UInt32 rem_bytes_l2;
    UInt32 vaCurr;
    Int status = 0;
    UInt32 temp;
    UInt32 pAddr;
    UInt32 numof4Kpages = 0;

    if (halObject == NULL) {
        status = -ENOMEM;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "benelli_mem_unmap",
                             status,
                             "halObject is NULL");
    }
    else if (halObject->mmuBase == 0) {
        status = -ENOMEM;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "benelli_mem_unmap",
                             status,
                             "halObject->mmuBase is 0");
    }
    else {
        vaCurr = da;
        rem_bytes = num_bytes;
        rem_bytes_l2 = 0;
        L1_base_va = p_pt_attrs->l1_base_va;
        pte_addr_l1 = hw_mmu_pte_addr_l1(L1_base_va, vaCurr);
        while (rem_bytes) {
            UInt32 vaCurrOrig = vaCurr;
            /* Find whether the L1 PTE points to a valid L2 PT */
            pte_addr_l1 = hw_mmu_pte_addr_l1(L1_base_va, vaCurr);
            pte_val = *(UInt32 *)pte_addr_l1;
            pte_size = hw_mmu_pte_sizel1(pte_val);
            if (pte_size == HW_MMU_COARSE_PAGE_SIZE) {
                /*
                 * Get the L2 PA from the L1 PTE, and find
                 * corresponding L2 VA
                 */
                L2_base_pa = hw_mmu_pte_coarsel1(pte_val);
                L2_base_va = L2_base_pa - p_pt_attrs->l2_base_pa
                            + p_pt_attrs->l2_base_va;
                L2_page_num = (L2_base_pa - p_pt_attrs->l2_base_pa) /
                        HW_MMU_COARSE_PAGE_SIZE;
                /*
                 * Find the L2 PTE address from which we will start
                 * clearing, the number of PTEs to be cleared on this
                 * page, and the size of VA space that needs to be
                 * cleared on this L2 page
                 */
                pte_addr_l2 = hw_mmu_pte_addr_l2(L2_base_va, vaCurr);
                pte_count = pte_addr_l2 & (HW_MMU_COARSE_PAGE_SIZE - 1);
                pte_count = (HW_MMU_COARSE_PAGE_SIZE - pte_count) /
                        sizeof(UInt32);
                if (rem_bytes < (pte_count * PAGE_SIZE))
                    pte_count = rem_bytes / PAGE_SIZE;

                rem_bytes_l2 = pte_count * PAGE_SIZE;
                /*
                 * Unmap the VA space on this L2 PT. A quicker way
                 * would be to clear pte_count entries starting from
                 * pte_addr_l2. However, below code checks that we don't
                 * clear invalid entries or less than 64KB for a 64KB
                 * entry. Similar checking is done for L1 PTEs too
                 * below
                 */
                while (rem_bytes_l2) {
                    pte_val = *(UInt32 *)pte_addr_l2;
                    pte_size = hw_mmu_pte_sizel2(pte_val);
                    /* vaCurr aligned to pte_size? */
                    if ((pte_size != 0) && (rem_bytes_l2
                        >= pte_size) &&
                        !(vaCurr & (pte_size - 1))) {
                        /* Collect Physical addresses from VA */
                        pAddr = (pte_val & ~(pte_size - 1));
                        if (pte_size == HW_PAGE_SIZE_64KB)
                            numof4Kpages = 16;
                        else
                            numof4Kpages = 1;
                        temp = 0;

                        if (hw_mmu_pte_clear(pte_addr_l2,
                            vaCurr, pte_size) == RET_OK) {
                            rem_bytes_l2 -= pte_size;
                            vaCurr += pte_size;
                            pte_addr_l2 += (pte_size >> 12)
                                * sizeof(UInt32);
                        } else {
                            status = -EFAULT;
                            goto EXIT_LOOP;
                        }
                    } else
                        status = -EFAULT;
                }
                if (rem_bytes_l2 != 0) {
                    status = -EFAULT;
                    goto EXIT_LOOP;
                }
                p_pt_attrs->pg_info[L2_page_num].num_entries -=
                            pte_count;
                if (p_pt_attrs->pg_info[L2_page_num].num_entries
                                    == 0) {
                    /*
                     * Clear the L1 PTE pointing to the
                     * L2 PT
                     */
                    if (RET_OK != hw_mmu_pte_clear(L1_base_va,
                        vaCurrOrig, HW_MMU_COARSE_PAGE_SIZE)) {
                        status = -EFAULT;
                        goto EXIT_LOOP;
                    }
                }
                rem_bytes -= pte_count * PAGE_SIZE;
            } else
                /* vaCurr aligned to pte_size? */
                /* pte_size = 1 MB or 16 MB */
                if ((pte_size != 0) && (rem_bytes >= pte_size) &&
                   !(vaCurr & (pte_size - 1))) {
                    if (pte_size == HW_PAGE_SIZE_1MB)
                        numof4Kpages = 256;
                    else
                        numof4Kpages = 4096;
                    temp = 0;
                    /* Collect Physical addresses from VA */
                    pAddr = (pte_val & ~(pte_size - 1));
                    if (hw_mmu_pte_clear(L1_base_va, vaCurr,
                            pte_size) == RET_OK) {
                        rem_bytes -= pte_size;
                        vaCurr += pte_size;
                    } else {
                        status = -EFAULT;
                        goto EXIT_LOOP;
                    }
            } else {
                status = -EFAULT;
            }
        }
    }
    /*
     * It is better to flush the TLB here, so that any stale old entries
     * get flushed
     */
EXIT_LOOP:
    hw_mmu_tlb_flushAll(halObject->mmuBase);
    return status;
}


/*========================================
 * This sets up the Benelli processor
 *
 */
Int ipu_setup (OMAP5430BENELLI_HalObject * halObject,
               ProcMgr_AddrInfo * memEntries,
               UInt32 numMemEntries)
{
    Int ret_val = 0;

    if (halObject->procId == PROCTYPE_IPU0) {
        ret_val = init_mmu_page_attribs(0x10000, 14, 128);
        if (ret_val < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ipu_setup",
                                 ret_val,
                                 "init_mmu_page_attribs failed");
        }
        else {
            /* Disable TWL  */
            ret_val = benelli_set_twl(halObject, FALSE);
            if (ret_val < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "ipu_setup",
                                     ret_val,
                                     "benelli_set_twl to FALSE failed");
            }
            else {
                ret_val = benelli_mmu_init (halObject, memEntries,
                                            numMemEntries);
                if (ret_val < 0) {
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "ipu_setup",
                                         ret_val,
                                         "benelli_mmu_init failed");
                }
                else {
                    ret_val = benelli_set_twl(halObject, TRUE);
                    if (ret_val < 0) {
                        GT_setFailureReason (curTrace,
                                             GT_4CLASS,
                                             "ipu_setup",
                                             ret_val,
                                             "ducati_set_twl to TRUE failed");
                    }
                }
            }
        }
    }
    return ret_val;
}



Void ipu_destroy(OMAP5430BENELLI_HalObject * halObject)
{
    if (halObject->procId == PROCTYPE_IPU0) {
        shm_phys_addr = 0;
        deinit_mmu_page_attribs();
    }
    else if (halObject->procId == PROCTYPE_DSP) {
        shm_phys_addr_dsp = 0;
        deinit_dsp_mmu_page_attribs();
    }
}

int tesla_setup (OMAP5430BENELLI_HalObject * halObject,
                 ProcMgr_AddrInfo * memEntries,
                 UInt32 numMemEntries)
{
    int ret_val = 0;

    /* Disable TWL  */
    ret_val = init_tesla_page_attributes();
    if(ret_val < 0){
            ret_val = -ENOMEM;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "tesla_setup",
                                 ret_val ,
                                 "init_tesla_page_attributes failed");
        }
    else {
        ret_val = tesla_set_twl(halObject, FALSE);
        if(ret_val < 0){
            ret_val = -ENOMEM;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "tesla_setup",
                                 ret_val ,
                                 "tesla_set_twl failed");
        }
        else {
            ret_val = tesla_mmu_init(halObject, memEntries, numMemEntries);
            if(ret_val < 0){
                ret_val = -ENOMEM;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "tesla_setup",
                                     ret_val ,
                                     "tesla_mmu_init failed");
            }
            else {
                ret_val = tesla_set_twl(halObject, TRUE);
                if(ret_val < 0){
                    ret_val = -ENOMEM;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "tesla_setup",
                                         ret_val ,
                                         "tesla_set_twl failed");
                }
            }
        }
    }

    return ret_val;
}

static Void iotlb_load_cr (OMAP5430BENELLI_HalObject * halObject,
                           struct cr_regs *cr)
{
    ULONG reg;
    OMAP5430Benelli_MMURegs * mmuRegs =
                                  (OMAP5430Benelli_MMURegs *)halObject->mmuBase;

    reg = cr->cam | MMU_CAM_V;
    OUTREG32(&mmuRegs->CAM, reg);

    reg = cr->ram;
    OUTREG32(&mmuRegs->RAM, reg);

    reg = 1;
    OUTREG32(&mmuRegs->FLUSH_ENTRY, reg);

    reg = 1;
    OUTREG32(&mmuRegs->LD_TLB, reg);
}


/**
 * iotlb_dump_cr - Dump an iommu tlb entry into buf
 * @obj:    target iommu
 * @cr:        contents of cam and ram register
 * @buf:    output buffer
 **/
static UInt32 iotlb_dump_cr (struct cr_regs *cr, char *buf)
{
    Char *p = buf;

    if(!cr || !buf)
        return 0;

    /* FIXME: Need more detail analysis of cam/ram */
    p += sprintf(p, "%08x %08x %01x\n", (unsigned int)cr->cam,
                    (unsigned int)cr->ram,
                    (cr->cam & MMU_CAM_P) ? 1 : 0);
    return (p - buf);
}



static Int iotlb_cr_valid (struct cr_regs *cr)
{
    if (!cr)
        return -EINVAL;

    return (cr->cam & MMU_CAM_V);
}



static struct cr_regs *omap5_alloc_cr (struct iotlb_entry *e)
{
    struct cr_regs *cr;

    if (e->da & ~(get_cam_va_mask(e->pgsz))) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "omap5_alloc_cr",
                             -EINVAL,
                             "failed mask check");
        return NULL;
    }

    cr = mmap(NULL,
              sizeof(struct cr_regs),
              PROT_NOCACHE | PROT_READ | PROT_WRITE,
              MAP_ANON | MAP_PHYS | MAP_PRIVATE,
              NOFD,
              0);

    if (MAP_FAILED == cr)
    {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "omap5_alloc_cr",
                             -EINVAL,
                             "mmap failed");
        return NULL;
    }

    cr->cam = (e->da & MMU_CAM_VATAG_MASK) | e->prsvd | e->pgsz | e->valid;
    cr->ram = e->pa | e->endian | e->elsz | e->mixed;
    return cr;
}



static struct cr_regs *iotlb_alloc_cr (struct iotlb_entry *e)
{
    if (!e) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "iotlb_alloc_cr",
                             -EINVAL,
                             "e is NULL");
        return NULL;
    }

    return omap5_alloc_cr(e);
}



/**
 * load_iotlb_entry - Set an iommu tlb entry
 * @obj:    target iommu
 * @e:        an iommu tlb entry info
 **/
static Int load_iotlb_entry (OMAP5430BENELLI_HalObject * halObject,
                             struct iotlb_entry *e)
{
    Int err = 0;
    struct iotlb_lock l;
    struct cr_regs *cr;

    if (halObject == NULL) {
        err = -EINVAL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "load_iotlb_entry",
                             err,
                             "halObject is NULL");
        goto out;
    }

    if (halObject->mmuBase == NULL) {
        err = -EINVAL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "load_iotlb_entry",
                             err,
                             "halObject->mmuBase is NULL");
        goto out;
    }

    if (!e) {
        err = -EINVAL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "load_iotlb_entry",
                             err,
                             "e is NULL");
        goto out;
    }

    iotlb_getLock(halObject, &l);

    if (l.base == 32) {
        err = -EBUSY;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "load_iotlb_entry",
                             err,
                             "l.base is full");
        goto out;
    }
    if (!e->prsvd) {
        int i;
        struct cr_regs tmp;

        for_each_iotlb_cr(32, i, tmp)
            if (!iotlb_cr_valid(&tmp))
                break;

        if (i == 32) {
            err = -EBUSY;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "load_iotlb_entry",
                                 err,
                                 "i == 32");
            goto out;
        }

        iotlb_getLock(halObject, &l);
    } else {
        l.vict = l.base;
        iotlb_setLock(halObject, &l);
    }

    cr = iotlb_alloc_cr(e);
    if (!cr){
        err = -ENOMEM;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "load_iotlb_entry",
                             err,
                             "iotlb_alloc_cr failed");
        goto out;
    }

    iotlb_load_cr(halObject, cr);
    munmap(cr, sizeof(struct cr_regs));

    if (e->prsvd)
        l.base++;
    /* increment victim for next tlb load */
    if (++l.vict == 32)
        l.vict = l.base;
    iotlb_setLock(halObject, &l);

out:
    return err;
}

