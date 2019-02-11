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


/*==========================================================================*/
/**
*  @file:      peak_detection_tb.c
*
*  @brief:     This file contains test code for Beam Forming applet
*
*
*  @date:      April 2017
*
*  @description:
*    This file contains test code to validate the frame level applet for
*    Peak detection applet. It also checks the output against c reference
*    outputs and profiles the performance and computes the system
*    overheads.
**/
/*==========================================================================*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <vcop.h>
#include <math.h>
#pragma RESET_MISRA ("required")

#include "xdais_types.h"

#include "starterware.h"
#include "alg_osal.h"
#include "eve_profile.h"
#include "ti_mem_manager.h"
#include "ti_file_io.h"

#include "peak_detection_config.h"
#include "ipeak_detection_ti.h"
#include "vcop_peak_detection_cn.h"


#define ENABLE_TRACES     (0U)
#define ENABLE_PROFILE    (1U)
#define COMPARE_REFERENCE (1U)

#define ENABLE_INTERMEDIATE_OUTPUT_COMPARE (1)

#define MAX_CONFIG_LINE_SIZE     (300U)
#define MAX_FILE_NAME_SIZE       (200U)
#define MAX_PARAM_STRING_SIZE    (30U)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

#define PRINT_ERROR_MSG() printf("Error at line: %5d in file: %22s of function: %s\n",__LINE__,__FILE__,__FUNCTION__)
#define ALIGN(x,y)        (((x + y - 1)/y)*y)

#define FIXED_PATTERN 0

#define DMEM_SIZE (16*1024U)
#define OCMC_SIZE (510*1024U)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
/* This will be used for allocation of memory in DMEM*/
uint8_t DMEM_SCRATCH[DMEM_SIZE];

#pragma DATA_SECTION (OCMC_SCRATCH, ".OCMC");
/* This will be used for allocation of memory in OCMC*/
uint8_t OCMC_SCRATCH[OCMC_SIZE];

extern uint64_t gTest_TI_profileSctm[2], gTest_TI_profileTsc;


TIMemObject memObj_DMEM;
TIMemObject memObj_OCMC;

void* TestApp_AlignedMalloc(size_t required_bytes, size_t alignment)
{
    void* p1; // original block
    void** p2; // aligned block
    int offset = alignment - 1 + sizeof(void*);
    if ((p1 = (void*)malloc(required_bytes + offset)) == NULL)
    {
       return NULL;
    }
    p2 = (void**)(((size_t)(p1) + offset) & ~(alignment - 1));
    p2[-1] = p1;
    return p2;
}

void TestApp_AlignedFree(void *p)
{
    free(((void**)p)[-1]);
}


int32_t TestApp_AllocMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
  int32_t i;
  TIMemHandle memHdl_DMEM = &memObj_DMEM;
  TIMemHandle memHdl_OCMC = &memObj_OCMC;

  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].space == IALG_DARAM0) {
      memRec[i].base = TI_GetMemoryChunk(memHdl_DMEM, memRec[i].size, memRec[i].alignment);
    }
    else if (memRec[i].space == IALG_SARAM0)
    {
      memRec[i].base = TI_GetMemoryChunk(memHdl_OCMC, memRec[i].size, memRec[i].alignment);
    }
    else {
      memRec[i].base = (Void *) TestApp_AlignedMalloc( memRec[i].size, memRec[i].alignment);
    }
    if(memRec[i].base == NULL)
    {
      return IALG_EFAIL;
    }
  }
  return IALG_EOK;
}

int32_t TestApp_FreeMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
  int32_t i;
  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].base == NULL)
    {
      return IALG_EFAIL;
    }
    if((memRec[i].space != IALG_DARAM0) && (memRec[i].space != IALG_SARAM0)){
        TestApp_AlignedFree(memRec[i].base);
    }
  }
  return IALG_EOK;
}

typedef struct IM_Fxns
{
  IVISION_Fxns * ivision;

} IM_Fxns;


char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	')||(LinePtr[0] == ','))
  {
    LinePtr++;
  }
  return(LinePtr);
}

void fillDefaultConfig(sPEAK_DETECTION_Config* params)
{
  strcpy((char *)params->testCaseName, "Peak Detection");
  strcpy((char *)params->antennaData, "");
  strcpy((char *)params->rangeDopplerList, "");
  strcpy((char *)params->energyList, "");
  strcpy((char *)params->desc, "");
  params->performanceTestcase = 1;

  params->numTx       = 3;
  params->numRx       = 4;
  params->noiseLen    = 4;
  params->gaurdLen    = 2;
  params->numHorzPtPerAntenna = 8;
  params->rangeDim    = 512;
  params->dopplerDim  = 128;
  params->offsetBwTx  = 4 * params->numHorzPtPerAntenna * sizeof(uint32_t);
  params->offsetBwRx  = 1 * params->numHorzPtPerAntenna * sizeof(uint32_t);
  params->const1      = 15;
  params->const2      = 4;

}

#define PEAK_DETECTION_TB_ALPHA_Q_FORMAT (6U)
#define PEAK_DETECTION_TB_LUT_Q_FORMAT   (8U)
#define PEAK_DETECTION_TB_ENERGY_COMP_NUM_TABLES (8U)

