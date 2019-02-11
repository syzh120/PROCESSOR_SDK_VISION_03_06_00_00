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

/*
 *  ======== HeapStd.c ========
 */

#include <stdlib.h>                     /* malloc */

#include <ti/ipc/heaps/HeapStd.h>
#include <ti/ipc/interfaces/IHeap.h>


/*
 *  ======== HeapStd_Module ========
 */
typedef struct {
    IHeap_Object base;                  /* inheritance */
} HeapStd_Module;

/*
 *  ======== instance function declarations ========
 */
void *HeapStd_alloc(void *handle, size_t size);
void HeapStd_free(void *handle, void *block);

/*
 *  ======== HeapStd_Fxns ========
 *  The instance function table
 */
IHeap_Fxns HeapStd_Fxns = {
    HeapStd_alloc,
    HeapStd_free
};

/*
 *  ======== HeapStd_module ========
 *  The module state object
 */
static HeapStd_Module HeapStd_module = {
    .base.fxns = &HeapStd_Fxns
};

/*
 *  ======== HeapStd_handle ========
 */
HeapStd_Handle HeapStd_handle(void)
{
    HeapStd_Handle handle;

    handle = (HeapStd_Handle)&HeapStd_module;
    return (handle);
}

/*
 *  ======== HeapStd_upCast ========
 */
IHeap_Handle HeapStd_upCast(HeapStd_Handle inst)
{
    return ((IHeap_Handle)inst);
}

/*
 *  ======== HeapStd_downCast ========
 */
HeapStd_Handle HeapStd_downCast(IHeap_Handle base)
{
    return ((HeapStd_Handle)base);
}

/*
 *  ======== HeapStd_alloc ========
 */
void *HeapStd_alloc(void *handle, size_t size)
{
    void *block;

    block = malloc(size);
    return (block);
}

/*
 *  ======== HeapStd_free ========
 */
void HeapStd_free(void *handle, void *block)
{
    free(block);
}
