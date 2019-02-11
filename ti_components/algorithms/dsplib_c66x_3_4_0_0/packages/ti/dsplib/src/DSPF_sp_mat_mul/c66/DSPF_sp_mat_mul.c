/* ======================================================================= */
/* DSPF_sp_mat_mul.c -- Matrix Multiply                                    */
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

#pragma CODE_SECTION(DSPF_sp_mat_mul, ".text:optimized");

#include "DSPF_sp_mat_mul.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

#ifdef _LITTLE_ENDIAN
void DSPF_sp_mat_mul(float *x1, const int r1, const int c1,
    float *x2, const int c2, float *restrict y)
{
    int i, j, k;
    float *ptr_x, *ptr_y;
    __float2_t sum0, sum1, sum2, sum3;
    __float2_t x_10, x_32, y_20, y_31, y_10, y_32;
    unsigned int xoff;

    _nassert(r1 > 0);
    _nassert(c1 > 0);
    _nassert(c2 > 0);
    _nassert( (int) x1 % 8 == 0 );
    _nassert( (int) x2 % 8 == 0 );
    _nassert( (int) y  % 8 == 0 );
    _nassert( r1 % 2 == 0 );
    _nassert( c2 % 2 == 0 );
    _nassert( c1 % 2 == 0 );

    /* ---------------------------------------------------- */
    /*  Multiply each row in x1 by each column in x2.  The  */
    /*  product of row m in x1 and column n in x2 is placed */
    /*  in position (m,n) in the result.                    */
    /* ---------------------------------------------------- */

    #pragma MUST_ITERATE(1,,)
    for (i = 0; i < r1; i+=2) {
        xoff = i*c1;

        #pragma MUST_ITERATE(1,,)
        for (j = 0; j < c2; j+=2) {                                                     
            sum0 = 0;
            sum1 = 0;
            sum2 = 0;
            sum3 = 0;
            
            ptr_x = &x1[xoff];
            ptr_y = &x2[j];
            
            #pragma MUST_ITERATE(1,,)
            for (k = 0; k < c1; k+=2,ptr_x+=2,ptr_y+=2*c2) {
                _amem8_f2(&x_10) = _amem8_f2_const(&ptr_x[0]);
                _amem8_f2(&x_32) = _amem8_f2_const(&ptr_x[c1]);
                _amem8_f2(&y_20) = _amem8_f2_const(&ptr_y[0]);
                _amem8_f2(&y_31) = _amem8_f2_const(&ptr_y[c2]);
              
                y_10 = _ftof2(_lof2(y_31), _lof2(y_20));
                y_32 = _ftof2(_hif2(y_31), _hif2(y_20));
              
                sum0 = _daddsp(sum0, _dmpysp(x_10, y_10));
                sum1 = _daddsp(sum1, _dmpysp(x_10, y_32));
                sum2 = _daddsp(sum2, _dmpysp(x_32, y_10));
                sum3 = _daddsp(sum3, _dmpysp(x_32, y_32));
            }
           
            _amem8_f2(&y[(i + 0)*c2 + j]) = _ftof2(_hif2(sum1) + _lof2(sum1),
                                                   _hif2(sum0) + _lof2(sum0));
            _amem8_f2(&y[(i + 1)*c2 + j]) = _ftof2(_hif2(sum3) + _lof2(sum3),
                                                   _hif2(sum2) + _lof2(sum2));
        }
    }                                                     
}
#else
void DSPF_sp_mat_mul(float *x1, const int r1, const int c1,
    float *x2, const int c2, float *restrict y)
{
    int i, j, k;
    float *ptr_x, *ptr_y;
    __float2_t sum0, sum1, sum2, sum3;
    __float2_t x_01, x_23, y_02, y_13, y_01, y_23;
    unsigned int xoff;

    _nassert(r1 > 0);
    _nassert(c1 > 0);
    _nassert(c2 > 0);
    _nassert( (int) x1 % 8 == 0 );
    _nassert( (int) x2 % 8 == 0 );
    _nassert( (int) y  % 8 == 0 );
    _nassert( r1 % 2 == 0 );
    _nassert( c2 % 2 == 0 );
    _nassert( c1 % 2 == 0 );

    /* ---------------------------------------------------- */
    /*  Multiply each row in x1 by each column in x2.  The  */
    /*  product of row m in x1 and column n in x2 is placed */
    /*  in position (m,n) in the result.                    */
    /* ---------------------------------------------------- */

    #pragma MUST_ITERATE(1,,)
    for (i = 0; i < r1; i+=2) {
        xoff = i*c1;

        #pragma MUST_ITERATE(1,,)
        for (j = 0; j < c2; j+=2) {                                                     
            sum0 = 0;
            sum1 = 0;
            sum2 = 0;
            sum3 = 0;
            
            ptr_x = &x1[xoff];
            ptr_y = &x2[j];
            
            #pragma MUST_ITERATE(1,,)
            for (k = 0; k < c1; k+=2,ptr_x+=2,ptr_y+=2*c2) {
                _amem8_f2(&x_01) = _amem8_f2_const(&ptr_x[0]);
                _amem8_f2(&x_23) = _amem8_f2_const(&ptr_x[c1]);
                _amem8_f2(&y_02) = _amem8_f2_const(&ptr_y[0]);
                _amem8_f2(&y_13) = _amem8_f2_const(&ptr_y[c2]);
              
                y_01 = _ftof2(_hif2(y_02), _hif2(y_13));
                y_23 = _ftof2(_lof2(y_02), _lof2(y_13));
              
                sum0 = _daddsp(sum0, _dmpysp(x_01, y_01));
                sum1 = _daddsp(sum1, _dmpysp(x_01, y_23));
                sum2 = _daddsp(sum2, _dmpysp(x_23, y_01));
                sum3 = _daddsp(sum3, _dmpysp(x_23, y_23));
            }
            
            _amem8_f2(&y[(i + 0)*c2 + j]) = _ftof2(_hif2(sum0) + _lof2(sum0),
                                                   _hif2(sum1) + _lof2(sum1));
            _amem8_f2(&y[(i + 1)*c2 + j]) = _ftof2(_hif2(sum2) + _lof2(sum2),
                                                   _hif2(sum3) + _lof2(sum3));
        }
    }                                                     
}
#endif
/* ======================================================================= */
/*  End of file:  DSPF_sp_mat_mul.c                                        */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
