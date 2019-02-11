/*
 *  @file   VAYUIpuPwr.c
 *
 *  @brief      PwrMgr implementation for VAYUIPU.
 *
 *              This module is responsible for handling power requests for
 *              the ProcMgr.
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2013-2015, Texas Instruments Incorporated
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


#include <ti/syslink/Std.h>

/* OSAL & Utils headers */
#include <ti/syslink/utils/String.h>
#include <ti/syslink/utils/IGateProvider.h>
#include <ti/syslink/utils/GateMutex.h>
#include <ti/syslink/utils/Memory.h>
#include <ti/syslink/utils/Gate.h>


#include <string.h>

#include <ti/syslink/utils/Trace.h>

/* Module level headers */
#include <ti/ipc/MultiProc.h>
#include <ti/syslink/inc/_MultiProc.h>
#include <ti/syslink/inc/knl/PwrDefs.h>
#include <ti/syslink/inc/knl/PwrMgr.h>
#include <ti/syslink/inc/knl/VAYUIpuPwr.h>
#include <ti/syslink/inc/knl/_VAYUIpuPwr.h>
#include <ti/syslink/inc/knl/Qnx/VAYUIpuMmu.h>
#include <ti/syslink/inc/knl/VAYUIpuPhyShmem.h>

#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief  VAYUIPU module and mmr addresses (physical)
 */


#define MAX_WAIT_COUNT              0x50000

#define REG(x)              *((volatile UInt32 *) (x))
#define MEM(x)              *((volatile UInt32 *) (x))

/* Macro to make a correct module magic number with refCount */
#define VAYUIPUPWR_MAKE_MAGICSTAMP(x) \
                            ((VAYUIPUPWR_MODULEID << 12u) | (x))

/*!
 *  @brief  VAYUIPUPWR Module state object
 */
typedef struct VAYUIPUPWR_ModuleObject_tag {
    UInt32                  refCount;
    /* Module Reference count */
    UInt32                  pwrstateRefCount;
    /* Reference count */
    UInt32                 configSize;
    /*!< Size of configuration structure */
    VAYUIPUPWR_Config      cfg;
    /*!< VAYUIPUPWR configuration structure */
    VAYUIPUPWR_Config      defCfg;
    /*!< Default module configuration */
    Bool                   isSetup;
    /*!< Indicates whether the VAYUIPUPWR module is setup. */
    VAYUIPUPWR_Handle      pwrHandles [MultiProc_MAXPROCESSORS];
    /*!< PwrMgr handle array. */
    IGateProvider_Handle   gateHandle;
    /*!< Handle of gate to be used for local thread safety */
    Ptr                    ipuClkHandle;
    /*!< clock handle used to call kernel APIs */
    Ptr                    ipuSpinlockHandle;
    /*!< dsp Spinlock handle */
    Ptr                    ipuMailboxHandle;
    /*!< dsp Mailbox handle */
} VAYUIPUPWR_ModuleObject;

/* =============================================================================
 *  Globals
 * =============================================================================
 */
/*!
 *  @var    VAYUIPUPWR_state
 *
 *  @brief  VAYUIPUPWR state object variable
 */
#if !defined(IPC_BUILD_DEBUG)
static
#endif /* if !defined(IPC_BUILD_DEBUG) */
VAYUIPUPWR_ModuleObject VAYUIPUPWR_state =
{
    .isSetup = FALSE,
    .configSize = sizeof (VAYUIPUPWR_Config),
    .refCount   = 0,
    .pwrstateRefCount = 0,
    .defCfg.reserved = 0,
    .gateHandle = NULL,
};

/* =============================================================================
 * APIs directly called by applications
 * =============================================================================
 */
/*!
 *  @brief      Function to get the default configuration for the VAYUIPUPWR
 *              module.
 *
 *              This function can be called by the application to get their
 *              configuration parameter to VAYUIPUPWR_setup filled in by the
 *              VAYUIPUPWR module with the default parameters. If the user does
 *              not wish to make any change in the default parameters, this API
 *              is not required to be called.
 *
 *  @param      cfg        Pointer to the VAYUIPUPWR module configuration
 *                         structure in which the default config is to be
 *                         returned.
 *
 *  @sa         VAYUIPUPWR_setup
 */
