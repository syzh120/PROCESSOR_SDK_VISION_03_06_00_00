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


/** @file hough_for_circles_tb.c
*
*  @brief  This file contains test code for Hough For circles applet
*
*  @date   Sept 2014
*
*  Description
*    This file contains test code to validate the frame level applet hough
*    for circles. It also checks the output against c reference outputs and
*    profiles the performance and computes the system overheads.
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
#include "hough_for_circles_config.h"
#include "xdais_types.h"
#include "ihough_for_circles_ti.h"

#include "ti_file_io.h"
#include "ti_mem_manager.h"
#include "eve_profile.h"
#include "vcop_vec_gradients_xy_and_magnitude_c.h"
#include "math.h"
#include "hough_for_circles_cn.h"

#define ENABLE_OUTPUT_DUMP 0
#define ENABLE_DUMP_CIRCLE_COORDINATES 0
#define DUMP_EDGE_MAP 0
#define ENABLE_TRACES 0
#define FIXED_PATTERN 0
#define ENABLE_PROFILE 0

#define ALIGN_T0_32(x) (((x+31)/32)*32)



#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")


#define PRINT_ERRORE_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define DMEM_SIZE (20*1024)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
/* This will be used for allocation of memory in DMEM*/
uint8_t DMEM_SCRATCH[DMEM_SIZE];
#define MAX_CIRC_PER_RADIUS (1024)


TIMemObject memObj_DMEM;


