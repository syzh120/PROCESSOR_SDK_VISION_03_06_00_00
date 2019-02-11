/*
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
 */


/*  ----------------------------------- Standard headers   */
#include <ti/syslink/Std.h>

/*  ----------------------------------- IPC module Headers   */
#include <ti/ipc/Ipc.h>
#include <_Ipc.h>
#include <IpcKnl.h>
#include <Platform.h>
#include <Bitops.h>
#include <RscTable.h>
#include <_MessageQCopy.h>
#include <ti/ipc/MessageQCopy.h>

#if defined(IPC_PLATFORM_VAYU)
#include <Gpt.h>
#endif

/*  ----------------------------------- utils Headers   */
#include <ti/syslink/inc/_MultiProc.h>
#include <ti/ipc/MultiProc.h>
#include <ti/syslink/utils/Gate.h>
#include <ti/syslink/utils/Trace.h>
#include <ti/syslink/utils/Cache.h>
#include <ti/syslink/utils/Memory.h>

#if defined(IPC_USE_IPU_PM)
#include <ipu_pm.h>
#endif

#if defined  (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 * Macros
 * =============================================================================
 */
/* Macro to make a correct module magic number with refCount */
#define Ipc_MAKE_MAGICSTAMP(x) ((SharedRegion_MODULEID << 16u) | (x))


/* =============================================================================
 * Enums & Structures
 * =============================================================================
 */

/* The structure used for reserving memory in SharedRegion */
typedef struct Ipc_Reserved {
    volatile Bits32    startedKey;
//    SharedRegion_SRPtr ipu_pm_sr_ptr; //Ramesh: Port from WinCe.
} Ipc_Reserved;


/*!
 *  head of the config list
 */
typedef struct Ipc_ConfigHead {
    volatile Bits32 first;
    /* Address of first config entry */
} Ipc_ConfigHead;


/*!
 *   This structure captures Configuration details of a module/instance
 *   written by a slave to synchornize with a remote slave/HOST
 */
typedef struct Ipc_ConfigEntry {
    volatile Bits32 remoteProcId;
    /* Remote processor identifier */
    volatile Bits32 localProcId;
    /* Config Entry owner processor identifier */
    volatile Bits32 tag;
    /* Unique tag to distinguish config from other config entries */
    volatile Bits32 size;
    /* Size of the config pointer */
    volatile Bits32 next;
    /* Address of next config entry  (In SRPtr format) */
} Ipc_ConfigEntry;

/*
 *  This structure defines the fields that are to be configured
 *  between the executing processor and a remote processor.
 */
typedef struct Ipc_Entry {
    UInt16 remoteProcId;            /* the remote processor id   */
    Bool    setup_ipu_pm;          //Ramesh: port from WinCE
} Ipc_Entry;

/*!
 *   Ipc instance structure.
 */
typedef struct Ipc_ProcEntry {
    Ptr        localConfigList;
    Ptr        remoteConfigList;
    Ptr        userObj;
    Bool       slave;
    Ipc_Entry  entry;
    Bool       isAttached;
} Ipc_ProcEntry;


/*!
 *  Module state structure
 */
typedef struct Ipc_Module_State {
    Int32         refCount;
    Ipc_Config    cfg;
    Ipc_ProcEntry procEntry [MultiProc_MAXPROCESSORS];
} Ipc_Module_State;


/* =============================================================================
 * Globals
 * =============================================================================
 */
static Ipc_Module_State Ipc_module_state = {
                                             .refCount = 0,
                                           };
static Ipc_Module_State * Ipc_module = &Ipc_module_state;


/* =============================================================================
 * APIs
 * =============================================================================
 */

/* attaches to a remote processor */
Int Ipc_attach (UInt16 remoteProcId)
{
    Int                     status = 0;
    IArg                    key;
    UInt32                  numVrings = 0;
    UInt32                  vringAddr = 0;
    ProcMgr_Handle          procHandle = NULL;

    GT_1trace (curTrace, GT_ENTER, "Ipc_attach", remoteProcId);

    GT_assert(curTrace,remoteProcId < MultiProc_INVALIDID);
    GT_assert(curTrace,remoteProcId != MultiProc_self());

    key = Gate_enterSystem ();
   /* Make sure its not already attached */
    if (Ipc_module->procEntry[remoteProcId].isAttached) {
        Ipc_module->procEntry[remoteProcId].isAttached++;
        Gate_leaveSystem (key);
        status = Ipc_S_ALREADYSETUP;
    }
    else {
        Gate_leaveSystem (key);

        status = ProcMgr_open(&procHandle, remoteProcId);
        if (status >= 0) {
            /* get IPC VRING information */
            status = RscTable_getInfo(remoteProcId, TYPE_VDEV, 0, NULL,
                                      NULL, &numVrings);
            if (status >= 0) {
                status = RscTable_getInfo(remoteProcId, TYPE_VDEV, 1,
                                          &vringAddr, NULL, NULL);
                if (status >= 0) {
                    status = MessageQCopy_attach(remoteProcId,
                                                 (Ptr)vringAddr, 0);
                    if (status >= 0) {
                        status = RscTable_setStatus(remoteProcId, 7);
                    }
                }
            }

            if (status >= 0) {
                /* flush the resource table to device memory */
                status = RscTable_update(remoteProcId, procHandle);
            }
            ProcMgr_close(&procHandle);
        }

#if defined(IPC_USE_IPU_PM) && defined(IPC_PLATFORM_OMAP5430)
        if (status >= 0) {
            status = ipu_pm_attach(remoteProcId);
            if (status < 0) {
                MessageQCopy_detach(remoteProcId);
            }
        }
#endif

#if !defined(IPC_DISABLE_WATCHDOG) && defined(IPC_PLATFORM_VAYU)
        if (status >= 0) {
            status = Gpt_wdt_attach(remoteProcId);
            if (status < 0) {
                MessageQCopy_detach(remoteProcId);
            }
        }
#endif

        if (status >= 0) {
            key = Gate_enterSystem ();
            Ipc_module->procEntry[remoteProcId].isAttached++;
            Gate_leaveSystem (key);
        }
    }
    GT_1trace (curTrace, GT_LEAVE, "Ipc_attach", status);

    return  (status);
}


