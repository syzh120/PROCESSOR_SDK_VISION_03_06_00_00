/*
 *  @file   Platform.c
 *
 *  @brief      Implementation of Platform initialization logic.
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


/* Standard header files */
#include <ti/syslink/Std.h>

/* Utilities & Osal headers */
#include <ti/syslink/utils/Gate.h>
#include <ti/syslink/utils/GateMutex.h>
#include <ti/syslink/utils/Memory.h>
#include <ti/syslink/utils/Trace.h>
#include <ti/ipc/MultiProc.h>
#include <_MultiProc.h>
#include <ti/syslink/utils/OsalPrint.h>
#include <ti/syslink/utils/String.h>

/* Ipc device specific headers */
#include <ProcDefs.h>
#include <Processor.h>
#include <OMAP5430BenelliHal.h>
#include <OMAP5430BenelliHalReset.h>
#include <OMAP5430BenelliHalMmu.h>
#include <OMAP5430BenelliProc.h>
#include <Omap5430IpcInt.h>

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
#include <ipu_pm.h>
#include <GateHWSpinlock.h>

#if defined (__cplusplus)
extern "C" {
#endif


/** ============================================================================
 *  Macros.
 *  ============================================================================
 */
#define RESETVECTOR_SYMBOL          "_Ipc_ResetVector"

#define IPC_MEM_VRING0          0xA0000000
#define IPC_MEM_VRING1          0xA0004000
#define IPC_MEM_VRING2          0xA0008000
#define IPC_MEM_VRING3          0xA000c000

#define HWSPINLOCK_BASE             0x4A0F6000
#define HWSPINLOCK_SIZE             0x1000
#define HWSPINLOCK_OFFSET           0x800

#ifndef IPC_SYSBIOS_SMP
#define CORE0 "CORE0"
#else
#define CORE0 "IPU"
#endif

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
    /*!< Notify config parameter */

    ProcMgr_Config                  procMgrConfig;
    /*!< Processor manager config parameter */

    ipu_pm_config                   ipu_pm_config;
    /* ipu_pm config parameter */

    ElfLoader_Config                elfLoaderConfig;
    /*!< Elf loader config parameter */

    GateHWSpinlock_Config           gateHWSpinlockConfig;
    /*!< GateHWSpinlock config parameter */
} Platform_Config;


/* Struct embedded into slave binary */
typedef struct Platform_SlaveConfig {
    UInt32  cacheLineSize;
    UInt32  brOffset;
} Platform_SlaveConfig;

typedef struct Platform_SlaveSRConfig {
    UInt32 entryBase;
    UInt32 entryLen;
    UInt32 ownerProcId;
    UInt32 id;
    UInt32 createHeap;
    UInt32 cacheLineSize;
} Platform_SlaveSRConfig;

/* Shared region configuration information for host side. */
typedef struct Platform_HostSRConfig {
    UInt16 refCount;
} Platform_HostSRConfig;

/*! @brief structure for platform instance */
typedef struct Platform_Object {
    /*!< Flag to indicate platform initialization status */
    ProcMgr_Handle                pmHandle;
    /*!< Handle to the ProcMgr instance used */
    union{
        struct {
            OMAP5430BENELLIPROC_Handle    pHandle;
            /*!< Handle to the Processor instance used */
            /*!< Handle to the PwrMgr instance used */
            ElfLoader_Handle             ldrHandle;
            /*!< Handle to the Loader instance used */
            UInt32                       fileId;
            /*!< File ID of loaded image, needed for un-loading */
        } ipu0;
#ifndef IPC_SYSBIOS_SMP
        struct {
            OMAP5430BENELLIPROC_Handle    pHandle;
            /*!< Handle to the Processor instance used */
            /*!< Handle to the PwrMgr instance used */
            /* NOTE: no loader used for ipu1, both cores loaded at once */
            /*!< Handle to the Loader instance used */
        } ipu1;
#endif
        struct {
            OMAP5430BENELLIPROC_Handle    pHandle;
            /*!< Handle to the Processor instance used */
            /*!< Handle to the PwrMgr instance used */
            ElfLoader_Handle              ldrHandle;
            /*!< Handle to the Loader instance used */
        } dsp;
    } sHandles;
    /*!< Slave specific handles */
    Platform_SlaveConfig          slaveCfg;
    /*!< Slave embedded config */
    Platform_SlaveSRConfig *      slaveSRCfg;
    /*!< Shared region details from slave */
} Platform_Object, *Platform_Handle;