Void
VAYUIPUPWR_getConfig (VAYUIPUPWR_Config * cfg)
{
    GT_1trace (curTrace, GT_ENTER, "VAYUIPUPWR_getConfig", cfg);

    GT_assert (curTrace, (cfg != NULL));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (cfg == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_getConfig",
                             PWRMGR_E_INVALIDARG,
                             "Argument of type (VAYUIPUPWR_Config *) passed "
                             "is null!");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

        if (VAYUIPUPWR_state.refCount == 0) {
            memcpy (cfg,
                         &VAYUIPUPWR_state.defCfg,
                         sizeof (VAYUIPUPWR_Config));
        }
        else {
            memcpy (cfg,
                         &VAYUIPUPWR_state.cfg,
                         sizeof (VAYUIPUPWR_Config));
        }
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    GT_0trace (curTrace, GT_LEAVE, "VAYUIPUPWR_getConfig");
}

/*!
 *  @brief      Function to setup the VAYUIPUPWR module.
 *
 *              This function sets up the VAYUIPUPWR module. This function must
 *              be called before any other instance-level APIs can be invoked.
 *              Module-level configuration needs to be provided to this
 *              function. If the user wishes to change some specific config
 *              parameters, then VAYUIPUPWR_getConfig can be called to get the
 *              configuration filled with the default values. After this, only
 *              the required configuration values can be changed. If the user
 *              does not wish to make any change in the default parameters, the
 *              application can simply call VAYUIPUPWR_setup with NULL
 *              parameters. The default parameters would get automatically used.
 *
 *  @param      cfg   Optional VAYUIPUPWR module configuration. If provided as
 *                    NULL, default configuration is used.
 *
 *  @sa         VAYUIPUPWR_destroy
 *              GateMutex_create
 */
Int
VAYUIPUPWR_setup (VAYUIPUPWR_Config * cfg)
{
    Int                      status = PWRMGR_SUCCESS;
    VAYUIPUPWR_Config   tmpCfg;
    IArg                     key;
    Error_Block              eb;

    eb = 0;

    GT_1trace (curTrace, GT_ENTER, "VAYUIPUPWR_setup", cfg);
    if (cfg == NULL) {
        VAYUIPUPWR_getConfig (&tmpCfg);
        cfg = &tmpCfg;
    }

    /* This sets the refCount variable is not initialized, upper 16 bits is
     * written with module Id to ensure correctness of refCount variable.
     */
    key = Gate_enterSystem();
    VAYUIPUPWR_state.refCount++;
    if (VAYUIPUPWR_state.refCount > 1) {
        status = VAYUIPUPWR_S_ALREADYSETUP;
        Gate_leaveSystem(key);
    }
    else {
        Gate_leaveSystem(key);

        /* Create a default gate handle for local module protection. */
        VAYUIPUPWR_state.gateHandle = (IGateProvider_Handle)
                                GateMutex_create ((GateMutex_Params*)NULL, &eb);
        if (VAYUIPUPWR_state.gateHandle == NULL) {
            key = Gate_enterSystem();
            VAYUIPUPWR_state.refCount = 0;
            Gate_leaveSystem(key);
            /*! @retval PWRMGR_E_FAIL Failed to create GateMutex! */
            status = PWRMGR_E_FAIL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUIPUPWR_setup",
                                 status,
                                 "Failed to create GateMutex!");
        }
        else {
            /* Copy the user provided values into the state object. */
            memcpy (&VAYUIPUPWR_state.cfg,
                         cfg,
                         sizeof (VAYUIPUPWR_Config));

            /* Initialize the name to handles mapping array. */
            memset (&VAYUIPUPWR_state.pwrHandles,
                        0,
                        (sizeof (VAYUIPUPWR_Handle) * MultiProc_MAXPROCESSORS));
            VAYUIPUPWR_state.isSetup = TRUE;
        }
    }

    GT_1trace (curTrace, GT_LEAVE, "VAYUIPUPWR_setup", status);
    /*! @retval PWRMGR_SUCCESS Operation successful */
    return (status);
}

/*!
 *  @brief      Function to destroy the VAYUIPUPWR module.
 *
 *              Once this function is called, other VAYUIPUPWR module APIs, except
 *              for the VAYUIPUPWR_getConfig API cannot be called anymore.
 *
 *  @sa         VAYUIPUPWR_setup
 *              GateMutex_delete
 */
