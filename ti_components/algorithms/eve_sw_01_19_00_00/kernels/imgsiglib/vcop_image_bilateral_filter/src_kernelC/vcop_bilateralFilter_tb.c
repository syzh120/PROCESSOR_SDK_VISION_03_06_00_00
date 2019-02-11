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


/* ===========================================================================*/
/*   @file   : vcop_bilateralFilter.c                                         */

/*   @brief  : Test bench to validate bilateral filter                        */

/*   @author Gajanan Ambi(gajanan.ambi@ti.com)                                */

/*   @version 0.0 (March 2012) : Base version.                                */

/*============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <vcop.h>
#include <math.h>

#if VCOP_HOST_EMULATION
  #include "vcop_bilateralFilter_kernel.k"    // kernel source
#else
void vcop_img_bilateralFilter
  (
    __vptr_uint8 input_ptr,
    __vptr_uint8 output_ptr,
    __vptr_uint8 diff_ptr,
    __vptr_uint16 G_pq_ptr,
    __vptr_uint32 W_p_ptr,
    __vptr_uint32 BF_p_ptr,
    __vptr_uint16 LUT_RANGE_8TBL,
    __vptr_uint16 LUT_SPACE_TBL,
    int blk_width,
    int blk_height,
    int blk_stride,
    int horz_pad_size,
    int vert_pad_size,
    unsigned int Qpoint_tbl,  
    unsigned int Qpoint_div,
    unsigned char pixel_format   
  );
#endif

/*----------------------------------------------------------------------------*/
/*PIX_FMT: input data format                                                  */
/*4: RGBA format                                                              */
/*1: Planar format (R,G,B,A)                                                  */
/*----------------------------------------------------------------------------*/
#define PIX_FMT 4 

/*----------------------------------------------------------------------------*/
/*WINDOW_SIZE: Filter window size                                             */ 
/*----------------------------------------------------------------------------*/
#define WINDOW_WIDTH  5
#define WINDOW_HEIGHT 5
#define WINDOW_SIZE  (WINDOW_WIDTH*WINDOW_HEIGHT)

#define BLK_HEIGHT    8
#define BLK_WIDTH     (8*PIX_FMT)

/*----------------------------------------------------------------------------*/
/*VERT_PAD_SIZE: Vertical padding size                                        */
/*Number of lines padded at top and bottom                                    */
/*----------------------------------------------------------------------------*/
#define VERT_PAD_SIZE 2

/*----------------------------------------------------------------------------*/
/*HORZ_PAD_SIZE: Horizontal padding size                                      */
/*Number of pixels padded at left and right of input block                    */
/*----------------------------------------------------------------------------*/
#define HORZ_PAD_SIZE (2  * PIX_FMT)

/*----------------------------------------------------------------------------*/
/*BLK_STRIDE: block stride for input image                                    */
/*Number of pixel gap between the lines                                       */
/*----------------------------------------------------------------------------*/
#define INPUT_STRIDE    (12 * PIX_FMT)

/*----------------------------------------------------------------------------*/
/*QFORMAT_TBL: Qformat required for bin log division and look up map          */
/*QFORMAT_DIV:                                                                */
/*----------------------------------------------------------------------------*/
#define QFORMAT_TBL 15
#define QFORMAT_DIV 18

