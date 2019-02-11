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
 *  ======== ires_tiledmemory.c ========
 */

/* This difine must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_fc_ires_tiledmem_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include "ires_tiledmemory.h"
#include "iresman_protocol_tiledmemory.h"
#include "tiledmemory.h"
#include "_tiledmemory.h"

#ifdef xdc_target__os_Linux

#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#endif


extern TILEDMEMORY_Params TILEDMEMORY_PARAMS;

extern void IRES_TILEDMEMORY_getStaticProperties(IRES_Handle resourceHandle,
        IRES_Properties * resourceProperties);


extern Registry_Desc ti_sdo_fc_ires_tiledmem_desc;

/**
 *  ======= IRES_TILEDMEMORY_getProtocolName =======
 *  Return the name of the protocol
 */
String IRES_TILEDMEMORY_getName()
{
    /*
    Log_print0(Diags_ENTRY, "[+E] IRES_TILEDMEMORY_getName> Enter");

    Log_print1(Diags_EXIT, "[+X] IRES_TILEDMEMORY_getName> Exit (Name=%s)",
            (IArg)IRES_TILEDMEMORY_PROTOCOLNAME);
    */

    return (IRES_TILEDMEMORY_PROTOCOLNAME);
}

/**
 *  ======= IRES_TILEDMEMORY_getRevision =======
 *  Return the revision of the protocol
 */
IRES_ProtocolRevision * IRES_TILEDMEMORY_getRevision()
{
    /*
    Log_print0(Diags_ENTRY, "[+E] IRES_TILEDMEMORY_getRevision> Enter");

    Log_print3(Diags_EXIT, "[+X] IRES_TILEDMEMORY_getRevision>"
            "Exit (Version=(%d.%d.%d))",
            (IArg)(IRES_TILEDMEMORY_PROTOCOLREVISION.Major),
            (IArg)(IRES_TILEDMEMORY_PROTOCOLREVISION.Source),
            (IArg)(IRES_TILEDMEMORY_PROTOCOLREVISION.Radius));
    */

    return (&IRES_TILEDMEMORY_PROTOCOLREVISION);
}

/**
 *  ======= IRES_TILEDMEMORY_getMemRecs =======
 *  Provide the memory requirements for allocating the Logical Resource
 *  handle.
 *
 *  The 'protocol' determines the size and attributes of the memory that
 *  represents the logical resource. The size must be at least the size of
 *  IRES_TILEDMEMORY_Obj.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_TILEDMEMORY_getMemRecs(IRES_Handle handle,
        IRES_ProtocolArgs * resProtocolArgs, IALG_MemRec *memRecs)
{

    Assert_isTrue(memRecs != NULL, (Assert_Id)NULL);
    Assert_isTrue(resProtocolArgs != NULL, (Assert_Id)NULL);

    Log_print3(Diags_ENTRY,
            "[+E] IRES_TILEDMEMORY_getMemRecs> Enter (handle=0x%x, "
            "resProtocolArgs=0x%x, memRecs=0x%x)",
            (IArg)handle, (IArg)resProtocolArgs, (IArg)memRecs);

    memRecs[0].alignment = 4;
    memRecs[0].size = sizeof(IRES_TILEDMEMORY_IntObj);

    /*
     * IALG_EXTERNAL because we don't care where this memory is allocated
     */
    memRecs[0].space = IALG_EXTERNAL;

    /*
     * Memory should be persistent.
     */
    memRecs[0].attrs = IALG_PERSIST;

    Log_print2(Diags_USER4,
            "[+4] IRES_TILEDMEMORY_getMemRecs> Amount of memory requested 0x%x, "
            "alignment 0x%x, space IALG_EXTERNAL attrs IALG_PERSIST",
            (IArg)(memRecs[0].size), (IArg)(memRecs[0].alignment));

    Log_print0(Diags_EXIT,
            "[+X] IRES_TILEDMEMORY_getMemRecs> Exit (status=IRES_EOK)");

    return (IRES_OK); /* number of MemRecs */
}

