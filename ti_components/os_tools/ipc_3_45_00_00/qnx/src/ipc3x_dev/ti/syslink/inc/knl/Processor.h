/**
 *  @file   Processor.h
 *
 *  @brief      Header file for the generic Processor implementation.
 *
 *
 *  @ver        02.00.00.46_alpha1
 *
 *  ============================================================================
 *
 *  Copyright (c) 2008-2014, Texas Instruments Incorporated
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


#ifndef Processor_H_0x6a85
#define Processor_H_0x6a85


/* Module level headers */
#include <ProcDefs.h>


#if defined (__cplusplus)
extern "C" {
#endif




/*!
 *  @def    PROCESSOR_MODULEID
 *  @brief  Module ID for loader.
 */
#define PROCESSOR_MODULEID           (UInt16) 0x6a85

/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */

/*!
 *  @def    PROCESSOR_STATUSCODEBASE
 *  @brief  Error code base for ProcMgr.
 */
#define PROCESSOR_STATUSCODEBASE      (PROCESSOR_MODULEID << 12u)

/*!
 *  @def    PROCESSOR_MAKE_FAILURE
 *  @brief  Macro to make failure code.
 */
#define PROCESSOR_MAKE_FAILURE(x)    ((Int)(  0x80000000                       \
                                            | (PROCESSOR_STATUSCODEBASE + (x))))

/*!
 *  @def    PROCESSOR_MAKE_SUCCESS
 *  @brief  Macro to make success code.
 */
#define PROCESSOR_MAKE_SUCCESS(x)    (PROCESSOR_STATUSCODEBASE + (x))

/*!
 *  @def    PROCESSOR_E_INVALIDARG
 *  @brief  Argument passed to a function is invalid.
 */
#define PROCESSOR_E_INVALIDARG       PROCESSOR_MAKE_FAILURE(1)

/*!
 *  @def    PROCESSOR_E_MEMORY
 *  @brief  Memory allocation failed.
 */
#define PROCESSOR_E_MEMORY           PROCESSOR_MAKE_FAILURE(2)

/*!
 *  @def    PROCESSOR_E_FAIL
 *  @brief  Generic failure.
 */
#define PROCESSOR_E_FAIL             PROCESSOR_MAKE_FAILURE(3)

/*!
 *  @def    PROCESSOR_E_NOTSUPPORTED
 *  @brief  Functionality is not supported
 */
#define PROCESSOR_E_NOTSUPPORTED     PROCESSOR_MAKE_FAILURE(4)

/*!
 *  @def    PROCESSOR_E_NOTIMPL
 *  @brief  Functionality is not implemented
 */
#define PROCESSOR_E_NOTIMPL          PROCESSOR_MAKE_FAILURE(5)

/*!
 *  @def    PROCESSOR_E_INIT
 *  @brief  A required dependency has not been initialized
 */
#define PROCESSOR_E_INIT             PROCESSOR_MAKE_FAILURE(6)

/*!
 *  @def    PROCESSOR_E_ALREADYEXIST
 *  @brief  Specified loader name already exists.
 */
#define PROCESSOR_E_ALREADYEXIST     PROCESSOR_MAKE_FAILURE(7)

/*!
 *  @def    PROCESSOR_E_HANDLE
 *  @brief  Invalid object handle specified
 */
#define PROCESSOR_E_HANDLE           PROCESSOR_MAKE_FAILURE(8)

/*!
 *  @def    PROCESSOR_E_NOTFOUND
 *  @brief  Specified Processor not found.
 */
#define PROCESSOR_E_NOTFOUND         PROCESSOR_MAKE_FAILURE(0x9)

/*!
 *  @def    PROCESSOR_E_LIST
 *  @brief  A list error occurred.
 */
#define PROCESSOR_E_LIST             PROCESSOR_MAKE_FAILURE(0xA)

/*!
 *  @def    PROCESSOR_E_TRANSLATE
 *  @brief  Failed in address translation
 */
