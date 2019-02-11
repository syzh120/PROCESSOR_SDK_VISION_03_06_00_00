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
/* NAME : vcop_white_balance.c                                */
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/*=================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <vcop.h>

#if VCOP_HOST_EMULATION
  #include "vcop_white_balance_kernel.k"  /* kernel source */
#else
  #include "vcop_white_balance_kernel.h" 
#endif

/*---------------------------------------------------------------------------*/
/*Input image dimensions*/
/*---------------------------------------------------------------------------*/
#define INPUT_IMG_WIDTH   32
#define INPUT_IMG_HEIGHT  8

/*---------------------------------------------------------------------------*/
/*Input block dimensions*/
/*IMPORTANT!! BLK_WIDTH should be a multiple of 16*/
/*---------------------------------------------------------------------------*/
#define BLK_WIDTH    16
#define BLK_HEIGHT   8

#define INPUT_STRIDE  INPUT_IMG_WIDTH
#define OUTPUT_STRIDE INPUT_IMG_WIDTH

/*---------------------------------------------------------------------------*/
/*Gain factors for white balance*/
/*---------------------------------------------------------------------------*/
#define GAIN_FACTOR_R  256
#define GAIN_FACTOR_Gb 256
#define GAIN_FACTOR_Gr 256
#define GAIN_FACTOR_B  256

/*---------------------------------------------------------------------------*/
/*shift value for white balance*/
/*---------------------------------------------------------------------------*/
#define SHIFT_VAL      8

/*---------------------------------------------------------------------------*/
/*input image buffer*/
/*---------------------------------------------------------------------------*/
#pragma DATA_SECTION (CFA_short, "Adata");
unsigned short CFA_short[INPUT_IMG_WIDTH * INPUT_IMG_HEIGHT] =
{
  0x01fd,0x028c,0x020f,0x025c,0x0251,0x0322,0x025a,0x031c,0x023c,0x02b9,0x0205,0x02fc,0x01f6,0x026b,0x0203,0x0293,
  0x01e9,0x0283,0x0224,0x02b7,0x0214,0x02c6,0x0206,0x02a4,0x0224,0x02aa,0x0228,0x02c3,0x0275,0x031a,0x027f,0x033b,
  
  0x0269,0x01c7,0x0291,0x01df,0x02f8,0x022c,0x02f5,0x0246,0x02c7,0x01d9,0x025d,0x0231,0x0282,0x01cb,0x029b,0x01cc,
  0x027c,0x01dc,0x02bd,0x01fe,0x02b4,0x020a,0x02b4,0x01f8,0x02a4,0x01f6,0x02db,0x01f4,0x0324,0x023f,0x0360,0x0258,
  
  0x020b,0x028a,0x021c,0x02bf,0x0226,0x02b9,0x01eb,0x0276,0x0229,0x0308,0x0255,0x02e2,0x01f7,0x028d,0x01eb,0x029a,
  0x0290,0x0350,0x023e,0x0317,0x0289,0x0305,0x01c8,0x0259,0x0238,0x02ec,0x0262,0x02e2,0x020b,0x0283,0x024f,0x02d0,
  
  0x0281,0x01ce,0x02d4,0x0219,0x02e1,0x020f,0x025a,0x01d9,0x02d7,0x025e,0x02d7,0x01f6,0x02bf,0x01ea,0x02a0,0x0201,
  0x039d,0x027f,0x02ec,0x0210,0x0337,0x01fc,0x0242,0x01cc,0x02df,0x021f,0x0308,0x0232,0x02b7,0x0203,0x0301,0x0212,
  
  0x020b,0x028a,0x0229,0x02ad,0x0216,0x02af,0x01e1,0x0296,0x0230,0x02b7,0x01cd,0x0270,0x021c,0x02a3,0x01e9,0x025e,
  0x0230,0x02c6,0x0244,0x02f3,0x024e,0x0313,0x0249,0x02df,0x0226,0x02be,0x021b,0x0256,0x021a,0x02f5,0x0207,0x02bd,
  
  0x02b1,0x01e3,0x02e4,0x0225,0x02a4,0x01ea,0x0278,0x01f0,0x02b6,0x01e6,0x0260,0x01d7,0x02bf,0x01f4,0x028b,0x01c5,
  0x02aa,0x021a,0x02d1,0x022d,0x02c5,0x0216,0x02c9,0x0216,0x02c6,0x022e,0x02b1,0x01c2,0x02d0,0x0256,0x02a2,0x0210,
  
  0x01bc,0x025a,0x01f1,0x0290,0x0246,0x02d7,0x0208,0x02b2,0x0213,0x02c3,0x01e6,0x02a4,0x020a,0x02b9,0x0231,0x02db,
  0x0226,0x02e3,0x0210,0x02d0,0x022e,0x02b8,0x01e2,0x026d,0x01f0,0x025e,0x0211,0x02aa,0x0223,0x02c4,0x021c,0x02c5,
  
  0x0287,0x01b9,0x0285,0x01d7,0x030e,0x0233,0x0296,0x0209,0x02c5,0x01f8,0x02b0,0x01fe,0x02a6,0x020b,0x02cf,0x021b,
  0x02c7,0x0226,0x027a,0x01fe,0x02b5,0x01fe,0x025f,0x01cc,0x0288,0x01d0,0x02a2,0x021c,0x02c0,0x0202,0x029c,0x01ec,
};

