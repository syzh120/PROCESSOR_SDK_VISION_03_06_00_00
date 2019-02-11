/*
 *  @file   ProcMgr.c
 *
 *  @brief      The Processor Manager on a master processor provides control
 *              functionality for a slave device.
 *
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


/* Standard headers */
#include <ti/syslink/Std.h>

/*-------------------------   OSAL and utils   -------------------------------*/
#include <ti/syslink/utils/Gate.h>
#include <ti/syslink/utils/IGateProvider.h>
#include <ti/syslink/utils/GateMutex.h>
#include <ti/syslink/utils/Memory.h>

/*-------------------------   OSAL and utils   -------------------------------*/
#include <ti/syslink/utils/Trace.h>
/*-------------------------   Standard headers   -----------------------------*/
#include <Bitops.h>

/*-------------------------   Module headers   -------------------------------*/
#include <ti/syslink/ProcMgr.h>
#include <_ProcMgr.h>
#include <ProcMgrDrv.h>
#include <ProcDefs.h>
#include <Processor.h>
#include <LoaderDefs.h>
#include <Loader.h>
#include <PwrDefs.h>
#include <PwrMgr.h>
#include <ti/ipc/MultiProc.h>
#include <_MultiProc.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief  Checks if a value lies in given range.
 */
#define IS_RANGE_VALID(x,min,max) (((x) < (max)) && ((x) >= (min)))

/*! @brief Macro to make a correct module magic number with refCount */
#define ProcMgr_MAKE_MAGICSTAMP(x) ((ProcMgr_MODULEID << 12u) | (x))

/*!
 *  @brief  ProcMgr Module state object
 */
typedef struct ProcMgr_ModuleObject_tag {
    Atomic               refCount;
    /*!< Reference count */
    UInt32               configSize;
    /*!< Size of configuration structure */
    ProcMgr_Config       cfg;
    /*!< ProcMgr configuration structure */
    ProcMgr_Config       defCfg;
    /*!< Default module configuration */
    ProcMgr_Params       defInstParams;
    /*!< Default parameters for the ProcMgr instances */
    ProcMgr_AttachParams defAttachParams;
    /*!< Default parameters for the ProcMgr attach function */
    ProcMgr_StartParams  defStartParams;
    /*!< Default parameters for the ProcMgr start function */
    IGateProvider_Handle gateHandle;
    /*!< Handle of gate to be used for local thread safety */
    ProcMgr_Handle       procHandles [MultiProc_MAXPROCESSORS];
    /*!< Array of Handles of ProcMgr instances */
} ProcMgr_ModuleObject;

/*!
 *  @brief  ProcMgr instance object
 */
struct ProcMgr_Object_tag {
    UInt16                 procId;
    /*!< Processor ID associated with this ProcMgr. */
    Processor_Object *     procHandle;
    /*!< Handle to the Processor object associated with this ProcMgr. */
    Loader_Object *        loaderHandle;
    /*!< Handle to the Loader object associated with this ProcMgr. */
    PwrMgr_Object *        pwrHandle;
    /*!< Handle to the PwrMgr object associated with this ProcMgr. */
    /*!< Processor ID of the processor being represented by this instance. */
    ProcMgr_Params         params;
    /*!< ProcMgr instance params structure */
    ProcMgr_AttachParams   attachParams;
    /*!< ProcMgr attach params structure */
    ProcMgr_StartParams    startParams;
    /*!< ProcMgr start params structure */
    UInt32                 fileId;
    /*!< File ID of the loaded static executable */
    UInt16                 maxMemoryRegions;
    /*!< Number of storage slots in memEntries */
    UInt16                 numMemEntries;
    /*!< Number of valid memory entries */
    ProcMgr_MappedMemEntry memEntries [ProcMgr_MAX_MEMORY_REGIONS];
    /*!< Configuration of memory regions */
    Atomic                 attachCount;
    /*!< Attach Count */
} ;

/* Defines the ProcMgr_Object type. */
typedef struct ProcMgr_Object_tag ProcMgr_Object;


/* =============================================================================
 *  Globals
 * =============================================================================
 */
/*!
 *  @var    ProcMgr_state
 *
 *  @brief  ProcMgr state object variable
 */
#if !defined(IPC_BUILD_DEBUG)
static
#endif /* if !defined(IPC_BUILD_DEBUG) */
ProcMgr_ModuleObject ProcMgr_state =
{
    .configSize = sizeof (ProcMgr_Config),
    .gateHandle = NULL,
    .defCfg.sysMemMap           = NULL,
    .defInstParams.procHandle   = NULL,
    .defInstParams.loaderHandle = NULL,
    .defInstParams.pwrHandle    = NULL,
    .defInstParams.rstVectorSectionName    = ".Ipc_ResetVector",
    .defAttachParams.bootParams = NULL,
    .defAttachParams.bootMode   = ProcMgr_BootMode_Boot,
};

/* instance params override */
String ProcMgr_ipcCfgParams = NULL;

extern int ipc_notify_event(int event, int arg);

/* =============================================================================
 *  APIs
 * =============================================================================
 */
/*!
 *  @brief      Function to get the default configuration for the ProcMgr
 *              module.
 *
 *              This function can be called by the application to get their
 *              configuration parameter to ProcMgr_setup filled in by the
 *              ProcMgr module with the default parameters. If the user does
 *              not wish to make any change in the default parameters, this API
 *              is not required to be called.
 *
 *  @param      cfg        Pointer to the ProcMgr module configuration structure
 *                         in which the default config is to be returned.
 *
 *  @sa         ProcMgr_setup
 */
