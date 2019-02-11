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


#ifndef FAST9_BEST_FEATURE_TO_FRONT_CONFIG_H_
#define FAST9_BEST_FEATURE_TO_FRONT_CONFIG_H_

#pragma CHECK_MISRA ("none")
#include "configparser.h"
#include "stdint.h"
#pragma RESET_MISRA ("required")
#include <xdais_types.h>
#include "ifast9_best_feature_to_front_ti.h"

#define FILE_NAME_SIZE           (300)
#define DESCRIPTION_SIZE  (256)
#define FAST9_BFTF_NUM_MAX_TESTCASES 20

#define XY_IN_DMEM               (1)
#define MAX_NUMBER_OF_FEATURES   (256)


typedef struct
{
  uint8_t  inImage[FAST9_BFFT_TI_MAXLEVELS][FILE_NAME_SIZE];
  uint8_t  inXYList[FAST9_BFFT_TI_MAXLEVELS][FILE_NAME_SIZE];
  uint32_t outXY[FAST9_BFFT_TI_MAXLEVELS][FILE_NAME_SIZE];
  uint16_t srcImageWidth[FAST9_BFFT_TI_MAXLEVELS];
  uint16_t srcImageHeight[FAST9_BFFT_TI_MAXLEVELS];
  uint16_t total_features[FAST9_BFFT_TI_MAXLEVELS];
  uint8_t  fast9threshold;
  uint16_t bestNFeatures[FAST9_BFFT_TI_MAXLEVELS];
  uint8_t  numLevels;
  uint8_t  XYInDmem;
  uint8_t  fileBased;
  uint8_t  writeOutput;
  uint16_t maxFeatures;
  uint16_t maxbestNFeatures;
  uint8_t  suppressionMethod;
  uint8_t  testCaseName[FILE_NAME_SIZE];
  uint8_t  performanceTestcase;
  uint8_t  desc[DESCRIPTION_SIZE];
} sFast9BestFeatureToFront_Config;

extern uint32_t numTestCases;
extern sFast9BestFeatureToFront_Config gConfig_Fast9BestFeatureToFront[FAST9_BFTF_NUM_MAX_TESTCASES];
extern sTokenMapping gsTokenMap_Fast9BestFeatureToFront[MAX_ITEMS_TO_PARSE];

#define PRINT_ERROR_MSG()  printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#endif /* FAST9_BEST_FEATURE_TO_FRONT_CONFIG_H_*/
