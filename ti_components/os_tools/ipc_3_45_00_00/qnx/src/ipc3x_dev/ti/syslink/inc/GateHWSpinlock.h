/*
 * Copyright (c) 2008-2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  ======== GateHWSpinlock.h ========
 */

#ifndef GATEHWSPINLOCK_H_0xF416
#define GATEHWSPINLOCK_H_0xF416

/* Utilities & Osal headers */
#include <ti/syslink/Std.h>

#include <ti/ipc/GateMP.h>

#if defined (__cplusplus)
extern "C" {
#endif

/*!
 *  @def    GateHWSpinlock_MODULEID
 *  @brief  Unique module ID.
 */
#define GateHWSpinlock_MODULEID               (0xc43d)

/* =============================================================================
 * Module Success and Failure codes
 * =============================================================================
 */
/*!
 *  @def    GateHWSpinlock_E_INVALIDARG
 *  @brief  Argument passed to a function is invalid.
 */
#define GateHWSpinlock_E_INVALIDARG       -1

/*!
 *  @def    GateHWSpinlock_E_MEMORY
 *  @brief  Memory allocation failed.
 */
#define GateHWSpinlock_E_MEMORY           -2

/*!
 *  @def    GateHWSpinlock_E_BUSY
 *  @brief  the name is already registered or not.
 */
#define GateHWSpinlock_E_BUSY             -3

/*!
 *  @def    GateHWSpinlock_E_FAIL
 *  @brief  Generic failure.
 */
#define GateHWSpinlock_E_FAIL             -4

/*!
 *  @def    GateHWSpinlock_E_NOTFOUND
 *  @brief  name not found in the nameserver.
 */
#define GateHWSpinlock_E_NOTFOUND         -5

/*!
 *  @def    GateHWSpinlock_E_INVALIDSTATE
 *  @brief  Module is not initialized.
 */
#define GateHWSpinlock_E_INVALIDSTATE     -6

/*!
 *  @def    GateHWSpinlock_E_NOTONWER
 *  @brief  Instance is not created on this processor.
 */
#define GateHWSpinlock_E_NOTONWER         -7

/*!
 *  @def    GateHWSpinlock_E_REMOTEACTIVE
 *  @brief  Remote opener of the instance has not closed the instance.
 */
#define GateHWSpinlock_E_REMOTEACTIVE     -8

/*!
 *  @def    GateHWSpinlock_E_INUSE
 *  @brief  Indicates that the instance is in use..
 */
#define GateHWSpinlock_E_INUSE            -9

/*!
 *  @def    GateHWSpinlock_E_OSFAILURE
 *  @brief  Failure in OS call.
 */
#define GateHWSpinlock_E_OSFAILURE        -10

/*!
 *  @def    GateHWSpinlock_E_VERSION
 *  @brief  Version mismatch error.
 */
#define GateHWSpinlock_E_VERSION          -11

/*!
 *  @def    GateHWSpinlock_S_SUCCESS
 *  @brief  Operation successful.
 */
#define GateHWSpinlock_S_SUCCESS            0

/*!
 *  @def    GateHWSpinlock_S_ALREADYSETUP
 *  @brief  The GATEHWSPINLOCK module has already been setup in this process.
 */
#define GateHWSpinlock_S_ALREADYSETUP     1

/* =============================================================================
 * Macros
 * =============================================================================
 */
/*! @brief Forward declaration of structure defining object for the
 *                 GateHWSpinlock. */
typedef struct GateHWSpinlock_Object GateHWSpinlock_Object;

/*!
 *  @brief  Handle for the GateHWSpinlock.
 */
typedef struct GateHWSpinlock_Object * GateHWSpinlock_Handle;

/* Q_BLOCKING */
#define GateHWSem_Q_BLOCKING   (1)

/* Q_PREEMPTING */
#define GateHWSem_Q_PREEMPTING (2)


/* =============================================================================
 * Structures & Enums
 * =============================================================================
 */

/*!
 *  @brief  Structure defining config parameters for the GateHWSpinlock module.
 */
typedef struct GateHWSpinlock_Config {
    UInt32               baseAddr;
    /* Device-specific base address for HW Semaphore subsystem in HOST OS
     * address space */
    UInt32               size;
    /* Device-specific size for HW Semaphore subsystem */
    UInt32               offset;
    /* Device-specific offset for HW Semaphore registers */
    UInt                 numLocks;
    /* Device-specific number of semphores in the HW Semaphore subsystem */
} GateHWSpinlock_Config;

/*!
 *  @brief  Structure defining config parameters for the GateHWSpinlock
 *          instances.
 */
typedef struct GateHWSpinlock_Params {
    Bits32 resourceId;
    Bool   openFlag;
    UInt16 regionId;
    Ptr    sharedAddr;
} GateHWSpinlock_Params;


typedef enum GateHWSpinlock_LocalProtect {
        GateHWSpinlock_LocalProtect_NONE      = 0,
        GateHWSpinlock_LocalProtect_INTERRUPT = 1,
        GateHWSpinlock_LocalProtect_TASKLET   = 2,
        GateHWSpinlock_LocalProtect_THREAD    = 3,
        GateHWSpinlock_LocalProtect_PROCESS   = 4
} GateHWSpinlock_LocalProtect;

/* =============================================================================
 * APIs
 * =============================================================================
 */
/* Function to get the default configuration for the GateHWSpinlock module. */
Void
GateHWSpinlock_getConfig (GateHWSpinlock_Config * cfgParams);

/* Function to setup the GateHWSpinlock module. */
Int
GateHWSpinlock_setup (const GateHWSpinlock_Config * config);

/* Function to destroy the GateHWSpinlock module */
Int
GateHWSpinlock_destroy (Void);

/* Initialize parameter structure */
Void GateHWSpinlock_Params_init(GateHWSpinlock_Params *params);

/* Function to start GateHWSpinlock module */
Int32 GateHWSpinlock_start(Void);

/* Funciton to stop GateHWSpinlock module */
Int GateHWSpinlock_stop(Void);

/* Function to create an instance of GateHWSpinlock */
GateHWSpinlock_Handle
GateHWSpinlock_create (      GateHWSpinlock_LocalProtect localProtect,
                       const GateHWSpinlock_Params *     params);

/* Function to delete an instance of GateHWSpinlock */
Int
GateHWSpinlock_delete (GateHWSpinlock_Handle * handlePtr);

/* Function to delete all instances of GateHWSpinlock */
Int
GateHWSpinlock_deleteAll (Void);

/* Function to enter the GateHWSpinlock instance */
IArg
GateHWSpinlock_enter  (GateHWSpinlock_Handle handle);

/* Function to leave the GateHWSpinlock instance */
Int
GateHWSpinlock_leave  (GateHWSpinlock_Handle handle, IArg   key);

/*!
 *  @brief      Function to return the number of instances configured in the
 *              module.
 *
 *  @return     Number of instances configured.
 */
UInt32 GateHWSpinlock_getNumInstances (Void);

/*!
 *  @brief      Function to initialize the locks
 *              module.
 *
 */
Void GateHWSpinlock_locksinit(Void);

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */


#endif /* GATEHWSPINLOCK_H_0xF416 */
