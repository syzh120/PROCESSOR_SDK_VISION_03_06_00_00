/*
 *  @file   VAYUDspProc.c
 *
 * @brief       Processor implementation for VAYUDSP.
 *
 *              This module is responsible for taking care of device-specific
 *              operations for the processor. This module can be used
 *              stand-alone or as part of ProcMgr.
 *              The implementation is specific to VAYUDSP.
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2013-2016, Texas Instruments Incorporated
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
#include <ti/syslink/utils/Cfg.h>
#include <ti/syslink/utils/String.h>
#include <ti/syslink/utils/IGateProvider.h>
#include <ti/syslink/utils/GateMutex.h>
#include <ti/syslink/utils/Memory.h>

#include <string.h>

#include <ti/syslink/utils/Trace.h>
/* Module level headers */
#include <ProcDefs.h>
#include <Processor.h>
#include <VAYUDspProc.h>
#include <_VAYUDspProc.h>
#include <VAYUDspHal.h>
#include <VAYUDspHalReset.h>
#include <VAYUDspHalBoot.h>
#include <VAYUDspEnabler.h>
#include <ti/ipc/MultiProc.h>
#include <_MultiProc.h>
#include <RscTable.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */

/*!
 *  @brief  Number of static entries in address translation table.
 */
#define AddrTable_STATIC_COUNT 3

/*!
 *  @brief  Max entries in address translation table.
 */
#define AddrTable_SIZE 32

/* Number of DSPs supported */
#define NUM_DSPS 2

/* Convert procId to DSP # */
#define PROCID_TO_DSP(procId) (procId == VAYUDSPPROC_state.dsp1ProcId ?\
    0 : 1)


/*!
 *  @brief  VAYUDSPPROC Module state object
 */
typedef struct VAYUDSPPROC_ModuleObject_tag {
    UInt32              configSize;
    /*!< Size of configuration structure */
    VAYUDSPPROC_Config cfg;
    /*!< VAYUDSPPROC configuration structure */
    VAYUDSPPROC_Config defCfg;
    /*!< Default module configuration */
    VAYUDSPPROC_Params      defInstParams;
    /*!< Default parameters for the VAYUDSPPROC instances */
    Bool                isSetup;
    /*!< Indicates whether the VAYUDSPPROC module is setup. */
    VAYUDSPPROC_Handle procHandles [MultiProc_MAXPROCESSORS];
    /*!< Processor handle array. */
    IGateProvider_Handle         gateHandle;
    /*!< Handle of gate to be used for local thread safety */
    UInt16                     dsp1ProcId;
    /*!< MultiProc id of DSP1 (to avoid multiple lookups) */
} VAYUDSPPROC_ModuleObject;

/* Default memory regions */
static UInt32 AddrTable_count[NUM_DSPS] = {
    AddrTable_STATIC_COUNT,
    AddrTable_STATIC_COUNT
};

/*
 * Address translation table
 * static memory regions
 * CAUTION: AddrTable_STATIC_COUNT must match number of entries below.
 */
static ProcMgr_AddrInfo AddrTable_DSP1[AddrTable_SIZE] =
    {
        /* L2 RAM */
        {
            .addr[ProcMgr_AddrType_MasterKnlVirt] = -1u,
            .addr[ProcMgr_AddrType_MasterUsrVirt] = -1u,
            .addr[ProcMgr_AddrType_MasterPhys] = 0x40800000u,
            .addr[ProcMgr_AddrType_SlaveVirt] = 0x800000u,
            .addr[ProcMgr_AddrType_SlavePhys] = -1u,
            .size = 0x40000u,
            .isCached = FALSE,
            .mapMask = ProcMgr_SLAVEVIRT,
            .isMapped = TRUE,
            .refCount = 0u      /* refCount set to 0 for static entry */
        },

        /* L1P RAM */
        {
            .addr[ProcMgr_AddrType_MasterKnlVirt] = -1u,
            .addr[ProcMgr_AddrType_MasterUsrVirt] = -1u,
            .addr[ProcMgr_AddrType_MasterPhys] = 0x40E00000u,
            .addr[ProcMgr_AddrType_SlaveVirt] = 0xE00000u,
            .addr[ProcMgr_AddrType_SlavePhys] = -1u,
            .size = 0x8000u,
            .isCached = FALSE,
            .mapMask = ProcMgr_SLAVEVIRT,
            .isMapped = TRUE,
            .refCount = 0u      /* refCount set to 0 for static entry */
        },

        /* L1D RAM */
        {
            .addr[ProcMgr_AddrType_MasterKnlVirt] = -1u,
            .addr[ProcMgr_AddrType_MasterUsrVirt] = -1u,
            .addr[ProcMgr_AddrType_MasterPhys] = 0x40F00000u,
            .addr[ProcMgr_AddrType_SlaveVirt] = 0xF00000u,
            .addr[ProcMgr_AddrType_SlavePhys] = -1u,
            .size = 0x8000u,
            .isCached = FALSE,
            .mapMask = ProcMgr_SLAVEVIRT,
            .isMapped = TRUE,
            .refCount = 0u      /* refCount set to 0 for static entry */
        },
    };

static ProcMgr_AddrInfo AddrTable_DSP2[AddrTable_SIZE] =
    {
        /* L2 RAM */
        {
            .addr[ProcMgr_AddrType_MasterKnlVirt] = -1u,
            .addr[ProcMgr_AddrType_MasterUsrVirt] = -1u,
            .addr[ProcMgr_AddrType_MasterPhys] = 0x41000000u,
            .addr[ProcMgr_AddrType_SlaveVirt] = 0x800000u,
            .addr[ProcMgr_AddrType_SlavePhys] = -1u,
            .size = 0x40000u,
            .isCached = FALSE,
            .mapMask = ProcMgr_SLAVEVIRT,
            .isMapped = TRUE,
            .refCount = 0u      /* refCount set to 0 for static entry */
        },

        /* L1P RAM */
        {
            .addr[ProcMgr_AddrType_MasterKnlVirt] = -1u,
            .addr[ProcMgr_AddrType_MasterUsrVirt] = -1u,
            .addr[ProcMgr_AddrType_MasterPhys] = 0x41600000u,
            .addr[ProcMgr_AddrType_SlaveVirt] = 0xE00000u,
            .addr[ProcMgr_AddrType_SlavePhys] = -1u,
            .size = 0x8000u,
            .isCached = FALSE,
            .mapMask = ProcMgr_SLAVEVIRT,
            .isMapped = TRUE,
            .refCount = 0u      /* refCount set to 0 for static entry */
        },

        /* L1D RAM */
        {
            .addr[ProcMgr_AddrType_MasterKnlVirt] = -1u,
            .addr[ProcMgr_AddrType_MasterUsrVirt] = -1u,
            .addr[ProcMgr_AddrType_MasterPhys] = 0x41700000u,
            .addr[ProcMgr_AddrType_SlaveVirt] = 0xF00000u,
            .addr[ProcMgr_AddrType_SlavePhys] = -1u,
            .size = 0x8000u,
            .isCached = FALSE,
            .mapMask = ProcMgr_SLAVEVIRT,
            .isMapped = TRUE,
            .refCount = 0u      /* refCount set to 0 for static entry */
        },
    };

static ProcMgr_AddrInfo * AddrTable[NUM_DSPS] =
{
    AddrTable_DSP1,
    AddrTable_DSP2
};

/* =============================================================================
 *  Globals
 * =============================================================================
 */

/*!
 *  @var    VAYUDSPPROC_state
 *
 *  @brief  VAYUDSPPROC state object variable
 */
#if !defined(IPC_BUILD_DEBUG)
static
#endif /* if !defined(IPC_BUILD_DEBUG) */
VAYUDSPPROC_ModuleObject VAYUDSPPROC_state =
{
    .isSetup = FALSE,
    .configSize = sizeof(VAYUDSPPROC_Config),
    .gateHandle = NULL,
    .defInstParams.numMemEntries = AddrTable_STATIC_COUNT
};