Void
ProcMgr_getConfig (ProcMgr_Config * cfg)
{
    GT_1trace (curTrace, GT_ENTER, "ProcMgr_getConfig", cfg);

    GT_assert (curTrace, (cfg != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (cfg == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getConfig",
                             ProcMgr_E_INVALIDARG,
                             "Argument of type (ProcMgr_Config *) passed "
                             "is null!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        /* This sets the refCount variable if not initialized, upper 16 bits are
         * written with module Id to ensure correctness of refCount variable.
         */
        Atomic_cmpmask_and_set (&ProcMgr_state.refCount,
                                ProcMgr_MAKE_MAGICSTAMP(0),
                                ProcMgr_MAKE_MAGICSTAMP(0));

        if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                      ProcMgr_MAKE_MAGICSTAMP(0),
                                      ProcMgr_MAKE_MAGICSTAMP(1))
            == FALSE) {
            Memory_copy (cfg,
                         &ProcMgr_state.cfg,
                         sizeof (ProcMgr_Config));
        }
        else {
            /* (If setup has not yet been called) */
            Memory_copy (cfg,
                         &ProcMgr_state.defCfg,
                         sizeof (ProcMgr_Config));
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "ProcMgr_getConfig");
}


/*!
 *  @brief      Function to setup the ProcMgr module.
 *
 *              This function sets up the ProcMgr module. This function must
 *              be called before any other instance-level APIs can be invoked.
 *              Module-level configuration needs to be provided to this
 *              function. If the user wishes to change some specific config
 *              parameters, then ProcMgr_getConfig can be called to get the
 *              configuration filled with the default values. After this, only
 *              the required configuration values can be changed. If the user
 *              does not wish to make any change in the default parameters, the
 *              application can simply call ProcMgr_setup with NULL parameters.
 *              The default parameters would get automatically used.
 *
 *  @param      cfg   Optional ProcMgr module configuration. If provided as
 *                    NULL, default configuration is used.
 *
 *  @sa         ProcMgr_destroy
 *              GateMutex_create
 */
Int
ProcMgr_setup (ProcMgr_Config * cfg)
{
    Int              status = ProcMgr_S_SUCCESS;
    Error_Block      eb;
    ProcMgr_Config   tmpCfg;

    GT_1trace (curTrace, GT_ENTER, "ProcMgr_setup", cfg);

    Error_init(&eb);

    /* This sets the refCount variable is not initialized, upper 16 bits is
     * written with module Id to ensure correctness of refCount variable.
     */
    Atomic_cmpmask_and_set (&ProcMgr_state.refCount,
                            ProcMgr_MAKE_MAGICSTAMP(0),
                            ProcMgr_MAKE_MAGICSTAMP(0));

    if (   Atomic_inc_return (&ProcMgr_state.refCount)
        != ProcMgr_MAKE_MAGICSTAMP(1u)) {
        status = ProcMgr_S_ALREADYSETUP;
        GT_0trace (curTrace,
                   GT_2CLASS,
                   "ProcMgr Module already initialized!");
    }
    else {
        if (cfg == NULL) {
            ProcMgr_getConfig (&tmpCfg);
            cfg = &tmpCfg;
        }

        /* Create a default gate handle for local module protection. */
        ProcMgr_state.gateHandle = (IGateProvider_Handle)
                              GateMutex_create ((GateMutex_Params *) NULL, &eb);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (ProcMgr_state.gateHandle == NULL) {
            /*! @retval ProcMgr_E_FAIL Failed to create GateMutex! */
            status = ProcMgr_E_FAIL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ProcMgr_setup",
                                 status,
                                 "Failed to create GateMutex!");
            Atomic_set (&ProcMgr_state.refCount,
                        ProcMgr_MAKE_MAGICSTAMP(0));
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            /* Copy the user provided values into the state object. */
            Memory_copy (&ProcMgr_state.cfg,
                         cfg,
                         sizeof (ProcMgr_Config));

            /* Initialize the procHandles array. */
            Memory_set (&ProcMgr_state.procHandles,
                        0,
                        (sizeof (ProcMgr_Handle) * MultiProc_MAXPROCESSORS));

#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_setup", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return (status);
}


/*!
 *  @brief      Function to destroy the ProcMgr module.
 *
 *              Once this function is called, other ProcMgr module APIs, except
 *              for the ProcMgr_getConfig API cannot be called anymore.
 *
 *  @sa         ProcMgr_setup
 *              GateMutex_delete
 */
Int
ProcMgr_destroy (Void)
{
    Int    status = ProcMgr_S_SUCCESS;
    UInt16 i;

    GT_0trace (curTrace, GT_ENTER, "ProcMgr_destroy");

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_destroy",
                             status,
                             "Module was not initialized!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        if (   Atomic_dec_return (&ProcMgr_state.refCount)
            == ProcMgr_MAKE_MAGICSTAMP(0)) {
            /* Check if any ProcMgr instances have not been deleted so far.
             * If not, delete them.
             */
            for (i = 0 ; i < MultiProc_MAXPROCESSORS ; i++) {
                GT_assert (curTrace, (ProcMgr_state.procHandles [i] == NULL));
                if (ProcMgr_state.procHandles [i] != NULL) {
                    ProcMgr_delete (&(ProcMgr_state.procHandles [i]));
                }
            }

            if (ProcMgr_state.gateHandle != NULL) {
                GateMutex_delete ((GateMutex_Handle *)
                                            &(ProcMgr_state.gateHandle));
            }

            /* Free the memory alloacted for memory map in th module struct*/
            if (ProcMgr_state.cfg.sysMemMap  != NULL) {
                if (ProcMgr_state.cfg.sysMemMap->memBlocks != NULL) {

                    Memory_free(NULL,
                                ProcMgr_state.cfg.sysMemMap->memBlocks,
                                (sizeof(Ipc_MemEntry_Block)
                                 * ProcMgr_state.cfg.sysMemMap->numBlocks));
                    Memory_free(NULL,
                                ProcMgr_state.cfg.sysMemMap ,
                                sizeof (Ipc_MemoryMap));
                }
            }

            /* free instance params string */
            if (ProcMgr_ipcCfgParams != NULL) {
                Ptr ptr = ProcMgr_ipcCfgParams;
                Int len = strlen(ptr) + 1;
                Memory_free(NULL, ptr, len);
                ProcMgr_ipcCfgParams = NULL;
            }
            /* Decrease the refCount */
            Atomic_set (&ProcMgr_state.refCount,
                        ProcMgr_MAKE_MAGICSTAMP(0));
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_destroy", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return (status);
}


/*!
 *  @brief      Function to initialize the parameters for the ProcMgr instance.
 *
 *              This function can be called by the application to get their
 *              configuration parameter to ProcMgr_create filled in by the
 *              ProcMgr module with the default parameters.
 *
 *  @param      handle   Handle to the ProcMgr object. If specified as NULL,
 *                       the default global configuration values are returned.
 *  @param      params   Pointer to the ProcMgr instance params structure in
 *                       which the default params is to be returned.
 *
 *  @sa         ProcMgr_create
 */
Void
ProcMgr_Params_init (ProcMgr_Handle handle, ProcMgr_Params * params)
{
    ProcMgr_Object * procMgrHandle = (ProcMgr_Object *) handle;

    GT_2trace (curTrace, GT_ENTER, "ProcMgr_Params_init", handle, params);

    GT_assert (curTrace, (params != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_Params_init",
                             ProcMgr_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if (params == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_Params_init",
                             ProcMgr_E_INVALIDARG,
                             "Argument of type (ProcMgr_Params *) passed "
                             "is null!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        if (handle == NULL) {
            Memory_copy (params,
                         &(ProcMgr_state.defInstParams),
                         sizeof (ProcMgr_Params));
        }
        else {
            /* Return updated ProcMgr instance specific parameters. */
            Memory_copy (params,
                         &(procMgrHandle->params),
                         sizeof (ProcMgr_Params));
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "ProcMgr_Params_init");
}


/*!
 *  @brief      Function to create a ProcMgr object for a specific slave
 *              processor.
 *
 *              This function creates an instance of the ProcMgr module and
 *              returns an instance handle, which is used to access the
 *              specified slave processor. The processor ID specified here is
 *              the ID of the slave processor as configured with the MultiProc
 *              module.
 *              Instance-level configuration needs to be provided to this
 *              function. If the user wishes to change some specific config
 *              parameters, then ProcMgr_Params_init can be called to get the
 *              configuration filled with the default values. After this, only
 *              the required configuration values can be changed. For this
 *              API, the params argument is not optional, since the user needs
 *              to provide some essential values such as loader, PwrMgr and
 *              Processor instances to be used with this ProcMgr instance.
 *
 *  @param      procId   Processor ID represented by this ProcMgr instance
 *  @param      params   ProcMgr instance configuration parameters.
 *
 *  @sa         ProcMgr_delete
 *              Memory_calloc
 */
ProcMgr_Handle
ProcMgr_create (UInt16 procId, const ProcMgr_Params * params)
{
    ProcMgr_Object *       handle = NULL;
    IArg                   key;

    GT_2trace (curTrace, GT_ENTER, "ProcMgr_create", procId, params);

    GT_assert (curTrace, IS_VALID_PROCID (procId));
    GT_assert (curTrace, (params != NULL));
    GT_assert (curTrace, ((params != NULL)) && (params->procHandle != NULL));
    GT_assert (curTrace, ((params != NULL)) && (params->loaderHandle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_create",
                             ProcMgr_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if (!IS_VALID_PROCID (procId)) {
        /*! @retval NULL Function failed */
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_create",
                             ProcMgr_E_INVALIDARG,
                             "Invalid procId specified");
    }
    else if (params == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_create",
                             ProcMgr_E_INVALIDARG,
                             "Invalid params pointer specified");
    }
    else if (params->procHandle == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_create",
                             ProcMgr_E_INVALIDARG,
                             "Invalid procHandle specified in params");
    }
    else if (params->loaderHandle == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_create",
                             ProcMgr_E_INVALIDARG,
                             "Invalid loaderHandle specified in params");
    } else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Enter critical section protection. */
        key = IGateProvider_enter (ProcMgr_state.gateHandle);

        /* Allocate memory for the handle */
        handle = (ProcMgr_Object *) Memory_calloc (NULL,
                                                   sizeof (ProcMgr_Object),
                                                   0, NULL);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (handle == NULL) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ProcMgr_create",
                                 ProcMgr_E_MEMORY,
                                 "Memory allocation failed for handle!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            /* Copy the user provided values into the instance object. */
            Memory_copy (&(handle->params),
                         (Ptr) params,
                         sizeof (ProcMgr_Params));
            handle->procId = procId;
            handle->procHandle   = params->procHandle;
            handle->loaderHandle = params->loaderHandle;
            handle->pwrHandle    = params->pwrHandle;

            handle->maxMemoryRegions = ProcMgr_MAX_MEMORY_REGIONS;
            handle->numMemEntries = 0;
            Memory_set ((Ptr) handle->memEntries, 0,
                    handle->maxMemoryRegions * sizeof(ProcMgr_MappedMemEntry));
            /* Store the ProcMgr handle in the local array. */
            ProcMgr_state.procHandles [procId] = (ProcMgr_Handle) handle;
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Leave critical section protection. */
        IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_create", handle);

    /*! @retval Valid-Handle Operation successful */
    return (ProcMgr_Handle) handle;
}


/*!
 *  @brief      Function to delete a ProcMgr object for a specific slave
 *              processor.
 *
 *              Once this function is called, other ProcMgr instance level APIs
 *              that require the instance handle cannot be called.
 *
 *  @param      handlePtr     Pointer to Handle to the ProcMgr object
 *
 *  @sa         ProcMgr_create
 *              Memory_free
 */
Int
ProcMgr_delete (ProcMgr_Handle * handlePtr)
{
    Int              status = ProcMgr_S_SUCCESS;
    ProcMgr_Object * handle;
    IArg             key;

    GT_1trace (curTrace, GT_ENTER, "ProcMgr_delete", handlePtr);

    GT_assert (curTrace, (handlePtr != NULL));
    GT_assert (curTrace, ((handlePtr != NULL) && (*handlePtr != NULL)));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_delete",
                             status,
                             "Module was not initialized!");
    }
    else if (handlePtr == NULL) {
        /*! @retval ProcMgr_E_INVALIDARG Invalid NULL handlePtr pointer
                                         specified*/
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_delete",
                             status,
                             "Invalid NULL handlePtr pointer specified");
    }
    else if (*handlePtr == NULL) {
        /*! @retval ProcMgr_E_HANDLE Invalid NULL *handlePtr specified */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_delete",
                             status,
                             "Invalid NULL *handlePtr specified");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        handle = (ProcMgr_Object *) (*handlePtr);
        /* Enter critical section protection. */
        key = IGateProvider_enter (ProcMgr_state.gateHandle);

        GT_assert (curTrace, IS_VALID_PROCID (handle->procId));
        if (!(IS_VALID_PROCID (handle->procId))) {
            /* Don't set the procHandles[handle->procId] as null but clean up
             * handle */
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ProcMgr_delete",
                                 status,
                                 "Invalid ProcId, but freeing up the Handle");
        }
        else {
            /* Clear the ProcMgr handle in the local array. */
            ProcMgr_state.procHandles [handle->procId] = NULL;
        }
        Memory_free (NULL, handle, sizeof (ProcMgr_Object));
        *handlePtr = NULL;

        /* Leave critical section protection. */
        IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_delete", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successfully completed. */
    return status;
}


/* Function to open a handle to an existing ProcMgr object handling the
 * procId.
 */
Int
ProcMgr_open (ProcMgr_Handle * handlePtr, UInt16 procId)
{
    Int    status = ProcMgr_S_SUCCESS;
    IArg   key;

    GT_2trace (curTrace, GT_ENTER, "ProcMgr_open", handlePtr, procId);

    GT_assert (curTrace, (handlePtr != NULL));
    GT_assert (curTrace, IS_VALID_PROCID (procId));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_open",
                             status,
                             "Module was not initialized!");
    }
    else if (handlePtr == NULL) {
        /*! @retval ProcMgr_E_INVALIDARG Invalid NULL handlePtr pointer
                                         specified*/
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_open",
                             status,
                             "Invalid NULL handlePtr pointer specified");
    }
    else if (!IS_VALID_PROCID (procId)) {
        *handlePtr = NULL;
        /*! @retval ProcMgr_E_INVALIDARG Invalid procId specified */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_open",
                             status,
                             "Invalid procId specified");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Enter critical section protection. */
        key = IGateProvider_enter (ProcMgr_state.gateHandle);
        /* Return handle in the local array. */
        *handlePtr = ProcMgr_state.procHandles [procId];
        /* Leave critical section protection. */
        IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_open", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return (status);
}


/* Function to close this handle to the ProcMgr instance. */
Int
ProcMgr_close (ProcMgr_Handle * handlePtr)
{
    Int status = ProcMgr_S_SUCCESS;

    GT_1trace (curTrace, GT_ENTER, "ProcMgr_close", handlePtr);

    GT_assert (curTrace, (handlePtr != NULL));
    GT_assert (curTrace, ((handlePtr != NULL) && (*handlePtr != NULL)));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_close",
                             status,
                             "Module was not initialized!");
    }
    else if (handlePtr == NULL) {
        /*! @retval ProcMgr_E_INVALIDARG Invalid NULL handlePtr pointer
                                         specified*/
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_close",
                             status,
                             "Invalid NULL handlePtr pointer specified");
    }
    else if (*handlePtr == NULL) {
        /*! @retval ProcMgr_E_HANDLE Invalid NULL *handlePtr specified */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_close",
                             status,
                             "Invalid NULL *handlePtr specified");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Nothing to be done for closing the handle. */
        *handlePtr = NULL;
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_close", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return (status);
}


