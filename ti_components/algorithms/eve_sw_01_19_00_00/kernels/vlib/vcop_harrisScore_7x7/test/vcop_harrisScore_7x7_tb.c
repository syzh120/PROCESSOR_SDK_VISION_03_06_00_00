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
#include "vcop_harrisScore_7x7_config.h"

/* ------------------------------------------------------------------------ */
/*  Include prototypes for "C" implementation of Harris Score 7x7  */
/*  function.                                                               */
/* ------------------------------------------------------------------------ */
#include "vcop_harrisScore_7x7_cn.h"

#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_harrisScore_7x7_kernel.k"
#else
#include "../inc/vcop_harrisScore_7x7_kernel.h"
#endif

//#define __DEBUG

#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))
#define ALIGN_2SIMD(a)   (((a) + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))

#define NUM_ITER         (1)
#define MAX_WIDTH         (38)
#define MAX_HEIGHT        (38)

#define ALIGNED_WIDTH ALIGN_SIMD(MAX_WIDTH)

uint8_t IMAGE_BLOCKS[MAX_WIDTH*MAX_HEIGHT];

#pragma DATA_SECTION(OUT_SCORE, "Adata");
short OUT_SCORE[MAX_WIDTH*MAX_HEIGHT] = {0};

short NATC_SCORE[MAX_WIDTH*MAX_HEIGHT] = {0};
short GRADMAG[MAX_WIDTH*MAX_HEIGHT];

#pragma DATA_SECTION(GRADX, "Cdata");
short GRADX[(MAX_WIDTH*MAX_HEIGHT)] = {0};

#pragma DATA_SECTION(GRADY, "Bdata");
short GRADY[(MAX_WIDTH*MAX_HEIGHT)] = {0};

#pragma DATA_SECTION(XX, "Adata");
static int XX[ALIGNED_WIDTH * (MAX_HEIGHT+ 1)];
#pragma DATA_SECTION(YY, "Cdata");
static int YY[ALIGNED_WIDTH * (MAX_HEIGHT+ 1)];
#pragma DATA_SECTION(XY, "Bdata");
static int XY[ALIGNED_WIDTH * (MAX_HEIGHT+ 1)];

#pragma DATA_SECTION(detL, "Cdata");
static unsigned int detL[MAX_WIDTH * (MAX_HEIGHT)];
#pragma DATA_SECTION(detH, "Bdata");
static int detH[MAX_WIDTH * (MAX_HEIGHT)];


void fillDefaultConfig(sHarris_score_7x7_Config * params)
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

