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
#include "vcop_fast9score_c.h"
#include "fast9_score_bftf.h"

#include <stdlib.h>

#define N_POINTS (32)
#define MIN(a, b) ((a) < (b) ? (a) : (b))

static unsigned char lut_index_sad[136] =
{
     3,  3,  3,  3,  3,  3,  3,  3,
     4,  4,  4,  4,  4,  4,  4,  4,
    13, 13, 13, 13, 13, 13, 13, 13,
    22, 22, 22, 22, 22, 22, 22, 22,
    30, 30, 30, 30, 30, 30, 30, 30,
    38, 38, 38, 38, 38, 38, 38, 38,
    45, 45, 45, 45, 45, 45, 45, 45,
    52, 52, 52, 52, 52, 52, 52, 52,
    51, 51, 51, 51, 51, 51, 51, 51,
    50, 50, 50, 50, 50, 50, 50, 50,
    41, 41, 41, 41, 41, 41, 41, 41,
    32, 32, 32, 32, 32, 32, 32, 32,
    24, 24, 24, 24, 24, 24, 24, 24,
    16, 16, 16, 16, 16, 16, 16, 16,
     9,  9,  9,  9,  9,  9,  9,  9,
     2,  2,  2,  2,  2,  2,  2,  2,
    27, 27, 27, 27, 27, 27, 27, 27
};

static unsigned char lut_index_thresh[200] =
{
     3,  3,  3,  3,  3,  3,  3,  3,
     4,  4,  4,  4,  4,  4,  4,  4,
    13, 13, 13, 13, 13, 13, 13, 13,
    22, 22, 22, 22, 22, 22, 22, 22,
    30, 30, 30, 30, 30, 30, 30, 30,
    38, 38, 38, 38, 38, 38, 38, 38,
    45, 45, 45, 45, 45, 45, 45, 45,
    52, 52, 52, 52, 52, 52, 52, 52,
    51, 51, 51, 51, 51, 51, 51, 51,
    50, 50, 50, 50, 50, 50, 50, 50,
    41, 41, 41, 41, 41, 41, 41, 41,
    32, 32, 32, 32, 32, 32, 32, 32,
    24, 24, 24, 24, 24, 24, 24, 24,
    16, 16, 16, 16, 16, 16, 16, 16,
     9,  9,  9,  9,  9,  9,  9,  9,
     2,  2,  2,  2,  2,  2,  2,  2,
     3,  3,  3,  3,  3,  3,  3,  3,
     4,  4,  4,  4,  4,  4,  4,  4,
    13, 13, 13, 13, 13, 13, 13, 13,
    22, 22, 22, 22, 22, 22, 22, 22,
    30, 30, 30, 30, 30, 30, 30, 30,
    38, 38, 38, 38, 38, 38, 38, 38,
    45, 45, 45, 45, 45, 45, 45, 45,
    52, 52, 52, 52, 52, 52, 52, 52,
    27, 27, 27, 27, 27, 27, 27, 27
};

int FAST9ScoreCompute(
    unsigned char *src,
    unsigned short srcImageWidth,
    unsigned short srcImageHeight,
    unsigned short srcBufferPitch,
    unsigned int   * cornerListXY,
    unsigned int   cornerListSize,
    unsigned char  fast9Th,
    unsigned char  sad_method,
    unsigned short *outScore
)
{

  unsigned char *intBuf = (unsigned char *) malloc(N_POINTS * 8 *8);
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
    /* Copy 8x8 region around the key point to a linear memory           */
    /*-------------------------------------------------------------------*/
    for(k = 0 ; k < keyPoints; k++)
    {
      y = cornerListXY[i + k] & 0xFFFF ;
      x = cornerListXY[i + k] >> 16 ;

      /*-------------------------------------------------*/
      /* Come to top left of the block as x,y are center */
      /*-------------------------------------------------*/
      x -= 3 ;
      y -= 3 ;

      /*--------------------------------*/
      /* Copy the content in 8x8 region */
      /*--------------------------------*/
      for(row = 0; row < 8 ; row++)
      {
        for(col = 0; col < 8 ; col++)
        {
          tempDst  = intBuf + k*8*8 + row*8 + col ;
          tempSrc  = src    + (row + y)*srcBufferPitch + (col + x);
          *tempDst = *tempSrc ;
        }
      }
    }
    /*--------------------------------------*/
    /* Get the score of N Key points        */
    /*--------------------------------------*/

  if(sad_method)
    {
        fast9_sad_score(intBuf,
          (unsigned short)keyPoints,
          lut_index_sad,
          fast9Th,
          (outScore + i));
    }
  else
    {
      fast9_thresh_score(intBuf,
              (unsigned short)keyPoints,
              lut_index_thresh,
              fast9Th,
              (outScore+i));
    }

  }
  free(intBuf);
  return 0 ;

}

