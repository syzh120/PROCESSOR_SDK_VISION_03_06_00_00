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


/** @file orb_tb.c
*
*  @brief  This file contains test code for ORB Algorithm
*
*
*  @date   Dec 2013
*  version : base
*
*  @date  April 2014
*  version : Updated
*
*  Description
*    This file contains test code to validate the frame level ORB Algorithm.
*    It also checks the output against c reference outputs and profiles the performance
*    and computes the system overheads.
*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <vcop.h>


#include "evestarterware.h"
#include "alg_osal.h"
#include "orb_config.h"
#include "xdais_types.h"
#include "iorb_ti.h"

#include "ti_mem_manager.h"
#include "eve_profile.h"

#define ENABLE_TRACES 0


#define PRINT_ERRORE_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#include <stdint.h>


const int8_t orbPattern[1024]  = {
  /* X Position of SRC */
  -13,    -2,    1,    2,    7,    -11,    4,    8,    -9,    -13,    -4,    7,    -11,    -13,    10,    -13,
  -8,    3,    5,    4,    11,    -6,    -3,    12,    1,    5,    5,    -10,    -4,    -7,    -13,    -2,
  -13,    0,    4,    -8,    -4,    2,    4,    9,    -6,    10,    -13,    7,    0,    8,    -6,    -3,
  2,    3,    -1,    5,    3,    -13,    -13,    10,    -12,    -2,    -9,    6,    -7,    -13,    -13,    -13,
  -4,    5,    -1,    -11,    2,    -3,    -7,    3,    -7,    7,    -4,    -7,    7,    10,    -12,    -9,
  -1,    -4,    2,    1,    -13,    7,    -3,    -13,    6,    12,    7,    -13,    -1,    9,    1,    7,
  1,    -11,    -8,    9,    2,    3,    2,    5,    -5,    -10,    -11,    7,    3,    6,    2,    6,
  7,    -5,    -2,    4,    -10,    4,    8,    -10,    11,    -2,    7,    1,    -9,    8,    -5,    -9,
  5,    -1,    0,    -9,    0,    5,    3,    -12,    1,    -13,    -7,    6,    -4,    -5,    -13,    3,
  7,    -3,    -6,    4,    -2,    2,    -2,    4,    2,    -13,    -8,    -7,    7,    7,    -13,    4,
  5,    -11,    -12,    -11,    2,    8,    -6,    10,    -4,    -9,    2,    -3,    -10,    -13,    -1,    -2,
  -4,    -1,    7,    11,    -13,    6,    -6,    -4,    1,    1,    -13,    -5,    -8,    -7,    -13,    -7,
  2,    8,    -13,    -1,    -9,    -1,    5,    9,    4,    5,    -4,    3,    4,    -10,    -10,    7,
  2,    -8,    8,    -10,    3,    -12,    0,    -9,    4,    -8,    -3,    -1,    -3,    -7,    6,    10,
  -10,    2,    4,    -3,    11,    3,    6,    2,    5,    -13,    -9,    -13,    0,    6,    -13,    -13,
  -13,    3,    -1,    3,    11,    9,    -1,    2,    -1,    7,    9,    7,    -10,    7,    8,    5,

  /* X Position of DST */

  -11,    -2,    1,    2,    12,    -8,    7,    9,    -7,    -12,    -3,    12,    -9,    -8,    11,    -12,
  -6,    6,    10,    5,    12,    -4,    -2,    12,    4,    7,    6,    -6,    -3,    -5,    -8,    -1,
  -8,    1,    9,    -7,    -2,    4,    4,    11,    -6,    12,    -11,    11,    1,    10,    -4,    -2,
  3,    5,    1,    10,    7,    -8,    -8,    12,    -7,    0,    -7,    12,    -4,    -11,    -12,    -13,
  -4,    5,    0,    -5,    5,    -1,    -4,    8,    -5,    12,    -3,    -6,    12,    12,    -8,    -9,
  1,    -2,    3,    12,    -11,    12,    -2,    -12,    7,    12,    10,    -10,    -1,    12,    3,    8,
  2,    -4,    -7,    10,    12,    4,    2,    6,    -3,    -5,    -6,    9,    8,    11,    3,    7,
  10,    -5,    -2,    6,    -8,    6,    12,    -9,    12,    -1,    9,    1,    -9,    9,    -5,    -8,
  7,    1,    2,    -5,    2,    10,    7,    -6,    3,    -5,    -6,    8,    -3,    -3,    -8,    6,
  12,    -1,    -3,    9,    0,    12,    2,    8,    3,    -12,    -7,    -7,    7,    8,    -9,    5,
  11,    -10,    -7,    -10,    2,    9,    -6,    12,    -3,    -4,    3,    -2,    -10,    -12,    0,    -1,
  -3,    0,    12,    12,    -5,    6,    -4,    -2,    10,    5,    -8,    -4,    -6,    -6,    -8,    -6,
  3,    10,    -8,    1,    -6,    1,    10,    10,    5,    10,    -3,    8,    8,    -8,    -5,    12,
  3,    -6,    12,    -10,    4,    -6,    3,    -4,    12,    -8,    -3,    -1,    -3,    -6,    8,    11,
  -8,    2,    4,    -3,    12,    7,    11,    3,    8,    -8,    -6,    -9,    1,    11,    -11,    -11,
  -10,    4,    0,    3,    12,    11,    -1,    3,    0,    12,    10,    12,    -10,    8,    9,    12,

  /* Y Position of SRC */

  -13,    -10,    -7,    -13,    -12,    9,    2,    -3,    0,    2,    -5,    7,    7,    -8,    4,    -3,
  -7,    -7,    -3,    7,    -13,    -13,    6,    -6,    0,    -6,    -12,    -12,    2,    3,    12,    11,
  -2,    -8,    11,    -5,    -12,    -1,    7,    11,    -3,    7,    -6,    -5,    9,    12,    9,    -2,
  -4,    -10,    7,    7,    3,    0,    8,    -9,    5,    -5,    -1,    -10,    12,    3,    -7,    0,
  -13,    -3,    6,    -13,    9,    -2,    -7,    -10,    6,    -1,    9,    -13,    12,    2,    -10,    -6,
  -13,    3,    -6,    -3,    -7,    -8,    7,    11,    3,    -5,    7,    -13,    -9,    1,    -1,    1,
  12,    12,    4,    -12,    6,    8,    -12,    -13,    -8,    11,    -5,    8,    -3,    3,    3,    -9,
  -6,    -8,    0,    -2,    12,    -6,    -1,    5,    -6,    1,    -4,    -8,    -11,    -8,    -13,    -13,
  11,    2,    7,    12,    -4,    5,    7,    -9,    -10,    6,    6,    5,    -7,    9,    -4,    5,
  5,    -13,    -10,    1,    -13,    -12,    -2,    1,    4,    6,    11,    -4,    -8,    1,    9,    -2,
  -3,    0,    -13,    -2,    -12,    -3,    -5,    -5,    6,    -13,    -3,    9,    -2,    -11,    -8,    -13,
  -8,    12,    -5,    11,    11,    -3,    -11,    12,    0,    5,    7,    -1,    5,    -2,    -12,    1,
  -13,    -11,    1,    -10,    -3,    11,    -8,    12,    -13,    -13,    2,    12,    -6,    -8,    -10,    -13,
  2,    -12,    -13,    -10,    2,    1,    3,    9,    2,    -2,    -7,    -13,    -9,    10,    8,    6,
  -6,    -4,    -11,    0,    -1,    -1,    -9,    -5,    -9,    -6,    8,    3,    -1,    0,    12,    7,
  0,    -6,    4,    0,    -3,    5,    -6,    7,    -6,    0,    -7,    3,    4,    -4,    9,    8,

  /* Y Position of DST */
  -8,    -4,    6,    12,    -13,    2,    -12,    5,    5,    -3,    0,    6,    12,    -9,    9,    -9,
  -2,    12,    -3,    1,    -8,    -8,    12,    -1,    -5,    -1,    -7,    11,    7,    -3,    10,    -10,
  2,    -13,    12,    -10,    7,    4,    12,    -13,    12,    1,    0,    -10,    3,    7,    -9,    3,
  -10,    6,    -12,    -7,    8,    -4,    -12,    -4,    5,    12,    -6,    8,    7,    8,    12,    5,
  12,    2,    -1,    -13,    -11,    -7,    5,    -13,    1,    2,    4,    5,    12,    -3,    -4,    6,
  9,    -13,    0,    12,    -12,    -7,    -6,    5,    11,    9,    12,    5,    3,    6,    12,    -6,
  -8,    -6,    9,    3,    -13,    -6,    3,    10,    12,    10,    -4,    3,    -8,    0,    -2,    -4,
  12,    2,    12,    7,    7,    -11,    -6,    0,    -11,    -4,    1,    -2,    0,    -13,    -2,    -8,
  -9,    7,    12,    -13,    8,    8,    12,    4,    10,    -2,    12,    0,    -12,    -3,    9,    -8,
  -11,    1,    -5,    3,    -6,    12,    -13,    -4,    9,    -8,    -8,    1,    6,    6,    -5,    -7,
  8,    -5,    -9,    3,    8,    -8,    7,    3,    -10,    0,    2,    -13,    11,    -5,    9,    12,
  -2,    7,    -2,    6,    5,    11,    9,    -7,    -13,    -13,    10,    5,    -9,    -8,    -13,    7,
  -6,    -6,    -10,    12,    2,    -13,    -9,    -1,    -1,    -12,    -3,    -13,    5,    -13,    -7,    -9,
  7,    -5,    12,    9,    -8,    1,    -9,    3,    12,    3,    4,    5,    9,    5,    -12,    -8,
  1,    1,    12,    6,    4,    12,    -13,    11,    10,    -2,    -3,    -2,    4,    -13,    -13,    1,
  5,    5,    10,    5,    -8,    -2,    -1,    -9,    -11,    -2,    -2,    4,    9,    -12,    -6,    11
} ;
#define DMEM_SIZE (26*1024)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
/* This will be used for allocation of memory in DMEM*/
uint8_t DMEM_SCRATCH[DMEM_SIZE];

