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


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vcop.h"
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_contrast_stretching_config.h"


/* ------------------------------------------------------------------------ */
/*  Include prototype for the "C" implementation of SOFT ISP functions      */
/* ------------------------------------------------------------------------ */
#include "vcop_contrast_stretching_cn.h"


#if VCOP_HOST_EMULATION
  #include "..\src_kernelC\vcop_contrast_stretching_kernel.k" // kernel source
#else
  #include "vcop_contrast_stretching_kernel.h"
#endif

//#define __DEBUG

#define NUM_HISTO_BINS (256)
#define SIZE_HISTO_8_COPY (NUM_HISTO_BINS * sizeof(uint32_t) * 8)
#define SIZE_HISTOGRAM    (NUM_HISTO_BINS * sizeof(uint32_t))

#define MAX_IMG_WIDTH  (64)
#define MAX_IMG_HEIGHT (64)

void createRndPattern(uint8_t * image,
                      uint32_t width,
                      uint32_t height,
                      uint32_t pitch

                      )
{
  int32_t i, j;

  for(i = 0; i < height; i++) {
    for(j = 0; j < width; j++) {
      image[i * pitch + j] = rand() % (255);
    }
  }
}


void fillDefaultConfig(sContrastStretching_Config * params)
{
  strcpy(params->inputImage, "");
  strcpy(params->outputImage, "");
  params->imageWidth  = MAX_IMG_WIDTH;
  params->imageHeight = MAX_IMG_HEIGHT;
  params->inputPitch  = MAX_IMG_WIDTH;
  params->outputPitch  = MAX_IMG_WIDTH;
  params->randSeed    = 0;
  params->numIter     = 1;
}


int32_t main(int32_t argc, char *argv[])
{
  int32_t iter, fail, status = 0;
  uint32_t seed;
  FILE *fp_in = NULL, *fp_out = NULL;
  char configFile[FILE_NAME_SIZE];
  const char  *statusStr = NULL;
  uint32_t totalPixels;
  int32_t i;
  uint32_t minThrIndexVal;
  uint32_t maxThrIndexVal;
  uint32_t minVal;
  uint32_t maxVal;
  uint32_t minPercentileThreshold = 1;
  uint32_t maxPercentileThreshold = 99;
  uint32_t scaleFactorQ16;

  uint8_t * inputImage;
  uint8_t * outputImage;
  uint8_t * outputImageRef;
  uint32_t * yHistogram8Copy;
  uint32_t * yHistogram8CopyRef;
  uint32_t * yHistogram;
  uint32_t * yHistogramRef;
  uint32_t * transposeBuff;

  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,"../testvecs/config/contrast_stretching.cfg");
  }

  fillDefaultConfig(&gConfig_contrast_stretching);
  status = readparamfile(configFile, &gsTokenMap_contrast_stretching[0]) ;
  if(status == -1)
  {
    printf("Parser Failed. Continuing with default configuration ...\n\n");
    status = 0;
  }

  profiler_init();

#if VCOP_HOST_EMULATION
  inputImage      = (uint8_t *)malloc(gConfig_contrast_stretching.imageWidth *
                  gConfig_contrast_stretching.imageHeight);

  outputImage     = (uint8_t *)malloc(gConfig_contrast_stretching.imageWidth *
                  gConfig_contrast_stretching.imageHeight);

  yHistogram8Copy = (uint32_t *)malloc(SIZE_HISTO_8_COPY);

  yHistogram      = (uint32_t *)malloc(SIZE_HISTOGRAM);


  transposeBuff   = (uint32_t *)malloc(SIZE_HISTOGRAM * 9);

#else
  inputImage      = (uint8_t *)vcop_malloc(VCOP_IBUFLA,
                            gConfig_contrast_stretching.imageWidth *
                            gConfig_contrast_stretching.imageHeight);

  outputImage     = (uint8_t *)vcop_malloc(VCOP_IBUFHA,
                            gConfig_contrast_stretching.imageWidth *
                            gConfig_contrast_stretching.imageHeight);

  yHistogram8Copy = (uint32_t *)vcop_malloc(VCOP_WMEM,
                          SIZE_HISTO_8_COPY);

  yHistogram      = (uint32_t *)vcop_malloc(VCOP_IBUFHA,
                          SIZE_HISTO_8_COPY);

  transposeBuff   = (uint32_t *)vcop_malloc(VCOP_IBUFLA,
                          SIZE_HISTOGRAM * 9);

