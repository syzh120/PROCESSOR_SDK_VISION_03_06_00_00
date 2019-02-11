/*
 *  @file   VAYUDspPwr.c
 *
 *  @brief      PwrMgr implementation for VAYUDSP.
 *
 *              This module is responsible for handling power requests for
 *              the ProcMgr. The implementation is specific to VAYUDSP.
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



/* Standard headers */
#include <ti/syslink/Std.h>
/* OSAL & Utils headers */
#include <ti/syslink/utils/String.h>
#include <ti/syslink/utils/IGateProvider.h>
#include <ti/syslink/utils/GateMutex.h>
#include <ti/syslink/utils/Memory.h>
#include <_MultiProc.h>
#include <string.h>

#include <ti/syslink/utils/Trace.h>
#include <Bitops.h>

/* Module level headers */
#include <ti/ipc/MultiProc.h>
#include <ti/syslink/inc/_MultiProc.h>
#include <ti/syslink/inc/knl/PwrDefs.h>
#include <ti/syslink/inc/knl/PwrMgr.h>
#include <ti/syslink/inc/knl/VAYUDspPwr.h>
#include <ti/syslink/inc/knl/_VAYUDspPwr.h>
#include <ti/syslink/inc/ClockOps.h>



#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief  VAYUDSP module and mmr addresses (physical)
 */
#define PRCM_BASE_ADDR              0x48180000
#define PRCM_SIZE                   0x00003000
#define PM_ACTIVE_PWRSTST           0x00000A04
#define CM_ACTIVE_GEM_CLKCTRL       0x00000420


#define CM_MMU_CLKSTCTRL            0x0000140C
#define CM_ALWON_MMUDATA_CLKCTRL    0x0000159C
#define CM_MMUCFG_CLKSTCTRL         0x00001410
#define CM_ALWON_MMUCFG_CLKCTRL     0x000015A8


#define RM_ACTIVE_RSTCTRL           0x00000A10
#define RM_ACTIVE_RSTST             0x00000A14

#define GEM_L2RAM_DSP1_BASE_ADDR    0x40800000
#define GEM_L2RAM_DSP2_BASE_ADDR    0x41000000
#define GEM_L2RAM_SIZE              0x00040000

#define CTRL_MODULE_BASE_ADDR       0x48140000
#define CTRL_MODULE_SIZE            0x00020000
#define DSPMEM_SLEEP                0x00000650

#define DSP_IDLE_CFG                0x0000061c

#define REG(x)              *((volatile UInt32 *) (x))
#define MEM(x)              *((volatile UInt32 *) (x))

/*!
 *  @brief  VAYUDSPPWR Module state object
 */
typedef struct VAYUDSPPWR_ModuleObject_tag {
    UInt32                configSize;
    /*!< Size of configuration structure */
    VAYUDSPPWR_Config       cfg;
    /*!< VAYUDSPPWR configuration structure */
    VAYUDSPPWR_Config       defCfg;
    /*!< Default module configuration */
    Bool                  isSetup;
    /*!< Indicates whether the VAYUDSPPWR module is setup. */
    VAYUDSPPWR_Handle       pwrHandles [MultiProc_MAXPROCESSORS];
    /*!< PwrMgr handle array. */
    IGateProvider_Handle           gateHandle;
    /*!< Handle of gate to be used for local thread safety */
} VAYUDSPPWR_ModuleObject;

/*!
 *  @brief  VAYUDSPPWR instance object.
 */
struct VAYUDSPPWR_Object_tag {
    VAYUDSPPWR_Params params;
    /*!< Instance parameters (configuration values) */
    UInt32             prcmVA;
    /*!< Virtual address for prcm module */
    UInt32             controlVA;
    /*!< Virtual address for control module */
    UInt32             l2baseVA;
    /*!< Virtual address for control module */
    Ptr                dspClkHandle;
    /*!< dsp clk handle */
    Ptr                dspMmuClkHandle;
    /*!< dsp clk handle */
    Ptr                dspMmuCfgClkHandle;
    /*!< dsp clk handle */
    Ptr                dspSpinlockHandle;
    /*!< dsp Spinlock handle */
    Ptr                dspMailboxHandle;
    /*!< dsp Mailbox handle */
    Ptr                dspTimerIclkHandle;
    /*!< dsp Timer4 handle */
    Ptr                dspTimerFclkHandle;
    /*!< dsp Timer4 handle */
    ClockOps_Handle    clockHandle;
    /*!< Pointer to the Clock object. */

};

