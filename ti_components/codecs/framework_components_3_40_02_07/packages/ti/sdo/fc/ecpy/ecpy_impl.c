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
/**
 *  @file       ti/sdo/fc/ecpy/ecpy_impl.c
 *
 *  @brief      ECPY Definitions (C64P) - EDMA functional library
 *              Provides a comprehensive list of DMA operations an algorithm
 *              can perform on logical DMA channels it acquires through the
 *              IRES_EDMA3CHAN protocol.
 *
 *  WARNING:    THIS IS NOT THE FINAL REVISION OF ECPY INTERFACE. IT IS SUBJECT
 *              TO CHANGES PER REVIEW FEEDBACK. ADDITIONALLY, CURRENTLY IT IS
 *              AN API DEFINITION ONLY, IMPLEMENTATION AND COLLATERAL SUPPORT
 *              WILL BE ADDED IN FUTURE FC RELEASES.
 */

/**
 *  @defgroup   ti_sdo_fc_ecpy_ECPY ECPY (C64P)
 *
 *              The ECPY module provides a comprehensive list of DMA
 *              operations an algorithm can perform on logical DMA channels
 *              it acquires through the IRES_EDMA3CHAN protocol. Example of ECPY
 *              operations include channel configuration, DMA transfer
 *              scheduling, and DMA transfer synchronization.
 *
 *  @remark     For additional information, please refer to the
 *              "Using DMA with Framework Components for 'C64x+" document.
 */

