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
/* NAME : vcop_rgb24_rgb : Test bench data.                        */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The function "vcop_rgb24_rgb" accepts packed 24-bit data in     */
/* the form of 8-bit "r", "g" and "b", and writes out seperate     */
/* 8-bit "r", 8-bit "g" and "b". The reason for having this        */
/* function, is to allow the vector core to work in it's           */
/* natural format of looking at similar data together, rather      */
/* than diverse data.                                              */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_rgb24_rgb                                             */
/* (                                                               */
/*     unsigned int   rgb24[],                                     */
/*     unsigned int   npixels,                                     */
/*     unsigned char  r[],                                         */
/*     unsigned char  g[],                                         */
/*     unsigned char  b[]                                          */
/* )                                                               */
/*                                                                 */
/* The function "vcop_rgb24_rgb" accepts packed 24-bit "r", "g"    */
/* and "b" data, for "npixels" pixels, and writing it into         */
/* seperate output buffers of "r", "g" and "b". Since we are       */
/* packing 24-bit pixels in 32-bit memory, the actual size of      */
/* the input buffer "rgb24" is (3 * npixels) >> 2 and each of      */
/* the output buffers "r", "g" and "b" are of size "npixels".      */
/*                                                                 */
/*=================================================================*/
/*-----------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "vcop.h"

#define true    1
#define false   0


#if VCOP_HOST_EMULATION
  #include "vcop_rgb24_rgb_kernel.k"    // kernel source
#else
  void vcop_rgb24_rgb
  (
      __vptr_uint32  rgb24,
      __vptr_int8    rgbmask,
      unsigned int   npixels,
      __vptr_uint8   r,
      __vptr_uint8   g,
      __vptr_uint8   b 
  );

#endif


#define NUM_PIXELS 24

#pragma DATA_SECTION (rgb24, "Adata");
unsigned int rgb24[((3 * NUM_PIXELS) >> 2)] =
{
    0x02030201, 0x04030403, 0x06050405, 0x06070605,
    0x08070807, 0x0A090809, 0x0A0B0A09, 0x0C0B0C0B,
    0x0E0D0C0D, 0x0E0F0E0D, 0x100F100F, 0x12111011,
    0x12131211, 0x14131413, 0x16151415, 0x16171615,
    0x18171817, 0x1A191819
};

#pragma DATA_SECTION (rgb_s, "Bdata");
char rgb_s[24] =
{
   -0,  -24, -16,  -8,  -0, -24, -16,   -8,
   -8,  -0,  -24, -16,  -8,  -0, -24,  -16,
  -16,  -8,   -0, -24, -16,  -8,  -0,  -24
};

#pragma DATA_SECTION (r, "Cdata");
#pragma DATA_SECTION (g, "Cdata");
#pragma DATA_SECTION (b, "Cdata");

unsigned char r[NUM_PIXELS] = {0};
unsigned char g[NUM_PIXELS] = {0};
unsigned char b[NUM_PIXELS] = {0};

unsigned char Er[NUM_PIXELS] =
{
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
    0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18
};

unsigned char Eg[NUM_PIXELS] =
{
    0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
    0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 
    0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19
};

unsigned char Eb[NUM_PIXELS] =
{
    0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 
    0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 
    0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A
};



int main()
{
    int i;
    
    vcop_rgb24_rgb
    (
        rgb24,
        rgb_s,
        NUM_PIXELS,
        r,
        g,
        b
    );


    for ( i = 0; i < NUM_PIXELS; i++)
    printf ("r:0x%.2x, g:0x%.2x, b:0x%.2x \n",
             (r[i] & 0xFF), (g[i] & 0xFF), (b[i] & 0xFF)
           );

   if 
   (
       (memcmp (r, Er, sizeof(r)))
    || (memcmp (g, Eg, sizeof(g)))
    || (memcmp (b, Eb, sizeof(b)))
   )
   printf ("Fail \n");
   else
   printf ("Pass \n");
}

/*=================================================================*/
/* End of file: vcop_rgb24_rgb_tb.c                                */
/*-----------------------------------------------------------------*/
/*-----------------------------------------------------------------*/


