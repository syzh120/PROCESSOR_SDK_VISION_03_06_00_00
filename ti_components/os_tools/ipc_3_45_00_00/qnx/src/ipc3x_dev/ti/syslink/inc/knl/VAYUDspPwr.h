/**
 *  @file   VAYUDspPwr.h
 *
 *  @brief      Power Manager interface for VAYUDSPPWR.
 *
 *
 */
/*
 *  ============================================================================
 *
 *  Copyright (c) 2013, Texas Instruments Incorporated
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



#ifndef VAYUDSPPWR_H_0xa861
#define VAYUDSPPWR_H_0xa861


#if defined (__cplusplus)
extern "C" {
#endif


/*!
 *  @def    VAYUDSPPWR_MODULEID
 *  @brief  Module ID for VAYUDSPPWR.
 */
#define VAYUDSPPWR_MODULEID           (UInt16) 0xa860

/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */
/*!
 *  @def    VAYUDSPPWR_STATUSCODEBASE
 *  @brief  Error code base for VAYUDSPPWR.
 */
#define VAYUDSPPWR_STATUSCODEBASE      (VAYUDSPPWR_MODULEID << 12u)

/*!
 *  @def    VAYUDSPPWR_MAKE_FAILURE
 *  @brief  Macro to make failure code.
 */
#define VAYUDSPPWR_MAKE_FAILURE(x)    ((Int)(  0x80000000                    \
                                         | (VAYUDSPPWR_STATUSCODEBASE + (x))))

/*!
 *  @def    VAYUDSPPWR_MAKE_SUCCESS
 *  @brief  Macro to make success code.
 */
#define VAYUDSPPWR_MAKE_SUCCESS(x)    (VAYUDSPPWR_STATUSCODEBASE + (x))

/*!
 *  @def    VAYUDSPPWR_E_OSFAILURE
 *  @brief  Failure in an OS-specific operation.
 */
#define VAYUDSPPWR_E_OSFAILURE        VAYUDSPPWR_MAKE_FAILURE(1)

/*!
 *  @def    VAYUDSPPWR_E_INVALIDARG
 *  @brief  Argument passed to a function is invalid.
 */
#define VAYUDSPPWR_E_INVALIDARG       VAYUDSPPWR_MAKE_FAILURE(2)

/*!
 *  @def    VAYUDSPPWR_E_MEMORY
 *  @brief  Memory allocation failed.
 */
#define VAYUDSPPWR_E_MEMORY           VAYUDSPPWR_MAKE_FAILURE(3)

/*!
 *  @def    VAYUDSPPWR_E_HANDLE
 *  @brief  Invalid object handle specified
 */
#define VAYUDSPPWR_E_HANDLE           VAYUDSPPWR_MAKE_FAILURE(4)

/*!
 *  @def    VAYUDSPPWR_E_ACCESSDENIED
 *  @brief  The operation is not permitted in this process.
 */
#define VAYUDSPPWR_E_ACCESSDENIED     VAYUDSPPWR_MAKE_FAILURE(5)

/*!
 *  @def    VAYUDSPPWR_E_FAIL
 *  @brief  Generic failure.
 */
#define VAYUDSPPWR_E_FAIL             VAYUDSPPWR_MAKE_FAILURE(6)

/*!
 *  @def    VAYUDSPPWR_SUCCESS
 *  @brief  Operation successful.
 */
#define VAYUDSPPWR_SUCCESS            VAYUDSPPWR_MAKE_SUCCESS(0)

/*!
 *  @def    VAYUDSPPWR_S_ALREADYSETUP
 *  @brief  The VAYUDSPPWR module has already been setup in this process.
 */
#define VAYUDSPPWR_S_ALREADYSETUP     VAYUDSPPWR_MAKE_SUCCESS(1)

/*!
 *  @def    VAYUDSPPWR_S_OPENHANDLE
 *  @brief  Other VAYUDSPPWR clients have still setup the VAYUDSPPWR module.
 */
#define VAYUDSPPWR_S_SETUP            VAYUDSPPWR_MAKE_SUCCESS(2)

/*!
 *  @def    VAYUDSPPWR_S_OPENHANDLE
 *  @brief  Other VAYUDSPPWR handles are still open in this process.
 */
#define VAYUDSPPWR_S_OPENHANDLE       VAYUDSPPWR_MAKE_SUCCESS(3)

/*!
 *  @def    VAYUDSPPWR_S_ALREADYEXISTS
 *  @brief  The VAYUDSPPWR instance has already been created/opened in this
 *          process
 */
#define VAYUDSPPWR_S_ALREADYEXISTS    VAYUDSPPWR_MAKE_SUCCESS(4)


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief  Module configuration structure.
 */
typedef struct VAYUDSPPWR_Config {
    UInt32 reserved; /*!< Reserved field (not currently required) */
} VAYUDSPPWR_Config;

/*!
 *  @brief  Configuration parameters specific to this processor.
 */
typedef struct VAYUDSPPWR_Params_tag {
    UInt32  reserved;
    /*!< Reserved field (not currently required) */
    Ptr     clockHandle;
    /*!< Pointer to the Clock Object that will be passed to create */

} VAYUDSPPWR_Params;

/*!
 *  @brief  Defines VAYUDSPPWR object handle
 */
typedef struct VAYUDSPPWR_Object * VAYUDSPPWR_Handle;


/* =============================================================================
 *  APIs
 * =============================================================================
 */

/* Function to get the default configuration for the VAYUDSPPWR module. */
Void VAYUDSPPWR_getConfig (VAYUDSPPWR_Config * cfg);

/* Function to setup the VAYUDSPPWR module. */
Int VAYUDSPPWR_setup (VAYUDSPPWR_Config * cfg);

/* Function to destroy the VAYUDSPPWR module. */
Int VAYUDSPPWR_destroy (Void);

/* Function to initialize the parameters for this PwrMgr instance. */
Void VAYUDSPPWR_Params_init (VAYUDSPPWR_Params * params);

/* Function to create an instance of this PwrMgr. */
VAYUDSPPWR_Handle VAYUDSPPWR_create (       UInt16               procId,
                                       const  VAYUDSPPWR_Params * params);

/* Function to delete an instance of this PwrMgr. */
Int VAYUDSPPWR_delete (VAYUDSPPWR_Handle * handlePtr);

/* Function to open an instance of this PwrMgr. */
Int VAYUDSPPWR_open (VAYUDSPPWR_Handle * handlePtr, UInt16 procId);

/* Function to close an instance of this PwrMgr. */
Int VAYUDSPPWR_close (VAYUDSPPWR_Handle * handlePtr);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* VAYUDSPPWR_H_0xa860 */
