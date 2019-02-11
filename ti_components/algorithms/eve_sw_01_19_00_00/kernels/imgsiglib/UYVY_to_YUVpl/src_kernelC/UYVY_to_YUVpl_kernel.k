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
/* NAME: eve_UYVY_to_YUVpl                                                    */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*                                                                            */
/* The function "eve_UYVY_to_YUVpl" takes an interleaved array of luma and    */
/* chroma pixels YUV 4:2:2 and deinterleaves them into three separate memory  */
/* regions.                                                                   */
/*                                                                            */
/* The function has the following prototype:                                  */
/*                                                                            */
/* void eve_UYVY_to_YUVpl                                                     */
/* (                                                                          */
/*   __vptr_uint16 in1_ptr,           // interleaved YUV image data           */
/*          int width,                // image width                          */
/*          int line_pitch,           // pitch of each line                   */
/*          int height,               // image height                         */
/*   __vptr_uint8 optr_Y,             // output data pointer, Y               */
/*   __vptr_uint8 optr_Cr,            // output data pointer, Cr              */
/*   __vptr_uint8 optr_Cb             // output data pointer, Cb              */
/* )                                                                          */
/*                                                                            */
/*                                                                            */
/* The input data is stored in the following format:                          */
/*                                                                            */
/*                Byte 0   Byte 1  Byte 2  Byte 3                             */
/*                  Cb0      Y0      Cr0     Y1                               */
/*                                                                            */
/* The image data is loaded as 16-bit halfwords where each half word contains */
/* a Y component and either a Cr or Cb component. Planarization is done       */
/* by using store-byte to ignore the upper byte of the half word and store    */
/* only Cb and Cr, and store-byte with trunction by 8-bits to shift the luma  */
/* from the upper byte to the lower byte before the store.                    */
/*                                                                            */
/* ASSUMPTIONS:                                                               */
/*                                                                            */
/* This function expects the image width to be a multiple of 16.              */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2012.                                  */
/*============================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif


#define ELEMSZ              sizeof(*in1_ptr)
#define OUT_ELEMSZ          sizeof(*optr_Y)
#define VECTORSZ            (2 * VCOP_SIMD_WIDTH*ELEMSZ)
#define OUT_Y_VECTORSZ      (2 * VCOP_SIMD_WIDTH*OUT_ELEMSZ)
#define OUT_CrCb_VECTORSZ   (VCOP_SIMD_WIDTH*OUT_ELEMSZ)
#define VCOP_2SIMD_WIDTH    (2 * VCOP_SIMD_WIDTH)

void eve_UYVY_to_YUVpl
(
   __vptr_uint16 in1_ptr,           // interleaved YUV image data
          int    width,             // image width
          int    line_pitch,        // pitch of each line
          int    height,            // image height
   __vptr_uint8 optr_Y,             // output data pointer, Y
   __vptr_uint8 optr_Cr,            // output data pointer, Cr
   __vptr_uint8 optr_Cb             // output data pointer, Cb

)
{
   __vector Vin1,  Vin2;

   for (int I1 = 0; I1 < height; I1++)
   {
       for (int I2 = 0; I2 < width/VCOP_2SIMD_WIDTH; I2++)
       {
           __agen Addr, AddrOut_Y, AddrOut_CrCb;

           /* --------------------------------------------------------------- */
           /* Input Increments                                                */
           /* --------------------------------------------------------------- */
           Addr         = I1*line_pitch*ELEMSZ    + I2*VECTORSZ;

           /* --------------------------------------------------------------- */
           /* Output Increments                                               */
           /* Cr & Cb are half the width of the Y data                        */
           /* --------------------------------------------------------------- */
           AddrOut_Y    = I1*width*OUT_ELEMSZ     + I2*OUT_Y_VECTORSZ;
           AddrOut_CrCb = I1*(width/2)*OUT_ELEMSZ + I2*OUT_CrCb_VECTORSZ;

           /* --------------------------------------------------------------- */
           /* Load the interleaved image data in half-word chunks. For        */
           /* example:                                                        */
           /*            Vin1 = {Y0 Cb0, Y2 Cb1, Y4 Cb2, . . . Y14 Cb7}       */
           /*            Vin2 = {Y1 Cr0, Y3 Cr1, Y5 Cr2, . . . Y15 Cr7}       */
           /* --------------------------------------------------------------- */
           (Vin1,Vin2) = in1_ptr[Addr].deinterleave();

           /* --------------------------------------------------------------- */
           /* Luma data is in upper byte of half word Vin1 and Vin2           */
           /* Perform a truncation by 8-bits to extract and store             */
           /* the luma value to memory.                                       */
           /* --------------------------------------------------------------- */
           optr_Y[AddrOut_Y].interleave() = (Vin1, Vin2).truncate(8);

           /* --------------------------------------------------------------- */
           /* Cb and Cr pixels are in the lower bytes of the odd and even     */
           /* registers from the deinterleaving load. Since the luma pixel is */
           /* in the upper byte of the half word, we use a "store byte" so    */
           /* that only the Cr/Cb data is stored in these memory locations.   */
           /* --------------------------------------------------------------- */
           optr_Cb[AddrOut_CrCb] = Vin1;
           optr_Cr[AddrOut_CrCb] = Vin2;
       }
   }
}

/*----------------------------------------------------------------------------*/
/* End of file: UYVY_to_YUVpl_kernel.k                                        */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2012.                                  */
/*============================================================================*/

