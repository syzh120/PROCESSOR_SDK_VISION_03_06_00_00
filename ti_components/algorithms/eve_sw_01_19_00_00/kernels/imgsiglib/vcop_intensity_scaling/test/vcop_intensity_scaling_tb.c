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
#include "vcop_intensity_scaling.h"
#include "vcop_intensity_scaling_config.h"

/* ------------------------------------------------------------------------ */
/*  Include prototype for the "C" reference of Intensity Scaling function   */
/* ------------------------------------------------------------------------ */
#include "vcop_intensity_scaling_cn.h"

#if VCOP_HOST_EMULATION
  #include "../src_kernelC/vcop_intensity_scaling_kernel.k" // kernel source
#else
  #include "vcop_intensity_scaling_kernel.h"
#endif

//#define __DEBUG

#define IMG_WIDTH  (128)
#define IMG_PITCH  (128)
#define IMG_HEIGHT (128)
#define NUM_LEVELS (110)

#pragma DATA_SECTION(IN, "Adata");
uint8_t IN[IMG_HEIGHT*IMG_PITCH] =
                     {0,  1,  2,  3,  4,  5,  6,  7,
                      8,  9, 10, 11, 12, 13, 14, 15};

#pragma DATA_SECTION(OUT_SI, "Bdata");
uint8_t OUT_SI[IMG_HEIGHT*IMG_WIDTH] = {0};

#pragma DATA_SECTION(SCALING_LUT, "Cdata");
uint8_t SCALING_LUT[8*256] = {0};

#pragma DATA_SECTION(REF_SI, "Eoutdata");
uint8_t REF_SI[IMG_HEIGHT*IMG_WIDTH] = {0};

void createRndPattern(uint8_t *img, uint16_t height, uint32_t width,
                      uint32_t pitch, uint16_t max)
{
  int32_t i, j;

  for(i = 0; i < height; i++) {
    for(j = 0; j < width; j++) {
      img[i*pitch + j] = rand()%(max + 1);
    }
  }
}

void fillDefaultConfig(sIntensityScaling_Config * params)
{
  strcpy(params->inImg, "");
  strcpy(params->outImg, "");
  params->imageWidth  = 8;
  params->imageHeight = 2;
  params->imagePitch  = 8;
  params->loPixelVal  = 4;
  params->hiPixelVal  = 11;
  params->numLevels   = 5;
  params->randSeed    = 0;
  params->numIter     = 1;
}


void print_2d_buf_u8(uint8_t    *buf,
                     uint16_t    buf_height,
                     uint16_t    buf_width,
                     uint16_t    buf_pitch,
                     const char *str)
{
#ifdef __DEBUG
    int32_t i,j;

    printf("\n%s:\n", str);
    for(i = 0; i < buf_height; i++) {
        for(j = 0; j < buf_width; j++) {
            printf("%d, ", buf[i*buf_pitch + j]);
        }
        printf("\n");
    }
#endif
}


int32_t main(int32_t argc, char *argv[])
{
  int32_t iter, fail, status = 0;
  uint32_t i, j;
  uint32_t seed;
  FILE *fp_in = NULL, *fp_out = NULL;
  char configFile[FILE_NAME_SIZE];

  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
#if VCOP_HOST_EMULATION
    strcpy(configFile,"testvecs/config/intensity_scaling.cfg");
#else
    strcpy(configFile,"../testvecs/config/intensity_scaling.cfg");
#endif
  }

  fillDefaultConfig(&gConfig_intensity_scaling);
  status = readparamfile(configFile, &gsTokenMap_intensity_scaling[0]) ;
  if(status == -1)
  {
    printf("Parser Failed");
    return -1 ;
  }

  profiler_init();

  printf("Testing Intensity Scaling of an 8-bit Gray-scale image:\n");

#if !(VCOP_HOST_EMULATION)
  VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                      IBUFHA_SYST, IBUFLA_SYST);

  vcop_intensity_scaling_init(IN, SCALING_LUT, OUT_SI,
        gConfig_intensity_scaling.imageWidth,
        gConfig_intensity_scaling.imageHeight,
        gConfig_intensity_scaling.imagePitch,
        __pblock_vcop_intensity_scaling);
