/**
 *  @file   rprcloader.h
 *
 *  @brief      Internal Loader interface for rprc format.
 *
 *
 *  @ver        02.00.00.46_alpha1
 *
 *  ============================================================================
 *
 *  Copyright (c) 2008-2009, Texas Instruments Incorporated
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


#ifndef rprcloader_H_0x1bc5
#define rprcloader_H_0x1bc5


#if defined (__cplusplus)
extern "C" {
#endif


/*!
 *  @def    RPRCLOADER_MODULEID
 *  @brief  Module ID for RPRCLOADER.
 */
#define RPRCLOADER_MODULEID           (UInt16) 0x1bc5

/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */

/*!
 *  @def    RPRCLOADER_STATUSCODEBASE
 *  @brief  Status code base for RPRC loader.
 */
#define RPRCLOADER_STATUSCODEBASE      (RPRCLOADER_MODULEID << 12u)

/*!
 *  @def    RPRCLOADER_MAKE_FAILURE
 *  @brief  Macro to make failure code.
 */
#define RPRCLOADER_MAKE_FAILURE(x) ((Int)(  0x80000000                         \
                                          | (RPRCLOADER_STATUSCODEBASE + (x))))

/*!
 *  @def    RPRCLOADER_MAKE_SUCCESS
 *  @brief  Macro to make success code.
 */
#define RPRCLOADER_MAKE_SUCCESS(x)    (RPRCLOADER_STATUSCODEBASE + (x))

/*!
 *  @def    RPRCLOADER_E_SIZE
 *  @brief  An invalid size is specified
 */
#define RPRCLOADER_E_SIZE             RPRCLOADER_MAKE_FAILURE(1)

/*!
 *  @def    RPRCLOADER_E_FILEPARSE
 *  @brief  RPRC file parsing error
 */
#define RPRCLOADER_E_FILEPARSE        RPRCLOADER_MAKE_FAILURE(2)

/*!
 *  @def    RPRCLOADER_E_RANGE
 *  @brief  A value is out of range
 */
#define RPRCLOADER_E_RANGE            RPRCLOADER_MAKE_FAILURE(3)

/*!
 *  @def    RPRCLOADER_E_OSFAILURE
 *  @brief  Failure in an OS-specific operation.
 */
#define RPRCLOADER_E_OSFAILURE        RPRCLOADER_MAKE_FAILURE(4)

/*!
 *  @def    RPRCLOADER_E_INVALIDARG
 *  @brief  Argument passed to a function is invalid.
 */
#define RPRCLOADER_E_INVALIDARG       RPRCLOADER_MAKE_FAILURE(4)

/*!
 *  @def    RPRCLOADER_E_MEMORY
 *  @brief  Memory allocation failed.
 */
#define RPRCLOADER_E_MEMORY           RPRCLOADER_MAKE_FAILURE(5)

/*!
 *  @def    RPRCLOADER_E_HANDLE
 *  @brief  Invalid object handle specified
 */
#define RPRCLOADER_E_HANDLE           RPRCLOADER_MAKE_FAILURE(6)

/*!
 *  @def    RPRCLOADER_E_ACCESSDENIED
 *  @brief  The operation is not permitted in this process.
 */
#define RPRCLOADER_E_ACCESSDENIED     RPRCLOADER_MAKE_FAILURE(7)

/*!
 *  @def    RPRCLOADER_E_ACCESSDENIED
 *  @brief  The operation is not permitted in this process.
 */
#define RPRCLOADER_E_FAIL             RPRCLOADER_MAKE_FAILURE(8)

/*!
 *  @def    RPRCLOADER_SUCCESS
 *  @brief  Operation successful.
 */
#define RPRCLOADER_SUCCESS            RPRCLOADER_MAKE_SUCCESS(0)

/*!
 *  @def    RPRCLOADER_S_ALREADYSETUP
 *  @brief  The rprcloader module has already been setup in this process.
 */
#define RPRCLOADER_S_ALREADYSETUP     RPRCLOADER_MAKE_SUCCESS(1)

/*!
 *  @def    RPRCLOADER_S_OPENHANDLE
 *  @brief  Other rprcloader clients have still setup the rprcloader module.
 */
#define RPRCLOADER_S_SETUP            RPRCLOADER_MAKE_SUCCESS(2)

/*!
 *  @def    RPRCLOADER_S_OPENHANDLE
 *  @brief  Other rprcloader handles are still open in this process.
 */
#define RPRCLOADER_S_OPENHANDLE       RPRCLOADER_MAKE_SUCCESS(3)

/*!
 *  @def    RPRCLOADER_S_ALREADYEXISTS
 *  @brief  The rprcloader instance has already been created/opened in this
 *          process
 */
#define RPRCLOADER_S_ALREADYEXISTS    RPRCLOADER_MAKE_SUCCESS(4)


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief  Module configuration structure.
 */
typedef struct rprcloader_Config {
    UInt32 reserved;
    /*!< Reserved value. */
} rprcloader_Config;

/*!
 *  @brief  Configuration parameters specific to this processor.
 */
typedef struct rprcloader_Params_tag {
    UInt32 reserved;
    /*!< Reserved field (not currently required) */
} rprcloader_Params;


/*!
 *  @brief  rprcloader instance object.
 */
typedef struct rprcloader_Object_tag {
    Ptr                     rprcObject;
    /*!< Object used by the generic RPRC parser. */
    Ptr                     rprcloaderObject;
    /*!< Internal object used by RPRC Loader module. */
} rprcloader_Object, *rprcloader_Handle;


/* =============================================================================
 *  APIs
 * =============================================================================
 */

/* Function to get the default configuration for the rprcloader module. */
Void rprcloader_getConfig (rprcloader_Config * cfg);

/* Function to setup the rprcloader module. */
Int rprcloader_setup (rprcloader_Config * cfg);

/* Function to destroy the rprcloader module. */
Int rprcloader_destroy (Void);

/* Function to initialize the parameters for this loader instance. */
Void rprcloader_Params_init (rprcloader_Handle handle,
                             rprcloader_Params * params);

/* Function to create an instance of this loader. */
rprcloader_Handle rprcloader_create (      UInt16              procId,
                                     const rprcloader_Params * params);

/* Function to delete an instance of this loader. */
Int rprcloader_delete (rprcloader_Handle * handlePtr);

/* Function to open an instance of this loader. */
Int rprcloader_open (rprcloader_Handle * handlePtr, UInt16 procId);

/* Function to close an instance of this loader. */
Int rprcloader_close (rprcloader_Handle * handlePtr);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* rprcloader_H_0x1bc5 */
