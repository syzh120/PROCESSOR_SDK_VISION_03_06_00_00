/*
* module name       :TI Object Classification
*
* module descripton :Classification of German traffic signs using TI’s C66x DSP
*
*/
/*

Copyright (c) [2014] – [2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive license under copyrights and patents it now or hereafter owns or controls to make, have made, use, import, offer to sell and sell ("Utilize") this software subject to the terms herein.  With respect to the foregoing patent license, such license is granted  solely to the extent that any such patent is necessary to Utilize the software alone.  The patent license shall not apply to any combinations which include this software, other than combinations with devices manufactured by or for TI (“TI Devices”).  No hardware patent is licensed hereunder.

Redistributions must preserve existing copyright notices and reproduce this license (including the above copyright notice and the disclaimer and (if applicable) source code license limitations below) in the documentation and/or other materials provided with the distribution

Redistribution and use in binary form, without modification, are permitted provided that the following conditions are met:

*       No reverse engineering, decompilation, or disassembly of this software is permitted with respect to any software provided in binary form.

*       any redistribution and use are licensed by TI for use only with TI Devices.

*       Nothing shall obligate TI to provide you with source code for the software licensed and provided to you in object code.

If software source code is provided to you, modification and redistribution of the source code are permitted provided that the following conditions are met:

*       any redistribution and use of the source code, including any resulting derivative works, are licensed by TI for use only with TI Devices.

*       any redistribution and use of any object code compiled from the source code and any resulting derivative works, are licensed by TI for use only with TI Devices.

Neither the name of Texas Instruments Incorporated nor the names of its suppliers may be used to endorse or promote products derived from this software without specific prior written permission.

DISCLAIMER.

THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "object_classification_config.h"
#pragma RESET_MISRA ("required")

uint32_t objectClassification_numTestCases;
sObjectClassification_Config gConfig_objectClassification[MAX_TESTCASES];

sTokenMapping gsTokenMap_objectClassification[] =
{
  {(char *)"inFileName1"           ,&gConfig_objectClassification[0].inFileName1,         STRING,  SINGLE},
  {(char *)"inFileName2"           ,&gConfig_objectClassification[0].inFileName2,         STRING,  SINGLE},
  {(char *)"outFileName"           ,&gConfig_objectClassification[0].outFileName,         STRING,  SINGLE},
  {(char *)"imgFileName"           ,&gConfig_objectClassification[0].imgFileName,         STRING,  SINGLE},
  {(char *)"maxImageWidth"         ,&gConfig_objectClassification[0].maxImageWidth,       INT_16,  SINGLE},
  {(char *)"maxImageHeight"        ,&gConfig_objectClassification[0].maxImageHeight,      INT_16,  SINGLE},
  {(char *)"maxFrames"             ,&gConfig_objectClassification[0].maxFrames,           INT_16,  SINGLE},
  {(char *)"maxScales"             ,&gConfig_objectClassification[0].maxScales,           INT_16,  SINGLE},
  {(char *)"inputMode"             ,&gConfig_objectClassification[0].inputMode,           INT_8,  SINGLE},
  {(char *)"classifierType"        ,&gConfig_objectClassification[0].classifierType,      INT_8,  SINGLE},
} ;

/*----------------------------------------------------------------------------*/
/* Error strings which are mapped to CNN Classifier errors                    */
/* Please refer User guide for more details on error strings                  */
/*----------------------------------------------------------------------------*/
static sErrorMapping gErrorStrings[32] =
{
  (XDAS_Int8 *)"TI_OC_UNSUPPORTED_IMAGE_WIDTH = 16\0",
  (XDAS_Int8 *)"TI_OC_UNSUPPORTED_IMAGE_HEIGHT = 17,\0",
  (XDAS_Int8 *)"TI_OC_UNSUPPORTED_NUM_SCALES = 18,\0",
  (XDAS_Int8 *)"TI_OC_UNSUPPORTED_INPUT_MODE = 19,\0",
  (XDAS_Int8 *)"TI_OC_UNSUPPORTED_CLASSIFIER_TYPE = 20,\0",
  (XDAS_Int8 *)"TI_OC_EDMA_MEMCPY_ERROR = 21,\0",
  (XDAS_Int8 *)"TI_OC_EDMA_SCATTER_GATHER_ERROR = 22,\0",
  (XDAS_Int8 *)"TI_OC_RESERVED_PARAMS_NOT_ZERO = 23,\0",
  (XDAS_Int8 *)"TI_OC_UNSUPPORTED_PARAMETER = 24,\0"
};

XDAS_Int32 TI_OC_Report_Error(XDAS_Int32 uiErrorMsg)
{
  int i;
  if(uiErrorMsg)
  {
    /*------------------------------------------------------------------------*/
    /* Loop through all the bits in error message and print error string.     */
    /*------------------------------------------------------------------------*/
    for (i = 16; i < 32; i ++)
    {
      if (uiErrorMsg & (1 << i))
      {
        printf("ERROR: %s \n",  gErrorStrings[(i - 16)].errorName);
      }
    }

    return IALG_EFAIL;
  }

  return IALG_EOK;
}
