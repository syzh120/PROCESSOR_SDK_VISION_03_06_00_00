/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
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
 * BAM DMA node for Binary image to list
 *
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *******************************************************************************
*/

/**
 *****************************************************************************
 * @file
 *  bin_img_to_list_bam_dma_node.c
 *
 * @brief
 *
 * @version 0.1 (Dec 2013) : First version of eve edma utils function
 *
 *****************************************************************************
*/

/*-----------------------------------------------------------------------*/
/*  Standard header includes for c environment.                          */
/*-----------------------------------------------------------------------*/

#include "algframework.h"
#include "edma_utils.h"
#include "edma_utils_autoincrement.h"
#include "edma_utils_scatterGather.h"
#include "edma_utils_context_size.h"
#include "bin_img_to_list_bam_dma_node.h"
#include "bam_common.h"

/**
  Maximum number of pixels in a block. Output requires 4 bytes per pix. Reserving 32 bytes
  for VCOP malloc header and 32 byte for buffer alignment.
*/
#define BIN_IMAGE_TO_LIST_MAX_PIXELS                 (4080U)


typedef struct
{
    uint8_t   autoIncrContext[EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE];
    uint8_t   scatterDmaContext[EDMA_UTILS_SCATTERGATHER_CONTEXT_SIZE];

    int16_t   blkIdxOut;

    uint16_t  numBlkHorz;
    uint16_t  numBlkVert;
    uint16_t  numTotalBlk;

    uint8_t  *srcPtr[1];
    uint8_t  *dstPtr[1];
    uint16_t  stride[1];
    uint16_t  blkWidth[1];
    EDMA_UTILS_scattherGather_transferProperties updateParams;
    uint8_t * interMemPtrAutoIncrement;

    uint8_t   *dstStartPtr[1];
    uint32_t  *pIntListSize;
    uint32_t  *pIntListSizePing;
    uint32_t  *pListSize;
}BIN_IMG2LIST_DMA_context;

/* Function prototypes */
static BAM_Status BIN_IMG2LIST_BAM_DMA_IN_getMemRecFunc(
                             const void *edmaArgs,
                             BAM_MemRec memRecInternal[],
                             BAM_MemRec memRecOutputDataBlock[],
                             uint8_t *numRecInternal,
                             uint8_t *numRecOutputDataBlock);

static BAM_Status BIN_IMG2LIST_BAM_DMA_IN_setMemRecFunc(
                              const BAM_MemRec *memRecInternal[],
                              const BAM_MemRec *memRecInputDataBlock[],
                              const BAM_MemRec *memRecOutputDataBlock[],
                              uint8_t numRecInternal,
                              uint8_t numRecInputDataBlock,
                              uint8_t numRecOutputDataBlock,
                              void *edmaContext,
                              const void *edmaArgs);

BAM_Status BIN_IMG2LIST_BAM_DMA_updateInDDRptr(void * edmaContext, void * params);

static BAM_Status BIN_IMG2LIST_BAM_DMA_frameInitInChannel( void * edmaContext);

static BAM_Status BIN_IMG2LIST_BAM_DMA_frameInitInChannel( void * edmaContext);

static BAM_Status BIN_IMG2LIST_BAM_DMA_OUT_getMemRecFunc(
                             const void *edmaArgs,
                             BAM_MemRec memRecInternal[],
                             BAM_MemRec memRecOutputDataBlock[],
                             uint8_t *numRecInternal,
                             uint8_t *numRecOutputDataBlock);

static BAM_Status BIN_IMG2LIST_BAM_DMA_OUT_setMemRecFunc(
                              const BAM_MemRec *memRecInternal[],
                              const BAM_MemRec *memRecInputDataBlock[],
                              const BAM_MemRec *memRecOutputDataBlock[],
                              uint8_t numRecInternal,
                              uint8_t numRecInputDataBlock,
                              uint8_t numRecOutputDataBlock,
                              void *edmaContext,
                              const void *edmaArgs);

