/*
*
* Copyright (c) 2013-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/*
 *******************************************************************************
 *
 *  EDMA utility functions
 *
 *******************************************************************************
*/

/**
 *****************************************************************************
 * @file
 *  edma_utils_scatterGather.c
 *
 * @brief
 *  This file contains function implementation for util functions for
 *  configuring EVE EDMA for scatter Gather usecase.
 *
 * @author: Anshu Jain (anshu_jain@ti.com)
 * @version 0.1 (Aug 2013) : First version of eve edma utils function
 *
 *****************************************************************************
 */

#include "edma_utils_scatterGather.h"
#include "dma_resource_allocator.h"
#include "dma_funcs.h"
#include "edma_utils_state.h"
#include "edma_utils_context_size.h"
#include "edma_utils.h"

/**< Pointer to the start of EDMA CC0 */
#ifdef HOST_EMULATION
extern uint32_t edmaBase[1];
#else
extern const volatile  uint32_t edmaBase[1];
#endif
/** ========================================================
 *  @name   EDMA_UTILS_scattherGather_context
 *
 *  @desc   This structure contains the context for scatterGather usecase. It contains
 *               variables which are internally needed by scatterGather usecase
 *
 *  @field  numTransfers
 *             Total number of scattered transfers
 *
 *  @field submitWord
 *             Submit word to be written in the trigger word address to trigger the
 *              QDMA transfer
 *
 *  @field waitWord
 *             Wait word for which this usecase waits after triggering a transfer
 *
 *  @field optLink
 *              Opt field for the linked transfers
 *
 *  @field baseParamLast
 *              baseParam for the last transfer in the list of param set
 *
 *  @field triggerWordAddr
 *              Address of the trigger word writing at which will trigger
 *              QDMA transfer
 *
 *  @field qdmaChannel
 *              QDMA channel allocated for this transfer
 *
 *  @field tccVal
 *              TCC val assigned for this transfer
 *  ===============================================================
 */
typedef struct
{
    uint8_t                     numTransfers;
    uint32_t                    waitWord;
    uint16_t                    submitWord;
    uint32_t                    optLink;
    volatile uint32_t           *baseParam;
    volatile uint32_t           *baseParamLastSrc;
    volatile uint32_t           *baseParamLastDst;
    volatile uint32_t           *triggerWordAddr;
    uint8_t                     qdmaChannel;
    uint8_t                     tccVal;
} EDMA_UTILS_scattherGather_context;

#ifdef HOST_EMULATION

static void DMA_SUBMIT_ScatterGather_host(volatile uint32_t * triggerAddress,
                            uint16_t submit_word)
{

    uint32_t shift  = 0;
    uint32_t   rowCnt;
    uint8_t *srcPtr;
    uint8_t *dstPtr;
    uint32_t noBytes;
    uint32_t noLines;
    int32_t srcLinePitch;
    int32_t dstLinePitch;
    uint32_t cCnt;
    int32_t dstCidx;
    int32_t srcCidx;
    volatile uint32_t * baseParam;
    uint16_t    higherByte;
    uint16_t    linkAddr = 0u;
    uint32_t    baseParamAddr;
    uint32_t    flag = 1U;

    higherByte = (uint32_t)triggerAddress >>16;

    baseParamAddr = pack2(higherByte, submit_word);
    baseParam = (volatile uint32_t * )(baseParamAddr);
    linkAddr    = baseParam[5] & 0x0000FFFFU;

    while (flag)
    {
        if ( linkAddr == 0xFFFFU)
        {
            flag = 0;
        }
        noBytes = (baseParam[2] & 0x0000FFFFU);
        noLines = ((baseParam[2]) >> 16u);
        srcLinePitch = baseParam[4] & 0x0000FFFFU;
        dstLinePitch = baseParam[4] >>16;
        cCnt = baseParam[7] & 0x0000FFFFU;
        srcCidx = baseParam[6] & 0x0000FFFFU;
        dstCidx = baseParam[6] >> 16u;
        srcPtr  = (uint8_t *)baseParam[1];
        dstPtr  = (uint8_t *)baseParam[3];

        for (rowCnt = 0 ; rowCnt < noLines; rowCnt++)
        {
            memcpy (dstPtr + rowCnt * dstLinePitch, srcPtr + rowCnt * srcLinePitch, noBytes);
        }
        baseParam   = baseParam + 8;
        linkAddr    = baseParam[5] & 0x0000FFFFU;
    }

}



