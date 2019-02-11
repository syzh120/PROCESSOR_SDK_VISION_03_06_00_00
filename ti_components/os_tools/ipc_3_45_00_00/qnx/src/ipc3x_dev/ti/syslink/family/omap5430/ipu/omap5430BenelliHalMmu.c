/*
 *  @file   omap5430BenelliHalMmu.c
 *
 *  @brief      Hardware abstraction for Memory Management Unit module.
 *
 *              This module is responsible for handling slave MMU-related
 *              hardware- specific operations.
 *              The implementation is specific to OMAP5430BENELLI.
 *
 *
 *  @ver        02.00.00.44_pre-alpha3
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


/* Standard headers */
#include <ti/syslink/Std.h>

/* OSAL and utils headers */
#include <ti/syslink/utils/List.h>
#include <ti/syslink/utils/Trace.h>
#include <ti/syslink/utils/OsalPrint.h>

/* Module level headers */
#include <_ProcDefs.h>
#include <Processor.h>

/* Hardware Abstraction Layer headers */
#include <OMAP5430BenelliHal.h>
#include <OMAP5430BenelliHalMmu.h>
#include <OMAP5430BenelliPhyShmem.h>
#include <OMAP5430BenelliEnabler.h>
#include <MMUAccInt.h>
#include <hw/inout.h>

/*QNX specific header include */
#include <sys/neutrino.h>
#include <errno.h>
#include <pthread.h>

