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


/** @file edge_detector_tb.c
*
*  @brief  This file contains test code for Edge Detector applet
*
*  @date   Dec 2014
*
*  Description
*    This file contains test code to validate the frame level applet for
*    edge detector. It also checks the output against c reference outputs and
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
#include "edge_detector_config.h"
#include "xdais_types.h"
#include "iedge_detector_ti.h"

#include "ti_file_io.h"
#include "ti_mem_manager.h"
#include "eve_profile.h"
#include "vcop_sobel_xy_cn.h"
#include "math.h"

#include "vcop_yuv420_fir2d_separable_cn.h"
#include "vcop_vec_gradients_xy_and_magnitude_c.h"
#include "vcop_canny_non_maximum_suppression_cn.h"

#define ENABLE_OUTPUT_DUMP 0
#define ENABLE_EDGE_RELAXATION 0
#define ENABLE_TRACES 0
#define FIXED_PATTERN 0

#define ALIGN_T0_32(x) (((x+31)/32)*32)


#define ENABLE_PROFILE 0


#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")


#define PRINT_ERRORE_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define DMEM_SIZE (20*1024)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
/* This will be used for allocation of memory in DMEM*/
uint8_t DMEM_SCRATCH[DMEM_SIZE];


TIMemObject memObj_DMEM;

#define CEIL(x,y) ((( x + y - 1) / y) * y)

int8_t  gSobelX3x3CoeffPtr[]= {1, 0, -1,
                               2, 0, -2,
                               1, 0, -1};

int8_t  gSobelY3x3CoeffPtr[]= {+1, +2, +1,
                                0,  0, 0,
                               -1, -2, -1};

#define ALIGN_2SIMD(a)   (((a) + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))

int vcop_doublethresholding_2(
                     unsigned char *edgeMap,
                     unsigned int * strongEdgeListPtr,
                     int * numStrongEdges,
                     unsigned short width,
                     unsigned short pitch,
                     unsigned short height,
                     unsigned int pos_frm)
{
    int y;
    int x;
    int numItems;
    unsigned char value;

    numItems = *numStrongEdges;

    for (y=0; y < height; y++)
    {
        for (x=0; x < width; x++)
        {

            value = edgeMap[x+y*pitch];
            if (value == 255)
            strongEdgeListPtr[numItems++] = pos_frm + x+y*pitch;

        }
    }

    *numStrongEdges =  numItems;

    return 0;

}

#define POSSIBLE_EDGE 1

int vcop_edgeRelaxation_cn(
                     unsigned char *edgeMap,
                     unsigned int *  strongEdgeListPtr,
                     int * numStrongEdges,
                     unsigned short width)
{
    int checkLocation;

    unsigned char addTL;
    unsigned char addTC;
    unsigned char addTR;
    unsigned char addLC;
    unsigned char addRC;
    unsigned char addBL;
    unsigned char addBC;
    unsigned char addBR;

    short offsetTL;
    short offsetTC;
    short offsetTR;
    short offsetRC;
    short offsetBR;
    short offsetBC;
    short offsetBL;
    short offsetLC;

    unsigned char * mapTL;
    unsigned char * mapTC;
    unsigned char * mapTR;
    unsigned char * mapLC;
    unsigned char * mapRC;
    unsigned char * mapBL;
    unsigned char * mapBC;
    unsigned char * mapBR;
    unsigned char * mapC;

    int numItems = * numStrongEdges;

    offsetTL = - 1 - width;
    offsetTC = - 0 - width;
    offsetTR = + 1 - width;
    offsetRC = + 1;
    offsetBR = + 1 + width;
    offsetBC = - 0 + width;
    offsetBL = - 1 + width;
    offsetLC = - 1;

    checkLocation = strongEdgeListPtr[numItems - 1];

    while (--numItems)
    {
        mapC = edgeMap + checkLocation;

        mapTL = mapC + offsetTL;
        mapTC = mapC + offsetTC;
        mapTR = mapC + offsetTR;
        mapLC = mapC + offsetLC;
        mapRC = mapC + offsetRC;
        mapBR = mapC + offsetBR;
        mapBC = mapC + offsetBC;
        mapBL = mapC + offsetBL;

        addTL = (*mapTL == POSSIBLE_EDGE);
        addTC = (*mapTC == POSSIBLE_EDGE);
        addTR = (*mapTR == POSSIBLE_EDGE);
        addRC = (*mapRC == POSSIBLE_EDGE);
        addBR = (*mapBR == POSSIBLE_EDGE);
        addBC = (*mapBC == POSSIBLE_EDGE);
        addBL = (*mapBL == POSSIBLE_EDGE);
        addLC = (*mapLC == POSSIBLE_EDGE);

        *mapTL += addTL << 7;
        *mapTC += addTC << 7;
        *mapTR += addTR << 7;
        *mapRC += addRC << 7;
        *mapBR += addBR << 7;
        *mapBC += addBC << 7;
        *mapBL += addBL << 7;
        *mapLC += addLC << 7;

        strongEdgeListPtr[numItems] = checkLocation + offsetTL;
        numItems += addTL;
        strongEdgeListPtr[numItems] = checkLocation + offsetTC;
        numItems += addTC;
        strongEdgeListPtr[numItems] = checkLocation + offsetTR;
        numItems += addTR;
        strongEdgeListPtr[numItems] = checkLocation + offsetRC;
        numItems += addRC;
        strongEdgeListPtr[numItems] = checkLocation + offsetBR;
        numItems += addBR;
        strongEdgeListPtr[numItems] = checkLocation + offsetBC;
        numItems += addBC;
        strongEdgeListPtr[numItems] = checkLocation + offsetBL;
        numItems += addBL;
        strongEdgeListPtr[numItems] = checkLocation + offsetLC;
        numItems += addLC;

        checkLocation = strongEdgeListPtr[numItems - 1];
    }

  return 0;
}