/* Defines the VAYUDSPPWR object type. */
typedef struct VAYUDSPPWR_Object_tag VAYUDSPPWR_Object;


/* =============================================================================
 *  Globals
 * =============================================================================
 */
/*!
 *  @var    VAYUDSPPWR_state
 *
 *  @brief  VAYUDSPPWR state object variable
 */
#if !defined(IPC_BUILD_DEBUG)
static
#endif /* if !defined(IPC_BUILD_DEBUG) */
VAYUDSPPWR_ModuleObject VAYUDSPPWR_state =
{
    .isSetup = FALSE,
    .configSize = sizeof (VAYUDSPPWR_Config),
    .defCfg.reserved = 0,
    .gateHandle = NULL,
};


/* =============================================================================
 * APIs directly called by applications
 * =============================================================================
 */
/*!
 *  @brief      Function to get the default configuration for the VAYUDSPPWR
 *              module.
 *
 *              This function can be called by the application to get their
 *              configuration parameter to VAYUDSPPWR_setup filled in by the
 *              VAYUDSPPWR module with the default parameters. If the user does
 *              not wish to make any change in the default parameters, this API
 *              is not required to be called.
 *
 *  @param      cfg        Pointer to the VAYUDSPPWR module configuration
 *                         structure in which the default config is to be
 *                         returned.
 *
 *  @sa         VAYUDSPPWR_setup
 */
Void
VAYUDSPPWR_getConfig (VAYUDSPPWR_Config * cfg)
{
    GT_1trace (curTrace, GT_ENTER, "VAYUDSPPWR_getConfig", cfg);

    GT_assert (curTrace, (cfg != NULL));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (cfg == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPWR_getConfig",
                             PWRMGR_E_INVALIDARG,
                             "Argument of type (VAYUDSPPWR_Config *) passed "
                             "is null!");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        memcpy (cfg,
                     &VAYUDSPPWR_state.defCfg,
                     sizeof (VAYUDSPPWR_Config));
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    GT_0trace (curTrace, GT_LEAVE, "VAYUDSPPWR_getConfig");
}


/*!
 *  @brief      Function to setup the VAYUDSPPWR module.
 *
 *              This function sets up the VAYUDSPPWR module. This function must
 *              be called before any other instance-level APIs can be invoked.
 *              Module-level configuration needs to be provided to this
 *              function. If the user wishes to change some specific config
 *              parameters, then VAYUDSPPWR_getConfig can be called to get the
 *              configuration filled with the default values. After this, only
 *              the required configuration values can be changed. If the user
 *              does not wish to make any change in the default parameters, the
 *              application can simply call VAYUDSPPWR_setup with NULL
 *              parameters. The default parameters would get automatically used.
 *
 *  @param      cfg   Optional VAYUDSPPWR module configuration. If provided as
 *                    NULL, default configuration is used.
 *
 *  @sa         VAYUDSPPWR_destroy
 *              GateMutex_create
 */