#if defined (__cplusplus)
extern "C" {
#endif



/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief  CAM register field values
 */
#define MMU_CAM_PRESERVE          (1 << 3)
#define MMU_CAM_VALID             (1 << 2)

/*!
 *  @brief  Addresses lower than this do not go through the DSP's MMU
 */
#define MMU_GLOBAL_MEMORY         0x11000000

/*!
 *  @brief  Interrupt Id for DSP MMU faults
 */
#define MMU_FAULT_INTERRUPT          132
#define MMU_FAULT_INTERRUPT_DSP      60

/*!
 *  @brief  Size constants
 */
#define SIZE_4KB                 0x1000
#define SIZE_64KB               0x10000
#define SIZE_1MB               0x100000
#define SIZE_16MB             0x1000000

#define MMU_SECTION_ADDR_MASK    0xFFF00000
#define MMU_SSECTION_ADDR_MASK   0xFF000000
#define MMU_PAGE_TABLE_MASK      0xFFFFFC00
#define MMU_LARGE_PAGE_MASK      0xFFFF0000
#define MMU_SMALL_PAGE_MASK      0xFFFFF000


#define SLAVEVIRTADDR(x)  ((x)->addr [ProcMgr_AddrType_SlaveVirt])
#define SLAVEPHYSADDR(x)  ((x)->addr [ProcMgr_AddrType_SlavePhys])
#define MASTERPHYSADDR(x) ((x)->addr [ProcMgr_AddrType_MasterPhys])

#define MMUPAGE_ALIGN(size, psz)  (((size) + psz - 1) & ~(psz -1))

#define IOPTE_SHIFT     12
#define IOPTE_SIZE      (1 << IOPTE_SHIFT)
#define IOPTE_MASK      (~(IOPTE_SIZE - 1))
#define IOPAGE_MASK     IOPTE_MASK

/*!
 *  @def    REG32
 *  @brief  Regsiter access method.
 */
#define REG32(x)        (*(volatile UInt32 *) (x))

/* =============================================================================
 *  Structures used in this file
 * =============================================================================
 */

/* =============================================================================
 *  Forward declarations of internal functions
 * =============================================================================
 */
/* Enables the MMU for GEM Module. */
Int _OMAP5430BENELLI_halMmuEnable (OMAP5430BENELLI_HalObject * halObject,
                                UInt32                   numMemEntries,
                                ProcMgr_AddrInfo *       memTable);

/* Disables the MMU for GEM Module. */
Int _OMAP5430BENELLI_halMmuDisable (OMAP5430BENELLI_HalObject * halObject);

/* This function configures the specified addr to be in the TLB */
Int _OMAP5430BENELLI_halMmuAddEntry (OMAP5430BENELLI_HalObject * halObject,
                                        OMAP5430BENELLI_HalMmuEntryInfo * entry);

int _OMAP5430BENELLI_halMmuAddStaticEntries (OMAP5430BENELLI_HalObject * halObject,
                                          UInt32               numMemEntries,
                                          ProcMgr_AddrInfo *   memTable);


/* Delete entry from TLB. */
Int _OMAP5430BENELLI_halMmuDeleteEntry (OMAP5430BENELLI_HalObject * halObject,
                                        OMAP5430BENELLI_HalMmuEntryInfo * entry);

/* Set entry in to TLB. */
Int _OMAP5430BENELLI_halMmuPteSet (OMAP5430BENELLI_HalObject       * halObject,
                        OMAP5430BENELLI_HalMmuEntryInfo * setPteInfo);


/* =============================================================================
 * APIs called by OMAP5430BENELLIPROC module
 * =============================================================================
 */
/*!
 *  @brief      Function to control MMU operations for this slave device.
 *
 *  @param      halObj  Pointer to the HAL object
 *  @param      cmd     MMU control command
 *  @param      arg     Arguments specific to the MMU control command
 *
 *  @sa
 */
Int
OMAP5430BENELLI_halMmuCtrl (Ptr halObj, Processor_MmuCtrlCmd cmd, Ptr args)
{
    Int                  status    = PROCESSOR_SUCCESS;
    OMAP5430BENELLI_HalObject * halObject = NULL;

    GT_3trace (curTrace, GT_ENTER, "OMAP5430BENELLI_halMmuCtrl", halObj, cmd, args);

    GT_assert (curTrace, (halObj != NULL));

    halObject = (OMAP5430BENELLI_HalObject *) halObj ;

    switch (cmd) {
        case Processor_MmuCtrlCmd_Enable:
        {
            OMAP5430BENELLI_HalMmuCtrlArgs_Enable * enableArgs;
            enableArgs = (OMAP5430BENELLI_HalMmuCtrlArgs_Enable *) args;
            halObject = (OMAP5430BENELLI_HalObject *) halObj;
            status = _OMAP5430BENELLI_halMmuEnable (halObject,
                                          enableArgs->numMemEntries,
                                          enableArgs->memEntries);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                /*! @retval PROCESSOR_E_FAIL Failed to configure DSP MMU. */
                status = PROCESSOR_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "OMAP5430BENELLI_halMmuCtrl",
                                     status,
                                     "Failed to configure DSP MMU");
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
        break;

        case Processor_MmuCtrlCmd_Disable:
        {
            /* args are not used. */
            halObject = (OMAP5430BENELLI_HalObject *) halObj;
            status = _OMAP5430BENELLI_halMmuDisable (halObject);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                /*! @retval PROCESSOR_E_FAIL Failed to configure DSP MMU. */
                status = PROCESSOR_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "OMAP5430BENELLI_halMmuCtrl",
                                     status,
                                     "Failed to disable DSP MMU");
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
        break ;

        case Processor_MmuCtrlCmd_AddEntry:
        {
            OMAP5430BENELLI_HalMmuCtrlArgs_AddEntry * addEntry;
            addEntry = (OMAP5430BENELLI_HalMmuCtrlArgs_AddEntry *) args;

            halObject = (OMAP5430BENELLI_HalObject *) halObj;
           /* Add the entry in TLB for new request */
            //status = _OMAP5430BENELLI_halMmuAddEntry (halObject,addEntry) ;
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                status = PROCESSOR_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "OMAP5430BENELLI_halMmuCtrl",
                                     status,
                                     "Failed to dynamically add DSP MMU entry");
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        }
        break;

        case Processor_MmuCtrlCmd_DeleteEntry:
        {
            OMAP5430BENELLI_HalMmuCtrlArgs_DeleteEntry * deleteEntry;
            deleteEntry = (OMAP5430BENELLI_HalMmuCtrlArgs_DeleteEntry *) args;

            halObject = (OMAP5430BENELLI_HalObject *) halObj;

            //status = _OMAP5430BENELLI_halMmuDeleteEntry (halObject,deleteEntry);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                status = PROCESSOR_E_FAIL;
                GT_setFailureReason (curTrace,
                                  GT_4CLASS,
                                  "OMAP5430BENELLI_halMmuCtrl",
                                  status,
                                  "Failed to dynamically delete DSP MMU entry");
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
        break;
           default:
        {
            /*! @retval PROCESSOR_E_INVALIDARG Invalid argument */
            status = PROCESSOR_E_INVALIDARG;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "OMAP5430BENELLI_halMmuCtrl",
                                 status,
                                 "Unsupported MMU ctrl cmd specified");
        }
        break;
    }

    GT_1trace (curTrace, GT_LEAVE, "OMAP5430BENELLI_halMmuCtrl",status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}

/* =============================================================================
 * Internal functions
 * =============================================================================
 */
/*!
 *  @brief      Enables and configures the DSP MMU as per provided memory map.
 *
 *  @param      halObject       Pointer to the HAL object
 *  @param      numMemEntries   Number of memory entries in memTable
 *  @param      memTable        Table of memory entries to be configured
 *
 *  @sa
 */

Int
_OMAP5430BENELLI_halMmuAddStaticEntries (OMAP5430BENELLI_HalObject * halObject,
                                  UInt32               numMemEntries,
                                  ProcMgr_AddrInfo *   memTable)
{
    Int                           status    = PROCESSOR_SUCCESS;
    OMAP5430BENELLI_HalMmuEntryInfo      staticEntry;
    UInt32                        i;

    GT_3trace (curTrace, GT_ENTER, "_OMAP5430BENELLI_halMmuAddStaticEntries",
               halObject, numMemEntries, memTable);

    GT_assert (curTrace, (halObject != NULL));
    /* It is possible that numMemEntries may be 0, if user does not want to
     * configure any default regions.
     * memTable may also be NULL.
     */

    for (i = 0 ; i < numMemEntries && (status >= 0) ; i++) {
        if (SLAVEVIRTADDR (&memTable [i]) >= MMU_GLOBAL_MEMORY) {
            /* Configure the TLB */
            if (memTable [i].size != 0)
            {
                staticEntry.slaveVirtAddr =
                                         SLAVEVIRTADDR (&memTable [i]);
                staticEntry.size          = memTable[i].size;
                staticEntry.masterPhyAddr =
                                         MASTERPHYSADDR (&memTable [i]);
                /*TBD : elementSize, endianism, mixedSized are hard
                 *      coded now, must be configurable later*/
                staticEntry.elementSize   = MMU_RAM_ELSZ_16;
                staticEntry.endianism     = LITTLE_ENDIAN;
                staticEntry.mixedSize     = MMU_TLBES;
                status = _OMAP5430BENELLI_halMmuAddEntry (halObject,
                                                   &staticEntry);
                if (status < 0) {
                    /*! @retval PROCESSOR_E_FAIL Failed to add MMU entry. */
                    status = PROCESSOR_E_FAIL;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "_OMAP5430BENELLI_halMmuAddStaticEntries",
                                         status,
                                         "Failed to add MMU entry!");
                }
            }
        }
    }
    GT_1trace (curTrace, GT_LEAVE, "_OMAP5430BENELLI_halMmuAddStaticEntries", status);

    /*! @retval PROCESSOR_SUCCESS Operation completed successfully. */
    return status ;
}