/*----------------------------------------------------------------------------*/
/* input_img_blk : Test example                                               */
/*----------------------------------------------------------------------------*/
#pragma DATA_ALIGN   (input_img_blk,  32)
#pragma DATA_SECTION(input_img_blk, "Adata");
unsigned char input_img_blk[12*48] = 
{  /* RGBA*/
  0x39, 0x16, 0x52, 0xFF, 0x39, 0x16, 0x52, 0xFF,0x39, 0x16, 0x52, 0xFF, 0x39, 0x16, 0x52, 0xFF, 0x3E, 0x20, 0x60, 0xFF, 0x3E, 0x1C, 0x5D, 0xFF, 0x41, 0x1E, 0x61, 0xFF, 0x39, 0x15, 0x5E, 0xFF, 0x3E, 0x1A, 0x5C, 0xFF, 0x3C, 0x1C, 0x5D, 0xFF, 0x3E, 0x1A, 0x5C, 0xFF, 0x3C, 0x1C, 0x5D, 0xFF,
  0x39, 0x16, 0x52, 0xFF, 0x39, 0x16, 0x52, 0xFF,0x39, 0x16, 0x52, 0xFF, 0x39, 0x16, 0x52, 0xFF, 0x3E, 0x20, 0x60, 0xFF, 0x3E, 0x1C, 0x5D, 0xFF, 0x41, 0x1E, 0x61, 0xFF, 0x39, 0x15, 0x5E, 0xFF, 0x3E, 0x1A, 0x5C, 0xFF, 0x3C, 0x1C, 0x5D, 0xFF, 0x3E, 0x1A, 0x5C, 0xFF, 0x3C, 0x1C, 0x5D, 0xFF,
  0x3C, 0x12, 0x54, 0xFF, 0x3C, 0x12, 0x54, 0xFF,0x3C, 0x12, 0x54, 0xFF, 0x3C, 0x12, 0x54, 0xFF, 0x3A, 0x1B, 0x5C, 0xFF, 0x3A, 0x15, 0x5D, 0xFF, 0x3E, 0x1F, 0x61, 0xFF, 0x3B, 0x15, 0x5C, 0xFF, 0x38, 0x19, 0x60, 0xFF, 0x36, 0x1B, 0x5A, 0xFF, 0x38, 0x19, 0x60, 0xFF, 0x36, 0x1B, 0x5A, 0xFF,
  0x3C, 0x17, 0x56, 0xFF, 0x3C, 0x17, 0x56, 0xFF,0x3C, 0x17, 0x56, 0xFF, 0x3C, 0x17, 0x56, 0xFF, 0x39, 0x1B, 0x5B, 0xFF, 0x42, 0x1A, 0x5B, 0xFF, 0x41, 0x1D, 0x5D, 0xFF, 0x3E, 0x17, 0x60, 0xFF, 0x3D, 0x19, 0x5F, 0xFF, 0x3C, 0x1C, 0x5E, 0xFF, 0x3D, 0x19, 0x5F, 0xFF, 0x3C, 0x1C, 0x5E, 0xFF,
  0x42, 0x1F, 0x5D, 0xFF, 0x42, 0x1F, 0x5D, 0xFF,0x42, 0x1F, 0x5D, 0xFF, 0x42, 0x1F, 0x5D, 0xFF, 0x3F, 0x19, 0x56, 0xFF, 0x39, 0x18, 0x59, 0xFF, 0x41, 0x1E, 0x5F, 0xFF, 0x3E, 0x1E, 0x60, 0xFF, 0x3D, 0x19, 0x5E, 0xFF, 0x3F, 0x1F, 0x62, 0xFF, 0x3D, 0x19, 0x5E, 0xFF, 0x3F, 0x1F, 0x62, 0xFF,
  0x39, 0x1A, 0x58, 0xFF, 0x39, 0x1A, 0x58, 0xFF,0x39, 0x1A, 0x58, 0xFF, 0x39, 0x1A, 0x58, 0xFF, 0x40, 0x23, 0x61, 0xFF, 0x3C, 0x1E, 0x5D, 0xFF, 0x40, 0x1D, 0x64, 0xFF, 0x3E, 0x1D, 0x63, 0xFF, 0x40, 0x19, 0x5E, 0xFF, 0x42, 0x22, 0x62, 0xFF, 0x40, 0x19, 0x5E, 0xFF, 0x42, 0x22, 0x62, 0xFF,
  0x38, 0x18, 0x59, 0xFF, 0x38, 0x18, 0x59, 0xFF,0x38, 0x18, 0x59, 0xFF, 0x38, 0x18, 0x59, 0xFF, 0x3F, 0x20, 0x61, 0xFF, 0x3D, 0x1D, 0x61, 0xFF, 0x39, 0x19, 0x5F, 0xFF, 0x43, 0x20, 0x5F, 0xFF, 0x3D, 0x1C, 0x61, 0xFF, 0x3D, 0x1A, 0x60, 0xFF, 0x3D, 0x1C, 0x61, 0xFF, 0x3D, 0x1A, 0x60, 0xFF,
  0x3F, 0x19, 0x59, 0xFF, 0x3F, 0x19, 0x59, 0xFF,0x3F, 0x19, 0x59, 0xFF, 0x3F, 0x19, 0x59, 0xFF, 0x3E, 0x1D, 0x60, 0xFF, 0x3B, 0x18, 0x5F, 0xFF, 0x3D, 0x1F, 0x5E, 0xFF, 0x46, 0x1F, 0x66, 0xFF, 0x3E, 0x1C, 0x5C, 0xFF, 0x40, 0x1D, 0x61, 0xFF, 0x3E, 0x1C, 0x5C, 0xFF, 0x40, 0x1D, 0x61, 0xFF,
  0x3E, 0x19, 0x5C, 0xFF, 0x3E, 0x19, 0x5C, 0xFF,0x3E, 0x19, 0x5C, 0xFF, 0x3E, 0x19, 0x5C, 0xFF, 0x3D, 0x1E, 0x63, 0xFF, 0x3B, 0x20, 0x63, 0xFF, 0x43, 0x1E, 0x67, 0xFF, 0x3C, 0x18, 0x5D, 0xFF, 0x40, 0x15, 0x5E, 0xFF, 0x42, 0x1C, 0x5F, 0xFF, 0x40, 0x15, 0x5E, 0xFF, 0x42, 0x1C, 0x5F, 0xFF,
  0x3E, 0x19, 0x58, 0xFF, 0x3E, 0x19, 0x58, 0xFF,0x3E, 0x19, 0x58, 0xFF, 0x3E, 0x19, 0x58, 0xFF, 0x42, 0x22, 0x61, 0xFF, 0x47, 0x28, 0x69, 0xFF, 0x46, 0x27, 0x65, 0xFF, 0x3F, 0x1B, 0x5F, 0xFF, 0x39, 0x1A, 0x5D, 0xFF, 0x46, 0x1F, 0x61, 0xFF, 0x39, 0x1A, 0x5D, 0xFF, 0x46, 0x1F, 0x61, 0xFF,
  0x3F, 0x18, 0x5F, 0xFF, 0x3F, 0x18, 0x5F, 0xFF,0x3F, 0x18, 0x5F, 0xFF, 0x3F, 0x18, 0x5F, 0xFF, 0x3A, 0x1D, 0x60, 0xFF, 0x47, 0x20, 0x62, 0xFF, 0x41, 0x1D, 0x62, 0xFF, 0x40, 0x1B, 0x63, 0xFF, 0x3A, 0x19, 0x60, 0xFF, 0x45, 0x1F, 0x62, 0xFF, 0x3A, 0x19, 0x60, 0xFF, 0x45, 0x1F, 0x62, 0xFF,
  0x3B, 0x1D, 0x5D, 0xFF, 0x3B, 0x1D, 0x5D, 0xFF,0x3B, 0x1D, 0x5D, 0xFF, 0x3B, 0x1D, 0x5D, 0xFF, 0x43, 0x21, 0x62, 0xFF, 0x44, 0x23, 0x66, 0xFF, 0x45, 0x22, 0x65, 0xFF, 0x44, 0x21, 0x66, 0xFF, 0x3B, 0x1C, 0x61, 0xFF, 0x49, 0x26, 0x66, 0xFF, 0x3B, 0x1C, 0x61, 0xFF, 0x49, 0x26, 0x66, 0xFF
};