Int
VAYUDSPPWR_setup (VAYUDSPPWR_Config * cfg)
{
    Int               status = PWRMGR_SUCCESS;
    VAYUDSPPWR_Config tmpCfg;
    Error_Block eb;

    Error_init(&eb);

    GT_1trace (curTrace, GT_ENTER, "VAYUDSPPWR_setup", cfg);

    if (cfg == NULL) {
        VAYUDSPPWR_getConfig (&tmpCfg);
        cfg = &tmpCfg;
    }

    /* Create a default gate handle for local module protection. */
    VAYUDSPPWR_state.gateHandle = (IGateProvider_Handle)
                             GateMutex_create ((GateMutex_Params*)NULL, &eb);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (VAYUDSPPWR_state.gateHandle == NULL) {
        /*! @retval PWRMGR_E_FAIL Failed to create GateMutex! */
        status = PWRMGR_E_FAIL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPWR_setup",
                             status,
                             "Failed to create GateMutex!");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        /* Copy the user provided values into the state object. */
        Memory_copy (&VAYUDSPPWR_state.cfg,
                     cfg,
                     sizeof (VAYUDSPPWR_Config));

        /* Initialize the name to handles mapping array. */
        Memory_set (&VAYUDSPPWR_state.pwrHandles,
                    0,
                    (sizeof (VAYUDSPPWR_Handle) * MultiProc_MAXPROCESSORS));
        VAYUDSPPWR_state.isSetup = TRUE;
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPWR_setup", status);

    /*! @retval PWRMGR_SUCCESS Operation successful */
    return (status);
}


/*!
 *  @brief      Function to destroy the VAYUDSPPWR module.
 *
 *              Once this function is called, other VAYUDSPPWR module APIs, except
 *              for the VAYUDSPPWR_getConfig API cannot be called anymore.
 *
 *  @sa         VAYUDSPPWR_setup
 *              GateMutex_delete
 */
Int
VAYUDSPPWR_destroy (Void)
{
    Int    status = PWRMGR_SUCCESS;
    UInt16 i;

    GT_0trace (curTrace, GT_ENTER, "VAYUDSPPWR_destroy");

    /* Check if any VAYUDSPPWR instances have not been deleted so far. If not,
     * delete them.
     */
    for (i = 0 ; i < MultiProc_MAXPROCESSORS ; i++) {
        GT_assert (curTrace, (VAYUDSPPWR_state.pwrHandles [i] == NULL));
        if (VAYUDSPPWR_state.pwrHandles [i] != NULL) {
            VAYUDSPPWR_delete (&(VAYUDSPPWR_state.pwrHandles [i]));
        }
    }

    if (VAYUDSPPWR_state.gateHandle != NULL) {
        GateMutex_delete ((GateMutex_Handle *)
                                &(VAYUDSPPWR_state.gateHandle));
    }

    VAYUDSPPWR_state.isSetup = FALSE;

    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPWR_destroy", status);

    /*! @retval PWRMGR_SUCCESS Operation successful */
    return (status);
}


/*!
 *  @brief      Function to initialize the parameters for this PwrMgr instance.
 *
 *  @param      params  Configuration parameters.
 *
 *  @sa         VAYUDSPPWR_create
 */
Void
VAYUDSPPWR_Params_init (VAYUDSPPWR_Params * params)
{
    GT_1trace (curTrace, GT_ENTER, "VAYUDSPPWR_Params_init",params);

    GT_assert (curTrace, (params != NULL));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (params == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPWR_Params_init",
                             PWRMGR_E_INVALIDARG,
                             "Argument of type (VAYUDSPPWR_Params *) "
                             "passed is null!");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        /* Return updated VAYUDSPPWR instance specific parameters. */
        params->reserved = 0;
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    GT_0trace (curTrace, GT_LEAVE, "VAYUDSPPWR_Params_init");
}

/*!
 *  @brief      Function to create an instance of this PwrMgr.
 *
 *  @param      procId  Processor ID addressed by this PwrMgr instance.
 *  @param      params  Configuration parameters.
 *
 *  @sa         VAYUDSPPWR_delete
 */
