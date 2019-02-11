/*
 * Copyright (c) 2012-2013, Texas Instruments Incorporated
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
 *
 */
/*
 *  ======== iresman_hdvicp2.c ========
 */

/* This difine must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_fc_ires_hdvicp2_desc

/* TOFIGURE: Issue when calling deactivate, we don't know the size of the
 * actual
 * Algorithm object, so mmap, will map only the IALG_Obj part of it :(
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/IGateProvider.h>

#include <xdc/runtime/Registry.h>

#include <xdc/runtime/IGateProvider.h>
#include <xdc/runtime/knl/GateProcess.h>

#include <ti/sdo/fc/global/FCSettings.h>
#include <ti/sdo/fc/utils/osalsupport/OsalSupport.h>

#define ti_sdo_fc_ires_NOPROTOCOLREV

#include "iresman_hdvicp.h"
#include "iresman_protocol_hdvicp2.h"
#include "ires_hdvicp2.h"
#include "hdvicp2.h"
#include "_hdvicp2.h"

#include <xdc/runtime/Gate.h>

#ifdef xdc_target__os_Linux

#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <ti/sdo/fc/utils/shm.h>
#include <xdc/runtime/knl/SemProcess.h>

__FAR__ static Int memfd = -1;

#else

#include <xdc/runtime/knl/SemThread.h>
#include <src/links_ipu/iva/codec_utils/utils_encdec_prf.h>
#endif

#include <ti/sdo/fc/memutils/memutils.h>

/* can't make this static, as it's used throughout this package (other files) */

/* Indicates a free resource entry */
#define IRESMAN_HDVICP2_RESOURCEFREE 0xFFFF

/* Value to initialize the ALG filed of the _resmanInternalState */
#define ALGNULL                      ((IALG_Handle)0xDEADBEEF)

/* Convenience macros to access _resmanInternalState entries */

/* Number of resources */
#define _HDVICP2_NUMRES       (_resmanInternalState->numResources)
#define _HDVICP2_LATEALG(i)   (_resmanInternalState->lateAlg[(i)])
#define _HDVICP2_LATERES(i)   (_resmanInternalState->lateHdvicp[(i)])
#define _HDVICP2_LASTCLASS(i) ((_HDVICP2_LATEALG(i) == ALGNULL) ? NULL: \
        ((Void *)((_HDVICP2_LATEALG(i))->fxns->implementationId)))
#define _HDVICP2_TOTALFREE    (_resmanInternalState->totalFree)
#define _HDVICP2_LASTMODE(i)  (_resmanInternalState->configurationId[(i)])

/*
#ifdef xdc_target__os_Linux
#define  VIRTADDR(size,addr) (mmap(0,(void *)(size), PROT_READ|PROT_WRITE, \
        MAP_SHARED, memfd, (__off_t)(addr)));
#else
#define  VIRTADDR(size,addr) (addr)
#endif
*/

/* Other convenience macros */
#ifdef xdc_target_os__Linux

#define _HDVICP2_SEMPEND(i) SemProcess_pend(_resmanInternalState->semres[(i)], \
        SemProcess_FOREVER, NULL)
#define _HDVICP2_SEMPOST(i) SemProcess_post(_resmanInternalState->semres[(i)], \
        NULL)
#else

#define _HDVICP2_SEMPEND(i)    SemThread_pend(_resmanInternalState->semres[(i)]\
        ,SemThread_FOREVER, NULL)
#define _HDVICP2_SEMPOST(i)    SemThread_post(_resmanInternalState->semres[(i)]\
        , NULL)
#endif


/* Signature for the acquire=any function */
typedef XDAS_Int32 (*acquireFxn)(IALG_Handle alg,
            XDAS_UInt32 *reloadHDVICP, XDAS_UInt32 * configurationId,
            IRES_HDVICP2_Handle h);
typedef XDAS_Int32 (*reacquireFxn)(IALG_Handle alg, IRES_HDVICP2_Handle h);

/* Signature for the acquire-specific function */
typedef Void (*acquireIdFxn)(XDAS_Int32 Id, IALG_Handle alg,
        XDAS_UInt32 *reloadHDVICP, XDAS_UInt32 * configurationId,
        IRES_HDVICP2_Handle h);

/* Signature for the release function */
typedef Void (*releaseFxn) (XDAS_Int32 Id, IALG_Handle alg,
        IRES_HDVICP2_Handle hdvicp2);
/*
 * Holds the internal state of an initialized object
 */
typedef struct IRESMAN_HDVICP2_InternalState {

    int numOpens;                               /* Number of instances of this
                                                 * resource manager
                                                 */

    int resourceBusy[_HDVICP2_MAXRESOURCES];    /* Busy-status of HDVICP2
                                                 * resources.
                                                 */

    int refCount[_HDVICP2_MAXRESOURCES];        /* Reference count
                                                 * when multiple
                                                 * requestors from
                                                 * the same scratch
                                                 * group have been
                                                 * granted the
                                                 * resource.
                                                 */

    int numResources;                           /* Total number of resources
                                                 * being managed.
                                                 */

    IALG_Handle lateAlg[_HDVICP2_MAXRESOURCES]; /* Last algorithm to have used
                                                 * the resource. (only used for
                                                 * JIT APIs)
                                                 */

    IRES_HDVICP2_Handle lateHdvicp[_HDVICP2_MAXRESOURCES];
                                                /* Resource handle of the last
                                                 * algorithm to have used
                                                 * the resource. (only used for
                                                 * JIT APIs)
                                                 * Should be cleared only after
                                                 * algorithm has been
                                                 * deactivated or if algorithm
                                                 * frees all its resources.
                                                 */

    IALG_Handle alg[_HDVICP2_MAXRESOURCES];     /* Current algorithm that has
                                                 * been granted the resource.
                                                 */


    /* Bool inUse[_HDVICP2_MAXRESOURCES];        * Keeps track of the resource
                                                 * currently in use.
                                                 * This info is used by
                                                 * the JIT acquire/release API
                                                 * to see if a resource is
                                                 * available to be granted JIT.
                                                 */

    XDAS_UInt32 configurationId[_HDVICP2_MAXRESOURCES];/* Keeps track of the
                                                 * configurationId
                                                 * for a particular HDVICP.
                                                 */

#ifdef xdc_target__os_Linux
    SemProcess_Handle semres[_HDVICP2_MAXRESOURCES + 1];
#else
    SemThread_Handle semres[_HDVICP2_MAXRESOURCES + 1];
#endif                                          /* on during JIT acquire calls
                                                 */

    int totalFree;                              /* Number of free HDVICP2
                                                 *  resources
                                                 */

    int sharedMemId;                            /* Identifies the shared
                                                 * memory segment used to
                                                 * hold this state (in MP
                                                 * cases).
                                                 */
} IRESMAN_HDVICP2_InternalState;

extern UInt32 _HDVICP2_ipcKeyBase;

/* Internal placeholders for the various acquire/release functions etc */
__FAR__ static acquireFxn _acquire = NULL;
__FAR__ static acquireIdFxn _acquireId = NULL;
__FAR__ static releaseFxn _release = NULL;


__FAR__ static IRESMAN_PersistentAllocFxn * allocFxn;   /* Memory alloc func */
__FAR__ static IRESMAN_PersistentFreeFxn * freeFxn;     /* Memory free func */

/*
 * Flag indicating if the resource manager is initialized
 */
__FAR__ static unsigned int _initialized = 0;

__FAR__ static Int regInit = 0;  /* Registry_addModule() called */

__FAR__ Registry_Desc ti_sdo_fc_ires_hdvicp2_desc;

/*
 * To indicate 'any' resource was requested or some resource
 * was freed
 */
__FAR__ static unsigned int ANYRESOURCE = _HDVICP2_MAXRESOURCES;

/*
 * Represents the IRES EDMA3 Resource manager
 */
__FAR__ static IRESMAN_HDVICP2_InternalState * _resmanInternalState;

#ifdef xdc_target__os_Linux

#else

/*
 * For non-Linux, non-MP case, use statically allocated memory
 */
__FAR__ static IRESMAN_HDVICP2_InternalState _HDVICP2_internalState = {0};

#endif

__FAR__ static IGateProvider_Handle gate = NULL;

static void getInternalState();
static void setInternalState();
static void freeInternalState();
static inline Void freeRes(Int Id, IALG_Handle alg, Int scratchGroupId);

static Void _acquireSpecific(Int Id, IALG_Handle alg,
        XDAS_UInt32 *reloadHDVICP, XDAS_UInt32 * configurationId,
        IRES_HDVICP2_Handle h);
static Void _acquireSpecificPlugin(Int Id, IALG_Handle alg,
        XDAS_UInt32 *reloadHDVICP, XDAS_UInt32 *configurationId,
        IRES_HDVICP2_Handle h);

static XDAS_Int32 _acquireAny(IALG_Handle alg,
            XDAS_UInt32 *reloadHDVICP,
            XDAS_UInt32 * configurationId, IRES_HDVICP2_Handle h);
static XDAS_Int32 _acquireAnyPlugin(IALG_Handle alg,
            XDAS_UInt32 *reloadHDVICP,
            XDAS_UInt32 * configurationId, IRES_HDVICP2_Handle h);

static Void _releaseSpecific(XDAS_Int32 Id, IALG_Handle alg,
        IRES_HDVICP2_Handle hdvicp2);
static Void _releaseSpecificPlugin(XDAS_Int32 Id, IALG_Handle alg,
        IRES_HDVICP2_Handle hdvicp2);

extern __FAR__ unsigned int _HDVICP2_NUMRESOURCES;

extern __FAR__ ti_sdo_fc_ires_hdvicp_HDVICP2_GetHdvicp2Fxn
        ti_sdo_fc_ires_hdvicp_HDVICP2_getHdvicp2Fxn;

extern __FAR__ ti_sdo_fc_ires_hdvicp_HDVICP2_FreeHdvicp2Fxn
        ti_sdo_fc_ires_hdvicp_HDVICP2_freeHdvicp2Fxn;

/* Function to intiailzie the semaphore "semArray" array with sem handles */
extern Bool ti_sdo_fc_ires_hdvicp_HDVICP2_semInit();

/* Optional plugin functions for release/free APIs */
extern ti_sdo_fc_ires_hdvicp_HDVICP2_GetHdvicp2Fxn
        ti_sdo_fc_ires_hdvicp_HDVICP2_getHdvicp2Fxn;