/* =============================================================================
 * APIs directly called by applications
 * =============================================================================
 */
/*!
 *  @brief      Function to get the default configuration for the VAYUDSPPROC
 *              module.
 *
 *              This function can be called by the application to get their
 *              configuration parameter to VAYUDSPPROC_setup filled in by the
 *              VAYUDSPPROC module with the default parameters. If the user
 *              does not wish to make any change in the default parameters, this
 *              API is not required to be called.
 *
 *  @param      cfg        Pointer to the VAYUDSPPROC module configuration
 *                         structure in which the default config is to be
 *                         returned.
 *
 *  @sa         VAYUDSPPROC_setup
 */
Void
VAYUDSPPROC_getConfig (VAYUDSPPROC_Config * cfg)
{
    GT_1trace (curTrace, GT_ENTER, "VAYUDSPPROC_getConfig", cfg);

    GT_assert (curTrace, (cfg != NULL));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (cfg == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_getConfig",
                             PROCESSOR_E_INVALIDARG,
                             "Argument of type (VAYUDSPPROC_Config *) passed "
                             "is null!");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        Memory_copy (cfg,
                     &(VAYUDSPPROC_state.defCfg),
                     sizeof (VAYUDSPPROC_Config));
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    GT_0trace (curTrace, GT_LEAVE, "VAYUDSPPROC_getConfig");
}


/*!
 *  @brief      Function to setup the VAYUDSPPROC module.
 *
 *              This function sets up the VAYUDSPPROC module. This function
 *              must be called before any other instance-level APIs can be
 *              invoked.
 *              Module-level configuration needs to be provided to this
 *              function. If the user wishes to change some specific config
 *              parameters, then VAYUDSPPROC_getConfig can be called to get the
 *              configuration filled with the default values. After this, only
 *              the required configuration values can be changed. If the user
 *              does not wish to make any change in the default parameters, the
 *              application can simply call VAYUDSPPROC_setup with NULL
 *              parameters. The default parameters would get automatically used.
 *
 *  @param      cfg   Optional VAYUDSPPROC module configuration. If provided as
 *                    NULL, default configuration is used.
 *
 *  @sa         VAYUDSPPROC_destroy
 *              GateMutex_create
 */
Int
VAYUDSPPROC_setup (VAYUDSPPROC_Config * cfg)
{
    Int                  status = PROCESSOR_SUCCESS;
    VAYUDSPPROC_Config   tmpCfg;
    Error_Block          eb;

    Error_init(&eb);

    GT_1trace (curTrace, GT_ENTER, "VAYUDSPPROC_setup", cfg);

    if (cfg == NULL) {
        VAYUDSPPROC_getConfig (&tmpCfg);
        cfg = &tmpCfg;
    }

    /* Create a default gate handle for local module protection. */
    VAYUDSPPROC_state.gateHandle = (IGateProvider_Handle)
                               GateMutex_create ((GateMutex_Params *)NULL, &eb);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (VAYUDSPPROC_state.gateHandle == NULL) {
        /*! @retval PROCESSOR_E_FAIL Failed to create GateMutex! */
        status = PROCESSOR_E_FAIL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_setup",
                             status,
                             "Failed to create GateMutex!");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        /* Copy the user provided values into the state object. */
        Memory_copy (&VAYUDSPPROC_state.cfg,
                     cfg,
                     sizeof (VAYUDSPPROC_Config));

        /* Initialize the name to handles mapping array. */
        Memory_set (&VAYUDSPPROC_state.procHandles,
                    0,
                    (sizeof (VAYUDSPPROC_Handle) * MultiProc_MAXPROCESSORS));

        VAYUDSPPROC_state.dsp1ProcId = MultiProc_getId("DSP1");
        VAYUDSPPROC_state.isSetup = TRUE;
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPROC_setup", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return (status);
}


/*!
 *  @brief      Function to destroy the VAYUDSPPROC module.
 *
 *              Once this function is called, other VAYUDSPPROC module APIs,
 *              except for the VAYUDSPPROC_getConfig API cannot be called
 *              anymore.
 *
 *  @sa         VAYUDSPPROC_setup
 *              GateMutex_delete
 */
Int
VAYUDSPPROC_destroy (Void)
{
    Int    status = PROCESSOR_SUCCESS;
    UInt16 i;

    GT_0trace (curTrace, GT_ENTER, "VAYUDSPPROC_destroy");

    /* Check if any VAYUDSPPROC instances have not been deleted so far. If not,
     * delete them.
     */
    for (i = 0 ; i < MultiProc_MAXPROCESSORS ; i++) {
        GT_assert (curTrace, (VAYUDSPPROC_state.procHandles [i] == NULL));
        if (VAYUDSPPROC_state.procHandles [i] != NULL) {
            VAYUDSPPROC_delete (&(VAYUDSPPROC_state.procHandles [i]));
        }
    }

    if (VAYUDSPPROC_state.gateHandle != NULL) {
        GateMutex_delete ((GateMutex_Handle *)
                                &(VAYUDSPPROC_state.gateHandle));
    }

    VAYUDSPPROC_state.isSetup = FALSE;

    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPROC_destroy", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return (status);
}


/*!
 *  @brief      Function to initialize the parameters for this Processor
 *              instance.
 *
 *  @param      params  Configuration parameters to be returned
 *
 *  @sa         VAYUDSPPROC_create
 */
Void
VAYUDSPPROC_Params_init(
        VAYUDSPPROC_Handle    handle,
        VAYUDSPPROC_Params *  params)
{
    VAYUDSPPROC_Object * procObject = (VAYUDSPPROC_Object *) handle;

    GT_2trace (curTrace, GT_ENTER, "VAYUDSPPROC_Params_init", handle, params);

    GT_assert (curTrace, (params != NULL));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (params == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_Params_init",
                             PROCESSOR_E_INVALIDARG,
                             "Argument of type (VAYUDSPPROC_Params *) "
                             "passed is null!");
    }
    else {
#endif
        if (handle == NULL) {

            Memory_copy(params, &(VAYUDSPPROC_state.defInstParams),
                sizeof(VAYUDSPPROC_Params));
        }
        else {
            /* return updated VAYUDSPPROC instance specific parameters */
            Memory_copy(params, &(procObject->params), sizeof(VAYUDSPPROC_Params));
        }
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif

    GT_0trace (curTrace, GT_LEAVE, "VAYUDSPPROC_Params_init");
}

/*!
 *  @brief      Function to create an instance of this Processor.
 *
 *  @param      name    Name of the Processor instance.
 *  @param      params  Configuration parameters.
 *
 *  @sa         VAYUDSPPROC_delete
 */