/* Function to initialize the parameters for the ProcMgr attach function. */
Void
ProcMgr_getAttachParams (ProcMgr_Handle handle, ProcMgr_AttachParams * params)
{
    ProcMgr_Object * procMgrHandle = (ProcMgr_Object *) handle ;

    GT_2trace (curTrace, GT_ENTER, "ProcMgr_getAttachParams", handle, params);

    GT_assert (curTrace, (params != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getAttachParams",
                             ProcMgr_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if (params == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getAttachParams",
                             ProcMgr_E_INVALIDARG,
                             "Argument of type (ProcMgr_AttachParams *) passed "
                             "is null!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        if (handle == NULL) {
            Memory_copy (params,
                         &(ProcMgr_state.defAttachParams),
                         sizeof (ProcMgr_AttachParams));
        }
        else {
            /* Return updated ProcMgr instance specific Start parameters. */
            Memory_copy (params,
                         &(procMgrHandle->attachParams),
                         sizeof (ProcMgr_AttachParams));
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "ProcMgr_getAttachParams");
}


/* Function to attach the client to the specified slave and also initialize the
 * slave (if required).
 */
Int
ProcMgr_attach (ProcMgr_Handle handle, ProcMgr_AttachParams * params)
{
    Int                      status        = ProcMgr_S_SUCCESS;
    ProcMgr_Object *         procMgrHandle = (ProcMgr_Object *) handle ;
    IArg                     key;
    ProcMgr_AttachParams     tmpParams;
    Processor_AttachParams   procAttachParams;
    Loader_AttachParams      loaderAttachParams;
    PwrMgr_AttachParams      pwrAttachParams;
    UInt32                   i;
    UInt32                   dstAddr;
    UInt32                   srcAddr;
    ProcMgr_AddrInfo *       me;
    ProcMgr_AddrInfo         aInfo;

    GT_2trace (curTrace, GT_ENTER, "ProcMgr_attach", handle, params);

    GT_assert (curTrace, (handle != NULL));

    if (params == NULL) {
        ProcMgr_getAttachParams (handle, &tmpParams);
        params = &tmpParams;
    }

    GT_assert (curTrace, (params->bootMode < ProcMgr_BootMode_EndValue));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_attach",
                             status,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_attach",
                             status,
                             "Invalid handle specified");
    }
    else if (params->bootMode >= ProcMgr_BootMode_EndValue) {
        /*! @retval ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_create",
                             status,
                             "Invalid bootMode specified in params");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        Atomic_cmpmask_and_set(&procMgrHandle->attachCount,
                               ProcMgr_MAKE_MAGICSTAMP(0),
                               ProcMgr_MAKE_MAGICSTAMP(0));
        if (Atomic_inc_return(&procMgrHandle->attachCount) != ProcMgr_MAKE_MAGICSTAMP(1))
            return 1;

        /* Enter critical section protection. */
        key = IGateProvider_enter (ProcMgr_state.gateHandle);
        /* Copy the user provided values into the instance object. */
        Memory_copy (&(procMgrHandle->attachParams),
                     params,
                     sizeof (ProcMgr_AttachParams));

        /* Attach to the specified PwrMgr instance. */
        pwrAttachParams.params = params;
        status = PwrMgr_attach (procMgrHandle->pwrHandle,
                                &pwrAttachParams);

#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ProcMgr_attach",
                                 status,
                                 "PwrMgr_attach failed!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            /* Attach to the specified Processor instance. */
            procAttachParams.pmHandle = handle;
            procAttachParams.params = params;
            procAttachParams.numMemEntries = 0; /* Return parameter. */

            /* Pass the system memory map to Processor to update the
             * translation table */

            procAttachParams.sysMemMap = ProcMgr_state.cfg.sysMemMap;

            status = Processor_attach (procMgrHandle->procHandle,
                                       &procAttachParams);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "ProcMgr_attach",
                                     status,
                                     "Processor_attach failed!");
            }
            else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                /* Since the processor is attached now, we can safely map the
                 * entries
                 */
                for (i = 0;
                     (i < procAttachParams.numMemEntries) && (status >= 0);
                     i++) {
                    me = &procAttachParams.memEntries [i];
                    srcAddr = me->addr [ProcMgr_AddrType_SlaveVirt];
                    dstAddr = me->addr [ProcMgr_AddrType_MasterPhys];
                    /* This translation is redundant */
                    /*status = Processor_translateAddr (procMgrHandle->procHandle,
                                                      &dstAddr,
                                                      srcAddr);*/
#if !defined(IPC_BUILD_OPTIMIZE)
                    if (status < 0) {
                        GT_setFailureReason (curTrace,
                                             GT_4CLASS,
                                             "ProcMgr_attach",
                                             status,
                                             "Processor_translateAddr failed!");
                    }
                    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                        aInfo.addr [ProcMgr_AddrType_SlaveVirt]  = srcAddr;
                        aInfo.addr [ProcMgr_AddrType_MasterPhys] = dstAddr;
                        aInfo.isCached = me->isCached;
                        aInfo.size = me->size;

                        status = _ProcMgr_map (handle, me->mapMask, &aInfo,
                                               ProcMgr_AddrType_MasterPhys);

#if !defined(IPC_BUILD_OPTIMIZE)
                        if (status < 0) {
                            GT_setFailureReason (curTrace,
                                                 GT_4CLASS,
                                                 "ProcMgr_attach",
                                                 status,
                                                 "_ProcMgr_map failed!");
                        }
                    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                }
                if (status >= 0) {
                    /* Attach to the specified Loader instance. */
                    loaderAttachParams.params     = params;
                    loaderAttachParams.pmHandle   = handle;
                    loaderAttachParams.procHandle = procMgrHandle->procHandle;
                    loaderAttachParams.procArch = procAttachParams.procArch;
                    status = Loader_attach (procMgrHandle->loaderHandle,
                                            &loaderAttachParams);
#if !defined(IPC_BUILD_OPTIMIZE)
                    if (status < 0) {
                        GT_setFailureReason (curTrace,
                                             GT_4CLASS,
                                             "ProcMgr_attach",
                                             status,
                                             "Loader_attach failed!");
                    }
                    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                        /* TBD: Check registered processors and do callback for
                         *      state change.
                         */
#if !defined(IPC_BUILD_OPTIMIZE)
                    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                }
#if !defined(IPC_BUILD_OPTIMIZE)
            }
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        /* Leave critical section protection. */
        IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_attach", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return (status);
}


/* Function to detach the client from the specified slave and also finalze the
 * slave (if required).
 */
Int
ProcMgr_detach (ProcMgr_Handle handle)
{
    Int                      status        = ProcMgr_S_SUCCESS;
    Int                      tmpStatus     = ProcMgr_S_SUCCESS;
    ProcMgr_Object *         procMgrHandle = (ProcMgr_Object *) handle;
    IArg                     key;
    UInt32                   i;
    ProcMgr_MappedMemEntry * me;

    GT_1trace (curTrace, GT_ENTER, "ProcMgr_detach", handle);

    GT_assert (curTrace, (handle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_detach",
                             status,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_detach",
                             status,
                             "Invalid handle specified");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        if (!(Atomic_dec_return(&procMgrHandle->attachCount) == \
            ProcMgr_MAKE_MAGICSTAMP(0)))
            return 1;

        /* Enter critical section protection. */
        key = IGateProvider_enter (ProcMgr_state.gateHandle);

        /* Detach from the Loader. */
        tmpStatus = Loader_detach (procMgrHandle->loaderHandle);
#if !defined(IPC_BUILD_OPTIMIZE)
        if ((tmpStatus < 0) && (status >= 0)) {
            status = tmpStatus;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ProcMgr_detach",
                                 status,
                                 "Loader_detach failed!");
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        /* since the processor is in stopped state we can safely unmap the
         * entries
         */
        for (i = 0; i < procMgrHandle->maxMemoryRegions; i++) {
            me = &procMgrHandle->memEntries [i];
            if (me->inUse == TRUE) {
                status = _ProcMgr_unmap (handle, me->mapMask, &me->info,
                                          me->srcAddrType);
#if !defined(IPC_BUILD_OPTIMIZE)
                if (status < 0) {
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "ProcMgr_detach",
                                         status,
                                         "_ProcMgr_unmap failed!");
                }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            }
        }

        /* Detach from the Processor. */
        tmpStatus = Processor_detach (procMgrHandle->procHandle);
#if !defined(IPC_BUILD_OPTIMIZE)
        if ((tmpStatus < 0) && (status >= 0)) {
            status = tmpStatus;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ProcMgr_detach",
                                 status,
                                 "Processor_detach failed!");
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        /* Detach from the PwrMgr. */
        tmpStatus = PwrMgr_detach (procMgrHandle->pwrHandle);
#if !defined(IPC_BUILD_OPTIMIZE)
        if ((tmpStatus < 0) && (status >= 0)) {
            status = tmpStatus;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ProcMgr_detach",
                                 status,
                                 "PwrMgr_detach failed!");
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* TBD: Check registered processors and do callback for state
         *      change.
         */

        /* Leave critical section protection. */
        IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_detach", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return (status);
}


/* Function to load the specified slave executable on the slave Processor. */
Int
ProcMgr_load (ProcMgr_Handle handle,
              String         imagePath,
              UInt32         argc,
              String *       argv,
              Ptr            params,
              UInt32 *       fileId)
{
    Int                      status        = ProcMgr_S_SUCCESS;
    ProcMgr_Object *         procMgrHandle = (ProcMgr_Object *) handle;
    IArg                     key;

    GT_5trace (curTrace, GT_ENTER, "ProcMgr_load",
               handle, imagePath, argc, argv, params);

    GT_assert (curTrace, (handle != NULL));
    GT_assert (curTrace, (fileId != NULL));
    /* imagePath may be NULL if a non-file based loader is used. In that case,
     * loader-specific params will contain the required information.
     */

    GT_assert (curTrace,
               (   ((argc == 0) && (argv == NULL))
                || ((argc != 0) && (argv != NULL))));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_load",
                             status,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval  ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_load",
                             status,
                             "Invalid handle specified");
    }
    else if (   ((argc == 0) && (argv != NULL))
             || ((argc != 0) && (argv == NULL))) {
        /*! @retval  ProcMgr_E_INVALIDARG Invalid argument */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_load",
                             status,
                             "Invalid argc/argv values specified");
    }
    else if (fileId == NULL) {
        /*! @retval  ProcMgr_E_INVALIDARG Invalid argument */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_load",
                             status,
                             "Invalid fileId pointer specified");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Enter critical section protection. */
        key = IGateProvider_enter (ProcMgr_state.gateHandle);

        GT_assert (curTrace, (procMgrHandle->loaderHandle != NULL));
        status = Loader_load (procMgrHandle->loaderHandle,
                              imagePath,
                              argc,
                              argv,
                              params,
                              fileId);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ProcMgr_load",
                                 status,
                                 "Failed to load file on the slave!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            /* Need to keep this for future calls to ELF loader fxns! */
            procMgrHandle->fileId = *fileId;
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        /* Leave critical section protection. */
        IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_load", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return status;
}