void edgeDetectorCanny_cn(IVISION_InBufs * inBufs,
                         EDGE_DETECTOR_TI_CreateParams * createParams,
                         EDGE_DETECTOR_TI_InArgs        * inArgs,
                         uint8_t *outputDataPtr,
                         uint16_t outputPitch)
{
  uint8_t idx;
  uint16_t  imageWidth;
  uint16_t  imageHeight;
  uint16_t inputPitch;
  uint8_t  *inputDataPtr;
  int8_t   horzCoeffPtr[]= { 1, 2, 1};
  int8_t   vertCoeffPtr[]= { 1, 2, 1};

  int16_t   *gradX         = NULL;
  int16_t   *gradY         = NULL;
  uint16_t  *gradMag       = NULL;
  uint8_t   *gaussianImage = NULL;
  uint8_t * pIndex    = NULL;
  uint16_t * pMaxCase1 = NULL;
  uint16_t * pMaxCase2 = NULL;
  uint16_t * pMaxCase3 = NULL;
  uint16_t * pMaxCase4 = NULL;
  uint8_t lowThreshold;
  uint8_t highThreshold;

  idx = EDGE_DETECTOR_TI_BUFDESC_IN_IMAGE;

  imageWidth  =  inBufs->bufDesc[idx]->bufPlanes[0].frameROI.width;
  imageHeight =  inBufs->bufDesc[idx]->bufPlanes[0].frameROI.height;

  inputPitch = inBufs->bufDesc[idx]->bufPlanes[0].width;

  inputDataPtr = (uint8_t *)inBufs->bufDesc[idx]->bufPlanes[0].buf +
                  (inBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y *
                  inBufs->bufDesc[idx]->bufPlanes[0].width) +
                  inBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x;


  gaussianImage    = (uint8_t *) malloc ( imageWidth * imageHeight * sizeof(uint8_t));

  gradX    = (int16_t *) malloc ( imageWidth * imageHeight * sizeof(int16_t));
  gradY    = (int16_t *) malloc ( imageWidth * imageHeight * sizeof(int16_t) );
  gradMag  = (uint16_t *) malloc ( imageWidth * imageHeight * sizeof(uint16_t));
  pIndex  = (uint8_t *) malloc ( imageWidth * imageHeight * sizeof(uint8_t));
  pMaxCase1  = (uint16_t *) malloc ( imageWidth * imageHeight * sizeof(uint16_t));
  pMaxCase2  = (uint16_t *) malloc ( imageWidth * imageHeight * sizeof(uint16_t));
  pMaxCase3  = (uint16_t *) malloc ( imageWidth * imageHeight * sizeof(uint16_t));
  pMaxCase4  = (uint16_t *) malloc ( imageWidth * imageHeight * sizeof(uint16_t));

  vcop_yuv420_fir2d_separable_y_cn(inputDataPtr,
                                   horzCoeffPtr,
                                   vertCoeffPtr,
                                   imageWidth - 2,
                                   inputPitch,
                                   imageHeight - 2,
                                   3,
                                   gaussianImage,
                                   4);
  vcop_vec_gradients_xy_and_magnitude_cn(gaussianImage,
                                         gradX,
                                         gradY,
                                         (int16_t *)gradMag,
                                         ALIGN_2SIMD(imageWidth - 4),
                                         imageHeight - 4,
                                         imageWidth - 2);

  vcop_canny_bin_indexing_cn(gradX,
                             gradY,
                             pIndex,
                             imageWidth - 4,
                             imageHeight - 4,
                             ALIGN_2SIMD(imageWidth - 4));

  vcop_canny_nms_max_cases_cn(gradMag,
                              pMaxCase1,
                              pMaxCase2,
                              pMaxCase3,
                              pMaxCase4,
                              imageWidth - 6,
                              imageHeight - 6,
                              ALIGN_2SIMD(imageWidth - 4));

  lowThreshold  = inArgs->threshold1;
  highThreshold = inArgs->threshold2;

  if ( inArgs->threshold1 > inArgs->threshold2)
  {
    lowThreshold  = inArgs->threshold2;
    highThreshold = inArgs->threshold1;
  }


  vcop_canny_nms_double_thresholding_cn(pIndex,
                                        pMaxCase1,
                                        pMaxCase2,
                                        pMaxCase3,
                                        pMaxCase4,
                                        outputDataPtr,
                                        lowThreshold,
                                        highThreshold,
                                        imageWidth - 6,
                                        imageHeight - 6,
                                        ALIGN_2SIMD(imageWidth - 4),
                                        outputPitch);

  if (gradMag)
  {
    free(gradMag);
  }

  if (gradX)
  {
    free(gradX);
  }

  if (gradY)
  {
    free(gradY);
  }

  if ( pIndex)
  {
   free(pIndex);
  }
  if ( pMaxCase1)
  {
   free(pMaxCase1);
  }
  if ( pMaxCase2)
  {
   free(pMaxCase2);
  }
  if ( pMaxCase3)
  {
   free(pMaxCase3);
  }

  if ( pMaxCase4)
  {
   free(pMaxCase4);
  }

  if ( gaussianImage)
  {
   free(gaussianImage);
  }


}

