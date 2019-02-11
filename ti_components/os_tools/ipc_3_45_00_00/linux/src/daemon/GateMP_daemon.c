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
 *  ======== GateMP_daemon.c ========
 */


/* Standard headers */
#include <ti/ipc/Std.h>

/* Linux specific header files */
#include <pthread.h>

/* System headers */
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

/* Module level headers */
#include <ti/ipc/GateMP.h>
#include <ti/ipc/NameServer.h>
#include <ti/ipc/MultiProc.h>
#include <_MultiProc.h>
#include <GateMP_config.h>
#include <_GateMP.h>

#include <IGateProvider.h>
#include <_GateMP_daemon.h>
#include <_lad.h>

#if defined (__cplusplus)
extern "C" {
#endif

#define NUM_INFO_FIELDS       6    /* Number of fields in info entry */

/* Values used to populate the resource 'inUse' arrays */
#define UNUSED          ((UInt8)0)
#define USED            ((UInt8)1)
#define RESERVED        ((UInt8)-1)

/* Name of GateMP's nameserver */
#define GateMP_NAMESERVER  "GateMP"

/* sysfs path for the UIO user-space drivers */
#define UIO_SYSFS          "/sys/class/uio"

#define PAGE_ALIGN(size, psz)  (((size) + psz - 1) & ~(psz -1))

/* =============================================================================
 * Structures & Enums
 * =============================================================================
 */

/* structure for GateMP module state */
typedef struct {
    Int               numRemoteSystem;
    Int               numRemoteCustom1;
    Int               numRemoteCustom2;
    UInt8 *           remoteSystemInUse;
    UInt8 *           remoteCustom1InUse;
    UInt8 *           remoteCustom2InUse;
    GateMP_Handle     defaultGate;
    NameServer_Handle nameServer;
    Bool              isSetup;
    Int               refCount[MultiProc_MAXPROCESSORS];
    UInt16            attachedProcId;
} GateMP_ModuleObject;

/* Internal functions */
static Int GateMP_get_sr0(Char *name, UInt32 name_len, UInt32 *baseaddr);
static Int GateMP_openDefaultGate(GateMP_Handle *handlePtr, UInt16 procId[]);
static Int GateMP_closeDefaultGate(GateMP_Handle *handlePtr);

/* =============================================================================
 *  Globals
 * =============================================================================
 */
/*
 * GateMP_state
 */
static GateMP_ModuleObject GateMP_state = {
    .numRemoteSystem                 = 0,
    .numRemoteCustom1                = 0,
    .numRemoteCustom2                = 0,
    .remoteSystemInUse               = NULL,
    .remoteCustom1InUse              = NULL,
    .remoteCustom2InUse              = NULL,
    .defaultGate                     = NULL,
    .nameServer                      = NULL,
    .isSetup                         = FALSE,
    .refCount                        = {0},
    .attachedProcId                  = MultiProc_INVALIDID,
};

static GateMP_ModuleObject * GateMP_module = &GateMP_state;

/* =============================================================================
 * APIS
 * =============================================================================
 */

/*
 * Function to setup the gatemp module.
 *
 * No need to refCount this since it's not callable by user.
 */
Int GateMP_setup(Void)
{
    Int               status = GateMP_S_SUCCESS;
    NameServer_Params params;

    NameServer_Params_init(&params);
    params.maxRuntimeEntries = MAX_RUNTIME_ENTRIES;
    params.maxNameLen = MAX_NAME_LEN;

    /* Assume info entry has more fields than other entries */
    params.maxValueLen = NUM_INFO_FIELDS * sizeof(UInt32);

    GateMP_module->nameServer =
                NameServer_create(GateMP_NAMESERVER, &params);

    if (GateMP_module->nameServer == NULL) {
        status = GateMP_E_FAIL;
        LOG0("GateMP_setup: NameServer_create failed\n");
    }
    else {
        GateMP_module->isSetup = TRUE;
    }

    return status;
}

Int GateMP_attach(UInt16 procId)
{
    GateMP_Handle     deflateGate;  /* that's right, Pats fan here */
    Int               status = GateMP_S_SUCCESS;
    UInt32            nsValue[NUM_INFO_FIELDS];
    UInt32            len;
    UInt32            size;
    UInt32            alignDiff;
    UInt32            offset;
    UInt32            baseaddr;
    Int32             fdMem;
    UInt16            procList[2];
    UInt16            clId;
    Char              filename[PATH_MAX];

    /* procId already validated in API layer */
    clId = procId - MultiProc_getBaseIdOfCluster();
    if (clId >= MultiProc_getNumProcsInCluster()) {
        LOG1("GateMP_attach: procId %d not in range for local cluster\n",
             procId);
        return GateMP_E_INVALIDARG;
    }

    /* must reference count because we have multiple clients */
    if (GateMP_module->refCount[clId] > 0) {
        GateMP_module->refCount[clId]++;
        goto done;
    }

    procList[0] = procId;
    procList[1] = MultiProc_INVALIDID;
    status = GateMP_openDefaultGate(&deflateGate, procList);

    if (status < 0) {
        LOG1("GateMP_attach: failed to open default gate on procId %d\n",
             procId);
        goto done;
    }

    if (status == GateMP_S_SUCCESS) {
        if (GateMP_module->attachedProcId != MultiProc_INVALIDID) {
            LOG1("GateMP_attach: can't attach to procId %d\n", procId);
            LOG1("               already attached to %d\n",
                 GateMP_module->attachedProcId);
            status = GateMP_E_ALREADYEXISTS;
            goto done;
        }

        GateMP_module->attachedProcId = procId;
        GateMP_module->defaultGate = deflateGate;

        GateMP_module->refCount[clId]++;

        /* Process global info NameServer entry */
        len = sizeof(nsValue);

        status = NameServer_get(GateMP_module->nameServer, "_GateMP_TI_info",
            &nsValue, &len, procList);

        if (status < 0) {
            LOG0("GateMP_attach: failed to find info entry\n");
            status = GateMP_E_NOTFOUND;
        }
        else {
            status = GateMP_get_sr0(filename, PATH_MAX, &baseaddr);
            if (status < 0) {
                LOG1("GateMP_attach: failed to find sr0: %s\n", strerror(status));
                status = GateMP_E_NOTFOUND;
            }

            fdMem = open (filename, O_RDWR | O_SYNC);
            if (fdMem < 0){
                LOG1("GateMP_attach: failed to open the %s!\n", filename);
                status = GateMP_E_OSFAILURE;
                goto done;
            }

            GateMP_module->numRemoteSystem = nsValue[3];
            GateMP_module->numRemoteCustom1 = nsValue[4];
            GateMP_module->numRemoteCustom2 = nsValue[5];

            /* Map InUse arrays to daemon's address space */
            size = GateMP_module->numRemoteSystem * sizeof (UInt8) +
                (nsValue[0] & (sysconf(_SC_PAGE_SIZE) - 1));
            size = PAGE_ALIGN(size, sysconf(_SC_PAGE_SIZE));
            offset = nsValue[0] & ~(sysconf(_SC_PAGE_SIZE) - 1);
            offset -= baseaddr;

            if (size > 0) {
#if defined(IPC_BUILDOS_ANDROID)
                GateMP_module->remoteSystemInUse = mmap64(NULL, size,
                    (PROT_READ|PROT_WRITE), (MAP_SHARED), fdMem,
                    (off64_t)offset);
#else
                GateMP_module->remoteSystemInUse = mmap(NULL, size,
                    (PROT_READ|PROT_WRITE), (MAP_SHARED), fdMem,
                    (off_t)offset);
#endif
                if (GateMP_module->remoteSystemInUse == MAP_FAILED) {
                     LOG1("Failed to map remoteSystemInUse=0x%p to host address" \
                          "  space!", GateMP_module->remoteSystemInUse);
                     GateMP_module->remoteSystemInUse = NULL;
                     status = GateMP_E_MEMORY;
                }
                else {
                    alignDiff = nsValue[0] - baseaddr - offset;
                    GateMP_module->remoteSystemInUse =
                        GateMP_module->remoteSystemInUse + alignDiff;
                }
            }
            else {
                LOG0("Invalid configuration for remoteSystem gate");
                status = GateMP_E_FAIL;
            }

            size = GateMP_module->numRemoteCustom1 * sizeof (UInt8) +
                (nsValue[1] & (sysconf(_SC_PAGE_SIZE) - 1));
            size = PAGE_ALIGN(size, sysconf(_SC_PAGE_SIZE));
            offset = nsValue[1] & ~(sysconf(_SC_PAGE_SIZE) - 1);
            offset -= baseaddr;

            if ((status == GateMP_S_SUCCESS) && (size > 0)) {
#if defined(IPC_BUILDOS_ANDROID)
                GateMP_module->remoteCustom1InUse = mmap64(NULL, size,
                    (PROT_READ|PROT_WRITE), (MAP_SHARED), fdMem,
                    (off64_t)offset);
#else
                GateMP_module->remoteCustom1InUse = mmap(NULL, size,
                    (PROT_READ|PROT_WRITE), (MAP_SHARED), fdMem,
                    (off_t)offset);
#endif
                if (GateMP_module->remoteCustom1InUse == MAP_FAILED) {
                    LOG1("Failed to map remoteCustom1InUse=%p to host address" \
                        " space!", GateMP_module->remoteCustom1InUse);
                    GateMP_module->remoteCustom1InUse = NULL;
                    status = GateMP_E_MEMORY;
                }
                else {
                    alignDiff = nsValue[1] - baseaddr - offset;
                    GateMP_module->remoteCustom1InUse =
                        GateMP_module->remoteCustom1InUse + alignDiff;
                }
            }

            size = GateMP_module->numRemoteCustom2 * sizeof (UInt8) +
                (nsValue[2] & (sysconf(_SC_PAGE_SIZE) - 1));
            size = PAGE_ALIGN(size, sysconf(_SC_PAGE_SIZE));
            offset = nsValue[2] & ~(sysconf(_SC_PAGE_SIZE) - 1);
            offset -= baseaddr;

            if ((status == GateMP_S_SUCCESS) && (size > 0)) {
#if defined(IPC_BUILDOS_ANDROID)
                GateMP_module->remoteCustom2InUse = mmap64(NULL, size,
                    (PROT_READ|PROT_WRITE), (MAP_SHARED), fdMem,
                    (off64_t)offset);
#else
                GateMP_module->remoteCustom2InUse = mmap(NULL, size,
                    (PROT_READ|PROT_WRITE), (MAP_SHARED), fdMem,
                    (off_t)offset);
#endif
                if (GateMP_module->remoteCustom2InUse == MAP_FAILED) {
                    LOG1("Failed to map remoteCustom2InUse=%p to host address" \
                        " space!", GateMP_module->remoteCustom2InUse);
                    GateMP_module->remoteCustom2InUse = NULL;
                    status = GateMP_E_MEMORY;
                }
                else {
                    alignDiff = nsValue[2] - baseaddr - offset;
                    GateMP_module->remoteCustom2InUse =
                        GateMP_module->remoteCustom2InUse + alignDiff;
                }
            }
        }
    }

    /* TODO: setup the proxy map */

done:

    return (status);
}

Int GateMP_detach(UInt16 procId)
{
    UInt16 clId;

    if (procId != GateMP_module->attachedProcId) {
        return GateMP_E_NOTFOUND;
    }

    /* procId already validated in API layer */
    clId = procId - MultiProc_getBaseIdOfCluster();
    if (clId >= MultiProc_getNumProcsInCluster()) {
        LOG1("GateMP_detach: procId %d not in range for local cluster\n",
             procId);
        return GateMP_E_INVALIDARG;
    }


    /* decrement reference count regardless of outcome below */
    if (--GateMP_module->refCount[clId] > 0) {
        goto done;
    }

    if (GateMP_module->remoteSystemInUse) {
        munmap((unsigned int *)GateMP_module->remoteSystemInUse,
            GateMP_module->numRemoteSystem * sizeof (UInt8));
        GateMP_module->remoteSystemInUse = NULL;
    }

    if (GateMP_module->remoteCustom1InUse) {
        munmap((unsigned int *)GateMP_module->remoteCustom1InUse,
            GateMP_module->numRemoteCustom1 * sizeof (UInt8));
        GateMP_module->remoteCustom1InUse = NULL;
    }

    if (GateMP_module->remoteCustom2InUse) {
        munmap((unsigned int *)GateMP_module->remoteCustom2InUse,
            GateMP_module->numRemoteCustom2 * sizeof (UInt8));
        GateMP_module->remoteCustom2InUse = NULL;
    }

    if (GateMP_module->defaultGate) {
        GateMP_closeDefaultGate(&GateMP_module->defaultGate);
        GateMP_module->attachedProcId = MultiProc_INVALIDID;
    }

done:

    return GateMP_S_SUCCESS;
}

Void GateMP_destroy(Void)
{
    if (GateMP_module->nameServer) {
        NameServer_delete(&GateMP_module->nameServer);
        GateMP_module->nameServer = NULL;
    }

    GateMP_module->isSetup = FALSE;

    return;
}

static Int GateMP_get_sr0(Char *name, UInt32 name_len, UInt32 *baseaddr)
{
    Char filename[PATH_MAX];
    Char format[80];
    Char uio_name[80];
    DIR *dir;
    struct dirent *de;
    struct stat st;
    FILE *fd;
    Bool found = false;
    Int ret = 0;

    if (stat(UIO_SYSFS, &st) < 0) {
        if ((errno == ENOENT) || (errno == ENOTDIR)) {
            LOG0("GateMP_get_sr0: UIO support not found\n");
            ret = errno;
            goto out;
        }
    }

    dir = opendir(UIO_SYSFS);
    if (!dir) {
        LOG1("GateMP_get_sr0: failed to open UIO sysfs %s\n", UIO_SYSFS);
        ret = errno;
        goto out;
    }

    while (!found) {
        de = readdir(dir);
        if (!de) {
            break;
        }

        if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, "..")) {
            continue;
        }

        /* Skip if this is not an UIO entry */
        snprintf(filename, sizeof(filename), "%s/%s/name", UIO_SYSFS, de->d_name);
        fd = fopen(filename, "r");
        if (fd == NULL) {
            continue;
        }

        snprintf(format, sizeof(format), "%%%ds", sizeof(uio_name)-1);
        fscanf(fd, format, uio_name);
        fclose(fd);

        /* Skip if this UIO entry is not SR0 */
        if (strncmp(uio_name, "sr0", sizeof(uio_name)-1)) {
            continue;
        }

        /* Find the base address of the SR0 UIO */
        snprintf(filename, sizeof(filename), "%s/%s/maps/map0/addr", UIO_SYSFS, de->d_name);
        fd = fopen(filename, "r");
        if (fd == NULL) {
            LOG0("Gate_sr0_filename: failed to open uio map sysfs\n");
            ret = errno;
            break;
        }

        fscanf(fd, "0x%x", baseaddr);
        fclose(fd);

        snprintf(name, name_len, "/dev/%s", de->d_name);
        found = true;
    }

    closedir(dir);

