/*
 *  @file   Platform.c
 *
 *  @brief      Implementation of Platform initialization logic.
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


/* Standard header files */
#include <ti/syslink/Std.h>

/* Utilities & Osal headers */
#include <ti/syslink/utils/Gate.h>
#include <ti/syslink/utils/GateMutex.h>
#include <ti/syslink/utils/Memory.h>
#include <ti/syslink/utils/Trace.h>
#include <ti/ipc/MultiProc.h>
#include <ti/syslink/utils/OsalPrint.h>
#include <ti/syslink/inc/knl/OsalThread.h>
#include <ti/syslink/utils/String.h>
#include <ti/syslink/utils/Cfg.h>

/* Ipc device specific headers */
#include <VAYUIpcInt.h>
#include <VAYUDspPwr.h>
#include <VAYUDspProc.h>
#include <VAYUIpuCore0Proc.h>
#include <VAYUIpuPwr.h>

/* Module level headers */
#include <_MessageQCopy.h>
#include <ti/ipc/MessageQCopy.h>
#include <_MessageQCopyDefs.h>

#include <ti/syslink/ProcMgr.h>
#include <_ProcMgr.h>
#include <ti/syslink/inc/knl/Platform.h>
#include <ElfLoader.h>

#include <ti/ipc/Ipc.h>
#include <_Ipc.h>
#include <_MultiProc.h>
#include <IpcKnl.h>
#include <sys/mman.h>
#include <GateHWSpinlock.h>
#include <_GateHWSpinlock.h>
#include <Gpt.h>

