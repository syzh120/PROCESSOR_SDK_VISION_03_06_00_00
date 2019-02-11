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

#include <vcop.h>
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_harrisScore_32_7x7_config.h"

/* ------------------------------------------------------------------------ */
/*  Include prototypes for "C" implementation of Harris Score 7x7  */
/*  function.                                                               */
/* ------------------------------------------------------------------------ */
#include "vcop_harrisScore_32_7x7_cn.h"

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")
#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_harrisScore_32_7x7_kernel.k"
#else
#include "../inc/vcop_harrisScore_32_7x7_kernel.h"
#endif

//#define __DEBUG

#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))
#define ALIGN_2SIMD(a)   (((a) + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))

#define NUM_ITER         (1)
#define MAX_WIDTH         (38)
#define MAX_HEIGHT        (38)

#define ALIGNED_WIDTH ALIGN_SIMD(MAX_WIDTH)

#define GRADIENT_BORDER (2U)


void fillDefaultConfig(sHarris_score_32_7x7_Config * params)
{
  strcpy(params->inputBlock  , "");
  strcpy(params->outputScore , "");
  params->width             = MAX_WIDTH;
  params->height            = MAX_HEIGHT;
  params->srcPitch          = MAX_WIDTH;
  params->destPitch         = MAX_HEIGHT;
  params->sensitivityParam  = 1310;
  params->randSeed          = 0;
  params->numIter           = 1;
}

int vcop_harrisScore_32_7x7
(
    short *  gradX,
    short *  gradY,
    int width,
    int height,
    int *  outm,
    unsigned short k,
    int * XX,
    int * YY,
    int * XY,
    unsigned int * detL,
    int * detH,
    unsigned char windowSize
)
{

   char *pIn1 = (char *) (XX);
   char *pIn2 = (char *) (YY);
   char *pIn3 = (char *) (XY);

    vcop_harrisScore_32_7x7_1
    (
    gradX,
    gradY,
    width,
    height,
    width,
    width,
    windowSize,
    XX,
    YY,
    XY
    );

    vcop_harrisScore_32_7x7_2
    (
    width  - (windowSize - 1),
    height - (windowSize - 1),
    width,
    width,
    outm,
    k,
    XX,
    YY,
    XY,
    (unsigned short *) (pIn1),
    (unsigned short *) (pIn2),
    (unsigned short *) (pIn3),
    (short *)          (pIn1 + 2),
    (short *)          (pIn2 + 2),
    (short *)          (pIn3 + 2),
    detL,
    detH
    );

  return 0;
}

///////////////////////////////////////
// Makes a 32x32 random
///////////////////////////////////////

static void CreateRandPattern(uint8_t *p, unsigned short w, unsigned short h, unsigned short pitch)
{
    int i, j;
    for (j = 0; j < h; j++)
    {
        for (i = 0; i < w; i++)
        {
          p[i + j * pitch] = rand() % 255;
        }
    }
}


void vcop_vec_gradients_xy_and_magnitude_cn
(
    unsigned char  pIn[],
    short          pGradX[],
    short          pGradY[],
    short          pMag[],
    unsigned short width,
    unsigned short height
)
{
    int i4;
    unsigned int inT, inL, inR, inB;

    for (i4 = 0; i4 < width*height; i4++)
    {
        inT = pIn[i4+1];
        inL = pIn[i4+width];
        inR = pIn[i4+width+2];
        inB = pIn[i4+2*width+1];

        pGradX[i4] =  inR - inL;
        pGradY[i4] =  inB - inT;
        pMag  [i4] =  abs(pGradX[i4]) + abs(pGradY[i4]);
    }
}

#if (VCOP_HOST_EMULATION)
#define harris_score_malloc(heap, size)   malloc(size)
#define harris_score_free(ptr)            free(ptr)
#else
#define harris_score_malloc(heap, size)   vcop_malloc(heap, size)
#define harris_score_free(ptr)            vcop_free(ptr)
#endif