VAYUDSPPWR_Handle
VAYUDSPPWR_create (      UInt16               procId,
                    const VAYUDSPPWR_Params * params)
{
    Int                  status = PWRMGR_SUCCESS;
    PwrMgr_Object *      handle = NULL;
    IArg                 key;

    GT_2trace (curTrace, GT_ENTER, "VAYUDSPPWR_create", procId, params);

    GT_assert (curTrace, IS_VALID_PROCID (procId));
    GT_assert (curTrace, (params != NULL));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (!IS_VALID_PROCID (procId)) {
        status = PWRMGR_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPWR_create",
                             status,
                             "Invalid procId specified");
    }
    else if (params == NULL) {
        status = PWRMGR_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPWR_create",
                             status,
                             "params passed is null!");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        /* Enter critical section protection. */
        key = IGateProvider_enter (VAYUDSPPWR_state.gateHandle);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
        /* Check if the PwrMgr already exists for specified procId. */
        if (VAYUDSPPWR_state.pwrHandles [procId] != NULL) {
            status = PWRMGR_E_ALREADYEXIST;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUDSPPWR_create",
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
                status = PWRMGR_E_MEMORY;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "VAYUDSPPWR_create",
                                     status,
                                     "Memory allocation failed for handle!");
            }
            else {
                /* Populate the handle fields */
                handle->pwrFxnTable.attach = &VAYUDSPPWR_attach;
                handle->pwrFxnTable.detach = &VAYUDSPPWR_detach;
                handle->pwrFxnTable.on     = &VAYUDSPPWR_on;
                handle->pwrFxnTable.off    = &VAYUDSPPWR_off;
                /* TBD: Other functions */

                /* Allocate memory for the VAYUDSPPWR handle */
                handle->object = Memory_calloc (NULL,
                                                sizeof (VAYUDSPPWR_Object),
                                                0,
                                                NULL);
                if (handle->object == NULL) {
                    status = PWRMGR_E_MEMORY;
                    GT_setFailureReason (curTrace,
                                        GT_4CLASS,
                                        "VAYUDSPPWR_create",
                                        status,
                                        "Memory allocation failed for handle!");
                }
                else {
                    handle->procId = procId;
                    VAYUDSPPWR_state.pwrHandles [procId] =
                                                (VAYUDSPPWR_Handle) handle;
                }
            }
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
        }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        /* Leave critical section protection. */
        IGateProvider_leave (VAYUDSPPWR_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    if (status < 0) {
        if (handle !=  NULL) {
            if (handle->object != NULL) {
                Memory_free (NULL, handle->object, sizeof (VAYUDSPPWR_Object));
            }
            Memory_free (NULL, handle, sizeof (PwrMgr_Object));
        }
        /*! @retval NULL Function failed */
        handle = NULL;
    }

    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPWR_create", handle);

    /*! @retval Valid-Handle Operation successful */
    return (VAYUDSPPWR_Handle) handle;
}


/*!
 *  @brief      Function to delete an instance of this PwrMgr.
 *
 *              The user provided pointer to the handle is reset after
 *              successful completion of this function.
 *
 *  @param      handlePtr  Pointer to Handle to the PwrMgr instance
 *
 *  @sa         VAYUDSPPWR_create
 */