/*----------------------------------------------------------------------------*/
/*LUT_RANGE_8TBL :8 times replicated range look up table                      */
/*----------------------------------------------------------------------------*/
#pragma DATA_ALIGN   (LUT_RANGE_8TBL,  32)
#pragma DATA_SECTION(LUT_RANGE_8TBL, "Cdata");
unsigned short LUT_RANGE_8TBL[8*256] = {0};

/*----------------------------------------------------------------------------*/
/*LUT_RANGE_1TBL : range look up table, before replication                    */
/*----------------------------------------------------------------------------*/
#pragma DATA_ALIGN   (LUT_RANGE_1TBL,  32)
#pragma DATA_SECTION(LUT_RANGE_1TBL, "Cdata");
unsigned short LUT_RANGE_1TBL[256] = {0};

/*----------------------------------------------------------------------------*/
/*LUT_SPACE_TBL : space look up table                                         */
/*----------------------------------------------------------------------------*/
#pragma DATA_ALIGN   (LUT_SPACE_TBL,  32)
#pragma DATA_SECTION(LUT_SPACE_TBL, "Bdata");
unsigned short LUT_SPACE_TBL[25] = {0};

/*----------------------------------------------------------------------------*/
/* vcop_diff_out : intermediate difference result                             */
/*----------------------------------------------------------------------------*/
#pragma DATA_ALIGN   (vcop_diff_out,  32)
#pragma DATA_SECTION(vcop_diff_out, "Bdata"); 
unsigned char vcop_diff_out[WINDOW_SIZE * BLK_HEIGHT * BLK_WIDTH] = {0};

