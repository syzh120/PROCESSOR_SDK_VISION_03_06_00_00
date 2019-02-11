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

#include "edma_utils_autoincrement_int.h"
#include "edma_utils_autoincrement.h"
#include "dma_resource_allocator.h"
#include "dma_funcs.h"
#include "edma_utils_state.h"
#include "edma_utils_context_size.h"
#include "edma_utils.h"

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define CEIL(x,y) ((( (x) + (y) - 1U) / (y)) * (y))
/* RESET_MISRA("19.7")  -> Reset rule 19.7  */




extern DMA_utilsStateStruct gDmaUtilsStateStruct;         /**< EDMA state structure */
/**< Pointer to the start of EDMA CC0 */
#ifdef HOST_EMULATION
extern uint32_t edmaBase[1];
#else
extern const volatile  uint32_t edmaBase[1];
#endif


#ifdef HOST_EMULATION

static void DMA_SUBMIT_host(CSL_EdmaccRegsOvly edmaCc , uint32_t submit_word)
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
    volatile uint32_t * trigParam;

    for ( shift = 0 ; shift < 32 ; shift++ )
    {
        if ( (submit_word >> shift ) & 0x1)
        {
            trigParam = gDmaUtilsStateStruct.baseParam[shift];
            noBytes = (trigParam[2] & 0x0000FFFFu);
            noLines = ((trigParam[2]) >> 16u);
            srcLinePitch = trigParam[4] & 0x0000FFFFu;
            dstLinePitch = trigParam[4] >>16;
            cCnt = trigParam[7] & 0x0000FFFFu;
            srcCidx = trigParam[6] & 0x0000FFFFu;
            dstCidx = trigParam[6] >> 16u;
            srcPtr  = (uint8_t *)trigParam[1];
            dstPtr  = (uint8_t *)trigParam[3];

            for (rowCnt = 0 ; rowCnt < noLines; rowCnt++)
            {
                memcpy (dstPtr + rowCnt * dstLinePitch, srcPtr + rowCnt * srcLinePitch, noBytes);
            }
            srcPtr  = (uint8_t *)trigParam[1] + srcCidx;
            dstPtr  = (uint8_t *)trigParam[3] + dstCidx;

            trigParam[1] = (uint32_t)srcPtr;
            trigParam[3] = (uint32_t)dstPtr;
            trigParam[7] = (cCnt-1) & 0x0000FFFFu;
        }
    }

}

static void DMA_WAIT_host(CSL_EdmaccRegsOvly edmaCc , uint32_t wait_word)
{
    return;
}

#endif

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_getContextSize
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
int32_t EDMA_UTILS_autoIncrement_getContextSize(void)
{
    int32_t size;

    size = sizeof(EDMA_UTILS_autoIncrement_context);

    return size;
}

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_initializeContext
 *
 *  @desc     This function is an internal routine to initialize some of the variables
 *            inside autoincrement context
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                    EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                    by user by first getting the size using EDMA_UTILS_autoIncrement_getContextSize.
 *
 *  @outputs NONE
 *
 *  @return  NONE
 *
 *  =======================================================
 */
static void  EDMA_UTILS_autoIncrement_initializeContext(void * autoIncrementContext);
static void  EDMA_UTILS_autoIncrement_initializeContext(void * autoIncrementContext)
{
    EDMA_UTILS_autoIncrement_context * autoIncrementHandle = (EDMA_UTILS_autoIncrement_context *)autoIncrementContext;

    autoIncrementHandle->blkHorzIdxIn     = 0;
    autoIncrementHandle->blkVertIdxIn     = 0;
    autoIncrementHandle->blkVertIdxOut    = 0;
    autoIncrementHandle->blkHorzIdxOut    = -1;
    autoIncrementHandle->numInTransfers   = 0;
    autoIncrementHandle->numOutTransfers  = 0;
    autoIncrementHandle->submitWordIn     = 0;
    autoIncrementHandle->submitWordOut    = 0;
    autoIncrementHandle->waitWordIn       = 0;
    autoIncrementHandle->waitWordOut      = 0;

    return ;
}


