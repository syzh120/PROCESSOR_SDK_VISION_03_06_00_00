/*
 *  @file   VayuDspHalMmu.c
 *
 *  @brief      Hardware abstraction for Memory Management Unit module.
 *
 *              This module is responsible for handling slave MMU-related
 *              hardware- specific operations.
 *              The implementation is specific to VAYUDSP.
 *
 *
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



/* Standard headers */
#include <ti/syslink/Std.h>

/* OSAL and utils headers */
#include <ti/syslink/utils/List.h>
#include <ti/syslink/utils/Trace.h>
#include <ti/syslink/utils/OsalPrint.h>
#include <ti/syslink/utils/Memory.h>
#include <Bitops.h>

/* Module level headers */
#include <_ProcDefs.h>
#include <Processor.h>

/* Hardware Abstraction Layer headers */
#include <VAYUDspHal.h>
#include <VAYUDspHalMmu.h>
#include <VAYUDspPhyShmem.h>
#include <VAYUDspEnabler.h>
#include <MMUAccInt.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 * @brief Defines default mixedSize i.e same types of pages in one segment
 */
#define MMU_RAM_DEFAULT         0

#define MPU_INT_OFFSET               32

/*!
 *  @brief  Interrupt Id for DSP1 MMU faults
 */
#define MMU_FAULT_INTR_DSP1_MMU0     28

#define MMU_FAULT_INTR_DSP1_MMU1     143
#define MMU_XBAR_INTR_DSP1_MMU1      145

/*!
 *  @brief  Interrupt Id for DSP2 MMU faults
 */
#define MMU_FAULT_INTR_DSP2_MMU0     144
#define MMU_XBAR_INTR_DSP2_MMU0      146

#define MMU_FAULT_INTR_DSP2_MMU1     145
#define MMU_XBAR_INTR_DSP2_MMU1      147


/*!
 *  @brief  CAM register field values
 */
#define MMU_CAM_PRESERVE          (1 << 3)
#define MMU_CAM_VALID             (1 << 2)

#define IOPTE_SHIFT     12
#define IOPTE_SIZE      (1 << IOPTE_SHIFT)
#define IOPTE_MASK      (~(IOPTE_SIZE - 1))
#define IOPAGE_MASK     IOPTE_MASK

#define MMU_SECTION_ADDR_MASK    0xFFF00000
#define MMU_SSECTION_ADDR_MASK   0xFF000000
#define MMU_PAGE_TABLE_MASK      0xFFFFFC00
#define MMU_LARGE_PAGE_MASK      0xFFFF0000
#define MMU_SMALL_PAGE_MASK      0xFFFFF000

/*!
 * @brief returns page number based on physical address
 */
#define ti_ipc_phys_to_page(phys)      pfn_to_page((phys) >> PAGE_SHIFT)

/*!
 * @brief helper macros
 */
#define SLAVEVIRTADDR(x)  ((x)->addr [ProcMgr_AddrType_SlaveVirt])
#define SLAVEPHYSADDR(x)  ((x)->addr [ProcMgr_AddrType_SlavePhys])
#define MASTERPHYSADDR(x) ((x)->addr [ProcMgr_AddrType_MasterPhys])

#define MMUPAGE_ALIGN(size, psz)  (((size) + psz - 1) & ~(psz -1))

/*!
 *  @brief  offset in ctrl module to MMR LOCK reg.
 */
#define CTRL_MODULE_MMR_OFFSET           0x544

/*!
 *  @brief  offset in ctrl module to MPU INTs.
 */
#define CTRL_MODULE_MPU_OFFSET           0xA4C

/*!
 *  @brief  interrupt num at offset.
 */
#define CTRL_MODULE_INT_BASE             0x8

/*!
 *  @brief  interrupt num at offset.
 */
#define CTRL_MODULE_INT_m_OFFSET(m)      CTRL_MODULE_MPU_OFFSET + \
                                         ((((m) - CTRL_MODULE_INT_BASE) / 2) * 4) - \
                                         (((m) > 131) ? 4 : 0)

/*!
 *  @def    REG32
 *  @brief  Regsiter access method.
 */
