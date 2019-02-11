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



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#include "vcop.h"
#include "eve_profile.h"

#include "configparser.h"
#include "vcop_nonMaxSuppress_mxn_16s_config.h"

/* ------------------------------------------------------------------------ */
/*  Include prototype for the "C" implementation of non-maximum suppression */
/*  function.                                                               */
/* ------------------------------------------------------------------------ */
#include "vcop_nonMaxSuppress_mxn_16s_c.h"//:TODO:


#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	')||(LinePtr[0] == ','))
  {
    LinePtr++;
  }
  return(LinePtr);
}

#define WIN_HEIGHT (7)
#define WIN_WIDTH  (7)

#define BLOCK_HEIGHT (32 + WIN_HEIGHT - 1)
#define BLOCK_WIDTH  (64 + WIN_WIDTH - 1)

#if VCOP_HOST_EMULATION
  #include "../src_kernelC/vcop_nonMaxSuppress_mxn_16s_kernel.k" // kernel source
#else
  #include "vcop_nonMaxSuppress_mxn_16s_kernel.h"
#endif

#pragma DATA_SECTION(IMAGE, "Adata");
unsigned short IMAGE[BLOCK_WIDTH*BLOCK_HEIGHT] = {0x00};

#pragma DATA_SECTION(OUT, "Bdata");
unsigned char OUT[BLOCK_WIDTH*BLOCK_HEIGHT] = {0x00};

#pragma DATA_SECTION(scratch, "Bdata");
unsigned short scratch[BLOCK_WIDTH*BLOCK_HEIGHT] = {0x00};

#pragma DATA_SECTION(scratch1, "Cdata");
unsigned short scratch1[BLOCK_WIDTH*BLOCK_HEIGHT] = {0x00};

#pragma DATA_SECTION(OUTREF, "Eoutdata");
unsigned char OUTREF[BLOCK_WIDTH*BLOCK_HEIGHT] = {0x00};

#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))
#define ALIGN_2SIMD(a)    ((a + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))

void createRandomPattern(uint16_t * ptr, uint16_t width, uint16_t height)
{
  uint32_t i;
  for ( i = 0 ; i < width * height; i++)
  {
    ptr[i] = rand() & 0xFFFF;
  }
}


void createRandomPatternS(int16_t * ptr, uint16_t width, uint16_t height)
{
  uint32_t i;
  for ( i = 0 ; i < width * height; i++)
  {
    ptr[i] = rand() & 0xFFFF;
  }
}