out:
    /* Fall back to /dev/mem if UIO is not supported */
    if (!found) {
        strncpy(name, "/dev/mem", name_len);
        *baseaddr = 0x0;
    }

    return ret;
}

/* Open default gate during GateMP_attach. Should only be called once */
static Int GateMP_openDefaultGate(GateMP_Handle *handlePtr, UInt16 procId[])
{
    Int             status = GateMP_S_SUCCESS;
    UInt32          len;
    UInt32          nsValue[4];
    GateMP_Object * obj = NULL;
    UInt32          arg;
    UInt32          mask;

    GateMP_RemoteSystemProxy_Params     systemParams;

    /* assert that a valid pointer has been supplied */
    if (handlePtr == NULL) {
        LOG0("GateMP_openDefaultGate: argument cannot be null\n");
        status = GateMP_E_INVALIDARG;
    }

    if (status == GateMP_S_SUCCESS) {
        len = sizeof(nsValue);

        status = NameServer_get(GateMP_module->nameServer, "_GateMP_TI_dGate",
            &nsValue, &len, procId);

        if (status < 0) {
            *handlePtr = NULL;
            status = GateMP_E_NOTFOUND;
        }
        else if (len != sizeof(nsValue)) {
            *handlePtr = NULL;
            status = GateMP_E_NOTFOUND;
            LOG0("GateMP configuration not valid for hostSupport. "
                 "Try adding hostSupport to your config if it is needed.\n");
        }
        else {
            arg = nsValue[2];
            mask = nsValue[3];
        }
    }

    if (status == GateMP_S_SUCCESS) {
        /* allocate the instance object */
        obj = (GateMP_Object *)calloc(1, sizeof (GateMP_Object));
        if (obj != NULL) {
            obj->localGate  = NULL;  /* TODO: create the local gate instance */
            obj->localProtect  = GETLOCAL(mask);
            obj->remoteProtect = GETREMOTE(mask);
            obj->nsKey         = 0;
            obj->numOpens      = 1;
            obj->objType       = Ipc_ObjType_OPENDYNAMIC;
            obj->resourceId    = arg;

            assert(obj->remoteProtect == GateMP_RemoteProtect_SYSTEM);

            /* create the proxy object */
            GateMP_RemoteSystemProxy_Params_init(&systemParams);
            systemParams.resourceId = obj->resourceId;
            systemParams.openFlag = TRUE;

            /*
             * TODO: Currently passing in localProtect instead of localGate,
             * since GateHWSpinlock owns the local gate
             */
            obj->gateHandle = (IGateProvider_Handle)
                GateMP_RemoteSystemProxy_create(obj->localProtect,
                    &systemParams);

            if (obj->gateHandle == NULL) {
                LOG0("GateMP_openDefaultGate: failed to create proxy\n");
                free(obj);
                obj = NULL;
            }
        }
        else {
            LOG0("GateMP_openDefaultGate: Memory allocation failed")
        }

        if (obj == NULL) {
            status = GateMP_E_FAIL;
        }
    }

    /* Return the "opened" GateMP instance  */
    *handlePtr = (GateMP_Handle)obj;

    return status;
}

