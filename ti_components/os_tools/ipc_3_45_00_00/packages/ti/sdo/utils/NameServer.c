/*
 * Copyright (c) 2012-2015 Texas Instruments Incorporated - http://www.ti.com
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
 * */
/*
 *  ======== NameServer.c ========
 *  Implementation of functions specified in NameServer.xdc.
 */

 /*
 *  The dynamic name/value table looks like the following. This approach allows
 *  each instance table to have different value and different name lengths.
 *  The names block is allocated on the create. The size of that block is
 *  (maxRuntimeEntries * maxNameLen). That block is sliced and diced up and
 *  given to each table entry.
 *  The same thing is done for the values block.
 *
 *     names                    table                  values
 *   -------------           -------------          -------------
 *   |           |<-\        |   elem    |   /----->|           |
 *   |           |   \-------|   name    |  /       |           |
 *   |           |           |   value   |-/        |           |
 *   |           |           |   len     |          |           |
 *   |           |<-\        |-----------|          |           |
 *   |           |   \       |   elem    |          |           |
 *   |           |    \------|   name    |  /------>|           |
 *   |           |           |   value   |-/        |           |
 *   -------------           |   len     |          |           |
 *                           -------------          |           |
 *                                                  |           |
 *                                                  |           |
 *                                                  -------------
 *
 *  There is an optimization for small values (e.g. <= sizeof(UInt32).
 *  In this case, there is no values block allocated. Instead the value
 *  field is used directly.  This optimization occurs and is managed when
 *  obj->maxValueLen <= sizeof(UInt32).
 *
 *  The static create is a little different. The static entries point directly
 *  to a name string (and value). Since it points directly to static items,
 *  this entries cannot be removed.
 *  If maxRuntimeEntries is non-zero, a names and values block is created.
 *  Here is an example of a table with 1 static entry and 2 dynamic entries
 *
 *                           -------------
 *                           |   elem    |
 *      "myName" <-----------|   name    |----------> someValue
 *                           |   value   |
 *     names                 |   len     |              values
 *   -------------           -------------          -------------
 *   |           |<-\        |   elem    |   /----->|           |
 *   |           |   \-------|   name    |  /       |           |
 *   |           |           |   value   |-/        |           |
 *   |           |           |   len     |          |           |
 *   |           |<-\        |-----------|          |           |
 *   |           |   \       |   elem    |          |           |
 *   |           |    \------|   name    |  /------>|           |
 *   |           |           |   value   |-/        |           |
 *   -------------           |   len     |          |           |
 *                           -------------          |           |
 *                                                  |           |
 *                                                  |           |
 *                                                  -------------
 *
 *  NameServer uses a freeList and nameList to maintain the empty
 *  and filled-in entries. So when a name/value pair is added, an entry
 *  is pulled off the freeList, filled-in and placed on the nameList.
 *  The reverse happens on a remove.
 *
 *  For static adds, the entries are placed on the nameList statically.
 *
 *  For dynamic creates, the freeList is populated in postInit and there are no
 *  entries placed on the nameList (this happens when the add is called).
 */

/* below #define to eliminate strncpy depracation warning for win targets */
#define _CRT_SECURE_NO_DEPRECATE

#include <xdc/std.h>
#include <string.h>
#include <stdlib.h>

#include <xdc/runtime/Assert.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Startup.h>

#include <ti/sysbios/gates/GateSwi.h>
#include <ti/sysbios/hal/Hwi.h>

#include <ti/sdo/utils/List.h>
#include <ti/sdo/utils/INameServerRemote.h>

#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/utils/_NameServer.h>

#include "package/internal/NameServer.xdc.h"

#ifdef __ti__
    #pragma FUNC_EXT_CALLED(NameServer_Params_init);
    #pragma FUNC_EXT_CALLED(NameServer_add);
    #pragma FUNC_EXT_CALLED(NameServer_addUInt32);
    #pragma FUNC_EXT_CALLED(NameServer_create);
    #pragma FUNC_EXT_CALLED(NameServer_delete);
    #pragma FUNC_EXT_CALLED(NameServer_get);
    #pragma FUNC_EXT_CALLED(NameServer_getHandle);
    #pragma FUNC_EXT_CALLED(NameServer_getLocal);
    #pragma FUNC_EXT_CALLED(NameServer_getLocalUInt32);
    #pragma FUNC_EXT_CALLED(NameServer_getUInt32);
    #pragma FUNC_EXT_CALLED(NameServer_match);
    #pragma FUNC_EXT_CALLED(NameServer_remove);
    #pragma FUNC_EXT_CALLED(NameServer_removeEntry);
