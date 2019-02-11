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
/* NAME : vcop_image_interleave.c                                */
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/*=================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <vcop.h>

#if VCOP_HOST_EMULATION
#include "vcop_image_pyramid_uv_u8_kernel.k"  /* kernel source */
#endif

/*---------------------------------------------------------------------------*/
/*Input block dimensions*/
/*IMPORTANT!! BLK_WIDTH should be a multiple of 16*/
/*---------------------------------------------------------------------------*/
#define BLK_WIDTH    16
#define BLK_HEIGHT   8

/*---------------------------------------------------------------------------*/
/*input image buffer*/
/*---------------------------------------------------------------------------*/
#pragma DATA_SECTION (input_blk, "Adata");
unsigned char input_blk[BLK_WIDTH * BLK_HEIGHT] =
{
  0xA1,0x21,0xA2,0x22,0xA3,0x23,0xA4,0x24,0xA5,0x25,0xA6,0x26,0xA7,0x27,0xA8,0x28,
  0xB1,0x31,0xB2,0x32,0xB3,0x33,0xB4,0x34,0xB5,0x35,0xB6,0x36,0xB7,0x37,0xB8,0x38,
  0xC1,0x41,0xC2,0x42,0xC3,0x43,0xC4,0x44,0xC5,0x45,0xC6,0x46,0xC7,0x47,0xC8,0x48,
  0xD1,0x51,0xD2,0x52,0xD3,0x53,0xD4,0x54,0xD5,0x55,0xD6,0x56,0xD7,0x57,0xD8,0x58,
  0xE1,0x61,0xE2,0x62,0xE3,0x63,0xE4,0x64,0xE5,0x65,0xE6,0x66,0xE7,0x67,0xE8,0x68,
  0xF1,0x71,0xF2,0x72,0xF3,0x73,0xF4,0x74,0xF5,0x75,0xF6,0x76,0xF7,0x77,0xF8,0x78,
  0x11,0x81,0x12,0x82,0x13,0x83,0x14,0x84,0x15,0x85,0x16,0x86,0x17,0x87,0x18,0x88,
  0x01,0x91,0x02,0x92,0x03,0x93,0x04,0x94,0x05,0x95,0x06,0x96,0x07,0x97,0x08,0x98
};

/*---------------------------------------------------------------------------*/
/*output image buffer*/
/*---------------------------------------------------------------------------*/
#pragma DATA_SECTION(output_blk, "Cdata");
#pragma DATA_ALIGN(output_blk, 32);
unsigned char output_blk[(BLK_WIDTH/2) * (BLK_HEIGHT/2)] =
{
  0
};

/*---------------------------------------------------------------------------*/
/*Reference output image buffer*/
/*---------------------------------------------------------------------------*/
#pragma DATA_SECTION (ref_output_blk, "Adata");
unsigned char ref_output_blk[(BLK_WIDTH/2) * (BLK_HEIGHT/2)] =
{
  0xAA,0x2A,0xAC,0x2C,0xAE,0x2E,0xB0,0x30,
  0xCA,0x4A,0xCC,0x4C,0xCE,0x4E,0xD0,0x50,
  0xEA,0x6A,0xEC,0x6C,0xEE,0x6E,0xF0,0x70,
  0x0A,0x8A,0x0C,0x8C,0x0E,0x8E,0x10,0x90
};


void print_output
(
  unsigned char *buffer,
  unsigned int   blk_height,
  unsigned int   blk_width
);

unsigned int verify_output
(
unsigned char *output,
unsigned char *output_ref,
unsigned int   blk_height,
unsigned int   blk_width
);

int main()
{
    unsigned int status = 0;
    
    vcop_image_pyramid_uv_u8(input_blk,
                            BLK_WIDTH,
                            BLK_HEIGHT,
                            output_blk
                            );

   status = verify_output(output_blk,ref_output_blk,BLK_HEIGHT/2,BLK_WIDTH/2);
   if(status)
   {
     printf("PASS: bit match \n");
   }
   else
   {
     printf("FAIL: not bit match \n");
     /*---------------------------------------------------------------------*/
     /*  If there is a mismatch, print out a memory trace*/
     /*---------------------------------------------------------------------*/
     print_output(output_blk,BLK_HEIGHT,BLK_WIDTH/2);
   }
   
  printf("Done!!!\n");
  return 0;
}

unsigned int verify_output
(
unsigned char *output,
unsigned char *output_ref,
unsigned int   blk_height,
unsigned int   blk_width
)
{
  unsigned int i, j;
  unsigned int status = 1;

  for(i = 0; i<blk_height; ++i)
  {
    for( j = 0; j<blk_width; j++)
    {
      if((output[(i * blk_width) + j]) != (output_ref[(i * blk_width) + j]))
      {
        status = 0;
      }
    }
  }

return(status);
}

void print_output
(
unsigned char *buffer,
unsigned int blk_height,
unsigned int blk_width
)
{
  unsigned int i,j;

  for(i = 0; i<blk_height; ++i)
  {
    for(j = 0; j<blk_width; j++)
    {
      printf("%4x, ",buffer[(i * blk_width) + j]);
    }
    printf("\n");
  }
}