static void DMA_WAIT_ScatterGather_host(CSL_EdmaccRegsOvly edmaCc , uint32_t wait_word)
{
    return;
}

#endif

/* ==================================================
 *  @func     EDMA_UTILS_scattherGather_getContextSize
 *
 *  @desc     This function returns the size of the EDMA UTILS scatter gather handle.
 *            User is then expected to allocate this memory and provide it to EDMA UTILS
 *            scatter gather function. It is always advisable to allocate this handle
 *            in EVE's internal memory for better performance.
 *
 *  @modif    NONE
 *
 *  @inputs   NONE
 *
 *  @outputs NONE
 *
 *  @return    Size of the EDMA UTILS scatter gather context in bytes
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_scattherGather_getContextSize(void)
{
    int32_t size;

    size = sizeof(EDMA_UTILS_scattherGather_context);

    return size;
}

/* ==================================================
 *  @func     EDMA_UTILS_scattherGather_init
 *
 *  @desc     This function configures EDMA hardware based initParams
 *
 *  @modif    This function modifies scatterGatherContext
 *
 *  @inputs   This function takes following Inputs
 *                  scatterGatherContext :
 *                          EDMA utils handle for the scatter gather usecase. This memory is
 *                          expected to be allocated by user by first getting the size using
 *                          EDMA_UTILS_scattherGather_getContextSize.It is always advisable
 *                          to allocate this memory in internal memory for better performance
 *                  initParams :
 *                          Pointer to structure describing init configuration for the EDMA transfer
 *
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_scattherGather_init(void * scatterGatherContext ,
        const EDMA_UTILS_scattherGather_transferProperties * initParams ,
        uint8_t numTransfers)
{
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    const CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)edmaBase[0];
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

    EDMA_UTILS_scattherGather_context * scatterGatherHandle = (EDMA_UTILS_scattherGather_context *)scatterGatherContext;
    DMA_resourceStruct  edmaResources;
    int32_t             status = 0;
    uint8_t             transferCnt = 0;
    uint32_t            itccEn;
    uint32_t            tccEn;
    uint32_t            itcintEn;
    uint32_t            tcintEn;
    uint32_t            tccMode;
    uint32_t            fwid;
    uint32_t            stat;
    uint32_t            syncDim;
    uint32_t            dam;
    uint32_t            sam;

    uint32_t            tcc;
    uint32_t            optLink;
    uint32_t            optLast;
    uint16_t            Acnt , Bcnt;
    int16_t             srcBidx , dstBidx;
    uint16_t            linkAddr = 0;
    volatile uint32_t   (*baseParam)[][8];
    uint32_t            contextSize;
    uint32_t            numTransferNeeded = 0;

    if ( (scatterGatherHandle == NULL) || (initParams == NULL))
    {
#ifdef DEBUG
        printf("Null Pointer\n");
#endif
        status = -1;
    }
    contextSize = sizeof(EDMA_UTILS_scattherGather_context);

    /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
    /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
    /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
    /*  UNREACH.GEN :   Unreachable code  */
    /* Below condition in general will never be true and hence the code becomoes unreachable. But if later we add
    any new element in the context then the below condition can be true. So below condition check is to avoid
    missing such instances*/
    if (  (contextSize) != EDMA_UTILS_SCATTERGATHER_CONTEXT_SIZE )
    {
#ifdef DEBUG
        printf("Scatter Gather context size is not correct, it should be %d \n" ,
            sizeof(EDMA_UTILS_scattherGather_context));
#endif
        status = -1;
    }
    /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */
    /*RESET_MISRA("14.1")  -> Reset rule 14.1 for  UNREACH.GEN */

    if ( status == 0 )
    {
        memset(scatterGatherHandle , (int32_t)0 , sizeof *scatterGatherHandle);

        /* We are using linking feature of EDMA hardware to implement this utility.
        One problem with Linking is with every new trigger it will write the linked
        param set to the base parameter (1st parameter) of your linked transfers. This
        will result in overwriting the param set configuration for 1st transfer.
        In order to avoid this we are using a Dummy transfer ( with atleast one of Acnt,
        Bcnt and Ccnt being zero and atleast one of them being non-zreo). This dummy
        transfer will always be linked to the first param set describing the first transfer.
        Also we are using QDMA channel so that after first transfer all the subsequent
        transfers are triggered automatically because of the behavior of QDMA channel (transfer
        gets triggered as soon as we write to the trigger word which is one of the entry
        of the paramset */
        numTransferNeeded = (uint32_t)numTransfers + 1U;

        edmaResources.numChannels       = 1U;
        edmaResources.dmaAttr[0]        = DMA_CHAN_ATTR_QDMA;
        edmaResources.numParam[0]       = (uint8_t)numTransferNeeded;
        edmaResources.trigWordIndex[0]  = 5U;
        edmaResources.queNo[0]          = initParams->dmaQueNo;

        status = DMA_resourceAllocator_allocateResources(gEdmaCc, &edmaResources);
        if ( status == 0 )
        {
            status = DMA_funcs_hardwareRegSetup(gEdmaCc ,&edmaResources);
        }

        if ( status == 0 )
        {
            scatterGatherHandle->qdmaChannel = edmaResources.logicalChannelNo[0];
            scatterGatherHandle->tccVal      = edmaResources.tccVal[0];
            /* ------------------------------------------------------------- */
            /* Set options field for transfers                               */
            /* ------------------------------------------------------------- */
            itccEn     =  CSL_EDMACC_OPT_ITCCHEN_DISABLE;
            tccEn      =  CSL_EDMACC_OPT_TCCHEN_DISABLE;
            itcintEn   =  CSL_EDMACC_OPT_ITCINTEN_DISABLE;
            tcintEn    =  CSL_EDMACC_OPT_TCINTEN_DISABLE;
            tccMode    =  CSL_EDMACC_OPT_TCCMODE_EARLY;/* Enable Early Completion */
            fwid       =  CSL_EDMACC_OPT_FWID_8;
            stat       =  CSL_EDMACC_OPT_STATIC_NORMAL;/* For linking */
            syncDim    =  CSL_EDMACC_OPT_SYNCDIM_ABSYNC;
            dam        =  CSL_EDMACC_OPT_DAM_INCR;
            sam        =  CSL_EDMACC_OPT_SAM_INCR;
            tcc        =  edmaResources.tccVal[0];

            optLink =
                CSL_EDMA_OPT_MAKE
                (itccEn,tccEn,itcintEn,tcintEn,tcc,tccMode,fwid,stat,syncDim,dam,sam);


            tcintEn    =  CSL_EDMACC_OPT_TCINTEN_ENABLE;
            tccMode    =  CSL_EDMACC_OPT_TCCMODE_NORMAL;
            stat       =  CSL_EDMACC_OPT_STATIC_STATIC;

            optLast =
                CSL_EDMA_OPT_MAKE
                (itccEn,tccEn,itcintEn,tcintEn,tcc,tccMode,fwid,stat,syncDim,dam,sam);


            baseParam   = (volatile uint32_t (*)[][8])(volatile void *)edmaResources.baseParam[0];

            scatterGatherHandle->baseParam          = edmaResources.baseParam[0];
            scatterGatherHandle->triggerWordAddr    = &(*baseParam)[0][edmaResources.trigWordIndex[0]];
            scatterGatherHandle->waitWord           = (uint32_t)0x1U << edmaResources.tccVal[0];
            scatterGatherHandle->numTransfers       = numTransfers;
            scatterGatherHandle->optLink            = optLink;


            (*baseParam)[0][2] = 0x1U;
            (*baseParam)[0][7] = 0x1U;



            /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
            /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
            /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
             The address space is 32 bit and type casting to integer will not result into any loss because of TI's
            compiler teratment to integer.   */

            linkAddr    =  (uint16_t)((uint32_t)(&(*baseParam)[1][0]) & 0x0000FFFFU);
            /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

            /* Submit word for the dummy param is always the link address
            of the 2nd param entry */
            scatterGatherHandle->submitWord         = pack2((uint16_t)0U, linkAddr);

            /* First param block to Fill */
            baseParam = (volatile uint32_t (*)[][8])(volatile void *)&(*baseParam)[1][0];

            for ( transferCnt = 0 ; transferCnt < numTransfers; transferCnt++ )
            {
                /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
                /* MISRA.PTR.ARITH:  Pointer is used in arithmetic or array index expression  */
                /*  These pointers are allocated outside this module hence we cannot check if we are accessing within allocated memory.
                The harmful side effect of voilating this rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
                Acnt    = initParams->blkWidth[transferCnt];
                Bcnt    = initParams->blkHeight[transferCnt];
                srcBidx = (int16_t)initParams->srcPtrStride[transferCnt];
                dstBidx = (int16_t)initParams->dstPtrStride[transferCnt];
                /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

                if ( transferCnt == ( numTransfers - (uint8_t)1U ) )
                {
                    (*baseParam)[transferCnt][0]  = (uint32_t) optLast;
                    linkAddr      = 0xFFFFU;
                }
                else
                {
                    linkAddr = linkAddr + 32U;
                    (*baseParam)[transferCnt][0]  = (uint32_t) optLink;
                }

                linkAddr &= 0xFFFFU;

                /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
               /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
               /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
                            The address space is 32 bit and type casting to integer will not result into any loss because of TI's
                           compiler teratment to integer.   */

                /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
                /* MISRA.PTR.ARITH:  Pointer is used in arithmetic or array index expression  */
               /*  These pointers are allocated outside this module hence we cannot check if we are accessing within allocated memory.
              The harmful side effect of voilating this rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
                (*baseParam)[transferCnt][1]  = (uint32_t)initParams->srcPtr[transferCnt];
                (*baseParam)[transferCnt][2]  = pack2(Bcnt, Acnt);
                (*baseParam)[transferCnt][3]  = (uint32_t)initParams->dstPtr[transferCnt];
                /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */
                /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
                (*baseParam)[transferCnt][4]  = pack2((uint16_t)dstBidx, (uint16_t)srcBidx);
                (*baseParam)[transferCnt][5]  = pack2(Bcnt , linkAddr);
                (*baseParam)[transferCnt][6]  = 0x0U;
                (*baseParam)[transferCnt][7]  = 0x1U;

            }

        }

    }
    return status;

}