#endif

/*
 *************************************************************************
 *                       Common Header Functions
 *************************************************************************
 */

/*
 *  ======== NameServer_Params_init ========
 */
Void NameServer_Params_init(NameServer_Params *params)
{
    /* init the params to the defaults */
    params->maxRuntimeEntries = NameServer_ALLOWGROWTH;
    params->tableHeap         = NULL;
    params->checkExisting     = TRUE;
    params->maxValueLen       = 0;
    params->maxNameLen        = NameServer_Params_MAXNAMELEN;
}

/*
 *  ======== NameServer_add ========
 *  Grab a free entry and fill it up.
 */
Ptr NameServer_add(NameServer_Handle handle, String name, Ptr value,
                   UInt32 len)
{
    ti_sdo_utils_NameServer_Object *obj =
            (ti_sdo_utils_NameServer_Object *)handle;
    IArg key;
    ti_sdo_utils_NameServer_TableEntry *tableEntry;
    Error_Block eb;
    List_Handle freeList = ti_sdo_utils_NameServer_Instance_State_freeList(obj);
    List_Handle nameList = ti_sdo_utils_NameServer_Instance_State_nameList(obj);

    /* Make sure the name and value can be copied into the table */
    Assert_isTrue((len <= obj->maxValueLen),
            ti_sdo_utils_NameServer_A_invalidLen);
    Assert_isTrue((strlen(name) < obj->maxNameLen),
            ti_sdo_utils_NameServer_A_invalidLen);

    Error_init(&eb);

    /* Only check if configured to check */
    if (obj->checkExisting == TRUE ) {
        key = GateSwi_enter(NameServer_module->gate);
        if (NameServer_findLocal(obj, name) != NULL) {
            GateSwi_leave(NameServer_module->gate, key);
            Error_raise(&eb, ti_sdo_utils_NameServer_E_entryExists, name, 0);
            return (NULL);
        }
        GateSwi_leave(NameServer_module->gate, key);
    }

    /* Get a free entry */
    tableEntry = List_get(freeList);

    /* If no entry, see if numDynamic is set to allow growth or raise error */
    if (tableEntry == NULL) {
        if (obj->numDynamic == NameServer_ALLOWGROWTH) {

            tableEntry = Memory_alloc(obj->tableHeap,
                sizeof(ti_sdo_utils_NameServer_TableEntry), 0, &eb);
            if (tableEntry == NULL) {
                return (NULL);
            }

            tableEntry->name = Memory_alloc(obj->tableHeap,
                    strlen(name) + 1, 0, &eb);
            if (tableEntry->name == NULL) {
                Memory_free(obj->tableHeap, tableEntry,
                            sizeof(ti_sdo_utils_NameServer_TableEntry));
                return (NULL);
            }

            if (!(obj->maxValueLen == sizeof(UInt32))) {

                tableEntry->value = (UArg)Memory_alloc(obj->tableHeap,
                        obj->maxValueLen, 0, &eb);
                if (tableEntry->value == 0) {
                    Memory_free(obj->tableHeap, tableEntry,
                            sizeof(ti_sdo_utils_NameServer_TableEntry));
                    Memory_free(obj->tableHeap, tableEntry->name,
                            strlen(name) + 1);
                    return (NULL);
                }
            }
        }
        else {
            Error_raise(&eb, ti_sdo_utils_NameServer_E_maxReached,
                    obj->numDynamic, 0);
            return (NULL);
        }
    }

    /*
     *  Fill in the value.
     *  If the maxValueLen is sizeof(UInt32), simply copy
     *  the value into the value field.
     */
    if (obj->maxValueLen == sizeof(UInt32)) {
        tableEntry->value = *((UInt32 *)value);
        tableEntry->len = sizeof(UInt32);
    }
    else {
        memcpy((Ptr)(tableEntry->value), (Ptr)value, len);
        tableEntry->len = len;
    }

    /* Copy the name. Note the table holds the '\0' also */
    strncpy(tableEntry->name, name, strlen(name) + 1);

    /* Add to the nameList */
    List_put(nameList, (List_Elem *)tableEntry);

    return (tableEntry);
}

