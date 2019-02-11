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
*  @file       peak_detection_alg.c
*
*  @brief       This file defines the XDAIS/iVISION functions for Peak Detection applet
*  @version     0.0 (Apr 2017) : Base version.
*/

/* #pragma CHECK_MISRA ("none") */
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>
/* #pragma RESET_MISRA ("required") */

#include "peak_detection_alg_int.h"

#include "edma_utils_memcpy.h"
#include "edma_utils.h"
#include "vcop_peak_detection_kernel.h"


#define INDIVIDUAL_PROFILING (0)

#if (INDIVIDUAL_PROFILING)
#include "eve_profile.h"
#endif


/**
* IVISION interface of the algorithm
*/
const IVISION_Fxns PEAK_DETECTION_TI_VISION_FXNS =
{
  {
      &PEAK_DETECTION_TI_activate, /* module ID */
      &PEAK_DETECTION_TI_activate,    /* activate */
      &PEAK_DETECTION_TI_alloc,       /* algAlloc */
      NULL,                      /* control (not suported) */
      &PEAK_DETECTION_TI_deactivate,  /* deactivate */
      &PEAK_DETECTION_TI_free,        /* free */
      &PEAK_DETECTION_TI_init,        /* init */
      NULL,                      /* moved (not suported) */
      &PEAK_DETECTION_TI_numAlloc     /* algNumAlloc  */
  },
  &PEAK_DETECTION_TI_process,
  &PEAK_DETECTION_TI_control
};


