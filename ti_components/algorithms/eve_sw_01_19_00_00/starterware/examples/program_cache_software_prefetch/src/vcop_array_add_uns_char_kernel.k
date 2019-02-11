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

/*----------------------------------------------------------------------------*/
/* NAME: eve_array_add_uns_char_                                              */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*                                                                            */
/* The function "eve_array_add_uns_char_     " takes two input arrays         */
/* in1_ptr and in2_ptr, and adds the values in them writing it out to         */
/* the output array "optr". The input and output arrays are 2D arrays         */
/* of the form [width * height].                                              */
/*                                                                            */
/* The function has the following prototype:                                  */
/*                                                                            */
/* void eve_array_add_uns_char_                                               */
/* (                                                                          */
/*    __vptr_uint8  in1_ptr,         // input 1 data pointer                  */
/*    __vptr_uint8  in2_ptr,         // input 2 data pointer                  */
/*    __vptr_uint8  optr,            // output data pointer                   */
/*           unsigned short width,           // width of each line            */
/*           unsigned short height           // height of each line           */
/* )                                                                          */
/*                                                                            */
/* ASSUMPTIONS:                                                               */
/*                                                                            */
/* This function does not expect any alignment restrictions on "in1_ptr"      */
/* "in2_ptr" and "optr". It expects the width to be a multiple of 8, and      */
/* can be as small as 8.                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2012.                                  */
/*============================================================================*/

#define ELEMSZ          sizeof(*in1_ptr)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)

void eve_array_add_uns_char
(
   __vptr_uint8    in1_ptr,         // input 1 data pointer
   __vptr_uint8    in2_ptr,         // input 2 data pointer
   __vptr_uint8    optr,            // output data pointer
   unsigned short  width,           // width of each line
   unsigned short  height           // height of each line
)
{
   __vector Vin1;                 // input1
   __vector Vin2;                 // input2
   __vector Vout;                 // output
   __vector Vdum;                 // dum

   for (int I0 = 0; I0 < 1; I0++)
   {
       for (int I1 = 0; I1 < height; I1++)
       {
           for (int I2 = 0; I2 < width/VCOP_SIMD_WIDTH; I2++)
           {
               __agen Addr;
      
               Addr = I1*width*ELEMSZ + I2*VECTORSZ; 

               Vin1     = in1_ptr[Addr];
               Vin2     = in2_ptr[Addr];
               Vout     = Vin1 + Vin2;
               optr[Addr] = Vout;
           }
       }
   }
}

/*----------------------------------------------------------------------------*/
/* End of file: vcop_array_add_uns_char_kernel.k                              */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2012.                                  */
/*============================================================================*/

