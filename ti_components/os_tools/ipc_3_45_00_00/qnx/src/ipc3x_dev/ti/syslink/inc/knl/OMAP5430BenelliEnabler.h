/*
 *  @file  OMAP5430BenelliEnabler.h
 *
 *  @brief  MMU programming module
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2010-2011, Texas Instruments Incorporated
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

#ifndef _DBENELLIMMU_ENABLER_H_
#define _DBENELLIMMU_ENABLER_H_

#include <OMAP5430BenelliHal.h>
#ifndef _U32
#define _U32
typedef unsigned long u32;
#endif
typedef unsigned short u16;

#define PAGE_SIZE_4KB                0x1000
#define PAGE_SIZE_64KB               0x10000
#define PAGE_SIZE_1MB                0x100000
#define PAGE_SIZE_16MB               0x1000000


/* Types of mapping attributes */

/* MPU address is virtual and needs to be translated to physical addr */
#define DSP_MAPVIRTUALADDR           0x00000000
#define DSP_MAPPHYSICALADDR          0x00000001

/* Mapped data is big endian */
#define DSP_MAPBIGENDIAN             0x00000002
#define DSP_MAPLITTLEENDIAN          0x00000000

/* Element size is based on DSP r/w access size */
#define DSP_MAPMIXEDELEMSIZE         0x00000004

/*
 * Element size for MMU mapping (8, 16, 32, or 64 bit)
 * Ignored if DSP_MAPMIXEDELEMSIZE enabled
 */
#define DSP_MAPELEMSIZE8             0x00000008
#define DSP_MAPELEMSIZE16            0x00000010
#define DSP_MAPELEMSIZE32            0x00000020
#define DSP_MAPELEMSIZE64            0x00000040

#define DSP_MAPVMALLOCADDR           0x00000080
#define DSP_MAPTILERADDR             0x00000100


/*
    Vikas KM: For MMU registry
    Taken from iommu2.h of Linux
*/

#define MMU_BENELLI_ENABLER_BASE     0x55082000
#define MMU_REVISION                 MMU_BENELLI_ENABLER_BASE + 0x00
#define MMU_SYSCONFIG                MMU_BENELLI_ENABLER_BASE + 0x10
#define MMU_SYSSTATUS                MMU_BENELLI_ENABLER_BASE + 0x14
#define MMU_IRQSTATUS                MMU_BENELLI_ENABLER_BASE + 0x18
#define MMU_IRQENABLE                MMU_BENELLI_ENABLER_BASE + 0x1c
#define MMU_WALKING_ST               MMU_BENELLI_ENABLER_BASE + 0x40
#define MMU_CNTL                     MMU_BENELLI_ENABLER_BASE + 0x44
#define MMU_FAULT_AD                 MMU_BENELLI_ENABLER_BASE + 0x48
#define MMU_TTB                      MMU_BENELLI_ENABLER_BASE + 0x4c
#define MMU_LOCK                     MMU_BENELLI_ENABLER_BASE + 0x50
#define MMU_LD_TLB                   MMU_BENELLI_ENABLER_BASE + 0x54
#define MMU_CAM                      MMU_BENELLI_ENABLER_BASE + 0x58
#define MMU_RAM                      MMU_BENELLI_ENABLER_BASE + 0x5c
#define MMU_GFLUSH                   MMU_BENELLI_ENABLER_BASE + 0x60
#define MMU_FLUSH_ENTRY              MMU_BENELLI_ENABLER_BASE + 0x64
#define MMU_READ_CAM                 MMU_BENELLI_ENABLER_BASE + 0x68
#define MMU_READ_RAM                 MMU_BENELLI_ENABLER_BASE + 0x6c
#define MMU_EMU_FAULT_AD             MMU_BENELLI_ENABLER_BASE + 0x70

#define MMU_REG_SIZE                 256

