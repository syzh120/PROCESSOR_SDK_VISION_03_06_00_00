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


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "vcop_hamming_distance_cn.h"

#define PIX_SORT(a,b) { if ((a)>(b)) PIX_SWAP((a),(b)); }
#define PIX_SWAP(a,b) { uint32_t temp=(a);(a)=(b);(b)=temp; }

int32_t feature_matching_cn(
    uint8_t  *pFeatureDescriptors_1,
    uint8_t  *pFeatureDescriptors_2,
    uint16_t *pCorrespondenceList,
    uint16_t  numDescriptors1,
    uint16_t  numDescriptors2,
    uint16_t  descriptorLength,
    uint16_t  minDistanceThres,
    uint16_t  matchConfidence)  // U1.15
{
  int32_t status = 0;
  uint32_t i, j;
  uint32_t currDist, minDist0, minDist1;
  uint16_t minHamDist0, minHamDist1;
  uint32_t *pHammingDistance;

  pHammingDistance = (uint32_t *)malloc(numDescriptors2*sizeof(uint32_t));

  for(i = 0; i < numDescriptors1; i++) {
    vcop_hamming_distance_cn(pFeatureDescriptors_2, pFeatureDescriptors_1 +
         i*descriptorLength, descriptorLength, numDescriptors2, 0,
         descriptorLength, pHammingDistance, 1, 0);

    minDist0 = 0xFFFFFFFF;
    minDist1 = 0xFFFFFFFF;

    for(j = 0; j < numDescriptors2; j++) {
      currDist = pHammingDistance[j];
      PIX_SORT(minDist0, currDist);
      PIX_SORT(minDist1, currDist);
    }

    pCorrespondenceList[i] = 0xFFFF;
    minHamDist0 = minDist0 >> 16;
    minHamDist1 = minDist1 >> 16;
    if((minHamDist0 <= minDistanceThres) && (minHamDist0 <= (((1<<15) -
        matchConfidence)*minHamDist1)>>15)) {
      pCorrespondenceList[i] = (uint16_t)(minDist0 & 0x0000FFFF);
    }
  }

  free(pHammingDistance);

  return (status);
}

