/*
 *  @file        OsalIsr.c
 *
 *  @brief      QNX ISR interface implementation.
 *
 *              This abstracts the ISR interface on kernel side code.
 *              Installs the handler for individual IRQs and handlers
 *              are invoked as the interrupts occur.
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
#include <OsalIsr.h>
#include <OsalThread.h>
#include <ti/syslink/utils/Trace.h>
#include <ti/syslink/utils/Memory.h>

/* QNX specific header files */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/neutrino.h>
#include <sys/syspage.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <inttypes.h>
#include <hw/inout.h>
#include <fcntl.h>
#include <sys/slog.h>
#include <sys/slogcodes.h>

#define ISR_EVENT_PULSE        (_PULSE_CODE_MINAVAIL + 1)

#if defined (__cplusplus)
extern "C" {
#endif


#define PRIORITY_REALTIME_LOW 29

/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief   Defines object to encapsulate the interrupt service routine.
 *           The definition is OS/platform specific.
 */
typedef struct OsalIsr_Object_tag {
    UInt32                      irq;
    /*!< The IRQ number handled by this ISR object. */
    OsalThread_Handle           bottomHalf;
    /*!< OsalThread_Object which is being invoked by the ISR handler */
    OsalIsr_CheckAndClearFxn    checkFunc;
    /*!< Argument for the CheckAndClear function */
    Ptr                         checkFuncArg;
    /*!< CheckAndClear function registered for this interrupt */
    Bool                        isSharedInt;
    /*!< Is the interrupt a shared interrupt? */
    OsalIsr_State               isrState;
    /*!< Current state of the ISR. */
    //OsalIsr_CallbackFxn            callbackFunc,
    //Ptr                            callbackArgs,
    Int32                          handle;
    Bool                         enabled;
    Int32                       chid;
    Int32                       coid;
    Int32                       tid;
    Int32                       index;
} OsalIsr_Object;

/* =============================================================================
 * Interrupt event handler declaration
 * =============================================================================
 */
void *ISR_event_handler (void *area);

/* =============================================================================
 * APIs
 * =============================================================================
 */
/*!
 *  @brief      Creates an ISR object.
 *
 *  @param      fxn     ISR handler function to be registered
 *  @param      fxnArgs Optional parameter associated with the ISR handler
 *  @param      params  Parameters with information about the interrupt to be
 *                      registered.
 *
 *  @sa         OsalIsr_delete, Memory_alloc
 */
OsalIsr_Handle
OsalIsr_create (OsalIsr_CallbackFxn fxn,
                Ptr                 fxnArgs,
                OsalIsr_Params *    params)
{
    OsalIsr_Object *        isrObj =  NULL;
    OsalThread_Params       threadParams;

    GT_3trace (curTrace, GT_ENTER, "OsalIsr_create", fxn, fxnArgs, params);

    GT_assert (curTrace, (fxn != NULL));
    /* fxnArgs are optional and may be passed as NULL. */
    GT_assert (curTrace, (params != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (fxn == NULL) {
        /*! @retval NULL provided for argument fxn */
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalIsr_create",
                             OSALISR_E_INVALIDARG,
                             "NULL provided for argument fxn");
    }
    else if (params == NULL) {
        /*! @retval NULL provided for argument params */
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalIsr_create",
                             OSALISR_E_INVALIDARG,
                             "NULL provided for argument params");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        isrObj = Memory_alloc (NULL, sizeof (OsalIsr_Object), 0, NULL);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (isrObj == NULL) {
            /*! @retval NULL Failed to allocate memory for ISR object. */
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "OsalIsr_create",
                                 OSALISR_E_MEMORY,
                                 "Failed to allocate memory for ISR object.");
        }
        else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
            /* Create the thread object used for the interrupt handler. */
            threadParams.priority     = OsalThread_Priority_High;
            threadParams.priorityType = OsalThread_PriorityType_Generic;
            threadParams.once         = FALSE;
            isrObj->bottomHalf = OsalThread_create ((OsalThread_CallbackFxn)
                                                    fxn,
                                                    fxnArgs,
                                                    &threadParams);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (isrObj->bottomHalf == NULL) {
                /*! @retval NULL Failed to create thread for ISR handler. */
                GT_setFailureReason (curTrace,
                                    GT_4CLASS,
                                    "OsalIsr_create",
                                    OSALISR_E_THREAD,
                                    "Failed to create thread for ISR handler.");
                Memory_free (NULL, isrObj, sizeof (OsalIsr_Object));
                isrObj = NULL;
            }
            else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
            /* Copy the creation parameters for further use */
            isrObj->irq             = params->intId;
            isrObj->isSharedInt  = params->sharedInt;
            isrObj->checkFunc     = params->checkAndClearFxn;
            isrObj->checkFuncArg = params->fxnArgs;
            //isrObj->callbackFunc = fxn;
            //isrObj->callbackArgs = fxnArgs;

            /* Initialize state to uninstalled. */
            isrObj->isrState = OsalIsr_State_Uninstalled;

#if !defined(IPC_BUILD_OPTIMIZE)
            }
        }
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "OsalIsr_create", isrObj);

    /*! @retval ISR-handle Operation successfully completed. */
    return (OsalIsr_Handle) isrObj;
}


