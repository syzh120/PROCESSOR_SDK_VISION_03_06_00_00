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
 */
/*
 *  ======== ListMP.c ========
 *  Implementation of functions specified in ListMP.xdc.
 */

#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Startup.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/IHeap.h>

#include <ti/sysbios/hal/Cache.h>

#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/utils/_NameServer.h>
#include <ti/sdo/ipc/_GateMP.h>
#include <ti/sdo/ipc/_ListMP.h>
#include <ti/sdo/ipc/_SharedRegion.h>

#include "package/internal/ListMP.xdc.h"


#ifdef __ti__
    #pragma FUNC_EXT_CALLED(ListMP_Params_init);
    #pragma FUNC_EXT_CALLED(ListMP_create);
    #pragma FUNC_EXT_CALLED(ListMP_close);
    #pragma FUNC_EXT_CALLED(ListMP_delete);
    #pragma FUNC_EXT_CALLED(ListMP_open);
    #pragma FUNC_EXT_CALLED(ListMP_openByAddr);
    #pragma FUNC_EXT_CALLED(ListMP_sharedMemReq);
    #pragma FUNC_EXT_CALLED(ListMP_empty);
    #pragma FUNC_EXT_CALLED(ListMP_getGate);
    #pragma FUNC_EXT_CALLED(ListMP_getHead);
    #pragma FUNC_EXT_CALLED(ListMP_getTail);
    #pragma FUNC_EXT_CALLED(ListMP_insert);
    #pragma FUNC_EXT_CALLED(ListMP_next);
    #pragma FUNC_EXT_CALLED(ListMP_prev);
    #pragma FUNC_EXT_CALLED(ListMP_putHead);
    #pragma FUNC_EXT_CALLED(ListMP_putTail);
    #pragma FUNC_EXT_CALLED(ListMP_remove);
#endif

/*
 *************************************************************************
 *                       Common Header Functions
 *************************************************************************
 */

/*
 *  ======== ListMP_Params_init ========
 */
Void ListMP_Params_init(ListMP_Params *params)
{
    /* init the params to the defaults */
    params->gate       = NULL;
    params->sharedAddr = 0;
    params->name       = NULL;
    params->regionId   = 0;
}

/*
 *  ======== ListMP_create ========
 */
ListMP_Handle ListMP_create(const ListMP_Params *params)
{
    ti_sdo_ipc_ListMP_Params mpParams;
    ti_sdo_ipc_ListMP_Object *obj;
    Error_Block eb;

    Error_init(&eb);

    if (params != NULL) {
        /* init the module params struct */
        ti_sdo_ipc_ListMP_Params_init(&mpParams);
        mpParams.gate       = (ti_sdo_ipc_GateMP_Handle)params->gate;
        mpParams.openFlag   = FALSE;
        mpParams.sharedAddr = params->sharedAddr;
        mpParams.name       = params->name;
        mpParams.regionId   = params->regionId;

        /* call the module create */
        obj = ti_sdo_ipc_ListMP_create(&mpParams, &eb);
    }
    else {
        obj = ti_sdo_ipc_ListMP_create(NULL, &eb);
    }

    return ((ListMP_Handle)obj);
}

/*
 *  ======== ListMP_close ========
 */
Int ListMP_close(ListMP_Handle *handlePtr)
{
    ListMP_delete(handlePtr);

    return (ListMP_S_SUCCESS);
}

/*
 *  ======== ListMP_delete ========
 */
Int ListMP_delete(ListMP_Handle *handlePtr)
{
    ti_sdo_ipc_ListMP_delete((ti_sdo_ipc_ListMP_Handle *)handlePtr);

    return (ListMP_S_SUCCESS);
}

/*
 *  ======== ListMP_open ========
 */
Int ListMP_open(String name, ListMP_Handle *handlePtr)
{
    SharedRegion_SRPtr sharedShmBase;
    Ptr sharedAddr;
    Int status;

    /* Assert that a pointer has been supplied */
    Assert_isTrue(handlePtr != NULL, ti_sdo_ipc_Ipc_A_nullArgument);

    /* Assert that we have enough information to open the gate */
    Assert_isTrue(name != NULL, ti_sdo_ipc_Ipc_A_invParam);

    /* Search NameServer */
    status = NameServer_getUInt32((NameServer_Handle)ListMP_module->nameServer,
            name, &sharedShmBase, MultiProc_getClusterProcList());

    if (status < 0) {
        /* Name was not found */
        *handlePtr = NULL;
        return (ListMP_E_NOTFOUND);
    }

    sharedAddr = SharedRegion_getPtr(sharedShmBase);

    status = ListMP_openByAddr(sharedAddr, handlePtr);

    return (status);
}

