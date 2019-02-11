/**
 *  @file   Loader.h
 *
 *  @brief      Header file for the generic loader implementation.
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


#ifndef Loader_H_0x485f
#define Loader_H_0x485f


/* Module level headers */
#include <LoaderDefs.h>


#if defined (__cplusplus)
extern "C" {
#endif


/*!
 *  @def    LOADER_MODULEID
 *  @brief  Module ID for loader.
 */
#define LOADER_MODULEID           (UInt16) 0x485f

/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */

/*!
 *  @def    LOADER_STATUSCODEBASE
 *  @brief  Error code base for ProcMgr.
 */
#define LOADER_STATUSCODEBASE      (LOADER_MODULEID << 12u)

/*!
 *  @def    LOADER_MAKE_FAILURE
 *  @brief  Macro to make failure code.
 */
#define LOADER_MAKE_FAILURE(x)    ((Int)(  0x80000000l                         \
                                         | (LOADER_STATUSCODEBASE + (x))))

/*!
 *  @def    LOADER_MAKE_SUCCESS
 *  @brief  Macro to make success code.
 */
#define LOADER_MAKE_SUCCESS(x)    (LOADER_STATUSCODEBASE + (x))

/*!
 *  @def    LOADER_E_INVALIDARG
 *  @brief  Argument passed to a function is invalid.
 */
#define LOADER_E_INVALIDARG       LOADER_MAKE_FAILURE(1u)

/*!
 *  @def    LOADER_E_MEMORY
 *  @brief  Memory allocation failed.
 */
#define LOADER_E_MEMORY           LOADER_MAKE_FAILURE(2u)

/*!
 *  @def    LOADER_E_FAIL
 *  @brief  Generic failure.
 */
#define LOADER_E_FAIL             LOADER_MAKE_FAILURE(3u)

/*!
 *  @def    LOADER_E_NOTSUPPORTED
 *  @brief  Functionality is not supported
 */
#define LOADER_E_NOTSUPPORTED     LOADER_MAKE_FAILURE(4u)

/*!
 *  @def    LOADER_E_NOTIMPL
 *  @brief  Functionality is not implemented
 */
#define LOADER_E_NOTIMPL          LOADER_MAKE_FAILURE(5u)

/*!
 *  @def    LOADER_E_INIT
 *  @brief  A required dependency has not been initialized
 */
#define LOADER_E_INIT             LOADER_MAKE_FAILURE(6u)

/*!
 *  @def    LOADER_E_ALREADYEXIST
 *  @brief  Specified loader name already exists.
 */
#define LOADER_E_ALREADYEXIST     LOADER_MAKE_FAILURE(7u)

/*!
 *  @def    LOADER_E_FILE
 *  @brief  A file error occurred
 */
#define LOADER_E_FILE             LOADER_MAKE_FAILURE(8u)

/*!
 *  @def    LOADER_E_FILEOPEN
 *  @brief  Failure to open the file.
 */
#define LOADER_E_FILEOPEN         LOADER_MAKE_FAILURE(9u)

/*!
 *  @def    LOADER_E_CORRUPTFILE
 *  @brief  The file is not in a supported format
 */
#define LOADER_E_CORRUPTFILE      LOADER_MAKE_FAILURE(0xA)

/*!
 *  @def    LOADER_E_HANDLE
 *  @brief  Invalid object handle specified
 */
#define LOADER_E_HANDLE           LOADER_MAKE_FAILURE(0xB)

/*!
 *  @def    LOADER_E_NOTFOUND
 *  @brief  Specified Loader not found.
 */
#define LOADER_E_NOTFOUND         LOADER_MAKE_FAILURE(0xC)

/*!
 *  @def    LOADER_E_OSFAILURE
 *  @brief  Failure in an OS-specific operation.
 */
#define LOADER_E_OSFAILURE        LOADER_MAKE_FAILURE(0xD)

