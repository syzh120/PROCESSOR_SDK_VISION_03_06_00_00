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


/**
 *  @file       templateMatching_alg.c
 *
 *  @brief       This file defines the XDAIS/iVISION functions for template matching applet
 *  @version     0.0 (Dec 2013) : Base version.
 */

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#pragma RESET_MISRA ("required")
#include "edma_utils.h"

#include "edma_utils_memcpy.h"
#include "templateMatching_graph_int.h"
#include "templateMatching_alg_int.h"

/* CHECK_MISRA("-15.1")  -> Disable rule 15.1 */
/* Goto statement is used */
/* Deviation is allowed because we use GOTO several times throughout the code but they are all forward GOTO to a single exit point */


/**
 * IVISION interface of the algorithm
 */
const IVISION_Fxns TEMPLATE_MATCHING_TI_VISION_FXNS =
{
        {
                &TEMPLATE_MATCHING_TI_activate, /* module ID */
                &TEMPLATE_MATCHING_TI_activate,    /* activate */
                &TEMPLATE_MATCHING_TI_alloc,       /* algAlloc */
                NULL,                          /* control (not suported) */
                &TEMPLATE_MATCHING_TI_deactivate,  /* deactivate */
                &TEMPLATE_MATCHING_TI_free,        /* free */
                &TEMPLATE_MATCHING_TI_init,        /* init */
                NULL,                          /* moved (not suported) */
                &TEMPLATE_MATCHING_TI_numAlloc     /* algNumAlloc  */
        },
        &TEMPLATE_MATCHING_TI_process,
        &TEMPLATE_MATCHING_TI_control
};


/**
 * IRES interface of the algorithm
 */
const IRES_Fxns TEMPLATE_MATCHING_TI_IRES = {
        NULL,
        NULL,                                     /*getResourceDescriptors, */
        NULL,                                     /*numResourceDescriptors */
        NULL,                                     /*initResources,  */
        NULL,                                     /*reinitResources, */
        NULL,                                     /*deinitResources, */
        NULL,                                     /*activateResource,*/
        NULL,                                     /*activateAllResources, */
        NULL,                                     /*deactivateResource,   */
        NULL                                      /*deactivateAllResources */
};

/* Prototype for log2() function */
static uint32_t log2(uint32_t val);


static uint32_t log2(uint32_t val) {

    uint32_t origval= val;
    uint32_t i= 0;

    val= val >> 1U;

    while (val!=0) {
        val>>=1U;
        i++;
    }

    if ((uint32_t)origval & (uint32_t)((uint32_t)((uint32_t)1U<<(uint32_t)i) - (uint32_t)1U)) { /* round up the result */
            i= i + 1U;
    }

    return i;
}

/**
 * Other exposed functions
 */
int32_t TEMPLATE_MATCHING_TI_numAlloc(void)
{
    return NUM_MEMRECS;
}