/* ==================================================
 *  @func     EDMA_UTILS_scattherGather_configure
 *
 *  @desc     TBD
 *
 *  @modif    This function modifies scatterGatherContext
 *
 *  @inputs   This function takes following Inputs
 *                  scatterGatherContext :
 *                          EDMA utils handle for the scatter gather usecase.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_scattherGather_configure(void * const scatterGatherContext )
{
    int32_t             status = 0;

    if ( scatterGatherContext == NULL)
    {
        status = -1;
    }

    return status;

}

/* ==================================================
 *  @func     EDMA_UTILS_scattherGather_updateNtrigger
 *
 *  @desc   This function can selectively update four properties of the transfers and actually
 *          trigger the transfer. These prioperties are are sourceAddress, Destination Address,
 *          block widht and block Height. Which property needs to be updated can be given in
 *          EDMA_UTILS_scattherGather_updateParams. Refer this structure for futher details on
 *          each individual fields.
 *          This function can only be called after EDMA_UTILS_scattherGather_init
 *          has been called. Size of array update param should be same as what has
 *          already been initialized in EDMA_UTILS_scattherGather_init.
 *
 *  @modif    This function modifies scatterGatherContext
 *
 *  @inputs   This function takes following Inputs
 *                  scatterGatherContext :
 *                          DMA utils handle for the scatter gather usecase.
 *                  updateParams :
 *                          Pointer to the EDMA_UTILS_scattherGather_transferProperties
 *                          describing property to be updated for all the transfers
 *                          which were initialized during init time. dmaQueNo field
 *                          is a don't care during this call. It is to be noted that
 *                          while updating source/destination pointer user is expected to
 *                          provide the source and destination stride also
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_scattherGather_updateNtrigger(void * scatterGatherContext ,
        const EDMA_UTILS_scattherGather_transferProperties * updateParams)
{
    EDMA_UTILS_scattherGather_context * scatterGatherHandle =
                    (EDMA_UTILS_scattherGather_context *)scatterGatherContext;
    uint32_t             transferCnt;
    int32_t             status = 0;
    volatile uint32_t   (*baseParam)[][8];
    volatile uint16_t    (*tempPtr)[2];
#ifdef DEBUG
    if (scatterGatherHandle)
#endif
    {
        baseParam = (volatile uint32_t (*)[][8])(volatile void *)scatterGatherHandle->baseParam;

        /* Reset the opt parameter for dummy PARAM block */
        (*baseParam)[0][0] = scatterGatherHandle->optLink;
        /* Update the ACNT BCNT field for the dummy PARAM block */
        (*baseParam)[0][2] = 0x1U;


        /* First param block to Fill */
        baseParam = (volatile uint32_t (*)[][8])(volatile void *)&(*baseParam)[1][0];
        /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
        /* MISRA.PTR.ARITH:  Pointer is used in arithmetic or array index expression  */
       /*  These pointers(updateParams-> blkWidth,srcPtr, dstPtr etc) are allocated outside this module hence we cannot check if we
       are accessing within allocated memory. The harmful side effect of voilating this rule (accessing outside valid memory) shall be checked
       by another code checker like Klocwork     */

        for ( transferCnt = 0U; transferCnt < (uint32_t)scatterGatherHandle->numTransfers; transferCnt++ )
        {
            if ( (uint32_t) (updateParams->updateMask & (uint32_t)EDMA_UTILS_SCATTERGATHER_UPDATE_BLOCK_W) )
            {
                tempPtr = (volatile uint16_t (*)[2])(volatile void *)&(*baseParam)[transferCnt][2];
                (*tempPtr)[0] = updateParams->blkWidth[transferCnt];
            }

            if ( (uint32_t) (updateParams->updateMask & (uint32_t)EDMA_UTILS_SCATTERGATHER_UPDATE_BLOCK_H) )
            {
                tempPtr = (volatile uint16_t (*)[2])(volatile void *)&(*baseParam)[transferCnt][2];
                (*tempPtr)[1] = updateParams->blkHeight[transferCnt];
            }
            if ( (uint32_t) (updateParams->updateMask & (uint32_t)EDMA_UTILS_SCATTERGATHER_UPDATE_SRCPTR_STRIDE ) )
            {
                /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
               /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
               /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
                            The address space is 32 bit and type casting to integer will not result into any loss because of TI's
                           compiler teratment to integer.   */
                (*baseParam)[transferCnt][1] = (uint32_t)updateParams->srcPtr[transferCnt];
                /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
                tempPtr = (volatile uint16_t (*)[2])(volatile void *)&(*baseParam)[transferCnt][4];
                (*tempPtr)[0] = updateParams->srcPtrStride[transferCnt];
             }

            if ( (uint32_t) (updateParams->updateMask & (uint32_t)EDMA_UTILS_SCATTERGATHER_UPDATE_DSTPTR_STRIDE) )
            {
                /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
               /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
               /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
                            The address space is 32 bit and type casting to integer will not result into any loss because of TI's
                           compiler teratment to integer.   */
                (*baseParam)[transferCnt][3] = (uint32_t)updateParams->dstPtr[transferCnt];
                /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
                tempPtr     = (volatile uint16_t (*)[2])(volatile void *)&(*baseParam)[transferCnt][4];
                (*tempPtr)[1]  = updateParams->dstPtrStride[transferCnt];
            }
        }
        /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

