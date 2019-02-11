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
 *  ======== rmp.h ========
 *
 *  This "remote" memory manager provides general heap management of an
 *  arbitrary memory segment.
 *
 *  Public functions:
 *      RMP_alloc
 *      RMP_create
 *      RMP_delete
 *      RMP_exit
 *      RMP_free
 *      RMP_init
 *
 */

#ifndef ti_sdo_fc_utils_RMP_H_
#define ti_sdo_fc_utils_RMP_H_

#include "rmm.h"
#include <xdc/runtime/knl/GateProcess.h>

#define RMMP_MAXINSTANCES 5

/*
 *  Name to use when enabling logging for this module with Diags_setMask().
 *  eg, Diags_setMask(RMMP_MODNAME"+EX1234567");
 */
#define RMMP_MODNAME "ti.sdo.fc.utils.RMMP"

/*
 *  ======== RMP_Attrs ========
 *  Attributes passed to RMP_create().
 */
typedef struct RMP_Attrs {
    Uns             maxFreeListBlocks;
                                     /* Maximum number of free blocks */
    Uint32          base;            /* Base address of memory to be managed */
    Uint32          length;          /* Size (MAUs) of memory to be managed */
    GateProcess_Handle   gate;
    void *          key;
} RMP_Attrs;

/*
 *  ======== RMP_Handle ========
 */
typedef struct RMP_Obj *RMP_Handle;

/*
 *  ======== RMP_Stat ========
 *  Status structure for RMM_Segment, used for debugging.
 */
typedef struct RMP_Stat {
    Uint32  size;       /* original size of segment */
    Uint32  used;       /* number of bytes used in segment */
    Uint32  length;     /* length of largest contiguous block (target MAUs) */
    Uns     nBlocks;    /* Total number of free blocks */
} RMP_Stat;

/*
 *  ======== RMP_alloc ========
 *
 *  RMP_alloc is used to remotely allocate or reserve memory on the DSP.
 *
 *  Parameters:
 *      rmpHandle       - Handle returned from RMP_create().
 *      size            - Size (target MAUS) to allocate.
 *      pAddr           - Location to store allocated address.
 *  Returns:
 *      TRUE:                   Success.
 *      FALSE:                  Memory allocation failed.
 *
 *  Requires:
 *      Valid rmpHandle.
 *      dspAddr != NULL.
 *      size > 0
 *      reserve || rmpHandle->numSegs > 0.
 *  Ensures:
 */
extern Bool RMP_alloc(RMP_Handle rmpHandle, Uint32 size, Uint32 *pAddr);

/*
 *  ======== RMP_check ========
 *
 *  RMP_check checks (via asserts) the "sanity" of the free list for
 *  all valid memory segments.
 */
extern Void RMP_check(RMP_Handle rmpHandle, RMP_Stat *stat);

/*
 *  ======== RMP_create ========
 *  Create an RMP object for reserving memory.
 *
 *  Parameters:
 *      seg:         - memory segment base, length.
 *      attrs:       - pointer to RMP_Attrs.
 *  Returns:
 *      attrs != NULL
 *      attrs->maxFreeListBlocks > 0
 *  Requires:
 *      attrs != NULL
 *      attrs->maxFreeListBlocks > 0;
 *      attrs->length > 0;
 *  Ensures:
 */
extern RMP_Handle RMP_create(RMP_Attrs *attrs);

/*
 *  ======== RMP_delete ========
 *  Delete rmpHandle allocated in RMP_create().
 *
 *  Parameters:
 *      rmpHandle          - Handle returned from RMP_create().
 *  Returns:
 *  Requires:
 *      RMP initialized.
 *      rmpHandle != NULL.
 *  Ensures:
 */
extern Void RMP_delete(RMP_Handle rmpHandle);

/*
 *  ======== RMP_exit ========
 *  Exit the RMP module
 *
 *  Parameters:
 *  Returns:
 *  Requires:
 *  Ensures:
 */
extern Void RMP_exit(Void);

/*
 *  ======== RMP_free ========
 *  Free or unreserve memory allocated through RMP_alloc().
 *
 *  Parameters:
 *      rmpHandle:      - Handle returned from RMP_create().
 *      addr:           - Address to free.
 *      size:           - Size of memory to free.
 *  Returns:
 *  Requires:
 *      rmpHandle != NULL.
 *      size > 0
 *  Ensures:
 */
extern Bool RMP_free(RMP_Handle rmpHandle, Uint32 dspAddr, Uint32 size);

/*
 *  ======== RMP_init ========
 *  Initialize the RMP module
 *
 *  Parameters:
 *  Returns:
 *  Requires:
 *  Ensures:
 */
extern Void RMP_init(Void);


#endif /* ti_sdo_fc_utils_RMP_H_ */
