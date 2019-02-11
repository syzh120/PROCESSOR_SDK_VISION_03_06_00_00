/*
*
* Copyright (c) 2012-2017 Texas Instruments Incorporated
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


/**
 * Returns the Bhattacharyya (aka Hellinger) Distance between two input arrays of U16 variables.
 * @see http://en.wikipedia.org/wiki/Bhattacharyya_distance#Bhattacharyya_coefficient
 * @see http://en.wikipedia.org/wiki/Hellinger_distance
 */
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define ELEMSZ_A        	sizeof(*in1_ptr)
#define ELEMSZ_B			sizeof(*log4_ptr)
#define ELEMSZ_C			sizeof(*out_ptr)
#define VCOP_2SIMD_WIDTH	(2*VCOP_SIMD_WIDTH)
#define VECTORSZ_A			(VCOP_2SIMD_WIDTH*ELEMSZ_A)
#define VECTORSZ_B			(VCOP_2SIMD_WIDTH*ELEMSZ_B)
#define VECTORSZ_C			(VCOP_SIMD_WIDTH*ELEMSZ_A)
#define VECTORSZ_D			(VCOP_SIMD_WIDTH*ELEMSZ_B)
#define VECTORSZ_E			(VCOP_SIMD_WIDTH*ELEMSZ_C)

#define ELEM_TLU_SZ			(sizeof(*inp_data))
#define VECTOR_TLU_SZ		(ELEM_TLU_SZ)
#define ROW_TLU_SZ			((blk_wdth) * VECTOR_TLU_SZ)

#define MAX_U16_B 65536

#define normH MAX_U16_B/15360

void vcop_bhattacharyaDistance
(
	__vptr_int16 X_ptr,
    __vptr_int16 Y_ptr,
    unsigned short num,
    __vptr_int16 in1_ptr
)
{
	__vector Vin1, Vin2, Vin_x, Vin_y;
	__vector Vout;

	__vector R0;

	for (int I1 = 0; I1 < num/VCOP_SIMD_WIDTH; I1++)
	{
		__agen Addr;

		R0 = normH;

		Addr = I1*VECTORSZ_C;

		Vin_x = X_ptr[Addr];
		Vin_y = Y_ptr[Addr];

		Vin1 = Vin_x * R0;
		Vin2 = Vin_y * R0;

		Vout = Vin1 * Vin2;
		in1_ptr[Addr] = Vout;
	}
}


