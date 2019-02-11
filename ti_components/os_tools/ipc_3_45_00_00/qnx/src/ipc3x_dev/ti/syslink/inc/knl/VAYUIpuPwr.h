/**
 *  @file   VAYUIpuPwr.h
 *
 *  @brief      Power Manager interface for VAYUIPUPWR.
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



#ifndef VAYUIPUPWR_H_0xa862
#define VAYUIPUPWR_H_0xa862


#if defined (__cplusplus)
extern "C" {
#endif

#include <ti/syslink/inc/ClockOps.h>

/*!
 *  @def    VAYUIPUPWR_MODULEID
 *  @brief  Module ID for VAYUIPUPWR.
 */
#define VAYUIPUPWR_MODULEID           (UInt16) 0xa860

/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */
/*!
 *  @def    VAYUIPUPWR_STATUSCODEBASE
 *  @brief  Error code base for VAYUIPUPWR.
 */
#define VAYUIPUPWR_STATUSCODEBASE      (VAYUIPUPWR_MODULEID << 12u)

/*!
 *  @def    VAYUIPUPWR_MAKE_FAILURE
 *  @brief  Macro to make failure code.
 */
#define VAYUIPUPWR_MAKE_FAILURE(x)((Int)(  0x80000000                    \
                                      | (VAYUIPUPWR_STATUSCODEBASE + (x))))

/*!
 *  @def    VAYUIPUPWR_MAKE_SUCCESS
 *  @brief  Macro to make success code.
 */
#define VAYUIPUPWR_MAKE_SUCCESS(x)   (VAYUIPUPWR_STATUSCODEBASE + (x))

/*!
 *  @def    VAYUIPUPWR_E_OSFAILURE
 *  @brief  Failure in an OS-specific operation.
 */
#define VAYUIPUPWR_E_OSFAILURE        VAYUIPUPWR_MAKE_FAILURE(1)

/*!
 *  @def    VAYUIPUPWR_E_INVALIDARG
 *  @brief  Argument passed to a function is invalid.
 */
#define VAYUIPUPWR_E_INVALIDARG       VAYUIPUPWR_MAKE_FAILURE(2)

/*!
 *  @def    VAYUIPUPWR_E_MEMORY
 *  @brief  Memory allocation failed.
 */
#define VAYUIPUPWR_E_MEMORY           VAYUIPUPWR_MAKE_FAILURE(3)

/*!
 *  @def    VAYUIPUPWR_E_HANDLE
 *  @brief  Invalid object handle specified
 */
#define VAYUIPUPWR_E_HANDLE           VAYUIPUPWR_MAKE_FAILURE(4)

/*!
 *  @def    VAYUIPUPWR_E_ACCESSDENIED
 *  @brief  The operation is not permitted in this process.
 */
#define VAYUIPUPWR_E_ACCESSDENIED     VAYUIPUPWR_MAKE_FAILURE(5)

/*!
 *  @def    VAYUIPUPWR_E_FAIL
 *  @brief  Generic failure.
 */
#define VAYUIPUPWR_E_FAIL             VAYUIPUPWR_MAKE_FAILURE(6)
/*!
 *  @def    VAYUIPUPWR_E_FAIL
 *  @brief  Generic failure.
 */
#define VAYUIPUPWR_E_INVALIDSTATE     VAYUIPUPWR_MAKE_FAILURE(7)

/*!
 *  @def    VAYUIPUPWR_SUCCESS
 *  @brief  Operation successful.
 */
#define VAYUIPUPWR_SUCCESS            VAYUIPUPWR_MAKE_SUCCESS(0)

/*!
 *  @def    VAYUIPUPWR_S_ALREADYSETUP
 *  @brief  The VAYUIPUPWR module has already been setup in this process.
 */
#define VAYUIPUPWR_S_ALREADYSETUP     VAYUIPUPWR_MAKE_SUCCESS(1)

