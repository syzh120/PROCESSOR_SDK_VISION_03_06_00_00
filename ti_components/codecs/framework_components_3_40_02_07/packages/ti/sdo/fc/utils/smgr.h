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
 *  ======== smgr.h ========
 *
 *  This "remote" memory manager provides general scratch management of an
 *  arbitrary resource.
 *
 *  Public functions:
 *      SMGR_alloc
 *      SMGR_create
 *      SMGR_delete
 *      SMGR_exit
 *      SMGR_free
 *      SMGR_init
 *
 */

#ifndef ti_sdo_fc_utils_SMGR_H_
#define ti_sdo_fc_utils_SMGR_H_

#include <ti/xdais/ialg.h>

/*
 *  Name to use when enabling logging for this module with Diags_setMask().
 *  eg, Diags_setMask(SMGR_MODNAME"+EX1234567");
 */
#define SMGR_MODNAME "ti.sdo.fc.utils.SMGR"

typedef Void * (*SMGR_allocFxn)(Int segid, Uint32 size, Uint32 align);
typedef Bool  (*SMGR_freeFxn)(Int segid, Void *addr, Uint32 size);

/*
 *  ======== SMGR_Attrs ========
 *  Attributes passed to SMGR_create().
 */
typedef struct SMGR_Attrs {
    Int          segid;              /* Heap ID used for internal SMGR allocs */
    Uint32       numScratchGroups;   /* Number of scratch groups to manage */
    Uint32       numResources;       /* Number of resources to be managed */
    SMGR_allocFxn allocFxn;          /* Function to alloc internal SMGR objs */
    SMGR_freeFxn  freeFxn;           /* Function to free internal SMGR objs */
} SMGR_Attrs;

/*
 *  ======== SMGR_Handle ========
 */
typedef struct SMGR_Obj *SMGR_Handle;


/*
 *  ======== SMGR_alloc ========
 *
 *  SMGR_alloc is used to remotely allocate or reserve memory on the DSP.
 *
 *  Parameters:
 *      smgrHandle       - Handle returned from SMGR_create().
 *      alg              - Handle of the alg requesting the resource.
 *      resourceId       - Id of the resource to obtain, when NULL used as o/p,
 *                         else used to indicate specific resource to be
 *                         obtained.
 *      numResources     - Number of resources to acquire (always contiguous)
 *      scratchGroup     - Scratch Group to share the resource in.
 *  Returns:
 *      TRUE:                   Success.
 *      FALSE:                  Resource allocation failed.
 *
 *  Requires:
 *      Valid smgrHandle.
 *  Ensures:
 */
extern Bool SMGR_alloc(SMGR_Handle smgrHandle, IALG_Handle alg,
        Int * resourceId, Int numResources, Int scratchId);

/*
 *  ======== SMGR_create ========
 *  Create an SMGR object for reserving memory.
 *
 *  Parameters:
 *      attrs:       - pointer to SMGR_Attrs.
 *  Returns:
 *      attrs != NULL
 *  Requires:
 *      attrs != NULL
 *  Ensures:
 */
extern SMGR_Handle SMGR_create(SMGR_Attrs *attrs);

/*
 *  ======== SMGR_delete ========
 *  Delete smgrHandle allocated in SMGR_create().
 *
 *  Parameters:
 *      smgrHandle          - Handle returned from SMGR_create().
 *  Returns:
 *  Requires:
 *      SMGR initialized.
 *      smgrHandle != NULL.
 *  Ensures:
 */
extern Void SMGR_delete(SMGR_Handle smgrHandle);

/*
 *  ======== SMGR_exit ========
 *  Exit the SMGR module
 *
 *  Parameters:
 *  Returns:
 *  Requires:
 *  Ensures:
 */
extern Void SMGR_exit(Void);

/*
 *  ======== SMGR_free ========
 *  Free or unreserve memory allocated through SMGR_alloc().
 *
 *  Parameters:
 *      smgrHandle:      - Handle returned from SMGR_create().
 *      alg              - Algorithm handle
 *      resourceId:      - Resource to free.
 *      numResources     - Number of contiguous resources to tree
 *      scratchId:       - Scratch group from which to free the resource.
 *  Returns:
 *  Requires:
 *      smgrHandle != NULL.
 *      size > 0
 *  Ensures:
 */
extern Bool SMGR_free(SMGR_Handle smgrHandle, IALG_Handle alg, Int resourceId,
        Int numResources, Int scratchId);

/*
 *  ======== SMGR_init ========
 *  Initialize the SMGR module
 *
 *  Parameters:
 *  Returns:
 *  Requires:
 *  Ensures:
 */
extern Void SMGR_init(Void);


#endif /* ti_sdo_fc_utils_SMGR_H_*/