/*
 *  ======== ListMP_openByAddr ========
 */
Int ListMP_openByAddr(Ptr sharedAddr, ListMP_Handle *handlePtr)
{
    ti_sdo_ipc_ListMP_Params params;
    ti_sdo_ipc_ListMP_Attrs *attrs;
    Error_Block eb;
    Int status;
    UInt16 id;

    Error_init(&eb);

    ti_sdo_ipc_ListMP_Params_init(&params);

    /* Tell Instance_init() that we're opening */
    params.openFlag = TRUE;

    attrs = (ti_sdo_ipc_ListMP_Attrs *)sharedAddr;
    params.sharedAddr = sharedAddr;
    id = SharedRegion_getId(sharedAddr);

    if (SharedRegion_isCacheEnabled(id)) {
        Cache_inv(attrs, sizeof(ti_sdo_ipc_ListMP_Attrs), Cache_Type_ALL, TRUE);
    }

    if (attrs->status != ti_sdo_ipc_ListMP_CREATED) {
        *handlePtr = NULL;
        status = ListMP_E_NOTFOUND;
    }
    else {
        /* Create the object */
        *handlePtr = (ListMP_Handle)ti_sdo_ipc_ListMP_create(&params, &eb);
        if (*handlePtr == NULL) {
            status = ListMP_E_FAIL;
        }
        else {
            status = ListMP_S_SUCCESS;
        }
    }

    if (SharedRegion_isCacheEnabled(id)) {
        Cache_inv(attrs, sizeof(ti_sdo_ipc_ListMP_Attrs), Cache_Type_ALL, TRUE);
    }

    return (status);
}

/*
 *  ======== ListMP_sharedMemReq ========
 */
SizeT ListMP_sharedMemReq(const ListMP_Params *params)
{
    SizeT  memReq, minAlign;
    UInt16 regionId;

    if (params->sharedAddr == NULL) {
        regionId = params->regionId;
    }
    else {
        regionId = SharedRegion_getId(params->sharedAddr);
    }

    /* Assert that the region is valid */
    Assert_isTrue(regionId != SharedRegion_INVALIDREGIONID,
                  ti_sdo_ipc_Ipc_A_addrNotInSharedRegion);

    minAlign = Memory_getMaxDefaultTypeAlign();
    if (SharedRegion_getCacheLineSize(regionId) > minAlign) {
        minAlign = SharedRegion_getCacheLineSize(regionId);
    }

    memReq = _Ipc_roundup(sizeof(ti_sdo_ipc_ListMP_Attrs), minAlign);

    return (memReq);
}

/*
 *  ======== ListMP_empty ========
 */
