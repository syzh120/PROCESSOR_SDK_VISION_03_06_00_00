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


/**
*  @file       integral_image_test.c
*
*  @brief      Example file that shows the usage of integral image applet
*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <vcop.h>
#pragma RESET_MISRA ("required")

#include "alg_osal.h"
#include "evestarterware.h"

#include "integral_image_test.h"
#include "iIntegral_image_ti.h"

#include "eve_profile.h"
#include "ti_mem_manager.h"
#include "configparser.h"
#include "ti_file_io.h"

config_params gParams ;
sTokenMapping gsTokenMap_sof[MAX_ITEMS_TO_PARSE] =
{
  {"inFile",                    &(gParams.inFile)                , STRING, SINGLE},
  {"outFile",                   &(gParams.outFile)               , STRING, SINGLE},
  {"imWidth",                   &gParams.imWidth                 , INT_32, SINGLE},
  {"imHeight",                  &gParams.imHeight                , INT_32, SINGLE},
  {(char *)"testCaseName",              &gParams.testCaseName            , STRING, SINGLE},
  {(char *)"testCaseDesc",              &gParams.testCaseDesc            , STRING, SINGLE},
  {(char* )"performanceTestcase",       &gParams.performanceTestcase     , INT_8,  SINGLE},
} ;


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
  gParams.imWidth   = 720;
  gParams.imHeight  = 480;

  strcpy((char*)params->testCaseName, " ");
  strcpy((char*)params->testCaseDesc, " ");


}

#define DMEM_SIZE (8*1024)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
uint8_t DMEM_SCRATCH[DMEM_SIZE];

TIMemObject memObj_DMEM;
int32_t TestApp_AllocMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
    int32_t i;
    TIMemHandle memHdl_DMEM = &memObj_DMEM;
    for (i = 0; i < numMemRec; i++)
    {
        if(memRec[i].space == IALG_DARAM0) {
            memRec[i].base = TI_GetMemoryChunk(memHdl_DMEM, memRec[i].size, memRec[i].alignment);
        }
        else {
            memRec[i].base = (Void *) malloc( memRec[i].size);
        }
        if(memRec[i].base == NULL)
        {
            return IALG_EFAIL;
        }
    }
    return IALG_EOK;
}

int32_t TestApp_FreeMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
    int32_t i;
    TIMemHandle memHdl_DMEM = &memObj_DMEM;

    for (i = 0; i < numMemRec; i++)
    {
        if(memRec[i].base == NULL)
        {
            return IALG_EFAIL;
        }
        if(memRec[i].space == IALG_DARAM0) {
            TI_ResetMemoryHandle(memHdl_DMEM);
        }else {
            free(memRec[i].base);
        }
    }
    return IALG_EOK;
}


void integral_image_cn
  (
  uint16_t width,
  uint16_t height,
  uint8_t *inimgptr,
  uint32_t  *outimgptr
  )
{
  int32_t i,j;
  for(i = 0; i < width; i++)
  {
    for(j = 0; j < height; j++)
    {
      outimgptr[j*width + i] = inimgptr[j*width + i];
    }
  }


  for(i = 0; i < width; i++)
  {
    for(j = 1; j < height; j++)
    {
      outimgptr[j*width + i] += outimgptr[(j-1)*width + i];
    }
  }

  for(i = 1; i < width; i++)
  {
    for(j = 0; j < height; j++)
    {
      outimgptr[j*width + i] += outimgptr[j*width + i-1];
    }
  }

}


#if (!VCOP_HOST_EMULATION)
extern void minit(void);
#endif


typedef struct IM_Fxns
{
  IVISION_Fxns * ivision;

} IM_Fxns;

unsigned int t0, t1, overhead, profile_tsc, profile_create_tsc;
unsigned int tcntr0, tcntr1, overflow, profile_sctm;
unsigned int testnum=0;

int32_t integralImageTest(config_params* params)
{
  int32_t numMemRec;
  int32_t i,j;
  IALG_MemRec *memRec;
  int32_t status;

  uint8_t * ptr;
  uint32_t * ptr1;
  int32_t size;
  int32_t fail = 0;
  int32_t * ref_out;

  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  INTEGRAL_IMAGE_TI_CreateParams   createParams;

  IVISION_InArgs    inArgs;
  IVISION_InBufs    inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc;
  IVISION_BufDesc   * inBufDescList[2];

  IVISION_OutArgs   outArgs;
  IVISION_OutBufs   outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   outBufDesc;
  IVISION_BufDesc   * outBufDescList[2];


  /*--------------------------------------------------------------------------*/
  /*Create memory handle for ARP32 DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;

  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);

  /*-----------------------------------------------------------------
  Set buffer descriptor pointers array base
  -----------------------------------------------------------------*/
  inBufs.bufDesc  = inBufDescList;
  outBufs.bufDesc = outBufDescList;

  inBufs.numBufs   = 1;
  outBufs.numBufs  = 1;

  inBufDescList[0]     = &inBufDesc;
  outBufDescList[0]    = &outBufDesc;
  /*-----------------------------------------------------------------
  Set algorithm parameters
  -----------------------------------------------------------------*/

  createParams.visionParams.algParams.size   = sizeof(INTEGRAL_IMAGE_TI_CreateParams);
  createParams.visionParams.cacheWriteBack   = NULL;
  createParams.imgFrameWidth                 = params->imWidth;
  createParams.imgFrameHeight                = params->imHeight;


  profiler_init();
  profiler_initStack(profiler_getSP());
  profiler_start();
  /*-----------------------------------------------------------------
  Query alogorithm memory requirement using standard IALG interface
  -----------------------------------------------------------------*/
  numMemRec = INTEGRAL_IMAGE_TI_VISION_FXNS.ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

  status = INTEGRAL_IMAGE_TI_VISION_FXNS.ialg.algAlloc(
    (IALG_Params *)(&createParams), NULL, memRec);

  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    goto Exit;
  }

  /*-----------------------------------------------------------------
  Allocate memory for all the mem records
  Application has to implement the below function
  Refer the example implementation below in this file
  -----------------------------------------------------------------*/
  status = TestApp_AllocMemRecords(memRec,numMemRec);
  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    goto Exit;
  }

  /*-----------------------------------------------------------------
  Intialize the algorithm instance with the alocated memory
  and user create parameters
  -----------------------------------------------------------------*/
  status = INTEGRAL_IMAGE_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
    memRec,NULL,(IALG_Params *)(&createParams));

  handle = (IM_Fxns *) memRec[0].base;

  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    goto Exit;
  }

  profiler_end_print(0);

  inArgs.subFrameInfo = 0;
  inArgs.size                  = sizeof(IVISION_InArgs);

  inBufDesc.numPlanes                          = 1;
  inBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_IN_IMAGEBUFFER].frameROI.topLeft.x    = 0;
  inBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_IN_IMAGEBUFFER].frameROI.topLeft.y    = 0;
  inBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_IN_IMAGEBUFFER].width                 = params->imWidth;
  inBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_IN_IMAGEBUFFER].height                = params->imHeight;
  inBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_IN_IMAGEBUFFER].frameROI.width        = params->imWidth;
  inBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_IN_IMAGEBUFFER].frameROI.height       = params->imHeight;

  inBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_IN_IMAGEBUFFER].buf = malloc(inBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_IN_IMAGEBUFFER].width *
    inBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_IN_IMAGEBUFFER].height);
  if(inBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_IN_IMAGEBUFFER].buf == NULL)
  {
    PRINT_ERRORE_MSG();
    goto Exit;
  }

  outBufDesc.numPlanes                          = 1;
  outBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_OUT].frameROI.topLeft.x    = 0;
  outBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_OUT].frameROI.topLeft.y    = 0;
  outBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_OUT].width                 = params->imWidth * sizeof(int32_t);
  outBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_OUT].height                = params->imHeight;
  outBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_OUT].frameROI.width        = params->imWidth * sizeof(int32_t);
  outBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_OUT].frameROI.height       = params->imHeight;

  outBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_OUT].buf = malloc(outBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_OUT].width *
    outBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_OUT].height);
  if(outBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_OUT].buf == NULL)
  {
    PRINT_ERRORE_MSG();
    goto Exit;
  }

  ptr1 = (uint32_t * )outBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_OUT].buf;
  for(i = 0; i < (outBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_OUT].width * outBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_OUT].height)/4; i++)
  {
    ptr1[i] = 0;
  }


  ptr = (uint8_t * )inBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_IN_IMAGEBUFFER].buf;
  size = inBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_IN_IMAGEBUFFER].width * inBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_IN_IMAGEBUFFER].height;
  for(i = 0; i < size; i++)
  {
      ptr[i] = rand() % 256;;
  }
  profiler_start();

  status = handle->ivision->algProcess((IVISION_Handle)handle,
          &inBufs,&outBufs,&inArgs,&outArgs);

  profiler_end_print(1);
  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    goto Exit;
  }

  ref_out = (int32_t *)malloc(outBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_OUT].width * outBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_OUT].height);
  if(ref_out == NULL)
  {
    PRINT_ERRORE_MSG();
    goto Exit;
  }

  integral_image_cn(createParams.imgFrameWidth ,createParams.imgFrameHeight,(uint8_t *)inBufDesc.bufPlanes[INTEGRAL_IMAGE_BUFDESC_IN_IMAGEBUFFER].buf,(uint32_t *)ref_out);

  for(j = 0; j < createParams.imgFrameHeight; j++)
  {
    for(i = 0; i < createParams.imgFrameWidth; i++)
    {
      if(ref_out[j*createParams.imgFrameWidth + i] != ptr1[j*createParams.imgFrameWidth + i])
      {
        printf("Integral Image Applet Failing at %4d %4d : %8d,%8d \n",j,i,ref_out[j*createParams.imgFrameWidth + i],ptr1[j*createParams.imgFrameWidth + i]);
        fail = 1;
        break;
      }
    }
  }

  profiler_printStatus(fail);
  fflush(stdout);
  free(ref_out);

  status = handle->ivision->ialg.algFree((IALG_Handle)(handle), memRec);
  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    goto Exit;
  }
  /* Here Free memory for all the mem records */
  status = TestApp_FreeMemRecords(memRec,numMemRec);
  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    goto Exit;
  }
  free(memRec);
  /* Get the stack usage */
