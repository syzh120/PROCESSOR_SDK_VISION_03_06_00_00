/*
*
* Copyright (c) 2014-2017 Texas Instruments Incorporated
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



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vcop.h>
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_nxn_block_sum_cn.h"

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define MAX_INPUT_LINE_SIZE      (300)
#define MAX_INPUT_VALUE_SIZE      (20)

#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

typedef struct
{
  char block1File[MAX_FILE_NAME_SIZE];
  char block2File[MAX_FILE_NAME_SIZE];
  char sum1File[MAX_FILE_NAME_SIZE];
  char sum2File[MAX_FILE_NAME_SIZE];
  int  nValue;
  int  width;
  int  height;
  int  interleaved;
  int  shiftForInterleaved;
  int  inputDataSize;
  int  writeOutput;
  int  seedForRND;
  char inputSrc[MAX_PARAM_STRING_SIZE];
  char configLine[MAX_CONFIG_LINE_SIZE];
  char configParam[MAX_PARAM_STRING_SIZE];

} config_params;

config_params gParams ;


sTokenMapping gsTokenMap_sof[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                   &(gParams.inputSrc)                    , STRING, SINGLE},
  {(char* )"block1File",                 &(gParams.block1File)                  , STRING, SINGLE},
  {(char* )"block2File",                 &(gParams.block2File)                  , STRING, SINGLE},
  {(char* )"sum1File",                   &(gParams.sum1File)                    , STRING, SINGLE},
  {(char* )"sum2File",                   &(gParams.sum2File)                    , STRING, SINGLE},
  {(char* )"nValue",                     &gParams.nValue                        , INT_32, SINGLE},
  {(char* )"width",                      &gParams.width                         , INT_32, SINGLE},
  {(char* )"height",                     &gParams.height                        , INT_32, SINGLE},
  {(char* )"interleaved",                &gParams.interleaved                   , INT_32, SINGLE},
  {(char* )"shiftForInterleaved",        &gParams.shiftForInterleaved           , INT_32, SINGLE},
  {(char* )"inputDataSize",              &gParams.inputDataSize                 , INT_32, SINGLE},
  {(char* )"writeOutput",                &gParams.writeOutput                   , INT_32, SINGLE},
  {(char* )"seedForRND",                 &gParams.seedForRND                    , INT_32, SINGLE},
} ;

#define COMPARE_REFERENCE

#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_nxn_block_sum_kernel.k"
#else
#include "vcop_nxn_block_sum_kernel.h"
#endif

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	'))
  {
    LinePtr++;
  }
  return(LinePtr);
}
void fillDefaultConfig(config_params * params)
{
  strcpy(params->inputSrc, "RND_PTRN");
  params->writeOutput         = 0;
  params->nValue              = 4;
  params->width               = 32;
  params->height              = 32;
  params->interleaved         = 0;
  params->shiftForInterleaved = 0;
  params->inputDataSize       = 8;
  params->seedForRND          = 0xABDC1234;
}
static int writeOutputToTxtFile(unsigned short n, unsigned short * ptr1, char * fileName)
{
  int i;
  FILE * fp;
  fp = fopen(fileName, "w+");
  if(fp== NULL)
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
    return (-1);
  }
  for(i = 0; i < n; i++)
  {
    fprintf(fp,"%d\n",ptr1[i]);
  }
  fclose(fp);
  return(0);
}

static int readInputFromTxtFile(unsigned char * ptr, unsigned short n, char * fileName, unsigned char inputDataSize)
{
  int k;
  FILE * fp;
  int status;
  int value;
  char inputLine[MAX_INPUT_LINE_SIZE];
  unsigned char * ptr8Bits  = ptr;
  unsigned short * ptr16Bits = (unsigned short *)ptr;

  fp = fopen(fileName, "r");
  if(fp== NULL)
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
    return (-1);
  }
  for(k = 0; k < n; k++)
  {
    memset(inputLine, 0, MAX_INPUT_LINE_SIZE);
    status = (int)fgets(inputLine,MAX_CONFIG_LINE_SIZE,fp);
    if ((status == EOF) || (status == 0))
    {
      printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
      return(-1);
    }
    sscanf(inputLine, "%d",&value);
    if(inputDataSize != 8)
    {
      ptr16Bits[k] = value;
    }
    else
    {
      ptr8Bits[k] = value;
    }
  }
  fclose(fp);
  return(0);
}

static void CreateRandPatternU8(unsigned char *ptr, unsigned short n)
{
  int i;
  unsigned char val;
  for(i = 0; i < n; i++)
  {
    val = rand() & 0xFF;
    ptr[i] =  val;
  }
}
static void CreateRandPatternU9(unsigned short *ptr, unsigned short n)
{
  int i;
  unsigned short val;
  for(i = 0; i < n; i++)
  {
    val = rand() & 0x1FF;
    ptr[i] =  val;
  }
}

static void interleaveDataBlocks(unsigned char *ptr, unsigned char *ptr1, unsigned char *ptr2, unsigned short n)
{
  int i;
  for(i = 0; i < n; i++)
  {
    ptr[2*i]   =  ptr1[i];
    ptr[2*i+1] =  ptr2[i];
  }
}

int test_bench(config_params * params)
{
  unsigned char    * inBlk  ;
  unsigned char    * inBlk1 ;
  unsigned char    * inBlk2 ;
  unsigned short   * outBlk1;
  unsigned short   * outBlk2;
  unsigned short   * ref1;
  unsigned short   * ref2;
  unsigned int     * tmpPtr1;
  unsigned int     * tmpPtr2;

  unsigned short numBytes;
  unsigned short blkWidth  = params->width ;
  unsigned short blkHeight = params->height;
  unsigned short nValue    = params->nValue;
  unsigned int  SCARTCH_BUF_SIZE =  (((((blkWidth *blkHeight)/(nValue))/(8*8))*8*9*4) + ((((blkWidth *blkHeight)/(nValue*nValue))/(8*8))*8*9*4));
  unsigned int  OUT_BUF_SIZE     =  (((blkWidth *blkHeight)/(nValue*nValue))*2);

  int fail,i,j,k,l;
  profiler_init();
  fail = 0;
  if(params->inputDataSize == 8)
  {
    numBytes = 1;
  }
  else
  {
    numBytes = 2;
  }

#if VCOP_HOST_EMULATION
    inBlk1    = (unsigned char  *)malloc(blkWidth *blkHeight*numBytes);
    inBlk2    = (unsigned char  *)malloc(blkWidth *blkHeight*numBytes);
    outBlk1   = (unsigned short *)malloc(OUT_BUF_SIZE);
    outBlk2   = (unsigned short *)malloc(OUT_BUF_SIZE);
    tmpPtr1   = (unsigned int   *)malloc(SCARTCH_BUF_SIZE);
    tmpPtr2   = (unsigned int   *)malloc(SCARTCH_BUF_SIZE);
    inBlk     = (unsigned char  *)malloc(blkWidth *blkHeight*2*numBytes);
#else
    inBlk1    = (unsigned char  *)vcop_malloc(VCOP_IBUFLA,blkWidth *blkHeight*numBytes);
    inBlk2    = (unsigned char  *)vcop_malloc(VCOP_IBUFHA,blkWidth *blkHeight*numBytes);
    tmpPtr1   = (unsigned int   *)vcop_malloc(VCOP_IBUFLA,SCARTCH_BUF_SIZE);
    tmpPtr2   = (unsigned int   *)vcop_malloc(VCOP_IBUFHA,SCARTCH_BUF_SIZE);
    outBlk1   = (unsigned short *)vcop_malloc(VCOP_IBUFLA, OUT_BUF_SIZE);
    outBlk2   = (unsigned short *)vcop_malloc(VCOP_IBUFHA, OUT_BUF_SIZE);
    inBlk     = (unsigned char  *)vcop_malloc(VCOP_IBUFHA,blkWidth *blkHeight*2*numBytes);
#endif
    ref1   = (unsigned short *)malloc(OUT_BUF_SIZE);
    ref2   = (unsigned short *)malloc(OUT_BUF_SIZE);


  if(strcmp(params->inputSrc, "RND_PTRN")==0)
  {
    printf("Pattern Generation Seed = %d\n", params->seedForRND);
    srand(params->seedForRND);

    if(params->inputDataSize == 8)
    {
      CreateRandPatternU8(inBlk1, params->width*params->height);
      CreateRandPatternU8(inBlk2, params->width*params->height);
    }
    else
    {
      CreateRandPatternU9((unsigned short *)inBlk1, params->width*params->height);
      CreateRandPatternU9((unsigned short *)inBlk2, params->width*params->height);
    }

  }
  else if(strcmp(params->inputSrc, "TXT_FILE")==0)
  {
    readInputFromTxtFile(inBlk1, params->width*params->height, params->block1File, params->inputDataSize);
    readInputFromTxtFile(inBlk2, params->width*params->height, params->block2File, params->inputDataSize);
  }

  if(params->interleaved == 1)
  {
    if(params->inputDataSize != 8)
    {
      printf("Interleave mode is currenlty supported for 8 bit input data \n");
      exit(0);
    }
    interleaveDataBlocks(inBlk,inBlk1,inBlk2,params->width*params->height);
  }

#ifdef COMPARE_REFERENCE
  if(params->interleaved == 1)
  {
    vcop_nxn_sum_interleaved_cn(inBlk, ref1, ref2,params->nValue, params->width, params->height, params->width,params->shiftForInterleaved);
  }
  else
  {
    if(params->inputDataSize == 8)
    {
      vcop_nxn_sum_u8_cn(inBlk1, inBlk2, ref1, ref2,params->nValue, params->width, params->height, params->width,params->width);
    }
    else
    {
      vcop_nxn_sum_u16_cn((unsigned short *)inBlk1, (unsigned short *)inBlk2, ref1, ref2,params->nValue, params->width, params->height, params->width,params->width);
    }
  }
#endif
  profiler_start();

  if(params->interleaved == 1)
  {
    vcop_nxn_sum_interleaved(inBlk, outBlk1, outBlk2, tmpPtr1, tmpPtr2, params->nValue, params->width, params->height, params->width*2,params->shiftForInterleaved);
  }
  else
  {
    if(params->inputDataSize == 8)
    {
      vcop_nxn_sum_u8(inBlk1, inBlk2, outBlk1, outBlk2, tmpPtr1, tmpPtr2, params->nValue, params->width, params->height, params->width,params->width);
    }
    else
    {
      vcop_nxn_sum_u16((unsigned short *)inBlk1, (unsigned short *)inBlk2, outBlk1, outBlk2, tmpPtr1, tmpPtr2, params->nValue, params->width, params->height, params->width,params->width);
    }
  }

  profiler_end();

#ifdef COMPARE_REFERENCE

  fail = memcmp(outBlk1,ref1,(params->height*params->width)/(params->nValue*params->nValue));
  fail |= memcmp(outBlk2,ref2,(params->height*params->width)/(params->nValue*params->nValue));
  printf(fail ? "FAIL\n\n" : "PASS\n\n");

  if(fail != 0)
  {
    for(i = 0; i < (params->height*params->width)/(params->nValue*params->nValue); i++)
    {
      printf("At %3d - outBlk1:ref1 = %9d:%9d - outBlk2:ref2 = %9d:%9d",i,outBlk1[i], ref1[i],outBlk2[i], ref2[i]);
      if((outBlk1[i] != ref1[i]) || (outBlk2[i] != ref2[i]))
      {
        printf("*******\n");
      }
      else
      {
        printf("\n");
      }
    }
  }

#endif

  profiler_deinit();

  if(params->writeOutput)
  {
    writeOutputToTxtFile((params->height*params->width)/(params->nValue*params->nValue),outBlk1,params->sum1File);
    writeOutputToTxtFile((params->height*params->width)/(params->nValue*params->nValue),outBlk2,params->sum2File);
  }

#if VCOP_HOST_EMULATION
  free(inBlk1 );
  free(inBlk2 );
  free(outBlk1);
  free(outBlk2);
  free(tmpPtr1);
  free(tmpPtr2);
  free(inBlk  );
#else
  vcop_free(inBlk1  );
  vcop_free(inBlk2  );
  vcop_free(tmpPtr1 );
  vcop_free(tmpPtr2 );
  vcop_free(outBlk1 );
  vcop_free(outBlk2 );
  vcop_free(inBlk   );
#endif
  free(ref1);
  free(ref2);
  return (0);
}

int main()
{


  FILE * fp;
  char * LinePtr;
  int status;
  int lineNum = -1;
  config_params * params;
  int config_cmd;
  char configFileName[MAX_FILE_NAME_SIZE];

  params = (config_params *)(&gParams);

  fp = fopen(CONFIG_LIST_FILE_NAME, "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s , Runing in defult mode \n",CONFIG_LIST_FILE_NAME);
    fillDefaultConfig(params);
    test_bench(params);
    return(0);
  }

  while(1)
  {
    memset(params->configLine, 0, MAX_CONFIG_LINE_SIZE);
    status = (int)fgets(params->configLine,MAX_CONFIG_LINE_SIZE,fp);
    LinePtr = params->configLine;
    if ((status == EOF) || (status == 0))
      break;
    lineNum++;
    sscanf(LinePtr, "%d",&config_cmd);
    sscanf(LinePtr, "%s",params->configParam);
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
      LinePtr = moveToNextElement(params->configParam,LinePtr);
      status  = sscanf(LinePtr, "%s",configFileName);
      printf("Processing config file %s !\n", configFileName);
      fillDefaultConfig(params);
      status = readparamfile(configFileName, &gsTokenMap_sof[0]) ;
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }
      test_bench(params);
    }
    else
    {
      printf(" Unsupported config list command parameter at line num : %4d !\n", lineNum);
    }
  }
  fclose(fp);
  return (0);

}
