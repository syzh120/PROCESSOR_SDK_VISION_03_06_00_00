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
 *  ======== ires_edma3Chan.c ========
 *  Implementation of the IRESMAN_ConstructFxns interface used to construct
 *  EDMA3 handles.
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_fc_ires_edma3chan_desc


#include <xdc/std.h>

#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <ti/sdo/fc/ires/iresman_protocol.h>
#include "ires_edma3Chan.h"
#include "iresman_protocol_edma3Chan.h"
#include "_edma3Chan.h"

extern Registry_Desc ti_sdo_fc_ires_edma3chan_desc;

extern void IRES_EDMA3CHAN_getStaticProperties(IRES_Handle resourceHandle,
        IRES_Properties * resourceProperties);

/*
 * Holds the internal state of the protocol
 */
__FAR__ static IRES_EDMA3CHAN_InternalState internalState;

/**
 *  ======= IRES_EDMA3CHAN_getName =======
 *  Return the name of the protocol
 */
String IRES_EDMA3CHAN_getName()
{
    /*
    Log_print0(Diags_ENTRY, "[+E] IRES_EDMA3CHAN_getName> Enter");

    Log_print1(Diags_EXIT, "[+X] IRES_EDMA3CHAN_getName> Exit (Name=%s)",
            (IArg)IRES_EDMA3CHAN_PROTOCOLNAME);
    */

        return (IRES_EDMA3CHAN_PROTOCOLNAME);
}


/**
 *  ======= IRES_EDMA3CHAN_getRevision =======
 *  Return the revision of the protocol
 */
IRES_ProtocolRevision * IRES_EDMA3CHAN_getRevision ()
{
    /*
     * Holds the current version of the protocol revision
     */
    __FAR__ static IRES_ProtocolRevision _CurrentProtocolRevision = {2, 0, 0};

    /*
    Log_print0(Diags_ENTRY, "[+E] IRES_EDMA3CHAN_getRevision> Enter");

    Log_print3(Diags_EXIT,
            "[+X] IRES_EDMA3CHAN_getRevision> Exit (Version=(%d.%d.%d))",
            (IArg)(IRES_EDMA3CHAN_PROTOCOLREVISION.Major),
            (IArg)(IRES_EDMA3CHAN_PROTOCOLREVISION.Source),
            (IArg)(IRES_EDMA3CHAN_PROTOCOLREVISION.Radius));
    */

    return (&_CurrentProtocolRevision);
}

/**
 *  ======= IRES_EDMA3CHAN_getMemRecs =======
 *  Provide the memory requirements for allocating the Logical Resource
 *  handle.
 *
 *  The 'protocol' determines the size and attributes of the memory that
 *  represents the logical resource. The size must be at least the size of
 *  IRES_EDMA3CHAN2_Obj.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_EDMA3CHAN_getMemRecs(IRES_Handle handle,
        IRES_ProtocolArgs * resProtocolArgs, IALG_MemRec *memRecs)
{
    int size;
    int numPaRams;
    int numTccs;

    IRES_EDMA3CHAN_ProtocolArgs * protocolArgs =
            (IRES_EDMA3CHAN_ProtocolArgs *)resProtocolArgs;

    Assert_isTrue(memRecs != NULL, (Assert_Id)NULL);
    Assert_isTrue(resProtocolArgs != NULL, (Assert_Id)NULL);

    Log_print3(Diags_ENTRY,
            "[+E] IRES_EDMA3CHAN_getMemRecs> Enter (handle=0x%x, "
            "resProtocolArgs=0x%x, memRecs=0x%x)",
            (IArg)handle, (IArg)resProtocolArgs, (IArg)memRecs);

    /* Calculate size based on the number of params requested use protocolArgs
     * from the resourceDescriptor */
    numPaRams = protocolArgs->numPaRams;
    numTccs = protocolArgs->numTccs;

    /*
     * Amount of memory required is basically size of the paRamArray and size
     * of the shadow params (if requested), the tcc Array,
     * param Addresses plus the size of IRES_EDMA3CHAN2_OBJ
     */
    if (protocolArgs->shadowPaRamsAllocation) {
        size = numPaRams * (sizeof(short) + sizeof(IRES_EDMA3CHAN_PaRamStruct)
                + sizeof(unsigned int));
    }
    else {
        size = numPaRams * ( sizeof(short) + sizeof(unsigned int));
    }
    size += numTccs * ( sizeof(short));
    size += sizeof(IRES_EDMA3CHAN2_Obj);

    memRecs[0].size = size;

    memRecs[0].alignment = 4;

    /*
     * IALG_EXTERNAL because we don't care where this memory is allocated
     */
    memRecs[0].space = IALG_EXTERNAL;

    /*
     * Memory should be persistent.
     */
    memRecs[0].attrs = IALG_PERSIST;

    Log_print2(Diags_USER4,
            "[+4] IRES_EDMA3CHAN_getMemRecs> Amount of memory requested 0x%x, "
            "alignment 0x%x, space IALG_EXTERNAL attrs IALG_PERSIST",
            (IArg)(memRecs[0].size), (IArg)(memRecs[0].alignment));


    Log_print0(Diags_EXIT,
            "[+X] IRES_EDMA3CHAN_getMemRecs> Exit (status=IRES_EOK)");

    return (IRES_OK); /* number of MemRecs */
}

