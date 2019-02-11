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
 *  @file      peak_detection_energy_comp_graph.c
 *
 *  @brief     This file defines the functions for graph for  Peak Detection energy computation graph
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

#include "peak_detection_energy_comp_graph_int.h"

#include "peak_detection_alg_int.h"
#include "bam_dma_custom_energy_comp_node.h"

static int32_t PEAK_DETECTION_ENERGY_COMP_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams);


#define SOURCE_NODE        (0)
#define PEAK_DETECTION_ENERGY_COMP_NODE  (1U)
#define SINK_NODE          (2U)


typedef enum _bam_ti_kernelid
{
    BAM_TI_KERNELID_CUSTOM_ENERGY_COMP_DMAREAD_NODE,
    BAM_TI_KERNELID_PEAK_DETECTION_ENERGY_COMP,
    BAM_TI_KERNELID_CUSTOM_ENERGY_COMP_DMAWRITE_NODE
} BAM_PEAK_DETECTION_ENERGY_COMP_TI_KernelID;

/**
 * Kernel Database - used for graph construction. If the application is running others graphs
   that share many common kernels with this local database, it may be worthwhile to move this
   local database into the "master" database defined in kernels/bamdb
 */
static BAM_KernelHostDBdef bamEnergyCompKernelHostDB[] =
{
    { &gBAM_TI_dmaCustomEnergyCompNodeReadKernel, &gBAM_TI_dmaCustomEnergyCompNodeReadKernelHelperFunc,
            "ti_energy_comp_dma_read", BAM_TI_KERNELID_CUSTOM_ENERGY_COMP_DMAREAD_NODE},

    { &gBAM_TI_peakDetectionEnergyComputeKernel, &gBAM_TI_peakDetectionEnergyComputeHelperFunc,
            "ti_energy_comp", BAM_TI_KERNELID_PEAK_DETECTION_ENERGY_COMP },

    { &gBAM_TI_dmaCustomEnergyCompNodeWriteKernel, &gBAM_TI_dmaCustomEnergyCompNodeWriteKernelHelperFunc,
            "ti_energy_comp_dma_write", BAM_TI_KERNELID_CUSTOM_ENERGY_COMP_DMAWRITE_NODE},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamEnergyCompKernelExecFuncDB[] =
{
    { &gBAM_TI_dmaCustomEnergyCompNodeReadKernel, &gBAM_TI_dmaCustomEnergyCompNodeReadKernelExecFunc,
            "ti_energy_comp_dma_read", BAM_TI_KERNELID_CUSTOM_ENERGY_COMP_DMAREAD_NODE},

    { &gBAM_TI_peakDetectionEnergyComputeKernel, &gBAM_TI_peakDetectionEnergyComputeExecFunc,
            "ti_energy_comp", BAM_TI_KERNELID_PEAK_DETECTION_ENERGY_COMP},

    { &gBAM_TI_dmaCustomEnergyCompNodeWriteKernel, &gBAM_TI_dmaCustomEnergyCompNodeWriteKernelExecFunc,
            "ti_energy_comp_dma_write", BAM_TI_KERNELID_CUSTOM_ENERGY_COMP_DMAWRITE_NODE},
};


BAM_KernelDBdef gEnergyComp_TI_BAM_kernelDBdef =
{
    sizeof(bamEnergyCompKernelExecFuncDB) / sizeof(bamEnergyCompKernelExecFuncDB[0]),
    bamEnergyCompKernelHostDB,
    bamEnergyCompKernelExecFuncDB
};



int32_t PEAK_DETECTION_ENERGY_COMP_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
  memReq->graphObjSize      = PEAK_DETECTION_ENERGY_COMP_GRAPH_OBJ_SIZE;
  memReq->graphScratchSize  = PEAK_DETECTION_ENERGY_COMP_GRAPH_SCRATCH_SIZE;
  memReq->graphcontextSize  = PEAK_DETECTION_ENERGY_COMP_GRAPH_CONTEXT_SIZE;
  memReq->graphArgsSize    = sizeof(PEAK_DETECTION_ENERGY_COMP_TI_graphArgs) ;
  return 0;
}

