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
#include "edma_utils_memcpy.h"
#include "edma_utils_autoincrement.h"
#include "bam_dma_one_shot_node.h"
#include "bam_dma_one_shot_node_int.h"
#include "bam_common.h"
#include "edma_utils_context_size.h"

/* CHECK_MISRA("-15.1")  -> Disable rule 15.1 */
/* Goto statement is used */
/* Deviation is allowed because we use GOTO several times throughout the code but they are all forward GOTO to a single exit point */

BAM_Status BAM_DMA_ONESHOT_waitChannel(void * edmaContext);
BAM_Status BAM_DMA_ONESHOT_triggerOutChannel(void * edmaContext);
BAM_Status BAM_DMA_ONESHOT_triggerInChannel(void * edmaContext);
BAM_Status BAM_DMA_ONESHOT_updateDDRptrInChannel(void * edmaContext, void * params);
BAM_Status BAM_DMA_ONESHOT_updateDDRptrOutChannel(void * edmaContext, void * params);
BAM_Status BAM_DMA_ONESHOT_frameInitOutChannel(void * edmaContext);
BAM_Status BAM_DMA_ONESHOT_frameInitInChannel(void * edmaContext);
BAM_Status BAM_DMA_ONESHOT_setMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);
BAM_Status BAM_DMA_ONESHOT_getMemRecFunc(const void *edmaArgs, BAM_MemRec *memRecInternal, BAM_MemRec *memRecOutputDataBlock,
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);