/* Function to unload the previously loaded file on the slave processor.
 * The fileId received from the load function must be passed to this
 * function.
 */
Int
ProcMgr_unload (ProcMgr_Handle handle, UInt32 fileId)
{
    Int                      status        = ProcMgr_S_SUCCESS;
    Int                      tmpStatus     = ProcMgr_S_SUCCESS;
    ProcMgr_Object *         procMgrHandle = (ProcMgr_Object *) handle;
    IArg                     key;

    GT_2trace (curTrace, GT_ENTER, "ProcMgr_unload", handle, fileId);

    GT_assert (curTrace, (handle != NULL));
    /* Cannot check for fileId because it is loader dependent. */

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_unload",
                             status,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval  ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_unload",
                             status,
                             "Invalid handle specified");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Enter critical section protection. */
        key = IGateProvider_enter (ProcMgr_state.gateHandle);

        tmpStatus = Loader_unload (procMgrHandle->loaderHandle, fileId);
        if ((tmpStatus < 0) && (status >= 0)) {
            status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ProcMgr_unload",
                                 status,
                                 "Failed to unload file from the slave!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }

        /* Clear the file ID of loaded static executable. */
        procMgrHandle->fileId = (UInt32) 0xFFFFFFFF;

        /* Leave critical section protection. */
        IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_unload", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return status;
}


/* Function to initialize the parameters for the ProcMgr start function. */
Void
ProcMgr_getStartParams (ProcMgr_Handle handle, ProcMgr_StartParams * params)
{
    ProcMgr_Object * procMgrHandle = (ProcMgr_Object *) handle ;

    GT_2trace (curTrace, GT_ENTER, "ProcMgr_getStartParams", handle, params);

    GT_assert (curTrace, (params != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getStartParams",
                             ProcMgr_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if (params == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getStartParams",
                             ProcMgr_E_INVALIDARG,
                             "Argument of type (ProcMgr_StartParams *) passed "
                             "is null!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        if (handle == NULL) {
            Memory_copy (params,
                         &(ProcMgr_state.defStartParams),
                         sizeof (ProcMgr_StartParams));
        }
        else {
            /* Return updated ProcMgr instance specific Start parameters. */
            Memory_copy (params,
                         &(procMgrHandle->startParams),
                         sizeof (ProcMgr_StartParams));
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "ProcMgr_getStartParams");
}


/* Function to starts execution of the loaded code on the slave from the
 * starting point specified in the slave executable loaded earlier by call to
 * ProcMgr_load ().
 */
Int
ProcMgr_start (ProcMgr_Handle handle, ProcMgr_StartParams * params)
{
    Int                   status         = ProcMgr_S_SUCCESS;
    ProcMgr_Object *      procMgrHandle  = (ProcMgr_Object *) handle;
    IArg                  key;
    ProcMgr_StartParams   tmpParams;
    Processor_StartParams procParams;
    UInt32                entryPt = 0;

    GT_2trace (curTrace, GT_ENTER, "ProcMgr_start", handle, params);

    GT_assert (curTrace, (handle != NULL));

    if (params == NULL) {
        ProcMgr_getStartParams (handle, &tmpParams);
        params = &tmpParams;
    }

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_start",
                             status,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval  ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_start",
                             status,
                             "Invalid handle specified");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Start the slave processor running. */
        if (procMgrHandle->attachParams.bootMode == ProcMgr_BootMode_Boot) {
            status = Loader_getEntryPt (procMgrHandle->loaderHandle,
                                        procMgrHandle->fileId,
                                        &entryPt);
        }

#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ProcMgr_start",
                                 status,
                                 "Loader_getEntryPt failed");
        }
        else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
            /* Enter critical section protection. */
            key = IGateProvider_enter (ProcMgr_state.gateHandle);

            /* Copy the user provided values into the instance object. */
            Memory_copy (&(procMgrHandle->startParams),
                         params,
                         sizeof (ProcMgr_StartParams));

            procParams.params = params;
            status = Processor_start (procMgrHandle->procHandle,
                                      entryPt,
                                      &procParams);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                    GT_4CLASS,
                                    "ProcMgr_start",
                                    status,
                                    "Failed to get start the slave "
                                    "processor!");
            }
            else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                /* TBD: Check registered processors and do callback for
                 *      state change.
                 */
                //ipc_notify_event(IPC_PROC_START, params->procId);
#if !defined(IPC_BUILD_OPTIMIZE)
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

            /* Leave critical section protection. */
            IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
        }
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_start", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return status;
}


/* Function to stop execution of the slave Processor. */
Int
ProcMgr_stop (ProcMgr_Handle handle)
{
    Int                  status         = ProcMgr_S_SUCCESS;
    ProcMgr_Object *     procMgrHandle  = (ProcMgr_Object *) handle;
    IArg                 key;

    GT_1trace (curTrace, GT_ENTER, "ProcMgr_stop", handle);

    GT_assert (curTrace, (handle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_stop",
                             status,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval  ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_stop",
                             status,
                             "Invalid handle specified");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        /* Enter critical section protection. */
        key = IGateProvider_enter (ProcMgr_state.gateHandle);

        /* Stop the slave processor. */
        status = Processor_stop (procMgrHandle->procHandle);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ProcMgr_stop",
                                 status,
                                 "Failed to get stop the slave processor!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            /* TBD: Check registered processors and do callback for state
             *      change.
             */
            //ipc_notify_event(IPC_PROC_STOP, procMgrHandle->procId);
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        /* Leave critical section protection. */
        IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_stop", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return status;
}


/* Function to get the current state of the slave Processor as maintained on
 * the master Processor state machine.
 */
ProcMgr_State
ProcMgr_getState (ProcMgr_Handle handle)
{
    ProcMgr_Object *     procMgrHandle  = (ProcMgr_Object *) handle;
    ProcMgr_State        state          = ProcMgr_State_Unknown;
    IArg                 key;

    GT_1trace (curTrace, GT_ENTER, "ProcMgr_getState", handle);

    GT_assert (curTrace, (handle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getState",
                             ProcMgr_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /* No status set here since this function does not return status. */
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getState",
                             ProcMgr_E_HANDLE,
                             "Invalid handle specified");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Enter critical section protection. */
        key = IGateProvider_enter (ProcMgr_state.gateHandle);

        /* Get the processor state. */
        state = Processor_getState (procMgrHandle->procHandle);

        /* Leave critical section protection. */
        IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_getState", state);

    /*! @retval Processor state */
    return state;
}

/* Function to set the current state of the slave Processor as maintained on
 * the master Processor state machine.
 */
Void
ProcMgr_setState (ProcMgr_Handle handle, ProcMgr_State state)
{
    ProcMgr_Object *     procMgrHandle  = (ProcMgr_Object *) handle;
    Int                  status = ProcMgr_S_SUCCESS;
    IArg                 key;

    GT_1trace (curTrace, GT_ENTER, "ProcMgr_setState", handle);

    GT_assert (curTrace, (handle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_setState",
                             ProcMgr_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /* No status set here since this function does not return status. */
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_setState",
                             ProcMgr_E_HANDLE,
                             "Invalid handle specified");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Enter critical section protection. */
        key = IGateProvider_enter (ProcMgr_state.gateHandle);

        /* Get the processor state. */
        Processor_setState (procMgrHandle->procHandle, state);

        /* Leave critical section protection. */
        IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_setState", status);

    /*! @retval None */
    return;
}

/* Function to read from the slave Processor's memory space. */
Int
ProcMgr_read (ProcMgr_Handle handle,
              UInt32         procAddr,
              UInt32 *       numBytes,
              Ptr            buffer)
{
    Int              status         = ProcMgr_S_SUCCESS;
    ProcMgr_Object * procMgrHandle  = (ProcMgr_Object *) handle;
    IArg             key;
    Ptr              addr;

    GT_4trace (curTrace, GT_ENTER, "ProcMgr_read",
               handle, procAddr, numBytes, buffer);

    GT_assert (curTrace, (handle   != NULL));
    GT_assert (curTrace, (numBytes != NULL));
    GT_assert (curTrace, (buffer   != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_read",
                             status,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval  ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_read",
                             status,
                             "Invalid handle specified");
    }
    else if (numBytes == NULL) {
        /*! @retval  ProcMgr_E_INVALIDARG Invalid value NULL provided for
                     argument numBytes */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                           GT_4CLASS,
                           "ProcMgr_read",
                           status,
                           "Invalid value NULL provided for argument numBytes");
    }
    else if (buffer == NULL) {
        /*! @retval  ProcMgr_E_INVALIDARG Invalid value NULL provided for
                     argument buffer */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_read",
                             status,
                             "Invalid value NULL provided for argument buffer");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Check if the address is already mapped */
        status = ProcMgr_translateAddr (handle,
                                        (Ptr *) &addr,
                                        ProcMgr_AddrType_MasterKnlVirt,
                                        (Ptr) procAddr,
                                        ProcMgr_AddrType_SlaveVirt);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ProcMgr_read",
                                 status,
                                 "Address is not mapped!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            /* Enter critical section protection. */
            key = IGateProvider_enter (ProcMgr_state.gateHandle);

            /* Read from the slave processor's memory. */
            status = Processor_read (procMgrHandle->procHandle,
                                     (UInt32)addr,
                                     numBytes,
                                     buffer);
            /* Leave critical section protection. */
            IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                               GT_4CLASS,
                               "ProcMgr_read",
                               status,
                               "Failed to get read from slave processor's memory!");
            }
        }
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_read", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return status;
}