/* =============================================================================
 * Internal functions
 * =============================================================================
 */
/*!
 *  @brief      Function to check and clear the remote proc interrupt
 *
 *  @param      arg     Optional argument to the function.
 *
 *  @sa         _OMAP5430BENELLI_halMmuInt_isr
 */
static
Bool
_OMAP5430BENELLI_halMmuCheckAndClearFunc (Ptr arg)
{
    OMAP5430BENELLI_HalObject * halObject = (OMAP5430BENELLI_HalObject *)arg;
    OMAP5430BENELLI_HalMmuObject * mmuObj = &(halObject->mmuObj);

    /* Check the interrupt status */
    mmuObj->mmuIrqStatus = REG32(halObject->mmuBase + MMU_MMU_IRQSTATUS_OFFSET);
    mmuObj->mmuIrqStatus &= MMU_IRQ_MASK;
    if (!(mmuObj->mmuIrqStatus))
        return (FALSE);

    /* Get the fault address. */
    mmuObj->mmuFaultAddr = REG32(halObject->mmuBase + MMU_MMU_FAULT_AD_OFFSET);

    /* Print the fault information */
    GT_1trace (curTrace, GT_4CLASS,
            "**************** %s-MMU Fault ****************",
            MultiProc_getName(halObject->procId));

    GT_1trace (curTrace, GT_4CLASS,
               "****    addr: 0x%x", mmuObj->mmuFaultAddr);
    if (mmuObj->mmuIrqStatus & MMU_IRQ_TLBMISS)
        GT_0trace (curTrace, GT_4CLASS, "****    TLBMISS");
    if (mmuObj->mmuIrqStatus & MMU_IRQ_TRANSLATIONFAULT)
        GT_0trace (curTrace, GT_4CLASS, "****    TRANSLATIONFAULT");
    if (mmuObj->mmuIrqStatus & MMU_IRQ_EMUMISS)
        GT_0trace (curTrace, GT_4CLASS, "****    EMUMISS");
    if (mmuObj->mmuIrqStatus & MMU_IRQ_TABLEWALKFAULT)
        GT_0trace (curTrace, GT_4CLASS, "****    TABLEWALKFAULT");
    if (mmuObj->mmuIrqStatus & MMU_IRQ_MULTIHITFAULT)
        GT_0trace (curTrace, GT_4CLASS, "****    MULTIHITFAULT");
    GT_0trace (curTrace, GT_4CLASS,
               "**************************************************");

    /* Clear the interrupt and disable further interrupts. */
    REG32(halObject->mmuBase + MMU_MMU_IRQENABLE_OFFSET) = 0x0;
    REG32(halObject->mmuBase + MMU_MMU_IRQSTATUS_OFFSET) = mmuObj->mmuIrqStatus;

    /* This is not a shared interrupt, so interrupt has always occurred */
    /*! @retval TRUE Interrupt has occurred. */
    return (TRUE);
}

