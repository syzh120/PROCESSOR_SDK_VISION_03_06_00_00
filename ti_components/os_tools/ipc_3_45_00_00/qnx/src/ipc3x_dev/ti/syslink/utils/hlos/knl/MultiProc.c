/*
 *  @file   MultiProc.c
 *
 *  @brief      Handles processor id management in multi processor systems.Used
 *              by all modules which need processor ids for their oprations.
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


/* Standard headers */
#include <ti/syslink/Std.h>

/* OSAL & Utils headers */
#include <ti/syslink/utils/Trace.h>
#include <ti/syslink/utils/Memory.h>
#include <ti/syslink/utils/String.h>
#include <Bitops.h>

/* Module level headers */
#include <_MultiProc.h>
#include <ti/ipc/MultiProc.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/* Macro to make a correct module magic number with refCount */
#define MultiProc_MAKE_MAGICSTAMP(x) ((MultiProc_MODULEID << 12u) | (x))

/*!
 *  @brief  MultiProc Module state object
 */
typedef struct MultiProc_ModuleObject_tag {
    MultiProc_Config cfg;
    /*!< Notify configuration structure */
    MultiProc_Config defCfg;
    /*!< Default module configuration */
    Atomic           refCount;
    /* Reference count */
    UInt16           id;
    /* Local processor ID */
} MultiProc_ModuleObject;


/* =============================================================================
 *  Extern declarations
 * =============================================================================
 */
#if !defined(IPC_BUILD_DEBUG)
static
#endif /* if !defined(IPC_BUILD_DEBUG) */
MultiProc_ModuleObject MultiProc_state = {
    .defCfg.numProcessors     = 0u,
    .defCfg.id                = MultiProc_INVALIDID,
    .id                       = MultiProc_INVALIDID
};

/*!
 *  @var    MultiProc_module
 *
 *  @brief  Pointer to the MultiProc module state.
 */
#if !defined(IPC_BUILD_DEBUG)
static
#endif /* if !defined(IPC_BUILD_DEBUG) */
MultiProc_ModuleObject * MultiProc_module = &MultiProc_state;


/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Get the default configuration for the MultiProc module. */
Void
MultiProc_getConfig (MultiProc_Config * cfg)
{
    GT_1trace (curTrace, GT_ENTER, "MultiProc_getConfig", cfg);

    GT_assert (curTrace, (cfg != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (EXPECT_FALSE (cfg == NULL)) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MultiProc_getConfig",
                             MultiProc_E_INVALIDARG,
                             "Argument of type (MultiProc_Config *) passed "
                             "is null!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        if (EXPECT_TRUE (  Atomic_cmpmask_and_lt (&(MultiProc_module->refCount),
                                                  MultiProc_MAKE_MAGICSTAMP(0),
                                                  MultiProc_MAKE_MAGICSTAMP(1))
                        == TRUE)) {
            /* (If setup has not yet been called) */
            Memory_copy (cfg,
                         &MultiProc_module->defCfg,
                         sizeof (MultiProc_Config));
        }
        else {
            Memory_copy (cfg,
                         &MultiProc_module->cfg,
                         sizeof (MultiProc_Config));
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "MultiProc_getConfig");
}


/* Setup the MultiProc module. */
Int
MultiProc_setup (MultiProc_Config * cfg)
{
    Int              status = MultiProc_S_SUCCESS;
    MultiProc_Config tmpCfg;

    GT_1trace (curTrace, GT_ENTER, "MultiProc_setup", cfg);

    /* This sets the refCount variable is not initialized, upper 16 bits is
     * written with module Id to ensure correctness of refCount variable.
     */
    Atomic_cmpmask_and_set (&MultiProc_module->refCount,
                            MultiProc_MAKE_MAGICSTAMP(0),
                            MultiProc_MAKE_MAGICSTAMP(0));

    if (   Atomic_inc_return (&MultiProc_module->refCount)
        != MultiProc_MAKE_MAGICSTAMP(1u)) {
        status = MultiProc_S_ALREADYSETUP;
        GT_0trace (curTrace,
                   GT_2CLASS,
                   "MultiProc Module already initialized!");
    }
    else {
        if (cfg == NULL) {
            MultiProc_getConfig (&tmpCfg);
            cfg = &tmpCfg;
        }

        Memory_copy (&MultiProc_module->cfg, cfg, sizeof (MultiProc_Config));
        MultiProc_module->id = cfg->id;
    }

    GT_1trace (curTrace, GT_LEAVE, "MultiProc_setup", status);

    /*! @retval MultiProc_S_SUCCESS Operation successful */
    return (status);
}


