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
#include "vcop_multipoint_harrisScore_u16_config.h"

/* ------------------------------------------------------------------------ */
/*  Include prototypes for "C" implementation of Multi-point Harris Score   */
/*  function.                                                               */
/* ------------------------------------------------------------------------ */
#include "vcop_multipoint_harrisScore_u16_cn.h"

#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_multipoint_harrisScore_u16_kernel.k"
#else
#include "../inc/vcop_multipoint_harrisScore_u16_kernel.h"
#endif

//#define __DEBUG

#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))
#define ALIGN_2SIMD(a)   (((a) + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))

#define NUM_ITER         (1)
#define WIN_WIDTH        (7)
#define WIN_HEIGHT       (7)
#define NUM_POINTS       (128)

#define IN_BLK_SIZE      ((WIN_WIDTH+2)*(WIN_HEIGHT+2))

#pragma DATA_SECTION(IMAGE_BLOCKS, "Adata");
uint8_t IMAGE_BLOCKS[NUM_POINTS*IN_BLK_SIZE] = {
     38,  39, 246, 133, 151,  21, 173,  29, 210,
    148, 221, 196, 118,  25,  57,  49, 241, 173,
    181,  88, 240, 147, 151,  50,  25,  43, 209,
    192, 253,  22, 142,  78,  72, 155,  11, 245,
     59,  73, 168,  99,  93, 222,  63, 223, 109,
    104, 180, 135, 154, 170, 205, 220, 247, 193,
     68, 129,  41,   8,  27,  64,  98,  56,  48,
     78, 148, 212,  17, 208, 222, 196,  17, 157,
     75,  63, 156,  70, 187, 239, 199,  84,  33,
     80,  43, 208, 239,  90, 244,   9, 207,  95,
     53, 145, 148,  54, 127, 137, 112, 153, 177,
     30, 103, 204,  17,  84,   3, 127, 156,   3,
     74, 246, 155,  30, 237, 103, 119,  59, 194,
    164, 206,  80, 116, 249, 198, 187, 122,  88,
    162, 134,  69, 179, 147, 232, 190, 170, 208,
     15, 239, 102, 232,  28,   0, 197,  87, 112,
    102, 183,  88,  38,  87, 232, 251, 224, 129,
    159, 119, 199, 251, 230, 193, 205, 124, 235,
     94,  54, 203, 166, 117,  86, 118, 188,  40,
    156, 199, 163,  36, 207, 244,   7, 119, 152,
    150, 109, 163,  65,  92,  23, 240, 188,   1,
     39,   6, 231, 123,   7, 186,  14, 118,   7,
     41, 177,   0,  72,   3, 136, 134, 218,  42,
    197, 255,  33, 124, 153, 103, 125, 236, 249,
    111,  41, 216, 162, 115, 100, 151,  91, 172,
    207,  81, 122, 167,  23,  19, 169, 245, 211,
     34, 234,  37, 176, 144, 217, 239, 203,  14,
     49, 178,  94,   1, 146,  33, 159, 216, 130,
     56, 229, 156, 177, 118,  13, 200, 129,  70,
     28,  92, 197, 190,  37,  45, 201, 139, 110,
    127, 148,  44, 206, 213, 105,  95,  89,   8,
    148, 217,  64, 151,  99,  58, 242,  62, 114,
     64, 135, 202,  43,  59,  95,  43, 142, 193,
      6, 203,  46, 162,  91,  30, 124,  30, 242,
    123,  72,  86, 182,  42, 133,   1, 211, 190,
     77,  96, 211, 164,  37, 116,   6, 253, 129,
    110,  40, 169, 139, 103,  62, 164,  32,  81,
    193, 150,  27,  46, 254, 165, 215, 128, 189,
    142, 239,   0,  33, 244,  72, 146, 207, 248,
     82, 121,  82,   9, 138, 199, 191, 253,  68,
     24, 148,  97, 167, 128, 230,  14, 249, 194,
    188, 253,  29, 195, 182,  93,  89,  62, 242,
    226,  93, 184,  47,  95, 129, 183,  51, 151,
     79,  47, 107,  81,  65,  61, 210, 170, 203,
     23,  19, 175, 156,  68, 242,  43,  34,   8,
    232, 190,  76,  35,  13,  47, 147, 187,  60,
      3,  59, 150, 113,  79, 214, 140, 117, 202,
     11,  60, 190,  38, 149, 255, 144, 161, 142,
     26, 105, 215, 238,  56, 156, 218,  79,  23,
     60, 132, 243, 129,  59,  12,   7, 126, 211,
    216,  41, 200,  37, 146,  41, 127,  33, 126,
     12,  30, 165,  11,  87, 174, 233, 168, 138,
     57,  26, 216, 234, 130,  69, 137, 131, 243,
    119, 162, 110, 215,  35, 219,  80, 201, 195,
    209,  35, 108, 194,  90,  57,  93, 154,  21,
    125, 102,  58,  70, 253, 245, 170, 225, 165,
    204, 241, 229,  77, 249,  55, 235, 247,   9,
     39, 255,  81, 121, 151, 174, 130, 109, 107,
     96,  34, 164, 182, 233, 138, 172,  35,  90,
     79,  82, 148,  29,   9,  93,   8,  65,  89,
    124, 194,  18,  42, 124, 168, 237,  54, 190,
    233,  82, 204, 233, 226,  59, 209, 220,  67,
    172,   6, 231, 109, 140, 136,  58,  31, 179,
    157, 157,  82,  68, 173,  98,  97,  61, 143,
    152, 109,  76,   7, 130,   0, 229, 140,  72,
    240, 145,  78, 235, 135, 137, 119, 126, 224,
    131, 177, 148, 148, 204, 233, 245, 151, 151,
     83, 149,  92, 149, 175, 198,  64, 197, 202,
    172,  37, 142,  71, 241,  93,  11, 159, 187,
    203, 166, 103, 219,  68, 232, 210,  72,  59,
    143, 118, 203, 158, 225,  83, 251, 251,  65,
     17, 108, 231,   0, 137,  36, 160, 117, 135
};

