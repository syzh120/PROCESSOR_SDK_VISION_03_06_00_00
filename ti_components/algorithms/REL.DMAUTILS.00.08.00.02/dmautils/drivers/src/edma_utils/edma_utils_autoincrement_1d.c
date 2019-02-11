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
 *  edma_utils_autoincrement.c
 *
 * @brief
 *  This file contains function implementation for util functions for
 *  configuring EVE EDMA sub module.
 *
 * @author: Anshu Jain (anshu_jain@ti.com)
 * @version 0.1 (Aug 2013) : First version of eve edma utils function
 *
 *****************************************************************************
 */

#include "edma_utils_autoincrement_1d.h"
#include "dma_resource_allocator.h"
#include "dma_funcs.h"
#include "edma_utils_state.h"
#include "edma_utils_context_size.h"
#include "edma_utils.h"


/*#pragma RESET_MISRA ("required")*/


extern DMA_utilsStateStruct gDmaUtilsStateStruct;         /**< EDMA state structure */

/**< Pointer to the start of EDMA CC0 */
#ifdef HOST_EMULATION
extern uint32_t edmaBase[1];
#else
extern const volatile  uint32_t edmaBase[1];
#endif



/** ========================================================
 *  @name   EDMA_UTILS_autoIncrement1D_context
 *
 *  @desc   This structure contains the context for autoincrement usecase. It contains
 *               variables which are internally needed by auto increment usecase
 *
 *  @field  numInTransfers
 *             Total number of input transfers
 *
 *  @field numOutTransfers
 *             Total number of output transfers
 *
 *  @field startChannelIdIn
 *               This field stores the channelId from which the allocation of all input channels
 *               is done. Actual channel number in the dmaStateStructure can be retreived by adding
 *               this field of the channelNum in this context
 *
 *  @field startChannelIdOut
 *               This field stores the channelId from which the allocation of all output channels
 *               is done. Actual channel number in the dmaStateStructure can be retreived by adding
 *               this field of the channelNum in this context
 *
 *  @field submitWordIn
 *             Submit word to be written in ESR register for all the input transfers
 *
 *  @field submitWordOut
 *             Submit word to be written in ESR register for all the output transfers
 *
 *  @field waitWordIn
 *             Wait word to be written in ESR register for all the input transfers=
 *
 *  @field waitWordOut
 *             Wait to be written in ESR register for all the output transfers
 *
 *  @field idxIn
 *              Horizontal index of the block during autoincrement for input transfers
 *
 *  @field  blkVertIdxIn
 *              Vertical index of the block during autoincrement for input transfers
 *
 *  @field idxOut
 *              Horizontal index of the block during autoincrement for output transfers
 *
 *  @field blkVertIdxOut
 *              Vertical index of the block during autoincrement for output transfers
 *
 *  @field numBlkHorz
 *              Total number of times we should run in horizontal direction before updating
 *              param set. It is calculated as follows:
 *              numBlkHorz = ( roiWidth[i] - blkWidth[i])/(extBlkIncrementX[i])
 *
 *  @field numBlkVert
 *              Total number of times we should increment in vertical direction
  *              numBlkVert = ( roiHeight[i] - blkHeight[i])/(extBlkIncrementY[i])
 *
 * @field numTotal1D
 *              Total number of blocks in auto increment. It is calculated as follows:
 *              numTotal1D = numBlkHorz * numBlkVert

 *
 * @field transferProp
 *              Array storing transfer properties for each transfer
 *  ===============================================================
 */
typedef struct
{
    uint8_t                      numInTransfers;
    uint8_t                      numOutTransfers;
    uint8_t                      startChannelIdIn;
    uint8_t                      startChannelIdOut;
    uint32_t                     submitWordIn;
    uint32_t                     submitWordOut;
    uint32_t                     waitWordIn;
    uint32_t                     waitWordOut;

    int16_t                      idxIn;
    int16_t                      idxOut;

    uint16_t                     numTotal1D;
    EDMA_UTILS_autoIncrement1D_transferProperties transferProp[NUM_MAX_TRANSFER_AUTOINCREMENT_1D];

} EDMA_UTILS_autoIncrement1D_context;


#ifdef HOST_EMULATION

static void DMA_SUBMIT_AUTOINCREMENT1D_host(CSL_EdmaccRegsOvly edmaCc , uint32_t submit_word)
{
    uint32_t shift  = 0;
    uint8_t *srcPtr;
    uint8_t *dstPtr;
    uint32_t noBytes;
    uint32_t noLines;
    int32_t srcLinePitch;
    int32_t dstLinePitch;
    uint32_t cCnt;
    int16_t dstCidx;
    int16_t srcCidx;
    volatile uint32_t * trigParam;

    for ( shift = 0 ; shift < 32 ; shift++ )
    {
        if ( (submit_word >> shift ) & 0x1)
        {
            trigParam = gDmaUtilsStateStruct.baseParam[shift];
            cCnt = trigParam[7] & 0x0000FFFFu;
            if ( cCnt != 0 )
            {
                noBytes = (trigParam[2] & 0x0000FFFFu);
                noLines = ((trigParam[2]) >> 16u);
                srcLinePitch = trigParam[4] & 0x0000FFFFu;
                dstLinePitch = trigParam[4] >>16;

                srcCidx = trigParam[6] & 0x0000FFFFu;
                dstCidx = trigParam[6] >> 16u;
                srcPtr  = (uint8_t *)trigParam[1];
                dstPtr  = (uint8_t *)trigParam[3];

                memcpy (dstPtr, srcPtr , noBytes);

                srcPtr  = (uint8_t *)trigParam[1] + srcLinePitch;
                dstPtr  = (uint8_t *)trigParam[3] + dstLinePitch;

                noLines = noLines - 1 ;

                if ( noLines == 0 )
                {
                    noLines = trigParam[5] >> 16u;
                    srcPtr  = (uint8_t *)trigParam[1] + srcCidx;
                    dstPtr  = (uint8_t *)trigParam[3] + dstCidx;
                    trigParam[7] = (cCnt-1) & 0x0000FFFFu;
                }

                trigParam[2] = pack2( noLines , noBytes);

                trigParam[1] = (uint32_t)srcPtr;
                trigParam[3] = (uint32_t)dstPtr;
            }
        }
    }

}

