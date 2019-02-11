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

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "profile.h"

unsigned int TI_DSP_ProfileReset(TI_DSP_PrfInfo* prfInfo)
{
  volatile unsigned int temp;
  int i;

  if(prfInfo->prfData != NULL){
    for(i =0; i < TI_DSP_PROFILE_MAX; i++)
    {
      prfInfo->prfData[i].totalTime    = 0;
      prfInfo->prfData[i].count        = 0;
      prfInfo->prfData[i].moduleId     = -1;
      prfInfo->prfData[i].start        = 0;
      prfInfo->prfData[i].nestedOverhead = 0;
    }
  }

  prfInfo->profileDataIdx        = 0;
  prfInfo->totalOvehead          = 0;
  prfInfo->rsvd1                 = 0;
  prfInfo->rsvd2                 = 0;
  prfInfo->rsvd3                 = 0;
  prfInfo->rsvd4                 = 0;

  return 0;
}
unsigned int TI_DSP_ProfileInit(TI_DSP_PrfInfo* prfInfo)
{
  long long timeStart = TI_DSP_getTime();
  long long time      = TI_DSP_getTime();
  long long timeEnd   = TI_DSP_getTime();
  long long overhead  = (timeEnd - time);

  volatile unsigned int temp;
  int indProfileOverhead, accProfileOverhead;

  TI_DSP_ProfileReset(prfInfo);

  TI_DSP_ProfileModule(prfInfo,
  TI_DSP_PROFILE_MODULE0,
  TI_DSP_PROFILE_START,
  TI_DSP_PROFILE_CUMULATIVE);

  TI_DSP_ProfileModule(prfInfo,
  TI_DSP_PROFILE_MODULE0,
  TI_DSP_PROFILE_END,
  TI_DSP_PROFILE_CUMULATIVE);

  accProfileOverhead = prfInfo->prfData[0].totalTime;

  TI_DSP_ProfileReset(prfInfo);

  TI_DSP_ProfileModule(prfInfo,
  TI_DSP_PROFILE_MODULE0,
  TI_DSP_PROFILE_START,
  TI_DSP_PROFILE_INDIVIDUAL);

  TI_DSP_ProfileModule(prfInfo,
  TI_DSP_PROFILE_MODULE0,
  TI_DSP_PROFILE_END,
  TI_DSP_PROFILE_INDIVIDUAL);

  indProfileOverhead = prfInfo->prfData[0].totalTime;

  TI_DSP_ProfileReset(prfInfo);

  timeEnd = TI_DSP_getTime();

  prfInfo->totalOvehead = (timeEnd - timeStart - overhead);
  prfInfo->rsvd1 = accProfileOverhead;
  prfInfo->rsvd2 = indProfileOverhead;

  return 0;
}

int TI_DSP_ProfileModule(TI_DSP_PrfInfo* prfInfo, unsigned int moduleId, unsigned int start, unsigned int acc)
{
#ifdef ENABLE_PROFILE
  long long time = TI_DSP_getTime();
  long long timeEnd = TI_DSP_getTime();
  TI_DSP_PrfData * currPtr;

  int i;
  int index;
  int callOverhead, callOverheadTot;

  if(prfInfo->prfData == NULL)
    return 0;

  if(acc){
    callOverhead = prfInfo->rsvd1;
    callOverheadTot = prfInfo->rsvd3;
  }
  else{
    callOverhead = prfInfo->rsvd2;
    callOverheadTot = prfInfo->rsvd4;
  }

  if(acc)
  {
    index = -1;

    for(i = 0; i < TI_DSP_PROFILE_MAX; i++)
    {
      if((prfInfo->prfData[i].moduleId == moduleId) && (index == -1))
      {
        index = i;
      }
    }

    if((index == -1) && (prfInfo->profileDataIdx < (TI_DSP_PROFILE_MAX - 1)))
      index = prfInfo->profileDataIdx;

    currPtr = &(prfInfo->prfData[index]);

    if(index == prfInfo->profileDataIdx )
    {
     prfInfo->profileDataIdx++;
    }

  }
  else if(start)
  {
    currPtr = &(prfInfo->prfData[prfInfo->profileDataIdx]);
    prfInfo->profileDataIdx++;
  }
  else  /* if end */
  {
    index = -1;
    for(i = TI_DSP_PROFILE_MAX-1; i >= 0; i--)
    {
      if((prfInfo->prfData[i].moduleId == moduleId) && (index == -1))
      {
        index = i;
      }
    }

    if(index < 0)
    {
      return (-1);
    }

    currPtr = &(prfInfo->prfData[index]);
  }
  if(prfInfo->profileDataIdx >= TI_DSP_PROFILE_MAX)
  {
     return (-1);
  }

  currPtr->moduleId = moduleId;

  if(start)
  {
    currPtr->start          = time;
    currPtr->nestedOverhead = 0;
  }
  else
  {
    currPtr->totalTime   += ((time - currPtr->start) - currPtr->nestedOverhead);
    currPtr->count++;
  }

  timeEnd = TI_DSP_getTime();

  for(i = 0; i < TI_DSP_PROFILE_MAX; i++)
  {
    prfInfo->prfData[i].nestedOverhead += (timeEnd - time) + callOverhead;
  }

  timeEnd = TI_DSP_getTime();

  prfInfo->totalOvehead += callOverheadTot + (timeEnd - time);

#endif

  return 1;
}
#if (!HOST_EMULATION)
long long _TSC_read();
#endif
static inline long long TI_DSP_getTime()
{
#if (!HOST_EMULATION)
  return(_TSC_read());
#else
  return(0);
#endif
}

#pragma RESET_MISRA ("required")
