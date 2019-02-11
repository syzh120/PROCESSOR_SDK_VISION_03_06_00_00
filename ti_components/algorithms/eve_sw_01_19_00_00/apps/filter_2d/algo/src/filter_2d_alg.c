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
 *  @file       filter_2d_alg.c
 *
 *  @brief       This file defines the XDAIS/iVISION functions for 2d filter applet
 *  @version     0.0 (Jan 2014) : Base version.
 */

/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/*#pragma RESET_MISRA ("required")*/

#include "filter_2d_alg_int.h"
#include "edma_utils_memcpy.h"
#include "evestarterware.h"
#include "vcop_contrast_stretching_kernel.h"



/**
 * IVISION interface of the algorithm
 */
const IVISION_Fxns FILTER_2D_TI_VISION_FXNS =
{
        {
                &FILTER_2D_TI_activate, /* module ID */
                &FILTER_2D_TI_activate,    /* activate */
                &FILTER_2D_TI_alloc,       /* algAlloc */
                NULL,                          /* control (not suported) */
                &FILTER_2D_TI_deactivate,  /* deactivate */
                &FILTER_2D_TI_free,        /* free */
                &FILTER_2D_TI_init,        /* init */
                NULL,                          /* moved (not suported) */
                &FILTER_2D_TI_numAlloc     /* algNumAlloc  */
        },
        &FILTER_2D_TI_process,
        &FILTER_2D_TI_control
};


/**
 * IRES interface of the algorithm
 */