/*---------------------------------------------------------------*/
/* Function to supply memory requirement to user                 */
/* refer algAlloc function for details in XADIS (ialg.h file)    */
/*---------------------------------------------------------------*/
int32_t TEMPLATE_MATCHING_TI_alloc(const IALG_Params *params,
        IALG_Fxns **parentFxns,
        IALG_MemRec memRec[])
{
    int32_t status = IALG_EOK;

    BAM_GraphMemReq graphMemReq;

    /*---------------------------------------------------------*/
    /* Request BAM public function about memories associated   */
    /* to graph creation                                       */
    /*---------------------------------------------------------*/
    TEMPLATE_MATCHING_TI_getGraphMemReq(&graphMemReq);

    /*-----------------------------------------------------------------------------*/
    /*  For memory record ALG_HANDLE_INT_MEMREC and GRAPH_OBJ_INT_MEMREC,          */
    /*  which are scratch buffers in BAM_MEMSPACE_DMEM, they must be preceded      */
    /*  by a persistent memory record in IALG_EXTERNAL of the same size.           */
    /*  This persistent record will be used to backup the following scratch        */
    /*  memory record during context saving when TEMPLATE_MATCHING_TI_deactivate */
    /*  is called. Likewise when TEMPLATE_MATCHING_TI_activate it called,        */
    /*  the content of the persistent memory record is copied back to the          */
    /*  scratch memory record in BAM_MEMSPACE_DMEM                                 */
    /*-----------------------------------------------------------------------------*/
    memRec[ALG_HANDLE_MEMREC].size          = sizeof(TEMPLATE_MATCHING_TI_Obj);
    memRec[ALG_HANDLE_MEMREC].space         = (IALG_MemSpace)IALG_EXTERNAL;
    memRec[ALG_HANDLE_MEMREC].attrs         = IALG_PERSIST;
    memRec[ALG_HANDLE_MEMREC].alignment     = 4;

    memRec[ALG_HANDLE_INT_MEMREC].size      = sizeof(TEMPLATE_MATCHING_TI_Obj);
    memRec[ALG_HANDLE_INT_MEMREC].space     = (IALG_MemSpace)IALG_DARAM0;
    memRec[ALG_HANDLE_INT_MEMREC].attrs     = IALG_SCRATCH;
    memRec[ALG_HANDLE_INT_MEMREC].alignment = 4;

    /*-------------------------------------------------------------------------*/
    /* Below 5 memory records are used to store data related to the BAM graph: */
    /* 1. GRAPH_OBJ_MEMREC     - To hold graph object in external memory       */
    /* 2. GRAPH_OBJ_INT_MEMREC - To hold the graph object in internal memory   */
    /* GRAPH OBJECT has 2 instances - internal and external memory - it is to  */
    /* speed up the processing - Main processing will work on internal memory  */
    /* instance and before any one else needing internal memory, deacitavte    */
    /* has to be performed by caller to make sure the data is backed up to ext */
    /* memory                                                                  */
    /*                                                                         */
    /* 3. GRAPH_SCRATCH_MEMREC -                                               */
    /*  It is used as scratch memory during graph create time                  */
    /*  Scratch mem is currently placed in external memory.                    */
    /*  For faster graph creation time, you can place it in internal memory    */
    /*                                                                         */
    /* 4. GRAPH_CONTEXT_MEMREC                                                 */
    /*  It is used to backup into external memory the graph's                  */
    /*  nodes internal memory records that are persistent.                     */
    /*                                                                         */
    /* 5. GRAPH_ARGS_MEMREC  -                                                 */
    /*   It is used keep kernels arguments during graph create time            */
    /*-------------------------------------------------------------------------*/

    memRec[GRAPH_OBJ_MEMREC].size           = graphMemReq.graphObjSize;
    memRec[GRAPH_OBJ_MEMREC].space          = (IALG_MemSpace) IALG_EXTERNAL;
    memRec[GRAPH_OBJ_MEMREC].attrs          = IALG_PERSIST;
    memRec[GRAPH_OBJ_MEMREC].alignment      = 4;

    /*
    GRAPH_OBJ_INT_MEMREC is allocated in DMEM and is used when the backup is
    restored from external memory to faster internal memory when activate is called.
     */
    memRec[GRAPH_OBJ_INT_MEMREC].size       = graphMemReq.graphObjSize;
    memRec[GRAPH_OBJ_INT_MEMREC].space      = (IALG_MemSpace) IALG_DARAM0;
    memRec[GRAPH_OBJ_INT_MEMREC].attrs      = IALG_SCRATCH;
    memRec[GRAPH_OBJ_INT_MEMREC].alignment  = 4;

    memRec[GRAPH_SCRATCH_MEMREC].size       =  graphMemReq.graphScratchSize;
    memRec[GRAPH_SCRATCH_MEMREC].space      =  (IALG_MemSpace) IALG_EXTERNAL;
    memRec[GRAPH_SCRATCH_MEMREC].attrs      =  IALG_SCRATCH;
    memRec[GRAPH_SCRATCH_MEMREC].alignment  = 4;

    memRec[GRAPH_CONTEXT_MEMREC].size       =  graphMemReq.graphcontextSize;
    memRec[GRAPH_CONTEXT_MEMREC].space      =  (IALG_MemSpace) IALG_EXTERNAL;
    memRec[GRAPH_CONTEXT_MEMREC].attrs      =  IALG_SCRATCH;
    memRec[GRAPH_CONTEXT_MEMREC].alignment  = 4;

    memRec[GRAPH_ARGS_MEMREC].size          =  graphMemReq.graphArgsSize;
    memRec[GRAPH_ARGS_MEMREC].space         =  (IALG_MemSpace) IALG_EXTERNAL;
    memRec[GRAPH_ARGS_MEMREC].attrs         =  IALG_SCRATCH;
    memRec[GRAPH_ARGS_MEMREC].alignment     = 4;

    return (status);
}