#define REG32(x)        (*(volatile UInt32 *) (x))

/* =============================================================================
 *  Forward declarations of internal functions
 * =============================================================================
 */
/* Enables the MMU for GEM Module. */
Int _VAYUDSP_halMmuEnable (VAYUDSP_HalObject * halObject,
                            UInt32               numMemEntries,
                            ProcMgr_AddrInfo *   memTable);

/* Disables the MMU for GEM Module. */
Int _VAYUDSP_halMmuDisable (VAYUDSP_HalObject * halObject);

/* Add entry in TWL. */
Int
_VAYUDSP_halMmuAddEntry (VAYUDSP_HalObject       * halObject,
                          VAYUDSP_HalMmuEntryInfo * entry);
/* Add static entries in TWL. */
Int
_VAYUDSP_halMmuAddStaticEntries (VAYUDSP_HalObject * halObject,
                                  UInt32               numMemEntries,
                                  ProcMgr_AddrInfo *   memTable);

/* Delete entry from TLB. */
Int
_VAYUDSP_halMmuDeleteEntry (VAYUDSP_HalObject       * halObject,
                             VAYUDSP_HalMmuEntryInfo * entry);
/* Set entry in to TLB. */
Int
_VAYUDSP_halMmuPteSet (VAYUDSP_HalObject       * halObject,
                        VAYUDSP_HalMmuEntryInfo * setPteInfo);


/* =============================================================================
 * APIs called by VAYUDSPPROC module
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
VAYUDSP_halMmuCtrl (Ptr halObj, Processor_MmuCtrlCmd cmd, Ptr args)
{
    Int                  status     = PROCESSOR_SUCCESS;
    VAYUDSP_HalObject * halObject  = NULL;

    GT_3trace (curTrace, GT_ENTER, "VAYUDSP_halMmuCtrl", halObj, cmd, args);

    GT_assert (curTrace, (halObj != NULL));

    halObject = (VAYUDSP_HalObject *) halObj ;

    switch (cmd) {
        case Processor_MmuCtrlCmd_Enable:
        {
            VAYUDSP_HalMmuCtrlArgs_Enable * enableArgs;
            enableArgs = (VAYUDSP_HalMmuCtrlArgs_Enable *) args;
            halObject = (VAYUDSP_HalObject *) halObj;
            status = _VAYUDSP_halMmuEnable (halObject,
                                             enableArgs->numMemEntries,
                                             enableArgs->memEntries);

#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                /*! @retval PROCESSOR_E_FAIL Failed to configure DSP MMU. */
                status = PROCESSOR_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "VAYUDSP_halMmuCtrl",
                                     status,
                                     "Failed to configure DSP MMU"
                                     "at _VAYUDSP_halMmuEnable");
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
        break;

        case Processor_MmuCtrlCmd_Disable:
        {
            /* args are not used. */
            halObject = (VAYUDSP_HalObject *) halObj;
            status = _VAYUDSP_halMmuDisable (halObject);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                /*! @retval PROCESSOR_E_FAIL Failed to disable DSP MMU. */
                status = PROCESSOR_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "VAYUDSP_halMmuCtrl",
                                     status,
                                     "Failed to disable DSP MMU");
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
        break ;

        case Processor_MmuCtrlCmd_AddEntry:
        {
        }
        break;

        case Processor_MmuCtrlCmd_DeleteEntry:
        {
        }
        break;

        default:
        {
            /*! @retval PROCESSOR_E_INVALIDARG Invalid argument */
            status = PROCESSOR_E_INVALIDARG;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUDSP_halMmuCtrl",
                                 status,
                                 "Unsupported MMU ctrl cmd specified");
        }
        break;
    }

    GT_1trace (curTrace, GT_LEAVE, "VAYUDSP_halMmuCtrl",status);

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
_VAYUDSP_halMmuAddStaticEntries (VAYUDSP_HalObject * halObject,
                                  UInt32               numMemEntries,
                                  ProcMgr_AddrInfo *   memTable)
{
    Int                           status    = PROCESSOR_SUCCESS;
    VAYUDSP_HalMmuEntryInfo      staticEntry;
    UInt32                        i;

    GT_3trace (curTrace, GT_ENTER, "_VAYUDSP_halMmuAddStaticEntries",
               halObject, numMemEntries, memTable);

    GT_assert (curTrace, (halObject != NULL));
    /* It is possible that numMemEntries may be 0, if user does not want to
     * configure any default regions.
     * memTable may also be NULL.
     */

    for (i = 0 ; i < numMemEntries && (status >= 0) ; i++) {
        /* Configure the TLB */
        if (memTable [i].size != 0) {
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
            status = _VAYUDSP_halMmuAddEntry (halObject,
                                               &staticEntry);
            if (status < 0) {
                /*! @retval PROCESSOR_E_FAIL Failed to add MMU entry. */
                status = PROCESSOR_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_VAYUDSP_halMmuAddStaticEntries",
                                     status,
                                     "Failed to add MMU entry!");
            }
        }
    }
    GT_1trace (curTrace, GT_LEAVE, "_VAYUDSP_halMmuAddStaticEntries", status);

    /*! @retval PROCESSOR_SUCCESS Operation completed successfully. */
    return status ;
}


