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


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include <vcop.h>
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_hough_for_circles_config.h"


/* ------------------------------------------------------------------------ */
/*  Include prototypes for "C" implementation of Hough for Circles kernel   */
/*  function.                                                               */
/* ------------------------------------------------------------------------ */
#include "vcop_hough_for_circles_cn.h"


#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_hough_for_circles_kernel.k"
#else
#include "../inc/vcop_hough_for_circles_kernel.h"
#endif

//#define __DEBUG
#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)

void fillDefaultConfig(sHough_for_circles_Config * params)
{
  strcpy(params->gradDir, "");
  strcpy(params->xyList, "");
  strcpy(params->houghIdx, "");

  params->testCase            = 1;

  // common parameters
  params->listSize            = 32;
  params->imgWidth            = 48;
  params->imgHeight           = 48;

  // parameters for compute index
  params->radius              = 16;
  params->houghSpaceDownScale = 2;

  // parameter for circle detection
  params->houghScoreThreshold = 10;

  params->randSeedGrad        = 0;
  params->randSeedXY          = 0;
  params->randSeedHoughIdx    = 0;
  params->numIter             = 1;
}


int32_t houghForCirclesCompIdxTest(sHough_for_circles_Config * testcaseParams)
{
  int32_t fail, status = 0;
  uint32_t seed;
  FILE *fp_in = NULL, *fp_out = NULL;
  int32_t i, iter;
  int8_t x, y;
  uint8_t shift, downScaleFactor;

  int16_t  *pUnitGradXY, *pScratch;
  uint16_t *pXYList, *pOutHoughIdx, *pRefHoughIdx;
  uint32_t numEdgePoints;
  uint16_t houghSpaceWidth;
  uint16_t houghSpaceHeight;

  profiler_init();
  vcop_minit();

  printf("Testing Hough for Circle: Compute Hough Space Index Kernel:\n");

  numEdgePoints = ((testcaseParams->listSize + 15)/16)*16;

#if VCOP_HOST_EMULATION
  /* Multiplication by two because it stores x and y coordinate in packed format*/
  pUnitGradXY  = (int16_t *)malloc(numEdgePoints*2*sizeof(int16_t));
  pXYList      = (uint16_t *)malloc(numEdgePoints*2*sizeof(uint16_t));
  pScratch     = (int16_t *)malloc(numEdgePoints*2*sizeof(int16_t));
  pOutHoughIdx = (uint16_t *)malloc(numEdgePoints*sizeof(uint16_t));
#else
  pUnitGradXY  = (int16_t *)vcop_malloc(VCOP_IBUFLA, numEdgePoints*2*sizeof(int16_t));
  pXYList      = (uint16_t *)vcop_malloc(VCOP_IBUFHA, numEdgePoints*2*sizeof(uint16_t));
  pScratch     = (int16_t *)vcop_malloc(VCOP_WMEM, numEdgePoints*2*sizeof(int16_t));
  pOutHoughIdx = (uint16_t *)vcop_malloc(VCOP_IBUFHA, numEdgePoints*sizeof(uint16_t));
#endif
  pRefHoughIdx = (uint16_t *)malloc(numEdgePoints*sizeof(uint16_t));

  for(iter = 0; iter < testcaseParams->numIter; iter++)
  {
    printf("Iteration %d\n", iter);
    fail = 0;

    if(strcmp(testcaseParams->gradDir, "")) {
      printf("File Test\n");
      fp_in = fopen((const char *)testcaseParams->gradDir, "rb");

      if(fp_in == NULL) {
        printf("Failed to open input file: %s.\n", testcaseParams->gradDir);
        return -1;
      }

      fread(pUnitGradXY, testcaseParams->listSize*2, sizeof(int16_t), fp_in);
      fclose(fp_in);
    }
    else {
      /* Generate input data */
      seed = (testcaseParams->randSeedGrad == 0) ? _tsc_gettime() : testcaseParams->randSeedGrad;
      srand(seed);
      printf("Random pattern test: Seed = %d\n", seed);
      for(i = 0; i < testcaseParams->listSize; i++) {
        x = rand() & 0xFF;
        y = rand() & 0xFF;
        pUnitGradXY[2*i] = (int16_t)(x/sqrt(x*x + y*y));
        pUnitGradXY[2*i + 1] = (int16_t)(y/sqrt(x*x + y*y));
      }
    }

    if(strcmp(testcaseParams->xyList, "")) {
      printf("File Test\n");
      fp_in = fopen((const char *)testcaseParams->xyList, "rb");

      if(fp_in == NULL) {
        printf("Failed to open input file: %s.\n", testcaseParams->xyList);
        return -1;
      }

      fread(pXYList, testcaseParams->listSize*2, sizeof(uint16_t), fp_in);
      fclose(fp_in);
    }
    else {
      /* Generate input data */
      seed = (testcaseParams->randSeedXY == 0) ? _tsc_gettime() : testcaseParams->randSeedXY;
      srand(seed);
      printf("Random pattern test: Seed = %d\n", seed);
      for(i = 0; i < testcaseParams->listSize; i++) {
        pXYList[2*i] = rand() % testcaseParams->imgHeight;
        pXYList[2*i + 1] = rand() % testcaseParams->imgWidth;
      }
    }

    downScaleFactor = testcaseParams->houghSpaceDownScale;
    shift = 0;
    while(downScaleFactor > 1) {
      shift++;
      if(downScaleFactor % 2 != 0) {
        printf("houghSpaceDownScale should be a power of 2.\n");
        return -1;
      }
      downScaleFactor >>= 1;
    }
    houghSpaceWidth  = (testcaseParams->imgWidth  + (1<<shift) - 1)>>shift;
    houghSpaceHeight = (testcaseParams->imgHeight + (1<<shift) - 1)>>shift;

    profiler_start();
    vcop_hough_circle_compute_idx(pUnitGradXY, pXYList, pScratch, pOutHoughIdx,
      testcaseParams->listSize, testcaseParams->radius, shift, houghSpaceWidth , houghSpaceHeight ,houghSpaceWidth);
    profiler_end();

    vcop_hough_circle_compute_idx_cn(pUnitGradXY, pXYList, pRefHoughIdx,
      testcaseParams->listSize, testcaseParams->radius, shift,houghSpaceWidth, houghSpaceHeight, houghSpaceWidth);

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/
    fail = memcmp(pOutHoughIdx, pRefHoughIdx , testcaseParams->listSize*sizeof(uint16_t));

    fp_out = fopen((const char*)testcaseParams->houghIdx, "w");
    if(fp_out != NULL) {
      fwrite(pOutHoughIdx, testcaseParams->listSize, sizeof(uint16_t), fp_out);
      fclose(fp_out);
    }

    if(fail != 0) {
      for(i = 0; i < testcaseParams->listSize; i++) {
        if(pOutHoughIdx[i] != pRefHoughIdx[i]) {
          printf("Mismatch at %d: Output = %d, Expected = %d\n", i,
            pOutHoughIdx[i], pRefHoughIdx[i]);
        }
      }
    }

    printf(fail ? "FAIL\n":"PASS\n");
    status |= fail;
  }

#if !(VCOP_HOST_EMULATION)
    vcop_free(pUnitGradXY);
    vcop_free(pXYList);
    vcop_free(pScratch);
    vcop_free(pOutHoughIdx);
#endif

  profiler_deinit();

  printf(status ? "\nFAIL\n" : "\nPASS\n");

  return (status);
}


