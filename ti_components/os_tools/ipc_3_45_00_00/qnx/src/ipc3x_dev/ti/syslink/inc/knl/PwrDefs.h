/**
 *  @file   PwrDefs.h
 *
 *  @brief      Definitions for the PwrMgr interface.
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


#ifndef PwrDefs_H_0x783c
#define PwrDefs_H_0x783c


/* Module level headers */
#include <ti/syslink/ProcMgr.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief  Enumerations of PwrMgr power states, in ranking order
 */
typedef enum {
    PwrMgr_PowerState_Hibernate = 0x00402001         /*!< Hibernation mode */
} PwrMgr_PowerState;

/*!
 *  @brief  Configuration parameters for attaching to the PwrMgr
 */
typedef struct PwrMgr_AttachParams_tag {
    ProcMgr_AttachParams * params;
    /*!< Common attach parameters for ProcMgr */
} PwrMgr_AttachParams ;

/* Forward declaration for PwrMgr */
typedef struct PwrMgr_Object_tag PwrMgr_Object;

/*!
 *  @brief  Defines PwrMgr object handle
 */
typedef PwrMgr_Object * PwrMgr_Handle;


/* =============================================================================
 *  Function pointer types
 * =============================================================================
 */
/*!
 *  @brief  Function pointer type for the function to attach to the PwrMgr.
 */
typedef Int (*PwrMgr_AttachFxn) (PwrMgr_Handle         handle,
                                 PwrMgr_AttachParams * params);

/*!
 *  @brief  Function pointer type for the function to detach from the PwrMgr.
 */
typedef Int (*PwrMgr_DetachFxn) (PwrMgr_Handle handle);

/*!
 *  @brief  Function pointer type for the function to turn on power for the
 *          Slave processor.
 */
typedef Int (*PwrMgr_OnFxn) (PwrMgr_Handle handle);

/*!
 *  @brief  Function pointer type for the function to turn off power for the
 *          Slave processor.
 */
typedef Int (*PwrMgr_OffFxn) (PwrMgr_Handle handle, Bool force);

/*!
 *  @brief  Function pointer type for the function to put the Slave processor
 *  into a specified sleep state.
 */
typedef Int (*PwrMgr_SleepFxn) (PwrMgr_Handle handle,
                                UInt16        sleepState,
                                UArg          sleepArgs,
                                UArg          wakeupConditions,
                                UInt32        timeout);

/*!
 *  @brief  Function pointer type for the function to wake the Slave processor
 *  from its sleep state.
 */
typedef Int (*PwrMgr_WakeFxn) (PwrMgr_Handle handle);

/*!
 *  @brief  Function pointer type for the function to resume the previous sleep
 *          state of the Slave processor.
 */
typedef Int (*PwrMgr_ResumeSleepFxn) (PwrMgr_Handle handle);

/*!
 *  @brief  Function pointer type for the function to get the activity state of
 *          the Slave processor.
 */
typedef PwrMgr_PowerState (*PwrMgr_GetStateFxn) (PwrMgr_Handle handle);

/*!
 *  @brief  Function pointer type for the function to set the performance level
 *          for the Slave processor, or the communication link to the Slave.
 */
typedef Int (*PwrMgr_SetPerformanceFxn) (PwrMgr_Handle handle,
                                         UInt32        type,
                                         UInt32        target,
                                         UInt32        performance,
                                         UInt32        timeout);

/*!
 *  @brief  Function pointer type for the function to get the performance level
 *          for the Slave processor, or the communication link to the Slave.
 */
typedef UInt32 (*PwrMgr_GetPerformanceFxn) (PwrMgr_Handle handle,
                                            UInt32        target);

/*!
 *  @brief  Function pointer type for the function to declare a need for a
 *          resource, e.g., a clock.
 */
typedef Int (*PwrMgr_SetDependencyFxn) (PwrMgr_Handle handle,
                                        UInt16        resourceId);

/*!
 *  @brief  Function pointer type for the function to release a
 *          previously-declared need for a resource, e.g., a clock.
 */
typedef Int (*PwrMgr_ReleaseDependencyFxn) (PwrMgr_Handle handle,
                                            UInt16        resourceId);

/*!
 *  @brief  Function pointer type for the function to register a callback
 *          function to be called upon the occurrence of a specific power event.
 */
typedef Int (*PwrMgr_RegisterNotifyFxn) (PwrMgr_Handle handle,
                                         UInt16        eventType,
                                         UArg          eventArgs,
                                         Ptr           callbackFxn,
                                         Ptr *         notifyHandle,
                                         UInt32        timeout);

/*!
 *  @brief  Function pointer type for the function to unregister a previously
 *          registered request for notification.
 */
typedef Int (*PwrMgr_UnregisterNotifyFxn) (PwrMgr_Handle handle,
                                           Ptr           notifyHandle);

/*!
 *  @brief  Function pointer type for the function to declare a constraint with
 *          the Power Manager.
 */