/**
* IRES interface of the algorithm
*/
const IRES_Fxns PEAK_DETECTION_TI_IRES = {
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


#define PEAK_DETECTION_TI_MAX_BLOCK_SIZE (16384U)
#define PEAK_DETECTION_TI_MIN_NUM_LINES      (2U)
#define PEAK_DETECTION_TI_LINE_INCREMENT (2U)
#define PEAK_DETECTION_TI_MIN_NUM_HORZ_POINT      (8U)

/**
* Internally used functions
*/

static void extractAntennaData(int16_t outputBuf[],
                                     const int16_t  inputBuf[],
                                     const uint16_t rangeDopplerBuf[],
                                     uint16_t numDetections,
                                     const PEAK_DETECTION_TI_InArgs *inArgs);

static void extractAntennaData(int16_t outputBuf[],
                                     const int16_t inputBuf[],
                                     const uint16_t rangeDopplerBuf[],
                                     uint16_t numDetections,
                                     const PEAK_DETECTION_TI_InArgs *inArgs)
{
  uint16_t detectionIdx;
  uint16_t antennaIdx;
  uint16_t range;
  uint16_t doppler;
  uint16_t rowNum;
  uint16_t columnNum;

  for ( detectionIdx = 0; detectionIdx < numDetections; detectionIdx++)
  {
    range   = rangeDopplerBuf[(2U*detectionIdx) + 1U];
    doppler = rangeDopplerBuf[(2U*detectionIdx) + 0];

    columnNum = range % inArgs->bufDescription.numHorzPoints[0];
    rowNum    = ((range / inArgs->bufDescription.numHorzPoints[0]) *
                 inArgs->dopplerDim) +
                 doppler;

    for ( antennaIdx =0; antennaIdx <inArgs->bufDescription.numAntennas; antennaIdx++)
    {
      outputBuf[(2U * antennaIdx) + (detectionIdx * inArgs->bufDescription.numAntennas * 2U)] =
        inputBuf[(2U * columnNum) + (rowNum * (uint16_t)(inArgs->bufDescription.pitch[0]/sizeof(int16_t)))  +
                 (antennaIdx * inArgs->bufDescription.numHorzPoints[0] * 2U) ];
      outputBuf[(2U * antennaIdx) + (detectionIdx * inArgs->bufDescription.numAntennas * 2U) + 1U] =
              inputBuf[(2U * columnNum) + (rowNum * (uint16_t)(inArgs->bufDescription.pitch[0]/sizeof(int16_t)))  +
                       (antennaIdx * inArgs->bufDescription.numHorzPoints[0] * 2U) + 1U];
    }
  }
}
static uint16_t findNumRowsPerBlock(uint16_t numHorzPointPerAntenna,
                                             uint16_t numAntennas,
                                             uint16_t dopplerDim);

static uint16_t findNumHorzPointPerBlock(uint16_t numHorzPoint,
                                                 uint16_t numVertPoint);


static uint16_t findNumRowsPerBlock(uint16_t numHorzPointPerAntenna,
                                           uint16_t numAntennas,
                                           uint16_t dopplerDim)
{
  uint16_t numBytesPerLine;
  uint16_t numLines = 0;
  uint16_t numTotalBytes = 0;
  numBytesPerLine = numHorzPointPerAntenna * numAntennas * sizeof(int16_t) * 2U;

  numLines = PEAK_DETECTION_TI_MIN_NUM_LINES;
  numTotalBytes = numLines * numBytesPerLine;

  while ( (numTotalBytes < PEAK_DETECTION_TI_MAX_BLOCK_SIZE) && (numLines <= dopplerDim) )
  {
    numLines *= PEAK_DETECTION_TI_LINE_INCREMENT;
    numTotalBytes = numLines * numBytesPerLine;
  }
  numLines = (numLines/ PEAK_DETECTION_TI_LINE_INCREMENT);


  return numLines;
}

static uint16_t findNumHorzPointPerBlock(uint16_t numHorzPoint,
                                                 uint16_t numVertPoint)
{
  uint16_t numHorzPointPerBlock;
  uint16_t numTotalBytes = 0;

  numHorzPointPerBlock = PEAK_DETECTION_TI_MIN_NUM_HORZ_POINT;
  numTotalBytes = numVertPoint * numHorzPointPerBlock * sizeof(uint16_t);

  if ( numTotalBytes < PEAK_DETECTION_TI_MAX_BLOCK_SIZE )
  {
    while ( (numTotalBytes < PEAK_DETECTION_TI_MAX_BLOCK_SIZE) && (numHorzPointPerBlock <= numHorzPoint))
    {
      numHorzPointPerBlock *= PEAK_DETECTION_TI_LINE_INCREMENT;
      numTotalBytes = numVertPoint * numHorzPointPerBlock * sizeof(uint16_t);
    }
    numHorzPointPerBlock = (numHorzPointPerBlock/ PEAK_DETECTION_TI_LINE_INCREMENT);
  }
  else if ( numTotalBytes == PEAK_DETECTION_TI_MAX_BLOCK_SIZE)
  {
    numHorzPointPerBlock = PEAK_DETECTION_TI_MIN_NUM_HORZ_POINT;
  }
  else
  {
    numHorzPointPerBlock = 0;
  }


  return numHorzPointPerBlock;
}

/**
* Other exposed functions
*/
int32_t PEAK_DETECTION_TI_numAlloc(void)
{
  return (NUM_MEMRECS);
}

/*---------------------------------------------------------------*/
/* Function to supply memory requirement to user                 */
/* refer algAlloc function for details in XADIS (ialg.h file)    */
/*---------------------------------------------------------------*/
int32_t PEAK_DETECTION_TI_alloc(const IALG_Params *params,
                                       IALG_Fxns **parentFxns,
                                       IALG_MemRec       memRec[])
{
    int32_t status = IALG_EOK;
    BAM_GraphMemReq graphMemReqEnergyCompGraph;
    BAM_GraphMemReq graphMemReqCfarCaGraph;
    BAM_GraphMemReq graphMemReqCfarCaDopplerGraph;
    uint32_t numLUTPoints;

    const PEAK_DETECTION_TI_CreateParams * createParams =
    (const PEAK_DETECTION_TI_CreateParams*)(const void *)params;
    /*---------------------------------------------------------*/
    /* Request BAM public function about memories assosiated   */
    /* to graph creation                                       */
    /*---------------------------------------------------------*/
    PEAK_DETECTION_ENERGY_COMP_TI_getGraphMemReq(&graphMemReqEnergyCompGraph);
    PEAK_DETECTION_CFAR_CA_TI_getGraphMemReq(&graphMemReqCfarCaGraph);
    PEAK_DETECTION_CFAR_CA_DOPPLER_TI_getGraphMemReq(&graphMemReqCfarCaDopplerGraph);

    /*-----------------------------------------------------------------------------*/
    /*  For memory record ALG_HANDLE_INT_MEMREC and FAST9_GRAPH_OBJ_INT_MEMREC,          */
    /*  which are scratch buffers in BAM_MEMSPACE_DMEM, they must be preceded      */
    /*  by a persistent memory record in IALG_EXTERNAL of the same size.           */
    /*  This persistent record will be used to backup the following scratch        */
    /*  memory record during context saving when PEAK_DETECTION_TI_deactivate */
    /*  is called. Likewise when PEAK_DETECTION_TI_activate it called,        */
    /*  the content of the persistent memory record is copied back to the          */
    /*  scratch memory record in BAM_MEMSPACE_DMEM                                 */
    /*-----------------------------------------------------------------------------*/
    memRec[ALG_HANDLE_MEMREC].size          = sizeof(PEAK_DETECTION_TI_Obj);
    memRec[ALG_HANDLE_MEMREC].space         = (IALG_MemSpace)IALG_EXTERNAL;
    memRec[ALG_HANDLE_MEMREC].attrs         = IALG_PERSIST;
    memRec[ALG_HANDLE_MEMREC].alignment     = 4U;

    memRec[ALG_HANDLE_INT_MEMREC].size      = sizeof(PEAK_DETECTION_TI_Obj);
    memRec[ALG_HANDLE_INT_MEMREC].space     = (IALG_MemSpace)IALG_DARAM0;
    memRec[ALG_HANDLE_INT_MEMREC].attrs     = IALG_SCRATCH;
    memRec[ALG_HANDLE_INT_MEMREC].alignment = 4U;

    /*-------------------------------------------------------------------------*/
    /* Below 5 memory records are used to store data related to the BAM graph: */
    /* 1. PEAK_DETECTION_GRAPH_OBJ_MEMREC     - To hold graph object in external memory       */
    /* 2. PEAK_DETECTION_OBJ_INT_MEMREC - To hold the graph object in internal memory   */
    /* GRAPH OBJECT has 2 instances - internal and external memory - it is to  */
    /* speed up the processing - Main processing will work on internal memory  */
    /* instance and before any one else needing internal memory, deacitavte    */
    /* has to be performed by caller to make sure the data is backed up to ext */
    /* memory                                                                  */
    /*                                                                         */
    /* 3. PEAK_DETECTION_SCRATCH_MEMREC -                                               */
    /*  It is used as scratch memory during graph create time                  */
    /*  Scratch mem is currently placed in external memory.                    */
    /*  For faster graph creation time, you can place it in internal memory    */
    /*                                                                         */
    /* 4. PEAK_DETECTION_CONTEXT_MEMREC                                                 */
    /*  It is used to backup into external memory the graph's                  */
    /*  nodes internal memory records that are persistent.                     */
    /*                                                                         */
    /* 5. PEAK_DETECTION_ARGS_MEMREC  -                                                 */
    /*   It is used keep kernels arguments during graph create time            */
    /*-------------------------------------------------------------------------*/

    memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_OBJ_MEMREC].size  = graphMemReqEnergyCompGraph.graphObjSize;
    memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_OBJ_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_OBJ_MEMREC].attrs = IALG_PERSIST;
    memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_OBJ_MEMREC].alignment      = 4U;

    /*
    PEAK_DETECTION_ENERGY_COMP_GRAPH_OBJ_INT_MEMREC is allocated in DMEM and is used when the backup is
    restored from external memory to faster internal memory when activate is called.
     */
    memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_OBJ_INT_MEMREC].size  = graphMemReqEnergyCompGraph.graphObjSize;
    memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_OBJ_INT_MEMREC].space =(IALG_MemSpace) IALG_DARAM0;
    memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_OBJ_INT_MEMREC].attrs = IALG_SCRATCH;
    memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_OBJ_INT_MEMREC].alignment  = 4U;

    memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_SCRATCH_MEMREC].size  = graphMemReqEnergyCompGraph.graphScratchSize;
    memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_SCRATCH_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_SCRATCH_MEMREC].attrs = IALG_SCRATCH;
    memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_SCRATCH_MEMREC].alignment  = 4U;

    memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_CONTEXT_MEMREC].size  = graphMemReqEnergyCompGraph.graphcontextSize;
    memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_CONTEXT_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_CONTEXT_MEMREC].attrs = IALG_SCRATCH;
    memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_CONTEXT_MEMREC].alignment  = 4U;

    memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_ARGS_MEMREC].size  = graphMemReqEnergyCompGraph.graphArgsSize;
    memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_ARGS_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_ARGS_MEMREC].attrs = IALG_SCRATCH;
    memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_ARGS_MEMREC].alignment     = 4U;

    memRec[PEAK_DETECTION_CFAR_CA_GRAPH_OBJ_MEMREC].size  = graphMemReqCfarCaGraph.graphObjSize;
    memRec[PEAK_DETECTION_CFAR_CA_GRAPH_OBJ_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[PEAK_DETECTION_CFAR_CA_GRAPH_OBJ_MEMREC].attrs = IALG_PERSIST;
    memRec[PEAK_DETECTION_CFAR_CA_GRAPH_OBJ_MEMREC].alignment      = 4U;

    /*
    PEAK_DETECTION_CFAR_CA_GRAPH_OBJ_INT_MEMREC is allocated in DMEM and is used when the backup is
    restored from external memory to faster internal memory when activate is called.
     */
    memRec[PEAK_DETECTION_CFAR_CA_GRAPH_OBJ_INT_MEMREC].size  = graphMemReqCfarCaGraph.graphObjSize;
    memRec[PEAK_DETECTION_CFAR_CA_GRAPH_OBJ_INT_MEMREC].space =(IALG_MemSpace) IALG_DARAM0;
    memRec[PEAK_DETECTION_CFAR_CA_GRAPH_OBJ_INT_MEMREC].attrs = IALG_SCRATCH;
    memRec[PEAK_DETECTION_CFAR_CA_GRAPH_OBJ_INT_MEMREC].alignment  = 4U;

    memRec[PEAK_DETECTION_CFAR_CA_GRAPH_SCRATCH_MEMREC].size  = graphMemReqCfarCaGraph.graphScratchSize;
    memRec[PEAK_DETECTION_CFAR_CA_GRAPH_SCRATCH_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[PEAK_DETECTION_CFAR_CA_GRAPH_SCRATCH_MEMREC].attrs = IALG_SCRATCH;
    memRec[PEAK_DETECTION_CFAR_CA_GRAPH_SCRATCH_MEMREC].alignment  = 4U;

    memRec[PEAK_DETECTION_CFAR_CA_GRAPH_CONTEXT_MEMREC].size  = graphMemReqCfarCaGraph.graphcontextSize;
    memRec[PEAK_DETECTION_CFAR_CA_GRAPH_CONTEXT_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[PEAK_DETECTION_CFAR_CA_GRAPH_CONTEXT_MEMREC].attrs = IALG_SCRATCH;
    memRec[PEAK_DETECTION_CFAR_CA_GRAPH_CONTEXT_MEMREC].alignment  = 4U;

    memRec[PEAK_DETECTION_CFAR_CA_GRAPH_ARGS_MEMREC].size  = graphMemReqCfarCaGraph.graphArgsSize;
    memRec[PEAK_DETECTION_CFAR_CA_GRAPH_ARGS_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[PEAK_DETECTION_CFAR_CA_GRAPH_ARGS_MEMREC].attrs = IALG_SCRATCH;
    memRec[PEAK_DETECTION_CFAR_CA_GRAPH_ARGS_MEMREC].alignment     = 4U;

    memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_OBJ_MEMREC].size  = graphMemReqCfarCaDopplerGraph.graphObjSize;
    memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_OBJ_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_OBJ_MEMREC].attrs = IALG_PERSIST;
    memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_OBJ_MEMREC].alignment      = 4U;

    /*
    PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_OBJ_INT_MEMREC is allocated in DMEM and is used when the backup is
    restored from external memory to faster internal memory when activate is called.
     */
    memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_OBJ_INT_MEMREC].size  = graphMemReqCfarCaDopplerGraph.graphObjSize;
    memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_OBJ_INT_MEMREC].space =(IALG_MemSpace) IALG_DARAM0;
    memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_OBJ_INT_MEMREC].attrs = IALG_SCRATCH;
    memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_OBJ_INT_MEMREC].alignment  = 4U;

    memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_SCRATCH_MEMREC].size  = graphMemReqCfarCaDopplerGraph.graphScratchSize;
    memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_SCRATCH_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_SCRATCH_MEMREC].attrs = IALG_SCRATCH;
    memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_SCRATCH_MEMREC].alignment  = 4U;

    memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_CONTEXT_MEMREC].size  = graphMemReqCfarCaDopplerGraph.graphcontextSize;
    memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_CONTEXT_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_CONTEXT_MEMREC].attrs = IALG_SCRATCH;
    memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_CONTEXT_MEMREC].alignment  = 4U;

    memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_ARGS_MEMREC].size  = graphMemReqCfarCaDopplerGraph.graphArgsSize;
    memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_ARGS_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_ARGS_MEMREC].attrs = IALG_SCRATCH;
    memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_ARGS_MEMREC].alignment     = 4U;

    /* This buffer is to store intermediate energy */
    if ( createParams->detectionMethod == PEAK_DETECTION_TI_METHOD_ENERGY_OUT)
    {
      /* In this case we dont need this buffer so just request small memory so that
      allocation doesnt fail */
      memRec[PEAK_DETECTION_INTERIM_ENERGY_BUF].size  = 4U;
    }
    else
    {
      memRec[PEAK_DETECTION_INTERIM_ENERGY_BUF].size  = createParams->maxRangeDimension *
                                                        createParams->maxDopplerDimension * sizeof(uint16_t);
    }
    memRec[PEAK_DETECTION_INTERIM_ENERGY_BUF].space =(IALG_MemSpace) IALG_SARAM0;
    memRec[PEAK_DETECTION_INTERIM_ENERGY_BUF].attrs = IALG_SCRATCH;
    memRec[PEAK_DETECTION_INTERIM_ENERGY_BUF].alignment     = 128U;


    numLUTPoints = (uint32_t)((uint32_t)1U<<(uint32_t)(PEAK_DETECTION_TI_ALPHA_Q_FORMAT));

    memRec[PEAK_DETECTION_LUT_TABLE_BUF].size  = (numLUTPoints / 2U ) *
                                                  PEAK_DETECTION_ENERGY_COMP_NUM_TABLES *
                                                  sizeof(uint32_t);
    memRec[PEAK_DETECTION_LUT_TABLE_BUF].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[PEAK_DETECTION_LUT_TABLE_BUF].attrs = IALG_PERSIST;
    memRec[PEAK_DETECTION_LUT_TABLE_BUF].alignment     = 128U;

    memRec[PEAK_DETECTION_INTERIM_RANGEDOPPLER_LISTBUF].size  = (createParams->maxRangeDimension *
                                                      createParams->maxDopplerDimension * sizeof(uint16_t) * 2U);
    memRec[PEAK_DETECTION_INTERIM_RANGEDOPPLER_LISTBUF].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[PEAK_DETECTION_INTERIM_RANGEDOPPLER_LISTBUF].attrs = IALG_PERSIST;
    memRec[PEAK_DETECTION_INTERIM_RANGEDOPPLER_LISTBUF].alignment     = 128U;

    return (status);
}