Int
VAYUDSPPWR_delete (VAYUDSPPWR_Handle * handlePtr)
{
    Int                  status = PWRMGR_SUCCESS;
    VAYUDSPPWR_Object * object = NULL;
    PwrMgr_Object *      handle;
    IArg                 key;

    GT_1trace (curTrace, GT_ENTER, "VAYUDSPPWR_delete", handlePtr);

    GT_assert (curTrace, (handlePtr != NULL));
    GT_assert (curTrace, ((handlePtr != NULL) && (*handlePtr != NULL)));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (handlePtr == NULL) {
        /*! @retval PWRMGR_E_INVALIDARG Invalid NULL handlePtr specified*/
        status = PWRMGR_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPWR_delete",
                             status,
                             "Invalid NULL handlePtr specified");
    }
    else if (*handlePtr == NULL) {
        /*! @retval PWRMGR_E_HANDLE Invalid NULL *handlePtr specified */
        status = PWRMGR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPWR_delete",
                             status,
                             "Invalid NULL *handlePtr specified");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        handle = (PwrMgr_Object *) (*handlePtr);
        /* Enter critical section protection. */
        key = IGateProvider_enter (VAYUDSPPWR_state.gateHandle);

        /* Reset handle in PwrMgr handle array. */
        GT_assert (curTrace, IS_VALID_PROCID (handle->procId));
        VAYUDSPPWR_state.pwrHandles [handle->procId] = NULL;

        object = (VAYUDSPPWR_Object *) handle->object;
        /* Free memory used for the VAYUDSPPWR object. */
        if (handle->object != NULL) {
            /* Free memory used for the clock handle */
            Memory_free (NULL,
                         object,
                         sizeof (VAYUDSPPWR_Object));
            handle->object = NULL;
        }

        /* Free memory used for the PwrMgr object. */
        Memory_free (NULL, handle, sizeof (PwrMgr_Object));
        *handlePtr = NULL;

        /* Leave critical section protection. */
        IGateProvider_leave (VAYUDSPPWR_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPWR_delete", status);

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
 *  @sa         VAYUDSPPWR_close
 */
Int
VAYUDSPPWR_open (VAYUDSPPWR_Handle * handlePtr, UInt16 procId)
{
    Int status = PWRMGR_SUCCESS;

    GT_2trace (curTrace, GT_ENTER, "VAYUDSPPWR_open", handlePtr, procId);

    GT_assert (curTrace, (handlePtr != NULL));
    GT_assert (curTrace, IS_VALID_PROCID (procId));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (handlePtr == NULL) {
        /*! @retval PWRMGR_E_HANDLE Invalid NULL handlePtr specified */
        status = PWRMGR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPWR_open",
                             status,
                             "Invalid NULL handlePtr specified");
    }
    else if (!IS_VALID_PROCID (procId)) {
        /*! @retval PWRMGR_E_INVALIDARG Invalid procId specified */
        status = PWRMGR_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPWR_open",
                             status,
                             "Invalid procId specified");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        /* Initialize return parameter handle. */
        *handlePtr = NULL;

        /* Check if the PwrMgr exists and return the handle if found. */
        if (VAYUDSPPWR_state.pwrHandles [procId] == NULL) {
            /*! @retval PWRMGR_E_NOTFOUND Specified instance not found */
            status = PWRMGR_E_NOTFOUND;
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "VAYUDSPPWR_open",
                              status,
                              "Specified VAYUDSPPWR instance does not exist!");
        }
        else {
            *handlePtr = VAYUDSPPWR_state.pwrHandles [procId];
        }
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPWR_open", status);

    /*! @retval PWRMGR_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to close a handle to an instance of this PwrMgr.
 *
 *  @param      handlePtr  Pointer to Handle to the PwrMgr instance
 *
 *  @sa         VAYUDSPPWR_open
 */
Int
VAYUDSPPWR_close (VAYUDSPPWR_Handle * handlePtr)
{
    Int status = PWRMGR_SUCCESS;

    GT_1trace (curTrace, GT_ENTER, "VAYUDSPPWR_close", handlePtr);

    GT_assert (curTrace, (handlePtr != NULL));
    GT_assert (curTrace, ((handlePtr != NULL) && (*handlePtr != NULL)));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (handlePtr == NULL) {
        /*! @retval PWRMGR_E_INVALIDARG Invalid NULL handlePtr pointer
                                         specified*/
        status = PWRMGR_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPWR_close",
                             status,
                             "Invalid NULL handlePtr pointer specified");
    }
    else if (*handlePtr == NULL) {
        /*! @retval PWRMGR_E_HANDLE Invalid NULL *handlePtr specified */
        status = PWRMGR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPWR_close",
                             status,
                             "Invalid NULL *handlePtr specified");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        /* Nothing to be done for close. */
        *handlePtr = NULL;
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPWR_close", status);

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
 *  @sa         VAYUDSPPWR_detach
 */
