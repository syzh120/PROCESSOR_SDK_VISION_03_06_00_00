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


/** @file hough_for_lines_tb.c
*
*  @brief  This file contains test code for Hough For lines applet
*
*
*  @date   July 2014
*
*  Description
*    This file contains test code to validate the frame level applet hough for lines.
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
#include "hough_for_lines_config.h"
#include "xdais_types.h"
#include "ihough_for_lines_ti.h"

#include "ti_mem_manager.h"
#include "eve_profile.h"
#include "ti_file_io.h"

#include "vcop_hough_for_lines_cn.h"

#define ENABLE_OUTPUT_DUMP 0
#define ENABLE_TRACES 0
#define ENABLE_PROFILE 1
#define ALIGN_T0_32(x) (((x+31)/32)*32)

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")


#define PRINT_ERRORE_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

extern uint64_t gTest_TI_profileSctm[2], gTest_TI_profileTsc;

#define DMEM_SIZE (14*1024)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
/* This will be used for allocation of memory in DMEM*/
uint8_t DMEM_SCRATCH[DMEM_SIZE];


TIMemObject memObj_DMEM;


#define HOUGH_FOR_LINES_MAX_THETA_RANGE   (360U)
#define HOUGH_FOR_LINES_MAX_LIST_SIZE     (4000U)
#define SQRTof2_Q8      (362)
#define max(x,y)         ((x) > (y) ? (x) : (y))

int16_t sinLutQ8[HOUGH_FOR_LINES_MAX_THETA_RANGE]=
{
0, 4, 8, 13, 17, 22, 26, 31,
35, 40, 44, 48, 53, 57, 61, 66,
70, 74, 79, 83, 87, 91, 95, 99,
104, 108, 112, 116, 120, 124, 127, 131,
135, 139, 143, 146, 150, 153, 157, 161,
164, 167, 171, 174, 177, 180, 184, 187,
190, 193, 196, 198, 201, 204, 207, 209,
212, 214, 217, 219, 221, 223, 225, 228,
230, 231, 233, 235, 237, 238, 240, 242,
243, 244, 246, 247, 248, 249, 250, 251,
252, 252, 253, 254, 254, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255,
254, 254, 253, 252, 252, 251, 250, 249,
248, 247, 246, 244, 243, 242, 240, 239,
237, 235, 233, 232, 230, 228, 226, 224,
221, 219, 217, 214, 212, 209, 207, 204,
201, 199, 196, 193, 190, 187, 184, 181,
178, 174, 171, 168, 164, 161, 157, 154,
150, 147, 143, 139, 135, 132, 128, 124,
120, 116, 112, 108, 104, 100, 96, 92,
87, 83, 79, 75, 70, 66, 62, 57,
53, 49, 44, 40, 36, 31, 27, 22,
18, 13, 9, 4, 0, -4, -8, -12,
-17, -21, -26, -30, -35, -39, -44, -48,
-52, -57, -61, -65, -70, -74, -78, -82,
-87, -91, -95, -99, -103, -107, -111, -115,
-119, -123, -127, -131, -135, -139, -142, -146,
-150, -153, -157, -160, -164, -167, -170, -174,
-177, -180, -183, -186, -189, -192, -195, -198,
-201, -204, -206, -209, -211, -214, -216, -219,
-221, -223, -225, -227, -229, -231, -233, -235,
-237, -238, -240, -241, -243, -244, -245, -247,
-248, -249, -250, -251, -252, -252, -253, -254,
-254, -254, -255, -255, -255, -255, -255, -255,
-255, -255, -255, -255, -254, -254, -253, -252,
-252, -251, -250, -249, -248, -247, -246, -245,
-243, -242, -240, -239, -237, -235, -234, -232,
-230, -228, -226, -224, -222, -219, -217, -215,
-212, -210, -207, -204, -202, -199, -196, -193,
-190, -187, -184, -181, -178, -175, -171, -168,
-165, -161, -158, -154, -151, -147, -143, -140,
-136, -132, -128, -124, -120, -116, -112, -108,
-104, -100, -96, -92, -88, -84, -79, -75,
-71, -67, -62, -58, -53, -49, -45, -40,
-36, -31, -27, -23, -18, -14, -9, -5};