int32_t nmsMxn16sBitPackTest(sNms_mxn_16s_Config * testcaseParams)
{
  int32_t iter,i, j, status = 0;
  uint32_t seed;
  FILE *fp_in = NULL, *fp_out = NULL;
  uint32_t   size;

  int16_t * inputPtr = NULL;
  uint8_t  * outputPtr = NULL;
  uint16_t * scratchBuf1 = NULL;
  uint16_t * scratchBuf2 = NULL;
  uint8_t  * outputPtrRef = NULL;
  uint16_t   inBlockWidth;
  uint16_t   inBlockHeight;

  uint16_t   outBlockWidth;
  uint16_t   outBlockHeight;
  char  *statusStr = NULL;
  uint8_t   mask;
  profiler_init();

  inBlockWidth    = testcaseParams->width;
  inBlockHeight   = testcaseParams->height;

  outBlockWidth   = testcaseParams->width - (testcaseParams->windowWidth - 1);
  outBlockHeight  = testcaseParams->height - (testcaseParams->windowHeight - 1);

#if (!VCOP_HOST_EMULATION)
  inputPtr      = (int16_t*)vcop_malloc(VCOP_IBUFLA , inBlockWidth * inBlockHeight * sizeof(int16_t));
  outputPtr     = (uint8_t*)vcop_malloc(VCOP_IBUFHA, ALIGN_SIMD(outBlockWidth) * outBlockHeight/ 8 );
  scratchBuf1   = (uint16_t*)vcop_malloc(VCOP_IBUFHA, ALIGN_2SIMD(inBlockWidth) * inBlockHeight * sizeof(uint16_t));
  scratchBuf2   = (uint16_t*)vcop_malloc(VCOP_WMEM, ALIGN_SIMD(inBlockWidth) * inBlockHeight * sizeof(uint16_t));
#else
  inputPtr      = (int16_t*)malloc(inBlockWidth * inBlockHeight * sizeof(int16_t));
  outputPtr     = (uint8_t*)malloc( ALIGN_SIMD(outBlockWidth) * outBlockHeight/ 8);
  scratchBuf1   = (uint16_t*)malloc( ALIGN_2SIMD(inBlockWidth) * inBlockHeight * sizeof(uint16_t));
  scratchBuf2   = (uint16_t*)malloc( ALIGN_SIMD(inBlockWidth) * inBlockHeight * sizeof(uint16_t));

#endif

  outputPtrRef  = (uint8_t*)malloc( ALIGN_SIMD(outBlockWidth) * outBlockHeight / 8);

  if(strcmp(testcaseParams->outputImage, ""))
  {
    fp_out = fopen((const char*)testcaseParams->outputImage, "wb+");
  }

  if(fp_out == NULL)
  {
    printf("Failed to open Output file.\n");
  }

  for (iter = 0; iter < testcaseParams->numIter; iter++)
  {

    if ( strcmp(testcaseParams->inputImage, "" ) )
    {
      printf("File Test\n");
      fp_in = fopen((const char *)testcaseParams->inputImage, "rb");

      if(fp_in == NULL)
      {
          printf("Failed to open input file: %s.\n", testcaseParams->inputImage);
          return -1;
      }

      size = inBlockWidth * inBlockHeight * sizeof(uint16_t);
      fread(inputPtr, size, 1, fp_in);

      fclose(fp_in);
    }
    else
    {
      seed = (testcaseParams->randSeed == 0) ? _tsc_gettime() : testcaseParams->randSeed;
      srand(seed);
      printf("Random pattern test: Seed = %d\n", seed);
      createRandomPatternS(inputPtr, inBlockWidth , inBlockHeight);


    }


#if !(VCOP_HOST_EMULATION)
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                        IBUFHA_SYST, IBUFLA_SYST);

    vcop_nonMaxSuppress_mxn_16sbitPack_init(inputPtr,
                                  outputPtr,
                                  scratchBuf1,
                                  scratchBuf2,
                                  inBlockWidth,
                                  inBlockHeight,
                                  testcaseParams->inputStride,
                                  ALIGN_SIMD(outBlockWidth) / 8,
                                  testcaseParams->windowWidth,
                                  testcaseParams->windowHeight,
                                  testcaseParams->nmsThreshold,
                                   __pblock_vcop_nonMaxSuppress_mxn_16sbitPack);
#endif

    profiler_start();

#if VCOP_HOST_EMULATION
    vcop_nonMaxSuppress_mxn_16sbitPack(inputPtr,
                                outputPtr,
                                scratchBuf1,
                                scratchBuf2,
                                inBlockWidth,
                                inBlockHeight,
                                testcaseParams->inputStride,
                                ALIGN_SIMD(outBlockWidth) / 8,
                                testcaseParams->windowWidth,
                                testcaseParams->windowHeight,
                                testcaseParams->nmsThreshold);
#else
    VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                    IBUFHA_VCOP, IBUFLA_VCOP);

    /*---------------------------------------------------------------------*/
    /*  Function call to the VCOP-C API to be tested                       */
    /*---------------------------------------------------------------------*/
    vcop_nonMaxSuppress_mxn_16sbitPack_vloops(__pblock_vcop_nonMaxSuppress_mxn_16sbitPack);
    _vcop_vloop_done();

    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                    IBUFHA_SYST, IBUFLA_SYST);

#endif
    profiler_end();

    /*---------------------------------------------------------------------*/
    /*  Function call to the Natural-C API to be tested                    */
    /*---------------------------------------------------------------------*/

    vcop_nonMaxSuppress_mxn_16sbitPack_cn(inputPtr,
                                    outputPtrRef,
                                    inBlockWidth,
                                    inBlockHeight,
                                    testcaseParams->inputStride,
                                    ALIGN_SIMD(outBlockWidth) / 8,
                                    testcaseParams->windowWidth,
                                    testcaseParams->windowHeight,
                                    testcaseParams->nmsThreshold);




    for ( j = 0 ; j < outBlockHeight; j++)
    {
      for ( i = 0; i < ALIGN_SIMD(outBlockWidth) / 8; i++)
      {
        if ( i == ((ALIGN_SIMD(outBlockWidth) / 8) - 1) )
        {
          mask = 0xFF >> (ALIGN_SIMD(outBlockWidth) - outBlockWidth);
        }
        else
        {
          mask = 0xFFU;
        }

        if ( (outputPtr[i + (j * ALIGN_SIMD(outBlockWidth) / 8)] & mask) !=
          (outputPtrRef[i + (j * ALIGN_SIMD(outBlockWidth)/ 8)] & mask))
        {
          status = -1;
          printf ( "Output not Bit matching for iteration %d at (%d,%d) \n", iter,i,j);
          break;
        }
      }
      if ( status != 0 )
      {
        break;
      }
    }

    statusStr = status ? "FAILED":"PASSED";
    printf(" nmsMxn16sBitPackTest : Itereatio Number %d : %s \n",iter , statusStr);

  }

  if(fp_out != NULL)
  {
    fwrite(outputPtr , outBlockWidth * outBlockHeight,
                    1, fp_out);
    fclose(fp_out);
  }