/*
 *  ======== NameServer_addUInt32 ========
 *  Defer to the add.
 */
Ptr NameServer_addUInt32(NameServer_Handle handle, String name, UInt32 value)
{
    return (NameServer_add(handle, name, &value, sizeof(UInt32)));
}

/*
 *  ======== NameServer_create ========
 */
NameServer_Handle NameServer_create(String name, const NameServer_Params *params)
{
    ti_sdo_utils_NameServer_Params nsParams;
    ti_sdo_utils_NameServer_Object *obj;
    Error_Block eb;
    NameServer_Handle handle = NULL;

    Error_init(&eb);

    /* check if the name is already created or not */
    handle = NameServer_getHandle(name);
    if (handle != NULL) {
        obj = (ti_sdo_utils_NameServer_Object *)handle;
        if ((obj->numDynamic == params->maxRuntimeEntries) &&
            (obj->tableHeap == params->tableHeap) &&
            (obj->checkExisting == params->checkExisting) &&
            (obj->maxValueLen == params->maxValueLen) &&
            (obj->maxNameLen == params->maxNameLen)) {
            obj->refCount++;
        }
        else {
            Error_raise(&eb, ti_sdo_utils_NameServer_E_paramMismatch, name, 0);
            handle = NULL;
        }
    }
    else {
        if (params != NULL) {
            /* init the module params struct */
            ti_sdo_utils_NameServer_Params_init(&nsParams);
            nsParams.maxRuntimeEntries = params->maxRuntimeEntries;
            nsParams.tableHeap         = params->tableHeap;
            nsParams.checkExisting     = params->checkExisting;
            nsParams.maxValueLen       = params->maxValueLen;
            nsParams.maxNameLen        = params->maxNameLen;

            /* call the module create */
            obj = ti_sdo_utils_NameServer_create(name, &nsParams, &eb);
        }
        else {
            /* passing in NULL uses the default params */
            obj = ti_sdo_utils_NameServer_create(name, NULL, &eb);
        }
    }

    return ((NameServer_Handle)obj);
}

/*
 *  ======== NameServer_delete ========
 */
Int NameServer_delete(NameServer_Handle *handlePtr)
{
    ti_sdo_utils_NameServer_Object * obj =
        (ti_sdo_utils_NameServer_Object *)*handlePtr;

    obj->refCount--;
    if (obj->refCount == 0) {
        ti_sdo_utils_NameServer_delete(
            (ti_sdo_utils_NameServer_Handle *)handlePtr);
    }

    return (NameServer_S_SUCCESS);
}

/*
 *  ======== NameServer_get ========
 *  Currently not using ISync in RemoteProxy call. This is for async support.
 */
