/**
 *  @file   OMAP5430BenelliProc.h
 *
 *  @brief      Processor interface for OMAP5430Benelli.
 *
 *
 *  @ver        02.00.00.44_pre-alpha3
 *
 *  ============================================================================
 *
 *  Copyright (c) 2010-2014, Texas Instruments Incorporated
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


#ifndef OMAP5430BENELLIPROC_H_0xbbed
#define OMAP5430BENELLIPROC_H_0xbbed


/* Module headers */
#include <ti/syslink/ProcMgr.h>
#include <ProcDefs.h>


#if defined (__cplusplus)
extern "C" {
#endif


/*!
 *  @def    OMAP5430BENELLIPROC_MODULEID
 *  @brief  Module ID for OMAP5430BENELLI.
 */
#define OMAP5430BENELLIPROC_MODULEID           (UInt16) 0xbbec

/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */
/*!
 *  @def    OMAP5430BENELLIPROC_STATUSCODEBASE
 *  @brief  Error code base for ProcMgr.
 */
#define OMAP5430BENELLIPROC_STATUSCODEBASE      (OMAP5430BENELLIPROC_MODULEID << 12u)

/*!
 *  @def    OMAP5430BENELLIPROC_MAKE_FAILURE
 *  @brief  Macro to make failure code.
 */
#define OMAP5430BENELLIPROC_MAKE_FAILURE(x)    ((Int)(  0x80000000                    \
                                         | (OMAP5430BENELLIPROC_STATUSCODEBASE + (x))))

/*!
 *  @def    OMAP5430BENELLIPROC_MAKE_SUCCESS
 *  @brief  Macro to make success code.
 */
#define OMAP5430BENELLIPROC_MAKE_SUCCESS(x) (OMAP5430BENELLIPROC_STATUSCODEBASE + (x))

/*!
 *  @def    OMAP5430BENELLIPROC_E_MMUENTRYEXISTS
 *  @brief  Specified MMU entry already exists.
 */
#define OMAP5430BENELLIPROC_E_MMUENTRYEXISTS OMAP5430BENELLIPROC_MAKE_FAILURE(1)

/*!
 *  @def    OMAP5430BENELLIPROC_E_ISR
 *  @brief  Error occurred during ISR operation.
 */
#define OMAP5430BENELLIPROC_E_ISR            OMAP5430BENELLIPROC_MAKE_FAILURE(2)

/*!
 *  @def    OMAP5430BENELLIPROC_E_MMUCONFIG
 *  @brief  Error occurred during MMU configuration
 */
#define OMAP5430BENELLIPROC_E_MMUCONFIG      OMAP5430BENELLIPROC_MAKE_FAILURE(3)

/*!
 *  @def    OMAP5430BENELLIPROC_E_OSFAILURE
 *  @brief  Failure in an OS-specific operation.
 */
#define OMAP5430BENELLIPROC_E_OSFAILURE      OMAP5430BENELLIPROC_MAKE_FAILURE(4)

/*!
 *  @def    OMAP5430BENELLIPROC_E_INVALIDARG
 *  @brief  Argument passed to a function is invalid.
 */
#define OMAP5430BENELLIPROC_E_INVALIDARG     OMAP5430BENELLIPROC_MAKE_FAILURE(5)

/*!
 *  @def    OMAP5430BENELLIPROC_E_MEMORY
 *  @brief  Memory allocation failed.
 */
#define OMAP5430BENELLIPROC_E_MEMORY         OMAP5430BENELLIPROC_MAKE_FAILURE(6)

/*!
 *  @def    OMAP5430BENELLIPROC_E_HANDLE
 *  @brief  Invalid object handle specified
 */
#define OMAP5430BENELLIPROC_E_HANDLE         OMAP5430BENELLIPROC_MAKE_FAILURE(7)

/*!
 *  @def    OMAP5430BENELLIPROC_E_ACCESSDENIED
 *  @brief  The operation is not permitted in this process.
 */
#define OMAP5430BENELLIPROC_E_ACCESSDENIED   OMAP5430BENELLIPROC_MAKE_FAILURE(8)