extern ti_sdo_fc_ires_hdvicp_HDVICP2_FreeHdvicp2Fxn
        ti_sdo_fc_ires_hdvicp_HDVICP2_freeHdvicp2Fxn;

/* Call to obtain yield arguments for a particular scratch group */
extern IRES_YieldArgs (* ti_sdo_fc_ires_hdvicp_HDVICP2_getYieldArgs)
        (Int scratchId);

/* Call to release group lock/context etc */
extern Void (* ti_sdo_fc_ires_hdvicp_HDVICP2_yieldRelease)
        (IRES_YieldResourceType resource, IRES_YieldContextHandle ctxt,
        IRES_YieldArgs args);

/* Call to re-acquire group lock/context etc */
extern Void (* ti_sdo_fc_ires_hdvicp_HDVICP2_yieldAcquire)
        (IRES_YieldResourceType resource, IRES_YieldContextHandle ctxt,
        IRES_YieldArgs args);

/* Call to obtain IRES_Fxns corresponding to a particular algHandle */
extern IRES_Fxns * RMAN_getIresEntry(IALG_Handle alg);

/*
 *  ======== IRESMAN_HDVICP2_getProtocolName ========
 *  Function to return the name of the protocol
 */
String IRESMAN_HDVICP2_getProtocolName()
{
    if (regInit) {
    Log_print0(Diags_ENTRY, "[+E] IRESMAN_HDVICP2_getProtocolName> Enter");

    Log_print1(Diags_EXIT,
            "[+X] IRESMAN_HDVICP2_getProtocolName> Exit (name=%s)",
            (IArg)(IRESMAN_HDVICP2_CONSTRUCTFXNS.getName()));
    }

    return (IRESMAN_HDVICP2_CONSTRUCTFXNS.getName());
}

/*
 *  ======== IRESMAN_HDVICP2_getProtocolRevision ========
 *  Function to return the revision of the protocol
 */
IRES_ProtocolRevision * IRESMAN_HDVICP2_getProtocolRevision()
{
    IRES_ProtocolRevision * version;

    if (regInit)
    Log_print0(Diags_ENTRY, "[+E] IRESMAN_HDVICP2_getProtocolRevision> Enter");

    version = IRESMAN_HDVICP2_CONSTRUCTFXNS.getRevision();

    if (regInit)
    Log_print3(Diags_EXIT,
            "[+X] IRESMAN_HDVICP2_getProtocolRevision> Exit "
            "(version=(%d.%d.%d))", (IArg)(version->Major),
            (IArg)(version->Source), (IArg)(version->Radius));

    return (version);
}

/*
 *  ======== IRESMAN_HDVICP2_init ========
 * Function to initialize the device specific resource manager implementation
 */
IRES_Status IRESMAN_HDVICP2_init(IRESMAN_Params * initArgs)
{
    Bool result = TRUE;
    IRESMAN_HdVicpParams * resmanArgs = (IRESMAN_HdVicpParams *)initArgs;
    IArg key;
#ifndef xdc_runtime_Assert_DISABLE_ALL
    Registry_Result   regResult;
#endif


    Assert_isTrue(initArgs != NULL, (Assert_Id)NULL);

    /*
     *  Register the module name for logging only once. Do this before any
     *  Log functions are called.
     */
    if (!regInit) {
#ifndef xdc_runtime_Assert_DISABLE_ALL
        regResult =
#endif
                Registry_addModule(&ti_sdo_fc_ires_hdvicp2_desc,
                HDVICP2_MODNAME);

        Assert_isTrue(regResult == Registry_SUCCESS, (Assert_Id)NULL);

        /* Set diags mask to FC default */
        FCSettings_init();
        FCSettings_setDiags(HDVICP2_MODNAME);
        regInit = 1;
    }

    Log_print1(Diags_ENTRY, "[+E] IRESMAN_HDVICP2_init> Enter (initArgs=0x%x)",
            (IArg)initArgs);
    /* Check if already initialized */
    if (_initialized) {
       Log_print0(Diags_EXIT,
               "[+X] IRESMAN_HDVICP2_init> Exit (status=IRES_EEXISTS)");
       return (IRES_EEXISTS);
    }

    /* Memory allocation/free functions */
    ANYRESOURCE = _HDVICP2_NUMRESOURCES;
    allocFxn = resmanArgs->baseConfig.allocFxn;
    freeFxn = resmanArgs->baseConfig.freeFxn;

    gate = OsalSupport_createGate(_HDVICP2_ipcKeyBase);
    if (gate == NULL) {
        Log_print0(Diags_USER7, "[+7] IRESMAN_HDVICP2_init> Could not "
                "create gate");
        Log_print0(Diags_EXIT, (IArg)("[+X] IRESMAN_HDVICP2_init> Exit "
                "(status=IRES_EFAIL)"));

        return (IRES_EFAIL);
    }

#ifdef xdc_target__os_Linux
    memfd = open("/dev/mem", O_RDONLY);

    if (-1 == memfd) {
        Log_print0(Diags_USER7, "[+7] IRESMAN_HDVICP2_init> Could not "
                "open file descriptor to /dev/mem");

        initStatus = IRES_EFAIL;

        Log_print1(Diags_EXIT, (IArg)("[+X] IRESMAN_HDVICP2_init> Exit "
                "(status=IRES_EFAIL)"));

        return (IRES_EFAIL);
    }
#endif

    key = IGateProvider_enter(gate);

    /* Populates the _resmanInternalState pointer */
    getInternalState();

    if ((NULL == _resmanInternalState)  || (-1 ==
            _resmanInternalState->sharedMemId )) {

        IGateProvider_leave(gate, key);

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_VICP2_init> Failed to obtain Internal state "
                "Object");

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_VICP2_init> Exit (status=IRES_EFAIL)");

        return (IRES_EFAIL);
    }

    _HDVICP2_NUMRES = _HDVICP2_NUMRESOURCES;

    IGateProvider_leave(gate, key);

    if ((NULL == ti_sdo_fc_ires_hdvicp_HDVICP2_getHdvicp2Fxn)  ||
            (NULL == ti_sdo_fc_ires_hdvicp_HDVICP2_freeHdvicp2Fxn)) {

        _acquire = _acquireAny;
        _release = _releaseSpecific;
        _acquireId = _acquireSpecific;
    }
    else {
        _acquire = _acquireAnyPlugin;
        _release = _releaseSpecificPlugin;
        _acquireId = _acquireSpecificPlugin;
    }

    Assert_isTrue(_HDVICP2_NUMRES <= _HDVICP2_MAXRESOURCES, (Assert_Id)NULL);

    /* Initialize the semaphore table */
    result = ti_sdo_fc_ires_hdvicp_HDVICP2_semInit();
    if (FALSE == result) {
        Log_print0(Diags_EXIT,
                "IRESMAN_HDVICP2_init> Exit (status=IRES_EFAIL)");

        return (IRES_EFAIL);
    }

    /* Set Initalized flag to 1 if successful */
     _initialized = 1;

     Log_print0(Diags_EXIT, "[+X] IRESMAN_HDVICP2_init> Exit (status=IRES_OK)");

     return (IRES_OK);
}

/*
 *  ======== IRESMAN_HDVICP2_exit ========
 *  Function called when RESMAN is no longer needed. Use it to free memory
 *  allocated etc
 */
IRES_Status IRESMAN_HDVICP2_exit()
{
    IArg key;

    /* Check if initialized */
    Log_print0(Diags_ENTRY, "[+E] IRESMAN_HDVICP2_exit> Enter");

    if (!(_initialized)) {
        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_HDVICP2_exit> Exit (status=IRES_ENOINIT)");

        return (IRES_ENOINIT);
    }

    /* Set the initialized flag to zero again */
    _initialized = 0;

    if (gate) {
        key = IGateProvider_enter(gate);
        freeInternalState();
        IGateProvider_leave(gate, key);

        OsalSupport_deleteGate(gate);
        gate = NULL;
    }

    Log_print0(Diags_EXIT, "[+X] IRESMAN_HDVICP2_exit> Exit (status=IRES_OK)");

    return (IRES_OK);
}

/*
 *  ======== IRESMAN_HDVICP2_getHandles ========
 *  Function that returns the IRES_Handle to the resource requested using the
 *  IRES_ResourceProtocolArgs
 */
/*  ARGSUSED - this line tells the compiler not to warn about unused args */

IRES_Handle IRESMAN_HDVICP2_getHandles(IALG_Handle algHandle,
        IRES_ResourceDescriptor * resDesc, Int scratchGroupId,
        IRES_Status * status)
{
    IArg key;
    IALG_MemRec protocolMemRecs[_HDVICP2_MAXRESOURCES];
    IALG_MemRec constructHandleMemRec;
    Int numMemRecs = 0;
    Int Id = -1;
    Int count = 0;
    IRESMAN_HDVICP2_ConstructHandleArgs * constructArgs = NULL;
    IRES_Handle resourceHandle = (IRES_Handle)NULL;
    Bool lateAcquire = FALSE;
    Int reqId;
    IRES_ProtocolArgs * protocolArgs = resDesc->protocolArgs;
    /*
     * Cast the protocolArgs
     */
    IRES_HDVICP2_ProtocolArgs * configArgs =
            (IRES_HDVICP2_ProtocolArgs *) protocolArgs;

    Assert_isTrue(protocolArgs, (Assert_Id)NULL);

    Log_print3(Diags_ENTRY,
            "[+E] IRESMAN_HDVICP2_getHandles> Enter (algHandle = 0x%x, "
            "protocolArgs=0x%x, scratchGroupId=%d)",
            (IArg)algHandle, (IArg)protocolArgs, (IArg)scratchGroupId);

    if (_initialized != 1) {

        *status =  IRES_ENORESOURCE;

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_HDVICP2_getHandles> RMAN register for HDVICP2 resource"
                "not happened successfully. Please call RMAN_register before "
                "trying to assign or release resources");

        return (NULL);
    }

    if (0 == _HDVICP2_NUMRES) {

        *status =  IRES_ENORESOURCE;

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_HDVICP2_getHandles> Trying to request HDVICP2 resource"
                "on a device with 0 HDVICP2 resources. Check device "
                "configuration.");

        return (NULL);
    }

    if (configArgs->base.mode == IRES_PERSISTENT) {
        scratchGroupId = -1;
    }

    reqId = configArgs->id;

    /*
     * Use the protocolArgs to determine which resource to allocate
     */

    /* 1. Check for late acquire, if so, do nothing at this time */
    if ((configArgs->id == IRES_HDVICP2_ID_LATE_ACQUIRE) ||
            (configArgs->base.mode == IRES_LATEACQUIRE)) {

        Log_print0(Diags_USER4,
                "[+4] IRESMAN_HDVICP2_getHandles> Late acquire requested");

        Id = IRES_HDVICP2_ID_LATE_ACQUIRE;

        lateAcquire = TRUE;
#ifdef xdc_target__os_Linux

        *status = IRES_EFAIL;

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_HDVICP2_getHandles> Trying to request HDVICP2 resource"
                " in LATEACQUIRE mode on Linux. Not yet supported.");

        return (NULL);