int32_t PEAK_DETECTION_ENERGY_COMP_TI_graphCreate(const BAM_GraphMem * graphMem,
                                                      PEAK_DETECTION_ENERGY_COMP_TI_graphCreateParams * createParams)
{
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    PEAK_DETECTION_ENERGY_COMP_TI_graphArgs * graphArgs = (PEAK_DETECTION_ENERGY_COMP_TI_graphArgs *)graphMem->graphArgs;
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
            {SOURCE_NODE,           BAM_TI_KERNELID_CUSTOM_ENERGY_COMP_DMAREAD_NODE,  NULL},\
            {PEAK_DETECTION_ENERGY_COMP_NODE,     BAM_TI_KERNELID_PEAK_DETECTION_ENERGY_COMP,          NULL},\
            {SINK_NODE,             BAM_TI_KERNELID_CUSTOM_ENERGY_COMP_DMAWRITE_NODE, NULL},\
            {BAM_END_NODE_MARKER,   0,                                        NULL},\
    };

    /* This is done to avoid build errors because of --gcc flag not being enable as per MISRA C */
    NODELIST[SOURCE_NODE].kernelArgs                        = (void *)&graphArgs->dmaReadKernelArgs;
    NODELIST[PEAK_DETECTION_ENERGY_COMP_NODE].kernelArgs       = (void *)&graphArgs->energyCompArgs;

    BAM_EdgeParams EDGELIST[]= {\
            {{SOURCE_NODE, BAM_SOURCE_NODE_PORT1},
                            {PEAK_DETECTION_ENERGY_COMP_NODE, BAM_PEAK_DETECTION_ENERGY_COMPUTE_ANTENNA_DATA_PORT}},\

            {{PEAK_DETECTION_ENERGY_COMP_NODE, BAM_PEAK_DETECTION_ENERGY_COMPUTE_OUTPUT_PORT},
                            {SINK_NODE, BAM_SINK_NODE_PORT1}},\

            {{BAM_END_NODE_MARKER, 0},
                            {BAM_END_NODE_MARKER, 0}},\
    };

    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.graphMemConsumed = 0;
    graphCreateParams.onChipScratchMemConsumed = 0;
    graphCreateParams.extMemConsumed = 0;

    status= BAM_initKernelDB(&gEnergyComp_TI_BAM_kernelDBdef);

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
    graphCreateParams.kernelDB             = &gEnergyComp_TI_BAM_kernelDBdef;
    graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
    graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
    graphCreateParams.graphMem             = graphHandle;
    graphCreateParams.graphMemSize         = PEAK_DETECTION_ENERGY_COMP_GRAPH_OBJ_SIZE;
    graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
    graphCreateParams.onChipScratchMemSize = PEAK_DETECTION_ENERGY_COMP_GRAPH_SCRATCH_SIZE;
    graphCreateParams.extMem               = graphMem->graphcontext;
    graphCreateParams.extMemSize           = PEAK_DETECTION_ENERGY_COMP_GRAPH_CONTEXT_SIZE;
    graphCreateParams.useSmartMemAlloc     = 1U;
    graphCreateParams.optimizeBlockDim     = 0;

    graphArgs->createParams = createParams;

     /*---------------------------------------------------------------*/
    /* Initialize the members related to the  kernels init function  */
    /*---------------------------------------------------------------*/
    graphCreateParams.initKernelsArgsFunc   = &PEAK_DETECTION_ENERGY_COMP_TI_initKernelsArgs;
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
      PRINTF("Peak Detection EnergyComp: Graph construction failed!!! graphMemSize must be >= %d, onChipScratchMemSize >= %d and extMemSize must be >= %d\n",
        graphCreateParams.graphMemConsumed, graphCreateParams.onChipScratchMemConsumed, graphCreateParams.extMemConsumed);
    }
    else if (status== BAM_E_BLOCK_DIM_TOO_BIG)
    {
      PRINTF("Peak Detection EnergyComp: Graph construction failed!!! Decrease the value of blockWidth : or blockHeight :");
    }
    else if (status != BAM_S_SUCCESS)
    {
      PRINTF("Peak Detection EnergyComp: Graph construction failed!!!");
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
static int32_t PEAK_DETECTION_ENERGY_COMP_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams)
{
  int32_t status = BAM_S_SUCCESS;

  PEAK_DETECTION_ENERGY_COMP_TI_graphArgs              *graphArgs          = (PEAK_DETECTION_ENERGY_COMP_TI_graphArgs*)args;
  BAM_DMA_CUSTOM_ENERGY_COMP_READ_initArgs  *dmaReadKernelArgs  = &(graphArgs->dmaReadKernelArgs);
  BAM_PeakDetectionEnergyCompute_Args       *energyCompArgs    = &(graphArgs->energyCompArgs);

  /* Chose these values so as to allocate full 16KB of input buffer which can be allocated
    if we use 1024x4 configuration. Note that each entery is 4 bytes */
  dmaReadKernelArgs->maxNumPoints       = 1024;
  dmaReadKernelArgs->maxNumRowsPerBlock = 4;

  energyCompArgs->maxNumTx                 = graphArgs->createParams->iPeakDetectCreateParams->maxNumTx;
  energyCompArgs->maxNumHorzPtPerAntenna   = 16;
  energyCompArgs->maxNumRows               = 8;
  energyCompArgs->alphaQFormat             = PEAK_DETECTION_TI_ALPHA_Q_FORMAT;

  return (status);

}