static void DMA_WAIT_AUTOINCREMENT1D_host(CSL_EdmaccRegsOvly edmaCc , uint32_t wait_word)
{
    return;
}

#endif

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement1D_getContextSize
 *
 *  @desc     This function returns the size of the EDMA UTILS autoincrement handle. User is
 *                 then expected to allocate this memory and provide it to EDMA UTILS autoincrement
 *                 function as an input
 *
 *  @modif    NONE
 *
 *  @inputs   NONE
 *
 *  @outputs NONE
 *
 *  @return    Size of the EDMA UTILS context in bytes
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement1D_getContextSize(void)
{
    int32_t size;

    size = sizeof(EDMA_UTILS_autoIncrement1D_context);

    return size;
}

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement1D_init
 *
 *  @desc     This function initializes the EDMA UTILS context for autoincrement usecase.
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement1D_getContextSize.
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
int32_t EDMA_UTILS_autoIncrement1D_init(void * autoIncrementContext ,const EDMA_UTILS_autoIncrement1D_initParam * initParams)
{
    EDMA_UTILS_autoIncrement1D_context * autoIncrementHandle = (EDMA_UTILS_autoIncrement1D_context *)autoIncrementContext;
    int32_t       status = 0;
    uint32_t      transferCnt = 0;
    uint32_t      transferCntOffset;
    uint32_t      actualTransferCnt;
    uint32_t      numTransfers;
    uint32_t      contextSize;

    if ( (autoIncrementHandle == NULL) || (initParams == NULL))
    {
#ifdef DEBUG
        printf("Null Pointer\n");
#endif
        status = -1;
    }
    contextSize = sizeof(EDMA_UTILS_autoIncrement1D_context);

        /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
    /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
    /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
    /*  UNREACH.GEN :   Unreachable code  */
    /* Below condition will currently never fail and hence code is unreachable but
    as the implementation of the function changes contextSize and the macro defined can be different
    this error check is to catch such mismatch*/
    if (  (contextSize) != EDMA_UTILS_AUTOINCREMENT_1D_CONTEXT_SIZE )
    {
#ifdef DEBUG
        printf("Autoincrement context size is not correct, it should be %d \n" ,
            sizeof(EDMA_UTILS_autoIncrement1D_context));
#endif
        status = -1;
    }
    /*RESET_MISRA("14.1")  -> Reset rule 14.1 for  UNREACH.GEN */
    /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */

    if ( status == 0 )
    {
        if ( (initParams->transferType == EDMA_UTILS_TRANSFER_IN) || (initParams->transferType == EDMA_UTILS_TRANSFER_INOUT))
        {
            memset(autoIncrementHandle , 0 , sizeof *autoIncrementHandle);
            autoIncrementHandle->idxOut = -1;
        }

        switch (initParams->transferType)
        {
            case EDMA_UTILS_TRANSFER_IN:
                numTransfers                         = initParams->numInTransfers;
                transferCntOffset                    = 0;
                autoIncrementHandle->numInTransfers  = initParams->numInTransfers;
                break;
            case EDMA_UTILS_TRANSFER_OUT:
                transferCntOffset                    = autoIncrementHandle->numInTransfers;
                numTransfers                         = initParams->numOutTransfers;
                autoIncrementHandle->numOutTransfers = initParams->numOutTransfers;
                break;
            case EDMA_UTILS_TRANSFER_INOUT:
                transferCntOffset                    = 0;
                numTransfers                         = initParams->numInTransfers + initParams->numOutTransfers;
                autoIncrementHandle->numInTransfers  = initParams->numInTransfers;
                autoIncrementHandle->numOutTransfers = initParams->numOutTransfers;
                break;
            default :
#ifdef DEBUG
                printf("Invalid Transfer Type \n");
#endif
                status = -1;
                break;
        }

        if ( status == 0 )
        {

            for ( transferCnt = 0; transferCnt < numTransfers; transferCnt++)
            {
                actualTransferCnt = transferCnt + transferCntOffset;

                autoIncrementHandle->transferProp[actualTransferCnt].totalLength
                                        = initParams->transferProp[transferCnt].totalLength;

                autoIncrementHandle->transferProp[actualTransferCnt].numBytes
                                        = initParams->transferProp[transferCnt].numBytes;

                autoIncrementHandle->transferProp[actualTransferCnt].extMemIncrement
                                        = initParams->transferProp[transferCnt].extMemIncrement;

                autoIncrementHandle->transferProp[actualTransferCnt].intMemIncrement
                                        = initParams->transferProp[transferCnt].intMemIncrement;

                autoIncrementHandle->transferProp[actualTransferCnt].extMemPtr
                                        = initParams->transferProp[transferCnt].extMemPtr;

                autoIncrementHandle->transferProp[actualTransferCnt].interMemPtr
                                        = initParams->transferProp[transferCnt].interMemPtr;

                autoIncrementHandle->transferProp[actualTransferCnt].numCircBuf
                                        = initParams->transferProp[transferCnt].numCircBuf;

                autoIncrementHandle->transferProp[actualTransferCnt].dmaQueNo
                                        = initParams->transferProp[transferCnt].dmaQueNo;

            }
        }
    }

    return status;

}