int32_t TestApp_AllocMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
  int32_t i;
  TIMemHandle memHdl_DMEM = &memObj_DMEM;
  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].space == IALG_DARAM0) {
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

int32_t TestApp_AllocateBufs(IVISION_InBufs * inBufs,
                             IVISION_InBufs * outBufs)
{
  uint32_t i, j;
  int32_t status = 0;
  if ( inBufs != NULL)
  {
    for ( i  = 0 ; i < inBufs->numBufs ; i++)
    {
      for ( j  = 0 ; j < inBufs->bufDesc[i]->numPlanes ; j++)
      {
        inBufs->bufDesc[i]->bufPlanes[j].buf = malloc(inBufs->bufDesc[i]->bufPlanes[j].width *
                                                           inBufs->bufDesc[i]->bufPlanes[j].height);
        if ( inBufs->bufDesc[i]->bufPlanes[j].buf == NULL )
        {
          TEST_PRINTF("Malloc failed Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
          return -1;
        }
      }
    }
  }

  if ( outBufs != NULL )
  {
    for ( i  = 0 ; i < outBufs->numBufs ; i++)
    {
      for ( j  = 0 ; j < outBufs->bufDesc[i]->numPlanes ; j++)
      {
        outBufs->bufDesc[i]->bufPlanes[j].buf = malloc(outBufs->bufDesc[i]->bufPlanes[j].width *
                                                       outBufs->bufDesc[i]->bufPlanes[j].height);
        if ( outBufs->bufDesc[i]->bufPlanes[j].buf == NULL )
        {
          TEST_PRINTF("Malloc failed Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
          return -1;
        }
      }
    }
  }

  return status;
}


int32_t TestApp_FreeBufs(IVISION_InBufs * inBufs,
                                 IVISION_InBufs * outBufs)
{
  uint32_t i, j;
  int32_t status = 0;
  if ( inBufs != NULL )
  {
    for ( i  = 0 ; i < inBufs->numBufs ; i++)
    {
      for ( j  = 0 ; j < inBufs->bufDesc[i]->numPlanes ; j++)
      {
        if (inBufs->bufDesc[i]->bufPlanes[j].buf != NULL)
        {
          free(inBufs->bufDesc[i]->bufPlanes[j].buf);
          inBufs->bufDesc[i]->bufPlanes[j].buf = NULL;
        }
      }
    }
  }
  if ( outBufs != NULL )
  {

    for ( i  = 0 ; i < outBufs->numBufs ; i++)
    {
      for ( j  = 0 ; j < outBufs->bufDesc[i]->numPlanes ; j++)
      {
        if (outBufs->bufDesc[i]->bufPlanes[j].buf != NULL)
        {
          free(outBufs->bufDesc[i]->bufPlanes[j].buf);
          outBufs->bufDesc[i]->bufPlanes[j].buf = NULL;
        }
      }
    }
  }
  return status;
}

int32_t houghForCirclesTest(sHoughForCircles_Config * testcaseParams)
{
#if ENABLE_PROFILE
  uint32_t tcntr0, tcntr1, overflow, profile_sctm;
  uint32_t t0, t1, overhead, profile_tsc, profile_create_tsc;
  char  *statusStr = NULL;
#endif
  uint32_t i, j, idx;
  int32_t numMemRec;
  IALG_MemRec *memRec;
  int32_t status;
  uint32_t seed;
  uint8_t * edgeImPtr;


  uint32_t testcase;
  uint32_t edgeMapPitch;
  int32_t fail;
  TI_FILE *fp_in = NULL;

  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  HOUGH_FOR_CIRCLES_TI_CreateParams   createParams;

  HOUGH_FOR_CIRCLES_TI_InArgs inArgs;
  IVISION_InBufs    inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc[HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_TOTAL];
  IVISION_BufDesc   *inBufDescList[HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_TOTAL];

  HOUGH_FOR_CIRCLES_TI_OutArgs   * outArgs = NULL;
  HOUGH_FOR_CIRCLES_TI_OutArgs   * outArgsRef = NULL;

  HOUGH_FOR_CIRCLES_TI_ControlInArgs ctrlInArgs;
  HOUGH_FOR_CIRCLES_TI_ControlOutArgs ctrlOutArgs;

  /*--------------------------------------------------------------------------*/
  /*Create memory handle for ARP32 DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;
  HOUGH_FOR_CIRCLES_TI_CircleInfo *ptrRef;
  HOUGH_FOR_CIRCLES_TI_CircleInfo *ptrTarget;
  uint8_t numRadius;
  uint8_t maxRadius;

  /* This is just to remove warning coming from linker command file */
  vcop_minit();

  outArgs     = (HOUGH_FOR_CIRCLES_TI_OutArgs *)malloc(sizeof(HOUGH_FOR_CIRCLES_TI_OutArgs));

  if ( outArgs == NULL )
  {
    goto EXIT_LOOP;
  }
  outArgsRef  = (HOUGH_FOR_CIRCLES_TI_OutArgs *)malloc(sizeof(HOUGH_FOR_CIRCLES_TI_OutArgs));

  if ( outArgsRef == NULL )
  {
    goto EXIT_LOOP;
  }

  outArgs->iVisionOutArgs.size = sizeof(HOUGH_FOR_CIRCLES_TI_OutArgs);
  inArgs.iVisionInArgs.size   = sizeof(HOUGH_FOR_CIRCLES_TI_InArgs);


  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);

#if ENABLE_PROFILE
  _tsc_start();

  t0 = _tsc_gettime();
  overhead = _tsc_gettime() - t0;
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
  TEST_PRINTF("\n%-20s %10s %10s %10s %10s %15s %20s %10s %10s %16s    %s\n", \
    "Algorithm", "Status", "BaseWidth", "BaseHeight","NumRadius", "MegaCycPerFr", \
    "MegaCycPerSec(30Fr)", "TotalCycPerPix", "VcopBusyCycPerPix","TimePerFr(MSec)", \
    "Comments");
#endif

  profiler_init();


  profiler_initStack(profiler_getSP());

  /*-----------------------------------------------------------------
      Set buffer descriptor pointers array base
      -----------------------------------------------------------------*/
  inBufs.bufDesc  = inBufDescList;

  inBufs.numBufs   = HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_TOTAL;

  for(i = 0 ; i < HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_TOTAL ;i++) {
    inBufDescList[i] = &inBufDesc[i];
  }

  for( testcase = 0 ; testcase < houghForCircles_numTestCases; testcase++ ){


   createParams.circleType          = (HOUGH_FOR_CIRCLES_TI_CircleType)testcaseParams[testcase].circleType;
   createParams.houghSpaceScaling   = (HOUGH_FOR_CIRCLES_TI_HoughSpaceScaling)testcaseParams[testcase].houghSpaceScaling;
   createParams.maxPercentageEdges  = testcaseParams[testcase].maxPercentageEdges;
   createParams.maxNumRadius        = testcaseParams[testcase].numRadius;


   /*-----------------------------------------------------------------
      Set algorithm parameters
      -----------------------------------------------------------------*/
    /*-----------------------------------------------------------------
    Query alogorithm memory requirement using standard IALG interface
    -----------------------------------------------------------------*/


    numMemRec = HOUGH_FOR_CIRCLES_TI_VISION_FXNS.ialg.algNumAlloc();
    memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

    status = HOUGH_FOR_CIRCLES_TI_VISION_FXNS.ialg.algAlloc(
      (IALG_Params *)(&createParams), NULL, memRec);

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    TEST_PRINTF("Hough For Circles Applet Create Done\n");
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
#if ENABLE_PROFILE
    /* Start measuring execution time for creation process */
    t0 = _tsc_gettime();
#endif
    profiler_start();

    /*-----------------------------------------------------------------
    Intialize the algorithm instance with the alocated memory
    and user create parameters
    -----------------------------------------------------------------*/
    status = HOUGH_FOR_CIRCLES_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
      memRec,NULL,(IALG_Params *)(&createParams));

#if ENABLE_PROFILE
    /* Set the end point of the timing measurement for the creation process */
    t1 = _tsc_gettime();
    profile_create_tsc = (t1 - t0 - overhead);
#endif
    profiler_end_print(0);

    handle = (IM_Fxns *) memRec[0].base;

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }



#if ENABLE_TRACES
    TEST_PRINTF("Hough For Circles  Applet Init Done\n");
#endif

    edgeMapPitch = testcaseParams[testcase].imageWidth;

    idx = HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_IMAGE;
    inBufs.bufDesc[idx]->numPlanes                          = 1;
    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
    inBufs.bufDesc[idx]->bufPlanes[0].width                 = testcaseParams[testcase].imagePitch;
    inBufs.bufDesc[idx]->bufPlanes[0].height                = testcaseParams[testcase].imageHeight;
    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = testcaseParams[testcase].imageWidth;
    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = testcaseParams[testcase].imageHeight;
    inBufs.bufDesc[idx]->bufPlanes[0].planeType             = 0;
    inBufs.bufDesc[idx]->bufPlanes[0].buf                   = NULL;

    idx = HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_EDGEMAP;
    inBufs.bufDesc[idx]->numPlanes                          = 1;
    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
    inBufs.bufDesc[idx]->bufPlanes[0].width                 = edgeMapPitch;
    inBufs.bufDesc[idx]->bufPlanes[0].height                = testcaseParams[testcase].imageHeight;
    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = testcaseParams[testcase].imageWidth;
    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = testcaseParams[testcase].imageHeight;

    inBufs.bufDesc[idx]->bufPlanes[0].planeType             = 0;
    inBufs.bufDesc[idx]->bufPlanes[0].buf                   = NULL;

    inArgs.iVisionInArgs.subFrameInfo = 0;
    inArgs.iVisionInArgs.size = sizeof(HOUGH_FOR_CIRCLES_TI_InArgs);
    inArgs.numRadius      = testcaseParams[testcase].numRadius;

    maxRadius = 0;
    for ( i = 0; i < inArgs.numRadius; i++)
    {
      inArgs.circleProps[i].radius              = testcaseParams[testcase].radius[i];
      inArgs.circleProps[i].houghScoreThreshold = testcaseParams[testcase].houghScoreThreshold[i];
      if (inArgs.circleProps[i].radius > maxRadius )
      {
        maxRadius =inArgs.circleProps[i].radius;
      }
    }

    idx = HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_EDGEMAP;

    ctrlInArgs.imageWidth   = inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width;
    ctrlInArgs.imageHeight  = inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height;
    ctrlInArgs.maxRadius    = maxRadius;
    /* This is an optional call to get the buffer requirement for edge and image buffer and also to do the zero padding for edgemap buffer */
    /* Incase user doesnt want to call control call in that case it is expected that user allocate the worst case buffer which is
    of border 48 on exterme left and bottom of the image. Also it is expected that user fill this buffer border with zero for edgemap buffer */
    status = handle->ivision->algControl((IVISION_Handle)handle, HOUGH_FOR_CIRCLES_TI_CONTROLCMD_GET_EFFECTIVE_IMAGEDIMENSION , (IALG_Params *)&ctrlInArgs, (IALG_Params *)&ctrlOutArgs);

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }

    idx = HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_IMAGE;
    inBufs.bufDesc[idx]->bufPlanes[0].width                 = ctrlOutArgs.effImageWidth;
    inBufs.bufDesc[idx]->bufPlanes[0].height                = ctrlOutArgs.effImageHeight;

    idx = HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_EDGEMAP;
    inBufs.bufDesc[idx]->bufPlanes[0].width                 = ctrlOutArgs.effImageWidth;
    inBufs.bufDesc[idx]->bufPlanes[0].height                = ctrlOutArgs.effImageHeight;


    status = TestApp_AllocateBufs(&inBufs, NULL);
    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }

    idx = HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_IMAGE;
    inBufs.bufDesc[idx]->bufPlanes[0].width                 = testcaseParams->imagePitch;

    idx = HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_EDGEMAP;
    inBufs.bufDesc[idx]->bufPlanes[0].width                 = ctrlOutArgs.effImageWidth;
    edgeMapPitch = ctrlOutArgs.effImageWidth;

    edgeImPtr  = (uint8_t *) inBufs.bufDesc[HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_EDGEMAP]->bufPlanes[0].buf;
    /* It is expected that edgeMap buffer is filled with zero for the regions beyond the actual image region */
    memset (edgeImPtr, 0x0 , ctrlOutArgs.effImageWidth * ctrlOutArgs.effImageHeight);
    inBufs.bufDesc[HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_EDGEMAP]->bufPlanes[0].buf = (uint8_t *)edgeImPtr;

    if ( status != 0 )
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }

    if ( strcmp((const char *)testcaseParams[testcase].inImg, ""))
    {
      fp_in = FOPEN((const char *)testcaseParams[testcase].inImg, "rb");

      if(fp_in == NULL)
      {
          TEST_PRINTF("Failed to open input file: %s.\n", testcaseParams[testcase].inImg);
          return -1;
      }
      FREAD(inBufs.bufDesc[HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].buf,
        testcaseParams[testcase].imagePitch *testcaseParams[testcase].imageHeight, 1, fp_in);

      FCLOSE(fp_in);
    }
    else
    {
      uint8_t * ptr  = (uint8_t *) inBufs.bufDesc[HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].buf;
      seed = (testcaseParams[testcase].randSeed == 0) ? _tsc_gettime() : testcaseParams[testcase].randSeed;
      srand(seed);

      for ( j = 0; j < testcaseParams[testcase].imageHeight; j++ )
      {
        for ( i = 0; i < testcaseParams[testcase].imageWidth; i++ )
        {
#if FIXED_PATTERN
          ptr[i + (j * testcaseParams[testcase].imagePitch)] = (i +j *98) % 255;
#else
          ptr[i + (j * testcaseParams[testcase].imagePitch)] = rand() % 255;
#endif
        }
      }
    }


    if ( strcmp((const char *)testcaseParams[testcase].edgeImg, ""))
    {
      uint8_t * ptr  = (uint8_t *)edgeImPtr;
      fp_in = FOPEN((const char *)testcaseParams[testcase].edgeImg, "rb");

      if(fp_in == NULL)
      {
          TEST_PRINTF("Failed to open input file: %s.\n", testcaseParams[testcase].edgeImg);
          return -1;
      }

      for ( j = 0; j < testcaseParams[testcase].imageHeight; j++ )
      {
        FREAD(ptr,testcaseParams[testcase].imageWidth, 1, fp_in);
        ptr = ptr + edgeMapPitch;

      }
      FCLOSE(fp_in);
    }
    else
    {
      uint8_t * ptr  = (uint8_t *) edgeImPtr;
      seed = (testcaseParams[testcase].randSeed == 0) ? _tsc_gettime() : testcaseParams[testcase].randSeed;
      srand(seed);

      for ( j = 0; j < testcaseParams[testcase].imageHeight; j++ )
      {
        for ( i = 0; i < testcaseParams[testcase].imageWidth; i++ )
        {
#if FIXED_PATTERN
          ptr[i + j*(edgeMapPitch)] = (i + j*(edgeMapPitch)) % 2;
#else
          ptr[i + j*(edgeMapPitch)] = rand() % 2;
#endif


        }
      }
    }
    if(testcaseParams[testcase].genEdgeMap)
    {
      genEdgeMap_cn((uint8_t *) inBufs.bufDesc[HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].buf,
                    edgeImPtr,
                    testcaseParams[testcase].imageWidth,
                    testcaseParams[testcase].imageHeight,
                    testcaseParams[testcase].imagePitch,
                    edgeMapPitch,
                    80);
    }

