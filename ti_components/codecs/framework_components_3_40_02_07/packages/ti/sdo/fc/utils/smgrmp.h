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
 *  ======== smgrmp.h ========
 *
 *  This "remote" memory manager provides general scratch management of an
 *  arbitrary resource.
 *
 *  Public functions:
 *      SMGRMP_alloc
 *      SMGRMP_create
 *      SMGRMP_delete
 *      SMGRMP_exit
 *      SMGRMP_free
 *      SMGRMP_init
 *
 */

#ifndef ti_sdo_fc_utils_SMGRMP_H_
#define ti_sdo_fc_utils_SMGRMP_H_

#include "smgr.h"
#include <xdc/runtime/knl/GateProcess.h>

#define SMGRMP_MAXINSTANCES 5

#define SMGRMP_MODNAME "ti.sdo.fc.utils.SMGRMP"

/*
 *  ======== SMGRMP_Attrs ========
 *  Attributes passed to SMGRMP_create().
 */
typedef struct SMGRMP_Attrs {
    Uint32          numScratchGroups;  /* Number of scratch groups to manage */
    Uint32          numResources;      /* Number of resources to be managed */
    GateProcess_Handle gate;
    void *          key;
} SMGRMP_Attrs;

/*
 *  ======== SMGRMP_Handle ========
 */
typedef struct SMGRMP_Obj *SMGRMP_Handle;


/*
 *  ======== SMGRMP_alloc ========
 *
 *  SMGRMP_alloc is used to remotely allocate or reserve memory on the DSP.
 *
 *  Parameters:
 *      smgrHandle       - Handle returned from SMGRMP_create().
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
extern Bool SMGRMP_alloc(SMGRMP_Handle smgrHandle, IALG_Handle alg,
        Int * resourceId, Int numResources, Int scratchId);

/*
 *  ======== SMGRMP_create ========
 *  Create an SMGR object for reserving memory.
 *
 *  Parameters:
 *      attrs:       - pointer to SMGRMP_Attrs.
 *  Returns:
 *      attrs != NULL
 *  Requires:
 *      attrs != NULL
 *  Ensures:
 */
extern SMGRMP_Handle SMGRMP_create(SMGRMP_Attrs *attrs);

/*
 *  ======== SMGRMP_delete ========
 *  Delete smgrHandle allocated in SMGRMP_create().
 *
 *  Parameters:
 *      smgrHandle          - Handle returned from SMGRMP_create().
 *  Returns:
 *  Requires:
 *      SMGR initialized.
 *      smgrHandle != NULL.
 *  Ensures:
 */
extern Void SMGRMP_delete(SMGRMP_Handle smgrHandle);

/*
 *  ======== SMGRMP_exit ========
 *  Exit the SMGR module
 *
 *  Parameters:
 *  Returns:
 *  Requires:
 *  Ensures:
 */
extern Void SMGRMP_exit(Void);

/*
 *  ======== SMGRMP_free ========
 *  Free or unreserve memory allocated through SMGRMP_alloc().
 *
 *  Parameters:
 *      smgrHandle:      - Handle returned from SMGRMP_create().
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
extern Bool SMGRMP_free(SMGRMP_Handle smgrHandle, IALG_Handle alg, Int resourceId,
        Int numResources, Int scratchId);

/*
 *  ======== SMGRMP_init ========
 *  Initialize the SMGR module
 *
 *  Parameters:
 *  Returns:
 *  Requires:
 *  Ensures:
 */
extern Void SMGRMP_init(Void);


#endif /* ti_sdo_fc_utils_SMGRMP_H_*/
