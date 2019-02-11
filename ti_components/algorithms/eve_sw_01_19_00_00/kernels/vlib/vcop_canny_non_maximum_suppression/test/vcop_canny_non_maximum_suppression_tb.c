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
#include "vcop_canny_non_maximum_suppression_config.h"
#include "vcop_canny_non_maximum_suppression_cn.h"

#include <math.h>


/* ------------------------------------------------------------------------ */
/*  Include prototypes for "C" implementation of Gradient XY and magnitude kernel  */
/*  function.                                                               */
/* ------------------------------------------------------------------------ */
//#include "vcop_vec_gradients_xy_and_magnitude_c.h"
void vcop_vec_gradients_xy_and_magnitude_cn
(
    uint8_t  pIn[],
    int16_t          pGradX[],
    int16_t          pGradY[],
    uint16_t          pMag[],
    uint16_t width,
    uint16_t height,
    uint16_t pitch
)
{
  int32_t i , j;
  uint32_t inT, inL, inR, inB;
  uint8_t * rowPtr;
  for (j = 0; j < height; j++)
  {
    rowPtr = &pIn[j * pitch];
    for (i = 0; i < width; i++)
    {

      inT = rowPtr[i+1];
      inL = rowPtr[i+pitch];
      inR = rowPtr[i+pitch+2];
      inB = rowPtr[i+2*pitch+1];

      pGradX[i + (j*pitch)] = inR - inL;
      pGradY[i + (j*pitch)] = inB - inT;
      pMag[i + (j*pitch)]   = abs(pGradX[i + (j*pitch)]) + abs(pGradY[i + (j*pitch)]);
    }
  }
}


#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_canny_non_maximum_suppression_kernel.k"
#else
#include "../inc/vcop_canny_non_maximum_suppression_kernel.h"
#endif

//#define __DEBUG
#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

#define ALIGN_2SIMD(a)   (((a) + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))
#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))

void fillDefaultConfig(sCanny_non_maximum_suppression_Config * params)
{
  strcpy(params->inputData,"");
  params->width             = 34;
  params->height            = 34;
  params->inDataPitch       = 34;
  params->outputPitch       = 34;
  params->lowThreshold      = 50;
  params->highThreshold     = 150;
  params->numIter           = 1;
}

//#define FIXEDPATTERN
///////////////////////////////////////
// Makes a 32x32 random
///////////////////////////////////////
static void CreatePattern(uint8_t * p, uint16_t imgWidth, uint16_t imgHeight, uint16_t imgPitch, uint8_t maxVal)
{
  int32_t i, j;

  for ( j = 0 ; j < imgWidth; j++)
  {
    for (i = 0; i < imgHeight; i++)
    {
#ifdef FIXEDPATTERN
      p[i + j * imgPitch] = (i * j)% maxVal;

#else
      p[i + j * imgPitch] = rand() % maxVal;
#endif
    }
  }


}