void memcpy2D(
    void        *dstPtr,
    const void  *srcPtr,
    uint16_t     width,
    uint16_t     height,
    int32_t      dstStride,
    int32_t      srcStride
)
{
  uint32_t rowCnt;

  for (rowCnt = 0 ; rowCnt < height; rowCnt++)
  {
      memcpy ((uint8_t *)dstPtr + rowCnt * dstStride, (uint8_t *)srcPtr + rowCnt * srcStride, width);
  }

  return;
}

#define MIN_NUM_HORZ_POINT      (8U)
#define MAX_BLOCK_SIZE (16384U)
#define INCREMENT (2U)

static uint16_t findNumHorzPointPerBlock(uint16_t numHorzPoint,
                                                 uint16_t numVertPoint)
{
  uint16_t numHorzPointPerBlock;
  uint16_t numTotalBytes = 0;

  numHorzPointPerBlock = MIN_NUM_HORZ_POINT;
  numTotalBytes = numVertPoint * numHorzPointPerBlock * sizeof(uint16_t);

  if ( numTotalBytes < MAX_BLOCK_SIZE )
  {
    while ( (numTotalBytes < (MAX_BLOCK_SIZE))&& (numHorzPointPerBlock <= numHorzPoint))
    {
      numHorzPointPerBlock *= INCREMENT;
      numTotalBytes = numVertPoint * numHorzPointPerBlock * sizeof(uint16_t);
    }
    numHorzPointPerBlock = (numHorzPointPerBlock/ INCREMENT);
  }
  else if ( numTotalBytes == MAX_BLOCK_SIZE)
  {
    numHorzPointPerBlock = MIN_NUM_HORZ_POINT;
  }
  else
  {
    numHorzPointPerBlock = 0;
  }


  return numHorzPointPerBlock;
}