Int NameServer_get(NameServer_Handle handle, String name, Ptr value,
                   UInt32 *len, UInt16 procId[])
{
    ti_sdo_utils_NameServer_Object *obj =
            (ti_sdo_utils_NameServer_Object *)handle;
    Int i;
    Int status = NameServer_E_FAIL;
    Error_Block eb;
    UInt16 baseId;
    UInt16 length;
    UInt16 index;
    UInt16 cluster;

    Error_init(&eb);

    /* processor address mode determines cluster baseId */
    switch (ti_sdo_utils_MultiProc_procAddrMode) {
        case ti_sdo_utils_MultiProc_ProcAddrMode_Global:
            baseId = 0;
            break;

        case ti_sdo_utils_MultiProc_ProcAddrMode_Cluster:
            baseId = MultiProc_getBaseIdOfCluster();
            break;

        default:
            Assert_isTrue(FALSE, NULL);
            break;
    }

    /*
     *  Query all the processors.
     */
    if (procId == NULL) {
        /* Query the local one first */
        status = NameServer_getLocal(handle, name, value, len);
        if (status == NameServer_E_NOTFOUND) {
            /* To eliminate code if possible */
            if (ti_sdo_utils_NameServer_singleProcessor == FALSE) {
                length = (UInt16)NameServer_module->nsRemoteHandle.length;

                for (i = 0; i < length; i++) {
                    /* skip myself, local table already searched above */
                    if ((baseId + i) == MultiProc_self()) {
                        continue;
                    }
                    if (NameServer_module->nsRemoteHandle.elem[i] != NULL) {
                        status = INameServerRemote_get(
                                NameServer_module->nsRemoteHandle.elem[i],
                                obj->name, name, value, len, NULL, &eb);
                    }
                    /* stop looking if found or encoutered fatal error */
                    if ((status >= 0) || ((status != NameServer_E_NOTFOUND)
                            && (status != NameServer_E_TIMEOUT))) {
                        break;
                    }
                }
            }
        }
    }
    else {
        /*  Search the query list. It might contain the local proc
         *  somewhere in the list.
         */
        status = NameServer_E_NOTFOUND;
        cluster = MultiProc_getNumProcsInCluster();

        for (i = 0; (procId[i] != MultiProc_INVALIDID) && (i < cluster); i++) {
            if (procId[i] == MultiProc_self()) {
                /* check local */
                status = NameServer_getLocal(handle, name, value, len);
            }
            else if (ti_sdo_utils_NameServer_singleProcessor == FALSE) {
                index = procId[i] - baseId;
                /* check remote */
                if (NameServer_module->nsRemoteHandle.elem[index] != NULL) {
                    status = INameServerRemote_get(
                            NameServer_module->nsRemoteHandle.elem[index],
                            obj->name, name, value, len, NULL, &eb);
                }
            }
            /* stop looking if found or encoutered fatal error */
            if ((status >= 0) || ((status != NameServer_E_NOTFOUND)
                    && (status != NameServer_E_TIMEOUT))) {
                break;
            }
        }
    }

    return (status);
}

/*
 *  ======== NameServer_getHandle ========
 *  Helper function to get a handle based on the instance name.
 */
NameServer_Handle NameServer_getHandle(String instanceName)
{
    ti_sdo_utils_NameServer_Object *obj;
    IArg key;
    Int i;

    /* Search static instances */
    for (i = 0; i < ti_sdo_utils_NameServer_Object_count(); i++) {
        obj = ti_sdo_utils_NameServer_Object_get(NULL, i);
        if ((obj->name != NULL) &&
            (strcmp(obj->name, instanceName) == 0)) {
            return ((NameServer_Handle)obj);
        }
    }

    /* Search dynamic instances (in a thread safe manner) */
    key = GateSwi_enter(NameServer_module->gate);

    obj = ti_sdo_utils_NameServer_Object_first();
    while (obj != NULL) {
        if ((obj->name != NULL) &&
            (strcmp(obj->name, instanceName) == 0)) {
            GateSwi_leave(NameServer_module->gate, key);
            return ((NameServer_Handle)obj);
        }
        obj = ti_sdo_utils_NameServer_Object_next(obj);
    }
    GateSwi_leave(NameServer_module->gate, key);

    return (NULL);
}

/*
 *  ======== NameServer_getLocal ========
 */
Int NameServer_getLocal(NameServer_Handle handle, String name, Ptr value,
                        UInt32 *len)
{
    ti_sdo_utils_NameServer_Object *obj =
            (ti_sdo_utils_NameServer_Object *)handle;
    IArg key;
    ti_sdo_utils_NameServer_TableEntry *tableEntry;

    key = GateSwi_enter(NameServer_module->gate);

    /* search the local table */
    tableEntry = NameServer_findLocal(obj, name);

    if (tableEntry != NULL) {
        /*
         *  Found the entry.
         *  If the table holds value (and not buffers) simply
         *  copy into value and return
         */
        if (obj->maxValueLen == sizeof(UInt32)) {
            memcpy((Ptr)value, &(tableEntry->value), sizeof(UInt32));
        }
        else {
            Assert_isTrue((tableEntry->len <= *len), ti_sdo_utils_NameServer_A_invalidLen);
            memcpy((Ptr)value, (Ptr)(tableEntry->value), tableEntry->len);
        }
        GateSwi_leave(NameServer_module->gate, key);
        *len = tableEntry->len;
        return (NameServer_S_SUCCESS);
    }

    GateSwi_leave(NameServer_module->gate, key);

    /* Name not found locally. */
    return (NameServer_E_NOTFOUND);
}

/*
 *  ======== NameServer_getLocalUInt32 ========
 *
 */