/*!
 *  @brief      Delete the ISR object.
 *
 *  @param      isrHandle   ISR object handle which needs to be deleted.
 *
 *  @sa         OsalIsr_create, Memory_free
 */
Int
OsalIsr_delete (OsalIsr_Handle * isrHandle)
{
    Int                 status = OSALISR_SUCCESS;
    OsalIsr_Object *    isrObj = NULL;

    GT_1trace (curTrace, GT_ENTER, "OsalIsr_delete", isrHandle);

    GT_assert (curTrace, (isrHandle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (isrHandle == NULL) {
        /*! @retval OSALISR_E_INVALIDARG NULL provided for argument isrHandle.*/
        status = OSALISR_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalIsr_delete",
                             status,
                             "NULL provided for argument isrHandle");
    }
    else if (*isrHandle == NULL) {
        /*! @retval OSALISR_E_HANDLE NULL ISR handle provided. */
        status = OSALISR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalIsr_delete",
                             status,
                             "NULL ISR handle provided.");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        isrObj = (OsalIsr_Object*) (*isrHandle);
        /* Delete the thread used for the ISR handler */
        if (isrObj->bottomHalf != NULL) {
            OsalThread_delete (&(isrObj->bottomHalf));
        }

        /* Free the ISR object. */
        Memory_free (NULL, isrObj, sizeof (OsalIsr_Object));
        *isrHandle = NULL;
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "OsalIsr_delete", status);

    /*! @retval OSALISR_SUCCESS Operation successfully completed. */
    return status;
}


/*!
 *  @brief      Install an interrupt service routine.
 *
 *              This function calls the InterruptAttachEvent () function and installs
 *              the specified interrupt service routine in non-shared, non-fiq
 *              mode.
 *
 *  @param      isrHandle   ISR object handle to be installed
 *
 *  @sa         OsalIsr_uninstall
 */
