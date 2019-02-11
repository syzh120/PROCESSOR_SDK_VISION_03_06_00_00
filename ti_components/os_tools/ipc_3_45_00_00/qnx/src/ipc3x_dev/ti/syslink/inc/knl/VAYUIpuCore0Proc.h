/**
 *  @file   VAYUIpuCore0Proc.h
 *
 *  @brief      Processor interface for VAYUIPUCORE0.
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



#ifndef VAYUIPUCORE0PROC_H_0xbbef
#define VAYUIPUCORE0PROC_H_0xbbef


/* Module headers */
#include <ti/syslink/ProcMgr.h>
#include <ProcDefs.h>


#if defined (__cplusplus)
extern "C" {
#endif


/*!
 *  @def    VAYUIPUCORE0PROC_MODULEID
 *  @brief  Module ID for VAYUSLAVE.
 */
#define VAYUIPUCORE0PROC_MODULEID           (UInt16) 0xbbec

/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */
/*!
 *  @def    VAYUIPUCORE0PROC_STATUSCODEBASE
 *  @brief  Error code base for ProcMgr.
 */
#define VAYUIPUCORE0PROC_STATUSCODEBASE      (VAYUIPUCORE0PROC_MODULEID << 12u)

/*!
 *  @def    VAYUIPUCORE0PROC_MAKE_FAILURE
 *  @brief  Macro to make failure code.
 */
#define VAYUIPUCORE0PROC_MAKE_FAILURE(x) ((Int)(  0x80000000                   \
                                     | (VAYUIPUCORE0PROC_STATUSCODEBASE + (x))))

/*!
 *  @def    VAYUIPUCORE0PROC_MAKE_SUCCESS
 *  @brief  Macro to make success code.
 */
#define VAYUIPUCORE0PROC_MAKE_SUCCESS(x) (VAYUIPUCORE0PROC_STATUSCODEBASE + (x))

/*!
 *  @def    VAYUIPUCORE0PROC_E_MMUENTRYEXISTS
 *  @brief  Specified MMU entry already exists.
 */
#define VAYUIPUCORE0PROC_E_MMUENTRYEXISTS   VAYUIPUCORE0PROC_MAKE_FAILURE(1)

/*!
 *  @def    VAYUIPUCORE0PROC_E_ISR
 *  @brief  Error occurred during ISR operation.
 */
#define VAYUIPUCORE0PROC_E_ISR              VAYUIPUCORE0PROC_MAKE_FAILURE(2)

/*!
 *  @def    VAYUIPUCORE0PROC_E_MMUCONFIG
 *  @brief  Error occurred during MMU configuration
 */
#define VAYUIPUCORE0PROC_E_MMUCONFIG        VAYUIPUCORE0PROC_MAKE_FAILURE(3)

/*!
 *  @def    VAYUIPUCORE0PROC_E_OSFAILURE
 *  @brief  Failure in an OS-specific operation.
 */
#define VAYUIPUCORE0PROC_E_OSFAILURE        VAYUIPUCORE0PROC_MAKE_FAILURE(4)

/*!
 *  @def    VAYUIPUCORE0PROC_E_INVALIDARG
 *  @brief  Argument passed to a function is invalid.
 */
#define VAYUIPUCORE0PROC_E_INVALIDARG       VAYUIPUCORE0PROC_MAKE_FAILURE(5)

/*!
 *  @def    VAYUIPUCORE0PROC_E_MEMORY
 *  @brief  Memory allocation failed.
 */
#define VAYUIPUCORE0PROC_E_MEMORY           VAYUIPUCORE0PROC_MAKE_FAILURE(6)

/*!
 *  @def    VAYUIPUCORE0PROC_E_HANDLE
 *  @brief  Invalid object handle specified
 */
#define VAYUIPUCORE0PROC_E_HANDLE           VAYUIPUCORE0PROC_MAKE_FAILURE(7)

/*!
 *  @def    VAYUIPUCORE0PROC_E_ACCESSDENIED
 *  @brief  The operation is not permitted in this process.
 */
#define VAYUIPUCORE0PROC_E_ACCESSDENIED     VAYUIPUCORE0PROC_MAKE_FAILURE(8)

/*!
 *  @def    VAYUIPUCORE0PROC_E_FAIL
 *  @brief  Generic failure.
 */
#define VAYUIPUCORE0PROC_E_FAIL             VAYUIPUCORE0PROC_MAKE_FAILURE(9)

/*!
 *  @def    VAYUIPUCORE0PROC_SUCCESS
 *  @brief  Operation successful.
 */
