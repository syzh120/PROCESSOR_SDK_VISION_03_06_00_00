/*
 * Copyright (c) 2011-2014, Texas Instruments Incorporated
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
 *  ======== Resource.c ========
 *
 */

#include <xdc/runtime/System.h>
#include <xdc/runtime/Startup.h>
#include <ti/sysbios/hal/Cache.h>

#include "rsc_types.h"
#include "package/internal/Resource.xdc.h"


/*
 *  ======== Resource_getTraceBufPtr ========
 */
Ptr Resource_getTraceBufPtr()
{
    UInt32 i;
    UInt32 offset;
    UInt32 type;
    struct fw_rsc_trace *entry = NULL;
    Resource_RscTable *table = (Resource_RscTable *)
                                            (Resource_module->pTable);

    for (i = 0; i < module->pTable->num; i++) {
        offset = (UInt32)((Char *)table + table->offset[i]);
        type = *(UInt32 *)offset;
        if (type == TYPE_TRACE) {
            entry = (struct fw_rsc_trace *)offset;
            return ((Ptr)entry->da);
        }
    }

    return (NULL);
}

/*
 *  ======== getVdevStatus ========
 */
Char Resource_getVdevStatus(UInt32 id)
{
    UInt32 i;
    UInt32 offset;
    UInt32 type;
    Char status = 0;
    struct fw_rsc_vdev *vdev= NULL;
    Resource_RscTable *table = (Resource_RscTable *)
                                            (Resource_module->pTable);

    for (i = 0; i < module->pTable->num; i++) {
        offset = (UInt32)((Char *)table + table->offset[i]);
        type = *(UInt32 *)offset;
        if (type == TYPE_VDEV) {
            vdev = (struct fw_rsc_vdev *)offset;
            if (vdev->id == id) {
                /* invalidate memory as host will update the status field */
                Cache_inv(vdev, sizeof(*vdev), Cache_Type_ALL, TRUE);
                status = vdev->status;
                break;
            }
        }
    }

    return (status);
}

/*
 *  ======== Resource_getVringDA ========
 */
Ptr Resource_getVringDA(UInt32 vqId)
{
    UInt32 i;
    UInt32 offset;
    UInt32 type;
    Ptr	   da = NULL;
    struct fw_rsc_vdev *vdev= NULL;
    Resource_RscTable *table = (Resource_RscTable *)
                                            (Resource_module->pTable);

    for (i = 0; i < module->pTable->num; i++) {
        offset = (UInt32)((Char *)table + table->offset[i]);
        type = *(UInt32 *)offset;
        if (type == TYPE_VDEV) {
            vdev = (struct fw_rsc_vdev *)offset;
            /* Ensure vqID is within expected number of vrings: */
            if (vqId < vdev->num_of_vrings) {
                da = (Ptr)(((struct fw_rsc_vdev_vring *)
                            (offset + sizeof(*vdev) +
                            vqId * sizeof(struct fw_rsc_vdev_vring)))->da);
            }
            else {
                break;   /* Not found.  da is NULL */
            }
        }
    }

    return (da);
}

/*
 *  ======== Resource_getMemEntry ========
 */
Resource_MemEntry *Resource_getMemEntry(UInt index)
{
    UInt32 offset;
    UInt32 *type;
    Resource_MemEntry *entry = NULL;
    Resource_RscTable *table = (Resource_RscTable *)
                                            (Resource_module->pTable);

    if (index >= table->num) {
        return (NULL);
    }

    offset = (UInt32)((Char *)table + table->offset[index]);
    type = (UInt32 *)offset;
    if (*type == TYPE_CARVEOUT || *type == TYPE_DEVMEM) {
        entry = (Resource_MemEntry *) ((Char *)offset);
    }

    return (entry);
}

/*
 *************************************************************************
 *                      Module wide functions
 *************************************************************************
 */

/*
 *  ======== Resource_Module_startup ========
 */
Int Resource_Module_startup(Int phase)
{
    Resource_init();
    return (Startup_DONE);
}

/*
 *  ======== Resource_virtToPhys ========
 */
Int Resource_virtToPhys(UInt32 va, UInt32 *pa)
{
    UInt32 i;
    UInt32 offset;
    Resource_MemEntry *entry;

    *pa = 0;

    for (i = 0; i < module->pTable->num; i++) {
        entry = Resource_getMemEntry(i);
        if (entry && va >= entry->da && va < (entry->da + entry->len)) {
                offset = va - entry->da;
                *pa = entry->pa + offset;
                return (Resource_S_SUCCESS);
        }
    }

    return (Resource_E_NOTFOUND);
}

/*
 *  ======== Resource_physToVirt ========
 */
Int Resource_physToVirt(UInt32 pa, UInt32 *va)
{
    UInt32 i;
    UInt32 offset;
    Resource_MemEntry *entry;

    *va = 0;

    for (i = 0; i < module->pTable->num; i++) {
        entry = Resource_getMemEntry(i);
        if (entry && pa >= entry->pa && pa < (entry->pa + entry->len)) {
                offset = pa - entry->pa;
                *va = entry->da + offset;
                return (Resource_S_SUCCESS);
        }
    }

    return (Resource_E_NOTFOUND);
}
