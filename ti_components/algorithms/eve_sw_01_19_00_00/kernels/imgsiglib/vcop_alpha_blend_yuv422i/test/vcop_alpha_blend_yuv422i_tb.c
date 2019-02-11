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
/*  Include the "C" implementation of YUV422i Alpha Blend function.         */
/* ------------------------------------------------------------------------ */
#include "../src_C/vcop_alpha_blend_yuv422i_cn.c"

#include "vcop_host.h"
#include "vcop_alpha_blend_yuv422i_kernel.h"

//#define __DEBUG

#define NUM_ITER (1)
#define BLK_WIDTH (64)
#define BLK_STRIDE (2*BLK_WIDTH)
#define BLK_HEIGHT (64)

#pragma DATA_SECTION(IN_1, "Adata");
unsigned char IN_1[BLK_STRIDE*BLK_HEIGHT] = {0};

#pragma DATA_SECTION(IN_2, "Bdata");
unsigned char IN_2[BLK_STRIDE*BLK_HEIGHT] = {0};

#pragma DATA_SECTION(ALPHA, "Adata");
unsigned char ALPHA[BLK_WIDTH*BLK_HEIGHT] = {0};

#pragma DATA_SECTION(OUT, "Bdata");
unsigned char OUT[BLK_STRIDE*BLK_HEIGHT] = {0};

#pragma DATA_SECTION(OUT_REF, "DDR_MEM");
unsigned char OUT_REF[BLK_STRIDE*BLK_HEIGHT] = {0};


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


int test_alpha_blend_yuv422i()
{
    int i, j, iter, fail = 0, status = 0;
    unsigned int seed;

    profiler_init();

    printf("Block size = %dx%d \n", BLK_WIDTH, BLK_HEIGHT);

    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    vcop_alpha_blend_yuv422i_init(IN_1, IN_2, ALPHA, OUT, BLK_WIDTH, BLK_HEIGHT, BLK_STRIDE,
                                BLK_STRIDE, BLK_STRIDE, __pblock_vcop_alpha_blend_yuv422i);

    for (iter = 0; iter < NUM_ITER; iter++)
    {
        printf("Iteration %d:\n", iter);

        seed = _tsc_gettime();
        srand(seed);
        printf("Pattern Generation Seed = %d\n", seed);
        createPattern(IN_1, 2*BLK_WIDTH, BLK_HEIGHT, BLK_STRIDE, 255);
        createPattern(IN_2, 2*BLK_WIDTH, BLK_HEIGHT, BLK_STRIDE, 255);
        createPattern(ALPHA, BLK_WIDTH, BLK_HEIGHT, BLK_WIDTH, 16);

#ifdef __DEBUG
        printf("\nInput Image 1 Block:\n");
        for(i = 0; i < BLK_HEIGHT; i++) {
            for(j = 0; j < 2*BLK_WIDTH; j++) {
                printf("%3d ",IN_1[i*BLK_STRIDE+j]);
            }
            printf("\n");
        }
        printf("\n");

        printf("\nInput Image 2 Block:\n");
        for(i = 0; i < BLK_HEIGHT; i++) {
            for(j = 0; j < 2*BLK_WIDTH; j++) {
                printf("%3d ",IN_2[i*BLK_STRIDE+j]);
            }
            printf("\n");
        }
        printf("\n");

        printf("\nInput Alpha Block:\n");
        for(i = 0; i < BLK_HEIGHT; i++) {
            for(j = 0; j < BLK_WIDTH; j++) {
                printf("%3d ",ALPHA[i*BLK_WIDTH+j]);
            }
            printf("\n");
        }
        printf("\n");
#endif

        /*---------------------------------------------------------------------*/
        /*  Function call to the Natural-C API to generate reference output    */
        /*---------------------------------------------------------------------*/
        vcop_alpha_blend_yuv422i_cn(IN_1, IN_2, ALPHA, OUT_REF, BLK_WIDTH, BLK_HEIGHT,
                                    BLK_STRIDE, BLK_STRIDE, BLK_STRIDE);

        profiler_start();

        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                        IBUFHA_VCOP, IBUFLA_VCOP);

        /*---------------------------------------------------------------------*/
        /*  Function call to the VCOP-C API to be tested                       */
        /*---------------------------------------------------------------------*/
        vcop_alpha_blend_yuv422i_vloops(__pblock_vcop_alpha_blend_yuv422i);
        _vcop_vloop_done();

        VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                        IBUFHA_SYST, IBUFLA_SYST);

        profiler_end();

        /*---------------------------------------------------------------------*/
        /*  Compare the results of output arrays with expected output arrays.  */
        /*---------------------------------------------------------------------*/
        fail = memcmp(OUT, OUT_REF, 2*BLK_HEIGHT*BLK_WIDTH);

        if(fail != 0) {
            for (i = 0; i < BLK_HEIGHT; i++)
            {
                for (j = 0; j < 2*BLK_WIDTH; j++)
                {
                    if (OUT[i*BLK_STRIDE+j] != OUT_REF[i*BLK_STRIDE+j])
                    {
                        printf("Error: At (%d, %d) Output = %d, Expected = %d\n",
                               i, j, OUT[i*BLK_STRIDE+j], OUT_REF[i*BLK_STRIDE+j]);
                    }
                }
            }
        }

