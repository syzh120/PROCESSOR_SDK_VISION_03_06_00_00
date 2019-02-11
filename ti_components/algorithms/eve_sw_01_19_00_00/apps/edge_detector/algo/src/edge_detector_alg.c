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
 *  @file       edge_detector_alg.c
 *
 *  @brief       This file defines the XDAIS/iVISION functions for Edge Detector applet
 *  @version     0.0 (Dec 2014) : Base version.
 */

/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/*#pragma RESET_MISRA ("required")*/

#include "edge_detector_alg_int.h"
#include "edma_utils_memcpy.h"
#include "evestarterware.h"
#include "edma_utils.h"


/**
 * IVISION interface of the algorithm
 */
const IVISION_Fxns EDGE_DETECTOR_TI_VISION_FXNS =
{
        {
                &EDGE_DETECTOR_TI_activate, /* module ID */
                &EDGE_DETECTOR_TI_activate,    /* activate */
                &EDGE_DETECTOR_TI_alloc,       /* algAlloc */
                NULL,                          /* control (not suported) */
                &EDGE_DETECTOR_TI_deactivate,  /* deactivate */
                &EDGE_DETECTOR_TI_free,        /* free */
                &EDGE_DETECTOR_TI_init,        /* init */
                NULL,                          /* moved (not suported) */
                &EDGE_DETECTOR_TI_numAlloc     /* algNumAlloc  */
        },
        &EDGE_DETECTOR_TI_process,
        &EDGE_DETECTOR_TI_control
};


/**
 * IRES interface of the algorithm
 */
