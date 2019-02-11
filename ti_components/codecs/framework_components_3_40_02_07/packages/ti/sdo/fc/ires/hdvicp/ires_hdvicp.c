/*
 * Copyright (c) 2012-2013, Texas Instruments Incorporated
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
 *  ======== ires_hdvicp.c ========
 */

/* This difine must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_fc_ires_hdvicp_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>

#include <xdc/runtime/Registry.h>

#include "ires_hdvicp.h"
#include "iresman_protocol_hdvicp.h"
#include "_hdvicp.h"

#ifdef xdc_target__os_Linux

#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
__FAR__ static int memfd = -1;           /* File descriptor for "/dev/mem"  */
#endif

extern unsigned int _HDVICP_REGBASEADDR;
extern unsigned int _HDVICP_MEMBASEADDR;

#define _HDVICP_SYSSIZE 0x00200000


extern void IRES_HDVICP_getStaticProperties(IRES_Handle resourceHandle,
        IRES_Properties * resourceProperties);

extern Registry_Desc ti_sdo_fc_ires_hdvicp_desc;

/**
 *  ======= IRES_HDVICP_getProtocolName =======
 *  Return the name of the protocol
 */
String IRES_HDVICP_getName()
{

    /*
    Log_print0(Diags_ENTRY, "[+E] IRES_HDVICP_getName> Enter");

    Log_print1(Diags_EXIT, "[+X] IRES_HDVICP_getName> Exit (Name=%s)",
            (IArg)IRES_HDVICP_PROTOCOLNAME);
    */

    return (IRES_HDVICP_PROTOCOLNAME);
}

/**
 *  ======= IRES_HDVICP_getRevision =======
 *  Return the revision of the protocol
 */
IRES_ProtocolRevision * IRES_HDVICP_getRevision()
{
    /*
    Log_print0(Diags_ENTRY, "[+E] IRES_HDVICP_getRevision>"            " Enter");

    Log_print3(Diags_EXIT, "[+X] IRES_HDVICP_getRevision>"
            "Exit (Version=(%d.%d.%d))",
            (IArg)(IRES_HDVICP_PROTOCOLREVISION.Major),
            (IArg)(IRES_HDVICP_PROTOCOLREVISION.Source),
            (IArg)(IRES_HDVICP_PROTOCOLREVISION.Radius));
    */

    return (&IRES_HDVICP_PROTOCOLREVISION);
}

/**
 *  ======= IRES_HDVICP_getMemRecs =======
 *  Provide the memory requirements for allocating the Logical Resource
 *  handle.
 *
 *  The 'protocol' determines the size and attributes of the memory that
 *  represents the logical resource. The size must be at least the size of
 *  IRES_HDVICP_Obj.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_HDVICP_getMemRecs(IRES_Handle handle,
        IRES_ProtocolArgs * resProtocolArgs, IALG_MemRec *memRecs)
{
    Assert_isTrue(memRecs != NULL, (Assert_Id)NULL);
    Assert_isTrue(resProtocolArgs != NULL, (Assert_Id)NULL);

    Log_print3(Diags_ENTRY,
            "[+E] IRES_HDVICP_getMemRecs> Enter (handle=0x%x, "
            "resProtocolArgs=0x%x, memRecs=0x%x)",
            (IArg)handle, (IArg)resProtocolArgs, (IArg)memRecs);

    memRecs[0].alignment = 4;
    memRecs[0].size = sizeof(IRES_HDVICP_Obj);

    /*
     * IALG_EXTERNAL because we don't care where this memory is allocated
     */
    memRecs[0].space = IALG_EXTERNAL;

    /*
     * Memory should be persistent.
     */
    memRecs[0].attrs = IALG_PERSIST;

    Log_print2(Diags_USER4,
            "[+4] IRES_HDVICP_getMemRecs> Amount of memory requested 0x%x, "
            "alignment 0x%x, space IALG_EXTERNAL attrs IALG_PERSIST",
            (IArg)(memRecs[0].size), (IArg)(memRecs[0].alignment));

    Log_print0(Diags_EXIT,
            "[+X] IRES_HDVICP_getMemRecs> Exit (status=IRES_EOK)");

    return (IRES_OK); /* number of MemRecs */
}

