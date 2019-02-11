/*
*
* Copyright (c) 2012-2017 Texas Instruments Incorporated
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




/*-----------------------------------------------------------------------*/
/*  Standard header includes for c environment.                          */
/*-----------------------------------------------------------------------*/
#pragma CHECK_MISRA ("none")
#include <string.h>
#pragma RESET_MISRA ("required")

#include "algframework.h"
#include "edma_utils.h"

#ifdef CORE_DSP
#include "edma_utils_autoincrement_v2.h"
#elif defined(CORE_EVE)
#include "edma_utils_autoincrement.h"
#endif
#include "bam_dma_autoincrement_node.h"
#include "bam_dma_autoincrement_node.h"
#include "bam_common.h"
#include "edma_utils_context_size.h"


#ifdef CORE_DSP
#define BAM_NODE_autoIncrement_initParam EDMA_UTILS_autoIncrement_initParam_v2
#define BAM_NODE_AUTOINCREMENT_CONTEXT_SIZE   EDMA_UTILS_AUTOINCREMENT_CONTEXT_V2_SIZE
#define BAM_NODE_autoIncrement_init              EDMA_UTILS_autoIncrement_init_v2               
#define BAM_NODE_autoIncrement_configure         EDMA_UTILS_autoIncrement_configure_v2              
#define BAM_NODE_autoIncrement_update            EDMA_UTILS_autoIncrement_update_v2              
#define BAM_NODE_autoIncrement_triggerInChannel  EDMA_UTILS_autoIncrement_triggerInChannel_v2              
#define BAM_NODE_autoIncrement_waitInChannel     EDMA_UTILS_autoIncrement_waitInChannel_v2              
#define BAM_NODE_autoIncrement_triggerOutChannel EDMA_UTILS_autoIncrement_triggerOutChannel_v2              
#define BAM_NODE_autoIncrement_waitOutChannel    EDMA_UTILS_autoIncrement_waitOutChannel_v2                         

#elif defined(CORE_EVE)
#define BAM_NODE_autoIncrement_initParam         EDMA_UTILS_autoIncrement_initParam
#define BAM_NODE_AUTOINCREMENT_CONTEXT_SIZE      EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE
#define BAM_NODE_autoIncrement_init              EDMA_UTILS_autoIncrement_init               
#define BAM_NODE_autoIncrement_configure         EDMA_UTILS_autoIncrement_configure              
#define BAM_NODE_autoIncrement_update            EDMA_UTILS_autoIncrement_update             
#define BAM_NODE_autoIncrement_triggerInChannel  EDMA_UTILS_autoIncrement_triggerInChannel              
#define BAM_NODE_autoIncrement_waitInChannel     EDMA_UTILS_autoIncrement_waitInChannel             
#define BAM_NODE_autoIncrement_triggerOutChannel EDMA_UTILS_autoIncrement_triggerOutChannel              
#define BAM_NODE_autoIncrement_waitOutChannel    EDMA_UTILS_autoIncrement_waitOutChannel                         
#endif


