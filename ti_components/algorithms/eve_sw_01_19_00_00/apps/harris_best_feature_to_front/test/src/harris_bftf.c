/*
*
* Copyright (c) 2013-2017 Texas Instruments Incorporated
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


#include "stdint.h"
#include "vcop_extract_bit_field_u32_cn.h"
#include "vcop_prune_big_list_cn.h"
#include "vcop_sort_cn.h"
#include "vcop_multipoint_harrisScore_u16_cn.h"

#include <stdlib.h>
#include <string.h>

#define MAX_LEVELS (4)

#define N_POINTS (32)
#define MIN(a, b) ((a) < (b) ? (a) : (b))

static int32_t beg[1000];
static int32_t end[1000];

static int HarrisScoreCompute(
    unsigned char *src,
    unsigned short srcImageWidth,
    unsigned short srcImageHeight,
    unsigned short srcBufferPitch,
    unsigned int   * cornerListXY,
    unsigned int   cornerListSize,
    unsigned short  sensitivityParam,
    unsigned short  start_id,
    unsigned short *pHarrisScore
)
{

  unsigned char *intBuf = (unsigned char *) malloc(N_POINTS * 9 *9);
  short x, y, row, col ;
  unsigned char *tempSrc, *tempDst ;
  unsigned int i, keyPoints, k ;

  for(i =0 ; i < cornerListSize ; i+= N_POINTS)
  {
    /*-------------------------------------------------------------------*/
    /* Do N points together and take care of last if N are not remaining */
    /*-------------------------------------------------------------------*/
    keyPoints  = MIN(N_POINTS, cornerListSize - i);

    /*-------------------------------------------------------------------*/
    /* Copy 9x9 region around the key point to a linear memory           */
    /*-------------------------------------------------------------------*/
    for(k = 0 ; k < keyPoints; k++)
    {
      y = cornerListXY[i + k] & 0xFFFF ;
      x = cornerListXY[i + k] >> 16 ;

      /*-------------------------------------------------*/
      /* Come to top left of the block as x,y are center */
      /*-------------------------------------------------*/
      x -= 4 ;
      y -= 4 ;

      /*--------------------------------*/
      /* Copy the content in 8x8 region */
      /*--------------------------------*/
      for(row = 0; row < 9 ; row++)
      {
        for(col = 0; col < 9 ; col++)
        {
          tempDst  = intBuf + k*9*9 + row*9 + col ;
          tempSrc  = src    + (row + y)*srcBufferPitch + (col + x);
          *tempDst = *tempSrc ;
        }
      }
    }

    /*--------------------------------------*/
    /* Get the score of N Key points        */
    /*--------------------------------------*/
    vcop_multipoint_harrisScore_u16_cn(
      intBuf,
      pHarrisScore,
      keyPoints,
      7,
      7,
      9,
      81,
      sensitivityParam,
      start_id
      );
    pHarrisScore += 2*keyPoints ;
    start_id += keyPoints  ;
  }

  free(intBuf);
  return 0 ;

}

int HarrisScoreBestFeatureToFront(
    unsigned char *src[],
    unsigned int  *cornerListXY[],
    unsigned int   cornerListSize[],
    unsigned short srcImageWidth,
    unsigned short srcImageHeight,
    unsigned short srcBufferPitch,
    unsigned short sensitivityParam,
    unsigned int  *cornerListXYOut,
    unsigned char *cornerListLevelOut,
    unsigned char  numLevels,
    unsigned int   bestN
)
{
  int i, j;
  unsigned short  start_id;
  unsigned short *pHarrisScore, *pHarrisScoreBase;
  unsigned int *pXYList;
  unsigned int nonBffCnt;
  unsigned int totalPoints;
  int offset;

  pXYList = (unsigned int *)malloc(2048*sizeof(unsigned int)*numLevels);

  totalPoints = 0;
  for (i= 0; i < numLevels; i++)
  {
    totalPoints += cornerListSize[i];
  }

  if(bestN < totalPoints)
  {

    pHarrisScore = pHarrisScoreBase = (unsigned short *)malloc(totalPoints * sizeof(unsigned int));

    for (i= 0; i < numLevels ; i++)
    {
      start_id = (i << 11) ;
      HarrisScoreCompute(
        src[i],
        srcImageWidth >> i,
        srcImageHeight >> i,
        srcBufferPitch >> i,
        cornerListXY[i],
        cornerListSize[i],
        sensitivityParam,
        start_id,
        pHarrisScore
        );

      memcpy(pXYList + i*2048, cornerListXY[i], cornerListSize[i]*4);

      pHarrisScore += 2*cornerListSize[i] ;
    }

    /*------------------------------------------------------------------------*/
    /* In: pHarrisScoreBase = 32-bit element array = 4*totalPoints (size)     */
    /* Out: pHarrisScoreBase - sorted In place write                          */
    /* beg and end are 1000 elements scratch array                            */
    /*------------------------------------------------------------------------*/
    vcop_sort_cn(totalPoints, (unsigned int *)pHarrisScoreBase, beg, end) ;

    offset = totalPoints - bestN ;
    vcop_prune_big_list_cn(pXYList, (unsigned short*) pHarrisScoreBase + offset*2, (unsigned int*) pHarrisScoreBase + offset*2, cornerListXYOut, &nonBffCnt, 0, bestN);
    vcop_extract_bit_field_u32_cn((unsigned int *)pHarrisScoreBase + offset, bestN, 0xFFFF, 11, cornerListLevelOut);

    free(pHarrisScoreBase);
  }
  else
  {
    offset = 0 ;
    for (i= 0; i < numLevels; i++)
    {
      memcpy(cornerListXYOut + offset, cornerListXY[i], 4*cornerListSize[i]);

      /* Prepare level id list */
      for(j = 0; j < cornerListSize[i]; j++) {
        cornerListLevelOut[offset + j] = i;
      }

      offset += cornerListSize[i] ;
    }
  }

  free(pXYList);

  return 0;

}