/**
 *  ======= IRES_HDVICP_getNumMemRecs =======
 *  HDVICP protocol does not request any extra memory buffers.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int IRES_HDVICP_getNumMemRecs(IRES_ProtocolArgs * protArgs)
{
    Log_print1(Diags_ENTRY,
            "[+E] IRES_HDVICP_getNumMemRecs> Enter (protArgs=0x%x)",
            (IArg)protArgs);

    Log_print0(Diags_EXIT, "[+X] IRES_HDVICP_getNumMemRecs> Exit (Num=1)");

    return ((Int)1);
}

/**
 *  ======= IRES_HDVICP_constructHandle =======
 *  HDVICP Protocol specific initialization function to finalize the
 *  creation of a resource object (handle).
 *  The protocol::initHandle function can extend the IRES_HDVICP_Obj struct
 *  and must store any additional allocated 'environment' memory
 *  within the resource handle and return the IALG_MemRec descriptors
 *  in protocol::getEnvBuffDescriptors() function.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Handle IRES_HDVICP_constructHandle(
        IRES_ProtocolArgs * resProtocolArgs,
        IALG_MemRec *memRecs,
        IRESMAN_ConstructArgs * constructHandleArgs,
        IRES_Status *status)
{
    void * memoryBaseAddress = NULL;
    void * registerBaseAddress = NULL;
    unsigned int pscBaseAddress = 0x0;

    IRES_HDVICP_Handle handle = (IRES_HDVICP_Handle)memRecs[0].base;

    IRESMAN_HDVICP_ConstructHandleArgs * constructArgs =
        (IRESMAN_HDVICP_ConstructHandleArgs *)constructHandleArgs;

    Assert_isTrue(resProtocolArgs != NULL, (Assert_Id)NULL);
    Assert_isTrue(memRecs != NULL, (Assert_Id)NULL);
    Assert_isTrue(constructHandleArgs != NULL, (Assert_Id)NULL);
    Assert_isTrue(status != NULL, (Assert_Id)NULL);

    Log_print3(Diags_ENTRY,
            "[+E] IRES_HDVICP_constructHandle> Enter (protArgs=0x%x, "
            "memRecs=0x%x, constructHandleArgs=0x%x)",
            (IArg)resProtocolArgs, (IArg)memRecs, (IArg)constructHandleArgs);

    if (handle == NULL) {

        *status = IRES_ENORESOURCE;

        Log_print0(Diags_USER7,
                "[+7] IRES_HDVICP_constructHandle> NULL handle returned "
                "through memRecs");

        Log_print0(Diags_EXIT,
                "[+X] IRES_HDVICP_constructHandle> Exit (handle=NULL)");

        return ((IRES_Handle)NULL);
    }

    (handle->ires).getStaticProperties = IRES_HDVICP_getStaticProperties;

    /*
     * Use the constructHandleargs to populate the handle withi the correct
     * id
     */
    handle->id = constructArgs->id;
    (handle->ires).persistent = constructArgs->persistent;

#ifdef xdc_target__os_Linux
    memfd = open("/dev/mem", O_RDWR | O_SYNC);
    if (-1 == memfd) {
        *status = IRES_EFAIL;
        return (NULL);
    }

    registerBaseAddress =
            (void *)mmap(0, _HDVICP_SYSSIZE, PROT_READ | PROT_WRITE,
            MAP_SHARED, memfd, (off_t)_HDVICP_REGBASEADDR);

    if (-1 == (unsigned int)registerBaseAddress) {
        *status = IRES_EFAIL;
        return (NULL);
    }

        pscBaseAddress =
            (unsigned int)mmap(0, _HDVICP_PSCSIZE,
            PROT_READ | PROT_WRITE, MAP_SHARED, memfd,
            (off_t)_HDVICP_PSCBASE);

    if (-1 == pscBaseAddress) {
           *status = IRES_EFAIL;
            return (NULL);
    }
#else
    registerBaseAddress = (void *)_HDVICP_REGBASEADDR;
#ifdef xdc_target__isaCompatible_64P

        /* Invalid field for C64P devices */
        pscBaseAddress = 0xFFFFFFFF;
#else
        pscBaseAddress = (unsigned int)_HDVICP_PSCBASE;
#endif
#endif

    handle->registerBaseAddress = registerBaseAddress;
    handle->pscRegisterSpace = pscBaseAddress;

    if (NULL == memoryBaseAddress) {

#ifdef xdc_target__os_Linux
        memoryBaseAddress = registerBaseAddress +
                (_HDVICP_MEMBASEADDR - _HDVICP_REGBASEADDR);
#else
        memoryBaseAddress = (void *)_HDVICP_MEMBASEADDR;
#endif
    }

    handle->memoryBaseAddress = memoryBaseAddress;

    *status = IRES_OK;

    Log_print2(Diags_EXIT,
            "[+X] IRES_HDVICP_constructHandle> Exit (status=%d, handle=0x%x)",
            (IArg)(*status), (IArg)handle);

    return ((IRES_Handle)handle);
}

/**
 *  ======= IRES_HDVICP_getStaticProperties =======
 *  Returns the static properties of the particular resource
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
void IRES_HDVICP_getStaticProperties(IRES_Handle resourceHandle,
        IRES_Properties * resourceProperties)
{
    Log_print2(Diags_ENTRY,
            "[+E] IRES_HDVICP_getStaticProperties> Enter (resourceHandle=0x%x, "
            "resourceProperties=0x%x)",
            (IArg)resourceHandle, (IArg)resourceProperties);

#ifndef xdc_target__isaCompatible_64P
    ((IRES_HDVICP_Properties *)resourceProperties)->globalRegs =
            (IRES_HDVICP_RegisterLayer *)
            (((IRES_HDVICP_Handle)resourceHandle)->registerBaseAddress);
#endif

    Log_print0(Diags_EXIT, "[+X] IRES_HDVICP_getStaticProperties> Exit");
}

/**
 *  ======= IRES_HDVICP_destructHandle =======
 *  De-initialize the env stored in the IRES_HDVICP channel handle, before
 *  it is freed by the resource manager.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_HDVICP_destructHandle(IRES_Handle handle)
{
    Log_print0(Diags_ENTRY, "[+E] IRES_HDVICP_destructHandle> Enter");

    /*
     * Nothing allocated in this module
     * So nothing needs to be done.
     */
    Log_print0(Diags_EXIT,
            "[+X] IRES_HDVICP_destructHandle> Exit (returnVal=IRES_OK)");

    return (IRES_OK);
}

IRESMAN_ConstructFxns IRESMAN_HDVICP_CONSTRUCTFXNS = {
    IRES_HDVICP_getName,
    IRES_HDVICP_getRevision,
    IRES_HDVICP_getMemRecs,
    IRES_HDVICP_getNumMemRecs,
    IRES_HDVICP_constructHandle,
    IRES_HDVICP_destructHandle
};
