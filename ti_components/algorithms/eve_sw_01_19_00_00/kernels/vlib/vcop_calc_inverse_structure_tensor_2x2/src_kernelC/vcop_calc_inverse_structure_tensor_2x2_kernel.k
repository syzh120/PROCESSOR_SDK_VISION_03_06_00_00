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

/*--------------------------------------------------------------------------*/
/* NAME: vcop_calc_inverse_structure_tensor_2x2_kernel.k                    */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*                                                                          */
/* The file provides kernel for computing inverse of the 2x2 structure      */
/* tensor which is quite commonly used in vision applications               */
/*                                                                          */
/* Calculate inverse of 2x2 structure tensor kernel accepts the structure   */
/* tensor elements which includes summation of squared gradients over the   */
/* given neighborhood window such as 7x7 along with determinant of the      */
/* 2x2 structure tensor matrix. The squared gradients include product of    */
/* GradX * GradX; GradY * GradY; GradX * GradY where GradX denotes gradient */
/* along X and GradY denotes gradient along Y directions respectively       */
/* The outputs of this kernel essentially provides result obtained by       */
/* dividing squared gradients summation with determinant, D of structure    */
/* tensor                                                                   */
/* That is, the outputs include the following:                              */
/* SUM(GradX*GradX)/D, SUM(GradY*GradY)/D, SUM(GradX*GradY)/D,              */
/* The dimension of each output is (numKeyPoints x 2) and each output       */
/* includes the fractional and exponential parts and therefore factor of 2  */
/* is used                                                                  */
/*                                                                          */
/* ASSUMPTIONS:                                                             */
/*   1. Fractional and exponential parts are used for denoting determinant  */
/*   2. All inputs should have their dimension equal to numKeyPoints        */
/*                                                                          */
/* RECOMMENDATIONS FOR OPTIMAL PERFORMANCE                                  */
/*   1. numKeyPoints is multiple of 8                                       */
/*                                                                          */
/* PERFORMANCE:                                                             */
/*                                                                          */
/*   vcop_calc_inverse_structure_tensor_2x2:                                */
/*   - ~ = 3*(6 + 6) * numKeyPoints + 50 cycles loop overhead               */
/*                                                                          */
/* @author Venkat R Peddigari (a0393744@ti.com)                             */
/*                                                                          */
/* version 1.0 (November 2013) : Base version.                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define INP_ELEMSZ          sizeof(*pTensorArrInp_A)
#define INP_VECTORSZ        (VCOP_SIMD_WIDTH*INP_ELEMSZ)
#define OUT_ELEMSZ          sizeof(*pInverseArrOut_A)
#define OUT_VECTORSZ        (VCOP_SIMD_WIDTH*OUT_ELEMSZ)
#define M2_DIVIDE_BITS 9
#define M2_FRAC_BITS 4
#define NUM_TENSOR_ARR_ELEM  3

void vcop_calc_inverse_structure_tensor_2x2
(
    __vptr_int32      pTensorArrInp_A,
    __vptr_uint16     pD_nrsb_B,
    __vptr_uint32     pD_norm_C,
    __vptr_int16      pInverseArrOut_A,
    __vptr_int32      pScratchNorm_C,
    __vptr_uint32     pScratchDividend_C,
    unsigned short    inputStride,
    unsigned short    outputStride,
    unsigned short    numFracBits,
    unsigned short    numKeyPoints
)
{
    __vector Vn, Vn1, Vn2, Vd_nrsb, Vn_nrsb, Vout_exp;
    __vector Vleadbit, Vsign;
    __vector Vshift32, Vcst30, VcstZero, VcstOne, Vcst31_M2_DIVIDE_BITS_M2_FRAC_BITS, VdivbitsMask;
    __vector V_quotientA, V_quotientB, V_dividendA, V_dividendB, V_dividend, Vd_norm;

#define Vn_norm Vn
#define V_quotientOut Vleadbit
#define Vgt Vsign
#define V_divider Vd_norm
#define V_quotient VcstZero

    Vshift32= -32;
    Vcst30= 30;
    VcstZero= 0;
    VcstOne= 1;
    Vleadbit= 1;
    Vcst31_M2_DIVIDE_BITS_M2_FRAC_BITS= 32 + (M2_DIVIDE_BITS-1) - numFracBits;
    VdivbitsMask = ~((1 << M2_DIVIDE_BITS) -1);
    /*
    int a_nrsb = _norm(zxx) - 1;
    int a_norm = zxx << a_nrsb;//QS0.31

    int b_nrsb = _norm(zyy) - 1;
    int b_norm = zyy << b_nrsb;//QS0.31

    int c_nrsb = norm(zxy);
    int c_norm = zxy << c_nrsb;//QS0.31
     */
    for (int I2 = 0; I2 < NUM_TENSOR_ARR_ELEM; I2++)
    {
        for (int I1 = 0; I1 < (numKeyPoints+VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I1++)
        {
            __agen Addr_in, Addr_norm, Addr_nrsb;
            __agen Addr_out;

            Addr_in   = I2*inputStride*INP_ELEMSZ+I1*INP_VECTORSZ;
            Addr_norm = I1*INP_VECTORSZ;
            Addr_nrsb = I1*OUT_VECTORSZ;
            Addr_out  = I2*outputStride*OUT_ELEMSZ+I1*2*OUT_VECTORSZ;

            Vn       = pTensorArrInp_A[Addr_in].npt();
            Vd_norm  = pD_norm_C[Addr_norm].npt();
            Vd_nrsb  = pD_nrsb_B[Addr_nrsb].npt();

            Vd_norm = Vd_norm & VdivbitsMask;
            // Find number of non-redundant sign bits in numerator
            // First determine sign of Vn
            // Vsign will contain -1 if Vn negative, otherwise it will be 0
            Vsign  = Vn << Vshift32;

            // Then determine the bit we are looking for, 0 or 1
            // For positive numbers, we search for leading bit = 1 & for negative numbers, leading bit = 0
            Vleadbit = VcstOne + VcstZero;
            Vleadbit  = select(Vsign, VcstZero, Vleadbit);

            // Then we detect leading bit position to get norm(Vn)
            Vn_nrsb  = leading_bit(Vn, Vleadbit);

            // Now get the quantity, (number of redundant bits - 1), to match DSP behaviour
            Vn_nrsb  = Vcst30 - Vn_nrsb;

            // int a_norm = zxx << a_nrsb;//QS0.31
            // int b_norm = zyy << b_nrsb;//QS0.31
            // int c_norm = zxy << c_nrsb;//QS0.31
            //Compute the norm now
            Vn_norm  = Vn  << Vn_nrsb;
            V_dividend  =  abs(Vn_norm);

            //(31-d_nrsb) + (M2_DIVIDE_BITS-1) - M2_FRAC_BITS;
            Vout_exp  = Vcst31_M2_DIVIDE_BITS_M2_FRAC_BITS - Vd_nrsb;

            Vout_exp    = Vn_nrsb  + Vout_exp;
            Vout_exp = VcstZero - Vout_exp;

            pD_nrsb_B[Addr_nrsb].npt()         = Vd_nrsb;
            pInverseArrOut_A[Addr_out].npt()   = Vout_exp;
            pD_norm_C[Addr_norm].npt()         = Vd_norm;
            pScratchNorm_C[Addr_in].npt()      = Vn_norm;
            pScratchDividend_C[Addr_in].npt()  = V_dividend;
        }
    }

    for (int I2 = 0; I2 < NUM_TENSOR_ARR_ELEM; I2++)
    {
        for (int I1=0; I1 < (numKeyPoints+VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH ; I1++)
        {
            __agen Addr_in, Addr_norm;
            __agen Addr_out;

            Addr_in   = I2*inputStride*INP_ELEMSZ+I1*INP_VECTORSZ;
            Addr_norm = I1*INP_VECTORSZ;
            Addr_out  = I2*outputStride*OUT_ELEMSZ+I1*2*OUT_VECTORSZ;

            V_divider  = pD_norm_C[Addr_norm].npt();
            Vn_norm    = pScratchNorm_C[Addr_in].npt();
            V_dividend = pScratchDividend_C[Addr_in].npt();
            Vout_exp   = pInverseArrOut_A[Addr_out].npt();

            V_quotient= 0;
            V_quotientA= 1;
            V_quotientB= 1;

            for (int J1 = 0; J1 < M2_DIVIDE_BITS; J1++)
            {
                // quotientA = (quotient<<1) | 1;
                V_quotientA |= V_quotient << VcstOne;

                // dividend = (dividend-divider)<<1;
                V_dividendA = V_dividend - V_divider;
                V_dividendA = V_dividendA << VcstOne;

                // quotientB = quotient<<1;
                V_quotientB  = V_quotient << VcstOne;

                // dividendB = dividend << 1;
                V_dividendB  = V_dividend << VcstOne;

                /*
                    if(dividend > divider){
                        quotient = quotientA;
                        dividend = dividendA;
                    }else{
                        quotient = quotientB;
                        dividend = dividendB;
                    }
                */
                Vgt = V_dividend > V_divider;
                V_quotientB = select(Vgt, V_quotientA, V_quotientB);
                V_dividendB = select(Vgt, V_dividendA, V_dividendB);

                V_quotient = V_quotientB;
                V_dividend = V_dividendB;

                /*
                    if(sign) quotient = -quotient;
                    return quotient;
                */
                V_quotientOut = apply_sign(Vn_norm, V_quotient);
                V_quotientA   = VcstOne;
            }
            pInverseArrOut_A[Addr_out].interleave() = (V_quotientOut, Vout_exp);
        }
    }
}
