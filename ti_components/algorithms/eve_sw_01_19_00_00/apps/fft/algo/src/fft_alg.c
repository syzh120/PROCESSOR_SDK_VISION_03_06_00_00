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
*  @file       fft_alg.c
*
*  @brief       This file defines the XDAIS/iVISION functions for hough for lines applet
*  @version     0.0 (Mar 2016) : Base version.
*/

/* #pragma CHECK_MISRA ("none") */
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/* #pragma RESET_MISRA ("required") */

#include "fft_alg_int.h"
#include "fft_graph_int.h"

#include "edma_utils_memcpy.h"
#include "evestarterware.h"
#include "edma_utils.h"
#include "vcop_fft_npt_16ix16o_gen_twiddleFactor.h"
#include "vcop_fft_utils.h"

/**
* IVISION interface of the algorithm
*/
const IVISION_Fxns FFT_TI_VISION_FXNS =
{
  {
      &FFT_TI_activate, /* module ID */
      &FFT_TI_activate,    /* activate */
      &FFT_TI_alloc,       /* algAlloc */
      NULL,                      /* control (not suported) */
      &FFT_TI_deactivate,  /* deactivate */
      &FFT_TI_free,        /* free */
      &FFT_TI_init,        /* init */
      NULL,                      /* moved (not suported) */
      &FFT_TI_numAlloc     /* algNumAlloc  */
  },
  &FFT_TI_process,
  &FFT_TI_control
};