Int
VAYUIPUPWR_destroy (Void)
{
    Int    status = PWRMGR_SUCCESS;
    UInt16 i;
    IArg key;

    GT_0trace (curTrace, GT_ENTER, "VAYUIPUPWR_destroy");

    GT_assert (curTrace, (VAYUIPUPWR_state.refCount != 0));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (VAYUIPUPWR_state.refCount == 0) {
        status = VAYUIPUPWR_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_destroy",
                             status,
                             "Module was not initialized!");
    }
    else {
#endif /* !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        key = Gate_enterSystem();
        VAYUIPUPWR_state.refCount--;
        Gate_leaveSystem(key);

        if (VAYUIPUPWR_state.refCount == 0) {
            /* Temporarily increment refCount here. */
            key = Gate_enterSystem();
            VAYUIPUPWR_state.refCount = 1;
            Gate_leaveSystem(key);

            /* Check if any VAYUIPUPWR instances have not been deleted so far. If not,
             * delete them.
             */
            for (i = 0 ; i < MultiProc_MAXPROCESSORS ; i++) {
                GT_assert (curTrace, (VAYUIPUPWR_state.pwrHandles [i] == NULL));
                if (VAYUIPUPWR_state.pwrHandles [i] != NULL) {
                    VAYUIPUPWR_delete (&(VAYUIPUPWR_state.pwrHandles [i]));
                }
            }
            /* restore refCount here. */
            key = Gate_enterSystem();
            VAYUIPUPWR_state.refCount = 0;
            Gate_leaveSystem(key);

            if (VAYUIPUPWR_state.gateHandle != NULL) {
                GateMutex_delete ((GateMutex_Handle *)
                                        &(VAYUIPUPWR_state.gateHandle));
            }
            VAYUIPUPWR_state.isSetup = FALSE;
        }
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
    GT_1trace (curTrace, GT_LEAVE, "VAYUIPUPWR_destroy", status);

    /*! @retval PWRMGR_SUCCESS Operation successful */
    return (status);
}

/*!
 *  @brief      Function to initialize the parameters for this PwrMgr instance.
 *
 *  @param      params  Configuration parameters.
 *
 *  @sa         VAYUIPUPWR_create
 */
Void
VAYUIPUPWR_Params_init (VAYUIPUPWR_Params * params)
{
    GT_1trace (curTrace, GT_ENTER, "VAYUIPUPWR_Params_init", params);

    GT_assert (curTrace, (params != NULL));
    GT_assert (curTrace, (VAYUIPUPWR_state.refCount != 0));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (VAYUIPUPWR_state.refCount == 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_Params_initv",
                             VAYUIPUPWR_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if (params == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_Params_init",
                             PWRMGR_E_INVALIDARG,
                             "Argument of type (VAYUIPUPWR_Params *) "
                             "passed is null!");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        params->reserved = 0;
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    GT_0trace (curTrace, GT_LEAVE, "VAYUIPUPWR_Params_init");
}

/*!
 *  @brief      Function to create an instance of this PwrMgr.
 *
 *  @param      procId  Processor ID addressed by this PwrMgr instance.
 *  @param      params  Configuration parameters.
 *
 *  @sa         VAYUIPUPWR_delete
 */
VAYUIPUPWR_Handle
VAYUIPUPWR_create (      UInt16               procId,
                    const VAYUIPUPWR_Params * params)
{
    Int                  status = PWRMGR_SUCCESS;
    PwrMgr_Object *      handle = NULL;
    IArg                 key;

    GT_2trace (curTrace, GT_ENTER, "VAYUIPUPWR_create", procId, params);

    GT_assert (curTrace, IS_VALID_PROCID (procId));
    GT_assert (curTrace, (params != NULL));
    GT_assert (curTrace, (VAYUIPUPWR_state.refCount != 0));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (VAYUIPUPWR_state.refCount == 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_create",
                             VAYUIPUPWR_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if (!IS_VALID_PROCID (procId)) {
        /* Not setting status here since this function does not return status.*/
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_create",
                             PWRMGR_E_INVALIDARG,
                             "Invalid procId specified");
    }
    else if (params == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_create",
                             PWRMGR_E_INVALIDARG,
                             "params passed is null!");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        /* Enter critical section protection. */
        key = IGateProvider_enter (VAYUIPUPWR_state.gateHandle);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
        /* Check if the PwrMgr already exists for specified procId. */
        if (VAYUIPUPWR_state.pwrHandles [procId] != NULL) {
            status = PWRMGR_E_ALREADYEXIST;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUIPUPWR_create",
                                 status,
                                 "PwrMgr already exists for specified procId!");
        }
        else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
            /* Allocate memory for the handle */
            handle = (PwrMgr_Object *) Memory_calloc (NULL,
                                                      sizeof (PwrMgr_Object),
                                                      0,
                                                      NULL);
            if (handle == NULL) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "VAYUIPUPWR_create",
                                     PWRMGR_E_MEMORY,
                                     "Memory allocation failed for handle!");
            }
            else {
                /* Populate the handle fields */
                handle->pwrFxnTable.attach = &VAYUIPUPWR_attach;
                handle->pwrFxnTable.detach = &VAYUIPUPWR_detach;
                handle->pwrFxnTable.on     = &VAYUIPUPWR_on;
                handle->pwrFxnTable.off    = &VAYUIPUPWR_off;
                /* TBD: Other functions */

                /* Allocate memory for the VAYUIPUPWR handle */
                handle->object = Memory_calloc (NULL,
                                                sizeof (VAYUIPUPWR_Object),
                                                0,
                                                NULL);
                if (handle == NULL) {
                    status = PWRMGR_E_MEMORY;
                    GT_setFailureReason (curTrace,
                                        GT_4CLASS,
                                        "VAYUIPUPWR_create",
                                        status,
                                        "Memory allocation failed for handle!");
                }
                else {
                    handle->procId = procId;
                    VAYUIPUPWR_state.pwrHandles [procId] =
                                                (VAYUIPUPWR_Handle) handle;
                }
            }
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
        }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        /* Leave critical section protection. */
        IGateProvider_leave (VAYUIPUPWR_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    if (status < 0) {
        if (handle !=  NULL) {
            if (handle->object != NULL) {
                Memory_free (NULL, handle->object, sizeof (VAYUIPUPWR_Object));
            }
            Memory_free (NULL, handle, sizeof (PwrMgr_Object));
        }
        /*! @retval NULL Function failed */
        handle = NULL;
    }

    GT_1trace (curTrace, GT_LEAVE, "VAYUIPUPWR_create", handle);

    /*! @retval Valid-Handle Operation successful */
    return (VAYUIPUPWR_Handle) handle;
}