#endif
    }
    /* If request is for ANY resource, return available resource */
    else if (configArgs->id == IRES_HDVICP2_ID_ANY) {

        Log_print0(Diags_USER4,
                "[+4] IRESMAN_HDVICP2_getHandles> ANY Resource requested");

        for (count = 0; count < _HDVICP2_NUMRES; count++) {

            key = IGateProvider_enter(gate);

            /*
             * If the requested resource is free or if the same scratch group
             * requests it, return the Id
             * If the resourceBusy status is set to -1, this implies that the
             * resource has been granted persistently
             */
            if ((IRESMAN_HDVICP2_RESOURCEFREE ==
                    _resmanInternalState->resourceBusy[count])) {

                /* Note the scratch group that is occupying this resource */
                _resmanInternalState->resourceBusy[count] = scratchGroupId;

                _resmanInternalState->refCount[count] = 1;

                /* We keep track of what alg was "just" granted this resource,
                   this is required so that if one alg requests resources in
                   two different descriptors, it isn't granted the same resource
                   in both */
                _resmanInternalState->alg[count] = algHandle;

                IGateProvider_leave(gate, key);

                Id = count;

                Log_print1(Diags_USER4,
                        "[+4] IRESMAN_HDVICP2_getHandles> HDVICP2 Resource %d is "
                        "available", (IArg)Id);

                break;
            }

            /* Check if request is for a scratch resource in the same
               scratch group, also ensure it wasn't just assigned to the same
               alg
             */
            else if ((scratchGroupId != -1 ) &&
                    (_resmanInternalState->resourceBusy[count] ==
                    scratchGroupId) &&
                    ( _resmanInternalState->alg[count] != algHandle )) {

                _resmanInternalState->refCount[count]++;

                _resmanInternalState->alg[count] = algHandle;

                IGateProvider_leave(gate, key);

                Id = count;

                Log_print2(Diags_USER4,
                        "[+4] IRESMAN_HDVICP2_getHandles> HDVICP2 Resource %d is "
                        "available to scratch group %d",
                        (IArg)Id, (IArg)scratchGroupId);

                break;
            }

            IGateProvider_leave(gate, key);
        }

        if (Id == -1) {

            /* Did not obtain any valid resource */
            *status = IRES_ENORESOURCE;

            Log_print0(Diags_USER7,
                    "[+7] IRESMAN_HDVICP2_getHandles> Error obtaining free "
                    "HDVICP2 resource.");

            Log_print0(Diags_EXIT,
                    "[+X] IRESMAN_HDVICP2_getHandles> Exit (handle=NULL, "
                    "status=IRES_ENORESOURCE)");

            return (NULL);
        }

    }
    /* Request is for a specific resource, not ANY */
    else {
        /* 3. If fixed, check for availability and return or fail */
        Id = configArgs->id;

        /* Bad request */
        if ((Id >= _HDVICP2_NUMRES) || (Id < 0)) {

            *status = IRES_ENORESOURCE;

            Log_print2(Diags_USER7,
                    "[+7] IRESMAN_HDVICP2_getHandles> Did not recognize "
                    "HDVICP2 resource request: %d, num hdvicp2 resource: %d",
                    (IArg)Id, (IArg)_HDVICP2_NUMRES);

            Log_print0(Diags_EXIT,
                    "[+X] IRESMAN_HDVICP2_getHandles> Exit (handle=NULL, "
                    "status=IRES_ENORESOURCE)");

            return (NULL);
        }

        Log_print1(Diags_USER4,
                "[+4] IRESMAN_HDVICP2_getHandles>Specific HDVICP2 Resource req"
                "uested%d", (IArg)Id);

        key = IGateProvider_enter(gate);

        /* Check if resource is free */
        if ((IRESMAN_HDVICP2_RESOURCEFREE ==
                _resmanInternalState->resourceBusy[Id])) {

            _resmanInternalState->resourceBusy[Id] = scratchGroupId;
            _resmanInternalState->refCount[Id] = 1;

            _resmanInternalState->alg[Id] = algHandle;

            IGateProvider_leave(gate, key);

            Log_print1(Diags_USER4,
                    "[+4] IRESMAN_HDVICP2_getHandles>HDVICP2 Resource %d avail"
                    "able" , (IArg)Id);
        }

        /* Check if resource is already available to the scratch group
           requesting it, and ensure it wasn't already grantd to the same
           algorithm */
        else if ((scratchGroupId != -1) &&
                (_resmanInternalState->resourceBusy[Id] == scratchGroupId) &&
                (_resmanInternalState->alg[Id] != algHandle )) {

            _resmanInternalState->refCount[Id]++;

            _resmanInternalState->alg[Id] = algHandle;

            IGateProvider_leave(gate, key);

            Log_print2(Diags_USER4,
                    "[+4] IRESMAN_HDVICP2_getHandles> HDVICP2 Resource %d available "
                    "to scratch group %d", (IArg)Id, (IArg)scratchGroupId);
        }
        else {

            IGateProvider_leave(gate, key);

            *status = IRES_ENORESOURCE;

            Log_print0(Diags_USER7,
                    "[+7] IRESMAN_HDVICP2_getHandles> Error obtaining HDVICP2"
                    "resource.");

            Log_print0(Diags_EXIT,
                    "[+X] IRESMAN_HDVICP2_getHandles> Exit (handle=NULL, "
                    "status=IRES_ENORESOURCE)");

            return (NULL);
        }
    }

    /*
     * Get IRES_HDVICP2 handle's memory requirements
     */
    numMemRecs = IRESMAN_HDVICP2_CONSTRUCTFXNS.getNumMemRecs
         ( (IRES_ProtocolArgs *)protocolArgs);

    Assert_isTrue(numMemRecs <= _HDVICP2_MAXRESOURCES, (Assert_Id)NULL);

    /*
     * Allocate memory for the constructHandle Arguments
     */
    constructHandleMemRec.size = sizeof(IRESMAN_HDVICP2_ConstructHandleArgs);
    constructHandleMemRec.alignment = 4;
    constructHandleMemRec.space = IALG_EXTERNAL;
    constructHandleMemRec.attrs = IALG_PERSIST;

    if (FALSE == allocFxn(&constructHandleMemRec, 1)) {
        *status =  IRES_ENOMEM;

        Log_print2(Diags_USER7,
                "[+7] IRESMAN_HDVICP2_getHandles> Error allocating memory for "
                "constructing handle of size 0x%x, alignment 0x%x, space "
                "IALG_EXTERNAL, attrs IALG_PERSIST",
                (IArg)(constructHandleMemRec.size),
                (IArg)(constructHandleMemRec.alignment));

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_HDVICP2_getHandles> Exit (handle=NULL, "
                "status=IRES_ENOMEM)");

        /* Error so free acquired resource */
        freeRes(Id, algHandle, scratchGroupId);

        return (NULL);
    }

    Assert_isTrue(IALG_EXTERNAL == constructHandleMemRec.space,
            (Assert_Id)NULL);
    constructArgs = constructHandleMemRec.base;

    /*
     * Populate the construct args
     */
        (constructArgs->args).size = sizeof(IRESMAN_HDVICP2_ConstructHandleArgs);
    constructArgs->id = Id;       /* What this function managed to assign */
    constructArgs->lateAcquire = lateAcquire;
    constructArgs->scratchGroup = scratchGroupId;
    constructArgs->info = NULL;
    constructArgs->reqId = reqId; /* What the alg actually requested */

    if ((!lateAcquire) && (-1 == scratchGroupId)) {
        constructArgs->persistent = TRUE;
    }
    else {
        constructArgs->persistent = FALSE;
    }

    /*
     * Obtain memory resources to build the handle
     */
    IRESMAN_HDVICP2_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, protocolMemRecs);

    /*
     * Allocate that memory
     */
    if (FALSE == allocFxn(protocolMemRecs, numMemRecs)) {

        *status = IRES_ENOMEM;

        Log_print2(Diags_USER7,
                "[+7] IRESMAN_HDVICP2_getHandles> Error allocating memory for "
                "constructing handle of size 0x%x, alignment 0x%x, space "
                "IALG_EXTERNAL, attrs IALG_PERSIST",
                (IArg)(protocolMemRecs->size),
                (IArg)(protocolMemRecs->alignment));

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_HDVICP2_getHandles> Exit (handle=NULL, "
                "status=IRES_ENOMEM)");

        freeFxn(&constructHandleMemRec, 1);

        /* Error so free acquired resource */
        freeRes(Id, algHandle, scratchGroupId);

        return (NULL);
    }

    /*
     * Use the CONSTRUCT interface of the protocol implementation to
     * construct the handle within the allocated resource
     */
    resourceHandle = IRESMAN_HDVICP2_CONSTRUCTFXNS.constructHandle(
            protocolArgs, protocolMemRecs,
            (IRESMAN_ConstructArgs *)constructArgs, status);

    /*
     * Free constructArgs memory, that was just to pass the arguments
     */
    freeFxn(&constructHandleMemRec, 1);

    if (IRES_OK != *status) {

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_HDVICP2_getHandles> Error freeing memory ");

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_HDVICP2_getHandles> Exit (handle=NULL, "
                "status=IRES_EFAIL)");

        /* Error so free acquired resource */
        freeRes(Id, algHandle, scratchGroupId);

        return (NULL);
    }
    else {

        Log_print2(Diags_EXIT,
                "[+X] IRESMAN_HDVICP2_getHandles> Exit (handle=0x%x, "
                "status=0x%x)", (IArg)resourceHandle, (IArg)(*status));

        resDesc->handle = resourceHandle;

        resDesc->revision->Major = 1;
        resDesc->revision->Source = 0;
        resDesc->revision->Radius = 0;

        return (resourceHandle);
    }
}

/*
 *  ======== IRESMAN_HDVICP2_freeHandles ========
 *  Frees handles back to the resource pool resources to free
 */