#pragma DATA_SECTION(OUT_SCORE, "Cdata");
uint16_t OUT_SCORE[2*2048] = {0};

#pragma DATA_SECTION(SEQ_ARRAY, "Cdata");
uint16_t SEQ_ARRAY[8] = {0, 1, 2, 3, 4, 5, 6, 7};

#pragma DATA_SECTION(SCRATCH_XX, "Bdata");
int32_t SCRATCH_XX[(WIN_WIDTH*9*ALIGN_2SIMD(NUM_POINTS))/8 + 8] = {0};

#pragma DATA_SECTION(SCRATCH_YY, "Cdata");
int32_t SCRATCH_YY[(WIN_WIDTH*9*ALIGN_2SIMD(NUM_POINTS))/8 + 8] = {0};

#pragma DATA_SECTION(SCRATCH_XY, "Bdata");
int32_t SCRATCH_XY[(WIN_WIDTH*9*ALIGN_2SIMD(NUM_POINTS))/8 + 8] = {0};

#pragma DATA_SECTION(IXX, "Adata");
int32_t IXX[ALIGN_2SIMD(NUM_POINTS)] = {0};

#pragma DATA_SECTION(IYY, "Cdata");
int32_t IYY[ALIGN_2SIMD(NUM_POINTS)] = {0};

#pragma DATA_SECTION(IXY, "Adata");
int32_t IXY[ALIGN_2SIMD(NUM_POINTS)] = {0};

#pragma DATA_SECTION(DET_L, "Bdata");
uint32_t DET_L[ALIGN_SIMD(NUM_POINTS)] = {0};

#pragma DATA_SECTION(DET_H, "Bdata");
int32_t DET_H[ALIGN_SIMD(NUM_POINTS)] = {0};

#pragma DATA_SECTION(OUT_SCORE_REF, "DDR_MEM");
uint16_t OUT_SCORE_REF[2*2048] = {0, 29415, 0, 29543, 0, 30351, 0, 29349, 0, 30221, 0, 30259, 0, 30274, 0, 29358};

/* Parameter Register Block */
#pragma DATA_SECTION(pblock_vcop_multipoint_harrisScore_7x7_u16, "Cdata");
unsigned short pblock_vcop_multipoint_harrisScore_7x7_u16[512];