/*!
 *  @brief      Function to delete an instance of this PwrMgr.
 *
 *              The user provided pointer to the handle is reset after
 *              successful completion of this function.
 *
 *  @param      handlePtr  Pointer to Handle to the PwrMgr instance
 *
 *  @sa         VAYUIPUPWR_create
 */
Int
VAYUIPUPWR_delete (VAYUIPUPWR_Handle * handlePtr)
{
    Int                  status = PWRMGR_SUCCESS;
    VAYUIPUPWR_Object * object = NULL;
    PwrMgr_Object *      handle;
    IArg                 key;

    GT_1trace (curTrace, GT_ENTER, "VAYUIPUPWR_delete", handlePtr);

    GT_assert (curTrace, (handlePtr != NULL));
    GT_assert (curTrace, ((handlePtr != NULL) && (*handlePtr != NULL)));

    GT_assert (curTrace, (VAYUIPUPWR_state.refCount != 0));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (VAYUIPUPWR_state.refCount == 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_delete",
                             VAYUIPUPWR_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if (handlePtr == NULL) {
        /*! @retval PWRMGR_E_INVALIDARG Invalid NULL handlePtr specified*/
        status = PWRMGR_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_delete",
                             status,
                             "Invalid NULL handlePtr specified");
    }
    else if (*handlePtr == NULL) {
        /*! @retval PWRMGR_E_HANDLE Invalid NULL *handlePtr specified */
        status = PWRMGR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_delete",
                             status,
                             "Invalid NULL *handlePtr specified");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        handle = (PwrMgr_Object *) (*handlePtr);
        /* Enter critical section protection. */
        key = IGateProvider_enter (VAYUIPUPWR_state.gateHandle);

        /* Reset handle in PwrMgr handle array. */
        GT_assert (curTrace, IS_VALID_PROCID (handle->procId));
        VAYUIPUPWR_state.pwrHandles [handle->procId] = NULL;

        object = (VAYUIPUPWR_Object *) handle->object;
        /* Free memory used for the VAYUIPUPWR object. */
        if (handle->object != NULL) {
            /* Free memory used for the clock handle */
            Memory_free (NULL,
                         object,
                         sizeof (VAYUIPUPWR_Object));
            handle->object = NULL;
        }

        /* Free memory used for the PwrMgr object. */
        Memory_free (NULL, handle, sizeof (PwrMgr_Object));
        *handlePtr = NULL;

        /* Leave critical section protection. */
        IGateProvider_leave (VAYUIPUPWR_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    GT_1trace (curTrace, GT_LEAVE, "VAYUIPUPWR_delete", status);

    /*! @retval PWRMGR_SUCCESS Operation successful */
    return (status);
}

/*!
 *  @brief      Function to open a handle to an instance of this PwrMgr. This
 *              function is called when access to the PwrMgr is required from
 *              a different process.
 *
 *  @param      handlePtr   Handle to the PwrMgr instance
 *  @param      procId      Processor ID addressed by this PwrMgr instance.
 *
 *  @sa         VAYUIPUPWR_close
 */
Int
VAYUIPUPWR_open (VAYUIPUPWR_Handle * handlePtr, UInt16 procId)
{
    Int status = PWRMGR_SUCCESS;

    GT_2trace (curTrace, GT_ENTER, "VAYUIPUPWR_open", handlePtr, procId);

    GT_assert (curTrace, (handlePtr != NULL));
    GT_assert (curTrace, IS_VALID_PROCID (procId));

    GT_assert (curTrace, (VAYUIPUPWR_state.refCount != 0));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (VAYUIPUPWR_state.refCount == 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_open",
                             VAYUIPUPWR_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if (handlePtr == NULL) {
        /*! @retval PWRMGR_E_HANDLE Invalid NULL handlePtr specified */
        status = PWRMGR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_open",
                             status,
                             "Invalid NULL handlePtr specified");
    }
    else if (!IS_VALID_PROCID (procId)) {
        /*! @retval PWRMGR_E_INVALIDARG Invalid procId specified */
        status = PWRMGR_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_open",
                             status,
                             "Invalid procId specified");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        /* Initialize return parameter handle. */
        *handlePtr = NULL;

        /* Check if the PwrMgr exists and return the handle if found. */
        if (VAYUIPUPWR_state.pwrHandles [procId] == NULL) {
            /*! @retval PWRMGR_E_NOTFOUND Specified instance not found */
            status = PWRMGR_E_NOTFOUND;
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "VAYUIPUPWR_open",
                              status,
                              "Specified VAYUIPUPWR instance does not exist!");
        }
        else {
            *handlePtr = VAYUIPUPWR_state.pwrHandles [procId];
        }
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    GT_1trace (curTrace, GT_LEAVE, "VAYUIPUPWR_open", status);

    /*! @retval PWRMGR_SUCCESS Operation successful */
    return status;
}