/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement1D_configure
 *
 *  @desc   This function configures autoincrement usecase. This function can be called
 *               separately for IN and OUT channels or can also be called together for both INOUT channel.
 *              This functions behavior is undefined if you configure OUT trasnfer first followed by IN channel
 *              or if you configure IN and OUT transfer multiple number of times
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement1D_getContextSize.
 *                  transferType :
 *                           Type of transfer that you want to configure ( IN, OUT or INOUT)
 *                           Refer to EDMA_UTILS_TRANSFER_TYPE enum for valid values
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement1D_configure(void * autoIncrementContext , uint32_t transferType)
{
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    const CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)edmaBase[0];
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

    EDMA_UTILS_autoIncrement1D_context * autoIncrementHandle = (EDMA_UTILS_autoIncrement1D_context *)autoIncrementContext;
    DMA_resourceStruct  edmaResourcesIn;
    DMA_resourceStruct  edmaResourcesOut;
    uint32_t            actualTransferCnt;
    uint32_t            transferCnt = 0;
    uint32_t            transferCntOffset;
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
    uint16_t            aCNT, bCNT, cCNT;

    /* ----------------------------------------------------------------- */
    /* Option words to hold configuration of dma transfers               */
    /* ----------------------------------------------------------------- */
    uint32_t            opt;
    int32_t             status = 0;
    uint32_t            channelCnt;
    int16_t             circBufOffset;
    uint32_t            numTotal1D;

    if ( autoIncrementHandle == NULL )
    {
#ifdef DEBUG
        printf("Null Pointer\n");
#endif

        status = -1;
    }

    if ( status == 0 )
    {
        /* Reset internal variables after context switch */
        autoIncrementHandle->idxOut = -1;
        autoIncrementHandle->idxIn  = 0;

        if ( autoIncrementHandle->transferProp[0].extMemIncrement != 0)
        {
            autoIncrementHandle->numTotal1D = ((autoIncrementHandle->transferProp[0].totalLength -
                              autoIncrementHandle->transferProp[0].numBytes) /
                              autoIncrementHandle->transferProp[0].extMemIncrement) + 1U;
        }
        else
        {
             autoIncrementHandle->numTotal1D = 1U;
        }

        switch (transferType)
        {
            case EDMA_UTILS_TRANSFER_IN:
                transferCntOffset                       = 0;

                edmaResourcesIn.numChannels             = autoIncrementHandle->numInTransfers;
                for ( channelCnt = 0 ; channelCnt < edmaResourcesIn.numChannels ; channelCnt++ )
                {
                    edmaResourcesIn.numParam[channelCnt]    = 1U;
                    edmaResourcesIn.dmaAttr[channelCnt]     = DMA_CHAN_ATTR_EDMA;
                    edmaResourcesIn.queNo[channelCnt]       =
                        autoIncrementHandle->transferProp[channelCnt].dmaQueNo;
                }
                status = DMA_resourceAllocator_allocateResources(gEdmaCc, &edmaResourcesIn);


                break;
            case EDMA_UTILS_TRANSFER_OUT:
                transferCntOffset                       = autoIncrementHandle->numInTransfers;

                edmaResourcesOut.numChannels            = autoIncrementHandle->numOutTransfers;
                for ( channelCnt = 0 ; channelCnt < edmaResourcesOut.numChannels ; channelCnt++ )
                {
                    edmaResourcesOut.numParam[channelCnt]    = 1U;
                    edmaResourcesOut.dmaAttr[channelCnt]     = DMA_CHAN_ATTR_EDMA;
                    edmaResourcesOut.queNo[channelCnt]       =
                                            autoIncrementHandle->transferProp[transferCntOffset + channelCnt].dmaQueNo;

                }
                status = DMA_resourceAllocator_allocateResources(gEdmaCc, &edmaResourcesOut);
                break;
            case EDMA_UTILS_TRANSFER_INOUT:
                transferCntOffset                       = autoIncrementHandle->numInTransfers;

                edmaResourcesIn.numChannels             = autoIncrementHandle->numInTransfers;
                edmaResourcesOut.numChannels            = autoIncrementHandle->numOutTransfers;

                for ( channelCnt = 0 ; channelCnt < edmaResourcesIn.numChannels ; channelCnt++ )
                {
                    edmaResourcesIn.numParam[channelCnt]    = 1U;
                    edmaResourcesIn.dmaAttr[channelCnt]     = DMA_CHAN_ATTR_EDMA;
                    edmaResourcesIn.queNo[channelCnt]       =
                                            autoIncrementHandle->transferProp[channelCnt].dmaQueNo;

                }
                status = DMA_resourceAllocator_allocateResources(gEdmaCc, &edmaResourcesIn);

                for ( channelCnt = 0 ; channelCnt < edmaResourcesOut.numChannels ; channelCnt++ )
                {
                    edmaResourcesOut.numParam[channelCnt]    = 1U;
                    edmaResourcesOut.dmaAttr[channelCnt]     = DMA_CHAN_ATTR_EDMA;
                    edmaResourcesOut.queNo[channelCnt]       =
                        autoIncrementHandle->transferProp[transferCntOffset + channelCnt].dmaQueNo;

                }
                if ( status == 0 )
                {
                    status = DMA_resourceAllocator_allocateResources(gEdmaCc, &edmaResourcesOut);
                }

                break;
            default :
#ifdef DEBUG
                printf("Invalid Transfer Type \n");
#endif
                status = -1;
                break;
        }

        if ( status == 0 )
        {
            if (( transferType == EDMA_UTILS_TRANSFER_IN ) ||
                        ( transferType == EDMA_UTILS_TRANSFER_INOUT))
            {
                status = DMA_funcs_hardwareRegSetup(gEdmaCc ,&edmaResourcesIn);
                if ( status == 0)
                {
                    status = DMA_utils_updateStateStruct(&edmaResourcesIn,
                                    &autoIncrementHandle->startChannelIdIn);
                }
            }

            if (( transferType == EDMA_UTILS_TRANSFER_OUT ) ||
                        ( transferType == EDMA_UTILS_TRANSFER_INOUT))
            {
                if ( status == 0)
                {
                    status = DMA_funcs_hardwareRegSetup(gEdmaCc ,&edmaResourcesOut);
                }

                if ( status == 0)
                {
                    status = DMA_utils_updateStateStruct(&edmaResourcesOut,
                                     &autoIncrementHandle->startChannelIdOut);
                }
            }

        }

        if ( status == 0 )
        {
            /* ------------------------------------------------------------- */
            /* Set options field for transfers                               */
            /* ------------------------------------------------------------- */
            itccEn     =  CSL_EDMACC_OPT_ITCCHEN_DISABLE;
            tccEn      =  CSL_EDMACC_OPT_TCCHEN_DISABLE;
            itcintEn   =  CSL_EDMACC_OPT_ITCINTEN_ENABLE;
            tcintEn    =  CSL_EDMACC_OPT_TCINTEN_ENABLE;
            tccMode    =  CSL_EDMACC_OPT_TCCMODE_NORMAL;
            fwid       =  CSL_EDMACC_OPT_FWID_8;
            stat       =  CSL_EDMACC_OPT_STATIC_NORMAL;
            syncDim    =  CSL_EDMACC_OPT_SYNCDIM_ASYNC;
            dam        =  CSL_EDMACC_OPT_DAM_INCR;
            sam        =  CSL_EDMACC_OPT_SAM_INCR;

            if (( transferType == EDMA_UTILS_TRANSFER_IN ) ||
                        ( transferType == EDMA_UTILS_TRANSFER_INOUT))
            {
                for ( transferCnt = 0; transferCnt < autoIncrementHandle->numInTransfers ; transferCnt++ )
                {
                    actualTransferCnt = transferCnt;

                    if(autoIncrementHandle->transferProp[transferCnt].extMemIncrement != 0)
                    {
                      numTotal1D = (uint32_t)((autoIncrementHandle->transferProp[actualTransferCnt].totalLength -
                        autoIncrementHandle->transferProp[actualTransferCnt].numBytes) /
                        autoIncrementHandle->transferProp[actualTransferCnt].extMemIncrement) + 1U;
                    }
                    else
                    {
                      numTotal1D = 1U;
                    }

                    if(numTotal1D != autoIncrementHandle->numTotal1D)
                    {
#ifdef DEBUG
                      printf(" ( totalLength - numBytes / extMemIncrement is not an integer \n");
#endif
                      status = -1;
                      break;
                    }

                    aCNT = autoIncrementHandle->transferProp[actualTransferCnt].numBytes;
                    bCNT = autoIncrementHandle->transferProp[actualTransferCnt].numCircBuf;
                    cCNT = (autoIncrementHandle->numTotal1D + ( bCNT - 1U ))/
                           autoIncrementHandle->transferProp[actualTransferCnt].numCircBuf;


                    tcc        = (uint32_t)gDmaUtilsStateStruct.tccVal[transferCnt +
                                    autoIncrementHandle->startChannelIdIn];

                    /* ------------------------------------------------------------- */
                    /* Options field calculation for the EDMA transfer.              */
                    /* ------------------------------------------------------------- */

                    opt =
                        CSL_EDMA_OPT_MAKE
                        (itccEn,tccEn,itcintEn,tcintEn,tcc,tccMode,fwid,stat,syncDim,dam,sam);

                    autoIncrementHandle->submitWordIn  |=
                                         (uint32_t) 0x1U  <<
                                        gDmaUtilsStateStruct.logicalChanNo[transferCnt +
                                        autoIncrementHandle->startChannelIdIn];

                    autoIncrementHandle->waitWordIn    |=
                                         (uint32_t) 0x1U <<
                                        gDmaUtilsStateStruct.tccVal[transferCnt +
                                        autoIncrementHandle->startChannelIdIn];

                    circBufOffset = (int16_t)((autoIncrementHandle->transferProp[actualTransferCnt].numCircBuf - (uint8_t)1U) *
                            autoIncrementHandle->transferProp[actualTransferCnt].intMemIncrement);
                    /* Configure trig param for channel In
                           Source is external memory
                           Destination is internal memory */

                    DMA_funcs_writeTransferParams
                    (
                        gDmaUtilsStateStruct.baseParam[transferCnt + autoIncrementHandle->startChannelIdIn],
                        opt ,
                        autoIncrementHandle->transferProp[actualTransferCnt].extMemPtr,
                        autoIncrementHandle->transferProp[actualTransferCnt].interMemPtr,
                        aCNT , bCNT,
                        autoIncrementHandle->transferProp[actualTransferCnt].extMemIncrement,
                        autoIncrementHandle->transferProp[actualTransferCnt].intMemIncrement,
                        autoIncrementHandle->transferProp[actualTransferCnt].extMemIncrement,
                        -circBufOffset,
                        cCNT,
                        0           /* No linking*/
                    );
                }

            }

            if (( transferType == EDMA_UTILS_TRANSFER_OUT ) ||
                        ( transferType == EDMA_UTILS_TRANSFER_INOUT))
            {
                for ( transferCnt = 0; transferCnt < autoIncrementHandle->numOutTransfers ; transferCnt++ )
                {
                    actualTransferCnt = transferCnt + transferCntOffset;

                    if(autoIncrementHandle->transferProp[transferCnt].extMemIncrement != 0)
                    {
                      numTotal1D = (uint32_t)((autoIncrementHandle->transferProp[actualTransferCnt].totalLength -
                        autoIncrementHandle->transferProp[actualTransferCnt].numBytes) /
                        autoIncrementHandle->transferProp[actualTransferCnt].extMemIncrement) + 1U;
                    }
                    else
                    {
                      numTotal1D = 1U;
                    }

                    if(numTotal1D != autoIncrementHandle->numTotal1D)
                    {
#ifdef DEBUG
                      printf(" ( totalLength - numBytes / extMemIncrement is not an integer \n");
#endif
                      status = -1;
                      break;
                    }

                    aCNT = autoIncrementHandle->transferProp[actualTransferCnt].numBytes;
                    bCNT = autoIncrementHandle->transferProp[actualTransferCnt].numCircBuf;
                    cCNT = (uint16_t)((autoIncrementHandle->numTotal1D + (bCNT - 1U))/
                           autoIncrementHandle->transferProp[actualTransferCnt].numCircBuf );

                    tcc        = (uint32_t)gDmaUtilsStateStruct.tccVal[transferCnt +
                                    autoIncrementHandle->startChannelIdOut];

                    /* ------------------------------------------------------------- */
                    /* Options field calculation for the EDMA transfer.              */
                    /* ------------------------------------------------------------- */

                    opt =
                        CSL_EDMA_OPT_MAKE
                        (itccEn,tccEn,itcintEn,tcintEn,tcc,tccMode,fwid,stat,syncDim,dam,sam);

                    autoIncrementHandle->submitWordOut  |=
                                        (uint32_t)0x1U  <<
                                        gDmaUtilsStateStruct.logicalChanNo[transferCnt +
                                        autoIncrementHandle->startChannelIdOut];

                    autoIncrementHandle->waitWordOut |=
                                        (uint32_t)0x1U <<
                                        gDmaUtilsStateStruct.tccVal[transferCnt +
                                        autoIncrementHandle->startChannelIdOut];

                    /* Configure trig param for channel In
                           Source is external memory
                           Destination is internal memory */
                      circBufOffset = (int16_t)((autoIncrementHandle->transferProp[actualTransferCnt].numCircBuf -
                                (uint8_t)1U) *
                                autoIncrementHandle->transferProp[actualTransferCnt].intMemIncrement);

                    DMA_funcs_writeTransferParams
                    (
                        gDmaUtilsStateStruct.baseParam[transferCnt + autoIncrementHandle->startChannelIdOut],
                        opt ,
                        autoIncrementHandle->transferProp[actualTransferCnt].interMemPtr,
                        autoIncrementHandle->transferProp[actualTransferCnt].extMemPtr,
                        aCNT , bCNT,
                        autoIncrementHandle->transferProp[actualTransferCnt].intMemIncrement,
                        autoIncrementHandle->transferProp[actualTransferCnt].extMemIncrement,
                        -circBufOffset,
                        autoIncrementHandle->transferProp[actualTransferCnt].extMemIncrement,
                        cCNT,/* Adding 1 so that once a block row is finished we dont
                                want complete trig params to be zero */
                        0           /* No linking*/
                    );
                }
            }
        }
    }


    return status;
}

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement1D_update
 *
 *  @desc   This function updates a certain set of parameters of autoincrement usecase.
 *               This function can only be called after EDMA_UTILS_autoIncrement1D_configure
 *               has been called. Size of array update param should be same as what has already been
 *               configured for IN, OUT or INOUT transfer in EDMA_UTILS_autoIncrement1D_configure otherwise
 *               this function will return an error. This function only updates the internal context and not actually
 *              update the param set. Param set is updated when the next frame starts.
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement1D_getContextSize.
 *                  updateParams :
 *                          Pointer to the array of params set that needs to be updated for IN, OUT or INOUT transfer.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement1D_update(void * autoIncrementContext, const EDMA_UTILS_autoIncrement1D_updateParams *updateParams)
{
    EDMA_UTILS_autoIncrement1D_context * autoIncrementHandle = (EDMA_UTILS_autoIncrement1D_context *)autoIncrementContext;
    int32_t status = 0;
    uint32_t      transferCnt = 0;
    uint32_t      transferCntOffset;
    uint32_t      actualTransferCnt;
    uint32_t      numTransfers;

    if ( (autoIncrementHandle == NULL) || (updateParams == NULL))
    {
#ifdef DEBUG
        printf("Null Pointer\n");
#endif

        status = -1;
    }

    if ( status == 0 )
    {
        switch (updateParams->transferType)
        {
            case EDMA_UTILS_TRANSFER_IN:
                numTransfers                         = autoIncrementHandle->numInTransfers;
                transferCntOffset                    = 0;
                break;
            case EDMA_UTILS_TRANSFER_OUT:
                transferCntOffset                    = autoIncrementHandle->numInTransfers;
                numTransfers                         = autoIncrementHandle->numOutTransfers;
                break;
            case EDMA_UTILS_TRANSFER_INOUT:
                transferCntOffset                    = 0;
                numTransfers                         = autoIncrementHandle->numInTransfers + autoIncrementHandle->numOutTransfers;
                break;
            default :
#ifdef DEBUG
                printf("Invalid Transfer Type \n");
#endif
                status = -1;
                break;
        }
    }

    if ( status == 0 )
    {
        for ( transferCnt = 0; transferCnt < numTransfers ; transferCnt++ )
        {
            actualTransferCnt = transferCnt + transferCntOffset;

            if( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_TOTALLENGTH) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].totalLength
                                    = updateParams->updateParams[transferCnt].totalLength;
            }

            if( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_NUMBYTES) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].numBytes
                                    = updateParams->updateParams[transferCnt].numBytes;
            }

            if( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_EXTMEMINCREMENT) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].extMemIncrement
                                    = updateParams->updateParams[transferCnt].extMemIncrement;
            }

            if( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_INTMEMINCREMENT) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].intMemIncrement
                                    = updateParams->updateParams[transferCnt].intMemIncrement;
            }

            if( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_EXTMEMPTR) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].extMemPtr
                                    = updateParams->updateParams[transferCnt].extMemPtr;
            }

            if( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_INTERMEMPTR) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].interMemPtr
                                    = updateParams->updateParams[transferCnt].interMemPtr;
            }

            if( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_NUMCIRCBUF) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].numCircBuf
                                    = updateParams->updateParams[transferCnt].numCircBuf;
            }

            if( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_DMAQUENO) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].dmaQueNo
                                    = updateParams->updateParams[transferCnt].dmaQueNo;
            }
        }

    }

    return status;
}