/*!
 *  @brief      Function to check and clear the remote proc interrupt
 *
 *  @param      arg     Optional argument to the function.
 *
 *  @sa         _VAYUDSP_halMmuInt_isr
 */
static
Bool
_VAYUDSP_halMmuCheckAndClearFunc (Ptr arg)
{
    VAYUDSP_HalObject * halObject = (VAYUDSP_HalObject *)arg;
    VAYUDSP_HalMmuObject * mmuObj = &(halObject->mmu0Obj);
    UInt32 mmuBase;

    /* Check the interrupt status */
    mmuObj->mmuIrqStatus = REG32(halObject->mmu0Base + MMU_MMU_IRQSTATUS_OFFSET);
    mmuObj->mmuIrqStatus &= MMU_IRQ_MASK;
    if (!(mmuObj->mmuIrqStatus)) {
        mmuObj = &(halObject->mmu1Obj);

        /* Check the interrupt status */
        mmuObj->mmuIrqStatus = REG32(halObject->mmu1Base + MMU_MMU_IRQSTATUS_OFFSET);
        mmuObj->mmuIrqStatus &= MMU_IRQ_MASK;
        if (!(mmuObj->mmuIrqStatus)) {
            return (FALSE);
        }
        else {
            mmuBase = halObject->mmu1Base;
            GT_0trace (curTrace, GT_4CLASS,
                       "****************** DSP-MMU1 Fault ******************");
        }
    }
    else {
        mmuBase = halObject->mmu0Base;
        GT_0trace (curTrace, GT_4CLASS,
                   "****************** DSP-MMU0 Fault ******************");
    }

    /* Get the fault address. */
    mmuObj->mmuFaultAddr = REG32(mmuBase + MMU_MMU_FAULT_AD_OFFSET);

    /* Print the fault information */
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
    REG32(mmuBase + MMU_MMU_IRQENABLE_OFFSET) = 0x0;
    REG32(mmuBase + MMU_MMU_IRQSTATUS_OFFSET) = mmuObj->mmuIrqStatus;

    /* This is not a shared interrupt, so interrupt has always occurred */
    /*! @retval TRUE Interrupt has occurred. */
    return (TRUE);
}

/*!
 *  @brief      Interrupt Service Routine for VAYUDSPHalMmu module
 *
 *  @param      arg     Optional argument to the function.
 *
 *  @sa         _VAYUDSP_halMmuCheckAndClearFunc
 */
