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
 *  ======== ires_vicp.c ========
 */

/* This difine must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_fc_ires_vicp_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Registry.h>

#include "ires_vicp.h"
#include "iresman_protocol_vicp.h"
#include "_vicp.h"


extern unsigned int _VICP_imcopUmap1Base;
extern unsigned int _VICP_imcopConfigBase;

extern void IRES_VICP_getStaticProperties(IRES_Handle resourceHandle,
        IRES_Properties * resourceProperties);

extern Registry_Desc ti_sdo_fc_ires_vicp_desc;

/*
 * Register values  to return as properties of this resource
 */
__FAR__ static IRES_VICP_Registers _registers = {
    sizeof(IRES_VICP_Registers),
    0x0,
    0x0,
    IMGBUF_BASE   ,
    IMGBUF_A_FULL_BASE,
    IMGBUF_B_FULL_BASE,
    IMXCOEFFBUF_BASE,
    IMXCMDBUF_BASE ,
    VLCDDATA_BASE ,
    QIQBUF_BASE  ,
    VLCDBUF_BASE,
    SEQ_PMEM_BASE,
    SEQDATA_BASE  ,
    IMGBUF_SIZE     ,
    IMGBUF_A_SIZE  ,
    IMGBUF_B_SIZE ,
    IMXCOEFFBUF_SIZE,
    IMXCMDBUF_SIZE ,
    VLCDDATA_SIZE ,
    QIQBUF_SIZE  ,
    VLCDBUF_SIZE,
    SEQMEM_SIZE,
    SEQDATA_SIZE
};

__FAR__ static Int _registerInit = 0;

/**
 *  ======= IRES_VICP_getProtocolName =======
 *  Return the name of the protocol
 */
String IRES_VICP_getName()
{
        return IRES_VICP_PROTOCOLNAME;
}


/**
 *  ======= IRES_VICP_getRevision =======
 *  Return the revision of the protocol
 */
IRES_ProtocolRevision * IRES_VICP_getRevision ()
{
        return &IRES_VICP_PROTOCOLREVISION;
}

/**
 *  ======= IRES_VICP_getMemRecs =======
 *  Provide the memory requirements for allocating the Logical Resource
 *  handle.
 *
 *  The 'protocol' determines the size and attributes of the memory that
 *  represents the logical resource. The size must be at least the size of
 *  IRES_VICP_Obj.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_VICP_getMemRecs(IRES_Handle handle,
        IRES_ProtocolArgs * resProtocolArgs, IALG_MemRec *memRecs)
{

    Assert_isTrue(memRecs != NULL, (Assert_Id)NULL);
    Assert_isTrue(resProtocolArgs != NULL, (Assert_Id)NULL);

    memRecs[0].alignment = 4;
        memRecs[0].size = sizeof(IRES_VICP_Obj);

    /*
     * IALG_EXTERNAL because we don't care where this memory is allocated
     */
    memRecs[0].space = IALG_EXTERNAL;

    /*
     * Memory should be persistent.
     */
    memRecs[0].attrs = IALG_PERSIST;

    return IRES_OK; /* number of MemRecs */
}