/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter edmaArgs is not used to modify the addressed object but is not declared as a pointer to const */
/* Must be a false positive because it is declared as pointer to const void here */
BAM_Status BAM_DMA_AUTOINCREMENT_getMemRecFunc(const void *edmaArgs, BAM_MemRec *memRecInternal, BAM_MemRec memRecOutputDataBlock[],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock)
{
    const EDMA_UTILS_autoIncrement_initParam *initParams = (EDMA_UTILS_autoIncrement_initParam *)edmaArgs;
    DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
    uint32_t        transferCnt = 0;
    uint32_t        numTransfer = 0;

    /* Not checking memRecInternal pointer since it is not used in this function */
    if ((initParams== NULL) || (numRecInternal== 0) || (numRecOutputDataBlock== 0))
    {
        PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Argument pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
    }

    else {
        if((initParams->transferType == EDMA_UTILS_TRANSFER_IN ) && (memRecOutputDataBlock== 0))
        {
            PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Argument pointer is NULL\n");
            errCode = DMANODE_EDMA_ERR_NULL_ARGS;
        }

        if(initParams->transferType == EDMA_UTILS_TRANSFER_IN)
        {
            numTransfer = initParams->numInTransfers;
        }
        else if (initParams->transferType == EDMA_UTILS_TRANSFER_OUT )
        {
            numTransfer = initParams->numOutTransfers;
        }
        else
        {
            PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Invalid Transfer Types!!\n");
            errCode = DMANODE_EDMA_ERR_FAILED;
        }


        if(numTransfer > MAX_NODE_CHANNELS)
        {
            PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Num of transfer Requested(= %d) is greater than max number \n",numTransfer);
            errCode = DMANODE_EDMA_ERR_CROSSED_MAX_NODE_CHANNELS;
        }

        if(errCode == DMANODE_EDMA_ERR_SUCCESS)
        {
            for(transferCnt = 0 ; transferCnt < numTransfer; transferCnt++)
            {
                if( (initParams->transferProp[transferCnt].blkWidth <= 0U) ||
                        (initParams->transferProp[transferCnt].blkHeight <= 0U) )
                {
                    PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Invalid Image Dimentions!!\n");
                    errCode = DMANODE_EDMA_ERR_INVALID_BLOCK_DIM;
                    break;
                }

                if(initParams->transferType == EDMA_UTILS_TRANSFER_IN)
                {
                    memRecOutputDataBlock[transferCnt].space = BAM_MEMSPACE_ANY_VCOPBUF;
                    memRecOutputDataBlock[transferCnt].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;

                    memRecOutputDataBlock[transferCnt].size = (initParams->transferProp[transferCnt].blkWidth)*
                            (initParams->transferProp[transferCnt].blkHeight);
                }
            }

            if(errCode == DMANODE_EDMA_ERR_SUCCESS)
            {
                if(initParams->transferType == EDMA_UTILS_TRANSFER_IN)
                {
                    *numRecOutputDataBlock = initParams->numInTransfers;
                    *numRecInternal = 0;
                }
                else if(initParams->transferType == EDMA_UTILS_TRANSFER_OUT)
                {
                    *numRecOutputDataBlock = 0;
                    *numRecInternal = 0;
                }
                else
                {
                    PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Invalid Transfer Type!!\n");
                    errCode = DMANODE_EDMA_ERR_FAILED;
                }
            }
        }
    }
    return errCode;
}

/*RESET_MISRA("16.7")  -> Reset rule 16.7 */

/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter edmaArgs is not used to modify the addressed object but is not declared as a pointer to const */
/* Must be a false positive because it is declared as pointer to const void here */
BAM_Status BAM_DMA_AUTOINCREMENT_setMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs)
{
    BAM_NODE_autoIncrement_initParam initParams;
    EDMA_UTILS_autoIncrement_initParam *initParamsPtr;
    uint8_t (*base)[];
    DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
    uint32_t        transferCnt = 0;
    int32_t         status = 0;
  
    memcpy(&initParams, edmaArgs, sizeof(initParams));

#ifdef CORE_DSP
  initParamsPtr = &initParams.initParams;
#elif defined(CORE_EVE)
  initParamsPtr = &initParams;
#endif

    if (edmaContext== NULL)
    {
        PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
    }

    if(errCode == DMANODE_EDMA_ERR_SUCCESS)
    {
        if ((memRecOutputDataBlock!= 0) && (initParamsPtr->transferType == EDMA_UTILS_TRANSFER_IN) )
        {
            if(initParamsPtr->numInTransfers > MAX_NODE_CHANNELS)
            {
                PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Not enough channels available for transfer\n");
                errCode = DMANODE_EDMA_ERR_CROSSED_MAX_NODE_CHANNELS;
            }

            if(errCode == DMANODE_EDMA_ERR_SUCCESS)
            {
                /* Reset globalStateStruct for the first time for IN channels before configuring EDMA */
                EDMA_UTILS_globalReset();

                for(transferCnt = 0 ; transferCnt < initParamsPtr->numInTransfers; transferCnt++)
                {
                    /* ------------------------------------------------------------- */
                    /* Set internal memory pointers                                  */
                    /* ------------------------------------------------------------- */
                    if(memRecOutputDataBlock[transferCnt]->base== NULL)
                    {
                        errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
                        break;
                    }
                    base= (uint8_t (*)[])memRecOutputDataBlock[transferCnt]->base;
                    initParamsPtr->transferProp[transferCnt].interMemPtr = &((*base)[initParamsPtr->transferProp[transferCnt].blkOffset]);
                }
            }
        }
        else if( (memRecInputDataBlock!= 0) && (initParamsPtr->transferType == EDMA_UTILS_TRANSFER_OUT) )
        {
            if(initParamsPtr->numOutTransfers > MAX_NODE_CHANNELS)
            {
                PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Not enough channels available for transfer\n");
                errCode = DMANODE_EDMA_ERR_CROSSED_MAX_NODE_CHANNELS;
            }

            if(errCode == DMANODE_EDMA_ERR_SUCCESS)
            {
                for(transferCnt = 0 ; transferCnt < initParamsPtr->numOutTransfers; transferCnt++)
                {
                    /* ------------------------------------------------------------- */
                    /* Set internal memory pointers                                  */
                    /* ------------------------------------------------------------- */
                    if(memRecInputDataBlock[transferCnt]->base== NULL)
                    {
                        errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
                        break;
                    }
                    base= (uint8_t (*)[])memRecInputDataBlock[transferCnt]->base;
                    initParamsPtr->transferProp[transferCnt].interMemPtr = &((*base)[initParamsPtr->transferProp[transferCnt].blkOffset]);

                }
            }
        }
        else
        {
            errCode = DMANODE_EDMA_ERR_FAILED;
        }
    }

    if ( errCode == DMANODE_EDMA_ERR_SUCCESS )
    {
        status = BAM_NODE_autoIncrement_init(edmaContext, &initParams);
    }

    if ( status != 0 )
    {
        errCode = DMANODE_EDMA_ERR_FAILED;
    }

    return errCode;
}
/*RESET_MISRA("16.7")  -> Reset rule 16.7 */


