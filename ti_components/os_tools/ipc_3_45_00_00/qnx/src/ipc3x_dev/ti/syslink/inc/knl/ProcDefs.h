/**
 *  @file   ProcDefs.h
 *
 *  @brief      Definitions for the Processor interface.
 *
 *
 *  @ver        02.00.00.46_alpha1
 *
 *  ============================================================================
 *
 *  Copyright (c) 2008-2015, Texas Instruments Incorporated
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


#ifndef ProcDefs_H_0x6a85
#define ProcDefs_H_0x6a85


/* Osal & Utils headers */
#include <ti/syslink/utils/Memory.h>
#include <ti/syslink/utils/List.h>
#include <OsalMutex.h>

/* Module level headers */
#include <ti/ipc/MultiProc.h>
#include <ti/syslink/ProcMgr.h>
#include <ti/syslink/SysLink.h>

#include <pthread.h>

#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief   Enumerates the types of Endianism of slave processor.
 */
typedef enum {
    Processor_Endian_Default  = 0u,
    /*!< Default endianism (no conversion required) */
    Processor_Endian_Big      = 1u,
    /*!< Big endian */
    Processor_Endian_Little   = 2u,
    /*!< Little endian */
    Processor_Endian_EndValue = 3u
    /*!< End delimiter indicating start of invalid values for this enum */
} Processor_Endian;

/*!
 *  @brief   Enumerates the various architectures of processor supported.
 */
typedef enum {
    Processor_ProcArch_Unknown       = 0u,
    /* !< Indicates that the architecture is not supported. */
    Processor_ProcArch_C55x          = 1u,
    /* !< Indicates that the architecture is C55x. */
    Processor_ProcArch_C64x          = 2u,
    /* !< Indicates that the architecture is C64x. */
    Processor_ProcArch_M3            = 3u,
    /* !< Indicates that the architecture is CORTEX M3. */
    Processor_ProcArch_M4            = 4u,
    /* !< Indicates that the architecture is CORTEX M4. */
    Processor_ProcArch_C66x          = 5u,
    /* !< Indicates that the architecture is C66x. */
    Processor_ProcArch_EndValue      = 6u
    /*!< End delimiter indicating start of invalid values for this enum */
} Processor_ProcArch;


/*!
 *  @brief  Configuration parameters for attaching to the slave Processor
 */
typedef struct Processor_AttachParams_tag {
    ProcMgr_AttachParams * params;
    /*!< Common attach parameters for ProcMgr */
    UInt16                 numMemEntries;
    /*!< Number of valid memory entries */
    ProcMgr_AddrInfo       memEntries [ProcMgr_MAX_MEMORY_REGIONS];
    /*!< Configuration of memory regions */
    Processor_ProcArch     procArch;
    /*!< Processor architecture */
    ProcMgr_Handle         pmHandle;
    /*!< Handle to proc manager */
    Ipc_MemoryMap        * sysMemMap;
    /*!< System Memory map to be added to translation table */
} Processor_AttachParams ;

/*!
 *  @brief  Configuration parameters for starting the slave Processor
 */
typedef struct Processor_StartParams_tag {
    ProcMgr_StartParams * params;
    /*!< Common start parameters for ProcMgr */
} Processor_StartParams ;


/* Forward declaration for Processor_Object */
typedef struct Processor_Object_tag Processor_Object;

/*!
 *  @brief  Defines Processor object handle
 */
typedef Processor_Object * Processor_Handle;

/*!
 *  @brief  Args type for Processor_MmuCtrlCmd_Register
 */
typedef struct Processor_Register_tag {
    Int32               timeout;
    /*!< Timeout. */
    ProcMgr_CallbackFxn cbFxn;
    /*!< Client callback function. */
    Ptr                 arg;
    /*!< Client arg to pass to the callback function. */
    ProcMgr_State       state[];
    /*!< States registered for notification. */
} Processor_Register;

/*!
 *  @brief  List element for registered fault listeners.
 */
typedef struct Processor_RegisterElem_tag {
    List_Elem                              elem;
    /*!< List Elem. */
    Processor_Register                   * info;
    /*!< Information about the registered client. */
    timer_t                                timer;
    /*!< Timer handle. */
    UInt16                                 procId;
    /*!< ProcId associated with elem */
} Processor_RegisterElem;

/* =============================================================================
 *  Function pointer types
 * =============================================================================
 */
/*!
 *  @brief  Function pointer type for the function to attach to the processor.
 */
typedef Int (*Processor_AttachFxn) (Processor_Handle         handle,
                                    Processor_AttachParams * params);

/*!
 *  @brief  Function pointer type for the function to detach from the
 *          procssor
 */
typedef Int (*Processor_DetachFxn) (Processor_Handle handle);

/*!
 *  @brief  Function pointer type for the function to start the processor.
 */
typedef Int (*Processor_StartFxn) (Processor_Handle        handle,
                                   UInt32                  entryPt,
                                   Processor_StartParams * params);

/*!
 *  @brief  Function pointer type for the function to stop the processor.
 */
typedef Int (*Processor_StopFxn) (Processor_Handle handle);

/*!
 *  @brief  Function pointer type for the function to read from the slave
 *          processor's memory.
 */