/* Function to read from the slave Processor's memory space. */
Int
ProcMgr_write (ProcMgr_Handle handle,
               UInt32         procAddr,
               UInt32 *       numBytes,
               Ptr            buffer)
{
    Int              status         = ProcMgr_S_SUCCESS;
    ProcMgr_Object * procMgrHandle  = (ProcMgr_Object *) handle;
    IArg             key;
    Ptr              addr;

    GT_4trace (curTrace, GT_ENTER, "ProcMgr_write",
               handle, procAddr, numBytes, buffer);

    GT_assert (curTrace, (handle   != NULL));
    GT_assert (curTrace, (numBytes != NULL));
    GT_assert (curTrace, (buffer   != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_write",
                             status,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval  ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_write",
                             status,
                             "Invalid handle specified");
    }
    else if (numBytes == NULL) {
        /*! @retval  ProcMgr_E_INVALIDARG Invalid value NULL provided for
                     argument numBytes */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                           GT_4CLASS,
                           "ProcMgr_write",
                           status,
                           "Invalid value NULL provided for argument numBytes");
    }
    else if (buffer == NULL) {
        /*! @retval  ProcMgr_E_INVALIDARG Invalid value NULL provided for
                     argument buffer */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_write",
                             status,
                             "Invalid value NULL provided for argument buffer");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Check if the address is already mapped */
        status = ProcMgr_translateAddr (handle,
                                        (Ptr *) &addr,
                                        ProcMgr_AddrType_MasterKnlVirt,
                                        (Ptr) procAddr,
                                        ProcMgr_AddrType_SlaveVirt);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ProcMgr_read",
                                 status,
                                 "Address is not mapped!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            /* Enter critical section protection. */
            key = IGateProvider_enter (ProcMgr_state.gateHandle);

            /* Write into the slave processor's memory. */
            status = Processor_write (procMgrHandle->procHandle,
                                      (UInt32)addr,
                                      numBytes,
                                      buffer);
            /* Leave critical section protection. */
            IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "ProcMgr_write",
                              status,
                              "Failed to get write into slave processor's memory!");
            }
        }
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_write", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return status;
}


/* Function that provides a hook for performing device dependent operations on
 * the slave Processor.
 */
Int
ProcMgr_control (ProcMgr_Handle handle, Int32 cmd, Ptr arg)
{
    Int              status         = ProcMgr_S_SUCCESS;
    ProcMgr_Object * procMgrHandle  = (ProcMgr_Object *) handle;
    IArg             key;

    GT_3trace (curTrace, GT_ENTER, "ProcMgr_control", handle, cmd, arg);

    GT_assert (curTrace, (handle != NULL));
    /* cmd and arg can be 0/NULL, so cannot check for validity. */

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_control",
                             status,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval  ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_control",
                             status,
                             "Invalid handle specified");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Enter critical section protection. */
        key = IGateProvider_enter (ProcMgr_state.gateHandle);

        /* Perform device-dependent control operation. */
        status = Processor_control (procMgrHandle->procHandle, cmd, arg);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                      GT_4CLASS,
                      "ProcMgr_control",
                      status,
                      "Failed to perform device-dependent control operation.!");
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Leave critical section protection. */
        IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_control", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return status;
}


/* Function to translate between two types of address spaces. */
Int
ProcMgr_translateAddr (ProcMgr_Handle   handle,
                       Ptr *            dstAddr,
                       ProcMgr_AddrType dstAddrType,
                       Ptr              srcAddr,
                       ProcMgr_AddrType srcAddrType)
{
    Int                      status         = ProcMgr_S_SUCCESS;
    ProcMgr_Object *         procMgrHandle  = (ProcMgr_Object *) handle;
    IArg                     key;
    UInt32                   fmAddrBase      = (UInt32) NULL;
    UInt32                   toAddrBase      = (UInt32) NULL;
    Bool                     found           = FALSE;
    ProcMgr_MappedMemEntry * me;
    UInt32                   i;
    UInt32                   mapBit;

    GT_5trace (curTrace, GT_ENTER, "ProcMgr_translateAddr",
               handle, dstAddr, dstAddrType, srcAddr, srcAddrType);

    GT_assert (curTrace, (handle        != NULL));
    GT_assert (curTrace, (dstAddr       != NULL));
    GT_assert (curTrace, (dstAddrType   < ProcMgr_AddrType_EndValue));
    GT_assert (curTrace, (srcAddrType   < ProcMgr_AddrType_EndValue));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_translateAddr",
                             status,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval  ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_translateAddr",
                             status,
                             "Invalid handle specified");
    }
    else if (dstAddr == NULL) {
        /*! @retval  ProcMgr_E_INVALIDARG Invalid value NULL provided for
                     argument dstAddr */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                            GT_4CLASS,
                            "ProcMgr_translateAddr",
                            status,
                            "Invalid value NULL provided for argument dstAddr");
    }
    else if (dstAddrType >= ProcMgr_AddrType_EndValue) {
        /*! @retval  ProcMgr_E_INVALIDARG Invalid value provided for
                     argument dstAddrType */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_translateAddr",
                             status,
                             "Invalid value provided for argument dstAddrType");
    }
    else if (srcAddrType >= ProcMgr_AddrType_EndValue) {
        /*! @retval  ProcMgr_E_INVALIDARG Invalid value provided for
                     argument srcAddrType */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_translateAddr",
                             status,
                             "Invalid value provided for argument srcAddrType");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* compute map bit if looking for a virtual address */
        if (dstAddrType == ProcMgr_AddrType_MasterKnlVirt) {
            mapBit = ProcMgr_MASTERKNLVIRT;
        }
        else if (dstAddrType == ProcMgr_AddrType_MasterUsrVirt) {
            mapBit = ProcMgr_MASTERUSRVIRT;
        }
        else if (dstAddrType == ProcMgr_AddrType_SlaveVirt) {
            mapBit = ProcMgr_SLAVEVIRT;
        }
        else {
            mapBit = 0;
        }

        /* Enter critical section protection. */
        key = IGateProvider_enter (ProcMgr_state.gateHandle);

        /* Translate the address. */
        for (i = 0; i < procMgrHandle->maxMemoryRegions; i++) {
            me = &procMgrHandle->memEntries [i];
            if (me->inUse == TRUE && (srcAddrType == me->srcAddrType)) {

                /* skip entry if virtual address not mapped */
                if ((mapBit > 0) && ((me->mapMask & mapBit) == 0)) {
                    continue;
                }

                /* check if entry maps source address */
                fmAddrBase = me->info.addr [srcAddrType];
                toAddrBase = me->info.addr [dstAddrType];
                if (IS_RANGE_VALID ((UInt32) srcAddr,
                                    fmAddrBase,
                                    (fmAddrBase + me->info.size))) {
                    found = TRUE;
                    *dstAddr = (Ptr)(((UInt32)srcAddr-fmAddrBase) + toAddrBase);
                    break;
                }
            }
        }

        /* This check must not be removed even with build optimize. */
        if (found == FALSE) {
            if (   (srcAddrType == ProcMgr_AddrType_SlaveVirt)
                && (dstAddrType == ProcMgr_AddrType_MasterPhys)) {
                status = Processor_translateAddr (procMgrHandle->procHandle,
                                                  (UInt32 *) dstAddr,
                                                  (UInt32) srcAddr);
                if (status < 0) {
                    /*! @retval ProcMgr_E_TRANSLATE Failed to translate address.
                     */
                    status = ProcMgr_E_TRANSLATE;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "ProcMgr_translateAddr",
                                         status,
                                         "Processor_translateAddr failed");
                }
            }
            else {
                /*! @retval ProcMgr_E_TRANSLATE Failed to translate address. */
                status = ProcMgr_E_TRANSLATE;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "ProcMgr_translateAddr",
                                     status,
                                     "Failed to translate address");
            }
        }
        else {
            GT_2trace (curTrace,
                       GT_1CLASS,
                       "    ProcMgr_translateAddr: srcAddr [0x%x] "
                       "dstAddr [0x%x]",
                       srcAddr,
                      *dstAddr);
        }
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ProcMgr_translateAddr",
                                 status,
                                 "Failed to translate address!");
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Leave critical section protection. */
        IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_translateAddr", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return status;
}


/* Function that gets the slave address corresponding to a symbol within an
 * executable currently loaded on the slave Processor.
 */
Int
ProcMgr_getSymbolAddress (ProcMgr_Handle handle,
                          UInt32         fileId,
                          String         symbolName,
                          UInt32 *       symValue)
{
    Int              status         = ProcMgr_S_SUCCESS;
    ProcMgr_Object * procMgrHandle  = (ProcMgr_Object *) handle;
    IArg             key;

    GT_4trace (curTrace, GT_ENTER, "ProcMgr_getSymbolAddress",
               handle, fileId, symbolName, symValue);

    GT_assert (curTrace, (handle      != NULL));
    /* fileId may be 0, so no check for fileId. */
    GT_assert (curTrace, (symbolName  != NULL));
    GT_assert (curTrace, (symValue    != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getSymbolAddress",
                             status,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval  ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getSymbolAddress",
                             status,
                             "Invalid handle specified");
    }
    else if (symbolName == NULL) {
        /*! @retval  ProcMgr_E_INVALIDARG Invalid value NULL provided for
                     argument symbolName */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                         GT_4CLASS,
                         "ProcMgr_getSymbolAddress",
                         status,
                         "Invalid value NULL provided for argument symbolName");
    }
    else if (symValue == NULL) {
        /*! @retval  ProcMgr_E_INVALIDARG Invalid value NULL provided for
                     argument symValue */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                         GT_4CLASS,
                         "ProcMgr_getSymbolAddress",
                         status,
                         "Invalid value NULL provided for argument symValue");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Enter critical section protection. */
        key = IGateProvider_enter (ProcMgr_state.gateHandle);

        /* Map to host address space. */
        status = Loader_getSymbolAddress (procMgrHandle->loaderHandle,
                                          fileId,
                                          symbolName,
                                          symValue);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ProcMgr_getSymbolAddress",
                                 status,
                                 "Failed to get symbol address!");
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Leave critical section protection. */
        IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_getSymbolAddress", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return status;
}


/* Function that maps the specified slave address to master address space. */
Int
ProcMgr_map (ProcMgr_Handle     handle,
             ProcMgr_MapMask    mapType,
             ProcMgr_AddrInfo * addrInfo,
             ProcMgr_AddrType   srcAddrType)
{
    Int    status = ProcMgr_S_SUCCESS;
    IArg   key    = 0;

    GT_4trace (curTrace, GT_ENTER, "ProcMgr_map",
               handle, mapType, addrInfo, srcAddrType);

    GT_assert (curTrace, (handle   != NULL));
#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_map",
                             status,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval  ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_map",
                             status,
                             "Invalid handle specified");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Enter critical section protection. */
        key = IGateProvider_enter (ProcMgr_state.gateHandle);
        status = _ProcMgr_map (handle, mapType, addrInfo, srcAddrType);
        IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_map", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return status;
}

/*!
 *  @brief      Function to copy memory map passed by user.
 *
 */
