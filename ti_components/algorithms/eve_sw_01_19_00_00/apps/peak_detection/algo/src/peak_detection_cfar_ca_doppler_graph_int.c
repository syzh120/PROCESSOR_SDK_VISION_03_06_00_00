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
 *  @file      peak_detection_cfar_ca_doppler_graph.c
 *
 *  @brief     This file defines the functions for graph for  Peak Detection CFAR CA doppler graph
 *
 *  @version 0.0 (Apr 2017) : Base version.
 */


/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
/*#pragma RESET_MISRA ("required")*/

#include "xdais_types.h"
#include "ipeak_detection_ti.h"

#include "edma_utils.h"

#include "peak_detection_cfar_ca_doppler_graph_int.h"

#include "peak_detection_alg_int.h"


static int32_t PEAK_DETECTION_CFAR_CA_DOPPLER_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams);


#define SOURCE_NODE        (0)
#define PEAK_DETECTION_CFAR_CA_DOPPLER_NODE  (1U)
#define SINK_NODE          (2U)


typedef enum _bam_ti_kernelid
{
    BAM_TI_KERNELID_CUSTOM_CFAR_CA_DOPPLER_DMAREAD_NODE,
    BAM_TI_KERNELID_PEAK_DETECTION_CFAR_CA_DOPPLER,
    BAM_TI_KERNELID_CUSTOM_CFAR_CA_DOPPLER_DMAWRITE_NODE
} BAM_PEAK_DETECTION_CFAR_CA_DOPPLER_TI_KernelID;

/**
 * Kernel Database - used for graph construction. If the application is running others graphs
   that share many common kernels with this local database, it may be worthwhile to move this
   local database into the "master" database defined in kernels/bamdb
 */
static BAM_KernelHostDBdef bamCfarCaDopplerKernelHostDB[] =
{
    { &gBAM_TI_dmaCustomCfarCaDopplerNodeReadKernel, &gBAM_TI_dmaCustomCfarCaDopplerNodeReadKernelHelperFunc,
            "ti_cfar_ca_dma_read", BAM_TI_KERNELID_CUSTOM_CFAR_CA_DOPPLER_DMAREAD_NODE},

    { &gBAM_TI_peakDetectionCfarCaKernel, &gBAM_TI_peakDetectionCfarCaHelperFunc,
            "ti_cfar_ca_doppler", BAM_TI_KERNELID_PEAK_DETECTION_CFAR_CA_DOPPLER },

    { &gBAM_TI_dmaCustomCfarCaDopplerNodeWriteKernel, &gBAM_TI_dmaCustomCfarCaDopplerNodeWriteKernelHelperFunc,
            "ti_cfar_ca_dma_write", BAM_TI_KERNELID_CUSTOM_CFAR_CA_DOPPLER_DMAWRITE_NODE},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamCfarCaDopplerKernelExecFuncDB[] =
{
    { &gBAM_TI_dmaCustomCfarCaDopplerNodeReadKernel, &gBAM_TI_dmaCustomCfarCaDopplerNodeReadKernelExecFunc,
            "ti_cfar_ca_dma_read", BAM_TI_KERNELID_CUSTOM_CFAR_CA_DOPPLER_DMAREAD_NODE},

    { &gBAM_TI_peakDetectionCfarCaKernel, &gBAM_TI_peakDetectionCfarCaExecFunc,
            "ti_cfar_ca_doppler", BAM_TI_KERNELID_PEAK_DETECTION_CFAR_CA_DOPPLER},

    { &gBAM_TI_dmaCustomCfarCaDopplerNodeWriteKernel, &gBAM_TI_dmaCustomCfarCaDopplerNodeWriteKernelExecFunc,
            "ti_cfar_ca_dma_write", BAM_TI_KERNELID_CUSTOM_CFAR_CA_DOPPLER_DMAWRITE_NODE},
};


BAM_KernelDBdef gCfarCaDoppler_TI_BAM_kernelDBdef =
{
    sizeof(bamCfarCaDopplerKernelExecFuncDB) / sizeof(bamCfarCaDopplerKernelExecFuncDB[0]),
    bamCfarCaDopplerKernelHostDB,
    bamCfarCaDopplerKernelExecFuncDB
};



int32_t PEAK_DETECTION_CFAR_CA_DOPPLER_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
  memReq->graphObjSize      = PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_OBJ_SIZE;
  memReq->graphScratchSize  = PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_SCRATCH_SIZE;
  memReq->graphcontextSize  = PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_CONTEXT_SIZE;
  memReq->graphArgsSize    = sizeof(PEAK_DETECTION_CFAR_CA_DOPPLER_TI_graphArgs) ;
  return 0;
}