Int
VAYUDSPPWR_attach (PwrMgr_Handle handle, PwrMgr_AttachParams * params)
{
    Int status                        = PWRMGR_SUCCESS;
    PwrMgr_Object *      pwrMgrHandle = (PwrMgr_Object *) handle;
    VAYUDSPPWR_Object *  object    = NULL;
    UInt16               dsp1ProcId   = MultiProc_getId("DSP1");
    Memory_MapInfo       mapInfo;
    /* Mapping for prcm base is done in VAYUVIDEOM3_phyShmemInit */

    GT_2trace (curTrace, GT_ENTER, "VAYUDSPPWR_attach", handle, params);

    GT_assert (curTrace, (handle != NULL));
    GT_assert (curTrace, (params != NULL));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (handle == NULL) {
        /*! @retval PWRMGR_E_HANDLE Invalid argument */
        status = PWRMGR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPWR_attach",
                             status,
                             "Invalid handle specified");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        object = (VAYUDSPPWR_Object *) pwrMgrHandle->object;
        GT_assert (curTrace, (object != NULL));
        /* Map and get the virtual address for system control module */
        mapInfo.src      = PRCM_BASE_ADDR;
        mapInfo.size     = PRCM_SIZE;
        mapInfo.isCached = FALSE;
        status = Memory_map (&mapInfo);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
        if (status < 0) {
            status = VAYUDSPPWR_E_FAIL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUDSPPWR_attach",
                                 status,
                                 "Failure in mapping prcm module");
        }
        else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
            object->prcmVA = mapInfo.dst;

            /* Map and get the virtual address for system control module */
            mapInfo.src      = CTRL_MODULE_BASE_ADDR;
            mapInfo.size     = CTRL_MODULE_SIZE;
            mapInfo.isCached = FALSE;
            status = Memory_map (&mapInfo);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
            if (status < 0) {
                status = VAYUDSPPWR_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "VAYUDSPPWR_attach",
                                     status,
                                     "Failure in mapping prcm module");
            }
            else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
                object->controlVA = mapInfo.dst;

                /* Map and get the virtual address for system l2 ram */
                if (handle->procId == dsp1ProcId) {
                    mapInfo.src      = GEM_L2RAM_DSP1_BASE_ADDR;
                }
                else {
                    mapInfo.src      = GEM_L2RAM_DSP2_BASE_ADDR;
                }
                mapInfo.size     = GEM_L2RAM_SIZE;
                mapInfo.isCached = FALSE;
                status = Memory_map (&mapInfo);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
                if (status < 0) {
                    status = VAYUDSPPWR_E_FAIL;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "VAYUDSPPWR_attach",
                                         status,
                                         "Failure in mapping prcm module");
                }
                else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
                object->l2baseVA = mapInfo.dst;
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
                }
            }
        }
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
    /*! @retval PWRMGR_SUCCESS Operation successful */
    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPWR_attach", status);
    return (status);

}


/*!
 *  @brief      Function to detach from the PwrMgr.
 *
 *  @param      handle  Handle to the PwrMgr instance
 *
 *  @sa         VAYUDSPPWR_attach
 */
Int
VAYUDSPPWR_detach (PwrMgr_Handle handle)
{

    Int status                     = PWRMGR_SUCCESS;
    PwrMgr_Object * pwrMgrHandle   = (PwrMgr_Object *) handle;
    VAYUDSPPWR_Object * object = NULL;
    Memory_UnmapInfo     unmapInfo;


    /* Mapping for prcm base is done in VAYUVIDEOM3_phyShmemInit */

    GT_1trace (curTrace, GT_ENTER, "VAYUDSPPWR_detach", handle);

    GT_assert (curTrace, (handle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (handle == NULL) {
        /*! @retval PWRMGR_E_HANDLE Invalid argument */
        status = PWRMGR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPWR_detach",
                             status,
                             "Invalid handle specified");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        object = (VAYUDSPPWR_Object *) pwrMgrHandle->object;
        GT_assert (curTrace, (object != NULL));

        if (object->controlVA != 0x0) {
            /* Unmap the virtual address for control module */
            unmapInfo.addr = object->controlVA;
            unmapInfo.size = CTRL_MODULE_SIZE;
            unmapInfo.isCached = FALSE;
            if (unmapInfo.addr != 0) {
                status = Memory_unmap (&unmapInfo);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
                if (status < 0) {
                    status = VAYUDSPPWR_E_FAIL;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "VAYUDSPPWR_detach",
                                         status,
                                         "Failure in mapping prcm module");
                }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
            }
        }
        if (object->prcmVA != 0x0) {
            /* Unmap the virtual address for prcm module */
            unmapInfo.addr = object->prcmVA;
            unmapInfo.size = PRCM_SIZE;
            unmapInfo.isCached = FALSE;
            if (unmapInfo.addr != 0) {
                status = Memory_unmap (&unmapInfo);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
                if (status < 0) {
                    status = VAYUDSPPWR_E_FAIL;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "VAYUDSPPWR_detach",
                                         status,
                                         "Failure in mapping prcm module");
                }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
            }
        }
        if (object->l2baseVA != 0x0) {
            /* Unmap the virtual address for prcm module */
            unmapInfo.addr = object->l2baseVA;
            unmapInfo.size = GEM_L2RAM_SIZE;
            unmapInfo.isCached = FALSE;
            if (unmapInfo.addr != 0) {
                status = Memory_unmap (&unmapInfo);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
                if (status < 0) {
                    status = VAYUDSPPWR_E_FAIL;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "VAYUDSPPWR_detach",
                                         status,
                                         "Failure in mapping prcm module");
                }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
            }
        }
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPWR_detach", status);
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
 *  @sa         VAYUDSPPWR_off
 */