#if DUMP_EDGE_MAP
    dumpEdgeMap_cn( edgeImPtr,
                    testcaseParams[testcase].imageWidth,
                    testcaseParams[testcase].imageHeight,
                    edgeMapPitch
                    );
#endif

#if ENABLE_TRACES
    TEST_PRINTF("Processing started for frame %d \n",0);
#endif


    profiler_start();

#if ENABLE_PROFILE
        tcntr0 = EVE_SCTM_CounterRead(CTM, SCTM_Counter_0);
        t0 = _tsc_gettime();
#endif

    status = handle->ivision->algProcess((IVISION_Handle)handle,
     &inBufs,NULL,(IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)outArgs);

#if ENABLE_PROFILE
    t1 = _tsc_gettime();

    profile_tsc = (t1 - t0 - overhead);
    tcntr1 = EVE_SCTM_CounterRead(CTM, SCTM_Counter_0);
    overflow = EVE_SCTM_OverflowCheck(CTM, SCTM_Counter_0);
    if(overflow) {
      TEST_PRINTF("Counter overflow!!!\n");
    }
    profile_sctm = ((overflow) ? (0XFFFFFFFF + tcntr1 - tcntr0) : (tcntr1 - tcntr0));
#endif

    profiler_end_print(1);

#if ENABLE_PROFILE
    TEST_PRINTF("TSC Cycles : SCTM %12d :% 12d\n", profile_tsc,profile_sctm);
