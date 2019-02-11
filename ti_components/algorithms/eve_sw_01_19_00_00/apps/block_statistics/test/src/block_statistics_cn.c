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


/* ===========================================================================*/
/*   @file : block_statistics_cn.c                                            */
/*                                                                            */
/*   @brief  : This file contains all functions calls for block statistics    */
/*             reference                                                      */
/*                                                                            */
/*   @version 0.2 (Aug 2014) : Base version.                                  */
/*                                                                            */
/*============================================================================*/
#include "block_statistics_cn.h"

void blockStat_cn(
    BLOCK_STATISTICS_TI_CreateParams *createParams,
    uint16_t imageStride,
    uint8_t  *inbuff,
    uint8_t  *refMinOutbuff,
    uint8_t  *refMaxOutbuff,
    uint16_t *refMeanOutbuff,
    uint32_t *refVarOutbuff)
{
  unsigned short sum;
  unsigned int sqSum;
  unsigned char min, max;
  unsigned int uiRow, uiCol, uiNumPix, i, j;
  const unsigned char *pPixel;

  unsigned char *pMinimumVal = refMinOutbuff;
  unsigned char *pMaximumVal = refMaxOutbuff;
  unsigned short *pMeanVal   = refMeanOutbuff;
  unsigned int *pVarianceVal = refVarOutbuff;

  if((inbuff == NULL) || (refMinOutbuff == NULL) ||
     (refMaxOutbuff == NULL) || (refMeanOutbuff == NULL) ||
     (refVarOutbuff == NULL))
  {
    printf("ERROR!! : MEMORY ALLOCATION FAILED ");
  }
  else
  {
    for (uiRow =0; uiRow < createParams->imageHeight; uiRow = uiRow+createParams->statBlockHeight) {
      for (uiCol = 0; uiCol< createParams->imageWidth; uiCol = uiCol+createParams->statBlockWidth) {
        sum = 0;
        sqSum = 0;
        min = 255;
        max = 0;

        for (i = 0; i < createParams->statBlockWidth; i++) {
          for (j = 0; j < createParams->statBlockHeight; j++) {
            pPixel = (unsigned char*) &inbuff[(uiRow+j)*imageStride + (uiCol+i)];

            sum += *pPixel;

            sqSum += ((*pPixel) * (*pPixel));

            if(min > *pPixel) {
              min = *pPixel;
            }

            if(max < *pPixel) {
              max = *pPixel;
            }
          }
        }
        uiNumPix = (createParams->statBlockWidth * createParams->statBlockHeight);

        if (pMeanVal != NULL) {
          *(pMeanVal++) = sum;
        }

        if (pVarianceVal != NULL) {
          *(pVarianceVal++) = (unsigned int)(uiNumPix*sqSum - (int)(sum*sum));
        }

        if (pMinimumVal != NULL) {
          *(pMinimumVal++) = min;
        }

        if (pMaximumVal != NULL) {
          *(pMaximumVal++) = max;
        }
      }
    }
  }
}
