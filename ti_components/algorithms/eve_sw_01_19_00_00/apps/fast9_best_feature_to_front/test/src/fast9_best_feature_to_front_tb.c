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
*  @file       fast9_best_feature_to_front_tb.c
*
*  @version 0.0 (Dec 2013) : Base version.
*  @version 0.1 (May 2014) : Updated version
*  @version 0.2 (Oct 2014) : Updated natural C code and test bench with count of non-BFF points
*  @brief      Example file that shows the usage of Fast9 best feature to front applet
*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <vcop.h>

#include "evestarterware.h"
#include "xdais_types.h"
#include "ifast9_best_feature_to_front_ti.h"
#include "alg_osal.h"
#include "fast9_best_feature_to_front_config.h"

#include "fast9_score_bftf.h"
#include "vcop_horizontal_non_max_suppression_cn.h"
#include "vcop_vertical_non_max_suppression_cn.h"
#include "vcop_sort_cn.h"
#include "vcop_prune_big_list_cn.h"

#include "eve_profile.h"
#include "configparser.h"
#include "ti_mem_manager.h"
#include "ti_file_io.h"

#define ENABLE_TRACES 0
#define ENABLE_PROFILE (1U)

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

#define BORDER_X         3
#define BORDER_Y         3
#define DMEM_SIZE        (24*1024)
#define COMPARE_REFERENCE (1)
#define MIN(a,b) ((a) < (b) ? (a) : (b))

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
uint8_t DMEM_SCRATCH[DMEM_SIZE];

TIMemObject memObj_DMEM;

extern uint64_t gTest_TI_profileSctm[2], gTest_TI_profileTsc;

int32_t TestApp_readXyList(const char * fileName, uint32_t *pXYList, uint16_t NumFeatures);
int32_t FAST9BestFeatureToFront_cn(
  uint8_t    *src,
  uint32_t   *src_xy,
  uint8_t     threshold,
  uint8_t     sad_method,
  uint16_t    srcImageWidth,
  uint16_t    srcImageHeight,
  uint16_t    totFeatures,
  uint16_t    bestN,
  uint16_t   *scoreOutput,
  uint32_t   *output_xy,
  uint8_t    suppressionMethod
);