Int NameServer_getLocalUInt32(NameServer_Handle handle, String name, Ptr value)
{
    UInt32 len = sizeof(UInt32);
    Int status;

    status = NameServer_getLocal(handle, name, value, &len);

    return (status);
}

/*
 *  ======== NameServer_getUInt32 ========
 */
Int NameServer_getUInt32(NameServer_Handle handle, String name,
                         Ptr value, UInt16 remoteProcId[])
{
    UInt32 len = sizeof(UInt32);
    Int status;

    status = NameServer_get(handle, name, value, &len, remoteProcId);

    return (status);
}

/*  ======== NameServer_match ========
 *  Currently only supporting 32-bit values.
 */
Int NameServer_match(NameServer_Handle handle, String name, UInt32 *value)
{
    ti_sdo_utils_NameServer_Object *obj =
            (ti_sdo_utils_NameServer_Object *)handle;
    Int len = 0;
    Int foundLen = 0;
    IArg key;
    ti_sdo_utils_NameServer_TableEntry *tableEntry = NULL;
    List_Handle nameList = ti_sdo_utils_NameServer_Instance_State_nameList(obj);

    Assert_isTrue((sizeof(UInt32) == obj->maxValueLen),
            ti_sdo_utils_NameServer_A_invalidLen);

    key = GateSwi_enter(NameServer_module->gate);

    /* Search the entire table and find the longest match */
    while ((tableEntry = List_next(nameList, (List_Elem*)tableEntry)) != NULL) {

        len = strlen(tableEntry->name);

        /*
         *  Only check if the name in the table is going to potentially be
         *  a better match.
         */
        if (len > foundLen) {
            if (strncmp(name, tableEntry->name, len) == 0) {
                *value = (UInt32)(tableEntry->value);
                foundLen = len;
            }
        }
    }

    GateSwi_leave(NameServer_module->gate, key);

    /* The name was not found...return 0 characters matched*/
    return (foundLen);
}

/*
 *  ======== NameServer_remove ========
 *  Remove a name/value pair.
 */
Int NameServer_remove(NameServer_Handle handle, String name)
{
    ti_sdo_utils_NameServer_Object *obj =
            (ti_sdo_utils_NameServer_Object *)handle;
    UInt i;
    IArg key;
    Int status = NameServer_E_INVALIDARG;
    ti_sdo_utils_NameServer_TableEntry *tableEntry = NULL;
    List_Handle nameList = ti_sdo_utils_NameServer_Instance_State_nameList(obj);

    /* Skip over the static ones. They are always at the head of the list */
    for (i = 0; i < obj->numStatic; i++) {
        tableEntry = List_next(nameList, (List_Elem *)tableEntry);
    }

    /* Enter the gate. */
    key = GateSwi_enter(NameServer_module->gate);

    /* Loop through the list searching for the name */
    while ((tableEntry = List_next(nameList, (List_Elem*)tableEntry)) != NULL) {
        /* Remove it from the nameList and add to the freeList */
        if (strcmp(tableEntry->name, name) == 0) {
            NameServer_removeLocal(obj, tableEntry);
            status = NameServer_S_SUCCESS;
            break;
        }
    }

    /* Leave the gate */
    GateSwi_leave(NameServer_module->gate, key);

    return (status);
}

/*
 *  ======== NameServer_removeEntry ========
 */
Int NameServer_removeEntry(NameServer_Handle handle, Ptr entry)
{
    ti_sdo_utils_NameServer_Object *obj =
            (ti_sdo_utils_NameServer_Object *)handle;

    NameServer_removeLocal(obj, (ti_sdo_utils_NameServer_TableEntry *)entry);

    return (NameServer_S_SUCCESS);
}

/*
 *************************************************************************
 *                       Instance functions
 *************************************************************************
 */

/*
 *  ======== ti_sdo_utils_NameServer_Instance_init ========
 */
