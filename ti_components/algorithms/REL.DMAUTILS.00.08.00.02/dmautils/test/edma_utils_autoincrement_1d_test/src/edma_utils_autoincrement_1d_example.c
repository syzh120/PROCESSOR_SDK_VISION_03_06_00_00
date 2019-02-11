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

/*============================================================================*/
/*============================================================================*/

/**
----------------------------------------------------------------------------
@file    dma_example.c
@brief   Demostrates a simple example of auto increment DMA to allow DSP to
operate a function on internal memory and transfer back the result.
@version 0.0 (Jan 2017) : First version
----------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdint.h>

#ifdef HOST_EMULATION
#include "C6xSimulator.h"
#include <assert.h>
#define restrict
#define _nassert assert
#else
#include "c6x.h"
#endif

#include "edma_utils_context_size.h"
#include "edma_utils.h"
#include "edma_utils_autoincrement_1d.h"

int32_t flipHorizontalKernel(
  uint8_t *inputData,
  uint8_t  *outputData,
  uint16_t width,
  uint16_t height,
  uint16_t inPitch,
  uint16_t outPitch)
{
  int32_t i, j;
  for(j = 0; j < height; j++)
  {
    for(i = 0; i < width; i++)
    {
      outputData[i] =  inputData[width - i - 1] ;
    }
    inputData  += inPitch ;
    outputData += outPitch ;
  }
  return 0;
}

int32_t flipHorizontalKernel_ci(
  uint8_t  *inputData,
  uint8_t  *outputData,
  uint16_t  width,
  uint16_t  height,
  uint16_t  inPitch,
  uint16_t  outPitch)
{
  int32_t i, j, inData_lo, inData_hi;
  int64_t *restrict pOutLtoR, *restrict pInRtoL;
  int64_t inData, outData ;


  for(j = 0; j < height; j++)
  {
    pInRtoL  = (int64_t *) (inputData + (j*inPitch) + width - 8);
    pOutLtoR = (int64_t *) (outputData + (j*outPitch)) ;
    for(i = 0; i < width; i += 8)
    {
      inData  = _amem8(pInRtoL--) ; //7654_3210
      inData_lo = _loll(inData); //3210
      inData_hi = _hill(inData); //7654

      inData_lo = _swap2(inData_lo); //1032
      inData_lo = _swap4(inData_lo); //0123
      inData_hi = _swap2(inData_hi); //5476
      inData_hi = _swap4(inData_hi); //4567

      outData   = _itoll(inData_lo, inData_hi ); //0123_4567
      _amem8(pOutLtoR++)  = outData  ;
    }
  }
  return 0;
}

/*Configure DMA context structures for input and outputs DMA transfers  */
static int32_t biasDmaAutoIncrementRowXferInit(
  uint8_t  *dmaAutoContextInOut,
  uint8_t  *inBufExt,
  uint8_t  *outBufExt,
  uint8_t  *inBufInt[2],
  uint8_t  *outBufInt[2],
  int16_t   width,
  int16_t   height,
  int16_t   blockHeight,
  int16_t   inPitch,
  int16_t   outPitch
  )
{
  int32_t    status = 1;
  EDMA_UTILS_autoIncrement1D_initParam initParam;
  int16_t  pingPongOffset;
  /*--------------------------------------------------------------------------------------------*/
  /* We need two context to transfer from Ext to internal memory for ping and pong buffer       */
  /* The transfer nature is first row from external memory to ping buffer, second row to pong,  */
  /* third to ping and so on.....                                                               */
  /* ping and pong buffer in internal memory are contigous and each is of size width*blkHeight  */
  /* whn DMA is configured for in out, the same context is used for both in and out transfer    */
  /*--------------------------------------------------------------------------------------------*/

  pingPongOffset = (int16_t)((uint32_t)inBufInt[1] - (uint32_t)inBufInt[0]);

  initParam.numInTransfers  = 1;
  initParam.numOutTransfers = 1;
  initParam.transferType    = EDMA_UTILS_TRANSFER_INOUT;

  initParam.transferProp[0].totalLength     = width * height;
  initParam.transferProp[0].numBytes        = width;
  initParam.transferProp[0].extMemPtr       = (uint8_t *)(inBufExt);
  initParam.transferProp[0].extMemIncrement = width;
  initParam.transferProp[0].interMemPtr     = (uint8_t *)(inBufInt[0]);
  initParam.transferProp[0].intMemIncrement = pingPongOffset;
  initParam.transferProp[0].numCircBuf      = 2;
  initParam.transferProp[0].dmaQueNo        = 0;

  initParam.transferProp[1].totalLength     = width * height;
  initParam.transferProp[1].numBytes        = width;
  initParam.transferProp[1].extMemPtr       = (uint8_t *)(outBufExt);
  initParam.transferProp[1].extMemIncrement = width;
  initParam.transferProp[1].interMemPtr     = (uint8_t *)(outBufInt[0]);
  initParam.transferProp[1].intMemIncrement = pingPongOffset;
  initParam.transferProp[1].numCircBuf      = 2;
  initParam.transferProp[1].dmaQueNo        = 1;


  //configure EDMA for ping set both Ext -> Int and Int -> Ext
  EDMA_UTILS_autoIncrement1D_init(dmaAutoContextInOut,&initParam);

  status = EDMA_UTILS_autoIncrement1D_configure(dmaAutoContextInOut , EDMA_UTILS_TRANSFER_INOUT);

  return status;
}

