/**
 *  @file   VAYUDspHalMmu.h
 *
 *  @brief      Hardware abstraction for Memory Management Unit module.
 *
 *              This module is responsible for handling slave MMU related
 *              hardware- specific operations.
 *              The implementation is specific to VAYUDSP.
 *
 *
 */
/*
 *  ============================================================================
 *
 *  Copyright (c) 2013-2015, Texas Instruments Incorporated
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


#ifndef VAYUDSPHALMMU_H_0xbbed
#define VAYUDSPHALMMU_H_0xbbed


/* OSAL and utils headers */
#include <ti/syslink/utils/List.h>
#include <OsalIsr.h>

/* Module level headers */
#include <_ProcDefs.h>
#include <VAYUDspProc.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros
 *  See _ProcDefs.h
 * =============================================================================
 */
/*!
 *  @brief  Number of MMU entry sizes possible
 */
#define  NUM_SIZE_ENTRIES_TLB    4

/*!
 *  @brief  Page size constants
 */
#define PAGE_SIZE_4KB             0x1000
/*!
 *  @brief  Page size constants
 */
#define PAGE_SIZE_64KB            0x10000
/*!
 *  @brief  Page size constants
 */
#define PAGE_SIZE_1MB             0x100000
/*!
 *  @brief  Page size constants
 */
#define PAGE_SIZE_16MB            0x1000000

#define MMU_CAM_P                   (1 << 3)
#define MMU_CAM_V                   (1 << 2)
#define MMU_CAM_PGSZ_MASK           3
#define MMU_CAM_PGSZ_1M             (0 << 0)
#define MMU_CAM_PGSZ_64K            (1 << 0)
#define MMU_CAM_PGSZ_4K             (2 << 0)
#define MMU_CAM_PGSZ_16M            (3 << 0)

#define MMU_RAM_ENDIAN_SHIFT        9
#define MMU_RAM_ENDIAN_MASK         (1 << MMU_RAM_ENDIAN_SHIFT)
#define MMU_RAM_ENDIAN_BIG          (1 << MMU_RAM_ENDIAN_SHIFT)
#define MMU_RAM_ENDIAN_LITTLE       (0 << MMU_RAM_ENDIAN_SHIFT)

#define MMU_RAM_ELSZ_SHIFT          7
#define MMU_RAM_ELSZ_MASK           (3 << MMU_RAM_ELSZ_SHIFT)
#define MMU_RAM_ELSZ_8              (0 << MMU_RAM_ELSZ_SHIFT)
#define MMU_RAM_ELSZ_16             (1 << MMU_RAM_ELSZ_SHIFT)
#define MMU_RAM_ELSZ_32             (2 << MMU_RAM_ELSZ_SHIFT)
#define MMU_RAM_ELSZ_NONE           (3 << MMU_RAM_ELSZ_SHIFT)
#define MMU_RAM_MIXED_SHIFT         6
#define MMU_RAM_MIXED_MASK          (1 << MMU_RAM_MIXED_SHIFT)
#define MMU_RAM_MIXED               MMU_RAM_MIXED_MASK
#define MMU_RAM_DEFAULT                0

#define NR_TLBS_MAX                 32

typedef struct VAYUDsp_MMURegs_t {
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
} VAYUDsp_MMURegs;

#define MMU_REGS_SIZE (sizeof(VAYUDsp_MMURegs) / sizeof (UInt32))



/* =============================================================================
 *  Enums
 * =============================================================================
 */
/*!
 *  @brief  enum for Element size.
 */
enum VAYUDsp_Hal_Mmu_Element_Size_tag {
    ELEM_SIZE_8BIT,
    ELEM_SIZE_16BIT,
    ELEM_SIZE_32BIT,
    ELEM_SIZE_64BIT
};

/*!
 *  @brief  enum for endianism.
 */
enum VAYUDsp_Hal_Mmu_Endianism_tag {
    LITTLE_ENDIAN,
    BIG_ENDIAN
};

/*!
 *  @brief  enum for endianism.
 */
enum VAYUDsp_Hal_Mmu_Mixed_Size_tag {
    MMU_TLBES,
    MMU_CPUES
};

struct iotlb_entry
{
    ULONG pgsz;
    ULONG prsvd;
    ULONG valid;
    ULONG elsz;
    ULONG endian;
    ULONG mixed;
    ULONG da;
    ULONG pa;
};

/* =============================================================================
 *  structs
 * =============================================================================
 */

/*!
 *  @brief  Hardware Abstraction object for MMU module.
 */
typedef struct VAYUDSP_HalMmuObject_tag {
    UInt32          entriesCount [NUM_SIZE_ENTRIES_TLB];
    /*!< TLB entry counter in MMU. */
    List_Handle     mmuEntryList;
    /*!< List of MMU entries. */
    UInt32          mmuIrqStatus;
    /*!< IRQ status of MMU fault that has occurred. */
    UInt32                 mmuFaultAddr;
    /*!< Fault address of MMU fault that has occurred. */
    OsalIsr_Handle  isrHandle;
    /*!< Pointer to IsrObject. */
    struct clk *           clkHandle;
    /*!< Enables and disables the iva2_ck clock. */
    UInt32          tlbIndex;
    /*!< Next available MMU TLB index */
    Bool            isDynamic;
    /*!< Indicates whether the entry is dynamically created. */
    Void *          pPtAttrs;
    /*!< Attrs used by BenelliEnabler for mmu programming. */
    struct iotlb_entry tlbs[NR_TLBS_MAX];
    /*!< Space to save the TLBS during hibernation. */
    UInt32          nrTlbs;
    /*!< Number of TLBs saved in tlbs[]. */
    UInt32          mmuRegs[MMU_REGS_SIZE];
} VAYUDSP_HalMmuObject;

/*!
 *  @brief  Args type for Processor_MmuCtrlCmd_Enable
 */
typedef struct VAYUDSP_HalMmuCtrlArgs_Enable_tag {
    UInt32             numMemEntries;
    /*!< Number of memory regions to be configured. */
    ProcMgr_AddrInfo * memEntries;
    /*!< Array of information structures for memory regions to be configured. */
} VAYUDSP_HalMmuCtrlArgs_Enable;

/*!
 *  @brief  Args type for Processor_MmuCtrlCmd_AddEntry
 */
typedef struct VAYUDSP_HalMmuEntryInfo_tag {
    UInt32   slaveVirtAddr;
    /*!< Slave address to be mapped */
    UInt32   size;
    /*!< Size (in bytes) of region to be mapped */
    UInt32   masterPhyAddr;
    /*!< Mapped address in host address space */
    UInt32   elementSize;
    /*!< element size */
    UInt32   endianism;
    /*!< Little / big endian */
    UInt32   mixedSize;
    /*!< Types of pages in on segment*/
}VAYUDSP_HalMmuEntryInfo ;

/*!
 *  @brief  Args type for Processor_MmuCtrlCmd_DeleteEntry
 */
typedef VAYUDSP_HalMmuEntryInfo VAYUDSP_HalMmuCtrlArgs_AddEntry;
typedef VAYUDSP_HalMmuEntryInfo VAYUDSP_HalMmuCtrlArgs_DeleteEntry;

/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Function to control MMU operations for this slave device. */
Int VAYUDSP_halMmuCtrl (Ptr halObj, Processor_MmuCtrlCmd cmd, Ptr arg);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* VAYUDspHalMmu_H_0xbbec */
