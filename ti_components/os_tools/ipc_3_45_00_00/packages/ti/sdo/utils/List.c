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
 * */
/*
 *  ======== List.c ========
 *  Implementation of functions specified in List.xdc.
 */

#include <xdc/std.h>

#include <ti/sysbios/hal/Hwi.h>

#include "package/internal/List.xdc.h"

/*
 *************************************************************************
 *                       Instance functions
 *************************************************************************
 */

/*
 *  ======== List_Instance_init ========
 */
Void List_Instance_init(List_Object *obj, const List_Params *params)
{
    obj->elem.next = obj->elem.prev = &(obj->elem);
}

/*
 *  ======== List_empty ========
 *  No thread-safety is needed since this API does not modify
 *  any of the contents.
 */
Bool List_empty(List_Object *obj)
{
    return (obj->elem.next == &(obj->elem));
}

/*
 *  ======== List_get ========
 */
Ptr List_get(List_Object *obj)
{
    List_Elem *elem;
    UInt key;

    key = Hwi_disable();

    elem = List_dequeue(obj);

    Hwi_restore(key);

    return (elem);
}

/*
 *  ======== List_put ========
 */
Void List_put(List_Object *obj, List_Elem *elem)
{
    UInt key;

    key = Hwi_disable();

    List_enqueue(obj, elem);

    Hwi_restore(key);
}

/*
 *  ======== List_putHead ========
 */
Void List_putHead(List_Object *obj, List_Elem *elem)
{
    UInt key;

    key = Hwi_disable();

    List_enqueueHead(obj, elem);

    Hwi_restore(key);
}

/*
 *  ======== List_insert ========
 */
Void List_insert(List_Object *obj, List_Elem *newElem, List_Elem *curElem)
{
    List_enqueue((List_Object *)curElem, newElem);
}

/*
 *  ======== List_next ========
 */
Ptr List_next(List_Object *obj, List_Elem *elem)
{
    List_Elem *retElem;  /* returned elem */

    /* elem == NULL -> start at the head */
    if (elem == NULL) {
        retElem = obj->elem.next;
    }
    else {
        retElem = elem->next;
    }

    if (retElem == (List_Elem *)obj) {
        retElem = NULL;
    }

    return (retElem);
}

/*
 *  ======== List_prev ========
 */
Ptr List_prev(List_Object *obj, List_Elem *elem)
{
    List_Elem *retElem;  /* returned elem */

    /* elem == NULL -> start at the tail */
    if (elem == NULL) {
        retElem = obj->elem.prev;
    }
    else {
        retElem = elem->prev;
    }

    if (retElem == (List_Elem *)obj) {
        retElem = NULL;
    }

    return (retElem);
}

/*
 *  ======== List_remove ========
 */
Void List_remove(List_Object *obj, List_Elem *elem)
{
    elem->prev->next = elem->next;
    elem->next->prev = elem->prev;
}

/*
 *  ======== List_dequeue ========
 */
Ptr List_dequeue(List_Object *obj)
{
    List_Elem *elem;

    elem = obj->elem.next;

    /* See if the List was empty */
    if (elem == (List_Elem *)obj) {
        elem = NULL;
    }
    else {
        obj->elem.next   = elem->next;
        elem->next->prev = &(obj->elem);
    }

    return (elem);
}

/*
 *  ======== List_enqueue ========
 */
Void List_enqueue(List_Object *obj, List_Elem *elem)
{
    elem->next           = &(obj->elem);
    elem->prev           = obj->elem.prev;
    obj->elem.prev->next = elem;
    obj->elem.prev       = elem;
}

/*
 *  ======== List_enqueueHead ========
 */
Void List_enqueueHead(List_Object *obj, List_Elem *elem)
{
    elem->next           = obj->elem.next;
    elem->prev           = &(obj->elem);
    obj->elem.next->prev = elem;
    obj->elem.next       = elem;
}

/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*
 *  ======== List_elemClear ========
 */

Void List_elemClear(List_Elem *elem)
{
    elem->next = elem->prev = elem;
}
