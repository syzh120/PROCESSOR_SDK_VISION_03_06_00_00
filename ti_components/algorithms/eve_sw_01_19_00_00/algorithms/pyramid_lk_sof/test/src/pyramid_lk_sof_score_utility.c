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


/** @file pyramid_lk_sof_score_utility.c
*
*  @brief  This file contains coode to calculate score for SOF using ground truth file
*
*
*  @date   Dec 2013
*
*  Description
*     This file contains coode to calculate score for SOF using ground truth file
*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <vcop.h>

#if (VCOP_HOST_EMULATION)
#include "pyramid_lk_sof_config.h"
#include "pyramid_lk_sof_tb.h"
#include "configparser.h"

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	')||(LinePtr[0] == ','))
  {
    LinePtr++;
  }
  return(LinePtr);
}
void fillDefaultConfig(config_params * params)
{
  params->maxNumKeyPoints = 0;
  params->numLevels    = 4; 
  params->maxItersLK   = 10; 
  params->imWidth      = 640;
  params->imHeight     = 320;
  params->minErrValue  = 0;
}

int SOFDemo_ComputeStats(char *fileRef, char *fileCur, char *fileStats)
{
  FILE *fpCur, *fpStats;
  int ret ;
  int totalPts = 0;
  int rightPts = 0 ;
  
  sSOFFlow (*flowGT) [MAX_WIDTH];

  int x, y ;
  float u, v ;
  unsigned int error= 0;
  int totalPoints = 0 ;
  float accuracy;

#ifndef CREATE_FIXED_MOTION
  FILE *fpRef;
  fpRef = fopen(fileRef, "r");
  if(fpRef == NULL)
  {
    printf("Not able to open Ref flow vector file - %s\n",fileRef );
    return -1 ;
  }
#endif

  fpCur = fopen(fileCur, "r");
  if(fpCur == NULL)
  {
    printf("Not able to open Cur flow vector file - %s\n",fileCur );
    return -1 ;
  }

  fpStats = fopen(fileStats, "w");
  if(fpStats == NULL)
  {
    printf("Not able to open Out stats file - %s\n",fileStats );
    return -1 ;
  }

  /*---------------------------------------------------------------*/
  /* Main aim of this memory zeroing is to Set the valid flag = 0  */
  /*---------------------------------------------------------------*/
  flowGT   = (sSOFFlow (*)[MAX_WIDTH])malloc(MAX_HEIGHT*MAX_WIDTH* sizeof(sSOFFlow));
  memset(flowGT, 0, sizeof(sSOFFlow)*MAX_HEIGHT*MAX_WIDTH);

#ifndef CREATE_FIXED_MOTION
  while (!feof(fpRef))
  {
    ret = fscanf(fpRef,"%d,%d,%f,%f\n",&x,&y,&u,&v);
    if (ret != -1)
    {
      if(x <0 || x> (MAX_WIDTH-1) || y <0 || y> (MAX_HEIGHT-1))
      {
        printf("Ref flow vector file - %s is not Valid\n",fileRef );
        break;
      }
      flowGT[y][x].u = u ;
      flowGT[y][x].v = v ;
      flowGT[y][x].valid = 1 ;
    }
  }
#endif

  fprintf(fpStats, "XPos,YPos,u[calculated],v[calculated],u[GT],v[GT], Disatnce\n");
  while (!feof(fpCur))
  {
    ret = fscanf(fpCur,"%d,%d,%f,%f",&x,&y,&u,&v);
    if (ret != -1)
    {
      if(x <0 || x> (MAX_WIDTH-1) || y <0 || y> (MAX_HEIGHT-1))
      {
        printf("Flow vector file - %s is not Valid\n",fileCur );
        break;
      }
#ifdef CREATE_FIXED_MOTION
      flowGT[y][x].valid = 1 ;
      flowGT[y][x].u = MOTION_u ;
      flowGT[y][x].v = MOTION_v ;
#endif
      if(flowGT[y][x].valid == 1 )
      {
        double distance;
        distance = 
          sqrt((flowGT[y][x].u - u)*(flowGT[y][x].u - u) + (flowGT[y][x].v - v)*(flowGT[y][x].v - v));
        fprintf(fpStats, "%d,%d,%f,%f,%f,%f,%f\n",x,y,u,v,flowGT[y][x].u, flowGT[y][x].v,distance);
        if(distance <= MAX_PIXEL_DIFF)
        {
          rightPts++;
        }
        totalPts++;
      }
    }
  }
  if(totalPts !=0)
  {
    accuracy = (float)rightPts/totalPts;
    fprintf(fpStats,"****************** Distance Accurcay = %f %%  *************\n",accuracy*100);
    printf("****************** Distance Accurcay = %f %%  for %d points*************\n",accuracy*100,totalPts);
  }
  fclose(fpRef);
  fclose(fpCur);
  fclose(fpStats);
  free(flowGT );
  return 0 ;
}

int main(int argc, char *argv[])
{
  int32_t         status = 0;
  FILE           *fp;
  int8_t         *LinePtr;
  int32_t         lineNum = -1;
  config_params  *params;
  int32_t         config_cmd;
  int8_t          configFileName[MAX_FILE_NAME_SIZE];

  params = (config_params *)(&gParams);

  if (argc > 1)
  {
    strcpy((char *)configFileName, argv[1]) ;
  }
  else
  {
    strcpy((char *)configFileName,CONFIG_LIST_FILE_NAME);
  }

  fp = fopen((const char *)configFileName , "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s , Exiting...\n",CONFIG_LIST_FILE_NAME);
    return(status);
  }

  while(1)
  {
    memset(params->configLine, 0, MAX_CONFIG_LINE_SIZE);
    status = (int)fgets(params->configLine,MAX_CONFIG_LINE_SIZE,fp);
    LinePtr = (int8_t *)params->configLine;
    if ((status == EOF) || (status == 0))
      break;
    lineNum++;
    sscanf((const char *)LinePtr, "%d",&config_cmd);
    sscanf((const char *)LinePtr, "%s",params->configParam);
    if(config_cmd == 0)
    {
      printf("End of config list found !\n");
      break;
    }
    else if(config_cmd == 2)
    {
      continue;
    }
    else if(config_cmd == 1)
    {
      LinePtr = (int8_t *)moveToNextElement(params->configParam,(char *)LinePtr);
      status  = sscanf((const char *)LinePtr, "%s",configFileName);
      printf("Processing config file %s !\n", configFileName);
      fillDefaultConfig(params);
      status = readparamfile((char *)configFileName, gsTokenMap_sof) ;
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }     

      /* Validate the applet */
      SOFDemo_ComputeStats(params->gtFileName,params->outFileName,params->statsFileName);
      if(status == -1)
      {
        return status;
      }
    }
    else
    {
      printf(" Unsupported config list command parameter at line num : %4d !\n", lineNum);
    }
  }
  fclose(fp);

  return status;
}
#endif
