/*
 *  @file  OsalEvent.h
 *
 *  @brief      Events interface definitions.
 *
 *              This is used iprovide event based
 *              synchronisation. the implementation is done using the wait
 *              queues.
 *  ============================================================================
 *
 *  Copyright (c) 20010-2011, Texas Instruments Incorporated
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

#ifndef _OSALEVENT_H_0xB9F8
#define _OSALEVENT_H_0xB9F8


#if defined (__cplusplus)
extern "C" {
#endif

/*!
 *  @def    OSALEVENT_MODULEID
 *  @brief  Module ID for OsalEvent OSAL module.
 */
#define OSALEVENT_MODULEID                     (UInt16) 0x3046

/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */
/*!
* @def   OSALEVENT_ERRORCODEBASE
* @brief errorcode base for OSALEVENT object.
*/
#define OSALEVENT_ERRORCODEBASE                (0xB9F8 << 12u)

/*!
* @def   OSALEVENT_MAKE_FAILURE
* @brief macro to make error code.
*/
#define OSALEVENT_MAKE_FAILURE(x)          ((Int) (0x80000000  \
                                           + (OSALEVENT_ERRORCODEBASE + (x))))
/*!
* @def   OSALEVENT_MAKE_SUCCESS
* @brief macro to make success code.
*/
#define OSALEVENT_MAKE_SUCCESS(x)            (OSALEVENT_ERRORCODEBASE + (x))

/*!
* @def   OSALEVENT_E_MEMORY
* @brief macro to describe the Memory alloc/free failure.
*/
#define OSALEVENT_E_MEMORY                    OSALEVENT_MAKE_FAILURE(1)

/*!
* @def   OSALEVENT_E_SPINLOCK
* @brief macro to describe the SPINLOCK operation failures.
*/
#define OSALEVENT_E_SPINLOCK                  OSALEVENT_MAKE_FAILURE(2)

/*!
* @def   OSALEVENT_E_SYNCFAIL
* @brief macro to describe the synchronisation failure.
*/
#define OSALEVENT_E_SYNCFAIL                  OSALEVENT_MAKE_FAILURE(3)

/*!
* @def   OSALEVENT_E_TIMEOUT
* @brief macro to describe the timeout failure at wait state.
*/
#define OSALEVENT_E_TIMEOUT                   OSALEVENT_MAKE_FAILURE(4)

/*!
* @def   OSALEVENT_E_RESTARTSYS
* @brief macro to describe the timeout failure at wait state.
*/
#define OSALEVENT_E_RESTARTSYS                OSALEVENT_MAKE_FAILURE(5)

/*!
* @def   OSALEVENT_SUCCESS
* @brief macro to make success code.
*/
#define OSALEVENT_SUCCESS                     OSALEVENT_MAKE_SUCCESS(0)


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @def    OSAL_WAIT_FOREVER
 *  @brief  Macro to describe wait forever scenario.
 */
#define OSAL_WAIT_FOREVER           (~((UInt32) 0u))

/*!
 *  @def    OSAL_WAIT_NONE
 *  @brief  Macro to describe no wait secnario.
 */
#define OSAL_WAIT_NONE                ((UInt32) 0u)


/*!
 *  @brief  Declaration for the OsalEvent object handle.
 *          Definition of OsalEvent_Object is not exposed.
 */
typedef struct OsalEvent_Object * OsalEvent_Handle;


/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Function to create/open an Event Kernel object */
OsalEvent_Handle OsalEvent_create (Void);

/* Function to close an Event Kernel object */
Int OsalEvent_delete (OsalEvent_Handle handle);

/* Function to Reset an Event Kernel object */
Int OsalEvent_reset (OsalEvent_Handle handle);

/* Function to Set an Event Kernel object */
Int OsalEvent_set (OsalEvent_Handle handle);

/* Function to wait on an Event Kernel object with timeout if any*/
Int OsalEvent_wait (OsalEvent_Handle handle, UInt32 timeout);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* ifndef MEMORYOS_H_0xB9F8*/