Int ti_sdo_utils_NameServer_Instance_init(
        ti_sdo_utils_NameServer_Object *obj, String name,
        const ti_sdo_utils_NameServer_Params *params, Error_Block *eb)
{
    List_Handle freeList = ti_sdo_utils_NameServer_Instance_State_freeList(obj);
    List_Handle nameList = ti_sdo_utils_NameServer_Instance_State_nameList(obj);

    obj->name          = name;
    obj->numStatic     = 0;
    obj->numDynamic    = params->maxRuntimeEntries;
    obj->checkExisting = params->checkExisting;
    obj->maxNameLen    = params->maxNameLen;
    obj->table         = NULL;
    obj->values        = NULL;
    obj->names         = NULL;
    obj->refCount      = 1;

    if (params->tableHeap == NULL) {
        obj->tableHeap = ti_sdo_utils_NameServer_Object_heap();
    }
    else {
        obj->tableHeap = params->tableHeap;
    }

    /* minimum value of maxValueLen is sizeof(UInt32) */
    if (params->maxValueLen < sizeof(UInt32)) {
        obj->maxValueLen = sizeof(UInt32);
    }
    else {
        obj->maxValueLen = params->maxValueLen;
    }

    /* Construct the free and name lists */
    List_construct(List_struct(freeList), NULL);
    List_construct(List_struct(nameList), NULL);

    /* Allocate the entry table. */
    if (obj->numDynamic != NameServer_ALLOWGROWTH) {
        obj->table = Memory_alloc(obj->tableHeap,
            sizeof(ti_sdo_utils_NameServer_TableEntry) * obj->numDynamic, 0, eb);

        if (obj->table == NULL) {
            return (3);
        }

        /*
         * Allocate one big buffer that will be used for a copy of the values.
         * Allocate not done when size == UInt32 because we copy the value
         * to obj->values directly and do not need the extra space.
         */
        if (!(obj->maxValueLen == sizeof(UInt32))) {
            obj->values = Memory_alloc(obj->tableHeap,
                          obj->maxValueLen * obj->numDynamic, 0, eb);

            if (obj->values == NULL) {
                return (2);
            }
        }

        /* Allocate one big buffer that will be used for a copy of the names */
        obj->names = Memory_alloc(obj->tableHeap,
                         params->maxNameLen * obj->numDynamic, 0, eb);
        if (obj->names == NULL) {
            return (1);
        }

        /* Finish the rest of the object init */
        NameServer_postInit(obj);
    }

    return(0);
}

/*
 *  ======== ti_sdo_utils_NameServer_Instance_finalize ========
 */
Void ti_sdo_utils_NameServer_Instance_finalize(
        ti_sdo_utils_NameServer_Object *obj, Int status)
{
    List_Handle freeList = ti_sdo_utils_NameServer_Instance_State_freeList(obj);
    List_Handle nameList = ti_sdo_utils_NameServer_Instance_State_nameList(obj);
    ti_sdo_utils_NameServer_TableEntry *tableEntry;
    ti_sdo_utils_NameServer_TableEntry *tableEntryNext;

    if (obj->numDynamic != NameServer_ALLOWGROWTH) {
        if (obj->names != NULL) {
            Memory_free(obj->tableHeap, obj->names,
                        obj->maxNameLen * obj->numDynamic);
        }

        if (obj->values != NULL && !(obj->maxValueLen == sizeof(UInt32))) {
            Memory_free(obj->tableHeap, obj->values,
                        obj->maxValueLen * obj->numDynamic);
        }

        if (obj->table != NULL) {
            Memory_free(obj->tableHeap, obj->table,
                        sizeof(ti_sdo_utils_NameServer_TableEntry) * obj->numDynamic);
        }
    }
    else {
        tableEntryNext = List_next(nameList, NULL);
        while (tableEntryNext != NULL) {
            tableEntry = tableEntryNext;
            tableEntryNext = List_next(nameList, (List_Elem*)tableEntryNext);

            /* Free the value if not UInt32 */
            if (!(obj->maxValueLen == sizeof(UInt32))) {
                Memory_free(obj->tableHeap, (Ptr)(tableEntry->value),
                            obj->maxValueLen);
            }

            /* Free the name */
            Memory_free(obj->tableHeap, tableEntry->name,
                        strlen(tableEntry->name) + 1);

            /* Free the entry */
            Memory_free(obj->tableHeap, tableEntry,
                        sizeof(ti_sdo_utils_NameServer_TableEntry));
        }
    }

    List_destruct(List_struct(freeList));
    List_destruct(List_struct(nameList));
}





/*
 *  ======== ti_sdo_utils_NameServer_removeLocal ========
 */