VAYUDSPPROC_Handle
VAYUDSPPROC_create (      UInt16                procId,
                     const VAYUDSPPROC_Params * params)
{
    Int                   status    = PROCESSOR_SUCCESS;
    Processor_Object *    handle    = NULL;
    VAYUDSPPROC_Object *  object    = NULL;
    Int i                            = 0;
    ProcMgr_AddrInfo *ai             = NULL;
    IArg                  key;
    List_Params           listParams;

    GT_2trace (curTrace, GT_ENTER, "VAYUDSPPROC_create", procId, params);

    GT_assert (curTrace, IS_VALID_PROCID (procId));
    GT_assert (curTrace, (params != NULL));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (!IS_VALID_PROCID (procId)) {
        /* Not setting status here since this function does not return status.*/
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_create",
                             PROCESSOR_E_INVALIDARG,
                             "Invalid procId specified");
    }
    else if (params == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_create",
                             PROCESSOR_E_INVALIDARG,
                             "params passed is NULL!");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        /* Enter critical section protection. */
        key = IGateProvider_enter (VAYUDSPPROC_state.gateHandle);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
        /* Check if the Processor already exists for specified procId. */
        if (VAYUDSPPROC_state.procHandles [procId] != NULL) {
            status = PROCESSOR_E_ALREADYEXIST;
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "VAYUDSPPROC_create",
                              status,
                              "Processor already exists for specified procId!");
        }
        else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
            /* Allocate memory for the handle */
            handle = (Processor_Object *) Memory_calloc (NULL,
                                                      sizeof (Processor_Object),
                                                      0,
                                                      NULL);
            if (handle == NULL) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "VAYUDSPPROC_create",
                                     PROCESSOR_E_MEMORY,
                                     "Memory allocation failed for handle!");
            }
            else {
                /* Populate the handle fields */
                handle->procFxnTable.attach        = &VAYUDSPPROC_attach;
                handle->procFxnTable.detach        = &VAYUDSPPROC_detach;
                handle->procFxnTable.start         = &VAYUDSPPROC_start;
                handle->procFxnTable.stop          = &VAYUDSPPROC_stop;
                handle->procFxnTable.read          = &VAYUDSPPROC_read;
                handle->procFxnTable.write         = &VAYUDSPPROC_write;
                handle->procFxnTable.control       = &VAYUDSPPROC_control;
                handle->procFxnTable.map           = &VAYUDSPPROC_map;
                handle->procFxnTable.unmap         = &VAYUDSPPROC_unmap;
                handle->procFxnTable.translateAddr = &VAYUDSPPROC_translate;
                handle->procFxnTable.translateFromPte = NULL;

                handle->state = ProcMgr_State_Unknown;

                /* Allocate memory for the VAYUDSPPROC handle */
                handle->object = Memory_calloc (NULL,
                                                sizeof (VAYUDSPPROC_Object),
                                                0,
                                                NULL);
                if (handle->object == NULL) {
                    status = PROCESSOR_E_MEMORY;
                    GT_setFailureReason (curTrace,
                                GT_4CLASS,
                                "VAYUDSPPROC_create",
                                status,
                                "Memory allocation failed for handle->object!");
                }
                else {
                    handle->procId = procId;
                    object = (VAYUDSPPROC_Object *) handle->object;
                    object->halObject = NULL;
                    object->procHandle = (Processor_Handle)handle;
                    /* Copy params into instance object. */
                    Memory_copy (&(object->params),
                                 (Ptr) params,
                                 sizeof (VAYUDSPPROC_Params));

                    /* initialize the translation table */
                    for (i = AddrTable_count[PROCID_TO_DSP(procId)];
                        i < AddrTable_SIZE; i++) {
                        ai = &AddrTable[PROCID_TO_DSP(procId)][i];
                        ai->addr[ProcMgr_AddrType_MasterKnlVirt] = -1u;
                        ai->addr[ProcMgr_AddrType_MasterUsrVirt] = -1u;
                        ai->addr[ProcMgr_AddrType_MasterPhys] = -1u;
                        ai->addr[ProcMgr_AddrType_SlaveVirt] = -1u;
                        ai->addr[ProcMgr_AddrType_SlavePhys] = -1u;
                        ai->size = 0u;
                        ai->isCached = FALSE;
                        ai->mapMask = 0u;
                        ai->isMapped = FALSE;
                    }

                    /*
                     * initialize refCount for all entries
                     */
                    for (i = 0; i < AddrTable_SIZE; i++) {
                        AddrTable[PROCID_TO_DSP(procId)][i].refCount = 0u;
                    }
                    Memory_copy((Ptr)(object->params.memEntries),
                        AddrTable[PROCID_TO_DSP(procId)],
                        (procId == VAYUDSPPROC_state.dsp1ProcId ?
                        sizeof(AddrTable_DSP1) : sizeof(AddrTable_DSP2)));

                    /* Set the handle in the state object. */
                    VAYUDSPPROC_state.procHandles [procId] =
                                                     (VAYUDSPPROC_Handle) object;
                    /* Initialize the list of listeners */
                    List_Params_init(&listParams);
                    handle->registeredNotifiers = List_create(&listParams);

#if !defined(IPC_BUILD_OPTIMIZE)
                    if (handle->registeredNotifiers == NULL) {
                        /*! @retval PROCESSOR_E_FAIL OsalIsr_create failed */
                        status = PROCESSOR_E_FAIL;
                        GT_setFailureReason (curTrace,
                                             GT_4CLASS,
                                             "VAYUDSPPROC_create",
                                             status,
                                             "List_create failed");
                    }
                    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

                        handle->notifiersLock =
                                 OsalMutex_create(OsalMutex_Type_Interruptible);

#if !defined(IPC_BUILD_OPTIMIZE)
                        if (handle->notifiersLock == NULL) {
                            /*! @retval PROCESSOR_E_FAIL OsalIsr_create failed*/
                            status = PROCESSOR_E_FAIL;
                            GT_setFailureReason (curTrace,
                                                 GT_4CLASS,
                                                 "VAYUDSPPROC_create",
                                                 status,
                                                 "OsalMutex_create failed");
                        }
                    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                }
            }
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
        }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

        /* Leave critical section protection. */
        IGateProvider_leave (VAYUDSPPROC_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    if (status < 0) {
        if (handle !=  NULL) {
            if (handle->registeredNotifiers != NULL) {
                List_delete (&handle->registeredNotifiers);
            }
            if (handle->object != NULL) {
                Memory_free (NULL,
                             handle->object,
                             sizeof (VAYUDSPPROC_Object));
            }
            Memory_free (NULL, handle, sizeof (Processor_Object));
        }
        /*! @retval NULL Function failed */
        handle = NULL;
    }
    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPROC_create", handle);

    /*! @retval Valid-Handle Operation successful */
    return (VAYUDSPPROC_Handle) handle;
}


/*!
 *  @brief      Function to delete an instance of this Processor.
 *
 *              The user provided pointer to the handle is reset after
 *              successful completion of this function.
 *
 *  @param      handlePtr  Pointer to Handle to the Processor instance
 *
 *  @sa         VAYUDSPPROC_create
 */
Int
VAYUDSPPROC_delete (VAYUDSPPROC_Handle * handlePtr)
{
    Int                   status = PROCESSOR_SUCCESS;
    VAYUDSPPROC_Object *  object = NULL;
    Processor_Object *    handle;
    IArg                  key;
    List_Elem *           elem    = NULL;
    Processor_RegisterElem * regElem = NULL;

    GT_1trace (curTrace, GT_ENTER, "VAYUDSPPROC_delete", handlePtr);

    GT_assert (curTrace, (handlePtr != NULL));
    GT_assert (curTrace, ((handlePtr != NULL) && (*handlePtr != NULL)));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (handlePtr == NULL) {
        /*! @retval PROCESSOR_E_INVALIDARG Invalid NULL handlePtr pointer
                                         specified*/
        status = PROCESSOR_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_delete",
                             status,
                             "Invalid NULL handlePtr pointer specified");
    }
    else if (*handlePtr == NULL) {
        /*! @retval PROCESSOR_E_HANDLE Invalid NULL *handlePtr specified */
        status = PROCESSOR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_delete",
                             status,
                             "Invalid NULL *handlePtr specified");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        handle = (Processor_Object *) (*handlePtr);
        /* Enter critical section protection. */
        key = IGateProvider_enter (VAYUDSPPROC_state.gateHandle);

        /* Reset handle in PwrMgr handle array. */
        GT_assert (curTrace, IS_VALID_PROCID (handle->procId));
        VAYUDSPPROC_state.procHandles [handle->procId] = NULL;

        /* Free memory used for the VAYUDSPPROC object. */
        if (handle->object != NULL) {
            object = (VAYUDSPPROC_Object *) handle->object;
            Memory_free (NULL,
                         object,
                         sizeof (VAYUDSPPROC_Object));
            handle->object = NULL;
        }

        /*
         * Check the list of listeners to see if any are remaining
         * and reply to them
         */
        OsalMutex_delete(&handle->notifiersLock);

        while ((elem = List_dequeue(handle->registeredNotifiers)) != NULL) {
            regElem = (Processor_RegisterElem *)elem;

            /* Check if there is an associated timer and cancel it */
            if (regElem->timer != -1) {
                struct itimerspec value ;
                value.it_value.tv_sec = 0;
                value.it_value.tv_nsec = 0;
                value.it_interval.tv_sec = 0;
                value.it_interval.tv_nsec = 0;
                timer_settime(regElem->timer, 0, &value, NULL);

                timer_delete(regElem->timer);
                regElem->timer = -1;
            }

            /* Call the callback function so it can clean up. */
            regElem->info->cbFxn(handle->procId,
                                 NULL,
                                 handle->state,
                                 handle->state,
                                 ProcMgr_EventStatus_Canceled,
                                 regElem->info->arg);
            /* Free the memory */
            Memory_free(NULL, regElem, sizeof(Processor_RegisterElem));
        }

        /* Delete the list of listeners */
        List_delete(&handle->registeredNotifiers);

        /* Free memory used for the Processor object. */
        Memory_free (NULL, handle, sizeof (Processor_Object));
        *handlePtr = NULL;

        /* Leave critical section protection. */
        IGateProvider_leave (VAYUDSPPROC_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPROC_delete", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return (status);
}


