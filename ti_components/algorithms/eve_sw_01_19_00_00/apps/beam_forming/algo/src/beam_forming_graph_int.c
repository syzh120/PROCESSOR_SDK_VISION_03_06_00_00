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
 *  @file      beam_forming_graph.c
 *
 *  @brief     This file defines the functions for graph for Beam Forming applet
 *
 *  @version 0.0 (Jan 2017) : Base version.
 */


/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
/*#pragma RESET_MISRA ("required")*/

#include "xdais_types.h"
#include "ibeam_forming_ti.h"

#include "edma_utils.h"

#include "beam_forming_graph_int.h"

#include "beam_forming_alg_int.h"
#include "bam_dma_custom_beam_forming_node.h"

static int32_t BEAM_FORMING_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams);


#define SOURCE_NODE        (0)
#define BEAM_FORMING_NODE  (1U)
#define SINK_NODE          (2U)


typedef enum _bam_ti_kernelid
{
    BAM_TI_KERNELID_CUSTOM_BEAM_FORMING_DMAREAD_NODE,
    BAM_TI_KERNELID_BEAM_FORMING,
    BAM_TI_KERNELID_CUSTOM_BEAM_FORMING_DMAWRITE_NODE
} BAM_BEAM_FORMING_TI_KernelID;

/**
 * Kernel Database - used for graph construction. If the application is running others graphs
   that share many common kernels with this local database, it may be worthwhile to move this
   local database into the "master" database defined in kernels/bamdb
 */
static BAM_KernelHostDBdef bamBeamFormingKernelHostDB[] =
{
    { &gBAM_TI_dmaCustomBeamFormingNodeReadKernel, &gBAM_TI_dmaCustomBeamFormingNodeReadKernelHelperFunc,
            "ti_dma_read", BAM_TI_KERNELID_CUSTOM_BEAM_FORMING_DMAREAD_NODE},

    { &gBAM_TI_beamFormingKernel, &gBAM_TI_beamFormingHelperFunc,
            "ti_beam_forming", BAM_TI_KERNELID_BEAM_FORMING },

    { &gBAM_TI_dmaCustomBeamFormingNodeWriteKernel, &gBAM_TI_dmaCustomBeamFormingNodeWriteKernelHelperFunc,
            "ti_dma_write", BAM_TI_KERNELID_CUSTOM_BEAM_FORMING_DMAWRITE_NODE},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamBeamFormingKernelExecFuncDB[] =
{
    { &gBAM_TI_dmaCustomBeamFormingNodeReadKernel, &gBAM_TI_dmaCustomBeamFormingNodeReadKernelExecFunc,
            "ti_dma_read", BAM_TI_KERNELID_CUSTOM_BEAM_FORMING_DMAREAD_NODE},

    { &gBAM_TI_beamFormingKernel, &gBAM_TI_beamFormingExecFunc,
              "ti_beam_forming", BAM_TI_KERNELID_BEAM_FORMING},

    { &gBAM_TI_dmaCustomBeamFormingNodeWriteKernel, &gBAM_TI_dmaCustomBeamFormingNodeWriteKernelExecFunc,
            "ti_dma_write", BAM_TI_KERNELID_CUSTOM_BEAM_FORMING_DMAWRITE_NODE},
};


BAM_KernelDBdef gBeamForming_TI_BAM_kernelDBdef =
{
    sizeof(bamBeamFormingKernelExecFuncDB) / sizeof(bamBeamFormingKernelExecFuncDB[0]),
    bamBeamFormingKernelHostDB,
    bamBeamFormingKernelExecFuncDB
};



int32_t BEAM_FORMING_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
  memReq->graphObjSize      = BEAM_FORMING_GRAPH_OBJ_SIZE;
  memReq->graphScratchSize  = BEAM_FORMING_GRAPH_SCRATCH_SIZE;
  memReq->graphcontextSize  = BEAM_FORMING_GRAPH_CONTEXT_SIZE;
  memReq->graphArgsSize    = sizeof(BEAM_FORMING_TI_graphArgs) ;
  return 0;
}