#endif

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
  }
#if ENABLE_TRACES
    TEST_PRINTF("Processing Completed for frame %d \n",0);
    TEST_PRINTF("Starting Tile Based processing \n");
#endif

     houghForCircle_TileBased_cn(
      (uint8_t *)inBufs.bufDesc[HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].buf,
      (uint8_t *)inBufs.bufDesc[HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_EDGEMAP]->bufPlanes[0].buf,
      &createParams, &inArgs, outArgsRef, testcaseParams[testcase].imageWidth,
      testcaseParams[testcase].imageHeight, testcaseParams[testcase].imagePitch,edgeMapPitch,
      testcaseParams[testcase].maxPercentageEdges,
      MAX_CIRC_PER_RADIUS);

     numRadius = (createParams.circleType == HOUGH_FOR_CIRCLES_TI_CIRCLE_BOTH) ? 2 * inArgs.numRadius : inArgs.numRadius;

     fail = 0;

      for ( i = 0 ; i < numRadius; i++)
      {
        if ( outArgsRef->numCircles[i]  == outArgs->numCircles[i] )
        {
#if ENABLE_TRACES
          TEST_PRINTF("Number of circles detected for radius=%d is %d \n",inArgs.circleProps[i%inArgs.numRadius].radius,outArgsRef->numCircles[i]);
#endif
          ptrRef    = (HOUGH_FOR_CIRCLES_TI_CircleInfo *)outArgsRef->circleInfo[i];
          ptrTarget = (HOUGH_FOR_CIRCLES_TI_CircleInfo *)outArgs->circleInfo[i];

          for ( j = 0; j < outArgsRef->numCircles[i]; j++ )
          {
            if ( (ptrRef[j].centerX != ptrTarget[j].centerX) ||
                 (ptrRef[j].centerY != ptrTarget[j].centerY) ||
                 (outArgsRef->houghScore[i][j] != outArgs->houghScore[i][j]))
            {
              fail = 1;
              break;
            }
          }
        }
        else
        {
          fail = 1;
          TEST_PRINTF("Number of circles are mismatching for radius %d, Numcircles Ref %d , target %d \n",
                                inArgs.circleProps[i%inArgs.numRadius].radius, outArgsRef->numCircles[i] , outArgs->numCircles[i]);

          break;
        }
        if ( fail == 1 )
        {
          TEST_PRINTF("Circle Info mismatches at radius=%d for circle %d  \n",inArgs.circleProps[i%inArgs.numRadius].radius,j);
        }
      }


