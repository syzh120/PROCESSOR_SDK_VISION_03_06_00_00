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
/* NAME : vcop_BayerCFA_interpolate.c                                */
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The "vcop_image_bayer2rgb" code accepts    */
/* in the form of 8 or 16-bit Bayer Pattern, and writes out        */
/* the result as separate R, G and B planes. The output is         */
/* interpolated data to match the input width and height.          */
/* Interpolation is carried out by averaging the left and right    */
/* pixels, or the top and bottom pixels as the case may be.        */
/* In some cases, all four of the top-bottom-left-right pixels are */
/* used to compute the center pixel value.                         */
/*                                                                 */
/* The Bayer pattern is as follows:                                */
/* -------------------------------                                 */
/* B G B G B G B G                                                 */
/* G R G R G R G R                                                 */
/* B G B G B G B G                                                 */
/* G R G R G R G R                                                 */
/* B G B G B G B G                                                 */
/* G R G R G R G R                                                 */
/*                                                                 */
/* After demosiacing or deinterleaving step we get:                */
/* ------------------------------------------------                */
/* B  bx B  bx B  bx  B                                            */
/* by bz by bz by bz  by                                           */
/* B  bx B  bx B  bx  B                                            */
/* by bz by bz by bz  by                                           */
/*                                                                 */
/* rz ry rz ry rz  ry ry                                           */
/* rx R  rx R  rx  R  R                                            */
/* rz ry rz ry rz  ry ry                                           */
/* rx R  rx R  rx  R  R                                            */
/*                                                                 */
/* gy G gy  G  gy G  gy                                            */
/* G  gx G  gx G  gx  G                                            */
/* gy G gy  G  gy G  gy                                            */
/* G  gx G  gx G  gx  G                                            */
/*                                                                 */
/* At this stage, bx, by, bz, rx, ry, rz, gx, gy are zeros.        */
/*                                                                 */
/* After interpolating we get:                                     */
/* ---------------------------                                     */
/* Where bx = (Bleft + Bright)/2                                   */
/* Where by = (Btop  + Bbottom)/2                                  */
/* Where bz = (Bleft + Bright + Btop + Bbottom)/4                  */
/*                                                                 */
/* Where rx = (Rleft + Rright)/2                                   */
/* Where ry = (Rtop  + Rbottom)/2                                  */
/* Where rz = (Rleft + Rright + Rtop + Rbottom)/4                  */
/*                                                                 */
/* Where gx = (Gleft + Gright)/2                                   */
/* Where gy = (Gtop  + Gbottom)/2                                  */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_BayerCFA_Interpolate_char                             */
/* (                                                               */
/*     __vptr_uint8   CFA_char,                                    */
/*     unsigned int   blk_w,                                       */
/*     unsigned int   blk_h,                                       */
/*     __vptr_uint8   R_char,                                      */
/*     __vptr_uint8   G_char,                                      */
/*     __vptr_uint8   B_char                                       */
/* );                                                              */
/*                                                                 */
/*                                                                 */
/*                                                                 */
/*=================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <vcop.h>

#if VCOP_HOST_EMULATION
  #include "vcop_BayerCFA_interpolate_kernel.k"    // kernel source
#else
  #include "vcop_BayerCFA_interpolate_kernel.h"           // kernel source
#endif

typedef unsigned short Uint16;
typedef unsigned char  Uint8;
/*---------------------------------------------------------------------------*/
/*Input image dimensions*/
/*---------------------------------------------------------------------------*/
#define INPUT_IMG_WIDTH   32
#define INPUT_IMG_HEIGHT  8

/*---------------------------------------------------------------------------*/
/*Input block dimensions*/
/*IMPORTANT!! BLK_WIDTH should be a multiple of 16*/
/*---------------------------------------------------------------------------*/
#define BLK_WIDTH   16
#define BLK_HEIGHT   8

#define INPUT_STRIDE  INPUT_IMG_WIDTH
#define OUTPUT_STRIDE (BLK_WIDTH + 16)


#pragma DATA_SECTION (CFA_short, "Adata");
unsigned short CFA_short[INPUT_IMG_WIDTH * (INPUT_IMG_HEIGHT+2)] =
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

  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,

  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};

#pragma DATA_SECTION(R, "Cdata");
#pragma DATA_ALIGN(R, 32);
unsigned short R[(OUTPUT_STRIDE*BLK_HEIGHT)+64] = {0};