/*----------------------------------------------------------------------------*/
/* vcop_G_pq_out : intermediate G_pq result                                   */
/*----------------------------------------------------------------------------*/
#pragma DATA_SECTION(vcop_G_pq_out, "Adata"); 
unsigned short vcop_G_pq_out[WINDOW_SIZE*BLK_HEIGHT*BLK_WIDTH + 8] = {0};

/*----------------------------------------------------------------------------*/
/* vcop_W_p_out : intermediate W_p result                                     */
/*----------------------------------------------------------------------------*/
#pragma DATA_SECTION(vcop_W_p_out, "Bdata"); 
unsigned int vcop_W_p_out[BLK_HEIGHT * BLK_WIDTH + 8] = {0};

/*----------------------------------------------------------------------------*/
/* vcop_BF_p_out : intermediate BF_p result                                   */
/*----------------------------------------------------------------------------*/
#pragma DATA_SECTION(vcop_BF_p_out, "Bdata"); 
unsigned int vcop_BF_p_out[BLK_HEIGHT * BLK_WIDTH + 8] = {0};

/*----------------------------------------------------------------------------*/
/* vcop_filter_out : vcop output image block                                  */
/*----------------------------------------------------------------------------*/
#pragma DATA_SECTION(vcop_filter_out, "Adata");
unsigned char vcop_filter_out[BLK_HEIGHT * BLK_WIDTH] = {0};

