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
 *  @file      fft_graph.c
 *
 *  @brief     This file defines the functions for graph for FFT applet
 *
 *  @version 0.0 (Aug 2016) : Base version.
 */


/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
/*#pragma RESET_MISRA ("required")*/

#include "xdais_types.h"
#include "ifft_ti.h"

#include "edma_utils.h"

#include "fft_graph_int.h"

#include "fft_alg_int.h"
#include "bam_dma_custom_fft_horz_node.h"
#include "bam_dma_custom_fft_vert_node.h"

static int32_t FFT_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams);


#define SOURCE_NODE        (0)
#define PREPROCESSING_NODE (1U)
#define FFT_NODE           (2U)
#define SINK_NODE          (3U)


/* Windowing output is fed to FFT and as there is a bit growth of 2 bit in radix-4
FFT we want to limit the output of windowing to 15bit signed number */
#define FFT_TI_SATURATION_LIMIT_15BIT (16384U)
#define FFT_TI_SATURATION_LIMIT_16BIT (32768U)

typedef enum _bam_ti_kernelid
{
    BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT,
    BAM_TI_KERNELID_PREPROCESSING,
    BAM_TI_KERNELID_FFT,
    BAM_TI_KERNELID_FFT_32O,
    BAM_TI_KERNELID_DMAWRITE_CUSTOM_HORZ,
    BAM_TI_KERNELID_DMAWRITE_CUSTOM_VERT,
    BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT
} BAM_FFT_TI_KernelID;

/**
 * Kernel Database - used for graph construction. If the application is running others graphs
   that share many common kernels with this local database, it may be worthwhile to move this
   local database into the "master" database defined in kernels/bamdb
 */