/*!
 *  @def    VAYUIPUPWR_S_OPENHANDLE
 *  @brief  Other VAYUIPUPWR clients have still setup the VAYUIPUPWR module.
 */
#define VAYUIPUPWR_S_SETUP            VAYUIPUPWR_MAKE_SUCCESS(2)

/*!
 *  @def    VAYUIPUPWR_S_OPENHANDLE
 *  @brief  Other VAYUIPUPWR handles are still open in this process.
 */
#define VAYUIPUPWR_S_OPENHANDLE       VAYUIPUPWR_MAKE_SUCCESS(3)

/*!
 *  @def    VAYUIPUPWR_S_ALREADYEXISTS
 *  @brief  The VAYUIPUPWR instance has already been created/opened in this
 *          process
 */
#define VAYUIPUPWR_S_ALREADYEXISTS    VAYUIPUPWR_MAKE_SUCCESS(4)
/*!
 *  @def    VAYUIPUPWR_S_ALREADYPOWEREDON
 *  @brief  The VAYUIPUPWR power on code has been executed
 */
#define  VAYUIPUPWR_S_ALREADYPOWEREDON VAYUIPUPWR_MAKE_SUCCESS(5)


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief  Module configuration structure.
 */
typedef struct VAYUIPUPWR_Config {
    UInt32 reserved; /*!< Reserved field (not currently required) */
} VAYUIPUPWR_Config;

/*!
 *  @brief  Configuration parameters specific to this processor.
 */
typedef struct VAYUIPUPWR_Params_tag {
    UInt32             reserved;
    /*!< Reserved field (not currently required) */
    Ptr                clockHandle;
    /*!< Pointer to the Clock Object that will be passed to create */
} VAYUIPUPWR_Params;



/*!
 *  @brief  VAYUIPUPWR instance object.
 */
struct VAYUIPUPWR_Object_tag {

    VAYUIPUPWR_Params params;
    /*!< Instance parameters (configuration values) */
    UInt32                prcmVA;
    /*!< Virtual address for prcm module */
    UInt32                ipuMmuVA;
    /*!< Virtual address for mmu module */
    UInt32                ipubaseVA;
    /*!< Virtual address for control module */
    ClockOps_Handle       clockHandle;
    /*!< Pointer to the Clock object. */

};


/*!
 *  @brief  Defines VAYUIPUPWR object handle
 */
typedef struct VAYUIPUPWR_Object_tag VAYUIPUPWR_Object;


/*!
 *  @brief  Defines VAYUIPUPWR object handle
 */
typedef struct VAYUIPUPWR_Object * VAYUIPUPWR_Handle;


/* =============================================================================
 *  APIs
 * =============================================================================
 */

/* Function to get the default configuration for the VAYUIPUPWR module. */
Void VAYUIPUPWR_getConfig (VAYUIPUPWR_Config * cfg);

/* Function to setup the VAYUIPUPWR module. */
Int VAYUIPUPWR_setup (VAYUIPUPWR_Config * cfg);

/* Function to destroy the VAYUIPUPWR module. */
Int VAYUIPUPWR_destroy (Void);

/* Function to initialize the parameters for this PwrMgr instance. */
Void VAYUIPUPWR_Params_init (VAYUIPUPWR_Params * params);

/* Function to create an instance of this PwrMgr. */
VAYUIPUPWR_Handle VAYUIPUPWR_create (       UInt16               procId,
                                       const  VAYUIPUPWR_Params * params);

/* Function to delete an instance of this PwrMgr. */
Int VAYUIPUPWR_delete (VAYUIPUPWR_Handle * handlePtr);

/* Function to open an instance of this PwrMgr. */
Int VAYUIPUPWR_open (VAYUIPUPWR_Handle * handlePtr, UInt16 procId);

/* Function to close an instance of this PwrMgr. */
Int VAYUIPUPWR_close (VAYUIPUPWR_Handle * handlePtr);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* VAYUIPUPWR_H_0xa860 */