int32_t BEAM_FORMING_TI_graphCreate(const BAM_GraphMem * graphMem,
                                                      BEAM_FORMING_TI_graphCreateParams * createParams)
{
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    BEAM_FORMING_TI_graphArgs * graphArgs = (BEAM_FORMING_TI_graphArgs *)graphMem->graphArgs;
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
            {SOURCE_NODE,           BAM_TI_KERNELID_CUSTOM_BEAM_FORMING_DMAREAD_NODE,  NULL},\
            {BEAM_FORMING_NODE,     BAM_TI_KERNELID_BEAM_FORMING,          NULL},\
            {SINK_NODE,             BAM_TI_KERNELID_CUSTOM_BEAM_FORMING_DMAWRITE_NODE, NULL},\
            {BAM_END_NODE_MARKER,   0,                                        NULL},\
    };

    /* This is done to avoid build errors because of --gcc flag not being enable as per MISRA C */
    NODELIST[SOURCE_NODE].kernelArgs                        = (void *)&graphArgs->dmaReadKernelArgs;
    NODELIST[BEAM_FORMING_NODE].kernelArgs       = (void *)&graphArgs->beamFormingArgs;

    BAM_EdgeParams EDGELIST[]= {\
            {{SOURCE_NODE, BAM_SOURCE_NODE_PORT1},
                            {BEAM_FORMING_NODE, BAM_BEAM_FORMING_ANTENNA_DATA_PORT}},\

            {{SOURCE_NODE, BAM_SOURCE_NODE_PORT2},
                            {BEAM_FORMING_NODE, BAM_BEAM_FORMING_STEERING_MATRIX_PORT}},\

            {{SOURCE_NODE, BAM_SOURCE_NODE_PORT3},
                            {BEAM_FORMING_NODE, BAM_BEAM_FORMING_INFO_PORT}},\

            {{BEAM_FORMING_NODE, BAM_BEAM_FORMING_OUTPUT_PORT},
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

    status= BAM_initKernelDB(&gBeamForming_TI_BAM_kernelDBdef);

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
    graphCreateParams.kernelDB             = &gBeamForming_TI_BAM_kernelDBdef;
    graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
    graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
    graphCreateParams.graphMem             = graphHandle;
    graphCreateParams.graphMemSize         = BEAM_FORMING_GRAPH_OBJ_SIZE;
    graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
    graphCreateParams.onChipScratchMemSize = BEAM_FORMING_GRAPH_SCRATCH_SIZE;
    graphCreateParams.extMem               = graphMem->graphcontext;
    graphCreateParams.extMemSize           = BEAM_FORMING_GRAPH_CONTEXT_SIZE;
    graphCreateParams.useSmartMemAlloc     = 1U;
    graphCreateParams.optimizeBlockDim     = 0;

    graphArgs->createParams = createParams;

     /*---------------------------------------------------------------*/
    /* Initialize the members related to the  kernels init function  */
    /*---------------------------------------------------------------*/
    graphCreateParams.initKernelsArgsFunc   = &BEAM_FORMING_TI_initKernelsArgs;
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
      PRINTF("BeamForming: Graph construction failed!!! graphMemSize must be >= %d, onChipScratchMemSize >= %d and extMemSize must be >= %d\n",
        graphCreateParams.graphMemConsumed, graphCreateParams.onChipScratchMemConsumed, graphCreateParams.extMemConsumed);
    }
    else if (status== BAM_E_BLOCK_DIM_TOO_BIG)
    {
      PRINTF("BeamForming: Graph construction failed!!! Decrease the value of blockWidth : or blockHeight :");
    }
    else if (status != BAM_S_SUCCESS)
    {
      PRINTF("BeamForming: Graph construction failed!!!");
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
static int32_t BEAM_FORMING_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams)
{
  int32_t status = BAM_S_SUCCESS;

  BEAM_FORMING_TI_graphArgs              *graphArgs          = (BEAM_FORMING_TI_graphArgs*)args;
  BAM_DMA_CUSTOM_BEAM_FORMING_READ_initArgs  *dmaReadKernelArgs  = &(graphArgs->dmaReadKernelArgs);
  BAM_BeamForming_Args                       *beamFormingArgs    = &(graphArgs->beamFormingArgs);

  dmaReadKernelArgs->maxNumAngles            = graphArgs->createParams->iBeamFormingCreateParams->maxNumAngle;
  dmaReadKernelArgs->maxNumAntennas          = graphArgs->createParams->iBeamFormingCreateParams->maxNumAntenna;
  dmaReadKernelArgs->maxNumTotalDetection    = graphArgs->createParams->iBeamFormingCreateParams->maxNumDetection;
  dmaReadKernelArgs->maxNumDetectionPerBlock = BEAM_FORMING_MAX_DETECTION_PER_BLOCK;

  beamFormingArgs->maxNumAngle              = graphArgs->createParams->iBeamFormingCreateParams->maxNumAngle;
  beamFormingArgs->maxNumAntenna            = graphArgs->createParams->iBeamFormingCreateParams->maxNumAntenna;
  beamFormingArgs->maxNumTotalDetection     = graphArgs->createParams->iBeamFormingCreateParams->maxNumDetection;
  beamFormingArgs->maxNumDetectionPerBlock  = BEAM_FORMING_MAX_DETECTION_PER_BLOCK;

  return (status);

}

/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t BEAM_FORMING_TI_execute(
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

int32_t BEAM_FORMING_TI_dmaControl(const BAM_GraphMem *graphMem,
                                uint16_t  numAngles,
                                uint16_t  numAntennas,
                                uint16_t  numDetections,
                                uint8_t  *ptrToAntennaData,
                                uint8_t  *ptrToSteeringMatrix,
                                uint16_t  *ptrToAngleDetectionBuf,
                                uint32_t  *enableSMcopyShared)
{
  BAM_DMA_CUSTOM_BEAM_FORMING_READ_ctrlArgs  dmaReadCtrlArgs;

  int32_t status = BAM_S_SUCCESS;

  /* initilize the sub-handles inside the main handle */
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

  dmaReadCtrlArgs.numAngles             = numAngles;
  dmaReadCtrlArgs.numAntennas           = numAntennas;
  dmaReadCtrlArgs.numDetections         = numDetections;
  /* This infornation is shared between DMA node and kernel node using INFO port of DMA  node
and hence it can be different from what we set here*/
  dmaReadCtrlArgs.numDetectionsPerBlock = BEAM_FORMING_MAX_DETECTION_PER_BLOCK;
  dmaReadCtrlArgs.ptrToAntennaData      = ptrToAntennaData;
  dmaReadCtrlArgs.ptrToSteeringMatrix   = ptrToSteeringMatrix;
  dmaReadCtrlArgs.ptrToAngleDetectionBuf = ptrToAngleDetectionBuf;
  dmaReadCtrlArgs.enableSMcopyShared     = enableSMcopyShared;

  status= BAM_controlNode(graphHandle, SOURCE_NODE, &dmaReadCtrlArgs);

  return status;
}


int32_t BEAM_FORMING_TI_kernelControl(const  BAM_GraphMem * graphMem,
                                  uint16_t numAngles,
                                  uint16_t numAntennas,
                                  uint16_t beamFormingScaling,
                                  uint16_t energyScaling,
                                  uint32_t  *enableSMcopyShared
                                  )
{
  int32_t status = BAM_S_SUCCESS;
  BAM_BeamForming_CtrlArgs          beamFormingCtrlArgs;
  BAM_BeamForming_InCtrlArgs        beamFormingInCtrlArgs;
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

  beamFormingCtrlArgs.cmdId = BAM_BEAM_FORMING_CTRL_CMD_ID_SET_PARAMS;
  beamFormingCtrlArgs.ctrlArgs = (void *)&beamFormingInCtrlArgs;


  beamFormingInCtrlArgs.beamFormingScaling = beamFormingScaling;
  beamFormingInCtrlArgs.energyScaling      = energyScaling;
  beamFormingInCtrlArgs.numAngles          = numAngles;
  beamFormingInCtrlArgs.numAntennas        = numAntennas;
  /* This infornation is shared between DMA node and kernel node using INFO port of kernel node
  and hence it can be different from what we set here*/
  beamFormingInCtrlArgs.numDetections      = BEAM_FORMING_MAX_DETECTION_PER_BLOCK;
  beamFormingInCtrlArgs.enableSMcopyShared     = enableSMcopyShared;


  status = BAM_controlNode( graphHandle, BEAM_FORMING_NODE, &beamFormingCtrlArgs);


  return status;
}

int32_t BEAM_FORMING_TI_getWBUFptr(const  BAM_GraphMem * graphMem,
                                  uint16_t ** WBUFptrToAngleBuf,
                                  uint16_t ** WBUFptrToEnergyBuf,
                                  uint16_t ** WBUFpBlockPtr
                                  )
{
  int32_t status = BAM_S_SUCCESS;
  BAM_BeamForming_CtrlArgs          beamFormingCtrlArgs;
  BAM_BeamForming_OutCtrlArgs        beamFormingOutCtrlArgs;
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

  beamFormingCtrlArgs.cmdId = BAM_BEAM_FORMING_CTRL_CMD_ID_GET_WBUF_PTR;
  beamFormingCtrlArgs.ctrlArgs = (void *)&beamFormingOutCtrlArgs;

  status = BAM_controlNode( graphHandle, BEAM_FORMING_NODE, &beamFormingCtrlArgs);

  (*WBUFptrToAngleBuf) = beamFormingOutCtrlArgs.WBUFptrToAngleBuf;
  (*WBUFptrToEnergyBuf) = beamFormingOutCtrlArgs.WBUFptrToEnergyBuf;
  (*WBUFpBlockPtr) = beamFormingOutCtrlArgs.WBUFpBlockPtr;


  return status;
}