/*!
 *  @def    OMAP5430BENELLIPROC_E_FAIL
 *  @brief  Generic failure.
 */
#define OMAP5430BENELLIPROC_E_FAIL           OMAP5430BENELLIPROC_MAKE_FAILURE(9)

/*!
 *  @def    OMAP5430BENELLIPROC_SUCCESS
 *  @brief  Operation successful.
 */
#define OMAP5430BENELLIPROC_SUCCESS         OMAP5430BENELLIPROC_MAKE_SUCCESS(0)

/*!
 *  @def    OMAP5430BENELLIPROC_S_ALREADYSETUP
 *  @brief  The OMAP5430BENELLIPROC module has already been setup in this
 *          process.
 */
#define OMAP5430BENELLIPROC_S_ALREADYSETUP   OMAP5430BENELLIPROC_MAKE_SUCCESS(1)

/*!
 *  @def    OMAP5430BENELLIPROC_S_OPENHANDLE
 *  @brief  Other OMAP5430BENELLIPROC clients have still setup the
 *          OMAP5430BENELLIPROC module.
 */
#define OMAP5430BENELLIPROC_S_SETUP          OMAP5430BENELLIPROC_MAKE_SUCCESS(2)

/*!
 *  @def    OMAP5430BENELLIPROC_S_OPENHANDLE
 *  @brief  Other OMAP5430BENELLIPROC handles are still open in this process.
 */
#define OMAP5430BENELLIPROC_S_OPENHANDLE     OMAP5430BENELLIPROC_MAKE_SUCCESS(3)

/*!
 *  @def    OMAP5430BENELLIPROC_S_ALREADYEXISTS
 *  @brief  The OMAP5430BENELLIPROC instance has already been created/opened in
 *          this process
 */
#define OMAP5430BENELLIPROC_S_ALREADYEXISTS  OMAP5430BENELLIPROC_MAKE_SUCCESS(4)


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */

/*!
 *  @brief  Enumerations to indicate types of control commands supported.
 */
typedef enum {
    Omap5430BenelliProc_CtrlCmd_Suspend         = 0u,
    /*!< Suspend the remote proc. */
    Omap5430BenelliProc_CtrlCmd_Resume          = 1u,
    /*!< Resume the remote proc. */
    Omap5430BenelliProc_CtrlCmd_EndValue        = 2u
    /*!< End delimiter indicating start of invalid values for this enum */
} Omap5430BenelliProc_CtrlCmd ;

/*!
 *  @brief  Module configuration structure.
 */
typedef struct OMAP5430BENELLIPROC_Config {
    UInt32 reserved; /*!< Reserved field (not currently required) */
} OMAP5430BENELLIPROC_Config;

typedef struct OMAP5430TESLAPROC_Config {
    UInt32 reserved; /*!< Reserved field (not currently required) */
} OMAP5430TESLAPROC_Config;

/*!
 *  @brief  Configuration parameters specific to this processor.
 */
typedef struct OMAP5430BENELLIPROC_Params_tag {
    UInt32           numMemEntries;
    /*!< Number of memory regions to be configured. */
    ProcMgr_AddrInfo memEntries [ProcMgr_MAX_MEMORY_REGIONS];
    /*!< Array of information structures for memory regions to be configured. */
    Processor_Handle procHandle;
} OMAP5430BENELLIPROC_Params;

/*!
 *  @brief  Defines OMAP5430BENELLIPROC object handle
 */
/*!
 *  @brief  DM740M3VIDEOPROC instance object.
 */
struct OMAP5430BENELLIPROC_Object_tag {
    OMAP5430BENELLIPROC_Params params;
    /*!< Instance parameters (configuration values) */
    Ptr                        halObject;
    /*!< Pointer to the Hardware Abstraction Layer object. */
    ProcMgr_Handle             pmHandle;
    /*!< Handle to proc manager */
    Processor_Handle           procHandle;
    /*!< Handle to processor */
};

/* Defines the OMAP5430BENELLIPROC object type. */
typedef struct OMAP5430BENELLIPROC_Object_tag OMAP5430BENELLIPROC_Object;

