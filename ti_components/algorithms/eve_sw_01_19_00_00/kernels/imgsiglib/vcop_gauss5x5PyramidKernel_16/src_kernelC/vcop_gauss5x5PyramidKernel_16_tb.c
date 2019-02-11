/*
*
* Copyright (c) 2010-2017 Texas Instruments Incorporated
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
#include <string.h>
#include <vcop.h>

#include "test_profile.h"

#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))

#define BLOCK_PITCH   (16)
#define BLOCK_WIDTH   (16-4)
#define BLOCK_HEIGHT  (2)

#if VCOP_HOST_EMULATION
  #include "vcop_gauss5x5PyramidKernel_16_kernel.k"  // kernel source
#else
void vcop_gauss5x5PyramidKernel_16_horiz
(
    __vptr_uint16   pIn,
    __vptr_uint16   pOut,
    unsigned short width,
    unsigned short height,
    unsigned short inPitch,
    unsigned short outPitch
);

void vcop_gauss5x5PyramidKernel_16_vert
(
    __vptr_uint16   pIn,
    __vptr_uint16   pOut,
    unsigned short width,
    unsigned short height,
    unsigned short inPitch,
    unsigned short outPitch
);
#endif

void vcop_gauss5x5PyramidKernel_16
(
    unsigned short pIn[],
    unsigned short pB[],
    unsigned short width,
    unsigned short pitch,
    unsigned short height,
    unsigned short pOut[]
)
{

    /*---------------------------------------------------------------------*/
    /*  Function call to the VCOP-C APIs to be tested                      */
    /*---------------------------------------------------------------------*/

vcop_gauss5x5PyramidKernel_16_horiz
(
    pIn,
    pB,
    width,
    height+4,
    pitch,
    ALIGN_SIMD(width)/2
);

vcop_gauss5x5PyramidKernel_16_vert
(
    pB,
    pOut,
    width/2,
    height,
    ALIGN_SIMD(width)/2,
    width/2
);

}

#pragma DATA_SECTION(InData_Gauss5x5PyramidKernel_16, "Adata");
unsigned short InData_Gauss5x5PyramidKernel_16[16*5] =
{
    0x0097, 0x0039, 0x0074, 0x00aa, 0x0009, 0x00f7, 0x00d0, 0x008c,
    0x0096, 0x003c, 0x0058, 0x004d, 0x0004, 0x0006, 0x00a2, 0x0006,
    0x001f, 0x008f, 0x00b2, 0x0003, 0x0087, 0x005b, 0x0036, 0x009a,
    0x00c1, 0x00a1, 0x0014, 0x00a2, 0x0089, 0x0096, 0x0080, 0x00e0,
    0x00d6, 0x0071, 0x0009, 0x001c, 0x0035, 0x00d3, 0x0062, 0x00d9,
    0x0095, 0x00e9, 0x00e7, 0x007f, 0x0073, 0x00cb, 0x00b1, 0x002a,
    0x003e, 0x009b, 0x0003, 0x0067, 0x007f, 0x0010, 0x0087, 0x0083,
    0x00d3, 0x009e, 0x0009, 0x0002, 0x006a, 0x00e3, 0x00f9, 0x00ff,
    0x0097, 0x0039, 0x0074, 0x00aa, 0x0009, 0x00f7, 0x00d0, 0x008c,
    0x0096, 0x003c, 0x0058, 0x004d, 0x0004, 0x0006, 0x00a2, 0x0006
};

#pragma DATA_SECTION(Temp_Gauss5x5PyramidKernel_16, "Bdata");
unsigned short Temp_Gauss5x5PyramidKernel_16[16*5];

#pragma DATA_SECTION(trueOutData_Gauss5x5PyramidKernel_16, "EOutdata");
unsigned short trueOutData_Gauss5x5PyramidKernel_16[2*6] =
{
    0x0051, 0x005b, 0x0086, 0x00a4, 0x007c, 0x007c
};

#pragma DATA_SECTION(calculatedOutData_Gauss5x5PyramidKernel_16, "Cdata");
unsigned short calculatedOutData_Gauss5x5PyramidKernel_16[2*6];