/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t PEAK_DETECTION_ENERGY_COMP_TI_execute(
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

int32_t PEAK_DETECTION_ENERGY_COMP_TI_dmaControl(const BAM_GraphMem *graphMem,
                                const PEAK_DETECTION_TI_InArgs *inArgs,
                                uint16_t numRowsPerBlock,
                                uint8_t * ptrToAntennaData,
                                uint8_t * ptrToEnergyBuf)
{
  BAM_DMA_CUSTOM_ENERGY_COMP_ctrlArgs  dmaReadCtrlArgs;

  int32_t status = BAM_S_SUCCESS;

  /* initilize the sub-handles inside the main handle */
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

  dmaReadCtrlArgs.rangeDim                = inArgs->rangeDim;
  dmaReadCtrlArgs.dopplerDim              = inArgs->dopplerDim;
  dmaReadCtrlArgs.numRows                 = inArgs->bufDescription.numVertPoints;
  dmaReadCtrlArgs.numHorzPointPerAnetnna  = inArgs->bufDescription.numHorzPoints[0];
  dmaReadCtrlArgs.numAntennas             = inArgs->bufDescription.numAntennas;
  dmaReadCtrlArgs.numRowsPerBlock         = numRowsPerBlock;
  dmaReadCtrlArgs.ptrToAntennaData        = ptrToAntennaData;
  dmaReadCtrlArgs.ptrToEnergyBuf          = ptrToEnergyBuf;

  status= BAM_controlNode(graphHandle, SOURCE_NODE, &dmaReadCtrlArgs);

  return status;
}


int32_t PEAK_DETECTION_ENERGY_COMP_TI_kernelControl(const  BAM_GraphMem * graphMem,
                                  const PEAK_DETECTION_TI_InArgs *inArgs,
                                  uint16_t numRowsPerBlock,
                                  uint8_t * ptrToLutTableBuf)
{
  int32_t status = BAM_S_SUCCESS;
  BAM_PeakDetectionEnergyCompute_ctrlArgs          energyCompCtrlArgs;
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

  energyCompCtrlArgs.alphaQFormat         = PEAK_DETECTION_TI_ALPHA_Q_FORMAT;
  energyCompCtrlArgs.enableTxDecoding     = inArgs->enableTxDecoding;
  energyCompCtrlArgs.lutQFormat           = PEAK_DETECTION_TI_LUT_Q_FORMAT;
  energyCompCtrlArgs.numHorzPtPerAntenna  = inArgs->bufDescription.numHorzPoints[0];
  energyCompCtrlArgs.numTx                = inArgs->numTx;
  energyCompCtrlArgs.numRx                = inArgs->numRx;
  energyCompCtrlArgs.nuwRows              = numRowsPerBlock;
  energyCompCtrlArgs.offsetBwTx           = inArgs->offsetBwTx;
  energyCompCtrlArgs.offsetBwRx           = inArgs->offsetBwRx;
  energyCompCtrlArgs.txDecodingPtr        = inArgs->txDecodingCoefficients;
  energyCompCtrlArgs.lutTablePtr          = ptrToLutTableBuf;

  status = BAM_controlNode( graphHandle, PEAK_DETECTION_ENERGY_COMP_NODE, &energyCompCtrlArgs);


  return status;
}