void edgeDetector_cn(IVISION_InBufs * inBufs,
                         EDGE_DETECTOR_TI_CreateParams * createParams,
                         EDGE_DETECTOR_TI_InArgs        * inArgs,
                         uint8_t *outputDataPtr,
                         uint16_t outputPitch)
{
  uint8_t idx;
  uint16_t  imageWidth;
  uint16_t  imageHeight;
  uint16_t inputPitch;
  uint8_t  *inputDataPtr;
  int8_t   *gradX = NULL;
  int8_t   *gradY = NULL;
  uint16_t  computeWidth;
  uint16_t  computeHeight;

  idx = EDGE_DETECTOR_TI_BUFDESC_IN_IMAGE;

  imageWidth  =  inBufs->bufDesc[idx]->bufPlanes[0].frameROI.width;
  imageHeight =  inBufs->bufDesc[idx]->bufPlanes[0].frameROI.height;

  inputPitch = inBufs->bufDesc[idx]->bufPlanes[0].width;

  inputDataPtr = (uint8_t *)inBufs->bufDesc[idx]->bufPlanes[0].buf +
                  (inBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y *
                  inBufs->bufDesc[idx]->bufPlanes[0].width) +
                  inBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x;

  computeWidth  = imageWidth - 2;
  computeHeight = imageHeight - 2;


  gradX = (int8_t *) malloc ( computeWidth * computeHeight );
  gradY = (int8_t *) malloc ( computeWidth * computeHeight );

  vcop_sobelXY_3x3_separable_uchar_cn(inputDataPtr,
                          0,
                          0,
                          gradX,
                          gradY,
                          computeWidth,
                          computeHeight,
                          inputPitch,
                          computeWidth,
                          3);

  if ( createParams->outputFormat == EDGE_DETECTOR_TI_OUTPUT_FORMAT_BYTE_EDGEMAP)
  {
    vcop_sobelXy_3x3_L1_thresholding_cn(gradX,
                                        gradY,
                                        outputDataPtr,
                                        computeWidth,
                                        computeHeight,
                                        computeWidth,
                                        outputPitch,
                                        inArgs->threshold1);

  }
  else
  {
    vcop_sobelXy_3x3_L1_thresholding_binPack_cn(gradX,
                                        gradY,
                                        outputDataPtr,
                                        computeWidth,
                                        computeHeight,
                                        computeWidth,
                                        outputPitch,
                                        inArgs->threshold1);
  }
  if (gradX)
  {
    free(gradX);
  }

  if (gradY)
  {
    free(gradY);
  }
}

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