/*-----------------------------------------------------------------------*/
/* Function to accept memory pointers from user and initialize algorithm */
/* Refer algInit function for details in XADIS (ialg.h file)             */
/*-----------------------------------------------------------------------*/
int32_t TEMPLATE_MATCHING_TI_init(IALG_Handle handle,
        const IALG_MemRec memRec[],
        IALG_Handle parent,
        const IALG_Params * params)
{
    int32_t status = IALG_EOK;

    const TEMPLATE_MATCHING_TI_CreateParams * createParams =
            (const TEMPLATE_MATCHING_TI_CreateParams*)(const void*)params;

    TEMPLATE_MATCHING_TI_graphCreateParams graphCreateParams;

    TEMPLATE_MATCHING_TI_Handle algHandle =
            (TEMPLATE_MATCHING_TI_Handle)(void*)memRec[ALG_HANDLE_MEMREC].base;

    /*-----------------------------------------------------------------------*/
    /* Call BAM Graph creation function with passing all the memories        */
    /*-----------------------------------------------------------------------*/
    algHandle->graphMem.graphObj      = memRec[GRAPH_OBJ_MEMREC].base;
    algHandle->graphMem.graphScratch  = memRec[GRAPH_SCRATCH_MEMREC].base;
    algHandle->graphMem.graphcontext  = memRec[GRAPH_CONTEXT_MEMREC].base;
    algHandle->graphMem.graphArgs     = memRec[GRAPH_ARGS_MEMREC].base;

    graphCreateParams.imgFrameWidth= createParams->imgFrameWidth;
    graphCreateParams.imgFrameHeight= createParams->imgFrameHeight;

    graphCreateParams.templateWidth= createParams->templateWidth;
    graphCreateParams.templateHeight= createParams->templateHeight;

    graphCreateParams.activeImgWidth= 0;
    graphCreateParams.activeImgHeight= 0;

    if ((graphCreateParams.templateWidth * graphCreateParams.templateHeight) > TEMPLATE_MATCHING_TI_MAX_TEMPLATE_DIM) {
        status= TEMPLATE_MATCHING_TI_ERROR_INVALID_TEMPLATE_DIM;
        goto Exit;
    }

    graphCreateParams.qShift= createParams->qShift;

    graphCreateParams.sizeQshift= (uint8_t)log2(createParams->templateWidth*createParams->templateHeight);

    status = TEMPLATE_MATCHING_TI_graphCreate(&(algHandle->graphMem),&graphCreateParams);

    if (status != IALG_EOK)
    {
        PRINTF("TEMPLATE_MATCHING_TI_graphCreate() returned error!!!");
        goto Exit;
    }

    algHandle->activeImgWidth= graphCreateParams.activeImgWidth;
    algHandle->activeImgHeight= graphCreateParams.activeImgHeight;

    algHandle->outputBlockWidth = graphCreateParams.outputBlockWidth;
    algHandle->outputBlockHeight = graphCreateParams.outputBlockHeight;
    algHandle->templateWidth= graphCreateParams.templateWidth;
    algHandle->templateHeight= graphCreateParams.templateHeight;

    algHandle->numMemRecs  = NUM_MEMRECS;
    memcpy(algHandle->memRec,memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);
    algHandle->ivision = &TEMPLATE_MATCHING_TI_VISION_FXNS;

    /*-----------------------------------------------------------------------*/
    /* State to indicate that internal context of algorithm is not active    */
    /*-----------------------------------------------------------------------*/
    algHandle->algState = ALG_NOT_ACTIVE;
    EDMA_UTILS_setEdma3RmHandle(NULL);

    Exit:
    return (status);
}

/*-----------------------------------------------------------------------*/
/* Function to accept any run time updates with recreation of object     */
/* Refer algControl function for details in ivision.h file               */
/*-----------------------------------------------------------------------*/
int32_t TEMPLATE_MATCHING_TI_control(IVISION_Handle handle,
        IALG_Cmd cmd,
        const IALG_Params *inParams,
        IALG_Params *outParams)
{
    int32_t status = IALG_EOK;
    TEMPLATE_MATCHING_TI_ControlOutParams *controlOutParams= (TEMPLATE_MATCHING_TI_ControlOutParams *)(void*)outParams;
    TEMPLATE_MATCHING_TI_Handle algHandle = (TEMPLATE_MATCHING_TI_Handle)(void*)(handle);

    if (cmd== TEMPLATE_MATCHING_TI_GET_OUTPUT_BLOCK_DIM) {
        controlOutParams->outputBlockWidth= algHandle->outputBlockWidth;
        controlOutParams->outputBlockHeight= algHandle->outputBlockHeight;
    }
    else {
        status= IALG_EFAIL;
    }

    return (status);
}


