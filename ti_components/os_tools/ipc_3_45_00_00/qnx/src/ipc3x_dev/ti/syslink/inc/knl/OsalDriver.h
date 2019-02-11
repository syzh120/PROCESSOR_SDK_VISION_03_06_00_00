/**
 *  @file   OsalDriver.h
 *
 *  @brief      Kernel-utils side Driver Model manager interface.
 *
 *              This abstracts the Driver Model calls interface in the Kernel
 *              code. This will expose the interface to register and unregister
 *              functions with their command ids. There will be interface also
 *              for getting the function from table. This will also interface
 *              with command ids arbitrator.
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



#ifndef OSALDRIVER_H_0x010D
#define OSALDRIVER_H_0x010D


/* OSAL and utils */
#include <ti/syslink/utils/List.h>

/* Linux specific header files */
#if defined (__cplusplus)
extern "C" {
#endif


/*!
 *  @def    OSALDRIVER_MODULEID
 *  @brief  Module ID for OsalDriver OSAL module.
 */
#define OSALDRIVER_MODULEID                 (UInt16) 0x010D

/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */
/*!
* @def   OSALDRIVER_STATUSCODEBASE
* @brief Stauts code base for MEMORY module.
*/
#define OSALDRIVER_STATUSCODEBASE      (OSALDRIVER_MODULEID << 12u)

/*!
* @def   OSALDRIVER_MAKE_FAILURE
* @brief Convert to failure code.
*/
#define OSALDRIVER_MAKE_FAILURE(x)    ((Int) (0x80000000  \
                                       + (OSALDRIVER_STATUSCODEBASE + (x))))
/*!
* @def   OSALDRIVER_MAKE_SUCCESS
* @brief Convert to success code.
*/
#define OSALDRIVER_MAKE_SUCCESS(x)      (OSALDRIVER_STATUSCODEBASE + (x))

/*!
* @def   OSALDRIVER_E_MEMORY
* @brief Indicates OsalDriver alloc/free failure.
*/
#define OSALDRIVER_E_MEMORY             OSALDRIVER_MAKE_FAILURE(1)

/*!
* @def   OSALDRIVER_E_INVALIDARG
* @brief Invalid argument provided
*/
#define OSALDRIVER_E_INVALIDARG         OSALDRIVER_MAKE_FAILURE(2)

/*!
* @def   OSALDRIVER_E_FAIL
* @brief Generic failure
*/
#define OSALDRIVER_E_FAIL               OSALDRIVER_MAKE_FAILURE(3)

/*!
* @def   OSALDRIVER_E_OUTOFRANGE
* @brief Indicates that specified value is out of range
*/
#define OSALDRIVER_E_OUTOFRANGE         OSALDRIVER_MAKE_FAILURE(4)

/*!
 *  @def    LOADER_E_FILEOPEN
 *  @brief  Failure to open the file.
 */
#define OSALDRIVER_E_FILEOPEN           OSALDRIVER_MAKE_FAILURE(5)

/*!
* @def   OSALDRIVER_E_INVALIDSTATE
* @brief Module is invalidstate
*/
#define OSALDRIVER_E_INVALIDSTATE       OSALDRIVER_MAKE_FAILURE(6)

/*!
* @def   OSALDRIVER_SUCCESS
* @brief Operation successfully completed
*/
#define OSALDRIVER_SUCCESS              OSALDRIVER_MAKE_SUCCESS(0)


/* =============================================================================
 *  Structure & Enums
 * =============================================================================
 */
/*!
 *  @brief   Kernel Driver object structure definition.
 */

/* =============================================================================
 *  APIs
 * =============================================================================
 */

/* Initialize the Driver module. */
Int32 OsalDriver_setup (Void);

/* Finalize the Driver module */
Int32 OsalDriver_destroy (Void);

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* ifndef OSALDRIVER_H_0x010D */