int32_t edgeDetectorTest(sEdgeDetector_Config * testcaseParams)
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

  uint32_t testcase;

  int32_t fail;
  TI_FILE *fp_in = NULL;


  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  EDGE_DETECTOR_TI_CreateParams   createParams;

  EDGE_DETECTOR_TI_InArgs inArgs;
  IVISION_OutArgs outArgs;

  IVISION_InBufs    inBufs;
  IVISION_OutBufs    outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc[EDGE_DETECTOR_TI_BUFDESC_IN_TOTAL];
  IVISION_BufDesc   *inBufDescList[EDGE_DETECTOR_TI_BUFDESC_IN_TOTAL];

  IVISION_BufDesc   outBufDesc[EDGE_DETECTOR_TI_BUFDESC_OUT_TOTAL];
  IVISION_BufDesc   *outBufDescList[EDGE_DETECTOR_TI_BUFDESC_OUT_TOTAL];


  /*--------------------------------------------------------------------------*/
  /*Create memory handle for ARP32 DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;
  uint8_t * outputDataPtrRef;
  uint8_t * outDataPtrTarget;
  uint32_t numBytesToCompare;
  uint8_t mask;
  uint8_t lastByteMask;
  uint8_t borderX;
  uint8_t borderY;
  /* This is just to remove warning coming from linker command file */
  vcop_minit();


  inArgs.iVisionInArgs.size   = sizeof(EDGE_DETECTOR_TI_InArgs);

  outArgs.size = sizeof(IVISION_OutArgs);

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
  TEST_PRINTF("\n%-15s %10s %15s %15s %15s %20s %16s %17s %16s    %s\n", \
    "Algorithm", "Status", "imageWidth", "imageHeight", "MegaCycPerFr", \
    "MegaCycPerSec(30Fr)", "TotalCycPerPoint", "VcopBusyCycPerPix","TimePerFr(MSec)", "Comments");


#else
  profiler_init();
#endif

  profiler_initStack(profiler_getSP());

  /*-----------------------------------------------------------------
      Set buffer descriptor pointers array base
      -----------------------------------------------------------------*/
  inBufs.bufDesc  = inBufDescList;

  inBufs.numBufs   = EDGE_DETECTOR_TI_BUFDESC_IN_TOTAL;

  for(i = 0 ; i < EDGE_DETECTOR_TI_BUFDESC_IN_TOTAL ;i++) {
    inBufDescList[i] = &inBufDesc[i];
  }

  outBufs.bufDesc = outBufDescList;
  outBufs.numBufs   = EDGE_DETECTOR_TI_BUFDESC_OUT_TOTAL;

  for(i = 0 ; i < EDGE_DETECTOR_TI_BUFDESC_OUT_TOTAL ;i++)
  {
    outBufDescList[i]     = &outBufDesc[i];
  }

  for( testcase = 0 ; testcase < edgeDetector_numTestCases; testcase++ )
  {
   createParams.method        = testcaseParams[testcase].method;
   createParams.normType      = EDGE_DETECTOR_TI_NORM_L1;
   createParams.outputFormat  = testcaseParams[testcase].outputFormat;


   /*-----------------------------------------------------------------
      Set algorithm parameters
      -----------------------------------------------------------------*/
    /*-----------------------------------------------------------------
    Query alogorithm memory requirement using standard IALG interface
    -----------------------------------------------------------------*/
    numMemRec = EDGE_DETECTOR_TI_VISION_FXNS.ialg.algNumAlloc();
    memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

    status = EDGE_DETECTOR_TI_VISION_FXNS.ialg.algAlloc(
      (IALG_Params *)(&createParams), NULL, memRec);

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    TEST_PRINTF("Edge Detector Applet Create Done\n");
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
#else
    profiler_start();
#endif

    /*-----------------------------------------------------------------
    Intialize the algorithm instance with the alocated memory
    and user create parameters
    -----------------------------------------------------------------*/
    status = EDGE_DETECTOR_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
      memRec,NULL,(IALG_Params *)(&createParams));


