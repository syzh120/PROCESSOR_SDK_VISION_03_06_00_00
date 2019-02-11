/**
 *  @file   OMAP5430BenelliHalMmu.h
 *
 *  @brief      Hardware abstraction for Memory Management Unit module.
 *
 *              This module is responsible for handling slave MMU related
 *              hardware- specific operations.
 *              The implementation is specific to OMAP5430BENELLI.
 *
 *
 *  @ver        02.00.00.44_pre-alpha3
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

#ifndef OMAP5430BENELLIHALMMU_H_0xbbee
#define OMAP5430BENELLIHALMMU_H_0xbbee


/* OSAL and utils headers */
#include <ti/syslink/utils/List.h>
#include <OsalIsr.h>
#include <OsalMutex.h>

/* Module level headers */
#include <_ProcDefs.h>
#include "OMAP5430BenelliProc.h"


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
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

/*!
 *  @brief  enum for Element size.
 */
enum Omap3530_Hal_Mmu_Element_Size_tag {
    ELEM_SIZE_8BIT,
    ELEM_SIZE_16BIT,
    ELEM_SIZE_32BIT,
    ELEM_SIZE_64BIT
};

/*!
 *  @brief  enum for endianism.
 */
enum Omap3530_Hal_Mmu_Endianism_tag {
    LITTLE_ENDIAN,
    BIG_ENDIAN
};

/*!
 *  @brief  enum for endianism.
 */
enum Omap3530_Hal_Mmu_Mixed_Size_tag {
    MMU_TLBES,
    MMU_CPUES
};


/*!
 *  @brief  Information structure for each MMU Entry
 */
//typedef struct OMAP5430BENELLI_HalMmuEntryInfo_tag {
//    List_Elem   element;
//    /*!< List header to enable linking of this structure into linked list. */
//    UInt32      slaveVirtAddr;
//    /*!< Slave virtual address. */
//    UInt32      actualSize;
//    /*!< Actual Size of Entry. */
//    UInt32      processAddr;
//    /*!< Processed address. */
//    UInt32      processSize;
//    /*!< Processed size. */
//    UInt32      tlbEntry;
//    /*!< TLB entry of the MMU module. */
//    Bool        isDynamic;
//    /*!< Is the entry dynamic? */
//} OMAP5430BENELLI_HalMmuEntryInfo;

/*!
 *  @brief  Hardware Abstraction object for MMU module.
 */
typedef struct OMAP5430BENELLI_HalMmuObject_tag {
    UInt32          entriesCount [NUM_SIZE_ENTRIES_TLB];
    /*!< TLB entry counter in MMU. */
    List_Handle     mmuEntryList;
    /*!< List of MMU entries. */
    UInt32          mmuIrqStatus;
    /*!< IRQ status of MMU fault that has occurred. */
    UInt32          mmuFaultAddr;
    /*!< Fault address of MMU fault that has occurred. */
    OsalIsr_Handle  isrHandle;
    /*!< Pointer to IsrObject. */
    UInt32          tlbIndex;
    /*!< Next available MMU TLB index */
    Bool            isDynamic;
    /*!< Indicates whether the entry is dynamically created. */
} OMAP5430BENELLI_HalMmuObject;

/*!
 *  @brief  Args type for Processor_MmuCtrlCmd_Enable
 */
typedef struct OMAP5430BENELLI_HalMmuCtrlArgs_Enable_tag {
    UInt32             numMemEntries;
    /*!< Number of memory regions to be configured. */
    ProcMgr_AddrInfo * memEntries;
    /*!< Array of information structures for memory regions to be configured. */
} OMAP5430BENELLI_HalMmuCtrlArgs_Enable;

/*!
 *  @brief  Args type for Processor_MmuCtrlCmd_AddEntry
 */
//typedef struct OMAP5430BENELLI_HalMmuCtrlArgs_AddEntry_tag {
//    UInt32   procAddr;
//    /*!< Slave address to be mapped */
//    UInt32   size;
//    /*!< Size (in bytes) of region to be mapped */
//    UInt32   mappedAddr;
//    /*!< Mapped address in host address space */
//    UInt32   mappedSize;
//    /*!< Mapped size */
//} OMAP5430BENELLI_HalMmuCtrlArgs_AddEntry;

/*!
 *  @brief  Args type for Processor_MmuCtrlCmd_DeleteEntry
 */
/*!
 *  @brief  Args type for Processor_MmuCtrlCmd_AddEntry
 */


typedef struct OMAP5430BENELLI_HalMmuEntryInfo_tag {
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
}OMAP5430BENELLI_HalMmuEntryInfo ;

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
/*!
 *  @brief  Args type for Processor_MmuCtrlCmd_DeleteEntry
 */
typedef OMAP5430BENELLI_HalMmuEntryInfo OMAP5430BENELLI_HalMmuCtrlArgs_AddEntry;
typedef OMAP5430BENELLI_HalMmuEntryInfo OMAP5430BENELLI_HalMmuCtrlArgs_DeleteEntry;

/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Function to control MMU operations for this slave device. */
Int OMAP5430BENELLI_halMmuCtrl (Ptr halObj, Processor_MmuCtrlCmd cmd, Ptr arg);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* OMAP5430BenelliHalMmu_H_0xbbec */