/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement1D_triggerInChannel
 *
 *  @desc   This function triggers all Input channels together
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement1D_getContextSize.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement1D_triggerInChannel(void * autoIncrementContext)
{
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    const CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)edmaBase[0];
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */


    EDMA_UTILS_autoIncrement1D_context * autoIncrementHandle = (EDMA_UTILS_autoIncrement1D_context *)autoIncrementContext;
    int32_t             status = 0;

#ifdef DEBUG
    if ( autoIncrementHandle )
#endif
    {
        if(autoIncrementHandle->idxIn < autoIncrementHandle->numTotal1D)
        {
#ifdef HOST_EMULATION
    DMA_SUBMIT_AUTOINCREMENT1D_host(gEdmaCc , autoIncrementHandle->submitWordIn);
#else
    DMA_SUBMIT(gEdmaCc , autoIncrementHandle->submitWordIn);
#endif
        }
    }
#ifdef DEBUG
    else
    {
        printf("Auto Increment Context Structure pointer is NULL\n");
        status = -1;
    }
#endif
    return status;
}

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement1D_triggerOutChannel
 *
 *  @desc   This function triggers all Output channels together. It also indicates when the last
 *              block is reached in the ROI given by user.
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement1D_getContextSize.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *                  1 : Last Block in auto increment
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement1D_triggerOutChannel(void * autoIncrementContext)
{
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    const CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)edmaBase[0];
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

    EDMA_UTILS_autoIncrement1D_context * autoIncrementHandle = (EDMA_UTILS_autoIncrement1D_context *)autoIncrementContext;
    int32_t            status = 0;