int32_t test_harrisScore_32_7x7(sHarris_score_32_7x7_Config * testcaseParams)
{
    int32_t i,j, iter, status;
    uint32_t seed;
    FILE *fp_in = NULL, *fp_out = NULL;

    uint8_t  * inputData = NULL;
    int16_t  * gradX = NULL;
    int16_t  * gradY = NULL;
    uint16_t  * gradMag = NULL;

    int32_t * outHarrisScore = NULL;
    int32_t * scratchXX = NULL;
    int32_t * scratchYY = NULL;
    int32_t * scratchXY = NULL;

    int32_t * detH = NULL;
    uint32_t * detL = NULL;

    int32_t * outHarrisScoreRef = NULL;

    uint16_t   harrisInBlockWidth;
    uint16_t   harrisInBlockHeight;

    uint16_t   destinationPitch;

    profiler_init();

    harrisInBlockWidth  = (testcaseParams->width);
    harrisInBlockHeight = (testcaseParams->height);

    status = 1;

    inputData      = (uint8_t *)harris_score_malloc(VCOP_IBUFLA , testcaseParams->srcPitch * (testcaseParams->height + GRADIENT_BORDER)  * sizeof(uint8_t));
    if( inputData == NULL )
    {
      goto Exit;
    }

    gradX     = (int16_t*)harris_score_malloc(VCOP_IBUFLB, harrisInBlockWidth * harrisInBlockHeight * sizeof(int16_t) );
    if( gradX == NULL )
    {
      goto Exit;
    }

    gradY     = (int16_t*)harris_score_malloc(VCOP_WMEM, harrisInBlockWidth * harrisInBlockHeight * sizeof(int16_t) );
    if( gradY == NULL )
    {
      goto Exit;
    }

    gradMag     = (uint16_t*)harris_score_malloc(VCOP_IBUFHA, harrisInBlockWidth * harrisInBlockHeight * sizeof(uint16_t) );
    if( gradMag == NULL )
    {
      goto Exit;
    }

#if !VCOP_HOST_EMULATION
    /* this is not used so just release it */
    harris_score_free(gradMag);

    harris_score_free(inputData);
#endif
    scratchXX   = (int32_t*)harris_score_malloc(VCOP_IBUFLA, ALIGN_SIMD(harrisInBlockWidth) * (harrisInBlockHeight + 1) * sizeof(int32_t));
    if( scratchXX == NULL )
    {
      goto Exit;
    }
    scratchYY   = (int32_t*)harris_score_malloc(VCOP_WMEM, ALIGN_SIMD(harrisInBlockWidth) * (harrisInBlockHeight + 1) * sizeof(int32_t));
    if( scratchYY == NULL )
    {
      goto Exit;
    }

    if ( testcaseParams->scoreMethod == 0 )
    {
      scratchXY   = (int32_t*)harris_score_malloc(VCOP_IBUFHA, ALIGN_SIMD(harrisInBlockWidth) * (harrisInBlockHeight + 1) * sizeof(int32_t));
      if( scratchXY == NULL )
      {
        goto Exit;
      }

      detL   = (uint32_t*)harris_score_malloc(VCOP_WMEM, ALIGN_SIMD(harrisInBlockWidth) * harrisInBlockHeight * sizeof(uint32_t));
      if( detL == NULL )
      {
        goto Exit;
      }
      detH   = (int32_t*)harris_score_malloc(VCOP_IBUFHA, ALIGN_SIMD(harrisInBlockWidth) * harrisInBlockHeight * sizeof(int32_t));
      if( detH == NULL )
      {
        goto Exit;
      }
    }
    outHarrisScore = (int32_t*)harris_score_malloc(VCOP_IBUFLA, ALIGN_SIMD(harrisInBlockWidth) * harrisInBlockHeight * sizeof(int32_t));
    if( outHarrisScore == NULL )
    {
      goto Exit;
    }

    outHarrisScoreRef = (int32_t*)malloc( ALIGN_SIMD(harrisInBlockWidth) * harrisInBlockHeight * sizeof(int32_t));
    if( outHarrisScoreRef == NULL )
    {
      goto Exit;
    }

    for (iter = 0; iter < testcaseParams->numIter; iter++)
    {
        printf("Iteration %d\n", iter);

        if(strcmp(testcaseParams->inputBlock, "")) {
            printf("File Test\n");
            fp_in = fopen((const char *)testcaseParams->inputBlock, "rb");
            if(fp_in == NULL) {
                printf("Failed to open input file: %s.\n", testcaseParams->inputBlock);
                return -1;
            }
            fread(inputData, testcaseParams->width * testcaseParams->height, 1, fp_in);
            fclose(fp_in);
        }
        else {
            /* Generate input data */
            seed = (testcaseParams->randSeed == 0) ? _tsc_gettime() : testcaseParams->randSeed;
            srand(seed);
            printf("Random pattern test: Seed = %d\n", seed);
            CreateRandPattern(inputData, testcaseParams->width, testcaseParams->height, testcaseParams->srcPitch);
        }

        vcop_vec_gradients_xy_and_magnitude_cn(inputData,
                                               gradX,
                                               gradY,
                                               (int16_t *)gradMag,
                                               testcaseParams->width,
                                               testcaseParams->height);


        if ( testcaseParams->scoreMethod == 0 )
        {
          profiler_start();


          vcop_harrisScore_32_7x7(gradX,
                                  gradY,
                                  testcaseParams->width,
                                  testcaseParams->height,
                                  outHarrisScore,
                                  testcaseParams->sensitivityParam,
                                  scratchXX,
                                  scratchYY,
                                  scratchXY,
                                  detL,
                                  detH,
                                  testcaseParams->windowSize);

          profiler_end_print(1);

          /*---------------------------------------------------------------------*/
          /*  Function call to the Natural-C API to be tested                    */
          /*  Compute Harris scores for all blocks in IMAGE_BLOCKS               */
          /*---------------------------------------------------------------------*/
          vcop_harrisScore_32_7x7_cn(gradX,
                                  gradY,
                                  testcaseParams->width,
                                  testcaseParams->height,
                                  testcaseParams->width,
                                  testcaseParams->width,
                                  testcaseParams->windowSize,
                                  outHarrisScoreRef,
                                  testcaseParams->sensitivityParam);

            destinationPitch = testcaseParams->width;
         }
        else
        {
          profiler_start();
          vcop_harrisScore_32_methodB(gradX,
                                      gradY,
                                      (uint32_t *)scratchXX,
                                      (uint32_t *)scratchYY,
                                      testcaseParams->width,
                                      testcaseParams->height,
                                      testcaseParams->width,
                                      testcaseParams->destPitch,
                                      testcaseParams->windowSize,
                                      (uint32_t *)outHarrisScore);
          profiler_end_print(1);


          vcop_harrisScore_32_methodB_cn(gradX,
                                      gradY,
                                      testcaseParams->width,
                                      testcaseParams->height,
                                      testcaseParams->width,
                                      testcaseParams->destPitch,
                                      testcaseParams->windowSize,
                                      (uint32_t *)outHarrisScoreRef);

          destinationPitch = testcaseParams->destPitch;
        }





        /*---------------------------------------------------------------------*/
        /*  Compare the results of output arrays with expected output arrays.  */
        /*---------------------------------------------------------------------*/
        status = 0;
        for(j =0; j <  testcaseParams->height - (testcaseParams->windowSize - 1); j++)
        {
            for(i =0; i <  testcaseParams->width - (testcaseParams->windowSize - 1); i++)
            {
                if(outHarrisScoreRef[(j)* destinationPitch + i] !=
                        outHarrisScore[j* destinationPitch + i])
                {
                    status = 1;
                    goto Exit1;
                }
            }
        }
Exit1:

        if ( status != 0 )
        {
          printf("NATC and Kernel C output not matching at iteration %d \n", iter);
          break;
        }

        if(strcmp(testcaseParams->outputScore , "")) {
            fp_out = fopen((const char*)testcaseParams->outputScore, "wb");
            if(fp_out != NULL) {
                fwrite(outHarrisScoreRef, 4 * testcaseParams->width *
                  testcaseParams->height, 1, fp_out);
                fclose(fp_out);
            }
            else {
                printf("Failed to open Output file.\n");
            }
        }
    }

#if VCOP_HOST_EMULATION
    if( inputData != NULL )
    {
      harris_score_free(inputData);
    }

    if( gradMag != NULL )
    {
      harris_score_free(gradMag);
    }
#endif
    if( gradX != NULL )
    {
      harris_score_free(gradX);
    }
    if( gradY != NULL )
    {
      harris_score_free(gradY);
    }

    if( scratchXX != NULL )
    {
      harris_score_free(scratchXX);
    }
    if( scratchYY != NULL )
    {
      harris_score_free(scratchYY);
    }
    if( scratchXY != NULL )
    {
      harris_score_free(scratchXY);
    }
    if( detL != NULL )
    {
      harris_score_free(detL);
    }
    if( detH != NULL )
    {
      harris_score_free(detH);
    }

    if( outHarrisScore != NULL )
    {
     harris_score_free(outHarrisScore);
    }

    if( outHarrisScoreRef != NULL )
    {
      free(outHarrisScoreRef);
    }

Exit:

    if(status != 0) {
        printf("Harris score mismatches:\n");
    }

    profiler_deinit();

    printf(status ? "test_harrisScore_32_7x7: FAIL\n" : "test_harrisScore_32_7x7: PASS\n");

    return (status);
}

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	')||(LinePtr[0] == ','))
  {
    LinePtr++;
  }
  return(LinePtr);
}

int32_t main(int32_t argc, char *argv[])
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

  CF_profile_init(3, "vcop_harrisScore_32_7x7");
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
    status = readparamfile(configFile, &gsTokenMap_harris_score_32_7x7[0]) ;
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }

      /* Validate the kernel */
      profiler_testCaseInfo((int8_t *)gConfig_harris_score_32_7x7.testCaseName, (int8_t *)gConfig_harris_score_32_7x7.testCaseDesc, 0);
      printparams(&gsTokenMap_harris_score_32_7x7[0], (int32_t)MAX_ITEMS_TO_PARSE,
                  (uint32_t)(&gConfig_harris_score_32_7x7),sizeof(sHarris_score_32_7x7_Config));

      /* Validate the kernel  */
      status = test_harrisScore_32_7x7(&gConfig_harris_score_32_7x7);

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