static
Bool
_VAYUDSP_halMmuInt_isr (Ptr arg)
{
    VAYUDSP_HalObject * halObject = (VAYUDSP_HalObject *)arg;
    VAYUDSPPROC_Object * procObject = NULL;
    Int32 status;

    GT_1trace (curTrace, GT_ENTER, "_VAYUDSP_halMmuInt_isr", arg);
    status = VAYUDSPPROC_open((VAYUDSPPROC_Handle *)&procObject, halObject->procId);
    if (status >= 0) {
        Processor_setState(procObject->procHandle, ProcMgr_State_Mmu_Fault);
        VAYUDSPPROC_close((VAYUDSPPROC_Handle *)&procObject);
    }

    GT_1trace (curTrace, GT_LEAVE, "_VAYUDSP_halMmuInt_isr", TRUE);

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
_VAYUDSP_halMmuEnable (VAYUDSP_HalObject * halObject,
                       UInt32               numMemEntries,
                       ProcMgr_AddrInfo *   memTable)
{
    Int                           status    = PROCESSOR_SUCCESS;
    VAYUDSP_HalMmuObject *        mmu0Obj, *mmu1Obj;
    OsalIsr_Params                isrParams;
    UInt32                        reg = 0;
    UInt16                        dsp1ProcId = MultiProc_getId("DSP1");

    GT_3trace (curTrace, GT_ENTER, "_VAYUDSP_halMmuEnable",
               halObject, numMemEntries, memTable);

    GT_assert (curTrace, (halObject != NULL));
    /* It is possible that numMemEntries may be 0, if user does not want to
     * configure any default regions.
     * memTable may also be NULL.
     */
    mmu0Obj = &(halObject->mmu0Obj);
    mmu1Obj = &(halObject->mmu1Obj);

    /* Program the MMR lock registers to access the SCM
     * IRQ crossbar register address range */
    REG32(halObject->ctrlModBase + CTRL_MODULE_MMR_OFFSET) = 0xF757FDC0;

    /* Program the IntXbar */
    if (halObject->procId == dsp1ProcId) {
        reg = REG32(halObject->ctrlModBase + CTRL_MODULE_INT_m_OFFSET(MMU_FAULT_INTR_DSP1_MMU1));
        if ((MMU_FAULT_INTR_DSP1_MMU1 - CTRL_MODULE_INT_BASE) % 2) {
            REG32(halObject->ctrlModBase + CTRL_MODULE_INT_m_OFFSET(MMU_FAULT_INTR_DSP1_MMU1)) =
                (reg & 0x0000FFFF) | (MMU_XBAR_INTR_DSP1_MMU1 << 16);
        }
        else {
            REG32(halObject->ctrlModBase + CTRL_MODULE_INT_m_OFFSET(MMU_FAULT_INTR_DSP1_MMU1)) =
                (reg & 0xFFFF0000) | (MMU_XBAR_INTR_DSP1_MMU1);
        }
    }
    else {
        reg = REG32(halObject->ctrlModBase + CTRL_MODULE_INT_m_OFFSET(MMU_FAULT_INTR_DSP2_MMU0));
        if ((MMU_FAULT_INTR_DSP2_MMU0 - CTRL_MODULE_INT_BASE) % 2) {
            REG32(halObject->ctrlModBase + CTRL_MODULE_INT_m_OFFSET(MMU_FAULT_INTR_DSP2_MMU0)) =
                (reg & 0x0000FFFF) | (MMU_XBAR_INTR_DSP2_MMU0 << 16);
        }
        else {
            REG32(halObject->ctrlModBase + CTRL_MODULE_INT_m_OFFSET(MMU_FAULT_INTR_DSP2_MMU0)) =
                (reg & 0xFFFF0000) | (MMU_XBAR_INTR_DSP2_MMU0);
        }

        reg = REG32(halObject->ctrlModBase + CTRL_MODULE_INT_m_OFFSET(MMU_FAULT_INTR_DSP2_MMU1));
        if ((MMU_FAULT_INTR_DSP2_MMU1 - CTRL_MODULE_INT_BASE) % 2) {
            REG32(halObject->ctrlModBase + CTRL_MODULE_INT_m_OFFSET(MMU_FAULT_INTR_DSP2_MMU1)) =
                (reg & 0x0000FFFF) | (MMU_XBAR_INTR_DSP2_MMU1 << 16);
        }
        else {
            REG32(halObject->ctrlModBase + CTRL_MODULE_INT_m_OFFSET(MMU_FAULT_INTR_DSP2_MMU1)) =
                (reg & 0xFFFF0000) | (MMU_XBAR_INTR_DSP2_MMU1);
        }
    }

    /* Create the ISR to listen for MMU Faults */
    isrParams.sharedInt        = FALSE;
    isrParams.checkAndClearFxn = &_VAYUDSP_halMmuCheckAndClearFunc;
    isrParams.fxnArgs          = halObject;
    isrParams.intId            = (dsp1ProcId == halObject->procId ?
        MMU_FAULT_INTR_DSP1_MMU0 + MPU_INT_OFFSET: MMU_FAULT_INTR_DSP2_MMU0 + MPU_INT_OFFSET);
    mmu0Obj->isrHandle = OsalIsr_create (&_VAYUDSP_halMmuInt_isr,
                                        halObject,
                                        &isrParams);
    isrParams.intId            = (dsp1ProcId == halObject->procId ?
        MMU_FAULT_INTR_DSP1_MMU1 + MPU_INT_OFFSET: MMU_FAULT_INTR_DSP2_MMU1+ MPU_INT_OFFSET);
    mmu1Obj->isrHandle = OsalIsr_create (&_VAYUDSP_halMmuInt_isr,
                                        halObject,
                                        &isrParams);

#if !defined(IPC_BUILD_OPTIMIZE)
    if (mmu0Obj->isrHandle == NULL || mmu1Obj->isrHandle == NULL) {
        /*! @retval PROCESSOR_E_FAIL OsalIsr_create failed */
        status = PROCESSOR_E_FAIL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_VAYUDSP_halMmuEnable",
                             status,
                             "OsalIsr_create failed");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        status = OsalIsr_install (mmu0Obj->isrHandle);

#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_VAYUDSP_halMmuEnable",
                                 status,
                                 "OsalIsr_install failed");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

            status = OsalIsr_install (mmu1Obj->isrHandle);

#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_VAYUDSP_halMmuEnable",
                                     status,
                                     "OsalIsr_install failed");
            }
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        if ((status >= 0) && (numMemEntries != 0)) {
            GT_1trace(curTrace, GT_4CLASS, "_VAYUDSP_halMmuEnable: adding %d entries...", numMemEntries);

            /* Only statically created entries are being added here. */
            status = _VAYUDSP_halMmuAddStaticEntries(halObject,
                                                     numMemEntries,
                                                     memTable);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                /*! @retval PROCESSOR_E_FAIL Failed at
                 *                         _VAYUDSP_halMmuAddStaticEntries. */
                status = PROCESSOR_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_VAYUDSP_halMmuEnable",
                                     status,
                                     "_VAYUDSP_halMmuAddStaticEntries failed !");
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "_VAYUDSP_halMmuEnable", status);

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
_VAYUDSP_halMmuDisable (VAYUDSP_HalObject * halObject)
{
    Int                        status    = PROCESSOR_SUCCESS;
    Int                        tmpStatus = PROCESSOR_SUCCESS;
    VAYUDSP_HalMmuObject *     mmu0Obj, *mmu1Obj;

    GT_1trace (curTrace, GT_ENTER, "_VAYUDSP_halMmuDisable", halObject);

    GT_assert (curTrace, (halObject != NULL));
    mmu0Obj = &(halObject->mmu0Obj);
    mmu1Obj = &(halObject->mmu1Obj);

    status = OsalIsr_uninstall (mmu0Obj->isrHandle);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_VAYUDSP_halMmuDisable",
                             status,
                             "OsalIsr_uninstall failed");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    status = OsalIsr_uninstall (mmu1Obj->isrHandle);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_VAYUDSP_halMmuDisable",
                             status,
                             "OsalIsr_uninstall failed");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