Void ti_sdo_utils_NameServer_removeLocal(ti_sdo_utils_NameServer_Object *obj,
                             ti_sdo_utils_NameServer_TableEntry *entry)
{
    IArg key;
    List_Handle freeList = ti_sdo_utils_NameServer_Instance_State_freeList(obj);
    List_Handle nameList = ti_sdo_utils_NameServer_Instance_State_nameList(obj);

    /* Remove it from the nameList and add to the freeList or free it */
    if (obj->numDynamic == NameServer_ALLOWGROWTH) {

        key = GateSwi_enter(NameServer_module->gate);
        List_remove(nameList, (List_Elem *)entry);
        GateSwi_leave(NameServer_module->gate, key);

        if (!(obj->maxValueLen == sizeof(UInt32))) {
            Memory_free(obj->tableHeap, (Ptr)entry->value,
                        obj->maxValueLen);
        }

        Memory_free(obj->tableHeap, entry->name,
                    strlen(entry->name) + 1);

        Memory_free(obj->tableHeap, entry,
                    sizeof(ti_sdo_utils_NameServer_TableEntry));
    }
    else {
        key = GateSwi_enter(NameServer_module->gate);
        List_remove(nameList, (List_Elem *)entry);
        GateSwi_leave(NameServer_module->gate, key);

        List_put(freeList, (List_Elem *)entry);
    }
}

/*
 *  ======== ti_sdo_utils_NameServer_getKey ========
 */
Ptr ti_sdo_utils_NameServer_getKey(ti_sdo_utils_NameServer_Object *obj,
        UInt32 val)
{
    IArg  key;
    ti_sdo_utils_NameServer_TableEntry *tableEntry = NULL;
    List_Handle nameList = ti_sdo_utils_NameServer_Instance_State_nameList(obj);

    /* Need to assume the value length is sizeof(UInt32) */
    Assert_isTrue(obj->maxValueLen == sizeof(UInt32), NULL);

    key = GateSwi_enter(NameServer_module->gate);

    while ((tableEntry = List_next(nameList, (List_Elem *)tableEntry))
        != NULL) {
        /* Do the comparison */
        if (tableEntry->value == val) {
            break;
        }
    }

    GateSwi_leave(NameServer_module->gate, key);

    return (tableEntry);
}


/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*
 *  ======== ti_sdo_utils_NameServer_Module_startup ========
 */
Int ti_sdo_utils_NameServer_Module_startup( Int phase )
{
    Int i;
    ti_sdo_utils_NameServer_Object *obj;

    /* Finish setting up the freeList */
    for (i = 0; i < ti_sdo_utils_NameServer_Object_count(); i++) {
        obj = ti_sdo_utils_NameServer_Object_get(NULL, i);
        if ((obj->numDynamic != 0) &&
            (obj->numDynamic != NameServer_ALLOWGROWTH)) {
            NameServer_postInit(obj);
        }
    }

    return (Startup_DONE);
}


/*
 *  ======== ti_sdo_utils_NameServer_isRegistered ========
 */
Bool ti_sdo_utils_NameServer_isRegistered(UInt16 procId)
{
    Bool registered;
    UInt16 index;

    Assert_isTrue(procId < ti_sdo_utils_MultiProc_numProcessors,
            ti_sdo_utils_NameServer_A_invArgument);

    switch (ti_sdo_utils_MultiProc_procAddrMode) {
        case ti_sdo_utils_MultiProc_ProcAddrMode_Global:
            index = procId;
            break;

        case ti_sdo_utils_MultiProc_ProcAddrMode_Cluster:
            index = procId - MultiProc_getBaseIdOfCluster();
            break;

        default:
            Assert_isTrue(FALSE, NULL);
            break;
    }

    Assert_isTrue(index < NameServer_module->nsRemoteHandle.length,
            ti_sdo_utils_NameServer_A_invArgument);

    registered = (NameServer_module->nsRemoteHandle.elem[index] != NULL);

    return (registered);
}

/*
 *  ======== ti_sdo_utils_NameServer_registerRemoteDriver ========
 */
