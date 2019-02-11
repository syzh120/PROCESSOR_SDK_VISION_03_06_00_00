/* ======================================================================= */
/* DSPF_sp_mat_mul_gemm.c -- Matrix Multiply "y = a*x1*x2+y"               */
/*              Optimized C Implementation (w/ Intrinsics)                 */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/  */ 
/*                                                                         */
/*                                                                         */
/*  Redistribution and use in source and binary forms, with or without     */
/*  modification, are permitted provided that the following conditions     */
/*  are met:                                                               */
/*                                                                         */
/*    Redistributions of source code must retain the above copyright       */
/*    notice, this list of conditions and the following disclaimer.        */
/*                                                                         */
/*    Redistributions in binary form must reproduce the above copyright    */
/*    notice, this list of conditions and the following disclaimer in the  */
/*    documentation and/or other materials provided with the               */
/*    distribution.                                                        */
/*                                                                         */
/*    Neither the name of Texas Instruments Incorporated nor the names of  */
/*    its contributors may be used to endorse or promote products derived  */
/*    from this software without specific prior written permission.        */
/*                                                                         */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    */
/*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  */
/*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  */
/*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   */
/*                                                                         */
/* ======================================================================= */

#pragma CODE_SECTION(DSPF_sp_mat_mul_gemm, ".text:optimized");

#include "DSPF_sp_mat_mul_gemm.h"
#ifdef __TI_COMPILER_VERSION__            // for TI compiler only
#include "c6x.h"
#endif