#if defined (__cplusplus)
extern "C" {
#endif


/** ============================================================================
 *  Macros.
 *  ============================================================================
 */

/** ============================================================================
 *  Application specific configuration, please change these value according to
 *  your application's need.
 *  ============================================================================
 */
/*!
 *  @brief  Structure defining config parameters for overall System.
 */
typedef struct Platform_Config {
    MultiProc_Config                multiProcConfig;
    /*!< Multiproc config parameter */

    MessageQCopy_Config             MQCopyConfig;
    /*!< MessageQCopy config parameter */

    ProcMgr_Config                  procMgrConfig;
    /*!< Processor manager config parameter */

    ElfLoader_Config                elfLoaderConfig;
    /*!< Elf loader config parameter */

    GateHWSpinlock_Config           gateHWSpinlockConfig;
    /*!< GateHWSpinlock config parameter */
} Platform_Config;

/*! @brief structure for platform instance */
typedef struct Platform_Object {
    /*!< Flag to indicate platform initialization status */
    ProcMgr_Handle                pmHandle;
    /*!< Handle to the ProcMgr instance used */
    union {
        struct {
            VAYUDSPPROC_Handle pHandle;
            /*!< Handle to the Processor instance used */
            VAYUDSPPWR_Handle  pwrHandle;
            /*!< Handle to the PwrMgr instance used */
            ElfLoader_Handle   ldrHandle;
            /*!< Handle to the Loader instance used */
        } dsp;
        struct {
            VAYUIPUCORE0PROC_Handle pHandle;
            /*!< Handle to the Processor instance used */
            VAYUIPUPWR_Handle       pwrHandle;
            /*!< Handle to the PwrMgr instance used */
            ElfLoader_Handle        ldrHandle;
            /*!< Handle to the Loader instance used */
        } ipu;
    } sHandles;
    /*!< Slave specific handles */
} Platform_Object, *Platform_Handle;


/*! @brief structure for platform instance */
typedef struct Platform_Module_State {
    Bool              multiProcInitFlag;
    /*!< MultiProc Initialize flag */
    Bool              messageQCopyInitFlag;
    /*!< MessageQCopy Initialize flag */
    Bool              procMgrInitFlag;
    /*!< Processor manager Initialize flag */
    Bool              elfLoaderInitFlag;
    /*!< Elf loader Initialize flag */
    Bool              ipcIntInitFlag;
    /*!< IpcInt Initialize flag */
    Bool              platformInitFlag;
    /*!< Flag to indicate platform initialization status */
    Bool              gateHWSpinlockInitFlag;
    /*!< GateHWSpinlock Initialize flag */
} Platform_Module_State;


/* =============================================================================
 * GLOBALS
 * =============================================================================
 */
static Platform_Object Platform_objects [MultiProc_MAXPROCESSORS];
static Platform_Module_State Platform_Module_state;
static Platform_Module_State * Platform_module = &Platform_Module_state;

Int32 _Platform_setup  (Ipc_Config * cfg);
Int32 _Platform_destroy (void);


/** ============================================================================
 *  APIs.
 *  ============================================================================
 */
/* Function to read slave memory */
Int32
_Platform_readSlaveMemory (UInt16   procId,
                           UInt32   addr,
                           Ptr      value,
                           UInt32 * numBytes);

/* Function to write slave memory */
Int32
_Platform_writeSlaveMemory (UInt16   procId,
                            UInt32   addr,
                            Ptr      value,
                            UInt32 * numBytes);
/*!
 *  @brief      Function to get the default values for configurations.
 *
 *  @param      config   Configuration values.
 */
Void
Platform_getConfig (Platform_Config * config)
{
    GT_1trace (curTrace, GT_ENTER, "Platform_getConfig", config);

    GT_assert (curTrace, (config != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (config == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "Platform_getConfig",
                             Platform_E_INVALIDARG,
                             "Argument of type (Platform_getConfig *) passed "
                             "is null!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        /* Get the gatepeterson default config */
        MultiProc_getConfig (&config->multiProcConfig);

        /* Get the PROCMGR default config */
        ProcMgr_getConfig (&config->procMgrConfig);

        /* Get the ElfLoader default config */
        ElfLoader_getConfig (&config->elfLoaderConfig);

        /* Get the HWSpinlock default config */
        GateHWSpinlock_getConfig (&config->gateHWSpinlockConfig);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "Platform_getConfig");
}

/*!
 *  @brief      Function to override the default configuration values.
 *
 *  @param      config   Configuration values.
 */
Int32
Platform_overrideConfig (Platform_Config * config, Ipc_Config * cfg)
{
    Int32  status = Platform_S_SUCCESS;

    GT_1trace (curTrace, GT_ENTER, "Platform_overrideConfig", config);

    GT_assert (curTrace, (config != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (config == NULL) {
        /*! @retval Platform_E_INVALIDARG Argument of type
         *  (Platform_Config *) passed is null*/
        status = Platform_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "Platform_overrideConfig",
                             status,
                             "Argument of type (Platform_getConfig *) passed "
                             "is null!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        /* Set the MultiProc config as defined in MultiProcCfg.c */
        config->multiProcConfig = _MultiProc_cfg;

        /* Override the MESSAGEQCOPY default config */
        config->MQCopyConfig.intId[1] = 173; // 141 + 32
        config->MQCopyConfig.intId[2] = 168; // 136 + 32
        config->MQCopyConfig.intId[3] = 173; // 141 + 32
        config->MQCopyConfig.intId[4] = 168; // 136 + 32

        /* Set the GateHWSpinlock config as defined in GateHWSpinlockCfg.c */
        config->gateHWSpinlockConfig = _GateHWSpinlock_cfg;

#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_ENTER, "Platform_overrideConfig", status);

    /*! @retval Platform_S_SUCCESS operation was successful */
    return status;
}

/*!
 *  @brief      Function to setup platform.
 *              TBD: logic would change completely in the final system.
 */
Int32
Platform_setup (Ipc_Config * cfg)
{
    Int32             status = Platform_S_SUCCESS;
    Platform_Config   _config;
    Platform_Config * config;
    VAYUIpcInt_Config VAYUcfg;

    Platform_getConfig (&_config);
    config = &_config;

    Platform_overrideConfig (config, cfg);

    status = MultiProc_setup (&(config->multiProcConfig));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "Platform_setup",
                             status,
                             "MultiProc_setup failed!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            Platform_module->multiProcInitFlag = TRUE;
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

/* Initialize PROCMGR */
    if (status >= 0) {
        status = ProcMgr_setup (&(config->procMgrConfig));
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "ProcMgr_setup failed!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            Platform_module->procMgrInitFlag = TRUE;
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    /* Initialize IpcInt required for VirtQueue/MessageQCopy. */
    if (status >= 0) {
        /* Do the IPC interrupts setup for the full platform (cfg is not used) */
        VAYUIpcInt_setup (&VAYUcfg);
        Platform_module->ipcIntInitFlag = TRUE;
    }


/* Intialize MESSAGEQCOPY */
    if (status >= 0) {
        status = MessageQCopy_setup (&config->MQCopyConfig);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "MessageQCopy_setup failed!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            Platform_module->messageQCopyInitFlag = TRUE;
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

/* Intialize Elf loader */
    if (status >= 0) {
        status = ElfLoader_setup (&config->elfLoaderConfig);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "ElfLoader_setup failed!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            Platform_module->elfLoaderInitFlag = TRUE;
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    if (status >= 0) {
        Memory_set (Platform_objects,
                    0,
                    (sizeof (Platform_Object) * MultiProc_getNumProcessors()));
    }

    if (status >= 0) {
        status = _Platform_setup (cfg);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "_Platform_setup failed!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            Platform_module->platformInitFlag = TRUE;
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }
    if (status >= 0) {
        status = GateHWSpinlock_setup (&config->gateHWSpinlockConfig);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "GateHWSpinlock_setup failed!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            status = GateHWSpinlock_start();
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "GateHWSpinlock_start failed!");
            }
            else {
                Platform_module->gateHWSpinlockInitFlag = TRUE;
            }
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    /* Enable GP timers */
    if (status >= 0) {
        status = Gpt_setup(&ti_ipc_Gpt_cfg);
        if (status < 0) {
            GT_setFailureReason(curTrace, GT_4CLASS, "Platform_setup",
                    status, "Gpt_setup failed!");
        }
    }

    if (status < 0) {
        Platform_destroy();
    }
    return status;
}


/*!
 *  @brief      Function to destroy the System.
 *
 *  @sa         Platform_setup
 */
Int32
Platform_destroy (void)
{
    Int32  status = Platform_S_SUCCESS;

    GT_0trace (curTrace, GT_ENTER, "Platform_destroy");

    /* Finalize Platform-specific destroy */
    if (Platform_module->platformInitFlag == TRUE) {
        status = _Platform_destroy ();
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "Platform_destroy failed!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            Platform_module->platformInitFlag = FALSE;
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    /* disable GP timers */
    Gpt_destroy();

    /* Finalize elf loader */
    if (Platform_module->elfLoaderInitFlag == TRUE) {
        status = ElfLoader_destroy ();
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "ElfLoader_destroy failed!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            Platform_module->elfLoaderInitFlag = FALSE;
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    /* Finalize MESSAGEQCOPY */
    if (Platform_module->messageQCopyInitFlag == TRUE) {
        status = MessageQCopy_destroy ();
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "MessageQCopy_destroy failed!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            Platform_module->messageQCopyInitFlag = FALSE;
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }


    if (Platform_module->ipcIntInitFlag == TRUE) {
        VAYUIpcInt_destroy ();
        Platform_module->ipcIntInitFlag = FALSE;
    }

    /* Finalize PROCMGR */
    if (Platform_module->procMgrInitFlag == TRUE) {
        status = ProcMgr_destroy ();
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "ProcMgr_destroy failed!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            Platform_module->procMgrInitFlag = FALSE;
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    /* Finalize MultiProc */
    if (Platform_module->multiProcInitFlag == TRUE) {
        status = MultiProc_destroy ();
#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "Platform_destroy",
                             status,
                             "MultiProc_destroy failed!");
    }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            Platform_module->multiProcInitFlag = FALSE;
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    if (status >= 0) {
        Memory_set (Platform_objects,
                    0,
                    (sizeof (Platform_Object) * MultiProc_getNumProcessors()));
    }

    if (Platform_module->gateHWSpinlockInitFlag == TRUE) {
        status = GateHWSpinlock_stop();
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "GateHWSpinlock_stop failed!");
        }
        else {
            status = GateHWSpinlock_destroy();
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "GateHWSpinlock_destroy failed!");
            }
            else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                Platform_module->gateHWSpinlockInitFlag = FALSE;
#if !defined(IPC_BUILD_OPTIMIZE)
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }

    GT_1trace (curTrace, GT_LEAVE, "Platform_destroy", status);

    /*! @retval Platform_S_SUCCESS Operation successful */
    return status;
}

/*
 * union _Platform_setup_Local exists so that we don't waste stack or
 * alloc'ed memory on storage for things that exist for just a few
 * statements of the function _Platform_setup().  The *PROC_Params
 * elements are large and variably sized, depending on the macro
 * ProcMgr_MAX_MEMORY_REGIONS.
 */
typedef union _Platform_setup_Local {
    ProcMgr_Params          params;
    VAYUDSPPROC_Config      dspProcConfig;
    VAYUIPUCORE0PROC_Config ipuProcConfig;
    VAYUDSPPWR_Config       dspPwrConfig;
    VAYUIPUPWR_Config       ipuPwrConfig;
    VAYUDSPPROC_Params      dspProcParams;
    VAYUIPUCORE0PROC_Params ipuProcParams;
    VAYUDSPPWR_Params       dspPwrParams;
    VAYUIPUPWR_Params       ipuPwrParams;
    ElfLoader_Params        elfLoaderParams;
} _Platform_setup_Local;


/*!
 *  @brief      Function to setup platform.
 *              TBD: logic would change completely in the final system.
 */
Int32
_Platform_setup (Ipc_Config * cfg)
{
    Int32                   status = Platform_S_SUCCESS;
    _Platform_setup_Local   *lv;
    UInt16                  procId;
    Platform_Handle         handle;

    GT_0trace (curTrace, GT_ENTER, "_Platform_setup");

    lv = Memory_alloc(NULL, sizeof(_Platform_setup_Local), 0, NULL);
    if (lv == NULL) {
        status = Platform_E_FAIL;
        GT_setFailureReason (curTrace,
                                GT_4CLASS,
                                "_Platform_setup",
                                status,
                                "Memory_alloc failed");
        goto ret;
    }
    if (status >= 0) {
        /* Get MultiProc ID by name. */
        procId = MultiProc_getId ("IPU1");

        handle = &Platform_objects [procId];
        VAYUIPUCORE0PROC_getConfig (&lv->ipuProcConfig);
        status = VAYUIPUCORE0PROC_setup (&lv->ipuProcConfig);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_setup",
                                 status,
                                 "VAYUIPUCORE0PROC_setup failed!");
        }
        else {
            VAYUIPUPWR_getConfig (&lv->ipuPwrConfig);
            status = VAYUIPUPWR_setup (&lv->ipuPwrConfig);
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "VAYUIPUPWR_setup failed!");
            }
        }

        if (status >= 0) {
            /* Create an instance of the Processor object for
             * VAYUIPUCORE0 */
            VAYUIPUCORE0PROC_Params_init (NULL, &lv->ipuProcParams);
            handle->sHandles.ipu.pHandle = VAYUIPUCORE0PROC_create (procId,
                                                         &lv->ipuProcParams);

            /* Create an instance of the ELF Loader object */
            ElfLoader_Params_init (NULL, &lv->elfLoaderParams);
            handle->sHandles.ipu.ldrHandle = ElfLoader_create (procId,
                                                        &lv->elfLoaderParams);

            /* Create an instance of the PwrMgr object for VAYUIPUCORE0 */
            VAYUIPUPWR_Params_init (&lv->ipuPwrParams);
            handle->sHandles.ipu.pwrHandle = VAYUIPUPWR_create (
                                                           procId,
                                                           &lv->ipuPwrParams);

            if (handle->sHandles.ipu.pHandle == NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "VAYUIPUCORE0PROC_create failed!");
            }
            else if (handle->sHandles.ipu.ldrHandle ==  NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "Failed to create loader instance!");
            }
            else if (handle->sHandles.ipu.pwrHandle ==  NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "VAYUIPUPWR_create failed!");
            }
            else {
                /* Initialize parameters */
                ProcMgr_Params_init (NULL, &lv->params);
                lv->params.procHandle = handle->sHandles.ipu.pHandle;
                lv->params.loaderHandle = handle->sHandles.ipu.ldrHandle;
                lv->params.pwrHandle = handle->sHandles.ipu.pwrHandle;
                handle->pmHandle = ProcMgr_create (procId, &lv->params);
                if (handle->pmHandle == NULL) {
                    status = Platform_E_FAIL;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "_Platform_setup",
                                         status,
                                         "ProcMgr_create failed!");
                }
            }
        }
    }

    if (status >= 0) {
        /* Get MultiProc ID by name. */
        procId = MultiProc_getId ("IPU2");

        handle = &Platform_objects [procId];

        if (status >= 0) {
            /* Create an instance of the Processor object for
             * VAYUIPUCORE0 */
            VAYUIPUCORE0PROC_Params_init (NULL, &lv->ipuProcParams);
            handle->sHandles.ipu.pHandle = VAYUIPUCORE0PROC_create (procId,
                                                         &lv->ipuProcParams);

            /* Create an instance of the ELF Loader object */
            ElfLoader_Params_init (NULL, &lv->elfLoaderParams);
            handle->sHandles.ipu.ldrHandle = ElfLoader_create (procId,
                                                        &lv->elfLoaderParams);

            /* Create an instance of the PwrMgr object for VAYUIPUCORE0 */
            VAYUIPUPWR_Params_init (&lv->ipuPwrParams);
            handle->sHandles.ipu.pwrHandle = VAYUIPUPWR_create (
                                                           procId,
                                                           &lv->ipuPwrParams);

            if (handle->sHandles.ipu.pHandle == NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "VAYUIPUCORE0PROC_create failed!");
            }
            else if (handle->sHandles.ipu.ldrHandle ==  NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "Failed to create loader instance!");
            }
            else if (handle->sHandles.ipu.pwrHandle ==  NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "VAYUIPUPWR_create failed!");
            }
            else {
                /* Initialize parameters */
                ProcMgr_Params_init (NULL, &lv->params);
                lv->params.procHandle = handle->sHandles.ipu.pHandle;
                lv->params.loaderHandle = handle->sHandles.ipu.ldrHandle;
                lv->params.pwrHandle = handle->sHandles.ipu.pwrHandle;
                handle->pmHandle = ProcMgr_create (procId, &lv->params);
                if (handle->pmHandle == NULL) {
                    status = Platform_E_FAIL;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "_Platform_setup",
                                         status,
                                         "ProcMgr_create failed!");
                }
            }
        }
    }

    if (status >= 0) {
        /* Get MultiProc ID by name. */
        procId = MultiProc_getId ("DSP1");

        handle = &Platform_objects [procId];
        VAYUDSPPROC_getConfig (&lv->dspProcConfig);
        status = VAYUDSPPROC_setup (&lv->dspProcConfig);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_setup",
                                 status,
                                 "VAYUDSPPROC_setup failed!");
        }
        else {
            VAYUDSPPWR_getConfig (&lv->dspPwrConfig);
            status = VAYUDSPPWR_setup (&lv->dspPwrConfig);
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "VAYUDSPPWR_setup failed!");
            }
        }

        if (status >= 0) {
            /* Create an instance of the Processor object for
             * VAYUDSP */
            VAYUDSPPROC_Params_init (NULL, &lv->dspProcParams);
            handle->sHandles.dsp.pHandle = VAYUDSPPROC_create (procId,
                                                              &lv->dspProcParams);

            /* Create an instance of the ELF Loader object */
            ElfLoader_Params_init (NULL, &lv->elfLoaderParams);
            handle->sHandles.dsp.ldrHandle =
                                           ElfLoader_create (procId,
                                                             &lv->elfLoaderParams);
            /* Create an instance of the PwrMgr object for VAYUDSP */
            VAYUDSPPWR_Params_init (&lv->dspPwrParams);
            handle->sHandles.dsp.pwrHandle = VAYUDSPPWR_create (procId,
                                                    &lv->dspPwrParams);

            if (handle->sHandles.dsp.pHandle == NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "VAYUDSPPROC_create failed!");
            }
            else if (handle->sHandles.dsp.ldrHandle ==  NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "Failed to create loader instance!");
            }
            else if (handle->sHandles.dsp.pwrHandle ==  NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "VAYUDSPPWR_create failed!");
            }
            else {
                /* Initialize parameters */
                ProcMgr_Params_init (NULL, &lv->params);
                lv->params.procHandle = handle->sHandles.dsp.pHandle;
                lv->params.loaderHandle = handle->sHandles.dsp.ldrHandle;
                lv->params.pwrHandle = handle->sHandles.dsp.pwrHandle;
                handle->pmHandle = ProcMgr_create (procId, &lv->params);
                if (handle->pmHandle == NULL) {
                    status = Platform_E_FAIL;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "_Platform_setup",
                                         status,
                                         "ProcMgr_create failed!");
                }
            }
        }
    }

    if (status >= 0) {
        /* Get MultiProc ID by name. */
        procId = MultiProc_getId ("DSP2");

        handle = &Platform_objects [procId];

        if (status >= 0) {
            /* Create an instance of the Processor object for
             * VAYUDSP */
            VAYUDSPPROC_Params_init (NULL, &lv->dspProcParams);
            handle->sHandles.dsp.pHandle = VAYUDSPPROC_create (procId,
                                                              &lv->dspProcParams);

            /* Create an instance of the ELF Loader object */
            ElfLoader_Params_init (NULL, &lv->elfLoaderParams);
            handle->sHandles.dsp.ldrHandle =
                                           ElfLoader_create (procId,
                                                             &lv->elfLoaderParams);
            /* Create an instance of the PwrMgr object for VAYUDSP */
            VAYUDSPPWR_Params_init (&lv->dspPwrParams);
            handle->sHandles.dsp.pwrHandle = VAYUDSPPWR_create (procId,
                                                    &lv->dspPwrParams);

            if (handle->sHandles.dsp.pHandle == NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "VAYUDSPPROC_create failed!");
            }
            else if (handle->sHandles.dsp.ldrHandle ==  NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "Failed to create loader instance!");
            }
            else if (handle->sHandles.dsp.pwrHandle ==  NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "VAYUDSPPWR_create failed!");
            }
            else {
                /* Initialize parameters */
                ProcMgr_Params_init (NULL, &lv->params);
                lv->params.procHandle = handle->sHandles.dsp.pHandle;
                lv->params.loaderHandle = handle->sHandles.dsp.ldrHandle;
                lv->params.pwrHandle = handle->sHandles.dsp.pwrHandle;
                handle->pmHandle = ProcMgr_create (procId, &lv->params);
                if (handle->pmHandle == NULL) {
                    status = Platform_E_FAIL;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "_Platform_setup",
                                         status,
                                         "ProcMgr_create failed!");
                }
            }
        }
    }

    Memory_free(NULL, lv, sizeof(_Platform_setup_Local));