TIMemObject memObj_DMEM;

void TestApp_WriteORBOutput(const char *fileName, IVISION_OutBufs *outBufs, uint16_t numCorners)
{
  FILE *fp ;
  uint16_t i, k, X, Y ;
  uint8_t level ;

  fp= fopen(fileName,"w");

  uint32_t *pXYBuffer    = (uint32_t*) outBufs->bufDesc[ORB_TI_BUFDESC_OUT_XY_LIST]->bufPlanes[0].buf ;
  uint8_t *pLevelBuffer  = (uint8_t *) outBufs->bufDesc[ORB_TI_BUFDESC_OUT_LEVEL_ID]->bufPlanes[0].buf ;
  uint8_t *pDescBuffer   = (uint8_t *) outBufs->bufDesc[ORB_TI_BUFDESC_OUT_DESCRIPTOR]->bufPlanes[0].buf ;

  if ( fp == NULL)
  {
    TEST_PRINTF("Error, unable to open file %s \n", fileName);
    goto EXIT_WRITEORB;
  }

  /* Format to print is as below */
  /*  X,  Y,    LEVEL,    DESCRIPTOR */
  for(i= 0 ; i<numCorners; i++)
  {
    X = *(pXYBuffer + i) >> 16 ;
    Y = *(pXYBuffer + i) & 0xFFFF ;
    level = *(pLevelBuffer + i);

    fprintf(fp, "%6d,%6d,%3d,",X, Y, level);
    for(k=0; k < 256/8 ; k++)
    {
      fprintf(fp, "%02X",*(pDescBuffer + i*(256/8) + k));
    }
    fprintf(fp,"\n");
  }

  fclose(fp);

EXIT_WRITEORB:
  return ;
}