#pragma DATA_SECTION(profile_array, "Cdata");
unsigned int profile_array[2];

int main()
{

    int i, fail;
#ifdef REPORT
#ifdef SCTM
    unsigned int sctm_t1, sctm_t2, exec_diff;
    unsigned int overflow;
#endif
    FILE* fpReport = fopen("../../../report.csv","a+");
#endif

    /*---------------------------------------------------------------------*/
    /*  Wrapper to use the VCOP-C API to call horiz and vert filters       */
    /*---------------------------------------------------------------------*/

#if VCOP_HOST_EMULATION
#else
    unsigned int t0, t1;
    _tsc_start();
#endif

   for (i = 0; i < 2; i++)
   {
#if VCOP_HOST_EMULATION
#else
    t0 = _tsc_gettime();
#endif

#ifdef REPORT
#ifdef SCTM
    EVE_SCTM_Enable(CTM);
    EVE_SCTM_CounterConfig(CTM, SCTM_Counter_0, VCOP_BUSY, SCTM_DURATION);
    EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_0);
    sctm_t1 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
#endif
#endif
    vcop_gauss5x5PyramidKernel_16(InData_Gauss5x5PyramidKernel_16,
                                 Temp_Gauss5x5PyramidKernel_16,
                                 BLOCK_WIDTH,
                                 BLOCK_PITCH,
                                 BLOCK_HEIGHT,
                                 calculatedOutData_Gauss5x5PyramidKernel_16);

#ifdef REPORT
#ifdef SCTM
    sctm_t2 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
    overflow= EVE_SCTM_OverflowCheck(CTM,SCTM_Counter_0);
    assert(overflow!=1);

    exec_diff = sctm_t2 - sctm_t1;
    EVE_SCTM_CounterTimerDisable(CTM, SCTM_Counter_0);
#endif
#endif

#if VCOP_HOST_EMULATION
#else
        t1 = _tsc_gettime();
        profile_array[i]  = (t1 - t0);
#endif
    }

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/
    fail = memcmp (calculatedOutData_Gauss5x5PyramidKernel_16,
                                   trueOutData_Gauss5x5PyramidKernel_16, 6);

    /*---------------------------------------------------------------------*/
    /*  If there is a mis-compare, print out a memory trace, else print    */
    /*  pass.                                                              */
    /*---------------------------------------------------------------------*/
#ifdef REPORT
    fprintf(fpReport,"vcop_gauss5x5PyramidKernel_16,");
    fprintf(fpReport,"%d,",BLOCK_WIDTH);
    fprintf(fpReport,"%d,",BLOCK_HEIGHT);
    fprintf(fpReport,"%d,",BLOCK_WIDTH);
    fprintf(fpReport,"%d,",BLOCK_HEIGHT);
    fprintf(fpReport,"1,");
#endif

    if (fail)
    {
#ifdef CONSOLE
        for (i = 0; i < 6; i++)
        {
             printf("i:%d, out:%u, EOut:%u, %c \n",
                   i,
                   calculatedOutData_Gauss5x5PyramidKernel_16[i],
                   trueOutData_Gauss5x5PyramidKernel_16[i],
                   (calculatedOutData_Gauss5x5PyramidKernel_16[i]!=
                   trueOutData_Gauss5x5PyramidKernel_16[i])
                   ? '*':' '
                   );
        }
#endif

#ifdef REPORT
        fprintf(fpReport,"FAIL,");
#endif
    }
    else{
#ifdef REPORT
        fprintf(fpReport,"PASS,");
#endif

#ifdef CONSOLE
        printf ("Pass\n");
#endif
    }

#if VCOP_HOST_EMULATION
#else
#ifdef CONSOLE
    for (i = 0; i < 2; i++)
        printf ("Time taken: %d cycles \n", profile_array[i]);
#endif
#endif

#ifdef REPORT
#ifdef SCTM
    fprintf(fpReport,"%d\n",exec_diff);
#endif

    if(fpReport){
        fclose(fpReport);
    }
#endif
}

/* ======================================================================== */
/*  End of file:  vcop_gauss5x5PyramidKernel_16.c                           */
/*--------------------------------------------------------------------------*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
