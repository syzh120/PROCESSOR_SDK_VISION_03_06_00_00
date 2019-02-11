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


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "vcop.h"
#include "eve_profile.h"
#include "vcop_median_filter_mxn_u8_config.h"


#if VCOP_HOST_EMULATION
    #include "..\inc\vcop_median_filter_mxn_u8_host.h"

    /* Dummy Parameter Register Blocks For Enabling Host Emulation Support */
    unsigned short __pblock_vcop_update_block_histogram_8c[1];
    unsigned short __pblock_vcop_select_kth_smallest_from_hist[1];
#else
    #include "vcop_median_filter_mxn_u8_kernel.h"
#endif

#include "vcop_median_filter_mxn_u8.h"

/* ------------------------------------------------------------------------ */
/*  Include the "C" implementation of median filter function.               */
/* ------------------------------------------------------------------------ */
#include "../src_C/vcop_median_filter_mxn_u8_cn.c"

#define MAX_BLK_STRIDE (64)
#define MAX_BLK_HEIGHT (64)

#pragma DATA_SECTION(inData, "Adata");
static unsigned char inData[MAX_BLK_HEIGHT*MAX_BLK_STRIDE] = {0};

#pragma DATA_ALIGN(wgt, 32);
#pragma DATA_SECTION(wgt, "Bdata");
static char wgt[16] = {0};

#pragma DATA_ALIGN(hist, 32);
#pragma DATA_SECTION(hist, "Cdata");
static short hist[256*8] = {0};

#pragma DATA_ALIGN(coarseHist, 32);
#pragma DATA_SECTION(coarseHist, "Adata");
static short coarseHist[16] = {0};

#pragma DATA_ALIGN(scratch_histo, 32);
#pragma DATA_SECTION(scratch_histo, "Bdata");
static short scratch_histo[4*36*8] = {0};

#pragma DATA_ALIGN(blk_hist, 32);
#pragma DATA_SECTION(blk_hist, "Cdata");
static short blk_hist[36*16] = {0};

#pragma DATA_SECTION(med, "Adata");
static unsigned char med[1] = {0};

#pragma DATA_SECTION(pBlocks, "Cdata");
//static unsigned short pBlocks[156] = {0};
static unsigned short pBlocks[1024] = {0};

#pragma DATA_SECTION(medianContext, "EOutdata");
static median_kernel_context medianContext = {NULL, NULL};

#pragma DATA_SECTION(med_ref, "EOutdata");
static unsigned char med_ref[1] = {0};

static void CreateRandPattern8(unsigned char *p, unsigned short w, unsigned short h, unsigned short stride)
{
    int i, j;

    // Sample input block pattern
#ifdef __DEBUG
    printf("Input Block:\n");
#endif
    for(i = 0; i < h; i++) {
        for(j = 0; j < w; j++) {
            p[i*stride+j] = rand()&0xFF; // (i*w+j)&0xFF;
#ifdef __DEBUG
            printf("%4d, ", inData[i*stride+j]);
#endif
        }
#ifdef __DEBUG
        printf("\n");
#endif
    }
}


void fillDefaultConfig(sMedianFilter_mxn_u8_Config* params)
{
  strcpy(params->inImg, "");
  strcpy(params->outImg, "");
  params->blkWidth  = 16;
  params->blkHeight = 16;
  params->blkPitch  = 16;
  params->kernelWidth  = 9;
  params->kernelHeight = 9;

  params->stepSizeHorz = 3;
  params->stepSizeVert = 3;

  params->randSeed    = 0;
  params->numIter     = 1;
}