/*!
 *  @brief      Function to open a handle to an instance of this Processor. This
 *              function is called when access to the Processor is required from
 *              a different process.
 *
 *  @param      handlePtr   Handle to the Processor instance
 *  @param      procId      Processor ID addressed by this Processor instance.
 *
 *  @sa         VAYUDSPPROC_close
 */
Int
VAYUDSPPROC_open (VAYUDSPPROC_Handle * handlePtr, UInt16 procId)
{
    Int status = PROCESSOR_SUCCESS;

    GT_2trace (curTrace, GT_ENTER, "VAYUDSPPROC_open", handlePtr, procId);

    GT_assert (curTrace, (handlePtr != NULL));
    GT_assert (curTrace, IS_VALID_PROCID (procId));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (handlePtr == NULL) {
        /*! @retval PROCESSOR_E_HANDLE Invalid NULL handlePtr specified */
        status = PROCESSOR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_open",
                             status,
                             "Invalid NULL handlePtr specified");
    }
    else if (!IS_VALID_PROCID (procId)) {
        /*! @retval PROCESSOR_E_INVALIDARG Invalid procId specified */
        status = PROCESSOR_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_open",
                             status,
                             "Invalid procId specified");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        /* Initialize return parameter handle. */
        *handlePtr = NULL;

        /* Check if the PwrMgr exists and return the handle if found. */
        if (VAYUDSPPROC_state.procHandles [procId] == NULL) {
            /*! @retval PROCESSOR_E_NOTFOUND Specified instance not found */
            status = PROCESSOR_E_NOTFOUND;
            GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_open",
                             status,
                             "Specified VAYUDSPPROC instance does not exist!");
        }
        else {
            *handlePtr = VAYUDSPPROC_state.procHandles [procId];
        }
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPROC_open", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to close a handle to an instance of this Processor.
 *
 *  @param      handlePtr  Pointer to Handle to the Processor instance
 *
 *  @sa         VAYUDSPPROC_open
 */
Int
VAYUDSPPROC_close (VAYUDSPPROC_Handle * handlePtr)
{
    Int status = PROCESSOR_SUCCESS;

    GT_1trace (curTrace, GT_ENTER, "VAYUDSPPROC_close", handlePtr);

    GT_assert (curTrace, (handlePtr != NULL));
    GT_assert (curTrace, ((handlePtr != NULL) && (*handlePtr != NULL)));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (handlePtr == NULL) {
        /*! @retval PROCESSOR_E_INVALIDARG Invalid NULL handlePtr pointer
                                         specified*/
        status = PROCESSOR_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_close",
                             status,
                             "Invalid NULL handlePtr pointer specified");
    }
    else if (*handlePtr == NULL) {
        /*! @retval PROCESSOR_E_HANDLE Invalid NULL *handlePtr specified */
        status = PROCESSOR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_close",
                             status,
                             "Invalid NULL *handlePtr specified");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        /* Nothing to be done for close. */
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPROC_close", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


/* =============================================================================
 * APIs called by Processor module (part of function table interface)
 * =============================================================================
 */
/*!
 *  @brief      Function to initialize the slave processor
 *
 *  @param      handle  Handle to the Processor instance
 *  @param      params  Attach parameters
 *
 *  @sa         VAYUDSPPROC_detach
 */