/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_init
 *
 *  @desc     This function initializes the EDMA UTILS context for autoincrement usecase.
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement_getContextSize.
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
int32_t EDMA_UTILS_autoIncrement_init(void * autoIncrementContext ,const EDMA_UTILS_autoIncrement_initParam * initParams)
{
    EDMA_UTILS_autoIncrement_context * autoIncrementHandle = (EDMA_UTILS_autoIncrement_context *)autoIncrementContext;
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
    contextSize = sizeof(EDMA_UTILS_autoIncrement_context);

    /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
    /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
    /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
    /*  UNREACH.GEN :   Unreachable code  */
    /* Below condition will currently never fail and hence code is unreachable but
    as the implementation of the function changes contextSize and the macro defined can be different
    this error check is to catch such mismatch*/
    if (  (contextSize) != EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE )
    {
#ifdef DEBUG
        printf("Autoincrement context size is not correct, it should be %d \n" ,
            sizeof(EDMA_UTILS_autoIncrement_context));
#endif
        status = -1;
    }
    /*RESET_MISRA("14.1")  -> Reset rule 14.1 for  UNREACH.GEN */
    /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */

    if ( status == 0 )
    {
        if ( (initParams->transferType == EDMA_UTILS_TRANSFER_IN) || (initParams->transferType == EDMA_UTILS_TRANSFER_INOUT))
        {
            /* Reset internal variables of autoincrement context */
            EDMA_UTILS_autoIncrement_initializeContext(autoIncrementHandle);
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
        /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
        /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
        /* Below condition will currently never fail and hence code is unreachable but
           as the implementation of the function changes contextSize and the macro defined can be different
           this error check is to catch such mismatch*/
        if ( status == 0 )
        {
        /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */
            for ( transferCnt = 0; transferCnt < numTransfers; transferCnt++)
            {
                actualTransferCnt = transferCnt+transferCntOffset;

                autoIncrementHandle->transferProp[actualTransferCnt].roiWidth
                                        = initParams->transferProp[transferCnt].roiWidth;

                autoIncrementHandle->transferProp[actualTransferCnt].roiHeight
                                        = initParams->transferProp[transferCnt].roiHeight;

                autoIncrementHandle->transferProp[actualTransferCnt].blkWidth
                                        = initParams->transferProp[transferCnt].blkWidth;

                autoIncrementHandle->transferProp[actualTransferCnt].blkHeight
                                        = initParams->transferProp[transferCnt].blkHeight;

                autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementX
                                        = initParams->transferProp[transferCnt].extBlkIncrementX;

                autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementY
                                        = initParams->transferProp[transferCnt].extBlkIncrementY;

                autoIncrementHandle->transferProp[actualTransferCnt].intBlkIncrementX
                                        = initParams->transferProp[transferCnt].intBlkIncrementX;

                autoIncrementHandle->transferProp[actualTransferCnt].intBlkIncrementY
                                        = initParams->transferProp[transferCnt].intBlkIncrementY;

                autoIncrementHandle->transferProp[actualTransferCnt].roiOffset
                                        = initParams->transferProp[transferCnt].roiOffset;

                autoIncrementHandle->transferProp[actualTransferCnt].extMemPtr
                                        = initParams->transferProp[transferCnt].extMemPtr;

                autoIncrementHandle->transferProp[actualTransferCnt].interMemPtr
                                        = initParams->transferProp[transferCnt].interMemPtr;

                autoIncrementHandle->transferProp[actualTransferCnt].extMemPtrStride
                                        = initParams->transferProp[transferCnt].extMemPtrStride;

                autoIncrementHandle->transferProp[actualTransferCnt].interMemPtrStride
                                        = initParams->transferProp[transferCnt].interMemPtrStride;

                autoIncrementHandle->transferProp[actualTransferCnt].dmaQueNo
                                        = initParams->transferProp[transferCnt].dmaQueNo;

            }
        }
    }

    return status;

}

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_configure
 *
 *  @desc   This function configures autoincrement usecase. This function can be called
 *               separately for IN and OUT channels or can also be called together for both INOUT channel.
 *              This functions behavior is undefined if you configure OUT transfer first followed by IN channel
 *              or if you configure IN and OUT transfer multiple number of times
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
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
int32_t EDMA_UTILS_autoIncrement_configure(void * autoIncrementContext , uint32_t transferType)
{
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    const CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)edmaBase[0];
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

    EDMA_UTILS_autoIncrement_context * autoIncrementHandle = (EDMA_UTILS_autoIncrement_context *)autoIncrementContext;
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
    uint32_t             channelCnt;
    uint16_t      numBlkHorz , numBlkVert;

    if ( autoIncrementHandle == NULL )
    {
#ifdef DEBUG
        printf("Null Pointer\n");
#endif

        status = -1;
    }

    if ( status == 0 )
    {
        /* Reset internal variables of autoincrement context */
        autoIncrementHandle->blkHorzIdxIn     = 0;
        autoIncrementHandle->blkVertIdxIn     = 0;
        autoIncrementHandle->blkVertIdxOut    = 0;
        autoIncrementHandle->blkHorzIdxOut    = -1;

        /* Calculate the number of vertical and horizontal block based on the first entry.
        Later will check if all the entries are having same number of vertical and horizontal blocks */
        if ( (autoIncrementHandle->transferProp[0].extBlkIncrementX != 0) &&
              (autoIncrementHandle->transferProp[0].blkWidth < autoIncrementHandle->transferProp[0].roiWidth))
        {
            autoIncrementHandle->numBlkHorz = ((autoIncrementHandle->transferProp[0].roiWidth -
                                                autoIncrementHandle->transferProp[0].blkWidth - 1U) /
                                                autoIncrementHandle->transferProp[0].extBlkIncrementX ) +
                                                (uint16_t)2U;
        }
        else
        {
             autoIncrementHandle->numBlkHorz = 1U;
        }

        if (  (autoIncrementHandle->transferProp[0].extBlkIncrementY != 0 ) &&
              (autoIncrementHandle->transferProp[0].blkHeight < autoIncrementHandle->transferProp[0].roiHeight))
        {
            autoIncrementHandle->numBlkVert = ((autoIncrementHandle->transferProp[0].roiHeight -
                                                autoIncrementHandle->transferProp[0].blkHeight - 1U) /
                                                autoIncrementHandle->transferProp[0].extBlkIncrementY ) +
                                                (uint16_t)2U;
        }
        else
        {
             autoIncrementHandle->numBlkVert = autoIncrementHandle->transferProp[0].roiHeight/autoIncrementHandle->transferProp[0].blkHeight;
        }
        /* Request resources based on number of transfers and user settings */
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
                /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
                /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
                /* Status will never be 0 because we are passing all the correct parameters to the function above and hence all the error conditions inside the function
                will never occur.*/
                status = DMA_funcs_hardwareRegSetup(gEdmaCc ,&edmaResourcesIn);
                if ( status == 0)
                {
                    status = DMA_utils_updateStateStruct(&edmaResourcesIn,
                                    &autoIncrementHandle->startChannelIdIn);
                }
                /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */
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
            syncDim    =  CSL_EDMACC_OPT_SYNCDIM_ABSYNC;
            dam        =  CSL_EDMACC_OPT_DAM_INCR;
            sam        =  CSL_EDMACC_OPT_SAM_INCR;

            if (( transferType == EDMA_UTILS_TRANSFER_IN ) ||
                        ( transferType == EDMA_UTILS_TRANSFER_INOUT))
            {
                for ( transferCnt = 0; transferCnt < autoIncrementHandle->numInTransfers ; transferCnt++ )
                {
                    actualTransferCnt = transferCnt;
                    if ( (autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementX != 0) &&
                          (autoIncrementHandle->transferProp[actualTransferCnt].blkWidth <
                           autoIncrementHandle->transferProp[actualTransferCnt].roiWidth))
                    {
                        numBlkHorz = ((autoIncrementHandle->transferProp[actualTransferCnt].roiWidth -
                         autoIncrementHandle->transferProp[actualTransferCnt].blkWidth - 1U) /
                         autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementX ) +
                         (uint16_t)2U;
                    }
                    else
                    {
                        numBlkHorz = autoIncrementHandle->numBlkHorz;

                    }

                    if ( (autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementY != 0 ) &&
                         (autoIncrementHandle->transferProp[actualTransferCnt].blkHeight <
                          autoIncrementHandle->transferProp[actualTransferCnt].roiHeight))
                    {
                        numBlkVert = ((autoIncrementHandle->transferProp[actualTransferCnt].roiHeight -
                          autoIncrementHandle->transferProp[actualTransferCnt].blkHeight - 1U) /
                          autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementY ) +
                          (uint16_t)2U;
                    }
                    else
                    {
                        numBlkVert = autoIncrementHandle->numBlkVert;
                    }
                    if ( ( numBlkHorz != autoIncrementHandle->numBlkHorz ) || ( numBlkVert != autoIncrementHandle->numBlkVert ) )
                    {
#ifdef DEBUG
                        printf("Ratio of all ROI width/height with Block width/height are not the same \n");
#endif
                        status = -1;
                        break;
                    }

                    aCNT = autoIncrementHandle->transferProp[actualTransferCnt].blkWidth;
                    bCNT = autoIncrementHandle->transferProp[actualTransferCnt].blkHeight;
                    cCNT = autoIncrementHandle->numBlkHorz;
                    autoIncrementHandle->blkWidthLast[actualTransferCnt] =
                         autoIncrementHandle->transferProp[actualTransferCnt].roiWidth -
                        (autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementX*(autoIncrementHandle->numBlkHorz - (uint16_t)1U));
                    if(autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementY != 0)
                    {
                      autoIncrementHandle->blkHeightLast[actualTransferCnt] =
                        autoIncrementHandle->transferProp[actualTransferCnt].roiHeight -
                        (autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementY*(autoIncrementHandle->numBlkVert - (uint16_t)1U));
                    }
                    else
                    {
                      autoIncrementHandle->blkHeightLast[actualTransferCnt] =
                               autoIncrementHandle->transferProp[actualTransferCnt].blkHeight;
                    }
                    tcc        = (uint32_t)gDmaUtilsStateStruct.tccVal[transferCnt +
                                    autoIncrementHandle->startChannelIdIn];

                    /* ------------------------------------------------------------- */
                    /* Options field calculation for the EDMA transfer.              */
                    /* ------------------------------------------------------------- */

                    opt =
                        CSL_EDMA_OPT_MAKE
                        (itccEn,tccEn,itcintEn,tcintEn,tcc,tccMode,fwid,stat,syncDim,dam,sam);

                    autoIncrementHandle->submitWordIn  |=
                                        (uint32_t)0x1U  <<
                                        gDmaUtilsStateStruct.logicalChanNo[transferCnt +
                                        autoIncrementHandle->startChannelIdIn];

                    autoIncrementHandle->waitWordIn    |=
                                        (uint32_t)0x1U <<
                                        gDmaUtilsStateStruct.tccVal[transferCnt +
                                        autoIncrementHandle->startChannelIdIn];

                    /* Configure trig param for channel In
                           Source is external memory
                           Destination is internal memory */

                    DMA_funcs_writeTransferParams
                    (
                        gDmaUtilsStateStruct.baseParam[transferCnt + autoIncrementHandle->startChannelIdIn],
                        opt ,
                        /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
                        /* MISRA.PTR.ARITH:  Pointer is used in arithmetic or array index expression  */
                        /*  Pointer below are allocated by user and hence we dont know the bound at this level. The harmful side effect of voilating this
                        rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
                        autoIncrementHandle->transferProp[actualTransferCnt].extMemPtr +
                        autoIncrementHandle->transferProp[actualTransferCnt].roiOffset,
                        /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */
                        autoIncrementHandle->transferProp[actualTransferCnt].interMemPtr,
                        aCNT , bCNT,
                        autoIncrementHandle->transferProp[actualTransferCnt].extMemPtrStride,
                        autoIncrementHandle->transferProp[actualTransferCnt].interMemPtrStride,
                        autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementX,
                        autoIncrementHandle->transferProp[actualTransferCnt].intBlkIncrementX,
                        cCNT + 1U,/* Adding 1 so that once a block row is finished we dont
                                want complete trig params to be zero */
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

                    if ( (autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementX != 0) &&
                         (autoIncrementHandle->transferProp[actualTransferCnt].blkWidth <
                          autoIncrementHandle->transferProp[actualTransferCnt].roiWidth))
                    {
                        numBlkHorz = ((autoIncrementHandle->transferProp[actualTransferCnt].roiWidth -
                                                  autoIncrementHandle->transferProp[actualTransferCnt].blkWidth - 1U) /
                                                  autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementX ) +
                                                  (uint16_t)2U;
                    }
                    else
                    {
                        numBlkHorz = autoIncrementHandle->numBlkHorz;

                    }

                    if ( (autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementY != 0 ) &&
                         (autoIncrementHandle->transferProp[actualTransferCnt].blkHeight <
                          autoIncrementHandle->transferProp[actualTransferCnt].roiHeight))
                    {
                        numBlkVert = ((autoIncrementHandle->transferProp[actualTransferCnt].roiHeight -
                                                  autoIncrementHandle->transferProp[actualTransferCnt].blkHeight - 1U) /
                                                  autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementY ) +
                                                  (uint16_t)2U;
                    }
                    else
                    {
                        numBlkVert = autoIncrementHandle->numBlkVert;
                    }
                    if ( ( numBlkHorz != autoIncrementHandle->numBlkHorz ) || ( numBlkVert != autoIncrementHandle->numBlkVert ) )
                    {
#ifdef DEBUG
                        printf("Ratio of all ROI width/height with Block width/height are not the same \n");
#endif
                        status = -1;
                        break;
                    }
                    aCNT = autoIncrementHandle->transferProp[actualTransferCnt].blkWidth;
                    bCNT = autoIncrementHandle->transferProp[actualTransferCnt].blkHeight;
                    cCNT = autoIncrementHandle->numBlkHorz;
                    autoIncrementHandle->blkWidthLast[actualTransferCnt] =
                         autoIncrementHandle->transferProp[actualTransferCnt].roiWidth -
                        (autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementX*(autoIncrementHandle->numBlkHorz - (uint16_t)1U));
                    if(autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementY != 0)
                    {
                      autoIncrementHandle->blkHeightLast[actualTransferCnt] =
                         autoIncrementHandle->transferProp[actualTransferCnt].roiHeight -
                        (autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementY*(autoIncrementHandle->numBlkVert - (uint16_t)1U));
                    }
                    else
                    {
                      autoIncrementHandle->blkHeightLast[actualTransferCnt] = autoIncrementHandle->transferProp[actualTransferCnt].blkHeight;
                    }
                    tcc        = (uint32_t)gDmaUtilsStateStruct.tccVal[transferCnt +
                                    autoIncrementHandle->startChannelIdOut];

                    /* ------------------------------------------------------------- */
                    /* Options field calculation for the EDMA transfer.              */
                    /* ------------------------------------------------------------- */
                    opt =
                        (uint32_t)CSL_EDMA_OPT_MAKE
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

                    DMA_funcs_writeTransferParams
                    (
                        gDmaUtilsStateStruct.baseParam[transferCnt + autoIncrementHandle->startChannelIdOut],
                        opt ,
                        autoIncrementHandle->transferProp[actualTransferCnt].interMemPtr,
                        /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
                        /* MISRA.PTR.ARITH:  Pointer is used in arithmetic or array index expression  */
                        /*  Pointer below are allocated by user and hence we dont know the bound at this level. The harmful side effect of voilating this
                        rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
                        autoIncrementHandle->transferProp[actualTransferCnt].extMemPtr +
                        autoIncrementHandle->transferProp[actualTransferCnt].roiOffset,
                        /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */
                        aCNT , bCNT,
                        autoIncrementHandle->transferProp[actualTransferCnt].interMemPtrStride,
                        autoIncrementHandle->transferProp[actualTransferCnt].extMemPtrStride,
                        autoIncrementHandle->transferProp[actualTransferCnt].intBlkIncrementX,
                        autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementX,
                        cCNT + 1U,/* Adding 1 so that once a block row is finished we dont
                                want complete trig params to be zero */
                        0           /* No linking*/
                    );
                }
            }
        }
    }

    if ( status == 0 )
    {
        autoIncrementHandle->numTotalBlk = autoIncrementHandle->numBlkHorz * autoIncrementHandle->numBlkVert;
    }
    return status;
}

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_update
 *
 *  @desc   This function updates a certain set of parameters of autoincrement usecase.
 *               This function can only be called after EDMA_UTILS_autoIncrement_configure
 *               has been called. Size of array update param should be same as what has already been
 *               configured for IN, OUT or INOUT transfer in EDMA_UTILS_autoIncrement_configure otherwise
 *               this function will return an error. This function only updates the internal context and not actually
 *              update the param set. Param set is updated when the next frame starts.
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement_getContextSize.
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
int32_t EDMA_UTILS_autoIncrement_update(void * autoIncrementContext, const EDMA_UTILS_autoIncrement_updateParams *updateParams)
{
    EDMA_UTILS_autoIncrement_context * autoIncrementHandle = (EDMA_UTILS_autoIncrement_context *)autoIncrementContext;
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
            if ( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIWIDTH) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].roiWidth
                                    = updateParams->updateParams[transferCnt].roiWidth;
            }

            if ( (updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIHEGIHT) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].roiHeight
                                    = updateParams->updateParams[transferCnt].roiHeight;
            }
            if ( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_BLOCKWIDTH) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].blkWidth
                                    = updateParams->updateParams[transferCnt].blkWidth;
            }
            if ( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_BLOCKHEIGHT) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].blkHeight
                                    = updateParams->updateParams[transferCnt].blkHeight;
            }

            if ( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTBLKINCREMENTX) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementX
                                    = updateParams->updateParams[transferCnt].extBlkIncrementX;
            }

            if ( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTBLKINCREMENTY) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementY
                                    = updateParams->updateParams[transferCnt].extBlkIncrementY;
            }

            if ( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_INTBLKINCREMENTX) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].intBlkIncrementX
                                    = updateParams->updateParams[transferCnt].intBlkIncrementX;
            }

            if ( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_INTBLKINCREMENTY) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].intBlkIncrementY
                                    = updateParams->updateParams[transferCnt].intBlkIncrementY;
            }

            if ( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIOFFSET) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].roiOffset
                                    = updateParams->updateParams[transferCnt].roiOffset;
            }

            if ( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].extMemPtr
                                    = updateParams->updateParams[transferCnt].extMemPtr;
            }

            if ( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_INTERMEMPTR) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].interMemPtr
                                    = updateParams->updateParams[transferCnt].interMemPtr;
            }

            if ( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].extMemPtrStride
                                    = updateParams->updateParams[transferCnt].extMemPtrStride;
            }

            if ( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_INTERMEMPTRSTRIDE) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].interMemPtrStride
                                    = updateParams->updateParams[transferCnt].interMemPtrStride;
            }
            if ( ( updateParams->updateMask & (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_DMAQUENO) != 0)
            {
              autoIncrementHandle->transferProp[actualTransferCnt].dmaQueNo
                                    = updateParams->updateParams[transferCnt].dmaQueNo;
            }

        }

    }

    return status;
}