void eve_array_sqrt_intlv_lut_idx_log4
(
   __vptr_uint16  in1_ptr,        // input data pointer
   __vptr_uint16  TLU_idx_ptr,    // lookup table index
    __vptr_uint8  log4_ptr,       // log4(x)
  unsigned short  num_data,       // number of elements
             int  TLU_Qbits_p1,
             int  idx_norm2
)
{
   __vector Vin1,      Vin2;
   __vector Vone,      Vneg_one;
   __vector Vlmbd1,    Vlmbd2;
   __vector VQbits_p1, Vidx_norm2;
   __vector Vlog4_1,   Vlog4_2;
   __vector Vlog2_1,   Vlog2_2;
   __vector Vmant1,    Vmant2;
   __vector Vshft1,    Vshft2;
   __vector Vlut_idx1, Vlut_idx2;
   __vector Vtwo;

    Vone       = 1;
    Vneg_one   = -1;
    VQbits_p1  = TLU_Qbits_p1;
    Vidx_norm2 = idx_norm2;
    Vtwo       = 2;

    for (int I4 = 0; I4 < num_data/VCOP_2SIMD_WIDTH; I4++)
    {
        __agen Addr1, Addr2;

        Addr1 = I4*VECTORSZ_A;
        Addr2 = I4*VECTORSZ_B;

        (Vin1,Vin2) = in1_ptr[Addr1].deinterleave();

        /* ----------------------------------------------------------------- */
        /* Get LMBD                                                          */
        /* ----------------------------------------------------------------- */

        Vlmbd1 = leading_bit(Vin1, Vone);
        Vlmbd2 = leading_bit(Vin2, Vone);


        /* ----------------------------------------------------------------- */
        /* log4(x) ~= LMBD(x)/2                                              */
        /* ----------------------------------------------------------------- */

        Vlog4_1 = Vlmbd1 << Vneg_one;
        Vlog4_2 = Vlmbd2 << Vneg_one;


        /* ----------------------------------------------------------------- */
        /* Calculate (Q+1) - 2*log4(x), which is the shift amount needed to  */
        /* compute the scaled (2*mantissa).                                  */
        /* ----------------------------------------------------------------- */

        Vlog2_1 = Vlog4_1 << Vone;
        Vlog2_2 = Vlog4_2 << Vone;

        Vshft1 = VQbits_p1 - Vlog2_1;
        Vshft2 = VQbits_p1 - Vlog2_2;


        /* ----------------------------------------------------------------- */
        /* Compute (2*mantissa(x))                                           */
        /* Mantissa range is [1,4] scaled by 2^Q, which is included in the   */
        /* shift amount.                                                     */
        /* ----------------------------------------------------------------- */

        Vmant1 = Vin1 << Vshft1;
        Vmant2 = Vin2 << Vshft2;


        /* ----------------------------------------------------------------- */
        /* Compute LUT idx by subtracting "1" from the scaled mantissa.      */
        /* Where "1" is represented as 2^Q                                   */
        /* ----------------------------------------------------------------- */

        Vlut_idx1 = Vmant1 - Vidx_norm2;
        Vlut_idx2 = Vmant2 - Vidx_norm2;


        /* ----------------------------------------------------------------- */
        /* Save TLU index which we will use to get sqrt(mantissa(x))         */
        /* ----------------------------------------------------------------- */

        TLU_idx_ptr[Addr1].interleave() = (Vlut_idx1, Vlut_idx2).round(1);


        /* ----------------------------------------------------------------- */
        /* Save out int(log4(x)) value, which we will use later to compute   */
        /* the product expression:                                           */
        /*                                                                   */
        /*    sqrt(x) = sqrt(2^(2*int(lmbd(x)/2))) * sqrt(mantissa(x))       */
        /*                                                                   */
        /* Saving out log4(x) is sufficient since                            */
        /*                                                                   */
        /*    sqrt(2^(2*int(lmbd(x)/2))) = 2^int(lmbd(x)/2) = int(log4(x))   */
        /*                                                                   */
        /* ----------------------------------------------------------------- */

        log4_ptr[Addr2].interleave()    = (Vlog4_1, Vlog4_2);
    }
}



void eve_tlu_1c_hword
(
	__vptr_uint16  Table,
    __vptr_uint16  inp_data,
    unsigned int   blk_hght,
    unsigned int   blk_wdth,
    __vptr_uint16  Out
)
{
   __vector Vindex, Vdata;
   __vector Vout;


    /*--------------------------------------------------------------*/
    /*  Define explicitly that loop below is a table lookup loop.   */
    /*--------------------------------------------------------------*/

   _LOOKUP(1,1);


   for (int i3 = 0; i3 < blk_hght; i3++)
   {
      for (int i4 = 0; i4 < blk_wdth; i4++)
      {
         __agen TLU_agen = 0;
         __agen ind_agen  = i3*ROW_TLU_SZ + i4*VECTOR_TLU_SZ;
         __agen out_agen  = i3*ROW_TLU_SZ + i4*VECTOR_TLU_SZ;

         Vindex  = inp_data[ind_agen];
         Vdata   = Table[TLU_agen].lookup(Vindex);
         Out[out_agen].table_npt() = Vdata;
      }
   }

}


void eve_array_sqrt_intlv_align
(
   __vptr_uint16  in1_ptr,        // input 1 data pointer
    __vptr_uint8  log4_ptr,       // log4(in1_ptr)
  unsigned short  num_data,       // number of elements
   __vptr_uint32  out_ptr

)
{
   __vector Vin,      Vlog4;
   __vector Vout1, Vout;

    for (int I4 = 0; I4 < num_data/VCOP_SIMD_WIDTH; I4++)
    {
        __agen Addr1, Addr2, Addr3;

        Addr1 = I4*VECTORSZ_C;
        Addr2 = I4*VECTORSZ_D;
        Addr3 = I4*VECTORSZ_E;

        Vin   = in1_ptr[Addr1];
        Vlog4 = log4_ptr[Addr2];


        /* ----------------------------------------------------------------- */
        /* Compute the product expression:                                   */
        /*                                                                   */
        /*        sqrt(x) = sqrt(2^(2*int(lmbd(x)/2))) * sqrt(mantissa(x))   */
        /*                                                                   */
        /*                      "2^int(lmbd(x)/2)"         "TLU"             */
        /* ----------------------------------------------------------------- */

        Vout = Vin << Vlog4;

        //Vout += Vout1;

        out_ptr[Addr3] = Vout;
    }
}