Void _ProcMgr_configSysMap(ProcMgr_Config * cfg)
{
    GT_1trace(curTrace, GT_ENTER, "_ProcMgr_configSysMap: cfg=0x%x", cfg);

    /* Copy the user provided values into the state object.
     * Since this code is in kernel side we should be careful when this function
     * is called from two different processes from user side and we should not
     * overwrite the existing memory map. If map already exists we should
     * verify the map and it should match with the one already programmed
     */

    if (ProcMgr_state.cfg.sysMemMap == NULL) {
        ProcMgr_state.cfg.sysMemMap = Memory_calloc(NULL,
            (sizeof(Ipc_MemoryMap)), 0u, NULL);

        GT_assert(curTrace, (ProcMgr_state.cfg.sysMemMap != NULL));

        memcpy(ProcMgr_state.cfg.sysMemMap, cfg->sysMemMap,
            sizeof(Ipc_MemoryMap));

        if (cfg->sysMemMap->numBlocks > 0) {
            ProcMgr_state.cfg.sysMemMap->memBlocks = Memory_calloc(NULL,
                (sizeof(Ipc_MemEntry_Block) * cfg->sysMemMap->numBlocks),
                0u, NULL);
            memcpy(ProcMgr_state.cfg.sysMemMap->memBlocks,
               cfg->sysMemMap->memBlocks,
               (sizeof(Ipc_MemEntry_Block) * cfg->sysMemMap->numBlocks));
        }
    }
    else {
        /* TO DO : If the memory map is already present verify with the entries
         *         with existing one
         */
    }

    GT_1trace (curTrace, GT_LEAVE, "_ProcMgr_configSysMap", cfg);
}

/*!
 *  @brief      Function to copy instance params overrides passed by user.
 *
 */
Void _ProcMgr_saveParams(String params, Int len)
{
    GT_2trace (curTrace, GT_ENTER, "_ProcMgr_saveParams", params, len);

    /* free params string if already configured */
    if (ProcMgr_ipcCfgParams != NULL) {
        Ptr ptr = ProcMgr_ipcCfgParams;
        Int len = strlen(ptr) + 1;
        Memory_free(NULL, ptr, len);
        ProcMgr_ipcCfgParams = NULL;
    }

    /* save params pointer in global symbol */
    if (params != NULL) {
        ProcMgr_ipcCfgParams = params;
    }

    GT_0trace (curTrace, GT_LEAVE, "_ProcMgr_saveParams");
}

/*!
 *  @brief      Function to map address to slave address space. does not hold
 *              state lock.
 *
 *              This function maps the provided slave address to a host address
 *              and returns the mapped address and size.
 *
 *  @param      handle      Handle to the Processor object
 *  @param      mapType     Type of mapping to be performed.
 *  @param      addrInfo    Structure containing map info.
 *  @param      srcAddrType Source address type.
 *
 *  @sa         Processor_map
 */
Int
_ProcMgr_map (ProcMgr_Handle     handle,
              ProcMgr_MapMask    mapType,
              ProcMgr_AddrInfo * addrInfo,
              ProcMgr_AddrType   srcAddrType)
{
    Int                      status         = ProcMgr_S_SUCCESS;
    ProcMgr_Object *         procMgrHandle  = (ProcMgr_Object *) handle;
    UInt32                   dstAddr;
    UInt32                   i;
    Memory_MapInfo           mInfo;
    Memory_SGList            sgList;

    GT_4trace (curTrace, GT_ENTER, "_ProcMgr_map",
               handle, mapType, addrInfo, srcAddrType);

    GT_assert (curTrace, (handle  != NULL));
    GT_assert (curTrace, (addrInfo != NULL));
    GT_assert (curTrace, (srcAddrType < ProcMgr_AddrType_EndValue));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_ProcMgr_map",
                             status,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval  ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_ProcMgr_map",
                             status,
                             "Invalid handle specified");
    }
    else if (addrInfo == NULL) {
        /*! @retval  ProcMgr_E_INVALIDARG Invalid value NULL provided for
                     argument addrInfo */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                         GT_4CLASS,
                         "_ProcMgr_map",
                         status,
                         "Invalid value NULL provided for argument addrInfo");
    }
    else if (srcAddrType >= ProcMgr_AddrType_EndValue) {
        /*! @retval  ProcMgr_E_INVALIDARG Invalid value provided for
                     argument srcAddrType */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                         GT_4CLASS,
                         "_ProcMgr_map",
                         status,
                         "Invalid value provided for argument srcAddrType");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        if (mapType & ProcMgr_MASTERKNLVIRT) {
            addrInfo->addr [ProcMgr_AddrType_MasterKnlVirt] = -1u;
            switch (srcAddrType) {
                case ProcMgr_AddrType_MasterKnlVirt:
                {
                    /*! @retval  ProcMgr_E_INVALIDARG Invalid srcAddrType for
                                                      MapType */
                    status = ProcMgr_E_INVALIDARG;
                    GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_ProcMgr_map",
                                     status,
                                     "Invalid srcAddrType for MapType");
                }
                break;

                case ProcMgr_AddrType_MasterUsrVirt:
                {
                    /*! @retval  ProcMgr_E_INVALIDARG Invalid srcAddrType for
                                                      MapType */
                    status = ProcMgr_E_INVALIDARG;
                    GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_ProcMgr_map",
                                     status,
                                     "Invalid srcAddrType for MapType");
                }
                break;

                case ProcMgr_AddrType_MasterPhys:
                {
                    mInfo.src  = addrInfo->addr [ProcMgr_AddrType_MasterPhys];
                    mInfo.size = addrInfo->size;
                    mInfo.isCached = addrInfo->isCached;

                    status = Memory_map (&mInfo);

#if !defined(IPC_BUILD_OPTIMIZE)
                    if (status < 0) {
                        /* Override with ProcMgr status code. */
                        status = ProcMgr_E_MAP;
                        GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "_ProcMgr_map",
                                         status,
                                         "Memory_map failed");
                    }
                    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                        addrInfo->addr [ProcMgr_AddrType_MasterKnlVirt] =
                                                                      mInfo.dst;
#if !defined(IPC_BUILD_OPTIMIZE)
                    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                }
                break;
                default:
                {
                    /*! @retval  ProcMgr_E_INVALIDARG Invalid srcAddrType */
                    status = ProcMgr_E_INVALIDARG;
                    GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_ProcMgr_map",
                                     status,
                                     "Invalid srcAddrType");
                }
                break;
            }
        }

        if (mapType & ProcMgr_SLAVEVIRT) {

            switch (srcAddrType) {

                case ProcMgr_AddrType_MasterKnlVirt:
                {
                    /* Create a sglist (TBD: For now we use translate API) */
                    sgList.paddr = (UInt32)Memory_translate(
                        (Ptr)addrInfo->addr[ProcMgr_AddrType_MasterKnlVirt],
                                Memory_XltFlags_Virt2Phys);

                    /* Align the address */
                    sgList.offset = (sgList.paddr & (0x1000 - 1));
                    sgList.size = addrInfo->size + sgList.offset;
                    sgList.paddr  = sgList.paddr & ~(0x1000 -1);

                    if (addrInfo->addr [ProcMgr_AddrType_SlaveVirt] != -1u) {
                        dstAddr = addrInfo->addr [ProcMgr_AddrType_SlaveVirt];
                        dstAddr &= ~(0x1000 - 1);

                        status = Processor_map (procMgrHandle->procHandle,
                            &dstAddr, 1, &sgList);

#if !defined(IPC_BUILD_OPTIMIZE)
                        if (status < 0) {
                            GT_setFailureReason (curTrace,
                                                 GT_4CLASS,
                                                 "_ProcMgr_map",
                                                 status,
                                                 "Processor_map failed");
                        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                    }
                    else {
                        /* Allocate a VMA if ProcMgr_AddrType_SlaveVirt is
                         * NULL
                         */
                    }
                }
                break;

                case ProcMgr_AddrType_MasterUsrVirt:
                {
                    /* TBD: Create a sglist */
                }
                break;
                case ProcMgr_AddrType_MasterPhys:
                {
                    /* Align the address to page size */
                    /* Create a sglist */
                    sgList.paddr = addrInfo->addr [ProcMgr_AddrType_MasterPhys];
                    sgList.offset = (sgList.paddr & (0x1000 - 1));
                    sgList.size = addrInfo->size + sgList.offset;
                    sgList.paddr  = sgList.paddr & ~(0x1000 -1);
                    if (addrInfo->addr [ProcMgr_AddrType_SlaveVirt] != -1u) {
                        dstAddr = addrInfo->addr [ProcMgr_AddrType_SlaveVirt];
                        dstAddr &= ~(0x1000 - 1);
                        GT_4trace (curTrace,
                                   GT_1CLASS,
                                   "_ProcMgr_map for SlaveVirt:\n"
                                   "    dstAddr       [0x%x]\n"
                                   "    sgList.paddr  [0x%x]\n"
                                   "    sgList.offset [0x%x]\n"
                                   "    sgList.size [0x%x]",
                                   dstAddr,
                                   sgList.paddr,
                                   sgList.offset,
                                   sgList.size);
                        status = Processor_map (procMgrHandle->procHandle,
                                                &dstAddr,
                                                1,
                                                &sgList);
#if !defined(IPC_BUILD_OPTIMIZE)
                        if (status < 0) {
                            GT_setFailureReason (curTrace,
                                                 GT_4CLASS,
                                                 "_ProcMgr_map",
                                                 status,
                                                 "Processor_map failed");
                        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                    }
                    else {
                        /* Allocate a VMA if ProcMgr_AddrType_SlaveVirt is not
                         * NULL
                         */
                    }
                }
                break;
                case ProcMgr_AddrType_SlaveVirt:
                {
                    /* TBD: Allocate a VMA region */
                    /* TBD: Allocate a buffer here from SysMemMgr */
                }
                break;
                default:
                {
                    /*! @retval  ProcMgr_E_INVALIDARG Invalid srcAddrType */
                    status = ProcMgr_E_INVALIDARG;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "_ProcMgr_map",
                                         status,
                                         "Invalid srcAddrType");
                }
                break;
            }
        }

       if (status >= 0) {
            /* Find a free slot */
            for (i = 0; i < procMgrHandle->maxMemoryRegions; i++) {
                if (procMgrHandle->memEntries [i].inUse == FALSE) {
                    break;
                }
            }

            if (i != procMgrHandle->maxMemoryRegions) {
                Memory_copy (&procMgrHandle->memEntries [i].info,
                             addrInfo,
                             sizeof (ProcMgr_AddrInfo));

                procMgrHandle->memEntries [i].inUse = TRUE;
                procMgrHandle->memEntries [i].srcAddrType = srcAddrType;
                procMgrHandle->memEntries [i].mapMask = mapType;
                procMgrHandle->numMemEntries++;
            }
            else {
                /* TBD: unmap the mapped */
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_ProcMgr_map",
                                     status,
                                     "All memEntries slots are in use!");
            }
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "_ProcMgr_map", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return status;
}


