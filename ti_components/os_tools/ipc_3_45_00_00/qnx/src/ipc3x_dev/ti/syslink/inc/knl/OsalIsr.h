/**
 *  @file   OsalIsr.h
 *
 *  @brief      Kernel ISR interface definitions.
 *
 *              This abstracts the ISR interface on kernel side code.
 *              Installs the handler for individual IRQs and handlers
 *              are invoked as the interrupts occur.
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


#ifndef OSALISR_H_0x93FE
#define OSALISR_H_0x93FE


/* OSAL and utils */


#if defined (__cplusplus)
extern "C" {
#endif


/*!
 *  @def    OSALISR_MODULEID
 *  @brief  Module ID for OsalIsr OSAL module.
 */
#define OSALISR_MODULEID                 (UInt16) 0x93FE

/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */
/*!
* @def   OSALISR_STATUSCODEBASE
* @brief Stauts code base for MEMORY module.
*/
#define OSALISR_STATUSCODEBASE      (OSALISR_MODULEID << 12u)

/*!
* @def   OSALISR_MAKE_FAILURE
* @brief Convert to failure code.
*/
#define OSALISR_MAKE_FAILURE(x)    ((Int) (0x80000000  \
                                    + (OSALISR_STATUSCODEBASE + (x))))
/*!
* @def   OSALISR_MAKE_SUCCESS
* @brief Convert to success code.
*/
#define OSALISR_MAKE_SUCCESS(x)      (OSALISR_STATUSCODEBASE + (x))

/*!
* @def   OSALISR_E_MEMORY
* @brief Indicates OsalIsr alloc/free failure.
*/
#define OSALISR_E_MEMORY             OSALISR_MAKE_FAILURE(1)

/*!
* @def   OSALISR_E_INVALIDARG
* @brief Invalid argument provided
*/
#define OSALISR_E_INVALIDARG         OSALISR_MAKE_FAILURE(2)

/*!
* @def   OSALISR_E_FAIL
* @brief Generic failure
*/
#define OSALISR_E_FAIL               OSALISR_MAKE_FAILURE(3)

/*!
* @def   OSALISR_E_THREAD
* @brief Failed to create a thread
*/
#define OSALISR_E_THREAD             OSALISR_MAKE_FAILURE(4)

/*!
* @def   OSALISR_E_IRQINSTALL
* @brief Failed to install/install ISR with the OS.
*/
#define OSALISR_E_IRQINSTALL         OSALISR_MAKE_FAILURE(5)

/*!
 *  @def    OSALISR_E_HANDLE
 *  @brief  Invalid handle provided
 */
#define OSALISR_E_HANDLE             OSALISR_MAKE_FAILURE(6)

/*!
* @def   OSALISR_SUCCESS
* @brief Operation successfully completed
*/
#define OSALISR_SUCCESS              OSALISR_MAKE_SUCCESS(0)


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief  Declaration for the OsalIsr object handle.
 *          Definition of OsalIsr_Object is not exposed.
 */
typedef struct OsalIsr_Object * OsalIsr_Handle;

/*!
 *  @brief  Callback function type. Returns whether interrupt has been handled.
 */
typedef Bool (*OsalIsr_CallbackFxn) (Ptr fxnArgs);

/*!
 *  @brief  Function type for function to:
 *          1. Check if the expected interrupt has been generated. This is only
 *             relevant for shared interrupts. For non-shared, TRUE will always
 *             be returned.
 *          2. Clear the hardware interrupt
 */
typedef Bool (*OsalIsr_CheckAndClearFxn) (Ptr fxnArgs);


/*!
 *  @brief   Enumerates the types of semaphores
 */
typedef enum {
    OsalIsr_State_Installed          = 0u,
    /*!< ISR is installed. */
    OsalIsr_State_Uninstalled        = 1u,
    /*!< ISR is not installed and enabled. */
    OsalIsr_State_Disabled           = 3u,
    /*!< ISR is disabled. */
    OsalIsr_State_EndValue           = 4u
    /*!< End delimiter indicating start of invalid values for this enum */
} OsalIsr_State;


/*!
 *  @brief   Parameters for ISR creation.
 */
typedef struct OsalIsr_Params_tag {
    Bool                     sharedInt;
    /*!< Is it a shared interrupt? */
    OsalIsr_CheckAndClearFxn checkAndClearFxn;
    /*!< Function for CheckAndClear */
    Ptr                      fxnArgs;
    /*!< Args for checkAndClear function */
    UInt32                   intId;
    /*!< Interrupt ID to be used. */
} OsalIsr_Params;


/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Function to create an ISR object.*/
OsalIsr_Handle OsalIsr_create (OsalIsr_CallbackFxn fxn,
                               Ptr                 fxnArgs,
                               OsalIsr_Params *    params);

/* Function to Delete the ISR object.*/
Int OsalIsr_delete (OsalIsr_Handle * isrHandle);

/* Function to Install an interrupt service routine.*/
Int OsalIsr_install (OsalIsr_Handle isrHandle);

/* Function to Uninstalls an ISR. */
Int OsalIsr_uninstall (OsalIsr_Handle isrHandle);

/* Function to disable the specified ISR. */
Void OsalIsr_disableIsr (OsalIsr_Handle isrHandle);

/* Function to enable the specified ISR. */
Void OsalIsr_enableIsr (OsalIsr_Handle isrHandle);

/* Function to disable all interrupts */
UInt32 OsalIsr_disable (Void);

/* Function to enable all interrupts */
Void OsalIsr_restore (UInt32 flags);

/* Function to Returns the state of an ISR.*/
OsalIsr_State OsalIsr_getState (OsalIsr_Handle isrHandle);

/* Checks if current context is an interrupt context. */
Bool OsalIsr_inIsr (Void);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* ifndef OSALISR_H_0x93FE */