typedef struct OMAP5430Benelli_MMURegs_t {
    UInt32 REVISION;        /* offset 0x00 */
    UInt32 reserved0[3];    /* offset 0x04-0x0C */
    UInt32 SYSCONFIG;       /* offset 0x10 */
    UInt32 SYSSTATUS;       /* offset 0x14 */
    UInt32 IRQSTATUS;       /* offset 0x18 */
    UInt32 IRQENABLE;       /* offset 0x1C */
    UInt32 reserved1[8];    /* offset 0x20-0x3C */
    UInt32 WALKING_ST;      /* offset 0x40 */
    UInt32 CNTL;            /* offset 0x44 */
    UInt32 FAULT_AD;        /* offset 0x48 */
    UInt32 TTB;             /* offset 0x4C */
    UInt32 LOCK;            /* offset 0x50 */
    UInt32 LD_TLB;          /* offset 0x54 */
    UInt32 CAM;             /* offset 0x58 */
    UInt32 RAM;             /* offset 0x5C */
    UInt32 GFLUSH;          /* offset 0x60 */
    UInt32 FLUSH_ENTRY;     /* offset 0x64 */
    UInt32 READ_CAM;        /* offset 0x68 */
    UInt32 READ_RAM;        /* offset 0x6C */
    UInt32 EMU_FAULT_AD;    /* offset 0x70 */
    UInt32 reserved2[3];    /* offset 0x74-0x7C */
    UInt32 FAULT_PC;        /* offset 0x80 */
    UInt32 FAULT_STATUS;    /* offset 0x84 */
    UInt32 GP_REG;          /* offset 0x88 */
} OMAP5430Benelli_MMURegs;

/*
 * MMU Register bit definitions
 */
#define MMU_LOCK_BASE_SHIFT    10
#define MMU_LOCK_BASE_MASK    (0x1f << MMU_LOCK_BASE_SHIFT)
#define MMU_LOCK_BASE(x)    \
    ((x & MMU_LOCK_BASE_MASK) >> MMU_LOCK_BASE_SHIFT)

#define MMU_LOCK_VICT_SHIFT    4
#define MMU_LOCK_VICT_MASK    (0x1f << MMU_LOCK_VICT_SHIFT)
#define MMU_LOCK_VICT(x)    \
    ((x & MMU_LOCK_VICT_MASK) >> MMU_LOCK_VICT_SHIFT)

#define MMU_CAM_VATAG_SHIFT    12
#define MMU_CAM_VATAG_MASK \
    ((~0UL >> MMU_CAM_VATAG_SHIFT) << MMU_CAM_VATAG_SHIFT)
#define MMU_CAM_P              (1 << 3)
#define MMU_CAM_V              (1 << 2)
#define MMU_CAM_PGSZ_MASK      3
#define MMU_CAM_PGSZ_1M        (0 << 0)
#define MMU_CAM_PGSZ_64K       (1 << 0)
#define MMU_CAM_PGSZ_4K        (2 << 0)
#define MMU_CAM_PGSZ_16M       (3 << 0)

#define MMU_RAM_PADDR_SHIFT    12
#define MMU_RAM_PADDR_MASK \
    ((~0UL >> MMU_RAM_PADDR_SHIFT) << MMU_RAM_PADDR_SHIFT)
#define MMU_RAM_ENDIAN_SHIFT   9
#define MMU_RAM_ENDIAN_MASK    (1 << MMU_RAM_ENDIAN_SHIFT)
#define MMU_RAM_ENDIAN_BIG     (1 << MMU_RAM_ENDIAN_SHIFT)
#define MMU_RAM_ENDIAN_LITTLE  (0 << MMU_RAM_ENDIAN_SHIFT)
#define MMU_RAM_ELSZ_SHIFT     7
#define MMU_RAM_ELSZ_MASK      (3 << MMU_RAM_ELSZ_SHIFT)
#define MMU_RAM_ELSZ_8         (0 << MMU_RAM_ELSZ_SHIFT)
#define MMU_RAM_ELSZ_16        (1 << MMU_RAM_ELSZ_SHIFT)
#define MMU_RAM_ELSZ_32        (2 << MMU_RAM_ELSZ_SHIFT)
#define MMU_RAM_ELSZ_NONE      (3 << MMU_RAM_ELSZ_SHIFT)
#define MMU_RAM_MIXED_SHIFT    6
#define MMU_RAM_MIXED_MASK     (1 << MMU_RAM_MIXED_SHIFT)
#define MMU_RAM_MIXED          MMU_RAM_MIXED_MASK

/*
    Vikas KM: The MMU reguistry Ends Here.
*/


/*
 * omap2 architecture specific register bit definitions
 */
#define IOMMU_ARCH_VERSION     0x00000011