#pragma DATA_SECTION (testData, "EXTDMEM");
uint8_t testData[] =
{
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,242,242,249,248,250,250,250,249,249,249,248,251,244,242,0,0,0,242,242,249,248,250,250,250,249,249,249,248,251,244,242,0,0,0,242,242,249,248,250,250,250,249,249,249,248,251,244,242,0,0,0,242,242,249,248,250,250,250,249,249,249,248,251,244,242,0,0,
  0,0,0,243,245,252,251,253,253,253,252,252,252,250,254,247,242,0,0,0,243,245,252,251,253,253,253,252,252,252,250,254,247,242,0,0,0,243,245,252,251,253,253,253,252,252,252,250,254,247,242,0,0,0,243,245,252,251,253,253,253,252,252,252,250,254,247,242,0,0,
  0,0,0,244,245,252,251,253,253,253,252,252,252,250,254,247,249,0,0,0,244,245,252,251,253,253,253,252,252,252,250,254,247,249,0,0,0,244,245,252,251,253,253,253,252,252,252,250,254,247,249,0,0,0,244,245,252,251,253,253,253,252,252,252,250,254,247,249,0,0,
  0,0,0,254,246,253,252,254,254,254,253,248,255,0,0,0,0,0,0,0,254,246,253,252,254,254,254,253,248,255,0,0,0,0,0,0,0,254,246,253,252,254,254,254,253,248,255,0,0,0,0,0,0,0,254,246,253,252,254,254,254,253,248,255,0,0,0,0,0,0,
  0,0,0,243,248,255,252,244,255,247,67,0,0,0,0,252,252,252,252,255,243,248,255,252,244,255,247,67,0,0,0,0,252,252,252,252,255,243,248,255,252,244,255,247,67,0,0,0,0,252,252,252,252,255,243,248,255,252,244,255,247,67,0,0,0,0,252,252,0,0,
  0,0,0,246,245,255,255,246,255,0,0,0,0,0,252,252,252,252,255,255,246,245,255,255,246,255,0,0,0,0,0,252,252,252,252,255,255,246,245,255,255,246,255,0,0,0,0,0,252,252,252,252,255,255,246,245,255,255,246,255,0,0,0,0,0,252,252,252,0,0,
  0,0,0,248,253,255,255,0,0,0,0,0,0,0,252,252,252,255,246,255,248,253,255,255,0,0,0,0,0,0,0,252,252,252,255,246,255,248,253,255,255,0,0,0,0,0,0,0,252,252,252,255,246,255,248,253,255,255,0,0,0,0,0,0,0,252,252,252,0,0,
  0,0,0,241,254,255,255,248,251,253,253,249,254,245,0,0,0,0,0,0,241,254,255,255,248,251,253,253,249,254,245,0,0,0,0,0,0,241,254,255,255,248,251,253,253,249,254,245,0,0,0,0,0,0,241,254,255,255,248,251,253,253,249,254,245,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

#pragma DATA_SECTION (inXY, "EXTDMEM");
uint32_t inXY[] =
{
  0x30003, 0x40003, 0x50003, 0xE0003, 0xF0003, 0x100003, 0x130003, 0x140003, 0x150003, 0x160003, 0x1F0003, 0x200003, 0x210003, 0x250003, 0x260003, 0x270003,
  0x30004, 0x40004, 0x50004, 0xE0004, 0xF0004, 0x100004, 0x130004, 0x140004, 0x150004, 0x160004, 0x1F0004, 0x200004, 0x210004, 0x250004, 0x260004, 0x270004,
  0x30005, 0x40005, 0x50005, 0xE0005, 0xF0005, 0x100005, 0x130005, 0x140005, 0x150005, 0x160005, 0x1F0005, 0x200005, 0x210005, 0x250005, 0x260005, 0x270005,
  0x30006, 0x40006, 0x50006, 0xE0006, 0xF0006, 0x100006, 0x130006, 0x140006, 0x150006, 0x160006, 0x1F0006, 0x200006, 0x210006, 0x250006, 0x260006, 0x270006,
  0x30007, 0x40007, 0x50007, 0xE0007, 0xF0007, 0x100007, 0x130007, 0x140007, 0x150007, 0x160007, 0x1F0007, 0x200007, 0x210007, 0x250007, 0x260007, 0x270007,
  0x30008, 0x40008, 0x50008, 0xE0008, 0xF0008, 0x100008, 0x130008, 0x140008, 0x150008, 0x160008, 0x1F0008, 0x200008, 0x210008, 0x250008, 0x260008, 0x270008,
  0x30009, 0x40009, 0x50009, 0xE0009, 0xF0009, 0x100009, 0x130009, 0x140009, 0x150009, 0x160009, 0x1F0009, 0x200009, 0x210009, 0x250009, 0x260009, 0x270009,
  0x3000A, 0x4000A, 0x5000A, 0xE000A, 0xF000A, 0x10000A, 0x13000A, 0x14000A, 0x15000A, 0x16000A, 0x1F000A, 0x20000A, 0x21000A, 0x25000A, 0x26000A, 0x27000A
};


int32_t TestApp_readXyList(const char * fileName, uint32_t *pXYList, uint16_t NumFeatures)
{
  uint32_t X;
  uint32_t Y;
  int32_t status = 0;
  uint16_t  j;
  TI_FILE *fp = FOPEN(fileName, "r");

  if ( fp == NULL )
  {
    PRINT_ERROR_MSG();
    status = -1;
    goto EXIT;
  }

  for(j = 0; j < NumFeatures; j++)
  {
    FSCANF(fp,"%d,%d, \n",&X,&Y);
    pXYList[j] = ((X << 16) | (Y & 0xffff)) ;
  }
  FCLOSE(fp);

  EXIT:
    return status ;
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


int32_t FAST9BestFeatureToFront_cn(
  uint8_t    *src,
  uint32_t   *src_xy,
  uint8_t     threshold,
  uint8_t     score_method,
  uint16_t    srcImageWidth,
  uint16_t    srcImageHeight,
  uint16_t    totFeatures,
  uint16_t    bestN,
  uint16_t   *scoreOutput,
  uint32_t   *output_xy,
  uint8_t    suppressionMethod
)
{

  uint32_t * nms_x_corners;
  uint16_t * nms_x_score;
  uint32_t * nms_corners;
  uint32_t * nms_y_corners;
  uint16_t * nms_y_score;
  uint16_t * nms_id;
  uint32_t * nms_score;
  uint32_t i, j;
  uint32_t * bffXYout;
  uint32_t * nmsXYin;
  uint32_t * nmsXYout;
  uint32_t * nms8Wayout;
  int32_t Xcur, Ycur; 
  int32_t Xnew, Ynew; 
  int32_t absX, absY;
  uint8_t flag;
  int32_t beg[1000];
  int32_t end[1000];
  uint16_t totPoints;
  uint16_t offset;
  uint32_t nonBffCnt;
  int16_t cnt;  
  int16_t outCnt;

  nms_x_corners = (uint32_t *) malloc(totFeatures*sizeof(uint32_t));
  nms_x_score   = (uint16_t *) malloc(totFeatures*sizeof(uint16_t));
  nms_id = (uint16_t *) malloc(FAST9_BFFT_TI_MAXNUMFEATURES*sizeof(uint16_t));
  nms_y_score = (uint16_t *) malloc(FAST9_BFFT_TI_MAXNUMFEATURES*sizeof(uint16_t));
  nms_y_corners = (uint32_t *) malloc(FAST9_BFFT_TI_MAXNUMFEATURES*sizeof(uint32_t));
  nms_corners = (uint32_t *) malloc(totFeatures*sizeof(uint32_t));
  nms_score     = (uint32_t *) malloc(totFeatures*sizeof(uint32_t));
  bffXYout      = (uint32_t *) malloc(totFeatures*sizeof(uint32_t));
  nms8Wayout    = (uint32_t *) malloc(totFeatures*sizeof(uint32_t));

  if (totFeatures > 0)
  {
    /* Compute Fas9 Sad based score natural C function call*/
    FAST9ScoreCompute(src,
                     srcImageWidth,
                     srcImageHeight,
                     srcImageWidth,
                     src_xy,
                     totFeatures,
                     threshold,
                     score_method,
                     scoreOutput);

    /* Horizontal NMS natural C function call*/
    horizontal_nms(src_xy,
                   totFeatures,
                   scoreOutput,
                   nms_x_corners,
                   nms_x_score);

    /* Sort(Ascending order) natural C function call */
    /* Sort on packed XY-ID  */
    vcop_sort_cn(totFeatures, nms_x_corners, beg, end);

    /* Vertical NMS natural C function call */
    vertical_nms(nms_x_corners,
                 totFeatures,
                 nms_x_score,
                 nms_id,
                 nms_y_score,
                 (uint16_t *)nms_y_corners,
                 nms_corners,
                 nms_score);

    /* Sort(Ascending order) natural C function call */
    /* Sort the suppressed scores*/
    vcop_sort_cn(totFeatures, nms_score, beg, end);

    if(suppressionMethod)
    {
      totPoints = bestN * 1.3;
      if(totPoints > totFeatures)
      {
        totPoints = totFeatures;
      }

      offset = totFeatures - totPoints;
      vcop_prune_big_list_cn(nms_corners,
                            (uint16_t *)(nms_score + offset),
                            (uint32_t *)(nms_score + offset),
                             bffXYout,
                             &nonBffCnt,
                             0,
                             totPoints);

      nmsXYin  = (uint32_t *)bffXYout + nonBffCnt;
      nmsXYout = (uint32_t *)nms8Wayout;
      totPoints -= nonBffCnt;
      cnt = MIN(bestN - 1, totPoints);
      outCnt = MIN(bestN, totPoints);

      for(i=totPoints-1; (i>0) && (cnt>=0); i--)
      {
        Xcur = nmsXYin[i] >> 16;
        Ycur = nmsXYin[i] & 0xFFFF;

        flag = 0;

        /*-----------------------------------------------*/
        /* Read XY which have score greater than Xcur and Ycur  */
        /* and check if there is diagonal neighor                         */
        /* If so, then suppress, Xcur and Ycur                           */
        /*-----------------------------------------------*/
        for(j=i; j<totPoints; j++)
        {
            Xnew = nmsXYin[j] >> 16;
            Ynew = nmsXYin[j] & 0xFFFF;

            absX = abs(Xnew-Xcur);
            absY = abs(Ynew-Ycur);

            if(absX == 1 && absY == 1)
            {
                flag = 1;
                break;
            }
        }
        if(!flag)
            nmsXYout[cnt--] = nmsXYin[i];
      }
      memcpy(output_xy, nmsXYout+(cnt+1), (outCnt-cnt)*sizeof(uint32_t));
    }
    else
    {
      if(bestN > totFeatures)
      {
        bestN = totFeatures;
      }
      /* Since sort is in ascending order, offset needs to be computed for bestN */
      offset = totFeatures - bestN;

      vcop_prune_big_list_cn(nms_corners,
                            (uint16_t *)(nms_score + offset),
                            (uint32_t *)(nms_score + offset),
                             bffXYout,
                             &nonBffCnt,
                             0,
                             bestN);

      memcpy(output_xy, bffXYout + nonBffCnt, (bestN - nonBffCnt)*sizeof(uint32_t));
    }
  }
  else
  {
    memcpy(output_xy, src_xy, totFeatures*sizeof(uint32_t));
  }
  free(nms_x_corners);
  free(nms_x_score);
  free(nms_y_corners);
  free(nms_y_score);
  free(nms_id);
  free(nms_corners);
  free(nms_score);
  free(bffXYout);
  free(nms8Wayout);

  return 0;
}



int32_t fast9bestfeaturetofrontTest(sFast9BestFeatureToFront_Config * params)
{
  int32_t numMemRec;
  int32_t i,j;
  IALG_MemRec *memRec;
  int32_t status;
  uint8_t *input;
  uint32_t *inputXY;
  uint32_t *inputXY_natC;
  uint32_t *output;
  uint8_t *wbufToZero;
  int32_t size;
  uint16_t * natC_Scoreout;
  uint32_t * natC_XYout;
  uint32_t features_at_all_levels;
  uint32_t bestN_at_all_levels;
#if (ENABLE_PROFILE)
  uint64_t profile_tsc, profile_create_tsc, profile_sctm;
#endif
  char filepath[256];
  TI_FILE *fid;
  uint32_t numBytes;
  uint32_t testcase;
  uint8_t fail = 0;
  char  *statusStr = NULL;
  uint32_t levelCnt;

  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  FAST9_BEST_FEATURE_TO_FRONT_TI_CreateParams   createParams;

  FAST9_BEST_FEATURE_TO_FRONT_TI_InArgs    inArgs;
  IVISION_InBufs    inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc;
  IVISION_BufDesc   inXYBufDesc;
  IVISION_BufDesc   * inBufDescList[FAST9_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_TOTAL];

  FAST9_BEST_FEATURE_TO_FRONT_TI_OutArgs outArgs;
  IVISION_OutBufs   outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   outBufDesc;
  IVISION_BufDesc   * outBufDescList[FAST9_BFTF_TI_BUFDESC_OUT_TOTAL];

  outArgs.iVisionOutArgs.size = sizeof(FAST9_BEST_FEATURE_TO_FRONT_TI_OutArgs);
  inArgs.iVisionInArgs.size   = sizeof(FAST9_BEST_FEATURE_TO_FRONT_TI_InArgs);

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
  

  for( testcase = 0; testcase < numTestCases; testcase++)
  {
    /*-----------------------------------------------------------------
      Set buffer descriptor pointers array base
      -----------------------------------------------------------------*/
    inBufs.bufDesc  = inBufDescList;
    outBufs.bufDesc = outBufDescList;

    /* 2 inBufs: 1 buffer to input frame and the other to the XY list   */
    /* 1 outBuf: To store the output                                            */
    inBufs.numBufs   = FAST9_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_TOTAL;
    outBufs.numBufs  = FAST9_BFTF_TI_BUFDESC_OUT_TOTAL;

    inBufDescList[FAST9_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_IMAGEBUFFER] = &inBufDesc;
    inBufDescList[FAST9_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_XY_LIST]     = &inXYBufDesc;
    outBufDescList[FAST9_BFTF_TI_BUFDESC_OUT_XY_LIST]                    = &outBufDesc;

    /*-----------------------------------------------------------------
      Set algorithm parameters
      -----------------------------------------------------------------*/
    if(params[testcase].fileBased == 1)
    {
      createParams.visionParams.algParams.size   = sizeof(FAST9_BEST_FEATURE_TO_FRONT_TI_CreateParams);
      createParams.visionParams.cacheWriteBack   = NULL;
      createParams.maxFeatures                   = params[testcase].maxFeatures;
      createParams.maxbestNFeatures              = params[testcase].maxbestNFeatures;
      createParams.fast9Threshold                = params[testcase].fast9threshold;
      createParams.xyInIntMem                    = params[testcase].XYInDmem;
      createParams.scoreMethod                  = FAST9_BFTF_TI_THRESH_METHOD ;
    }

    else
    {
      createParams.visionParams.algParams.size   = sizeof(FAST9_BEST_FEATURE_TO_FRONT_TI_CreateParams);
      createParams.visionParams.cacheWriteBack   = NULL;
      createParams.maxFeatures                   = MAX_NUMBER_OF_FEATURES;
      createParams.maxbestNFeatures              = 64;
      createParams.fast9Threshold                = 31;
      createParams.xyInIntMem                    = XY_IN_DMEM;
      createParams.scoreMethod                   = FAST9_BFTF_TI_SAD_METHOD ;
    }

#if (ENABLE_PROFILE)
    profiler_initStack(profiler_getSP());
    profiler_start();
#endif
    /*-----------------------------------------------------------------
      Query alogorithm memory requirement using standard IALG interface
      -----------------------------------------------------------------*/
    numMemRec = FAST9_BEST_FEATURE_TO_FRONT_TI_VISION_FXNS.ialg.algNumAlloc();
    memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

    status = FAST9_BEST_FEATURE_TO_FRONT_TI_VISION_FXNS.ialg.algAlloc((IALG_Params *)(&createParams), NULL, memRec);

    if(status != IALG_EOK)
    {
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }

#if ENABLE_TRACES
    TEST_PRINTF("FAST9 BEST FEATURE TO FRONT applet Create done\n");
#endif

    /*-----------------------------------------------------------------
       Allocate memory for all the mem records
       Application has to implement the below function
       Refer the example implementation below in this file
       -----------------------------------------------------------------*/
    status = TestApp_AllocMemRecords(memRec,numMemRec);
    if(status != IALG_EOK)
    {
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }

    /*-----------------------------------------------------------------
       Intialize the algorithm instance with the alocated memory
       and user create parameters
       -----------------------------------------------------------------*/
    status = FAST9_BEST_FEATURE_TO_FRONT_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle), memRec, NULL, (IALG_Params *)(&createParams));

#if (ENABLE_PROFILE)
    /* Set the end point of the timing measurement for the creation process */
    profiler_end_print(0);
    profile_create_tsc = gTest_TI_profileTsc;
#endif
    handle = (IM_Fxns *) memRec[0].base;

    if(status != IALG_EOK)
    {
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }

#if ENABLE_TRACES
    TEST_PRINTF("FAST9 BEST FEATURE TO FRONT applet Init Done\n");
#endif

    inArgs.iVisionInArgs.subFrameInfo = 0;
    inArgs.iVisionInArgs.size         = sizeof(FAST9_BEST_FEATURE_TO_FRONT_TI_InArgs);
    inBufDesc.numPlanes               = params[testcase].numLevels;
    inXYBufDesc.numPlanes             = params[testcase].numLevels;
    outBufDesc.numPlanes              = params[testcase].numLevels;

    if(params[testcase].numLevels > 4)
    {
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }

    features_at_all_levels = 0;
    bestN_at_all_levels = 0;

    for( levelCnt = 0; levelCnt < params[testcase].numLevels; levelCnt++)
    {
      inArgs.bestNFeatures[levelCnt]           = params[testcase].bestNFeatures[levelCnt];
      inArgs.numFeaturesIn[levelCnt]           = params[testcase].total_features[levelCnt];
      inArgs.suppressionMethod                 = params[testcase].suppressionMethod;

      features_at_all_levels += params[testcase].total_features[levelCnt];           

      inBufDesc.bufPlanes[levelCnt].frameROI.topLeft.x    = 0;
      inBufDesc.bufPlanes[levelCnt].frameROI.topLeft.y    = 0;

      inBufDesc.bufPlanes[levelCnt].width                 = params[testcase].srcImageWidth[levelCnt];
      inBufDesc.bufPlanes[levelCnt].height                = params[testcase].srcImageHeight[levelCnt];
      inBufDesc.bufPlanes[levelCnt].frameROI.width        = inBufDesc.bufPlanes[levelCnt].width;
      inBufDesc.bufPlanes[levelCnt].frameROI.height       = inBufDesc.bufPlanes[levelCnt].height;

      size = (inBufDesc.bufPlanes[levelCnt].width * inBufDesc.bufPlanes[levelCnt].height);
      input = (uint8_t *)malloc(size);
      inBufDesc.bufPlanes[levelCnt].buf = (uint8_t *)input;

      if(inBufDesc.bufPlanes[levelCnt].buf == NULL)
      {
        PRINT_ERROR_MSG();
        goto EXIT_LOOP;
      }

      inXYBufDesc.bufPlanes[levelCnt].frameROI.topLeft.x    = 0;
      inXYBufDesc.bufPlanes[levelCnt].frameROI.topLeft.y    = 0;
      inXYBufDesc.bufPlanes[levelCnt].width                 = (createParams.maxFeatures)*sizeof(uint32_t);
      inXYBufDesc.bufPlanes[levelCnt].height                = 1;
      inXYBufDesc.bufPlanes[levelCnt].frameROI.width        = inXYBufDesc.bufPlanes[levelCnt].width;
      inXYBufDesc.bufPlanes[levelCnt].frameROI.height       = 1;

      size = inXYBufDesc.bufPlanes[levelCnt].width * inXYBufDesc.bufPlanes[levelCnt].height;
      inputXY = (uint32_t *) malloc(size);
      inputXY_natC = (uint32_t *)malloc(size);
      inXYBufDesc.bufPlanes[levelCnt].buf = inputXY;

      if(inXYBufDesc.bufPlanes[0].buf == NULL)
      {
        PRINT_ERROR_MSG();
        goto EXIT_LOOP;
      }

      /* Output XY list */
      outBufDesc.bufPlanes[levelCnt].frameROI.topLeft.x    = 0;
      outBufDesc.bufPlanes[levelCnt].frameROI.topLeft.y    = 0;
      outBufDesc.bufPlanes[levelCnt].width                 = (createParams.maxFeatures)*sizeof(uint32_t);
      outBufDesc.bufPlanes[levelCnt].height                = 1;
      outBufDesc.bufPlanes[levelCnt].frameROI.width        = outBufDesc.bufPlanes[levelCnt].width;
      outBufDesc.bufPlanes[levelCnt].frameROI.height       = 1;

      outBufDesc.bufPlanes[levelCnt].buf = malloc(outBufDesc.bufPlanes[levelCnt].width * outBufDesc.bufPlanes[levelCnt].height);
      if(outBufDesc.bufPlanes[levelCnt].buf == NULL)
      {
        PRINT_ERROR_MSG();
        goto EXIT_LOOP;
      }

      output = (uint32_t *)outBufDesc.bufPlanes[levelCnt].buf;

      if(params[testcase].fileBased == 1)
      {
        /* Read input image  */
        sprintf(filepath, "../testvecs/input/%s", params[testcase].inImage[levelCnt]);
        fid = FOPEN(filepath,"rb");
        if (fid == NULL)
        {
          PRINT_ERROR_MSG();
          TEST_PRINTF("Error, unable to open file %s \n", filepath);
          goto EXIT_LOOP;
        }
        input = (uint8_t * )inBufDesc.bufPlanes[levelCnt].buf;
        size = inBufDesc.bufPlanes[levelCnt].width * inBufDesc.bufPlanes[levelCnt].height;
        numBytes= FREAD(input, 1, size, fid);
        assert(numBytes== size);
        FCLOSE(fid);

        sprintf(filepath, "../testvecs/input/%s",params[testcase].inXYList[levelCnt]);
        /* Read XY list  */
        status = TestApp_readXyList(filepath,
                        (uint32_t *)inputXY,
                         params[testcase].total_features[levelCnt]);

        if(status != 0)
        {
          PRINT_ERROR_MSG();
          goto EXIT_LOOP;
        }
      }
      else
      {
        for(i=0; i<14; i++)
        {
          for(j=0; j<70; j++)
          {
            input[i*70+j] = testData[i*70+j];
          }
        }
        for(i=0; i<128; i++)
        {
          inputXY[i] = inXY[i];
        }
      }
    }
    vcop_minit();
    wbufToZero = (uint8_t *)vcop_malloc(VCOP_WMEM, 31*1024);
    memset(wbufToZero, 0, 31*1024);
    vcop_free(wbufToZero);

#if ENABLE_TRACES
    TEST_PRINTF("Processing start\n");
#endif
#if (ENABLE_PROFILE)
    profiler_start();
#endif

    status = handle->ivision->algProcess((IVISION_Handle)handle, &inBufs,&outBufs,(IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)&outArgs);

#if (ENABLE_PROFILE)
    profiler_end_print(1);
    profile_tsc = gTest_TI_profileTsc;
    profile_sctm = gTest_TI_profileSctm[0];
#endif

    if(status != IALG_EOK)
    {
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }

#if ENABLE_TRACES
    TEST_PRINTF("Processing End\n");
#endif
    fail = 0;

    for( levelCnt = 0; levelCnt < params[testcase].numLevels; levelCnt++)
    {
      /* Need to read XY list again since the inBufDesc for XY list was re-used with the applet */
      sprintf(filepath, "../testvecs/input/%s",params[testcase].inXYList[levelCnt]);
      status = TestApp_readXyList(filepath, (uint32_t *)inputXY_natC,
                              params[testcase].total_features[levelCnt]);

      if(status != 0)
      {
        PRINT_ERROR_MSG();
        goto EXIT_LOOP;
      }

      /* check if number of input features is 0, then output = NULL */
      if(params[testcase].total_features[levelCnt] <= 0 )
      {
        memcpy(output, inputXY_natC, params[testcase].total_features[levelCnt]*sizeof(uint32_t));
      }
      else
      {
        output = (uint32_t *)outBufDesc.bufPlanes[levelCnt].buf;
      }
      bestN_at_all_levels += outArgs.bestNFeaturesOut[levelCnt];

      /* Write output */
      if(params[testcase].writeOutput == 1)
      {
        sprintf(filepath,"../testvecs/output/%s", params[testcase].outXY[levelCnt]);
        fid = FOPEN(filepath, "w");
        if(fid == NULL)
        {
          TEST_PRINTF("ERROR, unable to open file %s \n", filepath);
          goto EXIT_LOOP;
        }
        numBytes = FWRITE(output, 1, outArgs.bestNFeaturesOut[levelCnt]*sizeof(uint32_t),fid);
        assert(numBytes == outArgs.bestNFeaturesOut[levelCnt]*sizeof(uint32_t));
        FCLOSE(fid);
      }

      input = (uint8_t *)inBufDesc.bufPlanes[levelCnt].buf;
      natC_Scoreout = (uint16_t *)malloc(params[testcase].total_features[levelCnt]* sizeof(uint16_t));
      natC_XYout = (uint32_t *)malloc(params[testcase].total_features[levelCnt]* sizeof(uint32_t));

      if(natC_Scoreout == NULL)
      {
        PRINT_ERROR_MSG();
        goto EXIT_LOOP;
      }
      if(natC_XYout == NULL)
      {
        PRINT_ERROR_MSG();
        goto EXIT_LOOP;
      }

      /* Call natural C implementation */
      FAST9BestFeatureToFront_cn(input,
                  inputXY_natC,
                  params[testcase].fast9threshold,
                  createParams.scoreMethod,
                  params[testcase].srcImageWidth[levelCnt],
                  params[testcase].srcImageHeight[levelCnt],
                  params[testcase].total_features[levelCnt],
                  params[testcase].bestNFeatures[levelCnt],
                  natC_Scoreout,
                  natC_XYout,
                  params[testcase].suppressionMethod);

#if ENABLE_TRACES
      for( i=0; i<params[testcase].bestNFeatures[levelCnt]; i++)
      {
        TEST_PRINTF("%d\n",natC_Scoreout);
      }

      for( i=0; i<params[testcase].bestNFeatures[levelCnt]; i++)
      {
        TEST_PRINTF("%d\n",natC_XYout);
      }
#endif

#ifdef COMPARE_REFERENCE
      fail |= memcmp(natC_XYout, output, 4*outArgs.bestNFeaturesOut[levelCnt]);
#endif

      statusStr = fail?"FAILED":"PASSED";
      if ( fail )
      {
        TEST_PRINTF("Failed at level %d \n", levelCnt);
        break;
      }
    }

    profiler_printStatus(fail);

#if (ENABLE_PROFILE)
    TEST_PRINTF("\n%-20s %10s %10s %10s %15s %20s %10s %10s %16s    %s\n", \
      "Algorithm", "Status", "Total features", "BestN features Out", "MegaCycPerFr", \
      "MegaCycPerSec(30Fr)", "TotalCycPerPix", "VcopBusyCycPerPix","TimePerFr(MSec)", "Comments");


    TEST_PRINTF("%-20s %10s %10d %10d %15.2f %20.2f %14.2f %17.2f %16.2f \
                Create graph is %2.2f Mcycles per frame but it is a one-time startup call\n",\
                "FAST9 BFTF",statusStr, features_at_all_levels, bestN_at_all_levels,\
                (profile_tsc/1000000.0), 30*(profile_tsc/1000000.0),\
                (1.0*profile_tsc)/(features_at_all_levels),\
                (1.0*profile_sctm)/(features_at_all_levels),\
                (profile_tsc/500000.0), (profile_create_tsc)/1000000.0);
#endif
  }

  fflush(stdout);

  EXIT_LOOP:
  status = handle->ivision->ialg.algFree((IALG_Handle)(handle), memRec);
  if(status != IALG_EOK)
  {
    PRINT_ERROR_MSG();
  }
  /* Here Free memory for all the mem records */
  status = TestApp_FreeMemRecords(memRec,numMemRec);
  if(status != IALG_EOK)
  {
    PRINT_ERROR_MSG();
  }
  if ( memRec != NULL )
  {
    free(memRec);
  }
  if ( input != NULL )
  {
    free(input);
  }
  if ( inputXY != NULL)
  {
    free(inputXY);
  }
  if ( output != NULL )
  {
    free(output);
  }
  if( natC_Scoreout != NULL)
  {
    free(natC_Scoreout);
  }
  if( natC_XYout != NULL)
  {
    free(natC_XYout);
  }
  if ( inputXY_natC != NULL)
  {
    free(inputXY_natC);
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

int32_t main(int argc, char *argv[])
{
  int status = 0;
  char configFile[FILE_NAME_SIZE]={0};
  char configLine[MAX_CONFIG_LINE_SIZE];
  char configParam[MAX_PARAM_STRING_SIZE];
  int8_t *LinePtr;
  TI_FILE * fp;
  int32_t lineNum = -1;
  int32_t config_cmd;

  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,CONFIG_LIST_FILE_NAME);
  }

  report_printAppletInfo((int8_t *)"FAST9_BFTF_TI_VISION");

  fp = FOPEN((const char *)configFile, "r");
  if (fp == NULL)
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
      status = readparamfile(configFile, &gsTokenMap_Fast9BestFeatureToFront[0]);
      if(status == -1)
      {
        TEST_PRINTF("Parser Failed");
        return -1 ;
      }

      profiler_testCaseInfo((int8_t *)gConfig_Fast9BestFeatureToFront[0].testCaseName, (int8_t *)gConfig_Fast9BestFeatureToFront[0].desc,
                            gConfig_Fast9BestFeatureToFront[0].performanceTestcase);
      printparams(&gsTokenMap_Fast9BestFeatureToFront[0], (int32_t)MAX_ITEMS_TO_PARSE, (uint32_t)(&gConfig_Fast9BestFeatureToFront),
                            sizeof(sFast9BestFeatureToFront_Config));

      /* Validate the applet */
        status = fast9bestfeaturetofrontTest(gConfig_Fast9BestFeatureToFront);
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