static Int GateMP_closeDefaultGate(GateMP_Handle *handlePtr)
{
    Int status = GateMP_S_SUCCESS;
    GateMP_Object * obj = *(GateMP_Object **)handlePtr;

    if (obj->gateHandle != NULL) {
        /* Default gate is always of type System when more than 1 processor */
        GateMP_RemoteSystemProxy_delete(
            (GateMP_RemoteSystemProxy_Handle *)&obj->gateHandle);
    }

    free(*handlePtr);
    *handlePtr = NULL;

    return(status);
}

Int GateMP_getFreeResource(GateMP_RemoteProtect type)
{
    IArg   key;
    Bool   flag = FALSE;
    Int    resourceId = -1;
    UInt8* inUse = NULL;
    Int    num = 0;

    /* Remote case */
    switch (type) {
        /* TODO: currently only support System proxy */
        case GateMP_RemoteProtect_SYSTEM:
        case GateMP_RemoteProtect_CUSTOM1:
        case GateMP_RemoteProtect_CUSTOM2:
            inUse = GateMP_module->remoteSystemInUse;
            num = GateMP_module->numRemoteSystem;
            break;

        default:
            LOG0("GateMP_getFreeResource: Invalid remote protection type\n");
            break;
    }

    if (inUse != NULL) {
        assert(GateMP_module->defaultGate != NULL);
        key = GateMP_enter(GateMP_module->defaultGate);

        /*
         *  Find a free resource id. Note: zero is reserved on the
         *  system proxy for the default gate.
         */
        for (resourceId = 0; resourceId < num; resourceId++) {
            /*
             *  If not in-use, set the inUse to TRUE to prevent other
             *  creates from getting this one.
             */
            if (inUse[resourceId] == UNUSED) {
                flag = TRUE;

                /* Denote in shared memory that the resource is used */
                inUse[resourceId] = USED;
                break;
            }
        }

        GateMP_leave(GateMP_module->defaultGate, key);
    }

    if (flag == FALSE) {
        resourceId = -1;
    }

    return (resourceId);
}