#if !defined(IPC_BUILD_OPTIMIZE)
    tmpStatus =
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        OsalIsr_delete (&(mmu0Obj->isrHandle));
#if !defined(IPC_BUILD_OPTIMIZE)
    if ((status >= 0) && (tmpStatus < 0)) {
        status = tmpStatus;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_VAYUDSP_halMmuDisable",
                             status,
                             "OsalIsr_delete failed");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

#if !defined(IPC_BUILD_OPTIMIZE)
    tmpStatus =
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        OsalIsr_delete (&(mmu1Obj->isrHandle));
#if !defined(IPC_BUILD_OPTIMIZE)
    if ((status >= 0) && (tmpStatus < 0)) {
        status = tmpStatus;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_VAYUDSP_halMmuDisable",
                             status,
                             "OsalIsr_delete failed");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "_VAYUDSP_halMmuDisable", status);

    /*! @retval PROCESSOR_SUCCESS Operation completed successfully. */
    return status;
}


/*!
 *  @brief      This function adds an MMU entry for the specfied address and
 *              size.
 *
 *  @param      halObject   Pointer to the HAL object
 *  @param      entry       entry to be added
 *
 *  @sa
 */
Int
_VAYUDSP_halMmuAddEntry (VAYUDSP_HalObject       * halObject,
                         VAYUDSP_HalMmuEntryInfo * entry)
{
    Int                         status = PROCESSOR_SUCCESS;
    UInt32  *                   ppgd = NULL;
    UInt32  *                   ppte = NULL;
    VAYUDSP_HalMmuEntryInfo     te;
    VAYUDSP_HalMmuEntryInfo     currentEntry;
    Int32                       currentEntrySize;

    GT_2trace (curTrace, GT_ENTER, "_VAYUDSP_halMmuAddEntry",
               halObject, entry);

    GT_assert (curTrace, (halObject != NULL));
    GT_assert (curTrace, (entry     != NULL));

    /* Add the entry (or entries) */
    Memory_copy(&currentEntry,
                entry,
                sizeof(VAYUDSP_HalMmuEntryInfo));

    /* Align the addresses to page size */
    currentEntry.size += (currentEntry.slaveVirtAddr & (PAGE_SIZE_4KB -1));
    currentEntry.slaveVirtAddr &= ~(PAGE_SIZE_4KB-1);
    currentEntry.masterPhyAddr &= ~(PAGE_SIZE_4KB-1);

    /* Align the size as well */
    currentEntry.size = MMUPAGE_ALIGN(currentEntry.size, PAGE_SIZE_4KB);
    currentEntrySize = currentEntry.size;

    /* To find the max. page size with which both PA & VA are
     * aligned */
    while ((currentEntrySize != 0) &&
           (status >= 0)) {
        if (currentEntrySize >= PAGE_SIZE_16MB
            && !(currentEntry.slaveVirtAddr & (PAGE_SIZE_16MB - 1))) {
            currentEntry.size = PAGE_SIZE_16MB;
        }
        else if (currentEntrySize >= PAGE_SIZE_1MB
                 && !(currentEntry.slaveVirtAddr & (PAGE_SIZE_1MB - 1))) {
            currentEntry.size = PAGE_SIZE_1MB;
        }
        else if (currentEntrySize >= PAGE_SIZE_64KB
                 && !(currentEntry.slaveVirtAddr & (PAGE_SIZE_64KB - 1))){
            currentEntry.size = PAGE_SIZE_64KB;
        }
        else  if (currentEntrySize >= PAGE_SIZE_4KB
                 && !(currentEntry.slaveVirtAddr & (PAGE_SIZE_4KB - 1))){
            currentEntry.size = PAGE_SIZE_4KB;
        }
        else {
            Osal_printf ("Configuration error: "
                         " MMU entries must be aligned to their"
                         "page size(4KB,"
                         " 64KB, 1MB, or 16MB).\n");
            Osal_printf ("Since the addresses are not aligned buffer"
                         "of size: %x at address: %x cannot be  "
                         "TLB entries\n",
                       currentEntrySize, currentEntry.slaveVirtAddr);
            /*! @retval VAYUDSPPROC_E_MMUCONFIG Memory region is not
                                                 aligned to page size */
            status = VAYUDSPPROC_E_MMUCONFIG;
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "_VAYUDSP_halMmuAddEntry",
                               status,
                          "Memory region is not aligned to page size!");
            break ;
        }

        /* DO NOT put this check under IPC_BUILD_OPTIMIZE */
        if (status >= 0) {
            /* Lookup if the entry exists */
            if (1) {//(!*ppgd || !*ppte) {
                /* Entry doesnot exists, insert this page */
                te.size = currentEntry.size;
                te.slaveVirtAddr = currentEntry.slaveVirtAddr;
                te.masterPhyAddr = currentEntry.masterPhyAddr;
                te.elementSize   = currentEntry.elementSize;
                te.endianism     = currentEntry.endianism;
                te.mixedSize     = currentEntry.mixedSize;
                status = _VAYUDSP_halMmuPteSet (halObject, &te);
            }
            else if (ppgd && ppte) {
                if (currentEntry.masterPhyAddr != (*ppte & IOPAGE_MASK)) {
                    /* Entry doesnot exists, insert this page */
                    te.size = currentEntry.size;
                    te.slaveVirtAddr = currentEntry.slaveVirtAddr;
                    te.masterPhyAddr = currentEntry.masterPhyAddr;
                    te.elementSize   = currentEntry.elementSize;
                    te.endianism     = currentEntry.endianism;
                    te.mixedSize     = currentEntry.mixedSize;
                    status = _VAYUDSP_halMmuPteSet (halObject, &te);
                }
            }

#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                GT_setFailureReason (
                                curTrace,
                                GT_4CLASS,
                                "_VAYUDSP_halMmuAddEntry",
                                status,
                                "Failed to in _VAYUDSP_halMmuPteSet!");
                break;
            }
            else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                currentEntrySize           -= currentEntry.size;
                currentEntry.masterPhyAddr += currentEntry.size;
                currentEntry.slaveVirtAddr += currentEntry.size;