Int
VAYUDSPPROC_attach(
        Processor_Handle            handle,
        Processor_AttachParams *    params)
{

    Int                         status = PROCESSOR_SUCCESS;
    Processor_Object *          procHandle = (Processor_Object *)handle;
    VAYUDSPPROC_Object *        object = NULL;
    UInt32                      i = 0;
    UInt32                      index = 0;
    ProcMgr_AddrInfo *          me;
    Ipc_MemEntry *              entry;
    Ipc_MemEntry_Block          memBlock;
    VAYUDSP_HalMmuCtrlArgs_Enable mmuEnableArgs;
    VAYUDSP_HalParams           halParams;

    GT_2trace (curTrace, GT_ENTER, "VAYUDSPPROC_attach", handle, params);
    GT_assert (curTrace, (handle != NULL));
    GT_assert (curTrace, (params != NULL));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (handle == NULL) {
        /*! @retval PROCESSOR_E_HANDLE Invalid argument */
        status = PROCESSOR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_attach",
                             status,
                             "Invalid handle specified");
    }
    else if (params == NULL) {
            /*! @retval PROCESSOR_E_INVALIDARG Invalid argument */
            status = PROCESSOR_E_INVALIDARG;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUDSPPROC_attach",
                                 status,
                                 "Invalid params specified");
    }
    else {
#endif
        object = (VAYUDSPPROC_Object *) procHandle->object;
        GT_assert (curTrace, (object != NULL));

        /* Initialize halObject */
        halParams.procId = procHandle->procId;
        status = VAYUDSP_halInit(&(object->halObject), &halParams);

        if (status < 0) {
            GT_setFailureReason(curTrace, GT_4CLASS,
                "VAYUDSPPROC_attach", status,
                "VAYUDSP_halInit failed");
        }
        params->procArch = Processor_ProcArch_C66x;

        object->pmHandle = params->pmHandle;
        GT_0trace(curTrace, GT_1CLASS,
            "VAYUDSPPROC_attach: Mapping memory regions");

        /* search for dsp memory map */
        status = RscTable_process(procHandle->procId,
                                  TRUE,
                                  &memBlock.numEntries,
                                  procHandle,
                                  procHandle->bootMode);
        if (status < 0 || memBlock.numEntries > IPC_MAX_MEMENTRIES) {
            /*! @retval PROCESSOR_E_INVALIDARG Invalid argument */
            status = PROCESSOR_E_INVALIDARG;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUDSPPROC_attach",
                                 status,
                                 "Failed to process resource table");
        }
        else {
            status = RscTable_getMemEntries(procHandle->procId,
                                            memBlock.memEntries,
                                            &memBlock.numEntries);
            if (status < 0) {
                /*! @retval PROCESSOR_E_INVALIDARG Invalid argument */
                status = PROCESSOR_E_INVALIDARG;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "VAYUDSPPROC_attach",
                                     status,
                                     "Failed to get resource table memEntries");
            }
        }

        /* update translation tables with memory map */
        for (i = 0; (i < memBlock.numEntries)
            && (memBlock.memEntries[i].isValid) && (status >= 0); i++) {

            entry = &memBlock.memEntries[i];

            if (entry->map == FALSE) {
                /* update table with entries which don't require mapping */
                if (AddrTable_count[PROCID_TO_DSP(procHandle->procId)] !=
                   AddrTable_SIZE) {
                    me = &AddrTable[PROCID_TO_DSP(procHandle->procId)][
                        AddrTable_count[PROCID_TO_DSP(procHandle->procId)]];

                    me->addr[ProcMgr_AddrType_MasterKnlVirt] = -1u;
                    me->addr[ProcMgr_AddrType_MasterUsrVirt] = -1u;
                    me->addr[ProcMgr_AddrType_MasterPhys] =
                        entry->masterPhysAddr;
                    me->addr[ProcMgr_AddrType_SlaveVirt] = entry->slaveVirtAddr;
                    me->addr[ProcMgr_AddrType_SlavePhys] = -1u;
                    me->size = entry->size;
                    me->isCached = entry->isCached;
                    me->mapMask = entry->mapMask;

                    AddrTable_count[PROCID_TO_DSP(procHandle->procId)]++;
                }
                else {
                    status = PROCESSOR_E_FAIL;
                    GT_setFailureReason(curTrace, GT_4CLASS,
                        "VAYUDSPPROC_attach", status,
                        "AddrTable_SIZE reached!");
                }
            }
            else if (entry->map == TRUE) {
                /* send these entries back to ProcMgr for mapping */
                index = object->params.numMemEntries;

                if (index != ProcMgr_MAX_MEMORY_REGIONS) {
                    me = &object->params.memEntries[index];

                    me->addr[ProcMgr_AddrType_MasterKnlVirt] = -1u;
                    me->addr[ProcMgr_AddrType_MasterUsrVirt] = -1u;
                    me->addr[ProcMgr_AddrType_MasterPhys] =
                        entry->masterPhysAddr;
                    me->addr[ProcMgr_AddrType_SlaveVirt] = entry->slaveVirtAddr;
                    me->addr[ProcMgr_AddrType_SlavePhys] = -1u;
                    me->size = entry->size;
                    me->isCached = entry->isCached;
                    me->mapMask = entry->mapMask;

                    object->params.numMemEntries++;
                }
                else {
                    status = PROCESSOR_E_FAIL;
                    GT_setFailureReason(curTrace, GT_4CLASS,
                        "VAYUDSPPROC_attach", status,
                        "ProcMgr_MAX_MEMORY_REGIONS reached!");
                }
            }
            else {
                status = PROCESSOR_E_INVALIDARG;
                GT_setFailureReason(curTrace, GT_4CLASS,
                    "VAYUDSPPROC_attach", status,
                    "Memory map has entry with invalid 'map' value");
            }
        } /* for (...) */

        if (status >= 0) {
            /* populate the return params */
            params->numMemEntries = object->params.numMemEntries;
            memcpy((Ptr)params->memEntries, (Ptr)object->params.memEntries,
                sizeof(ProcMgr_AddrInfo) * params->numMemEntries);


            /* Setup the xbar for MMU fault interrupts */
            GT_0trace(curTrace, GT_3CLASS,
                "VAYUDSPPROC_attach: slave is now in reset");

            mmuEnableArgs.numMemEntries = 0;
            status = VAYUDSP_halMmuCtrl(object->halObject,
                Processor_MmuCtrlCmd_Enable, &mmuEnableArgs);

            if ((procHandle->bootMode == ProcMgr_BootMode_Boot)
                || (procHandle->bootMode == ProcMgr_BootMode_NoLoad_Pwr)) {
#if !defined(IPC_BUILD_OPTIMIZE)
                if (status < 0) {
                    GT_setFailureReason(curTrace, GT_4CLASS,
                        "VAYUDSPPROC_attach", status,
                        "Failed to enable the slave MMU");
                }
                else {
#endif
                    GT_0trace(curTrace, GT_2CLASS,
                        "VAYUDSPPROC_attach: Slave MMU "
                        "is configured!");

                    /*
                     * Pull DSP MMU out of reset to make internal
                     * memory "loadable"
                     */
                    status = VAYUDSP_halResetCtrl(
                        object->halObject,
                        Processor_ResetCtrlCmd_MMU_Release);
                    if (status < 0) {
                        /*! @retval status */
                        GT_setFailureReason(curTrace,
                            GT_4CLASS,
                            "VAYUDSP_halResetCtrl",
                            status,
                            "Reset MMU_Release failed");
                    }
#if !defined(IPC_BUILD_OPTIMIZE)
                }
#endif
            }

        }
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif

    GT_1trace(curTrace, GT_LEAVE,
        "VAYUDSPPROC_attach", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to detach from the Processor.
 *
 *  @param      handle  Handle to the Processor instance
 *
 *  @sa         VAYUDSPPROC_attach
 */
Int
VAYUDSPPROC_detach (Processor_Handle handle)
{
    Int                   status       = PROCESSOR_SUCCESS;
    Int                   tmpStatus    = PROCESSOR_SUCCESS;
    Processor_Object *    procHandle   = (Processor_Object *) handle;
    VAYUDSPPROC_Object * object       = NULL;
    Int i                              = 0;
    ProcMgr_AddrInfo *    ai;

    GT_1trace (curTrace, GT_ENTER, "VAYUDSPPROC_detach", handle);

    GT_assert (curTrace, (handle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (handle == NULL) {
        /*! @retval PROCESSOR_E_HANDLE Invalid argument */
        status = PROCESSOR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_detach",
                             PROCESSOR_E_HANDLE,
                             "Invalid handle specified");
    }
    else {
#endif
        object = (VAYUDSPPROC_Object *) procHandle->object;
        GT_assert (curTrace, (object != NULL));

        if (    (procHandle->bootMode == ProcMgr_BootMode_Boot)
            ||  (procHandle->bootMode == ProcMgr_BootMode_NoLoad_Pwr)) {

            GT_0trace(curTrace, GT_2CLASS,
                "VAYUDSPPROC_detach: Disabling Slave MMU ...");

            status = VAYUDSP_halResetCtrl(object->halObject,
                Processor_ResetCtrlCmd_MMU_Reset);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
            if (status < 0) {
                /*! @retval status */
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "VAYUDSP_halResetCtrl",
                                     status,
                                     "Reset MMU failed");
            }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

            status = VAYUDSP_halMmuCtrl(object->halObject,
                Processor_MmuCtrlCmd_Disable, NULL);

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
            if (status < 0) {
                GT_setFailureReason(curTrace, GT_4CLASS,
                    "VAYUDSPPROC_detach", status,
                    "Failed to disable the slave MMU");
            }
#endif
        }

        /* delete all dynamically added entries */
        for (i = AddrTable_STATIC_COUNT; i <
            AddrTable_count[PROCID_TO_DSP(procHandle->procId)]; i++) {
            ai = &AddrTable[PROCID_TO_DSP(procHandle->procId)][i];
            ai->addr[ProcMgr_AddrType_MasterKnlVirt] = -1u;
            ai->addr[ProcMgr_AddrType_MasterUsrVirt] = -1u;
            ai->addr[ProcMgr_AddrType_MasterPhys] = -1u;
            ai->addr[ProcMgr_AddrType_SlaveVirt] = -1u;
            ai->addr[ProcMgr_AddrType_SlavePhys] = -1u;
            ai->size = 0u;
            ai->isCached = FALSE;
            ai->mapMask = 0u;
            ai->isMapped = FALSE;
            ai->refCount = 0u;
        }
        object->params.numMemEntries = AddrTable_STATIC_COUNT;
        AddrTable_count[PROCID_TO_DSP(procHandle->procId)] = AddrTable_STATIC_COUNT;

        //No need to reset.. that will be done in STOP
        /*tmpStatus = VAYUDSP_halResetCtrl(object->halObject,
            VAYUDspHal_Reset_Detach);

        GT_0trace(curTrace, GT_2CLASS,
            "VAYUDSPPROC_detach: Slave processor is now in reset");*/

#if !defined(IPC_BUILD_OPTIMIZE)
        if ((tmpStatus < 0) && (status >= 0)) {
            status = tmpStatus;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUDSPPROC_detach",
                                 status,
                                 "Failed to reset the slave processor");
        }
#endif

        GT_0trace (curTrace,
                   GT_2CLASS,
                   "    VAYUDSPPROC_detach: Unmapping memory regions\n");

        tmpStatus = VAYUDSP_halExit (object->halObject);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
        if ((tmpStatus < 0) && (status >= 0)) {
            status = tmpStatus;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUDSPPROC_detach",
                                 status,
                                 "Failed to finalize HAL object");
        }
    }