#ifdef HOST_EMULATION
    DMA_SUBMIT_ScatterGather_host(scatterGatherHandle->triggerWordAddr, scatterGatherHandle->submitWord);
#else
        QDMA_SUBMIT(scatterGatherHandle->triggerWordAddr, scatterGatherHandle->submitWord);
#endif
    }
#ifdef DEBUG
    else
    {
        status = -1;
    }
#endif

    return status;
}

/* ==================================================
 *  @func     EDMA_UTILS_scattherGather_updateSrcNtrigger
 *
 *  @desc   This function updates the source pointer for all the transfers and trigger the transfer.
 *          This function should be used when only source pointer is getting updated after initializing
 *          other parameters
 *          This function can only be called after EDMA_UTILS_scattherGather_init
 *          has been called. Size of array update param should be same as what has
 *          already been initialized in EDMA_UTILS_scattherGather_init.
 *
 *  @modif    This function modifies scatterGatherContext
 *
 *  @inputs   This function takes following Inputs
 *                  scatterGatherContext :
 *                          DMA utils handle for the scatter gather usecase.
 *                  updateParams :
 *                          Pointer to the EDMA_UTILS_scattherGather_updateParams
 *                          describing property to be updated for all the transfers
 *                          which were initialized during init time. Only source
 *                          address field should be provided. Other fields are dont care
 *                          for this API
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_scattherGather_updateSrcNtrigger(void * scatterGatherContext ,
        uint8_t ** const srcPtr)
{
    EDMA_UTILS_scattherGather_context * scatterGatherHandle =
                    (EDMA_UTILS_scattherGather_context *)scatterGatherContext;
    uint32_t             transferCnt;
    int32_t             status = 0;
    volatile uint32_t   (*baseParam)[][8];

#ifdef DEBUG
    if (scatterGatherHandle)
#endif
    {
        baseParam = (volatile uint32_t (*)[][8])(volatile void *)scatterGatherHandle->baseParam;

        /* Reset the opt parameter for dummy PARAM block */
        (*baseParam)[0][0] = scatterGatherHandle->optLink;
        /* Update the ACNT BCNT field for the dummy PARAM block */
        (*baseParam)[0][2] = 0x1U;


        /* First param block to Fill */
         baseParam = (volatile uint32_t (*)[][8])(volatile void *)&(*baseParam)[1][0];

        for ( transferCnt = 0U; transferCnt < (uint32_t)scatterGatherHandle->numTransfers; transferCnt++ )
        {
           /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
           /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
           /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
                        The address space is 32 bit and type casting to integer will not result into any loss because of TI's
                       compiler teratment to integer.   */
          /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
          /* MISRA.PTR.ARITH:  Pointer is used in arithmetic or array index expression  */
          /*  These pointers(srcPtr) are allocated outside this module hence we cannot check if we
          are accessing within allocated memory. The harmful side effect of voilating this rule (accessing outside valid memory) shall be checked
          by another code checker like Klocwork     */
           (*baseParam)[transferCnt][1] = (uint32_t)srcPtr[transferCnt];
           /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */
           /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
        }