/*!
 *  @brief      Function to close a handle to an instance of this PwrMgr.
 *
 *  @param      handlePtr  Pointer to Handle to the PwrMgr instance
 *
 *  @sa         VAYUIPUPWR_open
 */
Int
VAYUIPUPWR_close (VAYUIPUPWR_Handle * handlePtr)
{
    Int status = PWRMGR_SUCCESS;

    GT_1trace (curTrace, GT_ENTER, "VAYUIPUPWR_close", handlePtr);

    GT_assert (curTrace, (handlePtr != NULL));
    GT_assert (curTrace, ((handlePtr != NULL) && (*handlePtr != NULL)));
    GT_assert (curTrace, (VAYUIPUPWR_state.refCount != 0));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (VAYUIPUPWR_state.refCount == 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_close",
                             VAYUIPUPWR_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if (handlePtr == NULL) {
        /*! @retval PWRMGR_E_INVALIDARG Invalid NULL handlePtr pointer
                                         specified*/
        status = PWRMGR_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_close",
                             status,
                             "Invalid NULL handlePtr pointer specified");
    }
    else if (*handlePtr == NULL) {
        /*! @retval PWRMGR_E_HANDLE Invalid NULL *handlePtr specified */
        status = PWRMGR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_close",
                             status,
                             "Invalid NULL *handlePtr specified");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined(IPC_BUILD_HLOS) */
        /* Nothing to be done for close. */
        *handlePtr = NULL;
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined(IPC_BUILD_HLOS) */

    GT_1trace (curTrace, GT_LEAVE, "VAYUIPUPWR_close", status);

    /*! @retval PWRMGR_SUCCESS Operation successful */
    return status;
}

/* =============================================================================
 * APIs called by PwrMgr module (part of function table interface)
 * =============================================================================
 */
/*!
 *  @brief      Function to attach to the PwrMgr.
 *
 *  @param      handle  Handle to the PwrMgr instance
 *  @param      params  Attach parameters
 *
 *  @sa         VAYUIPUPWR_detach
 */