/*! @brief structure for platform instance */
typedef struct Platform_Module_State {
    Bool              multiProcInitFlag;
    /*!< MultiProc Initialize flag */
    Bool              ipu_pm_init_flag;
    /*!< ipu_pm Initialize flag */
    Bool              procMgrInitFlag;
    /*!< Processor manager Initialize flag */
    Bool              elfLoaderInitFlag;
    /*!< Elf loader Initialize flag */
    Bool              ipcIntInitFlag;
    /*!< IpcInt Initialize flag */
    Bool              platformInitFlag;
    /*!< Flag to indicate platform initialization status */
    Bool              mqcopyInitFlag;
    /*!< MQCopy Initialize flag */
    Bool              platform_mem_init_flag;
    /*!< Flag to indicate platform initialization status */
    Bool              gateHWSpinlockInitFlag;
    /*!< GateHWSpinlock Initialize flag */
    Ptr               gateHWSpinlockVAddr;
    /*!< GateHWSpinlock Virtual Address */
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
        ElfLoader_getConfig(&config->elfLoaderConfig);

        /* Get the HWSpinlock default config */
        GateHWSpinlock_getConfig (&config->gateHWSpinlockConfig);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "Platform_getConfig");
}

/*!
 *  @brief      Function to override the default confiuration values.
 *
 *  @param      config   Configuration values.
 */
Int32
Platform_overrideConfig (Platform_Config * config, Ipc_Config * cfg)
{
    Int32  status = Platform_S_SUCCESS;
    /*Char   hexString[16];*/

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

        /* Set the MultiProc config as defined in SystemCfg.c */
        config->multiProcConfig = _MultiProc_cfg;

        /* Override the PROCMGR default config */

        /* Override the MessageQCopy default config */
        config->MQCopyConfig.intId[1] = 58;
        config->MQCopyConfig.intId[2] = 58;
        config->MQCopyConfig.intId[3] = 58;

        config->ipu_pm_config.int_id = 58;
#ifdef IPC_SYSBIOS_SMP
        config->ipu_pm_config.num_procs = 2;
        config->ipu_pm_config.proc_ids[0] = 1; // IPU is set as 1 above
        config->ipu_pm_config.proc_ids[1] = 2; // DSP is set as 2 above
#else
        config->ipu_pm_config.num_procs = 3;
        config->ipu_pm_config.proc_ids[0] = 1; // CORE0 is set as 1 above
        config->ipu_pm_config.proc_ids[1] = 2; // CORE1 is set as 2 above
        config->ipu_pm_config.proc_ids[2] = 3; // DSP is set as 3 above
#endif

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
    Int32                   status      = Platform_S_SUCCESS;
    Platform_Config         _config;
    Platform_Config *       config;
    Omap5430IpcInt_Config   omap5430cfg;
    Memory_MapInfo    minfo;

    Platform_getConfig (&_config);
    config = &_config;

/* Initialize PlatformMem */
    status = MemoryOS_setup();
#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "Platform_setup",
                             status,
                             "platform_mem_setup!");
    } else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        Platform_module->platform_mem_init_flag = TRUE;
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

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
        /* Do the IPC interrupt setup for the full platform (cfg is not used) */
        Omap5430IpcInt_setup(&omap5430cfg);
        Platform_module->ipcIntInitFlag = TRUE;
    }

/* Initialize Elf loader */
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