#endif

    GT_1trace(curTrace, GT_LEAVE, "VAYUDSPPROC_detach", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to start the slave processor
 *
 *              Start the slave processor running from its entry point.
 *              Depending on the boot mode, this involves configuring the boot
 *              address and releasing the slave from reset.
 *
 *  @param      handle    Handle to the Processor instance
 *
 *  @sa         VAYUDSPPROC_stop, VAYUDSP_halBootCtrl, VAYUDSP_halResetCtrl
 */
Int
VAYUDSPPROC_start (Processor_Handle        handle,
                   UInt32                  entryPt,
                   Processor_StartParams * params)
{
    Int                   status        = PROCESSOR_SUCCESS ;
    Processor_Object *    procHandle    = (Processor_Object *) handle;
    VAYUDSPPROC_Object *  object        = NULL;

    GT_3trace (curTrace, GT_ENTER, "VAYUDSPPROC_start",
               handle, entryPt, params);

    GT_assert (curTrace, (handle != NULL));
    GT_assert (curTrace, (params != NULL));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (handle == NULL) {
        /*! @retval PROCESSOR_E_HANDLE Invalid argument */
        status = PROCESSOR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_start",
                             status,
                             "Invalid handle specified");
    }
    else if (params == NULL) {
            /*! @retval PROCESSOR_E_INVALIDARG Invalid argument */
            status = PROCESSOR_E_INVALIDARG;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUDSPPROC_start",
                                 status,
                                 "Invalid params specified");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        object = (VAYUDSPPROC_Object *) procHandle->object;
        GT_assert (curTrace, (object != NULL));
        if (    (procHandle->bootMode == ProcMgr_BootMode_Boot)
            ||  (procHandle->bootMode == ProcMgr_BootMode_NoLoad_Pwr)
            ||  (procHandle->bootMode == ProcMgr_BootMode_NoLoad_NoPwr)) {
            /* Slave is to be started only for Boot mode and NoLoad mode. */
            /* Specify the DSP boot address in the boot config register */
            status = VAYUDSP_halBootCtrl (object->halObject,
                                        Processor_BootCtrlCmd_SetEntryPoint,
                                        (Ptr) entryPt);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "VAYUDSPPROC_start",
                                     status,
                                     "Failed to set slave boot entry point");
            }
            else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
                status = rproc_dsp_setup(object->halObject,
                                         object->params.memEntries,
                                         object->params.numMemEntries);
                if (status < 0) {
                    /*! @retval status */
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "VAYUDSP_halResetCtrl",
                                         status,
                                         "rproc_dsp_setup failed");
                }
                /* release the slave cpu from reset */
                if (status >= 0) {
                    status = VAYUDSP_halResetCtrl(object->halObject,
                                                Processor_ResetCtrlCmd_Release);
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
                    if (status < 0) {
                        GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "VAYUDSPPROC_start",
                                         status,
                                         "Failed to release slave from reset");
                    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
                }
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
            }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        }

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    if (status >= 0) {
        GT_0trace (curTrace,
                   GT_1CLASS,
                   "    VAYUDSPPROC_start: Slave successfully started!\n");
    }
    else {
        GT_0trace (curTrace,
                   GT_1CLASS,
                   "    VAYUDSPPROC_start: Slave could not be started!\n");
    }

    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPROC_start", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to stop the slave processor
 *
 *              Stop the execution of the slave processor. Depending on the boot
 *              mode, this may result in placing the slave processor in reset.
 *
 *  @param      handle    Handle to the Processor instance
 *
 *  @sa         VAYUDSPPROC_start, VAYUDSP_halResetCtrl
 */
Int
VAYUDSPPROC_stop (Processor_Handle handle)
{
    Int                   status       = PROCESSOR_SUCCESS ;
    Processor_Object *    procHandle   = (Processor_Object *) handle;
    VAYUDSPPROC_Object * object        = NULL;

    GT_1trace (curTrace, GT_ENTER, "VAYUDSPPROC_stop", handle);

    GT_assert (curTrace, (handle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (handle == NULL) {
        /*! @retval PROCESSOR_E_HANDLE Invalid argument */
        status = PROCESSOR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_stop",
                             status,
                             "Invalid handle specified");
    }
    else {
#endif
        object = (VAYUDSPPROC_Object *) procHandle->object;
        GT_assert (curTrace, (object != NULL));

        /* Slave is to be stopped only for Boot mode and NoLoad mode. */
        if (    (procHandle->bootMode == ProcMgr_BootMode_Boot)
            ||  (procHandle->bootMode == ProcMgr_BootMode_NoLoad_Pwr)
            ||  (procHandle->bootMode == ProcMgr_BootMode_NoLoad_NoPwr)) {
            status = VAYUDSP_halResetCtrl(object->halObject,
                                          Processor_ResetCtrlCmd_Reset);

            GT_0trace (curTrace,
                       GT_1CLASS,
                       "    VAYUDSPPROC_stop: Slave is now in reset!\n");
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "VAYUDSPPROC_stop",
                                     status,
                                     "Failed to place slave in reset");
            }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
            rproc_dsp_destroy(object->halObject);
        }
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPROC_stop", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to read from the slave processor's memory.
 *
 *              Read from the slave processor's memory and copy into the
 *              provided buffer.
 *
 *  @param      handle     Handle to the Processor instance
 *  @param      procAddr   Address in host processor's address space of the
 *                         memory region to read from.
 *  @param      numBytes   IN/OUT parameter. As an IN-parameter, it takes in the
 *                         number of bytes to be read. When the function
 *                         returns, this parameter contains the number of bytes
 *                         actually read.
 *  @param      buffer     User-provided buffer in which the slave processor's
 *                         memory contents are to be copied.
 *
 *  @sa         VAYUDSPPROC_write
 */
Int
VAYUDSPPROC_read (Processor_Handle   handle,
                  UInt32             procAddr,
                  UInt32 *           numBytes,
                  Ptr                buffer)
{
    Int       status   = PROCESSOR_SUCCESS ;
    UInt8  *  procPtr8 = NULL;

    GT_4trace (curTrace, GT_ENTER, "VAYUDSPPROC_read",
               handle, procAddr, numBytes, buffer);

    GT_assert (curTrace, (handle   != NULL));
    GT_assert (curTrace, (numBytes != NULL));
    GT_assert (curTrace, (buffer   != NULL));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (handle == NULL) {
        /*! @retval PROCESSOR_E_HANDLE Invalid argument */
        status = PROCESSOR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_read",
                             status,
                             "Invalid handle specified");
    }
    else if (numBytes == 0) {
            /*! @retval PROCESSOR_E_INVALIDARG Invalid argument */
            status = PROCESSOR_E_INVALIDARG;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUDSPPROC_read",
                                 status,
                                 "Invalid numBytes specified");
    }
    else if (buffer == NULL) {
            /*! @retval PROCESSOR_E_INVALIDARG Invalid argument */
            status = PROCESSOR_E_INVALIDARG;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUDSPPROC_read",
                                 status,
                                 "Invalid buffer specified");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        procPtr8 = (UInt8 *) procAddr ;
        buffer = Memory_copy (buffer, procPtr8, *numBytes);
        GT_assert (curTrace, (buffer != (UInt32) NULL));
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
        if (buffer == (UInt32) NULL) {
            /*! @retval PROCESSOR_E_FAIL Failed in memcpy */
            status = PROCESSOR_E_FAIL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUDSPPROC_read",
                                 status,
                                 "Failed in Memory_copy");
            *numBytes = 0;
        }
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPROC_read",status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to write into the slave processor's memory.
 *
 *              Read from the provided buffer and copy into the slave
 *              processor's memory.
 *
 *  @param      handle     Handle to the Processor object
 *  @param      procAddr   Address in host processor's address space of the
 *                         memory region to write into.
 *  @param      numBytes   IN/OUT parameter. As an IN-parameter, it takes in the
 *                         number of bytes to be written. When the function
 *                         returns, this parameter contains the number of bytes
 *                         actually written.
 *  @param      buffer     User-provided buffer from which the data is to be
 *                         written into the slave processor's memory.
 *
 *  @sa         VAYUDSPPROC_read, VAYUDSPPROC_translateAddr
 */