typedef Int (*PwrMgr_RegisterConstraintFxn) (PwrMgr_Handle handle,
                                             UInt16        type,
                                             UInt32        value,
                                             UArg          constraintArgs,
                                             Ptr *         constraintHandle);

/*!
 *  @brief  Function pointer type for the function to declare a constraint with
 *          the Power Manager.
 */
typedef Int (*PwrMgr_UnregisterConstraintFxn) (PwrMgr_Handle handle,
                                               Ptr           constraintHandle);


/* =============================================================================
 *  Configured Functions for Communicating with external Master Power Manager
 * =============================================================================
 */
/*!
 *  @brief  Function pointer type for the function to signal an external power
 *          event, from the Container, or the  Master Power Manager directly,
 *          into to the Ipc Power Manager.
 */
typedef Void (*PwrMgr_MasterNotifyReceiveFxn) (UInt16 eventType,
                                               UArg   eventArgs);

/*!
 *  @brief  Function pointer type for the configurable hook function that will
 *          be called by PwrMgr, to send a synchronous request to the Master
 *          Power Manager.
 */
typedef Void (*PwrMgr_MasterRequestSyncFxn) (UInt16   requestType,
                                             UArg     requestArgs,
                                             UInt32 * requestStatus,
                                             UArg   * responseArgs);

/*!
 *  @brief  Function pointer type for the configurable hook function that will
 *          be called by PwrMgr, to send an asynchronous request to the Master
 *          Power Manager.
 */
typedef Void (*PwrMgr_MasterRequestAsyncSendFxn) (UInt16 requestType,
                                                  UArg   requestArgs,
                                                  Ptr *  requestHandle);

/*!
 *  @brief  Function pointer type for the function to signal an acknowledgement
 *          from the Master Power Manager, in response to an asynchronous
 *          request from PwrMgr.
 */
typedef Void (*PwrMgr_masterRequestAsyncAckFxn) (Ptr      requestHandle,
                                                 UInt32 * requestStatus,
                                                 UArg   * responseArgs);


/* =============================================================================
 *  Function table interface
 * =============================================================================
 */
/*!
 *  @brief  Function table interface for PwrMgr.
 */
typedef struct PwrMgr_FxnTable_tag {
    PwrMgr_AttachFxn                attach;
    /*!< Function to attach to the PwrMgr instance */
    PwrMgr_DetachFxn                detach;
    /*!< Function to detach from the PwrMgr instance */
    PwrMgr_OnFxn                    on;
    /*!< Function for power on for the PwrMgr instance */
    PwrMgr_OffFxn                   off;
    /*!< Function for power off for the PwrMgr instance */
    PwrMgr_SleepFxn                 sleep;
    /*!< Function for sleep for the PwrMgr instance */
    PwrMgr_WakeFxn                  wake;
    /*!< Function for wake for the PwrMgr instance */
    PwrMgr_ResumeSleepFxn           resumeSleep;
    /*!< Function for resume sleep for the PwrMgr instance */
    PwrMgr_GetStateFxn              getState;
    /*!< Function for GetState for the PwrMgr instance */
    PwrMgr_SetPerformanceFxn        setPerformance;
    /*!< Function for SetPerformance for the PwrMgr instance */
    PwrMgr_GetPerformanceFxn        getPerformance;
    /*!< Function for GetPerformance for the PwrMgr instance */
    PwrMgr_SetDependencyFxn         setDependency;
    /*!< Function for SetDependency for the PwrMgr instance */
    PwrMgr_ReleaseDependencyFxn     releaseDependency;
    /*!< Function for ReleaseDependency for the PwrMgr instance */
    PwrMgr_RegisterNotifyFxn        registerNotify;
    /*!< Function for RegisterNotify for the PwrMgr instance */
    PwrMgr_UnregisterNotifyFxn      unregisterNotify;
    /*!< Function for UnregisterNotify for the PwrMgr instance */
    PwrMgr_RegisterConstraintFxn    registerConstraint;
    /*!< Function for RegisterConstraint for the PwrMgr instance */
    PwrMgr_UnregisterConstraintFxn  unregisterConstraint;
    /*!< Function for UnregisterConstraint for the PwrMgr instance */
} PwrMgr_FxnTable;


/* =============================================================================
 * PwrMgr structure
 * =============================================================================
 */
/*
 *  Generic PwrMgr object. This object defines the handle type for all
 *  PwrMgr operations.
 */
struct PwrMgr_Object_tag {
    PwrMgr_FxnTable       pwrFxnTable;
    /*!< Interface function table to plug into the generic PwrMgr. */
    Ptr                   object;
    /*!< Pointer to PwrMgr-specific object. */
    UInt16                procId;
    /*!< Processor ID addressed by this PwrMgr instance. */
    ProcMgr_BootMode      bootMode;
    /*!< Boot mode for the slave processor. */
};


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* PwrDefs_H_0x783c */
