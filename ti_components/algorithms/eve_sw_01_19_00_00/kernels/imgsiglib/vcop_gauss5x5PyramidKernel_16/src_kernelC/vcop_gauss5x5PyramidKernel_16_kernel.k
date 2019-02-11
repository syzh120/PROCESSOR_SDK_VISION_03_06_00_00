/*
*
* Copyright (c) 2013-2017 Texas Instruments Incorporated
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

/*      Copyright (C) 2013 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define VCOP_SIMD_WIDTH2 (2*VCOP_SIMD_WIDTH)
#define ELEMSZ          sizeof(*pIn)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)

#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))
#define ALIGN_SIMD2(a)   (((a) + (2*VCOP_SIMD_WIDTH)-1) & ~(2*VCOP_SIMD_WIDTH-1))

/*--------------------------------------------------------------------------------*/
/* Input to this kernel is WxH block and output of this kernel is (W/2) x H block */
/*--------------------------------------------------------------------------------*/
void vcop_gauss5x5PyramidKernel_16_horiz
(
    __vptr_uint16   pIn,
    __vptr_uint16   pOut,
    unsigned short width,
    unsigned short height,
    unsigned short inPitch,
    unsigned short outPitch
)
{

    __vector vIn024_14, vIn135_15,	vIn246_16, vIn357_17, vIn468_18, vIn579_19, vTemp, C_4, C_6;
    __vector  vTemp1,vTemp2;

    C_4 = 4;
    C_6 = 6;

    for( int i = 0; i < height; i++)
    {
        for(int j = 0; j < ALIGN_SIMD2(width)/VCOP_SIMD_WIDTH2; j++)
        {
            __agen Addr1,Addr2;

            Addr1 = i*inPitch*ELEMSZ  + j*2*VECTORSZ;
            Addr2 = i*outPitch*ELEMSZ + j*VECTORSZ;

            (vIn024_14, vIn135_15)= (pIn)[Addr1].deinterleave();
            (vIn246_16, vIn357_17)= (pIn+ 2*ELEMSZ)[Addr1].deinterleave();
            (vIn468_18, vIn579_19)= (pIn+ 4*ELEMSZ)[Addr1].deinterleave();

            vTemp1      = vIn135_15 + vIn357_17;
            vTemp2      = vIn468_18 + vIn024_14;
            vTemp       = vIn246_16*C_6;
            vTemp1      = vTemp1*C_4;
            vTemp2     += vTemp1 + vTemp;
            pOut[Addr2] = vTemp2.truncate(4);

        }
    }
}

/*----------------------------------------------------------------------------------*/
/* Input to this kernel is WxH block and output of this kernel is (W) x (H/2) block */
/*----------------------------------------------------------------------------------*/
void vcop_gauss5x5PyramidKernel_16_vert
(
    __vptr_uint16   pIn,
    __vptr_uint16   pOut,
    unsigned short width,
    unsigned short height,
    unsigned short inPitch,
    unsigned short outPitch
)
{
    __vector vec1_e,vec2_e,vec3_e,vec4_e, vec5_e, vTemp_e, vec1_o,vec2_o,vec3_o,vec4_o, vec5_o, vTemp_o, C_4, C_6;
    __vector  vTemp1,vTemp2;

    C_4 = 4;
    C_6 = 6;

    for(int i = 0; i < (height/2); i++)
    {
        for(int j = 0; j < ALIGN_SIMD2(width)/VCOP_SIMD_WIDTH2; j++)
        {
            __agen Addr1,Addr2;

            Addr1 = i*2*inPitch*ELEMSZ + j*2*VECTORSZ;
            Addr2 = i*outPitch*ELEMSZ  + j*2*VECTORSZ  ;

            (vec1_e, vec1_o) = (pIn                   )[Addr1].deinterleave();
            (vec2_e, vec2_o) = (pIn+   inPitch*ELEMSZ )[Addr1].deinterleave();
            (vec3_e, vec3_o) = (pIn+ 2*inPitch*ELEMSZ )[Addr1].deinterleave();
            (vec4_e, vec4_o) = (pIn+ 3*inPitch*ELEMSZ )[Addr1].deinterleave();
            (vec5_e, vec5_o) = (pIn+ 4*inPitch*ELEMSZ )[Addr1].deinterleave();

            vTemp1  = vec2_e + vec4_e;
            vec1_e += vec5_e;
            vTemp_e = vec3_e*C_6;
            vTemp1  = vTemp1*C_4;
            vec1_e  += vTemp_e + vTemp1   ;

            vTemp2  = vec2_o + vec4_o;
            vec1_o += vec5_o;
            vTemp_o = vec3_o*C_6;
            vTemp2  = vTemp2*C_4;
            vec1_o  += vTemp_o + vTemp2   ;

            pOut[Addr2].interleave() = (vec1_e, vec1_o).truncate(4);
        }
    }
}

/* ======================================================================== */
/*  End of file: vcop_gauss5x5PyramidKernel_8_kernel.k                      */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

