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
 *  ======== _rmmScratch.h ========
 */

#ifndef ti_sdo_fc_utils__RMMSCRATCH_H
#define ti_sdo_fc_utils__RMMSCRATCH_H

#include "rmmScratch.h"

/*
 *  ======== RMMS_Header ========
 *  This header is used to maintain a list of free memory blocks.
 */
typedef struct RMMS_Header {
    Int         nextIdx;   /* Index of next header */
    Uns         size;   /* size of the free memory */
    UInt32      addr;   /* Address of memory block */
    Int         scratchId;
                        /* Scratch Id to which this block belongs */
    Int         refCount;
                        /* Number of times this block has been granted to
                           a scratch group. Should always be 1 when scratchId
                           is -1 */
} RMMS_Header;

/*
 *  ======== RMMS_Obj ========
 */
typedef struct RMMS_Obj {
    UInt32          base;           /* base of memory segment */
    UInt32          length;         /* length of memory segment */
    RMMS_Header     availList;      /* List of free memory blocks
                                     * Keeps track of available memory blocks.
                                     * Initially this list points to the entire
                                     * block of memory to be managed.
                                     */

    RMMS_Header     headerPool;     /* Pool of RMM headers so we don't
                                     * have to allocate any in RMMS_free().
                                     * Points to a list of preallocated
                                     * RMMS_Header linked list that correspond
                                     * to available allocatable RMMS_Headers
                                     * Maximum number of these entries is
                                     * nHeaders
                                     */
    UInt32          headers;         /* Offset of RMMS_Headers array
                                      * This points to the pre-allocated RMM
                                      * headers that keep track of allocated
                                      * memory
                                      */
    Int             segid;           /* Memory segment to allocate from */
    Int             nHeaders;        /* Number of RMM headers allocated */
    RMMS_allocFxn   allocFxn;
    RMMS_freeFxn    freeFxn;
} RMMS_Obj;

#endif