/**
 *  ======= IRES_TILEDMEMORY_getNumMemRecs =======
 *  TILEDMEMORY protocol does not request any extra memory buffers.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int IRES_TILEDMEMORY_getNumMemRecs(IRES_ProtocolArgs * protArgs)
{
    Log_print1(Diags_ENTRY,
            "[+E] IRES_TILEDMEMORY_getNumMemRecs> Enter (protArgs=0x%x)",
            (IArg)protArgs);

    Log_print0(Diags_EXIT, "[+X] IRES_TILEDMEMORY_getNumMemRecs> Exit (Num=1)");

    return ((Int)1);
}

/**
 *  ======= IRES_TILEDMEMORY_constructHandle =======
 *  TILEDMEMORY Protocol specific initialization function to finalize the
 *  creation of a resource object (handle).
 *  The protocol::initHandle function can extend the IRES_TILEDMEMORY_Obj struct
 *  and must store any additional allocated 'environment' memory
 *  within the resource handle and return the IALG_MemRec descriptors
 *  in protocol::getEnvBuffDescriptors() function.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Handle IRES_TILEDMEMORY_constructHandle(
        IRES_ProtocolArgs * resProtocolArgs,
        IALG_MemRec *memRecs,
        IRESMAN_ConstructArgs * constructHandleArgs,
        IRES_Status *status)
{
    IRES_TILEDMEMORY_Handle handle = (IRES_TILEDMEMORY_Handle)memRecs[0].base;

    IRESMAN_TILEDMEMORY_ConstructHandleArgs * constructArgs =
        (IRESMAN_TILEDMEMORY_ConstructHandleArgs *)constructHandleArgs;


    Assert_isTrue(resProtocolArgs != NULL, (Assert_Id)NULL);
    Assert_isTrue(memRecs != NULL, (Assert_Id)NULL);
    Assert_isTrue(constructHandleArgs != NULL, (Assert_Id)NULL);
    Assert_isTrue(status != NULL, (Assert_Id)NULL);

    Log_print3(Diags_ENTRY,
            "[+E] IRES_TILEDMEMORY_constructHandle> Enter (protArgs=0x%x,"
            "memRecs=0x%x, constructHandleArgs=0x%x)",
            (IArg)resProtocolArgs, (IArg)memRecs, (IArg)constructHandleArgs);

    if (handle == NULL) {

        *status = IRES_ENORESOURCE;

        Log_print0(Diags_USER7,
                "[+7] IRES_TILEDMEMORY_constructHandle> NULL handle returned"
                "through memRecs");

        Log_print0(Diags_EXIT,
                "[+X] IRES_TILEDMEMORY_constructHandle> Exit (handle=NULL)");

        return ((IRES_Handle)NULL);
    }

    (handle->ires).getStaticProperties = IRES_TILEDMEMORY_getStaticProperties;

    /*
     * Use the constructHandleargs to populate the handle withi the correct
     * memoryBaseAddress
     */
    (handle->ires).persistent = constructArgs->persistent;
    handle->memoryBaseAddress = constructArgs->memBaseAddr;
    handle->systemSpaceBaseAddress = constructArgs->systemSpaceBaseAddress;
    handle->isTiledMemory = constructArgs->isTiledMemory;
    handle->accessUnit = constructArgs->unit;
    handle->tilerBaseAddress = constructArgs->tilerBaseAddr;

    ((IRES_TILEDMEMORY_IntObj *)handle)->sizeTiledMemory =
            constructArgs->sizeTiledMemory;

    *status = IRES_OK;

    Log_print2(Diags_EXIT,
            "[+X] IRES_TILEDMEMORY_constructHandle> Exit (status=%d, "
            "handle=0x%x)\n", (IArg)(*status), (IArg)handle);

    return ((IRES_Handle)handle);
}

/**
 *  ======= IRES_TILEDMEMORY_getStaticProperties =======
 *  Returns the static properties of the particular resource
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
void IRES_TILEDMEMORY_getStaticProperties(IRES_Handle resourceHandle,
        IRES_Properties * resourceProperties)
{
    Log_print2(Diags_ENTRY,
            "[+E] IRES_TILEDMEMORY_getStaticProperties> Enter (resourceHandle=0x%x, "
            "resourceProperties=0x%x)",
            (IArg)resourceHandle, (IArg)resourceProperties);
    Log_print0(Diags_EXIT, "[+X] IRES_TILEDMEMORY_getStaticProperties> Exit");
}

/**
 *  ======= IRES_TILEDMEMORY_destructHandle =======
 *  De-initialize the env stored in the IRES_TILEDMEMORY channel handle, before
 *  it is freed by the resource manager.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_TILEDMEMORY_destructHandle(IRES_Handle handle)
{
    Log_print0(Diags_ENTRY, "[+E] IRES_TILEDMEMORY_destructHandle> Enter");
    /*
     * Nothing allocated in this module
     * So nothing needs to be done.
     */
    Log_print0(Diags_EXIT,
            "[+X] IRES_TILEDMEMORY_destructHandle> Exit (returnVal=IRES_OK)");

    return (IRES_OK);
}

IRESMAN_ConstructFxns IRESMAN_TILEDMEMORY_CONSTRUCTFXNS = {
    IRES_TILEDMEMORY_getName,
    IRES_TILEDMEMORY_getRevision,
    IRES_TILEDMEMORY_getMemRecs,
    IRES_TILEDMEMORY_getNumMemRecs,
    IRES_TILEDMEMORY_constructHandle,
    IRES_TILEDMEMORY_destructHandle
};