#if ENABLE_DUMP_CIRCLE_COORDINATES
     {
       TI_FILE * fp = FOPEN("SubFrameProc_outRef.csv","w");
       FPRINTF(fp,"Radius, X, Y, Score\n");

       for ( i = 0; i < numRadius; i++ )
       {
         ptrRef    = (HOUGH_FOR_CIRCLES_TI_CircleInfo *)outArgsRef->circleInfo[i];
         for ( j = 0; j < outArgsRef->numCircles[i]; j++ )
         {
           FPRINTF(fp,"%4d,%4d,%4d,%4d\n", inArgs.circleProps[i%inArgs.numRadius].radius,ptrRef[j].centerX,ptrRef[j].centerY,outArgsRef->houghScore[i][j]);
         }
       }
       FCLOSE(fp);
     }
     {
        TI_FILE * fp = FOPEN("SubFrameProc_out.csv","w");
        FPRINTF(fp,"Radius, X, Y, Score\n");
        for ( i = 0; i < numRadius; i++ )
        {
          ptrTarget    = (HOUGH_FOR_CIRCLES_TI_CircleInfo *)outArgs->circleInfo[i];
          for ( j = 0; j < outArgs->numCircles[i]; j++ )
          {
            FPRINTF(fp,"%4d,%4d,%4d,%4d\n", inArgs.circleProps[i%inArgs.numRadius].radius,ptrTarget[j].centerX,ptrTarget[j].centerY,outArgs->houghScore[i][j]);
          }
        }
        FCLOSE(fp);
      }