/*----------------------------------------------------------------------------*/
/* ref_filter_out : reference output block                                    */
/*----------------------------------------------------------------------------*/
#pragma DATA_SECTION(ref_filter_out, "Ddata");  
unsigned char ref_filter_out[BLK_HEIGHT * BLK_WIDTH] = 
{
  0x3D,0x15,0x5B,0xFF,0x3D,0x15,0x57,0xFF,0x3D,0x1C,0x5F,0xFF,0x3E,0x1A,0x67,0xFF,0x3F,0x1D,0x66,0xFF,0x3D,0x18,0x67,0xFF,0x3D,0x1B,0x68,0xFF,0x39,0x1C,0x62,0xFF,
  0x3E,0x18,0x5C,0xFF,0x3E,0x19,0x5B,0xFF,0x3D,0x1C,0x61,0xFF,0x3F,0x1C,0x64,0xFF,0x3F,0x1D,0x68,0xFF,0x3E,0x1A,0x69,0xFF,0x3E,0x1C,0x68,0xFF,0x3D,0x1C,0x68,0xFF,
  0x40,0x1D,0x5D,0xFF,0x3F,0x1D,0x5D,0xFF,0x3F,0x1C,0x5A,0xFF,0x3C,0x1C,0x5D,0xFF,0x40,0x1E,0x68,0xFF,0x3F,0x1E,0x69,0xFF,0x3F,0x1D,0x69,0xFF,0x3F,0x1E,0x69,0xFF,
  0x3C,0x1C,0x62,0xFF,0x3D,0x1D,0x5E,0xFF,0x3F,0x20,0x60,0xFF,0x3E,0x1E,0x63,0xFF,0x3F,0x1E,0x62,0xFF,0x3F,0x1E,0x68,0xFF,0x3F,0x1D,0x6A,0xFF,0x40,0x1F,0x6B,0xFF,
  0x3C,0x1B,0x64,0xFF,0x3C,0x1C,0x60,0xFF,0x3E,0x1F,0x64,0xFF,0x3E,0x1E,0x6A,0xFF,0x3C,0x1D,0x6A,0xFF,0x41,0x1F,0x6A,0xFF,0x3F,0x1D,0x6A,0xFF,0x3F,0x1D,0x69,0xFF,
  0x3F,0x1B,0x65,0xFF,0x3F,0x1C,0x5F,0xFF,0x3E,0x1E,0x66,0xFF,0x3E,0x1C,0x69,0xFF,0x3E,0x1F,0x65,0xFF,0x44,0x1E,0x68,0xFF,0x3F,0x1D,0x63,0xFF,0x40,0x1D,0x6A,0xFF,
  0x3F,0x1B,0x64,0xFF,0x3F,0x1C,0x61,0xFF,0x3F,0x1E,0x64,0xFF,0x3E,0x1F,0x6A,0xFF,0x42,0x1F,0x67,0xFF,0x3F,0x1A,0x62,0xFF,0x40,0x1A,0x69,0xFF,0x41,0x1D,0x68,0xFF,
  0x3F,0x1B,0x5E,0xFF,0x3F,0x1C,0x5E,0xFF,0x41,0x20,0x66,0xFF,0x48,0x26,0x6A,0xFF,0x45,0x26,0x6B,0xFF,0x40,0x1D,0x67,0xFF,0x3D,0x1D,0x67,0xFF,0x46,0x1E,0x6A,0xFF
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

void lut_space_preparation
(
unsigned short *lut_range_q12
);

void lut_range_preparation
(
unsigned short *lut_range_q12
);

void range_lut_replication
(
unsigned short *src_buffer,
unsigned short *dst_buffer
);

/**
 *******************************************************************************
 * @fn       main 
 * @brief    Implementation and validation of Bilateral filter 
 * @return  - 
 *******************************************************************************
*/
int main()
{
    unsigned int status = 0;
    
    /*------------------------------------------------------------------------*/
    /*  Space look up table preparation                                       */
    /*------------------------------------------------------------------------*/
    lut_space_preparation(LUT_SPACE_TBL);
    
    /*------------------------------------------------------------------------*/
    /*  Range look up table preparation                                       */
    /*------------------------------------------------------------------------*/
    lut_range_preparation(LUT_RANGE_1TBL);

    /*------------------------------------------------------------------------*/
    /*  Range look up table 8 times replication                               */
    /*------------------------------------------------------------------------*/
    range_lut_replication(LUT_RANGE_1TBL,LUT_RANGE_8TBL);
    
    /*------------------------------------------------------------------------*/
    /*  vcop function call for bilateral filter                               */
    /*------------------------------------------------------------------------*/
    vcop_img_bilateralFilter(input_img_blk,
                             vcop_filter_out,
                             vcop_diff_out,
                             vcop_G_pq_out,
                             vcop_W_p_out,
                             vcop_BF_p_out,
                             LUT_RANGE_8TBL,
                             LUT_SPACE_TBL,
                             BLK_WIDTH,
                             BLK_HEIGHT,
                             INPUT_STRIDE,
                             HORZ_PAD_SIZE,
                             VERT_PAD_SIZE,
                             QFORMAT_TBL,
                             QFORMAT_DIV,
                             PIX_FMT
                             );


    /*------------------------------------------------------------------------*/
    /*  verify output with reference                                          */
    /*------------------------------------------------------------------------*/
    status = verify_output(vcop_filter_out,ref_filter_out,BLK_HEIGHT,BLK_WIDTH);
    if(status)
    {
      printf("PASS: bit match \n");
    }
    else
    {
      printf("FAIL: not bit match \n");
     /*-----------------------------------------------------------------------*/
     /*  If there is a mismatch, print out a memory trace                     */
     /*-----------------------------------------------------------------------*/
     print_output(vcop_filter_out,BLK_HEIGHT,BLK_WIDTH);
    }
   
  printf("Done!!!\n");
  return 0;
}

/**
 *******************************************************************************
 * @fn       verify_output 
 * @brief    function to compare output data with reference. 
 *
 * @inputs -  output    : Output data buffer from vcop
 *         -  output_ref: Reference output data buffer 
 *         -  blk_height: Block height 
 *         -  blk_width : Block width 
 * @return - None
 * @param Comments:
 *******************************************************************************
*/
unsigned int verify_output
(
unsigned char *output,
unsigned char *output_ref,
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
      if((output[(i * blk_width) + j]) != (output_ref[(i * blk_width) + j]))
      {
        status = 0;
      }
    }
  }

