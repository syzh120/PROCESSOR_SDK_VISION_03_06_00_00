/**
 *  @file   OsalThread.h
 *
 *  @brief      Kernel utils thread interface definitions.
 *
 *              This interface abstracts the kernel side thread
 *              implementation.
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


#ifndef OSALTHREAD_H_0x6833
#define OSALTHREAD_H_0x6833


/* OSAL and utils */


#if defined (__cplusplus)
extern "C" {
#endif


/*!
 *  @def    OSALTHREAD_MODULEID
 *  @brief  Module ID for OsalThread OSAL module.
 */
#define OSALTHREAD_MODULEID                 (UInt16) 0x6833

/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */
/*!
* @def   OSALTHREAD_STATUSCODEBASE
* @brief Stauts code base for MEMORY module.
*/
#define OSALTHREAD_STATUSCODEBASE      (OSALTHREAD_MODULEID << 12u)

/*!
* @def   OSALTHREAD_MAKE_FAILURE
* @brief Convert to failure code.
*/
#define OSALTHREAD_MAKE_FAILURE(x)    ((Int) (0x80000000  \
                                       + (OSALTHREAD_STATUSCODEBASE + (x))))
/*!
* @def   OSALTHREAD_MAKE_SUCCESS
* @brief Convert to success code.
*/
#define OSALTHREAD_MAKE_SUCCESS(x)      (OSALTHREAD_STATUSCODEBASE + (x))

/*!
* @def   OSALTHREAD_E_MEMORY
* @brief Indicates OsalThread alloc/free failure.
*/
#define OSALTHREAD_E_MEMORY             OSALTHREAD_MAKE_FAILURE(1)

/*!
* @def   OSALTHREAD_E_INVALIDARG
* @brief Invalid argument provided
*/
#define OSALTHREAD_E_INVALIDARG         OSALTHREAD_MAKE_FAILURE(2)

/*!
* @def   OSALTHREAD_E_FAIL
* @brief Generic failure
*/
#define OSALTHREAD_E_FAIL               OSALTHREAD_MAKE_FAILURE(3)

/*!
* @def   OSALTHREAD_SUCCESS
* @brief Operation successfully completed
*/
#define OSALTHREAD_SUCCESS              OSALTHREAD_MAKE_SUCCESS(0)


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief  Declaration for the OsalThread object handle.
 *          Definition of OsalThread_Object is not exposed.
 */
typedef struct OsalThread_Object * OsalThread_Handle;

/*!
 *  @brief  Callback function type
 */
typedef Void (*OsalThread_CallbackFxn) (Ptr fxnArgs);


/*!
 *  @brief   Enumerates the different values of thread priorities.
 */
typedef enum {
    OsalThread_Priority_Low       = 0u,
    /*!< Low priority */
    OsalThread_Priority_Medium    = 1u,
    /*!< Medium priority */
    OsalThread_Priority_High      = 2u,
    /*!< High priority */
    OsalThread_Priority_EndValue  = 3u
    /*!< End delimiter indicating start of invalid values for this enum */
} OsalThread_Priority;

/*!
 *  @brief   Enumerates the types of thread priorities.
 */
typedef enum {
    OsalThread_PriorityType_Generic    = 0u,
    /*!< Generic priority is to be used for fully portable code */
    OsalThread_PriorityType_OsSpecific = 1u,
    /*!< OS specific priority is to be used for higher granularity */
    OsalThread_PriorityType_EndValue   = 2u
    /*!< End delimiter indicating start of invalid values for this enum */
} OsalThread_PriorityType;


/*!
 *  @brief   Structure containing information required for unmapping a
 *           memory region.
 */
typedef struct OsalThread_Params_tag {
    OsalThread_PriorityType  priorityType;
    /*!< Priority type to be used. */
    UInt32  priority;
    /*!< Thread priority to be used. Interpretation of this value depends on
         priority type specified in this structure. */
    Bool    once;
    /*!< Indicates whether thread function has to be executed once or in a loop
     */
} OsalThread_Params;


/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Initialize the thread module. */
Int32 OsalThread_setup (Void);

/* Finalize the thread module. */
Int32 OsalThread_destroy (Void);

/* create the thread. */
OsalThread_Handle OsalThread_create (OsalThread_CallbackFxn fxn,
                                     Ptr                    fxnArgs,
                                     OsalThread_Params *    params);

/* Destroys the thread. */
Int OsalThread_delete (OsalThread_Handle * threadHandle);

/* Disables the specific thread. */
Void OsalThread_disableThread (OsalThread_Handle threadHandle);

/* Enables the specific thread. */
Void OsalThread_enableThread (OsalThread_Handle threadHandle);

/* Disables all threads created using this module. */
Void OsalThread_disable (Void);

/* Enable all threads created using this module. */
Void OsalThread_enable (Void);

/* Activate this thread. This function may gets invoked from ISR context. */
Void OsalThread_activate (OsalThread_Handle threadHandle);

/* Yield this thread. */
Void OsalThread_yield (OsalThread_Handle threadHandle);

/* Sleep this thread for specific time in milli-seconds. */
Void OsalThread_sleep (UInt32 time);

/* Delay this thread for specific time in milli-seconds. Does not schedule out
 * this thread.
 */
Void OsalThread_delay (UInt32 time);

/* Checks if current context is a thread context. */
Bool OsalThread_inThread (Void);

/* Wait for thread completion */
Void OsalThread_waitForThread (OsalThread_Handle threadHandle);

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* ifndef OSALTHREAD_H_0x6833 */
