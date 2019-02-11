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

/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.            */
/*                      All Rights Reserved                                */
/*=========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif


#define ELEMSZ_IN      sizeof(*input_ptr)
#define VECTORSZ_IN    (VCOP_SIMD_WIDTH * ELEMSZ_IN)

#define ELEMSZ_OUT     sizeof(*output_ptr)
#define VECTORSZ_OUT   (VCOP_SIMD_WIDTH * ELEMSZ_OUT)

/*-----------------------------------------------------------------------*/
/* Median col-wise filter with 3 taps.                                   */
/* This routine takes 3/16 VCOP cycles per pixel and is lD-ST bound.     */
/*-----------------------------------------------------------------------*/

void vcop_median_3tap_filt_col_short
(
    __vptr_int16 input_ptr,	        /* starting address of input */
    __vptr_int16 output_ptr,        /* starting address of output */
    signed short input_width,	    /* height of input array */
    signed short input_height,      /* width of input array */
    signed short output_width,      /* height of output array */
    signed short output_height,     /* width of output array */
    signed short compute_width,     /* height of compute block */
    signed short compute_height,    /* width of compute block */
    signed short median_size,	    /* 3 or 5-tap median filter */
    signed short input_type,	    /* 0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT  */
    signed short output_type	    /* 0 - BYTE,  1 - SHORT */
)
{
    __vector low_e, mid_e, high_e;
    __vector low_o, mid_o, high_o;

    /*---------------------------------------------------------------------*/
    /* This is the first loop where sets of three consecutive cols are     */
    /* re ordered as min, med and max cols. Thus, the output of this loop  */
    /* has a height of 3x that of the input array.                         */
    /*---------------------------------------------------------------------*/

    for ( int I1 = 0; I1 < compute_height; I1++)
    {
       for (int I2 = 0; I2 <  compute_width/(2 * VCOP_SIMD_WIDTH); I2++ )
       {
           __agen dataAddr0;

           dataAddr0 =  (I2 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN) +
                        (I1 * input_width * ELEMSZ_IN);

          /*--------------------------------------------------------------*/
          /* Read in the latest column.                                   */
          /*--------------------------------------------------------------*/

          (low_e, low_o)   = input_ptr[dataAddr0].deinterleave();
          (mid_e, mid_o)   = (input_ptr + (1 * input_width * ELEMSZ_IN))[dataAddr0].deinterleave();
          (high_e, high_o) = (input_ptr + (2 * input_width * ELEMSZ_IN))[dataAddr0].deinterleave();

          /*--------------------------------------------------------------*/
          /* First level of sorting.                                      */
          /*--------------------------------------------------------------*/

          (mid_e, high_e).minmax();
          (mid_o, high_o).minmax();

          (low_e, high_e).minmax();
          (low_o, high_o).minmax();

          (low_e, mid_e).minmax();
          (low_o, mid_o).minmax();

          output_ptr[dataAddr0].interleave() = (mid_e, mid_o);
       }
   }
}

/*-------------------------------------------------------------------------*/
/* Median col-wise filter with 5 taps.                                     */
/* This routine takes 9/16 VCOP cycles per pixel and is computations       */
/* bound.                                                                  */
/*-------------------------------------------------------------------------*/

void vcop_median_5tap_filt_col_short
(
    __vptr_int16 input_ptr,	        /* starting address of input */
    __vptr_int16 output_ptr,        /* starting address of output */
    signed short input_width,	    /* height of input array */
    signed short input_height,      /* width of input array */
    signed short output_width,      /* height of output array */
    signed short output_height,     /* width of output array */
    signed short compute_width,     /* height of compute block */
    signed short compute_height,    /* width of compute block */
    signed short median_size,	    /* 3 or 5-tap median filter */
    signed short input_type,	    /* 0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT  */
    signed short output_type	    /* 0 - BYTE,  1 - SHORT */
)
{

    __vector data0_e, data1_e, data2_e, data3_e, data4_e;
    __vector data0_o, data1_o, data2_o, data3_o, data4_o;

    /*---------------------------------------------------------------------*/
    /* This is the first loop where sets of three consecutive cols are     */
    /* re ordered as min, med and max cols. Thus, the output of this loop  */
    /* has a height of 3x that of the input array.                         */
    /*---------------------------------------------------------------------*/

    for ( int I1 = 0; I1 < compute_height; I1++)
    {
       for (int I2 = 0; I2 <  compute_width/(2 * VCOP_SIMD_WIDTH); I2++ )
       {
           __agen dataAddr0;

           dataAddr0 = (I2 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_OUT) +
                       (I1 * input_width * ELEMSZ_OUT);

          /*--------------------------------------------------------------*/
          /* Read in the latest column.                                   */
          /*--------------------------------------------------------------*/

          (data4_e, data4_o) =  (input_ptr + (0 * input_width * ELEMSZ_IN))[dataAddr0].deinterleave();
          (data3_e, data3_o) =  (input_ptr + (1 * input_width * ELEMSZ_IN))[dataAddr0].deinterleave();
          (data2_e, data2_o) =  (input_ptr + (2 * input_width  * ELEMSZ_IN))[dataAddr0].deinterleave();
          (data1_e, data1_o) =  (input_ptr + (3 * input_width  * ELEMSZ_IN))[dataAddr0].deinterleave();
          (data0_e, data0_o) =  (input_ptr + (4 * input_width  * ELEMSZ_IN))[dataAddr0].deinterleave();

          /*--------------------------------------------------------------*/
          /* First level of sorting.                                      */
          /*--------------------------------------------------------------*/

          (data0_e, data1_e).minmax();
          (data0_o, data1_o).minmax();

          (data1_e, data2_e).minmax();
          (data1_o, data2_o).minmax();

          (data2_e, data3_e).minmax();
          (data2_o, data3_o).minmax();

          (data3_e, data4_e).minmax();
          (data3_o, data4_o).minmax();

          /*--------------------------------------------------------------*/
          /* Second level of sorting.                                     */
          /*--------------------------------------------------------------*/

          (data0_e, data1_e).minmax();
          (data0_o, data1_o).minmax();

          (data1_e, data2_e).minmax();
          (data1_o, data2_o).minmax();

          (data2_e, data3_e).minmax();
          (data2_o, data3_o).minmax();

          /*--------------------------------------------------------------*/
          /* Third level of sorting.                                      */
          /*--------------------------------------------------------------*/

          (data0_e, data1_e).minmax();
          (data0_o, data1_o).minmax();

          (data1_e, data2_e).minmax();
          (data1_o, data2_o).minmax();

           output_ptr[dataAddr0].interleave() = (data2_e, data2_o);
       }
   }
}