#ifdef HOST_EMULATION
        DMA_SUBMIT_ScatterGather_host(scatterGatherHandle->triggerWordAddr, scatterGatherHandle->submitWord);
#else
        QDMA_SUBMIT(scatterGatherHandle->triggerWordAddr, scatterGatherHandle->submitWord);
#endif

    }
#ifdef DEBUG
    else
    {
        status = -1;
    }
#endif

    return status;
}



/* ==================================================
 *  @func     EDMA_UTILS_scattherGather_updateDstNtrigger
 *
 *  @desc   This function updates the destination pointer for all the transfers and trigger the transfer.
 *          This function should be used when only destination pointer is getting updated after initializing
 *          other parameters
 *          This function can only be called after EDMA_UTILS_scattherGather_init
 *          has been called. Size of array update param should be same as what has
 *          already been initialized in EDMA_UTILS_scattherGather_init.
 *
 *  @modif    This function modifies scatterGatherContext
 *
 *  @inputs   This function takes following Inputs
 *                  scatterGatherContext :
 *                          DMA utils handle for the scatter gather usecase.
 *                  dstPtr :
 *                          Pointer to the list of source pointers that needs to be updated
 *                          It is to be noted that only destination pointers is updated with
 *                          this call stride remains same as the one configured during the init
 *                          call.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_scattherGather_updateDstNtrigger(void * scatterGatherContext ,
        uint8_t ** const dstPtr)
{
    EDMA_UTILS_scattherGather_context * scatterGatherHandle =
                    (EDMA_UTILS_scattherGather_context *)scatterGatherContext;
    uint32_t             transferCnt;
    int32_t             status = 0;
    volatile uint32_t   (*baseParam)[][8];
#ifdef DEBUG
    if (scatterGatherHandle)
#endif
    {
        baseParam = (volatile uint32_t (*)[][8])(volatile void *)scatterGatherHandle->baseParam;

        /* Reset the opt parameter for dummy PARAM block */
        (*baseParam)[0][0] = scatterGatherHandle->optLink;
        /* Update the ACNT BCNT field for the dummy PARAM block */
        (*baseParam)[0][2] = 0x1U;

        /* First param block to Fill */
         baseParam = (volatile uint32_t (*)[][8])(volatile void *)&(*baseParam)[1][0];

        for ( transferCnt = 0U; transferCnt < (uint32_t)scatterGatherHandle->numTransfers; transferCnt++ )
        {
            /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
           /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
           /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
                        The address space is 32 bit and type casting to integer will not result into any loss because of TI's
                       compiler teratment to integer.   */
              /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
              /* MISRA.PTR.ARITH:  Pointer is used in arithmetic or array index expression  */
              /*  These pointers (dstPtr) are allocated outside this module hence we cannot check if we
              are accessing within allocated memory. The harmful side effect of voilating this rule (accessing outside valid memory) shall be checked
              by another code checker like Klocwork     */
            (*baseParam)[transferCnt][3] = (uint32_t)dstPtr[transferCnt];
            /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */
            /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
        }

