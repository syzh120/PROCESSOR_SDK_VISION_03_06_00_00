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

#include "vcop.h"
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_bin_image_to_list_config.h"

#if VCOP_HOST_EMULATION
  #include "../src_kernelC/vcop_bin_image_to_list_kernel.k" // kernel source
#else
  #include "vcop_bin_image_to_list_kernel.h"
#endif

/* ------------------------------------------------------------------------ */
/*  Include prototype for the "C" implementation of binary image to list    */
/*  function.                                                               */
/* ------------------------------------------------------------------------ */
#include "vcop_bin_image_to_list_cn.h"

//#define __DEBUG

#define BLOCK_HEIGHT  (56)
#define BLOCK_WIDTH   (56)          // In binary pixels
#define BLOCK_STRIDE  (BLOCK_WIDTH) // In binary pixels
#define OUT_LEN       (BLOCK_WIDTH*BLOCK_HEIGHT)

#pragma DATA_SECTION(IMAGE, "Adata");
uint8_t IMAGE[BLOCK_STRIDE*BLOCK_HEIGHT/8] = {
    0x29,  0x23,
    0xbe,  0x84,
    0xe1,  0x6c,
    0xd6,  0xae,
    0x52,  0x90,
    0x49,  0xf1,
    0xf1,  0xbb,
    0xe9,  0xeb,
    0xb3,  0xa6,
    0xdb,  0x3c,
    0x87,  0x0c,
    0x3e,  0x99,
    0x24,  0x5e,
    0x0d,  0x1c,
    0x06,  0xb7,
    0x47,  0xde};

#pragma DATA_SECTION(OUTXY, "Bdata");
uint32_t OUTXY[OUT_LEN] = {0x00};

#pragma DATA_SECTION(XSEQ, "Cdata");
uint32_t XSEQ[BLOCK_WIDTH] = {0x00};

#pragma DATA_SECTION(UPPERLEFTXY, "Bdata");
uint32_t UPPERLEFTXY[1] = {0};

#pragma DATA_SECTION(LISTSIZE, "Cdata");
uint32_t LISTSIZE[8] = {0};

#pragma DATA_SECTION(UPPERLEFTXY_REF, "Bdata");
uint32_t UPPERLEFTXY_REF[1] = {0};

#pragma DATA_SECTION(OUTXY_REF, "DDR_MEM");
uint32_t OUTXY_REF[OUT_LEN] = {
    0x00000000, 0x00030000, 0x00050000, 0x00080000,
    0x00090000, 0x000d0000, 0x00010001, 0x00020001,
    0x00030001, 0x00040001, 0x00050001, 0x00070001,
    0x000a0001, 0x000f0001, 0x00000002, 0x00050002,
    0x00060002, 0x00070002, 0x000a0002, 0x000b0002,
    0x000d0002, 0x000e0002, 0x00010003, 0x00020003,
    0x00040003, 0x00060003, 0x00070003, 0x00090003,
    0x000a0003, 0x000b0003, 0x000d0003, 0x000f0003,
    0x00010004, 0x00040004, 0x00060004, 0x000c0004,
    0x000f0004, 0x00000005, 0x00030005, 0x00060005,
    0x00080005, 0x000c0005, 0x000d0005, 0x000e0005,
    0x000f0005, 0x00000006, 0x00040006, 0x00050006,
    0x00060006, 0x00070006, 0x00080006, 0x00090006,
    0x000b0006, 0x000c0006, 0x000d0006, 0x000f0006,
    0x00000007, 0x00030007, 0x00050007, 0x00060007,
    0x00070007, 0x00080007, 0x00090007, 0x000b0007,
    0x000d0007, 0x000e0007, 0x000f0007, 0x00000008,
    0x00010008, 0x00040008, 0x00050008, 0x00070008,
    0x00090008, 0x000a0008, 0x000d0008, 0x000f0008,
    0x00000009, 0x00010009, 0x00030009, 0x00040009,
    0x00060009, 0x00070009, 0x000a0009, 0x000b0009,
    0x000c0009, 0x000d0009, 0x0000000a, 0x0001000a,
    0x0002000a, 0x0007000a, 0x000a000a, 0x000b000a,
    0x0001000b, 0x0002000b, 0x0003000b, 0x0004000b,
    0x0005000b, 0x0008000b, 0x000b000b, 0x000c000b,
    0x000f000b, 0x0002000c, 0x0005000c, 0x0009000c,
    0x000a000c, 0x000b000c, 0x000c000c, 0x000e000c,
    0x0000000d, 0x0002000d, 0x0003000d, 0x000a000d,
    0x000b000d, 0x000c000d, 0x0001000e, 0x0002000e,
    0x0008000e, 0x0009000e, 0x000a000e, 0x000c000e,
    0x000d000e, 0x000f000e, 0x0000000f, 0x0001000f,
    0x0002000f, 0x0006000f, 0x0009000f, 0x000a000f,
    0x000b000f, 0x000c000f, 0x000e000f, 0x000f000f};

