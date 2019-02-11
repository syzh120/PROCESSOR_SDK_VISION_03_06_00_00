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
#include <stdlib.h>

#include <vcop.h>

#include "test_profile.h"

#if VCOP_HOST_EMULATION
  #include "vcop_vec_update_ewr_mean_s16_kernel.k"    // kernel source
#else
void vcop_vec_update_ewr_mean_s16
(
    __vptr_int16   currentMean,
    __vptr_uint8   newestData,
    __vptr_uint8   foreground,
    unsigned short weight,
    unsigned short weight_neg,
    unsigned int   frameSize
);
#endif

#define NUM_PIXELS   (32)
#define UPDATE_RATE  (0x10)

#pragma DATA_SECTION(newLuma, "Adata");
unsigned char newLuma[32]   =
{
    0x000, 0x001, 0x002, 0x003, 0x004, 0x005, 0x006, 0x007,
    0x008, 0x009, 0x00a, 0x00b, 0x00c, 0x00d, 0x00e, 0x00f,
    0x010, 0x011, 0x012, 0x013, 0x014, 0x015, 0x016, 0x017,
    0x018, 0x019, 0x01a, 0x01b, 0x01c, 0x01d, 0x01e, 0x01f
};

#pragma DATA_SECTION(mask32packed, "Bdata");
unsigned char mask32packed[16] = {0xC0,0x07,0xFF,0xFF};

#pragma DATA_SECTION(runningMean, "Cdata");
short runningMean[32] =
{
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 0x0800,
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000,
    0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x0000, 0x0000
};

#pragma DATA_SECTION(trueRunningMean, "EOutdata");
short trueRunningMean[32] =
{
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0800, 0x0800, 0x0800, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF,
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000,
    0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x0000, 0x0000
};


#pragma DATA_SECTION(profile_array, "Cdata");
unsigned int profile_array[2];

int main()
{
    int fail;
    int i;
#ifdef REPORT
#ifdef SCTM
    unsigned int sctm_t1, sctm_t2, exec_diff;
    unsigned int overflow;
#endif
    FILE* fpReport = fopen("../../../report.csv","a+");
#endif

    /*---------------------------------------------------------------------*/
    /*  Function call to the VCOP-C API to be tested                       */
    /*---------------------------------------------------------------------*/

#if VCOP_HOST_EMULATION
#else
    unsigned int t0, t1;
    _tsc_start();
#endif

    //For profiling, use 2 as loop counter
    for (i = 0; i < 1; i++)
    {
#if VCOP_HOST_EMULATION
#else
        t0 = _tsc_gettime();
#endif

    /*---------------------------------------------------------------------*/
    /*  Function call to the VCOP-C API to be tested                       */
    /*---------------------------------------------------------------------*/
#ifdef REPORT
#ifdef SCTM
         EVE_SCTM_Enable(CTM);
         EVE_SCTM_CounterConfig(CTM, SCTM_Counter_0, VCOP_BUSY, SCTM_DURATION);
         EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_0);
         sctm_t1 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
#endif
#endif

        vcop_vec_update_ewr_mean_s16(runningMean,newLuma,mask32packed,
                                     UPDATE_RATE,2^16-1-UPDATE_RATE,NUM_PIXELS);
#ifdef REPORT
#ifdef SCTM
        sctm_t2 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
        overflow = EVE_SCTM_OverflowCheck(CTM,SCTM_Counter_0);
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
    fail = memcmp (runningMean, trueRunningMean, NUM_PIXELS);

    /*---------------------------------------------------------------------*/
    /*  If there is a mis-compare, print out a memory trace, else print    */
    /*  pass.                                                              */
    /*---------------------------------------------------------------------*/
#ifdef REPORT
    fprintf(fpReport,"vcop_vec_update_ewr_mean_s16,");
    fprintf(fpReport,"%d,",NUM_PIXELS);
    fprintf(fpReport,"%d,",1);
    fprintf(fpReport,"%d,",NUM_PIXELS);
    fprintf(fpReport,"%d,",1);
    fprintf(fpReport,"%d,",1);
#endif

    if (fail)
    {
#ifdef CONSOLE
        for (i = 0; i < NUM_PIXELS; i++)
        {
             printf ("i:%d, out:%u, EOut:%u, %c \n",
                      i, runningMean[i], trueRunningMean[i],
                      (runningMean[i]!=trueRunningMean[i]) ? '*':' '
                    );
        }
#endif

#ifdef REPORT
        fprintf(fpReport,"FAIL,");
#endif
    }
    else {
#ifdef CONSOLE
        printf("Pass\n");
#endif
#ifdef REPORT
        fprintf(fpReport,"PASS,");
#endif
    }

#if VCOP_HOST_EMULATION
#else
#ifdef CONSOLE
    for(i = 0; i < 2; i++)
        printf("Time taken: %d cycles \n", profile_array[i]);
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
/*  End of file:  vcop_vec_update_ewr_mean_s16.c                            */
/*--------------------------------------------------------------------------*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
