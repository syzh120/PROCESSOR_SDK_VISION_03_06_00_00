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
#include "vcop_extract_bit_field_u32_config.h"

#if VCOP_HOST_EMULATION
  #include "../src_kernelC/vcop_extract_bit_field_u32_kernel.k" // kernel source
#else
  #include "vcop_extract_bit_field_u32_kernel.h"
#endif

/* ------------------------------------------------------------------------ */
/*  Include prototype of "C" implementation of prune big list function.     */
/* ------------------------------------------------------------------------ */
#include "vcop_extract_bit_field_u32_cn.h"

//#define __DEBUG

#define MAX_LIST_LENGTH  (4096)

#pragma DATA_SECTION(IN, "Adata");
uint32_t IN[MAX_LIST_LENGTH] = {0};

#pragma DATA_SECTION(OUT, "Bdata");
uint8_t OUT[MAX_LIST_LENGTH] = {0};

#pragma DATA_SECTION(OUT_REF, "DDR_MEM");
uint8_t OUT_REF[MAX_LIST_LENGTH] = {0};


void createRndPattern32(uint32_t *img, uint16_t length, uint32_t mask)
{
    int32_t i;

    for(i = 0; i < length; i++) {
        img[i] = rand()&mask;
    }
}


void fillDefaultConfig(sextract_bit_field_u32_Config * params)
{
  strcpy(params->inList, "");
  strcpy(params->outList, "");
  params->listLength  = MAX_LIST_LENGTH;
  params->bitMask     = 0x00003800;
  params->shift       = 11;
  params->randSeed    = 0;
  params->numIter     = 1;
}


int32_t test_extract_bit_field_u32()
{
    int32_t i, iter, fail, status = 0;
    uint32_t seed;
    FILE *fp_in = NULL, *fp_out = NULL;

    profiler_init();

    printf("List length = %d\n", gConfig_extract_bit_field_u32.listLength);

#if !(VCOP_HOST_EMULATION)
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                        IBUFHA_SYST, IBUFLA_SYST);

    vcop_extract_bit_field_u32_init(IN, gConfig_extract_bit_field_u32.listLength,
            gConfig_extract_bit_field_u32.bitMask, gConfig_extract_bit_field_u32.shift,
            OUT, __pblock_vcop_extract_bit_field_u32);
#endif


    for (iter = 0; iter < gConfig_extract_bit_field_u32.numIter; iter++)
    {
        printf("Iteration %d\n", iter);
        fail = 0;

        if(strcmp(gConfig_extract_bit_field_u32.inList, "")) {
            fp_in = fopen((const char *)gConfig_extract_bit_field_u32.inList, "r");
            if(fp_in == NULL) {
                printf("Failed to open input file: %s.\n", gConfig_extract_bit_field_u32.inList);
                return -1;
            }

            for(i = 0; i < gConfig_extract_bit_field_u32.listLength; i++) {
                fscanf(fp_in, "%6d, ", &IN[i]);
            }

            fclose(fp_in);
        }
        else {
            seed = (gConfig_extract_bit_field_u32.randSeed == 0) ? _tsc_gettime() : gConfig_extract_bit_field_u32.randSeed;
            srand(seed);
            printf("Pattern Generation Seed = %d\n", seed);
            createRndPattern32(IN, gConfig_extract_bit_field_u32.listLength, 0xFFFF1FFF);
        }

#ifdef __DEBUG
        printf("\nInput List:\n");
        for(i = 0; i < gConfig_extract_bit_field_u32.listLength; i++) {
            printf("%6d, ", IN[i]);
            printf((i % 8 == 7) ? "\n" : "");
        }
        printf("\n");
#endif

        profiler_start();

#if VCOP_HOST_EMULATION
        vcop_extract_bit_field_u32(IN, gConfig_extract_bit_field_u32.listLength,
                                   gConfig_extract_bit_field_u32.bitMask,
                                   gConfig_extract_bit_field_u32.shift, OUT);
#else
        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                        IBUFHA_VCOP, IBUFLA_VCOP);

        /*---------------------------------------------------------------------*/
        /*  Function call to the VCOP-C API to be tested                       */
        /*---------------------------------------------------------------------*/
        vcop_extract_bit_field_u32_vloops(__pblock_vcop_extract_bit_field_u32);
        _vcop_vloop_done();

        VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                            IBUFHA_SYST, IBUFLA_SYST);
#endif

        profiler_end();

        /*---------------------------------------------------------------------*/
        /*  Compare the results of output arrays with expected output arrays.  */
        /*---------------------------------------------------------------------*/
        vcop_extract_bit_field_u32_cn(IN, gConfig_extract_bit_field_u32.listLength,
                                      gConfig_extract_bit_field_u32.bitMask,
                                      gConfig_extract_bit_field_u32.shift, OUT_REF);
        fail = memcmp(OUT, OUT_REF, gConfig_extract_bit_field_u32.listLength);

        if(fail != 0) {
            for(i = 0; i < gConfig_extract_bit_field_u32.listLength; i++) {
                if(OUT[i] != OUT_REF[i]) {
                    printf("\nOutput mismatch at %d, Output = %d, Expected = %d\n",
                           i, OUT[i], OUT_REF[i]);
                }
            }
        }

#ifdef __DEBUG
        printf("\nOutput List:\n");
        for(i = 0; i < gConfig_extract_bit_field_u32.listLength; i++) {
            printf("%3d, ",OUT[i]);
            printf((i % 16 == 15) ? "\n" : "");
        }
        printf("\n");

        printf("\nReference Output Frame:\n");
        for(i = 0; i < gConfig_extract_bit_field_u32.listLength; i++) {
            printf("%3d, ",OUT_REF[i]);
            printf((i % 16 == 15) ? "\n" : "");
        }
        printf("\n");
#endif

        fp_out = fopen((const char*)gConfig_extract_bit_field_u32.outList, "w");
        if(fp_out != NULL) {
            for(i = 0; i < gConfig_extract_bit_field_u32.listLength; i++) {
                fprintf(fp_out, "%3d, ",OUT[i]);
            }
            fclose(fp_out);
        }

        printf(fail ? "FAIL\n":"PASS\n");
        status |= fail;
    }

    profiler_deinit();

    printf(status ? "test_extract_bit_field_u32: FAIL\n":"test_extract_bit_field_u32: PASS\n");

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
      strcpy(configFile,"../testvecs/config/extract_bit_field_u32.cfg");
    }

    fillDefaultConfig(&gConfig_extract_bit_field_u32);
    status = readparamfile(configFile, &gsTokenMap_extract_bit_field_u32[0]) ;
    if(status == -1)
    {
        printf("Parser Failed");
        return -1 ;
    }

    /* Validate the Kernel */
    printf ("\nExtract Bit-field from uint32 Test Bench: Validating Kernel\n");
    status = test_extract_bit_field_u32();

    return status;
}