/*  ARGSUSED - this line tells the compiler not to warn about unused args */
IRES_Status IRESMAN_HDVICP2_freeHandles(IALG_Handle algHandle,
        IRES_Handle algResourceHandle, IRES_ResourceDescriptor * resDesc,
        Int scratchGroupId)
{
    IALG_MemRec resourceMemRecs[_HDVICP2_MAXRESOURCES];
    Int numMemRecs;
    IRES_Status status = IRES_OK;
    Int Id = -1;
    IArg key;
    Int i;
    IRES_ProtocolArgs * protocolArgs = resDesc->protocolArgs;
    IRES_HDVICP2_Handle resourceHandle = (IRES_HDVICP2_Handle)
            algResourceHandle;

    Assert_isTrue(protocolArgs, (Assert_Id)NULL);
    Assert_isTrue(algResourceHandle, (Assert_Id)NULL);

    Log_print3(Diags_ENTRY,
            "[+E] IRESMAN_HDVICP2_freeHandle> Enter (handle=0x%x, "
            "protocolArgs=0x%x, scratchGroupId=%d)",
            (IArg)algResourceHandle, (IArg)protocolArgs,
            (IArg)scratchGroupId);

    if (_initialized != 1) {

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_HDVICP2_freeHandles>RMAN register for HDVICP2 resource"
                "not happened successfully. Please call RMAN_register before "
                "trying to assign or release resources");

        status =  IRES_ENORESOURCE;

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_HDVICP2_freeHandles>Exit (status=IRES_ENORESOURCE)");

        return (status);
    }

    /*
     * Use the handle to determine which resource to free
     */
    Id = resourceHandle->id;

    /* No need to do anything for late acquire Handles */
    if (((IRES_HDVICP2_IntObj *)(resourceHandle))->lateAcquire != TRUE) {

        if ((Id >= _HDVICP2_NUMRES) ||
                ( IRESMAN_HDVICP2_RESOURCEFREE ==
                _resmanInternalState->resourceBusy[Id])) {

            Log_print0(Diags_USER7,
                    "[+7] IRESMAN_HDVICP2_freeHandles> Error freeing HDVICP2 "
                    "resource. Resource already free");

            Log_print0(Diags_EXIT,
                    "[+X] IRESMAN_HDVICP2_freeHandles> Exit "
                    "(status=IRES_ENORESOURCE)");

            return (IRES_ENORESOURCE);
        }
        else {
            freeRes(Id, algHandle, scratchGroupId);
        }
    }
    else {

        key = IGateProvider_enter(gate);

        for (i = 0; i < _HDVICP2_MAXRESOURCES; i++) {

            if (_HDVICP2_LATEALG(i) == algHandle) {

                _HDVICP2_LATEALG(i) = ALGNULL;
                _HDVICP2_LATERES(i) = NULL;
                break;
            }
        }

        IGateProvider_leave(gate, key);
    }

    /*
     * Obtain memory resources to free and free them
     */
    numMemRecs = IRESMAN_HDVICP2_CONSTRUCTFXNS.getNumMemRecs
         ( (IRES_ProtocolArgs *)protocolArgs);

    IRESMAN_HDVICP2_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, resourceMemRecs);

    resourceMemRecs[0].base = algResourceHandle;

    /*
     * Use IRES_HDVICP2_RESOURCEPROTOCOL to de-init the resource protocol
     * if required
     */
    IRESMAN_HDVICP2_CONSTRUCTFXNS.destructHandle(algResourceHandle);

    /*
     * Free the memory for the handles
     */
    freeFxn(resourceMemRecs, numMemRecs);

    Log_print1(Diags_EXIT, "[+X] IRESMAN_HDVICP2_freeHandles> Exit (status=%d)",
            (IArg)status);

    return (status);
}

/*
 *  ======== getInternalState ========
 *  Function to populate _resmanInternalState that points to the Internal
 *  state of this resource manager
 */
static void getInternalState()
{
#ifdef xdc_target__os_Linux
    Int sharedMemId = -1;

    _resmanInternalState = (IRESMAN_HDVICP2_InternalState *)SHM_getObj(
            ti_sdo_fc_ires_hdvicp_HDVICP2_gate,
            sizeof(IRESMAN_HDVICP2_InternalState),
            _HDVICP2_LOCKID, &setInternalState, &sharedMemId);

    Assert_isTrue(sharedMemId != -1, (Assert_Id)NULL);

    if (sharedMemId == -1) {
        _resmanInternalState = NULL;
        return;
    }

    _resmanInternalState->sharedMemId = sharedMemId;

#else
    _resmanInternalState = (IRESMAN_HDVICP2_InternalState *)
            &_HDVICP2_internalState;

    /* Initialize this state the first time */
    setInternalState(_resmanInternalState);

#endif
    _resmanInternalState->numOpens++;
}

/*
 *  ======== freeInternalState ========
 *  Funciton to free/clear the internal state of the resource manager
 */
static void freeInternalState()
{
    int i = 0;
    _resmanInternalState->numOpens--;

    if (0 == _resmanInternalState->numOpens) {
#ifdef xdc_target__os_Linux
        for (i = 0; i <= _HDVICP2_NUMRESOURCES; i++) {
            SemProcess_delete(&_resmanInternalState->semres[i]);
        }
    }

    SHM_freeObj(_resmanInternalState, _resmanInternalState->sharedMemId);
#else
        for (i = 0; i <= _HDVICP2_NUMRESOURCES; i++) {
            SemThread_delete(&_resmanInternalState->semres[i]);
        }
    }
#endif

    _resmanInternalState = NULL;
}

/*
 *  ======= setInternalState =======
 *  Function called to initialize the resource manager state
 */
static Void setInternalState(Void * addr)
{
    IRESMAN_HDVICP2_InternalState * intState =
            (IRESMAN_HDVICP2_InternalState *)addr;
    Int i;
    IArg key;
#ifdef xdc_target__os_Linux
    SemProcess_Params semParams;
    SemProcess_Params_init(&semParams);
#else
    SemThread_Params semParams;
    SemThread_Params_init(&semParams);
    semParams.mode = SemThread_Mode_BINARY;
#endif

    if (NULL != intState) {

        key = IGateProvider_enter(gate);
        intState->numOpens = 0;

        for (i = 0; i < _HDVICP2_MAXRESOURCES; i++) {
            intState->resourceBusy[i] = IRESMAN_HDVICP2_RESOURCEFREE;
            intState->refCount[i] = 0;
            intState->lateAlg[i] = ALGNULL;
            intState->alg[i] = ALGNULL;
            intState->lateHdvicp[i] = NULL;
            intState->configurationId[i] = 0;
            intState->lateHdvicp[i] = NULL;
            intState->semres[i] = NULL;
        }

                intState->semres[_HDVICP2_MAXRESOURCES] = NULL;

#ifdef xdc_target__os_Linux
        for (i = 0; i <= _HDVICP2_NUMRESOURCES; i++) {
            /* semParams.instance->name =
                    "ti_sdo_fc_ires_hdvicp_HDVICP2_resourceSem";*/
            intState->semres[i] = SemProcess_create(0, _HDVICP2_CSID + i,
                    &semParams, NULL);
        }
#else
        for (i = 0; i <= _HDVICP2_NUMRESOURCES; i++) {
            SemThread_Params_init(&semParams);
            semParams.mode = SemThread_Mode_BINARY;
            intState->semres[i] = SemThread_create(0, &semParams, NULL);
        }
        intState->sharedMemId = 0;
#endif

        intState->totalFree = _HDVICP2_NUMRESOURCES;
        IGateProvider_leave(gate, key);
    }
}

/*
 *  ========  IRESMAN_HDVICP2_JITacquire ========
 *  Function called by the algorithm to do a JIT acquire of the IVA-HD resource
 *  Before this, the process doesn't truly own the resource, unless it acquired
 *  it persistently (scratchGroupId -1)
 */