#endif

#if ENABLE_OUTPUT_DUMP
    {
      if ( strcmp((const char *)testcaseParams[testcase].outputImage, ""))
      {
        TI_FILE * fp = FOPEN((const char *)testcaseParams[testcase].outputImage,"wb");
        uint8_t * circleImage;
        uint16_t x,y,k;
        circleImage = (uint8_t *)malloc (testcaseParams[testcase].imageWidth * testcaseParams[testcase].imageHeight);
        memcpy( circleImage, inBufs.bufDesc[0]->bufPlanes[0].buf, testcaseParams[testcase].imageWidth * testcaseParams[testcase].imageHeight);

        for ( i = 0; i < numRadius; i++ )
        {
          ptrRef    = (HOUGH_FOR_CIRCLES_TI_CircleInfo *)outArgsRef->circleInfo[i];
          for ( j = 0; j < outArgsRef->numCircles[i]; j++ )
          {

            for ( k = 0; k < 360; k++)
            {
              x = ptrRef[j].centerX + inArgs.circleProps[i%inArgs.numRadius].radius * cos(k);
              y = ptrRef[j].centerY + inArgs.circleProps[i%inArgs.numRadius].radius * sin(k);
              circleImage[x + y * testcaseParams[testcase].imageWidth] = 255;
            }
          }
        }

        if ( fp)
        {
          FWRITE(circleImage, testcaseParams[testcase].imageWidth * testcaseParams[testcase].imageHeight, 1, fp);
          FCLOSE(fp);
        }
      }
    }
