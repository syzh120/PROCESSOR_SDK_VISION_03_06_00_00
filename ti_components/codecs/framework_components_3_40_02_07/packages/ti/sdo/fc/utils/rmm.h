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
 *  ======== rmm.h ========
 *
 *  This "remote" memory manager provides general heap management of an
 *  arbitrary memory segment.
 *
 *  Public functions:
 *      RMM_alloc
 *      RMM_create
 *      RMM_delete
 *      RMM_exit
 *      RMM_free
 *      RMM_init
 *
 */

#ifndef ti_sdo_fc_utils_RMM_H_
#define ti_sdo_fc_utils_RMM_H_

/*
 *  Name to use when enabling logging for this module with Diags_setMask().
 *  eg, Diags_setMask(RMM_MODNAME"+EX1234567");
 */
#define RMM_MODNAME "ti.sdo.fc.utils.RMM"

typedef Void * (*RMM_allocFxn)(Int segid, Uint32 size, Uint32 align);
typedef Bool  (*RMM_freeFxn)(Int segid, Void *addr, Uint32 size);

/*
 *  ======== RMM_Attrs ========
 *  Attributes passed to RMM_create().
 */
typedef struct RMM_Attrs {
    Int          segid;              /* Heap ID used for internal RMM allocs */
    Uns          maxFreeListBlocks;  /* Maximum number of free blocks */
    Uint32       base;               /* Base address of memory to be managed */
    Uint32       length;             /* Size (MAUs) of memory to be managed */
    RMM_allocFxn allocFxn;           /* Function to alloc internal RMM objs */
    RMM_freeFxn  freeFxn;            /* Function to free internal RMM objs */
} RMM_Attrs;

/*
 *  ======== RMM_Segment ========
 *  Memory segment on the DSP available for remote allocations.
 */
typedef struct RMM_Segment {
    Uint32  base;       /* Base of the segment */
    Uint32  length;     /* Size of the segment (target MAUs) */
} RMM_Segment;

/*
 *  ======== RMM_Stat ========
 *  Status structure for RMM_Segment, used for debugging.
 */
typedef struct RMM_Stat {
    Uint32  size;       /* original size of segment */
    Uint32  used;       /* number of bytes used in segment */
    Uint32  length;     /* length of largest contiguous block (target MAUs) */
    Uns     nBlocks;    /* Total number of free blocks */
} RMM_Stat;

/*
 *  ======== RMM_Handle ========
 */
typedef struct RMM_Obj *RMM_Handle;


/*
 *  ======== RMM_alloc ========
 *
 *  RMM_alloc is used to remotely allocate or reserve memory on the DSP.
 *  This call does not use any synchronization objects to protect internal
 *  structures, so it is up to the caller to ensure that this call is
 *  protected!
 *
 *  Parameters:
 *      rmmHandle       - Handle returned from RMM_create().
 *      size            - Size (target MAUS) to allocate.
 *      pAddr           - Location to store allocated address.
 *  Returns:
 *      TRUE:                   Success.
 *      FALSE:                  Memory allocation failed.
 *
 *  Requires:
 *      Valid rmmHandle.
 *      dspAddr != NULL.
 *      size > 0
 *      reserve || rmmHandle->numSegs > 0.
 *  Ensures:
 */
extern Bool RMM_alloc(RMM_Handle rmmHandle, Uint32 size, Uint32 *pAddr);

/*
 *  ======== RMM_check ========
 *
 *  RMM_check checks (via asserts) the "sanity" of the free list for
 *  all valid memory segments.
 */
extern Void RMM_check(RMM_Handle rmmHandle, RMM_Stat *stat);

/*
 *  ======== RMM_create ========
 *  Create an RMM object for reserving memory.
 *
 *  Parameters:
 *      seg:         - memory segment base, length.
 *      attrs:       - pointer to RMM_Attrs.
 *  Returns:
 *      attrs != NULL
 *      attrs->maxFreeListBlocks > 0
 *  Requires:
 *      attrs != NULL
 *      attrs->maxFreeListBlocks > 0;
 *      attrs->length > 0;
 *  Ensures:
 */
extern RMM_Handle RMM_create(RMM_Attrs *attrs);

/*
 *  ======== RMM_delete ========
 *  Delete rmmHandle allocated in RMM_create().
 *
 *  Parameters:
 *      rmmHandle          - Handle returned from RMM_create().
 *  Returns:
 *  Requires:
 *      RMM initialized.
 *      rmmHandle != NULL.
 *  Ensures:
 */
extern Void RMM_delete(RMM_Handle rmmHandle);

/*
 *  ======== RMM_exit ========
 *  Exit the RMM module
 *
 *  Parameters:
 *  Returns:
 *  Requires:
 *  Ensures:
 */
extern Void RMM_exit(Void);

/*
 *  ======== RMM_free ========
 *  Free or unreserve memory allocated through RMM_alloc().
 *  This call does not use any synchronization objects to protect internal
 *  structures, so it is up to the caller to ensure that this call is
 *  protected!
 *
 *  Parameters:
 *      rmmHandle:      - Handle returned from RMM_create().
 *      addr:           - Address to free.
 *      size:           - Size of memory to free.
 *  Returns:
 *  Requires:
 *      rmmHandle != NULL.
 *      size > 0
 *  Ensures:
 */
extern Bool RMM_free(RMM_Handle rmmHandle, Uint32 dspAddr, Uint32 size);

/*
 *  ======== RMM_init ========
 *  Initialize the RMM module
 *
 *  Parameters:
 *  Returns:
 *  Requires:
 *  Ensures:
 */
extern Void RMM_init(Void);


#endif /* ti_sdo_fc_utils_RMM_H_ */
