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


/*==========================================================================*/
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_image_pyramid_u8_one_level_kernel                               */
/*                                                                          */
/*S    REVISION HISTORY                                                    S*/
/*S    03/02/10..............Initial Version.........Sarthak Aggrwal       S*/
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_image_pyramid_u8                                           */
/*     (                                                                    */
/*        	 __vptr_uint8   pIn,                                            */
/*         	unsigned short inCols,                                          */
/*         	unsigned short inRows,                                          */
/*			__vptr_uint8   pOutY,											*/
/*			__vptr_uint8   pOutUV                                           */
/*     )                                                                    */
/*                                                                          */
/*     pIn      :  8-bit input image                                        */
/*     inCols   :  Number of coluns in the image                            */
/*     inRows   :  Number of rows in the image                              */
/*     pOutY    :  8-bit Y output image                                     */
/*     pOutUV    :  8-bit UV output image                                   */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts an 8-bit input image and outputs three  */
/*     levels of image pryamid in the pOut array.                           */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*     The number of columns in the input image should be a multiple of 16. */
/*                                                                          */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif


#define ELEMSZ          sizeof(*pInY)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)

void vcop_image_interleave_u8
(
    __vptr_uint8   pInY,
	__vptr_uint8   pInUV,
    unsigned short inCols,
    unsigned short inRows,
    __vptr_uint8   pOut
)
{
    __vector in00,in01,a,b;

    for( int I1 = 0; I1 < inRows; I1++)
    {
        for(int I2 = 0; I2 < inCols/(VCOP_SIMD_WIDTH); I2++)
        {
            __agen Addr1,Addr2;

            Addr1 = I1*inCols*ELEMSZ + I2*VECTORSZ;
            Addr2 = (2*inCols)*I1*ELEMSZ + I2*2*VECTORSZ  ;

            in00 = pInY[Addr1];
            in01 = pInUV[Addr1];

			//(in01,in00).interleave();
            //pOut[Addr2] = in01;
            //(pOut + VECTORSZ)[Addr2] = in00;

            a = in00;
            b = in01;
            pOut[Addr2].interleave() = (b,a);
        }
    }
}

/* ======================================================================== */
/*  End of file: vcop_image_pyramid_u8_one_level_kernel.k                   */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


