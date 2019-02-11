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

#ifndef _PROFILE_H_
#define _PROFILE_H_

//#define ENABLE_PROFILE

typedef enum
{
  TI_DSP_PROFILE_MODULE0    = 0,
  TI_DSP_PROFILE_MODULE1    = 1,
  TI_DSP_PROFILE_MODULE2    = 2,
  TI_DSP_PROFILE_MODULE3    = 3,
  TI_DSP_PROFILE_MODULE4    = 4,
  TI_DSP_PROFILE_MODULE5    = 5,
  TI_DSP_PROFILE_MODULE6    = 6,
  TI_DSP_PROFILE_MODULE7    = 7,
  TI_DSP_PROFILE_MODULE8    = 8,
  TI_DSP_PROFILE_MODULE9    = 9,
  TI_DSP_PROFILE_MODULE10   = 10,
  TI_DSP_PROFILE_MODULE11   = 11,
  TI_DSP_PROFILE_MODULE12   = 12,
  TI_DSP_PROFILE_MODULE13   = 13,
  TI_DSP_PROFILE_MODULE14   = 14,
  TI_DSP_PROFILE_MODULE15   = 15,
  TI_DSP_PROFILE_MODULE16   = 16,
  TI_DSP_PROFILE_MODULE17   = 17,
  TI_DSP_PROFILE_MODULE18   = 18,
  TI_DSP_PROFILE_MODULE19   = 19,
  TI_DSP_PROFILE_MODULE20   = 20,
  TI_DSP_PROFILE_MODULE21   = 21,
  TI_DSP_PROFILE_MODULE22   = 22,
  TI_DSP_PROFILE_MODULE23   = 23,
  TI_DSP_PROFILE_MODULE24   = 24,
  TI_DSP_PROFILE_MAX        = 25
} TI_DSP_ProfileModuleID;

typedef enum
{
  TI_DSP_PROFILE_END      = 0,
  TI_DSP_PROFILE_START    = 1
} TI_DSP_ProfileFlag;

typedef enum
{
  TI_DSP_PROFILE_INDIVIDUAL     = 0,
  TI_DSP_PROFILE_CUMULATIVE     = 1

} TI_DSP_ProfileMode;

typedef struct
{
  short         moduleId;
  short         count;
  long long     totalTime;
  long long     start;
  unsigned int  nestedOverhead;
} TI_DSP_PrfData;

typedef struct
{
  TI_DSP_PrfData* prfData;

  unsigned int        profileDataIdx;
  long long           totalOvehead;

  long long           rsvd1;
  long long           rsvd2;
  long long           rsvd3;
  long long           rsvd4;
} TI_DSP_PrfInfo;

unsigned int TI_DSP_ProfileReset(TI_DSP_PrfInfo* prfInfo);
int TI_DSP_ProfileModule(TI_DSP_PrfInfo* prfInfo, unsigned int moduleId, unsigned int start, unsigned int acc);
static inline long long TI_DSP_getTime();
unsigned int TI_DSP_ProfileInit(TI_DSP_PrfInfo* prfInfo);

#endif