XDAS_Void IRESMAN_HDVICP2_JITacquire (IALG_Handle algHandle,
        IRES_HDVICP2_Obj * hdvicpHandle,  IRES_YieldContextHandle yieldCtxt,
        XDAS_UInt32 * reloadHDVICP, XDAS_UInt32 * configurationId,
        XDAS_Int32 lateAcquireArg)
{
    int Id = IRES_HDVICP2_ID_LATE_ACQUIRE;
    IRES_YieldArgs yieldArgs = NULL;

    if (NULL != configurationId) {
        Log_print4(Diags_ENTRY, "[+E] IRESMAN_HDVICP2_JITacquire> Enter "
                "(algHandle=0x%x, hdvicpHandle=0x%x, yieldCtxt=0x%x, "
                "configurationId=%d)",
                (IArg)algHandle, (IArg)hdvicpHandle, (IArg)yieldCtxt,
                (IArg)(*configurationId));
    }
    else {
        Log_print3(Diags_ENTRY, "[+E] IRESMAN_HDVICP2_JITacquire> Enter "
                "(algHandle=0x%x, hdvicpHandle=0x%x, yieldCtxt=0x%x, "
                "configurationId=NULL)",
                (IArg)algHandle, (IArg)hdvicpHandle, (IArg)yieldCtxt);
    }

    /* Populate the yield args */
    if (NULL != ti_sdo_fc_ires_hdvicp_HDVICP2_getYieldArgs) {

        Log_print1(Diags_USER4, "[+4] IRESMAN_HDVICP2_JITacquire> Alg 0x%x: "
                "Obtained yield arguments", (IArg)algHandle);

        yieldArgs = ti_sdo_fc_ires_hdvicp_HDVICP2_getYieldArgs(
                ((IRES_HDVICP2_IntObj *)hdvicpHandle)->scratchGroup);
    }

    if (((IRES_HDVICP2_IntObj *)hdvicpHandle)->lateAcquire) {

        /* Check orginal request Id here */
        if ( (((IRES_HDVICP2_IntObj*)hdvicpHandle)->reqId ==
                IRES_HDVICP2_ID_LATE_ACQUIRE) ||
                (((IRES_HDVICP2_IntObj*)hdvicpHandle)->reqId ==
                IRES_HDVICP2_ID_ANY)) {

            /* Late acquire any request */

            Log_print1(Diags_USER4, "[+4] IRESMAN_HDVICP2_JITacquire> "
                    "Alg 0x%x Late acquire requested ", (IArg)algHandle);

            if ((NULL != ti_sdo_fc_ires_hdvicp_HDVICP2_yieldRelease) &&
                    (NULL != ti_sdo_fc_ires_hdvicp_HDVICP2_yieldAcquire)) {

                Log_print1(Diags_USER4, "[+4] IRESMAN_HDVICP2_JITacquire> "
                        "Alg 0x%x Yielding lock/context to same/higher priority"
                        " alg.", (IArg)algHandle);

                ti_sdo_fc_ires_hdvicp_HDVICP2_yieldRelease(IRES_ALL, yieldCtxt,
                        yieldArgs);

                Id = _acquire(algHandle, reloadHDVICP, configurationId,
                        hdvicpHandle);

                Log_print1(Diags_USER4, "[+4] IRESMAN_HDVICP2_JITacquire> "
                        "Alg 0x%x Re-acquiring scratch group lock/context",
                        (IArg)algHandle);

                ti_sdo_fc_ires_hdvicp_HDVICP2_yieldAcquire(IRES_ALL, yieldCtxt,
                        yieldArgs);
            }
            else {
                Id = _acquire(algHandle, reloadHDVICP, configurationId,
                        hdvicpHandle);
            }

            Log_print2(Diags_USER4, "[+4] IRESMAN_HDVICP2_JITacquire> "
                    "Alg 0x%x Acquired IVAHD %d", (IArg)algHandle, (IArg)Id);
        }
        else {

            /* Late acquired specific resource */

            /* 2. If Id == #N */
            Id = ((IRES_HDVICP2_IntObj*)hdvicpHandle)->reqId;

            Log_print2(Diags_USER4, "[+4] IRESMAN_HDVICP2_JITacquire> "
                    "Alg 0x%x Trying to acquire IVAHD %d",
                    (IArg)algHandle, (IArg)Id);


            if ((NULL != ti_sdo_fc_ires_hdvicp_HDVICP2_yieldAcquire)  &&
                    (NULL != ti_sdo_fc_ires_hdvicp_HDVICP2_yieldRelease)) {

                Log_print1(Diags_USER4, "[+4] IRESMAN_HDVICP2_JITacquire> "
                        "Alg 0x%x Yielding lock/context to same/higher priority"
                        " alg.", (IArg)algHandle);

                ti_sdo_fc_ires_hdvicp_HDVICP2_yieldRelease( IRES_ALL, yieldCtxt,
                        yieldArgs);

                _acquireId(Id, algHandle, reloadHDVICP, configurationId,
                        hdvicpHandle);

                Log_print1(Diags_USER4, "[+4] IRESMAN_HDVICP2_JITacquire> "
                        "Alg 0x%x Re-acquiring lock/context ", (IArg)algHandle);

                ti_sdo_fc_ires_hdvicp_HDVICP2_yieldAcquire( IRES_ALL, yieldCtxt,
                        yieldArgs);
            }
            else {
                _acquireId(Id, algHandle, reloadHDVICP, configurationId,
                        hdvicpHandle);
            }

            Log_print2(Diags_USER4, "[+4] IRESMAN_HDVICP2_JITacquire> "
                    "Alg 0x%x Acquired IVAHD %d", (IArg)algHandle, (IArg)Id);
        }

        if (NULL != configurationId) {
            Log_print2(Diags_EXIT, "[+X] IRESMAN_HDVICP2_JITacquire> Exit "
                    "(reloadHDVICP=%d, configurationId=%d)",
                    (IArg)(*reloadHDVICP), (IArg)(*configurationId));
        }
        else {
            Log_print1(Diags_EXIT, "[+X] IRESMAN_HDVICP2_JITacquire> Exit "
                    "(reloadHDVICP=%d, configurationId=NULL)",
                    (IArg)(*reloadHDVICP));
        }

    }

    /* Return available resource */
    return;
}


/*
 *  ========  IRESMAN_HDVICP2_JITreacquire ========
 *  Function called by the algorithm to do a JIT acquire of the IVA-HD resource
 *  Before this, the process doesn't truly own the resource, unless it acquired
 *  it persistently (scratchGroupId -1)
 */
XDAS_UInt32 IRESMAN_HDVICP2_JITreacquire(IALG_Handle algHandle,
        IRES_HDVICP2_Obj * hdvicpHandle)
{

    /* Figure out last used IVAHD from the handle preferably ?! */
    XDAS_Int32 Id = hdvicpHandle->id;
    XDAS_UInt32 status = XDAS_FALSE;
    IArg key;

    Log_print2(Diags_ENTRY, "[+E] IRESMAN_HDVICP2_JITreacquire> Enter "
            "(algHandle=0x%x, hdvicpHandle=0x%x)",
            (IArg)algHandle, (IArg)hdvicpHandle);

    Log_print2(Diags_USER4, "[+4] IRESMAN_HDVICP2_JITreacquire> Last "
            "resource used by algHandle 0x%x %d", (IArg)algHandle, (IArg)Id);

    /* Id should be valid */
    Assert_isTrue(Id < _HDVICP2_NUMRES, (Assert_Id)NULL);

    key = IGateProvider_enter(gate);

    if ((algHandle == _HDVICP2_LATEALG(Id))) {

        _resmanInternalState->resourceBusy[Id] = -1;

        status = XDAS_TRUE;

        Log_print1(Diags_USER4, "[+4] IRESMAN_HDVICP2_JITreacquire> Resource %d active",
                (IArg)Id);
    }

    IGateProvider_leave(gate, key);

    if (status) {

        /* Update the handle with everything it needs */
        hdvicpHandle->id = Id;
        hdvicpHandle->memoryBaseAddress =
               (void *)HDVICP2_PARAMS.memoryBaseAddress[Id];
        hdvicpHandle->registerBaseAddress =
              (void *)HDVICP2_PARAMS.registerBaseAddress[Id];
        hdvicpHandle->resetControlAddress =
              (void *)HDVICP2_PARAMS.resetControlAddress[Id];
    }

    Log_print1(Diags_EXIT, "[+X] IRESMAN_HDVICP2_JITreacquire> Exit "
            "(status=0x%x)", (IArg)status);

    /* Return available resource */
    return (status);
}

/*
 *  ======== IRESMAN_HDVICP2_JITrelease ========
 *  Function called by the algorithm to do a JIT release of the IVA-HD resource
 *  After this, the process doesn't truly own the resource, unless it acquired
 *  it persistently (scratchGroupId -1)
 */
/* ARGSUSED */
Void IRESMAN_HDVICP2_JITrelease (IALG_Handle algHandle,
        IRES_HDVICP2_Obj * hdvicpHandle)
{

    XDAS_Int32 Id = hdvicpHandle->id;

    Log_print2(Diags_USER4, "[+4] IRESMAN_HDVICP2_JITrelease> "
            "Alg 0x%x Releasing IVAHD %d", (IArg)algHandle, (IArg)Id);

    /* Mark resource as available */
    _release(Id, algHandle, hdvicpHandle);

    Log_print2(Diags_USER4, "[+4] IRESMAN_HDVICP2_JITrelease> "
            "Alg 0x%x Released IVAHD %d", (IArg)algHandle, (IArg)Id);
}

/* NEW API to cleanup after lazy deactivates */
Void IRESMAN_HDVICP2_deactivateResource(IALG_Handle algHandle,
        IRES_Fxns * resFxns)
{
    Int i = -1;

    /* For all the resources, check if alghandle matches any of freed
       resources that might have been lazily deactivated */

    for (i = 0; i < _HDVICP2_NUMRESOURCES ; i++) {

        if ((_resmanInternalState->resourceBusy[i] ==
                IRESMAN_HDVICP2_RESOURCEFREE) &&
                (algHandle == _HDVICP2_LATEALG(i))) {

            resFxns->deactivateResource((IALG_Handle) algHandle,
                    (IRES_Handle)_HDVICP2_LATERES(i));

            /* Indiate that the resource has been deactivated */
            _HDVICP2_LATEALG(i) = ALGNULL;
        }
    }
}

/*
 *  ======== _acquireSpecific ========
 *  Blocking function used to acquire a specific IVA-HD resource if/when it is
 *  available
 */
static Void _acquireSpecific(XDAS_Int32 Id, IALG_Handle alg,
        XDAS_UInt32 *reloadHDVICP, XDAS_UInt32 *configurationId,
        IRES_HDVICP2_Handle h)
{
    IArg key;
    UInt tempmode = 0;
    IRES_Fxns * lateResFxns = NULL;
    IRES_HDVICP2_Handle lateResHandle = NULL;
    IRES_Fxns * currResFxns = NULL;


    if (NULL != configurationId) {
        Log_print3(Diags_ENTRY, "[+E] _acquireSpecific> Enter (IVAHD=%d, "
                "alg=0x%x, configurationId=0x%x)",
                (IArg)Id, (IArg)alg, (IArg)(*configurationId));
    }
    else {
        Log_print2(Diags_ENTRY, "[+E] _acquireSpecific> Enter (IVAHD=%d, "
                "alg=0x%x, configurationId=NULL)", (IArg)Id, (IArg)alg);
    }

    while (1) {

        key = IGateProvider_enter(gate);

        /* Resource should be not be BUSY ( assigned as S or P or L ) */
        if (_resmanInternalState->resourceBusy[Id]
                == IRESMAN_HDVICP2_RESOURCEFREE) {

            /* If available, grab it !*/
            _resmanInternalState->resourceBusy[Id] = -1;

            /* Update flag if current alg not same as LASTALG */
            if (_HDVICP2_LATEALG(Id) == alg) {

                *reloadHDVICP = SAMECODEC;

                Log_print2(Diags_USER2, "[+2] _acquireSpecific> Acquired %d "
                        " with status %d", (IArg)Id, (IArg)(*reloadHDVICP));

                /* No activation or deactivation required here */
            }
            else {

                if (alg->fxns->implementationId == _HDVICP2_LASTCLASS(Id)) {

                    *reloadHDVICP = SAMECODECTYPE;

                }
                else {
                    *reloadHDVICP = DIFFERENTCODEC;
                }

                Log_print2(Diags_USER2, "[+2] _acquireSpecific> Acquired %d "
                        " with status %d", (IArg)Id, (IArg)(*reloadHDVICP));

                /* Granting same IVAHD to different alg, deactivate prev
                   owner if still active */
                if (ALGNULL != _HDVICP2_LATEALG(Id)) {

                    Log_print2(Diags_USER2, "[+2] _acquireSpecific> Calling "
                            " deactivate ctxt for IVAHD %d alg 0x%x",
                            (IArg)Id, (IArg)(_HDVICP2_LATEALG(Id)));

                    /* 1. Obtain the IRES handle for this alg */
                    lateResFxns = RMAN_getIresEntry((_HDVICP2_LATEALG(Id)));

                    /* 2. Obtain the "resourceHandle" res for this alg */
                    lateResHandle = (IRES_HDVICP2_Handle)(_HDVICP2_LATERES(Id));

                    /* 3. Call deactivateResource(LATEALG, LATERES) */
                    lateResFxns->deactivateResource((IALG_Handle)
                            _HDVICP2_LATEALG(Id),(IRES_Handle)lateResHandle);

                }

                /* 4. Call activateResource(alg, h) */
                currResFxns = RMAN_getIresEntry(alg);

                /* Update the handle with everything it needs */
                h->id = Id;
                h->memoryBaseAddress =
                        (void *)HDVICP2_PARAMS.memoryBaseAddress[Id];
                h->registerBaseAddress =
                        (void *)HDVICP2_PARAMS.registerBaseAddress[Id];
                h->resetControlAddress =
                (void *)HDVICP2_PARAMS.resetControlAddress[Id];
                currResFxns->activateResource(alg, (IRES_Handle)h);

                /* Update LASTALG */
                /* We actually need to do this only during release */
                _HDVICP2_LATEALG(Id) = (IALG_Handle)alg;
                _HDVICP2_LATERES(Id) = (IRES_HDVICP2_Handle)(h);
            }

            if (NULL != configurationId) {
                    tempmode = *configurationId;
                    *configurationId = _HDVICP2_LASTMODE(Id);
                Log_print1(Diags_USER2, "[+2] _acquireSpecific> "
                        "configurationId 0x%x", (IArg)(*configurationId));
            }
            else {
                tempmode = NULL;
            }
             _HDVICP2_LASTMODE(Id) = tempmode;

            /* Update total free */
            _HDVICP2_TOTALFREE--;

            IGateProvider_leave(gate, key);

            break;
        }
        else {

            Log_print1(Diags_USER2, "[+2] _acquireSpecific> Resource %d not "
                    "available, pending on it", (IArg)Id);

            IGateProvider_leave(gate, key);

            /* Wakes up when this particular resource is freed */
            _HDVICP2_SEMPEND(Id);

            /* But there might be a higher priority alg waiting on
               ANY resource, so play nice */
            /* Unblock a same/higher priority wait on ANYRESOURCE so that
               so that priority inversion doesn't occur because of ordering of
               SEMPOST in the _release call */
           _HDVICP2_SEMPOST(ANYRESOURCE);

            /* We are back, check if resource still available */
        }
    }

    Log_print0(Diags_EXIT, "[+X] _acquireSpecific> Exit");

    return;
}