int32_t cannyNmsTest(sCanny_non_maximum_suppression_Config * testcaseParams)
{
  int32_t i,j, iter, status = 0;
  uint32_t seed;
  FILE *fp_in = NULL;

  uint8_t * pInputData = NULL;
  uint8_t * pIndex    = NULL;
  uint16_t * pMaxCase1 = NULL;
  uint16_t * pMaxCase2 = NULL;
  uint16_t * pMaxCase3 = NULL;
  uint16_t * pMaxCase4 = NULL;
  int16_t * pGradX    = NULL;
  int16_t * pGradY    = NULL;
  uint16_t * pGradMag = NULL;
  uint8_t * pOutput = NULL;


  uint8_t * pIndexRef = NULL;
  uint16_t * pMaxCase1Ref = NULL;
  uint16_t * pMaxCase2Ref = NULL;
  uint16_t * pMaxCase3Ref = NULL;
  uint16_t * pMaxCase4Ref = NULL;
  uint8_t * pOutputRef = NULL;
  char    testcaseName[100];

  profiler_init();
  vcop_minit();


#if VCOP_HOST_EMULATION
  /* Multiplication by two because it stores x and y coordinate in packed format*/
  pInputData = (uint8_t *) malloc((ALIGN_2SIMD(testcaseParams->width - 2) + 2 ) *
                                  testcaseParams->height);

  pIndex      = (uint8_t *) malloc( ALIGN_2SIMD(testcaseParams->width - 2) *
                                  (testcaseParams->height) * sizeof(uint8_t));

  pMaxCase1   = (uint16_t *) malloc(ALIGN_2SIMD(testcaseParams->width - 2)*
                                  (testcaseParams->height ) * sizeof(uint16_t));

  pMaxCase2   = (uint16_t *) malloc(ALIGN_2SIMD(testcaseParams->width - 2)*
                                (testcaseParams->height ) * sizeof(uint16_t));

  pMaxCase3   = (uint16_t *) malloc(ALIGN_2SIMD(testcaseParams->width - 2)*
                                  (testcaseParams->height ) * sizeof(uint16_t));
  pMaxCase4   = (uint16_t *) malloc(ALIGN_2SIMD(testcaseParams->width - 2)*
                                (testcaseParams->height ) * sizeof(uint16_t));

  pGradX      = (int16_t *) malloc( ALIGN_2SIMD(testcaseParams->width - 2)*
                                  (testcaseParams->height) * sizeof(int16_t));

  pGradY      = (int16_t *) malloc( ALIGN_2SIMD(testcaseParams->width - 2)*
                                  (testcaseParams->height) * sizeof(int16_t));

  pGradMag    = (uint16_t *) malloc( ALIGN_2SIMD(testcaseParams->width - 2)*
                                  (testcaseParams->height) * sizeof(uint16_t));
#else
     /* vcop_malloc doesnt allow to allocate full 16k of image buffer LA. Hence using
     hard coded address for it edgeMap*/
  pInputData = (uint8_t *) vcop_malloc(VCOP_IBUFLA,(ALIGN_2SIMD(testcaseParams->width - 2) + 2) *
                                  testcaseParams->height);

  pGradX   = (int16_t *) vcop_malloc(VCOP_IBUFHA, ALIGN_2SIMD(testcaseParams->width - 2)*
                                (testcaseParams->height) * sizeof(int16_t));

  pGradY   = (int16_t *) vcop_malloc(VCOP_IBUFHA, ALIGN_2SIMD(testcaseParams->width - 2)*
                                (testcaseParams->height) * sizeof(int16_t));

  pIndex     = (uint8_t *) vcop_malloc(VCOP_IBUFHA, ALIGN_2SIMD(testcaseParams->width - 2)*
                                  (testcaseParams->height) * sizeof(uint8_t));

  if ( pGradX)
  {
    vcop_free(pGradX);
  }
  if ( pGradY)
  {
    vcop_free(pGradY);
  }

  pMaxCase1   = (uint16_t *) vcop_malloc(VCOP_WMEM, ALIGN_2SIMD(testcaseParams->width - 2)*
                                  (testcaseParams->height) * sizeof(uint16_t));

  pMaxCase2   = (uint16_t *) vcop_malloc(VCOP_WMEM, ALIGN_2SIMD(testcaseParams->width - 2)*
                                (testcaseParams->height) * sizeof(uint16_t));

  pMaxCase3   = (uint16_t *) vcop_malloc(VCOP_WMEM, ALIGN_2SIMD(testcaseParams->width - 2)*
                                (testcaseParams->height) * sizeof(uint16_t));

  pMaxCase4   = (uint16_t *) vcop_malloc(VCOP_WMEM, ALIGN_2SIMD(testcaseParams->width - 2)*
                                (testcaseParams->height) * sizeof(uint16_t));


  pGradMag   = (uint16_t *) vcop_malloc(VCOP_WMEM, ALIGN_2SIMD(testcaseParams->width)*
                                (testcaseParams->height) * sizeof(uint16_t));


#endif
  pIndexRef      = (uint8_t *) malloc( (testcaseParams->width)*
                                  (testcaseParams->height) * sizeof(uint8_t));

  pMaxCase1Ref   = (uint16_t *) malloc((testcaseParams->width)*
                                  (testcaseParams->height ) * sizeof(uint16_t));

  pMaxCase2Ref   = (uint16_t *) malloc((testcaseParams->width)*
                                (testcaseParams->height ) * sizeof(uint16_t));

  pMaxCase3Ref   = (uint16_t *) malloc((testcaseParams->width)*
                                  (testcaseParams->height ) * sizeof(uint16_t));
  pMaxCase4Ref   = (uint16_t *) malloc((testcaseParams->width)*
                                (testcaseParams->height ) * sizeof(uint16_t));


  for (iter = 0; iter < testcaseParams->numIter; iter++)
  {
    printf("Iteration %d\n", iter);

    if(strcmp(testcaseParams->inputData, ""))
    {
      printf("File Test\n");
      fp_in = fopen((const char *)testcaseParams->inputData, "rb");

      if(fp_in == NULL)
      {
          printf("Failed to open input file: %s.\n", testcaseParams->inputData);
          return -1;
      }

      fread(pInputData, testcaseParams->width * testcaseParams->height,
                        1, fp_in);


      fclose(fp_in);
    }
    else
    {
      /* Generate input data */
      seed = (testcaseParams->randSeed == 0) ? _tsc_gettime() : testcaseParams->randSeed;
      srand(seed);
      printf("Random pattern test: Seed = %d\n", seed);
      CreatePattern(pInputData,
                    testcaseParams->width,
                    testcaseParams->height,
                    testcaseParams->inDataPitch,
                    255);
    }

    vcop_vec_gradients_xy_and_magnitude_cn(pInputData,
                                           pGradX,
                                           pGradY,
                                           pGradMag,
                                           testcaseParams->width - 2,
                                           testcaseParams->height - 2,
                                           testcaseParams->inDataPitch);


    strcpy(testcaseName, (char *)testcaseParams->testCaseName);
    strcat(testcaseName," Canny NMS Bin Indexing");

    profiler_testCaseInfo((int8_t *)testcaseName,(int8_t *)" ",0);
    printparams(&gsTokenMap_canny_non_maximum_suppression[0],(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)(testcaseParams),sizeof(sCanny_non_maximum_suppression_Config)) ;



    profiler_start();
    vcop_canny_bin_indexing(pGradX,
                          pGradY,
                          pIndex,
                          (testcaseParams->width - 2),
                          (testcaseParams->height - 2),
                          testcaseParams->inDataPitch
                          );
    profiler_end_print(1);

    vcop_canny_bin_indexing_cn(pGradX,
                         pGradY,
                         pIndexRef,
                         (testcaseParams->width - 2),
                         (testcaseParams->height - 2),
                         testcaseParams->inDataPitch
                         );


    for ( j = 0 ; j < (testcaseParams->height - 2); j++ )
    {
      for ( i = 0 ; i < (testcaseParams->width - 2); i++)
      {
        if ( pIndex[i + j * testcaseParams->inDataPitch ] != pIndexRef[i + j * testcaseParams->inDataPitch])
        {
          status = -1;
          printf("vcop_canny_bin_indexing : output not bit matching at (%d,%d) \n",i , j);
          goto EXIT;
        }
      }
    }

EXIT:
    profiler_printStatus(status);

    strcpy(testcaseName, (char *)testcaseParams->testCaseName);
    strcat(testcaseName," Canny NMS Max Cases");

    profiler_testCaseInfo((int8_t *)testcaseName,(int8_t *)" ",0);
    printparams(&gsTokenMap_canny_non_maximum_suppression[0],(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)(testcaseParams),sizeof(sCanny_non_maximum_suppression_Config)) ;

    profiler_start();
    vcop_canny_nms_max_cases(pGradMag,
                           pMaxCase1,
                           pMaxCase2,
                           pMaxCase3,
                           pMaxCase4,
                          (testcaseParams->width - 2),
                          (testcaseParams->height - 2),
                          testcaseParams->inDataPitch
                          );
    profiler_end_print(1);



    vcop_canny_nms_max_cases_cn(pGradMag,
                           pMaxCase1Ref,
                           pMaxCase2Ref,
                           pMaxCase3Ref,
                           pMaxCase4Ref,
                          (testcaseParams->width - 2),
                          (testcaseParams->height - 2),
                          testcaseParams->inDataPitch
                          );


    for ( j = 0 ; j < (testcaseParams->height - 2); j++ )
    {
      for ( i = 0 ; i < (testcaseParams->width - 2); i++)
      {
        if (pMaxCase1[i + j * testcaseParams->inDataPitch] != pMaxCase1Ref[i + j * testcaseParams->inDataPitch])
        {
          status = -1;
          printf("vcop_canny_nms_max_cases : output for case 1 not bit matching at (%d,%d) \n",i , j);
          goto EXIT1;
        }

        if (pMaxCase2[i + j * testcaseParams->inDataPitch] != pMaxCase2Ref[i + j * testcaseParams->inDataPitch])
        {
          status = -1;
          printf("vcop_canny_nms_max_cases : output for case 2 not bit matching at (%d,%d) \n",i , j);
          goto EXIT1;
        }
        if (pMaxCase3[i + j * testcaseParams->inDataPitch] != pMaxCase3Ref[i + j * testcaseParams->inDataPitch])
        {
          status = -1;
          printf("vcop_canny_nms_max_cases : output for case 3 not bit matching at (%d,%d) \n",i , j);
          goto EXIT1;
        }
        if (pMaxCase4[i + j * testcaseParams->inDataPitch] != pMaxCase4Ref[i + j * testcaseParams->inDataPitch])
        {
          status = -1;
          printf("vcop_canny_nms_max_cases : output for case 4 not bit matching at (%d,%d) \n",i , j);
          goto EXIT1;
        }
      }
    }

EXIT1:
    profiler_printStatus(status);

    pOutput = (uint8_t *)pGradMag;
    pOutputRef = (uint8_t *)pInputData;

    memset ( pOutput,    0xcd, (testcaseParams->width - 2) * (testcaseParams->height - 2) );
    memset ( pOutputRef, 0xcd, (testcaseParams->width - 2) * (testcaseParams->height - 2) );

    strcpy(testcaseName, (char *)testcaseParams->testCaseName);
    strcat(testcaseName," Canny NMS Double Thresholding");

    profiler_testCaseInfo((int8_t *)testcaseName,(int8_t *)" ",0);
    printparams(&gsTokenMap_canny_non_maximum_suppression[0],(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)(testcaseParams),sizeof(sCanny_non_maximum_suppression_Config)) ;

    profiler_start();
    vcop_canny_nms_double_thresholding(pIndex,
                                       pMaxCase1,
                                       pMaxCase2,
                                       pMaxCase3,
                                       pMaxCase4,
                                       pOutput,
                                       50,
                                       150,
                                      (testcaseParams->width - 2),
                                      (testcaseParams->height - 2),
                                      testcaseParams->inDataPitch,
                                      testcaseParams->outputPitch);
    profiler_end_print(1);


    vcop_canny_nms_double_thresholding_cn(pIndex,
                                       pMaxCase1,
                                       pMaxCase2,
                                       pMaxCase3,
                                       pMaxCase4,
                                       pOutputRef,
                                       50,
                                       150,
                                      (testcaseParams->width - 2),
                                      (testcaseParams->height - 2),
                                      testcaseParams->inDataPitch,
                                      testcaseParams->outputPitch);

    for ( j = 0 ; j < (testcaseParams->height - 2); j++ )
    {
      for ( i = 0 ; i < (testcaseParams->width - 2); i++)
      {
        if ( pOutput[i + j * testcaseParams->inDataPitch] != pOutputRef[i + j * testcaseParams->inDataPitch])
        {
          status = -1;
          printf("vcop_canny_nms_double_thresholding : output not bit matching at (%d,%d) \n",i , j);
          goto EXIT2;
        }
      }
    }
EXIT2:
    profiler_printStatus(status);

  }


  printf(status ? "cannyNmsTest: FAIL\n" : "cannyNmsTest: PASS\n");
#if VCOP_HOST_EMULATION
  if ( pInputData)
  {
    free(pInputData);
  }

  if ( pIndex)
  {
    free(pIndex);
  }
  if ( pMaxCase1)
  {
    free(pMaxCase1);
  }
  if ( pMaxCase2)
  {
    free(pMaxCase2);
  }
  if ( pMaxCase3)
  {
    free(pMaxCase3);
  }
  if ( pMaxCase4)
  {
    free(pMaxCase4);
  }

  if ( pGradX)
  {
    free(pGradX);
  }

  if ( pGradY)
  {
    free(pGradY);
  }

  if ( pGradMag)
  {
    free(pGradMag);
  }
#else
  if ( pInputData)
  {
    vcop_free(pInputData);
  }

  if ( pIndex)
  {
    vcop_free(pIndex);
  }
  if ( pMaxCase1)
  {
    vcop_free(pMaxCase1);
  }
  if ( pMaxCase2)
  {
    vcop_free(pMaxCase2);
  }
  if ( pMaxCase3)
  {
    vcop_free(pMaxCase3);
  }
  if ( pMaxCase4)
  {
    vcop_free(pMaxCase4);
  }


  if ( pGradMag)
  {
    vcop_free(pGradMag);
  }
#endif
  if ( pIndexRef)
  {
    free(pIndexRef);
  }
  if ( pMaxCase1Ref)
  {
    free(pMaxCase1Ref);
  }
  if ( pMaxCase2Ref)
  {
    free(pMaxCase2Ref);
  }
  if ( pMaxCase3Ref)
  {
    free(pMaxCase3Ref);
  }
  if ( pMaxCase4Ref)
  {
    free(pMaxCase4Ref);
  }

  profiler_deinit();

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

  CF_profile_init(3, "Canny_NMS");

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
      status = readparamfile(configFile, &gsTokenMap_canny_non_maximum_suppression[0]);
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }


      /* Validate the kernel  */
      status = cannyNmsTest(&gConfig_canny_non_maximum_suppression);

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