/* Initialize ipu_pm */
    if (status >= 0) {
        status = ipu_pm_setup (&config->ipu_pm_config);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_setup",
                                 status,
                                 "ipu_pm_setup failed!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            Platform_module->ipu_pm_init_flag = TRUE;
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

/* Initialize MessageQCopy */
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
            Platform_module->mqcopyInitFlag = TRUE;
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
        /* Doing per remote-proc init stuff */
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
        minfo.src  = HWSPINLOCK_BASE;
        minfo.size = HWSPINLOCK_SIZE;
        minfo.isCached = FALSE;
        status = Memory_map (&minfo);
        if (status < 0) {
           GT_setFailureReason (curTrace,
                                GT_4CLASS,
                                "Platform_setup",
                                status,
                                "Memory_map failed!");
        }
        else {
            Platform_module->gateHWSpinlockVAddr = (Ptr)minfo.dst;
            config->gateHWSpinlockConfig.numLocks = 32;
            config->gateHWSpinlockConfig.baseAddr = minfo.dst  + HWSPINLOCK_OFFSET;
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
                Platform_module->gateHWSpinlockInitFlag = TRUE;
#if !defined(IPC_BUILD_OPTIMIZE)
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
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
    Memory_UnmapInfo minfo;

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

    /* Finalize MessageQCopy */
    if (Platform_module->mqcopyInitFlag == TRUE) {
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
            Platform_module->mqcopyInitFlag = FALSE;
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    /* Finalize ipu_pm */
    if (Platform_module->ipu_pm_init_flag == TRUE) {
        status = ipu_pm_destroy ();
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "ipu_pm_destroy failed!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            Platform_module->ipu_pm_init_flag = FALSE;
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    /* Finalize Elf loader */
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

    if (Platform_module->ipcIntInitFlag == TRUE) {
        Omap5430IpcInt_destroy ();
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

    if (Platform_module->gateHWSpinlockVAddr) {
        minfo.addr = (UInt32)Platform_module->gateHWSpinlockVAddr;
        minfo.size = HWSPINLOCK_SIZE;
        minfo.isCached = FALSE;
        status = Memory_unmap(&minfo);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "Memory_unmap failed!");
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        Platform_module->gateHWSpinlockVAddr = NULL;
    }

    if (Platform_module->platform_mem_init_flag == TRUE) {
        status = MemoryOS_destroy();
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Platform_destroy",
                                 status,
                                 "MemoryOS_destroy failed!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            Platform_module->platform_mem_init_flag = FALSE;
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    GT_1trace (curTrace, GT_LEAVE, "Platform_destroy", status);

    /*! @retval Platform_S_SUCCESS Operation successful */
    return status;
}

/*!
 *  @brief      Function to setup platform.
 *              TBD: logic would change completely in the final system.
 */
Int32
_Platform_setup (Ipc_Config * cfg)
{
    Int32                       status              = Platform_S_SUCCESS;
    ProcMgr_Params              params;
    OMAP5430BENELLIPROC_Config  ipu0ProcConfig;
#ifndef IPC_SYSBIOS_SMP
    OMAP5430BENELLIPROC_Config  ipu1ProcConfig;
#endif
    OMAP5430BENELLIPROC_Config  dspProcConfig;
    OMAP5430BENELLIPROC_Params  ipu0ProcParams;
#ifndef IPC_SYSBIOS_SMP
    OMAP5430BENELLIPROC_Params  ipu1ProcParams;
#endif
    OMAP5430BENELLIPROC_Params  dspProcParams;
    ElfLoader_Params            elfLoaderParams;
    ElfLoader_Handle            ldrHandle;
    UInt16                      procId;
    Platform_Handle             handle;
    Bool                        core0Setup          = FALSE;
#ifndef IPC_SYSBIOS_SMP
    Bool                        core1Setup          = FALSE;
#endif
    Bool                        dspSetup            = FALSE;

    GT_0trace (curTrace, GT_ENTER, "_Platform_setup");

    /* Get MultiProc ID by name. */
    procId = MultiProc_getId (CORE0);

    handle = &Platform_objects [procId];

    OMAP5430BENELLIPROC_get_config(&ipu0ProcConfig, procId );
    status = OMAP5430BENELLIPROC_setup (&ipu0ProcConfig, procId);
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_Platform_setup",
                             status,
                             "OMAP5430PROC_setup failed!");
    }
    else {
        core0Setup = TRUE;
        /* Create an instance of the Processor object for
         * OMAP5430 */
        OMAP5430BENELLIPROC_Params_init (NULL, &ipu0ProcParams, procId);

        handle->sHandles.ipu0.pHandle = OMAP5430BENELLIPROC_create (
                                                      procId,
                                                      &ipu0ProcParams);

        /* Create an instance of the Elf Loader object */
        ElfLoader_Params_init (NULL, &elfLoaderParams);
        handle->sHandles.ipu0.ldrHandle = ElfLoader_create (procId,
                                                          &elfLoaderParams);

        if (handle->sHandles.ipu0.pHandle == NULL) {
            status = Platform_E_FAIL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_setup",
                                 status,
                                 "OMAP5430PROC_create failed!");
        }
        else if (handle->sHandles.ipu0.ldrHandle ==  NULL) {
            status = Platform_E_FAIL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_setup",
                                 status,
                                 "Failed to create loader instance!");
        }
        else {
            /* Initialize parameters */
            ProcMgr_Params_init (NULL, &params);
            params.procHandle = handle->sHandles.ipu0.pHandle;
            params.loaderHandle = handle->sHandles.ipu0.ldrHandle;
            ldrHandle = params.loaderHandle;
            String_cpy (params.rstVectorSectionName,
                        RESETVECTOR_SYMBOL);
            handle->pmHandle = ProcMgr_create (procId, &params);
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

#ifndef IPC_SYSBIOS_SMP
    if (status >= 0) {
        /* Get MultiProc ID by name. */
        procId = MultiProc_getId ("CORE1");

        handle = &Platform_objects [procId];
        OMAP5430BENELLIPROC_get_config (&ipu1ProcConfig, procId );
        status = OMAP5430BENELLIPROC_setup (&ipu1ProcConfig, procId);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_setup",
                                 status,
                                 "OMAP5430PROC_setup failed!");
        }
        else {
            core1Setup = TRUE;
            /* Create an instance of the Processor object for
             * OMAP5430 */
            OMAP5430BENELLIPROC_Params_init(NULL, &ipu1ProcParams,procId);

            handle->sHandles.ipu1.pHandle = OMAP5430BENELLIPROC_create(procId,
                                                          &ipu1ProcParams);

            /* Don't create an instance of the Elf Loader - not needed */

            if (handle->sHandles.ipu1.pHandle == NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "OMAP5430PROC_create failed!");
            }
            else {
                /* Initialize parameters */
                ProcMgr_Params_init (NULL, &params);
                params.procHandle = handle->sHandles.ipu1.pHandle;
                /* Use the same loader handle as ipu0 to avoid ProcMgr errors */
                params.loaderHandle = ldrHandle;
                String_cpy (params.rstVectorSectionName,
                            RESETVECTOR_SYMBOL);
                handle->pmHandle = ProcMgr_create (procId, &params);
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
#endif

    if (status >= 0) {
        /* Get MultiProc ID by name. */
        procId = MultiProc_getId ("DSP");

        handle = &Platform_objects [procId];
        OMAP5430BENELLIPROC_get_config(&dspProcConfig, procId);
        status = OMAP5430BENELLIPROC_setup (&dspProcConfig, procId);
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_setup",
                                 status,
                                 "OMAP5430PROC_setup failed!");
        }
        else {
            dspSetup = TRUE;
            /* Create an instance of the Processor object for
                       * OMAP5430 */
            OMAP5430BENELLIPROC_Params_init (NULL, &dspProcParams, procId);

            handle->sHandles.dsp.pHandle = OMAP5430BENELLIPROC_create (
                                                          procId,
                                                          &dspProcParams);

            /* Create an instance of the Elf Loader object */
            ElfLoader_Params_init (NULL, &elfLoaderParams);
            handle->sHandles.dsp.ldrHandle = ElfLoader_create (procId,
                                                          &elfLoaderParams);

            if (handle->sHandles.dsp.pHandle == NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "OMAP5430PROC_create failed!");
            }
            else if (handle->sHandles.dsp.ldrHandle ==  NULL) {
                status = Platform_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_Platform_setup",
                                     status,
                                     "Failed to create loader instance!");
            }
            else {
                /* Initialize parameters */
                ProcMgr_Params_init (NULL, &params);
                params.procHandle = handle->sHandles.dsp.pHandle;
                params.loaderHandle = handle->sHandles.dsp.ldrHandle;
                String_cpy (params.rstVectorSectionName,
                            RESETVECTOR_SYMBOL);
                handle->pmHandle = ProcMgr_create (procId, &params);
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

    if (status < 0) {
        /* Cleanup in case of error */
#ifndef IPC_SYSBIOS_SMP
        procId = MultiProc_getId ("CORE1");
        handle = &Platform_objects [procId];
        if (handle->pmHandle) {
            ProcMgr_delete(&handle->pmHandle);
            handle->pmHandle = NULL;
        }
        if (handle->sHandles.ipu1.pHandle) {
            OMAP5430BENELLIPROC_delete(&handle->sHandles.ipu1.pHandle);
            handle->sHandles.ipu1.pHandle = NULL;
        }
        if (core1Setup)
            OMAP5430BENELLIPROC_destroy(procId);
#endif

        procId = MultiProc_getId (CORE0);

        handle = &Platform_objects [procId];
        if (handle->pmHandle) {
            ProcMgr_delete(&handle->pmHandle);
            handle->pmHandle = NULL;
        }
        if (handle->sHandles.ipu0.ldrHandle) {
            ElfLoader_delete(&handle->sHandles.ipu0.ldrHandle);
            handle->sHandles.ipu0.ldrHandle = NULL;
        }
        if (handle->sHandles.ipu0.pHandle) {
            OMAP5430BENELLIPROC_delete(&handle->sHandles.ipu0.pHandle);
            handle->sHandles.ipu0.pHandle = NULL;
        }
        if (core0Setup)
            OMAP5430BENELLIPROC_destroy(procId);

        procId = MultiProc_getId ("DSP");
        handle = &Platform_objects [procId];
        if (handle->pmHandle) {
            ProcMgr_delete(&handle->pmHandle);
            handle->pmHandle = NULL;
        }
        if (handle->sHandles.dsp.ldrHandle) {
            ElfLoader_delete(&handle->sHandles.dsp.ldrHandle);
            handle->sHandles.dsp.ldrHandle = NULL;
        }
        if (handle->sHandles.dsp.pHandle) {
            OMAP5430BENELLIPROC_delete(&handle->sHandles.dsp.pHandle);
            handle->sHandles.dsp.pHandle = NULL;
        }
        if (dspSetup)
            OMAP5430BENELLIPROC_destroy(procId);
    }
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
    /*UInt16          procId;*/

    /* Get MultiProc ID by name. */

    GT_0trace (curTrace, GT_ENTER, "_Platform_destroy");

#ifndef IPC_SYSBIOS_SMP
    /* ------------------------- ipu1 cleanup ------------------------------- */
    handle = &Platform_objects [MultiProc_getId ("CORE1")];
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

    if (handle->sHandles.ipu1.pHandle != NULL) {
        tmpStatus = OMAP5430BENELLIPROC_delete (&handle->sHandles.ipu1.pHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "OMAP5430PROC_delete failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }

    tmpStatus = OMAP5430BENELLIPROC_destroy (MultiProc_getId ("CORE1"));
    GT_assert (curTrace, (tmpStatus >= 0));
    if ((status >= 0) && (tmpStatus < 0)) {
        status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_Platform_destroy",
                             status,
                             "OMAP5430PROC_destroy failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }
#endif

    /* ------------------------- ipu0 cleanup ------------------------------- */
    handle = &Platform_objects [MultiProc_getId (CORE0)];
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

    if (handle->sHandles.ipu0.ldrHandle != NULL) {
        tmpStatus = ElfLoader_delete (&handle->sHandles.ipu0.ldrHandle);
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

    if (handle->sHandles.ipu0.pHandle != NULL) {
        tmpStatus = OMAP5430BENELLIPROC_delete (&handle->sHandles.ipu0.pHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "OMAP5430PROC_delete failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }

    tmpStatus = OMAP5430BENELLIPROC_destroy (MultiProc_getId (CORE0));
    GT_assert (curTrace, (tmpStatus >= 0));
    if ((status >= 0) && (tmpStatus < 0)) {
        status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_Platform_destroy",
                             status,
                             "OMAP5430PROC_destroy failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    /* ------------------------- dsp cleanup ------------------------------- */
    handle = &Platform_objects [MultiProc_getId ("DSP")];
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
        tmpStatus = OMAP5430BENELLIPROC_delete (&handle->sHandles.dsp.pHandle);
        GT_assert (curTrace, (tmpStatus >= 0));
        if ((status >= 0) && (tmpStatus < 0)) {
            status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_Platform_destroy",
                                 status,
                                 "OMAP5430PROC_delete failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }

    tmpStatus = OMAP5430BENELLIPROC_destroy (MultiProc_getId ("DSP"));
    GT_assert (curTrace, (tmpStatus >= 0));
    if ((status >= 0) && (tmpStatus < 0)) {
        status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_Platform_destroy",
                             status,
                             "OMAP5430PROC_destroy failed!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    GT_1trace (curTrace, GT_LEAVE, "_Platform_destroy", status);

    /*! @retval Platform_S_SUCCESS operation was successful */
    return status;
}


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