/*
 *  ======== _acquireSpecificPlugin ========
 *  Blocking function used to acquire a specific IVA-HD resource if/when it is
 *  available
 */
static Void _acquireSpecificPlugin(XDAS_Int32 Id, IALG_Handle alg,
        XDAS_UInt32 *reloadHDVICP, XDAS_UInt32 *configurationId,
        IRES_HDVICP2_Handle h)
{

    IArg key;
    UInt tempmode = 0;
    IRES_Fxns * lateResFxns = NULL;
    IRES_HDVICP2_Handle lateResHandle = NULL;
    IRES_Fxns * currResFxns = NULL;
#ifdef UTILS_ENCDEC_HDVICP_PROFILE     
    XDAS_UInt32 activateEndTime = 0, activateStartTime = 0;
#endif

    if (NULL != configurationId) {
        Log_print3(Diags_ENTRY, "[+E] _acquireSpecific> Enter (IVAHD=%d, "
                "alg=0x%x, configurationId=0x%x)",
                (IArg)Id, (IArg)alg, (IArg)(*configurationId));
    }
    else {
        Log_print2(Diags_ENTRY, "[+E] _acquireSpecific> Enter (IVAHD=%d, "
                "alg=0x%x, configurationId=NULL)", (IArg)Id, (IArg)alg);
    }

    /* Call Plugin API */
    key = IGateProvider_enter(gate);

    if (IRES_OK == ti_sdo_fc_ires_hdvicp_HDVICP2_getHdvicp2Fxn(&Id, alg, h)) {

        while (1) {

            if (_resmanInternalState->resourceBusy[Id] ==
                    IRESMAN_HDVICP2_RESOURCEFREE) {

                /* If available, grab it !*/
                _resmanInternalState->resourceBusy[Id] = -1;
#ifdef UTILS_ENCDEC_HDVICP_PROFILE
                UInt32 curTime = Utils_encdecGetTime ();

                if (g_HDVICP_logTbl[Id].startTime == 0) {
                  g_HDVICP_logTbl[Id].startTime = curTime;
                } else {
                  g_HDVICP_logTbl[Id].totalAcq2acqDelay +=
                    (curTime - g_HDVICP_logTbl[Id].endTime);
                }
                g_HDVICP_logTbl[Id].tempAcquireTime = curTime;     
#endif                
                /* Update flag if current alg not same as LASTALG */
                if ((_HDVICP2_LATEALG(Id) == alg) &&
/* TODO: Check what the last used IVAHD was by this alg */
                            (h->id == Id)) {

                    *reloadHDVICP = SAMECODEC;

                    Log_print2(Diags_USER2, "[+2] _acquireSpecific> Acquired %d"
                            " with status %d", (IArg)Id, (IArg)(*reloadHDVICP));

                    /* No activation or deactivation required here */
                }
                else {

                    if (alg->fxns->implementationId == _HDVICP2_LASTCLASS(Id)) {

                        *reloadHDVICP = SAMECODECTYPE;

                    }
                    else {
                        *reloadHDVICP = DIFFERENTCODEC;
                    }

                    Log_print2(Diags_USER2, "[+2] _acquireSpecific> Acquired %d"
                        " with status %d", (IArg)Id, (IArg)(*reloadHDVICP));
#ifdef UTILS_ENCDEC_HDVICP_PROFILE                    
                    activateStartTime = Timestamp_get32 ();
#endif                    
                    /* Granting same IVAHD to different alg, restore the context
                       if saved here */
                    if (ALGNULL != _HDVICP2_LATEALG(Id)) {

                        Log_print2(Diags_USER2, "[+2] _acquireSpecific> Calling"
                                " deactivate ctxt for IVAHD %d alg 0x%x",
                                (IArg)Id, (IArg)(_HDVICP2_LATEALG(Id)));

                        /* 1. Obtain the IRES handle for this alg */
                        lateResFxns = RMAN_getIresEntry((_HDVICP2_LATEALG(Id)));

                        /* 2. Obtain the "resourceHandle" res for this alg */
                        lateResHandle = (IRES_HDVICP2_Handle)
                                (_HDVICP2_LATERES(Id));

                        /* 3. Call deactivateResource(LATEALG, LATERES) */
                        lateResFxns->deactivateResource(
                                (IALG_Handle) _HDVICP2_LATEALG(Id),
                                (IRES_Handle)lateResHandle);

                    }

                    /* This alg previously used some other resource */
                    if ((h->id >= 0) && (h->id != Id) &&
                            (_HDVICP2_LATEALG(h->id) != ALGNULL)) {
                        lateResFxns = RMAN_getIresEntry(alg);

                        /* Need to deactivate previously used resource */
                        lateResFxns->deactivateResource(alg, (IRES_Handle)h);
                        _HDVICP2_LATEALG(h->id) = ALGNULL;
                    }


                    /* 4. Call activateResource(alg, h) */
                    currResFxns = RMAN_getIresEntry(alg);

                    /* Update the handle with everything it needs */
                    h->id = Id;
                    h->memoryBaseAddress =
                            (void *)HDVICP2_PARAMS.memoryBaseAddress[Id];
                    h->registerBaseAddress =
                            (void *)HDVICP2_PARAMS.registerBaseAddress[Id];
                    h->resetControlAddress =
                            (void *)HDVICP2_PARAMS.resetControlAddress[Id];

                    currResFxns->activateResource(alg, (IRES_Handle)h);

                    /* Update LASTALG */
                    /* We may need to do this only during release */
                    _HDVICP2_LATEALG(Id) = (IALG_Handle)alg;
                    _HDVICP2_LATERES(Id) = (IRES_HDVICP2_Handle)h;
#ifdef UTILS_ENCDEC_HDVICP_PROFILE                    
                    activateEndTime = Timestamp_get32 ();
                    if (activateEndTime >= activateStartTime)
                    {
                        g_HDVICP_logTbl[Id].totalIVAHDActivateTime += (activateEndTime -
                                                                       activateStartTime);
                    }
                    else
                    {
                        g_HDVICP_logTbl[Id].totalIVAHDActivateTime += (0xFFFFFFFF - activateStartTime) +
                                                                                    activateEndTime;                    
                    }
#endif                     
                }

                if (NULL != configurationId) {
                    tempmode = *configurationId;
                    *configurationId = _HDVICP2_LASTMODE(Id);
                    Log_print1(Diags_USER2, "[+2] _acquireSpecific> "
                            "configurationId 0x%x", (IArg)(*configurationId));
                }
                else {
                    tempmode = NULL;
                }

                _HDVICP2_LASTMODE(Id) = tempmode;

                /* Update total free */
                _HDVICP2_TOTALFREE--;

                IGateProvider_leave(gate, key);

                break;
            }
            else {

                Log_print1(Diags_USER2, "[+2] _acquireSpecific> Resource %d not"
                        " available, pending on it", (IArg)Id);

                IGateProvider_leave(gate, key);

                /* Wakes up when any resource is freed */
                _HDVICP2_SEMPEND(Id);

                /* But play nice, see if there are same/higher priority
                   requestors that are waiting */
                /* Unblock a same/higher priority wait on ANYRESOURCE so that
                   so that priority inversion doesn't occur because of ordering
                   of SEMPOST in the _release call */
                _HDVICP2_SEMPOST(ANYRESOURCE);

                /* We are back, check if resource still  available */
                key = IGateProvider_enter(gate);
            }
        }
    }
    else {

        IGateProvider_leave(gate, key);

        /* Not sure what to do if there is an error from scheduler */
        Assert_isTrue(0, (Assert_Id)NULL);
    }

    Log_print0(Diags_EXIT, "[+X] _acquireSpecific> Exit");

    return;
}

/*
 *  ======== _acquireAny ========
 *  Blocking function used to acquire any IVA-HD resource if/when it is
 *  available
 */
