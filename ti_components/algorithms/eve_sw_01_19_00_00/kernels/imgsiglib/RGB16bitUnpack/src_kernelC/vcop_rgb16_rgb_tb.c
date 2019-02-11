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

/*-----------------------------------------------------------------*/
/* NAME : vcop_rgb16_rgb : Test bench data                         */ 
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The function "vcop_rgb16_rgb" accepts packed 16-bit data in     */
/* the form of 8-bit "r", "g" and "b", and writes out seperate     */
/* 8-bit "r", 8-bit "g" and "b". The reason for having this        */
/* function, is to allow the vector core to work in it's           */
/* natural format of looking at similar data together, rather      */
/* than diverse data.                                              */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_rgb16_rgb                                             */
/* (                                                               */
/*     unsigned int   rgb16[],                                     */
/*     unsigned int   npixels,                                     */
/*     unsigned char  r[],                                         */
/*     unsigned char  g[],                                         */
/*     unsigned char  b[]                                          */
/* )                                                               */
/*                                                                 */
/* The function "vcop_rgb16_rgb" accepts packed 16-bit "r", "g"    */
/* and "b" data, for "npixels" pixels, and writing it into         */
/* seperate output buffers of "r", "g" and "b".                    */
/*                                                                 */
/*=================================================================*/


#include <stdio.h>
#include <vcop.h>

#include "test_profile.h"

typedef unsigned short Uint16;
typedef unsigned char  Uint8;

#define NUM_PIXELS   16

#pragma DATA_SECTION (rgb16, "Adata");
#pragma DATA_ALIGN(rgb16, 32);
unsigned short rgb16[NUM_PIXELS] =
{
    0x7F9A, 0x3DFF, 0x7F9F, 0x3DFA, 
    0x7F9A, 0x3DFF, 0x7F9F, 0x3DFA,
    0x7F9A, 0x3DFF, 0x7F9F, 0x3DFA,
    0x7F9A, 0x3DFF, 0x7F9F, 0x3DFA,
};

#pragma DATA_SECTION (r1, "Bdata");
unsigned char r1[NUM_PIXELS] = {0};

#pragma DATA_SECTION (g1, "Bdata");
unsigned char g1[NUM_PIXELS] = {0};

#pragma DATA_SECTION (b1, "Bdata");
unsigned char b1[NUM_PIXELS] = {0};

#pragma DATA_SECTION (Er1, "EOutdata");
unsigned char Er1[NUM_PIXELS] =
{
    0x1A, 0x1F, 0x1F, 0x1A, 0x1A, 0x1F, 0x1F, 0x1A,
    0x1A, 0x1F, 0x1F, 0x1A, 0x1A, 0x1F, 0x1F, 0x1A,
};

#pragma DATA_SECTION (Eg1, "EOutdata");
unsigned char Eg1[NUM_PIXELS] =
{
    0x1C, 0x0F, 0x1C, 0x0F, 0x1C, 0x0F, 0x1C, 0x0F,
    0x1C, 0x0F, 0x1C, 0x0F, 0x1C, 0x0F, 0x1C, 0x0F,
};

#pragma DATA_SECTION (Eb1, "EOutdata");
unsigned char Eb1[NUM_PIXELS] =
{
    0x1F, 0x0F, 0x1F, 0x0F, 0x1F, 0x0F, 0x1F, 0x0F,
    0x1F, 0x0F, 0x1F, 0x0F, 0x1F, 0x0F, 0x1F, 0x0F,
};

#pragma DATA_SECTION (r2, "Bdata");
unsigned char r2[NUM_PIXELS] = {0};

#pragma DATA_SECTION (g2, "Bdata");
unsigned char g2[NUM_PIXELS] = {0};

#pragma DATA_SECTION (b2, "Bdata");
unsigned char b2[NUM_PIXELS] = {0};

#pragma DATA_SECTION (Er2, "EOutdata");
unsigned char Er2[NUM_PIXELS] =
{
    0x1A, 0x1F, 0x1F, 0x1A, 0x1A, 0x1F, 0x1F, 0x1A,
    0x1A, 0x1F, 0x1F, 0x1A, 0x1A, 0x1F, 0x1F, 0x1A,
};

#pragma DATA_SECTION (Eg2, "EOutdata");
unsigned char Eg2[NUM_PIXELS] =
{
    0x3C, 0x2F, 0x3C, 0x2F, 0x3C, 0x2F, 0x3C, 0x2F,
    0x3C, 0x2F, 0x3C, 0x2F, 0x3C, 0x2F, 0x3C, 0x2F
};

