/**
 *  @file   VAYUDspProc.h
 *
 *  @brief      Processor interface for VAYUSLAVE.
 *
 *
 */
/*
 *  ============================================================================
 *
 *  Copyright (c) 2013-2014, Texas Instruments Incorporated
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



#ifndef VAYUDSPPROC_H_0xbbed
#define VAYUDSPPROC_H_0xbbed


/* Module headers */
#include <ti/syslink/ProcMgr.h>
#include <ProcDefs.h>


#if defined (__cplusplus)
extern "C" {
#endif


/*!
 *  @def    VAYUDSPPROC_MODULEID
 *  @brief  Module ID for VAYUSLAVE.
 */
#define VAYUDSPPROC_MODULEID           (UInt16) 0xbbec

/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */
/*!
 *  @def    VAYUDSPPROC_STATUSCODEBASE
 *  @brief  Error code base for ProcMgr.
 */
#define VAYUDSPPROC_STATUSCODEBASE      (VAYUDSPPROC_MODULEID << 12u)

/*!
 *  @def    VAYUDSPPROC_MAKE_FAILURE
 *  @brief  Macro to make failure code.
 */
#define VAYUDSPPROC_MAKE_FAILURE(x)    ((Int)(  0x80000000                    \
                                         | (VAYUDSPPROC_STATUSCODEBASE + (x))))

/*!
 *  @def    VAYUDSPPROC_MAKE_SUCCESS
 *  @brief  Macro to make success code.
 */
#define VAYUDSPPROC_MAKE_SUCCESS(x)    (VAYUDSPPROC_STATUSCODEBASE + (x))

/*!
 *  @def    VAYUDSPPROC_E_MMUENTRYEXISTS
 *  @brief  Specified MMU entry already exists.
 */
#define VAYUDSPPROC_E_MMUENTRYEXISTS   VAYUDSPPROC_MAKE_FAILURE(1)

/*!
 *  @def    VAYUDSPPROC_E_ISR
 *  @brief  Error occurred during ISR operation.
 */
#define VAYUDSPPROC_E_ISR              VAYUDSPPROC_MAKE_FAILURE(2)

/*!
 *  @def    VAYUDSPPROC_E_MMUCONFIG
 *  @brief  Error occurred during MMU configuration
 */
#define VAYUDSPPROC_E_MMUCONFIG        VAYUDSPPROC_MAKE_FAILURE(3)

/*!
 *  @def    VAYUDSPPROC_E_OSFAILURE
 *  @brief  Failure in an OS-specific operation.
 */
#define VAYUDSPPROC_E_OSFAILURE        VAYUDSPPROC_MAKE_FAILURE(4)

/*!
 *  @def    VAYUDSPPROC_E_INVALIDARG
 *  @brief  Argument passed to a function is invalid.
 */
#define VAYUDSPPROC_E_INVALIDARG       VAYUDSPPROC_MAKE_FAILURE(5)

/*!
 *  @def    VAYUDSPPROC_E_MEMORY
 *  @brief  Memory allocation failed.
 */
#define VAYUDSPPROC_E_MEMORY           VAYUDSPPROC_MAKE_FAILURE(6)

/*!
 *  @def    VAYUDSPPROC_E_HANDLE
 *  @brief  Invalid object handle specified
 */
#define VAYUDSPPROC_E_HANDLE           VAYUDSPPROC_MAKE_FAILURE(7)

/*!
 *  @def    VAYUDSPPROC_E_ACCESSDENIED
 *  @brief  The operation is not permitted in this process.
 */
#define VAYUDSPPROC_E_ACCESSDENIED     VAYUDSPPROC_MAKE_FAILURE(8)

/*!
 *  @def    VAYUDSPPROC_E_FAIL
 *  @brief  Generic failure.
 */
#define VAYUDSPPROC_E_FAIL             VAYUDSPPROC_MAKE_FAILURE(9)

/*!
 *  @def    VAYUDSPPROC_SUCCESS
 *  @brief  Operation successful.
 */