Int
VAYUDSPPROC_write (Processor_Handle handle,
                   UInt32           procAddr,
                   UInt32 *         numBytes,
                   Ptr              buffer)
{
    Int                   status       = PROCESSOR_SUCCESS ;
    UInt8  *              procPtr8     = NULL;
    UInt8                 temp8_1;
    UInt8                 temp8_2;
    UInt8                 temp8_3;
    UInt8                 temp8_4;
    UInt32                temp;

    GT_4trace (curTrace, GT_ENTER, "VAYUDSPPROC_write",
               handle, procAddr, numBytes, buffer);

    GT_assert (curTrace, (handle   != NULL));
    GT_assert (curTrace, (numBytes != NULL));
    GT_assert (curTrace, (buffer   != NULL));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (handle == NULL) {
        /*! @retval PROCESSOR_E_HANDLE Invalid argument */
        status = PROCESSOR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_write",
                             status,
                             "Invalid handle specified");
    }
    else if (numBytes == 0) {
            /*! @retval PROCESSOR_E_INVALIDARG Invalid argument */
            status = PROCESSOR_E_INVALIDARG;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUDSPPROC_write",
                                 status,
                                 "Invalid numBytes specified");
    }
    else if (buffer == NULL) {
            /*! @retval PROCESSOR_E_INVALIDARG Invalid argument */
            status = PROCESSOR_E_INVALIDARG;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUDSPPROC_write",
                                 status,
                                 "Invalid buffer specified");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        if (*numBytes != sizeof (UInt32)) {
            procPtr8 = (UInt8 *) procAddr ;
            procAddr = (UInt32) Memory_copy (procPtr8,
                                             buffer,
                                             *numBytes);
            GT_assert (curTrace, (procAddr != (UInt32) NULL));
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
            if (procAddr == (UInt32) NULL) {
                /*! @retval PROCESSOR_E_FAIL Failed in Memory_copy */
                status = PROCESSOR_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "VAYUDSPPROC_write",
                                     status,
                                     "Failed in Memory_copy");
                *numBytes = 0;
            }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        }
        else  {
             /* For 4 bytes, directly write as a UInt32 */
            temp8_1 = ((UInt8 *) buffer) [0];
            temp8_2 = ((UInt8 *) buffer) [1];
            temp8_3 = ((UInt8 *) buffer) [2];
            temp8_4 = ((UInt8 *) buffer) [3];
            temp = (UInt32) (    ((UInt32) temp8_4 << 24)
                             |   ((UInt32) temp8_3 << 16)
                             |   ((UInt32) temp8_2 << 8)
                             |   ((UInt32) temp8_1));
            *((UInt32*) procAddr) = temp;
        }
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */

    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPROC_write",status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to perform device-dependent operations.
 *
 *              Performs device-dependent control operations as exposed by this
 *              implementation of the Processor module.
 *
 *  @param      handle     Handle to the Processor object
 *  @param      cmd        Device specific processor command
 *  @param      arg        Arguments specific to the type of command.
 *
 *  @sa
 */
