/**
 *  @file   PwrMgr.h
 *
 *  @brief      Header file for the generic Power Manager implementation.
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


#ifndef PwrMgr_H_0x783c
#define PwrMgr_H_0x783c


/* Module level headers */
#include <PwrDefs.h>


#if defined (__cplusplus)
extern "C" {
#endif


/*!
 *  @def    PWRMGR_MODULEID
 *  @brief  Module ID for loader.
 */
#define PWRMGR_MODULEID           (UInt16) 0x783c

/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */

/*!
 *  @def    PWRMGR_STATUSCODEBASE
 *  @brief  Error code base for ProcMgr.
 */
#define PWRMGR_STATUSCODEBASE      (PWRMGR_MODULEID << 12u)

/*!
 *  @def    PWRMGR_MAKE_FAILURE
 *  @brief  Macro to make failure code.
 */
#define PWRMGR_MAKE_FAILURE(x)    ((Int)(  0x80000000                          \
                                         | (PWRMGR_STATUSCODEBASE + (x))))

/*!
 *  @def    PWRMGR_MAKE_SUCCESS
 *  @brief  Macro to make success code.
 */
#define PWRMGR_MAKE_SUCCESS(x)    (PWRMGR_STATUSCODEBASE + (x))

/*!
 *  @def    PWRMGR_E_INVALIDARG
 *  @brief  Argument passed to a function is invalid.
 */
#define PWRMGR_E_INVALIDARG       PWRMGR_MAKE_FAILURE(1)

/*!
 *  @def    PWRMGR_E_MEMORY
 *  @brief  Memory allocation failed.
 */
#define PWRMGR_E_MEMORY           PWRMGR_MAKE_FAILURE(2)

/*!
 *  @def    PWRMGR_E_FAIL
 *  @brief  Generic failure.
 */
#define PWRMGR_E_FAIL             PWRMGR_MAKE_FAILURE(3)

/*!
 *  @def    PWRMGR_E_HANDLE
 *  @brief  Invalid object handle specified
 */
#define PWRMGR_E_HANDLE           PWRMGR_MAKE_FAILURE(4)

/*!
 *  @def    PWRMGR_E_NOTSUPPORTED
 *  @brief  Functionality is not supported
 */
#define PWRMGR_E_NOTSUPPORTED     PWRMGR_MAKE_FAILURE(5)

/*!
 *  @def    PWRMGR_E_NOTIMPL
 *  @brief  Functionality is not implemented
 */
#define PWRMGR_E_NOTIMPL          PWRMGR_MAKE_FAILURE(6)

/*!
 *  @def    PWRMGR_E_INIT
 *  @brief  A required dependency has not been initialized
 */
#define PWRMGR_E_INIT             PWRMGR_MAKE_FAILURE(7)

/*!
 *  @def    PWRMGR_E_ALREADYEXIST
 *  @brief  Specified PwrMgr already exists.
 */
#define PWRMGR_E_ALREADYEXIST     PWRMGR_MAKE_FAILURE(8)

/*!
 *  @def    PWRMGR_E_INVALIDSTATE
 *  @brief  Invalid state of the PwrMgr
 */
#define PWRMGR_E_INVALIDSTATE     PWRMGR_MAKE_FAILURE(9)

/*!
 *  @def    PWRMGR_E_NOTFOUND
 *  @brief  Specified PwrMgr not found.
 */
#define PWRMGR_E_NOTFOUND         PWRMGR_MAKE_FAILURE(0xA)

/*!
 *  @def    PWRMGR_E_OSFAILURE
 *  @brief  Failure in an OS-specific operation.
 */
#define PWRMGR_E_OSFAILURE        PWRMGR_MAKE_FAILURE(0xB)

/*!
 *  @def    PWRMGR_SUCCESS
 *  @brief  Operation successful.
 */
#define PWRMGR_SUCCESS            PWRMGR_MAKE_SUCCESS(0)


/* =============================================================================
 *  Macros and types
 *  See pwrdefs.h
 * =============================================================================
 */

/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Function to attach to the PwrMgr. */
Int PwrMgr_attach (PwrMgr_Handle handle, PwrMgr_AttachParams * params);

/* Function to detach from the PwrMgr. */
Int PwrMgr_detach (PwrMgr_Handle handle);

/* Function to turn on power for the Slave processor. */
Int PwrMgr_on (PwrMgr_Handle handle);

/* Function to turn off power for the Slave processor. */
Int PwrMgr_off (PwrMgr_Handle handle, Bool force);

/* =============================================================================
 *  Compatibility layer for SYSBIOS
 * =============================================================================
 */
#define PwrMgr_MODULEID           PWRMGR_MODULEID
#define PwrMgr_STATUSCODEBASE     PWRMGR_STATUSCODEBASE
#define PwrMgr_MAKE_FAILURE       PWRMGR_MAKE_FAILURE
#define PwrMgr_MAKE_SUCCESS       PWRMGR_MAKE_SUCCESS
#define PwrMgr_E_INVALIDARG       PWRMGR_E_INVALIDARG
#define PwrMgr_E_MEMORY           PWRMGR_E_MEMORY
#define PwrMgr_E_FAIL             PWRMGR_E_FAIL
#define PwrMgr_E_NOTSUPPORTED     PWRMGR_E_NOTSUPPORTED
#define PwrMgr_E_NOTIMPL          PWRMGR_E_NOTIMPL
#define PwrMgr_E_INIT             PWRMGR_E_INIT
#define PwrMgr_E_ALREADYEXIST     PWRMGR_E_ALREADYEXIST
#define PwrMgr_SUCCESS            PWRMGR_SUCCESS


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* PwrMgr_H_0x783c */