#if (VCOP_HOST_EMULATION)
  if ( inputPtr != NULL )
  {
    free ( inputPtr);
  }

  if ( scratchBuf1 != NULL )
  {
    free ( scratchBuf1);
  }

  if ( scratchBuf2 != NULL )
  {
    free ( scratchBuf2);
  }

  if ( outputPtr != NULL )
  {
    free ( outputPtr);
  }

  if ( outputPtrRef != NULL )
  {
    free ( outputPtrRef);
  }
#endif


  return status;

}


int32_t nmsMxn16sTest(sNms_mxn_16s_Config * testcaseParams)
{
  int32_t iter ,i ,j , status = 0;
  uint32_t seed;
  FILE *fp_in = NULL, *fp_out = NULL;
  uint32_t   size;

  uint16_t * inputPtr = NULL;
  uint8_t  * outputPtr = NULL;
  uint16_t * scratchBuf1 = NULL;
  uint16_t * scratchBuf2 = NULL;
  uint8_t  * outputPtrRef = NULL;
  uint16_t   inBlockWidth;
  uint16_t   inBlockHeight;
  char  *statusStr = NULL;

  uint16_t   outBlockWidth;
  uint16_t   outBlockHeight;

  profiler_init();

  inBlockWidth    = testcaseParams->width;
  inBlockHeight   = testcaseParams->height;

  outBlockWidth   = testcaseParams->width - (testcaseParams->windowWidth - 1);
  outBlockHeight  = testcaseParams->height - (testcaseParams->windowHeight - 1);

  #if (!VCOP_HOST_EMULATION)
  inputPtr      = (uint16_t*)vcop_malloc(VCOP_IBUFLA , ALIGN_2SIMD(inBlockWidth) * inBlockHeight * sizeof(uint16_t));
  /* We are allocating more memory for output block then needed because we initialize
  outputPtr to zero in a loop which is running for more number of times */
  outputPtr     = (uint8_t*)vcop_malloc(VCOP_IBUFHA, ALIGN_2SIMD(inBlockWidth) * outBlockHeight );
  scratchBuf1   = (uint16_t*)vcop_malloc(VCOP_WMEM, ALIGN_2SIMD(inBlockWidth) * inBlockHeight * sizeof(uint16_t));
  scratchBuf2   = (uint16_t*)vcop_malloc(VCOP_IBUFHA, ALIGN_SIMD(inBlockWidth) * inBlockHeight * sizeof(uint16_t));
#else
  inputPtr      = (uint16_t*)malloc(ALIGN_2SIMD(inBlockWidth) * inBlockHeight * sizeof(uint16_t));
  /* We are allocating more memory for output block then needed because we initialize
  outputPtr to zero in a loop which is running for more number of times */
  outputPtr     = (uint8_t*)malloc( ALIGN_2SIMD(inBlockWidth) * outBlockHeight);
  scratchBuf1   = (uint16_t*)malloc( ALIGN_2SIMD(inBlockWidth) * inBlockHeight * sizeof(uint16_t));
  scratchBuf2   = (uint16_t*)malloc( ALIGN_SIMD(inBlockWidth) * inBlockHeight * sizeof(uint16_t));

#endif

  outputPtrRef  = (uint8_t*)malloc( ALIGN_SIMD(inBlockWidth) * outBlockHeight);

  if(strcmp(testcaseParams->outputImage, ""))
  {
    fp_out = fopen((const char*)testcaseParams->outputImage, "wb+");
  }

  if(fp_out == NULL)
  {
    printf("Failed to open Output file.\n");
  }

  for (iter = 0; iter < testcaseParams->numIter; iter++)
  {

    if ( strcmp(testcaseParams->inputImage, "" ) )
    {
      printf("File Test\n");
      fp_in = fopen((const char *)testcaseParams->inputImage, "rb");

      if(fp_in == NULL)
      {
          printf("Failed to open input file: %s.\n", testcaseParams->inputImage);
          return -1;
      }

      size = inBlockWidth * inBlockHeight * sizeof(uint16_t);
      fread(inputPtr, size, 1, fp_in);

      fclose(fp_in);
    }
    else
    {
      seed = (testcaseParams->randSeed == 0) ? _tsc_gettime() : testcaseParams->randSeed;
      srand(seed);
      printf("Random pattern test: Seed = %d\n", seed);
      createRandomPattern(inputPtr, inBlockWidth , inBlockHeight);

    }


#if !(VCOP_HOST_EMULATION)
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                        IBUFHA_SYST, IBUFLA_SYST);

    vcop_nonMaxSuppress_mxn_16s_init(inputPtr,
                                  outputPtr,
                                  scratchBuf1,
                                  scratchBuf2,
                                  inBlockHeight,
                                  inBlockWidth,
                                  inBlockWidth,
                                  inBlockWidth,
                                  testcaseParams->windowWidth,
                                  testcaseParams->windowHeight,
                                  testcaseParams->nmsThreshold,
                                   __pblock_vcop_nonMaxSuppress_mxn_16s);
#endif

    profiler_start();

#if VCOP_HOST_EMULATION
    vcop_nonMaxSuppress_mxn_16s(inputPtr,
                                outputPtr,
                                scratchBuf1,
                                scratchBuf2,
                                inBlockHeight,
                                inBlockWidth,
                                inBlockWidth,
                                inBlockWidth,
                                testcaseParams->windowWidth,
                                testcaseParams->windowHeight,
                                testcaseParams->nmsThreshold);
#else
    VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                    IBUFHA_VCOP, IBUFLA_VCOP);

    /*---------------------------------------------------------------------*/
    /*  Function call to the VCOP-C API to be tested                       */
    /*---------------------------------------------------------------------*/
    vcop_nonMaxSuppress_mxn_16s_vloops(__pblock_vcop_nonMaxSuppress_mxn_16s);
    _vcop_vloop_done();

    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                    IBUFHA_SYST, IBUFLA_SYST);