/* interimEnergyPointer is an optional parameter to test intermediate energy results */
void peak_detection_cn(IVISION_InBufs * inBufs,
             PEAK_DETECTION_TI_CreateParams * createParams,
             PEAK_DETECTION_TI_InArgs        * inArgs,
             uint16_t *outputBuf,
             uint16_t *outEnergyListBuf,
#if ENABLE_INTERMEDIATE_OUTPUT_COMPARE
             uint16_t *interimEnergyPointer,
#endif
             uint16_t *numDetections)
{
  int16_t   *antennaDataPtr = NULL;
  int16_t   *inputEnergyComp = NULL;
  int16_t   *outputTxDecoding = NULL;
  uint16_t  *interimEnergyPtr = NULL;
  uint32_t  *outputEnergy32 = NULL;
  uint16_t  *lutTableBuf = NULL;
  uint16_t  *lutTableBasePtr = NULL;
  uint16_t  *inEnergyBlockPtr = NULL;
  uint16_t  *cellSum=NULL;
  uint16_t numLUTPoints;
  uint16_t numDetectionPerBlock;
  uint16_t numTotalDetections;
  uint16_t numHorzPointPerBlock;
  uint32_t i,j;
  int16_t  cfarCaThreshold;
  uint32_t Log2Const;
  uint32_t shitAmount;
  uint16_t *  horzIdxOffset;
  uint16_t finalNumDetections;
  uint16_t * interimRangeDopplerListBuf;

  antennaDataPtr = (int16_t *)inBufs->bufDesc[PEAK_DETECTION_TI_BUFDESC_IN_ANTENNA_DATA_BUF]->bufPlanes[0].buf;

  interimEnergyPtr  = (uint16_t *) malloc( inArgs->rangeDim * inArgs->dopplerDim * sizeof(uint16_t));
  outputEnergy32    = (uint32_t *) malloc( inArgs->rangeDim * inArgs->dopplerDim * sizeof(uint32_t));
  outputTxDecoding = (int16_t *)malloc( inArgs->bufDescription.pitch[0] * inArgs->bufDescription.numVertPoints);


  numLUTPoints = (1<<(PEAK_DETECTION_TB_ALPHA_Q_FORMAT));
  lutTableBuf   = (uint16_t *) malloc( 2 *  PEAK_DETECTION_TB_ENERGY_COMP_NUM_TABLES *
                                         (numLUTPoints /2 ) *
                                         sizeof(uint32_t));/* Multiplication by 2 because we
  will be storing LUT table starting from index of 64 for alphaQFormat = 6. This way we can avoid substraction by one during compute and save cycles */


  lutTableBasePtr = &lutTableBuf[(numLUTPoints/2) * 2 * PEAK_DETECTION_TB_ENERGY_COMP_NUM_TABLES];

  /* Generate LUT For binary Scaling */
  for ( i = 0; i < numLUTPoints ; i+=2)
  {
    double one_plus_aplha;

    one_plus_aplha = (double)(i + numLUTPoints) /(double)numLUTPoints    ;
    lutTableBasePtr[8 * i] =  ((double)log(one_plus_aplha) / (double)log(2) ) *
                                              ( 1 << PEAK_DETECTION_TB_LUT_Q_FORMAT);

    one_plus_aplha = (double)(i + 1 + numLUTPoints) /(double)numLUTPoints    ;

    lutTableBasePtr[8 * i + 1] =  ((double)log(one_plus_aplha) / (double)log(2) ) *
                                              ( 1 << PEAK_DETECTION_TB_LUT_Q_FORMAT);
    for ( j = 1; j < 8;j++)
    {
      lutTableBasePtr[8* i + 2*j ] = lutTableBasePtr[8 * i];
      lutTableBasePtr[8 * i + 2*j + 1] = lutTableBasePtr[8 * i + 1];
    }
  }


  inputEnergyComp = antennaDataPtr;

  if (inArgs->enableTxDecoding)
  {
    vcop_tx_decoding_cn(antennaDataPtr,
                        inArgs->txDecodingCoefficients,
                        outputTxDecoding,
                        inArgs->numTx,
                        inArgs->numRx,
                        inArgs->bufDescription.numVertPoints,
                        inArgs->bufDescription.numHorzPoints[0],
                        inArgs->offsetBwTx,
                        inArgs->offsetBwRx,
                        inArgs->bufDescription.pitch[0]);


    inputEnergyComp = outputTxDecoding;
  }

  for ( i = 0; i < inArgs->rangeDim / inArgs->bufDescription.numHorzPoints[0]; i++)
  {
    vcop_peak_detection_energy_across_antenna_cn(inputEnergyComp + i * inArgs->bufDescription.pitch[0] * inArgs->dopplerDim / 2,
                                                 outputEnergy32,
                                                 inArgs->dopplerDim,
                                                 inArgs->bufDescription.numAntennas,
                                                 inArgs->bufDescription.numHorzPoints[0],
                                                 inArgs->bufDescription.pitch[0]);

    vcop_peak_detection_binlog_energy_scaling_cn(outputEnergy32,
                                                 lutTableBuf,
                                                 interimEnergyPtr + i * inArgs->dopplerDim * inArgs->bufDescription.numHorzPoints[0],
                                                 PEAK_DETECTION_TB_LUT_Q_FORMAT,
                                                 PEAK_DETECTION_TB_ALPHA_Q_FORMAT,
                                                 inArgs->dopplerDim,
                                                 inArgs->bufDescription.numHorzPoints[0]);
  }

  if ( createParams->detectionMethod == PEAK_DETECTION_TI_METHOD_CFARCA_DB )
  {
    numHorzPointPerBlock = findNumHorzPointPerBlock(inArgs->dopplerDim,
                                                    inArgs->rangeDim);




    TEST_PRINTF("peak_detection_cn: numHorzPointPerBlock  %d \n",numHorzPointPerBlock );
    Log2Const =  (log((double)inArgs->algoParams.cfarCaDb.constant1) / log(2.0)) * (1 << PEAK_DETECTION_TB_LUT_Q_FORMAT);
    cfarCaThreshold = Log2Const - inArgs->algoParams.cfarCaDb.constant2 * (1 <<PEAK_DETECTION_TB_LUT_Q_FORMAT);


    cellSum           = (uint16_t *) malloc( numHorzPointPerBlock * sizeof(uint16_t) * (inArgs->rangeDim +
                                      2 *(inArgs->algoParams.cfarCaDb.noiseLen + inArgs->algoParams.cfarCaDb.gaurdLen)));

    inEnergyBlockPtr = (uint16_t*)malloc(inArgs->rangeDim * numHorzPointPerBlock * sizeof(uint16_t));

    horzIdxOffset = (uint16_t *) malloc(numHorzPointPerBlock * sizeof(uint16_t));

    memset(horzIdxOffset, 0 , (numHorzPointPerBlock * sizeof(uint16_t)));

    numTotalDetections = 0;
    shitAmount = log((double)inArgs->algoParams.cfarCaDb.noiseLen)/log((double)2.0) + 1U;

    for ( i = 0; i < inArgs->dopplerDim/numHorzPointPerBlock; i++)
    {
      numDetectionPerBlock = 0;
      memcpy2D(inEnergyBlockPtr,
               interimEnergyPtr + i * numHorzPointPerBlock,
               numHorzPointPerBlock * sizeof(uint16_t),
               inArgs->rangeDim,
               numHorzPointPerBlock * sizeof(uint16_t),
               inArgs->dopplerDim * sizeof(uint16_t));

      vcop_peak_detection_cell_sum_cn(inEnergyBlockPtr,
                                      cellSum,
                                      inArgs->algoParams.cfarCaDb.noiseLen,
                                      inArgs->algoParams.cfarCaDb.gaurdLen,
                                      numHorzPointPerBlock,
                                      inArgs->rangeDim,
                                      numHorzPointPerBlock * sizeof(uint16_t),
                                      numHorzPointPerBlock * sizeof(uint16_t),
                                      shitAmount);

      vcop_peak_detection_CFARCA_thresholding_cn(inEnergyBlockPtr,
                                                 cellSum,
                                                 outputBuf + numTotalDetections *  2,
                                                 outEnergyListBuf + numTotalDetections,
                                                 &numDetectionPerBlock,
                                                 horzIdxOffset,
                                                 i * numHorzPointPerBlock,
                                                 inArgs->algoParams.cfarCaDb.noiseLen,
                                                 inArgs->algoParams.cfarCaDb.gaurdLen,
                                                 numHorzPointPerBlock,
                                                 inArgs->rangeDim,
                                                 numHorzPointPerBlock * sizeof(uint16_t),
                                                 numHorzPointPerBlock * sizeof(uint16_t),
                                                 cfarCaThreshold,
                                                 16);

      numTotalDetections += numDetectionPerBlock;
    }

    *numDetections = numTotalDetections;
    TEST_PRINTF("Num Detections First Pass %d \n",numTotalDetections);
    interimRangeDopplerListBuf = (uint16_t *) malloc( numTotalDetections * sizeof(uint16_t) * 2 );

    memcpy(interimRangeDopplerListBuf, outputBuf, ( numTotalDetections * sizeof(uint16_t) * 2 ));

#if ENABLE_INTERMEDIATE_OUTPUT_COMPARE
  {
    int32_t fail = 0;
    uint16_t *outputTarget = (uint16_t *)interimEnergyPointer;

    for ( i = 0; i < inArgs->rangeDim;i++)
    {
      for ( j =0; j < inArgs->dopplerDim;j++)
      {
        if ( (uint16_t)outputTarget[j + i*(inArgs->dopplerDim)] != (uint16_t)interimEnergyPtr[j + i*(inArgs->dopplerDim)])
        {
          TEST_PRINTF("Intermediate Output is not matching at doppler %d range %d \n",j,i);
          fail = 1;
          break;
        }
      }
      if ( fail == 1)
      {
        break;
      }

    }
    if (  fail == 1)
    {
      TEST_PRINTF("FAIL \n");
    }
    else
    {
      TEST_PRINTF("Intermediate Output is matching\n");
    }
  }
#endif

    if ( outputTxDecoding)
    {
     free(outputTxDecoding);
    }

    if (cellSum)
    {
      free(cellSum);
      cellSum = NULL;
    }

    if (outputEnergy32)
    {
      free(outputEnergy32);
    }

    if ( inEnergyBlockPtr )
    {
      free(inEnergyBlockPtr);
    }

    if ( horzIdxOffset )
    {
      free(horzIdxOffset);
    }
  /* Again call the cfar ca only on the detectect objects and run it along the doppler dimension */
    {
      uint8_t  * rangeIndexBuf       = (uint8_t *) malloc (inArgs->rangeDim * sizeof(uint8_t));
      uint16_t  rangeIdx, colIdx;
      uint16_t * energyBufTransposeBuf;
      uint16_t numUniqueDetections;
      uint16_t currDetecetionIdx;
      uint16_t numLinesPerBlock;

      uint32_t exitCondition = 0;

      if ( inArgs->dopplerDim == 512U)
      {
        numLinesPerBlock = 16U;
      }
      else
      {
        numLinesPerBlock = 32U;
      }



      energyBufTransposeBuf = (uint16_t *) malloc (numLinesPerBlock * inArgs->dopplerDim * sizeof(uint16_t));

      memset(rangeIndexBuf, 0, (inArgs->rangeDim * sizeof(uint8_t)));
      horzIdxOffset = (uint16_t *) malloc( numLinesPerBlock * sizeof(uint16_t));

      cellSum           = (uint16_t *) malloc( numLinesPerBlock * sizeof(uint16_t) * (inArgs->dopplerDim +
                                          2 *(inArgs->algoParams.cfarCaDb.noiseLen + inArgs->algoParams.cfarCaDb.gaurdLen)));

      currDetecetionIdx = 0;
      finalNumDetections = 0;
      numDetectionPerBlock = 0;


      while( exitCondition == 0 )
      {
        colIdx = 0;
        for ( i = currDetecetionIdx; i < numTotalDetections; i++)
        {
          rangeIdx = interimRangeDopplerListBuf[2 * i + 1];

          /* Check if this range has already been used */
          if ( rangeIndexBuf[rangeIdx] == 0 )
          {
            for ( j = 0; j < inArgs->dopplerDim; j++)
            {
              energyBufTransposeBuf[colIdx +  j * numLinesPerBlock] = interimEnergyPtr[j + rangeIdx * inArgs->dopplerDim];
            }
            horzIdxOffset[colIdx] = rangeIdx;
            colIdx++;
            rangeIndexBuf[rangeIdx] = 1;
            if ( colIdx == numLinesPerBlock)
            {
              i++;
              break;
            }
          }
        }
        currDetecetionIdx = i;
        numUniqueDetections = ALIGN(colIdx,numLinesPerBlock);
        if ( (numUniqueDetections != colIdx) || (currDetecetionIdx == numTotalDetections) )
        {
          exitCondition = 1;
        }

        if ( colIdx == 0 )
        {
          goto Exit;
        }
        for ( i = 0; i< numUniqueDetections - colIdx; i++)
        {
          for ( j = 0; j < inArgs->dopplerDim; j++)
          {
            energyBufTransposeBuf[i + colIdx + j * numLinesPerBlock] = 0;
          }
        }


        vcop_peak_detection_cell_sum_cn(energyBufTransposeBuf,
                                          cellSum,
                                          inArgs->algoParams.cfarCaDb.noiseLen,
                                          inArgs->algoParams.cfarCaDb.gaurdLen,
                                          numLinesPerBlock,
                                          inArgs->dopplerDim,
                                          numLinesPerBlock * sizeof(uint16_t),
                                          numLinesPerBlock * sizeof(uint16_t),
                                          shitAmount);

        vcop_peak_detection_CFARCA_thresholding_cn(energyBufTransposeBuf,
                                                   cellSum,
                                                   outputBuf + finalNumDetections *  2,
                                                   outEnergyListBuf + finalNumDetections,
                                                   &numDetectionPerBlock,
                                                   horzIdxOffset,
                                                   0,
                                                   inArgs->algoParams.cfarCaDb.noiseLen,
                                                   inArgs->algoParams.cfarCaDb.gaurdLen,
                                                   numLinesPerBlock,
                                                   inArgs->dopplerDim,
                                                   numLinesPerBlock * sizeof(uint16_t),
                                                   numLinesPerBlock * sizeof(uint16_t),
                                                   cfarCaThreshold,
                                                   0);
        finalNumDetections += numDetectionPerBlock;
      }
  Exit:
      *numDetections = finalNumDetections;

      if (energyBufTransposeBuf)
      {
        free(energyBufTransposeBuf);
      }

      if (rangeIndexBuf)
      {
        free(rangeIndexBuf);
      }
    }

    if (cellSum)
    {
      free(cellSum);
    }
  }
  else
  {
    memcpy(outputBuf,interimEnergyPtr, inArgs->rangeDim * inArgs->dopplerDim * sizeof(uint16_t));
  }
  if (interimEnergyPtr)
  {
    free(interimEnergyPtr);
  }



}