#pragma DATA_SECTION(G, "Cdata");
#pragma DATA_ALIGN(G, 32);
unsigned short G[(OUTPUT_STRIDE*BLK_HEIGHT)+64] = {0};

#pragma DATA_SECTION(B, "Cdata");
#pragma DATA_ALIGN(B, 32);
unsigned short B[(OUTPUT_STRIDE*BLK_HEIGHT)+64] = {0};

/*---------------------------------------------------------------------------*/
/*Reference R component output*/
/*---------------------------------------------------------------------------*/
#pragma DATA_SECTION (R_Ref, "Adata");
unsigned short R_Ref[BLK_WIDTH * BLK_HEIGHT] =
{
  0x01C7,0x01D3,0x01DF,0x0205,0x022C,0x0239,0x0246,0x020F,0x01D9,0x0205,0x0231,0x01FE,0x01CB,0x01CB,0x01CC,0x01D4,
  0x01CA,0x01E3,0x01FC,0x020C,0x021D,0x0216,0x020F,0x0215,0x021B,0x0217,0x0213,0x01F7,0x01DA,0x01E0,0x01E6,0x020A,
  0x01CE,0x01F3,0x0219,0x0214,0x020F,0x01F4,0x01D9,0x021B,0x025E,0x022A,0x01F6,0x01F0,0x01EA,0x01F5,0x0201,0x0240,
  0x01D8,0x01FB,0x021F,0x020D,0x01FC,0x01F0,0x01E4,0x0203,0x0222,0x0204,0x01E6,0x01EA,0x01EF,0x01E8,0x01E3,0x0217,
  0x01E3,0x0204,0x0225,0x0207,0x01EA,0x01ED,0x01F0,0x01EB,0x01E6,0x01DE,0x01D7,0x01E5,0x01F4,0x01DC,0x01C5,0x01EF,
  0x01CE,0x01E6,0x01FE,0x0206,0x020E,0x0205,0x01FC,0x01F5,0x01EF,0x01EC,0x01EA,0x01F4,0x01FF,0x01F7,0x01F0,0x0207,
  0x01B9,0x01C8,0x01D7,0x0205,0x0233,0x021E,0x0209,0x0200,0x01F8,0x01FB,0x01FE,0x0204,0x020B,0x0213,0x021B,0x0220,
  0x00DC,0x00E4,0x00EB,0x0102,0x0119,0x010F,0x0104,0x0100,0x00FC,0x00FD,0x00FF,0x0102,0x0105,0x0109,0x010D,0x0110
};

/*---------------------------------------------------------------------------*/
/*Reference G component output*/
/*---------------------------------------------------------------------------*/
#pragma DATA_SECTION (G_Ref, "Adata");
unsigned short G_Ref[BLK_WIDTH * BLK_HEIGHT] =
{
  0x028C,0x0274,0x025C,0x02BF,0x0322,0x031F,0x031C,0x02EA,0x02B9,0x02DA,0x02FC,0x02B3,0x026B,0x027F,0x0293,0x028B,
  0x0269,0x027D,0x0291,0x02C4,0x02F8,0x02F6,0x02F5,0x02DE,0x02C7,0x0292,0x025D,0x026F,0x0282,0x028E,0x029B,0x028B,
  0x028A,0x02A4,0x02BF,0x02BC,0x02B9,0x0297,0x0276,0x02BF,0x0308,0x02F5,0x02E2,0x02B7,0x028D,0x0293,0x029A,0x02F5,
  0x0281,0x02AA,0x02D4,0x02DA,0x02E1,0x029D,0x025A,0x0298,0x02D7,0x02D7,0x02D7,0x02CB,0x02BF,0x02AF,0x02A0,0x031E,
  0x028A,0x029B,0x02AD,0x02AE,0x02AF,0x02A2,0x0296,0x02A6,0x02B7,0x0293,0x0270,0x0289,0x02A3,0x0280,0x025E,0x0292,
  0x02B1,0x02CA,0x02E4,0x02C4,0x02A4,0x028E,0x0278,0x0297,0x02B6,0x028B,0x0260,0x028F,0x02BF,0x02A5,0x028B,0x029A,
  0x025A,0x0275,0x0290,0x02B3,0x02D7,0x02C4,0x02B2,0x02BA,0x02C3,0x02B3,0x02A4,0x02AE,0x02B9,0x02CA,0x02DB,0x02DF,
  0x0287,0x0286,0x0285,0x02C9,0x030E,0x02D2,0x0296,0x02AD,0x02C5,0x02BA,0x02B0,0x02AB,0x02A6,0x02BA,0x02CF,0x02CB
};