Int
OsalIsr_install (OsalIsr_Handle isrHandle)
{
    Int                 status   = OSALISR_SUCCESS;
    OsalIsr_Object *    isrObj   = (OsalIsr_Object *) isrHandle;
    pthread_attr_t        pattr;
    struct sched_param    param;
    struct sigevent        event;
    char                threadName[20];

    GT_1trace (curTrace, GT_ENTER, "OsalIsr_install", isrHandle);

    GT_assert (curTrace, (isrHandle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (isrHandle == NULL) {
        /*! @retval OSALISR_E_HANDLE NULL ISR handle provided. */
        status = OSALISR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalIsr_install",
                             status,
                             "NULL ISR handle provided.");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

        if ((isrObj->chid = ChannelCreate(_NTO_CHF_DISCONNECT | _NTO_CHF_UNBLOCK)) == -1 ) {
            status = OSALISR_E_IRQINSTALL;
            ChannelDestroy(isrObj->chid);
        }
        else {
            if ((isrObj->coid = ConnectAttach(0, 0, isrObj->chid, _NTO_SIDE_CHANNEL, 0)) == -1) {
                status = OSALISR_E_IRQINSTALL;
                ConnectDetach(isrObj->coid);
                ChannelDestroy(isrObj->chid);
            }
            else {
                pthread_attr_init(&pattr);
                pthread_attr_setschedpolicy(&pattr, SCHED_RR);
                param.sched_priority = PRIORITY_REALTIME_LOW;
                pthread_attr_setschedparam(&pattr, &param);
                pthread_attr_setinheritsched(&pattr, PTHREAD_EXPLICIT_SCHED);

                if (pthread_create(&isrObj->tid, &pattr, (void *)ISR_event_handler, isrObj)) {
                    status = OSALISR_E_IRQINSTALL;
                    ConnectDetach(isrObj->coid);
                    ChannelDestroy(isrObj->chid);
                }
                else {
                    snprintf (threadName, sizeof(threadName), "OsalIsrThread_%d", isrObj->irq);
                    pthread_setname_np(isrObj->tid, threadName);
                }
                pthread_attr_destroy(&pattr);

                event.sigev_notify   = SIGEV_PULSE;
                event.sigev_coid     = isrObj->coid;
                event.sigev_code     = ISR_EVENT_PULSE;
                event.sigev_priority = PRIORITY_REALTIME_LOW + 1;

                if ((isrObj->handle =
                         InterruptAttachEvent(isrObj->irq, &event,
                                              _NTO_INTR_FLAGS_TRK_MSK)) == -1 ) {
                    status = OSALISR_E_IRQINSTALL;
                }
                isrObj->isrState = OsalIsr_State_Installed;
            }
        }

#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "OsalIsr_install", status);

    /*! @retval OSALISR_SUCCESS Operation successfully completed. */
    return status;
}


/*!
 *  @brief      Uninstalls an interrupt service routine.
 *
 *  @param      isrHandle   ISR object handle to be uninstalled.
 *
 *  @sa         OsalIsr_install
 */
Int
OsalIsr_uninstall (OsalIsr_Handle isrHandle)
{
    Int                 status  = OSALISR_SUCCESS;
    OsalIsr_Object *    isrObj  = (OsalIsr_Object *) isrHandle;

    GT_1trace (curTrace, GT_ENTER, "OsalIsr_uninstall", isrHandle);

    GT_assert (curTrace, (isrHandle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (isrHandle == NULL) {
        /*! @retval OSALISR_E_HANDLE NULL ISR handle provided. */
        status = OSALISR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalIsr_uninstall",
                             status,
                             "NULL ISR handle provided.");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        InterruptDetach (isrObj->handle);
        pthread_cancel(isrObj->tid);
        pthread_join(isrObj->tid, NULL);
        ConnectDetach(isrObj->coid);
        ChannelDestroy(isrObj->chid);

        isrObj->isrState = OsalIsr_State_Uninstalled;
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "OsalIsr_uninstall", status);

    /*! @retval OSALISR_SUCCESS Operation successfully completed. */
    return status;
}


/*!
 *  @brief      Disables the specified ISR.
 *
 *              This function calls disable_irq () to disable the ISR.
 *              disble_irq() function doesn't return any value so this
 *              function assumes it was successful.
 *
 *  @param      isrHandle   ISR object handle for the interrupt to be disabled.
 *
 *  @sa         OsalIsr_enableIsr
 */
Void
OsalIsr_disableIsr (OsalIsr_Handle isrHandle)
{
    OsalIsr_Object * isrObj = (OsalIsr_Object *) isrHandle;

    GT_1trace (curTrace, GT_ENTER, "OsalIsr_disableIsr", isrHandle);

    GT_assert (curTrace, (isrHandle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (isrHandle == NULL) {
        /* Void function, so status is not set. */
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalIsr_disableIsr",
                             OSALISR_E_HANDLE,
                             "NULL ISR handle provided.");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        if (isrObj->isSharedInt != TRUE) {
            /* Disable the IRQ handler */
            InterruptMask(isrObj->irq, isrObj->handle);
            isrObj->enabled = FALSE;
            isrObj->isrState = OsalIsr_State_Disabled;
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "OsalIsr_disableIsr");
}


/*!
 *  @brief      Enables the specified ISR.
 *
 *              This function calls enable_irq () to enable the ISR.
 *              enble_irq() function doesn't return any value so this function
 *              assumes it was successful.
 *
 *  @param      isrHandle   ISR object handle for the interrupt to be enabled.
 *
 *  @sa         OsalIsr_disableIsr
 */
Void
OsalIsr_enableIsr (OsalIsr_Handle isrHandle)
{
    OsalIsr_Object * isrObj = (OsalIsr_Object *) isrHandle;

    GT_1trace (curTrace, GT_ENTER, "OsalIsr_enableIsr", isrHandle);

    GT_assert (curTrace, (isrHandle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (isrHandle == NULL) {
        /* Void function, so status is not set. */
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalIsr_enableIsr",
                             OSALISR_E_HANDLE,
                             "NULL ISR handle provided.");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        if (isrObj->isSharedInt != TRUE) {
            InterruptUnmask(isrObj->irq, isrObj->handle);
            isrObj->enabled  = TRUE ;
            isrObj->isrState = OsalIsr_State_Installed;
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "OsalIsr_enableIsr");
}


/*!
 *  @brief      Disables all interrupts. Returns flags that must be passed to
 *              the corresponding restore API.
 *
 *  @sa         OsalIsr_restore
 */
UInt32 OsalIsr_disable (Void)
{
    unsigned long flags = 0;

    GT_0trace (curTrace, GT_ENTER, "OsalIsr_disable");

    InterruptDisable();

    GT_1trace (curTrace, GT_1CLASS, "   ISR disable flags [0x%x]", flags);
    GT_1trace (curTrace, GT_LEAVE, "OsalIsr_disable", flags);

    /*! @retval flags State of the interrupts before disable was called. */
    return flags;
}


/*!
 *  @brief      Restores all interrupts to their status before disable was
 *              called.
 *
 *  @param      flags   Flags indicating interrupts state before disable was
 *                      called. These are the flags returned from
 *                      OsalIsr_disable.
 *
 *  @sa         OsalIsr_disable
 */
Void OsalIsr_restore (UInt32 flags)
{
    GT_1trace (curTrace, GT_ENTER, "OsalIsr_restore", flags);

    InterruptEnable();

    GT_0trace (curTrace, GT_LEAVE, "OsalIsr_restore");
}


/*!
 *  @brief      Returns the state of an ISR.
 *
 *  @param      ISR object handle.
 *  @param      returned ISR object state.
 */
OsalIsr_State
OsalIsr_getState (OsalIsr_Handle isrHandle)
{
    OsalIsr_Object * isrObj   = (OsalIsr_Object *) isrHandle;
    OsalIsr_State    isrState = OsalIsr_State_EndValue;

    GT_1trace (curTrace, GT_ENTER, "OsalIsr_enableIsr", isrHandle);

    GT_assert (curTrace, (isrHandle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (isrHandle == NULL) {
        /*! @retval OsalIsr_State_EndValue NULL ISR handle provided. */
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "OsalIsr_getState",
                             OSALISR_E_HANDLE,
                             "NULL ISR handle provided.");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        isrState = isrObj->isrState;
        GT_1trace (curTrace, GT_1CLASS, "   ISR state [%d]", isrState);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "OsalIsr_getState", isrState);

    /*! @retval ISR-state State of the ISR */
    return isrState;
}


/*!
 *  @brief      Returns the state of whether the current context is ISR context.
 *
 *  @sa
 */
Bool
OsalIsr_inIsr (Void)
{
    Bool inIsr = FALSE;

    GT_0trace (curTrace, GT_ENTER, "OsalIsr_inIsr");

//    if (in_interrupt() != 0) {
//        inIsr = TRUE;
//    }

    GT_1trace (curTrace, GT_1CLASS, "   In ISR context [%d]", inIsr);
    GT_1trace (curTrace, GT_LEAVE, "OsalIsr_inIsr", inIsr);

    /*! @retval FALSE Not in ISR context. */
    return inIsr;
}


/*!
 *  @brief      ISR event handler
 *
 *  @param      ISR object handle.
 */
void *
ISR_event_handler (void *area) {
    struct _pulse        pulse;
    iov_t                iov;
    Bool                 isAsserted;
    int                    rcvid;
    OsalIsr_Object *    isrObj = (OsalIsr_Object * )area;

    SETIOV( &iov, &pulse, sizeof( pulse ) );

    while(1) {
        if ((rcvid = MsgReceivev( isrObj->chid, &iov, 1, NULL )) == -1 ) {
            if (errno == ESRCH){
                pthread_exit( NULL );
            }
            continue;
        }

        isAsserted = TRUE;

        if (isrObj->checkFunc) {
            isAsserted = (*isrObj->checkFunc) (isrObj->checkFuncArg);
        }

        if (TRUE == isAsserted) {
            OsalThread_activate (isrObj->bottomHalf);

             /* Call the bottom half routine */
            //(*isrObj->callbackFunc) (isrObj->callbackFuncArgs);
        }

        /* enble interrupt */
        InterruptUnmask(isrObj->irq, isrObj->handle);

    }
}


#if defined (__cplusplus)
}
#endif /* defined (_cplusplus)*/
