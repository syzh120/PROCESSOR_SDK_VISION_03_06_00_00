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
 *  ======== smgr.c ========
 *  Description:
 *
 *  This "remote" memory manager provides general scratch management of an
 *  arbitrary resource.
 *
 *  Notes:
 *
 */

/*
 *  This define is for Logging and must precede the inclusion of any xdc
 *  header files
 */
#define Registry_CURDESC ti_sdo_fc_utils_smgr_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <ti/sdo/fc/global/FCSettings.h>

#include "smgr.h"
#include "_smgr.h"

static inline Void _alloc(SMGR_Handle handle, Int resourceId, Int scratchId,
        IALG_Handle alg);

static inline Bool _match(SMGR_Handle handle, Int resourceId, Int scratchId,
        IALG_Handle alg);

Registry_Desc ti_sdo_fc_utils_smgr_desc;

static Int refCount  = 0;

/*
 *  ======== SMGR_alloc ========
 */
Bool SMGR_alloc(SMGR_Handle handle, IALG_Handle alg, Int *resourceId, Int num,
        Int scratchId)
{
    Bool                status = TRUE;
    Bool                toMatch = TRUE;
    Bool                found = FALSE;
    Int i, j, saveIndex, tax, minTax, count;

    Assert_isTrue(handle != NULL, (Assert_Id)NULL);
    Assert_isTrue(scratchId < handle->numGroups, (Assert_Id)NULL);

    /* First check if resourceId is specified or not */
    if (*resourceId == SMGR_RESANY) {
        toMatch = FALSE;
    }

    /* If a resourceId is to be matched */
    if (toMatch) {

        Assert_isTrue(*resourceId < handle->numResources, (Assert_Id)NULL);

        /* First check availability only */
        for (i = 0 ; i < num; i++) {
            if (!(_match(handle, (Int)(*resourceId + i), scratchId, alg))) {
                status = FALSE;
                break;
            }
        }

        if (TRUE == status) {
            for (i = 0 ; i < num; i++) {
                _alloc(handle, (Int)(*resourceId + i), scratchId, alg);
            }
            /* Update maxId */
            RESMAXID = MAX((Int)(*resourceId + num - 1), RESMAXID);
        }

        return (status);
    }

    /* Return any "num" contiguous resources, while avoiding wastage */

    /* Scan entire resource List till "num" free entries are detected */
    minTax = handle->numResources;         /* Optimal entry requires minimal
                                           allocs */
    tax = 0;
    saveIndex = RESMAXID;                 /* Saves the index at which optimal
                                             entry was found */
    found = FALSE;
    count = num;

    j = 0;
    /* Run loop till you've exhausted available resources */
    while (j + count < handle->numResources) {

        if (_match(handle, j, scratchId, alg)) {

            if (count == 0 ) {
                tax = tax - TAX(j-num) + TAX(j);
            }
            else {
                count--;
                tax += TAX(j);
            }

            if (count == 0) {

                /* Found some contiguous resources */
                found = TRUE;

                if ((0 == tax) || (scratchId == -1)) {
                    /* If tax is 0  or if these are persis. resources, this is
                       optimal, quit */
                    saveIndex = j - num + 1;
                    minTax = 0;
                    break;
                }

                if (minTax > tax) {
                    /* update the min tax and the index */
                    saveIndex = j - num + 1;
                    minTax = tax;
                }
            }
        }
        else {
            count = num;
            tax = 0;
        }

        j++;
    }

    /* Out of while loop, check if we found something */
    if (TRUE == found) {

        /* Now do the actual alloc from saveIndex */
        for (i = 0; i < num; i++) {
            _alloc(handle, saveIndex + i, scratchId, alg);
        }

        *resourceId = saveIndex;

        status = TRUE;

        RESMAXID = MAX((saveIndex + num - 1), RESMAXID);
    }
    else {
        status = FALSE;
    }

    return (status);
}

/*
 *  ======== SMGR_create ========
 */
SMGR_Handle SMGR_create(SMGR_Attrs *attrs)
{
    SMGR_Obj    *handle;
    Int         i;
    Int         segid;


    Assert_isTrue(attrs != NULL, (Assert_Id)NULL);
    Assert_isTrue(attrs->allocFxn != NULL, (Assert_Id)NULL);
    Assert_isTrue(attrs->freeFxn != NULL, (Assert_Id)NULL);

    segid = attrs->segid;

    /* Allocate SMGR object and also memory to hold the list of resources */
    /* TODO: Could replace this with an SHM_getObj (?) */
    handle = (SMGR_Obj *)(attrs->allocFxn)(segid, sizeof(SMGR_Obj) +
            (sizeof(SMGR_Counter) * attrs->numResources), sizeof(UInt32));

    if (handle != NULL) {

        handle->segid = attrs->segid;
        handle->allocFxn = attrs->allocFxn;
        handle->freeFxn = attrs->freeFxn;
        handle->numResources = attrs->numResources;
        handle->numGroups = attrs->numScratchGroups;
        RESMAXID = 0;

        /*
         * Initialize the array as required.
         */
        /*
        handle->resourceList = (SMGR_Counter *)((UInt32 )handle +
                sizeof(SMGR_Obj));
        */
        handle->resourceListOffset = (sizeof(SMGR_Obj));

        for (i = 0 ; i < attrs->numResources; i++) {
            RESSTAT(i) = SMGR_RESAVAILABLE;
            RESCOUNT(i) = 0;
            RESALG(i) = NULL;
        }
    }

    return (handle);
}

