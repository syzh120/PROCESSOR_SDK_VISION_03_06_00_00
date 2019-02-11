/**
 *  @file   OsalSemaphore.c
 *
 *  @brief      Semaphore interface implementation.
 *
 *              This abstracts the Semaphore interface in Kernel code and
 *              is implemented using the wait queues. It has interfaces
 *              for creating, destroying, waiting and triggering the Semaphores.
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


/* Standard headers */
#include <ti/syslink/Std.h>

/* OSAL and utils headers */
#include <OsalSemaphore.h>
#include <ti/syslink/utils/Trace.h>
#include <ti/syslink/utils/Memory.h>

#include <pthread.h>
#include <time.h>
#include <inttypes.h>
#include <errno.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief   Defines object to encapsulate the Semaphore.
 *           The definition is OS/platform specific.
 */
typedef struct OsalSemaphore_Object_tag {
    OsalSemaphore_Type  semType;
    /*!< Indicates the type of the semaphore (binary or counting). */
    /*!< List of waiting processes. */
    UInt32              value;
    /*!< Current status of semaphore (0,1) - binary and (0-n) counting. */
    pthread_mutex_t       lock;
    pthread_cond_t        cond;
    /*!< lock on which this Semaphore is based. */
} OsalSemaphore_Object;


/* =============================================================================
 * APIs
 * =============================================================================
 */
/*!
 *  @brief      Creates an instance of Mutex object.
 *
 *  @param      semType Type of semaphore. This parameter is a mask of semaphore
 *                      type and interruptability type.
 *
 *  @sa         OsalSemaphore_delete
 */
OsalSemaphore_Handle
OsalSemaphore_create (UInt32 semType)
{
    OsalSemaphore_Object * semObj = NULL;

    GT_1trace (curTrace, GT_ENTER, "OsalSemaphore_create", semType);

    /* Check for semaphore type (binary/counting) */
    GT_assert (curTrace,
               (    (OSALSEMAPHORE_TYPE_VALUE(semType))
                <   OsalSemaphore_Type_EndValue));
    /* Check for semaphore interruptability */
    GT_assert (curTrace,
               (    (OSALSEMAPHORE_INTTYPE_VALUE(semType))
                <   OsalSemaphore_IntType_EndValue));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (OSALSEMAPHORE_TYPE_VALUE(semType) >= OsalSemaphore_Type_EndValue) {
        /*! @retval NULL Invalid semaphore type (OsalSemaphore_Type) provided */
        GT_setFailureReason (curTrace,
                        GT_4CLASS,
                        "OsalSemaphore_create",
                        OSALSEMAPHORE_E_INVALIDARG,
                        "Invalid semaphore type (OsalSemaphore_Type) provided");
    }
    else if (   OSALSEMAPHORE_INTTYPE_VALUE(semType)
             >= OsalSemaphore_IntType_EndValue) {
        /*! @retval NULL Invalid semaphore interruptability type
                         (OsalSemaphore_IntType) provided */
        GT_setFailureReason (curTrace,
                        GT_4CLASS,
                        "OsalSemaphore_create",
                        OSALSEMAPHORE_E_INVALIDARG,
                        "Invalid semaphore interruptability type "
                        "(OsalSemaphore_IntType) provided");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        semObj = calloc (1, sizeof (OsalSemaphore_Object));
#if !defined(IPC_BUILD_OPTIMIZE)
        if (semObj == NULL) {
            /*! @retval NULL Failed to allocate memory for semaphore object. */
            GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalSemaphore_create",
                             OSALSEMAPHORE_E_MEMORY,
                             "Failed to allocate memory for semaphore object.");
        }
        else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
            pthread_condattr_t attr;
            semObj->semType = semType;
            semObj->value = 0u;
            pthread_mutex_init (&(semObj->lock), NULL);
            pthread_condattr_init(&attr);
            pthread_condattr_setclock(&attr, CLOCK_MONOTONIC);
            pthread_cond_init (&(semObj->cond), &attr);
            pthread_condattr_destroy(&attr);
#if !defined(IPC_BUILD_OPTIMIZE)
        }
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "OsalSemaphore_create", semObj);

    /*! @retval Semaphore-handle Operation successfully completed. */
    return (OsalSemaphore_Handle) semObj;
}


/*!
 *  @brief      Deletes an instance of Semaphore object.
 *
 *  @param      mutexHandle   Semaphore object handle which needs to be deleted.
 *
 *  @sa         OsalSemaphore_create
 */
Int
OsalSemaphore_delete (OsalSemaphore_Handle * semHandle)
{
    Int status = OSALSEMAPHORE_SUCCESS;
    OsalSemaphore_Object *  semObj;

    GT_1trace (curTrace, GT_ENTER, "OsalSemaphore_delete", semHandle);

    GT_assert (curTrace, (semHandle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (semHandle == NULL) {
        /*! @retval OSALSEMAPHORE_E_INVALIDARG NULL provided for argument
                                           semHandle.*/
        status = OSALSEMAPHORE_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalSemaphore_delete",
                             status,
                             "NULL provided for argument semHandle");
    }
    else if (*semHandle == NULL) {
        /*! @retval OSALSEMAPHORE_E_HANDLE NULL Semaphore handle provided. */
        status = OSALSEMAPHORE_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalSemaphore_delete",
                             status,
                             "NULL Semaphore handle provided.");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        semObj = (OsalSemaphore_Object *) *semHandle;
        pthread_mutex_destroy(&semObj->lock);
        pthread_cond_destroy(&semObj->cond);
        free (semObj);
        *semHandle = NULL;
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "OsalSemaphore_delete", status);

    /*! @retval OSALSEMAPHORE_SUCCESS Operation successfully completed. */
    return status;
}