int32_t TestApp_AllocMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
  int32_t i;
  TIMemHandle memHdl_DMEM = &memObj_DMEM;

  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].space == IALG_DARAM0 ) {
      memRec[i].base = TI_GetMemoryChunk(memHdl_DMEM, memRec[i].size, memRec[i].alignment);
    }
    else {
      memRec[i].base = (Void *) malloc( memRec[i].size);
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
    if(memRec[i].space != IALG_DARAM0) {
        free(memRec[i].base);
    }
  }
  return IALG_EOK;
}

typedef struct IM_Fxns
{
  IVISION_Fxns * ivision;

} IM_Fxns;


int32_t ORBTest(sORB_Config * params)
{
  uint32_t tcntr0, tcntr1, overflow, profile_sctm;
  uint8_t *wbufToZero;
  int32_t numMemRec;
  int32_t i,j;
  IALG_MemRec *memRec;
  int32_t status;
  uint8_t *input;
  uint8_t *output;
  uint8_t *refOutput = NULL;
  uint16_t totalActivePixels, levelCnt ;

  uint32_t t0, t1, overhead, profile_tsc, profile_create_tsc;

  uint32_t outsize[ORB_TI_BUFDESC_OUT_TOTAL];
  uint32_t sizeInput;
  uint32_t numBytes;
  uint32_t testcase;

  char  filepath[256];
  FILE *fid;


  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  ORB_TI_CreateParams   createParams;

  ORB_TI_InArgs     inArgs;
  IVISION_InBufs    inBufs;
  IVISION_OutBufs   outBufs;
  ORB_TI_OutArgs    outArgs;

  IVISION_BufDesc   inBufDesc[ORB_TI_BUFDESC_IN_TOTAL];
  IVISION_BufDesc   outBufDesc[ORB_TI_BUFDESC_OUT_TOTAL];

  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   *inBufDescList[ORB_TI_BUFDESC_IN_TOTAL];

  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   *outBufDescList[ORB_TI_BUFDESC_OUT_TOTAL];

  outArgs.iVisionOutArgs.size = sizeof(ORB_TI_OutArgs);
  /*--------------------------------------------------------------------------*/
  /*Create memory handle for ARP32 DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;


  /*-----------------------------------------------------------------
  Set buffer descriptor pointers array base
  -----------------------------------------------------------------*/
  inBufs.bufDesc  = inBufDescList;
  outBufs.bufDesc = outBufDescList;

  inBufs.numBufs   = ORB_TI_BUFDESC_IN_TOTAL ;
  outBufs.numBufs  = ORB_TI_BUFDESC_OUT_TOTAL;

  for(i = 0 ; i < ORB_TI_BUFDESC_IN_TOTAL ;i++)
  {
    inBufDescList[i]     = &inBufDesc[i];
  }
  for(i = 0 ; i < ORB_TI_BUFDESC_OUT_TOTAL ;i++)
  {
    outBufDescList[i]     = &outBufDesc[i];
  }

  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);
  _tsc_start();

  t0 = _tsc_gettime();
  overhead = _tsc_gettime() - t0;

  TEST_PRINTF("\n%-20s %10s %10s %10s %10s %15s %10s %10s %16s    %s\n", \
    "Algorithm", "TotalFeatures", "BaseWidth", "BaseHeight","NumLevels", "MegaCycPerFr", \
    "MegaCycPerSec(30Fr)", "VcopBusyMegaCycPerFr","TimePerFr(MSec)", "Comments");


  /*------------------------------------------------------------*/
  /* This function actually sets Enable bit in the CT CNTL      */
  /* register of SCTM. Parameter CTM is defined in              */
  /* baseaddress.h, and is used by cred macros to compute       */
  /* baseaddress of CTM.                                        */
  /*------------------------------------------------------------*/
  EVE_SCTM_Enable(CTM);

  /*------------------------------------------------------------*/
  /* Configure Counter 0, to measure "vcop_busy" which is a     */
  /* duration signal, and enable the counter.                   */
  /*------------------------------------------------------------*/
  EVE_SCTM_CounterConfig(CTM, SCTM_Counter_0, VCOP_BUSY, SCTM_DURATION);
  EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_0);

  for ( testcase = 0 ; testcase < orb_numTestCases; testcase++ )
  {

    /*-----------------------------------------------------------------
    Set algorithm parameters
    -----------------------------------------------------------------*/

    createParams.visionParams.algParams.size   = sizeof(ORB_TI_CreateParams);
    createParams.visionParams.cacheWriteBack   = NULL;

    createParams.imgFrameWidth           = params[testcase].imgFrameWidth           ;
    createParams.imgFrameHeight          = params[testcase].imgFrameHeight          ;
    createParams.imgFramePitch           = params[testcase].imgFramePitch           ;
    createParams.numLevels               = params[testcase].numLevels               ;
    createParams.fast9Threshold          = params[testcase].fast9Threshold          ;
    createParams.startX                  = params[testcase].startX                  ;
    createParams.startY                  = params[testcase].startY                  ;
    createParams.harrisSensitivityParam  = params[testcase].harrisSensitivityParam  ;
    createParams.bestNFeaturesOut        = params[testcase].totalFeatures           ;
    createParams.scoreMethod             = ORB_TI_THRESH_METHOD ;
    createParams.orbPattern              = orbPattern ;

    /*-----------------------------------------------------------------
    Query alogorithm memory requirement using standard IALG interface
    -----------------------------------------------------------------*/
    numMemRec = ORB_TI_VISION_FXNS.ialg.algNumAlloc();
    memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

    status = ORB_TI_VISION_FXNS.ialg.algAlloc(
      (IALG_Params *)(&createParams), NULL, memRec);

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    TEST_PRINTF("ORB Algo Create Done\n");
#endif
    /*-----------------------------------------------------------------
    Allocate memory for all the mem records
    Application has to implement the below function
    Refer the example implementation below in this file
    -----------------------------------------------------------------*/
    status = TestApp_AllocMemRecords(memRec,numMemRec);
    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }

    /* Start measuring execution time for creation process */
    t0 = _tsc_gettime();

    /*-----------------------------------------------------------------
    Intialize the algorithm instance with the alocated memory
    and user create parameters
    -----------------------------------------------------------------*/
    status = ORB_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
      memRec,NULL,(IALG_Params *)(&createParams));


    /* Set the end point of the timing measurement for the creation process */
    t1 = _tsc_gettime();
    profile_create_tsc = (t1 - t0 - overhead);

    handle = (IM_Fxns *) memRec[0].base;

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    TEST_PRINTF("FAST9 corner detect Applet Init Done\n");
#endif

    inArgs.iVisionInArgs.subFrameInfo = 0;
    inArgs.iVisionInArgs.size         = sizeof(ORB_TI_InArgs);
    inArgs.fast9CornerSelectMethod    = params[testcase].fast9CornerSelectMethod ;

    inBufs.bufDesc[ORB_TI_BUFDESC_IN_IMAGEBUFFER]->numPlanes                          = 1;
    inBufs.bufDesc[ORB_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.topLeft.x    = createParams.startX;
    inBufs.bufDesc[ORB_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.topLeft.y    = createParams.startX;
    inBufs.bufDesc[ORB_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].width                 = params[testcase].imgFramePitch;
    inBufs.bufDesc[ORB_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].height                = createParams.imgFrameHeight;
    inBufs.bufDesc[ORB_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.width        = createParams.imgFrameWidth;
    inBufs.bufDesc[ORB_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.height       = createParams.imgFrameHeight;

    sizeInput = inBufs.bufDesc[ORB_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].width *
      inBufs.bufDesc[ORB_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].height;
    input  = (uint8_t * )malloc(sizeInput);
    inBufs.bufDesc[ORB_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].buf = (uint8_t * )input ;

    if(inBufs.bufDesc[ORB_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].buf == NULL)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }

    outsize[ORB_TI_BUFDESC_OUT_DESCRIPTOR] = createParams.bestNFeaturesOut*(256/8);
    outsize[ORB_TI_BUFDESC_OUT_XY_LIST]    = createParams.bestNFeaturesOut*(4);
    outsize[ORB_TI_BUFDESC_OUT_LEVEL_ID]   = createParams.bestNFeaturesOut*(1);
    for(i = 0 ; i < ORB_TI_BUFDESC_OUT_TOTAL ;i++)
    {
      output = (uint8_t * )malloc(outsize[i]);
      if(output == NULL)
      {
        PRINT_ERRORE_MSG();
        goto EXIT_LOOP;
      }
      outBufs.bufDesc[i]->bufPlanes[0].buf                   = (uint8_t * )output  ;
      outBufs.bufDesc[i]->numPlanes                          = 1 ;
      outBufs.bufDesc[i]->bufPlanes[0].frameROI.topLeft.x    = 0 ;
      outBufs.bufDesc[i]->bufPlanes[0].frameROI.topLeft.y    = 0 ;
      outBufs.bufDesc[i]->bufPlanes[0].width                 = outsize[i];
      outBufs.bufDesc[i]->bufPlanes[0].height                = 1 ;
      outBufs.bufDesc[i]->bufPlanes[0].frameROI.width        = outsize[i];
      outBufs.bufDesc[i]->bufPlanes[0].frameROI.height       = 1;
    }


    if ( params[testcase].fileBased == 1 )
    {
      sprintf(filepath, "../testvecs/input/%s", params[testcase].inImage);
      fid = fopen(filepath,"rb");
      if (fid == NULL) {
        PRINT_ERRORE_MSG();
        TEST_PRINTF("Error, unable to open file %s \n", filepath);
        goto EXIT_LOOP;
      }
      input = (uint8_t * )inBufs.bufDesc[ORB_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].buf;
      numBytes= fread(input, 1, sizeInput, fid);
      assert(numBytes== sizeInput);
      fclose(fid);
    }
    else
    {
      /* Create Random input data */
      for ( i = 0 ; i < createParams.imgFrameHeight; i++)
      {
        for ( j = 0; j < createParams.imgFrameWidth ; j++)
        {
          input[j + (i*params[testcase].imgFramePitch)] = rand() % 256;
        }
      }
    }

    vcop_minit();
    wbufToZero= (uint8_t*)vcop_malloc(VCOP_WMEM, 31*1024);
    memset(wbufToZero, 0xcd, 31*1024);
    vcop_free(wbufToZero);

#if ENABLE_TRACES
    TEST_PRINTF("Processing start \n");
#endif

    status = handle->ivision->algProcess((IVISION_Handle)handle,
      &inBufs,&outBufs,(IVISION_InArgs*)&inArgs,(IVISION_OutArgs *)&outArgs);

    tcntr0 = EVE_SCTM_CounterRead(CTM, SCTM_Counter_0);

    t0 = _tsc_gettime();
    /* Profile second process call to reduce progarm cache overheads */
    status = handle->ivision->algProcess((IVISION_Handle)handle,
      &inBufs,&outBufs,(IVISION_InArgs*)&inArgs,(IVISION_OutArgs *)&outArgs);

    t1 = _tsc_gettime();
    profile_tsc = (t1 - t0 - overhead);
    tcntr1 = EVE_SCTM_CounterRead(CTM, SCTM_Counter_0);
    overflow = EVE_SCTM_OverflowCheck(CTM, SCTM_Counter_0);
    if(overflow) {
      TEST_PRINTF("Counter overflow!!!\n");
    }
    profile_sctm = ((overflow) ? (0XFFFFFFFF + tcntr1 - tcntr0) : (tcntr1 - tcntr0));

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    TEST_PRINTF("Processing End\n");
#endif

    if (params[testcase].fileBased == 1)
    {
      /* Write output files */
      sprintf(filepath, "../testvecs/output/%s", params[testcase].outImage);
      TestApp_WriteORBOutput(filepath, &outBufs, outArgs.numCorners);
    }


    totalActivePixels  = 0;

    for ( levelCnt = 0 ; levelCnt < params[testcase].numLevels ; levelCnt++)
    {
      totalActivePixels  += outArgs.activeImgWidth[levelCnt] * outArgs.activeImgHeight[levelCnt];
    }
    TEST_PRINTF("%-20s %10d %10d %10d %10d %15.2f %20.2f %17.2f %16.2f \
        Create graph is %2.2f Mcycles per frame but it is a one-time startup call\n",\
        "ORB",params[testcase].totalFeatures, params[testcase].imgFrameWidth, params[testcase].imgFrameHeight,\
        params[testcase].numLevels, (2*profile_tsc/1000000.0), 30*(2*profile_tsc/1000000.0),\
        (profile_sctm*2.0)/1000000.0,\
        (2*profile_tsc/500000.0), (profile_create_tsc*2.0)/1000000.0);

    fflush(stdout);
EXIT_LOOP:
    status = handle->ivision->ialg.algFree((IALG_Handle)(handle), memRec);
    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
    }
    /* Here Free memory for all the mem records */
    status = TestApp_FreeMemRecords(memRec,numMemRec);
    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
    }

    if ( memRec != NULL )
    {
      free(memRec);
    }
    for(i = 0 ; i < ORB_TI_BUFDESC_OUT_TOTAL ;i++)
    {
      output = (uint8_t*) outBufs.bufDesc[i]->bufPlanes[0].buf ;
      if ( output != NULL )
      {
        free(output);
      }
    }
    for(i = 0 ; i < ORB_TI_BUFDESC_IN_TOTAL ;i++)
    {
      input = (uint8_t*) inBufs.bufDesc[i]->bufPlanes[0].buf ;
      if ( input != NULL )
      {
        free(input);
      }
    }

    if ( refOutput != NULL )
    {
      free(refOutput);
    }

  }
  return status;
}

int main(int argc, char *argv[])
{
  int status = 0;
  char configFile[FILE_NAME_SIZE]={0};

  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,"../testvecs/config/orb.cfg");
  }

  gConfig_ORB[0].fast9CornerSelectMethod = 0 ;
  status = readparamfile(configFile, &gsTokenMap_ORB[0]) ;
  if(status == -1)
  {
    TEST_PRINTF("Parser Failed");
    return -1 ;
  }

  /* Validate the applet */
  status = ORBTest(gConfig_ORB);

  return status;
}