#if !defined(IPC_BUILD_OPTIMIZE)
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }

    GT_1trace (curTrace, GT_LEAVE, "_VAYUDSP_halMmuAddEntry", status);

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
Int
_VAYUDSP_halMmuDeleteEntry (VAYUDSP_HalObject       * halObject,
                            VAYUDSP_HalMmuEntryInfo * entry)
{
    Int                         status      = PROCESSOR_SUCCESS;
    UInt32 *                    iopgd       = NULL;
    UInt32                      currentEntrySize;
    VAYUDSP_HalMmuEntryInfo     currentEntry;
    //UInt32                      clearBytes = 0;

    GT_2trace (curTrace, GT_ENTER, "_VAYUDSP_halMmuDeleteEntry",
               halObject, entry);

    GT_assert (curTrace, (halObject            != NULL));
    GT_assert (curTrace, (entry                != NULL));
    GT_assert (curTrace, (entry->size          != 0));

    /* Add the entry (or entries) */
    Memory_copy(&currentEntry,
                entry,
                sizeof(VAYUDSP_HalMmuEntryInfo));

    /* Align the addresses to page size */
    currentEntry.size += (currentEntry.slaveVirtAddr & (PAGE_SIZE_4KB -1));
    currentEntry.slaveVirtAddr &= ~(PAGE_SIZE_4KB-1);

    /* Align the size as well */
    currentEntry.size = MMUPAGE_ALIGN(currentEntry.size, PAGE_SIZE_4KB);
    currentEntrySize = currentEntry.size;

    /* To find the max. page size with which both PA & VA are
     * aligned */
    while ((currentEntrySize != 0)
            && (status >= 0)) {
        if (currentEntrySize >= PAGE_SIZE_16MB
            && !(currentEntry.slaveVirtAddr & (PAGE_SIZE_16MB - 1))) {
            currentEntry.size = PAGE_SIZE_16MB;
        }
        else if (currentEntrySize >= PAGE_SIZE_1MB
                 && !(currentEntry.slaveVirtAddr & (PAGE_SIZE_1MB - 1))) {
            currentEntry.size = PAGE_SIZE_1MB;
        }
        else if (currentEntrySize >= PAGE_SIZE_64KB
                 && !(currentEntry.slaveVirtAddr & (PAGE_SIZE_64KB - 1))){
            currentEntry.size = PAGE_SIZE_64KB;
        }
        else  if (currentEntrySize >= PAGE_SIZE_4KB
                 && !(currentEntry.slaveVirtAddr & (PAGE_SIZE_4KB - 1))){
            currentEntry.size = PAGE_SIZE_4KB;
        }
        else {
            Osal_printf ("Configuration error: "
                         " MMU entries must be aligned to their"
                         "page size(4KB,"
                         " 64KB, 1MB, or 16MB).\n");
            Osal_printf ("Since the addresses are not aligned buffer"
                         "of size: %x at address: %x cannot be  "
                         "TLB entries\n",
                       currentEntrySize, currentEntry.slaveVirtAddr);
            /*! @retval VAYUDSPPROC_E_MMUCONFIG Memory region is not
                                                 aligned to page size */
            status = VAYUDSPPROC_E_MMUCONFIG;
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "_VAYUDSP_halMmuAddEntry",
                               status,
                          "Memory region is not aligned to page size!");
            break ;
        }
        /* DO NOT put this check under IPC_BUILD_OPTIMIZE */
        if (status >= 0) {
            /* Check every page if exists */
            //iopgd = iopgd_offset(mmuObj->dspMmuHandler,
            //                     currentEntry.slaveVirtAddr);

            if (*iopgd) {
                /* Clear the requested page entry */
                //clearBytes = iopgtable_clear_entry(mmuObj->dspMmuHandler,
                //                      currentEntry.slaveVirtAddr);
            }

            currentEntry.slaveVirtAddr += currentEntry.size;
            currentEntrySize           -= currentEntry.size;
        }
    }

    GT_1trace (curTrace, GT_LEAVE, "_VAYUDSP_halMmuDeleteEntry", status);

    /*! @retval PROCESSOR_SUCCESS Operation completed successfully. */
    return status;
}