Int
VAYUIPUPWR_attach (PwrMgr_Handle handle, PwrMgr_AttachParams * params)
{

    Int status                            = PWRMGR_SUCCESS;
    PwrMgr_Object *          pwrMgrHandle = (PwrMgr_Object *) handle;
    VAYUIPUPWR_Object *      object       = NULL;
    UInt16                   ipu1ProcId   = MultiProc_getId("IPU1");
    Memory_MapInfo           mapInfo;

    GT_2trace (curTrace, GT_ENTER, "VAYUIPUPWR_attach", handle, params);

    GT_assert (curTrace, (handle != NULL));
    GT_assert (curTrace, (params != NULL));
    GT_assert (curTrace, (VAYUIPUPWR_state.refCount != 0));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (VAYUIPUPWR_state.refCount == 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_attach",
                             VAYUIPUPWR_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval PWRMGR_E_HANDLE Invalid argument */
        status = PWRMGR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_attach",
                             status,
                             "Invalid handle specified");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined(IPC_BUILD_HLOS) */
        object = (VAYUIPUPWR_Object *) pwrMgrHandle->object;
        GT_assert (curTrace, (object != NULL));
        /* Map and get the virtual address for PRCM registers */
        if (handle->procId == ipu1ProcId) {
            mapInfo.src      = IPU1_PRCM_BASE_ADDR;
        }
        else {
            mapInfo.src      = IPU2_PRCM_BASE_ADDR;
        }
        mapInfo.size     = PRCM_SIZE;
        mapInfo.isCached = FALSE;
        status = Memory_map (&mapInfo);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
        if (status < 0) {
            status = VAYUIPUPWR_E_FAIL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUIPUPWR_attach",
                                 status,
                                 "Failure in mapping prcm module");
        }
        else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined(IPC_BUILD_HLOS) */
            object->prcmVA = mapInfo.dst;
            /* Map and get the virtual address for MMU registers */
            if (handle->procId == ipu1ProcId) {
                mapInfo.src      = IPU1_MMU_BASE;
            }
            else {
                mapInfo.src      = IPU2_MMU_BASE;
            }
            mapInfo.size     = MMU_SIZE;
            mapInfo.isCached = FALSE;
            status = Memory_map (&mapInfo);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
            if (status < 0) {
                status = VAYUIPUPWR_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "VAYUIPUPWR_attach",
                                     status,
                                     "Failure in mapping ipummu module");
            }
            else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined(IPC_BUILD_HLOS) */
                object->ipuMmuVA = mapInfo.dst;
                /* Map and get the virtual address for the control module */
                if (handle->procId == ipu1ProcId) {
                    mapInfo.src      = IPU1_CM_BASE_ADDR;
                }
                else {
                    mapInfo.src      = IPU2_CM_BASE_ADDR;
                }
                mapInfo.size     = CM_SIZE;
                mapInfo.isCached = FALSE;
                status = Memory_map (&mapInfo);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
                if (status < 0) {
                    status = VAYUIPUPWR_E_FAIL;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "VAYUIPUPWR_attach",
                                         status,
                                         "Failure in mapping ipubase module");
                }
                else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined(IPC_BUILD_HLOS) */
                    object->ipubaseVA = mapInfo.dst;
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
                }
            }
        }
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined(IPC_BUILD_HLOS) */

    GT_1trace (curTrace, GT_LEAVE, "VAYUIPUPWR_attach", status);
    /*! @retval PWRMGR_SUCCESS Operation successful */
    return (status);
}

/*!
 *  @brief      Function to detach from the PwrMgr.
 *
 *  @param      handle  Handle to the PwrMgr instance
 *
 *  @sa         VAYUIPUPWR_attach
 */