void fillDefaultConfig(sMultipoint_harris_score_Config * params)
{
  strcpy(params->inImageBlocks, "");
  strcpy(params->outHarrisScore, "");
  params->numPoints            = 32;
  params->interBlockOffset     = 81;
  params->inputStride          = 9;
  params->sensitivityParam     = 1310;
  params->start_id             = 0;
  params->randSeed             = 0;
  params->numIter              = 1;
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


int32_t test_multipoint_harrisScore_u16()
{
    int32_t n, iter, status = 0;
    uint32_t seed;
    FILE *fp_in = NULL, *fp_out = NULL;

    profiler_init();

    if(gConfig_multipoint_harris_score.numPoints > 128) {
        printf("Error: Test bench supports only upto %d numPoints.\n", gConfig_multipoint_harris_score.numPoints);
        return -1;
    }

    printf("Number of points = %d, Start ID = %d, Rand seed = %d\n", gConfig_multipoint_harris_score.numPoints,
           gConfig_multipoint_harris_score.start_id, gConfig_multipoint_harris_score.randSeed);

    memset(OUT_SCORE, 0, sizeof(OUT_SCORE));

#if !(VCOP_HOST_EMULATION)
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                        IBUFHA_SYST, IBUFLA_SYST);

    vcop_multipoint_harrisScore_7x7_u16_init(IMAGE_BLOCKS,
        (uint16_t *)OUT_SCORE, gConfig_multipoint_harris_score.numPoints,
        WIN_WIDTH + 2, (WIN_WIDTH + 2)*(WIN_HEIGHT + 2),
        gConfig_multipoint_harris_score.sensitivityParam,
        (gConfig_multipoint_harris_score.start_id - 8), SEQ_ARRAY, SCRATCH_XX, SCRATCH_YY, SCRATCH_XY,
        IXX, IYY, IXY, (uint16_t *)IXX, (uint16_t *)IYY, (uint16_t *)IXY,
        (int16_t *)IXX + 1, (int16_t *)IYY + 1, (int16_t *)IXY + 1,
        DET_L, DET_H, (int32_t *)pblock_vcop_multipoint_harrisScore_7x7_u16,
        pblock_vcop_multipoint_harrisScore_7x7_u16);
#endif

    for (iter = 0; iter < gConfig_multipoint_harris_score.numIter; iter++)
    {
        printf("Iteration %d\n", iter);

        if(strcmp(gConfig_multipoint_harris_score.inImageBlocks, "")) {
            printf("File Test\n");
            fp_in = fopen((const char *)gConfig_multipoint_harris_score.inImageBlocks, "rb");
            if(fp_in == NULL) {
                printf("Failed to open input file: %s.\n", gConfig_multipoint_harris_score.inImageBlocks);
                return -1;
            }
            fread(IMAGE_BLOCKS, gConfig_multipoint_harris_score.numPoints*(WIN_WIDTH+2)*(WIN_HEIGHT+2), 1, fp_in);
            fclose(fp_in);
        }
        else {
            /* Generate input data */
            seed = (gConfig_multipoint_harris_score.randSeed == 0) ? _tsc_gettime() : gConfig_multipoint_harris_score.randSeed;
            srand(seed);
            printf("Random pattern test: Seed = %d\n", seed);
            createRandPattern(IMAGE_BLOCKS, (WIN_WIDTH+2)*(WIN_HEIGHT+2),
                              gConfig_multipoint_harris_score.interBlockOffset,
                              gConfig_multipoint_harris_score.numPoints, 256);
        }

#ifdef __DEBUG
        int32_t i, j;
        printf("\nInput Image Blocks:\n");
        for(n = 0; n < gConfig_multipoint_harris_score.numPoints; n++) {
            printf("I%d = [", n);
            for(i = 0; i < (WIN_HEIGHT+2); i++) {
                for(j = 0; j < (WIN_WIDTH+2); j++) {
                    printf("%3d, ",IMAGE_BLOCKS[n*gConfig_multipoint_harris_score.interBlockOffset +
                                               i*(WIN_WIDTH+2) + j]);
                }
                printf("\b\b;\n");
            }
            printf("\b\b]\n");
        }
#endif

        profiler_start();

#if VCOP_HOST_EMULATION
        vcop_multipoint_harrisScore_7x7_u16(IMAGE_BLOCKS,
            (uint16_t *)OUT_SCORE + iter*2*gConfig_multipoint_harris_score.numPoints,
            gConfig_multipoint_harris_score.numPoints,
            WIN_WIDTH + 2, (WIN_WIDTH + 2)*(WIN_HEIGHT + 2),
            gConfig_multipoint_harris_score.sensitivityParam,
            (gConfig_multipoint_harris_score.start_id - 8) +
            iter*gConfig_multipoint_harris_score.numPoints,
            SEQ_ARRAY, SCRATCH_XX, SCRATCH_YY, SCRATCH_XY,
            IXX, IYY, IXY, (uint16_t *)IXX, (uint16_t *)IYY, (uint16_t *)IXY,
            (int16_t *)IXX + 1, (int16_t *)IYY + 1, (int16_t *)IXY + 1,
            DET_L, DET_H, (int32_t *)pblock_vcop_multipoint_harrisScore_7x7_u16);
#else
        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                        IBUFHA_VCOP, IBUFLA_VCOP);

        /*---------------------------------------------------------------------*/
        /*  Function call to the VCOP-C API to be tested                       */
        /*---------------------------------------------------------------------*/
        vcop_multipoint_harrisScore_7x7_u16_vloops(pblock_vcop_multipoint_harrisScore_7x7_u16);
        _vcop_vloop_done();

        VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                            IBUFHA_SYST, IBUFLA_SYST);