/* Function that unmaps the specified slave address from master address space. */
Int
ProcMgr_unmap (ProcMgr_Handle     handle,
               ProcMgr_MapMask    mapType,
               ProcMgr_AddrInfo * addrInfo,
               ProcMgr_AddrType   srcAddrType)
{
    Int    status = ProcMgr_S_SUCCESS;
    IArg   key    = 0;

    GT_4trace (curTrace, GT_ENTER, "ProcMgr_unmap",
               handle, mapType, addrInfo, srcAddrType);

    GT_assert (curTrace, (handle   != NULL));
#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_unmap",
                             status,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval  ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_unmap",
                             status,
                             "Invalid handle specified");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Enter critical section protection. */
        key = IGateProvider_enter (ProcMgr_state.gateHandle);
        status = _ProcMgr_unmap (handle, mapType, addrInfo, srcAddrType);
        IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_unmap", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to unmap address from slave address space.
 *              does not hold state lock.
 *
 *  @param      handle      Handle to the Processor object
 *  @param      mapType     Type of mapping to be performed.
 *  @param      addrInfo    Structure containing map info.
 *  @param      srcAddrType Source address type.
 *
 *  @sa         Processor_map
 */
Int
_ProcMgr_unmap (ProcMgr_Handle     handle,
                ProcMgr_MapMask    unmapType,
                ProcMgr_AddrInfo * addrInfo,
                ProcMgr_AddrType   srcAddrType)
{
    Int                      status         = ProcMgr_S_SUCCESS;
    ProcMgr_Object *         procMgrHandle  = (ProcMgr_Object *) handle;
    ProcMgr_MappedMemEntry * mme            = NULL;
    UInt32                   addr;
    UInt32                   i;
    Memory_UnmapInfo         umInfo;

    GT_4trace (curTrace, GT_ENTER, "_ProcMgr_unmap",
               handle, unmapType, addrInfo, srcAddrType);

    GT_assert (curTrace, (handle   != NULL));
    GT_assert (curTrace, (addrInfo != NULL));
    GT_assert (curTrace, (srcAddrType < ProcMgr_AddrType_EndValue));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_ProcMgr_unmap",
                             status,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval  ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_ProcMgr_unmap",
                             status,
                             "Invalid handle specified");
    }
    else if (addrInfo == NULL) {
        /*! @retval  ProcMgr_E_INVALIDARG Addrinfo is NULL */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_ProcMgr_unmap",
                             status,
                             "Addrinfo is NULL");
    }
    else if (srcAddrType >= ProcMgr_AddrType_EndValue) {
        /*! @retval  ProcMgr_E_INVALIDARG Invalid value provided for
                     argument srcAddrType */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                         GT_4CLASS,
                         "_ProcMgr_unmap",
                         status,
                         "Invalid value provided for argument srcAddrType");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* First try to find exact entry */
        for (i = 0; i < procMgrHandle->maxMemoryRegions; i++) {
            if (   (   procMgrHandle->memEntries [i].info.addr [srcAddrType]
                    == addrInfo->addr [srcAddrType])
                && (unmapType == procMgrHandle->memEntries [i].mapMask)
                && (procMgrHandle->memEntries[i].info.size == addrInfo->size)
                && (procMgrHandle->memEntries [i].inUse == TRUE))   {
                mme = &procMgrHandle->memEntries [i];
                GT_5trace (curTrace,
                     GT_1CLASS,
                 "_ProcMgr_unmap check:\n"
                 "    unmapType                                       [0x%x]\n"
                 "    srcAddrType                                     [0x%x]\n"
                 "    mme->info.addr [ProcMgr_AddrType_MasterPhys]    [0x%x]\n"
                 "    mme->info.addr [ProcMgr_AddrType_SlaveVirt]     [0x%x]\n"
                 "    mme->info.addr [ProcMgr_AddrType_MasterKnlVirt] [0x%x]",
                 unmapType,
                 srcAddrType,
                 mme->info.addr [ProcMgr_AddrType_MasterPhys],
                 mme->info.addr [ProcMgr_AddrType_SlaveVirt],
                 mme->info.addr [ProcMgr_AddrType_MasterKnlVirt]);

                /* Check if the address provided for unmap type matches. If it
                 * doesn't, then there are multiple mappings for the same source
                 * address, and this is not the correct one to be unmappd.
                 * In that case, continue to search.
                 */
                if ((unmapType & ProcMgr_MASTERKNLVIRT)
                    &&  (   mme->info.addr [ProcMgr_AddrType_MasterKnlVirt]
                         != addrInfo->addr [ProcMgr_AddrType_MasterKnlVirt])) {
                    continue;
                }

                if ((unmapType & ProcMgr_SLAVEVIRT)
                    &&  (   mme->info.addr [ProcMgr_AddrType_SlaveVirt]
                         != addrInfo->addr [ProcMgr_AddrType_SlaveVirt])) {
                    continue;
                }

                /* Otherwise found the entry, so break. */
                break;
            }
        }

        /* This may be partial unmap */
        if (i == procMgrHandle->maxMemoryRegions) {
            for (i = 0; i < procMgrHandle->maxMemoryRegions; i++) {
                if ( (    procMgrHandle->memEntries [i].info.addr [srcAddrType]
                       == addrInfo->addr [srcAddrType])
                    && (procMgrHandle->memEntries[i].info.size
                       == addrInfo->size)
                    && (procMgrHandle->memEntries [i].inUse == TRUE)) {
                    mme = &procMgrHandle->memEntries [i];

                    GT_5trace (curTrace,
                               GT_1CLASS,
                 "_ProcMgr_unmap check:\n"
                 "    unmapType                                       [0x%x]\n"
                 "    srcAddrType                                     [0x%x]\n"
                 "    mme->info.addr [ProcMgr_AddrType_MasterPhys]    [0x%x]\n"
                 "    mme->info.addr [ProcMgr_AddrType_SlaveVirt]     [0x%x]\n"
                 "    mme->info.addr [ProcMgr_AddrType_MasterKnlVirt] [0x%x]",
                               unmapType,
                               srcAddrType,
                               mme->info.addr [ProcMgr_AddrType_MasterPhys],
                               mme->info.addr [ProcMgr_AddrType_SlaveVirt],
                               mme->info.addr [ProcMgr_AddrType_MasterKnlVirt]);

                    /* Check if the address provided for unmap type matches. If
                     * it doesn't, then there are multiple mappings for the same
                     * source address, and this is not the correct one to be
                     * unmapped. In that case, continue to search.
                     */
                    if ((unmapType & ProcMgr_MASTERKNLVIRT)
                        && (   mme->info.addr [ProcMgr_AddrType_MasterKnlVirt]
                           != addrInfo->addr [ProcMgr_AddrType_MasterKnlVirt])){
                        continue;
                    }

                    if ((unmapType & ProcMgr_SLAVEVIRT)
                        &&  (   mme->info.addr [ProcMgr_AddrType_SlaveVirt]
                             != addrInfo->addr [ProcMgr_AddrType_SlaveVirt])) {
                        continue;
                    }

                    /* Otherwise found the entry, so break. */
                    break;
                }
            }
        }

#if !defined(IPC_BUILD_OPTIMIZE)
        if (i == procMgrHandle->maxMemoryRegions) {
            status = ProcMgr_E_NOTFOUND;
            /*! @retval  ProcMgr_E_NOTFOUND Info provided does not match with
                         any mapped entry */
            GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_ProcMgr_unmap",
                             status,
                             "Info provided does not match with any"
                             " mapped entry");
            GT_5trace (curTrace,
                 GT_1CLASS,
                 "_ProcMgr_unmap failure!\n"
                 "    unmapType                                       [0x%x]\n"
                 "    srcAddrType                                     [0x%x]\n"
                 "    addrInfo->addr [ProcMgr_AddrType_MasterPhys]    [0x%x]\n"
                 "    addrInfo->addr [ProcMgr_AddrType_SlaveVirt]     [0x%x]\n"
                 "    addrInfo->addr [ProcMgr_AddrType_MasterKnlVirt] [0x%x]",
                 unmapType,
                 srcAddrType,
                 addrInfo->addr [ProcMgr_AddrType_MasterPhys],
                 addrInfo->addr [ProcMgr_AddrType_SlaveVirt],
                 addrInfo->addr [ProcMgr_AddrType_MasterKnlVirt]);
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            if (unmapType & ProcMgr_MASTERKNLVIRT) {
                umInfo.addr = mme->info.addr [ProcMgr_AddrType_MasterKnlVirt];
                umInfo.size = mme->info.size;
                umInfo.isCached = mme->info.isCached;

                status = Memory_unmap (&umInfo);
#if !defined(IPC_BUILD_OPTIMIZE)
                if (status < 0) {
                    /* Override with ProcMgr status code. */
                    status = ProcMgr_E_MAP;
                    GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_ProcMgr_unmap",
                                     status,
                                     "Memory_unmap failed");
                }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            }

            if (unmapType & ProcMgr_SLAVEVIRT) {
                /* Unmap from host address space. */
                addr = mme->info.addr [ProcMgr_AddrType_SlaveVirt];
                status = Processor_unmap (procMgrHandle->procHandle,
                                          addr,
                                          mme->info.size);
#if !defined(IPC_BUILD_OPTIMIZE)
                if (status < 0) {
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "_ProcMgr_unmap",
                                         status,
                                         "Processor_unmap failed!");
                }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            }

            if (unmapType == mme->mapMask) {
                /* Since entry is unmapped from all address space, we can
                 * safely free the slot used */
                mme->inUse = FALSE;
                procMgrHandle->numMemEntries--;
            }
            else {
                mme->mapMask &= ~(unmapType);
            }
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "_ProcMgr_unmap", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return status;
}


/* Function that registers for notification when the slave processor
 * transitions to any of the states specified.
 */
Int
ProcMgr_registerNotify (ProcMgr_Handle      handle,
                        ProcMgr_CallbackFxn fxn,
                        Ptr                 args,
                        Int                 timeout,
                        ProcMgr_State       state [])
{
    Int              status         = ProcMgr_S_SUCCESS;
    ProcMgr_Object * procMgrHandle  = (ProcMgr_Object *) handle;
    IArg             key;

    GT_4trace (curTrace, GT_ENTER, "ProcMgr_registerNotify",
               handle, fxn, args, state);

    GT_assert (curTrace, (handle        != NULL));
    GT_assert (curTrace, (fxn           != 0));
    /* args is optional and may be NULL. */

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_registerNotify",
                             status,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval  ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_registerNotify",
                             status,
                             "Invalid handle specified");
    }
    else if (fxn == NULL) {
        /*! @retval  ProcMgr_E_INVALIDARG Invalid value NULL provided for
                     argument fxn */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_registerNotify",
                             status,
                             "Invalid value NULL provided for argument fxn");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Enter critical section protection. */
        key = IGateProvider_enter (ProcMgr_state.gateHandle);

        /* Register for notification with the Processor component. */
        status = Processor_registerNotify (procMgrHandle->procHandle,
                                           fxn,
                                           args,
                                           timeout,
                                           state);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ProcMgr_registerNotify",
                                 status,
                                 "Failed to register for notification!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            status = ProcMgr_S_REPLYLATER;
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Leave critical section protection. */
        IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_registerNotify", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return status;
}