#if ENABLE_PROFILE
    /* Set the end point of the timing measurement for the creation process */
    t1 = _tsc_gettime();
    profile_create_tsc = (t1 - t0 - overhead);
#else
    profiler_end_print(0);
#endif

    handle = (IM_Fxns *) memRec[0].base;

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }



#if ENABLE_TRACES
    TEST_PRINTF("Edge detector Applet Init Done\n");
#endif

    idx = EDGE_DETECTOR_TI_BUFDESC_IN_IMAGE;
    inBufs.bufDesc[idx]->numPlanes                          = 1;
    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
    inBufs.bufDesc[idx]->bufPlanes[0].width                 = testcaseParams[testcase].imagePitch;
    inBufs.bufDesc[idx]->bufPlanes[0].height                = testcaseParams[testcase].imageHeight + 64;
    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = testcaseParams[testcase].imageWidth;
    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = testcaseParams[testcase].imageHeight;
    inBufs.bufDesc[idx]->bufPlanes[0].planeType             = 0;
    inBufs.bufDesc[idx]->bufPlanes[0].buf                   = NULL;

    idx = EDGE_DETECTOR_TI_BUFDESC_OUT_IMAGE_BUFFER;
    outBufs.bufDesc[idx]->numPlanes                          = 1;
    outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
    outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
    outBufs.bufDesc[idx]->bufPlanes[0].width                 = testcaseParams[testcase].outputPitch;
    outBufs.bufDesc[idx]->bufPlanes[0].height                = testcaseParams[testcase].imageHeight + 64;
    outBufs.bufDesc[idx]->bufPlanes[0].frameROI.width         = testcaseParams[testcase].imageWidth;
    outBufs.bufDesc[idx]->bufPlanes[0].frameROI.height        = testcaseParams[testcase].imageHeight;

    outBufs.bufDesc[idx]->bufPlanes[0].planeType             = 0;
    outBufs.bufDesc[idx]->bufPlanes[0].buf                   = NULL;

    inArgs.iVisionInArgs.subFrameInfo = 0;
    inArgs.iVisionInArgs.size = sizeof(EDGE_DETECTOR_TI_InArgs);
    inArgs.threshold1   = testcaseParams[testcase].threshold1;
    inArgs.threshold2   = testcaseParams[testcase].threshold2;

    status = TestApp_AllocateBufs(&inBufs, &outBufs);
    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }

    outputDataPtrRef = (uint8_t *)malloc (testcaseParams[testcase].imageWidth * testcaseParams[testcase].imageHeight);

    if(outputDataPtrRef == NULL)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }

    if ( strcmp((const char *)testcaseParams[testcase].inImage, ""))
    {
      fp_in = FOPEN((const char *)testcaseParams[testcase].inImage, "rb");

      if(fp_in == NULL)
      {
          TEST_PRINTF("Failed to open input file: %s.\n", testcaseParams[testcase].inImage);
          return -1;
      }
      FREAD(inBufs.bufDesc[EDGE_DETECTOR_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].buf,
        testcaseParams[testcase].imagePitch *testcaseParams[testcase].imageHeight, 1, fp_in);

      FCLOSE(fp_in);
    }
    else
    {
      uint8_t * ptr  = (uint8_t *) inBufs.bufDesc[EDGE_DETECTOR_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].buf;
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

#if ENABLE_TRACES
    TEST_PRINTF("Processing started for frame %d \n",0);
#endif

#if ENABLE_PROFILE
    tcntr0 = EVE_SCTM_CounterRead(CTM, SCTM_Counter_0);
    t0 = _tsc_gettime();
#else
    profiler_start();
#endif
    status = handle->ivision->algProcess((IVISION_Handle)handle,
     &inBufs,&outBufs,(IVISION_InArgs *)&inArgs, &outArgs);

#if ENABLE_PROFILE
    t1 = _tsc_gettime();

    profile_tsc = (t1 - t0 - overhead);
    tcntr1 = EVE_SCTM_CounterRead(CTM, SCTM_Counter_0);
    overflow = EVE_SCTM_OverflowCheck(CTM, SCTM_Counter_0);
    if(overflow) {
      TEST_PRINTF("Counter overflow!!!\n");
    }
    profile_sctm = ((overflow) ? (0XFFFFFFFF + tcntr1 - tcntr0) : (tcntr1 - tcntr0));
    TEST_PRINTF("TSC Cycles : SCTM %12d :% 12d\n", profile_tsc,profile_sctm);
#else
    profiler_end_print(1);
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

    if ( createParams.method == EDGE_DETECTOR_TI_METHOD_SOBEL )
    {
      edgeDetector_cn(&inBufs,
                      &createParams,
                      &inArgs,
                      outputDataPtrRef,
                      testcaseParams[testcase].outputPitch);
      borderX = 2;
      borderY = 2;
    }
    else if ( createParams.method == EDGE_DETECTOR_TI_METHOD_CANNY )
    {
      edgeDetectorCanny_cn(&inBufs,
                      &createParams,
                      &inArgs,
                      outputDataPtrRef,
                      testcaseParams[testcase].outputPitch);

      borderX = 6;
      borderY = 6;

    }

    fail = 0;
    outDataPtrTarget = (uint8_t *)outBufs.bufDesc[0]->bufPlanes[0].buf;
    numBytesToCompare = testcaseParams[testcase].imageWidth - borderX;
    mask = 0xFFU;
    lastByteMask = 0xFFU;
    if ( createParams.outputFormat == EDGE_DETECTOR_TI_OUTPUT_FORMAT_BINARY_PACK && createParams.method == EDGE_DETECTOR_TI_METHOD_SOBEL)
    {
      numBytesToCompare  = CEIL(numBytesToCompare,8);
      if ( testcaseParams[testcase].imageWidth - borderX != numBytesToCompare)
      {
        lastByteMask = 0xFFU >> (numBytesToCompare - (testcaseParams[testcase].imageWidth - borderX ));
      }
      numBytesToCompare = numBytesToCompare / 8;
    }

    for ( j = 0 ; j < testcaseParams[testcase].imageHeight - borderY ; j++)
    {
      for (i = 0; i < numBytesToCompare; i++)
      {
        if ( i < numBytesToCompare - 1 )
        {
          mask = 0xFFU;
        }
        else
        {
          mask = lastByteMask;
        }

        if ( (outputDataPtrRef[i + j * testcaseParams->outputPitch]& mask) != (outDataPtrTarget[i + j * testcaseParams->outputPitch]& mask) )
        {
          fail = 1;
          TEST_PRINTF("edgeDetector Test : Output not bit matching at (%d,%d)\n", i,j);
          goto EXIT_LOOP;
        }
      }
    }

#if ENABLE_EDGE_RELAXATION
{
  uint8_t idx;
  uint16_t  imageWidth;
  uint16_t  imageHeight;
  uint16_t inputPitch;
  uint16_t outputPitch;
  uint8_t  *inputDataPtr;
  uint32_t * strongEdgeListPtr;
  int32_t numStrongEdges = 0;
  uint32_t i,j;

  if ( testcaseParams->method == EDGE_DETECTOR_TI_METHOD_CANNY )
  {
    idx = EDGE_DETECTOR_TI_BUFDESC_IN_IMAGE;

    imageWidth  =  inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width;
    imageHeight =  inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height;

    inputPitch = inBufs.bufDesc[idx]->bufPlanes[0].width;
    outputPitch = testcaseParams[testcase].outputPitch;

    strongEdgeListPtr  = (uint32_t *) malloc( ( imageWidth - 6 ) * ( imageHeight - 6 ) * sizeof(uint32_t));
#if 1
    for ( j = 0 ; j < imageHeight - 6; j++ )
    {
      for ( i = 0 ; i < imageHeight - 6; i++ )
      {
        if ( outputDataPtrRef[i + ( j * outputPitch)] == 1 )
        {
          outputDataPtrRef[i + ( j * outputPitch)] = 127;
        }
      }
    }
#endif

    vcop_doublethresholding_2(outputDataPtrRef,
                              strongEdgeListPtr,
                              &numStrongEdges,
                              imageWidth - 6,
                              outputPitch,
                              imageHeight - 6,
                              0);

    vcop_edgeRelaxation_cn(outputDataPtrRef,strongEdgeListPtr,&numStrongEdges,outputPitch );
#if 0
    for ( j = 0 ; j < imageHeight - 6; j++ )
    {
      for ( i = 0 ; i < imageHeight - 6; i++ )
      {
          outputDataPtrRef[i + ( j * outputPitch)] = (outputDataPtrRef[i + ( j * outputPitch)] >> 7) * 255;

      }
    }
#endif
    {

      TI_FILE * fp = FOPEN("finalOutputImage.raw","wb");

      if(fp == NULL)
      {
         TEST_PRINTF("Failed to open output  file: .\n");

      }

      FWRITE(outputDataPtrRef, outputPitch * (imageHeight - 6), 1, fp);
      FCLOSE(fp);
    }
  }
}
#endif

#if ENABLE_OUTPUT_DUMP
    if ( strcmp((const char *)testcaseParams[testcase].outImage, ""))
    {
      uint8_t * edgeImage = NULL;
      uint8_t * targetOutputImage;
      targetOutputImage = (uint8_t *)outBufs.bufDesc[EDGE_DETECTOR_TI_BUFDESC_OUT_IMAGE_BUFFER]->bufPlanes[0].buf;
      edgeImage = (uint8_t *)malloc (testcaseParams[testcase].outputPitch *testcaseParams[testcase].imageHeight);
      if ( edgeImage == NULL )
      {
          TEST_PRINTF("Fail to allocate edge image for dumping\n");
          goto EXIT_LOOP;
      }

      if ( createParams.method == EDGE_DETECTOR_TI_METHOD_CANNY )
      {
        for ( j = 0 ; j < testcaseParams[testcase].imageHeight - 2 ; j++)
        {
          for (i = 0; i < numBytesToCompare; i++)
          {
            if ( targetOutputImage[i + j * testcaseParams->outputPitch] == 1 )
            {
              edgeImage[i + j * testcaseParams->outputPitch] = 255;
            }
            else
            {
              edgeImage[i + j * testcaseParams->outputPitch] = 0;
            }
          }
        }
      }
      else
      {
        memcpy(edgeImage, targetOutputImage, testcaseParams[testcase].outputPitch *testcaseParams[testcase].imageHeight);
      }

      TI_FILE * fp = FOPEN((const char *)testcaseParams[testcase].outImage,"wb");

      if(fp == NULL)
      {
         TEST_PRINTF("Failed to open output  file: %s.\n", testcaseParams[testcase].outImage);
         return -1;
      }

      FWRITE(edgeImage, testcaseParams[testcase].outputPitch *testcaseParams[testcase].imageHeight, 1, fp);

      FCLOSE(fp);

      if ( edgeImage )
      {
        free(edgeImage);
      }

    }

#endif


   fflush(stdout);

#if ENABLE_PROFILE
    statusStr = fail ? "FAILED":"PASSED";

    TEST_PRINTF("%-15s %10s %15d %15d %15.2f %20.2f %16.2f %17.2f %16.2f\
      Create graph is %2.2f MegaCycPerFr (one-time)\n",\
      "Edge Detector", statusStr, testcaseParams[testcase].imageWidth, testcaseParams[testcase].imageHeight,\
      (2*profile_tsc/1000000.0), 30*(2*profile_tsc/1000000.0),\
      (profile_tsc*2.0)/(testcaseParams[testcase].imageWidth * testcaseParams[testcase].imageHeight),\
      (profile_sctm*2.0)/(testcaseParams[testcase].imageWidth * testcaseParams[testcase].imageHeight),\
      (2*profile_tsc/500000.0), (profile_create_tsc*2.0)/1000000.0);

#else
     profiler_printStatus(fail);

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

    if ( outputDataPtrRef !=NULL)
    {
      free (outputDataPtrRef);
    }
   TestApp_FreeBufs(&inBufs, &outBufs);


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
  while((LinePtr[0] == ' ')||(LinePtr[0] == '    ')||(LinePtr[0] == ','))
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

  report_printAppletInfo((int8_t *)"EDGE_DETECTOR_TI_VISION");

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
      status = readparamfile(configFile, &gsTokenMap_edgeDetector[0]);
      if(status == -1)
      {
        TEST_PRINTF("Parser Failed");
        return -1 ;
      }

      profiler_testCaseInfo((int8_t *)gConfig_edgeDetector[0].testCaseName, (int8_t *)gConfig_edgeDetector[0].desc,
                            gConfig_edgeDetector[0].performanceTestcase);
      printparams(&gsTokenMap_edgeDetector[0], (int32_t)MAX_ITEMS_TO_PARSE, (uint32_t)(&gConfig_edgeDetector),
                            sizeof(sEdgeDetector_Config));

      /* Validate the applet */
      status = edgeDetectorTest(gConfig_edgeDetector);
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



