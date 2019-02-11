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
 *  ======== HeapStd.h ========
 */
#ifndef ti_ipc_heaps_HeapStd_h
#define ti_ipc_heaps_HeapStd_h

#include <ti/ipc/interfaces/IHeap.h>

#if defined (__cplusplus)
extern "C" {
#endif

#define HeapStd_S_SUCCESS       0
#define HeapStd_E_FAIL          -1

/*
 *  ======== HeapStd_Handle ========
 *  Opaque handle to heap instance object
 */
typedef struct HeapStd_Module *HeapStd_Handle;

/*
 *  ======== HeapStd_handle ========
 *  Return the heap handle
 *
 *  This module does not support instance creation. When the module
 *  is initialized, a single implicit instance is created. This method
 *  returns the handle to this implicit instance.
 */
HeapStd_Handle HeapStd_handle(void);

/*
 *  ======== HeapStd_upCast ========
 *  Instance converter, return a handle to the inherited interface
 */
IHeap_Handle HeapStd_upCast(HeapStd_Handle inst);

/*
 *  ======== HeapStd_downCast ========
 *  Instance converter, return an opaque handle to the instance object
 *
 *  It is the caller's responsibility to ensure the underlying object
 *  is of the correct type.
 */
HeapStd_Handle HeapStd_downCast(IHeap_Handle base);


#if defined (__cplusplus)
}
#endif
#endif