#pragma DATA_SECTION(LISTSIZE_REF, "DDR_MEM");
uint32_t LISTSIZE_REF[1] = {132};

void createPattern(uint8_t *img, uint16_t width, uint16_t height,
                   uint16_t stride, uint16_t upper_bound)
{
    int32_t i, j;

    for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            img[i*stride + j] = (rand() & 0xFF) % (upper_bound + 1);
        }
    }
}

int32_t test_bin_image_to_list_cn()
{
    int32_t i, status = 0;

    printf("test_bin_image_to_list_cn: ");

#ifdef __DEBUG
    int32_t j, k;
    printf("\nInput Image Block:\n");
    for(i = 0; i < 16; i++) {
        for(j = 0; j < 2; j++) {
            for(k = 0; k < 8; k++) {
                printf("%d", ((IMAGE[i*16/8+j] >> k) & 0x1));
            }
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
#endif

    /*---------------------------------------------------------------------*/
    /*  Function call to the Natural-C API to be tested                    */
    /*  Binary image to X and Y co-ordinate lists                          */
    /*---------------------------------------------------------------------*/
    vcop_bin_image_to_list_cn(IMAGE, UPPERLEFTXY, OUTXY, LISTSIZE, 16, 16, 16, 0, 1);

#ifdef __DEBUG
    printf("List Size = %d", LISTSIZE[0]);

    printf("\nOutput List:\n");
    for(i = 0; i < LISTSIZE[0]; i++) {
        printf("(%2d, %2d) ",((uint16_t*)OUTXY)[2*i], ((uint16_t*)OUTXY)[2*i+1]);
        if(i % 8 == 7) printf("\n");
    }
    printf("\n");

    printf("\nReference Output Frame:\n");
    for(i = 0; i < LISTSIZE[0]; i++) {
        printf("(%2d, %2d) ", ((uint16_t*)OUTXY_REF)[2*i], ((uint16_t*)OUTXY_REF)[2*i+1]);
        if(i % 8 == 7) printf("\n");
    }
    printf("\n");
#endif

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/
    if(LISTSIZE[0] != LISTSIZE_REF[0]) {
        printf("List size mismatch: Actual = %d, Expected = %d\n", LISTSIZE[0], LISTSIZE_REF[0]);
        status = 1;
    }

    if(status == 0) {
        status = memcmp(OUTXY, OUTXY_REF, 4*LISTSIZE_REF[0]);
    }

    if(status != 0) {
        for(i = 0; i < LISTSIZE[0]; i++) {
            if(OUTXY[i] != OUTXY_REF[i]) {
                printf("\nOutput mismatch at %d, Output = (%d, %d), Expected = (%d, %d)\n",
                       i, ((uint16_t*)OUTXY)[2*i], ((uint16_t*)OUTXY)[2*i],
                       ((uint16_t*)OUTXY_REF)[2*i+1], ((uint16_t*)OUTXY_REF)[2*i+1]);
            }
        }
    }

    printf(status ? "FAIL\n" : "PASS\n");
    return (status);
}


int32_t test_bin_image_to_list()
{
    int32_t i, iter, fail, status = 0;
    uint32_t seed;

    uint8_t  outputQformat;
    profiler_init();

    printf("Block size = %dx%d \n", gConfig_bin_image_to_list.blockWidth, gConfig_bin_image_to_list.blockHeight);

    UPPERLEFTXY[0] = gConfig_bin_image_to_list.upperLeftXY;

    outputQformat =  gConfig_bin_image_to_list.outputQformat;



    if ( gConfig_bin_image_to_list.xyOrder )
    {
      outputQformat = gConfig_bin_image_to_list.outputQformat;
    }
    else
    {
      outputQformat = gConfig_bin_image_to_list.outputQformat + 16;
    }

    for (i = 0; i < gConfig_bin_image_to_list.blockWidth; i++)
    {
        if ( gConfig_bin_image_to_list.xyOrder )
        {
          XSEQ[i] = (i << gConfig_bin_image_to_list.outputQformat)<<16;
        }
        else
        {
          XSEQ[i] = (i << gConfig_bin_image_to_list.outputQformat);
        }
    }


#if !(VCOP_HOST_EMULATION)
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                        IBUFHA_SYST, IBUFLA_SYST);

    vcop_bin_image_to_list_init(IMAGE, UPPERLEFTXY, OUTXY, LISTSIZE, gConfig_bin_image_to_list.blockWidth,
                                 gConfig_bin_image_to_list.blockHeight, gConfig_bin_image_to_list.blockStride,
                                 outputQformat,
                                 XSEQ, __pblock_vcop_bin_image_to_list);
#endif




    for (iter = 0; iter < gConfig_bin_image_to_list.numIter; iter++)
    {
        printf("Iteration %d\n", iter);
        fail = 0;

        seed = (gConfig_bin_image_to_list.randSeed == 0) ? _tsc_gettime() : gConfig_bin_image_to_list.randSeed;
        srand(seed);
        printf("Pattern Generation Seed = %d\n", seed);
        createPattern(IMAGE, gConfig_bin_image_to_list.blockWidth/8, gConfig_bin_image_to_list.blockHeight, gConfig_bin_image_to_list.blockStride/8, 255);

#ifdef __DEBUG
        int32_t j, k;
        printf("\nInput Image Block:\n");
        for(i = 0; i < gConfig_bin_image_to_list.blockHeight; i++) {
            for(j = 0; j < gConfig_bin_image_to_list.blockWidth/8; j++) {
                for(k = 0; k < 8; k++) {
                    printf("%d", ((IMAGE[i*gConfig_bin_image_to_list.blockStride/8+j] >> k) & 0x1));
                }
                printf(" ");
            }
            printf("\n");
        }
        printf("\n");
#endif

        profiler_start();

#if VCOP_HOST_EMULATION
        vcop_bin_image_to_list(IMAGE, UPPERLEFTXY, OUTXY, LISTSIZE, gConfig_bin_image_to_list.blockWidth,
                               gConfig_bin_image_to_list.blockHeight, gConfig_bin_image_to_list.blockStride,
                               outputQformat,
                               XSEQ);
#else
        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                        IBUFHA_VCOP, IBUFLA_VCOP);

        /*---------------------------------------------------------------------*/
        /*  Function call to the VCOP-C API to be tested                       */
        /*---------------------------------------------------------------------*/
        vcop_bin_image_to_list_vloops(__pblock_vcop_bin_image_to_list);
        _vcop_vloop_done();

        VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                            IBUFHA_SYST, IBUFLA_SYST);
#endif

        profiler_end();

        /*---------------------------------------------------------------------*/
        /*  Compare the results of output arrays with expected output arrays.  */
        /*---------------------------------------------------------------------*/
        UPPERLEFTXY_REF[0] = gConfig_bin_image_to_list.upperLeftXY;
        vcop_bin_image_to_list_cn(IMAGE, UPPERLEFTXY_REF, OUTXY_REF, LISTSIZE_REF,
            gConfig_bin_image_to_list.blockWidth,
            gConfig_bin_image_to_list.blockHeight,
            gConfig_bin_image_to_list.blockStride,
            gConfig_bin_image_to_list.outputQformat,
            gConfig_bin_image_to_list.xyOrder);

        if(LISTSIZE[0] != LISTSIZE_REF[0]) {
            printf("List size mismatch: Actual = %d, Expected = %d\n", LISTSIZE[0], LISTSIZE_REF[0]);
            fail = 1;
        }

        if(fail == 0) {
            fail = memcmp(OUTXY, OUTXY_REF, 4*LISTSIZE_REF[0]);
        }

        if(fail != 0) {
            for(i = 0; i < LISTSIZE[0]; i++) {
                if(OUTXY[i] != OUTXY_REF[i]) {
                    printf("\nOutput mismatch at %d, Output = (%d, %d), Expected = (%d, %d)\n",
                           i, ((uint16_t*)OUTXY)[2*i], ((uint16_t*)OUTXY)[2*i+1],
                           ((uint16_t*)OUTXY_REF)[2*i], ((uint16_t*)OUTXY_REF)[2*i+1]);
                }
            }
        }

#ifdef __DEBUG
        printf("Kernel Output:\n");
        for (i = 0; i < LISTSIZE[0]; i++)
        {
            printf("(%d, %d) ", ((uint16_t*)OUTXY)[2*i], ((uint16_t*)OUTXY)[2*i+1]);
            if((i % 8) == 7) {
                printf("\n");
            }
        }
        printf("\n");

        printf("Number of elements in the list = %d\n", LISTSIZE[0]);
#endif

        printf(fail ? "FAIL\n":"PASS\n");
        status |= fail;
    }

    profiler_deinit();

    printf(status ? "test_bin_image_to_list: FAIL\n":"test_bin_image_to_list: PASS\n");

    return 0;
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
#if VCOP_HOST_EMULATION
        strcpy(configFile,"../testvecs/config/bin_image_to_list.cfg");
#else
        strcpy(configFile,"../testvecs/config/bin_image_to_list.cfg");
#endif
    }

    status = readparamfile(configFile, &gsTokenMap_bin_image_to_list[0]) ;
    if(status == -1)
    {
        printf("Parser Failed");
        return -1 ;
    }

    /* Validate the Kernel */
    printf ("\nBinary Image to List Test Bench: Validating Kernel\n");
    status = test_bin_image_to_list();

    return status;
}