BAM_Status BAM_DMA_AUTOINCREMENT_frameInitInChannel(void * edmaContext)
{
    BAM_Status                 status = 0;
    DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;

    if (edmaContext== NULL)
    {
        PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
    }

    /* Reset globalStateStruct for every new frame for IN channels before configuring EDMA */
    EDMA_UTILS_globalReset();

    status = BAM_NODE_autoIncrement_configure(edmaContext , EDMA_UTILS_TRANSFER_IN);

    if ( status != 0 )
    {
        errCode = DMANODE_EDMA_ERR_FAILED;
    }

    return errCode;
}

BAM_Status BAM_DMA_AUTOINCREMENT_frameInitOutChannel(void * edmaContext)
{
    BAM_Status                 status = 0;
    DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;

    if (edmaContext== NULL)
    {
        PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
    }

    status = BAM_NODE_autoIncrement_configure(edmaContext, EDMA_UTILS_TRANSFER_OUT);

    if ( status != 0 )
    {
        errCode = DMANODE_EDMA_ERR_FAILED;
    }

    return errCode;

}


/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* BAM_DMA_AUTOINCREMENT_updateDDRptrInChannel() will be supplied as type BAM_KernelCtlFunc to the framework, thus its prototype must adhere to it */
BAM_Status BAM_DMA_AUTOINCREMENT_updateDDRptrInChannel(void * edmaContext,
        void *params)
{
    EDMA_UTILS_autoIncrement_updateParams updateParams;

    BAM_Status                 status = 0;
    DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;

    if (edmaContext== NULL)
    {
        PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
        goto EXIT;
    }

    if (params== NULL)
    {
        PRINTF("BAM_DMA_AUTOINCREMENT ERROR : updateParams NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
        goto EXIT;
    }

    memcpy(&updateParams, params, sizeof(updateParams));

    updateParams.transferType = EDMA_UTILS_TRANSFER_IN;

    status = BAM_NODE_autoIncrement_update(edmaContext , &updateParams);


    /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
    /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
    /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
    /*  UNREACH.GEN :   Unreachable code  */
    /* Status will never be 0 because we are passing all the correct parameters to the function above and hence all the error conditions inside the function
    will never occur.*/
    if ( status != 0 )
    {
        errCode = DMANODE_EDMA_ERR_FAILED;
    }
    /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */
    /*RESET_MISRA("14.1")  -> Reset rule 14.1 for  UNREACH.GEN */

    EXIT:
    return errCode;

}
/*RESET_MISRA("16.7")  -> Reset rule 16.7 */

/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* BAM_DMA_AUTOINCREMENT_updateDDRptrOutChannel() will be supplied as type BAM_KernelCtlFunc to the framework, thus its prototype must adhere to it */
BAM_Status BAM_DMA_AUTOINCREMENT_updateDDRptrOutChannel(void * edmaContext,
        void *params)
{
    EDMA_UTILS_autoIncrement_updateParams updateParams;

    BAM_Status                 status = 0;
    DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;

    if (edmaContext== NULL)
    {
        PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
        goto EXIT;
    }


    if (params== NULL)
    {
        PRINTF("BAM_DMA_AUTOINCREMENT ERROR : updateParams NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
        goto EXIT;
    }

    memcpy(&updateParams, params, sizeof(updateParams));

    updateParams.transferType = EDMA_UTILS_TRANSFER_OUT;

    status = BAM_NODE_autoIncrement_update(edmaContext, &updateParams);

    /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
    /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
    /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
    /*  UNREACH.GEN :   Unreachable code  */
    /* Status will never be 0 because we are passing all the correct parameters to the function above and hence all the error conditions inside the function
    will never occur.*/
    if ( status != 0 )
    {
        errCode = DMANODE_EDMA_ERR_FAILED;
    }
    /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */
    /*RESET_MISRA("14.1")  -> Reset rule 14.1 for  UNREACH.GEN */

    EXIT:
    return errCode;

}
/*RESET_MISRA("16.7")  -> Reset rule 16.7 */

BAM_KernelInfo gBAM_TI_dmaAutoIncrementReadKernel =
{
        0,                                    /*kernelId*/
        BAM_NODE_AUTOINCREMENT_CONTEXT_SIZE,
        sizeof(BAM_NODE_autoIncrement_initParam),
        BAM_EVE_ARP32,                      /*coreType*/
        BAM_NODE_SOURCE,                    /*nodeType*/
        0,                                  /*numInputDataBlocks */
        MAX_NODE_CHANNELS,                  /*numOutputDataBlocks */
        1                                   /*numRecInternal */
};

BAM_KernelInfo gBAM_TI_dmaAutoIncrementWriteKernel =
{
        0,                                    /*kernelId*/
        0,
        sizeof(BAM_NODE_autoIncrement_initParam),
        BAM_EVE_ARP32,      /*coreType*/
        BAM_NODE_SINK,      /*nodeType*/
        MAX_NODE_CHANNELS,  /*numInputDataBlocks */
        0,                  /*numOutputDataBlocks */
        1                   /*numRecInternal */
};

#ifndef HOST_EMULATION

BAM_KernelHelperFuncDef gBAM_TI_dmaReadAutoIncrementKernelHelperFunc =
{
        &BAM_DMA_AUTOINCREMENT_getMemRecFunc, /* function to get kernel’s memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
        &BAM_DMA_AUTOINCREMENT_setMemRecFunc /* function to get kernel’s memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};

BAM_KernelHelperFuncDef gBAM_TI_dmaWriteAutoIncrementKernelHelperFunc =
{
        &BAM_DMA_AUTOINCREMENT_getMemRecFunc, /* function to get kernel’s memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
        &BAM_DMA_AUTOINCREMENT_setMemRecFunc /* function to get kernel’s memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};

BAM_KernelExecFuncDef gBAM_TI_dmaReadAutoIncrementKernelExecFunc =
{
        NULL, &BAM_DMA_AUTOINCREMENT_frameInitInChannel, &BAM_NODE_autoIncrement_triggerInChannel,
        &BAM_NODE_autoIncrement_waitInChannel, &BAM_DMA_AUTOINCREMENT_updateDDRptrInChannel, NULL
};

BAM_KernelExecFuncDef gBAM_TI_dmaWriteAutoIncrementKernelExecFunc =
{
        NULL, &BAM_DMA_AUTOINCREMENT_frameInitOutChannel , &BAM_NODE_autoIncrement_triggerOutChannel,
        &BAM_NODE_autoIncrement_waitOutChannel, &BAM_DMA_AUTOINCREMENT_updateDDRptrOutChannel, NULL
};

#else

BAM_KernelHelperFuncDef gBAM_TI_dmaReadAutoIncrementKernelHelperFunc =
{
        &BAM_DMA_AUTOINCREMENT_getMemRecFunc, /* function to get kernel’s memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
        &BAM_DMA_AUTOINCREMENT_setMemRecFunc /* function to get kernel’s memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};

BAM_KernelHelperFuncDef gBAM_TI_dmaWriteAutoIncrementKernelHelperFunc =
{
        &BAM_DMA_AUTOINCREMENT_getMemRecFunc, /* function to get kernel’s memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
        &BAM_DMA_AUTOINCREMENT_setMemRecFunc /* function to get kernel’s memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};

BAM_KernelExecFuncDef gBAM_TI_dmaReadAutoIncrementKernelExecFunc =
{
        NULL, (BAM_KernelFunc)&BAM_DMA_AUTOINCREMENT_frameInitInChannel, (BAM_KernelFunc)&BAM_NODE_autoIncrement_triggerInChannel,
        (BAM_KernelFunc)&BAM_NODE_autoIncrement_waitInChannel, (BAM_KernelCtlFunc)&BAM_DMA_AUTOINCREMENT_updateDDRptrInChannel, NULL
};

BAM_KernelExecFuncDef gBAM_TI_dmaWriteAutoIncrementKernelExecFunc =
{
        NULL, (BAM_KernelFunc)&BAM_DMA_AUTOINCREMENT_frameInitOutChannel , (BAM_KernelFunc)&BAM_NODE_autoIncrement_triggerOutChannel,
        (BAM_KernelFunc)&BAM_NODE_autoIncrement_waitOutChannel, (BAM_KernelCtlFunc)&BAM_DMA_AUTOINCREMENT_updateDDRptrOutChannel, NULL
};

#endif