BAM_Status BIN_IMG2LIST_BAM_DMA_frameInitOutChannel(void * edmaContext);

BAM_Status BIN_IMG2LIST_BAM_DMA_updateOutDDRptr(void * edmaContext, void * params);

BAM_Status BIN_IMG2LIST_BAM_DMA_triggerOutChannel(void * edmaContext);

BAM_Status BIN_IMG2LIST_BAM_DMA_waitOutChannel(void * edmaContext);


static BAM_Status BIN_IMG2LIST_BAM_DMA_IN_getMemRecFunc(
                             const void *edmaArgs,
                             BAM_MemRec memRecInternal[],
                             BAM_MemRec memRecOutputDataBlock[],
                             uint8_t *numRecInternal,
                             uint8_t *numRecOutputDataBlock)
{
    BAM_Status errCode = DMANODE_EDMA_ERR_SUCCESS;

    /* Not checking memRecInternal pointer since it is not used in this function */
    if ((numRecInternal == NULL) || (numRecOutputDataBlock == NULL))
    {
        PRINTF("BIN_IMG2LIST_BAM_DMA ERROR : Argument pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    if(memRecOutputDataBlock == NULL)
    {
        PRINTF("BIN_IMG2LIST_BAM_DMA ERROR : Argument pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    memRecOutputDataBlock[0].space = BAM_MEMSPACE_ANY_VCOPBUF;
    memRecOutputDataBlock[0].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;

    /* Allocate maximum size needed by this node */
    memRecOutputDataBlock[0].size = BIN_IMAGE_TO_LIST_MAX_PIXELS * sizeof(uint8_t);

    /* This node needs only one output data blocks and no internal data blocks */
    *numRecOutputDataBlock = 1U;
    *numRecInternal = 0;

EXIT:

    return errCode;
}


static BAM_Status BIN_IMG2LIST_BAM_DMA_IN_setMemRecFunc(
                              const BAM_MemRec *memRecInternal[],
                              const BAM_MemRec *memRecInputDataBlock[],
                              const BAM_MemRec *memRecOutputDataBlock[],
                              uint8_t numRecInternal,
                              uint8_t numRecInputDataBlock,
                              uint8_t numRecOutputDataBlock,
                              void *edmaContext,
                              const void *edmaArgs)
{
    BIN_IMG2LIST_DMA_context *dmaContext = (BIN_IMG2LIST_DMA_context *)edmaContext;
    EDMA_UTILS_autoIncrement_initParam initParams;

    BAM_Status errCode = DMANODE_EDMA_ERR_SUCCESS;
    uint32_t        transferCnt = 0;

    if (edmaContext == NULL)
    {
        PRINTF("BIN_IMG2LIST_BAM_DMA ERROR : Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    if (memRecOutputDataBlock == NULL)
    {
      errCode = DMANODE_EDMA_ERR_FAILED;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }


    /* Populate the internal memory pointer */
    /* Reset globalStateStruct for the first time for IN channels before configuring EDMA */
    EDMA_UTILS_globalReset();

    if(memRecOutputDataBlock[transferCnt]->base == NULL)
    {
        errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    /* initialize EDMA transfer with a dummy transfer with just internal memory pointer*/
    initParams.transferType   = EDMA_UTILS_TRANSFER_IN;
    initParams.numInTransfers = 1;
    initParams.transferProp[0].interMemPtr = (uint8_t *)memRecOutputDataBlock[transferCnt]->base;

    EDMA_UTILS_autoIncrement_init(dmaContext->autoIncrContext,&initParams);

EXIT:
    return errCode;
}


BAM_Status BIN_IMG2LIST_BAM_DMA_updateInDDRptr(void * edmaContext, void * params)
{
    BIN_IMG2LIST_DMA_context *dmaContext = (BIN_IMG2LIST_DMA_context *)edmaContext;
    EDMA_UTILS_autoIncrement_updateParams *updateParams= (EDMA_UTILS_autoIncrement_updateParams*) params;
    int32_t                 status = 0;
    BAM_Status         errCode = DMANODE_EDMA_ERR_SUCCESS;

    if (edmaContext == NULL)
    {
        PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    if (params == NULL)
    {
        PRINTF("BAM_DMA_AUTOINCREMENT ERROR : updateParams NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    updateParams->transferType = EDMA_UTILS_TRANSFER_IN;
    if ((updateParams->updateParams[0].blkWidth * updateParams->updateParams[0].blkHeight) >
                    BIN_IMAGE_TO_LIST_MAX_PIXELS)
    {
        PRINTF("BIN_IMG2LIST_BAM_DMA ERROR : Block Width or  Height is not within limits\n");
        errCode = DMANODE_EDMA_ERR_FAILED;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    if ( updateParams->updateParams[0].extBlkIncrementX != 0u)
    {
        dmaContext->numBlkHorz = ((updateParams->updateParams[0].roiWidth -
                                  updateParams->updateParams[0].blkWidth) /
                                  updateParams->updateParams[0].extBlkIncrementX ) + 1u;
    }
    else
    {
         dmaContext->numBlkHorz = 1u;
    }

    if ( updateParams->updateParams[0].extBlkIncrementY != 0u )
    {
        dmaContext->numBlkVert = ((updateParams->updateParams[0].roiHeight -
                                    updateParams->updateParams[0].blkHeight) /
                                    updateParams->updateParams[0].extBlkIncrementY ) + 1u;
    }
    else
    {
         dmaContext->numBlkVert = 1u;
    }

    status = EDMA_UTILS_autoIncrement_update(edmaContext , updateParams);
    /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
    /*Currently the function returns -1 when the edmaContext or updateParams is NULL. */
    /*However, this check is already done at the start of the function. Hence, code is currently unreachable */
    /*but as the implementation of the function changes, it will not be unreachable*/
    /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
    /*  MISRA.BOOL.INVAR.TRUE : The condition is always true  */
    /* status will never be non-zero because we are exiting */
    /* in case of failures by having checks for various contitions above */
    if ( status != 0 )
    {
        errCode = DMANODE_EDMA_ERR_FAILED;
    }
    /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */
    /* RESET_MISRA("14.1")  -> Reset rule 14.1  */
EXIT:
    return errCode;

}



static BAM_Status BIN_IMG2LIST_BAM_DMA_frameInitInChannel(void * edmaContext)
{
    BIN_IMG2LIST_DMA_context *dmaContext = (BIN_IMG2LIST_DMA_context *)edmaContext;
    int32_t                 status = 0;
    BAM_Status         errCode = DMANODE_EDMA_ERR_SUCCESS;

    if ( edmaContext == NULL)
    {
        PRINTF("BIN_IMG2LIST_BAM_DMA ERROR : Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    /* Reset globalStateStruct for every new frame for IN channels before configuring EDMA */
    EDMA_UTILS_globalReset();

    /* Reset internal variables of context */
    dmaContext->blkIdxOut = -1;
    dmaContext->numTotalBlk = dmaContext->numBlkHorz * dmaContext->numBlkVert;
    status = EDMA_UTILS_autoIncrement_configure((void *)dmaContext->autoIncrContext , EDMA_UTILS_TRANSFER_IN);

    if ( status != 0 )
    {
        errCode = DMANODE_EDMA_ERR_FAILED;
    }
EXIT:
    return errCode;
}


/********************************************************************************************/
/*                        Helper and exec functions for OUT transfer                        */
/********************************************************************************************/
static BAM_Status BIN_IMG2LIST_BAM_DMA_OUT_getMemRecFunc(
                             const void *edmaArgs,
                             BAM_MemRec memRecInternal[],
                             BAM_MemRec memRecOutputDataBlock[],
                             uint8_t *numRecInternal,
                             uint8_t *numRecOutputDataBlock)
{
    BAM_Status errCode = DMANODE_EDMA_ERR_SUCCESS;

    /* Not checking memRecInternal pointer since it is not used in this function */
    if ((numRecInternal == NULL) || (numRecOutputDataBlock == NULL))
    {
        PRINTF("BIN_IMG2LIST_BAM_DMA ERROR : Argument pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
    }

    if(errCode == DMANODE_EDMA_ERR_SUCCESS)
    {
        *numRecOutputDataBlock = 0;
        *numRecInternal = 0;
    }

    return errCode;
}


static BAM_Status BIN_IMG2LIST_BAM_DMA_OUT_setMemRecFunc(
                              const BAM_MemRec *memRecInternal[],
                              const BAM_MemRec *memRecInputDataBlock[],
                              const BAM_MemRec *memRecOutputDataBlock[],
                              uint8_t numRecInternal,
                              uint8_t numRecInputDataBlock,
                              uint8_t numRecOutputDataBlock,
                              void *edmaContext,
                              const void *edmaArgs)
{
    BIN_IMG2LIST_DMA_context *dmaContext = (BIN_IMG2LIST_DMA_context *)edmaContext;
    BAM_Status errCode = DMANODE_EDMA_ERR_SUCCESS;

    if (dmaContext == NULL)
    {
        PRINTF("BIN_IMG2LIST_BAM_DMA ERROR : Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    if( memRecInputDataBlock != NULL)
    {
        /* ------------------------------------------------------------- */
        /* Set internal memory pointers                                  */
        /* ------------------------------------------------------------- */
        if(memRecInputDataBlock[0]->base == NULL)
        {
            errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
            /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
            /* GOTO is used at error check to jump to end of function, to exit.   */
            goto EXIT;
            /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
        }
        else
        {
            dmaContext->srcPtr[0] = (uint8_t *)memRecInputDataBlock[0]->base;
            dmaContext->pIntListSizePing = (uint32_t *)memRecInputDataBlock[1]->base;
            dmaContext->pIntListSize = dmaContext->pIntListSizePing;
        }
      }
      else
      {
          errCode = DMANODE_EDMA_ERR_FAILED;
          /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
          /* GOTO is used at error check to jump to end of function, to exit.   */
          goto EXIT;
          /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }
EXIT:

    return errCode;
}





BAM_Status BIN_IMG2LIST_BAM_DMA_frameInitOutChannel(void * edmaContext)
{
    BIN_IMG2LIST_DMA_context *dmaContext = (BIN_IMG2LIST_DMA_context *)edmaContext;
    int32_t                 status = 0;
    BAM_Status         errCode = DMANODE_EDMA_ERR_SUCCESS;
    uint16_t  blkHeight[1];

    if (edmaContext == NULL)
    {
        PRINTF("BIN_IMG2LIST_BAM_DMA ERROR : Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }
    dmaContext->stride[0] = 0;
    dmaContext->blkWidth[0] = 1U;
    blkHeight[0] = 1U;
    dmaContext->updateParams.updateMask   = (EDMA_UTILS_SCATTERGATHER_UPDATE_BLOCK_W |
                                          EDMA_UTILS_SCATTERGATHER_UPDATE_DSTPTR_STRIDE);
    dmaContext->updateParams.dmaQueNo     = 1;
    dmaContext->updateParams.srcPtr       = dmaContext->srcPtr;
    dmaContext->updateParams.dstPtr       = dmaContext->dstPtr;
    dmaContext->updateParams.srcPtrStride = dmaContext->stride;
    dmaContext->updateParams.dstPtrStride = dmaContext->stride;
    dmaContext->updateParams.blkWidth     = dmaContext->blkWidth;
    dmaContext->updateParams.blkHeight    = blkHeight;
    status = EDMA_UTILS_scattherGather_init(dmaContext->scatterDmaContext, &(dmaContext->updateParams), 1U);

    if (status == 0 )
    {
      /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
      /*currently the function is hardcoded to return a value. Code is currently unreachable */
      /*but as the implementation of the function changes, it will not be unreachable*/
       status = EDMA_UTILS_scattherGather_configure(dmaContext->scatterDmaContext);
      /* RESET_MISRA("14.1")  -> Reset rule 14.1  */
    }

    if ( status != 0 )
    {
        errCode = DMANODE_EDMA_ERR_FAILED;
    }

EXIT:
    return errCode;
}


BAM_Status BIN_IMG2LIST_BAM_DMA_updateOutDDRptr(void * edmaContext, void * params)
{
    BIN_IMG2LIST_DMA_context *context = (BIN_IMG2LIST_DMA_context *)edmaContext;
    BAM_DMA_CUSTOM_BINIMG2LIST_WRITENODE_ctrlArgs * ctrlArgs =
                              (BAM_DMA_CUSTOM_BINIMG2LIST_WRITENODE_ctrlArgs *)params;
    BAM_Status         errCode = DMANODE_EDMA_ERR_SUCCESS;

    if (edmaContext == NULL)
    {
        PRINTF("BIN_IMG2LIST_BAM_DMA ERROR : Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
    }

    if ( errCode == DMANODE_EDMA_ERR_SUCCESS)
    {

        context->dstPtr[0] = ctrlArgs->dstPtr;
        context->dstStartPtr[0] = ctrlArgs->dstPtr;
        context->pListSize = ctrlArgs->pListSize;
    }

    return errCode;
}


BAM_Status BIN_IMG2LIST_BAM_DMA_triggerOutChannel(void * edmaContext)
{
    BIN_IMG2LIST_DMA_context *context = (BIN_IMG2LIST_DMA_context *)edmaContext;
    BAM_Status errCode = DMANODE_EDMA_ERR_SUCCESS;
    int32_t         status = 0;

    if(context->blkIdxOut >= 0)
    {
        /* Update the amount of transfer to be done based on the list size returned by the kernel */
        /* context->blkWidth[0]     = 4*context->pIntListSize[0]; */
        context->blkWidth[0]     = (uint16_t)(*((uint32_t*)context->pIntListSize)*sizeof(uint32_t));

        /* Trigger the transfer */
        status = EDMA_UTILS_scattherGather_updateNtrigger(context->scatterDmaContext, &(context->updateParams));
    }

    /* Indicate BAM to pipe down on encountering penultimate block */
    /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
    /*  MISRA.BOOL.INVAR.TRUE : The condition is always true  */
    /* status will never be nonzero because we are exiting */
    /* in case of failures by having checks for various contitions above */
    if ((status != 0) || ((context->blkIdxOut + 1) >= (context->numTotalBlk - 1)))
    {
    /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */
        errCode = DMANODE_EDMA_ERR_FAILED;
    }

    return errCode;
}


BAM_Status BIN_IMG2LIST_BAM_DMA_waitOutChannel(void * edmaContext)
{
    BIN_IMG2LIST_DMA_context *context = (BIN_IMG2LIST_DMA_context *)edmaContext;
    BAM_Status errCode = DMANODE_EDMA_ERR_SUCCESS;

    if(context->blkIdxOut >= 0)
    {
        EDMA_UTILS_scattherGather_wait(context->scatterDmaContext);

        /* CHECK_MISRA("-17.1,17.4")  -> Disable rule 17.1,17.4  */
        /* Pointer arithmetic is needed here to update the output pointer */
        /* The harmful side effect of voilating this rule (accessing outside valid memory) */
        /* shall be checked by another code checker like Klocwork */

        /* Update the destination pointer in DDR */
        context->dstPtr[0] += context->blkWidth[0];
        /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1,17.4  */

#if (!VCOP_HOST_EMULATION)

        /* Switch the listSize buffer to PING and PONG copies as required */
        if((context->blkIdxOut % 2) == 0) {
          /* CHECK_MISRA("-17.1,17.4")  -> Disable rule 17.1,17.4  */
          /* Pointer arithmetic is needed here to update the output pointer */
          /* The harmful side effect of voilating this rule (accessing outside valid memory) */
          /* shall be checked by another code checker like Klocwork */
            context->pIntListSize += 0x8000;
          /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1,17.4  */
        }
        else {
          /* CHECK_MISRA("-17.1,17.4")  -> Disable rule 17.1,17.4  */
          /* Pointer arithmetic is needed here to update the output pointer */
          /* The harmful side effect of voilating this rule (accessing outside valid memory) */
          /* shall be checked by another code checker like Klocwork */
            context->pIntListSize -= 0x8000;
          /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1,17.4  */
        }
#endif
    }

    /* ------------------------------------------------------------- */
    /* Update block position                                         */
    /* ------------------------------------------------------------- */
    context->blkIdxOut++;
    if(context->blkIdxOut >= context->numTotalBlk)
    {
        /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
        /* Function pointers converted to uint32_t */
        /* CHECK_MISRA("-17.1,17.4")  -> Disable rule 17.1,17.4  */
        /* Pointer arithmetic is needed here to update the output pointer */
        /* The harmful side effect of voilating this rule (accessing outside valid memory) */
        /* shall be checked by another code checker like Klocwork */
        /* Return the list size */
        context->pListSize[0] = ((uintptr_t)context->dstPtr[0] - (uintptr_t)context->dstStartPtr[0])/4U;
        /* RESET_MISRA("11.3")  -> Reset rule 11.3  */
        /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1,17.4  */

        /* Restore back to initial state at end of pipeline */
        context->blkIdxOut = -1;
        context->pIntListSize = context->pIntListSizePing;
        context->dstPtr[0] = context->dstStartPtr[0];
    }

    return errCode;
}


BAM_KernelInfo gBAM_TI_binImg2ListReadKernel =
{
    0,                                   /*kernelId*/
    sizeof(BIN_IMG2LIST_DMA_context),
    0,
    BAM_EVE_ARP32,                       /*coreType*/
    BAM_NODE_SOURCE,                     /*nodeType*/
    0,                                   /*numInputDataBlocks */
    1,                                   /*numOutputDataBlocks */
    1                                    /*numRecInternal */
};

BAM_KernelHelperFuncDef gBAM_TI_dmaReadBinImg2ListHelperFunc =
{
    &BIN_IMG2LIST_BAM_DMA_IN_getMemRecFunc, /* function to get kernel's memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
    &BIN_IMG2LIST_BAM_DMA_IN_setMemRecFunc /* function to get kernel's memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};


BAM_KernelExecFuncDef gBAM_TI_dmaReadBinImg2ListExecFunc =
{
    NULL,
    &BIN_IMG2LIST_BAM_DMA_frameInitInChannel,
    &EDMA_UTILS_autoIncrement_triggerInChannel,
    &EDMA_UTILS_autoIncrement_waitInChannel,
    &BIN_IMG2LIST_BAM_DMA_updateInDDRptr,
    NULL
};

BAM_KernelInfo gBAM_TI_binImg2ListWriteKernel =
{
    0,                                    /*kernelId*/
    0,
    0,
    BAM_EVE_ARP32,                        /*coreType*/
    BAM_NODE_SINK,                        /*nodeType*/
    2,                                    /*numInputDataBlocks */
    0,                                    /*numOutputDataBlocks */
    1                                     /*numRecInternal */
};

BAM_KernelHelperFuncDef gBAM_TI_dmaWriteBinImg2ListHelperFunc =
{
    &BIN_IMG2LIST_BAM_DMA_OUT_getMemRecFunc, /* function to get kernel's memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
    &BIN_IMG2LIST_BAM_DMA_OUT_setMemRecFunc /* function to get kernel's memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};

BAM_KernelExecFuncDef gBAM_TI_dmaWriteBinImg2ListExecFunc =
{
    NULL,
    &BIN_IMG2LIST_BAM_DMA_frameInitOutChannel ,
    &BIN_IMG2LIST_BAM_DMA_triggerOutChannel,
    &BIN_IMG2LIST_BAM_DMA_waitOutChannel,
    &BIN_IMG2LIST_BAM_DMA_updateOutDDRptr,
    NULL
};