/* This function is main function exposed to user*/
int32_t flipHorizontal(
  uint8_t*   pInput,
  uint8_t*   pOutput,
  uint16_t   width,
  uint16_t   height,
  uint16_t   inPitch,
  uint16_t   outPitch,
  uint8_t*   pIntMmeBase,
  uint32_t   intMemSize,
  uint8_t    useDMA
  )
{
  if(useDMA == 0)
  {
    //call the kernel directly on data in DDR
    flipHorizontalKernel(pInput,
      pOutput,
      width,
      height,
      inPitch,
      outPitch);
  }
  else
  {
    uint8_t bufIdx = 0;
    uint8_t blkHeight = 1 ; //currently set to have 1 row, can be higher as well for larger internal memory
    uint32_t intMemUsedSize = 0, numRowsPending ;

    uint8_t *dmaAutoContextInOut;
    uint8_t *pInBufInt[2]  ;
    uint8_t  *pOutBufInt[2] ;

    //Allocation/Assignment of buffers in internal memory
    dmaAutoContextInOut     =  pIntMmeBase + intMemUsedSize ; intMemUsedSize += EDMA_UTILS_AUTOINCREMENT_1D_CONTEXT_SIZE;
    pInBufInt[0]            =  pIntMmeBase + intMemUsedSize;  intMemUsedSize += (width * blkHeight) ;
    pInBufInt[1]            =  pIntMmeBase + intMemUsedSize;  intMemUsedSize += (width * blkHeight) ;
    pOutBufInt[0]           =  pIntMmeBase + intMemUsedSize;  intMemUsedSize += (width * blkHeight) ;
    pOutBufInt[1]           =  pIntMmeBase + intMemUsedSize;  intMemUsedSize += (width * blkHeight) ;
    if(intMemUsedSize > intMemSize)
    {
      printf("insufficient memory, required is %d vs provided %d\n",intMemUsedSize, intMemSize);
      return -1 ;
    }

    //DMA initilaization
    EDMA_UTILS_globalReset();

    biasDmaAutoIncrementRowXferInit(
      dmaAutoContextInOut,
      pInput,
      pOutput,
      pInBufInt,
      pOutBufInt,
      width,
      height,
      blkHeight,
      inPitch,
      outPitch  );

    //DMA trigger for pipe-up, out transfer is dummy and handled inside DMA utility
    EDMA_UTILS_autoIncrement1D_triggerInChannel(dmaAutoContextInOut);

    //Below 2 extra transfers are dummy and needed by DMA utility
    EDMA_UTILS_autoIncrement1D_triggerOutChannel(dmaAutoContextInOut);

    //Core Block level scheduler loop
    numRowsPending = height ;
    while (numRowsPending)
    {
      //Wait for previous transfer of in
      EDMA_UTILS_autoIncrement1D_waitInChannel(dmaAutoContextInOut);
      //DMA trigger for next in buffer
      EDMA_UTILS_autoIncrement1D_triggerInChannel(dmaAutoContextInOut);

      //Wait for previous transfer out
      EDMA_UTILS_autoIncrement1D_waitOutChannel(dmaAutoContextInOut)  ;

      flipHorizontalKernel(
        pInBufInt[bufIdx],
        pOutBufInt[bufIdx],
        width,
        blkHeight,
        width,
        width);
      EDMA_UTILS_autoIncrement1D_triggerOutChannel(dmaAutoContextInOut) ;

      bufIdx ^= 1;
      numRowsPending -= blkHeight;
    }
    //Need to wait for last out transfer
    EDMA_UTILS_autoIncrement1D_waitOutChannel(dmaAutoContextInOut)  ;
  }

  return 0 ;
}