/*!
 *  @brief      Wait on the Semaphore in the kernel thread context
 *
 *  @param      semHandle   Semaphore object handle
 *  @param      timeout     Timeout (in msec). Special values are provided for
 *                          no-wait and infinite-wait.
 *
 *  @sa         OsalSemaphore_post
 */
Int
OsalSemaphore_pend (OsalSemaphore_Handle semHandle, UInt32 timeout)
{
    Int                     status      = OSALSEMAPHORE_SUCCESS;
    OsalSemaphore_Object *  semObj      = (OsalSemaphore_Object *) semHandle;
    int                     osStatus    = 0;

    GT_2trace (curTrace, GT_ENTER, "OsalSemaphore_pend", semHandle, timeout);

    GT_assert (curTrace, (semHandle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (semHandle == NULL) {
        /*! @retval OSALSEMAPHORE_E_HANDLE NULL Semaphore handle provided. */
        status = OSALSEMAPHORE_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalSemaphore_pend",
                             status,
                             "NULL Semaphore handle provided.");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        /* Different handling for no-timeout case. */
        if (timeout == OSALSEMAPHORE_WAIT_NONE) {
            osStatus = pthread_mutex_lock(&(semObj->lock));
            GT_assert (curTrace, (osStatus == 0));
            if (semObj->value == 0u) {
                /*! @retval OSALSEMAPHORE_E_WAITNONE WAIT_NONE timeout value was
                            provided, but semaphore was not available. */
                status = OSALSEMAPHORE_E_WAITNONE ;
                GT_1trace (curTrace,
                           GT_3CLASS,
                           "OsalSemaphore_pend:    "
                           "WAIT_NONE timeout value was provided, but"
                           " semaphore was not available\n"
                           "    Handle [0x%x]",
                           semObj);
            }
            else {
                if (    OSALSEMAPHORE_TYPE_VALUE(semObj->semType)
                    ==  OsalSemaphore_Type_Binary) {
                    semObj->value = 0u;
                }
                else {
                    semObj->value--;
                }
            }
            pthread_mutex_unlock (&semObj->lock);
        }
        /* Finite and infinite timeout cases */
        else {
            /* Get timeout value in OS-recognizable format. */
            if (timeout == OSALSEMAPHORE_WAIT_FOREVER) {
                pthread_mutex_lock(&semObj->lock);
                while (semObj->value == 0u) {
                    pthread_cond_wait(&semObj->cond, &semObj->lock);
                }
              if (    OSALSEMAPHORE_TYPE_VALUE(semObj->semType)
                 ==  OsalSemaphore_Type_Binary) {
                    semObj->value = 0u;
                }
                else {
                    semObj->value--;
                }
                pthread_mutex_unlock(&semObj->lock);
            }
            else {
                uint64_t nsecs;
                struct timespec abstime;
                int ret;
                clock_gettime(CLOCK_MONOTONIC, &abstime);
                nsecs = abstime.tv_sec * 1000000000ULL + abstime.tv_nsec;
                nsecs += timeout * 1000000ULL;
                nsec2timespec(&abstime, nsecs);
                pthread_mutex_lock(&semObj->lock);
                while (semObj->value == 0u)    {
                    ret = pthread_cond_timedwait(&semObj->cond, &semObj->lock, &abstime);
                    if (ret == ETIMEDOUT) {
                        status = OSALSEMAPHORE_E_TIMEOUT ;
                        break;
                    }
                }
                if (status != OSALSEMAPHORE_E_TIMEOUT) {
                  if (    OSALSEMAPHORE_TYPE_VALUE(semObj->semType)
                     ==  OsalSemaphore_Type_Binary) {
                        semObj->value = 0u;
                    }
                    else {
                        semObj->value--;
                    }
                }
                else {
                    GT_1trace (curTrace,
                               GT_3CLASS,
                               "OsalSemaphore_pend:    "
                               "Timeout occurred on semaphore pend\n"
                               "    Handle [0x%x]",
                               semObj);
                }
                pthread_mutex_unlock(&semObj->lock);
            }
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "OsalSemaphore_pend", status);

    /*! @retval OSALSEMAPHORE_SUCCESS Operation successfully completed. */
    return status;
}

/*!
 *  @brief      Signals the semaphore and makes it available for other
 *              threads.
 *
 *  @param      semHandle Semaphore object handle
 *
 *  @sa         OsalSemaphore_pend
 */
Int
OsalSemaphore_post (OsalSemaphore_Handle semHandle)
{
    Int                     status      = OSALSEMAPHORE_SUCCESS;
    OsalSemaphore_Object *  semObj      = (OsalSemaphore_Object *) semHandle;
    int                     osStatus    = 0;

    GT_1trace (curTrace, GT_ENTER, "OsalSemaphore_post", semHandle);

    GT_assert (curTrace, (semHandle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (semHandle == NULL) {
        /*! @retval OSALSEMAPHORE_E_HANDLE NULL Semaphore handle provided. */
        status = OSALSEMAPHORE_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalSemaphore_post",
                             status,
                             "NULL Semaphore handle provided.");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        osStatus = pthread_mutex_lock (&(semObj->lock));
        GT_assert (curTrace, (osStatus == 0));
        semObj->value = 1u;
        osStatus = pthread_cond_signal (&(semObj->cond));
        pthread_mutex_unlock(&(semObj->lock));
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "OsalSemaphore_post", status);

    /*! @retval OSALSEMAPHORE_SUCCESS Operation successfully completed. */
    return status;
}


#if defined (__cplusplus)
}
#endif /* defined (_cplusplus)*/