int32_t peakDetectionTest(sPEAK_DETECTION_Config* params)
{
  int16_t     *antennaData = NULL;
  int16_t      * txDecodingCoefficients = NULL;
  int32_t      i, j,  numMemRec, status, fail = 0;
  TI_FILE     *fp;
  IALG_MemRec *memRec;
  uint16_t    *outputBuf = NULL;
  uint16_t    *outEnergyListBuf = NULL;

  uint16_t    *outputBufRef = NULL;
  uint16_t    *outEnergyListBufRef = NULL;
  uint16_t     numDetectionsRef;
  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *    handle;

  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  PEAK_DETECTION_TI_CreateParams   createParams;

  PEAK_DETECTION_TI_InArgs  inArgs;
  PEAK_DETECTION_TI_OutArgs outArgs;

  IVISION_InBufs        inBufs;
  IVISION_OutBufs       outBufs;

  IVISION_BufDesc    inBufDesc[PEAK_DETECTION_TI_BUFDESC_IN_TOTAL];
  IVISION_BufDesc   *inBufDescList[PEAK_DETECTION_TI_BUFDESC_IN_TOTAL];
  IVISION_BufDesc    outBufDesc[PEAK_DETECTION_TI_BUFDESC_OUT_TOTAL];
  IVISION_BufDesc   *outBufDescList[PEAK_DETECTION_TI_BUFDESC_OUT_TOTAL];

  outArgs.iVisionOutArgs.size = sizeof(PEAK_DETECTION_TI_OutArgs);

  inArgs.iVisionInArgs.size   = sizeof(PEAK_DETECTION_TI_InArgs);
  inArgs.iVisionInArgs.subFrameInfo = 0;

  /*--------------------------------------------------------------------------*/
  /*Create memory handle for ARP32 DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;

  uint8_t *pOcmc;
  TIMemHandle memHdl_OCMC;

  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);

  pOcmc = (uint8_t *)&OCMC_SCRATCH;
  memHdl_OCMC = &memObj_OCMC;
  TI_CreateMemoryHandle(memHdl_OCMC, pOcmc, OCMC_SIZE);

#if (ENABLE_PROFILE)
  profiler_init();
#endif

  /*-----------------------------------------------------------------
  Set buffer descriptor pointers array base
  -----------------------------------------------------------------*/
  inBufs.bufDesc  = inBufDescList;
  outBufs.bufDesc = outBufDescList;

  inBufs.numBufs  = PEAK_DETECTION_TI_BUFDESC_IN_TOTAL;
  outBufs.numBufs = PEAK_DETECTION_TI_BUFDESC_OUT_TOTAL;

  for(i = 0 ; i < PEAK_DETECTION_TI_BUFDESC_IN_TOTAL ;i++)
  {
    inBufDescList[i]  = &inBufDesc[i];
  }

  for(i = 0 ; i < PEAK_DETECTION_TI_BUFDESC_OUT_TOTAL ;i++)
  {
    outBufDescList[i] = &outBufDesc[i];
  }

  /*-----------------------------------------------------------------
  Set algorithm parameters
  -----------------------------------------------------------------*/
  createParams.maxRangeDimension    = params->rangeDim;
  createParams.maxDopplerDimension  = params->dopplerDim;
  createParams.maxNumAntenna        = params->numTx * params->numRx;
  createParams.maxNumTx             = params->numTx;
  createParams.enableAntennaDataOut = params->enableAntennaDataOut;
  createParams.detectionMethod      = params->detectionMethod;


  createParams.algoCreateParams.cfarCaDb.maxNoiseLen         = params->noiseLen;
  createParams.algoCreateParams.cfarCaDb.maxGaurdLen         = params->gaurdLen;

  createParams.visionParams.algParams.size = sizeof(PEAK_DETECTION_TI_CreateParams);
  createParams.visionParams.cacheWriteBack = NULL;

#if (ENABLE_PROFILE)
  profiler_initStack(profiler_getSP());
  profiler_start();
#endif

  /*-----------------------------------------------------------------
  Query algorithm memory requirement using standard IALG interface
  -----------------------------------------------------------------*/
  numMemRec = PEAK_DETECTION_TI_VISION_FXNS.ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec * sizeof(IALG_MemRec));

  status = PEAK_DETECTION_TI_VISION_FXNS.ialg.algAlloc((IALG_Params *)(&createParams), NULL, memRec);

  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