/*!
 *  @brief      Interrupt Service Routine for Omap5430BenelliHalMmu module
 *
 *  @param      arg     Optional argument to the function.
 *
 *  @sa         _OMAP5430BENELLI_halMmuCheckAndClearFunc
 */
static
Bool
_OMAP5430BENELLI_halMmuInt_isr (Ptr arg)
{
    OMAP5430BENELLI_HalObject * halObject = (OMAP5430BENELLI_HalObject *)arg;
    OMAP5430BENELLIPROC_Object * proc5430Object = NULL;

    GT_1trace (curTrace, GT_ENTER, "_OMAP5430BENELLI_halMmuInt_isr", arg);
    OMAP5430BENELLIPROC_open((OMAP5430BENELLIPROC_Handle *)&proc5430Object, halObject->procId);
    Processor_setState(proc5430Object->procHandle, ProcMgr_State_Mmu_Fault);
    OMAP5430BENELLIPROC_close((OMAP5430BENELLIPROC_Handle *)&proc5430Object);


    GT_1trace (curTrace, GT_LEAVE, "_OMAP5430BENELLI_halMmuInt_isr", TRUE);

    /*! @retval TRUE Interrupt has been handled. */
    return (TRUE);
}

/*!
 *  @brief      Enables and configures the DSP MMU as per provided memory map.
 *
 *  @param      halObject       Pointer to the HAL object
 *  @param      numMemEntries   Number of memory entries in memTable
 *  @param      memTable        Table of memory entries to be configured
 *
 *  @sa
 */
