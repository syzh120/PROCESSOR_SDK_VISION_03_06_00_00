/**
 *  @file   RscTable.h
 *
 *  @brief      Definitions for the RscTable interface.
 *
 *  ============================================================================
 *
 *  Copyright (c) 2012-2015, Texas Instruments Incorporated
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


#ifndef RscTable_H
#define RscTable_H

#if defined (__cplusplus)
extern "C" {
#endif

#include <ti/syslink/SysLink.h>
#include <rsc_types.h>
#include <ti/syslink/ProcMgr.h>
#include <Processor.h>

/*!
 *  @def    RSCTABLE_MODULEID
 *  @brief  Module ID for rsctable.
 */
#define RSCTABLE_MODULEID           (UInt16) 0x6a87

/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */

/*!
 *  @def    RSCTABLE_STATUSCODEBASE
 *  @brief  Error code base for RscTable.
 */
#define RSCTABLE_STATUSCODEBASE      (RSCTABLE_MODULEID << 12u)

/*!
 *  @def    RSCTABLE_MAKE_FAILURE
 *  @brief  Macro to make failure code.
 */
#define RSCTABLE_MAKE_FAILURE(x)    ((Int)(  0x80000000                       \
                                            | (RSCTABLE_STATUSCODEBASE + (x))))

/*!
 *  @def    RSCTABLE_MAKE_SUCCESS
 *  @brief  Macro to make success code.
 */
#define RSCTABLE_MAKE_SUCCESS(x)    (RSCTABLE_STATUSCODEBASE + (x))

/*!
 *  @def    RSCTABLE_E_INVALIDARG
 *  @brief  Argument passed to a function is invalid.
 */
#define RSCTABLE_E_INVALIDARG       RSCTABLE_MAKE_FAILURE(1)

/*!
 *  @def    RSCTABLE_E_MEMORY
 *  @brief  Memory allocation failed.
 */
#define RSCTABLE_E_MEMORY           RSCTABLE_MAKE_FAILURE(2)

/*!
 *  @def    RSCTABLE_E_FAIL
 *  @brief  Generic failure.
 */
#define RSCTABLE_E_FAIL             RSCTABLE_MAKE_FAILURE(3)

/*!
 *  @def    RSCTABLE_E_NOTSUPPORTED
 *  @brief  Functionality is not supported
 */
#define RSCTABLE_E_NOTSUPPORTED     RSCTABLE_MAKE_FAILURE(4)

/*!
 *  @def    RSCTABLE_E_NOTIMPL
 *  @brief  Functionality is not implemented
 */
#define RSCTABLE_E_NOTIMPL          RSCTABLE_MAKE_FAILURE(5)

/*!
 *  @def    RSCTABLE_SUCCESS
 *  @brief  Operation successful.
 */
#define RSCTABLE_SUCCESS            RSCTABLE_MAKE_SUCCESS(0)


/*
 *  @brief  Defines RscTable object handle
 */
typedef struct RscTable_Object * RscTable_Handle;

RscTable_Handle RscTable_alloc (Char * fileName, UInt16 procId);

Int RscTable_free (RscTable_Handle * handle);

Int RscTable_process (UInt16 procId, Bool tryAlloc, UInt32 * numBlocks,
    Processor_Handle procHandle, ProcMgr_BootMode bootMode);

Int RscTable_getMemEntries (UInt16 procId, Ipc_MemEntry * memEntries,
                            UInt32 * numMemEntries);

Int RscTable_getInfo (UInt16 procId, UInt32 type, UInt32 extra, UInt32 * da,
                      UInt32 *pa, UInt32 * len);

Int RscTable_update (UInt16 procId, ProcMgr_Handle procHandle);

Int RscTable_free (RscTable_Handle * handle);

Int RscTable_setStatus (UInt16 procId, UInt32 value);

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* RscTable_H */