#endif
  outputImageRef  = (uint8_t *)malloc(gConfig_contrast_stretching.imageWidth *
                   gConfig_contrast_stretching.imageHeight);

  yHistogram8CopyRef = (uint32_t *)malloc(SIZE_HISTO_8_COPY);

  yHistogramRef   = (uint32_t *)malloc(SIZE_HISTOGRAM);




  printf("Testing Contrast Stretching kernels:\n");

  for (iter = 0; iter < gConfig_contrast_stretching.numIter; iter++)
  {
    printf("Iteration %d\n", iter);
    fail = 0;

    if(strcmp(gConfig_contrast_stretching.inputImage , "")) {
      fp_in = fopen((const char *)gConfig_contrast_stretching.inputImage, "rb");
      if(fp_in == NULL) {
        printf("Failed to open input file: %s.\n", gConfig_contrast_stretching.inputImage);
        return -1;
      }
      fread(inputImage, 1, gConfig_contrast_stretching.imageWidth *
        gConfig_contrast_stretching.imageHeight, fp_in);

      fclose(fp_in);
    }
    else {
      seed = (gConfig_contrast_stretching.randSeed == 0) ? _tsc_gettime() : gConfig_contrast_stretching.randSeed;
      srand(seed);
      printf("Pattern Generation Seed = %d\n", seed);
      createRndPattern(inputImage,
        gConfig_contrast_stretching.imageWidth,
        gConfig_contrast_stretching.imageHeight,
        gConfig_contrast_stretching.inputPitch);

    }

    memset(yHistogram8Copy, 0 , SIZE_HISTO_8_COPY);
    memset(yHistogram8CopyRef, 0 , SIZE_HISTO_8_COPY);

    profiler_start();
    vcop_histogram_8c_word(inputImage,
            gConfig_contrast_stretching.imageWidth,
            gConfig_contrast_stretching.imageHeight,
            gConfig_contrast_stretching.inputPitch,
            yHistogram8Copy
            );

    profiler_end();


    /* Compare against reference */
    vcop_histogram_8c_word_cn(inputImage,
            gConfig_contrast_stretching.imageWidth,
            gConfig_contrast_stretching.imageHeight,
            gConfig_contrast_stretching.inputPitch,
            yHistogram8CopyRef);

    fail = memcmp(yHistogram8CopyRef, yHistogram8Copy, SIZE_HISTO_8_COPY);
    statusStr = fail?"FAILED":"PASSED";

    printf("vcop_histogram_8c_word kernel %s \n",statusStr);

    profiler_start();
    vcop_histogram_8c_word_sum(yHistogram8Copy, transposeBuff, yHistogram);
    profiler_end();

    vcop_histogram_8c_word_sum_cn(yHistogram8CopyRef, yHistogramRef);

    fail = memcmp(yHistogramRef, yHistogram, SIZE_HISTOGRAM);
        statusStr = fail?"FAILED":"PASSED";

    printf("vcop_histogram_8c_word_sum kernel %s \n",statusStr);

    /* Find Min and Max of histogram */
    for ( i = 1; i < 256; i++)
    {
      yHistogram[i] = yHistogram[i] + yHistogram[i-1];
    }
    totalPixels = yHistogram[255];
    minThrIndexVal = yHistogram[0];
    minVal = 0;
    for(i = 0; i < 256 ; i++)
    {
      minThrIndexVal = yHistogram[i];
      minVal = i;
      if( minThrIndexVal > totalPixels * minPercentileThreshold / 100)
      {
        break;
      }
    }
    maxThrIndexVal = yHistogram[255];
    maxVal = 255;
    for( i = 255 ; i >= 0; i--)
    {
      maxThrIndexVal = yHistogram[i];
      maxVal = i;
      if(maxThrIndexVal<totalPixels * maxPercentileThreshold / 100)
      {
        break;
      }
    }

    minVal = ( minVal > 64  ) ? 64  : minVal;
    maxVal = ( maxVal < 128 ) ? 128 : maxVal;

    if ( (maxVal - minVal) != 0 )
    {
      scaleFactorQ16 = ( 1 << 16) / ( maxVal - minVal);
    }
    else
    {
      scaleFactorQ16 = (1<<16);
    }

    profiler_start();

    vcop_contrast_stretching(
      inputImage,
      outputImage,
      gConfig_contrast_stretching.imageWidth,
      gConfig_contrast_stretching.imageHeight,
      gConfig_contrast_stretching.inputPitch,
      gConfig_contrast_stretching.outputPitch,
      minVal,
      scaleFactorQ16);

    profiler_end();

    vcop_contrast_stretching_cn(
          inputImage,
          outputImageRef,
          gConfig_contrast_stretching.imageWidth,
          gConfig_contrast_stretching.imageHeight,
          gConfig_contrast_stretching.inputPitch,
          gConfig_contrast_stretching.outputPitch,
          minVal,
          scaleFactorQ16);


    fail = memcmp(outputImageRef, outputImage, gConfig_contrast_stretching.imageWidth *
          gConfig_contrast_stretching.imageHeight);

    statusStr = fail?"FAILED":"PASSED";

    printf("vcop_contrast_stretching kernel %s \n",statusStr);

    if(strcmp(gConfig_contrast_stretching.outputImage , ""))
    {
      fp_out = fopen((const char*)gConfig_contrast_stretching.outputImage , "wb");

      if(fp_out == NULL)
      {
        printf("Failed to open output file: %s.\n", gConfig_contrast_stretching.outputImage);
        return -1;
      }

      fwrite(outputImageRef, 1, gConfig_contrast_stretching.imageWidth *
        gConfig_contrast_stretching.imageHeight, fp_out);

      fclose(fp_out);

    }

  }

#if VCOP_HOST_EMULATION
  if (inputImage)
  {
    free(inputImage);
  }

  if (outputImage)
  {
    free(outputImage);
  }

  if (yHistogram8Copy)
  {
    free(yHistogram8Copy);
  }

  if (transposeBuff)
  {
    free(transposeBuff);
  }

  if (yHistogram)
  {
    free(yHistogram);
  }

#else
#endif
  if (outputImageRef)
  {
    free(outputImageRef);
  }

  if (yHistogramRef)
  {
    free(yHistogramRef);
  }

  if (yHistogram8CopyRef)
  {
    free(yHistogram8CopyRef);
  }



  return (status);
}