/**
 *  ======= IRES_EDMA3CHAN_getNumMemRecs =======
 *  EDMA3CHAN protocol does not request any extra memory buffers.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int IRES_EDMA3CHAN_getNumMemRecs(IRES_ProtocolArgs * protArgs)
{
    Log_print1(Diags_ENTRY,
            "[+E] IRES_EDMA3CHAN_getNumMemRecs> Enter (protArgs=0x%x)",
            (IArg)protArgs);

    Log_print0(Diags_EXIT, "[+X] IRES_EDMA3CHAN_getNumMemRecs> Exit (Num=1)");

    return (1);
}

/**
 *  ======= IRES_EDMA3CHAN_constructHandle =======
 *  EDMA3CHAN Protocol specific initialization function to finalize the
 *  creation of a resource object (handle).
 *  The protocol::initHandle function can extend the IRES_EDMA3CHAN2_Obj struct
 *  and must store any additional allocated 'environment' memory
 *  within the resource handle and return the IALG_MemRec descriptors
 *  in protocol::getEnvBuffDescriptors() function.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Handle IRES_EDMA3CHAN_constructHandle(
        IRES_ProtocolArgs * resProtocolArgs,
        IALG_MemRec *memRecs,
        IRESMAN_ConstructArgs * constructHandleArgs,
        IRES_Status *status)
{
    int numPaRams = 0;
    int numTccs = 0;
    int i = 0;
    IRES_EDMA3CHAN_PaRamStruct * shadowPaRamsPtr = 0x0;
    unsigned int * paRamAddressPtr = 0x0;
    short * paRamIndexPtr = 0x0;
    short * tccIndexPtr = 0x0;
    short * actualPaRamIndex = 0x0;
    short edmaChannel;
    unsigned int paRamBase;
    IRES_EDMA3CHAN2_Handle handle = (IRES_EDMA3CHAN2_Handle)memRecs[0].base;

    IRESMAN_EDMA3CHAN_ConstructHandleArgs * constructArgs =
        (IRESMAN_EDMA3CHAN_ConstructHandleArgs *)constructHandleArgs;
    Bool shadow = ((IRES_EDMA3CHAN_ProtocolArgs *)resProtocolArgs)
            ->shadowPaRamsAllocation;

    Assert_isTrue(resProtocolArgs != NULL, (Assert_Id)NULL);
    Assert_isTrue(memRecs != NULL, (Assert_Id)NULL);
    Assert_isTrue(constructHandleArgs != NULL, (Assert_Id)NULL);
    Assert_isTrue(status != NULL, (Assert_Id)NULL);


    Log_print3(Diags_ENTRY,
            "[+E] IRES_EDMA3CHAN_constructHandle> Enter (protArgs=0x%x, "
            "memRecs=0x%x, constructHandleArgs=0x%x)",
            (IArg)resProtocolArgs, (IArg)memRecs, (IArg)constructHandleArgs);

    if (handle == NULL) {

        *status = IRES_ENORESOURCE;

        Log_print0(Diags_USER7,
                "[+7] IRES_EDMA3CHAN_constructHandle> NULL handle returned through "
                "memRecs");

        Log_print0(Diags_EXIT,
                "[+X] IRES_EDMA3CHAN_constructHandle> Exit (handle=NULL)");

        return ((IRES_Handle)NULL);
    }

    /*
     * Assign the proper IRES_Obj properties to the handle first
     */
    (handle->ires).getStaticProperties = IRES_EDMA3CHAN_getStaticProperties;
    (handle->ires).persistent = TRUE;

    internalState.edma3BaseAddress = constructArgs->edma3CCBaseAddress;

    paRamBase = internalState.edma3BaseAddress + IRES_EDMA3CHAN_PARAMBASEOFFSET;

    actualPaRamIndex = constructArgs->paRamIndex;

    numPaRams = constructArgs->numPaRams;

    numTccs = constructArgs->numTccs;

    /*
     * Point the shadowPaRamsPtr to the address of space allocated for
     * shadow params .
     * The space gets allocated immediately following the IRES_EDMA3CHAN2_Obj
     * structure. The initialization of the shadow, param and tcc arrays
     * remains compatible for both revs 1 and  2 of the IRES EDMA3CHAN protocol
     */
    shadowPaRamsPtr = (IRES_EDMA3CHAN_PaRamStruct *)((UInt8 *)handle +
            sizeof(IRES_EDMA3CHAN2_Obj));

    /*
     * Point the paRamAddress pointer to the address of space allocated in
     * param addresses
     */
    if (shadow) {
        paRamAddressPtr = (unsigned int *)((UInt8 *)shadowPaRamsPtr +
                (numPaRams * sizeof(IRES_EDMA3CHAN_PaRamStruct)));
    }
    else {
        paRamAddressPtr =  (unsigned int *)shadowPaRamsPtr;
                shadowPaRamsPtr = NULL;
    }
    /*
     * Point the paRamIndexPtr to the address of space allocated for
     * paRam indices.
     */
    paRamIndexPtr = (short *)((UInt8 *)paRamAddressPtr + (numPaRams *
            sizeof(unsigned int)));

    tccIndexPtr = (short *)((UInt8 *)paRamIndexPtr + (numPaRams *
            sizeof(unsigned short)));

    edmaChannel = constructArgs->edma3Chan;

    /*
     * Use the constructHandleargs to populate the TCC index array
     */
    for (i = 0; i < numTccs; i++) {
        tccIndexPtr[i] = constructArgs->tccIndex[i];
    }

    /*
     * Use the constructHandleargs to populate the ShadowPaRams with the
     * correct link
     */
    if (numPaRams != 0) {

        paRamAddressPtr[0] = paRamBase + ((unsigned int)actualPaRamIndex[0] *
                sizeof(IRES_EDMA3CHAN_PaRamStruct));

        paRamIndexPtr[0] = actualPaRamIndex[0];

        Log_print6(Diags_USER2,
                "[+2] IRES_EDMA3CHAN_constructHandle> Address of handle 0x%x, "
                "paRamIndices 0x%x, paRamAddresses 0x%x, shadowParams 0x%x,"
                " tccIndices 0x%x, edmaChannel %d",
                (IArg)handle, (IArg)paRamIndexPtr, (IArg)paRamAddressPtr,
                (IArg)shadowPaRamsPtr, (IArg)tccIndexPtr, (IArg)edmaChannel);

        for (i = 0 ; i < numPaRams-1; i++) {

            /*
             * Copy the actual Param indices to the handle memory
             */
            paRamAddressPtr[i+1] = paRamBase + (actualPaRamIndex[i+1] *
                    sizeof(IRES_EDMA3CHAN_PaRamStruct));

            paRamIndexPtr[i+1] = actualPaRamIndex[i+1];

            if (shadow) {
                /* First some clean index values */
                (shadowPaRamsPtr[i]).src = 0x0;
                (shadowPaRamsPtr[i]).dst = 0x0;
                (shadowPaRamsPtr[i]).srcElementIndex = 0x0;
                (shadowPaRamsPtr[i]).dstElementIndex = 0x0;
                (shadowPaRamsPtr[i]).srcFrameIndex = 0x0;
                (shadowPaRamsPtr[i]).dstFrameIndex = 0x0;
                (shadowPaRamsPtr[i]).acnt = 0x1;
                (shadowPaRamsPtr[i]).bcnt = 0x1;
                (shadowPaRamsPtr[i]).bCntrld = 0x1;

                /*
                 * ccnt is the trigger word, don't write to it
                 */

                /*
                 * For each PaRam index (except the last), construct a
                 * shadowPaRam entry with link to the next PaRam
                 */
                (shadowPaRamsPtr[i]).link =
                        ((sizeof(IRES_EDMA3CHAN_PaRamStruct)) *
                        actualPaRamIndex[i+1]) + IRES_EDMA3CHAN_PARAMBASEOFFSET;

                Log_print2(Diags_USER2,
                        "[+2] IRES_EDMA3CHAN_constructHandle> "
                        "shadowPaRamsPtr[%d].link = 0x%x",
                        (IArg)i, (IArg)(shadowPaRamsPtr[i].link));

                /*
                 * Set up the OPT, AB_SYNC for all PaRams
                 */
                (shadowPaRamsPtr[i]).opt =
                        IRES_EDMA3CHAN_PARAMSTRUCT_OPT_ABSYNC;
            }
        }

        /*
         * Set up the last paRam
         */
        if (shadow ) {
            /* First some clean index values */
            (shadowPaRamsPtr[numPaRams - 1]).src = 0x0;
            (shadowPaRamsPtr[numPaRams - 1]).dst = 0x0;
            (shadowPaRamsPtr[numPaRams - 1]).srcElementIndex = 0x0;
            (shadowPaRamsPtr[numPaRams - 1]).dstElementIndex = 0x0;
            (shadowPaRamsPtr[numPaRams - 1]).srcFrameIndex = 0x0;
            (shadowPaRamsPtr[numPaRams - 1]).dstFrameIndex = 0x0;
            (shadowPaRamsPtr[numPaRams - 1]).acnt = 0x1;
            (shadowPaRamsPtr[numPaRams - 1]).bcnt = 0x1;
            (shadowPaRamsPtr[i]).bCntrld = 0x1;

            /*
             * Link to a null PaRam
             */
            (shadowPaRamsPtr[numPaRams - 1]).link =
                    IRES_EDMA3CHAN_PARAMSTRUCT_NULLLINK;

            Log_print2(Diags_USER2,
                    "[+2] IRES_EDMA3CHAN_constructHandle> shadowPaRamsPtr[%d].link ="
                    " 0x%x",
                    (IArg)((numPaRams -1)),
                    (IArg)(shadowPaRamsPtr[numPaRams -1].link));

            /*
             * Set OPT for last paRam
             * Static field, interrupt enabled
             * If TCCs requested, use tcc[0] as OPT bit.
             */
            if (numTccs > 0) {
                (shadowPaRamsPtr[numPaRams - 1]).opt =
                        IRES_EDMA3CHAN_PARAMSTRUCT_OPT_ABSYNC |
                        IRES_EDMA3CHAN_PARAMSTRUCT_OPT_TCCINTEN |
                        IRES_EDMA3CHAN_PARAMSTRUCT_OPT_TCCSTATIC |
                        IRES_EDMA3CHAN_PARAMSTRUCT_OPT_TCCBITS(tccIndexPtr[0]);
            }
            else {
                (shadowPaRamsPtr[numPaRams - 1]).opt =
                        IRES_EDMA3CHAN_PARAMSTRUCT_OPT_ABSYNC |
                        IRES_EDMA3CHAN_PARAMSTRUCT_OPT_TCCINTEN |
                        IRES_EDMA3CHAN_PARAMSTRUCT_OPT_TCCSTATIC;
            }
        }
    }
    else {
        paRamAddressPtr =  NULL;
                shadowPaRamsPtr = NULL;
        paRamIndexPtr = NULL;
    }

    if (numTccs ==0) {
        tccIndexPtr = NULL;
    }

    /*
     * Populate other fields of handle
     */
    handle->assignedNumPaRams = numPaRams;
    handle->assignedNumTccs = numTccs;

    handle->assignedQdmaChannelIndex = constructArgs->qdmaChan;
    handle->assignedEdmaChannelIndex = edmaChannel;

    Log_print4(Diags_USER2,
            "[+2] IRES_EDMA3CHAN_constructHandle> Num params %d, Num Tccs %d, "
            "Qdma channel %d Edma channel %d",
            (IArg)(handle->assignedNumPaRams), (IArg)(handle->assignedNumTccs),
            (IArg)(handle->assignedQdmaChannelIndex),
            (IArg)(handle->assignedEdmaChannelIndex));

     if (IRES_EDMA3CHAN_CHAN_NONE != edmaChannel) {
         /*
          * Edma channel is assigned, configure ESR correctly
          */
         if ( edmaChannel < 32) {
             handle->esrBitMaskL |= (0x1 << edmaChannel);
             handle->esrBitMaskH = 0x0;
         }
         else {
             handle->esrBitMaskH |= (0x1 <<(edmaChannel -32));
             handle->esrBitMaskL = 0x0;
         }
     }
         else {
                handle->esrBitMaskL = 0x0;
                handle->esrBitMaskH = 0x0;
         }

    if (numTccs > 0) {
        if (tccIndexPtr[0] < 32) {
            handle->iprBitMaskH = 0x0;
            handle->iprBitMaskL |= (0x1 << tccIndexPtr[0]);
        }
        else {
            handle->iprBitMaskL = 0x0;
            handle->iprBitMaskH |= (0x1 <<(tccIndexPtr[0] - 32));
        }
    }
        else {
                handle->iprBitMaskL = 0x0;
                handle->iprBitMaskH = 0x0;
        }

    Log_print4(Diags_USER2,
            "[+2] IRES_EDMA3CHAN_constructHandle> ESR 0x%x: 0x%x IPR 0x%x: 0x%x ",
            (IArg)(handle->esrBitMaskH), (IArg)(handle->esrBitMaskL),
            (IArg)(handle->iprBitMaskH), (IArg)(handle->iprBitMaskL));

    (handle->ires).persistent = constructArgs->persistent;

    /*
     * Adjust the pointers in the IRES_EDMA3CHAN2_Obj to point to the paRam
     * indices and the shadow parameters
     */
    handle->assignedPaRamIndices = paRamIndexPtr;
    handle->shadowPaRams = shadowPaRamsPtr;
    handle->assignedPaRamAddresses = paRamAddressPtr;
    handle->assignedTccIndices = tccIndexPtr;

    *status = IRES_OK;

    Log_print2(Diags_EXIT,
            "[+X] IRES_EDMA3CHAN_constructHandle> Exit (status=%d, handle=0x%x)",
            (IArg)(*status), (IArg)handle);

    return ((IRES_Handle)handle);
}