#ifdef MMUTEST
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
#endif

#define OUTREG32(x, y)      WRITE_REGISTER_ULONG(x, (ULONG)(y))

int VAYUDSP_InternalMMU_PteSet (const ULONG        pgTblVa,
                                      struct iotlb_entry    *mapAttrs)
{
    Int status = 0;
#ifdef MMUTEST
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
        ((ULONG*)pteAddr)[numEntries] = pteVal;
    }
#endif

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
_VAYUDSP_halMmuPteSet (VAYUDSP_HalObject *      halObject,
                       VAYUDSP_HalMmuEntryInfo* setPteInfo)
{
    VAYUDSP_HalMmuObject *     mmu0Obj, *mmu1Obj;
    struct iotlb_entry tlb_entry;
    Int    status = PROCESSOR_SUCCESS;

    GT_assert (curTrace, (halObject  != NULL));
    GT_assert (curTrace, (setPteInfo != NULL));

    mmu0Obj = &(halObject->mmu0Obj);
    GT_assert(curTrace, (mmu0Obj != NULL));
    mmu1Obj = &(halObject->mmu1Obj);
    GT_assert(curTrace, (mmu1Obj != NULL));

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
                                 "_VAYUDSP_halMmuPteSet",
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
                                     "_VAYUDSP_halMmuPteSet",
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
                                         "_VAYUDSP_halMmuPteSet",
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
                                             "_VAYUDSP_halMmuPteSet",
                                             status,
                                             "Invalid mixed size passed!");
                }

                tlb_entry.da = setPteInfo->slaveVirtAddr;
                tlb_entry.pa = setPteInfo->masterPhyAddr;

                if (VAYUDSP_InternalMMU_PteSet(halObject->mmu0Base, &tlb_entry)){
                    status = PROCESSOR_E_STOREENTERY;
                    GT_setFailureReason (curTrace,
                            GT_4CLASS,
                            "_VAYUDSP_halMmuPteSet",
                            status,
                            "iopgtable_store_entry failed!");
                }
                if (VAYUDSP_InternalMMU_PteSet(halObject->mmu1Base, &tlb_entry)){
                    status = PROCESSOR_E_STOREENTERY;
                    GT_setFailureReason (curTrace,
                            GT_4CLASS,
                            "_VAYUDSP_halMmuPteSet",
                            status,
                            "iopgtable_store_entry failed!");
                }
#if !defined(IPC_BUILD_OPTIMIZE)
            }
        }
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

//    GT_1trace (curTrace, GT_LEAVE, "_VAYUDSP_halMmuPteSet", status);

    /*! @retval PROCESSOR_SUCCESS Operation completed successfully. */
    return status;
}


#if defined (__cplusplus)
}
#endif