#define VAYUIPUCORE0PROC_SUCCESS           VAYUIPUCORE0PROC_MAKE_SUCCESS(0)

/*!
 *  @def    VAYUIPUCORE0PROC_S_ALREADYSETUP
 *  @brief  The VAYUIPUCORE0PROC module has already been setup in this process.
 */
#define VAYUIPUCORE0PROC_S_ALREADYSETUP     VAYUIPUCORE0PROC_MAKE_SUCCESS(1)

/*!
 *  @def    VAYUIPUCORE0PROC_S_OPENHANDLE
 *  @brief  Other VAYUIPUCORE0PROC clients have still setup the
 *          VAYUIPUCORE0PROC module.
 */
#define VAYUIPUCORE0PROC_S_SETUP            VAYUIPUCORE0PROC_MAKE_SUCCESS(2)

/*!
 *  @def    VAYUIPUCORE0PROC_S_OPENHANDLE
 *  @brief  Other VAYUIPUCORE0PROC handles are still open in this process.
 */
#define VAYUIPUCORE0PROC_S_OPENHANDLE       VAYUIPUCORE0PROC_MAKE_SUCCESS(3)

/*!
 *  @def    VAYUIPUCORE0PROC_S_ALREADYEXISTS
 *  @brief  The VAYUIPUCORE0PROC instance has already been created/opened in
 *          this process
 */
#define VAYUIPUCORE0PROC_S_ALREADYEXISTS    VAYUIPUCORE0PROC_MAKE_SUCCESS(4)


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief  Module configuration structure.
 */
typedef struct VAYUIPUCORE0PROC_Config {
    UInt32 reserved; /*!< Reserved field (not currently required) */
} VAYUIPUCORE0PROC_Config;

/*!
 *  @brief  Configuration parameters specific to this processor.
 */
typedef struct VAYUIPUCORE0PROC_Params_tag {
    UInt32              numMemEntries;
    /*!< Number of memory regions to be configured. */
    ProcMgr_AddrInfo    memEntries[ProcMgr_MAX_MEMORY_REGIONS];
    /*!< Array of information structures for memory regions to be configured. */
} VAYUIPUCORE0PROC_Params;

/*!
 *  @brief  VAYUIPUCORE0PROC instance object.
 */
struct VAYUIPUCORE0PROC_Object_tag {
    VAYUIPUCORE0PROC_Params  params;
    /*!< Instance parameters (configuration values) */
    Ptr                      halObject;
    /*!< Pointer to the Hardware Abstraction Layer object. */
    ProcMgr_Handle           pmHandle;
    /*!< Handle to proc manager */
    Processor_Handle         procHandle;
    /*!< Handle to processor */
};

/*!
 *  @brief  Defines the VAYUIPUCORE0PROC object type
 */
typedef struct VAYUIPUCORE0PROC_Object_tag VAYUIPUCORE0PROC_Object;

/*!
 *  @brief  Defines VAYUIPUCORE0PROC object handle
 */
typedef struct VAYUIPUCORE0PROC_Object * VAYUIPUCORE0PROC_Handle;


/* =============================================================================
 *  APIs
 * =============================================================================
 */

/* Function to get the default configuration for the VAYUIPUCORE0PROC module. */
Void VAYUIPUCORE0PROC_getConfig (VAYUIPUCORE0PROC_Config * cfg);

/* Function to setup the VAYUIPUCORE0PROC module. */
Int VAYUIPUCORE0PROC_setup (VAYUIPUCORE0PROC_Config * cfg);

/* Function to destroy the VAYUIPUCORE0PROC module. */
Int VAYUIPUCORE0PROC_destroy (Void);

/* Function to initialize the parameters for this processor instance. */
Void VAYUIPUCORE0PROC_Params_init (VAYUIPUCORE0PROC_Handle    handle,
                                   VAYUIPUCORE0PROC_Params *  params);

/* Function to create an instance of this processor. */
VAYUIPUCORE0PROC_Handle VAYUIPUCORE0PROC_create (      UInt16           procId,
                                        const VAYUIPUCORE0PROC_Params * params);

/* Function to delete an instance of this processor. */
Int VAYUIPUCORE0PROC_delete (VAYUIPUCORE0PROC_Handle * handlePtr);

/* Function to open an instance of this processor. */
Int VAYUIPUCORE0PROC_open (VAYUIPUCORE0PROC_Handle * handlePtr, UInt16 procId);

/* Function to close an instance of this processor. */
Int VAYUIPUCORE0PROC_close (VAYUIPUCORE0PROC_Handle * handlePtr);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* VAYUIPUCORE0PROC_H_0xbbec */