/**
 *  ======= IRES_EDMA3CHAN_getStaticProperties =======
 *  Returns the static properties of the particular resource
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
void IRES_EDMA3CHAN_getStaticProperties(IRES_Handle resourceHandle,
        IRES_Properties * resourceProperties)
{
    IRES_EDMA3CHAN_Properties * properties =
            (IRES_EDMA3CHAN_Properties *)resourceProperties;

    unsigned int * addr = (unsigned int *) internalState.edma3BaseAddress;

    unsigned int cccfg = addr[1];

    Log_print2(Diags_ENTRY,
            "[+E] IRES_EDMA3CHAN_getStaticProperties> Enter (resourceHandle=0x%x, "
            "resourceProperties=0x%x)",
            (IArg)resourceHandle, (IArg)resourceProperties);

    Assert_isTrue(NULL != addr, (Assert_Id)NULL);

    properties->numDmaChannels =
            IRES_EDMA3CHAN_EDMA3REGISTERLAYER_NUMDMACH(cccfg);
    properties->numEvtQueue =
            IRES_EDMA3CHAN_EDMA3REGISTERLAYER_NUMEVTQUE(cccfg);
    properties->numPaRAMSets =
            IRES_EDMA3CHAN_EDMA3REGISTERLAYER_NUMPAENTRY(cccfg);
    properties->numQdmaChannels =
            IRES_EDMA3CHAN_EDMA3REGISTERLAYER_NUMQDMACH(cccfg);
    properties->numRegions = IRES_EDMA3CHAN_EDMA3REGISTERLAYER_NUMREGN(cccfg);
    properties->numTccs = IRES_EDMA3CHAN_EDMA3REGISTERLAYER_NUMINTCH(cccfg);
    properties->numTcs = properties->numEvtQueue;
    properties->dmaChPaRAMMapExists    =
            IRES_EDMA3CHAN_EDMA3REGISTERLAYER_CHMAPEXIST(cccfg);
    properties->memProtectionExists    =
            IRES_EDMA3CHAN_EDMA3REGISTERLAYER_MPEXIST(cccfg);
    properties->globalRegs = (IRES_EDMA3CHAN_EDMA3RegisterLayer *)
            internalState.edma3BaseAddress;

    Log_print6(Diags_USER4,
            "[+4] IRES_EDMA3CHAN_getStaticProperties> Properties numDmaChannels %d,"
            " numEvtQueues %d, numPaRAMSets %d, numQdmaChannels %d, numRegions "
            "%d, numTccs %d",
            (IArg)(properties->numDmaChannels),
            (IArg)(properties->numEvtQueue), (IArg)(properties->numPaRAMSets),
            (IArg)(properties->numQdmaChannels), (IArg)(properties->numRegions),
            (IArg)(properties->numTccs));


    Log_print0(Diags_EXIT, "[+X] IRES_EDMA3CHAN_getStaticProperties> Exit");
}

/**
 *  ======= IRES_EDMA3CHAN_destructHandle =======
 *  De-initialize the env stored in the IRES_EDMA3CHAN channel handle, before
 *  it is freed by the resource manager.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_EDMA3CHAN_destructHandle(IRES_Handle handle)
{
    Log_print0(Diags_ENTRY, "[+E] IRES_EDMA3CHAN_destructHandle> Enter");

    /*
     * Nothing allocated in this module
     * So nothing needs to be done.
     */
    Log_print0(Diags_EXIT,
            "[+X] IRES_EDMA3CHAN_destructHandle> Exit (returnVal=IRES_OK)");

     return (IRES_OK);
}

IRESMAN_ConstructFxns IRESMAN_EDMA3CHAN_CONSTRUCTFXNS = {
    IRES_EDMA3CHAN_getName,
    IRES_EDMA3CHAN_getRevision,
    IRES_EDMA3CHAN_getMemRecs,
    IRES_EDMA3CHAN_getNumMemRecs,
    IRES_EDMA3CHAN_constructHandle,
    IRES_EDMA3CHAN_destructHandle
};