#define VAYUDSPPROC_SUCCESS           VAYUDSPPROC_MAKE_SUCCESS(0)

/*!
 *  @def    VAYUDSPPROC_S_ALREADYSETUP
 *  @brief  The VAYUDSPPROC module has already been setup in this process.
 */
#define VAYUDSPPROC_S_ALREADYSETUP     VAYUDSPPROC_MAKE_SUCCESS(1)

/*!
 *  @def    VAYUDSPPROC_S_OPENHANDLE
 *  @brief  Other VAYUDSPPROC clients have still setup the VAYUDSPPROC module.
 */
#define VAYUDSPPROC_S_SETUP            VAYUDSPPROC_MAKE_SUCCESS(2)

/*!
 *  @def    VAYUDSPPROC_S_OPENHANDLE
 *  @brief  Other VAYUDSPPROC handles are still open in this process.
 */
#define VAYUDSPPROC_S_OPENHANDLE       VAYUDSPPROC_MAKE_SUCCESS(3)

/*!
 *  @def    VAYUDSPPROC_S_ALREADYEXISTS
 *  @brief  The VAYUDSPPROC instance has already been created/opened in this
 *          process
 */
#define VAYUDSPPROC_S_ALREADYEXISTS    VAYUDSPPROC_MAKE_SUCCESS(4)


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief  Module configuration structure.
 */
typedef struct VAYUDSPPROC_Config {
    UInt32 reserved; /*!< Reserved field (not currently required) */
} VAYUDSPPROC_Config;

/*!
 *  @brief  Configuration parameters specific to this processor.
 */
typedef struct VAYUDSPPROC_Params_tag {
    UInt32              numMemEntries;
    /*!< Number of memory regions to be configured. */
    ProcMgr_AddrInfo    memEntries[ProcMgr_MAX_MEMORY_REGIONS];
    /*!< Array of information structures for memory regions to be configured. */
} VAYUDSPPROC_Params;

/*!
 *  @brief  VAYUDSPPROC instance object.
 */
struct VAYUDSPPROC_Object_tag {
    VAYUDSPPROC_Params  params;
    /*!< Instance parameters (configuration values) */
    Ptr                 halObject;
    /*!< Pointer to the Hardware Abstraction Layer object. */
    ProcMgr_Handle      pmHandle;
    /*!< Handle to proc manager */
    Processor_Handle    procHandle;
    /*!< Handle to processor */
};

/*!
 *  @brief  Defines the VAYUDSPPROC object type
 */
typedef struct VAYUDSPPROC_Object_tag VAYUDSPPROC_Object;

/*!
 *  @brief  Defines VAYUDSPPROC object handle
 */
typedef struct VAYUDSPPROC_Object * VAYUDSPPROC_Handle;


/* =============================================================================
 *  APIs
 * =============================================================================
 */

/* Function to get the default configuration for the VAYUDSPPROC module. */
Void VAYUDSPPROC_getConfig (VAYUDSPPROC_Config * cfg);

/* Function to setup the VAYUDSPPROC module. */
Int VAYUDSPPROC_setup (VAYUDSPPROC_Config * cfg);

/* Function to destroy the VAYUDSPPROC module. */
Int VAYUDSPPROC_destroy (Void);

/* Function to initialize the parameters for this processor instance. */
Void VAYUDSPPROC_Params_init (VAYUDSPPROC_Handle    handle,
                            VAYUDSPPROC_Params *  params);

/* Function to create an instance of this processor. */
VAYUDSPPROC_Handle VAYUDSPPROC_create (      UInt16                   procId,
                                         const VAYUDSPPROC_Params * params);

/* Function to delete an instance of this processor. */
Int VAYUDSPPROC_delete (VAYUDSPPROC_Handle * handlePtr);

/* Function to open an instance of this processor. */
Int VAYUDSPPROC_open (VAYUDSPPROC_Handle * handlePtr, UInt16 procId);

/* Function to close an instance of this processor. */
Int VAYUDSPPROC_close (VAYUDSPPROC_Handle * handlePtr);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* VAYUDSPPROC_H_0xbbec */