/**
 *  ======= IRES_VICP_getNumMemRecs =======
 *  VICP protocol does not request any extra memory buffers.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int IRES_VICP_getNumMemRecs(IRES_ProtocolArgs * protArgs)
{
    return ((Int)1);
}

/**
 *  ======= IRES_VICP_constructHandle =======
 *  VICP Protocol specific initialization function to finalize the
 *  creation of a resource object (handle).
 *  The protocol::initHandle function can extend the IRES_VICP_Obj struct
 *  and must store any additional allocated 'environment' memory
 *  within the resource handle and return the IALG_MemRec descriptors
 *  in protocol::getEnvBuffDescriptors() function.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Handle IRES_VICP_constructHandle(
        IRES_ProtocolArgs * resProtocolArgs,
        IALG_MemRec *memRecs,
        IRESMAN_ConstructArgs * constructHandleArgs,
        IRES_Status *status)
{
    IRES_VICP_Handle handle = (IRES_VICP_Handle)memRecs[0].base;

    IRESMAN_VICP_ConstructHandleArgs * constructArgs =
        (IRESMAN_VICP_ConstructHandleArgs *)constructHandleArgs;

    Assert_isTrue(resProtocolArgs != NULL, (Assert_Id)NULL);
    Assert_isTrue(memRecs != NULL, (Assert_Id)NULL);
    Assert_isTrue(constructHandleArgs != NULL, (Assert_Id)NULL);
    Assert_isTrue(status != NULL, (Assert_Id)NULL);

    if (handle == NULL) {
        *status = IRES_ENORESOURCE;
        return (IRES_Handle) NULL;
    }

    ((IRES_VICP_Handle)handle)->ires.getStaticProperties =
            IRES_VICP_getStaticProperties;

    /*
     * Use the constructHandleargs to populate the ShadowPaRams with the
     * correct link
     */
    handle->assignedIMX = constructArgs->assignedIMX;
    handle->assignedVLCD = constructArgs->assignedVLCD;
    handle->assignedSEQ = constructArgs->assignedSEQ;

    (handle->ires).persistent = constructArgs->persistent;

    *status = IRES_OK;

    return (IRES_Handle)handle;
}

/**
 *  ======= IRES_VICP_getStaticProperties =======
 *  Returns the static properties of the particular resource
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
void IRES_VICP_getStaticProperties(IRES_Handle resourceHandle,
        IRES_Properties * resourceProperties)
{
    IRES_VICP_Properties * properties =
            (IRES_VICP_Properties *)resourceProperties;

    properties->size = sizeof(IRES_VICP_Properties);

    if (_registerInit == 0) {
        _registers.vicp_umap1_base = (unsigned char *)_VICP_imcopUmap1Base;
        _registers.vicp_cfg_base = (unsigned char *)_VICP_imcopConfigBase;
        _registers.imgBuf_base =  (unsigned char *)(IMGBUF_BASE +
                _VICP_imcopUmap1Base);
        _registers.imgBufA_base = (unsigned char *)(IMGBUF_A_FULL_BASE +
                _VICP_imcopUmap1Base);
        _registers.imgBufB_base = (unsigned char *)(IMGBUF_B_FULL_BASE +
                _VICP_imcopUmap1Base);
        _registers.imxCoeffBuff_base = (unsigned char *)(IMXCOEFFBUF_BASE +
                _VICP_imcopUmap1Base);
        _registers.imxCmdBuf_base = (unsigned char *)(IMXCMDBUF_BASE +
                _VICP_imcopUmap1Base);
        _registers.vlcdDataBuf_base = (unsigned char *)(VLCDDATA_BASE +
                _VICP_imcopUmap1Base);
        _registers.qiqBuf_base = (unsigned char *)(QIQBUF_BASE +
                _VICP_imcopUmap1Base);
        _registers.vlcdBuf_base = (unsigned char *)(VLCDBUF_BASE +
                _VICP_imcopUmap1Base);
        _registers.seqProgMem_base = (unsigned char *)(SEQ_PMEM_BASE +
                _VICP_imcopUmap1Base);
        _registers.seqDataMem_base = (unsigned char *)(SEQDATA_BASE +
                _VICP_imcopConfigBase);
        _registerInit = 1;
    }
    properties->globalRegs = (IRES_VICP_Registers *)&_registers;
}

/**
 *  ======= IRES_VICP_destructHandle =======
 *  De-initialize the env stored in the IRES_VICP channel handle, before
 *  it is freed by the resource manager.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_VICP_destructHandle(IRES_Handle handle)
{
    /*
     * Nothing allocated in this module
     * So nothing needs to be done.
     */
     return (IRES_OK);
}

IRESMAN_ConstructFxns IRESMAN_VICP_CONSTRUCTFXNS = {
    IRES_VICP_getName,
    IRES_VICP_getRevision,
    IRES_VICP_getMemRecs,
    IRES_VICP_getNumMemRecs,
    IRES_VICP_constructHandle,
    IRES_VICP_destructHandle
};