int32_t PEAK_DETECTION_CFAR_CA_DOPPLER_TI_graphCreate(const BAM_GraphMem * graphMem,
                                                      PEAK_DETECTION_CFAR_CA_DOPPLER_TI_graphCreateParams * createParams)
{
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    PEAK_DETECTION_CFAR_CA_DOPPLER_TI_graphArgs * graphArgs = (PEAK_DETECTION_CFAR_CA_DOPPLER_TI_graphArgs *)graphMem->graphArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/
    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/

    BAM_NodeParams NODELIST[]= {\
            {SOURCE_NODE,           BAM_TI_KERNELID_CUSTOM_CFAR_CA_DOPPLER_DMAREAD_NODE,  NULL},\
            {PEAK_DETECTION_CFAR_CA_DOPPLER_NODE,     BAM_TI_KERNELID_PEAK_DETECTION_CFAR_CA_DOPPLER,          NULL},\
            {SINK_NODE,             BAM_TI_KERNELID_CUSTOM_CFAR_CA_DOPPLER_DMAWRITE_NODE, NULL},\
            {BAM_END_NODE_MARKER,   0,                                        NULL},\
    };

    /* This is done to avoid build errors because of --gcc flag not being enable as per MISRA C */
    NODELIST[SOURCE_NODE].kernelArgs                        = (void *)&graphArgs->dmaReadKernelArgs;
    NODELIST[PEAK_DETECTION_CFAR_CA_DOPPLER_NODE].kernelArgs       = (void *)&graphArgs->cfarCaArgs;

    BAM_EdgeParams EDGELIST[]= {\
            {{SOURCE_NODE, BAM_SOURCE_NODE_PORT1},
                            {PEAK_DETECTION_CFAR_CA_DOPPLER_NODE, BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ENERGY1_PORT}},\

            {{SOURCE_NODE, BAM_SOURCE_NODE_PORT2},
                            {PEAK_DETECTION_CFAR_CA_DOPPLER_NODE, BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ENERGY2_PORT}},\


            {{PEAK_DETECTION_CFAR_CA_DOPPLER_NODE, BAM_PEAK_DETECTION_CFAR_CA_OUTPUT_RANGE_DOPPLER_PORT},
                            {SINK_NODE, BAM_SINK_NODE_PORT1}},\

            {{PEAK_DETECTION_CFAR_CA_DOPPLER_NODE, BAM_PEAK_DETECTION_CFAR_CA_OUTPUT_ENERGY_PORT},
                            {SINK_NODE, BAM_SINK_NODE_PORT2}},\

            {{PEAK_DETECTION_CFAR_CA_DOPPLER_NODE, BAM_PEAK_DETECTION_CFAR_CA_NUM_DETECTIONS_PORT},
                            {SINK_NODE, BAM_SINK_NODE_PORT3}},\

            {{BAM_END_NODE_MARKER, 0},
                            {BAM_END_NODE_MARKER, 0}},\
    };

    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.graphMemConsumed = 0;
    graphCreateParams.onChipScratchMemConsumed = 0;
    graphCreateParams.extMemConsumed = 0;

    status= BAM_initKernelDB(&gCfarCaDoppler_TI_BAM_kernelDBdef);

    if(status != BAM_S_SUCCESS)
    {
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.coreType             = BAM_EVE;
    graphCreateParams.kernelDB             = &gCfarCaDoppler_TI_BAM_kernelDBdef;
    graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
    graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
    graphCreateParams.graphMem             = graphHandle;
    graphCreateParams.graphMemSize         = PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_OBJ_SIZE;
    graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
    graphCreateParams.onChipScratchMemSize = PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_SCRATCH_SIZE;
    graphCreateParams.extMem               = graphMem->graphcontext;
    graphCreateParams.extMemSize           = PEAK_DETECTION_CFAR_CA_DOPPLER_GRAPH_CONTEXT_SIZE;
    graphCreateParams.useSmartMemAlloc     = 1U;
    graphCreateParams.optimizeBlockDim     = 0;

    graphArgs->createParams = createParams;

     /*---------------------------------------------------------------*/
    /* Initialize the members related to the  kernels init function  */
    /*---------------------------------------------------------------*/
    graphCreateParams.initKernelsArgsFunc   = &PEAK_DETECTION_CFAR_CA_DOPPLER_TI_initKernelsArgs;
    graphCreateParams.initKernelsArgsParams = (void*)graphArgs;

    /*---------------------------------------------------------------*/
    /* Initialize the members related to the  kernels init function  */
    /*---------------------------------------------------------------*/
    status = BAM_createGraph(&graphCreateParams, &graphHandle);
    if(status != BAM_S_SUCCESS)
    {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    /*-------------------------------------------------------------------------*/
    /* error message handling and return of error code                         */
    /*-------------------------------------------------------------------------*/
  Exit:
    if (status== BAM_E_INVALID_MEM_SIZE)
    {
      PRINTF("Peak Detection CfarCa: Graph construction failed!!! graphMemSize must be >= %d, onChipScratchMemSize >= %d and extMemSize must be >= %d\n",
        graphCreateParams.graphMemConsumed, graphCreateParams.onChipScratchMemConsumed, graphCreateParams.extMemConsumed);
    }
    else if (status== BAM_E_BLOCK_DIM_TOO_BIG)
    {
      PRINTF("Peak Detection CfarCa: Graph construction failed!!! Decrease the value of blockWidth : or blockHeight :");
    }
    else if (status != BAM_S_SUCCESS)
    {
      PRINTF("Peak Detection CfarCa: Graph construction failed!!!");
    }
    else
    {
       /*BAM_printMemRec(graphCreateParams.memRec, graphCreateParams.numMemRec);*/
    }

    return (status);
}


/*-------------------------------------------------------------------------*/
/* Function to initialize kernel arguments                                 */
/*-------------------------------------------------------------------------*/
static int32_t PEAK_DETECTION_CFAR_CA_DOPPLER_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams)
{
  int32_t status = BAM_S_SUCCESS;

  PEAK_DETECTION_CFAR_CA_DOPPLER_TI_graphArgs              *graphArgs          = (PEAK_DETECTION_CFAR_CA_DOPPLER_TI_graphArgs*)args;
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_initArgs  *dmaReadKernelArgs  = &(graphArgs->dmaReadKernelArgs);
  BAM_PeakDetectionCfarCa_Args       *cfarCaArgs    = &(graphArgs->cfarCaArgs);

  /* Chose these values so as to allocate full 16KB of input buffer which can be allocated
  if we use 1024x8 configuration. Note that each entery is 2 bytes */
  dmaReadKernelArgs->maxNumPoints = 512;
  dmaReadKernelArgs->maxNumLines  = 16;
  dmaReadKernelArgs->maxExtraBufferRequired = graphArgs->createParams->iPeakDetectCreateParams->algoCreateParams.cfarCaDb.maxNoiseLen *
                                             32U * sizeof(uint16_t);

  /* Set maximum value in terms of product of maxNumHorzPoint x maxNumVertPoint */
  cfarCaArgs->maxNumHorzPoint           = 8;
  cfarCaArgs->maxNumVertPoint           = 1024;
  cfarCaArgs->rangeDopplerOrder         = 0;
  cfarCaArgs->maxExtraInputBufRequired  = graphArgs->createParams->iPeakDetectCreateParams->algoCreateParams.cfarCaDb.maxNoiseLen *
                                             32U * sizeof(uint16_t);

  cfarCaArgs->maxNoiseLen               = graphArgs->createParams->iPeakDetectCreateParams->algoCreateParams.cfarCaDb.maxNoiseLen;
  cfarCaArgs->maxGaurdLen               = graphArgs->createParams->iPeakDetectCreateParams->algoCreateParams.cfarCaDb.maxGaurdLen;
  cfarCaArgs->log2QFormat               = PEAK_DETECTION_TI_LUT_Q_FORMAT;


  return (status);

}

/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t PEAK_DETECTION_CFAR_CA_DOPPLER_TI_execute(
        BAM_GraphMem * graphMem,
        const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs)
{

  BAM_ProcessHints hints;
  int32_t status = BAM_S_SUCCESS;

  /* Specify which processing schedule is the best, unsupported for now */
  hints.priority= BAM_COMPUTE_FIRST;

  status  = BAM_process(graphMem->graphObj, inArgs, outArgs, &hints);

  return status;

}

int32_t PEAK_DETECTION_CFAR_CA_DOPPLER_TI_dmaControl(const BAM_GraphMem *graphMem,
                                const PEAK_DETECTION_TI_InArgs *inArgs,
                                uint16_t numDetectionsPerBlock,
                                uint16_t numDetections,
                                const uint16_t (*ptrToEnergyBuf)[],
                                const uint16_t (*ptrToRangeDopplerListIn)[],
                                uint8_t * ptrToRangeDopplerListOut,
                                uint8_t * ptrToEnergyList,
                                uint8_t * ptrToNumDetection)
{
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ctrlArgs  dmaReadCtrlArgs;
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_WRITE_ctrlArgs dmaWriteCtrlArgs;

  int32_t status = BAM_S_SUCCESS;

  /* initilize the sub-handles inside the main handle */
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

  dmaReadCtrlArgs.dopplerDim                = inArgs->dopplerDim;
  dmaReadCtrlArgs.numDetections             = numDetections;
  dmaReadCtrlArgs.numDetectionsPerBlock     = numDetectionsPerBlock;
  dmaReadCtrlArgs.energyPtrExtMem           = ptrToEnergyBuf;
  dmaReadCtrlArgs.rangeDopplerCoordinateBuf = ptrToRangeDopplerListIn;

  status= BAM_controlNode(graphHandle, SOURCE_NODE, &dmaReadCtrlArgs);

  if ( status == 0 )
  {
    dmaWriteCtrlArgs.ptrToEnergyBuf         = ptrToEnergyList;
    dmaWriteCtrlArgs.ptrToRangeDopplerBuf   = ptrToRangeDopplerListOut;
    dmaWriteCtrlArgs.ptrToNumDetectionBuf   = ptrToNumDetection;

    status= BAM_controlNode(graphHandle, SINK_NODE, &dmaWriteCtrlArgs);
  }

  return status;
}


int32_t PEAK_DETECTION_CFAR_CA_DOPPLER_TI_kernelControl(const  BAM_GraphMem * graphMem,
                                  const PEAK_DETECTION_TI_InArgs *inArgs,
                                  uint16_t numDetectionsPerBlock
                                  )
{
  int32_t status = BAM_S_SUCCESS;
  BAM_PeakDetectionCfarCa_ctrlArgs          cfarCaCtrlArgs;
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

  cfarCaCtrlArgs.noiseLen           = inArgs->algoParams.cfarCaDb.noiseLen;
  cfarCaCtrlArgs.gaurdLen           = inArgs->algoParams.cfarCaDb.gaurdLen;
  cfarCaCtrlArgs.numHorzPoint       = numDetectionsPerBlock;
  cfarCaCtrlArgs.numVertPoint       = inArgs->dopplerDim;
  cfarCaCtrlArgs.inputDataPitch     = numDetectionsPerBlock * sizeof(uint16_t);
  cfarCaCtrlArgs.const1             = inArgs->algoParams.cfarCaDb.constant1;
  cfarCaCtrlArgs.const2             = inArgs->algoParams.cfarCaDb.constant2;

  status = BAM_controlNode( graphHandle, PEAK_DETECTION_CFAR_CA_DOPPLER_NODE, &cfarCaCtrlArgs);


  return status;
}