#define PROCESSOR_E_TRANSLATE        PROCESSOR_MAKE_FAILURE(0xB)

/*!
 *  @def    PROCESSOR_E_ACCESSDENIED
 *  @brief  Access denied for specified operation
 */
#define PROCESSOR_E_ACCESSDENIED     PROCESSOR_MAKE_FAILURE(0xC)

/*!
 *  @def    PROCESSOR_E_OSFAILURE
 *  @brief  Failure in an OS-specific operation.
 */
#define PROCESSOR_E_OSFAILURE        PROCESSOR_MAKE_FAILURE(0xD)
/*!
 *  @def    PROCESSOR_E_OSFAILURE
 *  @brief  Failure in an iommu operation.
 */
#define PROCESSOR_E_STOREENTERY      PROCESSOR_MAKE_FAILURE(0xE)

/*!
 *  @def    PROCESSOR_E_INVALIDSTATE
 *  @brief  Invalid state transition.
 */
#define PROCESSOR_E_INVALIDSTATE     PROCESSOR_MAKE_FAILURE(0xF)

/*!
 *  @def    PROCESSOR_SUCCESS
 *  @brief  Operation successful.
 */
#define PROCESSOR_SUCCESS            PROCESSOR_MAKE_SUCCESS(0)

/* =============================================================================
 *  Macros and types
 *  See ProcDefs.h
 * =============================================================================
 */

/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Function to attach to the Processor. */
Int Processor_attach (Processor_Handle handle, Processor_AttachParams * params);

/* Function to detach from the Processor. */
Int Processor_detach (Processor_Handle handle);

/* Function to start the processor. */
Int Processor_start (Processor_Handle        handle,
                     UInt32                  entryPt,
                     Processor_StartParams * params);

/* Function to stop the processor. */
Int Processor_stop (Processor_Handle handle);

/* Function to read from the slave processor's memory. */
Int Processor_read (Processor_Handle handle,
                    UInt32           procAddr,
                    UInt32 *         numBytes,
                    Ptr              buffer);

/* Function to read write into the slave processor's memory. */
Int Processor_write (Processor_Handle handle,
                     UInt32           procAddr,
                     UInt32 *         numBytes,
                     Ptr              buffer);

/* Function to get the current state of the slave Processor as maintained on
 * the master Processor state machine.
 */
ProcMgr_State Processor_getState (Processor_Handle handle);

/* Function to set the current state of the slave Processor to specified value.
 */
Void Processor_setState (Processor_Handle handle, ProcMgr_State state);

/* Function to perform device-dependent operations. */
Int Processor_control (Processor_Handle handle, Int32 cmd, Ptr arg);

/* Function to translate between two types of address spaces. */
Int Processor_translateAddr (Processor_Handle handle,
                             UInt32 *         dstAddr,
                             UInt32           srcAddr)
;

/* Function to translate slave virtual address to physical using page table */
Int Processor_translateFromPte (Processor_Handle handle,
                                UInt32 *         dstAddr,
                                UInt32           srcAddr)
;

/* Function to map address to slave address space */
Int Processor_map (Processor_Handle handle,
                   UInt32 *         dstAddr,
                   UInt32           nSegs,
                   Memory_SGList *  sglist);

/* Function to unmap address from slave address space */
Int Processor_unmap (Processor_Handle handle,
                     UInt32           slaveVirtAddr,
                     UInt32           size);

/* Function that registers for notification when the slave processor
 * transitions to any of the states specified.
 */
Int Processor_registerNotify (Processor_Handle    handle,
                              ProcMgr_CallbackFxn fxn,
                              Ptr                 args,
                              Int                 timeout,
                              ProcMgr_State       state []);

/* Function that un-registers for notification when the slave processor
 * transitions to any of the states specified.
 */
Int Processor_unregisterNotify (Processor_Handle    handle,
                                ProcMgr_CallbackFxn fxn,
                                Ptr                 args,
                                ProcMgr_State       state []);

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* Processor_H_0x6a85 */