Int
_OMAP5430BENELLI_halMmuEnable (OMAP5430BENELLI_HalObject * halObject,
                            UInt32                   numMemEntries,
                            ProcMgr_AddrInfo *       memTable)
{
    Int                           status    = PROCESSOR_SUCCESS;
    OMAP5430BENELLI_HalMmuObject *       mmuObj;
    OsalIsr_Params isrParams;

    GT_3trace (curTrace, GT_ENTER, "_OMAP5430BENELLI_halMmuEnable",
               halObject, numMemEntries, memTable);

    GT_assert (curTrace, (halObject != NULL));
    /* It is possible that numMemEntries may be 0, if user does not want to
     * configure any default regions.
     * memTable may also be NULL.
     */
    mmuObj = &(halObject->mmuObj);

    /* Create the ISR to listen for MMU Faults */
    isrParams.sharedInt        = FALSE;
    isrParams.checkAndClearFxn = &_OMAP5430BENELLI_halMmuCheckAndClearFunc;
    isrParams.fxnArgs          = halObject;
    if (halObject->procId == MultiProc_getId("DSP")) {
        isrParams.intId        = MMU_FAULT_INTERRUPT_DSP;
    }
    else {
        isrParams.intId        = MMU_FAULT_INTERRUPT;
    }

    mmuObj->isrHandle = OsalIsr_create (&_OMAP5430BENELLI_halMmuInt_isr,
                                        halObject,
                                        &isrParams);

#if !defined(IPC_BUILD_OPTIMIZE)
    if (mmuObj->isrHandle == NULL) {
        /*! @retval PROCESSOR_E_FAIL OsalIsr_create failed */
        status = PROCESSOR_E_FAIL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_OMAP5430BENELLI_halMmuEnable",
                             status,
                             "OsalIsr_create failed");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        status = OsalIsr_install (mmuObj->isrHandle);

#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_OMAP5430BENELLI_halMmuEnable",
                                 status,
                                 "OsalIsr_install failed");
        }
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "_OMAP5430BENELLI_halMmuEnable", status);

    /*! @retval PROCESSOR_SUCCESS Operation completed successfully. */
    return status ;
}


/*!
 *  @brief      Disables the DSP MMU.
 *
 *  @param      halObject       Pointer to the HAL object
 *
 *  @sa
 */
Int
_OMAP5430BENELLI_halMmuDisable (OMAP5430BENELLI_HalObject * halObject)
{
    Int                        status    = PROCESSOR_SUCCESS;
    Int                        tmpStatus = PROCESSOR_SUCCESS;
    OMAP5430BENELLI_HalMmuObject *    mmuObj;

    GT_1trace (curTrace, GT_ENTER, "_OMAP5430BENELLI_halMmuDisable", halObject);

    GT_assert (curTrace, (halObject != NULL));
    mmuObj = &(halObject->mmuObj);

    status = OsalIsr_uninstall (mmuObj->isrHandle);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_OMAP5430BENELLI_halMmuDisable",
                             status,
                             "OsalIsr_uninstall failed");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

#if !defined(IPC_BUILD_OPTIMIZE)
    tmpStatus =
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        OsalIsr_delete (&(mmuObj->isrHandle));
#if !defined(IPC_BUILD_OPTIMIZE)
    if ((status >= 0) && (tmpStatus < 0)) {
        status = tmpStatus;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_OMAP5430BENELLI_halMmuDisable",
                             status,
                             "OsalIsr_delete failed");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "_OMAP5430BENELLI_halMmuDisable", status);

    /*! @retval PROCESSOR_SUCCESS Operation completed successfully. */
    return status;
}


/*!
 *  @brief      This function adds an MMU entry for the specfied address and
 *              size.
 *
 *  @param      halObject   Pointer to the HAL object
 *  @param      slaveVirtAddr DSP virtual address of the memory region
 *  @param      size        Size of the memory region to be configured
 *  @param      isDynamic   Is the MMU entry being dynamically added?
 *
 *  @sa
 */