#ifdef DEBUG
    if ( autoIncrementHandle )
#endif
    {
        if (autoIncrementHandle->idxOut >=0 )
        {
#ifdef HOST_EMULATION
                DMA_SUBMIT_AUTOINCREMENT1D_host(gEdmaCc , autoIncrementHandle->submitWordOut);
#else
                DMA_SUBMIT(gEdmaCc , autoIncrementHandle->submitWordOut);
#endif

        }

        if((autoIncrementHandle->idxOut) >=
                (autoIncrementHandle->numTotal1D - 2))
        {
            status  = 1;
        }
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
 *  @func     EDMA_UTILS_autoIncrement1D_waitInChannel
 *
 *  @desc   This function waits for all Input channels together
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement1D_getContextSize.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement1D_waitInChannel(void * autoIncrementContext)
{
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    const CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)edmaBase[0];
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

    EDMA_UTILS_autoIncrement1D_context * autoIncrementHandle = (EDMA_UTILS_autoIncrement1D_context *)autoIncrementContext;
    int32_t            status = 0;

#ifdef DEBUG
    if ( autoIncrementHandle)
#endif
    {
        if(autoIncrementHandle->idxIn < autoIncrementHandle->numTotal1D)
        {

#ifdef HOST_EMULATION
            DMA_WAIT_AUTOINCREMENT1D_host(gEdmaCc ,autoIncrementHandle->waitWordIn);
#else
            DMA_WAIT(gEdmaCc ,autoIncrementHandle->waitWordIn);
#endif

        }

        autoIncrementHandle->idxIn++;

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
 *  @func     EDMA_UTILS_autoIncrement1D_waitOutChannel
 *
 *  @desc   This function waits for all output channels together
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement1D_getContextSize.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement1D_waitOutChannel(void * autoIncrementContext)
{
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    const CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)edmaBase[0];
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

    EDMA_UTILS_autoIncrement1D_context * autoIncrementHandle = (EDMA_UTILS_autoIncrement1D_context *)autoIncrementContext;
    int32_t status = 0;

#ifdef DEBUG
    if ( autoIncrementHandle)
#endif
    {

        if(autoIncrementHandle->idxOut >= 0)
        {

#ifdef HOST_EMULATION
            DMA_WAIT_AUTOINCREMENT1D_host(gEdmaCc ,autoIncrementHandle->waitWordOut);
#else
            DMA_WAIT(gEdmaCc ,autoIncrementHandle->waitWordOut);
#endif

        }

        /* ------------------------------------------------------------- */
        /* Update block position                                         */
        /* ------------------------------------------------------------- */
        autoIncrementHandle->idxOut++;

        /* if vert Blk count reaches total number of vertical blocks it mean we  have reached the last block
        so reset block indexes to initial values for next call */
        if ( autoIncrementHandle->idxOut == autoIncrementHandle->numTotal1D)
        {
            autoIncrementHandle->idxIn  = 0;
            autoIncrementHandle->idxOut = -1;
        }
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
 *  @func     EDMA_UTILS_autoIncrement1D_deconfigure
 *
 *  @desc   This function deconfigures autoincrement 1D usecase and releases all the allocated EDMA resources.
 *          This function can be called separately for IN and OUT channels or can also be called together
 *         for both INOUT channel. This functions behavior is undefined if you configure OUT trasnfer
 *          first followed by IN channel or if you configure IN and OUT transfer multiple number of times.
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected tobe allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement_getContextSize.
 *                  transferType :
 *                           Type of transfer that you want to configure ( IN, OUT or INOUT)
 *                           Refer to EDMA_UTILS_TRANSFER_TYPE enum for valid values
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement1D_deconfigure(void * autoIncrementContext , uint32_t transferType)
{
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    const CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)edmaBase[0];
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

    EDMA_UTILS_autoIncrement1D_context * autoIncrementHandle = (EDMA_UTILS_autoIncrement1D_context *)autoIncrementContext;
    DMA_resourceStruct  edmaResourcesIn;
    DMA_resourceStruct  edmaResourcesOut;
    uint32_t            transferCntOffset;
    uint32_t            channelCnt = 0;
    int32_t             status = 0;

    if ( autoIncrementHandle == NULL )
    {
#ifdef DEBUG
            printf("Null Pointer\n");
#endif

        status = -1;
    }

    if ( status == 0 )
    {
        /* Reset internal variables after context switch */
        autoIncrementHandle->idxOut = -1;
        autoIncrementHandle->idxIn  = 0;

        switch (transferType)
        {
            case EDMA_UTILS_TRANSFER_IN:
                transferCntOffset                       = 0;
                edmaResourcesIn.numChannels             = autoIncrementHandle->numInTransfers;
                for ( channelCnt = 0 ; channelCnt < edmaResourcesIn.numChannels ; channelCnt++ )
                {
                    edmaResourcesIn.numParam[channelCnt]    = 1U;
                    edmaResourcesIn.dmaAttr[channelCnt]     = DMA_CHAN_ATTR_EDMA;
                    edmaResourcesIn.queNo[channelCnt]       =
                        autoIncrementHandle->transferProp[channelCnt].dmaQueNo;
                    edmaResourcesIn.logicalChannelNo[channelCnt] = (uint8_t)gDmaUtilsStateStruct.logicalChanNo[autoIncrementHandle->startChannelIdIn + channelCnt];
                    edmaResourcesIn.baseParam[channelCnt]       = gDmaUtilsStateStruct.baseParam[autoIncrementHandle->startChannelIdIn + channelCnt];
                    edmaResourcesIn.tccVal[channelCnt]       = (uint8_t)gDmaUtilsStateStruct.tccVal[autoIncrementHandle->startChannelIdIn + channelCnt];
                }
                status = DMA_resourceAllocator_deallocateResources(gEdmaCc, &edmaResourcesIn);
                  /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
                  /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
                  /* Status will never be 0 because we are passing all the correct parameters to the function above and hence all the error conditions inside the function
                  will never occur.*/
                if ( status == 0 )
                {
                    DMA_utils_freeStateStruct( autoIncrementHandle->startChannelIdIn,  autoIncrementHandle->numInTransfers );
                }
                /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */


                break;
            case EDMA_UTILS_TRANSFER_OUT:
                transferCntOffset                       = autoIncrementHandle->numInTransfers;

                edmaResourcesOut.numChannels            = autoIncrementHandle->numOutTransfers;
                for ( channelCnt = 0 ; channelCnt < edmaResourcesOut.numChannels ; channelCnt++ )
                {
                    edmaResourcesOut.numParam[channelCnt]    = 1U;
                    edmaResourcesOut.dmaAttr[channelCnt]     = DMA_CHAN_ATTR_EDMA;
                    edmaResourcesOut.queNo[channelCnt]       =
                                            autoIncrementHandle->transferProp[transferCntOffset + channelCnt].dmaQueNo;

                    edmaResourcesOut.logicalChannelNo[channelCnt] = (uint8_t)gDmaUtilsStateStruct.logicalChanNo[autoIncrementHandle->startChannelIdOut + channelCnt];
                    edmaResourcesOut.baseParam[channelCnt]       = gDmaUtilsStateStruct.baseParam[autoIncrementHandle->startChannelIdOut + channelCnt];
                    edmaResourcesOut.tccVal[channelCnt]       = (uint8_t)gDmaUtilsStateStruct.tccVal[autoIncrementHandle->startChannelIdOut + channelCnt];

                }
                /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
                /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
                /* Status will never be 0 because we are passing all the correct parameters to the function above and hence all the error conditions inside the function
                will never occur.*/
                status = DMA_resourceAllocator_deallocateResources(gEdmaCc, &edmaResourcesOut);
                if ( status == 0 )
                {
                    DMA_utils_freeStateStruct( autoIncrementHandle->startChannelIdOut,  autoIncrementHandle->numOutTransfers);
                }
                /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */
                break;
            case EDMA_UTILS_TRANSFER_INOUT:
                transferCntOffset                       = autoIncrementHandle->numInTransfers;

                edmaResourcesIn.numChannels             = autoIncrementHandle->numInTransfers;
                edmaResourcesOut.numChannels            = autoIncrementHandle->numOutTransfers;

                for ( channelCnt = 0 ; channelCnt < edmaResourcesIn.numChannels ; channelCnt++ )
                {
                    edmaResourcesIn.numParam[channelCnt]    = 1U;
                    edmaResourcesIn.dmaAttr[channelCnt]     = DMA_CHAN_ATTR_EDMA;
                    edmaResourcesIn.queNo[channelCnt]       =
                                            autoIncrementHandle->transferProp[channelCnt].dmaQueNo;

                    edmaResourcesIn.logicalChannelNo[channelCnt] = (uint8_t)gDmaUtilsStateStruct.logicalChanNo[autoIncrementHandle->startChannelIdIn + channelCnt];
                    edmaResourcesIn.baseParam[channelCnt]       = gDmaUtilsStateStruct.baseParam[autoIncrementHandle->startChannelIdIn + channelCnt];
                    edmaResourcesIn.tccVal[channelCnt]       = (uint8_t)gDmaUtilsStateStruct.tccVal[autoIncrementHandle->startChannelIdIn + channelCnt];

                }
                status = DMA_resourceAllocator_deallocateResources(gEdmaCc, &edmaResourcesIn);


                /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
                /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
                /* Status will never be 0 because we are passing all the correct parameters to the function above and hence all the error conditions inside the function
                will never occur.*/
                if ( status == 0 )
                {
                    DMA_utils_freeStateStruct( autoIncrementHandle->startChannelIdIn,  autoIncrementHandle->numInTransfers );
                }
                /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */

                for ( channelCnt = 0 ; channelCnt < edmaResourcesOut.numChannels ; channelCnt++ )
                {
                    edmaResourcesOut.numParam[channelCnt]    = 1U;
                    edmaResourcesOut.dmaAttr[channelCnt]     = DMA_CHAN_ATTR_EDMA;
                    edmaResourcesOut.queNo[channelCnt]       =
                        autoIncrementHandle->transferProp[transferCntOffset + channelCnt].dmaQueNo;

                    edmaResourcesOut.logicalChannelNo[channelCnt] = (uint8_t)gDmaUtilsStateStruct.logicalChanNo[autoIncrementHandle->startChannelIdOut + channelCnt];
                    edmaResourcesOut.baseParam[channelCnt]       = gDmaUtilsStateStruct.baseParam[autoIncrementHandle->startChannelIdOut + channelCnt];
                    edmaResourcesOut.tccVal[channelCnt]       = (uint8_t)gDmaUtilsStateStruct.tccVal[autoIncrementHandle->startChannelIdOut + channelCnt];

                }
                if ( status == 0 )
                {
                    status = DMA_resourceAllocator_deallocateResources(gEdmaCc, &edmaResourcesOut);
                }

                /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
                /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
                /* Status will never be 0 because we are passing all the correct parameters to the function above and hence all the error conditions inside the function
                will never occur.*/
                if ( status == 0 )
                {
                    DMA_utils_freeStateStruct( autoIncrementHandle->startChannelIdOut,  autoIncrementHandle->numOutTransfers);
                }
                /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */
                break;
            default :
#ifdef DEBUG
                printf("Invalid Transfer Type \n");
#endif
                status = -1;
                break;
        }
    }
    return status;
}

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement1D_isDone
 *
 *  @desc   This function checks for the DMA transfer to be completed or not.
 *          It can be used for any of the above trigger.
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          DMA utils handle for the scatter gather usecase.
 *                  transferType :
 *                           Type of transfer that you want to configure ( IN, OUT or INOUT)
 *                           Refer to EDMA_UTILS_TRANSFER_TYPE enum for valid values
 *
 *  @outputs NONE
 *
 *  @return    0 : Transfer not completed
 *             1 : Transfer completed
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement1D_isDone(void * autoIncrementContext, uint32_t transferType)
{
  /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
  /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
  /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
  The address space is 32 bit and type casting to integer will not result into any loss because of TI's
  compiler teratment to integer.   */
  const CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)edmaBase[0];
  /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

  EDMA_UTILS_autoIncrement1D_context * autoIncrementHandle = (EDMA_UTILS_autoIncrement1D_context *)autoIncrementContext;
  int32_t            status = 0;
  uint32_t waitWord =0;

  switch (transferType)
  {
    case EDMA_UTILS_TRANSFER_IN:
        waitWord                         = autoIncrementHandle->waitWordIn;
        break;
    case EDMA_UTILS_TRANSFER_OUT:
        waitWord                         = autoIncrementHandle->waitWordOut;
        break;
    case EDMA_UTILS_TRANSFER_INOUT:
        waitWord                         = autoIncrementHandle->waitWordIn | autoIncrementHandle->waitWordOut;
        break;
    default :
#ifdef DEBUG
        printf("Invalid Transfer Type \n");
#endif
        status = -1;
        break;
  }


#ifdef HOST_EMULATION

#else
    if((gEdmaCc->IPR & (waitWord)) == waitWord)
    {
        status = 1;
    }
#endif

return status;
}