int16_t cosLutQ8[HOUGH_FOR_LINES_MAX_THETA_RANGE] =
{256, 255, 255, 255, 255, 255, 254, 254,
253, 252, 252, 251, 250, 249, 248, 247,
246, 244, 243, 242, 240, 239, 237, 235,
233, 232, 230, 228, 226, 223, 221, 219,
217, 214, 212, 209, 207, 204, 201, 199,
196, 193, 190, 187, 184, 181, 177, 174,
171, 168, 164, 161, 157, 154, 150, 146,
143, 139, 135, 131, 128, 124, 120, 116,
112, 108, 104, 100, 96, 91, 87, 83,
79, 75, 70, 66, 62, 57, 53, 49,
44, 40, 35, 31, 26, 22, 18, 13,
9, 4, 0, -4, -8, -13, -17, -22,
-26, -30, -35, -39, -44, -48, -52, -57,
-61, -66, -70, -74, -78, -83, -87, -91,
-95, -99, -103, -107, -111, -115, -119, -123,
-127, -131, -135, -139, -142, -146, -150, -153,
-157, -160, -164, -167, -171, -174, -177, -180,
-183, -187, -190, -192, -195, -198, -201, -204,
-206, -209, -212, -214, -216, -219, -221, -223,
-225, -227, -229, -231, -233, -235, -237, -238,
-240, -241, -243, -244, -245, -247, -248, -249,
-250, -251, -252, -252, -253, -254, -254, -254,
-255, -255, -255, -255, -255, -255, -255, -255,
-255, -255, -254, -254, -253, -252, -252, -251,
-250, -249, -248, -247, -246, -244, -243, -242,
-240, -239, -237, -235, -234, -232, -230, -228,
-226, -224, -221, -219, -217, -214, -212, -209,
-207, -204, -202, -199, -196, -193, -190, -187,
-184, -181, -178, -174, -171, -168, -164, -161,
-158, -154, -150, -147, -143, -139, -136, -132,
-128, -124, -120, -116, -112, -108, -104, -100,
-96, -92, -88, -83, -79, -75, -71, -66,
-62, -58, -53, -49, -45, -40, -36, -31,
-27, -22, -18, -14, -9, -5, 0, 3,
8, 12, 17, 21, 26, 30, 35, 39,
43, 48, 52, 56, 61, 65, 69, 74,
78, 82, 86, 91, 95, 99, 103, 107,
111, 115, 119, 123, 127, 131, 135, 138,
142, 146, 149, 153, 157, 160, 164, 167,
170, 174, 177, 180, 183, 186, 189, 192,
195, 198, 201, 204, 206, 209, 211, 214,
216, 219, 221, 223, 225, 227, 229, 231,
233, 235, 237, 238, 240, 241, 243, 244,
245, 247, 248, 249, 250, 251, 251, 252,
253, 253, 254, 254, 255, 255, 255, 255};