/*--------------------------------------------------------------------------*/
/* This is the main processing function and should be called for each frame */
/* Refer process function for details in ivision.h file                     */
/*--------------------------------------------------------------------------*/
int32_t TEMPLATE_MATCHING_TI_process(IVISION_Handle Handle,
        IVISION_InBufs *inBufs,
        IVISION_OutBufs *outBufs,
        IVISION_InArgs *inArgs,
        IVISION_OutArgs *outArgs)
{
    TEMPLATE_MATCHING_TI_Handle algHandle = (TEMPLATE_MATCHING_TI_Handle)(void*)(Handle);
    TEMPLATE_MATCHING_TI_Handle intAlgHandle;
    int32_t status            = IALG_EOK;
    IVISION_BufDesc    *(*inBufDesc)[TEMPLATE_MATCHING_TI_BUFDESC_IN_TOTAL];
    IVISION_BufDesc    *(*outBufDesc)[TEMPLATE_MATCHING_TI_BUFDESC_OUT_TOTAL];

    IBAMALG_InArgs          bamInArgs;
    IBAMALG_OutArgs         bamOutArgs;
    TEMPLATE_MATCHING_TI_outArgs * templateMatchingOutArgs;

    inBufDesc  = (IVISION_BufDesc *(*)[TEMPLATE_MATCHING_TI_BUFDESC_IN_TOTAL])(void *)inBufs->bufDesc;
    outBufDesc = (IVISION_BufDesc *(*)[TEMPLATE_MATCHING_TI_BUFDESC_OUT_TOTAL])(void *)outBufs->bufDesc;

    /*-----------------------------------------------------------------------*/
    /* Activate the algorithm to make sure that now onwards internal memory  */
    /* handle can be utilized                                                */
    /*-----------------------------------------------------------------------*/
    TEMPLATE_MATCHING_TI_activate((IALG_Handle)(void*)Handle);

    intAlgHandle                      = (TEMPLATE_MATCHING_TI_Handle)(void*)(algHandle->memRec[ALG_HANDLE_INT_MEMREC].base);
    intAlgHandle->graphMem.graphObj      = intAlgHandle->memRec[GRAPH_OBJ_INT_MEMREC].base;

    /*-----------------------------------------------------------------------*/
    /* BAM specific In Args and OutArgs Assignment                           */
    /*-----------------------------------------------------------------------*/
    bamInArgs.size                  = sizeof(IBAMALG_InArgs);
    bamInArgs.sliceIndex            = 0;

    bamOutArgs.size                 = sizeof(IBAMALG_OutArgs);

    BAM_activateGraph(intAlgHandle->graphMem.graphObj);


    status= TEMPLATE_MATCHING_TI_dmaControl(&(intAlgHandle->graphMem), intAlgHandle, (const IVISION_BufDesc **)inBufs->bufDesc, (const IVISION_BufDesc **)outBufs->bufDesc);

    if (status!= IALG_EOK) {
        goto Exit;
    }

    /*-----------------------------------------------------------------------*/
    /* Call execute function                                                 */
    /*-----------------------------------------------------------------------*/
    status =  TEMPLATE_MATCHING_TI_execute(&(intAlgHandle->graphMem), &bamInArgs, &bamOutArgs);

    /*-----------------------------------------------------------------------*/
    /* iVISION doesn't allow multiple control output, so last output will be */
    /* available to user                                                     */
    /*-----------------------------------------------------------------------*/
    if (outArgs->size == sizeof (TEMPLATE_MATCHING_TI_outArgs) )
    {
        templateMatchingOutArgs = (TEMPLATE_MATCHING_TI_outArgs *)(void*)outArgs;
        templateMatchingOutArgs->outputBlockWidth= intAlgHandle->outputBlockWidth;
        templateMatchingOutArgs->outputBlockHeight= intAlgHandle->outputBlockHeight;
        templateMatchingOutArgs->activeImgWidth= intAlgHandle->activeImgWidth;
        templateMatchingOutArgs->activeImgHeight= intAlgHandle->activeImgHeight;
    }

    Exit:
    /*----------------------------------*/
    /* Free the input and output buffer */
    /*----------------------------------*/
    outArgs->inFreeBufIDs[TEMPLATE_MATCHING_TI_BUFDESC_IN]=
            (*inBufDesc)[TEMPLATE_MATCHING_TI_BUFDESC_IN]->bufferId;

    outArgs->inFreeBufIDs[TEMPLATE_MATCHING_TI_BUFDESC_IN_TEMPLATE]=
            (*inBufDesc)[TEMPLATE_MATCHING_TI_BUFDESC_IN_TEMPLATE]->bufferId;

    outArgs->inFreeBufIDs[TEMPLATE_MATCHING_TI_BUFDESC_IN_TOTAL]    = 0 ;

    outArgs->outFreeBufIDs[TEMPLATE_MATCHING_TI_BUFDESC_OUT]=
            (*outBufDesc)[TEMPLATE_MATCHING_TI_BUFDESC_OUT]->bufferId;
    outArgs->outFreeBufIDs[TEMPLATE_MATCHING_TI_BUFDESC_OUT_TOTAL]   = 0;

    (*outBufDesc)[TEMPLATE_MATCHING_TI_BUFDESC_OUT]->bufPlanes[0].accessMask= IVISION_ACCESSMODE_HWA;
    (*outBufDesc)[TEMPLATE_MATCHING_TI_BUFDESC_OUT]->bufPlanes[1].accessMask= IVISION_ACCESSMODE_HWA;

    return status;
}

