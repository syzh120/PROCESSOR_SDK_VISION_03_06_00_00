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
 @file    test.c
 @brief   To test DMA ping pong usage example
 ----------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "edma_utils_autoincrement_example.h"
#include "tsc.h"
#ifdef HOST_EMULATION
  #include "C6xSimulator.h"
  #include <assert.h>
  #define restrict
  #define _nassert assert
#else
  #include "cache.h"
  #include "c6x.h"
#endif

#if (CORE_C6XX) && (!HOST_EMULATION)

long long _TSC_read();

void SetMAR()
{
  uint32_t i ;
  uint32_t* MAR = (uint32_t*)0x01848000 ;
  /*
  * MAR Reg         Address range             Cache behavior
  * MAR 128 - 135   8000 0000h : 87FF FFFFh   Prefetch + cachable
  */
  for(i = 128 ;i <= 133 ; i++)
  {
    MAR[i] = 0x3;
  }
  return ;
}

void InitCache()
{
  /*-----------------------------------------------------------------------*/
  /* 7-> full,6 -> 1024KB,5 -> 512KB,4-> 256KB,3 -> 128KB,2-> 64KB,0-->0   */
  /*-----------------------------------------------------------------------*/
  *L2CFG  = 3;

  /*-----------------------------------------------------------------------*/
  /* Full L1P is configured as 32KB of cache                               */
  /*-----------------------------------------------------------------------*/
  *L1PCFG = 4;

  /*-----------------------------------------------------------------------*/
  /* 1 -> 4 KB, 2-> 8KB, 3 ->16 KB, 4 -> 32KB as cache                     */
  /*-----------------------------------------------------------------------*/
  *L1DCFG = 4;

  SetMAR() ;
}
#endif //!HOST_EMULATION

/* Dummy functions  */
void edma3OsSemGive ()
{
}

/* Dummy functions  */
void edma3OsSemTake ()
{
}

#define L2SRAM_SIZE (128*1024)
#pragma DATA_SECTION (L2SRAM, ".L2SramSect");
uint8_t L2SRAM[L2SRAM_SIZE];

int32_t main(int32_t argc, char *argv[])
{
  int32_t i, j ;
  uint8_t *input     = NULL;
  uint8_t  *output    = NULL;
  uint8_t  *refOut    = NULL;

  uint8_t*    pIntMmeBase  = L2SRAM;
  uint32_t   intMemSize   = L2SRAM_SIZE;
  uint8_t    useDMA      ;
  uint8_t status = 1;

  /* Basic input parameters are hardcoded here.  */
  uint16_t   width    = 1024;
  uint16_t   height   = 512;
  uint16_t   inPitch  = 1056;
  uint16_t   outPitch = 1088;

#if (!HOST_EMULATION) && (CORE_C6XX)
  uint64_t tscStart,  tscEnd;
  /*---------------------------------------------------------------------------
  Initialization of cache. Currently 128KB of L2 , 16 KB
  of L1, and full L1P is configured as cache.
  ----------------------------------------------------------------------------*/
  InitCache();

  /* Enable clock for profiling  */
  _TSC_enable();
#endif

  printf("\nDMA example usage on C66x DSP with Horizontal Flip function\n");
  printf("\nwidth = %d\theight = %d\n",width,height);

  /* Buffer allocations for input, output and reference output  */
  input     = (uint8_t *) malloc(inPitch  * height * sizeof(uint8_t));
  output    = (uint8_t *)  malloc(outPitch * height * sizeof(uint8_t));
  refOut    = (uint8_t *)  malloc(outPitch * height * sizeof(uint8_t));
  /* Random pattern generator for input  */
  for ( j = 0 ; j < height; j++)
  {
    for (i = 0; i < width; i++)
    {
      input[i + j * inPitch] = rand() % 255;
    }
  }

  //DMA based function call
  useDMA = 1;

#if (!HOST_EMULATION) && (CORE_C6XX)
  tscStart = _TSC_read();
#endif
  flipHorizontal(
    input,
    output,
    width,
    height,
    inPitch,
    outPitch,
    pIntMmeBase,
    intMemSize,
    useDMA );

#if (!HOST_EMULATION) && (CORE_C6XX)
  tscEnd = _TSC_read();
  printf("Cycles - Using DMA = %llu\n",(tscEnd-tscStart));
#endif

  useDMA = 0;
#if (!HOST_EMULATION) && (CORE_C6XX)
  tscStart = _TSC_read();
#endif
  flipHorizontal(
    input,
    refOut,
    width,
    height,
    inPitch,
    outPitch,
    pIntMmeBase,
    intMemSize,
    useDMA );
#if (!HOST_EMULATION) && (CORE_C6XX)
  tscEnd = _TSC_read();
  printf("Cycles - Without using DMA = %llu\n",(tscEnd-tscStart));
#endif

  /*Compare output with reference output */
  for(j = 0; j < height; j++)
  {
    for(i = 0; i < width; i++)
    {
      if(output[j*outPitch + i] != refOut[j*outPitch + i])
      {
        status = 0;
        printf("[%d][%d] - output = %d\trefOutput = %d\n",j,i,
        output[j*outPitch + i], refOut[j*outPitch + i]);
        i = width;
        j = height;
        break;
      }
    }
  }

  if(status)
  {
    printf("\nEDMA Test,        PASSED \n");
  }
  else
  {
    printf("\nEDMA Test,        FAILED!!!!!! \n");
  }
  return 0;
}
