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
 */
/*
 *  ======== List.xdc ========
 *
 */

import xdc.rov.ViewInfo;

/*!
 *  ======== List ========
 *  Doubly Linked List Manager
 *
 *  The List module makes available a set of functions that manipulate
 *  List objects accessed through handles of type List_Handle.
 *  Each List contains a linked sequence of zero or more elements
 *  referenced through variables of type List_Elem, which are typically
 *  embedded as the first field within a structure.
 *
 *  All List function are atomic unless noted otherwise in the API
 *  descriptions. An atomic API means that the API completes in core
 *  functionality without being interrupted. Therefore, atomic APIs are
 *  thread-safe. An example is {@link #put}. Multiple threads can call
 *  {@link #put} at the same time. The threads do not have to manage the
 *  synchronization.
 *
 *  The {@link xdc.runtime.Gate#enterSystem}/{@link xdc.runtime.Gate#leaveSystem}
 *  calls are used to make the APIs atomic. This Gate calls internally use
 *  {@link xdc.runtime.System}'s gate.
 *
 *  The List module can be used both as a queue (i.e. First In First Out),
 *  as a stack (i.e. Last In First Out), or as a general purpose linked list.
 *
 *  Lists are represented as doubly-linked lists, so calls to {@link #next}
 *  or {@link #prev} can loop continuously over the List.
 *  Refer to {@link #next} and {@link #prev} for examples.
 *
 *  @a(List as a Queue)
 *
 *  To treat the list object as a queue:
 *  @p(blist)
 *  -Use {@link #put} to put at the tail of the queue
 *  -Use {@link #get} to get from the head of the queue
 *  @p
 *
 *  Here is sample code that acts on a List instance (listHandle) as a queue
 *  in a FIFO manner.
 *
 *  @p(code)
 *  List_Elem  elem[4];
 *  List_Elem *tmpElem;
 *
 *  // place at the tail of the queue
 *  for (i = 0; i < 4; i++) {
 *      List_put(listHandle, &(elem[i]));
 *  }
 *
 *  // remove the buffers from the head
 *  while((tmpElem = List_get(listHandle)) != NULL) {
 *      // process tmpElem
 *  }
 *  @p
 *
 *  @a(List as a Stack)
 *
 *  To treat the list object as a stack:
 *  @p(blist)
 *  -Use {@link #putHead} to put at the top of the stack
 *  -Use {@link #get} to get from the top of the stack
 *  @p
 *
 *  Here is sample code that acts on a List instance (listHandle) as a stack
 *  in a LIFO manner.
 *
 *  @p(code)
 *  List_Elem  elem[4];
 *  List_Elem *tmpElem;
 *
 *  // push onto the top (i.e. head)
 *  for (i = 0; i < 4; i++) {
 *      List_putHead(listHandle, &(elem[i]));
 *  }
 *
 *  // remove the buffers in FIFO order.
 *  while((tmpElem = List_get(listHandle)) != NULL) {
 *      // process tmpElem
 *  }
 *  @p
 */

module List
{
    metaonly struct BasicView {
        String  label;
        Ptr     elems[];
    }

    @Facet
    metaonly config ViewInfo.Instance rovViewInfo =
        ViewInfo.create({
            viewMap: [
                ['Basic', {type: ViewInfo.INSTANCE, viewInitFxn: 'viewInitInstance', structName: 'BasicView'}]
            ]
        });

    /*!
     *  ======== Elem ========
     *  Opaque List element
     *
     *  A field of this type is placed at the head of client structs.
     */
    @Opaque struct Elem {
        Elem *volatile next;    /* must be volatile for whole_program */
        Elem *volatile prev;    /* must be volatile for whole_program */
    };

    /*!
     *  ======== elemClearMeta ========
     *  Clears a List element's pointers
     *
     *  This API is not for removing elements from a List, and
     *  should never be called on an element in a List--only on deListed
     *  elements.
     *
     *  @param(elem)            element to be cleared
     */
    metaonly Void elemClearMeta(Elem *elem);

    /*!
     *  ======== elemClear ========
     *  Clears a List element's pointers
     *
     *  This API does not removing elements from a List, and
     *  should never be called on an element in a List--only on deListed
     *  elements.
     *
     *  @param(elem)            element to be cleared
     */
    @DirectCall
    Void elemClear(Elem *elem);

instance:

    /*!
     *  ======== metaList ========
     *  @_nodoc
     *  Used to store elem before the object is initialized.
     */
    metaonly config any metaList[];

    /*!
     *  ======== create ========
     *  Create a List object
     */
    create();

    /*!
     *  ======== empty ========
     *  Test for an empty List (atomic)
     *
     *  @b(returns)     TRUE if this List is empty
     */
    @DirectCall
    Bool empty();

    /*!
     *  ======== get ========
     *  Get element from front of List (atomic)
     *
     *  This function atomically removes the element from the front of a
     *  List and returns a pointer to it.
     *
     *  @b(returns)     pointer to former first element or NULL if empty
     */
    @DirectCall
    Ptr get();