/*---------------------------------------------------------------------------*/
/*Reference B component output*/
/*---------------------------------------------------------------------------*/
#pragma DATA_SECTION (B_Ref, "Adata");
unsigned short B_Ref[BLK_WIDTH * BLK_HEIGHT] =
{
  0x01FD,0x0206,0x020F,0x0230,0x0251,0x0255,0x025A,0x024B,0x023C,0x0220,0x0205,0x01FD,0x01F6,0x01FC,0x0203,0x01F6,
  0x0204,0x020C,0x0215,0x0228,0x023B,0x022E,0x0222,0x022A,0x0232,0x022F,0x022D,0x0211,0x01F6,0x01F6,0x01F7,0x0219,
  0x020B,0x0213,0x021C,0x0221,0x0226,0x0208,0x01EB,0x020A,0x0229,0x023F,0x0255,0x0226,0x01F7,0x01F1,0x01EB,0x023D,
  0x020B,0x0216,0x0222,0x0220,0x021E,0x0201,0x01E6,0x0209,0x022C,0x021E,0x0211,0x020D,0x0209,0x01F9,0x01EA,0x0224,
  0x020B,0x021A,0x0229,0x021F,0x0216,0x01FB,0x01E1,0x0208,0x0230,0x01FE,0x01CD,0x01F4,0x021C,0x0202,0x01E9,0x020C,
  0x01E3,0x01F8,0x020D,0x021D,0x022E,0x0211,0x01F4,0x020A,0x0221,0x01FD,0x01D9,0x01F6,0x0213,0x020F,0x020D,0x021B,
  0x01BC,0x01D6,0x01F1,0x021B,0x0246,0x0227,0x0208,0x020D,0x0213,0x01FC,0x01E6,0x01F8,0x020A,0x021D,0x0231,0x022B,
  0x00DE,0x00EB,0x00F8,0x010D,0x0123,0x0113,0x0104,0x0106,0x0109,0x00FE,0x00F3,0x00FC,0x0105,0x010E,0x0118,0x0115
};

void print_output
(
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

    vcop_BayerCFA_interpolate_short_BGGR(CFA_short,
                                          INPUT_IMG_WIDTH,
                                          BLK_WIDTH,
                                          BLK_HEIGHT,
                                          R,
                                          G,
                                          B,
                                          OUTPUT_STRIDE
                                        );


   status = verify_output(R,R_Ref,BLK_HEIGHT,BLK_WIDTH);
   if(status)
   {
     printf("PASS: Component R is bit match \n");
   }
   else
   {
     printf("FAIL: Component R is not bit match \n");
     /*---------------------------------------------------------------------*/
     /*  If there is a mismatch, print out a memory trace*/
     /*---------------------------------------------------------------------*/
     print_output(R,INPUT_IMG_HEIGHT,INPUT_IMG_WIDTH);
   }

  status = verify_output(G,G_Ref,BLK_HEIGHT,BLK_WIDTH);
  if(status)
  {
    printf("PASS: Component G is bit match \n");
  }
  else
  {
    printf("FAIL: Component G is not bit match \n");
    /*---------------------------------------------------------------------*/
    /*  If there is a mismatch, print out a memory trace*/
    /*---------------------------------------------------------------------*/
    print_output(B,INPUT_IMG_HEIGHT,INPUT_IMG_WIDTH);
  }

  status = verify_output(B,B_Ref,BLK_HEIGHT,BLK_WIDTH);
  if(status)
  {
    printf("PASS: Component B is bit match \n");
  }
  else
  {
    printf("FAIL: Component B is not bit match \n");
    /*---------------------------------------------------------------------*/
    /*  If there is a mismatch, print out a memory trace*/
    /*---------------------------------------------------------------------*/
    print_output(B,INPUT_IMG_HEIGHT,INPUT_IMG_WIDTH);
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
      if((output[(i * INPUT_IMG_WIDTH) + j]) != (output_ref[(i * blk_width) + j]))
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