/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter edmaArgs is not used to modify the addressed object but is not declared as a pointer to const */
/* Must be a false positive because it is declared as pointer to const void here */
BAM_Status BAM_DMA_ONESHOT_getMemRecFunc(const void *edmaArgs, BAM_MemRec *memRecInternal, BAM_MemRec memRecOutputDataBlock[],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock)
{
#ifndef HOST_EMULATION
    const BAM_DMA_OneShot_Args *initParams = edmaArgs;
#else
    const BAM_DMA_OneShot_Args *initParams = (const BAM_DMA_OneShot_Args *)edmaArgs;
#endif

    DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
    uint32_t        transferCnt = 0;
    uint32_t        numTransfer = 0;

    /* Not checking memRecInternal pointer since it is not used in this function */
    if ((initParams== NULL) || (numRecInternal== 0) || (numRecOutputDataBlock== 0))
    {
        PRINTF("BAM_DMA_ONE_SHOT ERROR: Argument pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
    }
    else {
        if((initParams->transferType == EDMA_UTILS_TRANSFER_IN ) && (memRecOutputDataBlock== 0))
        {
            PRINTF("BAM_DMA_ONE_SHOT ERROR: Argument pointer is NULL\n");
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
            PRINTF("BAM_DMA_ONE_SHOT ERROR: Invalid Transfer Types!!\n");
            errCode = DMANODE_EDMA_ERR_FAILED;
        }


        if(numTransfer > MAX_NODE_CHANNELS)
        {
            PRINTF("BAM_DMA_ONE_SHOT ERROR: Num of transfer Requested(= %d) is greater than max number \n",numTransfer);
            errCode = DMANODE_EDMA_ERR_CROSSED_MAX_NODE_CHANNELS;
        }

        if(errCode == DMANODE_EDMA_ERR_SUCCESS)
        {
            for(transferCnt = 0 ; transferCnt < numTransfer; transferCnt++)
            {
                if( (initParams->transferProp[transferCnt].blkWidth <= 0U) ||
                        (initParams->transferProp[transferCnt].blkHeight <= 0U) )
                {
                    PRINTF("BAM_DMA_ONE_SHOT ERROR: Invalid Image Dimentions!!\n");
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
                    PRINTF("BAM_DMA_ONE_SHOT ERROR: Invalid Transfer Type!!\n");
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
BAM_Status BAM_DMA_ONESHOT_setMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs)
{

    BAM_DMA_OneShot_Args initParams;
    BAM_DMA_OneShot_Context *context = (BAM_DMA_OneShot_Context *) edmaContext;

    DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
    uint32_t        transferCnt = 0;

    memcpy(&initParams, edmaArgs, sizeof(initParams));

    if (edmaContext== NULL)
    {
        PRINTF("BAM_DMA_ONE_SHOT ERROR: Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
    }

    if(errCode == DMANODE_EDMA_ERR_SUCCESS)
    {
        if ((memRecOutputDataBlock!= NULL) && (initParams.transferType == EDMA_UTILS_TRANSFER_IN) )
        {
            if(initParams.numInTransfers > MAX_NODE_CHANNELS)
            {
                PRINTF("BAM_DMA_ONE_SHOT ERROR: Not enough channels available for transfer\n");
                errCode = DMANODE_EDMA_ERR_CROSSED_MAX_NODE_CHANNELS;
            }

            if(errCode == DMANODE_EDMA_ERR_SUCCESS)
            {
                /* Reset globalStateStruct for the first time for IN channels before configuring EDMA */
                EDMA_UTILS_globalReset();

                for(transferCnt = 0 ; transferCnt < initParams.numInTransfers; transferCnt++)
                {
                    /* ------------------------------------------------------------- */
                    /* Set internal memory pointers                                  */
                    /* ------------------------------------------------------------- */
                    if(memRecOutputDataBlock[transferCnt]->base== NULL)
                    {
                        errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
                        break;
                    }
                    initParams.transferProp[transferCnt].interMemPtr = (uint8_t *)memRecOutputDataBlock[transferCnt]->base;
                }
            }
        }
        else if( (memRecInputDataBlock!= NULL) && (initParams.transferType == EDMA_UTILS_TRANSFER_OUT) )
        {
            if(initParams.numOutTransfers > MAX_NODE_CHANNELS)
            {
                PRINTF("BAM_DMA_ONE_SHOT ERROR: Not enough channels available for transfer\n");
                errCode = DMANODE_EDMA_ERR_CROSSED_MAX_NODE_CHANNELS;
            }

            if(errCode == DMANODE_EDMA_ERR_SUCCESS)
            {
                for(transferCnt = 0 ; transferCnt < initParams.numOutTransfers; transferCnt++)
                {
                    /* ------------------------------------------------------------- */
                    /* Set internal memory pointers                                  */
                    /* ------------------------------------------------------------- */
                    if(memRecInputDataBlock[transferCnt]->base== NULL)
                    {
                        errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
                        break;
                    }
                    initParams.transferProp[transferCnt].interMemPtr = (uint8_t *)memRecInputDataBlock[transferCnt]->base;
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
        memcpy((void*)&(context->kernelArgs), &initParams, sizeof(BAM_DMA_OneShot_Args));
    }

    return errCode;
}
/*RESET_MISRA("16.7")  -> Reset rule 16.7 */

BAM_Status BAM_DMA_ONESHOT_frameInitInChannel(void * edmaContext)
{
    BAM_DMA_OneShot_Context *context = (BAM_DMA_OneShot_Context *) edmaContext;
    DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;

    if (edmaContext== NULL)
    {
        PRINTF("BAM_DMA_ONE_SHOT ERROR: Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
    }
    else {
        /* Reset globalStateStruct for every new frame for IN channels before configuring EDMA */
        EDMA_UTILS_globalReset();

        context->triggerTimer= context->kernelArgs.triggerBlockId;
        context->oneShotDone= 0;
    }

    return errCode;
}

BAM_Status BAM_DMA_ONESHOT_frameInitOutChannel(void * edmaContext)
{
    BAM_DMA_OneShot_Context *context = (BAM_DMA_OneShot_Context *) edmaContext;
    DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;

    if (edmaContext== NULL)
    {
        PRINTF("BAM_DMA_ONE_SHOT ERROR: Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
    }
    else {
        context->triggerTimer= -1;
        context->oneShotDone= 0;
    }

    return errCode;

}

/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* BAM_DMA_ONESHOT_updateDDRptrInChannel() will be supplied as type BAM_KernelCtlFunc to the framework, thus its prototype must adhere to it */
BAM_Status BAM_DMA_ONESHOT_updateDDRptrInChannel(void * edmaContext, void * params)
{
#ifndef HOST_EMULATION
    const BAM_DMA_OneShot_CtlArgs *ctlArgs = params;
#else
    const BAM_DMA_OneShot_CtlArgs *ctlArgs = (const BAM_DMA_OneShot_CtlArgs *)params;
#endif
    BAM_DMA_OneShot_Context *context = (BAM_DMA_OneShot_Context *) edmaContext;

    uint8_t numTransfer= 0, transferCnt= 0;
    DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;

    if (edmaContext== NULL)
    {
        PRINTF("BAM_DMA_ONE_SHOT ERROR: Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
        goto EXIT;
    }

    if (params== NULL)
    {
        PRINTF("BAM_DMA_ONE_SHOT ERROR : updateParams NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
        goto EXIT;
    }

    if(context->kernelArgs.transferType == EDMA_UTILS_TRANSFER_IN)
    {
        numTransfer = context->kernelArgs.numInTransfers;
        if (numTransfer != ctlArgs->numTransfers) {
            PRINTF("BAM_DMA_ONE_SHOT ERROR: Number of input buffers passed doesn't match number of transfers initialized !!\n");
            errCode = DMANODE_EDMA_ERR_FAILED;
            goto EXIT;
        }
    }
    else
    {
        PRINTF("BAM_DMA_ONE_SHOT ERROR: Invalid Transfer Types!!\n");
        errCode = DMANODE_EDMA_ERR_FAILED;
        goto EXIT;
    }

    if(numTransfer > MAX_NODE_CHANNELS)
    {
        PRINTF("BAM_DMA_ONE_SHOT ERROR: Num of transfer Requested(= %d) is greater than max number \n",numTransfer);
        errCode = DMANODE_EDMA_ERR_CROSSED_MAX_NODE_CHANNELS;
        goto EXIT;
    }

    for(transferCnt = 0 ; transferCnt < numTransfer; transferCnt++) {
        context->kernelArgs.transferProp[transferCnt].extMemPtr= ctlArgs->extMemPtr[transferCnt];
        context->kernelArgs.transferProp[transferCnt].extMemPtrStride = ctlArgs->extMemPtrStride[transferCnt];
    }

    EXIT:
    return errCode;

}
/*RESET_MISRA("16.7")  -> Reset rule 16.7 */


/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* BAM_DMA_ONESHOT_updateDDRptrOutChannel() will be supplied as type BAM_KernelCtlFunc to the framework, thus its prototype must adhere to it */
BAM_Status BAM_DMA_ONESHOT_updateDDRptrOutChannel(void * edmaContext, void * params)
{
#ifndef HOST_EMULATION
    const BAM_DMA_OneShot_CtlArgs *ctlArgs = params;
#else
    const BAM_DMA_OneShot_CtlArgs *ctlArgs = (const BAM_DMA_OneShot_CtlArgs *)params;
#endif
    BAM_DMA_OneShot_Context *context = (BAM_DMA_OneShot_Context *) edmaContext;

    uint8_t numTransfer= 0, transferCnt= 0;
    DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;

    if (edmaContext== NULL)
    {
        PRINTF("BAM_DMA_ONE_SHOT ERROR: Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
        goto EXIT;
    }

    if (params== NULL)
    {
        PRINTF("BAM_DMA_ONE_SHOT ERROR : updateParams NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
        goto EXIT;
    }

    if(context->kernelArgs.transferType == EDMA_UTILS_TRANSFER_OUT)
    {
        numTransfer = context->kernelArgs.numOutTransfers;
        if (numTransfer != ctlArgs->numTransfers) {
            PRINTF("BAM_DMA_ONE_SHOT ERROR: Number of output buffers passed doesn't match number of transfers initialized !!\n");
            errCode = DMANODE_EDMA_ERR_FAILED;
            goto EXIT;
        }
    }
    else
    {
        PRINTF("BAM_DMA_ONE_SHOT ERROR: Invalid Transfer Types!!\n");
        errCode = DMANODE_EDMA_ERR_FAILED;
        goto EXIT;
    }

    if(numTransfer > MAX_NODE_CHANNELS)
    {
        PRINTF("BAM_DMA_ONE_SHOT ERROR: Num of transfer Requested(= %d) is greater than max number \n",numTransfer);
        errCode = DMANODE_EDMA_ERR_CROSSED_MAX_NODE_CHANNELS;
        goto EXIT;
    }

    for(transferCnt = 0 ; transferCnt < numTransfer; transferCnt++) {
        context->kernelArgs.transferProp[transferCnt].extMemPtr= ctlArgs->extMemPtr[transferCnt];
        context->kernelArgs.transferProp[transferCnt].extMemPtrStride = ctlArgs->extMemPtrStride[transferCnt];
    }

    EXIT:
    return errCode;

}
/*RESET_MISRA("16.7")  -> Reset rule 16.7 */

BAM_Status BAM_DMA_ONESHOT_triggerInChannel(void * edmaContext)
{
    uint8_t numTransfer= 0, transferCnt= 0;
    BAM_DMA_OneShot_Context *context = (BAM_DMA_OneShot_Context *) edmaContext;
    int32_t errCode = DMANODE_EDMA_ERR_SUCCESS;

    numTransfer = context->kernelArgs.numInTransfers;

    if ((context->triggerTimer== 0) && (context->oneShotDone== 0)) {
        for (transferCnt=0;transferCnt<numTransfer;transferCnt++) {
            if (EDMA_UTILS_memcpy2D(context->kernelArgs.transferProp[transferCnt].interMemPtr, context->kernelArgs.transferProp[transferCnt].extMemPtr, context->kernelArgs.transferProp[transferCnt].blkWidth, context->kernelArgs.transferProp[transferCnt].blkHeight, context->kernelArgs.transferProp[transferCnt].interMemPtrStride, context->kernelArgs.transferProp[transferCnt].extMemPtrStride)== -1) {
                errCode= -1;
            }
        }
        context->oneShotDone= 1;
    }

    context->triggerTimer--;

    return (DMANODE_EdmaErr)errCode;
}

BAM_Status BAM_DMA_ONESHOT_waitChannel(void * edmaContext)
{
    return DMANODE_EDMA_ERR_SUCCESS;
}


BAM_Status BAM_DMA_ONESHOT_triggerOutChannel(void * edmaContext)
{
    uint8_t numTransfer=0, transferCnt= 0;
    BAM_DMA_OneShot_Context *context = (BAM_DMA_OneShot_Context *) edmaContext;
    int32_t errCode = DMANODE_EDMA_ERR_SUCCESS;

    numTransfer = context->kernelArgs.numOutTransfers;

    if ((context->triggerTimer== 0) && (context->oneShotDone== 0)) {
        for (transferCnt=0;transferCnt<numTransfer;transferCnt++) {
            if (EDMA_UTILS_memcpy2D(context->kernelArgs.transferProp[transferCnt].extMemPtr, context->kernelArgs.transferProp[transferCnt].interMemPtr, context->kernelArgs.transferProp[transferCnt].blkWidth, context->kernelArgs.transferProp[transferCnt].blkHeight,  context->kernelArgs.transferProp[transferCnt].extMemPtrStride, context->kernelArgs.transferProp[transferCnt].interMemPtrStride)== -1) {
                errCode= -1;
            }
        }
        context->oneShotDone= 1;
    }
    else{
        if (context->triggerTimer== -1) {
            context->triggerTimer= context->kernelArgs.triggerBlockId+1; /* +1 because we are going to dincrement next line */
            context->blockCount= context->kernelArgs.numTotalBlocksInFrame+1;
        }
    }

    context->triggerTimer--;
    context->blockCount--;

    if (context->blockCount<= 1) {
        errCode= DMANODE_EDMA_ERR_FAILED;
    }

    return (DMANODE_EdmaErr)errCode;
}


BAM_KernelInfo gBAM_TI_dmaOneShotReadKernel =
{
        0,                                    /*kernelId*/
        sizeof(BAM_DMA_OneShot_Context),
        sizeof(BAM_DMA_OneShot_Args),
        BAM_EVE_ARP32,                      /*coreType*/
        BAM_NODE_SOURCE,                    /*nodeType*/
        0,                                  /*numInputDataBlocks */
        MAX_NODE_CHANNELS,                  /*numOutputDataBlocks */
        1                                   /*numRecInternal */
};

BAM_KernelInfo gBAM_TI_dmaOneShotWriteKernel =
{
        0,                                    /*kernelId*/
        sizeof(BAM_DMA_OneShot_Context),
        sizeof(BAM_DMA_OneShot_Args),
        BAM_EVE_ARP32,      /*coreType*/
        BAM_NODE_SINK,      /*nodeType*/
        MAX_NODE_CHANNELS,  /*numInputDataBlocks */
        0,                  /*numOutputDataBlocks */
        1                   /*numRecInternal */
};

#ifndef HOST_EMULATION

BAM_KernelHelperFuncDef gBAM_TI_dmaReadOneShotKernelHelperFunc =
{
        &BAM_DMA_ONESHOT_getMemRecFunc, /* function to get kernel’s memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
        &BAM_DMA_ONESHOT_setMemRecFunc /* function to get kernel’s memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};

BAM_KernelHelperFuncDef gBAM_TI_dmaWriteOneShotKernelHelperFunc =
{
        &BAM_DMA_ONESHOT_getMemRecFunc, /* function to get kernel’s memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
        &BAM_DMA_ONESHOT_setMemRecFunc /* function to get kernel’s memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};

BAM_KernelExecFuncDef gBAM_TI_dmaReadOneShotKernelExecFunc =
{
        NULL,&BAM_DMA_ONESHOT_frameInitInChannel, &BAM_DMA_ONESHOT_triggerInChannel,
        &BAM_DMA_ONESHOT_waitChannel, &BAM_DMA_ONESHOT_updateDDRptrInChannel, NULL
};

BAM_KernelExecFuncDef gBAM_TI_dmaWriteOneShotKernelExecFunc =
{
        NULL, &BAM_DMA_ONESHOT_frameInitOutChannel , &BAM_DMA_ONESHOT_triggerOutChannel,
        &BAM_DMA_ONESHOT_waitChannel, &BAM_DMA_ONESHOT_updateDDRptrOutChannel, NULL
};

#else

    BAM_KernelHelperFuncDef gBAM_TI_dmaReadOneShotKernelHelperFunc =
    {
            &BAM_DMA_ONESHOT_getMemRecFunc, /* function to get kernel’s memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
            &BAM_DMA_ONESHOT_setMemRecFunc /* function to get kernel’s memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
    };

    BAM_KernelHelperFuncDef gBAM_TI_dmaWriteOneShotKernelHelperFunc =
    {
            &BAM_DMA_ONESHOT_getMemRecFunc, /* function to get kernel’s memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
            &BAM_DMA_ONESHOT_setMemRecFunc /* function to get kernel’s memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
    };

    BAM_KernelExecFuncDef gBAM_TI_dmaReadOneShotKernelExecFunc =
    {
            NULL,(BAM_KernelFunc) &BAM_DMA_ONESHOT_frameInitInChannel, (BAM_KernelFunc) &BAM_DMA_ONESHOT_triggerInChannel,
            (BAM_KernelFunc) &BAM_DMA_ONESHOT_waitChannel, (BAM_KernelCtlFunc) &BAM_DMA_ONESHOT_updateDDRptrInChannel, NULL
    };

    BAM_KernelExecFuncDef gBAM_TI_dmaWriteOneShotKernelExecFunc =
    {
            NULL, (BAM_KernelFunc) &BAM_DMA_ONESHOT_frameInitOutChannel , (BAM_KernelFunc) &BAM_DMA_ONESHOT_triggerOutChannel,
            (BAM_KernelFunc) &BAM_DMA_ONESHOT_waitChannel, (BAM_KernelCtlFunc) &BAM_DMA_ONESHOT_updateDDRptrOutChannel, NULL
    };

#endif

    /*RESET_MISRA("15.1")  -> Reset rule 15.1 for GOTO */

