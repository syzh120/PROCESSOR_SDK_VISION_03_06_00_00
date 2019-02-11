/**
 *  @file   OsalSpinlock.h
 *
 *  @brief      SpinLock interface definitions.
 *
 *              This abstracts the kernel side Spin Lock which is used in
 *              halting the CPU for some specified amout of time. this
 *              interface covers all aspects of SpinLock required in Ipc.
 *
 *
 *  @ver        02.00.00.46_alpha1
 *
 *  ============================================================================
 *
 *  Copyright (c) 2008-2015, Texas Instruments Incorporated
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


#ifndef OSALSPINLOCK_H_0x188E
#define OSALSPINLOCK_H_0x188E


/* OSAL and utils */


#if defined (__cplusplus)
extern "C" {
#endif


/*!
 *  @def    OSALSPINLOCK_MODULEID
 *  @brief  Module ID for Memory OSAL module.
 */
#define OSALSPINLOCK_MODULEID                 (UInt16) 0x188E

/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */
/*!
* @def   OSALSPINLOCK_STATUSCODEBASE
* @brief Stauts code base for OsalSpinlock module.
*/
#define OSALSPINLOCK_STATUSCODEBASE      (OSALSPINLOCK_MODULEID << 12u)

/*!
* @def   OSALSPINLOCK_MAKE_FAILURE
* @brief Convert to failure code.
*/
#define OSALSPINLOCK_MAKE_FAILURE(x)  ((Int) (0x80000000  \
                                       + (OSALSPINLOCK_STATUSCODEBASE + (x))))
/*!
* @def   OSALSPINLOCK_MAKE_SUCCESS
* @brief Convert to success code.
*/
#define OSALSPINLOCK_MAKE_SUCCESS(x)      (OSALSPINLOCK_STATUSCODEBASE + (x))

/*!
* @def   OSALSPINLOCK_E_MEMORY
* @brief Indicates Memory alloc/free failure.
*/
#define OSALSPINLOCK_E_MEMORY             OSALSPINLOCK_MAKE_FAILURE(1)

/*!
* @def   OSALSPINLOCK_E_INVALIDARG
* @brief Invalid argument provided
*/
#define OSALSPINLOCK_E_INVALIDARG         OSALSPINLOCK_MAKE_FAILURE(2)

/*!
* @def   OSALSPINLOCK_E_FAIL
* @brief Generic failure
*/
#define OSALSPINLOCK_E_FAIL               OSALSPINLOCK_MAKE_FAILURE(3)

/*!
 *  @def    OSALSPINLOCK_E_HANDLE
 *  @brief  Invalid handle provided
 */
#define OSALSPINLOCK_E_HANDLE             OSALSPINLOCK_MAKE_FAILURE(4)

/*!
* @def   OSALSPINLOCK_SUCCESS
* @brief Operation successfully completed
*/
#define OSALSPINLOCK_SUCCESS              OSALSPINLOCK_MAKE_SUCCESS(0)


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief  Declaration for the OsalSpinlock object handle.
 *          Definition of OsalSpinlock_Object is not exposed.
 */
typedef struct OsalSpinlock_Object * OsalSpinlock_Handle;

/*!
 *  @brief   Enumerates the types of spinlocks
 */
typedef enum {
    OsalSpinlock_Type_Normal         = 0u,
    /*!< Normal spinlock. Callable from ISR context. */
    OsalSpinlock_Type_Raw            = 1u,
    /*!< Raw spinlock. In OSes where normal spinlock falls back to mutex due to
         real-time preemption, this implements a 'real' raw spinlock. */
    OsalSpinlock_Type_EndValue       = 2u
    /*!< End delimiter indicating start of invalid values for this enum */
} OsalSpinlock_Type;


/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Creates the Spinlock Object. */
OsalSpinlock_Handle OsalSpinlock_create (OsalSpinlock_Type type);

/* Destroys the Spinlock Object. */
Int OsalSpinlock_delete (OsalSpinlock_Handle * lockHandle);

/* Function to begin the spinlock operation. Returns key. */
UInt32 OsalSpinlock_enter (OsalSpinlock_Handle lockHandle);

/* End protection of code through spin lock. Takes in key received from enter */
Void OsalSpinlock_leave (OsalSpinlock_Handle lockHandle, UInt32 key);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* ifndef OSALSPINLOCK_H_0x188E */