Int
VAYUDSPPROC_control (Processor_Handle handle, Int32 cmd, Ptr arg)
{
    Int                   status       = PROCESSOR_SUCCESS ;

    GT_3trace (curTrace, GT_ENTER, "VAYUDSPPROC_control", handle, cmd, arg);

    GT_assert (curTrace, (handle   != NULL));
    /* cmd and arg can be 0/NULL, so cannot check for validity. */

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (handle == NULL) {
        /*! @retval PROCESSOR_E_HANDLE Invalid argument */
        status = PROCESSOR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_control",
                             status,
                             "Invalid handle specified");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
        /* No control operations currently implemented. */
        /*! @retval PROCESSOR_E_NOTSUPPORTED No control operations are supported
                                             for this device. */
        status = PROCESSOR_E_NOTSUPPORTED;
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS) */
    GT_1trace (curTrace, GT_LEAVE, "VAYUDSPPROC_control",status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Translate slave virtual address to master physical address.
 *
 *  @param      handle     Handle to the Processor object
 *  @param      dstAddr    Returned: master physical address.
 *  @param      srcAddr    Slave virtual address.
 *
 *  @sa
 */
Int
VAYUDSPPROC_translate(
        Processor_Handle    handle,
        UInt32 *            dstAddr,
        UInt32              srcAddr)
{
    Int                         status = PROCESSOR_SUCCESS;
    Processor_Object *          procHandle= (Processor_Object *)handle;
    VAYUDSPPROC_Object *        object = NULL;
    UInt32                      i;
    UInt32                      startAddr;
    UInt32                      endAddr;
    UInt32                      offset;
    ProcMgr_AddrInfo *          ai;

    GT_3trace(curTrace, GT_ENTER, "VAYUDSPPROC_translate",
              handle, dstAddr, srcAddr);

    GT_assert (curTrace, (handle != NULL));
    GT_assert (curTrace, (dstAddr != NULL));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (handle == NULL) {
        /*! @retval PROCESSOR_E_HANDLE Invalid argument */
        status = PROCESSOR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_translate",
                             status,
                             "Invalid handle specified");
    }
    else if (dstAddr == NULL) {
        /*! @retval PROCESSOR_E_INVALIDARG sglist provided as NULL */
        status = PROCESSOR_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_translate",
                             status,
                             "dstAddr provided as NULL");
    }
    else {
#endif
        object = (VAYUDSPPROC_Object *)procHandle->object;
        GT_assert(curTrace, (object != NULL));
        *dstAddr = -1u;

        /* search all entries AddrTable */
        for (i = 0; i < AddrTable_count[PROCID_TO_DSP(procHandle->procId)];
            i++) {
            ai = &AddrTable[PROCID_TO_DSP(procHandle->procId)][i];
            startAddr = ai->addr[ProcMgr_AddrType_SlaveVirt];
            endAddr = startAddr + ai->size;

            if ((startAddr <= srcAddr) && (srcAddr < endAddr)) {
                offset = srcAddr - startAddr;
                *dstAddr = ai->addr[ProcMgr_AddrType_MasterPhys] + offset;
                GT_3trace(curTrace, GT_1CLASS, "VAYUDSPPROC_translate: "
                    "translated [%d] srcAddr=0x%x --> dstAddr=0x%x",
                    i, srcAddr, *dstAddr);
                break;
            }
        }

        if (*dstAddr == -1u) {
            /* srcAddr not found in slave address space */
            status = PROCESSOR_E_INVALIDARG;
            GT_setFailureReason(curTrace, GT_4CLASS,
                "VAYUDSPPROC_translate", status,
                "srcAddr not found in slave address space");
        }
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif
    GT_1trace(curTrace, GT_LEAVE,
        "VAYUDSPPROC_translate: status=0x%x", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}

/*!
 *  @brief      Map the given address translation into the slave mmu
 *
 *  @param      handle      Handle to the Processor object
 *  @param      dstAddr     Base virtual address
 *  @param      nSegs       Number of given segments
 *  @param      sglist      Segment list
 */
Int
VAYUDSPPROC_map(
        Processor_Handle    handle,
        UInt32 *            dstAddr,
        UInt32              nSegs,
        Memory_SGList *     sglist)
{
    Int                         status = PROCESSOR_SUCCESS;
    Processor_Object *          procHandle = (Processor_Object *)handle;
    VAYUDSPPROC_Object *        object = NULL;
    Bool                        found = FALSE;
    UInt32                      startAddr;
    UInt32                      endAddr;
    UInt32                      i;
    UInt32                      j;
    ProcMgr_AddrInfo *          ai = NULL;

    GT_4trace (curTrace, GT_ENTER, "VAYUDSPPROC_map",
               handle, dstAddr, nSegs, sglist);

    GT_assert (curTrace, (handle != NULL));
    GT_assert (curTrace, (sglist != NULL));
    GT_assert (curTrace, (nSegs > 0));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (handle == NULL) {
        /*! @retval PROCESSOR_E_HANDLE Invalid argument */
        status = PROCESSOR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_map",
                             status,
                             "Invalid handle specified");
    }
    else if (sglist == NULL) {
        /*! @retval PROCESSOR_E_INVALIDARG sglist provided as NULL */
        status = PROCESSOR_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_map",
                             status,
                             "sglist provided as NULL");
    }
    else if (nSegs == 0) {
        /*! @retval PROCESSOR_E_INVALIDARG Number of segments provided is 0 */
        status = PROCESSOR_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_map",
                             status,
                             "Number of segments provided is 0");
    }
    else {
#endif
        object = (VAYUDSPPROC_Object *)procHandle->object;
        GT_assert (curTrace, (object != NULL));

        for (i = 0; (i < nSegs) && (status >= 0); i++) {
            /* Update the translation table with entries for which mapping
             * is required. Add the entry only if the range does not exist
             * in the translation table.
             */
            /* check in static entries first */
            for (j = 0;
                j < AddrTable_STATIC_COUNT; j++) {
                ai = &AddrTable[PROCID_TO_DSP(procHandle->procId)][j];
                startAddr = ai->addr[ProcMgr_AddrType_SlaveVirt];
                endAddr = startAddr + ai->size;

                if ((startAddr <= *dstAddr) && (*dstAddr < endAddr)) {
                    found = TRUE;

                    /* refCount does not need to be incremented for static entries */

                    break;
                 }
            }

            /* if not found in static entries, check in dynamic entries */
            if (!found) {
                for (j = AddrTable_STATIC_COUNT;
                    j < AddrTable_count[PROCID_TO_DSP(procHandle->procId)]; j++) {
                    ai = &AddrTable[PROCID_TO_DSP(procHandle->procId)][j];

                    if (ai->isMapped == TRUE) {
                        startAddr = ai->addr[ProcMgr_AddrType_SlaveVirt];
                        endAddr = startAddr + ai->size;

                        if ((startAddr <= *dstAddr) && (*dstAddr < endAddr)
                            && ((*dstAddr + sglist[i].size) <= endAddr)) {
                            found = TRUE;
                            ai->refCount++;
                            break;
                        }
                    }
                }
            }

            /* if not found and mmu is enabled, add new entry to table */
            if (!found) {
                if (AddrTable_count[PROCID_TO_DSP(procHandle->procId)] !=
                    AddrTable_SIZE) {
                    ai = &AddrTable[PROCID_TO_DSP(procHandle->procId)]
                        [AddrTable_count[PROCID_TO_DSP
                        (procHandle->procId)]];
                    ai->addr[ProcMgr_AddrType_MasterKnlVirt] = -1u;
                    ai->addr[ProcMgr_AddrType_MasterUsrVirt] = -1u;
                    ai->addr[ProcMgr_AddrType_MasterPhys] = sglist[i].paddr;
                    ai->addr[ProcMgr_AddrType_SlaveVirt] = *dstAddr;
                    ai->addr[ProcMgr_AddrType_SlavePhys] = -1u;
                    ai->size = sglist[i].size;
                    ai->isCached = sglist[i].isCached;
                    ai->refCount++;
                    ai->isMapped = TRUE;

                    AddrTable_count[PROCID_TO_DSP(procHandle->procId)]++;
                }
                else {
                    status = PROCESSOR_E_FAIL;
                    GT_setFailureReason(curTrace, GT_4CLASS,
                        "VAYUDSPPROC_map", status,
                        "AddrTable_SIZE reached!");
                }
            }
        }
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif
    GT_1trace(curTrace, GT_LEAVE, "VAYUDSPPROC_map", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to unmap slave address from host address space
 *
 *  @param      handle      Handle to the Processor object
 *  @param      dstAddr     Return parameter: Pointer to receive the mapped
 *                          address.
 *  @param      size        Size of the region to be mapped.
 *
 *  @sa
 */
Int
VAYUDSPPROC_unmap(
        Processor_Handle    handle,
        UInt32              addr,
        UInt32              size)
{
    Int                         status = PROCESSOR_SUCCESS;
    Processor_Object *          procHandle = (Processor_Object *)handle;
    VAYUDSPPROC_Object *        object = NULL;
    ProcMgr_AddrInfo *          ai;
    Int                         i;
    UInt32                      startAddr;
    UInt32                      endAddr;
    VAYUDSP_HalMmuCtrlArgs_DeleteEntry deleteEntryArgs;

    GT_3trace (curTrace, GT_ENTER, "VAYUDSPPROC_unmap",
               handle, addr, size);

    GT_assert (curTrace, (handle != NULL));
    GT_assert (curTrace, (size   != 0));

#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    if (handle == NULL) {
        /*! @retval PROCESSOR_E_HANDLE Invalid argument */
        status = PROCESSOR_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_unmap",
                             status,
                             "Invalid handle specified");
    }
    else if (size == 0) {
        /*! @retval  PROCESSOR_E_INVALIDARG Size provided is zero */
        status = PROCESSOR_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "VAYUDSPPROC_unmap",
                             status,
                             "Size provided is zero");
    }
    else {
#endif
        object = (VAYUDSPPROC_Object *) procHandle->object;
        GT_assert (curTrace, (object != NULL));

        /* Delete entries from translation
         * table only in last unmap called on that entry
         */
        for (i = 0;
            i < AddrTable_count[PROCID_TO_DSP(procHandle->procId)]; i++) {
            ai = &AddrTable[PROCID_TO_DSP(procHandle->procId)][i];

            if (!ai->isMapped) {
                continue;
            }

            startAddr = ai->addr[ProcMgr_AddrType_SlaveVirt];
            endAddr = startAddr + ai->size;

            if ((startAddr <= addr) && (addr < endAddr)) {
                ai->refCount--;

                if (ai->refCount == 0) {
                    ai->addr[ProcMgr_AddrType_MasterKnlVirt] = -1u;
                    ai->addr[ProcMgr_AddrType_MasterUsrVirt] = -1u;
                    ai->addr[ProcMgr_AddrType_MasterPhys] = -1u;
                    ai->addr[ProcMgr_AddrType_SlaveVirt] = -1u;
                    ai->addr[ProcMgr_AddrType_SlavePhys] = -1u;
                    ai->size = 0u;
                    ai->isCached = FALSE;
                    ai->mapMask = 0u;
                    ai->isMapped = FALSE;

                    /* Remove the entry from the DSP MMU also */
                    deleteEntryArgs.size          = size;
                    deleteEntryArgs.slaveVirtAddr = addr;
                    /* TBD: elementSize, endianism, mixedSized are
                     * hard coded now, must be configurable later
                     */
                    deleteEntryArgs.elementSize   = ELEM_SIZE_16BIT;
                    deleteEntryArgs.endianism     = LITTLE_ENDIAN;
                    deleteEntryArgs.mixedSize     = MMU_TLBES;

                    status = VAYUDSP_halMmuCtrl(object->halObject,
                        Processor_MmuCtrlCmd_DeleteEntry, &deleteEntryArgs);
#if !defined(IPC_BUILD_OPTIMIZE)
                    if (status < 0) {
                        GT_setFailureReason(curTrace, GT_4CLASS,
                            "VAYUDSPPROC_unmap", status,
                            "DSP MMU configuration failed");
                    }
#endif
                }
            }
        }
#if !defined(IPC_BUILD_OPTIMIZE) && defined (IPC_BUILD_HLOS)
    }
#endif
    GT_1trace(curTrace, GT_LEAVE, "VAYUDSPPROC_unmap", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
