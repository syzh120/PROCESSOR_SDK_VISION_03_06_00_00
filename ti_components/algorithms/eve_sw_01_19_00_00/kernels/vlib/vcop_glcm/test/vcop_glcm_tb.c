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
#include "vcop_glcm_config.h"

/* ------------------------------------------------------------------------ */
/*  Include prototype for the "C" implementation of GLCM function           */
/* ------------------------------------------------------------------------ */
#include "vcop_glcm_cn.h"

#if VCOP_HOST_EMULATION
  #include "../src_kernelC/vcop_glcm_kernel.k" // kernel source
#else
  #include "vcop_glcm_kernel.h"
#endif

//#define __DEBUG

#define MAX_IMG_WIDTH  (90)
#define MAX_IMG_HEIGHT (90)
#define MAX_NUM_LEVELS (110)

#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define MIN(A, B) (((A) < (B)) ? (A) : (B))

#pragma DATA_SECTION(IN, "Bdata");
uint8_t IN[MAX_IMG_HEIGHT*MAX_IMG_WIDTH] = {0};

#pragma DATA_SECTION(SCRATCH_IDX, "Adata");
uint16_t SCRATCH_IDX[MAX_IMG_HEIGHT*((MAX_IMG_WIDTH + 1)/2)*2 + 15] = {0};

#pragma DATA_SECTION(SCRATCH_OFFSET, "Bdata");
uint16_t SCRATCH_OFFSET[8] = {0};

#pragma DATA_SECTION(HIST_WGT, "Cdata");
uint8_t HIST_WGT[8];

#pragma DATA_ALIGN(OUT_GLCM, 32);
#pragma DATA_SECTION(OUT_GLCM, "Cdata");
uint16_t OUT_GLCM[MAX_NUM_LEVELS*MAX_NUM_LEVELS] = {0};

#pragma DATA_SECTION(REF_GLCM, "Eoutdata");
uint16_t REF_GLCM[MAX_NUM_LEVELS*MAX_NUM_LEVELS] = {0};


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