#pragma DATA_SECTION (Eb2, "EOutdata");
unsigned char Eb2[NUM_PIXELS] =
{
    0x0F, 0x07, 0x0F, 0x07, 0x0F, 0x07, 0x0F, 0x07,
    0x0F, 0x07, 0x0F, 0x07, 0x0F, 0x07, 0x0F, 0x07,
};

#if VCOP_HOST_EMULATION
  #include "vcop_rgb16_rgb_kernel.k"           // kernel source
#else
  #include "../inc/vcop_rgb16_rgb_kernel.h"    // translated kernel
#endif

void print_output();
int  verify_output();

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

#ifdef REPORT
#ifdef SCTM
sctm_t1 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
#endif
#endif        
    vcop_rgb555_rgb
    (
        rgb16,
        NUM_PIXELS,
        r1,
        g1,
        b1
    );

    vcop_rgb565_rgb
    (
        rgb16,
        NUM_PIXELS,
        r2,
        g2,
        b2
    );
#ifdef REPORT	
#ifdef SCTM
sctm_t2 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
		overflow= EVE_SCTM_OverflowCheck(CTM,SCTM_Counter_0);
		assert(overflow!=1);

exec_diff = sctm_t2 - sctm_t1;		
EVE_SCTM_CounterTimerDisable(CTM, SCTM_Counter_0);
#endif			
#endif	

#ifdef CONSOLE
   print_output();
#endif
   
   ok = verify_output();
#ifdef CONSOLE 
   if (ok ) printf(ok ? "\n\nRGB 16-bit unpack to R, G, B planes -- Kernel-C code: PASS\n" : "FAIL\n"); 
#endif   

#ifdef REPORT
fprintf(fpReport,"vcop_rgb16bitUnPack,");
fprintf(fpReport,"%d,",NUM_PIXELS);
fprintf(fpReport,"%d,",1);
fprintf(fpReport,"%d,",NUM_PIXELS);
fprintf(fpReport,"%d,",1);
fprintf(fpReport,"1,");
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

void print_output()
{
   int i;

   printf("\n\n R - DATA  \n");
   for (i = 0; i < NUM_PIXELS; ++i)
   {
      printf("0x%2.2x, ", r1[i]); 
   }
 
   printf("\n\n G - DATA  \n");
   for (i = 0; i < NUM_PIXELS; ++i)
   {
      printf("0x%2.2x, ", g1[i]); 
   }

   printf("\n\n B - DATA  \n");
   for (i = 0; i < NUM_PIXELS; ++i)
   {
      printf("0x%2.2x, ", b1[i]); 
   }

   printf("\n\n R - DATA  \n");
   for (i = 0; i < NUM_PIXELS; ++i)
   {
      printf("0x%2.2x, ", r2[i]); 
   }
 
   printf("\n\n G - DATA  \n");
   for (i = 0; i < NUM_PIXELS; ++i)
   {
      printf("0x%2.2x, ", g2[i]); 
   }

   printf("\n\n B - DATA  \n");
   for (i = 0; i < NUM_PIXELS; ++i)
   {
      printf("0x%2.2x, ", b2[i]); 
   }

}

int verify_output()
{
   int ok = 1;
   int i;

   for (i = 0; i < NUM_PIXELS; ++i)
   {
      if (r1[i] != Er1[i])
          ok = 0;
   }
 
   for (i = 0; i < NUM_PIXELS; ++i)
   {
      if (g1[i] != Eg1[i])
          ok = 0;
   }

   for (i = 0; i < NUM_PIXELS; ++i)
   {
      if (b1[i] != Eb1[i])
          ok = 0;
   }

   for (i = 0; i < NUM_PIXELS; ++i)
   {
      if (r2[i] != Er2[i])
          ok = 0;
   }
 
   for (i = 0; i < NUM_PIXELS; ++i)
   {
      if (g2[i] != Eg2[i])
          ok = 0;
   }

   for (i = 0; i < NUM_PIXELS; ++i)
   {
      if (b2[i] != Eb2[i])
          ok = 0;
   }

  return (ok);

}

/*=================================================================*/
/* End of file: vcop_rgb16_rgb_tb.c                                */
/*-----------------------------------------------------------------*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/