int32_t houghForCirclesDetectCirclesTest(sHough_for_circles_Config * testcaseParams)
{
  int32_t fail, status = 0;
  uint32_t seed;
  FILE *fp_in = NULL;
  int32_t i, iter;
  uint8_t shift, downScaleFactor;

  uint16_t houghSpaceWidth, houghSpaceHeight, houghSpacePitch;
  uint16_t *pHoughIdx;
  uint8_t  *pHoughSpace, *pHoughScoreList;
  uint8_t  *pHoughSpaceRef, *pHoughScoreListRef;
  uint32_t *pUpperLeftXY, *xSequence, *pCenterListXY, *pCenterListXYRef;
  uint16_t *pNumCircles, *pNumCirclesRef;

  profiler_init();
  vcop_minit();

  printf("Testing Hough for Circle - Circle Detect Kernels:\n");

  downScaleFactor = testcaseParams->houghSpaceDownScale;
  shift = 0;
  while(downScaleFactor > 1) {
    shift++;
    if(downScaleFactor % 2 != 0) {
      printf("houghSpaceDownScale should be a power of 2.\n");
      return -1;
    }
    downScaleFactor >>= 1;
  }
  houghSpaceWidth = (testcaseParams->imgWidth + (1<<shift) - 1)>>shift;
  houghSpaceHeight = (testcaseParams->imgHeight + (1<<shift) - 1)>>shift;

  houghSpacePitch = 8*((houghSpaceWidth + 7)/8);

#if VCOP_HOST_EMULATION
  pHoughIdx = (uint16_t *)malloc(testcaseParams->listSize*sizeof(uint16_t));
  pHoughSpace = (uint8_t *)malloc(houghSpaceHeight*houghSpacePitch);
  pUpperLeftXY = (uint32_t *)malloc(sizeof(uint32_t));
  xSequence = (uint32_t *)malloc(sizeof(uint32_t)*houghSpacePitch);
  pNumCircles = (uint16_t *)malloc(8*sizeof(uint16_t));
  pCenterListXY = (uint32_t *)malloc(testcaseParams->listSize*sizeof(uint32_t));
  pHoughScoreList = (uint8_t *)malloc(testcaseParams->listSize);
#else
  pHoughIdx = (uint16_t *)vcop_malloc(VCOP_IBUFLA, testcaseParams->listSize*sizeof(uint16_t));
  pHoughSpace = (uint8_t *)vcop_malloc(VCOP_WMEM, houghSpaceHeight*houghSpacePitch);
  pUpperLeftXY = (uint32_t *)vcop_malloc(VCOP_IBUFLA, sizeof(uint32_t));
  xSequence = (uint32_t *)vcop_malloc(VCOP_WMEM, sizeof(uint32_t)*houghSpacePitch);
  pNumCircles = (uint16_t *)vcop_malloc(VCOP_IBUFLA, 8*sizeof(uint16_t));
  pCenterListXY = (uint32_t *)vcop_malloc(VCOP_IBUFHA, testcaseParams->listSize*sizeof(uint32_t));
  pHoughScoreList = (uint8_t *)vcop_malloc(VCOP_IBUFLA, testcaseParams->listSize);
#endif
  pHoughSpaceRef = (uint8_t *)malloc(32*(((houghSpacePitch*houghSpaceHeight + 3)/4 + 7)/8));
  pNumCirclesRef = (uint16_t *)malloc(sizeof(uint16_t));
  pCenterListXYRef = (uint32_t *)malloc(testcaseParams->listSize*sizeof(uint32_t));
  pHoughScoreListRef = (uint8_t *)malloc(testcaseParams->listSize);

  for(iter = 0; iter < testcaseParams->numIter; iter++)
  {
    printf("Iteration %d\n", iter);
    fail = 0;

    if(strcmp(testcaseParams->houghIdx, "")) {
      printf("File Test\n");
      fp_in = fopen((const char *)testcaseParams->houghIdx, "rb");

      if(fp_in == NULL) {
        printf("Failed to open input file: %s.\n", testcaseParams->houghIdx);
        return -1;
      }

      fread(pHoughIdx, testcaseParams->listSize, sizeof(uint16_t), fp_in);
      fclose(fp_in);
    }
    else {
      /* Generate input data */
      seed = (testcaseParams->randSeedHoughIdx == 0) ? _tsc_gettime() : testcaseParams->randSeedHoughIdx;
      srand(seed);
      printf("Random pattern test: Seed = %d\n", seed);
      for(i = 0; i < testcaseParams->listSize; i++) {
        pHoughIdx[i] = (int16_t)(rand() % (houghSpaceHeight * houghSpacePitch));
      }
    }

    profiler_start();
    vcop_hough_circle_init_hough_space((uint32_t*)pHoughSpace, houghSpacePitch,
      houghSpaceHeight);
    profiler_end();

    memset(pHoughSpaceRef, 0, 32*(((houghSpacePitch*houghSpaceHeight + 3)/4 + 7)/8));

    profiler_start();
    vcop_hough_circle_vote_to_hough_space(pHoughIdx, pHoughSpace,
      testcaseParams->listSize);
    profiler_end();

    vcop_hough_circle_vote_to_hough_space_cn(pHoughIdx, pHoughSpaceRef,
      testcaseParams->listSize);

    fail |= memcmp(pHoughSpace, pHoughSpaceRef, houghSpaceHeight*houghSpacePitch);

    ((uint16_t*)pUpperLeftXY)[0] = testcaseParams->startY;
    ((uint16_t*)pUpperLeftXY)[1] = testcaseParams->startX;
    for(i = 0; i < houghSpacePitch; i++) {
      ((uint16_t*)xSequence)[2*i] = 0;
      ((uint16_t*)xSequence)[2*i + 1] = (i << shift);
    }

    profiler_start();
    vcop_hough_for_circle_detect(pHoughSpace, pUpperLeftXY, xSequence, pNumCircles,
      pCenterListXY, pHoughScoreList, testcaseParams->houghScoreThreshold,
      houghSpaceWidth, houghSpaceHeight, houghSpacePitch, shift);
    profiler_end();

    vcop_hough_for_circle_detect_cn(pHoughSpaceRef, pUpperLeftXY, xSequence,
      pNumCirclesRef, pCenterListXYRef, pHoughScoreListRef,
      testcaseParams->houghScoreThreshold, houghSpaceWidth, houghSpaceHeight,
      houghSpacePitch, shift);

    fail |= (pNumCirclesRef[0] != pNumCircles[0]);

    fail |= memcmp(pCenterListXYRef, pCenterListXY, 4*pNumCircles[0]);

    fail |= memcmp(pHoughScoreListRef, pHoughScoreList, pNumCircles[0]);

    printf("Number of Circles Detected = %d\n", pNumCircles[0]);
#if 0
    for(i = 0; i < pNumCircles[0]; i++) {
      printf("Center: (%d, %d), Score: %d\n", ((uint16_t*)pCenterListXY)[2*i], ((uint16_t*)pCenterListXY)[2*i+1], pHoughScoreList[i]);
    }
#endif

    printf(fail ? "FAIL\n":"PASS\n");
    status |= fail;
  }

#if !(VCOP_HOST_EMULATION)
    vcop_free(pHoughIdx);
    vcop_free(pHoughSpace);
    vcop_free(pUpperLeftXY);
    vcop_free(xSequence);
    vcop_free(pNumCircles);
    vcop_free(pCenterListXY);
    vcop_free(pHoughScoreList);
#endif

  profiler_deinit();

  printf(status ? "\nFAIL\n" : "\nPASS\n");

  return (status);
}


char* moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	')||(LinePtr[0] == ',')) {
    LinePtr++;
  }
  return(LinePtr);
}

int32_t main(int32_t argc, char *argv[])
{
  int status = 0;
  char configFile[FILE_NAME_SIZE]={0};
  char configLine[MAX_CONFIG_LINE_SIZE];
  char configParam[MAX_PARAM_STRING_SIZE];
  int8_t *LinePtr;
  FILE *fp;
  int32_t lineNum = -1, config_cmd;

  if (argc > 1) {
    strcpy(configFile, argv[1]) ;
  }
  else {
    strcpy(configFile, "../testvecs/config/config_list.txt");
  }

  fp = fopen((const char *)configFile , "r");
  if(fp== NULL) {
    printf("Could not open config list file : %s \n", configFile);
    return(status);
  }

  while(1) {
    memset(configLine, 0, MAX_CONFIG_LINE_SIZE);
    status = (int)fgets(configLine,MAX_CONFIG_LINE_SIZE,fp);
    LinePtr = (int8_t *)configLine;
    if ((status == EOF) || (status == 0)) {
      break;
    }

    status = 0;
    lineNum++;
    sscanf((const char *)LinePtr, "%d",&config_cmd);
    sscanf((const char *)LinePtr, "%s",configParam);

    if(config_cmd == 0) {
      printf("End of config list found !\n");
      break;
    }
    else if(config_cmd == 2) {
      continue;
    }
    else if(config_cmd == 1) {
      LinePtr = (int8_t *)moveToNextElement(configParam,(char *)LinePtr);
      status  = sscanf((const char *)LinePtr, "%s",configFile);
      printf("\nProcessing config file %s !\n", configFile);
      status = readparamfile(configFile, &gsTokenMap_hough_for_circles[0]);
      if(status == -1) {
        printf("Parser Failed");
        return -1 ;
      }

      /* Validate the kernel */
      if(gConfig_hough_for_circles.testCase == 1) {
        status = houghForCirclesCompIdxTest(&gConfig_hough_for_circles);
      }
      else {
        status = houghForCirclesDetectCirclesTest(&gConfig_hough_for_circles);
      }
      if(status == -1) {
        return status;
      }
    }
    else {
      printf("Unsupported config list command parameter at line num : %4d !\n", lineNum);
    }
  }

  fclose(fp);

  return status;
}