#ifdef HOST_EMULATION
        DMA_SUBMIT_ScatterGather_host(scatterGatherHandle->triggerWordAddr, scatterGatherHandle->submitWord);
#else
        QDMA_SUBMIT(scatterGatherHandle->triggerWordAddr, scatterGatherHandle->submitWord);
#endif


    }
#ifdef DEBUG
    else
    {
        status = -1;
    }
#endif

    return status;
}

/* ==================================================
 *  @func     EDMA_UTILS_scattherGather_wait
 *
 *  @desc   This function waits for the DMA transfer to be completed and can be used
 *          for any of the above trigger.
 *
 *  @modif    This function modifies scatterGatherContext
 *
 *  @inputs   This function takes following Inputs
 *                  scatterGatherContext :
 *                          DMA utils handle for the scatter gather usecase.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_scattherGather_wait(void * scatterGatherContext)
{
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    const CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)edmaBase[0];
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

    EDMA_UTILS_scattherGather_context * scatterGatherHandle = (EDMA_UTILS_scattherGather_context *)scatterGatherContext;
    int32_t            status = 0;

#ifdef DEBUG
    if ( scatterGatherHandle)
#endif
    {
#ifdef HOST_EMULATION
    DMA_WAIT_ScatterGather_host(gEdmaCc,scatterGatherHandle->waitWord);
#else
    QDMA_WAIT(gEdmaCc,scatterGatherHandle->waitWord);
#endif

    }
#ifdef DEBUG
    else
    {
        printf("Context Structure pointer is NULL\n");
        status = -1;
    }
#endif

return status;
}

/* ==================================================
 *  @func     EDMA_UTILS_scattherGather_isDone
 *
 *  @desc   This function checks for the DMA transfer to be completed or not.
 *          It can be used for any of the above trigger.
 *
 *  @modif    This function modifies scatterGatherContext
 *
 *  @inputs   This function takes following Inputs
 *                  scatterGatherContext :
 *                          DMA utils handle for the scatter gather usecase.
 *
 *  @outputs NONE
 *
 *  @return    0 : Transfer not completed
 *             1 : Transfer completed
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_scattherGather_isDone(void * scatterGatherContext)
{
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    const CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)edmaBase[0];
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

    EDMA_UTILS_scattherGather_context * scatterGatherHandle = (EDMA_UTILS_scattherGather_context *)scatterGatherContext;
    int32_t            status = 0;
#ifdef HOST_EMULATION

#else
    if((gEdmaCc->IPR & (scatterGatherHandle->waitWord)) == (scatterGatherHandle->waitWord))
    {
        status = 1;
    }
#endif



return status;
}

/* ==================================================
 *  @func     EDMA_UTILS_scattherGather_deinit
 *
 *  @desc   This function releases all the DMA resource allocated in
 *              EDMA_UTILS_scattherGather_deinit
 *
 *  @modif    This function modifies scatterGatherContext
 *
 *  @inputs   This function takes following Inputs
 *                  scatterGatherContext :
 *                          DMA utils handle for the scatter gather usecase.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_scattherGather_deinit(void * scatterGatherContext)
{
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    const CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)edmaBase[0];
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

    EDMA_UTILS_scattherGather_context * scatterGatherHandle = (EDMA_UTILS_scattherGather_context *)scatterGatherContext;
    DMA_resourceStruct  edmaResources;
    int32_t            status = 0;
    uint32_t            numTransferNeeded = 0;

    /* We are using linking feature of EDMA hardware to implement this utility.
    One problem with Linking is with every new trigger it will write the linked
    param set to the base parameter (1st parameter) of your linked transfers. This
    will result in overwriting the param set configuration for 1st transfer.
    In order to avoid this we are using a Dummy transfer ( with atleast one of Acnt,
    Bcnt and Ccnt being zero and atleast one of them being non-zreo). This dummy
    transfer will always be linked to the first param set describing the first transfer.
    Also we are using QDMA channel so that after first transfer all the subsequent
    transfers are triggered automatically because of the behavior of QDMA channel (transfer
    gets triggered as soon as we write to the trigger word which is one of the entry
    of the paramset */
    numTransferNeeded = (uint32_t)scatterGatherHandle->numTransfers + 1U;

    edmaResources.numChannels         = 1U;
    edmaResources.dmaAttr[0]          = DMA_CHAN_ATTR_QDMA;
    edmaResources.numParam[0]         = (uint8_t)numTransferNeeded;
    edmaResources.trigWordIndex[0]    = 5U;
    edmaResources.logicalChannelNo[0] = scatterGatherHandle->qdmaChannel;
    edmaResources.tccVal[0]           = scatterGatherHandle->tccVal;
    edmaResources.baseParam[0]        = scatterGatherHandle->baseParam;

    status = DMA_resourceAllocator_deallocateResources(gEdmaCc,&edmaResources);

    return status;
}