/**
* IRES interface of the algorithm
*/
const IRES_Fxns FFT_TI_IRES = {
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

#define FFT_IMGBUFLA_ADDRESS   ((void*) 0x40050000)

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define CLIP(x,y) ((( (x) / (y)) * (y))
#define ALIGN(x,y)         (((x) + (y) - 1U)/(y))*(y)
#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define MIN(A, B) (((A) < (B)) ? (A) : (B))

/* RESET_MISRA("19.7")  -> Reset rule 19.7  */




/**
* Internally used functions
*/
static uint32_t getBufferSplit(uint16_t numAntennas, uint16_t numPoints, uint16_t * numPointPerSplit);

static uint32_t getBufferSplit(uint16_t numAntennas, uint16_t numPoints, uint16_t * numPointPerSplit)
{
  uint32_t pointPerSplit;
  uint32_t numSplitRequired;

  numSplitRequired = 1U;

  do
  {
    pointPerSplit = ALIGN( (numPoints/numSplitRequired) , VCOP_SIMD_WIDTH);
    numSplitRequired++;

  }while ( (pointPerSplit * sizeof(int32_t) * numAntennas) >  FFT_TI_MAX_PITCH_SUPPORTED );

  numSplitRequired =     numSplitRequired - 1U;

  *numPointPerSplit = (uint16_t)pointPerSplit;
  return numSplitRequired;

}

#define FFT_TI_MIN_NUM_LINES  (4U)
#define FFT_TI_MAX_BLOCK_SIZE (16384U)

static uint32_t findNumLinesPerBlock(uint16_t numPoints, uint8_t fftDirection, uint8_t enable32bitsPrecision);

static uint32_t findNumLinesPerBlock(uint16_t numPoints, uint8_t fftDirection, uint8_t enable32bitsPrecision)
{
  uint32_t blockSize;
  uint32_t numLinesPerBlock;
  uint32_t numLineIncrement;
  uint32_t extraColForTranspose;
  uint32_t elmSize;

  if ( fftDirection == FFT_TI_DIRECTION_HORIZONTAL)
  {
    numLineIncrement = FFT_TI_MIN_NUM_LINES;
    extraColForTranspose = 0;
  }
  else if ( fftDirection == FFT_TI_DIRECTION_VERTICAL)
  {
    numLineIncrement = FFT_TI_MIN_NUM_LINES * 2U;
    extraColForTranspose = 1U;
  }
  else
  {
    numLinesPerBlock = 0;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */

  }

  numLinesPerBlock = numLineIncrement;

  if (enable32bitsPrecision== 1u)
  {
    elmSize= 2u*sizeof(int32_t);
    extraColForTranspose= 0;
  }
  else
  {
    elmSize= 2u*sizeof(int16_t);
  }
  blockSize = (numPoints + extraColForTranspose) * numLinesPerBlock * elmSize;

  /* We want to find block dimension such that number of lines is mulitple of 8 ( for vertical direction). Also
  number of lines should be power of 2 so that output dimension is multiple of block
  dimension */
  while ( blockSize <= FFT_TI_MAX_BLOCK_SIZE)
  {
    numLinesPerBlock = 2U * (numLinesPerBlock);
    blockSize = (numPoints + extraColForTranspose) * numLinesPerBlock * elmSize;
  }
  numLinesPerBlock = numLinesPerBlock/2U;

  /* For 64 point FFT output cannot be of same size as input as output after FFT kernel contains
  holes of 4 bytes between them. To avoid this for 64 point FFT we directly using 48 lines to process */
  if ( numPoints == 64U )
  {
    if ( numLinesPerBlock > 32U)
    {
      numLinesPerBlock = 32U;
    }
    if (enable32bitsPrecision)
    {
      numLinesPerBlock >>=1;
    }
  }

  if ( (enable32bitsPrecision== 0) && (numPoints == 512U) )
  {
    /* For 512 point FFT we need more than 16KB of memory for transpose. So we will use WBUF for it
    and hence set lines per block as 8 */
    numLinesPerBlock = 8U;
  }

Exit:
  return numLinesPerBlock;


}

/**
* Other exposed functions
*/
int32_t FFT_TI_numAlloc(void)
{
  return NUM_MEMRECS;
}

/*---------------------------------------------------------------*/
/* Function to supply memory requirement to user                 */
/* refer algAlloc function for details in XADIS (ialg.h file)    */
/*---------------------------------------------------------------*/
int32_t FFT_TI_alloc(const IALG_Params *params,
                                       IALG_Fxns **parentFxns,
                                       IALG_MemRec       memRec[])
{
    int32_t status = IALG_EOK;
    BAM_GraphMemReq graphMemReqGraph;
    /*---------------------------------------------------------*/
    /* Request BAM public function about memories assosiated   */
    /* to graph creation                                       */
    /*---------------------------------------------------------*/
    FFT_TI_getGraphMemReq(&graphMemReqGraph);



    /*-----------------------------------------------------------------------------*/
    /*  For memory record ALG_HANDLE_INT_MEMREC and FAST9_GRAPH_OBJ_INT_MEMREC,          */
    /*  which are scratch buffers in BAM_MEMSPACE_DMEM, they must be preceded      */
    /*  by a persistent memory record in IALG_EXTERNAL of the same size.           */
    /*  This persistent record will be used to backup the following scratch        */
    /*  memory record during context saving when FFT_TI_deactivate */
    /*  is called. Likewise when FFT_TI_activate it called,        */
    /*  the content of the persistent memory record is copied back to the          */
    /*  scratch memory record in BAM_MEMSPACE_DMEM                                 */
    /*-----------------------------------------------------------------------------*/
    memRec[ALG_HANDLE_MEMREC].size          = sizeof(FFT_TI_Obj);
    memRec[ALG_HANDLE_MEMREC].space         = (IALG_MemSpace)IALG_EXTERNAL;
    memRec[ALG_HANDLE_MEMREC].attrs         = IALG_PERSIST;
    memRec[ALG_HANDLE_MEMREC].alignment     = 4U;

    memRec[ALG_HANDLE_INT_MEMREC].size      = sizeof(FFT_TI_Obj);
    memRec[ALG_HANDLE_INT_MEMREC].space     = (IALG_MemSpace)IALG_DARAM0;
    memRec[ALG_HANDLE_INT_MEMREC].attrs     = IALG_SCRATCH;
    memRec[ALG_HANDLE_INT_MEMREC].alignment = 4U;

    /*-------------------------------------------------------------------------*/
    /* Below 5 memory records are used to store data related to the BAM graph: */
    /* 1. FFT_GRAPH_OBJ_MEMREC     - To hold graph object in external memory       */
    /* 2. FFT_OBJ_INT_MEMREC - To hold the graph object in internal memory   */
    /* GRAPH OBJECT has 2 instances - internal and external memory - it is to  */
    /* speed up the processing - Main processing will work on internal memory  */
    /* instance and before any one else needing internal memory, deacitavte    */
    /* has to be performed by caller to make sure the data is backed up to ext */
    /* memory                                                                  */
    /*                                                                         */
    /* 3. FFT_SCRATCH_MEMREC -                                               */
    /*  It is used as scratch memory during graph create time                  */
    /*  Scratch mem is currently placed in external memory.                    */
    /*  For faster graph creation time, you can place it in internal memory    */
    /*                                                                         */
    /* 4. FFT_CONTEXT_MEMREC                                                 */
    /*  It is used to backup into external memory the graph's                  */
    /*  nodes internal memory records that are persistent.                     */
    /*                                                                         */
    /* 5. FFT_ARGS_MEMREC  -                                                 */
    /*   It is used keep kernels arguments during graph create time            */
    /*-------------------------------------------------------------------------*/

    memRec[FFT_GRAPH_OBJ_MEMREC].size  = graphMemReqGraph.graphObjSize;
    memRec[FFT_GRAPH_OBJ_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[FFT_GRAPH_OBJ_MEMREC].attrs = IALG_PERSIST;
    memRec[FFT_GRAPH_OBJ_MEMREC].alignment      = 4U;

    /*
    FFT_GRAPH_OBJ_INT_MEMREC is allocated in DMEM and is used when the backup is
    restored from external memory to faster internal memory when activate is called.
     */
    memRec[FFT_GRAPH_OBJ_INT_MEMREC].size  = graphMemReqGraph.graphObjSize;
    memRec[FFT_GRAPH_OBJ_INT_MEMREC].space =(IALG_MemSpace) IALG_DARAM0;
    memRec[FFT_GRAPH_OBJ_INT_MEMREC].attrs = IALG_SCRATCH;
    memRec[FFT_GRAPH_OBJ_INT_MEMREC].alignment  = 4U;

    memRec[FFT_GRAPH_SCRATCH_MEMREC].size  = graphMemReqGraph.graphScratchSize;
    memRec[FFT_GRAPH_SCRATCH_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[FFT_GRAPH_SCRATCH_MEMREC].attrs = IALG_SCRATCH;
    memRec[FFT_GRAPH_SCRATCH_MEMREC].alignment  = 4U;

    memRec[FFT_GRAPH_CONTEXT_MEMREC].size  = graphMemReqGraph.graphcontextSize;
    memRec[FFT_GRAPH_CONTEXT_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[FFT_GRAPH_CONTEXT_MEMREC].attrs = IALG_SCRATCH;
    memRec[FFT_GRAPH_CONTEXT_MEMREC].alignment  = 4U;

    memRec[FFT_GRAPH_ARGS_MEMREC].size  = graphMemReqGraph.graphArgsSize;
    memRec[FFT_GRAPH_ARGS_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[FFT_GRAPH_ARGS_MEMREC].attrs = IALG_SCRATCH;
    memRec[FFT_GRAPH_ARGS_MEMREC].alignment     = 4U;

    memRec[FFT_ALL_STAGE_TWIDDLE_FACTOR_MEMREC].size  = getSizeTwiddleFactor_128() +
                                                        getSizeTwiddleFactor_512() +
                                                        getSizeTwiddleFactor_256() +
                                                        getSizeTwiddleFactor_1024()+
                                                        getSizeTwiddleFactor_64();

    memRec[FFT_ALL_STAGE_TWIDDLE_FACTOR_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[FFT_ALL_STAGE_TWIDDLE_FACTOR_MEMREC].attrs = IALG_PERSIST;
    memRec[FFT_ALL_STAGE_TWIDDLE_FACTOR_MEMREC].alignment     = 4U;


    return (status);
}


/*-----------------------------------------------------------------------*/
/* Function to accept memory pointers from user and initialize algorithm */
/* Refer algInit function for details in XADIS (ialg.h file)             */
/*-----------------------------------------------------------------------*/
int32_t FFT_TI_init(IALG_Handle        handle,
                                     const IALG_MemRec  memRec[],
                                     IALG_Handle        parent,
                                     const IALG_Params *params)
{
    int32_t status = IALG_EOK;
    int32_t bamStatus;

    FFT_TI_Handle algHandle =
            (FFT_TI_Handle)(void *)memRec[ALG_HANDLE_MEMREC].base;
    const FFT_TI_CreateParams* createParams = (const FFT_TI_CreateParams * )(const void *)params;
    FFT_TI_graphCreateParams     graphCreateParams;

    if ((createParams->outputContainerFormat!= FFT_TI_CONTAINER_FORMAT_16BIT) && (createParams->outputContainerFormat!= FFT_TI_CONTAINER_FORMAT_32BIT)) {
        status = IALG_EFAIL;
       /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
       /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    algHandle->graphMem.graphObj      = memRec[FFT_GRAPH_OBJ_MEMREC].base;
    algHandle->graphMem.graphScratch  = memRec[FFT_GRAPH_SCRATCH_MEMREC].base;
    algHandle->graphMem.graphcontext  = memRec[FFT_GRAPH_CONTEXT_MEMREC].base;
    algHandle->graphMem.graphArgs     = memRec[FFT_GRAPH_ARGS_MEMREC].base;

    algHandle->createParams = *createParams;

    graphCreateParams.iFftCreateParams = createParams;

    bamStatus = FFT_TI_graphCreate(&(algHandle->graphMem),
                                                  &graphCreateParams);

    if ( bamStatus != BAM_S_SUCCESS)
    {
        status = IALG_EFAIL;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
       /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    /* Generate Twiddle factor for all stages */

    algHandle->twiddleFactorBufs[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_1024] = (int8_t *)(void *)memRec[FFT_ALL_STAGE_TWIDDLE_FACTOR_MEMREC].base;
    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH:  Pointer is used in arithmetic or array index expression  */
    /*  Pointer arithmetic is required for performance like auto increment in loop. The harmful side effect of voilating this
      rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    algHandle->twiddleFactorBufs[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_512] =  algHandle->twiddleFactorBufs[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_1024] + getSizeTwiddleFactor_1024();
    algHandle->twiddleFactorBufs[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_256] = algHandle->twiddleFactorBufs[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_512] + getSizeTwiddleFactor_512();
    algHandle->twiddleFactorBufs[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_128] = algHandle->twiddleFactorBufs[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_256] + getSizeTwiddleFactor_256();
    algHandle->twiddleFactorBufs[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_64] = algHandle->twiddleFactorBufs[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_128] + getSizeTwiddleFactor_128();

    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    generateTwiddleFactor_1024((int16_t *)(void *)algHandle->twiddleFactorBufs[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_1024]);
    generateTwiddleFactor_512((int16_t *)(void *)algHandle->twiddleFactorBufs[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_512]);
    generateTwiddleFactor_256((int16_t *)(void *)algHandle->twiddleFactorBufs[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_256]);
    generateTwiddleFactor_128((int16_t *)(void *)algHandle->twiddleFactorBufs[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_128]);
    generateTwiddleFactor_64((int16_t *)(void *)algHandle->twiddleFactorBufs[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_64]);

    algHandle->numMemRecs  = NUM_MEMRECS;
    memcpy(algHandle->memRec,memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);
    algHandle->ivision = &FFT_TI_VISION_FXNS;

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
int32_t FFT_TI_control(IVISION_Handle     handle,
                                          IALG_Cmd           cmd,
                                          const IALG_Params *inParams,
                                          IALG_Params       *outParams)
{
  FFT_TI_Handle algHandle = (FFT_TI_Handle)(void *)(handle);
  int32_t status = IALG_EOK;
  const FFT_TI_InArgs *fftInArgs = (const FFT_TI_InArgs*)(const void *)inParams;
  FFT_TI_BufferDescriptor * outputBufDesc = ( FFT_TI_BufferDescriptor*) (void *)outParams;
  uint16_t numSplitRequired = 1U;
  uint16_t numPointsPerSplit;
  uint16_t numPointsLastBlock;
  uint16_t numLinesPerBlock;
  uint16_t numPointsFFT;
  uint16_t numActualPoints;
  uint16_t numTotalHorzPoints;
  uint16_t chunkIdx;
  uint32_t outputElmtSize;

  outputElmtSize= ((uint32_t)sizeof(int32_t))<<algHandle->createParams.outputContainerFormat;

  if ( algHandle->createParams.fftDirection == FFT_TI_DIRECTION_HORIZONTAL )
  {
    numActualPoints = fftInArgs->bufDescription.numHorzPoints[0];
    numPointsFFT = numActualPoints + fftInArgs->numPointsZeroPadding;
    numPointsPerSplit = numPointsFFT;
    numLinesPerBlock = (uint16_t)findNumLinesPerBlock((uint16_t)numPointsFFT, FFT_TI_DIRECTION_HORIZONTAL, fftInArgs->enable32bitsIntermResults | algHandle->createParams.outputContainerFormat);
    /* If FFT direction is horizontal then find the number of buffers required for the output so that
    all antenna data lies within pitch less than (32kB) */

    numSplitRequired = (uint16_t)getBufferSplit(fftInArgs->bufDescription.numAntennas, numPointsFFT, &numPointsPerSplit);
    numPointsLastBlock = (uint16_t)(numPointsFFT - ((numSplitRequired - 1U) * numPointsPerSplit));

    outputBufDesc->numAntennas   = fftInArgs->bufDescription.numAntennas;
    outputBufDesc->numChunks     = numSplitRequired;
    outputBufDesc->numVertPoints = fftInArgs->bufDescription.numVertPoints;

    for ( chunkIdx = 0; chunkIdx < numSplitRequired; chunkIdx++)
    {
      if ( chunkIdx == (numSplitRequired - 1U))
      {
        outputBufDesc->numHorzPoints[chunkIdx]    = (uint16_t)numPointsLastBlock;
      }
      else
      {
        outputBufDesc->numHorzPoints[chunkIdx]    = (uint16_t)numPointsPerSplit;
      }
      outputBufDesc->pitch[chunkIdx]            = (uint32_t)outputBufDesc->numHorzPoints[chunkIdx] *
                                                              outputBufDesc->numAntennas * outputElmtSize;
      outputBufDesc->offsetBwAntennas[chunkIdx] = (uint32_t)outputBufDesc->numHorzPoints[chunkIdx] * outputElmtSize;
    }
  }
  else if ( algHandle->createParams.fftDirection == FFT_TI_DIRECTION_VERTICAL)
  {
    numActualPoints = fftInArgs->bufDescription.numVertPoints;
    numPointsFFT = numActualPoints + fftInArgs->numPointsZeroPadding;
    numLinesPerBlock = (uint16_t)findNumLinesPerBlock((uint16_t)numPointsFFT, FFT_TI_DIRECTION_VERTICAL, fftInArgs->enable32bitsIntermResults | algHandle->createParams.outputContainerFormat);

    if (algHandle->createParams.outputContainerFormat== FFT_TI_CONTAINER_FORMAT_32BIT) {
        numLinesPerBlock= numLinesPerBlock>>=1;
        }

    numTotalHorzPoints = 0;
    for ( chunkIdx = 0; chunkIdx < fftInArgs->bufDescription.numChunks; chunkIdx++)
    {
      numTotalHorzPoints += fftInArgs->bufDescription.numHorzPoints[chunkIdx];
    }
    outputBufDesc->numAntennas          = fftInArgs->bufDescription.numAntennas;
    outputBufDesc->numChunks            = 1U;
    outputBufDesc->numHorzPoints[0]     = numLinesPerBlock;
    outputBufDesc->offsetBwAntennas[0]  = (uint32_t)numLinesPerBlock * outputElmtSize;
    outputBufDesc->numVertPoints        = (numTotalHorzPoints * numPointsFFT) / numLinesPerBlock;
    outputBufDesc->pitch[0]             = (uint32_t)outputBufDesc->numAntennas * numLinesPerBlock * outputElmtSize;

  }
  else
  {
    status = FFT_TI_ERRORTYPE_FFT_UNSUPPORTED_FFT_DIRECTION;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }
Exit:
  return (status);
}

/*--------------------------------------------------------------------------*/
/* This is the main processing function and should be called for each frame */
/* Refer process function for details in ivision.h file                     */
/*--------------------------------------------------------------------------*/
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter inBufs and outBufs are not used to modify the addressed object but is not declared as a pointer to const */
/* Deviation is allowed because this function is of type IVISION_Fxns : algProcess in order to be ASSIGNED IVISION_Fxns */
int32_t FFT_TI_process(IVISION_Handle   handle,
                                           IVISION_InBufs  *inBufs,
                                           IVISION_OutBufs *outBufs,
                                           IVISION_InArgs  *inArgs,
                                           IVISION_OutArgs *outArgs)
{
  /* RESET_MISRA("16.7")  -> Reset rule 16.7     */

    FFT_TI_Handle algHandle = (FFT_TI_Handle)(void *)(handle);
    FFT_TI_Handle intAlgHandle;
    int32_t status            = IALG_EOK;
    int32_t bamStatus  = BAM_S_SUCCESS;
    IBAMALG_InArgs          bamInArgs;
    IBAMALG_OutArgs         bamOutArgs;
    FFT_TI_InArgs          *fftInArgs;
    FFT_TI_OutArgs          *fftOutArgs;
    uint8_t idx;
    uint8_t  *inputDataPtr;
    uint8_t  *outputDataPtr;
    uint16_t numSplitRequired = 1U;
    uint16_t numPointsPerSplit;
    uint16_t chunkIdx;
    uint16_t numPointsLastBlock;
    uint16_t numLinesPerBlock;
    uint16_t numPointsFFT;
    uint16_t numActualPoints;
    uint16_t numTotalHorzPoints;
    uint16_t numHorzPtPerBlock;
    uint16_t numVertPtPerBlock;
    uint8_t * winCoefBuf = NULL;
    uint8_t *dopplerCorrectionBuf;
    uint16_t numVertPointPreviousChunk;
    uint8_t  enableSignExtension;
    uint8_t * WBUFPtrScaleFactorOut;
    uint32_t numTempPoints;
    uint32_t numStages;
    uint32_t i, outputElmtSize;
    uint32_t dopplerOutputPitch;


    IVISION_BufDesc    *(*inBufDesc)[FFT_TI_BUFDESC_IN_TOTAL];
    IVISION_BufDesc    *(*outBufDesc)[FFT_TI_BUFDESC_OUT_TOTAL];


    inBufDesc  = (IVISION_BufDesc *(*)[FFT_TI_BUFDESC_IN_TOTAL])(void *)inBufs->bufDesc;
    outBufDesc = (IVISION_BufDesc *(*)[FFT_TI_BUFDESC_OUT_TOTAL])(void *)outBufs->bufDesc;

    if (inArgs->size != sizeof(FFT_TI_InArgs))
    {
      status = IALG_EFAIL;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }
    if (outArgs->size != sizeof(FFT_TI_OutArgs))
    {
      status = IALG_EFAIL;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    fftInArgs  = (FFT_TI_InArgs *)(void *)inArgs;
    fftOutArgs  = (FFT_TI_OutArgs *)(void *)outArgs;

    /*-----------------------------------------------------------------------*/
    /* Activate the algorithm to make sure that now onwards internal memory  */
    /* handle can be utilized                                                */
    /*-----------------------------------------------------------------------*/
    FFT_TI_activate((IALG_Handle)(void *)handle);

    intAlgHandle                      = (FFT_TI_Handle)(void *)algHandle->memRec[ALG_HANDLE_INT_MEMREC].base;
    intAlgHandle->graphMem.graphObj      =
            intAlgHandle->memRec[FFT_GRAPH_OBJ_INT_MEMREC].base;


    bamInArgs.size        = sizeof(IBAMALG_InArgs);
    bamInArgs.sliceIndex  = 0;

    bamOutArgs.size       = sizeof(IBAMALG_OutArgs);


    enableSignExtension = (fftInArgs->numValidBits == (uint8_t)16U)? 0 : (uint8_t)1U;

    outputElmtSize= ((uint32_t)sizeof(int32_t))<<intAlgHandle->createParams.outputContainerFormat;

    if ( intAlgHandle->createParams.fftDirection == FFT_TI_DIRECTION_HORIZONTAL)
    {
      uint16_t maxOutBlockWidth;
      uint32_t maxNumHorzBlock;
      numActualPoints = fftInArgs->bufDescription.numHorzPoints[0];

      /* This is the number of points after we do zero padding */
      maxOutBlockWidth = (uint16_t)((numActualPoints + fftInArgs->numPointsZeroPadding) * (uint16_t)outputElmtSize);

      maxNumHorzBlock =  FFT_TI_MAX_PITCH_SUPPORTED/ maxOutBlockWidth;

      if ( (fftInArgs->bufDescription.irregularityFrequency + 1U) > maxNumHorzBlock)
      {
        status = FFT_TI_ERRORTYPE_UNSUPPORTED_IRREGULARITYFREQUENCY;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }

      if ( fftInArgs->enableDopplerCorrection == 1U)
      {
        status = FFT_TI_ERRORTYPE_HORZ_FFT_DOPPLER_CORR_NOTSUPPORTED;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }

      if ( fftInArgs->bufDescription.numChunks != 1U )
      {
        status = FFT_TI_ERRORTYPE_HORZ_FFT_NUM_CHUNK_INVALID;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }
    }
    else if ( intAlgHandle->createParams.fftDirection == FFT_TI_DIRECTION_VERTICAL)
    {
      numActualPoints = fftInArgs->bufDescription.numVertPoints;
      if ( fftInArgs->enableDcOffset == 1U)
      {
        status = FFT_TI_ERRORTYPE_VERT_FFT_DCOFFSET_NOTSUPPORTED;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }
      if ( fftInArgs->enableInterferenceZeroOut == 1U)
      {
        status = FFT_TI_ERRORTYPE_VERT_FFT_INTERFERENCE_ZEROOUT_NOTSUPPORTED;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }
      if ( enableSignExtension == 1U)
      {
        status = FFT_TI_ERRORTYPE_VERT_FFT_SIGN_EXTENSION_NOTSUPPORTED;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }
      for ( chunkIdx = 0; chunkIdx < fftInArgs->bufDescription.numChunks; chunkIdx++ )
      {
        if ( status == IALG_EOK)
        {
          if ( fftInArgs->bufDescription.pitch[chunkIdx] > FFT_TI_MAX_PITCH_SUPPORTED )
          {
            status = FFT_TI_ERRORTYPE_VERT_FFT_UNSUPPORTED_PITCH;
          }

          if ( fftInArgs->bufDescription.offsetBwAntennas[chunkIdx] != ((uint32_t)fftInArgs->bufDescription.numHorzPoints[chunkIdx] * sizeof(int32_t)))
          {
            status = FFT_TI_ERRORTYPE_VERT_FFT_UNSUPPORTED_OFFSET_BW_ANTENNAS;
          }
        }
        if ( status == IALG_EOK)
        {
          if ( fftInArgs->bufDescription.numVertPoints > FFT_TI_NUM_POINTS_512)
          {
            status = FFT_TI_ERRORTYPE_VERT_FFT_UNSUPPORTED_FFT_DIMENSION;
          }
        }

        if ( status == IALG_EOK)
        {
          if ( fftInArgs->bufDescription.irregularityFrequency != 0)
          {
            status = FFT_TI_ERRORTYPE_VERT_FFT_UNSUPPORTED_IRREGULARITYFREQUENCY;
          }
        }
      }

      if ( status != IALG_EOK)
      {
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }
    }
    else
    {
      status = IALG_EFAIL;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    numPointsFFT = numActualPoints + fftInArgs->numPointsZeroPadding;
    numPointsPerSplit = numPointsFFT;

    if ( fftInArgs->numPointsZeroPadding != 0 )
    {
       if ( (fftInArgs->numPointsZeroPadding % VCOP_SIMD_WIDTH) != 0 )
      {
        status = FFT_TI_ERRORTYPE_UNSUPPORTED_ZERO_PADDING;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }

      if ((numPointsFFT < FFT_TI_NUM_POINTS_64) || (numPointsFFT > FFT_TI_NUM_POINTS_1024) )
      {
        status = FFT_TI_ERRORTYPE_UNSUPPORTED_ZERO_PADDING;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }


      if ( (numPointsFFT & (numPointsFFT -1U)) != 0)
      {
        status = FFT_TI_ERRORTYPE_UNSUPPORTED_ZERO_PADDING;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }
    }


    idx = FFT_TI_BUFDESC_IN_LISTBUFFER;

    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are allocated from the user outside this applet hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
    rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    inputDataPtr = (uint8_t *)(*inBufDesc)[idx]->bufPlanes[0].buf;
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    idx = FFT_TI_BUFDESC_OUT_BUFFER;

    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are allocated from the user outside this applet hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
    rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    outputDataPtr = (uint8_t *)(*outBufDesc)[idx]->bufPlanes[0].buf;
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    if (fftInArgs->enableWindowing == 1U )
    {
      winCoefBuf = (uint8_t *)(*inBufDesc)[FFT_TI_BUFDESC_IN_WINDOWING_COEFF_BUF]->bufPlanes[0].buf;
    }
    if ( fftInArgs->enableDopplerCorrection == 1U)
    {
      dopplerCorrectionBuf = (uint8_t *)(void *)(*inBufDesc)[FFT_TI_BUFDESC_IN_DOPPLER_CORRECTION_BUF]->bufPlanes[0].buf;
    }
    else
    {
      dopplerCorrectionBuf = NULL;
    }


    if ( intAlgHandle->createParams.fftDirection == FFT_TI_DIRECTION_HORIZONTAL )
    {
      numLinesPerBlock = (uint16_t)findNumLinesPerBlock((uint16_t)numPointsFFT, FFT_TI_DIRECTION_HORIZONTAL, (fftInArgs->enable32bitsIntermResults | intAlgHandle->createParams.outputContainerFormat));
      /* If FFT direction is horizontal then find the number of buffers required for the output so that
      all antenna data lies within pitch less than (32kB) */

      numHorzPtPerBlock = (uint16_t)numPointsFFT;
      numVertPtPerBlock = (uint16_t)numLinesPerBlock;

      numSplitRequired = (uint16_t)getBufferSplit(fftInArgs->bufDescription.numAntennas, numPointsFFT, &numPointsPerSplit);
      numPointsLastBlock = (uint16_t)(numPointsFFT - ((numSplitRequired - 1U) * numPointsPerSplit));

      fftOutArgs->bufDescription.numAntennas   = fftInArgs->bufDescription.numAntennas;
      fftOutArgs->bufDescription.numChunks     = numSplitRequired;
      fftOutArgs->bufDescription.numVertPoints = fftInArgs->bufDescription.numVertPoints;

      for ( chunkIdx = 0; chunkIdx < numSplitRequired; chunkIdx++)
      {
        if ( chunkIdx == (numSplitRequired - 1U))
        {
          fftOutArgs->bufDescription.numHorzPoints[chunkIdx]    = (uint16_t)numPointsLastBlock;
        }
        else
        {
          fftOutArgs->bufDescription.numHorzPoints[chunkIdx]    = (uint16_t)numPointsPerSplit;
        }
        fftOutArgs->bufDescription.pitch[chunkIdx]            = (uint32_t)fftOutArgs->bufDescription.numHorzPoints[chunkIdx] *
                                                                fftOutArgs->bufDescription.numAntennas * outputElmtSize;
        fftOutArgs->bufDescription.offsetBwAntennas[chunkIdx] = (uint32_t)fftOutArgs->bufDescription.numHorzPoints[chunkIdx] * outputElmtSize;
      }
    }
    else if ( intAlgHandle->createParams.fftDirection == FFT_TI_DIRECTION_VERTICAL)
    {
      numLinesPerBlock = (uint16_t)findNumLinesPerBlock((uint16_t)numPointsFFT, FFT_TI_DIRECTION_VERTICAL, fftInArgs->enable32bitsIntermResults | intAlgHandle->createParams.outputContainerFormat);

      if (algHandle->createParams.outputContainerFormat== FFT_TI_CONTAINER_FORMAT_32BIT) {
          numLinesPerBlock= numLinesPerBlock>>=1;
          }

#if 0
      if ( numLinesPerBlock < VCOP_SIMD_WIDTH)
      {
        status = FFT_TI_ERRORTYPE_VERT_FFT_UNSUPPORTED_FFT_DIMENSION;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }
#endif
      numHorzPtPerBlock = (uint16_t)numLinesPerBlock;
      numVertPtPerBlock = (uint16_t)numPointsFFT;

      numTotalHorzPoints = 0;
      for ( chunkIdx = 0; chunkIdx < fftInArgs->bufDescription.numChunks; chunkIdx++)
      {
        numTotalHorzPoints += fftInArgs->bufDescription.numHorzPoints[chunkIdx];
      }
      fftOutArgs->bufDescription.numAntennas          = fftInArgs->bufDescription.numAntennas;
      fftOutArgs->bufDescription.numChunks            = 1U;
      fftOutArgs->bufDescription.numHorzPoints[0]     = numLinesPerBlock;
      fftOutArgs->bufDescription.offsetBwAntennas[0]  = (uint32_t)numLinesPerBlock * outputElmtSize;
      fftOutArgs->bufDescription.numVertPoints        = (numTotalHorzPoints * numPointsFFT) / numLinesPerBlock;

      if ( (*outBufDesc)[idx]->bufPlanes[0].width != 0 )
      {
        dopplerOutputPitch = (*outBufDesc)[idx]->bufPlanes[0].width;
        if (dopplerOutputPitch < ((uint32_t)fftOutArgs->bufDescription.numAntennas * numLinesPerBlock * outputElmtSize))
        {
          status = FFT_TI_ERRORTYPE_VERT_FFT_INVALID_OUTPUT_PITCH;
          /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
          /* GOTO is used at error check to jump to end of function, to exit.   */
          goto Exit;
          /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
        }
        if (dopplerOutputPitch > 32767U)
        {
          status = FFT_TI_ERRORTYPE_VERT_FFT_INVALID_OUTPUT_PITCH;
          /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
          /* GOTO is used at error check to jump to end of function, to exit.   */
          goto Exit;
          /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
        }
      }
      else
      {
        dopplerOutputPitch = (uint32_t)fftOutArgs->bufDescription.numAntennas * numLinesPerBlock * outputElmtSize;
      }

      fftOutArgs->bufDescription.pitch[0]             = dopplerOutputPitch;

    }
    else
    {
      status = FFT_TI_ERRORTYPE_FFT_UNSUPPORTED_FFT_DIRECTION;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    for (chunkIdx = 0; chunkIdx < fftInArgs->bufDescription.numChunks; chunkIdx++)
    {
      if ( chunkIdx != 0 )
      {
        numVertPointPreviousChunk = ((fftInArgs->bufDescription.numHorzPoints[chunkIdx - 1U] * numPointsFFT) / numLinesPerBlock);
        /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
        /* MISRA.PTR.ARITH:  Pointer is used in arithmetic or array index expression  */
        /*  These pointers are allocated from user and bound cannot be known within this function. The harmful side effect of voilating this
        rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
        inputDataPtr = inputDataPtr + (fftInArgs->bufDescription.pitch[chunkIdx - 1U] * fftInArgs->bufDescription.numVertPoints);
        outputDataPtr = outputDataPtr +  (numVertPointPreviousChunk * fftOutArgs->bufDescription.pitch[0]);
        /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */
      }
      if ( bamStatus == BAM_S_SUCCESS)
      {

        if (intAlgHandle->createParams.outputContainerFormat== FFT_TI_CONTAINER_FORMAT_32BIT)
        {
                bamStatus = FFT_TI_dmaControl(&(intAlgHandle->graphMem),
                                           &fftInArgs->bufDescription,
                                           &fftOutArgs->bufDescription,
                                           intAlgHandle->createParams.fftDirection,
                                           numLinesPerBlock,
                                           inputDataPtr,
                                           (uint8_t)chunkIdx,
                                           outputDataPtr,
                                           numPointsFFT,
                                           1u);
                if (bamStatus == BAM_S_SUCCESS)
                {
                    bamStatus = FFT32O_TI_kernelControl(&(intAlgHandle->graphMem),
                                                      fftInArgs,
                                                      numActualPoints,
                                                      numHorzPtPerBlock,
                                                      numVertPtPerBlock,
                                                      (int16_t *)(void *)winCoefBuf,
                                                      intAlgHandle->twiddleFactorBufs,
                                                      dopplerCorrectionBuf,
                                                      intAlgHandle->createParams.fftDirection,
                                                      (uint8_t)chunkIdx);

                }
        }
        else
        {
            bamStatus = FFT_TI_dmaControl(&(intAlgHandle->graphMem),
                                               &fftInArgs->bufDescription,
                                               &fftOutArgs->bufDescription,
                                               intAlgHandle->createParams.fftDirection,
                                               numLinesPerBlock,
                                               inputDataPtr,
                                               (uint8_t)chunkIdx,
                                               outputDataPtr,
                                               numPointsFFT,
                                               0u);
            if (bamStatus == BAM_S_SUCCESS)
            {
                bamStatus = FFT_TI_kernelControl(&(intAlgHandle->graphMem),
                                              fftInArgs,
                                              numActualPoints,
                                              numHorzPtPerBlock,
                                              numVertPtPerBlock,
                                              (int16_t *)(void *)winCoefBuf,
                                              intAlgHandle->twiddleFactorBufs,
                                              dopplerCorrectionBuf,
                                              intAlgHandle->createParams.fftDirection,
                                              (uint8_t)chunkIdx);
            }
        }
      }

        if (bamStatus == BAM_S_SUCCESS)
        {
          bamStatus = FFT_TI_execute(&(intAlgHandle->graphMem), &bamInArgs,&bamOutArgs);
        }
      }

    if ( bamStatus != BAM_S_SUCCESS)
    {
        status = IALG_EFAIL;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    numStages = 0;
    numTempPoints = numPointsFFT;

    while (numTempPoints != 0 )
    {
      numTempPoints = numTempPoints >> 2;
      numStages++;
      if ( numTempPoints == 1U)
      {
        break;
      }
    }

    if ( fftInArgs->enableOverFlowDetection == 1 )
    {
      uint8_t (*outScaleFactors)[FFT_TI_MAX_NUM_STAGES];

      if (intAlgHandle->createParams.outputContainerFormat== FFT_TI_CONTAINER_FORMAT_32BIT)
      {
      bamStatus = FFT32O_TI_getWBUFptr(&(intAlgHandle->graphMem),
                                                      &WBUFPtrScaleFactorOut);
      }
      else
      {
      bamStatus = FFT_TI_getWBUFptr(&(intAlgHandle->graphMem),
                                                      &WBUFPtrScaleFactorOut);
      }

      outScaleFactors = (uint8_t (*)[FFT_TI_MAX_NUM_STAGES])(void *)WBUFPtrScaleFactorOut;

      for ( i = 0 ; i < numStages; i++)
      {
        fftOutArgs->scaleFactors[i]     = (*outScaleFactors)[i];
      }

    }
    else
    {
      for ( i = 0 ; i < numStages; i++)
      {
        fftOutArgs->scaleFactors[i]     = 0;
      }
    }



Exit:
    /*----------------------------------*/
    /* Free the input and output buffer */
    /*----------------------------------*/
    outArgs->inFreeBufIDs[FFT_TI_BUFDESC_IN_LISTBUFFER] =
            (*inBufDesc)[FFT_TI_BUFDESC_IN_LISTBUFFER]->bufferId ;

    outArgs->inFreeBufIDs[FFT_TI_BUFDESC_IN_WINDOWING_COEFF_BUF] =
            (*inBufDesc)[FFT_TI_BUFDESC_IN_WINDOWING_COEFF_BUF]->bufferId ;

    outArgs->inFreeBufIDs[FFT_TI_BUFDESC_IN_DOPPLER_CORRECTION_BUF] =
            (*inBufDesc)[FFT_TI_BUFDESC_IN_DOPPLER_CORRECTION_BUF]->bufferId ;

    outArgs->inFreeBufIDs[FFT_TI_BUFDESC_IN_TOTAL] = 0 ;

    outArgs->outFreeBufIDs[FFT_TI_BUFDESC_OUT_BUFFER] =
                (*outBufDesc)[FFT_TI_BUFDESC_OUT_BUFFER]->bufferId ;

    (*outBufDesc)[FFT_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].accessMask =
            IVISION_ACCESSMODE_HWA;

    return status;
}


/*--------------------------------------------------------------------------*/
/* This is the function to do activation of algorithm. All scratch memory   */
/* are restored in this                                                     */
/* Refer algActivate function for details in ialg.h file                    */
/*--------------------------------------------------------------------------*/
void  FFT_TI_activate(IALG_Handle handle)
{
  FFT_TI_Handle algHandle = (FFT_TI_Handle)(void *)handle;
  uint32_t i;

  /*----------------------------------------------------------------*/
  /* Do Activation only if it is deactivated or just after creation */
  /*----------------------------------------------------------------*/
  if(algHandle->algState == ALG_NOT_ACTIVE)
  {
    for(i= 1U; i < algHandle->numMemRecs; i++)
    {
      if((i == ALG_HANDLE_INT_MEMREC) ||(i == FFT_GRAPH_OBJ_INT_MEMREC))
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
void  FFT_TI_deactivate(IALG_Handle handle)
{
  FFT_TI_Handle algHandle = (FFT_TI_Handle)(void *)handle;
  uint32_t i;

  /*----------------------------------------------------------------*/
  /* Do Activation only if it is deactivated or just after creation */
  /*----------------------------------------------------------------*/
  if(algHandle->algState == ALG_ACTIVE)
  {
    for(i= 1U; i < algHandle->numMemRecs; i++)
    {
      if((i == ALG_HANDLE_INT_MEMREC) ||(i == FFT_GRAPH_OBJ_INT_MEMREC))
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
int32_t FFT_TI_free(IALG_Handle handle, IALG_MemRec memRec[])
{
  FFT_TI_Handle algHandle = (FFT_TI_Handle)(void *)handle;

  memcpy(memRec, algHandle->memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

  return (IALG_EOK);
}