void TestApp_HoughForLinesBlockWiseReference
(
    uint16_t        * pEdgeMapList,
    HOUGH_FOR_LINES_TI_CreateParams * createParams,
    HOUGH_FOR_LINES_InArgs       * inArgs,
    uint16_t          srcImageWidth,
    uint16_t          srcImageHeight,
    uint16_t        * votedRhoThetaSpace
)
{
  uint32_t numListBlocks;
  uint32_t listCount;
  uint16_t theta;
  uint16_t thetaRange;
  uint16_t * currListPtr;
  uint16_t   currListBlockSize;
  uint16_t   lastBlockSize;
  int16_t pCosSinThetaMulNormQ16[2];
  int32_t  tempData;
  uint16_t normalizationFactorQ8;
  uint32_t diameterQ8;
  uint16_t * listBlock = NULL;
  uint16_t * intermIndexArray = NULL;
  uint16_t * votedRhoArrayPerTheta = NULL;
  uint16_t * votedRhoArrayPerThetaInterim = NULL;
  uint16_t * currRhoArrayForTheta;

  uint16_t  listSize;
  uint16_t  thetaStart;
  uint16_t  thetaEnd;
  uint8_t   thetaStepSize;
  uint16_t  rhoMaxLength;


  listSize      = inArgs->listSize;
  thetaStart    = inArgs->thetaStart;
  thetaEnd      = inArgs->thetaEnd;
  thetaStepSize = inArgs->thetaStepSize;
  rhoMaxLength  = inArgs->rhoMaxLength;

  diameterQ8 = SQRTof2_Q8 * max( srcImageWidth,
                                    srcImageHeight);

  normalizationFactorQ8 = (rhoMaxLength << 16) / (2 * diameterQ8);

  thetaRange = ( thetaEnd - thetaStart )/thetaStepSize;

  memset (votedRhoThetaSpace, 0 , rhoMaxLength * thetaRange * sizeof(uint16_t));

  listBlock = ( uint16_t *) malloc (HOUGH_FOR_LINES_MAX_LIST_SIZE * sizeof(uint16_t) * 2);

  intermIndexArray = (uint16_t *) malloc(HOUGH_FOR_LINES_MAX_LIST_SIZE * sizeof(uint16_t));

  votedRhoArrayPerTheta = (uint16_t *) malloc(rhoMaxLength * sizeof(uint16_t));

  votedRhoArrayPerThetaInterim = (uint16_t *) malloc(rhoMaxLength * sizeof(uint16_t));

  numListBlocks = (listSize + HOUGH_FOR_LINES_MAX_LIST_SIZE - 1U)/
                                        HOUGH_FOR_LINES_MAX_LIST_SIZE ;

  if ( listSize % HOUGH_FOR_LINES_MAX_LIST_SIZE != 0 )
  {
    lastBlockSize = listSize % HOUGH_FOR_LINES_MAX_LIST_SIZE;
  }
  else
  {
    lastBlockSize = HOUGH_FOR_LINES_MAX_LIST_SIZE;
  }

  currListBlockSize = HOUGH_FOR_LINES_MAX_LIST_SIZE;

  for ( listCount = 0 ; listCount < numListBlocks; listCount++)
  {
    currListPtr = pEdgeMapList + (listCount * HOUGH_FOR_LINES_MAX_LIST_SIZE) * 2;
    if ( listCount == numListBlocks - 1)
    {
      currListBlockSize = lastBlockSize;
    }
    /* Get current block of edge list points to work with */
    memcpy ( listBlock, currListPtr , currListBlockSize * sizeof(uint16_t) * 2);

    for ( theta = thetaStart; theta < thetaEnd; theta += thetaStepSize)
    {
      tempData = cosLutQ8[theta] * normalizationFactorQ8;
      pCosSinThetaMulNormQ16[0] = (int16_t) (tempData / 2) ;//round(tempData, 1);
          tempData = sinLutQ8[theta] * normalizationFactorQ8;
      pCosSinThetaMulNormQ16[1] = (int16_t)(tempData / 2);//round(tempData, 1);

      currRhoArrayForTheta = votedRhoThetaSpace + ( rhoMaxLength * theta ) / thetaStepSize;

      memcpy ( votedRhoArrayPerTheta, currRhoArrayForTheta, rhoMaxLength * sizeof ( uint16_t) );

      vcop_hough_for_lines_cn(listBlock,
                              pCosSinThetaMulNormQ16,
                              intermIndexArray,
                              votedRhoArrayPerThetaInterim,
                              currListBlockSize,
                              rhoMaxLength);

      vcop_merge_voted_rho_array_cn(votedRhoArrayPerThetaInterim,
                              votedRhoArrayPerTheta,
                              rhoMaxLength);

       memcpy ( currRhoArrayForTheta, votedRhoArrayPerTheta, rhoMaxLength * sizeof ( uint16_t));
    }
  }

  if ( listBlock)
  {
    free(listBlock);
    listBlock = NULL;
  }

  if ( intermIndexArray)
  {
    free(intermIndexArray);
    intermIndexArray = NULL;
  }

  if ( votedRhoArrayPerTheta)
  {
    free(votedRhoArrayPerTheta);
    votedRhoArrayPerTheta = NULL;
  }

  if ( votedRhoArrayPerThetaInterim)
  {
    free(votedRhoArrayPerThetaInterim);
    votedRhoArrayPerThetaInterim = NULL;
  }

}