Int ti_sdo_utils_NameServer_registerRemoteDriver(INameServerRemote_Handle
        nsrHandle, UInt16 procId)
{
    Int status;
    UInt16 index;
    UInt key;

    Assert_isTrue(procId < ti_sdo_utils_MultiProc_numProcessors,
            ti_sdo_utils_NameServer_A_invArgument);

    switch (ti_sdo_utils_MultiProc_procAddrMode) {
        case ti_sdo_utils_MultiProc_ProcAddrMode_Global:
            index = procId;
            break;

        case ti_sdo_utils_MultiProc_ProcAddrMode_Cluster:
            index = procId - MultiProc_getBaseIdOfCluster();
            break;

        default:
            Assert_isTrue(FALSE, NULL);
            break;
    }

    Assert_isTrue(index < NameServer_module->nsRemoteHandle.length,
            ti_sdo_utils_NameServer_A_invArgument);

    key = Hwi_disable();

    if (NameServer_module->nsRemoteHandle.elem[index] != NULL) {
        status = NameServer_E_FAIL;
    }
    else {
        NameServer_module->nsRemoteHandle.elem[index] = nsrHandle;
        status = NameServer_S_SUCCESS;
    }

    Hwi_restore(key);

    return (status);
}

/*
 *  ======== ti_sdo_utils_NameServer_unregisterRemoteDriver ========
 */
Void ti_sdo_utils_NameServer_unregisterRemoteDriver(UInt16 procId)
{
    UInt16 index;
    UInt key;

    Assert_isTrue(procId < ti_sdo_utils_MultiProc_numProcessors,
            ti_sdo_utils_NameServer_A_invArgument);

    switch (ti_sdo_utils_MultiProc_procAddrMode) {
        case ti_sdo_utils_MultiProc_ProcAddrMode_Global:
            index = procId;
            break;

        case ti_sdo_utils_MultiProc_ProcAddrMode_Cluster:
            index = procId - MultiProc_getBaseIdOfCluster();
            break;

        default:
            Assert_isTrue(FALSE, NULL);
            break;
    }

    Assert_isTrue(index < NameServer_module->nsRemoteHandle.length,
            ti_sdo_utils_NameServer_A_invArgument);

    key = Hwi_disable();

    NameServer_module->nsRemoteHandle.elem[index] = NULL;

    Hwi_restore(key);
}

/*
 *************************************************************************
 *                       Internal functions
 *************************************************************************
 */

/*
 *  ======== ti_sdo_utils_NameServer_findLocal ========
 *  Searches the local instance table.
 */
ti_sdo_utils_NameServer_TableEntry *NameServer_findLocal(
        ti_sdo_utils_NameServer_Object *obj, String name)
{
    IArg  key;
    ti_sdo_utils_NameServer_TableEntry *tableEntry = NULL;

    List_Handle nameList = ti_sdo_utils_NameServer_Instance_State_nameList(obj);

    /* Search the table in a thread safe manner */
    key = GateSwi_enter(NameServer_module->gate);

    while ((tableEntry = List_next(nameList, (List_Elem *)tableEntry))
        != NULL) {
        /* Do the comparison */
        if (strcmp(tableEntry->name, name) == 0) {
            break;
        }
    }

    GateSwi_leave(NameServer_module->gate, key);

    return (tableEntry);
}

/*
 *  ======== ti_sdo_utils_NameServer_postInit ========
 *  Function to be called during
 *  1. module startup to complete the initialization of all static instances
 *  2. instance_init to complete the initialization of a dynamic instance
 *
 *  The empty entries are added into the freeList. There can be non-empty
 *  entries on statically created instances. The instance$static$init already
 *  put those entries onto the nameList.
 */
Int ti_sdo_utils_NameServer_postInit(ti_sdo_utils_NameServer_Object *obj)
{
    UInt i;
    List_Handle freeList = ti_sdo_utils_NameServer_Instance_State_freeList(obj);
    ti_sdo_utils_NameServer_TableEntry *tableEntry;
    String name;

    name = obj->names;
    for (i = 0; i < obj->numDynamic; i++) {
        tableEntry = &(obj->table[i + obj->numStatic]);

        /* Carve out some room for the dynamically added names */
        tableEntry->name = name;
        name += obj->maxNameLen;

        /* Carve out some room for the dynamically added values */
        if (obj->maxValueLen > sizeof(UInt32)) {
            tableEntry->value = (UArg)((UInt32)obj->values +
                    (i * obj->maxValueLen));
            tableEntry->len   = obj->maxValueLen;
        }

        /* Put the entry onto the freeList */
        List_put(freeList, (List_Elem *)(tableEntry));
    }

    return (0);
}