Int
VAYUIPUPWR_detach (PwrMgr_Handle handle)
{
    Int status                     = PWRMGR_SUCCESS;
    PwrMgr_Object * pwrMgrHandle   = (PwrMgr_Object *) handle;
    VAYUIPUPWR_Object * object = NULL;
    Memory_UnmapInfo     unmapInfo;


    GT_1trace (curTrace, GT_ENTER, "VAYUIPUPWR_detach", handle);

    GT_assert (curTrace, (handle != NULL));
    GT_assert (curTrace, (VAYUIPUPWR_state.refCount != 0));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (VAYUIPUPWR_state.refCount == 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_detach",
                             VAYUIPUPWR_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval PWRMGR_E_HANDLE Invalid argument */
        status = PWRMGR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_detach",
                             status,
                             "Invalid handle specified");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined(IPC_BUILD_HLOS) */
        object = (VAYUIPUPWR_Object *) pwrMgrHandle->object;
        GT_assert (curTrace, (object != NULL));

        /* Unmap the virtual address for prcm module */
        unmapInfo.addr = object->prcmVA;
        unmapInfo.size = PRCM_SIZE;
        unmapInfo.isCached = FALSE;
        if (unmapInfo.addr != 0) {
            status = Memory_unmap (&unmapInfo);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
            if (status < 0) {
                status = VAYUIPUPWR_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "VAYUIPUPWR_detach",
                                     status,
                                     "Failure in mapping prcm module");
            }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined(IPC_BUILD_HLOS) */
        }
        /* Unmap the virtual address for mmu base*/
        unmapInfo.addr = object->ipuMmuVA;
        unmapInfo.size = MMU_SIZE;
        unmapInfo.isCached = FALSE;
        if (unmapInfo.addr != 0) {
            status = Memory_unmap (&unmapInfo);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
            if (status < 0) {
                status = VAYUIPUPWR_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "VAYUIPUPWR_detach",
                                     status,
                                     "Failure in mapping ipuMmu module");
            }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined(IPC_BUILD_HLOS) */
        }

        /* Unmap the virtual address for ipu control base */
        unmapInfo.addr = object->ipubaseVA;
        unmapInfo.size = CM_SIZE;
        unmapInfo.isCached = FALSE;
        if (unmapInfo.addr != 0) {
            status = Memory_unmap (&unmapInfo);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
            if (status < 0) {
                status = VAYUIPUPWR_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "VAYUIPUPWR_detach",
                                     status,
                                     "Failure in mapping ipuMmu module");
            }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined(IPC_BUILD_HLOS) */
        }
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined(IPC_BUILD_HLOS) */

    GT_1trace (curTrace, GT_LEAVE, "VAYUIPUPWR_detach", status);
    /*! @retval PWRMGR_SUCCESS Operation successful */
    return (status);
}

/*!
 *  @brief      Function to power on the slave processor.
 *
 *              Power on the IVA subsystem, hold the DSP and SEQ in reset, and
 *              release IVA2_RST. This is a hostile reset of the IVA. If the IVA
 *              is already powered on, then it must be powered off in order to
 *              terminate all current activity and initiate a power-on-reset
 *              transition to bring the IVA to a know good state.
 *
 *  @param      handle    Handle to the PwrMgr instance
 *
 *  @sa         VAYUIPUPWR_off
 */
Int
VAYUIPUPWR_on (PwrMgr_Handle handle)
{
    Int                  status       = PWRMGR_SUCCESS ;
    Int32                tmpstatus    = 0;
    PwrMgr_Object *      pwrMgrHandle = (PwrMgr_Object *) handle;
    VAYUIPUPWR_Object * object   = NULL;
    IArg                     key;
    (Void)tmpstatus;
    GT_1trace (curTrace, GT_ENTER, "VAYUIPUPWR_on", handle);

    GT_assert (curTrace, (handle != NULL));
    GT_assert (curTrace, (VAYUIPUPWR_state.refCount != 0));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (VAYUIPUPWR_state.refCount == 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_on",
                             VAYUIPUPWR_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        /* This sets the refCount variable is not initialized, upper 16 bits is
         * written with module Id to ensure correctness of refCount variable.
         */
        key = Gate_enterSystem();
        VAYUIPUPWR_state.pwrstateRefCount++;
        if (VAYUIPUPWR_state.pwrstateRefCount > 1) {
            status = VAYUIPUPWR_S_ALREADYSETUP;
            Gate_leaveSystem(key);
        }
        else {
            Gate_leaveSystem(key);
#if !defined(IPC_BUILD_OPTIMIZE)&& defined(IPC_BUILD_HLOS)
            if (handle == NULL) {
                /*! @retval PWRMGR_E_HANDLE Invalid argument */
                status = PWRMGR_E_HANDLE;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "VAYUIPUPWR_on",
                                     status,
                                     "Invalid handle specified");
            }
            else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined(IPC_BUILD_HLOS) */
                 object = (VAYUIPUPWR_Object *) pwrMgrHandle->object;

                 GT_assert (curTrace, (object != NULL));
                 /* Enable spinlocks, mailbox and timers before powering on ipu */

                 VAYUIPUPWR_state.ipuSpinlockHandle
                            = ClockOps_get(object->clockHandle, "spinbox_ick");
                     /* Do not put this check under IPC_BUILD_OPTIMIZE */
                 GT_assert (curTrace,
                               (VAYUIPUPWR_state.ipuSpinlockHandle != NULL));
                 status = ClockOps_enable(object->clockHandle,
                                         VAYUIPUPWR_state.ipuSpinlockHandle);
                 GT_assert (curTrace, (status >= 0));

                 VAYUIPUPWR_state.ipuMailboxHandle
                            = ClockOps_get(object->clockHandle, "mailbox_ick");
                             /* Do not put this check under IPC_BUILD_OPTIMIZE */
                 GT_assert (curTrace, (VAYUIPUPWR_state.ipuMailboxHandle != NULL));
                 status = ClockOps_enable(object->clockHandle,
                                          VAYUIPUPWR_state.ipuMailboxHandle);
                 GT_assert (curTrace, (status >= 0));

                 /* poer on ipu */
                 VAYUIPUPWR_state.ipuClkHandle
                             = ClockOps_get(object->clockHandle, "ipu_ick");
                 /* Do not put this check under IPC_BUILD_OPTIMIZE */
                 if (VAYUIPUPWR_state.ipuClkHandle == NULL) {
                         /*! @retval PWRMGR_E_HANDLE Invalid argument */
                         status = PWRMGR_E_HANDLE;
                         GT_setFailureReason (curTrace,
                                              GT_4CLASS,
                                              "VAYUIPUPWR_on",
                                              status,
                                          "object->clkHandle retuned NULL clk_get failed for ipu");
                 }
                 else {
                     tmpstatus = ClockOps_enable(object->clockHandle,
                                              VAYUIPUPWR_state.ipuClkHandle);
                     GT_assert (curTrace, (tmpstatus >= 0));
                     /* Complete the remaining power sequence here*/
                     VAYUIPUMMU_enable(pwrMgrHandle);
                 }
#if !defined(IPC_BUILD_OPTIMIZE) && defined(IPC_BUILD_HLOS)
            }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined(IPC_BUILD_HLOS)*/
        }
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)*/
    GT_1trace (curTrace, GT_LEAVE, "VAYUIPUPWR_on", status);
    /*! @retval PWRMGR_SUCCESS Operation successful */
    return (status);
}