int vcop_harrisScore_7x7
(
    short *  gradX,
    short *  gradY,
    int width,
    int height,
    short *  outm,
    unsigned short k,
    int * XX,
    int * YY,
    int * XY,
    unsigned int * detL,
    int * detH
)
{

   char *pIn1 = (char *) (XX);
   char *pIn2 = (char *) (YY);
   char *pIn3 = (char *) (XY);

    vcop_harrisScore_7x7_1
    (
    gradX,
    gradY,
    width,
    height,
    width,
    width,
    XX,
    YY,
    XY
    );


    vcop_harrisScore_7x7_2
    (
    width-6,
    height-6,
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

void createRandPattern(uint8_t *img_blocks, uint16_t blk_size,
                   uint16_t inter_blk_offset,
                   uint16_t nblocks, uint16_t upper_bound)
{
    int32_t i, j;

    for(i = 0; i < nblocks; i++) {
        for(j = 0; j < inter_blk_offset; j++) {
            img_blocks[i*inter_blk_offset + j] = (j < blk_size) ? (rand() & 0xFF) % (upper_bound + 1) : 0;
        }
    }
}

///////////////////////////////////////
// Makes a 32x32 random
///////////////////////////////////////
static void CreatePattern(unsigned char *p)
{
    int i;

    for (i = 0; i < (MAX_WIDTH)*(MAX_HEIGHT); i++)
    {
        p[i] =(rand() & 0xFF);

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

int32_t test_harrisScore_7x7()
{
    int32_t i,j, iter, status = 0;
    uint32_t seed;
    FILE *fp_in = NULL, *fp_out = NULL;

    profiler_init();

    memset(OUT_SCORE, 0, sizeof(OUT_SCORE));

    for (iter = 0; iter < gConfig_harris_score_7x7.numIter; iter++)
    {
        printf("Iteration %d\n", iter);

        if(strcmp(gConfig_harris_score_7x7.inputBlock, "")) {
            printf("File Test\n");
            fp_in = fopen((const char *)gConfig_harris_score_7x7.inputBlock, "rb");
            if(fp_in == NULL) {
                printf("Failed to open input file: %s.\n", gConfig_harris_score_7x7.inputBlock);
                return -1;
            }
            fread(IMAGE_BLOCKS, gConfig_harris_score_7x7.width * gConfig_harris_score_7x7.height, 1, fp_in);
            fclose(fp_in);
        }
        else {
            /* Generate input data */
            seed = (gConfig_harris_score_7x7.randSeed == 0) ? _tsc_gettime() : gConfig_harris_score_7x7.randSeed;
            srand(seed);
            printf("Random pattern test: Seed = %d\n", seed);
            CreatePattern(IMAGE_BLOCKS);
        }

        vcop_vec_gradients_xy_and_magnitude_cn(IMAGE_BLOCKS, GRADX,
                   GRADY, GRADMAG,gConfig_harris_score_7x7.width,
                   gConfig_harris_score_7x7.height);
        profiler_start();

        vcop_harrisScore_7x7(GRADX, GRADY, gConfig_harris_score_7x7.width,
            gConfig_harris_score_7x7.height, OUT_SCORE,
            gConfig_harris_score_7x7.sensitivityParam, XX,YY,XY, detL, detH);

        profiler_end();

        /*---------------------------------------------------------------------*/
        /*  Function call to the Natural-C API to be tested                    */
        /*  Compute Harris scores for all blocks in IMAGE_BLOCKS               */
        /*---------------------------------------------------------------------*/
        vcop_harrisScore_7x7_cn(GRADX, GRADY, gConfig_harris_score_7x7.width,
            gConfig_harris_score_7x7.height, NATC_SCORE,
            gConfig_harris_score_7x7.sensitivityParam);

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/
    status = 0;
    for(j =0; j <  gConfig_harris_score_7x7.height - 6; j++)
    {
        for(i =0; i <  gConfig_harris_score_7x7.width - 6; i++)
        {
            if(NATC_SCORE[(j)*  gConfig_harris_score_7x7.width + (i)] !=
                  OUT_SCORE[j*  gConfig_harris_score_7x7.width + i])
            {
                status = 1;
                break;
            }
        }
    }

        if ( status != 0 )
        {
          printf("NATC and Kernel C output not matching at iteration %d \n", iter);
          break;
        }

        if(strcmp(gConfig_harris_score_7x7.outputScore , "")) {
            fp_out = fopen((const char*)gConfig_harris_score_7x7.outputScore, "wb");
            if(fp_out != NULL) {
                fwrite(OUT_SCORE, 4 * gConfig_harris_score_7x7.width *
                  gConfig_harris_score_7x7.height, 1, fp_out);
                fclose(fp_out);
            }
            else {
                printf("Failed to open Output file.\n");
            }
        }
    }



    if(status != 0) {
        printf("Harris score mismatches:\n");
    }

    profiler_deinit();

    printf(status ? "test_harrisScore_7x7: FAIL\n" : "test_harrisScore_7x7: PASS\n");

    return (status);
}


int32_t main(int32_t argc, char *argv[])
{
    int32_t status = 0;
    char configFile[FILE_NAME_SIZE];

    if (argc > 1)
    {
        strcpy(configFile, argv[1]) ;
    }
    else
    {
        strcpy(configFile,"../testvecs/config/vcop_harrisScore_7x7.cfg");
    }

    fillDefaultConfig(&gConfig_harris_score_7x7);
    status = readparamfile(configFile, &gsTokenMap_harris_score_7x7[0]) ;
    if(status == -1)
    {
        printf("Parser Failed. Using default values.\n");
    }

    printf ("\nHarris Score 7x7 Test Bench:\n");
    status = test_harrisScore_7x7();

    return status;
}