ret:
    GT_1trace (curTrace, GT_LEAVE, "_Platform_setup", status);

    /*! @retval Platform_S_SUCCESS operation was successful */
    return status;
}


/*!
 *  @brief      Function to setup platform.
 *              TBD: logic would change completely in the final system.
 */
Int32
_Platform_destroy (void)
{
    Int32           status    = Platform_S_SUCCESS;
    Int32           tmpStatus = Platform_S_SUCCESS;
    Platform_Handle handle;

    GT_0trace (curTrace, GT_ENTER, "_Platform_destroy");

    /* ------------------------- DSP1 cleanup -------------------------------- */
    handle = &Platform_objects [MultiProc_getId ("DSP1")];
    if (handle->pmHandle != NULL) {
        status = ProcMgr_delete (&handle->pmHandle);
        GT_assert (curTrace, (status >= 0));
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "ProcMgr_delete failed!");
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    /* Delete the Processor, Loader and PwrMgr instances */
    if (handle->sHandles.dsp.pwrHandle != NULL) {
        tmpStatus = VAYUDSPPWR_delete (&handle->sHandles.dsp.pwrHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "VAYUDSPPWR_delete failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }

    if (handle->sHandles.dsp.ldrHandle != NULL) {
        tmpStatus = ElfLoader_delete (&handle->sHandles.dsp.ldrHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "Failed to delete loader instance!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }

    if (handle->sHandles.dsp.pHandle != NULL) {
        tmpStatus = VAYUDSPPROC_delete (&handle->sHandles.dsp.pHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "VAYUDSPPROC_delete failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }

    /* ------------------------- DSP2 cleanup -------------------------------- */
    handle = &Platform_objects [MultiProc_getId ("DSP2")];
    if (handle->pmHandle != NULL) {
        status = ProcMgr_delete (&handle->pmHandle);
        GT_assert (curTrace, (status >= 0));
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "ProcMgr_delete failed!");
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    /* Delete the Processor, Loader and PwrMgr instances */
    if (handle->sHandles.dsp.pwrHandle != NULL) {
        tmpStatus = VAYUDSPPWR_delete (&handle->sHandles.dsp.pwrHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "VAYUDSPPWR_delete failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }

    if (handle->sHandles.dsp.ldrHandle != NULL) {
        tmpStatus = ElfLoader_delete (&handle->sHandles.dsp.ldrHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "Failed to delete loader instance!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }

    if (handle->sHandles.dsp.pHandle != NULL) {
        tmpStatus = VAYUDSPPROC_delete (&handle->sHandles.dsp.pHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "VAYUDSPPROC_delete failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }

    tmpStatus = VAYUDSPPWR_destroy ();
    GT_assert (curTrace, (tmpStatus >= 0));
    if ((status >= 0) && (tmpStatus < 0)) {
        status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_Platform_destroy",
                             status,
                             "VAYUDSPPWR_destroy failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    tmpStatus = VAYUDSPPROC_destroy ();
    GT_assert (curTrace, (tmpStatus >= 0));
    if ((status >= 0) && (tmpStatus < 0)) {
        status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_Platform_destroy",
                             status,
                             "VAYUDSPPROC_destroy failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    /* ------------------------- IPU1 cleanup ------------------------------- */
    handle = &Platform_objects [MultiProc_getId ("IPU1")];
    if (handle->pmHandle != NULL) {
        tmpStatus = ProcMgr_delete (&handle->pmHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "ProcMgr_delete failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }

    /* Delete the Processor, Loader and PwrMgr instances */
    if (handle->sHandles.ipu.pwrHandle != NULL) {
        tmpStatus = VAYUIPUPWR_delete (&handle->sHandles.ipu.pwrHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "VAYUIPUPWR_delete failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }

    if (handle->sHandles.ipu.ldrHandle != NULL) {
        tmpStatus = ElfLoader_delete (&handle->sHandles.ipu.ldrHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "Failed to delete loader instance!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }

    if (handle->sHandles.ipu.pHandle != NULL) {
        tmpStatus = VAYUIPUCORE0PROC_delete (&handle->sHandles.ipu.pHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "VAYUIPUCORE0PROC_delete failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }

    /* ------------------------- IPU2 cleanup ------------------------------- */
    handle = &Platform_objects [MultiProc_getId ("IPU2")];
    if (handle->pmHandle != NULL) {
        tmpStatus = ProcMgr_delete (&handle->pmHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "ProcMgr_delete failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }

    /* Delete the Processor, Loader and PwrMgr instances */
    if (handle->sHandles.ipu.pwrHandle != NULL) {
        tmpStatus = VAYUIPUPWR_delete (&handle->sHandles.ipu.pwrHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "VAYUIPUPWR_delete failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }

    if (handle->sHandles.ipu.ldrHandle != NULL) {
        tmpStatus = ElfLoader_delete (&handle->sHandles.ipu.ldrHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "Failed to delete loader instance!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }

    if (handle->sHandles.ipu.pHandle != NULL) {
        tmpStatus = VAYUIPUCORE0PROC_delete (&handle->sHandles.ipu.pHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "VAYUIPUCORE0PROC_delete failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }

    tmpStatus = VAYUIPUPWR_destroy ();
    GT_assert (curTrace, (tmpStatus >= 0));
    if ((status >= 0) && (tmpStatus < 0)) {
        status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_Platform_destroy",
                             status,
                             "VAYUIPUPWR_destroy failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    tmpStatus = VAYUIPUCORE0PROC_destroy ();
    GT_assert (curTrace, (tmpStatus >= 0));
    if ((status >= 0) && (tmpStatus < 0)) {
        status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_Platform_destroy",
                             status,
                             "VAYUIPUCORE0PROC_destroy failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    GT_1trace (curTrace, GT_LEAVE, "_Platform_destroy", status);

    /*! @retval Platform_S_SUCCESS operation was successful */
    return status;
}


#if defined (__cplusplus)
}
#endif