const IRES_Fxns EDGE_DETECTOR_TI_IRES = {
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

/**
 * Other exposed functions
 */
int32_t EDGE_DETECTOR_TI_numAlloc(void)
{
    return NUM_MEMRECS;
}

/*---------------------------------------------------------------*/
/* Function to supply memory requirement to user                 */
/* refer algAlloc function for details in XADIS (ialg.h file)    */
/*---------------------------------------------------------------*/
int32_t EDGE_DETECTOR_TI_alloc(const IALG_Params *params,
        IALG_Fxns **parentFxns,
        IALG_MemRec memRec[])
{
    int32_t status = IALG_EOK;
    BAM_GraphMemReq graphMemReqGraph;
    const EDGE_DETECTOR_TI_CreateParams* createParams = (const EDGE_DETECTOR_TI_CreateParams * )(const void *)params;

    /*---------------------------------------------------------*/
    /* Request BAM public function about memories assosiated   */
    /* to graph creation                                       */
    /*---------------------------------------------------------*/
    if ( createParams->method == EDGE_DETECTOR_TI_METHOD_SOBEL )
    {
      EDGE_DETECTOR_SOBEL_TI_getGraphMemReq(&graphMemReqGraph);

    }
    else if ( createParams->method == EDGE_DETECTOR_TI_METHOD_CANNY )
    {
     EDGE_DETECTOR_CANNY_TI_getGraphMemReq(&graphMemReqGraph);
    }
    else
    {
      status = IALG_EFAIL;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }



    /*-----------------------------------------------------------------------------*/
    /*  For memory record ALG_HANDLE_INT_MEMREC and FAST9_GRAPH_OBJ_INT_MEMREC,          */
    /*  which are scratch buffers in BAM_MEMSPACE_DMEM, they must be preceded      */
    /*  by a persistent memory record in IALG_EXTERNAL of the same size.           */
    /*  This persistent record will be used to backup the following scratch        */
    /*  memory record during context saving when EDGE_DETECTOR_TI_deactivate */
    /*  is called. Likewise when EDGE_DETECTOR_TI_activate it called,        */
    /*  the content of the persistent memory record is copied back to the          */
    /*  scratch memory record in BAM_MEMSPACE_DMEM                                 */
    /*-----------------------------------------------------------------------------*/
    memRec[ALG_HANDLE_MEMREC].size          = sizeof(EDGE_DETECTOR_TI_Obj);
    memRec[ALG_HANDLE_MEMREC].space         = (IALG_MemSpace)IALG_EXTERNAL;
    memRec[ALG_HANDLE_MEMREC].attrs         = IALG_PERSIST;
    memRec[ALG_HANDLE_MEMREC].alignment     = 4U;

    memRec[ALG_HANDLE_INT_MEMREC].size      = sizeof(EDGE_DETECTOR_TI_Obj);
    memRec[ALG_HANDLE_INT_MEMREC].space     = (IALG_MemSpace)IALG_DARAM0;
    memRec[ALG_HANDLE_INT_MEMREC].attrs     = IALG_SCRATCH;
    memRec[ALG_HANDLE_INT_MEMREC].alignment = 4U;

    /*-------------------------------------------------------------------------*/
    /* Below 5 memory records are used to store data related to the BAM graph: */
    /* 1. EDGE_DETECTOR_GRAPH_OBJ_MEMREC     - To hold graph object in external memory       */
    /* 2. EDGE_DETECTOR_OBJ_INT_MEMREC - To hold the graph object in internal memory   */
    /* GRAPH OBJECT has 2 instances - internal and external memory - it is to  */
    /* speed up the processing - Main processing will work on internal memory  */
    /* instance and before any one else needing internal memory, deacitavte    */
    /* has to be performed by caller to make sure the data is backed up to ext */
    /* memory                                                                  */
    /*                                                                         */
    /* 3. EDGE_DETECTOR_SCRATCH_MEMREC -                                               */
    /*  It is used as scratch memory during graph create time                  */
    /*  Scratch mem is currently placed in external memory.                    */
    /*  For faster graph creation time, you can place it in internal memory    */
    /*                                                                         */
    /* 4. EDGE_DETECTOR_CONTEXT_MEMREC                                                 */
    /*  It is used to backup into external memory the graph's                  */
    /*  nodes internal memory records that are persistent.                     */
    /*                                                                         */
    /* 5. EDGE_DETECTOR_ARGS_MEMREC  -                                                 */
    /*   It is used keep kernels arguments during graph create time            */
    /*-------------------------------------------------------------------------*/

    memRec[EDGE_DETECTOR_GRAPH_OBJ_MEMREC].size  = graphMemReqGraph.graphObjSize;
    memRec[EDGE_DETECTOR_GRAPH_OBJ_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[EDGE_DETECTOR_GRAPH_OBJ_MEMREC].attrs = IALG_PERSIST;
    memRec[EDGE_DETECTOR_GRAPH_OBJ_MEMREC].alignment      = 4U;

    /*
    EDGE_DETECTOR_GRAPH_OBJ_INT_MEMREC is allocated in DMEM and is used when the backup is
    restored from external memory to faster internal memory when activate is called.
     */
    memRec[EDGE_DETECTOR_GRAPH_OBJ_INT_MEMREC].size  = graphMemReqGraph.graphObjSize;
    memRec[EDGE_DETECTOR_GRAPH_OBJ_INT_MEMREC].space =(IALG_MemSpace) IALG_DARAM0;
    memRec[EDGE_DETECTOR_GRAPH_OBJ_INT_MEMREC].attrs = IALG_SCRATCH;
    memRec[EDGE_DETECTOR_GRAPH_OBJ_INT_MEMREC].alignment  = 4U;

    memRec[EDGE_DETECTOR_GRAPH_SCRATCH_MEMREC].size  = graphMemReqGraph.graphScratchSize;
    memRec[EDGE_DETECTOR_GRAPH_SCRATCH_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[EDGE_DETECTOR_GRAPH_SCRATCH_MEMREC].attrs = IALG_SCRATCH;
    memRec[EDGE_DETECTOR_GRAPH_SCRATCH_MEMREC].alignment  = 4U;

    memRec[EDGE_DETECTOR_GRAPH_CONTEXT_MEMREC].size  = graphMemReqGraph.graphcontextSize;
    memRec[EDGE_DETECTOR_GRAPH_CONTEXT_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[EDGE_DETECTOR_GRAPH_CONTEXT_MEMREC].attrs = IALG_SCRATCH;
    memRec[EDGE_DETECTOR_GRAPH_CONTEXT_MEMREC].alignment  = 4U;

    memRec[EDGE_DETECTOR_GRAPH_ARGS_MEMREC].size  = graphMemReqGraph.graphArgsSize;
    memRec[EDGE_DETECTOR_GRAPH_ARGS_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[EDGE_DETECTOR_GRAPH_ARGS_MEMREC].attrs = IALG_SCRATCH;
    memRec[EDGE_DETECTOR_GRAPH_ARGS_MEMREC].alignment     = 4U;

Exit:

    return (status);
}

/*-----------------------------------------------------------------------*/
/* Function to accept memory pointers from user and initialize algorithm */
/* Refer algInit function for details in XADIS (ialg.h file)             */
/*-----------------------------------------------------------------------*/
int32_t EDGE_DETECTOR_TI_init(IALG_Handle handle,
        const IALG_MemRec memRec[],
        IALG_Handle parent,
        const IALG_Params * params)
{
    int32_t status = IALG_EOK;
    int32_t bamStatus;

    EDGE_DETECTOR_TI_Handle algHandle =
            (EDGE_DETECTOR_TI_Handle)(void *)memRec[ALG_HANDLE_MEMREC].base;
    const EDGE_DETECTOR_TI_CreateParams* createParams = (const EDGE_DETECTOR_TI_CreateParams * )(const void *)params;
    EDGE_DETECTOR_CANNY_TI_graphCreateParams     cannyCreateParams;
    EDGE_DETECTOR_SOBEL_TI_graphCreateParams           sobelGraphCreateParams;

    algHandle->edgeDetectGraphMem.graphObj      = memRec[EDGE_DETECTOR_GRAPH_OBJ_MEMREC].base;
    algHandle->edgeDetectGraphMem.graphScratch  = memRec[EDGE_DETECTOR_GRAPH_SCRATCH_MEMREC].base;
    algHandle->edgeDetectGraphMem.graphcontext  = memRec[EDGE_DETECTOR_GRAPH_CONTEXT_MEMREC].base;
    algHandle->edgeDetectGraphMem.graphArgs     = memRec[EDGE_DETECTOR_GRAPH_ARGS_MEMREC].base;


    algHandle->createParams = *createParams;

    if ( createParams->method == EDGE_DETECTOR_TI_METHOD_SOBEL )
    {
      sobelGraphCreateParams.iEdgeDetectorCreateParams = createParams;
      bamStatus = EDGE_DETECTOR_SOBEL_TI_graphCreate(&(algHandle->edgeDetectGraphMem),
                                                        &sobelGraphCreateParams);
    }
    else if ( createParams->method == EDGE_DETECTOR_TI_METHOD_CANNY)
    {
      cannyCreateParams.iEdgeDetectorCreateParams = createParams;
      bamStatus = EDGE_DETECTOR_CANNY_TI_graphCreate(&(algHandle->edgeDetectGraphMem),
                                                        &cannyCreateParams);
    }
    else
    {
      status = IALG_EFAIL;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    if ( bamStatus != BAM_S_SUCCESS)
    {
        status = IALG_EFAIL;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
       /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    algHandle->numMemRecs  = NUM_MEMRECS;
    memcpy(algHandle->memRec,memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);
    algHandle->ivision = &EDGE_DETECTOR_TI_VISION_FXNS;

    /*-----------------------------------------------------------------------*/
    /* State to indicate that internal context of algorithm is not active    */
    /*-----------------------------------------------------------------------*/
    algHandle->algState = ALG_NOT_ACTIVE;

    EDMA_UTILS_setEdma3RmHandle(NULL);

    Exit:
    return (status);
}

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define EDGE_DETECTOR_CEIL(x,y) ((( (x) + (y) - 1U) / (y)) * (y))
#define EDGE_DETECTOR_FLOOR(x,y) (( (x)  / (y)) * (y))
#define EDGE_DETECTOR_MIN(a, b) ((a) < (b) ? (a) : (b))
/* RESET_MISRA("19.7")  -> Reset rule 19.7  */

/*-----------------------------------------------------------------------*/
/* Function to accept any run time updates with recreation of object     */
/* Refer algControl function for details in ivision.h file               */
/* Not implemented for this function                                     */
/*-----------------------------------------------------------------------*/
int32_t EDGE_DETECTOR_TI_control(IVISION_Handle handle,
        IALG_Cmd cmd,
        const IALG_Params *inParams,
        IALG_Params *outParams)
{

  int32_t status = IALG_EOK;

  return (status);
}


/*--------------------------------------------------------------------------*/
/* This is the main processing function and should be called for each frame */
/* Refer process function for details in ivision.h file                     */
/*--------------------------------------------------------------------------*/
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7  */
/* MISRA.PPARAM.NEEDS.CONST:   Pointer parameter is not used to modify the addressed object but is not declared as a pointer to const*/
/* Pointer parameter inBufs and outBufs are not used to modify the addressed object but is not declared as a pointer to const. Fixing this will
    involve changing ivision interface and as this interface is already widely in use we have decided to waive this issue for such incidences */
int32_t EDGE_DETECTOR_TI_process(IVISION_Handle handle,
        IVISION_InBufs *inBufs,
        IVISION_OutBufs *outBufs,
        IVISION_InArgs *inArgs,
        IVISION_OutArgs *outArgs)
{
  /* RESET_MISRA("16.7")  -> Reset rule 16.7     */

    EDGE_DETECTOR_TI_Handle algHandle = (EDGE_DETECTOR_TI_Handle)(void *)(handle);
    EDGE_DETECTOR_TI_Handle intAlgHandle;
    int32_t status            = IALG_EOK;
    int32_t bamStatus;
    IBAMALG_InArgs          bamInArgs;
    IBAMALG_OutArgs         bamOutArgs;
    EDGE_DETECTOR_TI_InArgs          *edgeDetectorInArgs;
    uint8_t idx;
    uint16_t  imageWidth;
    uint16_t  imageHeight;
    uint16_t inputPitch;
    uint16_t outputPitch;
    uint8_t  *inputDataPtr;
    uint8_t  *outputDataPtr;
    uint8_t lowThreshold;
    uint8_t highThreshold;

    IVISION_BufDesc    *(*inBufDesc)[EDGE_DETECTOR_TI_BUFDESC_IN_TOTAL];
    IVISION_BufDesc    *(*outBufDesc)[EDGE_DETECTOR_TI_BUFDESC_OUT_TOTAL];


    inBufDesc  = (IVISION_BufDesc *(*)[EDGE_DETECTOR_TI_BUFDESC_IN_TOTAL])(void *)inBufs->bufDesc;
    outBufDesc = (IVISION_BufDesc *(*)[EDGE_DETECTOR_TI_BUFDESC_OUT_TOTAL])(void *)outBufs->bufDesc;

    if ( inBufs->numBufs < 1U )
    {
        status = IVISION_ERRORTYPE_NUM_INBUF_LESS;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }
    if (inArgs->size != sizeof(EDGE_DETECTOR_TI_InArgs))
    {
      status = IALG_EFAIL;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }


    edgeDetectorInArgs  = (EDGE_DETECTOR_TI_InArgs *)(void *)inArgs;

    /*-----------------------------------------------------------------------*/
    /* Activate the algorithm to make sure that now onwards internal memory  */
    /* handle can be utilized                                                */
    /*-----------------------------------------------------------------------*/
    EDGE_DETECTOR_TI_activate((IALG_Handle)(void *)handle);

    intAlgHandle                      = (EDGE_DETECTOR_TI_Handle)(void *)algHandle->memRec[ALG_HANDLE_INT_MEMREC].base;
    intAlgHandle->edgeDetectGraphMem.graphObj      =
            intAlgHandle->memRec[EDGE_DETECTOR_GRAPH_OBJ_INT_MEMREC].base;


    bamInArgs.size        = sizeof(IBAMALG_InArgs);
    bamInArgs.sliceIndex  = 0;

    bamOutArgs.size       = sizeof(IBAMALG_OutArgs);

    idx = EDGE_DETECTOR_TI_BUFDESC_IN_IMAGE;

    imageWidth  =  (*inBufDesc)[idx]->bufPlanes[0].frameROI.width;
    imageHeight =  (*inBufDesc)[idx]->bufPlanes[0].frameROI.height;

    inputPitch = (*inBufDesc)[idx]->bufPlanes[0].width;

    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are allocated from the user outside this applet hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
    rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    inputDataPtr = (uint8_t *)(*inBufDesc)[idx]->bufPlanes[0].buf +
                    ((*inBufDesc)[idx]->bufPlanes[0].frameROI.topLeft.y *
                    (*inBufDesc)[idx]->bufPlanes[0].width) +
                    (*inBufDesc)[idx]->bufPlanes[0].frameROI.topLeft.x;
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    idx = EDGE_DETECTOR_TI_BUFDESC_OUT_IMAGE_BUFFER;

    outputPitch = (*outBufDesc)[idx]->bufPlanes[0].width;


    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are allocated from the user outside this applet hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
    rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    outputDataPtr = (uint8_t *)(*outBufDesc)[idx]->bufPlanes[0].buf +
                    (((*outBufDesc)[idx]->bufPlanes[0].frameROI.topLeft.y)*
                    (*outBufDesc)[idx]->bufPlanes[0].width) +
                    (*outBufDesc)[idx]->bufPlanes[0].frameROI.topLeft.x;
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */


    if ( intAlgHandle->createParams.method == EDGE_DETECTOR_TI_METHOD_SOBEL)
    {
      bamStatus = EDGE_DETECTOR_SOBEL_TI_dmaControl(&(intAlgHandle->edgeDetectGraphMem),
                                         imageWidth,
                                         imageHeight,
                                         inputPitch,
                                         outputPitch,
                                         inputDataPtr,
                                         outputDataPtr,
                                         intAlgHandle->createParams.outputFormat);

      if (bamStatus != BAM_S_SUCCESS)
      {
          PRINTF("EDGE_DETECTOR_SOBEL_TI_dmaControl() returned error\n");
          /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
          /* GOTO is used at error check to jump to end of function, to exit.   */
          goto Exit;
          /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }


      bamStatus = EDGE_DETECTOR_SOBEL_TI_kernelControl(&(intAlgHandle->edgeDetectGraphMem),
                                                  edgeDetectorInArgs->threshold1,
                                                  intAlgHandle->createParams.outputFormat);

      if (bamStatus != BAM_S_SUCCESS)
      {
          status = IALG_EFAIL;
          PRINTF("EDGE_DETECTOR_SOBEL_TI_kernelControl() returned error\n");
          /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
          /* GOTO is used at error check to jump to end of function, to exit.   */
          goto Exit;
          /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }

      bamStatus = EDGE_DETECTOR_SOBEL_TI_execute(&(intAlgHandle->edgeDetectGraphMem), &bamInArgs,&bamOutArgs);

      if (bamStatus != BAM_S_SUCCESS)
      {
          status = IALG_EFAIL;

          PRINTF("EDGE_DETECTOR_SOBEL_TI_execute() returned error\n");
          /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
          /* GOTO is used at error check to jump to end of function, to exit.   */
          goto Exit;
          /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }
    }
    else if ( intAlgHandle->createParams.method == EDGE_DETECTOR_TI_METHOD_CANNY )
    {
      bamStatus = EDGE_DETECTOR_CANNY_TI_dmaControl(&(intAlgHandle->edgeDetectGraphMem),
                                               imageWidth,
                                               imageHeight,
                                               inputPitch,
                                               outputPitch,
                                               inputDataPtr,
                                               outputDataPtr,
                                               intAlgHandle->createParams.outputFormat);

        if (bamStatus != BAM_S_SUCCESS)
        {
            status = IALG_EFAIL;

            PRINTF("EDGE_DETECTOR_TI_dmaControl() returned error\n");
            /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
            /* GOTO is used at error check to jump to end of function, to exit.   */
            goto Exit;
            /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
        }

        lowThreshold  = edgeDetectorInArgs->threshold1;
        highThreshold = edgeDetectorInArgs->threshold2;

        if ( edgeDetectorInArgs->threshold1 > edgeDetectorInArgs->threshold2)
        {
          lowThreshold  = edgeDetectorInArgs->threshold2;
          highThreshold = edgeDetectorInArgs->threshold1;
        }
        bamStatus = EDGE_DETECTOR_CANNY_TI_kernelControl(&(intAlgHandle->edgeDetectGraphMem),
                                                    lowThreshold,
                                                    highThreshold);

        if (bamStatus != BAM_S_SUCCESS)
        {
            status = IALG_EFAIL;
            PRINTF("EDGE_DETECTOR_TI_execute() returned error\n");
            /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
            /* GOTO is used at error check to jump to end of function, to exit.   */
            goto Exit;
            /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
        }

        bamStatus = EDGE_DETECTOR_CANNY_TI_execute(&(intAlgHandle->edgeDetectGraphMem), &bamInArgs,&bamOutArgs);

        if (bamStatus != BAM_S_SUCCESS)
        {
            status = IALG_EFAIL;
            PRINTF("EDGE_DETECTOR_TI_execute() returned error\n");
            /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
            /* GOTO is used at error check to jump to end of function, to exit.   */
            goto Exit;
            /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
        }
    }
    else
    {
      status = IALG_EFAIL;
      PRINTF("Unsupported method for edge detection\n");
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

Exit:
    /*----------------------------------*/
    /* Free the input and output buffer */
    /*----------------------------------*/
    outArgs->inFreeBufIDs[EDGE_DETECTOR_TI_BUFDESC_IN_IMAGE] =
            (*inBufDesc)[EDGE_DETECTOR_TI_BUFDESC_IN_IMAGE]->bufferId ;

    outArgs->inFreeBufIDs[EDGE_DETECTOR_TI_BUFDESC_IN_TOTAL] = 0 ;

    outArgs->outFreeBufIDs[EDGE_DETECTOR_TI_BUFDESC_OUT_IMAGE_BUFFER] =
                (*outBufDesc)[EDGE_DETECTOR_TI_BUFDESC_OUT_IMAGE_BUFFER]->bufferId ;

    (*outBufDesc)[EDGE_DETECTOR_TI_BUFDESC_OUT_IMAGE_BUFFER]->bufPlanes[0].accessMask =
            IVISION_ACCESSMODE_HWA;

    return status;
}

/*--------------------------------------------------------------------------*/
/* This is the function to do activation of algorithm. All scratch memory   */
/* are restored in this                                                     */
/* Refer algActivate function for details in ialg.h file                    */
/*--------------------------------------------------------------------------*/
void  EDGE_DETECTOR_TI_activate(IALG_Handle handle)
{
    EDGE_DETECTOR_TI_Handle algHandle = (EDGE_DETECTOR_TI_Handle)(void *)(handle);
    uint32_t i;

    /*----------------------------------------------------------------*/
    /* Do Activation only if it is deactivated or just after creation */
    /*----------------------------------------------------------------*/
    if(algHandle->algState == ALG_NOT_ACTIVE)
    {
        for(i= 1U; i < algHandle->numMemRecs; i++)
        {
            if((i == ALG_HANDLE_INT_MEMREC) ||(i == EDGE_DETECTOR_GRAPH_OBJ_INT_MEMREC))
            {

                EDMA_UTILS_memcpy2D(algHandle->memRec[i].base,
                        algHandle->memRec[i-1U].base,
                        algHandle->memRec[i].size,
                        1U,
                        0,
                        0);
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
void  EDGE_DETECTOR_TI_deactivate(IALG_Handle handle)
{
    EDGE_DETECTOR_TI_Handle algHandle = (EDGE_DETECTOR_TI_Handle)(void *)(handle);
    uint32_t i;
    /*----------------------------------------------------------------*/
    /* Do De-activation only if it is deactivated or just after creation */
    /*----------------------------------------------------------------*/
    if(algHandle->algState == ALG_ACTIVE)
    {
        for(i= 1U; i < algHandle->numMemRecs; i++)
        {
            if((i == ALG_HANDLE_INT_MEMREC) ||(i == EDGE_DETECTOR_GRAPH_OBJ_INT_MEMREC))
            {
                EDMA_UTILS_memcpy2D(algHandle->memRec[i-1U].base,
                        algHandle->memRec[i].base,
                        algHandle->memRec[i].size,
                        1U,
                        0,
                        0);
            }

        }
        algHandle->algState = ALG_NOT_ACTIVE;
    }
    return;
}

/*--------------------------------------------------------------------------*/
/* This is the function which user can call to get back the memory given to */
/* algo                                                                     */
/* Refer algFree function for details in ialg.h file                        */
/*--------------------------------------------------------------------------*/
int32_t EDGE_DETECTOR_TI_free(IALG_Handle handle, IALG_MemRec memRec[])
{
    int32_t status            = IALG_EOK;
    EDGE_DETECTOR_TI_Handle algHandle = (EDGE_DETECTOR_TI_Handle)(void *)(handle);

    memcpy(memRec, algHandle->memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

    return status;
}