void print_2d_buf_u16(uint16_t   *buf,
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


void createRndPattern(uint8_t *img, uint16_t height, uint32_t width,
                      uint32_t pitch, uint8_t max_val)
{
  int32_t i, j;

  for(i = 0; i < height; i++) {
    for(j = 0; j < pitch; j++) {
      img[i*pitch + j] = rand() % (max_val + 1);
    }
  }
}


void fillDefaultConfig(sGlcm_Config * params)
{
  strcpy(params->inImg, "");
  strcpy(params->outGLCM, "");
  params->imageWidth  = 64;
  params->imageHeight = 64;
  params->imagePitch  = 64;
  params->numLevels   = 10;
  params->numOffsets  = 4;

  params->rowOffsets[0] = 0;
  params->colOffsets[0] = 1;

  params->rowOffsets[1] = -1;
  params->colOffsets[1] = 1;

  params->rowOffsets[2] = -1;
  params->colOffsets[2] = 0;

  params->rowOffsets[3] = -1;
  params->colOffsets[3] = -1;

  params->randSeed    = 0;
  params->numIter     = 1;
}

int32_t main(int32_t argc, char *argv[])
{
  int32_t iter, fail, status = 0;
  uint32_t n, rem;
  uint8_t rowStart[MAX_NUM_DIRECTIONS], colStart[MAX_NUM_DIRECTIONS];
  int8_t maxColOffset, minColOffset, maxRowOffset, minRowOffset;
  uint8_t numRows, numCols;
  uint16_t *scratch_idx_arr[8], *glcm_8c_arr[8], *out_glcm_arr[8], *scratch_arr[8];
  uint16_t scatter_offset;
  uint32_t seed;
  FILE *fp_in = NULL, *fp_out = NULL;
  char configFile[FILE_NAME_SIZE];

  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,"../testvecs/config/glcm.cfg");
  }

  fillDefaultConfig(&gConfig_glcm);
  status = readparamfile(configFile, &gsTokenMap_glcm[0]) ;
  if(status == -1)
  {
    printf("Parser Failed");
    return -1;
  }

  if(gConfig_glcm.numOffsets > 8) {
    printf("Only upto 8 offsets supported by kernel.\n");
    return -1 ;
  }

  profiler_init();

  printf("Testing Gray-level co-occurrence Matrix:\n");

  if(gConfig_glcm.numLevels > 110) {
      printf("Unsuported number of levels.\n");
      return -1;
  }

  for (iter = 0; iter < gConfig_glcm.numIter; iter++)
  {
    printf("Iteration %d\n", iter);
    fail = 0;

    if(strcmp(gConfig_glcm.inImg, "")) {
      fp_in = fopen((const char *)gConfig_glcm.inImg, "r");
      if(fp_in == NULL) {
        printf("Failed to open input file: %s.\n", gConfig_glcm.inImg);
        return -1;
      }

      fread(IN, gConfig_glcm.imageHeight*gConfig_glcm.imagePitch, 1, fp_in);
      fclose(fp_in);
    }
    else {
      seed = (gConfig_glcm.randSeed == 0) ? _tsc_gettime() : gConfig_glcm.randSeed;
      srand(seed);
      printf("Pattern Generation Seed = %d\n", seed);
      createRndPattern(IN, gConfig_glcm.imageHeight,
                       gConfig_glcm.imageWidth,
                       gConfig_glcm.imagePitch,
                       gConfig_glcm.numLevels - 1);
    }

    print_2d_buf_u8(IN, gConfig_glcm.imageHeight, gConfig_glcm.imageWidth,
                    gConfig_glcm.imagePitch, "Input image");

    maxColOffset = 0;
    minColOffset = 0;
    maxRowOffset = 0;
    minRowOffset = 0;

    printf("\n");
    for(n = 0; n < gConfig_glcm.numOffsets; n++) {

      rowStart[n] = (gConfig_glcm.rowOffsets[n] > 0) ? 0 : -gConfig_glcm.rowOffsets[n];
      colStart[n] = (gConfig_glcm.colOffsets[n] > 0) ? 0 : -gConfig_glcm.colOffsets[n];

      maxColOffset = MAX(maxColOffset, gConfig_glcm.colOffsets[n]);
      minColOffset = MIN(minColOffset, gConfig_glcm.colOffsets[n]);
      maxRowOffset = MAX(maxRowOffset, gConfig_glcm.rowOffsets[n]);
      minRowOffset = MIN(minRowOffset, gConfig_glcm.rowOffsets[n]);

      printf("%d: RowOffset = %d, ColOffset = %d, rowStart = %d, colStart = %d\n", n,
          gConfig_glcm.rowOffsets[n], gConfig_glcm.colOffsets[n], rowStart[n], colStart[n]);
    }

    numRows = gConfig_glcm.imageHeight - (maxRowOffset - minRowOffset);
    numCols = gConfig_glcm.imageWidth - (maxColOffset - minColOffset);

    printf("numRows = %d, numCols = %d\n\n", numRows, numCols);

    if(gConfig_glcm.numLevels > 39) {
      printf("One Channel Histogram\n");

      for(n = 0; n < gConfig_glcm.numOffsets; n++) {
          scratch_idx_arr[n] = SCRATCH_IDX + n*numRows*4*((numCols+1)/2);
          out_glcm_arr[n] = OUT_GLCM + n*gConfig_glcm.numLevels*gConfig_glcm.numLevels;
      }

      profiler_start();
      vcop_initialize_glcm(OUT_GLCM, gConfig_glcm.numLevels, gConfig_glcm.numOffsets);
      profiler_end();

      profiler_start();
      vcop_glcm_compute_1c(IN, scratch_idx_arr, out_glcm_arr,
          gConfig_glcm.numLevels, gConfig_glcm.numOffsets, rowStart, colStart,
          gConfig_glcm.rowOffsets, gConfig_glcm.colOffsets, numRows, numCols,
          gConfig_glcm.imageWidth, gConfig_glcm.imageHeight, gConfig_glcm.imagePitch);
      profiler_end();
    }
    else {
      printf("Eight Channel Histogram\n");

      for(n = 0; n < gConfig_glcm.numOffsets; n++) {
          scratch_idx_arr[n] = SCRATCH_IDX + n*numRows*4*((numCols+1)/2);
          glcm_8c_arr[n] = OUT_GLCM + n*8*gConfig_glcm.numLevels*gConfig_glcm.numLevels;
      }

      rem = numCols - (8*((numCols-1)/8));
      for(n = 0; n < 8; n++) {
          HIST_WGT[n] = (n < rem) ? 1 : 0;
      }

      profiler_start();
      vcop_initialize_glcm(OUT_GLCM, gConfig_glcm.numLevels, 8*gConfig_glcm.numOffsets);
      profiler_end();

      profiler_start();
      vcop_glcm_compute_8c(IN, scratch_idx_arr, glcm_8c_arr, HIST_WGT,
          gConfig_glcm.numLevels, gConfig_glcm.numOffsets, rowStart,
          colStart, gConfig_glcm.rowOffsets, gConfig_glcm.colOffsets,
          numRows, numCols, gConfig_glcm.imageWidth,
          gConfig_glcm.imageHeight, gConfig_glcm.imagePitch);
      profiler_end();

      scatter_offset = 4*(2*(((gConfig_glcm.numLevels*gConfig_glcm.numLevels + 1)/2 + 1)/4) + 1);
      printf("Scatter Offset = %d\n", scatter_offset);
      for(n = 0; n < 8; n++) {
          SCRATCH_OFFSET[n] = n*scatter_offset;
      }
      for(n = 0; n < gConfig_glcm.numOffsets; n++) {
          out_glcm_arr[n] = OUT_GLCM + n*gConfig_glcm.numLevels*gConfig_glcm.numLevels;
          scratch_arr[n] = SCRATCH_IDX + n*scatter_offset*8;
      }

      profiler_start();
      vcop_accumulate_8c_glcm(glcm_8c_arr, out_glcm_arr, scratch_arr, SCRATCH_OFFSET, gConfig_glcm.numLevels,
                              gConfig_glcm.numOffsets, scatter_offset);
      profiler_end();
    }

    /*---------------------------------------------------------------------*/
    /* Compare the results of output arrays with expected output arrays.   */
    /*---------------------------------------------------------------------*/
    vcop_glcm_cn(IN, REF_GLCM, gConfig_glcm.imageWidth, gConfig_glcm.imageHeight,
                 gConfig_glcm.imagePitch, gConfig_glcm.numLevels,
                 gConfig_glcm.numOffsets, gConfig_glcm.rowOffsets,
                 gConfig_glcm.colOffsets);

    print_2d_buf_u16(OUT_GLCM, gConfig_glcm.numOffsets*gConfig_glcm.numLevels,
                     gConfig_glcm.numLevels, gConfig_glcm.numLevels, "GLCM output");

    /* Compare against reference */
    fail = memcmp(OUT_GLCM, REF_GLCM, gConfig_glcm.numOffsets*2*gConfig_glcm.numLevels*gConfig_glcm.numLevels);

    fp_out = fopen((const char*)gConfig_glcm.outGLCM, "w");
    if(fp_out != NULL) {
        fwrite(OUT_GLCM, gConfig_glcm.numOffsets*gConfig_glcm.numLevels*gConfig_glcm.numLevels, 2, fp_out);
        fclose(fp_out);
    }

    printf(fail ? "FAIL\n":"PASS\n");
    status |= fail;
  }

  printf(status ? "\nFAIL\n" : "\nPASS\n");

  return (status);
}