/* Function that returns the maximum number of memory entries
 *
 * The kernel objects contain tables of size ProcMgr_MAX_MEMORY_REGIONS, so
 * this function retrieves that value for dynamically-sized arrays.
 */
UInt32
ProcMgr_getMaxMemoryRegions(ProcMgr_Handle handle)
{
    UInt32 maxMemRegions;
    ProcMgr_Object *objectPtr;

    GT_1trace(curTrace, GT_ENTER, "ProcMgr_getMaxMemoryRegions", handle);

    GT_assert(curTrace, (handle != NULL));

    maxMemRegions = 0;
    if (handle) {
        objectPtr = (ProcMgr_Object *)handle;
        maxMemRegions = objectPtr->maxMemoryRegions;
    }

    GT_1trace(curTrace, GT_LEAVE, "ProcMgr_getMaxMemoryRegions", maxMemRegions);

    return maxMemRegions;
}


/* Function that returns information about the characteristics of the slave
 * processor.
 */
Int
ProcMgr_getProcInfo (ProcMgr_Handle     handle,
                     ProcMgr_ProcInfo * procInfo)
{
    Int                      status         = ProcMgr_S_SUCCESS;
    ProcMgr_Object *         procMgrHandle  = (ProcMgr_Object *) handle;
    IArg                     key;

    GT_2trace (curTrace, GT_ENTER, "ProcMgr_getProcInfo", handle, procInfo);

    GT_assert (curTrace, (handle    != NULL));
    GT_assert (curTrace, (procInfo  != 0));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getProcInfo",
                             status,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval  ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getProcInfo",
                             status,
                             "Invalid handle specified");
    }
    else if (procInfo == NULL) {
        /*! @retval  ProcMgr_E_INVALIDARG Invalid value NULL provided for
                     argument procInfo */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                           GT_4CLASS,
                           "ProcMgr_getProcInfo",
                           status,
                           "Invalid value NULL provided for argument procInfo");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Enter critical section protection. */
        key = IGateProvider_enter (ProcMgr_state.gateHandle);

        /* Return bootMode information. */
        procInfo->bootMode = procMgrHandle->attachParams.bootMode;
        /* Return memory information. */
        procInfo->numMemEntries = procMgrHandle->numMemEntries;
        procInfo->maxMemoryRegions = procMgrHandle->maxMemoryRegions;
        Memory_copy (procInfo->memEntries, procMgrHandle->memEntries,
                (sizeof (ProcMgr_MappedMemEntry)
                 * procMgrHandle->maxMemoryRegions));

        GT_1trace (curTrace,
                   GT_2CLASS,
                   "    ProcMgr_getProcInfo: bootMode: [%d]",
                   procInfo->bootMode);

        /* Leave critical section protection. */
        IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_getProcInfo", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return status;
}


/* Function that returns section information given the name of section and
 * number of bytes to read
 */
Int ProcMgr_getSectionInfo (ProcMgr_Handle        handle,
                            UInt32                fileId,
                            String                sectionName,
                            ProcMgr_SectionInfo * sectionInfo)
{

    Int status = ProcMgr_S_SUCCESS;
    ProcMgr_Object * procMgrHandle  = (ProcMgr_Object *) handle;

    GT_4trace (curTrace,
               GT_ENTER,
               "ProcMgr_getSectionInfo",
               handle,
               fileId,
               sectionName,
               sectionInfo);

    GT_assert (curTrace, (handle      != NULL));
    /* Cannot check for fileId because it is loader dependent. */
    GT_assert (curTrace, (sectionName != NULL));
    /* Number of bytes to be read can be zero */
    GT_assert (curTrace, (sectionInfo != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getSectionInfo",
                             status,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval  ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getSectionInfo",
                             status,
                             "Invalid handle specified");
    }
    else if (sectionName == NULL) {
        /*! @retval  ProcMgr_E_INVALIDARG Invalid value NULL provided for
                     argument symbolName */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                         GT_4CLASS,
                         "ProcMgr_getSectionInfo",
                         status,
                         "Invalid value NULL provided for argument symbolName");
    }
    else if (sectionInfo == NULL) {
        /*! @retval  ProcMgr_E_INVALIDARG Invalid value NULL provided for
                     argument symValue */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                         GT_4CLASS,
                         "ProcMgr_getSectionInfo",
                         status,
                         "Invalid value NULL provided for argument symValue");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        status = Loader_getSectionInfo (procMgrHandle->loaderHandle,
                                        fileId,
                                        sectionName,
                                        sectionInfo);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ProcMgr_getSectionInfo",
                                 status,
                                 "Failed to get symbol address!");
        }
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, " ", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return status;
}


/* Function that returns section data in a buffer given section id and size
 * to be read
 */
Int ProcMgr_getSectionData (ProcMgr_Handle        handle,
                            UInt32                fileId,
                            ProcMgr_SectionInfo * sectionInfo,
                            Ptr                   buffer)
{
    Int status = ProcMgr_S_SUCCESS;
    ProcMgr_Object * procMgrHandle  = (ProcMgr_Object *) handle;

    GT_4trace (curTrace,
               GT_ENTER,
               "ProcMgr_getSectionData",
               handle,
               fileId,
               sectionInfo,
               buffer);

    GT_assert (curTrace, (handle != NULL));
    /* Cannot check for fileId because it is loader dependent. */
    GT_assert (curTrace, (sectionInfo != NULL));
    /* Number of bytes to be read can be zero */
    GT_assert (curTrace, (buffer != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getSectionData",
                             status,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval  ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getSectionData",
                             status,
                             "Invalid handle specified");
    }
    else if (buffer == NULL) {
        /*! @retval  ProcMgr_E_INVALIDARG Invalid value NULL provided for
                     argument symValue */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                         GT_4CLASS,
                         "ProcMgr_getSectionData",
                         status,
                         "Invalid value NULL provided for argument symValue");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        status = Loader_getSectionData (procMgrHandle->loaderHandle,
                                        fileId,
                                        sectionInfo,
                                        buffer);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ProcMgr_getSectionData",
                                 status,
                                 "Failed to get symbol address!");
        }
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_getSectionData", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return status;
}


/* Function to access fileId field from ProcMgr object */
UInt32
ProcMgr_getLoadedFileId (ProcMgr_Handle handle)
{
    ProcMgr_Object * procMgrObj = (ProcMgr_Object *) handle;
    UInt32           fileId     = 0;

    GT_assert (curTrace, (procMgrObj != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getSectionData",
                             ProcMgr_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getLoadedFileId",
                             ProcMgr_E_INVALIDARG,
                             "handle is null!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        fileId = procMgrObj->fileId;
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    /*! @retval fileId Operation successful */
    return (fileId);
}


/* Function that unregisters for notification when the slave processor
 * transitions to any of the states specified.
 */
Int
ProcMgr_unregisterNotify (ProcMgr_Handle      handle,
                          ProcMgr_CallbackFxn fxn,
                          Ptr                 args,
                          ProcMgr_State       state [])
{
    Int              status         = ProcMgr_S_SUCCESS;
    ProcMgr_Object * procMgrHandle  = (ProcMgr_Object *) handle;
    IArg             key;

    GT_4trace (curTrace, GT_ENTER, "ProcMgr_unregisterNotify",
               handle, fxn, args, state);

    GT_assert (curTrace, (handle        != NULL));
    GT_assert (curTrace, (fxn           != 0));
    /* args is optional and may be NULL. */

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                  ProcMgr_MAKE_MAGICSTAMP(0),
                                  ProcMgr_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval ProcMgr_E_INVALIDSTATE Module was not initialized */
        status = ProcMgr_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_unregisterNotify",
                             status,
                             "Module was not initialized!");
    }
    else if (handle == NULL) {
        /*! @retval  ProcMgr_E_HANDLE Invalid argument */
        status = ProcMgr_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_unregisterNotify",
                             status,
                             "Invalid handle specified");
    }
    else if (fxn == NULL) {
        /*! @retval  ProcMgr_E_INVALIDARG Invalid value NULL provided for
                     argument fxn */
        status = ProcMgr_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_unregisterNotify",
                             status,
                             "Invalid value NULL provided for argument fxn");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Enter critical section protection. */
        key = IGateProvider_enter (ProcMgr_state.gateHandle);

        /* Register for notification with the Processor component. */
        status = Processor_unregisterNotify (procMgrHandle->procHandle,
                                             fxn,
                                             args,
                                             state);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ProcMgr_unregisterNotify",
                                 status,
                                 "Failed to register for notification!");
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Leave critical section protection. */
        IGateProvider_leave (ProcMgr_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_unregisterNotify", status);

    /*! @retval ProcMgr_S_SUCCESS Operation successful */
    return status;
}

UInt32 ProcMgr_getId (ProcMgr_Handle handle)
{
    UInt32 id = (UInt32)(-1);
    UInt32 i  = 0;

    GT_1trace (curTrace, GT_ENTER, "ProcMgr_getId", handle);

    GT_assert (curTrace, (handle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (EXPECT_FALSE (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                                ProcMgr_MAKE_MAGICSTAMP(0),
                                                ProcMgr_MAKE_MAGICSTAMP(1))
                      == TRUE)) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getId",
                             ProcMgr_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if (EXPECT_FALSE (handle == NULL)) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getId",
                             ProcMgr_E_INVALIDSTATE,
                             "Invalid NULL handle pointer specified!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        for (i = 0; i < MultiProc_MAXPROCESSORS; i++) {
            if (ProcMgr_state.procHandles[i] == handle) {
                id = i;
                break;
            }
        }

        #if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_getId", id);

    return id;
}


ProcMgr_Handle ProcMgr_getHandle (UInt32 id)
{
    ProcMgr_Handle handle = NULL;

    GT_1trace (curTrace, GT_ENTER, "ProcMgr_getHandle", id);

    GT_assert (curTrace, (id >= 0));
    GT_assert (curTrace, (id < MultiProc_MAXPROCESSORS));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (EXPECT_FALSE (   Atomic_cmpmask_and_lt (&(ProcMgr_state.refCount),
                                                ProcMgr_MAKE_MAGICSTAMP(0),
                                                ProcMgr_MAKE_MAGICSTAMP(1))
                      == TRUE)) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getHandle",
                             ProcMgr_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if (EXPECT_FALSE (id >= MultiProc_MAXPROCESSORS)) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ProcMgr_getHandle",
                             ProcMgr_E_INVALIDARG,
                             "Invalid id specified!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        handle = ProcMgr_state.procHandles[id];

#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ProcMgr_getHandle", handle);

    return handle;
}


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
