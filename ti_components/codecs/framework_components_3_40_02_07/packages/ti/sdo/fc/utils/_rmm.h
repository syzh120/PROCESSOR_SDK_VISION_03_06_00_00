/*
 * Copyright (c) 2012, Texas Instruments Incorporated
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
 *  ======== _rmm.h ========
 */

#ifndef ti_sdo_fc_utils__RMM_H
#define ti_sdo_fc_utils__RMM_H

#include "rmm.h"

/*
 *  ======== RMM_Header ========
 *  This header is used to maintain a list of free memory blocks.
 */
typedef struct RMM_Header {
    Int         next;   /* Index of next header */
    Uns         size;   /* size of the free memory */
    UInt32      addr;   /* Address of memory block */
} RMM_Header;

/*
 *  ======== RMM_Obj ========
 */
typedef struct RMM_Obj {
    UInt32          base;           /* base of memory segment */
    UInt32          length;         /* length of memory segment */
    RMM_Header      freeList;       /* List of free memory blocks
                                     * Keeps track of freed memory blocks
                                     * Initially this list points to the entire
                                     * block of memory to be managed.
                                     */

    RMM_Header      headerPool;     /* Pool of RMM headers so we don't
                                     * have to allocate any in RMM_free().
                                     * Points to a list of preallocated
                                     * RMM_Header linked list that correspond
                                     * to available allocatable RMM_Headers
                                     * Maximum number of these entries is
                                     * nHeaders
                                     */
    UInt32          headers;         /* Offset of RMM_Headers array
                                      * This points to the pre-allocated RMM
                                      * headers that keep track of allocated
                                      * memory
                                      */
    Int             segid;           /* Memory segment to allocate from */
    Int             nHeaders;        /* Number of RMM headers allocated */
    RMM_allocFxn    allocFxn;
    RMM_freeFxn     freeFxn;
} RMM_Obj;

#endif