/*---------------------------------------------------------------------------*/
/*output image buffer*/
/*---------------------------------------------------------------------------*/
#pragma DATA_SECTION(CFA_short_out, "Cdata");
#pragma DATA_ALIGN(CFA_short_out, 32);
unsigned short CFA_short_out[BLK_WIDTH * BLK_HEIGHT] =
{
 0
};

/*---------------------------------------------------------------------------*/
/*Reference output image buffer*/
/*---------------------------------------------------------------------------*/
#pragma DATA_SECTION (Ref_CFA_short_out, "Adata");
unsigned short Ref_CFA_short_out[BLK_WIDTH * BLK_HEIGHT] =
{
  0x01fd,0x028c,0x020f,0x025c,0x0251,0x0322,0x025a,0x031c,0x023c,0x02b9,0x0205,0x02fc,0x01f6,0x026b,0x0203,0x0293,
  0x0269,0x01c7,0x0291,0x01df,0x02f8,0x022c,0x02f5,0x0246,0x02c7,0x01d9,0x025d,0x0231,0x0282,0x01cb,0x029b,0x01cc,
  0x020b,0x028a,0x021c,0x02bf,0x0226,0x02b9,0x01eb,0x0276,0x0229,0x0308,0x0255,0x02e2,0x01f7,0x028d,0x01eb,0x029a,
  0x0281,0x01ce,0x02d4,0x0219,0x02e1,0x020f,0x025a,0x01d9,0x02d7,0x025e,0x02d7,0x01f6,0x02bf,0x01ea,0x02a0,0x0201,
  0x020b,0x028a,0x0229,0x02ad,0x0216,0x02af,0x01e1,0x0296,0x0230,0x02b7,0x01cd,0x0270,0x021c,0x02a3,0x01e9,0x025e,
  0x02b1,0x01e3,0x02e4,0x0225,0x02a4,0x01ea,0x0278,0x01f0,0x02b6,0x01e6,0x0260,0x01d7,0x02bf,0x01f4,0x028b,0x01c5,
  0x01bc,0x025a,0x01f1,0x0290,0x0246,0x02d7,0x0208,0x02b2,0x0213,0x02c3,0x01e6,0x02a4,0x020a,0x02b9,0x0231,0x02db,
  0x0287,0x01b9,0x0285,0x01d7,0x030e,0x0233,0x0296,0x0209,0x02c5,0x01f8,0x02b0,0x01fe,0x02a6,0x020b,0x02cf,0x021b
};

void print_output(
unsigned short *buffer,
unsigned int blk_height,
unsigned int blk_width
);

unsigned int verify_output
(
unsigned short *output,
unsigned short *output_ref,
unsigned int blk_height,
unsigned int blk_width
);

int main()
{
    unsigned int status = 0;

    vcop_white_balance_BGGR(CFA_short,
                            CFA_short_out, 
                            BLK_WIDTH,
                            BLK_HEIGHT,
                            GAIN_FACTOR_R,
                            GAIN_FACTOR_Gr,
                            GAIN_FACTOR_Gb,
                            GAIN_FACTOR_B,
                            SHIFT_VAL,
                            INPUT_STRIDE,
                            OUTPUT_STRIDE
                            );


   status = verify_output(CFA_short_out,Ref_CFA_short_out,BLK_HEIGHT,BLK_WIDTH);
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
     print_output(CFA_short_out,INPUT_IMG_HEIGHT,INPUT_IMG_WIDTH);
   }
   
  printf("Done!!!\n");
  return 0;
}

unsigned int verify_output
(
unsigned short *output,
unsigned short *output_ref,
unsigned int blk_height,
unsigned int blk_width
)
{
  unsigned int i, j;
  unsigned int status = 1;

  for(i = 0; i<blk_height; ++i)
  {
    for( j = 0; j<blk_width; j++)
    {
      if((output[(i * OUTPUT_STRIDE) + j]) != (output_ref[(i * blk_width) + j]))
      {
        status = 0;
      }
    }
  }

return(status);
}

void print_output
(
unsigned short *buffer,
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
