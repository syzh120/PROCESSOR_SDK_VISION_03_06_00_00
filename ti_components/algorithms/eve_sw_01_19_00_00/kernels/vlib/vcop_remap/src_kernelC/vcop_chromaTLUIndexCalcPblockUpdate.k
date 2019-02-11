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

/* Compute the bilinear interpolated luma pixels for U8BIT format */
void vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate(
        __vptr_uint16       numMappedPixels_ptr,
        __vptr_uint16       pBlock16
)
{
#define NUM_ITERATIONS_LOOP_1_PTR (6)
        __vector VnumMappedPixels;
        __agen Addr0 = 0;

        VnumMappedPixels = numMappedPixels_ptr[Addr0].onept();

    for (int I1 = 0; I1 < 1; I1++) {

        __vector Vone, Vseven, Vshiftthree, Vloop1;

        Vone = 0x00000001;
        Vseven = 0x00000007;
        Vshiftthree = -3;

        VnumMappedPixels   = max(VnumMappedPixels, Vone);
        Vloop1   = VnumMappedPixels + Vseven;
        Vloop1   = Vloop1 << Vshiftthree;
        Vloop1   = Vloop1 - Vone;

        (pBlock16 + NUM_ITERATIONS_LOOP_1_PTR)[Addr0].onept()  = Vloop1;
    }
}

void vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate(
        __vptr_uint16       numMappedPixels_ptr,
        __vptr_uint16       pBlock16
)
{
#define NUM_ITERATIONS_LOOP_1_PTR (6)
        __vector VnumMappedPixels;
        __agen Addr0 = 0;

        VnumMappedPixels = numMappedPixels_ptr[Addr0].onept();

    for (int I1 = 0; I1 < 1; I1++) {

        __vector Vone, Vfifteen, Vshiftfour, Vloop1;

        Vone = 0x00000001;
        Vfifteen = 0x0000000F;
        Vshiftfour = -4;

        VnumMappedPixels   = max(VnumMappedPixels, Vone);
        Vloop1   = VnumMappedPixels + Vfifteen;
        Vloop1   = Vloop1 << Vshiftfour;
        Vloop1   = Vloop1 - Vone;

        (pBlock16 + NUM_ITERATIONS_LOOP_1_PTR)[Addr0].onept()  = Vloop1;
    }
}