/* ==================================================
 *  @func     EDMA_UTILS_autoIncrement_triggerInChannel
 *
 *  @desc   This function triggers all Input channels together
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement_getContextSize.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement_triggerInChannel(void * autoIncrementContext)
{
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    const CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)edmaBase[0];
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

    EDMA_UTILS_autoIncrement_context * autoIncrementHandle = (EDMA_UTILS_autoIncrement_context *)autoIncrementContext;
    uint32_t            transferCnt = 0;
    volatile uint32_t   (*tparam)[8];
    int32_t             extPtrOffset;
    int32_t             intPtrOffset;
    uint16_t            autoIncrCnt;
    uint8_t             *extMemPtr;
    uint8_t             *intMemPtr;
    int32_t             status = 0;

#ifdef DEBUG
    if ( autoIncrementHandle )
#endif
    {
        if(autoIncrementHandle->blkVertIdxIn < autoIncrementHandle->numBlkVert)
        {
            uint16_t aCNT, bCNT;
            if (autoIncrementHandle->blkHorzIdxIn == 0 )
            {
               for ( transferCnt = 0 ; transferCnt < autoIncrementHandle->numInTransfers ; transferCnt++ )
                {
                    autoIncrCnt  = autoIncrementHandle->numBlkHorz;
                    extPtrOffset = ( autoIncrementHandle->transferProp[transferCnt].extBlkIncrementY *
                                    autoIncrementHandle->transferProp[transferCnt].extMemPtrStride *
                                    autoIncrementHandle->blkVertIdxIn ) +
                                    autoIncrementHandle->transferProp[transferCnt].roiOffset;

                    intPtrOffset   = autoIncrementHandle->transferProp[transferCnt].intBlkIncrementY *
                                    autoIncrementHandle->transferProp[transferCnt].interMemPtrStride *
                                    autoIncrementHandle->blkVertIdxIn;

                    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
                    /* MISRA.PTR.ARITH:  Pointer is used in arithmetic or array index expression  */
                    /*  Pointer below are allocated by user and hence we dont know the bound at this level. The harmful side effect of voilating this
                    rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
                    extMemPtr      = autoIncrementHandle->transferProp[transferCnt].extMemPtr +
                                        extPtrOffset;

                    intMemPtr      = autoIncrementHandle->transferProp[transferCnt].interMemPtr +
                                        intPtrOffset;
                    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

                    tparam      = (volatile uint32_t (*)[8])(volatile void *)gDmaUtilsStateStruct.baseParam[transferCnt +
                                            autoIncrementHandle->startChannelIdIn];

                    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
                    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
                    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
                    The address space is 32 bit and type casting to integer will not result into any loss because of TI's compiler teratment to integer.   */

                    /* ------------------------------------------------------------- */
                    /* Assign pointer values to their associated PARAM ram entries   */
                    /* ------------------------------------------------------------- */
                    (*tparam)[1]  =    (uint32_t) extMemPtr;
                    /* ------------------------------------------------------------- */
                    /* Assign intermem pointer values to their associated PARAM ram entries   */
                    /* ------------------------------------------------------------- */
                    (*tparam)[3]  =    (uint32_t) intMemPtr;
                    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

                    /* ------------------------------------------------------------- */
                    /* Refill C Count                                                */
                    /* ------------------------------------------------------------- */
                    (*tparam)[7]  =    (uint32_t)2U * autoIncrCnt;
                    if (autoIncrementHandle->blkVertIdxIn == (autoIncrementHandle->numBlkVert-1U) )
                    {
                        bCNT = autoIncrementHandle->blkHeightLast[transferCnt];
                    }
                    else
                    {
                        bCNT = autoIncrementHandle->transferProp[transferCnt].blkHeight;
                    }
                    aCNT = autoIncrementHandle->transferProp[transferCnt].blkWidth;
                    (*tparam)[2]  =    (uint32_t) pack2(bCNT, aCNT);
                }
            }
            if (autoIncrementHandle->blkHorzIdxIn == (autoIncrementHandle->numBlkHorz-1))
            {
               for ( transferCnt = 0 ; transferCnt < autoIncrementHandle->numInTransfers ; transferCnt++ )
                {
                    tparam      = (volatile uint32_t (*)[8])(volatile void *)gDmaUtilsStateStruct.baseParam[transferCnt +
                                            autoIncrementHandle->startChannelIdIn];
                    aCNT = autoIncrementHandle->blkWidthLast[transferCnt];
                    if (autoIncrementHandle->blkVertIdxIn == (autoIncrementHandle->numBlkVert-1U) )
                    {
                        bCNT = autoIncrementHandle->blkHeightLast[transferCnt];
                    }
                    else
                    {
                        bCNT = autoIncrementHandle->transferProp[transferCnt].blkHeight;
                    }
                    (*tparam)[2]  =    (uint32_t) pack2(bCNT, aCNT);
                }
            }