Bool ListMP_empty(ListMP_Handle handle)
{
    ti_sdo_ipc_ListMP_Object *obj = (ti_sdo_ipc_ListMP_Object *)handle;
    ti_sdo_ipc_ListMP_Attrs *attrs = obj->attrs;
    Bool flag = FALSE;
    IArg key;
    SharedRegion_SRPtr sharedHead;

    /* prevent another thread or processor from modifying the ListMP */
    key = GateMP_enter((GateMP_Handle)obj->gate);

#ifdef xdc_target__isaCompatible_v7A
    /* ARM speculative execution might have pulled attrs into cache */
    if (obj->cacheEnabled) {
        Cache_inv(attrs, sizeof(ti_sdo_ipc_ListMP_Attrs), Cache_Type_ALL, TRUE);
    }
#endif

    if (ti_sdo_ipc_SharedRegion_translate == FALSE) {
        /* get the SRPtr for the head */
        sharedHead = (SharedRegion_SRPtr)&(attrs->head);
    }
    else {
        /* get the SRPtr for the head */
        sharedHead = SharedRegion_getSRPtr(&(attrs->head), obj->regionId);
    }

    /* if 'next' is ourself, then the ListMP must be empty */
    if (attrs->head.next == sharedHead) {
        flag = TRUE;
    }

    if (obj->cacheEnabled) {
        /* invalidate the head to make sure we are not getting stale data */
        Cache_inv(&(attrs->head), sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }

    /* leave the gate */
    GateMP_leave((GateMP_Handle)obj->gate, key);

    return (flag);
}

/*
 *  ======== ListMP_getGate ========
 */
GateMP_Handle ListMP_getGate(ListMP_Handle handle)
{
    ti_sdo_ipc_ListMP_Object *obj = (ti_sdo_ipc_ListMP_Object *)handle;

    return ((GateMP_Handle)obj->gate);
}

/*
 *  ======== ListMP_getHead ========
 */
Ptr ListMP_getHead(ListMP_Handle handle)
{
    ti_sdo_ipc_ListMP_Object *obj = (ti_sdo_ipc_ListMP_Object *)handle;
    ti_sdo_ipc_ListMP_Attrs *attrs = obj->attrs;
    ListMP_Elem *elem;
    ListMP_Elem *localHeadNext;
    ListMP_Elem *localNext;
    Bool localNextIsCached;
    UInt key;

    /* prevent another thread or processor from modifying the ListMP */
    key = GateMP_enter((GateMP_Handle)obj->gate);

#ifdef xdc_target__isaCompatible_v7A
    /* ARM speculative execution might have pulled attrs into cache */
    if (obj->cacheEnabled) {
        Cache_inv(attrs, sizeof(ti_sdo_ipc_ListMP_Attrs), Cache_Type_ALL, TRUE);
    }
#endif

    if (ti_sdo_ipc_SharedRegion_translate == FALSE) {
        localHeadNext = (ListMP_Elem *)attrs->head.next;
    }
    else {
        localHeadNext = SharedRegion_getPtr(attrs->head.next);
    }

    /* Assert that pointer is not NULL */
    Assert_isTrue(localHeadNext != NULL, ti_sdo_ipc_Ipc_A_nullPointer);

    /* See if the ListMP was empty */
    if (localHeadNext == (ListMP_Elem *)(&(attrs->head))) {
        /* Empty, return NULL */
        elem = NULL;
    }
    else {
        if (SharedRegion_isCacheEnabled(SharedRegion_getId(localHeadNext))) {
            /* invalidate elem */
            Cache_inv(localHeadNext, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
        }

        if (ti_sdo_ipc_SharedRegion_translate == FALSE) {
            localNext = (ListMP_Elem *)localHeadNext->next;
        }
        else {
            localNext = SharedRegion_getPtr(localHeadNext->next);
        }

        /* Assert that pointer is not NULL */
        Assert_isTrue(localNext != NULL, ti_sdo_ipc_Ipc_A_nullPointer);

        /* Elem to return */
        elem = localHeadNext;
        localNextIsCached = SharedRegion_isCacheEnabled(
                SharedRegion_getId(localNext));
        if (localNextIsCached) {
            Cache_inv(localNext, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
        }

        /* Fix the head of the list next pointer */
        attrs->head.next = elem->next;

        /* Fix the prev pointer of the new first elem on the list */
        localNext->prev = localHeadNext->prev;
        if (localNextIsCached) {
            Cache_wbInv(localNext, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
        }
    }

    if (obj->cacheEnabled) {
        Cache_wbInv(&(attrs->head), sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }

    GateMP_leave((GateMP_Handle)obj->gate, key);

    return (elem);
}

/*
 *  ======== ListMP_getTail ========
 */
Ptr ListMP_getTail(ListMP_Handle handle)
{
    ti_sdo_ipc_ListMP_Object *obj = (ti_sdo_ipc_ListMP_Object *)handle;
    ti_sdo_ipc_ListMP_Attrs *attrs = obj->attrs;
    ListMP_Elem *elem;
    ListMP_Elem *localHeadPrev;
    ListMP_Elem *localPrev;
    Bool localPrevIsCached;
    UInt key;

    /* prevent another thread or processor from modifying the ListMP */
    key = GateMP_enter((GateMP_Handle)obj->gate);

#ifdef xdc_target__isaCompatible_v7A
    /* ARM speculative execution might have pulled attrs into cache */
    if (obj->cacheEnabled) {
        Cache_inv(attrs, sizeof(ti_sdo_ipc_ListMP_Attrs), Cache_Type_ALL, TRUE);
    }
#endif

    if (ti_sdo_ipc_SharedRegion_translate == FALSE) {
        localHeadPrev = (ListMP_Elem *)attrs->head.prev;
    }
    else {
        localHeadPrev = SharedRegion_getPtr(attrs->head.prev);
    }

    /* Assert that pointer is not NULL */
    Assert_isTrue(localHeadPrev != NULL, ti_sdo_ipc_Ipc_A_nullPointer);

    /* See if the ListMP was empty */
    if (localHeadPrev == (ListMP_Elem *)(&(attrs->head))) {
        /* Empty, return NULL */
        elem = NULL;
    }
    else {
        if (SharedRegion_isCacheEnabled(SharedRegion_getId(localHeadPrev))) {
            /* invalidate elem */
            Cache_inv(localHeadPrev, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
        }

        if (ti_sdo_ipc_SharedRegion_translate == FALSE) {
            localPrev = (ListMP_Elem *)localHeadPrev->prev;
        }
        else {
            localPrev = SharedRegion_getPtr(localHeadPrev->prev);
        }

        /* Assert that pointer is not NULL */
        Assert_isTrue(localPrev != NULL, ti_sdo_ipc_Ipc_A_nullPointer);

        /* Elem to return */
        elem = localHeadPrev;
        localPrevIsCached = SharedRegion_isCacheEnabled(
                SharedRegion_getId(localPrev));
        if (localPrevIsCached) {
            Cache_inv(localPrev, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
        }

        /* Fix the head of the list prev pointer */
        attrs->head.prev = elem->prev;

        /* Fix the next pointer of the new last elem on the list */
        localPrev->next = localHeadPrev->next;
        if (localPrevIsCached) {
            Cache_wbInv(localPrev, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
        }
    }

    if (obj->cacheEnabled) {
        Cache_wbInv(&(attrs->head), sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }

    GateMP_leave((GateMP_Handle)obj->gate, key);

    return (elem);
}

/*
 *  ======== ListMP_insert ========
 */
Int ListMP_insert(ListMP_Handle handle, ListMP_Elem *newElem,
                  ListMP_Elem *curElem)
{
    ti_sdo_ipc_ListMP_Object *obj = (ti_sdo_ipc_ListMP_Object *)handle;
    UInt key;
    Int  id;
    ListMP_Elem *localPrevElem;
    SharedRegion_SRPtr sharedNewElem;
    SharedRegion_SRPtr sharedCurElem;
    Bool curElemIsCached, localPrevElemIsCached;

    /* prevent another thread or processor from modifying the ListMP */
    key = GateMP_enter((GateMP_Handle)obj->gate);

    if (ti_sdo_ipc_SharedRegion_translate == FALSE) {
        sharedNewElem = (SharedRegion_SRPtr)newElem;
        sharedCurElem = (SharedRegion_SRPtr)curElem;
    }
    else {
        /* get SRPtr for newElem */
        id = SharedRegion_getId(newElem);
        sharedNewElem = SharedRegion_getSRPtr(newElem, id);

        /* get SRPtr for curElem */
        id = SharedRegion_getId(curElem);
        sharedCurElem = SharedRegion_getSRPtr(curElem, id);
    }

    curElemIsCached = SharedRegion_isCacheEnabled(SharedRegion_getId(curElem));
    if (curElemIsCached) {
        Cache_inv(curElem, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }

    /* get Ptr for curElem->prev */
    localPrevElem = SharedRegion_getPtr(curElem->prev);

    localPrevElemIsCached = SharedRegion_isCacheEnabled(
            SharedRegion_getId(localPrevElem));
    if (localPrevElemIsCached) {
        Cache_inv(localPrevElem, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }

    newElem->next       = sharedCurElem;
    newElem->prev       = curElem->prev;
    localPrevElem->next = sharedNewElem;
    curElem->prev       = sharedNewElem;

    if (localPrevElemIsCached) {
        Cache_wbInv(localPrevElem, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }

    /*
     *  The next two Cache_wbInv needs to be done because curElem
     *  and newElem are passed in and maybe already in the cache
     */
    if (curElemIsCached) {
        /* writeback invalidate current elem structure */
        Cache_wbInv(curElem, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }

    if (SharedRegion_isCacheEnabled(SharedRegion_getId(newElem))) {
        /* writeback invalidate new elem structure  */
        Cache_wbInv(newElem, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }

    GateMP_leave((GateMP_Handle)obj->gate, key);

    return (ListMP_S_SUCCESS);
}

/*
 *  ======== ListMP_next ========
 */
Ptr ListMP_next(ListMP_Handle handle, ListMP_Elem *elem)
{
    ti_sdo_ipc_ListMP_Object *obj = (ti_sdo_ipc_ListMP_Object *)handle;
    ListMP_Elem *retElem;  /* returned elem */
    Bool elemIsCached;

    /* elem == NULL -> start at the head */
    if (elem == NULL) {
        /* Keep track of whether an extra Cache_inv is needed */
        elemIsCached = obj->cacheEnabled;
        elem = (ListMP_Elem *)&(obj->attrs->head);
    }
    else {
        elemIsCached = SharedRegion_isCacheEnabled(SharedRegion_getId(elem));
    }

    if (elemIsCached) {
        Cache_inv(elem, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }

    retElem = SharedRegion_getPtr(elem->next);

    if (retElem == (ListMP_Elem *)(&obj->attrs->head)) {
        retElem = NULL;
    }

    if (elemIsCached) {
        /* invalidate because elem pulled into cache */
        Cache_inv(elem, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }

    return (retElem);
}

/*
 *  ======== ListMP_prev ========
 */
Ptr ListMP_prev(ListMP_Handle handle, ListMP_Elem *elem)
{
    ti_sdo_ipc_ListMP_Object *obj = (ti_sdo_ipc_ListMP_Object *)handle;
    ListMP_Elem *retElem;  /* returned elem */
    Bool elemIsCached;

    /* elem == NULL -> start at the head */
    if (elem == NULL) {
        elemIsCached = obj->cacheEnabled;
        elem = (ListMP_Elem *)&(obj->attrs->head);
    }
    else {
        elemIsCached = SharedRegion_isCacheEnabled(SharedRegion_getId(elem));
    }

    if (elemIsCached) {
        Cache_inv(elem, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }

    retElem = SharedRegion_getPtr(elem->prev);

    if (retElem == (ListMP_Elem *)(&(obj->attrs->head))) {
        retElem = NULL;
    }

    if (elemIsCached) {
        /* invalidate because elem pulled into cache */
        Cache_inv(elem, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }

    return (retElem);
}

/*
 *  ======== ListMP_putHead ========
 */
Int ListMP_putHead(ListMP_Handle handle, ListMP_Elem *elem)
{
    ti_sdo_ipc_ListMP_Object *obj = (ti_sdo_ipc_ListMP_Object *)handle;
    ti_sdo_ipc_ListMP_Attrs *attrs = obj->attrs;
    UInt key;
    UInt16 id;
    ListMP_Elem *localNextElem;
    SharedRegion_SRPtr sharedElem;
    SharedRegion_SRPtr sharedHead;
    Bool localNextElemIsCached;

    /* prevent another thread or processor from modifying the ListMP */
    key = GateMP_enter((GateMP_Handle)obj->gate);

#ifdef xdc_target__isaCompatible_v7A
    /* ARM speculative execution might have pulled attrs into cache */
    if (obj->cacheEnabled) {
        Cache_inv(attrs, sizeof(ti_sdo_ipc_ListMP_Attrs), Cache_Type_ALL, TRUE);
    }
#endif

    id = SharedRegion_getId(elem);
    if (ti_sdo_ipc_SharedRegion_translate == FALSE) {
        sharedElem = (SharedRegion_SRPtr)elem;
        sharedHead = (SharedRegion_SRPtr)&(attrs->head);
        localNextElem = (ListMP_Elem *)attrs->head.next;
    }
    else {
        sharedElem = SharedRegion_getSRPtr(elem, id);
        sharedHead = SharedRegion_getSRPtr(&(attrs->head), obj->regionId);
        localNextElem = SharedRegion_getPtr(attrs->head.next);
    }

    /* Assert that pointer is not NULL */
    Assert_isTrue(localNextElem != NULL, ti_sdo_ipc_Ipc_A_nullPointer);

    localNextElemIsCached = SharedRegion_isCacheEnabled(
        SharedRegion_getId(localNextElem));
    if (localNextElemIsCached) {
        Cache_inv(localNextElem, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }

    /* add the new elem into the list */
    elem->next = attrs->head.next;
    elem->prev = sharedHead;
    localNextElem->prev = sharedElem;
    attrs->head.next = sharedElem;

    if (localNextElemIsCached) {
        /* Write-back because localNextElem->prev changed */
        Cache_wbInv(localNextElem, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }
    if (obj->cacheEnabled) {
        /* Write-back because attrs->head.next changed */
        Cache_wbInv(&(attrs->head), sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }
    if (SharedRegion_isCacheEnabled(id)) {
        /* Write-back because elem->next & elem->prev changed */
        Cache_wbInv(elem, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }

    GateMP_leave((GateMP_Handle)obj->gate, key);

    return (ListMP_S_SUCCESS);
}

/*
 *  ======== ListMP_putTail ========
 */
Int ListMP_putTail(ListMP_Handle handle, ListMP_Elem *elem)
{
    ti_sdo_ipc_ListMP_Object *obj = (ti_sdo_ipc_ListMP_Object *)handle;
    ti_sdo_ipc_ListMP_Attrs *attrs = obj->attrs;
    UInt key;
    UInt16  id;
    ListMP_Elem *localPrevElem;
    SharedRegion_SRPtr sharedElem;
    SharedRegion_SRPtr sharedHead;
    Bool localPrevElemIsCached;

    /* prevent another thread or processor from modifying the ListMP */
    key = GateMP_enter((GateMP_Handle)obj->gate);

#ifdef xdc_target__isaCompatible_v7A
    /* ARM speculative execution might have pulled attrs into cache */
    if (obj->cacheEnabled) {
        Cache_inv(attrs, sizeof(ti_sdo_ipc_ListMP_Attrs), Cache_Type_ALL, TRUE);
    }
#endif

    id = SharedRegion_getId(elem);
    if (ti_sdo_ipc_SharedRegion_translate == FALSE) {
        sharedElem = (SharedRegion_SRPtr)elem;
        sharedHead = (SharedRegion_SRPtr)&(attrs->head);
        localPrevElem = (ListMP_Elem *)attrs->head.prev;
    }
    else {
        sharedElem = SharedRegion_getSRPtr(elem, id);
        sharedHead = SharedRegion_getSRPtr(&(attrs->head), obj->regionId);
        localPrevElem = SharedRegion_getPtr(attrs->head.prev);
    }

    /* Assert that pointer is not NULL */
    Assert_isTrue(localPrevElem != NULL, ti_sdo_ipc_Ipc_A_nullPointer);

    localPrevElemIsCached = SharedRegion_isCacheEnabled(
        SharedRegion_getId(localPrevElem));
    if (localPrevElemIsCached) {
        Cache_inv(localPrevElem, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }

    /* add the new elem into the list */
    elem->next = sharedHead;
    elem->prev = attrs->head.prev;
    localPrevElem->next = sharedElem;
    attrs->head.prev = sharedElem;

    if (localPrevElemIsCached) {
        /* Write-back because localPrevElem->next changed */
        Cache_wbInv(localPrevElem, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }
    if (obj->cacheEnabled) {
        /* Write-back because attrs->head.prev changed */
        Cache_wbInv(&(attrs->head), sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }
    if (SharedRegion_isCacheEnabled(id)) {
        /* Write-back because elem->next & elem->prev changed */
        Cache_wbInv(elem, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }

    GateMP_leave((GateMP_Handle)obj->gate, key);

    return (ListMP_S_SUCCESS);
}

/*
 *  ======== ListMP_remove ========
 */
Int ListMP_remove(ListMP_Handle handle, ListMP_Elem *elem)
{
    ti_sdo_ipc_ListMP_Object *obj = (ti_sdo_ipc_ListMP_Object *)handle;
    UInt key;
    ListMP_Elem *localPrevElem;
    ListMP_Elem *localNextElem;
    Bool localPrevElemIsCached, localNextElemIsCached;

    /* Prevent another thread or processor from modifying the ListMP */
    key = GateMP_enter((GateMP_Handle)obj->gate);

    if (ti_sdo_ipc_SharedRegion_translate == FALSE) {
        localPrevElem = (ListMP_Elem *)(elem->prev);
        localNextElem = (ListMP_Elem *)(elem->next);
    }
    else {
        localPrevElem = SharedRegion_getPtr(elem->prev);
        localNextElem = SharedRegion_getPtr(elem->next);
    }

    localPrevElemIsCached = SharedRegion_isCacheEnabled(
            SharedRegion_getId(localPrevElem));
    localNextElemIsCached = SharedRegion_isCacheEnabled(
            SharedRegion_getId(localNextElem));

    if (localPrevElemIsCached) {
        Cache_inv(localPrevElem, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }
    if (localNextElemIsCached) {
        Cache_inv(localNextElem, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }

    localPrevElem->next = elem->next;
    localNextElem->prev = elem->prev;

    if (localPrevElemIsCached) {
        Cache_wbInv(localPrevElem, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }
    if (localNextElemIsCached) {
        Cache_wbInv(localNextElem, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }

    GateMP_leave((GateMP_Handle)obj->gate, key);

    return (ListMP_S_SUCCESS);
}

/*
 *************************************************************************
 *                       Instance functions
 *************************************************************************
 */

/*
 *  ======== ti_sdo_ipc_ListMP_Instance_init ========
 */
Int ti_sdo_ipc_ListMP_Instance_init(ti_sdo_ipc_ListMP_Object *obj,
        const ti_sdo_ipc_ListMP_Params *params,
        Error_Block *eb)
{
    SharedRegion_SRPtr sharedShmBase;
    Ptr localAddr;
    Int status;
    ListMP_Params sparams;
    IHeap_Handle regionHeap;

    if (params->openFlag == TRUE) {
        /* Open by sharedAddr */
        obj->objType = ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC;
        obj->attrs = (ti_sdo_ipc_ListMP_Attrs *)params->sharedAddr;
        obj->regionId = SharedRegion_getId(&(obj->attrs->head));
        obj->cacheEnabled = SharedRegion_isCacheEnabled(obj->regionId);
        obj->cacheLineSize = SharedRegion_getCacheLineSize(obj->regionId);

#ifdef xdc_target__isaCompatible_v7A
    /* ARM speculative execution might have pulled attrs into cache */
    if (obj->cacheEnabled) {
        Cache_inv(obj->attrs, sizeof(ti_sdo_ipc_ListMP_Attrs), Cache_Type_ALL,
                TRUE);
    }
#endif
        /* get the local address of the SRPtr */
        localAddr = SharedRegion_getPtr(obj->attrs->gateMPAddr);

        status = GateMP_openByAddr(localAddr, (GateMP_Handle *)&(obj->gate));
        if (status != GateMP_S_SUCCESS) {
            Error_raise(eb, ti_sdo_ipc_Ipc_E_internal, 0, 0);
            return (1);
        }

        return (0);
    }

    /* init the gate */
    if (params->gate != NULL) {
        obj->gate = params->gate;
    }
    else {
        obj->gate = (ti_sdo_ipc_GateMP_Handle)GateMP_getDefaultRemote();
    }

    if (params->sharedAddr == NULL) {
        /* Creating using a shared region ID */
        obj->objType = ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC_REGION;
        obj->regionId = params->regionId;
        obj->cacheEnabled = SharedRegion_isCacheEnabled(obj->regionId);
        obj->cacheLineSize = SharedRegion_getCacheLineSize(obj->regionId);

        /* Need to allocate from the heap */
        ListMP_Params_init(&sparams);
        sparams.regionId = params->regionId;
        obj->allocSize = ListMP_sharedMemReq(&sparams);

        regionHeap = SharedRegion_getHeap(obj->regionId);
        Assert_isTrue(regionHeap != NULL, ti_sdo_ipc_SharedRegion_A_noHeap);

        /* The region heap will take care of the alignment */
        obj->attrs = Memory_alloc(regionHeap, obj->allocSize, 0, eb);

        if (obj->attrs == NULL) {
            return (2);
        }
    }
    else {
        /* Creating using sharedAddr */
        obj->regionId = SharedRegion_getId(params->sharedAddr);

        /* Assert that the buffer is in a valid shared region */
        Assert_isTrue(obj->regionId != SharedRegion_INVALIDREGIONID,
                      ti_sdo_ipc_Ipc_A_addrNotInSharedRegion);

        /* set object's cacheEnabled, objType, and attrs  */
        obj->cacheEnabled = SharedRegion_isCacheEnabled(obj->regionId);
        obj->cacheLineSize = SharedRegion_getCacheLineSize(obj->regionId);
        obj->objType = ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC;
        obj->attrs = (ti_sdo_ipc_ListMP_Attrs *)params->sharedAddr;

        /* Assert that sharedAddr is cache aligned */
        Assert_isTrue((obj->cacheLineSize == 0) ||
                      ((UInt32)params->sharedAddr % obj->cacheLineSize == 0),
                      ti_sdo_ipc_Ipc_A_addrNotCacheAligned);
    }

    /* init the head (to be empty) */
    ListMP_elemClear(&(obj->attrs->head));

    /* store the GateMP sharedAddr in the Attrs */
    obj->attrs->gateMPAddr = ti_sdo_ipc_GateMP_getSharedAddr(obj->gate);

    /* last thing, set the status */
    obj->attrs->status = ti_sdo_ipc_ListMP_CREATED;

    if (obj->cacheEnabled) {
        Cache_wbInv(obj->attrs, sizeof(ti_sdo_ipc_ListMP_Attrs),
                Cache_Type_ALL, TRUE);
    }

    /* add to NameServer if name not NULL */
    if (params->name != NULL) {
        sharedShmBase = SharedRegion_getSRPtr(obj->attrs, obj->regionId);
        obj->nsKey = NameServer_addUInt32(
            (NameServer_Handle)ListMP_module->nameServer, params->name,
            (UInt32)sharedShmBase);

        if (obj->nsKey == NULL) {
            Error_raise(eb, ti_sdo_ipc_Ipc_E_nameFailed, params->name, 0);
            return (3);
        }
    }

    return (0);
}

/*
 *  ======== ti_sdo_ipc_ListMP_Instance_finalize ========
 */
Void ti_sdo_ipc_ListMP_Instance_finalize(ti_sdo_ipc_ListMP_Object *obj,
        Int status)
{
    if (obj->objType & (ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC |
                        ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC_REGION)) {
        /* List is being deleted */
        /* Remove entry from NameServer */
        if (obj->nsKey != NULL) {
            NameServer_removeEntry((NameServer_Handle)ListMP_module->nameServer,
                    obj->nsKey);
        }

        /* Set status to 'not created' */
        if (obj->attrs != NULL) {
            obj->attrs->status = 0;
            if (obj->cacheEnabled == TRUE) {
                Cache_wbInv(obj->attrs, sizeof(ti_sdo_ipc_ListMP_Attrs),
                    Cache_Type_ALL, TRUE);
            }
        }

        /*
         *  Free the shared memory back to the region heap. If NULL, then the
         *  Memory_alloc failed.
         */
        if (obj->objType == ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC_REGION &&
            obj->attrs != NULL) {
            Memory_free(SharedRegion_getHeap(obj->regionId), obj->attrs,
                        obj->allocSize);
        }
    }
    else {
        /* List is being closed */
        /* Close the gate. If NULL, then GateMP_openByAddr failed. */
        if (obj->gate != NULL) {
            GateMP_close((GateMP_Handle *)&(obj->gate));
        }
    }
}

/*
 *************************************************************************
 *                       Module functions
 *************************************************************************
 */
/*
 *  ======== ti_sdo_ipc_ListMP_elemClear ========
 */
Void ti_sdo_ipc_ListMP_elemClear(ti_sdo_ipc_ListMP_Elem *elem)
{
    SharedRegion_SRPtr sharedElem;
    UInt16 id;

    id = SharedRegion_getId(elem);
    sharedElem = SharedRegion_getSRPtr(elem, id);

    elem->next = elem->prev = sharedElem;
    if (SharedRegion_isCacheEnabled(id)) {
        Cache_wbInv(elem, sizeof(ListMP_Elem), Cache_Type_ALL, TRUE);
    }
}