/*!
 *  @brief      Function to power off the slave processor.
 *
 *              Turn the IVA power domain off. To ensure a clean power-off
 *              transition, the IVA subsystem must first be turned on so that
 *              the DSP can initiate an autonomous power-off transition.
 *
 *  @param      handle    Handle to the PwrMgr instance
 *  @param      force     Indicates whether power-off is to be forced
 *
 *  @sa         VAYUIPUPWR_on
 */
Int
VAYUIPUPWR_off (PwrMgr_Handle handle, Bool force)
{
    Int                  status       = PWRMGR_SUCCESS ;
    PwrMgr_Object *      pwrMgrHandle = (PwrMgr_Object *) handle;
    VAYUIPUPWR_Object * object   = NULL;
    IArg                     key;

    GT_1trace (curTrace, GT_ENTER, "VAYUIPUPWR_off", handle);

    GT_assert (curTrace, (handle != NULL));

    GT_assert (curTrace, (VAYUIPUPWR_state.refCount != 0));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (VAYUIPUPWR_state.refCount == 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_off",
                             VAYUIPUPWR_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval PWRMGR_E_HANDLE Invalid argument */
        status = PWRMGR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUIPUPWR_off",
                             status,
                             "Invalid handle specified");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
                 object = (VAYUIPUPWR_Object *) pwrMgrHandle->object;
        key = Gate_enterSystem();
        VAYUIPUPWR_state.pwrstateRefCount--;
        Gate_leaveSystem(key);

        if (VAYUIPUPWR_state.pwrstateRefCount == 0) {
            VAYUIPUMMU_disable(pwrMgrHandle);
            /* Disable Mailbox clocks */
            if(VAYUIPUPWR_state.ipuMailboxHandle) {
                ClockOps_disable(object->clockHandle,
                                     VAYUIPUPWR_state.ipuMailboxHandle);
                ClockOps_put(object->clockHandle,
                                     VAYUIPUPWR_state.ipuMailboxHandle);
            }
            /* Disable Spinlock clocks */
            if(VAYUIPUPWR_state.ipuSpinlockHandle) {
                ClockOps_disable(object->clockHandle,
                                    VAYUIPUPWR_state.ipuSpinlockHandle);
                ClockOps_put(object->clockHandle,
                                    VAYUIPUPWR_state.ipuSpinlockHandle);
            }
            if(VAYUIPUPWR_state.ipuClkHandle) {
                ClockOps_disable(object->clockHandle,
                                         VAYUIPUPWR_state.ipuClkHandle);
                ClockOps_put(object->clockHandle,
                                         VAYUIPUPWR_state.ipuClkHandle);
            }
        }
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined(IPC_BUILD_HLOS) */
    GT_1trace (curTrace, GT_LEAVE, "VAYUIPUPWR_off", status);
    /*! @retval PWRMGR_SUCCESS Operation successful */
    return (status);
}

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