#endif

  for (iter = 0; iter < gConfig_intensity_scaling.numIter; iter++)
  {
    printf("Iteration %d\n", iter);
    fail = 0;

    if(strcmp(gConfig_intensity_scaling.inImg, "")) {
      fp_in = fopen((const char *)gConfig_intensity_scaling.inImg, "r");
      if(fp_in == NULL) {
        printf("Failed to open input file: %s.\n", gConfig_intensity_scaling.inImg);
        return -1;
      }

      fread(IN, gConfig_intensity_scaling.imageWidth*gConfig_intensity_scaling.imageHeight, 1, fp_in);
      fclose(fp_in);
    }
    else {
      seed = (gConfig_intensity_scaling.randSeed == 0) ? _tsc_gettime() : gConfig_intensity_scaling.randSeed;
      srand(seed);
      printf("Pattern Generation Seed = %d\n", seed);
      createRndPattern(IN, gConfig_intensity_scaling.imageHeight,
                       gConfig_intensity_scaling.imageWidth,
                       gConfig_intensity_scaling.imagePitch,
                       gConfig_intensity_scaling.hiPixelVal);
    }

    print_2d_buf_u8(IN, gConfig_intensity_scaling.imageHeight,
        gConfig_intensity_scaling.imageWidth,
        gConfig_intensity_scaling.imagePitch, "Input image");

    /* Prepare LUT for intensity scaling */
    prepare_lut(gConfig_intensity_scaling.loPixelVal,
        gConfig_intensity_scaling.hiPixelVal,
        gConfig_intensity_scaling.numLevels,
        8, SCALING_LUT);

    profiler_start();

  #if VCOP_HOST_EMULATION
    vcop_intensity_scaling(IN, SCALING_LUT, OUT_SI,
        gConfig_intensity_scaling.imageWidth,
        gConfig_intensity_scaling.imageHeight,
        gConfig_intensity_scaling.imagePitch);
  #else
    VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                    IBUFHA_VCOP, IBUFLA_VCOP);

    /*---------------------------------------------------------------------*/
    /*  Function call to the VCOP-C API to be tested                       */
    /*---------------------------------------------------------------------*/
    vcop_intensity_scaling_vloops(__pblock_vcop_intensity_scaling);
    _vcop_vloop_done();

    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                        IBUFHA_SYST, IBUFLA_SYST);
  #endif

    profiler_end();

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/
    prepare_lut(gConfig_intensity_scaling.loPixelVal,
        gConfig_intensity_scaling.hiPixelVal,
        gConfig_intensity_scaling.numLevels,
        1, SCALING_LUT);
    vcop_intensity_scaling_cn(IN, SCALING_LUT, REF_SI,
        gConfig_intensity_scaling.imageWidth,
        gConfig_intensity_scaling.imageHeight,
        gConfig_intensity_scaling.imagePitch);

    print_2d_buf_u8(OUT_SI, gConfig_intensity_scaling.imageHeight,
        gConfig_intensity_scaling.imageWidth,
        gConfig_intensity_scaling.imagePitch, "Scaled output");
    print_2d_buf_u8(REF_SI, gConfig_intensity_scaling.imageHeight,
        gConfig_intensity_scaling.imageWidth,
        gConfig_intensity_scaling.imagePitch, "Reference output");

    /* Compare against reference */
    fail = memcmp(OUT_SI, REF_SI, sizeof(OUT_SI));
    if(fail != 0) {
      for(i = 0; i < gConfig_intensity_scaling.imageHeight; i++) {
        for(j = 0; j < gConfig_intensity_scaling.imageWidth; j++) {
          if(OUT_SI[i] != REF_SI[i]) {
            printf("\nOutput mismatch at (%d, %d), Output = %d, Expected = %d\n",
                   i, j, OUT_SI[i*gConfig_intensity_scaling.imageWidth + j],
                   REF_SI[i*gConfig_intensity_scaling.imageWidth + j]);
          }
        }
      }
    }

    fp_out = fopen((const char*)gConfig_intensity_scaling.outImg, "w");
    if(fp_out != NULL) {
        fwrite(OUT_SI, gConfig_intensity_scaling.imageHeight*gConfig_intensity_scaling.imageWidth, 1, fp_out);
        fclose(fp_out);
    }

    printf(fail ? "FAIL\n":"PASS\n");
    status |= fail;
  }

  profiler_deinit();

  printf(status ? "Intensity Scaling: FAIL\n":"Intensity Scaling: PASS\n");

  return (status);
}