static BAM_KernelHostDBdef bamFftKernelHostDB[] =
{
    { &gBAM_TI_dmaAutoIncrementReadKernel, &gBAM_TI_dmaReadAutoIncrementKernelHelperFunc,
            "ti_dma_read", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},

    { &gBAM_TI_dcoffsetWindowingKernel, &gBAM_TI_dcoffsetWindowingHelperFunc,
            "ti_preprocessing", BAM_TI_KERNELID_PREPROCESSING },

    { &gBAM_TI_Fftnpt16ix16oKernel, &gBAM_TI_Fftnpt16ix16oHelperFunc,
            "ti_fft", BAM_TI_KERNELID_FFT },

    { &gBAM_TI_Fftnpt16ix32oKernel, &gBAM_TI_Fftnpt16ix32oHelperFunc,
            "ti_fft", BAM_TI_KERNELID_FFT_32O },

    { &gBAM_TI_dmaCustomFftHorzNodeWriteKernel, &gBAM_TI_dmaCustomFftHorzNodeWriteKernelHelperFunc,
             "ti_dma_write_custom_horz", BAM_TI_KERNELID_DMAWRITE_CUSTOM_HORZ},

    { &gBAM_TI_dmaCustomFftVertNodeWriteKernel, &gBAM_TI_dmaCustomFftVertNodeWriteKernelHelperFunc,
             "ti_dma_write_custom_vert", BAM_TI_KERNELID_DMAWRITE_CUSTOM_VERT},

    { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelHelperFunc,
            "ti_dma_write", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamFftKernelExecFuncDB[] =
{
    { &gBAM_TI_dmaAutoIncrementReadKernel, &gBAM_TI_dmaReadAutoIncrementKernelExecFunc,
            "ti_dma_read", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},

    { &gBAM_TI_dcoffsetWindowingKernel, &gBAM_TI_dcoffsetWindowingExecFunc,
              "ti_preprocessing", BAM_TI_KERNELID_PREPROCESSING},

    { &gBAM_TI_Fftnpt16ix16oKernel, &gBAM_TI_Fftnpt16ix16oExecFunc,
            "ti_fft", BAM_TI_KERNELID_FFT },

    { &gBAM_TI_Fftnpt16ix32oKernel, &gBAM_TI_Fftnpt16ix32oExecFunc,
            "ti_fft", BAM_TI_KERNELID_FFT_32O },

    { &gBAM_TI_dmaCustomFftHorzNodeWriteKernel, &gBAM_TI_dmaCustomFftHorzNodeWriteKernelExecFunc,
             "ti_dma_write_custom_horz", BAM_TI_KERNELID_DMAWRITE_CUSTOM_HORZ},

    { &gBAM_TI_dmaCustomFftVertNodeWriteKernel, &gBAM_TI_dmaCustomFftVertNodeWriteKernelExecFunc,
             "ti_dma_write_custom_vert", BAM_TI_KERNELID_DMAWRITE_CUSTOM_VERT},

    { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelExecFunc,
            "ti_dma_write", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
};


BAM_KernelDBdef gFft_BAM_TI_kernelDBdef =
{
    sizeof(bamFftKernelExecFuncDB) / sizeof(bamFftKernelExecFuncDB[0]),
    bamFftKernelHostDB,
    bamFftKernelExecFuncDB
};



int32_t FFT_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
  memReq->graphObjSize      = FFT_GRAPH_OBJ_SIZE;
  memReq->graphScratchSize  = FFT_GRAPH_SCRATCH_SIZE;
  memReq->graphcontextSize  = FFT_GRAPH_CONTEXT_SIZE;
  memReq->graphArgsSize    = sizeof(FFT_TI_graphArgs) ;
  return 0;
}

int32_t FFT_TI_graphCreate(const BAM_GraphMem * graphMem,
                                                      FFT_TI_graphCreateParams * createParams)
{
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    FFT_TI_graphArgs * graphArgs = (FFT_TI_graphArgs *)graphMem->graphArgs;
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
            {SOURCE_NODE,           BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT,  NULL},\
            {PREPROCESSING_NODE,      BAM_TI_KERNELID_PREPROCESSING,          NULL},\
            {FFT_NODE,      BAM_TI_KERNELID_FFT,          NULL},\
            {SINK_NODE,             BAM_TI_KERNELID_DMAWRITE_CUSTOM_HORZ, NULL},\
            {BAM_END_NODE_MARKER,   0,                                        NULL},\
    };

    /* This is done to avoid build errors because of --gcc flag not being enable as per MISRA C */
    NODELIST[SOURCE_NODE].kernelArgs                        = (void *)&graphArgs->dmaReadKernelArgs;
    NODELIST[PREPROCESSING_NODE].kernelArgs       = (void *)&graphArgs->dcOffsetWindowingArgs;
    NODELIST[FFT_NODE].kernelArgs       = (void *)&graphArgs->fftArgs.fft16ix16o;

    BAM_EdgeParams EDGELIST[]= {\
            {{SOURCE_NODE, BAM_SOURCE_NODE_PORT1},
                            {PREPROCESSING_NODE, BAM_DCOFFSET_WINDOWING_INPUT_PORT}},\

            {{PREPROCESSING_NODE, BAM_DCOFFSET_WINDOWING_OUTPUT_PORT},
                            {FFT_NODE, BAM_FFT_NPT_16IX16O_INPUT_PORT}},\

            {{FFT_NODE, BAM_FFT_NPT_16IX16O_OUTPUT_PORT},
                            {SINK_NODE, BAM_SINK_NODE_PORT1}},\

            {{BAM_END_NODE_MARKER, 0},
                            {BAM_END_NODE_MARKER, 0}},\
    };

    if ( createParams->iFftCreateParams->fftDirection == FFT_TI_DIRECTION_VERTICAL )
    {
      NODELIST[SINK_NODE].kernelId    = BAM_TI_KERNELID_DMAWRITE_CUSTOM_VERT;
    }

    if ( createParams->iFftCreateParams->outputContainerFormat == FFT_TI_CONTAINER_FORMAT_32BIT)
    {
      NODELIST[FFT_NODE].kernelId    = BAM_TI_KERNELID_FFT_32O;
      NODELIST[FFT_NODE].kernelArgs       = (void *)&graphArgs->fftArgs.fft16ix32o;
    }
    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.graphMemConsumed = 0;
    graphCreateParams.onChipScratchMemConsumed = 0;
    graphCreateParams.extMemConsumed = 0;

    status= BAM_initKernelDB(&gFft_BAM_TI_kernelDBdef);

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
    graphCreateParams.kernelDB             = &gFft_BAM_TI_kernelDBdef;
    graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
    graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
    graphCreateParams.graphMem             = graphHandle;
    graphCreateParams.graphMemSize         = FFT_GRAPH_OBJ_SIZE;
    graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
    graphCreateParams.onChipScratchMemSize = FFT_GRAPH_SCRATCH_SIZE;
    graphCreateParams.extMem               = graphMem->graphcontext;
    graphCreateParams.extMemSize           = FFT_GRAPH_CONTEXT_SIZE;
    graphCreateParams.useSmartMemAlloc     = 1;
    graphCreateParams.optimizeBlockDim     = 0;

    graphArgs->createParams = createParams;

     /*---------------------------------------------------------------*/
    /* Initialize the members related to the  kernels init function  */
    /*---------------------------------------------------------------*/
    graphCreateParams.initKernelsArgsFunc   = &FFT_TI_initKernelsArgs;
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
      PRINTF("FFT: Graph construction failed!!! graphMemSize must be >= %d, onChipScratchMemSize >= %d and extMemSize must be >= %d\n",
        graphCreateParams.graphMemConsumed, graphCreateParams.onChipScratchMemConsumed, graphCreateParams.extMemConsumed);
    }
    else if (status== BAM_E_BLOCK_DIM_TOO_BIG)
    {
      PRINTF("FFT: Graph construction failed!!! Decrease the value of blockWidth : or blockHeight :");
    }
    else if (status != BAM_S_SUCCESS)
    {
      PRINTF("FFT: Graph construction failed!!!");
    }
    else
    {
       /*BAM_printMemRec(graphCreateParams.memRec, graphCreateParams.numMemRec);*/
    }

    return (status);
}