/* Destroy the MultiProc module. */
Int
MultiProc_destroy (Void)
{
    Int status = MultiProc_S_SUCCESS;

    GT_0trace (curTrace, GT_ENTER, "MultiProc_destroy");

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(MultiProc_module->refCount),
                                  MultiProc_MAKE_MAGICSTAMP(0),
                                  MultiProc_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval MultiProc_E_INVALIDSTATE Module was not initialized */
        status = MultiProc_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MultiProc_destroy",
                             status,
                             "Module was not initialized!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        Atomic_dec_return (&MultiProc_module->refCount);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "MultiProc_destroy", status);

    /*! @retval MultiProc_S_SUCCESS Operation successful */
    return (status);
}


/* Function to set Local processor Id */
Int
MultiProc_setLocalId (UInt16 id)
{
    Int status = MultiProc_S_SUCCESS;

    GT_1trace (curTrace, GT_ENTER, "MultiProc_setLocalId", id);

#if !defined(IPC_BUILD_OPTIMIZE)
    if (EXPECT_FALSE (   Atomic_cmpmask_and_lt (&(MultiProc_module->refCount),
                                                MultiProc_MAKE_MAGICSTAMP(0),
                                                MultiProc_MAKE_MAGICSTAMP(1))
                      == TRUE)) {
        status = MultiProc_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MultiProc_setLocalId",
                             status,
                             "Module was not initialized!");
    }
    else if (EXPECT_FALSE (id >= MultiProc_module->cfg.numProcessors)) {
        status = MultiProc_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MultiProc_setLocalId",
                             MultiProc_E_INVALIDARG,
                             "ID cannot be greater than or equal to"
                             " numProcessors");
    }
    else if (EXPECT_FALSE (MultiProc_module->id != MultiProc_INVALIDID)) {
        status = MultiProc_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MultiProc_setLocalId",
                             MultiProc_E_INVALIDARG,
                             "Cannot change the ID after module"
                             " startup");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        MultiProc_module->id = id;
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "MultiProc_setLocalId", status);

    return (status);
}


/* Function to get proccesor Id from proccessor name. */
UInt16
MultiProc_getId (String name)
{
    Bool   found = FALSE;
    UInt32 id    = MultiProc_INVALIDID;
    Int    i;

    GT_1trace (curTrace, GT_ENTER, "MultiProc_getId", name);

#if !defined(IPC_BUILD_OPTIMIZE)
    if (EXPECT_FALSE (   Atomic_cmpmask_and_lt (&(MultiProc_module->refCount),
                                                 MultiProc_MAKE_MAGICSTAMP(0),
                                                 MultiProc_MAKE_MAGICSTAMP(1))
                       == TRUE)) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MultiProc_getId",
                             MultiProc_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* If the name is NULL, simply return the local id */
        if (EXPECT_FALSE (name == NULL)) {
#if !defined(IPC_BUILD_OPTIMIZE)
            if (EXPECT_FALSE (MultiProc_module->id == MultiProc_INVALIDID)) {
                GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "MultiProc_getId",
                                 MultiProc_E_INVALIDSTATE,
                                 "MultiProc_localId not set to proper value");
            }
            else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                GT_assert (curTrace,
                           (MultiProc_module->id != MultiProc_INVALIDID));
                id = MultiProc_module->id;
                found = TRUE;
#if !defined(IPC_BUILD_OPTIMIZE)
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
        else {
            for (i = 0; i < MultiProc_module->cfg.numProcessors ; i++) {
                if (   String_cmp (name, &MultiProc_module->cfg.nameList [i][0])
                    == 0) {
                    id = i;
                    found = TRUE;
                    break;
                }
            }

#if !defined(IPC_BUILD_OPTIMIZE)
            if (EXPECT_FALSE (!found)) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "MultiProc_getId",
                                     MultiProc_E_NOTFOUND,
                                     "Processor name not found");
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_assert (curTrace, (found == TRUE));

    GT_1trace (curTrace, GT_LEAVE, "MultiProc_getId", id);

    return (id);
}