/*!
 *  @def    LOADER_E_INVALIDSTATE
 *  @brief  Module not initialized
 */
#define LOADER_E_INVALIDSTATE     LOADER_MAKE_FAILURE(0xE)

/*!
 *  @def    LOADER_SUCCESS
 *  @brief  Operation successful.
 */
#define LOADER_SUCCESS            LOADER_MAKE_SUCCESS(0)

/*!
 *  @def    LOADER_S_ALREADYSETUP
 *  @brief  Module is already initialized.
 */
#define LOADER_S_ALREADYSETUP     LOADER_MAKE_SUCCESS(1)


/* =============================================================================
 *  Macros and types
 *  See loaderdefs.h
 * =============================================================================
 */

/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Function to attach to the Loader. */
Int Loader_attach (Loader_Handle handle, Loader_AttachParams * params);

/* Function to detach from the Loader. */
Int Loader_detach (Loader_Handle handle);

/* Function to load the slave processor.
 * Returns file ID in the passed fileId parameter.
 */
Int Loader_load (Loader_Handle handle,
                 String        imagePath,
                 UInt32        argc,
                 String *      argv,
                 Ptr           params,
                 UInt32 *      fileId);

/* Function to function to load symbols for the specified file. This will allow
 * the symbols to be usable when linked against another object file.
 * External symbols will be made available for global symbol linkage.
 * NOTE: This function is only relevant for dynamic loader. Other loaders can
 *       return LOADER_E_NOTIMPL.
 */
Int Loader_loadSymbols (Loader_Handle handle,
                        String        imagePath,
                        Ptr           params);

/* Function to unload the previously loaded file on the slave processor.
 * The fileId received from the load function must be passed to this function.
 */
Int Loader_unload (Loader_Handle handle, UInt32 fileId);

/* Function to retrieve the target address of a symbol from the specified file.
 * The fileId received from the load function must be passed to this function.
 */
Int Loader_getSymbolAddress (Loader_Handle handle,
                             UInt32        fileId,
                             String        symName,
                             UInt32 *      symValue);

/* Function to retrieve the entry point of the specified file.
 * The fileId received from the load function must be passed to this function.
 */
Int Loader_getEntryPt (Loader_Handle handle,
                       UInt32        fileId,
                       UInt32 *      entryPt);
/* Function that returns section information given the name of section and
 * number of bytes to read
 */
Int Loader_getSectionInfo (Loader_Handle         handle,
                           UInt32                fileId,
                           String                sectionName,
                           ProcMgr_SectionInfo * sectionInfo);

/* Function that returns section data in a buffer given section Info struct
 * returned by a previous call to Loader_getSectionInfo.
 */
Int Loader_getSectionData (Loader_Handle        handle,
                           UInt32                fileId,
                           ProcMgr_SectionInfo * sectionInfo,
                           Ptr                   buffer);

/* =============================================================================
 *  Compatibility layer for SYSBIOS
 * =============================================================================
 */
#define Loader_MODULEID           LOADER_MODULEID
#define Loader_STATUSCODEBASE     LOADER_STATUSCODEBASE
#define Loader_MAKE_FAILURE       LOADER_MAKE_FAILURE
#define Loader_MAKE_SUCCESS       LOADER_MAKE_SUCCESS
#define Loader_E_INVALIDARG       LOADER_E_INVALIDARG
#define Loader_E_MEMORY           LOADER_E_MEMORY
#define Loader_E_FAIL             LOADER_E_FAIL
#define Loader_E_NOTSUPPORTED     LOADER_E_NOTSUPPORTED
#define Loader_E_NOTIMPL          LOADER_E_NOTIMPL
#define Loader_E_INIT             LOADER_E_INIT
#define Loader_E_ALREADYEXIST     LOADER_E_ALREADYEXIST
#define Loader_SUCCESS            LOADER_SUCCESS


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* Loader_H_0x485f */