int32_t main(int32_t argc, char *argv[])
{
    int iter, fail = 0, status = 0;
    uint32_t seed;
    FILE *fp_in = NULL, *fp_out = NULL;
    char configFile[FILE_NAME_SIZE];
    char fileName[FILE_NAME_SIZE];

    if (argc > 1)
    {
      strcpy(configFile, argv[1]) ;
    }
    else
    {
      strcpy(configFile,"../testvecs/config/median_filter_mxn_u8.cfg");
    }

    fillDefaultConfig(&gConfig_median_filter_mxn_u8);
    fail = readparamfile(configFile, &gsTokenMap_median_filter_mxn_u8[0]) ;
    if(fail == -1)
    {
      printf("Parser Failed. Running default config.\n");
    }

    profiler_init();

    /* Test median filtering using 8 threaded histogram sort */
    printf("Testing Median MxN Kernel:\n");

    for(iter = 0; iter < gConfig_median_filter_mxn_u8.numIter; iter++) {

        printf("Iteration %d:\n", iter);
        fail = 0;

        if(strcmp(gConfig_median_filter_mxn_u8.inImg, "")) {
          sprintf(fileName, "../testvecs/input/%s", gConfig_median_filter_mxn_u8.inImg);
          fp_in = fopen((const char *)fileName, "r");
          if(fp_in == NULL) {
            printf("Failed to open input file: %s.\n", gConfig_median_filter_mxn_u8.inImg);
            return -1;
          }

          fread(inData, gConfig_median_filter_mxn_u8.blkPitch*gConfig_median_filter_mxn_u8.blkHeight, 1, fp_in);
          fclose(fp_in);
        }
        else {
          seed = (gConfig_median_filter_mxn_u8.randSeed == 0) ? _tsc_gettime() : gConfig_median_filter_mxn_u8.randSeed;
          srand(seed);
          printf("Pattern Generation Seed = %d\n", seed);
          CreateRandPattern8(inData, gConfig_median_filter_mxn_u8.blkWidth,
                             gConfig_median_filter_mxn_u8.blkHeight,
                             gConfig_median_filter_mxn_u8.blkPitch);
        }

        //Initialize the kernel
        VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                       IBUFHA_SYST, IBUFLA_SYST);

        vcop_large_kernel_median_wrapper_init(inData, med, gConfig_median_filter_mxn_u8.blkPitch,
          gConfig_median_filter_mxn_u8.blkWidth, gConfig_median_filter_mxn_u8.blkHeight,
          gConfig_median_filter_mxn_u8.kernelWidth, gConfig_median_filter_mxn_u8.kernelHeight,
          gConfig_median_filter_mxn_u8.stepSizeHorz, gConfig_median_filter_mxn_u8.stepSizeVert,
          hist, wgt, scratch_histo, blk_hist, coarseHist, pBlocks, &medianContext);

        profiler_start();

        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                       IBUFHA_VCOP, IBUFLA_VCOP);

        vcop_large_kernel_median_wrapper_vloops(&medianContext);
        _vcop_vloop_done();

        VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                       IBUFHA_SYST, IBUFLA_SYST);

        profiler_end();

        // Validate the kernel output against reference output
        vcop_median_filter_mxn_u8_cn(inData, med_ref, gConfig_median_filter_mxn_u8.blkPitch,
          gConfig_median_filter_mxn_u8.kernelWidth, gConfig_median_filter_mxn_u8.kernelHeight,
          gConfig_median_filter_mxn_u8.kernelWidth, gConfig_median_filter_mxn_u8.kernelHeight,
          gConfig_median_filter_mxn_u8.stepSizeHorz, gConfig_median_filter_mxn_u8.stepSizeVert);

#ifdef __DEBUG
        printf("Median output = %d\n", med[0]);
        printf("Expected median = %d\n", med_ref[0]);
#endif

        sprintf(fileName, "../testvecs/output/%s", gConfig_median_filter_mxn_u8.outImg);
        fp_out = fopen((const char*)fileName, "w");
        if(fp_out != NULL) {
          fwrite(med, 1, 1, fp_out);
          fclose(fp_out);
        }

        // Validate the kernel output against reference output
        fail = (med[0] != med_ref[0]);
        printf(fail ? "FAIL\n\n" : "PASS\n\n");
        status |= fail;
    }

    profiler_deinit();

    printf(status ? "Median mxn: FAIL\n\n" : "Median mxn: PASS\n\n");
    return (status);
}