#if ENABLE_TRACES
  printf("Peak Detection Create Done\n");
#endif

  /*-----------------------------------------------------------------
  Allocate memory for all the mem records
  Application has to implement the below function
  Refer the example implementation below in this file
  -----------------------------------------------------------------*/
  status = TestApp_AllocMemRecords(memRec, numMemRec);
  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  /*-----------------------------------------------------------------
  Intialize the algorithm instance with the alocated memory
  and user create parameters
  -----------------------------------------------------------------*/
  status = PEAK_DETECTION_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
                                                   memRec,
                                                   NULL,
                                                   (IALG_Params *)(&createParams));

#if (ENABLE_PROFILE)
  profiler_end_print(0);
/*  profile_create_tsc = gTest_TI_profileTsc;  */
#endif

  handle = (IM_Fxns *) memRec[0].base;

  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

#if ENABLE_TRACES
  printf("Peak Detection Applet Init Done\n");
#endif


  /*-----------------------------------------------------------------
  Set buffer descriptors
  -----------------------------------------------------------------*/
  /*-----------------------------------------------------------------
  Input buffer
  -----------------------------------------------------------------*/

  inBufDesc[PEAK_DETECTION_TI_BUFDESC_IN_ANTENNA_DATA_BUF].numPlanes = 1;
  inBufDesc[PEAK_DETECTION_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].frameROI.topLeft.x = 0;
  inBufDesc[PEAK_DETECTION_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].frameROI.topLeft.y = 0;
  inBufDesc[PEAK_DETECTION_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].frameROI.width =
            params->numHorzPtPerAntenna * params->numTx * params->numRx * sizeof(int16_t) * 2U;
  inBufDesc[PEAK_DETECTION_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].frameROI.height =
            params->dopplerDim * params->rangeDim / params->numHorzPtPerAntenna;
  inBufDesc[PEAK_DETECTION_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].width  =
            inBufDesc[PEAK_DETECTION_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].frameROI.width;
  inBufDesc[PEAK_DETECTION_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].height =
            inBufDesc[PEAK_DETECTION_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].frameROI.height;
  inBufDesc[PEAK_DETECTION_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].buf =
       TestApp_AlignedMalloc(inBufDesc[PEAK_DETECTION_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].width *
              inBufDesc[PEAK_DETECTION_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].height, 128);

  txDecodingCoefficients = (int16_t *)malloc(params->numTx * params->numTx * sizeof(int16_t));


  /*-----------------------------------------------------------------
  Output buffer
  -----------------------------------------------------------------*/
  outBufDesc[PEAK_DETECTION_TI_BUFDESC_OUT_BUFFER].bufPlanes[0].buf = TestApp_AlignedMalloc(params->rangeDim *
                                                                                                    params->dopplerDim *
                                                                                                    sizeof(uint32_t),128);

  outBufDesc[PEAK_DETECTION_TI_BUFDESC_OUT_ENERGY_BUFFER].bufPlanes[0].buf = TestApp_AlignedMalloc(params->rangeDim *
                                                                                                params->dopplerDim *
                                                                                                sizeof(uint16_t),128);

  outBufDesc[PEAK_DETECTION_TI_BUFDESC_OUT_ANTENNA_DATA].bufPlanes[0].buf = TestApp_AlignedMalloc(params->rangeDim *
                                                                                          params->dopplerDim *
                                                                                          params->numTx *
                                                                                          params->numRx *
                                                                                          sizeof(uint32_t),128);

  outputBuf = (uint16_t*)outBufDesc[PEAK_DETECTION_TI_BUFDESC_OUT_BUFFER].bufPlanes[0].buf ;
  outEnergyListBuf       = (uint16_t*)outBufDesc[PEAK_DETECTION_TI_BUFDESC_OUT_ENERGY_BUFFER].bufPlanes[0].buf ;

  outputBufRef = (uint16_t*)malloc(params->rangeDim *
                                    params->dopplerDim *
                                    sizeof(uint16_t) * 2);
  outEnergyListBufRef       = (uint16_t*)malloc(params->rangeDim *
                                    params->dopplerDim *
                                    sizeof(uint16_t));

  /*-----------------------------------------------------------------
  Allocate Reference Buffers
  -----------------------------------------------------------------*/

  antennaData    = ( int16_t *)inBufDesc[PEAK_DETECTION_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].buf;

  /*-----------------------------------------------------------------
        Open Input File. If non existant, fill input with data.
        -----------------------------------------------------------------*/
  fp = FOPEN((char *)params->antennaData, "rb");
  if(fp == NULL)
  {
    srand(params->randSeed);

    for(j = 0; j < params->rangeDim * params->dopplerDim / params->numHorzPtPerAntenna; j++)
    {
      for(i = 0; i < (params->numTx * params->numRx * params->numHorzPtPerAntenna); i++)
      {
#if FIXED_PATTERN
        antennaData[ 2 * (i + j * (params->numTx * params->numRx * params->numHorzPtPerAntenna))] = i + j * 12;//rand();
        antennaData[ 2 * (i + j * (params->numTx * params->numRx * params->numHorzPtPerAntenna)) + 1] = i + j * 12;//rand();
#else
        antennaData[ 2 * (i + j * (params->numTx * params->numRx * params->numHorzPtPerAntenna))] = (rand()%256);
        antennaData[ 2 * (i + j * (params->numTx * params->numRx * params->numHorzPtPerAntenna)) + 1] = (rand()%256);
#endif

      }
    }
  }
  else
  {
      FREAD(antennaData, (params->numTx * params->numRx * params->numHorzPtPerAntenna)*
              (params->rangeDim * params->dopplerDim / params->numHorzPtPerAntenna) *
              sizeof(int16_t) * 2, 1, fp);
      FCLOSE(fp);
      printf("FILE READ Complete \n");
  }


  memcpy(txDecodingCoefficients,params->txDecodingCoeff, params->numTx*params->numTx*sizeof(int16_t));

  inArgs.numTx              = params->numTx;
  inArgs.numRx              = params->numRx;
  inArgs.enableTxDecoding   = params->enableTxDecoding;
  inArgs.rangeDim           = params->rangeDim;
  inArgs.dopplerDim         = params->dopplerDim;
  inArgs.offsetBwTx         = params->offsetBwTx;
  inArgs.offsetBwRx         = params->offsetBwRx;
  inArgs.txDecodingCoefficients = txDecodingCoefficients;
  inArgs.algoParams.cfarCaDb.noiseLen  = params->noiseLen;
  inArgs.algoParams.cfarCaDb.gaurdLen  = params->gaurdLen;
  inArgs.algoParams.cfarCaDb.constant1 = params->const1;
  inArgs.algoParams.cfarCaDb.constant2 = params->const2;

  inArgs.bufDescription.numAntennas = params->numTx * params->numRx;
  inArgs.bufDescription.numChunks   = 1;
  inArgs.bufDescription.numHorzPoints[0]    = params->numHorzPtPerAntenna;
  inArgs.bufDescription.numVertPoints       = params->rangeDim * params->dopplerDim / params->numHorzPtPerAntenna;
  inArgs.bufDescription.offsetBwAntennas[0] = params->numHorzPtPerAntenna * sizeof(int16_t) * 2;
  inArgs.bufDescription.pitch[0]            = params->numTx * params->numRx * params->numHorzPtPerAntenna * sizeof(int16_t) * 2;


  /*-----------------------------------------------------------------
        Fill Structuring Element buffer.
        -----------------------------------------------------------------*/

  /*-----------------------------------------------------------------
        Process.
        -----------------------------------------------------------------*/
