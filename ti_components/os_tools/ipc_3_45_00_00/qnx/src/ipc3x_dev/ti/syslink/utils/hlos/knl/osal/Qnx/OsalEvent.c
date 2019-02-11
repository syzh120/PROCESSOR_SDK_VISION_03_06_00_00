/*
 *  @file  OsalEvent.c
 *
 *  @brief  Qnx Events interface definitions.
 *
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

/* OSAL and kernel utils */
#include <OsalEvent.h>
#include <OsalSpinlock.h>
#include <ti/syslink/utils/Trace.h>
#include <ti/syslink/utils/Memory.h>

#include <pthread.h>
#include <time.h>
#include <inttypes.h>
#include <errno.h>

#if defined (__cplusplus)
extern "C" {
#endif


/*!
 *  @brief  This object is used for various event related API.
 */
typedef struct OsalEvent_Object_tag {
    UInt32                   value;      /*!< Current value of the event.*/
        pthread_mutex_t lock;
        pthread_cond_t  cond;
} OsalEvent_Object;

/*!
 *  @brief      Creates and initializes an event object for thread
 *              synchronization. The event is initialized to a
 *              non-signaled state..
 *
 *  @param      Un-allocated event object.
 *  @sa         EventClose
 */
OsalEvent_Handle
OsalEvent_create (Void)
{
    Int status = OSALEVENT_SUCCESS ;
    OsalEvent_Object* event = NULL;
    pthread_condattr_t attr;

    GT_0trace (curTrace, GT_ENTER, "OsalEvent_create");

    event = Memory_alloc (NULL, sizeof (OsalEvent_Object), 0, NULL);

#if !defined(IPC_BUILD_OPTIMIZE)
    if (event == NULL) {
        status = OSALEVENT_E_MEMORY;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalEvent_create",
                             OSALEVENT_E_MEMORY,
                             "Memory allocation failed");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        event->value = 0;
        pthread_mutex_init(&event->lock, NULL);
        pthread_condattr_init(&attr);
        pthread_condattr_setclock(&attr, CLOCK_MONOTONIC);
        pthread_cond_init (&(event->cond), &attr);
        pthread_condattr_destroy(&attr);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
    GT_1trace (curTrace, GT_LEAVE, "OsalEvent_create", status);

    /*!@status The object created */
    return (OsalEvent_Handle) event;
}

/*!
 *  @brief      Closes the handle corresponding to an event. It also frees the
 *              resources allocated, if any, during call to OpenEvent ()
 *
 *  @param      allocated event object handle.
 *  @sa         OsalEvent_delete
 */
Int OsalEvent_delete (OsalEvent_Handle handle)
{
    Int status = OSALEVENT_SUCCESS ;
    OsalEvent_Object* event = (OsalEvent_Object*) handle;

    GT_1trace (curTrace, GT_ENTER,"OsalEvent_close",event );
    GT_assert (curTrace, (NULL != event) );

    pthread_mutex_destroy(&event->lock);
    pthread_cond_destroy(&event->cond);

    GT_1trace (curTrace, GT_LEAVE,"Event_Close",status );

    /*!@status OSALEVENT_SUCCESS if call succeeded.*/
    /*!@status OSALEVENT_E_SPINLOCK when SpinLock operation fails.*/
    return status;
}

/*!
 *  @brief      Reset the synchronization object to non-signaled state.
 *
 *  @param      allocated event object handle.
 *  @sa         OsalEvent_set
 */
Int OsalEvent_reset (OsalEvent_Handle handle)
{
    Int status = OSALEVENT_SUCCESS ;
    OsalEvent_Object* event = (OsalEvent_Object*) handle;

    GT_1trace (curTrace, GT_ENTER,"OsalEvent_reset", event);

    GT_assert (curTrace, (NULL != event) );

    pthread_mutex_lock(&event->lock);
    event->value = 0u;
    pthread_mutex_unlock(&event->lock);

    GT_1trace (curTrace, GT_LEAVE,"Event_Reset", status );

    /*! @retval OSALEVENT_SUCCESS as value get resetted.*/
    return status;
}

/*!
 *  @brief      Set the state of synchronization object to signaled and
 *              unblock all threads waiting for it.
 *
 *  @param      allocated event object handle.
 *  @sa         OsalEvent_reset
 */
Int OsalEvent_set (OsalEvent_Handle handle)
{
    Int status = OSALEVENT_SUCCESS ;
    OsalEvent_Object* event = (OsalEvent_Object*) handle;

    GT_1trace (curTrace, GT_ENTER,"OsalEvent_set", event );

    GT_assert (curTrace, (NULL != event) );

    pthread_mutex_lock(&event->lock);
    event->value = 1u;
    pthread_cond_broadcast(&event->cond);
    pthread_mutex_unlock(&event->lock);

    GT_1trace (curTrace, GT_LEAVE,"OsalEvent_set", status );
    return status;
}

/*!
 *  @brief      Wait for an event to be signaled for some specified time.
 *              It is possible to wait infinitely, this calls Blocks and does
 *              not Spin.
 *
 *  @param      allocated event object handle.
 *
 *  @retval     Int as success if succedded otherwise failure
 */
Int OsalEvent_wait (OsalEvent_Handle handle, UInt32 timeout)
{
    Int status = OSALEVENT_SUCCESS ;

    OsalEvent_Object* event = (OsalEvent_Object*) handle;

    GT_2trace (curTrace, GT_ENTER,"OsalEvent_wait", event, timeout );

    GT_assert (curTrace, (NULL != event) );

    if (OSAL_WAIT_NONE == timeout)
    {
        pthread_mutex_lock(&event->lock) ;
        if (event->value == 0u) {
            /*! @retval OSALEVENT_SYNC_FAIL when value is found zero. */
            status = OSALEVENT_E_SYNCFAIL ;
            GT_setFailureReason(curTrace, GT_4CLASS,
                "OsalEvent_wait",OSALEVENT_E_SYNCFAIL,"Wrong combination");
        }
        pthread_mutex_unlock (&event->lock);
    }
    else {
        pthread_mutex_lock (&event->lock) ;
        if (!event->value) {
            if (timeout == OSAL_WAIT_FOREVER) {
                while (event->value == 0u) {
                    pthread_cond_wait(&event->cond, &event->lock);
                }
            }
            else {
                uint64_t nsecs;
                struct timespec abstime;
                int ret;
                clock_gettime(CLOCK_MONOTONIC, &abstime);
                nsecs = abstime.tv_sec * 1000000000ULL + abstime.tv_nsec;
                nsecs += timeout * 1000000ULL;
                nsec2timespec(&abstime, nsecs);
                while (event->value == 0u) {
                    ret = pthread_cond_timedwait(&event->cond,
                                                 &event->lock,
                                                 &abstime);
                    if (ret == ETIMEDOUT) {
                        status = OSALEVENT_E_TIMEOUT ;
                        GT_setFailureReason(curTrace, GT_4CLASS,
                                            "OsalEvent_wait",
                                            OSALEVENT_E_TIMEOUT,
                                            "Timeout occured");
                        break;
                    }
                }
            }
        }
        /* End the lock */
        pthread_mutex_unlock (&event->lock);
    }

    GT_1trace (curTrace, GT_LEAVE,"OsalEvent_wait",status);

    return status;
}


#if defined (__cplusplus)
}
#endif /* defined (_cplusplus)*/