Int
VAYUDSPPWR_on (PwrMgr_Handle handle)
{

    Int                  status       = PWRMGR_SUCCESS ;

#if !defined (NETRA_SIMULATOR) /* Commented for simulator */
    PwrMgr_Object *      pwrMgrHandle = (PwrMgr_Object *) handle;
    VAYUDSPPWR_Object * object   = NULL;

    GT_1trace (curTrace, GT_ENTER, "VAYUDSPPWR_on", handle);

    GT_assert (curTrace, (handle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (handle == NULL) {
        /*! @retval PWRMGR_E_HANDLE Invalid argument */
        status = PWRMGR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPWR_on",
                             status,
                             "Invalid handle specified");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        object = (VAYUDSPPWR_Object *) pwrMgrHandle->object;
        GT_assert (curTrace, (object != NULL));

        /* Enable spinlocks, mailbox and timers before powering on dsp */
        object->dspSpinlockHandle = ClockOps_get(object->clockHandle, "spinbox_ick");

        /* Do not put this check under IPC_BUILD_OPTIMIZE */
        GT_assert (curTrace, (object->dspSpinlockHandle != NULL));
        status = ClockOps_enable(object->clockHandle, object->dspSpinlockHandle);
        if (status < 0) {
            /*! @retval PWRMGR_E_HANDLE Invalid argument */
            status = PWRMGR_E_FAIL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUDSPPWR_on",
                                 status,
                                 "ClockOps_enable failed");
        }
        object->dspMailboxHandle = ClockOps_get(object->clockHandle, "mailbox_ick");
        /* Do not put this check under IPC_BUILD_OPTIMIZE */
        GT_assert (curTrace, (object->dspMailboxHandle != NULL));
        status = ClockOps_enable(object->clockHandle, object->dspMailboxHandle);
        GT_assert (curTrace, (status >= 0));

        /* GP timer4 is actually timer 3 for bios it will be enabled from bios
         * Here we are enabling the gptimer 4 clk module
         */

        object->dspTimerIclkHandle = ClockOps_get(object->clockHandle, "gpt4_ick");
        /* Do not put this check under IPC_BUILD_OPTIMIZE */
        GT_assert (curTrace, (object->dspTimerIclkHandle != NULL));
        status = ClockOps_enable(object->clockHandle, object->dspTimerIclkHandle);
        GT_assert (curTrace, (status >= 0));

        object->dspTimerFclkHandle = ClockOps_get(object->clockHandle, "gpt4_fck");
        /* Do not put this check under IPC_BUILD_OPTIMIZE */
        GT_assert (curTrace, (object->dspTimerFclkHandle != NULL));
        status = ClockOps_enable(object->clockHandle, object->dspTimerFclkHandle);
        GT_assert (curTrace, (status >= 0));

        /* Enable Dsp MMU clocks */

        object->dspMmuCfgClkHandle = ClockOps_get(object->clockHandle, "mmu_cfg_ick");
        /* Do not put this check under IPC_BUILD_OPTIMIZE */
        GT_assert (curTrace, (object->dspMmuCfgClkHandle != NULL));
        status = ClockOps_enable(object->clockHandle, object->dspMmuCfgClkHandle);
        GT_assert (curTrace, (status >= 0));

        object->dspMmuClkHandle = ClockOps_get(object->clockHandle, "mmu_ick");
        /* Do not put this check under IPC_BUILD_OPTIMIZE */
        GT_assert (curTrace, (object->dspMmuClkHandle != NULL));
        status = ClockOps_enable(object->clockHandle, object->dspMmuClkHandle);
        GT_assert (curTrace, (status >= 0));
        object->dspClkHandle = ClockOps_get(object->clockHandle, "gem_ick");

        GT_assert (curTrace, (object->dspClkHandle != NULL));
        status = ClockOps_enable(object->clockHandle, object->dspClkHandle);
        GT_assert (curTrace, (status >= 0));

        /* Warm Reset to  access Internal RAM of DSP - to access internal RAM */
//      REG((object->prcmVA) + RM_ACTIVE_RSTCTRL) = 0x01;

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPWR_on", status);
    /*! @retval PWRMGR_SUCCESS Operation successful */
#endif /*#if !defined (NETRA_SIMULATOR)*/
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
 *  @sa         VAYUDSPPWR_on
 */
Int
VAYUDSPPWR_off (PwrMgr_Handle handle, Bool force)
{
    Int                  status       = PWRMGR_SUCCESS ;
    PwrMgr_Object *      pwrMgrHandle = (PwrMgr_Object *) handle;
    VAYUDSPPWR_Object * object   = NULL;

    GT_1trace (curTrace, GT_ENTER, "VAYUDSPPWR_off", handle);

    GT_assert (curTrace, (handle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (handle == NULL) {
        /*! @retval PWRMGR_E_HANDLE Invalid argument */
        status = PWRMGR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPWR_off",
                             status,
                             "Invalid handle specified");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        object = (VAYUDSPPWR_Object *) pwrMgrHandle->object;
        GT_assert (curTrace, (object != NULL));


        /* Disable Dsp mmu clocks */
        if(object->dspMmuClkHandle) {
            ClockOps_disable(object->clockHandle, object->dspMmuClkHandle);
            ClockOps_put(object->clockHandle, object->dspMmuClkHandle);
        }
        /* Disable Dsp mmu cfg clocks */
        if(object->dspMmuCfgClkHandle) {
            ClockOps_disable(object->clockHandle, object->dspMmuCfgClkHandle);
            ClockOps_put(object->clockHandle, object->dspMmuCfgClkHandle);
        }

        /* assert DSP standby, removed to fix DSP internal memory load, -rams */
//      REG(object->controlVA + DSP_IDLE_CFG) |= 0x8000;

        /* Disable GEM clocks */
        if(object->dspClkHandle) {
            ClockOps_disable(object->clockHandle, object->dspClkHandle);
            ClockOps_put(object->clockHandle, object->dspClkHandle);
        }

        /* Disable  Timer4 functional clocks */
        if(object->dspTimerFclkHandle) {
            ClockOps_disable(object->clockHandle, object->dspTimerFclkHandle);
            ClockOps_put(object->clockHandle, object->dspTimerFclkHandle);
        }
        /* Disable Timer4 interface clocks */
        if(object->dspTimerIclkHandle) {
            ClockOps_disable(object->clockHandle, object->dspTimerIclkHandle);
            ClockOps_put(object->clockHandle, object->dspTimerIclkHandle);
        }
        /* Disable Mailbox clocks */
        if(object->dspMailboxHandle) {
            ClockOps_disable(object->clockHandle, object->dspMailboxHandle);
            ClockOps_put(object->clockHandle, object->dspMailboxHandle);
        }
        /* Disable Spinlock clocks */
        if(object->dspSpinlockHandle) {
            ClockOps_disable(object->clockHandle, object->dspSpinlockHandle);
            ClockOps_put(object->clockHandle, object->dspSpinlockHandle);
        }

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPWR_off", status);
    /*! @retval PWRMGR_SUCCESS Operation successful */
    return (status);
}


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