/*--------------------------------------------------------------------------*/
/* This is the function to do activation of algorithm. All scratch memory   */
/* are restored in this                                                     */
/* Refer algActivate function for details in ialg.h file                    */
/*--------------------------------------------------------------------------*/
XDAS_Void  TEMPLATE_MATCHING_TI_activate(IALG_Handle handle)
{
    TEMPLATE_MATCHING_TI_Handle algHandle = (TEMPLATE_MATCHING_TI_Handle)(void*)(handle);
    int32_t i;

    /*----------------------------------------------------------------*/
    /* Do Activation only if it is deactivated or just after creation */
    /*----------------------------------------------------------------*/
    if(algHandle->algState == ALG_NOT_ACTIVE)
    {
        for(i= 1; i < algHandle->numMemRecs; i++)
        {
            if((i == ALG_HANDLE_INT_MEMREC) ||(i == GRAPH_OBJ_INT_MEMREC))
            {
                EDMA_UTILS_memcpy2D((void*)algHandle->memRec[i].base, (const void*)algHandle->memRec[i-1].base, (uint16_t)algHandle->memRec[i].size, (uint16_t)1, 0, 0);
            }

        }
        algHandle->algState = ALG_ACTIVE;
    }

    return;
}

/*--------------------------------------------------------------------------*/
/* This is the function to do de-activation of algorithm. All scratch memory*/
/* are stoed to external memory in this                                     */
/* Refer algDeActivate function for details in ialg.h file                  */
/*--------------------------------------------------------------------------*/
XDAS_Void  TEMPLATE_MATCHING_TI_deactivate(IALG_Handle handle)
{
    TEMPLATE_MATCHING_TI_Handle algHandle = (TEMPLATE_MATCHING_TI_Handle)(void*)(handle);
    int32_t i;
    for(i= 1; i < algHandle->numMemRecs; i++)
    {
        if((i == ALG_HANDLE_INT_MEMREC) ||(i == GRAPH_OBJ_INT_MEMREC) )
        {
            EDMA_UTILS_memcpy2D((void*)algHandle->memRec[i-1].base, (const void*)algHandle->memRec[i].base, (uint16_t)algHandle->memRec[i].size, (uint16_t)1, 0, 0);
        }

    }
    algHandle->algState = ALG_NOT_ACTIVE;
    return;
}

/*--------------------------------------------------------------------------*/
/* This is the function which user can call to get back the memory given to */
/* algo                                                                     */
/* Refer algFree function for details in ialg.h file                        */
/*--------------------------------------------------------------------------*/
int32_t TEMPLATE_MATCHING_TI_free(IALG_Handle handle, IALG_MemRec memRec[])
{
    int32_t status            = IALG_EOK;
    TEMPLATE_MATCHING_TI_Handle algHandle = (TEMPLATE_MATCHING_TI_Handle)(void*)(handle);

    memcpy(memRec, algHandle->memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

    return status;
}

/*RESET_MISRA("15.1")  -> Reset rule 15.1 for GOTO */