#endif



    profiler_printStatus(fail);

    fflush(stdout);

#if ENABLE_PROFILE
#if ENABLE_TRACES
    statusStr = fail ? "FAILED":"PASSED";

TEST_PRINTF("%-20s %10s %10d %10d %10d %15.2f %20.2f %14.2f %17.2f %16.2f \
    Create graph is %2.2f Mcycles per frame but it is a one-time startup call\n",\
    "Hough for Circle",statusStr, testcaseParams[testcase].imageWidth,
    testcaseParams[testcase].imageHeight,\
    testcaseParams[testcase].numRadius, (2*profile_tsc/1000000.0), 30*(2*profile_tsc/1000000.0),\
    (profile_tsc*2.0)/(testcaseParams[testcase].imageWidth * testcaseParams[testcase].imageHeight * testcaseParams[testcase].numRadius),\
    (profile_sctm*2.0)/(testcaseParams[testcase].imageWidth * testcaseParams[testcase].imageHeight * testcaseParams[testcase].numRadius),\
    (2*profile_tsc/500000.0), (profile_create_tsc*2.0)/1000000.0);
#endif
#endif

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

   if ( outArgs != NULL )
   {
     free(outArgs);
   }

   if ( outArgsRef != NULL )
   {
     free(outArgsRef);
   }

   inBufs.bufDesc[HOUGH_FOR_CIRCLES_TI_BUFDESC_IN_EDGEMAP]->bufPlanes[0].buf = (uint8_t *)edgeImPtr;
   TestApp_FreeBufs(&inBufs, NULL);


  }
 /* Get the stack usage */
#if !(VCOP_HOST_EMULATION)
  profiler_getStackDepth();
#endif

  return status;
}

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	')||(LinePtr[0] == ','))
  {
    LinePtr++;
  }
  return(LinePtr);
}

int main(int argc, char *argv[])
{
  int status = 0;
  char configFile[FILE_NAME_SIZE]={0};
  char configLine[MAX_CONFIG_LINE_SIZE];
  char configParam[MAX_PARAM_STRING_SIZE];
  int8_t         *LinePtr;
  TI_FILE * fp;
  int32_t         lineNum = -1;
  int32_t         config_cmd;

  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,CONFIG_LIST_FILE_NAME);
  }

  report_printAppletInfo((int8_t *)"HOUGH_FOR_CIRCLE_TI_VISION");

  fp = FOPEN((const char *)configFile , "r");
  if(fp== NULL)
  {
    TEST_PRINTF("Could not open config list file : %s \n",CONFIG_LIST_FILE_NAME);
    return(status);
  }

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
      TEST_PRINTF("End of config list found !\n");
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
      TEST_PRINTF("\n Processing config file %s !\n", configFile);
      status = readparamfile(configFile, &gsTokenMap_houghForCircles[0]);
      if(status == -1)
      {
        TEST_PRINTF("Parser Failed");
        return -1 ;
      }

      profiler_testCaseInfo((int8_t *)gConfig_houghForCircles[0].testCaseName, (int8_t *)gConfig_houghForCircles[0].desc,
                            gConfig_houghForCircles[0].performanceTestcase);
      printparams(&gsTokenMap_houghForCircles[0], (int32_t)MAX_ITEMS_TO_PARSE, (uint32_t)(&gConfig_houghForCircles),
                            sizeof(sHoughForCircles_Config));

      /* Validate the applet */
      status = houghForCirclesTest(gConfig_houghForCircles);
      if(status == -1)
      {
        return status;
      }
    }
    else
    {
      TEST_PRINTF(" Unsupported config list command parameter at line num : %4d !\n", lineNum);
    }

  }

  FCLOSE(fp);


#if !(VCOP_HOST_EMULATION)
    profiler_getStackDepth();
#endif

  return status;
}