const IRES_Fxns FILTER_2D_TI_IRES = {
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
int32_t FILTER_2D_TI_numAlloc(void)
{
    return NUM_MEMRECS;
}

/*---------------------------------------------------------------*/
/* Function to supply memory requirement to user                 */
/* refer algAlloc function for details in XADIS (ialg.h file)    */
/*---------------------------------------------------------------*/
int32_t FILTER_2D_TI_alloc(const IALG_Params *params,
        IALG_Fxns **parentFxns,
        IALG_MemRec memRec[])
{
    int32_t status = IALG_EOK;
    BAM_GraphMemReq graphMemReqFilter2D;
    /*---------------------------------------------------------*/
    /* Request BAM public function about memories assosiated   */
    /* to graph creation                                       */
    /*---------------------------------------------------------*/
    FILTER_2D_TI_getGraphMemReq(&graphMemReqFilter2D);

    /*-----------------------------------------------------------------------------*/
    /*  For memory record ALG_HANDLE_INT_MEMREC and FAST9_GRAPH_OBJ_INT_MEMREC,          */
    /*  which are scratch buffers in BAM_MEMSPACE_DMEM, they must be preceded      */
    /*  by a persistent memory record in IALG_EXTERNAL of the same size.           */
    /*  This persistent record will be used to backup the following scratch        */
    /*  memory record during context saving when FILTER_2D_TI_deactivate */
    /*  is called. Likewise when FILTER_2D_TI_activate it called,        */
    /*  the content of the persistent memory record is copied back to the          */
    /*  scratch memory record in BAM_MEMSPACE_DMEM                                 */
    /*-----------------------------------------------------------------------------*/
    memRec[ALG_HANDLE_MEMREC].size          = sizeof(FILTER_2D_TI_Obj);
    memRec[ALG_HANDLE_MEMREC].space         = (IALG_MemSpace)IALG_EXTERNAL;
    memRec[ALG_HANDLE_MEMREC].attrs         = IALG_PERSIST;
    memRec[ALG_HANDLE_MEMREC].alignment     = 4;

    memRec[ALG_HANDLE_INT_MEMREC].size      = sizeof(FILTER_2D_TI_Obj);
    memRec[ALG_HANDLE_INT_MEMREC].space     = (IALG_MemSpace)IALG_DARAM0;
    memRec[ALG_HANDLE_INT_MEMREC].attrs     = IALG_SCRATCH;
    memRec[ALG_HANDLE_INT_MEMREC].alignment = 4;

    /*-------------------------------------------------------------------------*/
    /* Below 5 memory records are used to store data related to the BAM graph: */
    /* 1. FILTER_2D_GRAPH_OBJ_MEMREC     - To hold graph object in external memory       */
    /* 2. FILTER_2D_OBJ_INT_MEMREC - To hold the graph object in internal memory   */
    /* GRAPH OBJECT has 2 instances - internal and external memory - it is to  */
    /* speed up the processing - Main processing will work on internal memory  */
    /* instance and before any one else needing internal memory, deacitavte    */
    /* has to be performed by caller to make sure the data is backed up to ext */
    /* memory                                                                  */
    /*                                                                         */
    /* 3. FILTER_2D_SCRATCH_MEMREC -                                               */
    /*  It is used as scratch memory during graph create time                  */
    /*  Scratch mem is currently placed in external memory.                    */
    /*  For faster graph creation time, you can place it in internal memory    */
    /*                                                                         */
    /* 4. FILTER_2D_CONTEXT_MEMREC                                                 */
    /*  It is used to backup into external memory the graph's                  */
    /*  nodes internal memory records that are persistent.                     */
    /*                                                                         */
    /* 5. FILTER_2D_ARGS_MEMREC  -                                                 */
    /*   It is used keep kernels arguments during graph create time            */
    /*-------------------------------------------------------------------------*/

    memRec[FILTER_2D_GRAPH_OBJ_MEMREC].size  = graphMemReqFilter2D.graphObjSize;
    memRec[FILTER_2D_GRAPH_OBJ_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[FILTER_2D_GRAPH_OBJ_MEMREC].attrs = IALG_PERSIST;
    memRec[FILTER_2D_GRAPH_OBJ_MEMREC].alignment      = 4;

    /*
    FILTER_2D_GRAPH_OBJ_INT_MEMREC is allocated in DMEM and is used when the backup is
    restored from external memory to faster internal memory when activate is called.
     */
    memRec[FILTER_2D_GRAPH_OBJ_INT_MEMREC].size  = graphMemReqFilter2D.graphObjSize;
    memRec[FILTER_2D_GRAPH_OBJ_INT_MEMREC].space =(IALG_MemSpace) IALG_DARAM0;
    memRec[FILTER_2D_GRAPH_OBJ_INT_MEMREC].attrs = IALG_SCRATCH;
    memRec[FILTER_2D_GRAPH_OBJ_INT_MEMREC].alignment  = 4;

    memRec[FILTER_2D_GRAPH_SCRATCH_MEMREC].size  = graphMemReqFilter2D.graphScratchSize;
    memRec[FILTER_2D_GRAPH_SCRATCH_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[FILTER_2D_GRAPH_SCRATCH_MEMREC].attrs = IALG_SCRATCH;
    memRec[FILTER_2D_GRAPH_SCRATCH_MEMREC].alignment  = 4;

    memRec[FILTER_2D_GRAPH_CONTEXT_MEMREC].size  = graphMemReqFilter2D.graphcontextSize;
    memRec[FILTER_2D_GRAPH_CONTEXT_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[FILTER_2D_GRAPH_CONTEXT_MEMREC].attrs = IALG_SCRATCH;
    memRec[FILTER_2D_GRAPH_CONTEXT_MEMREC].alignment  = 4;

    memRec[FILTER_2D_GRAPH_ARGS_MEMREC].size  = graphMemReqFilter2D.graphArgsSize;
    memRec[FILTER_2D_GRAPH_ARGS_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[FILTER_2D_GRAPH_ARGS_MEMREC].attrs = IALG_SCRATCH;
    memRec[FILTER_2D_GRAPH_ARGS_MEMREC].alignment     = 4;

    return (status);
}

/*-----------------------------------------------------------------------*/
/* Function to accept memory pointers from user and initialize algorithm */
/* Refer algInit function for details in XADIS (ialg.h file)             */
/*-----------------------------------------------------------------------*/
int32_t FILTER_2D_TI_init(IALG_Handle handle,
        const IALG_MemRec memRec[],
        IALG_Handle parent,
        const IALG_Params * params)
{
    int32_t status = IALG_EOK;
    int32_t bamStatus;

    FILTER_2D_TI_graphCreateParams    filter2dCreateParams;

    FILTER_2D_TI_Handle algHandle =
            (FILTER_2D_TI_Handle)(void *)memRec[ALG_HANDLE_MEMREC].base;

    uint8_t (*filterCoef)[BAM_YUV420_FIR2D_MAX_COEFF_SIZE];

    algHandle->filter2DGraphMem.graphObj      = memRec[FILTER_2D_GRAPH_OBJ_MEMREC].base;
    algHandle->filter2DGraphMem.graphScratch  = memRec[FILTER_2D_GRAPH_SCRATCH_MEMREC].base;
    algHandle->filter2DGraphMem.graphcontext  = memRec[FILTER_2D_GRAPH_CONTEXT_MEMREC].base;
    algHandle->filter2DGraphMem.graphArgs     = memRec[FILTER_2D_GRAPH_ARGS_MEMREC].base;



    algHandle->createParams = *((const FILTER_2D_CreateParams*)(const void *)params);
    /* If user wants to bypass filter then overwrite the coefficients and filterCoeffWidth and height
    for filter of 1 */
    if ( algHandle->createParams.enableFilter == 0)
    {
      algHandle->createParams.filterCoefWidth  = 1;
      algHandle->createParams.filterCoefHeight = 1;
      algHandle->createParams.filterCoef       = algHandle->byPassFilterCoeff;
      filterCoef = (uint8_t (*)[BAM_YUV420_FIR2D_MAX_COEFF_SIZE])(void *)algHandle->createParams.filterCoef;
      (*filterCoef)[0] = 1U;
      (*filterCoef)[1] = 1U;
    }

    filter2dCreateParams.ifilterCreateParams = &algHandle->createParams;


    if ( algHandle->createParams.imageFormat >= FILTER_2D_TI_IMAGE_FORMAT_TOTAL )
    {
      status = FILTER_2D_TI_ERRORTYPE_IMAGEFORMAT_UNSUPPORTED;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }
    bamStatus = FILTER_2D_TI_graphCreate(&(algHandle->filter2DGraphMem),
            &filter2dCreateParams);

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
    algHandle->ivision = &FILTER_2D_TI_VISION_FXNS;

    /*-----------------------------------------------------------------------*/
    /* State to indicate that internal context of algorithm is not active    */
    /*-----------------------------------------------------------------------*/
    algHandle->algState = ALG_NOT_ACTIVE;

    Exit:
    return (status);
}

/*-----------------------------------------------------------------------*/
/* Function to accept any run time updates with recreation of object     */
/* Refer algControl function for details in ivision.h file               */
/* Not implemented for this function                                     */
/*-----------------------------------------------------------------------*/
int32_t FILTER_2D_TI_control(IVISION_Handle handle,
        IALG_Cmd cmd,
        const IALG_Params *inParams,
        IALG_Params *outParams)
{
  int32_t status = IALG_EOK;
  const IVISION_InBufs *inBufs = (const IVISION_InBufs*)(const void *)inParams;
  FILTER_2D_EffectiveDims * effDims = ( FILTER_2D_EffectiveDims*) (void *)outParams;
  uint16_t imgWidth;
  uint16_t imgHeight;
  IVISION_BufDesc    *(*inBufDesc)[FILTER_2D_TI_BUFDESC_IN_TOTAL];

  inBufDesc  = (IVISION_BufDesc *(*)[FILTER_2D_TI_BUFDESC_IN_TOTAL])(void *)inBufs->bufDesc;

  if(cmd == FILTER_2D_CONTROL_GET_EFFECTIVE_OUTPUT_DIM)
  {
    imgWidth = (*inBufDesc)[FILTER_2D_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.width;
    imgHeight = (*inBufDesc)[FILTER_2D_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.height;

    FILTER_2D_TI_getEffectiveDimensionsUsed(imgWidth, imgHeight, effDims);

  }
  else
  {
    status = IALG_EFAIL;
  }

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
int32_t FILTER_2D_TI_process(IVISION_Handle handle,
        IVISION_InBufs *inBufs,
        IVISION_OutBufs *outBufs,
        IVISION_InArgs *inArgs,
        IVISION_OutArgs *outArgs)
{
/* RESET_MISRA("16.7")  -> Reset rule 16.7     */

    FILTER_2D_TI_Handle algHandle = (FILTER_2D_TI_Handle)(void *)(handle);
    FILTER_2D_TI_Handle intAlgHandle;
    int32_t status            = IALG_EOK;
    int32_t bamStatus;
    IBAMALG_InArgs          bamInArgs;
    IBAMALG_OutArgs         bamOutArgs;
    uint8_t                 sinkNodeId;
    FILTER_2D_OutArgs       *filter2DoutArgs;
    FILTER_2D_InArgs        *filter2DinArgs;
    uint32_t                *histgram8CopyBuf;
    int32_t i;
    uint32_t minThrIndexVal;
    uint32_t maxThrIndexVal;
    uint8_t  minVal;
    uint8_t  maxVal;
    uint32_t minPercentileThreshold;
    uint32_t maxPercentileThreshold;
    uint32_t totalPixels;
    uint32_t * transposeBuff = NULL;
    uint32_t  (*histogram)[256];
    uint16_t * paramBlock = NULL;
    uint16_t effectiveImageWidth;
    uint16_t effectiveImageHeight;
    uint8_t  tempNumNodeOffset = 0;
    uint8_t  numPlanesExpected;

    IVISION_BufDesc    *(*inBufDesc)[FILTER_2D_TI_BUFDESC_IN_TOTAL];
    IVISION_BufDesc    *(*outBufDesc)[FILTER_2D_TI_BUFDESC_OUT_TOTAL];


    inBufDesc  = (IVISION_BufDesc *(*)[FILTER_2D_TI_BUFDESC_IN_TOTAL])(void *)inBufs->bufDesc;
    outBufDesc = (IVISION_BufDesc *(*)[FILTER_2D_TI_BUFDESC_OUT_TOTAL])(void *)outBufs->bufDesc;

    if ( inBufs->numBufs < 1U )
    {
        status = IVISION_ERRORTYPE_NUM_INBUF_LESS;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    /*-----------------------------------------------------------------------*/
    /* Activate the algorithm to make sure that now onwards internal memory  */
    /* handle can be utilized                                                */
    /*-----------------------------------------------------------------------*/
    FILTER_2D_TI_activate((IALG_Handle)(void *)handle);

    intAlgHandle                      = (FILTER_2D_TI_Handle)(void *)algHandle->memRec[ALG_HANDLE_INT_MEMREC].base;
    intAlgHandle->filter2DGraphMem.graphObj      =
            intAlgHandle->memRec[FILTER_2D_GRAPH_OBJ_INT_MEMREC].base;

    bamInArgs.size        = sizeof(IBAMALG_InArgs);
    bamInArgs.sliceIndex  = 0;

    bamOutArgs.size       = sizeof(IBAMALG_OutArgs);

    /* Default is gray scale */
    numPlanesExpected = 1U;

    if ( intAlgHandle->createParams.imageFormat == FILTER_2D_TI_IMAGE_FORMAT_YUV420)
    {
      numPlanesExpected = 2U;
    }

    if ( (*inBufDesc)[FILTER_2D_TI_BUFDESC_IN_IMAGEBUFFER]->numPlanes < numPlanesExpected )
    {
        status = FILTER_2D_TI_ERRORTYPE_IMAGEFORMAT_MISMATCH;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }


    if ( intAlgHandle->createParams.imageFormat == FILTER_2D_TI_IMAGE_FORMAT_GRAYSCALE)
    {
      tempNumNodeOffset = 1U;
    }

    /* The position of SINK node in the graph will depened on the image format as gray scale image will have one lessor node
    tempNumNodeOffset variables is used to find the correct SINK node location in graph. Total number of nodes in graph
    when contrast stretching and YUV420 format is used is 5 and if contrast stretching is disabled then its only 3. Hence reduce one
    more if image format is only gray scale.*/
    if ( intAlgHandle->createParams.enableContrastStretching)
    {
      sinkNodeId = (uint8_t)5U - tempNumNodeOffset;
    }
    else
    {
      sinkNodeId = (uint8_t)3U - tempNumNodeOffset;
    }

    bamStatus = FILTER_2D_TI_dmaControl(&(intAlgHandle->filter2DGraphMem),
                                   intAlgHandle->createParams.filterCoefWidth,
                                   intAlgHandle->createParams.filterCoefHeight,
                                   sinkNodeId,
                                   (*inBufDesc)[FILTER_2D_TI_BUFDESC_IN_IMAGEBUFFER],
                                   (*outBufDesc)[FILTER_2D_TI_BUFDESC_OUT_IMAGE_BUFFER],
                                   &effectiveImageWidth,
                                   &effectiveImageHeight);

    if (bamStatus != BAM_S_SUCCESS) {
      status = IALG_EFAIL;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    if ( intAlgHandle->createParams.enableContrastStretching)
    {

      bamStatus = FILTER_2D_TI_setHistogramImageDim(&(intAlgHandle->filter2DGraphMem),
            (*inBufDesc)[FILTER_2D_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.width,
            (*inBufDesc)[FILTER_2D_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.height);

      if (bamStatus != BAM_S_SUCCESS) {
          status = IALG_EFAIL;
          /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
          /* GOTO is used at error check to jump to end of function, to exit.   */
          goto Exit;
          /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }

      if (inArgs->size == sizeof (FILTER_2D_InArgs))
      {
        uint32_t scaleFactorQ16;

        filter2DinArgs = (FILTER_2D_InArgs *)(void *)inArgs;

        minVal = filter2DinArgs->minVal;
        maxVal = filter2DinArgs->maxVal;

        if ( (maxVal - minVal) != 0 )
        {
          scaleFactorQ16 = (uint32_t)(( (uint32_t)1U << 16U) / (( (uint32_t)maxVal - (uint32_t)minVal)));
        }
        else
        {
          scaleFactorQ16 = (uint32_t)((uint32_t)1U << 16U);
        }

        bamStatus = FILTER_2D_TI_setContrastStretchingArgs(&(intAlgHandle->filter2DGraphMem),
                          (uint32_t)minVal,
                          scaleFactorQ16);

        if (bamStatus != BAM_S_SUCCESS) {
            status = IALG_EFAIL;
            /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
            /* GOTO is used at error check to jump to end of function, to exit.   */
            goto Exit;
            /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
        }
      }
    }

    bamStatus = FILTER_2D_TI_execute(&(intAlgHandle->filter2DGraphMem), &bamInArgs,&bamOutArgs);


    if (bamStatus != BAM_S_SUCCESS)
    {
        status = IALG_EFAIL;
        PRINTF("FILTER_2D_TI_execute() returned error\n");
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    if ( intAlgHandle->createParams.enableContrastStretching)
    {

      histgram8CopyBuf =     FILTER_2D_TI_getHist8CopyBuf(&(intAlgHandle->filter2DGraphMem));

      if (histgram8CopyBuf == NULL)
      {
          status = IALG_EFAIL;
          PRINTF("FILTER_2D_TI_getHist8CopyBuf() returned error\n");
          /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
          /* GOTO is used at error check to jump to end of function, to exit.   */
          goto Exit;
          /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }

      /* Sum all 8 copy histogram to get final histrogram */
#if (!VCOP_HOST_EMULATION)
      /* At this point of time histgram8CopyBuf is in WBUF, and IBUFLA IBUFHA are fully available
      for use. Hence directly use them */
      transposeBuff = (uint32_t *)0x40050000;/*IBUFLA*/
      histogram     = (uint32_t (*)[256])0x40054000;/*IBUFHA*/
      paramBlock    = (uint16_t *)0x40053C00;/*IBUFLA*/
      VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_VCOP, IBUFLB_VCOP, IBUFHA_SYST, IBUFLA_SYST);
      vcop_histogram_8c_word_sum_init(histgram8CopyBuf, transposeBuff, (*histogram),paramBlock);
      VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_VCOP, IBUFLA_VCOP);
      vcop_histogram_8c_word_sum_vloops(paramBlock);
      _vcop_vloop_done();
      VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_VCOP, IBUFLB_VCOP, IBUFHA_SYST, IBUFLA_SYST);
#else
      transposeBuff =  (uint32_t *)malloc(256U * sizeof(uint32_t)* 9U);
      histogram     =  (uint32_t (*)[256])malloc(256U * 4U);
      vcop_histogram_8c_word_sum(histgram8CopyBuf, transposeBuff, (*histogram));
#endif


      /* Find Cumulative histogram */
      for ( i = 1; i < 256; i++)
      {
        (*histogram)[i] = (*histogram)[i] + (*histogram)[i-1];
      }

      minPercentileThreshold = intAlgHandle->createParams.minPercentileThreshold;
      maxPercentileThreshold = intAlgHandle->createParams.maxPercentileThreshold;

      /* Now find min and max histogram */
      totalPixels = (*histogram)[255];
      minThrIndexVal = (*histogram)[0];
      minVal = 0;
      for(i = 0; i < 256 ; i++)
      {
        minThrIndexVal = (*histogram)[i];
        minVal = (uint8_t)i;
        if( minThrIndexVal > ((totalPixels * minPercentileThreshold) / 100U))
        {
          break;
        }
      }
      maxThrIndexVal = (*histogram)[255];
      maxVal = 255U;
      for( i = 255 ; i >= 0; i--)
      {
        maxThrIndexVal = (*histogram)[i];
        maxVal = (uint8_t)i;
        if(maxThrIndexVal< ((totalPixels * maxPercentileThreshold) / 100U))
        {
          break;
        }
      }

      minVal = ( minVal > 64U  ) ? 64U  : minVal;
      maxVal = ( maxVal < 128U ) ? 128U : maxVal;
#if VCOP_HOST_EMULATION
      if ( histogram)
      {
        free( histogram);
      }

      if ( transposeBuff)
      {
        free (transposeBuff);
      }
#endif
    }

    if (outArgs->size == sizeof (FILTER_2D_OutArgs))
    {
      filter2DoutArgs = (FILTER_2D_OutArgs *)(void *)outArgs;
      if ( intAlgHandle->createParams.enableContrastStretching)
      {
        filter2DoutArgs->minVal = minVal;
        filter2DoutArgs->maxVal = maxVal;
      }
      else
      {
        filter2DoutArgs->minVal = 0;
        filter2DoutArgs->maxVal = 255U;
      }

    }
Exit:
    /*----------------------------------*/
    /* Free the input and output buffer */
    /*----------------------------------*/
    outArgs->inFreeBufIDs[FILTER_2D_TI_BUFDESC_IN_IMAGEBUFFER] =
            (*inBufDesc)[FILTER_2D_TI_BUFDESC_IN_IMAGEBUFFER]->bufferId ;

    outArgs->inFreeBufIDs[FILTER_2D_TI_BUFDESC_IN_TOTAL] = 0 ;

    outArgs->outFreeBufIDs[FILTER_2D_TI_BUFDESC_OUT_IMAGE_BUFFER] =
            (*outBufDesc)[FILTER_2D_TI_BUFDESC_OUT_IMAGE_BUFFER]->bufferId ;

    outArgs->outFreeBufIDs[FILTER_2D_TI_BUFDESC_OUT_TOTAL] = 0 ;

    (*outBufDesc)[FILTER_2D_TI_BUFDESC_OUT_IMAGE_BUFFER]->bufPlanes[0].accessMask =
            IVISION_ACCESSMODE_HWA;

    return status;
}

/*--------------------------------------------------------------------------*/
/* This is the function to do activation of algorithm. All scratch memory   */
/* are restored in this                                                     */
/* Refer algActivate function for details in ialg.h file                    */
/*--------------------------------------------------------------------------*/
void  FILTER_2D_TI_activate(IALG_Handle handle)
{
    FILTER_2D_TI_Handle algHandle = (FILTER_2D_TI_Handle)(void *)(handle);
    uint32_t i;

    /*----------------------------------------------------------------*/
    /* Do Activation only if it is deactivated or just after creation */
    /*----------------------------------------------------------------*/
    if(algHandle->algState == ALG_NOT_ACTIVE)
    {
        for(i= 1U; i < algHandle->numMemRecs; i++)
        {
            if((i == ALG_HANDLE_INT_MEMREC) ||(i == FILTER_2D_GRAPH_OBJ_INT_MEMREC))
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
void  FILTER_2D_TI_deactivate(IALG_Handle handle)
{
    FILTER_2D_TI_Handle algHandle = (FILTER_2D_TI_Handle)(void *)(handle);
    uint32_t i;
    /*----------------------------------------------------------------*/
    /* Do De-activation only if it is deactivated or just after creation */
    /*----------------------------------------------------------------*/
    if(algHandle->algState == ALG_ACTIVE)
    {
        for(i= 1U; i < algHandle->numMemRecs; i++)
        {
            if((i == ALG_HANDLE_INT_MEMREC) ||(i == FILTER_2D_GRAPH_OBJ_INT_MEMREC))
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
int32_t FILTER_2D_TI_free(IALG_Handle handle, IALG_MemRec memRec[])
{
    int32_t status            = IALG_EOK;
    FILTER_2D_TI_Handle algHandle = (FILTER_2D_TI_Handle)(void *)(handle);

    memcpy(memRec, algHandle->memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

    return status;
}