#if !(VCOP_HOST_EMULATION)
  profiler_getStackDepth();
#endif
Exit:
  return status;
}


int32_t main()
{


  TI_FILE * fp;
  char * LinePtr;
  int32_t status;
  int32_t lineNum = -1;
  config_params * params;
  int32_t config_cmd;
  char configFileName[MAX_FILE_NAME_SIZE];

  report_printAppletInfo((int8_t *)"INTEGRAL_IMAGE_TI_VISION");

  params = (config_params *)(&gParams);

  fp = FOPEN(CONFIG_LIST_FILE_NAME, "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s , Exiting \n",CONFIG_LIST_FILE_NAME);
    return(0);
  }

  while(1)
  {
    memset(params->configLine, 0, MAX_CONFIG_LINE_SIZE);
    status = (int32_t)FGETS(params->configLine,MAX_CONFIG_LINE_SIZE,fp);
    LinePtr = params->configLine;
    if ((status == EOF) || (status == 0))
      break;
    lineNum++;
    sscanf(LinePtr, "%d",&config_cmd);
    sscanf(LinePtr, "%s",params->configParam);
    if(config_cmd == 0)
    {
      /*printf("End of config list found !\n");*/
      break;
    }
    else if(config_cmd == 2)
    {
      continue;
    }
    else if(config_cmd == 1)
    {
      LinePtr = moveToNextElement(params->configParam,LinePtr);
      status  = sscanf(LinePtr, "%s",configFileName);
      /*printf("Processing config file %s !\n", configFileName);*/
      fillDefaultConfig(params);
      status = readparamfile(configFileName, &gsTokenMap_sof[0]) ;
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }

      profiler_testCaseInfo((int8_t *)params->testCaseName,(int8_t *)params->testCaseDesc,params->performanceTestcase);
      printparams(&gsTokenMap_sof[0],(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)params,sizeof(config_params)) ;


      status = integralImageTest(params);
    }
    else
    {
      printf(" Unsupported config list command parameter at line num : %4d !\n", lineNum);
    }
  }
  FCLOSE(fp);

  return (0);

}
