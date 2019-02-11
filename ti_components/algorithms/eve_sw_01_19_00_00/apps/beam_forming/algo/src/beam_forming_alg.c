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
*  @file       beam_forming_alg.c
*
*  @brief       This file defines the XDAIS/iVISION functions for Beam Forming applet
*  @version     0.0 (Jan 2017) : Base version.
*/

/* #pragma CHECK_MISRA ("none") */
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

/* #pragma RESET_MISRA ("required") */

#include "beam_forming_alg_int.h"
#include "beam_forming_graph_int.h"

#include "edma_utils_memcpy.h"
#include "evestarterware.h"
#include "edma_utils.h"
#include "vcop_beam_forming_kernel.h"


#define INDIVIDUAL_PROFILING (0)

#if (INDIVIDUAL_PROFILING)
#include "eve_profile.h"
#endif

/**
* IVISION interface of the algorithm
*/
const IVISION_Fxns BEAM_FORMING_TI_VISION_FXNS =
{
  {
      &BEAM_FORMING_TI_activate, /* module ID */
      &BEAM_FORMING_TI_activate,    /* activate */
      &BEAM_FORMING_TI_alloc,       /* algAlloc */
      NULL,                      /* control (not suported) */
      &BEAM_FORMING_TI_deactivate,  /* deactivate */
      &BEAM_FORMING_TI_free,        /* free */
      &BEAM_FORMING_TI_init,        /* init */
      NULL,                      /* moved (not suported) */
      &BEAM_FORMING_TI_numAlloc     /* algNumAlloc  */
  },
  &BEAM_FORMING_TI_process,
  &BEAM_FORMING_TI_control
};


#define BEAM_FORMING_MAX_NUM_ANGLE (65535U)

/**
* IRES interface of the algorithm
*/
const IRES_Fxns BEAM_FORMING_TI_IRES = {
  NULL,
  NULL,                                     /*getResourceDescriptors, */
  NULL,                                     /*numResourceDescriptors */
  NULL  ,                                     /*initResources,  */
  NULL,                                     /*reinitResources, */
  NULL,                                     /*deinitResources, */
  NULL,                                     /*activateResource,*/
  NULL,                                     /*activateAllResources, */
  NULL,                                     /*deactivateResource,   */
  NULL                                      /*deactivateAllResources */
};

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define CLIP(x,y) ((( (x) / (y)) * (y))
#define ALIGN(x,y)         ((((x) + (y) - 1U)/(y))*(y))

/* RESET_MISRA("19.7")  -> Reset rule 19.7  */


#define BEAM_FORMING_IMGBUFLA_ADDRESS   ((void*) 0x40050000)
#define BEAM_FORMING_IMGBUFHA_ADDRESS   ((void*) 0x40054000)
#define BEAM_FORMING_IMGBUFLB_ADDRESS   ((void*) 0x40070000)
#define BEAM_FORMING_IMGBUFHB_ADDRESS   ((void*) 0x40074000)

/**
* Internally used functions
*/

/**
* Other exposed functions
*/
int32_t BEAM_FORMING_TI_numAlloc(void)
{
  return (NUM_MEMRECS);
}

/*---------------------------------------------------------------*/
/* Function to supply memory requirement to user                 */
/* refer algAlloc function for details in XADIS (ialg.h file)    */
/*---------------------------------------------------------------*/
int32_t BEAM_FORMING_TI_alloc(const IALG_Params *params,
                                       IALG_Fxns **parentFxns,
                                       IALG_MemRec       memRec[])
{
    int32_t status = IALG_EOK;
    BAM_GraphMemReq graphMemReqGraph;


    const BEAM_FORMING_TI_CreateParams * createParams =
    (const BEAM_FORMING_TI_CreateParams*)(const void *)params;
    /*---------------------------------------------------------*/
    /* Request BAM public function about memories assosiated   */
    /* to graph creation                                       */
    /*---------------------------------------------------------*/
    BEAM_FORMING_TI_getGraphMemReq(&graphMemReqGraph);



    /*-----------------------------------------------------------------------------*/
    /*  For memory record ALG_HANDLE_INT_MEMREC and FAST9_GRAPH_OBJ_INT_MEMREC,          */
    /*  which are scratch buffers in BAM_MEMSPACE_DMEM, they must be preceded      */
    /*  by a persistent memory record in IALG_EXTERNAL of the same size.           */
    /*  This persistent record will be used to backup the following scratch        */
    /*  memory record during context saving when BEAM_FORMING_TI_deactivate */
    /*  is called. Likewise when BEAM_FORMING_TI_activate it called,        */
    /*  the content of the persistent memory record is copied back to the          */
    /*  scratch memory record in BAM_MEMSPACE_DMEM                                 */
    /*-----------------------------------------------------------------------------*/
    memRec[ALG_HANDLE_MEMREC].size          = sizeof(BEAM_FORMING_TI_Obj);
    memRec[ALG_HANDLE_MEMREC].space         = (IALG_MemSpace)IALG_EXTERNAL;
    memRec[ALG_HANDLE_MEMREC].attrs         = IALG_PERSIST;
    memRec[ALG_HANDLE_MEMREC].alignment     = 4U;

    memRec[ALG_HANDLE_INT_MEMREC].size      = sizeof(BEAM_FORMING_TI_Obj);
    memRec[ALG_HANDLE_INT_MEMREC].space     = (IALG_MemSpace)IALG_DARAM0;
    memRec[ALG_HANDLE_INT_MEMREC].attrs     = IALG_SCRATCH;
    memRec[ALG_HANDLE_INT_MEMREC].alignment = 4U;

    /*-------------------------------------------------------------------------*/
    /* Below 5 memory records are used to store data related to the BAM graph: */
    /* 1. BEAM_FORMING_GRAPH_OBJ_MEMREC     - To hold graph object in external memory       */
    /* 2. BEAM_FORMING_OBJ_INT_MEMREC - To hold the graph object in internal memory   */
    /* GRAPH OBJECT has 2 instances - internal and external memory - it is to  */
    /* speed up the processing - Main processing will work on internal memory  */
    /* instance and before any one else needing internal memory, deacitavte    */
    /* has to be performed by caller to make sure the data is backed up to ext */
    /* memory                                                                  */
    /*                                                                         */
    /* 3. BEAM_FORMING_SCRATCH_MEMREC -                                               */
    /*  It is used as scratch memory during graph create time                  */
    /*  Scratch mem is currently placed in external memory.                    */
    /*  For faster graph creation time, you can place it in internal memory    */
    /*                                                                         */
    /* 4. BEAM_FORMING_CONTEXT_MEMREC                                                 */
    /*  It is used to backup into external memory the graph's                  */
    /*  nodes internal memory records that are persistent.                     */
    /*                                                                         */
    /* 5. BEAM_FORMING_ARGS_MEMREC  -                                                 */
    /*   It is used keep kernels arguments during graph create time            */
    /*-------------------------------------------------------------------------*/

    memRec[BEAM_FORMING_GRAPH_OBJ_MEMREC].size  = graphMemReqGraph.graphObjSize;
    memRec[BEAM_FORMING_GRAPH_OBJ_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[BEAM_FORMING_GRAPH_OBJ_MEMREC].attrs = IALG_PERSIST;
    memRec[BEAM_FORMING_GRAPH_OBJ_MEMREC].alignment      = 4U;

    /*
    BEAM_FORMING_GRAPH_OBJ_INT_MEMREC is allocated in DMEM and is used when the backup is
    restored from external memory to faster internal memory when activate is called.
     */
    memRec[BEAM_FORMING_GRAPH_OBJ_INT_MEMREC].size  = graphMemReqGraph.graphObjSize;
    memRec[BEAM_FORMING_GRAPH_OBJ_INT_MEMREC].space =(IALG_MemSpace) IALG_DARAM0;
    memRec[BEAM_FORMING_GRAPH_OBJ_INT_MEMREC].attrs = IALG_SCRATCH;
    memRec[BEAM_FORMING_GRAPH_OBJ_INT_MEMREC].alignment  = 4U;

    memRec[BEAM_FORMING_GRAPH_SCRATCH_MEMREC].size  = graphMemReqGraph.graphScratchSize;
    memRec[BEAM_FORMING_GRAPH_SCRATCH_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[BEAM_FORMING_GRAPH_SCRATCH_MEMREC].attrs = IALG_SCRATCH;
    memRec[BEAM_FORMING_GRAPH_SCRATCH_MEMREC].alignment  = 4U;

    memRec[BEAM_FORMING_GRAPH_CONTEXT_MEMREC].size  = graphMemReqGraph.graphcontextSize;
    memRec[BEAM_FORMING_GRAPH_CONTEXT_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[BEAM_FORMING_GRAPH_CONTEXT_MEMREC].attrs = IALG_SCRATCH;
    memRec[BEAM_FORMING_GRAPH_CONTEXT_MEMREC].alignment  = 4U;

    memRec[BEAM_FORMING_GRAPH_ARGS_MEMREC].size  = graphMemReqGraph.graphArgsSize;
    memRec[BEAM_FORMING_GRAPH_ARGS_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[BEAM_FORMING_GRAPH_ARGS_MEMREC].attrs = IALG_SCRATCH;
    memRec[BEAM_FORMING_GRAPH_ARGS_MEMREC].alignment     = 4U;

    /* This buffer is to store angle and detection for sorting */
    memRec[BEAM_FORMING_ANGLE_DETECTION_BUF_MEMREC].size  = createParams->maxNumDetection * sizeof(uint32_t);
    memRec[BEAM_FORMING_ANGLE_DETECTION_BUF_MEMREC].space =(IALG_MemSpace) IALG_DARAM0;
    memRec[BEAM_FORMING_ANGLE_DETECTION_BUF_MEMREC].attrs = IALG_SCRATCH;
    memRec[BEAM_FORMING_ANGLE_DETECTION_BUF_MEMREC].alignment     = 4U;

    /* This buffer is used to share information between DMA node and kernel node. This is mainly used
    to indicate kernel node whether to do SM copy or not */
    memRec[BEAM_FORMING_ENABLE_SM_COPY_SHARED_BUF_MEMREC].size  = sizeof(uint32_t);
    memRec[BEAM_FORMING_ENABLE_SM_COPY_SHARED_BUF_MEMREC].space =(IALG_MemSpace) IALG_DARAM0;
    memRec[BEAM_FORMING_ENABLE_SM_COPY_SHARED_BUF_MEMREC].attrs = IALG_SCRATCH;
    memRec[BEAM_FORMING_ENABLE_SM_COPY_SHARED_BUF_MEMREC].alignment     = 4U;


    return (status);
}


/*-----------------------------------------------------------------------*/
/* Function to accept memory pointers from user and initialize algorithm */
/* Refer algInit function for details in XADIS (ialg.h file)             */
/*-----------------------------------------------------------------------*/
int32_t BEAM_FORMING_TI_init(IALG_Handle        handle,
                                     const IALG_MemRec  memRec[],
                                     IALG_Handle        parent,
                                     const IALG_Params *params)
{
    int32_t status = IALG_EOK;
    int32_t bamStatus;

    BEAM_FORMING_TI_Coordinates coordinateStruct;
    uint16_t * energyBaseAddress;
    uint16_t * angleBaseAddress;

    BEAM_FORMING_TI_Handle algHandle =
            (BEAM_FORMING_TI_Handle)(void *)memRec[ALG_HANDLE_MEMREC].base;
    const BEAM_FORMING_TI_CreateParams* createParams = (const BEAM_FORMING_TI_CreateParams * )(const void *)params;
    BEAM_FORMING_TI_graphCreateParams     graphCreateParams;

    energyBaseAddress = &coordinateStruct.energy;
    angleBaseAddress  = &coordinateStruct.angleBin;

    /* It is expected that eneryg and angle are stored next to each other and hence have a assert for them incase
    anyone changes this order */
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
    /* This statement is under assert and hence wont be present in release build   */
    assert(((uint32_t)angleBaseAddress - (uint32_t)energyBaseAddress) == sizeof(uint16_t));
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */


    if ( createParams->maxNumDetection > BEAM_FORMING_TI_MAX_NUM_DETECTIONS )
    {
     status = BEAM_FORMING_TI_ERRORTYPE_UNSUPPORTED_NUM_DETECTIONS;
     /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
     /* GOTO is used at error check to jump to end of function, to exit.   */
     goto Exit;
     /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    if ( (createParams->maxNumAngle * createParams->maxNumAntenna * sizeof (int16_t ) * 2U) > BEAM_FORMING_TI_MAX_STEERING_MATRIX_SIZE )
    {
     status = BEAM_FORMING_TI_ERRORTYPE_UNSUPPORTED_STEERINGMATRIX_SIZE;
     /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
     /* GOTO is used at error check to jump to end of function, to exit.   */
     goto Exit;
     /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    algHandle->graphMem.graphObj      = memRec[BEAM_FORMING_GRAPH_OBJ_MEMREC].base;
    algHandle->graphMem.graphScratch  = memRec[BEAM_FORMING_GRAPH_SCRATCH_MEMREC].base;
    algHandle->graphMem.graphcontext  = memRec[BEAM_FORMING_GRAPH_CONTEXT_MEMREC].base;
    algHandle->graphMem.graphArgs     = memRec[BEAM_FORMING_GRAPH_ARGS_MEMREC].base;


    algHandle->createParams = *createParams;

    graphCreateParams.iBeamFormingCreateParams = createParams;
    bamStatus = BEAM_FORMING_TI_graphCreate(&(algHandle->graphMem),
                                                      &graphCreateParams);

    if ( bamStatus == BAM_E_BLOCK_DIM_TOO_BIG)
    {
        status = BEAM_FORMING_TI_ERRORTYPE_UNSUPPORTED_CONFIGURATION;
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
    algHandle->ivision = &BEAM_FORMING_TI_VISION_FXNS;

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
/* Not implemented for this function                                     */
/*-----------------------------------------------------------------------*/
int32_t BEAM_FORMING_TI_control(IVISION_Handle     handle,
                                          IALG_Cmd           cmd,
                                          const IALG_Params *inParams,
                                          IALG_Params       *outParams)
{
  return (IALG_EOK);
}

/*--------------------------------------------------------------------------*/
/* This is the main processing function and should be called for each frame */
/* Refer process function for details in ivision.h file                     */
/*--------------------------------------------------------------------------*/
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter inBufs and outBufs are not used to modify the addressed object but is not declared as a pointer to const */
/* Deviation is allowed because this function is of type IVISION_Fxns : algProcess in order to be ASSIGNED IVISION_Fxns */
int32_t BEAM_FORMING_TI_process(IVISION_Handle   handle,
                                           IVISION_InBufs  *inBufs,
                                           IVISION_OutBufs *outBufs,
                                           IVISION_InArgs  *inArgs,
                                           IVISION_OutArgs *outArgs)
{
  /* RESET_MISRA("16.7")  -> Reset rule 16.7     */

    BEAM_FORMING_TI_Handle algHandle = (BEAM_FORMING_TI_Handle)(void *)(handle);
    BEAM_FORMING_TI_Handle intAlgHandle;
    int32_t status            = IALG_EOK;
    int32_t bamStatus  = BAM_S_SUCCESS;
    IBAMALG_InArgs          bamInArgs;
    IBAMALG_OutArgs         bamOutArgs;
    BEAM_FORMING_TI_InArgs  *beam_formingInArgs;
    BEAM_FORMING_TI_Coordinates *pInCoordinateBufPtr;
    BEAM_FORMING_TI_Coordinates *pOutCoordinateBufPtr;
    BEAM_FORMING_TI_Coordinates *pOutCoordinateBufPtrIBUFL;
    uint32_t idx, i ;
    uint8_t * antennaDataPtr;
    uint8_t * steeringMatrixPtr;
    uint8_t * coordinateBufPtr;
    uint16_t (*angleDetectionBufDMEM)[BEAM_FORMING_TI_MAX_NUM_DETECTIONS];
    uint16_t (*angleDetectionBufIBUFH)[BEAM_FORMING_TI_MAX_NUM_DETECTIONS];
    uint32_t *enableSMcopyShared;
    uint16_t * WBUFAnglePtr;
    uint16_t * WBUFenergyPtr;
    uint16_t * WBUFpBlockPtr;

    /*-----------------------------------------------------------------
                For test purpose it is allocated in stack. Application may get
                this descriptors from its buffer manager
                -----------------------------------------------------------------*/
    /*-----------------------------------------------------------------
                For test purpose it is allocated in stack. Application may get
                this descriptors from its buffer manager
    -----------------------------------------------------------------*/
    IVISION_BufDesc    *(*inBufDesc)[BEAM_FORMING_TI_BUFDESC_IN_TOTAL];
    IVISION_BufDesc    *(*outBufDesc)[BEAM_FORMING_TI_BUFDESC_OUT_TOTAL];


    inBufDesc  = (IVISION_BufDesc *(*)[BEAM_FORMING_TI_BUFDESC_IN_TOTAL])(void *)inBufs->bufDesc;
    outBufDesc = (IVISION_BufDesc *(*)[BEAM_FORMING_TI_BUFDESC_OUT_TOTAL])(void *)outBufs->bufDesc;

    if (inArgs->size != sizeof(BEAM_FORMING_TI_InArgs))
    {
      status = IALG_EFAIL;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }
    if (outArgs->size != sizeof(BEAM_FORMING_TI_OutArgs))
    {
      status = IALG_EFAIL;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    beam_formingInArgs  = (BEAM_FORMING_TI_InArgs *)(void *)inArgs;

    /*-----------------------------------------------------------------------*/
    /* Activate the algorithm to make sure that now onwards internal memory  */
    /* handle can be utilized                                                */
    /*-----------------------------------------------------------------------*/
    BEAM_FORMING_TI_activate((IALG_Handle)(void *)handle);

    intAlgHandle                      = (BEAM_FORMING_TI_Handle)(void *)algHandle->memRec[ALG_HANDLE_INT_MEMREC].base;
    intAlgHandle->graphMem.graphObj      =
            intAlgHandle->memRec[BEAM_FORMING_GRAPH_OBJ_INT_MEMREC].base;


    bamInArgs.size        = sizeof(IBAMALG_InArgs);
    bamInArgs.sliceIndex  = 0;

    bamOutArgs.size       = sizeof(IBAMALG_OutArgs);

    if ( beam_formingInArgs->numDetections > intAlgHandle->createParams.maxNumDetection)
    {
      status = BEAM_FORMING_TI_ERRORTYPE_UNSUPPORTED_NUM_DETECTIONS;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    if ( (beam_formingInArgs->numAngles * beam_formingInArgs->numAntennas * sizeof (int16_t ) * 2U) > BEAM_FORMING_TI_MAX_STEERING_MATRIX_SIZE )
    {
      status = BEAM_FORMING_TI_ERRORTYPE_UNSUPPORTED_STEERINGMATRIX_SIZE;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    if (beam_formingInArgs->numDetections == 0 )
    {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }
    idx = BEAM_FORMING_TI_BUFDESC_IN_ANTENNA_DATA_BUF;

    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are allocated from the user outside this applet hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
    rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    antennaDataPtr = (uint8_t *)(*inBufDesc)[idx]->bufPlanes[0].buf;
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    idx = BEAM_FORMING_TI_BUFDESC_IN_STEERINGMATRIX_BUF;

    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are allocated from the user outside this applet hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
    rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    steeringMatrixPtr = (uint8_t *)(*inBufDesc)[idx]->bufPlanes[0].buf;
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    idx = BEAM_FORMING_TI_BUFDESC_IN_COORDINATE_BUF;

    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are allocated from the user outside this applet hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
    rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    coordinateBufPtr = (uint8_t *)(*inBufDesc)[idx]->bufPlanes[0].buf;
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    idx = BEAM_FORMING_TI_BUFDESC_OUT_BUFFER;
    pInCoordinateBufPtr = (BEAM_FORMING_TI_Coordinates *)(void *)coordinateBufPtr;
    pOutCoordinateBufPtr = (BEAM_FORMING_TI_Coordinates *)(void *)(*outBufDesc)[idx]->bufPlanes[0].buf;

    angleDetectionBufDMEM  = (uint16_t (*)[BEAM_FORMING_TI_MAX_NUM_DETECTIONS])(void *)algHandle->memRec[BEAM_FORMING_ANGLE_DETECTION_BUF_MEMREC].base;
    enableSMcopyShared = (uint32_t*)(void *)algHandle->memRec[BEAM_FORMING_ENABLE_SM_COPY_SHARED_BUF_MEMREC].base;




#if INDIVIDUAL_PROFILING
    profiler_start();
#endif


    for ( i = 0; i < intAlgHandle->createParams.maxNumDetection; i++)
    {
      (*angleDetectionBufDMEM)[2U * i] = (uint16_t)i;
    }


#if INDIVIDUAL_PROFILING
    profiler_end_print(1);
    profiler_start();
#endif
    bamStatus = BEAM_FORMING_TI_dmaControl(&(intAlgHandle->graphMem),
                                      beam_formingInArgs->numAngles,
                                      beam_formingInArgs->numAntennas,
                                      beam_formingInArgs->numDetections,
                                      antennaDataPtr,
                                      steeringMatrixPtr,
                                      (*angleDetectionBufDMEM),
                                      enableSMcopyShared);


    if (bamStatus == BAM_S_SUCCESS)
    {
      bamStatus = BEAM_FORMING_TI_kernelControl(&(intAlgHandle->graphMem),
                                                beam_formingInArgs->numAngles,
                                                beam_formingInArgs->numAntennas,
                                                beam_formingInArgs->beamFormingScaling,
                                                beam_formingInArgs->energyScaling,
                                                enableSMcopyShared);
    }

    if (bamStatus == BAM_S_SUCCESS)
    {
      bamStatus = BEAM_FORMING_TI_getWBUFptr(&(intAlgHandle->graphMem),
                                                &WBUFAnglePtr,
                                                &WBUFenergyPtr,
                                                &WBUFpBlockPtr);
    }

    if (bamStatus == BAM_S_SUCCESS)
    {
      bamStatus = BEAM_FORMING_TI_execute(&(intAlgHandle->graphMem), &bamInArgs,&bamOutArgs);
    }

    if ( bamStatus != BAM_S_SUCCESS)
    {
        status = IALG_EFAIL;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

#if INDIVIDUAL_PROFILING
    profiler_end_print(1);
    profiler_start();
#endif

#if (!VCOP_HOST_EMULATION)
      /* At this point of time WBUFAnglePtr, WBUFenergyPtr and WBUFpBlockPtr  are in WBUF,
      and IBUFLA IBUFHA are fully available      for use. Hence directly use them */
      VCOP_SET_MEM_VIEW ((uint32_t)FLAT_MEM_VIEW);

      pOutCoordinateBufPtrIBUFL = (BEAM_FORMING_TI_Coordinates *)BEAM_FORMING_IMGBUFLA_ADDRESS;/*IBUFLA*/
      angleDetectionBufIBUFH    = (uint16_t (*)[BEAM_FORMING_TI_MAX_NUM_DETECTIONS])BEAM_FORMING_IMGBUFLB_ADDRESS;/*IBUFLA*/

#else
      pOutCoordinateBufPtrIBUFL = (BEAM_FORMING_TI_Coordinates *)malloc((beam_formingInArgs->numDetections + VCOP_SIMD_WIDTH )*
                                                              sizeof(BEAM_FORMING_TI_Coordinates));
      angleDetectionBufIBUFH = (uint16_t (*)[BEAM_FORMING_TI_MAX_NUM_DETECTIONS])malloc((beam_formingInArgs->numDetections + VCOP_SIMD_WIDTH) *
                                                              sizeof(uint16_t) * 2U);

#endif

  /* Copy full coordinate buff from DDR to internal memory of EVE before starting to process */
  if ( intAlgHandle->createParams.coordinateBufFormat == BEAM_FORMING_TI_COORDINATE_BUF_FORMAT_1)
  {
    EDMA_UTILS_memcpy2D(pOutCoordinateBufPtrIBUFL,
                        pInCoordinateBufPtr,
                        sizeof(BEAM_FORMING_TI_Coordinates),
                        beam_formingInArgs->numDetections,
                        (int16_t)sizeof(BEAM_FORMING_TI_Coordinates),
                        (int16_t)sizeof(BEAM_FORMING_TI_Coordinates));
  }
  else if ( intAlgHandle->createParams.coordinateBufFormat == BEAM_FORMING_TI_COORDINATE_BUF_FORMAT_2)
  {
      EDMA_UTILS_memcpy2D(pOutCoordinateBufPtrIBUFL,
                      pInCoordinateBufPtr,
                      sizeof(uint32_t),
                      beam_formingInArgs->numDetections,
                      (int16_t)sizeof(BEAM_FORMING_TI_Coordinates),
                      sizeof(uint32_t));
  }
  else
  {
    status = BEAM_FORMING_TI_ERRORTYPE_UNSUPPORTED_COORDINATE_FORMAT;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  EDMA_UTILS_memcpy2D((*angleDetectionBufIBUFH),
                      angleDetectionBufDMEM,
                      beam_formingInArgs->numDetections * sizeof(uint16_t) * 2U,
                      1U,
                      0,
                      0);

  for ( i = 0 ; i < ((ALIGN_SIMD(beam_formingInArgs->numDetections)) - beam_formingInArgs->numDetections); i++)
  {
    idx = i + beam_formingInArgs->numDetections;
    (*angleDetectionBufIBUFH)[2U * idx ] = beam_formingInArgs->numDetections;
  }
#if (!VCOP_HOST_EMULATION)
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_VCOP, IBUFLB_VCOP, IBUFHA_SYST, IBUFLA_SYST);
    vcop_range_doppler_energy_angle_mapping_kernel_init((uint32_t*)(void *)&pOutCoordinateBufPtrIBUFL->energy,
                                                        (*angleDetectionBufIBUFH),
                                                        WBUFAnglePtr,
                                                        WBUFenergyPtr,
                                                        sizeof(BEAM_FORMING_TI_Coordinates),
                                                        beam_formingInArgs->numDetections,
                                                        WBUFpBlockPtr);
    VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP, IBUFHA_VCOP, IBUFLA_VCOP);
    vcop_range_doppler_energy_angle_mapping_kernel_vloops(WBUFpBlockPtr);
    _vcop_vloop_done();
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);
#else

    vcop_range_doppler_energy_angle_mapping_kernel((uint32_t*)(void *)&pOutCoordinateBufPtrIBUFL->energy,
                                                    (*angleDetectionBufIBUFH),
                                                    WBUFAnglePtr,
                                                    WBUFenergyPtr,
                                                    sizeof(BEAM_FORMING_TI_Coordinates),
                                                    beam_formingInArgs->numDetections
                                                    );
#endif

    /* Copy full coordinate buff from internal memory of EVE to DDR after process */
     EDMA_UTILS_memcpy2D(pOutCoordinateBufPtr,
                         pOutCoordinateBufPtrIBUFL,
                         sizeof(BEAM_FORMING_TI_Coordinates),
                         beam_formingInArgs->numDetections,
                         (int16_t)sizeof(BEAM_FORMING_TI_Coordinates),
                         (int16_t)sizeof(BEAM_FORMING_TI_Coordinates));

#if INDIVIDUAL_PROFILING
    profiler_end_print(1);
#endif


#if VCOP_HOST_EMULATION
    if ( pOutCoordinateBufPtrIBUFL )
    {
      free(pOutCoordinateBufPtrIBUFL);
      pOutCoordinateBufPtrIBUFL = NULL;
    }
    if ( angleDetectionBufIBUFH )
    {
      free(angleDetectionBufIBUFH);
      angleDetectionBufIBUFH = NULL;
    }
#endif

Exit:
    /*----------------------------------*/
    /* Free the input and output buffer */
    /*----------------------------------*/
    outArgs->inFreeBufIDs[BEAM_FORMING_TI_BUFDESC_IN_ANTENNA_DATA_BUF] =
            (*inBufDesc)[BEAM_FORMING_TI_BUFDESC_IN_ANTENNA_DATA_BUF]->bufferId ;

    outArgs->inFreeBufIDs[BEAM_FORMING_TI_BUFDESC_IN_COORDINATE_BUF] =
            (*inBufDesc)[BEAM_FORMING_TI_BUFDESC_IN_COORDINATE_BUF]->bufferId ;

    outArgs->inFreeBufIDs[BEAM_FORMING_TI_BUFDESC_IN_STEERINGMATRIX_BUF] =
            (*inBufDesc)[BEAM_FORMING_TI_BUFDESC_IN_STEERINGMATRIX_BUF]->bufferId ;

    outArgs->inFreeBufIDs[BEAM_FORMING_TI_BUFDESC_IN_TOTAL] = 0 ;

    outArgs->outFreeBufIDs[BEAM_FORMING_TI_BUFDESC_OUT_BUFFER] =
                (*outBufDesc)[BEAM_FORMING_TI_BUFDESC_OUT_BUFFER]->bufferId ;

    (*outBufDesc)[BEAM_FORMING_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].accessMask =
            IVISION_ACCESSMODE_HWA;

    return status;
}


/*--------------------------------------------------------------------------*/
/* This is the function to do activation of algorithm. All scratch memory   */
/* are restored in this                                                     */
/* Refer algActivate function for details in ialg.h file                    */
/*--------------------------------------------------------------------------*/
void  BEAM_FORMING_TI_activate(IALG_Handle handle)
{
  BEAM_FORMING_TI_Handle algHandle = (BEAM_FORMING_TI_Handle)(void *)handle;
  uint32_t i;

  /*----------------------------------------------------------------*/
  /* Do Activation only if it is deactivated or just after creation */
  /*----------------------------------------------------------------*/
  if(algHandle->algState == ALG_NOT_ACTIVE)
  {
    for(i= 1U; i < algHandle->numMemRecs; i++)
    {
      if((i == ALG_HANDLE_INT_MEMREC) ||(i == BEAM_FORMING_GRAPH_OBJ_INT_MEMREC))
      {
        EDMA_UTILS_memcpy2D((void *)      algHandle->memRec[i].base,
                            (const void *)algHandle->memRec[i-1U].base,
                            (uint16_t)    algHandle->memRec[i].size,
                            (uint16_t)1,
                            (int16_t) 0,
                            (int16_t) 0);
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
void  BEAM_FORMING_TI_deactivate(IALG_Handle handle)
{
  BEAM_FORMING_TI_Handle algHandle = (BEAM_FORMING_TI_Handle)(void *)handle;
  uint32_t i;

  /*----------------------------------------------------------------*/
  /* Do Activation only if it is deactivated or just after creation */
  /*----------------------------------------------------------------*/
  if(algHandle->algState == ALG_ACTIVE)
  {
    for(i= 1U; i < algHandle->numMemRecs; i++)
    {
      if((i == ALG_HANDLE_INT_MEMREC) ||(i == BEAM_FORMING_GRAPH_OBJ_INT_MEMREC))
      {
        EDMA_UTILS_memcpy2D((void *)      algHandle->memRec[i-1U].base,
                            (const void *)algHandle->memRec[i].base,
                            (uint16_t)    algHandle->memRec[i].size,
                            (uint16_t)1,
                            (int16_t) 0,
                            (int16_t) 0);
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
int32_t BEAM_FORMING_TI_free(IALG_Handle handle, IALG_MemRec memRec[])
{
  BEAM_FORMING_TI_Handle algHandle = (BEAM_FORMING_TI_Handle)(void *)handle;

  memcpy(memRec, algHandle->memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

  return (IALG_EOK);
}