void DSPF_sp_mat_mul_gemm(float *restrict x1, float const a, const int r1, const int c1,
    float *restrict x2, const int c2, float *restrict y)
{
    int    i, j, k, xoff1, xoff2;
    float  *restrict y0, *restrict y1, *restrict y2, *restrict y3;
    float  *ptr_x, *ptr_y;
    __float2_t x_01, x_23, x_45, x_67, y_01, y_23, y_45, y_67, a_a;
    __float2_t sum0, sum1, sum2, sum3, sum4, sum5, sum6, sum7;
    __float2_t sum8, sum9, suma, sumb, sumc, sumd, sume, sumf;
    __x128_t temp1, temp2, temp3, temp4, temp5;

    _nassert(r1 > 0);
    _nassert(c1 > 0);
    _nassert(c2 > 0);
    _nassert((int)x1 % 8 == 0);
    _nassert((int)x2 % 8 == 0);
    _nassert((int)y  % 8 == 0 );
    _nassert(r1 % 4 == 0 );
    _nassert(c2 % 4 == 0 );
    _nassert(c1 % 2 == 0 );

    #pragma MUST_ITERATE(1,,)
    for (j = 0; j < c2; j+=4) {

        xoff2 = j * c1;
        y0 = &y[(j + 0) * r1];
        y1 = &y[(j + 1) * r1];
        y2 = &y[(j + 2) * r1];
        y3 = &y[(j + 3) * r1]; 

        #pragma MUST_ITERATE(1,,)
        for (i = 0; i < r1; i+=4) {
            sum0  = 0;
            sum1  = 0;
            sum2  = 0;
            sum3  = 0;
            sum4  = 0;
            sum5  = 0;
            sum6  = 0;
            sum7  = 0;
            sum8  = 0;
            sum9  = 0;
            suma  = 0;
            sumb  = 0;
            sumc  = 0;
            sumd  = 0;
            sume  = 0;
            sumf  = 0;
            xoff1 = i * c1;                                                 
            ptr_x = &x1[xoff1];
            ptr_y = &x2[xoff2];

            #pragma MUST_ITERATE(1,,)
            for (k = 0; k < c1; k+=2,ptr_x+=2,ptr_y+=2) {
                x_01 = _amem8_f2_const(&ptr_x[0]);
                x_23 = _amem8_f2_const(&ptr_x[c1]);
                x_45 = _amem8_f2_const(&ptr_x[2 * c1]);
                x_67 = _amem8_f2_const(&ptr_x[3 * c1]);
                y_01 = _amem8_f2_const(&ptr_y[0]);
                y_23 = _amem8_f2_const(&ptr_y[c1]);
                y_45 = _amem8_f2_const(&ptr_y[2 * c1]);
                y_67 = _amem8_f2_const(&ptr_y[3 * c1]);

                sum4 = _daddsp(sum4, _dmpysp(x_01, y_23));
                sum1 = _daddsp(sum1, _dmpysp(x_23, y_01));
                sum8 = _daddsp(sum8, _dmpysp(x_01, y_45));
                sumd = _daddsp(sumd, _dmpysp(x_23, y_67));
                sumc = _daddsp(sumc, _dmpysp(x_01, y_67));
                sum9 = _daddsp(sum9, _dmpysp(x_23, y_45));
                sum2 = _daddsp(sum2, _dmpysp(x_45, y_01));
                sum7 = _daddsp(sum7, _dmpysp(x_67, y_23));
                sum6 = _daddsp(sum6, _dmpysp(x_45, y_23));
                sum3 = _daddsp(sum3, _dmpysp(x_67, y_01));
                sume = _daddsp(sume, _dmpysp(x_45, y_67));
                sumb = _daddsp(sumb, _dmpysp(x_67, y_45));

                temp1 = _f2to128(x_01, x_23);
                temp2 = _f2to128(y_01, y_23);
                temp3 = _qmpysp(temp1, temp2);
                sum0  = _daddsp(sum0, _hif2_128(temp3));
                sum5  = _daddsp(sum5, _lof2_128(temp3));

                temp4 = _f2to128(x_45, x_67);
                temp5 = _f2to128(y_45, y_67);
                temp3 = _qmpysp(temp4, temp5);
                suma  = _daddsp(suma, _hif2_128(temp3));
                sumf  = _daddsp(sumf, _lof2_128(temp3));
            }
#ifdef _LITTLE_ENDIAN
            sum0 = _ftof2(_hif2(sum1) + _lof2(sum1), _hif2(sum0) + _lof2(sum0));
            sum2 = _ftof2(_hif2(sum3) + _lof2(sum3), _hif2(sum2) + _lof2(sum2));
            sum4 = _ftof2(_hif2(sum5) + _lof2(sum5), _hif2(sum4) + _lof2(sum4));
            sum6 = _ftof2(_hif2(sum7) + _lof2(sum7), _hif2(sum6) + _lof2(sum6));
            sum8 = _ftof2(_hif2(sum9) + _lof2(sum9), _hif2(sum8) + _lof2(sum8));
            suma = _ftof2(_hif2(sumb) + _lof2(sumb), _hif2(suma) + _lof2(suma));
            sumc = _ftof2(_hif2(sumd) + _lof2(sumd), _hif2(sumc) + _lof2(sumc));
            sume = _ftof2(_hif2(sumf) + _lof2(sumf), _hif2(sume) + _lof2(sume));
#else
            sum0 = _ftof2(_hif2(sum0) + _lof2(sum0), _hif2(sum1) + _lof2(sum1));
            sum2 = _ftof2(_hif2(sum2) + _lof2(sum2), _hif2(sum3) + _lof2(sum3));
            sum4 = _ftof2(_hif2(sum4) + _lof2(sum4), _hif2(sum5) + _lof2(sum5));
            sum6 = _ftof2(_hif2(sum6) + _lof2(sum6), _hif2(sum7) + _lof2(sum7));
            sum8 = _ftof2(_hif2(sum8) + _lof2(sum8), _hif2(sum9) + _lof2(sum9));
            suma = _ftof2(_hif2(suma) + _lof2(suma), _hif2(sumb) + _lof2(sumb));
            sumc = _ftof2(_hif2(sumc) + _lof2(sumc), _hif2(sumd) + _lof2(sumd));
            sume = _ftof2(_hif2(sume) + _lof2(sume), _hif2(sumf) + _lof2(sumf));
#endif
            a_a  = _ftof2(a, a);
            sum0 = _dmpysp(a_a, sum0);
            sum2 = _dmpysp(a_a, sum2);
            sum4 = _dmpysp(a_a, sum4);
            sum6 = _dmpysp(a_a, sum6);
            sum8 = _dmpysp(a_a, sum8);
            suma = _dmpysp(a_a, suma);
            sumc = _dmpysp(a_a, sumc);
            sume = _dmpysp(a_a, sume);

            _amem8_f2(&y0[(i + 0)]) = _daddsp(sum0, _amem8_f2(&y0[(i + 0)]));
            _amem8_f2(&y0[(i + 2)]) = _daddsp(sum2, _amem8_f2(&y0[(i + 2)]));
            _amem8_f2(&y1[(i + 0)]) = _daddsp(sum4, _amem8_f2(&y1[(i + 0)]));
            _amem8_f2(&y1[(i + 2)]) = _daddsp(sum6, _amem8_f2(&y1[(i + 2)]));
            _amem8_f2(&y2[(i + 0)]) = _daddsp(sum8, _amem8_f2(&y2[(i + 0)]));
            _amem8_f2(&y2[(i + 2)]) = _daddsp(suma, _amem8_f2(&y2[(i + 2)]));
            _amem8_f2(&y3[(i + 0)]) = _daddsp(sumc, _amem8_f2(&y3[(i + 0)]));
            _amem8_f2(&y3[(i + 2)]) = _daddsp(sume, _amem8_f2(&y3[(i + 2)]));
        }
    }                                        
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_mat_mul_gemm.c                                   */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */



