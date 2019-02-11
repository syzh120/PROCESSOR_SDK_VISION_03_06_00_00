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

#include "vcop.h"
#include "eve_profile.h"

/* ------------------------------------------------------------------------ */
/*  Include the "C" implementation of 422UYVY to 420NV12 format conversion. */
/* ------------------------------------------------------------------------ */
#include "../src_C/vcop_yuv_422uyvy_to_420nv12_cn.c"

#if VCOP_HOST_EMULATION
  #include "../src_kernelC/vcop_yuv_422uyvy_to_420nv12_kernel.k" // kernel source
#else
  #include "vcop_yuv_422uyvy_to_420nv12_kernel.h"
#endif

//#define __DEBUG

#define NUM_ITER (1)
#define BLK_WIDTH (64)
#define BLK_HEIGHT (64)
#define IN_BLK_STRIDE (2*BLK_WIDTH)
#define OUT_BLK_STRIDE (BLK_WIDTH)

#pragma DATA_SECTION(IN, "Adata");
unsigned char IN[IN_BLK_STRIDE*BLK_HEIGHT] = {
     41,  35, 190, 132, 225, 108, 214, 174,  82, 144,  73, 241, 241, 187, 233, 235,
    179, 166, 219,  60, 135,  12,  62, 153,  36,  94,  13,  28,   6, 183,  71, 222,
    179,  18,  77, 200,  67, 187, 139, 166,  31,   3,  90, 125,   9,  56,  37,  31,
     93, 212, 203, 252, 150, 245,  69,  59,  19,  13, 137,  10,  28, 219, 174,  50,
     32, 154,  80, 238,  64, 120,  54, 253,  18,  73,  50, 246, 158, 125,  73, 220,
    173,  79,  20, 242,  68,  64, 102, 208, 107, 196,  48, 183,  50,  59, 161,  34,
    246,  34, 145, 157, 225, 139,  31, 218, 176, 202, 153,   2, 185, 114, 157,  73,
     44, 128, 126, 197, 153, 213, 233, 128, 178, 234, 201, 204,  83, 191, 103, 214,
    191,  20, 214, 126,  45, 220, 142, 102, 131, 239,  87,  73,  97, 255, 105, 143,
     97, 205, 209,  30, 157, 156,  22, 114, 114, 230,  29, 240, 132,  79,  74, 119,
      2, 215, 232,  57,  44,  83, 203, 201,  18,  30,  51, 116, 158,  12, 244, 213,
    212, 159, 212, 164,  89, 126,  53, 207,  50,  34, 244, 204, 207, 211, 144,  45,
     72, 211, 143, 117, 230, 217,  29,  42, 229, 192, 247,  43, 120, 129, 135,  68,
     14,  95,  80,   0, 212,  97, 141, 190, 123,   5,  21,   7,  59,  51, 130,  31,
     24, 112, 146, 218, 100,  84, 206, 177, 133,  62, 105,  21, 248,  70, 106,   4,
    150, 115,  14, 217,  22,  47, 103, 104, 212, 247,  74,  74, 208,  87, 104, 118};

#pragma DATA_SECTION(OUT, "Bdata");
unsigned char OUT[3*OUT_BLK_STRIDE*BLK_HEIGHT/2] = {0};

#pragma DATA_SECTION(OUT_REF, "DDR_MEM");
unsigned char OUT_REF[3*OUT_BLK_STRIDE*BLK_HEIGHT/2] = {
     35, 132, 108, 174, 144, 241, 187, 235, 166,  60,  12, 153,  94,  28, 183, 222,
     18, 200, 187, 166,   3, 125,  56,  31, 212, 252, 245,  59,  13,  10, 219,  50,
    154, 238, 120, 253,  73, 246, 125, 220,  79, 242,  64, 208, 196, 183,  59,  34,
     34, 157, 139, 218, 202,   2, 114,  73, 128, 197, 213, 128, 234, 204, 191, 214,
     20, 126, 220, 102, 239,  73, 255, 143, 205,  30, 156, 114, 230, 240,  79, 119,
    215,  57,  83, 201,  30, 116,  12, 213, 159, 164, 126, 207,  34, 204, 211,  45,
    211, 117, 217,  42, 192,  43, 129,  68,  95,   0,  97, 190,   5,   7,  51,  31,
    112, 218,  84, 177,  62,  21,  70,   4, 115, 217,  47, 104, 247,  74,  87, 118,
    110, 134, 146, 177,  57,  82, 125, 135, 136, 211, 143,  66,  28,  75,  17, 123,
    139, 113, 145,  43,  97, 102, 172, 115, 109,  73, 111, 168, 143, 125,  67, 132,
     97, 223,  45, 173,  75,  69, 128, 175, 155, 211, 123,  38,  82, 137, 170, 109,
     48, 145, 165, 118, 181, 176, 184, 121,  82,  47, 117, 122, 168,  48, 134, 117};

void createPattern(unsigned char *img, unsigned short width, unsigned short height,
                   unsigned short stride, unsigned short upper_bound)
{
    int i, j;

    for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            img[i*stride + j] = (rand() & 0xFF) % (upper_bound + 1);
        }
    }
}


int test_yuv_422uyvy_to_420nv12()
{
    int i, j, iter, fail = 0, status = 0;
    unsigned int seed;

    profiler_init();

    printf("Block size = %dx%d \n", BLK_WIDTH, BLK_HEIGHT);

#if !(VCOP_HOST_EMULATION)
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                    IBUFHA_SYST, IBUFLA_SYST);

    vcop_yuv_422uyvy_to_420nv12_init(IN, OUT, BLK_WIDTH, BLK_HEIGHT,
                    IN_BLK_STRIDE, OUT_BLK_STRIDE,
                    __pblock_vcop_yuv_422uyvy_to_420nv12);
#endif

    for (iter = 0; iter < NUM_ITER; iter++)
    {
        printf("Iteration %d:\n", iter);

        seed = _tsc_gettime();
        srand(seed);
        printf("Pattern Generation Seed = %d\n", seed);
        createPattern(IN, BLK_WIDTH, BLK_HEIGHT, IN_BLK_STRIDE, 255);

#ifdef __DEBUG
        printf("\nInput Image Block:\n");
        for(i = 0; i < BLK_HEIGHT; i++) {
            for(j = 0; j < 2*BLK_WIDTH; j++) {
                printf("%3d ", IN[i*IN_BLK_STRIDE+j]);
            }
            printf("\n");
        }
        printf("\n");
#endif

        /*---------------------------------------------------------------------*/
        /*  Function call to the Natural-C API to be tested                    */
        /*---------------------------------------------------------------------*/
        vcop_yuv_422uyvy_to_420nv12_cn(IN, OUT_REF, BLK_WIDTH, BLK_HEIGHT,
                        IN_BLK_STRIDE, OUT_BLK_STRIDE);

        profiler_start();

#if VCOP_HOST_EMULATION
        vcop_yuv_422uyvy_to_420nv12(IN, OUT, BLK_WIDTH, BLK_HEIGHT,
                        IN_BLK_STRIDE, OUT_BLK_STRIDE);
#else
        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                        IBUFHA_VCOP, IBUFLA_VCOP);

        /*---------------------------------------------------------------------*/
        /*  Function call to the VCOP-C API to be tested                       */
        /*---------------------------------------------------------------------*/
        vcop_yuv_422uyvy_to_420nv12_vloops(__pblock_vcop_yuv_422uyvy_to_420nv12);
        _vcop_vloop_done();

        VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                        IBUFHA_SYST, IBUFLA_SYST);
#endif

        profiler_end();

        /*---------------------------------------------------------------------*/
        /*  Compare the results of output arrays with expected output arrays.  */
        /*---------------------------------------------------------------------*/
        for (i = 0; i < 3*BLK_HEIGHT/2; i++) {
            fail |= memcmp((OUT + i*OUT_BLK_STRIDE), (OUT_REF + i*OUT_BLK_STRIDE), BLK_WIDTH);
        }

        if(fail != 0) {
            for (i = 0; i < 3*BLK_HEIGHT/2; i++)
            {
                for (j = 0; j < BLK_WIDTH; j++)
                {
                    if (OUT[i*OUT_BLK_STRIDE+j] != OUT_REF[OUT_BLK_STRIDE*i+j])
                    {
                        printf("Error: At (%d, %d) Output = %d, Expected = %d\n",
                               i, j, OUT[i*OUT_BLK_STRIDE+j], OUT_REF[OUT_BLK_STRIDE*i+j]);
                    }
                }
            }
        }

#ifdef __DEBUG
        printf("\nOutput Frame:\n");
        for(i = 0; i < 3*BLK_HEIGHT/2; i++) {
            for(j = 0; j < BLK_WIDTH; j++) {
                printf("%3d ",OUT[i*OUT_BLK_STRIDE+j]);
            }
            printf("\n");
        }
        printf("\n");

        printf("\nReference Output Frame:\n");
        for(i = 0; i < 3*BLK_HEIGHT/2; i++) {
            for(j = 0; j < BLK_WIDTH; j++) {
                printf("%3d ",OUT_REF[i*OUT_BLK_STRIDE+j]);
            }
            printf("\n");
        }
        printf("\n");
#endif

        printf(fail ? "FAIL\n":"PASS\n");
        status |= fail;
    }

    profiler_deinit();

    printf(status ? "test_yuv_422uyvy_to_420nv12: FAIL\n":"test_yuv_422uyvy_to_420nv12: PASS\n");

    return (status);
}


int test_yuv_422uyvy_to_420nv12_cn()
{
    int i, j, status = 0;

    printf("test_yuv_422uyvy_to_420nv12_cn: ");

#ifdef __DEBUG
    printf("\nInput Image Block:\n");
    for(i = 0; i < 8; i++) {
        for(j = 0; j < 32; j++) {
            printf("%3d ", IN[i*32+j]);
        }
        printf("\n");
    }
    printf("\n");
#endif
    
    /*---------------------------------------------------------------------*/
    /*  Function call to the Natural-C API to be tested                    */
    /*  FOrmat conversion of YUV420 NV12 image to YUV 422 UYVY             */
    /*---------------------------------------------------------------------*/
    vcop_yuv_422uyvy_to_420nv12_cn(IN, OUT, 16, 8, 32, 16);

#ifdef __DEBUG
    printf("\nOutput Frame:\n");
    for(i = 0; i < 3*8/2; i++) {
        for(j = 0; j < 16; j++) {
            printf("%3d ",OUT[i*16+j]);
        }
        printf("\n");
    }
    printf("\n");
    
    printf("\nReference Output Frame:\n");
    for(i = 0; i < 3*8/2; i++) {
        for(j = 0; j < 16; j++) {
            printf("%3d ",OUT_REF[i*16+j]);
        }
        printf("\n");
    }
    printf("\n");
#endif

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/
    status = memcmp(OUT, OUT_REF, 3*8*16/2);

    if(status != 0) {
        for(i = 0; i < 3*8/2; i++) {
            for(j = 0; j < 16; j++) {
                if(OUT[i*16 + j] != OUT_REF[i*16 + j]) {
                    printf("\nOutput mismatch at (%d, %d), Output = %d, Expected = %d\n",
                           i, j, OUT[i*16 + j], OUT_REF[i*16 + j]);
                }
            }
        }
    }

    printf(status ? "FAIL\n" : "PASS\n");
    return (status);
}


int main()
{
    int status = 0;

    /* Validate the C reference */
    printf ("\nYUV 422UYVY to 420NV12 Format Conversion Test Bench: Validating C-model\n");
    status = test_yuv_422uyvy_to_420nv12_cn();

    /* Validate the Kernel */
    printf ("\nYUV 422UYVY to 420NV12 Format Conversion Test Bench: Validating Kernel\n");
    status = test_yuv_422uyvy_to_420nv12();

    return status;
}
