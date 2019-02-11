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

/*                                                                          */
/*    @file : vcop_extract_bit_field_u32_kernel.k                           */
/*                                                                          */
/*    @brief : This routine accepts an array of 32-bit values. The outputs  */
/*         is a list of extracted 8-bit bit-fields.                         */
/*                                                                          */
/*     The recommended banks for each of the buffers is captured as A/B/C   */
/*     as part of the buffer pointer. A/B/C can either be IMBUF High,       */
/*     IMBUF low or WMEM.                                                   */
/*                                                                          */
/*    USAGE:                                                                */
/*    This routine is C-callable and can be called as:                      */
/*                                                                          */
/*    void vcop_extract_bit_field_u32                                       */
/*    (                                                                     */
/*        __vptr_uint32  *inArray_A,                                        */
/*        unsigned short  length,                                           */
/*        unsigned int    bit_mask,                                         */
/*        unsigned char   shift,                                            */
/*        __vptr_uint8   *outList_B                                         */
/*    )                                                                     */
/*                                                                          */
/*     inArray_A    : Input list to be pruned                               */
/*     length       : Length of the input array                             */
/*     bit_mask     : Bit mask indicating the bits to be selected.          */
/*     shift        : Shift required to align LSB                           */
/*     outList_B    : List of extracted bit-fields                          */
/*                                                                          */
/*    Returns     :  None or void.                                          */
/*                                                                          */
/*    PERFORMANCE MEASUREMENT:                                              */
/*      1 cycles/pixel + 54 cycle VCOP overheads                            */
/*                                                                          */
/*    @author  : Anoop K P(a-kp@ti.com)                                     */
/*                                                                          */
/*    @version : 1.0 (Dec 2013) : Base version.                             */
/*                                                                          */
/*==========================================================================*/

#if VCOP_HOST_EMULATION
  #include <vcop.h>
#endif

#define IN_ELEMSZ (sizeof(*inArray_A))
#define IN_VECTORSZ (VCOP_SIMD_WIDTH*IN_ELEMSZ)

#define OUT_ELEMSZ (sizeof(*outList_B))
#define OUT_VECTORSZ (VCOP_SIMD_WIDTH*OUT_ELEMSZ)

void vcop_extract_bit_field_u32
(
    __vptr_uint32   inArray_A,
    unsigned short  length,
    unsigned int    bit_mask,
    unsigned char   shift,
    __vptr_uint8    outList_B
)
{
    __vector Vmask;

    Vmask = bit_mask;

    for(int I1 = 0; I1 < (length + VCOP_SIMD_WIDTH - 1)/VCOP_SIMD_WIDTH; I1++) {
        __agen Addr_in, Addr_out;
        __vector Vin, Vout;

        Addr_in = I1*IN_VECTORSZ;
        Addr_out = I1*OUT_VECTORSZ;

        Vin = inArray_A[Addr_in];

        Vout = Vin & Vmask;

        outList_B[Addr_out] = Vout.truncate(shift);
    }
}
