/*
*
* Copyright (c) 2015-2017 Texas Instruments Incorporated
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

#ifndef STEREOVISION_CONFIG_H_
#define STEREOVISION_CONFIG_H_

#include "configparser.h"
#include "stdint.h"
#include "xdais_types.h"
#include "istereovision_ti.h"

#define STEREOVISION_FILE_NAME_SIZE  (256)
#define STEREOVISION_NUM_MAX_TESTCASES (20)

typedef struct
{
    uint8_t  inImageFileName[STEREOVISION_FILE_NAME_SIZE];
    uint8_t  inDisparityFileName[STEREOVISION_FILE_NAME_SIZE];
    uint8_t  inAuxDisparityFileName[STEREOVISION_FILE_NAME_SIZE];
    uint8_t  inCostFileName[STEREOVISION_FILE_NAME_SIZE];
    uint8_t  outFileName[STEREOVISION_FILE_NAME_SIZE];
    uint8_t  out16BitDispFileName[STEREOVISION_FILE_NAME_SIZE];
    uint16_t maxImageWidth;
    uint16_t maxImageHeight;
    uint16_t maxFrames;
    uint16_t roiWidth;
    uint16_t roiHeight;
    uint16_t startX;
    uint16_t startY;
    unsigned char inputBitDepth;
    unsigned char censusWinWidth;
    unsigned char censusWinHeight;
    unsigned char censusWinHorzStep;
    unsigned char censusWinVertStep;

    unsigned char costSupportWinWidth;
    unsigned char costSupportWinHeight;
    unsigned short numDisparities;
    unsigned char disparityStep;
    unsigned char searchDir;
    unsigned char smoothingStrength;
    unsigned char disparityNumFracBits;
    unsigned char disparityMinThreshold; /* 0 - 128 */
    unsigned char disparityMaxThreshold; /* 0 - 128 */
    unsigned char costMaxThreshold; /* in % 0 - 100 */
    unsigned char minConfidenceThreshold; /* in % 0 - 100 */
    unsigned char holeFillingStrength; /* in % 0 - 100 */
    unsigned char textureLumaLoThresh; /* 0 - 100 */
    unsigned char textureLumaHiThresh; /* 0 - 100 */
    unsigned char textureThreshold;    /* 0 - 100 */
    unsigned char maxDispDissimilarity; /* In number of disparities */
    unsigned char lrMaxDiffThreshold; /* In number of disparities */
    unsigned char minConfidentNSegment; /* In number of pixels */
    uint8_t enable16BitsDispOut;
} sSTEREOVISION_Config;

extern uint32_t stereovision_numTestCases;
extern sSTEREOVISION_Config gConfig_STEREOVISION[STEREOVISION_NUM_MAX_TESTCASES];
extern sTokenMapping gsTokenMap_STEREOVISION[MAX_ITEMS_TO_PARSE];

#endif /* STEREOVISION_CONFIG_H_ */

