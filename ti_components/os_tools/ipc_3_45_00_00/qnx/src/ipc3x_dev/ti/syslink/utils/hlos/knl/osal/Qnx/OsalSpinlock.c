/**
 *  @file   OsalSpinlock.c
 *
 *  @brief      SpinLock interface implementation.
 *
 *              This abstracts the kernel side Spin Lock which is used in
 *              halting the CPU for some specified amout of time. this
 *              interface covers all aspects of SpinLock required in Ipc.
 *
 *  @ver        02.00.00.46_alpha1
 *
 *  ============================================================================
 *
 *  Copyright (c) 2010-2015, Texas Instruments Incorporated
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

#include <pthread.h>

/* Standard headers */
#include <ti/syslink/Std.h>

/* OSAL and kernel utils */
#include <OsalSpinlock.h>
#include <ti/syslink/utils/Trace.h>
#include <ti/syslink/utils/Memory.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief   This object is used by spinlock APIs.
 */
typedef struct OsalSpinlock_Object_tag {
    pthread_mutex_t lock;
    /* !< handle to lock object used by OS.*/
    /* TBD: Needed otherwise size of object comes 0. */
} OsalSpinlock_Object;


/* =============================================================================
 * APIs
 * =============================================================================
 */
/*!
 *  @brief      Creates the Spinlock Object.
 *
 *  @param      type    Type of spinlock (Normal or Raw)
 *
 *  @sa         OsalSpinlock_delete
 */
OsalSpinlock_Handle
OsalSpinlock_create (OsalSpinlock_Type type)
{
    OsalSpinlock_Object * lockObject = NULL;

    GT_1trace (curTrace, GT_ENTER, "OsalSpinlock_create", type);

    GT_assert (curTrace, (type < OsalSpinlock_Type_EndValue));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (type >= OsalSpinlock_Type_EndValue) {
        /*! @retval NULL Invalid type provided */
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalSpinlock_create",
                             OSALSPINLOCK_E_INVALIDARG,
                             "Invalid type provided");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        lockObject = Memory_alloc (NULL, sizeof (OsalSpinlock_Object), 0, NULL);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (lockObject == NULL) {
            /*! @retval NULL Failed to allocate memory for spinlock object. */
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "OsalSpinlock_create",
                              OSALSPINLOCK_E_MEMORY,
                              "Failed to allocate memory for spinlock object.");
        }
        else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
            pthread_mutex_init(&(lockObject->lock), NULL);
#if !defined(IPC_BUILD_OPTIMIZE)
        }
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "OsalSpinlock_create", lockObject);

    /*! @retval Spinlock-handle Operation successfully completed. */
    return (OsalSpinlock_Handle) lockObject;
}

/*!
 *  @brief      Delete the Spinlock Object.
 *
 *  @param      lockHandle Spinlock object handle which needs to be deleted.
 *
 *  @sa         OsalSpinlock_create
 */
Int
OsalSpinlock_delete (OsalSpinlock_Handle * lockHandle)
{
    Int                   status     = OSALSPINLOCK_SUCCESS;
    OsalSpinlock_Object * lockObject = NULL;

    GT_1trace (curTrace, GT_ENTER, "OsalSpinlock_delete", lockHandle);

    GT_assert (curTrace, (lockHandle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (lockHandle == NULL) {
        /*! @retval OSALSPINLOCK_E_INVALIDARG NULL provided for argument
                                              lockHandle.*/
        status = OSALSPINLOCK_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalSpinlock_delete",
                             status,
                             "NULL provided for argument lockHandle");
    }
    else if (*lockHandle == NULL) {
        /*! @retval OSALSPINLOCK_E_HANDLE NULL spinlock handle provided. */
        status = OSALSPINLOCK_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalSpinlock_delete",
                             status,
                             "NULL spinlock handle provided.");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        lockObject = (OsalSpinlock_Object*) (*lockHandle);
                pthread_mutex_destroy(&lockObject->lock);
        Memory_free (NULL, lockObject, sizeof (OsalSpinlock_Object));
        *lockHandle = NULL;
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "OsalSpinlock_delete", status);

    /*! @retval OSALSPINLOCK_SUCCESS Operation successfully completed. */
    return status;
}


/*!
 *  @brief      Begin protection of code through spin lock with all ISRs
 *              disabled. Calling this API protects critical regions of code
 *              from preemption by tasks, DPCs and all interrupts.
 *
 *  @param      lockHandle   Spinlock object handle to be acquired.
 *
 *  @sa         OsalSpinlock_leave
 */
UInt32
OsalSpinlock_enter (OsalSpinlock_Handle lockHandle)
{
    UInt32 flags = 0;

    OsalSpinlock_Object * lockObject = (OsalSpinlock_Object*) lockHandle;

    GT_1trace (curTrace, GT_ENTER, "OsalSpinlock_enter", lockHandle);

    GT_assert (curTrace, (lockHandle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (lockHandle == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalSpinlock_enter",
                             OSALSPINLOCK_E_HANDLE,
                             "NULL spinlock handle provided.");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        pthread_mutex_lock (&(lockObject->lock));
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "OsalSpinlock_enter", flags);

    /*! @retval Flags Flags to be provided to corresponding leave call. */
    return flags;
}


/*!
 *  @brief      End protection of code through spin lock with all ISRs disabled.
 *
 *  @param      lockHandle   Spinlock object handle to be released.
 *  @param      key          Key received from the corresponding enter call.
 *
 *  @sa         OsalSpinlock_enter
 */
Void
OsalSpinlock_leave (OsalSpinlock_Handle lockHandle, UInt32 key)
{
    OsalSpinlock_Object * lockObject = (OsalSpinlock_Object*) lockHandle;

    GT_2trace (curTrace, GT_ENTER, "OsalSpinlock_leave", lockHandle, key);

    GT_assert (curTrace, (lockHandle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (lockHandle == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalSpinlock_enter",
                             OSALSPINLOCK_E_HANDLE,
                             "NULL spinlock handle provided.");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        pthread_mutex_unlock (&(lockObject->lock));
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "OsalSpinlock_leave");
}


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