/*-------------------------------------------------------------------------*/
/* Function to assign DMA parameters to EDMA utilitiy                      */
/*-------------------------------------------------------------------------*/
static inline void assignDMAautoIncrementParams(
  EDMA_UTILS_autoIncrement_transferProperties * param,
  uint16_t    roiWidth,
  uint16_t    roiHeight,
  uint16_t    blkWidth,
  uint16_t    blkHeight,
  uint16_t    extBlkIncrementX,
  uint16_t    extBlkIncrementY,
  uint16_t    intBlkIncrementX,
  uint16_t    intBlkIncrementY,
  uint32_t    roiOffset,
  uint32_t    blockOffset,
  uint8_t     *extMemPtr,
  uint16_t    extMemPtrStride,
  uint8_t     *interMemPtr,
  uint16_t    interMemPtrStride,
  uint8_t     dmaQueNo
)
{
  param->roiWidth             = roiWidth;
  param->roiHeight            = roiHeight;
  param->blkWidth             = blkWidth;
  param->blkHeight            = blkHeight;
  param->extBlkIncrementX     = extBlkIncrementX;
  param->extBlkIncrementY     = extBlkIncrementY;
  param->intBlkIncrementX     = intBlkIncrementX;
  param->intBlkIncrementY     = intBlkIncrementY;
  param->roiOffset            = roiOffset;
  param->blkOffset            = blockOffset;
  param->extMemPtr            = extMemPtr;
  param->extMemPtrStride      = extMemPtrStride ;
  param->interMemPtr          = interMemPtr ;
  param->interMemPtrStride    = interMemPtrStride;
  param->dmaQueNo             = dmaQueNo;
}

/*-------------------------------------------------------------------------*/
/* Function to initialize kernel arguments                                 */
/*-------------------------------------------------------------------------*/
static int32_t FFT_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams)
{
  int32_t status = BAM_S_SUCCESS;

  FFT_TI_graphArgs              *graphArgs          = (FFT_TI_graphArgs*)args;
  EDMA_UTILS_autoIncrement_initParam  *dmaReadKernelArgs  = &(graphArgs->dmaReadKernelArgs);
  BAM_DcoffsetWindowing_Args          *dcOffsetWindowingArgs = &(graphArgs->dcOffsetWindowingArgs);
  BAM_Fftnpt16ix16o_Args              *fftArgs = &(graphArgs->fftArgs.fft16ix16o);
  BAM_Fftnpt16ix32o_Args              *fft32Args = &(graphArgs->fftArgs.fft16ix32o);

  /* allocate maximum input block size */
  dmaReadKernelArgs->numInTransfers   = 1U;
  dmaReadKernelArgs->transferType     = EDMA_UTILS_TRANSFER_IN;

  /* Update dma node properties before executing the filter applet*/
  /* First transfer is for Y component of image buffer */
  assignDMAautoIncrementParams(&dmaReadKernelArgs->transferProp[0],
    0,/* roiWidth : This will come during Process call via bufDesc */
    0,/* roiHeight : This will come during Process call via bufDesc */
    (uint16_t)FFT_GRAPH_MAX_NUM_POINTS * sizeof(int32_t),/*blkWidth */
    (uint16_t)FFT_GRAPH_MAX_NUM_LINES,/*blkHeight*/
    (uint16_t)FFT_GRAPH_MAX_NUM_POINTS * sizeof(int32_t),/* extBlkIncrementX */
    (uint16_t)FFT_GRAPH_MAX_NUM_LINES,/* extBlkIncrementY */
    0,/* intBlkIncrementX */
    0,/* intBlkIncrementY */
    0,/* roiOffset */
    0,/* blkOffset */
    NULL,/* extMemPtr : This will come during process call */
    0,/* extMemPtrStride : This will be populated during process call using bufDesc */
    NULL,/* DMA node will be populating this field */
    (uint16_t)FFT_GRAPH_MAX_NUM_POINTS * sizeof(int32_t),/* interMemPtrStride */
    0 /* dmaQueNo */
    );

  dcOffsetWindowingArgs->enableTranspose = 0;
  dcOffsetWindowingArgs->maxNumPoints    = FFT_GRAPH_MAX_NUM_POINTS;

  if (graphArgs->createParams->iFftCreateParams->outputContainerFormat== FFT_TI_CONTAINER_FORMAT_32BIT)
  {
    fft32Args->maxNumLines = FFT_GRAPH_MAX_NUM_LINES;
    fft32Args->maxNumPoints = FFT_GRAPH_MAX_NUM_POINTS;
    fft32Args->enableTranspose = 0;

    if ( graphArgs->createParams->iFftCreateParams->fftDirection == FFT_TI_DIRECTION_VERTICAL)
    {
        dcOffsetWindowingArgs->enableTranspose = 1U;
        fft32Args->enableTranspose = 1U;
    }
  }
  else
  {
    fftArgs->maxNumLines = FFT_GRAPH_MAX_NUM_LINES;
    fftArgs->maxNumPoints = FFT_GRAPH_MAX_NUM_POINTS;
    fftArgs->enableTranspose = 0;

    if ( graphArgs->createParams->iFftCreateParams->fftDirection == FFT_TI_DIRECTION_VERTICAL)
    {
        dcOffsetWindowingArgs->enableTranspose = 1U;
        fftArgs->enableTranspose = 1U;
    }

  }




  return (status);

}