return(status);
}

/**
 *******************************************************************************
 * @fn       print_output 
 * @brief    Function to print the output data. 
 *
 * @inputs -  buffer    : Output data buffer from vcop
 *         -  blk_height: Block height 
 *         -  blk_width : Block width 
 * @return - None
 * @param Comments: 
 *******************************************************************************
*/
void print_output
(
unsigned char *buffer,
unsigned int   blk_height,
unsigned int   blk_width
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

/**
 *******************************************************************************
 * @fn       lut_space_preparation 
 * @brief    Function to prepare space look up table. 
 *
 * @inputs -  lut_range_q12  : LUT Buffer
 * @return - None
 * @param Comments: 
 *******************************************************************************
*/
void lut_space_preparation
(
unsigned short *lut_space_q12
)
{
  unsigned int s,t;
  float sigmaS = 1.0f;
  
  for(s = 0; s < 5; s++)
  {
    for(t = 0; t < 5; t++)
    {
      int qval   = 12;
      int maxval = (1<<qval)-1;
      float temp = ((s-2)*(s-2) + (t-2)*(t-2))/(2.0f*sigmaS*sigmaS);
      float val  = (float) exp(-temp) * (1<<qval) + (0.5);
      lut_space_q12[s*5+t] = val>=maxval? maxval : val;
    }
  }
}

/**
 *******************************************************************************
 * @fn       lut_range_preparation 
 * @brief    Function to prepare range look up table. 
 *
 * @inputs -  lut_range_q12  : LUT Buffer
 * @return - None
 * @param Comments: 
 *******************************************************************************
*/
void lut_range_preparation
(
unsigned short *lut_range_q12
)
{
  unsigned int i;
  float sigmaR = 0.02f * 255;
  
  for(i = 0; i <= 255; i++)
  {
    int qval = 12;
    int maxval = (1<<qval)-1;
    float temp = (i*i)/(2.0f*sigmaR*sigmaR);
    float val = exp(-temp) * (1<<qval) + (0.5);
    lut_range_q12[i] = val>=maxval? maxval : val;
  }
}


/**
 *******************************************************************************
 * @fn       range_lut_replication 
 * @brief    Function to replicate the range look up table 8 times. 
 *
 * @inputs -  src_buffer  : source buffer
 *         -  dst_buffer  : Replicated buffer
 * @return - None
 * @param Comments: 
 *******************************************************************************
*/
void range_lut_replication
(
unsigned short *src_buffer,
unsigned short *dst_buffer
)
{
  unsigned int i;
  unsigned int val;
  unsigned int fst = 1;
  unsigned int cnt = 0;
  unsigned int k = 0;

  for(i = 0; i<256; i++)
  {
    val = src_buffer[i];

    if((i+ fst)%2 == 0)
    {
      cnt += 16; 
      k = 0;
    }
    fst = 0;
    
    dst_buffer[cnt + k]      = val;   
    dst_buffer[cnt + k + 2]  = val;
    dst_buffer[cnt + k + 4]  = val;   
    dst_buffer[cnt + k + 6]  = val;
    dst_buffer[cnt + k + 8]  = val;   
    dst_buffer[cnt + k + 10] = val;
    dst_buffer[cnt + k + 12] = val;   
    dst_buffer[cnt + k + 14] = val;
    k++;
  }
}