/*
 *  ======== SMGR_delete ========
 */
Void SMGR_delete(SMGR_Handle smgr)
{
    Assert_isTrue(smgr != NULL, (Assert_Id)NULL);

    (smgr->freeFxn)(smgr->segid, smgr, sizeof(SMGR_Obj) +
            (smgr->numResources * sizeof(SMGR_Counter)));
}

/*
 *  ======== SMGR_exit ========
 */
Void SMGR_exit(Void)
{
    if (--refCount == 0) {
    }
}

/*
 *  ======== SMGR_free ========
 */
/* ARGSUSED */
Bool SMGR_free(SMGR_Handle handle, IALG_Handle alg, Int resourceId, Int num,
        Int scratchId)
{
    Bool status = TRUE;
    Int i;
#ifdef DEBUG
    SMGR_Counter * res = (SMGR_Counter *)(RESLIST(resourceId));
#endif

    Assert_isTrue(handle != NULL, (Assert_Id)NULL);
    Assert_isTrue(resourceId < handle->numResources, (Assert_Id)NULL);
    Assert_isTrue(scratchId < handle->numGroups, (Assert_Id)NULL);


    /* Ensure resource being freed is actually owned by this scratch group */
    if (scratchId == -1) {
        for (i = 0 ; i < num; i++) {

            Assert_isTrue(((RESSTAT(resourceId + i) != SMGR_RESAVAILABLE)                     && (RESSTAT(resourceId + i) == scratchId)),
                    (Assert_Id)NULL);

            /* Persistent resources when freed are marked as available */
            RESSTAT(resourceId + i) = SMGR_RESAVAILABLE;
            RESCOUNT(resourceId + i)--;
            Assert_isTrue(RESCOUNT(resourceId + i) == 0, (Assert_Id)NULL);
        }
    }
    else {

        for ( i = 0 ; i < num; i++) {

            Assert_isTrue(((RESSTAT(resourceId + i) != SMGR_RESAVAILABLE)                     && (RESSTAT(resourceId + i) == scratchId)),
                    (Assert_Id)NULL);

            /* Decrement counter for scratch resources */
            RESCOUNT(resourceId + i)--;

            /* Last guy to use this resource, just freed it, shouldn't
               use that alg anymore to track the owner */
            RESALG(resourceId + i) = NULL;

            /* If count goes to zero, resource is marked available */
            if (0 == RESCOUNT(resourceId + i)) {
                RESSTAT(resourceId + i) = SMGR_RESAVAILABLE;
            }
        }
    }

    return (status);
}

/*
 *  ======== SMGR_init ========
 */
Void SMGR_init(Void)
{
    Registry_Result result;

    if (refCount++ == 0) {
        FCSettings_init();

        result = Registry_addModule(&ti_sdo_fc_utils_smgr_desc, SMGR_MODNAME);
        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the FC default */
            FCSettings_setDiags(SMGR_MODNAME);
        }
    }
}

/*
 *  ======== _match ========
 *  Function checks if the resourceId is available to scratchGroupId, and alg
 */
static inline Bool _match(SMGR_Handle handle, Int resourceId, Int scratchId,
        IALG_Handle alg)
{
    Bool status = TRUE;
#ifdef DEBUG
    SMGR_Counter * res = (SMGR_Counter *)(RESLIST(resourceId));
#endif

    /* Check if resource is free */
    if (SMGR_RESAVAILABLE != RESSTAT(resourceId)) {
        /* Needs to be available for -1 */
        if (scratchId == -1) {
            status = FALSE;
        }
        else {
            /* For scratch resources, should be available to the same group */
            if (!((scratchId == RESSTAT(resourceId))
                    &&(RESALG(resourceId) != alg))) {
                status = FALSE;
            }
        }
    }
    return (status);
}

/*
 *  ======== _alloc ========
 *  Allocates the resourceId to scratchId and alg
 *  Assumes this resource is free
 */
static inline Void _alloc(SMGR_Handle handle, Int resourceId, Int scratchId,
        IALG_Handle alg)
{
#ifdef DEBUG
    SMGR_Counter * res = (SMGR_Counter *)(RESLIST(resourceId));
#endif

    if ( SMGR_RESAVAILABLE == RESSTAT(resourceId) ) {

        /* Resource is free. Mark is busy */
        RESSTAT(resourceId) = ((scratchId == -1) ? SMGR_RESPERSISTENT:
                scratchId);
    }

    /* Scratch resources need to stow the alg that req. them */
    RESALG(resourceId) = alg;

    /* Increment counter */
    RESCOUNT(resourceId)++;
}