Int GateMP_releaseResource(UInt id, GateMP_RemoteProtect type)
{
    Int    status = GateMP_S_SUCCESS;
    IArg   key;
    UInt8* inUse = NULL;
    Int    num = 0;

    /* Remote case */
    switch (type) {
        /* TODO: currently only support System proxy */
        case GateMP_RemoteProtect_SYSTEM:
        case GateMP_RemoteProtect_CUSTOM1:
        case GateMP_RemoteProtect_CUSTOM2:
            inUse = GateMP_module->remoteSystemInUse;
            num = GateMP_module->numRemoteSystem;
            break;

        default:
            LOG0("GateMP_releaseResource: Invalid remote protection type\n");
            status = GateMP_E_FAIL;
            break;
    }

    if ((inUse != NULL) && (id < num)) {
        assert(GateMP_module->defaultGate != NULL);
        key = GateMP_enter(GateMP_module->defaultGate);
        inUse[id] = UNUSED;
        GateMP_leave(GateMP_module->defaultGate, key);
    }
    else {
        /* Should not happen if module is properly setup */
        status = GateMP_E_FAIL;
    }

    return (status);
}

Int GateMP_getNumResources(GateMP_RemoteProtect type)
{
    Int   num = -1;

    /* Remote case */
    switch (type) {
        /* TODO: currently only support System proxy */
        case GateMP_RemoteProtect_SYSTEM:
        case GateMP_RemoteProtect_CUSTOM1:
        case GateMP_RemoteProtect_CUSTOM2:
            num = GateMP_module->numRemoteSystem;
            break;

        default:
            LOG0("GateMP_getNumResources: Invalid remote protection type\n");
            break;
    }

    return (num);
}

NameServer_Handle GateMP_getNameServer(Void)
{
    return (GateMP_module->nameServer);
}

Bool GateMP_isSetup(Void)
{
    return (GateMP_module->isSetup);
}

IArg GateMP_enter(GateMP_Handle handle)
{
    GateMP_Object * obj;
    IArg            key;

    obj = (GateMP_Object *)handle;
    key = IGateProvider_enter(obj->gateHandle);

    return(key);
}

Void GateMP_leave(GateMP_Handle handle, IArg key)
{
    GateMP_Object *obj;

    obj = (GateMP_Object *)handle;
    IGateProvider_leave(obj->gateHandle, key);
}