void TestApp_HoughForLinesReference
(
    uint16_t        * pEdgeMapList,
    HOUGH_FOR_LINES_TI_CreateParams * createParams,
    HOUGH_FOR_LINES_InArgs       * inArgs,
    uint16_t          srcImageWidth,
    uint16_t          srcImageHeight,
    uint16_t        * votedRhoThetaSpace
)
{
  uint16_t theta;
  uint16_t thetaRange;
  int16_t pCosSinThetaMulNormQ16[2];
  int32_t  tempData;
  uint16_t normalizationFactorQ8;
  uint32_t diameterQ8;
  uint16_t * intermIndexArray = NULL;
  uint16_t * votedRhoArrayPerThetaInterim = NULL;
  uint16_t * currRhoArrayForTheta;

  uint16_t  listSize;
  uint16_t  thetaStart;
  uint16_t  thetaEnd;
  uint8_t   thetaStepSize;
  uint16_t  rhoMaxLength;


  listSize      = inArgs->listSize;
  thetaStart    = inArgs->thetaStart;
  thetaEnd      = inArgs->thetaEnd;
  thetaStepSize = inArgs->thetaStepSize;
  rhoMaxLength  = inArgs->rhoMaxLength;

  diameterQ8 = SQRTof2_Q8 * max( srcImageWidth,
                                    srcImageHeight);

  normalizationFactorQ8 = (rhoMaxLength << 16) / (2 * diameterQ8);

  thetaRange = ( thetaEnd - thetaStart )/thetaStepSize;

  memset (votedRhoThetaSpace, 0 , rhoMaxLength * thetaRange * sizeof(uint16_t));

  intermIndexArray = (uint16_t *) malloc(listSize * sizeof(uint16_t));

  votedRhoArrayPerThetaInterim = (uint16_t *) malloc(rhoMaxLength * sizeof(uint16_t));

  for ( theta = thetaStart; theta < thetaEnd; theta += thetaStepSize)
  {
    tempData = cosLutQ8[theta] * normalizationFactorQ8;
    pCosSinThetaMulNormQ16[0] = (int16_t) (tempData / 2) ;//round(tempData, 1);
        tempData = sinLutQ8[theta] * normalizationFactorQ8;
    pCosSinThetaMulNormQ16[1] = (int16_t)(tempData / 2);//round(tempData, 1);

    currRhoArrayForTheta = votedRhoThetaSpace + ( rhoMaxLength * (theta - thetaStart))/ thetaStepSize;

    vcop_hough_for_lines_cn(pEdgeMapList,
                            pCosSinThetaMulNormQ16,
                            intermIndexArray,
                            votedRhoArrayPerThetaInterim,
                            listSize,
                            rhoMaxLength);

    vcop_merge_voted_rho_array_cn(votedRhoArrayPerThetaInterim,
                            currRhoArrayForTheta,
                            rhoMaxLength);

  }

  if ( intermIndexArray)
  {
    free(intermIndexArray);
    intermIndexArray = NULL;
  }

  if ( votedRhoArrayPerThetaInterim)
  {
    free(votedRhoArrayPerThetaInterim);
    votedRhoArrayPerThetaInterim = NULL;
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
  for ( i  = 0 ; i < inBufs->numBufs ; i++)
  {
    for ( j  = 0 ; j < inBufs->bufDesc[i]->numPlanes ; j++)
    {
      inBufs->bufDesc[i]->bufPlanes[j].buf = malloc(inBufs->bufDesc[i]->bufPlanes[j].frameROI.width *
                                                         inBufs->bufDesc[i]->bufPlanes[j].frameROI.height);
      if ( inBufs->bufDesc[i]->bufPlanes[j].buf == NULL )
      {
        TEST_PRINTF("Malloc failed Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return -1;
      }
    }
  }

  for ( i  = 0 ; i < outBufs->numBufs ; i++)
  {
    for ( j  = 0 ; j < outBufs->bufDesc[i]->numPlanes ; j++)
    {
      outBufs->bufDesc[i]->bufPlanes[j].buf = malloc(outBufs->bufDesc[i]->bufPlanes[j].frameROI.width *
                                                         outBufs->bufDesc[i]->bufPlanes[j].frameROI.height);
      if ( outBufs->bufDesc[i]->bufPlanes[j].buf == NULL )
      {
        TEST_PRINTF("Malloc failed Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return -1;
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

  return status;
}

int32_t houghForLinesTest(sHoughForLines_Config * testcaseParams)
{
  uint32_t i, idx;
  int32_t numMemRec;
  IALG_MemRec *memRec;
  int32_t status;
  uint32_t seed;

  uint32_t numThetaCnt;

#if (ENABLE_PROFILE)
  uint64_t     profile_tsc, profile_sctm, profile_create_tsc;
#endif

  uint32_t testcase;
  char  *statusStr = NULL;
  int32_t fail;
  TI_FILE *fp_in = NULL;
#if ENABLE_OUTPUT_DUMP
  TI_FILE * fp_out = NULL;
#endif

  uint16_t  * votedRhoThetaSpaceRef = NULL;
  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  HOUGH_FOR_LINES_TI_CreateParams   createParams;

  HOUGH_FOR_LINES_InArgs inArgs;
  IVISION_InBufs    inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc[HOUGH_FOR_LINES_TI_BUFDESC_IN_TOTAL];
  IVISION_BufDesc   *inBufDescList[HOUGH_FOR_LINES_TI_BUFDESC_IN_TOTAL];

  HOUGH_FOR_LINES_OutArgs   outArgs;
  IVISION_OutBufs     outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   outBufDesc[HOUGH_FOR_LINES_TI_BUFDESC_OUT_TOTAL];
  IVISION_BufDesc   *outBufDescList[HOUGH_FOR_LINES_TI_BUFDESC_OUT_TOTAL];

  outArgs.iVisionOutArgs.size = sizeof(HOUGH_FOR_LINES_OutArgs);
  inArgs.iVisionInArgs.size   = sizeof(HOUGH_FOR_LINES_InArgs);
  /*--------------------------------------------------------------------------*/
  /*Create memory handle for ARP32 DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;

  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);

#if (ENABLE_PROFILE)
  profiler_init();
#endif

  /*-----------------------------------------------------------------
      Set buffer descriptor pointers array base
      -----------------------------------------------------------------*/
  inBufs.bufDesc  = inBufDescList;
  outBufs.bufDesc = outBufDescList;

  inBufs.numBufs   = HOUGH_FOR_LINES_TI_BUFDESC_IN_TOTAL;
  outBufs.numBufs  = HOUGH_FOR_LINES_TI_BUFDESC_OUT_TOTAL;

  for(i = 0 ; i < HOUGH_FOR_LINES_TI_BUFDESC_IN_TOTAL ;i++)
  {
    inBufDescList[i]     = &inBufDesc[i];
  }

  for(i = 0 ; i < HOUGH_FOR_LINES_TI_BUFDESC_OUT_TOTAL ;i++)
  {
    outBufDescList[i]     = &outBufDesc[i];
  }

  for ( testcase = 0 ; testcase < houghForLines_numTestCases; testcase++ )
  {

   /*-----------------------------------------------------------------
      Set algorithm parameters
      -----------------------------------------------------------------*/
    /*-----------------------------------------------------------------
    Query alogorithm memory requirement using standard IALG interface
    -----------------------------------------------------------------*/
#if (ENABLE_PROFILE)
     profiler_initStack(profiler_getSP());
#endif

    numMemRec = HOUGH_FOR_LINES_TI_VISION_FXNS.ialg.algNumAlloc();
    memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

    status = HOUGH_FOR_LINES_TI_VISION_FXNS.ialg.algAlloc(
      (IALG_Params *)(&createParams), NULL, memRec);

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    TEST_PRINTF("Hough For Lines Applet Create Done\n");
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

#if (ENABLE_PROFILE)
      profiler_start();
#endif

    /*-----------------------------------------------------------------
    Intialize the algorithm instance with the alocated memory
    and user create parameters
    -----------------------------------------------------------------*/
    status = HOUGH_FOR_LINES_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
      memRec,NULL,(IALG_Params *)(&createParams));


#if (ENABLE_PROFILE)
    profiler_end_print(0);
    profile_create_tsc = gTest_TI_profileTsc;
#endif

    handle = (IM_Fxns *) memRec[0].base;

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    TEST_PRINTF("Hough For Lines  Applet Init Done\n");
#endif

    numThetaCnt = ( testcaseParams[testcase].thetaEnd - testcaseParams[testcase].thetaStart ) /
                        testcaseParams[testcase].thetaStepSize;


    idx = HOUGH_FOR_LINES_TI_BUFDESC_IN_XY_LIST;
    inBufs.bufDesc[idx]->numPlanes                          = 1;
    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
    inBufs.bufDesc[idx]->bufPlanes[0].width                 = testcaseParams[testcase].listSize *
                                                                sizeof(uint16_t) * 2;
    inBufs.bufDesc[idx]->bufPlanes[0].height                = 1;
    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = inBufs.bufDesc[idx]->bufPlanes[0].width;
    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = 1;
    inBufs.bufDesc[idx]->bufPlanes[0].planeType             = 0;
    inBufs.bufDesc[idx]->bufPlanes[0].buf                   = NULL;

    idx = HOUGH_FOR_LINES_TI_BUFDESC_OUT_RHO_THETA_SPACE;
    outBufs.bufDesc[idx]->numPlanes                          = 1;
    outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
    outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
    outBufs.bufDesc[idx]->bufPlanes[0].width                 = testcaseParams[testcase].rhoMaxLength *
                                                                sizeof(uint16_t) *
                                                                numThetaCnt;
                                                                ;
    outBufs.bufDesc[idx]->bufPlanes[0].height                = 1;
    outBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = outBufs.bufDesc[idx]->bufPlanes[0].width;
    outBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = 1;
    outBufs.bufDesc[idx]->bufPlanes[0].planeType             = 0;
    outBufs.bufDesc[idx]->bufPlanes[0].buf                   = NULL;

    status = TestApp_AllocateBufs(&inBufs, &outBufs);

    if ( status != 0 )
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }

    memset(outBufs.bufDesc[idx]->bufPlanes[0].buf, 0 , outBufs.bufDesc[idx]->bufPlanes[0].width);
    votedRhoThetaSpaceRef = (uint16_t *) malloc (outBufs.bufDesc[idx]->bufPlanes[0].width);

    if ( votedRhoThetaSpaceRef == NULL)
     {
       PRINT_ERRORE_MSG();
       goto EXIT_LOOP;
     }

    inArgs.iVisionInArgs.subFrameInfo = 0;
    inArgs.iVisionInArgs.size                  = sizeof(HOUGH_FOR_LINES_InArgs);
    inArgs.listSize       = testcaseParams[testcase].listSize;
    inArgs.thetaStart     = testcaseParams[testcase].thetaStart;
    inArgs.thetaEnd       = testcaseParams[testcase].thetaEnd;
    inArgs.thetaStepSize  = testcaseParams[testcase].thetaStepSize;
    inArgs.rhoMaxLength   = testcaseParams[testcase].rhoMaxLength;
    inArgs.imgWidth       = testcaseParams[testcase].srcImageWidth;
    inArgs.imgHeight      = testcaseParams[testcase].srcImageHeight;


    if ( strcmp((const char *)testcaseParams[testcase].edgeMapList, ""))
    {
      fp_in = FOPEN((const char *)testcaseParams[testcase].edgeMapList, "rb");

      if(fp_in == NULL)
      {
          TEST_PRINTF("Failed to open input file: %s.\n", testcaseParams[testcase].edgeMapList);
          return -1;
      }
      FREAD(inBufs.bufDesc[HOUGH_FOR_LINES_TI_BUFDESC_IN_XY_LIST]->bufPlanes[0].buf,
                    testcaseParams[testcase].listSize *
                              sizeof(uint16_t) * 2, 1, fp_in);

      FCLOSE(fp_in);
    }
    else
    {
      uint16_t * ptr  = (uint16_t *) inBufs.bufDesc[HOUGH_FOR_LINES_TI_BUFDESC_IN_XY_LIST]->bufPlanes[0].buf;
      seed = (testcaseParams[testcase].randSeed == 0) ? _tsc_gettime() : testcaseParams[testcase].randSeed;
      srand(seed);

      for ( i = 0; i < 2 * testcaseParams[testcase].listSize; i+=2 )
      {
        ptr[i]    = rand() % testcaseParams[testcase].srcImageWidth;
        ptr[i+1]  = rand() % testcaseParams[testcase].srcImageHeight;
      }
    }

#if ENABLE_TRACES
    TEST_PRINTF("Processing started for frame %d \n",0);
#endif

#if (ENABLE_PROFILE)
    profiler_start();
#endif

    status = handle->ivision->algProcess((IVISION_Handle)handle,
      &inBufs,&outBufs,(IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)&outArgs);

#if (ENABLE_PROFILE)
    profiler_end_print(1);

    profile_tsc  = gTest_TI_profileTsc;
    profile_sctm = gTest_TI_profileSctm[0];
#endif

#if ENABLE_TRACES
    TEST_PRINTF("TSC Cycles : SCTM %12d :% 12d\n", profile_tsc,profile_sctm);
#endif

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
  }
#if ENABLE_TRACES
    TEST_PRINTF("Processing Completed for frame %d \n",0);
#endif

    TestApp_HoughForLinesReference(
      (uint16_t *)inBufs.bufDesc[HOUGH_FOR_LINES_TI_BUFDESC_IN_XY_LIST]->bufPlanes[0].buf,
      &createParams,
      &inArgs,
      testcaseParams[testcase].srcImageWidth,
      testcaseParams[testcase].srcImageHeight,
      votedRhoThetaSpaceRef
    );

    fail = 0;

    fail = memcmp(outBufs.bufDesc[idx]->bufPlanes[0].buf ,
      votedRhoThetaSpaceRef,
      outBufs.bufDesc[idx]->bufPlanes[0].width);

    statusStr = fail ? "FAILED":"PASSED";

    profiler_printStatus(fail);

#if (ENABLE_PROFILE)
    TEST_PRINTF("\n%-20s %10s %10s %10s %10s %15s %20s %10s %10s %16s    %s\n", \
      "Algorithm", "Status", "BaseWidth", "BaseHeight","NumLevels", "MegaCycPerFr", \
      "MegaCycPerSec(30Fr)", "TotalCycPerPix", "VcopBusyCycPerPix","TimePerFr(MSec)", "Comments");
#if (VCOP_HOST_EMULATION)
      profile_sctm = 1;
      profile_tsc = 1;
#endif

TEST_PRINTF("%-20s %10s %10d %10d %10d %15.2f %20.2f %14.2f %17.2f %16.2f \
    Create graph is %2.2f Mcycles per frame but it is a one-time startup call\n",\
    "Stage 1",statusStr, testcaseParams[testcase].srcImageWidth,
    testcaseParams[testcase].srcImageHeight,\
    1, (profile_tsc/1000000.0), 30*(profile_tsc/1000000.0),\
    (profile_tsc)/(float)(testcaseParams[testcase].listSize *numThetaCnt),\
    (profile_sctm)/(float)(testcaseParams[testcase].listSize *numThetaCnt),\
    (profile_tsc/500000.0), (profile_create_tsc)/1000000.0);

#endif

    fflush(stdout);


#if ENABLE_OUTPUT_DUMP
    if(strcmp((const char *)testcaseParams[testcase].votedRhoThetaSpace , ""))
    {
      fp_out = FOPEN((const char*)testcaseParams[testcase].votedRhoThetaSpace, "wb+");


      if(fp_out != NULL)
      {
        FWRITE(votedRhoThetaSpaceRef , testcaseParams[testcase].rhoMaxLength *
                          sizeof(uint16_t) * numThetaCnt,
                          1, fp_out);
      }
      else
      {
        TEST_PRINTF("Failed to open Output file.\n");
      }
    }
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

    if ( votedRhoThetaSpaceRef)
    {
      free(votedRhoThetaSpaceRef);
      votedRhoThetaSpaceRef = NULL;
    }

    TestApp_FreeBufs(&inBufs, &outBufs);

#if !(VCOP_HOST_EMULATION)
    profiler_getStackDepth();
#endif

  }
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

  fp = FOPEN((const char *)configFile , "r");
  if(fp== NULL)
  {
    TEST_PRINTF("Could not open config list file : %s \n",CONFIG_LIST_FILE_NAME);
    return(status);
  }

  report_printAppletInfo((int8_t *)"HOUGH_FOR_LINES_TI_VISION");

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
      status = readparamfile(configFile, &gsTokenMap_houghForLines[0]);
      if(status == -1)
      {
        TEST_PRINTF("Parser Failed");
        return -1 ;
      }
      profiler_testCaseInfo((int8_t *)gConfig_houghForLines[0].testCaseName, (int8_t *)gConfig_houghForLines[0].desc,
                            gConfig_houghForLines[0].performanceTestcase);
      printparams(&gsTokenMap_houghForLines[0], (int32_t)MAX_ITEMS_TO_PARSE, (uint32_t)(&gConfig_houghForLines[0]),
                            sizeof(sHoughForLines_Config));

      /* Validate the applet */
      status = houghForLinesTest(gConfig_houghForLines);
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

  return status;
}