Int _OMAP5430BENELLI_halMmuAddEntry (OMAP5430BENELLI_HalObject * halObject,
                                        OMAP5430BENELLI_HalMmuEntryInfo * entry)
{
    Int                         status = PROCESSOR_SUCCESS;
    UInt32  *                   ppgd = NULL;
    UInt32  *                   ppte = NULL;
    OMAP5430BENELLI_HalMmuEntryInfo    currentEntry;
    OMAP5430BENELLI_HalMmuEntryInfo    te;
    Int32                       currentEntrySize;

    GT_2trace (curTrace, GT_ENTER, "_OMAP5430BENELLI_halMmuAddEntry",
               halObject, entry);

    GT_assert (curTrace, (halObject != NULL));
    GT_assert (curTrace, (entry     != NULL));

    /* Add the entry (or entries) */
    if (status >= 0) {
        Memory_copy(&currentEntry,
                    entry,
                    sizeof(OMAP5430BENELLI_HalMmuEntryInfo));

        /* Align the addresses to page size */
        currentEntry.size += (currentEntry.slaveVirtAddr & (PAGE_SIZE_4KB -1));
        currentEntry.slaveVirtAddr &= ~(PAGE_SIZE_4KB-1);
        currentEntry.masterPhyAddr &= ~(PAGE_SIZE_4KB-1);

        /* Align the size as well */
        currentEntry.size = MMUPAGE_ALIGN(currentEntry.size, PAGE_SIZE_4KB);
        currentEntrySize = currentEntry.size;

        /* Check every page if exists */
        do {
            /* Lookup if the entry exists */
            if (1)//!*ppgd || !*ppte)
            {
                /* Entry doesnot exists, insert this page */
                te.size = PAGE_SIZE_4KB;
                te.slaveVirtAddr = currentEntry.slaveVirtAddr;
                te.masterPhyAddr = currentEntry.masterPhyAddr;
                te.elementSize   = ELEM_SIZE_16BIT;
                te.endianism     = LITTLE_ENDIAN;
                te.mixedSize     = MMU_TLBES;
                status = _OMAP5430BENELLI_halMmuPteSet (halObject, &te);
#if !defined(IPC_BUILD_OPTIMIZE)
                if (status < 0) {
                    GT_setFailureReason (
                                    curTrace,
                                    GT_4CLASS,
                                    "_OMAP5430BENELLI_halMmuAddEntry",
                                    status,
                                    "Failed to in _OMAP5430BENELLI_halMmuPteSet!");
                }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            }
            else if (*ppgd && *ppte) {
                if (currentEntry.masterPhyAddr != (*ppte & IOPAGE_MASK)) {
                    /* Entry doesnot exists, insert this page */
                    te.size = PAGE_SIZE_4KB;
                    te.slaveVirtAddr = currentEntry.slaveVirtAddr;
                    te.masterPhyAddr = currentEntry.masterPhyAddr;
                    te.elementSize   = ELEM_SIZE_16BIT;
                    te.endianism     = LITTLE_ENDIAN;
                    te.mixedSize     = MMU_TLBES;
                    status = _OMAP5430BENELLI_halMmuPteSet (halObject, &te);
#if !defined(IPC_BUILD_OPTIMIZE)
                    if (status < 0) {
                        GT_setFailureReason (
                                        curTrace,
                                        GT_4CLASS,
                                        "_OMAP5430BENELLI_halMmuAddEntry",
                                        status,
                                        "Failed to in _OMAP5430BENELLI_halMmuPteSet!");
                    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                }
            }

            currentEntrySize -= PAGE_SIZE_4KB;
            currentEntry.slaveVirtAddr += PAGE_SIZE_4KB;
            currentEntry.masterPhyAddr += PAGE_SIZE_4KB;
        } while (currentEntrySize);

    }

    GT_1trace (curTrace, GT_LEAVE, "_OMAP5430BENELLI_halMmuAddEntry", status);

    /*! @retval PROCESSOR_SUCCESS Operation completed successfully. */
    return status;
}


/*!
 *  @brief      This function deletes an MMU entry for the specfied address and
 *              size.
 *
 *  @param      halObject   Pointer to the HAL object
 *  @param      slaveVirtAddr DSP virtual address of the memory region
 *  @param      size        Size of the memory region to be configured
 *  @param      isDynamic   Is the MMU entry being dynamically added?
 *
 *  @sa
 */
Int _OMAP5430BENELLI_halMmuDeleteEntry (OMAP5430BENELLI_HalObject * halObject,
                                        OMAP5430BENELLI_HalMmuEntryInfo * entry)
{
    Int                         status      = PROCESSOR_SUCCESS;
    OMAP5430BENELLI_HalMmuObject *     mmuObj;


    GT_2trace (curTrace, GT_ENTER, "_OMAP5430BENELLI_halMmuDeleteEntry",
               halObject, entry);

    GT_assert (curTrace, (halObject            != NULL));
    GT_assert (curTrace, (entry                != NULL));
    //GT_assert (curTrace, (entry->slaveVirtAddr != 0)); // 0 is a valid slave virtual addr
    GT_assert (curTrace, (entry->size          != 0));

    mmuObj = &(halObject->mmuObj);

    GT_1trace (curTrace, GT_LEAVE, "_OMAP5430BENELLI_halMmuDeleteEntry", status);

    /*! @retval PROCESSOR_SUCCESS Operation completed successfully. */
    return status;
}

static ULONG HAL_MMU_PteAddrL1(const ULONG L1_base, const ULONG va)
{
    ULONG TTB_13_to_7, VA_31_to_20, desc_13_to_0;

    TTB_13_to_7  = L1_base & (0x7FUL << 13);
    VA_31_to_20  = va >> (20 - 2); /* Left-shift by 2 here itself */
    desc_13_to_0 = (TTB_13_to_7 + VA_31_to_20) & (0xFFFUL << 2);

    return ( (L1_base & 0xFFFFC000) | desc_13_to_0 );
}

static ULONG HAL_MMU_PteAddrL2(const ULONG L2_base, const ULONG va)
{
    return ( (L2_base & 0xFFFFFC00) | ( (va >> 10) & 0x3FC ) );
}

#define OUTREG32(x, y)      WRITE_REGISTER_ULONG(x, (ULONG)(y))

int OMAP5430BENELLI_InternalMMU_PteSet (const ULONG        pgTblVa,
                                      struct iotlb_entry    *mapAttrs)
{
    Int status = 0;
    ULONG pteAddr, pteVal;
    Int  numEntries = 1;
    ULONG  physicalAddr = mapAttrs->pa;
    ULONG  virtualAddr  = mapAttrs->da;

    switch (mapAttrs->pgsz)
    {
    case MMU_CAM_PGSZ_4K:
        pteAddr = HAL_MMU_PteAddrL2(pgTblVa, virtualAddr & MMU_SMALL_PAGE_MASK);
        pteVal = ( (physicalAddr & MMU_SMALL_PAGE_MASK) |
                    (mapAttrs->endian << 9) |
                    (mapAttrs->elsz << 4) |
                    (mapAttrs->mixed << 11) | 2
                  );
        break;

    case MMU_CAM_PGSZ_64K:
        numEntries = 16;
        pteAddr = HAL_MMU_PteAddrL2(pgTblVa, virtualAddr & MMU_LARGE_PAGE_MASK);
        pteVal = ( (physicalAddr & MMU_LARGE_PAGE_MASK) |
                    (mapAttrs->endian << 9) |
                    (mapAttrs->elsz << 4) |
                    (mapAttrs->mixed << 11) | 1
                  );
        break;

    case MMU_CAM_PGSZ_1M:
        pteAddr = HAL_MMU_PteAddrL1(pgTblVa, virtualAddr & MMU_SECTION_ADDR_MASK);
        pteVal = ( ( ( (physicalAddr & MMU_SECTION_ADDR_MASK) |
                     (mapAttrs->endian << 15) |
                     (mapAttrs->elsz << 10) |
                     (mapAttrs->mixed << 17)) &
                     ~0x40000) | 0x2
                 );
        break;

    case MMU_CAM_PGSZ_16M:
        numEntries = 16;
        pteAddr = HAL_MMU_PteAddrL1(pgTblVa, virtualAddr & MMU_SSECTION_ADDR_MASK);
        pteVal = ( ( (physicalAddr & MMU_SSECTION_ADDR_MASK) |
                      (mapAttrs->endian << 15) |
                      (mapAttrs->elsz << 10) |
                      (mapAttrs->mixed << 17)
                    ) | 0x40000 | 0x2
                  );
        break;

    default:
        return -1;
    }

    while (--numEntries >= 0)
    {
#ifdef MMUTEST
        ((ULONG*)pteAddr)[numEntries] = pteVal;
#endif
    }

    return status;
}
/*!
 *  @brief      Updates entries in table.
 *
 *  @param      refData Argument provided to the ISR registration function
 *
 *  @sa
 */
Int
_OMAP5430BENELLI_halMmuPteSet (OMAP5430BENELLI_HalObject *      halObject,
                        OMAP5430BENELLI_HalMmuEntryInfo* setPteInfo)
{
    OMAP5430BENELLI_HalMmuObject *     mmuObj;
    struct iotlb_entry tlb_entry;
    Int    status = PROCESSOR_SUCCESS;
//    Commented as TRACEENTER log takes long time
//    GT_2trace (curTrace,
//               GT_ENTER,
//               "_OMAP5430BENELLI_halMmuPteSet",
//               halObject,
//               setPteInfo);

    GT_assert (curTrace, (halObject  != NULL));
    GT_assert (curTrace, (setPteInfo != NULL));

    mmuObj = &(halObject->mmuObj);
    GT_assert(curTrace, (mmuObj != NULL));

    switch (setPteInfo->size) {
        case PAGE_SIZE_16MB:
             tlb_entry.pgsz = MMU_CAM_PGSZ_16M;
             break;
        case PAGE_SIZE_1MB:
             tlb_entry.pgsz = MMU_CAM_PGSZ_1M;
             break;
        case PAGE_SIZE_64KB:
             tlb_entry.pgsz = MMU_CAM_PGSZ_64K;
             break;
        case PAGE_SIZE_4KB:
             tlb_entry.pgsz = MMU_CAM_PGSZ_4K;
             break;
        default :
            status = PROCESSOR_E_INVALIDARG;
            /*! @retval PROCESSOR_E_INVALIDARG Invalid Page size passed!. */
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_OMAP5430BENELLI_halMmuPteSet",
                                 status,
                                 "Invalid Page size passed!");
    }
#if !defined(IPC_BUILD_OPTIMIZE)
    if (status >= 0) {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        tlb_entry.prsvd  = MMU_CAM_PRESERVE;
        tlb_entry.valid  = MMU_CAM_VALID;
        /*TBD : elsz parameter has to be configured*/
        switch (setPteInfo->elementSize) {
            case ELEM_SIZE_8BIT:
                 tlb_entry.elsz = MMU_RAM_ELSZ_8;
                 break;
            case ELEM_SIZE_16BIT:
                 tlb_entry.elsz = MMU_RAM_ELSZ_16;
                 break;
            case ELEM_SIZE_32BIT:
                 tlb_entry.elsz = MMU_RAM_ELSZ_32;
                 break;
            case ELEM_SIZE_64BIT:
                 tlb_entry.elsz = 0x3; /* No translation */
                 break;
            default :
                status = PROCESSOR_E_INVALIDARG;
                /*! @retval PROCESSOR_E_INVALIDARG Invalid elementSize passed!*/
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_OMAP5430BENELLI_halMmuPteSet",
                                     status,
                                     "Invalid elementSize passed!");
        }
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status >= 0) {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            /*TBD : endian parameter has to configured*/
            switch (setPteInfo->endianism) {
                case LITTLE_ENDIAN:
                        tlb_entry.endian = MMU_RAM_ENDIAN_LITTLE;
                        break;
                case BIG_ENDIAN:
                        tlb_entry.endian = MMU_RAM_ENDIAN_BIG;
                        break;
                default :
                    status = PROCESSOR_E_INVALIDARG;
                    /*! @retval PROCESSOR_E_INVALIDARG Invalid endianism
                     *                                 passed!. */
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "_OMAP5430BENELLI_halMmuPteSet",
                                         status,
                                         "Invalid endianism passed!");
            }
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status >= 0) {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                /*TBD : mixed parameter has to configured*/
                switch (setPteInfo->mixedSize) {
                    case MMU_TLBES:
                            tlb_entry.mixed = MMU_RAM_DEFAULT;
                            break;
                    case MMU_CPUES:
                            tlb_entry.mixed = MMU_RAM_MIXED;
                            break;
                    default :
                        status = PROCESSOR_E_INVALIDARG;
                        /*! @retval PROCESSOR_E_INVALIDARG Invalid
                         *                                 mixed size passed!*/
                        GT_setFailureReason (curTrace,
                                             GT_4CLASS,
                                             "_OMAP5430BENELLI_halMmuPteSet",
                                             status,
                                             "Invalid mixed size passed!");
                }

                tlb_entry.da = setPteInfo->slaveVirtAddr;
                tlb_entry.pa = setPteInfo->masterPhyAddr;

                if (OMAP5430BENELLI_InternalMMU_PteSet(halObject->mmuBase, &tlb_entry)){
                    status = PROCESSOR_E_STOREENTERY;
                    GT_setFailureReason (curTrace,
                            GT_4CLASS,
                            "_OMAP5430BENELLI_halMmuPteSet",
                            status,
                            "iopgtable_store_entry failed!");
                }
#if !defined(IPC_BUILD_OPTIMIZE)
            }
        }
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

//    GT_1trace (curTrace, GT_LEAVE, "_OMAP5430BENELLI_halMmuPteSet", status);

    /*! @retval PROCESSOR_SUCCESS Operation completed successfully. */
    return status;
}



#if defined (__cplusplus)
}
#endif