typedef struct OMAP5430BENELLIPROC_Object * OMAP5430BENELLIPROC_Handle;


/* =============================================================================
 *  APIs
 * =============================================================================
 */

/* Function to get the default configuration for the OMAP5430BENELLIPROC
 * module. */
Void
OMAP5430BENELLIPROC_get_config (OMAP5430BENELLIPROC_Config * cfg, Int ProcType);

/* Function to setup the OMAP5430BENELLIPROC module. */
Int
OMAP5430BENELLIPROC_setup (OMAP5430BENELLIPROC_Config * cfg, Int ProcType);

/* Function to destroy the OMAP5430BENELLIPROC module. */
Int
OMAP5430BENELLIPROC_destroy (Int ProcType);

/* Function to initialize the parameters for this processor instance. */
Void
OMAP5430BENELLIPROC_Params_init (OMAP5430BENELLIPROC_Handle    handle,
                                 OMAP5430BENELLIPROC_Params *  params,
                                 Int                           ProcType);

/* Function to create an instance of this processor. */
OMAP5430BENELLIPROC_Handle
OMAP5430BENELLIPROC_create (      UInt16                       procId,
                            const OMAP5430BENELLIPROC_Params * params);

/* Function to delete an instance of this processor. */
Int
OMAP5430BENELLIPROC_delete (OMAP5430BENELLIPROC_Handle * handlePtr);

/* Function to open an instance of this processor. */
Int
OMAP5430BENELLIPROC_open (OMAP5430BENELLIPROC_Handle * handlePtr,
                          UInt16                       procId);

/* Function to close an instance of this processor. */
Int
OMAP5430BENELLIPROC_close (OMAP5430BENELLIPROC_Handle * handlePtr);

Int
OMAP5430BENELLIPROC_attach (Processor_Handle         handle,
                            Processor_AttachParams * params);

Int
OMAP5430BENELLIPROC_detach (Processor_Handle handle);

Int
OMAP5430BENELLIPROC_start (Processor_Handle        handle,
                           UInt32                  entryPt,
                           Processor_StartParams * params);

Int
OMAP5430BENELLIPROC_stop (Processor_Handle handle);

Int
OMAP5430BENELLIPROC_read (Processor_Handle   handle,
                          UInt32             procAddr,
                          UInt32 *           numBytes,
                          Ptr                buffer);

Int
OMAP5430BENELLIPROC_write (Processor_Handle handle,
                           UInt32           procAddr,
                           UInt32 *         numBytes,
                           Ptr              buffer);

Int
OMAP5430BENELLIPROC_control (Processor_Handle handle, Int32 cmd, Ptr arg);

Int
OMAP5430BENELLIPROC_map (Processor_Handle handle,
                         UInt32 *         dstAddr,
                         UInt32           nSegs,
                         Memory_SGList *  sglist);

Int
OMAP5430BENELLIPROC_unmap (Processor_Handle handle,
                           UInt32           addr,
                           UInt32           size);

Int
OMAP5430BENELLIPROC_translate (Processor_Handle handle,
                               UInt32 *         dstAddr,
                               UInt32           srcAddr);

Int
OMAP5430BENELLI_virtToPhys (Processor_Handle handle,
                            UInt32           da,
                            UInt32 *         mappedEntries,
                            UInt32           numEntries);

Int
OMAP5430BENELLIPROC_procInfo (Processor_Handle   handle,
                              ProcMgr_ProcInfo * procInfo);

Int
OMAP5430BENELLIPROC_registerNotify (Processor_Handle    handle,
                                    ProcMgr_CallbackFxn cbFxn,
                                    Ptr                 arg,
                                    Int32               timeout,
                                    ProcMgr_State       state []);

Int
OMAP5430BENELLIPROC_unregisterNotify (Processor_Handle      handle,
                                      ProcMgr_CallbackFxn   cbFxn,
                                      Ptr                   arg,
                                      ProcMgr_State         state []);

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* OMAP5430BENELLIPROC_H_0xbbec */