/* Function to get name from processor id. */
String
MultiProc_getName (UInt16 id)
{
    String name = NULL;

    GT_1trace (curTrace, GT_ENTER, "MultiProc_getName", id);

    GT_assert (curTrace, (id < MultiProc_module->cfg.numProcessors));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (EXPECT_FALSE (   Atomic_cmpmask_and_lt (&(MultiProc_module->refCount),
                                                MultiProc_MAKE_MAGICSTAMP(0),
                                                MultiProc_MAKE_MAGICSTAMP(1))
                      == TRUE)) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MultiProc_getName",
                             MultiProc_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if (EXPECT_FALSE (id >= MultiProc_module->cfg.numProcessors)) {
        GT_setFailureReason (curTrace,
                    GT_4CLASS,
                    "MultiProc_getName",
                    MultiProc_E_INVALIDARG,
                    "Processor id is not less than numProcessors");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        name = MultiProc_module->cfg.nameList [id];
        GT_1trace (curTrace, GT_1CLASS, "MultiProc_getName [%s]", name);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "MultiProc_getName");

    return (name);
}


/* Function to get maximum proc Id in the system. */
UInt16
MultiProc_getNumProcessors (Void)
{
    GT_0trace (curTrace, GT_ENTER, "MultiProc_getNumProcessors");
    GT_1trace (curTrace,
               GT_LEAVE,
               "MultiProc_getNumProcessors",
               MultiProc_module->cfg.numProcessors);

    /* Don't put any checks here, since this needs to be very fast. */

    return (MultiProc_module->cfg.numProcessors);
}


/* Return Id of current processor */
UInt16
MultiProc_self (Void)
{
    GT_0trace (curTrace, GT_ENTER, "MultiProc_self");

    GT_1trace (curTrace, GT_LEAVE, "MultiProc_self", MultiProc_module->id);

    /* Don't put any checks here, since this needs to be very fast. */

    return (MultiProc_module->id);
}


/* Determines the offset for any two processors. */
UInt
MultiProc_getSlot (UInt16 remoteProcId)
{
    UInt slot = 0u;
    UInt i;
    UInt j;
    UInt smallId;
    UInt largeId;

    GT_1trace (curTrace, GT_ENTER, "MultiProc_getSlot", remoteProcId);

#if !defined(IPC_BUILD_OPTIMIZE)
    if (EXPECT_FALSE (   Atomic_cmpmask_and_lt (&(MultiProc_module->refCount),
                                                MultiProc_MAKE_MAGICSTAMP(0),
                                                MultiProc_MAKE_MAGICSTAMP(1))
                      == TRUE)) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "MultiProc_getSlot",
                             MultiProc_E_INVALIDSTATE,
                             "Module was not initialized!");
    }
    else if (EXPECT_FALSE (   remoteProcId
                           >= MultiProc_module->cfg.numProcessors)) {
        GT_setFailureReason (curTrace,
                    GT_4CLASS,
                    "MultiProc_getSlot",
                    MultiProc_E_INVALIDARG,
                    "Processor id is not less than numProcessors");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        if (remoteProcId > MultiProc_self ()) {
            smallId = MultiProc_self ();
            largeId = remoteProcId;
        }
        else {
            largeId = MultiProc_self ();
            smallId = remoteProcId;
        }

        /* determine what offset to create for the remote Proc Id */
        for (i = 0; i < MultiProc_module->cfg.numProcessors; i++) {
            for (j = i + 1; j < MultiProc_module->cfg.numProcessors; j++) {
                if ((smallId == i) && (largeId == j)) {
                    break;
                }
                slot++;
            }
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "MultiProc_getSlot", slot);

    return (slot);
}


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */


