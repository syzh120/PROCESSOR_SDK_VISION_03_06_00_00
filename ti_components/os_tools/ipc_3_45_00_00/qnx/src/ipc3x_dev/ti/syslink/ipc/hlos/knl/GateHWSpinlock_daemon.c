/*
 * Copyright (c) 2013-2015, Texas Instruments Incorporated
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
 *  ======== GateHWSpinlock_daemon.c ========
 */

/* Standard headers */
#include <ti/syslink/Std.h>
/*QNX specific header include */
#include <proto.h>
#include <errno.h>
#include <unistd.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
/* Utilities & OSAL headers */
#include <ti/ipc/MultiProc.h>
#include <ti/syslink/utils/GateMutex.h>
#include <ti/syslink/utils/IGateProvider.h>
#include <IGateMPSupport.h>
#include <IObject.h>
#include <ti/syslink/utils/Memory.h>
#include <ti/syslink/utils/Trace.h>
#include <Bitops.h>
#include <ti/syslink/utils/List.h>


/* Module level headers */
#include <ti/syslink/utils/String.h>

#include <ti/syslink/utils/GateSpinlock.h>
#include <_GateHWSpinlock.h>
#include <GateHWSpinlock.h>
#include <HwSpinLockCmdBase.h>


#if defined (__cplusplus)
extern "C" {
#endif

#ifdef IPC_PLATFORM_VAYU
/*!
 *  @var    GateHWSpinlock_state
 *
 *  @brief  GateHWSpinlock Module state object.
 */
#if !defined(IPC_BUILD_DEBUG)
static
#endif /* if !defined(IPC_BUILD_DEBUG) */
extern GateHWSpinlock_Module_State _GateHWSpinlock_state;
GateHWSpinlock_Module_State * GateHWSpinlock_module = &_GateHWSpinlock_state;


/* =============================================================================
 * APIS
 * =============================================================================
 */
/*!
 *  @brief      Get the default configuration for the GateHWSpinlock module.
 *
 *              This function can be called by the application to get their
 *              configuration parameter to GateHWSpinlock_setup filled in by
 *              the GateHWSpinlock module.
 *
 *  @param      cfgParams  Pointer to the GateHWSpinlock module configuration
 *                         structure in which the module config is to be
 *                         returned.
 */
Void GateHWSpinlock_getConfig(GateHWSpinlock_Config * cfgParams)
{
    GT_1trace (curTrace, GT_ENTER, "GateHWSpinlock_getConfig", cfgParams);

    GT_assert (curTrace, (cfgParams != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (cfgParams == NULL) {
        /* No retVal since this is a Void function. */
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "GateHWSpinlock_getConfig",
                             GateHWSpinlock_E_INVALIDARG,
                             "Argument of type (GateHWSpinlock_Config *) passed "
                             "is null!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        Memory_copy((Ptr) cfgParams,
                     (Ptr) &GateHWSpinlock_module->cfg,
                     sizeof (GateHWSpinlock_Config));
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_ENTER, "GateHWSpinlock_getConfig");

    return;
}

/*!
 *  @brief      Setup the GateHWSpinlock module.
 *
 *              This function sets up the GateHWSpinlock module. This function
 *              must be called before any other instance-level APIs can be
 *              invoked.
 *              Module-level configuration needs to be provided to this
 *              function.
 *
 *  @param      cfg   GateHWSpinlock module configuration. Cannot be NULL.
 */
Int32 GateHWSpinlock_setup(const GateHWSpinlock_Config * cfg)
{
    Int32                 status = GateHWSpinlock_S_SUCCESS;

    GT_1trace (curTrace, GT_ENTER, "GateHWSpinlock_setup", cfg);

    if (cfg == NULL) {
        return (GateHWSpinlock_E_INVALIDARG);
    }

    /* Copy the cfg */
    Memory_copy((Ptr) &GateHWSpinlock_module->cfg,
                 (Ptr) cfg,
                 sizeof (GateHWSpinlock_Config));

    GateHWSpinlock_module->numLocks = cfg->numLocks;

    GT_1trace (curTrace, GT_LEAVE, "GateHWSpinlock_setup", status);

    /*! @retval GateHWSpinlock_S_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to destroy the GateHWSpinlock module.
 */
Int GateHWSpinlock_destroy(Void)
{
    Int32 status = GateHWSpinlock_S_SUCCESS;

    GT_0trace (curTrace, GT_ENTER, "GateHWSpinlock_destroy");
    /* Clear cfg area */
    Memory_set((Ptr) &GateHWSpinlock_module->cfg,
                0,
                sizeof (GateHWSpinlock_Config));

    GT_1trace (curTrace, GT_LEAVE, "GateHWSpinlock_destroy", status);

    /*! @retval GateHWSpinlock_S_SUCCESS Operation successful */
    return status;
}
#else
/*************************************************************************
 *  Code below is kept for legacy HWSpinlock module
 *  Deprecated and should be removed at some point along with the module
 ************************************************************************/
/* =============================================================================
 * Macros
 * =============================================================================
 */

/* Macro to make a correct module magic number with refCount */
#define GATEHWSPINLOCK_MAKE_MAGICSTAMP(x) (  (GateHWSpinlock_MODULEID << 12u)  \
                                           | (x))

static GateHWSpinlock_Object * GateHWSpinlock_firstObject = NULL;
static int token;

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

/* =============================================================================
 * Structures & Enums
 * =============================================================================
 */
/* structure for GateHWSpinlock module state */
typedef struct GateHWSpinlock_Module_State {
    Atomic                refCount;
    /* Reference count */
    GateHWSpinlock_Config cfg;
    /* Current config values */
    GateHWSpinlock_Config defaultCfg;
    /* default config values */
    UInt32 *              baseAddr;
    /* Base address of lock registers */
    UInt32                numLocks;
    /*!< Maximum number of locks */
} GateHWSpinlock_Module_State;

/* Structure defining internal object for the Gate Peterson.*/
typedef struct keyRec{
    IArg key;
    struct keyRec* next;
}keyRecs;

struct GateHWSpinlock_Object {
    IGateProvider_SuperObject; /* For inheritance from IGateProvider */
    IOBJECT_SuperObject;       /* For inheritance for IObject */
    UInt                        lockNum;
    UInt                        nested;
    IGateProvider_Handle        localGate;
    Int                         token;
    UInt                        pid;
    keyRecs                     *keys;
};


/* =============================================================================
 * Globals
 * =============================================================================
 */
/*!
 *  @var    GateHWSpinlock_state
 *
 *  @brief  GateHWSpinlock Module state object.
 */
#if !defined(IPC_BUILD_DEBUG)
static
#endif /* if !defined(IPC_BUILD_DEBUG) */
GateHWSpinlock_Module_State GateHWSpinlock_state =
{
    .defaultCfg.numLocks           = 128,
    .defaultCfg.baseAddr           = 0,
    .defaultCfg.offset             = 0,
    .defaultCfg.size               = 0,
    .numLocks                      = 128u,
};

/*!
 *  @var    GateHWSpinlock_state
 *
 *  @brief  GateHWSpinlock Module state object.
 */
#if !defined(IPC_BUILD_DEBUG)
static
#endif /* if !defined(IPC_BUILD_DEBUG) */
GateHWSpinlock_Module_State * GateHWSpinlock_module = &GateHWSpinlock_state;


/* =============================================================================
 * APIS
 * =============================================================================
 */
/*!
 *  @brief      Get the default configuration for the GateHWSpinlock module.
 *
 *              This function can be called by the application to get their
 *              configuration parameter to GateHWSpinlock_setup filled in by
 *              the GateHWSpinlock module with the default parameters. If the
 *              user does not wish to make any change in the default parameters,
 *              this API is not required to be called.
 *
 *  @param      cfgParams  Pointer to the GateHWSpinlock module configuration
 *                         structure in which the default config is to be
 *                         returned.
 *
 *  @sa         GateHWSpinlock_setup
 */

Void
GateHWSpinlock_getConfig (GateHWSpinlock_Config * cfgParams)
{
    GT_1trace (curTrace, GT_ENTER, "GateHWSpinlock_getConfig", cfgParams);

    GT_assert (curTrace, (cfgParams != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (cfgParams == NULL) {
        /* No retVal since this is a Void function. */
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "GateHWSpinlock_getConfig",
                             GateHWSpinlock_E_INVALIDARG,
                             "Argument of type (GateHWSpinlock_Config *) passed "
                             "is null!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* This sets the refCount variable is not initialized, upper 16 bits is
         * written with module Id to ensure correctness of refCount variable.
         */
        Atomic_cmpmask_and_set (&GateHWSpinlock_module->refCount,
                                GATEHWSPINLOCK_MAKE_MAGICSTAMP(0),
                                GATEHWSPINLOCK_MAKE_MAGICSTAMP(0));

        if (Atomic_cmpmask_and_lt (&(GateHWSpinlock_module->refCount),
                                   GATEHWSPINLOCK_MAKE_MAGICSTAMP(0),
                                   GATEHWSPINLOCK_MAKE_MAGICSTAMP(1))
            == TRUE) {
            Memory_copy ((Ptr) cfgParams,
                         (Ptr) &GateHWSpinlock_module->defaultCfg,
                         sizeof (GateHWSpinlock_Config));
        }
        else {
            Memory_copy ((Ptr) cfgParams,
                         (Ptr) &GateHWSpinlock_module->cfg,
                         sizeof (GateHWSpinlock_Config));
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_ENTER, "GateHWSpinlock_getConfig");
}

/*!
 *  @brief      Setup the GateHWSpinlock module.
 *
 *              This function sets up the GateHWSpinlock module. This function
 *              must be called before any other instance-level APIs can be
 *              invoked.
 *              Module-level configuration needs to be provided to this
 *              function. If the user wishes to change some specific config
 *              parameters, then GateHWSpinlock_getConfig can be called to get
 *              the configuration filled with the default values. After this,
 *              only the required configuration values can be changed. If the
 *              user does not wish to make any change in the default parameters,
 *              the application can simply call GateHWSpinlock_setup with NULL
 *              parameters. The default parameters would get automatically used.
 *
 *  @param      cfg   Optional GateHWSpinlock module configuration. If provided
 *                    as NULL, default configuration is used.
 *
 *  @sa         GateHWSpinlock_destroy, GateHWSpinlock_getConfig
 */
Int32
GateHWSpinlock_setup (const GateHWSpinlock_Config * cfg)
{
    Int32                 status = GateHWSpinlock_S_SUCCESS;
    GateHWSpinlock_Config tmpCfg;

    GT_1trace (curTrace, GT_ENTER, "GateHWSpinlock_setup", cfg);

    /* This sets the refCount variable is not initialized, upper 16 bits is
     * written with module Id to ensure correctness of refCount variable.
     */
    Atomic_cmpmask_and_set (&GateHWSpinlock_module->refCount,
                            GATEHWSPINLOCK_MAKE_MAGICSTAMP(0),
                            GATEHWSPINLOCK_MAKE_MAGICSTAMP(0));

    if (Atomic_inc_return (&GateHWSpinlock_module->refCount)
                           != GATEHWSPINLOCK_MAKE_MAGICSTAMP(1u)) {
        status = GateHWSpinlock_S_ALREADYSETUP;
        GT_0trace (curTrace,
                   GT_2CLASS,
                   "GateHWSpinlock Module already initialized!");
    }
    else {
        if (cfg == NULL) {
            GateHWSpinlock_getConfig (&tmpCfg);
            cfg = &tmpCfg;
        }

        /* Copy the cfg */
        Memory_copy ((Ptr) &GateHWSpinlock_module->cfg,
                     (Ptr) cfg,
                     sizeof (GateHWSpinlock_Config));
        GateHWSpinlock_module->baseAddr = (Ptr)cfg->baseAddr;
        GateHWSpinlock_module->numLocks = cfg->numLocks;
        //GateHWSpinlock_locksinit();
    }

    GT_1trace (curTrace, GT_LEAVE, "GateHWSpinlock_setup", status);

    /*! @retval GateHWSpinlock_S_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to destroy the GateHWSpinlock module.
 *
 *  @sa         GateHWSpinlock_setup
 */
Int32
GateHWSpinlock_destroy (void)
{
    Int32 status = GateHWSpinlock_S_SUCCESS;

    GT_0trace (curTrace, GT_ENTER, "GateHWSpinlock_destroy");

#if !defined(IPC_BUILD_OPTIMIZE)
    if (Atomic_cmpmask_and_lt (&(GateHWSpinlock_module->refCount),
                               GATEHWSPINLOCK_MAKE_MAGICSTAMP(0),
                               GATEHWSPINLOCK_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval GateHWSpinlock_E_INVALIDSTATE Module was not initialized */
        status = GateHWSpinlock_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "GateHWSpinlock_destroy",
                             status,
                             "Module was not initialized!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        if (Atomic_dec_return (&GateHWSpinlock_module->refCount)
            == GATEHWSPINLOCK_MAKE_MAGICSTAMP(0)) {
            if(!GateHWSpinlock_deleteAll()) {
                GT_0trace (curTrace, GT_3CLASS,
                           "GateHWSpinlock_destroy: Deleted all lock objects");
            }
            else {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "GateHWSpinlock_destroy",
                                     status,
                                     "Couldn't clean all lock objects");
            }

            /* Clear cfg area */
            Memory_set ((Ptr) &GateHWSpinlock_module->cfg,
                        0,
                        sizeof (GateHWSpinlock_Config));
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "GateHWSpinlock_destroy", status);

    /*! @retval GateHWSpinlock_S_SUCCESS Operation successful */
    return status;
}

/*!
 *  @brief      Function to return the number of instances configured in the
 *              module.
 *
 */
UInt32 GateHWSpinlock_getNumInstances()
{
    return (GateHWSpinlock_module->numLocks);
}

/* Initialize the locks */
Void GateHWSpinlock_locksinit()
{
    UInt32  i;

    for (i = 0; i < GateHWSpinlock_module->numLocks; i++) {
        GateHWSpinlock_module->baseAddr[i] = 0;
    }
}


/*
 *  ======== GateHWSpinlock_Instance_init ========
 */
Int GateHWSpinlock_Instance_init (      GateHWSpinlock_Object *obj,
                                        IGateMPSupport_LocalProtect localProtect,
                                  const GateHWSpinlock_Params *params)
{

    IGateProvider_ObjectInitializer (obj, GateHWSpinlock);

    /* Assert that params->resourceId is valid */
    if (params->resourceId >= GateHWSpinlock_module->numLocks) {

        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "GateHWSpinlock_Instance_init",
                             GateHWSpinlock_E_FAIL,
                             "params->resourceId >= GateHWSpinlock_numLocks!");
        return -1;
    }

    /* Create the local gate */
    if(localProtect == IGateMPSupport_LocalProtect_NONE)
        obj->localGate = IGateProvider_NULL;
    else if(localProtect == GateMP_LocalProtect_INTERRUPT)
        obj->localGate = Gate_systemHandle;
    else
        obj->localGate = (IGateProvider_Handle)GateMutex_create (NULL, NULL);

    if (obj->localGate == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "GateHWSpinlock_Instance_init",
                             GateHWSpinlock_E_FAIL,
                             "GateMP_createLocal failed!");
        return -2;
    }

    obj->lockNum = params->resourceId;
    obj->nested   = 0;
    obj->keys = NULL;

    return (0);
}

/*
 *  ======== GatePeterson_Instance_finalize ========
 */
Void GateHWSpinlock_Instance_finalize(GateHWSpinlock_Object *obj, Int status)
{
    keyRecs *rec;
    keyRecs *rec_prev;

    if(obj->keys) {
        rec_prev = obj->keys->next;
        while(rec_prev){
            rec = rec_prev->next;
            Memory_free (NULL, rec_prev, sizeof (keyRecs));
            rec_prev = rec;
        }
        obj->keys->next = NULL;
        if(obj->nested > 0)
            obj->nested = 1;
        GateHWSpinlock_leave(obj, obj->keys->key);
    }
}

/*
 *  ======== GateHWSpinlock_enter ========
 */
IArg GateHWSpinlock_enter(GateHWSpinlock_Object *obj)
{
    keyRecs *rec;
    keyRecs *prevRec;
    int count = 10;
    volatile UInt32 *baseAddr = (volatile UInt32 *)
                                             GateHWSpinlock_module->baseAddr;
    if(obj->keys == NULL) {
        obj->keys = Memory_alloc (NULL,
                                    sizeof (keyRecs),
                                    0,
                                    NULL);
        obj->keys->next = NULL;
        rec = obj->keys;
        prevRec = NULL;
    }
    else {
        rec = obj->keys;
        while(rec->next)
            rec = rec->next;
        rec->next = Memory_alloc (NULL,
                                  sizeof (keyRecs),
                                  0,
                                  NULL);
        rec->next->next = NULL;
        prevRec = rec;
        rec = rec->next;
    }

    rec->key = IGateProvider_enter(obj->localGate);

    /* If the gate object has already been entered, return the nested value */
    obj->nested++;
    if (obj->nested > 1) {
        return (rec->key);
    }

    /* Enter the spinlock */
    while (-- count) {
        if (baseAddr[obj->lockNum] == 0) {
            break;
        }
    }
    if(!count) {
        obj->nested--;
        IGateProvider_leave(obj->localGate, rec->key);
        if(!prevRec) {
            Memory_free (NULL, obj->keys, sizeof (keyRecs));
            obj->keys = NULL;
        }
        else {
            Memory_free (NULL, rec, sizeof (keyRecs));
            prevRec->next = NULL;
        }
        return (IArg)(-1);
    }
    return (rec->key);
}

/*
 *  ======== GateHWSpinlock_leave ========
 */
Int GateHWSpinlock_leave(GateHWSpinlock_Object *obj, IArg key)
{
    keyRecs *rec;
    keyRecs *rec_prev;
    volatile UInt32 *baseAddr = (volatile UInt32 *)
                                            GateHWSpinlock_module->baseAddr;
    int status = -1;

    if(obj->keys && obj->keys->key == key) {
        rec = obj->keys;
        obj->keys = obj->keys->next;
        Memory_free (NULL, rec, sizeof (keyRecs));
        status = 0;
    }
    else {
        rec_prev = obj->keys;
        rec = rec_prev->next;
        while(rec) {
            if(rec->key == key) {
                rec_prev->next = rec->next;
                Memory_free (NULL, rec, sizeof (keyRecs));
                status = 0;
                break;
            }
            rec_prev = rec;
            rec = rec->next;
        }
    }
    if(status != 0)
        return -1;

    obj->nested--;

    /* Leave the spinlock if the leave() is not nested */
    if (obj->nested == 0) {
        baseAddr[obj->lockNum] = 0;
    }

    IGateProvider_leave(obj->localGate, key);
    return 0;
}

/*
 *  ======== GateHWSpinlock_getResourceId ========
 */
Bits32 GateHWSpinlock_getResourceId(GateHWSpinlock_Object *obj)
{
    return (obj->lockNum);
}


/*
 *************************************************************************
 *                       Module functions
 *************************************************************************
 */

Int GateHWSpinlockDrv_devctl(resmgr_context_t * ctp, io_devctl_t * msg,
                        iofunc_ocb_t * ocb)
{
    GateHWSpinlock_Params params;
    GateHWSpinlock_Handle handle;
    GateHWSpinlock_Object * obj;
    int status;
    int dcmd = msg->i.dcmd;
    HWSpinLockDrv_CmdArgs *args =
                            (HWSpinLockDrv_CmdArgs*) (_DEVCTL_DATA (msg->i));
    HWSpinLockDrv_CmdArgs *result =
                            (HWSpinLockDrv_CmdArgs*) (_DEVCTL_DATA (msg->o));
    result->apiStatus = 0;
    msg->o.ret_val = 0;

    pthread_mutex_lock(&lock);

    if(dcmd != CMD_HWSPINLOCK_CREATE) {
        obj = GateHWSpinlock_firstObject;
        while(obj) {
            if(obj->token == args->handleID)
                break;
        }
        if(!obj) {
            result->apiStatus = -1;
            msg->o.ret_val = -EINVAL;
            pthread_mutex_unlock(&lock);
            return _RESMGR_ERRNO (EINVAL);
        }
    }
    switch(dcmd)
    {
        case CMD_HWSPINLOCK_CREATE:
            params.resourceId = args->resID;
            handle = GateHWSpinlock_create (args->protectType, &params);
            if(handle) {
                obj = (GateHWSpinlock_Object *) handle;
                obj->token = token ++;
                obj->pid = ((ipc_ocb_t *)ocb)->pid;
                obj->keys = NULL;
                result->handleID = obj->token;
            }
            else {
                result->handleID = -1;
                result->apiStatus = -1;
            }
            break;
        case CMD_HWSPINLOCK_DELETE:
            status = GateHWSpinlock_delete(&obj);
            if(status != GateHWSpinlock_S_SUCCESS)
                result->apiStatus = -1;
            break;
        case CMD_HWSPINLOCK_ENTER:
            result->key = GateHWSpinlock_enter(obj);
            if((int)result->key == -1)
                result->apiStatus = -1;
            break;
        case CMD_HWSPINLOCK_LEAVE:
            result->apiStatus = GateHWSpinlock_leave(obj, (IArg)args->key);
            break;
        case CMD_HWSPINLOCK_GETLOCKID:
            result->resID = GateHWSpinlock_getResourceId(obj);
            result->apiStatus = 0;
            break;
    }
    if(result->apiStatus == -1){
        msg->o.ret_val = -EINVAL;
    }

    pthread_mutex_unlock(&lock);

    return (_RESMGR_PTR (ctp, &msg->o,
                         sizeof (msg->o) + sizeof(HWSpinLockDrv_CmdArgs)));

}

void GateHWSpinlock_LeaveLockForPID(int pid)
{
    GateHWSpinlock_Object * obj;
    GateHWSpinlock_Object * obj_prev = GateHWSpinlock_firstObject;

    while(obj_prev) {
        if(obj_prev->pid == pid) {
            obj = obj_prev->next;
            GateHWSpinlock_delete (&obj_prev);
            obj_prev = obj;
        }
        else
            obj_prev = obj_prev->next;
    }
}

GateHWSpinlock_Handle GateHWSpinlock_create (GateHWSpinlock_LocalProtect arg,
                                           const GateHWSpinlock_Params * params)
{
    IArg key;
    GateHWSpinlock_Object * obj = (GateHWSpinlock_Object *) Memory_alloc (NULL,
                                                 sizeof (GateHWSpinlock_Object),
                                                 0,
                                                 NULL);
    if (!obj) return NULL;
    Memory_set (obj, 0, sizeof (GateHWSpinlock_Object));
    obj->status = GateHWSpinlock_Instance_init (obj, arg, params);
    if (obj->status == 0) {
        key = Gate_enterSystem ();
        if (GateHWSpinlock_firstObject == NULL) {
            GateHWSpinlock_firstObject = obj;
            obj->next = NULL;
        }
        else {
            obj->next = GateHWSpinlock_firstObject;
            GateHWSpinlock_firstObject = obj;
        }
        Gate_leaveSystem (key);
    }
    else {
        Memory_free (NULL, obj, sizeof (GateHWSpinlock_Object));
        obj = NULL;
    }
    return (GateHWSpinlock_Handle)obj;
}


Int GateHWSpinlock_delete (GateHWSpinlock_Handle * handle)
{
    IArg key;
    GateHWSpinlock_Object * temp;

    if (handle == NULL) {
        return GateHWSpinlock_E_INVALIDARG;
    }
    if (*handle == NULL) {
        return GateHWSpinlock_E_INVALIDARG;
    }
    key = Gate_enterSystem ();
        if ((GateHWSpinlock_Object *)*handle == GateHWSpinlock_firstObject) {
            GateHWSpinlock_firstObject = (*handle)->next;
    }
    else {
        temp = GateHWSpinlock_firstObject;
        while (temp) {
            if (temp->next == (*handle)) {
                temp->next = (*handle)->next;
                break;
            }
            else {
                temp = temp->next;
            }
        }
        if (temp == NULL) {
            Gate_leaveSystem (key);
            return GateHWSpinlock_E_INVALIDARG;
        }
    }
    Gate_leaveSystem (key);
    GateHWSpinlock_Instance_finalize (*handle, (*handle)->status);
    Memory_free (NULL, (*handle), sizeof (GateHWSpinlock_Object));
    *handle = NULL;
    return GateHWSpinlock_S_SUCCESS;
}

Int GateHWSpinlock_deleteAll ()
{
    GateHWSpinlock_Object * temp;
    GateHWSpinlock_Handle handle;

    if(!GateHWSpinlock_firstObject) {
        return 0;
    }

    handle = GateHWSpinlock_firstObject->next;
    while(handle) {
        temp = handle->next;
        GateHWSpinlock_delete(&handle);
        handle = temp;
    }
    handle = GateHWSpinlock_firstObject;
    GateHWSpinlock_delete(&handle);

    return GateHWSpinlock_S_SUCCESS;
}
#endif /* IPC_PLATFORM_VAYU */

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