#if ENABLE_TRACES
  printf("Processing start \n");
#endif
#if (ENABLE_PROFILE)
  profiler_start();
#endif

  status = handle->ivision->algProcess((IVISION_Handle)handle,
                                        &inBufs,
                                        &outBufs,
                                       (IVISION_InArgs *)&inArgs,
                                       (IVISION_OutArgs *)&outArgs);

#if (ENABLE_PROFILE)
  profiler_end_print(1);

#endif

  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }
#if ENABLE_TRACES
  printf("Processing End\n");
#endif


#if COMPARE_REFERENCE
  /*---------------------------------------------------------------------*/
  /*  Call the natural C implementation for  Peak Detection funcs.  */
  /*---------------------------------------------------------------------*/

  peak_detection_cn(&inBufs,
         &createParams,
         &inArgs,
         outputBufRef,
         outEnergyListBufRef,
 #if ENABLE_INTERMEDIATE_OUTPUT_COMPARE
        (uint16_t *)memRec[17].base,/*memRec[17].base this is just for matchign intermediate outptu */
 #endif
         &numDetectionsRef);

  fail = 0;

  if ( createParams.detectionMethod == PEAK_DETECTION_TI_METHOD_CFARCA_DB )
  {
    if ( numDetectionsRef != outArgs.numDetections)
    {
      fail = 1;
      TEST_PRINTF("Number of detections are not matching target %d, reference %d \n",outArgs.numDetections, numDetectionsRef);
    }

    if ( fail == 0 )
    {
      for ( i = 0; i < numDetectionsRef; i++)
      {
        if ( (outputBuf[2*i] != outputBufRef[2*i]) ||
              (outputBuf[2*i + 1] != outputBufRef[2*i + 1]))
        {
          fail = 1;
          TEST_PRINTF("Range Doppler coordinate not matching at detection %d \n", i);
          TEST_PRINTF("Range Target %d Reference %d\n", outputBuf[2*i], outputBufRef[2*i]);
          TEST_PRINTF("Doppler Target %d Reference %d\n", outputBuf[2*i + 1], outputBufRef[2*i + 1]);
          break;
        }

        if ( (outEnergyListBuf[i] != outEnergyListBufRef[i]))
        {
          fail = 1;
          TEST_PRINTF("Energy is not matching at detection %d \n", i);
          TEST_PRINTF("Energy Target %d Reference %d\n", outEnergyListBuf[i], outEnergyListBufRef[i]);
          break;
        }
      }
    }

    TEST_PRINTF("peakDetectionTest : Number of detections  %d \n",outArgs.numDetections);
  }
  else if ( createParams.detectionMethod == PEAK_DETECTION_TI_METHOD_ENERGY_OUT)
  {
    for ( j = 0 ; j < inArgs.dopplerDim; j++)
    {
      for ( i = 0 ; i < inArgs.rangeDim; i++)
      {
        if ( outputBuf[i + j * inArgs.rangeDim] != outputBufRef[i + j * inArgs.rangeDim])
        {
          fail = 1;
          TEST_PRINTF("Output energy is matching target %d reference %d \n", outputBuf[i + j * inArgs.rangeDim],outputBufRef[i + j * inArgs.rangeDim] );
          break;
        }
      }
      if ( fail == 1)
      {
        break;
      }
    }

  }