#ifdef HOST_EMULATION
    DMA_SUBMIT_host(gEdmaCc , autoIncrementHandle->submitWordIn);
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
 *  @func     EDMA_UTILS_autoIncrement_triggerOutChannel
 *
 *  @desc   This function triggers all Output channels together. It also indicates when the last
 *              block is reached in the ROI given by user.
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement_getContextSize.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *                  1 : Last Block in auto increment
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement_triggerOutChannel(void * autoIncrementContext)
{
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    const CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)edmaBase[0];
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

    EDMA_UTILS_autoIncrement_context * autoIncrementHandle = (EDMA_UTILS_autoIncrement_context *)autoIncrementContext;
    uint32_t            transferCnt = 0;
    volatile uint32_t   (*tparam)[8];
    uint16_t            autoIncrCnt;
    int32_t             extPtrOffset;
    int32_t             intPtrOffset;
    uint8_t             *extMemPtr;
    uint8_t             *intMemPtr;
    uint32_t            numInTransfers;
    uint32_t            actualTransferCnt;
    int32_t            status = 0;
#ifdef DEBUG
    if ( autoIncrementHandle )
#endif
    {
        if (autoIncrementHandle->blkHorzIdxOut >=0 )
        {
            uint16_t aCNT, bCNT;
            if (autoIncrementHandle->blkHorzIdxOut == 0 )
            {
                numInTransfers = autoIncrementHandle->numInTransfers ;

                for ( transferCnt = 0 ; transferCnt < autoIncrementHandle->numOutTransfers; transferCnt++ )
                {
                    actualTransferCnt = transferCnt + numInTransfers;
                    autoIncrCnt = autoIncrementHandle->numBlkHorz;
                    extPtrOffset  = ( autoIncrementHandle->transferProp[actualTransferCnt].extBlkIncrementY *
                                  autoIncrementHandle->transferProp[actualTransferCnt].extMemPtrStride *
                                  autoIncrementHandle->blkVertIdxOut ) +
                                    autoIncrementHandle->transferProp[actualTransferCnt].roiOffset;

                    intPtrOffset = autoIncrementHandle->transferProp[actualTransferCnt].intBlkIncrementY *
                                    autoIncrementHandle->transferProp[actualTransferCnt].interMemPtrStride *
                                    autoIncrementHandle->blkVertIdxOut;

                    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
                    /* MISRA.PTR.ARITH:  Pointer is used in arithmetic or array index expression  */
                    /*  Pointer below are allocated by user and hence we dont know the bound at this level. The harmful side effect of voilating this
                    rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */

                    extMemPtr   = autoIncrementHandle->transferProp[actualTransferCnt].extMemPtr +
                                        extPtrOffset;

                    intMemPtr      = autoIncrementHandle->transferProp[actualTransferCnt].interMemPtr +
                                        intPtrOffset;

                    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */


                    tparam      = (volatile uint32_t (*)[8])(volatile void *)gDmaUtilsStateStruct.baseParam[transferCnt +
                                        autoIncrementHandle->startChannelIdOut];

                    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
                    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
                    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
                    The address space is 32 bit and type casting to integer will not result into any loss because of TI's compiler teratment to integer.   */
                    /* ------------------------------------------------------------- */
                    /* Assign internal mem pointer values to their associated PARAM ram entries   */
                    /* ------------------------------------------------------------- */
                    (*tparam)[1]  =    (uint32_t) intMemPtr;

                    /* ------------------------------------------------------------- */
                    /* Assign pointer values to their associated PARAM ram entries   */
                    /* ------------------------------------------------------------- */
                    (*tparam)[3]  =    (uint32_t) extMemPtr;
                    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

                    /* ------------------------------------------------------------- */
                    /* Refill C Count                                                */
                    /* ------------------------------------------------------------- */
                    (*tparam)[7]  =    (uint32_t)2U * autoIncrCnt;
                    if (autoIncrementHandle->blkVertIdxOut == (autoIncrementHandle->numBlkVert-1U) )
                    {
                        bCNT = autoIncrementHandle->blkHeightLast[actualTransferCnt];
                    }
                    else
                    {
                        bCNT = autoIncrementHandle->transferProp[actualTransferCnt].blkHeight;
                    }
                    aCNT = autoIncrementHandle->transferProp[actualTransferCnt].blkWidth;
                    (*tparam)[2]  =    (uint32_t) pack2(bCNT, aCNT);
                }
            }
            if ( autoIncrementHandle->blkHorzIdxOut == (autoIncrementHandle->numBlkHorz-1) )
            {
                numInTransfers = autoIncrementHandle->numInTransfers ;

                for ( transferCnt = 0 ; transferCnt < autoIncrementHandle->numOutTransfers ; transferCnt++ )
                {
                    actualTransferCnt = transferCnt + numInTransfers;
                    tparam      = (volatile uint32_t (*)[8])(volatile void *)gDmaUtilsStateStruct.baseParam[transferCnt +
                                            autoIncrementHandle->startChannelIdOut];
                    aCNT = autoIncrementHandle->blkWidthLast[actualTransferCnt];
                    if (autoIncrementHandle->blkVertIdxOut == (autoIncrementHandle->numBlkVert-1U) )
                    {
                        bCNT = autoIncrementHandle->blkHeightLast[actualTransferCnt];
                    }
                    else
                    {
                        bCNT = autoIncrementHandle->transferProp[actualTransferCnt].blkHeight;
                    }
                    (*tparam)[2]  =    (uint32_t) pack2(bCNT, aCNT);
                }
            }
#ifdef HOST_EMULATION
                DMA_SUBMIT_host(gEdmaCc , autoIncrementHandle->submitWordOut);
#else
                DMA_SUBMIT(gEdmaCc , autoIncrementHandle->submitWordOut);
#endif

        }

        if(((autoIncrementHandle->blkHorzIdxOut) +
                ( autoIncrementHandle->numBlkHorz * autoIncrementHandle->blkVertIdxOut )) >=
                (autoIncrementHandle->numTotalBlk - 2))
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
 *  @func     EDMA_UTILS_autoIncrement_waitInChannel
 *
 *  @desc   This function waits for all Input channels together
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement_getContextSize.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement_waitInChannel(void * autoIncrementContext)
{
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    const CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)edmaBase[0];
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

    EDMA_UTILS_autoIncrement_context * autoIncrementHandle = (EDMA_UTILS_autoIncrement_context *)autoIncrementContext;
    int32_t            status = 0;

#ifdef DEBUG
    if ( autoIncrementHandle)
#endif
    {
        if(autoIncrementHandle->blkVertIdxIn < autoIncrementHandle->numBlkVert)
        {

#ifdef HOST_EMULATION
            DMA_WAIT_host(gEdmaCc ,autoIncrementHandle->waitWordIn);
#else
            DMA_WAIT(gEdmaCc ,autoIncrementHandle->waitWordIn);
#endif

        }

        autoIncrementHandle->blkHorzIdxIn++;
        if(autoIncrementHandle->blkHorzIdxIn >= (autoIncrementHandle->numBlkHorz))
        {
            autoIncrementHandle->blkHorzIdxIn = 0;
            autoIncrementHandle->blkVertIdxIn++;
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
 *  @func     EDMA_UTILS_autoIncrement_waitOutChannel
 *
 *  @desc   This function waits for all output channels together
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
 *                          by user by first getting the size using EDMA_UTILS_autoIncrement_getContextSize.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_autoIncrement_waitOutChannel(void * autoIncrementContext)
{
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    const CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)edmaBase[0];
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

    EDMA_UTILS_autoIncrement_context * autoIncrementHandle = (EDMA_UTILS_autoIncrement_context *)autoIncrementContext;
    int32_t status = 0;

#ifdef DEBUG
    if ( autoIncrementHandle)
#endif
    {

        if(autoIncrementHandle->blkHorzIdxOut >= 0)
        {

#ifdef HOST_EMULATION
            DMA_WAIT_host(gEdmaCc ,autoIncrementHandle->waitWordOut);
#else
            DMA_WAIT(gEdmaCc ,autoIncrementHandle->waitWordOut);
#endif

        }

        /* ------------------------------------------------------------- */
        /* Update block position                                         */
        /* ------------------------------------------------------------- */
        autoIncrementHandle->blkHorzIdxOut++;
        if(autoIncrementHandle->blkHorzIdxOut >= (autoIncrementHandle->numBlkHorz))
        {
            autoIncrementHandle->blkHorzIdxOut = 0;
            autoIncrementHandle->blkVertIdxOut++;
            /* if vert Blk count reaches total number of vertical blocks it mean we  have reached the last block
            so reset block indexes to initial values for next call */
            if ( autoIncrementHandle->blkVertIdxOut == autoIncrementHandle->numBlkVert)
            {
                autoIncrementHandle->blkHorzIdxIn  = 0;
                autoIncrementHandle->blkVertIdxIn  = 0;
                autoIncrementHandle->blkVertIdxOut = 0;

            }
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
 *  @func     EDMA_UTILS_autoIncrement_deconfigure
 *
 *  @desc   This function deconfigures autoincrement usecase and releases all the allocated EDMA resources.
 *          This function can be called separately for IN and OUT channels or can also be called together
 *         for both INOUT channel. This functions behavior is undefined if you configure OUT transfer
 *          first followed by IN channel or if you configure IN and OUT transfer multiple number of times.
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *                  autoIncrementContext :
 *                          EDMA utils handle for autoincrement usecase. This memory is expected to be allocated
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
int32_t EDMA_UTILS_autoIncrement_deconfigure(void * autoIncrementContext , uint32_t transferType)
{
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    const CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)edmaBase[0];
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

    EDMA_UTILS_autoIncrement_context * autoIncrementHandle = (EDMA_UTILS_autoIncrement_context *)autoIncrementContext;
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
        /* Reset internal variables of autoincrement context */
        autoIncrementHandle->blkHorzIdxIn  = 0;
        autoIncrementHandle->blkVertIdxIn  = 0;
        autoIncrementHandle->blkVertIdxOut = 0;
        autoIncrementHandle->blkHorzIdxOut = -1;
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
                    edmaResourcesIn.tccVal[channelCnt]       =(uint8_t) gDmaUtilsStateStruct.tccVal[autoIncrementHandle->startChannelIdIn + channelCnt];

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
                 /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
                /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
                /* Status will never be 0 because we are passing all the correct parameters to the function above and hence all the error conditions inside the function
                will never occur.*/
                if ( status == 0 )
                {
                    status = DMA_resourceAllocator_deallocateResources(gEdmaCc, &edmaResourcesOut);
                }

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
 *  @func     EDMA_UTILS_autoIncrement_isDone
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
int32_t EDMA_UTILS_autoIncrement_isDone(void * autoIncrementContext, uint32_t transferType)
{
  /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
  /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
  /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
  The address space is 32 bit and type casting to integer will not result into any loss because of TI's
  compiler teratment to integer.   */
  const CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)edmaBase[0];
  /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

  EDMA_UTILS_autoIncrement_context * autoIncrementHandle = (EDMA_UTILS_autoIncrement_context *)autoIncrementContext;
  int32_t            status = 0;
  uint32_t waitWord = 0;

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