typedef Int (*Processor_ReadFxn) (Processor_Handle handle,
                                  UInt32           procAddr,
                                  UInt32 *         numBytes,
                                  Ptr              buffer);

/*!
 *  @brief  Function pointer type for the function to write into the slave
 *          processor's memory.
 */
typedef Int (*Processor_WriteFxn) (Processor_Handle   handle,
                                   UInt32             procAddr,
                                   UInt32 *           numBytes,
                                   Ptr                buffer);

/*!
 *  @brief  Function pointer type for the function to perform device-dependent
 *          operations.
 */
typedef Int (*Processor_ControlFxn) (Processor_Handle handle,
                                     Int32            cmd,
                                     Ptr              arg);

/*!
 *  @brief  Function pointer type for the function to translate between
 *          two types of address spaces.
 */
typedef Int (*Processor_TranslateAddrFxn) (Processor_Handle handle,
                                           UInt32 *         dstAddr,
                                           UInt32           srcAddr);

/*!
 *  @brief  Function pointer type for the function to map address to slave
 *          address space
 */
typedef Int (*Processor_MapFxn) (Processor_Handle handle,
                                 UInt32 *         dstAddr,
                                 UInt32           nSegs,
                                 Memory_SGList *  sglist);

/*!
 *  @brief  Function pointer type for the function to unmap address from slave
 *          address space
 */
typedef Int (*Processor_UnmapFxn) (Processor_Handle handle,
                                   UInt32           addr,
                                   UInt32           size);

/*!
 *  @brief  Function pointer type for the function that returns proc info
 */
typedef Int (*Processor_GetProcInfoFxn) (Processor_Handle   handle,
                                         ProcMgr_ProcInfo * procInfo);

/*!
 *  @brief  Function pointer type for the function that returns phys addr
 */
typedef Int (*Processor_VirtToPhysFxn) (Processor_Handle handle,
                                        UInt32           ba,
                                        UInt32 *         mappedEntries,
                                        UInt32           numOfEntries);

/*!
 *  @brief  Function pointer type for the function to register for event notification.
 */
typedef Int (*Processor_RegisterNotifyFxn) (Processor_Handle    handle,
                                            ProcMgr_CallbackFxn cbFxn,
                                            Ptr                 arg,
                                            Int32               timeout,
                                            ProcMgr_State       state []);

/*!
 *  @brief  Function pointer type for the function to un-register for event notification.
 */
typedef Int (*Processor_UnRegisterNotifyFxn) (Processor_Handle    handle,
                                              ProcMgr_CallbackFxn cbFxn,
                                              Ptr                 arg,
                                              ProcMgr_State       state []);

/*!
 *  @brief  Function pointer type for the function to translate between
 *          two types of address spaces.
 */
typedef Int (*Processor_TranslateFromPteFxn) (Processor_Handle handle,
                                              UInt32 *         dstAddr,
                                              UInt32           srcAddr);

/* =============================================================================
 *  Function table interface
 * =============================================================================
 */
/*!
 *  @brief  Function table interface for Processor.
 */
typedef struct Processor_FxnTable_tag {
    Processor_AttachFxn                attach;
    /*!< Function to attach to the slave processor */
    Processor_DetachFxn                detach;
    /*!< Function to detach from the slave processor */
    Processor_StartFxn                 start;
    /*!< Function to start the slave processor */
    Processor_StopFxn                  stop;
    /*!< Function to stop the slave processor */
    Processor_ReadFxn                  read;
    /*!< Function to read from the slave processor's memory */
    Processor_WriteFxn                 write;
    /*!< Function to write into the slave processor's memory */
    Processor_ControlFxn               control;
    /*!< Function to perform device-dependent control function */
    Processor_TranslateAddrFxn         translateAddr;
    /*!< Function to translate between address ranges */
    Processor_MapFxn                   map;
    /*!< Function to map slave addresses to master address space */
    Processor_UnmapFxn                 unmap;
    /*!< Function to unmap slave addresses from master address space */
    Processor_GetProcInfoFxn           getProcInfo;
    /* !< Function to Get the proc info of the slave */
    Processor_VirtToPhysFxn            virtToPhys;
    /*!< Function to convert Virtual to Physical pages */
    Processor_TranslateFromPteFxn      translateFromPte;
    /*!< Function to translate slave virtual address into physical using page table */
} Processor_FxnTable;


/* =============================================================================
 * Processor structure
 * =============================================================================
 */
/*
 *  Generic Processor object. This object defines the handle type for all
 *  Processor operations.
 */
struct Processor_Object_tag {
    Processor_FxnTable      procFxnTable;
    /*!< Interface function table to plug into the generic Processor. */
    ProcMgr_State           state;
    /*!< State of the slave processor */
    ProcMgr_BootMode        bootMode;
    /*!< Boot mode for the slave processor. */
    Ptr                     object;
    /*!< Pointer to Processor-specific object. */
    UInt16                  procId;
    /*!< Processor ID addressed by this Processor instance. */
    List_Handle             registeredNotifiers;
    /*!< List of clients listening for an MMU fault event. */
    OsalMutex_Handle        notifiersLock;
    /*!< List of clients listening for an MMU fault event. */
};


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* ProcDefs_H_0x6a85 */
