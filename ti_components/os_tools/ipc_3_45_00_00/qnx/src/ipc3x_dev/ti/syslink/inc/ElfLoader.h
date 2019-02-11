/**
 *  @file   ElfLoader.h
 *
 *  @brief      Internal Loader interface for ELF format.
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


#ifndef ElfLoader_H_0x1bc5
#define ElfLoader_H_0x1bc5


#if defined (__cplusplus)
extern "C" {
#endif


/*!
 *  @def    ELFLOADER_MODULEID
 *  @brief  Module ID for ELFLOADER.
 */
#define ELFLOADER_MODULEID           (UInt16) 0x1bc5

/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */

/*!
 *  @def    ELFLOADER_STATUSCODEBASE
 *  @brief  Status code base for ELF loader.
 */
#define ELFLOADER_STATUSCODEBASE      (ELFLOADER_MODULEID << 12u)

/*!
 *  @def    ELFLOADER_MAKE_FAILURE
 *  @brief  Macro to make failure code.
 */
#define ELFLOADER_MAKE_FAILURE(x) ((Int)(  0x80000000                         \
                                          | (ELFLOADER_STATUSCODEBASE + (x))))

/*!
 *  @def    ELFLOADER_MAKE_SUCCESS
 *  @brief  Macro to make success code.
 */
#define ELFLOADER_MAKE_SUCCESS(x)    (ELFLOADER_STATUSCODEBASE + (x))

/*!
 *  @def    ELFLOADER_E_SIZE
 *  @brief  An invalid size is specified
 */
#define ELFLOADER_E_SIZE             ELFLOADER_MAKE_FAILURE(1)

/*!
 *  @def    ELFLOADER_E_FILEPARSE
 *  @brief  ELF file parsing error
 */
#define ELFLOADER_E_FILEPARSE        ELFLOADER_MAKE_FAILURE(2)

/*!
 *  @def    ELFLOADER_E_RANGE
 *  @brief  A value is out of range
 */
#define ELFLOADER_E_RANGE            ELFLOADER_MAKE_FAILURE(3)

/*!
 *  @def    ELFLOADER_E_OSFAILURE
 *  @brief  Failure in an OS-specific operation.
 */
#define ELFLOADER_E_OSFAILURE        ELFLOADER_MAKE_FAILURE(4)

/*!
 *  @def    ELFLOADER_E_INVALIDARG
 *  @brief  Argument passed to a function is invalid.
 */
#define ELFLOADER_E_INVALIDARG       ELFLOADER_MAKE_FAILURE(4)

/*!
 *  @def    ELFLOADER_E_MEMORY
 *  @brief  Memory allocation failed.
 */
#define ELFLOADER_E_MEMORY           ELFLOADER_MAKE_FAILURE(5)

/*!
 *  @def    ELFLOADER_E_HANDLE
 *  @brief  Invalid object handle specified
 */
#define ELFLOADER_E_HANDLE           ELFLOADER_MAKE_FAILURE(6)

/*!
 *  @def    ELFLOADER_E_ACCESSDENIED
 *  @brief  The operation is not permitted in this process.
 */
#define ELFLOADER_E_ACCESSDENIED     ELFLOADER_MAKE_FAILURE(7)

/*!
 *  @def    ELFLOADER_E_ACCESSDENIED
 *  @brief  The operation is not permitted in this process.
 */
#define ELFLOADER_E_FAIL             ELFLOADER_MAKE_FAILURE(8)

/*!
 *  @def    ELFLOADER_SUCCESS
 *  @brief  Operation successful.
 */
#define ELFLOADER_SUCCESS            ELFLOADER_MAKE_SUCCESS(0)

/*!
 *  @def    ELFLOADER_S_ALREADYSETUP
 *  @brief  The ElfLoader module has already been setup in this process.
 */
#define ELFLOADER_S_ALREADYSETUP     ELFLOADER_MAKE_SUCCESS(1)

/*!
 *  @def    ELFLOADER_S_OPENHANDLE
 *  @brief  Other ElfLoader clients have still setup the ElfLoader module.
 */
#define ELFLOADER_S_SETUP            ELFLOADER_MAKE_SUCCESS(2)

/*!
 *  @def    ELFLOADER_S_OPENHANDLE
 *  @brief  Other ElfLoader handles are still open in this process.
 */
#define ELFLOADER_S_OPENHANDLE       ELFLOADER_MAKE_SUCCESS(3)

/*!
 *  @def    ELFLOADER_S_ALREADYEXISTS
 *  @brief  The ElfLoader instance has already been created/opened in this
 *          process
 */
#define ELFLOADER_S_ALREADYEXISTS    ELFLOADER_MAKE_SUCCESS(4)


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief  Module configuration structure.
 */
typedef struct ElfLoader_Config {
    UInt32 reserved;
    /*!< Reserved value. */
} ElfLoader_Config;

/*!
 *  @brief  Configuration parameters specific to this processor.
 */
typedef struct ElfLoader_Params_tag {
    UInt32 reserved;
    /*!< Reserved field (not currently required) */
} ElfLoader_Params;


/*!
 *  @brief  ElfLoader instance object.
 */
typedef struct ElfLoader_Object_tag {
    Ptr                     elfObject;
    /*!< Object used by the generic ELF parser. */
    Ptr                     elfLoaderObject;
    /*!< Internal object used by ELF Loader module. */
} ElfLoader_Object, *ElfLoader_Handle;


/* =============================================================================
 *  APIs
 * =============================================================================
 */

/* Function to get the default configuration for the ElfLoader module. */
Void ElfLoader_getConfig (ElfLoader_Config * cfg);

/* Function to setup the ElfLoader module. */
Int ElfLoader_setup (ElfLoader_Config * cfg);

/* Function to destroy the ElfLoader module. */
Int ElfLoader_destroy (Void);

/* Function to initialize the parameters for this loader instance. */
Void ElfLoader_Params_init (ElfLoader_Handle handle,
                             ElfLoader_Params * params);

/* Function to create an instance of this loader. */
ElfLoader_Handle ElfLoader_create (      UInt16              procId,
                                     const ElfLoader_Params * params);

/* Function to delete an instance of this loader. */
Int ElfLoader_delete (ElfLoader_Handle * handlePtr);

/* Function to open an instance of this loader. */
Int ElfLoader_open (ElfLoader_Handle * handlePtr, UInt16 procId);

/* Function to close an instance of this loader. */
Int ElfLoader_close (ElfLoader_Handle * handlePtr);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* ElfLoader_H_0x1bc5 */