#endif

        profiler_end();

        /*---------------------------------------------------------------------*/
        /*  Function call to the Natural-C API to be tested                    */
        /*  Compute Harris scores for all blocks in IMAGE_BLOCKS               */
        /*---------------------------------------------------------------------*/
        vcop_multipoint_harrisScore_u16_cn(IMAGE_BLOCKS,
            OUT_SCORE_REF + iter*2*gConfig_multipoint_harris_score.numPoints,
            gConfig_multipoint_harris_score.numPoints,
            WIN_WIDTH,
            WIN_HEIGHT,
            WIN_WIDTH + 2,
            (WIN_WIDTH + 2)*(WIN_HEIGHT + 2),
            gConfig_multipoint_harris_score.sensitivityParam,
            (gConfig_multipoint_harris_score.start_id + iter*gConfig_multipoint_harris_score.numPoints));

#ifdef __DEBUG
        printf("\nOutput Harris Scores = \n");
        for(n = 0; n < 2*gConfig_multipoint_harris_score.numPoints; n++) {
            printf("%d, ", OUT_SCORE[n + iter*2*gConfig_multipoint_harris_score.numPoints]);
        }
        printf("\n");
#endif
    }

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/
    status = memcmp(OUT_SCORE, OUT_SCORE_REF, 4*iter*gConfig_multipoint_harris_score.numPoints);

    if(status != 0) {
        printf("Harris score mismatches:\n");
        for(n = 0; n < iter*gConfig_multipoint_harris_score.numPoints; n++) {
            if(OUT_SCORE[2*n+1] != OUT_SCORE_REF[2*n+1]) {
                printf("Output mismatch for block %d, Output = %d, Expected = %d\n", n, OUT_SCORE[2*n+1], OUT_SCORE_REF[2*n+1]);
            }
        }
        printf("\nPayload mismatches:\n");
        for(n = 0; n < iter*gConfig_multipoint_harris_score.numPoints; n++) {
            if(OUT_SCORE[2*n] != OUT_SCORE_REF[2*n]) {
                printf("Output mismatch for block %d, Output = %d, Expected = %d\n", n, OUT_SCORE[2*n], OUT_SCORE_REF[2*n]);
            }
        }
        printf("\n");
    }

    if(strcmp(gConfig_multipoint_harris_score.outHarrisScore, "")) {
        fp_out = fopen((const char*)gConfig_multipoint_harris_score.outHarrisScore, "wb");
        if(fp_out != NULL) {
            fwrite(OUT_SCORE, 4*iter*gConfig_multipoint_harris_score.numPoints, 1, fp_out);
            fclose(fp_out);
        }
        else {
            printf("Failed to open Output file.\n");
        }
    }
    
    profiler_deinit();

    printf(status ? "test_multipoint_harrisScore_u16: FAIL\n" : "test_multipoint_harrisScore_u16: PASS\n");

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
      strcpy(configFile,"../testvecs/config/multipoint_harrisScore_u16.cfg");
    }

    fillDefaultConfig(&gConfig_multipoint_harris_score);
    status = readparamfile(configFile, &gsTokenMap_multipoint_harris_score[0]) ;
    if(status == -1)
    {
        printf("Parser Failed. Using default values.\n");
    }

    printf ("\nMultipoint Harris Score Test Bench:\n");
    status = test_multipoint_harrisScore_u16();

    return status;
}