static XDAS_Int32 _acquireAny(IALG_Handle alg,
        XDAS_UInt32 *reloadHDVICP, XDAS_UInt32 * configurationId,
        IRES_HDVICP2_Handle h)
{
    IArg key;
    Bool found = FALSE;
    XDAS_Int32 resId = -1;
    Int i;
    UInt tempmode = 0;
    IRES_Fxns * lateResFxns = NULL;
    IRES_HDVICP2_Handle lateResHandle = NULL;
    IRES_Fxns * currResFxns = NULL;

    if (NULL != configurationId) {
        Log_print2(Diags_ENTRY, "[+E] _acquireAny> Enter (alg=0x%x, "
                "configurationId=0x%x)", (IArg)alg, (IArg)(*configurationId));
    }
    else {
        Log_print1(Diags_ENTRY, "[+E] _acquireAny> Enter (alg=0x%x, "
                "configurationId=NULL)", (IArg)alg);
    }

    while (1) {

        key = IGateProvider_enter(gate);

        /* Start checking resources only if there is atleast one free resource
         */
        if (_HDVICP2_TOTALFREE != 0) {

            Log_print0(Diags_USER2, "[+2] _acquireAny> Trying to grab the "
                    "resource last used");

            /* Check to see if something has ever been assigned to this alg */
            if (h->id != IRES_HDVICP2_ID_LATE_ACQUIRE) {

                i = h->id;

                Assert_isTrue(i < _HDVICP2_NUMRES, (Assert_Id)NULL);

                /* Grabbing the same resource that was used previously by the alg,
                   saves precious RELOAD time for the alg */
                if ( (_resmanInternalState->resourceBusy[i] ==
                                IRESMAN_HDVICP2_RESOURCEFREE)
                                        && (alg == _HDVICP2_LATEALG(i))) {

                    resId = i;
                    found = TRUE;

                    Log_print1(Diags_USER2, "[+2] _acquireAny> Found %d",
                            (IArg)resId);

                }
            }

            if (!found) {

                Log_print0(Diags_USER2, "[+2] _acquireAny> Trying to grab the "
                        "resource last used by an alg of same type");

                /* Second try and acquire a matching CLASS resource if
                   available */

                for (i = 0; i < _HDVICP2_NUMRES; i++) {

                    /* Grabbing a resource that was used previously by an alg
                       of the same class, saves some program RELOAD time for
                       the alg */

                    if ( (_resmanInternalState->resourceBusy[i] ==
                            IRESMAN_HDVICP2_RESOURCEFREE) &&
                                    (alg->fxns->implementationId
                            == _HDVICP2_LASTCLASS(i))) {

                        resId = i;
                        found = TRUE;

                        Log_print1(Diags_USER2, "[+2] _acquireAny> Found %d",
                                (IArg)resId);

                        break;
                    }
                }
            }

            if (!(found)) {

                Log_print0(Diags_USER2, "[+2] _acquireAny> Trying to grab any "
                        "free resource");

                /* Third, try and acquire any free resource */
                for (i = 0; i < _HDVICP2_NUMRES; i++) {

                    if (_resmanInternalState->resourceBusy[i] ==
                                        IRESMAN_HDVICP2_RESOURCEFREE) {
                        resId = i;
                        found = TRUE;

                        Log_print1(Diags_USER2, "[+2] _acquireAny> Found %d",
                                (IArg)resId);
                        break;
                    }
                }
            }

            /* Found a good resource */
            if (found) {

                /* Mark resource as busy */
                _resmanInternalState->resourceBusy[resId] = -1;

                /* Update the flag depending on whether alg is same as LASTALG*/
                if (_HDVICP2_LATEALG(resId) == alg) {

                    *reloadHDVICP = SAMECODEC;

                    Log_print2(Diags_USER2, "[+2] _acquireAny> Acquired %d "
                            " with status %d", (IArg)resId,
                            (IArg)(*reloadHDVICP));
                }
                else {

                    if (alg->fxns->implementationId ==
                            _HDVICP2_LASTCLASS(resId)) {
                        *reloadHDVICP = SAMECODECTYPE;
                    }
                    else {
                        /* Update LASTALG */
                        *reloadHDVICP = DIFFERENTCODEC;
                    }

                    Log_print2(Diags_USER2, "[+2] _acquireAny> Acquired %d "
                            " with status %d", (IArg)resId,
                            (IArg)(*reloadHDVICP));

                    if (ALGNULL != _HDVICP2_LATEALG(resId)) {

                        Log_print2(Diags_USER2, "[+2] _acquireSpecific> Calling"
                                " deactivate ctxt for IVAHD %d alg 0x%x",
                                (IArg)resId, (IArg)(_HDVICP2_LATEALG(resId)));

                        /* 1. Obtain the IRES handle for this alg */
                       lateResFxns = RMAN_getIresEntry(_HDVICP2_LATEALG(resId));

                        /* 2. Obtain the "resourceHandle" res for this alg */
                        lateResHandle = (IRES_HDVICP2_Handle)(
                                _HDVICP2_LATERES(resId));

                        /* 3. Call deactivateResource(LATEALG, LATERES) */
                        lateResFxns->deactivateResource(
                                (IALG_Handle)_HDVICP2_LATEALG(resId),
                                (IRES_Handle)lateResHandle);
                    }

                    /* 4. Call activateResource(alg, h) */
                    currResFxns = RMAN_getIresEntry(alg);

                    /* Need to populate "h" with the actual resource Id
                       before calling activate */
                    h->id = resId;
                    h->memoryBaseAddress =
                            (void *)HDVICP2_PARAMS.memoryBaseAddress[resId];
                    h->registerBaseAddress =
                            (void *)HDVICP2_PARAMS.registerBaseAddress[resId];
                    h->resetControlAddress =
                            (void *)HDVICP2_PARAMS.resetControlAddress[resId];

                    currResFxns->activateResource(alg, (IRES_Handle)h);

                    /* Update LASTALG */
                    /* We actually need to do this only during release */
                    _HDVICP2_LATEALG(resId) = alg;
                    _HDVICP2_LATERES(resId) = h;
                }

                if (NULL != configurationId) {

                    /* Update and store the configurationId */
                    tempmode = *configurationId;
                    *configurationId = _HDVICP2_LASTMODE(resId);
                    Log_print1(Diags_USER2, "[+2] _acquireAny> configurationId"
                            " 0x%x", (IArg)(*configurationId));
                }
                else {
                    tempmode = NULL;
                }
                _HDVICP2_LASTMODE(resId) = tempmode;

                /* Update total free */
                _HDVICP2_TOTALFREE--;

                /* Found, grab and exit the while loop */
                IGateProvider_leave(gate, key);
                break;
            }
       }

       Log_print0(Diags_USER2, "[+2] _acquireAny> Resources not "
                    "available, pending on them");

       /* Pend on it, after exiting the gate */
       IGateProvider_leave(gate, key);

       _HDVICP2_SEMPEND(ANYRESOURCE);
       /* Wakes up when ANY resource is freed */
    }

    Log_print1(Diags_EXIT, "[+X] _acquireAny> Exit (resId=%d)", (IArg)resId);
    return (resId);
}

/*
 *  ======== _acquireAnyPlugin ========
 *  Blocking function used to acquire any IVA-HD resource if/when it is
 *  available
 */
