/*
 * Copyright (c) 2015 Texas Instruments Incorporated - http://www.ti.com
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

/**
 *  @file       linux/include/ti/ipc/interfaces/IHeap.h
 *
 *  @brief      Interface to heap functions
 *
 *  Heap implementations to be registered with MessageQ must inherit
 *  and implement this interface. The heap implementation must have an
 *  API which returns an IHeap_Handle for each heap instance.
 *
 *  The IHeap interface includes the following instance methods:
 *
 *  alloc - allocate a block of memory from the heap
 *
 *  The allocated memory may be either uninitialized or zero-initialized.
 *  The implementation should document the behavior or provide an instance
 *  create parameter to define the behavior.
 *
 *  free - return a block of memory to the heap
 *
 *  This method gives back a block of memory to the heap instance. It is
 *  expected to always succeed (i.e. it does not return a failure code).
 */

/*
 *  ======== IHeap.h ========
 */

#ifndef ti_ipc_interfaces_IHeap_h
#define ti_ipc_interfaces_IHeap_h

#if defined (__cplusplus)
extern "C" {
#endif

/* opaque instance handle */
typedef struct IHeap_Object *IHeap_Handle;

/* virtual functions */
typedef struct IHeap_Fxns {
    void *(*alloc)(void *handle, size_t size);
    void (*free)(void *handle, void *block);
} IHeap_Fxns;

/* abstract instance object */
typedef struct IHeap_Object {
    IHeap_Fxns *fxns;
} IHeap_Object;

/* function stubs */
static inline
void *IHeap_alloc(IHeap_Handle inst, size_t size)
{
    IHeap_Object *obj = (IHeap_Object *)inst;
    return obj->fxns->alloc((void *)inst, size);
}

static inline
void IHeap_free(IHeap_Handle inst, void *block)
{
    IHeap_Object *obj = (IHeap_Object *)inst;
    obj->fxns->free((void *)inst, block);
}

#if defined (__cplusplus)
}
#endif
#endif