#endif
    profiler_end();

    /*---------------------------------------------------------------------*/
    /*  Function call to the Natural-C API to be tested                    */
    /*---------------------------------------------------------------------*/
    vcop_nonMaxSuppress_mxn_16s_cn(inputPtr,
                                    outputPtrRef,
                                    inBlockHeight,
                                    inBlockWidth,
                                    testcaseParams->windowWidth,
                                    testcaseParams->windowHeight,
                                    testcaseParams->nmsThreshold);

    for ( j = 0 ; j < outBlockHeight; j++)
    {
      for ( i = 0; i < outBlockWidth; i++)
      {
        if ( outputPtr[i + (j * inBlockWidth)] != outputPtrRef[i + (j * inBlockWidth)])//:TODO: stride
        {
          status = -1;
          printf ( "Output not Bit matching for iteration %d at (%d,%d) \n", iter,i,j);
          break;
        }
      }
      if ( status != 0 )
      {
        break;
      }
    }

    statusStr = status ? "FAILED":"PASSED";
    printf(" nmsMxn16sTest : Itereatio Number %d : %s \n",iter , statusStr);

  }

  if(fp_out != NULL)
  {
    fwrite(outputPtr , outBlockWidth * outBlockHeight,
                    1, fp_out);
    fclose(fp_out);
  }

#if (VCOP_HOST_EMULATION)
  if ( inputPtr != NULL )
  {
    free ( inputPtr);
  }

  if ( scratchBuf1 != NULL )
  {
    free ( scratchBuf1);
  }

  if ( scratchBuf2 != NULL )
  {
    free ( scratchBuf2);
  }

  if ( outputPtr != NULL )
  {
    free ( outputPtr);
  }

  if ( outputPtrRef != NULL )
  {
    free ( outputPtrRef);
  }
#endif

  return status;

}

int main(int argc, char *argv[])
{
  int status = 0;
  char configFile[FILE_NAME_SIZE]={0};
  char configLine[MAX_CONFIG_LINE_SIZE];
  char configParam[MAX_PARAM_STRING_SIZE];
  int8_t         *LinePtr;
  FILE * fp;
  int32_t         lineNum = -1;
  int32_t         config_cmd;

  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,CONFIG_LIST_FILE_NAME);
  }

  fp = fopen((const char *)configFile , "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s \n",CONFIG_LIST_FILE_NAME);
    return(status);
  }

  while ( 1 )
  {
    memset(configLine, 0, MAX_CONFIG_LINE_SIZE);
    status = (int)fgets(configLine,MAX_CONFIG_LINE_SIZE,fp);
    LinePtr = (int8_t *)configLine;
    if ((status == EOF) || (status == 0))
    {
      break;
    }
    status = 0;
    lineNum++;
    sscanf((const char *)LinePtr, "%d",&config_cmd);
    sscanf((const char *)LinePtr, "%s",configParam);

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
      LinePtr = (int8_t *)moveToNextElement(configParam,(char *)LinePtr);
      status  = sscanf((const char *)LinePtr, "%s",configFile);
      printf("\n Processing config file %s !\n", configFile);
      status = readparamfile(configFile, &gsTokenMap_nms_mxn_16s[0]);
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }

      /* Validate the kernel  */
      status = nmsMxn16sTest(&gConfig_nms_mxn_16s);

      /* Validate the kernel  */
      status |= nmsMxn16sBitPackTest(&gConfig_nms_mxn_16s);


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


