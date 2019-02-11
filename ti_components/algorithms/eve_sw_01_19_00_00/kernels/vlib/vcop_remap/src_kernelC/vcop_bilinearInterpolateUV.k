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

/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#include "vcop_remap_kernel.h"
void vcop_bilinearInterpolateUV(
        __vptr_uint8        src,
        __vptr_uint8        dst,
        unsigned short      outputBlockSize,
        __vptr_uint16       tluIndexArray,
        __vptr_uint8        fracArray,
        __vptr_uint16       scratch,                  /* size: 4*2*ALIGN_2SIMD(outputBlockSize) bytes */
        __vptr_uint8        scratchHbuf,
        unsigned short      stride,
        unsigned int        inSize,
         __vptr_uint8        inLUT,
       unsigned char       mnQShift,
        unsigned char       oQShift,
        unsigned short      qScale,
        unsigned char       mult,
        unsigned char       rightShift,
        long                sat_high,
        long                sat_high_set,
        long                sat_low,
        long                sat_low_set
)
{
    __agen Addr0=0;
    __agen Addr1,Addr2;
    __vector in_0,in_1;               //Top-left pixel
    __vector in_2,in_3;               //Top-left pixel
    __vector in_4,in_5;               //Top-left pixel
    __vector in_6,in_7;               //Top-left pixel
   __vector first_0,first_1;               //Top-left pixel

    for (int I2 = 0; I2 < ALIGN_2SIMD(inSize)/(2*VCOP_SIMD_WIDTH); I2++)
    {

      Addr1 = I2*4*VCOP_SIMD_WIDTH;
      Addr2 = I2*2*VCOP_SIMD_WIDTH;

      (in_0, in_1) = (src)[Addr2].deinterleave();
      (in_2, in_3) = (src+stride)[Addr2].deinterleave();

      (inLUT)[Addr1].interleave() = (in_0, in_1);
      (inLUT + 16)[Addr1].interleave() = (in_2, in_3);
    }

    _LOOKUP(2,4);
    for (int I1 = 0; I1 < outputBlockSize; I1++)
    {
            __vector Vindex, Vdata;
            __agen TLU_agen = 0;
            __agen ind_agen = I1*2;
            __agen out_agen = I1*8*sizeof(*dst);
            Vindex = tluIndexArray[ind_agen].onept();
            Vdata = inLUT[TLU_agen].lookup(Vindex);
            scratchHbuf[out_agen].table_npt() = Vdata;
    }

    __vector v_qScale;
    v_qScale= qScale;

    for (int I1 = 0; I1 < ALIGN_SIMD(outputBlockSize)/VCOP_SIMD_WIDTH; I1++)
    {
        __vector temp1, temp2, xFrac, yFrac, qScale_xFrac, qScale_yFrac, pix00, pix10, pix01, pix11, fracMap;
        __agen Addr_out;
        __vector Vmaskx;
        __vector Vmasky;
        __vector Vshiftx;
        __vector Vshifty;

        Vmaskx = 0x000000000F;
        Vshifty = -4;

        Addr1     = I1*VCOP_SIMD_WIDTH*sizeof(*fracArray);
        Addr2     = I1*8*VCOP_SIMD_WIDTH*sizeof(*scratchHbuf);
        Addr_out  = I1*2*VCOP_SIMD_WIDTH*sizeof(*dst);

        fracMap = fracArray[Addr1].npt();
        (in_0, in_1) = scratchHbuf[Addr2].deinterleave();       //in_0 --> 4 U input (of 0-1 ouput points) ; in_1 --> 4 V input (of 0-1 ouput points)
        (in_2, in_3) = (scratchHbuf+16)[Addr2].deinterleave();  //in_2 --> 4 U input (of 2-3 ouput points) ; in_3 --> 4 V input (of 2-3 ouput points)
        (in_4, in_5) = (scratchHbuf+32)[Addr2].deinterleave();       //in_4 --> 4 U input (of 4-5 ouput points) ; in_5 --> 4 V input (of 4-5 ouput points)
        (in_6, in_7) = (scratchHbuf+48)[Addr2].deinterleave();  //in_6 --> 4 U input (of 6-7 ouput points) ; in_7 --> 4 V input (of 6-7 ouput points)

#if 1
        (in_0,in_2) = (in_0,in_2).deinterleave();
        (in_4,in_6) = (in_4,in_6).deinterleave();

        // TL BL
        // TR BR
        (in_0,in_4) = (in_0,in_4).deinterleave();
        (in_2,in_6) = (in_2,in_6).deinterleave();

        (in_1,in_3) = (in_1,in_3).deinterleave();
        (in_5,in_7) = (in_5,in_7).deinterleave();

        // TL BL
        // TR BR
        (in_1,in_5) = (in_1,in_5).deinterleave();
        (in_3,in_7) = (in_3,in_7).deinterleave();


        xFrac = fracMap & Vmaskx;
        yFrac = fracMap << Vshifty;

        temp1= xFrac*in_2;
        temp2= xFrac*in_6;

        qScale_xFrac= v_qScale - xFrac;
        qScale_yFrac= v_qScale - yFrac;

        temp1+= qScale_xFrac*in_0;
        temp2+= qScale_xFrac*in_4;

        temp1= qScale_yFrac*temp1;
        temp2= yFrac*temp2;

        in_0= temp1 + temp2;

        temp1= xFrac*in_3;
        temp2= xFrac*in_7;

        temp1+= qScale_xFrac*in_1;
        temp2+= qScale_xFrac*in_5;

        temp1= qScale_yFrac*temp1;
        temp2= yFrac*temp2;

        in_1= temp1 + temp2;
#else
        (temp1,temp2) = (in_0,in_2).deinterleave();
        (in_0,in_2) = (in_4,in_6).deinterleave();

        // TL BL
        // TR BR
        (in_4,in_6)  = (temp1,in_0).deinterleave();
        (temp1,in_0) = (temp2,in_2).deinterleave();

        (in_2,temp2) = (in_1,in_3).deinterleave();
        (in_1,in_3)  = (in_5,in_7).deinterleave();

        // TL BL
        // TR BR
        (in_5,in_7)  = (in_2,in_1).deinterleave();
        (in_2,in_1)  = (temp2,in_3).deinterleave();

        in_3 = temp1;

        xFrac = fracMap & Vmaskx;
        yFrac = fracMap << Vshifty;

        temp1= xFrac*in_3;
        temp2= xFrac*in_0;

        qScale_xFrac= v_qScale - xFrac;
        qScale_yFrac= v_qScale - yFrac;

        temp1+= qScale_xFrac*in_4;
        temp2+= qScale_xFrac*in_6;

        temp1= qScale_yFrac*temp1;
        temp2= yFrac*temp2;

        in_0= temp1 + temp2;

        temp1= xFrac*in_2;
        temp2= xFrac*in_1;

        temp1+= qScale_xFrac*in_5;
        temp2+= qScale_xFrac*in_7;

        temp1= qScale_yFrac*temp1;
        temp2= yFrac*temp2;

        in_1= temp1 + temp2;

#endif

        dst[Addr_out].interleave()= (in_0,in_1).round(mnQShift+oQShift).saturate(sat_low, sat_low_set, sat_high, sat_high_set);
    }
}



