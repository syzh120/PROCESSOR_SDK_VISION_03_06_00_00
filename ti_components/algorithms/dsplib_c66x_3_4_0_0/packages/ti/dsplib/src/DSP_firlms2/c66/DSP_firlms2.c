/* ======================================================================= */
/*  TEXAS INSTRUMENTS, INC.                                                */
/*                                                                         */
/*  DSPLIB  DSP Signal Processing Library                                  */
/*                                                                         */
/*  This library contains proprietary intellectual property of Texas       */
/*  Instruments, Inc.  The library and its source code are protected by    */
/*  various copyrights, and portions may also be protected by patents or   */
/*  other legal protections.                                               */
/*                                                                         */
/*  This software is licensed for use with Texas Instruments TMS320        */
/*  family DSPs.  This license was provided to you prior to installing     */
/*  the software.  You may review this license by consulting the file      */
/*  TI_license.PDF which accompanies the files in this library.            */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*                                                                         */
/* DSP_firlms2.c -- Least Mean Square Adaptive Filter                      */
/*                  Intrinsic C Implementation                             */
/*                                                                         */
/* REV 0.0.1                                                               */
/*                                                                         */
/* USAGE                                                                   */
/*                                                                         */
/*      This routine has the following C prototype:                        */
/*                                                                         */
/*          int DSP_firlms2 (                                              */
/*              short       *restrict h,  // Filter Coefficients           */
/*              short       *restrict x,  // Input Data                    */
/*              short                 b,  // Error from previous FIR       */
/*              int                   nh, // Number of Coefficients        */
/*          )                                                              */
/*                                                                         */
/*      The DSP_firlms2 routine accepts a list of 'nh' input data and 'nh' */
/*      adaptive filter coefficients and updates the coefficients by       */
/*      adding weighted error times the inputs to the original             */
/*      coefficients. This assumes single sample input followed by the     */
/*      last nh-1 inputs and nh coefficients.                              */
/*                                                                         */
/* ASSUMPTIONS                                                             */
/*                                                                         */
/*      - Assumes 16-bit input data, error and filter coefficients.        */
/*      - nh > = 4 and is a multiple of 4                                  */
/*      - The Kernel assumes the filter coefficients are aligned to 8byte  */
/*        booundary                                                        */
/*      - The Kernel doesn't assumes any alignment for input data          */
/*      - The Kernel doesn't use any extra memory padding                  */
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

#pragma CODE_SECTION(DSP_firlms2, ".text:optimized");

#include "DSP_firlms2.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

#ifdef _LITTLE_ENDIAN
int DSP_firlms2 (
    short * restrict h,     /* h  = Point to Coefficient Array */
    short * restrict x,     /* x  = Point to Input Array       */
    short   b,              /* b  = Error from Previous FIR    */
    int     nh              /* nh = Number of Coefficients     */
)
{
    int b_2, i;
    long long * restrict h_ptr, * restrict x_ptr, * restrict x_ptr1;
    long long r, h_3210, x_3210, x_3120, x_4321, b_4;
    __x128_t  xb3120;

    /* Make a copy of the coefficient array */
    h_ptr = (long long*) h;

    /* Combine error into double word */
    b_2 = _pack2 (b, b);
    b_4 = _itoll (b_2, b_2);

    /* Create new data pointer for input array */
    x_ptr  = (long long*) x;
    x_ptr1 = (long long*) (x+1);

    /* Clear the result to start with */
    r = 0;

    /* The kernel assumes nh is multiple of 4 */
    for (i = 0; i < nh >> 2; i++) {
        
        /* Kernel assumes coefficient array is aligned to 8 byte boundary */
        h_3210 = _amem8(h_ptr);

        /* Kernel does NOT assumes any memory alignemnt for input data */
        x_3210 = _mem8(x_ptr++);
        x_3120 = _itoll(_packh2(_hill(x_3210), _loll(x_3210)),
                        _pack2 (_hill(x_3210), _loll(x_3210)));

        /* Load x to calculate next error */
        x_4321 = _mem8(x_ptr1++);

        /* Update h */
        xb3120 = _dsmpy2(b_4, x_3120);
        h_3210 = _dadd2(h_3210, _dpackh2(_hi128(xb3120), _lo128(xb3120)));
        _amem8(h_ptr++) = h_3210;

        /* Calculate the result r */
        r += _dotp4h(x_4321, h_3210);
    }

    /* Return the result */
    return r;
}
#else
int DSP_firlms2 (
    short * restrict h,     /* h   = Point to Coefficient Array */
    short * restrict x,     /* x   = Point to Input Array       */
    short   b,            /* b = Error from Previous FIR    */
    int     nh              /* nh  = Number of Coefficients     */
)
{
    int b_2, i;
    long long * restrict h_ptr, * restrict x_ptr, * restrict x_ptr1;
    long long r, h_0123, x_0123, x_0213, x_1234, b_4;
    __x128_t  xb0213;

    /* Make a copy of the coefficient array */
    h_ptr = (long long*) h;

    /* Combine error into double word */
    b_2 = _pack2 (b, b);
    b_4 = _itoll (b_2, b_2);

    /* Create new data pointer for input array */
    x_ptr  = (long long*) x;
    x_ptr1 = (long long*) (x+1);

    /* Clear the result to start with */
    r = 0;

    /* The kernel assumes nh is multiple of 4 */
    for (i = 0; i < nh >> 2; i++) {
        
        /* Kernel assumes coefficient array is aligned to 8 byte boundary */
        h_0123 = _amem8(h_ptr);

        /* Kernel does NOT assumes any memory alignemnt for input data */
        x_0123 = _mem8(x_ptr++);
        x_0213 = _itoll(_packh2(_hill(x_0123), _loll(x_0123)),
                        _pack2 (_hill(x_0123), _loll(x_0123)));

        /* Load x to calculate next error */
        x_1234 = _mem8(x_ptr1++);

        /* Update h */
        xb0213 = _dsmpy2(b_4, x_0213);
        h_0123 = _dadd2(h_0123, _dpackh2(_hi128(xb0213), _lo128(xb0213)));
        _amem8(h_ptr++) = h_0123;

        /* Calculate the result r */
        r += _dotp4h(x_1234, h_0123);
    }

    /* Return the result */
    return r;
}
#endif
/* ======================================================================== */
/*  End of file:  DSP_firlms2.c                                             */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