#ifdef __DEBUG
        printf("\nOutput Blended Frame:\n");
        for(i = 0; i < BLK_HEIGHT; i++) {
            for(j = 0; j < 2*BLK_WIDTH; j++) {
                printf("%3d ",OUT[i*BLK_STRIDE+j]);
            }
            printf("\n");
        }
        printf("\n");

        printf("\nReference Blended Frame:\n");
        for(i = 0; i < BLK_HEIGHT; i++) {
            for(j = 0; j < 2*BLK_WIDTH; j++) {
                printf("%3d ",OUT_REF[i*BLK_STRIDE+j]);
            }
            printf("\n");
        }
        printf("\n");
#endif

        printf(fail ? "FAIL\n":"PASS\n");
        status |= fail;
    }

    profiler_deinit();

    printf(status ? "test_alpha_blend_yuv422i: FAIL\n":"test_alpha_blend_yuv422i: PASS\n");

    return (status);
}


int test_alpha_blend_yuv422i_cn(unsigned char alpha, unsigned char *ref_out)
{
    int i, j, status = 0;

    printf("test_alpha_blend_yuv422i_cn (alpha = %2d): ", alpha);

    createPattern(IN_1, 2*BLK_WIDTH, BLK_HEIGHT, BLK_STRIDE, 256);
    createPattern(IN_2, 2*BLK_WIDTH, BLK_HEIGHT, BLK_STRIDE, 256);

    for(i = 0; i < BLK_HEIGHT; i++) {
        for(j = 0; j < BLK_WIDTH; j++) {
            ALPHA[i*BLK_WIDTH + j] = alpha;
        }
    }
    
    /*---------------------------------------------------------------------*/
    /*  Function call to the Natural-C API to be tested                    */
    /*  Alpha blending of YUV422 interleaved images IN_1 & IN_2            */
    /*---------------------------------------------------------------------*/
    vcop_alpha_blend_yuv422i_cn(IN_1, IN_2, ALPHA, OUT, BLK_WIDTH, BLK_HEIGHT,
                                BLK_STRIDE, BLK_STRIDE, BLK_STRIDE);
                                 
    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/
    status = memcmp(OUT, ref_out, 2*BLK_HEIGHT*BLK_WIDTH);

    if(status != 0) {
        for(i = 0; i < BLK_HEIGHT; i++) {
            for(j = 0; j < 2*BLK_WIDTH; j++) {
                if(OUT[i*BLK_STRIDE + j] != ref_out[i*BLK_STRIDE + j]) {
                    printf("\nOutput mismatch at (%d, %d), Output = %d, Expected = %d\n", i, j, OUT[i*BLK_STRIDE + j], ref_out[i*BLK_STRIDE + j]);
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
    printf ("\nYUV422i Alpha Blending Test Bench: Validating C-model\n");
    status = test_alpha_blend_yuv422i_cn(16, IN_1);
    status = test_alpha_blend_yuv422i_cn(0, IN_2);

    /* Validate the Kernel */
    printf ("\nYUV422i Alpha Blending Test Bench: Validating Kernel\n");
    status = test_alpha_blend_yuv422i();

    return status;
}