#ifdef __cplusplus
extern "C" {
#endif

#define Registry_CURDESC ti_sdo_fc_ecpy_desc

/** @ingroup    ti_sdo_fc_ecpy_ECPY */
/*@{*/
#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>
#include "ecpy.h"
#include "ecpy_util.h"

static Void *myAlloc(size_t size, size_t align);
static Void myFree(Ptr addr, size_t size);
extern Registry_Desc ti_sdo_fc_ecpy_desc;

/*
 *  ======== myAlloc ========
 *  Wrapper around ECPY_CFG_PARAMS.allocFxn.
 */
static Void *myAlloc(size_t size, size_t align)
{
    IALG_MemRec memTab;
    Void       *addr = NULL;

    if (NULL == ECPY_CFG_PARAMS.allocFxn) {
        return (NULL);
    }

    memTab.size = size;
    memTab.alignment = align;
    memTab.space = IALG_DARAM0; /* this gets overridden in DSKT2_allocPersistent
                                 * to IALG_ESDATA.  */
    memTab.attrs = IALG_PERSIST;

    if (ECPY_CFG_PARAMS.allocFxn(&memTab, 1)) {
        addr = memTab.base;
    }

    return (addr);
}

/*
 *  ======== myFree ========
 *  Wrapper around ECPY_CFG_PARAMS.freeFxn.
 */
static Void myFree(Ptr addr, size_t size)
{
    IALG_MemRec memTab;

    memTab.base = addr;
    memTab.size = size;
    memTab.alignment = 0;         /* Alignment shouldn't be needed here */
    memTab.space = IALG_DARAM0;
    memTab.attrs = IALG_PERSIST;

    ECPY_CFG_PARAMS.freeFxn(&memTab, 1);
}

static __FAR__ IRES_EDMA3CHAN_EDMA3RegisterLayer *_EDMA3_globalRegs = NULL;

static void _ECPY_initEDMA3CHANStaticProperties(IRES_EDMA3CHAN2_Handle handle)
{

    IRES_EDMA3CHAN_Properties  _EDMA3CHAN_staticProperties;
    /* ensure that the toolchain uses same structure layout for PaRAM overlay */
    Assert_isTrue((sizeof(IRES_EDMA3CHAN_PaRamStruct)==32), (Assert_Id)NULL);

    if (_EDMA3_globalRegs == NULL) {

        handle->ires.getStaticProperties((struct IRES_Obj *)handle,
                (IRES_Properties *)&_EDMA3CHAN_staticProperties);
        _EDMA3_globalRegs = _EDMA3CHAN_staticProperties.globalRegs;
    }
}

/*
 * ECPY_createHandle(IRES_EDMA3CHAN2_Handle handle)
 */
ECPY_Handle ECPY_createHandle(IRES_EDMA3CHAN2_Handle handle, IALG_Handle alg)
{
    ECPY_ScratchObj * scratchHandle = NULL;
    int allocSize = 0;
    int allocatedFromSharedScratch = 0;
    ECPY_Handle ecpyHandle = NULL;
    int scratchId;

    Log_print2(Diags_ENTRY, "[+E] ECPY_createHandle> Enter "
            "(handle=0x%x, ialgHandle=%d)", (IArg)handle, (IArg)(alg ));

#ifdef _DEBUG_
    Assert_isTrue(handle != NULL, (Assert_Id)NULL);

#endif /* _DEBUG_ defined only for debug profile */

    /* First time this API is called we initialize the EDMA3 Static Properties*/
    if (_EDMA3_globalRegs == NULL) {
            _ECPY_initEDMA3CHANStaticProperties(handle);
    }

    /* First create the persistent ECPY_Handle */
    allocSize = sizeof(ECPY_Obj);

    /* Allocate memory for the ECPY handle object */
    if ((ecpyHandle = myAlloc(allocSize, 0)) == NULL) {

        Log_print1(Diags_USER7, "[+7] ECPY_createHandle> "
                   "Could not allocate memory size 0x%x in space "
                   "IALG_EXTERNAL of type IALG_PERSIST", (IArg)allocSize);

        Log_print0(Diags_EXIT, "[+X] ECPY_createHandle> "
                    "Exit (status=NULL)");

        return  (ECPY_Handle) NULL;
    }

    /* then create the scratch handle */
    allocSize = sizeof(ECPY_ScratchObj) + sizeof(IRES_EDMA3CHAN_PaRamStruct)
                + handle->assignedNumPaRams * sizeof(unsigned int);

#define MULTI_CHANNEL_SCRATCH_SUPPORT
#ifdef  MULTI_CHANNEL_SCRATCH_SUPPORT

    if (ECPY_CFG_PARAMS.getScratchIdFxn != NULL) {
        scratchId = ECPY_CFG_PARAMS.getScratchIdFxn((IALG_Handle)alg);
    }
    else {
        ecpyHandle->scratchId = -1;
        scratchId = -1;
    }

    /* if there is an assigned scratch group to alg, try to allocate the
     * scratchHandle from the shared scratch buffer (past the alg's instance
     * memory).
     */
    if (scratchId != -1) {
        IALG_MemRec memTab[1];

        memTab[0].size = allocSize;
        memTab[0].alignment = 0;
        memTab[0].space = IALG_DARAM0;
        memTab[0].attrs = IALG_SCRATCH;
        memTab[0].base = (void *) NULL;

        if (allocatedFromSharedScratch = ECPY_CFG_PARAMS.scratchAllocFxn(
                (IALG_Handle)alg, scratchId, memTab, 1)) {

            scratchHandle = memTab[0].base;
            ecpyHandle->scratchId = scratchId;
        }
        else {
            Log_print2(Diags_USER7, "[+7] ECPY_createHandle> "
                   "Could not allocate scratch handle memory size 0x%x in "
                   "shared scratch for scratchId:%d ",
                   (IArg)allocSize, (IArg)scratchId);

            ecpyHandle->scratchId = -1;
        }
    }
#endif
    /*
     * if allocation from shared scratch was succesful, we are done, otherwise
     * allocate the scratchHandle persistently.
     */
    if (!allocatedFromSharedScratch &&
            (scratchHandle = myAlloc(allocSize, 0)) == NULL) {

        Log_print1(Diags_USER7, "[+7] ECPY_createHandle> "
                   "Could not allocate scratch handle memory size 0x%x in space"
                   "(IALG_EXTERNAL) ", (IArg)allocSize);

        Log_print0(Diags_EXIT, "[+X] ECPY_createHandle> "
                    "Exit (status=NULL)");

        /* Free memory for the ECPY handle object */
        myFree(ecpyHandle, sizeof(ECPY_Obj));

        return  (ECPY_Handle) NULL;
    }

    ecpyHandle->iresHandle = handle;
    ecpyHandle->scratchPtr = scratchHandle;

    Log_print0(Diags_EXIT, "[+E] ECPY_createHandle> Exit");

    return ecpyHandle;
}


void _initializeScratchHandle(ECPY_Handle pHandle)
{
    unsigned int channel;
    unsigned int tcc;
    ECPY_ScratchObj *ecpyHandle = pHandle->scratchPtr;
    IRES_EDMA3CHAN2_Handle handle = pHandle->iresHandle;
    unsigned int i = 0;

    ecpyHandle->iresHandle = pHandle->iresHandle;
    ecpyHandle->firstPARAMShadow =  (IRES_EDMA3CHAN_PaRamStruct *)
                ((unsigned int)ecpyHandle + sizeof(ECPY_ScratchObj));

    tcc     = handle->assignedTccIndices[0];
    channel = handle->assignedEdmaChannelIndex;

    /*
     * For performance optimization: cache the IPR Register, channel-mask
     * and the ESR Register and channel bitmask in the handle.
     */
    if (tcc < 32) {
        ecpyHandle->iprRegisterAddr = (unsigned int)&_EDMA3_globalRegs->IPR;
        ecpyHandle->iprBitMask = (1UL << tcc);

    } else {
        ecpyHandle->iprRegisterAddr = (unsigned int)&_EDMA3_globalRegs->IPRH;
        ecpyHandle->iprBitMask = (1UL << (tcc - 32));
    }

    if (channel < 32) {
        ecpyHandle->esrRegisterAddr = (unsigned int)&_EDMA3_globalRegs->ESR;
        ecpyHandle->esrBitMask = (1UL << channel);

    } else {
        ecpyHandle->esrRegisterAddr = (unsigned int)&_EDMA3_globalRegs->ESRH;
        ecpyHandle->esrBitMask = (1UL << (channel - 32));
    }

    /* cache fields from ires handle  -- was #ifdef _CACHE_IRES */
    ecpyHandle->assignedEdmaChannelIndex = handle->assignedEdmaChannelIndex;
    ecpyHandle->queueMap = (unsigned int *) handle->queueMap;
    ecpyHandle->assignedNumPaRams = handle->assignedNumPaRams;
    ecpyHandle->assignedPaRamAddresses = (unsigned int *)(
            (unsigned int)ecpyHandle + sizeof(IRES_EDMA3CHAN_PaRamStruct) +
            sizeof(ECPY_ScratchObj));
    for (i = 0; i < ecpyHandle->assignedNumPaRams; i++) {
        ecpyHandle->assignedPaRamAddresses[i] =
                handle->assignedPaRamAddresses[i];
    }
    /***/

    /*
     * 3D transfers require that intermediate transfer chaining (ITCCHEN)
     * is enabled, but that will be done separately.
     * Linked transfer require  transfer chaining (TCCHEN) is enabled.
     * Set TCCMODE=1 => Early Completion mode, for faster linked transfers as default
     */
    ecpyHandle->optLinked = ECPY_PARAMOPTS_TCCBITS(tcc) |
                     ECPY_PARAMOPTS_TCCMODE | /* enable Early Completion */
                     ECPY_PARAMOPTS_TCCHEN |
                     ECPY_PARAMOPTS_ABSYNC;

    /*
     * For Final transfers program OPT with the TCC assigned to this channel,
     * enable TCC Interrupt
     * Default is to keep the STATIC bit 0 to support 3D transfers,
     * this will be set =1 when it is a non-3D single transfer so that
     * ECPY_directXXX APIs can reuse the single transfer PaRAMs without having
     * to reconfigure after each directStart.
     * The intermediate TR chaining will be set when needed for 3D.
     */
    ecpyHandle->optFinalStaticOff = ECPY_PARAMOPTS_TCCBITS(tcc) |
                     ECPY_PARAMOPTS_ABSYNC       |
                     ECPY_PARAMOPTS_TCC_INTEN    ;

}

/*
 * ECPY_deleteHandle(ECPY_Handle handle)
 */
Void ECPY_deleteHandle(ECPY_Handle ecpyHandle)
{
    int handleSize;

    IRES_EDMA3CHAN2_Handle iresHandle = NULL;

    Log_print1(Diags_ENTRY, "[+E] ECPY_deleteHandle> Enter "
            "(handle=0x%x)", (IArg)ecpyHandle);

    /*  TODO: free scratch and persistent handles separately ....*/

#ifdef _DEBUG_
    Assert_isTrue(ecpyHandle != NULL, (Assert_Id)NULL);
#endif /* _DEBUG_ defined only for debug profile */

    if (ecpyHandle != NULL) {

        iresHandle = ecpyHandle->iresHandle;

        if ((ECPY_Handle)iresHandle->shadowPaRams != ecpyHandle) {

            /*
             * Free ecpyHandle memory ONLY IF the channel (iresHandle) has
             * NOT been assigned shadow PARAM memory that is
             * used by ECPY_createHandle to construct the ECPY handle and
             * nothing needs to be freed here.
             */
            /* use cached ires implementation */
            handleSize = sizeof(ECPY_ScratchObj) +
                         sizeof(IRES_EDMA3CHAN_PaRamStruct) +
                         iresHandle->assignedNumPaRams * sizeof(unsigned int);

            /* Free allocates memory for the Scratch ECPY handle object */
            if (ecpyHandle->scratchId == -1) {
                /* free persistently allocated handle */
                myFree(ecpyHandle->scratchPtr, handleSize);
            }
            else {
                /* free shared scratch allocated handle */
                ECPY_CFG_PARAMS.scratchFreeFxn(ecpyHandle->scratchId,
                        ecpyHandle->scratchPtr, handleSize);
            }

            /* Finally free the persistent ECPY Handle */
            myFree(ecpyHandle, sizeof(ECPY_Obj));
        }

    }

    Log_print0(Diags_EXIT, "[+E] ECPY_deleteHandle> Exit");
}

/*
 * ECPY_activate(ECPY_Handle handle)
 */
Void ECPY_activate(ECPY_Handle pHandle)
{
    unsigned int channel;
    ECPY_ScratchObj *handle = pHandle->scratchPtr;

    /* uses cached iresHandle */
    ECPY_ScratchObj *iresHandle = handle;

    Log_print1(Diags_ENTRY, "[+E] ECPY_activate> Enter "
            "(handle=0x%x)", (IArg)handle);

#ifdef _DEBUG_
    Assert_isTrue(pHandle != NULL, (Assert_Id)NULL);
#endif /* _DEBUG_ defined only for debug profile */

    /* Initialize scratch Handle using the persistent state + iresHandle */
    _initializeScratchHandle(pHandle);

    channel    = iresHandle->assignedEdmaChannelIndex;

    /* Map EDMA3 Channel to the PARAM associated with channel    */
    if (channel < 64) {
        _EDMA3_globalRegs->DCHMAP[channel] =
                iresHandle->assignedPaRamAddresses[0];
    }

    /* Check and clear event missed register EMR entry for the channel */
    /* Also Ensure that  ER and SER bits are clear (via ECR and SECR writes. */
    if (channel < 32) {

        if (*(volatile Uns *)(&_EDMA3_globalRegs->EMR) & (1UL << channel)) {
            Log_print1(Diags_USER4, "[+4] ECPY_activate> WARNING! (EMR) EDMA "
                    "Event Miss detected for (DMA channel=0x%x)",(IArg)channel);

            *(volatile Uns *)(&_EDMA3_globalRegs->EMCR) = (1UL << channel);
        }

        if (*(volatile Uns *)(&_EDMA3_globalRegs->ER) & (1UL << channel)) {
            Log_print1(Diags_USER4, "[+4] ECPY_activate> WARNING! (ER) EDMA "
                    "Event Register had to be cleared for (DMA channel=0x%x)",
                   (IArg)channel);

            *(volatile Uns *)(&_EDMA3_globalRegs->ECR) = (1UL << channel);
        }

        if (*(volatile Uns *)(&_EDMA3_globalRegs->SER) & (1UL << channel)) {
            Log_print1(Diags_USER4, "[+4] ECPY_activate> WARNING! (SER) EDMA "
                    "Secondary Event Register reset for (DMA channel=0x%x)",
                    (IArg)channel);

            *(volatile Uns *)(&_EDMA3_globalRegs->SECR) = (1UL << channel);
        }

    } else if (channel < 64) {

        if (*(volatile Uns *)(&_EDMA3_globalRegs->EMRH) & (1UL << (channel-32)))
        {
            Log_print1(Diags_USER4, "[+4] ECPY_activate> WARNING! (EMR) EDMA "
                    "Event Miss detected for (DMA channel=0x%x)",(IArg)channel);

            *(volatile Uns *)(&_EDMA3_globalRegs->EMCRH)= (1UL << (channel-32));
        }

        if (*(volatile Uns *)(&_EDMA3_globalRegs->ERH) & (1UL << (channel-32)))
        {
            Log_print1(Diags_USER4, "[+4] ECPY_activate> WARNING! (ER) EDMA "
                    "Event Register had to be cleared for (DMA channel=0x%x)",
                   (IArg)channel);

            *(volatile Uns *)(&_EDMA3_globalRegs->ECRH)= (1UL << (channel-32));
        }

        if (*(volatile Uns *)(&_EDMA3_globalRegs->SERH) & (1UL << (channel-32)))
        {
            Log_print1(Diags_USER4, "[+4] ECPY_activate> WARNING! (SER) EDMA "
                    "Secondary Event Register reset for (DMA channel=0x%x)",
                    (IArg)channel);

            *(volatile Uns *)(&_EDMA3_globalRegs->SECRH)= (1UL << (channel-32));
        }
    }

    /* Enable EDMA3 Channel */
    if (channel < 32) {
        *(volatile Uns *)(&_EDMA3_globalRegs->EESR) = (1UL << channel);

    } else if (channel < 64) {
        *(volatile Uns *)(&_EDMA3_globalRegs->EESRH) = (1UL << (channel-32));
    }

    Log_print0(Diags_EXIT, "[+E] ECPY_activate> Exit");

    /* Initialize transferPending  and finalTransferNo for the channel. */
    handle->transferPending = 0;
    handle->finalTransferNo = iresHandle->assignedNumPaRams;

    return;
}

/*
 * ECPY_deactivate(ECPY_Handle handle)
 *
 * Current implementation does not disable the EDMA3 channels associated with
 * the handle to avoid race conditions involving shared EDMA channels.
 */
Void ECPY_deactivate(ECPY_Handle handle)
{
    Log_print1(Diags_ENTRY, "[+E] ECPY_deactivate> Enter "
            "(handle=0x%x)", (IArg)handle);

#ifdef _DEBUG_
    Assert_isTrue(handle != NULL, (Assert_Id)NULL);
#endif /* _DEBUG_ defined only for debug profile */

    Log_print0(Diags_EXIT, "[+E] ECPY_deactivate> Exit");
}

/**
 *  @brief      Indicate the memory space that DMA transfers submitted to
 *              the channel associated with the handle will modify.
 *              This information can be used for channel to TC Queue mapping
 *              for avoiding known Silicon GEM lockup issues or for
 *              performance improvements.
 *
 *  @param[in]  handle  ECPY channel handle.
 *  @param[in]  mode    DMA destination description of type
 *                      IRES_EDMA3CHAN_DmaDestType.
 */
Void ECPY_setDestinationMemoryMode(ECPY_Handle pHandle, short mode)
{
    volatile unsigned int *dmaqnumRegister;
    unsigned int *dmaqnum0RegisterAddr =
           (unsigned int *)&_EDMA3_globalRegs->DMAQNUM[0];
    ECPY_ScratchObj *handle = pHandle->scratchPtr;

    /* use cached ires handle */
    unsigned int edmaChannelNo = handle->assignedEdmaChannelIndex;

    unsigned int queueNum = 0;

    Log_print2(Diags_ENTRY, "[+E] ECPY_setDestinationMemoryMode> Enter "
            "(handle=0x%x) (mode=%d)", (IArg)handle, (IArg)mode);

#ifdef _DEBUG_
    Assert_isTrue(handle != NULL, (Assert_Id)NULL);
#endif /* _DEBUG_ defined only for debug profile */

    /* map the channel to EDMA Queue */

    /*  select the DMAQNUM[i] register, each register mapping 8 channels */
    dmaqnumRegister = dmaqnum0RegisterAddr + (edmaChannelNo >> 3);

    /* get configuration supplied Queue Number using the IRES_EDMA3CHAN2 */
    /* use cached ires handle */
    queueNum = handle->queueMap[mode];

    /* clear and update the 3 bits corr to the Channel with the Queue number */
    (*dmaqnumRegister) &= ~( 0x0000000F  << (4 * (edmaChannelNo & 0x7)));
    (*dmaqnumRegister) |= (queueNum << (4 * (edmaChannelNo & 0x7)));

    Log_print2(Diags_USER4, "[+4] ECPY_setDestinationMemoryMode> Map "
            " EDMA Channel: %d to TC Queue: 0x%x",
            (IArg)(edmaChannelNo), (IArg)(queueNum));

    Log_print0(Diags_EXIT, "[+E] ECPY_setDestinationMemoryMode> Exit");
}

/**
 *  @brief      Setting the TCCMODE (Early or Normal) affects only the 'intermediate
 *              transfers' of the linked transfers submitted using this channel.
 *              All subsequent direct and non-direct ECPY_configure* calls
 *              using this ecpyHandle will program the OPT's TCCMODE to select
 *              Early or Normal completion mode based on the 'enabled' argument.
 *
 *              Selecting the Early Completion mode may lead to performance
 *              improvements by increasing the EDMA throughput of linked
 *              transfers
 *              by submitting each transfer request from the EDMA Channel
 *              Controller
 *              to the Transfer Controller without waiting for the completion of
 *              the previous transfer from the Transfer Controller.
 *
 *  @param[in]  handle  ECPY channel handle.
 *  @param[in]  enabled 1/TRUE  to set TCCMODE to 1 (Early Completion)
 *                      0/FALSE to set TCCMODE to 1 (Normal Completion)
 *
 *  ======== ECPY_setEarlyCompletionMode ========
 */
Void ECPY_setEarlyCompletionMode(ECPY_Handle pEcpyHandle, short enabled)
{
    ECPY_ScratchObj *ecpyHandle = pEcpyHandle->scratchPtr;

    Log_print2(Diags_ENTRY, "[+E] ECPY_setEarlyCompletionMode> Enter "
            "(ecpyHandle=0x%x) (enabled=%d)", (IArg)ecpyHandle, (IArg)enabled);
#ifdef _DEBUG_
    Assert_isTrue(ecpyHandle != NULL, (Assert_Id)NULL);
#endif /* _DEBUG_ defined only for debug profile */

    if (enabled) {
        ecpyHandle->optLinked |= ECPY_PARAMOPTS_TCCMODE;
    } else {
        ecpyHandle->optLinked &= ~(ECPY_PARAMOPTS_TCCMODE);
    }

    Log_print2(Diags_USER4, "[+4] ECPY_setEarlyCompletionMode> Set "
            "(ecpyHandle=0x%x) Early Completion mode to:%d",
            (IArg)ecpyHandle,(IArg)enabled);

    Log_print0(Diags_EXIT, "[+E] ECPY_setEarlyCompletionMode> Exit ");
}

/**
 *  @brief              Initialize the ECPY module.  Called by framework.
 */
Void ECPY_init(Void);

/**
 *  @brief              Finalization of the ECPY module.
 */
Void ECPY_exit(Void);


/*@}*/

#ifdef __cplusplus
}
#endif /* extern "C" */
