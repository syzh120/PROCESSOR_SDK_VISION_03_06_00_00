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
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <vcop.h>
#ifdef __ARP32__
#include "GlobalTypes.h"
#include "baseaddress.h"
#include "pcache.h"
#include "sctm.h"
#define SCTM
#include "test_profile.h"
#endif

#include <assert.h>

#define REPORT

typedef unsigned char  Uint8;
typedef unsigned short Uint16;
typedef unsigned int   Uint32;

typedef char    Int8;
typedef short   Int16;
typedef int     Int32;

#define   BLK_W       64
#define   BLK_H       32

#define   IN_W        (BLK_W + 6)
#define   IN_H        (BLK_H + 6)


#define   OUT_W       ((BLK_W/2)+2)        // OUT_W >= 2 AND a multiple of 8
#define   OUT_H       ((BLK_H/2)+2)

#define   N0           (IN_W  * IN_H )
#define   N1           (OUT_W * OUT_H )

#define   INPUT_TYPE        0   // 0 - uchar, 1 - char, 2 - ushort, 3 - short

#pragma DATA_SECTION(in_data, "Adata");
Uint8 in_data[2*N0];

#pragma DATA_SECTION(out_cn, "EOutdata");
Uint16 out_cn[N1];

#pragma DATA_SECTION(out, "Bdata");
Uint16 out[N1];

#if VCOP_HOST_EMULATION
  #include "../src_kernelC/vcop_blockAverage2x2_kernel.k"    // kernel source
#else
  #include "../inc/vcop_blockAverage2x2_kernel.h"    // translated kernel
#endif

#include "../inc/vcop_blockAverage2x2_cn.h"

void randomize_byte(Uint8 ptr[], int npts, int max_val);
int my_memcmp (short t_ptrn1_c[], short t_ptrn1_i[], int start_x, int stop_x);

int main()
{
    int ok;
#ifdef REPORT
FILE* fpReport = fopen("../../../report.csv","a+");
#ifdef SCTM
unsigned int sctm_t1, sctm_t2, exec_diff;
unsigned int overflow;
EVE_SCTM_Enable(CTM);
EVE_SCTM_CounterConfig(CTM, SCTM_Counter_0, VCOP_BUSY, SCTM_DURATION);
EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_0);
#endif
#endif

    randomize_byte(in_data, sizeof(in_data), 255);
    memset(out, 0, sizeof(out));
    memset(out_cn, 0, sizeof(out_cn));

    /*-------------------------------------------------------------------*/
    /* Actual filtering operation happens here as part of the test bench */
    /* and the results are written out so as to be compared with EVE     */
    /* results.                                                          */
    /*-------------------------------------------------------------------*/

#ifdef REPORT
#ifdef SCTM
sctm_t1 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
#endif
#endif
    if ( INPUT_TYPE == 0)
    {
        vcop_blockAverage2x2_uchar
        (
            (Uint8 *)in_data,
            (Uint8 *)out,
            IN_W,
            OUT_W,
            BLK_W,
            BLK_H
        );

        vcop_blockAverage2x2_uchar_cn
        (
                (Uint8 *)in_data,
                (Uint8 *)out_cn,
                IN_W,
                OUT_W,
                BLK_W,
                BLK_H
        );

        ok= !(my_memcmp ((Int16*)out, (Int16*)out_cn, 0, N1/2));
    }

    if ( INPUT_TYPE == 1)
    {
        vcop_blockAverage2x2_char
        (
            (Int8 *)in_data,
            (Int8 *)out,
            IN_W,
            OUT_W,
            BLK_W,
            BLK_H
        );

        vcop_blockAverage2x2_char_cn
        (
                (Int8 *)in_data,
                (Int8 *)out_cn,
                IN_W,
                OUT_W,
                BLK_W,
                BLK_H
        );
    }

    if ( INPUT_TYPE == 2)
    {
        vcop_blockAverage2x2_ushort
        (
            (Uint16 *)in_data,
            (Uint16*)out,
            IN_W,
            OUT_W,
            BLK_W,
            BLK_H
        );

        vcop_blockAverage2x2_ushort_cn
        (
                (Uint16 *)in_data,
                (Uint16*)out_cn,
                IN_W,
                OUT_W,
                BLK_W,
                BLK_H
        );
    }

    if ( INPUT_TYPE == 3)
    {
        vcop_blockAverage2x2_short
        (
            (Int16 *)in_data,
            (Int16 *)out,
            IN_W,
            OUT_W,
            BLK_W,
            BLK_H
        );

        vcop_blockAverage2x2_short_cn
        (
                (Int16 *)in_data,
                (Int16 *)out_cn,
                IN_W,
                OUT_W,
                BLK_W,
                BLK_H
        );
    }
#ifdef REPORT
#ifdef SCTM
sctm_t2 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
		overflow= EVE_SCTM_OverflowCheck(CTM,SCTM_Counter_0);
		assert(overflow!=1);

exec_diff = sctm_t2 - sctm_t1;
EVE_SCTM_CounterTimerDisable(CTM, SCTM_Counter_0);
#endif
#endif
#ifdef REPORT
fprintf(fpReport,"vcop_blockAverage2x2,");
fprintf(fpReport,"%d,",IN_W);
fprintf(fpReport,"%d,",IN_H);
fprintf(fpReport,"%d,",BLK_W);
fprintf(fpReport,"%d,",BLK_H);
fprintf(fpReport,"1,");
#endif
    /*-------------------------------------------------------------------*/
    /* Print out the results here.                                       */
    /*-------------------------------------------------------------------*/

#ifdef CONSOLE
#ifdef REPORT
#ifdef SCTM

   if (ok)
       printf(" \n\n ***** BLK AVERAGE 2x2-- Kernel-C -code: PASSED! %2.2f VCOP cyc/point *****\n\n", 2.0*exec_diff/(BLK_W*BLK_H));
   else
       printf(" \n\n ***** BLK AVERAGE 2x2-- FAIL! %2.2f VCOP cyc/point ****\n\n", 2.0*exec_diff/(BLK_W*BLK_H));
#endif
#endif
#endif
#ifdef REPORT
if(ok){
fprintf(fpReport,"PASS,");
}
else{
fprintf(fpReport,"FAIL,");
}
#ifdef SCTM
fprintf(fpReport,"%d\n",exec_diff);
#endif
if(fpReport){
fclose(fpReport);
}
#endif

return 0;
}



void randomize_byte(Uint8 ptr[], int npts, int max_val) {
    int i;
    short val;

    for (i = 0; i < npts; i++) {
        val = abs((rand() % (max_val)));

        assert(val < max_val);
        assert(val >= 0);

        ptr[i] = val;
    }
}

int my_memcmp (short t_ptrn1_c[], short t_ptrn1_i[], int start_x, int stop_x)
{
    int i;
    int fail = 0;

    for (i = start_x; i < stop_x; i++)
    {
   if (t_ptrn1_c[i] != t_ptrn1_i[i])
   {
#ifdef CONSOLE
               printf("ERROR out = %d, ref = %d,  *\n", t_ptrn1_c[i], t_ptrn1_i[i]);
#endif
      fail  = 1;
   }

    }

    return (fail);
}