#endif



  profiler_printStatus(fail);

  fflush(stdout);

EXIT_LOOP:

  status = handle->ivision->ialg.algFree((IALG_Handle)(handle), memRec);

  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
  }

  /* Here Free memory for all the mem records */
  status = TestApp_FreeMemRecords(memRec, numMemRec);
  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
  }

  if ( antennaData != NULL ) {
    TestApp_AlignedFree(antennaData);
  }

  if ( memRec != NULL ) {
    free(memRec);
  }

  if ( outputBufRef != NULL)
  {
    free(outputBufRef);
  }

  if ( outEnergyListBufRef != NULL)
  {
    free(outEnergyListBufRef);
  }


#if !(VCOP_HOST_EMULATION)
  profiler_getStackDepth();
#endif

  return status;
}


int main(int argc, char *argv[])
{
  TI_FILE *fp;
  char     configFile[FILE_NAME_SIZE] = {0};
  char     configLine[MAX_CONFIG_LINE_SIZE];
  char     configParam[MAX_PARAM_STRING_SIZE];
  int8_t  *LinePtr;
  int32_t  lineNum = -1, config_cmd, status = 0;

  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,CONFIG_LIST_FILE_NAME);
  }

  fp = FOPEN((const char *)configFile , "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s \n",CONFIG_LIST_FILE_NAME);
    return(status);
  }

  report_printAppletInfo((int8_t *)"PEAK_DETECTION_TI_VISION");

  while ( 1 )
  {
    memset(configLine, 0, MAX_CONFIG_LINE_SIZE);
    status = (int)FGETS(configLine,MAX_CONFIG_LINE_SIZE,fp);
    LinePtr = (int8_t *)configLine;
    if ((status == EOF) || (status == 0))
    {
      break;
    }
    status = 0;
    lineNum++;
    sscanf((const char *)LinePtr, "%d",&config_cmd);
    sscanf((const char *)LinePtr, "%s",configParam);

    if(config_cmd == 0)
    {
      printf("End of config list found !\n");
      break;
    }
    else if(config_cmd == 2)
    {
      continue;
    }
    else if(config_cmd == 1)
    {
      LinePtr = (int8_t *)moveToNextElement(configParam,(char *)LinePtr);
      status  = sscanf((const char *)LinePtr, "%s",configFile);

      printf("\n Processing config file %s !\n", configFile);

      fillDefaultConfig(&gConfig_peak_detection);

      status = readparamfile(configFile, &gsTokenMap_peak_detection[0]);
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }

      profiler_testCaseInfo((int8_t *)gConfig_peak_detection.testCaseName, (int8_t *)gConfig_peak_detection.desc,
                            gConfig_peak_detection.performanceTestcase);
      printparams(&gsTokenMap_peak_detection[0], (int32_t)MAX_ITEMS_TO_PARSE, (uint32_t)(&gConfig_peak_detection),
                            sizeof(sPEAK_DETECTION_Config));

      /* Validate the applet */
      status = peakDetectionTest(&gConfig_peak_detection);
      if(status == -1)
      {
        return status;
      }
    }
    else
    {
      printf(" Unsupported config list command parameter at line num : %4d !\n", lineNum);
    }

  }

  FCLOSE(fp);

#if VCOP_HOST_EMULATION
    printf("Press any key to continue ...\n");
    scanf("%c", configFile);
#endif

  return status;
}