/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t FFT_TI_execute(
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

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define FFT_TI_CEIL(x,y) ((( (x) + (y) - 1U) / (y)) * (y))
/* RESET_MISRA("19.7")  -> Reset rule 19.7  */

int32_t FFT_TI_kernelControl(const  BAM_GraphMem * graphMem,
                                  const FFT_TI_InArgs * inArgs,
                                  uint16_t numActualPoints,
                                  uint16_t numHorzPtPerBlock,
                                  uint16_t numVertPtPerBlock,
                                  int16_t  *windowingCoefficients,
                                  int8_t * twiddleFactorBuf[],
                                  uint8_t * dopplerCorrectionBuf,
                                  uint8_t fftDirection,
                                  uint8_t chunkIdx)
{
  int32_t status = BAM_S_SUCCESS;
  BAM_DcoffsetWindowing_CtrlArgs          dcOffsetWindowingArgs;
  BAM_Fftnpt16ix16o_CtrlArgs              ctrlArgs;
  BAM_Fftnpt16ix16o_InCtrlArgs            fftArgs;
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;
  uint32_t numFFTpoints;
  uint32_t numLines;
  uint32_t numWinPoints;
  uint32_t numWinLines;
  uint32_t i;
  uint32_t winOutputPitch;
  uint8_t enableSignExtension;
  uint32_t overFlowMask;
  uint16_t saturationLimit;
  uint32_t maxNumBits;
  uint32_t numBits;
  uint32_t stageWithoutOverflow;
  uint32_t temp;
  uint32_t numTempPoints;
  uint32_t numStages;
  uint32_t bitGrowthLastStage;
  uint32_t bitGrowth;
  enableSignExtension = (inArgs->numValidBits == (uint8_t)16U) ? 0 : (uint8_t)1;

  if ( fftDirection == FFT_TI_DIRECTION_HORIZONTAL )
  {
    numFFTpoints    = numHorzPtPerBlock;
    numLines        = numVertPtPerBlock;

    numWinPoints = numActualPoints;
    numWinLines  = numVertPtPerBlock;

    winOutputPitch = numFFTpoints * sizeof(int16_t) * 2U;
  }
  else if ( fftDirection == FFT_TI_DIRECTION_VERTICAL )
  {
    /* for vertical direction reverse */
    numFFTpoints  = numVertPtPerBlock;
    numLines      = numHorzPtPerBlock;

    numWinPoints = numHorzPtPerBlock;
    numWinLines  = numActualPoints;

    if ( numFFTpoints < VCOP_SIMD_WIDTH)
    {
     winOutputPitch = ( (VCOP_SIMD_WIDTH) + 1U ) * sizeof(uint32_t);
    }
    else
    {
     winOutputPitch = (((numFFTpoints % 2U)?numFFTpoints: numFFTpoints + 1U)) *   sizeof(uint32_t);
    }
  }
  else
  {
    status = BAM_E_FAIL;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
     goto Exit;
     /* RESET_MISRA("14.4")  -> Reset rule 14.4  */

  }
  /* this reserved entry is to remove the constraint the input to each stage of FFT is bound to 15 bits */
  /* User can switch to this mode if they want to utilize full 16 bit of data range. But this may result */
  /* in functionally incorrect results */
  if (inArgs->reserved == 0x5A716)
  {
    saturationLimit = FFT_TI_SATURATION_LIMIT_16BIT;
    maxNumBits = 16U;
  }
  else
  {
    saturationLimit = FFT_TI_SATURATION_LIMIT_15BIT;
    maxNumBits = 15U;
  }

  dcOffsetWindowingArgs.saturationLimit           = saturationLimit;
  dcOffsetWindowingArgs.enableDcoffset            = inArgs->enableDcOffset;
  dcOffsetWindowingArgs.enableInterferenceZeroOut = inArgs->enableInterferenceZeroOut;
  dcOffsetWindowingArgs.enableWindowing           = inArgs->enableWindowing;
  dcOffsetWindowingArgs.windowingCoefficients     = windowingCoefficients;
  dcOffsetWindowingArgs.scaleFactor               = inArgs->windowingScaleFactor;
  dcOffsetWindowingArgs.numPoints                 = numWinPoints;
  dcOffsetWindowingArgs.numLines                  = numWinLines;
  dcOffsetWindowingArgs.interferenceThreshold     = inArgs->interferenceZeroOutThreshold;
  dcOffsetWindowingArgs.winOutputPitch            = winOutputPitch;
  dcOffsetWindowingArgs.enableSignExtension       = enableSignExtension;
  dcOffsetWindowingArgs.numInBits                 = inArgs->numValidBits;

  fftArgs.saturationLimit         = saturationLimit;
  fftArgs.enable32bitsIntermResults = inArgs->enable32bitsIntermResults;
  fftArgs.enableOverflowDetection = inArgs->enableOverFlowDetection;
  fftArgs.enableDopplerCorrection = inArgs->enableDopplerCorrection;
  fftArgs.dopplerCorrectionBuf = dopplerCorrectionBuf;
  fftArgs.dopplerCorrectionScaling = inArgs->dopplerCorrectionScaleFactor;
  fftArgs.numLines = numLines;
  fftArgs.pitch    = winOutputPitch;
  fftArgs.numPointsZeroPadding = inArgs->numPointsZeroPadding;
  fftArgs.numActualPoints      = ALIGN_SIMD(numActualPoints);
  /* This field is only required if doppler correction is enabled */
  fftArgs.numBlocksPerAntenna  = inArgs->bufDescription.numHorzPoints[chunkIdx] / numLines;
  fftArgs.numValidBits = maxNumBits;


  if ( (numFFTpoints == FFT_TI_NUM_POINTS_1024) && (fftArgs.enable32bitsIntermResults== 0))
  {
    fftArgs.numPoints = BAM_FFT_NPT_16IX16O_NUM_POINTS_1024;
    fftArgs.twiddleFactorBuf = twiddleFactorBuf[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_1024];
  }
  else if ( numFFTpoints == FFT_TI_NUM_POINTS_512 )
  {
    fftArgs.numPoints = BAM_FFT_NPT_16IX16O_NUM_POINTS_512;
    fftArgs.twiddleFactorBuf = twiddleFactorBuf[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_512];
  }
  else if ( numFFTpoints == FFT_TI_NUM_POINTS_128 )
  {
    fftArgs.numPoints = BAM_FFT_NPT_16IX16O_NUM_POINTS_128;
    fftArgs.twiddleFactorBuf = twiddleFactorBuf[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_128];
  }
  else if ( numFFTpoints == FFT_TI_NUM_POINTS_256 )
  {
    fftArgs.numPoints = BAM_FFT_NPT_16IX16O_NUM_POINTS_256;
    fftArgs.twiddleFactorBuf = twiddleFactorBuf[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_256];
  }
  else if ( numFFTpoints == FFT_TI_NUM_POINTS_64 )
  {
    fftArgs.numPoints = BAM_FFT_NPT_16IX16O_NUM_POINTS_64;
    fftArgs.twiddleFactorBuf = twiddleFactorBuf[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_64];
  }
  else
  {
    status = BAM_E_FAIL;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */

  }

  overFlowMask = 0x1FU;
  numBits = inArgs->inDataRange;
  stageWithoutOverflow = 0;
  numStages = 0;
  numTempPoints = numFFTpoints;

  while (numTempPoints != 0 )
  {
    numTempPoints = numTempPoints >> 2;
    numStages++;
    /* If last stage is radix 2 and its vertical direction FFT then we can use full 16 bit of data */
    if ( (numTempPoints == 2U) && ( fftDirection == FFT_TI_DIRECTION_VERTICAL ))
    {
      bitGrowthLastStage = 1U;
    }
    else
    {
      bitGrowthLastStage = 2U;
    }
    if ( numTempPoints == 1U)
    {
      break;
    }
  }

  bitGrowth = 2U;

  for ( i = 0; i < numStages; i++)
  {
    if ( i == (numStages -1U) )
    {
      bitGrowth = bitGrowthLastStage;
    }
    /* each stage there is bit growth of 2 bits except last stage where it could be by 1 */
    if ( (numBits + bitGrowth) <= maxNumBits)
    {
      numBits += bitGrowth;
      stageWithoutOverflow++;
    }
    else
    {
      break;
    }
  }

  /* Last two stages will always happen irrespective of overflow detection is required for it or not*/
  if ( stageWithoutOverflow == (numStages - 1U))
  {
    stageWithoutOverflow++;
  }

  for ( i = 0; i <stageWithoutOverflow; i++)
  {
    temp = (uint32_t)( (uint32_t)0x1U << i );
    overFlowMask = (overFlowMask ^ temp);
  }

  fftArgs.overflowMask = overFlowMask;
  for ( i = 0 ; i < FFT_TI_MAX_NUM_STAGES; i++)
  {
    fftArgs.scaleFactors[i] = inArgs->scaleFactors[i];
  }

  /* In case intermediary results use the full 32-bits, disable scaling at intermediary stages. Instead final stage will perform
        all the scaling in order to prevent overflow since final results are still produced in 16-bits.
    */
  if (inArgs->enable32bitsIntermResults== 1)
  {
    for (i= 0; i < (uint32_t)(numStages - 1u); i++) {
      fftArgs.scaleFactors[(uint32_t)(numStages - 1u)]+= fftArgs.scaleFactors[i];
      fftArgs.scaleFactors[i]= 0;
    }
  }

  status = BAM_controlNode( graphHandle, PREPROCESSING_NODE, &dcOffsetWindowingArgs);
  if ( status == BAM_S_SUCCESS )
  {
    ctrlArgs.cmdId = BAM_FFT_NPT_16IX16O_CTRL_CMD_ID_SET_PARAMS;
    ctrlArgs.ctrlArgs = &fftArgs;
    status = BAM_controlNode( graphHandle, FFT_NODE, &ctrlArgs);
  }
Exit :

  return status;
}


int32_t FFT32O_TI_kernelControl(const  BAM_GraphMem * graphMem,
                                const FFT_TI_InArgs * inArgs,
                                uint16_t numActualPoints,
                                uint16_t numHorzPtPerBlock,
                                uint16_t numVertPtPerBlock,
                                int16_t  *windowingCoefficients,
                                int8_t * twiddleFactorBuf[],
                                uint8_t * dopplerCorrectionBuf,
                                uint8_t fftDirection,
                                uint8_t chunkIdx)
{
    int32_t status = BAM_S_SUCCESS;
    BAM_DcoffsetWindowing_CtrlArgs          dcOffsetWindowingArgs;
    BAM_Fftnpt16ix32o_CtrlArgs              ctrlArgs;
    BAM_Fftnpt16ix32o_InCtrlArgs            fftArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;
    uint32_t numFFTpoints;
    uint32_t numLines;
    uint32_t numWinPoints;
    uint32_t numWinLines;
    uint32_t winOutputPitch;
    uint8_t enableSignExtension;
    uint16_t saturationLimit;
    uint32_t maxNumBits;

    enableSignExtension = (inArgs->numValidBits == (uint8_t)16U) ? 0 : (uint8_t)1;

    if ( fftDirection == FFT_TI_DIRECTION_HORIZONTAL )
    {
        numFFTpoints    = numHorzPtPerBlock;
        numLines        = numVertPtPerBlock;

        numWinPoints = numActualPoints;
        numWinLines  = numVertPtPerBlock;

        winOutputPitch = numFFTpoints * sizeof(int16_t) * 2U;
    }
    else if ( fftDirection == FFT_TI_DIRECTION_VERTICAL )
    {
        /* for vertical direction reverse */
        numFFTpoints  = numVertPtPerBlock;
        numLines      = numHorzPtPerBlock;

        numWinPoints = numHorzPtPerBlock;
        numWinLines  = numActualPoints;

        if ( numFFTpoints < VCOP_SIMD_WIDTH)
        {
            winOutputPitch = ( (VCOP_SIMD_WIDTH) + 1U ) * sizeof(uint32_t);
        }
        else
        {
            winOutputPitch = (((numFFTpoints % 2U)?numFFTpoints: numFFTpoints + 1U)) *   sizeof(uint32_t);
        }
    }
    else
    {
        status = BAM_E_FAIL;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */

    }
    /* this reserved entry is to remove the constraint the input to each stage of FFT is bound to 15 bits */
    /* User can switch to this mode if they want to utilize full 16 bit of data range. But this may result */
    /* in functionally incorrect results */
    if (inArgs->reserved == 0x5A716)
    {
        saturationLimit = FFT_TI_SATURATION_LIMIT_16BIT;
        maxNumBits = 16U;
    }
    else
    {
        saturationLimit = FFT_TI_SATURATION_LIMIT_15BIT;
        maxNumBits = 15U;
    }

    dcOffsetWindowingArgs.saturationLimit           = saturationLimit;
    dcOffsetWindowingArgs.enableDcoffset            = inArgs->enableDcOffset;
    dcOffsetWindowingArgs.enableInterferenceZeroOut = inArgs->enableInterferenceZeroOut;
    dcOffsetWindowingArgs.enableWindowing           = inArgs->enableWindowing;
    dcOffsetWindowingArgs.windowingCoefficients     = windowingCoefficients;
    dcOffsetWindowingArgs.scaleFactor               = inArgs->windowingScaleFactor;
    dcOffsetWindowingArgs.numPoints                 = numWinPoints;
    dcOffsetWindowingArgs.numLines                  = numWinLines;
    dcOffsetWindowingArgs.interferenceThreshold     = inArgs->interferenceZeroOutThreshold;
    dcOffsetWindowingArgs.winOutputPitch            = winOutputPitch;
    dcOffsetWindowingArgs.enableSignExtension       = enableSignExtension;
    dcOffsetWindowingArgs.numInBits                 = inArgs->numValidBits;

    fftArgs.saturationLimit         = saturationLimit;
    fftArgs.enableOverflowDetection = inArgs->enableOverFlowDetection;
    fftArgs.enableDopplerCorrection = inArgs->enableDopplerCorrection;
    fftArgs.dopplerCorrectionBuf = dopplerCorrectionBuf;
    fftArgs.dopplerCorrectionScaling = inArgs->dopplerCorrectionScaleFactor;
    fftArgs.numLines = numLines;
    fftArgs.pitch    = winOutputPitch;
    fftArgs.numPointsZeroPadding = inArgs->numPointsZeroPadding;
    fftArgs.numActualPoints      = ALIGN_SIMD(numActualPoints);
    /* This field is only required if doppler correction is enabled */
    fftArgs.numBlocksPerAntenna  = inArgs->bufDescription.numHorzPoints[chunkIdx] / numLines;
    fftArgs.numValidBits = maxNumBits;


    if ( numFFTpoints == FFT_TI_NUM_POINTS_512 )
    {
        fftArgs.numPoints = BAM_FFT_NPT_16IX32O_NUM_POINTS_512;
        fftArgs.twiddleFactorBuf = twiddleFactorBuf[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_512];
    }
    else if ( numFFTpoints == FFT_TI_NUM_POINTS_128 )
    {
        fftArgs.numPoints = BAM_FFT_NPT_16IX32O_NUM_POINTS_128;
        fftArgs.twiddleFactorBuf = twiddleFactorBuf[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_128];
    }
    else if ( numFFTpoints == FFT_TI_NUM_POINTS_256 )
    {
        fftArgs.numPoints = BAM_FFT_NPT_16IX32O_NUM_POINTS_256;
        fftArgs.twiddleFactorBuf = twiddleFactorBuf[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_256];
    }
    else if ( numFFTpoints == FFT_TI_NUM_POINTS_64 )
    {
        fftArgs.numPoints = BAM_FFT_NPT_16IX32O_NUM_POINTS_64;
        fftArgs.twiddleFactorBuf = twiddleFactorBuf[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_64];
    }
    else
    {
        status = BAM_E_FAIL;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */

    }

    status = BAM_controlNode( graphHandle, PREPROCESSING_NODE, &dcOffsetWindowingArgs);
    if ( status == BAM_S_SUCCESS )
    {
        ctrlArgs.cmdId = BAM_FFT_NPT_16IX32O_CTRL_CMD_ID_SET_PARAMS;
        ctrlArgs.ctrlArgs = &fftArgs;
        status = BAM_controlNode( graphHandle, FFT_NODE, &ctrlArgs);
    }
    Exit :

    return status;
}

int32_t FFT_TI_dmaControl(const BAM_GraphMem *graphMem,
                                const FFT_TI_BufferDescriptor * fftInputDescriptor,
                                FFT_TI_BufferDescriptor * fftOutputDescriptor,
                                uint8_t fftDirection,
                                uint16_t numLinesPerBlock,
                                uint8_t  *inputDataPtr,
                                uint8_t  chunkIdx,
                                uint8_t  *outputDataPtr,
                                uint16_t  numFFTPoints,
                                uint8_t isOutput32bits)
{
    EDMA_UTILS_autoIncrement_updateParams  dmaReadUpdateParams;
    BAM_DMA_CUSTOM_FFT_HORZ_WRITE_ctrlArgs  dmaWriteHorzUpdateParams;
    BAM_DMA_CUSTOM_FFT_VERT_WRITE_ctrlArgs  dmaWriteVertUpdateParams;
    int32_t status = BAM_S_SUCCESS;
    uint32_t numHorzBlocks;
    uint32_t numVertBlocks;
    uint16_t roiWidth;


    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    dmaReadUpdateParams.transferType = EDMA_UTILS_TRANSFER_IN;
    dmaReadUpdateParams.updateMask= (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ALL &
                                (uint32_t)(~(uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_INTERMEMPTR);

    if ( fftDirection == FFT_TI_DIRECTION_HORIZONTAL )
    {
      uint32_t maxNumHorzBlock;
      uint32_t totalNumBlocks;
      uint16_t maxOutBlockWidth;
      uint16_t inputDmaPitch;

      /* This is the number of points after we do zero padding */
      maxOutBlockWidth = numFFTPoints * (uint16_t)sizeof(int32_t);

      if (isOutput32bits== 1u)
      {
        maxOutBlockWidth<<=1u;
      }

      maxNumHorzBlock =  FFT_TI_MAX_PITCH_SUPPORTED/ maxOutBlockWidth;

      totalNumBlocks = (uint32_t)((uint32_t)fftInputDescriptor->numAntennas * (uint32_t)fftInputDescriptor->numVertPoints) / (uint32_t)numLinesPerBlock;

      /* Find numHorzBlocks such that it is multiple of totalNumBlocks but less than or equal to maxNumHorzBlock */
      numHorzBlocks = maxNumHorzBlock;
      while ((totalNumBlocks % numHorzBlocks) != 0 )
      {
        numHorzBlocks--;
      }

      if ( fftInputDescriptor->irregularityFrequency != 0 )
      {
        numHorzBlocks = (fftInputDescriptor->irregularityFrequency + 1U);

        inputDmaPitch = (uint16_t)(((numHorzBlocks - 1U)* fftInputDescriptor->offsetBwAntennas[0]) +
                          fftInputDescriptor->offsetBwAntennas1[0]);

      }
      else
      {
        inputDmaPitch   = (uint16_t)(fftInputDescriptor->offsetBwAntennas[0] * numHorzBlocks);


      }

     roiWidth = (uint16_t)( (numHorzBlocks * fftInputDescriptor->offsetBwAntennas[0]) -
            (fftInputDescriptor->offsetBwAntennas[0] -
            ((uint32_t)fftInputDescriptor->numHorzPoints[0] * sizeof(int32_t))));

      numVertBlocks = totalNumBlocks / numHorzBlocks;

      /* Input data is visualized as set of horizontal block and vertical blocks */
      /* Following DMA is configured for following configuration, here Ak represeent
              Antenna k data */
      /*   */
      /*  A0      A1     A2 ......     Ak
               Ak+1   Ak+1  Ak+2 ......  A2k
               A2k+1 A2k+1 A2k+2 ......  A3k
               ..
               ..
               ..
               A2n+1 Ank+1 Ank+2 ......  Ank
               At time we will be working with a block of A0 Ak+1 A2k+1 ... data
               We can do this because we will write the data also in same
               order so that there is no disruption in the order in which samples are coming */
      assignDMAautoIncrementParams(&dmaReadUpdateParams.updateParams[0],
        (uint16_t)roiWidth,
        (uint16_t)numVertBlocks * numLinesPerBlock,
        (uint16_t)fftInputDescriptor->numHorzPoints[0] * sizeof(int32_t),/*blkWidth */
        (uint16_t)numLinesPerBlock,/*blkHeight*/
        (uint16_t)fftInputDescriptor->offsetBwAntennas[0],/* extBlkIncrementX */
        numLinesPerBlock,/* extBlkIncrementY */
        0,/* intBlkIncrementX */
        0,/* intBlkIncrementY */
        0,/* roiOffset */
        0,/*blockOffset */
        inputDataPtr,/* extMemPtr : This will come during process call */
        inputDmaPitch,/* extMemPtrStride */
        NULL,/*Int Mem Ptr DMA node will be populating this field */
        (uint16_t)fftInputDescriptor->numHorzPoints[0] * sizeof(int32_t),/* interMemPtrStride */
        0 /* dmaQueNo */
        );
    }
    else
    {
      /* Check if offset between antenna is same as number of points per chunk */
      if ( ((uint32_t)fftInputDescriptor->numHorzPoints[chunkIdx] * sizeof(int32_t)) !=
            fftInputDescriptor->offsetBwAntennas[chunkIdx])
      {
        status = BAM_E_FAIL;
        goto Exit;
      }
      assignDMAautoIncrementParams(&dmaReadUpdateParams.updateParams[0],
        fftInputDescriptor->numAntennas * fftInputDescriptor->numHorzPoints[chunkIdx] * sizeof(int32_t),
        fftInputDescriptor->numVertPoints,
        numLinesPerBlock * sizeof(int32_t),/*blkWidth */
        fftInputDescriptor->numVertPoints,/*blkHeight*/
        numLinesPerBlock * sizeof(int32_t),/* extBlkIncrementX */
        0,/* extBlkIncrementY */
        0,/* intBlkIncrementX */
        0,/* intBlkIncrementY */
        0,/* roiOffset */
        0,/*blockOffset */
        inputDataPtr,/* extMemPtr : This will come during process call */
        fftInputDescriptor->numAntennas * fftInputDescriptor->numHorzPoints[chunkIdx] * sizeof(int32_t),/* extMemPtrStride */
        NULL,/*Int Mem Ptr DMA node will be populating this field */
        numLinesPerBlock * sizeof(int32_t),/* interMemPtrStride */
        0 /* dmaQueNo */
        );
    }

    status= BAM_controlNode(graphHandle, SOURCE_NODE, &dmaReadUpdateParams);

    if (status!= BAM_S_SUCCESS) {
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    if ( fftDirection == FFT_TI_DIRECTION_HORIZONTAL )
    {
      dmaWriteHorzUpdateParams.fftBufDescription = fftOutputDescriptor;
      dmaWriteHorzUpdateParams.numHorzBlock      = numHorzBlocks;
      dmaWriteHorzUpdateParams.numVertBlock      = numVertBlocks;
      dmaWriteHorzUpdateParams.numLinesPerBlock  = numLinesPerBlock;
      dmaWriteHorzUpdateParams.ptrToOutputBuf    = outputDataPtr;
      dmaWriteHorzUpdateParams.isOutput32bits    = isOutput32bits;

      status= BAM_controlNode(graphHandle, SINK_NODE, &dmaWriteHorzUpdateParams);
    }
    else if ( fftDirection == FFT_TI_DIRECTION_VERTICAL)
    {
      dmaWriteVertUpdateParams.numHorzPointsPerBlock  = numLinesPerBlock;
      dmaWriteVertUpdateParams.numAntennas            = fftOutputDescriptor->numAntennas;
      dmaWriteVertUpdateParams.numVertPointsPerBlock  = numFFTPoints;
      dmaWriteVertUpdateParams.numTotalVertPoints     = (fftInputDescriptor->numHorzPoints[chunkIdx] * numFFTPoints) / numLinesPerBlock;
      dmaWriteVertUpdateParams.pitch                  = fftOutputDescriptor->pitch[0];
      dmaWriteVertUpdateParams.ptrToOutputBuf         = outputDataPtr;
      dmaWriteVertUpdateParams.isOutput32bits         = isOutput32bits;

      status= BAM_controlNode(graphHandle, SINK_NODE, &dmaWriteVertUpdateParams);

    }
    else
    {
      status = BAM_E_FAIL;
    }

 Exit:
    return status;
}

int32_t FFT_TI_getWBUFptr(const  BAM_GraphMem * graphMem,
                                  uint8_t  ** WBUFPtrScaleFactorOut
                                  )
{
  int32_t status = BAM_S_SUCCESS;
  BAM_Fftnpt16ix16o_CtrlArgs              ctrlArgs;
  BAM_Fftnpt16ix16o_OutCtrlArgs           fftOutArgs;
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

  ctrlArgs.cmdId = BAM_FFT_NPT_16IX16O_CTRL_CMD_ID_GET_WBUF_PTR;
  ctrlArgs.ctrlArgs = (void *)&fftOutArgs;

  status = BAM_controlNode( graphHandle, FFT_NODE, &ctrlArgs);

  (*WBUFPtrScaleFactorOut) = fftOutArgs.WBUFPtrScaleFactorOut;

  return status;
}

int32_t FFT32O_TI_getWBUFptr(const  BAM_GraphMem * graphMem,
                             uint8_t  ** WBUFPtrScaleFactorOut
)
{
    int32_t status = BAM_S_SUCCESS;
    BAM_Fftnpt16ix32o_CtrlArgs              ctrlArgs;
    BAM_Fftnpt16ix32o_OutCtrlArgs           fftOutArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    ctrlArgs.cmdId = BAM_FFT_NPT_16IX32O_CTRL_CMD_ID_GET_WBUF_PTR;
    ctrlArgs.ctrlArgs = (void *)&fftOutArgs;

    status = BAM_controlNode( graphHandle, FFT_NODE, &ctrlArgs);

    (*WBUFPtrScaleFactorOut) = fftOutArgs.WBUFPtrScaleFactorOut;

    return status;
}