/* detaches from a remote processor */
Int Ipc_detach (UInt16 remoteProcId)
{
    Int                     status = 0;
    IArg                    key;
    GT_1trace (curTrace, GT_ENTER, "Ipc_detach", remoteProcId);

    key = Gate_enterSystem ();
    if (Ipc_module->procEntry[remoteProcId].isAttached > 1) {
        /* Only detach if attach count reaches 1 */
        Ipc_module->procEntry[remoteProcId].isAttached--;
        Gate_leaveSystem (key);
        status = Ipc_S_BUSY;
    }
    else if (Ipc_module->procEntry[remoteProcId].isAttached == 0) {
        /* If already detached, then return fail */
        Gate_leaveSystem (key);
        status = Ipc_E_FAIL;
    }
    else {
        Gate_leaveSystem (key);

#if defined(IPC_USE_IPU_PM) && defined(IPC_PLATFORM_OMAP5430)
        status = ipu_pm_detach (remoteProcId);
#endif

#if !defined(IPC_DISABLE_WATCHDOG) && defined(IPC_PLATFORM_VAYU)
        status = Gpt_wdt_detach(remoteProcId);
#endif

        status = MessageQCopy_detach (remoteProcId);

        key = Gate_enterSystem ();
        Ipc_module->procEntry[remoteProcId].isAttached--;
        Gate_leaveSystem (key);
    }

    GT_1trace (curTrace, GT_LEAVE, "Ipc_detach", status);

    return  (status);
}

/*
 *  ======== Ipc_getConfig ========
 */
Void Ipc_getConfig (Ipc_Config * cfgParams)
{
    IArg key;

    GT_1trace (curTrace, GT_ENTER, "Ipc_getConfig", cfgParams);

    GT_assert (curTrace, (cfgParams != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (cfgParams == NULL) {
        /* No retVal since this is a Void function. */
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "Ipc_getConfig",
                             Ipc_E_INVALIDARG,
                             "Argument of type (Ipc_Config *) passed "
                             "is null!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        key = Gate_enterSystem ();
        if (Ipc_module->refCount != 0) {
            Memory_copy ((Ptr) cfgParams,
                         (Ptr) &Ipc_module->cfg,
                         sizeof (Ipc_Config));
        }
        Gate_leaveSystem (key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "Ipc_getConfig");
}


/* Sets up Ipc for this processor. */
Int Ipc_setup (const Ipc_Config * cfg)
{
    Int             status = Ipc_S_SUCCESS;
    Ipc_Config      tmpCfg;
    IArg            key;
    Int             i;

    GT_1trace (curTrace, GT_ENTER, "Ipc_setup", cfg);

    key = Gate_enterSystem ();
    Ipc_module->refCount++;

    /* This sets the refCount variable is not initialized, upper 16 bits is
     * written with module Id to ensure correctness of refCount variable.
     */
    if (Ipc_module->refCount > 1) {
        status = Ipc_S_ALREADYSETUP;
        GT_0trace (curTrace,
                   GT_2CLASS,
                   "Ipc Module already initialized!");
        Gate_leaveSystem (key);
    }
    else {
        Gate_leaveSystem (key);
        if (cfg == NULL) {
            Ipc_getConfig (&tmpCfg);
            cfg = &tmpCfg;
        }

        /* Copy the cfg */
        Memory_copy ((Ptr) &Ipc_module->cfg,
                     (Ptr) cfg,
                     sizeof (Ipc_Config));

        status = Platform_setup ((Ipc_Config *)cfg);
        if (status < 0) {
            key = Gate_enterSystem ();
            Ipc_module->refCount--;
            Gate_leaveSystem (key);
            status = Ipc_E_FAIL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "Ipc_setup",
                                 status,
                                 "Platform_setup failed!");
        }

        /* Following can be done regardless of status */
        for (i = 0; i < MultiProc_getNumProcessors (); i++) {
            Ipc_module->procEntry [i].isAttached = FALSE;
        }
    }

    GT_1trace (curTrace, GT_LEAVE, "Ipc_setup", status);

    /*! @retval Ipc_S_SUCCESS Operation successful */
    return status;
}


/* Destroys Ipc for this processor. */
Int
Ipc_destroy (Void)
{
    Int status = Ipc_S_SUCCESS;
    IArg  key;

    GT_0trace (curTrace, GT_ENTER, "Ipc_destroy");

    key = Gate_enterSystem ();
    Ipc_module->refCount--;
#if !defined(IPC_BUILD_OPTIMIZE)
    if (Ipc_module->refCount < 0) {
        Gate_leaveSystem (key);
        /*! @retval Ipc_E_INVALIDSTATE Module was not initialized */
        status = Ipc_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "Ipc_destroy",
                             status,
                             "Module was not initialized!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        if (Ipc_module->refCount == 0) {
            Gate_leaveSystem (key);
            status = Platform_destroy ();
            if (status < 0) {
                status = Ipc_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "Ipc_destroy",
                                     status,
                                     "Platform_destroy failed!");
            }
        }
        else {
            Gate_leaveSystem (key);
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "Ipc_destroy", status);

    /*! @retval Ipc_S_SUCCESS Operation successful */
    return status;
}


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