    /*!
     *  ======== put ========
     *  Put element at end of List (atomic)
     *
     *  This function atomically places the element at the end of
     *  List.
     *
     *  @param(elem)    pointer to new List element
     */
    @DirectCall
    Void put(Elem *elem);

    /*!
     *  ======== putHead ========
     *  Put element at head of List (atomic)
     *
     *  This function atomically places the element at the front of
     *  List.
     *
     *  @param(elem)    pointer to new List element
     */
    @DirectCall
    Void putHead(Elem *elem);

    /*!
     *  ======== putMeta ========
     *  @_nodoc
     *  Put element at end of List.
     *
     *  This meta function can be used to place an element onto
     *  the end of a list during configuration. There currently
     *  is no meta API to place the elem at the head of the list
     *  during configuration.
     *
     *  @param(elem)            pointer to new List element
     */
    metaonly Void putMeta(Elem* elem);

    /*!
     *  ======== next ========
     *  Return next element in List (non-atomic)
     *
     *  This function returns the next element on a list. It does not
     *  remove any items from the list. The caller should protect the
     *  list from being changed while using this call since it is non-atomic.
     *
     *  To look at the first elem on the list, use NULL as the elem argument.
     *
     *  This function is useful in searching a list. The following code shows
     *  an example. The scanning of a list should be protected against other
     *  threads that modify the list.
     *
     *  @p(code)
     *  List_Elem  *elem = NULL;
     *
     *  // Begin protection against modification of the list.
     *
     *  while ((elem = List_next(listHandle, elem)) != NULL) {
     *      //act elem as needed. For example call List_remove().
     *  }
     *
     *  // End protection against modification of the list.
     *  @p
     *
     *  @param(elem)    element in list or NULL to start at the head
     *
     *  @b(returns)     next element in list or NULL to denote end
     */
    @DirectCall
    Ptr next(Elem *elem);

    /*!
     *  ======== prev ========
     *  Return previous element in List (non-atomic)
     *
     *  This function returns the previous element on a list. It does not
     *  remove any items from the list. The caller should protect the
     *  list from being changed while using this call since it is non-atomic.
     *
     *  To look at the last elem on the list, use NULL as the elem argument.
     *
     *  This function is useful in searching a list in reverse order. The
     *  following code shows an example. The scanning of a list should be
     *  protected against other threads that modify the list.
     *
     *  @p(code)
     *  List_Elem  *elem = NULL;
     *
     *  // Begin protection against modification of the list.
     *
     *  while ((elem = List_prev(listHandle, elem)) != NULL) {
     *      //act elem as needed. For example call List_remove().
     *  }
     *
     *  // End protection against modification of the list.
     *  @p
     *
     *  @param(elem)    element in list or NULL to start at the end (i.e. tail)
     *
     *  @b(returns)     previous element in list or NULL to denote
     *                  no previous elem
     */
    @DirectCall
    Ptr prev(Elem *elem);

    /*!
     *  ======== insert ========
     *  Insert element at into a List (non-atomic)
     *
     *  This function inserts `newElem` in the queue in
     *  front of `curElem`. The caller should protect the
     *  list from being changed while using this call since it is non-atomic.
     *
     *  To place an elem at the end of the list, use {@link #put}.
     *  To place a elem at the front of the list, use {@link #putHead}.
     *
     *  @param(newElem)         element to insert
     *
     *  @param(curElem)         element to insert in front of
     */
    @DirectCall
    Void insert(Elem *newElem, Elem *curElem);

    /*!
     *  ======== remove ========
     *  Remove elem from middle of list (non-atomic)
     *
     *  This function removes an elem from a list.
     *  The `elem` parameter is a pointer to an existing element to be removed
     *  from the List.  The caller should protect the
     *  list from being changed while using this call since it is non-atomic.
     *
     *  @param(elem)            element in list
     */
    @DirectCall
    Void remove(Elem *elem);

    /*!
     *  ======== dequeue ========
     *  Get element from front of List (non-atomic)
     *
     *  This function atomically removes the element from the front of a
     *  List and returns a pointer to it.  This API is not thread safe.
     *  Use {@link #put} and {@link #get} if multiple calling contexts
     *  share the same list.
     *
     *  @b(returns)     pointer to former first element or NULL if empty
     */
    @DirectCall
    Ptr dequeue();

    /*!
     *  ======== enqueue ========
     *  Put element at end of List (non-atomic)
     *
     *  This function places the element at the end of a List.
     *  This API is not thread safe.  Use {@link #put} and {@link #get}
     *  if multiple calling contexts share the same list.
     *
     *  @param(elem)    pointer to new List element
     */
    @DirectCall
    Void enqueue(Elem *elem);

    /*!
     *  ======== enqueueHead ========
     *  Put element at head of List (non-atomic)
     *
     *  This function places the element at the front of the List.
     *  This API is not thread safe.  Use {@link #putHead}
     *  if multiple calling contexts share the same list.
     *
     *  @param(elem)    pointer to new List element
     */
    @DirectCall
    Void enqueueHead(Elem *elem);

internal:

    /* instance object */
    struct Instance_State {
        Elem elem;
    };
}