typedef double float64_t;

/*-----------------------------------------------------------------------*/
/* Function to accept memory pointers from user and initialize algorithm */
/* Refer algInit function for details in XADIS (ialg.h file)             */
/*-----------------------------------------------------------------------*/
int32_t PEAK_DETECTION_TI_init(IALG_Handle        handle,
                                     const IALG_MemRec  memRec[],
                                     IALG_Handle        parent,
                                     const IALG_Params *params)
{
    int32_t status = IALG_EOK;
    int32_t bamStatus;
    uint32_t numLUTPoints;
    uint32_t i,j;
    bamStatus =  BAM_S_SUCCESS;

    PEAK_DETECTION_TI_Handle algHandle =
            (PEAK_DETECTION_TI_Handle)(void *)memRec[ALG_HANDLE_MEMREC].base;
    const PEAK_DETECTION_TI_CreateParams* createParams = (const PEAK_DETECTION_TI_CreateParams * )(const void *)params;
    PEAK_DETECTION_ENERGY_COMP_TI_graphCreateParams     energyCompGraphCreateParams;
    PEAK_DETECTION_CFAR_CA_TI_graphCreateParams         cfarCaGraphCreateParams;
    PEAK_DETECTION_CFAR_CA_DOPPLER_TI_graphCreateParams         cfarCaDopplerGraphCreateParams;


    algHandle->energyCompGraphMem.graphObj      = memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_OBJ_MEMREC].base;
    algHandle->energyCompGraphMem.graphScratch  = memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_SCRATCH_MEMREC].base;
    algHandle->energyCompGraphMem.graphcontext  = memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_CONTEXT_MEMREC].base;
    algHandle->energyCompGraphMem.graphArgs     = memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_ARGS_MEMREC].base;


    algHandle->cfarCaGraphMem.graphObj      = memRec[PEAK_DETECTION_CFAR_CA_GRAPH_OBJ_MEMREC].base;
    algHandle->cfarCaGraphMem.graphScratch  = memRec[PEAK_DETECTION_CFAR_CA_GRAPH_SCRATCH_MEMREC].base;
    algHandle->cfarCaGraphMem.graphcontext  = memRec[PEAK_DETECTION_CFAR_CA_GRAPH_CONTEXT_MEMREC].base;
    algHandle->cfarCaGraphMem.graphArgs     = memRec[PEAK_DETECTION_CFAR_CA_GRAPH_ARGS_MEMREC].base;

    algHandle->cfarCaDopplerGraphMem.graphObj      = memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_OBJ_MEMREC].base;
    algHandle->cfarCaDopplerGraphMem.graphScratch  = memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_SCRATCH_MEMREC].base;
    algHandle->cfarCaDopplerGraphMem.graphcontext  = memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_CONTEXT_MEMREC].base;
    algHandle->cfarCaDopplerGraphMem.graphArgs     = memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_ARGS_MEMREC].base;

    algHandle->createParams = *createParams;

    energyCompGraphCreateParams.iPeakDetectCreateParams = createParams;

    bamStatus = PEAK_DETECTION_ENERGY_COMP_TI_graphCreate(&(algHandle->energyCompGraphMem),
                                                      &energyCompGraphCreateParams);


    if ( bamStatus == BAM_E_BLOCK_DIM_TOO_BIG)
    {
        status = PEAK_DETECTION_TI_ERRORTYPE_UNSUPPORTED_CONFIGURATION;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
       /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    cfarCaGraphCreateParams.iPeakDetectCreateParams = createParams;
    bamStatus = PEAK_DETECTION_CFAR_CA_TI_graphCreate(&(algHandle->cfarCaGraphMem),
                                                      &cfarCaGraphCreateParams);

    if ( bamStatus == BAM_E_BLOCK_DIM_TOO_BIG)
    {
        status = PEAK_DETECTION_TI_ERRORTYPE_UNSUPPORTED_CONFIGURATION;
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

    cfarCaDopplerGraphCreateParams.iPeakDetectCreateParams = createParams;
    bamStatus = PEAK_DETECTION_CFAR_CA_DOPPLER_TI_graphCreate(&(algHandle->cfarCaDopplerGraphMem),
                                                      &cfarCaDopplerGraphCreateParams);

    if ( bamStatus == BAM_E_BLOCK_DIM_TOO_BIG)
    {
        status = PEAK_DETECTION_TI_ERRORTYPE_UNSUPPORTED_CONFIGURATION;
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
    algHandle->ivision = &PEAK_DETECTION_TI_VISION_FXNS;

    /*-----------------------------------------------------------------------*/
    /* State to indicate that internal context of algorithm is not active    */
    /*-----------------------------------------------------------------------*/
    algHandle->algState = ALG_NOT_ACTIVE;

    EDMA_UTILS_setEdma3RmHandle(NULL);

    algHandle->lutTableBasePtr = (uint16_t (*)[])(void *)algHandle->memRec[PEAK_DETECTION_LUT_TABLE_BUF].base;

    numLUTPoints = (uint32_t)((uint32_t)1U<<(uint32_t)(PEAK_DETECTION_TI_ALPHA_Q_FORMAT));

    /* Generate LUT For binary Scaling */
    for ( i = 0; i < numLUTPoints ; i+=2U)
    {
      float64_t one_plus_aplha;
      float64_t tempFloat;
      uint32_t scaleFactor  = (uint32_t)( (uint32_t)1U << (uint32_t)PEAK_DETECTION_TI_LUT_Q_FORMAT);

      one_plus_aplha = (float64_t)((float64_t)i + (float64_t)numLUTPoints) /(float64_t)numLUTPoints    ;

      tempFloat = (((float64_t)log(one_plus_aplha) / (float64_t)log((float64_t)2.0) ) *
                                                (float64_t)scaleFactor);
      (*algHandle->lutTableBasePtr)[8U * i] =  (uint16_t)tempFloat;

      one_plus_aplha = (float64_t)((float64_t)i + (float64_t)1U + (float64_t)numLUTPoints) /(float64_t)numLUTPoints    ;

      tempFloat = (((float64_t)log(one_plus_aplha) / (float64_t)log((float64_t)2.0) ) *
                                                (float64_t)scaleFactor);

      (*algHandle->lutTableBasePtr)[(8U * i) + 1U] =  (uint16_t)tempFloat;
      for ( j = 1U; j < 8U;j++)
      {
        (*algHandle->lutTableBasePtr)[(8U * i)  + (2U * j) ] = (*algHandle->lutTableBasePtr)[8U* i];
        (*algHandle->lutTableBasePtr)[(8U * i) + (2U * j) + 1U] = (*algHandle->lutTableBasePtr)[(8U * i) + 1U];
      }
    }

Exit:
    return (status);
}


/*-----------------------------------------------------------------------*/
/* Function to accept any run time updates with recreation of object     */
/* Refer algControl function for details in ivision.h file               */
/* Not implemented for this function                                     */
/*-----------------------------------------------------------------------*/
int32_t PEAK_DETECTION_TI_control(IVISION_Handle     handle,
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
int32_t PEAK_DETECTION_TI_process(IVISION_Handle   handle,
                                           IVISION_InBufs  *inBufs,
                                           IVISION_OutBufs *outBufs,
                                           IVISION_InArgs  *inArgs,
                                           IVISION_OutArgs *outArgs)
{
  /* RESET_MISRA("16.7")  -> Reset rule 16.7     */

    PEAK_DETECTION_TI_Handle algHandle = (PEAK_DETECTION_TI_Handle)(void *)(handle);
    PEAK_DETECTION_TI_Handle intAlgHandle;
    int32_t status            = IALG_EOK;
    int32_t bamStatus  = BAM_S_SUCCESS;
    IBAMALG_InArgs          bamInArgs;
    IBAMALG_OutArgs         bamOutArgs;
    PEAK_DETECTION_TI_InArgs  *peak_detectionInArgs;
    PEAK_DETECTION_TI_OutArgs  *peak_detectionOutArgs;
    uint8_t * antennaDataPtr;
    uint8_t * interimOutputEnergy;
    uint8_t * interimRangeDopplerListBuf;
    uint32_t idx;
    uint16_t numRowsPerBlock;
    uint16_t numHorzPointPerBlock;
    uint16_t numDetections;
    uint16_t numDetectionsFinal;

    IVISION_BufDesc    *(*inBufDesc)[PEAK_DETECTION_TI_BUFDESC_IN_TOTAL];
    IVISION_BufDesc    *(*outBufDesc)[PEAK_DETECTION_TI_BUFDESC_OUT_TOTAL];


    inBufDesc  = (IVISION_BufDesc *(*)[PEAK_DETECTION_TI_BUFDESC_IN_TOTAL])(void *)inBufs->bufDesc;
    outBufDesc = (IVISION_BufDesc *(*)[PEAK_DETECTION_TI_BUFDESC_OUT_TOTAL])(void *)outBufs->bufDesc;

    if (inArgs->size != sizeof(PEAK_DETECTION_TI_InArgs))
    {
      status = IALG_EFAIL;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }
    if (outArgs->size != sizeof(PEAK_DETECTION_TI_OutArgs))
    {
      status = IALG_EFAIL;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    peak_detectionInArgs  = (PEAK_DETECTION_TI_InArgs *)(void *)inArgs;
    peak_detectionOutArgs = (PEAK_DETECTION_TI_OutArgs *)(void *)outArgs;


    /*-----------------------------------------------------------------------*/
    /* Activate the algorithm to make sure that now onwards internal memory  */
    /* handle can be utilized                                                */
    /*-----------------------------------------------------------------------*/
    PEAK_DETECTION_TI_activate((IALG_Handle)(void *)handle);

    intAlgHandle                      = (PEAK_DETECTION_TI_Handle)(void *)algHandle->memRec[ALG_HANDLE_INT_MEMREC].base;
    intAlgHandle->energyCompGraphMem.graphObj      =
            intAlgHandle->memRec[PEAK_DETECTION_ENERGY_COMP_GRAPH_OBJ_INT_MEMREC].base;

    intAlgHandle->cfarCaGraphMem.graphObj      =
            intAlgHandle->memRec[PEAK_DETECTION_CFAR_CA_GRAPH_OBJ_INT_MEMREC].base;

    intAlgHandle->cfarCaDopplerGraphMem.graphObj      =
                intAlgHandle->memRec[PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_OBJ_INT_MEMREC].base;

    if ( intAlgHandle->createParams.detectionMethod == PEAK_DETECTION_TI_METHOD_CFARCA_DB)
    {
      if(((peak_detectionInArgs->algoParams.cfarCaDb.noiseLen) & (peak_detectionInArgs->algoParams.cfarCaDb.noiseLen - 1U)) != 0 )
      {
          status = PEAK_DETECTION_TI_ERRORTYPE_UNSUPPORTED_NOISE_LENGTH;
          /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
          /* GOTO is used at error check to jump to end of function, to exit.   */
          goto Exit;
          /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }

      if(peak_detectionInArgs->algoParams.cfarCaDb.noiseLen == 0 )
      {
          status = PEAK_DETECTION_TI_ERRORTYPE_UNSUPPORTED_NOISE_LENGTH;
          /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
          /* GOTO is used at error check to jump to end of function, to exit.   */
          goto Exit;
          /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }
      if(peak_detectionInArgs->dopplerDim > 512 )
      {
          status = PEAK_DETECTION_TI_ERRORTYPE_UNSUPPORTED_DOPPLER_DIMENSION;
          /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
          /* GOTO is used at error check to jump to end of function, to exit.   */
          goto Exit;
          /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }
    }
    bamInArgs.size        = sizeof(IBAMALG_InArgs);
    bamInArgs.sliceIndex  = 0;

    bamOutArgs.size       = sizeof(IBAMALG_OutArgs);




    idx = PEAK_DETECTION_TI_BUFDESC_IN_ANTENNA_DATA_BUF;

    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are allocated from the user outside this applet hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
    rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    antennaDataPtr = (uint8_t *)(*inBufDesc)[idx]->bufPlanes[0].buf;
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    if ( intAlgHandle->createParams.detectionMethod == PEAK_DETECTION_TI_METHOD_CFARCA_DB)
    {
      interimOutputEnergy = (uint8_t *)(void *)intAlgHandle->memRec[PEAK_DETECTION_INTERIM_ENERGY_BUF].base;
    }
    else
    {
      interimOutputEnergy = (uint8_t *)(uint8_t *)(*outBufDesc)[PEAK_DETECTION_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].buf;
    }

   interimRangeDopplerListBuf = (uint8_t *)(void *)intAlgHandle->memRec[PEAK_DETECTION_INTERIM_RANGEDOPPLER_LISTBUF].base;

#if INDIVIDUAL_PROFILING
    profiler_start();
#endif

   numRowsPerBlock = findNumRowsPerBlock(peak_detectionInArgs->bufDescription.numHorzPoints[0],
                                         peak_detectionInArgs->bufDescription.numAntennas,
                                         peak_detectionInArgs->dopplerDim);


   bamStatus = PEAK_DETECTION_ENERGY_COMP_TI_dmaControl(&(intAlgHandle->energyCompGraphMem),
                                        peak_detectionInArgs,
                                        numRowsPerBlock,
                                        antennaDataPtr,
                                        interimOutputEnergy);


    if (bamStatus == BAM_S_SUCCESS)
    {
      bamStatus = PEAK_DETECTION_ENERGY_COMP_TI_kernelControl(&(intAlgHandle->energyCompGraphMem),
                                                peak_detectionInArgs,
                                                numRowsPerBlock,
                                                (uint8_t *)(void *)intAlgHandle->lutTableBasePtr);
    }

    if (bamStatus == BAM_S_SUCCESS)
    {
      bamStatus = PEAK_DETECTION_ENERGY_COMP_TI_execute(&(intAlgHandle->energyCompGraphMem), &bamInArgs,&bamOutArgs);
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

  if ( intAlgHandle->createParams.detectionMethod == PEAK_DETECTION_TI_METHOD_CFARCA_DB )
  {
      numHorzPointPerBlock = findNumHorzPointPerBlock(peak_detectionInArgs->dopplerDim,
                                                      peak_detectionInArgs->rangeDim);


      if (numHorzPointPerBlock == 0 )
      {
        status = PEAK_DETECTION_TI_ERRORTYPE_UNSUPPORTED_CONFIGURATION;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }

      bamStatus = PEAK_DETECTION_CFAR_CA_TI_dmaControl(&(intAlgHandle->cfarCaGraphMem),
                                              peak_detectionInArgs,
                                              numHorzPointPerBlock,
                                              interimOutputEnergy,
                                              (uint8_t *)interimRangeDopplerListBuf,
                                              (uint8_t *)(*outBufDesc)[PEAK_DETECTION_TI_BUFDESC_OUT_ENERGY_BUFFER]->bufPlanes[0].buf,
                                              (uint8_t *)(void *)&numDetections);


      if (bamStatus == BAM_S_SUCCESS)
      {
        bamStatus = PEAK_DETECTION_CFAR_CA_TI_kernelControl(&(intAlgHandle->cfarCaGraphMem),
                                                  peak_detectionInArgs,
                                                  numHorzPointPerBlock);
      }

      if (bamStatus == BAM_S_SUCCESS)
      {
        bamStatus = PEAK_DETECTION_CFAR_CA_TI_execute(&(intAlgHandle->cfarCaGraphMem), &bamInArgs,&bamOutArgs);
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


      if ( peak_detectionInArgs->dopplerDim == 512U)
      {
        numHorzPointPerBlock = 16U;
      }
      else
      {
        numHorzPointPerBlock = 32U;
      }

      numDetectionsFinal = numDetections;
      if ( numDetections != 0 )
      {
        bamStatus = PEAK_DETECTION_CFAR_CA_DOPPLER_TI_dmaControl(&(intAlgHandle->cfarCaDopplerGraphMem),
                                                peak_detectionInArgs,
                                                numHorzPointPerBlock,
                                                numDetections,
                                                (const uint16_t (*)[])(const void *)interimOutputEnergy,
                                                (const uint16_t (*)[])(const void *)interimRangeDopplerListBuf,
                                                (uint8_t *)(*outBufDesc)[PEAK_DETECTION_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].buf,
                                                (uint8_t *)(*outBufDesc)[PEAK_DETECTION_TI_BUFDESC_OUT_ENERGY_BUFFER]->bufPlanes[0].buf,
                                                (uint8_t *)(void *)&numDetectionsFinal);


        if (bamStatus == BAM_S_SUCCESS)
        {
          bamStatus = PEAK_DETECTION_CFAR_CA_DOPPLER_TI_kernelControl(&(intAlgHandle->cfarCaDopplerGraphMem),
                                                    peak_detectionInArgs,
                                                    numHorzPointPerBlock);
        }

        if (bamStatus == BAM_S_SUCCESS)
        {
          bamStatus = PEAK_DETECTION_CFAR_CA_DOPPLER_TI_execute(&(intAlgHandle->cfarCaDopplerGraphMem), &bamInArgs,&bamOutArgs);
        }

        if ( bamStatus != BAM_S_SUCCESS)
        {
            status = IALG_EFAIL;
            /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
            /* GOTO is used at error check to jump to end of function, to exit.   */
            goto Exit;
            /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
        }
      }
      peak_detectionOutArgs->numDetections = numDetectionsFinal;

#if INDIVIDUAL_PROFILING
      profiler_end_print(1);
      profiler_start();
#endif

      if ( intAlgHandle->createParams.enableAntennaDataOut == 1 )
      {
        extractAntennaData((int16_t *)(*outBufDesc)[PEAK_DETECTION_TI_BUFDESC_OUT_ANTENNA_DATA]->bufPlanes[0].buf,
                          (int16_t *)(void *)antennaDataPtr,
                          (uint16_t *)(*outBufDesc)[PEAK_DETECTION_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].buf,
                           numDetections,
                           peak_detectionInArgs
                           );
      }


#if INDIVIDUAL_PROFILING
      profiler_end_print(1);
#endif
    }


Exit:
    /*----------------------------------*/
    /* Free the input and output buffer */
    /*----------------------------------*/
    outArgs->inFreeBufIDs[PEAK_DETECTION_TI_BUFDESC_IN_ANTENNA_DATA_BUF] =
            (*inBufDesc)[PEAK_DETECTION_TI_BUFDESC_IN_ANTENNA_DATA_BUF]->bufferId ;

    outArgs->inFreeBufIDs[PEAK_DETECTION_TI_BUFDESC_IN_TOTAL] = 0 ;


    outArgs->outFreeBufIDs[PEAK_DETECTION_TI_BUFDESC_OUT_BUFFER] =
                (*outBufDesc)[PEAK_DETECTION_TI_BUFDESC_OUT_BUFFER]->bufferId ;

    (*outBufDesc)[PEAK_DETECTION_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].accessMask =
            IVISION_ACCESSMODE_HWA;


    if ( algHandle->createParams.detectionMethod == PEAK_DETECTION_TI_METHOD_CFARCA_DB )
    {
      outArgs->outFreeBufIDs[PEAK_DETECTION_TI_BUFDESC_OUT_ENERGY_BUFFER] =
                      (*outBufDesc)[PEAK_DETECTION_TI_BUFDESC_OUT_ENERGY_BUFFER]->bufferId ;

          (*outBufDesc)[PEAK_DETECTION_TI_BUFDESC_OUT_ENERGY_BUFFER]->bufPlanes[0].accessMask =
                  IVISION_ACCESSMODE_HWA;
    }

    if ( algHandle->createParams.enableAntennaDataOut == 1U )
    {
      outArgs->outFreeBufIDs[PEAK_DETECTION_TI_BUFDESC_OUT_ANTENNA_DATA] =
                      (*outBufDesc)[PEAK_DETECTION_TI_BUFDESC_OUT_ANTENNA_DATA]->bufferId ;

          (*outBufDesc)[PEAK_DETECTION_TI_BUFDESC_OUT_ANTENNA_DATA]->bufPlanes[0].accessMask =
                  IVISION_ACCESSMODE_HWA;
    }

    return status;
}


/*--------------------------------------------------------------------------*/
/* This is the function to do activation of algorithm. All scratch memory   */
/* are restored in this                                                     */
/* Refer algActivate function for details in ialg.h file                    */
/*--------------------------------------------------------------------------*/
void  PEAK_DETECTION_TI_activate(IALG_Handle handle)
{
  PEAK_DETECTION_TI_Handle algHandle = (PEAK_DETECTION_TI_Handle)(void *)handle;
  uint32_t i;

  /*----------------------------------------------------------------*/
  /* Do Activation only if it is deactivated or just after creation */
  /*----------------------------------------------------------------*/
  if(algHandle->algState == ALG_NOT_ACTIVE)
  {
    for(i= 1U; i < algHandle->numMemRecs; i++)
    {
      if((i == ALG_HANDLE_INT_MEMREC) ||(i == PEAK_DETECTION_ENERGY_COMP_GRAPH_OBJ_INT_MEMREC) ||
        (i == PEAK_DETECTION_CFAR_CA_GRAPH_OBJ_INT_MEMREC) ||
        (i == PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_OBJ_INT_MEMREC))
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
void  PEAK_DETECTION_TI_deactivate(IALG_Handle handle)
{
  PEAK_DETECTION_TI_Handle algHandle = (PEAK_DETECTION_TI_Handle)(void *)handle;
  uint32_t i;

  /*----------------------------------------------------------------*/
  /* Do Activation only if it is deactivated or just after creation */
  /*----------------------------------------------------------------*/
  if(algHandle->algState == ALG_ACTIVE)
  {
    for(i= 1U; i < algHandle->numMemRecs; i++)
    {
      if((i == ALG_HANDLE_INT_MEMREC) ||(i == PEAK_DETECTION_ENERGY_COMP_GRAPH_OBJ_INT_MEMREC) ||
        (i == PEAK_DETECTION_CFAR_CA_GRAPH_OBJ_INT_MEMREC) ||
        (i == PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_OBJ_INT_MEMREC))
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
int32_t PEAK_DETECTION_TI_free(IALG_Handle handle, IALG_MemRec memRec[])
{
  PEAK_DETECTION_TI_Handle algHandle = (PEAK_DETECTION_TI_Handle)(void *)handle;

  memcpy(memRec, algHandle->memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

  return (IALG_EOK);
}