/* SYSCONF */
#define MMU_SYS_IDLE_SHIFT     3
#define MMU_SYS_IDLE_FORCE     (0 << MMU_SYS_IDLE_SHIFT)
#define MMU_SYS_IDLE_NONE      (1 << MMU_SYS_IDLE_SHIFT)
#define MMU_SYS_IDLE_SMART     (2 << MMU_SYS_IDLE_SHIFT)
#define MMU_SYS_IDLE_MASK      (3 << MMU_SYS_IDLE_SHIFT)

#define MMU_SYS_SOFTRESET      (1 << 1)
#define MMU_SYS_AUTOIDLE       1

/* SYSSTATUS */
#define MMU_SYS_RESETDONE      1

/* IRQSTATUS & IRQENABLE */
#define MMU_IRQ_MULTIHITFAULT  (1 << 4)
#define MMU_IRQ_TABLEWALKFAULT (1 << 3)
#define MMU_IRQ_EMUMISS        (1 << 2)
#define MMU_IRQ_TRANSLATIONFAULT (1 << 1)
#define MMU_IRQ_TLBMISS        (1 << 0)

#define __MMU_IRQ_FAULT        \
    (MMU_IRQ_MULTIHITFAULT | MMU_IRQ_EMUMISS | MMU_IRQ_TRANSLATIONFAULT)
#define MMU_IRQ_MASK        \
    (__MMU_IRQ_FAULT | MMU_IRQ_TABLEWALKFAULT | MMU_IRQ_TLBMISS)
#define MMU_IRQ_TWL_MASK    (__MMU_IRQ_FAULT | MMU_IRQ_TABLEWALKFAULT)
#define MMU_IRQ_TLB_MISS_MASK    (__MMU_IRQ_FAULT | MMU_IRQ_TLBMISS)

/* MMU_CNTL */
#define MMU_CNTL_SHIFT         1
#define MMU_CNTL_MASK          (7 << MMU_CNTL_SHIFT)
#define MMU_CNTL_EML_TLB       (1 << 3)
#define MMU_CNTL_TWL_EN        (1 << 2)
#define MMU_CNTL_MMU_EN        (1 << 1)




#define PAGE_MASK(pg_size) (~((pg_size)-1))
#define PG_ALIGN_LOW(addr, pg_size) ((addr) & PAGE_MASK(pg_size))
#define PG_ALIGN_HIGH(addr, pg_size) (((addr)+(pg_size)-1) & PAGE_MASK(pg_size))



#define get_cam_va_mask(pgsz)                \
        (((pgsz) == MMU_CAM_PGSZ_16M) ? 0xff000000 :    \
         ((pgsz) == MMU_CAM_PGSZ_1M)  ? 0xfff00000 :    \
         ((pgsz) == MMU_CAM_PGSZ_64K) ? 0xffff0000 :    \
         ((pgsz) == MMU_CAM_PGSZ_4K)  ? 0xfffff000 : 0)


struct mmu_entry {
    u32 ul_phy_addr;
    u32 ul_virt_addr;
    u32 ul_size;
};

struct memory_entry {
    u32 ul_virt_addr;
    u32 ul_size;
};

struct cr_regs {
    union {
        struct {
            u16 cam_l;
            u16 cam_h;
        };
        u32 cam;
    };
    union {
        struct {
            u16 ram_l;
            u16 ram_h;
        };
        u32 ram;
    };
};

struct iotlb_lock {
    short base;
    short vict;
};


Int ipu_setup (OMAP5430BENELLI_HalObject * halObject,
               ProcMgr_AddrInfo * memEntries, UInt32 numMemEntries);
Void ipu_destroy (OMAP5430BENELLI_HalObject * halObject);
Int tesla_setup (OMAP5430BENELLI_HalObject * halObject,
                 ProcMgr_AddrInfo * memEntries, UInt32 numMemEntries);
UInt32 get_BenelliVirtAdd (OMAP5430BENELLI_HalObject * halObject,
                           UInt32 physAdd);
Int save_mmu_ctxt (OMAP5430BENELLI_HalObject * halObject, UInt32 procId);
Int restore_mmu_ctxt (OMAP5430BENELLI_HalObject * halObject, UInt32 procId);

#endif /* _DBENELLIMMU_ENABLER_H_*/