static XDAS_Int32 _acquireAnyPlugin(IALG_Handle alg,
        XDAS_UInt32 *reloadHDVICP, XDAS_UInt32 * configurationId,
        IRES_HDVICP2_Handle h)
{
    IArg key;
    XDAS_Int32 resId = IRES_HDVICP2_ID_ANY;
    UInt tempmode = 0;
    IRES_Fxns * lateResFxns = NULL;
    IRES_HDVICP2_Handle lateResHandle = NULL;
    IRES_Fxns * currResFxns = NULL;
#ifdef UTILS_ENCDEC_HDVICP_PROFILE     
    XDAS_UInt32 activateEndTime = 0, activateStartTime = 0;
#endif


    if (NULL != configurationId) {
        Log_print2(Diags_ENTRY, "[+E] _acquireAny> Enter (alg=0x%x, "
                "configurationId=0x%x)", (IArg)alg, (IArg)(*configurationId));
    }
    else {
        Log_print1(Diags_ENTRY, "[+E] _acquireAny> Enter (alg=0x%x, "
                "configurationId=NULL)", (IArg)alg);
    }

    key = IGateProvider_enter(gate);

    /* Find out what resource scheduler has assigned */
    if (IRES_OK == ti_sdo_fc_ires_hdvicp_HDVICP2_getHdvicp2Fxn(&resId, alg, h)){

         Log_print1(Diags_USER2, "[+2] _acquireAny> Trying to acquire %d",
                (IArg)resId);

         /* Now to wait for that resource to become available */
         while (1) {

            /* Start checking resources only if there is atleast one free
               resource */
            if (_HDVICP2_TOTALFREE != 0) {

                if (_resmanInternalState->resourceBusy[resId] ==
                        IRESMAN_HDVICP2_RESOURCEFREE) {

#ifdef UTILS_ENCDEC_HDVICP_PROFILE
                    {
                      UInt32 curTime = Utils_encdecGetTime();
                      if (g_HDVICP_logTbl[resId].startTime == 0) {
                        g_HDVICP_logTbl[resId].startTime = curTime;
                      } else {
                        g_HDVICP_logTbl[resId].totalAcq2acqDelay += 
                          (curTime - g_HDVICP_logTbl[resId].endTime);
                      }
                      g_HDVICP_logTbl[resId].tempAcquireTime = curTime;
                    }
#endif

                    /* Mark resource as busy */
                    _resmanInternalState->resourceBusy[resId] = -1;

                    /* Update the flag depending on whether alg is same as
                       LASTALG*/
                    if ((_HDVICP2_LATEALG(resId) == alg) &&
/* TODO: Check what the last used IVAHD was by this alg */
                            (h->id == resId)) {

                        *reloadHDVICP = SAMECODEC;

                        Log_print2(Diags_USER2, "[+2] _acquireAny> Acquired %d "
                                " with status %d", (IArg)resId,
                                (IArg)(*reloadHDVICP));
                    }
                    else {

                        if (alg->fxns->implementationId ==
                                _HDVICP2_LASTCLASS(resId)) {
                            *reloadHDVICP = SAMECODECTYPE;
                        }
                        else {
                            /* Update LASTALG */
                            *reloadHDVICP = DIFFERENTCODEC;
                        }

                        Log_print2(Diags_USER2, "[+2] _acquireAny> Acquired %d "
                                " with status %d", (IArg)resId,
                                (IArg)(*reloadHDVICP));
#ifdef UTILS_ENCDEC_HDVICP_PROFILE                    
                    activateStartTime = Timestamp_get32 ();
#endif                    

                        if (ALGNULL != _HDVICP2_LATEALG(resId)) {

                            Log_print2(Diags_USER2, "[+2] _acquireAny> "
                                    "Calling deactivate ctxt for IVAHD %d alg "
                                    "0x%x", (IArg)resId,
                                    (IArg)(_HDVICP2_LATEALG(resId)));

                            /* 1. Obtain the IRES handle for this alg */
                            lateResFxns = RMAN_getIresEntry(
                                    _HDVICP2_LATEALG(resId));

                            /* 2. Obtain the "resourceHandle" res for this alg*/
                            lateResHandle = (IRES_HDVICP2_Handle)(
                                    _HDVICP2_LATERES(resId));

                            /* 3. Call deactivateResource(LATEALG, LATERES) */
                            lateResFxns->deactivateResource(
                                    (IALG_Handle)_HDVICP2_LATEALG(resId),
                                    (IRES_Handle)lateResHandle);

                        }

                        /* This alg previously used some other resource */
                       if ((h->id >= 0) && (h->id != resId) &&
                                /* Not yet deactivated */
                                (_HDVICP2_LATEALG(h->id) != ALGNULL)) {
                            lateResFxns = RMAN_getIresEntry(alg);

                            /* Need to deactivate previously used resource */
                            lateResFxns->deactivateResource(alg,(IRES_Handle)h);
                            _HDVICP2_LATEALG(h->id) = ALGNULL;
                        }

                        /* 4. Call activateResource(alg, h) */
                        currResFxns = RMAN_getIresEntry(alg);

                        /* Need to populate "h" with teh actual resource Id
                           before calling activate */

                        h->id = resId;
                        h->memoryBaseAddress =
                                (void *)HDVICP2_PARAMS.memoryBaseAddress[resId];
                        h->registerBaseAddress =
                                (void *)HDVICP2_PARAMS.registerBaseAddress
                                [resId];
                        h->resetControlAddress =
                                (void *)HDVICP2_PARAMS.resetControlAddress
                                [resId];

                        currResFxns->activateResource(alg, (IRES_Handle)h);

                        /* Update LASTALG */
                        /* We may need to do this only during release */
                        _HDVICP2_LATEALG(resId) = alg;
                        _HDVICP2_LATERES(resId) = h;
#ifdef UTILS_ENCDEC_HDVICP_PROFILE                    
                         activateEndTime = Timestamp_get32 ();
                         if (activateEndTime >= activateStartTime)
                         {
                             g_HDVICP_logTbl[resId].totalIVAHDActivateTime += (activateEndTime -
                                                                           activateStartTime);
                         }
                         else
                         {
                             g_HDVICP_logTbl[resId].totalIVAHDActivateTime += (0xFFFFFFFF - activateStartTime) +
                                                                                         activateEndTime;                    
                         }
#endif                     
                        
                    }

                    if (NULL != configurationId) {

                        /* Update and store the configurationId */
                            tempmode = *configurationId;
                            *configurationId = _HDVICP2_LASTMODE(resId);
                        Log_print1(Diags_USER2, "[+2] acquireAny> "
                                "configurationId 0x%x",
                                (IArg)(*configurationId));
                    }
                    else {
                        tempmode = NULL;
                    }
                        _HDVICP2_LASTMODE(resId) = tempmode;

                    /* Update total free */
                    _HDVICP2_TOTALFREE--;

                    /* Found, grab and exit the while loop */
                    IGateProvider_leave(gate, key);
                    break;
                }
            }

            Log_print0(Diags_USER2, "[+2] _acquireAny> Resources not "
                    "available. Leaving gate");

            /* Pend on it, after exiting the gate */
            IGateProvider_leave(gate, key);

            Log_print0(Diags_USER2, "[+2] _acquireAny> Calling pend.");

            /* Wakes up when ANY resource is freed */
            _HDVICP2_SEMPEND(ANYRESOURCE);

            key = IGateProvider_enter(gate);
            Log_print0(Diags_USER2, "[+2] _acquireAny> Entered gate.");
        }
    }
    else {

        IGateProvider_leave(gate, key);

        /* Don't know what to do when an error is returned from external
           scheduler */
        Assert_isTrue(0, (Assert_Id)NULL);
    }

    Log_print1(Diags_EXIT, "[+X] _acquireAny> Exit (resId=%d)", (IArg)resId);
    return (resId);
}

static Void _releaseSpecific(XDAS_Int32 Id, IALG_Handle alg,
        IRES_HDVICP2_Handle hdvicp2)
{
    IArg key;

    key = IGateProvider_enter(gate);

    Log_print0(Diags_USER2, "[+2] _releaseSpecific> Entered gate.");

    /* Mark resource available */

    /* Issue a post for each pending acquire */
    _resmanInternalState->resourceBusy[Id] = IRESMAN_HDVICP2_RESOURCEFREE;

   /* Update total free resources */
    _HDVICP2_TOTALFREE++;

    _resmanInternalState->lateHdvicp[Id] = hdvicp2 ;

    Log_print1(Diags_USER2, "[+2] _releaseSpecific> Freed resource %d leaving "
            "gate.", Id);

    IGateProvider_leave(gate, key);

    /* Need to make sure either type of resources requests will get unblocked */
    /* Note:- Only one resource is freed, but we have 2 SEMPOSTs; this is reqd
       since there could be threads that are SEMPENDing on specific IVAHDs or
       ANY IVAHD. This may result in 1 redundant context switch, but that's a
       cost we pay to support LATEACQUIRE requests of type ANY and Specific IDs
     */
    Log_print0(Diags_USER2, "[+2] _releaseSpecific> Posting semaphores to "
            "indicate free resource.");

    _HDVICP2_SEMPOST(Id);
    _HDVICP2_SEMPOST(ANYRESOURCE);

    /* After the gate is exited, threads waiting for this/any resource, get
       scheduled and check if this resource is good for them */
    Log_print0(Diags_EXIT, "[+X] _releaseSpecific> Exit ");
}

static Void _releaseSpecificPlugin(XDAS_Int32 Id, IALG_Handle alg,
        IRES_HDVICP2_Handle hdvicp2)
{
    IArg key;

    /* We better be freeing what we've acquired !! */
    Assert_isTrue(_resmanInternalState->resourceBusy[Id] !=
            IRESMAN_HDVICP2_RESOURCEFREE, (Assert_Id)NULL);

    key = IGateProvider_enter(gate);

    Log_print0(Diags_USER2, "[+2] _releaseSpecific> Entered gate.");

#ifdef UTILS_ENCDEC_HDVICP_PROFILE
    {
      UInt32 curTime = Utils_encdecGetTime();

      g_HDVICP_logTbl[Id].totalAcquire2Release +=
        (curTime - g_HDVICP_logTbl[Id].tempAcquireTime);
      g_HDVICP_logTbl[Id].endTime = curTime;

      g_HDVICP_logTbl[Id].numAccessCnt += 1; /* Assume batch size as 1 */
    }
#endif

    /* Call plugin function to release */
    ti_sdo_fc_ires_hdvicp_HDVICP2_freeHdvicp2Fxn(Id, alg, hdvicp2);

    /* Mark resource available */
    _resmanInternalState->resourceBusy[Id] = IRESMAN_HDVICP2_RESOURCEFREE;

    /* Update total free resources */
    _HDVICP2_TOTALFREE++;

    _resmanInternalState->lateHdvicp[Id] = hdvicp2 ;

    Log_print1(Diags_USER2, "[+2] _releaseSpecific> Freed resource %d leaving "
            "gate.", Id);

    IGateProvider_leave(gate, key);

    /* Note:- Only one resource is freed, but we have 2 SEMPOSTs; this is reqd
       since there could be threads that are SEMPENDing on specific IVAHDs or
       ANY IVAHD. This may result in 1 redundant context switch, but that's a
       cost we pay to support LATEACQUIRE requests of type ANY and Specific IDs
     */

    Log_print0(Diags_USER2, "[+2] _releaseSpecific> Posting semaphores to "
            "indicate free resource.");

    _HDVICP2_SEMPOST(Id);
    _HDVICP2_SEMPOST(ANYRESOURCE);

    /* After the gate is exited, threads waiting for this/any resource, get
       scheduled and check if this resource is good for them */
    Log_print0(Diags_EXIT, "[+X] _releaseSpecific> Exit ");
}

static inline Void freeRes(XDAS_Int32 Id, IALG_Handle alg, Int scratchGroupId)
{
    IArg key;

    if (Id != IRES_HDVICP2_ID_LATE_ACQUIRE) {

        key = IGateProvider_enter(gate);

        _resmanInternalState->refCount[Id]-- ;

        /* If ref Count is 0, mark resource as free */
        if ( 0 == _resmanInternalState->refCount[Id]) {

            _resmanInternalState->resourceBusy[Id] =
                    IRESMAN_HDVICP2_RESOURCEFREE;

        }

        /* Clear resource owner */
        _resmanInternalState->alg[Id] = ALGNULL;

        /* If the alg freeing the resource, was the last one to have actually
           "used" it, change the the LASTALG field of that Id to ALGNULL.
           This is to guard against future algorithms that may be created
           with the same algHandle as one getting deleted
           This is NR, since LATEALG is now used only JIT,
           which should come here
        if (alg == _HDVICP2_LATEALG(Id) ) {

            _HDVICP2_LATEALG(Id) = ALGNULL;
        }
        */

        IGateProvider_leave(gate, key);
    }
}


IRESMAN_Fxns IRESMAN_HDVICP =  {
    IRESMAN_HDVICP2_getProtocolName,
    IRESMAN_HDVICP2_getProtocolRevision,
    IRESMAN_HDVICP2_init,
    IRESMAN_HDVICP2_exit,
    IRESMAN_HDVICP2_getHandles,
    IRESMAN_HDVICP2_freeHandles,
    NULL,
    IRESMAN_HDVICP2_deactivateResource
};

IRESMAN_HdVicpParams IRESMAN_HDVICP2_DEFAULTPARAM;

IRESMAN_Fxns * HDVICP2_getIresmanFxns()
{
    return ((Void *)(&IRESMAN_HDVICP));
}

IRESMAN_Params * HDVICP2_getDefaultParams()
{
    IRESMAN_HDVICP2_DEFAULTPARAM.baseConfig.size = sizeof(IRESMAN_Params);

    /* Don't need to populate this, xdt will figure this one out */
    /* IRESMAN_HDVICP_DEFAULTPARAM->numResources = 2;*/
    return ((IRESMAN_Params *)&IRESMAN_HDVICP2_DEFAULTPARAM);
}
